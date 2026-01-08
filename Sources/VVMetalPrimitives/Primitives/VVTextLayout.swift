import CoreGraphics

public struct VVTextLine: Hashable, Sendable {
    public var y: CGFloat
    public var height: CGFloat
    public var baseline: CGFloat
    public var width: CGFloat
    public var length: Int
    public var glyphs: [VVTextGlyph]

    public init(
        y: CGFloat,
        height: CGFloat,
        baseline: CGFloat,
        glyphs: [VVTextGlyph]
    ) {
        self.y = y
        self.height = height
        self.baseline = baseline
        self.glyphs = glyphs

        var maxX: CGFloat = 0
        var maxIndex: Int = 0
        for glyph in glyphs {
            maxX = max(maxX, glyph.position.x + glyph.size.width)
            if let index = glyph.stringIndex {
                maxIndex = max(maxIndex, index + 1)
            }
        }
        self.width = maxX
        self.length = maxIndex
    }

    public func indexForX(_ x: CGFloat) -> Int? {
        if x >= width {
            return nil
        }

        for glyph in glyphs.reversed() {
            guard let index = glyph.stringIndex else { continue }
            if glyph.position.x <= x {
                return index
            }
        }

        return glyphs.first?.stringIndex ?? 0
    }

    public func closestIndexForX(_ x: CGFloat) -> Int {
        var prevIndex = 0
        var prevX: CGFloat = 0

        for glyph in glyphs {
            guard let index = glyph.stringIndex else { continue }
            let gx = glyph.position.x
            if gx >= x {
                if gx - x < x - prevX {
                    return index
                }
                return prevIndex
            }
            prevIndex = index
            prevX = gx
        }

        if length <= 1 {
            return x > width * 0.5 ? 1 : 0
        }
        return length
    }

    public func xForIndex(_ index: Int) -> CGFloat {
        for glyph in glyphs {
            guard let glyphIndex = glyph.stringIndex else { continue }
            if glyphIndex >= index {
                return glyph.position.x
            }
        }
        return width
    }
}

public struct VVTextLayout: Hashable, Sendable {
    public var frame: CGRect
    public var lines: [VVTextLine]

    public init(frame: CGRect, lines: [VVTextLine]) {
        self.frame = frame
        self.lines = lines
    }

    public func line(at y: CGFloat) -> VVTextLine? {
        lines.first { y >= $0.y && y <= ($0.y + $0.height) }
    }
}
