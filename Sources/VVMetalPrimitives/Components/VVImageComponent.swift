import CoreGraphics

public struct VVImageComponent: VVComponent {
    public var url: String
    public var size: CGSize
    public var cornerRadius: CGFloat

    public init(url: String, size: CGSize, cornerRadius: CGFloat = 4) {
        self.url = url
        self.size = size
        self.cornerRadius = cornerRadius
    }

    public func measure(in env: VVLayoutEnvironment, width: CGFloat) -> VVComponentLayout {
        let frame = CGRect(origin: .zero, size: size)
        let primitive = VVPrimitiveKind.image(VVImagePrimitive(url: url, frame: frame, cornerRadius: cornerRadius))
        let node = VVNode(primitives: [primitive])
        return VVComponentLayout(size: size, node: node)
    }
}

