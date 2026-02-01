import AppKit
import VVGit

/// Gutter view displaying line numbers and git change indicators
public class GutterView: NSView {
    // MARK: - Properties

    /// The associated text view
    public weak var textView: NSTextView?

    /// Line count
    private var lineCount: Int = 1

    /// Current line (highlighted)
    public var currentLine: Int = 1

    /// Show line numbers
    public var showLineNumbers: Bool = true

    /// Show git gutter
    public var showGitGutter: Bool = true

    /// Git hunks
    private var gitHunks: [VVDiffHunk] = []

    /// Line-level git statuses
    private var lineStatuses: [Int: VVLineGitStatus.Status] = [:]

    // MARK: - Colors

    public var backgroundColor: NSColor = .textBackgroundColor {
        didSet { needsDisplay = true }
    }

    public var textColor: NSColor = .secondaryLabelColor {
        didSet { needsDisplay = true }
    }

    public var activeTextColor: NSColor = .labelColor {
        didSet { needsDisplay = true }
    }

    public var separatorColor: NSColor = .separatorColor {
        didSet { needsDisplay = true }
    }

    public var gitAddedColor: NSColor = .systemGreen {
        didSet { needsDisplay = true }
    }

    public var gitModifiedColor: NSColor = .systemBlue {
        didSet { needsDisplay = true }
    }

    public var gitDeletedColor: NSColor = .systemRed {
        didSet { needsDisplay = true }
    }

    // MARK: - Layout

    private let lineNumberPadding: CGFloat = 8
    private let gitGutterWidth: CGFloat = 4
    private let separatorWidth: CGFloat = 1

    // MARK: - Initialization

    public override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        wantsLayer = true
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    // Match NSScrollView's flipped coordinate system
    public override var isFlipped: Bool { true }

    // MARK: - Public Methods

    public func updateLineCount(_ count: Int) {
        guard lineCount != count else { return }
        lineCount = count
        updateWidth()
        needsDisplay = true
    }

    public func setGitHunks(_ hunks: [VVDiffHunk]) {
        self.gitHunks = hunks

        // Build line status map
        lineStatuses.removeAll()
        let statuses = VVDiffParser.lineStatuses(from: hunks)
        for status in statuses {
            lineStatuses[status.lineNumber] = status.status
        }

        needsDisplay = true
    }

    // MARK: - Layout

    private func updateWidth() {
        let digitCount = String(lineCount).count
        let font = NSFont.monospacedDigitSystemFont(ofSize: 11, weight: .regular)
        let sampleString = String(repeating: "0", count: digitCount)
        let size = (sampleString as NSString).size(withAttributes: [.font: font])

        var newWidth = size.width + lineNumberPadding * 2

        if showGitGutter {
            newWidth += gitGutterWidth + 2
        }

        newWidth += separatorWidth

        // Update width constraint if needed
        if let widthConstraint = constraints.first(where: { $0.firstAttribute == .width }) {
            widthConstraint.constant = max(newWidth, 40)
        } else {
            widthAnchor.constraint(equalToConstant: max(newWidth, 40)).isActive = true
        }
    }

    // MARK: - Drawing

    public override func draw(_ dirtyRect: NSRect) {
        // Background
        backgroundColor.setFill()
        dirtyRect.fill()

        guard let textView = textView,
              let layoutManager = textView.layoutManager,
              let textContainer = textView.textContainer else { return }

        let font = NSFont.monospacedDigitSystemFont(ofSize: 11, weight: .regular)
        let visibleRect = textView.visibleRect
        let containerOrigin = textView.textContainerOrigin

        // Calculate visible glyph range
        let visibleGlyphRange = layoutManager.glyphRange(forBoundingRect: visibleRect, in: textContainer)
        let visibleCharRange = layoutManager.characterRange(forGlyphRange: visibleGlyphRange, actualGlyphRange: nil)

        // Get the text
        let text = textView.string

        // Find line numbers in visible range
        var lineNumber = 1

        // Count lines before visible range
        for char in text.prefix(visibleCharRange.location) {
            if char == "\n" {
                lineNumber += 1
            }
        }

        // Draw visible lines
        var currentCharIndex = visibleCharRange.location

        while currentCharIndex < min(visibleCharRange.location + visibleCharRange.length + 1000, text.count) {
            let glyphIndex = layoutManager.glyphIndexForCharacter(at: currentCharIndex)

            // Skip if glyph is not in visible range
            if glyphIndex < visibleGlyphRange.location {
                // Find next newline
                if let nextNewline = text[text.index(text.startIndex, offsetBy: currentCharIndex)...].firstIndex(of: "\n") {
                    let nextIndex = text.distance(from: text.startIndex, to: nextNewline) + 1
                    lineNumber += 1
                    currentCharIndex = nextIndex
                    continue
                } else {
                    break
                }
            }

            if glyphIndex >= visibleGlyphRange.location + visibleGlyphRange.length {
                break
            }

            // Get line fragment rect
            var lineRect = layoutManager.lineFragmentRect(forGlyphAt: glyphIndex, effectiveRange: nil)
            lineRect.origin.y += containerOrigin.y - visibleRect.origin.y

            // Draw git gutter indicator
            if showGitGutter {
                drawGitIndicator(forLine: lineNumber, in: lineRect)
            }

            // Draw line number
            if showLineNumbers {
                drawLineNumber(lineNumber, in: lineRect, font: font, isCurrent: lineNumber == currentLine)
            }

            // Find next newline
            let startIndex = text.index(text.startIndex, offsetBy: currentCharIndex)
            if let nextNewline = text[startIndex...].firstIndex(of: "\n") {
                let nextIndex = text.distance(from: text.startIndex, to: nextNewline) + 1
                lineNumber += 1
                currentCharIndex = nextIndex
            } else {
                // Last line
                break
            }
        }

        // Draw separator line
        separatorColor.setFill()
        let separatorRect = NSRect(
            x: bounds.width - separatorWidth,
            y: 0,
            width: separatorWidth,
            height: bounds.height
        )
        separatorRect.fill()
    }

    private func drawLineNumber(_ number: Int, in lineRect: NSRect, font: NSFont, isCurrent: Bool) {
        let string = "\(number)"
        let color = isCurrent ? activeTextColor : textColor
        let fontToUse = isCurrent ? NSFont.monospacedDigitSystemFont(ofSize: 11, weight: .medium) : font

        let attributes: [NSAttributedString.Key: Any] = [
            .font: fontToUse,
            .foregroundColor: color
        ]

        let size = (string as NSString).size(withAttributes: attributes)
        let x = bounds.width - size.width - lineNumberPadding - separatorWidth - (showGitGutter ? gitGutterWidth + 2 : 0)
        let y = lineRect.origin.y + (lineRect.height - size.height) / 2

        (string as NSString).draw(at: NSPoint(x: x, y: y), withAttributes: attributes)
    }

    private func drawGitIndicator(forLine line: Int, in lineRect: NSRect) {
        guard let status = lineStatuses[line] else { return }

        let color: NSColor
        switch status {
        case .added:
            color = gitAddedColor
        case .modified:
            color = gitModifiedColor
        case .deleted:
            color = gitDeletedColor
        }

        let indicatorRect: NSRect

        if status == .deleted {
            // Draw a triangle for deleted lines
            indicatorRect = NSRect(
                x: bounds.width - separatorWidth - gitGutterWidth - 1,
                y: lineRect.origin.y,
                width: gitGutterWidth,
                height: 6
            )

            let path = NSBezierPath()
            path.move(to: NSPoint(x: indicatorRect.minX, y: indicatorRect.midY))
            path.line(to: NSPoint(x: indicatorRect.maxX, y: indicatorRect.minY))
            path.line(to: NSPoint(x: indicatorRect.maxX, y: indicatorRect.maxY))
            path.close()

            color.setFill()
            path.fill()
        } else {
            // Draw a bar for added/modified lines
            indicatorRect = NSRect(
                x: bounds.width - separatorWidth - gitGutterWidth - 1,
                y: lineRect.origin.y + 2,
                width: gitGutterWidth,
                height: lineRect.height - 4
            )

            color.setFill()
            indicatorRect.fill()
        }
    }

    // MARK: - Mouse Events

    public override func mouseDown(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)

        // Get line number at click
        if let line = lineNumber(at: point) {
            // Select the entire line
            selectLine(line)
        }
    }

    private func lineNumber(at point: NSPoint) -> Int? {
        guard let textView = textView,
              let layoutManager = textView.layoutManager,
              let textContainer = textView.textContainer else { return nil }

        let visibleRect = textView.visibleRect
        let textPoint = NSPoint(
            x: 0,
            y: point.y + visibleRect.origin.y - textView.textContainerOrigin.y
        )

        let glyphIndex = layoutManager.glyphIndex(for: textPoint, in: textContainer, fractionOfDistanceThroughGlyph: nil)
        let charIndex = layoutManager.characterIndexForGlyph(at: glyphIndex)

        // Count newlines to get line number
        let text = textView.string
        var lineNumber = 1
        for (index, char) in text.enumerated() {
            if index >= charIndex {
                break
            }
            if char == "\n" {
                lineNumber += 1
            }
        }

        return lineNumber
    }

    private func selectLine(_ line: Int) {
        guard let textView = textView else { return }

        let text = textView.string
        var currentLine = 1
        var lineStart = 0

        for (index, char) in text.enumerated() {
            if currentLine == line {
                // Find line end
                var lineEnd = text.count
                for (i, c) in text.enumerated().dropFirst(index) {
                    if c == "\n" {
                        lineEnd = i + 1
                        break
                    }
                }

                textView.setSelectedRange(NSRange(location: lineStart, length: lineEnd - lineStart))
                return
            }

            if char == "\n" {
                currentLine += 1
                lineStart = index + 1
            }
        }
    }
}
