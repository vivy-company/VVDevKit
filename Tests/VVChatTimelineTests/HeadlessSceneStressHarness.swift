import CoreGraphics
import CoreText
import Metal
import XCTest
@testable import VVMarkdown
import VVMetalPrimitives

final class HeadlessSceneStressHarness {
    private let renderer: MarkdownMetalRenderer
    private let viewportSize: CGSize

    init(baseFont: VVFont, viewportSize: CGSize) throws {
        guard let device = MTLCreateSystemDefaultDevice() else {
            throw XCTSkip("Metal is unavailable on this machine")
        }
        let context = try VVMetalContext(device: device)
        self.renderer = MarkdownMetalRenderer(context: context, baseFont: baseFont, scaleFactor: 2.0)
        self.viewportSize = viewportSize
    }

    @discardableResult
    func render(scene: VVScene, scrollOffset: CGPoint = .zero, visiblePadding: CGFloat = 512) throws -> MTLTexture {
        let texture = try makeTexture()
        guard let commandBuffer = renderer.commandQueue.makeCommandBuffer() else {
            XCTFail("Failed to create command buffer")
            throw CancellationError()
        }

        let descriptor = MTLRenderPassDescriptor()
        descriptor.colorAttachments[0].texture = texture
        descriptor.colorAttachments[0].loadAction = .clear
        descriptor.colorAttachments[0].storeAction = .store
        descriptor.colorAttachments[0].clearColor = MTLClearColor(red: 0.06, green: 0.06, blue: 0.08, alpha: 1)

        guard let encoder = commandBuffer.makeRenderCommandEncoder(descriptor: descriptor) else {
            XCTFail("Failed to create render encoder")
            throw CancellationError()
        }

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
        let descriptor = MTLTextureDescriptor.texture2DDescriptor(
            pixelFormat: .bgra8Unorm,
            width: max(1, Int(ceil(viewportSize.width))),
            height: max(1, Int(ceil(viewportSize.height))),
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
        let sceneRenderer = MarkdownScenePrimitiveRenderer(baseFont: renderer.baseFont)
        sceneRenderer.renderScene(
            scene,
            orderedPrimitives: scene.orderedPrimitives(),
            visibleRect: visibleRect,
            encoder: encoder,
            renderer: renderer
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
            return run.lineBounds ?? run.runBounds ?? glyphBounds(for: run.glyphs)
        case .quad(let quad):
            return quad.frame
        case .gradientQuad(let quad):
            return quad.frame
        case .line(let line):
            let minX = min(line.start.x, line.end.x)
            let minY = min(line.start.y, line.end.y)
            return CGRect(
                x: minX - line.thickness * 0.5,
                y: minY - line.thickness * 0.5,
                width: abs(line.end.x - line.start.x) + line.thickness,
                height: abs(line.end.y - line.start.y) + line.thickness
            )
        case .underline(let underline):
            return CGRect(x: underline.origin.x, y: underline.origin.y, width: underline.width, height: max(underline.thickness, 1))
        case .bullet(let bullet):
            return CGRect(x: bullet.position.x, y: bullet.position.y, width: bullet.size, height: bullet.size)
        case .image(let image):
            return image.frame
        case .blockQuoteBorder(let border):
            return border.frame
        case .tableLine(let line):
            let minX = min(line.start.x, line.end.x)
            let minY = min(line.start.y, line.end.y)
            return CGRect(
                x: minX - line.lineWidth * 0.5,
                y: minY - line.lineWidth * 0.5,
                width: abs(line.end.x - line.start.x) + line.lineWidth,
                height: abs(line.end.y - line.start.y) + line.lineWidth
            )
        case .pieSlice(let slice):
            return CGRect(x: slice.center.x - slice.radius, y: slice.center.y - slice.radius, width: slice.radius * 2, height: slice.radius * 2)
        case .path(let path):
            return path.bounds
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
        switch primitive.kind {
        case .quad(let quad):
            let instance = QuadInstance(
                position: SIMD2<Float>(Float(quad.frame.origin.x), Float(quad.frame.origin.y)),
                size: SIMD2<Float>(Float(quad.frame.width), Float(quad.frame.height)),
                color: quad.color,
                cornerRadius: Float(quad.cornerRadius)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: quad.cornerRadius > 0)
            }
        case .gradientQuad(let quad):
            let axis: SIMD2<Float>
            if let angle = quad.angle {
                axis = SIMD2<Float>(Float(cos(angle)), Float(sin(angle)))
            } else {
                axis = quad.direction == .horizontal ? SIMD2<Float>(1, 0) : SIMD2<Float>(0, 1)
            }
            let instance = GradientQuadInstance(
                position: SIMD2<Float>(Float(quad.frame.origin.x), Float(quad.frame.origin.y)),
                size: SIMD2<Float>(Float(quad.frame.width), Float(quad.frame.height)),
                startColor: quad.startColor,
                endColor: quad.endColor,
                axis: axis,
                cornerRadius: Float(quad.cornerRadius)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderGradientQuads(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .line(let line):
            let instance = LineInstance(
                position: SIMD2<Float>(Float(min(line.start.x, line.end.x)), Float(min(line.start.y, line.end.y))),
                width: Float(max(abs(line.end.x - line.start.x), line.thickness)),
                height: Float(max(abs(line.end.y - line.start.y), line.thickness)),
                color: line.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: 1)
            }
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
            let border = QuadInstance(
                position: SIMD2<Float>(Float(image.frame.origin.x), Float(image.frame.origin.y)),
                size: SIMD2<Float>(Float(image.frame.width), Float(image.frame.height)),
                color: .gray(0.35),
                cornerRadius: Float(image.cornerRadius)
            )
            let inner = image.frame.insetBy(dx: 1, dy: 1)
            let fill = QuadInstance(
                position: SIMD2<Float>(Float(inner.origin.x), Float(inner.origin.y)),
                size: SIMD2<Float>(Float(inner.width), Float(inner.height)),
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
            let instance = LineInstance(
                position: SIMD2<Float>(Float(underline.origin.x), Float(underline.origin.y)),
                width: Float(max(1, underline.width)),
                height: Float(max(underline.thickness, 1)),
                color: underline.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        case .path(let path):
            let vertices = path.vertices.map {
                PathRenderVertex(
                    position: SIMD2<Float>(Float($0.position.x), Float($0.position.y)),
                    stPosition: SIMD2<Float>(Float($0.stPosition.x), Float($0.stPosition.y))
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
        case .textRun:
            break
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
            guard let cached = cachedGlyph(for: glyph) else { continue }
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

        let glyphMinX = run.glyphs.map(\.position.x).min() ?? run.position.x
        let glyphMaxX = run.glyphs.map { $0.position.x + $0.size.width }.max() ?? run.position.x
        let bounds = run.runBounds ?? run.lineBounds
        let startX = bounds?.minX ?? glyphMinX
        let width = max(0, bounds?.width ?? (glyphMaxX - glyphMinX))

        if run.style.isLink {
            underlines.append(
                LineInstance(
                    position: SIMD2<Float>(Float(startX), Float(run.position.y + max(1, run.fontSize * 0.12))),
                    width: Float(width),
                    height: 1,
                    color: run.style.color
                )
            )
        }
        if run.style.isStrikethrough {
            strikethroughs.append(
                LineInstance(
                    position: SIMD2<Float>(Float(startX), Float(run.position.y - max(1, run.fontSize * 0.35))),
                    width: Float(width),
                    height: 1,
                    color: run.style.color
                )
            )
        }
    }

    private func cachedGlyph(for glyph: VVTextGlyph) -> MarkdownCachedGlyph? {
        let cgGlyph = CGGlyph(glyph.glyphID)
        let variant: FontVariant
        switch glyph.fontVariant {
        case .regular: variant = .regular
        case .semibold: variant = .semibold
        case .semiboldItalic: variant = .semiboldItalic
        case .bold: variant = .bold
        case .italic: variant = .italic
        case .boldItalic: variant = .boldItalic
        case .monospace: variant = .monospace
        case .emoji: variant = .emoji
        }

        if let fontName = glyph.fontName {
            return renderer.glyphAtlas.glyph(for: cgGlyph, fontName: fontName, fontSize: glyph.fontSize, variant: variant)
        }
        return renderer.glyphAtlas.glyph(for: cgGlyph, variant: variant, fontSize: glyph.fontSize, baseFont: renderer.baseFont)
    }

    private func renderGlyphBatches(_ batches: [Int: [MarkdownGlyphInstance]], encoder: MTLRenderCommandEncoder, isColor: Bool) {
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
}
