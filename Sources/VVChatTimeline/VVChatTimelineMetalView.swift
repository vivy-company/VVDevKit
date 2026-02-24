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
    func selectionQuads(forItemAt index: Int, itemOffset: CGPoint) -> [VVQuadPrimitive]
}

public extension VVChatTimelineRenderDataSource {
    func selectionQuads(forItemAt index: Int, itemOffset: CGPoint) -> [VVQuadPrimitive] { [] }
}

public protocol VVChatTimelineSelectionDelegate: AnyObject {
    func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseDownAt point: CGPoint, clickCount: Int, modifiers: NSEvent.ModifierFlags)
    func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseDraggedTo point: CGPoint, event: NSEvent)
    func chatTimelineMetalViewMouseUp(_ view: VVChatTimelineMetalView)
}

public final class VVChatTimelineMetalView: MTKView {
    public weak var renderDataSource: VVChatTimelineRenderDataSource?
    public weak var selectionDelegate: VVChatTimelineSelectionDelegate?

    private var renderer: MarkdownMetalRenderer?
    private var currentDrawableSize: CGSize = .zero
    private var currentScrollOffset: CGPoint = .zero
    private var baseFont: VVFont = .systemFont(ofSize: 14)
    private var baseFontAscent: CGFloat = 0
    private var baseFontDescent: CGFloat = 0

    public override var isFlipped: Bool { true }
    public override var isOpaque: Bool { false }
    public override var acceptsFirstResponder: Bool { true }

    public override func mouseDown(with event: NSEvent) {
        window?.makeFirstResponder(self)
        let point = convert(event.locationInWindow, from: nil)
        selectionDelegate?.chatTimelineMetalView(self, mouseDownAt: point, clickCount: event.clickCount, modifiers: event.modifierFlags)
    }

    public override func mouseDragged(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        selectionDelegate?.chatTimelineMetalView(self, mouseDraggedTo: point, event: event)
    }

    public override func mouseUp(with event: NSEvent) {
        selectionDelegate?.chatTimelineMetalViewMouseUp(self)
    }

    public override func resetCursorRects() {
        addCursorRect(bounds, cursor: .iBeam)
    }

    private var metalContext: VVMetalContext?

    public init(frame: CGRect, font: VVFont, metalContext: VVMetalContext? = nil) {
        self.metalContext = metalContext ?? VVMetalContext.shared
        let device = self.metalContext?.device ?? MTLCreateSystemDefaultDevice()
        super.init(frame: frame, device: device)
        configureRenderer(font: font)
    }

    required init(coder: NSCoder) {
        self.metalContext = VVMetalContext.shared
        super.init(coder: coder)
        device = metalContext?.device ?? MTLCreateSystemDefaultDevice()
        configureRenderer(font: .systemFont(ofSize: 14))
    }

    private func configureRenderer(font: VVFont) {
        guard device != nil else { return }
        baseFont = font
        baseFontAscent = CTFontGetAscent(font)
        baseFontDescent = CTFontGetDescent(font)
        layer?.isOpaque = false
        clearColor = MTLClearColor(red: 0, green: 0, blue: 0, alpha: 0)
        framebufferOnly = true
        enableSetNeedsDisplay = true
        isPaused = true
        if let ctx = metalContext {
            renderer = MarkdownMetalRenderer(context: ctx, baseFont: font, scaleFactor: window?.backingScaleFactor ?? 2.0)
        } else {
            renderer = nil
        }
    }

    public func updateFont(_ font: VVFont) {
        configureRenderer(font: font)
        setNeedsDisplay(bounds)
    }

    public override func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        if window == nil {
            releaseDrawables()
        }
    }

    public override func viewDidHide() {
        super.viewDidHide()
        releaseDrawables()
    }

    public override func viewDidUnhide() {
        super.viewDidUnhide()
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
        let visibilityPadding: CGFloat = 1024

        // Single beginFrame per draw — the uniform buffer is shared across all render
        // calls in the command encoder.  Calling beginFrame per item overwrites the
        // triple-buffered uniform after 3 items, corrupting earlier items' transforms.
        let scrollOffset = visibleRect.origin
        currentScrollOffset = scrollOffset
        renderer.beginFrame(viewportSize: viewportSize, scrollOffset: scrollOffset)

        for index in 0..<renderDataSource.renderItemCount {
            guard let item = renderDataSource.renderItem(at: index) else { continue }
            if item.frame.maxY < visibleRect.minY - visibilityPadding { continue }
            if item.frame.minY > visibleRect.maxY + visibilityPadding { continue }

            // Each item's scene uses local coordinates (0,0 = item top-left).
            // Offset primitives by the item's absolute position so they render
            // correctly under the single global projection + scroll offset.
            let itemOffset = CGPoint(x: item.frame.origin.x + item.contentOffset.x,
                                     y: item.frame.origin.y + item.contentOffset.y)

            renderScene(item.scene, encoder: encoder, renderer: renderer, imageProvider: renderDataSource, itemOffset: itemOffset)

            // Draw selection after scene so bubbles do not occlude highlight quads.
            let selQuads = renderDataSource.selectionQuads(forItemAt: index, itemOffset: itemOffset)
            if !selQuads.isEmpty {
                var instances: [QuadInstance] = []
                instances.reserveCapacity(selQuads.count)
                for quad in selQuads {
                    instances.append(QuadInstance(
                        position: SIMD2<Float>(Float(quad.frame.origin.x), Float(quad.frame.origin.y)),
                        size: SIMD2<Float>(Float(quad.frame.width), Float(quad.frame.height)),
                        color: quad.color,
                        cornerRadius: Float(quad.cornerRadius)
                    ))
                }
                if let buffer = renderer.makeBuffer(for: instances) {
                    renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: instances.count, rounded: true)
                }
            }
        }

        encoder.endEncoding()
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
    }

    private func renderScene(
        _ scene: VVScene,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        imageProvider: VVChatTimelineRenderDataSource,
        itemOffset: CGPoint = .zero
    ) {
        let ox = Float(itemOffset.x)
        let oy = Float(itemOffset.y)
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
            let offsetClip = clip.map { $0.offsetBy(dx: itemOffset.x, dy: itemOffset.y) }
            if offsetClip != currentClip {
                flushTextBatches()
                if let offsetClip {
                    encoder.setScissorRect(scissorRect(for: offsetClip))
                } else {
                    encoder.setScissorRect(fullScissorRect())
                }
                currentClip = offsetClip
            }
        }

        for primitive in scene.orderedPrimitives() {
            updateClip(primitive.clipRect)
            switch primitive.kind {
            case .textRun(let run):
                appendTextPrimitive(run, offset: SIMD2(ox, oy), renderer: renderer, glyphInstances: &glyphInstances, colorGlyphInstances: &colorGlyphInstances, underlines: &underlines, strikethroughs: &strikethroughs)
            default:
                flushTextBatches()
                renderPrimitive(primitive, offset: SIMD2(ox, oy), encoder: encoder, renderer: renderer, imageProvider: imageProvider)
            }
        }

        flushTextBatches()
        updateClip(nil)
    }

    private func renderPrimitive(
        _ primitive: VVPrimitive,
        offset o: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        imageProvider: VVChatTimelineRenderDataSource
    ) {
        switch primitive.kind {
        case .quad(let quad):
            let instance = QuadInstance(
                position: SIMD2<Float>(Float(quad.frame.origin.x) + o.x, Float(quad.frame.origin.y) + o.y),
                size: SIMD2<Float>(Float(quad.frame.width), Float(quad.frame.height)),
                color: quad.color,
                cornerRadius: Float(quad.cornerRadius)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: quad.cornerRadius > 0)
            }

        case .gradientQuad(let quad):
            renderGradientQuad(quad, offset: o, encoder: encoder, renderer: renderer)

        case .line(let line):
            let minX = min(line.start.x, line.end.x)
            let minY = min(line.start.y, line.end.y)
            let width = abs(line.end.x - line.start.x)
            let height = abs(line.end.y - line.start.y)
            let rectWidth = width > 0 ? width : line.thickness
            let rectHeight = height > 0 ? height : line.thickness
            let instance = LineInstance(
                position: SIMD2<Float>(Float(minX) + o.x, Float(minY) + o.y),
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
                    position: SIMD2<Float>(Float(bullet.position.x) + o.x, Float(bullet.position.y) + o.y),
                    size: SIMD2<Float>(Float(bullet.size), Float(bullet.size)),
                    color: bullet.color,
                    bulletType: bulletType
                )
                if let buffer = renderer.makeBuffer(for: [instance]) {
                    renderer.renderBullets(encoder: encoder, instances: buffer, instanceCount: 1)
                }
            case .checkbox(let checked):
                let instance = CheckboxInstance(
                    position: SIMD2<Float>(Float(bullet.position.x) + o.x, Float(bullet.position.y) + o.y),
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
                position: SIMD2<Float>(Float(image.frame.origin.x) + o.x, Float(image.frame.origin.y) + o.y),
                size: SIMD2<Float>(Float(image.frame.width), Float(image.frame.height)),
                cornerRadius: Float(image.cornerRadius)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderImages(encoder: encoder, instances: buffer, instanceCount: 1, texture: texture)
            }

        case .blockQuoteBorder(let border):
            let instance = BlockQuoteBorderInstance(
                position: SIMD2<Float>(Float(border.frame.origin.x) + o.x, Float(border.frame.origin.y) + o.y),
                size: SIMD2<Float>(Float(border.frame.width), Float(border.frame.height)),
                color: border.color,
                borderWidth: Float(border.borderWidth)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderBlockQuoteBorders(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .tableLine(let line):
            let instance = TableGridLineInstance(
                start: SIMD2<Float>(Float(line.start.x) + o.x, Float(line.start.y) + o.y),
                end: SIMD2<Float>(Float(line.end.x) + o.x, Float(line.end.y) + o.y),
                color: line.color,
                lineWidth: Float(line.lineWidth)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderTableGrid(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .pieSlice(let slice):
            let instance = PieSliceInstance(
                center: SIMD2<Float>(Float(slice.center.x) + o.x, Float(slice.center.y) + o.y),
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

        case .underline(let underline):
            let instance = LineInstance(
                position: SIMD2<Float>(Float(underline.origin.x) + o.x, Float(underline.origin.y) + o.y),
                width: Float(underline.width),
                height: Float(underline.thickness),
                color: underline.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .path:
            break
        }
    }

    private func renderGradientQuad(
        _ gradient: VVGradientQuadPrimitive,
        offset o: SIMD2<Float> = .zero,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let stepCount = max(2, min(36, gradient.steps))
        let frame = gradient.frame.offsetBy(dx: CGFloat(o.x), dy: CGFloat(o.y)).integral
        guard frame.width > 0, frame.height > 0 else { return }

        var instances: [QuadInstance] = []
        instances.reserveCapacity(stepCount)

        switch gradient.direction {
        case .horizontal:
            let segmentWidth = frame.width / CGFloat(stepCount)
            for index in 0..<stepCount {
                let t = stepCount <= 1 ? Float(0) : Float(index) / Float(stepCount - 1)
                let x = frame.minX + CGFloat(index) * segmentWidth
                let width = index == stepCount - 1 ? max(0, frame.maxX - x) : segmentWidth + 0.75
                guard width > 0 else { continue }
                let cornerRadius = (index == 0 || index == stepCount - 1) ? gradient.cornerRadius : 0
                instances.append(
                    QuadInstance(
                        position: SIMD2<Float>(Float(x), Float(frame.minY)),
                        size: SIMD2<Float>(Float(width), Float(frame.height)),
                        color: lerpColor(gradient.startColor, gradient.endColor, t: t),
                        cornerRadius: Float(cornerRadius)
                    )
                )
            }

        case .vertical:
            let segmentHeight = frame.height / CGFloat(stepCount)
            for index in 0..<stepCount {
                let t = stepCount <= 1 ? Float(0) : Float(index) / Float(stepCount - 1)
                let y = frame.minY + CGFloat(index) * segmentHeight
                let height = index == stepCount - 1 ? max(0, frame.maxY - y) : segmentHeight + 0.75
                guard height > 0 else { continue }
                let cornerRadius = (index == 0 || index == stepCount - 1) ? gradient.cornerRadius : 0
                instances.append(
                    QuadInstance(
                        position: SIMD2<Float>(Float(frame.minX), Float(y)),
                        size: SIMD2<Float>(Float(frame.width), Float(height)),
                        color: lerpColor(gradient.startColor, gradient.endColor, t: t),
                        cornerRadius: Float(cornerRadius)
                    )
                )
            }
        }

        guard !instances.isEmpty, let buffer = renderer.makeBuffer(for: instances) else { return }
        renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: instances.count, rounded: gradient.cornerRadius > 0)
    }

    private func lerpColor(_ start: SIMD4<Float>, _ end: SIMD4<Float>, t: Float) -> SIMD4<Float> {
        let clamped = max(0, min(1, t))
        return start + (end - start) * clamped
    }

    private func appendTextPrimitive(
        _ run: VVTextRunPrimitive,
        offset o: SIMD2<Float> = .zero,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]],
        underlines: inout [LineInstance],
        strikethroughs: inout [LineInstance]
    ) {
        for glyph in run.glyphs {
            appendGlyphInstance(glyph, offset: o, renderer: renderer, glyphInstances: &glyphInstances, colorGlyphInstances: &colorGlyphInstances)
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
                position: SIMD2<Float>(Float(underlineStartX) + o.x, Float(underlineY) + o.y),
                width: Float(underlineWidth),
                height: 1,
                color: run.style.color
            ))
        }

        if run.style.isStrikethrough {
            let strikeY = run.position.y - max(1, ascent * 0.35)
            strikethroughs.append(LineInstance(
                position: SIMD2<Float>(Float(underlineStartX) + o.x, Float(strikeY) + o.y),
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
        return renderer.glyphAtlas.glyph(for: glyph.glyphID, variant: glyph.fontVariant, fontSize: glyph.fontSize, baseFont: renderer.baseFont)
    }

    private func cachedGlyph(for glyph: VVTextGlyph, renderer: MarkdownMetalRenderer) -> MarkdownCachedGlyph? {
        let layoutVariant = toLayoutFontVariant(glyph.fontVariant)
        let cgGlyph = CGGlyph(glyph.glyphID)
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

    private func appendGlyphInstance(
        _ glyph: LayoutGlyph,
        offset o: SIMD2<Float> = .zero,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]]
    ) {
        guard let cached = cachedGlyph(for: glyph, renderer: renderer) else { return }
        let glyphColor = cached.isColor ? SIMD4<Float>(1, 1, 1, glyph.color.w) : glyph.color
        let instance = MarkdownGlyphInstance(
            position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x) + o.x, Float(glyph.position.y + cached.bearing.y) + o.y),
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
        offset o: SIMD2<Float> = .zero,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]]
    ) {
        guard let cached = cachedGlyph(for: glyph, renderer: renderer) else { return }
        let glyphColor = cached.isColor ? SIMD4<Float>(1, 1, 1, glyph.color.w) : glyph.color
        let instance = MarkdownGlyphInstance(
            position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x) + o.x, Float(glyph.position.y + cached.bearing.y) + o.y),
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
