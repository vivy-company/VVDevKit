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
    public var transform: VVTransform2D?

    public init(kind: VVPrimitiveKind, clipRect: CGRect? = nil, zIndex: Int = 0, transform: VVTransform2D? = nil) {
        self.kind = kind
        self.clipRect = clipRect
        self.zIndex = zIndex
        self.transform = transform
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

    public mutating func add(kind: VVPrimitiveKind, clipRect: CGRect? = nil, zIndex: Int = 0, transform: VVTransform2D? = nil) {
        primitives.append(VVPrimitive(kind: kind, clipRect: clipRect, zIndex: zIndex, transform: transform))
    }

    public func orderedPrimitiveIndices() -> [Int] {
        guard !primitives.isEmpty else { return [] }

        var indices = Array(primitives.indices)
        var alreadyOrdered = true
        var previous = primitives[indices[0]].zIndex

        for index in indices.dropFirst() {
            let current = primitives[index].zIndex
            if current < previous {
                alreadyOrdered = false
                break
            }
            previous = current
        }

        guard !alreadyOrdered else { return indices }

        indices.sort { lhs, rhs in
            if primitives[lhs].zIndex == primitives[rhs].zIndex {
                return lhs < rhs
            }
            return primitives[lhs].zIndex < primitives[rhs].zIndex
        }
        return indices
    }

    public func orderedPrimitives() -> [VVPrimitive] {
        let indices = orderedPrimitiveIndices()
        guard !indices.isEmpty else { return [] }

        var isIdentityOrder = indices.count == primitives.count
        if isIdentityOrder {
            for position in indices.indices where indices[position] != position {
                isIdentityOrder = false
                break
            }
        }
        guard !isIdentityOrder else { return primitives }

        var ordered: [VVPrimitive] = []
        ordered.reserveCapacity(indices.count)
        for index in indices {
            ordered.append(primitives[index])
        }
        return ordered
    }
}
