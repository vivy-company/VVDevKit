import CoreGraphics

public struct VVNode: Hashable, Sendable {
    public var layoutSize: CGSize?
    public var identity: String?
    public var transition: VVTransition?
    public var animation: VVAnimationDescriptor?
    public var offset: CGPoint
    public var clipRect: CGRect?
    public var zIndex: Int
    public var transform: VVTransform2D?
    public var primitives: [VVPrimitiveKind]
    public var children: [VVNode]

    public init(
        layoutSize: CGSize? = nil,
        identity: String? = nil,
        transition: VVTransition? = nil,
        animation: VVAnimationDescriptor? = nil,
        offset: CGPoint = .zero,
        clipRect: CGRect? = nil,
        zIndex: Int = 0,
        transform: VVTransform2D? = nil,
        primitives: [VVPrimitiveKind] = [],
        children: [VVNode] = []
    ) {
        self.layoutSize = layoutSize
        self.identity = identity
        self.transition = transition
        self.animation = animation
        self.offset = offset
        self.clipRect = clipRect
        self.zIndex = zIndex
        self.transform = transform
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
        parentZ: Int = 0,
        parentTransform: VVTransform2D? = nil
    ) -> [VVPrimitive] {
        var primitives: [VVPrimitive] = []
        flatten(into: &primitives, parentClip: parentClip, parentOffset: parentOffset, parentZ: parentZ, parentTransform: parentTransform)
        return primitives
    }

    private func flatten(into output: inout [VVPrimitive], parentClip: CGRect?, parentOffset: CGPoint, parentZ: Int, parentTransform: VVTransform2D?) {
        let combinedOffset = CGPoint(x: parentOffset.x + offset.x, y: parentOffset.y + offset.y)
        let localClip = clipRect?.offsetBy(dx: combinedOffset.x, dy: combinedOffset.y)
        let combinedClip: CGRect?
        if let parentClip, let localClip {
            combinedClip = parentClip.intersection(localClip)
        } else {
            combinedClip = parentClip ?? localClip
        }

        let resolvedZ = parentZ + zIndex
        let combinedTransform: VVTransform2D?
        switch (parentTransform, transform) {
        case let (lhs?, rhs?):
            combinedTransform = lhs.composed(with: rhs)
        case let (lhs?, nil):
            combinedTransform = lhs
        case let (nil, rhs?):
            combinedTransform = rhs
        case (nil, nil):
            combinedTransform = nil
        }
        for kind in primitives {
            let offsetKind = Self.offsetPrimitive(kind, by: combinedOffset)
            output.append(VVPrimitive(kind: offsetKind, clipRect: combinedClip, zIndex: resolvedZ, transform: combinedTransform))
        }

        for child in children {
            child.flatten(into: &output, parentClip: combinedClip, parentOffset: combinedOffset, parentZ: resolvedZ, parentTransform: combinedTransform)
        }
    }

    public func animationSnapshots(parentOrigin: CGPoint = .zero) -> [String: VVLayoutAnimationSnapshot] {
        var snapshots: [String: VVLayoutAnimationSnapshot] = [:]
        collectAnimationSnapshots(into: &snapshots, parentOrigin: parentOrigin)
        return snapshots
    }

    private func collectAnimationSnapshots(into output: inout [String: VVLayoutAnimationSnapshot], parentOrigin: CGPoint) {
        let absoluteOrigin = CGPoint(x: parentOrigin.x + offset.x, y: parentOrigin.y + offset.y)
        if let identity, let layoutSize {
            output[identity] = VVLayoutAnimationSnapshot(
                id: identity,
                frame: CGRect(origin: absoluteOrigin, size: layoutSize),
                transition: transition,
                animation: animation
            )
        }

        for child in children {
            child.collectAnimationSnapshots(into: &output, parentOrigin: absoluteOrigin)
        }
    }

    /// Offsets a primitive's position-related fields by the given amount, preserving all other fields.
    static func offsetPrimitive(_ kind: VVPrimitiveKind, by offset: CGPoint) -> VVPrimitiveKind {
        guard offset != .zero else { return kind }
        switch kind {
        case .quad(var quad):
            quad.frame = quad.frame.offsetBy(dx: offset.x, dy: offset.y)
            return .quad(quad)

        case .gradientQuad(var gradient):
            gradient.frame = gradient.frame.offsetBy(dx: offset.x, dy: offset.y)
            return .gradientQuad(gradient)

        case .line(var line):
            line.start = CGPoint(x: line.start.x + offset.x, y: line.start.y + offset.y)
            line.end = CGPoint(x: line.end.x + offset.x, y: line.end.y + offset.y)
            return .line(line)

        case .underline(var underline):
            underline.origin = CGPoint(x: underline.origin.x + offset.x, y: underline.origin.y + offset.y)
            return .underline(underline)

        case .bullet(var bullet):
            bullet.position = CGPoint(x: bullet.position.x + offset.x, y: bullet.position.y + offset.y)
            return .bullet(bullet)

        case .image(var image):
            image.frame = image.frame.offsetBy(dx: offset.x, dy: offset.y)
            return .image(image)

        case .blockQuoteBorder(var border):
            border.frame = border.frame.offsetBy(dx: offset.x, dy: offset.y)
            return .blockQuoteBorder(border)

        case .tableLine(var line):
            line.start = CGPoint(x: line.start.x + offset.x, y: line.start.y + offset.y)
            line.end = CGPoint(x: line.end.x + offset.x, y: line.end.y + offset.y)
            return .tableLine(line)

        case .pieSlice(var slice):
            slice.center = CGPoint(x: slice.center.x + offset.x, y: slice.center.y + offset.y)
            return .pieSlice(slice)

        case .path(var path):
            path.bounds = path.bounds.offsetBy(dx: offset.x, dy: offset.y)
            path.vertices = path.vertices.map {
                VVPathVertex(
                    position: CGPoint(x: $0.position.x + offset.x, y: $0.position.y + offset.y),
                    stPosition: $0.stPosition
                )
            }
            return .path(path)

        case .textRun(var run):
            run.glyphs = run.glyphs.map { glyph in
                VVTextGlyph(
                    glyphID: glyph.glyphID,
                    position: CGPoint(x: glyph.position.x + offset.x, y: glyph.position.y + offset.y),
                    size: glyph.size,
                    color: glyph.color,
                    fontVariant: glyph.fontVariant,
                    fontSize: glyph.fontSize,
                    fontName: glyph.fontName,
                    fontDescriptorData: glyph.fontDescriptorData,
                    stringIndex: glyph.stringIndex
                )
            }
            run.lineBounds = run.lineBounds?.offsetBy(dx: offset.x, dy: offset.y)
            run.runBounds = run.runBounds?.offsetBy(dx: offset.x, dy: offset.y)
            run.position = CGPoint(x: run.position.x + offset.x, y: run.position.y + offset.y)
            return .textRun(run)
        }
    }
}
