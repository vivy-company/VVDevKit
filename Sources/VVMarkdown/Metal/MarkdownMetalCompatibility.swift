import Foundation
import CoreGraphics
import CoreText
@_exported import VVMetalPrimitives

public typealias MarkdownUniforms = VVTextRenderUniforms
public typealias MarkdownGlyphInstance = VVTextGlyphInstance
public typealias MarkdownMetalRenderer = VVTextMetalRenderer
public typealias MarkdownCachedGlyph = VVTextCachedGlyph
public typealias MarkdownGlyphAtlas = VVTextGlyphAtlas
public typealias MarkdownRendererError = VVMetalRendererError

public extension VVFontVariant {
    init(markdownVariant: FontVariant) {
        switch markdownVariant {
        case .regular:
            self = .regular
        case .semibold:
            self = .semibold
        case .semiboldItalic:
            self = .semiboldItalic
        case .bold:
            self = .bold
        case .italic:
            self = .italic
        case .boldItalic:
            self = .boldItalic
        case .monospace:
            self = .monospace
        case .emoji:
            self = .emoji
        }
    }
}

public extension VVTextGlyphAtlas {
    func glyph(for glyphID: CGGlyph, variant: FontVariant, fontSize: CGFloat, baseFont: VVFont? = nil) -> VVTextCachedGlyph? {
        glyph(for: glyphID, variant: VVFontVariant(markdownVariant: variant), fontSize: fontSize, baseFont: baseFont)
    }

    func glyph(for glyphID: CGGlyph, font: CTFont, variant: FontVariant = .regular) -> VVTextCachedGlyph? {
        glyph(for: glyphID, font: font, variant: VVFontVariant(markdownVariant: variant))
    }

    func glyph(for glyphID: CGGlyph, fontName: String, fontSize: CGFloat, variant: FontVariant = .regular) -> VVTextCachedGlyph? {
        glyph(
            for: glyphID,
            fontName: fontName,
            fontSize: fontSize,
            variant: VVFontVariant(markdownVariant: variant)
        )
    }

    func glyph(for character: Character, variant: FontVariant, fontSize: CGFloat, baseFont: VVFont? = nil) -> VVTextCachedGlyph? {
        glyph(for: character, variant: VVFontVariant(markdownVariant: variant), fontSize: fontSize, baseFont: baseFont)
    }
}
