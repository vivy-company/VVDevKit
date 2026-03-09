import CoreGraphics
import CoreText
import Metal
import XCTest
@testable import VVMarkdown
import VVMetalPrimitives

final class HeadlessSceneStressHarness {
    private let renderer: MarkdownMetalRenderer
    private let sceneRenderer: MarkdownScenePrimitiveRenderer
    private let viewportSize: CGSize
    private var cachedSceneKey: SceneCacheKey?
    private var cachedOrderedPrimitiveIndices: [Int] = []
    private var cachedVisibilityIndex: VVPrimitiveVisibilityIndex?

    init(baseFont: VVFont, viewportSize: CGSize) throws {
        guard let device = MTLCreateSystemDefaultDevice() else {
            throw XCTSkip("Metal is unavailable on this machine")
        }
        let context = try VVMetalContext(device: device)
        self.renderer = MarkdownMetalRenderer(context: context, baseFont: baseFont, scaleFactor: 2.0)
        self.sceneRenderer = MarkdownScenePrimitiveRenderer(baseFont: baseFont)
        self.viewportSize = viewportSize
    }

    var pooledBufferBytes: Int {
        renderer.context.pooledBufferBytes
    }

    var pooledBufferCount: Int {
        renderer.context.pooledBufferCount
    }

    @discardableResult
    func render(
        scene: VVScene,
        scrollOffset: CGPoint = .zero,
        visiblePadding: CGFloat = 512
    ) throws -> MTLTexture {
        let texture = try makeTexture()
        guard let commandBuffer = renderer.commandQueue.makeCommandBuffer() else {
            XCTFail("Failed to create command buffer")
            throw CancellationError()
        }
        commandBuffer.label = "VVRenderingStressTests.CommandBuffer"

        let descriptor = MTLRenderPassDescriptor()
        descriptor.colorAttachments[0].texture = texture
        descriptor.colorAttachments[0].loadAction = .clear
        descriptor.colorAttachments[0].storeAction = .store
        descriptor.colorAttachments[0].clearColor = MTLClearColor(red: 0.06, green: 0.06, blue: 0.08, alpha: 1)

        guard let encoder = commandBuffer.makeRenderCommandEncoder(descriptor: descriptor) else {
            XCTFail("Failed to create render encoder")
            throw CancellationError()
        }
        encoder.label = "VVRenderingStressTests.RenderEncoder"

        renderer.beginFrame(viewportSize: viewportSize, scrollOffset: scrollOffset)

        let visibleRect = CGRect(
            x: scrollOffset.x - visiblePadding,
            y: scrollOffset.y - visiblePadding,
            width: viewportSize.width + visiblePadding * 2,
            height: viewportSize.height + visiblePadding * 2
        )
        render(scene: scene, visibleRect: visibleRect, encoder: encoder)

        encoder.endEncoding()
        renderer.recycleTransientBuffers(after: commandBuffer)
        commandBuffer.commit()
        commandBuffer.waitUntilCompleted()

        if commandBuffer.status != .completed {
            XCTFail("Headless render failed with status \(commandBuffer.status.rawValue)")
        }
        return texture
    }

    private func makeTexture() throws -> MTLTexture {
        let width = max(1, Int(ceil(viewportSize.width)))
        let height = max(1, Int(ceil(viewportSize.height)))
        let descriptor = MTLTextureDescriptor.texture2DDescriptor(
            pixelFormat: .bgra8Unorm,
            width: width,
            height: height,
            mipmapped: false
        )
        descriptor.usage = [.renderTarget, .shaderRead]
        guard let texture = renderer.device.makeTexture(descriptor: descriptor) else {
            XCTFail("Failed to create offscreen texture")
            throw CancellationError()
        }
        return texture
    }

    private func render(scene: VVScene, visibleRect: CGRect, encoder: MTLRenderCommandEncoder) {
        refreshSceneCachesIfNeeded(for: scene)
        sceneRenderer.renderScene(
            scene,
            orderedPrimitiveIndices: cachedOrderedPrimitiveIndices,
            visibleRect: visibleRect,
            visibilityIndex: cachedVisibilityIndex,
            encoder: encoder,
            renderer: renderer
        )
    }

    private func refreshSceneCachesIfNeeded(for scene: VVScene) {
        let sceneKey = SceneCacheKey(scene: scene)
        guard sceneKey != cachedSceneKey else { return }
        let orderedPrimitiveIndices = scene.orderedPrimitiveIndices()
        cachedSceneKey = sceneKey
        cachedOrderedPrimitiveIndices = orderedPrimitiveIndices
        cachedVisibilityIndex = VVPrimitiveVisibilityIndex(
            scene: scene,
            orderedPrimitiveIndices: orderedPrimitiveIndices,
            bucketHeight: 320
        )
    }

    private func primitiveIntersectsVisibleRect(_ primitive: VVPrimitive, visibleRect: CGRect) -> Bool {
        guard let bounds = primitiveVisibilityBounds(primitive) else { return true }
        return bounds.intersects(visibleRect)
    }

    private func primitiveVisibilityBounds(_ primitive: VVPrimitive) -> CGRect? {
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
            let rect = CGRect(
                x: minX - line.thickness * 0.5,
                y: minY - line.thickness * 0.5,
                width: abs(line.end.x - line.start.x) + line.thickness,
                height: abs(line.end.y - line.start.y) + line.thickness
            )
            return transformed(rect: rect, by: primitive.transform)
        case .underline(let underline):
            let rect = CGRect(x: underline.origin.x, y: underline.origin.y, width: underline.width, height: max(underline.thickness, 1))
            return transformed(rect: rect, by: primitive.transform)
        case .bullet(let bullet):
            let rect = CGRect(x: bullet.position.x, y: bullet.position.y, width: bullet.size, height: bullet.size)
            return transformed(rect: rect, by: primitive.transform)
        case .image(let image):
            return transformed(rect: image.frame, by: primitive.transform)
        case .blockQuoteBorder(let border):
            return transformed(rect: border.frame, by: primitive.transform)
        case .tableLine(let line):
            let minX = min(line.start.x, line.end.x)
            let minY = min(line.start.y, line.end.y)
            let rect = CGRect(
                x: minX - line.lineWidth * 0.5,
                y: minY - line.lineWidth * 0.5,
                width: abs(line.end.x - line.start.x) + line.lineWidth,
                height: abs(line.end.y - line.start.y) + line.lineWidth
            )
            return transformed(rect: rect, by: primitive.transform)
        case .pieSlice(let slice):
            let rect = CGRect(x: slice.center.x - slice.radius, y: slice.center.y - slice.radius, width: slice.radius * 2, height: slice.radius * 2)
            return transformed(rect: rect, by: primitive.transform)
        case .path(let path):
            let pathBounds = transformed(rect: path.bounds, by: path.transform)
            return transformed(rect: pathBounds, by: primitive.transform)
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

    private func renderPrimitive(_ primitive: VVPrimitive, encoder: MTLRenderCommandEncoder) {
        let transform = primitive.transform
        switch primitive.kind {
        case .quad(let quad):
            renderQuadPrimitive(quad, transform: transform, encoder: encoder)
        case .gradientQuad(let quad):
            renderGradientQuad(quad, transform: transform, encoder: encoder)
        case .line(let line):
            renderLinePrimitive(line, transform: transform, encoder: encoder)
        case .bullet(let bullet):
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
                    position: SIMD2<Float>(Float(bullet.position.x), Float(bullet.position.y)),
                    size: SIMD2<Float>(Float(bullet.size), Float(bullet.size)),
                    color: bullet.color,
                    bulletType: bulletType
                )
                if let buffer = renderer.makeBuffer(for: [instance]) {
                    renderer.renderBullets(encoder: encoder, instances: buffer, instanceCount: 1)
                }
            case .checkbox(let checked):
                let instance = CheckboxInstance(
                    position: SIMD2<Float>(Float(bullet.position.x), Float(bullet.position.y)),
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
        case .image(let image):
            let frame = transformed(rect: image.frame, by: transform)
            let border = QuadInstance(
                position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
                size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
                color: .gray(0.35),
                cornerRadius: Float(image.cornerRadius)
            )
            let innerFrame = frame.insetBy(dx: 1, dy: 1)
            let fill = QuadInstance(
                position: SIMD2<Float>(Float(innerFrame.origin.x), Float(innerFrame.origin.y)),
                size: SIMD2<Float>(Float(innerFrame.width), Float(innerFrame.height)),
                color: .gray(0.12),
                cornerRadius: Float(max(0, image.cornerRadius - 1))
            )
            if let buffer = renderer.makeBuffer(for: [border, fill]) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 2, rounded: true)
            }
        case .blockQuoteBorder(let border):
            let instance = BlockQuoteBorderInstance(
                position: SIMD2<Float>(Float(border.frame.origin.x), Float(border.frame.origin.y)),
                size: SIMD2<Float>(Float(border.frame.width), Float(border.frame.height)),
                color: border.color,
                borderWidth: Float(border.borderWidth)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderBlockQuoteBorders(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .tableLine(let line):
            let instance = TableGridLineInstance(
                start: SIMD2<Float>(Float(line.start.x), Float(line.start.y)),
                end: SIMD2<Float>(Float(line.end.x), Float(line.end.y)),
                color: line.color,
                lineWidth: Float(line.lineWidth)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderTableGrid(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .pieSlice(let slice):
            let instance = PieSliceInstance(
                center: SIMD2<Float>(Float(slice.center.x), Float(slice.center.y)),
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
            let transformedSize = transformed(size: CGSize(width: underline.width, height: underline.thickness), by: transform)
            let instance = LineInstance(
                position: SIMD2<Float>(Float(transformedOrigin.x), Float(transformedOrigin.y)),
                width: Float(max(1, transformedSize.width)),
                height: Float(max(underline.thickness, transformedSize.height)),
                color: underline.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .path(let path):
            renderPathPrimitive(path, inheritedTransform: transform, encoder: encoder)
        case .textRun:
            break
        }
    }

    private func renderGradientQuad(_ gradient: VVGradientQuadPrimitive, transform: VVTransform2D?, encoder: MTLRenderCommandEncoder) {
        let frame = transformed(rect: gradient.frame, by: transform).integral
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

    private func renderQuadPrimitive(_ quad: VVQuadPrimitive, transform: VVTransform2D?, encoder: MTLRenderCommandEncoder) {
        let frame = transformed(rect: quad.frame, by: transform)
        guard frame.width > 0, frame.height > 0 else { return }

        let instance = QuadInstance(
            position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
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
                position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
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

        let segments = borderSegments(for: frame, border: border)
        guard !segments.isEmpty, let buffer = renderer.makeBuffer(for: segments) else { return }
        renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: segments.count, rounded: false)
    }

    private func renderLinePrimitive(_ line: VVLinePrimitive, transform: VVTransform2D?, encoder: MTLRenderCommandEncoder) {
        let transformedStart = transformed(point: line.start, by: transform)
        let transformedEnd = transformed(point: line.end, by: transform)
        let segments = dashedSegments(for: VVLinePrimitive(start: transformedStart, end: transformedEnd, thickness: line.thickness, color: line.color, dash: line.dash))

        let instances = segments.map { segment in
            let minX = min(segment.start.x, segment.end.x)
            let minY = min(segment.start.y, segment.end.y)
            let width = abs(segment.end.x - segment.start.x)
            let height = abs(segment.end.y - segment.start.y)
            return LineInstance(
                position: SIMD2<Float>(Float(minX), Float(minY)),
                width: Float(width > 0 ? width : segment.thickness),
                height: Float(height > 0 ? height : segment.thickness),
                color: segment.color
            )
        }

        if let buffer = renderer.makeBuffer(for: instances) {
            renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: instances.count)
        }
    }

    private func renderPathPrimitive(_ path: VVPathPrimitive, inheritedTransform: VVTransform2D?, encoder: MTLRenderCommandEncoder) {
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
            let position = transformed(point: vertex.position, by: combinedTransform)
            return PathRenderVertex(
                position: SIMD2<Float>(Float(position.x), Float(position.y)),
                stPosition: SIMD2<Float>(Float(vertex.stPosition.x), Float(vertex.stPosition.y))
            )
        }
        guard let buffer = renderer.makeBuffer(for: vertices) else { return }

        if let fill = path.fill, path.fillVertexCount > 0 {
            renderer.renderPath(encoder: encoder, vertices: buffer, vertexCount: path.fillVertexCount, color: fill)
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
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]],
        underlines: inout [LineInstance],
        strikethroughs: inout [LineInstance]
    ) {
        for glyph in run.glyphs {
            appendGlyphInstance(glyph, glyphInstances: &glyphInstances, colorGlyphInstances: &colorGlyphInstances)
        }

        guard run.style.isStrikethrough else { return }
        let glyphMinX = run.glyphs.map(\.position.x).min() ?? run.position.x
        let glyphMaxX = run.glyphs.map { $0.position.x + $0.size.width }.max() ?? run.position.x
        let bounds = run.runBounds ?? run.lineBounds
        let startX = bounds?.minX ?? glyphMinX
        let width = max(0, bounds?.width ?? (glyphMaxX - glyphMinX))
        let strikeY = run.position.y - max(1, run.fontSize * 0.35)
        strikethroughs.append(
            LineInstance(
                position: SIMD2<Float>(Float(startX), Float(strikeY)),
                width: Float(width),
                height: 1,
                color: run.style.color
            )
        )
        if run.style.isLink {
            let underlineY = run.position.y + max(1, run.fontSize * 0.12)
            underlines.append(
                LineInstance(
                    position: SIMD2<Float>(Float(startX), Float(underlineY)),
                    width: Float(width),
                    height: 1,
                    color: run.style.color
                )
            )
        }
    }

    private func appendGlyphInstance(
        _ glyph: VVTextGlyph,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]]
    ) {
        guard let cached = cachedGlyph(for: glyph) else { return }
        let glyphColor = cached.isColor ? SIMD4<Float>(1, 1, 1, glyph.color.w) : glyph.color
        let instance = MarkdownGlyphInstance(
            position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x), Float(glyph.position.y + cached.bearing.y)),
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

    private func cachedGlyph(for glyph: VVTextGlyph) -> MarkdownCachedGlyph? {
        let cgGlyph = CGGlyph(glyph.glyphID)
        let layoutVariant = toLayoutFontVariant(glyph.fontVariant)
        if let fontName = glyph.fontName {
            return renderer.glyphAtlas.glyph(for: cgGlyph, fontName: fontName, fontSize: glyph.fontSize, variant: layoutVariant)
        }
        return renderer.glyphAtlas.glyph(for: cgGlyph, variant: layoutVariant, fontSize: glyph.fontSize, baseFont: renderer.baseFont)
    }

    private func toLayoutFontVariant(_ variant: VVFontVariant) -> FontVariant {
        switch variant {
        case .regular: return .regular
        case .semibold: return .semibold
        case .semiboldItalic: return .semiboldItalic
        case .bold: return .bold
        case .italic: return .italic
        case .boldItalic: return .boldItalic
        case .monospace: return .monospace
        case .emoji: return .emoji
        }
    }

    private func renderGlyphBatches(_ batches: [Int: [MarkdownGlyphInstance]], encoder: MTLRenderCommandEncoder, isColor: Bool) {
        guard !batches.isEmpty else { return }
        let textures = isColor ? renderer.glyphAtlas.allColorAtlasTextures : renderer.glyphAtlas.allAtlasTextures
        for atlasIndex in batches.keys.sorted() {
            guard atlasIndex >= 0 && atlasIndex < textures.count else { continue }
            guard let instances = batches[atlasIndex], !instances.isEmpty else { continue }
            guard let buffer = renderer.makeBuffer(for: instances) else { continue }
            if isColor {
                renderer.renderColorGlyphs(encoder: encoder, instances: buffer, instanceCount: instances.count, texture: textures[atlasIndex])
            } else {
                renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: instances.count, texture: textures[atlasIndex])
            }
        }
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
        let cleaned = pattern.filter { $0 > 0 }
        guard cleaned.count >= 2 else { return [line] }

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
            let segmentLength = min(cleaned[patternIndex % cleaned.count], length - distance)
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

    private func borderSegments(for frame: CGRect, border: VVBorder) -> [QuadInstance] {
        let widths = border.widths
        let color = border.color
        var segments: [QuadInstance] = []

        func append(rect: CGRect) {
            guard rect.width > 0, rect.height > 0 else { return }
            segments.append(
                QuadInstance(
                    position: SIMD2<Float>(Float(rect.origin.x), Float(rect.origin.y)),
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

private struct SceneCacheKey: Equatable {
    let primitiveCount: Int
    let baseAddress: UInt

    init(scene: VVScene) {
        primitiveCount = scene.primitives.count
        baseAddress = scene.primitives.withUnsafeBufferPointer { buffer in
            buffer.baseAddress.map { UInt(bitPattern: UnsafeRawPointer($0)) } ?? 0
        }
    }
}
