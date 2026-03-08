import CoreGraphics

// MARK: - Layout Constraint

public struct VVLayoutConstraint: Sendable {
    public var minWidth: CGFloat
    public var idealWidth: CGFloat?
    public var maxWidth: CGFloat
    public var minHeight: CGFloat
    public var idealHeight: CGFloat?
    public var maxHeight: CGFloat

    public init(
        minWidth: CGFloat = 0,
        idealWidth: CGFloat? = nil,
        maxWidth: CGFloat,
        minHeight: CGFloat = 0,
        idealHeight: CGFloat? = nil,
        maxHeight: CGFloat = .greatestFiniteMagnitude
    ) {
        self.minWidth = minWidth
        self.idealWidth = idealWidth
        self.maxWidth = maxWidth
        self.minHeight = minHeight
        self.idealHeight = idealHeight
        self.maxHeight = maxHeight
    }

    public var proposedWidth: CGFloat {
        if let idealWidth {
            return min(max(idealWidth, minWidth), maxWidth)
        }
        return maxWidth
    }

    public var proposedHeight: CGFloat {
        if let idealHeight {
            return min(max(idealHeight, minHeight), maxHeight)
        }
        return maxHeight
    }

    public var hasBoundedWidth: Bool {
        maxWidth.isFinite
    }

    public var hasBoundedHeight: Bool {
        maxHeight.isFinite
    }

    public func insetBy(dx: CGFloat, dy: CGFloat) -> VVLayoutConstraint {
        VVLayoutConstraint(
            minWidth: max(0, minWidth - dx),
            idealWidth: idealWidth.map { max(0, $0 - dx) },
            maxWidth: max(0, maxWidth - dx),
            minHeight: max(0, minHeight - dy),
            idealHeight: idealHeight.map { max(0, $0 - dy) },
            maxHeight: max(0, maxHeight - dy)
        )
    }

    public func clamped(size: CGSize) -> CGSize {
        CGSize(
            width: min(max(size.width, minWidth), maxWidth),
            height: min(max(size.height, minHeight), maxHeight)
        )
    }
}

// MARK: - View Layout Result

public struct VVViewLayout: Sendable {
    public var size: CGSize
    public var node: VVNode

    public init(size: CGSize, node: VVNode) {
        self.size = size
        var resolvedNode = node
        if resolvedNode.layoutSize == nil {
            resolvedNode.layoutSize = size
        }
        self.node = resolvedNode
    }

    public static let empty = VVViewLayout(size: .zero, node: VVNode())

    public func animationSnapshots() -> [String: VVLayoutAnimationSnapshot] {
        node.animationSnapshots()
    }
}

// MARK: - Frame Alignment

public enum VVFrameAlignment: Sendable {
    case topLeading
    case top
    case topTrailing
    case leading
    case center
    case trailing
    case bottomLeading
    case bottom
    case bottomTrailing

    func xOffset(containerWidth: CGFloat, childWidth: CGFloat) -> CGFloat {
        switch self {
        case .topLeading, .leading, .bottomLeading:
            return 0
        case .top, .center, .bottom:
            return max(0, (containerWidth - childWidth) * 0.5)
        case .topTrailing, .trailing, .bottomTrailing:
            return max(0, containerWidth - childWidth)
        }
    }

    func yOffset(containerHeight: CGFloat, childHeight: CGFloat) -> CGFloat {
        switch self {
        case .topLeading, .top, .topTrailing:
            return 0
        case .leading, .center, .trailing:
            return max(0, (containerHeight - childHeight) * 0.5)
        case .bottomLeading, .bottom, .bottomTrailing:
            return max(0, containerHeight - childHeight)
        }
    }
}

// MARK: - VVView Protocol

public protocol VVView: Sendable {
    func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout
}
