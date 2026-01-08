import CoreGraphics

public struct VVStackComponent: VVComponent {
    public enum Alignment: Sendable {
        case leading
        case center
        case trailing
    }

    public var spacing: CGFloat
    public var alignment: Alignment
    public var children: [VVComponent]

    public init(spacing: CGFloat = 0, alignment: Alignment = .leading, children: [VVComponent]) {
        self.spacing = spacing
        self.alignment = alignment
        self.children = children
    }

    public func measure(in env: VVLayoutEnvironment, width: CGFloat) -> VVComponentLayout {
        var y: CGFloat = 0
        var maxWidth: CGFloat = 0
        var nodes: [VVNode] = []

        for (index, child) in children.enumerated() {
            let layout = child.measure(in: env, width: width)
            let childX: CGFloat
            switch alignment {
            case .leading:
                childX = 0
            case .center:
                childX = max(0, (width - layout.size.width) * 0.5)
            case .trailing:
                childX = max(0, width - layout.size.width)
            }
            let node = VVNode(offset: CGPoint(x: childX, y: y), children: [layout.node])
            nodes.append(node)
            y += layout.size.height
            if index != children.count - 1 {
                y += spacing
            }
            maxWidth = max(maxWidth, layout.size.width)
        }

        let finalSize = CGSize(width: max(width, maxWidth), height: y)
        let root = VVNode(children: nodes)
        return VVComponentLayout(size: finalSize, node: root)
    }
}

