import Foundation
import AppKit
import MetalKit

/// Metal-rendered helix status bar.
public final class MetalStatusBarView: MTKView {

    override public var isFlipped: Bool { true }

    private let renderer: MetalRenderer
    private var glyphBatch: GlyphBatch
    private var quadBatch: QuadBatch

    private var redrawScheduled = false
    private var backingScaleFactor: CGFloat = 1.0

    private var font: NSFont
    private var lineHeight: CGFloat = 16
    private var baselineOffset: CGFloat = 12

    public var backgroundColor: NSColor = NSColor.black.withAlphaComponent(0.55) {
        didSet { updateClearColor(); scheduleRedraw() }
    }
    public var borderColor: NSColor = NSColor.white.withAlphaComponent(0.15) {
        didSet { scheduleRedraw() }
    }
    public var textColor: NSColor = NSColor.white {
        didSet { scheduleRedraw() }
    }
    public var secondaryTextColor: NSColor = NSColor.white.withAlphaComponent(0.85) {
        didSet { scheduleRedraw() }
    }
    public var modeBackgroundColor: NSColor = NSColor.systemBlue {
        didSet { scheduleRedraw() }
    }
    public var modeTextColor: NSColor = NSColor.black {
        didSet { scheduleRedraw() }
    }

    public var textInsets: NSEdgeInsets = NSEdgeInsets(top: 0, left: 10, bottom: 0, right: 10) {
        didSet { scheduleRedraw() }
    }
    public var modePadding: CGSize = CGSize(width: 8, height: 2) {
        didSet { scheduleRedraw() }
    }

    private var leftText: String = ""
    private var rightText: String = ""

    public init(frame: CGRect, renderer: MetalRenderer, font: NSFont) {
        self.renderer = renderer
        self.glyphBatch = GlyphBatch(device: renderer.device)
        self.quadBatch = QuadBatch(device: renderer.device)
        self.font = font
        super.init(frame: frame, device: renderer.device)
        commonInit()
    }

    required init(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    private func commonInit() {
        colorPixelFormat = .bgra8Unorm
        enableSetNeedsDisplay = true
        isPaused = true
        preferredFramesPerSecond = 60
        framebufferOnly = true
        if let metalLayer = layer as? CAMetalLayer {
            metalLayer.maximumDrawableCount = 2
        }
        updateBackingScaleFactor()
        updateFontMetrics()
        updateClearColor()
        updateDrawableSize()
    }

    public func setText(left: String, right: String) {
        if leftText == left && rightText == right {
            return
        }
        leftText = left
        rightText = right
        scheduleRedraw()
    }

    public func setFont(_ font: NSFont) {
        self.font = font
        updateFontMetrics()
        scheduleRedraw()
    }

    override public func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        updateBackingScaleFactor()
        updateDrawableSize()
    }

    override public func viewDidChangeBackingProperties() {
        super.viewDidChangeBackingProperties()
        updateBackingScaleFactor()
        updateDrawableSize()
    }

    override public func layout() {
        super.layout()
        updateDrawableSize()
    }

    private func updateBackingScaleFactor() {
        let scale = window?.backingScaleFactor ?? NSScreen.main?.backingScaleFactor ?? 1.0
        guard scale > 0 else { return }
        if abs(scale - backingScaleFactor) < 0.001 { return }
        backingScaleFactor = scale
        layer?.contentsScale = scale
        updateFontMetrics()
    }

    private func updateDrawableSize() {
        guard bounds.width > 0, bounds.height > 0, bounds.width.isFinite, bounds.height.isFinite else {
            return
        }
        let size = CGSize(width: bounds.width * backingScaleFactor, height: bounds.height * backingScaleFactor)
        if size.width <= 0 || size.height <= 0 {
            return
        }
        if drawableSize != size {
            drawableSize = size
        }
    }

    private func updateClearColor() {
        if let rgb = backgroundColor.usingColorSpace(.sRGB) {
            clearColor = MTLClearColor(
                red: Double(rgb.redComponent),
                green: Double(rgb.greenComponent),
                blue: Double(rgb.blueComponent),
                alpha: Double(rgb.alphaComponent)
            )
        }
    }

    private func updateFontMetrics() {
        let ctFont = font as CTFont
        let ascent = CTFontGetAscent(ctFont)
        let descent = CTFontGetDescent(ctFont)
        let leading = CTFontGetLeading(ctFont)
        let naturalLineHeight = ascent + descent + leading
        lineHeight = ceil(naturalLineHeight * backingScaleFactor) / backingScaleFactor
        let extraSpace = lineHeight - naturalLineHeight
        baselineOffset = round((extraSpace / 2 + ascent) * backingScaleFactor) / backingScaleFactor
    }

    // MARK: - Rendering

    override public func draw(_ dirtyRect: NSRect) {
        guard bounds.width > 0, bounds.height > 0 else { return }
        guard let commandBuffer = renderer.commandQueue.makeCommandBuffer(),
              let renderPassDescriptor = currentRenderPassDescriptor,
              let encoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor) else {
            return
        }

        renderer.beginFrame(viewportSize: bounds.size, scrollOffset: .zero)

        prepareQuadBatch()
        prepareGlyphBatch()

        if let (buffer, count) = quadBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }

        if let (buffer, count) = glyphBatch.prepareBuffer() {
            renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: count)
        }

        encoder.endEncoding()

        if let drawable = currentDrawable {
            commandBuffer.present(drawable)
        }

        commandBuffer.commit()
    }

    private func scheduleRedraw() {
        guard !redrawScheduled else { return }
        redrawScheduled = true
        DispatchQueue.main.async { [weak self] in
            guard let self = self else { return }
            self.redrawScheduled = false
            self.setNeedsDisplay(self.bounds)
        }
    }

    private func prepareQuadBatch() {
        quadBatch.clear()
        let bgRect = CGRect(x: 0, y: 0, width: bounds.width, height: bounds.height)
        quadBatch.addQuad(rect: bgRect, color: backgroundColor)

        let borderHeight = max(1.0 / backingScaleFactor, 1.0)
        let borderRect = CGRect(x: 0, y: bounds.height - borderHeight, width: bounds.width, height: borderHeight)
        quadBatch.addQuad(rect: borderRect, color: borderColor)

        if !leftText.isEmpty {
            let leftWidth = textWidth(leftText)
            let rectHeight = max(0, bounds.height - modePadding.height * 2)
            let rect = CGRect(
                x: textInsets.left,
                y: modePadding.height,
                width: leftWidth + modePadding.width * 2,
                height: rectHeight
            )
            quadBatch.addQuad(rect: rect, color: modeBackgroundColor)
        }
    }

    private func prepareGlyphBatch() {
        glyphBatch.clear()

        guard bounds.width > 0 else { return }

        let baselineY = (bounds.height - lineHeight) / 2 + baselineOffset
        let leftColor = modeTextColor.simdColor
        let rightColor = secondaryTextColor.simdColor

        if !leftText.isEmpty {
            addText(leftText, x: textInsets.left + modePadding.width, baselineY: baselineY, color: leftColor)
        }

        if !rightText.isEmpty {
            let rightWidth = textWidth(rightText)
            let startX = max(textInsets.left, bounds.width - textInsets.right - rightWidth)
            addText(rightText, x: startX, baselineY: baselineY, color: rightColor)
        }
    }

    private func addText(_ text: String, x: CGFloat, baselineY: CGFloat, color: SIMD4<Float>) {
        var penX = x
        for ch in text {
            guard let cached = renderer.glyphAtlas.glyph(for: ch, variant: .regular) else { continue }
            glyphBatch.addGlyph(
                cached: cached,
                screenPosition: CGPoint(x: penX, y: baselineY),
                color: color
            )
            penX += cached.advance
        }
    }

    private func textWidth(_ text: String) -> CGFloat {
        var width: CGFloat = 0
        for ch in text {
            if let cached = renderer.glyphAtlas.glyph(for: ch, variant: .regular) {
                width += cached.advance
            }
        }
        return width
    }
}
