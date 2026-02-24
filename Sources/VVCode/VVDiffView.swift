import AppKit
import CoreText
import MetalKit
import SwiftUI
import VVHighlighting
import VVMarkdown
import VVMetalPrimitives

// MARK: - Data Model

public enum VVDiffRenderStyle: Hashable, Sendable {
    case unifiedTable
    case split
}

/// A parsed row in a unified diff table.
public struct VVDiffRow: Identifiable, Hashable, Sendable {
    public enum Kind: String, Hashable, Sendable {
        case fileHeader
        case hunkHeader
        case context
        case added
        case deleted
        case metadata
    }

    public let id: Int
    public let kind: Kind
    public let oldLineNumber: Int?
    public let newLineNumber: Int?
    public let text: String

    public init(
        id: Int,
        kind: Kind,
        oldLineNumber: Int? = nil,
        newLineNumber: Int? = nil,
        text: String
    ) {
        self.id = id
        self.kind = kind
        self.oldLineNumber = oldLineNumber
        self.newLineNumber = newLineNumber
        self.text = text
    }
}

private struct VVDiffSection: Identifiable, Hashable {
    let id: Int
    let filePath: String
    let headerRow: VVDiffRow?
    let rows: [VVDiffRow]

    var addedCount: Int { rows.filter { $0.kind == .added }.count }
    var deletedCount: Int { rows.filter { $0.kind == .deleted }.count }
    var hunkCount: Int { rows.filter { $0.kind == .hunkHeader }.count }
}

private extension VVDiffRow.Kind {
    var isCode: Bool {
        switch self {
        case .context, .added, .deleted:
            return true
        case .fileHeader, .hunkHeader, .metadata:
            return false
        }
    }
}

private struct VVDiffSplitRow: Identifiable, Hashable {
    struct Cell: Hashable {
        let rowID: Int
        let lineNumber: Int?
        let text: String
        let kind: VVDiffRow.Kind
        let inlineChanges: [InlineRange]
    }

    struct InlineRange: Hashable {
        let start: Int
        let end: Int
    }

    let id: Int
    let header: VVDiffRow?
    let left: Cell?
    let right: Cell?
}

// MARK: - Text Selection Types

/// Position within the diff document: row index + character offset + pane.
private struct DiffTextPosition: Sendable, Hashable, Comparable, VVMetalPrimitives.VVTextPosition {
    let rowIndex: Int      // Index into rowGeometries array
    let charOffset: Int    // Character offset within row.text
    let paneX: CGFloat     // Pane origin X (0 for left/unified, columnWidth for right)

    init(rowIndex: Int, charOffset: Int, paneX: CGFloat = 0) {
        self.rowIndex = rowIndex
        self.charOffset = charOffset
        self.paneX = paneX
    }

    static func == (lhs: Self, rhs: Self) -> Bool {
        lhs.rowIndex == rhs.rowIndex && lhs.charOffset == rhs.charOffset
    }

    static func < (lhs: Self, rhs: Self) -> Bool {
        if lhs.rowIndex != rhs.rowIndex { return lhs.rowIndex < rhs.rowIndex }
        return lhs.charOffset < rhs.charOffset
    }
}

/// Geometry cache for a single row in the diff view.
private struct RowGeometry {
    let rowIndex: Int
    let rowID: Int
    let y: CGFloat
    let height: CGFloat
    let isCodeRow: Bool
    let text: String
    let codeStartX: CGFloat
    let paneX: CGFloat      // For split mode: left pane = 0, right pane = columnWidth + 1
    let paneWidth: CGFloat  // For split mode: width of the pane containing this row
}

private struct RowGeometryCacheKey: Equatable {
    let rowsSignature: Int
    let style: VVDiffRenderStyle
    let widthBucket: Int
    let wrapsUnified: Bool
    let fontSignature: Int
}

// MARK: - Diff Computation Helpers

/// Computes word-level inline change ranges between two lines.
/// Returns arrays of `VVDiffSplitRow.InlineRange` (UTF-16 offsets) for the old and new text.
private func computeInlineChanges(oldText: String, newText: String) -> (old: [VVDiffSplitRow.InlineRange], new: [VVDiffSplitRow.InlineRange]) {
    let oldChars = Array(oldText)
    let newChars = Array(newText)

    // Find common prefix
    var prefixLen = 0
    while prefixLen < oldChars.count && prefixLen < newChars.count && oldChars[prefixLen] == newChars[prefixLen] {
        prefixLen += 1
    }

    // Find common suffix (not overlapping with prefix)
    var suffixLen = 0
    while suffixLen < oldChars.count - prefixLen && suffixLen < newChars.count - prefixLen
        && oldChars[oldChars.count - 1 - suffixLen] == newChars[newChars.count - 1 - suffixLen] {
        suffixLen += 1
    }

    let oldMiddleStart = prefixLen
    let oldMiddleEnd = oldChars.count - suffixLen
    let newMiddleStart = prefixLen
    let newMiddleEnd = newChars.count - suffixLen

    // If nothing changed or everything changed, skip word-level
    if oldMiddleStart >= oldMiddleEnd && newMiddleStart >= newMiddleEnd {
        return (old: [], new: [])
    }

    // Tokenize middle portions by word boundaries
    let oldTokens = tokenize(Array(oldChars[oldMiddleStart..<oldMiddleEnd]), baseOffset: oldMiddleStart)
    let newTokens = tokenize(Array(newChars[newMiddleStart..<newMiddleEnd]), baseOffset: newMiddleStart)

    // LCS on tokens to find matching segments
    let lcs = longestCommonSubsequence(oldTokens.map(\.text), newTokens.map(\.text))

    // Mark old tokens not in LCS as changed
    var oldChanged: [VVDiffSplitRow.InlineRange] = []
    var lcsIdx = 0
    for token in oldTokens {
        if lcsIdx < lcs.oldIndices.count && token.index == lcs.oldIndices[lcsIdx] {
            lcsIdx += 1
        } else {
            oldChanged.append(VVDiffSplitRow.InlineRange(start: token.offset, end: token.offset + token.text.count))
        }
    }

    // Mark new tokens not in LCS as changed
    var newChanged: [VVDiffSplitRow.InlineRange] = []
    lcsIdx = 0
    for token in newTokens {
        if lcsIdx < lcs.newIndices.count && token.index == lcs.newIndices[lcsIdx] {
            lcsIdx += 1
        } else {
            newChanged.append(VVDiffSplitRow.InlineRange(start: token.offset, end: token.offset + token.text.count))
        }
    }

    // Merge adjacent ranges
    oldChanged = mergeRanges(oldChanged)
    newChanged = mergeRanges(newChanged)

    return (old: oldChanged, new: newChanged)
}

private struct Token {
    let text: String
    let offset: Int
    let index: Int
}

private func tokenize(_ chars: [Character], baseOffset: Int) -> [Token] {
    var tokens: [Token] = []
    var i = 0
    var tokenIndex = 0

    while i < chars.count {
        let ch = chars[i]
        if ch.isWhitespace {
            var j = i
            while j < chars.count && chars[j].isWhitespace { j += 1 }
            tokens.append(Token(text: String(chars[i..<j]), offset: baseOffset + i, index: tokenIndex))
            tokenIndex += 1
            i = j
        } else if ch.isLetter || ch.isNumber || ch == "_" {
            var j = i
            while j < chars.count && (chars[j].isLetter || chars[j].isNumber || chars[j] == "_") { j += 1 }
            tokens.append(Token(text: String(chars[i..<j]), offset: baseOffset + i, index: tokenIndex))
            tokenIndex += 1
            i = j
        } else {
            tokens.append(Token(text: String(ch), offset: baseOffset + i, index: tokenIndex))
            tokenIndex += 1
            i += 1
        }
    }
    return tokens
}

private struct LCSResult {
    let oldIndices: [Int]
    let newIndices: [Int]
}

private func longestCommonSubsequence(_ a: [String], _ b: [String]) -> LCSResult {
    let m = a.count, n = b.count
    if m == 0 || n == 0 { return LCSResult(oldIndices: [], newIndices: []) }

    var dp = Array(repeating: Array(repeating: 0, count: n + 1), count: m + 1)
    for i in 1...m {
        for j in 1...n {
            if a[i - 1] == b[j - 1] {
                dp[i][j] = dp[i - 1][j - 1] + 1
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
            }
        }
    }

    var oldIndices: [Int] = []
    var newIndices: [Int] = []
    var i = m, j = n
    while i > 0 && j > 0 {
        if a[i - 1] == b[j - 1] {
            oldIndices.append(i - 1)
            newIndices.append(j - 1)
            i -= 1
            j -= 1
        } else if dp[i - 1][j] > dp[i][j - 1] {
            i -= 1
        } else {
            j -= 1
        }
    }

    return LCSResult(oldIndices: oldIndices.reversed(), newIndices: newIndices.reversed())
}

private func mergeRanges(_ ranges: [VVDiffSplitRow.InlineRange]) -> [VVDiffSplitRow.InlineRange] {
    guard !ranges.isEmpty else { return [] }
    var merged: [VVDiffSplitRow.InlineRange] = [ranges[0]]
    for i in 1..<ranges.count {
        let last = merged[merged.count - 1]
        let cur = ranges[i]
        if cur.start <= last.end {
            merged[merged.count - 1] = VVDiffSplitRow.InlineRange(start: last.start, end: max(last.end, cur.end))
        } else {
            merged.append(cur)
        }
    }
    return merged
}

// MARK: - Parsing

/// Backward-compatible parse entry point for tests. Use `VVDiffView(unifiedDiff:)` for rendering.
public enum VVDiffTable {
    /// Parse unified git diff text into rows suitable for `VVDiffView`.
    public static func parse(unifiedDiff: String) -> [VVDiffRow] {
        parseDiffRows(unifiedDiff: unifiedDiff)
    }
}

private func parseDiffRows(unifiedDiff: String) -> [VVDiffRow] {
    var lines = unifiedDiff.split(omittingEmptySubsequences: false, whereSeparator: \.isNewline)
    if lines.last?.isEmpty == true {
        _ = lines.popLast()
    }
    var rows: [VVDiffRow] = []

    var oldLine = 0
    var newLine = 0
    var inHunk = false

    for rawLine in lines {
        let line = String(rawLine)

        if line.hasPrefix("diff --git ") {
            inHunk = false
            rows.append(
                VVDiffRow(
                    id: rows.count,
                    kind: .fileHeader,
                    text: filePath(from: line)
                )
            )
            continue
        }

        if line.hasPrefix("@@") {
            inHunk = true
            if let header = parseHunkHeader(line) {
                oldLine = header.oldStart
                newLine = header.newStart
            }
            rows.append(
                VVDiffRow(
                    id: rows.count,
                    kind: .hunkHeader,
                    text: line
                )
            )
            continue
        }

        if !inHunk {
            if isMetadataLine(line) {
                rows.append(
                    VVDiffRow(
                        id: rows.count,
                        kind: .metadata,
                        text: line
                    )
                )
            }
            continue
        }

        if line.hasPrefix("+") && !line.hasPrefix("+++") {
            rows.append(
                VVDiffRow(
                    id: rows.count,
                    kind: .added,
                    oldLineNumber: nil,
                    newLineNumber: newLine,
                    text: String(line.dropFirst())
                )
            )
            newLine += 1
            continue
        }

        if line.hasPrefix("-") && !line.hasPrefix("---") {
            rows.append(
                VVDiffRow(
                    id: rows.count,
                    kind: .deleted,
                    oldLineNumber: oldLine,
                    newLineNumber: nil,
                    text: String(line.dropFirst())
                )
            )
            oldLine += 1
            continue
        }

        if line.hasPrefix(" ") {
            rows.append(
                VVDiffRow(
                    id: rows.count,
                    kind: .context,
                    oldLineNumber: oldLine,
                    newLineNumber: newLine,
                    text: String(line.dropFirst())
                )
            )
            oldLine += 1
            newLine += 1
            continue
        }

        if line.hasPrefix("\\") {
            rows.append(
                VVDiffRow(
                    id: rows.count,
                    kind: .metadata,
                    text: line
                )
            )
            continue
        }

        // Empty line without prefix in hunk: treat as plain context line.
        if line.isEmpty {
            rows.append(
                VVDiffRow(
                    id: rows.count,
                    kind: .context,
                    oldLineNumber: oldLine,
                    newLineNumber: newLine,
                    text: ""
                )
            )
            oldLine += 1
            newLine += 1
            continue
        }

        rows.append(
            VVDiffRow(
                id: rows.count,
                kind: .context,
                oldLineNumber: oldLine,
                newLineNumber: newLine,
                text: line
            )
        )
        oldLine += 1
        newLine += 1
    }

    return rows
}

private func makeSections(from rows: [VVDiffRow]) -> [VVDiffSection] {
    var result: [VVDiffSection] = []

    var currentSectionID: Int?
    var currentPath: String?
    var currentHeaderRow: VVDiffRow?
    var currentRows: [VVDiffRow] = []
    var syntheticID = -1

    func flushSection() {
        guard let sectionID = currentSectionID, let path = currentPath else {
            return
        }

        result.append(
            VVDiffSection(
                id: sectionID,
                filePath: path,
                headerRow: currentHeaderRow,
                rows: currentRows
            )
        )

        currentRows.removeAll(keepingCapacity: true)
    }

    for row in rows {
        if row.kind == .fileHeader {
            flushSection()
            currentSectionID = row.id
            currentPath = row.text
            currentHeaderRow = row
            continue
        }

        if currentSectionID == nil {
            currentSectionID = syntheticID
            syntheticID -= 1
            currentPath = "workspace.diff"
            currentHeaderRow = nil
        }

        currentRows.append(row)
    }

    flushSection()
    return result
}

private func makeSplitRows(from rows: [VVDiffRow]) -> [VVDiffSplitRow] {
    var result: [VVDiffSplitRow] = []
    result.reserveCapacity(rows.count)
    var index = 0
    var splitID = 0

    while index < rows.count {
        let row = rows[index]

        if row.kind == .fileHeader {
            result.append(VVDiffSplitRow(id: splitID, header: row, left: nil, right: nil))
            splitID += 1
            index += 1
            continue
        }

        if row.kind == .metadata {
            index += 1
            continue
        }

        if row.kind == .hunkHeader {
            result.append(VVDiffSplitRow(id: splitID, header: row, left: nil, right: nil))
            splitID += 1
            index += 1
            continue
        }

        if row.kind == .context {
            result.append(
                VVDiffSplitRow(
                    id: splitID,
                    header: nil,
                    left: VVDiffSplitRow.Cell(rowID: row.id, lineNumber: row.oldLineNumber, text: row.text, kind: row.kind, inlineChanges: []),
                    right: VVDiffSplitRow.Cell(rowID: row.id, lineNumber: row.newLineNumber, text: row.text, kind: row.kind, inlineChanges: [])
                )
            )
            splitID += 1
            index += 1
            continue
        }

        if row.kind == .deleted || row.kind == .added {
            var deletedRows: [VVDiffRow] = []
            var addedRows: [VVDiffRow] = []

            while index < rows.count, rows[index].kind == .deleted {
                deletedRows.append(rows[index])
                index += 1
            }

            while index < rows.count, rows[index].kind == .added {
                addedRows.append(rows[index])
                index += 1
            }

            if deletedRows.isEmpty, addedRows.isEmpty {
                continue
            }

            let pairCount = max(deletedRows.count, addedRows.count)
            for pairIndex in 0..<pairCount {
                let leftRow = pairIndex < deletedRows.count ? deletedRows[pairIndex] : nil
                let rightRow = pairIndex < addedRows.count ? addedRows[pairIndex] : nil

                var leftInline: [VVDiffSplitRow.InlineRange] = []
                var rightInline: [VVDiffSplitRow.InlineRange] = []
                if let l = leftRow, let r = rightRow {
                    let changes = computeInlineChanges(oldText: l.text, newText: r.text)
                    leftInline = changes.old
                    rightInline = changes.new
                }

                result.append(
                    VVDiffSplitRow(
                        id: splitID,
                        header: nil,
                        left: leftRow.map { VVDiffSplitRow.Cell(rowID: $0.id, lineNumber: $0.oldLineNumber, text: $0.text, kind: $0.kind, inlineChanges: leftInline) },
                        right: rightRow.map { VVDiffSplitRow.Cell(rowID: $0.id, lineNumber: $0.newLineNumber, text: $0.text, kind: $0.kind, inlineChanges: rightInline) }
                    )
                )
                splitID += 1
            }
            continue
        }

        index += 1
    }

    return result
}

private func pathParts(for path: String) -> (fileName: String, directory: String) {
    let fileName = (path as NSString).lastPathComponent
    let directory = (path as NSString).deletingLastPathComponent
    return (fileName: fileName, directory: directory)
}

private func filePath(from line: String) -> String {
    let parts = line.split(separator: " ")
    guard parts.count >= 4 else { return line }

    let rawPath = String(parts[3])
    return rawPath.hasPrefix("b/") ? String(rawPath.dropFirst(2)) : rawPath
}

private func isMetadataLine(_ line: String) -> Bool {
    line.hasPrefix("index ") ||
    line.hasPrefix("--- ") ||
    line.hasPrefix("+++ ") ||
    line.hasPrefix("new file mode ") ||
    line.hasPrefix("deleted file mode ") ||
    line.hasPrefix("rename from ") ||
    line.hasPrefix("rename to ") ||
    line.hasPrefix("similarity index ") ||
    line.hasPrefix("dissimilarity index ") ||
    line.hasPrefix("Binary files ")
}

private func parseHunkHeader(_ line: String) -> (oldStart: Int, newStart: Int)? {
    let pattern = #"@@ -(\d+)(?:,\d+)? \+(\d+)(?:,\d+)? @@"#
    guard let regex = try? NSRegularExpression(pattern: pattern),
          let match = regex.firstMatch(in: line, range: NSRange(line.startIndex..., in: line)),
          let oldRange = Range(match.range(at: 1), in: line),
          let newRange = Range(match.range(at: 2), in: line),
          let oldStart = Int(line[oldRange]),
          let newStart = Int(line[newRange]) else {
        return nil
    }

    return (oldStart: oldStart, newStart: newStart)
}

private func makeJoinedCodeBuffer(from rows: [VVDiffRow]) -> (text: String, rowRanges: [Int: NSRange]) {
    let codeRows = rows.filter { $0.kind.isCode }
    var totalUTF16 = 0
    for row in codeRows {
        totalUTF16 += row.text.utf16.count + 1
    }

    var text = ""
    text.reserveCapacity(totalUTF16)

    var rowRanges: [Int: NSRange] = [:]
    rowRanges.reserveCapacity(codeRows.count)

    var offset = 0
    for row in codeRows {
        let length = row.text.utf16.count
        rowRanges[row.id] = NSRange(location: offset, length: length)
        text.append(row.text)
        text.append("\n")
        offset += length + 1
    }

    return (text: text, rowRanges: rowRanges)
}

// MARK: - VVDiffRenderer

private typealias MDLayoutGlyph = VVMarkdown.LayoutGlyph
private typealias MDFontVariant = VVMarkdown.FontVariant

/// Builds a VVScene from diff data using VVMetalPrimitives.
private final class VVDiffRenderer {
    let font: NSFont
    let lineHeight: CGFloat
    let charWidth: CGFloat
    let headerHeight: CGFloat
    let codeInsetX: CGFloat = 10

    var textColor: SIMD4<Float> = .gray(0.83)
    var backgroundColor: SIMD4<Float> = .gray(0.12)
    var gutterTextColor: SIMD4<Float> = .gray50
    var gutterBgColor: SIMD4<Float> = .gray(0.12)
    var addedBgColor: SIMD4<Float> = .rgba(0, 0.5, 0, 0.13)
    var deletedBgColor: SIMD4<Float> = .rgba(0.5, 0, 0, 0.13)
    var hunkBgColor: SIMD4<Float> = .gray20.withOpacity(0.88)
    var headerBgColor: SIMD4<Float> = .gray(0.15, opacity: 0.99)
    var metadataBgColor: SIMD4<Float> = .gray(0.15, opacity: 0.58)
    var addedMarkerColor: SIMD4<Float> = .rgba(0, 0.8, 0)
    var deletedMarkerColor: SIMD4<Float> = .rgba(0.8, 0, 0)
    var modifiedColor: SIMD4<Float> = .rgba(0, 0.5, 1)
    var addedInlineBg: SIMD4<Float> = .rgba(0, 0.5, 0, 0.22)
    var deletedInlineBg: SIMD4<Float> = .rgba(0.5, 0, 0, 0.22)
    var emptyPaneBg: SIMD4<Float> = .gray(0.15, opacity: 0.30)

    var layoutEngine: MarkdownLayoutEngine

    init(font: NSFont, theme: VVTheme, contentWidth: CGFloat) {
        self.font = font
        self.lineHeight = ceil(font.pointSize * 1.6)
        self.headerHeight = ceil(font.pointSize * 1.6 * 1.5)

        // Compute monospace char width from CTFont
        let ctFont = font as CTFont
        var glyphID: CGGlyph = 0
        var char: UniChar = 0x004D // 'M'
        CTFontGetGlyphsForCharacters(ctFont, &char, &glyphID, 1)
        var advance = CGSize.zero
        CTFontGetAdvancesForGlyphs(ctFont, .horizontal, &glyphID, &advance, 1)
        self.charWidth = advance.width > 0 ? advance.width : font.pointSize * 0.6

        // Create layout engine with a minimal markdown theme
        var mdTheme = MarkdownTheme.dark
        mdTheme.textColor = theme.textColor.simdColor
        mdTheme.contentPadding = 0
        mdTheme.paragraphSpacing = 0
        self.layoutEngine = MarkdownLayoutEngine(baseFont: font, theme: mdTheme, contentWidth: contentWidth)

        updateThemeColors(theme)
    }

    func updateThemeColors(_ theme: VVTheme) {
        textColor = theme.textColor.simdColor
        backgroundColor = theme.backgroundColor.simdColor
        gutterTextColor = theme.gutterTextColor.simdColor
        gutterBgColor = theme.gutterBackgroundColor.simdColor
        addedBgColor = withAlpha(theme.gitAddedColor.simdColor, 0.13)
        deletedBgColor = withAlpha(theme.gitDeletedColor.simdColor, 0.13)
        hunkBgColor = withAlpha(theme.currentLineColor.simdColor, 0.88)
        headerBgColor = withAlpha(theme.gutterBackgroundColor.simdColor, 0.99)
        metadataBgColor = withAlpha(theme.gutterBackgroundColor.simdColor, 0.58)
        addedMarkerColor = theme.gitAddedColor.simdColor
        deletedMarkerColor = theme.gitDeletedColor.simdColor
        modifiedColor = theme.gitModifiedColor.simdColor
        addedInlineBg = withAlpha(theme.gitAddedColor.simdColor, 0.22)
        deletedInlineBg = withAlpha(theme.gitDeletedColor.simdColor, 0.22)
        emptyPaneBg = withAlpha(theme.gutterBackgroundColor.simdColor, 0.30)
    }

    func updateContentWidth(_ width: CGFloat) {
        layoutEngine.updateContentWidth(width)
    }

    private func wrapCapacity(totalWidth: CGFloat, codeStartX: CGFloat) -> Int {
        let available = max(0, totalWidth - codeStartX - codeInsetX - 12)
        guard available > 0 else { return 1 }
        return max(1, Int(floor(available / max(charWidth, 1))))
    }

    private func wrappedTextSegments(_ text: String, maxChars: Int) -> [String] {
        guard maxChars > 0 else { return [text] }
        var result: [String] = []
        let logicalLines = text.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        for line in logicalLines {
            if line.isEmpty {
                result.append("")
                continue
            }
            var start = line.startIndex
            while start < line.endIndex {
                let end = line.index(start, offsetBy: maxChars, limitedBy: line.endIndex) ?? line.endIndex
                result.append(String(line[start..<end]))
                start = end
            }
        }
        return result.isEmpty ? [""] : result
    }

    private func wrappedTextSegmentCount(_ text: String, maxChars: Int) -> Int {
        guard maxChars > 0 else { return 1 }
        var count = 0
        text.enumerateSubstrings(in: text.startIndex..<text.endIndex, options: [.byLines, .substringNotRequired]) { _, range, _, _ in
            let length = text.distance(from: range.lowerBound, to: range.upperBound)
            if length == 0 {
                count += 1
            } else {
                count += max(1, Int(ceil(Double(length) / Double(maxChars))))
            }
        }
        return max(count, 1)
    }

    // MARK: - Unified Scene

    func buildUnifiedScene(
        sections: [VVDiffSection],
        rows: [VVDiffRow],
        width: CGFloat,
        viewport: CGRect,
        highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]],
        wrapLines: Bool = false,
        measureFullHeight: Bool = true
    ) -> (scene: VVScene, contentHeight: CGFloat) {
        let maxOld = rows.compactMap(\.oldLineNumber).max() ?? 0
        let maxNew = rows.compactMap(\.newLineNumber).max() ?? 0
        let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
        let gutterColWidth = CGFloat(gutterDigits) * charWidth + 16
        let markerWidth = charWidth + 8
        let codeStartX = gutterColWidth * 2 + markerWidth
        let maxCharsPerVisualLine = wrapCapacity(totalWidth: width, codeStartX: codeStartX)

        var builder = VVSceneBuilder()
        var y: CGFloat = 0

        for section in sections {
            // File header
            if section.headerRow != nil {
                let rowH = headerHeight
                if y + rowH >= viewport.minY - 200 && y <= viewport.maxY + 200 {
                    buildFileHeader(
                        section: section,
                        y: y, width: width, height: rowH,
                        builder: &builder
                    )
                }
                y += rowH
            }

            // Section rows (skip metadata — already shown in file header)
            for row in section.rows {
                if row.kind == .metadata { continue }
                let shouldWrap = wrapLines && (row.kind.isCode || row.kind == .hunkHeader)
                let visualLines = shouldWrap
                    ? wrappedTextSegmentCount(row.text, maxChars: maxCharsPerVisualLine)
                    : 1
                let rowH = lineHeight * CGFloat(max(1, visualLines))
                if y + rowH >= viewport.minY - 200 && y <= viewport.maxY + 200 {
                    let wrappedLines = shouldWrap
                        ? wrappedTextSegments(row.text, maxChars: maxCharsPerVisualLine)
                        : nil
                    buildUnifiedRow(
                        row: row,
                        y: y, width: width, height: rowH,
                        gutterColWidth: gutterColWidth,
                        markerWidth: markerWidth,
                        codeStartX: codeStartX,
                        highlightedRanges: highlightedRanges,
                        wrappedLines: wrappedLines,
                        builder: &builder
                    )
                }
                y += rowH
            }

            if !measureFullHeight, y > viewport.maxY + 200 {
                break
            }
        }

        return (scene: builder.scene, contentHeight: y)
    }

    // MARK: - Split Scene

    func buildSplitScene(
        splitRows: [VVDiffSplitRow],
        rows: [VVDiffRow],
        width: CGFloat,
        viewport: CGRect,
        highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]],
        measureFullHeight: Bool = true
    ) -> (scene: VVScene, contentHeight: CGFloat) {
        let maxOld = rows.compactMap(\.oldLineNumber).max() ?? 0
        let maxNew = rows.compactMap(\.newLineNumber).max() ?? 0
        let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
        let gutterColWidth = CGFloat(gutterDigits) * charWidth + 16
        let markerWidth = charWidth + 4
        let columnWidth = max(420, floor(width / 2))
        let totalWidth = columnWidth * 2
        let paneCodeStartX = markerWidth + gutterColWidth

        var builder = VVSceneBuilder()
        var y: CGFloat = 0

        for splitRow in splitRows {
            if let header = splitRow.header {
                let rowH = header.kind == .fileHeader ? headerHeight : lineHeight

                if y + rowH >= viewport.minY - 200 && y <= viewport.maxY + 200 {
                    if header.kind == .fileHeader {
                        let section = VVDiffSection(
                            id: header.id,
                            filePath: header.text,
                            headerRow: header,
                            rows: rowsForFileHeader(header, allRows: rows)
                        )
                        buildFileHeader(section: section, y: y, width: totalWidth, height: rowH, builder: &builder)
                    } else {
                        buildHunkHeaderRow(text: header.text, y: y, width: totalWidth, height: rowH, builder: &builder)
                    }
                }
                y += rowH
            } else {
                let rowH = lineHeight
                if y + rowH >= viewport.minY - 200 && y <= viewport.maxY + 200 {
                    // Left pane
                    buildSplitCell(
                        cell: splitRow.left,
                        y: y, paneX: 0, paneWidth: columnWidth, height: rowH,
                        gutterColWidth: gutterColWidth,
                        markerWidth: markerWidth,
                        codeStartX: paneCodeStartX,
                        isLeft: true,
                        highlightedRanges: highlightedRanges,
                        builder: &builder
                    )

                    // Right pane
                    buildSplitCell(
                        cell: splitRow.right,
                        y: y, paneX: columnWidth, paneWidth: columnWidth, height: rowH,
                        gutterColWidth: gutterColWidth,
                        markerWidth: markerWidth,
                        codeStartX: paneCodeStartX,
                        isLeft: false,
                        highlightedRanges: highlightedRanges,
                        builder: &builder
                    )
                }
                y += rowH
            }

            if !measureFullHeight, y > viewport.maxY + 200 {
                break
            }
        }

        return (scene: builder.scene, contentHeight: y)
    }

    // MARK: - Row Builders

    private func buildUnifiedRow(
        row: VVDiffRow,
        y: CGFloat, width: CGFloat, height: CGFloat,
        gutterColWidth: CGFloat,
        markerWidth: CGFloat,
        codeStartX: CGFloat,
        highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]],
        wrappedLines: [String]?,
        builder: inout VVSceneBuilder
    ) {
        // Hunk headers handle their own background
        if row.kind == .hunkHeader {
            let lines = wrappedLines ?? [row.text]
            buildHunkHeaderRow(lines: lines, y: y, width: width, height: height, builder: &builder)
            return
        }

        // Background quad
        let bgColor = rowBackgroundColor(for: row.kind)
        let bgQuad = VVQuadPrimitive(
            frame: CGRect(x: 0, y: y, width: width, height: height),
            color: bgColor
        )
        builder.add(kind: .quad(bgQuad), zIndex: -1)

        // Line numbers — use marker color for added/deleted rows
        let firstBaselineY = y + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
        let numFontSize = font.pointSize - 1
        let numColor = lineNumberColor(for: row.kind)

        if let oldNum = row.oldLineNumber {
            let numText = String(oldNum)
            let numGlyphs = layoutEngine.layoutTextGlyphs(numText, variant: .monospace, at: .zero, color: numColor)
            let numWidth = numGlyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            let offsetX = gutterColWidth - numWidth - 4
            addTextGlyphs(numGlyphs, offsetX: offsetX, baselineY: firstBaselineY, fontSize: numFontSize, builder: &builder)
        }

        if let newNum = row.newLineNumber {
            let numText = String(newNum)
            let numGlyphs = layoutEngine.layoutTextGlyphs(numText, variant: .monospace, at: .zero, color: numColor)
            let numWidth = numGlyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            let offsetX = gutterColWidth * 2 - numWidth - 4
            addTextGlyphs(numGlyphs, offsetX: offsetX, baselineY: firstBaselineY, fontSize: numFontSize, builder: &builder)
        }

        // Marker indicator (flush left)
        buildMarkerIndicator(kind: row.kind, x: 0, y: y, width: markerWidth, height: height, builder: &builder)

        // Code text
        if row.kind.isCode || row.kind == .metadata {
            let codeColor = row.kind == .metadata ? gutterTextColor : textColor
            let lines = wrappedLines ?? [row.text]
            let wrapped = wrappedLines != nil
            for (lineIndex, lineText) in lines.enumerated() {
                let baselineY = y + CGFloat(lineIndex) * lineHeight + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
                let codeGlyphs = layoutEngine.layoutTextGlyphs(lineText, variant: .monospace, at: .zero, color: codeColor)
                if !wrapped, let ranges = highlightedRanges[row.id], !ranges.isEmpty {
                    let coloredGlyphs = applyHighlightColors(codeGlyphs, ranges: ranges)
                    addTextGlyphs(coloredGlyphs, offsetX: codeStartX + codeInsetX, baselineY: baselineY, fontSize: font.pointSize, builder: &builder)
                } else {
                    addTextGlyphs(codeGlyphs, offsetX: codeStartX + codeInsetX, baselineY: baselineY, fontSize: font.pointSize, builder: &builder)
                }
            }
        }
    }

    private func buildHunkHeaderRow(
        text: String,
        y: CGFloat, width: CGFloat, height: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        buildHunkHeaderRow(lines: [text], y: y, width: width, height: height, builder: &builder)
    }

    private func buildHunkHeaderRow(
        lines: [String],
        y: CGFloat, width: CGFloat, height: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        let bgQuad = VVQuadPrimitive(
            frame: CGRect(x: 0, y: y, width: width, height: height),
            color: hunkBgColor
        )
        builder.add(kind: .quad(bgQuad), zIndex: -1)

        for (lineIndex, lineText) in lines.enumerated() {
            let baselineY = y + CGFloat(lineIndex) * lineHeight + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
            let glyphs = layoutEngine.layoutTextGlyphs(lineText, variant: .monospace, at: .zero, color: modifiedColor)
            addTextGlyphs(glyphs, offsetX: 12, baselineY: baselineY, fontSize: font.pointSize, builder: &builder)
        }
    }

    private func buildFileHeader(
        section: VVDiffSection,
        y: CGFloat, width: CGFloat, height: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        // Background
        let bgQuad = VVQuadPrimitive(
            frame: CGRect(x: 0, y: y, width: width, height: height),
            color: headerBgColor
        )
        builder.add(kind: .quad(bgQuad), zIndex: -1)

        let parts = pathParts(for: section.filePath)
        let baselineY = y + (height + font.pointSize) / 2 - font.pointSize * 0.15
        let iconX: CGFloat = 12
        let iconWidth = buildFileHeaderIcon(
            x: iconX,
            centerY: y + height * 0.5,
            builder: &builder
        )
        var curX: CGFloat = iconX + iconWidth + 8

        // Filename (semibold)
        let nameGlyphs = layoutEngine.layoutTextGlyphs(parts.fileName, variant: .semibold, at: .zero, color: textColor)
        addTextGlyphs(nameGlyphs, offsetX: curX, baselineY: baselineY, fontSize: font.pointSize + 1, builder: &builder)
        let nameWidth = nameGlyphs.map { $0.position.x + $0.size.width }.max() ?? 0
        curX += nameWidth + 8

        // Directory (dim)
        if !parts.directory.isEmpty {
            let dirGlyphs = layoutEngine.layoutTextGlyphs(parts.directory, variant: .monospace, at: .zero, color: gutterTextColor)
            addTextGlyphs(dirGlyphs, offsetX: curX, baselineY: baselineY, fontSize: font.pointSize, builder: &builder)
            let dirWidth = dirGlyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            curX += dirWidth + 12
        }

        // Stat badges
        let badgeY = baselineY - font.pointSize * 0.7
        let badgeH = font.pointSize + 4
        let badgeFontSize = font.pointSize - 1

        if section.addedCount > 0 {
            curX = buildBadge(
                text: "+\(section.addedCount)",
                color: addedMarkerColor,
                x: curX, badgeY: badgeY, badgeH: badgeH, fontSize: badgeFontSize,
                baselineY: baselineY,
                builder: &builder
            )
            curX += 6
        }

        if section.deletedCount > 0 {
            curX = buildBadge(
                text: "-\(section.deletedCount)",
                color: deletedMarkerColor,
                x: curX, badgeY: badgeY, badgeH: badgeH, fontSize: badgeFontSize,
                baselineY: baselineY,
                builder: &builder
            )
            curX += 6
        }

    }

    @discardableResult
    private func buildFileHeaderIcon(
        x: CGFloat,
        centerY: CGFloat,
        builder: inout VVSceneBuilder
    ) -> CGFloat {
        let iconHeight = min(max(font.pointSize * 0.95, 10), 15)
        let iconWidth = iconHeight * 0.82
        let originY = centerY - iconHeight * 0.5
        let frame = CGRect(x: x, y: originY, width: iconWidth, height: iconHeight)

        let borderColor = gutterTextColor
        let fillColor = withAlpha(gutterTextColor, 0.10)
        let line = max(1, floor(iconHeight * 0.11))

        builder.add(kind: .quad(VVQuadPrimitive(frame: frame, color: fillColor, cornerRadius: 2)))
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: frame.minX, y: frame.minY, width: frame.width, height: line),
            color: borderColor
        )))
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: frame.minX, y: frame.maxY - line, width: frame.width, height: line),
            color: borderColor
        )))
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: frame.minX, y: frame.minY, width: line, height: frame.height),
            color: borderColor
        )))
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: frame.maxX - line, y: frame.minY, width: line, height: frame.height),
            color: borderColor
        )))

        let foldSize = max(2, iconWidth * 0.3)
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: frame.maxX - foldSize, y: frame.minY, width: foldSize, height: foldSize),
            color: withAlpha(borderColor, 0.35)
        )))

        return iconWidth
    }

    private func buildSplitCell(
        cell: VVDiffSplitRow.Cell?,
        y: CGFloat, paneX: CGFloat, paneWidth: CGFloat, height: CGFloat,
        gutterColWidth: CGFloat,
        markerWidth: CGFloat,
        codeStartX: CGFloat,
        isLeft: Bool,
        highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]],
        builder: inout VVSceneBuilder
    ) {
        let bgColor: SIMD4<Float>
        if let cell {
            switch cell.kind {
            case .added: bgColor = addedBgColor
            case .deleted: bgColor = deletedBgColor
            default: bgColor = backgroundColor
            }
        } else {
            bgColor = emptyPaneBg
        }

        let bgQuad = VVQuadPrimitive(
            frame: CGRect(x: paneX, y: y, width: paneWidth, height: height),
            color: bgColor
        )
        builder.add(kind: .quad(bgQuad), zIndex: -1)

        guard let cell else { return }

        let baselineY = y + (height + font.pointSize) / 2 - font.pointSize * 0.15
        let numFontSize = font.pointSize - 1

        // Marker indicator
        let effectiveKind: VVDiffRow.Kind = cell.kind
        buildMarkerIndicator(kind: effectiveKind, x: paneX, y: y, width: markerWidth, height: height, builder: &builder)

        // Line number — colored for added/deleted
        let numColor = lineNumberColor(for: cell.kind)
        if let lineNum = cell.lineNumber {
            let numText = String(lineNum)
            let numGlyphs = layoutEngine.layoutTextGlyphs(numText, variant: .monospace, at: .zero, color: numColor)
            let numWidth = numGlyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            let numX = paneX + markerWidth + gutterColWidth - numWidth - 8
            addTextGlyphs(numGlyphs, offsetX: numX, baselineY: baselineY, fontSize: numFontSize, builder: &builder)
        }

        // Code text
        let codeGlyphs: [MDLayoutGlyph]
        if let ranges = highlightedRanges[cell.rowID], !ranges.isEmpty {
            let raw = layoutEngine.layoutTextGlyphs(cell.text, variant: .monospace, at: .zero, color: textColor)
            codeGlyphs = applyHighlightColors(raw, ranges: ranges)
        } else {
            codeGlyphs = layoutEngine.layoutTextGlyphs(cell.text, variant: .monospace, at: .zero, color: textColor)
        }
        addTextGlyphs(codeGlyphs, offsetX: paneX + codeStartX + codeInsetX, baselineY: baselineY, fontSize: font.pointSize, builder: &builder)

        // Inline change highlight quads
        if !cell.inlineChanges.isEmpty {
            let highlightColor = cell.kind == .deleted ? deletedInlineBg : addedInlineBg
            for range in cell.inlineChanges {
                let clampedStart = min(range.start, cell.text.count)
                let clampedEnd = min(range.end, cell.text.count)
                guard clampedStart < clampedEnd else { continue }

                // Find glyph positions for the range
                let startGlyphX = glyphXForCharIndex(clampedStart, in: codeGlyphs)
                let endGlyphX = glyphXForCharIndex(clampedEnd, in: codeGlyphs)
                let hlX = paneX + codeStartX + codeInsetX + startGlyphX
                let hlWidth = endGlyphX - startGlyphX

                if hlWidth > 0 {
                    let hlQuad = VVQuadPrimitive(
                        frame: CGRect(x: hlX, y: y, width: hlWidth, height: height),
                        color: highlightColor
                    )
                    builder.add(kind: .quad(hlQuad), zIndex: 0)
                }
            }
        }
    }

    // MARK: - Helpers

    private func buildBadge(
        text: String,
        color: SIMD4<Float>,
        x: CGFloat, badgeY: CGFloat, badgeH: CGFloat, fontSize: CGFloat,
        baselineY: CGFloat,
        builder: inout VVSceneBuilder
    ) -> CGFloat {
        let glyphs = layoutEngine.layoutTextGlyphs(text, variant: .monospace, at: .zero, color: color)
        let textWidth = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
        let badgeWidth = textWidth + 12
        let badgeBg = VVQuadPrimitive(
            frame: CGRect(x: x, y: badgeY, width: badgeWidth, height: badgeH),
            color: withAlpha(color, 0.13),
            cornerRadius: 5
        )
        builder.add(kind: .quad(badgeBg))
        addTextGlyphs(glyphs, offsetX: x + 6, baselineY: baselineY, fontSize: fontSize, builder: &builder)
        return x + badgeWidth
    }

    private func buildMarkerIndicator(
        kind: VVDiffRow.Kind,
        x: CGFloat, y: CGFloat, width: CGFloat, height: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        let barWidth: CGFloat = 6

        switch kind {
        case .added:
            // Solid green bar, flush left, full height (connects between rows)
            let bar = VVQuadPrimitive(
                frame: CGRect(x: x, y: y, width: barWidth, height: height),
                color: addedMarkerColor
            )
            builder.add(kind: .quad(bar), zIndex: 1)

        case .deleted:
            // Dashed red bar, flush left, continuous pattern across rows
            let dashHeight: CGFloat = 1
            let gapHeight: CGFloat = 1
            let period = dashHeight + gapHeight
            // Align to global Y=0 so pattern is seamless across rows
            let phase = y.truncatingRemainder(dividingBy: period)
            var dashY = y - phase
            while dashY < y + height {
                let dashBottom = dashY + dashHeight
                // Clip to this row's bounds
                let clippedTop = max(dashY, y)
                let clippedBottom = min(dashBottom, y + height)
                if clippedBottom > clippedTop {
                    let dash = VVQuadPrimitive(
                        frame: CGRect(x: x, y: clippedTop, width: barWidth, height: clippedBottom - clippedTop),
                        color: deletedMarkerColor
                    )
                    builder.add(kind: .quad(dash), zIndex: 1)
                }
                dashY += period
            }

        default:
            break
        }
    }

    private func addTextGlyphs(
        _ glyphs: [MDLayoutGlyph],
        offsetX: CGFloat,
        baselineY: CGFloat,
        fontSize: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        guard !glyphs.isEmpty else { return }
        let vvGlyphs = glyphs.map { glyph -> VVTextGlyph in
            VVTextGlyph(
                glyphID: UInt16(glyph.glyphID),
                position: CGPoint(x: glyph.position.x + offsetX, y: baselineY),
                size: glyph.size,
                color: glyph.color,
                fontVariant: toVVFontVariant(glyph.fontVariant),
                fontSize: glyph.fontSize,
                fontName: glyph.fontName,
                stringIndex: glyph.stringIndex
            )
        }
        let run = VVTextRunPrimitive(
            glyphs: vvGlyphs,
            style: VVTextRunStyle(color: vvGlyphs.first?.color ?? textColor),
            position: CGPoint(x: offsetX, y: baselineY),
            fontSize: fontSize
        )
        builder.add(kind: .textRun(run))
    }

    private func applyHighlightColors(_ glyphs: [MDLayoutGlyph], ranges: [(NSRange, SIMD4<Float>)]) -> [MDLayoutGlyph] {
        glyphs.map { glyph in
            guard let idx = glyph.stringIndex else { return glyph }
            for (range, color) in ranges {
                if idx >= range.location && idx < range.location + range.length {
                    return MDLayoutGlyph(
                        glyphID: glyph.glyphID,
                        position: glyph.position,
                        size: glyph.size,
                        color: color,
                        fontVariant: glyph.fontVariant,
                        fontSize: glyph.fontSize,
                        fontName: glyph.fontName,
                        stringIndex: glyph.stringIndex
                    )
                }
            }
            return glyph
        }
    }

    private func glyphXForCharIndex(_ charIndex: Int, in glyphs: [MDLayoutGlyph]) -> CGFloat {
        for glyph in glyphs {
            if let si = glyph.stringIndex, si >= charIndex {
                return glyph.position.x
            }
        }
        return glyphs.last.map { $0.position.x + $0.size.width } ?? 0
    }

    private func rowBackgroundColor(for kind: VVDiffRow.Kind) -> SIMD4<Float> {
        switch kind {
        case .added: return addedBgColor
        case .deleted: return deletedBgColor
        case .hunkHeader: return hunkBgColor
        case .metadata: return metadataBgColor
        case .context: return backgroundColor
        case .fileHeader: return headerBgColor
        }
    }

    private func lineNumberColor(for kind: VVDiffRow.Kind) -> SIMD4<Float> {
        switch kind {
        case .added: return addedMarkerColor
        case .deleted: return deletedMarkerColor
        default: return gutterTextColor
        }
    }

    private func markerColor(for kind: VVDiffRow.Kind) -> SIMD4<Float> {
        switch kind {
        case .added: return addedMarkerColor
        case .deleted: return deletedMarkerColor
        case .hunkHeader: return modifiedColor
        case .fileHeader, .metadata, .context: return gutterTextColor
        }
    }

    private func diffMarker(for kind: VVDiffRow.Kind) -> String {
        switch kind {
        case .added: return "+"
        case .deleted: return "-"
        case .hunkHeader: return "@"
        case .context, .fileHeader, .metadata: return " "
        }
    }

    private func toVVFontVariant(_ variant: MDFontVariant) -> VVFontVariant {
        switch variant {
        case .regular: return .regular
        case .semibold: return .semibold
        case .semiboldItalic: return .semiboldItalic
        case .bold: return .bold
        case .italic: return .italic
        case .boldItalic: return .boldItalic
        case .monospace: return .monospace
        case .emoji: return .emoji
        }
    }

    private func withAlpha(_ color: SIMD4<Float>, _ alpha: Float) -> SIMD4<Float> {
        SIMD4(color.x, color.y, color.z, alpha)
    }

    private func rowsForFileHeader(_ header: VVDiffRow, allRows: [VVDiffRow]) -> [VVDiffRow] {
        var result: [VVDiffRow] = []
        var found = false
        for row in allRows {
            if row.id == header.id {
                found = true
                continue
            }
            if found {
                if row.kind == .fileHeader { break }
                result.append(row)
            }
        }
        return result
    }
}

// MARK: - VVDiffMetalView

/// Plain NSView used as the scroll view's documentView purely for content sizing.
private final class DiffDocumentView: NSView {
    override var isFlipped: Bool { true }
}

/// MTKView subclass that forwards mouse events to VVDiffMetalView.
private final class DiffMTKView: MTKView {
    weak var diffView: VVDiffMetalView?

    override func mouseDown(with event: NSEvent) {
        diffView?.mouseDown(with: event)
    }

    override func mouseDragged(with event: NSEvent) {
        diffView?.mouseDragged(with: event)
    }

    override func mouseUp(with event: NSEvent) {
        diffView?.mouseUp(with: event)
    }
}

private final class VVDiffMetalView: NSView {
    override var isFlipped: Bool { true }
    override var acceptsFirstResponder: Bool { true }

    private var scrollView: NSScrollView!
    private var documentView: DiffDocumentView!
    private var metalView: DiffMTKView!
    private var renderer: MarkdownMetalRenderer?
    private var diffRenderer: VVDiffRenderer?
    var metalContext: VVMetalContext?

    private var rows: [VVDiffRow] = []
    private var sections: [VVDiffSection] = []
    private var splitRows: [VVDiffSplitRow] = []
    private var renderStyle: VVDiffRenderStyle = .unifiedTable
    private var theme: VVTheme = .defaultDark
    private var configuration: VVConfiguration = .default
    private var language: VVLanguage?
    private var syntaxHighlightingEnabled: Bool = true
    private var onFileHeaderActivate: ((String) -> Void)?

    private var cachedScene: VVScene?
    private var contentHeight: CGFloat = 0
    private var currentDrawableSize: CGSize = .zero
    private var currentScrollOffset: CGPoint = .zero

    private var highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]] = [:]
    private var highlightGeneration: Int = 0
    private var highlightTask: Task<Void, Never>?
    private var codeRows: [VVDiffRow] = []
    private var codeRowIndexByID: [Int: Int] = [:]
    private var highlightedCodeRowCount: Int = 0
    private var pendingHighlightCodeRowCount: Int = 0

    private static let initialHighlightCodeRows: Int = 3_000
    private static let incrementalHighlightCodeRows: Int = 3_000
    private static let highlightPrefetchCodeRows: Int = 600
    private static let highlightViewportMargin: CGFloat = 220
    private static let highlightWarmupContextRows: Int = 192

    private var baseFont: NSFont = .monospacedSystemFont(ofSize: 13, weight: .regular)
    private var baseFontAscent: CGFloat = 0
    private var baseFontDescent: CGFloat = 0

    // Selection support
    private let selectionController = VVTextSelectionController<DiffTextPosition>()
    private let selectionColor: SIMD4<Float> = .rgba(0.24, 0.40, 0.65, 0.55)
    private var rowGeometries: [RowGeometry] = []
    private var filePathByHeaderRowID: [Int: String] = [:]
    private var rowGeometryCacheKey: RowGeometryCacheKey?
    private var rowGeometriesContentHeight: CGFloat = 0
    private var rowsSignature: Int = 0
    private var fastPlainModeEnabled: Bool = false
    private let codeInsetX: CGFloat = 10

    init(frame: CGRect, metalContext: VVMetalContext? = nil) {
        self.metalContext = metalContext ?? VVMetalContext.shared
        super.init(frame: frame)
        setup()
    }

    required init?(coder: NSCoder) {
        self.metalContext = VVMetalContext.shared
        super.init(coder: coder)
        setup()
    }

    deinit {
        highlightTask?.cancel()
        NotificationCenter.default.removeObserver(
            self,
            name: NSView.boundsDidChangeNotification,
            object: scrollView?.contentView
        )
    }

    private func setup() {
        wantsLayer = true

        // Document view exists only for scroll content sizing (same pattern as MetalTextView)
        documentView = DiffDocumentView(frame: bounds)

        scrollView = NSScrollView(frame: bounds)
        scrollView.autoresizingMask = [.width, .height]
        scrollView.hasVerticalScroller = true
        scrollView.hasHorizontalScroller = true
        scrollView.drawsBackground = false
        scrollView.autohidesScrollers = true
        scrollView.documentView = documentView
        scrollView.contentView.postsBoundsChangedNotifications = true

        let device = metalContext?.device ?? MTLCreateSystemDefaultDevice()
        guard let device else { return }

        // MTKView is a sibling of the document view, always sized to the visible viewport.
        // Scroll offset is passed to beginFrame so the renderer shifts primitives.
        metalView = DiffMTKView(frame: bounds, device: device)
        metalView.diffView = self
        metalView.isPaused = true
        metalView.enableSetNeedsDisplay = true
        metalView.framebufferOnly = true
        metalView.delegate = self
        metalView.layer?.isOpaque = true

        addSubview(scrollView)
        scrollView.addSubview(metalView)

        if let ctx = metalContext {
            renderer = MarkdownMetalRenderer(context: ctx, baseFont: baseFont, scaleFactor: NSScreen.main?.backingScaleFactor ?? 2.0)
        } else {
            renderer = nil
        }

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(scrollViewBoundsChanged),
            name: NSView.boundsDidChangeNotification,
            object: scrollView.contentView
        )
    }

    @objc private func scrollViewBoundsChanged(_ notification: Notification) {
        updateMetalViewport()
        requestViewportHighlightingIfNeeded()
        cachedScene = nil
        metalView.setNeedsDisplay(metalView.bounds)
    }

    override func layout() {
        super.layout()
        scrollView.frame = bounds
        updateContentSize()
        requestViewportHighlightingIfNeeded()
    }

    /// Keep MTKView pinned to the visible viewport (same as VVMetalEditorContainerView).
    private func updateMetalViewport() {
        let viewportSize = scrollView.contentView.bounds.size
        let viewportOrigin = scrollView.contentView.frame.origin
        currentScrollOffset = scrollView.contentView.bounds.origin
        metalView.frame = CGRect(origin: viewportOrigin, size: viewportSize)
    }

    private var wrapsUnified: Bool {
        configuration.wrapLines && renderStyle == .unifiedTable && !fastPlainModeEnabled
    }

    private static func computeRowsSignature(_ rows: [VVDiffRow]) -> Int {
        var hasher = Hasher()
        hasher.combine(rows.count)
        for row in rows {
            hasher.combine(row.id)
            hasher.combine(row.kind.rawValue)
            hasher.combine(row.oldLineNumber ?? -1)
            hasher.combine(row.newLineNumber ?? -1)
            hasher.combine(row.text.utf16.count)
        }
        return hasher.finalize()
    }

    private static func fontSignature(_ font: NSFont) -> Int {
        var hasher = Hasher()
        hasher.combine(font.fontName)
        hasher.combine(font.pointSize)
        return hasher.finalize()
    }

    private static func shouldUseFastPlainMode(rows: [VVDiffRow]) -> Bool {
        let maxRows = 3_500
        let maxTotalUTF16 = 200_000
        let maxChangedRows = 1_800

        if rows.count > maxRows {
            return true
        }

        var totalUTF16 = 0
        var changedRows = 0
        for row in rows where row.kind.isCode {
            totalUTF16 += row.text.utf16.count + 1
            if row.kind == .added || row.kind == .deleted {
                changedRows += 1
            }
            if totalUTF16 > maxTotalUTF16 || changedRows > maxChangedRows {
                return true
            }
        }

        return false
    }

    func update(
        rows: [VVDiffRow],
        style: VVDiffRenderStyle,
        theme: VVTheme,
        configuration: VVConfiguration,
        language: VVLanguage?,
        syntaxHighlightingEnabled: Bool,
        onFileHeaderActivate: ((String) -> Void)?
    ) {
        let nextFastPlainMode = Self.shouldUseFastPlainMode(rows: rows)
        let effectiveSyntaxHighlightingEnabled = syntaxHighlightingEnabled
        let fastPlainModeChanged = fastPlainModeEnabled != nextFastPlainMode
        let rowsChanged = self.rows != rows
        let styleChanged = self.renderStyle != style
        let themeChanged = self.theme != theme
        let fontChanged = self.configuration.font != configuration.font
        let wrapsChanged = self.configuration.wrapLines != configuration.wrapLines
        let langChanged = self.language?.identifier != language?.identifier
        let syntaxHighlightingChanged = self.syntaxHighlightingEnabled != effectiveSyntaxHighlightingEnabled
        let effectiveWrapChanged = wrapsChanged || styleChanged || fastPlainModeChanged

        if !rowsChanged,
           !styleChanged,
           !themeChanged,
           !fontChanged,
           !langChanged,
           !syntaxHighlightingChanged,
           !effectiveWrapChanged,
           rowGeometryCacheKey != nil {
            return
        }

        fastPlainModeEnabled = nextFastPlainMode
        self.rows = rows
        self.renderStyle = style
        self.theme = theme
        self.configuration = configuration
        self.language = language
        self.syntaxHighlightingEnabled = effectiveSyntaxHighlightingEnabled
        self.onFileHeaderActivate = onFileHeaderActivate
        rowsSignature = rowsChanged ? Self.computeRowsSignature(rows) : rowsSignature
        rowGeometryCacheKey = nil

        if rowsChanged {
            rebuildCodeRowLookup()
        }

        if style == .split {
            scrollView?.hasHorizontalScroller = true
        } else {
            scrollView?.hasHorizontalScroller = !wrapsUnified && !fastPlainModeEnabled
        }

        if fontChanged {
            baseFont = configuration.font
            baseFontAscent = CTFontGetAscent(baseFont)
            baseFontDescent = CTFontGetDescent(baseFont)
            let scale = window?.backingScaleFactor ?? NSScreen.main?.backingScaleFactor ?? 2.0
            if let ctx = metalContext {
                renderer = MarkdownMetalRenderer(context: ctx, baseFont: baseFont, scaleFactor: scale)
            }
        }

        if rowsChanged || styleChanged {
            sections = makeSections(from: rows)
            rebuildFileHeaderPathLookup()
            if style == .split {
                splitRows = makeSplitRows(from: rows)
            } else {
                splitRows = []
            }
        }

        if themeChanged || fontChanged {
            diffRenderer = nil
        }

        if rowsChanged || langChanged || fontChanged || syntaxHighlightingChanged {
            resetHighlightingState()
        }

        cachedScene = nil
        updateContentSize()
        requestViewportHighlightingIfNeeded()
        metalView?.setNeedsDisplay(metalView.bounds)
    }

    private func ensureDiffRenderer() -> VVDiffRenderer {
        if let existing = diffRenderer { return existing }
        let width = scrollView?.bounds.width ?? bounds.width
        let r = VVDiffRenderer(font: configuration.font, theme: theme, contentWidth: width)
        diffRenderer = r
        return r
    }

    private func updateContentSize() {
        let width = scrollView?.bounds.width ?? bounds.width
        let dr = ensureDiffRenderer()
        dr.updateContentWidth(width)
        buildRowGeometries(width: width)
        contentHeight = rowGeometriesContentHeight
        cachedScene = nil

        let wrapsUnified = self.wrapsUnified

        // Compute max line width for horizontal scrolling
        let maxLineWidth: CGFloat
        if wrapsUnified || fastPlainModeEnabled {
            maxLineWidth = width
        } else {
            maxLineWidth = rowGeometries.map { geo in
                geo.codeStartX + codeInsetX + CGFloat(geo.text.count) * dr.charWidth + 20
            }.max() ?? width
        }

        let minWidth: CGFloat
        if renderStyle == .split {
            minWidth = 840 // 420 * 2
        } else if wrapsUnified || fastPlainModeEnabled {
            minWidth = width
        } else {
            minWidth = max(width, 520)
        }

        // Size the document view for scroll bars; MTKView stays viewport-sized
        let docWidth = (wrapsUnified || fastPlainModeEnabled) ? width : max(maxLineWidth, minWidth, width)
        let docHeight = max(contentHeight, scrollView.bounds.height)
        documentView.frame = CGRect(x: 0, y: 0, width: docWidth, height: docHeight)
        updateMetalViewport()
    }

    private func buildRowGeometries(width: CGFloat) {
        let widthBucket = Int((width * 2).rounded())
        let cacheKey = RowGeometryCacheKey(
            rowsSignature: rowsSignature,
            style: renderStyle,
            widthBucket: widthBucket,
            wrapsUnified: wrapsUnified,
            fontSignature: Self.fontSignature(configuration.font)
        )
        if rowGeometryCacheKey == cacheKey {
            return
        }

        rowGeometries.removeAll(keepingCapacity: true)
        let dr = ensureDiffRenderer()

        switch renderStyle {
        case .unifiedTable:
            buildRowGeometriesUnified(width: width, renderer: dr, wrapLines: wrapsUnified)
        case .split:
            buildRowGeometriesSplit(width: width, renderer: dr)
        }

        rowGeometriesContentHeight = rowGeometries.last.map { $0.y + $0.height } ?? 0
        rowGeometryCacheKey = cacheKey
    }

    private func buildRowGeometriesUnified(width: CGFloat, renderer: VVDiffRenderer, wrapLines: Bool) {
        let maxOld = rows.compactMap(\.oldLineNumber).max() ?? 0
        let maxNew = rows.compactMap(\.newLineNumber).max() ?? 0
        let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
        let gutterColWidth = CGFloat(gutterDigits) * renderer.charWidth + 16
        let markerWidth = renderer.charWidth + 8
        let codeStartX = gutterColWidth * 2 + markerWidth
        let maxCharsPerVisualLine = wrapCapacity(totalWidth: width, codeStartX: codeStartX, charWidth: renderer.charWidth)

        var y: CGFloat = 0
        var rowIndex = 0

        for section in sections {
            // File header
            if let header = section.headerRow {
                let rowH = renderer.headerHeight
                rowGeometries.append(RowGeometry(
                    rowIndex: rowIndex,
                    rowID: header.id,
                    y: y,
                    height: rowH,
                    isCodeRow: false,
                    text: header.text,
                    codeStartX: codeStartX,
                    paneX: 0,
                    paneWidth: width
                ))
                y += rowH
                rowIndex += 1
            }

            // Section rows (skip metadata)
            for row in section.rows {
                if row.kind == .metadata { continue }
                let wrappedLines: [String]
                if wrapLines && (row.kind.isCode || row.kind == .hunkHeader) {
                    wrappedLines = wrappedTextSegments(row.text, maxChars: maxCharsPerVisualLine)
                } else {
                    wrappedLines = [row.text]
                }

                for line in wrappedLines {
                    let rowH = renderer.lineHeight
                    rowGeometries.append(RowGeometry(
                        rowIndex: rowIndex,
                        rowID: row.id,
                        y: y,
                        height: rowH,
                        isCodeRow: row.kind.isCode,
                        text: line,
                        codeStartX: codeStartX,
                        paneX: 0,
                        paneWidth: width
                    ))
                    y += rowH
                    rowIndex += 1
                }
            }
        }
    }

    private func wrapCapacity(totalWidth: CGFloat, codeStartX: CGFloat, charWidth: CGFloat) -> Int {
        let available = max(0, totalWidth - codeStartX - codeInsetX - 12)
        guard available > 0 else { return 1 }
        return max(1, Int(floor(available / max(charWidth, 1))))
    }

    private func wrappedTextSegments(_ text: String, maxChars: Int) -> [String] {
        guard maxChars > 0 else { return [text] }
        var result: [String] = []
        let logicalLines = text.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        for line in logicalLines {
            if line.isEmpty {
                result.append("")
                continue
            }
            var start = line.startIndex
            while start < line.endIndex {
                let end = line.index(start, offsetBy: maxChars, limitedBy: line.endIndex) ?? line.endIndex
                result.append(String(line[start..<end]))
                start = end
            }
        }
        return result.isEmpty ? [""] : result
    }

    private func buildRowGeometriesSplit(width: CGFloat, renderer: VVDiffRenderer) {
        let maxOld = rows.compactMap(\.oldLineNumber).max() ?? 0
        let maxNew = rows.compactMap(\.newLineNumber).max() ?? 0
        let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
        let gutterColWidth = CGFloat(gutterDigits) * renderer.charWidth + 16
        let markerWidth = renderer.charWidth + 4
        let columnWidth = max(420, floor(width / 2))
        let paneCodeStartX = markerWidth + gutterColWidth

        var y: CGFloat = 0
        var rowIndex = 0

        for splitRow in splitRows {
            if let header = splitRow.header {
                let rowH = header.kind == .fileHeader ? renderer.headerHeight : renderer.lineHeight
                rowGeometries.append(RowGeometry(
                    rowIndex: rowIndex,
                    rowID: header.id,
                    y: y,
                    height: rowH,
                    isCodeRow: false,
                    text: header.text,
                    codeStartX: paneCodeStartX,
                    paneX: 0,
                    paneWidth: columnWidth * 2
                ))
                y += rowH
                rowIndex += 1
            } else {
                let rowH = renderer.lineHeight
                // Add left cell if present
                if let left = splitRow.left {
                    rowGeometries.append(RowGeometry(
                        rowIndex: rowIndex,
                        rowID: left.rowID,
                        y: y,
                        height: rowH,
                        isCodeRow: left.kind.isCode,
                        text: left.text,
                        codeStartX: paneCodeStartX,
                        paneX: 0,
                        paneWidth: columnWidth
                    ))
                    rowIndex += 1
                }
                // Add right cell if present
                if let right = splitRow.right {
                    rowGeometries.append(RowGeometry(
                        rowIndex: rowIndex,
                        rowID: right.rowID,
                        y: y,
                        height: rowH,
                        isCodeRow: right.kind.isCode,
                        text: right.text,
                        codeStartX: paneCodeStartX,
                        paneX: columnWidth,
                        paneWidth: columnWidth
                    ))
                    rowIndex += 1
                }
                y += rowH
            }
        }
    }

    private func rebuildFileHeaderPathLookup() {
        filePathByHeaderRowID.removeAll(keepingCapacity: true)
        filePathByHeaderRowID.reserveCapacity(sections.count)
        for section in sections {
            guard let header = section.headerRow else { continue }
            filePathByHeaderRowID[header.id] = section.filePath
        }
    }

    // MARK: - Syntax Highlighting

    private func rebuildCodeRowLookup() {
        codeRows = rows.filter { $0.kind.isCode }
        codeRowIndexByID.removeAll(keepingCapacity: true)
        codeRowIndexByID.reserveCapacity(codeRows.count)
        for (index, row) in codeRows.enumerated() {
            codeRowIndexByID[row.id] = index
        }
    }

    private func resetHighlightingState() {
        highlightGeneration += 1
        highlightTask?.cancel()
        highlightTask = nil
        highlightedRanges = [:]
        highlightedCodeRowCount = 0
        pendingHighlightCodeRowCount = 0

        guard syntaxHighlightingEnabled else { return }
        guard !codeRows.isEmpty else { return }

        scheduleHighlightingIfNeeded(targetCodeRowCount: min(codeRows.count, Self.initialHighlightCodeRows))
    }

    private func requestViewportHighlightingIfNeeded() {
        guard syntaxHighlightingEnabled else { return }
        guard !codeRows.isEmpty else { return }
        let targetCount = desiredHighlightedCodeRowCountForVisibleViewport()
        scheduleHighlightingIfNeeded(targetCodeRowCount: targetCount)
    }

    private func desiredHighlightedCodeRowCountForVisibleViewport() -> Int {
        let initialTarget = min(codeRows.count, Self.initialHighlightCodeRows)
        guard let scrollView else { return initialTarget }

        let visibleRect = scrollView.contentView.bounds
        guard let maxVisibleCodeIndex = maxVisibleCodeRowIndex(in: visibleRect) else {
            return initialTarget
        }

        let desiredByViewport = min(
            codeRows.count,
            maxVisibleCodeIndex + 1 + Self.highlightPrefetchCodeRows
        )
        if desiredByViewport <= initialTarget {
            return initialTarget
        }

        let extraNeeded = desiredByViewport - initialTarget
        let chunkCount = Int(ceil(Double(extraNeeded) / Double(Self.incrementalHighlightCodeRows)))
        return min(codeRows.count, initialTarget + chunkCount * Self.incrementalHighlightCodeRows)
    }

    private func firstVisibleGeometryIndex(minY: CGFloat) -> Int {
        var low = 0
        var high = rowGeometries.count

        while low < high {
            let mid = (low + high) / 2
            let geometry = rowGeometries[mid]
            if geometry.y + geometry.height < minY {
                low = mid + 1
            } else {
                high = mid
            }
        }

        return min(low, rowGeometries.count)
    }

    private func maxVisibleCodeRowIndex(in visibleRect: CGRect) -> Int? {
        guard !rowGeometries.isEmpty else { return nil }

        let minY = visibleRect.minY - Self.highlightViewportMargin
        let maxY = visibleRect.maxY + Self.highlightViewportMargin
        let startIndex = firstVisibleGeometryIndex(minY: minY)

        var maxCodeIndex: Int?
        var index = startIndex
        while index < rowGeometries.count {
            let geometry = rowGeometries[index]
            if geometry.y > maxY {
                break
            }
            if let codeIndex = codeRowIndexByID[geometry.rowID] {
                if let current = maxCodeIndex {
                    maxCodeIndex = max(current, codeIndex)
                } else {
                    maxCodeIndex = codeIndex
                }
            }
            index += 1
        }

        return maxCodeIndex
    }

    private func scheduleHighlightingIfNeeded(targetCodeRowCount: Int) {
        let boundedTarget = min(codeRows.count, max(0, targetCodeRowCount))
        guard boundedTarget > highlightedCodeRowCount else { return }

        pendingHighlightCodeRowCount = max(pendingHighlightCodeRowCount, boundedTarget)
        startNextHighlightBatchIfNeeded()
    }

    private func startNextHighlightBatchIfNeeded() {
        guard highlightTask == nil else { return }
        guard pendingHighlightCodeRowCount > highlightedCodeRowCount else { return }

        let generation = highlightGeneration
        let startIndex = highlightedCodeRowCount
        let batchLimit = startIndex == 0 ? Self.initialHighlightCodeRows : Self.incrementalHighlightCodeRows
        let endIndex = min(codeRows.count, min(pendingHighlightCodeRowCount, startIndex + batchLimit))

        guard endIndex > startIndex else { return }

        let warmupRows = min(Self.highlightWarmupContextRows, startIndex)
        let parseStart = startIndex - warmupRows
        let batchRows = Array(codeRows[parseStart..<endIndex])
        let targetRowIDs = Set(codeRows[startIndex..<endIndex].map(\.id))
        let currentLanguage = language
        let currentTheme = theme
        let currentFont = configuration.font

        highlightTask = Task(priority: .userInitiated) { [weak self] in
            guard !Task.isCancelled else { return }
            let ranges = await Self.computeHighlightRanges(
                rows: batchRows,
                language: currentLanguage,
                theme: currentTheme,
                font: currentFont
            )
            guard !Task.isCancelled else { return }

            await MainActor.run { [weak self] in
                guard let self, self.highlightGeneration == generation, !Task.isCancelled else { return }
                for (rowID, rowRanges) in ranges {
                    guard targetRowIDs.contains(rowID) else { continue }
                    self.highlightedRanges[rowID] = rowRanges
                }
                self.highlightedCodeRowCount = max(self.highlightedCodeRowCount, endIndex)
                self.highlightTask = nil
                self.cachedScene = nil
                self.metalView?.setNeedsDisplay(self.metalView.bounds)
                self.startNextHighlightBatchIfNeeded()
            }
        }
    }

    private static func computeHighlightRanges(
        rows: [VVDiffRow],
        language: VVLanguage?,
        theme: VVTheme,
        font: NSFont
    ) async -> [Int: [(NSRange, SIMD4<Float>)]] {
        let codeRows = rows.filter { $0.kind.isCode }
        guard !codeRows.isEmpty,
              let language,
              let languageConfig = LanguageRegistry.shared.language(for: language.identifier) else {
            return [:]
        }

        // Guardrails: skip expensive highlighting for large or pathological diffs.
        let maxHighlightRows = 3_500
        let maxHighlightUTF16 = 360_000
        let maxSingleLineUTF16 = 8_192
        guard codeRows.count <= maxHighlightRows else { return [:] }
        var totalUTF16 = 0
        for row in codeRows {
            if Task.isCancelled { return [:] }
            let rowUTF16 = row.text.utf16.count
            if rowUTF16 > maxSingleLineUTF16 { return [:] }
            totalUTF16 += rowUTF16 + 1
            if totalUTF16 > maxHighlightUTF16 {
                return [:]
            }
        }

        let highlightTheme: HighlightTheme = theme.backgroundColor.brightnessComponent < 0.5
            ? .defaultDark
            : .defaultLight

        let highlighter = TreeSitterHighlighter(theme: highlightTheme)
        let joined = makeJoinedCodeBuffer(from: rows)

        do {
            try await highlighter.setLanguage(languageConfig)
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

            for (rowID, rowNSRange) in sortedRows {
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

                        let attrs = range.style.attributes(baseFont: font)
                        let nsColor = attrs[.foregroundColor] as? NSColor ?? NSColor.white
                        let color = nsColor.simdColor

                        rowRanges.append((localRange, color))
                    }
                    index += 1
                }
                if !rowRanges.isEmpty {
                    result[rowID] = rowRanges
                }
            }

            return result
        } catch {
            return [:]
        }
    }

    override func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        if window == nil {
            metalView?.releaseDrawables()
        }
    }

    override func viewDidHide() {
        super.viewDidHide()
        metalView?.releaseDrawables()
    }

    override func viewDidUnhide() {
        super.viewDidUnhide()
        metalView?.setNeedsDisplay(metalView.bounds)
    }
}

// MARK: - MTKViewDelegate

extension VVDiffMetalView: MTKViewDelegate {
    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {
        currentDrawableSize = size
    }

    func draw(in view: MTKView) {
        guard let renderer,
              let drawable = view.currentDrawable else { return }

        let dr = ensureDiffRenderer()
        let bg = dr.backgroundColor

        let commandBuffer = renderer.commandQueue.makeCommandBuffer()
        currentDrawableSize = CGSize(width: drawable.texture.width, height: drawable.texture.height)

        let passDescriptor = MTLRenderPassDescriptor()
        passDescriptor.colorAttachments[0].texture = drawable.texture
        passDescriptor.colorAttachments[0].loadAction = .clear
        passDescriptor.colorAttachments[0].storeAction = .store
        passDescriptor.colorAttachments[0].clearColor = MTLClearColor(
            red: Double(bg.x), green: Double(bg.y), blue: Double(bg.z), alpha: Double(bg.w)
        )

        guard let encoder = commandBuffer?.makeRenderCommandEncoder(descriptor: passDescriptor) else { return }

        // MTKView is viewport-sized. Primitives use absolute document coordinates.
        // Pass scroll offset so the projection shifts them into the visible window
        // (same pattern as MetalTextView.draw).
        let scrollOffset = scrollView.contentView.bounds.origin
        currentScrollOffset = scrollOffset
        renderer.beginFrame(viewportSize: view.bounds.size, scrollOffset: scrollOffset)

        // Build or reuse scene
        let visibleRect = scrollView.contentView.bounds
        let scene: VVScene
        if let cached = cachedScene {
            scene = cached
        } else {
            let wrapsUnified = self.wrapsUnified
            let renderWidth = (wrapsUnified || fastPlainModeEnabled)
                ? scrollView.bounds.width
                : max(scrollView.bounds.width, documentView.frame.width)
            dr.updateContentWidth(scrollView.bounds.width)
            let result: (scene: VVScene, contentHeight: CGFloat)
            switch renderStyle {
            case .unifiedTable:
                result = dr.buildUnifiedScene(
                    sections: sections, rows: rows,
                    width: renderWidth,
                    viewport: visibleRect,
                    highlightedRanges: highlightedRanges,
                    wrapLines: wrapsUnified,
                    measureFullHeight: false
                )
            case .split:
                result = dr.buildSplitScene(
                    splitRows: splitRows, rows: rows,
                    width: renderWidth,
                    viewport: visibleRect,
                    highlightedRanges: highlightedRanges,
                    measureFullHeight: false
                )
            }
            scene = result.scene
            cachedScene = scene
        }

        renderScene(scene, encoder: encoder, renderer: renderer)

        // Render selection quads on top of scene (so they're visible over opaque row backgrounds)
        if let selection = selectionController.selection {
            let quads = selectionQuads(
                from: selection.ordered.start,
                to: selection.ordered.end,
                color: selectionColor
            )
            for quad in quads {
                let instance = QuadInstance(
                    position: SIMD2<Float>(Float(quad.frame.origin.x), Float(quad.frame.origin.y)),
                    size: SIMD2<Float>(Float(quad.frame.width), Float(quad.frame.height)),
                    color: quad.color,
                    cornerRadius: Float(quad.cornerRadius)
                )
                if let buffer = renderer.makeBuffer(for: [instance]) {
                    renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: quad.cornerRadius > 0)
                }
            }
        }

        encoder.endEncoding()
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
    }

    private func renderScene(
        _ scene: VVScene,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        var glyphInstances: [Int: [MarkdownGlyphInstance]] = [:]
        var colorGlyphInstances: [Int: [MarkdownGlyphInstance]] = [:]

        func flushTextBatches() {
            if !glyphInstances.isEmpty || !colorGlyphInstances.isEmpty {
                renderGlyphBatches(glyphInstances, encoder: encoder, renderer: renderer, isColor: false)
                renderGlyphBatches(colorGlyphInstances, encoder: encoder, renderer: renderer, isColor: true)
            }
            glyphInstances.removeAll(keepingCapacity: true)
            colorGlyphInstances.removeAll(keepingCapacity: true)
        }

        for primitive in scene.orderedPrimitives() {
            switch primitive.kind {
            case .textRun(let run):
                for glyph in run.glyphs {
                    appendGlyphInstance(glyph, renderer: renderer, glyphInstances: &glyphInstances, colorGlyphInstances: &colorGlyphInstances)
                }

            default:
                flushTextBatches()
                renderPrimitive(primitive, encoder: encoder, renderer: renderer)
            }
        }

        flushTextBatches()
    }

    private func renderPrimitive(
        _ primitive: VVPrimitive,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        switch primitive.kind {
        case .quad(let quad):
            let instance = QuadInstance(
                position: SIMD2<Float>(Float(quad.frame.origin.x), Float(quad.frame.origin.y)),
                size: SIMD2<Float>(Float(quad.frame.width), Float(quad.frame.height)),
                color: quad.color,
                cornerRadius: Float(quad.cornerRadius)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: quad.cornerRadius > 0)
            }

        case .line(let line):
            let minX = min(line.start.x, line.end.x)
            let minY = min(line.start.y, line.end.y)
            let width = abs(line.end.x - line.start.x)
            let height = abs(line.end.y - line.start.y)
            let rectWidth = width > 0 ? width : line.thickness
            let rectHeight = height > 0 ? height : line.thickness
            let instance = LineInstance(
                position: SIMD2<Float>(Float(minX), Float(minY)),
                width: Float(rectWidth),
                height: Float(rectHeight),
                color: line.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        default:
            break
        }
    }

    private func appendGlyphInstance(
        _ glyph: VVTextGlyph,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]]
    ) {
        let layoutVariant = toLayoutFontVariant(glyph.fontVariant)
        let cgGlyph = CGGlyph(glyph.glyphID)

        let cached: MarkdownCachedGlyph?
        if let fontName = glyph.fontName {
            cached = renderer.glyphAtlas.glyph(for: cgGlyph, fontName: fontName, fontSize: glyph.fontSize, variant: layoutVariant)
        } else {
            cached = renderer.glyphAtlas.glyph(for: cgGlyph, variant: layoutVariant, fontSize: glyph.fontSize, baseFont: renderer.baseFont)
        }

        guard let cached else { return }
        let glyphColor = cached.isColor ? SIMD4<Float>(1, 1, 1, glyph.color.w) : glyph.color
        let instance = MarkdownGlyphInstance(
            position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x), Float(glyph.position.y + cached.bearing.y)),
            size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
            uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
            uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
            color: glyphColor,
            atlasIndex: UInt32(cached.atlasIndex)
        )
        if cached.isColor {
            colorGlyphInstances[cached.atlasIndex, default: []].append(instance)
        } else {
            glyphInstances[cached.atlasIndex, default: []].append(instance)
        }
    }

    private func renderGlyphBatches(
        _ batches: [Int: [MarkdownGlyphInstance]],
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        isColor: Bool
    ) {
        guard !batches.isEmpty else { return }
        let textures = isColor ? renderer.glyphAtlas.allColorAtlasTextures : renderer.glyphAtlas.allAtlasTextures
        for atlasIndex in batches.keys.sorted() {
            guard atlasIndex >= 0 && atlasIndex < textures.count else { continue }
            guard let instances = batches[atlasIndex], !instances.isEmpty else { continue }
            guard let buffer = renderer.makeBuffer(for: instances) else { continue }
            if isColor {
                renderer.renderColorGlyphs(encoder: encoder, instances: buffer, instanceCount: instances.count, texture: textures[atlasIndex])
            } else {
                renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: instances.count, texture: textures[atlasIndex])
            }
        }
    }

    private func toLayoutFontVariant(_ variant: VVFontVariant) -> MDFontVariant {
        switch variant {
        case .regular: return .regular
        case .semibold: return .semibold
        case .semiboldItalic: return .semiboldItalic
        case .bold: return .bold
        case .italic: return .italic
        case .boldItalic: return .boldItalic
        case .monospace: return .monospace
        case .emoji: return .emoji
        }
    }

    // MARK: - Selection Support

    private func viewPointToDocumentPoint(_ point: CGPoint) -> CGPoint {
        let scrollOffset = scrollView.contentView.bounds.origin
        return CGPoint(x: point.x + scrollOffset.x, y: point.y + scrollOffset.y)
    }

    private func findRow(at y: CGFloat, x: CGFloat? = nil) -> RowGeometry? {
        guard !rowGeometries.isEmpty else { return nil }

        // Clamp to first/last row when outside bounds
        if y < rowGeometries.first!.y {
            return rowGeometries.first
        }
        let last = rowGeometries.last!
        if y >= last.y + last.height {
            return last
        }

        // Binary search by Y coordinate
        var low = 0
        var high = rowGeometries.count - 1

        while low <= high {
            let mid = (low + high) / 2
            let geo = rowGeometries[mid]

            if y < geo.y {
                high = mid - 1
            } else if y >= geo.y + geo.height {
                low = mid + 1
            } else {
                // Found a row at this Y. If X filtering is requested (split mode),
                // pick the row whose pane contains the X coordinate.
                if let x = x {
                    // Look for all rows at this same Y position
                    var candidates: [RowGeometry] = [geo]
                    // Check neighbors (split rows share the same Y)
                    for offset in [mid - 1, mid + 1] {
                        if offset >= 0 && offset < rowGeometries.count {
                            let neighbor = rowGeometries[offset]
                            if neighbor.y == geo.y {
                                candidates.append(neighbor)
                            }
                        }
                    }
                    // Return the row whose pane contains the X click
                    return candidates.first(where: { x >= $0.paneX && x < $0.paneX + $0.paneWidth }) ?? geo
                }
                return geo
            }
        }

        return rowGeometries[low < rowGeometries.count ? low : rowGeometries.count - 1]
    }

    private func invalidateAndRedraw() {
        metalView.setNeedsDisplay(metalView.bounds)
    }

    // MARK: - Mouse Events

    override func mouseDown(with event: NSEvent) {
        window?.makeFirstResponder(self)
        let point = convert(event.locationInWindow, from: nil)

        if event.clickCount == 1,
           let filePath = fileHeaderPath(at: point) {
            onFileHeaderActivate?(filePath)
            return
        }

        selectionController.handleMouseDown(
            at: point,
            clickCount: event.clickCount,
            modifiers: event.modifierFlags,
            hitTester: self
        )
        invalidateAndRedraw()
    }

    override func mouseDragged(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        selectionController.handleMouseDragged(to: point, hitTester: self)
        _ = autoscroll(with: event)
        invalidateAndRedraw()
    }

    override func mouseUp(with event: NSEvent) {
        selectionController.handleMouseUp()
    }

    private func fileHeaderPath(at point: CGPoint) -> String? {
        let docPoint = viewPointToDocumentPoint(point)
        let row: RowGeometry?
        if renderStyle == .split {
            row = findRow(at: docPoint.y, x: docPoint.x)
        } else {
            row = findRow(at: docPoint.y)
        }
        guard let row else { return nil }
        return filePathByHeaderRowID[row.rowID]
    }

    // MARK: - Keyboard Events

    override func performKeyEquivalent(with event: NSEvent) -> Bool {
        if event.modifierFlags.contains(.command),
           let chars = event.charactersIgnoringModifiers?.lowercased() {
            switch chars {
            case "c":
                copySelection()
                return true
            case "a":
                selectAll(nil)
                return true
            default:
                break
            }
        }
        return super.performKeyEquivalent(with: event)
    }

    @IBAction func copy(_ sender: Any?) {
        copySelection()
    }

    private func copySelection() {
        guard let selection = selectionController.selection else { return }
        let text = extractText(from: selection.ordered.start, to: selection.ordered.end)
        guard !text.isEmpty else { return }
        NSPasteboard.general.clearContents()
        NSPasteboard.general.setString(text, forType: .string)
    }

    @IBAction override func selectAll(_ sender: Any?) {
        guard !rowGeometries.isEmpty else { return }
        let first = DiffTextPosition(rowIndex: 0, charOffset: 0)
        let last = DiffTextPosition(rowIndex: rowGeometries.count - 1, charOffset: rowGeometries.last!.text.count)
        selectionController.selectAll(from: first, to: last)
        invalidateAndRedraw()
    }
}

// MARK: - VVTextHitTestable

extension VVDiffMetalView: VVTextHitTestable {
    func hitTest(at point: CGPoint) -> DiffTextPosition? {
        let docPoint = viewPointToDocumentPoint(point)

        // In split mode, find the row matching both Y and the correct pane (by X)
        let geo: RowGeometry?
        if renderStyle == .split {
            geo = findRow(at: docPoint.y, x: docPoint.x)
        } else {
            geo = findRow(at: docPoint.y)
        }
        guard let geo else { return nil }

        // For non-code rows, return position at start of row
        guard geo.isCodeRow else {
            return DiffTextPosition(rowIndex: geo.rowIndex, charOffset: 0, paneX: geo.paneX)
        }

        let dr = ensureDiffRenderer()

        // Convert X to character offset (monospace: relativeX / charWidth)
        let relativeX = docPoint.x - geo.paneX - geo.codeStartX - codeInsetX
        let charOffset = max(0, min(Int(relativeX / dr.charWidth), geo.text.count))

        return DiffTextPosition(rowIndex: geo.rowIndex, charOffset: charOffset, paneX: geo.paneX)
    }
}

// MARK: - VVTextSelectionRenderer

extension VVDiffMetalView: VVTextSelectionRenderer {
    func selectionQuads(from start: DiffTextPosition, to end: DiffTextPosition, color: SIMD4<Float>) -> [VVQuadPrimitive] {
        var quads: [VVQuadPrimitive] = []
        let dr = ensureDiffRenderer()
        let selectionPane = start.paneX

        for geo in rowGeometries {
            guard geo.rowIndex >= start.rowIndex && geo.rowIndex <= end.rowIndex else { continue }

            // In split mode, only select rows within the same pane
            if renderStyle == .split && geo.paneX != selectionPane { continue }

            // For non-code rows (hunk headers, file headers), draw full-width highlight
            guard geo.isCodeRow else {
                // Only fill non-code rows that are fully interior to the selection
                if geo.rowIndex > start.rowIndex && geo.rowIndex < end.rowIndex {
                    let quadPaneX = renderStyle == .split ? selectionPane : geo.paneX
                    let quadPaneW = renderStyle == .split ? geo.paneWidth / 2 : geo.paneWidth
                    quads.append(VVQuadPrimitive(
                        frame: CGRect(x: quadPaneX, y: geo.y, width: quadPaneW, height: geo.height),
                        color: color,
                        cornerRadius: 0
                    ))
                }
                continue
            }

            let startChar: Int
            let endChar: Int
            let extendToEnd: Bool  // extend selection to pane edge

            if geo.rowIndex == start.rowIndex && geo.rowIndex == end.rowIndex {
                startChar = start.charOffset
                endChar = end.charOffset
                extendToEnd = false
            } else if geo.rowIndex == start.rowIndex {
                startChar = start.charOffset
                endChar = geo.text.count
                extendToEnd = true
            } else if geo.rowIndex == end.rowIndex {
                startChar = 0
                endChar = end.charOffset
                extendToEnd = false
            } else {
                startChar = 0
                endChar = geo.text.count
                extendToEnd = true
            }

            guard extendToEnd || startChar < endChar else { continue }

            let startX = geo.paneX + geo.codeStartX + codeInsetX + CGFloat(startChar) * dr.charWidth
            let endX: CGFloat
            if extendToEnd {
                endX = geo.paneX + geo.paneWidth
            } else {
                endX = geo.paneX + geo.codeStartX + codeInsetX + CGFloat(endChar) * dr.charWidth
            }

            guard endX > startX else { continue }

            quads.append(VVQuadPrimitive(
                frame: CGRect(x: startX, y: geo.y, width: endX - startX, height: geo.height),
                color: color
            ))
        }

        return quads
    }
}

// MARK: - VVTextExtractor

extension VVDiffMetalView: VVTextExtractor {
    func extractText(from start: DiffTextPosition, to end: DiffTextPosition) -> String {
        var lines: [String] = []
        let selectionPane = start.paneX

        for geo in rowGeometries {
            guard geo.rowIndex >= start.rowIndex && geo.rowIndex <= end.rowIndex else { continue }
            // In split mode, only extract text from the same pane
            if renderStyle == .split && geo.paneX != selectionPane { continue }
            guard geo.isCodeRow else { continue }

            let text = geo.text
            if geo.rowIndex == start.rowIndex && geo.rowIndex == end.rowIndex {
                let startIdx = text.index(text.startIndex, offsetBy: min(start.charOffset, text.count))
                let endIdx = text.index(text.startIndex, offsetBy: min(end.charOffset, text.count))
                lines.append(String(text[startIdx..<endIdx]))
            } else if geo.rowIndex == start.rowIndex {
                let startIdx = text.index(text.startIndex, offsetBy: min(start.charOffset, text.count))
                lines.append(String(text[startIdx...]))
            } else if geo.rowIndex == end.rowIndex {
                let endIdx = text.index(text.startIndex, offsetBy: min(end.charOffset, text.count))
                lines.append(String(text[..<endIdx]))
            } else {
                lines.append(text)
            }
        }

        return lines.joined(separator: "\n")
    }
}

// MARK: - VVDiffViewRepresentable

private struct VVDiffViewRepresentable: NSViewRepresentable {
    let unifiedDiff: String
    let language: VVLanguage?
    let theme: VVTheme
    let configuration: VVConfiguration
    let renderStyle: VVDiffRenderStyle
    let syntaxHighlightingEnabled: Bool
    let onFileHeaderActivate: ((String) -> Void)?

    func makeCoordinator() -> Coordinator {
        Coordinator()
    }

    final class Coordinator {
        private var lastUnifiedDiff: String?
        private var cachedRows: [VVDiffRow] = []

        func rows(for unifiedDiff: String) -> [VVDiffRow] {
            if let lastUnifiedDiff, lastUnifiedDiff == unifiedDiff {
                return cachedRows
            }
            let parsed = parseDiffRows(unifiedDiff: unifiedDiff)
            lastUnifiedDiff = unifiedDiff
            cachedRows = parsed
            return parsed
        }
    }

    func makeNSView(context: Context) -> VVDiffMetalView {
        let view = VVDiffMetalView(frame: .zero)
        let rows = context.coordinator.rows(for: unifiedDiff)
        view.update(
            rows: rows,
            style: renderStyle,
            theme: theme,
            configuration: configuration,
            language: language,
            syntaxHighlightingEnabled: syntaxHighlightingEnabled,
            onFileHeaderActivate: onFileHeaderActivate
        )
        return view
    }

    func updateNSView(_ nsView: VVDiffMetalView, context: Context) {
        let rows = context.coordinator.rows(for: unifiedDiff)
        nsView.update(
            rows: rows,
            style: renderStyle,
            theme: theme,
            configuration: configuration,
            language: language,
            syntaxHighlightingEnabled: syntaxHighlightingEnabled,
            onFileHeaderActivate: onFileHeaderActivate
        )
    }
}

// MARK: - Public API

/// High-level diff component. Parses unified diff text and renders it through Metal.
public struct VVDiffView: View {
    private let unifiedDiff: String
    private var language: VVLanguage?
    private var theme: VVTheme
    private var configuration: VVConfiguration
    private var renderStyle: VVDiffRenderStyle
    private var syntaxHighlightingEnabled: Bool
    private var onFileHeaderActivate: ((String) -> Void)?

    public init(unifiedDiff: String) {
        self.unifiedDiff = unifiedDiff
        self.language = nil
        self.theme = .defaultDark
        self.configuration = .default
        self.renderStyle = .unifiedTable
        self.syntaxHighlightingEnabled = true
        self.onFileHeaderActivate = nil
    }

    public var body: some View {
        VVDiffViewRepresentable(
            unifiedDiff: unifiedDiff,
            language: effectiveLanguage,
            theme: theme,
            configuration: configuration,
            renderStyle: renderStyle,
            syntaxHighlightingEnabled: syntaxHighlightingEnabled,
            onFileHeaderActivate: onFileHeaderActivate
        )
    }

    private var effectiveLanguage: VVLanguage? {
        if let language {
            return language
        }

        for line in unifiedDiff.components(separatedBy: .newlines) where line.hasPrefix("+++ ") {
            let path = line
                .replacingOccurrences(of: "+++ b/", with: "")
                .replacingOccurrences(of: "+++ ", with: "")

            if path == "/dev/null" {
                continue
            }

            let url = URL(fileURLWithPath: path)
            if let detected = VVLanguage.detect(from: url) {
                return detected
            }
        }

        return nil
    }
}

extension VVDiffView {
    /// Override the syntax-highlighting language for code lines inside the diff.
    public func language(_ language: VVLanguage?) -> VVDiffView {
        var view = self
        view.language = language
        return view
    }

    /// Set visual theme for the diff view.
    public func theme(_ theme: VVTheme) -> VVDiffView {
        var view = self
        view.theme = theme
        return view
    }

    /// Set rendering configuration (font and sizing behavior).
    public func configuration(_ configuration: VVConfiguration) -> VVDiffView {
        var view = self
        view.configuration = configuration
        return view
    }

    /// Select unified table or side-by-side split rendering.
    public func renderStyle(_ style: VVDiffRenderStyle) -> VVDiffView {
        var view = self
        view.renderStyle = style
        return view
    }

    /// Enable or disable syntax highlighting for diff code rows.
    public func syntaxHighlighting(_ enabled: Bool) -> VVDiffView {
        var view = self
        view.syntaxHighlightingEnabled = enabled
        return view
    }

    /// Set monospaced font for diff text.
    public func font(_ font: NSFont) -> VVDiffView {
        var view = self
        view.configuration = view.configuration.with(font: font)
        return view
    }

    /// Called when a file header row is activated.
    public func onFileHeaderActivate(_ handler: ((String) -> Void)?) -> VVDiffView {
        var view = self
        view.onFileHeaderActivate = handler
        return view
    }
}
