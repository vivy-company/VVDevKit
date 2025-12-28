import AppKit
import VVHighlighting
import SwiftTreeSitter
import VVLSP

/// Main container view for the code editor
public class VVEditorContainerView: NSView {
    // MARK: - Subviews

    private let scrollView: NSScrollView
    private let textView: NSTextView
    private let gutterView: GutterView
    private let pieceTableStorage: PieceTableTextStorage

    // MARK: - State

    private var configuration: VVConfiguration
    private var theme: VVTheme
    private var language: VVLanguage?
    private var gitHunks: [VVDiffHunk] = []
    private var blameInfo: [VVBlameInfo] = []
    private var cachedLineCount: Int = 1

    // MARK: - Syntax Highlighting

    private let highlighter: TreeSitterHighlighter
    private var languageConfig: VVHighlighting.LanguageConfiguration?
    private var highlightTask: Task<Void, Never>?
    private var highlightDebounceTimer: Timer?
    private var textChangeDebounceTimer: Timer?
    private var isUserEditing = false
    private var previousText: String = ""
    private var lastEditRange: NSRange?
    private var lastReplacementLength: Int = 0
    private var lastHighlightedRange: NSRange?

    // MARK: - LSP Integration

    private var lspClient: (any VVLSPClient)?
    private var completionProvider: CompletionProvider?
    private var documentURI: String?
    private var documentVersion: Int = 0
    private var completionDebounceTimer: Timer?
    private var lastTypedCharacter: Character?

    /// Characters that trigger immediate completion
    private let immediateTriggerCharacters: Set<Character> = [".", "(", "<", ":", "/", "@"]

    /// Characters that trigger delayed completion (identifiers)
    private let delayedTriggerCharacters = CharacterSet.alphanumerics.union(CharacterSet(charactersIn: "_"))

    // MARK: - Delegate

    public weak var delegate: VVEditorDelegate?

    // MARK: - Public Properties

    public var text: String {
        textView.string
    }

    // MARK: - Initialization

    public init(frame: NSRect, configuration: VVConfiguration, theme: VVTheme) {
        self.configuration = configuration
        self.theme = theme
        self.highlighter = TreeSitterHighlighter(theme: .defaultDark)

        // Create text system with PieceTableTextStorage for O(log n) editing
        pieceTableStorage = PieceTableTextStorage()

        let layoutManager = NSLayoutManager()
        pieceTableStorage.addLayoutManager(layoutManager)

        let textContainer = NSTextContainer(containerSize: NSSize(
            width: frame.width,
            height: CGFloat.greatestFiniteMagnitude
        ))
        textContainer.widthTracksTextView = true
        layoutManager.addTextContainer(textContainer)

        // Create text view with custom storage
        textView = NSTextView(frame: NSRect(origin: .zero, size: frame.size), textContainer: textContainer)

        // Create scroll view manually
        scrollView = NSScrollView(frame: frame)
        scrollView.documentView = textView

        // Create gutter
        gutterView = GutterView(frame: NSRect(x: 0, y: 0, width: configuration.minimumGutterWidth, height: frame.height))

        super.init(frame: frame)

        setupViews()
        applyConfiguration()
        applyTheme()
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    // MARK: - Setup

    private func setupViews() {
        // Use frame-based layout (more reliable with NSViewRepresentable)

        // Add gutter first (renders on top)
        addSubview(gutterView)
        gutterView.textView = textView

        // Configure scroll view
        scrollView.hasVerticalScroller = true
        scrollView.hasHorizontalScroller = !configuration.wrapLines
        scrollView.autohidesScrollers = true
        scrollView.borderType = .noBorder
        addSubview(scrollView)

        // Configure text view for code editing
        textView.isRichText = false
        textView.allowsUndo = true
        textView.isEditable = true
        textView.isSelectable = true
        textView.drawsBackground = true
        textView.textContainerInset = NSSize(width: 4, height: 4)
        textView.delegate = self

        // Essential for proper scrolling with manual text system setup
        textView.minSize = NSSize(width: 0, height: 0)
        textView.maxSize = NSSize(width: CGFloat.greatestFiniteMagnitude, height: CGFloat.greatestFiniteMagnitude)
        textView.isVerticallyResizable = true
        textView.autoresizingMask = [.width]

        // Configure text container for wrapping behavior
        if !configuration.wrapLines {
            textView.textContainer?.containerSize = NSSize(width: CGFloat.greatestFiniteMagnitude, height: CGFloat.greatestFiniteMagnitude)
            textView.textContainer?.widthTracksTextView = false
            textView.isHorizontallyResizable = true
        }

        // Observe scroll changes
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(scrollViewDidScroll(_:)),
            name: NSView.boundsDidChangeNotification,
            object: scrollView.contentView
        )

        // Observe text changes
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(textDidChange(_:)),
            name: NSText.didChangeNotification,
            object: textView
        )
    }

    // MARK: - Public Methods

    public func setText(_ text: String) {
        // Skip if user is currently editing (prevents cursor jump)
        guard !isUserEditing else { return }
        guard textView.string != text else { return }

        textView.string = text
        textView.needsDisplay = true

        cachedLineCount = LineMap.lineCount(in: text)
        gutterView.updateLineCount(cachedLineCount)
        gutterView.setNeedsDisplay(gutterView.bounds)

        // Highlight after initial text set (if language configured)
        if languageConfig != nil {
            highlightSyntax()
        }
    }

    public func setLanguage(_ language: VVLanguage) {
        guard self.language?.identifier != language.identifier else { return }
        self.language = language

        // Configure tree-sitter for this language from registry
        Task {
            do {
                if let config = LanguageRegistry.shared.language(for: language.identifier) {
                    self.languageConfig = config
                    try await highlighter.setLanguage(config)
                    await highlightSyntaxAsync()
                }
            } catch {
                #if DEBUG
                print("[Editor] Failed to configure language: \(error)")
                #endif
            }
        }
    }

    public func setTheme(_ theme: VVTheme) {
        guard self.theme != theme else { return }
        self.theme = theme
        applyTheme()
    }

    public func setConfiguration(_ configuration: VVConfiguration) {
        guard self.configuration != configuration else { return }
        self.configuration = configuration
        applyConfiguration()
    }

    public func setGitHunks(_ hunks: [VVDiffHunk]) {
        self.gitHunks = hunks
        gutterView.setGitHunks(hunks)
    }

    public func setBlameInfo(_ blame: [VVBlameInfo]) {
        self.blameInfo = blame
    }

    /// Set LSP client for completions and diagnostics
    public func setLSPClient(_ client: (any VVLSPClient)?, documentURI: String?) {
        self.lspClient = client
        self.documentURI = documentURI

        // Setup completion provider
        if let client = client {
            completionProvider = CompletionProvider(textView: textView)
            completionProvider?.lspClient = client
            completionProvider?.documentURI = documentURI

            // Notify document opened
            if let uri = documentURI, let lang = language?.identifier {
                Task {
                    await client.documentOpened(uri, text: textView.string, language: lang)
                }
            }
        } else {
            completionProvider = nil
        }
    }

    /// Trigger completion at current cursor position
    public func triggerCompletion() {
        completionProvider?.triggerCompletion()
    }

    // MARK: - Configuration

    private func applyConfiguration() {
        textView.font = configuration.font

        // Line height
        let paragraphStyle = NSMutableParagraphStyle()
        paragraphStyle.lineHeightMultiple = configuration.lineHeight
        textView.defaultParagraphStyle = paragraphStyle

        // Wrapping
        if configuration.wrapLines {
            textView.textContainer?.widthTracksTextView = true
            textView.isHorizontallyResizable = false
        } else {
            textView.textContainer?.widthTracksTextView = false
            textView.isHorizontallyResizable = true
            textView.textContainer?.containerSize = NSSize(width: CGFloat.greatestFiniteMagnitude, height: CGFloat.greatestFiniteMagnitude)
        }

        // Gutter visibility
        gutterView.isHidden = !configuration.showGutter
        gutterView.showLineNumbers = configuration.showLineNumbers
        gutterView.showGitGutter = configuration.showGitGutter

        needsLayout = true
    }

    private func applyTheme() {
        // Background
        textView.backgroundColor = theme.backgroundColor
        scrollView.backgroundColor = theme.backgroundColor

        // Text color
        textView.textColor = theme.textColor
        textView.insertionPointColor = theme.cursorColor

        // Selection
        textView.selectedTextAttributes = [
            .backgroundColor: theme.selectionColor,
            .foregroundColor: theme.textColor
        ]

        // Gutter
        gutterView.backgroundColor = theme.gutterBackgroundColor
        gutterView.textColor = theme.gutterTextColor
        gutterView.activeTextColor = theme.gutterActiveTextColor
        gutterView.separatorColor = theme.gutterSeparatorColor
        gutterView.gitAddedColor = theme.gitAddedColor
        gutterView.gitModifiedColor = theme.gitModifiedColor
        gutterView.gitDeletedColor = theme.gitDeletedColor

        // Re-highlight with new theme colors
        highlightSyntax()
    }

    // MARK: - Syntax Highlighting (Tree-sitter)

    private func highlightSyntax() {
        highlightTask?.cancel()
        highlightTask = Task {
            await highlightSyntaxAsync()
        }
    }

    @MainActor
    private func highlightSyntaxAsync() async {
        guard let textStorage = textView.textStorage, textStorage.length > 0 else { return }
        guard languageConfig != nil else { return }

        let text = textStorage.string

        // Calculate visible range with padding for smooth scrolling
        let visibleRange = calculateVisibleRangeWithPadding()

        do {
            // Use incremental parsing if we have edit info
            if let editRange = lastEditRange, !previousText.isEmpty {
                let edit = createInputEdit(
                    oldText: previousText,
                    newText: text,
                    editRange: editRange,
                    replacementLength: lastReplacementLength
                )
                _ = try await highlighter.parseIncremental(text: text, edit: edit)
                lastEditRange = nil  // Clear after use
            } else {
                // Full parse for initial load or when edit info not available
                _ = try await highlighter.parse(text)
            }
            previousText = text
            lastHighlightedRange = nil  // Invalidate scroll cache after text change

            // Check for cancellation
            try Task.checkCancellation()

            // Get highlights only for visible range (like Helix viewport optimization)
            let highlights = try await highlighter.highlights(in: visibleRange)

            // Check if text changed during async operation
            guard textStorage.string == text else { return }

            // Apply base + highlights in ONE atomic operation (no flicker)
            textStorage.beginEditing()

            // Set base styling only for visible range
            let safeRange = NSIntersectionRange(visibleRange, NSRange(location: 0, length: textStorage.length))
            if safeRange.length > 0 {
                textStorage.setAttributes(
                    [
                        .font: configuration.font,
                        .foregroundColor: theme.textColor
                    ],
                    range: safeRange
                )
            }

            // Apply syntax highlights on top
            for highlight in highlights {
                guard highlight.range.location >= 0,
                      highlight.range.location + highlight.range.length <= textStorage.length else {
                    continue
                }
                let attrs = highlight.style.attributes(baseFont: configuration.font)
                textStorage.addAttributes(attrs, range: highlight.range)
            }

            textStorage.endEditing()
        } catch is CancellationError {
            // Task was cancelled, ignore
        } catch {
            #if DEBUG
            print("[Highlight] Error: \(error)")
            #endif
        }
    }

    /// Calculate visible character range with padding for smooth scrolling
    private func calculateVisibleRangeWithPadding() -> NSRange {
        guard let layoutManager = textView.layoutManager,
              let textContainer = textView.textContainer else {
            return NSRange(location: 0, length: textView.string.utf16.count)
        }

        let visibleRect = scrollView.documentVisibleRect

        // Add padding above and below visible area (4x viewport for fast scrolling)
        let paddedRect = visibleRect.insetBy(dx: 0, dy: -visibleRect.height * 1.5)

        // Convert to glyph range, then character range
        let glyphRange = layoutManager.glyphRange(forBoundingRect: paddedRect, in: textContainer)
        let charRange = layoutManager.characterRange(forGlyphRange: glyphRange, actualGlyphRange: nil)

        return charRange
    }

    /// Create tree-sitter InputEdit from NSRange edit info
    private func createInputEdit(oldText: String, newText: String, editRange: NSRange, replacementLength: Int) -> InputEdit {
        // Convert UTF-16 offsets to byte offsets (tree-sitter uses UTF-16 bytes internally)
        let startByte = UInt32(editRange.location * 2)  // UTF-16: 2 bytes per code unit
        let oldEndByte = UInt32((editRange.location + editRange.length) * 2)
        let newEndByte = UInt32((editRange.location + replacementLength) * 2)

        // Calculate line/column positions
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

    /// Convert character offset to tree-sitter Point (row, column)
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
                column += UInt32(char.utf16.count * 2)  // Bytes
            }
            currentOffset += char.utf16.count
        }

        return Point(row: row, column: column)
    }

    /// Count newlines in a range of text (for incremental line counting)
    private func countNewlines(in text: String, range: NSRange) -> Int {
        guard range.location >= 0, range.length > 0,
              range.location + range.length <= text.utf16.count else {
            return 0
        }
        let substring = (text as NSString).substring(with: range)
        return substring.filter { $0 == "\n" }.count
    }

    // MARK: - Notifications

    @objc private func scrollViewDidScroll(_ notification: Notification) {
        gutterView.setNeedsDisplay(gutterView.bounds)

        // Immediate highlight on scroll (no debounce) - use cached tree
        highlightVisibleRangeOnly()
    }

    /// Fast path: only apply highlights to newly visible areas using cached parse tree
    private func highlightVisibleRangeOnly() {
        guard let textStorage = textView.textStorage, textStorage.length > 0 else { return }
        guard languageConfig != nil else { return }

        let visibleRange = calculateVisibleRangeWithPadding()

        // Skip if this range was already highlighted
        if let lastRange = lastHighlightedRange,
           NSIntersectionRange(lastRange, visibleRange).length == visibleRange.length {
            return
        }

        highlightTask?.cancel()
        highlightTask = Task { @MainActor in
            do {
                // Use existing parse tree - just get highlights for new visible range
                let highlights = try await highlighter.highlights(in: visibleRange)

                guard textStorage.length > 0 else { return }

                textStorage.beginEditing()

                let safeRange = NSIntersectionRange(visibleRange, NSRange(location: 0, length: textStorage.length))
                if safeRange.length > 0 {
                    textStorage.setAttributes(
                        [.font: configuration.font, .foregroundColor: theme.textColor],
                        range: safeRange
                    )
                }

                for highlight in highlights {
                    guard highlight.range.location >= 0,
                          highlight.range.location + highlight.range.length <= textStorage.length else {
                        continue
                    }
                    textStorage.addAttributes(highlight.style.attributes(baseFont: configuration.font), range: highlight.range)
                }

                textStorage.endEditing()
                lastHighlightedRange = visibleRange
            } catch {
                // Ignore errors during scroll highlighting
            }
        }
    }

    @objc public func textDidChange(_ notification: Notification) {
        // Mark as user editing to prevent setText from resetting cursor
        isUserEditing = true

        // Debounce ALL work including gutter updates
        textChangeDebounceTimer?.invalidate()
        textChangeDebounceTimer = Timer.scheduledTimer(withTimeInterval: 0.03, repeats: false) { [weak self] _ in
            guard let self = self else { return }
            let text = self.textView.string

            // Incremental line count update (avoid O(n) scan)
            if let editRange = self.lastEditRange {
                // Count newlines in deleted text
                let deletedNewlines = self.previousText.isEmpty ? 0 :
                    self.countNewlines(in: self.previousText, range: editRange)
                // Count newlines in inserted text
                let insertedText = (text as NSString).substring(
                    with: NSRange(location: editRange.location, length: self.lastReplacementLength)
                )
                let insertedNewlines = insertedText.filter { $0 == "\n" }.count
                self.cachedLineCount += (insertedNewlines - deletedNewlines)
            } else {
                // Full recount if no edit info
                self.cachedLineCount = LineMap.lineCount(in: text)
            }

            self.gutterView.updateLineCount(self.cachedLineCount)
            self.gutterView.setNeedsDisplay(self.gutterView.bounds)

            // Notify delegate (triggers SwiftUI update)
            self.delegate?.editorDidChangeText(text)

            // Notify LSP of document change
            if let lspClient = self.lspClient, let uri = self.documentURI {
                self.documentVersion += 1
                Task {
                    await lspClient.documentChanged(uri, changes: [VVTextChange.full(text)])
                }
            }

            // Check for completion triggers
            self.checkCompletionTrigger()

            // Clear editing flag after SwiftUI has updated
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.05) {
                self.isUserEditing = false
            }
        }

        // Debounced syntax highlighting (longer delay)
        highlightDebounceTimer?.invalidate()
        highlightDebounceTimer = Timer.scheduledTimer(withTimeInterval: 0.3, repeats: false) { [weak self] _ in
            self?.highlightSyntax()
        }
    }

    // MARK: - Layout

    public override func layout() {
        super.layout()

        // Update gutter line count from cache
        gutterView.updateLineCount(cachedLineCount)

        // Calculate gutter width
        let gutterWidth = max(gutterView.frame.width, configuration.minimumGutterWidth)

        // Position gutter on the left
        gutterView.frame = NSRect(
            x: 0,
            y: 0,
            width: gutterWidth,
            height: bounds.height
        )

        // Position scroll view to the right of gutter
        scrollView.frame = NSRect(
            x: gutterWidth,
            y: 0,
            width: bounds.width - gutterWidth,
            height: bounds.height
        )
    }

    // MARK: - First Responder

    public override var acceptsFirstResponder: Bool { true }

    public override func becomeFirstResponder() -> Bool {
        window?.makeFirstResponder(textView)
        return true
    }

    public override func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        // Focus text view when added to window
        if window != nil {
            DispatchQueue.main.async { [weak self] in
                self?.window?.makeFirstResponder(self?.textView)
            }
        }
    }

    public func focusTextView() {
        if let window = window {
            window.makeFirstResponder(textView)
        }
    }

    deinit {
        NotificationCenter.default.removeObserver(self)
        highlightTask?.cancel()
        highlightDebounceTimer?.invalidate()
        highlightDebounceTimer = nil
        textChangeDebounceTimer?.invalidate()
        textChangeDebounceTimer = nil
        completionDebounceTimer?.invalidate()
        completionDebounceTimer = nil
    }
}

// MARK: - NSTextViewDelegate

extension VVEditorContainerView: NSTextViewDelegate {
    /// Capture edit info BEFORE the change happens (for incremental parsing)
    public func textView(_ textView: NSTextView, shouldChangeTextIn affectedCharRange: NSRange, replacementString: String?) -> Bool {
        // Store edit info for incremental tree-sitter parsing
        lastEditRange = affectedCharRange
        lastReplacementLength = replacementString?.utf16.count ?? 0
        previousText = textView.string

        // Track the typed character for completion triggering
        if let replacement = replacementString, replacement.count == 1 {
            lastTypedCharacter = replacement.first
        } else {
            lastTypedCharacter = nil
        }

        return true
    }

    /// Check if we should trigger completions after text change
    private func checkCompletionTrigger() {
        guard lspClient != nil, completionProvider != nil else { return }

        // Cancel any pending completion timer
        completionDebounceTimer?.invalidate()

        guard let char = lastTypedCharacter else { return }

        if immediateTriggerCharacters.contains(char) {
            // Immediate trigger for . ( < : / @
            triggerCompletion(character: String(char))
        } else if let scalar = char.unicodeScalars.first,
                  delayedTriggerCharacters.contains(scalar) {
            // Delayed trigger for identifiers (letters, numbers, _)
            completionDebounceTimer = Timer.scheduledTimer(withTimeInterval: 0.3, repeats: false) { [weak self] _ in
                self?.triggerCompletion(character: nil)
            }
        }

        lastTypedCharacter = nil
    }

    private func triggerCompletion(character: String?) {
        guard let completionProvider = completionProvider else { return }

        // Get current cursor position
        let selectedRange = textView.selectedRange()
        let position = LineMap.position(at: selectedRange.location, in: textView.string)
        let textPosition = VVTextPosition(line: position.line - 1, character: position.column - 1)

        // Trigger completion
        let triggerKind: VVCompletionTriggerKind = character != nil ? .triggerCharacter : .invoked
        completionProvider.triggerCompletion(at: textPosition, triggerKind: triggerKind, triggerCharacter: character)
    }

    public func textViewDidChangeSelection(_ notification: Notification) {
        let selectedRange = textView.selectedRange()
        delegate?.editorDidChangeSelection(selectedRange)

        // Update current line in gutter
        let position = LineMap.position(at: selectedRange.location, in: textView.string)
        gutterView.currentLine = position.line
        gutterView.setNeedsDisplay(gutterView.bounds)

        delegate?.editorDidChangeCursorPosition(VVTextPosition(line: position.line - 1, character: position.column - 1))
    }
}

// MARK: - Editor Delegate

public protocol VVEditorDelegate: AnyObject {
    func editorDidChangeText(_ text: String)
    func editorDidChangeSelection(_ range: NSRange)
    func editorDidChangeCursorPosition(_ position: VVTextPosition)
}
