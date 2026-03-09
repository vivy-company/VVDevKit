import Foundation
import VVHighlighting
import VVMetalPrimitives

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

public enum VVDiffHighlighting {
    public struct Guardrails: Sendable {
        public var maxHighlightRows: Int
        public var maxHighlightUTF16: Int
        public var maxSingleLineUTF16: Int

        public init(
            maxHighlightRows: Int = 3_500,
            maxHighlightUTF16: Int = 360_000,
            maxSingleLineUTF16: Int = 8_192
        ) {
            self.maxHighlightRows = maxHighlightRows
            self.maxHighlightUTF16 = maxHighlightUTF16
            self.maxSingleLineUTF16 = maxSingleLineUTF16
        }
    }

    public static let defaultGuardrails = Guardrails()

    public static func highlightTheme(isDarkBackground: Bool) -> HighlightTheme {
        isDarkBackground ? .defaultDark : .defaultLight
    }

    public static func computeHighlightedRanges<Row>(
        rows: [Row],
        language: LanguageConfiguration?,
        highlightTheme: HighlightTheme,
        font: VVFont,
        guardrails: Guardrails = defaultGuardrails,
        rowID: (Row) -> Int,
        rowText: (Row) -> String,
        rowIsCode: (Row) -> Bool
    ) async -> [Int: [(NSRange, SIMD4<Float>)]] {
        let codeRows = rows.filter(rowIsCode)
        guard !codeRows.isEmpty, let language else { return [:] }
        guard codeRows.count <= guardrails.maxHighlightRows else { return [:] }

        var totalUTF16 = 0
        for row in codeRows {
            if Task.isCancelled { return [:] }
            let rowUTF16 = rowText(row).utf16.count
            if rowUTF16 > guardrails.maxSingleLineUTF16 { return [:] }
            totalUTF16 += rowUTF16 + 1
            if totalUTF16 > guardrails.maxHighlightUTF16 { return [:] }
        }

        let joined = makeJoinedCodeBuffer(
            from: rows,
            rowID: rowID,
            rowText: rowText,
            rowIsCode: rowIsCode
        )
        let highlighter = TreeSitterHighlighter(theme: highlightTheme)

        do {
            try await highlighter.setLanguage(language)
            if Task.isCancelled { return [:] }
            _ = try await highlighter.parse(joined.text)
            if Task.isCancelled { return [:] }

            let sortedRanges = try await highlighter.allHighlights().sorted { lhs, rhs in
                lhs.range.location < rhs.range.location
            }
            if Task.isCancelled { return [:] }

            var result: [Int: [(NSRange, SIMD4<Float>)]] = [:]
            let sortedRows = joined.rowRanges.sorted { lhs, rhs in
                lhs.value.location < rhs.value.location
            }
            var rangeStartIndex = 0

            for (id, rowNSRange) in sortedRows {
                if Task.isCancelled { return [:] }
                var rowRanges: [(NSRange, SIMD4<Float>)] = []

                while rangeStartIndex < sortedRanges.count {
                    let rangeEnd = NSMaxRange(sortedRanges[rangeStartIndex].range)
                    if rangeEnd <= rowNSRange.location {
                        rangeStartIndex += 1
                        continue
                    }
                    break
                }

                var index = rangeStartIndex
                while index < sortedRanges.count {
                    let range = sortedRanges[index]
                    if range.range.location >= NSMaxRange(rowNSRange) {
                        break
                    }

                    let intersection = NSIntersectionRange(range.range, rowNSRange)
                    if intersection.length > 0 {
                        let localStart = intersection.location - rowNSRange.location
                        let localRange = NSRange(location: localStart, length: intersection.length)
                        rowRanges.append((localRange, simdColor(from: range.style, baseFont: font)))
                    }
                    index += 1
                }

                if !rowRanges.isEmpty {
                    result[id] = rowRanges
                }
            }

            return result
        } catch {
            return [:]
        }
    }

    public static func makeJoinedCodeBuffer<Row>(
        from rows: [Row],
        rowID: (Row) -> Int,
        rowText: (Row) -> String,
        rowIsCode: (Row) -> Bool
    ) -> (text: String, rowRanges: [Int: NSRange]) {
        let codeRows = rows.filter(rowIsCode)
        var totalUTF16 = 0
        for row in codeRows {
            totalUTF16 += rowText(row).utf16.count + 1
        }

        var text = ""
        text.reserveCapacity(totalUTF16)

        var rowRanges: [Int: NSRange] = [:]
        rowRanges.reserveCapacity(codeRows.count)

        var offset = 0
        for row in codeRows {
            let rowString = rowText(row)
            let length = rowString.utf16.count
            rowRanges[rowID(row)] = NSRange(location: offset, length: length)
            text.append(rowString)
            text.append("\n")
            offset += length + 1
        }

        return (text: text, rowRanges: rowRanges)
    }

    private static func simdColor(from style: HighlightStyle, baseFont: VVFont) -> SIMD4<Float> {
        let attributes = style.attributes(baseFont: baseFont)
        let color = (attributes[.foregroundColor] as? NSColor) ?? .white
        return SIMD4<Float>(
            Float(color.redComponent),
            Float(color.greenComponent),
            Float(color.blueComponent),
            Float(color.alphaComponent)
        )
    }
}
