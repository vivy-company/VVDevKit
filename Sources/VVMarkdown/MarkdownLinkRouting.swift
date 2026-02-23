import Foundation

public enum VVMarkdownLinkDecision: Sendable {
    case handled
    case openExternally
    case ignore
}

public struct VVMarkdownLinkContext: Sendable {
    public let raw: String
    public let resolvedURL: URL?
    public let baseURL: URL?

    public init(raw: String, resolvedURL: URL?, baseURL: URL?) {
        self.raw = raw
        self.resolvedURL = resolvedURL
        self.baseURL = baseURL
    }
}

public typealias VVMarkdownLinkHandler = @MainActor (VVMarkdownLinkContext) -> VVMarkdownLinkDecision
