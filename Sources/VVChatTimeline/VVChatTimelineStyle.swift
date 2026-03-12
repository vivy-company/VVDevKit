import Foundation
import VVMarkdown
import VVMetalPrimitives

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

public enum VVChatBubbleAlignment: Sendable {
    case leading
    case center
    case trailing
}

public struct VVChatBubbleStyle: Hashable, Sendable {
    public var isEnabled: Bool
    public var color: SIMD4<Float>
    public var borderColor: SIMD4<Float>
    public var borderWidth: CGFloat
    public var cornerRadius: CGFloat
    public var insets: VVInsets
    public var maxWidth: CGFloat
    public var alignment: VVChatBubbleAlignment

    public init(
        isEnabled: Bool = true,
        color: SIMD4<Float>,
        borderColor: SIMD4<Float> = .clear,
        borderWidth: CGFloat = 0,
        cornerRadius: CGFloat = 14,
        insets: VVInsets = .init(top: 10, left: 12, bottom: 10, right: 12),
        maxWidth: CGFloat = 420,
        alignment: VVChatBubbleAlignment = .trailing
    ) {
        self.isEnabled = isEnabled
        self.color = color
        self.borderColor = borderColor
        self.borderWidth = borderWidth
        self.cornerRadius = cornerRadius
        self.insets = insets
        self.maxWidth = maxWidth
        self.alignment = alignment
    }
}

public struct VVChatTimelineMotionStyle: Hashable, Sendable {
    public var layoutTransition: VVTransition
    public var layoutAnimation: VVAnimationDescriptor
    public var viewportFollowAnimation: VVAnimationDescriptor
    public var viewportClampAnimation: VVAnimationDescriptor
    public var jumpToLatestAnimation: VVAnimationDescriptor
    public var streamContentAnimation: VVAnimationDescriptor
    public var streamContentLift: CGFloat
    public var updateBatchInterval: TimeInterval

    public init(
        layoutTransition: VVTransition = .accordion,
        layoutAnimation: VVAnimationDescriptor = .smooth(duration: 0.26),
        viewportFollowAnimation: VVAnimationDescriptor = .smooth(duration: 0.24),
        viewportClampAnimation: VVAnimationDescriptor = .smooth(duration: 0.22),
        jumpToLatestAnimation: VVAnimationDescriptor = .timing(duration: 0.34, easing: .easeOut),
        streamContentAnimation: VVAnimationDescriptor = .timing(duration: 0.18, easing: .easeOut),
        streamContentLift: CGFloat = 10,
        updateBatchInterval: TimeInterval = 1.0 / 45.0
    ) {
        self.layoutTransition = layoutTransition
        self.layoutAnimation = layoutAnimation
        self.viewportFollowAnimation = viewportFollowAnimation
        self.viewportClampAnimation = viewportClampAnimation
        self.jumpToLatestAnimation = jumpToLatestAnimation
        self.streamContentAnimation = streamContentAnimation
        self.streamContentLift = max(0, streamContentLift)
        self.updateBatchInterval = updateBatchInterval
    }
}

public struct VVChatTimelineCacheBudget: Hashable, Sendable {
    public static let defaultRenderedMessageCostLimit = 12 * 1024 * 1024
    public static let defaultPreparedMarkdownCostLimit = 64 * 1024 * 1024
    public static let defaultDraftPreparedStateCostLimit = 24 * 1024 * 1024
    public static let defaultMaterializedPreparedLayoutCostLimit = 24 * 1024 * 1024
    public static let defaultSceneWindowCostLimit = 24 * 1024 * 1024
    public static let defaultSelectionWindowCostLimit = 12 * 1024 * 1024

    public var renderedMessageCountLimit: Int
    public var renderedMessageCostLimit: Int
    public var preparedMarkdownCountLimit: Int
    public var preparedMarkdownCostLimit: Int
    public var draftPreparedStateCountLimit: Int
    public var draftPreparedStateCostLimit: Int
    public var materializedPreparedLayoutCostLimit: Int
    public var sceneWindowCountLimit: Int
    public var sceneWindowCostLimit: Int
    public var selectionWindowCountLimit: Int
    public var selectionWindowCostLimit: Int

    public init(
        renderedMessageCountLimit: Int = 50,
        renderedMessageCostLimit: Int = VVChatTimelineCacheBudget.defaultRenderedMessageCostLimit,
        preparedMarkdownCountLimit: Int? = nil,
        preparedMarkdownCostLimit: Int = VVChatTimelineCacheBudget.defaultPreparedMarkdownCostLimit,
        draftPreparedStateCountLimit: Int? = nil,
        draftPreparedStateCostLimit: Int = VVChatTimelineCacheBudget.defaultDraftPreparedStateCostLimit,
        materializedPreparedLayoutCostLimit: Int = VVChatTimelineCacheBudget.defaultMaterializedPreparedLayoutCostLimit,
        sceneWindowCountLimit: Int? = nil,
        sceneWindowCostLimit: Int = VVChatTimelineCacheBudget.defaultSceneWindowCostLimit,
        selectionWindowCountLimit: Int? = nil,
        selectionWindowCostLimit: Int = VVChatTimelineCacheBudget.defaultSelectionWindowCostLimit
    ) {
        let renderedMessageCountLimit = Self.normalizedCountLimit(renderedMessageCountLimit)

        self.renderedMessageCountLimit = renderedMessageCountLimit
        self.renderedMessageCostLimit = Self.normalizedCostLimit(renderedMessageCostLimit)
        self.preparedMarkdownCountLimit = Self.normalizedCountLimit(
            preparedMarkdownCountLimit ?? renderedMessageCountLimit
        )
        self.preparedMarkdownCostLimit = Self.normalizedCostLimit(preparedMarkdownCostLimit)
        self.draftPreparedStateCountLimit = Self.normalizedCountLimit(
            draftPreparedStateCountLimit ?? max(2, renderedMessageCountLimit)
        )
        self.draftPreparedStateCostLimit = Self.normalizedCostLimit(draftPreparedStateCostLimit)
        self.materializedPreparedLayoutCostLimit = Self.normalizedCostLimit(materializedPreparedLayoutCostLimit)
        self.sceneWindowCountLimit = Self.normalizedCountLimit(
            sceneWindowCountLimit ?? max(8, renderedMessageCountLimit * 4)
        )
        self.sceneWindowCostLimit = Self.normalizedCostLimit(sceneWindowCostLimit)
        self.selectionWindowCountLimit = Self.normalizedCountLimit(
            selectionWindowCountLimit ?? max(8, renderedMessageCountLimit * 3)
        )
        self.selectionWindowCostLimit = Self.normalizedCostLimit(selectionWindowCostLimit)
    }

    public static func compatible(renderedCacheLimit: Int) -> Self {
        Self(renderedMessageCountLimit: renderedCacheLimit)
    }

    func applyingCompatibleRenderedMessageCountLimit(_ renderedCacheLimit: Int) -> Self {
        let renderedCacheLimit = Self.normalizedCountLimit(renderedCacheLimit)
        let currentCompatible = Self.compatible(renderedCacheLimit: renderedMessageCountLimit)
        let nextCompatible = Self.compatible(renderedCacheLimit: renderedCacheLimit)
        var updated = self
        updated.renderedMessageCountLimit = renderedCacheLimit

        if preparedMarkdownCountLimit == currentCompatible.preparedMarkdownCountLimit {
            updated.preparedMarkdownCountLimit = nextCompatible.preparedMarkdownCountLimit
        }
        if draftPreparedStateCountLimit == currentCompatible.draftPreparedStateCountLimit {
            updated.draftPreparedStateCountLimit = nextCompatible.draftPreparedStateCountLimit
        }
        if sceneWindowCountLimit == currentCompatible.sceneWindowCountLimit {
            updated.sceneWindowCountLimit = nextCompatible.sceneWindowCountLimit
        }
        if selectionWindowCountLimit == currentCompatible.selectionWindowCountLimit {
            updated.selectionWindowCountLimit = nextCompatible.selectionWindowCountLimit
        }

        return updated.normalized()
    }

    func normalized() -> Self {
        Self(
            renderedMessageCountLimit: renderedMessageCountLimit,
            renderedMessageCostLimit: renderedMessageCostLimit,
            preparedMarkdownCountLimit: preparedMarkdownCountLimit,
            preparedMarkdownCostLimit: preparedMarkdownCostLimit,
            draftPreparedStateCountLimit: draftPreparedStateCountLimit,
            draftPreparedStateCostLimit: draftPreparedStateCostLimit,
            materializedPreparedLayoutCostLimit: materializedPreparedLayoutCostLimit,
            sceneWindowCountLimit: sceneWindowCountLimit,
            sceneWindowCostLimit: sceneWindowCostLimit,
            selectionWindowCountLimit: selectionWindowCountLimit,
            selectionWindowCostLimit: selectionWindowCostLimit
        )
    }

    private static func normalizedCountLimit(_ limit: Int) -> Int {
        max(0, limit)
    }

    private static func normalizedCostLimit(_ limit: Int) -> Int {
        max(0, limit)
    }
}

public struct VVChatTimelineStyle {
    public var theme: MarkdownTheme
    public var draftTheme: MarkdownTheme
    public var baseFont: VVFont
    public var draftFont: VVFont
    public var headerFont: VVFont
    public var timestampFont: VVFont
    public var loadingIndicatorFont: VVFont
    public var headerTextColor: SIMD4<Float>
    public var timestampTextColor: SIMD4<Float>
    public var loadingIndicatorTextColor: SIMD4<Float>
    public var userBubbleColor: SIMD4<Float>
    public var userBubbleBorderColor: SIMD4<Float>
    public var userBubbleBorderWidth: CGFloat
    public var userBubbleCornerRadius: CGFloat
    public var userBubbleInsets: VVInsets
    public var userBubbleMaxWidth: CGFloat
    public var userBubbleAlignment: VVChatBubbleAlignment
    public var assistantBubbleEnabled: Bool
    public var assistantBubbleColor: SIMD4<Float>
    public var assistantBubbleBorderColor: SIMD4<Float>
    public var assistantBubbleBorderWidth: CGFloat
    public var assistantBubbleCornerRadius: CGFloat
    public var assistantBubbleInsets: VVInsets
    public var assistantBubbleMaxWidth: CGFloat
    public var assistantBubbleAlignment: VVChatBubbleAlignment
    public var systemBubbleEnabled: Bool
    public var systemBubbleColor: SIMD4<Float>
    public var systemBubbleBorderColor: SIMD4<Float>
    public var systemBubbleBorderWidth: CGFloat
    public var systemBubbleCornerRadius: CGFloat
    public var systemBubbleInsets: VVInsets
    public var systemBubbleMaxWidth: CGFloat
    public var systemBubbleAlignment: VVChatBubbleAlignment
    public var userHeaderEnabled: Bool
    public var assistantHeaderEnabled: Bool
    public var systemHeaderEnabled: Bool
    public var userHeaderTitle: String
    public var assistantHeaderTitle: String
    public var systemHeaderTitle: String
    public var userHeaderIconURL: String?
    public var assistantHeaderIconURL: String?
    public var systemHeaderIconURL: String?
    public var headerIconSize: CGFloat
    public var headerIconSpacing: CGFloat
    public var userTimestampEnabled: Bool
    public var assistantTimestampEnabled: Bool
    public var systemTimestampEnabled: Bool
    public var userTimestampSuffix: String
    public var assistantTimestampSuffix: String
    public var systemTimestampSuffix: String
    public var bubbleMetadataMinWidth: CGFloat
    public var headerSpacing: CGFloat
    public var footerSpacing: CGFloat
    public var loadingIndicatorText: String
    public var timelineInsets: VVInsets
    public var messageSpacing: CGFloat
    public var userInsets: VVInsets
    public var assistantInsets: VVInsets
    public var systemInsets: VVInsets
    public var pinThreshold: CGFloat
    public var backgroundColor: SIMD4<Float>
    private var _renderedCacheLimit: Int
    private var _cacheBudget: VVChatTimelineCacheBudget
    public var renderedCacheLimit: Int {
        get { _renderedCacheLimit }
        set {
            let renderedCacheLimit = max(0, newValue)
            _renderedCacheLimit = renderedCacheLimit
            _cacheBudget = _cacheBudget.applyingCompatibleRenderedMessageCountLimit(renderedCacheLimit)
        }
    }
    public var cacheBudget: VVChatTimelineCacheBudget {
        get { _cacheBudget }
        set {
            let normalizedBudget = newValue.normalized()
            _cacheBudget = normalizedBudget
            _renderedCacheLimit = normalizedBudget.renderedMessageCountLimit
        }
    }
    public var motion: VVChatTimelineMotionStyle

    public init(
        theme: MarkdownTheme = .dark,
        draftTheme: MarkdownTheme? = nil,
        baseFont: VVFont = .systemFont(ofSize: 14),
        draftFont: VVFont? = nil,
        headerFont: VVFont? = nil,
        timestampFont: VVFont? = nil,
        loadingIndicatorFont: VVFont? = nil,
        headerTextColor: SIMD4<Float>? = nil,
        timestampTextColor: SIMD4<Float>? = nil,
        loadingIndicatorTextColor: SIMD4<Float>? = nil,
        userBubbleColor: SIMD4<Float> = .darkText,
        userBubbleBorderColor: SIMD4<Float> = .clear,
        userBubbleBorderWidth: CGFloat = 0,
        userBubbleCornerRadius: CGFloat = 14,
        userBubbleInsets: VVInsets = .init(top: 10, left: 12, bottom: 10, right: 12),
        userBubbleMaxWidth: CGFloat = 420,
        userBubbleAlignment: VVChatBubbleAlignment = .trailing,
        assistantBubbleEnabled: Bool = true,
        assistantBubbleColor: SIMD4<Float> = .rgba(0.12, 0.14, 0.18),
        assistantBubbleBorderColor: SIMD4<Float> = .clear,
        assistantBubbleBorderWidth: CGFloat = 0,
        assistantBubbleCornerRadius: CGFloat = 14,
        assistantBubbleInsets: VVInsets = .init(top: 10, left: 12, bottom: 10, right: 12),
        assistantBubbleMaxWidth: CGFloat = 520,
        assistantBubbleAlignment: VVChatBubbleAlignment = .leading,
        systemBubbleEnabled: Bool = false,
        systemBubbleColor: SIMD4<Float> = .clear,
        systemBubbleBorderColor: SIMD4<Float> = .clear,
        systemBubbleBorderWidth: CGFloat = 0,
        systemBubbleCornerRadius: CGFloat = 12,
        systemBubbleInsets: VVInsets = .init(top: 8, left: 10, bottom: 8, right: 10),
        systemBubbleMaxWidth: CGFloat = 620,
        systemBubbleAlignment: VVChatBubbleAlignment = .leading,
        userHeaderEnabled: Bool = true,
        assistantHeaderEnabled: Bool = true,
        systemHeaderEnabled: Bool = true,
        userHeaderTitle: String = "User",
        assistantHeaderTitle: String = "Agent",
        systemHeaderTitle: String = "System",
        userHeaderIconURL: String? = nil,
        assistantHeaderIconURL: String? = nil,
        systemHeaderIconURL: String? = nil,
        headerIconSize: CGFloat = 14,
        headerIconSpacing: CGFloat = 6,
        userTimestampEnabled: Bool = true,
        assistantTimestampEnabled: Bool = true,
        systemTimestampEnabled: Bool = true,
        userTimestampSuffix: String = "",
        assistantTimestampSuffix: String = "",
        systemTimestampSuffix: String = "",
        bubbleMetadataMinWidth: CGFloat = 88,
        headerSpacing: CGFloat = 6,
        footerSpacing: CGFloat = 6,
        loadingIndicatorText: String = "Typing…",
        timelineInsets: VVInsets = .init(top: 12, left: 0, bottom: 12, right: 0),
        messageSpacing: CGFloat = 10,
        userInsets: VVInsets = .init(top: 6, left: 16, bottom: 6, right: 16),
        assistantInsets: VVInsets = .init(top: 6, left: 16, bottom: 6, right: 16),
        systemInsets: VVInsets = .init(top: 6, left: 16, bottom: 6, right: 16),
        pinThreshold: CGFloat = 24,
        backgroundColor: SIMD4<Float> = .darkBackground,
        renderedCacheLimit: Int = 50,
        cacheBudget: VVChatTimelineCacheBudget? = nil,
        motion: VVChatTimelineMotionStyle = .init(
            layoutTransition: VVTransition(
                insertion: VVTransitionPhase(opacity: 0, scale: 0.985, offset: CGSize(width: 0, height: 18)),
                removal: VVTransitionPhase(opacity: 0)
            ),
            layoutAnimation: .timing(duration: 0.2, easing: .smooth)
        )
    ) {
        func normalizedTheme(_ theme: MarkdownTheme) -> MarkdownTheme {
            var adjusted = theme
            adjusted.contentPadding = 0
            return adjusted
        }

        self.theme = normalizedTheme(theme)
        if let draftTheme {
            self.draftTheme = normalizedTheme(draftTheme)
        } else {
            var adjusted = normalizedTheme(theme)
            adjusted.textColor = theme.textColor.withOpacity(theme.textColor.w * 0.7)
            self.draftTheme = adjusted
        }
        self.baseFont = baseFont
        self.draftFont = draftFont ?? baseFont
        let headerFallbackSize = max(10, baseFont.pointSize - 2)
        let timestampFallbackSize = max(9, baseFont.pointSize - 3)
        self.headerFont = headerFont ?? baseFont.withSize(headerFallbackSize)
        self.timestampFont = timestampFont ?? baseFont.withSize(timestampFallbackSize)
        self.loadingIndicatorFont = loadingIndicatorFont ?? baseFont.withSize(timestampFallbackSize)
        self.headerTextColor = headerTextColor ?? theme.textColor.withOpacity(0.8)
        self.timestampTextColor = timestampTextColor ?? theme.textColor.withOpacity(0.6)
        self.loadingIndicatorTextColor = loadingIndicatorTextColor ?? theme.textColor.withOpacity(0.7)
        self.userBubbleColor = userBubbleColor
        self.userBubbleBorderColor = userBubbleBorderColor
        self.userBubbleBorderWidth = userBubbleBorderWidth
        self.userBubbleCornerRadius = userBubbleCornerRadius
        self.userBubbleInsets = userBubbleInsets
        self.userBubbleMaxWidth = userBubbleMaxWidth
        self.userBubbleAlignment = userBubbleAlignment
        self.assistantBubbleEnabled = assistantBubbleEnabled
        self.assistantBubbleColor = assistantBubbleColor
        self.assistantBubbleBorderColor = assistantBubbleBorderColor
        self.assistantBubbleBorderWidth = assistantBubbleBorderWidth
        self.assistantBubbleCornerRadius = assistantBubbleCornerRadius
        self.assistantBubbleInsets = assistantBubbleInsets
        self.assistantBubbleMaxWidth = assistantBubbleMaxWidth
        self.assistantBubbleAlignment = assistantBubbleAlignment
        self.systemBubbleEnabled = systemBubbleEnabled
        self.systemBubbleColor = systemBubbleColor
        self.systemBubbleBorderColor = systemBubbleBorderColor
        self.systemBubbleBorderWidth = systemBubbleBorderWidth
        self.systemBubbleCornerRadius = systemBubbleCornerRadius
        self.systemBubbleInsets = systemBubbleInsets
        self.systemBubbleMaxWidth = systemBubbleMaxWidth
        self.systemBubbleAlignment = systemBubbleAlignment
        self.userHeaderEnabled = userHeaderEnabled
        self.assistantHeaderEnabled = assistantHeaderEnabled
        self.systemHeaderEnabled = systemHeaderEnabled
        self.userHeaderTitle = userHeaderTitle
        self.assistantHeaderTitle = assistantHeaderTitle
        self.systemHeaderTitle = systemHeaderTitle
        self.userHeaderIconURL = userHeaderIconURL
        self.assistantHeaderIconURL = assistantHeaderIconURL
        self.systemHeaderIconURL = systemHeaderIconURL
        self.headerIconSize = headerIconSize
        self.headerIconSpacing = headerIconSpacing
        self.userTimestampEnabled = userTimestampEnabled
        self.assistantTimestampEnabled = assistantTimestampEnabled
        self.systemTimestampEnabled = systemTimestampEnabled
        self.userTimestampSuffix = userTimestampSuffix
        self.assistantTimestampSuffix = assistantTimestampSuffix
        self.systemTimestampSuffix = systemTimestampSuffix
        self.bubbleMetadataMinWidth = max(1, bubbleMetadataMinWidth)
        self.headerSpacing = headerSpacing
        self.footerSpacing = footerSpacing
        self.loadingIndicatorText = loadingIndicatorText
        self.timelineInsets = timelineInsets
        self.messageSpacing = messageSpacing
        self.userInsets = userInsets
        self.assistantInsets = assistantInsets
        self.systemInsets = systemInsets
        self.pinThreshold = pinThreshold
        self.backgroundColor = backgroundColor
        let resolvedCacheBudget = (cacheBudget ?? VVChatTimelineCacheBudget.compatible(renderedCacheLimit: renderedCacheLimit)).normalized()
        self._cacheBudget = resolvedCacheBudget
        self._renderedCacheLimit = resolvedCacheBudget.renderedMessageCountLimit
        self.motion = motion
    }

    public func insets(for role: VVChatMessageRole) -> VVInsets {
        switch role {
        case .user:
            return userInsets
        case .assistant:
            return assistantInsets
        case .system:
            return systemInsets
        }
    }

    public func bubbleStyle(for role: VVChatMessageRole) -> VVChatBubbleStyle? {
        switch role {
        case .user:
            let bubble = VVChatBubbleStyle(
                isEnabled: true,
                color: userBubbleColor,
                borderColor: userBubbleBorderColor,
                borderWidth: userBubbleBorderWidth,
                cornerRadius: userBubbleCornerRadius,
                insets: userBubbleInsets,
                maxWidth: userBubbleMaxWidth,
                alignment: userBubbleAlignment
            )
            return bubble.isEnabled ? bubble : nil
        case .assistant:
            let bubble = VVChatBubbleStyle(
                isEnabled: assistantBubbleEnabled,
                color: assistantBubbleColor,
                borderColor: assistantBubbleBorderColor,
                borderWidth: assistantBubbleBorderWidth,
                cornerRadius: assistantBubbleCornerRadius,
                insets: assistantBubbleInsets,
                maxWidth: assistantBubbleMaxWidth,
                alignment: assistantBubbleAlignment
            )
            return bubble.isEnabled ? bubble : nil
        case .system:
            let bubble = VVChatBubbleStyle(
                isEnabled: systemBubbleEnabled,
                color: systemBubbleColor,
                borderColor: systemBubbleBorderColor,
                borderWidth: systemBubbleBorderWidth,
                cornerRadius: systemBubbleCornerRadius,
                insets: systemBubbleInsets,
                maxWidth: systemBubbleMaxWidth,
                alignment: systemBubbleAlignment
            )
            return bubble.isEnabled ? bubble : nil
        }
    }

    public func showsHeader(for role: VVChatMessageRole) -> Bool {
        switch role {
        case .user:
            return userHeaderEnabled
        case .assistant:
            return assistantHeaderEnabled
        case .system:
            return systemHeaderEnabled
        }
    }

    public func headerTitle(for role: VVChatMessageRole) -> String {
        switch role {
        case .user:
            return userHeaderTitle
        case .assistant:
            return assistantHeaderTitle
        case .system:
            return systemHeaderTitle
        }
    }

    public func headerIconURL(for role: VVChatMessageRole) -> String? {
        switch role {
        case .user:
            return userHeaderIconURL
        case .assistant:
            return assistantHeaderIconURL
        case .system:
            return systemHeaderIconURL
        }
    }

    public func showsTimestamp(for role: VVChatMessageRole) -> Bool {
        switch role {
        case .user:
            return userTimestampEnabled
        case .assistant:
            return assistantTimestampEnabled
        case .system:
            return systemTimestampEnabled
        }
    }

    public func timestampSuffix(for role: VVChatMessageRole) -> String {
        switch role {
        case .user:
            return userTimestampSuffix
        case .assistant:
            return assistantTimestampSuffix
        case .system:
            return systemTimestampSuffix
        }
    }
}
