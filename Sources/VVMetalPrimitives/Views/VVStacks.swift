import CoreGraphics

private enum VVHorizontalSizingBehavior {
    case fixed
    case compressible
    case spacer(minLength: CGFloat)
}

private func vvHorizontalSizingBehavior(for child: any VVView) -> VVHorizontalSizingBehavior {
    switch child {
    case let spacer as VSpacer:
        return .spacer(minLength: max(spacer.width, spacer.minLength))
    case is VVImage, is VVNodeView, is VVPositionedFrame:
        return .fixed
    case let rect as VRect:
        return rect.width == nil ? .compressible : .fixed
    case is VText, is VVTextBlockView, is VVStack, is VVHStack, is VVZStack, is VVGroup:
        return .compressible
    case let modifier as VVFrameModifier:
        return modifier.width == nil ? vvHorizontalSizingBehavior(for: modifier.child) : .fixed
    case let modifier as VVPaddingModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVBackgroundModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVBorderModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVShadowModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVOpacityModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVClipModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVZIndexModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVOffsetModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVTransformModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVIdentityModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVTransitionModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVAnimationModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    default:
        return .compressible
    }
}

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

        let containerWidth = max(maxWidth, constraint.minWidth)
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
            size: constraint.clamped(size: CGSize(width: containerWidth, height: y)),
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
        let availableWidth = constraint.hasBoundedWidth
            ? max(0, constraint.maxWidth - totalSpacing)
            : .greatestFiniteMagnitude
        let behaviors = children.map(vvHorizontalSizingBehavior)

        var naturalLayouts: [Int: VVViewLayout] = [:]
        var naturalWidths: [Int: CGFloat] = [:]
        var fixedWidth: CGFloat = 0
        var compressibleWidth: CGFloat = 0
        var spacerMinWidth: CGFloat = 0
        var maxHeight: CGFloat = 0

        for (index, child) in children.enumerated() {
            switch behaviors[index] {
            case .spacer(let minLength):
                spacerMinWidth += minLength
                maxHeight = max(maxHeight, minLength > 0 ? minLength : 0)
            case .fixed, .compressible:
                let naturalConstraint = VVLayoutConstraint(
                    minWidth: 0,
                    idealWidth: nil,
                    maxWidth: .greatestFiniteMagnitude,
                    minHeight: constraint.minHeight,
                    idealHeight: constraint.idealHeight,
                    maxHeight: constraint.maxHeight
                )
                let naturalLayout = child.layout(in: env, constraint: naturalConstraint)
                naturalLayouts[index] = naturalLayout
                naturalWidths[index] = naturalLayout.size.width
                switch behaviors[index] {
                case .fixed:
                    fixedWidth += naturalLayout.size.width
                case .compressible:
                    compressibleWidth += naturalLayout.size.width
                case .spacer:
                    break
                }
                maxHeight = max(maxHeight, naturalLayout.size.height)
            }
        }

        let boundedContentWidth = constraint.hasBoundedWidth
            ? max(0, availableWidth - spacerMinWidth)
            : availableWidth
        let compressibleBudget = constraint.hasBoundedWidth
            ? max(0, boundedContentWidth - fixedWidth)
            : compressibleWidth
        let compressionRatio: CGFloat = {
            guard constraint.hasBoundedWidth, compressibleWidth > compressibleBudget, compressibleWidth > 0 else { return 1 }
            return max(0, compressibleBudget / compressibleWidth)
        }()

        var resolvedLayouts: [Int: VVViewLayout] = [:]
        var consumedNonSpacerWidth: CGFloat = 0

        for (index, child) in children.enumerated() {
            switch behaviors[index] {
            case .spacer:
                continue
            case .fixed:
                if let naturalLayout = naturalLayouts[index] {
                    resolvedLayouts[index] = naturalLayout
                    consumedNonSpacerWidth += naturalLayout.size.width
                    maxHeight = max(maxHeight, naturalLayout.size.height)
                }
            case .compressible:
                let naturalWidth = naturalWidths[index] ?? 0
                let targetWidth = constraint.hasBoundedWidth ? max(0, naturalWidth * compressionRatio) : naturalWidth
                let childConstraint = VVLayoutConstraint(
                    minWidth: 0,
                    idealWidth: targetWidth,
                    maxWidth: max(0, targetWidth),
                    minHeight: constraint.minHeight,
                    idealHeight: constraint.idealHeight,
                    maxHeight: constraint.maxHeight
                )
                let childLayout = child.layout(in: env, constraint: childConstraint)
                resolvedLayouts[index] = childLayout
                consumedNonSpacerWidth += childLayout.size.width
                maxHeight = max(maxHeight, childLayout.size.height)
            }
        }

        let spacerIndexes = children.indices.filter {
            if case .spacer = behaviors[$0] { return true }
            return false
        }
        let remainingWidth = constraint.hasBoundedWidth
            ? max(0, availableWidth - consumedNonSpacerWidth)
            : spacerMinWidth
        let extraSpacerWidth = spacerIndexes.isEmpty ? 0 : remainingWidth / CGFloat(spacerIndexes.count)

        var x: CGFloat = 0
        var childLayouts: [(layout: VVViewLayout, x: CGFloat)] = []

        for index in children.indices {
            let childLayout: VVViewLayout
            switch behaviors[index] {
            case .spacer(let minLength):
                let spacerWidth = constraint.hasBoundedWidth ? max(minLength, extraSpacerWidth) : minLength
                let spacerLayout = children[index].layout(
                    in: env,
                    constraint: VVLayoutConstraint(
                        minWidth: spacerWidth,
                        idealWidth: spacerWidth,
                        maxWidth: spacerWidth,
                        minHeight: 0,
                        idealHeight: nil,
                        maxHeight: constraint.maxHeight
                    )
                )
                childLayout = spacerLayout
            case .fixed, .compressible:
                childLayout = resolvedLayouts[index] ?? naturalLayouts[index] ?? .empty
            }
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
            size: constraint.clamped(size: CGSize(width: x, height: maxHeight)),
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
            size: constraint.clamped(size: CGSize(width: maxWidth, height: maxHeight)),
            node: VVNode(children: nodes)
        )
    }
}
