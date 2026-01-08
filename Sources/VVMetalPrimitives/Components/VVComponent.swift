import CoreGraphics

public struct VVLayoutEnvironment: Sendable {
    public var scale: CGFloat
    public var defaultTextColor: SIMD4<Float>
    public var defaultCornerRadius: CGFloat

    public init(
        scale: CGFloat = 1,
        defaultTextColor: SIMD4<Float> = SIMD4(1, 1, 1, 1),
        defaultCornerRadius: CGFloat = 6
    ) {
        self.scale = scale
        self.defaultTextColor = defaultTextColor
        self.defaultCornerRadius = defaultCornerRadius
    }
}

public struct VVInsets: Hashable, Sendable {
    public var top: CGFloat
    public var left: CGFloat
    public var bottom: CGFloat
    public var right: CGFloat

    public init(top: CGFloat = 0, left: CGFloat = 0, bottom: CGFloat = 0, right: CGFloat = 0) {
        self.top = top
        self.left = left
        self.bottom = bottom
        self.right = right
    }
}

public struct VVComponentLayout: Sendable {
    public var size: CGSize
    public var node: VVNode

    public init(size: CGSize, node: VVNode) {
        self.size = size
        self.node = node
    }
}

public protocol VVComponent: Sendable {
    func measure(in env: VVLayoutEnvironment, width: CGFloat) -> VVComponentLayout
}
