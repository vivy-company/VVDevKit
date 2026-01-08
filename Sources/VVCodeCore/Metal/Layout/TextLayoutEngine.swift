import Foundation
import CoreText
import CoreGraphics
import AppKit

/// Colored range from syntax highlighting
public struct ColoredRange {
    public let range: NSRange
    public let color: SIMD4<Float>
    public let fontVariant: FontVariant

    public init(range: NSRange, color: SIMD4<Float>, fontVariant: FontVariant = .regular) {
        self.range = range
        self.color = color
        self.fontVariant = fontVariant
    }
}

/// Result of laying out a line of text
public struct LineLayout {
    public let lineIndex: Int
    public let yOffset: CGFloat
    public let height: CGFloat
    public let baselineOffset: CGFloat
    public let glyphs: [LayoutGlyph]

    public init(lineIndex: Int, yOffset: CGFloat, height: CGFloat, baselineOffset: CGFloat, glyphs: [LayoutGlyph]) {
        self.lineIndex = lineIndex
        self.yOffset = yOffset
        self.height = height
        self.baselineOffset = baselineOffset
        self.glyphs = glyphs
    }
}

/// A positioned glyph ready for rendering
public struct LayoutGlyph {
    public let glyphID: CGGlyph
    public let position: CGPoint        // Position relative to line origin
    public let font: CTFont
    public let color: SIMD4<Float>
    public let characterIndex: Int      // Index in original string
    public let characterCount: Int      // Number of chars (>1 for ligatures)

    public init(
        glyphID: CGGlyph,
        position: CGPoint,
        font: CTFont,
        color: SIMD4<Float>,
        characterIndex: Int,
        characterCount: Int = 1
    ) {
        self.glyphID = glyphID
        self.position = position
        self.font = font
        self.color = color
        self.characterIndex = characterIndex
        self.characterCount = characterCount
    }
}

/// Engine for laying out text with syntax highlighting and ligature support
public final class TextLayoutEngine {

    // MARK: - Properties

    private var baseFont: NSFont
    private var lineHeightMultiplier: CGFloat
    private var scaleFactor: CGFloat
    private var fonts: [FontVariant: CTFont] = [:]
    private var lineHeight: CGFloat = 20
    private var ascent: CGFloat = 14
    private var descent: CGFloat = 4
    private var leading: CGFloat = 2
    private var baselineOffset: CGFloat = 14  // Offset from line top to baseline

    // Cache for line layouts
    private var lineCache: [Int: LineLayout] = [:]
    private var cacheVersion: Int = 0

    // MARK: - Initialization

    public init(font: NSFont, lineHeightMultiplier: CGFloat = 1.4, scaleFactor: CGFloat = 1.0) {
        self.baseFont = font
        self.lineHeightMultiplier = lineHeightMultiplier
        self.scaleFactor = scaleFactor
        updateFont(font, lineHeightMultiplier: lineHeightMultiplier, scaleFactor: scaleFactor)
    }

    // MARK: - Font Configuration

    public func updateFont(_ font: NSFont, lineHeightMultiplier: CGFloat = 1.4, scaleFactor: CGFloat = 1.0) {
        baseFont = font
        self.lineHeightMultiplier = lineHeightMultiplier
        self.scaleFactor = scaleFactor
        let ctFont = font as CTFont
        let size = CTFontGetSize(ctFont)

        fonts[.regular] = ctFont

        // Bold
        if let boldDesc = CTFontCopyFontDescriptor(ctFont).withSymbolicTraits(.boldTrait, .boldTrait) {
            fonts[.bold] = CTFontCreateWithFontDescriptor(boldDesc, size, nil)
        } else {
            fonts[.bold] = ctFont
        }

        // Italic
        if let italicDesc = CTFontCopyFontDescriptor(ctFont).withSymbolicTraits(.italicTrait, .italicTrait) {
            fonts[.italic] = CTFontCreateWithFontDescriptor(italicDesc, size, nil)
        } else {
            fonts[.italic] = ctFont
        }

        // Bold Italic
        let boldItalicTraits: CTFontSymbolicTraits = [.boldTrait, .italicTrait]
        if let boldItalicDesc = CTFontCopyFontDescriptor(ctFont).withSymbolicTraits(boldItalicTraits, boldItalicTraits) {
            fonts[.boldItalic] = CTFontCreateWithFontDescriptor(boldItalicDesc, size, nil)
        } else {
            fonts[.boldItalic] = fonts[.bold]
        }

        // Calculate line metrics
        ascent = CTFontGetAscent(ctFont)
        descent = CTFontGetDescent(ctFont)
        leading = CTFontGetLeading(ctFont)

        let naturalLineHeight = ascent + descent + leading
        let targetLineHeight = naturalLineHeight * lineHeightMultiplier
        lineHeight = ceil(targetLineHeight * scaleFactor) / scaleFactor

        // Center text vertically within the line
        // Extra space from multiplier should be distributed evenly top and bottom
        // Snap to device pixel boundary for consistent glyph alignment
        let extraSpace = lineHeight - naturalLineHeight
        baselineOffset = round((extraSpace / 2 + ascent) * scaleFactor) / scaleFactor

        invalidateCache()
    }

    public func updateScaleFactor(_ scaleFactor: CGFloat) {
        guard scaleFactor > 0 else { return }
        updateFont(baseFont, lineHeightMultiplier: lineHeightMultiplier, scaleFactor: scaleFactor)
    }

    // MARK: - Public API

    /// Get the line height
    public var calculatedLineHeight: CGFloat {
        lineHeight
    }

    /// Get baseline offset (from line top to baseline)
    public var calculatedBaselineOffset: CGFloat {
        baselineOffset
    }

    /// Layout a single line of text
    public func layoutLine(
        text: String,
        lineIndex: Int,
        yOffset: CGFloat,
        coloredRanges: [ColoredRange],
        defaultColor: SIMD4<Float>
    ) -> LineLayout {
        guard !text.isEmpty else {
            return LineLayout(
                lineIndex: lineIndex,
                yOffset: yOffset,
                height: lineHeight,
                baselineOffset: baselineOffset,
                glyphs: []
            )
        }

        var glyphs: [LayoutGlyph] = []

        // Group consecutive characters with same style
        let textLength = (text as NSString).length
        let styleRuns = computeStyleRuns(textLength: textLength, coloredRanges: coloredRanges, defaultColor: defaultColor)

        var xPosition: CGFloat = 0
        let nsText = text as NSString

        for run in styleRuns {
            guard let font = fonts[run.fontVariant] else { continue }
            let runText = nsText.substring(with: run.range)

            // Shape the text with CoreText (handles ligatures)
            let shapedGlyphs = shapeText(runText, font: font, startCharIndex: run.range.location)

            for shaped in shapedGlyphs {
                glyphs.append(LayoutGlyph(
                    glyphID: shaped.glyphID,
                    position: CGPoint(x: xPosition + shaped.position.x, y: shaped.position.y),
                    font: shaped.font,
                    color: run.color,
                    characterIndex: shaped.characterIndex,
                    characterCount: shaped.characterCount
                ))
            }

            // Advance x position by run width (positions are relative to run start)
            if let lastGlyph = shapedGlyphs.last {
                xPosition += lastGlyph.position.x + lastGlyph.advance
            }
        }

        return LineLayout(
            lineIndex: lineIndex,
            yOffset: yOffset,
            height: lineHeight,
            baselineOffset: baselineOffset,
            glyphs: glyphs
        )
    }

    /// Layout multiple lines
    public func layoutLines(
        lines: [(text: String, lineIndex: Int)],
        startY: CGFloat,
        coloredRanges: [ColoredRange],
        defaultColor: SIMD4<Float>
    ) -> [LineLayout] {
        var result: [LineLayout] = []
        var currentY = startY

        for (text, lineIndex) in lines {
            // Filter colored ranges for this line
            // Note: coloredRanges should be relative to the full document
            // This is a simplified version - real implementation would need proper range mapping

            let layout = layoutLine(
                text: text,
                lineIndex: lineIndex,
                yOffset: currentY,
                coloredRanges: coloredRanges,
                defaultColor: defaultColor
            )
            result.append(layout)
            currentY += lineHeight
        }

        return result
    }

    /// Convert character offset to x position in a line
    public func xPosition(forCharacterOffset offset: Int, in line: LineLayout) -> CGFloat {
        if offset == 0 { return 0 }

        // Find the glyph that contains or is after this character
        for (i, glyph) in line.glyphs.enumerated() {
            let glyphStart = glyph.characterIndex
            let glyphEnd = glyph.characterIndex + glyph.characterCount

            if offset <= glyphStart {
                return glyph.position.x
            }

            if offset <= glyphEnd {
                var glyphID = glyph.glyphID
                var advance = CGSize.zero
                CTFontGetAdvancesForGlyphs(glyph.font, .horizontal, &glyphID, &advance, 1)

                if glyph.characterCount > 1 {
                    if offset >= glyphEnd {
                        return glyph.position.x + advance.width
                    }
                    let subAdvance = advance.width / CGFloat(glyph.characterCount)
                    if subAdvance > 0 {
                        let local = CGFloat(offset - glyphStart)
                        return glyph.position.x + subAdvance * local
                    }
                }

                return offset >= glyphEnd ? (glyph.position.x + advance.width) : glyph.position.x
            }

            // If this is the last glyph
            if i == line.glyphs.count - 1 {
                // Return position after this glyph
                var glyphID = glyph.glyphID
                var advance = CGSize.zero
                CTFontGetAdvancesForGlyphs(glyph.font, .horizontal, &glyphID, &advance, 1)
                return glyph.position.x + advance.width
            }
        }

        return 0
    }

    /// Convert x position to character offset
    public func characterOffset(forX x: CGFloat, in line: LineLayout) -> Int {
        guard !line.glyphs.isEmpty else { return 0 }

        for glyph in line.glyphs {
            var glyphID = glyph.glyphID
            var advance = CGSize.zero
            CTFontGetAdvancesForGlyphs(glyph.font, .horizontal, &glyphID, &advance, 1)

            let glyphEnd = glyph.position.x + advance.width
            if x < glyphEnd {
                if glyph.characterCount > 1 && advance.width > 0 {
                    let subAdvance = advance.width / CGFloat(glyph.characterCount)
                    let relative = max(0, min(advance.width, x - glyph.position.x))
                    let rawIndex = Int(floor((relative / subAdvance) + 0.5))
                    let clamped = min(glyph.characterCount, max(0, rawIndex))
                    return glyph.characterIndex + clamped
                } else {
                    // Check if closer to start or end of glyph
                    let mid = glyph.position.x + advance.width / 2
                    if x < mid {
                        return glyph.characterIndex
                    } else {
                        return glyph.characterIndex + glyph.characterCount
                    }
                }
            }
        }

        // Beyond last glyph
        if let lastGlyph = line.glyphs.last {
            return lastGlyph.characterIndex + lastGlyph.characterCount
        }

        return 0
    }

    // MARK: - Cache Management

    public func invalidateCache() {
        lineCache.removeAll()
        cacheVersion += 1
    }

    public func invalidateLines(from startLine: Int) {
        for key in lineCache.keys where key >= startLine {
            lineCache.removeValue(forKey: key)
        }
    }

    // MARK: - Private Methods

    private struct StyleRun {
        let range: NSRange
        let color: SIMD4<Float>
        let fontVariant: FontVariant
    }

    private func computeStyleRuns(
        textLength: Int,
        coloredRanges: [ColoredRange],
        defaultColor: SIMD4<Float>
    ) -> [StyleRun] {
        guard textLength > 0 else { return [] }

        // Sort ranges by start position, then by length (longer first for priority)
        let sorted = coloredRanges.sorted {
            if $0.range.location != $1.range.location {
                return $0.range.location < $1.range.location
            }
            return $0.range.length > $1.range.length
        }

        var runs: [StyleRun] = []
        var currentPos = 0

        for colored in sorted {
            let rangeStart = colored.range.location
            let rangeEnd = min(colored.range.location + colored.range.length, textLength)

            // Skip if this range is entirely before currentPos (already covered)
            guard rangeEnd > currentPos else { continue }

            // Adjust start if it overlaps with already processed region
            let adjustedStart = max(rangeStart, currentPos)
            let adjustedLength = rangeEnd - adjustedStart

            guard adjustedLength > 0 else { continue }

            // Add gap with default color if needed
            if adjustedStart > currentPos {
                runs.append(StyleRun(
                    range: NSRange(location: currentPos, length: adjustedStart - currentPos),
                    color: defaultColor,
                    fontVariant: .regular
                ))
            }

            // Add colored range (adjusted for overlap)
            runs.append(StyleRun(
                range: NSRange(location: adjustedStart, length: adjustedLength),
                color: colored.color,
                fontVariant: colored.fontVariant
            ))

            currentPos = rangeEnd
        }

        // Add trailing default color if needed
        if currentPos < textLength {
            runs.append(StyleRun(
                range: NSRange(location: currentPos, length: textLength - currentPos),
                color: defaultColor,
                fontVariant: .regular
            ))
        }

        return runs
    }

    /// Shape text using CoreText (handles ligatures, kerning, etc.)
    private func shapeText(_ text: String, font: CTFont, startCharIndex: Int) -> [ShapedGlyph] {
        guard !text.isEmpty else { return [] }

        // Create attributed string with font
        let attributes: [NSAttributedString.Key: Any] = [
            .font: font,
            .ligature: 1  // Enable ligatures
        ]
        let attrString = NSAttributedString(string: text, attributes: attributes)

        // Create CTLine for shaping
        let line = CTLineCreateWithAttributedString(attrString)
        let runs = CTLineGetGlyphRuns(line) as? [CTRun] ?? []

        var result: [ShapedGlyph] = []

        let utf16Length = (text as NSString).length

        for run in runs {
            let glyphCount = CTRunGetGlyphCount(run)
            guard glyphCount > 0 else { continue }

            let attributes = CTRunGetAttributes(run) as NSDictionary
            let runFont = attributes[kCTFontAttributeName] as! CTFont

            // Get glyphs
            var glyphs = [CGGlyph](repeating: 0, count: glyphCount)
            CTRunGetGlyphs(run, CFRangeMake(0, glyphCount), &glyphs)

            // Get positions
            var positions = [CGPoint](repeating: .zero, count: glyphCount)
            CTRunGetPositions(run, CFRangeMake(0, glyphCount), &positions)

            // Get advances
            var advances = [CGSize](repeating: .zero, count: glyphCount)
            CTRunGetAdvances(run, CFRangeMake(0, glyphCount), &advances)

            // Get string indices (for ligature detection)
            var indices = [CFIndex](repeating: 0, count: glyphCount)
            CTRunGetStringIndices(run, CFRangeMake(0, glyphCount), &indices)

            for i in 0..<glyphCount {
                let charIndex = Int(indices[i])
                let nextCharIndex = (i + 1 < glyphCount) ? Int(indices[i + 1]) : utf16Length
                let charCount = nextCharIndex - charIndex

                result.append(ShapedGlyph(
                    glyphID: glyphs[i],
                    position: positions[i],
                    advance: advances[i].width,
                    font: runFont,
                    characterIndex: startCharIndex + charIndex,
                    characterCount: max(1, charCount)
                ))
            }
        }

        return result
    }
}
