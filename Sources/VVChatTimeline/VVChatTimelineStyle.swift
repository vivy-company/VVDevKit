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
    case trailing
}

public struct VVChatBubbleStyle: Sendable {
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
    public var userTimestampEnabled: Bool
    public var assistantTimestampEnabled: Bool
    public var systemTimestampEnabled: Bool
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
    public var renderedCacheLimit: Int

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
        userTimestampEnabled: Bool = true,
        assistantTimestampEnabled: Bool = true,
        systemTimestampEnabled: Bool = true,
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
        renderedCacheLimit: Int = 50
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
        self.userTimestampEnabled = userTimestampEnabled
        self.assistantTimestampEnabled = assistantTimestampEnabled
        self.systemTimestampEnabled = systemTimestampEnabled
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
        self.renderedCacheLimit = renderedCacheLimit
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
}
