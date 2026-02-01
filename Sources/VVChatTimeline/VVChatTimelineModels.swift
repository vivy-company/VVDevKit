import Foundation

public enum VVChatMessageRole: String, Sendable {
    case user
    case assistant
    case system
}

public enum VVChatMessageState: Sendable {
    case draft
    case final
}

public struct VVChatMessage: Identifiable, Hashable, Sendable {
    public let id: String
    public var role: VVChatMessageRole
    public var state: VVChatMessageState
    public var content: String
    public var revision: Int
    public var timestamp: Date?

    public init(
        id: String = UUID().uuidString,
        role: VVChatMessageRole,
        state: VVChatMessageState,
        content: String,
        revision: Int = 0,
        timestamp: Date? = nil
    ) {
        self.id = id
        self.role = role
        self.state = state
        self.content = content
        self.revision = revision
        self.timestamp = timestamp
    }

    public var isStreaming: Bool {
        state == .draft
    }
}
