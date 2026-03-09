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
    private struct PreparedTextRun {
        var glyphBatches: [[MarkdownGlyphInstance]]
        var colorGlyphBatches: [[MarkdownGlyphInstance]]
    }

    private let baseFont: VVFont
    private let baseFontAscent: CGFloat
    private let baseFontDescent: CGFloat
    private var behavior: MarkdownSceneRenderingBehavior
    private var glyphInstances: [[MarkdownGlyphInstance]] = []
    private var colorGlyphInstances: [[MarkdownGlyphInstance]] = []
    private var quadInstances: [QuadInstance] = []
    private var roundedQuadInstances: [QuadInstance] = []
    private var underlines: [LineInstance] = []
    private var strikethroughs: [LineInstance] = []
    private var preparedTextRunCache: [VVTextRunPrimitive: PreparedTextRun] = [:]
    private var preparedTextRunOrder: [VVTextRunPrimitive] = []
    private static let maxPreparedTextRuns = 2048

    public init(baseFont: VVFont, behavior: MarkdownSceneRenderingBehavior = MarkdownSceneRenderingBehavior()) {
        self.baseFont = baseFont
        self.baseFontAscent = CGFloat(CTFontGetAscent(baseFont))
        self.baseFontDescent = CGFloat(CTFontGetDescent(baseFont))
        self.behavior = behavior
    }

    public func updateBehavior(_ behavior: MarkdownSceneRenderingBehavior) {
        self.behavior = behavior
    }

    public func renderScene(
        _ scene: VVScene,
        orderedPrimitives: [VVPrimitive],
        visibleRect: CGRect? = nil,
        visibilityIndex: VVPrimitiveVisibilityIndex? = nil,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        itemOffset: CGPoint = .zero,
        scissorRectForClip: ((CGRect) -> MTLScissorRect)? = nil,
        fullScissorRect: (() -> MTLScissorRect)? = nil
    ) {
        let offset = SIMD2<Float>(Float(itemOffset.x), Float(itemOffset.y))
        var currentClip: CGRect?
        resetScratchBatches()

        func flushTextBatches() {
            if hasPendingTextBatches {
                renderGlyphBatches(glyphInstances, encoder: encoder, renderer: renderer, isColor: false)
                renderGlyphBatches(colorGlyphInstances, encoder: encoder, renderer: renderer, isColor: true)
            }
            if !underlines.isEmpty, let buffer = renderer.makeBuffer(for: underlines) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: underlines.count)
            }
            if !strikethroughs.isEmpty, let buffer = renderer.makeBuffer(for: strikethroughs) {
                renderer.renderStrikethroughs(encoder: encoder, instances: buffer, instanceCount: strikethroughs.count)
            }
            clearTextScratchBatches()
        }

        func flushQuadBatches() {
            if !quadInstances.isEmpty, let buffer = renderer.makeBuffer(for: quadInstances) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: quadInstances.count, rounded: false)
            }
            if !roundedQuadInstances.isEmpty, let buffer = renderer.makeBuffer(for: roundedQuadInstances) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: roundedQuadInstances.count, rounded: true)
            }
            quadInstances.removeAll(keepingCapacity: true)
            roundedQuadInstances.removeAll(keepingCapacity: true)
        }

        func updateClip(_ clip: CGRect?) {
            guard scissorRectForClip != nil || fullScissorRect != nil else { return }
            let offsetClip = clip.map { $0.offsetBy(dx: itemOffset.x, dy: itemOffset.y) }
            guard offsetClip != currentClip else { return }
            flushQuadBatches()
            flushTextBatches()
            if let offsetClip, let scissorRectForClip {
                encoder.setScissorRect(scissorRectForClip(offsetClip))
            } else if let fullScissorRect {
                encoder.setScissorRect(fullScissorRect())
            }
            currentClip = offsetClip
        }

        let visiblePositions = visibleRect.flatMap { rect in
            visibilityIndex?.visiblePositions(in: rect)
        }
        let primitivePositions = visiblePositions ?? Array(orderedPrimitives.indices)

        for position in primitivePositions {
            guard position >= orderedPrimitives.startIndex && position < orderedPrimitives.endIndex else { continue }
            let primitive = orderedPrimitives[position]
            if let visibleRect,
               let bounds = vvPrimitiveVisibilityBounds(primitive),
               !bounds.intersects(visibleRect) {
                continue
            }
            updateClip(primitive.clipRect)
            switch primitive.kind {
            case .textRun(let run):
                flushQuadBatches()
                appendTextPrimitive(
                    run,
                    offset: offset,
                    renderer: renderer,
                    glyphInstances: &glyphInstances,
                    colorGlyphInstances: &colorGlyphInstances,
                    underlines: &underlines,
                    strikethroughs: &strikethroughs
                )
            case .quad(let quad):
                flushTextBatches()
                appendQuadPrimitive(quad, transform: primitive.transform, offset: offset)
            default:
                flushQuadBatches()
                flushTextBatches()
                renderPrimitive(primitive, offset: offset, encoder: encoder, renderer: renderer)
            }
        }

        flushQuadBatches()
        flushTextBatches()
        updateClip(nil)
    }

    public func renderScene(
        _ scene: VVScene,
        orderedPrimitiveIndices: [Int],
        visibleRect: CGRect? = nil,
        visibilityIndex: VVPrimitiveVisibilityIndex? = nil,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        itemOffset: CGPoint = .zero,
        scissorRectForClip: ((CGRect) -> MTLScissorRect)? = nil,
        fullScissorRect: (() -> MTLScissorRect)? = nil
    ) {
        let offset = SIMD2<Float>(Float(itemOffset.x), Float(itemOffset.y))
        var currentClip: CGRect?
        resetScratchBatches()

        func flushTextBatches() {
            if hasPendingTextBatches {
                renderGlyphBatches(glyphInstances, encoder: encoder, renderer: renderer, isColor: false)
                renderGlyphBatches(colorGlyphInstances, encoder: encoder, renderer: renderer, isColor: true)
            }
            if !underlines.isEmpty, let buffer = renderer.makeBuffer(for: underlines) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: underlines.count)
            }
            if !strikethroughs.isEmpty, let buffer = renderer.makeBuffer(for: strikethroughs) {
                renderer.renderStrikethroughs(encoder: encoder, instances: buffer, instanceCount: strikethroughs.count)
            }
            clearTextScratchBatches()
        }

        func flushQuadBatches() {
            if !quadInstances.isEmpty, let buffer = renderer.makeBuffer(for: quadInstances) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: quadInstances.count, rounded: false)
            }
            if !roundedQuadInstances.isEmpty, let buffer = renderer.makeBuffer(for: roundedQuadInstances) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: roundedQuadInstances.count, rounded: true)
            }
            quadInstances.removeAll(keepingCapacity: true)
            roundedQuadInstances.removeAll(keepingCapacity: true)
        }

        func updateClip(_ clip: CGRect?) {
            guard scissorRectForClip != nil || fullScissorRect != nil else { return }
            let offsetClip = clip.map { $0.offsetBy(dx: itemOffset.x, dy: itemOffset.y) }
            guard offsetClip != currentClip else { return }
            flushQuadBatches()
            flushTextBatches()
            if let offsetClip, let scissorRectForClip {
                encoder.setScissorRect(scissorRectForClip(offsetClip))
            } else if let fullScissorRect {
                encoder.setScissorRect(fullScissorRect())
            }
            currentClip = offsetClip
        }

        let primitives = scene.primitives
        func renderPrimitiveAtPosition(_ position: Int) {
            guard position >= orderedPrimitiveIndices.startIndex && position < orderedPrimitiveIndices.endIndex else { return }
            let index = orderedPrimitiveIndices[position]
            guard index >= primitives.startIndex && index < primitives.endIndex else { return }
            let primitive = primitives[index]
            if let visibleRect,
               let bounds = vvPrimitiveVisibilityBounds(primitive),
               !bounds.intersects(visibleRect) {
                return
            }
            updateClip(primitive.clipRect)
            switch primitive.kind {
            case .textRun(let run):
                flushQuadBatches()
                appendTextPrimitive(
                    run,
                    offset: offset,
                    renderer: renderer,
                    glyphInstances: &glyphInstances,
                    colorGlyphInstances: &colorGlyphInstances,
                    underlines: &underlines,
                    strikethroughs: &strikethroughs
                )
            case .quad(let quad):
                flushTextBatches()
                appendQuadPrimitive(quad, transform: primitive.transform, offset: offset)
            default:
                flushQuadBatches()
                flushTextBatches()
                renderPrimitive(primitive, offset: offset, encoder: encoder, renderer: renderer)
            }
        }

        if let visibleRect, let visibilityIndex, let visiblePositions = Optional(visibilityIndex.visiblePositions(in: visibleRect)) {
            for position in visiblePositions {
                renderPrimitiveAtPosition(position)
            }
        } else {
            for position in orderedPrimitiveIndices.indices {
                renderPrimitiveAtPosition(position)
            }
        }

        flushQuadBatches()
        flushTextBatches()
        updateClip(nil)
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
        let previousQuadCount = quadInstances.count
        let previousRoundedCount = roundedQuadInstances.count
        appendQuadPrimitive(quad, transform: transform, offset: offset)

        let newQuads = Array(quadInstances[previousQuadCount...])
        if !newQuads.isEmpty, let buffer = renderer.makeBuffer(for: newQuads) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: newQuads.count, rounded: false)
        }
        quadInstances.removeLast(quadInstances.count - previousQuadCount)

        let newRounded = Array(roundedQuadInstances[previousRoundedCount...])
        if !newRounded.isEmpty, let buffer = renderer.makeBuffer(for: newRounded) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: newRounded.count, rounded: true)
        }
        roundedQuadInstances.removeLast(roundedQuadInstances.count - previousRoundedCount)
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
        glyphInstances: inout [[MarkdownGlyphInstance]],
        colorGlyphInstances: inout [[MarkdownGlyphInstance]],
        underlines: inout [LineInstance],
        strikethroughs: inout [LineInstance]
    ) {
        let prepared = preparedTextRun(for: run, renderer: renderer)
        appendPreparedBatches(prepared.glyphBatches, to: &glyphInstances, offset: offset)
        appendPreparedBatches(prepared.colorGlyphBatches, to: &colorGlyphInstances, offset: offset)

        var glyphMinX = CGFloat.greatestFiniteMagnitude
        var glyphMaxX = -CGFloat.greatestFiniteMagnitude

        for glyph in run.glyphs {
            glyphMinX = min(glyphMinX, glyph.position.x)
            glyphMaxX = max(glyphMaxX, glyph.position.x + glyph.size.width)
        }

        let baseSize = baseFont.pointSize
        let scale = baseSize > 0 ? run.fontSize / baseSize : 1
        let ascent = baseFontAscent * scale
        let descent = baseFontDescent * scale
        if glyphMinX == .greatestFiniteMagnitude {
            glyphMinX = run.position.x
            glyphMaxX = run.position.x
        }
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
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [[MarkdownGlyphInstance]],
        colorGlyphInstances: inout [[MarkdownGlyphInstance]]
    ) {
        guard let cached = cachedGlyph(for: glyph, renderer: renderer) else { return }
        let glyphColor = cached.isColor ? SIMD4<Float>(1, 1, 1, glyph.color.w) : glyph.color
        let instance = MarkdownGlyphInstance(
            position: SIMD2<Float>(
                Float(glyph.position.x + cached.bearing.x),
                Float(glyph.position.y + cached.bearing.y)
            ),
            size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
            uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
            uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
            color: glyphColor,
            atlasIndex: UInt32(cached.atlasIndex)
        )
        if cached.isColor {
            append(instance, toAtlasBatch: cached.atlasIndex, batches: &colorGlyphInstances)
        } else {
            append(instance, toAtlasBatch: cached.atlasIndex, batches: &glyphInstances)
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
        _ batches: [[MarkdownGlyphInstance]],
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        isColor: Bool
    ) {
        let textures = isColor ? renderer.glyphAtlas.allColorAtlasTextures : renderer.glyphAtlas.allAtlasTextures
        let limit = min(batches.count, textures.count)
        guard limit > 0 else { return }

        for atlasIndex in 0..<limit {
            let instances = batches[atlasIndex]
            guard !instances.isEmpty, let buffer = renderer.makeBuffer(for: instances) else { continue }
            if isColor {
                renderer.renderColorGlyphs(
                    encoder: encoder,
                    instances: buffer,
                    instanceCount: instances.count,
                    texture: textures[atlasIndex]
                )
            } else {
                renderer.renderGlyphs(
                    encoder: encoder,
                    instances: buffer,
                    instanceCount: instances.count,
                    texture: textures[atlasIndex]
                )
            }
        }
    }

    private var hasPendingTextBatches: Bool {
        !underlines.isEmpty ||
        !strikethroughs.isEmpty ||
        glyphInstances.contains(where: { !$0.isEmpty }) ||
        colorGlyphInstances.contains(where: { !$0.isEmpty })
    }

    private func resetScratchBatches() {
        quadInstances.removeAll(keepingCapacity: true)
        roundedQuadInstances.removeAll(keepingCapacity: true)
        clearTextScratchBatches()
    }

    private func clearTextScratchBatches() {
        clearGlyphBatches(&glyphInstances)
        clearGlyphBatches(&colorGlyphInstances)
        underlines.removeAll(keepingCapacity: true)
        strikethroughs.removeAll(keepingCapacity: true)
    }

    private func clearGlyphBatches(_ batches: inout [[MarkdownGlyphInstance]]) {
        for index in batches.indices {
            batches[index].removeAll(keepingCapacity: true)
        }
    }

    private func append(
        _ instance: MarkdownGlyphInstance,
        toAtlasBatch atlasIndex: Int,
        batches: inout [[MarkdownGlyphInstance]]
    ) {
        guard atlasIndex >= 0 else { return }
        if batches.count <= atlasIndex {
            batches.append(contentsOf: repeatElement([], count: atlasIndex - batches.count + 1))
        }
        batches[atlasIndex].append(instance)
    }

    private func appendPreparedBatches(
        _ prepared: [[MarkdownGlyphInstance]],
        to batches: inout [[MarkdownGlyphInstance]],
        offset: SIMD2<Float>
    ) {
        guard !prepared.isEmpty else { return }
        if batches.count < prepared.count {
            batches.append(contentsOf: repeatElement([], count: prepared.count - batches.count))
        }

        if offset == .zero {
            for index in prepared.indices where !prepared[index].isEmpty {
                batches[index].append(contentsOf: prepared[index])
            }
            return
        }

        for index in prepared.indices where !prepared[index].isEmpty {
            for instance in prepared[index] {
                batches[index].append(
                    MarkdownGlyphInstance(
                        position: SIMD2<Float>(instance.position.x + offset.x, instance.position.y + offset.y),
                        size: instance.size,
                        uvOrigin: instance.uvOrigin,
                        uvSize: instance.uvSize,
                        color: instance.color,
                        atlasIndex: instance.atlasIndex
                    )
                )
            }
        }
    }

    private func preparedTextRun(
        for run: VVTextRunPrimitive,
        renderer: MarkdownMetalRenderer
    ) -> PreparedTextRun {
        if let cached = preparedTextRunCache[run] {
            touchPreparedTextRun(run)
            return cached
        }

        var glyphBatches: [[MarkdownGlyphInstance]] = []
        var colorGlyphBatches: [[MarkdownGlyphInstance]] = []
        glyphBatches.reserveCapacity(2)
        colorGlyphBatches.reserveCapacity(1)

        for glyph in run.glyphs {
            appendGlyphInstance(
                glyph,
                renderer: renderer,
                glyphInstances: &glyphBatches,
                colorGlyphInstances: &colorGlyphBatches
            )
        }

        let prepared = PreparedTextRun(
            glyphBatches: glyphBatches,
            colorGlyphBatches: colorGlyphBatches
        )
        preparedTextRunCache[run] = prepared
        touchPreparedTextRun(run)
        while preparedTextRunOrder.count > Self.maxPreparedTextRuns {
            let evicted = preparedTextRunOrder.removeFirst()
            preparedTextRunCache.removeValue(forKey: evicted)
        }
        return prepared
    }

    private func touchPreparedTextRun(_ run: VVTextRunPrimitive) {
        preparedTextRunOrder.removeAll { $0 == run }
        preparedTextRunOrder.append(run)
    }

    private func appendQuadPrimitive(
        _ quad: VVQuadPrimitive,
        transform: VVTransform2D?,
        offset: SIMD2<Float>
    ) {
        let frame = transformed(rect: quad.frame, by: transform)
        guard frame.width > 0, frame.height > 0 else { return }

        let instance = QuadInstance(
            position: SIMD2<Float>(Float(frame.origin.x) + offset.x, Float(frame.origin.y) + offset.y),
            size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
            color: SIMD4<Float>(quad.color.x, quad.color.y, quad.color.z, quad.color.w * quad.opacity),
            cornerRadius: Float(quad.cornerRadius)
        )
        if quad.cornerRadius > 0 {
            roundedQuadInstances.append(instance)
        } else {
            quadInstances.append(instance)
        }

        guard let border = quad.border else { return }
        if canRenderBorderAsSingleRing(border) {
            roundedQuadInstances.append(
                QuadInstance(
                    position: SIMD2<Float>(Float(frame.origin.x) + offset.x, Float(frame.origin.y) + offset.y),
                    size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
                    color: border.color,
                    cornerRadius: Float(quad.cornerRadius),
                    borderWidth: Float(border.widths.top)
                )
            )
            return
        }
        quadInstances.append(contentsOf: borderSegments(for: frame, border: border, offset: offset))
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
