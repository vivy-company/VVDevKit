import AppKit
import CoreVideo
import CoreText
import MetalKit
import QuartzCore
import SwiftUI
import VVHighlighting
import VVMarkdown
import VVMetalPrimitives

// MARK: - Data Model

public typealias VVDiffRenderStyle = VVMarkdown.VVDiffRenderStyle
public typealias VVDiffRenderOptions = VVMarkdown.VVDiffRenderOptions
public typealias VVDiffChangeIndicatorStyle = VVMarkdown.VVDiffChangeIndicatorStyle
public typealias VVDiffInlineHighlightStyle = VVMarkdown.VVDiffInlineHighlightStyle
public typealias VVDiffRow = VVMarkdown.VVDiffRow
public typealias VVDiffInlineRenderResult = VVMarkdown.VVDiffRenderResult

private typealias VVDiffSection = VVMarkdown.VVDiffSection
private typealias VVDiffSplitRow = VVMarkdown.VVDiffSplitRow

public enum VVDiffInlineRenderer {
    public static func renderInline(
        unifiedDiff: String,
        width: CGFloat,
        theme: VVTheme,
        configuration: VVConfiguration
    ) -> VVDiffInlineRenderResult {
        VVDiffSceneRenderer.render(
            unifiedDiff: unifiedDiff,
            width: width,
            theme: diffMetalTheme(from: theme),
            baseFont: configuration.font,
            style: .inline
        )
    }
}

func diffMetalTheme(from theme: VVTheme) -> MarkdownTheme {
    var mdTheme: MarkdownTheme = theme.backgroundColor.brightnessComponent < 0.5 ? .dark : .light
    mdTheme.textColor = theme.textColor.simdColor
    mdTheme.codeColor = theme.textColor.simdColor
    mdTheme.codeBackgroundColor = theme.backgroundColor.simdColor
    mdTheme.codeHeaderBackgroundColor = theme.gutterBackgroundColor.simdColor
    mdTheme.codeHeaderTextColor = theme.textColor.simdColor
    mdTheme.codeHeaderDividerColor = markdownWithAlpha(theme.gutterTextColor.simdColor, 0.3)
    mdTheme.codeBorderColor = markdownWithAlpha(theme.gutterBackgroundColor.simdColor, 0.9)
    mdTheme.codeGutterBackgroundColor = theme.gutterBackgroundColor.simdColor
    mdTheme.codeGutterTextColor = theme.gutterTextColor.simdColor
    mdTheme.contentPadding = 0
    mdTheme.paragraphSpacing = 0
    return mdTheme
}

private func markdownWithAlpha(_ color: SIMD4<Float>, _ alpha: Float) -> SIMD4<Float> {
    SIMD4<Float>(color.x, color.y, color.z, alpha)
}

// MARK: - Text Selection Types

/// Position within the diff document: row index + character offset + pane.
private struct DiffTextPosition: Sendable, Hashable, Comparable, VVMetalPrimitives.VVTextPosition {
    let rowIndex: Int      // Index into rowGeometries array
    let charOffset: Int    // Character offset within row.text
    let paneX: CGFloat     // Pane origin X (0 for left/unified, columnWidth for right)

    init(rowIndex: Int, charOffset: Int, paneX: CGFloat = 0) {
        self.rowIndex = rowIndex
        self.charOffset = charOffset
        self.paneX = paneX
    }

    static func == (lhs: Self, rhs: Self) -> Bool {
        lhs.rowIndex == rhs.rowIndex && lhs.charOffset == rhs.charOffset
    }

    static func < (lhs: Self, rhs: Self) -> Bool {
        if lhs.rowIndex != rhs.rowIndex { return lhs.rowIndex < rhs.rowIndex }
        return lhs.charOffset < rhs.charOffset
    }
}

/// Geometry cache for a single visual row in the diff view.
private typealias RowGeometry = VVDiffLayoutVisualLine

private struct RowGeometryCacheKey: Equatable {
    let rowsSignature: Int
    let style: VVDiffRenderStyle
    let widthBucket: Int
    let wrapsUnified: Bool
    let fontSignature: Int
}

private struct ViewportSceneCacheKey: Equatable {
    let startBlockIndex: Int
    let endBlockIndex: Int
    let renderWidthBucket: Int
    let highlightVersion: Int

    func contains(
        renderWidth: CGFloat,
        highlightVersion: Int,
        requiredBlockRange: Range<Int>
    ) -> Bool {
        renderWidthBucket == Int((renderWidth * 2).rounded()) &&
        self.highlightVersion == highlightVersion &&
        startBlockIndex <= requiredBlockRange.lowerBound &&
        endBlockIndex >= requiredBlockRange.upperBound
    }
}

private typealias DisplayBlock = VVDiffLayoutBlock

struct VVDiffViewDebugMetrics {
    let rowGeometryCount: Int
    let totalVisualLineCount: Int
    let storedTextGeometryCount: Int
    let storedTextCharacterCount: Int
    let desiredHighlightRange: Range<Int>
    let codeRowCount: Int
    let contentHeight: CGFloat
    let totalDisplayBlockCount: Int
    let visibleDisplayBlockRange: Range<Int>
    let cachedRenderBlockRange: Range<Int>
    let cachedRenderDrawCallCount: Int

    var sceneCoversVisibleBlocks: Bool {
        cachedRenderBlockRange.lowerBound <= visibleDisplayBlockRange.lowerBound &&
        cachedRenderBlockRange.upperBound >= visibleDisplayBlockRange.upperBound
    }
}

private actor DiffViewportHighlighter {
    private struct CacheKey: Hashable {
        let rowID: Int
        let textHash: Int
        let languageID: String
        let usesDarkTheme: Bool
    }

    private var highlightersByLanguageID: [String: TreeSitterHighlighter] = [:]
    private var usesDarkTheme = true
    private var highlightTheme: HighlightTheme = .defaultDark
    private var rowCache: [CacheKey: [(NSRange, SIMD4<Float>)]] = [:]

    func clear() {
        rowCache.removeAll(keepingCapacity: true)
    }

    func highlightRanges(
        rows: [VVDiffRow],
        language: LanguageConfiguration,
        theme: VVTheme
    ) async -> [Int: [(NSRange, SIMD4<Float>)]] {
        await updateThemeIfNeeded(theme)
        guard let highlighter = await highlighter(for: language) else {
            return [:]
        }

        var result: [Int: [(NSRange, SIMD4<Float>)]] = [:]
        result.reserveCapacity(rows.count)

        for row in rows where row.kind.isCode {
            let cacheKey = makeCacheKey(row: row, languageID: language.identifier)
            if let cached = rowCache[cacheKey] {
                if !cached.isEmpty {
                    result[row.id] = cached
                }
                continue
            }

            let highlighted = await highlightRow(
                row,
                with: highlighter
            )
            rowCache[cacheKey] = highlighted
            if !highlighted.isEmpty {
                result[row.id] = highlighted
            }
        }

        return result
    }

    private func makeCacheKey(row: VVDiffRow, languageID: String) -> CacheKey {
        var hasher = Hasher()
        hasher.combine(row.text)
        return CacheKey(
            rowID: row.id,
            textHash: hasher.finalize(),
            languageID: languageID,
            usesDarkTheme: usesDarkTheme
        )
    }

    private func updateThemeIfNeeded(_ theme: VVTheme) async {
        let shouldUseDarkTheme = theme.backgroundColor.brightnessComponent < 0.5
        guard shouldUseDarkTheme != usesDarkTheme else { return }
        usesDarkTheme = shouldUseDarkTheme
        highlightTheme = shouldUseDarkTheme ? .defaultDark : .defaultLight
        rowCache.removeAll(keepingCapacity: true)
        for highlighter in highlightersByLanguageID.values {
            await highlighter.setTheme(highlightTheme)
        }
    }

    private func highlighter(for language: LanguageConfiguration) async -> TreeSitterHighlighter? {
        if let cached = highlightersByLanguageID[language.identifier] {
            return cached
        }

        let highlighter = TreeSitterHighlighter(theme: highlightTheme)
        do {
            try await highlighter.setLanguage(language)
            highlightersByLanguageID[language.identifier] = highlighter
            return highlighter
        } catch {
            return nil
        }
    }

    private func highlightRow(
        _ row: VVDiffRow,
        with highlighter: TreeSitterHighlighter
    ) async -> [(NSRange, SIMD4<Float>)] {
        do {
            _ = try await highlighter.parse(row.text)
            let highlights = try await highlighter.highlights(in: nil)
            guard !highlights.isEmpty else { return [] }

            return highlights.compactMap { highlight in
                guard highlight.range.length > 0 else { return nil }
                return (
                    highlight.range,
                    SIMD4<Float>(
                        Float(highlight.style.color.redComponent),
                        Float(highlight.style.color.greenComponent),
                        Float(highlight.style.color.blueComponent),
                        Float(highlight.style.color.alphaComponent)
                    )
                )
            }
        } catch {
            return []
        }
    }
}

@MainActor
enum VVDiffViewDebug {
    static func makeMetrics(
        unifiedDiff: String,
        style: VVDiffRenderStyle,
        theme: VVTheme = .defaultDark,
        configuration: VVConfiguration = .default,
        renderOptions: VVDiffRenderOptions = .full,
        language: VVLanguage? = nil,
        syntaxHighlightingEnabled: Bool = true,
        viewportSize: CGSize = CGSize(width: 1100, height: 760),
        scrollOffsetY: CGFloat = 0
    ) -> VVDiffViewDebugMetrics {
        let view = VVDiffMetalView(frame: CGRect(origin: .zero, size: viewportSize))
        let analysis = VVDiffSceneRenderer.analyze(unifiedDiff: unifiedDiff)
        view.update(
            unifiedDiff: unifiedDiff,
            analysis: analysis,
            style: style,
            theme: theme,
            configuration: configuration,
            renderOptions: renderOptions,
            language: language,
            syntaxHighlightingEnabled: syntaxHighlightingEnabled,
            onFileHeaderActivate: nil
        )

        if scrollOffsetY > 0 {
            view.debugScrollTo(y: scrollOffsetY)
        }

        return view.debugMetrics()
    }
}

// MARK: - VVDiffDisplayMetrics

// MARK: - VVDiffMetalView

/// Plain NSView used as the scroll view's documentView purely for content sizing.
private final class DiffDocumentView: NSView {
    override var isFlipped: Bool { true }
}

/// MTKView subclass that forwards mouse events to VVDiffMetalView.
private final class DiffMTKView: MTKView {
    weak var diffView: VVDiffMetalView?

    override func mouseDown(with event: NSEvent) {
        diffView?.mouseDown(with: event)
    }

    override func mouseDragged(with event: NSEvent) {
        diffView?.mouseDragged(with: event)
    }

    override func mouseUp(with event: NSEvent) {
        diffView?.mouseUp(with: event)
    }
}

private final class VVDiffMetalView: NSView {
    override var isFlipped: Bool { true }
    override var acceptsFirstResponder: Bool { true }

    private var scrollView: NSScrollView!
    private var documentView: DiffDocumentView!
    private var metalView: DiffMTKView!
    private var renderer: VVTextMetalRenderer?
    private var diffMetrics: VVDiffDisplayMetrics?
    var metalContext: VVMetalContext?

    private var rows: [VVDiffRow] = []
    private var unifiedDiffSource: String = ""
    private var sections: [VVDiffSection] = []
    private var splitRows: [VVDiffSplitRow] = []
    private var analyzedDocument: VVDiffDocument?
    private var renderStyle: VVDiffRenderStyle = .inline
    private var theme: VVTheme = .defaultDark
    private var configuration: VVConfiguration = .default
    private var renderOptions: VVDiffRenderOptions = .full
    private var language: VVLanguage?
    private var syntaxHighlightingEnabled: Bool = true
    private var onFileHeaderActivate: ((String) -> Void)?

    private var cachedRenderArtifacts: VVDiffRenderArtifacts?
    private var cachedRenderKey: ViewportSceneCacheKey?
    private var sceneBuildGeneration: Int = 0
    private var sceneBuildInFlightKey: ViewportSceneCacheKey?
    private var contentHeight: CGFloat = 0
    private var currentDrawableSize: CGSize = .zero
    private var currentScrollOffset: CGPoint = .zero
    private var displayLink: CVDisplayLink?
    private var activeScrollDeadline: CFTimeInterval = 0
    private var deferredHighlightSceneRefresh = false

    private var highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]] = [:]
    private var staleHighlightedRowIDs: Set<Int> = []
    private var highlightSceneVersion: Int = 0
    private var highlightGeneration: Int = 0
    private var highlightTask: Task<Void, Never>?
    private let viewportHighlighter = DiffViewportHighlighter()
    private var codeRows: [VVDiffRow] = []
    private var rowIndexByID: [Int: Int] = [:]
    private var codeRowIndexByID: [Int: Int] = [:]
    private var pendingHighlightCodeRowRange: Range<Int>?

    private static let minimumVisibleHighlightCodeRows: Int = 96
    private static let initialHighlightCodeRows: Int = 128
    private static let incrementalHighlightCodeRows: Int = 192
    private static let highlightLeadingPrefetchCodeRows: Int = 72
    private static let highlightPrefetchCodeRows: Int = 160
    private static let scrollHighlightPrefetchCodeRows: Int = 48
    private static let retainedHighlightLeadingCodeRows: Int = 192
    private static let retainedHighlightTrailingCodeRows: Int = 320
    private static let highlightViewportMargin: CGFloat = 220
    private static let highlightWarmupContextRows: Int = 32
    private static let renderCullPadding: CGFloat = 256
    private static let sceneCacheViewportPaddingMultiplier: CGFloat = 2.0
    private static let scrollActivityGrace: CFTimeInterval = 0.16
    private static let sceneBuildQueue = DispatchQueue(label: "vvdevkit.diff.scene-build", qos: .userInitiated)

    private var baseFont: NSFont = .monospacedSystemFont(ofSize: 13, weight: .regular)

    // Selection support
    private let selectionController = VVTextSelectionController<DiffTextPosition>()
    private let selectionColor: SIMD4<Float> = .rgba(0.24, 0.40, 0.65, 0.55)
    private var rowGeometries: [RowGeometry] = []
    private var rowGeometryWindowRange: Range<Int> = 0..<0
    private var displayBlocks: [DisplayBlock] = []
    private var layoutPlan: VVDiffLayoutPlan?
    private var filePathByHeaderRowID: [Int: String] = [:]
    private var rowGeometryCacheKey: RowGeometryCacheKey?
    private var rowGeometriesContentHeight: CGFloat = 0
    private var rowsSignature: Int = 0
    private var fastPlainModeEnabled: Bool = false
    private var drawFrameCounter: Int = 0
    private let codeInsetX: CGFloat = 10

    init(frame: CGRect, metalContext: VVMetalContext? = nil) {
        self.metalContext = metalContext ?? VVMetalContext.shared
        super.init(frame: frame)
        setup()
    }

    required init?(coder: NSCoder) {
        self.metalContext = VVMetalContext.shared
        super.init(coder: coder)
        setup()
    }

    deinit {
        highlightTask?.cancel()
        if let displayLink {
            CVDisplayLinkStop(displayLink)
        }
        NotificationCenter.default.removeObserver(
            self,
            name: NSView.boundsDidChangeNotification,
            object: scrollView?.contentView
        )
    }

    private func setup() {
        wantsLayer = true

        // Document view exists only for scroll content sizing (same pattern as MetalTextView)
        documentView = DiffDocumentView(frame: bounds)

        scrollView = NSScrollView(frame: bounds)
        scrollView.autoresizingMask = [.width, .height]
        scrollView.hasVerticalScroller = true
        scrollView.hasHorizontalScroller = true
        scrollView.drawsBackground = false
        scrollView.autohidesScrollers = true
        scrollView.documentView = documentView
        scrollView.contentView.postsBoundsChangedNotifications = true

        let device = metalContext?.device ?? MTLCreateSystemDefaultDevice()
        guard let device else { return }

        // MTKView is a sibling of the document view, always sized to the visible viewport.
        // Scroll offset is passed to beginFrame so the renderer shifts primitives.
        metalView = DiffMTKView(frame: bounds, device: device)
        metalView.diffView = self
        metalView.isPaused = true
        metalView.enableSetNeedsDisplay = true
        metalView.framebufferOnly = true
        metalView.delegate = self
        metalView.layer?.isOpaque = true
        if let metalLayer = metalView.layer as? CAMetalLayer {
            metalLayer.maximumDrawableCount = 3
        }

        addSubview(scrollView)
        scrollView.addSubview(metalView)

        if let ctx = metalContext {
            renderer = VVTextMetalRenderer(context: ctx, baseFont: baseFont, scaleFactor: NSScreen.main?.backingScaleFactor ?? 2.0)
            renderer?.glyphAtlas.preloadASCII(fontSize: baseFont.pointSize, baseFont: baseFont)
        } else {
            renderer = nil
        }

        setupDisplayLink()

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(scrollViewBoundsChanged),
            name: NSView.boundsDidChangeNotification,
            object: scrollView.contentView
        )
    }

    @objc private func scrollViewBoundsChanged(_ notification: Notification) {
        updateMetalViewport()
        noteScrollActivity()
        refreshVisibleRowGeometryWindow()
        // Defer ALL expensive work (highlighting, scene prefetch) until
        // scrolling stops. During active scrolling the cached scene covers
        // visible blocks and the display link drives rendering. Running
        // highlight tasks or async scene builds during scroll causes
        // main-thread contention and PreparedTextRun cache thrashing.
        if displayLink == nil {
            metalView.setNeedsDisplay(metalView.bounds)
        }
    }

    private func setupDisplayLink() {
        var link: CVDisplayLink?
        CVDisplayLinkCreateWithActiveCGDisplays(&link)
        guard let link else { return }

        let callback: CVDisplayLinkOutputCallback = { _, _, _, _, _, userInfo in
            guard let userInfo else { return kCVReturnSuccess }
            let view = Unmanaged<VVDiffMetalView>.fromOpaque(userInfo).takeUnretainedValue()
            DispatchQueue.main.async {
                view.handleDisplayLinkTick()
            }
            return kCVReturnSuccess
        }

        CVDisplayLinkSetOutputCallback(link, callback, Unmanaged.passUnretained(self).toOpaque())
        displayLink = link
    }

    private func startDisplayLink() {
        guard let displayLink, !CVDisplayLinkIsRunning(displayLink) else { return }
        CVDisplayLinkStart(displayLink)
    }

    private func stopDisplayLink() {
        guard let displayLink, CVDisplayLinkIsRunning(displayLink) else { return }
        CVDisplayLinkStop(displayLink)
    }

    private func noteScrollActivity() {
        activeScrollDeadline = CACurrentMediaTime() + Self.scrollActivityGrace
        startDisplayLink()
    }

    private var isActivelyScrolling: Bool {
        CACurrentMediaTime() < activeScrollDeadline
    }

    private func handleDisplayLinkTick() {
        guard window != nil, superview != nil, !isHidden else {
            stopDisplayLink()
            return
        }

        if isActivelyScrolling {
            metalView.setNeedsDisplay(metalView.bounds)
            return
        }

        // Scrolling just stopped — apply deferred highlights, prefetch, resume batching.
        var needsAnotherTick = false
        var shouldRedraw = false

        if deferredHighlightSceneRefresh {
            applyDeferredHighlightSceneRefresh(redraw: false)
            shouldRedraw = true
            needsAnotherTick = true
        }

        prewarmSceneBuildIfNeeded()
        requestViewportHighlightingIfNeeded()

        // Resume highlight batching that was paused during scrolling.
        if highlightTask == nil {
            startNextHighlightBatchIfNeeded()
        }

        if highlightTask != nil {
            needsAnotherTick = true
        }

        if shouldRedraw {
            metalView.setNeedsDisplay(metalView.bounds)
        }

        if !needsAnotherTick {
            stopDisplayLink()
        }
    }

    override func layout() {
        super.layout()
        scrollView.frame = bounds
        updateContentSize()
        requestViewportHighlightingIfNeeded()
        prewarmSceneBuildIfNeeded()
    }

    /// Keep MTKView pinned to the visible viewport (same as VVMetalEditorContainerView).
    private func updateMetalViewport() {
        let viewportSize = scrollView.contentView.bounds.size
        let viewportOrigin = scrollView.contentView.frame.origin
        currentScrollOffset = scrollView.contentView.bounds.origin
        metalView.frame = CGRect(origin: viewportOrigin, size: viewportSize)
    }

    private func invalidateSceneCache(clearScene: Bool) {
        sceneBuildGeneration &+= 1
        sceneBuildInFlightKey = nil
        cachedRenderKey = nil

        if clearScene {
            cachedRenderArtifacts = nil
        }
    }

    private func currentRenderWidth() -> CGFloat {
        if renderStyle == .sideBySide, let layoutPlan {
            return layoutPlan.width
        }
        let viewportWidth = scrollView?.bounds.width ?? bounds.width
        return (wrapsUnified || fastPlainModeEnabled)
            ? viewportWidth
            : max(viewportWidth, documentView.frame.width)
    }

    private func prewarmSceneBuildIfNeeded() {
        guard metalView != nil else { return }
        let renderWidth = currentRenderWidth()
        let sceneKey = makeViewportSceneCacheKey(renderWidth: renderWidth)
        scheduleSceneBuildIfNeeded(renderWidth: renderWidth, sceneKey: sceneKey)
    }

    private var wrapsUnified: Bool {
        configuration.wrapLines && (renderStyle == .sideBySide || !fastPlainModeEnabled)
    }

    private static func computeRowsSignature(_ rows: [VVDiffRow]) -> Int {
        var hasher = Hasher()
        hasher.combine(rows.count)
        for row in rows {
            hasher.combine(row.id)
            hasher.combine(row.kind.rawValue)
            hasher.combine(row.oldLineNumber ?? -1)
            hasher.combine(row.newLineNumber ?? -1)
            hasher.combine(row.text.utf16.count)
        }
        return hasher.finalize()
    }

    private static func fontSignature(_ font: NSFont) -> Int {
        var hasher = Hasher()
        hasher.combine(font.fontName)
        hasher.combine(font.pointSize)
        return hasher.finalize()
    }

    private static func shouldUseFastPlainMode(rows: [VVDiffRow]) -> Bool {
        let maxRows = 3_500
        let maxTotalUTF16 = 200_000
        let maxChangedRows = 1_800

        if rows.count > maxRows {
            return true
        }

        var totalUTF16 = 0
        var changedRows = 0
        for row in rows where row.kind.isCode {
            totalUTF16 += row.text.utf16.count + 1
            if row.kind == .added || row.kind == .deleted {
                changedRows += 1
            }
            if totalUTF16 > maxTotalUTF16 || changedRows > maxChangedRows {
                return true
            }
        }

        return false
    }

    func update(
        unifiedDiff: String,
        analysis: VVDiffDocument,
        style: VVDiffRenderStyle,
        theme: VVTheme,
        configuration: VVConfiguration,
        renderOptions: VVDiffRenderOptions,
        language: VVLanguage?,
        syntaxHighlightingEnabled: Bool,
        onFileHeaderActivate: ((String) -> Void)?
    ) {
        let rows = analysis.rows
        self.unifiedDiffSource = unifiedDiff
        let nextFastPlainMode = Self.shouldUseFastPlainMode(rows: rows)
        let effectiveSyntaxHighlightingEnabled = syntaxHighlightingEnabled
        self.onFileHeaderActivate = onFileHeaderActivate
        let fastPlainModeChanged = fastPlainModeEnabled != nextFastPlainMode
        let rowsChanged = self.rows != rows
        let styleChanged = self.renderStyle != style
        let themeChanged = self.theme != theme
        let fontChanged = self.configuration.font != configuration.font
        let wrapsChanged = self.configuration.wrapLines != configuration.wrapLines
        let renderOptionsChanged = self.renderOptions != renderOptions
        let langChanged = self.language?.identifier != language?.identifier
        let syntaxHighlightingChanged = self.syntaxHighlightingEnabled != effectiveSyntaxHighlightingEnabled
        let effectiveWrapChanged = wrapsChanged || styleChanged || fastPlainModeChanged || renderOptionsChanged

        if !rowsChanged,
           !styleChanged,
           !themeChanged,
           !fontChanged,
           !renderOptionsChanged,
           !langChanged,
           !syntaxHighlightingChanged,
           !effectiveWrapChanged,
           rowGeometryCacheKey != nil {
            return
        }

        fastPlainModeEnabled = nextFastPlainMode
        self.rows = rows
        self.renderStyle = style
        self.theme = theme
        self.configuration = configuration
        self.renderOptions = renderOptions
        self.language = language
        self.syntaxHighlightingEnabled = effectiveSyntaxHighlightingEnabled
        analyzedDocument = analysis
        rowsSignature = rowsChanged ? Self.computeRowsSignature(rows) : rowsSignature
        rowGeometryCacheKey = nil

        if rowsChanged {
            rebuildCodeRowLookup()
        }

        if style == .sideBySide {
            scrollView?.hasHorizontalScroller = !wrapsUnified
        } else {
            scrollView?.hasHorizontalScroller = !wrapsUnified && !fastPlainModeEnabled
        }

        if fontChanged {
            baseFont = configuration.font
            let scale = window?.backingScaleFactor ?? NSScreen.main?.backingScaleFactor ?? 2.0
            if let ctx = metalContext {
                renderer = VVTextMetalRenderer(context: ctx, baseFont: baseFont, scaleFactor: scale)
                renderer?.glyphAtlas.preloadASCII(fontSize: baseFont.pointSize, baseFont: baseFont)
            }
        }

        if rowsChanged || styleChanged {
            let document = analysis
            sections = document.sections
            rebuildFileHeaderPathLookup()
            splitRows = document.splitRows
        }

        if themeChanged || fontChanged {
            diffMetrics = nil
        }

        let shouldResetHighlighting = rowsChanged || langChanged || fontChanged || themeChanged || syntaxHighlightingChanged
        if shouldResetHighlighting {
            resetHighlightingState(scheduleImmediately: false)
        }

        invalidateSceneCache(clearScene: true)
        updateContentSize()
        requestViewportHighlightingIfNeeded()
        metalView?.setNeedsDisplay(metalView.bounds)
    }

    private func ensureDiffMetrics() -> VVDiffDisplayMetrics {
        if let existing = diffMetrics { return existing }
        let metrics = VVDiffDisplayMetrics(font: configuration.font, theme: theme)
        diffMetrics = metrics
        return metrics
    }

    private func updateContentSize() {
        let width = scrollView?.bounds.width ?? bounds.width
        let dr = ensureDiffMetrics()
        let previousContentHeight = contentHeight
        let previousDocumentFrame = documentView.frame
        buildLayoutIfNeeded(width: width)
        refreshVisibleRowGeometryWindow()
        contentHeight = rowGeometriesContentHeight

        let wrapsUnified = self.wrapsUnified

        // Compute max line width for horizontal scrolling
        let maxLineWidth: CGFloat
        if wrapsUnified || fastPlainModeEnabled {
            maxLineWidth = width
        } else {
            var widestLine = width
            for row in rows {
                let rowText = row.kind == .hunkHeader ? VVDiffDisplayText(for: row) : row.text
                let candidate = (layoutPlan?.metrics.codeStartX ?? dr.charWidth) + codeInsetX + CGFloat(rowText.count) * dr.charWidth + 20
                if candidate > widestLine {
                    widestLine = candidate
                }
            }
            maxLineWidth = widestLine
        }

        let minWidth: CGFloat
        if renderStyle == .sideBySide {
            minWidth = 840 // 420 * 2
        } else if wrapsUnified || fastPlainModeEnabled {
            minWidth = width
        } else {
            minWidth = max(width, 520)
        }

        // Size the document view for scroll bars; MTKView stays viewport-sized
        let docWidth: CGFloat
        if renderStyle == .sideBySide {
            docWidth = max(width, layoutPlan?.width ?? width)
        } else {
            docWidth = (wrapsUnified || fastPlainModeEnabled) ? width : max(maxLineWidth, minWidth, width)
        }
        let docHeight = max(contentHeight, scrollView.bounds.height)
        let documentSizeChanged =
            abs(previousDocumentFrame.width - docWidth) > 0.5 ||
            abs(previousDocumentFrame.height - docHeight) > 0.5
        let contentHeightChanged = abs(previousContentHeight - contentHeight) > 0.5
        if documentSizeChanged || contentHeightChanged || cachedRenderArtifacts == nil {
            invalidateSceneCache(clearScene: false)
        }
        documentView.frame = CGRect(x: 0, y: 0, width: docWidth, height: docHeight)
        updateMetalViewport()
        prewarmSceneBuildIfNeeded()
    }

    private func buildLayoutIfNeeded(width: CGFloat) {
        let widthBucket = Int((width * 2).rounded())
        let cacheKey = RowGeometryCacheKey(
            rowsSignature: rowsSignature,
            style: renderStyle,
            widthBucket: widthBucket,
            wrapsUnified: wrapsUnified,
            fontSignature: Self.fontSignature(configuration.font)
        )
        if rowGeometryCacheKey == cacheKey {
            return
        }

        guard let analyzedDocument else {
            layoutPlan = nil
            rowGeometries.removeAll(keepingCapacity: true)
            rowGeometryWindowRange = 0..<0
            displayBlocks.removeAll(keepingCapacity: true)
            rowGeometriesContentHeight = 0
            rowGeometryCacheKey = cacheKey
            return
        }

        let dr = ensureDiffMetrics()
        let layoutWidth = desiredLayoutWidth(viewportWidth: width, renderer: dr)
        let plan = VVDiffLayoutBuilder.makeLayout(
            document: analyzedDocument,
            width: layoutWidth,
            baseFont: configuration.font,
            style: renderStyle == .sideBySide ? .sideBySide : .inline,
            wrapLines: wrapsUnified,
            includesMetadata: false
        )
        layoutPlan = plan
        rowGeometries.removeAll(keepingCapacity: true)
        rowGeometryWindowRange = 0..<0
        displayBlocks = plan.blocks
        rowGeometriesContentHeight = plan.contentHeight
        refreshVisibleRowGeometryWindow(force: true)
        rowGeometryCacheKey = cacheKey
    }

    private func desiredLayoutWidth(viewportWidth: CGFloat, renderer: VVDiffDisplayMetrics) -> CGFloat {
        guard renderStyle == .sideBySide else { return viewportWidth }
        guard !wrapsUnified else { return max(viewportWidth, 840) }

        let maxOld = analyzedDocument?.maxOldLineNumber ?? rows.compactMap(\.oldLineNumber).max() ?? 0
        let maxNew = analyzedDocument?.maxNewLineNumber ?? rows.compactMap(\.newLineNumber).max() ?? 0
        let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
        let gutterColWidth = CGFloat(gutterDigits) * renderer.charWidth + 16
        let markerWidth = renderer.charWidth + 4
        let paneCodeStartX = markerWidth + gutterColWidth

        var paneWidth = max(420, floor(viewportWidth / 2))
        for splitRow in splitRows {
            if let left = splitRow.left {
                let candidate = paneCodeStartX + codeInsetX + CGFloat(left.text.count) * renderer.charWidth + 20
                paneWidth = max(paneWidth, candidate)
            }
            if let right = splitRow.right {
                let candidate = paneCodeStartX + codeInsetX + CGFloat(right.text.count) * renderer.charWidth + 20
                paneWidth = max(paneWidth, candidate)
            }
        }

        return max(viewportWidth, paneWidth * 2)
    }

    private func assertRowGeometriesAreSorted() {
        #if DEBUG
        guard !rowGeometries.isEmpty else { return }
        var previousY = rowGeometries[0].y
        for geometry in rowGeometries.dropFirst() {
            assert(geometry.y >= previousY, "Row geometries must remain sorted by y for viewport lookup")
            previousY = geometry.y
        }
        #endif
    }

    private func refreshVisibleRowGeometryWindow(force: Bool = false) {
        let visibleRect = scrollView.contentView.bounds.insetBy(dx: 0, dy: -Self.renderCullPadding)
        refreshRowGeometryWindow(in: visibleRect, force: force)
    }

    private func refreshRowGeometryWindow(aroundDocumentY y: CGFloat, force: Bool = false) {
        let viewportHeight = max(scrollView.contentView.bounds.height, 1)
        let visibleRect = CGRect(
            x: 0,
            y: max(0, y - viewportHeight * 0.5),
            width: documentView.bounds.width,
            height: viewportHeight
        ).insetBy(dx: 0, dy: -Self.renderCullPadding)
        refreshRowGeometryWindow(in: visibleRect, force: force)
    }

    private func refreshRowGeometryWindow(in visibleRect: CGRect, force: Bool = false) {
        guard let layoutPlan else {
            rowGeometries.removeAll(keepingCapacity: true)
            rowGeometryWindowRange = 0..<0
            return
        }

        let blockRange = rowGeometryBlockRange(in: visibleRect)
        let visualLineRange = visualLineRange(for: blockRange)
        if !force, rowGeometryWindowRange == visualLineRange {
            return
        }

        rowGeometries = VVDiffLayoutBuilder.materializeVisualLines(in: layoutPlan, blockRange: blockRange)
        rowGeometryWindowRange = visualLineRange
        assertRowGeometriesAreSorted()
    }

    private func rowGeometryBlockRange(in visibleRect: CGRect) -> Range<Int> {
        guard !displayBlocks.isEmpty else { return 0..<0 }
        let visibleRange = visibleDisplayBlockRange(in: visibleRect)
        guard visibleRange.lowerBound < visibleRange.upperBound else {
            return 0..<min(displayBlocks.count, 1)
        }

        let visibleCount = max(visibleRange.count, 1)
        let paddingBlocks = max(24, Int((CGFloat(visibleCount) * 0.75).rounded(.up)))
        let startBlockIndex = max(0, visibleRange.lowerBound - paddingBlocks)
        let endBlockIndex = min(displayBlocks.count, visibleRange.upperBound + paddingBlocks)
        return startBlockIndex..<endBlockIndex
    }

    private func visualLineRange(for blockRange: Range<Int>) -> Range<Int> {
        guard blockRange.lowerBound < blockRange.upperBound,
              displayBlocks.indices.contains(blockRange.lowerBound),
              displayBlocks.indices.contains(blockRange.upperBound - 1) else {
            return 0..<0
        }
        let start = displayBlocks[blockRange.lowerBound].visualLineStartIndex
        let endBlock = displayBlocks[blockRange.upperBound - 1]
        let end = endBlock.visualLineStartIndex + endBlock.visualLineCount
        return start..<end
    }

    private func materializedRowGeometries(for visualLineRange: Range<Int>) -> [RowGeometry] {
        guard let layoutPlan, visualLineRange.lowerBound < visualLineRange.upperBound else { return [] }
        if rowGeometryWindowRange.lowerBound <= visualLineRange.lowerBound &&
            rowGeometryWindowRange.upperBound >= visualLineRange.upperBound {
            let startOffset = visualLineRange.lowerBound - rowGeometryWindowRange.lowerBound
            let endOffset = startOffset + visualLineRange.count
            guard startOffset >= 0, endOffset <= rowGeometries.count else { return [] }
            return Array(rowGeometries[startOffset..<endOffset])
        }
        return VVDiffLayoutBuilder.materializeVisualLines(in: layoutPlan, visualLineRange: visualLineRange)
    }

    private func geometry(at rowIndex: Int) -> RowGeometry? {
        guard rowIndex >= 0 else { return nil }
        return materializedRowGeometries(for: rowIndex..<(rowIndex + 1)).first
    }

    private func rebuildFileHeaderPathLookup() {
        filePathByHeaderRowID.removeAll(keepingCapacity: true)
        filePathByHeaderRowID.reserveCapacity(sections.count)
        for section in sections {
            guard let header = section.headerRow else { continue }
            filePathByHeaderRowID[header.id] = section.filePath
        }
    }

    // MARK: - Syntax Highlighting

    private func rebuildCodeRowLookup() {
        rowIndexByID.removeAll(keepingCapacity: true)
        rowIndexByID.reserveCapacity(rows.count)
        codeRows = rows.filter { $0.kind.isCode }
        codeRowIndexByID.removeAll(keepingCapacity: true)
        codeRowIndexByID.reserveCapacity(codeRows.count)
        for (index, row) in rows.enumerated() {
            rowIndexByID[row.id] = index
        }
        for (index, row) in codeRows.enumerated() {
            codeRowIndexByID[row.id] = index
        }
    }

    private func resetHighlightingState(scheduleImmediately: Bool = true) {
        highlightGeneration += 1
        highlightTask?.cancel()
        highlightTask = nil
        highlightedRanges = [:]
        staleHighlightedRowIDs.removeAll(keepingCapacity: true)
        deferredHighlightSceneRefresh = false
        highlightSceneVersion &+= 1
        pendingHighlightCodeRowRange = nil

        guard scheduleImmediately else { return }
        guard syntaxHighlightingEnabled else { return }
        guard !codeRows.isEmpty else { return }
        guard effectiveHighlightLanguageConfiguration() != nil else { return }

        scheduleHighlightingIfNeeded(targetCodeRowRange: desiredHighlightedCodeRowRangeForVisibleViewport())
        startDisplayLink()
    }

    private func requestViewportHighlightingIfNeeded() {
        guard syntaxHighlightingEnabled else { return }
        guard !codeRows.isEmpty else { return }
        guard effectiveHighlightLanguageConfiguration() != nil else { return }
        let targetRange = desiredHighlightedCodeRowRangeForVisibleViewport()
        // Don't trim highlighted ranges — the dictionary cost is trivial and
        // trimming causes "replay" re-highlighting when scrolling back.
        scheduleHighlightingIfNeeded(targetCodeRowRange: targetRange)
    }

    private func desiredHighlightedCodeRowRangeForVisibleViewport() -> Range<Int> {
        let viewportPrefetch = isActivelyScrolling
            ? Self.scrollHighlightPrefetchCodeRows
            : Self.highlightPrefetchCodeRows
        let leadingPrefetch = isActivelyScrolling
            ? max(16, Self.highlightLeadingPrefetchCodeRows / 2)
            : Self.highlightLeadingPrefetchCodeRows
        let minimumTarget = min(codeRows.count, Self.minimumVisibleHighlightCodeRows)
        guard let scrollView else { return 0..<minimumTarget }

        let visibleRect = scrollView.contentView.bounds
        guard let visibleCodeRange = visibleCodeRowIndexRange(in: visibleRect) else {
            return 0..<minimumTarget
        }

        var lowerBound = max(0, visibleCodeRange.lowerBound - leadingPrefetch)
        var upperBound = min(codeRows.count, visibleCodeRange.upperBound + viewportPrefetch)
        if upperBound - lowerBound < minimumTarget {
            let missing = minimumTarget - (upperBound - lowerBound)
            let extendBefore = missing / 2
            let extendAfter = missing - extendBefore
            lowerBound = max(0, lowerBound - extendBefore)
            upperBound = min(codeRows.count, upperBound + extendAfter)
            if upperBound - lowerBound < minimumTarget, upperBound == codeRows.count {
                lowerBound = max(0, upperBound - minimumTarget)
            }
        }

        return lowerBound..<upperBound
    }

    private func firstVisibleGeometryIndex(minY: CGFloat) -> Int {
        var low = 0
        var high = rowGeometries.count

        while low < high {
            let mid = (low + high) / 2
            let geometry = rowGeometries[mid]
            if geometry.y + geometry.height < minY {
                low = mid + 1
            } else {
                high = mid
            }
        }

        return min(low, rowGeometries.count)
    }

    private func visibleCodeRowIndexRange(in visibleRect: CGRect) -> Range<Int>? {
        guard !rowGeometries.isEmpty else { return nil }

        let minY = visibleRect.minY - Self.highlightViewportMargin
        let maxY = visibleRect.maxY + Self.highlightViewportMargin
        let startIndex = firstVisibleGeometryIndex(minY: minY)

        var minCodeIndex: Int?
        var maxCodeIndex: Int?
        var index = startIndex
        while index < rowGeometries.count {
            let geometry = rowGeometries[index]
            if geometry.y > maxY {
                break
            }
            if let codeIndex = codeRowIndexByID[geometry.rowID] {
                if minCodeIndex == nil {
                    minCodeIndex = codeIndex
                }
                if let current = maxCodeIndex {
                    maxCodeIndex = max(current, codeIndex)
                } else {
                    maxCodeIndex = codeIndex
                }
            }
            index += 1
        }

        guard let minCodeIndex, let maxCodeIndex else { return nil }
        return minCodeIndex..<(maxCodeIndex + 1)
    }

    private func scheduleHighlightingIfNeeded(targetCodeRowRange: Range<Int>) {
        let lowerBound = min(max(0, targetCodeRowRange.lowerBound), codeRows.count)
        let upperBound = min(max(lowerBound, targetCodeRowRange.upperBound), codeRows.count)
        guard lowerBound < upperBound else { return }
        pendingHighlightCodeRowRange = lowerBound..<upperBound
        startNextHighlightBatchIfNeeded()
    }

    private func startNextHighlightBatchIfNeeded() {
        guard highlightTask == nil else { return }
        let targetRange = pendingHighlightCodeRowRange ?? desiredHighlightedCodeRowRangeForVisibleViewport()
        guard targetRange.lowerBound < targetRange.upperBound else { return }

        var startIndex: Int?
        for index in targetRange where highlightedRanges[codeRows[index].id] == nil {
            startIndex = index
            break
        }

        guard let startIndex else {
            pendingHighlightCodeRowRange = nil
            return
        }

        let generation = highlightGeneration
        let batchLimit = startIndex == targetRange.lowerBound ? Self.initialHighlightCodeRows : Self.incrementalHighlightCodeRows
        let endIndex = min(targetRange.upperBound, startIndex + batchLimit)

        guard endIndex > startIndex else { return }

        let warmupRows = min(Self.highlightWarmupContextRows, startIndex)
        let parseStart = startIndex - warmupRows
        let batchRows = Array(codeRows[parseStart..<endIndex])
        let targetRowIDs = Set(codeRows[startIndex..<endIndex].map(\.id))
        guard let currentLanguage = effectiveHighlightLanguageConfiguration() else {
            pendingHighlightCodeRowRange = nil
            return
        }
        let currentTheme = theme
        let viewportHighlighter = viewportHighlighter

        highlightTask = Task(priority: .utility) { [weak self] in
            guard !Task.isCancelled else { return }
            let ranges = await viewportHighlighter.highlightRanges(
                rows: batchRows,
                language: currentLanguage,
                theme: currentTheme
            )
            guard !Task.isCancelled else { return }

            await MainActor.run { [weak self] in
                guard let self, self.highlightGeneration == generation, !Task.isCancelled else { return }
                for (rowID, rowRanges) in ranges {
                    guard targetRowIDs.contains(rowID) else { continue }
                    self.highlightedRanges[rowID] = rowRanges
                }
                if !targetRowIDs.isEmpty {
                    self.staleHighlightedRowIDs.formUnion(targetRowIDs)
                }
                // Don't trim highlights — the dictionary cost is trivial and
                // trimming causes re-highlighting when scrolling back.
                self.highlightTask = nil
                if self.shouldRedrawForHighlightedRowIDs(targetRowIDs) {
                    if self.isActivelyScrolling {
                        // During scrolling, just mark deferred. The display link
                        // will apply highlights when scrolling stops.
                        self.deferredHighlightSceneRefresh = true
                        self.startDisplayLink()
                    } else {
                        self.deferredHighlightSceneRefresh = true
                        self.applyDeferredHighlightSceneRefresh(redraw: true)
                    }
                } else if self.isActivelyScrolling, !self.staleHighlightedRowIDs.isEmpty {
                    self.deferredHighlightSceneRefresh = true
                    self.startDisplayLink()
                }
                // Don't chain next batch during active scrolling — it causes
                // continuous MainActor callbacks that contend with scroll handling.
                if !self.isActivelyScrolling {
                    self.startNextHighlightBatchIfNeeded()
                }
            }
        }
    }

    private func highlightRetentionRange(for targetRange: Range<Int>) -> Range<Int> {
        let lowerBound = max(0, targetRange.lowerBound - Self.retainedHighlightLeadingCodeRows)
        let upperBound = min(codeRows.count, targetRange.upperBound + Self.retainedHighlightTrailingCodeRows)
        return lowerBound..<upperBound
    }

    private func hasMissingHighlightRows(in targetRange: Range<Int>) -> Bool {
        guard targetRange.lowerBound < targetRange.upperBound else { return false }
        for index in targetRange where highlightedRanges[codeRows[index].id] == nil {
            return true
        }
        return false
    }

    private func trimHighlightedRanges(keeping keepRange: Range<Int>) {
        guard !highlightedRanges.isEmpty else { return }

        var keepRowIDs: Set<Int> = []
        keepRowIDs.reserveCapacity(keepRange.count)
        for index in keepRange {
            keepRowIDs.insert(codeRows[index].id)
        }

        highlightedRanges = highlightedRanges.filter { keepRowIDs.contains($0.key) }
        staleHighlightedRowIDs = Set(staleHighlightedRowIDs.filter { keepRowIDs.contains($0) })
    }

    private func applyDeferredHighlightSceneRefresh(redraw: Bool) {
        guard deferredHighlightSceneRefresh || !staleHighlightedRowIDs.isEmpty else { return }
        deferredHighlightSceneRefresh = false
        staleHighlightedRowIDs.removeAll(keepingCapacity: true)
        highlightSceneVersion &+= 1
        let renderWidth = currentRenderWidth()
        if let layoutPlan {
            let refreshSceneKey = makeHighlightRefreshSceneCacheKey(renderWidth: renderWidth)
            let refreshBlockRange = refreshSceneKey.startBlockIndex..<refreshSceneKey.endBlockIndex
            if refreshBlockRange.lowerBound < refreshBlockRange.upperBound {
                let artifacts = Self.buildRenderArtifacts(
                    layoutPlan: layoutPlan,
                    blockRange: refreshBlockRange,
                    renderer: renderer,
                    theme: theme,
                    baseFont: configuration.font,
                    options: renderOptions,
                    highlightedRanges: highlightedRanges
                )
                cachedRenderArtifacts = artifacts
                cachedRenderKey = refreshSceneKey
                sceneBuildInFlightKey = nil

                let paddedSceneKey = makeViewportSceneCacheKey(renderWidth: renderWidth)
                if paddedSceneKey != refreshSceneKey {
                    scheduleSceneBuildIfNeeded(renderWidth: renderWidth, sceneKey: paddedSceneKey)
                }
            } else {
                invalidateSceneCache(clearScene: false)
                prewarmSceneBuildIfNeeded()
            }
        } else {
            invalidateSceneCache(clearScene: false)
            prewarmSceneBuildIfNeeded()
        }
        if redraw {
            metalView?.setNeedsDisplay(metalView.bounds)
        }
    }

    private func shouldRedrawForHighlightedRowIDs(_ rowIDs: Set<Int>) -> Bool {
        guard !rowIDs.isEmpty, let scrollView else { return false }

        let visibleRect = scrollView.contentView.bounds.insetBy(dx: -Self.renderCullPadding, dy: -Self.renderCullPadding)
        return geometryRange(visibleGeometryRange(in: visibleRect), intersects: rowIDs)
    }

    private static func buildRenderArtifacts(
        layoutPlan: VVDiffLayoutPlan,
        blockRange: Range<Int>,
        renderer: VVTextMetalRenderer?,
        theme: VVTheme,
        baseFont: NSFont,
        options: VVDiffRenderOptions,
        highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]]
    ) -> VVDiffRenderArtifacts {
        autoreleasepool {
            guard let renderer else {
                return VVDiffRenderArtifacts(quads: [], roundedQuads: [], paths: [], textPasses: [], contentHeight: layoutPlan.contentHeight)
            }
            return VVDiffPaneRenderer.buildArtifacts(
                layout: layoutPlan,
                blockRange: blockRange,
                theme: theme,
                baseFont: baseFont,
                options: options,
                highlightedRanges: highlightedRanges,
                metalRenderer: renderer
            )
        }
    }

    private func scheduleSceneBuildIfNeeded(renderWidth: CGFloat, sceneKey: ViewportSceneCacheKey) {
        guard let layoutPlan else { return }
        let requiredBlockRange = sceneKey.startBlockIndex..<sceneKey.endBlockIndex
        if let cachedRenderKey,
           cachedRenderKey.contains(
            renderWidth: renderWidth,
            highlightVersion: highlightSceneVersion,
            requiredBlockRange: requiredBlockRange
           ) {
            return
        }
        guard sceneBuildInFlightKey != sceneKey else { return }

        let generation = sceneBuildGeneration
        let theme = theme
        let baseFont = configuration.font
        let renderOptions = renderOptions
        let highlightedRanges = highlightedRanges

        sceneBuildInFlightKey = sceneKey
        Self.sceneBuildQueue.async { [weak self] in
            let artifacts = Self.buildRenderArtifacts(
                layoutPlan: layoutPlan,
                blockRange: requiredBlockRange,
                renderer: self?.renderer,
                theme: theme,
                baseFont: baseFont,
                options: renderOptions,
                highlightedRanges: highlightedRanges
            )

            DispatchQueue.main.async { [weak self] in
                guard let self else { return }
                guard self.sceneBuildGeneration == generation else {
                    if self.sceneBuildInFlightKey == sceneKey {
                        self.sceneBuildInFlightKey = nil
                        self.metalView?.setNeedsDisplay(self.metalView.bounds)
                    }
                    return
                }
                guard self.sceneBuildInFlightKey == sceneKey else { return }

                print("[DiffRender] async build complete blocks=\(sceneKey.startBlockIndex)..<\(sceneKey.endBlockIndex) calls=\(artifacts.drawCallCount)")
                self.cachedRenderArtifacts = artifacts
                self.cachedRenderKey = sceneKey
                self.staleHighlightedRowIDs.removeAll(keepingCapacity: true)
                self.sceneBuildInFlightKey = nil
                self.metalView?.setNeedsDisplay(self.metalView.bounds)
            }
        }
    }

    private func geometryRange(_ range: Range<Int>, intersects rowIDs: Set<Int>) -> Bool {
        guard range.lowerBound < range.upperBound else { return false }
        for index in range where rowIDs.contains(rowGeometries[index].rowID) {
            return true
        }
        return false
    }

    private func effectiveHighlightLanguageConfiguration() -> LanguageConfiguration? {
        if let language,
           let configuration = LanguageRegistry.shared.language(for: language.identifier) {
            return configuration
        }

        for section in sections {
            if let configuration = LanguageRegistry.shared.language(forPath: section.filePath) {
                return configuration
            }
        }

        return nil
    }

    private func textForGeometry(_ geometry: RowGeometry) -> String {
        guard geometry.textLength > 0 else { return "" }
        guard let rowIndex = rowIndexByID[geometry.rowID], rows.indices.contains(rowIndex) else { return "" }
        let sourceText = rows[rowIndex].text
        if geometry.textStart == 0 && geometry.textLength >= sourceText.count {
            return sourceText
        }

        let boundedStart = min(max(0, geometry.textStart), sourceText.count)
        let boundedLength = min(max(0, geometry.textLength), sourceText.count - boundedStart)
        let startIndex = sourceText.index(sourceText.startIndex, offsetBy: boundedStart)
        let endIndex = sourceText.index(startIndex, offsetBy: boundedLength)
        return String(sourceText[startIndex..<endIndex])
    }

    override func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        if window == nil {
            stopDisplayLink()
            metalView?.releaseDrawables()
        }
    }

    override func viewDidHide() {
        super.viewDidHide()
        stopDisplayLink()
        metalView?.releaseDrawables()
    }

    override func viewDidUnhide() {
        super.viewDidUnhide()
        if isActivelyScrolling || deferredHighlightSceneRefresh || highlightTask != nil {
            startDisplayLink()
        }
        metalView?.setNeedsDisplay(metalView.bounds)
    }
}

// MARK: - MTKViewDelegate

extension VVDiffMetalView: MTKViewDelegate {
    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {
        currentDrawableSize = size
    }

    func draw(in view: MTKView) {
        let t0 = CACurrentMediaTime()
        guard let renderer,
              let drawable = view.currentDrawable else { return }
        let tDrawable = CACurrentMediaTime()

        let dr = ensureDiffMetrics()
        let bg = dr.backgroundColor

        let commandBuffer = renderer.commandQueue.makeCommandBuffer()
        currentDrawableSize = CGSize(width: drawable.texture.width, height: drawable.texture.height)

        let passDescriptor = MTLRenderPassDescriptor()
        passDescriptor.colorAttachments[0].texture = drawable.texture
        passDescriptor.colorAttachments[0].loadAction = .clear
        passDescriptor.colorAttachments[0].storeAction = .store
        passDescriptor.colorAttachments[0].clearColor = MTLClearColor(
            red: Double(bg.x), green: Double(bg.y), blue: Double(bg.z), alpha: Double(bg.w)
        )

        guard let encoder = commandBuffer?.makeRenderCommandEncoder(descriptor: passDescriptor) else { return }

        // MTKView is viewport-sized. Primitives use absolute document coordinates.
        // Pass scroll offset so the projection shifts them into the visible window
        // (same pattern as MetalTextView.draw).
        let scrollOffset = scrollView.contentView.bounds.origin
        currentScrollOffset = scrollOffset
        renderer.beginFrame(viewportSize: view.bounds.size, scrollOffset: scrollOffset)

        let renderCullPadding = isActivelyScrolling ? max(64, Self.renderCullPadding / 2) : Self.renderCullPadding
        let visibleRect = scrollView.contentView.bounds.insetBy(dx: -renderCullPadding, dy: -renderCullPadding)
        let renderWidth = currentRenderWidth()
        let sceneKey = makeViewportSceneCacheKey(renderWidth: renderWidth)
        let requiredBlockRange = sceneKey.startBlockIndex..<sceneKey.endBlockIndex

        // Tight visible block range (no prefetch padding) — used for partial
        // cache hit test so the cached render packet padding acts as hysteresis.
        let tightVisibleRange = visibleDisplayBlockRange(in: visibleRect)

        var renderArtifacts: VVDiffRenderArtifacts?
        var sceneCachePath = "hit"
        // During active scrolling, accept stale highlights — don't let highlight
        // version changes trigger expensive synchronous packet rebuilds in draw().
        // Highlights will be applied when scrolling stops.
        let effectiveHighlightVersion = isActivelyScrolling
            ? (cachedRenderKey?.highlightVersion ?? highlightSceneVersion)
            : highlightSceneVersion
        if let cached = cachedRenderArtifacts,
           let cachedRenderKey,
           cachedRenderKey.contains(
            renderWidth: renderWidth,
            highlightVersion: effectiveHighlightVersion,
            requiredBlockRange: tightVisibleRange
           ) {
            renderArtifacts = cached
        } else if let layoutPlan {
            if isActivelyScrolling, let staleArtifacts = cachedRenderArtifacts {
                sceneCachePath = "stale[\(requiredBlockRange.count)blk]"
                scheduleSceneBuildIfNeeded(renderWidth: renderWidth, sceneKey: sceneKey)
                renderArtifacts = staleArtifacts
            } else {
                // Cache doesn't cover visible blocks — must build synchronously.
                sceneCachePath = "REBUILD[\(requiredBlockRange.count)blk]"
                let artifacts = Self.buildRenderArtifacts(
                    layoutPlan: layoutPlan,
                    blockRange: requiredBlockRange,
                    renderer: renderer,
                    theme: theme,
                    baseFont: configuration.font,
                    options: renderOptions,
                    highlightedRanges: highlightedRanges
                )
                renderArtifacts = artifacts
                cachedRenderArtifacts = artifacts
                cachedRenderKey = sceneKey
                staleHighlightedRowIDs.removeAll(keepingCapacity: true)
                sceneBuildInFlightKey = nil
            }
        } else {
            renderArtifacts = cachedRenderArtifacts
        }

        let tScene = CACurrentMediaTime()

        if let renderArtifacts {
            VVDiffPaneRenderer.render(
                renderArtifacts,
                encoder: encoder,
                renderer: renderer,
                scissorRectForClip: { [weak self] in
                    self?.scissorRect(for: $0) ?? MTLScissorRect(x: 0, y: 0, width: 0, height: 0)
                },
                fullScissorRect: { [weak self] in
                    self?.fullScissorRect() ?? MTLScissorRect(x: 0, y: 0, width: 0, height: 0)
                }
            )
        }

        // Render selection quads on top of scene (so they're visible over opaque row backgrounds)
        if let selection = selectionController.selection {
            let quads = selectionQuads(
                from: selection.ordered.start,
                to: selection.ordered.end,
                color: selectionColor
            )
            for quad in quads {
                let instance = QuadInstance(
                    position: SIMD2<Float>(Float(quad.frame.origin.x), Float(quad.frame.origin.y)),
                    size: SIMD2<Float>(Float(quad.frame.width), Float(quad.frame.height)),
                    color: quad.color,
                    cornerRadius: Float(quad.cornerRadius)
                )
                if let buffer = renderer.makeBuffer(for: [instance]) {
                    renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: quad.cornerRadius > 0)
                }
            }
        }

        let tRender = CACurrentMediaTime()

        encoder.endEncoding()
        renderer.recycleTransientBuffers(after: commandBuffer)
        commandBuffer?.present(drawable)
        commandBuffer?.commit()

        let tEnd = CACurrentMediaTime()
        let totalMs = (tEnd - t0) * 1000
        if totalMs > 8 || drawFrameCounter % 300 == 0 {
            let drawableMs = (tDrawable - t0) * 1000
            let sceneMs = (tScene - tDrawable) * 1000
            let renderMs = (tRender - tScene) * 1000
            let commitMs = (tEnd - tRender) * 1000
            let drawCalls = renderArtifacts?.drawCallCount ?? 0
            let viewSize = view.bounds.size
            print("[DiffDraw] total=\(String(format: "%.1f", totalMs))ms drw=\(String(format: "%.1f", drawableMs))ms prep=\(String(format: "%.1f", sceneMs))ms rnd=\(String(format: "%.1f", renderMs))ms cmt=\(String(format: "%.1f", commitMs))ms calls=\(drawCalls) \(sceneCachePath) \(Int(viewSize.width))x\(Int(viewSize.height))")
        }
        drawFrameCounter += 1
    }

    private func visibleGeometryRange(in visibleRect: CGRect) -> Range<Int> {
        guard !rowGeometries.isEmpty else { return 0..<0 }

        let startIndex = firstVisibleGeometryIndex(minY: visibleRect.minY)
        var endIndex = startIndex
        while endIndex < rowGeometries.count {
            let geometry = rowGeometries[endIndex]
            if geometry.y > visibleRect.maxY {
                break
            }
            endIndex += 1
        }
        return startIndex..<endIndex
    }

    private func visibleDisplayBlockRange(in visibleRect: CGRect) -> Range<Int> {
        guard !displayBlocks.isEmpty, !visibleRect.isNull, !visibleRect.isEmpty else { return 0..<0 }

        let startBlock = firstVisibleDisplayBlockIndex(minY: visibleRect.minY)
        var endBlock = startBlock
        while endBlock < displayBlocks.count {
            let block = displayBlocks[endBlock]
            if block.y > visibleRect.maxY {
                break
            }
            endBlock += 1
        }
        return startBlock..<endBlock
    }

    private func firstVisibleDisplayBlockIndex(minY: CGFloat) -> Int {
        var low = 0
        var high = displayBlocks.count

        while low < high {
            let mid = (low + high) / 2
            let block = displayBlocks[mid]
            if block.y + block.height < minY {
                low = mid + 1
            } else {
                high = mid
            }
        }

        return min(low, displayBlocks.count)
    }

    private func makeViewportSceneCacheKey(renderWidth: CGFloat) -> ViewportSceneCacheKey {
        let renderWidthBucket = Int((renderWidth * 2).rounded())
        guard let scrollView, !displayBlocks.isEmpty else {
            return ViewportSceneCacheKey(
                startBlockIndex: 0,
                endBlockIndex: 0,
                renderWidthBucket: renderWidthBucket,
                highlightVersion: highlightSceneVersion
            )
        }

        let visibleRange = visibleDisplayBlockRange(
            in: scrollView.contentView.bounds.insetBy(dx: 0, dy: -Self.renderCullPadding)
        )
        guard visibleRange.lowerBound < visibleRange.upperBound else {
            return ViewportSceneCacheKey(
                startBlockIndex: 0,
                endBlockIndex: min(displayBlocks.count, 1),
                renderWidthBucket: renderWidthBucket,
                highlightVersion: highlightSceneVersion
            )
        }

        let visibleCount = max(visibleRange.count, 1)
        let paddingBlocks = max(48, Int((CGFloat(visibleCount) * Self.sceneCacheViewportPaddingMultiplier).rounded(.up)))
        let startBlockIndex = max(0, visibleRange.lowerBound - paddingBlocks)
        let endBlockIndex = min(displayBlocks.count, visibleRange.upperBound + paddingBlocks)
        return ViewportSceneCacheKey(
            startBlockIndex: startBlockIndex,
            endBlockIndex: endBlockIndex,
            renderWidthBucket: renderWidthBucket,
            highlightVersion: highlightSceneVersion
        )
    }

    private func makeHighlightRefreshSceneCacheKey(renderWidth: CGFloat) -> ViewportSceneCacheKey {
        let renderWidthBucket = Int((renderWidth * 2).rounded())
        guard let scrollView, !displayBlocks.isEmpty else {
            return ViewportSceneCacheKey(
                startBlockIndex: 0,
                endBlockIndex: 0,
                renderWidthBucket: renderWidthBucket,
                highlightVersion: highlightSceneVersion
            )
        }

        let visibleRange = visibleDisplayBlockRange(in: scrollView.contentView.bounds.insetBy(dx: 0, dy: -Self.renderCullPadding * 0.5))
        guard visibleRange.lowerBound < visibleRange.upperBound else {
            return ViewportSceneCacheKey(
                startBlockIndex: 0,
                endBlockIndex: min(displayBlocks.count, 1),
                renderWidthBucket: renderWidthBucket,
                highlightVersion: highlightSceneVersion
            )
        }

        let paddingBlocks = min(12, max(4, visibleRange.count / 4))
        let startBlockIndex = max(0, visibleRange.lowerBound - paddingBlocks)
        let endBlockIndex = min(displayBlocks.count, visibleRange.upperBound + paddingBlocks)
        return ViewportSceneCacheKey(
            startBlockIndex: startBlockIndex,
            endBlockIndex: endBlockIndex,
            renderWidthBucket: renderWidthBucket,
            highlightVersion: highlightSceneVersion
        )
    }

    fileprivate func debugMetrics() -> VVDiffViewDebugMetrics {
        debugBuildCurrentRenderArtifactsIfNeeded()
        let visibleBlockRange = visibleDisplayBlockRange(in: scrollView.contentView.bounds)
        let cachedRenderBlockRange = if let cachedRenderKey {
            cachedRenderKey.startBlockIndex..<cachedRenderKey.endBlockIndex
        } else {
            0..<0
        }
        return VVDiffViewDebugMetrics(
            rowGeometryCount: rowGeometries.count,
            totalVisualLineCount: layoutPlan?.totalVisualLineCount ?? rowGeometries.count,
            storedTextGeometryCount: 0,
            storedTextCharacterCount: 0,
            desiredHighlightRange: desiredHighlightedCodeRowRangeForVisibleViewport(),
            codeRowCount: codeRows.count,
            contentHeight: contentHeight,
            totalDisplayBlockCount: displayBlocks.count,
            visibleDisplayBlockRange: visibleBlockRange,
            cachedRenderBlockRange: cachedRenderBlockRange,
            cachedRenderDrawCallCount: cachedRenderArtifacts?.drawCallCount ?? 0
        )
    }

    private func debugBuildCurrentRenderArtifactsIfNeeded() {
        let renderWidth = currentRenderWidth()
        let sceneKey = makeViewportSceneCacheKey(renderWidth: renderWidth)
        let requiredBlockRange = sceneKey.startBlockIndex..<sceneKey.endBlockIndex
        guard let layoutPlan else { return }
        guard cachedRenderArtifacts == nil || !(cachedRenderKey?.contains(
            renderWidth: renderWidth,
            highlightVersion: highlightSceneVersion,
            requiredBlockRange: requiredBlockRange
        ) ?? false) else {
            return
        }
        let artifacts = Self.buildRenderArtifacts(
            layoutPlan: layoutPlan,
            blockRange: requiredBlockRange,
            renderer: renderer,
            theme: theme,
            baseFont: configuration.font,
            options: renderOptions,
            highlightedRanges: highlightedRanges
        )
        cachedRenderArtifacts = artifacts
        cachedRenderKey = sceneKey
    }

    fileprivate func debugScrollTo(y: CGFloat) {
        let maxOffsetY = max(0, documentView.frame.height - bounds.height)
        let clampedOffsetY = min(max(0, y), maxOffsetY)
        let clipView = scrollView.contentView
        clipView.scroll(to: CGPoint(x: 0, y: clampedOffsetY))
        scrollView.reflectScrolledClipView(clipView)
        scrollViewBoundsChanged(
            Notification(name: NSView.boundsDidChangeNotification, object: clipView)
        )
    }

    private func fullScissorRect() -> MTLScissorRect {
        let width = max(1, Int(currentDrawableSize.width))
        let height = max(1, Int(currentDrawableSize.height))
        return MTLScissorRect(x: 0, y: 0, width: width, height: height)
    }

    private func scissorRect(for frame: CGRect) -> MTLScissorRect {
        let visibleFrame = frame.offsetBy(dx: -currentScrollOffset.x, dy: -currentScrollOffset.y)
        let viewBounds = CGRect(origin: .zero, size: metalView.bounds.size)
        let clipped = visibleFrame.intersection(viewBounds)
        if clipped.isNull || clipped.width <= 0 || clipped.height <= 0 {
            return fullScissorRect()
        }

        let scaleX = currentDrawableSize.width / max(1, metalView.bounds.width)
        let scaleY = currentDrawableSize.height / max(1, metalView.bounds.height)
        let x = max(0, Int(floor(clipped.minX * scaleX)))
        let y = max(0, Int(floor(clipped.minY * scaleY)))
        let maxWidth = max(1, Int(currentDrawableSize.width) - x)
        let maxHeight = max(1, Int(currentDrawableSize.height) - y)
        let width = min(maxWidth, Int(ceil(clipped.width * scaleX)))
        let height = min(maxHeight, Int(ceil(clipped.height * scaleY)))
        return MTLScissorRect(x: x, y: y, width: max(1, width), height: max(1, height))
    }

    // MARK: - Selection Support

    private func viewPointToDocumentPoint(_ point: CGPoint) -> CGPoint {
        let scrollOffset = scrollView.contentView.bounds.origin
        return CGPoint(x: point.x + scrollOffset.x, y: point.y + scrollOffset.y)
    }

    private func findRow(at y: CGFloat, x: CGFloat? = nil) -> RowGeometry? {
        if rowGeometries.isEmpty {
            refreshVisibleRowGeometryWindow(force: true)
        } else if let first = rowGeometries.first,
                  let last = rowGeometries.last,
                  (y < first.y || y >= last.y + last.height) {
            refreshRowGeometryWindow(aroundDocumentY: y, force: true)
        }
        guard !rowGeometries.isEmpty else { return nil }

        // Clamp to first/last row when outside bounds
        if y < rowGeometries.first!.y {
            return rowGeometries.first
        }
        let last = rowGeometries.last!
        if y >= last.y + last.height {
            return last
        }

        // Binary search by Y coordinate
        var low = 0
        var high = rowGeometries.count - 1

        while low <= high {
            let mid = (low + high) / 2
            let geo = rowGeometries[mid]

            if y < geo.y {
                high = mid - 1
            } else if y >= geo.y + geo.height {
                low = mid + 1
            } else {
                // Found a row at this Y. If X filtering is requested (split mode),
                // pick the row whose pane contains the X coordinate.
                if let x = x {
                    // Look for all rows at this same Y position
                    var candidates: [RowGeometry] = [geo]
                    // Check neighbors (split rows share the same Y)
                    for offset in [mid - 1, mid + 1] {
                        if offset >= 0 && offset < rowGeometries.count {
                            let neighbor = rowGeometries[offset]
                            if neighbor.y == geo.y {
                                candidates.append(neighbor)
                            }
                        }
                    }
                    // Return the row whose pane contains the X click
                    return candidates.first(where: { x >= $0.paneX && x < $0.paneX + $0.paneWidth })
                }
                return geo
            }
        }

        return rowGeometries[low < rowGeometries.count ? low : rowGeometries.count - 1]
    }

    private func invalidateAndRedraw() {
        metalView.setNeedsDisplay(metalView.bounds)
    }

    private func inputModifiers(from flags: NSEvent.ModifierFlags) -> VVInputModifiers {
        var modifiers: VVInputModifiers = []
        if flags.contains(.shift) { modifiers.insert(.shift) }
        if flags.contains(.control) { modifiers.insert(.control) }
        if flags.contains(.option) { modifiers.insert(.option) }
        if flags.contains(.command) { modifiers.insert(.command) }
        return modifiers
    }

    // MARK: - Mouse Events

    override func mouseDown(with event: NSEvent) {
        window?.makeFirstResponder(self)
        let point = convert(event.locationInWindow, from: nil)

        if event.clickCount == 1,
           let filePath = fileHeaderPath(at: point) {
            onFileHeaderActivate?(filePath)
            return
        }

        selectionController.handleMouseDown(
            at: point,
            clickCount: event.clickCount,
            modifiers: inputModifiers(from: event.modifierFlags),
            hitTester: self
        )
        invalidateAndRedraw()
    }

    override func mouseDragged(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        selectionController.handleMouseDragged(to: point, hitTester: self)
        _ = autoscroll(with: event)
        invalidateAndRedraw()
    }

    override func mouseUp(with event: NSEvent) {
        selectionController.handleMouseUp()
    }

    private func fileHeaderPath(at point: CGPoint) -> String? {
        let docPoint = viewPointToDocumentPoint(point)
        let row: RowGeometry?
        if renderStyle == .sideBySide {
            row = findRow(at: docPoint.y, x: docPoint.x)
        } else {
            row = findRow(at: docPoint.y)
        }
        guard let row else { return nil }
        return filePathByHeaderRowID[row.rowID]
    }

    // MARK: - Keyboard Events

    override func performKeyEquivalent(with event: NSEvent) -> Bool {
        if event.modifierFlags.contains(.command),
           let chars = event.charactersIgnoringModifiers?.lowercased() {
            switch chars {
            case "c":
                copySelection()
                return true
            case "a":
                selectAll(nil)
                return true
            default:
                break
            }
        }
        return super.performKeyEquivalent(with: event)
    }

    @IBAction func copy(_ sender: Any?) {
        copySelection()
    }

    private func copySelection() {
        guard let selection = selectionController.selection else { return }
        let text = extractText(from: selection.ordered.start, to: selection.ordered.end)
        guard !text.isEmpty else { return }
        NSPasteboard.general.clearContents()
        NSPasteboard.general.setString(text, forType: .string)
    }

    @IBAction override func selectAll(_ sender: Any?) {
        guard let layoutPlan, layoutPlan.totalVisualLineCount > 0 else { return }
        let first = DiffTextPosition(rowIndex: 0, charOffset: 0)
        guard let lastGeometry = geometry(at: layoutPlan.totalVisualLineCount - 1) else { return }
        let last = DiffTextPosition(rowIndex: lastGeometry.rowIndex, charOffset: lastGeometry.textLength, paneX: lastGeometry.paneX)
        selectionController.selectAll(from: first, to: last)
        invalidateAndRedraw()
    }
}

// MARK: - VVTextHitTestable

extension VVDiffMetalView: VVTextHitTestable {
    func hitTest(at point: CGPoint) -> DiffTextPosition? {
        let docPoint = viewPointToDocumentPoint(point)

        // In split mode, find the row matching both Y and the correct pane (by X)
        let geo: RowGeometry?
        if renderStyle == .sideBySide {
            geo = findRow(at: docPoint.y, x: docPoint.x)
        } else {
            geo = findRow(at: docPoint.y)
        }
        guard let geo else { return nil }

        // For non-code rows, return position at start of row
        guard geo.isCodeRow else {
            return DiffTextPosition(rowIndex: geo.rowIndex, charOffset: 0, paneX: geo.paneX)
        }

        let dr = ensureDiffMetrics()

        // Convert X to character offset (monospace: relativeX / charWidth)
        let relativeX = docPoint.x - geo.paneX - geo.codeStartX - codeInsetX
        let charOffset = max(0, min(Int(relativeX / dr.charWidth), geo.textLength))

        return DiffTextPosition(rowIndex: geo.rowIndex, charOffset: charOffset, paneX: geo.paneX)
    }
}

// MARK: - VVTextSelectionRenderer

extension VVDiffMetalView: VVTextSelectionRenderer {
    func selectionQuads(from start: DiffTextPosition, to end: DiffTextPosition, color: SIMD4<Float>) -> [VVQuadPrimitive] {
        var quads: [VVQuadPrimitive] = []
        let dr = ensureDiffMetrics()
        let selectionPane = start.paneX
        let geometries = materializedRowGeometries(for: start.rowIndex..<(end.rowIndex + 1))

        for geo in geometries {
            guard geo.rowIndex >= start.rowIndex && geo.rowIndex <= end.rowIndex else { continue }

            // In split mode, only select rows within the same pane
            if renderStyle == .sideBySide && geo.paneX != selectionPane { continue }

            // For non-code rows (hunk headers, file headers), draw full-width highlight
            guard geo.isCodeRow else {
                // Only fill non-code rows that are fully interior to the selection
                if geo.rowIndex > start.rowIndex && geo.rowIndex < end.rowIndex {
                    let quadPaneX = renderStyle == .sideBySide ? selectionPane : geo.paneX
                    let quadPaneW = renderStyle == .sideBySide ? geo.paneWidth / 2 : geo.paneWidth
                    quads.append(VVQuadPrimitive(
                        frame: CGRect(x: quadPaneX, y: geo.y, width: quadPaneW, height: geo.height),
                        color: color,
                        cornerRadius: 0
                    ))
                }
                continue
            }

            let startChar: Int
            let endChar: Int
            let extendToEnd: Bool  // extend selection to pane edge

            if geo.rowIndex == start.rowIndex && geo.rowIndex == end.rowIndex {
                startChar = start.charOffset
                endChar = end.charOffset
                extendToEnd = false
            } else if geo.rowIndex == start.rowIndex {
                startChar = start.charOffset
                endChar = geo.textLength
                extendToEnd = true
            } else if geo.rowIndex == end.rowIndex {
                startChar = 0
                endChar = end.charOffset
                extendToEnd = false
            } else {
                startChar = 0
                endChar = geo.textLength
                extendToEnd = true
            }

            guard extendToEnd || startChar < endChar else { continue }

            let startX = geo.paneX + geo.codeStartX + codeInsetX + CGFloat(startChar) * dr.charWidth
            let endX: CGFloat
            if extendToEnd {
                endX = geo.paneX + geo.paneWidth
            } else {
                endX = geo.paneX + geo.codeStartX + codeInsetX + CGFloat(endChar) * dr.charWidth
            }

            guard endX > startX else { continue }

            quads.append(VVQuadPrimitive(
                frame: CGRect(x: startX, y: geo.y, width: endX - startX, height: geo.height),
                color: color
            ))
        }

        return quads
    }
}

// MARK: - VVTextExtractor

extension VVDiffMetalView: VVTextExtractor {
    func extractText(from start: DiffTextPosition, to end: DiffTextPosition) -> String {
        var lines: [String] = []
        let selectionPane = start.paneX
        let geometries = materializedRowGeometries(for: start.rowIndex..<(end.rowIndex + 1))

        for geo in geometries {
            guard geo.rowIndex >= start.rowIndex && geo.rowIndex <= end.rowIndex else { continue }
            // In split mode, only extract text from the same pane
            if renderStyle == .sideBySide && geo.paneX != selectionPane { continue }
            guard geo.isCodeRow else { continue }

            let text = textForGeometry(geo)
            if geo.rowIndex == start.rowIndex && geo.rowIndex == end.rowIndex {
                let startIdx = text.index(text.startIndex, offsetBy: min(start.charOffset, text.count))
                let endIdx = text.index(text.startIndex, offsetBy: min(end.charOffset, text.count))
                lines.append(String(text[startIdx..<endIdx]))
            } else if geo.rowIndex == start.rowIndex {
                let startIdx = text.index(text.startIndex, offsetBy: min(start.charOffset, text.count))
                lines.append(String(text[startIdx...]))
            } else if geo.rowIndex == end.rowIndex {
                let endIdx = text.index(text.startIndex, offsetBy: min(end.charOffset, text.count))
                lines.append(String(text[..<endIdx]))
            } else {
                lines.append(text)
            }
        }

        return lines.joined(separator: "\n")
    }
}

// MARK: - VVDiffViewRepresentable

private struct VVDiffViewRepresentable: NSViewRepresentable {
    let unifiedDiff: String
    let language: VVLanguage?
    let theme: VVTheme
    let configuration: VVConfiguration
    let renderOptions: VVDiffRenderOptions
    let renderStyle: VVDiffRenderStyle
    let syntaxHighlightingEnabled: Bool
    let onFileHeaderActivate: ((String) -> Void)?

    func makeCoordinator() -> Coordinator {
        Coordinator()
    }

    @MainActor
    final class Coordinator {
        private var lastUnifiedDiff: String?
        private var cachedAnalysis: VVDiffDocument?
        private var analysisRequestID: Int = 0
        private var analysisTask: Task<Void, Never>?

        func cachedAnalysis(for unifiedDiff: String) -> VVDiffDocument? {
            if let lastUnifiedDiff, lastUnifiedDiff == unifiedDiff, let cachedAnalysis {
                return cachedAnalysis
            }
            return nil
        }

        func requestAnalysis(
            for unifiedDiff: String,
            apply: @escaping @MainActor (VVDiffDocument) -> Void
        ) {
            if let cached = cachedAnalysis(for: unifiedDiff) {
                apply(cached)
                return
            }

            analysisRequestID &+= 1
            let requestID = analysisRequestID
            analysisTask?.cancel()
            analysisTask = Task.detached(priority: .userInitiated) {
                let analysis = VVDiffSceneRenderer.analyze(unifiedDiff: unifiedDiff)
                await MainActor.run {
                    guard requestID == self.analysisRequestID else { return }
                    self.lastUnifiedDiff = unifiedDiff
                    self.cachedAnalysis = analysis
                    apply(analysis)
                }
            }
        }

        deinit {
            analysisTask?.cancel()
        }
    }

    func makeNSView(context: Context) -> VVDiffMetalView {
        let view = VVDiffMetalView(frame: .zero)
        view.update(
            unifiedDiff: unifiedDiff,
            analysis: context.coordinator.cachedAnalysis(for: unifiedDiff) ?? VVDiffDocument(rows: [], sections: [], splitRows: []),
            style: renderStyle,
            theme: theme,
            configuration: configuration,
            renderOptions: renderOptions,
            language: language,
            syntaxHighlightingEnabled: syntaxHighlightingEnabled,
            onFileHeaderActivate: onFileHeaderActivate
        )
        context.coordinator.requestAnalysis(for: unifiedDiff) { [weak view] analysis in
            guard let view else { return }
            view.update(
                unifiedDiff: unifiedDiff,
                analysis: analysis,
                style: renderStyle,
                theme: theme,
                configuration: configuration,
                renderOptions: renderOptions,
                language: language,
                syntaxHighlightingEnabled: syntaxHighlightingEnabled,
                onFileHeaderActivate: onFileHeaderActivate
            )
        }
        return view
    }

    func updateNSView(_ nsView: VVDiffMetalView, context: Context) {
        if let analysis = context.coordinator.cachedAnalysis(for: unifiedDiff) {
            nsView.update(
                unifiedDiff: unifiedDiff,
                analysis: analysis,
                style: renderStyle,
                theme: theme,
                configuration: configuration,
                renderOptions: renderOptions,
                language: language,
                syntaxHighlightingEnabled: syntaxHighlightingEnabled,
                onFileHeaderActivate: onFileHeaderActivate
            )
        } else {
            nsView.update(
                unifiedDiff: unifiedDiff,
                analysis: VVDiffDocument(rows: [], sections: [], splitRows: []),
                style: renderStyle,
                theme: theme,
                configuration: configuration,
                renderOptions: renderOptions,
                language: language,
                syntaxHighlightingEnabled: syntaxHighlightingEnabled,
                onFileHeaderActivate: onFileHeaderActivate
            )
            context.coordinator.requestAnalysis(for: unifiedDiff) { [weak nsView] analysis in
                guard let nsView else { return }
                nsView.update(
                    unifiedDiff: unifiedDiff,
                    analysis: analysis,
                    style: renderStyle,
                    theme: theme,
                    configuration: configuration,
                    renderOptions: renderOptions,
                    language: language,
                    syntaxHighlightingEnabled: syntaxHighlightingEnabled,
                    onFileHeaderActivate: onFileHeaderActivate
                )
            }
        }
    }
}

// MARK: - Public API

/// High-level diff component. Parses unified diff text and renders it through Metal.
public struct VVDiffView: View {
    private let unifiedDiff: String
    private var language: VVLanguage?
    private var theme: VVTheme
    private var configuration: VVConfiguration
    private var renderOptions: VVDiffRenderOptions
    private var renderStyle: VVDiffRenderStyle
    private var syntaxHighlightingEnabled: Bool
    private var onFileHeaderActivate: ((String) -> Void)?

    public init(unifiedDiff: String) {
        self.unifiedDiff = unifiedDiff
        self.language = nil
        self.theme = .defaultDark
        self.configuration = .default
        self.renderOptions = .full
        self.renderStyle = .inline
        self.syntaxHighlightingEnabled = true
        self.onFileHeaderActivate = nil
    }

    public var body: some View {
        VVDiffViewRepresentable(
            unifiedDiff: unifiedDiff,
            language: language,
            theme: theme,
            configuration: configuration,
            renderOptions: renderOptions,
            renderStyle: renderStyle,
            syntaxHighlightingEnabled: syntaxHighlightingEnabled,
            onFileHeaderActivate: onFileHeaderActivate
        )
    }
}

extension VVDiffView {
    /// Override the syntax-highlighting language for code lines inside the diff.
    public func language(_ language: VVLanguage?) -> VVDiffView {
        var view = self
        view.language = language
        return view
    }

    /// Set visual theme for the diff view.
    public func theme(_ theme: VVTheme) -> VVDiffView {
        var view = self
        view.theme = theme
        return view
    }

    /// Set rendering configuration (font and sizing behavior).
    public func configuration(_ configuration: VVConfiguration) -> VVDiffView {
        var view = self
        view.configuration = configuration
        return view
    }

    /// Set rendering options for diff-specific chrome and highlighting.
    public func renderOptions(_ renderOptions: VVDiffRenderOptions) -> VVDiffView {
        var view = self
        view.renderOptions = renderOptions
        return view
    }

    /// Select inline or side-by-side rendering.
    public func renderStyle(_ style: VVDiffRenderStyle) -> VVDiffView {
        var view = self
        view.renderStyle = style
        return view
    }

    /// Show or hide diff line numbers without changing the surrounding layout.
    public func showsLineNumbers(_ showsLineNumbers: Bool) -> VVDiffView {
        var view = self
        view.renderOptions.showsLineNumbers = showsLineNumbers
        return view
    }

    /// Show or hide added/deleted row background fills.
    public func showsBackgrounds(_ showsBackgrounds: Bool) -> VVDiffView {
        var view = self
        view.renderOptions.showsBackgrounds = showsBackgrounds
        return view
    }

    /// Choose how diff markers are drawn for changed rows.
    public func changeIndicatorStyle(_ style: VVDiffChangeIndicatorStyle) -> VVDiffView {
        var view = self
        view.renderOptions.changeIndicatorStyle = style
        return view
    }

    /// Control whether inline word-level highlights are shown inside paired changes.
    public func inlineHighlightStyle(_ style: VVDiffInlineHighlightStyle) -> VVDiffView {
        var view = self
        view.renderOptions.inlineHighlightStyle = style
        return view
    }

    /// Toggle diff line wrapping.
    public func wrapLines(_ wrapLines: Bool) -> VVDiffView {
        var view = self
        view.configuration = view.configuration.with(wrapLines: wrapLines)
        return view
    }

    /// Enable or disable syntax highlighting for diff code rows.
    public func syntaxHighlighting(_ enabled: Bool) -> VVDiffView {
        var view = self
        view.syntaxHighlightingEnabled = enabled
        return view
    }

    /// Set monospaced font for diff text.
    public func font(_ font: NSFont) -> VVDiffView {
        var view = self
        view.configuration = view.configuration.with(font: font)
        return view
    }

    /// Called when a file header row is activated.
    public func onFileHeaderActivate(_ handler: ((String) -> Void)?) -> VVDiffView {
        var view = self
        view.onFileHeaderActivate = handler
        return view
    }
}

public struct VVDiffControlsState: Equatable {
    public var renderStyle: VVDiffRenderStyle
    public var wrapLines: Bool
    public var showsLineNumbers: Bool
    public var showsBackgrounds: Bool
    public var changeIndicatorStyle: VVDiffChangeIndicatorStyle
    public var inlineHighlightStyle: VVDiffInlineHighlightStyle

    public init(
        renderStyle: VVDiffRenderStyle = .sideBySide,
        wrapLines: Bool = true,
        showsLineNumbers: Bool = true,
        showsBackgrounds: Bool = true,
        changeIndicatorStyle: VVDiffChangeIndicatorStyle = .bars,
        inlineHighlightStyle: VVDiffInlineHighlightStyle = .word
    ) {
        self.renderStyle = renderStyle
        self.wrapLines = wrapLines
        self.showsLineNumbers = showsLineNumbers
        self.showsBackgrounds = showsBackgrounds
        self.changeIndicatorStyle = changeIndicatorStyle
        self.inlineHighlightStyle = inlineHighlightStyle
    }
}

public enum VVDiffControlsStyle: Sendable {
    case toolbar
    case sidebar
}

extension VVDiffView {
    public func controlsState(_ state: VVDiffControlsState) -> VVDiffView {
        renderStyle(state.renderStyle)
            .wrapLines(state.wrapLines)
            .showsLineNumbers(state.showsLineNumbers)
            .showsBackgrounds(state.showsBackgrounds)
            .changeIndicatorStyle(state.changeIndicatorStyle)
            .inlineHighlightStyle(state.inlineHighlightStyle)
    }
}

public struct VVDiffControls: View {
    @Binding private var state: VVDiffControlsState
    private let style: VVDiffControlsStyle

    public init(
        state: Binding<VVDiffControlsState>,
        style: VVDiffControlsStyle = .toolbar
    ) {
        self._state = state
        self.style = style
    }

    public var body: some View {
        Group {
            switch style {
            case .toolbar:
                toolbarLayout
            case .sidebar:
                sidebarLayout
            }
        }
    }

    private var toolbarLayout: some View {
        VStack(alignment: .leading, spacing: 12) {
            Picker("Layout", selection: $state.renderStyle) {
                Text("Inline").tag(VVDiffRenderStyle.inline)
                Text("Side By Side").tag(VVDiffRenderStyle.sideBySide)
            }
            .pickerStyle(.segmented)

            HStack(spacing: 12) {
                Picker("Indicators", selection: $state.changeIndicatorStyle) {
                    Text("Bars").tag(VVDiffChangeIndicatorStyle.bars)
                    Text("Classic").tag(VVDiffChangeIndicatorStyle.classic)
                    Text("None").tag(VVDiffChangeIndicatorStyle.none)
                }
                .pickerStyle(.segmented)
                .frame(maxWidth: 360)

                Picker("Inline", selection: $state.inlineHighlightStyle) {
                    Text("Word").tag(VVDiffInlineHighlightStyle.word)
                    Text("Off").tag(VVDiffInlineHighlightStyle.off)
                }
                .pickerStyle(.menu)
                .frame(width: 110)

                Toggle("Backgrounds", isOn: $state.showsBackgrounds)
                    .toggleStyle(.switch)

                Toggle("Wrapping", isOn: $state.wrapLines)
                    .toggleStyle(.switch)

                Toggle("Line Numbers", isOn: $state.showsLineNumbers)
                    .toggleStyle(.switch)
            }
        }
        .padding(14)
        .background(
            RoundedRectangle(cornerRadius: 14, style: .continuous)
                .fill(Color.black.opacity(0.82))
        )
        .overlay(
            RoundedRectangle(cornerRadius: 14, style: .continuous)
                .stroke(Color.white.opacity(0.12), lineWidth: 1)
        )
    }

    private var sidebarLayout: some View {
        VStack(alignment: .leading, spacing: 14) {
            sidebarControlBlock("Layout") {
                Picker("", selection: $state.renderStyle) {
                    Text("Inline").tag(VVDiffRenderStyle.inline)
                    Text("Side By Side").tag(VVDiffRenderStyle.sideBySide)
                }
                .labelsHidden()
                .pickerStyle(.segmented)
            }

            sidebarControlBlock("Indicators") {
                Picker("", selection: $state.changeIndicatorStyle) {
                    Text("Bars").tag(VVDiffChangeIndicatorStyle.bars)
                    Text("Classic").tag(VVDiffChangeIndicatorStyle.classic)
                    Text("None").tag(VVDiffChangeIndicatorStyle.none)
                }
                .labelsHidden()
                .pickerStyle(.segmented)
            }

            sidebarControlBlock("Inline Highlights") {
                Picker("", selection: $state.inlineHighlightStyle) {
                    Text("Word").tag(VVDiffInlineHighlightStyle.word)
                    Text("Off").tag(VVDiffInlineHighlightStyle.off)
                }
                .labelsHidden()
                .pickerStyle(.menu)
            }

            sidebarControlBlock("Options") {
                VStack(spacing: 8) {
                    sidebarToggleRow("Backgrounds", isOn: $state.showsBackgrounds)
                    sidebarToggleRow("Wrapping", isOn: $state.wrapLines)
                    sidebarToggleRow("Line Numbers", isOn: $state.showsLineNumbers)
                }
            }
        }
    }

    private func sidebarControlBlock<Content: View>(
        _ title: String,
        @ViewBuilder content: () -> Content
    ) -> some View {
        VStack(alignment: .leading, spacing: 7) {
            Text(title)
                .font(.system(size: 10, weight: .semibold))
                .textCase(.uppercase)
                .foregroundStyle(.secondary)
            content()
        }
        .frame(maxWidth: .infinity, alignment: .leading)
    }

    private func sidebarToggleRow(_ title: String, isOn: Binding<Bool>) -> some View {
        Toggle(isOn: isOn) {
            Text(title)
                .font(.system(size: 12, weight: .medium))
        }
        .toggleStyle(.switch)
    }
}
