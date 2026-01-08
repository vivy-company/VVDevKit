import Foundation
import simd
import CoreText
import AppKit

// MARK: - GPU Data Structures

/// Per-glyph instance data for instanced rendering (64 bytes aligned)
public struct GlyphInstance {
    public var position: SIMD2<Float>     // Screen position (top-left)
    public var size: SIMD2<Float>         // Quad size in points
    public var uvOrigin: SIMD2<Float>     // UV top-left in atlas
    public var uvSize: SIMD2<Float>       // UV extent
    public var color: SIMD4<Float>        // RGBA color from syntax highlighting
    public var atlasIndex: UInt32         // Which atlas page (for overflow)
    public var padding: SIMD3<UInt32>     // Alignment padding

    public init(
        position: SIMD2<Float> = .zero,
        size: SIMD2<Float> = .zero,
        uvOrigin: SIMD2<Float> = .zero,
        uvSize: SIMD2<Float> = .zero,
        color: SIMD4<Float> = SIMD4<Float>(1, 1, 1, 1),
        atlasIndex: UInt32 = 0
    ) {
        self.position = position
        self.size = size
        self.uvOrigin = uvOrigin
        self.uvSize = uvSize
        self.color = color
        self.atlasIndex = atlasIndex
        self.padding = .zero
    }
}

/// Per-frame uniform data
public struct TextUniforms {
    public var projectionMatrix: simd_float4x4
    public var scrollOffset: SIMD2<Float>
    public var viewportSize: SIMD2<Float>
    public var atlasSize: SIMD2<Float>
    public var pxRange: Float              // MSDF pixel range for sharpness
    public var time: Float                 // For cursor blink animation
    public var padding: SIMD2<Float>       // Alignment

    public init(
        projectionMatrix: simd_float4x4 = matrix_identity_float4x4,
        scrollOffset: SIMD2<Float> = .zero,
        viewportSize: SIMD2<Float> = .zero,
        atlasSize: SIMD2<Float> = SIMD2<Float>(2048, 2048),
        pxRange: Float = 4.0,
        time: Float = 0
    ) {
        self.projectionMatrix = projectionMatrix
        self.scrollOffset = scrollOffset
        self.viewportSize = viewportSize
        self.atlasSize = atlasSize
        self.pxRange = pxRange
        self.time = time
        self.padding = .zero
    }

    public static func orthographic(width: Float, height: Float) -> simd_float4x4 {
        let left: Float = 0
        let right = width
        let bottom = height
        let top: Float = 0
        let near: Float = -1
        let far: Float = 1

        let sx = 2 / (right - left)
        let sy = 2 / (top - bottom)
        let sz = -2 / (far - near)
        let tx = -(right + left) / (right - left)
        let ty = -(top + bottom) / (top - bottom)
        let tz = -(far + near) / (far - near)

        return simd_float4x4(columns: (
            SIMD4<Float>(sx, 0, 0, 0),
            SIMD4<Float>(0, sy, 0, 0),
            SIMD4<Float>(0, 0, sz, 0),
            SIMD4<Float>(tx, ty, tz, 1)
        ))
    }
}

// MARK: - Glyph Metrics

/// Font variant for different styles
public enum FontVariant: UInt32, Hashable {
    case regular = 0
    case bold = 1
    case italic = 2
    case boldItalic = 3

    public init(bold: Bool, italic: Bool) {
        switch (bold, italic) {
        case (false, false): self = .regular
        case (true, false): self = .bold
        case (false, true): self = .italic
        case (true, true): self = .boldItalic
        }
    }
}

/// Key for identifying a specific font face/size
public struct FontKey: Hashable {
    public let postScriptName: String
    public let size: CGFloat
    public let traits: UInt32

    public init(postScriptName: String, size: CGFloat, traits: UInt32) {
        self.postScriptName = postScriptName
        self.size = size
        self.traits = traits
    }

    public init(_ font: CTFont) {
        self.postScriptName = CTFontCopyPostScriptName(font) as String
        self.size = CTFontGetSize(font)
        self.traits = CTFontGetSymbolicTraits(font).rawValue
    }

    public static let custom = FontKey(postScriptName: "__custom__", size: 0, traits: 0)
}

/// Cached glyph information for rendering
public struct CachedGlyph: Hashable {
    public let glyphID: CGGlyph
    public let fontKey: FontKey
    public let atlasIndex: Int
    public let uvRect: CGRect              // UV coordinates in atlas (0-1 range)
    public let size: CGSize                // Glyph size in points
    public let bearing: CGPoint            // Horizontal/vertical bearing
    public let advance: CGFloat            // Horizontal advance width
    public let isColor: Bool               // True for color/emoji glyphs

    public init(
        glyphID: CGGlyph,
        fontKey: FontKey,
        atlasIndex: Int,
        uvRect: CGRect,
        size: CGSize,
        bearing: CGPoint,
        advance: CGFloat,
        isColor: Bool = false
    ) {
        self.glyphID = glyphID
        self.fontKey = fontKey
        self.atlasIndex = atlasIndex
        self.uvRect = uvRect
        self.size = size
        self.bearing = bearing
        self.advance = advance
        self.isColor = isColor
    }

    public func hash(into hasher: inout Hasher) {
        hasher.combine(glyphID)
        hasher.combine(fontKey)
    }

    public static func == (lhs: CachedGlyph, rhs: CachedGlyph) -> Bool {
        lhs.glyphID == rhs.glyphID && lhs.fontKey == rhs.fontKey
    }
}

/// Key for looking up glyphs in the atlas
public struct GlyphKey: Hashable {
    public let glyphID: CGGlyph
    public let fontKey: FontKey

    public init(glyphID: CGGlyph, fontKey: FontKey) {
        self.glyphID = glyphID
        self.fontKey = fontKey
    }
}

// MARK: - Shaped Glyph (from CoreText)

/// A glyph after text shaping (ligature substitution applied)
public struct ShapedGlyph {
    public let glyphID: CGGlyph
    public let position: CGPoint           // Position relative to line start
    public let advance: CGFloat
    public let font: CTFont
    public let characterIndex: Int         // Index in original string
    public let characterCount: Int         // Number of characters this glyph represents (for ligatures)

    public init(
        glyphID: CGGlyph,
        position: CGPoint,
        advance: CGFloat,
        font: CTFont,
        characterIndex: Int,
        characterCount: Int = 1
    ) {
        self.glyphID = glyphID
        self.position = position
        self.advance = advance
        self.font = font
        self.characterIndex = characterIndex
        self.characterCount = characterCount
    }
}

// MARK: - Selection Quad

/// A rectangle for selection or cursor rendering
public struct SelectionQuad {
    public var position: SIMD2<Float>
    public var size: SIMD2<Float>
    public var color: SIMD4<Float>

    public init(position: SIMD2<Float>, size: SIMD2<Float>, color: SIMD4<Float>) {
        self.position = position
        self.size = size
        self.color = color
    }

    public init(rect: CGRect, color: NSColor) {
        self.position = SIMD2<Float>(Float(rect.origin.x), Float(rect.origin.y))
        self.size = SIMD2<Float>(Float(rect.width), Float(rect.height))
        self.color = color.simdColor
    }
}

// MARK: - Color Extensions

extension NSColor {
    public var simdColor: SIMD4<Float> {
        guard let rgb = usingColorSpace(.sRGB) else {
            return SIMD4<Float>(1, 1, 1, 1)
        }
        return SIMD4<Float>(
            Float(rgb.redComponent),
            Float(rgb.greenComponent),
            Float(rgb.blueComponent),
            Float(rgb.alphaComponent)
        )
    }
}
