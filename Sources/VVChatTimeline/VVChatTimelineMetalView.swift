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
    func visibleRenderIndexes() -> Range<Int>
    var viewportRect: CGRect { get }
    var backgroundColor: SIMD4<Float> { get }
    func texture(for url: String) -> MTLTexture?
    func selectionQuads(forItemAt index: Int, itemOffset: CGPoint) -> [VVQuadPrimitive]
    func hoverQuads(forItemAt index: Int, itemOffset: CGPoint) -> [VVQuadPrimitive]
}

public extension VVChatTimelineRenderDataSource {
    func visibleRenderIndexes() -> Range<Int> { 0..<renderItemCount }
    func selectionQuads(forItemAt index: Int, itemOffset: CGPoint) -> [VVQuadPrimitive] { [] }
    func hoverQuads(forItemAt index: Int, itemOffset: CGPoint) -> [VVQuadPrimitive] { [] }
}

public protocol VVChatTimelineSelectionDelegate: AnyObject {
    func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseDownAt point: CGPoint, clickCount: Int, modifiers: NSEvent.ModifierFlags)
    func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseDraggedTo point: CGPoint, event: NSEvent)
    func chatTimelineMetalViewMouseUp(_ view: VVChatTimelineMetalView)
    func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseMovedTo point: CGPoint)
    func chatTimelineMetalViewMouseExited(_ view: VVChatTimelineMetalView)
}

public extension VVChatTimelineSelectionDelegate {
    func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseMovedTo point: CGPoint) {}
    func chatTimelineMetalViewMouseExited(_ view: VVChatTimelineMetalView) {}
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
    private var trackingAreaRef: NSTrackingArea?

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

    public override func mouseMoved(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        selectionDelegate?.chatTimelineMetalView(self, mouseMovedTo: point)
    }

    public override func mouseExited(with event: NSEvent) {
        selectionDelegate?.chatTimelineMetalViewMouseExited(self)
    }

    public override func resetCursorRects() {
        addCursorRect(bounds, cursor: .iBeam)
    }

    public override func updateTrackingAreas() {
        if let trackingAreaRef {
            removeTrackingArea(trackingAreaRef)
        }

        let options: NSTrackingArea.Options = [
            .mouseMoved,
            .mouseEnteredAndExited,
            .activeInActiveApp,
            .inVisibleRect
        ]
        let tracking = NSTrackingArea(rect: .zero, options: options, owner: self, userInfo: nil)
        addTrackingArea(tracking)
        trackingAreaRef = tracking

        super.updateTrackingAreas()
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

        for index in renderDataSource.visibleRenderIndexes() {
            guard let item = renderDataSource.renderItem(at: index) else { continue }
            if item.frame.maxY < visibleRect.minY - visibilityPadding { continue }
            if item.frame.minY > visibleRect.maxY + visibilityPadding { continue }

            // Each item's scene uses local coordinates (0,0 = item top-left).
            // Offset primitives by the item's absolute position so they render
            // correctly under the single global projection + scroll offset.
            let itemOffset = CGPoint(x: item.frame.origin.x + item.contentOffset.x,
                                     y: item.frame.origin.y + item.contentOffset.y)

            renderScene(item.scene, encoder: encoder, renderer: renderer, imageProvider: renderDataSource, itemOffset: itemOffset)

            let hoverQuads = renderDataSource.hoverQuads(forItemAt: index, itemOffset: itemOffset)
            if !hoverQuads.isEmpty {
                var instances: [QuadInstance] = []
                instances.reserveCapacity(hoverQuads.count)
                for quad in hoverQuads {
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
        let transform = primitive.transform
        switch primitive.kind {
        case .quad(let quad):
            renderQuadPrimitive(quad, transform: transform, offset: o, encoder: encoder, renderer: renderer)

        case .gradientQuad(let quad):
            renderGradientQuad(quad, transform: transform, offset: o, encoder: encoder, renderer: renderer)

        case .line(let line):
            renderLinePrimitive(line, transform: transform, offset: o, encoder: encoder, renderer: renderer)

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
            renderImagePrimitive(image, transform: transform, offset: o, encoder: encoder, renderer: renderer, imageProvider: imageProvider)

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
            let transformedOrigin = transformed(point: underline.origin, by: transform)
            let transformedWidth = transformed(size: CGSize(width: underline.width, height: underline.thickness), by: transform)
            let instance = LineInstance(
                position: SIMD2<Float>(Float(transformedOrigin.x) + o.x, Float(transformedOrigin.y) + o.y),
                width: Float(max(1, transformedWidth.width)),
                height: Float(max(underline.thickness, transformedWidth.height)),
                color: underline.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .path(let path):
            renderPathPrimitive(path, inheritedTransform: transform, offset: o, encoder: encoder, renderer: renderer)
        }
    }

    private func renderGradientQuad(
        _ gradient: VVGradientQuadPrimitive,
        transform: VVTransform2D? = nil,
        offset o: SIMD2<Float> = .zero,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let transformedFrame = transformed(rect: gradient.frame, by: transform)
        let frame = transformedFrame.offsetBy(dx: CGFloat(o.x), dy: CGFloat(o.y)).integral
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
        offset o: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let frame = transformed(rect: quad.frame, by: transform)
        guard frame.width > 0, frame.height > 0 else { return }

        let instance = QuadInstance(
            position: SIMD2<Float>(Float(frame.origin.x) + o.x, Float(frame.origin.y) + o.y),
            size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
            color: SIMD4<Float>(quad.color.x, quad.color.y, quad.color.z, quad.color.w * quad.opacity),
            cornerRadius: Float(quad.cornerRadius)
        )
        if let buffer = renderer.makeBuffer(for: [instance]) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: quad.cornerRadius > 0)
        }

        guard let border = quad.border else { return }
        renderQuadBorder(frame: frame, border: border, cornerRadius: quad.cornerRadius, offset: o, encoder: encoder, renderer: renderer)
    }

    private func renderQuadBorder(
        frame: CGRect,
        border: VVBorder,
        cornerRadius: CGFloat,
        offset o: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        if canRenderBorderAsSingleRing(border) {
            let instance = QuadInstance(
                position: SIMD2<Float>(Float(frame.origin.x) + o.x, Float(frame.origin.y) + o.y),
                size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
                color: border.color,
                cornerRadius: Float(cornerRadius),
                borderWidth: Float(border.widths.top)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: true)
            }
            return
        }

        let segments = borderSegments(for: frame, border: border, cornerRadius: cornerRadius, offset: o)
        guard !segments.isEmpty else { return }
        if let buffer = renderer.makeBuffer(for: segments) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: segments.count, rounded: false)
        }
    }

    private func renderLinePrimitive(
        _ line: VVLinePrimitive,
        transform: VVTransform2D?,
        offset o: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let transformedStart = transformed(point: line.start, by: transform)
        let transformedEnd = transformed(point: line.end, by: transform)
        let segments = dashedSegments(for: VVLinePrimitive(start: transformedStart, end: transformedEnd, thickness: line.thickness, color: line.color, dash: line.dash))
        var instances: [LineInstance] = []
        instances.reserveCapacity(segments.count)

        for segment in segments {
            let minX = min(segment.start.x, segment.end.x)
            let minY = min(segment.start.y, segment.end.y)
            let width = abs(segment.end.x - segment.start.x)
            let height = abs(segment.end.y - segment.start.y)
            instances.append(
                LineInstance(
                    position: SIMD2<Float>(Float(minX) + o.x, Float(minY) + o.y),
                    width: Float(width > 0 ? width : segment.thickness),
                    height: Float(height > 0 ? height : segment.thickness),
                    color: segment.color
                )
            )
        }

        if let buffer = renderer.makeBuffer(for: instances) {
            renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: instances.count)
        }
    }

    private func renderImagePrimitive(
        _ image: VVImagePrimitive,
        transform: VVTransform2D?,
        offset o: SIMD2<Float>,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        imageProvider: VVChatTimelineRenderDataSource
    ) {
        guard let texture = imageProvider.texture(for: image.url) else { return }
        let frame = transformed(rect: image.frame, by: transform)
        let instance = ImageInstance(
            position: SIMD2<Float>(Float(frame.origin.x) + o.x, Float(frame.origin.y) + o.y),
            size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
            cornerRadius: Float(image.cornerRadius),
            opacity: image.opacity,
            grayscale: image.grayscale
        )
        if let buffer = renderer.makeBuffer(for: [instance]) {
            renderer.renderImages(encoder: encoder, instances: buffer, instanceCount: 1, texture: texture)
        }
    }

    private func renderPathPrimitive(
        _ path: VVPathPrimitive,
        inheritedTransform: VVTransform2D?,
        offset o: SIMD2<Float>,
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

        let transformedVertices = path.vertices.map { vertex in
            VVPathVertex(
                position: CGPoint(
                    x: transformed(point: vertex.position, by: combinedTransform).x + CGFloat(o.x),
                    y: transformed(point: vertex.position, by: combinedTransform).y + CGFloat(o.y)
                ),
                stPosition: vertex.stPosition
            )
        }

        guard let buffer = renderer.makeBuffer(for: transformedVertices) else { return }
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
        let rect = transformed(rect: CGRect(origin: .zero, size: size), by: transform)
        return rect.size
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

    private func borderSegments(for frame: CGRect, border: VVBorder, cornerRadius: CGFloat, offset o: SIMD2<Float>) -> [QuadInstance] {
        let widths = border.widths
        let color = border.color
        var segments: [QuadInstance] = []

        func append(rect: CGRect) {
            guard rect.width > 0, rect.height > 0 else { return }
            segments.append(
                QuadInstance(
                    position: SIMD2<Float>(Float(rect.origin.x) + o.x, Float(rect.origin.y) + o.y),
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
            let top = VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.minY), end: CGPoint(x: frame.maxX, y: frame.minY), thickness: max(1, widths.top), color: color, dash: .dashed(on: dashLength, off: gapLength))
            let bottom = VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.maxY), end: CGPoint(x: frame.maxX, y: frame.maxY), thickness: max(1, widths.bottom), color: color, dash: .dashed(on: dashLength, off: gapLength))
            let left = VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.minY), end: CGPoint(x: frame.minX, y: frame.maxY), thickness: max(1, widths.left), color: color, dash: .dashed(on: dashLength, off: gapLength))
            let right = VVLinePrimitive(start: CGPoint(x: frame.maxX, y: frame.minY), end: CGPoint(x: frame.maxX, y: frame.maxY), thickness: max(1, widths.right), color: color, dash: .dashed(on: dashLength, off: gapLength))
            for line in [top, bottom, left, right] {
                for segment in dashedSegments(for: line) {
                    let minX = min(segment.start.x, segment.end.x)
                    let minY = min(segment.start.y, segment.end.y)
                    let width = abs(segment.end.x - segment.start.x)
                    let height = abs(segment.end.y - segment.start.y)
                    append(rect: CGRect(
                        x: minX,
                        y: minY,
                        width: width > 0 ? width : segment.thickness,
                        height: height > 0 ? height : segment.thickness
                    ))
                }
            }
        }

        return segments
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
