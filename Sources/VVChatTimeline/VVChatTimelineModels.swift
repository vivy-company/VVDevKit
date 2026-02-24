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

public struct VVChatMessagePresentation: Hashable, Sendable {
    public var bubbleStyle: VVChatBubbleStyle?
    public var showsHeader: Bool?
    public var headerTitle: String?
    public var headerIconURL: String?
    public var showsTimestamp: Bool?
    public var prefixGlyphColor: SIMD4<Float>?
    public var prefixGlyphCount: Int?

    public init(
        bubbleStyle: VVChatBubbleStyle? = nil,
        showsHeader: Bool? = nil,
        headerTitle: String? = nil,
        headerIconURL: String? = nil,
        showsTimestamp: Bool? = nil,
        prefixGlyphColor: SIMD4<Float>? = nil,
        prefixGlyphCount: Int? = nil
    ) {
        self.bubbleStyle = bubbleStyle
        self.showsHeader = showsHeader
        self.headerTitle = headerTitle
        self.headerIconURL = headerIconURL
        self.showsTimestamp = showsTimestamp
        self.prefixGlyphColor = prefixGlyphColor
        self.prefixGlyphCount = prefixGlyphCount
    }
}

public struct VVChatMessage: Identifiable, Hashable, Sendable {
    public let id: String
    public var role: VVChatMessageRole
    public var state: VVChatMessageState
    public var content: String
    public var revision: Int
    public var timestamp: Date?
    public var presentation: VVChatMessagePresentation?

    public init(
        id: String = UUID().uuidString,
        role: VVChatMessageRole,
        state: VVChatMessageState,
        content: String,
        revision: Int = 0,
        timestamp: Date? = nil,
        presentation: VVChatMessagePresentation? = nil
    ) {
        self.id = id
        self.role = role
        self.state = state
        self.content = content
        self.revision = revision
        self.timestamp = timestamp
        self.presentation = presentation
    }

    public var isStreaming: Bool {
        state == .draft
    }
}

public struct VVCustomTimelineEntry: Identifiable, Hashable, Sendable {
    public let id: String
    public let kind: String
    public let payload: Data
    public let revision: Int
    public let timestamp: Date?

    public init(
        id: String,
        kind: String,
        payload: Data,
        revision: Int = 0,
        timestamp: Date? = nil
    ) {
        self.id = id
        self.kind = kind
        self.payload = payload
        self.revision = revision
        self.timestamp = timestamp
    }
}

public enum VVChatTimelineEntry: Identifiable, Hashable, Sendable {
    case message(VVChatMessage)
    case custom(VVCustomTimelineEntry)

    public var id: String {
        switch self {
        case .message(let message):
            return message.id
        case .custom(let custom):
            return custom.id
        }
    }
}
