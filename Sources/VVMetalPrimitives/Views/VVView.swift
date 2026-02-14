import CoreGraphics

// MARK: - Layout Constraint

public struct VVLayoutConstraint: Sendable {
    public var maxWidth: CGFloat
    public var maxHeight: CGFloat

    public init(maxWidth: CGFloat, maxHeight: CGFloat = .greatestFiniteMagnitude) {
        self.maxWidth = maxWidth
        self.maxHeight = maxHeight
    }
}

// MARK: - View Layout Result

public struct VVViewLayout: Sendable {
    public var size: CGSize
    public var node: VVNode

    public init(size: CGSize, node: VVNode) {
        self.size = size
        self.node = node
    }

    public static let empty = VVViewLayout(size: .zero, node: VVNode())
}

// MARK: - VVView Protocol

public protocol VVView: Sendable {
    func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout
}
