import CoreGraphics

// MARK: - Alignment

public enum VVAlignment: Sendable {
    case leading
    case center
    case trailing
}

public enum VVVerticalAlignment: Sendable {
    case top
    case center
    case bottom
}

// MARK: - VVStack

public struct VVStack: VVView {
    public var spacing: CGFloat
    public var alignment: VVAlignment
    public var children: [any VVView]

    public init(spacing: CGFloat = 0, alignment: VVAlignment = .leading, @VVViewBuilder content: () -> [any VVView]) {
        self.spacing = spacing
        self.alignment = alignment
        self.children = content()
    }

    public init(spacing: CGFloat = 0, alignment: VVAlignment = .leading, children: [any VVView]) {
        self.spacing = spacing
        self.alignment = alignment
        self.children = children
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        guard !children.isEmpty else { return .empty }

        var y: CGFloat = 0
        var maxWidth: CGFloat = 0
        var childLayouts: [(layout: VVViewLayout, y: CGFloat)] = []

        for (index, child) in children.enumerated() {
            let childLayout = child.layout(in: env, constraint: constraint)
            childLayouts.append((childLayout, y))
            y += childLayout.size.height
            if index < children.count - 1 {
                y += spacing
            }
            maxWidth = max(maxWidth, childLayout.size.width)
        }

        let containerWidth = min(constraint.maxWidth, max(maxWidth, constraint.maxWidth))
        var nodes: [VVNode] = []

        for (childLayout, childY) in childLayouts {
            let childX: CGFloat
            switch alignment {
            case .leading:
                childX = 0
            case .center:
                childX = max(0, (containerWidth - childLayout.size.width) * 0.5)
            case .trailing:
                childX = max(0, containerWidth - childLayout.size.width)
            }
            nodes.append(VVNode(offset: CGPoint(x: childX, y: childY), children: [childLayout.node]))
        }

        return VVViewLayout(
            size: CGSize(width: containerWidth, height: y),
            node: VVNode(children: nodes)
        )
    }
}

// MARK: - VVHStack

public struct VVHStack: VVView {
    public var spacing: CGFloat
    public var alignment: VVVerticalAlignment
    public var children: [any VVView]

    public init(spacing: CGFloat = 0, alignment: VVVerticalAlignment = .top, @VVViewBuilder content: () -> [any VVView]) {
        self.spacing = spacing
        self.alignment = alignment
        self.children = content()
    }

    public init(spacing: CGFloat = 0, alignment: VVVerticalAlignment = .top, children: [any VVView]) {
        self.spacing = spacing
        self.alignment = alignment
        self.children = children
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        guard !children.isEmpty else { return .empty }

        let totalSpacing = spacing * CGFloat(max(0, children.count - 1))
        let availableWidth = max(0, constraint.maxWidth - totalSpacing)
        let childWidth = availableWidth / CGFloat(children.count)

        var x: CGFloat = 0
        var maxHeight: CGFloat = 0
        var childLayouts: [(layout: VVViewLayout, x: CGFloat)] = []

        for (index, child) in children.enumerated() {
            let childConstraint = VVLayoutConstraint(maxWidth: childWidth, maxHeight: constraint.maxHeight)
            let childLayout = child.layout(in: env, constraint: childConstraint)
            childLayouts.append((childLayout, x))
            x += childLayout.size.width
            if index < children.count - 1 {
                x += spacing
            }
            maxHeight = max(maxHeight, childLayout.size.height)
        }

        var nodes: [VVNode] = []
        for (childLayout, childX) in childLayouts {
            let childY: CGFloat
            switch alignment {
            case .top:
                childY = 0
            case .center:
                childY = max(0, (maxHeight - childLayout.size.height) * 0.5)
            case .bottom:
                childY = max(0, maxHeight - childLayout.size.height)
            }
            nodes.append(VVNode(offset: CGPoint(x: childX, y: childY), children: [childLayout.node]))
        }

        return VVViewLayout(
            size: CGSize(width: x, height: maxHeight),
            node: VVNode(children: nodes)
        )
    }
}

// MARK: - VVZStack

public struct VVZStack: VVView {
    public var children: [any VVView]

    public init(@VVViewBuilder content: () -> [any VVView]) {
        self.children = content()
    }

    public init(children: [any VVView]) {
        self.children = children
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        guard !children.isEmpty else { return .empty }

        var maxWidth: CGFloat = 0
        var maxHeight: CGFloat = 0
        var childLayouts: [VVViewLayout] = []

        for child in children {
            let childLayout = child.layout(in: env, constraint: constraint)
            childLayouts.append(childLayout)
            maxWidth = max(maxWidth, childLayout.size.width)
            maxHeight = max(maxHeight, childLayout.size.height)
        }

        var nodes: [VVNode] = []
        for (index, childLayout) in childLayouts.enumerated() {
            var node = childLayout.node
            node.zIndex = index
            nodes.append(node)
        }

        return VVViewLayout(
            size: CGSize(width: maxWidth, height: maxHeight),
            node: VVNode(children: nodes)
        )
    }
}
