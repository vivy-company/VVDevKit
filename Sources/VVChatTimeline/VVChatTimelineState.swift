import Foundation

public struct VVChatTimelineState: Equatable {
    public var isPinnedToBottom: Bool
    public var userIsInteracting: Bool
    public var hasUnreadNewContent: Bool
    public var pinThreshold: CGFloat

    public init(
        isPinnedToBottom: Bool = true,
        userIsInteracting: Bool = false,
        hasUnreadNewContent: Bool = false,
        pinThreshold: CGFloat = 24
    ) {
        self.isPinnedToBottom = isPinnedToBottom
        self.userIsInteracting = userIsInteracting
        self.hasUnreadNewContent = hasUnreadNewContent
        self.pinThreshold = pinThreshold
    }

    public var shouldAutoFollow: Bool {
        isPinnedToBottom && !userIsInteracting
    }

    public mutating func updatePinnedState(distanceFromBottom: CGFloat) {
        isPinnedToBottom = distanceFromBottom <= pinThreshold
    }
}
