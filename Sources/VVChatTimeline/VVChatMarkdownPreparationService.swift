import Foundation
import VVMarkdown
import VVMetalPrimitives

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

extension MarkdownLayout: @unchecked Sendable {}
extension LayoutBlock: @unchecked Sendable {}
extension LayoutBlockType: @unchecked Sendable {}
extension LayoutContent: @unchecked Sendable {}
extension LayoutMermaidDiagram: @unchecked Sendable {}
extension LayoutDefinitionItem: @unchecked Sendable {}
extension LayoutAbbreviationItem: @unchecked Sendable {}
extension LayoutMermaidBackground: @unchecked Sendable {}
extension LayoutMermaidPieSlice: @unchecked Sendable {}
extension LayoutMermaidNodeShape: @unchecked Sendable {}
extension LayoutMermaidNode: @unchecked Sendable {}
extension LayoutMermaidLine: @unchecked Sendable {}
extension LayoutTextRun: @unchecked Sendable {}
extension LayoutInlineImage: @unchecked Sendable {}
extension TextRunStyle: @unchecked Sendable {}
extension LayoutGlyph: @unchecked Sendable {}
extension LayoutListItem: @unchecked Sendable {}
extension BulletType: @unchecked Sendable {}
extension LayoutTableRow: @unchecked Sendable {}
extension LayoutTableCell: @unchecked Sendable {}
extension VVPrimitiveVisibilityIndex: @unchecked Sendable {}
extension VVChatSceneArtifacts: @unchecked Sendable {}
extension VVMarkdownSelectionHelper: @unchecked Sendable {}
extension VVChatSelectionArtifacts: @unchecked Sendable {}

struct VVChatBackgroundPreparedMarkdown: @unchecked Sendable {
    let document: ParsedMarkdownDocument
    let layout: MarkdownLayout
    let appliedImageSizes: [String: CGSize]
    let sourceBlockIndexes: [Int]
}

struct VVChatMarkdownPreparationStyleSnapshot: Sendable {
    struct FontSnapshot: Sendable {
        let name: String
        let pointSize: CGFloat

        init(font: VVFont) {
            self.name = font.fontName
            self.pointSize = font.pointSize
        }

        func makeFont(scale: CGFloat) -> VVFont {
            let scaledSize = max(8, pointSize * scale)
            // For system fonts, always use the canonical systemFont method to ensure
            // consistent CTFont instances between background layout and main thread rendering
            #if canImport(AppKit)
            if isSystemFont() {
                return NSFont.systemFont(ofSize: scaledSize)
            }
            return NSFont(name: name, size: scaledSize) ?? .systemFont(ofSize: scaledSize)
            #else
            if isSystemFont() {
                return UIFont.systemFont(ofSize: scaledSize)
            }
            return UIFont(name: name, size: scaledSize) ?? .systemFont(ofSize: scaledSize)
            #endif
        }

        private func isSystemFont() -> Bool {
            return name.hasPrefix(".") || name == "SystemFont" || name == ".AppleSystemUIFont" || name == ".SFUI-Regular"
        }
    }

    let theme: MarkdownTheme
    let draftTheme: MarkdownTheme
    let baseFont: FontSnapshot
    let draftFont: FontSnapshot

    init(style: VVChatTimelineStyle) {
        self.theme = style.theme
        self.draftTheme = style.draftTheme
        self.baseFont = FontSnapshot(font: style.baseFont)
        self.draftFont = FontSnapshot(font: style.draftFont)
    }
}

struct VVChatMarkdownPreparationRequest: Sendable {
    let id: String
    let revision: Int
    let content: String
    let widthKey: Int
    let isDraft: Bool
    let contentScaleKey: Int
    let imageSizes: [String: CGSize]
}

struct VVChatMarkdownSceneRequest: Sendable {
    let layout: MarkdownLayout
    let blockRange: Range<Int>
    let widthKey: Int
    let isDraft: Bool
    let contentScaleKey: Int
    let textOpacityMultiplier: Float?
    let prefixGlyphColor: SIMD4<Float>?
    let prefixGlyphCount: Int
}

struct VVChatMarkdownSelectionRequest: Sendable {
    let layout: MarkdownLayout
    let blockRange: Range<Int>
    let widthKey: Int
    let isDraft: Bool
    let contentScaleKey: Int
}

actor VVChatMarkdownPreparationService {
    private struct ResourceKey: Hashable, Sendable {
        let widthKey: Int
        let isDraft: Bool
        let contentScaleKey: Int
    }

    private struct DraftPreparedKey: Hashable, Sendable {
        let id: String
        let widthKey: Int
        let contentScaleKey: Int
    }

    private struct DraftState {
        let key: DraftPreparedKey
        var revision: Int
        var content: String
        var stableContent: String
        var stableBlocks: [MarkdownBlock]
        var stableFootnotes: [String: MarkdownBlock]
        var prepared: VVChatBackgroundPreparedMarkdown
    }

    private let parser = MarkdownParser()
    private var styleSnapshot: VVChatMarkdownPreparationStyleSnapshot
    private var layoutEngines: [ResourceKey: MarkdownLayoutEngine] = [:]
    private var renderPipelines: [ResourceKey: VVMarkdownRenderPipeline] = [:]
    private var draftStates: [DraftPreparedKey: DraftState] = [:]

    init(styleSnapshot: VVChatMarkdownPreparationStyleSnapshot) {
        self.styleSnapshot = styleSnapshot
    }

    func updateStyleSnapshot(_ snapshot: VVChatMarkdownPreparationStyleSnapshot) {
        styleSnapshot = snapshot
        layoutEngines.removeAll(keepingCapacity: true)
        renderPipelines.removeAll(keepingCapacity: true)
        draftStates.removeAll(keepingCapacity: true)
    }

    func prepare(_ request: VVChatMarkdownPreparationRequest) -> VVChatBackgroundPreparedMarkdown {
        if request.isDraft {
            return prepareDraft(request)
        }
        return prepareFinal(request)
    }

    func prepareContentScene(_ request: VVChatMarkdownSceneRequest) -> VVChatSceneArtifacts {
        guard !request.blockRange.isEmpty else {
            return makeSceneArtifacts(VVScene())
        }
        let pipeline = pipeline(for: resourceKey(
            widthKey: request.widthKey,
            isDraft: request.isDraft,
            contentScaleKey: request.contentScaleKey
        ))
        let scene = applyScenePresentation(
            to: pipeline.buildScene(from: request.layout, blockRange: request.blockRange),
            textOpacityMultiplier: request.textOpacityMultiplier,
            prefixGlyphColor: request.prefixGlyphColor,
            prefixGlyphCount: request.prefixGlyphCount
        )
        return makeSceneArtifacts(scene)
    }

    func prepareSelectionArtifacts(_ request: VVChatMarkdownSelectionRequest) -> VVChatSelectionArtifacts? {
        guard !request.blockRange.isEmpty else { return nil }
        let key = resourceKey(
            widthKey: request.widthKey,
            isDraft: request.isDraft,
            contentScaleKey: request.contentScaleKey
        )
        let layoutEngine = layoutEngine(for: key)
        let selectionLayout: MarkdownLayout
        if request.blockRange.lowerBound == 0 && request.blockRange.upperBound == request.layout.blocks.count {
            selectionLayout = request.layout
        } else {
            selectionLayout = MarkdownLayout(
                blocks: Array(request.layout.blocks[request.blockRange]),
                totalHeight: request.layout.totalHeight,
                contentWidth: request.layout.contentWidth
            )
        }
        return VVChatSelectionArtifacts(
            helper: VVMarkdownSelectionHelper(layout: selectionLayout, layoutEngine: layoutEngine),
            blockRange: request.blockRange
        )
    }

    private func prepareFinal(_ request: VVChatMarkdownPreparationRequest) -> VVChatBackgroundPreparedMarkdown {
        let resourceKey = resourceKey(
            widthKey: request.widthKey,
            isDraft: request.isDraft,
            contentScaleKey: request.contentScaleKey
        )
        let layoutEngine = configuredLayoutEngine(for: resourceKey, imageSizes: request.imageSizes)
        let document = parser.parse(request.content)
        var layout = layoutEngine.layout(document)
        Self.applyKnownImageSizes(to: &layout, imageSizes: request.imageSizes, layoutEngine: layoutEngine)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)

        return VVChatBackgroundPreparedMarkdown(
            document: document,
            layout: layout,
            appliedImageSizes: Self.currentAppliedImageSizes(
                for: Self.collectImageURLs(from: layout),
                imageSizes: request.imageSizes
            ),
            sourceBlockIndexes: Self.sourceBlockIndexes(for: layout, document: document)
        )
    }

    private func prepareDraft(_ request: VVChatMarkdownPreparationRequest) -> VVChatBackgroundPreparedMarkdown {
        let resourceKey = resourceKey(
            widthKey: request.widthKey,
            isDraft: true,
            contentScaleKey: request.contentScaleKey
        )
        let layoutEngine = configuredLayoutEngine(for: resourceKey, imageSizes: request.imageSizes)
        let draftKey = DraftPreparedKey(
            id: request.id,
            widthKey: request.widthKey,
            contentScaleKey: request.contentScaleKey
        )

        if var cached = draftStates[draftKey] {
            let didUpdate = updateDraftState(
                &cached,
                content: request.content,
                revision: request.revision,
                imageSizes: request.imageSizes,
                layoutEngine: layoutEngine
            )
            let didRefresh = refreshPrepared(
                &cached.prepared,
                imageSizes: request.imageSizes,
                layoutEngine: layoutEngine
            )
            if didUpdate || didRefresh {
                draftStates[draftKey] = cached
            }
            return cached.prepared
        }

        let rebuilt = buildDraftState(
            key: draftKey,
            content: request.content,
            revision: request.revision,
            imageSizes: request.imageSizes,
            layoutEngine: layoutEngine
        )
        draftStates[draftKey] = rebuilt
        return rebuilt.prepared
    }

    private func buildDraftState(
        key: DraftPreparedKey,
        content: String,
        revision: Int,
        imageSizes: [String: CGSize],
        layoutEngine: MarkdownLayoutEngine
    ) -> DraftState {
        let boundary = parser.streamingBoundary(in: content)
        let stableDocument = parser.parse(boundary.stableContent, startingBlockIndex: 0)
        let trailingDocument = parser.parse(boundary.buffer, startingBlockIndex: stableDocument.blocks.count)
        let document = combineDraftDocuments(
            stableDocument: stableDocument,
            trailingDocument: trailingDocument,
            streamingBuffer: boundary.buffer
        )

        var layout = layoutEngine.layout(document)
        Self.applyKnownImageSizes(to: &layout, imageSizes: imageSizes, layoutEngine: layoutEngine)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)

        let prepared = VVChatBackgroundPreparedMarkdown(
            document: document,
            layout: layout,
            appliedImageSizes: Self.currentAppliedImageSizes(
                for: Self.collectImageURLs(from: layout),
                imageSizes: imageSizes
            ),
            sourceBlockIndexes: Self.sourceBlockIndexes(for: layout, document: document)
        )

        return DraftState(
            key: key,
            revision: revision,
            content: content,
            stableContent: boundary.stableContent,
            stableBlocks: stableDocument.blocks,
            stableFootnotes: stableDocument.footnotes,
            prepared: prepared
        )
    }

    private func updateDraftState(
        _ state: inout DraftState,
        content: String,
        revision: Int,
        imageSizes: [String: CGSize],
        layoutEngine: MarkdownLayoutEngine
    ) -> Bool {
        guard state.content != content || state.revision != revision else {
            return false
        }

        let previousPrepared = state.prepared
        guard content.hasPrefix(state.content) else {
            state = buildDraftState(
                key: state.key,
                content: content,
                revision: revision,
                imageSizes: imageSizes,
                layoutEngine: layoutEngine
            )
            return true
        }

        let boundary = parser.streamingBoundary(in: content)
        var stableBlocks = state.stableBlocks
        var stableFootnotes = state.stableFootnotes

        if boundary.stableContent != state.stableContent {
            guard boundary.stableContent.hasPrefix(state.stableContent) else {
                state = buildDraftState(
                    key: state.key,
                    content: content,
                    revision: revision,
                    imageSizes: imageSizes,
                    layoutEngine: layoutEngine
                )
                return true
            }

            let appendedStableSuffix = String(boundary.stableContent.dropFirst(state.stableContent.count))
            if !appendedStableSuffix.isEmpty {
                let appendedDocument = parser.parse(
                    appendedStableSuffix,
                    startingBlockIndex: stableBlocks.count
                )
                stableBlocks.append(contentsOf: appendedDocument.blocks)
                stableFootnotes.merge(appendedDocument.footnotes) { _, new in new }
            }
        }

        let trailingDocument: ParsedMarkdownDocument
        if boundary.buffer.isEmpty {
            trailingDocument = .empty
        } else {
            trailingDocument = parser.parse(boundary.buffer, startingBlockIndex: stableBlocks.count)
        }

        let document = combineDraftDocuments(
            stableDocument: ParsedMarkdownDocument(
                blocks: stableBlocks,
                footnotes: stableFootnotes,
                isComplete: true,
                streamingBuffer: ""
            ),
            trailingDocument: trailingDocument,
            streamingBuffer: boundary.buffer
        )

        let commonPrefixCount = commonPrefixBlockCount(
            lhs: previousPrepared.document.blocks,
            rhs: document.blocks
        )

        let nextLayout: MarkdownLayout
        if commonPrefixCount > 0 {
            let relayoutSourceIndex = max(0, commonPrefixCount - 1)
            nextLayout = layoutEngine.relayout(
                document,
                preservingPrefixFrom: previousPrepared.layout,
                previousSourceBlockIndexes: previousPrepared.sourceBlockIndexes,
                startingAtSourceIndex: relayoutSourceIndex
            )
        } else {
            nextLayout = layoutEngine.layout(document)
        }

        var adjustedLayout = nextLayout
        Self.applyKnownImageSizes(to: &adjustedLayout, imageSizes: imageSizes, layoutEngine: layoutEngine)
        layoutEngine.adjustParagraphImageSpacing(in: &adjustedLayout)

        state.revision = revision
        state.content = content
        state.stableContent = boundary.stableContent
        state.stableBlocks = stableBlocks
        state.stableFootnotes = stableFootnotes
        state.prepared = VVChatBackgroundPreparedMarkdown(
            document: document,
            layout: adjustedLayout,
            appliedImageSizes: Self.currentAppliedImageSizes(
                for: Self.collectImageURLs(from: adjustedLayout),
                imageSizes: imageSizes
            ),
            sourceBlockIndexes: Self.sourceBlockIndexes(for: adjustedLayout, document: document)
        )
        return true
    }

    private func refreshPrepared(
        _ prepared: inout VVChatBackgroundPreparedMarkdown,
        imageSizes: [String: CGSize],
        layoutEngine: MarkdownLayoutEngine
    ) -> Bool {
        let imageURLs = Self.collectImageURLs(from: prepared.layout)
        let nextAppliedImageSizes = Self.currentAppliedImageSizes(for: imageURLs, imageSizes: imageSizes)
        guard nextAppliedImageSizes != prepared.appliedImageSizes else {
            return false
        }

        var layout = prepared.layout
        Self.applyKnownImageSizes(to: &layout, imageSizes: imageSizes, layoutEngine: layoutEngine)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)
        prepared = VVChatBackgroundPreparedMarkdown(
            document: prepared.document,
            layout: layout,
            appliedImageSizes: nextAppliedImageSizes,
            sourceBlockIndexes: Self.sourceBlockIndexes(for: layout, document: prepared.document)
        )
        return true
    }

    private func resourceKey(
        widthKey: Int,
        isDraft: Bool,
        contentScaleKey: Int
    ) -> ResourceKey {
        ResourceKey(
            widthKey: widthKey,
            isDraft: isDraft,
            contentScaleKey: contentScaleKey
        )
    }

    private func configuredLayoutEngine(
        for key: ResourceKey,
        imageSizes: [String: CGSize]
    ) -> MarkdownLayoutEngine {
        let layoutEngine = layoutEngine(for: key)
        layoutEngine.updateContentWidth(max(1, CGFloat(key.widthKey) / 2))
        layoutEngine.updateImageSizeProvider { url in
            imageSizes[url]
        }
        return layoutEngine
    }

    private func layoutEngine(for key: ResourceKey) -> MarkdownLayoutEngine {
        if let cached = layoutEngines[key] {
            return cached
        }

        let scale = CGFloat(key.contentScaleKey) / 100
        let width = max(1, CGFloat(key.widthKey) / 2)
        let fontSnapshot = key.isDraft ? styleSnapshot.draftFont : styleSnapshot.baseFont
        let theme = key.isDraft ? styleSnapshot.draftTheme : styleSnapshot.theme
        let engine = MarkdownLayoutEngine(
            baseFont: fontSnapshot.makeFont(scale: scale),
            theme: theme,
            contentWidth: width
        )
        layoutEngines[key] = engine
        return engine
    }

    private func pipeline(for key: ResourceKey) -> VVMarkdownRenderPipeline {
        if let cached = renderPipelines[key] {
            return cached
        }
        let layoutEngine = layoutEngine(for: key)
        let theme = key.isDraft ? styleSnapshot.draftTheme : styleSnapshot.theme
        let pipeline = VVMarkdownRenderPipeline(theme: theme, layoutEngine: layoutEngine)
        renderPipelines[key] = pipeline
        return pipeline
    }

    private func makeSceneArtifacts(_ scene: VVScene) -> VVChatSceneArtifacts {
        let orderedPrimitiveIndices = scene.orderedPrimitiveIndices()
        return VVChatSceneArtifacts(
            scene: scene,
            orderedPrimitiveIndices: orderedPrimitiveIndices,
            visibilityIndex: VVPrimitiveVisibilityIndex(
                scene: scene,
                orderedPrimitiveIndices: orderedPrimitiveIndices,
                bucketHeight: 192
            )
        )
    }

    private func applyScenePresentation(
        to scene: VVScene,
        textOpacityMultiplier: Float?,
        prefixGlyphColor: SIMD4<Float>?,
        prefixGlyphCount: Int
    ) -> VVScene {
        var scene = scene
        if let textOpacityMultiplier {
            scene = applyingTextOpacity(to: scene, multiplier: textOpacityMultiplier)
        }
        if let prefixGlyphColor, prefixGlyphCount > 0, prefixGlyphColor.w > 0 {
            scene = applyingPrefixGlyphColor(
                to: scene,
                color: prefixGlyphColor,
                glyphCount: prefixGlyphCount
            )
        }
        return scene
    }

    private func applyingTextOpacity(
        to scene: VVScene,
        multiplier: Float
    ) -> VVScene {
        let alpha = max(0, multiplier)
        guard alpha != 1 else { return scene }

        var primitives: [VVPrimitive] = []
        primitives.reserveCapacity(scene.primitives.count)

        for primitive in scene.primitives {
            var updated = primitive
            if case .textRun(var run) = updated.kind {
                run.glyphs = run.glyphs.map { glyph in
                    VVTextGlyph(
                        glyphID: glyph.glyphID,
                        position: glyph.position,
                        size: glyph.size,
                        color: SIMD4<Float>(
                            glyph.color.x,
                            glyph.color.y,
                            glyph.color.z,
                            max(0, min(1, glyph.color.w * alpha))
                        ),
                        fontVariant: glyph.fontVariant,
                        fontSize: glyph.fontSize,
                        fontName: glyph.fontName,
                        fontDescriptorData: glyph.fontDescriptorData,
                        stringIndex: glyph.stringIndex
                    )
                }
                updated.kind = .textRun(run)
            }
            primitives.append(updated)
        }

        return VVScene(primitives: primitives)
    }

    private func applyingPrefixGlyphColor(
        to scene: VVScene,
        color: SIMD4<Float>,
        glyphCount: Int
    ) -> VVScene {
        guard glyphCount > 0 else { return scene }

        var remaining = glyphCount
        var primitives: [VVPrimitive] = []
        primitives.reserveCapacity(scene.primitives.count)

        for primitive in scene.primitives {
            var updated = primitive
            if remaining > 0, case .textRun(var run) = updated.kind {
                var glyphs = run.glyphs
                for index in glyphs.indices where remaining > 0 {
                    guard glyphs[index].color.w > 0 else { continue }
                    let glyph = glyphs[index]
                    glyphs[index] = VVTextGlyph(
                        glyphID: glyph.glyphID,
                        position: glyph.position,
                        size: glyph.size,
                        color: SIMD4<Float>(color.x, color.y, color.z, glyph.color.w),
                        fontVariant: glyph.fontVariant,
                        fontSize: glyph.fontSize,
                        fontName: glyph.fontName,
                        fontDescriptorData: glyph.fontDescriptorData,
                        stringIndex: glyph.stringIndex
                    )
                    remaining -= 1
                }
                run.glyphs = glyphs
                updated.kind = .textRun(run)
            }
            primitives.append(updated)
        }

        return VVScene(primitives: primitives)
    }

    private func combineDraftDocuments(
        stableDocument: ParsedMarkdownDocument,
        trailingDocument: ParsedMarkdownDocument,
        streamingBuffer: String
    ) -> ParsedMarkdownDocument {
        var footnotes = stableDocument.footnotes
        footnotes.merge(trailingDocument.footnotes) { _, new in new }
        return ParsedMarkdownDocument(
            blocks: stableDocument.blocks + trailingDocument.blocks,
            footnotes: footnotes,
            isComplete: false,
            streamingBuffer: streamingBuffer
        )
    }

    private func commonPrefixBlockCount(lhs: [MarkdownBlock], rhs: [MarkdownBlock]) -> Int {
        let count = min(lhs.count, rhs.count)
        var index = 0
        while index < count, lhs[index].id == rhs[index].id {
            index += 1
        }
        return index
    }

    private static func sourceBlockIndexes(
        for layout: MarkdownLayout,
        document: ParsedMarkdownDocument
    ) -> [Int] {
        let sourceIndexByBlockID = Dictionary(
            uniqueKeysWithValues: document.blocks.enumerated().map { ($0.element.id, $0.offset) }
        )
        return layout.blocks.map { block in
            sourceIndexByBlockID[block.blockId] ?? 0
        }
    }

    private static func applyKnownImageSizes(
        to layout: inout MarkdownLayout,
        imageSizes: [String: CGSize],
        layoutEngine: MarkdownLayoutEngine
    ) {
        guard !imageSizes.isEmpty else { return }

        for block in layout.blocks {
            switch block.content {
            case .image(let url, _, _):
                guard let size = imageSizes[url] else { continue }
                layoutEngine.updateImageLayout(in: &layout, blockId: block.blockId, imageSize: size)
            case .inline(let runs, let images) where runs.isEmpty && images.count == 1:
                let image = images[0]
                guard let size = imageSizes[image.url] else { continue }
                layoutEngine.updateImageLayout(in: &layout, blockId: block.blockId, imageSize: size)
            case .imageRow(let images):
                let hasKnownImage = images.contains { imageSizes[$0.url] != nil }
                guard hasKnownImage else { continue }
                layoutEngine.updateInlineImageRowLayout(in: &layout, blockId: block.blockId, imageSizes: imageSizes)
            default:
                continue
            }
        }
    }

    private static func currentAppliedImageSizes(
        for urls: Set<String>,
        imageSizes: [String: CGSize]
    ) -> [String: CGSize] {
        var applied: [String: CGSize] = [:]
        applied.reserveCapacity(urls.count)
        for url in urls {
            if let size = imageSizes[url] {
                applied[url] = size
            }
        }
        return applied
    }

    private static func collectImageURLs(from layout: MarkdownLayout) -> Set<String> {
        var urls = Set<String>()
        for block in layout.blocks {
            collectImageURLs(from: block, into: &urls)
        }
        return urls
    }

    private static func collectImageURLs(from block: LayoutBlock, into urls: inout Set<String>) {
        switch block.content {
        case .inline(_, let images):
            for image in images { urls.insert(image.url) }
        case .imageRow(let images):
            for image in images { urls.insert(image.url) }
        case .image(let url, _, _):
            urls.insert(url)
        case .listItems(let items):
            for item in items {
                collectImageURLs(from: item, into: &urls)
            }
        case .quoteBlocks(let blocks):
            for nested in blocks {
                collectImageURLs(from: nested, into: &urls)
            }
        case .tableRows(let rows):
            for row in rows {
                for cell in row.cells {
                    for image in cell.inlineImages {
                        urls.insert(image.url)
                    }
                }
            }
        case .definitionList(let items):
            for item in items {
                for image in item.termImages {
                    urls.insert(image.url)
                }
                for definitionImages in item.definitionImages {
                    for image in definitionImages {
                        urls.insert(image.url)
                    }
                }
            }
        case .abbreviationList(let items):
            for item in items {
                for image in item.images {
                    urls.insert(image.url)
                }
            }
        default:
            break
        }
    }

    private static func collectImageURLs(from item: LayoutListItem, into urls: inout Set<String>) {
        for image in item.inlineImages {
            urls.insert(image.url)
        }
        for child in item.children {
            collectImageURLs(from: child, into: &urls)
        }
    }
}
