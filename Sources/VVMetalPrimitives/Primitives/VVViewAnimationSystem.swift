import CoreGraphics
import QuartzCore

public struct VVSpring: Hashable, Sendable {
    public var response: Double
    public var dampingFraction: Double

    public init(response: Double = 0.32, dampingFraction: Double = 0.82) {
        self.response = response
        self.dampingFraction = dampingFraction
    }
}

public enum VVAnimationDescriptor: Hashable, Sendable {
    case timing(duration: Double, easing: VVEasing)
    case spring(VVSpring)

    public static func linear(duration: Double = 0.16) -> Self {
        .timing(duration: duration, easing: .linear)
    }

    public static func smooth(duration: Double = 0.24) -> Self {
        .timing(duration: duration, easing: .smooth)
    }

    public static func snappy(duration: Double = 0.24) -> Self {
        .timing(duration: duration, easing: .snappy)
    }

    public static func bouncy(duration: Double = 0.32) -> Self {
        .timing(duration: duration, easing: .bouncy)
    }

    public static func spring(response: Double = 0.32, dampingFraction: Double = 0.82) -> Self {
        .spring(VVSpring(response: response, dampingFraction: dampingFraction))
    }

    public var duration: Double {
        switch self {
        case .timing(let duration, _):
            return duration
        case .spring(let spring):
            return max(0.18, spring.response * 1.5)
        }
    }

    public var easing: VVEasing {
        switch self {
        case .timing(_, let easing):
            return easing
        case .spring(let spring):
            return spring.dampingFraction >= 0.85 ? .smooth : .bouncy
        }
    }
}

public struct VVTransitionPhase: Hashable, Sendable {
    public var opacity: Float
    public var scale: CGFloat
    public var offset: CGSize

    public init(opacity: Float = 1, scale: CGFloat = 1, offset: CGSize = .zero) {
        self.opacity = opacity
        self.scale = scale
        self.offset = offset
    }

    public static let identity = VVTransitionPhase()
}

public enum VVTransitionEdge: Hashable, Sendable {
    case top
    case bottom
    case leading
    case trailing

    var unitOffset: CGSize {
        switch self {
        case .top:
            return CGSize(width: 0, height: -1)
        case .bottom:
            return CGSize(width: 0, height: 1)
        case .leading:
            return CGSize(width: -1, height: 0)
        case .trailing:
            return CGSize(width: 1, height: 0)
        }
    }
}

public struct VVTransition: Hashable, Sendable {
    public var insertion: VVTransitionPhase
    public var removal: VVTransitionPhase

    public init(insertion: VVTransitionPhase = .identity, removal: VVTransitionPhase = .identity) {
        self.insertion = insertion
        self.removal = removal
    }

    public static let identity = VVTransition()
    public static let opacity = VVTransition(
        insertion: VVTransitionPhase(opacity: 0),
        removal: VVTransitionPhase(opacity: 0)
    )
    public static let scale = VVTransition(
        insertion: VVTransitionPhase(opacity: 0, scale: 0.92),
        removal: VVTransitionPhase(opacity: 0, scale: 0.92)
    )
    public static let accordion = VVTransition(
        insertion: VVTransitionPhase(opacity: 0, scale: 0.98, offset: CGSize(width: 0, height: -18)),
        removal: VVTransitionPhase(opacity: 0, scale: 0.98, offset: CGSize(width: 0, height: -12))
    )
    public static let morph = VVTransition(
        insertion: VVTransitionPhase(opacity: 0.6, scale: 0.94),
        removal: VVTransitionPhase(opacity: 0.6, scale: 1.04)
    )

    public static func move(edge: VVTransitionEdge, distance: CGFloat = 20) -> VVTransition {
        let delta = edge.unitOffset
        let offset = CGSize(width: delta.width * distance, height: delta.height * distance)
        return VVTransition(
            insertion: VVTransitionPhase(opacity: 0, offset: offset),
            removal: VVTransitionPhase(opacity: 0, offset: offset)
        )
    }
}

public struct VVLayoutAnimationSnapshot: Hashable, Sendable {
    public var id: String
    public var frame: CGRect
    public var contentOffset: CGPoint
    public var opacity: Float
    public var scale: CGFloat
    public var transition: VVTransition?
    public var animation: VVAnimationDescriptor?

    public init(
        id: String,
        frame: CGRect,
        contentOffset: CGPoint = .zero,
        opacity: Float = 1,
        scale: CGFloat = 1,
        transition: VVTransition? = nil,
        animation: VVAnimationDescriptor? = nil
    ) {
        self.id = id
        self.frame = frame
        self.contentOffset = contentOffset
        self.opacity = opacity
        self.scale = scale
        self.transition = transition
        self.animation = animation
    }
}

public struct VVAnimatedLayoutState: Sendable {
    public var snapshots: [String: VVLayoutAnimationSnapshot]
    public var progress: CGFloat
    public var isComplete: Bool

    public init(snapshots: [String: VVLayoutAnimationSnapshot], progress: CGFloat, isComplete: Bool) {
        self.snapshots = snapshots
        self.progress = progress
        self.isComplete = isComplete
    }
}

public struct VVLayoutTransitionAnimator: Sendable {
    private var fromSnapshots: [String: VVLayoutAnimationSnapshot] = [:]
    private var toSnapshots: [String: VVLayoutAnimationSnapshot] = [:]
    private var animation: VVAnimationDescriptor = .snappy()
    private var startTime: CFTimeInterval = 0
    private var duration: CFTimeInterval = 0

    public init() {}

    public var isRunning: Bool {
        duration > 0 && !toSnapshots.isEmpty
    }

    public mutating func start(
        from: [String: VVLayoutAnimationSnapshot],
        to: [String: VVLayoutAnimationSnapshot],
        fallbackTransition: VVTransition = .accordion,
        fallbackAnimation: VVAnimationDescriptor = .snappy(),
        startTime: CFTimeInterval = CACurrentMediaTime()
    ) {
        guard !to.isEmpty else {
            complete(with: to)
            return
        }

        fromSnapshots.removeAll(keepingCapacity: true)
        toSnapshots = to
        animation = resolvedAnimation(from: from, to: to, fallback: fallbackAnimation)
        duration = animation.duration
        self.startTime = startTime

        for (id, target) in to {
            if let previous = from[id] {
                fromSnapshots[id] = previous
                continue
            }

            let transition = target.transition ?? fallbackTransition
            let initialFrame = target.frame.offsetBy(dx: transition.insertion.offset.width, dy: transition.insertion.offset.height)
            fromSnapshots[id] = VVLayoutAnimationSnapshot(
                id: id,
                frame: initialFrame,
                contentOffset: target.contentOffset,
                opacity: transition.insertion.opacity,
                scale: transition.insertion.scale,
                transition: target.transition,
                animation: target.animation
            )
        }

        for (id, previous) in from where to[id] == nil {
            let transition = previous.transition ?? fallbackTransition
            let finalFrame = previous.frame.offsetBy(dx: transition.removal.offset.width, dy: transition.removal.offset.height)
            toSnapshots[id] = VVLayoutAnimationSnapshot(
                id: id,
                frame: finalFrame,
                contentOffset: previous.contentOffset,
                opacity: transition.removal.opacity,
                scale: transition.removal.scale,
                transition: previous.transition,
                animation: previous.animation
            )
            fromSnapshots[id] = previous
        }
    }

    public mutating func complete(with snapshots: [String: VVLayoutAnimationSnapshot]) {
        fromSnapshots.removeAll(keepingCapacity: false)
        toSnapshots = snapshots
        duration = 0
        startTime = 0
    }

    public func state(at now: CFTimeInterval = CACurrentMediaTime()) -> VVAnimatedLayoutState {
        guard isRunning else {
            return VVAnimatedLayoutState(snapshots: toSnapshots, progress: 1, isComplete: true)
        }

        let rawProgress = min(1.0, max(0.0, (now - startTime) / duration))
        let easedProgress = animation.easing.value(at: CGFloat(rawProgress))

        var interpolated: [String: VVLayoutAnimationSnapshot] = [:]
        interpolated.reserveCapacity(toSnapshots.count)

        for (id, target) in toSnapshots {
            let start = fromSnapshots[id] ?? target
            interpolated[id] = VVLayoutAnimationSnapshot(
                id: id,
                frame: CGRect(
                    x: start.frame.origin.x + (target.frame.origin.x - start.frame.origin.x) * easedProgress,
                    y: start.frame.origin.y + (target.frame.origin.y - start.frame.origin.y) * easedProgress,
                    width: start.frame.width + (target.frame.width - start.frame.width) * easedProgress,
                    height: start.frame.height + (target.frame.height - start.frame.height) * easedProgress
                ),
                contentOffset: CGPoint(
                    x: start.contentOffset.x + (target.contentOffset.x - start.contentOffset.x) * easedProgress,
                    y: start.contentOffset.y + (target.contentOffset.y - start.contentOffset.y) * easedProgress
                ),
                opacity: start.opacity + (target.opacity - start.opacity) * Float(easedProgress),
                scale: start.scale + (target.scale - start.scale) * easedProgress,
                transition: target.transition,
                animation: target.animation
            )
        }

        return VVAnimatedLayoutState(
            snapshots: interpolated,
            progress: CGFloat(rawProgress),
            isComplete: rawProgress >= 1
        )
    }

    private func resolvedAnimation(
        from: [String: VVLayoutAnimationSnapshot],
        to: [String: VVLayoutAnimationSnapshot],
        fallback: VVAnimationDescriptor
    ) -> VVAnimationDescriptor {
        for snapshot in to.values {
            if let animation = snapshot.animation {
                return animation
            }
        }
        for snapshot in from.values {
            if let animation = snapshot.animation {
                return animation
            }
        }
        return fallback
    }
}
