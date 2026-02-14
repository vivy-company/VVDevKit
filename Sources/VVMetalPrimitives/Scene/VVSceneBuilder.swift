import CoreGraphics

public struct VVSceneBuilder {
    public private(set) var scene: VVScene
    private var clipStack: [CGRect]
    private var currentClip: CGRect?
    private var offsetStack: [CGPoint]
    private var currentOffset: CGPoint

    public init(scene: VVScene = VVScene()) {
        self.scene = scene
        self.clipStack = []
        self.currentClip = nil
        self.offsetStack = []
        self.currentOffset = .zero
    }

    public mutating func pushClip(_ rect: CGRect) {
        clipStack.append(rect)
        if let existing = currentClip {
            currentClip = existing.intersection(rect)
        } else {
            currentClip = rect
        }
    }

    public mutating func popClip() {
        _ = clipStack.popLast()
        currentClip = nil
        for rect in clipStack {
            if let existing = currentClip {
                currentClip = existing.intersection(rect)
            } else {
                currentClip = rect
            }
        }
    }

    public mutating func withClip(_ rect: CGRect, _ body: (inout VVSceneBuilder) -> Void) {
        pushClip(rect)
        body(&self)
        popClip()
    }

    public mutating func add(_ primitive: VVPrimitive) {
        var resolved = primitive
        if resolved.clipRect == nil {
            resolved.clipRect = currentClip
        }
        if currentOffset != .zero {
            resolved = offsetPrimitive(resolved, by: currentOffset)
        }
        scene.add(resolved)
    }

    public mutating func add(kind: VVPrimitiveKind, clipRect: CGRect? = nil, zIndex: Int = 0) {
        let resolvedClip = clipRect ?? currentClip
        var primitive = VVPrimitive(kind: kind, clipRect: resolvedClip, zIndex: zIndex)
        if currentOffset != .zero {
            primitive = offsetPrimitive(primitive, by: currentOffset)
        }
        scene.add(primitive)
    }

    public mutating func add(node: VVNode) {
        let flattened = node.flattenedPrimitives(
            parentClip: currentClip,
            parentOffset: currentOffset,
            parentZ: 0
        )
        for primitive in flattened {
            scene.add(primitive)
        }
    }

    public mutating func pushOffset(_ offset: CGPoint) {
        offsetStack.append(offset)
        currentOffset = CGPoint(x: currentOffset.x + offset.x, y: currentOffset.y + offset.y)
    }

    public mutating func popOffset() {
        guard let offset = offsetStack.popLast() else { return }
        currentOffset = CGPoint(x: currentOffset.x - offset.x, y: currentOffset.y - offset.y)
    }

    public mutating func withOffset(_ offset: CGPoint, _ body: (inout VVSceneBuilder) -> Void) {
        pushOffset(offset)
        body(&self)
        popOffset()
    }

    private func offsetPrimitive(_ primitive: VVPrimitive, by offset: CGPoint) -> VVPrimitive {
        let clipRect = primitive.clipRect?.offsetBy(dx: offset.x, dy: offset.y)
        let offsetKind = VVNode.offsetPrimitive(primitive.kind, by: offset)
        return VVPrimitive(kind: offsetKind, clipRect: clipRect, zIndex: primitive.zIndex)
    }
}
