#if os(macOS)
import AppKit
import CoreText
import MetalKit
import VVMarkdown
import VVMetalPrimitives

public struct VVChatTimelineRenderItem {
    public let id: String
    public let frame: CGRect
    public let contentOffset: CGPoint
    public let scene: VVScene

    public init(id: String, frame: CGRect, contentOffset: CGPoint, scene: VVScene) {
        self.id = id
        self.frame = frame
        self.contentOffset = contentOffset
        self.scene = scene
    }
}

public protocol VVChatTimelineRenderDataSource: AnyObject {
    var renderItemCount: Int { get }
    func renderItem(at index: Int) -> VVChatTimelineRenderItem?
    var viewportRect: CGRect { get }
    var backgroundColor: SIMD4<Float> { get }
    func texture(for url: String) -> MTLTexture?
}

public final class VVChatTimelineMetalView: MTKView {
    public weak var renderDataSource: VVChatTimelineRenderDataSource?

    private var renderer: MarkdownMetalRenderer?
    private var currentDrawableSize: CGSize = .zero
    private var currentScrollOffset: CGPoint = .zero
    private var baseFont: VVFont = .systemFont(ofSize: 14)
    private var baseFontAscent: CGFloat = 0
    private var baseFontDescent: CGFloat = 0

    public override var isFlipped: Bool { true }

    public init(frame: CGRect, font: VVFont) {
        let device = MTLCreateSystemDefaultDevice()
        super.init(frame: frame, device: device)
        configureRenderer(font: font)
    }

    required init(coder: NSCoder) {
        super.init(coder: coder)
        device = MTLCreateSystemDefaultDevice()
        configureRenderer(font: .systemFont(ofSize: 14))
    }

    private func configureRenderer(font: VVFont) {
        guard let device else { return }
        baseFont = font
        baseFontAscent = CTFontGetAscent(font)
        baseFontDescent = CTFontGetDescent(font)
        framebufferOnly = true
        enableSetNeedsDisplay = true
        isPaused = true
        do {
            renderer = try MarkdownMetalRenderer(device: device, baseFont: font, scaleFactor: window?.backingScaleFactor ?? 2.0)
        } catch {
            renderer = nil
        }
    }

    public func updateFont(_ font: VVFont) {
        configureRenderer(font: font)
        setNeedsDisplay(bounds)
    }

    public override func draw(_ dirtyRect: NSRect) {
        guard let renderer,
              let renderDataSource,
              let drawable = currentDrawable else { return }

        let commandBuffer = renderer.commandQueue.makeCommandBuffer()
        currentDrawableSize = CGSize(width: drawable.texture.width, height: drawable.texture.height)

        let passDescriptor = MTLRenderPassDescriptor()
        passDescriptor.colorAttachments[0].texture = drawable.texture
        passDescriptor.colorAttachments[0].loadAction = .clear
        passDescriptor.colorAttachments[0].storeAction = .store
        let bg = renderDataSource.backgroundColor
        passDescriptor.colorAttachments[0].clearColor = MTLClearColor(red: Double(bg.x), green: Double(bg.y), blue: Double(bg.z), alpha: Double(bg.w))

        guard let encoder = commandBuffer?.makeRenderCommandEncoder(descriptor: passDescriptor) else { return }

        let visibleRect = renderDataSource.viewportRect
        let viewportSize = bounds.size

        for index in 0..<renderDataSource.renderItemCount {
            guard let item = renderDataSource.renderItem(at: index) else { continue }
            if item.frame.maxY < visibleRect.minY { continue }
            if item.frame.minY > visibleRect.maxY { break }

            let messageOrigin = CGPoint(x: item.frame.origin.x + item.contentOffset.x,
                                        y: item.frame.origin.y + item.contentOffset.y)
            let scrollOffset = CGPoint(x: visibleRect.origin.x - messageOrigin.x,
                                       y: visibleRect.origin.y - messageOrigin.y)
            currentScrollOffset = scrollOffset
            renderer.beginFrame(viewportSize: viewportSize, scrollOffset: scrollOffset)
            renderScene(item.scene, encoder: encoder, renderer: renderer, imageProvider: renderDataSource)
        }

        encoder.endEncoding()
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
    }

    private func renderScene(
        _ scene: VVScene,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        imageProvider: VVChatTimelineRenderDataSource
    ) {
        var currentClip: CGRect? = nil
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
            if clip != currentClip {
                flushTextBatches()
                if let clip {
                    encoder.setScissorRect(scissorRect(for: clip))
                } else {
                    encoder.setScissorRect(fullScissorRect())
                }
                currentClip = clip
            }
        }

        for primitive in scene.orderedPrimitives() {
            updateClip(primitive.clipRect)
            switch primitive.kind {
            case .textRun(let run):
                appendTextPrimitive(run, renderer: renderer, glyphInstances: &glyphInstances, colorGlyphInstances: &colorGlyphInstances, underlines: &underlines, strikethroughs: &strikethroughs)
            default:
                flushTextBatches()
                renderPrimitive(primitive, encoder: encoder, renderer: renderer, imageProvider: imageProvider)
            }
        }

        flushTextBatches()
        updateClip(nil)
    }

    private func renderPrimitive(
        _ primitive: VVPrimitive,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        imageProvider: VVChatTimelineRenderDataSource
    ) {
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

        case .line(let line):
            let minX = min(line.start.x, line.end.x)
            let minY = min(line.start.y, line.end.y)
            let width = abs(line.end.x - line.start.x)
            let height = abs(line.end.y - line.start.y)
            let rectWidth = width > 0 ? width : line.thickness
            let rectHeight = height > 0 ? height : line.thickness
            let instance = LineInstance(
                position: SIMD2<Float>(Float(minX), Float(minY)),
                width: Float(rectWidth),
                height: Float(rectHeight),
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
            guard let texture = imageProvider.texture(for: image.url) else { return }
            let instance = ImageInstance(
                position: SIMD2<Float>(Float(image.frame.origin.x), Float(image.frame.origin.y)),
                size: SIMD2<Float>(Float(image.frame.width), Float(image.frame.height)),
                cornerRadius: Float(image.cornerRadius)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderImages(encoder: encoder, instances: buffer, instanceCount: 1, texture: texture)
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

        case .textRun:
            break
        }
    }

    private func appendTextPrimitive(
        _ run: VVTextRunPrimitive,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]],
        underlines: inout [LineInstance],
        strikethroughs: inout [LineInstance]
    ) {
        for glyph in run.glyphs {
            appendGlyphInstance(glyph, renderer: renderer, glyphInstances: &glyphInstances, colorGlyphInstances: &colorGlyphInstances)
        }

        let baseSize = baseFont.pointSize
        let scale = baseSize > 0 ? run.fontSize / baseSize : 1
        let ascent = baseFontAscent * scale
        let descent = baseFontDescent * scale
        let glyphMinX = run.glyphs.map { $0.position.x }.min() ?? run.position.x
        let glyphMaxX = run.glyphs.map { $0.position.x + $0.size.width }.max() ?? run.position.x
        let fallbackBounds = run.runBounds ?? run.lineBounds
        let underlineStartX = fallbackBounds?.minX ?? glyphMinX
        let underlineWidth = max(0, fallbackBounds?.width ?? (glyphMaxX - glyphMinX))

        if run.style.isLink {
            let underlineY = run.position.y + max(1, descent * 0.6)
            underlines.append(LineInstance(
                position: SIMD2<Float>(Float(underlineStartX), Float(underlineY)),
                width: Float(underlineWidth),
                height: 1,
                color: run.style.color
            ))
        }

        if run.style.isStrikethrough {
            let strikeY = run.position.y - max(1, ascent * 0.35)
            strikethroughs.append(LineInstance(
                position: SIMD2<Float>(Float(underlineStartX), Float(strikeY)),
                width: Float(underlineWidth),
                height: 1,
                color: run.style.color
            ))
        }
    }

    private func cachedGlyph(for glyph: LayoutGlyph, renderer: MarkdownMetalRenderer) -> MarkdownCachedGlyph? {
        if let fontName = glyph.fontName {
            return renderer.glyphAtlas.glyph(for: glyph.glyphID, fontName: fontName, fontSize: glyph.fontSize, variant: glyph.fontVariant)
        }
        return renderer.glyphAtlas.glyph(for: glyph.glyphID, variant: glyph.fontVariant, fontSize: glyph.fontSize)
    }

    private func cachedGlyph(for glyph: VVTextGlyph, renderer: MarkdownMetalRenderer) -> MarkdownCachedGlyph? {
        let layoutVariant = toLayoutFontVariant(glyph.fontVariant)
        let cgGlyph = CGGlyph(glyph.glyphID)
        if let fontName = glyph.fontName {
            return renderer.glyphAtlas.glyph(for: cgGlyph, fontName: fontName, fontSize: glyph.fontSize, variant: layoutVariant)
        }
        return renderer.glyphAtlas.glyph(for: cgGlyph, variant: layoutVariant, fontSize: glyph.fontSize)
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

    private func appendGlyphInstance(
        _ glyph: LayoutGlyph,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]]
    ) {
        guard let cached = cachedGlyph(for: glyph, renderer: renderer) else { return }
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

    private func appendGlyphInstance(
        _ glyph: VVTextGlyph,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]]
    ) {
        guard let cached = cachedGlyph(for: glyph, renderer: renderer) else { return }
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

    private func renderGlyphBatches(
        _ batches: [Int: [MarkdownGlyphInstance]],
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        isColor: Bool
    ) {
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

    private func fullScissorRect() -> MTLScissorRect {
        let width = max(1, Int(currentDrawableSize.width))
        let height = max(1, Int(currentDrawableSize.height))
        return MTLScissorRect(x: 0, y: 0, width: width, height: height)
    }

    private func scissorRect(for frame: CGRect) -> MTLScissorRect {
        let visibleFrame = frame.offsetBy(dx: -currentScrollOffset.x, dy: -currentScrollOffset.y)
        let viewBounds = CGRect(origin: .zero, size: bounds.size)
        let clipped = visibleFrame.intersection(viewBounds)
        if clipped.isNull || clipped.width <= 0 || clipped.height <= 0 {
            return fullScissorRect()
        }
        let scaleX = currentDrawableSize.width / max(1, bounds.width)
        let scaleY = currentDrawableSize.height / max(1, bounds.height)
        let x = max(0, Int(floor(clipped.minX * scaleX)))
        let y = max(0, Int(floor(clipped.minY * scaleY)))
        let maxWidth = max(1, Int(currentDrawableSize.width) - x)
        let maxHeight = max(1, Int(currentDrawableSize.height) - y)
        let width = min(maxWidth, Int(ceil(clipped.width * scaleX)))
        let height = min(maxHeight, Int(ceil(clipped.height * scaleY)))
        return MTLScissorRect(x: x, y: y, width: max(1, width), height: max(1, height))
    }
}
#endif
