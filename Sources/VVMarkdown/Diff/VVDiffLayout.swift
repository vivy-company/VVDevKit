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
    package let charWidth: CGFloat
    package let gutterColWidth: CGFloat
    package let markerWidth: CGFloat
    package let codeStartX: CGFloat
    package let columnWidth: CGFloat
    package let totalWidth: CGFloat
}

package struct VVDiffLayoutBlock: Sendable {
    package enum Kind: Sendable {
        case unifiedFileHeader(sectionIndex: Int, rowID: Int?)
        case unifiedRow(rowIndex: Int)
        case splitHeader(rowIndex: Int, isFileHeader: Bool)
        case splitRow(splitRowIndex: Int)
    }

    package let index: Int
    package let y: CGFloat
    package let height: CGFloat
    package let visualLineStartIndex: Int
    package let visualLineCount: Int
    package let rowIDs: [Int]
    package let kind: Kind

    package var visualLineRange: Range<Int> {
        visualLineStartIndex..<(visualLineStartIndex + visualLineCount)
    }
}

package struct VVDiffLayoutPlan: Sendable {
    package let document: VVDiffDocument
    package let style: VVDiffRenderStyle
    package let width: CGFloat
    package let wrapLines: Bool
    package let metrics: VVDiffLayoutMetrics
    package let totalVisualLineCount: Int
    package let blocks: [VVDiffLayoutBlock]
    package let contentHeight: CGFloat
}

package enum VVDiffLayoutMaterializedBlock: Sendable {
    case unifiedFileHeader(sectionIndex: Int, rowID: Int?)
    case unifiedRow(rowIndex: Int, wrappedLines: [VVDiffWrappedTextDescriptor])
    case splitHeader(rowIndex: Int, isFileHeader: Bool, wrappedLines: [VVDiffWrappedTextDescriptor])
    case splitRow(
        splitRowIndex: Int,
        leftWrappedLines: [VVDiffWrappedTextDescriptor],
        rightWrappedLines: [VVDiffWrappedTextDescriptor]
    )
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
                charWidth: charWidth,
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
                charWidth: charWidth,
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
        var blocks: [VVDiffLayoutBlock] = []
        blocks.reserveCapacity(document.rows.count)
        let rowIndexByID = Dictionary(uniqueKeysWithValues: document.rows.enumerated().map { ($0.element.id, $0.offset) })

        var y: CGFloat = 0
        var visualLineIndex = 0

        for (sectionIndex, section) in document.sections.enumerated() {
            if let header = section.headerRow {
                blocks.append(
                    VVDiffLayoutBlock(
                        index: blocks.count,
                        y: y,
                        height: metrics.headerHeight,
                        visualLineStartIndex: visualLineIndex,
                        visualLineCount: 1,
                        rowIDs: [header.id],
                        kind: .unifiedFileHeader(sectionIndex: sectionIndex, rowID: header.id)
                    )
                )
                y += metrics.headerHeight
                visualLineIndex += 1
            }

            for row in section.rows {
                if row.kind == .metadata && !includesMetadata {
                    continue
                }
                let wrappedLineCount = wrappedTextDescriptorCount(
                    unifiedRow: row,
                    wrapLines: wrapLines,
                    maxChars: maxCharsPerVisualLine
                )
                let blockY = y
                let blockHeight = metrics.lineHeight * CGFloat(wrappedLineCount)
                guard let rowIndex = rowIndexByID[row.id] else { continue }

                blocks.append(
                    VVDiffLayoutBlock(
                        index: blocks.count,
                        y: blockY,
                        height: blockHeight,
                        visualLineStartIndex: visualLineIndex,
                        visualLineCount: wrappedLineCount,
                        rowIDs: [row.id],
                        kind: .unifiedRow(rowIndex: rowIndex)
                    )
                )
                y += blockHeight
                visualLineIndex += wrappedLineCount
            }
        }

        return VVDiffLayoutPlan(
            document: document,
            style: .inline,
            width: width,
            wrapLines: wrapLines,
            metrics: metrics,
            totalVisualLineCount: visualLineIndex,
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
        var blocks: [VVDiffLayoutBlock] = []
        blocks.reserveCapacity(document.splitRows.count)
        let rowIndexByID = Dictionary(uniqueKeysWithValues: document.rows.enumerated().map { ($0.element.id, $0.offset) })

        var y: CGFloat = 0
        var visualLineIndex = 0

        for (splitRowIndex, splitRow) in document.splitRows.enumerated() {
            if let header = splitRow.header {
                let wrappedLineCount = wrappedTextDescriptorCount(
                    headerRow: header,
                    wrapLines: wrapLines,
                    maxChars: headerMaxCharsPerVisualLine
                )
                let rowHeight = header.kind == .fileHeader
                    ? metrics.headerHeight
                    : metrics.lineHeight * CGFloat(wrappedLineCount)
                let blockY = y
                guard let headerRowIndex = rowIndexByID[header.id] else { continue }

                blocks.append(
                    VVDiffLayoutBlock(
                        index: blocks.count,
                        y: blockY,
                        height: rowHeight,
                        visualLineStartIndex: visualLineIndex,
                        visualLineCount: header.kind == .fileHeader ? 1 : wrappedLineCount,
                        rowIDs: [header.id],
                        kind: .splitHeader(
                            rowIndex: headerRowIndex,
                            isFileHeader: header.kind == .fileHeader
                        )
                    )
                )
                y += rowHeight
                visualLineIndex += header.kind == .fileHeader ? 1 : wrappedLineCount
                continue
            }

            let leftWrappedLineCount = splitRow.left.map {
                wrappedTextDescriptorCount(splitCell: $0, wrapLines: wrapLines, maxChars: paneMaxCharsPerVisualLine)
            } ?? 0
            let rightWrappedLineCount = splitRow.right.map {
                wrappedTextDescriptorCount(splitCell: $0, wrapLines: wrapLines, maxChars: paneMaxCharsPerVisualLine)
            } ?? 0
            let logicalVisualLineCount = max(1, max(leftWrappedLineCount, rightWrappedLineCount))
            let paneCount = (splitRow.left != nil ? 1 : 0) + (splitRow.right != nil ? 1 : 0)
            let blockVisualLineCount = max(1, logicalVisualLineCount * max(1, paneCount))
            let rowHeight = metrics.lineHeight * CGFloat(logicalVisualLineCount)
            let blockY = y

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
                    visualLineStartIndex: visualLineIndex,
                    visualLineCount: blockVisualLineCount,
                    rowIDs: rowIDs,
                    kind: .splitRow(splitRowIndex: splitRowIndex)
                )
            )
            y += rowHeight
            visualLineIndex += blockVisualLineCount
        }

        return VVDiffLayoutPlan(
            document: document,
            style: .sideBySide,
            width: metrics.totalWidth,
            wrapLines: wrapLines,
            metrics: metrics,
            totalVisualLineCount: visualLineIndex,
            blocks: blocks,
            contentHeight: y
        )
    }

    package static func materializedBlock(
        _ block: VVDiffLayoutBlock,
        in layout: VVDiffLayoutPlan
    ) -> VVDiffLayoutMaterializedBlock? {
        let rows = layout.document.rows
        let splitRows = layout.document.splitRows
        switch block.kind {
        case let .unifiedFileHeader(sectionIndex, rowID):
            return .unifiedFileHeader(sectionIndex: sectionIndex, rowID: rowID)

        case let .unifiedRow(rowIndex):
            guard rows.indices.contains(rowIndex) else { return nil }
            let row = rows[rowIndex]
            let wrappedLines = wrappedDescriptors(
                for: row,
                wrapLines: layout.wrapLines,
                maxChars: wrapCapacity(
                    totalWidth: layout.metrics.totalWidth,
                    codeStartX: layout.metrics.codeStartX,
                    codeInsetX: 10,
                    charWidth: layout.metrics.charWidth
                )
            )
            return .unifiedRow(rowIndex: rowIndex, wrappedLines: wrappedLines)

        case let .splitHeader(rowIndex, isFileHeader):
            guard rows.indices.contains(rowIndex) else { return nil }
            let row = rows[rowIndex]
            let wrappedLines: [VVDiffWrappedTextDescriptor]
            if isFileHeader {
                wrappedLines = [VVDiffWrappedTextDescriptor(start: 0, length: row.text.count)]
            } else {
                wrappedLines = wrappedDescriptors(
                    forHeader: row,
                    wrapLines: layout.wrapLines,
                    maxChars: wrapCapacity(
                        totalWidth: layout.metrics.totalWidth,
                        codeStartX: 12,
                        codeInsetX: 0,
                        charWidth: layout.metrics.charWidth
                    )
                )
            }
            return .splitHeader(rowIndex: rowIndex, isFileHeader: isFileHeader, wrappedLines: wrappedLines)

        case let .splitRow(splitRowIndex):
            guard splitRows.indices.contains(splitRowIndex) else { return nil }
            let splitRow = splitRows[splitRowIndex]
            let paneMaxChars = wrapCapacity(
                totalWidth: layout.metrics.columnWidth,
                codeStartX: layout.metrics.codeStartX,
                codeInsetX: 10,
                charWidth: layout.metrics.charWidth
            )
            let leftWrappedLines = splitRow.left.map {
                wrappedDescriptors(forSplitCell: $0, wrapLines: layout.wrapLines, maxChars: paneMaxChars)
            } ?? []
            let rightWrappedLines = splitRow.right.map {
                wrappedDescriptors(forSplitCell: $0, wrapLines: layout.wrapLines, maxChars: paneMaxChars)
            } ?? []
            return .splitRow(
                splitRowIndex: splitRowIndex,
                leftWrappedLines: leftWrappedLines,
                rightWrappedLines: rightWrappedLines
            )
        }
    }

    package static func materializeVisualLines(
        in layout: VVDiffLayoutPlan,
        blockRange: Range<Int>
    ) -> [VVDiffLayoutVisualLine] {
        guard !layout.blocks.isEmpty else { return [] }
        let clampedRange = max(0, blockRange.lowerBound)..<min(layout.blocks.count, blockRange.upperBound)
        guard clampedRange.lowerBound < clampedRange.upperBound else { return [] }

        let estimatedCount = layout.blocks[clampedRange].reduce(into: 0) { partialResult, block in
            partialResult += block.visualLineCount
        }
        var visualLines: [VVDiffLayoutVisualLine] = []
        visualLines.reserveCapacity(estimatedCount)

        for block in layout.blocks[clampedRange] {
            guard let materialized = materializedBlock(block, in: layout) else { continue }
            switch materialized {
            case let .unifiedFileHeader(_, rowID):
                visualLines.append(
                    VVDiffLayoutVisualLine(
                        rowIndex: block.visualLineStartIndex,
                        rowID: rowID ?? -1,
                        y: block.y,
                        height: block.height,
                        isCodeRow: false,
                        textStart: 0,
                        textLength: 0,
                        codeStartX: layout.metrics.codeStartX,
                        paneX: 0,
                        paneWidth: layout.metrics.totalWidth
                    )
                )

            case let .unifiedRow(rowIndex, wrappedLines):
                guard layout.document.rows.indices.contains(rowIndex) else { continue }
                let row = layout.document.rows[rowIndex]
                for (lineOffset, descriptor) in wrappedLines.enumerated() {
                    visualLines.append(
                        VVDiffLayoutVisualLine(
                            rowIndex: block.visualLineStartIndex + lineOffset,
                            rowID: row.id,
                            y: block.y + CGFloat(lineOffset) * layout.metrics.lineHeight,
                            height: layout.metrics.lineHeight,
                            isCodeRow: row.kind.isCode,
                            textStart: descriptor.start,
                            textLength: descriptor.length,
                            codeStartX: layout.metrics.codeStartX,
                            paneX: 0,
                            paneWidth: layout.metrics.totalWidth
                        )
                    )
                }

            case let .splitHeader(rowIndex, isFileHeader, wrappedLines):
                guard layout.document.rows.indices.contains(rowIndex) else { continue }
                let row = layout.document.rows[rowIndex]
                if isFileHeader {
                    visualLines.append(
                        VVDiffLayoutVisualLine(
                            rowIndex: block.visualLineStartIndex,
                            rowID: row.id,
                            y: block.y,
                            height: block.height,
                            isCodeRow: false,
                            textStart: 0,
                            textLength: row.text.count,
                            codeStartX: layout.metrics.codeStartX,
                            paneX: 0,
                            paneWidth: layout.metrics.totalWidth
                        )
                    )
                } else {
                    for (lineOffset, descriptor) in wrappedLines.enumerated() {
                        visualLines.append(
                            VVDiffLayoutVisualLine(
                                rowIndex: block.visualLineStartIndex + lineOffset,
                                rowID: row.id,
                                y: block.y + CGFloat(lineOffset) * layout.metrics.lineHeight,
                                height: layout.metrics.lineHeight,
                                isCodeRow: false,
                                textStart: descriptor.start,
                                textLength: descriptor.length,
                                codeStartX: layout.metrics.codeStartX,
                                paneX: 0,
                                paneWidth: layout.metrics.totalWidth
                            )
                        )
                    }
                }

            case let .splitRow(splitRowIndex, leftWrappedLines, rightWrappedLines):
                guard layout.document.splitRows.indices.contains(splitRowIndex) else { continue }
                let splitRow = layout.document.splitRows[splitRowIndex]
                let logicalVisualLineCount = max(1, max(leftWrappedLines.count, rightWrappedLines.count))
                var visualLineIndex = block.visualLineStartIndex
                for lineOffset in 0..<logicalVisualLineCount {
                    let lineY = block.y + CGFloat(lineOffset) * layout.metrics.lineHeight
                    if let left = splitRow.left {
                        let descriptor = lineOffset < leftWrappedLines.count
                            ? leftWrappedLines[lineOffset]
                            : VVDiffWrappedTextDescriptor(start: 0, length: 0)
                        visualLines.append(
                            VVDiffLayoutVisualLine(
                                rowIndex: visualLineIndex,
                                rowID: left.rowID,
                                y: lineY,
                                height: layout.metrics.lineHeight,
                                isCodeRow: lineOffset < leftWrappedLines.count ? left.kind.isCode : false,
                                textStart: descriptor.start,
                                textLength: descriptor.length,
                                codeStartX: layout.metrics.codeStartX,
                                paneX: 0,
                                paneWidth: layout.metrics.columnWidth
                            )
                        )
                        visualLineIndex += 1
                    }
                    if let right = splitRow.right {
                        let descriptor = lineOffset < rightWrappedLines.count
                            ? rightWrappedLines[lineOffset]
                            : VVDiffWrappedTextDescriptor(start: 0, length: 0)
                        visualLines.append(
                            VVDiffLayoutVisualLine(
                                rowIndex: visualLineIndex,
                                rowID: right.rowID,
                                y: lineY,
                                height: layout.metrics.lineHeight,
                                isCodeRow: lineOffset < rightWrappedLines.count ? right.kind.isCode : false,
                                textStart: descriptor.start,
                                textLength: descriptor.length,
                                codeStartX: layout.metrics.codeStartX,
                                paneX: layout.metrics.columnWidth,
                                paneWidth: layout.metrics.columnWidth
                            )
                        )
                        visualLineIndex += 1
                    }
                }
            }
        }

        return visualLines
    }

    package static func materializeVisualLines(
        in layout: VVDiffLayoutPlan,
        visualLineRange: Range<Int>
    ) -> [VVDiffLayoutVisualLine] {
        guard visualLineRange.lowerBound < visualLineRange.upperBound else { return [] }
        let blockRange = blockRange(in: layout, forVisualLineRange: visualLineRange)
        guard blockRange.lowerBound < blockRange.upperBound else { return [] }
        let visualLines = materializeVisualLines(in: layout, blockRange: blockRange)
        return visualLines.filter { visualLineRange.contains($0.rowIndex) }
    }

    package static func blockRange(
        in layout: VVDiffLayoutPlan,
        forVisualLineRange visualLineRange: Range<Int>
    ) -> Range<Int> {
        guard !layout.blocks.isEmpty, visualLineRange.lowerBound < visualLineRange.upperBound else {
            return 0..<0
        }
        let startIndex = firstBlockIndex(in: layout, containingVisualLineAtOrAfter: visualLineRange.lowerBound)
        var endIndex = startIndex
        while endIndex < layout.blocks.count {
            let block = layout.blocks[endIndex]
            if block.visualLineStartIndex >= visualLineRange.upperBound {
                break
            }
            endIndex += 1
        }
        return startIndex..<endIndex
    }

    private static func firstBlockIndex(
        in layout: VVDiffLayoutPlan,
        containingVisualLineAtOrAfter rowIndex: Int
    ) -> Int {
        var low = 0
        var high = layout.blocks.count

        while low < high {
            let mid = (low + high) / 2
            let block = layout.blocks[mid]
            if block.visualLineStartIndex + block.visualLineCount <= rowIndex {
                low = mid + 1
            } else {
                high = mid
            }
        }

        return min(low, layout.blocks.count)
    }

    private static func shouldWrapUnified(row: VVDiffRow, wrapLines: Bool) -> Bool {
        wrapLines && (row.kind.isCode || row.kind == .hunkHeader)
    }

    private static func wrappedDescriptors(
        for row: VVDiffRow,
        wrapLines: Bool,
        maxChars: Int
    ) -> [VVDiffWrappedTextDescriptor] {
        let displayText = row.kind == .hunkHeader ? VVDiffDisplayText(for: row) : row.text
        if shouldWrapUnified(row: row, wrapLines: wrapLines) {
            return wrappedTextDescriptors(displayText, maxChars: maxChars)
        }
        return [VVDiffWrappedTextDescriptor(start: 0, length: displayText.count)]
    }

    private static func wrappedDescriptors(
        forHeader row: VVDiffRow,
        wrapLines: Bool,
        maxChars: Int
    ) -> [VVDiffWrappedTextDescriptor] {
        let displayText = VVDiffDisplayText(for: row)
        if wrapLines && row.kind == .hunkHeader {
            return wrappedTextDescriptors(displayText, maxChars: maxChars)
        }
        return [VVDiffWrappedTextDescriptor(start: 0, length: displayText.count)]
    }

    private static func wrappedDescriptors(
        forSplitCell cell: VVDiffSplitRow.Cell,
        wrapLines: Bool,
        maxChars: Int
    ) -> [VVDiffWrappedTextDescriptor] {
        if wrapLines && cell.kind.isCode {
            return wrappedTextDescriptors(cell.text, maxChars: maxChars)
        }
        return [VVDiffWrappedTextDescriptor(start: 0, length: cell.text.count)]
    }

    private static func wrappedTextDescriptorCount(
        unifiedRow row: VVDiffRow,
        wrapLines: Bool,
        maxChars: Int
    ) -> Int {
        let displayText = row.kind == .hunkHeader ? VVDiffDisplayText(for: row) : row.text
        if shouldWrapUnified(row: row, wrapLines: wrapLines) {
            return wrappedTextDescriptorCount(displayText, maxChars: maxChars)
        }
        return 1
    }

    private static func wrappedTextDescriptorCount(
        headerRow row: VVDiffRow,
        wrapLines: Bool,
        maxChars: Int
    ) -> Int {
        let displayText = VVDiffDisplayText(for: row)
        if wrapLines && row.kind == .hunkHeader {
            return wrappedTextDescriptorCount(displayText, maxChars: maxChars)
        }
        return 1
    }

    private static func wrappedTextDescriptorCount(
        splitCell cell: VVDiffSplitRow.Cell,
        wrapLines: Bool,
        maxChars: Int
    ) -> Int {
        if wrapLines && cell.kind.isCode {
            return wrappedTextDescriptorCount(cell.text, maxChars: maxChars)
        }
        return 1
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
        if !text.contains("\n") {
            let lineLength = text.count
            guard lineLength > 0 else { return [VVDiffWrappedTextDescriptor(start: 0, length: 0)] }
            let segmentCount = max(1, Int(ceil(Double(lineLength) / Double(maxChars))))
            var result: [VVDiffWrappedTextDescriptor] = []
            result.reserveCapacity(segmentCount)
            var offset = 0
            var remaining = lineLength
            while remaining > 0 {
                let segmentLength = min(maxChars, remaining)
                result.append(VVDiffWrappedTextDescriptor(start: offset, length: segmentLength))
                offset += segmentLength
                remaining -= segmentLength
            }
            return result
        }

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

    private static func wrappedTextDescriptorCount(_ text: String, maxChars: Int) -> Int {
        guard maxChars > 0 else { return 1 }
        if !text.contains("\n") {
            let lineLength = text.count
            if lineLength == 0 {
                return 1
            }
            return max(1, Int(ceil(Double(lineLength) / Double(maxChars))))
        }

        let logicalLines = text.split(separator: "\n", omittingEmptySubsequences: false)
        var count = 0

        for line in logicalLines {
            let lineLength = line.count
            if lineLength == 0 {
                count += 1
            } else {
                count += Int(ceil(Double(lineLength) / Double(maxChars)))
            }
        }

        return max(1, count)
    }
}
