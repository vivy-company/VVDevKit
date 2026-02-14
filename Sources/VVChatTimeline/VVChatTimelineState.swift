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
        let distance = max(0, distanceFromBottom)
        // Hysteresis:
        // - unpin quickly once user moves away from bottom
        // - repin only when truly close to bottom
        let detachThreshold = min(pinThreshold, max(2, pinThreshold * 0.25))
        if isPinnedToBottom {
            isPinnedToBottom = distance <= detachThreshold
        } else {
            isPinnedToBottom = distance <= pinThreshold
        }
    }
}
