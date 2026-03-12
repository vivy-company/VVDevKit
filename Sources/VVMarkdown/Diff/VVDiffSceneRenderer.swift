import Foundation
import CoreText
import CoreGraphics
import VVGit
import VVHighlighting
import VVMetalPrimitives

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

public struct VVDiffRenderResult: Sendable {
    public let scene: VVScene
    public let contentHeight: CGFloat

    public init(scene: VVScene, contentHeight: CGFloat) {
        self.scene = scene
        self.contentHeight = contentHeight
    }
}

public enum VVDiffChangeIndicatorStyle: String, CaseIterable, Hashable, Sendable {
    case bars
    case classic
    case none
}

public enum VVDiffInlineHighlightStyle: String, CaseIterable, Hashable, Sendable {
    case word
    case off
}

public struct VVDiffRenderOptions: Hashable, Sendable {
    public var showsFileHeaders: Bool
    public var showsMetadata: Bool
    public var showsHunkHeaders: Bool
    public var showsLineNumbers: Bool
    public var showsBackgrounds: Bool
    public var changeIndicatorStyle: VVDiffChangeIndicatorStyle
    public var inlineHighlightStyle: VVDiffInlineHighlightStyle

    public init(
        showsFileHeaders: Bool = true,
        showsMetadata: Bool = true,
        showsHunkHeaders: Bool = true,
        showsLineNumbers: Bool = true,
        showsBackgrounds: Bool = true,
        changeIndicatorStyle: VVDiffChangeIndicatorStyle = .bars,
        inlineHighlightStyle: VVDiffInlineHighlightStyle = .word
    ) {
        self.showsFileHeaders = showsFileHeaders
        self.showsMetadata = showsMetadata
        self.showsHunkHeaders = showsHunkHeaders
        self.showsLineNumbers = showsLineNumbers
        self.showsBackgrounds = showsBackgrounds
        self.changeIndicatorStyle = changeIndicatorStyle
        self.inlineHighlightStyle = inlineHighlightStyle
    }

    public static let full = VVDiffRenderOptions()
    public static let compactInline = VVDiffRenderOptions(
        showsFileHeaders: false,
        showsMetadata: false,
        showsHunkHeaders: false
    )
}

public enum VVDiffRenderStyle: Hashable, Sendable {
    case inline
    case sideBySide
}

public enum VVDiffSceneRenderer {
    public static func analyze(unifiedDiff: String) -> VVDiffDocument {
        let rows = parseRows(unifiedDiff: unifiedDiff)
        return VVDiffDocument(
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
        style: VVDiffRenderStyle = .inline,
        options: VVDiffRenderOptions = .full
    ) -> VVDiffRenderResult {
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
        style: VVDiffRenderStyle = .inline,
        options: VVDiffRenderOptions = .full,
        highlightedRangesOverride: [Int: [(NSRange, SIMD4<Float>)]]?
    ) -> VVDiffRenderResult {
        let allowsRenderCaching = highlightedRangesOverride == nil && shouldCacheRenderResult(for: unifiedDiff)
        let renderCacheKey = allowsRenderCaching
            ? makeRenderCacheKey(
                unifiedDiff: unifiedDiff,
                width: width,
                theme: theme,
                baseFont: baseFont,
                style: style,
                options: options
            )
            : nil
        if let renderCacheKey, let cached = DiffCaches.renders.value(for: renderCacheKey) {
            return cached
        }

        let document = analyzedDocument(for: unifiedDiff)
        let renderResult = renderDocument(
            document: document,
            width: width,
            theme: theme,
            baseFont: baseFont,
            style: style,
            options: options,
            highlightedRanges: highlightedRangesOverride ?? highlightedRanges(for: unifiedDiff, rows: document.rows, theme: theme, font: baseFont)
        )
        if let renderCacheKey {
            DiffCaches.renders.set(renderResult, for: renderCacheKey)
        }
        return renderResult
    }

    public static func render(
        document: VVDiffDocument,
        width: CGFloat,
        theme: MarkdownTheme,
        baseFont: VVFont,
        style: VVDiffRenderStyle = .inline,
        options: VVDiffRenderOptions = .full,
        highlightedRangesOverride: [Int: [(NSRange, SIMD4<Float>)]] = [:],
        includedRowIDs: Set<Int>? = nil
    ) -> VVDiffRenderResult {
        renderDocument(
            document: document,
            width: width,
            theme: theme,
            baseFont: baseFont,
            style: style,
            options: options,
            highlightedRanges: highlightedRangesOverride,
            includedRowIDs: includedRowIDs
        )
    }

    package static func render(
        layout: VVDiffLayoutPlan,
        theme: MarkdownTheme,
        baseFont: VVFont,
        options: VVDiffRenderOptions = .full,
        highlightedRangesOverride: [Int: [(NSRange, SIMD4<Float>)]] = [:],
        blockRange: Range<Int>? = nil
    ) -> VVDiffRenderResult {
        let renderer = makeSceneBuilder(
            width: layout.width,
            theme: theme,
            baseFont: baseFont,
            highlightedRanges: highlightedRangesOverride
        )
        let result = renderer.buildScene(
            layout: layout,
            blockRange: blockRange ?? 0..<layout.blocks.count,
            options: options
        )
        return VVDiffRenderResult(scene: result.scene, contentHeight: layout.contentHeight)
    }
}

private final class DiffLRUCache<Value> {
    private let lock = NSLock()
    private let maxEntries: Int
    private var cache: [Int: Value] = [:]
    private var order: [Int] = []

    init(maxEntries: Int) {
        self.maxEntries = maxEntries
    }

    func value(for key: Int) -> Value? {
        lock.lock()
        defer { lock.unlock() }
        guard let value = cache[key] else { return nil }
        touch(key)
        return value
    }

    func set(_ value: Value, for key: Int) {
        lock.lock()
        defer { lock.unlock() }
        cache[key] = value
        touch(key)
        while order.count > maxEntries {
            let evicted = order.removeFirst()
            cache.removeValue(forKey: evicted)
        }
    }

    private func touch(_ key: Int) {
        order.removeAll { $0 == key }
        order.append(key)
    }
}

private enum DiffCaches {
    static let highlights = DiffLRUCache<[Int: [(NSRange, SIMD4<Float>)]]>(maxEntries: 24)
    static let documents = DiffLRUCache<VVDiffDocument>(maxEntries: 12)
    static let renders = DiffLRUCache<VVDiffRenderResult>(maxEntries: 4)
}

private enum DiffCacheSizing {
    static let maxCachedUnifiedDiffUTF16 = 120_000
    static let maxCachedHighlightRows = 2_000
    static let maxCachedRenderUTF16 = 80_000
    static let renderCacheRevision = 2
}

private func shouldCacheAnalyzedDocument(for unifiedDiff: String) -> Bool {
    unifiedDiff.utf16.count <= DiffCacheSizing.maxCachedUnifiedDiffUTF16
}

private func shouldCacheHighlightedRanges(for unifiedDiff: String, rows: [ParsedDiffRow]) -> Bool {
    unifiedDiff.utf16.count <= DiffCacheSizing.maxCachedUnifiedDiffUTF16 &&
    rows.count <= DiffCacheSizing.maxCachedHighlightRows
}

private func shouldCacheRenderResult(for unifiedDiff: String) -> Bool {
    unifiedDiff.utf16.count <= DiffCacheSizing.maxCachedRenderUTF16
}

public struct VVDiffRow: Identifiable, Hashable, Sendable {
    public enum Kind: String, Hashable, Sendable {
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

public struct VVDiffSection: Identifiable, Hashable, Sendable {
    public let id: Int
    public let filePath: String
    public let headerRow: VVDiffRow?
    public let rows: [VVDiffRow]
    public let addedCount: Int
    public let deletedCount: Int

    public init(id: Int, filePath: String, headerRow: VVDiffRow?, rows: [VVDiffRow]) {
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

public struct VVDiffSplitRow: Identifiable, Hashable, Sendable {
    public struct Cell: Hashable, Sendable {
        public let rowID: Int
        public let lineNumber: Int?
        public let text: String
        public let kind: VVDiffRow.Kind
        public let inlineChanges: [InlineRange]

        public init(rowID: Int, lineNumber: Int?, text: String, kind: VVDiffRow.Kind, inlineChanges: [InlineRange]) {
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
    public let header: VVDiffRow?
    public let left: Cell?
    public let right: Cell?

    public init(id: Int, header: VVDiffRow?, left: Cell?, right: Cell?) {
        self.id = id
        self.header = header
        self.left = left
        self.right = right
    }
}

public struct VVDiffDocument: Hashable, Sendable {
    public let rows: [VVDiffRow]
    public let sections: [VVDiffSection]
    public let splitRows: [VVDiffSplitRow]
    public let maxOldLineNumber: Int
    public let maxNewLineNumber: Int

    public init(rows: [VVDiffRow], sections: [VVDiffSection], splitRows: [VVDiffSplitRow]) {
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

private typealias ParsedDiffRow = VVDiffRow
private typealias ParsedDiffSection = VVDiffSection
private typealias ParsedDiffSplitRow = VVDiffSplitRow

private func analyzedDocument(for unifiedDiff: String) -> VVDiffDocument {
    if shouldCacheAnalyzedDocument(for: unifiedDiff) {
        var hasher = Hasher()
        hasher.combine(unifiedDiff)
        let cacheKey = hasher.finalize()
        if let cached = DiffCaches.documents.value(for: cacheKey) {
            return cached
        }
        let document = VVDiffSceneRenderer.analyze(unifiedDiff: unifiedDiff)
        DiffCaches.documents.set(document, for: cacheKey)
        return document
    }

    return VVDiffSceneRenderer.analyze(unifiedDiff: unifiedDiff)
}

private func makeSceneBuilder(
    width: CGFloat,
    theme: MarkdownTheme,
    baseFont: VVFont,
    highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]]
) -> DiffSceneBuilder {
    let renderer = DiffSceneBuilder(
        font: baseFont,
        theme: theme,
        contentWidth: width,
        highlightedRanges: highlightedRanges
    )
    renderer.updateContentWidth(width)
    return renderer
}

private func renderDocument(
    document: VVDiffDocument,
    width: CGFloat,
    theme: MarkdownTheme,
    baseFont: VVFont,
    style: VVDiffRenderStyle,
    options: VVDiffRenderOptions,
    highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]],
    includedRowIDs: Set<Int>? = nil
) -> VVDiffRenderResult {
    let renderer = makeSceneBuilder(
        width: width,
        theme: theme,
        baseFont: baseFont,
        highlightedRanges: highlightedRanges
    )
    let result = renderer.buildScene(
        document: document,
        width: width,
        style: style,
        wrapLines: true,
        options: options,
        includedRowIDs: includedRowIDs
    )
    return VVDiffRenderResult(scene: result.scene, contentHeight: result.contentHeight)
}

private func makeRenderCacheKey(
    unifiedDiff: String,
    width: CGFloat,
    theme: MarkdownTheme,
    baseFont: VVFont,
    style: VVDiffRenderStyle,
    options: VVDiffRenderOptions
) -> Int {
    var hasher = Hasher()
    hasher.combine(DiffCacheSizing.renderCacheRevision)
    hasher.combine(unifiedDiff)
    hasher.combine(Int(width.rounded(.toNearestOrEven)))
    hasher.combine(baseFont.pointSize)
    hasher.combine(baseFont.fontName)
    hasher.combine(style == .sideBySide ? 1 : 0)
    hasher.combine(options.showsFileHeaders)
    hasher.combine(options.showsMetadata)
    hasher.combine(options.showsHunkHeaders)
    hasher.combine(options.showsLineNumbers)
    hasher.combine(options.showsBackgrounds)
    hasher.combine(options.changeIndicatorStyle)
    hasher.combine(options.inlineHighlightStyle)
    hasher.combine(theme.codeColor.x)
    hasher.combine(theme.codeColor.y)
    hasher.combine(theme.codeColor.z)
    hasher.combine(theme.codeBackgroundColor.x)
    hasher.combine(theme.codeBackgroundColor.y)
    hasher.combine(theme.codeBackgroundColor.z)
    hasher.combine(theme.codeHeaderBackgroundColor.x)
    hasher.combine(theme.codeHeaderBackgroundColor.y)
    hasher.combine(theme.codeHeaderBackgroundColor.z)
    hasher.combine(theme.codeGutterTextColor.x)
    hasher.combine(theme.codeGutterTextColor.y)
    hasher.combine(theme.codeGutterTextColor.z)
    return hasher.finalize()
}

private func parseRows(unifiedDiff: String) -> [ParsedDiffRow] {
    let document = VVDiffParser.parseDocument(unifiedDiff: unifiedDiff)
    var rows: [ParsedDiffRow] = []
    rows.reserveCapacity(document.records.count)

    for record in document.records {
        let row: ParsedDiffRow
        switch record {
        case let .fileHeader(path, _):
            row = ParsedDiffRow(
                id: rows.count,
                kind: .fileHeader,
                oldLineNumber: nil,
                newLineNumber: nil,
                text: path
            )
        case let .metadata(text):
            row = ParsedDiffRow(
                id: rows.count,
                kind: .metadata,
                oldLineNumber: nil,
                newLineNumber: nil,
                text: text
            )
        case let .hunkHeader(header):
            row = ParsedDiffRow(
                id: rows.count,
                kind: .hunkHeader,
                oldLineNumber: nil,
                newLineNumber: nil,
                text: header.rawLine
            )
        case let .line(line):
            let kind: ParsedDiffRow.Kind
            switch line.kind {
            case .context:
                kind = .context
            case .added:
                kind = .added
            case .deleted:
                kind = .deleted
            }
            row = ParsedDiffRow(
                id: rows.count,
                kind: kind,
                oldLineNumber: line.oldLineNumber,
                newLineNumber: line.newLineNumber,
                text: line.text
            )
        }

        rows.append(row)
    }

    return rows
}

private func makeSections(from rows: [ParsedDiffRow]) -> [ParsedDiffSection] {
    var result: [ParsedDiffSection] = []
    result.reserveCapacity(max(1, rows.count / 64))
    var currentSectionID: Int?
    var currentPath: String?
    var currentHeaderRow: ParsedDiffRow?
    var currentRows: [ParsedDiffRow] = []
    var syntheticID = -1

    func flushSection() {
        guard let sectionID = currentSectionID, let path = currentPath else { return }
        result.append(
            ParsedDiffSection(
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

private func makeSplitRows(from rows: [ParsedDiffRow]) -> [ParsedDiffSplitRow] {
    var result: [ParsedDiffSplitRow] = []
    result.reserveCapacity(rows.count)
    var i = 0

    while i < rows.count {
        let row = rows[i]

        switch row.kind {
        case .fileHeader, .hunkHeader:
            result.append(ParsedDiffSplitRow(id: result.count, header: row, left: nil, right: nil))
            i += 1

        case .metadata:
            i += 1

        case .context:
            result.append(
                ParsedDiffSplitRow(
                    id: result.count,
                    header: nil,
                    left: .init(rowID: row.id, lineNumber: row.oldLineNumber, text: row.text, kind: .context, inlineChanges: []),
                    right: .init(rowID: row.id, lineNumber: row.newLineNumber, text: row.text, kind: .context, inlineChanges: [])
                )
            )
            i += 1

        case .deleted:
            var deletedRows: [ParsedDiffRow] = []
            var addedRows: [ParsedDiffRow] = []

            while i < rows.count, rows[i].kind == .deleted {
                deletedRows.append(rows[i])
                i += 1
            }
            var j = i
            while j < rows.count, rows[j].kind == .metadata {
                j += 1
            }
            while j < rows.count, rows[j].kind == .added {
                addedRows.append(rows[j])
                j += 1
            }

            let count = max(deletedRows.count, addedRows.count)
            for index in 0..<count {
                let deleted = index < deletedRows.count ? deletedRows[index] : nil
                let added = index < addedRows.count ? addedRows[index] : nil
                let inlineChanges = {
                    guard let deleted, let added else {
                        return (old: [ParsedDiffSplitRow.InlineRange](), new: [ParsedDiffSplitRow.InlineRange]())
                    }
                    return computeInlineChanges(oldText: deleted.text, newText: added.text)
                }()

                var leftCell: ParsedDiffSplitRow.Cell?
                var rightCell: ParsedDiffSplitRow.Cell?
                if let deleted {
                    leftCell = .init(
                        rowID: deleted.id,
                        lineNumber: deleted.oldLineNumber,
                        text: deleted.text,
                        kind: .deleted,
                        inlineChanges: inlineChanges.old
                    )
                }
                if let added {
                    rightCell = .init(
                        rowID: added.id,
                        lineNumber: added.newLineNumber,
                        text: added.text,
                        kind: .added,
                        inlineChanges: inlineChanges.new
                    )
                }

                result.append(ParsedDiffSplitRow(id: result.count, header: nil, left: leftCell, right: rightCell))
            }

            i = j

        case .added:
            result.append(
                ParsedDiffSplitRow(
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

private func computeInlineChanges(oldText: String, newText: String) -> (old: [ParsedDiffSplitRow.InlineRange], new: [ParsedDiffSplitRow.InlineRange]) {
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

    var oldChanged: [ParsedDiffSplitRow.InlineRange] = []
    var lcsIdx = 0
    for token in oldTokens {
        if lcsIdx < lcs.oldIndices.count && token.index == lcs.oldIndices[lcsIdx] {
            lcsIdx += 1
        } else {
            oldChanged.append(.init(start: token.offset, end: token.offset + token.text.count))
        }
    }

    var newChanged: [ParsedDiffSplitRow.InlineRange] = []
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

private func mergeRanges(_ ranges: [ParsedDiffSplitRow.InlineRange]) -> [ParsedDiffSplitRow.InlineRange] {
    guard !ranges.isEmpty else { return [] }
    var merged: [ParsedDiffSplitRow.InlineRange] = [ranges[0]]
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

package func VVDiffCompactHunkHeaderText(_ line: String) -> String {
    guard line.hasPrefix("@@") else { return line }
    let searchStart = line.index(line.startIndex, offsetBy: 2)
    guard let trailingRange = line.range(of: "@@", range: searchStart..<line.endIndex) else {
        return ""
    }
    return line[trailingRange.upperBound...].trimmingCharacters(in: .whitespacesAndNewlines)
}

package func VVDiffDisplayText(for row: VVDiffRow) -> String {
    if row.kind == .hunkHeader {
        return VVDiffCompactHunkHeaderText(row.text)
    }
    return row.text
}

private typealias MDLayoutGlyph = LayoutGlyph
private typealias MDFontVariant = FontVariant

private final class DiffSceneBuilder {
    private struct EmptyPaneHatchCacheKey: Hashable {
        let widthKey: Int
        let heightKey: Int
        let phaseKey: Int
        let thicknessKey: Int
        let spacingKey: Int
    }

    private struct CachedEmptyPaneHatchGeometry {
        let vertices: [VVPathVertex]
        let fillVertexCount: Int
        let bounds: CGRect
    }

    private struct LineNumberGlyphCacheKey: Hashable {
        let text: String
        let color: SIMD4<Float>
    }

    private struct WrappedTextSegment {
        let text: String
        let start: Int

        var end: Int {
            start + text.count
        }
    }

    let font: VVFont
    let lineHeight: CGFloat
    let layoutEngine: MarkdownLayoutEngine
    let codeInsetX: CGFloat = 10
    let highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]]
    private var lineNumberGlyphCache: [LineNumberGlyphCacheKey: [MDLayoutGlyph]] = [:]
    private static let emptyPaneHatchCacheLock = NSLock()
    private static var emptyPaneHatchCache: [EmptyPaneHatchCacheKey: CachedEmptyPaneHatchGeometry] = [:]

    var textColor: SIMD4<Float>
    var backgroundColor: SIMD4<Float>
    var gutterTextColor: SIMD4<Float>
    var headerBgColor: SIMD4<Float>
    var metadataBgColor: SIMD4<Float>
    var hunkBgColor: SIMD4<Float>
    var addedBgColor: SIMD4<Float>
    var deletedBgColor: SIMD4<Float>
    var emptyPaneBgColor: SIMD4<Float>
    var emptyPaneGuideColor: SIMD4<Float>
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
        let emptyPaneTint = isLight
            ? blended(theme.codeBackgroundColor, theme.codeGutterTextColor, 0.18)
            : blended(theme.codeBackgroundColor, theme.codeGutterTextColor, 0.24)
        self.emptyPaneBgColor = isLight
            ? blended(theme.codeBackgroundColor, emptyPaneTint, 0.16)
            : blended(theme.codeBackgroundColor, emptyPaneTint, 0.18)
        self.emptyPaneGuideColor = isLight
            ? withAlpha(blended(emptyPaneTint, theme.codeGutterTextColor, 0.24), 0.24)
            : withAlpha(blended(emptyPaneTint, theme.codeGutterTextColor, 0.32), 0.28)
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
        layout: VVDiffLayoutPlan,
        blockRange: Range<Int>,
        options: VVDiffRenderOptions
    ) -> (scene: VVScene, contentHeight: CGFloat) {
        guard !layout.blocks.isEmpty, blockRange.lowerBound < blockRange.upperBound else {
            return (VVScene(primitives: []), layout.contentHeight)
        }

        let clampedRange = max(0, blockRange.lowerBound)..<min(layout.blocks.count, blockRange.upperBound)
        guard clampedRange.lowerBound < clampedRange.upperBound else {
            return (VVScene(primitives: []), layout.contentHeight)
        }

        var builder = VVSceneBuilder()
        let rows = layout.document.rows
        let sections = layout.document.sections
        let splitRows = layout.document.splitRows

        // Collected split rows for pane-ordered rendering.
        // Rendering all left-pane content then all right-pane content with pane-wide
        // clip rects reduces per-frame clip transitions from O(rows) to O(1).
        struct CollectedSplit {
            let splitRow: ParsedDiffSplitRow
            let y: CGFloat
            let height: CGFloat
            let leftWrappedLines: [WrappedTextSegment]
            let rightWrappedLines: [WrappedTextSegment]
        }
        var collectedSplits: [CollectedSplit] = []

        func buildMergedEmptyPaneRuns() {
            guard !collectedSplits.isEmpty else { return }

            func emitRun(paneX: CGFloat, startY: CGFloat?, endY: CGFloat?) {
                guard let startY, let endY, endY > startY + 0.5 else { return }
                buildEmptySplitPanePlaceholder(
                    paneRect: CGRect(x: paneX, y: startY, width: layout.metrics.columnWidth, height: endY - startY),
                    builder: &builder
                )
            }

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

            for (paneX, segmentForItem) in [
                (CGFloat(0), { (item: CollectedSplit) in
                    emptySegment(for: item, wrappedLineCount: item.leftWrappedLines.count, hasCell: item.splitRow.left != nil)
                }),
                (layout.metrics.columnWidth, { (item: CollectedSplit) in
                    emptySegment(for: item, wrappedLineCount: item.rightWrappedLines.count, hasCell: item.splitRow.right != nil)
                })
            ] {
                var runStartY: CGFloat?
                var runEndY: CGFloat?
                for item in collectedSplits {
                    if let segment = segmentForItem(item) {
                        if runStartY == nil {
                            runStartY = segment.startY
                            runEndY = segment.endY
                        } else if let endY = runEndY, abs(segment.startY - endY) < 0.5 {
                            runEndY = segment.endY
                        } else {
                            emitRun(paneX: paneX, startY: runStartY, endY: runEndY)
                            runStartY = segment.startY
                            runEndY = segment.endY
                        }
                    } else {
                        emitRun(paneX: paneX, startY: runStartY, endY: runEndY)
                        runStartY = nil
                        runEndY = nil
                    }
                }
                emitRun(paneX: paneX, startY: runStartY, endY: runEndY)
            }
        }

        for block in layout.blocks[clampedRange] {
            guard let materializedBlock = VVDiffLayoutBuilder.materializedBlock(block, in: layout) else {
                continue
            }
            switch materializedBlock {
            case let .unifiedFileHeader(sectionIndex, _):
                guard options.showsFileHeaders, sections.indices.contains(sectionIndex) else { continue }
                buildFileHeader(
                    section: sections[sectionIndex],
                    y: block.y,
                    width: layout.metrics.totalWidth,
                    height: block.height,
                    builder: &builder
                )

            case let .unifiedRow(rowIndex, wrappedLines):
                guard rows.indices.contains(rowIndex) else { continue }
                let row = rows[rowIndex]
                if row.kind == .metadata && (!options.showsMetadata || row.text.isEmpty) {
                    continue
                }
                if row.kind == .hunkHeader && !options.showsHunkHeaders {
                    continue
                }
                if row.kind == .hunkHeader {
                    buildHunkHeaderRow(
                        lines: materializeWrappedTextSegments(
                            wrappedLines,
                            from: VVDiffDisplayText(for: row)
                        ),
                        y: block.y,
                        width: layout.metrics.totalWidth,
                        height: block.height,
                        builder: &builder
                    )
                } else {
                    buildUnifiedRow(
                        row: row,
                        y: block.y,
                        width: layout.metrics.totalWidth,
                        height: block.height,
                        options: options,
                        gutterColWidth: layout.metrics.gutterColWidth,
                        markerWidth: layout.metrics.markerWidth,
                        codeStartX: layout.metrics.codeStartX,
                        wrappedLines: materializeWrappedTextSegments(wrappedLines, from: row.text),
                        builder: &builder
                    )
                }

            case let .splitHeader(rowIndex, isFileHeader, wrappedLines):
                guard rows.indices.contains(rowIndex) else { continue }
                let row = rows[rowIndex]
                if isFileHeader {
                    guard options.showsFileHeaders else { continue }
                    let section = ParsedDiffSection(id: row.id, filePath: row.text, headerRow: row, rows: [])
                    buildFileHeader(
                        section: section,
                        y: block.y,
                        width: layout.metrics.totalWidth,
                        height: block.height,
                        builder: &builder
                    )
                } else {
                    guard options.showsHunkHeaders else { continue }
                    buildHunkHeaderRow(
                        lines: materializeWrappedTextSegments(
                            wrappedLines,
                            from: VVDiffDisplayText(for: row)
                        ),
                        y: block.y,
                        width: layout.metrics.totalWidth,
                        height: block.height,
                        builder: &builder
                    )
                }

            case let .splitRow(splitRowIndex, leftWrappedLines, rightWrappedLines):
                guard splitRows.indices.contains(splitRowIndex) else { continue }
                let splitRow = splitRows[splitRowIndex]

                // Pass 1: backgrounds only. Empty-pane placeholders are merged
                // across contiguous runs after block collection.
                buildSplitCellBackground(
                    cell: splitRow.left, y: block.y, paneX: 0,
                    paneWidth: layout.metrics.columnWidth, height: block.height, options: options, builder: &builder
                )
                buildSplitCellBackground(
                    cell: splitRow.right, y: block.y, paneX: layout.metrics.columnWidth,
                    paneWidth: layout.metrics.columnWidth, height: block.height, options: options, builder: &builder
                )

                collectedSplits.append(CollectedSplit(
                    splitRow: splitRow, y: block.y, height: block.height,
                    leftWrappedLines: materializeWrappedTextSegments(leftWrappedLines, from: splitRow.left?.text ?? ""),
                    rightWrappedLines: materializeWrappedTextSegments(rightWrappedLines, from: splitRow.right?.text ?? "")
                ))
            }
        }

        buildMergedEmptyPaneRuns()

        // Pass 2+3: pane-ordered content with pane-wide clips.
        // All left-pane primitives share one clip rect, all right-pane share another,
        // so the renderer only transitions clip twice total instead of per-row.
        if !collectedSplits.isEmpty {
            let columnWidth = layout.metrics.columnWidth
            let leftPaneClip = CGRect(x: 0, y: 0, width: columnWidth, height: layout.contentHeight)
            let rightPaneClip = CGRect(x: columnWidth, y: 0, width: columnWidth, height: layout.contentHeight)

            builder.pushClip(leftPaneClip)
            for item in collectedSplits {
                if let cell = item.splitRow.left {
                    buildSplitCellContent(
                        cell: cell, wrappedLines: item.leftWrappedLines,
                        y: item.y, paneX: 0, paneWidth: columnWidth, height: item.height,
                        options: options,
                        gutterColWidth: layout.metrics.gutterColWidth,
                        markerWidth: layout.metrics.markerWidth,
                        codeStartX: layout.metrics.codeStartX, builder: &builder
                    )
                }
            }
            builder.popClip()

            builder.pushClip(rightPaneClip)
            for item in collectedSplits {
                if let cell = item.splitRow.right {
                    buildSplitCellContent(
                        cell: cell, wrappedLines: item.rightWrappedLines,
                        y: item.y, paneX: columnWidth, paneWidth: columnWidth, height: item.height,
                        options: options,
                        gutterColWidth: layout.metrics.gutterColWidth,
                        markerWidth: layout.metrics.markerWidth,
                        codeStartX: layout.metrics.codeStartX, builder: &builder
                    )
                }
            }
            builder.popClip()
        }

        return (builder.scene, layout.contentHeight)
    }

    func buildScene(
        document: VVDiffDocument,
        width: CGFloat,
        style: VVDiffRenderStyle,
        wrapLines: Bool,
        options: VVDiffRenderOptions,
        includedRowIDs: Set<Int>? = nil
    ) -> (scene: VVScene, contentHeight: CGFloat) {
        if style == .sideBySide {
            return buildSplitScene(
                document: document,
                width: width,
                wrapLines: wrapLines,
                options: options,
                includedRowIDs: includedRowIDs
            )
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
            if options.showsFileHeaders, let headerRow = section.headerRow {
                let rowHeight = max(20, lineHeight * 1.5)
                if includedRowIDs == nil || includedRowIDs?.contains(headerRow.id) == true {
                    buildFileHeader(section: section, y: y, width: width, height: rowHeight, builder: &builder)
                }
                y += rowHeight
            }

            for row in section.rows {
                if row.kind == .metadata && (!options.showsMetadata || row.text.isEmpty) {
                    continue
                }
                if row.kind == .hunkHeader && !options.showsHunkHeaders {
                    continue
                }
                let visibleText = VVDiffDisplayText(for: row)
                let wrappedLines = shouldWrap(row: row, wrapLines: wrapLines)
                    ? wrappedTextSegments(visibleText, maxChars: maxCharsPerVisualLine)
                    : singleWrappedSegment(visibleText)
                let rowHeight = lineHeight * CGFloat(max(1, wrappedLines.count))
                if includedRowIDs == nil || includedRowIDs?.contains(row.id) == true {
                    buildUnifiedRow(
                        row: row,
                        y: y,
                        width: width,
                        height: rowHeight,
                        options: options,
                        gutterColWidth: gutterColWidth,
                        markerWidth: markerWidth,
                        codeStartX: codeStartX,
                        wrappedLines: wrappedLines,
                        builder: &builder
                    )
                }
                y += rowHeight
            }
        }

        return (builder.scene, y)
    }

    private func buildSplitScene(
        document: VVDiffDocument,
        width: CGFloat,
        wrapLines: Bool,
        options: VVDiffRenderOptions,
        includedRowIDs: Set<Int>? = nil
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
        let paneMaxCharsPerVisualLine = wrapCapacity(totalWidth: columnWidth, codeStartX: paneCodeStartX)
        let headerMaxCharsPerVisualLine = wrapCapacity(totalWidth: totalWidth, codeStartX: 12)

        var builder = VVSceneBuilder()
        var y: CGFloat = 0

        struct CollectedSplit {
            let splitRow: ParsedDiffSplitRow
            let y: CGFloat
            let height: CGFloat
            let leftCell: ParsedDiffSplitRow.Cell?
            let rightCell: ParsedDiffSplitRow.Cell?
            let leftWrappedLines: [WrappedTextSegment]
            let rightWrappedLines: [WrappedTextSegment]
        }
        var collectedSplits: [CollectedSplit] = []

        func buildMergedEmptyPaneRuns() {
            guard !collectedSplits.isEmpty else { return }

            func emitRun(paneX: CGFloat, startY: CGFloat?, endY: CGFloat?) {
                guard let startY, let endY, endY > startY + 0.5 else { return }
                buildEmptySplitPanePlaceholder(
                    paneRect: CGRect(x: paneX, y: startY, width: columnWidth, height: endY - startY),
                    builder: &builder
                )
            }

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

            for (paneX, segmentForItem) in [
                (CGFloat(0), { (item: CollectedSplit) in
                    emptySegment(for: item, wrappedLineCount: item.leftWrappedLines.count, hasCell: item.leftCell != nil)
                }),
                (columnWidth, { (item: CollectedSplit) in
                    emptySegment(for: item, wrappedLineCount: item.rightWrappedLines.count, hasCell: item.rightCell != nil)
                })
            ] {
                var runStartY: CGFloat?
                var runEndY: CGFloat?
                for item in collectedSplits {
                    if let segment = segmentForItem(item) {
                        if runStartY == nil {
                            runStartY = segment.startY
                            runEndY = segment.endY
                        } else if let endY = runEndY, abs(segment.startY - endY) < 0.5 {
                            runEndY = segment.endY
                        } else {
                            emitRun(paneX: paneX, startY: runStartY, endY: runEndY)
                            runStartY = segment.startY
                            runEndY = segment.endY
                        }
                    } else {
                        emitRun(paneX: paneX, startY: runStartY, endY: runEndY)
                        runStartY = nil
                        runEndY = nil
                    }
                }
                emitRun(paneX: paneX, startY: runStartY, endY: runEndY)
            }
        }

        for splitRow in splitRows {
            if let header = splitRow.header {
                if header.kind == .fileHeader && !options.showsFileHeaders {
                    continue
                }
                if header.kind == .hunkHeader && !options.showsHunkHeaders {
                    continue
                }
                let headerText = VVDiffDisplayText(for: header)
                let wrappedHeaderLines = header.kind == .hunkHeader && wrapLines
                    ? wrappedTextSegments(headerText, maxChars: headerMaxCharsPerVisualLine)
                    : singleWrappedSegment(headerText)
                let rowHeight = header.kind == .fileHeader
                    ? max(20, lineHeight * 1.5)
                    : lineHeight * CGFloat(max(1, wrappedHeaderLines.count))
                if includedRowIDs == nil || includedRowIDs?.contains(header.id) == true {
                    if header.kind == .fileHeader {
                        let section = ParsedDiffSection(id: header.id, filePath: header.text, headerRow: header, rows: [])
                        buildFileHeader(section: section, y: y, width: totalWidth, height: rowHeight, builder: &builder)
                    } else {
                        buildHunkHeaderRow(lines: wrappedHeaderLines, y: y, width: totalWidth, height: rowHeight, builder: &builder)
                    }
                }
                y += rowHeight
            } else {
                let leftWrappedLines = splitRow.left.map { cell in
                    wrapLines && cell.kind.isCode
                        ? wrappedTextSegments(cell.text, maxChars: paneMaxCharsPerVisualLine)
                        : singleWrappedSegment(cell.text)
                } ?? []
                let rightWrappedLines = splitRow.right.map { cell in
                    wrapLines && cell.kind.isCode
                        ? wrappedTextSegments(cell.text, maxChars: paneMaxCharsPerVisualLine)
                        : singleWrappedSegment(cell.text)
                } ?? []
                let rowHeight = lineHeight * CGFloat(max(1, max(leftWrappedLines.count, rightWrappedLines.count)))
                let includesLeft = splitRow.left.map { cell in
                    includedRowIDs == nil || includedRowIDs?.contains(cell.rowID) == true
                } ?? false
                let includesRight = splitRow.right.map { cell in
                    includedRowIDs == nil || includedRowIDs?.contains(cell.rowID) == true
                } ?? false

                if includesLeft || includesRight {
                    // Pass 1: backgrounds only. Empty-pane placeholders are merged
                    // across contiguous runs after row collection.
                    let leftCell = includesLeft ? splitRow.left : nil
                    let rightCell = includesRight ? splitRow.right : nil
                    buildSplitCellBackground(cell: leftCell, y: y, paneX: 0, paneWidth: columnWidth, height: rowHeight, options: options, builder: &builder)
                    buildSplitCellBackground(cell: rightCell, y: y, paneX: columnWidth, paneWidth: columnWidth, height: rowHeight, options: options, builder: &builder)

                    collectedSplits.append(CollectedSplit(
                        splitRow: splitRow, y: y, height: rowHeight,
                        leftCell: leftCell, rightCell: rightCell,
                        leftWrappedLines: includesLeft ? leftWrappedLines : [],
                        rightWrappedLines: includesRight ? rightWrappedLines : []
                    ))
                }
                y += rowHeight
            }
        }

        buildMergedEmptyPaneRuns()

        // Pane-ordered content with pane-wide clips
        if !collectedSplits.isEmpty {
            let leftPaneClip = CGRect(x: 0, y: 0, width: columnWidth, height: y)
            let rightPaneClip = CGRect(x: columnWidth, y: 0, width: columnWidth, height: y)

            builder.pushClip(leftPaneClip)
            for item in collectedSplits {
                if let cell = item.leftCell {
                    buildSplitCellContent(
                        cell: cell, wrappedLines: item.leftWrappedLines,
                        y: item.y, paneX: 0, paneWidth: columnWidth, height: item.height,
                        options: options,
                        gutterColWidth: gutterColWidth, markerWidth: markerWidth,
                        codeStartX: paneCodeStartX, builder: &builder
                    )
                }
            }
            builder.popClip()

            builder.pushClip(rightPaneClip)
            for item in collectedSplits {
                if let cell = item.rightCell {
                    buildSplitCellContent(
                        cell: cell, wrappedLines: item.rightWrappedLines,
                        y: item.y, paneX: columnWidth, paneWidth: columnWidth, height: item.height,
                        options: options,
                        gutterColWidth: gutterColWidth, markerWidth: markerWidth,
                        codeStartX: paneCodeStartX, builder: &builder
                    )
                }
            }
            builder.popClip()
        }

        return (builder.scene, y)
    }

    private func shouldWrap(row: ParsedDiffRow, wrapLines: Bool) -> Bool {
        wrapLines && (row.kind.isCode || row.kind == .hunkHeader)
    }

    private func buildUnifiedRow(
        row: ParsedDiffRow,
        y: CGFloat,
        width: CGFloat,
        height: CGFloat,
        options: VVDiffRenderOptions,
        gutterColWidth: CGFloat,
        markerWidth: CGFloat,
        codeStartX: CGFloat,
        wrappedLines: [WrappedTextSegment],
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
                    color: rowBackgroundColor(for: row.kind, options: options)
                )
            ),
            zIndex: -1
        )

        let firstBaselineY = y + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
        let lineNumberColor = lineNumberColor(for: row.kind)

        if options.showsLineNumbers, let oldNum = row.oldLineNumber {
            let glyphs = lineNumberGlyphs(text: String(oldNum), color: lineNumberColor)
            let width = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            addTextGlyphs(glyphs, offsetX: gutterColWidth - width - 4, baselineY: firstBaselineY, builder: &builder)
        }

        if options.showsLineNumbers, let newNum = row.newLineNumber {
            let glyphs = lineNumberGlyphs(text: String(newNum), color: lineNumberColor)
            let width = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            addTextGlyphs(glyphs, offsetX: gutterColWidth * 2 - width - 4, baselineY: firstBaselineY, builder: &builder)
        }

        buildMarkerIndicator(
            kind: row.kind,
            x: 0,
            y: y,
            width: markerWidth,
            height: height,
            options: options,
            builder: &builder
        )

        if row.kind.isCode || row.kind == .metadata {
            let codeColor = row.kind == .metadata ? gutterTextColor : textColor
            for (lineIndex, lineText) in wrappedLines.enumerated() {
                let baselineY = y + CGFloat(lineIndex) * lineHeight + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
                let glyphs = layoutEngine.layoutTextGlyphs(lineText.text, variant: .monospace, at: .zero, color: codeColor)
                let highlightRanges = clippedHighlightRanges(for: row.id, segment: lineText)
                addTextGlyphs(
                    glyphs,
                    highlightRanges: highlightRanges,
                    offsetX: codeStartX + codeInsetX,
                    baselineY: baselineY,
                    builder: &builder
                )
            }
        }
    }

    private func buildHunkHeaderRow(
        lines: [WrappedTextSegment],
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
            let glyphs = layoutEngine.layoutTextGlyphs(lineText.text, variant: .monospace, at: .zero, color: modifiedColor)
            addTextGlyphs(glyphs, offsetX: 12, baselineY: baselineY, builder: &builder)
        }
    }

    private func buildFileHeader(
        section: ParsedDiffSection,
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

        // File-header names should avoid weight-derived variants here. Custom/variable
        // fonts can keep the same PostScript name across weights, which breaks glyph-id
        // reuse in the Metal atlas and produces corrupted file names.
        let nameGlyphs = layoutEngine.layoutTextGlyphs(parts.fileName, variant: .regular, at: .zero, color: textColor)
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
        kind: ParsedDiffRow.Kind,
        x: CGFloat,
        y: CGFloat,
        width: CGFloat,
        height: CGFloat,
        options: VVDiffRenderOptions,
        builder: inout VVSceneBuilder
    ) {
        switch options.changeIndicatorStyle {
        case .none:
            return
        case .bars:
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
        case .classic:
            let symbol: String
            let color: SIMD4<Float>
            switch kind {
            case .added:
                symbol = "+"
                color = addedMarkerColor
            case .deleted:
                symbol = "-"
                color = deletedMarkerColor
            default:
                return
            }
            let glyphs = layoutEngine.layoutTextGlyphs(symbol, variant: .monospace, at: .zero, color: color)
            let glyphWidth = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            let baselineY = y + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
            addTextGlyphs(glyphs, offsetX: x + max(0, (width - glyphWidth) * 0.5), baselineY: baselineY, builder: &builder)
        }
    }

    /// Background quad (z=-2). Empty-pane placeholders are merged separately so
    /// large asymmetric gaps render as one continuous overlay instead of many slices.
    private func buildSplitCellBackground(
        cell: ParsedDiffSplitRow.Cell?,
        y: CGFloat,
        paneX: CGFloat,
        paneWidth: CGFloat,
        height: CGFloat,
        options: VVDiffRenderOptions,
        builder: inout VVSceneBuilder
    ) {
        let paneRect = CGRect(x: paneX, y: y, width: paneWidth, height: height)
        let background: SIMD4<Float>
        if let cell {
            switch cell.kind {
            case .added: background = options.showsBackgrounds ? addedBgColor : backgroundColor
            case .deleted: background = options.showsBackgrounds ? deletedBgColor : backgroundColor
            default: background = backgroundColor
            }
        } else {
            background = backgroundColor
        }
        builder.add(
            kind: .quad(VVQuadPrimitive(frame: paneRect, color: background)),
            zIndex: -2
        )
    }

    /// Markers (z=1), inline highlights (z=-1), text (z=0).
    /// Caller must have pushed a pane-wide clip before calling.
    private func buildSplitCellContent(
        cell: ParsedDiffSplitRow.Cell,
        wrappedLines: [WrappedTextSegment],
        y: CGFloat,
        paneX: CGFloat,
        paneWidth: CGFloat,
        height: CGFloat,
        options: VVDiffRenderOptions,
        gutterColWidth: CGFloat,
        markerWidth: CGFloat,
        codeStartX: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        let firstBaselineY = y + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
        buildMarkerIndicator(
            kind: cell.kind,
            x: paneX,
            y: y,
            width: markerWidth,
            height: height,
            options: options,
            builder: &builder
        )

        if options.showsLineNumbers, let lineNumber = cell.lineNumber {
            let glyphs = lineNumberGlyphs(text: String(lineNumber), color: lineNumberColor(for: cell.kind))
            let width = glyphs.map { $0.position.x + $0.size.width }.max() ?? 0
            let numX = paneX + markerWidth + gutterColWidth - width - 8
            addTextGlyphs(glyphs, offsetX: numX, baselineY: firstBaselineY, builder: &builder)
        }

        let inlineHighlightColor = cell.kind == .deleted ? withAlpha(deletedMarkerColor, 0.22) : withAlpha(addedMarkerColor, 0.22)
        for (lineIndex, lineText) in wrappedLines.enumerated() {
            let baselineY = y + CGFloat(lineIndex) * lineHeight + (lineHeight + font.pointSize) / 2 - font.pointSize * 0.15
            let baseGlyphs = layoutEngine.layoutTextGlyphs(lineText.text, variant: .monospace, at: .zero, color: textColor)
            let highlightRanges = clippedHighlightRanges(for: cell.rowID, segment: lineText)

            if options.inlineHighlightStyle != .off {
                for range in clippedInlineChanges(cell.inlineChanges, segment: lineText) {
                    let startX = glyphXForCharIndex(range.start, in: baseGlyphs)
                    let endX = glyphXForCharIndex(range.end, in: baseGlyphs)
                    let highlightWidth = endX - startX
                    if highlightWidth > 0 {
                        builder.add(
                            kind: .quad(
                                VVQuadPrimitive(
                                    frame: CGRect(
                                        x: paneX + codeStartX + codeInsetX + startX,
                                        y: y + CGFloat(lineIndex) * lineHeight,
                                        width: highlightWidth,
                                        height: lineHeight
                                    ),
                                    color: inlineHighlightColor
                                )
                            ),
                            zIndex: -1
                        )
                    }
                }
            }

            addTextGlyphs(
                baseGlyphs,
                highlightRanges: highlightRanges,
                offsetX: paneX + codeStartX + codeInsetX,
                baselineY: baselineY,
                builder: &builder
            )
        }

    }

    private func buildEmptySplitPanePlaceholder(
        paneRect: CGRect,
        builder: inout VVSceneBuilder
    ) {
        guard paneRect.width > 12, paneRect.height > 6 else { return }

        let stripeColor = emptyPaneGuideColor
        let stripeThickness: CGFloat = max(2, floor(lineHeight * 0.11))
        let stripeSpacing: CGFloat = max(12, floor(lineHeight * 0.60))
        let phaseShift = paneRect.minY.truncatingRemainder(dividingBy: stripeSpacing)
        let geometry = cachedEmptyPaneHatchGeometry(
            width: paneRect.width,
            height: paneRect.height,
            phaseShift: phaseShift,
            stripeThickness: stripeThickness,
            stripeSpacing: stripeSpacing
        )
        guard !geometry.vertices.isEmpty else { return }

        builder.add(
            kind: .path(
                VVPathPrimitive(
                    vertices: geometry.vertices,
                    fill: stripeColor,
                    fillVertexCount: geometry.fillVertexCount,
                    bounds: geometry.bounds
                )
            ),
            zIndex: -2,
            transform: VVTransform2D.identity.translated(by: paneRect.origin)
        )
    }

    private func cachedEmptyPaneHatchGeometry(
        width: CGFloat,
        height: CGFloat,
        phaseShift: CGFloat,
        stripeThickness: CGFloat,
        stripeSpacing: CGFloat
    ) -> CachedEmptyPaneHatchGeometry {
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

        var vertices: [VVPathVertex] = []
        var fillVertexCount = 0
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
                vertices.append(contentsOf: primitive.vertices)
                fillVertexCount += primitive.fillVertexCount
            }
            x += stripeSpacing
        }

        let geometry = CachedEmptyPaneHatchGeometry(
            vertices: vertices,
            fillVertexCount: fillVertexCount,
            bounds: originRect
        )
        Self.emptyPaneHatchCacheLock.lock()
        Self.emptyPaneHatchCache[key] = geometry
        Self.emptyPaneHatchCacheLock.unlock()
        return geometry
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

    private func addTextGlyphs(
        _ glyphs: [MDLayoutGlyph],
        highlightRanges: [(NSRange, SIMD4<Float>)] = [],
        offsetX: CGFloat,
        baselineY: CGFloat,
        builder: inout VVSceneBuilder
    ) {
        guard !glyphs.isEmpty else { return }
        var vvGlyphs: [VVTextGlyph] = []
        vvGlyphs.reserveCapacity(glyphs.count)
        var minX = CGFloat.greatestFiniteMagnitude
        var minY = CGFloat.greatestFiniteMagnitude
        var maxX = -CGFloat.greatestFiniteMagnitude
        var maxY = -CGFloat.greatestFiniteMagnitude
        var firstResolvedColor: SIMD4<Float>?
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

            if firstResolvedColor == nil {
                firstResolvedColor = resolvedColor
            }
            let position = CGPoint(x: glyph.position.x + offsetX, y: baselineY)
            vvGlyphs.append(
                VVTextGlyph(
                    glyphID: UInt16(glyph.glyphID),
                    position: position,
                    size: glyph.size,
                    color: resolvedColor,
                    fontVariant: toVVFontVariant(glyph.fontVariant),
                    fontSize: glyph.fontSize,
                    fontName: glyph.fontName,
                    stringIndex: glyph.stringIndex
                )
            )
            minX = min(minX, position.x)
            minY = min(minY, position.y)
            maxX = max(maxX, position.x + glyph.size.width)
            maxY = max(maxY, position.y + glyph.size.height)
        }

        let runBounds = CGRect(
            x: minX,
            y: minY,
            width: max(1, maxX - minX),
            height: max(1, maxY - minY)
        )
        builder.add(
            kind: .textRun(
                VVTextRunPrimitive(
                    glyphs: vvGlyphs,
                    style: VVTextRunStyle(color: firstResolvedColor ?? textColor),
                    lineBounds: runBounds,
                    runBounds: runBounds,
                    position: CGPoint(x: offsetX, y: baselineY),
                    fontSize: font.pointSize
                )
            )
        )
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

    private func clippedHighlightRanges(for rowID: Int, segment: WrappedTextSegment) -> [(NSRange, SIMD4<Float>)] {
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
        _ inlineChanges: [ParsedDiffSplitRow.InlineRange],
        segment: WrappedTextSegment
    ) -> [ParsedDiffSplitRow.InlineRange] {
        guard !inlineChanges.isEmpty else { return [] }
        var clipped: [ParsedDiffSplitRow.InlineRange] = []
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

    private func singleWrappedSegment(_ text: String) -> [WrappedTextSegment] {
        [WrappedTextSegment(text: text, start: 0)]
    }

    private func wrappedTextSegments(_ text: String, maxChars: Int) -> [WrappedTextSegment] {
        guard maxChars > 0 else { return singleWrappedSegment(text) }
        let logicalLines = text.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        var result: [WrappedTextSegment] = []
        var absoluteOffset = 0
        for (lineIndex, line) in logicalLines.enumerated() {
            if line.isEmpty {
                result.append(WrappedTextSegment(text: "", start: absoluteOffset))
                if lineIndex < logicalLines.count - 1 {
                    absoluteOffset += 1
                }
                continue
            }
            var start = line.startIndex
            var localOffset = 0
            while start < line.endIndex {
                let end = line.index(start, offsetBy: maxChars, limitedBy: line.endIndex) ?? line.endIndex
                let segmentText = String(line[start..<end])
                result.append(WrappedTextSegment(text: segmentText, start: absoluteOffset + localOffset))
                localOffset += segmentText.count
                start = end
            }
            absoluteOffset += line.count
            if lineIndex < logicalLines.count - 1 {
                absoluteOffset += 1
            }
        }
        return result.isEmpty ? [WrappedTextSegment(text: "", start: 0)] : result
    }

    private func materializeWrappedTextSegments(
        _ descriptors: [VVDiffWrappedTextDescriptor],
        from sourceText: String
    ) -> [WrappedTextSegment] {
        guard !descriptors.isEmpty else { return [WrappedTextSegment(text: "", start: 0)] }
        return descriptors.map { descriptor in
            guard descriptor.length > 0 else {
                return WrappedTextSegment(text: "", start: descriptor.start)
            }
            let boundedStart = min(max(0, descriptor.start), sourceText.count)
            let boundedLength = min(max(0, descriptor.length), sourceText.count - boundedStart)
            let startIndex = sourceText.index(sourceText.startIndex, offsetBy: boundedStart)
            let endIndex = sourceText.index(startIndex, offsetBy: boundedLength)
            return WrappedTextSegment(
                text: String(sourceText[startIndex..<endIndex]),
                start: descriptor.start
            )
        }
    }

    private func measureCharWidth() -> CGFloat {
        layoutEngine.measureTextWidth("8", variant: .monospace)
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
        for kind: ParsedDiffRow.Kind,
        options: VVDiffRenderOptions
    ) -> SIMD4<Float> {
        switch kind {
        case .added: return options.showsBackgrounds ? addedBgColor : backgroundColor
        case .deleted: return options.showsBackgrounds ? deletedBgColor : backgroundColor
        case .hunkHeader: return hunkBgColor
        case .metadata: return metadataBgColor
        case .context: return backgroundColor
        case .fileHeader: return headerBgColor
        }
    }

    private func lineNumberColor(for kind: ParsedDiffRow.Kind) -> SIMD4<Float> {
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
    rows: [ParsedDiffRow],
    theme: MarkdownTheme,
    font: VVFont
) -> [Int: [(NSRange, SIMD4<Float>)]] {
    guard let languageConfig = detectedLanguageConfiguration(for: unifiedDiff) else {
        return [:]
    }

    let allowsCaching = shouldCacheHighlightedRanges(for: unifiedDiff, rows: rows)
    let cacheKey: Int?
    if allowsCaching {
        var hasher = Hasher()
        hasher.combine(unifiedDiff)
        hasher.combine(languageConfig.identifier)
        hasher.combine(font.pointSize)
        hasher.combine(brightness(of: theme.codeBackgroundColor) > 0.58)
        let key = hasher.finalize()
        if let cached = DiffCaches.highlights.value(for: key) {
            return cached
        }
        cacheKey = key
    } else {
        cacheKey = nil
    }

    let semaphore = DispatchSemaphore(value: 0)
    var output: [Int: [(NSRange, SIMD4<Float>)]] = [:]

    Task.detached(priority: .userInitiated) {
        output = await computeHighlightedRanges(rows: rows, language: languageConfig, theme: theme, font: font)
        semaphore.signal()
    }
    semaphore.wait()
    if let cacheKey {
        DiffCaches.highlights.set(output, for: cacheKey)
    }
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
    rows: [ParsedDiffRow],
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
