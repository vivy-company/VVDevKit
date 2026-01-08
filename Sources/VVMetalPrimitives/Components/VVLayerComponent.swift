import CoreGraphics

public struct VVLayerComponent: VVComponent {
    public var children: [VVComponent]

    public init(children: [VVComponent]) {
        self.children = children
    }

    public func measure(in env: VVLayoutEnvironment, width: CGFloat) -> VVComponentLayout {
        var maxWidth: CGFloat = 0
        var maxHeight: CGFloat = 0
        var nodes: [VVNode] = []

        for child in children {
            let layout = child.measure(in: env, width: width)
            maxWidth = max(maxWidth, layout.size.width)
            maxHeight = max(maxHeight, layout.size.height)
            nodes.append(layout.node)
        }

        let size = CGSize(width: maxWidth, height: maxHeight)
        let root = VVNode(children: nodes)
        return VVComponentLayout(size: size, node: root)
    }
}

