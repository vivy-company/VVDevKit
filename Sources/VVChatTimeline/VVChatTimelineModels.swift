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
    /// Optional left lane reservation in points. Used to keep timeline columns aligned
    /// even when an icon is only rendered on some rows.
    public var leadingLaneWidth: CGFloat?
    public var leadingIconURL: String?
    public var leadingIconSize: CGFloat?
    public var leadingIconSpacing: CGFloat?
    public var showsTimestamp: Bool?
    public var timestampPrefix: String?
    public var timestampSuffix: String?
    public var timestampPrefixIconURL: String?
    public var timestampSuffixIconURL: String?
    public var timestampIconSize: CGFloat?
    public var timestampIconSpacing: CGFloat?
    public var textOpacityMultiplier: Float?
    public var prefixGlyphColor: SIMD4<Float>?
    public var prefixGlyphCount: Int?

    public init(
        bubbleStyle: VVChatBubbleStyle? = nil,
        showsHeader: Bool? = nil,
        headerTitle: String? = nil,
        headerIconURL: String? = nil,
        leadingLaneWidth: CGFloat? = nil,
        leadingIconURL: String? = nil,
        leadingIconSize: CGFloat? = nil,
        leadingIconSpacing: CGFloat? = nil,
        showsTimestamp: Bool? = nil,
        timestampPrefix: String? = nil,
        timestampSuffix: String? = nil,
        timestampPrefixIconURL: String? = nil,
        timestampSuffixIconURL: String? = nil,
        timestampIconSize: CGFloat? = nil,
        timestampIconSpacing: CGFloat? = nil,
        textOpacityMultiplier: Float? = nil,
        prefixGlyphColor: SIMD4<Float>? = nil,
        prefixGlyphCount: Int? = nil
    ) {
        self.bubbleStyle = bubbleStyle
        self.showsHeader = showsHeader
        self.headerTitle = headerTitle
        self.headerIconURL = headerIconURL
        self.leadingLaneWidth = leadingLaneWidth
        self.leadingIconURL = leadingIconURL
        self.leadingIconSize = leadingIconSize
        self.leadingIconSpacing = leadingIconSpacing
        self.showsTimestamp = showsTimestamp
        self.timestampPrefix = timestampPrefix
        self.timestampSuffix = timestampSuffix
        self.timestampPrefixIconURL = timestampPrefixIconURL
        self.timestampSuffixIconURL = timestampSuffixIconURL
        self.timestampIconSize = timestampIconSize
        self.timestampIconSpacing = timestampIconSpacing
        self.textOpacityMultiplier = textOpacityMultiplier
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
