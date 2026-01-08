import CoreGraphics

public struct VVNode: Hashable, Sendable {
    public var offset: CGPoint
    public var clipRect: CGRect?
    public var zIndex: Int
    public var primitives: [VVPrimitiveKind]
    public var children: [VVNode]

    public init(
        offset: CGPoint = .zero,
        clipRect: CGRect? = nil,
        zIndex: Int = 0,
        primitives: [VVPrimitiveKind] = [],
        children: [VVNode] = []
    ) {
        self.offset = offset
        self.clipRect = clipRect
        self.zIndex = zIndex
        self.primitives = primitives
        self.children = children
    }

    public func flattened() -> VVScene {
        var scene = VVScene()
        for primitive in flattenedPrimitives() {
            scene.add(primitive)
        }
        return scene
    }

    public func flattenedPrimitives(
        parentClip: CGRect? = nil,
        parentOffset: CGPoint = .zero,
        parentZ: Int = 0
    ) -> [VVPrimitive] {
        var primitives: [VVPrimitive] = []
        flatten(into: &primitives, parentClip: parentClip, parentOffset: parentOffset, parentZ: parentZ)
        return primitives
    }

    private func flatten(into output: inout [VVPrimitive], parentClip: CGRect?, parentOffset: CGPoint, parentZ: Int) {
        let combinedOffset = CGPoint(x: parentOffset.x + offset.x, y: parentOffset.y + offset.y)
        let localClip = clipRect?.offsetBy(dx: combinedOffset.x, dy: combinedOffset.y)
        let combinedClip: CGRect?
        if let parentClip, let localClip {
            combinedClip = parentClip.intersection(localClip)
        } else {
            combinedClip = parentClip ?? localClip
        }

        let resolvedZ = parentZ + zIndex
        for kind in primitives {
            let offsetKind = offsetPrimitive(kind, by: combinedOffset)
            output.append(VVPrimitive(kind: offsetKind, clipRect: combinedClip, zIndex: resolvedZ))
        }

        for child in children {
            child.flatten(into: &output, parentClip: combinedClip, parentOffset: combinedOffset, parentZ: resolvedZ)
        }
    }

    private func offsetPrimitive(_ kind: VVPrimitiveKind, by offset: CGPoint) -> VVPrimitiveKind {
        switch kind {
        case .quad(let quad):
            let updated = VVQuadPrimitive(
                frame: quad.frame.offsetBy(dx: offset.x, dy: offset.y),
                color: quad.color,
                cornerRadius: quad.cornerRadius
            )
            return .quad(updated)

        case .line(let line):
            let updated = VVLinePrimitive(
                start: CGPoint(x: line.start.x + offset.x, y: line.start.y + offset.y),
                end: CGPoint(x: line.end.x + offset.x, y: line.end.y + offset.y),
                thickness: line.thickness,
                color: line.color
            )
            return .line(updated)

        case .bullet(let bullet):
            let updated = VVBulletPrimitive(
                position: CGPoint(x: bullet.position.x + offset.x, y: bullet.position.y + offset.y),
                size: bullet.size,
                color: bullet.color,
                type: bullet.type
            )
            return .bullet(updated)

        case .image(let image):
            let updated = VVImagePrimitive(
                url: image.url,
                frame: image.frame.offsetBy(dx: offset.x, dy: offset.y),
                cornerRadius: image.cornerRadius
            )
            return .image(updated)

        case .blockQuoteBorder(let border):
            let updated = VVBlockQuoteBorderPrimitive(
                frame: border.frame.offsetBy(dx: offset.x, dy: offset.y),
                color: border.color,
                borderWidth: border.borderWidth
            )
            return .blockQuoteBorder(updated)

        case .tableLine(let line):
            let updated = VVTableLinePrimitive(
                start: CGPoint(x: line.start.x + offset.x, y: line.start.y + offset.y),
                end: CGPoint(x: line.end.x + offset.x, y: line.end.y + offset.y),
                color: line.color,
                lineWidth: line.lineWidth
            )
            return .tableLine(updated)

        case .pieSlice(let slice):
            let updated = VVPieSlicePrimitive(
                center: CGPoint(x: slice.center.x + offset.x, y: slice.center.y + offset.y),
                radius: slice.radius,
                startAngle: slice.startAngle,
                endAngle: slice.endAngle,
                color: slice.color
            )
            return .pieSlice(updated)

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
            return .textRun(updated)
        }
    }
}
