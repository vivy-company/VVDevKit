import Foundation
import AppKit
import MetalKit

/// Metal-based gutter view for line numbers and git indicators.
public final class MetalGutterView: MTKView {

    // Use flipped coordinates (Y=0 at top) for proper AppKit integration
    override public var isFlipped: Bool { true }

    // MARK: - Properties

    private let renderer: MetalRenderer
    private var glyphBatch: GlyphBatch
    private var quadBatch: QuadBatch

    private var redrawScheduled = false
    private var backingScaleFactor: CGFloat = 1.0

    // Configuration
    private var lineCount: Int = 0
    private var lineHeight: CGFloat = 20
    private var ascent: CGFloat = 14
    private var font: NSFont = NSFont.monospacedSystemFont(ofSize: 11, weight: .regular)

    // Folding
    public struct FoldRange: Hashable {
        public let startLine: Int
        public let endLine: Int

        public init(startLine: Int, endLine: Int) {
            self.startLine = startLine
            self.endLine = endLine
        }
    }

    private var foldRanges: [FoldRange] = []
    private var foldRangeByStartLine: [Int: FoldRange] = [:]
    private var foldedStartLines: Set<Int> = []

    // Colors
    public var lineNumberColor: NSColor = NSColor.secondaryLabelColor {
        didSet { scheduleRedraw() }
    }
    public var currentLineNumberColor: NSColor = NSColor.labelColor {
        didSet { scheduleRedraw() }
    }
    public var selectedLineNumberColor: NSColor = NSColor.labelColor {
        didSet { scheduleRedraw() }
    }
    public var backgroundColor: NSColor = NSColor.textBackgroundColor {
        didSet { updateClearColor(); scheduleRedraw() }
    }
    public var separatorColor: NSColor = NSColor.separatorColor {
        didSet { scheduleRedraw() }
    }
    public var foldMarkerColor: NSColor = NSColor.secondaryLabelColor {
        didSet { scheduleRedraw() }
    }
    public var foldMarkerActiveColor: NSColor = NSColor.labelColor {
        didSet { scheduleRedraw() }
    }
    public var foldMarkerHoverBackgroundColor: NSColor = NSColor.selectedTextBackgroundColor.withAlphaComponent(0.15) {
        didSet { scheduleRedraw() }
    }
    public var foldMarkerIconScale: CGFloat = 0.55 {
        didSet { scheduleRedraw() }
    }
    public var foldMarkerIconLineWidth: CGFloat = 1.4 {
        didSet { scheduleRedraw() }
    }
    public var foldMarkerHoverPadding: CGFloat = 3 {
        didSet { scheduleRedraw() }
    }
    public var foldMarkerHoverCornerRadius: CGFloat = 3 {
        didSet { scheduleRedraw() }
    }

    // Git hunk colors
    public var addedColor: NSColor = NSColor.systemGreen {
        didSet { scheduleRedraw() }
    }
    public var modifiedColor: NSColor = NSColor.systemBlue {
        didSet { scheduleRedraw() }
    }
    public var deletedColor: NSColor = NSColor.systemRed {
        didSet { scheduleRedraw() }
    }

    // State
    public var scrollOffset: CGFloat = 0 {
        didSet { scheduleRedraw() }
    }

    public var currentLine: Int = 0 {
        didSet { scheduleRedraw() }
    }

    private var gitHunks: [GitHunk] = []
    private var selectedLineRanges: [ClosedRange<Int>] = []

    // Layout
    public var textInsets: NSEdgeInsets = NSEdgeInsets(top: 4, left: 12, bottom: 4, right: 16) {
        didSet { updateWidth(); scheduleRedraw() }
    }
    public var foldMarkerAreaWidth: CGFloat = 12 {
        didSet { updateWidth(); scheduleRedraw() }
    }
    public var foldMarkerSpacing: CGFloat = 6 {
        didSet { updateWidth(); scheduleRedraw() }
    }
    public var minimumWidth: CGFloat = 0 {
        didSet { updateWidth(); scheduleRedraw() }
    }
    private let indicatorWidth: CGFloat = 3
    private let separatorWidth: CGFloat = 0
    private var hoveredFoldLine: Int? {
        didSet {
            if oldValue != hoveredFoldLine {
                scheduleRedraw()
            }
        }
    }

    // Alignment helpers
    public var baselineProvider: ((Int) -> CGFloat?)? {
        didSet { scheduleRedraw() }
    }
    public var visibleLineRangeProvider: ((CGFloat, CGFloat) -> (first: Int, last: Int))? {
        didSet { scheduleRedraw() }
    }
    public var linePresenceProvider: ((Int) -> Bool)? {
        didSet { scheduleRedraw() }
    }
    public var lineForPointProvider: ((CGFloat) -> Int?)?
    public var onToggleFold: ((Int) -> Void)?

    // Optional vertical offset to align gutter with text lines.
    public var verticalOffset: CGFloat = 0 {
        didSet { scheduleRedraw() }
    }

    // MARK: - Git Hunk

    public struct GitHunk {
        public enum Status {
            case added
            case modified
            case deleted
        }

        public let startLine: Int
        public let lineCount: Int
        public let status: Status

        public init(startLine: Int, lineCount: Int, status: Status) {
            self.startLine = startLine
            self.lineCount = lineCount
            self.status = status
        }
    }

    // MARK: - Initialization

    public init(frame: CGRect, renderer: MetalRenderer) {
        self.renderer = renderer
        self.glyphBatch = GlyphBatch(device: renderer.device)
        self.quadBatch = QuadBatch(device: renderer.device)
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
        updateClearColor()
        updateBackingScaleFactor()
        updateDrawableSize()
    }

    // MARK: - Public API

    public func setLineCount(_ count: Int) {
        lineCount = max(0, count)
        updateWidth()
        scheduleRedraw()
    }

    public func setLineHeight(_ height: CGFloat, ascent: CGFloat) {
        lineHeight = height
        self.ascent = ascent
        scheduleRedraw()
    }

    public func setFont(_ font: NSFont) {
        self.font = font
        updateWidth()
        scheduleRedraw()
    }

    public func setGitHunks(_ hunks: [GitHunk]) {
        gitHunks = hunks
        scheduleRedraw()
    }

    public func setFoldRanges(_ ranges: [FoldRange], foldedStartLines: Set<Int>) {
        foldRanges = ranges
        var map: [Int: FoldRange] = [:]
        for range in ranges where map[range.startLine] == nil {
            map[range.startLine] = range
        }
        foldRangeByStartLine = map
        self.foldedStartLines = foldedStartLines
        scheduleRedraw()
    }

    public func setSelectedLineRanges(_ ranges: [ClosedRange<Int>]) {
        selectedLineRanges = mergeLineRanges(ranges)
        scheduleRedraw()
    }

    public func setBackgroundColor(_ color: NSColor) {
        backgroundColor = color
    }

    public var requiredWidth: CGFloat {
        let textWidth = lineNumberColumnWidth
        let calculated = ceil(textInsets.left + textWidth + foldMarkerSpacing + foldMarkerAreaWidth + textInsets.right + indicatorWidth + separatorWidth)
        return max(minimumWidth, calculated)
    }

    // MARK: - Layout / Scale

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

    private func updateWidth() {
        frame.size.width = requiredWidth
    }

    private func updateBackingScaleFactor() {
        let scale = window?.backingScaleFactor ?? NSScreen.main?.backingScaleFactor ?? 1.0
        guard scale > 0 else { return }
        if abs(scale - backingScaleFactor) < 0.001 { return }
        backingScaleFactor = scale
        layer?.contentsScale = scale
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

    // MARK: - Rendering

    override public func draw(_ dirtyRect: NSRect) {
        guard bounds.width > 0, bounds.height > 0 else { return }
        guard let commandBuffer = renderer.commandQueue.makeCommandBuffer(),
              let renderPassDescriptor = currentRenderPassDescriptor,
              let encoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor) else {
            return
        }

        // Use only vertical scroll for gutter shader.
        renderer.beginFrame(viewportSize: bounds.size, scrollOffset: CGPoint(x: 0, y: scrollOffset))

        prepareQuadBatch()
        prepareGlyphBatch()

        if let (buffer, count) = quadBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }

        if let (buffer, count) = glyphBatch.prepareBuffer() {
            renderer.renderGutter(encoder: encoder, instances: buffer, instanceCount: count)
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

        let bgRect = CGRect(x: 0, y: scrollOffset, width: bounds.width, height: bounds.height)
        quadBatch.addQuad(rect: bgRect, color: backgroundColor)

        // No separator (separatorWidth is 0)

        guard !gitHunks.isEmpty else { return }

        let indicatorX = bounds.width - separatorWidth - indicatorWidth
        for hunk in gitHunks {
            let start = hunk.startLine
            let end = hunk.startLine + max(0, hunk.lineCount - 1)
            let visibleRange = visibleLineRange()
            if end < visibleRange.first || start > visibleRange.last {
                continue
            }

            let color: NSColor
            switch hunk.status {
            case .added: color = addedColor
            case .modified: color = modifiedColor
            case .deleted: color = deletedColor
            }

            let y = textInsets.top + CGFloat(hunk.startLine) * lineHeight + verticalOffset
            if hunk.status == .deleted {
                let rect = CGRect(x: indicatorX, y: y, width: indicatorWidth, height: lineHeight / 2)
                quadBatch.addQuad(rect: rect, color: color)
            } else {
                let height = CGFloat(hunk.lineCount) * lineHeight
                let rect = CGRect(x: indicatorX, y: y + 2, width: indicatorWidth, height: max(0, height - 4))
                quadBatch.addQuad(rect: rect, color: color)
            }
        }
    }

    private func prepareGlyphBatch() {
        glyphBatch.clear()

        let visibleRange = visibleLineRange()
        if visibleRange.first > visibleRange.last { return }

        let foldMetrics = foldIconMetrics()
        let mergedSelections = selectedLineRanges
        var selectionIndex = 0

        for lineIndex in visibleRange.first...visibleRange.last {
            if let present = linePresenceProvider, !present(lineIndex) {
                continue
            }

            while selectionIndex < mergedSelections.count && mergedSelections[selectionIndex].upperBound < lineIndex {
                selectionIndex += 1
            }
            let isSelected = selectionIndex < mergedSelections.count && mergedSelections[selectionIndex].contains(lineIndex)

            let baselineY = baselineProvider?(lineIndex) ??
                (textInsets.top + CGFloat(lineIndex) * lineHeight + ascent)

            let lineNumber = String(lineIndex + 1)
            let color: NSColor
            if lineIndex == currentLine {
                color = currentLineNumberColor
            } else if isSelected {
                color = selectedLineNumberColor
            } else {
                color = lineNumberColor
            }
            if foldRangeByStartLine[lineIndex] != nil {
                let isFolded = foldedStartLines.contains(lineIndex)
                let isHovered = hoveredFoldLine == lineIndex
                if isFolded || isHovered {
                    if isHovered,
                       let bgGlyph = renderer.glyphAtlas.customGlyph(
                        kind: .foldHoverBackground,
                        size: foldMetrics.hoverSize,
                        lineWidth: 1,
                        cornerRadius: foldMetrics.hoverCornerRadius
                       ) {
                        let bgX = foldMarkerAreaX + max(0, (foldMarkerAreaWidth - foldMetrics.hoverSize.width) / 2)
                        let bgY = baselineY + verticalOffset - ascent + (lineHeight - foldMetrics.hoverSize.height) / 2
                        addGutterGlyph(bgGlyph, topLeft: CGPoint(x: bgX, y: bgY), color: foldMarkerHoverBackgroundColor)
                    }

                    if let iconGlyph = renderer.glyphAtlas.customGlyph(
                        kind: isFolded ? .foldChevronClosed : .foldChevronOpen,
                        size: foldMetrics.iconSize,
                        lineWidth: foldMetrics.lineWidth
                    ) {
                        let iconX = foldMarkerAreaX + max(0, (foldMarkerAreaWidth - foldMetrics.iconSize.width) / 2)
                        let iconY = baselineY + verticalOffset - ascent + (lineHeight - foldMetrics.iconSize.height) / 2
                        let iconColor = isHovered || isFolded ? foldMarkerActiveColor : foldMarkerColor
                        addGutterGlyph(iconGlyph, topLeft: CGPoint(x: iconX, y: iconY), color: iconColor)
                    } else {
                        let markerChar = foldMarkerCharacter(isFolded: isFolded)
                        let marker = String(markerChar)
                        let markerWidth = renderer.glyphAtlas.glyph(for: markerChar, variant: .regular)?.advance ?? 8
                        let markerX = foldMarkerAreaX + max(0, (foldMarkerAreaWidth - markerWidth) / 2)
                        let iconColor = isHovered || isFolded ? foldMarkerActiveColor : foldMarkerColor
                        addGutterSymbol(marker, baselineY: baselineY + verticalOffset, x: markerX, color: iconColor)
                    }
                }
            }
            addGutterText(lineNumber, baselineY: baselineY + verticalOffset, color: color)
        }

        if visibleRange.last >= lineCount {
            let tildeLine = max(visibleRange.first, lineCount)
            let baselineY = baselineProvider?(tildeLine) ??
                (textInsets.top + CGFloat(tildeLine) * lineHeight + ascent)
            addGutterText("~", baselineY: baselineY + verticalOffset, color: lineNumberColor.withAlphaComponent(0.55))
        }
    }

    private func visibleLineRange() -> (first: Int, last: Int) {
        if let provider = visibleLineRangeProvider {
            return provider(scrollOffset, bounds.height)
        }

        guard lineHeight > 0 && lineHeight.isFinite else { return (0, -1) }
        let visibleTop = scrollOffset - textInsets.top
        let visibleBottom = scrollOffset + bounds.height - textInsets.top
        let firstLineRaw = floor(visibleTop / lineHeight)
        let lastLineRaw = ceil(visibleBottom / lineHeight)
        let first = max(0, Int(firstLineRaw))
        let last = min(lineCount - 1, Int(lastLineRaw))
        return (first, last)
    }

    private func addGutterText(_ text: String, baselineY: CGFloat, color: NSColor) {
        let characters = Array(text)
        guard !characters.isEmpty else { return }

        var glyphs: [CachedGlyph] = []
        glyphs.reserveCapacity(characters.count)
        var totalWidth: CGFloat = 0

        for ch in characters {
            if let cached = renderer.glyphAtlas.glyph(for: ch, variant: .regular) {
                glyphs.append(cached)
                totalWidth += cached.advance
            }
        }

        guard totalWidth > 0 else { return }

        let availableWidth = lineNumberColumnWidth
        let startX = lineNumberLeftInset + max(0, availableWidth - totalWidth)

        var penX = startX
        let colorSimd = color.simdColor
        for cached in glyphs {
            glyphBatch.addGlyph(
                cached: cached,
                screenPosition: CGPoint(x: penX, y: baselineY),
                color: colorSimd
            )
            penX += cached.advance
        }
    }

    private var lineNumberLeftInset: CGFloat {
        textInsets.left
    }

    private var lineNumberColumnWidth: CGFloat {
        let maxLine = max(1, lineCount)
        let sample = String(maxLine)
        return ceil((sample as NSString).size(withAttributes: [.font: font]).width)
    }

    private var foldMarkerAreaX: CGFloat {
        textInsets.left + lineNumberColumnWidth + foldMarkerSpacing
    }

    private func addGutterSymbol(_ text: String, baselineY: CGFloat, x: CGFloat, color: NSColor) {
        let characters = Array(text)
        guard !characters.isEmpty else { return }

        var glyphs: [CachedGlyph] = []
        glyphs.reserveCapacity(characters.count)
        var totalWidth: CGFloat = 0

        for ch in characters {
            if let cached = renderer.glyphAtlas.glyph(for: ch, variant: .regular) {
                glyphs.append(cached)
                totalWidth += cached.advance
            }
        }

        guard totalWidth > 0 else { return }

        var penX = x
        let colorSimd = color.simdColor
        for cached in glyphs {
            glyphBatch.addGlyph(
                cached: cached,
                screenPosition: CGPoint(x: penX, y: baselineY),
                color: colorSimd
            )
            penX += cached.advance
        }
    }

    private func addGutterGlyph(_ glyph: CachedGlyph, topLeft: CGPoint, color: NSColor) {
        glyphBatch.addGlyph(
            cached: glyph,
            screenPosition: topLeft,
            color: color.simdColor
        )
    }

    private struct FoldIconMetrics {
        let iconSize: CGSize
        let lineWidth: CGFloat
        let hoverSize: CGSize
        let hoverCornerRadius: CGFloat
    }

    private func foldIconMetrics() -> FoldIconMetrics {
        let iconSide = max(6, min(foldMarkerAreaWidth - 2, lineHeight * foldMarkerIconScale))
        let lineWidth = max(1, min(foldMarkerIconLineWidth, iconSide * 0.25))
        let hoverPadding = max(1, foldMarkerHoverPadding)
        let hoverSide = min(foldMarkerAreaWidth, lineHeight - 2, iconSide + hoverPadding * 2)
        let hoverCorner = min(foldMarkerHoverCornerRadius, hoverSide * 0.45)

        return FoldIconMetrics(
            iconSize: CGSize(width: iconSide, height: iconSide),
            lineWidth: lineWidth,
            hoverSize: CGSize(width: hoverSide, height: hoverSide),
            hoverCornerRadius: hoverCorner
        )
    }

    private func mergeLineRanges(_ ranges: [ClosedRange<Int>]) -> [ClosedRange<Int>] {
        guard !ranges.isEmpty else { return [] }
        let sorted = ranges.sorted { lhs, rhs in
            if lhs.lowerBound != rhs.lowerBound { return lhs.lowerBound < rhs.lowerBound }
            return lhs.upperBound < rhs.upperBound
        }
        var merged: [ClosedRange<Int>] = []
        for range in sorted {
            if let last = merged.last, range.lowerBound <= last.upperBound + 1 {
                merged[merged.count - 1] = last.lowerBound...max(last.upperBound, range.upperBound)
            } else {
                merged.append(range)
            }
        }
        return merged
    }

    private func foldMarkerCharacter(isFolded: Bool) -> Character {
        let preferred: Character = isFolded ? "▾" : "▸"
        if renderer.glyphAtlas.glyph(for: preferred, variant: .regular) != nil {
            return preferred
        }
        return isFolded ? "v" : ">"
    }

    // MARK: - Mouse Events

    public override func mouseDown(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        let adjustedY = point.y - verticalOffset
        guard let line = lineForPointProvider?(adjustedY) else { return }
        guard foldRangeByStartLine[line] != nil else { return }
        let markerLeft = foldMarkerAreaX
        let markerRight = markerLeft + foldMarkerAreaWidth
        guard point.x >= markerLeft && point.x <= markerRight else { return }
        onToggleFold?(line)
    }

    public override func mouseMoved(with event: NSEvent) {
        updateHoverState(with: event)
    }

    public override func mouseExited(with event: NSEvent) {
        hoveredFoldLine = nil
    }

    public override func updateTrackingAreas() {
        super.updateTrackingAreas()
        if let trackingArea {
            removeTrackingArea(trackingArea)
        }
        let options: NSTrackingArea.Options = [.activeInKeyWindow, .mouseMoved, .mouseEnteredAndExited, .inVisibleRect]
        let area = NSTrackingArea(rect: bounds, options: options, owner: self, userInfo: nil)
        trackingArea = area
        addTrackingArea(area)
    }

    private var trackingArea: NSTrackingArea?

    private func updateHoverState(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        let adjustedY = point.y - verticalOffset
        guard let line = lineForPointProvider?(adjustedY) else {
            hoveredFoldLine = nil
            return
        }
        guard foldRangeByStartLine[line] != nil else {
            hoveredFoldLine = nil
            return
        }
        let markerLeft = foldMarkerAreaX
        let markerRight = markerLeft + foldMarkerAreaWidth
        guard point.x >= markerLeft && point.x <= markerRight else {
            hoveredFoldLine = nil
            return
        }
        hoveredFoldLine = line
    }
}
