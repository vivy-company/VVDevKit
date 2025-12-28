import AppKit
import Combine
import VVGit

/// Overlay view for displaying inline git blame annotations
public class BlameOverlay: NSView {
    // MARK: - Properties

    /// The associated text view
    public weak var textView: NSTextView?

    /// Blame information by line number
    private var blameByLine: [Int: VVBlameInfo] = [:]

    /// Currently visible blame annotation
    private var visibleAnnotation: BlameAnnotationView?

    /// Current line being hovered
    private var hoveredLine: Int?

    /// Delay before showing blame
    public var showDelay: TimeInterval = 0.5

    /// Timer for delayed show
    private var showTimer: Timer?

    /// Tracking area for mouse events
    private var trackingArea: NSTrackingArea?

    // MARK: - Colors

    public var backgroundColor: NSColor = NSColor.windowBackgroundColor.withAlphaComponent(0.95) {
        didSet { visibleAnnotation?.backgroundColor = backgroundColor }
    }

    public var textColor: NSColor = .secondaryLabelColor {
        didSet { visibleAnnotation?.textColor = textColor }
    }

    public var authorColor: NSColor = .labelColor {
        didSet { visibleAnnotation?.authorColor = authorColor }
    }

    // MARK: - Initialization

    public override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        setupTrackingArea()
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    // MARK: - Setup

    private func setupTrackingArea() {
        let options: NSTrackingArea.Options = [
            .activeInKeyWindow,
            .mouseMoved,
            .mouseEnteredAndExited
        ]

        trackingArea = NSTrackingArea(
            rect: bounds,
            options: options,
            owner: self,
            userInfo: nil
        )

        if let area = trackingArea {
            addTrackingArea(area)
        }
    }

    public override func updateTrackingAreas() {
        super.updateTrackingAreas()

        if let existing = trackingArea {
            removeTrackingArea(existing)
        }

        setupTrackingArea()
    }

    // MARK: - Public Methods

    public func setBlameInfo(_ blameInfo: [VVBlameInfo]) {
        blameByLine.removeAll()
        for info in blameInfo {
            blameByLine[info.lineNumber] = info
        }
    }

    public func clearBlame() {
        blameByLine.removeAll()
        hideAnnotation()
    }

    // MARK: - Mouse Events

    public override func mouseMoved(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        handleMouseAt(point)
    }

    public override func mouseExited(with event: NSEvent) {
        cancelShow()
        hideAnnotation()
        hoveredLine = nil
    }

    private func handleMouseAt(_ point: NSPoint) {
        guard let line = lineNumber(at: point) else {
            cancelShow()
            hideAnnotation()
            hoveredLine = nil
            return
        }

        // Same line, ignore
        if line == hoveredLine {
            return
        }

        hoveredLine = line
        cancelShow()

        // Schedule show after delay
        showTimer = Timer.scheduledTimer(withTimeInterval: showDelay, repeats: false) { [weak self] _ in
            self?.showAnnotation(forLine: line)
        }
    }

    private func cancelShow() {
        showTimer?.invalidate()
        showTimer = nil
    }

    // MARK: - Annotation Display

    private func showAnnotation(forLine line: Int) {
        guard let blame = blameByLine[line],
              let textView = textView,
              let layoutManager = textView.layoutManager else {
            hideAnnotation()
            return
        }

        // Get line rect
        guard let lineRect = rectForLine(line, layoutManager: layoutManager, textView: textView) else {
            hideAnnotation()
            return
        }

        // Create or update annotation view
        if visibleAnnotation == nil {
            let annotation = BlameAnnotationView()
            annotation.backgroundColor = backgroundColor
            annotation.textColor = textColor
            annotation.authorColor = authorColor
            addSubview(annotation)
            visibleAnnotation = annotation
        }

        guard let annotation = visibleAnnotation else { return }

        // Configure annotation
        annotation.configure(with: blame)

        // Position annotation at end of line
        let annotationSize = annotation.intrinsicContentSize
        let x = bounds.width - annotationSize.width - 16
        let y = lineRect.origin.y + (lineRect.height - annotationSize.height) / 2

        annotation.frame = NSRect(
            x: max(x, bounds.width * 0.4),
            y: y,
            width: annotationSize.width,
            height: annotationSize.height
        )

        annotation.isHidden = false
    }

    private func hideAnnotation() {
        visibleAnnotation?.isHidden = true
    }

    // MARK: - Line Calculations

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

    private func rectForLine(_ line: Int, layoutManager: NSLayoutManager, textView: NSTextView) -> NSRect? {
        let text = textView.string
        var currentLine = 1
        var charIndex = 0

        for (index, char) in text.enumerated() {
            if currentLine == line {
                charIndex = index
                break
            }
            if char == "\n" {
                currentLine += 1
            }
        }

        guard currentLine == line else { return nil }

        let glyphIndex = layoutManager.glyphIndexForCharacter(at: charIndex)
        var lineRect = layoutManager.lineFragmentRect(forGlyphAt: glyphIndex, effectiveRange: nil)

        // Convert to overlay coordinates
        let visibleRect = textView.visibleRect
        lineRect.origin.y += textView.textContainerOrigin.y - visibleRect.origin.y

        return lineRect
    }
}

// MARK: - Blame Annotation View

class BlameAnnotationView: NSView {
    // MARK: - Properties

    var backgroundColor: NSColor = NSColor.windowBackgroundColor.withAlphaComponent(0.95) {
        didSet { needsDisplay = true }
    }

    var textColor: NSColor = .secondaryLabelColor {
        didSet { updateLabels() }
    }

    var authorColor: NSColor = .labelColor {
        didSet { updateLabels() }
    }

    private let authorLabel = NSTextField(labelWithString: "")
    private let dateLabel = NSTextField(labelWithString: "")
    private let summaryLabel = NSTextField(labelWithString: "")
    private let commitLabel = NSTextField(labelWithString: "")

    private let padding: CGFloat = 8
    private let spacing: CGFloat = 8

    // MARK: - Initialization

    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        setupViews()
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    // MARK: - Setup

    private func setupViews() {
        wantsLayer = true
        layer?.cornerRadius = 4

        // Configure labels
        for label in [authorLabel, dateLabel, summaryLabel, commitLabel] {
            label.isEditable = false
            label.isBordered = false
            label.drawsBackground = false
            label.lineBreakMode = .byTruncatingTail
            addSubview(label)
        }

        authorLabel.font = NSFont.systemFont(ofSize: 11, weight: .medium)
        dateLabel.font = NSFont.systemFont(ofSize: 10)
        summaryLabel.font = NSFont.systemFont(ofSize: 11)
        commitLabel.font = NSFont.monospacedSystemFont(ofSize: 10, weight: .regular)

        updateLabels()
    }

    private func updateLabels() {
        authorLabel.textColor = authorColor
        dateLabel.textColor = textColor
        summaryLabel.textColor = textColor
        commitLabel.textColor = textColor.withAlphaComponent(0.6)
    }

    // MARK: - Configuration

    func configure(with blame: VVBlameInfo) {
        authorLabel.stringValue = blame.author
        dateLabel.stringValue = formatDate(blame.date)
        summaryLabel.stringValue = blame.summary ?? ""
        commitLabel.stringValue = String(blame.commit.prefix(7))

        needsLayout = true
        needsDisplay = true
    }

    private func formatDate(_ date: Date) -> String {
        let formatter = RelativeDateTimeFormatter()
        formatter.unitsStyle = .abbreviated
        return formatter.localizedString(for: date, relativeTo: Date())
    }

    // MARK: - Layout

    override var intrinsicContentSize: NSSize {
        let authorSize = authorLabel.intrinsicContentSize
        let dateSize = dateLabel.intrinsicContentSize
        let summarySize = summaryLabel.intrinsicContentSize
        let commitSize = commitLabel.intrinsicContentSize

        let width = padding + authorSize.width + spacing + dateSize.width + spacing +
                   min(summarySize.width, 200) + spacing + commitSize.width + padding

        let height = padding + max(authorSize.height, dateSize.height, summarySize.height) + padding

        return NSSize(width: min(width, 500), height: height)
    }

    override func layout() {
        super.layout()

        let height = bounds.height
        var x = padding

        // Author
        let authorSize = authorLabel.intrinsicContentSize
        authorLabel.frame = NSRect(
            x: x,
            y: (height - authorSize.height) / 2,
            width: authorSize.width,
            height: authorSize.height
        )
        x += authorSize.width + spacing

        // Date
        let dateSize = dateLabel.intrinsicContentSize
        dateLabel.frame = NSRect(
            x: x,
            y: (height - dateSize.height) / 2,
            width: dateSize.width,
            height: dateSize.height
        )
        x += dateSize.width + spacing

        // Commit hash at end
        let commitSize = commitLabel.intrinsicContentSize
        let commitX = bounds.width - padding - commitSize.width
        commitLabel.frame = NSRect(
            x: commitX,
            y: (height - commitSize.height) / 2,
            width: commitSize.width,
            height: commitSize.height
        )

        // Summary fills remaining space
        let summaryWidth = max(0, commitX - x - spacing)
        let summarySize = summaryLabel.intrinsicContentSize
        summaryLabel.frame = NSRect(
            x: x,
            y: (height - summarySize.height) / 2,
            width: summaryWidth,
            height: summarySize.height
        )
    }

    // MARK: - Drawing

    override func draw(_ dirtyRect: NSRect) {
        backgroundColor.setFill()

        let path = NSBezierPath(roundedRect: bounds, xRadius: 4, yRadius: 4)
        path.fill()

        // Draw subtle border
        NSColor.separatorColor.withAlphaComponent(0.3).setStroke()
        path.lineWidth = 0.5
        path.stroke()
    }
}
