import CoreGraphics

public enum VVPrimitiveKind: Hashable, Sendable {
    case textRun(VVTextRunPrimitive)
    case quad(VVQuadPrimitive)
    case gradientQuad(VVGradientQuadPrimitive)
    case line(VVLinePrimitive)
    case underline(VVUnderlinePrimitive)
    case bullet(VVBulletPrimitive)
    case image(VVImagePrimitive)
    case blockQuoteBorder(VVBlockQuoteBorderPrimitive)
    case tableLine(VVTableLinePrimitive)
    case pieSlice(VVPieSlicePrimitive)
    case path(VVPathPrimitive)
}

public struct VVPrimitive: Hashable, Sendable {
    public var kind: VVPrimitiveKind
    public var clipRect: CGRect?
    public var zIndex: Int

    public init(kind: VVPrimitiveKind, clipRect: CGRect? = nil, zIndex: Int = 0) {
        self.kind = kind
        self.clipRect = clipRect
        self.zIndex = zIndex
    }
}

public struct VVScene: Sendable {
    public private(set) var primitives: [VVPrimitive]

    public init(primitives: [VVPrimitive] = []) {
        self.primitives = primitives
    }

    public mutating func add(_ primitive: VVPrimitive) {
        primitives.append(primitive)
    }

    public mutating func add(kind: VVPrimitiveKind, clipRect: CGRect? = nil, zIndex: Int = 0) {
        primitives.append(VVPrimitive(kind: kind, clipRect: clipRect, zIndex: zIndex))
    }

    public func orderedPrimitives() -> [VVPrimitive] {
        primitives.enumerated().sorted { lhs, rhs in
            if lhs.element.zIndex == rhs.element.zIndex {
                return lhs.offset < rhs.offset
            }
            return lhs.element.zIndex < rhs.element.zIndex
        }.map(\.element)
    }
}
