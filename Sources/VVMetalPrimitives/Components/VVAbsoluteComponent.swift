import CoreGraphics

public struct VVAbsoluteComponent: VVComponent {
    public var frame: CGRect
    public var child: VVNode
    public var clipRect: CGRect?

    public init(frame: CGRect, child: VVNode, clipRect: CGRect? = nil) {
        self.frame = frame
        self.child = child
        self.clipRect = clipRect
    }

    public func measure(in env: VVLayoutEnvironment, width: CGFloat) -> VVComponentLayout {
        let node = VVNode(offset: frame.origin, clipRect: clipRect, children: [child])
        return VVComponentLayout(size: frame.size, node: node)
    }
}
