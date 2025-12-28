import Foundation

/// Completion item from LSP
public struct VVCompletionItem: Sendable, Identifiable {
    public var id: String { label }

    /// Label shown in the completion list
    public let label: String

    /// Kind of completion item
    public let kind: VVCompletionKind

    /// Detail text (e.g., type signature)
    public let detail: String?

    /// Documentation for the item
    public let documentation: String?

    /// Text to insert when selected
    public let insertText: String

    /// Filter text for fuzzy matching
    public let filterText: String?

    /// Sort text for ordering
    public let sortText: String?

    /// Whether this item is preselected
    public let preselect: Bool

    /// Insert text format
    public let insertTextFormat: InsertTextFormat

    /// Additional text edits (for auto-imports, etc.)
    public let additionalTextEdits: [VVTextEdit]?

    public init(
        label: String,
        kind: VVCompletionKind = .text,
        detail: String? = nil,
        documentation: String? = nil,
        insertText: String? = nil,
        filterText: String? = nil,
        sortText: String? = nil,
        preselect: Bool = false,
        insertTextFormat: InsertTextFormat = .plainText,
        additionalTextEdits: [VVTextEdit]? = nil
    ) {
        self.label = label
        self.kind = kind
        self.detail = detail
        self.documentation = documentation
        self.insertText = insertText ?? label
        self.filterText = filterText
        self.sortText = sortText
        self.preselect = preselect
        self.insertTextFormat = insertTextFormat
        self.additionalTextEdits = additionalTextEdits
    }

    public enum InsertTextFormat: Int, Sendable {
        case plainText = 1
        case snippet = 2
    }
}

/// Completion item kind
public enum VVCompletionKind: Int, Sendable {
    case text = 1
    case method = 2
    case function = 3
    case constructor = 4
    case field = 5
    case variable = 6
    case `class` = 7
    case interface = 8
    case module = 9
    case property = 10
    case unit = 11
    case value = 12
    case `enum` = 13
    case keyword = 14
    case snippet = 15
    case color = 16
    case file = 17
    case reference = 18
    case folder = 19
    case enumMember = 20
    case constant = 21
    case `struct` = 22
    case event = 23
    case `operator` = 24
    case typeParameter = 25

    /// Icon name for this kind
    public var iconName: String {
        switch self {
        case .text: return "text.alignleft"
        case .method, .function: return "function"
        case .constructor: return "hammer"
        case .field, .property: return "rectangle.and.pencil.and.ellipsis"
        case .variable: return "x.squareroot"
        case .class, .interface, .struct: return "cube"
        case .module: return "shippingbox"
        case .unit, .value: return "number"
        case .enum, .enumMember: return "list.bullet"
        case .keyword: return "textformat.abc"
        case .snippet: return "doc.text"
        case .color: return "paintpalette"
        case .file, .folder: return "doc"
        case .reference: return "link"
        case .constant: return "c.circle"
        case .event: return "bolt"
        case .operator: return "plus.minus"
        case .typeParameter: return "t.circle"
        }
    }
}

/// Text edit
public struct VVTextEdit: Sendable {
    public let range: VVTextRange
    public let newText: String

    public init(range: VVTextRange, newText: String) {
        self.range = range
        self.newText = newText
    }
}
