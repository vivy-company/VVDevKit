import Foundation
import AppKit
import MetalKit
import Combine
import VVHighlighting
import SwiftTreeSitter
import VVLSP

/// Metal-based editor container view - replaces VVEditorContainerView for GPU-accelerated rendering
public final class VVMetalEditorContainerView: NSView {

    // MARK: - Properties

    public private(set) var metalTextView: MetalTextView!
    public private(set) var hiddenInputView: HiddenInputView!
    public private(set) var scrollView: NSScrollView!
    private var documentView: MetalDocumentView!

    private var textStorage: String = ""

    // Configuration
    private var _configuration: VVConfiguration
    private var _theme: VVTheme
    private var language: VVLanguage?

    // Cursor and selection state
    private var cursorLine: Int = 0
    private var cursorColumn: Int = 0
    private var selectionRanges: [NSRange] = []
    private var selectionAnchorLine: Int?
    private var selectionAnchorColumn: Int?
    private var selectionAnchorRange: NSRange?
    private var markedTextRange: NSRange?
    private var isComposingMarkedText: Bool = false

    private enum SelectionMode {
        case character
        case word
        case line
    }

    private var selectionMode: SelectionMode = .character

    private enum HelixMode {
        case normal
        case insert
        case select
        case searchForward
        case searchBackward
        case replaceCharacter
    }

    public enum SearchScope {
        case currentFile
        case openDocuments
    }

    private struct Selection {
        var anchor: Int
        var cursor: Int

        var range: NSRange {
            let start = min(anchor, cursor)
            let end = max(anchor, cursor)
            return NSRange(location: start, length: max(0, end - start))
        }
    }

    private struct YankRegister {
        var values: [String] = []
        mutating func clear() { values.removeAll() }
    }

    private var helixModeEnabled: Bool = false
    private var helixMode: HelixMode = .normal {
        didSet { updateModeIndicator() }
    }
    private var selections: [Selection] = [Selection(anchor: 0, cursor: 0)]
    private var primarySelectionIndex: Int = 0
    private var yankRegister = YankRegister()
    private var searchQuery: String = ""
    private var lastSearchQuery: String = ""
    private var lastSearchForward: Bool = true
    private var searchReturnMode: HelixMode?
    private var searchScope: SearchScope = .currentFile
    private var searchOverlayActive: Bool = false
    public var onSearchOpenDocuments: ((String) -> Void)?
    public var onSearchRequest: ((SearchScope) -> Void)?
    public var onRepeatSearchRequest: ((Bool) -> Void)?
    private var lastFindCharacter: Character?
    private var lastFindForward: Bool = true
    private var pendingGCommand = false

    private struct PendingFind {
        var forward: Bool
        var till: Bool
    }
    private var pendingFind: PendingFind?

    private let defaultStatusBarHeight: CGFloat = 22
    private var statusBarHeight: CGFloat { defaultStatusBarHeight }

    // Syntax highlighting
    private var highlighter: TreeSitterHighlighter?
    private var highlightDebouncer: DispatchWorkItem?
    private var highlightTask: Task<Void, Never>?
    private var scrollHighlightDebouncer: DispatchWorkItem?
    private var coloredRanges: [ColoredRange] = []
    private var highlightTheme: VVHighlighting.HighlightTheme = .defaultDark
    private var isSettingUpHighlighter = false
    private var preserveHighlightsDuringRehighlight = false
    private var suppressHighlightUpdates = false
    private var didPreloadGlyphs = false
    private var previousText: String = ""
    private var lastEditRange: NSRange?
    private var lastReplacementLength: Int = 0
    private var lastHighlightedRange: NSRange?
    private var dirtyHighlightRange: NSRange?
    private var lastParsedText: String?
    private var textRevision: Int = 0
    private var searchCache: (query: String, caseSensitive: Bool, token: Int, matches: [NSRange])?
    private let searchMatchLimit: Int = 20_000
    private var searchOptions = SearchEngine.Options(caseSensitive: true)

    // LSP / Completion
    private var lspClient: (any VVLSPClient)?
    private var documentURI: String?
    private var completionItems: [VVCompletionItem] = []
    private var filteredCompletionItems: [VVCompletionItem] = []
    private var completionAnchorOffset: Int = 0
    private var completionCursorOffset: Int = 0
    private var completionSelectedIndex: Int = 0
    private var completionDebounceTimer: Timer?
    private let immediateTriggerCharacters: Set<Character> = [".", "(", "<", ":", "/", "@", "\"", "'"]
    private let delayedTriggerCharacters = CharacterSet.alphanumerics.union(CharacterSet(charactersIn: "_"))

    // Git blame
    private var blameInfo: [VVBlameInfo] = []

    // Line map for position calculations
    private var lineMap: LineMap?

    // Folding / indentation guides
    private struct FoldRange: Hashable {
        let startLine: Int
        let endLine: Int
        let indentColumn: Int
    }

    private var foldableRanges: [FoldRange] = []
    private var foldedStartLines: Set<Int> = []
    private var foldedRanges: [ClosedRange<Int>] = []
    private var indentGuideSegments: [MetalTextView.IndentGuideSegment] = []

    // Cancellables
    private var cancellables = Set<AnyCancellable>()
    private var lastVisibleLineRange: ClosedRange<Int>?

    // Delegate
    public weak var delegate: VVEditorDelegate?

    // Public callbacks
    public var onTextChange: ((String) -> Void)?
    public var onSelectionChange: (([NSRange]) -> Void)?
    public var onCursorChange: ((Int, Int) -> Void)?
    public var onVisibleLineRangeChange: ((ClosedRange<Int>) -> Void)?

    // Callbacks (internal use)
    private var onTextChangeInternal: ((String) -> Void)?
    private var onSelectionChangeInternal: (([NSRange]) -> Void)?
    private var onCursorChangeInternal: ((Int, Int) -> Void)?

    // MARK: - Initialization

    public var metalContext: VVMetalContext?

    public init(frame: CGRect, configuration: VVConfiguration, theme: VVTheme, metalContext: VVMetalContext? = nil) {
        self._configuration = configuration
        self._theme = theme
        self.metalContext = metalContext ?? VVMetalContext.shared
        super.init(frame: frame)
        setupViews()
        applyConfiguration()
        applyTheme()
    }

    required init?(coder: NSCoder) {
        self._configuration = VVConfiguration()
        self._theme = VVTheme.defaultDark
        self.metalContext = VVMetalContext.shared
        super.init(coder: coder)
        setupViews()
        applyConfiguration()
        applyTheme()
    }

    deinit {
        highlightDebouncer?.cancel()
        highlightDebouncer = nil
        highlightTask?.cancel()
        highlightTask = nil
        scrollHighlightDebouncer?.cancel()
        scrollHighlightDebouncer = nil
        cancellables.removeAll()
        metalTextView?.textDelegate = nil
        hiddenInputView?.inputDelegate = nil
        hiddenInputView?.metalTextView = nil
        scrollView?.documentView = nil
    }

    private func setupViews() {
        guard let device = metalContext?.device ?? MTLCreateSystemDefaultDevice() else {
            fatalError("Metal is not supported on this device")
        }

        // Create Metal text view
        metalTextView = MetalTextView(
            frame: bounds,
            device: device,
            font: _configuration.font,
            metalContext: metalContext
        )
        metalTextView.onContentSizeChange = { [weak self] in
            self?.updateContentSize()
        }

        // Create document view wrapper (keeps scroll size without sizing MTKView)
        documentView = MetalDocumentView(frame: bounds)

        // Create scroll view
        scrollView = NSScrollView(frame: bounds)
        scrollView.documentView = documentView
        scrollView.hasVerticalScroller = true
        scrollView.hasHorizontalScroller = true
        scrollView.autohidesScrollers = true
        scrollView.drawsBackground = false
        scrollView.contentView.postsBoundsChangedNotifications = true

        // Create hidden input view
        hiddenInputView = HiddenInputView()
        hiddenInputView.inputDelegate = self
        hiddenInputView.metalTextView = metalTextView
        hiddenInputView.textProvider = { [weak self] in
            self?.textStorage ?? ""
        }
        hiddenInputView.selectedRangeProvider = { [weak self] in
            if let range = self?.selectionRanges.first {
                return range
            }
            let length = self?.currentTextLengthUTF16() ?? 0
            return NSRange(location: length, length: 0)
        }
        hiddenInputView.markedRangeProvider = { [weak self] in
            self?.markedTextRange
        }

        // Set delegate for mouse events
        metalTextView.textDelegate = self
        metalTextView.onToggleFold = { [weak self] line in
            self?.toggleFold(atLine: line)
        }
        metalTextView.menu = buildContextMenu()

        // Add subviews
        addSubview(scrollView)
        scrollView.addSubview(metalTextView)
        addSubview(hiddenInputView)

        // Setup scroll observation
        NotificationCenter.default.publisher(for: NSView.boundsDidChangeNotification, object: scrollView.contentView)
            .sink { [weak self] _ in
                self?.handleScroll()
            }
            .store(in: &cancellables)

        setupStatusBar()
        updateHelixUI()
    }

    // MARK: - Layout

    override public func layout() {
        super.layout()
        scrollView.frame = bounds
        updateContentSize()
    }

    override public func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        if window != nil {
            DispatchQueue.main.async { [weak self] in
                self?.focusTextView()
            }
        }
    }

    override public func viewDidChangeBackingProperties() {
        super.viewDidChangeBackingProperties()
        updateContentSize()
    }

    // MARK: - First Responder

    override public var acceptsFirstResponder: Bool { true }

    override public func becomeFirstResponder() -> Bool {
        window?.makeFirstResponder(hiddenInputView)
        return true
    }

    // MARK: - Public API

    /// Set the text content
    public func setText(_ text: String, applyHighlighting: Bool = true) {
        let normalized = normalizeLineEndings(text)
        let textChanged = normalized != textStorage
        textStorage = normalized
        textRevision &+= 1
        searchCache = nil
        metalTextView.setSearchMatchRanges([])
        metalTextView.setActiveSearchMatch(nil)
        if lastEditRange == nil {
            previousText = textStorage
        }
        if textChanged {
            lastParsedText = nil
        }
        lineMap = LineMap(text: textStorage)
        metalTextView.setText(textStorage)
        recomputeFolding()

        if applyHighlighting {
            if textChanged && !preserveHighlightsDuringRehighlight {
                preserveHighlightsDuringRehighlight = false
                coloredRanges = []
                metalTextView.setHighlights([])
                lastHighlightedRange = nil
                dirtyHighlightRange = nil
            }
            highlightSyntax()
        }
        updateContentSize()
        updateSelectionsDisplay()
    }

    /// Get the text content
    public var text: String {
        textStorage
    }

    /// Select a UTF-16 range and optionally scroll it into view.
    public func selectRange(_ range: NSRange, scrollToVisible: Bool = true) {
        let clamped = clampRangeToDocument(range)
        applySelection(clamped)
        if scrollToVisible {
            scrollToRange(clamped)
        }
    }

    public func findMatches(query: String, limit: Int? = nil) -> [NSRange] {
        guard !query.isEmpty else { return [] }
        let matches = searchMatches(for: query, options: searchOptions)
        if let limit, matches.count > limit {
            return Array(matches.prefix(limit))
        }
        return matches
    }

    public func findNextMatch(query: String, forward: Bool) -> NSRange? {
        guard !query.isEmpty else { return nil }
        let matches = searchMatches(for: query, options: searchOptions)
        guard !matches.isEmpty else { return nil }
        let cursor = selections.first?.cursor ?? 0
        let match = nextMatch(from: cursor, forward: forward, matches: matches)
        metalTextView?.setSearchMatchRanges(matches)
        metalTextView?.setActiveSearchMatch(match)
        return match
    }

    public func matchCount(query: String) -> Int {
        guard !query.isEmpty else { return 0 }
        return searchMatches(for: query, options: searchOptions).count
    }

    @discardableResult
    public func setSearchHighlights(query: String) -> Int {
        let trimmed = query.trimmingCharacters(in: .whitespacesAndNewlines)
        guard !trimmed.isEmpty else {
            metalTextView?.setSearchMatchRanges([])
            metalTextView?.setActiveSearchMatch(nil)
            return 0
        }
        let matches = searchMatches(for: trimmed, options: searchOptions)
        metalTextView?.setSearchMatchRanges(matches)
        let cursor = selections.first?.cursor ?? 0
        let active = nextMatch(from: cursor, forward: true, matches: matches)
        metalTextView?.setActiveSearchMatch(active)
        return matches.count
    }

    public func setActiveSearchMatch(_ range: NSRange?) {
        metalTextView?.setActiveSearchMatch(range)
    }

    public func clearSearchHighlights() {
        metalTextView?.setSearchMatchRanges([])
        metalTextView?.setActiveSearchMatch(nil)
    }

    public func setSearchOptions(_ options: SearchEngine.Options) {
        searchOptions = options
        searchCache = nil
        updateSearchOverlay()
    }

    private func buildContextMenu() -> NSMenu {
        let menu = NSMenu()
        menu.autoenablesItems = true

        let cutItem = NSMenuItem(title: "Cut", action: #selector(NSText.cut(_:)), keyEquivalent: "")
        let copyItem = NSMenuItem(title: "Copy", action: #selector(NSText.copy(_:)), keyEquivalent: "")
        let pasteItem = NSMenuItem(title: "Paste", action: #selector(NSText.paste(_:)), keyEquivalent: "")
        let selectAllItem = NSMenuItem(title: "Select All", action: #selector(NSText.selectAll(_:)), keyEquivalent: "")

        [cutItem, copyItem, pasteItem, selectAllItem].forEach { item in
            item.target = hiddenInputView
        }

        menu.addItem(cutItem)
        menu.addItem(copyItem)
        menu.addItem(pasteItem)
        menu.addItem(.separator())
        menu.addItem(selectAllItem)

        return menu
    }

    /// Set syntax highlighter
    public func setHighlighter(_ highlighter: TreeSitterHighlighter?) {
        setHighlighter(highlighter, textIsSynced: false)
    }

    /// Set syntax highlighter with optional reuse of existing parse tree.
    public func setHighlighter(_ highlighter: TreeSitterHighlighter?, textIsSynced: Bool) {
        self.highlighter = highlighter
        if textIsSynced {
            previousText = textStorage
            lastParsedText = textStorage
            lastEditRange = nil
            preserveHighlightsDuringRehighlight = false
            lastHighlightedRange = nil
            highlightVisibleRangeOnly()
        } else {
            lastParsedText = nil
            highlightSyntax()
        }
    }

    /// Current syntax highlighter instance.
    public var currentHighlighter: TreeSitterHighlighter? {
        highlighter
    }

    /// Snapshot current syntax highlighting ranges.
    public func currentHighlightRanges() -> [ColoredRange] {
        coloredRanges
    }

    /// Restore cached syntax highlighting ranges without clearing while re-highlighting.
    public func restoreHighlightRanges(_ ranges: [ColoredRange]) {
        coloredRanges = ranges
        metalTextView.setHighlights(ranges)
        preserveHighlightsDuringRehighlight = true
        lastHighlightedRange = nil
    }

    /// Trigger highlighting while optionally preserving current highlights until new ones are ready.
    public func refreshHighlighting(preservingCurrent: Bool) {
        preserveHighlightsDuringRehighlight = preservingCurrent
        highlightSyntax()
    }

    /// Set git hunks for gutter display
    public func setGitHunks(_ hunks: [MetalGutterGitHunk]) {
        metalTextView.setGitHunks(hunks)
    }

    /// Set rich diff overlays for in-content hunk visualization.
    public func setDiffOverlayHunks(_ hunks: [MetalDiffOverlayHunk]) {
        metalTextView.setDiffOverlayHunks(hunks)
    }

    /// Enable or disable drawing diff overlay callouts.
    public func setShowsDiffOverlayHunks(_ show: Bool) {
        metalTextView?.setShowsDiffOverlayHunks(show)
    }

    // MARK: - Cursor and Selection

    private func setCursor(line: Int, column: Int) {
        let clampedLine = max(0, min(line, max(0, (lineMap?.lineCount ?? 1) - 1)))
        let maxColumn = lineLengthUTF16(forLine: clampedLine)
        let clampedColumn = max(0, min(column, maxColumn))
        let offset = lineMapOffset(forLine: clampedLine) + clampedColumn
        if selections.isEmpty {
            selections = [Selection(anchor: offset, cursor: offset)]
            primarySelectionIndex = 0
        } else {
            let index = max(0, min(primarySelectionIndex, selections.count - 1))
            selections[index].anchor = offset
            selections[index].cursor = offset
        }
        updateSelectionsDisplay()
    }

    private func updateSelection(toLine line: Int, column: Int, updateCursor: Bool = true) {
        guard lineMap != nil else { return }

        let anchorLine = selectionAnchorLine ?? cursorLine
        let anchorColumn = selectionAnchorColumn ?? cursorColumn

        let startOffset = lineMapOffset(forLine: anchorLine) + anchorColumn
        let endOffset = lineMapOffset(forLine: line) + column
        let index = max(0, min(primarySelectionIndex, selections.count - 1))
        if selections.isEmpty {
            selections = [Selection(anchor: startOffset, cursor: endOffset)]
            primarySelectionIndex = 0
        } else {
            selections[index].anchor = startOffset
            selections[index].cursor = endOffset
        }
        updateSelectionsDisplay()

        if updateCursor {
            cursorLine = line
            cursorColumn = column
        }
    }

    private func setSelectionAnchor(line: Int, column: Int) {
        selectionAnchorLine = line
        selectionAnchorColumn = column
    }

    private func clearSelectionAnchor() {
        selectionAnchorLine = nil
        selectionAnchorColumn = nil
    }

    private func normalizeLineEndings(_ text: String) -> String {
        text.replacingOccurrences(of: "\r\n", with: "\n").replacingOccurrences(of: "\r", with: "\n")
    }

    private func currentTextLengthUTF16() -> Int {
        (textStorage as NSString).length
    }

    private func normalizeSelections() {
        let textLength = currentTextLengthUTF16()
        var ranges = selections.map { selection -> NSRange in
            let anchor = max(0, min(selection.anchor, textLength))
            let cursor = max(0, min(selection.cursor, textLength))
            let start = min(anchor, cursor)
            let end = max(anchor, cursor)
            return NSRange(location: start, length: max(0, end - start))
        }

        ranges.sort { lhs, rhs in
            if lhs.location != rhs.location { return lhs.location < rhs.location }
            return lhs.length < rhs.length
        }

        var merged: [NSRange] = []
        for range in ranges {
            if let last = merged.last, range.location <= last.location + last.length {
                let end = max(last.location + last.length, range.location + range.length)
                merged[merged.count - 1] = NSRange(location: last.location, length: end - last.location)
            } else {
                merged.append(range)
            }
        }

        selections = merged.map { range in
            Selection(anchor: range.location, cursor: range.location + range.length)
        }

        if selections.isEmpty {
            selections = [Selection(anchor: 0, cursor: 0)]
            primarySelectionIndex = 0
        } else {
            primarySelectionIndex = max(0, min(primarySelectionIndex, selections.count - 1))
        }
    }

    private func updateSelectionsDisplay() {
        normalizeSelections()
        selectionRanges = selections.map { $0.range }
        metalTextView.setSelection(selectionRanges)
        metalTextView.setSelectedLineRanges(selectionLineRanges(from: selectionRanges))
        if let hiddenInputView, !selectionRanges.isEmpty {
            let primary = max(0, min(primarySelectionIndex, selectionRanges.count - 1))
            hiddenInputView.selectedRange = selectionRanges[primary]
        }

        let cursorPositions = selections.map { selection -> (line: Int, column: Int) in
            lineMapPosition(forOffset: selection.cursor)
        }

        if !cursorPositions.isEmpty {
            let primary = max(0, min(primarySelectionIndex, cursorPositions.count - 1))
            let primaryPos = cursorPositions[primary]
            cursorLine = primaryPos.line
            cursorColumn = primaryPos.column
            metalTextView.setCursors(cursorPositions, primaryIndex: primary)
            metalTextView.setCurrentLineNumber(primaryPos.line)
            delegate?.editorDidChangeCursorPosition(VVTextPosition(line: primaryPos.line, character: primaryPos.column))
        }
        updateBracketHighlight()
        updateActiveIndentGuides()
        updateStatusBar()
        updateSearchOverlay()
    }

    private func applySelection(_ range: NSRange, updateAnchor: Bool = true) {
        let nsText = textStorage as NSString
        guard nsText.length > 0 else { return }
        let safeLocation = max(0, min(range.location, nsText.length))
        let safeLength = min(range.length, max(0, nsText.length - safeLocation))
        let safeRange = NSRange(location: safeLocation, length: safeLength)

        selections = [Selection(anchor: safeRange.location, cursor: safeRange.location + safeRange.length)]
        primarySelectionIndex = 0
        selectionRanges = [safeRange]
        metalTextView.setSelection(selectionRanges)
        hiddenInputView?.selectedRange = safeRange
        delegate?.editorDidChangeSelection(safeRange)

        if updateAnchor {
            let startPos = lineMapPosition(forOffset: safeRange.location)
            setSelectionAnchor(line: startPos.line, column: startPos.column)
            selectionAnchorRange = safeRange
        }

        let endOffset = safeRange.location + safeRange.length
        let endPos = lineMapPosition(forOffset: endOffset)
        cursorLine = endPos.line
        cursorColumn = endPos.column
        metalTextView.setCursor(line: endPos.line, column: endPos.column)
        updateBracketHighlight()
        updateStatusBar()
    }

    private func updateBracketHighlight() {
        let nsText = textStorage as NSString
        let length = nsText.length
        guard length > 0 else {
            metalTextView?.setBracketMatchRanges([])
            return
        }

        guard !selections.isEmpty else {
            metalTextView?.setBracketMatchRanges([])
            return
        }

        let primary = selections[max(0, min(primarySelectionIndex, selections.count - 1))]
        if primary.range.length > 0 {
            metalTextView?.setBracketMatchRanges([])
            return
        }

        let cursor = max(0, min(primary.cursor, length))
        let pairs: [unichar: (match: unichar, forward: Bool)] = [
            40: (41, true),   // (
            91: (93, true),   // [
            123: (125, true), // {
            41: (40, false),  // )
            93: (91, false),  // ]
            125: (123, false) // }
        ]

        let candidateOffsets = [cursor, cursor - 1]
        for candidate in candidateOffsets {
            if candidate < 0 || candidate >= length { continue }
            let ch = nsText.character(at: candidate)
            guard let pair = pairs[ch] else { continue }
            if let match = findMatchingBracket(from: candidate, char: ch, match: pair.match, forward: pair.forward, in: nsText) {
                metalTextView?.setBracketMatchRanges([
                    NSRange(location: candidate, length: 1),
                    NSRange(location: match, length: 1)
                ])
                return
            }
        }

        metalTextView?.setBracketMatchRanges([])
    }

    private func findMatchingBracket(from offset: Int, char: unichar, match: unichar, forward: Bool, in text: NSString) -> Int? {
        let length = text.length
        var depth = 0
        if forward {
            var i = offset
            while i < length {
                let c = text.character(at: i)
                if c == char { depth += 1 }
                if c == match { depth -= 1 }
                if depth == 0 { return i }
                i += 1
            }
        } else {
            var i = offset
            while true {
                let c = text.character(at: i)
                if c == char { depth += 1 }
                if c == match { depth -= 1 }
                if depth == 0 { return i }
                if i == 0 { break }
                i -= 1
            }
        }
        return nil
    }

    private func isWordCharacter(_ value: unichar) -> Bool {
        if value == 95 { return true } // "_"
        if let scalar = UnicodeScalar(value) {
            return CharacterSet.alphanumerics.contains(scalar)
        }
        return false
    }

    private func isWhitespaceCharacter(_ value: unichar) -> Bool {
        if let scalar = UnicodeScalar(value) {
            return CharacterSet.whitespaces.contains(scalar)
        }
        return false
    }

    private enum CharClass {
        case whitespace
        case word
        case punctuation
        case other
    }

    private func classifyCharacter(_ value: unichar) -> CharClass {
        if value == 10 { return .whitespace } // "\n"
        if isWhitespaceCharacter(value) { return .whitespace }
        if isWordCharacter(value) { return .word }
        if isPunctuationCharacter(value) { return .punctuation }
        return .other
    }

    private func isPunctuationCharacter(_ value: unichar) -> Bool {
        if value == 10 { return false } // "\n"
        if isWhitespaceCharacter(value) { return false }
        if isWordCharacter(value) { return false }
        if let scalar = UnicodeScalar(value) {
            return CharacterSet.punctuationCharacters.contains(scalar) ||
                CharacterSet.symbols.contains(scalar)
        }
        return false
    }

    private func wordRange(atLine line: Int, column: Int) -> NSRange? {
        let nsText = textStorage as NSString
        let length = nsText.length
        guard length > 0 else { return nil }

        let lineStart = lineMapOffset(forLine: line)
        let lineRange = lineMapRange(forLine: line)
        let lineEnd = min(length, lineRange.start + lineRange.length)
        let lineEndNoNewline = (lineEnd > lineStart && nsText.character(at: lineEnd - 1) == 10) ? lineEnd - 1 : lineEnd

        let offset = min(max(lineStart + column, lineStart), max(lineStart, lineEnd - 1))
        var index = min(max(offset, 0), length - 1)

        // If we're exactly on a newline, prefer the previous character.
        if nsText.character(at: index) == 10 && index > 0 {
            index -= 1
        }

        let value = nsText.character(at: index)
        if isWhitespaceCharacter(value) {
            var start = index
            while start > lineStart && isWhitespaceCharacter(nsText.character(at: start - 1)) {
                start -= 1
            }

            var end = index + 1
            while end < lineEndNoNewline && isWhitespaceCharacter(nsText.character(at: end)) {
                end += 1
            }

            return NSRange(location: start, length: max(1, end - start))
        }

        if isWordCharacter(value) {
            var start = index
            while start > lineStart && isWordCharacter(nsText.character(at: start - 1)) {
                start -= 1
            }

            var end = index
            while end < lineEndNoNewline && isWordCharacter(nsText.character(at: end)) {
                end += 1
            }

            return NSRange(location: start, length: max(0, end - start))
        }

        if isPunctuationCharacter(value) {
            var start = index
            while start > lineStart && isPunctuationCharacter(nsText.character(at: start - 1)) {
                start -= 1
            }

            var end = index
            while end < lineEndNoNewline && isPunctuationCharacter(nsText.character(at: end)) {
                end += 1
            }

            return NSRange(location: start, length: max(0, end - start))
        }

        return NSRange(location: index, length: 1)
    }

    private func lineRange(for line: Int) -> NSRange? {
        guard lineMap != nil else { return nil }
        let range = lineMapRange(forLine: line)
        return NSRange(location: range.start, length: range.length)
    }

    private func unionRange(_ a: NSRange, _ b: NSRange) -> NSRange {
        let start = min(a.location, b.location)
        let end = max(a.location + a.length, b.location + b.length)
        return NSRange(location: start, length: max(0, end - start))
    }

    private func nextWordOffset(from offset: Int, treatPunctuationAsWord: Bool) -> Int {
        let nsText = textStorage as NSString
        let length = nsText.length
        if length == 0 { return 0 }
        var index = max(0, min(offset, length))
        if index >= length { return length }

        let currentClass = classifyCharacter(nsText.character(at: index))
        let isWhitespace = currentClass == .whitespace
        if isWhitespace {
            while index < length && classifyCharacter(nsText.character(at: index)) == .whitespace {
                index += 1
            }
            return index
        }

        let skipClass: CharClass = {
            switch currentClass {
            case .word: return .word
            case .punctuation:
                return treatPunctuationAsWord ? .word : .punctuation
            default:
                return currentClass
            }
        }()

        while index < length {
            let cls = classifyCharacter(nsText.character(at: index))
            if cls == .whitespace { break }
            if skipClass == .word {
                if cls != .word && (treatPunctuationAsWord ? cls != .punctuation : true) { break }
            } else if cls != skipClass {
                break
            }
            index += 1
        }

        while index < length && classifyCharacter(nsText.character(at: index)) == .whitespace {
            index += 1
        }

        return index
    }

    private func previousWordOffset(from offset: Int, treatPunctuationAsWord: Bool) -> Int {
        let nsText = textStorage as NSString
        let length = nsText.length
        if length == 0 { return 0 }
        var index = max(0, min(offset, length))
        if index == 0 { return 0 }
        index -= 1

        while index > 0 && classifyCharacter(nsText.character(at: index)) == .whitespace {
            index -= 1
        }

        let currentClass = classifyCharacter(nsText.character(at: index))
        let isWordLike = currentClass == .word || (treatPunctuationAsWord && currentClass == .punctuation)

        if isWordLike {
            while index > 0 {
                let cls = classifyCharacter(nsText.character(at: index - 1))
                if cls == .word || (treatPunctuationAsWord && cls == .punctuation) {
                    index -= 1
                } else {
                    break
                }
            }
        } else if currentClass == .punctuation {
            while index > 0 && classifyCharacter(nsText.character(at: index - 1)) == .punctuation {
                index -= 1
            }
        }

        return index
    }

    private func endOfWordOffset(from offset: Int, treatPunctuationAsWord: Bool) -> Int {
        let nsText = textStorage as NSString
        let length = nsText.length
        if length == 0 { return 0 }
        var index = max(0, min(offset, length))
        if index >= length { return max(0, length - 1) }

        var cls = classifyCharacter(nsText.character(at: index))
        if cls == .whitespace {
            while index < length && classifyCharacter(nsText.character(at: index)) == .whitespace {
                index += 1
            }
            if index >= length { return max(0, length - 1) }
            cls = classifyCharacter(nsText.character(at: index))
        }

        let isWordLike = cls == .word || (treatPunctuationAsWord && cls == .punctuation)
        while index < length {
            let current = classifyCharacter(nsText.character(at: index))
            if current == .whitespace { break }
            if isWordLike {
                if current != .word && !(treatPunctuationAsWord && current == .punctuation) { break }
            } else if current != cls {
                break
            }
            index += 1
        }

        return max(0, min(length - 1, index - 1))
    }

    private func firstNonWhitespaceColumn(inLine line: Int) -> Int {
        let nsText = textStorage as NSString
        let range = lineMapRange(forLine: line)
        let end = range.start + range.length
        var offset = range.start
        while offset < end {
            let value = nsText.character(at: offset)
            if !isWhitespaceCharacter(value) && value != 10 {
                return offset - range.start
            }
            offset += 1
        }
        return 0
    }

    private func lineEndColumn(for line: Int) -> Int {
        lineLengthUTF16(forLine: line)
    }

    private func findCharacterInLine(from offset: Int, character: Character, forward: Bool, till: Bool) -> Int? {
        let nsText = textStorage as NSString
        let length = nsText.length
        guard length > 0 else { return nil }

        let pos = lineMapPosition(forOffset: offset)
        let lineStart = lineMapOffset(forLine: pos.line)
        let lineLength = lineLengthUTF16(forLine: pos.line)
        let lineEnd = lineStart + lineLength

        let charString = String(character)
        if forward {
            let start = min(offset + 1, lineEnd)
            if start >= lineEnd { return nil }
            let searchRange = NSRange(location: start, length: lineEnd - start)
            let found = nsText.range(of: charString, options: [], range: searchRange)
            guard found.location != NSNotFound else { return nil }
            return till ? max(lineStart, found.location - 1) : found.location
        } else {
            let start = max(lineStart, offset - 1)
            if start < lineStart { return nil }
            let searchRange = NSRange(location: lineStart, length: start - lineStart + 1)
            let found = nsText.range(of: charString, options: [.backwards], range: searchRange)
            guard found.location != NSNotFound else { return nil }
            return till ? min(lineEnd, found.location + 1) : found.location
        }
    }

    private func applyFind(character: Character, forward: Bool, till: Bool, extendSelection: Bool) {
        applyMotion(extendSelection: extendSelection) { selection in
            if let found = findCharacterInLine(from: selection.cursor, character: character, forward: forward, till: till) {
                return found
            }
            return selection.cursor
        }
    }

    private func applySearch(query: String, forward: Bool, extendSelection: Bool) {
        guard !query.isEmpty else { return }
        let matches = searchMatches(for: query, options: searchOptions)
        metalTextView?.setSearchMatchRanges(matches)
        guard !matches.isEmpty else {
            metalTextView?.setActiveSearchMatch(nil)
            NSSound.beep()
            return
        }

        let sorted = selections.enumerated().map { ($0.offset, $0.element) }
        var updated: [Selection] = selections

        for (index, selection) in sorted {
            let match = nextMatch(
                from: selection.cursor,
                forward: forward,
                matches: matches
            ) ?? matches.first

            guard let found = match else { continue }
            let cursor = found.location + found.length
            let anchor = extendSelection ? selection.anchor : found.location
            updated[index] = Selection(anchor: anchor, cursor: cursor)

            if index == primarySelectionIndex {
                metalTextView?.setActiveSearchMatch(found)
            }
        }

        selections = updated
        updateSelectionsDisplay()
    }

    private func beginSearchOverlay(scope: SearchScope, forward: Bool) {
        searchOverlayActive = true
        searchScope = scope
        if searchQuery.isEmpty {
            searchQuery = lastSearchQuery
        }
        lastSearchForward = forward
        updateSearchHighlightsForOverlay()
        updateSearchOverlay()
        window?.makeFirstResponder(hiddenInputView)
    }

    private func endSearchOverlay() {
        searchOverlayActive = false
        searchQuery = ""
        searchScope = .currentFile
        clearSearchHighlights()
        updateSearchOverlay()
    }

    private func updateSearchHighlightsForOverlay() {
        let trimmed = searchQuery.trimmingCharacters(in: .whitespacesAndNewlines)
        if trimmed.isEmpty {
            clearSearchHighlights()
            return
        }
        if searchScope == .currentFile {
            _ = setSearchHighlights(query: trimmed)
        } else {
            clearSearchHighlights()
        }
    }

    private func performOverlaySearch(forward: Bool) {
        let trimmed = searchQuery.trimmingCharacters(in: .whitespacesAndNewlines)
        guard !trimmed.isEmpty else {
            NSSound.beep()
            return
        }
        lastSearchQuery = trimmed
        lastSearchForward = forward

        if searchScope == .openDocuments {
            onSearchOpenDocuments?(trimmed)
            if onSearchOpenDocuments == nil {
                applySearch(query: trimmed, forward: forward, extendSelection: false)
            }
        } else {
            applySearch(query: trimmed, forward: forward, extendSelection: false)
        }

        updateSearchOverlay()
    }

    private func handleSearchOverlayKeyDown(_ event: NSEvent) -> Bool {
        if event.modifierFlags.contains(.command) {
            return false
        }

        if event.keyCode == 53 { // Esc
            endSearchOverlay()
            return true
        }

        if event.keyCode == 36 { // Return
            let forward = !event.modifierFlags.contains(.shift)
            performOverlaySearch(forward: forward)
            return true
        }

        if event.keyCode == 51 { // Backspace
            if !searchQuery.isEmpty {
                searchQuery.removeLast()
                updateSearchHighlightsForOverlay()
                updateSearchOverlay()
            }
            return true
        }

        if let chars = event.characters, !chars.isEmpty {
            searchQuery.append(chars)
            updateSearchHighlightsForOverlay()
            updateSearchOverlay()
            return true
        }

        return true
    }

    private func selectionRangesForOperation(expandEmptyToChar: Bool) -> [(range: NSRange, index: Int)] {
        let textLength = currentTextLengthUTF16()
        var result: [(NSRange, Int)] = []

        for (idx, selection) in selections.enumerated() {
            var range = selection.range
            if range.length == 0 && expandEmptyToChar {
                if selection.cursor < textLength {
                    range = NSRange(location: selection.cursor, length: 1)
                } else if selection.cursor > 0 {
                    range = NSRange(location: selection.cursor - 1, length: 1)
                }
            }
            if range.location + range.length <= textLength {
                result.append((range, idx))
            }
        }

        return result
    }

    private func searchMatches(for query: String, options: SearchEngine.Options) -> [NSRange] {
        if let cache = searchCache,
           cache.query == query,
           cache.caseSensitive == options.caseSensitive,
           cache.token == textRevision {
            return cache.matches
        }

        let matches = SearchEngine.findAllMatches(
            in: textStorage,
            query: query,
            options: options,
            limit: searchMatchLimit
        )
        searchCache = (query: query, caseSensitive: options.caseSensitive, token: textRevision, matches: matches)
        return matches
    }

    private func nextMatch(from cursor: Int, forward: Bool, matches: [NSRange]) -> NSRange? {
        guard !matches.isEmpty else { return nil }
        if forward {
            let target = cursor + 1
            if let idx = firstMatchIndex(atOrAfter: target, matches: matches) {
                return matches[idx]
            }
            return matches.first
        } else {
            let target = cursor - 1
            if let idx = lastMatchIndex(atOrBefore: target, matches: matches) {
                return matches[idx]
            }
            return matches.last
        }
    }

    private func firstMatchIndex(atOrAfter offset: Int, matches: [NSRange]) -> Int? {
        var low = 0
        var high = matches.count - 1
        var result: Int? = nil
        while low <= high {
            let mid = (low + high) / 2
            if matches[mid].location >= offset {
                result = mid
                high = mid - 1
            } else {
                low = mid + 1
            }
        }
        return result
    }

    private func matchIndex(for offset: Int, matches: [NSRange]) -> Int? {
        guard !matches.isEmpty else { return nil }
        if let idx = firstMatchIndex(atOrAfter: offset, matches: matches) {
            let match = matches[idx]
            if offset >= match.location && offset <= match.location + match.length {
                return idx
            }
            return idx
        }
        return matches.indices.last
    }

    private func lastMatchIndex(atOrBefore offset: Int, matches: [NSRange]) -> Int? {
        var low = 0
        var high = matches.count - 1
        var result: Int? = nil
        while low <= high {
            let mid = (low + high) / 2
            if matches[mid].location <= offset {
                result = mid
                low = mid + 1
            } else {
                high = mid - 1
            }
        }
        return result
    }

    private func replaceSelections(with text: String, expandEmptyToChar: Bool) {
        let nsText = NSMutableString(string: textStorage)
        let normalized = normalizeLineEndings(text)
        ensureGlyphPreloadIfNeeded(with: normalized)
        let insertLength = (normalized as NSString).length
        let ranges = selectionRangesForOperation(expandEmptyToChar: expandEmptyToChar)

        if ranges.isEmpty {
            return
        }

        previousText = textStorage
        lastHighlightedRange = nil
        preserveHighlightsDuringRehighlight = true

        suppressHighlightUpdates = true
        defer { suppressHighlightUpdates = false }

        if ranges.count == 1 {
            lastEditRange = ranges[0].range
            lastReplacementLength = insertLength
            markDirtyHighlight(range: dirtyRange(for: ranges[0].range, replacementLength: insertLength))
            applyHighlightEdit(range: ranges[0].range, replacementLength: insertLength)
        } else {
            lastEditRange = nil
            lastReplacementLength = 0
            for edit in ranges {
                markDirtyHighlight(range: dirtyRange(for: edit.range, replacementLength: insertLength))
            }
            let sortedEdits = ranges.map { ($0.range, insertLength) }
                .sorted { lhs, rhs in
                    if lhs.0.location != rhs.0.location { return lhs.0.location > rhs.0.location }
                    return lhs.0.length > rhs.0.length
                }
            for edit in sortedEdits {
                applyHighlightEdit(range: edit.0, replacementLength: edit.1)
            }
        }

        let sorted = ranges.sorted { lhs, rhs in
            if lhs.range.location != rhs.range.location { return lhs.range.location > rhs.range.location }
            return lhs.range.length > rhs.range.length
        }

        var newOffsets: [Int] = Array(repeating: 0, count: selections.count)
        for (range, index) in sorted {
            nsText.replaceCharacters(in: range, with: normalized)
            newOffsets[index] = range.location + insertLength
        }

        selections = newOffsets.map { Selection(anchor: $0, cursor: $0) }
        primarySelectionIndex = max(0, min(primarySelectionIndex, selections.count - 1))

        let newText = nsText as String
        textStorage = newText
        textRevision &+= 1
        searchCache = nil
        metalTextView?.setSearchMatchRanges([])
        metalTextView?.setActiveSearchMatch(nil)
        lineMap = LineMap(text: textStorage)

        if ranges.count == 1 {
            metalTextView.applyEdit(range: ranges[0].range, replacement: normalized)
        } else {
            metalTextView.setText(newText)
        }

        recomputeFolding()

        if let dirtyRange = dirtyHighlightRange {
            metalTextView.setHighlights(coloredRanges, invalidating: dirtyRange)
        } else {
            metalTextView.setHighlights(coloredRanges)
        }

        highlightSyntax()
        updateContentSize()
        updateSelectionsDisplay()
        notifyLSPDocumentChanged()
        updateCompletionFilter()
        notifyTextDidChange()
    }

    private func applyMotion(extendSelection: Bool, _ transform: (Selection) -> Int) {
        let textLength = currentTextLengthUTF16()
        for index in selections.indices {
            let selection = selections[index]
            var newCursor = transform(selection)
            newCursor = max(0, min(newCursor, textLength))
            if extendSelection {
                selections[index].cursor = newCursor
            } else {
                selections[index].anchor = newCursor
                selections[index].cursor = newCursor
            }
        }
        updateSelectionsDisplay()
        cancelCompletions()
    }

    private func applyMotionToLineColumn(extendSelection: Bool, _ transform: (Int, Int) -> (line: Int, column: Int)) {
        applyMotion(extendSelection: extendSelection) { selection in
            let pos = lineMapPosition(forOffset: selection.cursor)
            let newPos = transform(pos.line, pos.column)
            let line = max(0, min(newPos.line, max(0, (lineMap?.lineCount ?? 1) - 1)))
            let maxColumn = lineLengthUTF16(forLine: line)
            let column = max(0, min(newPos.column, maxColumn))
            return lineMapOffset(forLine: line) + column
        }
    }

    private func collapseSelections(toStart: Bool) {
        selections = selections.map { selection in
            let range = selection.range
            let position = toStart ? range.location : (range.location + range.length)
            return Selection(anchor: position, cursor: position)
        }
        updateSelectionsDisplay()
    }

    private func moveSelectionsToStartOfLine(extendSelection: Bool, firstNonWhitespace: Bool) {
        applyMotionToLineColumn(extendSelection: extendSelection) { line, _ in
            let column = firstNonWhitespace ? firstNonWhitespaceColumn(inLine: line) : 0
            return (line, column)
        }
    }

    private func moveSelectionsToEndOfLine(extendSelection: Bool) {
        applyMotionToLineColumn(extendSelection: extendSelection) { line, _ in
            let column = lineEndColumn(for: line)
            return (line, column)
        }
    }

    private func deleteBackwardSelections() {
        let textLength = currentTextLengthUTF16()
        var ranges: [(range: NSRange, index: Int)] = []

        for (idx, selection) in selections.enumerated() {
            let range = selection.range
            if range.length > 0 {
                ranges.append((range, idx))
            } else if selection.cursor > 0 && selection.cursor <= textLength {
                ranges.append((NSRange(location: selection.cursor - 1, length: 1), idx))
            }
        }

        if ranges.isEmpty { return }

        previousText = textStorage
        lastHighlightedRange = nil
        preserveHighlightsDuringRehighlight = true

        let nsText = NSMutableString(string: textStorage)
        let sorted = ranges.sorted { lhs, rhs in
            if lhs.range.location != rhs.range.location { return lhs.range.location > rhs.range.location }
            return lhs.range.length > rhs.range.length
        }

        suppressHighlightUpdates = true
        defer { suppressHighlightUpdates = false }

        if sorted.count == 1 {
            lastEditRange = sorted[0].range
            lastReplacementLength = 0
            markDirtyHighlight(range: dirtyRange(for: sorted[0].range, replacementLength: 0))
            applyHighlightEdit(range: sorted[0].range, replacementLength: 0)
        } else {
            lastEditRange = nil
            lastReplacementLength = 0
            for edit in sorted {
                markDirtyHighlight(range: dirtyRange(for: edit.range, replacementLength: 0))
                applyHighlightEdit(range: edit.range, replacementLength: 0)
            }
        }

        var newOffsets: [Int] = Array(repeating: 0, count: selections.count)
        for (range, index) in sorted {
            nsText.deleteCharacters(in: range)
            newOffsets[index] = range.location
        }

        selections = newOffsets.map { Selection(anchor: $0, cursor: $0) }
        primarySelectionIndex = max(0, min(primarySelectionIndex, selections.count - 1))

        let newText = nsText as String
        textStorage = newText
        textRevision &+= 1
        searchCache = nil
        metalTextView?.setSearchMatchRanges([])
        metalTextView?.setActiveSearchMatch(nil)
        lineMap = LineMap(text: textStorage)

        if sorted.count == 1 {
            metalTextView.applyEdit(range: sorted[0].range, replacement: "")
        } else {
            metalTextView.setText(newText)
        }

        recomputeFolding()

        if let dirtyRange = dirtyHighlightRange {
            metalTextView.setHighlights(coloredRanges, invalidating: dirtyRange)
        } else {
            metalTextView.setHighlights(coloredRanges)
        }

        highlightSyntax()
        updateContentSize()
        updateSelectionsDisplay()
        notifyLSPDocumentChanged()
        updateCompletionFilter()
        notifyTextDidChange()
    }

    private func deleteForwardSelections() {
        let textLength = currentTextLengthUTF16()
        var ranges: [(range: NSRange, index: Int)] = []

        for (idx, selection) in selections.enumerated() {
            let range = selection.range
            if range.length > 0 {
                ranges.append((range, idx))
            } else if selection.cursor < textLength {
                ranges.append((NSRange(location: selection.cursor, length: 1), idx))
            }
        }

        if ranges.isEmpty { return }

        previousText = textStorage
        lastHighlightedRange = nil
        preserveHighlightsDuringRehighlight = true

        let nsText = NSMutableString(string: textStorage)
        let sorted = ranges.sorted { lhs, rhs in
            if lhs.range.location != rhs.range.location { return lhs.range.location > rhs.range.location }
            return lhs.range.length > rhs.range.length
        }

        suppressHighlightUpdates = true
        defer { suppressHighlightUpdates = false }

        if sorted.count == 1 {
            lastEditRange = sorted[0].range
            lastReplacementLength = 0
            markDirtyHighlight(range: dirtyRange(for: sorted[0].range, replacementLength: 0))
            applyHighlightEdit(range: sorted[0].range, replacementLength: 0)
        } else {
            lastEditRange = nil
            lastReplacementLength = 0
            for edit in sorted {
                markDirtyHighlight(range: dirtyRange(for: edit.range, replacementLength: 0))
                applyHighlightEdit(range: edit.range, replacementLength: 0)
            }
        }

        var newOffsets: [Int] = Array(repeating: 0, count: selections.count)
        for (range, index) in sorted {
            nsText.deleteCharacters(in: range)
            newOffsets[index] = range.location
        }

        selections = newOffsets.map { Selection(anchor: $0, cursor: $0) }
        primarySelectionIndex = max(0, min(primarySelectionIndex, selections.count - 1))

        let newText = nsText as String
        textStorage = newText
        textRevision &+= 1
        searchCache = nil
        metalTextView?.setSearchMatchRanges([])
        metalTextView?.setActiveSearchMatch(nil)
        lineMap = LineMap(text: textStorage)

        if sorted.count == 1 {
            metalTextView.applyEdit(range: sorted[0].range, replacement: "")
        } else {
            metalTextView.setText(newText)
        }

        recomputeFolding()

        if let dirtyRange = dirtyHighlightRange {
            metalTextView.setHighlights(coloredRanges, invalidating: dirtyRange)
        } else {
            metalTextView.setHighlights(coloredRanges)
        }

        highlightSyntax()
        updateContentSize()
        updateSelectionsDisplay()
        notifyLSPDocumentChanged()
        updateCompletionFilter()
        notifyTextDidChange()
    }

    private func yankSelections(expandEmptyToChar: Bool) {
        let ranges = selectionRangesForOperation(expandEmptyToChar: expandEmptyToChar).map { $0.range }
        guard !ranges.isEmpty else { return }
        let nsText = textStorage as NSString
        yankRegister.values = ranges.map { nsText.substring(with: $0) }
    }

    private func deleteSelections(expandEmptyToChar: Bool) {
        replaceSelections(with: "", expandEmptyToChar: expandEmptyToChar)
    }

    private func changeSelections(expandEmptyToChar: Bool) {
        deleteSelections(expandEmptyToChar: expandEmptyToChar)
        helixMode = .insert
    }

    private func pasteSelections(before: Bool) {
        guard !yankRegister.values.isEmpty else { return }
        let ranges = selectionRangesForOperation(expandEmptyToChar: false)
        if ranges.isEmpty { return }

        previousText = textStorage
        lastHighlightedRange = nil
        preserveHighlightsDuringRehighlight = true

        let nsText = NSMutableString(string: textStorage)
        let sorted = ranges.sorted { lhs, rhs in
            if lhs.range.location != rhs.range.location { return lhs.range.location > rhs.range.location }
            return lhs.range.length > rhs.range.length
        }

        suppressHighlightUpdates = true
        defer { suppressHighlightUpdates = false }

        if sorted.count == 1 {
            let insertString = yankRegister.values.first ?? ""
            let insertLength = (insertString as NSString).length
            lastEditRange = sorted[0].range
            lastReplacementLength = insertLength
            markDirtyHighlight(range: dirtyRange(for: sorted[0].range, replacementLength: insertLength))
            applyHighlightEdit(range: sorted[0].range, replacementLength: insertLength)
        } else {
            lastEditRange = nil
            lastReplacementLength = 0
            for edit in sorted {
                let insertString = yankRegister.values.first ?? ""
                let insertLength = (insertString as NSString).length
                markDirtyHighlight(range: dirtyRange(for: edit.range, replacementLength: insertLength))
                applyHighlightEdit(range: edit.range, replacementLength: insertLength)
            }
        }

        var newOffsets: [Int] = Array(repeating: 0, count: selections.count)
        for item in sorted {
            let range = item.range
            let selectionIndex = item.index
            let value = yankRegister.values.count == ranges.count
                ? yankRegister.values[selectionIndex]
                : yankRegister.values[0]
            let insertLength = (value as NSString).length
            let insertOffset = before ? range.location : (range.location + range.length)
            nsText.insert(value, at: insertOffset)
            newOffsets[selectionIndex] = insertOffset + insertLength
        }

        selections = newOffsets.map { Selection(anchor: $0, cursor: $0) }
        primarySelectionIndex = max(0, min(primarySelectionIndex, selections.count - 1))

        let newText = nsText as String
        textStorage = newText
        lineMap = LineMap(text: textStorage)

        if sorted.count == 1 {
            metalTextView.applyEdit(range: sorted[0].range, replacement: yankRegister.values.first ?? "")
        } else {
            metalTextView.setText(newText)
        }

        recomputeFolding()

        if let dirtyRange = dirtyHighlightRange {
            metalTextView.setHighlights(coloredRanges, invalidating: dirtyRange)
        } else {
            metalTextView.setHighlights(coloredRanges)
        }

        highlightSyntax()
        updateContentSize()
        updateSelectionsDisplay()
    }

    // MARK: - Scroll Handling

    private func handleScroll() {
        _ = updateMetalViewport()

        // Trigger visible-range-only highlighting
        scheduleScrollHighlight()
        notifyVisibleLineRangeChanged()
    }

    // MARK: - Configuration

    private func applyConfiguration() {
        metalTextView?.setTextInsets(NSEdgeInsets(top: 4, left: 4, bottom: 4, right: 4))
        metalTextView?.setGutterInsets(NSEdgeInsets(top: 4, left: 14, bottom: 4, right: 20))
        metalTextView?.updateFont(_configuration.font, lineHeightMultiplier: _configuration.lineHeight)
        metalTextView?.setMinimumGutterWidth(_configuration.minimumGutterWidth)
        metalTextView?.setShowsGutter(_configuration.showGutter)
        metalTextView?.setShowsLineNumbers(_configuration.showLineNumbers)
        metalTextView?.setShowsGitGutter(_configuration.showGitGutter)
        metalTextView?.setStatusBarHeight(statusBarHeight)
        metalTextView?.setBlameInfo(blameInfo, showInline: _configuration.showInlineBlame, delay: _configuration.blameDelay)
        setHelixModeEnabled(_configuration.helixModeEnabled)

        // Update content size after font change
        updateContentSize()
        recomputeFolding()
    }

    private func updateModeIndicator() {
        updateCursorStyle()
        updateStatusBar()
        updateSearchOverlay()
    }

    private func updateHelixUI() {
        metalTextView?.setStatusBarEnabled(helixModeEnabled)
        metalTextView?.setStatusBarHeight(statusBarHeight)
        updateModeIndicator()
        updateContentSize()
    }

    private func updateCursorStyle() {
        guard helixModeEnabled else {
            metalTextView.cursorStyle = .bar
            return
        }
        switch helixMode {
        case .insert:
            metalTextView.cursorStyle = .bar
        case .normal, .select, .searchForward, .searchBackward, .replaceCharacter:
            metalTextView.cursorStyle = .block
        }
    }

    private func setupStatusBar() {
        updateStatusBar()
    }

    private func modeLabelText() -> String {
        switch helixMode {
        case .normal:
            return "NORMAL"
        case .insert:
            return "INSERT"
        case .select:
            return "SELECT"
        case .searchForward:
            let prefix = searchScope == .openDocuments ? "SEARCH ALL /" : "SEARCH /"
            if searchQuery.isEmpty { return prefix }
            return "\(prefix) \(searchQuery)\(searchStatusSuffix())"
        case .searchBackward:
            let prefix = searchScope == .openDocuments ? "SEARCH ALL ?" : "SEARCH ?"
            if searchQuery.isEmpty { return prefix }
            return "\(prefix) \(searchQuery)\(searchStatusSuffix())"
        case .replaceCharacter:
            return "REPLACE"
        }
    }

    private func updateStatusBar() {
        guard helixModeEnabled else {
            metalTextView?.setStatusBarText(left: "", right: "")
            return
        }
        let mode = modeLabelText()
        let line = cursorLine + 1
        let column = cursorColumn + 1
        let selectionInfo = selections.count > 1 ? "\(selections.count) selections" : "1 selection"
        let info = "Ln \(line), Col \(column)  •  \(selectionInfo)"
        let caseIndicator = searchOptions.caseSensitive ? "Aa" : "aA"
        applyStatusBarModeStyle()
        metalTextView?.setStatusBarText(left: mode, right: info, rightBadge: caseIndicator)
    }

    private var isSearchOverlayVisible: Bool {
        searchOverlayActive || helixMode == .searchForward || helixMode == .searchBackward
    }

    private func updateSearchOverlay() {
        guard let metalTextView = metalTextView else { return }

        let visible = isSearchOverlayVisible
        let active = searchOverlayActive || helixMode == .searchForward || helixMode == .searchBackward
        let scopeValue: MetalTextView.SearchOverlayScope = (searchScope == .openDocuments) ? .openDocuments : .currentFile
        let matchInfo = searchMatchInfo(query: searchQuery, scope: searchScope)

        metalTextView.setSearchOverlayState(
            visible: visible,
            active: active,
            query: searchQuery,
            scope: scopeValue,
            caseSensitive: searchOptions.caseSensitive,
            matchIndex: matchInfo?.index,
            matchCount: matchInfo?.count
        )
    }

    private func searchMatchInfo(query: String, scope: SearchScope) -> (index: Int, count: Int)? {
        let trimmed = query.trimmingCharacters(in: .whitespacesAndNewlines)
        guard !trimmed.isEmpty else { return nil }
        guard scope == .currentFile else { return nil }
        let matches = searchMatches(for: trimmed, options: searchOptions)
        guard !matches.isEmpty else { return (0, 0) }
        let cursor = selections.first?.cursor ?? 0
        let index = matchIndex(for: cursor, matches: matches) ?? 0
        return (index + 1, matches.count)
    }

    private func searchStatusSuffix() -> String {
        let trimmed = searchQuery.trimmingCharacters(in: .whitespacesAndNewlines)
        guard !trimmed.isEmpty else { return "" }
        let matches = searchMatches(for: trimmed, options: searchOptions)
        guard !matches.isEmpty else { return " (0/0)" }
        let cursor = selections.first?.cursor ?? 0
        let index = matchIndex(for: cursor, matches: matches) ?? 0
        return " (\(index + 1)/\(matches.count))"
    }

    private func applyStatusBarModeStyle() {
        let background: NSColor
        let text: NSColor
        switch helixMode {
        case .normal:
            background = _theme.selectionColor
            text = _theme.textColor
        case .insert:
            background = _theme.gitAddedColor
            text = _theme.textColor
        case .select:
            background = _theme.gitModifiedColor
            text = _theme.textColor
        case .searchForward, .searchBackward:
            background = _theme.gitDeletedColor
            text = _theme.textColor
        case .replaceCharacter:
            background = _theme.gitDeletedColor
            text = _theme.textColor
        }
        metalTextView?.statusBarModeBackgroundColor = background
        metalTextView?.statusBarModeTextColor = text
    }

    private func updateContentSize() {
        guard let metalTextView = metalTextView else { return }

        let contentSize = metalTextView.contentSize
        let viewportWidth = max(0, scrollView.contentView.bounds.width)
        let viewportHeight = max(0, scrollView.contentView.bounds.height)
        let documentSize = CGSize(
            width: max(contentSize.width, viewportWidth),
            height: max(contentSize.height, viewportHeight)
        )

        // Update document view size for scrollbars
        documentView.frame = CGRect(origin: .zero, size: documentSize)

        updateMetalViewport()
        notifyVisibleLineRangeChanged()
    }

    @discardableResult
    private func updateMetalViewport() -> CGRect {
        let visibleRect = scrollView.documentVisibleRect
        let viewportSize = scrollView.contentView.bounds.size
        let viewportOrigin = scrollView.contentView.frame.origin
        metalTextView.scrollOffset = visibleRect.origin
        metalTextView.frame = CGRect(origin: viewportOrigin, size: viewportSize)
        return visibleRect
    }

    private func notifyVisibleLineRangeChanged() {
        let visible = metalTextView.visibleLineRange(
            scrollOffset: scrollView.documentVisibleRect.origin.y,
            height: scrollView.contentView.bounds.height
        )
        guard visible.first <= visible.last else { return }

        let range = visible.first...visible.last
        guard range != lastVisibleLineRange else { return }

        lastVisibleLineRange = range
        onVisibleLineRangeChange?(range)
    }

    private func scrollToRange(_ range: NSRange) {
        guard let metalTextView = metalTextView else { return }
        let pos = lineMapPosition(forOffset: range.location)
        let lineHeight = metalTextView.lineHeight
        let viewportHeight = scrollView.contentView.bounds.height
        let docHeight = documentView.bounds.height

        guard lineHeight > 0, viewportHeight > 0 else { return }

        let targetLineY = CGFloat(pos.line) * lineHeight
        let centeredY = targetLineY - (viewportHeight - lineHeight) * 0.5
        let maxY = max(0, docHeight - viewportHeight)
        let clampedY = max(0, min(centeredY, maxY))

        let currentX = scrollView.documentVisibleRect.origin.x
        scrollView.contentView.scroll(to: NSPoint(x: currentX, y: clampedY))
        scrollView.reflectScrolledClipView(scrollView.contentView)
        updateMetalViewport()
    }

    private func ensureGlyphPreloadIfNeeded(with text: String) {
        guard !didPreloadGlyphs else { return }
        guard !text.isEmpty else { return }
        let fontSize = _configuration.font.pointSize
        metalTextView?.renderer?.glyphAtlas.preloadASCII(fontSize: fontSize)
        didPreloadGlyphs = true
    }

    private func applyTheme() {
        let lineHighlight = currentLineHighlightColor(for: _theme.backgroundColor)
        metalTextView?.setBackgroundColor(_theme.backgroundColor)
        metalTextView?.setDefaultTextColor(_theme.textColor)
        metalTextView?.selectionColor = _theme.selectionColor
        metalTextView?.cursorColor = _theme.textColor
        metalTextView?.searchHighlightColor = _theme.selectionColor.withAlphaComponent(0.2)
        metalTextView?.activeSearchHighlightColor = _theme.selectionColor.withAlphaComponent(0.4)
        metalTextView?.currentLineHighlightColor = lineHighlight
        metalTextView?.indentGuideColor = _theme.gutterSeparatorColor.withAlphaComponent(0.22)
        metalTextView?.indentGuideLinePadding = 0
        metalTextView?.indentGuideLineWidth = 1
        metalTextView?.activeIndentGuideColor = _theme.selectionColor.withAlphaComponent(0.5)
        metalTextView?.activeIndentGuideLineWidth = 1.5
        metalTextView?.bracketHighlightColor = _theme.selectionColor.withAlphaComponent(0.35)
        metalTextView?.foldPlaceholderColor = _theme.gutterTextColor.withAlphaComponent(0.8)
        metalTextView?.markedTextUnderlineColor = _theme.selectionColor.withAlphaComponent(0.9)

        metalTextView?.gutterBackgroundColor = _theme.gutterBackgroundColor
        metalTextView?.gutterSeparatorColor = _theme.gutterSeparatorColor
        metalTextView?.lineNumberColor = _theme.gutterTextColor
        metalTextView?.currentLineNumberColor = _theme.textColor
        metalTextView?.selectedLineNumberColor = _theme.gutterActiveTextColor
        metalTextView?.foldMarkerColor = _theme.gutterTextColor.withAlphaComponent(0.8)
        metalTextView?.foldMarkerActiveColor = _theme.textColor
        metalTextView?.foldMarkerHoverBackgroundColor = _theme.gutterSeparatorColor.withAlphaComponent(0.25)
        metalTextView?.gitAddedColor = _theme.gitAddedColor
        metalTextView?.gitModifiedColor = _theme.gitModifiedColor
        metalTextView?.gitDeletedColor = _theme.gitDeletedColor

        metalTextView?.statusBarBackgroundColor = _theme.gutterBackgroundColor
        metalTextView?.statusBarBorderColor = _theme.gutterSeparatorColor
        metalTextView?.statusBarTextColor = _theme.textColor
        metalTextView?.statusBarSecondaryTextColor = _theme.gutterTextColor
        metalTextView?.statusBarBadgeBackgroundColor = _theme.selectionColor.withAlphaComponent(0.25)
        metalTextView?.statusBarBadgeTextColor = _theme.textColor

        metalTextView?.searchOverlayBackgroundColor = _theme.gutterBackgroundColor.withAlphaComponent(0.95)
        metalTextView?.searchOverlayBorderColor = _theme.gutterSeparatorColor.withAlphaComponent(0.65)
        metalTextView?.searchOverlayFieldBackgroundColor = _theme.backgroundColor.withAlphaComponent(0.9)
        metalTextView?.searchOverlayFieldBorderColor = _theme.gutterSeparatorColor.withAlphaComponent(0.45)
        metalTextView?.searchOverlayFieldActiveBorderColor = _theme.selectionColor.withAlphaComponent(0.9)
        metalTextView?.searchOverlayTextColor = _theme.textColor
        metalTextView?.searchOverlayPlaceholderColor = _theme.gutterTextColor.withAlphaComponent(0.7)
        metalTextView?.searchOverlayButtonBackgroundColor = _theme.gutterSeparatorColor.withAlphaComponent(0.35)
        metalTextView?.searchOverlayButtonHoverBackgroundColor = _theme.gutterSeparatorColor.withAlphaComponent(0.55)
        metalTextView?.searchOverlayButtonActiveBackgroundColor = _theme.selectionColor.withAlphaComponent(0.6)
        metalTextView?.searchOverlayButtonTextColor = _theme.textColor.withAlphaComponent(0.85)
        metalTextView?.searchOverlayButtonActiveTextColor = _theme.textColor
        applyStatusBarModeStyle()

        // Update highlight theme based on background brightness
        let brightness = _theme.backgroundColor.brightnessComponent
        highlightTheme = brightness < 0.5 ? .defaultDark : .defaultLight
        Task { await highlighter?.setTheme(highlightTheme) }
    }

    private func currentLineHighlightColor(for background: NSColor) -> NSColor {
        let brightness = background.brightnessComponent
        let base = brightness < 0.5 ? NSColor.white : NSColor.black
        let alpha: CGFloat = brightness < 0.5 ? 0.12 : 0.07
        return base.withAlphaComponent(alpha)
    }

    // MARK: - Folding / Indent Guides

    private func recomputeFolding() {
        guard !textStorage.isEmpty else {
            clearFolding()
            return
        }

        guard let highlighter = highlighter else {
            clearFolding()
            return
        }

        guard lastParsedText == textStorage else {
            return
        }

        let textSnapshot = textStorage
        Task {
            let folding = await highlighter.foldingRanges()
            await MainActor.run { [weak self] in
                guard let self = self else { return }
                guard self.textStorage == textSnapshot else { return }
                self.applyFoldingRanges(folding)
            }
        }
    }

    private func clearFolding() {
        foldableRanges = []
        foldedStartLines.removeAll()
        foldedRanges = []
        indentGuideSegments = []
        metalTextView?.setIndentGuideSegments([])
        metalTextView?.setActiveIndentGuideSegments([])
        metalTextView?.setFoldedLineRanges([])
        metalTextView?.setFoldRanges([], foldedStartLines: [])
    }

    private func applyFoldingRanges(_ ranges: [VVHighlighting.FoldingRange]) {
        let lines = textStorage.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        guard !lines.isEmpty else {
            clearFolding()
            return
        }
        let lineCount = lines.count
        var byStart: [Int: FoldRange] = [:]

        for range in ranges {
            let start = max(0, min(range.startLine, lineCount - 1))
            let end = max(0, min(range.endLine, lineCount - 1))
            guard end > start else { continue }
            let candidate = FoldRange(startLine: start, endLine: end, indentColumn: range.indentColumn)
            if let existing = byStart[start] {
                if candidate.endLine > existing.endLine {
                    byStart[start] = candidate
                }
            } else {
                byStart[start] = candidate
            }
        }

        foldableRanges = byStart.values.sorted { lhs, rhs in
            if lhs.startLine != rhs.startLine { return lhs.startLine < rhs.startLine }
            return lhs.endLine < rhs.endLine
        }
        let validStarts = Set(foldableRanges.map { $0.startLine })
        foldedStartLines = foldedStartLines.intersection(validStarts)

        let guideSegments = computeIndentGuideSegments(lines: lines)
        indentGuideSegments = guideSegments
        metalTextView?.setIndentGuideSegments(guideSegments)
        updateActiveIndentGuides()

        applyFoldState()
    }

    private func applyFoldState() {
        let folded = foldableRanges
            .filter { foldedStartLines.contains($0.startLine) }
            .map { $0.startLine...$0.endLine }
        foldedRanges = folded
        metalTextView?.setFoldedLineRanges(folded)
        let gutterRanges = foldableRanges.map { MetalGutterFoldRange(startLine: $0.startLine, endLine: $0.endLine) }
        metalTextView?.setFoldRanges(gutterRanges, foldedStartLines: foldedStartLines)
        updateContentSize()
        ensureSelectionsVisibleAfterFolding()
    }

    private func toggleFold(atLine line: Int) {
        guard foldableRanges.contains(where: { $0.startLine == line }) else { return }
        if foldedStartLines.contains(line) {
            foldedStartLines.remove(line)
        } else {
            foldedStartLines.insert(line)
        }
        applyFoldState()
    }

    private func ensureSelectionsVisibleAfterFolding() {
        guard !foldedRanges.isEmpty else { return }
        var updated = false
        for index in selections.indices {
            let pos = lineMapPosition(forOffset: selections[index].cursor)
            if let fold = foldedRanges.first(where: { pos.line > $0.lowerBound && pos.line <= $0.upperBound }) {
                let targetLine = fold.lowerBound
                let lineStart = lineMapOffset(forLine: targetLine)
                let column = min(pos.column, lineLengthUTF16(forLine: targetLine))
                let newOffset = lineStart + column
                selections[index].anchor = newOffset
                selections[index].cursor = newOffset
                updated = true
            }
        }
        if updated {
            updateSelectionsDisplay()
        }
    }

    private func computeIndentGuideSegments(lines: [String]) -> [MetalTextView.IndentGuideSegment] {
        var guides: [MetalTextView.IndentGuideSegment] = []
        var stack: [MetalTextView.IndentGuideSegment] = []
        let tabWidth = max(1, _configuration.tabWidth)
        let lineCount = lines.count
        let trailingSearchLimit = 25

        var row = 0
        while row < lineCount {
            var lineIndent = leadingIndentColumns(lines[row])
            var lastRow = row
            var depth = 0
            let isBlank = isLineWhitespace(lines[row])

            if isBlank {
                var found = false
                var look = row + 1
                let limit = min(lineCount - 1, row + trailingSearchLimit)
                while look <= limit {
                    if !isLineWhitespace(lines[look]) {
                        lineIndent = leadingIndentColumns(lines[look])
                        lastRow = look
                        depth = lineIndent / tabWidth
                        found = true
                        row = look
                        break
                    }
                    look += 1
                }
                if !found {
                    depth = 0
                }
            } else {
                depth = lineIndent / tabWidth
            }

            let currentDepth = stack.count
            if depth < currentDepth {
                for _ in 0..<(currentDepth - depth) {
                    var guide = stack.removeLast()
                    if lastRow != row {
                        guide.endLine = max(guide.startLine, row - 1)
                    }
                    guides.append(guide)
                }
            } else if depth > currentDepth {
                for newDepth in currentDepth..<depth {
                    let column = newDepth * tabWidth
                    stack.append(MetalTextView.IndentGuideSegment(
                        startLine: row,
                        endLine: lastRow,
                        column: column
                    ))
                }
            }

            for index in stack.indices {
                stack[index].endLine = lastRow
            }

            row += 1
        }

        guides.append(contentsOf: stack)
        return guides
    }

    private func updateActiveIndentGuides() {
        guard let metalTextView = metalTextView else { return }
        guard !indentGuideSegments.isEmpty else {
            metalTextView.setActiveIndentGuideSegments([])
            return
        }

        let maxLine = max(0, (lineMap?.lineCount ?? 1) - 1)
        let line = max(0, min(cursorLine, maxLine))
        var best: MetalTextView.IndentGuideSegment?

        for segment in indentGuideSegments where line >= segment.startLine && line <= segment.endLine {
            if let current = best {
                if segment.column > current.column {
                    best = segment
                }
            } else {
                best = segment
            }
        }

        if let best = best {
            metalTextView.setActiveIndentGuideSegments([best])
        } else {
            metalTextView.setActiveIndentGuideSegments([])
        }
    }

    private func isLineWhitespace(_ line: String) -> Bool {
        for ch in line {
            if ch != " " && ch != "\t" { return false }
        }
        return true
    }

    private func leadingIndentColumns(_ line: String) -> Int {
        var columns = 0
        for ch in line {
            if ch == " " {
                columns += 1
            } else if ch == "\t" {
                let tabWidth = max(1, _configuration.tabWidth)
                let remainder = columns % tabWidth
                columns += tabWidth - remainder
            } else {
                break
            }
        }
        return columns
    }

    // MARK: - Public API (VVEditorContainerView compatible)

    /// Set the language for syntax highlighting
    public func setLanguage(_ language: VVLanguage) {
        setLanguage(language, resetHighlighter: true)
    }

    /// Set the language for syntax highlighting, optionally preserving the current highlighter.
    public func setLanguage(_ language: VVLanguage, resetHighlighter: Bool) {
        if self.language?.identifier == language.identifier {
            return
        }
        self.language = language
        guard resetHighlighter else { return }

        preserveHighlightsDuringRehighlight = false
        highlighter = nil
        coloredRanges = []
        lastParsedText = nil
        metalTextView?.setHighlights([])
        setupHighlighterIfNeeded()
    }

    /// Set the theme
    public func setTheme(_ theme: VVTheme) {
        self._theme = theme
        applyTheme()
    }

    /// Set the configuration
    public func setConfiguration(_ configuration: VVConfiguration) {
        self._configuration = configuration
        applyConfiguration()
    }

    /// Enable or disable Helix-style modal editing.
    public func setHelixModeEnabled(_ enabled: Bool) {
        if helixModeEnabled == enabled { return }
        helixModeEnabled = enabled
        helixMode = enabled ? .normal : .insert
        updateHelixUI()
    }

    /// Current Helix mode enabled state.
    public var isHelixModeEnabled: Bool {
        helixModeEnabled
    }

    /// Set git hunks (VVDiffHunk version for compatibility)
    public func setGitHunks(_ hunks: [VVDiffHunk]) {
        let metalHunks = hunks.map { hunk -> MetalGutterGitHunk in
            let status: MetalGutterGitHunk.Status
            switch hunk.changeType {
            case .added: status = .added
            case .deleted: status = .deleted
            case .modified: status = .modified
            }
            return MetalGutterGitHunk(
                startLine: hunk.newStart - 1,  // Convert to 0-indexed
                lineCount: hunk.newCount,
                status: status
            )
        }
        metalTextView.setGitHunks(metalHunks)
    }

    /// Set blame info
    public func setBlameInfo(_ blame: [VVBlameInfo]) {
        blameInfo = blame
        metalTextView?.setBlameInfo(blame, showInline: _configuration.showInlineBlame, delay: _configuration.blameDelay)
    }

    /// Set LSP client
    public func setLSPClient(_ client: (any VVLSPClient)?, documentURI: String?) {
        if lspClient != nil, client == nil, let oldURI = self.documentURI {
            Task { [oldURI] in
                await lspClient?.documentClosed(oldURI)
            }
        }

        lspClient = client
        self.documentURI = documentURI
        completionItems.removeAll()
        filteredCompletionItems.removeAll()
        completionAnchorOffset = 0
        completionSelectedIndex = 0
        completionDebounceTimer?.invalidate()
        completionDebounceTimer = nil
        metalTextView?.clearCompletions()

        guard let client, let uri = documentURI, let lang = language?.identifier else { return }
        Task {
            await client.documentOpened(uri, text: textStorage, language: lang)
        }
    }

    /// Focus the text view
    public func focusTextView() {
        window?.makeFirstResponder(hiddenInputView)
    }

    // MARK: - Syntax Highlighting

    private func highlightSyntax() {
        // Debounce highlighting
        highlightDebouncer?.cancel()

        let workItem = DispatchWorkItem { [weak self] in
            self?.performHighlighting()
        }

        highlightDebouncer = workItem
        DispatchQueue.main.asyncAfter(deadline: .now() + 0.1, execute: workItem)
    }

    // MARK: - LSP / Completions

    private func notifyLSPDocumentChanged() {
        guard let client = lspClient, let uri = documentURI else { return }
        let text = textStorage
        Task {
            await client.documentChanged(uri, changes: [VVTextChange.full(text)])
        }
    }

    private func notifyTextDidChange() {
        delegate?.editorDidChangeText(textStorage)
        onTextChange?(textStorage)
        onTextChangeInternal?(textStorage)
    }

    private func triggerCompletion(triggerKind: VVCompletionTriggerKind, triggerCharacter: String?) {
        guard let client = lspClient, let uri = documentURI else { return }
        guard let cursorOffset = metalTextView?.insertionOffset() else { return }
        let pos = lineMapPosition(forOffset: cursorOffset)
        let position = VVTextPosition(line: pos.line, character: pos.column)
        completionAnchorOffset = cursorOffset
        if triggerCharacter != nil {
            completionAnchorOffset = max(0, cursorOffset - 1)
        }

        Task {
            do {
                let items = try await client.completions(
                    at: position,
                    in: uri,
                    triggerKind: triggerKind,
                    triggerCharacter: triggerCharacter
                )
                await MainActor.run {
                    self.completionItems = items
                    self.updateCompletionFilter()
                }
            } catch {
                await MainActor.run {
                    self.cancelCompletions()
                }
            }
        }
    }

    private func handleCompletionTrigger(for insertedText: String) {
        guard lspClient != nil else { return }
        completionDebounceTimer?.invalidate()
        completionDebounceTimer = nil

        guard insertedText.count == 1, let char = insertedText.first else {
            return
        }

        if immediateTriggerCharacters.contains(char) {
            triggerCompletion(triggerKind: .triggerCharacter, triggerCharacter: String(char))
            return
        }

        if let scalar = char.unicodeScalars.first, delayedTriggerCharacters.contains(scalar) {
            completionDebounceTimer = Timer.scheduledTimer(withTimeInterval: 0.25, repeats: false) { [weak self] _ in
                self?.triggerCompletion(triggerKind: .invoked, triggerCharacter: nil)
            }
        } else if metalTextView?.isCompletionVisible == true {
            updateCompletionFilter()
        }
    }

    private func updateCompletionFilter() {
        guard let metalTextView, metalTextView.isCompletionVisible || !completionItems.isEmpty else { return }
        guard let cursorOffset = metalTextView.insertionOffset() else { return }
        completionCursorOffset = cursorOffset

        let start = min(completionAnchorOffset, cursorOffset)
        let end = max(completionAnchorOffset, cursorOffset)
        let nsText = textStorage as NSString
        let clampedStart = max(0, min(start, nsText.length))
        let clampedEnd = max(clampedStart, min(end, nsText.length))
        let prefix = nsText.substring(with: NSRange(location: clampedStart, length: clampedEnd - clampedStart))

        filteredCompletionItems = filterCompletionItems(prefix)
        completionSelectedIndex = 0

        if filteredCompletionItems.isEmpty {
            metalTextView.clearCompletions()
        } else {
            metalTextView.setCompletionItems(filteredCompletionItems, anchorOffset: completionAnchorOffset, cursorOffset: cursorOffset)
            metalTextView.updateCompletionSelection(completionSelectedIndex)
        }
    }

    private func filterCompletionItems(_ prefix: String) -> [VVCompletionItem] {
        guard !prefix.isEmpty else {
            return completionItems
        }
        let lower = prefix.lowercased()
        return completionItems.filter { item in
            let text = (item.filterText ?? item.label).lowercased()
            return text.hasPrefix(lower)
        }
    }

    private func cancelCompletions() {
        completionItems.removeAll()
        filteredCompletionItems.removeAll()
        completionSelectedIndex = 0
        metalTextView?.clearCompletions()
    }

    private func applySelectedCompletion() {
        guard let item = metalTextView?.selectedCompletionItem() else { return }
        let range = metalTextView?.completionAnchorRange()
        guard let cursorOffset = metalTextView?.insertionOffset(),
              let anchor = range?.anchor else { return }
        let start = min(anchor, cursorOffset)
        let end = max(anchor, cursorOffset)
        let replaceRange = NSRange(location: start, length: end - start)
        replaceRangeWithCompletion(replaceRange, insertText: item.insertText)
        cancelCompletions()
    }

    private func replaceRangeWithCompletion(_ range: NSRange, insertText: String) {
        replaceRange(range, with: insertText, updateMarkedRange: false)
    }

    private func performHighlighting() {
        guard let highlighter = highlighter else {
            setupHighlighterIfNeeded()
            if !preserveHighlightsDuringRehighlight {
                coloredRanges = []
                metalTextView.setHighlights(coloredRanges)
            }
            return
        }

        let visibleRange = calculateVisibleRangeWithPadding()
        let targetRange = dirtyHighlightRange.map { lineAlignedRange(for: $0) } ?? visibleRange
        let textSnapshot = textStorage
        highlightTask?.cancel()
        highlightTask = Task {
            do {
                let canIncremental = {
                    guard lastEditRange != nil else { return false }
                    guard !previousText.isEmpty else { return false }
                    guard let lastParsedText = lastParsedText else { return false }
                    guard lastParsedText == previousText else { return false }
                    return true
                }()

                if canIncremental, let editRange = lastEditRange {
                    let edit = createInputEdit(
                        oldText: previousText,
                        newText: textSnapshot,
                        editRange: editRange,
                        replacementLength: lastReplacementLength
                    )
                    _ = try await highlighter.parseIncremental(text: textSnapshot, edit: edit)
                    lastEditRange = nil
                } else {
                    lastEditRange = nil
                    _ = try await highlighter.parse(textSnapshot)
                }
                previousText = textSnapshot
                lastParsedText = textSnapshot
                lastHighlightedRange = nil

                let highlights = try await highlighter.highlights(in: targetRange)
                let ranges = coloredRanges(from: highlights)
                let folding = await highlighter.foldingRanges()

                await MainActor.run {
                    guard self.textStorage == textSnapshot else { return }
                    self.replaceHighlights(in: targetRange, with: ranges)
                    self.applyFoldingRanges(folding)
                    if let dirtyRange = self.dirtyHighlightRange,
                       NSIntersectionRange(dirtyRange, targetRange).length > 0 {
                        self.dirtyHighlightRange = nil
                    }
                    self.lastHighlightedRange = visibleRange
                    self.preserveHighlightsDuringRehighlight = false
                }
            } catch {
                print("[Metal] Highlighting error: \(error)")
            }
        }
    }

    private func setupHighlighterIfNeeded() {
        guard !isSettingUpHighlighter else { return }
        guard let language = language else { return }
        guard !textStorage.isEmpty else { return }

        isSettingUpHighlighter = true
        Task {
            do {
                let newHighlighter = TreeSitterHighlighter(theme: highlightTheme)
                if let config = LanguageRegistry.shared.language(for: language.identifier) {
                    try await newHighlighter.setLanguage(config)
                }
                await MainActor.run {
                    self.highlighter = newHighlighter
                    self.isSettingUpHighlighter = false
                    self.highlightSyntax()
                }
            } catch {
                await MainActor.run {
                    self.isSettingUpHighlighter = false
                }
                print("[Metal] Failed to setup highlighter for \(language.identifier): \(error)")
            }
        }
    }

    private func highlightVisibleRange() {
        highlightVisibleRangeOnly()
    }

    private func scheduleScrollHighlight() {
        scrollHighlightDebouncer?.cancel()
        let workItem = DispatchWorkItem { [weak self] in
            self?.highlightVisibleRangeOnly()
        }
        scrollHighlightDebouncer = workItem
        DispatchQueue.main.asyncAfter(deadline: .now() + 0.08, execute: workItem)
    }

    private func highlightVisibleRangeOnly() {
        guard highlighter != nil else { return }
        if preserveHighlightsDuringRehighlight || lastEditRange != nil || isSettingUpHighlighter {
            return
        }
        let visibleRange = calculateVisibleRangeWithPadding()

        if let lastRange = lastHighlightedRange,
           NSIntersectionRange(lastRange, visibleRange).length == visibleRange.length {
            if let dirtyRange = dirtyHighlightRange,
               NSIntersectionRange(dirtyRange, visibleRange).length > 0 {
                // Still need to refresh dirty visible area.
            } else {
                return
            }
        }

        highlightTask?.cancel()
        highlightTask = Task {
            do {
                guard let highlighter = highlighter else { return }
                let highlights = try await highlighter.highlights(in: visibleRange)
                let ranges = coloredRanges(from: highlights)
                await MainActor.run {
                    self.replaceHighlights(in: visibleRange, with: ranges)
                    self.lastHighlightedRange = visibleRange
                    if let dirtyRange = self.dirtyHighlightRange,
                       NSIntersectionRange(dirtyRange, visibleRange).length > 0 {
                        self.dirtyHighlightRange = nil
                    }
                }
            } catch {
                // Ignore scroll highlighting errors
            }
        }
    }

    private func calculateVisibleRangeWithPadding() -> NSRange {
        let textLength = (textStorage as NSString).length
        guard let lineMap = lineMap, textLength > 0 else {
            return NSRange(location: 0, length: textLength)
        }

        let visibleRect = scrollView.documentVisibleRect
        let paddedRect = visibleRect.insetBy(dx: 0, dy: -visibleRect.height * 1.5)
        let lineHeight = max(1, metalTextView.lineHeight)
        let topInset = metalTextView.textInsets.top

        let startY = max(0, paddedRect.minY - topInset)
        let endY = max(0, paddedRect.maxY - topInset)
        let startLine = max(0, Int(floor(startY / lineHeight)))
        let endLine = max(0, Int(ceil(endY / lineHeight)))

        let lineCount = lineMap.lineCount
        let clampedStart = min(startLine, max(0, lineCount - 1))
        let clampedEnd = min(endLine, max(0, lineCount - 1))

        let startOffset = lineMapOffset(forLine: clampedStart)
        let endRange = lineMapRange(forLine: clampedEnd)
        let endOffset = endRange.start + endRange.length
        let length = max(0, min(textLength, endOffset) - startOffset)
        return NSRange(location: startOffset, length: length)
    }

    private func createInputEdit(oldText: String, newText: String, editRange: NSRange, replacementLength: Int) -> InputEdit {
        let startByte = UInt32(editRange.location * 2)
        let oldEndByte = UInt32((editRange.location + editRange.length) * 2)
        let newEndByte = UInt32((editRange.location + replacementLength) * 2)

        let startPoint = pointForOffset(editRange.location, in: oldText)
        let oldEndPoint = pointForOffset(editRange.location + editRange.length, in: oldText)
        let newEndPoint = pointForOffset(editRange.location + replacementLength, in: newText)

        return InputEdit(
            startByte: startByte,
            oldEndByte: oldEndByte,
            newEndByte: newEndByte,
            startPoint: startPoint,
            oldEndPoint: oldEndPoint,
            newEndPoint: newEndPoint
        )
    }

    private func pointForOffset(_ offset: Int, in text: String) -> Point {
        var row: UInt32 = 0
        var column: UInt32 = 0
        var currentOffset = 0

        for char in text {
            if currentOffset >= offset { break }
            if char == "\n" {
                row += 1
                column = 0
            } else {
                column += UInt32(char.utf16.count * 2)
            }
            currentOffset += char.utf16.count
        }

        return Point(row: row, column: column)
    }

    private func coloredRanges(from highlights: [VVHighlighting.HighlightRange]) -> [ColoredRange] {
        highlights.map { highlight in
            ColoredRange(
                range: highlight.range,
                color: highlight.style.color.simdColor,
                fontVariant: FontVariant(
                    bold: highlight.style.isBold,
                    italic: highlight.style.isItalic
                )
            )
        }
    }

    private func replaceHighlights(in range: NSRange, with newRanges: [ColoredRange]) {
        let existing = normalizedRanges(coloredRanges.filter { NSIntersectionRange($0.range, range).length > 0 })
        let incoming = normalizedRanges(newRanges)
        if rangesEqual(existing, incoming) {
            return
        }

        let filtered = coloredRanges.filter { NSIntersectionRange($0.range, range).length == 0 }
        coloredRanges = filtered + incoming
        coloredRanges.sort { $0.range.location < $1.range.location }
        metalTextView.setHighlights(coloredRanges, invalidating: range)
    }

    private func applyHighlightEdit(range: NSRange, replacementLength: Int) {
        guard !coloredRanges.isEmpty else { return }

        let delta = replacementLength - range.length
        let editEnd = range.location + range.length
        var updated: [ColoredRange] = []
        updated.reserveCapacity(coloredRanges.count)

        for item in coloredRanges {
            let itemRange = item.range
            let itemEnd = itemRange.location + itemRange.length

            if itemRange.location >= editEnd {
                let shifted = NSRange(location: itemRange.location + delta, length: itemRange.length)
                updated.append(ColoredRange(range: shifted, color: item.color, fontVariant: item.fontVariant))
            } else if itemEnd <= range.location {
                updated.append(item)
            } else {
                // Keep overlapping highlights until new ones are ready to avoid flicker.
                updated.append(item)
            }
        }

        coloredRanges = updated
        if !suppressHighlightUpdates {
            metalTextView.setHighlights(coloredRanges, invalidating: dirtyRange(for: range, replacementLength: replacementLength))
        }
    }

    private func normalizedRanges(_ ranges: [ColoredRange]) -> [ColoredRange] {
        ranges.sorted {
            if $0.range.location != $1.range.location {
                return $0.range.location < $1.range.location
            }
            if $0.range.length != $1.range.length {
                return $0.range.length < $1.range.length
            }
            if $0.fontVariant != $1.fontVariant {
                return $0.fontVariant.rawValue < $1.fontVariant.rawValue
            }
            if $0.color != $1.color {
                let left = $0.color
                let right = $1.color
                if left.x != right.x { return left.x < right.x }
                if left.y != right.y { return left.y < right.y }
                if left.z != right.z { return left.z < right.z }
                return left.w < right.w
            }
            return false
        }
    }

    private func rangesEqual(_ lhs: [ColoredRange], _ rhs: [ColoredRange]) -> Bool {
        guard lhs.count == rhs.count else { return false }
        for (left, right) in zip(lhs, rhs) {
            if left.range.location != right.range.location { return false }
            if left.range.length != right.range.length { return false }
            if left.fontVariant != right.fontVariant { return false }
            if left.color != right.color { return false }
        }
        return true
    }

    private func dirtyRange(for range: NSRange, replacementLength: Int) -> NSRange {
        let length = max(range.length, replacementLength)
        return NSRange(location: range.location, length: max(1, length))
    }

    private func markDirtyHighlight(range: NSRange) {
        if let dirty = dirtyHighlightRange {
            dirtyHighlightRange = NSUnionRange(dirty, range)
        } else {
            dirtyHighlightRange = range
        }
    }

    private func lineAlignedRange(for range: NSRange) -> NSRange {
        guard let lineMap = lineMap else { return range }
        let startLine = max(0, lineMap.lineNumber(forOffset: range.location) - 1)
        let endOffset = max(range.location, range.location + max(0, range.length - 1))
        let endLine = max(0, lineMap.lineNumber(forOffset: endOffset) - 1)
        let startOffset = lineMapOffset(forLine: startLine)
        let endRange = lineMapRange(forLine: endLine)
        let end = endRange.start + endRange.length
        let length = max(0, end - startOffset)
        return NSRange(location: startOffset, length: length)
    }

    private func selectionLineRanges(from ranges: [NSRange]) -> [ClosedRange<Int>] {
        guard let lineMap = lineMap else { return [] }
        var result: [ClosedRange<Int>] = []
        result.reserveCapacity(ranges.count)
        for range in ranges where range.length > 0 {
            let startLine = max(0, lineMap.lineNumber(forOffset: range.location) - 1)
            let endOffset = max(range.location, range.location + max(0, range.length - 1))
            let endLine = max(0, lineMap.lineNumber(forOffset: endOffset) - 1)
            result.append(startLine...endLine)
        }
        guard !result.isEmpty else { return [] }
        let sorted = result.sorted { lhs, rhs in
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

    // MARK: - Text Editing

    private func insertText(_ text: String, at offset: Int) {
        ensureGlyphPreloadIfNeeded(with: text)
        replaceSelections(with: text, expandEmptyToChar: false)
        delegate?.editorDidChangeText(textStorage)
        onTextChange?(textStorage)
    }

    private func deleteText(in range: NSRange) {
        guard range.length > 0 else { return }
        selections = [Selection(anchor: range.location, cursor: range.location + range.length)]
        primarySelectionIndex = 0
        replaceSelections(with: "", expandEmptyToChar: true)
        delegate?.editorDidChangeText(textStorage)
        onTextChange?(textStorage)
    }

    private func clampRangeToDocument(_ range: NSRange) -> NSRange {
        let length = currentTextLengthUTF16()
        let safeLocation = max(0, min(range.location, length))
        let maxLength = max(0, length - safeLocation)
        let safeLength = max(0, min(range.length, maxLength))
        return NSRange(location: safeLocation, length: safeLength)
    }

    private func resolvedReplacementRange(_ replacementRange: NSRange) -> NSRange? {
        if replacementRange.location != NSNotFound {
            return clampRangeToDocument(replacementRange)
        }
        if let marked = markedTextRange {
            return clampRangeToDocument(marked)
        }
        if let selection = selectionRanges.first {
            return clampRangeToDocument(selection)
        }
        return nil
    }

    private func resolvedMarkedTextTargetRange(replacementRange: NSRange) -> NSRange {
        if let resolved = resolvedReplacementRange(replacementRange) {
            return resolved
        }
        return NSRange(location: currentTextLengthUTF16(), length: 0)
    }

    private func replaceRange(_ range: NSRange, with text: String, updateMarkedRange: Bool) {
        let clamped = clampRangeToDocument(range)
        selections = [Selection(anchor: clamped.location, cursor: clamped.location + clamped.length)]
        primarySelectionIndex = 0
        replaceSelections(with: text, expandEmptyToChar: false)
        if updateMarkedRange {
            let length = (text as NSString).length
            markedTextRange = NSRange(location: clamped.location, length: length)
            metalTextView?.setMarkedTextRange(markedTextRange)
        } else {
            markedTextRange = nil
            metalTextView?.setMarkedTextRange(nil)
        }
    }

    /// Convert 0-indexed line to LineMap 1-indexed
    private func lineMapOffset(forLine line: Int) -> Int {
        lineMap?.offset(forLine: line + 1) ?? 0
    }

    /// Get range for 0-indexed line
    private func lineMapRange(forLine line: Int) -> (start: Int, length: Int) {
        lineMap?.range(forLine: line + 1) ?? (0, 0)
    }

    /// Get 0-indexed position for offset
    private func lineMapPosition(forOffset offset: Int) -> (line: Int, column: Int) {
        guard let lineMap = lineMap else { return (0, 0) }
        let pos = lineMap.position(forOffset: offset)
        return (pos.line - 1, pos.column - 1)
    }

    private func lineLengthUTF16(forLine line: Int) -> Int {
        guard let lineMap = lineMap, line >= 0, line < lineMap.lineCount else { return 0 }
        let range = lineMapRange(forLine: line)
        let isLastLine = line == lineMap.lineCount - 1
        return max(0, range.length - (isLastLine ? 0 : 1))
    }
}

private final class MetalDocumentView: NSView {
    override var isFlipped: Bool { true }
}

// MARK: - HiddenInputViewDelegate

extension VVMetalEditorContainerView: HiddenInputViewDelegate {

    public func hiddenInputView(_ view: HiddenInputView, didInsertText text: String, replacementRange: NSRange) {
        if let range = resolvedReplacementRange(replacementRange), isComposingMarkedText || markedTextRange != nil || replacementRange.location != NSNotFound {
            replaceRange(range, with: text, updateMarkedRange: false)
            isComposingMarkedText = false
            markedTextRange = nil
            metalTextView?.setMarkedTextRange(nil)
            handleCompletionTrigger(for: text)
            return
        }
        replaceSelections(with: text, expandEmptyToChar: false)
        handleCompletionTrigger(for: text)
    }

    public func hiddenInputViewDidDeleteBackward(_ view: HiddenInputView) {
        deleteBackwardSelections()
    }

    public func hiddenInputViewDidDeleteForward(_ view: HiddenInputView) {
        deleteForwardSelections()
    }

    public func hiddenInputViewDidMoveUp(_ view: HiddenInputView) {
        let extend = helixMode == .select
        applyMotionToLineColumn(extendSelection: extend) { line, column in
            (line - 1, column)
        }
    }

    public func hiddenInputViewDidMoveDown(_ view: HiddenInputView) {
        let extend = helixMode == .select
        applyMotionToLineColumn(extendSelection: extend) { line, column in
            (line + 1, column)
        }
    }

    public func hiddenInputViewDidMoveLeft(_ view: HiddenInputView) {
        let extend = helixMode == .select
        applyMotion(extendSelection: extend) { max(0, $0.cursor - 1) }
    }

    public func hiddenInputViewDidMoveRight(_ view: HiddenInputView) {
        let extend = helixMode == .select
        applyMotion(extendSelection: extend) { min(currentTextLengthUTF16(), $0.cursor + 1) }
    }

    public func hiddenInputViewDidMoveWordLeft(_ view: HiddenInputView) {
        let extend = helixMode == .select
        applyMotion(extendSelection: extend) { previousWordOffset(from: $0.cursor, treatPunctuationAsWord: false) }
    }

    public func hiddenInputViewDidMoveWordRight(_ view: HiddenInputView) {
        let extend = helixMode == .select
        applyMotion(extendSelection: extend) { nextWordOffset(from: $0.cursor, treatPunctuationAsWord: false) }
    }

    public func hiddenInputViewDidMoveToBeginningOfLine(_ view: HiddenInputView) {
        let extend = helixMode == .select
        moveSelectionsToStartOfLine(extendSelection: extend, firstNonWhitespace: false)
    }

    public func hiddenInputViewDidMoveToEndOfLine(_ view: HiddenInputView) {
        let extend = helixMode == .select
        moveSelectionsToEndOfLine(extendSelection: extend)
    }

    public func hiddenInputViewDidMoveToBeginningOfDocument(_ view: HiddenInputView) {
        let extend = helixMode == .select
        applyMotion(extendSelection: extend) { _ in 0 }
    }

    public func hiddenInputViewDidMoveToEndOfDocument(_ view: HiddenInputView) {
        let extend = helixMode == .select
        applyMotion(extendSelection: extend) { _ in currentTextLengthUTF16() }
    }

    public func hiddenInputViewDidMoveUpAndModifySelection(_ view: HiddenInputView) {
        applyMotionToLineColumn(extendSelection: true) { line, column in
            (line - 1, column)
        }
    }

    public func hiddenInputViewDidMoveDownAndModifySelection(_ view: HiddenInputView) {
        applyMotionToLineColumn(extendSelection: true) { line, column in
            (line + 1, column)
        }
    }

    public func hiddenInputViewDidMoveLeftAndModifySelection(_ view: HiddenInputView) {
        applyMotion(extendSelection: true) { max(0, $0.cursor - 1) }
    }

    public func hiddenInputViewDidMoveRightAndModifySelection(_ view: HiddenInputView) {
        applyMotion(extendSelection: true) { min(currentTextLengthUTF16(), $0.cursor + 1) }
    }

    public func hiddenInputViewDidMoveWordLeftAndModifySelection(_ view: HiddenInputView) {
        applyMotion(extendSelection: true) { previousWordOffset(from: $0.cursor, treatPunctuationAsWord: false) }
    }

    public func hiddenInputViewDidMoveWordRightAndModifySelection(_ view: HiddenInputView) {
        applyMotion(extendSelection: true) { nextWordOffset(from: $0.cursor, treatPunctuationAsWord: false) }
    }

    public func hiddenInputViewDidMoveToBeginningOfLineAndModifySelection(_ view: HiddenInputView) {
        moveSelectionsToStartOfLine(extendSelection: true, firstNonWhitespace: false)
    }

    public func hiddenInputViewDidMoveToEndOfLineAndModifySelection(_ view: HiddenInputView) {
        moveSelectionsToEndOfLine(extendSelection: true)
    }

    public func hiddenInputViewDidSelectAll(_ view: HiddenInputView) {
        let length = (textStorage as NSString).length
        selections = [Selection(anchor: 0, cursor: length)]
        primarySelectionIndex = 0
        updateSelectionsDisplay()
    }

    public func hiddenInputViewDidCopy(_ view: HiddenInputView) {
        let ranges = selectionRangesForOperation(expandEmptyToChar: false).map { $0.range }
        guard !ranges.isEmpty else { return }
        let nsText = textStorage as NSString
        let selectedText = ranges.map { nsText.substring(with: $0) }.joined(separator: "\n")

        NSPasteboard.general.clearContents()
        NSPasteboard.general.setString(selectedText, forType: .string)
    }

    public func hiddenInputViewDidCut(_ view: HiddenInputView) {
        hiddenInputViewDidCopy(view)
        if let range = selectionRanges.first {
            deleteText(in: range)
            selectionRanges = []
        }
    }

    public func hiddenInputViewDidPaste(_ view: HiddenInputView) {
        guard let pasteString = NSPasteboard.general.string(forType: .string) else { return }
        replaceSelections(with: pasteString, expandEmptyToChar: false)
    }

    public func hiddenInputView(_ view: HiddenInputView, didSetMarkedText text: String, selectedRange: NSRange, replacementRange: NSRange) {
        if text.isEmpty {
            if let range = markedTextRange {
                replaceRange(range, with: "", updateMarkedRange: false)
            } else if replacementRange.location != NSNotFound {
                let clamped = clampRangeToDocument(replacementRange)
                if clamped.length > 0 {
                    replaceRange(clamped, with: "", updateMarkedRange: false)
                }
            }
            isComposingMarkedText = false
            markedTextRange = nil
            metalTextView?.setMarkedTextRange(nil)
            return
        }

        isComposingMarkedText = true
        let targetRange = resolvedMarkedTextTargetRange(replacementRange: replacementRange)
        replaceRange(targetRange, with: text, updateMarkedRange: true)
    }

    public func hiddenInputViewDidUnmarkText(_ view: HiddenInputView) {
        markedTextRange = nil
        metalTextView?.setMarkedTextRange(nil)
        isComposingMarkedText = false
    }

    public func hiddenInputView(_ view: HiddenInputView, shouldHandleKeyDown event: NSEvent) -> Bool {
        if metalTextView?.isCompletionVisible == true {
            switch event.keyCode {
            case 125: // Down
                completionSelectedIndex = min(completionSelectedIndex + 1, max(0, filteredCompletionItems.count - 1))
                metalTextView?.updateCompletionSelection(completionSelectedIndex)
                return true
            case 126: // Up
                completionSelectedIndex = max(0, completionSelectedIndex - 1)
                metalTextView?.updateCompletionSelection(completionSelectedIndex)
                return true
            case 36, 48: // Return or Tab
                applySelectedCompletion()
                return true
            case 53: // Esc
                cancelCompletions()
                return true
            default:
                break
            }
        }

        if searchOverlayActive && helixMode != .searchForward && helixMode != .searchBackward {
            return handleSearchOverlayKeyDown(event)
        }

        guard helixModeEnabled else {
            return false
        }

        if event.modifierFlags.contains(.command) {
            return false
        }

        if helixMode != .insert {
            // Swallow delete/backspace in non-insert modes.
            if event.keyCode == 51 || event.keyCode == 117 {
                return true
            }
        }

        if event.keyCode == 53 { // Esc
            helixMode = .normal
            collapseSelections(toStart: false)
            pendingGCommand = false
            pendingFind = nil
            return true
        }

        // Handle pending replace
        if helixMode == .replaceCharacter, let chars = event.charactersIgnoringModifiers, let ch = chars.first {
            helixMode = .normal
            replaceSelections(with: String(ch), expandEmptyToChar: true)
            return true
        }

        // Handle pending find
        if let pending = pendingFind, let chars = event.charactersIgnoringModifiers, let ch = chars.first {
            pendingFind = nil
            lastFindCharacter = ch
            lastFindForward = pending.forward
            applyFind(character: ch, forward: pending.forward, till: pending.till, extendSelection: helixMode == .select)
            return true
        }

        // Handle search input
        if helixMode == .searchForward || helixMode == .searchBackward {
            if event.keyCode == 53 { // Esc
                helixMode = .normal
                searchQuery = ""
                searchReturnMode = nil
                searchScope = .currentFile
                clearSearchHighlights()
                updateSearchOverlay()
                return true
            }
            if event.keyCode == 36 { // Return
                let forward = helixMode == .searchForward
                let wasSelect = searchReturnMode == .select
                helixMode = .normal
                lastSearchQuery = searchQuery
                lastSearchForward = forward
                if searchScope == .openDocuments {
                    onSearchOpenDocuments?(searchQuery)
                    if onSearchOpenDocuments == nil {
                        applySearch(query: searchQuery, forward: forward, extendSelection: wasSelect)
                    }
                } else {
                    applySearch(query: searchQuery, forward: forward, extendSelection: wasSelect)
                }
                searchQuery = ""
                searchReturnMode = nil
                searchScope = .currentFile
                updateSearchOverlay()
                return true
            }
            if event.keyCode == 51 { // Backspace
                if !searchQuery.isEmpty {
                    searchQuery.removeLast()
                    updateStatusBar()
                    _ = setSearchHighlights(query: searchQuery)
                    if searchQuery.isEmpty {
                        clearSearchHighlights()
                    }
                    updateSearchOverlay()
                }
                return true
            }
            if let chars = event.characters, !chars.isEmpty {
                searchQuery.append(chars)
                updateStatusBar()
                _ = setSearchHighlights(query: searchQuery)
                updateSearchOverlay()
                return true
            }
        }

        // Insert mode: allow typing, intercept Esc and mode commands.
        if helixMode == .insert {
            if event.keyCode == 53 { // Esc
                helixMode = .normal
                collapseSelections(toStart: false)
                return true
            }
            return false
        }

        guard let chars = event.charactersIgnoringModifiers, !chars.isEmpty else {
            return false
        }

        let ch = chars.first!
        let extendSelection = helixMode == .select

        if pendingGCommand && ch != "g" {
            pendingGCommand = false
        }

        switch ch {
        case "h":
            applyMotion(extendSelection: extendSelection) { max(0, $0.cursor - 1) }
        case "l":
            applyMotion(extendSelection: extendSelection) { min(currentTextLengthUTF16(), $0.cursor + 1) }
        case "j":
            applyMotionToLineColumn(extendSelection: extendSelection) { line, column in
                (line + 1, column)
            }
        case "k":
            applyMotionToLineColumn(extendSelection: extendSelection) { line, column in
                (line - 1, column)
            }
        case "w":
            applyMotion(extendSelection: extendSelection) { nextWordOffset(from: $0.cursor, treatPunctuationAsWord: false) }
        case "b":
            applyMotion(extendSelection: extendSelection) { previousWordOffset(from: $0.cursor, treatPunctuationAsWord: false) }
        case "e":
            applyMotion(extendSelection: extendSelection) { endOfWordOffset(from: $0.cursor, treatPunctuationAsWord: false) }
        case "W":
            applyMotion(extendSelection: extendSelection) { nextWordOffset(from: $0.cursor, treatPunctuationAsWord: true) }
        case "B":
            applyMotion(extendSelection: extendSelection) { previousWordOffset(from: $0.cursor, treatPunctuationAsWord: true) }
        case "E":
            applyMotion(extendSelection: extendSelection) { endOfWordOffset(from: $0.cursor, treatPunctuationAsWord: true) }
        case "0":
            moveSelectionsToStartOfLine(extendSelection: extendSelection, firstNonWhitespace: false)
        case "^":
            moveSelectionsToStartOfLine(extendSelection: extendSelection, firstNonWhitespace: true)
        case "$":
            moveSelectionsToEndOfLine(extendSelection: extendSelection)
        case "g":
            if pendingGCommand {
                pendingGCommand = false
                applyMotion(extendSelection: extendSelection) { _ in 0 }
            } else {
                pendingGCommand = true
            }
        case "G":
            applyMotion(extendSelection: extendSelection) { _ in currentTextLengthUTF16() }
        case "i":
            helixMode = .insert
            collapseSelections(toStart: true)
        case "a":
            helixMode = .insert
            collapseSelections(toStart: false)
        case "v":
            helixMode = (helixMode == .select) ? .normal : .select
        case "d":
            deleteSelections(expandEmptyToChar: true)
        case "x":
            deleteSelections(expandEmptyToChar: true)
        case "c":
            changeSelections(expandEmptyToChar: true)
        case "y":
            yankSelections(expandEmptyToChar: true)
        case "p":
            pasteSelections(before: false)
        case "P":
            pasteSelections(before: true)
        case "r":
            helixMode = .replaceCharacter
        case "/":
            searchReturnMode = helixMode
            helixMode = .searchForward
            searchQuery = ""
            searchScope = .currentFile
        case "?":
            searchReturnMode = helixMode
            helixMode = .searchBackward
            searchQuery = ""
            searchScope = .currentFile
        case "n":
            let forward = lastSearchForward
            applySearch(query: lastSearchQuery, forward: forward, extendSelection: extendSelection)
        case "N":
            let forward = !lastSearchForward
            applySearch(query: lastSearchQuery, forward: forward, extendSelection: extendSelection)
        case "f":
            pendingFind = PendingFind(forward: true, till: false)
        case "t":
            pendingFind = PendingFind(forward: true, till: true)
        case "F":
            pendingFind = PendingFind(forward: false, till: false)
        case "T":
            pendingFind = PendingFind(forward: false, till: true)
        case ";":
            if let last = lastFindCharacter {
                applyFind(character: last, forward: lastFindForward, till: false, extendSelection: extendSelection)
            }
        case ",":
            if let last = lastFindCharacter {
                applyFind(character: last, forward: !lastFindForward, till: false, extendSelection: extendSelection)
            }
        case "%":
            // Bracket matching (basic)
            let nsText = textStorage as NSString
            let length = nsText.length
            applyMotion(extendSelection: extendSelection) { selection in
                if length == 0 { return selection.cursor }
                let offset = max(0, min(selection.cursor, length - 1))
                let ch = nsText.character(at: offset)
                let pairs: [unichar: (match: unichar, forward: Bool)] = [
                    40: (41, true),  // (
                    91: (93, true),  // [
                    123: (125, true), // {
                    41: (40, false), // )
                    93: (91, false), // ]
                    125: (123, false) // }
                ]
                guard let pair = pairs[ch] else { return selection.cursor }
                var depth = 0
                if pair.forward {
                    var i = offset
                    while i < length {
                        let c = nsText.character(at: i)
                        if c == ch { depth += 1 }
                        if c == pair.match { depth -= 1 }
                        if depth == 0 { return i }
                        i += 1
                    }
                } else {
                    var i = offset
                    while true {
                        let c = nsText.character(at: i)
                        if c == ch { depth += 1 }
                        if c == pair.match { depth -= 1 }
                        if depth == 0 { return i }
                        if i == 0 { break }
                        i -= 1
                    }
                }
                return selection.cursor
            }
        case "\u{1b}":
            helixMode = .normal
            collapseSelections(toStart: false)
        default:
            // In non-insert modes, swallow printable input to avoid typing into the buffer.
            if helixMode != .insert {
                return true
            }
            return false
        }

        return true
    }

    public func hiddenInputViewDidRequestSearch(_ view: HiddenInputView, forward: Bool, scope: HiddenInputView.SearchScope) {
        let scopeValue: SearchScope = (scope == .openDocuments) ? .openDocuments : .currentFile
        beginSearchOverlay(scope: scopeValue, forward: forward)
    }

    public func hiddenInputViewDidRequestRepeatSearch(_ view: HiddenInputView, forward: Bool) {
        let query = searchQuery.isEmpty ? lastSearchQuery : searchQuery
        guard !query.isEmpty else {
            NSSound.beep()
            return
        }

        if helixModeEnabled && (helixMode == .select || helixMode == .normal) && !searchOverlayActive {
            let extendSelection = helixMode == .select
            applySearch(query: query, forward: forward, extendSelection: extendSelection)
            return
        }

        if searchScope == .openDocuments {
            onSearchOpenDocuments?(query)
            if onSearchOpenDocuments == nil {
                applySearch(query: query, forward: forward, extendSelection: false)
            }
        } else {
            applySearch(query: query, forward: forward, extendSelection: false)
        }

        lastSearchQuery = query
        lastSearchForward = forward
        updateSearchOverlay()
    }
}

// MARK: - MetalTextViewDelegate

extension VVMetalEditorContainerView: MetalTextViewDelegate {

    public func metalTextView(_ view: MetalTextView, didChangeText text: String) {
        // Not used - we manage text changes internally
    }

    public func metalTextView(_ view: MetalTextView, didChangeSelection ranges: [NSRange]) {
        // Not used - we manage selection internally
    }

    public func metalTextView(_ view: MetalTextView, didMoveCursor line: Int, column: Int) {
        // Not used - we manage cursor internally
    }

    public func metalTextView(_ view: MetalTextView, didClickAt point: CGPoint) {
        window?.makeFirstResponder(hiddenInputView)

        if let (line, column) = metalTextView.characterPosition(at: point) {
            if view.lastClickCount >= 3 {
                if let range = lineRange(for: line) {
                    selectionMode = .line
                    if view.lastMouseModifiers.contains(.shift) {
                        let anchor = selectionAnchorRange ?? lineRange(for: cursorLine) ?? range
                        selectionAnchorRange = anchor
                        let unioned = unionRange(anchor, range)
                        applySelection(unioned, updateAnchor: false)
                    } else {
                        selectionAnchorRange = range
                        applySelection(range)
                    }
                } else {
                    setCursor(line: line, column: column)
                }
            } else if view.lastClickCount == 2 {
                if let range = wordRange(atLine: line, column: column) {
                    selectionMode = .word
                    if view.lastMouseModifiers.contains(.shift) {
                        let anchor = selectionAnchorRange ?? wordRange(atLine: cursorLine, column: cursorColumn) ?? range
                        selectionAnchorRange = anchor
                        let unioned = unionRange(anchor, range)
                        applySelection(unioned, updateAnchor: false)
                    } else {
                        selectionAnchorRange = range
                        applySelection(range)
                    }
                } else {
                    setCursor(line: line, column: column)
                }
            } else if view.lastMouseModifiers.contains(.shift) {
                selectionMode = .character
                if selectionAnchorLine == nil || selectionAnchorColumn == nil {
                    setSelectionAnchor(line: cursorLine, column: cursorColumn)
                }
                updateSelection(toLine: line, column: column)
            } else {
                selectionMode = .character
                setCursor(line: line, column: column)
                setSelectionAnchor(line: line, column: column)
                selectionAnchorRange = nil
            }
        }
    }

    public func metalTextView(_ view: MetalTextView, didDragTo point: CGPoint) {
        if let (line, column) = metalTextView.characterPosition(at: point) {
            switch selectionMode {
            case .word:
                let anchor = selectionAnchorRange
                if let current = wordRange(atLine: line, column: column), let anchor = anchor {
                    let unioned = unionRange(anchor, current)
                    applySelection(unioned, updateAnchor: false)
                } else {
                    if selectionAnchorLine == nil || selectionAnchorColumn == nil {
                        setSelectionAnchor(line: cursorLine, column: cursorColumn)
                    }
                    updateSelection(toLine: line, column: column)
                }
            case .line:
                let anchor = selectionAnchorRange
                if let current = lineRange(for: line), let anchor = anchor {
                    let unioned = unionRange(anchor, current)
                    applySelection(unioned, updateAnchor: false)
                } else {
                    if selectionAnchorLine == nil || selectionAnchorColumn == nil {
                        setSelectionAnchor(line: cursorLine, column: cursorColumn)
                    }
                    updateSelection(toLine: line, column: column)
                }
            case .character:
                if selectionAnchorLine == nil || selectionAnchorColumn == nil {
                    setSelectionAnchor(line: cursorLine, column: cursorColumn)
                }
                updateSelection(toLine: line, column: column)
            }
        }
    }

    public func metalTextViewDidActivateSearchOverlay(_ view: MetalTextView) {
        if !isSearchOverlayVisible {
            beginSearchOverlay(scope: searchScope, forward: true)
        } else {
            window?.makeFirstResponder(hiddenInputView)
        }
    }

    public func metalTextViewDidRequestSearchPrev(_ view: MetalTextView) {
        performOverlaySearch(forward: false)
    }

    public func metalTextViewDidRequestSearchNext(_ view: MetalTextView) {
        performOverlaySearch(forward: true)
    }

    public func metalTextView(_ view: MetalTextView, didToggleSearchCase isCaseSensitive: Bool) {
        setSearchOptions(.init(caseSensitive: isCaseSensitive))
        updateSearchHighlightsForOverlay()
        updateSearchOverlay()
    }

    public func metalTextView(_ view: MetalTextView, didSetSearchScope scope: MetalTextView.SearchOverlayScope) {
        searchScope = (scope == .openDocuments) ? .openDocuments : .currentFile
        updateSearchHighlightsForOverlay()
        updateSearchOverlay()
    }
}
