import Foundation
import MetalKit
import AppKit
import QuartzCore
import CoreText
import VVMetalPrimitives
import VVMarkdown
import VVGit
import VVLSP

/// Metal-based text view for code rendering
public final class MetalTextView: MTKView {

    // Use flipped coordinates (Y=0 at top) for proper AppKit integration
    override public var isFlipped: Bool { true }

    // Set I-beam cursor for text editing
    override public func resetCursorRects() {
        addCursorRect(bounds, cursor: .iBeam)
    }

    // MARK: - Properties

    public private(set) var renderer: MarkdownMetalRenderer!
    public private(set) var layoutEngine: TextLayoutEngine!


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
    private var gutterInsets: NSEdgeInsets = NSEdgeInsets(top: 4, left: 12, bottom: 4, right: 14)
    private var gutterMinimumWidth: CGFloat = 0
    private var foldMarkerAreaWidth: CGFloat = 16
    private var foldMarkerSpacing: CGFloat = 6
    private let gutterIndicatorWidth: CGFloat = 2
    private let gutterSeparatorWidth: CGFloat = 0
    private var reserveFoldMarkerSpace: Bool = true
    private var foldRanges: [MetalGutterFoldRange] = []
    private var foldRangeByStartLine: [Int: MetalGutterFoldRange] = [:]
    private var foldedStartLines: Set<Int> = []
    private var gitHunks: [MetalGutterGitHunk] = []
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

    private var foldMarkerIconScale: CGFloat = 0.5
    private var foldMarkerIconLineWidth: CGFloat = 1.3
    private var foldMarkerHoverPadding: CGFloat = 5
    private var foldMarkerHoverCornerRadius: CGFloat = 4
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

    // Scene buffers (primitive-based rendering)
    private var contentTextRuns: [VVTextRunPrimitive] = []
    private var gutterTextRuns: [VVTextRunPrimitive] = []
    private var statusBarTextRuns: [VVTextRunPrimitive] = []
    private var searchOverlayTextRuns: [VVTextRunPrimitive] = []
    private var completionTextRuns: [VVTextRunPrimitive] = []
    private var blameTextRuns: [VVTextRunPrimitive] = []

    private var gutterQuads: [VVQuadPrimitive] = []
    private var lineHighlightQuads: [VVQuadPrimitive] = []
    private var indentGuideQuads: [VVQuadPrimitive] = []
    private var activeIndentGuideQuads: [VVQuadPrimitive] = []
    private var searchMatchQuads: [VVQuadPrimitive] = []
    private var activeSearchMatchQuads: [VVQuadPrimitive] = []
    private var selectionQuads: [VVQuadPrimitive] = []
    private var bracketMatchQuads: [VVQuadPrimitive] = []
    private var markedTextQuads: [VVQuadPrimitive] = []
    private var cursorQuads: [VVQuadPrimitive] = []
    private var statusBarQuads: [VVQuadPrimitive] = []
    private var searchOverlayQuads: [VVQuadPrimitive] = []
    private var completionQuads: [VVQuadPrimitive] = []

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

    // Completion overlay
    private var completionVisible: Bool = false
    private var completionItems: [VVCompletionItem] = []
    private var completionSelectedIndex: Int = 0
    private var completionAnchorOffset: Int = 0
    private var completionCursorOffset: Int = 0
    private let completionMaxVisibleItems: Int = 8

    // Blame overlay
    private var blameByLine: [Int: VVBlameInfo] = [:]
    private var showInlineBlame: Bool = false
    private var blameDelay: TimeInterval = 0.5
    private var blameVisibleLine: Int?
    private var blameTimer: Timer?

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
        let layerScale = (layer as? CAMetalLayer)?.contentsScale
            ?? window?.backingScaleFactor
            ?? NSScreen.main?.backingScaleFactor
            ?? 1.0
        if let metalLayer = layer as? CAMetalLayer {
            metalLayer.maximumDrawableCount = 2
        }

        // Initialize primitive renderer
        do {
            renderer = try MarkdownMetalRenderer(device: device, baseFont: font, scaleFactor: layerScale)
        } catch {
            print("Failed to initialize MarkdownMetalRenderer: \(error)")
            return
        }

        // Initialize layout engine
        let initialScale = window?.backingScaleFactor ?? NSScreen.main?.backingScaleFactor ?? 1.0
        backingScaleFactor = max(1.0, initialScale)
        layoutEngine = TextLayoutEngine(font: font, lineHeightMultiplier: lineHeightMultiplier, scaleFactor: backingScaleFactor)

        gutterFont = font
        updateStatusBarMetrics()

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

    private func scheduleBlameForCurrentLine() {
        blameTimer?.invalidate()
        blameTimer = nil
        blameVisibleLine = nil

        guard showInlineBlame else { return }
        let line = cursorLine
        guard blameByLine[line + 1] != nil else { return }

        if blameDelay <= 0 {
            blameVisibleLine = line
            scheduleRedraw()
            return
        }

        blameTimer = Timer.scheduledTimer(withTimeInterval: blameDelay, repeats: false) { [weak self] _ in
            guard let self = self else { return }
            self.blameVisibleLine = line
            self.scheduleRedraw()
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

    public func setFoldRanges(_ ranges: [MetalGutterFoldRange], foldedStartLines: Set<Int>) {
        foldRanges = ranges
        var map: [Int: MetalGutterFoldRange] = [:]
        for range in ranges where map[range.startLine] == nil {
            map[range.startLine] = range
        }
        foldRangeByStartLine = map
        self.foldedStartLines = foldedStartLines
        updateGutterMetrics()
        scheduleRedraw()
    }

    public func setGitHunks(_ hunks: [MetalGutterGitHunk]) {
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

    // MARK: - Completion Overlay

    public func setCompletionItems(_ items: [VVCompletionItem], anchorOffset: Int, cursorOffset: Int) {
        completionItems = items
        completionAnchorOffset = anchorOffset
        completionCursorOffset = cursorOffset
        completionSelectedIndex = max(0, min(completionSelectedIndex, max(0, items.count - 1)))
        completionVisible = !items.isEmpty
        scheduleRedraw()
    }

    public func updateCompletionSelection(_ index: Int) {
        completionSelectedIndex = max(0, min(index, max(0, completionItems.count - 1)))
        scheduleRedraw()
    }

    public func clearCompletions() {
        completionItems.removeAll()
        completionVisible = false
        completionSelectedIndex = 0
        scheduleRedraw()
    }

    public var isCompletionVisible: Bool {
        completionVisible
    }

    public func selectedCompletionItem() -> VVCompletionItem? {
        guard completionVisible, !completionItems.isEmpty else { return nil }
        let index = max(0, min(completionSelectedIndex, completionItems.count - 1))
        return completionItems[index]
    }

    public func completionAnchorRange() -> (anchor: Int, cursor: Int) {
        (completionAnchorOffset, completionCursorOffset)
    }

    // MARK: - Blame Overlay

    public func setBlameInfo(_ blameInfo: [VVBlameInfo], showInline: Bool, delay: TimeInterval) {
        blameByLine.removeAll()
        for info in blameInfo {
            blameByLine[info.lineNumber] = info
        }
        showInlineBlame = showInline
        blameDelay = delay
        scheduleBlameForCurrentLine()
    }

    public func clearBlameInfo() {
        blameByLine.removeAll()
        blameVisibleLine = nil
        blameTimer?.invalidate()
        blameTimer = nil
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
        scheduleBlameForCurrentLine()
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
        scheduleBlameForCurrentLine()
        scheduleRedraw()
    }

    /// Update font
    public func updateFont(_ font: NSFont, lineHeightMultiplier: CGFloat = 1.4) {
        currentFont = font
        gutterFont = font
        self.lineHeightMultiplier = lineHeightMultiplier
        rebuildRenderer(for: font)
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

        let scene = buildScene()
        renderScene(scene, encoder: encoder, renderer: renderer)

        encoder.endEncoding()

        if let drawable = currentDrawable {
            commandBuffer.present(drawable)
        }

        commandBuffer.commit()
    }

    private func buildScene() -> VVScene {
        prepareGutterBatches()
        prepareGlyphBatch()
        prepareIndentGuideBatch()
        prepareActiveIndentGuideBatch()
        prepareLineHighlightBatch()
        prepareSearchMatchBatch()
        prepareSelectionBatch()
        prepareBracketMatchBatch()
        prepareMarkedTextBatch()
        prepareCursorBatch()
        prepareStatusBarBatches()
        prepareSearchOverlayBatches()
        prepareCompletionOverlay()
        prepareBlameOverlay()

        var scene = VVScene()

        appendQuads(gutterQuads, to: &scene, zIndex: 1)
        appendQuads(lineHighlightQuads, to: &scene, zIndex: 2)
        appendQuads(indentGuideQuads, to: &scene, zIndex: 3)
        appendQuads(activeIndentGuideQuads, to: &scene, zIndex: 4)
        appendQuads(searchMatchQuads, to: &scene, zIndex: 5)
        appendQuads(activeSearchMatchQuads, to: &scene, zIndex: 6)
        appendQuads(selectionQuads, to: &scene, zIndex: 7)
        appendQuads(bracketMatchQuads, to: &scene, zIndex: 8)

        appendTextRuns(contentTextRuns, to: &scene, zIndex: 10)
        appendTextRuns(gutterTextRuns, to: &scene, zIndex: 11)
        appendTextRuns(blameTextRuns, to: &scene, zIndex: 12)

        appendQuads(markedTextQuads, to: &scene, zIndex: 13)
        appendQuads(cursorQuads, to: &scene, zIndex: 14)

        appendQuads(statusBarQuads, to: &scene, zIndex: 20)
        appendTextRuns(statusBarTextRuns, to: &scene, zIndex: 21)

        appendQuads(searchOverlayQuads, to: &scene, zIndex: 30)
        appendTextRuns(searchOverlayTextRuns, to: &scene, zIndex: 31)

        appendQuads(completionQuads, to: &scene, zIndex: 40)
        appendTextRuns(completionTextRuns, to: &scene, zIndex: 41)

        return scene
    }

    private func appendQuads(_ quads: [VVQuadPrimitive], to scene: inout VVScene, zIndex: Int) {
        for quad in quads {
            scene.add(kind: .quad(quad), zIndex: zIndex)
        }
    }

    private func appendTextRuns(_ runs: [VVTextRunPrimitive], to scene: inout VVScene, zIndex: Int) {
        for run in runs {
            scene.add(kind: .textRun(run), zIndex: zIndex)
        }
    }

    private func renderScene(_ scene: VVScene, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
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
                renderPrimitive(primitive, encoder: encoder, renderer: renderer)
            }
        }

        flushTextBatches()
        updateClip(nil)
    }

    private func renderPrimitive(_ primitive: VVPrimitive, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
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
            let borderColor = SIMD4<Float>(0.35, 0.35, 0.35, 1.0)
            let background = SIMD4<Float>(0.12, 0.12, 0.12, 1.0)
            let border = QuadInstance(
                position: SIMD2<Float>(Float(image.frame.origin.x), Float(image.frame.origin.y)),
                size: SIMD2<Float>(Float(image.frame.width), Float(image.frame.height)),
                color: borderColor,
                cornerRadius: Float(image.cornerRadius)
            )
            let innerFrame = image.frame.insetBy(dx: 1, dy: 1)
            let fill = QuadInstance(
                position: SIMD2<Float>(Float(innerFrame.origin.x), Float(innerFrame.origin.y)),
                size: SIMD2<Float>(Float(innerFrame.width), Float(innerFrame.height)),
                color: background,
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

        guard run.style.isLink || run.style.isStrikethrough else { return }

        let baseSize = max(1, currentFont.pointSize)
        let scale = baseSize > 0 ? run.fontSize / baseSize : 1
        let ascent = layoutEngine.calculatedBaselineOffset * scale
        let descent = max(1, (layoutEngine.calculatedLineHeight - layoutEngine.calculatedBaselineOffset) * scale)
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

    private func cachedGlyph(for glyph: VVTextGlyph, renderer: MarkdownMetalRenderer) -> MarkdownCachedGlyph? {
        let layoutVariant = toLayoutFontVariant(glyph.fontVariant)
        let cgGlyph = CGGlyph(glyph.glyphID)
        if let fontName = glyph.fontName {
            return renderer.glyphAtlas.glyph(for: cgGlyph, fontName: fontName, fontSize: glyph.fontSize, variant: layoutVariant)
        }
        return renderer.glyphAtlas.glyph(for: cgGlyph, variant: layoutVariant, fontSize: glyph.fontSize)
    }

    private func toLayoutFontVariant(_ variant: VVFontVariant) -> VVMarkdown.FontVariant {
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
        let width = max(1, Int(drawableSize.width))
        let height = max(1, Int(drawableSize.height))
        return MTLScissorRect(x: 0, y: 0, width: width, height: height)
    }

    private func scissorRect(for frame: CGRect) -> MTLScissorRect {
        let visibleFrame = frame.offsetBy(dx: -scrollOffset.x, dy: -scrollOffset.y)
        let viewBounds = CGRect(origin: .zero, size: bounds.size)
        let clipped = visibleFrame.intersection(viewBounds)
        if clipped.isNull || clipped.width <= 0 || clipped.height <= 0 {
            return fullScissorRect()
        }
        let scaleX = drawableSize.width / max(1, bounds.width)
        let scaleY = drawableSize.height / max(1, bounds.height)
        let x = max(0, Int(floor(clipped.minX * scaleX)))
        let y = max(0, Int(floor(clipped.minY * scaleY)))
        let maxWidth = max(1, Int(drawableSize.width) - x)
        let maxHeight = max(1, Int(drawableSize.height) - y)
        let width = min(maxWidth, Int(ceil(clipped.width * scaleX)))
        let height = min(maxHeight, Int(ceil(clipped.height * scaleY)))
        return MTLScissorRect(x: x, y: y, width: max(1, width), height: max(1, height))
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
            blameTimer?.invalidate()
            blameTimer = nil
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
        rebuildRenderer(for: currentFont)
        layoutEngine.updateFont(currentFont, lineHeightMultiplier: lineHeightMultiplier, scaleFactor: scale)
        updateStatusBarMetrics()
        updateGutterMetrics()
        invalidateLayout()
        updateEstimatedCharWidth()
        onContentSizeChange?()
        scheduleRedraw()
    }

    private func rebuildRenderer(for font: NSFont) {
        guard let device = device else { return }
        do {
            renderer = try MarkdownMetalRenderer(device: device, baseFont: font, scaleFactor: backingScaleFactor)
        } catch {
            print("Failed to rebuild MarkdownMetalRenderer: \(error)")
        }
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
        let advance = glyphAdvance(for: Character("M"), fontSize: currentFont.pointSize)
        estimatedCharWidth = max(1, advance > 0 ? advance : currentFont.pointSize * 0.6)
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
        let width = lastGlyph.position.x + glyphAdvance(for: lastGlyph.glyphID, font: lastGlyph.font)
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
        gutterQuads.removeAll(keepingCapacity: true)
        gutterTextRuns.removeAll(keepingCapacity: true)

        guard showsGutter, gutterWidth > 0 else { return }

        let backgroundRect = CGRect(
            x: scrollOffset.x,
            y: scrollOffset.y,
            width: gutterWidth,
            height: bounds.height
        )
        gutterQuads.append(VVQuadPrimitive(frame: backgroundRect, color: gutterBackgroundColor.simdColor))

        if let highlight = currentLineHighlightInfo() {
            let highlightRect = CGRect(
                x: scrollOffset.x,
                y: scrollOffset.y + highlight.y,
                width: gutterWidth,
                height: highlight.height
            )
            gutterQuads.append(VVQuadPrimitive(frame: highlightRect, color: currentLineHighlightColor.simdColor))
        }

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
                    gutterQuads.append(VVQuadPrimitive(frame: rect, color: color.simdColor))
                } else {
                    let height = CGFloat(hunk.lineCount) * layoutEngine.calculatedLineHeight
                    let rect = CGRect(x: quadX, y: quadY + 2, width: indicatorWidth, height: max(0, height - 4))
                    gutterQuads.append(VVQuadPrimitive(frame: rect, color: color.simdColor))
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
                if isHovered {
                    let bgX = foldMarkerAreaX + max(0, (foldMarkerAreaWidth - foldMetrics.hoverSize.width) / 2)
                    let bgY = baselineY - layoutEngine.calculatedBaselineOffset + (layoutEngine.calculatedLineHeight - foldMetrics.hoverSize.height) / 2
                    let rect = CGRect(x: bgX, y: bgY, width: foldMetrics.hoverSize.width, height: foldMetrics.hoverSize.height)
                    gutterQuads.append(VVQuadPrimitive(frame: rect, color: foldMarkerHoverBackgroundColor.simdColor, cornerRadius: foldMetrics.hoverCornerRadius))
                }

                let markerChar = foldMarkerCharacter(isFolded: isFolded)
                let marker = String(markerChar)
                let markerWidth = glyphAdvance(for: markerChar, fontSize: gutterFont.pointSize)
                let markerX = foldMarkerAreaX + max(0, (foldMarkerAreaWidth - markerWidth) / 2)
                let iconColor = isFolded ? foldMarkerActiveColor : (isHovered ? foldMarkerColor.withAlphaComponent(0.9) : foldMarkerColor)
                addGutterText(marker, baselineY: baselineY, color: iconColor, x: markerX)
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
        contentTextRuns.removeAll(keepingCapacity: true)

        let visibleRange = visibleLineRange(scrollOffset: scrollOffset.y, height: effectiveViewportHeight)
        let firstVisibleLine = visibleRange.first
        let lastVisibleLine = visibleRange.last
        guard firstVisibleLine >= 0 && lastVisibleLine >= firstVisibleLine else { return }

        for lineIndex in firstVisibleLine...lastVisibleLine {
            guard let layout = layoutForLine(lineIndex) else { continue }

            let baselineY = layout.yOffset + layout.baselineOffset
            let glyphs = layout.glyphs.compactMap { glyph -> VVTextGlyph? in
                makeTextGlyph(from: glyph, baselineY: baselineY)
            }

            if !glyphs.isEmpty {
                let run = VVTextRunPrimitive(
                    glyphs: glyphs,
                    style: VVTextRunStyle(color: defaultTextColor),
                    position: CGPoint(x: textInsets.left, y: baselineY),
                    fontSize: currentFont.pointSize
                )
                contentTextRuns.append(run)
            }

            if foldedRangeByStartLine[lineIndex] != nil {
                let placeholder = resolvedFoldPlaceholder()
                let lineLength = lineUTF16Length(lineIndex)
                let endX = textInsets.left + layoutEngine.xPosition(forCharacterOffset: lineLength, in: layout)
                let spaceWidth = glyphAdvance(for: Character(" "), fontSize: currentFont.pointSize)
                let placeholderX = endX + spaceWidth
                if let placeholderRun = makeTextRun(
                    placeholder,
                    baselineY: baselineY,
                    x: placeholderX,
                    color: foldPlaceholderColor.simdColor,
                    font: currentFont,
                    fontVariant: .monospace
                ) {
                    contentTextRuns.append(placeholderRun)
                }
            }
        }
    }

    private func prepareIndentGuideBatch() {
        indentGuideQuads.removeAll(keepingCapacity: true)
        guard !indentGuideSegments.isEmpty else { return }

        let lineHeight = layoutEngine.calculatedLineHeight
        guard lineHeight > 0 && lineHeight.isFinite else { return }

        let columnWidth = max(1, glyphAdvance(for: Character(" "), fontSize: currentFont.pointSize))
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
                output: &indentGuideQuads
            )
        }
    }

    private func prepareActiveIndentGuideBatch() {
        activeIndentGuideQuads.removeAll(keepingCapacity: true)
        guard !activeIndentGuideSegments.isEmpty else { return }

        let lineHeight = layoutEngine.calculatedLineHeight
        guard lineHeight > 0 && lineHeight.isFinite else { return }

        let columnWidth = max(1, glyphAdvance(for: Character(" "), fontSize: currentFont.pointSize))
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
                output: &activeIndentGuideQuads
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
        output: inout [VVQuadPrimitive]
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
                    output.append(VVQuadPrimitive(frame: rect, color: color.simdColor))
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
                    output.append(VVQuadPrimitive(frame: rect, color: color.simdColor))
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
            output.append(VVQuadPrimitive(frame: rect, color: color.simdColor))
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
            if glyphAdvance(for: ch, fontSize: currentFont.pointSize) <= 0 {
                return false
            }
        }
        return true
    }

    private func prepareSelectionBatch() {
        selectionQuads.removeAll(keepingCapacity: true)

        for range in selectionRanges {
            // Convert range to line/column coordinates and create selection rects
            let rects = rectsForRange(range)
            for rect in rects {
                selectionQuads.append(VVQuadPrimitive(frame: rect, color: selectionColor.simdColor))
            }
        }
    }

    private func prepareBracketMatchBatch() {
        bracketMatchQuads.removeAll(keepingCapacity: true)
        guard !bracketMatchRanges.isEmpty else { return }

        for range in bracketMatchRanges {
            let rects = rectsForRange(range)
            for rect in rects {
                bracketMatchQuads.append(VVQuadPrimitive(frame: rect, color: bracketHighlightColor.simdColor))
            }
        }
    }

    private func prepareSearchMatchBatch() {
        searchMatchQuads.removeAll(keepingCapacity: true)
        activeSearchMatchQuads.removeAll(keepingCapacity: true)

        guard !searchMatchRanges.isEmpty else {
            if let active = activeSearchMatch, active.length > 0 {
                let rects = rectsForRange(active)
                for rect in rects {
                    activeSearchMatchQuads.append(VVQuadPrimitive(frame: rect, color: activeSearchHighlightColor.simdColor))
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
                searchMatchQuads.append(VVQuadPrimitive(frame: rect, color: searchHighlightColor.simdColor))
            }
        }

        if let active = activeSearchMatch, active.length > 0 {
            let rects = rectsForRange(active)
            for rect in rects {
                activeSearchMatchQuads.append(VVQuadPrimitive(frame: rect, color: activeSearchHighlightColor.simdColor))
            }
        }
    }

    private func prepareMarkedTextBatch() {
        markedTextQuads.removeAll(keepingCapacity: true)
        guard let range = markedTextRange, range.length > 0 else { return }

        let lineHeight = layoutEngine.calculatedLineHeight
        let underlineThickness = max(1.0 / max(1.0, backingScaleFactor), 1.0)
        let underlineOffset: CGFloat = 1.0

        let rects = rectsForRange(range)
        for rect in rects {
            let y = min(rect.minY + lineHeight - underlineThickness - underlineOffset,
                        rect.minY + layoutEngine.calculatedBaselineOffset + underlineOffset)
            let underlineRect = CGRect(x: rect.minX, y: y, width: rect.width, height: underlineThickness)
            markedTextQuads.append(VVQuadPrimitive(frame: underlineRect, color: markedTextUnderlineColor.simdColor))
        }
    }

    private func prepareCursorBatch() {
        cursorQuads.removeAll(keepingCapacity: true)

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
            let defaultWidth = glyphAdvance(for: Character(" "), fontSize: currentFont.pointSize)
            let blockWidth = max(2, (xNext > xPos) ? (xNext - xPos) : defaultWidth)
            let width: CGFloat = (cursorStyle == .block) ? blockWidth : 2

            let rect = CGRect(x: xPos, y: layout.yOffset, width: width, height: layoutEngine.calculatedLineHeight)
            cursorQuads.append(VVQuadPrimitive(frame: rect, color: cursorColor.simdColor))
        }
    }

    private func prepareLineHighlightBatch() {
        lineHighlightQuads.removeAll(keepingCapacity: true)
        guard let highlight = currentLineHighlightInfo() else { return }
        let highlightX = showsGutter ? gutterWidth : 0
        let highlightWidth = max(0, bounds.width - highlightX + scrollOffset.x)
        let rect = CGRect(
            x: highlightX,
            y: highlight.y,
            width: highlightWidth,
            height: highlight.height
        )
        lineHighlightQuads.append(VVQuadPrimitive(frame: rect, color: currentLineHighlightColor.simdColor))
    }

    private func currentLineHighlightInfo() -> (line: Int, y: CGFloat, height: CGFloat)? {
        guard cursorLine < lines.count else { return nil }
        let currentRange = lineRangeUTF16(cursorLine)
        if currentRange.length > 0 {
            for selection in selectionRanges where selection.length > 0 {
                if NSIntersectionRange(selection, currentRange).length > 0 {
                    return nil
                }
            }
        }
        guard let layout = layoutForLine(cursorLine) else { return nil }
        let screenY = layout.yOffset - scrollOffset.y
        if screenY > effectiveViewportHeight || (screenY + layoutEngine.calculatedLineHeight) < 0 {
            return nil
        }
        return (cursorLine, layout.yOffset, layoutEngine.calculatedLineHeight)
    }

    private func prepareStatusBarBatches() {
        statusBarQuads.removeAll(keepingCapacity: true)
        statusBarTextRuns.removeAll(keepingCapacity: true)

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
        statusBarQuads.append(VVQuadPrimitive(frame: bgRect, color: statusBarBackgroundColor.simdColor))

        let borderHeight = max(1.0 / max(1.0, backingScaleFactor), 1.0)
        let borderRect = CGRect(
            x: scrollOffset.x,
            y: scrollOffset.y + barY + barHeight - borderHeight,
            width: bounds.width,
            height: borderHeight
        )
        statusBarQuads.append(VVQuadPrimitive(frame: borderRect, color: statusBarBorderColor.simdColor))

        if !statusBarLeftText.isEmpty {
            let leftWidth = statusBarTextWidth(statusBarLeftText)
            let rectHeight = max(0, barHeight - statusBarModePadding.height * 2)
            let rect = CGRect(
                x: scrollOffset.x + statusBarTextInsets.left,
                y: scrollOffset.y + barY + statusBarModePadding.height,
                width: leftWidth + statusBarModePadding.width * 2,
                height: rectHeight
            )
            statusBarQuads.append(VVQuadPrimitive(frame: rect, color: statusBarModeBackgroundColor.simdColor))
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
            statusBarQuads.append(VVQuadPrimitive(frame: rect, color: statusBarBadgeBackgroundColor.simdColor))
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
        searchOverlayQuads.removeAll(keepingCapacity: true)
        searchOverlayTextRuns.removeAll(keepingCapacity: true)
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
        searchOverlayQuads.append(VVQuadPrimitive(frame: bgRect, color: searchOverlayBackgroundColor.simdColor))

        let borderThickness = max(1.0 / max(1.0, backingScaleFactor), 1.0)
        let borderTop = CGRect(x: bgRect.minX, y: bgRect.maxY - borderThickness, width: bgRect.width, height: borderThickness)
        let borderBottom = CGRect(x: bgRect.minX, y: bgRect.minY, width: bgRect.width, height: borderThickness)
        let borderLeft = CGRect(x: bgRect.minX, y: bgRect.minY, width: borderThickness, height: bgRect.height)
        let borderRight = CGRect(x: bgRect.maxX - borderThickness, y: bgRect.minY, width: borderThickness, height: bgRect.height)
        searchOverlayQuads.append(VVQuadPrimitive(frame: borderTop, color: searchOverlayBorderColor.simdColor))
        searchOverlayQuads.append(VVQuadPrimitive(frame: borderBottom, color: searchOverlayBorderColor.simdColor))
        searchOverlayQuads.append(VVQuadPrimitive(frame: borderLeft, color: searchOverlayBorderColor.simdColor))
        searchOverlayQuads.append(VVQuadPrimitive(frame: borderRight, color: searchOverlayBorderColor.simdColor))

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
        searchOverlayQuads.append(VVQuadPrimitive(frame: fieldBgRect, color: searchOverlayFieldBackgroundColor.simdColor))
        searchOverlayQuads.append(VVQuadPrimitive(frame: CGRect(x: fieldBgRect.minX, y: fieldBgRect.minY, width: fieldBgRect.width, height: borderThickness), color: fieldBorder.simdColor))
        searchOverlayQuads.append(VVQuadPrimitive(frame: CGRect(x: fieldBgRect.minX, y: fieldBgRect.maxY - borderThickness, width: fieldBgRect.width, height: borderThickness), color: fieldBorder.simdColor))
        searchOverlayQuads.append(VVQuadPrimitive(frame: CGRect(x: fieldBgRect.minX, y: fieldBgRect.minY, width: borderThickness, height: fieldBgRect.height), color: fieldBorder.simdColor))
        searchOverlayQuads.append(VVQuadPrimitive(frame: CGRect(x: fieldBgRect.maxX - borderThickness, y: fieldBgRect.minY, width: borderThickness, height: fieldBgRect.height), color: fieldBorder.simdColor))

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
            searchOverlayQuads.append(VVQuadPrimitive(frame: caretRect, color: searchOverlayTextColor.simdColor))
        }

        let caseActive = searchOverlayCaseSensitive
        let caseColor = (caseActive ? searchOverlayButtonActiveTextColor : searchOverlayButtonTextColor).simdColor
        let caseBg = backgroundColorForSearchOverlayAction(.toggleCase, active: caseActive)
        searchOverlayQuads.append(VVQuadPrimitive(frame: caseRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y), color: caseBg.simdColor))
        addCenteredSearchOverlayText(caseLabel, rect: caseRect, baselineY: row1Baseline, color: caseColor)

        let currentActive = searchOverlayScope == .currentFile
        let openActive = searchOverlayScope == .openDocuments
        let currentBg = backgroundColorForSearchOverlayAction(.scopeCurrent, active: currentActive)
        let openBg = backgroundColorForSearchOverlayAction(.scopeOpen, active: openActive)
        searchOverlayQuads.append(VVQuadPrimitive(frame: currentRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y), color: currentBg.simdColor))
        searchOverlayQuads.append(VVQuadPrimitive(frame: openRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y), color: openBg.simdColor))

        let separatorRect = CGRect(
            x: currentRect.maxX + scrollOffset.x - borderThickness / 2,
            y: currentRect.minY + scrollOffset.y,
            width: borderThickness,
            height: currentRect.height
        )
        searchOverlayQuads.append(VVQuadPrimitive(frame: separatorRect, color: searchOverlayBorderColor.simdColor))

        let currentColor = (currentActive ? searchOverlayButtonActiveTextColor : searchOverlayButtonTextColor).simdColor
        let openColor = (openActive ? searchOverlayButtonActiveTextColor : searchOverlayButtonTextColor).simdColor
        addCenteredSearchOverlayText(currentLabel, rect: currentRect, baselineY: row1Baseline, color: currentColor)
        addCenteredSearchOverlayText(openLabel, rect: openRect, baselineY: row1Baseline, color: openColor)

        let prevBg = backgroundColorForSearchOverlayAction(.prev, active: false)
        let nextBg = backgroundColorForSearchOverlayAction(.next, active: false)
        searchOverlayQuads.append(VVQuadPrimitive(frame: prevRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y), color: prevBg.simdColor))
        searchOverlayQuads.append(VVQuadPrimitive(frame: nextRect.offsetBy(dx: scrollOffset.x, dy: scrollOffset.y), color: nextBg.simdColor))
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

    private func prepareCompletionOverlay() {
        completionQuads.removeAll(keepingCapacity: true)
        completionTextRuns.removeAll(keepingCapacity: true)
        guard completionVisible, !completionItems.isEmpty else { return }

        guard let layout = layoutForLine(cursorLine) else { return }

        let font = currentFont
        let rowHeight = max(22, statusBarLineHeight + 4)
        let padding: CGFloat = 8

        let visibleCount = min(completionItems.count, completionMaxVisibleItems)
        let labels = completionItems.prefix(visibleCount).map { $0.label }
        let maxLabelWidth = labels.map { overlayTextWidth($0, font: font) }.max() ?? 120

        let overlayWidth = max(200, maxLabelWidth + padding * 2)
        let overlayHeight = padding * 2 + CGFloat(visibleCount) * rowHeight

        let anchorX = textInsets.left + layoutEngine.xPosition(forCharacterOffset: cursorColumn, in: layout)
        let anchorY = layout.yOffset + layoutEngine.calculatedLineHeight

        var overlayX = anchorX
        var overlayY = anchorY

        // Flip above if it would overflow bottom
        if (overlayY - scrollOffset.y + overlayHeight) > bounds.height {
            overlayY = max(0, layout.yOffset - overlayHeight)
        }

        // Clamp horizontally within viewport
        let maxX = bounds.width - overlayWidth + scrollOffset.x
        overlayX = min(max(0, overlayX), max(0, maxX))

        let backgroundRect = CGRect(x: overlayX, y: overlayY, width: overlayWidth, height: overlayHeight)
        completionQuads.append(VVQuadPrimitive(frame: backgroundRect, color: searchOverlayBackgroundColor.simdColor, cornerRadius: 6))

        let borderThickness = max(1.0 / max(1.0, backingScaleFactor), 1.0)
        let borderRect = backgroundRect.insetBy(dx: -borderThickness / 2, dy: -borderThickness / 2)
        completionQuads.append(VVQuadPrimitive(frame: borderRect, color: searchOverlayBorderColor.simdColor, cornerRadius: 6))

        let selectedIndex = max(0, min(completionSelectedIndex, visibleCount - 1))
        for (index, item) in completionItems.prefix(visibleCount).enumerated() {
            let rowY = overlayY + padding + CGFloat(index) * rowHeight
            if index == selectedIndex {
                let highlightRect = CGRect(x: overlayX + 1, y: rowY, width: overlayWidth - 2, height: rowHeight)
                completionQuads.append(VVQuadPrimitive(frame: highlightRect, color: selectionColor.simdColor, cornerRadius: 4))
            }
            let baselineY = rowY + (rowHeight - statusBarLineHeight) / 2 + statusBarBaselineOffset
            let textX = overlayX + padding
            let textColor = (index == selectedIndex) ? themeTextColorForSelection() : searchOverlayTextColor.simdColor
            if let run = makeTextRun(item.label, baselineY: baselineY, x: textX, color: textColor, font: font, fontVariant: .regular) {
                completionTextRuns.append(run)
            }
        }
    }

    private func prepareBlameOverlay() {
        blameTextRuns.removeAll(keepingCapacity: true)
        guard showInlineBlame, let line = blameVisibleLine else { return }
        guard let info = blameByLine[line + 1] else { return }
        guard let layout = layoutForLine(line) else { return }

        let screenY = layout.yOffset - scrollOffset.y
        if screenY > effectiveViewportHeight || (screenY + layoutEngine.calculatedLineHeight) < 0 {
            return
        }

        let lineLength = lineUTF16Length(line)
        let endX = textInsets.left + layoutEngine.xPosition(forCharacterOffset: lineLength, in: layout)
        let spacer = glyphAdvance(for: Character(" "), fontSize: currentFont.pointSize) * 2
        let startX = endX + spacer
        let baselineY = layout.yOffset + layout.baselineOffset

        let blameText = formattedBlame(info)
        let font = currentFont.withSize(max(10, currentFont.pointSize - 2))
        let color = lineNumberColor.simdColor
        if let run = makeTextRun(blameText, baselineY: baselineY, x: startX, color: color, font: font, fontVariant: .regular) {
            blameTextRuns.append(run)
        }
    }

    private func themeTextColorForSelection() -> SIMD4<Float> {
        defaultTextColor
    }

    private func formattedBlame(_ info: VVBlameInfo) -> String {
        info.compactBlame
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
        guard let run = makeTextRun(
            text,
            baselineY: baselineY + scrollOffset.y,
            x: x + scrollOffset.x,
            color: color,
            font: currentFont,
            fontVariant: .regular
        ) else { return }
        searchOverlayTextRuns.append(run)
    }

    private func addCenteredSearchOverlayText(_ text: String, rect: CGRect, baselineY: CGFloat, color: SIMD4<Float>) {
        let textWidth = searchOverlayTextWidth(text)
        let startX = rect.minX + (rect.width - textWidth) / 2
        addSearchOverlayText(text, x: startX, baselineY: baselineY, color: color)
    }

    private func searchOverlayTextWidth(_ text: String) -> CGFloat {
        overlayTextWidth(text, font: currentFont)
    }

    private func addStatusBarText(_ text: String, x: CGFloat, baselineY: CGFloat, color: SIMD4<Float>) {
        guard let run = makeTextRun(
            text,
            baselineY: baselineY + scrollOffset.y,
            x: x + scrollOffset.x,
            color: color,
            font: currentFont,
            fontVariant: .regular
        ) else { return }
        statusBarTextRuns.append(run)
    }

    private func statusBarTextWidth(_ text: String) -> CGFloat {
        overlayTextWidth(text, font: currentFont)
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
        let hasFoldMarkers = reserveFoldMarkerSpace || !foldRangeByStartLine.isEmpty
        let foldArea = hasFoldMarkers ? (foldMarkerSpacing + foldMarkerAreaWidth) : 0
        let indicatorWidth = showsGitGutter ? gutterIndicatorWidth : 0
        let calculated = ceil(gutterInsets.left + lineWidth + foldArea + gutterInsets.right + indicatorWidth + gutterSeparatorWidth)
        return max(gutterMinimumWidth, calculated)
    }

    private func addGutterText(_ text: String, baselineY: CGFloat, color: NSColor, x: CGFloat? = nil) {
        let totalWidth = overlayTextWidth(text, font: gutterFont)
        let availableWidth = lineNumberColumnWidth
        let startX = x ?? (gutterInsets.left + max(0, availableWidth - totalWidth))
        guard let run = makeTextRun(
            text,
            baselineY: baselineY,
            x: startX,
            color: color.simdColor,
            font: gutterFont,
            fontVariant: .monospace
        ) else { return }
        gutterTextRuns.append(run)
    }

    private func overlayTextWidth(_ text: String, font: NSFont) -> CGFloat {
        let shaped = shapeOverlayText(text, font: font)
        guard let last = shaped.last else { return 0 }
        return max(0, last.position.x + last.advance)
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

    private func makeTextRun(
        _ text: String,
        baselineY: CGFloat,
        x: CGFloat,
        color: SIMD4<Float>,
        font: NSFont,
        fontVariant: VVFontVariant
    ) -> VVTextRunPrimitive? {
        let shaped = shapeOverlayText(text, font: font)
        guard !shaped.isEmpty else { return nil }
        let fontName = CTFontCopyPostScriptName(font as CTFont) as String
        var glyphs: [VVTextGlyph] = []
        glyphs.reserveCapacity(shaped.count)

        for glyph in shaped {
            let position = CGPoint(x: x + glyph.position.x, y: baselineY + glyph.position.y)
            let size = glyphSize(for: glyph.glyphID, font: glyph.font)
            glyphs.append(VVTextGlyph(
                glyphID: UInt16(glyph.glyphID),
                position: position,
                size: size,
                color: color,
                fontVariant: fontVariant,
                fontSize: font.pointSize,
                fontName: fontName,
                stringIndex: glyph.characterIndex
            ))
        }

        return VVTextRunPrimitive(
            glyphs: glyphs,
            style: VVTextRunStyle(color: color),
            position: CGPoint(x: x, y: baselineY),
            fontSize: font.pointSize
        )
    }

    private func makeTextGlyph(from glyph: LayoutGlyph, baselineY: CGFloat) -> VVTextGlyph? {
        let fontName = CTFontCopyPostScriptName(glyph.font) as String
        let size = glyphSize(for: glyph.glyphID, font: glyph.font)
        return VVTextGlyph(
            glyphID: UInt16(glyph.glyphID),
            position: CGPoint(x: textInsets.left + glyph.position.x, y: baselineY),
            size: size,
            color: glyph.color,
            fontVariant: .monospace,
            fontSize: currentFont.pointSize,
            fontName: fontName,
            stringIndex: glyph.characterIndex
        )
    }

    private func glyphSize(for glyphID: CGGlyph, font: CTFont) -> CGSize {
        var glyph = glyphID
        var rect = CGRect.zero
        CTFontGetBoundingRectsForGlyphs(font, .horizontal, &glyph, &rect, 1)
        return CGSize(width: max(0, rect.width), height: max(0, rect.height))
    }

    private func glyphAdvance(for glyphID: CGGlyph, font: CTFont) -> CGFloat {
        var glyph = glyphID
        var advance = CGSize.zero
        CTFontGetAdvancesForGlyphs(font, .horizontal, &glyph, &advance, 1)
        return advance.width
    }

    private func glyphAdvance(for character: Character, fontSize: CGFloat, variant: VVMarkdown.FontVariant = .monospace) -> CGFloat {
        guard let cached = renderer?.glyphAtlas.glyph(for: character, variant: variant, fontSize: fontSize) else {
            return estimatedCharWidth
        }
        return cached.advance
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
        if renderer?.glyphAtlas.glyph(for: preferred, variant: .monospace, fontSize: gutterFont.pointSize) != nil {
            return preferred
        }
        return isFolded ? "v" : ">"
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
        var locationInView = convert(event.locationInWindow, from: nil)
        if isPointInsideSearchOverlay(locationInView) {
            return
        }
        let textTop = max(0, bounds.height - statusBarTotalHeight)
        let textLeft = showsGutter ? gutterWidth : 0
        let isOutsideY = locationInView.y < 0 || locationInView.y > textTop
        let isOutsideX = locationInView.x < textLeft || locationInView.x > bounds.width
        if isOutsideY || isOutsideX {
            _ = autoscroll(with: event)
        }
        locationInView = clampSelectionPoint(locationInView)
        textDelegate?.metalTextView(self, didDragTo: locationInView)
    }

    private func clampSelectionPoint(_ point: CGPoint) -> CGPoint {
        let textTop = max(0, bounds.height - statusBarTotalHeight)
        let textLeft = showsGutter ? gutterWidth : 0
        let textRight = max(textLeft + 1, bounds.width)
        let textBottom: CGFloat = 0
        let clampedX = min(max(point.x, textLeft + 1), textRight - 1)
        let clampedY = min(max(point.y, textBottom + 1), max(textBottom + 1, textTop - 1))
        return CGPoint(x: clampedX, y: clampedY)
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
                    let spaceWidth: CGFloat = renderer?.glyphAtlas.glyph(
                        for: Character(" "),
                        variant: .regular,
                        fontSize: currentFont.pointSize
                    )?.advance ?? 8
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
