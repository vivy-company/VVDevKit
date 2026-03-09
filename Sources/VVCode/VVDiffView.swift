import AppKit
import CoreText
import MetalKit
import SwiftUI
import VVHighlighting
import VVMarkdown
import VVMetalPrimitives

// MARK: - Data Model

public enum VVDiffRenderStyle: Hashable, Sendable {
    case unifiedTable
    case split
}

/// A parsed row in a unified diff table.
public struct VVDiffRow: Identifiable, Hashable, Sendable {
    public enum Kind: String, Hashable, Sendable {
        case fileHeader
        case hunkHeader
        case context
        case added
        case deleted
        case metadata
    }

    public let id: Int
    public let kind: Kind
    public let oldLineNumber: Int?
    public let newLineNumber: Int?
    public let text: String

    public init(
        id: Int,
        kind: Kind,
        oldLineNumber: Int? = nil,
        newLineNumber: Int? = nil,
        text: String
    ) {
        self.id = id
        self.kind = kind
        self.oldLineNumber = oldLineNumber
        self.newLineNumber = newLineNumber
        self.text = text
    }
}

public struct VVDiffInlineRenderResult: Sendable {
    public let scene: VVScene
    public let contentHeight: CGFloat

    public init(scene: VVScene, contentHeight: CGFloat) {
        self.scene = scene
        self.contentHeight = contentHeight
    }
}

private struct VVDiffSection: Identifiable, Hashable {
    let id: Int
    let filePath: String
    let headerRow: VVDiffRow?
    let rows: [VVDiffRow]

    var addedCount: Int { rows.filter { $0.kind == .added }.count }
    var deletedCount: Int { rows.filter { $0.kind == .deleted }.count }
    var hunkCount: Int { rows.filter { $0.kind == .hunkHeader }.count }
}

public enum VVDiffInlineRenderer {
    public static func renderUnified(
        unifiedDiff: String,
        width: CGFloat,
        theme: VVTheme,
        configuration: VVConfiguration
    ) -> VVDiffInlineRenderResult {
        let result = VVUnifiedDiffSceneRenderer.render(
            unifiedDiff: unifiedDiff,
            width: width,
            theme: markdownTheme(from: theme),
            baseFont: configuration.font,
            style: .unifiedTable
        )
        return VVDiffInlineRenderResult(
            scene: result.scene,
            contentHeight: result.contentHeight
        )
    }
}

private func markdownTheme(from theme: VVTheme) -> MarkdownTheme {
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

private extension VVDiffRow.Kind {
    var isCode: Bool {
        switch self {
        case .context, .added, .deleted:
            return true
        case .fileHeader, .hunkHeader, .metadata:
            return false
        }
    }
}

private struct VVDiffSplitRow: Identifiable, Hashable {
    struct Cell: Hashable {
        let rowID: Int
        let lineNumber: Int?
        let text: String
        let kind: VVDiffRow.Kind
        let inlineChanges: [InlineRange]
    }

    struct InlineRange: Hashable {
        let start: Int
        let end: Int
    }

    let id: Int
    let header: VVDiffRow?
    let left: Cell?
    let right: Cell?
}

private func mapDiffRowKind(_ kind: VVUnifiedDiffRow.Kind) -> VVDiffRow.Kind {
    switch kind {
    case .fileHeader: return .fileHeader
    case .hunkHeader: return .hunkHeader
    case .context: return .context
    case .added: return .added
    case .deleted: return .deleted
    case .metadata: return .metadata
    }
}

private func mapDiffRow(_ row: VVUnifiedDiffRow) -> VVDiffRow {
    VVDiffRow(
        id: row.id,
        kind: mapDiffRowKind(row.kind),
        oldLineNumber: row.oldLineNumber,
        newLineNumber: row.newLineNumber,
        text: row.text
    )
}

private func mapDiffSection(_ section: VVUnifiedDiffSection) -> VVDiffSection {
    VVDiffSection(
        id: section.id,
        filePath: section.filePath,
        headerRow: section.headerRow.map(mapDiffRow),
        rows: section.rows.map(mapDiffRow)
    )
}

private func mapDiffSplitRow(_ row: VVUnifiedDiffSplitRow) -> VVDiffSplitRow {
    VVDiffSplitRow(
        id: row.id,
        header: row.header.map(mapDiffRow),
        left: row.left.map { cell in
            VVDiffSplitRow.Cell(
                rowID: cell.rowID,
                lineNumber: cell.lineNumber,
                text: cell.text,
                kind: mapDiffRowKind(cell.kind),
                inlineChanges: cell.inlineChanges.map { .init(start: $0.start, end: $0.end) }
            )
        },
        right: row.right.map { cell in
            VVDiffSplitRow.Cell(
                rowID: cell.rowID,
                lineNumber: cell.lineNumber,
                text: cell.text,
                kind: mapDiffRowKind(cell.kind),
                inlineChanges: cell.inlineChanges.map { .init(start: $0.start, end: $0.end) }
            )
        }
    )
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

/// Geometry cache for a single row in the diff view.
private struct RowGeometry {
    let rowIndex: Int
    let rowID: Int
    let y: CGFloat
    let height: CGFloat
    let isCodeRow: Bool
    let text: String
    let codeStartX: CGFloat
    let paneX: CGFloat      // For split mode: left pane = 0, right pane = columnWidth + 1
    let paneWidth: CGFloat  // For split mode: width of the pane containing this row
}

private struct RowGeometryCacheKey: Equatable {
    let rowsSignature: Int
    let style: VVDiffRenderStyle
    let widthBucket: Int
    let wrapsUnified: Bool
    let fontSignature: Int
}

private struct ViewportSceneCacheKey: Equatable {
    let startIndex: Int
    let endIndex: Int
    let renderWidthBucket: Int
    let highlightVersion: Int

    func contains(visibleRange: Range<Int>, renderWidth: CGFloat, highlightVersion: Int) -> Bool {
        renderWidthBucket == Int((renderWidth * 2).rounded()) &&
        self.highlightVersion == highlightVersion &&
        visibleRange.lowerBound >= startIndex &&
        visibleRange.upperBound <= endIndex
    }
}

// MARK: - Parsing

/// Backward-compatible parse entry point for tests. Use `VVDiffView(unifiedDiff:)` for rendering.
public enum VVDiffTable {
    /// Parse unified git diff text into rows suitable for `VVDiffView`.
    public static func parse(unifiedDiff: String) -> [VVDiffRow] {
        parseDiffModel(unifiedDiff: unifiedDiff).rows
    }
}

private struct ParsedDiffModel {
    let rows: [VVDiffRow]
    let analysis: VVUnifiedDiffDocument
}

private func parseDiffModel(unifiedDiff: String) -> ParsedDiffModel {
    let analysis = VVUnifiedDiffSceneRenderer.analyze(unifiedDiff: unifiedDiff)
    let rawHunkHeaders = unifiedDiff
        .split(omittingEmptySubsequences: false, whereSeparator: \.isNewline)
        .lazy
        .filter { $0.hasPrefix("@@") }
        .map(String.init)

    var rawHeaderIterator = rawHunkHeaders.makeIterator()
    let rows = analysis.rows.map { row in
        guard row.kind == .hunkHeader, let rawHeader = rawHeaderIterator.next() else {
            return mapDiffRow(row)
        }
        return VVDiffRow(
            id: row.id,
            kind: .hunkHeader,
            oldLineNumber: row.oldLineNumber,
            newLineNumber: row.newLineNumber,
            text: rawHeader
        )
    }
    return ParsedDiffModel(rows: rows, analysis: analysis)
}

// MARK: - VVDiffRenderer

private typealias MDLayoutGlyph = VVMarkdown.LayoutGlyph
private typealias MDFontVariant = VVMarkdown.FontVariant

/// Builds a VVScene from diff data using VVMetalPrimitives.
private final class VVDiffRenderer {
    let font: NSFont
    let lineHeight: CGFloat
    let charWidth: CGFloat
    let headerHeight: CGFloat
    let codeInsetX: CGFloat = 10

    var textColor: SIMD4<Float> = .gray(0.83)
    var backgroundColor: SIMD4<Float> = .gray(0.12)
    var gutterTextColor: SIMD4<Float> = .gray50
    var gutterBgColor: SIMD4<Float> = .gray(0.12)
    var addedBgColor: SIMD4<Float> = .rgba(0, 0.5, 0, 0.13)
    var deletedBgColor: SIMD4<Float> = .rgba(0.5, 0, 0, 0.13)
    var hunkBgColor: SIMD4<Float> = .gray20.withOpacity(0.88)
    var headerBgColor: SIMD4<Float> = .gray(0.15, opacity: 0.99)
    var metadataBgColor: SIMD4<Float> = .gray(0.15, opacity: 0.58)
    var addedMarkerColor: SIMD4<Float> = .rgba(0, 0.8, 0)
    var deletedMarkerColor: SIMD4<Float> = .rgba(0.8, 0, 0)
    var modifiedColor: SIMD4<Float> = .rgba(0, 0.5, 1)
    var addedInlineBg: SIMD4<Float> = .rgba(0, 0.5, 0, 0.22)
    var deletedInlineBg: SIMD4<Float> = .rgba(0.5, 0, 0, 0.22)
    var emptyPaneBg: SIMD4<Float> = .gray(0.15, opacity: 0.30)

    var layoutEngine: MarkdownLayoutEngine

    init(font: NSFont, theme: VVTheme, contentWidth: CGFloat) {
        self.font = font
        self.lineHeight = ceil(font.pointSize * 1.6)
        self.headerHeight = ceil(font.pointSize * 1.6 * 1.5)

        // Compute monospace char width from CTFont
        let ctFont = font as CTFont
        var glyphID: CGGlyph = 0
        var char: UniChar = 0x004D // 'M'
        CTFontGetGlyphsForCharacters(ctFont, &char, &glyphID, 1)
        var advance = CGSize.zero
        CTFontGetAdvancesForGlyphs(ctFont, .horizontal, &glyphID, &advance, 1)
        self.charWidth = advance.width > 0 ? advance.width : font.pointSize * 0.6

        // Create layout engine with a minimal markdown theme
        var mdTheme = MarkdownTheme.dark
        mdTheme.textColor = theme.textColor.simdColor
        mdTheme.contentPadding = 0
        mdTheme.paragraphSpacing = 0
        self.layoutEngine = MarkdownLayoutEngine(baseFont: font, theme: mdTheme, contentWidth: contentWidth)

        updateThemeColors(theme)
    }

    func updateThemeColors(_ theme: VVTheme) {
        textColor = theme.textColor.simdColor
        backgroundColor = theme.backgroundColor.simdColor
        gutterTextColor = theme.gutterTextColor.simdColor
        gutterBgColor = theme.gutterBackgroundColor.simdColor
        addedBgColor = withAlpha(theme.gitAddedColor.simdColor, 0.13)
        deletedBgColor = withAlpha(theme.gitDeletedColor.simdColor, 0.13)
        hunkBgColor = withAlpha(theme.currentLineColor.simdColor, 0.88)
        headerBgColor = withAlpha(theme.gutterBackgroundColor.simdColor, 0.99)
        metadataBgColor = withAlpha(theme.gutterBackgroundColor.simdColor, 0.58)
        addedMarkerColor = theme.gitAddedColor.simdColor
        deletedMarkerColor = theme.gitDeletedColor.simdColor
        modifiedColor = theme.gitModifiedColor.simdColor
        addedInlineBg = withAlpha(theme.gitAddedColor.simdColor, 0.22)
        deletedInlineBg = withAlpha(theme.gitDeletedColor.simdColor, 0.22)
        emptyPaneBg = withAlpha(theme.gutterBackgroundColor.simdColor, 0.30)
    }

    func updateContentWidth(_ width: CGFloat) {
        layoutEngine.updateContentWidth(width)
    }

    private func wrapCapacity(totalWidth: CGFloat, codeStartX: CGFloat) -> Int {
        let available = max(0, totalWidth - codeStartX - codeInsetX - 12)
        guard available > 0 else { return 1 }
        return max(1, Int(floor(available / max(charWidth, 1))))
    }

    private func wrappedTextSegments(_ text: String, maxChars: Int) -> [String] {
        guard maxChars > 0 else { return [text] }
        var result: [String] = []
        let logicalLines = text.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        for line in logicalLines {
            if line.isEmpty {
                result.append("")
                continue
            }
            var start = line.startIndex
            while start < line.endIndex {
                let end = line.index(start, offsetBy: maxChars, limitedBy: line.endIndex) ?? line.endIndex
                result.append(String(line[start..<end]))
                start = end
            }
        }
        return result.isEmpty ? [""] : result
    }

    private func wrappedTextSegmentCount(_ text: String, maxChars: Int) -> Int {
        guard maxChars > 0 else { return 1 }
        var count = 0
        text.enumerateSubstrings(in: text.startIndex..<text.endIndex, options: [.byLines, .substringNotRequired]) { _, range, _, _ in
            let length = text.distance(from: range.lowerBound, to: range.upperBound)
            if length == 0 {
                count += 1
            } else {
                count += max(1, Int(ceil(Double(length) / Double(maxChars))))
            }
        }
        return max(count, 1)
    }

    // Shared scene construction lives in VVUnifiedDiffSceneRenderer.
    // This wrapper-local renderer now exists only for diff metrics and colors that
    // are still needed for sizing, geometry, and selection math.

    private func withAlpha(_ color: SIMD4<Float>, _ alpha: Float) -> SIMD4<Float> {
        SIMD4(color.x, color.y, color.z, alpha)
    }
}

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
    private var renderer: MarkdownMetalRenderer?
    private var sceneRenderer: MarkdownScenePrimitiveRenderer?
    private var diffRenderer: VVDiffRenderer?
    var metalContext: VVMetalContext?

    private var rows: [VVDiffRow] = []
    private var unifiedDiffSource: String = ""
    private var sections: [VVDiffSection] = []
    private var splitRows: [VVDiffSplitRow] = []
    private var analyzedDocument: VVUnifiedDiffDocument?
    private var renderStyle: VVDiffRenderStyle = .unifiedTable
    private var theme: VVTheme = .defaultDark
    private var configuration: VVConfiguration = .default
    private var language: VVLanguage?
    private var syntaxHighlightingEnabled: Bool = true
    private var onFileHeaderActivate: ((String) -> Void)?

    private var cachedScene: VVScene?
    private var cachedSceneKey: ViewportSceneCacheKey?
    private var cachedOrderedScenePrimitives: [VVPrimitive] = []
    private var cachedSceneVisibilityIndex: VVPrimitiveVisibilityIndex?
    private var contentHeight: CGFloat = 0
    private var currentDrawableSize: CGSize = .zero
    private var currentScrollOffset: CGPoint = .zero

    private var highlightedRanges: [Int: [(NSRange, SIMD4<Float>)]] = [:]
    private var staleHighlightedRowIDs: Set<Int> = []
    private var highlightSceneVersion: Int = 0
    private var highlightGeneration: Int = 0
    private var highlightTask: Task<Void, Never>?
    private var codeRows: [VVDiffRow] = []
    private var codeRowIndexByID: [Int: Int] = [:]
    private var highlightedCodeRowCount: Int = 0
    private var pendingHighlightCodeRowCount: Int = 0

    private static let initialHighlightCodeRows: Int = 3_000
    private static let incrementalHighlightCodeRows: Int = 3_000
    private static let highlightPrefetchCodeRows: Int = 600
    private static let highlightViewportMargin: CGFloat = 220
    private static let highlightWarmupContextRows: Int = 192
    private static let renderCullPadding: CGFloat = 512
    private static let sceneCacheViewportPaddingMultiplier: CGFloat = 1.25

    private var baseFont: NSFont = .monospacedSystemFont(ofSize: 13, weight: .regular)
    private var baseFontAscent: CGFloat = 0
    private var baseFontDescent: CGFloat = 0

    // Selection support
    private let selectionController = VVTextSelectionController<DiffTextPosition>()
    private let selectionColor: SIMD4<Float> = .rgba(0.24, 0.40, 0.65, 0.55)
    private var rowGeometries: [RowGeometry] = []
    private var filePathByHeaderRowID: [Int: String] = [:]
    private var rowGeometryCacheKey: RowGeometryCacheKey?
    private var rowGeometriesContentHeight: CGFloat = 0
    private var rowsSignature: Int = 0
    private var fastPlainModeEnabled: Bool = false
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

        addSubview(scrollView)
        scrollView.addSubview(metalView)

        if let ctx = metalContext {
            renderer = MarkdownMetalRenderer(context: ctx, baseFont: baseFont, scaleFactor: NSScreen.main?.backingScaleFactor ?? 2.0)
            renderer?.glyphAtlas.preloadASCII(fontSize: baseFont.pointSize, baseFont: baseFont)
        } else {
            renderer = nil
        }

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(scrollViewBoundsChanged),
            name: NSView.boundsDidChangeNotification,
            object: scrollView.contentView
        )
    }

    @objc private func scrollViewBoundsChanged(_ notification: Notification) {
        updateMetalViewport()
        requestViewportHighlightingIfNeeded()
        if shouldRedrawForHighlightedRowIDs(staleHighlightedRowIDs) {
            cachedScene = nil
            cachedSceneKey = nil
        }
        metalView.setNeedsDisplay(metalView.bounds)
    }

    override func layout() {
        super.layout()
        scrollView.frame = bounds
        updateContentSize()
        requestViewportHighlightingIfNeeded()
    }

    /// Keep MTKView pinned to the visible viewport (same as VVMetalEditorContainerView).
    private func updateMetalViewport() {
        let viewportSize = scrollView.contentView.bounds.size
        let viewportOrigin = scrollView.contentView.frame.origin
        currentScrollOffset = scrollView.contentView.bounds.origin
        metalView.frame = CGRect(origin: viewportOrigin, size: viewportSize)
    }

    private var wrapsUnified: Bool {
        configuration.wrapLines && (renderStyle == .split || !fastPlainModeEnabled)
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
        analysis: VVUnifiedDiffDocument,
        rows: [VVDiffRow],
        style: VVDiffRenderStyle,
        theme: VVTheme,
        configuration: VVConfiguration,
        language: VVLanguage?,
        syntaxHighlightingEnabled: Bool,
        onFileHeaderActivate: ((String) -> Void)?
    ) {
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
        let langChanged = self.language?.identifier != language?.identifier
        let syntaxHighlightingChanged = self.syntaxHighlightingEnabled != effectiveSyntaxHighlightingEnabled
        let effectiveWrapChanged = wrapsChanged || styleChanged || fastPlainModeChanged

        if !rowsChanged,
           !styleChanged,
           !themeChanged,
           !fontChanged,
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
        self.language = language
        self.syntaxHighlightingEnabled = effectiveSyntaxHighlightingEnabled
        analyzedDocument = analysis
        rowsSignature = rowsChanged ? Self.computeRowsSignature(rows) : rowsSignature
        rowGeometryCacheKey = nil

        if rowsChanged {
            rebuildCodeRowLookup()
        }

        if style == .split {
            scrollView?.hasHorizontalScroller = !wrapsUnified
        } else {
            scrollView?.hasHorizontalScroller = !wrapsUnified && !fastPlainModeEnabled
        }

        if fontChanged {
            baseFont = configuration.font
            baseFontAscent = CTFontGetAscent(baseFont)
            baseFontDescent = CTFontGetDescent(baseFont)
            let scale = window?.backingScaleFactor ?? NSScreen.main?.backingScaleFactor ?? 2.0
            if let ctx = metalContext {
                renderer = MarkdownMetalRenderer(context: ctx, baseFont: baseFont, scaleFactor: scale)
                renderer?.glyphAtlas.preloadASCII(fontSize: baseFont.pointSize, baseFont: baseFont)
            }
            sceneRenderer = nil
        }

        if rowsChanged || styleChanged {
            let document = analysis
            sections = document.sections.map(mapDiffSection)
            rebuildFileHeaderPathLookup()
            splitRows = document.splitRows.map(mapDiffSplitRow)
        }

        if themeChanged || fontChanged {
            diffRenderer = nil
        }

        if rowsChanged || langChanged || fontChanged || syntaxHighlightingChanged {
            resetHighlightingState()
        }

        cachedScene = nil
        cachedSceneKey = nil
        updateContentSize()
        requestViewportHighlightingIfNeeded()
        metalView?.setNeedsDisplay(metalView.bounds)
    }

    private func ensureDiffRenderer() -> VVDiffRenderer {
        if let existing = diffRenderer { return existing }
        let width = scrollView?.bounds.width ?? bounds.width
        let r = VVDiffRenderer(font: configuration.font, theme: theme, contentWidth: width)
        diffRenderer = r
        return r
    }

    private func updateContentSize() {
        let width = scrollView?.bounds.width ?? bounds.width
        let dr = ensureDiffRenderer()
        dr.updateContentWidth(width)
        buildRowGeometries(width: width)
        contentHeight = rowGeometriesContentHeight
        cachedScene = nil
        cachedSceneKey = nil

        let wrapsUnified = self.wrapsUnified

        // Compute max line width for horizontal scrolling
        let maxLineWidth: CGFloat
        if wrapsUnified || fastPlainModeEnabled {
            maxLineWidth = width
        } else {
            var widestLine = width
            for geo in rowGeometries {
                let candidate = geo.codeStartX + codeInsetX + CGFloat(geo.text.count) * dr.charWidth + 20
                if candidate > widestLine {
                    widestLine = candidate
                }
            }
            maxLineWidth = widestLine
        }

        let minWidth: CGFloat
        if renderStyle == .split {
            minWidth = 840 // 420 * 2
        } else if wrapsUnified || fastPlainModeEnabled {
            minWidth = width
        } else {
            minWidth = max(width, 520)
        }

        // Size the document view for scroll bars; MTKView stays viewport-sized
        let docWidth = (wrapsUnified || fastPlainModeEnabled) ? width : max(maxLineWidth, minWidth, width)
        let docHeight = max(contentHeight, scrollView.bounds.height)
        documentView.frame = CGRect(x: 0, y: 0, width: docWidth, height: docHeight)
        updateMetalViewport()
    }

    private func buildRowGeometries(width: CGFloat) {
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

        rowGeometries.removeAll(keepingCapacity: true)
        let dr = ensureDiffRenderer()

        switch renderStyle {
        case .unifiedTable:
            buildRowGeometriesUnified(width: width, renderer: dr, wrapLines: wrapsUnified)
        case .split:
            buildRowGeometriesSplit(width: width, renderer: dr, wrapLines: wrapsUnified)
        }

        rowGeometriesContentHeight = rowGeometries.last.map { $0.y + $0.height } ?? 0
        rowGeometryCacheKey = cacheKey
    }

    private func buildRowGeometriesUnified(width: CGFloat, renderer: VVDiffRenderer, wrapLines: Bool) {
        let maxOld = analyzedDocument?.maxOldLineNumber ?? rows.compactMap(\.oldLineNumber).max() ?? 0
        let maxNew = analyzedDocument?.maxNewLineNumber ?? rows.compactMap(\.newLineNumber).max() ?? 0
        let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
        let gutterColWidth = CGFloat(gutterDigits) * renderer.charWidth + 16
        let markerWidth = renderer.charWidth + 8
        let codeStartX = gutterColWidth * 2 + markerWidth
        let maxCharsPerVisualLine = wrapCapacity(totalWidth: width, codeStartX: codeStartX, charWidth: renderer.charWidth)

        var y: CGFloat = 0
        var rowIndex = 0

        for section in sections {
            // File header
            if let header = section.headerRow {
                let rowH = renderer.headerHeight
                rowGeometries.append(RowGeometry(
                    rowIndex: rowIndex,
                    rowID: header.id,
                    y: y,
                    height: rowH,
                    isCodeRow: false,
                    text: header.text,
                    codeStartX: codeStartX,
                    paneX: 0,
                    paneWidth: width
                ))
                y += rowH
                rowIndex += 1
            }

            // Section rows (skip metadata)
            for row in section.rows {
                if row.kind == .metadata { continue }
                let wrappedLines: [String]
                if wrapLines && (row.kind.isCode || row.kind == .hunkHeader) {
                    wrappedLines = wrappedTextSegments(row.text, maxChars: maxCharsPerVisualLine)
                } else {
                    wrappedLines = [row.text]
                }

                for line in wrappedLines {
                    let rowH = renderer.lineHeight
                    rowGeometries.append(RowGeometry(
                        rowIndex: rowIndex,
                        rowID: row.id,
                        y: y,
                        height: rowH,
                        isCodeRow: row.kind.isCode,
                        text: line,
                        codeStartX: codeStartX,
                        paneX: 0,
                        paneWidth: width
                    ))
                    y += rowH
                    rowIndex += 1
                }
            }
        }
    }

    private func wrapCapacity(totalWidth: CGFloat, codeStartX: CGFloat, charWidth: CGFloat) -> Int {
        let available = max(0, totalWidth - codeStartX - codeInsetX - 12)
        guard available > 0 else { return 1 }
        return max(1, Int(floor(available / max(charWidth, 1))))
    }

    private func wrappedTextSegments(_ text: String, maxChars: Int) -> [String] {
        guard maxChars > 0 else { return [text] }
        var result: [String] = []
        let logicalLines = text.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        for line in logicalLines {
            if line.isEmpty {
                result.append("")
                continue
            }
            var start = line.startIndex
            while start < line.endIndex {
                let end = line.index(start, offsetBy: maxChars, limitedBy: line.endIndex) ?? line.endIndex
                result.append(String(line[start..<end]))
                start = end
            }
        }
        return result.isEmpty ? [""] : result
    }

    private func buildRowGeometriesSplit(width: CGFloat, renderer: VVDiffRenderer, wrapLines: Bool) {
        let maxOld = analyzedDocument?.maxOldLineNumber ?? rows.compactMap(\.oldLineNumber).max() ?? 0
        let maxNew = analyzedDocument?.maxNewLineNumber ?? rows.compactMap(\.newLineNumber).max() ?? 0
        let gutterDigits = max(1, String(max(maxOld, maxNew)).count)
        let gutterColWidth = CGFloat(gutterDigits) * renderer.charWidth + 16
        let markerWidth = renderer.charWidth + 4
        let columnWidth = max(420, floor(width / 2))
        let paneCodeStartX = markerWidth + gutterColWidth
        let paneMaxCharsPerVisualLine = wrapCapacity(totalWidth: columnWidth, codeStartX: paneCodeStartX, charWidth: renderer.charWidth)
        let headerMaxCharsPerVisualLine = wrapCapacity(totalWidth: columnWidth * 2, codeStartX: 12, charWidth: renderer.charWidth)

        var y: CGFloat = 0
        var rowIndex = 0

        for splitRow in splitRows {
            if let header = splitRow.header {
                let wrappedLines: [String]
                if wrapLines && header.kind == .hunkHeader {
                    wrappedLines = wrappedTextSegments(header.text, maxChars: headerMaxCharsPerVisualLine)
                } else {
                    wrappedLines = [header.text]
                }
                let rowH = header.kind == .fileHeader
                    ? renderer.headerHeight
                    : renderer.lineHeight * CGFloat(max(1, wrappedLines.count))
                if header.kind == .fileHeader {
                    rowGeometries.append(RowGeometry(
                        rowIndex: rowIndex,
                        rowID: header.id,
                        y: y,
                        height: rowH,
                        isCodeRow: false,
                        text: header.text,
                        codeStartX: paneCodeStartX,
                        paneX: 0,
                        paneWidth: columnWidth * 2
                    ))
                    rowIndex += 1
                } else {
                    for line in wrappedLines {
                        rowGeometries.append(RowGeometry(
                            rowIndex: rowIndex,
                            rowID: header.id,
                            y: y,
                            height: renderer.lineHeight,
                            isCodeRow: false,
                            text: line,
                            codeStartX: paneCodeStartX,
                            paneX: 0,
                            paneWidth: columnWidth * 2
                        ))
                        y += renderer.lineHeight
                        rowIndex += 1
                    }
                    continue
                }
                y += rowH
            } else {
                let leftWrappedLines = splitRow.left.map { cell in
                    wrapLines && cell.kind.isCode
                        ? wrappedTextSegments(cell.text, maxChars: paneMaxCharsPerVisualLine)
                        : [cell.text]
                } ?? []
                let rightWrappedLines = splitRow.right.map { cell in
                    wrapLines && cell.kind.isCode
                        ? wrappedTextSegments(cell.text, maxChars: paneMaxCharsPerVisualLine)
                        : [cell.text]
                } ?? []
                let visualLineCount = max(1, max(leftWrappedLines.count, rightWrappedLines.count))
                let rowH = renderer.lineHeight * CGFloat(visualLineCount)
                // Add left cell if present
                if let left = splitRow.left {
                    for (lineIndex, line) in leftWrappedLines.enumerated() {
                        rowGeometries.append(RowGeometry(
                            rowIndex: rowIndex,
                            rowID: left.rowID,
                            y: y + CGFloat(lineIndex) * renderer.lineHeight,
                            height: renderer.lineHeight,
                            isCodeRow: left.kind.isCode,
                            text: line,
                            codeStartX: paneCodeStartX,
                            paneX: 0,
                            paneWidth: columnWidth
                        ))
                        rowIndex += 1
                    }
                }
                // Add right cell if present
                if let right = splitRow.right {
                    for (lineIndex, line) in rightWrappedLines.enumerated() {
                        rowGeometries.append(RowGeometry(
                            rowIndex: rowIndex,
                            rowID: right.rowID,
                            y: y + CGFloat(lineIndex) * renderer.lineHeight,
                            height: renderer.lineHeight,
                            isCodeRow: right.kind.isCode,
                            text: line,
                            codeStartX: paneCodeStartX,
                            paneX: columnWidth,
                            paneWidth: columnWidth
                        ))
                        rowIndex += 1
                    }
                }
                y += rowH
            }
        }
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
        codeRows = rows.filter { $0.kind.isCode }
        codeRowIndexByID.removeAll(keepingCapacity: true)
        codeRowIndexByID.reserveCapacity(codeRows.count)
        for (index, row) in codeRows.enumerated() {
            codeRowIndexByID[row.id] = index
        }
    }

    private func resetHighlightingState() {
        highlightGeneration += 1
        highlightTask?.cancel()
        highlightTask = nil
        highlightedRanges = [:]
        staleHighlightedRowIDs.removeAll(keepingCapacity: true)
        highlightSceneVersion &+= 1
        highlightedCodeRowCount = 0
        pendingHighlightCodeRowCount = 0

        guard syntaxHighlightingEnabled else { return }
        guard !codeRows.isEmpty else { return }

        scheduleHighlightingIfNeeded(targetCodeRowCount: desiredHighlightedCodeRowCountForVisibleViewport())
    }

    private func requestViewportHighlightingIfNeeded() {
        guard syntaxHighlightingEnabled else { return }
        guard !codeRows.isEmpty else { return }
        let targetCount = desiredHighlightedCodeRowCountForVisibleViewport()
        scheduleHighlightingIfNeeded(targetCodeRowCount: targetCount)
    }

    private func desiredHighlightedCodeRowCountForVisibleViewport() -> Int {
        let minimumTarget = min(codeRows.count, max(256, Self.highlightWarmupContextRows * 2))
        guard let scrollView else { return minimumTarget }

        let visibleRect = scrollView.contentView.bounds
        guard let maxVisibleCodeIndex = maxVisibleCodeRowIndex(in: visibleRect) else {
            return minimumTarget
        }

        let desiredByViewport = min(
            codeRows.count,
            maxVisibleCodeIndex + 1 + Self.highlightPrefetchCodeRows
        )
        return max(minimumTarget, desiredByViewport)
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

    private func maxVisibleCodeRowIndex(in visibleRect: CGRect) -> Int? {
        guard !rowGeometries.isEmpty else { return nil }

        let minY = visibleRect.minY - Self.highlightViewportMargin
        let maxY = visibleRect.maxY + Self.highlightViewportMargin
        let startIndex = firstVisibleGeometryIndex(minY: minY)

        var maxCodeIndex: Int?
        var index = startIndex
        while index < rowGeometries.count {
            let geometry = rowGeometries[index]
            if geometry.y > maxY {
                break
            }
            if let codeIndex = codeRowIndexByID[geometry.rowID] {
                if let current = maxCodeIndex {
                    maxCodeIndex = max(current, codeIndex)
                } else {
                    maxCodeIndex = codeIndex
                }
            }
            index += 1
        }

        return maxCodeIndex
    }

    private func scheduleHighlightingIfNeeded(targetCodeRowCount: Int) {
        let boundedTarget = min(codeRows.count, max(0, targetCodeRowCount))
        guard boundedTarget > highlightedCodeRowCount else { return }

        pendingHighlightCodeRowCount = max(pendingHighlightCodeRowCount, boundedTarget)
        startNextHighlightBatchIfNeeded()
    }

    private func startNextHighlightBatchIfNeeded() {
        guard highlightTask == nil else { return }
        guard pendingHighlightCodeRowCount > highlightedCodeRowCount else { return }

        let generation = highlightGeneration
        let startIndex = highlightedCodeRowCount
        let batchLimit = startIndex == 0 ? Self.initialHighlightCodeRows : Self.incrementalHighlightCodeRows
        let endIndex = min(codeRows.count, min(pendingHighlightCodeRowCount, startIndex + batchLimit))

        guard endIndex > startIndex else { return }

        let warmupRows = min(Self.highlightWarmupContextRows, startIndex)
        let parseStart = startIndex - warmupRows
        let batchRows = Array(codeRows[parseStart..<endIndex])
        let targetRowIDs = Set(codeRows[startIndex..<endIndex].map(\.id))
        let currentLanguage = language
        let currentTheme = theme
        let currentFont = configuration.font

        highlightTask = Task(priority: .utility) { [weak self] in
            guard !Task.isCancelled else { return }
            let ranges = await Self.computeHighlightRanges(
                rows: batchRows,
                language: currentLanguage,
                theme: currentTheme,
                font: currentFont
            )
            guard !Task.isCancelled else { return }

            await MainActor.run { [weak self] in
                guard let self, self.highlightGeneration == generation, !Task.isCancelled else { return }
                for (rowID, rowRanges) in ranges {
                    guard targetRowIDs.contains(rowID) else { continue }
                    self.highlightedRanges[rowID] = rowRanges
                }
                if self.cachedSceneIntersectsRowIDs(targetRowIDs) {
                    self.staleHighlightedRowIDs.formUnion(targetRowIDs)
                }
                self.highlightSceneVersion &+= 1
                self.highlightedCodeRowCount = max(self.highlightedCodeRowCount, endIndex)
                self.highlightTask = nil
                if self.cachedSceneIntersectsRowIDs(targetRowIDs) {
                    self.cachedScene = nil
                    self.cachedSceneKey = nil
                }
                if self.shouldRedrawForHighlightedRowIDs(targetRowIDs) {
                    self.metalView?.setNeedsDisplay(self.metalView.bounds)
                }
                self.startNextHighlightBatchIfNeeded()
            }
        }
    }

    private func shouldRedrawForHighlightedRowIDs(_ rowIDs: Set<Int>) -> Bool {
        guard !rowIDs.isEmpty, let scrollView else { return false }

        let visibleRect = scrollView.contentView.bounds.insetBy(dx: -Self.renderCullPadding, dy: -Self.renderCullPadding)
        return geometryRange(visibleGeometryRange(in: visibleRect), intersects: rowIDs)
    }

    private func cachedSceneIntersectsRowIDs(_ rowIDs: Set<Int>) -> Bool {
        guard !rowIDs.isEmpty, let cachedSceneKey else { return false }
        return geometryRange(cachedSceneKey.startIndex..<cachedSceneKey.endIndex, intersects: rowIDs)
    }

    private func geometryRange(_ range: Range<Int>, intersects rowIDs: Set<Int>) -> Bool {
        guard range.lowerBound < range.upperBound else { return false }
        for index in range where rowIDs.contains(rowGeometries[index].rowID) {
            return true
        }
        return false
    }

    private static func computeHighlightRanges(
        rows: [VVDiffRow],
        language: VVLanguage?,
        theme: VVTheme,
        font: NSFont
    ) async -> [Int: [(NSRange, SIMD4<Float>)]] {
        guard let language,
              let languageConfig = LanguageRegistry.shared.language(for: language.identifier) else {
            return [:]
        }
        return await VVDiffHighlighting.computeHighlightedRanges(
            rows: rows,
            language: languageConfig,
            highlightTheme: VVDiffHighlighting.highlightTheme(
                isDarkBackground: theme.backgroundColor.brightnessComponent < 0.5
            ),
            font: font,
            rowID: \.id,
            rowText: \.text,
            rowIsCode: { $0.kind.isCode }
        )
    }

    override func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        if window == nil {
            metalView?.releaseDrawables()
        }
    }

    override func viewDidHide() {
        super.viewDidHide()
        metalView?.releaseDrawables()
    }

    override func viewDidUnhide() {
        super.viewDidUnhide()
        metalView?.setNeedsDisplay(metalView.bounds)
    }
}

// MARK: - MTKViewDelegate

extension VVDiffMetalView: MTKViewDelegate {
    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {
        currentDrawableSize = size
    }

    func draw(in view: MTKView) {
        guard let renderer,
              let drawable = view.currentDrawable else { return }

        let dr = ensureDiffRenderer()
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

        let visibleRect = scrollView.contentView.bounds.insetBy(dx: -Self.renderCullPadding, dy: -Self.renderCullPadding)
        let wrapsUnified = self.wrapsUnified
        let renderWidth = (wrapsUnified || fastPlainModeEnabled)
            ? scrollView.bounds.width
            : max(scrollView.bounds.width, documentView.frame.width)
        let visibleRange = visibleGeometryRange(in: visibleRect)
        let sceneKey = makeViewportSceneCacheKey(visibleRange: visibleRange, renderWidth: renderWidth)

        // Build or reuse scene
        let scene: VVScene
        if let cached = cachedScene, let cachedSceneKey, cachedSceneKey.contains(visibleRange: visibleRange, renderWidth: renderWidth, highlightVersion: highlightSceneVersion) {
            scene = cached
        } else {
            scene = buildViewportScene(visibleRect: visibleRect, renderWidth: renderWidth, cacheKey: sceneKey)
            cachedScene = scene
            cachedSceneKey = sceneKey
            staleHighlightedRowIDs.removeAll(keepingCapacity: true)
            cachedOrderedScenePrimitives = scene.orderedPrimitives()
            cachedSceneVisibilityIndex = VVPrimitiveVisibilityIndex(
                orderedPrimitives: cachedOrderedScenePrimitives,
                bucketHeight: Self.renderCullPadding
            )
        }

        let sceneRenderer = self.sceneRenderer ?? MarkdownScenePrimitiveRenderer(baseFont: renderer.baseFont)
        self.sceneRenderer = sceneRenderer
        sceneRenderer.updateBehavior(
            MarkdownSceneRenderingBehavior(
                imageTextureProvider: nil,
                shouldUnderlineLinkRun: { _ in false },
                missingImageBehavior: .skip
            )
        )
        sceneRenderer.renderScene(
            scene,
            orderedPrimitives: cachedOrderedScenePrimitives,
            visibleRect: visibleRect,
            visibilityIndex: cachedSceneVisibilityIndex,
            encoder: encoder,
            renderer: renderer,
            scissorRectForClip: { [weak self] in self?.scissorRect(for: $0) ?? MTLScissorRect(x: 0, y: 0, width: 0, height: 0) },
            fullScissorRect: { [weak self] in self?.fullScissorRect() ?? MTLScissorRect(x: 0, y: 0, width: 0, height: 0) }
        )

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

        encoder.endEncoding()
        renderer.recycleTransientBuffers(after: commandBuffer)
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
    }

    private func renderScene(
        _ scene: VVScene,
        orderedPrimitives: [VVPrimitive],
        visibleRect: CGRect,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        var glyphInstances: [Int: [MarkdownGlyphInstance]] = [:]
        var colorGlyphInstances: [Int: [MarkdownGlyphInstance]] = [:]

        func flushTextBatches() {
            if !glyphInstances.isEmpty || !colorGlyphInstances.isEmpty {
                renderGlyphBatches(glyphInstances, encoder: encoder, renderer: renderer, isColor: false)
                renderGlyphBatches(colorGlyphInstances, encoder: encoder, renderer: renderer, isColor: true)
            }
            glyphInstances.removeAll(keepingCapacity: true)
            colorGlyphInstances.removeAll(keepingCapacity: true)
        }

        let visiblePrimitives = cachedSceneVisibilityIndex?.visiblePrimitives(in: visibleRect, from: orderedPrimitives) ?? orderedPrimitives

        for primitive in visiblePrimitives {
            switch primitive.kind {
            case .textRun(let run):
                for glyph in run.glyphs {
                    appendGlyphInstance(glyph, renderer: renderer, glyphInstances: &glyphInstances, colorGlyphInstances: &colorGlyphInstances)
                }

            default:
                flushTextBatches()
                renderPrimitive(primitive, encoder: encoder, renderer: renderer)
            }
        }

        flushTextBatches()
    }

    private func buildViewportScene(visibleRect: CGRect, renderWidth: CGFloat, cacheKey: ViewportSceneCacheKey) -> VVScene {
        guard let analyzedDocument else { return VVScene() }
        let visibleRowIDs = rowIDs(inGeometryRange: cacheKey.startIndex..<cacheKey.endIndex)
        let result = VVUnifiedDiffSceneRenderer.render(
            document: analyzedDocument,
            width: renderWidth,
            theme: markdownTheme(from: theme),
            baseFont: configuration.font,
            style: renderStyle == .split ? .split : .unifiedTable,
            options: .full,
            highlightedRangesOverride: highlightedRanges,
            includedRowIDs: visibleRowIDs
        )
        return result.scene
    }

    private func rowIDs(inGeometryRange range: Range<Int>) -> Set<Int> {
        guard range.lowerBound < range.upperBound else { return [] }
        var rowIDs: Set<Int> = []
        rowIDs.reserveCapacity(range.count)
        for index in range {
            rowIDs.insert(rowGeometries[index].rowID)
        }
        return rowIDs
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

    private func makeViewportSceneCacheKey(visibleRange: Range<Int>, renderWidth: CGFloat) -> ViewportSceneCacheKey {
        let paddingRows = max(
            48,
            Int(ceil(Double(max(1, visibleRange.count)) * Double(Self.sceneCacheViewportPaddingMultiplier)))
        )
        let startIndex = max(0, visibleRange.lowerBound - paddingRows)
        let endIndex = min(rowGeometries.count, visibleRange.upperBound + paddingRows)
        return ViewportSceneCacheKey(
            startIndex: startIndex,
            endIndex: endIndex,
            renderWidthBucket: Int((renderWidth * 2).rounded()),
            highlightVersion: highlightSceneVersion
        )
    }

    private func renderPrimitive(
        _ primitive: VVPrimitive,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let transform = primitive.transform
        switch primitive.kind {
        case .quad(let quad):
            renderQuadPrimitive(quad, transform: transform, encoder: encoder, renderer: renderer)

        case .gradientQuad(let quad):
            renderGradientQuad(quad, transform: transform, encoder: encoder, renderer: renderer)

        case .line(let line):
            renderLinePrimitive(line, transform: transform, encoder: encoder, renderer: renderer)

        case .underline(let underline):
            let origin = transformed(point: underline.origin, by: transform)
            let size = transformed(size: CGSize(width: underline.width, height: underline.thickness), by: transform)
            let instance = LineInstance(
                position: SIMD2<Float>(Float(origin.x), Float(origin.y)),
                width: Float(max(1, size.width)),
                height: Float(max(underline.thickness, size.height)),
                color: underline.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .path(let path):
            renderPathPrimitive(path, inheritedTransform: transform, encoder: encoder, renderer: renderer)

        default:
            break
        }
    }

    private func renderGradientQuad(
        _ gradient: VVGradientQuadPrimitive,
        transform: VVTransform2D? = nil,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let frame = transformed(rect: gradient.frame, by: transform).integral
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

    private func renderQuadPrimitive(
        _ quad: VVQuadPrimitive,
        transform: VVTransform2D?,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let frame = transformed(rect: quad.frame, by: transform)
        guard frame.width > 0, frame.height > 0 else { return }

        let instance = QuadInstance(
            position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
            size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
            color: SIMD4<Float>(quad.color.x, quad.color.y, quad.color.z, quad.color.w * quad.opacity),
            cornerRadius: Float(quad.cornerRadius)
        )
        if let buffer = renderer.makeBuffer(for: [instance]) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: quad.cornerRadius > 0)
        }

        guard let border = quad.border else { return }
        if canRenderBorderAsSingleRing(border) {
            let borderInstance = QuadInstance(
                position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
                size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
                color: border.color,
                cornerRadius: Float(quad.cornerRadius),
                borderWidth: Float(border.widths.top)
            )
            if let buffer = renderer.makeBuffer(for: [borderInstance]) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: true)
            }
            return
        }
        let segments = borderSegments(for: frame, border: border, cornerRadius: quad.cornerRadius)
        if let buffer = renderer.makeBuffer(for: segments) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: segments.count, rounded: false)
        }
    }

    private func renderLinePrimitive(
        _ line: VVLinePrimitive,
        transform: VVTransform2D?,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let transformedLine = VVLinePrimitive(
            start: transformed(point: line.start, by: transform),
            end: transformed(point: line.end, by: transform),
            thickness: line.thickness,
            color: line.color,
            dash: line.dash
        )
        let segments = dashedSegments(for: transformedLine)
        let instances = segments.map { segment -> LineInstance in
            let minX = min(segment.start.x, segment.end.x)
            let minY = min(segment.start.y, segment.end.y)
            let width = abs(segment.end.x - segment.start.x)
            let height = abs(segment.end.y - segment.start.y)
            return LineInstance(
                position: SIMD2<Float>(Float(minX), Float(minY)),
                width: Float(width > 0 ? width : segment.thickness),
                height: Float(height > 0 ? height : segment.thickness),
                color: segment.color
            )
        }
        if let buffer = renderer.makeBuffer(for: instances) {
            renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: instances.count)
        }
    }

    private func renderPathPrimitive(
        _ path: VVPathPrimitive,
        inheritedTransform: VVTransform2D?,
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

        let transformedVertices = path.vertices.map {
            VVPathVertex(position: transformed(point: $0.position, by: combinedTransform), stPosition: $0.stPosition)
        }
        guard let buffer = renderer.makeBuffer(for: transformedVertices) else { return }
        if let fill = path.fill, path.fillVertexCount > 0 {
            renderer.renderPath(encoder: encoder, vertices: buffer, vertexStart: 0, vertexCount: path.fillVertexCount, color: fill)
        }
        if let stroke = path.stroke, path.strokeVertexCount > 0 {
            renderer.renderPath(encoder: encoder, vertices: buffer, vertexStart: path.fillVertexCount, vertexCount: path.strokeVertexCount, color: stroke.color)
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
        return transformed(rect: CGRect(origin: .zero, size: size), by: transform).size
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
        var index = 0
        var draw = true
        var segments: [VVLinePrimitive] = []

        while distance < length {
            let segmentLength = min(cleanedPattern[index % cleanedPattern.count], length - distance)
            let start = CGPoint(x: line.start.x + ux * distance, y: line.start.y + uy * distance)
            let end = CGPoint(x: line.start.x + ux * (distance + segmentLength), y: line.start.y + uy * (distance + segmentLength))
            if draw {
                segments.append(VVLinePrimitive(start: start, end: end, thickness: line.thickness, color: line.color))
            }
            distance += segmentLength
            index += 1
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

    private func borderSegments(for frame: CGRect, border: VVBorder, cornerRadius: CGFloat) -> [QuadInstance] {
        let widths = border.widths
        let color = border.color
        var segments: [QuadInstance] = []

        func append(_ rect: CGRect) {
            guard rect.width > 0, rect.height > 0 else { return }
            segments.append(
                QuadInstance(
                    position: SIMD2<Float>(Float(rect.origin.x), Float(rect.origin.y)),
                    size: SIMD2<Float>(Float(rect.width), Float(rect.height)),
                    color: color,
                    cornerRadius: 0
                )
            )
        }

        switch border.style {
        case .solid:
            append(CGRect(x: frame.minX, y: frame.minY, width: frame.width, height: widths.top))
            append(CGRect(x: frame.minX, y: frame.maxY - widths.bottom, width: frame.width, height: widths.bottom))
            append(CGRect(x: frame.minX, y: frame.minY + widths.top, width: widths.left, height: max(0, frame.height - widths.top - widths.bottom)))
            append(CGRect(x: frame.maxX - widths.right, y: frame.minY + widths.top, width: widths.right, height: max(0, frame.height - widths.top - widths.bottom)))
        case .dashed(let dashLength, let gapLength):
            let lines = [
                VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.minY), end: CGPoint(x: frame.maxX, y: frame.minY), thickness: max(1, widths.top), color: color, dash: .dashed(on: dashLength, off: gapLength)),
                VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.maxY), end: CGPoint(x: frame.maxX, y: frame.maxY), thickness: max(1, widths.bottom), color: color, dash: .dashed(on: dashLength, off: gapLength)),
                VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.minY), end: CGPoint(x: frame.minX, y: frame.maxY), thickness: max(1, widths.left), color: color, dash: .dashed(on: dashLength, off: gapLength)),
                VVLinePrimitive(start: CGPoint(x: frame.maxX, y: frame.minY), end: CGPoint(x: frame.maxX, y: frame.maxY), thickness: max(1, widths.right), color: color, dash: .dashed(on: dashLength, off: gapLength))
            ]
            for line in lines {
                for segment in dashedSegments(for: line) {
                    let minX = min(segment.start.x, segment.end.x)
                    let minY = min(segment.start.y, segment.end.y)
                    let width = abs(segment.end.x - segment.start.x)
                    let height = abs(segment.end.y - segment.start.y)
                    append(CGRect(x: minX, y: minY, width: width > 0 ? width : segment.thickness, height: height > 0 ? height : segment.thickness))
                }
            }
        }

        return segments
    }

    private func lerpColor(_ start: SIMD4<Float>, _ end: SIMD4<Float>, t: Float) -> SIMD4<Float> {
        let clamped = max(0, min(1, t))
        return start + (end - start) * clamped
    }

    private func appendGlyphInstance(
        _ glyph: VVTextGlyph,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]]
    ) {
        let layoutVariant = toLayoutFontVariant(glyph.fontVariant)
        let cgGlyph = CGGlyph(glyph.glyphID)

        let cached: MarkdownCachedGlyph?
        if let fontName = glyph.fontName {
            cached = renderer.glyphAtlas.glyph(for: cgGlyph, fontName: fontName, fontSize: glyph.fontSize, variant: layoutVariant)
        } else {
            cached = renderer.glyphAtlas.glyph(for: cgGlyph, variant: layoutVariant, fontSize: glyph.fontSize, baseFont: renderer.baseFont)
        }

        guard let cached else { return }
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

    private func toLayoutFontVariant(_ variant: VVFontVariant) -> MDFontVariant {
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

    // MARK: - Selection Support

    private func viewPointToDocumentPoint(_ point: CGPoint) -> CGPoint {
        let scrollOffset = scrollView.contentView.bounds.origin
        return CGPoint(x: point.x + scrollOffset.x, y: point.y + scrollOffset.y)
    }

    private func findRow(at y: CGFloat, x: CGFloat? = nil) -> RowGeometry? {
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
                    return candidates.first(where: { x >= $0.paneX && x < $0.paneX + $0.paneWidth }) ?? geo
                }
                return geo
            }
        }

        return rowGeometries[low < rowGeometries.count ? low : rowGeometries.count - 1]
    }

    private func invalidateAndRedraw() {
        metalView.setNeedsDisplay(metalView.bounds)
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
            modifiers: event.modifierFlags,
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
        if renderStyle == .split {
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
        guard !rowGeometries.isEmpty else { return }
        let first = DiffTextPosition(rowIndex: 0, charOffset: 0)
        let last = DiffTextPosition(rowIndex: rowGeometries.count - 1, charOffset: rowGeometries.last!.text.count)
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
        if renderStyle == .split {
            geo = findRow(at: docPoint.y, x: docPoint.x)
        } else {
            geo = findRow(at: docPoint.y)
        }
        guard let geo else { return nil }

        // For non-code rows, return position at start of row
        guard geo.isCodeRow else {
            return DiffTextPosition(rowIndex: geo.rowIndex, charOffset: 0, paneX: geo.paneX)
        }

        let dr = ensureDiffRenderer()

        // Convert X to character offset (monospace: relativeX / charWidth)
        let relativeX = docPoint.x - geo.paneX - geo.codeStartX - codeInsetX
        let charOffset = max(0, min(Int(relativeX / dr.charWidth), geo.text.count))

        return DiffTextPosition(rowIndex: geo.rowIndex, charOffset: charOffset, paneX: geo.paneX)
    }
}

// MARK: - VVTextSelectionRenderer

extension VVDiffMetalView: VVTextSelectionRenderer {
    func selectionQuads(from start: DiffTextPosition, to end: DiffTextPosition, color: SIMD4<Float>) -> [VVQuadPrimitive] {
        var quads: [VVQuadPrimitive] = []
        let dr = ensureDiffRenderer()
        let selectionPane = start.paneX

        for geo in rowGeometries {
            guard geo.rowIndex >= start.rowIndex && geo.rowIndex <= end.rowIndex else { continue }

            // In split mode, only select rows within the same pane
            if renderStyle == .split && geo.paneX != selectionPane { continue }

            // For non-code rows (hunk headers, file headers), draw full-width highlight
            guard geo.isCodeRow else {
                // Only fill non-code rows that are fully interior to the selection
                if geo.rowIndex > start.rowIndex && geo.rowIndex < end.rowIndex {
                    let quadPaneX = renderStyle == .split ? selectionPane : geo.paneX
                    let quadPaneW = renderStyle == .split ? geo.paneWidth / 2 : geo.paneWidth
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
                endChar = geo.text.count
                extendToEnd = true
            } else if geo.rowIndex == end.rowIndex {
                startChar = 0
                endChar = end.charOffset
                extendToEnd = false
            } else {
                startChar = 0
                endChar = geo.text.count
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

        for geo in rowGeometries {
            guard geo.rowIndex >= start.rowIndex && geo.rowIndex <= end.rowIndex else { continue }
            // In split mode, only extract text from the same pane
            if renderStyle == .split && geo.paneX != selectionPane { continue }
            guard geo.isCodeRow else { continue }

            let text = geo.text
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
    let renderStyle: VVDiffRenderStyle
    let syntaxHighlightingEnabled: Bool
    let onFileHeaderActivate: ((String) -> Void)?

    func makeCoordinator() -> Coordinator {
        Coordinator()
    }

    final class Coordinator {
        private var lastUnifiedDiff: String?
        private var cachedModel: ParsedDiffModel?

        func model(for unifiedDiff: String) -> ParsedDiffModel {
            if let lastUnifiedDiff, lastUnifiedDiff == unifiedDiff, let cachedModel {
                return cachedModel
            }
            let parsed = parseDiffModel(unifiedDiff: unifiedDiff)
            lastUnifiedDiff = unifiedDiff
            cachedModel = parsed
            return parsed
        }
    }

    func makeNSView(context: Context) -> VVDiffMetalView {
        let view = VVDiffMetalView(frame: .zero)
        let model = context.coordinator.model(for: unifiedDiff)
        view.update(
            unifiedDiff: unifiedDiff,
            analysis: model.analysis,
            rows: model.rows,
            style: renderStyle,
            theme: theme,
            configuration: configuration,
            language: language,
            syntaxHighlightingEnabled: syntaxHighlightingEnabled,
            onFileHeaderActivate: onFileHeaderActivate
        )
        return view
    }

    func updateNSView(_ nsView: VVDiffMetalView, context: Context) {
        let model = context.coordinator.model(for: unifiedDiff)
        nsView.update(
            unifiedDiff: unifiedDiff,
            analysis: model.analysis,
            rows: model.rows,
            style: renderStyle,
            theme: theme,
            configuration: configuration,
            language: language,
            syntaxHighlightingEnabled: syntaxHighlightingEnabled,
            onFileHeaderActivate: onFileHeaderActivate
        )
    }
}

// MARK: - Public API

/// High-level diff component. Parses unified diff text and renders it through Metal.
public struct VVDiffView: View {
    private let unifiedDiff: String
    private var language: VVLanguage?
    private var theme: VVTheme
    private var configuration: VVConfiguration
    private var renderStyle: VVDiffRenderStyle
    private var syntaxHighlightingEnabled: Bool
    private var onFileHeaderActivate: ((String) -> Void)?

    public init(unifiedDiff: String) {
        self.unifiedDiff = unifiedDiff
        self.language = nil
        self.theme = .defaultDark
        self.configuration = .default
        self.renderStyle = .unifiedTable
        self.syntaxHighlightingEnabled = true
        self.onFileHeaderActivate = nil
    }

    public var body: some View {
        VVDiffViewRepresentable(
            unifiedDiff: unifiedDiff,
            language: effectiveLanguage,
            theme: theme,
            configuration: configuration,
            renderStyle: renderStyle,
            syntaxHighlightingEnabled: syntaxHighlightingEnabled,
            onFileHeaderActivate: onFileHeaderActivate
        )
    }

    private var effectiveLanguage: VVLanguage? {
        if let language {
            return language
        }

        for line in unifiedDiff.components(separatedBy: .newlines) where line.hasPrefix("+++ ") {
            let path = line
                .replacingOccurrences(of: "+++ b/", with: "")
                .replacingOccurrences(of: "+++ ", with: "")

            if path == "/dev/null" {
                continue
            }

            let url = URL(fileURLWithPath: path)
            if let detected = VVLanguage.detect(from: url) {
                return detected
            }
        }

        return nil
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

    /// Select unified table or side-by-side split rendering.
    public func renderStyle(_ style: VVDiffRenderStyle) -> VVDiffView {
        var view = self
        view.renderStyle = style
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
