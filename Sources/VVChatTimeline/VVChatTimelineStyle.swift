import Foundation
import VVMarkdown
import VVMetalPrimitives

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

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
    public var userBubbleCornerRadius: CGFloat
    public var userBubbleInsets: VVInsets
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
        userBubbleColor: SIMD4<Float> = SIMD4(0.18, 0.2, 0.24, 1),
        userBubbleCornerRadius: CGFloat = 14,
        userBubbleInsets: VVInsets = .init(top: 10, left: 12, bottom: 10, right: 12),
        headerSpacing: CGFloat = 6,
        footerSpacing: CGFloat = 6,
        loadingIndicatorText: String = "Typing…",
        timelineInsets: VVInsets = .init(top: 12, left: 0, bottom: 12, right: 0),
        messageSpacing: CGFloat = 10,
        userInsets: VVInsets = .init(top: 6, left: 16, bottom: 6, right: 16),
        assistantInsets: VVInsets = .init(top: 6, left: 16, bottom: 6, right: 16),
        systemInsets: VVInsets = .init(top: 6, left: 16, bottom: 6, right: 16),
        pinThreshold: CGFloat = 24,
        backgroundColor: SIMD4<Float> = SIMD4(0.08, 0.09, 0.1, 1),
        renderedCacheLimit: Int = 200
    ) {
        self.theme = theme
        if let draftTheme {
            self.draftTheme = draftTheme
        } else {
            var adjusted = theme
            adjusted.textColor = SIMD4(theme.textColor.x, theme.textColor.y, theme.textColor.z, theme.textColor.w * 0.7)
            self.draftTheme = adjusted
        }
        self.baseFont = baseFont
        self.draftFont = draftFont ?? baseFont
        let headerFallbackSize = max(10, baseFont.pointSize - 2)
        let timestampFallbackSize = max(9, baseFont.pointSize - 3)
        self.headerFont = headerFont ?? baseFont.withSize(headerFallbackSize)
        self.timestampFont = timestampFont ?? baseFont.withSize(timestampFallbackSize)
        self.loadingIndicatorFont = loadingIndicatorFont ?? baseFont.withSize(timestampFallbackSize)
        self.headerTextColor = headerTextColor ?? SIMD4(theme.textColor.x, theme.textColor.y, theme.textColor.z, 0.8)
        self.timestampTextColor = timestampTextColor ?? SIMD4(theme.textColor.x, theme.textColor.y, theme.textColor.z, 0.6)
        self.loadingIndicatorTextColor = loadingIndicatorTextColor ?? SIMD4(theme.textColor.x, theme.textColor.y, theme.textColor.z, 0.7)
        self.userBubbleColor = userBubbleColor
        self.userBubbleCornerRadius = userBubbleCornerRadius
        self.userBubbleInsets = userBubbleInsets
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
}
