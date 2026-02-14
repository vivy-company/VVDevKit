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

// MARK: - VVMarkdownSelectionHelper

/// Extracts CTLine-based selection logic shared between VVMarkdownView and VVChatTimelineView.
/// Does not depend on any renderer or GlyphAtlas — uses CoreText metrics exclusively.
public final class VVMarkdownSelectionHelper {
    public let layout: MarkdownLayout
    public let layoutEngine: MarkdownLayoutEngine

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
            return MarkdownLineMetrics(line: line, length: length, originX: run.position.x, lineY: runLineY, lineHeight: runLineHeight, baseline: baseline, ascent: ascent, descent: descent, lineWidth: lineWidth)
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
        return MarkdownLineMetrics(line: line, length: length, originX: run.position.x, lineY: lineY, lineHeight: lineHeight, baseline: baseline, ascent: ascent, descent: descent, lineWidth: lineWidth)
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
        guard let metrics = lineMetrics(for: run) else { return nil }
        let offset = CTLineGetOffsetForStringIndex(metrics.line, clamped, nil)
        return metrics.originX + offset
    }

    // MARK: - Run Bounds

    public func runHorizontalBounds(_ run: LayoutTextRun) -> (minX: CGFloat, maxX: CGFloat)? {
        guard let metrics = lineMetrics(for: run) else { return nil }
        let bounds = CTLineGetBoundsWithOptions(metrics.line, [.useGlyphPathBounds, .useOpticalBounds])
        let minX = metrics.originX + bounds.origin.x
        let maxX = minX + bounds.width
        return (minX, maxX)
    }

    public func runLineBounds(_ run: LayoutTextRun) -> CGRect? {
        let horizontal = runHorizontalBounds(run) ?? {
            if let rendered = runRenderedBounds(run) {
                return (rendered.minX, rendered.maxX)
            }
            return nil
        }()

        let startX = horizontal?.0 ?? run.position.x
        let endX = horizontal?.1 ?? (run.position.x + 1)

        if let lineY = run.lineY,
           let lineHeight = run.lineHeight,
           lineHeight > 0 {
            return CGRect(
                x: startX,
                y: lineY,
                width: max(1, endX - startX),
                height: lineHeight
            )
        }

        if let metrics = lineMetrics(for: run) {
            return CGRect(
                x: startX,
                y: metrics.lineY,
                width: max(1, endX - startX),
                height: metrics.lineHeight
            )
        }

        if let rendered = runRenderedBounds(run) {
            return CGRect(x: rendered.minX, y: rendered.minY, width: rendered.width, height: rendered.height)
        }
        return nil
    }

    public func runVisualBounds(_ run: LayoutTextRun) -> CGRect? {
        guard let metrics = lineMetrics(for: run) else { return runLineBounds(run) }
        let bounds = CTLineGetBoundsWithOptions(metrics.line, [.useGlyphPathBounds, .useOpticalBounds])
        let rect = CGRect(
            x: metrics.originX + bounds.origin.x,
            y: metrics.baseline + bounds.origin.y,
            width: bounds.width,
            height: bounds.height
        )
        if rect.width > 0 && rect.height > 0 {
            return rect
        }
        return runLineBounds(run)
    }

    public func runRenderedBounds(_ run: LayoutTextRun) -> CGRect? {
        return runLineBounds(run) ?? runVisualBounds(run)
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

    // MARK: - Hit Testing

    public func hitTest(at point: CGPoint) -> MarkdownTextPosition? {
        for (blockIndex, block) in layout.blocks.enumerated() {
            guard let runs = getTextRuns(from: block) else { continue }
            let allowHorizontalOutside: Bool
            if case .codeBlock = block.blockType {
                allowHorizontalOutside = true
            } else {
                allowHorizontalOutside = false
            }

            for (runIndex, run) in runs.enumerated() {
                guard let metrics = lineMetrics(for: run) else { continue }
                guard let lineRect = runHitBounds(run) else { continue }
                let hitRect = lineRect.insetBy(dx: -4, dy: -4)
                guard point.y >= hitRect.minY && point.y <= hitRect.maxY else { continue }
                if !allowHorizontalOutside {
                    guard point.x >= hitRect.minX && point.x <= hitRect.maxX else { continue }
                }

                let clamped: Int
                if let glyphIndex = glyphIndexForX(run, x: point.x) {
                    clamped = max(0, min(glyphIndex, metrics.length))
                } else {
                    let relativeX = point.x - metrics.originX
                    var index = CTLineGetStringIndexForPosition(metrics.line, CGPoint(x: relativeX, y: 0))
                    if index == kCFNotFound {
                        index = relativeX <= 0 ? 0 : metrics.length
                    }
                    clamped = max(0, min(index, metrics.length))
                }
                return MarkdownTextPosition(
                    blockIndex: blockIndex,
                    runIndex: runIndex,
                    characterOffset: clamped
                )
            }
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
        for (index, block) in layout.blocks.enumerated() {
            guard getTextRuns(from: block) != nil else { continue }
            let frame = block.frame
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
                if distance == 0 { break }
            }
        }

        guard let blockIndex = closestBlockIndex else { return nil }
        guard let runs = getTextRuns(from: layout.blocks[blockIndex]), !runs.isEmpty else {
            return nil
        }

        var closestRunIndex = 0
        var closestRunDistance = CGFloat.greatestFiniteMagnitude
        var closestRunRect: CGRect?
        for (runIndex, run) in runs.enumerated() {
            guard let lineRect = runHitBounds(run) ?? runLineBounds(run) ?? runSelectionBounds(run) else { continue }
            let distance = abs(point.y - lineRect.midY)
            if distance < closestRunDistance {
                closestRunDistance = distance
                closestRunIndex = runIndex
                closestRunRect = lineRect
                if distance == 0 { break }
            }
        }

        let run = runs[closestRunIndex]
        let rect = closestRunRect ?? runHitBounds(run) ?? runLineBounds(run) ?? CGRect(x: run.position.x, y: run.position.y, width: 1, height: 1)
        let clampedX = min(max(point.x, rect.minX), rect.maxX)
        let clampedIndex = glyphIndexForX(run, x: clampedX) ?? 0
        let length = runTextLength(run)
        let index = max(0, min(clampedIndex, length))
        return MarkdownTextPosition(
            blockIndex: blockIndex,
            runIndex: closestRunIndex,
            characterOffset: index
        )
    }

    // MARK: - First / Last Position

    public func findFirstPosition() -> MarkdownTextPosition? {
        for (blockIndex, block) in layout.blocks.enumerated() {
            if let runs = getTextRuns(from: block), let firstRun = runs.first, !firstRun.glyphs.isEmpty {
                return MarkdownTextPosition(blockIndex: blockIndex, runIndex: 0, characterOffset: 0)
            }
        }
        return nil
    }

    public func findLastPosition() -> MarkdownTextPosition? {
        for (blockIndex, block) in layout.blocks.enumerated().reversed() {
            if let runs = getTextRuns(from: block), !runs.isEmpty {
                let lastRunIndex = runs.count - 1
                let lastRun = runs[lastRunIndex]
                let length = (lastRun.text as NSString).length
                if length > 0 || !lastRun.text.isEmpty {
                    return MarkdownTextPosition(
                        blockIndex: blockIndex,
                        runIndex: lastRunIndex,
                        characterOffset: length
                    )
                }
            }
        }
        return nil
    }

    // MARK: - Text Extraction

    public func extractText(from start: MarkdownTextPosition, to end: MarkdownTextPosition) -> String {
        let (actualStart, actualEnd) = start < end ? (start, end) : (end, start)
        var selectedText = ""

        for (blockIndex, block) in layout.blocks.enumerated() {
            guard blockIndex >= actualStart.blockIndex && blockIndex <= actualEnd.blockIndex else { continue }
            guard let runs = getTextRuns(from: block) else { continue }

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

    public func selectionRects(from start: MarkdownTextPosition, to end: MarkdownTextPosition) -> [CGRect] {
        let (actualStart, actualEnd) = start < end ? (start, end) : (end, start)
        var segments: [SelectionSegment] = []

        for (blockIndex, block) in layout.blocks.enumerated() {
            guard blockIndex >= actualStart.blockIndex && blockIndex <= actualEnd.blockIndex else { continue }
            guard let runs = getTextRuns(from: block) else { continue }

            for (runIndex, run) in runs.enumerated() {
                let isStartBlock = blockIndex == actualStart.blockIndex
                let isEndBlock = blockIndex == actualEnd.blockIndex
                let isStartRun = isStartBlock && runIndex == actualStart.runIndex
                let isEndRun = isEndBlock && runIndex == actualEnd.runIndex

                if isStartBlock && runIndex < actualStart.runIndex { continue }
                if isEndBlock && runIndex > actualEnd.runIndex { break }

                guard let metrics = lineMetrics(for: run) else { continue }
                let length = metrics.length
                let startIndex = isStartRun ? min(actualStart.characterOffset, length) : 0
                let endIndex = isEndRun ? min(actualEnd.characterOffset, length) : length

                if startIndex < endIndex {
                    let startOffset = CTLineGetOffsetForStringIndex(metrics.line, startIndex, nil)
                    let endOffset = CTLineGetOffsetForStringIndex(metrics.line, endIndex, nil)
                    var startX = metrics.originX + startOffset
                    var endX = metrics.originX + endOffset

                    if let glyphStartX = xForCharacterIndex(run, index: startIndex, preferTrailingEdge: false) {
                        startX = glyphStartX
                    }
                    if let glyphEndX = xForCharacterIndex(run, index: endIndex, preferTrailingEdge: true) {
                        endX = glyphEndX
                    }
                    if endX < startX {
                        swap(&startX, &endX)
                    }
                    if endX <= startX {
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
                        endX = startX + spaceWidth
                    }

                    let lineRect = runSelectionBounds(run)
                    let selectionY = lineRect?.minY ?? metrics.lineY
                    let selectionHeight = lineRect?.height ?? metrics.lineHeight
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
                segment.rect.maxY >= $0.rect.minY - 4 && segment.rect.minY <= $0.rect.maxY + 4
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
