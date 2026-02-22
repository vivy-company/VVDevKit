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
    /// Number of visual lines this document line occupies (1 when not wrapped).
    public let wrapCount: Int

    public init(lineIndex: Int, yOffset: CGFloat, height: CGFloat, baselineOffset: CGFloat, glyphs: [LayoutGlyph], wrapCount: Int = 1) {
        self.lineIndex = lineIndex
        self.yOffset = yOffset
        self.height = height
        self.baselineOffset = baselineOffset
        self.glyphs = glyphs
        self.wrapCount = wrapCount
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
        wrapWidth: CGFloat? = nil,
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

        // Apply word wrap if needed
        if let wrapWidth = wrapWidth, wrapWidth > 0, !glyphs.isEmpty {
            let (wrapped, wrapCount) = applyWordWrap(glyphs: glyphs, wrapWidth: wrapWidth)
            return LineLayout(
                lineIndex: lineIndex,
                yOffset: yOffset,
                height: lineHeight * CGFloat(wrapCount),
                baselineOffset: baselineOffset,
                glyphs: wrapped,
                wrapCount: wrapCount
            )
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

    // MARK: - Word Wrap

    /// Returns the visual sub-line index (0-based) that the given character offset falls on.
    public func wrapLine(forCharacterOffset offset: Int, in line: LineLayout) -> Int {
        guard line.wrapCount > 1 else { return 0 }
        for glyph in line.glyphs {
            let glyphEnd = glyph.characterIndex + glyph.characterCount
            if offset <= glyph.characterIndex || (offset > glyph.characterIndex && offset <= glyphEnd) {
                return Int(round(glyph.position.y / lineHeight))
            }
        }
        // Past all glyphs → last visual line
        if let last = line.glyphs.last {
            return Int(round(last.position.y / lineHeight))
        }
        return 0
    }

    /// Position (x, yDelta) for a character offset in a possibly-wrapped line.
    /// yDelta is relative to the line's yOffset.
    public func position(forCharacterOffset offset: Int, in line: LineLayout) -> CGPoint {
        let x = xPosition(forCharacterOffset: offset, in: line)
        guard line.wrapCount > 1 else { return CGPoint(x: x, y: 0) }
        let wl = wrapLine(forCharacterOffset: offset, in: line)
        return CGPoint(x: x, y: CGFloat(wl) * lineHeight)
    }

    /// Convert a point (x, yDelta relative to line yOffset) to a character offset in a wrapped line.
    public func characterOffset(atPoint point: CGPoint, in line: LineLayout) -> Int {
        guard line.wrapCount > 1 else {
            return characterOffset(forX: point.x, in: line)
        }

        let targetWrapLine = max(0, min(line.wrapCount - 1, Int(floor(point.y / lineHeight))))

        // Find glyphs on this visual line
        var bestGlyph: LayoutGlyph?
        var bestDistance: CGFloat = .greatestFiniteMagnitude
        for glyph in line.glyphs {
            let glyphWrapLine = Int(round(glyph.position.y / lineHeight))
            guard glyphWrapLine == targetWrapLine else { continue }
            let dist = abs(glyph.position.x - point.x)
            if dist < bestDistance {
                bestDistance = dist
                bestGlyph = glyph
            }

            var glyphID = glyph.glyphID
            var advance = CGSize.zero
            CTFontGetAdvancesForGlyphs(glyph.font, .horizontal, &glyphID, &advance, 1)
            let glyphEnd = glyph.position.x + advance.width
            if point.x < glyphEnd {
                let mid = glyph.position.x + advance.width / 2
                if point.x < mid {
                    return glyph.characterIndex
                } else {
                    return glyph.characterIndex + glyph.characterCount
                }
            }
        }

        // Past all glyphs on this wrap line
        let glyphsOnLine = line.glyphs.filter { Int(round($0.position.y / lineHeight)) == targetWrapLine }
        if let last = glyphsOnLine.last {
            return last.characterIndex + last.characterCount
        }
        return bestGlyph.map { $0.characterIndex } ?? 0
    }

    /// Compute the number of visual lines a line of text requires at the given wrap width.
    /// Cheaper than full layout - uses estimated character width.
    public func estimateWrapCount(lineUTF16Length: Int, wrapWidth: CGFloat, charWidth: CGFloat) -> Int {
        guard wrapWidth > 0, lineUTF16Length > 0 else { return 1 }
        let totalWidth = CGFloat(lineUTF16Length) * charWidth
        return max(1, Int(ceil(totalWidth / wrapWidth)))
    }

    /// Reposition glyphs for word wrapping at the given width.
    private func applyWordWrap(glyphs: [LayoutGlyph], wrapWidth: CGFloat) -> (glyphs: [LayoutGlyph], wrapCount: Int) {
        guard !glyphs.isEmpty, wrapWidth > 0 else { return (glyphs, 1) }

        var result: [LayoutGlyph] = []
        result.reserveCapacity(glyphs.count)
        var currentWrapLine = 0
        var wrapLineStartX: CGFloat = 0

        for glyph in glyphs {
            var glyphID = glyph.glyphID
            var advance = CGSize.zero
            CTFontGetAdvancesForGlyphs(glyph.font, .horizontal, &glyphID, &advance, 1)

            let glyphX = glyph.position.x
            let glyphRight = glyphX + advance.width

            // Check if this glyph exceeds the wrap width (don't wrap the first glyph on a line)
            if glyphX > wrapLineStartX && glyphRight > wrapLineStartX + wrapWidth {
                currentWrapLine += 1
                wrapLineStartX = glyphX
            }

            let newX = glyphX - wrapLineStartX
            let newY = CGFloat(currentWrapLine) * lineHeight

            result.append(LayoutGlyph(
                glyphID: glyph.glyphID,
                position: CGPoint(x: newX, y: newY),
                font: glyph.font,
                color: glyph.color,
                characterIndex: glyph.characterIndex,
                characterCount: glyph.characterCount
            ))
        }

        return (result, currentWrapLine + 1)
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
