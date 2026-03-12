import Foundation
import VVMarkdown

public enum VVChatMessageRole: String, Sendable {
    case user
    case assistant
    case system
}

public enum VVChatMessageState: Sendable {
    case draft
    case final
}

public struct VVHeaderBadge: Hashable, Sendable {
    public let text: String
    public let color: SIMD4<Float>

    public init(text: String, color: SIMD4<Float>) {
        self.text = text
        self.color = color
    }
}

public struct VVChatSummaryCardRow: Hashable, Sendable {
    public var id: String
    public var title: String
    public var subtitle: String?
    public var iconURL: String?
    public var actionURL: String?
    public var titleColor: SIMD4<Float>?
    public var subtitleColor: SIMD4<Float>?
    public var additionsText: String?
    public var additionsColor: SIMD4<Float>?
    public var deletionsText: String?
    public var deletionsColor: SIMD4<Float>?
    public var hoverFillColor: SIMD4<Float>?

    public init(
        id: String,
        title: String,
        subtitle: String? = nil,
        iconURL: String? = nil,
        actionURL: String? = nil,
        titleColor: SIMD4<Float>? = nil,
        subtitleColor: SIMD4<Float>? = nil,
        additionsText: String? = nil,
        additionsColor: SIMD4<Float>? = nil,
        deletionsText: String? = nil,
        deletionsColor: SIMD4<Float>? = nil,
        hoverFillColor: SIMD4<Float>? = nil
    ) {
        self.id = id
        self.title = title
        self.subtitle = subtitle
        self.iconURL = iconURL
        self.actionURL = actionURL
        self.titleColor = titleColor
        self.subtitleColor = subtitleColor
        self.additionsText = additionsText
        self.additionsColor = additionsColor
        self.deletionsText = deletionsText
        self.deletionsColor = deletionsColor
        self.hoverFillColor = hoverFillColor
    }
}

public struct VVChatSummaryCard: Hashable, Sendable {
    public var title: String
    public var iconURL: String?
    public var subtitle: String?
    public var rows: [VVChatSummaryCardRow]
    public var titleColor: SIMD4<Float>?
    public var subtitleColor: SIMD4<Float>?
    public var dividerColor: SIMD4<Float>?
    public var rowDividerColor: SIMD4<Float>?

    public init(
        title: String,
        iconURL: String? = nil,
        subtitle: String? = nil,
        rows: [VVChatSummaryCardRow],
        titleColor: SIMD4<Float>? = nil,
        subtitleColor: SIMD4<Float>? = nil,
        dividerColor: SIMD4<Float>? = nil,
        rowDividerColor: SIMD4<Float>? = nil
    ) {
        self.title = title
        self.iconURL = iconURL
        self.subtitle = subtitle
        self.rows = rows
        self.titleColor = titleColor
        self.subtitleColor = subtitleColor
        self.dividerColor = dividerColor
        self.rowDividerColor = rowDividerColor
    }
}

public struct VVChatInlineDiffContent: Hashable, Sendable {
    public var unifiedDiff: String
    public var renderOptions: VVDiffRenderOptions

    public init(
        unifiedDiff: String,
        renderOptions: VVDiffRenderOptions = .compactInline
    ) {
        self.unifiedDiff = unifiedDiff
        self.renderOptions = renderOptions
    }
}

public enum VVChatCustomContent: Hashable, Sendable {
    case summaryCard(VVChatSummaryCard)
    case inlineDiff(VVChatInlineDiffContent)
}

public struct VVChatMessagePresentation: Hashable, Sendable {
    public var bubbleStyle: VVChatBubbleStyle?
    public var showsHeader: Bool?
    public var headerTitle: String?
    public var headerIconURL: String?
    public var headerTrailingIconURL: String?
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
    public var contentFontScale: CGFloat?
    public var textOpacityMultiplier: Float?
    public var prefixGlyphColor: SIMD4<Float>?
    public var prefixGlyphCount: Int?
    /// Colored text badges rendered inline after the header title.
    public var headerBadges: [VVHeaderBadge]?

    public init(
        bubbleStyle: VVChatBubbleStyle? = nil,
        showsHeader: Bool? = nil,
        headerTitle: String? = nil,
        headerIconURL: String? = nil,
        headerTrailingIconURL: String? = nil,
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
        contentFontScale: CGFloat? = nil,
        textOpacityMultiplier: Float? = nil,
        prefixGlyphColor: SIMD4<Float>? = nil,
        prefixGlyphCount: Int? = nil,
        headerBadges: [VVHeaderBadge]? = nil
    ) {
        self.bubbleStyle = bubbleStyle
        self.showsHeader = showsHeader
        self.headerTitle = headerTitle
        self.headerIconURL = headerIconURL
        self.headerTrailingIconURL = headerTrailingIconURL
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
        self.contentFontScale = contentFontScale
        self.textOpacityMultiplier = textOpacityMultiplier
        self.prefixGlyphColor = prefixGlyphColor
        self.prefixGlyphCount = prefixGlyphCount
        self.headerBadges = headerBadges
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
    public var customContent: VVChatCustomContent?

    public init(
        id: String = UUID().uuidString,
        role: VVChatMessageRole,
        state: VVChatMessageState,
        content: String,
        revision: Int = 0,
        timestamp: Date? = nil,
        presentation: VVChatMessagePresentation? = nil,
        customContent: VVChatCustomContent? = nil
    ) {
        self.id = id
        self.role = role
        self.state = state
        self.content = content
        self.revision = revision
        self.timestamp = timestamp
        self.presentation = presentation
        self.customContent = customContent
    }

    public var isStreaming: Bool {
        state == .draft
    }
}

public enum VVChatTimelineItemKind: Hashable, Sendable {
    case message(role: VVChatMessageRole)
    case toolGroup
    case toolCall
    case summaryCard
    case systemEvent
    case diffCard
    case customWidget(name: String)

    static func classify(message: VVChatMessage) -> VVChatTimelineItemKind {
        if let customContent = message.customContent {
            switch customContent {
            case .summaryCard:
                return .summaryCard
            case .inlineDiff:
                return .diffCard
            }
        }
        return .message(role: message.role)
    }

    static func classify(customKind: String) -> VVChatTimelineItemKind {
        let normalized = customKind
            .trimmingCharacters(in: .whitespacesAndNewlines)
            .lowercased()

        switch normalized {
        case "toolgroup", "tool_call_group", "tool-call-group", "toolcallgroup":
            return .toolGroup
        case "toolcall", "tool_call", "tool-call", "toolcalldetail", "tool_call_detail", "tool-call-detail":
            return .toolCall
        case "summarycard", "summary_card", "summary-card":
            return .summaryCard
        case "systemevent", "system_event", "system-event":
            return .systemEvent
        case "diffcard", "diff_card", "diff-card", "inlinediff", "inline_diff", "inline-diff":
            return .diffCard
        case "":
            return .customWidget(name: "custom")
        default:
            return .customWidget(name: normalized)
        }
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

public enum VVChatTimelineItemContent: Hashable, Sendable {
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

    public var revision: Int {
        switch self {
        case .message(let message):
            return message.revision
        case .custom(let custom):
            return custom.revision
        }
    }

    public var timestamp: Date? {
        switch self {
        case .message(let message):
            return message.timestamp
        case .custom(let custom):
            return custom.timestamp
        }
    }

    public var kind: VVChatTimelineItemKind {
        switch self {
        case .message(let message):
            return VVChatTimelineItemKind.classify(message: message)
        case .custom(let custom):
            return VVChatTimelineItemKind.classify(customKind: custom.kind)
        }
    }

    public var entry: VVChatTimelineEntry {
        switch self {
        case .message(let message):
            return .message(message)
        case .custom(let custom):
            return .custom(custom)
        }
    }
}

public struct VVChatTimelineItemModel: Identifiable, Hashable, Sendable {
    public let content: VVChatTimelineItemContent

    public init(content: VVChatTimelineItemContent) {
        self.content = content
    }

    public init(message: VVChatMessage) {
        self.content = .message(message)
    }

    public init(customEntry: VVCustomTimelineEntry) {
        self.content = .custom(customEntry)
    }

    public var id: String {
        content.id
    }

    public var kind: VVChatTimelineItemKind {
        content.kind
    }

    public var revision: Int {
        content.revision
    }

    public var timestamp: Date? {
        content.timestamp
    }

    public var entry: VVChatTimelineEntry {
        content.entry
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
