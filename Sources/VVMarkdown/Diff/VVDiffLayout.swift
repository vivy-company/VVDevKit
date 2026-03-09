import CoreGraphics
import CoreText
import Foundation

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

package struct VVDiffWrappedTextDescriptor: Hashable, Sendable {
    package let start: Int
    package let length: Int

    package var end: Int {
        start + length
    }
}

package struct VVDiffLayoutVisualLine: Sendable {
    package let rowIndex: Int
    package let rowID: Int
    package let y: CGFloat
    package let height: CGFloat
    package let isCodeRow: Bool
    package let textStart: Int
    package let textLength: Int
    package let codeStartX: CGFloat
    package let paneX: CGFloat
    package let paneWidth: CGFloat
}

package struct VVDiffLayoutMetrics: Sendable {
    package let lineHeight: CGFloat
    package let headerHeight: CGFloat
    package let gutterColWidth: CGFloat
    package let markerWidth: CGFloat
    package let codeStartX: CGFloat
    package let columnWidth: CGFloat
    package let totalWidth: CGFloat
}

package struct VVDiffLayoutBlock: Sendable {
    package enum Kind: Sendable {
        case unifiedFileHeader(sectionIndex: Int, rowIndex: Int?)
        case unifiedRow(rowIndex: Int, wrappedLines: [VVDiffWrappedTextDescriptor])
        case splitHeader(rowIndex: Int, isFileHeader: Bool, wrappedLines: [VVDiffWrappedTextDescriptor])
        case splitRow(
            splitRowIndex: Int,
            leftWrappedLines: [VVDiffWrappedTextDescriptor],
            rightWrappedLines: [VVDiffWrappedTextDescriptor]
        )
    }

    package let index: Int
    package let y: CGFloat
    package let height: CGFloat
    package let rowIDs: [Int]
    package let kind: Kind
}

package struct VVDiffLayoutPlan: Sendable {
    package let document: VVDiffDocument
    package let style: VVDiffRenderStyle
    package let width: CGFloat
    package let wrapLines: Bool
    package let metrics: VVDiffLayoutMetrics
    package let visualLines: [VVDiffLayoutVisualLine]
    package let blocks: [VVDiffLayoutBlock]
    package let contentHeight: CGFloat
}

package enum VVDiffLayoutBuilder {
    package static func makeLayout(
        document: VVDiffDocument,
        width: CGFloat,
        baseFont: VVFont,
        style: VVDiffRenderStyle,
        wrapLines: Bool,
        includesMetadata: Bool = false
    ) -> VVDiffLayoutPlan {
        let monoFont = VVFont.monospacedSystemFont(ofSize: baseFont.pointSize, weight: .regular)
        let lineHeight = ceil(monoFont.pointSize * 1.6)
        let headerHeight = max(20, lineHeight * 1.5)
        let charWidth = measureMonospaceCharWidth(font: monoFont)

        switch style {
        case .inline:
            let maxOld = document.maxOldLineNumber
            let maxNew = document.maxNewLineNumber
            let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
            let gutterColWidth = CGFloat(gutterDigits) * charWidth + 16
            let markerWidth = charWidth + 8
            let codeStartX = gutterColWidth * 2 + markerWidth
            let totalWidth = width
            let maxCharsPerVisualLine = wrapCapacity(
                totalWidth: width,
                codeStartX: codeStartX,
                codeInsetX: 10,
                charWidth: charWidth
            )
            let metrics = VVDiffLayoutMetrics(
                lineHeight: lineHeight,
                headerHeight: headerHeight,
                gutterColWidth: gutterColWidth,
                markerWidth: markerWidth,
                codeStartX: codeStartX,
                columnWidth: totalWidth,
                totalWidth: totalWidth
            )
            return makeUnifiedLayout(
                document: document,
                width: width,
                wrapLines: wrapLines,
                includesMetadata: includesMetadata,
                metrics: metrics,
                maxCharsPerVisualLine: maxCharsPerVisualLine
            )

        case .sideBySide:
            let maxOld = document.maxOldLineNumber
            let maxNew = document.maxNewLineNumber
            let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
            let gutterColWidth = CGFloat(gutterDigits) * charWidth + 16
            let markerWidth = charWidth + 4
            let columnWidth = max(420, floor(width / 2))
            let totalWidth = columnWidth * 2
            let codeStartX = markerWidth + gutterColWidth
            let paneMaxCharsPerVisualLine = wrapCapacity(
                totalWidth: columnWidth,
                codeStartX: codeStartX,
                codeInsetX: 10,
                charWidth: charWidth
            )
            let headerMaxCharsPerVisualLine = wrapCapacity(
                totalWidth: totalWidth,
                codeStartX: 12,
                codeInsetX: 0,
                charWidth: charWidth
            )
            let metrics = VVDiffLayoutMetrics(
                lineHeight: lineHeight,
                headerHeight: headerHeight,
                gutterColWidth: gutterColWidth,
                markerWidth: markerWidth,
                codeStartX: codeStartX,
                columnWidth: columnWidth,
                totalWidth: totalWidth
            )
            return makeSplitLayout(
                document: document,
                wrapLines: wrapLines,
                metrics: metrics,
                paneMaxCharsPerVisualLine: paneMaxCharsPerVisualLine,
                headerMaxCharsPerVisualLine: headerMaxCharsPerVisualLine
            )
        }
    }

    private static func makeUnifiedLayout(
        document: VVDiffDocument,
        width: CGFloat,
        wrapLines: Bool,
        includesMetadata: Bool,
        metrics: VVDiffLayoutMetrics,
        maxCharsPerVisualLine: Int
    ) -> VVDiffLayoutPlan {
        var visualLines: [VVDiffLayoutVisualLine] = []
        var blocks: [VVDiffLayoutBlock] = []
        visualLines.reserveCapacity(document.rows.count)
        blocks.reserveCapacity(document.rows.count)

        var y: CGFloat = 0
        var visualLineIndex = 0

        for (sectionIndex, section) in document.sections.enumerated() {
            if let header = section.headerRow {
                visualLines.append(
                    VVDiffLayoutVisualLine(
                        rowIndex: visualLineIndex,
                        rowID: header.id,
                        y: y,
                        height: metrics.headerHeight,
                        isCodeRow: false,
                        textStart: 0,
                        textLength: header.text.count,
                        codeStartX: metrics.codeStartX,
                        paneX: 0,
                        paneWidth: width
                    )
                )
                blocks.append(
                    VVDiffLayoutBlock(
                        index: blocks.count,
                        y: y,
                        height: metrics.headerHeight,
                        rowIDs: [header.id],
                        kind: .unifiedFileHeader(sectionIndex: sectionIndex, rowIndex: header.id)
                    )
                )
                y += metrics.headerHeight
                visualLineIndex += 1
            }

            for row in section.rows {
                if row.kind == .metadata && !includesMetadata {
                    continue
                }
                let displayText = VVDiffDisplayText(for: row)
                let wrappedLines = shouldWrapUnified(row: row, wrapLines: wrapLines)
                    ? wrappedTextDescriptors(displayText, maxChars: maxCharsPerVisualLine)
                    : [VVDiffWrappedTextDescriptor(start: 0, length: displayText.count)]
                let blockY = y
                let blockHeight = metrics.lineHeight * CGFloat(max(1, wrappedLines.count))

                for line in wrappedLines {
                    visualLines.append(
                        VVDiffLayoutVisualLine(
                            rowIndex: visualLineIndex,
                            rowID: row.id,
                            y: y,
                            height: metrics.lineHeight,
                            isCodeRow: row.kind.isCode,
                            textStart: line.start,
                            textLength: line.length,
                            codeStartX: metrics.codeStartX,
                            paneX: 0,
                            paneWidth: width
                        )
                    )
                    y += metrics.lineHeight
                    visualLineIndex += 1
                }

                blocks.append(
                    VVDiffLayoutBlock(
                        index: blocks.count,
                        y: blockY,
                        height: blockHeight,
                        rowIDs: [row.id],
                        kind: .unifiedRow(rowIndex: row.id, wrappedLines: wrappedLines)
                    )
                )
            }
        }

        return VVDiffLayoutPlan(
            document: document,
            style: .inline,
            width: width,
            wrapLines: wrapLines,
            metrics: metrics,
            visualLines: visualLines,
            blocks: blocks,
            contentHeight: y
        )
    }

    private static func makeSplitLayout(
        document: VVDiffDocument,
        wrapLines: Bool,
        metrics: VVDiffLayoutMetrics,
        paneMaxCharsPerVisualLine: Int,
        headerMaxCharsPerVisualLine: Int
    ) -> VVDiffLayoutPlan {
        var visualLines: [VVDiffLayoutVisualLine] = []
        var blocks: [VVDiffLayoutBlock] = []
        visualLines.reserveCapacity(max(document.rows.count, document.splitRows.count * 2))
        blocks.reserveCapacity(document.splitRows.count)

        var y: CGFloat = 0
        var visualLineIndex = 0

        for splitRow in document.splitRows {
            if let header = splitRow.header {
                let headerDisplayText = VVDiffDisplayText(for: header)
                let wrappedLines = wrapLines && header.kind == .hunkHeader
                    ? wrappedTextDescriptors(headerDisplayText, maxChars: headerMaxCharsPerVisualLine)
                    : [VVDiffWrappedTextDescriptor(start: 0, length: headerDisplayText.count)]
                let rowHeight = header.kind == .fileHeader
                    ? metrics.headerHeight
                    : metrics.lineHeight * CGFloat(max(1, wrappedLines.count))
                let blockY = y
                if header.kind == .fileHeader {
                    visualLines.append(
                        VVDiffLayoutVisualLine(
                            rowIndex: visualLineIndex,
                            rowID: header.id,
                            y: y,
                            height: rowHeight,
                            isCodeRow: false,
                            textStart: 0,
                            textLength: headerDisplayText.count,
                            codeStartX: metrics.codeStartX,
                            paneX: 0,
                            paneWidth: metrics.totalWidth
                        )
                    )
                    visualLineIndex += 1
                    y += rowHeight
                } else {
                    for line in wrappedLines {
                        visualLines.append(
                            VVDiffLayoutVisualLine(
                                rowIndex: visualLineIndex,
                                rowID: header.id,
                                y: y,
                                height: metrics.lineHeight,
                                isCodeRow: false,
                                textStart: line.start,
                                textLength: line.length,
                                codeStartX: metrics.codeStartX,
                                paneX: 0,
                                paneWidth: metrics.totalWidth
                            )
                        )
                        visualLineIndex += 1
                        y += metrics.lineHeight
                    }
                }

                blocks.append(
                    VVDiffLayoutBlock(
                        index: blocks.count,
                        y: blockY,
                        height: rowHeight,
                        rowIDs: [header.id],
                        kind: .splitHeader(
                            rowIndex: header.id,
                            isFileHeader: header.kind == .fileHeader,
                            wrappedLines: wrappedLines
                        )
                    )
                )
                continue
            }

            let leftWrappedLines = splitRow.left.map { cell in
                wrapLines && cell.kind.isCode
                    ? wrappedTextDescriptors(cell.text, maxChars: paneMaxCharsPerVisualLine)
                    : [VVDiffWrappedTextDescriptor(start: 0, length: cell.text.count)]
            } ?? []
            let rightWrappedLines = splitRow.right.map { cell in
                wrapLines && cell.kind.isCode
                    ? wrappedTextDescriptors(cell.text, maxChars: paneMaxCharsPerVisualLine)
                    : [VVDiffWrappedTextDescriptor(start: 0, length: cell.text.count)]
            } ?? []
            let visualLineCount = max(1, max(leftWrappedLines.count, rightWrappedLines.count))
            let rowHeight = metrics.lineHeight * CGFloat(visualLineCount)
            let blockY = y

            for lineIndex in 0..<visualLineCount {
                let lineY = y + CGFloat(lineIndex) * metrics.lineHeight
                if let left = splitRow.left {
                    let line = lineIndex < leftWrappedLines.count
                        ? leftWrappedLines[lineIndex]
                        : VVDiffWrappedTextDescriptor(start: 0, length: 0)
                    visualLines.append(
                        VVDiffLayoutVisualLine(
                            rowIndex: visualLineIndex,
                            rowID: left.rowID,
                            y: lineY,
                            height: metrics.lineHeight,
                            isCodeRow: lineIndex < leftWrappedLines.count ? left.kind.isCode : false,
                            textStart: line.start,
                            textLength: line.length,
                            codeStartX: metrics.codeStartX,
                            paneX: 0,
                            paneWidth: metrics.columnWidth
                        )
                    )
                    visualLineIndex += 1
                }
                if let right = splitRow.right {
                    let line = lineIndex < rightWrappedLines.count
                        ? rightWrappedLines[lineIndex]
                        : VVDiffWrappedTextDescriptor(start: 0, length: 0)
                    visualLines.append(
                        VVDiffLayoutVisualLine(
                            rowIndex: visualLineIndex,
                            rowID: right.rowID,
                            y: lineY,
                            height: metrics.lineHeight,
                            isCodeRow: lineIndex < rightWrappedLines.count ? right.kind.isCode : false,
                            textStart: line.start,
                            textLength: line.length,
                            codeStartX: metrics.codeStartX,
                            paneX: metrics.columnWidth,
                            paneWidth: metrics.columnWidth
                        )
                    )
                    visualLineIndex += 1
                }
            }

            var rowIDs: [Int] = []
            rowIDs.reserveCapacity(2)
            if let left = splitRow.left {
                rowIDs.append(left.rowID)
            }
            if let right = splitRow.right {
                rowIDs.append(right.rowID)
            }

            blocks.append(
                VVDiffLayoutBlock(
                    index: blocks.count,
                    y: blockY,
                    height: rowHeight,
                    rowIDs: rowIDs,
                    kind: .splitRow(
                        splitRowIndex: splitRow.id,
                        leftWrappedLines: leftWrappedLines,
                        rightWrappedLines: rightWrappedLines
                    )
                )
            )
            y += rowHeight
        }

        return VVDiffLayoutPlan(
            document: document,
            style: .sideBySide,
            width: metrics.totalWidth,
            wrapLines: wrapLines,
            metrics: metrics,
            visualLines: visualLines,
            blocks: blocks,
            contentHeight: y
        )
    }

    private static func shouldWrapUnified(row: VVDiffRow, wrapLines: Bool) -> Bool {
        wrapLines && (row.kind.isCode || row.kind == .hunkHeader)
    }

    private static func measureMonospaceCharWidth(font: VVFont) -> CGFloat {
        let ctFont = font as CTFont
        var glyphID: CGGlyph = 0
        var character: UniChar = 0x0038 // '8'
        CTFontGetGlyphsForCharacters(ctFont, &character, &glyphID, 1)
        var advance = CGSize.zero
        CTFontGetAdvancesForGlyphs(ctFont, .horizontal, &glyphID, &advance, 1)
        return advance.width > 0 ? advance.width : font.pointSize * 0.6
    }

    private static func wrapCapacity(
        totalWidth: CGFloat,
        codeStartX: CGFloat,
        codeInsetX: CGFloat,
        charWidth: CGFloat
    ) -> Int {
        let available = max(0, totalWidth - codeStartX - codeInsetX - 12)
        guard available > 0 else { return 1 }
        return max(1, Int(floor(available / max(charWidth, 1))))
    }

    private static func wrappedTextDescriptors(_ text: String, maxChars: Int) -> [VVDiffWrappedTextDescriptor] {
        guard maxChars > 0 else { return [VVDiffWrappedTextDescriptor(start: 0, length: text.count)] }

        var result: [VVDiffWrappedTextDescriptor] = []
        let logicalLines = text.split(separator: "\n", omittingEmptySubsequences: false)
        var absoluteOffset = 0

        for (lineIndex, line) in logicalLines.enumerated() {
            let lineLength = line.count
            if lineLength == 0 {
                result.append(VVDiffWrappedTextDescriptor(start: absoluteOffset, length: 0))
            } else {
                var localOffset = 0
                var remaining = lineLength
                while remaining > 0 {
                    let segmentLength = min(maxChars, remaining)
                    result.append(
                        VVDiffWrappedTextDescriptor(
                            start: absoluteOffset + localOffset,
                            length: segmentLength
                        )
                    )
                    localOffset += segmentLength
                    remaining -= segmentLength
                }
            }

            absoluteOffset += lineLength
            if lineIndex < logicalLines.count - 1 {
                absoluteOffset += 1
            }
        }

        return result.isEmpty ? [VVDiffWrappedTextDescriptor(start: 0, length: 0)] : result
    }
}
