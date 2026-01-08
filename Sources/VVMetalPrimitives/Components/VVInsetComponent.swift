import CoreGraphics

public struct VVInsetComponent: VVComponent {
    public var insets: VVInsets
    public var child: VVComponent

    public init(insets: VVInsets, child: VVComponent) {
        self.insets = insets
        self.child = child
    }

    public func measure(in env: VVLayoutEnvironment, width: CGFloat) -> VVComponentLayout {
        let availableWidth = max(0, width - insets.left - insets.right)
        let layout = child.measure(in: env, width: availableWidth)
        let size = CGSize(
            width: layout.size.width + insets.left + insets.right,
            height: layout.size.height + insets.top + insets.bottom
        )
        let node = VVNode(
            offset: CGPoint(x: insets.left, y: insets.top),
            children: [layout.node]
        )
        return VVComponentLayout(size: size, node: node)
    }
}
