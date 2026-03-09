import CoreGraphics
import CoreText
import Foundation
import Metal
import VVMetalPrimitives

public struct MarkdownSceneRenderingBehavior {
    public enum MissingImageBehavior {
        case skip
        case drawPlaceholder
    }

    public var imageTextureProvider: ((String) -> MTLTexture?)?
    public var shouldUnderlineLinkRun: (VVTextRunPrimitive) -> Bool
    public var missingImageBehavior: MissingImageBehavior

    public init(
        imageTextureProvider: ((String) -> MTLTexture?)? = nil,
        shouldUnderlineLinkRun: @escaping (VVTextRunPrimitive) -> Bool = { $0.style.isLink },
        missingImageBehavior: MissingImageBehavior = .drawPlaceholder
    ) {
        self.imageTextureProvider = imageTextureProvider
        self.shouldUnderlineLinkRun = shouldUnderlineLinkRun
        self.missingImageBehavior = missingImageBehavior
    }
}

public final class MarkdownScenePrimitiveRenderer {
    private let baseFont: VVFont
    private let baseFontAscent: CGFloat
    private let baseFontDescent: CGFloat
    private let behavior: MarkdownSceneRenderingBehavior

    public init(baseFont: VVFont, behavior: MarkdownSceneRenderingBehavior = MarkdownSceneRenderingBehavior()) {
        self.baseFont = baseFont
        self.baseFontAscent = CGFloat(CTFontGetAscent(baseFont))
        self.baseFontDescent = CGFloat(CTFontGetDescent(baseFont))
        self.behavior = behavior
    }

    public func renderScene(
        _ scene: VVScene,
        orderedPrimitives: [VVPrimitive],
        visibleRect: CGRect? = nil,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        itemOffset: CGPoint = .zero,
        scissorRectForClip: ((CGRect) -> MTLScissorRect)? = nil,
        fullScissorRect: (() -> MTLScissorRect)? = nil
    ) {
        let offset = SIMD2<Float>(Float(itemOffset.x), Float(itemOffset.y))
        var currentClip: CGRect?
        var glyphInstances: [Int: [MarkdownGlyphInstance]] = [:]
        var colorGlyphInstances: [Int: [MarkdownGlyphInstance]] = [:]
        var underlines: [LineInstance] = []
        var strikethroughs: [LineInstance] = []

        func flushTextBatches() {
            if !glyphInstances.isEmpty || !colorGlyphInstances.isEmpty {
                renderGlyphBatches(glyphInstances, encoder: encoder, renderer: renderer, isColor: false)
                renderGlyphBatches(colorGlyphInstances, encoder: encoder, renderer: renderer, isColor: true)
            }
            if !underlines.isEmpty, let buffer = renderer.makeBuffer(for: underlines) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: underlines.count)
            }
            if !strikethroughs.isEmpty, let buffer = renderer.makeBuffer(for: strikethroughs) {
                renderer.renderStrikethroughs(encoder: encoder, instances: buffer, instanceCount: strikethroughs.count)
            }
            glyphInstances.removeAll(keepingCapacity: true)
            colorGlyphInstances.removeAll(keepingCapacity: true)
            underlines.removeAll(keepingCapacity: true)
            strikethroughs.removeAll(keepingCapacity: true)
        }

        func updateClip(_ clip: CGRect?) {
            guard scissorRectForClip != nil || fullScissorRect != nil else { return }
            let offsetClip = clip.map { $0.offsetBy(dx: itemOffset.x, dy: itemOffset.y) }
            guard offsetClip != currentClip else { return }
            flushTextBatches()
            if let offsetClip, let scissorRectForClip {
                encoder.setScissorRect(scissorRectForClip(offsetClip))
            } else if let fullScissorRect {
                encoder.setScissorRect(fullScissorRect())
            }
            currentClip = offsetClip
        }

        for primitive in orderedPrimitives {
            if let visibleRect,
               let bounds = primitiveVisibilityBounds(primitive),
               !bounds.intersects(visibleRect) {
                continue
            }
            updateClip(primitive.clipRect)
            switch primitive.kind {
            case .textRun(let run):
                appendTextPrimitive(
                    run,
                    offset: offset,
                    renderer: renderer,
                    glyphInstances: &glyphInstances,
                    colorGlyphInstances: &colorGlyphInstances,
                    underlines: &underlines,
                    strikethroughs: &strikethroughs
                )
            default:
                flushTextBatches()
                renderPrimitive(primitive, offset: offset, encoder: encoder, renderer: renderer)
            }
        }

        flushTextBatches()
        updateClip(nil)
    }

    public func primitiveVisibilityBounds(_ primitive: VVPrimitive) -> CGRect? {
        if let clipRect = primitive.clipRect, !clipRect.isNull, !clipRect.isEmpty {
            return clipRect
        }

        switch primitive.kind {
        case .textRun(let run):
            let baseBounds = run.lineBounds ?? run.runBounds ?? glyphBounds(for: run.glyphs)
            return baseBounds.map { transformed(rect: $0, by: primitive.transform) }
        case .quad(let quad):
            return transformed(rect: quad.frame, by: primitive.transform)
        case .gradientQuad(let quad):
            return transformed(rect: quad.frame, by: primitive.transform)
        case .line(let line):
            let minX = min(line.start.x, line.end.x)
            let minY = min(line.start.y, line.end.y)
            return transformed(
                rect: CGRect(
                    x: minX - line.thickness * 0.5,
                    y: minY - line.thickness * 0.5,
                    width: abs(line.end.x - line.start.x) + line.thickness,
                    height: abs(line.end.y - line.start.y) + line.thickness
                ),
                by: primitive.transform
            )
        case .underline(let underline):
            return transformed(
                rect: CGRect(
                    x: underline.origin.x,
                    y: underline.origin.y,
                    width: underline.width,
                    height: max(underline.thickness, 1)
                ),
                by: primitive.transform
            )
        case .bullet(let bullet):
            return transformed(
                rect: CGRect(x: bullet.position.x, y: bullet.position.y, width: bullet.size, height: bullet.size),
                by: primitive.transform
            )
        case .image(let image):
            return transformed(rect: image.frame, by: primitive.transform)
        case .blockQuoteBorder(let border):
            return transformed(rect: border.frame, by: primitive.transform)
        case .tableLine(let line):
            let minX = min(line.start.x, line.end.x)
            let minY = min(line.start.y, line.end.y)
            return transformed(
                rect: CGRect(
                    x: minX - line.lineWidth * 0.5,
                    y: minY - line.lineWidth * 0.5,
                    width: abs(line.end.x - line.start.x) + line.lineWidth,
                    height: abs(line.end.y - line.start.y) + line.lineWidth
                ),
                by: primitive.transform
            )
        case .pieSlice(let slice):
            return transformed(
                rect: CGRect(
                    x: slice.center.x - slice.radius,
                    y: slice.center.y - slice.radius,
                    width: slice.radius * 2,
                    height: slice.radius * 2
                ),
                by: primitive.transform
            )
        case .path(let path):
            let pathBounds = transformed(rect: path.bounds, by: path.transform)
            return transformed(rect: pathBounds, by: primitive.transform)
        }
    }

    private func renderPrimitive(
        _ primitive: VVPrimitive,
        offset: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let transform = primitive.transform
        switch primitive.kind {
        case .quad(let quad):
            renderQuadPrimitive(quad, transform: transform, offset: offset, encoder: encoder, renderer: renderer)
        case .gradientQuad(let quad):
            renderGradientQuad(quad, transform: transform, offset: offset, encoder: encoder, renderer: renderer)
        case .line(let line):
            renderLinePrimitive(line, transform: transform, offset: offset, encoder: encoder, renderer: renderer)
        case .bullet(let bullet):
            renderBulletPrimitive(bullet, offset: offset, encoder: encoder, renderer: renderer)
        case .image(let image):
            renderImagePrimitive(image, transform: transform, offset: offset, encoder: encoder, renderer: renderer)
        case .blockQuoteBorder(let border):
            let instance = BlockQuoteBorderInstance(
                position: SIMD2<Float>(Float(border.frame.origin.x) + offset.x, Float(border.frame.origin.y) + offset.y),
                size: SIMD2<Float>(Float(border.frame.width), Float(border.frame.height)),
                color: border.color,
                borderWidth: Float(border.borderWidth)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderBlockQuoteBorders(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .tableLine(let line):
            let instance = TableGridLineInstance(
                start: SIMD2<Float>(Float(line.start.x) + offset.x, Float(line.start.y) + offset.y),
                end: SIMD2<Float>(Float(line.end.x) + offset.x, Float(line.end.y) + offset.y),
                color: line.color,
                lineWidth: Float(line.lineWidth)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderTableGrid(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .pieSlice(let slice):
            let instance = PieSliceInstance(
                center: SIMD2<Float>(Float(slice.center.x) + offset.x, Float(slice.center.y) + offset.y),
                radius: Float(slice.radius),
                startAngle: Float(slice.startAngle),
                endAngle: Float(slice.endAngle),
                color: slice.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderPieSlices(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .underline(let underline):
            let transformedOrigin = transformed(point: underline.origin, by: transform)
            let transformedWidth = transformed(size: CGSize(width: underline.width, height: underline.thickness), by: transform)
            let instance = LineInstance(
                position: SIMD2<Float>(Float(transformedOrigin.x) + offset.x, Float(transformedOrigin.y) + offset.y),
                width: Float(max(1, transformedWidth.width)),
                height: Float(max(underline.thickness, transformedWidth.height)),
                color: underline.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .path(let path):
            renderPathPrimitive(path, inheritedTransform: transform, offset: offset, encoder: encoder, renderer: renderer)
        case .textRun:
            break
        }
    }

    private func renderBulletPrimitive(
        _ bullet: VVBulletPrimitive,
        offset: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        switch bullet.type {
        case .disc, .circle, .square:
            let bulletType: UInt32
            switch bullet.type {
            case .disc: bulletType = 0
            case .circle: bulletType = 1
            case .square: bulletType = 2
            default: bulletType = 0
            }
            let instance = BulletInstance(
                position: SIMD2<Float>(Float(bullet.position.x) + offset.x, Float(bullet.position.y) + offset.y),
                size: SIMD2<Float>(Float(bullet.size), Float(bullet.size)),
                color: bullet.color,
                bulletType: bulletType
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderBullets(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .checkbox(let checked):
            let instance = CheckboxInstance(
                position: SIMD2<Float>(Float(bullet.position.x) + offset.x, Float(bullet.position.y) + offset.y),
                size: SIMD2<Float>(Float(bullet.size), Float(bullet.size)),
                color: bullet.color,
                isChecked: checked
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderCheckboxes(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .number:
            break
        }
    }

    private func renderGradientQuad(
        _ gradient: VVGradientQuadPrimitive,
        transform: VVTransform2D? = nil,
        offset: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let transformedFrame = transformed(rect: gradient.frame, by: transform)
        let frame = transformedFrame.offsetBy(dx: CGFloat(offset.x), dy: CGFloat(offset.y)).integral
        guard frame.width > 0, frame.height > 0 else { return }
        let axis: SIMD2<Float>
        if let angle = gradient.angle {
            axis = SIMD2<Float>(Float(cos(angle)), Float(sin(angle)))
        } else {
            switch gradient.direction {
            case .horizontal: axis = SIMD2<Float>(1, 0)
            case .vertical: axis = SIMD2<Float>(0, 1)
            }
        }
        let instance = GradientQuadInstance(
            position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
            size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
            startColor: gradient.startColor,
            endColor: gradient.endColor,
            axis: axis,
            cornerRadius: Float(gradient.cornerRadius)
        )
        guard let buffer = renderer.makeBuffer(for: [instance]) else { return }
        renderer.renderGradientQuads(encoder: encoder, instances: buffer, instanceCount: 1)
    }

    private func renderQuadPrimitive(
        _ quad: VVQuadPrimitive,
        transform: VVTransform2D?,
        offset: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let frame = transformed(rect: quad.frame, by: transform)
        guard frame.width > 0, frame.height > 0 else { return }

        let instance = QuadInstance(
            position: SIMD2<Float>(Float(frame.origin.x) + offset.x, Float(frame.origin.y) + offset.y),
            size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
            color: SIMD4<Float>(quad.color.x, quad.color.y, quad.color.z, quad.color.w * quad.opacity),
            cornerRadius: Float(quad.cornerRadius)
        )
        if let buffer = renderer.makeBuffer(for: [instance]) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: quad.cornerRadius > 0)
        }

        guard let border = quad.border else { return }
        if canRenderBorderAsSingleRing(border) {
            let borderInstance = QuadInstance(
                position: SIMD2<Float>(Float(frame.origin.x) + offset.x, Float(frame.origin.y) + offset.y),
                size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
                color: border.color,
                cornerRadius: Float(quad.cornerRadius),
                borderWidth: Float(border.widths.top)
            )
            if let buffer = renderer.makeBuffer(for: [borderInstance]) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: true)
            }
            return
        }
        let segments = borderSegments(for: frame, border: border, offset: offset)
        guard !segments.isEmpty, let buffer = renderer.makeBuffer(for: segments) else { return }
        renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: segments.count, rounded: false)
    }

    private func renderLinePrimitive(
        _ line: VVLinePrimitive,
        transform: VVTransform2D?,
        offset: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let transformedStart = transformed(point: line.start, by: transform)
        let transformedEnd = transformed(point: line.end, by: transform)
        let segments = dashedSegments(
            for: VVLinePrimitive(
                start: transformedStart,
                end: transformedEnd,
                thickness: line.thickness,
                color: line.color,
                dash: line.dash
            )
        )

        let instances = segments.map { segment in
            let minX = min(segment.start.x, segment.end.x)
            let minY = min(segment.start.y, segment.end.y)
            let width = abs(segment.end.x - segment.start.x)
            let height = abs(segment.end.y - segment.start.y)
            return LineInstance(
                position: SIMD2<Float>(Float(minX) + offset.x, Float(minY) + offset.y),
                width: Float(width > 0 ? width : segment.thickness),
                height: Float(height > 0 ? height : segment.thickness),
                color: segment.color
            )
        }

        if let buffer = renderer.makeBuffer(for: instances) {
            renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: instances.count)
        }
    }

    private func renderImagePrimitive(
        _ image: VVImagePrimitive,
        transform: VVTransform2D?,
        offset: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let frame = transformed(rect: image.frame, by: transform)
        if let texture = behavior.imageTextureProvider?(image.url) {
            let instance = ImageRenderInstance(
                position: SIMD2<Float>(Float(frame.origin.x) + offset.x, Float(frame.origin.y) + offset.y),
                size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
                cornerRadius: Float(image.cornerRadius),
                opacity: image.opacity,
                grayscale: image.grayscale
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderImages(encoder: encoder, instances: buffer, instanceCount: 1, texture: texture)
            }
            return
        }

        guard behavior.missingImageBehavior == .drawPlaceholder else { return }
        let border = QuadInstance(
            position: SIMD2<Float>(Float(frame.origin.x) + offset.x, Float(frame.origin.y) + offset.y),
            size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
            color: .gray(0.35),
            cornerRadius: Float(image.cornerRadius)
        )
        let innerFrame = frame.insetBy(dx: 1, dy: 1)
        let fill = QuadInstance(
            position: SIMD2<Float>(Float(innerFrame.origin.x) + offset.x, Float(innerFrame.origin.y) + offset.y),
            size: SIMD2<Float>(Float(innerFrame.width), Float(innerFrame.height)),
            color: .gray(0.12),
            cornerRadius: Float(max(0, image.cornerRadius - 1))
        )
        if let buffer = renderer.makeBuffer(for: [border, fill]) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 2, rounded: true)
        }
    }

    private func renderPathPrimitive(
        _ path: VVPathPrimitive,
        inheritedTransform: VVTransform2D?,
        offset: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let combinedTransform: VVTransform2D
        switch (inheritedTransform, path.transform.isIdentity ? nil : path.transform) {
        case let (lhs?, rhs?):
            combinedTransform = lhs.composed(with: rhs)
        case let (lhs?, nil):
            combinedTransform = lhs
        case let (nil, rhs?):
            combinedTransform = rhs
        case (nil, nil):
            combinedTransform = .identity
        }

        let vertices = path.vertices.map { vertex in
            let transformedPosition = transformed(point: vertex.position, by: combinedTransform)
            return PathRenderVertex(
                position: SIMD2<Float>(Float(transformedPosition.x) + offset.x, Float(transformedPosition.y) + offset.y),
                stPosition: SIMD2<Float>(Float(vertex.stPosition.x), Float(vertex.stPosition.y))
            )
        }
        guard let buffer = renderer.makeBuffer(for: vertices) else { return }

        if let fill = path.fill, path.fillVertexCount > 0 {
            renderer.renderPath(encoder: encoder, vertices: buffer, vertexStart: 0, vertexCount: path.fillVertexCount, color: fill)
        }
        if let stroke = path.stroke, path.strokeVertexCount > 0 {
            renderer.renderPath(
                encoder: encoder,
                vertices: buffer,
                vertexStart: path.fillVertexCount,
                vertexCount: path.strokeVertexCount,
                color: stroke.color
            )
        }
    }

    private func appendTextPrimitive(
        _ run: VVTextRunPrimitive,
        offset: SIMD2<Float>,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]],
        underlines: inout [LineInstance],
        strikethroughs: inout [LineInstance]
    ) {
        for glyph in run.glyphs {
            appendGlyphInstance(
                glyph,
                offset: offset,
                renderer: renderer,
                glyphInstances: &glyphInstances,
                colorGlyphInstances: &colorGlyphInstances
            )
        }

        let baseSize = baseFont.pointSize
        let scale = baseSize > 0 ? run.fontSize / baseSize : 1
        let ascent = baseFontAscent * scale
        let descent = baseFontDescent * scale
        let glyphMinX = run.glyphs.map(\.position.x).min() ?? run.position.x
        let glyphMaxX = run.glyphs.map { $0.position.x + $0.size.width }.max() ?? run.position.x
        let fallbackBounds = run.runBounds ?? run.lineBounds
        let underlineStartX = fallbackBounds?.minX ?? glyphMinX
        let underlineWidth = max(0, fallbackBounds?.width ?? (glyphMaxX - glyphMinX))

        if behavior.shouldUnderlineLinkRun(run) {
            let underlineY = run.position.y + max(1, descent * 0.6)
            underlines.append(
                LineInstance(
                    position: SIMD2<Float>(Float(underlineStartX) + offset.x, Float(underlineY) + offset.y),
                    width: Float(underlineWidth),
                    height: 1,
                    color: run.style.color
                )
            )
        }

        if run.style.isStrikethrough {
            let strikeY = run.position.y - max(1, ascent * 0.35)
            strikethroughs.append(
                LineInstance(
                    position: SIMD2<Float>(Float(underlineStartX) + offset.x, Float(strikeY) + offset.y),
                    width: Float(underlineWidth),
                    height: 1,
                    color: run.style.color
                )
            )
        }
    }

    private func appendGlyphInstance(
        _ glyph: VVTextGlyph,
        offset: SIMD2<Float>,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]]
    ) {
        guard let cached = cachedGlyph(for: glyph, renderer: renderer) else { return }
        let glyphColor = cached.isColor ? SIMD4<Float>(1, 1, 1, glyph.color.w) : glyph.color
        let instance = MarkdownGlyphInstance(
            position: SIMD2<Float>(
                Float(glyph.position.x + cached.bearing.x) + offset.x,
                Float(glyph.position.y + cached.bearing.y) + offset.y
            ),
            size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
            uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
            uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
            color: glyphColor,
            atlasIndex: UInt32(cached.atlasIndex)
        )
        if cached.isColor {
            colorGlyphInstances[cached.atlasIndex, default: []].append(instance)
        } else {
            glyphInstances[cached.atlasIndex, default: []].append(instance)
        }
    }

    private func cachedGlyph(for glyph: VVTextGlyph, renderer: MarkdownMetalRenderer) -> MarkdownCachedGlyph? {
        let layoutVariant: FontVariant
        switch glyph.fontVariant {
        case .regular: layoutVariant = .regular
        case .semibold: layoutVariant = .semibold
        case .semiboldItalic: layoutVariant = .semiboldItalic
        case .bold: layoutVariant = .bold
        case .italic: layoutVariant = .italic
        case .boldItalic: layoutVariant = .boldItalic
        case .monospace: layoutVariant = .monospace
        case .emoji: layoutVariant = .emoji
        }
        let cgGlyph = CGGlyph(glyph.glyphID)
        if let fontName = glyph.fontName {
            return renderer.glyphAtlas.glyph(for: cgGlyph, fontName: fontName, fontSize: glyph.fontSize, variant: layoutVariant)
        }
        return renderer.glyphAtlas.glyph(for: cgGlyph, variant: layoutVariant, fontSize: glyph.fontSize, baseFont: renderer.baseFont)
    }

    private func renderGlyphBatches(
        _ batches: [Int: [MarkdownGlyphInstance]],
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        isColor: Bool
    ) {
        let textures = isColor ? renderer.glyphAtlas.allColorAtlasTextures : renderer.glyphAtlas.allAtlasTextures
        for atlasIndex in batches.keys.sorted() {
            guard atlasIndex >= 0 && atlasIndex < textures.count,
                  let instances = batches[atlasIndex],
                  let buffer = renderer.makeBuffer(for: instances) else { continue }
            renderer.renderGlyphs(
                encoder: encoder,
                instances: buffer,
                instanceCount: instances.count,
                texture: textures[atlasIndex]
            )
        }
    }

    private func glyphBounds(for glyphs: [VVTextGlyph]) -> CGRect? {
        guard let first = glyphs.first else { return nil }
        var minX = first.position.x
        var minY = first.position.y
        var maxX = first.position.x + first.size.width
        var maxY = first.position.y + first.size.height

        for glyph in glyphs.dropFirst() {
            minX = min(minX, glyph.position.x)
            minY = min(minY, glyph.position.y)
            maxX = max(maxX, glyph.position.x + glyph.size.width)
            maxY = max(maxY, glyph.position.y + glyph.size.height)
        }

        return CGRect(x: minX, y: minY, width: max(1, maxX - minX), height: max(1, maxY - minY))
    }

    private func transformed(rect: CGRect, by transform: VVTransform2D?) -> CGRect {
        guard let transform, !transform.isIdentity else { return rect }
        let corners = [
            rect.origin,
            CGPoint(x: rect.maxX, y: rect.minY),
            CGPoint(x: rect.maxX, y: rect.maxY),
            CGPoint(x: rect.minX, y: rect.maxY)
        ].map { transform.apply(to: $0) }
        let xs = corners.map(\.x)
        let ys = corners.map(\.y)
        return CGRect(
            x: xs.min() ?? rect.minX,
            y: ys.min() ?? rect.minY,
            width: (xs.max() ?? rect.maxX) - (xs.min() ?? rect.minX),
            height: (ys.max() ?? rect.maxY) - (ys.min() ?? rect.minY)
        )
    }

    private func transformed(point: CGPoint, by transform: VVTransform2D?) -> CGPoint {
        guard let transform, !transform.isIdentity else { return point }
        return transform.apply(to: point)
    }

    private func transformed(size: CGSize, by transform: VVTransform2D?) -> CGSize {
        guard let transform, !transform.isIdentity else { return size }
        return transformed(rect: CGRect(origin: .zero, size: size), by: transform).size
    }

    private func dashedSegments(for line: VVLinePrimitive) -> [VVLinePrimitive] {
        switch line.dash {
        case .solid:
            return [line]
        case .dashed(let on, let off):
            return patternedSegments(for: line, pattern: [on, off])
        case .pattern(let values):
            return patternedSegments(for: line, pattern: values)
        }
    }

    private func patternedSegments(for line: VVLinePrimitive, pattern: [CGFloat]) -> [VVLinePrimitive] {
        let cleanedPattern = pattern.filter { $0 > 0 }
        guard cleanedPattern.count >= 2 else { return [line] }

        let dx = line.end.x - line.start.x
        let dy = line.end.y - line.start.y
        let length = hypot(dx, dy)
        guard length > 0 else { return [line] }

        let ux = dx / length
        let uy = dy / length
        var distance: CGFloat = 0
        var patternIndex = 0
        var draw = true
        var segments: [VVLinePrimitive] = []

        while distance < length {
            let segmentLength = min(cleanedPattern[patternIndex % cleanedPattern.count], length - distance)
            let start = CGPoint(x: line.start.x + ux * distance, y: line.start.y + uy * distance)
            let end = CGPoint(x: line.start.x + ux * (distance + segmentLength), y: line.start.y + uy * (distance + segmentLength))
            if draw {
                segments.append(VVLinePrimitive(start: start, end: end, thickness: line.thickness, color: line.color))
            }
            distance += segmentLength
            patternIndex += 1
            draw.toggle()
        }

        return segments
    }

    private func canRenderBorderAsSingleRing(_ border: VVBorder) -> Bool {
        guard case .solid = border.style else { return false }
        let widths = border.widths
        return widths.top > 0 &&
            abs(widths.top - widths.right) < 0.001 &&
            abs(widths.top - widths.bottom) < 0.001 &&
            abs(widths.top - widths.left) < 0.001
    }

    private func borderSegments(
        for frame: CGRect,
        border: VVBorder,
        offset: SIMD2<Float>
    ) -> [QuadInstance] {
        let widths = border.widths
        let color = border.color
        var segments: [QuadInstance] = []

        func append(rect: CGRect) {
            guard rect.width > 0, rect.height > 0 else { return }
            segments.append(
                QuadInstance(
                    position: SIMD2<Float>(Float(rect.origin.x) + offset.x, Float(rect.origin.y) + offset.y),
                    size: SIMD2<Float>(Float(rect.width), Float(rect.height)),
                    color: color,
                    cornerRadius: 0
                )
            )
        }

        switch border.style {
        case .solid:
            append(rect: CGRect(x: frame.minX, y: frame.minY, width: frame.width, height: widths.top))
            append(rect: CGRect(x: frame.minX, y: frame.maxY - widths.bottom, width: frame.width, height: widths.bottom))
            append(rect: CGRect(x: frame.minX, y: frame.minY + widths.top, width: widths.left, height: max(0, frame.height - widths.top - widths.bottom)))
            append(rect: CGRect(x: frame.maxX - widths.right, y: frame.minY + widths.top, width: widths.right, height: max(0, frame.height - widths.top - widths.bottom)))
        case .dashed(let dashLength, let gapLength):
            let edges = [
                VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.minY), end: CGPoint(x: frame.maxX, y: frame.minY), thickness: max(1, widths.top), color: color, dash: .dashed(on: dashLength, off: gapLength)),
                VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.maxY), end: CGPoint(x: frame.maxX, y: frame.maxY), thickness: max(1, widths.bottom), color: color, dash: .dashed(on: dashLength, off: gapLength)),
                VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.minY), end: CGPoint(x: frame.minX, y: frame.maxY), thickness: max(1, widths.left), color: color, dash: .dashed(on: dashLength, off: gapLength)),
                VVLinePrimitive(start: CGPoint(x: frame.maxX, y: frame.minY), end: CGPoint(x: frame.maxX, y: frame.maxY), thickness: max(1, widths.right), color: color, dash: .dashed(on: dashLength, off: gapLength))
            ]
            for edge in edges {
                for segment in dashedSegments(for: edge) {
                    let minX = min(segment.start.x, segment.end.x)
                    let minY = min(segment.start.y, segment.end.y)
                    let width = abs(segment.end.x - segment.start.x)
                    let height = abs(segment.end.y - segment.start.y)
                    append(
                        rect: CGRect(
                            x: minX,
                            y: minY,
                            width: width > 0 ? width : segment.thickness,
                            height: height > 0 ? height : segment.thickness
                        )
                    )
                }
            }
        }

        return segments
    }
}
