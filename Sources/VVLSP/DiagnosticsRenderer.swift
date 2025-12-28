import AppKit
import Combine

/// Renders LSP diagnostics (errors, warnings, etc.) in the text view
public class DiagnosticsRenderer {
    // MARK: - Properties

    /// The text view to render diagnostics in
    public weak var textView: NSTextView?

    /// Current diagnostics by document URI
    private var diagnosticsByDocument: [String: [VVDiagnostic]] = [:]

    /// Current document URI
    public var documentURI: String?

    /// Subscription to diagnostics publisher
    private var cancellable: AnyCancellable?

    // MARK: - Colors

    public var errorColor: NSColor = .systemRed
    public var warningColor: NSColor = .systemYellow
    public var informationColor: NSColor = .systemBlue
    public var hintColor: NSColor = .systemGray

    // MARK: - Underline Style

    public var underlineStyle: NSUnderlineStyle = .patternDot

    // MARK: - Initialization

    public init(textView: NSTextView? = nil) {
        self.textView = textView
    }

    deinit {
        cancellable?.cancel()
        cancellable = nil
    }

    // MARK: - LSP Client Binding

    /// Subscribe to diagnostics from LSP client
    public func bind(to lspClient: any VVLSPClient) {
        cancellable = lspClient.diagnosticsPublisher
            .receive(on: DispatchQueue.main)
            .sink { [weak self] diagnostics in
                self?.handleDiagnostics(diagnostics)
            }
    }

    /// Unbind from LSP client
    public func unbind() {
        cancellable?.cancel()
        cancellable = nil
    }

    // MARK: - Diagnostics Handling

    private func handleDiagnostics(_ diagnostics: DocumentDiagnostics) {
        diagnosticsByDocument[diagnostics.uri] = diagnostics.diagnostics

        // Only re-render if this is the current document
        if diagnostics.uri == documentURI {
            render()
        }
    }

    /// Set diagnostics directly (for non-LSP use)
    public func setDiagnostics(_ diagnostics: [VVDiagnostic], for uri: String) {
        diagnosticsByDocument[uri] = diagnostics
        if uri == documentURI {
            render()
        }
    }

    /// Clear all diagnostics
    public func clearDiagnostics() {
        diagnosticsByDocument.removeAll()
        clearRenderedDiagnostics()
    }

    // MARK: - Rendering

    /// Render diagnostics in the text view
    public func render() {
        guard let textView = textView,
              let textStorage = textView.textStorage,
              let uri = documentURI else {
            return
        }

        // Clear existing diagnostic attributes
        clearRenderedDiagnostics()

        guard let diagnostics = diagnosticsByDocument[uri] else {
            return
        }

        let text = textView.string

        for diagnostic in diagnostics {
            guard let nsRange = convertToNSRange(diagnostic.range, in: text) else {
                continue
            }

            // Ensure range is valid
            guard nsRange.location >= 0,
                  nsRange.location + nsRange.length <= textStorage.length else {
                continue
            }

            let color = color(for: diagnostic.severity)

            // Add underline
            textStorage.addAttributes([
                .underlineStyle: underlineStyle.rawValue,
                .underlineColor: color,
                diagnosticKey: diagnostic
            ], range: nsRange)
        }
    }

    /// Clear rendered diagnostic attributes
    private func clearRenderedDiagnostics() {
        guard let textView = textView,
              let textStorage = textView.textStorage else {
            return
        }

        let fullRange = NSRange(location: 0, length: textStorage.length)
        textStorage.removeAttribute(.underlineStyle, range: fullRange)
        textStorage.removeAttribute(.underlineColor, range: fullRange)
        textStorage.removeAttribute(diagnosticKey, range: fullRange)
    }

    // MARK: - Queries

    /// Get diagnostics at a specific location
    public func diagnostics(at location: Int) -> [VVDiagnostic] {
        guard let textView = textView,
              let textStorage = textView.textStorage,
              location < textStorage.length else {
            return []
        }

        var results: [VVDiagnostic] = []

        textStorage.enumerateAttribute(diagnosticKey, in: NSRange(location: location, length: 1), options: []) { value, _, _ in
            if let diagnostic = value as? VVDiagnostic {
                results.append(diagnostic)
            }
        }

        return results
    }

    /// Get all diagnostics for current document
    public func currentDiagnostics() -> [VVDiagnostic] {
        guard let uri = documentURI else { return [] }
        return diagnosticsByDocument[uri] ?? []
    }

    /// Get diagnostics for a specific line
    public func diagnostics(forLine line: Int) -> [VVDiagnostic] {
        return currentDiagnostics().filter { diagnostic in
            diagnostic.range.start.line == line ||
            diagnostic.range.end.line == line ||
            (diagnostic.range.start.line < line && diagnostic.range.end.line > line)
        }
    }

    // MARK: - Helpers

    private func color(for severity: VVDiagnosticSeverity) -> NSColor {
        switch severity {
        case .error:
            return errorColor
        case .warning:
            return warningColor
        case .information:
            return informationColor
        case .hint:
            return hintColor
        }
    }

    private func convertToNSRange(_ range: VVTextRange, in text: String) -> NSRange? {
        var currentLine = 0
        var currentChar = 0
        var startOffset: Int?
        var endOffset: Int?

        for (index, char) in text.enumerated() {
            // Check for start position
            if currentLine == range.start.line && currentChar == range.start.character {
                startOffset = index
            }

            // Check for end position
            if currentLine == range.end.line && currentChar == range.end.character {
                endOffset = index
                break
            }

            if char == "\n" {
                currentLine += 1
                currentChar = 0
            } else {
                currentChar += 1
            }
        }

        // Handle end of file
        if endOffset == nil && currentLine == range.end.line {
            endOffset = text.count
        }

        guard let start = startOffset, let end = endOffset else {
            return nil
        }

        return NSRange(location: start, length: max(0, end - start))
    }

    /// Custom attribute key for storing diagnostic references
    private var diagnosticKey: NSAttributedString.Key {
        NSAttributedString.Key("VVDiagnostic")
    }
}

// MARK: - Diagnostic Tooltip Provider

public class DiagnosticTooltipProvider {
    public weak var textView: NSTextView?
    public weak var diagnosticsRenderer: DiagnosticsRenderer?

    private var trackingArea: NSTrackingArea?
    private var tooltipWindow: NSPanel?
    private var showTimer: Timer?

    public var showDelay: TimeInterval = 0.5

    public init(textView: NSTextView? = nil, diagnosticsRenderer: DiagnosticsRenderer? = nil) {
        self.textView = textView
        self.diagnosticsRenderer = diagnosticsRenderer
        setupTracking()
    }

    deinit {
        if let textView = textView, let area = trackingArea {
            textView.removeTrackingArea(area)
        }
        trackingArea = nil
        showTimer?.invalidate()
        showTimer = nil
        if let tooltipWindow = tooltipWindow {
            if let parent = tooltipWindow.parent {
                parent.removeChildWindow(tooltipWindow)
            }
            tooltipWindow.orderOut(nil)
        }
        tooltipWindow = nil
    }

    private func setupTracking() {
        guard let textView = textView else { return }

        let options: NSTrackingArea.Options = [
            .activeInKeyWindow,
            .mouseMoved,
            .mouseEnteredAndExited
        ]

        trackingArea = NSTrackingArea(
            rect: textView.bounds,
            options: options,
            owner: self,
            userInfo: nil
        )

        if let area = trackingArea {
            textView.addTrackingArea(area)
        }
    }

    public func updateTrackingArea() {
        guard let textView = textView, let oldArea = trackingArea else { return }

        textView.removeTrackingArea(oldArea)
        setupTracking()
    }

    @objc public func handleMouseMoved(at point: NSPoint) {
        guard let textView = textView,
              let layoutManager = textView.layoutManager,
              let textContainer = textView.textContainer else {
            hideTooltip()
            return
        }

        let textPoint = textView.convert(point, from: nil)
        let adjustedPoint = NSPoint(
            x: textPoint.x - textView.textContainerOrigin.x,
            y: textPoint.y - textView.textContainerOrigin.y
        )

        var fraction: CGFloat = 0
        let glyphIndex = layoutManager.glyphIndex(for: adjustedPoint, in: textContainer, fractionOfDistanceThroughGlyph: &fraction)
        let charIndex = layoutManager.characterIndexForGlyph(at: glyphIndex)

        let diagnostics = diagnosticsRenderer?.diagnostics(at: charIndex) ?? []

        if diagnostics.isEmpty {
            cancelShow()
            hideTooltip()
        } else {
            scheduleShow(diagnostics: diagnostics, at: point)
        }
    }

    @objc public func handleMouseExited() {
        cancelShow()
        hideTooltip()
    }

    private func scheduleShow(diagnostics: [VVDiagnostic], at point: NSPoint) {
        cancelShow()

        showTimer = Timer.scheduledTimer(withTimeInterval: showDelay, repeats: false) { [weak self] _ in
            self?.showTooltip(diagnostics: diagnostics, at: point)
        }
    }

    private func cancelShow() {
        showTimer?.invalidate()
        showTimer = nil
    }

    private func showTooltip(diagnostics: [VVDiagnostic], at point: NSPoint) {
        guard let textView = textView,
              let window = textView.window else {
            return
        }

        if tooltipWindow == nil {
            tooltipWindow = createTooltipWindow()
        }

        updateTooltipContent(diagnostics)

        let screenPoint = window.convertPoint(toScreen: point)
        tooltipWindow?.setFrameTopLeftPoint(NSPoint(x: screenPoint.x + 10, y: screenPoint.y - 10))
        tooltipWindow?.orderFront(nil)
        window.addChildWindow(tooltipWindow!, ordered: .above)
    }

    private func hideTooltip() {
        if let tooltipWindow = tooltipWindow {
            if let parent = tooltipWindow.parent {
                parent.removeChildWindow(tooltipWindow)
            }
            tooltipWindow.orderOut(nil)
        }
    }

    private func createTooltipWindow() -> NSPanel {
        let panel = NSPanel(
            contentRect: NSRect(x: 0, y: 0, width: 300, height: 100),
            styleMask: [.borderless],
            backing: .buffered,
            defer: true
        )

        panel.isOpaque = false
        panel.backgroundColor = NSColor.windowBackgroundColor.withAlphaComponent(0.95)
        panel.level = .floating
        panel.hasShadow = true

        panel.contentView?.wantsLayer = true
        panel.contentView?.layer?.cornerRadius = 6
        panel.contentView?.layer?.borderWidth = 1
        panel.contentView?.layer?.borderColor = NSColor.separatorColor.cgColor

        return panel
    }

    private func updateTooltipContent(_ diagnostics: [VVDiagnostic]) {
        guard let panel = tooltipWindow,
              let contentView = panel.contentView else { return }

        // Remove existing subviews
        contentView.subviews.forEach { $0.removeFromSuperview() }

        let stackView = NSStackView()
        stackView.orientation = .vertical
        stackView.alignment = .leading
        stackView.spacing = 8
        stackView.edgeInsets = NSEdgeInsets(top: 8, left: 8, bottom: 8, right: 8)

        for diagnostic in diagnostics {
            let messageView = createDiagnosticView(diagnostic)
            stackView.addArrangedSubview(messageView)
        }

        contentView.addSubview(stackView)
        stackView.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            stackView.topAnchor.constraint(equalTo: contentView.topAnchor),
            stackView.leadingAnchor.constraint(equalTo: contentView.leadingAnchor),
            stackView.trailingAnchor.constraint(equalTo: contentView.trailingAnchor),
            stackView.bottomAnchor.constraint(equalTo: contentView.bottomAnchor)
        ])

        panel.setContentSize(stackView.fittingSize)
    }

    private func createDiagnosticView(_ diagnostic: VVDiagnostic) -> NSView {
        let container = NSView()

        let iconView = NSImageView()
        iconView.image = icon(for: diagnostic.severity)
        iconView.contentTintColor = color(for: diagnostic.severity)

        let messageField = NSTextField(wrappingLabelWithString: diagnostic.message)
        messageField.font = NSFont.systemFont(ofSize: 11)
        messageField.textColor = .labelColor
        messageField.maximumNumberOfLines = 3

        container.addSubview(iconView)
        container.addSubview(messageField)

        iconView.translatesAutoresizingMaskIntoConstraints = false
        messageField.translatesAutoresizingMaskIntoConstraints = false

        NSLayoutConstraint.activate([
            iconView.leadingAnchor.constraint(equalTo: container.leadingAnchor),
            iconView.topAnchor.constraint(equalTo: container.topAnchor),
            iconView.widthAnchor.constraint(equalToConstant: 16),
            iconView.heightAnchor.constraint(equalToConstant: 16),

            messageField.leadingAnchor.constraint(equalTo: iconView.trailingAnchor, constant: 4),
            messageField.trailingAnchor.constraint(equalTo: container.trailingAnchor),
            messageField.topAnchor.constraint(equalTo: container.topAnchor),
            messageField.bottomAnchor.constraint(equalTo: container.bottomAnchor)
        ])

        return container
    }

    private func icon(for severity: VVDiagnosticSeverity) -> NSImage? {
        let systemName: String
        switch severity {
        case .error:
            systemName = "xmark.circle.fill"
        case .warning:
            systemName = "exclamationmark.triangle.fill"
        case .information:
            systemName = "info.circle.fill"
        case .hint:
            systemName = "lightbulb.fill"
        }
        return NSImage(systemSymbolName: systemName, accessibilityDescription: nil)
    }

    private func color(for severity: VVDiagnosticSeverity) -> NSColor {
        switch severity {
        case .error:
            return .systemRed
        case .warning:
            return .systemYellow
        case .information:
            return .systemBlue
        case .hint:
            return .systemGray
        }
    }
}
