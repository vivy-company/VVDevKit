import CoreGraphics

// MARK: - Padding Modifier

public struct VVPaddingModifier: VVView {
    public var child: any VVView
    public var top: CGFloat
    public var right: CGFloat
    public var bottom: CGFloat
    public var left: CGFloat

    public init(child: any VVView, top: CGFloat, right: CGFloat, bottom: CGFloat, left: CGFloat) {
        self.child = child
        self.top = top
        self.right = right
        self.bottom = bottom
        self.left = left
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let innerConstraint = constraint.insetBy(dx: left + right, dy: top + bottom)
        let childLayout = child.layout(in: env, constraint: innerConstraint)

        let totalSize = constraint.clamped(size: CGSize(
            width: childLayout.size.width + left + right,
            height: childLayout.size.height + top + bottom
        ))
        let node = VVNode(offset: CGPoint(x: left, y: top), children: [childLayout.node])
        return VVViewLayout(size: totalSize, node: VVNode(children: [node]))
    }
}

// MARK: - Background Modifier

public struct VVBackgroundModifier: VVView {
    public var child: any VVView
    public var color: SIMD4<Float>
    public var cornerRadii: VVCornerRadii

    public init(child: any VVView, color: SIMD4<Float>, cornerRadii: VVCornerRadii = .zero) {
        self.child = child
        self.color = color
        self.cornerRadii = cornerRadii
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        let quad = VVQuadPrimitive(
            frame: CGRect(origin: .zero, size: childLayout.size),
            color: color,
            cornerRadii: cornerRadii
        )
        let bgNode = VVNode(primitives: [.quad(quad)])
        let container = VVNode(children: [bgNode, childLayout.node])
        return VVViewLayout(size: childLayout.size, node: container)
    }
}

public struct VVBackgroundContentModifier: VVView {
    public var child: any VVView
    public var background: any VVView
    public var alignment: VVFrameAlignment

    public init(child: any VVView, background: any VVView, alignment: VVFrameAlignment = .center) {
        self.child = child
        self.background = background
        self.alignment = alignment
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        let backgroundLayout = background.layout(
            in: env,
            constraint: VVLayoutConstraint(
                minWidth: 0,
                idealWidth: childLayout.size.width,
                maxWidth: childLayout.size.width,
                minHeight: 0,
                idealHeight: childLayout.size.height,
                maxHeight: childLayout.size.height
            )
        )
        let bgOffset = CGPoint(
            x: alignment.xOffset(containerWidth: childLayout.size.width, childWidth: backgroundLayout.size.width),
            y: alignment.yOffset(containerHeight: childLayout.size.height, childHeight: backgroundLayout.size.height)
        )
        return VVViewLayout(
            size: childLayout.size,
            node: VVNode(children: [
                VVNode(offset: bgOffset, zIndex: -1, children: [backgroundLayout.node]),
                childLayout.node
            ])
        )
    }
}

// MARK: - Border Modifier

public struct VVBorderModifier: VVView {
    public var child: any VVView
    public var border: VVBorder
    public var cornerRadii: VVCornerRadii

    public init(child: any VVView, border: VVBorder, cornerRadii: VVCornerRadii = .zero) {
        self.child = child
        self.border = border
        self.cornerRadii = cornerRadii
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        let quad = VVQuadPrimitive(
            frame: CGRect(origin: .zero, size: childLayout.size),
            color: .clear,
            cornerRadii: cornerRadii,
            border: border
        )
        let borderNode = VVNode(zIndex: 1, primitives: [.quad(quad)])
        let container = VVNode(children: [childLayout.node, borderNode])
        return VVViewLayout(size: childLayout.size, node: container)
    }
}

// MARK: - Overlay Modifier

public struct VVOverlayModifier: VVView {
    public var child: any VVView
    public var overlay: any VVView
    public var alignment: VVFrameAlignment

    public init(child: any VVView, overlay: any VVView, alignment: VVFrameAlignment = .center) {
        self.child = child
        self.overlay = overlay
        self.alignment = alignment
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        let overlayLayout = overlay.layout(
            in: env,
            constraint: VVLayoutConstraint(
                minWidth: 0,
                idealWidth: childLayout.size.width,
                maxWidth: childLayout.size.width,
                minHeight: 0,
                idealHeight: childLayout.size.height,
                maxHeight: childLayout.size.height
            )
        )
        let overlayOffset = CGPoint(
            x: alignment.xOffset(containerWidth: childLayout.size.width, childWidth: overlayLayout.size.width),
            y: alignment.yOffset(containerHeight: childLayout.size.height, childHeight: overlayLayout.size.height)
        )
        return VVViewLayout(
            size: childLayout.size,
            node: VVNode(children: [
                childLayout.node,
                VVNode(offset: overlayOffset, zIndex: 1, children: [overlayLayout.node])
            ])
        )
    }
}

// MARK: - Shadow Modifier

public struct VVShadowModifier: VVView {
    public var child: any VVView
    public var color: SIMD4<Float>
    public var cornerRadii: VVCornerRadii
    public var spread: CGFloat
    public var blurRadius: CGFloat
    public var offset: CGPoint
    public var steps: Int

    public init(
        child: any VVView,
        color: SIMD4<Float>,
        cornerRadii: VVCornerRadii = .zero,
        spread: CGFloat = 10,
        blurRadius: CGFloat = 0,
        offset: CGPoint = .zero,
        steps: Int = 6
    ) {
        self.child = child
        self.color = color
        self.cornerRadii = cornerRadii
        self.spread = spread
        self.blurRadius = blurRadius
        self.offset = offset
        self.steps = steps
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        let shadow = VVShadowQuadPrimitive(
            frame: CGRect(origin: .zero, size: childLayout.size),
            color: color,
            cornerRadii: cornerRadii,
            spread: spread,
            blurRadius: blurRadius,
            offset: offset,
            steps: steps
        )
        let expandedQuads = shadow.expandedQuads()
        let shadowPrimitives = expandedQuads.map { VVPrimitiveKind.quad($0) }
        let shadowNode = VVNode(zIndex: -1, primitives: shadowPrimitives)
        let container = VVNode(children: [shadowNode, childLayout.node])
        return VVViewLayout(size: childLayout.size, node: container)
    }
}

// MARK: - Frame Modifier

public struct VVFrameModifier: VVView {
    public var child: any VVView
    public var minWidth: CGFloat?
    public var idealWidth: CGFloat?
    public var maxWidth: CGFloat?
    public var minHeight: CGFloat?
    public var idealHeight: CGFloat?
    public var maxHeight: CGFloat?
    public var alignment: VVFrameAlignment

    public init(
        child: any VVView,
        minWidth: CGFloat? = nil,
        idealWidth: CGFloat? = nil,
        maxWidth: CGFloat? = nil,
        minHeight: CGFloat? = nil,
        idealHeight: CGFloat? = nil,
        maxHeight: CGFloat? = nil,
        alignment: VVFrameAlignment = .center
    ) {
        self.child = child
        self.minWidth = minWidth
        self.idealWidth = idealWidth
        self.maxWidth = maxWidth
        self.minHeight = minHeight
        self.idealHeight = idealHeight
        self.maxHeight = maxHeight
        self.alignment = alignment
    }

    public init(child: any VVView, width: CGFloat? = nil, height: CGFloat? = nil, alignment: VVFrameAlignment = .center) {
        self.child = child
        self.minWidth = width
        self.idealWidth = width
        self.maxWidth = width
        self.minHeight = height
        self.idealHeight = height
        self.maxHeight = height
        self.alignment = alignment
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let explicitMinWidth = minWidth
        let explicitIdealWidth = idealWidth
        let explicitMaxWidth = maxWidth
        let explicitMinHeight = minHeight
        let explicitIdealHeight = idealHeight
        let explicitMaxHeight = maxHeight

        let childMaxWidth: CGFloat = {
            if let explicitMaxWidth {
                return explicitMaxWidth.isFinite ? min(explicitMaxWidth, constraint.maxWidth) : constraint.maxWidth
            }
            return constraint.maxWidth
        }()
        let childMaxHeight: CGFloat = {
            if let explicitMaxHeight {
                return explicitMaxHeight.isFinite ? min(explicitMaxHeight, constraint.maxHeight) : constraint.maxHeight
            }
            return constraint.maxHeight
        }()
        let innerConstraint = VVLayoutConstraint(
            minWidth: explicitMinWidth ?? 0,
            idealWidth: explicitIdealWidth ?? constraint.idealWidth,
            maxWidth: childMaxWidth,
            minHeight: explicitMinHeight ?? 0,
            idealHeight: explicitIdealHeight ?? constraint.idealHeight,
            maxHeight: childMaxHeight
        )
        let childLayout = child.layout(in: env, constraint: innerConstraint)

        let expandsToParentWidth = explicitMaxWidth == .greatestFiniteMagnitude && constraint.hasBoundedWidth
        let expandsToParentHeight = explicitMaxHeight == .greatestFiniteMagnitude && constraint.hasBoundedHeight

        let unclampedWidth = expandsToParentWidth
            ? constraint.maxWidth
            : max(explicitMinWidth ?? 0, min(childLayout.size.width, explicitMaxWidth ?? childLayout.size.width))
        let unclampedHeight = expandsToParentHeight
            ? constraint.maxHeight
            : max(explicitMinHeight ?? 0, min(childLayout.size.height, explicitMaxHeight ?? childLayout.size.height))
        let finalSize = constraint.clamped(size: CGSize(width: unclampedWidth, height: unclampedHeight))
        let childOffset = CGPoint(
            x: alignment.xOffset(containerWidth: finalSize.width, childWidth: childLayout.size.width),
            y: alignment.yOffset(containerHeight: finalSize.height, childHeight: childLayout.size.height)
        )
        return VVViewLayout(
            size: finalSize,
            node: VVNode(offset: childOffset, children: [childLayout.node])
        )
    }
}

// MARK: - Opacity Modifier

public struct VVOpacityModifier: VVView {
    public var child: any VVView
    public var opacity: Float

    public init(child: any VVView, opacity: Float) {
        self.child = child
        self.opacity = opacity
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        let node = applyOpacity(to: childLayout.node, factor: opacity)
        return VVViewLayout(size: childLayout.size, node: node)
    }

    private func applyOpacity(to node: VVNode, factor: Float) -> VVNode {
        let scaledPrimitives = node.primitives.map { kind -> VVPrimitiveKind in
            switch kind {
            case .quad(var quad):
                quad.color.w *= factor
                quad.opacity *= factor
                return .quad(quad)
            case .textRun(var run):
                run.glyphs = run.glyphs.map { glyph in
                    var color = glyph.color
                    color.w *= factor
                    return VVTextGlyph(
                        glyphID: glyph.glyphID,
                        position: glyph.position,
                        size: glyph.size,
                        color: color,
                        fontVariant: glyph.fontVariant,
                        fontSize: glyph.fontSize,
                        fontName: glyph.fontName,
                        stringIndex: glyph.stringIndex
                    )
                }
                run.style.color.w *= factor
                return .textRun(run)
            case .line(var line):
                line.color.w *= factor
                return .line(line)
            case .gradientQuad(var grad):
                grad.startColor.w *= factor
                grad.endColor.w *= factor
                return .gradientQuad(grad)
            case .underline(var u):
                u.color.w *= factor
                return .underline(u)
            case .bullet(var b):
                b.color.w *= factor
                return .bullet(b)
            case .blockQuoteBorder(var bq):
                bq.color.w *= factor
                return .blockQuoteBorder(bq)
            case .tableLine(var tl):
                tl.color.w *= factor
                return .tableLine(tl)
            case .pieSlice(var ps):
                ps.color.w *= factor
                return .pieSlice(ps)
            default:
                return kind
            }
        }

        let scaledChildren = node.children.map { applyOpacity(to: $0, factor: factor) }
        return VVNode(
            offset: node.offset,
            clipRect: node.clipRect,
            zIndex: node.zIndex,
            transform: node.transform,
            primitives: scaledPrimitives,
            children: scaledChildren
        )
    }
}

// MARK: - Clip Modifier

public struct VVClipModifier: VVView {
    public var child: any VVView
    public var clipRect: CGRect

    public init(child: any VVView, clipRect: CGRect) {
        self.child = child
        self.clipRect = clipRect
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        var node = childLayout.node
        node.clipRect = clipRect
        return VVViewLayout(size: childLayout.size, node: node)
    }
}

// MARK: - Offset Modifier

public struct VVOffsetModifier: VVView {
    public var child: any VVView
    public var x: CGFloat
    public var y: CGFloat

    public init(child: any VVView, x: CGFloat, y: CGFloat) {
        self.child = child
        self.x = x
        self.y = y
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        let node = VVNode(offset: CGPoint(x: x, y: y), children: [childLayout.node])
        return VVViewLayout(size: childLayout.size, node: node)
    }
}

// MARK: - Positioned Frame

public struct VVPositionedFrame: VVView {
    public var frame: CGRect
    public var child: any VVView
    public var clipRect: CGRect?

    public init(frame: CGRect, child: any VVView, clipRect: CGRect? = nil) {
        self.frame = frame
        self.child = child
        self.clipRect = clipRect
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let innerConstraint = VVLayoutConstraint(maxWidth: frame.width, maxHeight: frame.height)
        let childLayout = child.layout(in: env, constraint: innerConstraint)
        let node = VVNode(offset: frame.origin, clipRect: clipRect, children: [childLayout.node])
        return VVViewLayout(size: frame.size, node: node)
    }
}

// MARK: - Scroll Container

public enum VVScrollAxis: Sendable {
    case vertical
    case horizontal
    case both
}

public struct VVScrollContainer: VVView {
    public var child: any VVView
    public var axis: VVScrollAxis
    public var viewportSize: CGSize?
    public var contentOffset: CGPoint
    public var showsClipping: Bool

    public init(
        child: any VVView,
        axis: VVScrollAxis = .vertical,
        viewportSize: CGSize? = nil,
        contentOffset: CGPoint = .zero,
        showsClipping: Bool = true
    ) {
        self.child = child
        self.axis = axis
        self.viewportSize = viewportSize
        self.contentOffset = contentOffset
        self.showsClipping = showsClipping
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let resolvedViewport = CGSize(
            width: viewportSize?.width ?? (constraint.hasBoundedWidth ? constraint.maxWidth : constraint.proposedWidth),
            height: viewportSize?.height ?? (constraint.hasBoundedHeight ? constraint.maxHeight : constraint.proposedHeight)
        )

        let childConstraint = VVLayoutConstraint(
            minWidth: 0,
            idealWidth: axis == .vertical ? resolvedViewport.width : nil,
            maxWidth: axis == .vertical ? resolvedViewport.width : .greatestFiniteMagnitude,
            minHeight: 0,
            idealHeight: axis == .horizontal ? resolvedViewport.height : nil,
            maxHeight: axis == .horizontal ? resolvedViewport.height : .greatestFiniteMagnitude
        )
        let childLayout = child.layout(in: env, constraint: childConstraint)
        let clip = showsClipping ? CGRect(origin: .zero, size: resolvedViewport) : nil
        return VVViewLayout(
            size: constraint.clamped(size: resolvedViewport),
            node: VVNode(
                children: [
                    VVNode(offset: CGPoint(x: -contentOffset.x, y: -contentOffset.y), clipRect: clip, children: [childLayout.node])
                ]
            )
        )
    }
}

// MARK: - ZIndex Modifier

public struct VVZIndexModifier: VVView {
    public var child: any VVView
    public var zIndex: Int

    public init(child: any VVView, zIndex: Int) {
        self.child = child
        self.zIndex = zIndex
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        var node = childLayout.node
        node.zIndex = zIndex
        return VVViewLayout(size: childLayout.size, node: node)
    }
}

// MARK: - Transform Modifier

public struct VVTransformModifier: VVView {
    public var child: any VVView
    public var transform: VVTransform2D

    public init(child: any VVView, transform: VVTransform2D) {
        self.child = child
        self.transform = transform
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        var node = childLayout.node
        node.transform = transform
        return VVViewLayout(size: childLayout.size, node: node)
    }
}

// MARK: - Identity Modifier

public struct VVIdentityModifier: VVView {
    public var child: any VVView
    public var id: String

    public init(child: any VVView, id: String) {
        self.child = child
        self.id = id
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        var node = childLayout.node
        node.identity = id
        return VVViewLayout(size: childLayout.size, node: node)
    }
}

// MARK: - Transition Modifier

public struct VVTransitionModifier: VVView {
    public var child: any VVView
    public var transition: VVTransition

    public init(child: any VVView, transition: VVTransition) {
        self.child = child
        self.transition = transition
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        var node = childLayout.node
        node.transition = transition
        return VVViewLayout(size: childLayout.size, node: node)
    }
}

// MARK: - Animation Modifier

public struct VVAnimationModifier: VVView {
    public var child: any VVView
    public var animation: VVAnimationDescriptor

    public init(child: any VVView, animation: VVAnimationDescriptor) {
        self.child = child
        self.animation = animation
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let childLayout = child.layout(in: env, constraint: constraint)
        var node = childLayout.node
        node.animation = animation
        return VVViewLayout(size: childLayout.size, node: node)
    }
}
