import CoreGraphics

public struct VVFrameComponent: VVComponent {
    public var frame: CGRect
    public var child: VVComponent
    public var clipRect: CGRect?

    public init(frame: CGRect, child: VVComponent, clipRect: CGRect? = nil) {
        self.frame = frame
        self.child = child
        self.clipRect = clipRect
    }

    public func measure(in env: VVLayoutEnvironment, width: CGFloat) -> VVComponentLayout {
        let childLayout = child.measure(in: env, width: frame.width)
        let node = VVNode(offset: frame.origin, clipRect: clipRect, children: [childLayout.node])
        return VVComponentLayout(size: frame.size, node: node)
    }
}

