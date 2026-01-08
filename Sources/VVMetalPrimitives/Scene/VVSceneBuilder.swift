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
        switch primitive.kind {
        case .quad(let quad):
            let updated = VVQuadPrimitive(
                frame: quad.frame.offsetBy(dx: offset.x, dy: offset.y),
                color: quad.color,
                cornerRadius: quad.cornerRadius
            )
            return VVPrimitive(kind: .quad(updated), clipRect: clipRect, zIndex: primitive.zIndex)

        case .line(let line):
            let updated = VVLinePrimitive(
                start: CGPoint(x: line.start.x + offset.x, y: line.start.y + offset.y),
                end: CGPoint(x: line.end.x + offset.x, y: line.end.y + offset.y),
                thickness: line.thickness,
                color: line.color
            )
            return VVPrimitive(kind: .line(updated), clipRect: clipRect, zIndex: primitive.zIndex)

        case .bullet(let bullet):
            let updated = VVBulletPrimitive(
                position: CGPoint(x: bullet.position.x + offset.x, y: bullet.position.y + offset.y),
                size: bullet.size,
                color: bullet.color,
                type: bullet.type
            )
            return VVPrimitive(kind: .bullet(updated), clipRect: clipRect, zIndex: primitive.zIndex)

        case .image(let image):
            let updated = VVImagePrimitive(
                url: image.url,
                frame: image.frame.offsetBy(dx: offset.x, dy: offset.y),
                cornerRadius: image.cornerRadius
            )
            return VVPrimitive(kind: .image(updated), clipRect: clipRect, zIndex: primitive.zIndex)

        case .blockQuoteBorder(let border):
            let updated = VVBlockQuoteBorderPrimitive(
                frame: border.frame.offsetBy(dx: offset.x, dy: offset.y),
                color: border.color,
                borderWidth: border.borderWidth
            )
            return VVPrimitive(kind: .blockQuoteBorder(updated), clipRect: clipRect, zIndex: primitive.zIndex)

        case .tableLine(let line):
            let updated = VVTableLinePrimitive(
                start: CGPoint(x: line.start.x + offset.x, y: line.start.y + offset.y),
                end: CGPoint(x: line.end.x + offset.x, y: line.end.y + offset.y),
                color: line.color,
                lineWidth: line.lineWidth
            )
            return VVPrimitive(kind: .tableLine(updated), clipRect: clipRect, zIndex: primitive.zIndex)

        case .pieSlice(let slice):
            let updated = VVPieSlicePrimitive(
                center: CGPoint(x: slice.center.x + offset.x, y: slice.center.y + offset.y),
                radius: slice.radius,
                startAngle: slice.startAngle,
                endAngle: slice.endAngle,
                color: slice.color
            )
            return VVPrimitive(kind: .pieSlice(updated), clipRect: clipRect, zIndex: primitive.zIndex)

        case .textRun(let run):
            let glyphs = run.glyphs.map { glyph -> VVTextGlyph in
                VVTextGlyph(
                    glyphID: glyph.glyphID,
                    position: CGPoint(x: glyph.position.x + offset.x, y: glyph.position.y + offset.y),
                    size: glyph.size,
                    color: glyph.color,
                    fontVariant: glyph.fontVariant,
                    fontSize: glyph.fontSize,
                    fontName: glyph.fontName,
                    stringIndex: glyph.stringIndex
                )
            }
            let updated = VVTextRunPrimitive(
                glyphs: glyphs,
                style: run.style,
                lineBounds: run.lineBounds?.offsetBy(dx: offset.x, dy: offset.y),
                runBounds: run.runBounds?.offsetBy(dx: offset.x, dy: offset.y),
                position: CGPoint(x: run.position.x + offset.x, y: run.position.y + offset.y),
                fontSize: run.fontSize
            )
            return VVPrimitive(kind: .textRun(updated), clipRect: clipRect, zIndex: primitive.zIndex)
        }
    }
}
