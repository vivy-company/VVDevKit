//  VVMarkdownSelectionHelper.swift
//  VVMarkdown
//
//  Shared CTLine-based selection logic for markdown layouts.

import Foundation
import CoreText
import VVMetalPrimitives

// MARK: - MarkdownTextPosition

/// Position in a markdown layout for text selection.
public struct MarkdownTextPosition: Sendable, Hashable, Comparable {
    public let blockIndex: Int
    public let runIndex: Int
    public let characterOffset: Int

    public init(blockIndex: Int, runIndex: Int, characterOffset: Int) {
        self.blockIndex = blockIndex
        self.runIndex = runIndex
        self.characterOffset = characterOffset
    }

    public static func < (lhs: MarkdownTextPosition, rhs: MarkdownTextPosition) -> Bool {
        if lhs.blockIndex != rhs.blockIndex { return lhs.blockIndex < rhs.blockIndex }
        if lhs.runIndex != rhs.runIndex { return lhs.runIndex < rhs.runIndex }
        return lhs.characterOffset < rhs.characterOffset
    }
}

// MARK: - Line Metrics

/// CTLine metrics for a single text run.
public struct MarkdownLineMetrics {
    public let line: CTLine
    public let length: Int
    public let originX: CGFloat
    public let lineY: CGFloat
    public let lineHeight: CGFloat
    public let baseline: CGFloat
    public let ascent: CGFloat
    public let descent: CGFloat
    public let lineWidth: CGFloat
}

// MARK: - Selection Segment (for line-merging)

private struct SelectionSegment {
    let lineKey: Int
    let rect: CGRect
}

private struct GlyphBoundary {
    let index: Int
    let x: CGFloat
}

private struct GlyphRunGeometry {
    let minX: CGFloat
    let maxX: CGFloat
    let boundaries: [GlyphBoundary]
}

private struct RunBoundsSummary {
    let minX: CGFloat
    let maxX: CGFloat
    let lineY: CGFloat
    let lineHeight: CGFloat

    var rect: CGRect {
        CGRect(
            x: minX,
            y: lineY,
            width: max(1, maxX - minX),
            height: lineHeight
        )
    }
}

// MARK: - VVMarkdownSelectionHelper

/// Extracts CTLine-based selection logic shared between VVMarkdownView and VVChatTimelineView.
/// Does not depend on any renderer or GlyphAtlas — uses CoreText metrics exclusively.
public final class VVMarkdownSelectionHelper {
    public let layout: MarkdownLayout
    public let layoutEngine: MarkdownLayoutEngine
    private struct RunCacheKey: Hashable {
        let blockIndex: Int
        let runIndex: Int
    }
    private struct RunMetricsSignature: Hashable {
        let text: String
        let positionX: CGFloat
        let positionY: CGFloat
        let rangeLowerBound: Int
        let rangeUpperBound: Int
        let lineY: CGFloat?
        let lineHeight: CGFloat?
        let color: SIMD4<Float>
        let isBold: Bool
        let isItalic: Bool
        let isCode: Bool
        let fontVariant: FontVariant?
    }

    private var textRunsCache: [Int: [LayoutTextRun]?] = [:]
    private var lineMetricsCache: [RunCacheKey: MarkdownLineMetrics] = [:]
    private var lineMetricsCacheOrder: [RunCacheKey] = []
    private var sharedLineMetricsCache: [RunMetricsSignature: MarkdownLineMetrics] = [:]
    private var sharedLineMetricsCacheOrder: [RunMetricsSignature] = []
    private var runBoundsCache: [RunCacheKey: RunBoundsSummary] = [:]
    private var runBoundsCacheOrder: [RunCacheKey] = []
    private var glyphGeometryCache: [RunCacheKey: GlyphRunGeometry] = [:]
    private var glyphGeometryCacheOrder: [RunCacheKey] = []
    private var firstPositionCache: MarkdownTextPosition?
    private var lastPositionCache: MarkdownTextPosition?
    private var spaceWidthCache: CGFloat?
    private static let maxCachedLineMetrics = 512
    private static let maxCachedRunBounds = 1024
    private static let maxCachedGlyphGeometries = 512

    public init(layout: MarkdownLayout, layoutEngine: MarkdownLayoutEngine) {
        self.layout = layout
        self.layoutEngine = layoutEngine
    }

    // MARK: - Text Runs

    public func getTextRuns(from block: LayoutBlock) -> [LayoutTextRun]? {
        switch block.content {
        case .text(let runs):
            return runs
        case .inline(let runs, _):
            return runs
        case .code(_, _, let lines):
            return codeTextRuns(from: block, lines: lines)
        case .diff:
            return nil
        case .imageRow:
            return nil
        case .listItems(let items):
            return textRuns(in: items)
        case .quoteBlocks(let blocks):
            return blocks.compactMap { getTextRuns(from: $0) }.flatMap { $0 }
        case .tableRows(let rows):
            return rows.flatMap { $0.cells.flatMap { $0.textRuns } }
        case .definitionList(let items):
            var runs: [LayoutTextRun] = []
            for item in items {
                runs.append(contentsOf: item.termRuns)
                for defRuns in item.definitionRuns {
                    runs.append(contentsOf: defRuns)
                }
            }
            return runs
        case .abbreviationList(let items):
            return items.flatMap { $0.runs }
        case .mermaid:
            return nil
        default:
            return nil
        }
    }

    private func textRuns(for blockIndex: Int) -> [LayoutTextRun]? {
        if let cached = textRunsCache[blockIndex] {
            return cached
        }
        guard layout.blocks.indices.contains(blockIndex) else { return nil }
        let runs = getTextRuns(from: layout.blocks[blockIndex])
        textRunsCache[blockIndex] = runs
        return runs
    }

    private func codeTextRuns(from block: LayoutBlock, lines: [LayoutCodeLine]) -> [LayoutTextRun] {
        guard !lines.isEmpty else { return [] }

        let theme = layoutEngine.currentTheme
        let padding = CGFloat(theme.codeBlockPadding)
        let borderWidth = CGFloat(theme.codeBorderWidth)
        let frame = block.frame
        let contentOriginX = frame.origin.x + borderWidth
        let contentOriginY = frame.origin.y + borderWidth

        let maxLineNumber = max(lines.map(\.lineNumber).max() ?? 0, lines.count)
        let gutterWidth = codeGutterWidth(for: maxLineNumber)
        let startX = contentOriginX + padding + gutterWidth
        let lineHeight = layoutEngine.currentLineHeight
        let ascent = layoutEngine.currentAscent
        let descent = layoutEngine.currentDescent
        let extraLeading = max(0, lineHeight - (ascent + descent))
        let baselineOffset = ascent + extraLeading * 0.5

        var runs: [LayoutTextRun] = []
        runs.reserveCapacity(lines.count)

        for line in lines {
            let lineY = contentOriginY + line.yOffset
            let lineTop = lineY - baselineOffset
            let glyphs = layoutEngine.layoutCodeGlyphs(line.text, at: CGPoint(x: startX, y: lineY), color: theme.codeColor)
            var style = TextRunStyle(color: theme.codeColor)
            style.isCode = true
            let range = 0..<max(0, line.text.count)
            runs.append(LayoutTextRun(
                text: line.text,
                position: CGPoint(x: startX, y: lineY),
                glyphs: glyphs,
                style: style,
                characterRange: range,
                lineY: lineTop,
                lineHeight: lineHeight
            ))
        }

        return runs
    }

    private func textRuns(in items: [LayoutListItem]) -> [LayoutTextRun] {
        var runs: [LayoutTextRun] = []
        for item in items {
            runs.append(contentsOf: item.contentRuns)
            runs.append(contentsOf: textRuns(in: item.children))
        }
        return runs
    }

    private func codeGutterWidth(for maxLineNumber: Int) -> CGFloat {
        let digits = max(1, String(maxLineNumber).count)
        let charWidth = layoutEngine.measureTextWidth("8", variant: .monospace)
        return max(30, (CGFloat(digits) + 1.2) * charWidth)
    }

    // MARK: - Run Metrics

    public func runTextLength(_ run: LayoutTextRun) -> Int {
        (run.text as NSString).length
    }

    public func lineMetrics(for run: LayoutTextRun) -> MarkdownLineMetrics? {
        let signature = RunMetricsSignature(
            text: run.text,
            positionX: run.position.x,
            positionY: run.position.y,
            rangeLowerBound: run.characterRange.lowerBound,
            rangeUpperBound: run.characterRange.upperBound,
            lineY: run.lineY,
            lineHeight: run.lineHeight,
            color: run.style.color,
            isBold: run.style.isBold,
            isItalic: run.style.isItalic,
            isCode: run.style.isCode,
            fontVariant: run.style.fontVariant
        )
        if let cached = sharedLineMetricsCache[signature] {
            touchSharedLineMetricsCache(signature)
            return cached
        }

        let length = runTextLength(run)
        guard let font = runFont(for: run) else { return nil }

        let attributes: [NSAttributedString.Key: Any] = [
            .font: font,
            .ligature: 1
        ]
        let line = CTLineCreateWithAttributedString(NSAttributedString(string: run.text, attributes: attributes))
        let baseline = run.position.y
        let lineWidth = CGFloat(CTLineGetTypographicBounds(line, nil, nil, nil))

        if let runLineY = run.lineY, let runLineHeight = run.lineHeight, runLineHeight > 0 {
            let ascent = max(1, baseline - runLineY)
            let descent = max(1, runLineY + runLineHeight - baseline)
            let metrics = MarkdownLineMetrics(line: line, length: length, originX: run.position.x, lineY: runLineY, lineHeight: runLineHeight, baseline: baseline, ascent: ascent, descent: descent, lineWidth: lineWidth)
            storeSharedLineMetrics(metrics, for: signature)
            return metrics
        }

        let fontAscent = CTFontGetAscent(font)
        let fontDescent = CTFontGetDescent(font)
        let leading = CTFontGetLeading(font)
        let ascent = fontAscent
        let descent = fontDescent
        let baseLineHeight = ceil((fontAscent + fontDescent + leading) * 1.05)
        let extraLeading = max(0, baseLineHeight - (ascent + descent))
        let lineY = baseline - ascent - extraLeading * 0.5
        let lineHeight = baseLineHeight
        let metrics = MarkdownLineMetrics(line: line, length: length, originX: run.position.x, lineY: lineY, lineHeight: lineHeight, baseline: baseline, ascent: ascent, descent: descent, lineWidth: lineWidth)
        storeSharedLineMetrics(metrics, for: signature)
        return metrics
    }

    private func lineMetrics(for run: LayoutTextRun, blockIndex: Int, runIndex: Int) -> MarkdownLineMetrics? {
        let key = RunCacheKey(blockIndex: blockIndex, runIndex: runIndex)
        if let cached = lineMetricsCache[key] {
            touchLineMetricsCache(key)
            return cached
        }
        guard let metrics = lineMetrics(for: run) else { return nil }
        storeLineMetrics(metrics, for: key)
        return metrics
    }

    private func glyphGeometry(for run: LayoutTextRun, blockIndex: Int, runIndex: Int) -> GlyphRunGeometry? {
        let key = RunCacheKey(blockIndex: blockIndex, runIndex: runIndex)
        if let cached = glyphGeometryCache[key] {
            touchGlyphGeometryCache(key)
            return cached
        }
        guard let geometry = buildGlyphGeometry(for: run) else { return nil }
        glyphGeometryCache[key] = geometry
        touchGlyphGeometryCache(key)
        while glyphGeometryCacheOrder.count > Self.maxCachedGlyphGeometries {
            let evicted = glyphGeometryCacheOrder.removeFirst()
            glyphGeometryCache.removeValue(forKey: evicted)
        }
        return geometry
    }

    private func runBounds(for run: LayoutTextRun, blockIndex: Int, runIndex: Int) -> RunBoundsSummary {
        let key = RunCacheKey(blockIndex: blockIndex, runIndex: runIndex)
        if let cached = runBoundsCache[key] {
            touchRunBoundsCache(key)
            return cached
        }
        let summary = buildRunBounds(for: run)
        runBoundsCache[key] = summary
        touchRunBoundsCache(key)
        while runBoundsCacheOrder.count > Self.maxCachedRunBounds {
            let evicted = runBoundsCacheOrder.removeFirst()
            runBoundsCache.removeValue(forKey: evicted)
        }
        return summary
    }

    private func touchRunBoundsCache(_ key: RunCacheKey) {
        runBoundsCacheOrder.removeAll { $0 == key }
        runBoundsCacheOrder.append(key)
    }

    private func buildRunBounds(for run: LayoutTextRun) -> RunBoundsSummary {
        let defaultLineHeight = max(
            1,
            run.lineHeight ?? run.glyphs.first?.size.height ?? layoutEngine.currentLineHeight
        )
        let lineHeight = defaultLineHeight
        let lineY = run.lineY ?? (run.position.y - lineHeight * 0.8)

        var minX = CGFloat.greatestFiniteMagnitude
        var maxX: CGFloat = -.greatestFiniteMagnitude
        for glyph in run.glyphs where glyph.size.width > 0 {
            minX = min(minX, glyph.position.x)
            maxX = max(maxX, glyph.position.x + max(1, glyph.size.width))
        }

        if !minX.isFinite || !maxX.isFinite || maxX <= minX {
            minX = run.position.x
            maxX = run.position.x + max(1, layoutEngine.measureTextWidth(run.text, variant: runFontVariant(run)))
        }

        return RunBoundsSummary(
            minX: minX,
            maxX: maxX,
            lineY: lineY,
            lineHeight: lineHeight
        )
    }

    private func touchGlyphGeometryCache(_ key: RunCacheKey) {
        glyphGeometryCacheOrder.removeAll { $0 == key }
        glyphGeometryCacheOrder.append(key)
    }

    private func buildGlyphGeometry(for run: LayoutTextRun) -> GlyphRunGeometry? {
        var glyphs = run.glyphs.filter { $0.size.width > 0 }
        guard !glyphs.isEmpty else { return nil }

        var isOrdered = true
        var previousX = glyphs[0].position.x
        var previousIndex = glyphs[0].stringIndex ?? 0
        for glyph in glyphs.dropFirst() {
            let glyphIndex = glyph.stringIndex ?? previousIndex
            if glyph.position.x < previousX || (glyph.position.x == previousX && glyphIndex < previousIndex) {
                isOrdered = false
                break
            }
            previousX = glyph.position.x
            previousIndex = glyphIndex
        }
        if !isOrdered {
            glyphs.sort { lhs, rhs in
                if lhs.position.x != rhs.position.x {
                    return lhs.position.x < rhs.position.x
                }
                return (lhs.stringIndex ?? 0) < (rhs.stringIndex ?? 0)
            }
        }

        let length = runTextLength(run)
        var minX = CGFloat.greatestFiniteMagnitude
        var maxX: CGFloat = -.greatestFiniteMagnitude
        var boundaries: [GlyphBoundary] = [GlyphBoundary(index: 0, x: glyphs[0].position.x)]
        boundaries.reserveCapacity(glyphs.count + 2)

        for (i, glyph) in glyphs.enumerated() {
            let startX = glyph.position.x
            let nextStartX = i + 1 < glyphs.count ? glyphs[i + 1].position.x : startX + max(1, glyph.size.width)
            let endX = max(startX + max(1, glyph.size.width), nextStartX)
            minX = min(minX, startX)
            maxX = max(maxX, endX)
            if let stringIndex = glyph.stringIndex {
                if boundaries.last?.index != stringIndex {
                    boundaries.append(GlyphBoundary(index: stringIndex, x: startX))
                } else if let last = boundaries.last, startX < last.x {
                    boundaries[boundaries.count - 1] = GlyphBoundary(index: stringIndex, x: startX)
                }
            }
        }

        if boundaries.first?.x != minX {
            boundaries.insert(GlyphBoundary(index: 0, x: minX), at: 0)
        }
        if boundaries.last?.index != length {
            boundaries.append(GlyphBoundary(index: length, x: maxX))
        } else if let last = boundaries.last, maxX > last.x {
            boundaries[boundaries.count - 1] = GlyphBoundary(index: length, x: maxX)
        }

        return GlyphRunGeometry(minX: minX, maxX: maxX, boundaries: boundaries)
    }

    private func geometryLineRect(for run: LayoutTextRun, geometry: GlyphRunGeometry) -> CGRect {
        let summary = buildRunBounds(for: run)
        return CGRect(x: geometry.minX, y: summary.lineY, width: max(1, geometry.maxX - geometry.minX), height: summary.lineHeight)
    }

    private func geometryHitRect(for run: LayoutTextRun, geometry: GlyphRunGeometry) -> CGRect {
        var rect = geometryLineRect(for: run, geometry: geometry)
        let padY = max(2, rect.height * 0.2)
        let padX = max(2, rect.height * 0.12)
        rect = rect.insetBy(dx: -padX, dy: -padY)
        return rect
    }

    private func glyphIndexForX(_ x: CGFloat, geometry: GlyphRunGeometry, length: Int) -> Int {
        let boundaries = geometry.boundaries
        if x <= geometry.minX { return 0 }
        if x >= geometry.maxX { return length }
        for i in 0..<(boundaries.count - 1) {
            let lhs = boundaries[i]
            let rhs = boundaries[i + 1]
            let midpoint = lhs.x + (rhs.x - lhs.x) * 0.5
            if x < midpoint {
                return lhs.index
            }
            if x <= rhs.x {
                return rhs.index
            }
        }
        return length
    }

    private func xForCharacterIndex(_ index: Int, geometry: GlyphRunGeometry, length: Int, preferTrailingEdge: Bool) -> CGFloat {
        let clamped = max(0, min(index, length))
        let boundaries = geometry.boundaries
        if clamped <= 0 { return geometry.minX }
        if clamped >= length { return geometry.maxX }
        if let exact = boundaries.first(where: { $0.index == clamped }) {
            return exact.x
        }
        for i in 0..<(boundaries.count - 1) {
            let lhs = boundaries[i]
            let rhs = boundaries[i + 1]
            if clamped > lhs.index && clamped < rhs.index {
                return preferTrailingEdge ? rhs.x : lhs.x
            }
        }
        return preferTrailingEdge ? geometry.maxX : geometry.minX
    }

    private func touchSharedLineMetricsCache(_ key: RunMetricsSignature) {
        sharedLineMetricsCacheOrder.removeAll { $0 == key }
        sharedLineMetricsCacheOrder.append(key)
    }

    private func storeSharedLineMetrics(_ metrics: MarkdownLineMetrics, for key: RunMetricsSignature) {
        sharedLineMetricsCache[key] = metrics
        touchSharedLineMetricsCache(key)
        while sharedLineMetricsCacheOrder.count > Self.maxCachedLineMetrics {
            let evicted = sharedLineMetricsCacheOrder.removeFirst()
            sharedLineMetricsCache.removeValue(forKey: evicted)
        }
    }

    private func touchLineMetricsCache(_ key: RunCacheKey) {
        lineMetricsCacheOrder.removeAll { $0 == key }
        lineMetricsCacheOrder.append(key)
    }

    private func storeLineMetrics(_ metrics: MarkdownLineMetrics, for key: RunCacheKey) {
        lineMetricsCache[key] = metrics
        touchLineMetricsCache(key)
        while lineMetricsCacheOrder.count > Self.maxCachedLineMetrics {
            let evicted = lineMetricsCacheOrder.removeFirst()
            lineMetricsCache.removeValue(forKey: evicted)
        }
    }

    private func blockIndex(containingY y: CGFloat) -> Int? {
        guard !layout.blocks.isEmpty else { return nil }
        var low = 0
        var high = layout.blocks.count - 1
        while low <= high {
            let mid = (low + high) / 2
            let frame = layout.blocks[mid].frame
            if y < frame.minY {
                high = mid - 1
            } else if y > frame.maxY {
                low = mid + 1
            } else {
                return mid
            }
        }
        return nil
    }

    private func nearestBlockIndexes(forY y: CGFloat) -> [Int] {
        guard !layout.blocks.isEmpty else { return [] }
        if let containing = blockIndex(containingY: y) {
            return [containing]
        }

        var low = 0
        var high = layout.blocks.count
        while low < high {
            let mid = (low + high) / 2
            if layout.blocks[mid].frame.minY <= y {
                low = mid + 1
            } else {
                high = mid
            }
        }

        let upper = min(layout.blocks.count - 1, low)
        let lower = max(0, low - 1)
        if upper == lower {
            return [lower]
        }
        return [lower, upper]
    }

    // MARK: - Font Resolution

    private func runFontVariant(_ run: LayoutTextRun) -> FontVariant {
        if run.style.isCode {
            return .monospace
        }
        if run.style.isBold && run.style.isItalic {
            return .boldItalic
        }
        if run.style.isBold {
            return .bold
        }
        if let override = run.style.fontVariant {
            if override == .semibold && run.style.isItalic {
                return .semiboldItalic
            }
            return override
        }
        if run.style.isItalic {
            return .italic
        }
        return .regular
    }

    private func runFont(for run: LayoutTextRun) -> CTFont? {
        let baseSize = layoutEngine.baseFontSize
        let runFontSize: CGFloat
        if let runLineHeight = run.lineHeight, runLineHeight > 0 {
            runFontSize = max(1, baseSize * (runLineHeight / max(1, layoutEngine.currentLineHeight)))
        } else {
            runFontSize = baseSize
        }
        guard let baseFont = layoutEngine.font(for: runFontVariant(run)) else { return nil }
        return CTFontCreateCopyWithAttributes(baseFont, runFontSize, nil, nil)
    }

    // MARK: - Character / X Mapping

    public func glyphIndexForX(_ run: LayoutTextRun, x: CGFloat) -> Int? {
        if let geometry = buildGlyphGeometry(for: run) {
            let boundaries = geometry.boundaries
            if x <= geometry.minX { return 0 }
            if x >= geometry.maxX { return runTextLength(run) }
            for i in 0..<(boundaries.count - 1) {
                let lhs = boundaries[i]
                let rhs = boundaries[i + 1]
                let midpoint = lhs.x + (rhs.x - lhs.x) * 0.5
                if x < midpoint {
                    return lhs.index
                }
                if x <= rhs.x {
                    return rhs.index
                }
            }
            return runTextLength(run)
        }
        guard let metrics = lineMetrics(for: run) else { return nil }
        let relativeX = x - metrics.originX
        var index = CTLineGetStringIndexForPosition(metrics.line, CGPoint(x: relativeX, y: 0))
        if index == kCFNotFound {
            index = relativeX <= 0 ? 0 : metrics.length
        }
        return max(0, min(index, metrics.length))
    }

    public func xForCharacterIndex(_ run: LayoutTextRun, index: Int, preferTrailingEdge: Bool) -> CGFloat? {
        let length = runTextLength(run)
        let clamped = max(0, min(index, length))
        if let geometry = buildGlyphGeometry(for: run) {
            let boundaries = geometry.boundaries
            if clamped <= 0 { return geometry.minX }
            if clamped >= length { return geometry.maxX }
            if let exact = boundaries.first(where: { $0.index == clamped }) {
                return exact.x
            }
            for i in 0..<(boundaries.count - 1) {
                let lhs = boundaries[i]
                let rhs = boundaries[i + 1]
                if clamped > lhs.index && clamped < rhs.index {
                    return preferTrailingEdge ? rhs.x : lhs.x
                }
            }
            return preferTrailingEdge ? geometry.maxX : geometry.minX
        }
        guard let metrics = lineMetrics(for: run) else { return nil }
        var secondary: CGFloat = 0
        let primary = CTLineGetOffsetForStringIndex(metrics.line, clamped, &secondary)
        let offset = preferTrailingEdge ? max(primary, secondary) : min(primary, secondary)
        return metrics.originX + offset
    }

    // MARK: - Run Bounds

    public func runHorizontalBounds(_ run: LayoutTextRun) -> (minX: CGFloat, maxX: CGFloat)? {
        if let geometry = buildGlyphGeometry(for: run) {
            return (geometry.minX, geometry.maxX)
        }
        let summary = buildRunBounds(for: run)
        return (summary.minX, summary.maxX)
    }

    public func runLineBounds(_ run: LayoutTextRun) -> CGRect? {
        let horizontal = runHorizontalBounds(run)

        let startX = horizontal?.0 ?? run.position.x
        let endX = horizontal?.1 ?? (run.position.x + 1)

        let summary = buildRunBounds(for: run)
        return CGRect(
            x: startX,
            y: summary.lineY,
            width: max(1, endX - startX),
            height: summary.lineHeight
        )
    }

    public func runVisualBounds(_ run: LayoutTextRun) -> CGRect? {
        if let horizontal = runHorizontalBounds(run) {
            let lineY = run.lineY ?? (run.position.y - max(1, run.lineHeight ?? layoutEngine.currentLineHeight) * 0.8)
            let lineHeight = run.lineHeight ?? max(layoutEngine.currentLineHeight, run.glyphs.first?.size.height ?? layoutEngine.currentLineHeight)
            return CGRect(x: horizontal.minX, y: lineY, width: max(1, horizontal.maxX - horizontal.minX), height: lineHeight)
        }
        return runLineBounds(run)
    }

    public func runRenderedBounds(_ run: LayoutTextRun) -> CGRect? {
        return runVisualBounds(run) ?? runLineBounds(run)
    }

    public func runHitBounds(_ run: LayoutTextRun) -> CGRect? {
        guard var rect = runSelectionBounds(run) ?? runLineBounds(run) ?? runVisualBounds(run) else { return nil }
        let padY = max(2, rect.height * 0.2)
        let padX = max(2, rect.height * 0.12)
        rect = rect.insetBy(dx: -padX, dy: -padY)
        return rect
    }

    public func runSelectionBounds(_ run: LayoutTextRun) -> CGRect? {
        let horizontal = runHorizontalBounds(run) ?? {
            if let rendered = runRenderedBounds(run) {
                return (rendered.minX, rendered.maxX)
            }
            return nil
        }()
        let startX = horizontal?.0 ?? run.position.x
        let endX = horizontal?.1 ?? (run.position.x + 1)
        let lineRect: CGRect?
        if let metrics = lineMetrics(for: run) {
            lineRect = CGRect(x: startX, y: metrics.lineY, width: max(1, endX - startX), height: metrics.lineHeight)
        } else if let lineY = run.lineY, let lineHeight = run.lineHeight, lineHeight > 0 {
            lineRect = CGRect(x: startX, y: lineY, width: max(1, endX - startX), height: lineHeight)
        } else {
            lineRect = nil
        }
        return lineRect
    }

    // MARK: - Link Hit Testing

    public func linkURL(at point: CGPoint) -> String? {
        guard let blockIndex = blockIndex(containingY: point.y) else { return nil }
        if let url = linkURL(in: layout.blocks[blockIndex], point: point) {
            return url
        }
        return nil
    }

    private func linkURL(in block: LayoutBlock, point: CGPoint) -> String? {
        switch block.content {
        case .text(let runs):
            return linkURL(in: runs, point: point)
        case .inline(let runs, let images):
            if let url = linkURL(in: runs, point: point) {
                return url
            }
            return linkURL(in: images, point: point)
        case .imageRow(let images):
            return linkURL(in: images, point: point)
        case .code:
            return nil
        case .diff:
            return nil
        case .listItems(let items):
            return linkURL(in: items, point: point)
        case .quoteBlocks(let blocks):
            for nested in blocks {
                if let url = linkURL(in: nested, point: point) {
                    return url
                }
            }
            return nil
        case .tableRows(let rows):
            for row in rows {
                for cell in row.cells {
                    if let url = linkURL(in: cell.textRuns, point: point) {
                        return url
                    }
                    if let url = linkURL(in: cell.inlineImages, point: point) {
                        return url
                    }
                }
            }
            return nil
        case .definitionList(let items):
            for item in items {
                if let url = linkURL(in: item.termRuns, point: point) {
                    return url
                }
                if let url = linkURL(in: item.termImages, point: point) {
                    return url
                }
                for (index, runs) in item.definitionRuns.enumerated() {
                    if let url = linkURL(in: runs, point: point) {
                        return url
                    }
                    if item.definitionImages.indices.contains(index),
                       let url = linkURL(in: item.definitionImages[index], point: point) {
                        return url
                    }
                }
            }
            return nil
        case .abbreviationList(let items):
            for item in items {
                if let url = linkURL(in: item.runs, point: point) {
                    return url
                }
                if let url = linkURL(in: item.images, point: point) {
                    return url
                }
            }
            return nil
        case .image, .thematicBreak, .math, .mermaid:
            return nil
        }
    }

    private func linkURL(in items: [LayoutListItem], point: CGPoint) -> String? {
        for item in items {
            if let url = linkURL(in: item.contentRuns, point: point) {
                return url
            }
            if let url = linkURL(in: item.inlineImages, point: point) {
                return url
            }
            if let url = linkURL(in: item.children, point: point) {
                return url
            }
        }
        return nil
    }

    private func linkURL(in images: [LayoutInlineImage], point: CGPoint) -> String? {
        for image in images {
            if let linkURL = image.linkURL, !linkURL.isEmpty, image.frame.contains(point) {
                return linkURL
            }
        }
        return nil
    }

    private func linkURL(in runs: [LayoutTextRun], point: CGPoint) -> String? {
        for run in runs {
            guard let url = run.style.linkURL, !url.isEmpty else { continue }
            let summary = buildRunBounds(for: run)
            let padY = max(2, summary.lineHeight * 0.2)
            let padX = max(2, summary.lineHeight * 0.12)
            let hitBounds = summary.rect.insetBy(dx: -padX, dy: -padY)
            guard hitBounds.contains(point) else { continue }
            return url
        }
        return nil
    }

    // MARK: - Hit Testing

    public func hitTest(at point: CGPoint) -> MarkdownTextPosition? {
        guard let blockIndex = blockIndex(containingY: point.y),
              let runs = textRuns(for: blockIndex) else {
            return nil
        }
        let block = layout.blocks[blockIndex]
        let allowHorizontalOutside: Bool
        if case .codeBlock = block.blockType {
            allowHorizontalOutside = true
        } else {
            allowHorizontalOutside = false
        }

        for (runIndex, run) in runs.enumerated() {
            let summary = runBounds(for: run, blockIndex: blockIndex, runIndex: runIndex)
            let hitRect = summary.rect.insetBy(dx: -6, dy: -4)
            guard point.y >= hitRect.minY && point.y <= hitRect.maxY else { continue }
            if !allowHorizontalOutside {
                guard point.x >= hitRect.minX && point.x <= hitRect.maxX else { continue }
            }

            let length = runTextLength(run)
            let clamped: Int
            if let geometry = glyphGeometry(for: run, blockIndex: blockIndex, runIndex: runIndex) {
                clamped = glyphIndexForX(point.x, geometry: geometry, length: length)
            } else if let glyphIndex = glyphIndexForX(run, x: point.x) {
                clamped = max(0, min(glyphIndex, length))
            } else {
                clamped = 0
            }
            return MarkdownTextPosition(
                blockIndex: blockIndex,
                runIndex: runIndex,
                characterOffset: clamped
            )
        }

        return nil
    }

    public func nearestTextPosition(to point: CGPoint) -> MarkdownTextPosition? {
        guard !layout.blocks.isEmpty else { return nil }
        if let first = findFirstPosition(),
           let last = findLastPosition() {
            let firstFrame = layout.blocks.first?.frame ?? .zero
            let lastFrame = layout.blocks.last?.frame ?? .zero
            if point.y <= firstFrame.minY { return first }
            if point.y >= lastFrame.maxY { return last }
        }

        var closestBlockIndex: Int?
        var closestBlockDistance = CGFloat.greatestFiniteMagnitude
        for index in nearestBlockIndexes(forY: point.y) {
            guard textRuns(for: index) != nil else { continue }
            let frame = layout.blocks[index].frame
            let distance: CGFloat
            if point.y < frame.minY {
                distance = frame.minY - point.y
            } else if point.y > frame.maxY {
                distance = point.y - frame.maxY
            } else {
                distance = 0
            }
            if distance < closestBlockDistance {
                closestBlockDistance = distance
                closestBlockIndex = index
            }
        }

        guard let blockIndex = closestBlockIndex else { return nil }
        guard let runs = textRuns(for: blockIndex), !runs.isEmpty else {
            return nil
        }

        var closestRunIndex = 0
        var closestRunScore = CGFloat.greatestFiniteMagnitude
        var closestRunRect: CGRect?
        for (runIndex, run) in runs.enumerated() {
            let summary = runBounds(for: run, blockIndex: blockIndex, runIndex: runIndex)
            let lineRect = summary.rect.insetBy(
                dx: -max(2, summary.lineHeight * 0.12),
                dy: -max(2, summary.lineHeight * 0.2)
            )

            let dx: CGFloat
            if point.x < lineRect.minX {
                dx = lineRect.minX - point.x
            } else if point.x > lineRect.maxX {
                dx = point.x - lineRect.maxX
            } else {
                dx = 0
            }

            let dy: CGFloat
            if point.y < lineRect.minY {
                dy = lineRect.minY - point.y
            } else if point.y > lineRect.maxY {
                dy = point.y - lineRect.maxY
            } else {
                dy = 0
            }

            let score = dx * dx + dy * dy
            if score < closestRunScore {
                closestRunScore = score
                closestRunIndex = runIndex
                closestRunRect = lineRect
                if score == 0 { break }
            }
        }

        let run = runs[closestRunIndex]
        let rect = closestRunRect ?? runBounds(for: run, blockIndex: blockIndex, runIndex: closestRunIndex).rect
        let clampedX = min(max(point.x, rect.minX), rect.maxX)
        let length = runTextLength(run)
        let geometry = glyphGeometry(for: run, blockIndex: blockIndex, runIndex: closestRunIndex)
        var clampedIndex = geometry.map { glyphIndexForX(clampedX, geometry: $0, length: length) } ?? glyphIndexForX(run, x: clampedX) ?? 0
        let edgeSnapTolerance = max(2, min(10, rect.width * 0.08))
        if clampedX >= rect.maxX - edgeSnapTolerance {
            clampedIndex = length
        } else if clampedX <= rect.minX + edgeSnapTolerance {
            clampedIndex = 0
        }
        let index = max(0, min(clampedIndex, length))
        return MarkdownTextPosition(
            blockIndex: blockIndex,
            runIndex: closestRunIndex,
            characterOffset: index
        )
    }

    // MARK: - First / Last Position

    public func findFirstPosition() -> MarkdownTextPosition? {
        if let cached = firstPositionCache {
            return cached
        }
        for (blockIndex, _) in layout.blocks.enumerated() {
            if let runs = textRuns(for: blockIndex), let firstRun = runs.first, !firstRun.glyphs.isEmpty {
                let position = MarkdownTextPosition(blockIndex: blockIndex, runIndex: 0, characterOffset: 0)
                firstPositionCache = position
                return position
            }
        }
        return nil
    }

    public func findLastPosition() -> MarkdownTextPosition? {
        if let cached = lastPositionCache {
            return cached
        }
        for (blockIndex, _) in layout.blocks.enumerated().reversed() {
            if let runs = textRuns(for: blockIndex), !runs.isEmpty {
                let lastRunIndex = runs.count - 1
                let lastRun = runs[lastRunIndex]
                let length = (lastRun.text as NSString).length
                if length > 0 || !lastRun.text.isEmpty {
                    let position = MarkdownTextPosition(
                        blockIndex: blockIndex,
                        runIndex: lastRunIndex,
                        characterOffset: length
                    )
                    lastPositionCache = position
                    return position
                }
            }
        }
        return nil
    }

    // MARK: - Text Extraction

    public func extractText(from start: MarkdownTextPosition, to end: MarkdownTextPosition) -> String {
        let (actualStart, actualEnd) = start < end ? (start, end) : (end, start)
        var selectedText = ""

        for (blockIndex, _) in layout.blocks.enumerated() {
            guard blockIndex >= actualStart.blockIndex && blockIndex <= actualEnd.blockIndex else { continue }
            guard let runs = textRuns(for: blockIndex) else { continue }

            for (runIndex, run) in runs.enumerated() {
                let isStartBlock = blockIndex == actualStart.blockIndex
                let isEndBlock = blockIndex == actualEnd.blockIndex
                let isStartRun = isStartBlock && runIndex == actualStart.runIndex
                let isEndRun = isEndBlock && runIndex == actualEnd.runIndex

                if isStartBlock && runIndex < actualStart.runIndex { continue }
                if isEndBlock && runIndex > actualEnd.runIndex { break }

                let length = runTextLength(run)
                let startIndex: Int = isStartRun ? min(actualStart.characterOffset, length) : 0
                let endIndex: Int = isEndRun ? min(actualEnd.characterOffset, length) : length

                if startIndex < endIndex {
                    let nsText = run.text as NSString
                    let range = NSRange(location: startIndex, length: endIndex - startIndex)
                    selectedText += nsText.substring(with: range)
                }
            }

            if blockIndex < actualEnd.blockIndex {
                selectedText += "\n"
            }
        }

        return selectedText
    }

    // MARK: - Selection Rects

    public func selectionRects(
        from start: MarkdownTextPosition,
        to end: MarkdownTextPosition,
        visibleYRange: ClosedRange<CGFloat>? = nil
    ) -> [CGRect] {
        let (actualStart, actualEnd) = start < end ? (start, end) : (end, start)
        var segments: [SelectionSegment] = []

        for (blockIndex, _) in layout.blocks.enumerated() {
            guard blockIndex >= actualStart.blockIndex && blockIndex <= actualEnd.blockIndex else { continue }
            if let visibleYRange {
                let blockFrame = layout.blocks[blockIndex].frame
                if blockFrame.maxY < visibleYRange.lowerBound || blockFrame.minY > visibleYRange.upperBound {
                    continue
                }
            }
            guard let runs = textRuns(for: blockIndex) else { continue }

            for (runIndex, run) in runs.enumerated() {
                let isStartBlock = blockIndex == actualStart.blockIndex
                let isEndBlock = blockIndex == actualEnd.blockIndex
                let isStartRun = isStartBlock && runIndex == actualStart.runIndex
                let isEndRun = isEndBlock && runIndex == actualEnd.runIndex

                if isStartBlock && runIndex < actualStart.runIndex { continue }
                if isEndBlock && runIndex > actualEnd.runIndex { break }

                let length = runTextLength(run)
                let geometry = glyphGeometry(for: run, blockIndex: blockIndex, runIndex: runIndex)
                if let visibleYRange {
                    let lineHeight = run.lineHeight ?? max(layoutEngine.currentLineHeight, run.glyphs.first?.size.height ?? layoutEngine.currentLineHeight)
                    let lineY = run.lineY ?? (run.position.y - lineHeight * 0.8)
                    if lineY + lineHeight < visibleYRange.lowerBound || lineY > visibleYRange.upperBound {
                        continue
                    }
                }
                let startIndex = isStartRun ? min(actualStart.characterOffset, length) : 0
                let endIndex = isEndRun ? min(actualEnd.characterOffset, length) : length

                if startIndex < endIndex {
                    let startXBase = geometry.map { xForCharacterIndex(startIndex, geometry: $0, length: length, preferTrailingEdge: false) }
                        ?? xForCharacterIndex(run, index: startIndex, preferTrailingEdge: false)
                        ?? run.position.x
                    let endXBase = geometry.map { xForCharacterIndex(endIndex, geometry: $0, length: length, preferTrailingEdge: true) }
                        ?? xForCharacterIndex(run, index: endIndex, preferTrailingEdge: true)
                        ?? (run.position.x + 1)
                    var startX = startXBase
                    var endX = endXBase

                    let atStartEdge = isStartRun && startIndex <= 1
                    let atEndEdge = isEndRun && endIndex >= max(0, length - 1)

                    let horizontal = geometry.map { ($0.minX, $0.maxX) } ?? runHorizontalBounds(run)
                    let minVisualX = horizontal?.minX ?? min(startX, endX)
                    let maxVisualX = horizontal?.maxX ?? max(startX, endX)

                    let lineRect = geometry.map { geometryLineRect(for: run, geometry: $0) } ?? runSelectionBounds(run)
                    let lineHeight = lineRect?.height ?? run.lineHeight ?? max(layoutEngine.currentLineHeight, run.glyphs.first?.size.height ?? layoutEngine.currentLineHeight)

                    if atStartEdge {
                        startX = min(startX, minVisualX) - min(0.7, lineHeight * 0.04)
                    }
                    if atEndEdge {
                        endX = max(endX, maxVisualX) + min(1.0, lineHeight * 0.05)
                    }

                    // Clamp overshoot so selection does not visibly exceed glyph bounds in non-edge cases.
                    let maxVisualOvershoot: CGFloat
                    if atStartEdge || atEndEdge {
                        maxVisualOvershoot = max(0.85, min(1.4, lineHeight * 0.06))
                    } else {
                        maxVisualOvershoot = max(0.35, min(0.7, lineHeight * 0.03))
                    }
                    startX = max(startX, minVisualX - maxVisualOvershoot)
                    endX = min(endX, maxVisualX + maxVisualOvershoot)

                    if endX < startX {
                        swap(&startX, &endX)
                    }
                    if endX <= startX {
                        if let cached = spaceWidthCache {
                            endX = startX + cached
                        } else {
                            let fontSize = layoutEngine.baseFontSize
                            let spaceFont = layoutEngine.font(for: .regular)
                            let spaceWidth: CGFloat
                            if let spaceFont {
                                let spaceStr = NSAttributedString(string: " ", attributes: [.font: spaceFont])
                                let spaceLine = CTLineCreateWithAttributedString(spaceStr)
                                spaceWidth = CGFloat(CTLineGetTypographicBounds(spaceLine, nil, nil, nil))
                            } else {
                                spaceWidth = fontSize * 0.5
                            }
                            spaceWidthCache = spaceWidth
                            endX = startX + spaceWidth
                        }
                    }

                    let selectionY = lineRect?.minY ?? run.lineY ?? (run.position.y - lineHeight * 0.8)
                    let selectionHeight = lineRect?.height ?? lineHeight
                    let lineKey = Int(round((selectionY + selectionHeight * 0.5) * 0.5))
                    segments.append(SelectionSegment(
                        lineKey: lineKey,
                        rect: CGRect(
                            x: startX,
                            y: selectionY,
                            width: max(0, endX - startX),
                            height: selectionHeight
                        )
                    ))
                }
            }
        }

        guard !segments.isEmpty else { return [] }

        var grouped: [SelectionSegment] = []
        let sortedSegments = segments.sorted { $0.rect.minY < $1.rect.minY }
        for segment in sortedSegments {
            if let index = grouped.firstIndex(where: {
                segment.lineKey == $0.lineKey &&
                segment.rect.maxY >= $0.rect.minY - 4 &&
                segment.rect.minY <= $0.rect.maxY + 4
            }) {
                let existing = grouped[index].rect
                let mergedRect = existing.union(segment.rect)
                grouped[index] = SelectionSegment(lineKey: grouped[index].lineKey, rect: mergedRect)
            } else {
                grouped.append(segment)
            }
        }

        let merged = grouped.map { $0.rect }
        return merged.sorted { $0.minY < $1.minY }
    }
}
