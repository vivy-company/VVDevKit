import Foundation
import MetalKit
import AppKit
import QuartzCore

/// Metal-based text view for code rendering
public final class MetalTextView: MTKView {

    // Use flipped coordinates (Y=0 at top) for proper AppKit integration
    override public var isFlipped: Bool { true }

    // Set I-beam cursor for text editing
    override public func resetCursorRects() {
        addCursorRect(bounds, cursor: .iBeam)
    }

    // MARK: - Properties

    public private(set) var renderer: MetalRenderer!
    public private(set) var layoutEngine: TextLayoutEngine!

    private var glyphBatch: GlyphBatch!
    private var selectionBatch: QuadBatch!
    private var cursorBatch: QuadBatch!
    private var lineHighlightBatch: QuadBatch!
    private var indentGuideBatch: QuadBatch!
    private var activeIndentGuideBatch: QuadBatch!
    private var bracketMatchBatch: QuadBatch!

    // Text content
    private var lines: [String] = []
    private var lineStarts: [Int] = []
    private var lineLengths: [Int] = []
    private var lineLayouts: [Int: LineLayout] = [:]
    private var maxLineLength: Int = 0
    private var maxLineWidth: CGFloat = 0
    private var estimatedCharWidth: CGFloat = 8
    private var contentSizeUpdateScheduled = false

    // Syntax highlighting
    private var coloredRanges: [ColoredRange] = []
    private var defaultTextColor: SIMD4<Float> = SIMD4<Float>(1, 1, 1, 1)
    private var backgroundColor: NSColor = .black
    private var bracketMatchRanges: [NSRange] = []
    private var indentGuideSegments: [IndentGuideSegment] = []
    private var activeIndentGuideSegments: [IndentGuideSegment] = []
    private var indentGuideColumnsByLine: [[Int]] = []
    private var activeIndentGuideColumnsByLine: [Int?] = []

    // Folding (line-based)
    private var foldedLineRanges: [ClosedRange<Int>] = []
    private var visibleLineForDocumentLine: [Int] = []
    private var documentLineForVisibleLine: [Int] = []
    private var visibleLineCount: Int = 0
    private var foldedRangeByStartLine: [Int: ClosedRange<Int>] = [:]

    // Selection state
    private var selectionRanges: [NSRange] = []
    private var cursorLine: Int = 0
    private var cursorColumn: Int = 0
    private var cursorPositions: [(line: Int, column: Int)] = []

    // Scroll state
    public var scrollOffset: CGPoint = .zero {
        didSet {
            scheduleRedraw()
        }
    }

    public var onContentSizeChange: (() -> Void)?

    // Render coalescing - prevents excessive IOSurface allocations
    private var redrawScheduled = false

    // Configuration
    public private(set) var textInsets: NSEdgeInsets = NSEdgeInsets(top: 4, left: 4, bottom: 4, right: 4)

    private var currentFont: NSFont = NSFont.monospacedSystemFont(ofSize: 13, weight: .regular)
    private var lineHeightMultiplier: CGFloat = 1.4
    private var backingScaleFactor: CGFloat = 1.0

    // Theme colors
    public var selectionColor: NSColor = NSColor.selectedTextBackgroundColor
    public var cursorColor: NSColor = .white
    public var currentLineHighlightColor: NSColor = NSColor.white.withAlphaComponent(0.1)
    public var indentGuideColor: NSColor = NSColor.white.withAlphaComponent(0.08) {
        didSet { scheduleRedraw() }
    }
    public var indentGuideLinePadding: CGFloat = 0 {
        didSet { scheduleRedraw() }
    }
    public var indentGuideLineWidth: CGFloat = 1 {
        didSet { scheduleRedraw() }
    }
    public var activeIndentGuideColor: NSColor = NSColor.systemBlue.withAlphaComponent(0.45) {
        didSet { scheduleRedraw() }
    }
    public var activeIndentGuideLineWidth: CGFloat = 1.5 {
        didSet { scheduleRedraw() }
    }
    public var bracketHighlightColor: NSColor = NSColor.systemBlue.withAlphaComponent(0.25) {
        didSet { scheduleRedraw() }
    }
    public var foldPlaceholderColor: NSColor = NSColor.secondaryLabelColor {
        didSet { scheduleRedraw() }
    }
    public var foldPlaceholder: String = "⋯" {
        didSet { scheduleRedraw() }
    }

    public enum CursorStyle {
        case bar
        case block
    }

    public var cursorStyle: CursorStyle = .bar {
        didSet {
            updateCursorBlinkTimer()
            scheduleRedraw()
        }
    }

    private var cursorBlinkTimer: Timer?
    private let cursorBlinkInterval: TimeInterval = 0.5
    private let cursorBlinkSuspendDuration: TimeInterval = 0.15
    private var cursorBlinkVisible: Bool = true
    private var lastCursorMovementTime: CFTimeInterval = 0

    // Delegates
    public weak var textDelegate: MetalTextViewDelegate?

    public private(set) var lastMouseModifiers: NSEvent.ModifierFlags = []
    public private(set) var lastClickCount: Int = 0

    // MARK: - Initialization

    public init(frame: CGRect, device: MTLDevice, font: NSFont) {
        super.init(frame: frame, device: device)
        commonInit(font: font)
    }

    required init(coder: NSCoder) {
        super.init(coder: coder)
        if let device = MTLCreateSystemDefaultDevice() {
            self.device = device
            commonInit(font: NSFont.monospacedSystemFont(ofSize: 13, weight: .regular))
        }
    }

    private func commonInit(font: NSFont) {
        guard let device = self.device else { return }
        currentFont = font

        // Configure MTKView
        colorPixelFormat = .bgra8Unorm
        clearColor = MTLClearColor(red: 0.1, green: 0.1, blue: 0.1, alpha: 1.0)
        enableSetNeedsDisplay = true
        isPaused = true
        preferredFramesPerSecond = 60
        framebufferOnly = true
        if let metalLayer = layer as? CAMetalLayer {
            metalLayer.maximumDrawableCount = 2
        }

        // Initialize renderer
        do {
            renderer = try MetalRenderer(device: device, baseFont: font)
        } catch {
            print("Failed to initialize MetalRenderer: \(error)")
            return
        }

        // Initialize layout engine
        let initialScale = window?.backingScaleFactor ?? NSScreen.main?.backingScaleFactor ?? 1.0
        backingScaleFactor = max(1.0, initialScale)
        layoutEngine = TextLayoutEngine(font: font, lineHeightMultiplier: lineHeightMultiplier, scaleFactor: backingScaleFactor)

        // Initialize batches
        glyphBatch = GlyphBatch(device: device)
        selectionBatch = QuadBatch(device: device)
        cursorBatch = QuadBatch(device: device)
        lineHighlightBatch = QuadBatch(device: device)
        indentGuideBatch = QuadBatch(device: device)
        activeIndentGuideBatch = QuadBatch(device: device)
        bracketMatchBatch = QuadBatch(device: device)

        updateBackingScaleFactor()
        updateDrawableSize()
    }

    // MARK: - Render Coalescing

    /// Schedule a redraw on the next runloop iteration. Multiple calls coalesce into one redraw.
    private func scheduleRedraw() {
        guard !redrawScheduled else { return }
        redrawScheduled = true
        DispatchQueue.main.async { [weak self] in
            guard let self = self else { return }
            self.redrawScheduled = false
            self.setNeedsDisplay(self.bounds)
        }
    }

    // MARK: - Public API

    public var lineCount: Int {
        lines.count
    }

    /// Set the text content
    public func setText(_ text: String) {
        let parts = text.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        lines = parts.isEmpty ? [""] : parts
        lineStarts.removeAll(keepingCapacity: true)
        lineLengths.removeAll(keepingCapacity: true)
        lineStarts.reserveCapacity(lines.count)
        lineLengths.reserveCapacity(lines.count)
        maxLineLength = 0
        var offset = 0
        for (index, line) in lines.enumerated() {
            lineStarts.append(offset)
            let length = (line as NSString).length
            lineLengths.append(length)
            maxLineLength = max(maxLineLength, length)
            offset += length
            if index < lines.count - 1 {
                offset += 1
            }
        }
        rebuildVisibleLineMap()
        invalidateLayout()
        onContentSizeChange?()
        scheduleRedraw()
    }

    public func setTextInsets(_ insets: NSEdgeInsets) {
        textInsets = insets
        invalidateLayout()
        onContentSizeChange?()
        scheduleRedraw()
    }

    /// Apply an incremental text edit without rebuilding the entire layout cache.
    public func applyEdit(range: NSRange, replacement: String) {
        guard var lineRange = lineRangeForRange(range) else {
            return
        }

        let startLine = lineRange.lowerBound
        var endLine = lineRange.upperBound
        let endLineEnd = lineStartOffsetUTF16(endLine) + lineUTF16Length(endLine)
        var includeTrailingNewline = false
        if range.location + range.length > endLineEnd {
            if endLine < lines.count - 1 {
                endLine += 1
                lineRange = startLine...endLine
            } else {
                includeTrailingNewline = true
            }
        }
        let segmentStart = lineStartOffsetUTF16(startLine)

        var segment = lines[startLine...endLine].joined(separator: "\n")
        if includeTrailingNewline {
            segment.append("\n")
        }

        let localRange = NSRange(location: max(0, range.location - segmentStart), length: range.length)
        let mutable = NSMutableString(string: segment)
        if localRange.location + localRange.length <= mutable.length {
            mutable.replaceCharacters(in: localRange, with: replacement)
        } else {
            mutable.replaceCharacters(in: NSRange(location: localRange.location, length: max(0, mutable.length - localRange.location)), with: replacement)
        }

        var newLines = (mutable as String).split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        if newLines.isEmpty {
            newLines = [""]
        }
        let oldLineCount = lines.count
        let removedLineCount = endLine - startLine + 1
        let removedMax = lineLengths[startLine...endLine].max() ?? 0

        lines.replaceSubrange(startLine...endLine, with: newLines)
        let newLineCount = lines.count

        if startLine < lineStarts.count {
            lineStarts.removeSubrange(startLine...)
            lineLengths.removeSubrange(startLine...)
        }

        var offset = segmentStart
        for index in startLine..<lines.count {
            lineStarts.append(offset)
            let length = (lines[index] as NSString).length
            lineLengths.append(length)
            offset += length
            if index < lines.count - 1 {
                offset += 1
            }
        }

        let newMax = newLines.map { ($0 as NSString).length }.max() ?? 0
        if removedMax >= maxLineLength || newMax > maxLineLength {
            maxLineLength = lineLengths.max() ?? 0
            maxLineWidth = 0
        } else {
            maxLineLength = max(maxLineLength, newMax)
        }

        if newLineCount != oldLineCount {
            let deltaLines = newLineCount - oldLineCount
            let lineHeight = layoutEngine.calculatedLineHeight
            var shifted: [Int: LineLayout] = [:]
            shifted.reserveCapacity(lineLayouts.count)

            for (index, layout) in lineLayouts {
                if index < startLine {
                    shifted[index] = layout
                } else if index > endLine {
                    let newIndex = index + deltaLines
                    let newYOffset = textInsets.top + CGFloat(newIndex) * lineHeight
                    let updatedLayout = LineLayout(
                        lineIndex: newIndex,
                        yOffset: newYOffset,
                        height: layout.height,
                        baselineOffset: layout.baselineOffset,
                        glyphs: layout.glyphs
                    )
                    shifted[newIndex] = updatedLayout
                }
            }

            lineLayouts = shifted
            maxLineWidth = 0
            onContentSizeChange?()
        } else {
            for lineIndex in startLine..<(startLine + max(removedLineCount, newLines.count)) {
                lineLayouts.removeValue(forKey: lineIndex)
            }
        }

        rebuildVisibleLineMap()
        invalidateLayout()
        onContentSizeChange?()
        scheduleRedraw()
    }

    /// Set syntax highlighting
    public func setHighlights(_ ranges: [ColoredRange], invalidating range: NSRange? = nil) {
        coloredRanges = ranges
        if let range = range {
            invalidateLayout(in: range)
        } else {
            invalidateLayout()
        }
        scheduleRedraw()
    }

    /// Set bracket match highlight ranges
    public func setBracketMatchRanges(_ ranges: [NSRange]) {
        bracketMatchRanges = ranges
        scheduleRedraw()
    }

    public struct IndentGuideSegment: Hashable {
        public var startLine: Int
        public var endLine: Int
        public let column: Int

        public init(startLine: Int, endLine: Int, column: Int) {
            self.startLine = startLine
            self.endLine = endLine
            self.column = column
        }
    }

    /// Set indent guide segments (document line ranges + column)
    public func setIndentGuideSegments(_ segments: [IndentGuideSegment]) {
        indentGuideSegments = segments
        scheduleRedraw()
    }

    public func setActiveIndentGuideSegments(_ segments: [IndentGuideSegment]) {
        activeIndentGuideSegments = segments
        scheduleRedraw()
    }

    /// Set folded line ranges (0-based line indices, inclusive)
    public func setFoldedLineRanges(_ ranges: [ClosedRange<Int>]) {
        foldedLineRanges = ranges
        var map: [Int: ClosedRange<Int>] = [:]
        for range in ranges where map[range.lowerBound] == nil {
            map[range.lowerBound] = range
        }
        foldedRangeByStartLine = map
        rebuildVisibleLineMap()
        invalidateLayout()
        onContentSizeChange?()
        scheduleRedraw()
    }

    /// Set the default text color
    public func setDefaultTextColor(_ color: NSColor) {
        defaultTextColor = color.simdColor
        scheduleRedraw()
    }

    /// Set selection
    public func setSelection(_ ranges: [NSRange]) {
        selectionRanges = ranges
        scheduleRedraw()
    }

    /// Set cursor position
    public func setCursor(line: Int, column: Int) {
        cursorLine = line
        cursorColumn = column
        cursorPositions = [(line, column)]
        lastCursorMovementTime = CACurrentMediaTime()
        cursorBlinkVisible = true
        scheduleRedraw()
    }

    public func setCursors(_ positions: [(line: Int, column: Int)], primaryIndex: Int = 0) {
        cursorPositions = positions
        if !positions.isEmpty {
            let clampedIndex = max(0, min(primaryIndex, positions.count - 1))
            cursorLine = positions[clampedIndex].line
            cursorColumn = positions[clampedIndex].column
        }
        lastCursorMovementTime = CACurrentMediaTime()
        cursorBlinkVisible = true
        scheduleRedraw()
    }

    /// Update font
    public func updateFont(_ font: NSFont, lineHeightMultiplier: CGFloat = 1.4) {
        currentFont = font
        self.lineHeightMultiplier = lineHeightMultiplier
        renderer.updateFont(font, scaleFactor: backingScaleFactor)
        layoutEngine.updateFont(font, lineHeightMultiplier: lineHeightMultiplier, scaleFactor: backingScaleFactor)
        invalidateLayout()
        updateEstimatedCharWidth()
        onContentSizeChange?()
        scheduleRedraw()
    }

    /// Set background color
    public func setBackgroundColor(_ color: NSColor) {
        backgroundColor = color
        if let rgb = color.usingColorSpace(.sRGB) {
            clearColor = MTLClearColor(
                red: Double(rgb.redComponent),
                green: Double(rgb.greenComponent),
                blue: Double(rgb.blueComponent),
                alpha: Double(rgb.alphaComponent)
            )
        }
        scheduleRedraw()
    }

    /// Get content size
    public var contentSize: CGSize {
        let effectiveLines = max(1, visibleLineCount)
        let height = CGFloat(effectiveLines) * layoutEngine.calculatedLineHeight + textInsets.top + textInsets.bottom
        let estimatedWidth = CGFloat(maxLineLength) * estimatedCharWidth
        let contentWidth = max(maxLineWidth, estimatedWidth)

        return CGSize(
            width: contentWidth + textInsets.left + textInsets.right,
            height: height
        )
    }

    /// Get line height
    public var lineHeight: CGFloat {
        layoutEngine.calculatedLineHeight
    }

    // MARK: - Rendering

    override public func draw(_ dirtyRect: NSRect) {
        guard bounds.width > 0, bounds.height > 0 else { return }
        guard let renderer = renderer,
              let commandBuffer = renderer.commandQueue.makeCommandBuffer(),
              let renderPassDescriptor = currentRenderPassDescriptor,
              let encoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor) else {
            return
        }

        // Begin frame with scroll offset for viewport-sized rendering
        renderer.beginFrame(viewportSize: bounds.size, scrollOffset: scrollOffset)

        // Prepare batches
        prepareGlyphBatch()
        prepareIndentGuideBatch()
        prepareActiveIndentGuideBatch()
        prepareSelectionBatch()
        prepareBracketMatchBatch()
        prepareCursorBatch()
        prepareLineHighlightBatch()

        // Render current line highlight
        renderCurrentLineHighlight(encoder: encoder)

        // Render indent guides
        if let (buffer, count) = indentGuideBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }
        if let (buffer, count) = activeIndentGuideBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }

        // Render selections
        if let (buffer, count) = selectionBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }

        // Render bracket match highlights
        if let (buffer, count) = bracketMatchBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }

        // Render glyphs
        if let (buffer, count) = glyphBatch.prepareBuffer() {
            renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: count)
        }

        // Render cursor
        if let (buffer, count) = cursorBatch.prepareBuffer() {
            if cursorStyle == .block {
                renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
            } else {
                renderer.renderCursor(encoder: encoder, quads: buffer, quadCount: count)
            }
        }

        encoder.endEncoding()

        if let drawable = currentDrawable {
            commandBuffer.present(drawable)
        }

        commandBuffer.commit()
    }

    // MARK: - Backing Scale Handling

    override public func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        updateBackingScaleFactor()
        updateDrawableSize()
        updateCursorBlinkTimer()
    }

    override public func viewDidChangeBackingProperties() {
        super.viewDidChangeBackingProperties()
        updateBackingScaleFactor()
        updateDrawableSize()
    }

    override public func viewWillMove(toWindow newWindow: NSWindow?) {
        super.viewWillMove(toWindow: newWindow)
        if newWindow == nil {
            stopCursorBlinkTimer()
        }
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
        renderer.updateFont(currentFont, scaleFactor: scale)
        layoutEngine.updateFont(currentFont, lineHeightMultiplier: lineHeightMultiplier, scaleFactor: scale)
        invalidateLayout()
        updateEstimatedCharWidth()
        onContentSizeChange?()
        scheduleRedraw()
    }

    private func updateCursorBlinkTimer() {
        let shouldBlink = window != nil && cursorStyle == .bar
        if shouldBlink {
            if cursorBlinkTimer == nil {
                cursorBlinkVisible = true
                lastCursorMovementTime = CACurrentMediaTime()
                let timer = Timer(timeInterval: cursorBlinkInterval, repeats: true) { [weak self] _ in
                    self?.tickCursorBlink()
                }
                timer.tolerance = 0.05
                RunLoop.main.add(timer, forMode: .common)
                cursorBlinkTimer = timer
            }
        } else {
            stopCursorBlinkTimer()
        }
    }

    private func stopCursorBlinkTimer() {
        cursorBlinkTimer?.invalidate()
        cursorBlinkTimer = nil
    }

    private func tickCursorBlink() {
        guard cursorStyle == .bar else { return }
        let now = CACurrentMediaTime()
        if now - lastCursorMovementTime < cursorBlinkSuspendDuration {
            if !cursorBlinkVisible {
                cursorBlinkVisible = true
                scheduleRedraw()
            }
            return
        }
        cursorBlinkVisible.toggle()
        scheduleRedraw()
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

    // MARK: - Layout

    private func invalidateLayout() {
        layoutEngine.invalidateCache()
        lineLayouts.removeAll()
        maxLineWidth = CGFloat(maxLineLength) * estimatedCharWidth
    }

    private func invalidateLayout(in range: NSRange) {
        guard let lineRange = lineRangeForRange(range) else { return }
        for lineIndex in lineRange {
            lineLayouts.removeValue(forKey: lineIndex)
        }
    }

    private func layoutForLine(_ lineIndex: Int) -> LineLayout? {
        guard lineIndex >= 0 && lineIndex < lines.count else { return nil }
        guard let visibleIndex = visibleLineIndex(forDocumentLine: lineIndex) else { return nil }
        if let cached = lineLayouts[lineIndex] {
            return cached
        }

        let yOffset = textInsets.top + CGFloat(visibleIndex) * layoutEngine.calculatedLineHeight
        let layout = layoutEngine.layoutLine(
            text: lines[lineIndex],
            lineIndex: lineIndex,
            yOffset: yOffset,
            coloredRanges: coloredRangesForLine(lineIndex),
            defaultColor: defaultTextColor
        )
        lineLayouts[lineIndex] = layout
        updateMaxLineWidth(from: layout)
        return layout
    }

    private func lineUTF16Length(_ lineIndex: Int) -> Int {
        guard lineIndex >= 0 && lineIndex < lineLengths.count else { return 0 }
        return lineLengths[lineIndex]
    }

    private func lineStartOffsetUTF16(_ lineIndex: Int) -> Int {
        guard lineIndex >= 0 && lineIndex < lineStarts.count else { return 0 }
        return lineStarts[lineIndex]
    }

    private func lineRangeUTF16(_ lineIndex: Int) -> NSRange {
        let start = lineStartOffsetUTF16(lineIndex)
        let length = lineUTF16Length(lineIndex) + ((lineIndex < lines.count - 1) ? 1 : 0)
        return NSRange(location: start, length: max(0, length))
    }

    private func lineIndexForOffset(_ offset: Int) -> Int? {
        guard !lineStarts.isEmpty else { return nil }
        let clamped = max(0, min(offset, (lines.count > 0 ? (lineStartOffsetUTF16(lines.count - 1) + lineUTF16Length(lines.count - 1)) : 0)))
        var low = 0
        var high = lineStarts.count - 1
        while low <= high {
            let mid = (low + high) / 2
            let start = lineStarts[mid]
            if start == clamped {
                return mid
            }
            if start < clamped {
                low = mid + 1
            } else {
                high = mid - 1
            }
        }
        return max(0, min(high, lineStarts.count - 1))
    }

    private func rebuildVisibleLineMap() {
        let lineCount = lines.count
        visibleLineForDocumentLine = Array(repeating: -1, count: lineCount)
        documentLineForVisibleLine.removeAll(keepingCapacity: true)
        visibleLineCount = 0

        guard lineCount > 0 else { return }

        var hidden = Array(repeating: false, count: lineCount)
        if !foldedLineRanges.isEmpty {
            for range in foldedLineRanges {
                let start = max(0, min(range.lowerBound, lineCount - 1))
                let end = max(0, min(range.upperBound, lineCount - 1))
                if end <= start { continue }
                if start + 1 <= end {
                    for line in (start + 1)...end {
                        hidden[line] = true
                    }
                }
            }
        }

        for line in 0..<lineCount {
            if hidden[line] {
                continue
            }
            visibleLineForDocumentLine[line] = visibleLineCount
            documentLineForVisibleLine.append(line)
            visibleLineCount += 1
        }
    }

    private func visibleLineIndex(forDocumentLine lineIndex: Int) -> Int? {
        guard lineIndex >= 0 && lineIndex < visibleLineForDocumentLine.count else { return nil }
        let value = visibleLineForDocumentLine[lineIndex]
        return value >= 0 ? value : nil
    }

    private func documentLineIndex(forVisibleLine visibleIndex: Int) -> Int? {
        guard visibleIndex >= 0 && visibleIndex < documentLineForVisibleLine.count else { return nil }
        return documentLineForVisibleLine[visibleIndex]
    }

    /// Baseline Y in document coordinates for a given line index.
    public func baselineY(forLine lineIndex: Int) -> CGFloat? {
        guard let layout = layoutForLine(lineIndex) else { return nil }
        return layout.yOffset + layout.baselineOffset
    }

    public func visibleLineRange(scrollOffset: CGFloat, height: CGFloat) -> (first: Int, last: Int) {
        let lineHeight = layoutEngine.calculatedLineHeight
        guard lineHeight > 0 && lineHeight.isFinite else { return (0, 0) }
        guard visibleLineCount > 0 else { return (0, -1) }
        let topOffset = scrollOffset - textInsets.top
        let bottomOffset = scrollOffset + height - textInsets.top
        let firstVisible = max(0, Int(floor(topOffset / lineHeight)))
        let lastVisible = max(0, Int(ceil(bottomOffset / lineHeight)))
        let clampedLastVisible = min(max(0, visibleLineCount - 1), lastVisible)
        let clampedFirstVisible = min(max(0, visibleLineCount - 1), firstVisible)
        let firstDoc = documentLineIndex(forVisibleLine: clampedFirstVisible) ?? 0
        let lastDoc = documentLineIndex(forVisibleLine: clampedLastVisible) ?? firstDoc
        return (firstDoc, lastDoc)
    }

    public func documentLineIndex(atY y: CGFloat) -> Int? {
        let lineHeight = layoutEngine.calculatedLineHeight
        guard lineHeight > 0 && lineHeight.isFinite else { return nil }
        let adjustedY = y + scrollOffset.y - textInsets.top
        let visibleIndex = Int(floor(adjustedY / lineHeight))
        return documentLineIndex(forVisibleLine: visibleIndex)
    }

    private func lineRangeForRange(_ range: NSRange) -> ClosedRange<Int>? {
        guard !lineStarts.isEmpty else { return nil }
        let startOffset = range.location
        let endOffset = max(range.location, range.location + max(0, range.length - 1))
        guard let startLine = lineIndexForOffset(startOffset),
              let endLine = lineIndexForOffset(endOffset) else {
            return nil
        }
        let lower = max(0, min(startLine, lines.count - 1))
        let upper = max(0, min(endLine, lines.count - 1))
        return lower <= upper ? (lower...upper) : nil
    }

    private func updateEstimatedCharWidth() {
        if let glyph = renderer?.glyphAtlas.glyph(for: Character("M"), variant: .regular) {
            estimatedCharWidth = max(1, glyph.advance)
        } else {
            estimatedCharWidth = max(1, currentFont.pointSize * 0.6)
        }
    }

    private func updateMaxLineWidth(from layout: LineLayout) {
        guard let lastGlyph = layout.glyphs.last else { return }
        let glyphInfo = renderer?.glyphAtlas.glyph(for: lastGlyph.glyphID, variant: lastGlyph.fontVariant)
        let width = lastGlyph.position.x + (glyphInfo?.advance ?? 0)
        if width > maxLineWidth + 0.5 {
            maxLineWidth = width
            scheduleContentSizeUpdate()
        }
    }

    private func scheduleContentSizeUpdate() {
        guard !contentSizeUpdateScheduled else { return }
        contentSizeUpdateScheduled = true
        DispatchQueue.main.async { [weak self] in
            guard let self = self else { return }
            self.contentSizeUpdateScheduled = false
            self.onContentSizeChange?()
        }
    }

    private func coloredRangesForLine(_ lineIndex: Int) -> [ColoredRange] {
        let lineStart = lineStartOffsetUTF16(lineIndex)
        let lineEnd = lineStart + lineUTF16Length(lineIndex)

        guard !coloredRanges.isEmpty else { return [] }

        // Binary search for first range that could intersect this line.
        var low = 0
        var high = coloredRanges.count - 1
        var firstMatch = coloredRanges.count
        while low <= high {
            let mid = (low + high) / 2
            let range = coloredRanges[mid].range
            let rangeEnd = range.location + range.length
            if rangeEnd <= lineStart {
                low = mid + 1
            } else {
                firstMatch = mid
                high = mid - 1
            }
        }

        guard firstMatch < coloredRanges.count else { return [] }

        var results: [ColoredRange] = []
        results.reserveCapacity(8)
        let lineLength = lineUTF16Length(lineIndex)
        var index = firstMatch

        while index < coloredRanges.count {
            let range = coloredRanges[index]
            let rangeStart = range.range.location
            if rangeStart >= lineEnd { break }

            let rangeEnd = rangeStart + range.range.length
            if rangeEnd > lineStart {
                let adjustedStart = max(0, rangeStart - lineStart)
                let adjustedEnd = min(lineLength, rangeEnd - lineStart)
                let adjustedLength = adjustedEnd - adjustedStart
                if adjustedLength > 0 {
                    results.append(ColoredRange(
                        range: NSRange(location: adjustedStart, length: adjustedLength),
                        color: range.color,
                        fontVariant: range.fontVariant
                    ))
                }
            }

            index += 1
        }

        return results
    }

    // MARK: - Batch Preparation

    private func prepareGlyphBatch() {
        glyphBatch.clear()

        let visibleRange = visibleLineRange(scrollOffset: scrollOffset.y, height: bounds.height)
        let firstVisibleLine = visibleRange.first
        let lastVisibleLine = visibleRange.last
        guard firstVisibleLine >= 0 && lastVisibleLine >= firstVisibleLine else { return }

        for lineIndex in firstVisibleLine...lastVisibleLine {
            guard let layout = layoutForLine(lineIndex) else { continue }

            for glyph in layout.glyphs {
                guard let cached = renderer.glyphAtlas.glyph(for: glyph.glyphID, variant: glyph.fontVariant) else {
                    continue
                }

                // Pass the pen position (baseline) - addGlyph will apply bearing offset
                let penPosition = CGPoint(
                    x: textInsets.left + glyph.position.x,
                    y: layout.yOffset + layout.baselineOffset
                )

                glyphBatch.addGlyph(cached: cached, screenPosition: penPosition, color: glyph.color)
            }

            if foldedRangeByStartLine[lineIndex] != nil {
                let placeholder = resolvedFoldPlaceholder()
                let lineLength = lineUTF16Length(lineIndex)
                let endX = textInsets.left + layoutEngine.xPosition(forCharacterOffset: lineLength, in: layout)
                let spaceWidth = renderer?.glyphAtlas.glyph(for: Character(" "), variant: .regular)?.advance ?? 8
                let placeholderX = endX + spaceWidth
                addInlinePlaceholder(
                    placeholder,
                    baselineY: layout.yOffset + layout.baselineOffset,
                    startX: placeholderX
                )
            }
        }
    }

    private func prepareIndentGuideBatch() {
        indentGuideBatch.clear()
        guard !indentGuideSegments.isEmpty else { return }

        let lineHeight = layoutEngine.calculatedLineHeight
        guard lineHeight > 0 && lineHeight.isFinite else { return }

        let columnWidth = max(
            1,
            renderer?.glyphAtlas.glyph(for: Character(" "), variant: .regular)?.advance ?? estimatedCharWidth
        )
        let pad = max(0, indentGuideLinePadding)
        let width = max(indentGuideLineWidth, 1.0 / max(1.0, backingScaleFactor))

        for segment in indentGuideSegments {
            addIndentGuideSegment(
                segment,
                columnWidth: columnWidth,
                lineHeight: lineHeight,
                linePadding: pad,
                lineWidth: width,
                color: indentGuideColor,
                batch: indentGuideBatch
            )
        }
    }

    private func prepareActiveIndentGuideBatch() {
        activeIndentGuideBatch.clear()
        guard !activeIndentGuideSegments.isEmpty else { return }

        let lineHeight = layoutEngine.calculatedLineHeight
        guard lineHeight > 0 && lineHeight.isFinite else { return }

        let columnWidth = max(
            1,
            renderer?.glyphAtlas.glyph(for: Character(" "), variant: .regular)?.advance ?? estimatedCharWidth
        )
        let pad = max(0, indentGuideLinePadding)
        let width = max(activeIndentGuideLineWidth, 1.0 / max(1.0, backingScaleFactor))

        for segment in activeIndentGuideSegments {
            addIndentGuideSegment(
                segment,
                columnWidth: columnWidth,
                lineHeight: lineHeight,
                linePadding: pad,
                lineWidth: width,
                color: activeIndentGuideColor,
                batch: activeIndentGuideBatch
            )
        }
    }

    private func addIndentGuideSegment(
        _ segment: IndentGuideSegment,
        columnWidth: CGFloat,
        lineHeight: CGFloat,
        linePadding: CGFloat,
        lineWidth: CGFloat,
        color: NSColor,
        batch: QuadBatch
    ) {
        guard segment.endLine >= segment.startLine else { return }

        let rawX = textInsets.left + CGFloat(max(0, segment.column)) * columnWidth
        let alignedX = round(rawX * backingScaleFactor) / backingScaleFactor
        let segmentWidth = max(lineWidth, 1.0 / max(1.0, backingScaleFactor))
        let pad = max(0, linePadding)

        var currentStartVisible: Int?
        var currentEndVisible = 0

        for line in segment.startLine...segment.endLine {
            guard let visibleIndex = visibleLineIndex(forDocumentLine: line) else {
                if let start = currentStartVisible {
                    let height = CGFloat(currentEndVisible - start + 1) * lineHeight
                    let y = textInsets.top + CGFloat(start) * lineHeight + pad
                    let rect = CGRect(x: alignedX, y: y, width: segmentWidth, height: max(0, height - pad * 2))
                    batch.addQuad(rect: rect, color: color)
                    currentStartVisible = nil
                }
                continue
            }

            if let start = currentStartVisible {
                if visibleIndex == currentEndVisible + 1 {
                    currentEndVisible = visibleIndex
                } else {
                    let height = CGFloat(currentEndVisible - start + 1) * lineHeight
                    let y = textInsets.top + CGFloat(start) * lineHeight + pad
                    let rect = CGRect(x: alignedX, y: y, width: segmentWidth, height: max(0, height - pad * 2))
                    batch.addQuad(rect: rect, color: color)
                    currentStartVisible = visibleIndex
                    currentEndVisible = visibleIndex
                }
            } else {
                currentStartVisible = visibleIndex
                currentEndVisible = visibleIndex
            }
        }

        if let start = currentStartVisible {
            let height = CGFloat(currentEndVisible - start + 1) * lineHeight
            let y = textInsets.top + CGFloat(start) * lineHeight + pad
            let rect = CGRect(x: alignedX, y: y, width: segmentWidth, height: max(0, height - pad * 2))
            batch.addQuad(rect: rect, color: color)
        }
    }

    private func addInlinePlaceholder(_ text: String, baselineY: CGFloat, startX: CGFloat) {
        let characters = Array(text)
        guard !characters.isEmpty else { return }

        var penX = startX
        let color = foldPlaceholderColor.simdColor

        for ch in characters {
            guard let cached = renderer.glyphAtlas.glyph(for: ch, variant: .regular) else { continue }
            glyphBatch.addGlyph(
                cached: cached,
                screenPosition: CGPoint(x: penX, y: baselineY),
                color: color
            )
            penX += cached.advance
        }
    }

    private func resolvedFoldPlaceholder() -> String {
        if placeholderGlyphsAvailable(foldPlaceholder) {
            return foldPlaceholder
        }
        return "..."
    }

    private func placeholderGlyphsAvailable(_ text: String) -> Bool {
        for ch in text {
            if renderer.glyphAtlas.glyph(for: ch, variant: .regular) == nil {
                return false
            }
        }
        return true
    }

    private func prepareSelectionBatch() {
        selectionBatch.clear()

        for range in selectionRanges {
            // Convert range to line/column coordinates and create selection rects
            let rects = rectsForRange(range)
            for rect in rects {
                selectionBatch.addQuad(rect: rect, color: selectionColor)
            }
        }
    }

    private func prepareBracketMatchBatch() {
        bracketMatchBatch.clear()
        guard !bracketMatchRanges.isEmpty else { return }

        for range in bracketMatchRanges {
            let rects = rectsForRange(range)
            for rect in rects {
                bracketMatchBatch.addQuad(rect: rect, color: bracketHighlightColor)
            }
        }
    }

    private func prepareCursorBatch() {
        cursorBatch.clear()

        if cursorStyle == .bar && !cursorBlinkVisible {
            return
        }

        let positions = cursorPositions.isEmpty ? [(cursorLine, cursorColumn)] : cursorPositions
        for position in positions {
            guard position.line >= 0 && position.line < lines.count else { continue }
            guard let layout = layoutForLine(position.line) else { continue }
            let xPos = textInsets.left + layoutEngine.xPosition(forCharacterOffset: position.column, in: layout)
            let maxColumn = lineUTF16Length(position.line)
            let nextColumn = min(position.column + 1, maxColumn)
            let xNext = textInsets.left + layoutEngine.xPosition(forCharacterOffset: nextColumn, in: layout)
            let defaultWidth = renderer?.glyphAtlas.glyph(for: Character(" "), variant: .regular)?.advance ?? 8
            let blockWidth = max(2, (xNext > xPos) ? (xNext - xPos) : defaultWidth)
            let width: CGFloat = (cursorStyle == .block) ? blockWidth : 2

            cursorBatch.addCursor(
                x: xPos,
                y: layout.yOffset,
                height: layoutEngine.calculatedLineHeight,
                width: width,
                color: cursorColor
            )
        }
    }

    private func prepareLineHighlightBatch() {
        lineHighlightBatch.clear()
        guard cursorLine < lines.count else { return }

        let currentRange = lineRangeUTF16(cursorLine)
        if currentRange.length > 0 {
            for selection in selectionRanges where selection.length > 0 {
                if NSIntersectionRange(selection, currentRange).length > 0 {
                    return
                }
            }
        }

        guard let layout = layoutForLine(cursorLine) else { return }
        let rect = CGRect(
            x: 0,
            y: layout.yOffset,
            width: bounds.width + scrollOffset.x,
            height: layoutEngine.calculatedLineHeight
        )
        lineHighlightBatch.addQuad(rect: rect, color: currentLineHighlightColor)
    }

    private func renderCurrentLineHighlight(encoder: MTLRenderCommandEncoder) {
        if let (buffer, count) = lineHighlightBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }
    }

    // MARK: - Mouse Events

    override public func mouseDown(with event: NSEvent) {
        lastMouseModifiers = event.modifierFlags
        lastClickCount = event.clickCount
        window?.makeFirstResponder(self)
        let locationInView = convert(event.locationInWindow, from: nil)
        textDelegate?.metalTextView(self, didClickAt: locationInView)
    }

    override public func mouseDragged(with event: NSEvent) {
        lastMouseModifiers = event.modifierFlags
        let locationInView = convert(event.locationInWindow, from: nil)
        textDelegate?.metalTextView(self, didDragTo: locationInView)
    }

    // MARK: - Hit Testing

    /// Convert point to character position
    public func characterPosition(at point: CGPoint) -> (line: Int, column: Int)? {
        let lineHeight = layoutEngine.calculatedLineHeight
        guard lineHeight > 0 && lineHeight.isFinite else { return nil }

        // Convert view-local point to document coordinates using scroll offset
        let adjustedY = point.y + scrollOffset.y - textInsets.top
        let visibleIndex = Int(floor(adjustedY / lineHeight))
        guard let lineIndex = documentLineIndex(forVisibleLine: visibleIndex) else { return nil }

        guard lineIndex >= 0 && lineIndex < lines.count else {
            return nil
        }

        guard let layout = layoutForLine(lineIndex) else { return nil }
        let adjustedX = point.x + scrollOffset.x - textInsets.left
        let rawColumn = layoutEngine.characterOffset(forX: adjustedX, in: layout)
        let maxColumn = lineUTF16Length(lineIndex)
        let column = min(max(rawColumn, 0), maxColumn)

        return (lineIndex, column)
    }

    /// Get rects for a character range
    public func rectsForRange(_ range: NSRange) -> [CGRect] {
        var rects: [CGRect] = []
        guard let lineRange = lineRangeForRange(range) else { return rects }

        for lineIndex in lineRange {
            guard let layout = layoutForLine(lineIndex) else { continue }
            let lineStart = lineStartOffsetUTF16(lineIndex)
            let lineLength = lineUTF16Length(lineIndex)
            let lineEnd = lineStart + lineLength

            let lineEndWithNewline = lineEnd + ((lineIndex < lines.count - 1) ? 1 : 0)
            if range.location < lineEndWithNewline && range.location + range.length > lineStart {
                let startCol = max(0, range.location - lineStart)
                let endCol = min(lineLength, range.location + range.length - lineStart)

                let startX = textInsets.left + layoutEngine.xPosition(forCharacterOffset: startCol, in: layout)
                var endX = textInsets.left + layoutEngine.xPosition(forCharacterOffset: endCol, in: layout)

                if endX <= startX {
                    let spaceWidth: CGFloat = renderer?.glyphAtlas.glyph(for: Character(" "), variant: .regular)?.advance ?? 8
                    endX = startX + spaceWidth
                }

                if range.location + range.length > lineEnd {
                    endX = bounds.width + scrollOffset.x
                }

                rects.append(CGRect(
                    x: startX,
                    y: layout.yOffset,
                    width: endX - startX,
                    height: layoutEngine.calculatedLineHeight
                ))
            }
        }

        return rects
    }
}

// MARK: - Delegate Protocol

public protocol MetalTextViewDelegate: AnyObject {
    func metalTextView(_ view: MetalTextView, didChangeText text: String)
    func metalTextView(_ view: MetalTextView, didChangeSelection ranges: [NSRange])
    func metalTextView(_ view: MetalTextView, didMoveCursor line: Int, column: Int)
    func metalTextView(_ view: MetalTextView, didClickAt point: CGPoint)
    func metalTextView(_ view: MetalTextView, didDragTo point: CGPoint)
}
