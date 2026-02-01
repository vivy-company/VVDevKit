import AppKit
import Combine

/// Manages viewport-based rendering for large files
public class ViewportManager {
    // MARK: - Properties

    /// The text view being managed
    private weak var textView: NSTextView?

    /// Line map for efficient lookups
    private var lineMap: LineMap

    /// Buffer lines beyond visible viewport
    public var bufferLines: Int = 50

    /// Current visible line range (1-indexed, inclusive)
    public private(set) var visibleLineRange: ClosedRange<Int> = 1...1

    /// Extended range including buffer (1-indexed, inclusive)
    public private(set) var extendedLineRange: ClosedRange<Int> = 1...1

    /// Publisher for viewport changes
    public let viewportChanged = PassthroughSubject<ViewportChange, Never>()

    /// Last known scroll position
    private var lastScrollY: CGFloat = 0

    /// Debounce timer for viewport updates
    private var debounceTimer: Timer?

    // MARK: - Initialization

    public init(textView: NSTextView? = nil) {
        self.textView = textView
        self.lineMap = LineMap()

        if let textView = textView {
            setupObservers(for: textView)
        }
    }

    deinit {
        NotificationCenter.default.removeObserver(self)
        debounceTimer?.invalidate()
        debounceTimer = nil
    }

    // MARK: - Setup

    public func setTextView(_ textView: NSTextView) {
        self.textView = textView
        setupObservers(for: textView)
        updateText(textView.string)
    }

    private func setupObservers(for textView: NSTextView) {
        guard let scrollView = textView.enclosingScrollView else { return }

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(scrollViewDidScroll(_:)),
            name: NSView.boundsDidChangeNotification,
            object: scrollView.contentView
        )

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(textDidChange(_:)),
            name: NSText.didChangeNotification,
            object: textView
        )

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(frameDidChange(_:)),
            name: NSView.frameDidChangeNotification,
            object: textView
        )
    }

    // MARK: - Text Updates

    public func updateText(_ text: String) {
        lineMap = LineMap(text: text)
        updateViewport()
    }

    // MARK: - Viewport Calculation

    private func updateViewport() {
        guard let textView = textView,
              let layoutManager = textView.layoutManager,
              let textContainer = textView.textContainer else { return }

        let visibleRect = textView.visibleRect

        // Get glyph range for visible rect
        let glyphRange = layoutManager.glyphRange(forBoundingRect: visibleRect, in: textContainer)
        let charRange = layoutManager.characterRange(forGlyphRange: glyphRange, actualGlyphRange: nil)

        // Convert to line numbers
        let startLine = lineMap.lineNumber(forOffset: charRange.location)
        let endLine = lineMap.lineNumber(forOffset: charRange.location + charRange.length)

        let newVisibleRange = startLine...max(startLine, endLine)

        // Calculate extended range with buffer
        let totalLines = lineMap.lineCount
        let extendedStart = max(1, startLine - bufferLines)
        let extendedEnd = min(totalLines, endLine + bufferLines)
        let newExtendedRange = extendedStart...max(extendedStart, extendedEnd)

        // Check if viewport changed significantly
        let visibleChanged = newVisibleRange != visibleLineRange
        let extendedChanged = newExtendedRange != extendedLineRange

        if visibleChanged || extendedChanged {
            let oldVisibleRange = visibleLineRange
            let oldExtendedRange = extendedLineRange

            visibleLineRange = newVisibleRange
            extendedLineRange = newExtendedRange

            let change = ViewportChange(
                oldVisibleRange: oldVisibleRange,
                newVisibleRange: newVisibleRange,
                oldExtendedRange: oldExtendedRange,
                newExtendedRange: newExtendedRange,
                scrollDirection: detectScrollDirection()
            )

            viewportChanged.send(change)
        }
    }

    private func detectScrollDirection() -> ScrollDirection {
        guard let textView = textView else { return .none }

        let currentY = textView.visibleRect.origin.y
        let direction: ScrollDirection

        if currentY > lastScrollY {
            direction = .down
        } else if currentY < lastScrollY {
            direction = .up
        } else {
            direction = .none
        }

        lastScrollY = currentY
        return direction
    }

    // MARK: - Notifications

    @objc private func scrollViewDidScroll(_ notification: Notification) {
        // Debounce rapid scroll events
        debounceTimer?.invalidate()
        debounceTimer = Timer.scheduledTimer(withTimeInterval: 0.016, repeats: false) { [weak self] _ in
            self?.updateViewport()
        }
    }

    @objc private func textDidChange(_ notification: Notification) {
        guard let textView = textView else { return }
        updateText(textView.string)
    }

    @objc private func frameDidChange(_ notification: Notification) {
        updateViewport()
    }

    // MARK: - Queries

    /// Check if a line is currently visible
    public func isLineVisible(_ line: Int) -> Bool {
        visibleLineRange.contains(line)
    }

    /// Check if a line is in the extended (buffered) range
    public func isLineInBuffer(_ line: Int) -> Bool {
        extendedLineRange.contains(line)
    }

    /// Get lines that need to be rendered (entered the extended range)
    public func linesToRender(for change: ViewportChange) -> [Int] {
        let newLines = Set(change.newExtendedRange)
        let oldLines = Set(change.oldExtendedRange)
        return Array(newLines.subtracting(oldLines)).sorted()
    }

    /// Get lines that can be unloaded (left the extended range)
    public func linesToUnload(for change: ViewportChange) -> [Int] {
        let newLines = Set(change.newExtendedRange)
        let oldLines = Set(change.oldExtendedRange)
        return Array(oldLines.subtracting(newLines)).sorted()
    }

    /// Get the character range for the extended viewport
    public func extendedCharacterRange() -> NSRange {
        let startOffset = lineMap.offset(forLine: extendedLineRange.lowerBound)
        let endRange = lineMap.range(forLine: extendedLineRange.upperBound)
        let endOffset = endRange.start + endRange.length

        return NSRange(location: startOffset, length: endOffset - startOffset)
    }

    /// Scroll to a specific line
    public func scrollToLine(_ line: Int) {
        guard let textView = textView,
              let layoutManager = textView.layoutManager else { return }

        let offset = lineMap.offset(forLine: line)
        let glyphIndex = layoutManager.glyphIndexForCharacter(at: offset)
        let lineRect = layoutManager.lineFragmentRect(forGlyphAt: glyphIndex, effectiveRange: nil)

        textView.scroll(lineRect.origin)
    }
}

// MARK: - Supporting Types

public struct ViewportChange {
    public let oldVisibleRange: ClosedRange<Int>
    public let newVisibleRange: ClosedRange<Int>
    public let oldExtendedRange: ClosedRange<Int>
    public let newExtendedRange: ClosedRange<Int>
    public let scrollDirection: ScrollDirection

    /// Lines that became visible
    public var newlyVisibleLines: [Int] {
        let newLines = Set(newVisibleRange)
        let oldLines = Set(oldVisibleRange)
        return Array(newLines.subtracting(oldLines)).sorted()
    }

    /// Lines that left the visible area
    public var nowHiddenLines: [Int] {
        let newLines = Set(newVisibleRange)
        let oldLines = Set(oldVisibleRange)
        return Array(oldLines.subtracting(newLines)).sorted()
    }
}

public enum ScrollDirection {
    case up
    case down
    case none
}
