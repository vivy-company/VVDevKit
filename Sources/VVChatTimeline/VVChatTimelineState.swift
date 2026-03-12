import Foundation

public enum VVChatTimelineViewportMode: Equatable, Sendable {
    case liveTail
    case detached
}

public struct VVChatTimelineState: Equatable {
    public var viewportMode: VVChatTimelineViewportMode
    public var userIsInteracting: Bool
    public var hasUnreadNewContent: Bool
    public var pinThreshold: CGFloat

    public var isLiveTail: Bool {
        viewportMode == .liveTail
    }

    public init(
        viewportMode: VVChatTimelineViewportMode = .liveTail,
        userIsInteracting: Bool = false,
        hasUnreadNewContent: Bool = false,
        pinThreshold: CGFloat = 24
    ) {
        self.viewportMode = viewportMode
        self.userIsInteracting = userIsInteracting
        self.hasUnreadNewContent = hasUnreadNewContent
        self.pinThreshold = pinThreshold
    }

    public var shouldAutoFollow: Bool {
        isLiveTail && !userIsInteracting
    }

    public mutating func updateViewportMode(distanceFromBottom: CGFloat) {
        let distance = max(0, distanceFromBottom)
        // Hysteresis:
        // - unpin quickly once user moves away from bottom
        // - repin only when truly close to bottom
        let detachThreshold = min(pinThreshold, max(2, pinThreshold * 0.25))
        if isLiveTail {
            if distance > detachThreshold {
                viewportMode = .detached
            }
        } else {
            if distance <= pinThreshold {
                viewportMode = .liveTail
            }
        }

        if isLiveTail {
            hasUnreadNewContent = false
        }
    }
}
