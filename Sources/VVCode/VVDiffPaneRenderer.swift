import AppKit
import CoreGraphics
import CoreText
import Foundation
import Metal
import VVMarkdown
import VVMetalPrimitives

private typealias MDLayoutGlyph = VVMarkdown.LayoutGlyph

private extension VVFontVariant {
    var diffCacheKey: UInt8 {
        switch self {
        case .regular:
            return 0
        case .semibold:
            return 1
        case .semiboldItalic:
            return 2
        case .bold:
            return 3
        case .italic:
            return 4
        case .boldItalic:
            return 5
        case .monospace:
            return 6
        case .emoji:
            return 7
        }
    }
}

struct VVDiffTextPass {
    let clipRect: CGRect?
    let glyphBatches: [Int: [VVTextGlyphInstance]]
    let colorGlyphBatches: [Int: [VVTextGlyphInstance]]

    var drawCallCount: Int {
        glyphBatches.count + colorGlyphBatches.count
    }
}

struct VVDiffPathBatch {
    let clipRect: CGRect?
    let vertices: [PathRenderVertex]
    let fillVertexCount: Int
    let fillColor: SIMD4<Float>?
    let strokeVertexCount: Int
    let strokeColor: SIMD4<Float>?
}

struct VVDiffRenderArtifacts {
    let quads: [QuadInstance]
    let roundedQuads: [QuadInstance]
    let paths: [VVDiffPathBatch]
    let textPasses: [VVDiffTextPass]
    let contentHeight: CGFloat

    var drawCallCount: Int {
        let quadDraws = (quads.isEmpty ? 0 : 1) + (roundedQuads.isEmpty ? 0 : 1)
        let pathDraws = paths.reduce(into: 0) { partialResult, batch in
            if batch.fillColor != nil && batch.fillVertexCount > 0 {
                partialResult += 1
            }
            if batch.strokeColor != nil && batch.strokeVertexCount > 0 {
                partialResult += 1
            }
        }
        let textDraws = textPasses.reduce(0) { $0 + $1.drawCallCount }
        return quadDraws + pathDraws + textDraws
    }
}

enum VVDiffPaneRenderer {
    static func buildArtifacts(
        layout: VVDiffLayoutPlan,
        blockRange: Range<Int>,
        theme: VVTheme,
        baseFont: NSFont,
        options: VVDiffRenderOptions,
        highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]],
        metalRenderer: VVTextMetalRenderer
    ) -> VVDiffRenderArtifacts {
        let builder = DiffPacketBuilder(
            font: baseFont,
            theme: diffMetalTheme(from: theme),
            contentWidth: layout.width,
            options: options,
            highlightedRanges: highlightedRanges,
            metalRenderer: metalRenderer
        )
        return builder.build(layout: layout, blockRange: blockRange)
    }

    static func render(
        _ artifacts: VVDiffRenderArtifacts,
        encoder: MTLRenderCommandEncoder,
        renderer: VVTextMetalRenderer,
        scissorRectForClip: (CGRect) -> MTLScissorRect,
        fullScissorRect: () -> MTLScissorRect
    ) {
        if !artifacts.quads.isEmpty, let buffer = renderer.makeBuffer(for: artifacts.quads) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: artifacts.quads.count, rounded: false)
        }

        if !artifacts.roundedQuads.isEmpty, let buffer = renderer.makeBuffer(for: artifacts.roundedQuads) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: artifacts.roundedQuads.count, rounded: true)
        }

        for path in artifacts.paths {
            if let clipRect = path.clipRect {
                encoder.setScissorRect(scissorRectForClip(clipRect))
            } else {
                encoder.setScissorRect(fullScissorRect())
            }
            guard let buffer = renderer.makeBuffer(for: path.vertices) else { continue }
            if let fillColor = path.fillColor, path.fillVertexCount > 0 {
                renderer.renderPath(
                    encoder: encoder,
                    vertices: buffer,
                    vertexStart: 0,
                    vertexCount: path.fillVertexCount,
                    color: fillColor
                )
            }
            if let strokeColor = path.strokeColor, path.strokeVertexCount > 0 {
                renderer.renderPath(
                    encoder: encoder,
                    vertices: buffer,
                    vertexStart: path.fillVertexCount,
                    vertexCount: path.strokeVertexCount,
                    color: strokeColor
                )
            }
        }

        for pass in artifacts.textPasses {
            if let clipRect = pass.clipRect {
                encoder.setScissorRect(scissorRectForClip(clipRect))
            } else {
                encoder.setScissorRect(fullScissorRect())
            }
            renderGlyphBatches(pass.glyphBatches, encoder: encoder, renderer: renderer, isColor: false)
            renderGlyphBatches(pass.colorGlyphBatches, encoder: encoder, renderer: renderer, isColor: true)
        }

        encoder.setScissorRect(fullScissorRect())
    }

    private static func renderGlyphBatches(
        _ batches: [Int: [VVTextGlyphInstance]],
        encoder: MTLRenderCommandEncoder,
        renderer: VVTextMetalRenderer,
        isColor: Bool
    ) {
        guard !batches.isEmpty else { return }
        let textures = isColor ? renderer.glyphAtlas.allColorAtlasTextures : renderer.glyphAtlas.allAtlasTextures
        for atlasIndex in batches.keys.sorted() {
            guard atlasIndex >= 0, atlasIndex < textures.count else { continue }
            guard let instances = batches[atlasIndex], !instances.isEmpty else { continue }
            guard let buffer = renderer.makeBuffer(for: instances) else { continue }
            if isColor {
                renderer.renderColorGlyphs(
                    encoder: encoder,
                    instances: buffer,
                    instanceCount: instances.count,
                    texture: textures[atlasIndex]
                )
            } else {
                renderer.renderGlyphs(
                    encoder: encoder,
                    instances: buffer,
                    instanceCount: instances.count,
                    texture: textures[atlasIndex]
                )
            }
        }
    }
}

private final class DiffPacketBuilder {
    private typealias BaseGlyphLookupKey = UInt64

    private struct EmptyPaneHatchCacheKey: Hashable {
        let widthKey: Int
        let heightKey: Int
        let phaseKey: Int
        let thicknessKey: Int
        let spacingKey: Int
    }

    private struct LineNumberGlyphCacheKey: Hashable {
        let text: String
        let color: SIMD4<Float>
    }

    private struct WrappedTextSegment: Hashable {
        let text: String
        let start: Int
        let length: Int

        var end: Int {
            start + length
        }
    }

    private struct TextPassAccumulator {
        let clipRect: CGRect?
        var glyphBatches: [Int: [VVTextGlyphInstance]] = [:]
        var colorGlyphBatches: [Int: [VVTextGlyphInstance]] = [:]

        init(clipRect: CGRect?) {
            self.clipRect = clipRect
        }

        var isEmpty: Bool {
            glyphBatches.isEmpty && colorGlyphBatches.isEmpty
        }

        func makePass() -> VVDiffTextPass {
            VVDiffTextPass(
                clipRect: clipRect,
                glyphBatches: glyphBatches,
                colorGlyphBatches: colorGlyphBatches
            )
        }
    }

    private struct PathAccumulator {
        var vertices: [PathRenderVertex] = []
        var fillVertexCount: Int = 0
        let fillColor: SIMD4<Float>
        let clipRect: CGRect?

        init(fillColor: SIMD4<Float>, clipRect: CGRect? = nil) {
            self.fillColor = fillColor
            self.clipRect = clipRect
        }

        mutating func append(fillVertices newVertices: [PathRenderVertex]) {
            vertices.append(contentsOf: newVertices)
            fillVertexCount += newVertices.count
        }

        func makeBatch() -> VVDiffPathBatch? {
            guard !vertices.isEmpty else { return nil }
            return VVDiffPathBatch(
                clipRect: clipRect,
                vertices: vertices,
                fillVertexCount: fillVertexCount,
                fillColor: fillColor,
                strokeVertexCount: 0,
                strokeColor: nil
            )
        }
    }

    private struct CollectedSplit {
        let splitRow: VVDiffSplitRow
        let y: CGFloat
        let height: CGFloat
        let leftWrappedLines: [WrappedTextSegment]
        let rightWrappedLines: [WrappedTextSegment]
    }

    private let font: NSFont
    private let lineHeight: CGFloat
    private let layoutEngine: MarkdownLayoutEngine
    private let codeInsetX: CGFloat = 10
    private let options: VVDiffRenderOptions
    private let highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]]
    private let metalRenderer: VVTextMetalRenderer

    private static let emptyPaneHatchCacheLock = NSLock()
    private static var emptyPaneHatchCache: [EmptyPaneHatchCacheKey: [PathRenderVertex]] = [:]

    private var lineNumberGlyphCache: [LineNumberGlyphCacheKey: [MDLayoutGlyph]] = [:]
    private var baseGlyphLookupCache: [BaseGlyphLookupKey: VVTextCachedGlyph] = [:]

    private let textColor: SIMD4<Float>
    private let backgroundColor: SIMD4<Float>
    private let gutterTextColor: SIMD4<Float>
    private let headerBgColor: SIMD4<Float>
    private let metadataBgColor: SIMD4<Float>
    private let hunkBgColor: SIMD4<Float>
    private let addedBgColor: SIMD4<Float>
    private let deletedBgColor: SIMD4<Float>
    private let emptyPaneBgColor: SIMD4<Float>
    private let emptyPaneGuideColor: SIMD4<Float>
    private let addedMarkerColor: SIMD4<Float>
    private let deletedMarkerColor: SIMD4<Float>
    private let modifiedColor: SIMD4<Float>

    init(
        font: NSFont,
        theme: MarkdownTheme,
        contentWidth: CGFloat,
        options: VVDiffRenderOptions,
        highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]],
        metalRenderer: VVTextMetalRenderer
    ) {
        self.font = font
        self.options = options
        self.highlightedRanges = highlightedRanges
        self.metalRenderer = metalRenderer

        let monoFont = NSFont.monospacedSystemFont(ofSize: font.pointSize, weight: .regular)
        var rendererTheme = theme
        rendererTheme.contentPadding = 0
        rendererTheme.paragraphSpacing = 0
        self.layoutEngine = MarkdownLayoutEngine(
            baseFont: monoFont,
            monoFont: monoFont,
            theme: rendererTheme,
            contentWidth: contentWidth
        )
        self.lineHeight = ceil(monoFont.pointSize * 1.6)

        let isLight = brightness(of: theme.codeBackgroundColor) > 0.58
        self.textColor = theme.codeColor
        self.backgroundColor = theme.codeBackgroundColor
        self.gutterTextColor = theme.codeGutterTextColor
        self.headerBgColor = theme.codeHeaderBackgroundColor
        self.metadataBgColor = withAlpha(theme.codeHeaderBackgroundColor, 0.58)
        self.hunkBgColor = isLight
            ? SIMD4<Float>(0.90, 0.94, 0.99, 1.0)
            : SIMD4<Float>(0.18, 0.24, 0.33, 0.96)
        self.addedBgColor = isLight
            ? SIMD4<Float>(0.86, 0.96, 0.88, 1.0)
            : SIMD4<Float>(0.07, 0.24, 0.13, 0.92)
        self.deletedBgColor = isLight
            ? SIMD4<Float>(0.98, 0.90, 0.90, 1.0)
            : SIMD4<Float>(0.27, 0.12, 0.13, 0.92)
        let emptyPaneTint = isLight
            ? blended(theme.codeBackgroundColor, theme.codeGutterTextColor, 0.18)
            : blended(theme.codeBackgroundColor, theme.codeGutterTextColor, 0.24)
        self.emptyPaneBgColor = isLight
            ? blended(theme.codeBackgroundColor, emptyPaneTint, 0.16)
            : blended(theme.codeBackgroundColor, emptyPaneTint, 0.18)
        self.emptyPaneGuideColor = isLight
            ? withAlpha(blended(theme.codeBackgroundColor, emptyPaneTint, 0.30), 0.20)
            : withAlpha(blended(theme.codeBackgroundColor, emptyPaneTint, 0.36), 0.24)
        self.addedMarkerColor = isLight
            ? SIMD4<Float>(0.11, 0.57, 0.25, 1.0)
            : SIMD4<Float>(0.43, 0.86, 0.56, 1.0)
        self.deletedMarkerColor = isLight
            ? SIMD4<Float>(0.76, 0.27, 0.30, 1.0)
            : SIMD4<Float>(0.94, 0.50, 0.53, 1.0)
        self.modifiedColor = isLight
            ? SIMD4<Float>(0.15, 0.43, 0.81, 1.0)
            : SIMD4<Float>(0.56, 0.74, 0.98, 1.0)
    }

    func build(
        layout: VVDiffLayoutPlan,
        blockRange: Range<Int>
    ) -> VVDiffRenderArtifacts {
        guard !layout.blocks.isEmpty, blockRange.lowerBound < blockRange.upperBound else {
            return VVDiffRenderArtifacts(quads: [], roundedQuads: [], paths: [], textPasses: [], contentHeight: layout.contentHeight)
        }

        let clampedRange = max(0, blockRange.lowerBound)..<min(layout.blocks.count, blockRange.upperBound)
        guard clampedRange.lowerBound < clampedRange.upperBound else {
            return VVDiffRenderArtifacts(quads: [], roundedQuads: [], paths: [], textPasses: [], contentHeight: layout.contentHeight)
        }

        let rows = layout.document.rows
        let sections = layout.document.sections
        let splitRows = layout.document.splitRows

        var quads: [QuadInstance] = []
        var roundedQuads: [QuadInstance] = []
        var pathBatches: [VVDiffPathBatch] = []
        var fullWidthText = TextPassAccumulator(clipRect: nil)

        var collectedSplits: [CollectedSplit] = []

        for block in layout.blocks[clampedRange] {
            guard let materialized = VVDiffLayoutBuilder.materializedBlock(block, in: layout) else {
                continue
            }

            switch materialized {
            case let .unifiedFileHeader(sectionIndex, _):
                guard sections.indices.contains(sectionIndex) else { continue }
                appendFileHeader(
                    section: sections[sectionIndex],
                    y: block.y,
                    width: layout.metrics.totalWidth,
                    height: block.height,
                    quads: &quads,
                    roundedQuads: &roundedQuads,
                    text: &fullWidthText
                )

            case let .unifiedRow(rowIndex, wrappedLines):
                guard rows.indices.contains(rowIndex) else { continue }
                let row = rows[rowIndex]
                if row.kind == .hunkHeader {
                    appendHunkHeaderRow(
                        lines: materializeWrappedTextSegments(wrappedLines, from: VVDiffDisplayText(for: row)),
                        y: block.y,
                        width: layout.metrics.totalWidth,
                        height: block.height,
                        quads: &quads,
                        text: &fullWidthText
                    )
                } else {
                    appendUnifiedRow(
                        row: row,
                        y: block.y,
                        width: layout.metrics.totalWidth,
                        height: block.height,
                        options: options,
                        gutterColWidth: layout.metrics.gutterColWidth,
                        markerWidth: layout.metrics.markerWidth,
                        codeStartX: layout.metrics.codeStartX,
                        wrappedLines: materializeWrappedTextSegments(wrappedLines, from: row.text),
                        quads: &quads,
                        text: &fullWidthText
                    )
                }

            case let .splitHeader(rowIndex, isFileHeader, wrappedLines):
                guard rows.indices.contains(rowIndex) else { continue }
                let row = rows[rowIndex]
                if isFileHeader {
                    let section = VVDiffSection(id: row.id, filePath: row.text, headerRow: row, rows: [])
                    appendFileHeader(
                        section: section,
                        y: block.y,
                        width: layout.metrics.totalWidth,
                        height: block.height,
                        quads: &quads,
                        roundedQuads: &roundedQuads,
                        text: &fullWidthText
                    )
                } else {
                    appendHunkHeaderRow(
                        lines: materializeWrappedTextSegments(wrappedLines, from: VVDiffDisplayText(for: row)),
                        y: block.y,
                        width: layout.metrics.totalWidth,
                        height: block.height,
                        quads: &quads,
                        text: &fullWidthText
                    )
                }

            case let .splitRow(splitRowIndex, leftWrappedLines, rightWrappedLines):
                guard splitRows.indices.contains(splitRowIndex) else { continue }
                let splitRow = splitRows[splitRowIndex]
                appendSplitCellBackground(
                    cell: splitRow.left,
                    y: block.y,
                    paneX: 0,
                    paneWidth: layout.metrics.columnWidth,
                    height: block.height,
                    options: options,
                    quads: &quads
                )
                appendSplitCellBackground(
                    cell: splitRow.right,
                    y: block.y,
                    paneX: layout.metrics.columnWidth,
                    paneWidth: layout.metrics.columnWidth,
                    height: block.height,
                    options: options,
                    quads: &quads
                )
                collectedSplits.append(
                    CollectedSplit(
                        splitRow: splitRow,
                        y: block.y,
                        height: block.height,
                        leftWrappedLines: materializeWrappedTextSegments(leftWrappedLines, from: splitRow.left?.text ?? ""),
                        rightWrappedLines: materializeWrappedTextSegments(rightWrappedLines, from: splitRow.right?.text ?? "")
                    )
                )
            }
        }

        var textPasses: [VVDiffTextPass] = []
        if !fullWidthText.isEmpty {
            textPasses.append(fullWidthText.makePass())
        }

        if !collectedSplits.isEmpty {
            appendMergedEmptyPaneRuns(
                collectedSplits,
                columnWidth: layout.metrics.columnWidth,
                quads: &quads,
                pathBatches: &pathBatches
            )
        }

        if !collectedSplits.isEmpty {
            let columnWidth = layout.metrics.columnWidth
            let leftPaneClip = CGRect(x: 0, y: 0, width: columnWidth, height: layout.contentHeight)
            let rightPaneClip = CGRect(x: columnWidth, y: 0, width: columnWidth, height: layout.contentHeight)
            var leftText = TextPassAccumulator(clipRect: leftPaneClip)
            var rightText = TextPassAccumulator(clipRect: rightPaneClip)

            for item in collectedSplits {
                if let cell = item.splitRow.left {
                    appendSplitCellContent(
                        cell: cell,
                        wrappedLines: item.leftWrappedLines,
                        y: item.y,
                        paneX: 0,
                        height: item.height,
                        options: options,
                        gutterColWidth: layout.metrics.gutterColWidth,
                        markerWidth: layout.metrics.markerWidth,
                        codeStartX: layout.metrics.codeStartX,
                        quads: &quads,
                        text: &leftText
                    )
                }
                if let cell = item.splitRow.right {
                    appendSplitCellContent(
                        cell: cell,
                        wrappedLines: item.rightWrappedLines,
                        y: item.y,
                        paneX: columnWidth,
                        height: item.height,
                        options: options,
                        gutterColWidth: layout.metrics.gutterColWidth,
                        markerWidth: layout.metrics.markerWidth,
                        codeStartX: layout.metrics.codeStartX,
                        quads: &quads,
                        text: &rightText
                    )
                }
            }

            if !leftText.isEmpty {
                textPasses.append(leftText.makePass())
            }
            if !rightText.isEmpty {
                textPasses.append(rightText.makePass())
            }
        }

        return VVDiffRenderArtifacts(
            quads: quads,
            roundedQuads: roundedQuads,
            paths: pathBatches,
            textPasses: textPasses,
            contentHeight: layout.contentHeight
        )
    }

    private func appendUnifiedRow(
        row: VVDiffRow,
        y: CGFloat,
        width: CGFloat,
        height: CGFloat,
        options: VVDiffRenderOptions,
        gutterColWidth: CGFloat,
        markerWidth: CGFloat,
        codeStartX: CGFloat,
        wrappedLines: [WrappedTextSegment],
        quads: inout [QuadInstance],
        text: inout TextPassAccumulator
    ) {
        quads.append(
            QuadInstance(
                position: SIMD2<Float>(Float(0), Float(y)),
                size: SIMD2<Float>(Float(width), Float(height)),
                color: rowBackgroundColor(for: row.kind, options: options)
            )
        )

        let firstBaselineY = y + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
        let lineNumberColor = lineNumberColor(for: row.kind)

        if options.showsLineNumbers, let oldNum = row.oldLineNumber {
            let glyphs = lineNumberGlyphs(text: String(oldNum), color: lineNumberColor)
            let width = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            appendTextGlyphs(glyphs, offsetX: gutterColWidth - width - 4, baselineY: firstBaselineY, into: &text)
        }

        if options.showsLineNumbers, let newNum = row.newLineNumber {
            let glyphs = lineNumberGlyphs(text: String(newNum), color: lineNumberColor)
            let width = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            appendTextGlyphs(glyphs, offsetX: gutterColWidth * 2 - width - 4, baselineY: firstBaselineY, into: &text)
        }

        appendMarkerIndicator(kind: row.kind, x: 0, y: y, width: markerWidth, height: height, options: options, quads: &quads)

        if row.kind.isCode || row.kind == .metadata {
            let codeColor = row.kind == .metadata ? gutterTextColor : textColor
            for (lineIndex, lineText) in wrappedLines.enumerated() {
                let baselineY = y + CGFloat(lineIndex) * lineHeight + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
                let glyphs = layoutEngine.layoutTextGlyphs(lineText.text, variant: .monospace, at: .zero, color: codeColor)
                let highlightRanges = clippedHighlightRanges(for: row.id, segment: lineText)
                appendTextGlyphs(
                    glyphs,
                    highlightRanges: highlightRanges,
                    offsetX: codeStartX + codeInsetX,
                    baselineY: baselineY,
                    into: &text
                )
            }
        }
    }

    private func appendHunkHeaderRow(
        lines: [WrappedTextSegment],
        y: CGFloat,
        width: CGFloat,
        height: CGFloat,
        quads: inout [QuadInstance],
        text: inout TextPassAccumulator
    ) {
        quads.append(
            QuadInstance(
                position: SIMD2<Float>(Float(0), Float(y)),
                size: SIMD2<Float>(Float(width), Float(height)),
                color: hunkBgColor
            )
        )

        for (lineIndex, lineText) in lines.enumerated() {
            let baselineY = y + CGFloat(lineIndex) * lineHeight + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
            let glyphs = layoutEngine.layoutTextGlyphs(lineText.text, variant: .monospace, at: .zero, color: modifiedColor)
            appendTextGlyphs(glyphs, offsetX: 12, baselineY: baselineY, into: &text)
        }
    }

    private func appendFileHeader(
        section: VVDiffSection,
        y: CGFloat,
        width: CGFloat,
        height: CGFloat,
        quads: inout [QuadInstance],
        roundedQuads: inout [QuadInstance],
        text: inout TextPassAccumulator
    ) {
        quads.append(
            QuadInstance(
                position: SIMD2<Float>(Float(0), Float(y)),
                size: SIMD2<Float>(Float(width), Float(height)),
                color: headerBgColor
            )
        )

        let parts = pathParts(for: section.filePath)
        let baselineY = y + (height + font.pointSize) / 2 - font.pointSize * 0.15
        let iconX: CGFloat = 12
        let iconWidth = appendFileHeaderIcon(x: iconX, centerY: y + height * 0.5, quads: &quads)
        var currentX = iconX + iconWidth + 8

        let nameGlyphs = layoutEngine.layoutTextGlyphs(parts.fileName, variant: .regular, at: .zero, color: textColor)
        appendTextGlyphs(nameGlyphs, offsetX: currentX, baselineY: baselineY, into: &text)
        currentX += (nameGlyphs.map { $0.position.x + $0.size.width }.max() ?? 0) + 8

        if !parts.directory.isEmpty {
            let dirGlyphs = layoutEngine.layoutTextGlyphs(parts.directory, variant: .monospace, at: .zero, color: gutterTextColor)
            appendTextGlyphs(dirGlyphs, offsetX: currentX, baselineY: baselineY, into: &text)
            currentX += (dirGlyphs.map { $0.position.x + $0.size.width }.max() ?? 0) + 12
        }

        let badgeFontSize = max(10, font.pointSize - 1)
        let badgeHeight = max(14, badgeFontSize + 6)
        let badgeY = y + (height - badgeHeight) * 0.5

        if section.addedCount > 0 {
            currentX = appendBadge(
                text: "+\(section.addedCount)",
                color: addedMarkerColor,
                x: currentX,
                badgeY: badgeY,
                badgeH: badgeHeight,
                roundedQuads: &roundedQuads,
                textPass: &text
            ) + 6
        }

        if section.deletedCount > 0 {
            _ = appendBadge(
                text: "-\(section.deletedCount)",
                color: deletedMarkerColor,
                x: currentX,
                badgeY: badgeY,
                badgeH: badgeHeight,
                roundedQuads: &roundedQuads,
                textPass: &text
            )
        }
    }

    @discardableResult
    private func appendFileHeaderIcon(
        x: CGFloat,
        centerY: CGFloat,
        quads: inout [QuadInstance]
    ) -> CGFloat {
        let iconHeight = min(max(font.pointSize * 1.05, 12), 16)
        let iconWidth = iconHeight * 0.78
        let originY = centerY - iconHeight * 0.5
        let frame = CGRect(x: x, y: originY, width: iconWidth, height: iconHeight)
        let borderColor = withAlpha(textColor, 0.94)
        let foldLineColor = withAlpha(textColor, 0.66)
        let fillColor = withAlpha(textColor, 0.16)
        let line = max(1, floor(iconHeight * 0.12))
        let foldSize = max(3, floor(iconWidth * 0.34))

        quads.append(quad(frame: frame, color: fillColor))
        quads.append(quad(frame: CGRect(x: frame.minX, y: frame.minY, width: frame.width - foldSize, height: line), color: borderColor))
        quads.append(quad(frame: CGRect(x: frame.minX, y: frame.maxY - line, width: frame.width, height: line), color: borderColor))
        quads.append(quad(frame: CGRect(x: frame.minX, y: frame.minY, width: line, height: frame.height), color: borderColor))
        quads.append(quad(frame: CGRect(x: frame.maxX - line, y: frame.minY + foldSize, width: line, height: frame.height - foldSize), color: borderColor))

        let foldX = frame.maxX - foldSize
        quads.append(quad(frame: CGRect(x: foldX, y: frame.minY, width: foldSize, height: foldSize), color: headerBgColor))
        quads.append(quad(frame: CGRect(x: foldX, y: frame.minY + foldSize - line, width: foldSize, height: line), color: foldLineColor))
        quads.append(quad(frame: CGRect(x: foldX, y: frame.minY, width: line, height: foldSize), color: foldLineColor))

        return iconWidth
    }

    @discardableResult
    private func appendBadge(
        text: String,
        color: SIMD4<Float>,
        x: CGFloat,
        badgeY: CGFloat,
        badgeH: CGFloat,
        roundedQuads: inout [QuadInstance],
        textPass: inout TextPassAccumulator
    ) -> CGFloat {
        let glyphs = layoutEngine.layoutTextGlyphs(text, variant: .monospace, at: .zero, color: color)
        let textWidth = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
        let badgeWidth = textWidth + 12
        roundedQuads.append(
            QuadInstance(
                position: SIMD2<Float>(Float(x), Float(badgeY)),
                size: SIMD2<Float>(Float(badgeWidth), Float(badgeH)),
                color: withAlpha(color, 0.13),
                cornerRadius: 5
            )
        )
        let textX = x + max(0, (badgeWidth - textWidth) * 0.5)
        let baselineY = badgeY + (badgeH + font.pointSize - 1) * 0.5 - (font.pointSize - 1) * 0.16
        appendTextGlyphs(glyphs, offsetX: textX, baselineY: baselineY, into: &textPass)
        return x + badgeWidth
    }

    private func appendMarkerIndicator(
        kind: VVDiffRow.Kind,
        x: CGFloat,
        y: CGFloat,
        width: CGFloat,
        height: CGFloat,
        options: VVDiffRenderOptions,
        quads: inout [QuadInstance]
    ) {
        switch options.changeIndicatorStyle {
        case .none:
            return
        case .bars:
            let barWidth: CGFloat = min(width, 6)
            switch kind {
            case .added:
                quads.append(quad(frame: CGRect(x: x, y: y, width: barWidth, height: height), color: addedMarkerColor))
            case .deleted:
                let dashHeight: CGFloat = 1
                let gapHeight: CGFloat = 1
                let period = dashHeight + gapHeight
                let phase = y.truncatingRemainder(dividingBy: period)
                var dashY = y - phase
                while dashY < y + height {
                    let top = max(dashY, y)
                    let bottom = min(dashY + dashHeight, y + height)
                    if bottom > top {
                        quads.append(quad(frame: CGRect(x: x, y: top, width: barWidth, height: bottom - top), color: deletedMarkerColor))
                    }
                    dashY += period
                }
            default:
                break
            }
        case .classic:
            let color: SIMD4<Float>
            switch kind {
            case .added:
                color = addedMarkerColor
            case .deleted:
                color = deletedMarkerColor
            default:
                return
            }
            let centerX = x + width * 0.5
            let centerY = y + height * 0.5
            let horizontalWidth = max(6, width - 2)
            let stroke = max(1, floor(lineHeight * 0.08))
            quads.append(
                quad(
                    frame: CGRect(
                        x: centerX - horizontalWidth * 0.5,
                        y: centerY - stroke * 0.5,
                        width: horizontalWidth,
                        height: stroke
                    ),
                    color: color
                )
            )
            if kind == .added {
                quads.append(
                    quad(
                        frame: CGRect(
                            x: centerX - stroke * 0.5,
                            y: centerY - horizontalWidth * 0.5,
                            width: stroke,
                            height: horizontalWidth
                        ),
                        color: color
                    )
                )
            }
        }
    }

    private func appendSplitCellBackground(
        cell: VVDiffSplitRow.Cell?,
        y: CGFloat,
        paneX: CGFloat,
        paneWidth: CGFloat,
        height: CGFloat,
        options: VVDiffRenderOptions,
        quads: inout [QuadInstance]
    ) {
        let background: SIMD4<Float>
        if let cell {
            switch cell.kind {
            case .added:
                background = options.showsBackgrounds ? addedBgColor : backgroundColor
            case .deleted:
                background = options.showsBackgrounds ? deletedBgColor : backgroundColor
            default:
                background = backgroundColor
            }
        } else {
            background = backgroundColor
        }
        quads.append(
            QuadInstance(
                position: SIMD2<Float>(Float(paneX), Float(y)),
                size: SIMD2<Float>(Float(paneWidth), Float(height)),
                color: background
            )
        )
    }

    private func appendSplitCellContent(
        cell: VVDiffSplitRow.Cell,
        wrappedLines: [WrappedTextSegment],
        y: CGFloat,
        paneX: CGFloat,
        height: CGFloat,
        options: VVDiffRenderOptions,
        gutterColWidth: CGFloat,
        markerWidth: CGFloat,
        codeStartX: CGFloat,
        quads: inout [QuadInstance],
        text: inout TextPassAccumulator
    ) {
        let firstBaselineY = y + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
        appendMarkerIndicator(kind: cell.kind, x: paneX, y: y, width: markerWidth, height: height, options: options, quads: &quads)

        if options.showsLineNumbers, let lineNumber = cell.lineNumber {
            let glyphs = lineNumberGlyphs(text: String(lineNumber), color: lineNumberColor(for: cell.kind))
            let width = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            let numX = paneX + markerWidth + gutterColWidth - width - 8
            appendTextGlyphs(glyphs, offsetX: numX, baselineY: firstBaselineY, into: &text)
        }

        let inlineHighlightColor = cell.kind == .deleted ? withAlpha(deletedMarkerColor, 0.22) : withAlpha(addedMarkerColor, 0.22)
        for (lineIndex, lineText) in wrappedLines.enumerated() {
            let baselineY = y + CGFloat(lineIndex) * lineHeight + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
            let glyphs = layoutEngine.layoutTextGlyphs(lineText.text, variant: .monospace, at: .zero, color: textColor)
            let highlightRanges = clippedHighlightRanges(for: cell.rowID, segment: lineText)

            if options.inlineHighlightStyle != .off {
                for range in clippedInlineChanges(cell.inlineChanges, segment: lineText) {
                    let startX = glyphXForCharIndex(range.start, in: glyphs)
                    let endX = glyphXForCharIndex(range.end, in: glyphs)
                    let highlightWidth = endX - startX
                    if highlightWidth > 0 {
                        quads.append(
                            quad(
                                frame: CGRect(
                                    x: paneX + codeStartX + codeInsetX + startX,
                                    y: y + CGFloat(lineIndex) * lineHeight,
                                    width: highlightWidth,
                                    height: lineHeight
                                ),
                                color: inlineHighlightColor
                            )
                        )
                    }
                }
            }

            appendTextGlyphs(
                glyphs,
                highlightRanges: highlightRanges,
                offsetX: paneX + codeStartX + codeInsetX,
                baselineY: baselineY,
                into: &text
            )
        }
    }

    private func appendMergedEmptyPaneRuns(
        _ collectedSplits: [CollectedSplit],
        columnWidth: CGFloat,
        quads: inout [QuadInstance],
        pathBatches: inout [VVDiffPathBatch]
    ) {
        func emptySegment(
            for item: CollectedSplit,
            wrappedLineCount: Int,
            hasCell: Bool
        ) -> (startY: CGFloat, endY: CGFloat)? {
            let logicalLineCount = max(1, max(item.leftWrappedLines.count, item.rightWrappedLines.count))
            let occupiedLineCount = hasCell ? wrappedLineCount : 0
            guard occupiedLineCount < logicalLineCount else { return nil }
            return (
                startY: item.y + CGFloat(occupiedLineCount) * lineHeight,
                endY: item.y + item.height
            )
        }

        func accumulateRuns(
            paneX: CGFloat,
            emptySegmentForItem: (CollectedSplit) -> (startY: CGFloat, endY: CGFloat)?
        ) {
            var accumulator = PathAccumulator(fillColor: emptyPaneGuideColor)
            var runStartY: CGFloat?
            var runEndY: CGFloat?

            func flushRun() {
                guard let startY = runStartY, let endY = runEndY, endY > startY + 0.5 else { return }
                let paneRect = CGRect(x: paneX, y: startY, width: columnWidth, height: endY - startY)
                appendEmptySplitPanePlaceholder(
                    paneRect: paneRect,
                    into: &accumulator
                )
                runStartY = nil
                runEndY = nil
            }

            for item in collectedSplits {
                if let segment = emptySegmentForItem(item) {
                    if runStartY == nil {
                        runStartY = segment.startY
                        runEndY = segment.endY
                    } else if let currentEnd = runEndY, abs(segment.startY - currentEnd) < 0.5 {
                        runEndY = segment.endY
                    } else {
                        flushRun()
                        runStartY = segment.startY
                        runEndY = segment.endY
                    }
                } else {
                    flushRun()
                }
            }

            flushRun()

            if let batch = accumulator.makeBatch() {
                pathBatches.append(batch)
            }
        }

        accumulateRuns(paneX: 0) {
            emptySegment(for: $0, wrappedLineCount: $0.leftWrappedLines.count, hasCell: $0.splitRow.left != nil)
        }
        accumulateRuns(paneX: columnWidth) {
            emptySegment(for: $0, wrappedLineCount: $0.rightWrappedLines.count, hasCell: $0.splitRow.right != nil)
        }
    }

    private func appendEmptySplitPanePlaceholder(
        paneRect: CGRect,
        into accumulator: inout PathAccumulator
    ) {
        guard paneRect.width > 12, paneRect.height > 6 else { return }

        let stripeThickness: CGFloat = max(2, floor(lineHeight * 0.11))
        let stripeSpacing: CGFloat = max(12, floor(lineHeight * 0.60))
        let phaseShift = paneRect.minY.truncatingRemainder(dividingBy: stripeSpacing)
        let cachedVertices = cachedEmptyPaneHatchVertices(
            width: paneRect.width,
            height: paneRect.height,
            phaseShift: phaseShift,
            stripeThickness: stripeThickness,
            stripeSpacing: stripeSpacing
        )
        guard !cachedVertices.isEmpty else { return }

        let translatedVertices = cachedVertices.map {
            PathRenderVertex(
                position: SIMD2<Float>(
                    $0.position.x + Float(paneRect.minX),
                    $0.position.y + Float(paneRect.minY)
                ),
                stPosition: $0.stPosition
            )
        }
        accumulator.append(fillVertices: translatedVertices)
    }

    private func cachedEmptyPaneHatchVertices(
        width: CGFloat,
        height: CGFloat,
        phaseShift: CGFloat,
        stripeThickness: CGFloat,
        stripeSpacing: CGFloat
    ) -> [PathRenderVertex] {
        let key = EmptyPaneHatchCacheKey(
            widthKey: Int((width * 2).rounded()),
            heightKey: Int((height * 2).rounded()),
            phaseKey: Int((phaseShift * 4).rounded()),
            thicknessKey: Int((stripeThickness * 4).rounded()),
            spacingKey: Int((stripeSpacing * 4).rounded())
        )

        Self.emptyPaneHatchCacheLock.lock()
        if let cached = Self.emptyPaneHatchCache[key] {
            Self.emptyPaneHatchCacheLock.unlock()
            return cached
        }
        Self.emptyPaneHatchCacheLock.unlock()

        let originRect = CGRect(x: 0, y: 0, width: width, height: height)
        let stripeTravel = max(originRect.width + originRect.height, 24)
        let startX = -stripeTravel - stripeSpacing - phaseShift
        let endX = originRect.maxX + stripeSpacing

        var vertices: [PathRenderVertex] = []
        var x = startX
        while x <= endX {
            let dx = stripeTravel
            let dy = stripeTravel
            let invLength = 1 / max(1, hypot(dx, dy))
            let normalX = -dy * invLength * stripeThickness * 0.5
            let normalY = dx * invLength * stripeThickness * 0.5
            let p0 = CGPoint(x: round(x), y: 0)
            let p1 = CGPoint(x: round(x + dx), y: round(dy))
            let polygon = [
                CGPoint(x: p0.x + normalX, y: p0.y + normalY),
                CGPoint(x: p0.x - normalX, y: p0.y - normalY),
                CGPoint(x: p1.x - normalX, y: p1.y - normalY),
                CGPoint(x: p1.x + normalX, y: p1.y + normalY)
            ]
            let clipped = clipPolygon(polygon, to: originRect)
            if clipped.count >= 3 {
                var path = VVPathBuilder()
                path.addPolygon(clipped)
                let primitive = path.build(fill: emptyPaneGuideColor)
                vertices.append(contentsOf: primitive.vertices.map {
                    PathRenderVertex(
                        position: SIMD2<Float>(Float($0.position.x), Float($0.position.y)),
                        stPosition: SIMD2<Float>(Float($0.stPosition.x), Float($0.stPosition.y))
                    )
                })
            }
            x += stripeSpacing
        }

        Self.emptyPaneHatchCacheLock.lock()
        Self.emptyPaneHatchCache[key] = vertices
        Self.emptyPaneHatchCacheLock.unlock()
        return vertices
    }

    private func appendTextGlyphs(
        _ glyphs: [MDLayoutGlyph],
        highlightRanges: [(NSRange, SIMD4<Float>)] = [],
        offsetX: CGFloat,
        baselineY: CGFloat,
        into pass: inout TextPassAccumulator
    ) {
        guard !glyphs.isEmpty else { return }
        var rangeIndex = 0

        for glyph in glyphs {
            let resolvedColor: SIMD4<Float>
            if highlightRanges.isEmpty {
                resolvedColor = glyph.color
            } else if let stringIndex = glyph.stringIndex {
                while rangeIndex < highlightRanges.count && NSMaxRange(highlightRanges[rangeIndex].0) <= stringIndex {
                    rangeIndex += 1
                }
                if rangeIndex < highlightRanges.count {
                    let (range, color) = highlightRanges[rangeIndex]
                    resolvedColor = (stringIndex >= range.location && stringIndex < NSMaxRange(range)) ? color : glyph.color
                } else {
                    resolvedColor = glyph.color
                }
            } else {
                resolvedColor = glyph.color
            }

            guard let cached = cachedGlyph(for: glyph) else { continue }
            let glyphColor = cached.isColor ? SIMD4<Float>(1, 1, 1, resolvedColor.w) : resolvedColor
            let instance = VVTextGlyphInstance(
                position: SIMD2<Float>(
                    Float(glyph.position.x + offsetX + cached.bearing.x),
                    Float(baselineY + cached.bearing.y)
                ),
                size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
                uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
                uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
                color: glyphColor,
                atlasIndex: UInt32(cached.atlasIndex)
            )

            if cached.isColor {
                pass.colorGlyphBatches[cached.atlasIndex, default: []].append(instance)
            } else {
                pass.glyphBatches[cached.atlasIndex, default: []].append(instance)
            }
        }
    }

    private func cachedGlyph(for glyph: MDLayoutGlyph) -> VVTextCachedGlyph? {
        let variant = VVFontVariant(markdownVariant: glyph.fontVariant)
        if let fontName = glyph.fontName {
            return metalRenderer.glyphAtlas.glyph(
                for: glyph.glyphID,
                fontName: fontName,
                fontSize: glyph.fontSize,
                variant: variant
            )
        }

        let key = packedBaseGlyphLookupKey(
            glyphID: glyph.glyphID,
            fontVariant: variant,
            fontSizeKey: Int(glyph.fontSize * 100)
        )
        if let cached = baseGlyphLookupCache[key] {
            return cached
        }

        let resolved = metalRenderer.glyphAtlas.glyph(
            for: glyph.glyphID,
            variant: variant,
            fontSize: glyph.fontSize,
            baseFont: metalRenderer.baseFont
        )
        if let resolved {
            baseGlyphLookupCache[key] = resolved
        }
        return resolved
    }

    private func packedBaseGlyphLookupKey(
        glyphID: CGGlyph,
        fontVariant: VVFontVariant,
        fontSizeKey: Int
    ) -> BaseGlyphLookupKey {
        let packedSize = UInt64(UInt32(clamping: max(0, fontSizeKey)))
        return UInt64(glyphID)
            | (UInt64(fontVariant.diffCacheKey) << 16)
            | (packedSize << 24)
    }

    private func glyphXForCharIndex(_ charIndex: Int, in glyphs: [MDLayoutGlyph]) -> CGFloat {
        for glyph in glyphs {
            if let index = glyph.stringIndex, index >= charIndex {
                return glyph.position.x
            }
        }
        return glyphs.last.map { $0.position.x + $0.size.width } ?? 0
    }

    private func clippedHighlightRanges(
        for rowID: Int,
        segment: WrappedTextSegment
    ) -> [(NSRange, SIMD4<Float>)] {
        guard let ranges = highlightedRanges[rowID], !ranges.isEmpty else { return [] }
        var clipped: [(NSRange, SIMD4<Float>)] = []
        clipped.reserveCapacity(ranges.count)
        for (range, color) in ranges {
            let start = max(segment.start, range.location)
            let end = min(segment.end, NSMaxRange(range))
            if end > start {
                clipped.append((NSRange(location: start - segment.start, length: end - start), color))
            }
        }
        return clipped
    }

    private func clippedInlineChanges(
        _ inlineChanges: [VVDiffSplitRow.InlineRange],
        segment: WrappedTextSegment
    ) -> [VVDiffSplitRow.InlineRange] {
        guard !inlineChanges.isEmpty else { return [] }
        var clipped: [VVDiffSplitRow.InlineRange] = []
        clipped.reserveCapacity(inlineChanges.count)
        for range in inlineChanges {
            let start = max(segment.start, range.start)
            let end = min(segment.end, range.end)
            if end > start {
                clipped.append(.init(start: start - segment.start, end: end - segment.start))
            }
        }
        return clipped
    }

    private func materializeWrappedTextSegments(
        _ descriptors: [VVDiffWrappedTextDescriptor],
        from sourceText: String
    ) -> [WrappedTextSegment] {
        guard !descriptors.isEmpty else { return [WrappedTextSegment(text: "", start: 0, length: 0)] }
        return descriptors.map { descriptor in
            guard descriptor.length > 0 else {
                return WrappedTextSegment(text: "", start: descriptor.start, length: 0)
            }
            let boundedStart = min(max(0, descriptor.start), sourceText.count)
            let boundedLength = min(max(0, descriptor.length), sourceText.count - boundedStart)
            let startIndex = sourceText.index(sourceText.startIndex, offsetBy: boundedStart)
            let endIndex = sourceText.index(startIndex, offsetBy: boundedLength)
            return WrappedTextSegment(
                text: String(sourceText[startIndex..<endIndex]),
                start: descriptor.start,
                length: boundedLength
            )
        }
    }

    private func lineNumberGlyphs(text: String, color: SIMD4<Float>) -> [MDLayoutGlyph] {
        let key = LineNumberGlyphCacheKey(text: text, color: color)
        if let cached = lineNumberGlyphCache[key] {
            return cached
        }
        let glyphs = layoutEngine.layoutTextGlyphs(text, variant: .monospace, at: .zero, color: color)
        lineNumberGlyphCache[key] = glyphs
        return glyphs
    }

    private func rowBackgroundColor(
        for kind: VVDiffRow.Kind,
        options: VVDiffRenderOptions
    ) -> SIMD4<Float> {
        switch kind {
        case .added:
            return options.showsBackgrounds ? addedBgColor : backgroundColor
        case .deleted:
            return options.showsBackgrounds ? deletedBgColor : backgroundColor
        case .hunkHeader:
            return hunkBgColor
        case .metadata:
            return metadataBgColor
        case .context:
            return backgroundColor
        case .fileHeader:
            return headerBgColor
        }
    }

    private func lineNumberColor(for kind: VVDiffRow.Kind) -> SIMD4<Float> {
        switch kind {
        case .added:
            return addedMarkerColor
        case .deleted:
            return deletedMarkerColor
        default:
            return gutterTextColor
        }
    }

    private func clipPolygon(_ polygon: [CGPoint], to rect: CGRect) -> [CGPoint] {
        guard polygon.count >= 3 else { return [] }

        enum Edge {
            case left
            case right
            case top
            case bottom
        }

        func inside(_ point: CGPoint, edge: Edge) -> Bool {
            switch edge {
            case .left:
                return point.x >= rect.minX
            case .right:
                return point.x <= rect.maxX
            case .top:
                return point.y >= rect.minY
            case .bottom:
                return point.y <= rect.maxY
            }
        }

        func intersection(from start: CGPoint, to end: CGPoint, edge: Edge) -> CGPoint {
            let dx = end.x - start.x
            let dy = end.y - start.y

            switch edge {
            case .left:
                let x = rect.minX
                let t = dx == 0 ? 0 : (x - start.x) / dx
                return CGPoint(x: x, y: start.y + dy * t)
            case .right:
                let x = rect.maxX
                let t = dx == 0 ? 0 : (x - start.x) / dx
                return CGPoint(x: x, y: start.y + dy * t)
            case .top:
                let y = rect.minY
                let t = dy == 0 ? 0 : (y - start.y) / dy
                return CGPoint(x: start.x + dx * t, y: y)
            case .bottom:
                let y = rect.maxY
                let t = dy == 0 ? 0 : (y - start.y) / dy
                return CGPoint(x: start.x + dx * t, y: y)
            }
        }

        var output = polygon
        for edge in [Edge.left, .right, .top, .bottom] {
            guard !output.isEmpty else { break }
            let input = output
            output = []
            var previous = input[input.count - 1]

            for current in input {
                let currentInside = inside(current, edge: edge)
                let previousInside = inside(previous, edge: edge)

                if currentInside {
                    if !previousInside {
                        output.append(intersection(from: previous, to: current, edge: edge))
                    }
                    output.append(current)
                } else if previousInside {
                    output.append(intersection(from: previous, to: current, edge: edge))
                }

                previous = current
            }
        }

        return output
    }

    private func quad(frame: CGRect, color: SIMD4<Float>) -> QuadInstance {
        QuadInstance(
            position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
            size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
            color: color
        )
    }
}

private func brightness(of color: SIMD4<Float>) -> Double {
    0.2126 * Double(color.x) + 0.7152 * Double(color.y) + 0.0722 * Double(color.z)
}

private func withAlpha(_ color: SIMD4<Float>, _ alpha: Float) -> SIMD4<Float> {
    SIMD4(color.x, color.y, color.z, alpha)
}

private func blended(_ a: SIMD4<Float>, _ b: SIMD4<Float>, _ t: Float) -> SIMD4<Float> {
    let clampedT = max(0, min(1, t))
    let inverse = 1 - clampedT
    return SIMD4(
        a.x * inverse + b.x * clampedT,
        a.y * inverse + b.y * clampedT,
        a.z * inverse + b.z * clampedT,
        a.w * inverse + b.w * clampedT
    )
}

private func pathParts(for path: String) -> (fileName: String, directory: String) {
    ((path as NSString).lastPathComponent, (path as NSString).deletingLastPathComponent)
}
