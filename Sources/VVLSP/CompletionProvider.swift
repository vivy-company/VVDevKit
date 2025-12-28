import AppKit
import Combine

/// Manages completion popup and insertion
public class CompletionProvider {
    // MARK: - Properties

    /// The text view to show completions in
    public weak var textView: NSTextView?

    /// LSP client for fetching completions
    public weak var lspClient: (any VVLSPClient)?

    /// Document URI for LSP requests
    public var documentURI: String?

    /// Current completion state
    private var state: CompletionState = .idle

    /// Completion window
    private var completionWindow: CompletionWindow?

    /// Current completion items
    private var items: [VVCompletionItem] = []

    /// Filtered items based on current prefix
    private var filteredItems: [VVCompletionItem] = []

    /// Selected index
    private var selectedIndex: Int = 0

    /// Trigger characters that auto-show completions
    public var triggerCharacters: Set<Character> = [".", "(", "<", "\"", "'", "/"]

    /// Minimum characters before showing completions
    public var minimumPrefixLength: Int = 1

    /// Debounce delay for completion requests
    public var debounceDelay: TimeInterval = 0.15

    /// Cancellable for current completion request
    private var cancellable: AnyCancellable?

    /// Debounce timer
    private var debounceTimer: Timer?

    /// Current completion prefix
    private var currentPrefix: String = ""

    /// Anchor position for current completion session
    private var anchorPosition: Int = 0

    // MARK: - Initialization

    public init(textView: NSTextView? = nil) {
        self.textView = textView
    }

    deinit {
        debounceTimer?.invalidate()
        debounceTimer = nil
        dismissCompletion()
    }

    // MARK: - Public Methods

    /// Trigger completion at current cursor position
    public func triggerCompletion() {
        triggerCompletion(at: cursorPosition(), triggerKind: .invoked, triggerCharacter: nil)
    }

    /// Trigger completion at a specific position with trigger info
    public func triggerCompletion(at position: VVTextPosition, triggerKind: VVCompletionTriggerKind, triggerCharacter: String?) {
        // Don't trigger if already loading
        guard state != .loading else { return }
        guard let lspClient = lspClient, let documentURI = documentURI else { return }

        // Update anchor position for filtering
        if let textView = textView {
            anchorPosition = textView.selectedRange().location
            if triggerCharacter != nil {
                // For trigger characters, anchor is before the character
                anchorPosition = max(0, anchorPosition - 1)
            }
        }

        state = .loading

        Task {
            do {
                let items = try await lspClient.completions(
                    at: position,
                    in: documentURI,
                    triggerKind: triggerKind,
                    triggerCharacter: triggerCharacter
                )

                await MainActor.run {
                    self.handleCompletionResponse(items)
                }
            } catch {
                await MainActor.run {
                    self.dismissCompletion()
                }
            }
        }
    }

    /// Handle text change - may trigger completions
    public func textDidChange(at range: NSRange, replacementString: String) {
        // Check if we should trigger completion
        if shouldTriggerCompletion(for: replacementString) {
            debounceTimer?.invalidate()
            debounceTimer = Timer.scheduledTimer(withTimeInterval: debounceDelay, repeats: false) { [weak self] _ in
                self?.triggerCompletion()
            }
        } else if state == .showing {
            // Update filter for existing completions
            updateFilter()
        }
    }

    /// Dismiss completions
    public func dismissCompletion() {
        state = .idle
        if let completionWindow = completionWindow {
            if let parent = completionWindow.parent {
                parent.removeChildWindow(completionWindow)
            }
            completionWindow.orderOut(nil)
        }
        items = []
        filteredItems = []
        selectedIndex = 0
        currentPrefix = ""
    }

    /// Select next completion item
    public func selectNext() {
        guard state == .showing, !filteredItems.isEmpty else { return }
        selectedIndex = (selectedIndex + 1) % filteredItems.count
        completionWindow?.selectRow(selectedIndex)
    }

    /// Select previous completion item
    public func selectPrevious() {
        guard state == .showing, !filteredItems.isEmpty else { return }
        selectedIndex = (selectedIndex - 1 + filteredItems.count) % filteredItems.count
        completionWindow?.selectRow(selectedIndex)
    }

    /// Accept current selection
    public func acceptSelection() {
        guard state == .showing,
              selectedIndex < filteredItems.count else { return }

        let item = filteredItems[selectedIndex]
        insertCompletion(item)
        dismissCompletion()
    }

    // MARK: - Private Methods

    private func shouldTriggerCompletion(for text: String) -> Bool {
        guard let char = text.first else { return false }

        // Trigger on trigger characters
        if triggerCharacters.contains(char) {
            return true
        }

        // Trigger on identifier characters if we have enough prefix
        if char.isLetter || char == "_" {
            let prefix = currentPrefix + text
            return prefix.count >= minimumPrefixLength
        }

        return false
    }

    private func cursorPosition() -> VVTextPosition {
        guard let textView = textView else {
            return VVTextPosition(line: 0, character: 0)
        }

        let location = textView.selectedRange().location
        let text = textView.string

        var line = 0
        var character = 0

        for (index, char) in text.enumerated() {
            if index >= location {
                break
            }
            if char == "\n" {
                line += 1
                character = 0
            } else {
                character += 1
            }
        }

        return VVTextPosition(line: line, character: character)
    }

    private func handleCompletionResponse(_ items: [VVCompletionItem]) {
        guard !items.isEmpty else {
            dismissCompletion()
            return
        }

        self.items = items
        self.filteredItems = items
        self.selectedIndex = 0
        self.state = .showing
        self.anchorPosition = textView?.selectedRange().location ?? 0

        showCompletionWindow()
    }

    private func updateFilter() {
        guard let textView = textView else { return }

        let currentPosition = textView.selectedRange().location
        let prefixLength = currentPosition - anchorPosition

        guard prefixLength >= 0 else {
            dismissCompletion()
            return
        }

        if prefixLength > 0 {
            let start = textView.string.index(textView.string.startIndex, offsetBy: anchorPosition)
            let end = textView.string.index(start, offsetBy: prefixLength)
            currentPrefix = String(textView.string[start..<end]).lowercased()
        } else {
            currentPrefix = ""
        }

        // Filter items
        if currentPrefix.isEmpty {
            filteredItems = items
        } else {
            filteredItems = items.filter { item in
                let filterText = (item.filterText ?? item.label).lowercased()
                return filterText.contains(currentPrefix)
            }
        }

        // Sort by relevance
        filteredItems.sort { a, b in
            let aText = (a.filterText ?? a.label).lowercased()
            let bText = (b.filterText ?? b.label).lowercased()

            let aStarts = aText.hasPrefix(currentPrefix)
            let bStarts = bText.hasPrefix(currentPrefix)

            if aStarts && !bStarts { return true }
            if !aStarts && bStarts { return false }

            return aText < bText
        }

        if filteredItems.isEmpty {
            dismissCompletion()
        } else {
            selectedIndex = 0
            completionWindow?.updateItems(filteredItems)
            completionWindow?.selectRow(selectedIndex)
        }
    }

    private func showCompletionWindow() {
        guard let textView = textView,
              let window = textView.window else { return }

        if completionWindow == nil {
            completionWindow = CompletionWindow()
            // Only accept on double-click, not on selection change
            completionWindow?.onAccept = { [weak self] index in
                self?.selectedIndex = index
                self?.acceptSelection()
            }
        }

        completionWindow?.updateItems(filteredItems)
        completionWindow?.selectRow(selectedIndex)

        // Position below cursor
        let cursorRect = textView.firstRect(forCharacterRange: textView.selectedRange(), actualRange: nil)
        var origin = cursorRect.origin
        origin.y -= 4 // Small gap

        completionWindow?.setFrameTopLeftPoint(origin)
        completionWindow?.orderFront(nil)
        window.addChildWindow(completionWindow!, ordered: .above)
    }

    private func insertCompletion(_ item: VVCompletionItem) {
        guard let textView = textView else { return }

        let insertText = item.insertText

        // Replace from anchor to current position
        let currentPosition = textView.selectedRange().location
        let replaceRange = NSRange(location: anchorPosition, length: currentPosition - anchorPosition)

        textView.insertText(insertText, replacementRange: replaceRange)
    }
}

// MARK: - Completion State

private enum CompletionState {
    case idle
    case loading
    case showing
}

// MARK: - Completion Window

class CompletionWindow: NSPanel {
    private let tableView: NSTableView
    private let scrollView: NSScrollView

    /// Called when user accepts a completion (double-click or Enter)
    var onAccept: ((Int) -> Void)?

    private var items: [VVCompletionItem] = []

    override init(contentRect: NSRect, styleMask style: NSWindow.StyleMask, backing backingStoreType: NSWindow.BackingStoreType, defer flag: Bool) {
        tableView = NSTableView()
        scrollView = NSScrollView()

        super.init(contentRect: NSRect(x: 0, y: 0, width: 300, height: 200),
                   styleMask: [.borderless],
                   backing: .buffered,
                   defer: true)

        setupWindow()
        setupTableView()
    }

    convenience init() {
        self.init(contentRect: .zero, styleMask: [], backing: .buffered, defer: true)
    }

    private func setupWindow() {
        isOpaque = false
        backgroundColor = NSColor.windowBackgroundColor.withAlphaComponent(0.95)
        level = .floating
        hasShadow = true

        contentView?.wantsLayer = true
        contentView?.layer?.cornerRadius = 6
        contentView?.layer?.borderWidth = 1
        contentView?.layer?.borderColor = NSColor.separatorColor.cgColor
    }

    private func setupTableView() {
        tableView.delegate = self
        tableView.dataSource = self
        tableView.headerView = nil
        tableView.rowHeight = 24
        tableView.intercellSpacing = NSSize(width: 0, height: 2)
        tableView.backgroundColor = .clear
        tableView.doubleAction = #selector(tableViewDoubleClicked)
        tableView.target = self

        let column = NSTableColumn(identifier: NSUserInterfaceItemIdentifier("item"))
        column.width = 280
        tableView.addTableColumn(column)

        scrollView.documentView = tableView
        scrollView.hasVerticalScroller = true
        scrollView.hasHorizontalScroller = false
        scrollView.autohidesScrollers = true
        scrollView.borderType = .noBorder
        scrollView.backgroundColor = .clear
        scrollView.drawsBackground = false

        contentView?.addSubview(scrollView)
        scrollView.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            scrollView.topAnchor.constraint(equalTo: contentView!.topAnchor, constant: 4),
            scrollView.leadingAnchor.constraint(equalTo: contentView!.leadingAnchor, constant: 4),
            scrollView.trailingAnchor.constraint(equalTo: contentView!.trailingAnchor, constant: -4),
            scrollView.bottomAnchor.constraint(equalTo: contentView!.bottomAnchor, constant: -4)
        ])
    }

    func updateItems(_ items: [VVCompletionItem]) {
        self.items = items
        tableView.reloadData()

        // Resize window based on item count
        let height = min(CGFloat(items.count) * tableView.rowHeight + 8, 300)
        setContentSize(NSSize(width: 300, height: height))
    }

    func selectRow(_ row: Int) {
        guard row >= 0 && row < items.count else { return }
        tableView.selectRowIndexes(IndexSet(integer: row), byExtendingSelection: false)
        tableView.scrollRowToVisible(row)
    }

    @objc private func tableViewDoubleClicked() {
        let row = tableView.clickedRow
        if row >= 0 {
            onAccept?(row)
        }
    }
}

extension CompletionWindow: NSTableViewDelegate, NSTableViewDataSource {
    func numberOfRows(in tableView: NSTableView) -> Int {
        items.count
    }

    func tableView(_ tableView: NSTableView, viewFor tableColumn: NSTableColumn?, row: Int) -> NSView? {
        let item = items[row]

        let cell = CompletionCellView()
        cell.configure(with: item)

        return cell
    }

    func tableViewSelectionDidChange(_ notification: Notification) {
        // Just track selection, don't auto-accept
    }
}

// MARK: - Completion Cell View

class CompletionCellView: NSView {
    private let iconView = NSImageView()
    private let labelField = NSTextField(labelWithString: "")
    private let detailField = NSTextField(labelWithString: "")

    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        setupViews()
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    private func setupViews() {
        iconView.translatesAutoresizingMaskIntoConstraints = false
        labelField.translatesAutoresizingMaskIntoConstraints = false
        detailField.translatesAutoresizingMaskIntoConstraints = false

        labelField.font = NSFont.systemFont(ofSize: 12)
        labelField.textColor = .labelColor
        labelField.lineBreakMode = .byTruncatingTail

        detailField.font = NSFont.systemFont(ofSize: 10)
        detailField.textColor = .secondaryLabelColor
        detailField.lineBreakMode = .byTruncatingTail

        addSubview(iconView)
        addSubview(labelField)
        addSubview(detailField)

        NSLayoutConstraint.activate([
            iconView.leadingAnchor.constraint(equalTo: leadingAnchor, constant: 4),
            iconView.centerYAnchor.constraint(equalTo: centerYAnchor),
            iconView.widthAnchor.constraint(equalToConstant: 16),
            iconView.heightAnchor.constraint(equalToConstant: 16),

            labelField.leadingAnchor.constraint(equalTo: iconView.trailingAnchor, constant: 4),
            labelField.centerYAnchor.constraint(equalTo: centerYAnchor),

            detailField.leadingAnchor.constraint(equalTo: labelField.trailingAnchor, constant: 8),
            detailField.trailingAnchor.constraint(lessThanOrEqualTo: trailingAnchor, constant: -4),
            detailField.centerYAnchor.constraint(equalTo: centerYAnchor)
        ])
    }

    func configure(with item: VVCompletionItem) {
        labelField.stringValue = item.label
        detailField.stringValue = item.detail ?? ""
        iconView.image = icon(for: item.kind)
    }

    private func icon(for kind: VVCompletionKind) -> NSImage? {
        let systemName: String
        switch kind {
        case .method, .function:
            systemName = "m.square"
        case .property, .field:
            systemName = "p.square"
        case .variable:
            systemName = "v.square"
        case .class, .struct:
            systemName = "c.square"
        case .interface:
            systemName = "i.square"
        case .module:
            systemName = "shippingbox"
        case .keyword:
            systemName = "k.square"
        case .snippet:
            systemName = "doc.text"
        case .text:
            systemName = "textformat"
        case .constant:
            systemName = "number.square"
        case .enum:
            systemName = "e.square"
        case .enumMember:
            systemName = "smallcircle.filled.circle"
        case .typeParameter:
            systemName = "t.square"
        case .file:
            systemName = "doc"
        case .folder:
            systemName = "folder"
        case .color:
            systemName = "paintpalette"
        case .unit, .value, .event, .operator, .reference, .constructor:
            systemName = "star.square"
        }

        return NSImage(systemSymbolName: systemName, accessibilityDescription: nil)
    }
}
