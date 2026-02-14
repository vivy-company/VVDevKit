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
        let innerWidth = max(0, constraint.maxWidth - left - right)
        let innerHeight = max(0, constraint.maxHeight - top - bottom)
        let innerConstraint = VVLayoutConstraint(maxWidth: innerWidth, maxHeight: innerHeight)
        let childLayout = child.layout(in: env, constraint: innerConstraint)

        let totalSize = CGSize(
            width: childLayout.size.width + left + right,
            height: childLayout.size.height + top + bottom
        )
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
    public var width: CGFloat?
    public var height: CGFloat?

    public init(child: any VVView, width: CGFloat? = nil, height: CGFloat? = nil) {
        self.child = child
        self.width = width
        self.height = height
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let constrainedWidth = width ?? constraint.maxWidth
        let constrainedHeight = height ?? constraint.maxHeight
        let innerConstraint = VVLayoutConstraint(maxWidth: constrainedWidth, maxHeight: constrainedHeight)
        let childLayout = child.layout(in: env, constraint: innerConstraint)

        let finalWidth = width ?? childLayout.size.width
        let finalHeight = height ?? childLayout.size.height
        return VVViewLayout(
            size: CGSize(width: finalWidth, height: finalHeight),
            node: childLayout.node
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
