import AppKit
import CoreGraphics
import CoreText
import Foundation

struct VVDiffDisplayMetrics {
    let charWidth: CGFloat
    let backgroundColor: SIMD4<Float>

    init(font: NSFont, theme: VVTheme) {
        let ctFont = font as CTFont
        var glyphID: CGGlyph = 0
        var char: UniChar = 0x004D
        CTFontGetGlyphsForCharacters(ctFont, &char, &glyphID, 1)
        var advance = CGSize.zero
        CTFontGetAdvancesForGlyphs(ctFont, .horizontal, &glyphID, &advance, 1)
        self.charWidth = advance.width > 0 ? advance.width : font.pointSize * 0.6
        self.backgroundColor = theme.backgroundColor.simdColor
    }
}
