import CoreGraphics

public struct VRect: VVView {
    public var color: SIMD4<Float>
    public var cornerRadii: VVCornerRadii
    public var border: VVBorder?
    public var opacity: Float

    public init(
        color: SIMD4<Float>,
        cornerRadii: VVCornerRadii = .zero,
        border: VVBorder? = nil,
        opacity: Float = 1
    ) {
        self.color = color
        self.cornerRadii = cornerRadii
        self.border = border
        self.opacity = opacity
    }

    public init(color: SIMD4<Float>, cornerRadius: CGFloat) {
        self.color = color
        self.cornerRadii = VVCornerRadii(cornerRadius)
        self.border = nil
        self.opacity = 1
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let width = constraint.maxWidth
        let height: CGFloat = 0
        let quad = VVQuadPrimitive(
            frame: CGRect(x: 0, y: 0, width: width, height: height),
            color: color,
            cornerRadii: cornerRadii,
            border: border,
            opacity: opacity
        )
        let node = VVNode(primitives: [.quad(quad)])
        return VVViewLayout(size: CGSize(width: width, height: height), node: node)
    }
}
