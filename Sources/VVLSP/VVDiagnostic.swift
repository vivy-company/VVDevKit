import Foundation

/// Diagnostic message from LSP
public struct VVDiagnostic: Sendable, Identifiable, Hashable {
    public var id: String {
        "\(range.start.line):\(range.start.character)-\(message)"
    }

    /// Range of the diagnostic
    public let range: VVTextRange

    /// Severity of the diagnostic
    public let severity: VVDiagnosticSeverity

    /// Diagnostic code (for quick fixes)
    public let code: String?

    /// Source of the diagnostic (e.g., "swiftc", "eslint")
    public let source: String?

    /// Human-readable message
    public let message: String

    /// Related information
    public let relatedInformation: [VVDiagnosticRelatedInfo]?

    /// Tags for styling
    public let tags: [VVDiagnosticTag]?

    public init(
        range: VVTextRange,
        severity: VVDiagnosticSeverity,
        code: String? = nil,
        source: String? = nil,
        message: String,
        relatedInformation: [VVDiagnosticRelatedInfo]? = nil,
        tags: [VVDiagnosticTag]? = nil
    ) {
        self.range = range
        self.severity = severity
        self.code = code
        self.source = source
        self.message = message
        self.relatedInformation = relatedInformation
        self.tags = tags
    }

    public static func == (lhs: VVDiagnostic, rhs: VVDiagnostic) -> Bool {
        lhs.id == rhs.id
    }

    public func hash(into hasher: inout Hasher) {
        hasher.combine(id)
    }
}

/// Diagnostic severity
public enum VVDiagnosticSeverity: Int, Sendable {
    case error = 1
    case warning = 2
    case information = 3
    case hint = 4

    /// Icon name for this severity
    public var iconName: String {
        switch self {
        case .error: return "xmark.circle.fill"
        case .warning: return "exclamationmark.triangle.fill"
        case .information: return "info.circle.fill"
        case .hint: return "lightbulb.fill"
        }
    }
}

/// Diagnostic tag
public enum VVDiagnosticTag: Int, Sendable {
    case unnecessary = 1
    case deprecated = 2
}

/// Related diagnostic information
public struct VVDiagnosticRelatedInfo: Sendable, Hashable {
    public let location: VVLocation
    public let message: String

    public init(location: VVLocation, message: String) {
        self.location = location
        self.message = message
    }

    public static func == (lhs: VVDiagnosticRelatedInfo, rhs: VVDiagnosticRelatedInfo) -> Bool {
        lhs.location.uri == rhs.location.uri && lhs.message == rhs.message
    }

    public func hash(into hasher: inout Hasher) {
        hasher.combine(location.uri)
        hasher.combine(message)
    }
}

// MARK: - Hover

/// Hover information
public struct VVHoverInfo: Sendable {
    /// Content of the hover
    public let contents: [VVMarkupContent]

    /// Range to highlight while showing hover
    public let range: VVTextRange?

    public init(contents: [VVMarkupContent], range: VVTextRange? = nil) {
        self.contents = contents
        self.range = range
    }

    /// Convenience initializer for a single markdown/plaintext string
    public init(contents: String, range: VVTextRange? = nil) {
        self.contents = [VVMarkupContent(kind: .markdown, value: contents)]
        self.range = range
    }
}

/// Markup content (for hover, documentation, etc.)
public struct VVMarkupContent: Sendable, Equatable {
    public let kind: Kind
    public let value: String

    public init(kind: Kind, value: String) {
        self.kind = kind
        self.value = value
    }

    public enum Kind: String, Sendable {
        case plaintext
        case markdown
    }
}

// MARK: - Signature Help

/// Signature help information
public struct VVSignatureHelp: Sendable {
    /// Available signatures
    public let signatures: [VVSignatureInfo]

    /// Active signature index
    public let activeSignature: Int?

    /// Active parameter index
    public let activeParameter: Int?

    public init(
        signatures: [VVSignatureInfo],
        activeSignature: Int? = nil,
        activeParameter: Int? = nil
    ) {
        self.signatures = signatures
        self.activeSignature = activeSignature
        self.activeParameter = activeParameter
    }
}

/// Signature information
public struct VVSignatureInfo: Sendable, Identifiable {
    public var id: String { label }

    /// Signature label
    public let label: String

    /// Documentation
    public let documentation: String?

    /// Parameters
    public let parameters: [VVParameterInfo]

    public init(label: String, documentation: String? = nil, parameters: [VVParameterInfo] = []) {
        self.label = label
        self.documentation = documentation
        self.parameters = parameters
    }
}

/// Parameter information
public struct VVParameterInfo: Sendable, Identifiable {
    public var id: String { label }

    /// Parameter label
    public let label: String

    /// Documentation
    public let documentation: String?

    public init(label: String, documentation: String? = nil) {
        self.label = label
        self.documentation = documentation
    }
}
