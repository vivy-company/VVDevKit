import CoreGraphics

public struct VRect: VVView {
    public var color: SIMD4<Float>
    public var cornerRadii: VVCornerRadii
    public var border: VVBorder?
    public var opacity: Float
    public var width: CGFloat?
    public var height: CGFloat?

    public init(
        color: SIMD4<Float>,
        cornerRadii: VVCornerRadii = .zero,
        border: VVBorder? = nil,
        opacity: Float = 1,
        width: CGFloat? = nil,
        height: CGFloat? = nil
    ) {
        self.color = color
        self.cornerRadii = cornerRadii
        self.border = border
        self.opacity = opacity
        self.width = width
        self.height = height
    }

    public init(color: SIMD4<Float>, cornerRadius: CGFloat) {
        self.color = color
        self.cornerRadii = VVCornerRadii(cornerRadius)
        self.border = nil
        self.opacity = 1
        self.width = nil
        self.height = nil
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let width = width ?? (constraint.hasBoundedWidth ? constraint.proposedWidth : max(constraint.minWidth, 0))
        let resolvedHeight = height ?? (constraint.hasBoundedHeight ? constraint.proposedHeight : max(constraint.minHeight, 0))
        let quad = VVQuadPrimitive(
            frame: CGRect(x: 0, y: 0, width: width, height: resolvedHeight),
            color: color,
            cornerRadii: cornerRadii,
            border: border,
            opacity: opacity
        )
        let node = VVNode(primitives: [.quad(quad)])
        return VVViewLayout(size: constraint.clamped(size: CGSize(width: width, height: resolvedHeight)), node: node)
    }
}
