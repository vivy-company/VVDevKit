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
        if let minWidth = modifier.minWidth,
           let idealWidth = modifier.idealWidth,
           let maxWidth = modifier.maxWidth,
           abs(minWidth - idealWidth) < 0.001,
           abs(minWidth - maxWidth) < 0.001 {
            return .fixed
        }
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVPaddingModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVBackgroundModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVBackgroundContentModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVBorderModifier:
        return vvHorizontalSizingBehavior(for: modifier.child)
    case let modifier as VVOverlayModifier:
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
    case let container as VVScrollContainer:
        return vvHorizontalSizingBehavior(for: container.child)
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

public enum VVZStackSizing: Sendable {
    case union
    case firstChild
}

public enum VVFlowAlignment: Sendable {
    case leading
    case center
    case trailing
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
    public var alignment: VVFrameAlignment
    public var sizing: VVZStackSizing
    public var children: [any VVView]

    public init(
        alignment: VVFrameAlignment = .topLeading,
        sizing: VVZStackSizing = .union,
        @VVViewBuilder content: () -> [any VVView]
    ) {
        self.alignment = alignment
        self.sizing = sizing
        self.children = content()
    }

    public init(
        alignment: VVFrameAlignment = .topLeading,
        sizing: VVZStackSizing = .union,
        children: [any VVView]
    ) {
        self.alignment = alignment
        self.sizing = sizing
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

        let containerSize: CGSize
        switch sizing {
        case .union:
            containerSize = constraint.clamped(size: CGSize(width: maxWidth, height: maxHeight))
        case .firstChild:
            containerSize = constraint.clamped(size: childLayouts.first?.size ?? .zero)
        }

        var nodes: [VVNode] = []
        for (index, childLayout) in childLayouts.enumerated() {
            let offset = CGPoint(
                x: alignment.xOffset(containerWidth: containerSize.width, childWidth: childLayout.size.width),
                y: alignment.yOffset(containerHeight: containerSize.height, childHeight: childLayout.size.height)
            )
            nodes.append(VVNode(offset: offset, zIndex: index, children: [childLayout.node]))
        }

        return VVViewLayout(
            size: containerSize,
            node: VVNode(children: nodes)
        )
    }
}

// MARK: - VVFlowStack

public struct VVFlowStack: VVView {
    public var horizontalSpacing: CGFloat
    public var verticalSpacing: CGFloat
    public var alignment: VVFlowAlignment
    public var children: [any VVView]

    public init(
        horizontalSpacing: CGFloat = 8,
        verticalSpacing: CGFloat = 8,
        alignment: VVFlowAlignment = .leading,
        @VVViewBuilder content: () -> [any VVView]
    ) {
        self.horizontalSpacing = horizontalSpacing
        self.verticalSpacing = verticalSpacing
        self.alignment = alignment
        self.children = content()
    }

    public init(
        horizontalSpacing: CGFloat = 8,
        verticalSpacing: CGFloat = 8,
        alignment: VVFlowAlignment = .leading,
        children: [any VVView]
    ) {
        self.horizontalSpacing = horizontalSpacing
        self.verticalSpacing = verticalSpacing
        self.alignment = alignment
        self.children = children
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        guard !children.isEmpty else { return .empty }

        let maxLineWidth = constraint.hasBoundedWidth ? constraint.maxWidth : .greatestFiniteMagnitude
        let measured = children.map {
            $0.layout(
                in: env,
                constraint: VVLayoutConstraint(
                    minWidth: 0,
                    idealWidth: nil,
                    maxWidth: maxLineWidth,
                    minHeight: 0,
                    idealHeight: nil,
                    maxHeight: constraint.maxHeight
                )
            )
        }

        struct Line {
            var items: [(index: Int, layout: VVViewLayout)]
            var width: CGFloat
            var height: CGFloat
        }

        var lines: [Line] = []
        var currentItems: [(index: Int, layout: VVViewLayout)] = []
        var currentWidth: CGFloat = 0
        var currentHeight: CGFloat = 0

        for (index, layout) in measured.enumerated() {
            let proposedWidth = currentItems.isEmpty ? layout.size.width : currentWidth + horizontalSpacing + layout.size.width
            let shouldWrap = !currentItems.isEmpty && constraint.hasBoundedWidth && proposedWidth > maxLineWidth
            if shouldWrap {
                lines.append(Line(items: currentItems, width: currentWidth, height: currentHeight))
                currentItems = [(index, layout)]
                currentWidth = layout.size.width
                currentHeight = layout.size.height
            } else {
                currentItems.append((index, layout))
                currentWidth = currentItems.count == 1 ? layout.size.width : proposedWidth
                currentHeight = max(currentHeight, layout.size.height)
            }
        }

        if !currentItems.isEmpty {
            lines.append(Line(items: currentItems, width: currentWidth, height: currentHeight))
        }

        var nodes: [VVNode] = []
        var y: CGFloat = 0
        var maxWidth: CGFloat = 0

        for (lineIndex, line) in lines.enumerated() {
            let lineX: CGFloat
            switch alignment {
            case .leading:
                lineX = 0
            case .center:
                lineX = constraint.hasBoundedWidth ? max(0, (maxLineWidth - line.width) * 0.5) : 0
            case .trailing:
                lineX = constraint.hasBoundedWidth ? max(0, maxLineWidth - line.width) : 0
            }

            var x = lineX
            for (_, layout) in line.items {
                nodes.append(VVNode(offset: CGPoint(x: x, y: y), children: [layout.node]))
                x += layout.size.width + horizontalSpacing
            }
            maxWidth = max(maxWidth, line.width)
            y += line.height
            if lineIndex < lines.count - 1 {
                y += verticalSpacing
            }
        }

        let finalWidth = constraint.hasBoundedWidth ? max(maxWidth, constraint.minWidth) : maxWidth
        return VVViewLayout(
            size: constraint.clamped(size: CGSize(width: finalWidth, height: y)),
            node: VVNode(children: nodes)
        )
    }
}
