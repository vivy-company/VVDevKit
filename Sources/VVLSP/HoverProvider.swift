import AppKit
import Combine

/// Provides hover information from LSP
public class HoverProvider {
    // MARK: - Properties

    /// The text view
    public weak var textView: NSTextView?

    /// LSP client for hover requests
    public weak var lspClient: (any VVLSPClient)?

    /// Document URI for LSP requests
    public var documentURI: String?

    /// Delay before showing hover
    public var showDelay: TimeInterval = 0.5

    /// Tracking area for mouse events
    private var trackingArea: NSTrackingArea?

    /// Timer for delayed show
    private var showTimer: Timer?

    /// Current hover task
    private var hoverTask: Task<Void, Never>?

    /// Hover popup window
    private var hoverWindow: HoverWindow?

    /// Currently hovered position
    private var currentPosition: VVTextPosition?

    // MARK: - Initialization

    public init(textView: NSTextView? = nil) {
        self.textView = textView
        setupTracking()
    }

    deinit {
        showTimer?.invalidate()
        showTimer = nil
        if let textView = textView, let area = trackingArea {
            textView.removeTrackingArea(area)
        }
        trackingArea = nil
        if let hoverWindow = hoverWindow {
            if let parent = hoverWindow.parent {
                parent.removeChildWindow(hoverWindow)
            }
            hoverWindow.orderOut(nil)
        }
        hoverWindow = nil
        hoverTask?.cancel()
    }

    // MARK: - Setup

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

    // MARK: - Mouse Events

    @objc public func handleMouseMoved(at point: NSPoint) {
        guard let textView = textView,
              let layoutManager = textView.layoutManager,
              let textContainer = textView.textContainer else {
            hideHover()
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

        let position = textPositionAt(charIndex)

        // Skip if same position
        if position == currentPosition {
            return
        }

        currentPosition = position
        cancelPendingHover()

        // Schedule hover request
        showTimer = Timer.scheduledTimer(withTimeInterval: showDelay, repeats: false) { [weak self] _ in
            self?.requestHover(at: position, screenPoint: point)
        }
    }

    @objc public func handleMouseExited() {
        cancelPendingHover()
        hideHover()
        currentPosition = nil
    }

    // MARK: - Hover Request

    private func requestHover(at position: VVTextPosition, screenPoint: NSPoint) {
        guard let lspClient = lspClient,
              let documentURI = documentURI else {
            return
        }

        hoverTask?.cancel()

        hoverTask = Task {
            do {
                guard let hoverInfo = try await lspClient.hover(at: position, in: documentURI) else {
                    return
                }

                await MainActor.run {
                    self.showHover(hoverInfo, at: screenPoint)
                }
            } catch {
                // Silently ignore hover errors
            }
        }
    }

    private func cancelPendingHover() {
        showTimer?.invalidate()
        showTimer = nil
        hoverTask?.cancel()
    }

    // MARK: - Hover Display

    private func showHover(_ info: VVHoverInfo, at point: NSPoint) {
        guard let textView = textView,
              let window = textView.window else {
            return
        }

        if hoverWindow == nil {
            hoverWindow = HoverWindow()
        }

        hoverWindow?.update(with: info)

        let screenPoint = window.convertPoint(toScreen: point)
        hoverWindow?.setFrameTopLeftPoint(NSPoint(x: screenPoint.x + 10, y: screenPoint.y - 10))
        hoverWindow?.orderFront(nil)
        window.addChildWindow(hoverWindow!, ordered: .above)
    }

    private func hideHover() {
        if let hoverWindow = hoverWindow {
            if let parent = hoverWindow.parent {
                parent.removeChildWindow(hoverWindow)
            }
            hoverWindow.orderOut(nil)
        }
    }

    // MARK: - Helpers

    private func textPositionAt(_ charIndex: Int) -> VVTextPosition {
        guard let textView = textView else {
            return VVTextPosition(line: 0, character: 0)
        }

        let text = textView.string
        var line = 0
        var character = 0

        for (index, char) in text.enumerated() {
            if index >= charIndex {
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
}

// MARK: - Hover Window

class HoverWindow: NSPanel {
    private let contentScrollView: NSScrollView
    private let contentTextView: NSTextView

    private let maxWidth: CGFloat = 500
    private let maxHeight: CGFloat = 300
    private let padding: CGFloat = 8

    override init(contentRect: NSRect, styleMask style: NSWindow.StyleMask, backing backingStoreType: NSWindow.BackingStoreType, defer flag: Bool) {
        contentScrollView = NSScrollView()
        contentTextView = NSTextView()

        super.init(contentRect: NSRect(x: 0, y: 0, width: 300, height: 100),
                   styleMask: [.borderless],
                   backing: .buffered,
                   defer: true)

        setupWindow()
        setupContent()
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

    private func setupContent() {
        contentTextView.isEditable = false
        contentTextView.isSelectable = true
        contentTextView.backgroundColor = .clear
        contentTextView.drawsBackground = false
        contentTextView.isRichText = true
        contentTextView.textContainerInset = NSSize(width: padding, height: padding)

        contentScrollView.documentView = contentTextView
        contentScrollView.hasVerticalScroller = true
        contentScrollView.hasHorizontalScroller = false
        contentScrollView.autohidesScrollers = true
        contentScrollView.borderType = .noBorder
        contentScrollView.backgroundColor = .clear
        contentScrollView.drawsBackground = false

        contentView?.addSubview(contentScrollView)
        contentScrollView.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            contentScrollView.topAnchor.constraint(equalTo: contentView!.topAnchor),
            contentScrollView.leadingAnchor.constraint(equalTo: contentView!.leadingAnchor),
            contentScrollView.trailingAnchor.constraint(equalTo: contentView!.trailingAnchor),
            contentScrollView.bottomAnchor.constraint(equalTo: contentView!.bottomAnchor)
        ])
    }

    func update(with info: VVHoverInfo) {
        let attributedString = renderContent(info)
        contentTextView.textStorage?.setAttributedString(attributedString)

        // Calculate size
        let layoutManager = contentTextView.layoutManager!
        let textContainer = contentTextView.textContainer!

        textContainer.containerSize = NSSize(width: maxWidth - padding * 2, height: CGFloat.greatestFiniteMagnitude)
        layoutManager.ensureLayout(for: textContainer)

        let usedRect = layoutManager.usedRect(for: textContainer)
        let width = min(usedRect.width + padding * 2, maxWidth)
        let height = min(usedRect.height + padding * 2, maxHeight)

        setContentSize(NSSize(width: width, height: height))
    }

    private func renderContent(_ info: VVHoverInfo) -> NSAttributedString {
        let result = NSMutableAttributedString()

        for content in info.contents {
            if result.length > 0 {
                result.append(NSAttributedString(string: "\n\n"))
            }

            if content.kind == .markdown && content.value.hasPrefix("```") {
                // Code block
                let codeContent = extractCodeBlock(from: content.value)
                let codeAttrs: [NSAttributedString.Key: Any] = [
                    .font: NSFont.monospacedSystemFont(ofSize: 12, weight: .regular),
                    .foregroundColor: NSColor.labelColor
                ]
                result.append(NSAttributedString(string: codeContent, attributes: codeAttrs))
            } else {
                // Regular text
                let attrs: [NSAttributedString.Key: Any] = [
                    .font: NSFont.systemFont(ofSize: 12),
                    .foregroundColor: NSColor.labelColor
                ]
                result.append(NSAttributedString(string: content.value, attributes: attrs))
            }
        }

        return result
    }

    private func extractCodeBlock(from markdown: String) -> String {
        // Remove markdown code fence
        var lines = markdown.components(separatedBy: "\n")

        // Remove first line if it's a fence
        if lines.first?.hasPrefix("```") == true {
            lines.removeFirst()
        }

        // Remove last line if it's a fence
        if lines.last?.hasPrefix("```") == true {
            lines.removeLast()
        }

        return lines.joined(separator: "\n")
    }
}

// MARK: - VVHoverInfo Extension

extension VVHoverInfo: Equatable {
    public static func == (lhs: VVHoverInfo, rhs: VVHoverInfo) -> Bool {
        lhs.contents == rhs.contents
    }
}
