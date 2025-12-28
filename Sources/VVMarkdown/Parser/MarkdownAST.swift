//  MarkdownAST.swift
//  VVMarkdown
//
//  Markdown block and inline types for Metal-based rendering

import Foundation

// MARK: - Parsed Markdown Document

/// Represents a fully parsed markdown document
public struct ParsedMarkdownDocument: Sendable {
    public let blocks: [MarkdownBlock]
    public let footnotes: [String: MarkdownBlock]
    public let isComplete: Bool
    public let streamingBuffer: String

    public static let empty = ParsedMarkdownDocument(blocks: [], footnotes: [:], isComplete: true, streamingBuffer: "")

    public init(blocks: [MarkdownBlock], footnotes: [String: MarkdownBlock], isComplete: Bool, streamingBuffer: String) {
        self.blocks = blocks
        self.footnotes = footnotes
        self.isComplete = isComplete
        self.streamingBuffer = streamingBuffer
    }
}

// MARK: - Markdown Block

/// Markdown block with stable ID for efficient diffing
public struct MarkdownBlock: Identifiable, Equatable, Sendable {
    public let id: String
    public let type: MarkdownBlockType

    public init(_ type: MarkdownBlockType, index: Int = 0) {
        self.type = type
        self.id = Self.generateId(for: type, index: index)
    }

    private static func generateId(for type: MarkdownBlockType, index: Int) -> String {
        switch type {
        case .paragraph(let content):
            return "p-\(index)-\(content.hashValue)"
        case .heading(_, let level):
            return "h\(level)-\(index)"
        case .codeBlock(let code, let lang, _):
            return "code-\(index)-\(lang ?? "plain")-\(code.prefix(50).hashValue)"
        case .list(let items, let ordered, _):
            return "list-\(ordered)-\(index)-\(items.count)"
        case .blockQuote(let blocks):
            return "quote-\(index)-\(blocks.count)"
        case .table(let rows, _):
            return "table-\(index)-\(rows.count)"
        case .image(let url, _):
            return "img-\(index)-\(url.hashValue)"
        case .thematicBreak:
            return "hr-\(index)"
        case .htmlBlock(let html):
            return "html-\(index)-\(html.prefix(50).hashValue)"
        case .mathBlock(let content):
            return "math-\(index)-\(content.hashValue)"
        case .footnoteReference(let id):
            return "fnref-\(index)-\(id)"
        case .footnoteDefinition(let id, _):
            return "fndef-\(index)-\(id)"
        }
    }

    public static func == (lhs: MarkdownBlock, rhs: MarkdownBlock) -> Bool {
        lhs.id == rhs.id
    }
}

// MARK: - Markdown Block Type

public enum MarkdownBlockType: Equatable, Sendable {
    case paragraph(MarkdownInlineContent)
    case heading(MarkdownInlineContent, level: Int)
    case codeBlock(code: String, language: String?, isStreaming: Bool)
    case list(items: [MarkdownListItem], ordered: Bool, startIndex: Int)
    case blockQuote(blocks: [MarkdownBlock])
    case table(rows: [MarkdownTableRow], alignments: [ColumnAlignment])
    case image(url: String, alt: String?)
    case thematicBreak
    case htmlBlock(String)
    case mathBlock(String)
    case footnoteReference(id: String)
    case footnoteDefinition(id: String, blocks: [MarkdownBlock])

    public static func == (lhs: MarkdownBlockType, rhs: MarkdownBlockType) -> Bool {
        switch (lhs, rhs) {
        case (.paragraph(let l), .paragraph(let r)): return l == r
        case (.heading(let lc, let ll), .heading(let rc, let rl)): return lc == rc && ll == rl
        case (.codeBlock(let lc, let ll, _), .codeBlock(let rc, let rl, _)): return lc == rc && ll == rl
        case (.thematicBreak, .thematicBreak): return true
        case (.htmlBlock(let l), .htmlBlock(let r)): return l == r
        case (.mathBlock(let l), .mathBlock(let r)): return l == r
        case (.footnoteReference(let l), .footnoteReference(let r)): return l == r
        case (.image(let lu, let la), .image(let ru, let ra)): return lu == ru && la == ra
        case (.list(let li, let lo, let ls), .list(let ri, let ro, let rs)):
            return li == ri && lo == ro && ls == rs
        case (.blockQuote(let l), .blockQuote(let r)): return l == r
        case (.table(let lr, let la), .table(let rr, let ra)): return lr == rr && la == ra
        case (.footnoteDefinition(let li, let lb), .footnoteDefinition(let ri, let rb)):
            return li == ri && lb == rb
        default: return false
        }
    }
}

// MARK: - Column Alignment

public enum ColumnAlignment: Equatable, Sendable {
    case left
    case center
    case right
    case none
}

// MARK: - Markdown List Item

public struct MarkdownListItem: Identifiable, Equatable, Sendable {
    public let id: String
    public let content: MarkdownInlineContent
    public let children: [MarkdownListItem]
    public let checkbox: CheckboxState?
    public let depth: Int
    public let listOrdered: Bool
    public let listStartIndex: Int
    public let itemIndex: Int

    public enum CheckboxState: Equatable, Sendable {
        case checked
        case unchecked
    }

    public init(
        content: MarkdownInlineContent,
        children: [MarkdownListItem] = [],
        checkbox: CheckboxState? = nil,
        depth: Int = 0,
        index: Int = 0,
        listOrdered: Bool = false,
        listStartIndex: Int = 1
    ) {
        self.content = content
        self.children = children
        self.checkbox = checkbox
        self.depth = depth
        self.listOrdered = listOrdered
        self.listStartIndex = listStartIndex
        self.itemIndex = index
        let orderTag = listOrdered ? "o" : "u"
        self.id = "li-\(depth)-\(index)-\(orderTag)-\(content.hashValue)"
    }
}

// MARK: - Markdown Table Row

public struct MarkdownTableRow: Identifiable, Equatable, Sendable {
    public let id: String
    public let cells: [MarkdownInlineContent]
    public let isHeader: Bool

    public init(cells: [MarkdownInlineContent], isHeader: Bool = false, index: Int = 0) {
        self.cells = cells
        self.isHeader = isHeader
        self.id = "row-\(isHeader ? "h" : "b")-\(index)"
    }
}

// MARK: - Markdown Inline Content

/// Rich inline content for rendering
public struct MarkdownInlineContent: Equatable, Hashable, Sendable {
    public let elements: [InlineElement]

    public var isEmpty: Bool { elements.isEmpty }

    public var plainText: String {
        elements.map { $0.plainText }.joined()
    }

    public var containsImages: Bool {
        elements.contains { element in
            switch element {
            case .image:
                return true
            case .link(let content, _, _):
                return content.containsImages
            default:
                return false
            }
        }
    }

    public init(elements: [InlineElement] = []) {
        self.elements = elements
    }

    public init(text: String) {
        self.elements = [.text(text)]
    }

    public func hash(into hasher: inout Hasher) {
        hasher.combine(plainText)
    }
}

// MARK: - Inline Element

public enum InlineElement: Equatable, Hashable, Sendable {
    case text(String)
    case emphasis(MarkdownInlineContent)
    case strong(MarkdownInlineContent)
    case strikethrough(MarkdownInlineContent)
    case code(String)
    case link(text: MarkdownInlineContent, url: String, title: String?)
    case image(url: String, alt: String?, title: String?)
    case softBreak
    case hardBreak
    case html(String)
    case math(String)
    case footnoteReference(id: String)

    public var plainText: String {
        switch self {
        case .text(let t): return t
        case .emphasis(let c): return c.plainText
        case .strong(let c): return c.plainText
        case .strikethrough(let c): return c.plainText
        case .code(let c): return c
        case .link(let t, _, _): return t.plainText
        case .image(_, let alt, _): return alt ?? ""
        case .softBreak: return " "
        case .hardBreak: return "\n"
        case .html(let h): return h
        case .math(let m): return m
        case .footnoteReference(let id): return "[\(id)]"
        }
    }

    public func hash(into hasher: inout Hasher) {
        hasher.combine(plainText)
    }
}

// MARK: - Inline Style

/// Style information for inline text rendering
public struct InlineStyle: OptionSet, Sendable {
    public let rawValue: UInt8

    public init(rawValue: UInt8) {
        self.rawValue = rawValue
    }

    public static let bold = InlineStyle(rawValue: 1 << 0)
    public static let italic = InlineStyle(rawValue: 1 << 1)
    public static let strikethrough = InlineStyle(rawValue: 1 << 2)
    public static let code = InlineStyle(rawValue: 1 << 3)
    public static let link = InlineStyle(rawValue: 1 << 4)
    public static let math = InlineStyle(rawValue: 1 << 5)
}
