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
    public let orderedPrimitiveIndices: [Int]

    public init(id: String, frame: CGRect, contentOffset: CGPoint, scene: VVScene, orderedPrimitiveIndices: [Int]) {
        self.id = id
        self.frame = frame
        self.contentOffset = contentOffset
        self.scene = scene
        self.orderedPrimitiveIndices = orderedPrimitiveIndices
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
    func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseDownAt point: CGPoint, clickCount: Int, modifiers: VVInputModifiers)
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
    private var sceneRenderer: MarkdownScenePrimitiveRenderer?
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
        selectionDelegate?.chatTimelineMetalView(
            self,
            mouseDownAt: point,
            clickCount: event.clickCount,
            modifiers: inputModifiers(from: event.modifierFlags)
        )
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
            sceneRenderer = MarkdownScenePrimitiveRenderer(baseFont: font)
        } else {
            renderer = nil
            sceneRenderer = nil
        }
    }

    private func inputModifiers(from flags: NSEvent.ModifierFlags) -> VVInputModifiers {
        var modifiers: VVInputModifiers = []
        if flags.contains(.shift) { modifiers.insert(.shift) }
        if flags.contains(.control) { modifiers.insert(.control) }
        if flags.contains(.option) { modifiers.insert(.option) }
        if flags.contains(.command) { modifiers.insert(.command) }
        return modifiers
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

            renderScene(
                item.scene,
                orderedPrimitiveIndices: item.orderedPrimitiveIndices,
                encoder: encoder,
                renderer: renderer,
                imageProvider: renderDataSource,
                itemOffset: itemOffset
            )

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
        renderer.recycleTransientBuffers(after: commandBuffer)
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
    }

    private func renderScene(
        _ scene: VVScene,
        orderedPrimitiveIndices: [Int],
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        imageProvider: VVChatTimelineRenderDataSource,
        itemOffset: CGPoint = .zero
    ) {
        let sceneRenderer = sceneRenderer ?? MarkdownScenePrimitiveRenderer(baseFont: baseFont)
        self.sceneRenderer = sceneRenderer
        sceneRenderer.updateBehavior(
            MarkdownSceneRenderingBehavior(
                imageTextureProvider: { url in imageProvider.texture(for: url) },
                shouldUnderlineLinkRun: { $0.style.isLink },
                missingImageBehavior: MarkdownSceneRenderingBehavior.MissingImageBehavior.skip
            )
        )
        sceneRenderer.renderScene(
            scene,
            orderedPrimitiveIndices: orderedPrimitiveIndices,
            encoder: encoder,
            renderer: renderer,
            itemOffset: itemOffset,
            scissorRectForClip: { [weak self] in self?.scissorRect(for: $0) ?? MTLScissorRect(x: 0, y: 0, width: 0, height: 0) },
            fullScissorRect: { [weak self] in self?.fullScissorRect() ?? MTLScissorRect(x: 0, y: 0, width: 0, height: 0) }
        )
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
