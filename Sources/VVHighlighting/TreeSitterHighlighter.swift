import Foundation
import AppKit
import SwiftTreeSitter

// MARK: - Offset Converter

/// Converts SwiftTreeSitter byte offsets to NSRange
///
/// IMPORTANT: SwiftTreeSitter uses UTF-16LE encoding internally (TSInputEncodingUTF16LE),
/// so node.byteRange returns UTF-16 *byte* offsets (2 bytes per code unit for BMP characters).
/// NSRange uses UTF-16 code unit offsets, so we simply divide by 2.
///
/// For characters outside BMP (emoji, etc.), UTF-16 uses surrogate pairs (2 code units = 4 bytes),
/// but dividing by 2 still gives the correct UTF-16 code unit offset.
public struct OffsetConverter {
    private let textLength: Int  // UTF-16 code unit count

    public init(text: String) {
        self.textLength = text.utf16.count
    }

    /// Convert SwiftTreeSitter UTF-16 byte offset to UTF-16 code unit offset
    public func toUTF16(_ utf16ByteOffset: Int) -> Int {
        // SwiftTreeSitter uses UTF-16LE: 2 bytes per code unit
        return utf16ByteOffset / 2
    }

    /// Convert tree-sitter byte range to NSRange
    public func toNSRange(byteStart: Int, byteEnd: Int) -> NSRange {
        let start = toUTF16(byteStart)
        let end = toUTF16(byteEnd)
        return NSRange(location: start, length: end - start)
    }
}

// MARK: - Tree-sitter Highlighter

/// Tree-sitter based syntax highlighter with correct UTF-8/UTF-16 handling
public actor TreeSitterHighlighter {
    // MARK: - Properties

    private var parser: Parser?
    private var tree: MutableTree?
    private var language: LanguageConfiguration?
    private var theme: HighlightTheme
    private var currentText: String = ""
    private var offsetConverter: OffsetConverter?

    // MARK: - Initialization

    public init(theme: HighlightTheme = .defaultDark) {
        self.theme = theme
    }

    // MARK: - Configuration

    public func setLanguage(_ config: LanguageConfiguration) throws {
        self.language = config

        if parser == nil {
            parser = Parser()
        }

        try parser?.setLanguage(config.language)
        tree = nil
        offsetConverter = nil
    }

    public func setTheme(_ theme: HighlightTheme) {
        self.theme = theme
    }

    // MARK: - Parsing

    public func parse(_ text: String) throws -> MutableTree? {
        guard let parser = parser else { return nil }

        currentText = text
        offsetConverter = OffsetConverter(text: text)
        tree = parser.parse(text)

        return tree
    }

    public func parseIncremental(text: String, edit: InputEdit) throws -> MutableTree? {
        guard let parser = parser, let currentTree = tree else {
            return try parse(text)
        }

        currentTree.edit(edit)
        currentText = text
        offsetConverter = OffsetConverter(text: text)
        tree = parser.parse(tree: currentTree, string: text)

        return tree
    }

    // MARK: - Highlighting

    public func highlights(in range: NSRange? = nil) throws -> [HighlightRange] {
        guard let tree = tree,
              let language = language,
              let query = language.queries[.highlights],
              let converter = offsetConverter else {
            return []
        }

        var highlights: [HighlightRange] = []
        let cursor = query.execute(in: tree)
        if let filterRange = range {
            cursor.setRange(filterRange)
        }
        let textLength = currentText.utf16.count

        while let match = cursor.next() {
            for capture in match.captures {
                let node = capture.node
                let byteStart = Int(node.byteRange.lowerBound)
                let byteEnd = Int(node.byteRange.upperBound)
                let nsRange = converter.toNSRange(byteStart: byteStart, byteEnd: byteEnd)

                // Validate range
                guard nsRange.location >= 0,
                      nsRange.length > 0,
                      nsRange.location + nsRange.length <= textLength else {
                    continue
                }

                // Filter by requested range if provided
                if let filterRange = range {
                    guard NSIntersectionRange(nsRange, filterRange).length > 0 else {
                        continue
                    }
                }

                let captureName = query.captureName(for: capture.index) ?? "unknown"
                let style = theme.style(for: captureName)

                highlights.append(HighlightRange(
                    range: nsRange,
                    capture: captureName,
                    style: style
                ))
            }
        }

        return highlights
    }

    public func allHighlights() throws -> [HighlightRange] {
        return try highlights(in: nil)
    }
}

// MARK: - Supporting Types

public struct HighlightRange: Sendable {
    public let range: NSRange
    public let capture: String
    public let style: HighlightStyle

    public init(range: NSRange, capture: String, style: HighlightStyle) {
        self.range = range
        self.capture = capture
        self.style = style
    }
}

public struct FoldingRange: Sendable, Hashable {
    public let startLine: Int
    public let endLine: Int
    public let indentColumn: Int

    public init(startLine: Int, endLine: Int, indentColumn: Int) {
        self.startLine = startLine
        self.endLine = endLine
        self.indentColumn = indentColumn
    }
}

public struct HighlightStyle: Sendable, Equatable {
    public let color: NSColor
    public let isBold: Bool
    public let isItalic: Bool
    public let isUnderlined: Bool

    public init(
        color: NSColor,
        isBold: Bool = false,
        isItalic: Bool = false,
        isUnderlined: Bool = false
    ) {
        self.color = color
        self.isBold = isBold
        self.isItalic = isItalic
        self.isUnderlined = isUnderlined
    }

    public func attributes(baseFont: NSFont) -> [NSAttributedString.Key: Any] {
        var attrs: [NSAttributedString.Key: Any] = [
            .foregroundColor: color
        ]

        if isBold || isItalic {
            var fontDescriptor = baseFont.fontDescriptor
            var traits = fontDescriptor.symbolicTraits

            if isBold { traits.insert(.bold) }
            if isItalic { traits.insert(.italic) }

            fontDescriptor = fontDescriptor.withSymbolicTraits(traits)
            attrs[.font] = NSFont(descriptor: fontDescriptor, size: baseFont.pointSize) ?? baseFont
        } else {
            attrs[.font] = baseFont
        }

        if isUnderlined {
            attrs[.underlineStyle] = NSUnderlineStyle.single.rawValue
        }

        return attrs
    }
}

// MARK: - Folding (Tree-sitter)

extension TreeSitterHighlighter {
    public func foldingRanges() -> [FoldingRange] {
        guard let tree = tree,
              let root = tree.rootNode else { return [] }
        var results: [FoldingRange] = []
        var stack: [(node: Node, ignored: Bool)] = [(root, false)]

        while let current = stack.popLast() {
            let node = current.node
            let type = node.nodeType ?? ""
            let isIgnored = current.ignored || isIgnoredNodeType(type)
            let pointRange = node.pointRange
            let startPoint = pointRange.lowerBound
            let endPoint = pointRange.upperBound

            if !isIgnored,
               node.isNamed,
               endPoint.row > startPoint.row,
               isFoldableNodeType(type) {
                results.append(FoldingRange(
                    startLine: Int(startPoint.row),
                    endLine: Int(endPoint.row),
                    indentColumn: Int(startPoint.column)
                ))
            }

            let childCount = node.childCount
            if childCount > 0 {
                for index in stride(from: childCount - 1, through: 0, by: -1) {
                    if let child = node.child(at: index) {
                        stack.append((child, isIgnored))
                    }
                }
            }
        }

        // Filter out child body/block ranges that are redundant with their parent.
        // e.g. function_declaration (line 8-11) + function_body (line 9-11) -> keep only function_declaration
        let sorted = results.sorted { $0.startLine < $1.startLine }
        var filtered: [FoldingRange] = []
        for range in sorted {
            let isChildBody = filtered.contains { parent in
                range.startLine == parent.startLine + 1 &&
                range.endLine <= parent.endLine
            }
            if !isChildBody {
                filtered.append(range)
            }
        }
        return filtered
    }

    private func isIgnoredNodeType(_ type: String) -> Bool {
        let lower = type.lowercased()
        return lower.contains("comment") || lower.contains("string")
    }

    private func isFoldableNodeType(_ type: String) -> Bool {
        let lower = type.lowercased()
        if lower == "source_file" || lower == "program" || lower == "translation_unit" {
            return false
        }
        let keywords = [
            "block",
            "body",
            "statement",
            "declaration",
            "class",
            "struct",
            "enum",
            "interface",
            "namespace",
            "module",
            "function",
            "method",
            "if",
            "for",
            "while",
            "switch",
            "case",
            "try",
            "catch",
            "do",
            "with",
            "match",
            "loop",
            "lambda",
            "closure",
            "array",
            "list",
            "object",
            "map",
            "dictionary",
            "tuple"
        ]
        return keywords.contains { lower.contains($0) }
    }
}
