import Foundation
import AppKit
import MetalKit
import Combine
import VVHighlighting
import SwiftTreeSitter

/// Metal-based editor container view - replaces VVEditorContainerView for GPU-accelerated rendering
public final class VVMetalEditorContainerView: NSView {

    // MARK: - Properties

    public private(set) var metalTextView: MetalTextView!
    public private(set) var gutterView: MetalGutterView!
    public private(set) var hiddenInputView: HiddenInputView!
    public private(set) var scrollView: NSScrollView!
    private var documentView: MetalDocumentView!

    private var renderer: MetalRenderer!
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
    private var lastFindCharacter: Character?
    private var lastFindForward: Bool = true
    private var pendingGCommand = false

    private struct PendingFind {
        var forward: Bool
        var till: Bool
    }
    private var pendingFind: PendingFind?

    private var statusBar: MetalStatusBarView!
    private let defaultStatusBarHeight: CGFloat = 22
    private var statusBarHeight: CGFloat { defaultStatusBarHeight }
    private var statusBarBottomInset: CGFloat {
        guard helixModeEnabled else { return 0 }
        return metalTextView?.lineHeight ?? defaultStatusBarHeight
    }
    private var statusBarTotalHeight: CGFloat {
        guard helixModeEnabled else { return 0 }
        return statusBarHeight + statusBarBottomInset
    }

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

    // Delegate
    public weak var delegate: VVEditorDelegate?

    // Public callbacks
    public var onTextChange: ((String) -> Void)?
    public var onSelectionChange: (([NSRange]) -> Void)?
    public var onCursorChange: ((Int, Int) -> Void)?

    // Callbacks (internal use)
    private var onTextChangeInternal: ((String) -> Void)?
    private var onSelectionChangeInternal: (([NSRange]) -> Void)?
    private var onCursorChangeInternal: ((Int, Int) -> Void)?

    // MARK: - Initialization

    public init(frame: CGRect, configuration: VVConfiguration, theme: VVTheme) {
        self._configuration = configuration
        self._theme = theme
        super.init(frame: frame)
        setupViews()
        applyConfiguration()
        applyTheme()
    }

    required init?(coder: NSCoder) {
        self._configuration = VVConfiguration()
        self._theme = VVTheme.defaultDark
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
        guard let device = MTLCreateSystemDefaultDevice() else {
            fatalError("Metal is not supported on this device")
        }

        // Create renderer
        do {
            renderer = try MetalRenderer(device: device, baseFont: _configuration.font)
        } catch {
            fatalError("Failed to create Metal renderer: \(error)")
        }

        // Create Metal text view
        metalTextView = MetalTextView(
            frame: bounds,
            device: device,
            font: _configuration.font
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

        // Create gutter view
        gutterView = MetalGutterView(frame: NSRect(x: 0, y: 0, width: 50, height: bounds.height), renderer: renderer)
        gutterView.baselineProvider = { [weak metalTextView] line in
            metalTextView?.baselineY(forLine: line)
        }
        gutterView.visibleLineRangeProvider = { [weak metalTextView] scrollOffset, height in
            metalTextView?.visibleLineRange(scrollOffset: scrollOffset, height: height) ?? (0, 0)
        }
        gutterView.linePresenceProvider = { [weak metalTextView] line in
            metalTextView?.baselineY(forLine: line) != nil
        }
        gutterView.lineForPointProvider = { [weak metalTextView] y in
            metalTextView?.documentLineIndex(atY: y)
        }
        gutterView.onToggleFold = { [weak self] line in
            self?.toggleFold(atLine: line)
        }

        // Create hidden input view
        hiddenInputView = HiddenInputView()
        hiddenInputView.inputDelegate = self
        hiddenInputView.metalTextView = metalTextView

        // Set delegate for mouse events
        metalTextView.textDelegate = self

        // Add subviews
        statusBar = MetalStatusBarView(
            frame: NSRect(x: 0, y: 0, width: bounds.width, height: defaultStatusBarHeight),
            renderer: renderer,
            font: _configuration.font
        )

        addSubview(gutterView)
        addSubview(scrollView)
        scrollView.addSubview(metalTextView)
        addSubview(hiddenInputView)
        addSubview(statusBar)

        // Setup scroll observation
        NotificationCenter.default.publisher(for: NSView.boundsDidChangeNotification, object: scrollView.contentView)
            .sink { [weak self] _ in
                self?.handleScroll()
            }
            .store(in: &cancellables)

        setupStatusBar()
        updateHelixUI()
        syncGutterInsets()
    }

    // MARK: - Layout

    override public func layout() {
        super.layout()

        let gutterWidth = gutterView.requiredWidth
        let reservedHeight = statusBarTotalHeight
        let availableHeight = max(0, bounds.height - reservedHeight)
        gutterView.frame = NSRect(x: 0, y: reservedHeight, width: gutterWidth, height: availableHeight)
        scrollView.frame = NSRect(x: gutterWidth, y: reservedHeight, width: bounds.width - gutterWidth, height: availableHeight)
        let barHeight = helixModeEnabled ? statusBarHeight : 0
        statusBar.frame = NSRect(x: 0, y: statusBarBottomInset, width: bounds.width, height: barHeight)

        updateContentSize()

        layoutStatusBar()
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
        if lastEditRange == nil {
            previousText = textStorage
        }
        if textChanged {
            lastParsedText = nil
        }
        lineMap = LineMap(text: textStorage)
        metalTextView.setText(textStorage)
        gutterView.setLineCount(lineMap?.lineCount ?? 0)
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
    public func setGitHunks(_ hunks: [MetalGutterView.GitHunk]) {
        gutterView.setGitHunks(hunks)
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
        gutterView.setSelectedLineRanges(selectionLineRanges(from: selectionRanges))

        let cursorPositions = selections.map { selection -> (line: Int, column: Int) in
            lineMapPosition(forOffset: selection.cursor)
        }

        if !cursorPositions.isEmpty {
            let primary = max(0, min(primarySelectionIndex, cursorPositions.count - 1))
            let primaryPos = cursorPositions[primary]
            cursorLine = primaryPos.line
            cursorColumn = primaryPos.column
            metalTextView.setCursors(cursorPositions, primaryIndex: primary)
            gutterView.currentLine = primaryPos.line
            delegate?.editorDidChangeCursorPosition(VVTextPosition(line: primaryPos.line, character: primaryPos.column))
        }
        updateBracketHighlight()
        updateActiveIndentGuides()
        updateStatusBar()
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
        let nsText = textStorage as NSString
        let length = nsText.length
        if length == 0 { return }

        let sorted = selections.enumerated().map { ($0.offset, $0.element) }
        var updated: [Selection] = selections

        for (index, selection) in sorted {
            if forward {
                let start = min(selection.cursor + 1, length)
                let range = NSRange(location: start, length: length - start)
                let found = nsText.range(of: query, options: [], range: range)
                if found.location != NSNotFound {
                    let cursor = found.location + found.length
                    let anchor = extendSelection ? selection.anchor : found.location
                    updated[index] = Selection(anchor: anchor, cursor: cursor)
                }
            } else {
                let start = max(0, min(selection.cursor - 1, length - 1))
                let range = NSRange(location: 0, length: start + 1)
                let found = nsText.range(of: query, options: [.backwards], range: range)
                if found.location != NSNotFound {
                    let cursor = found.location + found.length
                    let anchor = extendSelection ? selection.anchor : found.location
                    updated[index] = Selection(anchor: anchor, cursor: cursor)
                }
            }
        }

        selections = updated
        updateSelectionsDisplay()
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
        lineMap = LineMap(text: textStorage)
        gutterView.setLineCount(lineMap?.lineCount ?? 0)

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
        lineMap = LineMap(text: textStorage)
        gutterView.setLineCount(lineMap?.lineCount ?? 0)

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
        lineMap = LineMap(text: textStorage)
        gutterView.setLineCount(lineMap?.lineCount ?? 0)

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
        gutterView.setLineCount(lineMap?.lineCount ?? 0)

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
        let visibleRect = updateMetalViewport()
        gutterView.scrollOffset = visibleRect.origin.y

        // Trigger visible-range-only highlighting
        scheduleScrollHighlight()
    }

    // MARK: - Configuration

    private func applyConfiguration() {
        metalTextView?.setTextInsets(NSEdgeInsets(top: 4, left: 0, bottom: 4, right: 4))
        metalTextView?.updateFont(_configuration.font, lineHeightMultiplier: _configuration.lineHeight)
        gutterView?.setFont(_configuration.font)
        gutterView?.minimumWidth = _configuration.minimumGutterWidth
        gutterView?.setLineHeight(metalTextView.lineHeight, ascent: metalTextView.layoutEngine.calculatedBaselineOffset)
        statusBar?.setFont(_configuration.font)
        renderer?.updateFont(_configuration.font)
        setHelixModeEnabled(_configuration.helixModeEnabled)
        syncGutterInsets()

        // Update content size after font change
        updateContentSize()
        recomputeFolding()
    }

    private func syncGutterInsets() {
        guard let metalTextView = metalTextView else { return }
        var insets = gutterView.textInsets
        insets.top = metalTextView.textInsets.top
        insets.bottom = metalTextView.textInsets.bottom
        gutterView.textInsets = insets
        gutterView.verticalOffset = 0
    }

    private func updateModeIndicator() {
        updateCursorStyle()
        updateStatusBar()
    }

    private func updateHelixUI() {
        statusBar.isHidden = !helixModeEnabled
        updateModeIndicator()
        needsLayout = true
        layoutSubtreeIfNeeded()
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
        statusBar.setFont(_configuration.font)
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
            return searchQuery.isEmpty ? "SEARCH /" : "SEARCH / \(searchQuery)"
        case .searchBackward:
            return searchQuery.isEmpty ? "SEARCH ?" : "SEARCH ? \(searchQuery)"
        case .replaceCharacter:
            return "REPLACE"
        }
    }

    private func updateStatusBar() {
        guard helixModeEnabled else {
            statusBar?.setText(left: "", right: "")
            return
        }
        let mode = modeLabelText()
        let line = cursorLine + 1
        let column = cursorColumn + 1
        let selectionInfo = selections.count > 1 ? "\(selections.count) selections" : "1 selection"
        let info = "Ln \(line), Col \(column)  •  \(selectionInfo)"
        applyStatusBarModeStyle()
        statusBar.setText(left: mode, right: info)
        layoutStatusBar()
    }

    private func applyStatusBarModeStyle() {
        guard let statusBar = statusBar else { return }
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
        statusBar.modeBackgroundColor = background
        statusBar.modeTextColor = text
    }

    private func layoutStatusBar() {
        guard helixModeEnabled else { return }
        statusBar.frame = NSRect(x: 0, y: statusBarBottomInset, width: bounds.width, height: statusBarHeight)
    }

    private func updateContentSize() {
        guard let metalTextView = metalTextView else { return }

        let gutterWidth = gutterView?.requiredWidth ?? 0
        let contentSize = metalTextView.contentSize
        gutterView?.setLineHeight(metalTextView.lineHeight, ascent: metalTextView.layoutEngine.calculatedBaselineOffset)
        gutterView?.verticalOffset = 0
        let availableHeight = max(0, bounds.height - statusBarTotalHeight)
        let viewportWidth = max(0, scrollView.contentView.bounds.width)
        let viewportHeight = max(0, scrollView.contentView.bounds.height)
        let documentSize = CGSize(
            width: max(contentSize.width, viewportWidth),
            height: max(contentSize.height, viewportHeight)
        )

        // Update document view size for scrollbars
        documentView.frame = CGRect(origin: .zero, size: documentSize)

        // Update gutter height
        if let gutterView = gutterView {
            gutterView.frame = NSRect(
                x: 0,
                y: statusBarTotalHeight,
                width: gutterWidth,
                height: availableHeight
            )
        }

        updateMetalViewport()
    }

    @discardableResult
    private func updateMetalViewport() -> CGRect {
        let visibleRect = scrollView.documentVisibleRect
        let viewportSize = scrollView.contentView.bounds.size
        let viewportOrigin = scrollView.contentView.frame.origin
        metalTextView.scrollOffset = visibleRect.origin
        gutterView.scrollOffset = visibleRect.origin.y
        metalTextView.frame = CGRect(origin: viewportOrigin, size: viewportSize)
        return visibleRect
    }

    private func ensureGlyphPreloadIfNeeded(with text: String) {
        guard !didPreloadGlyphs else { return }
        guard !text.isEmpty else { return }
        renderer?.glyphAtlas.preloadASCII()
        didPreloadGlyphs = true
    }

    private func applyTheme() {
        metalTextView?.setBackgroundColor(_theme.backgroundColor)
        metalTextView?.setDefaultTextColor(_theme.textColor)
        metalTextView?.selectionColor = _theme.selectionColor
        metalTextView?.cursorColor = _theme.cursorColor
        metalTextView?.indentGuideColor = _theme.gutterSeparatorColor.withAlphaComponent(0.22)
        metalTextView?.indentGuideLinePadding = 0
        metalTextView?.indentGuideLineWidth = 1
        metalTextView?.activeIndentGuideColor = _theme.selectionColor.withAlphaComponent(0.5)
        metalTextView?.activeIndentGuideLineWidth = 1.5
        metalTextView?.bracketHighlightColor = _theme.selectionColor.withAlphaComponent(0.35)
        metalTextView?.foldPlaceholderColor = _theme.gutterTextColor.withAlphaComponent(0.8)

        gutterView?.setBackgroundColor(_theme.backgroundColor)
        gutterView?.lineNumberColor = _theme.gutterTextColor
        gutterView?.currentLineNumberColor = _theme.textColor
        gutterView?.selectedLineNumberColor = _theme.gutterActiveTextColor
        gutterView?.foldMarkerColor = _theme.gutterTextColor.withAlphaComponent(0.8)
        gutterView?.foldMarkerActiveColor = _theme.textColor
        gutterView?.foldMarkerHoverBackgroundColor = _theme.gutterSeparatorColor.withAlphaComponent(0.25)

        statusBar?.backgroundColor = _theme.gutterBackgroundColor
        statusBar?.borderColor = _theme.gutterSeparatorColor
        statusBar?.textColor = _theme.textColor
        statusBar?.secondaryTextColor = _theme.gutterTextColor
        applyStatusBarModeStyle()

        // Update highlight theme based on background brightness
        let brightness = _theme.backgroundColor.brightnessComponent
        highlightTheme = brightness < 0.5 ? .defaultDark : .defaultLight
        Task { await highlighter?.setTheme(highlightTheme) }
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
        gutterView?.setFoldRanges([], foldedStartLines: [])
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
        let gutterRanges = foldableRanges.map { MetalGutterView.FoldRange(startLine: $0.startLine, endLine: $0.endLine) }
        gutterView?.setFoldRanges(gutterRanges, foldedStartLines: foldedStartLines)
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
        let metalHunks = hunks.map { hunk -> MetalGutterView.GitHunk in
            let status: MetalGutterView.GitHunk.Status
            switch hunk.changeType {
            case .added: status = .added
            case .deleted: status = .deleted
            case .modified: status = .modified
            }
            return MetalGutterView.GitHunk(
                startLine: hunk.newStart - 1,  // Convert to 0-indexed
                lineCount: hunk.newCount,
                status: status
            )
        }
        gutterView.setGitHunks(metalHunks)
    }

    /// Set blame info (stub - not implemented for Metal yet)
    public func setBlameInfo(_ blame: [VVBlameInfo]) {
        // TODO: Implement blame overlay for Metal view
    }

    /// Set LSP client (stub - not implemented for Metal yet)
    public func setLSPClient(_ client: Any, documentURI: String) {
        // TODO: Implement LSP integration for Metal view
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
        replaceSelections(with: text, expandEmptyToChar: false)
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

    public func hiddenInputView(_ view: HiddenInputView, shouldHandleKeyDown event: NSEvent) -> Bool {
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
                return true
            }
            if event.keyCode == 36 { // Return
                let forward = helixMode == .searchForward
                let wasSelect = searchReturnMode == .select
                helixMode = .normal
                lastSearchQuery = searchQuery
                lastSearchForward = forward
                applySearch(query: searchQuery, forward: forward, extendSelection: wasSelect)
                searchQuery = ""
                searchReturnMode = nil
                return true
            }
            if event.keyCode == 51 { // Backspace
                if !searchQuery.isEmpty {
                    searchQuery.removeLast()
                    updateStatusBar()
                }
                return true
            }
            if let chars = event.characters, !chars.isEmpty {
                searchQuery.append(chars)
                updateStatusBar()
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
        case "?":
            searchReturnMode = helixMode
            helixMode = .searchBackward
            searchQuery = ""
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
                selectionRanges = []
                metalTextView.setSelection([])
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
}
