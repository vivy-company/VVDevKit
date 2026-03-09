import Foundation
import CoreText
import CoreGraphics
import VVHighlighting
import VVMetalPrimitives

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

public struct VVUnifiedDiffRenderResult: Sendable {
    public let scene: VVScene
    public let contentHeight: CGFloat

    public init(scene: VVScene, contentHeight: CGFloat) {
        self.scene = scene
        self.contentHeight = contentHeight
    }
}

public struct VVUnifiedDiffRenderOptions: Sendable {
    public var showsFileHeaders: Bool
    public var showsMetadata: Bool
    public var showsHunkHeaders: Bool

    public init(
        showsFileHeaders: Bool = true,
        showsMetadata: Bool = true,
        showsHunkHeaders: Bool = true
    ) {
        self.showsFileHeaders = showsFileHeaders
        self.showsMetadata = showsMetadata
        self.showsHunkHeaders = showsHunkHeaders
    }

    public static let full = VVUnifiedDiffRenderOptions()
    public static let compactInline = VVUnifiedDiffRenderOptions(
        showsFileHeaders: false,
        showsMetadata: false,
        showsHunkHeaders: false
    )
}

public enum VVDiffSceneRenderStyle: Sendable {
    case unifiedTable
    case split
}

public enum VVUnifiedDiffSceneRenderer {
    public static func analyze(unifiedDiff: String) -> VVUnifiedDiffDocument {
        let rows = parseRows(unifiedDiff: unifiedDiff)
        return VVUnifiedDiffDocument(
            rows: rows,
            sections: makeSections(from: rows),
            splitRows: makeSplitRows(from: rows)
        )
    }

    public static func render(
        unifiedDiff: String,
        width: CGFloat,
        theme: MarkdownTheme,
        baseFont: VVFont,
        style: VVDiffSceneRenderStyle = .unifiedTable,
        options: VVUnifiedDiffRenderOptions = .full
    ) -> VVUnifiedDiffRenderResult {
        render(
            unifiedDiff: unifiedDiff,
            width: width,
            theme: theme,
            baseFont: baseFont,
            style: style,
            options: options,
            highlightedRangesOverride: nil
        )
    }

    public static func render(
        unifiedDiff: String,
        width: CGFloat,
        theme: MarkdownTheme,
        baseFont: VVFont,
        style: VVDiffSceneRenderStyle = .unifiedTable,
        options: VVUnifiedDiffRenderOptions = .full,
        highlightedRangesOverride: [Int: [(NSRange, SIMD4<Float>)]]?
    ) -> VVUnifiedDiffRenderResult {
        let document = analyzedDocument(for: unifiedDiff)
        let renderer = UnifiedDiffRenderer(
            font: baseFont,
            theme: theme,
            contentWidth: width,
            highlightedRanges: highlightedRangesOverride ?? highlightedRanges(for: unifiedDiff, rows: document.rows, theme: theme, font: baseFont)
        )
        renderer.updateContentWidth(width)
        let result = renderer.buildScene(
            document: document,
            width: width,
            style: style,
            wrapLines: true,
            options: options
        )
        return VVUnifiedDiffRenderResult(
            scene: result.scene,
            contentHeight: result.contentHeight
        )
    }
}

private enum UnifiedDiffParsingCache {
    static let hunkHeaderRegex: NSRegularExpression? = try? NSRegularExpression(
        pattern: #"@@ -(\d+)(?:,\d+)? \+(\d+)(?:,\d+)? @@"#
    )
}

private enum UnifiedDiffHighlightCache {
    private static let lock = NSLock()
    private static var cache: [Int: [Int: [(NSRange, SIMD4<Float>)]]] = [:]

    static func value(for key: Int) -> [Int: [(NSRange, SIMD4<Float>)]]? {
        lock.lock()
        defer { lock.unlock() }
        return cache[key]
    }

    static func set(_ value: [Int: [(NSRange, SIMD4<Float>)]], for key: Int) {
        lock.lock()
        defer { lock.unlock() }
        cache[key] = value
        if cache.count > 24, let firstKey = cache.keys.first {
            cache.removeValue(forKey: firstKey)
        }
    }
}

private enum UnifiedDiffDocumentCache {
    private static let lock = NSLock()
    private static var cache: [Int: VVUnifiedDiffDocument] = [:]
    private static var order: [Int] = []
    private static let maxEntries = 12

    static func value(for key: Int) -> VVUnifiedDiffDocument? {
        lock.lock()
        defer { lock.unlock() }
        guard let document = cache[key] else { return nil }
        touch(key)
        return document
    }

    static func set(_ value: VVUnifiedDiffDocument, for key: Int) {
        lock.lock()
        defer { lock.unlock() }
        cache[key] = value
        touch(key)
        while order.count > maxEntries {
            let evicted = order.removeFirst()
            cache.removeValue(forKey: evicted)
        }
    }

    private static func touch(_ key: Int) {
        order.removeAll { $0 == key }
        order.append(key)
    }
}

public struct VVUnifiedDiffRow: Identifiable, Hashable, Sendable {
    public enum Kind: Hashable, Sendable {
        case fileHeader
        case hunkHeader
        case context
        case added
        case deleted
        case metadata

        public var isCode: Bool {
            switch self {
            case .context, .added, .deleted:
                return true
            case .fileHeader, .hunkHeader, .metadata:
                return false
            }
        }
    }

    public let id: Int
    public let kind: Kind
    public let oldLineNumber: Int?
    public let newLineNumber: Int?
    public let text: String

    public init(id: Int, kind: Kind, oldLineNumber: Int?, newLineNumber: Int?, text: String) {
        self.id = id
        self.kind = kind
        self.oldLineNumber = oldLineNumber
        self.newLineNumber = newLineNumber
        self.text = text
    }
}

public struct VVUnifiedDiffSection: Identifiable, Hashable, Sendable {
    public let id: Int
    public let filePath: String
    public let headerRow: VVUnifiedDiffRow?
    public let rows: [VVUnifiedDiffRow]
    public let addedCount: Int
    public let deletedCount: Int

    public init(id: Int, filePath: String, headerRow: VVUnifiedDiffRow?, rows: [VVUnifiedDiffRow]) {
        self.id = id
        self.filePath = filePath
        self.headerRow = headerRow
        self.rows = rows
        var added = 0
        var deleted = 0
        for row in rows {
            switch row.kind {
            case .added:
                added += 1
            case .deleted:
                deleted += 1
            default:
                break
            }
        }
        self.addedCount = added
        self.deletedCount = deleted
    }
}

public struct VVUnifiedDiffSplitRow: Identifiable, Hashable, Sendable {
    public struct Cell: Hashable, Sendable {
        public let rowID: Int
        public let lineNumber: Int?
        public let text: String
        public let kind: VVUnifiedDiffRow.Kind
        public let inlineChanges: [InlineRange]

        public init(rowID: Int, lineNumber: Int?, text: String, kind: VVUnifiedDiffRow.Kind, inlineChanges: [InlineRange]) {
            self.rowID = rowID
            self.lineNumber = lineNumber
            self.text = text
            self.kind = kind
            self.inlineChanges = inlineChanges
        }
    }

    public struct InlineRange: Hashable, Sendable {
        public let start: Int
        public let end: Int

        public init(start: Int, end: Int) {
            self.start = start
            self.end = end
        }
    }

    public let id: Int
    public let header: VVUnifiedDiffRow?
    public let left: Cell?
    public let right: Cell?

    public init(id: Int, header: VVUnifiedDiffRow?, left: Cell?, right: Cell?) {
        self.id = id
        self.header = header
        self.left = left
        self.right = right
    }
}

public struct VVUnifiedDiffDocument: Hashable, Sendable {
    public let rows: [VVUnifiedDiffRow]
    public let sections: [VVUnifiedDiffSection]
    public let splitRows: [VVUnifiedDiffSplitRow]
    public let maxOldLineNumber: Int
    public let maxNewLineNumber: Int

    public init(rows: [VVUnifiedDiffRow], sections: [VVUnifiedDiffSection], splitRows: [VVUnifiedDiffSplitRow]) {
        self.rows = rows
        self.sections = sections
        self.splitRows = splitRows
        var maxOld = 0
        var maxNew = 0
        for row in rows {
            if let old = row.oldLineNumber, old > maxOld {
                maxOld = old
            }
            if let new = row.newLineNumber, new > maxNew {
                maxNew = new
            }
        }
        self.maxOldLineNumber = maxOld
        self.maxNewLineNumber = maxNew
    }
}

private typealias UnifiedDiffRow = VVUnifiedDiffRow
private typealias UnifiedDiffSection = VVUnifiedDiffSection
private typealias UnifiedDiffSplitRow = VVUnifiedDiffSplitRow

private func analyzedDocument(for unifiedDiff: String) -> VVUnifiedDiffDocument {
    var hasher = Hasher()
    hasher.combine(unifiedDiff)
    let cacheKey = hasher.finalize()
    if let cached = UnifiedDiffDocumentCache.value(for: cacheKey) {
        return cached
    }
    let document = VVUnifiedDiffSceneRenderer.analyze(unifiedDiff: unifiedDiff)
    UnifiedDiffDocumentCache.set(document, for: cacheKey)
    return document
}

private func parseRows(unifiedDiff: String) -> [UnifiedDiffRow] {
    var lines = unifiedDiff.split(omittingEmptySubsequences: false, whereSeparator: \.isNewline)
    if lines.last?.isEmpty == true {
        _ = lines.popLast()
    }
    var rows: [UnifiedDiffRow] = []
    rows.reserveCapacity(lines.count)
    var oldLine = 0
    var newLine = 0
    var inHunk = false

    for rawLine in lines {
        let line = String(rawLine)

        if line.hasPrefix("diff --git ") {
            inHunk = false
            rows.append(
                UnifiedDiffRow(
                    id: rows.count,
                    kind: .fileHeader,
                    oldLineNumber: nil,
                    newLineNumber: nil,
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
            let compactHeader = compactHunkHeaderText(line)
            if !compactHeader.isEmpty {
                rows.append(
                    UnifiedDiffRow(
                        id: rows.count,
                        kind: .hunkHeader,
                        oldLineNumber: nil,
                        newLineNumber: nil,
                        text: compactHeader
                    )
                )
            }
            continue
        }

        if !inHunk {
            if isMetadataLine(line) {
                rows.append(
                    UnifiedDiffRow(
                        id: rows.count,
                        kind: .metadata,
                        oldLineNumber: nil,
                        newLineNumber: nil,
                        text: line
                    )
                )
            }
            continue
        }

        if line.hasPrefix("+") && !line.hasPrefix("+++") {
            rows.append(
                UnifiedDiffRow(
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
                UnifiedDiffRow(
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
                UnifiedDiffRow(
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
                UnifiedDiffRow(
                    id: rows.count,
                    kind: .metadata,
                    oldLineNumber: nil,
                    newLineNumber: nil,
                    text: line
                )
            )
            continue
        }

        rows.append(
            UnifiedDiffRow(
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

private func makeSections(from rows: [UnifiedDiffRow]) -> [UnifiedDiffSection] {
    var result: [UnifiedDiffSection] = []
    result.reserveCapacity(max(1, rows.count / 64))
    var currentSectionID: Int?
    var currentPath: String?
    var currentHeaderRow: UnifiedDiffRow?
    var currentRows: [UnifiedDiffRow] = []
    var syntheticID = -1

    func flushSection() {
        guard let sectionID = currentSectionID, let path = currentPath else { return }
        result.append(
            UnifiedDiffSection(
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
            currentPath = "workspace.diff"
            currentHeaderRow = nil
            syntheticID -= 1
        }

        currentRows.append(row)
    }

    flushSection()
    return result
}

private func makeSplitRows(from rows: [UnifiedDiffRow]) -> [UnifiedDiffSplitRow] {
    var result: [UnifiedDiffSplitRow] = []
    result.reserveCapacity(rows.count)
    var i = 0

    while i < rows.count {
        let row = rows[i]

        switch row.kind {
        case .fileHeader, .hunkHeader:
            result.append(UnifiedDiffSplitRow(id: result.count, header: row, left: nil, right: nil))
            i += 1

        case .metadata:
            i += 1

        case .context:
            result.append(
                UnifiedDiffSplitRow(
                    id: result.count,
                    header: nil,
                    left: .init(rowID: row.id, lineNumber: row.oldLineNumber, text: row.text, kind: .context, inlineChanges: []),
                    right: .init(rowID: row.id, lineNumber: row.newLineNumber, text: row.text, kind: .context, inlineChanges: [])
                )
            )
            i += 1

        case .deleted:
            var deletedRows: [UnifiedDiffRow] = []
            var addedRows: [UnifiedDiffRow] = []

            while i < rows.count, rows[i].kind == .deleted {
                deletedRows.append(rows[i])
                i += 1
            }
            var j = i
            while j < rows.count, rows[j].kind == .added {
                addedRows.append(rows[j])
                j += 1
            }

            let count = max(deletedRows.count, addedRows.count)
            for index in 0..<count {
                let deleted = index < deletedRows.count ? deletedRows[index] : nil
                let added = index < addedRows.count ? addedRows[index] : nil

                var leftCell: UnifiedDiffSplitRow.Cell?
                var rightCell: UnifiedDiffSplitRow.Cell?
                if let deleted {
                    let inline = added.map { computeInlineChanges(oldText: deleted.text, newText: $0.text).old } ?? []
                    leftCell = .init(rowID: deleted.id, lineNumber: deleted.oldLineNumber, text: deleted.text, kind: .deleted, inlineChanges: inline)
                }
                if let added {
                    let inline = deleted.map { computeInlineChanges(oldText: $0.text, newText: added.text).new } ?? []
                    rightCell = .init(rowID: added.id, lineNumber: added.newLineNumber, text: added.text, kind: .added, inlineChanges: inline)
                }

                result.append(UnifiedDiffSplitRow(id: result.count, header: nil, left: leftCell, right: rightCell))
            }

            i = j

        case .added:
            result.append(
                UnifiedDiffSplitRow(
                    id: result.count,
                    header: nil,
                    left: nil,
                    right: .init(rowID: row.id, lineNumber: row.newLineNumber, text: row.text, kind: .added, inlineChanges: [])
                )
            )
            i += 1
        }
    }

    return result
}

private func computeInlineChanges(oldText: String, newText: String) -> (old: [UnifiedDiffSplitRow.InlineRange], new: [UnifiedDiffSplitRow.InlineRange]) {
    let oldChars = Array(oldText)
    let newChars = Array(newText)

    var prefixLen = 0
    while prefixLen < oldChars.count && prefixLen < newChars.count && oldChars[prefixLen] == newChars[prefixLen] {
        prefixLen += 1
    }

    var suffixLen = 0
    while suffixLen < oldChars.count - prefixLen && suffixLen < newChars.count - prefixLen
        && oldChars[oldChars.count - 1 - suffixLen] == newChars[newChars.count - 1 - suffixLen] {
        suffixLen += 1
    }

    let oldMiddleStart = prefixLen
    let oldMiddleEnd = oldChars.count - suffixLen
    let newMiddleStart = prefixLen
    let newMiddleEnd = newChars.count - suffixLen

    if oldMiddleStart >= oldMiddleEnd && newMiddleStart >= newMiddleEnd {
        return ([], [])
    }

    let oldTokens = tokenize(Array(oldChars[oldMiddleStart..<oldMiddleEnd]), baseOffset: oldMiddleStart)
    let newTokens = tokenize(Array(newChars[newMiddleStart..<newMiddleEnd]), baseOffset: newMiddleStart)
    let lcs = longestCommonSubsequence(oldTokens.map(\.text), newTokens.map(\.text))

    var oldChanged: [UnifiedDiffSplitRow.InlineRange] = []
    var lcsIdx = 0
    for token in oldTokens {
        if lcsIdx < lcs.oldIndices.count && token.index == lcs.oldIndices[lcsIdx] {
            lcsIdx += 1
        } else {
            oldChanged.append(.init(start: token.offset, end: token.offset + token.text.count))
        }
    }

    var newChanged: [UnifiedDiffSplitRow.InlineRange] = []
    lcsIdx = 0
    for token in newTokens {
        if lcsIdx < lcs.newIndices.count && token.index == lcs.newIndices[lcsIdx] {
            lcsIdx += 1
        } else {
            newChanged.append(.init(start: token.offset, end: token.offset + token.text.count))
        }
    }

    return (mergeRanges(oldChanged), mergeRanges(newChanged))
}

private struct DiffToken {
    let text: String
    let offset: Int
    let index: Int
}

private func tokenize(_ chars: [Character], baseOffset: Int) -> [DiffToken] {
    var tokens: [DiffToken] = []
    var i = 0
    var tokenIndex = 0
    while i < chars.count {
        let ch = chars[i]
        if ch.isWhitespace {
            var j = i
            while j < chars.count && chars[j].isWhitespace { j += 1 }
            tokens.append(DiffToken(text: String(chars[i..<j]), offset: baseOffset + i, index: tokenIndex))
            tokenIndex += 1
            i = j
        } else if ch.isLetter || ch.isNumber || ch == "_" {
            var j = i
            while j < chars.count && (chars[j].isLetter || chars[j].isNumber || chars[j] == "_") { j += 1 }
            tokens.append(DiffToken(text: String(chars[i..<j]), offset: baseOffset + i, index: tokenIndex))
            tokenIndex += 1
            i = j
        } else {
            tokens.append(DiffToken(text: String(ch), offset: baseOffset + i, index: tokenIndex))
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
    if m == 0 || n == 0 { return .init(oldIndices: [], newIndices: []) }

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
    var i = m
    var j = n
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

    return .init(oldIndices: oldIndices.reversed(), newIndices: newIndices.reversed())
}

private func mergeRanges(_ ranges: [UnifiedDiffSplitRow.InlineRange]) -> [UnifiedDiffSplitRow.InlineRange] {
    guard !ranges.isEmpty else { return [] }
    var merged: [UnifiedDiffSplitRow.InlineRange] = [ranges[0]]
    for range in ranges.dropFirst() {
        let last = merged[merged.count - 1]
        if range.start <= last.end {
            merged[merged.count - 1] = .init(start: last.start, end: max(last.end, range.end))
        } else {
            merged.append(range)
        }
    }
    return merged
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
    guard let regex = UnifiedDiffParsingCache.hunkHeaderRegex,
          let match = regex.firstMatch(in: line, range: NSRange(line.startIndex..., in: line)),
          let oldRange = Range(match.range(at: 1), in: line),
          let newRange = Range(match.range(at: 2), in: line),
          let oldStart = Int(line[oldRange]),
          let newStart = Int(line[newRange]) else {
        return nil
    }
    return (oldStart: oldStart, newStart: newStart)
}

private func compactHunkHeaderText(_ line: String) -> String {
    guard line.hasPrefix("@@") else { return line }
    let searchStart = line.index(line.startIndex, offsetBy: 2)
    guard let trailingRange = line.range(of: "@@", range: searchStart..<line.endIndex) else {
        return ""
    }
    return line[trailingRange.upperBound...].trimmingCharacters(in: .whitespacesAndNewlines)
}

private typealias MDLayoutGlyph = LayoutGlyph
private typealias MDFontVariant = FontVariant

private final class UnifiedDiffRenderer {
    let font: VVFont
    let lineHeight: CGFloat
    let layoutEngine: MarkdownLayoutEngine
    let codeInsetX: CGFloat = 10
    let highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]]

    var textColor: SIMD4<Float>
    var backgroundColor: SIMD4<Float>
    var gutterTextColor: SIMD4<Float>
    var headerBgColor: SIMD4<Float>
    var metadataBgColor: SIMD4<Float>
    var hunkBgColor: SIMD4<Float>
    var addedBgColor: SIMD4<Float>
    var deletedBgColor: SIMD4<Float>
    var addedMarkerColor: SIMD4<Float>
    var deletedMarkerColor: SIMD4<Float>
    var modifiedColor: SIMD4<Float>

    init(font: VVFont, theme: MarkdownTheme, contentWidth: CGFloat, highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]]) {
        self.font = font
        self.highlightedRanges = highlightedRanges
        let monoFont = VVFont.monospacedSystemFont(ofSize: font.pointSize, weight: .regular)
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

    func updateContentWidth(_ width: CGFloat) {
        layoutEngine.updateContentWidth(width)
    }

    func buildScene(
        document: VVUnifiedDiffDocument,
        width: CGFloat,
        style: VVDiffSceneRenderStyle,
        wrapLines: Bool,
        options: VVUnifiedDiffRenderOptions
    ) -> (scene: VVScene, contentHeight: CGFloat) {
        if style == .split {
            return buildSplitScene(document: document, width: width, options: options)
        }

        let sections = document.sections
        let maxOld = document.maxOldLineNumber
        let maxNew = document.maxNewLineNumber
        let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
        let gutterColWidth = CGFloat(gutterDigits) * measureCharWidth() + 16
        let markerWidth = measureCharWidth() + 8
        let codeStartX = gutterColWidth * 2 + markerWidth
        let maxCharsPerVisualLine = wrapCapacity(totalWidth: width, codeStartX: codeStartX)

        var builder = VVSceneBuilder()
        var y: CGFloat = 0

        for section in sections {
            if options.showsFileHeaders, section.headerRow != nil {
                let rowHeight = max(20, lineHeight * 1.5)
                buildFileHeader(section: section, y: y, width: width, height: rowHeight, builder: &builder)
                y += rowHeight
            }

            for row in section.rows {
                if row.kind == .metadata && (!options.showsMetadata || row.text.isEmpty) {
                    continue
                }
                if row.kind == .hunkHeader && !options.showsHunkHeaders {
                    continue
                }
                let wrappedLines = shouldWrap(row: row, wrapLines: wrapLines)
                    ? wrappedTextSegments(row.text, maxChars: maxCharsPerVisualLine)
                    : [row.text]
                let rowHeight = lineHeight * CGFloat(max(1, wrappedLines.count))
                buildUnifiedRow(
                    row: row,
                    y: y,
                    width: width,
                    height: rowHeight,
                    gutterColWidth: gutterColWidth,
                    markerWidth: markerWidth,
                    codeStartX: codeStartX,
                    wrappedLines: wrappedLines,
                    builder: &builder
                )
                y += rowHeight
            }
        }

        return (builder.scene, y)
    }

    private func buildSplitScene(
        document: VVUnifiedDiffDocument,
        width: CGFloat,
        options: VVUnifiedDiffRenderOptions
    ) -> (scene: VVScene, contentHeight: CGFloat) {
        let splitRows = document.splitRows
        let maxOld = document.maxOldLineNumber
        let maxNew = document.maxNewLineNumber
        let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
        let gutterColWidth = CGFloat(gutterDigits) * measureCharWidth() + 16
        let markerWidth = measureCharWidth() + 4
        let columnWidth = max(420, floor(width / 2))
        let totalWidth = columnWidth * 2
        let paneCodeStartX = markerWidth + gutterColWidth

        var builder = VVSceneBuilder()
        var y: CGFloat = 0

        for splitRow in splitRows {
            if let header = splitRow.header {
                if header.kind == .fileHeader && !options.showsFileHeaders {
                    continue
                }
                if header.kind == .hunkHeader && !options.showsHunkHeaders {
                    continue
                }
                let rowHeight = header.kind == .fileHeader ? max(20, lineHeight * 1.5) : lineHeight
                if header.kind == .fileHeader {
                    let section = UnifiedDiffSection(id: header.id, filePath: header.text, headerRow: header, rows: [])
                    buildFileHeader(section: section, y: y, width: totalWidth, height: rowHeight, builder: &builder)
                } else {
                    buildHunkHeaderRow(lines: [header.text], y: y, width: totalWidth, height: rowHeight, builder: &builder)
                }
                y += rowHeight
            } else {
                let rowHeight = lineHeight
                buildSplitCell(
                    cell: splitRow.left,
                    y: y,
                    paneX: 0,
                    paneWidth: columnWidth,
                    height: rowHeight,
                    gutterColWidth: gutterColWidth,
                    markerWidth: markerWidth,
                    codeStartX: paneCodeStartX,
                    builder: &builder
                )
                buildSplitCell(
                    cell: splitRow.right,
                    y: y,
                    paneX: columnWidth,
                    paneWidth: columnWidth,
                    height: rowHeight,
                    gutterColWidth: gutterColWidth,
                    markerWidth: markerWidth,
                    codeStartX: paneCodeStartX,
                    builder: &builder
                )
                y += rowHeight
            }
        }

        return (builder.scene, y)
    }

    private func shouldWrap(row: UnifiedDiffRow, wrapLines: Bool) -> Bool {
        wrapLines && (row.kind.isCode || row.kind == .hunkHeader)
    }

    private func buildUnifiedRow(
        row: UnifiedDiffRow,
        y: CGFloat,
        width: CGFloat,
        height: CGFloat,
        gutterColWidth: CGFloat,
        markerWidth: CGFloat,
        codeStartX: CGFloat,
        wrappedLines: [String],
        builder: inout VVSceneBuilder
    ) {
        if row.kind == .hunkHeader {
            buildHunkHeaderRow(lines: wrappedLines, y: y, width: width, height: height, builder: &builder)
            return
        }

        builder.add(
            kind: .quad(
                VVQuadPrimitive(
                    frame: CGRect(x: 0, y: y, width: width, height: height),
                    color: rowBackgroundColor(for: row.kind)
                )
            ),
            zIndex: -1
        )

        let firstBaselineY = y + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
        let lineNumberColor = lineNumberColor(for: row.kind)

        if let oldNum = row.oldLineNumber {
            let glyphs = layoutEngine.layoutTextGlyphs(String(oldNum), variant: .monospace, at: .zero, color: lineNumberColor)
            let width = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            addTextGlyphs(glyphs, offsetX: gutterColWidth - width - 4, baselineY: firstBaselineY, builder: &builder)
        }

        if let newNum = row.newLineNumber {
            let glyphs = layoutEngine.layoutTextGlyphs(String(newNum), variant: .monospace, at: .zero, color: lineNumberColor)
            let width = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            addTextGlyphs(glyphs, offsetX: gutterColWidth * 2 - width - 4, baselineY: firstBaselineY, builder: &builder)
        }

        buildMarkerIndicator(kind: row.kind, x: 0, y: y, width: markerWidth, height: height, builder: &builder)

        if row.kind.isCode || row.kind == .metadata {
            let codeColor = row.kind == .metadata ? gutterTextColor : textColor
            for (lineIndex, lineText) in wrappedLines.enumerated() {
                let baselineY = y + CGFloat(lineIndex) * lineHeight + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
                let glyphs = layoutEngine.layoutTextGlyphs(lineText, variant: .monospace, at: .zero, color: codeColor)
                let coloredGlyphs: [MDLayoutGlyph]
                if wrappedLines.count == 1, let ranges = highlightedRanges[row.id], !ranges.isEmpty {
                    coloredGlyphs = applyHighlightColors(glyphs, ranges: ranges)
                } else {
                    coloredGlyphs = glyphs
                }
                addTextGlyphs(coloredGlyphs, offsetX: codeStartX + codeInsetX, baselineY: baselineY, builder: &builder)
            }
        }
    }

    private func buildHunkHeaderRow(
        lines: [String],
        y: CGFloat,
        width: CGFloat,
        height: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        builder.add(
            kind: .quad(
                VVQuadPrimitive(
                    frame: CGRect(x: 0, y: y, width: width, height: height),
                    color: hunkBgColor
                )
            ),
            zIndex: -1
        )

        for (lineIndex, lineText) in lines.enumerated() {
            let baselineY = y + CGFloat(lineIndex) * lineHeight + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
            let glyphs = layoutEngine.layoutTextGlyphs(lineText, variant: .monospace, at: .zero, color: modifiedColor)
            addTextGlyphs(glyphs, offsetX: 12, baselineY: baselineY, builder: &builder)
        }
    }

    private func buildFileHeader(
        section: UnifiedDiffSection,
        y: CGFloat,
        width: CGFloat,
        height: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        builder.add(
            kind: .quad(
                VVQuadPrimitive(
                    frame: CGRect(x: 0, y: y, width: width, height: height),
                    color: headerBgColor
                )
            ),
            zIndex: -1
        )

        let parts = pathParts(for: section.filePath)
        let baselineY = y + (height + font.pointSize) / 2 - font.pointSize * 0.15
        let iconX: CGFloat = 12
        let iconWidth = buildFileHeaderIcon(x: iconX, centerY: y + height * 0.5, builder: &builder)
        var currentX = iconX + iconWidth + 8

        let nameGlyphs = layoutEngine.layoutTextGlyphs(parts.fileName, variant: .semibold, at: .zero, color: textColor)
        addTextGlyphs(nameGlyphs, offsetX: currentX, baselineY: baselineY, builder: &builder)
        currentX += (nameGlyphs.map { $0.position.x + $0.size.width }.max() ?? 0) + 8

        if !parts.directory.isEmpty {
            let dirGlyphs = layoutEngine.layoutTextGlyphs(parts.directory, variant: .monospace, at: .zero, color: gutterTextColor)
            addTextGlyphs(dirGlyphs, offsetX: currentX, baselineY: baselineY, builder: &builder)
            currentX += (dirGlyphs.map { $0.position.x + $0.size.width }.max() ?? 0) + 12
        }

        let badgeFontSize = max(10, font.pointSize - 1)
        let badgeHeight = max(14, badgeFontSize + 6)
        let badgeY = y + (height - badgeHeight) * 0.5

        if section.addedCount > 0 {
            currentX = buildBadge(
                text: "+\(section.addedCount)",
                color: addedMarkerColor,
                x: currentX,
                badgeY: badgeY,
                badgeH: badgeHeight,
                builder: &builder
            ) + 6
        }

        if section.deletedCount > 0 {
            _ = buildBadge(
                text: "-\(section.deletedCount)",
                color: deletedMarkerColor,
                x: currentX,
                badgeY: badgeY,
                badgeH: badgeHeight,
                builder: &builder
            )
        }
    }

    @discardableResult
    private func buildFileHeaderIcon(
        x: CGFloat,
        centerY: CGFloat,
        builder: inout VVSceneBuilder
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

        builder.add(kind: .quad(VVQuadPrimitive(frame: frame, color: fillColor, cornerRadius: 2)))
        builder.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: frame.minX, y: frame.minY, width: frame.width - foldSize, height: line), color: borderColor)))
        builder.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: frame.minX, y: frame.maxY - line, width: frame.width, height: line), color: borderColor)))
        builder.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: frame.minX, y: frame.minY, width: line, height: frame.height), color: borderColor)))
        builder.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: frame.maxX - line, y: frame.minY + foldSize, width: line, height: frame.height - foldSize), color: borderColor)))

        let foldX = frame.maxX - foldSize
        builder.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: foldX, y: frame.minY, width: foldSize, height: foldSize), color: headerBgColor)))
        builder.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: foldX, y: frame.minY + foldSize - line, width: foldSize, height: line), color: foldLineColor)))
        builder.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: foldX, y: frame.minY, width: line, height: foldSize), color: foldLineColor)))

        return iconWidth
    }

    @discardableResult
    private func buildBadge(
        text: String,
        color: SIMD4<Float>,
        x: CGFloat,
        badgeY: CGFloat,
        badgeH: CGFloat,
        builder: inout VVSceneBuilder
    ) -> CGFloat {
        let glyphs = layoutEngine.layoutTextGlyphs(text, variant: .monospace, at: .zero, color: color)
        let textWidth = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
        let badgeWidth = textWidth + 12
        builder.add(
            kind: .quad(
                VVQuadPrimitive(
                    frame: CGRect(x: x, y: badgeY, width: badgeWidth, height: badgeH),
                    color: withAlpha(color, 0.13),
                    cornerRadius: 5
                )
            )
        )
        let textX = x + max(0, (badgeWidth - textWidth) * 0.5)
        let baselineY = badgeY + (badgeH + font.pointSize - 1) * 0.5 - (font.pointSize - 1) * 0.16
        addTextGlyphs(glyphs, offsetX: textX, baselineY: baselineY, builder: &builder)
        return x + badgeWidth
    }

    private func buildMarkerIndicator(
        kind: UnifiedDiffRow.Kind,
        x: CGFloat,
        y: CGFloat,
        width: CGFloat,
        height: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        let barWidth: CGFloat = min(width, 6)
        switch kind {
        case .added:
            builder.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: x, y: y, width: barWidth, height: height), color: addedMarkerColor)), zIndex: 1)
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
                    builder.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: x, y: top, width: barWidth, height: bottom - top), color: deletedMarkerColor)), zIndex: 1)
                }
                dashY += period
            }
        default:
            break
        }
    }

    private func buildSplitCell(
        cell: UnifiedDiffSplitRow.Cell?,
        y: CGFloat,
        paneX: CGFloat,
        paneWidth: CGFloat,
        height: CGFloat,
        gutterColWidth: CGFloat,
        markerWidth: CGFloat,
        codeStartX: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        let background: SIMD4<Float>
        if let cell {
            switch cell.kind {
            case .added: background = addedBgColor
            case .deleted: background = deletedBgColor
            default: background = backgroundColor
            }
        } else {
            background = withAlpha(headerBgColor, 0.30)
        }
        builder.add(
            kind: .quad(
                VVQuadPrimitive(
                    frame: CGRect(x: paneX, y: y, width: paneWidth, height: height),
                    color: background
                )
            ),
            zIndex: -1
        )

        guard let cell else { return }

        let baselineY = y + (height + font.pointSize) / 2 - font.pointSize * 0.15
        buildMarkerIndicator(kind: cell.kind, x: paneX, y: y, width: markerWidth, height: height, builder: &builder)

        if let lineNumber = cell.lineNumber {
            let glyphs = layoutEngine.layoutTextGlyphs(String(lineNumber), variant: .monospace, at: .zero, color: lineNumberColor(for: cell.kind))
            let width = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            let numX = paneX + markerWidth + gutterColWidth - width - 8
            addTextGlyphs(glyphs, offsetX: numX, baselineY: baselineY, builder: &builder)
        }

        let baseGlyphs = layoutEngine.layoutTextGlyphs(cell.text, variant: .monospace, at: .zero, color: textColor)
        let glyphs = highlightedRanges[cell.rowID].map { applyHighlightColors(baseGlyphs, ranges: $0) } ?? baseGlyphs
        addTextGlyphs(glyphs, offsetX: paneX + codeStartX + codeInsetX, baselineY: baselineY, builder: &builder)

        let inlineHighlightColor = cell.kind == .deleted ? withAlpha(deletedMarkerColor, 0.22) : withAlpha(addedMarkerColor, 0.22)
        for range in cell.inlineChanges {
            let startX = glyphXForCharIndex(range.start, in: glyphs)
            let endX = glyphXForCharIndex(range.end, in: glyphs)
            let highlightWidth = endX - startX
            if highlightWidth > 0 {
                builder.add(
                    kind: .quad(
                        VVQuadPrimitive(
                            frame: CGRect(x: paneX + codeStartX + codeInsetX + startX, y: y, width: highlightWidth, height: height),
                            color: inlineHighlightColor
                        )
                    ),
                    zIndex: 0
                )
            }
        }
    }

    private func addTextGlyphs(
        _ glyphs: [MDLayoutGlyph],
        offsetX: CGFloat,
        baselineY: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        guard !glyphs.isEmpty else { return }
        let vvGlyphs = glyphs.map { glyph in
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
        builder.add(
            kind: .textRun(
                VVTextRunPrimitive(
                    glyphs: vvGlyphs,
                    style: VVTextRunStyle(color: vvGlyphs.first?.color ?? textColor),
                    position: CGPoint(x: offsetX, y: baselineY),
                    fontSize: font.pointSize
                )
            )
        )
    }

    private func applyHighlightColors(_ glyphs: [MDLayoutGlyph], ranges: [(NSRange, SIMD4<Float>)]) -> [MDLayoutGlyph] {
        glyphs.map { glyph in
            guard let idx = glyph.stringIndex else { return glyph }
            for (range, color) in ranges where idx >= range.location && idx < range.location + range.length {
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
            return glyph
        }
    }

    private func glyphXForCharIndex(_ charIndex: Int, in glyphs: [MDLayoutGlyph]) -> CGFloat {
        for glyph in glyphs {
            if let index = glyph.stringIndex, index >= charIndex {
                return glyph.position.x
            }
        }
        return glyphs.last.map { $0.position.x + $0.size.width } ?? 0
    }

    private func wrapCapacity(totalWidth: CGFloat, codeStartX: CGFloat) -> Int {
        let available = max(0, totalWidth - codeStartX - codeInsetX - 12)
        return max(1, Int(floor(available / max(measureCharWidth(), 1))))
    }

    private func wrappedTextSegments(_ text: String, maxChars: Int) -> [String] {
        guard maxChars > 0 else { return [text] }
        let logicalLines = text.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        var result: [String] = []
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

    private func measureCharWidth() -> CGFloat {
        layoutEngine.measureTextWidth("8", variant: .monospace)
    }

    private func rowBackgroundColor(for kind: UnifiedDiffRow.Kind) -> SIMD4<Float> {
        switch kind {
        case .added: return addedBgColor
        case .deleted: return deletedBgColor
        case .hunkHeader: return hunkBgColor
        case .metadata: return metadataBgColor
        case .context: return backgroundColor
        case .fileHeader: return headerBgColor
        }
    }

    private func lineNumberColor(for kind: UnifiedDiffRow.Kind) -> SIMD4<Float> {
        switch kind {
        case .added: return addedMarkerColor
        case .deleted: return deletedMarkerColor
        default: return gutterTextColor
        }
    }
}

private func pathParts(for path: String) -> (fileName: String, directory: String) {
    ((path as NSString).lastPathComponent, (path as NSString).deletingLastPathComponent)
}

private func brightness(of color: SIMD4<Float>) -> Double {
    0.2126 * Double(color.x) + 0.7152 * Double(color.y) + 0.0722 * Double(color.z)
}

private func withAlpha(_ color: SIMD4<Float>, _ alpha: Float) -> SIMD4<Float> {
    SIMD4(color.x, color.y, color.z, alpha)
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

private func highlightedRanges(
    for unifiedDiff: String,
    rows: [UnifiedDiffRow],
    theme: MarkdownTheme,
    font: VVFont
) -> [Int: [(NSRange, SIMD4<Float>)]] {
    guard let languageConfig = detectedLanguageConfiguration(for: unifiedDiff) else {
        return [:]
    }

    var hasher = Hasher()
    hasher.combine(unifiedDiff)
    hasher.combine(languageConfig.identifier)
    hasher.combine(font.pointSize)
    hasher.combine(brightness(of: theme.codeBackgroundColor) > 0.58)
    let cacheKey = hasher.finalize()
    if let cached = UnifiedDiffHighlightCache.value(for: cacheKey) {
        return cached
    }

    let semaphore = DispatchSemaphore(value: 0)
    var output: [Int: [(NSRange, SIMD4<Float>)]] = [:]

    Task.detached(priority: .userInitiated) {
        output = await computeHighlightedRanges(rows: rows, language: languageConfig, theme: theme, font: font)
        semaphore.signal()
    }
    semaphore.wait()
    UnifiedDiffHighlightCache.set(output, for: cacheKey)
    return output
}

private func detectedLanguageConfiguration(for unifiedDiff: String) -> LanguageConfiguration? {
    var detected: LanguageConfiguration?
    unifiedDiff.enumerateLines { line, stop in
        guard line.hasPrefix("+++ ") else { return }
        let path = line
            .replacingOccurrences(of: "+++ b/", with: "")
            .replacingOccurrences(of: "+++ ", with: "")
        if path != "/dev/null", let config = LanguageRegistry.shared.language(forPath: path) {
            detected = config
            stop = true
        }
    }
    return detected
}

private func computeHighlightedRanges(
    rows: [UnifiedDiffRow],
    language: LanguageConfiguration,
    theme: MarkdownTheme,
    font: VVFont
) async -> [Int: [(NSRange, SIMD4<Float>)]] {
    await VVDiffHighlighting.computeHighlightedRanges(
        rows: rows,
        language: language,
        highlightTheme: VVDiffHighlighting.highlightTheme(
            isDarkBackground: !(brightness(of: theme.codeBackgroundColor) > 0.58)
        ),
        font: font,
        rowID: \.id,
        rowText: \.text,
        rowIsCode: { $0.kind.isCode }
    )
}
