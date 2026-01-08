import CoreGraphics

public struct VVRuleComponent: VVComponent {
    public var thickness: CGFloat
    public var color: SIMD4<Float>
    public var inset: CGFloat

    public init(thickness: CGFloat = 1, color: SIMD4<Float>, inset: CGFloat = 0) {
        self.thickness = thickness
        self.color = color
        self.inset = inset
    }

    public func measure(in env: VVLayoutEnvironment, width: CGFloat) -> VVComponentLayout {
        let lineWidth = max(0, width - inset * 2)
        let line = VVLinePrimitive(
            start: CGPoint(x: inset, y: thickness * 0.5),
            end: CGPoint(x: inset + lineWidth, y: thickness * 0.5),
            thickness: thickness,
            color: color
        )
        let node = VVNode(primitives: [.line(line)])
        return VVComponentLayout(size: CGSize(width: width, height: max(1, thickness)), node: node)
    }
}

