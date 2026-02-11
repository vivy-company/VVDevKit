import Foundation
import VVMarkdown
import VVMetalPrimitives

public struct VVChatRenderedMessage {
    public let id: String
    public let revision: Int
    public let layout: MarkdownLayout
    public let scene: VVScene
    public let height: CGFloat
    public let contentOffset: CGPoint
    public let isDraft: Bool
    public let imageURLs: [String]
}

public final class VVChatMessageRenderer {
    private final class LRUCache<Key: Hashable, Value> {
        private var values: [Key: Value] = [:]
        private var order: [Key] = []
        private var limit: Int

        init(limit: Int) {
            self.limit = max(0, limit)
        }

        func updateLimit(_ limit: Int) {
            self.limit = max(0, limit)
            evictIfNeeded()
        }

        func value(for key: Key) -> Value? {
            guard let value = values[key] else { return nil }
            touch(key)
            return value
        }

        func set(_ value: Value, for key: Key) {
            if limit == 0 {
                values.removeAll(keepingCapacity: true)
                order.removeAll(keepingCapacity: true)
                return
            }
            values[key] = value
            touch(key)
            evictIfNeeded()
        }

        func remove(where predicate: (Key) -> Bool) {
            for key in order where predicate(key) {
                values.removeValue(forKey: key)
            }
            order.removeAll(where: predicate)
        }

        func removeAll() {
            values.removeAll(keepingCapacity: true)
            order.removeAll(keepingCapacity: true)
        }

        private func touch(_ key: Key) {
            if let index = order.firstIndex(of: key) {
                order.remove(at: index)
            }
            order.append(key)
        }

        private func evictIfNeeded() {
            guard limit > 0 else { return }
            while order.count > limit {
                let key = order.removeFirst()
                values.removeValue(forKey: key)
            }
        }
    }

    private struct CacheKey: Hashable {
        let id: String
        let revision: Int
        let widthKey: Int
        let isDraft: Bool
    }

    private let parser = MarkdownParser()
    private var finalLayoutEngine: MarkdownLayoutEngine
    private var draftLayoutEngine: MarkdownLayoutEngine
    private var finalPipeline: VVMarkdownRenderPipeline
    private var draftPipeline: VVMarkdownRenderPipeline
    private var assistantLayoutEngine: MarkdownLayoutEngine
    private var assistantDraftLayoutEngine: MarkdownLayoutEngine
    private var assistantPipeline: VVMarkdownRenderPipeline
    private var assistantDraftPipeline: VVMarkdownRenderPipeline
    private var headerLayoutEngine: MarkdownLayoutEngine
    private var timestampLayoutEngine: MarkdownLayoutEngine
    private var headerPipeline: VVMarkdownRenderPipeline
    private var timestampPipeline: VVMarkdownRenderPipeline
    private var loadingLayoutEngine: MarkdownLayoutEngine
    private var loadingPipeline: VVMarkdownRenderPipeline
    private var cache: LRUCache<CacheKey, VVChatRenderedMessage>
    private var contentWidth: CGFloat
    private var style: VVChatTimelineStyle
    private var imageSizes: [String: CGSize] = [:]
    private static let timeFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateStyle = .none
        formatter.timeStyle = .short
        return formatter
    }()

    public init(style: VVChatTimelineStyle, contentWidth: CGFloat) {
        self.style = style
        self.contentWidth = contentWidth
        self.finalLayoutEngine = MarkdownLayoutEngine(baseFont: style.baseFont, theme: style.theme, contentWidth: contentWidth)
        self.draftLayoutEngine = MarkdownLayoutEngine(baseFont: style.draftFont, theme: style.draftTheme, contentWidth: contentWidth)
        self.finalPipeline = VVMarkdownRenderPipeline(theme: style.theme, layoutEngine: finalLayoutEngine)
        self.draftPipeline = VVMarkdownRenderPipeline(theme: style.draftTheme, layoutEngine: draftLayoutEngine)
        let assistantTheme = Self.makeFlatTheme(from: style.theme)
        let assistantDraftTheme = Self.makeFlatTheme(from: style.draftTheme)
        self.assistantLayoutEngine = MarkdownLayoutEngine(baseFont: style.baseFont, theme: assistantTheme, contentWidth: contentWidth)
        self.assistantDraftLayoutEngine = MarkdownLayoutEngine(baseFont: style.draftFont, theme: assistantDraftTheme, contentWidth: contentWidth)
        self.assistantPipeline = VVMarkdownRenderPipeline(theme: assistantTheme, layoutEngine: assistantLayoutEngine)
        self.assistantDraftPipeline = VVMarkdownRenderPipeline(theme: assistantDraftTheme, layoutEngine: assistantDraftLayoutEngine)
        let headerTheme = Self.makeMetaTheme(base: style.theme, textColor: style.headerTextColor)
        let timestampTheme = Self.makeMetaTheme(base: style.theme, textColor: style.timestampTextColor)
        let loadingTheme = Self.makeMetaTheme(base: style.theme, textColor: style.loadingIndicatorTextColor)
        self.headerLayoutEngine = MarkdownLayoutEngine(baseFont: style.headerFont, theme: headerTheme, contentWidth: contentWidth)
        self.timestampLayoutEngine = MarkdownLayoutEngine(baseFont: style.timestampFont, theme: timestampTheme, contentWidth: contentWidth)
        self.headerPipeline = VVMarkdownRenderPipeline(theme: headerTheme, layoutEngine: headerLayoutEngine)
        self.timestampPipeline = VVMarkdownRenderPipeline(theme: timestampTheme, layoutEngine: timestampLayoutEngine)
        self.loadingLayoutEngine = MarkdownLayoutEngine(baseFont: style.loadingIndicatorFont, theme: loadingTheme, contentWidth: contentWidth)
        self.loadingPipeline = VVMarkdownRenderPipeline(theme: loadingTheme, layoutEngine: loadingLayoutEngine)
        self.cache = LRUCache(limit: style.renderedCacheLimit)
    }

    public func updateStyle(_ style: VVChatTimelineStyle) {
        self.style = style
        finalLayoutEngine = MarkdownLayoutEngine(baseFont: style.baseFont, theme: style.theme, contentWidth: contentWidth)
        draftLayoutEngine = MarkdownLayoutEngine(baseFont: style.draftFont, theme: style.draftTheme, contentWidth: contentWidth)
        finalPipeline = VVMarkdownRenderPipeline(theme: style.theme, layoutEngine: finalLayoutEngine)
        draftPipeline = VVMarkdownRenderPipeline(theme: style.draftTheme, layoutEngine: draftLayoutEngine)
        let assistantTheme = Self.makeFlatTheme(from: style.theme)
        let assistantDraftTheme = Self.makeFlatTheme(from: style.draftTheme)
        assistantLayoutEngine = MarkdownLayoutEngine(baseFont: style.baseFont, theme: assistantTheme, contentWidth: contentWidth)
        assistantDraftLayoutEngine = MarkdownLayoutEngine(baseFont: style.draftFont, theme: assistantDraftTheme, contentWidth: contentWidth)
        assistantPipeline = VVMarkdownRenderPipeline(theme: assistantTheme, layoutEngine: assistantLayoutEngine)
        assistantDraftPipeline = VVMarkdownRenderPipeline(theme: assistantDraftTheme, layoutEngine: assistantDraftLayoutEngine)
        let headerTheme = Self.makeMetaTheme(base: style.theme, textColor: style.headerTextColor)
        let timestampTheme = Self.makeMetaTheme(base: style.theme, textColor: style.timestampTextColor)
        let loadingTheme = Self.makeMetaTheme(base: style.theme, textColor: style.loadingIndicatorTextColor)
        headerLayoutEngine = MarkdownLayoutEngine(baseFont: style.headerFont, theme: headerTheme, contentWidth: contentWidth)
        timestampLayoutEngine = MarkdownLayoutEngine(baseFont: style.timestampFont, theme: timestampTheme, contentWidth: contentWidth)
        headerPipeline = VVMarkdownRenderPipeline(theme: headerTheme, layoutEngine: headerLayoutEngine)
        timestampPipeline = VVMarkdownRenderPipeline(theme: timestampTheme, layoutEngine: timestampLayoutEngine)
        loadingLayoutEngine = MarkdownLayoutEngine(baseFont: style.loadingIndicatorFont, theme: loadingTheme, contentWidth: contentWidth)
        loadingPipeline = VVMarkdownRenderPipeline(theme: loadingTheme, layoutEngine: loadingLayoutEngine)
        cache.updateLimit(style.renderedCacheLimit)
        cache.removeAll()
    }

    public func updateContentWidth(_ width: CGFloat) {
        let widthKey = Self.widthKey(for: width)
        if widthKey == Self.widthKey(for: contentWidth) {
            return
        }
        contentWidth = width
        finalLayoutEngine.updateContentWidth(width)
        draftLayoutEngine.updateContentWidth(width)
        assistantLayoutEngine.updateContentWidth(width)
        assistantDraftLayoutEngine.updateContentWidth(width)
        headerLayoutEngine.updateContentWidth(width)
        timestampLayoutEngine.updateContentWidth(width)
        loadingLayoutEngine.updateContentWidth(width)
        cache.removeAll()
    }

    public func updateImageSize(url: String, size: CGSize) -> Bool {
        if imageSizes[url] == size {
            return false
        }
        imageSizes[url] = size
        return true
    }

    public func invalidate(messageID: String) {
        cache.remove(where: { $0.id == messageID })
    }

    public func renderedMessage(for message: VVChatMessage) -> VVChatRenderedMessage {
        let insets = style.insets(for: message.role)
        let usesBubble = message.role == .user
        let bubbleInsets = usesBubble ? style.userBubbleInsets : VVInsets()
        let availableWidth = max(0, contentWidth - insets.left - insets.right)
        let maxContentWidth = usesBubble ? min(availableWidth - bubbleInsets.left - bubbleInsets.right, style.userBubbleMaxWidth) : availableWidth
        let messageContentWidth = max(0, maxContentWidth)
        let widthKey = Self.widthKey(for: messageContentWidth)
        let isDraft = message.state == .draft
        let key = CacheKey(id: message.id, revision: message.revision, widthKey: widthKey, isDraft: isDraft)
        if let cached = cache.value(for: key) {
            return cached
        }

        let document = isDraft ? makeStreamingDocument(text: message.content) : parser.parse(message.content)
        let usesFlatTheme = message.role != .user
        let layoutEngine: MarkdownLayoutEngine
        let pipeline: VVMarkdownRenderPipeline
        if isDraft {
            layoutEngine = usesFlatTheme ? assistantDraftLayoutEngine : draftLayoutEngine
            pipeline = usesFlatTheme ? assistantDraftPipeline : draftPipeline
        } else {
            layoutEngine = usesFlatTheme ? assistantLayoutEngine : finalLayoutEngine
            pipeline = usesFlatTheme ? assistantPipeline : finalPipeline
        }

        layoutEngine.updateImageSizeProvider { [weak self] url in
            self?.imageSizes[url]
        }
        layoutEngine.updateContentWidth(messageContentWidth)
        var layout = layoutEngine.layout(document)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)

        let contentScene = pipeline.buildScene(from: layout)
        let imageURLs = Array(collectImageURLs(from: layout))
        let sceneBounds = sceneBounds(for: contentScene, layoutEngine: layoutEngine)
        let contentMinX = sceneBounds?.minX ?? 0
        let contentMinY = sceneBounds?.minY ?? 0
        let contentWidth = sceneBounds.map { max(1, $0.width) }
        let contentHeight = sceneBounds.map { max(1, $0.height) } ?? layoutHeight(for: layout)
        let bubbleContentWidth = usesBubble ? max(1, min(messageContentWidth, contentWidth ?? messageContentWidth)) : messageContentWidth
        let metaWidth = usesBubble ? max(bubbleContentWidth, 1) : messageContentWidth
        let headerText = headerTitle(for: message.role)
        let headerRender = renderMeta(text: headerText, layoutEngine: headerLayoutEngine, pipeline: headerPipeline, width: metaWidth)
        let footerRender: (layout: MarkdownLayout, scene: VVScene)
        if isDraft && message.role == .assistant {
            footerRender = renderMeta(text: style.loadingIndicatorText, layoutEngine: loadingLayoutEngine, pipeline: loadingPipeline, width: metaWidth)
        } else {
            footerRender = renderMeta(text: timestampLabel(for: message), layoutEngine: timestampLayoutEngine, pipeline: timestampPipeline, width: metaWidth)
        }

        let headerHeight = layoutHeight(for: headerRender.layout)
        let footerHeight = layoutHeight(for: footerRender.layout)
        let headerBlockHeight = headerHeight > 0 ? headerHeight + style.headerSpacing : 0
        let footerBlockHeight = footerHeight > 0 ? style.footerSpacing + footerHeight : 0
        let contentBlockHeight = usesBubble
            ? (bubbleInsets.top + contentHeight + bubbleInsets.bottom)
            : contentHeight
        let bubbleWidth = usesBubble ? (bubbleContentWidth + bubbleInsets.left + bubbleInsets.right) : 0
        let messageHeight = headerBlockHeight + contentBlockHeight + footerBlockHeight

        var builder = VVSceneBuilder()
        var currentY: CGFloat = 0
        if headerHeight > 0 {
            builder.add(node: VVNode.fromScene(headerRender.scene))
            currentY += headerHeight + style.headerSpacing
        }

        if usesBubble {
            let bubbleFrame = CGRect(x: 0, y: currentY, width: bubbleWidth, height: contentBlockHeight)
            if style.userBubbleBorderWidth > 0, style.userBubbleBorderColor.w > 0 {
                let borderFrame = bubbleFrame.insetBy(dx: -style.userBubbleBorderWidth, dy: -style.userBubbleBorderWidth)
                let border = VVQuadPrimitive(
                    frame: borderFrame,
                    color: style.userBubbleBorderColor,
                    cornerRadius: style.userBubbleCornerRadius + style.userBubbleBorderWidth
                )
                builder.add(kind: .quad(border), zIndex: -2)
            }
            let bubble = VVQuadPrimitive(
                frame: bubbleFrame,
                color: style.userBubbleColor,
                cornerRadius: style.userBubbleCornerRadius
            )
            builder.add(kind: .quad(bubble), zIndex: -1)
            let contentOffsetX = bubbleInsets.left - contentMinX
            let contentOffsetY = currentY + bubbleInsets.top - contentMinY
            builder.withOffset(CGPoint(x: contentOffsetX, y: contentOffsetY)) { builder in
                builder.add(node: VVNode.fromScene(contentScene))
            }
        } else {
            let contentOffsetY = currentY - contentMinY
            builder.withOffset(CGPoint(x: 0, y: contentOffsetY)) { builder in
                builder.add(node: VVNode.fromScene(contentScene))
            }
        }

        currentY += contentBlockHeight
        if footerHeight > 0 {
            currentY += style.footerSpacing
            builder.withOffset(CGPoint(x: 0, y: currentY)) { builder in
                builder.add(node: VVNode.fromScene(footerRender.scene))
            }
        }

        let scene = builder.scene
        let height = messageHeight + insets.top + insets.bottom
        let bubbleOffsetX = usesBubble ? max(0, availableWidth - bubbleWidth) : 0
        let rendered = VVChatRenderedMessage(
            id: message.id,
            revision: message.revision,
            layout: layout,
            scene: scene,
            height: height,
            contentOffset: CGPoint(x: insets.left + bubbleOffsetX, y: insets.top),
            isDraft: isDraft,
            imageURLs: imageURLs
        )
        cache.set(rendered, for: key)
        return rendered
    }

    private func makeDraftDocument(text: String) -> ParsedMarkdownDocument {
        let content = MarkdownInlineContent(text: text)
        let block = MarkdownBlock(.paragraph(content), index: 0)
        return ParsedMarkdownDocument(blocks: [block], footnotes: [:], isComplete: false, streamingBuffer: text)
    }

    private func makeStreamingDocument(text: String) -> ParsedMarkdownDocument {
        let parsed = parser.parseStreaming(text, isComplete: false)
        guard !parsed.streamingBuffer.isEmpty else { return parsed }

        var blocks = parsed.blocks
        let bufferContent = MarkdownInlineContent(text: parsed.streamingBuffer)
        blocks.append(MarkdownBlock(.paragraph(bufferContent), index: blocks.count))
        return ParsedMarkdownDocument(
            blocks: blocks,
            footnotes: parsed.footnotes,
            isComplete: false,
            streamingBuffer: parsed.streamingBuffer
        )
    }

    private func renderMeta(
        text: String,
        layoutEngine: MarkdownLayoutEngine,
        pipeline: VVMarkdownRenderPipeline,
        width: CGFloat
    ) -> (layout: MarkdownLayout, scene: VVScene) {
        layoutEngine.updateContentWidth(width)
        let document = makeMetaDocument(text: text)
        var layout = layoutEngine.layout(document)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)
        let scene = pipeline.buildScene(from: layout)
        return (layout, scene)
    }

    private func makeMetaDocument(text: String) -> ParsedMarkdownDocument {
        let content = MarkdownInlineContent(text: text)
        let block = MarkdownBlock(.paragraph(content), index: 0)
        return ParsedMarkdownDocument(blocks: [block], footnotes: [:], isComplete: true, streamingBuffer: "")
    }

    private func headerTitle(for role: VVChatMessageRole) -> String {
        switch role {
        case .user:
            return "User"
        case .assistant:
            return "Agent"
        case .system:
            return "System"
        }
    }

    private func timestampLabel(for message: VVChatMessage) -> String {
        let timestamp = message.timestamp ?? Date()
        return Self.timeFormatter.string(from: timestamp)
    }

    private static func makeMetaTheme(base: MarkdownTheme, textColor: SIMD4<Float>) -> MarkdownTheme {
        var theme = base
        theme.textColor = textColor
        theme.headingColor = textColor
        theme.linkColor = textColor
        theme.codeColor = textColor
        theme.blockQuoteColor = textColor
        theme.listBulletColor = textColor
        theme.checkboxCheckedColor = textColor
        theme.checkboxUncheckedColor = textColor
        theme.thematicBreakColor = textColor
        theme.tableBorderColor = textColor
        theme.diagramTextColor = textColor
        theme.mathColor = textColor
        theme.strikethroughColor = textColor
        theme.contentPadding = 0
        theme.paragraphSpacing = 2
        return theme
    }

    private static func makeFlatTheme(from base: MarkdownTheme) -> MarkdownTheme {
        var theme = base
        theme.contentPadding = 0
        theme.paragraphSpacing = max(4, theme.paragraphSpacing * 0.6)
        theme.headingSpacing = max(4, theme.headingSpacing * 0.5)
        theme.listIndent = 0
        theme.blockQuoteIndent = 0
        theme.blockQuoteBorderWidth = 0
        theme.codeBlockPadding = 0
        theme.codeBlockHeaderHeight = 0
        theme.codeHeaderDividerHeight = 0
        theme.codeGutterDividerWidth = 0
        theme.codeCopyButtonCornerRadius = 0
        theme.tableRowPadding = 2
        theme.tableCellPadding = 4
        theme.codeBackgroundColor = withAlpha(theme.codeBackgroundColor, 0)
        theme.codeHeaderBackgroundColor = withAlpha(theme.codeHeaderBackgroundColor, 0)
        theme.codeHeaderTextColor = withAlpha(theme.codeHeaderTextColor, 0)
        theme.codeCopyButtonBackground = withAlpha(theme.codeCopyButtonBackground, 0)
        theme.codeCopyButtonTextColor = withAlpha(theme.codeCopyButtonTextColor, 0)
        theme.codeBorderColor = withAlpha(theme.codeBorderColor, 0)
        theme.codeGutterBackgroundColor = withAlpha(theme.codeGutterBackgroundColor, 0)
        theme.codeBorderWidth = 0
        theme.codeBlockCornerRadius = 0
        theme.blockQuoteBorderColor = withAlpha(theme.blockQuoteBorderColor, 0)
        theme.tableHeaderBackground = withAlpha(theme.tableHeaderBackground, 0)
        theme.tableBackground = withAlpha(theme.tableBackground, 0)
        theme.tableBorderColor = withAlpha(theme.tableBorderColor, 0)
        theme.tableCornerRadius = 0
        theme.diagramBackground = withAlpha(theme.diagramBackground, 0)
        theme.diagramNodeBackground = withAlpha(theme.diagramNodeBackground, 0)
        theme.diagramNodeBorder = withAlpha(theme.diagramNodeBorder, 0)
        theme.diagramNoteBackground = withAlpha(theme.diagramNoteBackground, 0)
        theme.diagramNoteBorder = withAlpha(theme.diagramNoteBorder, 0)
        theme.diagramGroupBackground = withAlpha(theme.diagramGroupBackground, 0)
        theme.diagramGroupBorder = withAlpha(theme.diagramGroupBorder, 0)
        theme.diagramActivationColor = withAlpha(theme.diagramActivationColor, 0)
        theme.diagramActivationBorder = withAlpha(theme.diagramActivationBorder, 0)
        return theme
    }

    private static func withAlpha(_ color: SIMD4<Float>, _ alpha: Float) -> SIMD4<Float> {
        SIMD4(color.x, color.y, color.z, alpha)
    }

    private func layoutHeight(for layout: MarkdownLayout) -> CGFloat {
        guard let last = layout.blocks.last else { return 0 }
        return last.frame.maxY
    }

    private func sceneBounds(for scene: VVScene, layoutEngine: MarkdownLayoutEngine) -> CGRect? {
        var minX = CGFloat.greatestFiniteMagnitude
        var minY = CGFloat.greatestFiniteMagnitude
        var maxX = CGFloat.leastNormalMagnitude
        var maxY = CGFloat.leastNormalMagnitude
        var hasValue = false

        let baseSize = max(1, layoutEngine.baseFontSize)
        let ascent = layoutEngine.currentAscent
        let descent = layoutEngine.currentDescent

        func updateBounds(minX newMinX: CGFloat, minY newMinY: CGFloat, maxX newMaxX: CGFloat, maxY newMaxY: CGFloat) {
            minX = min(minX, newMinX)
            minY = min(minY, newMinY)
            maxX = max(maxX, newMaxX)
            maxY = max(maxY, newMaxY)
            hasValue = true
        }

        func updateBounds(_ rect: CGRect) {
            updateBounds(minX: rect.minX, minY: rect.minY, maxX: rect.maxX, maxY: rect.maxY)
        }

        func updateGlyphs(_ glyphs: [VVTextGlyph], fontSize: CGFloat) {
            guard !glyphs.isEmpty else { return }
            let scale = max(0.5, fontSize / baseSize)
            let glyphAscent = ascent * scale
            let glyphDescent = descent * scale
            for glyph in glyphs where glyph.color.w > 0 {
                updateBounds(
                    minX: glyph.position.x,
                    minY: glyph.position.y - glyphAscent,
                    maxX: glyph.position.x + glyph.size.width,
                    maxY: glyph.position.y + glyphDescent
                )
            }
        }

        for primitive in scene.primitives {
            switch primitive.kind {
            case .textRun(let run):
                updateGlyphs(run.glyphs, fontSize: run.fontSize)

            case .quad(let quad):
                guard quad.color.w > 0 else { continue }
                updateBounds(quad.frame)

            case .line(let line):
                guard line.color.w > 0 else { continue }
                let minX = min(line.start.x, line.end.x)
                let minY = min(line.start.y, line.end.y)
                let width = abs(line.end.x - line.start.x)
                let height = abs(line.end.y - line.start.y)
                let rectWidth = width > 0 ? width : line.thickness
                let rectHeight = height > 0 ? height : line.thickness
                updateBounds(CGRect(x: minX, y: minY, width: rectWidth, height: rectHeight))

            case .bullet(let bullet):
                guard bullet.color.w > 0 else { continue }
                updateBounds(CGRect(x: bullet.position.x, y: bullet.position.y, width: bullet.size, height: bullet.size))

            case .image(let image):
                updateBounds(image.frame)

            case .blockQuoteBorder(let border):
                guard border.color.w > 0 else { continue }
                updateBounds(border.frame)

            case .tableLine(let line):
                guard line.color.w > 0 else { continue }
                let minX = min(line.start.x, line.end.x)
                let minY = min(line.start.y, line.end.y)
                let width = abs(line.end.x - line.start.x)
                let height = abs(line.end.y - line.start.y)
                let rectWidth = width > 0 ? width : line.lineWidth
                let rectHeight = height > 0 ? height : line.lineWidth
                updateBounds(CGRect(x: minX, y: minY, width: rectWidth, height: rectHeight))

            case .pieSlice(let slice):
                guard slice.color.w > 0 else { continue }
                let rect = CGRect(
                    x: slice.center.x - slice.radius,
                    y: slice.center.y - slice.radius,
                    width: slice.radius * 2,
                    height: slice.radius * 2
                )
                updateBounds(rect)
            }
        }

        guard hasValue else { return nil }
        return CGRect(x: minX, y: minY, width: max(1, maxX - minX), height: max(1, maxY - minY))
    }

    private func collectImageURLs(from layout: MarkdownLayout) -> Set<String> {
        var urls = Set<String>()
        for block in layout.blocks {
            collectImageURLs(from: block, into: &urls)
        }
        return urls
    }

    private func collectImageURLs(from block: LayoutBlock, into urls: inout Set<String>) {
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

    private func collectImageURLs(from item: LayoutListItem, into urls: inout Set<String>) {
        for image in item.inlineImages {
            urls.insert(image.url)
        }
        for child in item.children {
            collectImageURLs(from: child, into: &urls)
        }
    }

    private static func widthKey(for width: CGFloat) -> Int {
        Int((width * 2).rounded(.down))
    }
}
