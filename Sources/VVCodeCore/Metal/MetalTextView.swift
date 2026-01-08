import Foundation
import MetalKit
import AppKit
import QuartzCore
import CoreText

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
    private var colorGlyphBatch: GlyphBatch!
    private var selectionBatch: QuadBatch!
    private var cursorBatch: QuadBatch!
    private var lineHighlightBatch: QuadBatch!
    private var indentGuideBatch: QuadBatch!
    private var activeIndentGuideBatch: QuadBatch!
    private var bracketMatchBatch: QuadBatch!
    private var searchMatchBatch: QuadBatch!
    private var activeSearchMatchBatch: QuadBatch!
    private var markedTextBatch: QuadBatch!
    private var gutterGlyphBatch: GlyphBatch!
    private var gutterColorGlyphBatch: GlyphBatch!
    private var gutterQuadBatch: QuadBatch!
    private var statusBarGlyphBatch: GlyphBatch!
    private var statusBarColorGlyphBatch: GlyphBatch!
    private var statusBarQuadBatch: QuadBatch!
    private var searchOverlayGlyphBatch: GlyphBatch!
    private var searchOverlayColorGlyphBatch: GlyphBatch!
    private var searchOverlayQuadBatch: QuadBatch!

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
    private var searchMatchRanges: [NSRange] = []
    private var activeSearchMatch: NSRange?
    private var markedTextRange: NSRange?
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

    // Gutter state
    private var showsGutter: Bool = true
    private var showsLineNumbers: Bool = true
    private var showsGitGutter: Bool = true
    private var gutterFont: NSFont = NSFont.monospacedSystemFont(ofSize: 11, weight: .regular)
    private var gutterInsets: NSEdgeInsets = NSEdgeInsets(top: 4, left: 8, bottom: 4, right: 8)
    private var gutterMinimumWidth: CGFloat = 0
    private var foldMarkerAreaWidth: CGFloat = 10
    private var foldMarkerSpacing: CGFloat = 4
    private let gutterIndicatorWidth: CGFloat = 2
    private let gutterSeparatorWidth: CGFloat = 0
    private var foldRanges: [MetalGutterView.FoldRange] = []
    private var foldRangeByStartLine: [Int: MetalGutterView.FoldRange] = [:]
    private var foldedStartLines: Set<Int> = []
    private var gitHunks: [MetalGutterView.GitHunk] = []
    private var selectedLineRanges: [ClosedRange<Int>] = []
    private var hoveredFoldLine: Int? {
        didSet {
            if oldValue != hoveredFoldLine {
                scheduleRedraw()
            }
        }
    }
    private var currentLineNumber: Int = 0
    private var gutterWidth: CGFloat = 0

    private var foldMarkerIconScale: CGFloat = 0.55
    private var foldMarkerIconLineWidth: CGFloat = 1.4
    private var foldMarkerHoverPadding: CGFloat = 3
    private var foldMarkerHoverCornerRadius: CGFloat = 3
    private var gutterTrackingArea: NSTrackingArea?

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
    private var baseTextInsets: NSEdgeInsets = NSEdgeInsets(top: 4, left: 4, bottom: 4, right: 4)
    public private(set) var textInsets: NSEdgeInsets = NSEdgeInsets(top: 4, left: 4, bottom: 4, right: 4)
    private var statusBarTextInsets: NSEdgeInsets = NSEdgeInsets(top: 0, left: 10, bottom: 0, right: 10)
    private var statusBarModePadding: CGSize = CGSize(width: 8, height: 2)
    private var statusBarBadgePadding: CGSize = CGSize(width: 6, height: 2)
    private var statusBarBadgeSpacing: CGFloat = 8

    private var currentFont: NSFont = NSFont.monospacedSystemFont(ofSize: 13, weight: .regular)
    private var lineHeightMultiplier: CGFloat = 1.4
    private var backingScaleFactor: CGFloat = 1.0

    // Theme colors
    public var selectionColor: NSColor = NSColor.selectedTextBackgroundColor
    public var searchHighlightColor: NSColor = NSColor.selectedTextBackgroundColor.withAlphaComponent(0.2)
    public var activeSearchHighlightColor: NSColor = NSColor.selectedTextBackgroundColor.withAlphaComponent(0.4)
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
    public var markedTextUnderlineColor: NSColor = NSColor.controlAccentColor {
        didSet { scheduleRedraw() }
    }
    public var foldPlaceholderColor: NSColor = NSColor.secondaryLabelColor {
        didSet { scheduleRedraw() }
    }
    public var foldPlaceholder: String = "⋯" {
        didSet { scheduleRedraw() }
    }

    // Gutter colors
    public var gutterBackgroundColor: NSColor = NSColor.textBackgroundColor {
        didSet { scheduleRedraw() }
    }
    public var gutterSeparatorColor: NSColor = NSColor.separatorColor {
        didSet { scheduleRedraw() }
    }
    public var lineNumberColor: NSColor = NSColor.secondaryLabelColor {
        didSet { scheduleRedraw() }
    }
    public var currentLineNumberColor: NSColor = NSColor.labelColor {
        didSet { scheduleRedraw() }
    }
    public var selectedLineNumberColor: NSColor = NSColor.labelColor {
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
    public var gitAddedColor: NSColor = NSColor.systemGreen {
        didSet { scheduleRedraw() }
    }
    public var gitModifiedColor: NSColor = NSColor.systemBlue {
        didSet { scheduleRedraw() }
    }
    public var gitDeletedColor: NSColor = NSColor.systemRed {
        didSet { scheduleRedraw() }
    }

    // Status bar colors
    public var statusBarBackgroundColor: NSColor = NSColor.black.withAlphaComponent(0.55) {
        didSet { scheduleRedraw() }
    }
    public var statusBarBorderColor: NSColor = NSColor.white.withAlphaComponent(0.15) {
        didSet { scheduleRedraw() }
    }
    public var statusBarTextColor: NSColor = NSColor.white {
        didSet { scheduleRedraw() }
    }
    public var statusBarSecondaryTextColor: NSColor = NSColor.white.withAlphaComponent(0.85) {
        didSet { scheduleRedraw() }
    }
    public var statusBarModeBackgroundColor: NSColor = NSColor.systemBlue {
        didSet { scheduleRedraw() }
    }
    public var statusBarModeTextColor: NSColor = NSColor.black {
        didSet { scheduleRedraw() }
    }
    public var statusBarBadgeBackgroundColor: NSColor = NSColor.systemBlue.withAlphaComponent(0.25) {
        didSet { scheduleRedraw() }
    }
    public var statusBarBadgeTextColor: NSColor = NSColor.white {
        didSet { scheduleRedraw() }
    }

    // Search overlay colors
    public var searchOverlayBackgroundColor: NSColor = NSColor.black.withAlphaComponent(0.85) {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayBorderColor: NSColor = NSColor.white.withAlphaComponent(0.15) {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayFieldBackgroundColor: NSColor = NSColor.black.withAlphaComponent(0.35) {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayFieldBorderColor: NSColor = NSColor.white.withAlphaComponent(0.2) {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayFieldActiveBorderColor: NSColor = NSColor.systemBlue.withAlphaComponent(0.7) {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayTextColor: NSColor = NSColor.white {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayPlaceholderColor: NSColor = NSColor.white.withAlphaComponent(0.5) {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayButtonBackgroundColor: NSColor = NSColor.white.withAlphaComponent(0.08) {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayButtonHoverBackgroundColor: NSColor = NSColor.white.withAlphaComponent(0.16) {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayButtonActiveBackgroundColor: NSColor = NSColor.systemBlue.withAlphaComponent(0.55) {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayButtonTextColor: NSColor = NSColor.white.withAlphaComponent(0.85) {
        didSet { scheduleRedraw() }
    }
    public var searchOverlayButtonActiveTextColor: NSColor = NSColor.white {
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

    // Status bar state
    private var statusBarEnabled: Bool = false
    private var statusBarHeight: CGFloat = 22
    private var statusBarLineHeight: CGFloat = 16
    private var statusBarBaselineOffset: CGFloat = 12
    private var statusBarLeftText: String = ""
    private var statusBarRightText: String = ""
    private var statusBarRightBadgeText: String = ""

    public enum SearchOverlayScope {
        case currentFile
        case openDocuments
    }

    private enum SearchOverlayAction: Hashable {
        case field
        case toggleCase
        case scopeCurrent
        case scopeOpen
        case prev
        case next
    }

    private struct SearchOverlayHitArea {
        let action: SearchOverlayAction
        let rect: CGRect
    }

    private var searchOverlayVisible: Bool = false
    private var searchOverlayActive: Bool = false
    private var searchOverlayQuery: String = ""
    private var searchOverlayScope: SearchOverlayScope = .currentFile
    private var searchOverlayCaseSensitive: Bool = true
    private var searchOverlayMatchIndex: Int?
    private var searchOverlayMatchCount: Int?
    private var searchOverlayPlaceholder: String = "Search"
    private var searchOverlayHoverAction: SearchOverlayAction? {
        didSet { scheduleRedraw() }
    }
    private var searchOverlayHitAreas: [SearchOverlayHitArea] = []
    private var searchOverlayRect: CGRect?
    private let searchOverlayMargin: CGFloat = 12
    private let searchOverlayPadding: CGFloat = 10
    private let searchOverlayRowSpacing: CGFloat = 8
    private let searchOverlayItemSpacing: CGFloat = 6
    private let searchOverlayFieldPadding: CGFloat = 8
    private let searchOverlayButtonPadding: CGFloat = 8

    // Delegates
    public weak var textDelegate: MetalTextViewDelegate?
    public var onToggleFold: ((Int) -> Void)?

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

        gutterFont = font
        updateStatusBarMetrics()

        // Initialize batches
        glyphBatch = GlyphBatch(device: device)
        colorGlyphBatch = GlyphBatch(device: device)
        selectionBatch = QuadBatch(device: device)
        cursorBatch = QuadBatch(device: device)
        lineHighlightBatch = QuadBatch(device: device)
        indentGuideBatch = QuadBatch(device: device)
        activeIndentGuideBatch = QuadBatch(device: device)
        bracketMatchBatch = QuadBatch(device: device)
        searchMatchBatch = QuadBatch(device: device)
        activeSearchMatchBatch = QuadBatch(device: device)
        markedTextBatch = QuadBatch(device: device)
        gutterGlyphBatch = GlyphBatch(device: device)
        gutterColorGlyphBatch = GlyphBatch(device: device)
        gutterQuadBatch = QuadBatch(device: device)
        statusBarGlyphBatch = GlyphBatch(device: device)
        statusBarColorGlyphBatch = GlyphBatch(device: device)
        statusBarQuadBatch = QuadBatch(device: device)
        searchOverlayGlyphBatch = GlyphBatch(device: device)
        searchOverlayColorGlyphBatch = GlyphBatch(device: device)
        searchOverlayQuadBatch = QuadBatch(device: device)

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
        updateGutterMetrics()
        invalidateLayout()
        onContentSizeChange?()
        scheduleRedraw()
    }

    public func setTextInsets(_ insets: NSEdgeInsets) {
        baseTextInsets = insets
        recomputeTextInsets()
    }

    public func setGutterInsets(_ insets: NSEdgeInsets) {
        gutterInsets = insets
        updateGutterMetrics()
    }

    public func setMinimumGutterWidth(_ width: CGFloat) {
        gutterMinimumWidth = max(0, width)
        updateGutterMetrics()
    }

    public func setShowsGutter(_ show: Bool) {
        showsGutter = show
        updateGutterMetrics()
    }

    public func setShowsLineNumbers(_ show: Bool) {
        showsLineNumbers = show
        updateGutterMetrics()
    }

    public func setShowsGitGutter(_ show: Bool) {
        showsGitGutter = show
        updateGutterMetrics()
    }

    public func setFoldRanges(_ ranges: [MetalGutterView.FoldRange], foldedStartLines: Set<Int>) {
        foldRanges = ranges
        var map: [Int: MetalGutterView.FoldRange] = [:]
        for range in ranges where map[range.startLine] == nil {
            map[range.startLine] = range
        }
        foldRangeByStartLine = map
        self.foldedStartLines = foldedStartLines
        updateGutterMetrics()
        scheduleRedraw()
    }

    public func setGitHunks(_ hunks: [MetalGutterView.GitHunk]) {
        gitHunks = hunks
        scheduleRedraw()
    }

    public func setSelectedLineRanges(_ ranges: [ClosedRange<Int>]) {
        selectedLineRanges = mergeLineRanges(ranges)
        scheduleRedraw()
    }

    public func setCurrentLineNumber(_ line: Int) {
        currentLineNumber = max(0, line)
        scheduleRedraw()
    }

    public func setStatusBarEnabled(_ enabled: Bool) {
        statusBarEnabled = enabled
        recomputeTextInsets()
    }

    public func setStatusBarHeight(_ height: CGFloat) {
        statusBarHeight = max(0, height)
        recomputeTextInsets()
    }

    public func setStatusBarText(left: String, right: String, rightBadge: String = "") {
        if statusBarLeftText == left && statusBarRightText == right && statusBarRightBadgeText == rightBadge {
            return
        }
        statusBarLeftText = left
        statusBarRightText = right
        statusBarRightBadgeText = rightBadge
        scheduleRedraw()
    }

    public func setSearchOverlayState(
        visible: Bool,
        active: Bool,
        query: String,
        scope: SearchOverlayScope,
        caseSensitive: Bool,
        matchIndex: Int?,
        matchCount: Int?
    ) {
        let shouldRedraw = searchOverlayVisible != visible
            || searchOverlayActive != active
            || searchOverlayQuery != query
            || searchOverlayScope != scope
            || searchOverlayCaseSensitive != caseSensitive
            || searchOverlayMatchIndex != matchIndex
            || searchOverlayMatchCount != matchCount

        searchOverlayVisible = visible
        searchOverlayActive = active
        searchOverlayQuery = query
        searchOverlayScope = scope
        searchOverlayCaseSensitive = caseSensitive
        searchOverlayMatchIndex = matchIndex
        searchOverlayMatchCount = matchCount

        if !visible {
            searchOverlayHoverAction = nil
            searchOverlayHitAreas.removeAll()
            searchOverlayRect = nil
        }

        if shouldRedraw {
            scheduleRedraw()
        }
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
        updateGutterMetrics()
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

    /// Set search match highlight ranges
    public func setSearchMatchRanges(_ ranges: [NSRange]) {
        searchMatchRanges = ranges
        scheduleRedraw()
    }

    /// Set active search match range
    public func setActiveSearchMatch(_ range: NSRange?) {
        activeSearchMatch = range
        scheduleRedraw()
    }

    /// Set marked text (IME composition) range
    public func setMarkedTextRange(_ range: NSRange?) {
        markedTextRange = range
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
        gutterFont = font
        self.lineHeightMultiplier = lineHeightMultiplier
        renderer.updateFont(font, scaleFactor: backingScaleFactor)
        layoutEngine.updateFont(font, lineHeightMultiplier: lineHeightMultiplier, scaleFactor: backingScaleFactor)
        updateStatusBarMetrics()
        updateGutterMetrics()
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

    private var statusBarBottomInset: CGFloat {
        guard statusBarEnabled else { return 0 }
        return lineHeight
    }

    private var statusBarTotalHeight: CGFloat {
        guard statusBarEnabled else { return 0 }
        return statusBarHeight + statusBarBottomInset
    }

    private var effectiveViewportHeight: CGFloat {
        max(0, bounds.height - statusBarTotalHeight)
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
        prepareGutterBatches()
        prepareGlyphBatch()
        prepareIndentGuideBatch()
        prepareActiveIndentGuideBatch()
        prepareSelectionBatch()
        prepareBracketMatchBatch()
        prepareSearchMatchBatch()
        prepareMarkedTextBatch()
        prepareCursorBatch()
        prepareLineHighlightBatch()
        prepareStatusBarBatches()
        prepareSearchOverlayBatches()

        // Render gutter background and indicators
        if let (buffer, count) = gutterQuadBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }

        // Render current line highlight
        renderCurrentLineHighlight(encoder: encoder)

        // Render indent guides
        if let (buffer, count) = indentGuideBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }
        if let (buffer, count) = activeIndentGuideBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }

        // Render search matches
        if let (buffer, count) = searchMatchBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }
        if let (buffer, count) = activeSearchMatchBatch.prepareBuffer() {
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
        if let (buffer, count) = colorGlyphBatch.prepareBuffer() {
            renderer.renderColorGlyphs(encoder: encoder, instances: buffer, instanceCount: count)
        }

        // Render IME marked text underline
        if let (buffer, count) = markedTextBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }

        // Render gutter glyphs
        if let (buffer, count) = gutterGlyphBatch.prepareBuffer() {
            renderer.renderGutter(encoder: encoder, instances: buffer, instanceCount: count)
        }
        if let (buffer, count) = gutterColorGlyphBatch.prepareBuffer() {
            renderer.renderGutterColorGlyphs(encoder: encoder, instances: buffer, instanceCount: count)
        }

        // Render cursor
        if let (buffer, count) = cursorBatch.prepareBuffer() {
            if cursorStyle == .block {
                renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
            } else {
                renderer.renderCursor(encoder: encoder, quads: buffer, quadCount: count)
            }
        }

        // Render status bar overlay
        if let (buffer, count) = statusBarQuadBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }
        if let (buffer, count) = statusBarGlyphBatch.prepareBuffer() {
            renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: count)
        }
        if let (buffer, count) = statusBarColorGlyphBatch.prepareBuffer() {
            renderer.renderColorGlyphs(encoder: encoder, instances: buffer, instanceCount: count)
        }

        // Render search overlay
        if let (buffer, count) = searchOverlayQuadBatch.prepareBuffer() {
            renderer.renderSelections(encoder: encoder, quads: buffer, quadCount: count)
        }
        if let (buffer, count) = searchOverlayGlyphBatch.prepareBuffer() {
            renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: count)
        }
        if let (buffer, count) = searchOverlayColorGlyphBatch.prepareBuffer() {
            renderer.renderColorGlyphs(encoder: encoder, instances: buffer, instanceCount: count)
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
        window?.acceptsMouseMovedEvents = true
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

    private func updateStatusBarMetrics() {
        let ctFont = currentFont as CTFont
        let ascent = CTFontGetAscent(ctFont)
        let descent = CTFontGetDescent(ctFont)
        let leading = CTFontGetLeading(ctFont)
        let naturalLineHeight = ascent + descent + leading
        statusBarLineHeight = ceil(naturalLineHeight * backingScaleFactor) / backingScaleFactor
        let extraSpace = statusBarLineHeight - naturalLineHeight
        statusBarBaselineOffset = round((extraSpace / 2 + ascent) * backingScaleFactor) / backingScaleFactor
    }

    private func updateBackingScaleFactor() {
        let scale = window?.backingScaleFactor ?? NSScreen.main?.backingScaleFactor ?? 1.0
        guard scale > 0 else { return }
        if abs(scale - backingScaleFactor) < 0.001 { return }
        backingScaleFactor = scale
        layer?.contentsScale = scale
        renderer.updateFont(currentFont, scaleFactor: scale)
        layoutEngine.updateFont(currentFont, lineHeightMultiplier: lineHeightMultiplier, scaleFactor: scale)
        updateStatusBarMetrics()
        updateGutterMetrics()
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
        if statusBarEnabled && y > bounds.height - statusBarTotalHeight {
            return nil
        }
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

    private func recomputeTextInsets() {
        gutterInsets.top = baseTextInsets.top
        gutterInsets.bottom = baseTextInsets.bottom
        let newGutterWidth = showsGutter ? calculatedGutterWidth() : 0
        let newInsets = NSEdgeInsets(
            top: baseTextInsets.top,
            left: baseTextInsets.left + newGutterWidth,
            bottom: baseTextInsets.bottom + statusBarTotalHeight,
            right: baseTextInsets.right
        )
        let widthChanged = abs(newGutterWidth - gutterWidth) > 0.5
        let insetsChanged = newInsets.top != textInsets.top
            || newInsets.left != textInsets.left
            || newInsets.bottom != textInsets.bottom
            || newInsets.right != textInsets.right
        gutterWidth = newGutterWidth
        if widthChanged || insetsChanged {
            textInsets = newInsets
            invalidateLayout()
            onContentSizeChange?()
        }
        scheduleRedraw()
    }

    private func updateGutterMetrics() {
        recomputeTextInsets()
    }

    private func updateMaxLineWidth(from layout: LineLayout) {
        guard let lastGlyph = layout.glyphs.last else { return }
        let glyphInfo = renderer?.glyphAtlas.glyph(for: lastGlyph.glyphID, font: lastGlyph.font)
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

    private func prepareGutterBatches() {
        gutterQuadBatch.clear()
        gutterGlyphBatch.clear()
        gutterColorGlyphBatch.clear()

        guard showsGutter, gutterWidth > 0 else { return }

        let backgroundRect = CGRect(
            x: scrollOffset.x,
            y: scrollOffset.y,
            width: gutterWidth,
            height: bounds.height
        )
        gutterQuadBatch.addQuad(rect: backgroundRect, color: gutterBackgroundColor)

        if showsGitGutter && !gitHunks.isEmpty {
            let indicatorWidth = gutterIndicatorWidth
            let indicatorX = gutterWidth - gutterSeparatorWidth - indicatorWidth
            for hunk in gitHunks {
                let start = hunk.startLine
                let end = hunk.startLine + max(0, hunk.lineCount - 1)
                let visibleRange = visibleLineRange(scrollOffset: scrollOffset.y, height: effectiveViewportHeight)
                if end < visibleRange.first || start > visibleRange.last {
                    continue
                }

                let color: NSColor
                switch hunk.status {
                case .added: color = gitAddedColor
                case .modified: color = gitModifiedColor
                case .deleted: color = gitDeletedColor
                }

                let y = textInsets.top + CGFloat(hunk.startLine) * layoutEngine.calculatedLineHeight
                let quadX = scrollOffset.x + indicatorX
                let quadY = scrollOffset.y + y
                if hunk.status == .deleted {
                    let rect = CGRect(x: quadX, y: quadY, width: indicatorWidth, height: layoutEngine.calculatedLineHeight / 2)
                    gutterQuadBatch.addQuad(rect: rect, color: color)
                } else {
                    let height = CGFloat(hunk.lineCount) * layoutEngine.calculatedLineHeight
                    let rect = CGRect(x: quadX, y: quadY + 2, width: indicatorWidth, height: max(0, height - 4))
                    gutterQuadBatch.addQuad(rect: rect, color: color)
                }
            }
        }

        let visibleRange = visibleLineRange(scrollOffset: scrollOffset.y, height: effectiveViewportHeight)
        if visibleRange.first > visibleRange.last { return }

        let foldMetrics = foldIconMetrics()
        let mergedSelections = selectedLineRanges
        var selectionIndex = 0

        for lineIndex in visibleRange.first...visibleRange.last {
            guard isLineVisible(lineIndex) else { continue }

            while selectionIndex < mergedSelections.count && mergedSelections[selectionIndex].upperBound < lineIndex {
                selectionIndex += 1
            }
            let isSelected = selectionIndex < mergedSelections.count && mergedSelections[selectionIndex].contains(lineIndex)

            let baselineY = baselineY(forLine: lineIndex) ??
                (textInsets.top + CGFloat(lineIndex) * layoutEngine.calculatedLineHeight + layoutEngine.calculatedBaselineOffset)

            if showsLineNumbers {
                let lineNumber = String(lineIndex + 1)
                let color: NSColor
                if lineIndex == currentLineNumber {
                    color = currentLineNumberColor
                } else if isSelected {
                    color = selectedLineNumberColor
                } else {
                    color = lineNumberColor
                }
                addGutterText(lineNumber, baselineY: baselineY, color: color)
            }

            if foldRangeByStartLine[lineIndex] != nil {
                let isFolded = foldedStartLines.contains(lineIndex)
                let isHovered = hoveredFoldLine == lineIndex
                if isHovered,
                   let bgGlyph = renderer.glyphAtlas.customGlyph(
                    kind: .foldHoverBackground,
                    size: foldMetrics.hoverSize,
                    lineWidth: 1,
                    cornerRadius: foldMetrics.hoverCornerRadius
                   ) {
                    let bgX = foldMarkerAreaX + max(0, (foldMarkerAreaWidth - foldMetrics.hoverSize.width) / 2)
                    let bgY = baselineY - layoutEngine.calculatedBaselineOffset + (layoutEngine.calculatedLineHeight - foldMetrics.hoverSize.height) / 2
                    addGutterGlyph(bgGlyph, topLeft: CGPoint(x: bgX, y: bgY), color: foldMarkerHoverBackgroundColor)
                }

                if let iconGlyph = renderer.glyphAtlas.customGlyph(
                    kind: isFolded ? .foldChevronClosed : .foldChevronOpen,
                    size: foldMetrics.iconSize,
                    lineWidth: foldMetrics.lineWidth
                ) {
                    let iconX = foldMarkerAreaX + max(0, (foldMarkerAreaWidth - foldMetrics.iconSize.width) / 2)
                    let iconY = baselineY - layoutEngine.calculatedBaselineOffset + (layoutEngine.calculatedLineHeight - foldMetrics.iconSize.height) / 2
                    let iconColor = isHovered || isFolded ? foldMarkerActiveColor : foldMarkerColor
                    addGutterGlyph(iconGlyph, topLeft: CGPoint(x: iconX, y: iconY), color: iconColor)
                } else {
                    let markerChar = foldMarkerCharacter(isFolded: isFolded)
                    let marker = String(markerChar)
                    let markerWidth = renderer.glyphAtlas.glyph(for: markerChar, variant: .regular)?.advance ?? 8
                    let markerX = foldMarkerAreaX + max(0, (foldMarkerAreaWidth - markerWidth) / 2)
                    let iconColor = isHovered || isFolded ? foldMarkerActiveColor : foldMarkerColor
                    addGutterSymbol(marker, baselineY: baselineY, x: markerX, color: iconColor)
                }
            }
        }

        if showsLineNumbers && visibleRange.last >= lines.count {
            let tildeLine = max(visibleRange.first, lines.count)
            let baselineY = baselineY(forLine: tildeLine) ??
                (textInsets.top + CGFloat(tildeLine) * layoutEngine.calculatedLineHeight + layoutEngine.calculatedBaselineOffset)
            addGutterText("~", baselineY: baselineY, color: lineNumberColor.withAlphaComponent(0.55))
        }
    }

    private func prepareGlyphBatch() {
        glyphBatch.clear()
        colorGlyphBatch.clear()

        let visibleRange = visibleLineRange(scrollOffset: scrollOffset.y, height: effectiveViewportHeight)
        let firstVisibleLine = visibleRange.first
        let lastVisibleLine = visibleRange.last
        guard firstVisibleLine >= 0 && lastVisibleLine >= firstVisibleLine else { return }

        for lineIndex in firstVisibleLine...lastVisibleLine {
            guard let layout = layoutForLine(lineIndex) else { continue }

            for glyph in layout.glyphs {
                guard let cached = renderer.glyphAtlas.glyph(for: glyph.glyphID, font: glyph.font) else {
                    continue
                }

                // Pass the pen position (baseline) - addGlyph will apply bearing offset
                let penPosition = CGPoint(
                    x: textInsets.left + glyph.position.x,
                    y: layout.yOffset + layout.baselineOffset
                )

                if cached.isColor {
                    let color = SIMD4<Float>(1, 1, 1, glyph.color.w)
                    colorGlyphBatch.addGlyph(cached: cached, screenPosition: penPosition, color: color)
                } else {
                    glyphBatch.addGlyph(cached: cached, screenPosition: penPosition, color: glyph.color)
                }
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

    private func prepareSearchMatchBatch() {
        searchMatchBatch.clear()
        activeSearchMatchBatch.clear()

        guard !searchMatchRanges.isEmpty else {
            if let active = activeSearchMatch, active.length > 0 {
                let rects = rectsForRange(active)
                for rect in rects {
                    activeSearchMatchBatch.addQuad(rect: rect, color: activeSearchHighlightColor)
                }
            }
            return
        }

        let visible = visibleLineRange(scrollOffset: scrollOffset.y, height: effectiveViewportHeight)
        guard visible.first <= visible.last else { return }

        for range in searchMatchRanges {
            guard let lineRange = lineRangeForRange(range) else { continue }
            if lineRange.upperBound < visible.first || lineRange.lowerBound > visible.last {
                continue
            }
            let rects = rectsForRange(range)
            for rect in rects {
                searchMatchBatch.addQuad(rect: rect, color: searchHighlightColor)
            }
        }

        if let active = activeSearchMatch, active.length > 0 {
            let rects = rectsForRange(active)
            for rect in rects {
                activeSearchMatchBatch.addQuad(rect: rect, color: activeSearchHighlightColor)
            }
        }
    }

    private func prepareMarkedTextBatch() {
        markedTextBatch.clear()
        guard let range = markedTextRange, range.length > 0 else { return }

        let lineHeight = layoutEngine.calculatedLineHeight
        let underlineThickness = max(1.0 / max(1.0, backingScaleFactor), 1.0)
        let underlineOffset: CGFloat = 1.0

        let rects = rectsForRange(range)
        for rect in rects {
            let y = min(rect.minY + lineHeight - underlineThickness - underlineOffset,
                        rect.minY + layoutEngine.calculatedBaselineOffset + underlineOffset)
            let underlineRect = CGRect(x: rect.minX, y: y, width: rect.width, height: underlineThickness)
            markedTextBatch.addQuad(rect: underlineRect, color: markedTextUnderlineColor)
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
            let screenY = layout.yOffset - scrollOffset.y
            if screenY > effectiveViewportHeight || (screenY + layoutEngine.calculatedLineHeight) < 0 {
                continue
            }
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
        let screenY = layout.yOffset - scrollOffset.y
        if screenY > effectiveViewportHeight || (screenY + layoutEngine.calculatedLineHeight) < 0 {
            return
        }
        let highlightX = showsGutter ? gutterWidth : 0
        let highlightWidth = max(0, bounds.width - highlightX + scrollOffset.x)
        let rect = CGRect(
            x: highlightX,
            y: layout.yOffset,
            width: highlightWidth,
            height: layoutEngine.calculatedLineHeight
        )
        lineHighlightBatch.addQuad(rect: rect, color: currentLineHighlightColor)
    }

    private func prepareStatusBarBatches() {
        statusBarQuadBatch.clear()
        statusBarGlyphBatch.clear()
        statusBarColorGlyphBatch.clear()

        guard statusBarEnabled, statusBarHeight > 0 else { return }
        let barHeight = statusBarHeight
        let barY = bounds.height - statusBarBottomInset - barHeight
        if barY.isNaN || barHeight <= 0 || barY.isInfinite {
            return
        }

        let bgRect = CGRect(
            x: scrollOffset.x,
            y: scrollOffset.y + barY,
            width: bounds.width,
            height: barHeight
        )
        statusBarQuadBatch.addQuad(rect: bgRect, color: statusBarBackgroundColor)

        let borderHeight = max(1.0 / max(1.0, backingScaleFactor), 1.0)
        let borderRect = CGRect(
            x: scrollOffset.x,
            y: scrollOffset.y + barY + barHeight - borderHeight,
            width: bounds.width,
            height: borderHeight
        )
        statusBarQuadBatch.addQuad(rect: borderRect, color: statusBarBorderColor)

        if !statusBarLeftText.isEmpty {
            let leftWidth = statusBarTextWidth(statusBarLeftText)
            let rectHeight = max(0, barHeight - statusBarModePadding.height * 2)
            let rect = CGRect(
                x: scrollOffset.x + statusBarTextInsets.left,
                y: scrollOffset.y + barY + statusBarModePadding.height,
                width: leftWidth + statusBarModePadding.width * 2,
                height: rectHeight
            )
            statusBarQuadBatch.addQuad(rect: rect, color: statusBarModeBackgroundColor)
        }

        let baselineY = barY + (barHeight - statusBarLineHeight) / 2 + statusBarBaselineOffset
        let leftColor = statusBarModeTextColor.simdColor
        let rightColor = statusBarSecondaryTextColor.simdColor
        let badgeTextColor = statusBarBadgeTextColor.simdColor

        if !statusBarLeftText.isEmpty {
            addStatusBarText(
                statusBarLeftText,
                x: statusBarTextInsets.left,
                baselineY: baselineY,
                color: leftColor
            )
        }

        let rightEdge = bounds.width - statusBarTextInsets.right
        var rightTextStartX: CGFloat?
        if !statusBarRightText.isEmpty {
            let rightWidth = statusBarTextWidth(statusBarRightText)
            rightTextStartX = max(statusBarTextInsets.left, rightEdge - rightWidth)
        }

        if !statusBarRightBadgeText.isEmpty {
            let badgeTextWidth = statusBarTextWidth(statusBarRightBadgeText)
            let rectHeight = max(0, barHeight - statusBarBadgePadding.height * 2)
            let rectWidth = badgeTextWidth + statusBarBadgePadding.width * 2
            let badgeRightEdge = (rightTextStartX ?? rightEdge) - statusBarBadgeSpacing
            let rectX = scrollOffset.x + max(statusBarTextInsets.left, badgeRightEdge - rectWidth)
            let rectY = scrollOffset.y + barY + statusBarBadgePadding.height
            let rect = CGRect(x: rectX, y: rectY, width: rectWidth, height: rectHeight)
            statusBarQuadBatch.addQuad(rect: rect, color: statusBarBadgeBackgroundColor)
            let badgeTextX = rectX - scrollOffset.x + statusBarBadgePadding.width
            addStatusBarText(
                statusBarRightBadgeText,
                x: badgeTextX,
                baselineY: baselineY,
                color: badgeTextColor
            )
        }

        if !statusBarRightText.isEmpty, let startX = rightTextStartX {
            addStatusBarText(
                statusBarRightText,
                x: startX,
                baselineY: baselineY,
                color: rightColor
            )
        }
    }

    private func prepareSearchOverlayBatches() {
        searchOverlayQuadBatch.clear()
        searchOverlayGlyphBatch.clear()
        searchOverlayColorGlyphBatch.clear()
        searchOverlayHitAreas.removeAll()
        searchOverlayRect = nil

        guard searchOverlayVisible else { return }
        guard bounds.width > 0, bounds.height > 0 else { return }

        let rowHeight = max(24, statusBarLineHeight + 6)
        let countText = searchOverlayCountText()

        let caseLabel = "Aa"
        let currentLabel = "Current"
        let openLabel = "Open"
        let prevLabel = "Prev"
        let nextLabel = "Next"

        let caseWidth = searchOverlayTextWidth(caseLabel) + searchOverlayButtonPadding * 2
        let currentWidth = searchOverlayTextWidth(currentLabel) + searchOverlayButtonPadding * 2
        let openWidth = searchOverlayTextWidth(openLabel) + searchOverlayButtonPadding * 2
        let scopeWidth = currentWidth + openWidth
        let prevWidth = searchOverlayTextWidth(prevLabel) + searchOverlayButtonPadding * 2
        let nextWidth = searchOverlayTextWidth(nextLabel) + searchOverlayButtonPadding * 2
        let countWidth = countText.isEmpty ? 0 : searchOverlayTextWidth(countText)

        let maxFieldWidth = max(140, bounds.width - searchOverlayMargin * 2 - (caseWidth + scopeWidth + searchOverlayItemSpacing * 2 + searchOverlayPadding * 2))
        let fieldWidth = min(320, maxFieldWidth)

        let row1Width = fieldWidth + searchOverlayItemSpacing + caseWidth + searchOverlayItemSpacing + scopeWidth
        let row2Width = prevWidth + searchOverlayItemSpacing + nextWidth + (countWidth > 0 ? (searchOverlayItemSpacing + countWidth) : 0)
        let overlayWidth = max(row1Width, row2Width) + searchOverlayPadding * 2
        let overlayHeight = searchOverlayPadding * 2 + rowHeight * 2 + searchOverlayRowSpacing

        let overlayX = max(searchOverlayMargin, bounds.width - overlayWidth - searchOverlayMargin)
        let overlayY = max(searchOverlayMargin, bounds.height - overlayHeight - searchOverlayMargin)
        let overlayRect = CGRect(x: overlayX, y: overlayY, width: overlayWidth, height: overlayHeight)
        searchOverlayRect = overlayRect

        let bgRect = overlayRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y)
        searchOverlayQuadBatch.addQuad(rect: bgRect, color: searchOverlayBackgroundColor)

        let borderThickness = max(1.0 / max(1.0, backingScaleFactor), 1.0)
        let borderTop = CGRect(x: bgRect.minX, y: bgRect.maxY - borderThickness, width: bgRect.width, height: borderThickness)
        let borderBottom = CGRect(x: bgRect.minX, y: bgRect.minY, width: bgRect.width, height: borderThickness)
        let borderLeft = CGRect(x: bgRect.minX, y: bgRect.minY, width: borderThickness, height: bgRect.height)
        let borderRight = CGRect(x: bgRect.maxX - borderThickness, y: bgRect.minY, width: borderThickness, height: bgRect.height)
        searchOverlayQuadBatch.addQuad(rect: borderTop, color: searchOverlayBorderColor)
        searchOverlayQuadBatch.addQuad(rect: borderBottom, color: searchOverlayBorderColor)
        searchOverlayQuadBatch.addQuad(rect: borderLeft, color: searchOverlayBorderColor)
        searchOverlayQuadBatch.addQuad(rect: borderRight, color: searchOverlayBorderColor)

        let row1Y = overlayY + overlayHeight - searchOverlayPadding - rowHeight
        let row2Y = overlayY + searchOverlayPadding

        var cursorX = overlayX + searchOverlayPadding
        let fieldRect = CGRect(x: cursorX, y: row1Y, width: fieldWidth, height: rowHeight)
        cursorX += fieldWidth + searchOverlayItemSpacing
        let caseRect = CGRect(x: cursorX, y: row1Y, width: caseWidth, height: rowHeight)
        cursorX += caseWidth + searchOverlayItemSpacing
        let scopeRect = CGRect(x: cursorX, y: row1Y, width: scopeWidth, height: rowHeight)
        let currentRect = CGRect(x: scopeRect.minX, y: scopeRect.minY, width: currentWidth, height: scopeRect.height)
        let openRect = CGRect(x: currentRect.maxX, y: scopeRect.minY, width: openWidth, height: scopeRect.height)

        let prevRect = CGRect(x: overlayX + searchOverlayPadding, y: row2Y, width: prevWidth, height: rowHeight)
        let nextRect = CGRect(x: prevRect.maxX + searchOverlayItemSpacing, y: row2Y, width: nextWidth, height: rowHeight)
        let countRect = countText.isEmpty
            ? CGRect.zero
            : CGRect(x: nextRect.maxX + searchOverlayItemSpacing, y: row2Y, width: countWidth, height: rowHeight)

        searchOverlayHitAreas.append(SearchOverlayHitArea(action: .field, rect: fieldRect))
        searchOverlayHitAreas.append(SearchOverlayHitArea(action: .toggleCase, rect: caseRect))
        searchOverlayHitAreas.append(SearchOverlayHitArea(action: .scopeCurrent, rect: currentRect))
        searchOverlayHitAreas.append(SearchOverlayHitArea(action: .scopeOpen, rect: openRect))
        searchOverlayHitAreas.append(SearchOverlayHitArea(action: .prev, rect: prevRect))
        searchOverlayHitAreas.append(SearchOverlayHitArea(action: .next, rect: nextRect))

        let fieldBorder = searchOverlayActive ? searchOverlayFieldActiveBorderColor : searchOverlayFieldBorderColor
        let fieldBgRect = fieldRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y)
        searchOverlayQuadBatch.addQuad(rect: fieldBgRect, color: searchOverlayFieldBackgroundColor)
        searchOverlayQuadBatch.addQuad(rect: CGRect(x: fieldBgRect.minX, y: fieldBgRect.minY, width: fieldBgRect.width, height: borderThickness), color: fieldBorder)
        searchOverlayQuadBatch.addQuad(rect: CGRect(x: fieldBgRect.minX, y: fieldBgRect.maxY - borderThickness, width: fieldBgRect.width, height: borderThickness), color: fieldBorder)
        searchOverlayQuadBatch.addQuad(rect: CGRect(x: fieldBgRect.minX, y: fieldBgRect.minY, width: borderThickness, height: fieldBgRect.height), color: fieldBorder)
        searchOverlayQuadBatch.addQuad(rect: CGRect(x: fieldBgRect.maxX - borderThickness, y: fieldBgRect.minY, width: borderThickness, height: fieldBgRect.height), color: fieldBorder)

        let row1Baseline = row1Y + (rowHeight - statusBarLineHeight) / 2 + statusBarBaselineOffset
        let row2Baseline = row2Y + (rowHeight - statusBarLineHeight) / 2 + statusBarBaselineOffset

        let queryText = searchOverlayQuery.isEmpty ? searchOverlayPlaceholder : searchOverlayQuery
        let queryColor = (searchOverlayQuery.isEmpty ? searchOverlayPlaceholderColor : searchOverlayTextColor).simdColor
        let fieldTextX = fieldRect.minX + searchOverlayFieldPadding
        addSearchOverlayText(
            queryText,
            x: fieldTextX,
            baselineY: row1Baseline,
            color: queryColor
        )

        if searchOverlayActive {
            let queryWidth = searchOverlayTextWidth(searchOverlayQuery)
            let caretX = min(fieldRect.maxX - searchOverlayFieldPadding, fieldTextX + queryWidth + 1)
            let caretRect = CGRect(
                x: caretX + scrollOffset.x,
                y: row1Y + (rowHeight - statusBarLineHeight) / 2 + scrollOffset.y,
                width: max(1.0 / max(1.0, backingScaleFactor), 1.0),
                height: statusBarLineHeight
            )
            searchOverlayQuadBatch.addQuad(rect: caretRect, color: searchOverlayTextColor)
        }

        let caseActive = searchOverlayCaseSensitive
        let caseColor = (caseActive ? searchOverlayButtonActiveTextColor : searchOverlayButtonTextColor).simdColor
        let caseBg = backgroundColorForSearchOverlayAction(.toggleCase, active: caseActive)
        searchOverlayQuadBatch.addQuad(rect: caseRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y), color: caseBg)
        addCenteredSearchOverlayText(caseLabel, rect: caseRect, baselineY: row1Baseline, color: caseColor)

        let currentActive = searchOverlayScope == .currentFile
        let openActive = searchOverlayScope == .openDocuments
        let currentBg = backgroundColorForSearchOverlayAction(.scopeCurrent, active: currentActive)
        let openBg = backgroundColorForSearchOverlayAction(.scopeOpen, active: openActive)
        searchOverlayQuadBatch.addQuad(rect: currentRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y), color: currentBg)
        searchOverlayQuadBatch.addQuad(rect: openRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y), color: openBg)

        let separatorRect = CGRect(
            x: currentRect.maxX + scrollOffset.x - borderThickness / 2,
            y: currentRect.minY + scrollOffset.y,
            width: borderThickness,
            height: currentRect.height
        )
        searchOverlayQuadBatch.addQuad(rect: separatorRect, color: searchOverlayBorderColor)

        let currentColor = (currentActive ? searchOverlayButtonActiveTextColor : searchOverlayButtonTextColor).simdColor
        let openColor = (openActive ? searchOverlayButtonActiveTextColor : searchOverlayButtonTextColor).simdColor
        addCenteredSearchOverlayText(currentLabel, rect: currentRect, baselineY: row1Baseline, color: currentColor)
        addCenteredSearchOverlayText(openLabel, rect: openRect, baselineY: row1Baseline, color: openColor)

        let prevBg = backgroundColorForSearchOverlayAction(.prev, active: false)
        let nextBg = backgroundColorForSearchOverlayAction(.next, active: false)
        searchOverlayQuadBatch.addQuad(rect: prevRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y), color: prevBg)
        searchOverlayQuadBatch.addQuad(rect: nextRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y), color: nextBg)
        addCenteredSearchOverlayText(prevLabel, rect: prevRect, baselineY: row2Baseline, color: searchOverlayButtonTextColor.simdColor)
        addCenteredSearchOverlayText(nextLabel, rect: nextRect, baselineY: row2Baseline, color: searchOverlayButtonTextColor.simdColor)

        if !countText.isEmpty {
            let countColor = searchOverlayPlaceholderColor.simdColor
            addSearchOverlayText(
                countText,
                x: countRect.minX,
                baselineY: row2Baseline,
                color: countColor
            )
        }
    }

    private func searchOverlayCountText() -> String {
        guard let count = searchOverlayMatchCount else { return "" }
        if count == 0 { return "0" }
        let index = max(1, searchOverlayMatchIndex ?? 1)
        return "\(index)/\(count)"
    }

    private func backgroundColorForSearchOverlayAction(_ action: SearchOverlayAction, active: Bool) -> NSColor {
        if active { return searchOverlayButtonActiveBackgroundColor }
        if searchOverlayHoverAction == action { return searchOverlayButtonHoverBackgroundColor }
        return searchOverlayButtonBackgroundColor
    }

    private func addSearchOverlayText(_ text: String, x: CGFloat, baselineY: CGFloat, color: SIMD4<Float>) {
        guard !text.isEmpty else { return }
        let shaped = cachedOverlayGlyphs(text, font: currentFont)
        guard !shaped.isEmpty else { return }
        let bounds = overlayBounds(for: shaped)
        let startX = x + scrollOffset.x - bounds.minX
        let penY = baselineY + scrollOffset.y
        for (glyph, cached) in shaped {
            let position = CGPoint(x: startX + glyph.position.x, y: penY)
            if cached.isColor {
                let colorGlyph = SIMD4<Float>(1, 1, 1, color.w)
                searchOverlayColorGlyphBatch.addGlyph(cached: cached, screenPosition: position, color: colorGlyph)
            } else {
                searchOverlayGlyphBatch.addGlyph(cached: cached, screenPosition: position, color: color)
            }
        }
    }

    private func addCenteredSearchOverlayText(_ text: String, rect: CGRect, baselineY: CGFloat, color: SIMD4<Float>) {
        let textWidth = searchOverlayTextWidth(text)
        let startX = rect.minX + (rect.width - textWidth) / 2
        addSearchOverlayText(text, x: startX, baselineY: baselineY, color: color)
    }

    private func searchOverlayTextWidth(_ text: String) -> CGFloat {
        guard !text.isEmpty else { return 0 }
        let shaped = cachedOverlayGlyphs(text, font: currentFont)
        guard !shaped.isEmpty else { return 0 }
        return overlayBounds(for: shaped).width
    }

    private func addStatusBarText(_ text: String, x: CGFloat, baselineY: CGFloat, color: SIMD4<Float>) {
        let shaped = cachedOverlayGlyphs(text, font: currentFont)
        guard !shaped.isEmpty else { return }
        let bounds = overlayBounds(for: shaped)
        let startX = x + scrollOffset.x - bounds.minX
        let penY = baselineY + scrollOffset.y
        for (glyph, cached) in shaped {
            let position = CGPoint(x: startX + glyph.position.x, y: penY)
            if cached.isColor {
                let colorGlyph = SIMD4<Float>(1, 1, 1, color.w)
                statusBarColorGlyphBatch.addGlyph(cached: cached, screenPosition: position, color: colorGlyph)
            } else {
                statusBarGlyphBatch.addGlyph(cached: cached, screenPosition: position, color: color)
            }
        }
    }

    private func statusBarTextWidth(_ text: String) -> CGFloat {
        let shaped = cachedOverlayGlyphs(text, font: currentFont)
        guard !shaped.isEmpty else { return 0 }
        return overlayBounds(for: shaped).width
    }

    private func isLineVisible(_ lineIndex: Int) -> Bool {
        visibleLineIndex(forDocumentLine: lineIndex) != nil
    }

    private var lineNumberColumnWidth: CGFloat {
        guard showsLineNumbers else { return 0 }
        let maxLine = max(1, lines.count)
        let sample = String(maxLine)
        return ceil((sample as NSString).size(withAttributes: [.font: gutterFont]).width)
    }

    private var foldMarkerAreaX: CGFloat {
        gutterInsets.left + lineNumberColumnWidth + foldMarkerSpacing
    }

    private func calculatedGutterWidth() -> CGFloat {
        let lineWidth = lineNumberColumnWidth
        let hasFoldMarkers = !foldRangeByStartLine.isEmpty
        let foldArea = hasFoldMarkers ? (foldMarkerSpacing + foldMarkerAreaWidth) : 0
        let indicatorWidth = showsGitGutter ? gutterIndicatorWidth : 0
        let calculated = ceil(gutterInsets.left + lineWidth + foldArea + gutterInsets.right + indicatorWidth + gutterSeparatorWidth)
        return max(gutterMinimumWidth, calculated)
    }

    private func addGutterText(_ text: String, baselineY: CGFloat, color: NSColor) {
        let shaped = cachedOverlayGlyphs(text, font: gutterFont)
        guard !shaped.isEmpty else { return }
        let bounds = overlayBounds(for: shaped)
        let totalWidth = bounds.width
        let availableWidth = lineNumberColumnWidth
        let startX = gutterInsets.left + max(0, availableWidth - totalWidth) - bounds.minX
        let colorSimd = color.simdColor
        for (glyph, cached) in shaped {
            let position = CGPoint(x: startX + glyph.position.x, y: baselineY)
            if cached.isColor {
                let colorGlyph = SIMD4<Float>(1, 1, 1, colorSimd.w)
                gutterColorGlyphBatch.addGlyph(cached: cached, screenPosition: position, color: colorGlyph)
            } else {
                gutterGlyphBatch.addGlyph(cached: cached, screenPosition: position, color: colorSimd)
            }
        }
    }

    private func addGutterSymbol(_ text: String, baselineY: CGFloat, x: CGFloat, color: NSColor) {
        let shaped = cachedOverlayGlyphs(text, font: gutterFont)
        guard !shaped.isEmpty else { return }
        let bounds = overlayBounds(for: shaped)
        let penX = x - bounds.minX
        let colorSimd = color.simdColor
        for (glyph, cached) in shaped {
            let position = CGPoint(x: penX + glyph.position.x, y: baselineY)
            if cached.isColor {
                let colorGlyph = SIMD4<Float>(1, 1, 1, colorSimd.w)
                gutterColorGlyphBatch.addGlyph(cached: cached, screenPosition: position, color: colorGlyph)
            } else {
                gutterGlyphBatch.addGlyph(cached: cached, screenPosition: position, color: colorSimd)
            }
        }
    }

    private func cachedOverlayGlyphs(_ text: String, font: NSFont) -> [(glyph: ShapedGlyph, cached: CachedGlyph)] {
        let shapedGlyphs = shapeOverlayText(text, font: font)
        guard let renderer else { return [] }

        var results: [(ShapedGlyph, CachedGlyph)] = []
        results.reserveCapacity(shapedGlyphs.count)

        for glyph in shapedGlyphs {
            if let cached = renderer.glyphAtlas.glyph(for: glyph.glyphID, font: glyph.font) {
                results.append((glyph, cached))
            }
        }

        return results
    }

    private func overlayBounds(for glyphs: [(glyph: ShapedGlyph, cached: CachedGlyph)]) -> (minX: CGFloat, maxX: CGFloat, width: CGFloat) {
        var minX = CGFloat.greatestFiniteMagnitude
        var maxX = CGFloat.leastNormalMagnitude

        for (glyph, cached) in glyphs {
            let glyphMinX = glyph.position.x + cached.bearing.x
            let glyphMaxX = glyphMinX + cached.size.width
            minX = min(minX, glyphMinX)
            maxX = max(maxX, glyphMaxX)
        }

        if minX == CGFloat.greatestFiniteMagnitude { return (0, 0, 0) }
        return (minX, maxX, max(0, maxX - minX))
    }

    private func shapeOverlayText(_ text: String, font: NSFont) -> [ShapedGlyph] {
        guard !text.isEmpty else { return [] }

        let attributes: [NSAttributedString.Key: Any] = [
            .font: font,
            .ligature: 1
        ]
        let attrString = NSAttributedString(string: text, attributes: attributes)
        let line = CTLineCreateWithAttributedString(attrString)
        let runs = CTLineGetGlyphRuns(line) as? [CTRun] ?? []

        var result: [ShapedGlyph] = []
        let utf16Length = (text as NSString).length

        for run in runs {
            let glyphCount = CTRunGetGlyphCount(run)
            guard glyphCount > 0 else { continue }

            let attributes = CTRunGetAttributes(run) as NSDictionary
            let runFont = attributes[kCTFontAttributeName] as! CTFont

            var glyphs = [CGGlyph](repeating: 0, count: glyphCount)
            CTRunGetGlyphs(run, CFRangeMake(0, glyphCount), &glyphs)

            var positions = [CGPoint](repeating: .zero, count: glyphCount)
            CTRunGetPositions(run, CFRangeMake(0, glyphCount), &positions)

            var advances = [CGSize](repeating: .zero, count: glyphCount)
            CTRunGetAdvances(run, CFRangeMake(0, glyphCount), &advances)

            var indices = [CFIndex](repeating: 0, count: glyphCount)
            CTRunGetStringIndices(run, CFRangeMake(0, glyphCount), &indices)

            for i in 0..<glyphCount {
                let charIndex = Int(indices[i])
                let nextCharIndex = (i + 1 < glyphCount) ? Int(indices[i + 1]) : utf16Length
                let charCount = nextCharIndex - charIndex

                result.append(ShapedGlyph(
                    glyphID: glyphs[i],
                    position: positions[i],
                    advance: advances[i].width,
                    font: runFont,
                    characterIndex: charIndex,
                    characterCount: max(1, charCount)
                ))
            }
        }

        return result
    }

    private func addGutterGlyph(_ glyph: CachedGlyph, topLeft: CGPoint, color: NSColor) {
        gutterGlyphBatch.addGlyph(
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
        let iconSide = max(6, min(foldMarkerAreaWidth - 2, layoutEngine.calculatedLineHeight * foldMarkerIconScale))
        let lineWidth = max(1, min(foldMarkerIconLineWidth, iconSide * 0.25))
        let hoverPadding = max(1, foldMarkerHoverPadding)
        let hoverSide = min(foldMarkerAreaWidth, layoutEngine.calculatedLineHeight - 2, iconSide + hoverPadding * 2)
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
        if handleSearchOverlayMouseDown(at: locationInView) {
            return
        }
        if handleGutterMouseDown(at: locationInView) {
            return
        }
        if statusBarEnabled && locationInView.y > bounds.height - statusBarTotalHeight {
            return
        }
        if showsGutter && locationInView.x < gutterWidth {
            return
        }
        textDelegate?.metalTextView(self, didClickAt: locationInView)
    }

    override public func mouseDragged(with event: NSEvent) {
        lastMouseModifiers = event.modifierFlags
        let locationInView = convert(event.locationInWindow, from: nil)
        if isPointInsideSearchOverlay(locationInView) {
            return
        }
        if statusBarEnabled && locationInView.y > bounds.height - statusBarTotalHeight {
            return
        }
        if showsGutter && locationInView.x < gutterWidth {
            return
        }
        textDelegate?.metalTextView(self, didDragTo: locationInView)
    }

    override public func mouseMoved(with event: NSEvent) {
        updateHoverState(with: event)
    }

    override public func mouseExited(with event: NSEvent) {
        hoveredFoldLine = nil
        if searchOverlayHoverAction != nil {
            searchOverlayHoverAction = nil
        }
    }

    override public func updateTrackingAreas() {
        super.updateTrackingAreas()
        if let area = gutterTrackingArea {
            removeTrackingArea(area)
        }
        let options: NSTrackingArea.Options = [.mouseMoved, .mouseEnteredAndExited, .activeInKeyWindow, .inVisibleRect]
        let area = NSTrackingArea(rect: bounds, options: options, owner: self, userInfo: nil)
        addTrackingArea(area)
        gutterTrackingArea = area
    }

    private func handleGutterMouseDown(at point: CGPoint) -> Bool {
        guard showsGutter, gutterWidth > 0 else { return false }
        guard point.x <= gutterWidth else { return false }

        guard let line = documentLineIndex(atY: point.y) else { return true }
        guard foldRangeByStartLine[line] != nil else { return true }

        let markerLeft = foldMarkerAreaX
        let markerRight = markerLeft + foldMarkerAreaWidth
        if point.x >= markerLeft && point.x <= markerRight {
            onToggleFold?(line)
        }
        return true
    }

    private func handleSearchOverlayMouseDown(at point: CGPoint) -> Bool {
        guard searchOverlayVisible else { return false }
        guard let overlayRect = searchOverlayRect, overlayRect.contains(point) else { return false }

        if let hit = searchOverlayHitAreas.first(where: { $0.rect.contains(point) }) {
            switch hit.action {
            case .field:
                textDelegate?.metalTextViewDidActivateSearchOverlay(self)
            case .toggleCase:
                textDelegate?.metalTextView(self, didToggleSearchCase: !searchOverlayCaseSensitive)
            case .scopeCurrent:
                textDelegate?.metalTextView(self, didSetSearchScope: .currentFile)
            case .scopeOpen:
                textDelegate?.metalTextView(self, didSetSearchScope: .openDocuments)
            case .prev:
                textDelegate?.metalTextViewDidRequestSearchPrev(self)
            case .next:
                textDelegate?.metalTextViewDidRequestSearchNext(self)
            }
        } else {
            textDelegate?.metalTextViewDidActivateSearchOverlay(self)
        }

        return true
    }

    private func updateSearchOverlayHover(at point: CGPoint) -> Bool {
        guard searchOverlayVisible, let overlayRect = searchOverlayRect else {
            if searchOverlayHoverAction != nil {
                searchOverlayHoverAction = nil
            }
            return false
        }
        guard overlayRect.contains(point) else {
            if searchOverlayHoverAction != nil {
                searchOverlayHoverAction = nil
            }
            return false
        }

        let newHover = searchOverlayHitAreas.first(where: { $0.rect.contains(point) })?.action
        if newHover != searchOverlayHoverAction {
            searchOverlayHoverAction = newHover
        }
        return true
    }

    private func isPointInsideSearchOverlay(_ point: CGPoint) -> Bool {
        guard searchOverlayVisible, let overlayRect = searchOverlayRect else { return false }
        return overlayRect.contains(point)
    }

    private func updateHoverState(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        if updateSearchOverlayHover(at: point) {
            hoveredFoldLine = nil
            return
        }
        guard showsGutter, gutterWidth > 0 else {
            hoveredFoldLine = nil
            return
        }
        if point.x > gutterWidth {
            hoveredFoldLine = nil
            return
        }
        if statusBarEnabled && point.y > bounds.height - statusBarTotalHeight {
            hoveredFoldLine = nil
            return
        }

        guard let line = documentLineIndex(atY: point.y) else {
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

    // MARK: - Hit Testing

    /// Convert point to character position
    public func characterPosition(at point: CGPoint) -> (line: Int, column: Int)? {
        if statusBarEnabled && point.y > bounds.height - statusBarTotalHeight {
            return nil
        }
        if showsGutter && point.x < gutterWidth {
            return nil
        }
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

    /// Insertion rect in view coordinates for the primary cursor.
    public func insertionRect() -> CGRect? {
        guard cursorLine >= 0 && cursorLine < lines.count else { return nil }
        guard let layout = layoutForLine(cursorLine) else { return nil }
        let lineHeight = layoutEngine.calculatedLineHeight
        let xPos = textInsets.left + layoutEngine.xPosition(forCharacterOffset: cursorColumn, in: layout)
        let yPos = layout.yOffset
        let viewX = xPos - scrollOffset.x
        let viewY = yPos - scrollOffset.y
        return CGRect(x: viewX, y: viewY, width: 1, height: lineHeight)
    }

    /// UTF-16 insertion offset for the primary cursor.
    public func insertionOffset() -> Int? {
        guard cursorLine >= 0 && cursorLine < lines.count else { return nil }
        let lineStart = lineStartOffsetUTF16(cursorLine)
        let column = min(max(0, cursorColumn), lineUTF16Length(cursorLine))
        return lineStart + column
    }
}

// MARK: - Delegate Protocol

public protocol MetalTextViewDelegate: AnyObject {
    func metalTextView(_ view: MetalTextView, didChangeText text: String)
    func metalTextView(_ view: MetalTextView, didChangeSelection ranges: [NSRange])
    func metalTextView(_ view: MetalTextView, didMoveCursor line: Int, column: Int)
    func metalTextView(_ view: MetalTextView, didClickAt point: CGPoint)
    func metalTextView(_ view: MetalTextView, didDragTo point: CGPoint)
    func metalTextViewDidActivateSearchOverlay(_ view: MetalTextView)
    func metalTextViewDidRequestSearchPrev(_ view: MetalTextView)
    func metalTextViewDidRequestSearchNext(_ view: MetalTextView)
    func metalTextView(_ view: MetalTextView, didToggleSearchCase isCaseSensitive: Bool)
    func metalTextView(_ view: MetalTextView, didSetSearchScope scope: MetalTextView.SearchOverlayScope)
}

public extension MetalTextViewDelegate {
    func metalTextViewDidActivateSearchOverlay(_ view: MetalTextView) {}
    func metalTextViewDidRequestSearchPrev(_ view: MetalTextView) {}
    func metalTextViewDidRequestSearchNext(_ view: MetalTextView) {}
    func metalTextView(_ view: MetalTextView, didToggleSearchCase isCaseSensitive: Bool) {}
    func metalTextView(_ view: MetalTextView, didSetSearchScope scope: MetalTextView.SearchOverlayScope) {}
}
