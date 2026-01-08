import CoreGraphics

public struct VVPrimitiveComponent: VVComponent {
    public var primitives: [VVPrimitiveKind]
    public var size: CGSize
    public var clipRect: CGRect?

    public init(primitives: [VVPrimitiveKind], size: CGSize = .zero, clipRect: CGRect? = nil) {
        self.primitives = primitives
        self.size = size
        self.clipRect = clipRect
        self.node = nil
    }

    public init(node: VVNode, size: CGSize = .zero) {
        self.primitives = []
        self.size = size
        self.clipRect = nil
        self.node = node
    }

    private var node: VVNode?

    public func measure(in env: VVLayoutEnvironment, width: CGFloat) -> VVComponentLayout {
        if let node = node {
            return VVComponentLayout(size: size, node: node)
        }
        let node = VVNode(clipRect: clipRect, primitives: primitives)
        return VVComponentLayout(size: size, node: node)
    }
}
