import AppKit

/// Custom layout manager for code editor
public class VVLayoutManager: NSLayoutManager {
    // MARK: - Properties

    /// Invisible character color
    public var invisibleColor: NSColor = .tertiaryLabelColor

    /// Whether to show invisible characters
    public var showInvisibles: Bool = false

    /// Space glyph
    private let spaceGlyph = "·"

    /// Tab glyph
    private let tabGlyph = "→"

    /// Newline glyph
    private let newlineGlyph = "¬"

    // MARK: - Drawing

    public override func drawGlyphs(forGlyphRange glyphsToShow: NSRange, at origin: NSPoint) {
        super.drawGlyphs(forGlyphRange: glyphsToShow, at: origin)

        if showInvisibles {
            drawInvisibleCharacters(forGlyphRange: glyphsToShow, at: origin)
        }
    }

    private func drawInvisibleCharacters(forGlyphRange glyphsToShow: NSRange, at origin: NSPoint) {
        guard let textStorage = textStorage else { return }

        let charRange = characterRange(forGlyphRange: glyphsToShow, actualGlyphRange: nil)
        let text = textStorage.string as NSString

        text.enumerateSubstrings(in: charRange, options: .byComposedCharacterSequences) { substring, substringRange, _, _ in
            guard let char = substring?.first else { return }

            var glyph: String?

            switch char {
            case " ":
                glyph = self.spaceGlyph
            case "\t":
                glyph = self.tabGlyph
            case "\n", "\r":
                glyph = self.newlineGlyph
            default:
                return
            }

            if let glyph = glyph {
                let glyphRange = self.glyphRange(forCharacterRange: substringRange, actualCharacterRange: nil)
                var point = self.location(forGlyphAt: glyphRange.location)

                if self.textContainer(forGlyphAt: glyphRange.location, effectiveRange: nil) != nil {
                    let lineRect = self.lineFragmentRect(forGlyphAt: glyphRange.location, effectiveRange: nil)
                    point.x += lineRect.origin.x + origin.x
                    point.y = lineRect.origin.y + origin.y + lineRect.height - 4
                }

                let attributes: [NSAttributedString.Key: Any] = [
                    .foregroundColor: self.invisibleColor,
                    .font: NSFont.systemFont(ofSize: 10)
                ]

                (glyph as NSString).draw(at: point, withAttributes: attributes)
            }
        }
    }

    // MARK: - Line Rect Calculation

    /// Get the rectangle for a specific line
    public func rectForLine(_ line: Int, in textContainer: NSTextContainer) -> NSRect? {
        guard let textStorage = textStorage else { return nil }

        let text = textStorage.string
        var currentLine = 1

        for (index, char) in text.enumerated() {
            if currentLine == line {
                let charRange = NSRange(location: index, length: 0)
                let glyphRange = glyphRange(forCharacterRange: charRange, actualCharacterRange: nil)
                return lineFragmentRect(forGlyphAt: glyphRange.location, effectiveRange: nil)
            }

            if char == "\n" {
                currentLine += 1
            }
        }

        return nil
    }

    /// Get line number at a point
    public func lineNumber(at point: NSPoint, in textContainer: NSTextContainer) -> Int? {
        let glyphIndex = glyphIndex(for: point, in: textContainer, fractionOfDistanceThroughGlyph: nil)
        let charIndex = characterIndexForGlyph(at: glyphIndex)

        guard let textStorage = textStorage else { return nil }

        let text = textStorage.string
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
}
