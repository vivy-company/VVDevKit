import Foundation
import Combine

/// Protocol for LSP client integration
/// Users implement this protocol to connect their LSP server to VVCode
public protocol VVLSPClient: AnyObject, Sendable {
    /// Request completions at a position
    func completions(
        at position: VVTextPosition,
        in document: DocumentURI,
        triggerKind: VVCompletionTriggerKind,
        triggerCharacter: String?
    ) async throws -> [VVCompletionItem]

    /// Request hover information at a position
    func hover(
        at position: VVTextPosition,
        in document: DocumentURI
    ) async throws -> VVHoverInfo?

    /// Request signature help at a position
    func signatureHelp(
        at position: VVTextPosition,
        in document: DocumentURI
    ) async throws -> VVSignatureHelp?

    /// Request go-to-definition
    func definition(
        at position: VVTextPosition,
        in document: DocumentURI
    ) async throws -> [VVLocation]?

    /// Request document diagnostics
    func diagnostics(for document: DocumentURI) async throws -> [VVDiagnostic]

    /// Publisher for diagnostic updates
    var diagnosticsPublisher: AnyPublisher<DocumentDiagnostics, Never> { get }

    /// Notify document opened
    func documentOpened(_ document: DocumentURI, text: String, language: String) async

    /// Notify document changed
    func documentChanged(_ document: DocumentURI, changes: [VVTextChange]) async

    /// Notify document closed
    func documentClosed(_ document: DocumentURI) async
}

/// Document URI type
public typealias DocumentURI = String

/// Text position (0-indexed line and character)
public struct VVTextPosition: Sendable, Hashable, Codable, Comparable {
    /// Line number (0-indexed)
    public let line: Int

    /// Character offset (UTF-16 code units, 0-indexed)
    public let character: Int

    public init(line: Int, character: Int) {
        self.line = line
        self.character = character
    }

    /// Convert from 1-indexed line number
    public static func from(oneBased lineNumber: Int, character: Int) -> VVTextPosition {
        VVTextPosition(line: lineNumber - 1, character: character)
    }

    public static func < (lhs: VVTextPosition, rhs: VVTextPosition) -> Bool {
        if lhs.line != rhs.line {
            return lhs.line < rhs.line
        }
        return lhs.character < rhs.character
    }
}

/// Text change notification
public struct VVTextChange: Sendable {
    public let range: VVTextRange?
    public let text: String

    public init(range: VVTextRange?, text: String) {
        self.range = range
        self.text = text
    }

    /// Full document sync
    public static func full(_ text: String) -> VVTextChange {
        VVTextChange(range: nil, text: text)
    }
}

/// Text range
public struct VVTextRange: Sendable, Hashable, Codable {
    public let start: VVTextPosition
    public let end: VVTextPosition

    public init(start: VVTextPosition, end: VVTextPosition) {
        self.start = start
        self.end = end
    }
}

/// Location in a document
public struct VVLocation: Sendable {
    public let uri: DocumentURI
    public let range: VVTextRange

    public init(uri: DocumentURI, range: VVTextRange) {
        self.uri = uri
        self.range = range
    }
}

/// Completion trigger kind
public enum VVCompletionTriggerKind: Int, Sendable {
    case invoked = 1
    case triggerCharacter = 2
    case triggerForIncompleteCompletions = 3
}

/// Diagnostics for a document
public struct DocumentDiagnostics: Sendable {
    public let uri: DocumentURI
    public let diagnostics: [VVDiagnostic]

    public init(uri: DocumentURI, diagnostics: [VVDiagnostic]) {
        self.uri = uri
        self.diagnostics = diagnostics
    }
}
