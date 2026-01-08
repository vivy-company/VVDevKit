//  MarkdownGlyphAtlas.swift
//  VVMarkdown
//
//  Glyph atlas manager for markdown text rendering

import Foundation
import Metal
import MetalKit
import CoreText
import CoreGraphics

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

// MARK: - Cached Glyph

public struct MarkdownCachedGlyph {
    public let glyphID: CGGlyph
    public let fontVariant: FontVariant
    public let atlasIndex: Int
    public let uvRect: CGRect          // UV coordinates in pixel space
    public let size: CGSize            // Size in screen coordinates
    public let bearing: CGPoint        // Offset from pen position
    public let advance: CGFloat        // Horizontal advance
    public let isColor: Bool

    public init(
        glyphID: CGGlyph,
        fontVariant: FontVariant,
        atlasIndex: Int,
        uvRect: CGRect,
        size: CGSize,
        bearing: CGPoint,
        advance: CGFloat,
        isColor: Bool = false
    ) {
        self.glyphID = glyphID
        self.fontVariant = fontVariant
        self.atlasIndex = atlasIndex
        self.uvRect = uvRect
        self.size = size
        self.bearing = bearing
        self.advance = advance
        self.isColor = isColor
    }
}

// MARK: - Glyph Key

private struct GlyphKey: Hashable {
    let glyphID: CGGlyph
    let fontVariant: FontVariant
    let fontSize: Int  // Scaled font size for cache key
}

private struct FontKey: Hashable {
    let name: String
    let size: Int  // Scaled font size for cache key
}

private struct FontGlyphKey: Hashable {
    let glyphID: CGGlyph
    let fontKey: FontKey
}
// MARK: - Markdown Glyph Atlas

/// Manages glyph texture atlases for markdown Metal text rendering
public final class MarkdownGlyphAtlas {

    // MARK: - Constants

    public static let atlasSize = 4096
    public static let glyphPadding = 2

    // MARK: - Properties

    private let device: MTLDevice
    private var atlasPages: [MTLTexture] = []
    private var colorAtlasPages: [MTLTexture] = []
    private var glyphCache: [GlyphKey: MarkdownCachedGlyph] = [:]
    private var fontGlyphCache: [FontGlyphKey: MarkdownCachedGlyph] = [:]
    private var fonts: [FontVariant: [Int: CTFont]] = [:]  // Variant -> [fontSize -> font]
    private var fontCache: [FontKey: CTFont] = [:]

    private var baseFont: VVFont
    private var scaleFactor: CGFloat = 2.0

    // Atlas packing state
    private var currentAtlasIndex = 0
    private var packingX = 0
    private var packingY = 0
    private var rowHeight = 0
    private var colorAtlasIndex = 0
    private var colorPackingX = 0
    private var colorPackingY = 0
    private var colorRowHeight = 0

    private let queue = DispatchQueue(label: "com.vvmarkdown.glyphatlas")

    // MARK: - Initialization

    public init(device: MTLDevice, baseFont: VVFont, scaleFactor: CGFloat = 2.0) {
        self.device = device
        self.baseFont = baseFont
        self.scaleFactor = scaleFactor
        setupFontVariants()
        createNewAtlasPage()
    }

    private func setupFontVariants() {
        fonts = [:]
        for variant in [FontVariant.regular, .semibold, .semiboldItalic, .bold, .italic, .boldItalic, .monospace, .emoji] {
            fonts[variant] = [:]
        }
    }

    private func fontFor(variant: FontVariant, size: CGFloat) -> CTFont {
        let scaledSize = size * scaleFactor
        let intSize = Int(scaledSize)

        if let cached = fonts[variant]?[intSize] {
            return cached
        }

        let font: CTFont
        switch variant {
        case .regular:
            font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(baseFont as CTFont), scaledSize, nil)

        case .semibold:
            #if canImport(AppKit)
            let descriptor = baseFont.fontDescriptor.addingAttributes([
                NSFontDescriptor.AttributeName.traits: [
                    NSFontDescriptor.TraitKey.weight: NSFont.Weight.semibold
                ]
            ])
            if let semiboldFont = NSFont(descriptor: descriptor, size: scaledSize) {
                font = semiboldFont as CTFont
            } else {
                font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(baseFont as CTFont), scaledSize, nil)
            }
            #else
            let descriptor = baseFont.fontDescriptor.addingAttributes([
                UIFontDescriptor.AttributeName.traits: [
                    UIFontDescriptor.TraitKey.weight: UIFont.Weight.semibold
                ]
            ])
            let semiboldFont = UIFont(descriptor: descriptor, size: scaledSize)
            font = semiboldFont as CTFont
            #endif

        case .semiboldItalic:
            #if canImport(AppKit)
            let descriptor = baseFont.fontDescriptor.addingAttributes([
                NSFontDescriptor.AttributeName.traits: [
                    NSFontDescriptor.TraitKey.weight: NSFont.Weight.semibold
                ]
            ])
            if let semiboldFont = NSFont(descriptor: descriptor, size: scaledSize) {
                if let italic = NSFontManager.shared.convert(semiboldFont, toHaveTrait: .italicFontMask) as NSFont? {
                    font = italic as CTFont
                } else {
                    font = semiboldFont as CTFont
                }
            } else {
                font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(baseFont as CTFont), scaledSize, nil)
            }
            #else
            let descriptor = baseFont.fontDescriptor.addingAttributes([
                UIFontDescriptor.AttributeName.traits: [
                    UIFontDescriptor.TraitKey.weight: UIFont.Weight.semibold
                ]
            ])
            if let italicDescriptor = descriptor.withSymbolicTraits(.traitItalic) {
                let semiboldItalic = UIFont(descriptor: italicDescriptor, size: scaledSize)
                font = semiboldItalic as CTFont
            } else {
                let semiboldFont = UIFont(descriptor: descriptor, size: scaledSize)
                font = semiboldFont as CTFont
            }
            #endif

        case .bold:
            #if canImport(AppKit)
            let manager = NSFontManager.shared
            if let boldFont = manager.convert(baseFont, toHaveTrait: .boldFontMask) as CTFont? {
                font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(boldFont), scaledSize, nil)
            } else {
                font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(baseFont as CTFont), scaledSize, nil)
            }
            #else
            font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(baseFont as CTFont), scaledSize, nil)
            #endif

        case .italic:
            #if canImport(AppKit)
            let manager = NSFontManager.shared
            if let italicFont = manager.convert(baseFont, toHaveTrait: .italicFontMask) as CTFont? {
                font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(italicFont), scaledSize, nil)
            } else {
                font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(baseFont as CTFont), scaledSize, nil)
            }
            #else
            font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(baseFont as CTFont), scaledSize, nil)
            #endif

        case .boldItalic:
            #if canImport(AppKit)
            let manager = NSFontManager.shared
            if let boldItalicFont = manager.convert(baseFont, toHaveTrait: [.boldFontMask, .italicFontMask]) as CTFont? {
                font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(boldItalicFont), scaledSize, nil)
            } else {
                font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(baseFont as CTFont), scaledSize, nil)
            }
            #else
            font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(baseFont as CTFont), scaledSize, nil)
            #endif

        case .monospace:
            let monoFont = VVFont.monospacedSystemFont(ofSize: size, weight: .regular)
            font = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(monoFont as CTFont), scaledSize, nil)

        case .emoji:
            #if canImport(AppKit)
            let emojiFont = NSFont(name: "AppleColorEmoji", size: scaledSize) ?? NSFont.systemFont(ofSize: scaledSize)
            font = emojiFont as CTFont
            #else
            let emojiFont = UIFont(name: "AppleColorEmoji", size: scaledSize) ?? UIFont.systemFont(ofSize: scaledSize)
            font = emojiFont as CTFont
            #endif
        }

        fonts[variant]?[intSize] = font
        return font
    }

    private func normalizedFontName(_ name: String) -> String {
        switch name {
        case ".AppleColorEmojiUI":
            return "AppleColorEmoji"
        default:
            return name
        }
    }

    private func fontFor(name: String, size: CGFloat) -> CTFont {
        let intSize = Int(size * scaleFactor)
        let resolvedName = normalizedFontName(name)
        let key = FontKey(name: resolvedName, size: intSize)

        if let cached = fontCache[key] {
            return cached
        }

        let font = CTFontCreateWithName(resolvedName as CFString, size, nil)
        fontCache[key] = font
        return font
    }

    // MARK: - Public API

    /// Get or create a cached glyph for rendering
    public func glyph(for glyphID: CGGlyph, variant: FontVariant, fontSize: CGFloat) -> MarkdownCachedGlyph? {
        let intSize = Int(fontSize * scaleFactor)
        let key = GlyphKey(glyphID: glyphID, fontVariant: variant, fontSize: intSize)

        if let cached = glyphCache[key] {
            return cached
        }

        return queue.sync {
            glyphUnsafe(for: glyphID, variant: variant, fontSize: fontSize)
        }
    }

    private func glyphUnsafe(for glyphID: CGGlyph, variant: FontVariant, fontSize: CGFloat) -> MarkdownCachedGlyph? {
        let intSize = Int(fontSize * scaleFactor)
        let key = GlyphKey(glyphID: glyphID, fontVariant: variant, fontSize: intSize)

        if let cached = glyphCache[key] {
            return cached
        }

        let font = fontFor(variant: variant, size: fontSize)
        return rasterizeGlyph(glyphID: glyphID, font: font, variant: variant, fontSize: fontSize)
    }

    public func glyph(for glyphID: CGGlyph, font: CTFont, variant: FontVariant = .regular) -> MarkdownCachedGlyph? {
        let fontName = CTFontCopyPostScriptName(font) as String
        let intSize = Int(CTFontGetSize(font) * scaleFactor)
        let key = FontGlyphKey(glyphID: glyphID, fontKey: FontKey(name: fontName, size: intSize))

        if let cached = fontGlyphCache[key] {
            return cached
        }

        return queue.sync {
            let scaledFont = CTFontCreateCopyWithAttributes(font, CTFontGetSize(font) * scaleFactor, nil, nil)
            guard let cached = rasterizeGlyph(glyphID: glyphID, font: scaledFont, variant: variant, fontSize: CTFontGetSize(font), storeInVariantCache: false) else {
                return nil
            }
            fontGlyphCache[key] = cached
            return cached
        }
    }

    public func glyph(for glyphID: CGGlyph, fontName: String, fontSize: CGFloat, variant: FontVariant = .regular) -> MarkdownCachedGlyph? {
        let font = fontFor(name: fontName, size: fontSize)
        return glyph(for: glyphID, font: font, variant: variant)
    }

    /// Get glyph for a character
    public func glyph(for character: Character, variant: FontVariant, fontSize: CGFloat) -> MarkdownCachedGlyph? {
        return queue.sync {
            glyphUnsafe(for: character, variant: variant, fontSize: fontSize)
        }
    }

    private func glyphUnsafe(for character: Character, variant: FontVariant, fontSize: CGFloat) -> MarkdownCachedGlyph? {
        let font = fontFor(variant: variant, size: fontSize)

        let text = String(character)
        var unichars = Array(text.utf16)
        var glyphs = [CGGlyph](repeating: 0, count: unichars.count)

        if CTFontGetGlyphsForCharacters(font, &unichars, &glyphs, unichars.count) {
            return glyphUnsafe(for: glyphs[0], variant: variant, fontSize: fontSize)
        }

        let fallback = CTFontCreateForString(font, text as CFString, CFRangeMake(0, unichars.count))
        var fallbackGlyphs = [CGGlyph](repeating: 0, count: unichars.count)
        guard CTFontGetGlyphsForCharacters(fallback, &unichars, &fallbackGlyphs, unichars.count) else {
            return nil
        }

        let fontName = CTFontCopyPostScriptName(fallback) as String
        let fontKey = FontKey(name: fontName, size: Int(CTFontGetSize(fallback)))
        return glyphUnsafe(for: fallbackGlyphs[0], font: fallback, variant: variant, fontKey: fontKey, fontSize: fontSize)
    }

    private func glyphUnsafe(
        for glyphID: CGGlyph,
        font: CTFont,
        variant: FontVariant,
        fontKey: FontKey,
        fontSize: CGFloat
    ) -> MarkdownCachedGlyph? {
        let key = FontGlyphKey(glyphID: glyphID, fontKey: fontKey)
        if let cached = fontGlyphCache[key] {
            return cached
        }

        guard let cached = rasterizeGlyph(
            glyphID: glyphID,
            font: font,
            variant: variant,
            fontSize: fontSize,
            storeInVariantCache: false
        ) else {
            return nil
        }

        fontGlyphCache[key] = cached
        return cached
    }

    /// Preload ASCII glyphs for fast startup
    public func preloadASCII(fontSize: CGFloat) {
        queue.async { [weak self] in
            guard let self = self else { return }

        for variant in [FontVariant.regular, .semibold, .semiboldItalic, .bold, .italic, .boldItalic, .monospace, .emoji] {
            for codePoint in 32..<127 {
                if let scalar = Unicode.Scalar(codePoint) {
                    _ = self.glyphUnsafe(for: Character(scalar), variant: variant, fontSize: fontSize)
                }
            }
            }
        }
    }

    /// Get the current atlas texture
    public var atlasTexture: MTLTexture? {
        atlasPages.first
    }

    public var colorAtlasTexture: MTLTexture? {
        colorAtlasPages.first
    }

    /// Get all atlas pages
    public var allAtlasTextures: [MTLTexture] {
        atlasPages
    }

    public var allColorAtlasTextures: [MTLTexture] {
        colorAtlasPages
    }

    // MARK: - Private Methods

    private func createNewAtlasPage() {
        let descriptor = MTLTextureDescriptor.texture2DDescriptor(
            pixelFormat: .r8Unorm,
            width: Self.atlasSize,
            height: Self.atlasSize,
            mipmapped: false
        )
        descriptor.usage = [.shaderRead]
        descriptor.storageMode = device.hasUnifiedMemory ? .shared : .managed

        guard let texture = device.makeTexture(descriptor: descriptor) else {
            fatalError("Failed to create atlas texture")
        }

        atlasPages.append(texture)
        currentAtlasIndex = atlasPages.count - 1
        packingX = Self.glyphPadding
        packingY = Self.glyphPadding
        rowHeight = 0
    }

    private func createNewColorAtlasPage() {
        let descriptor = MTLTextureDescriptor.texture2DDescriptor(
            pixelFormat: .rgba8Unorm,
            width: Self.atlasSize,
            height: Self.atlasSize,
            mipmapped: false
        )
        descriptor.usage = [.shaderRead]
        descriptor.storageMode = device.hasUnifiedMemory ? .shared : .managed

        guard let texture = device.makeTexture(descriptor: descriptor) else {
            fatalError("Failed to create color atlas texture")
        }

        colorAtlasPages.append(texture)
        colorAtlasIndex = colorAtlasPages.count - 1
        colorPackingX = Self.glyphPadding
        colorPackingY = Self.glyphPadding
        colorRowHeight = 0
    }

    private func rasterizeGlyph(glyphID: CGGlyph, font: CTFont, variant: FontVariant, fontSize: CGFloat, storeInVariantCache: Bool = true) -> MarkdownCachedGlyph? {
        var glyph = glyphID
        var boundingRect = CGRect.zero
        CTFontGetBoundingRectsForGlyphs(font, .horizontal, &glyph, &boundingRect, 1)

        var advance = CGSize.zero
        CTFontGetAdvancesForGlyphs(font, .horizontal, &glyph, &advance, 1)

        let padding = CGFloat(Self.glyphPadding)
        let glyphWidth = Int(ceil(boundingRect.width + padding * 2))
        let glyphHeight = Int(ceil(boundingRect.height + padding * 2))

        guard glyphWidth > 0 && glyphHeight > 0 else {
            return MarkdownCachedGlyph(
                glyphID: glyphID,
                fontVariant: variant,
                atlasIndex: currentAtlasIndex,
                uvRect: .zero,
                size: .zero,
                bearing: .zero,
                advance: advance.width / scaleFactor
            )
        }

        let isColor = CTFontCreatePathForGlyph(font, glyphID, nil) == nil

        let region: MTLRegion
        let uvRect: CGRect
        let atlasIndex: Int

        if isColor {
            if colorAtlasPages.isEmpty {
                createNewColorAtlasPage()
            }

            if colorPackingX + glyphWidth + Self.glyphPadding > Self.atlasSize {
                colorPackingX = Self.glyphPadding
                colorPackingY += colorRowHeight + Self.glyphPadding
                colorRowHeight = 0
            }

            if colorPackingY + glyphHeight + Self.glyphPadding > Self.atlasSize {
                createNewColorAtlasPage()
            }

            guard let colorData = rasterizeGlyphToRGBA(
                glyph: glyphID,
                font: font,
                boundingRect: boundingRect,
                width: glyphWidth,
                height: glyphHeight,
                padding: padding
            ) else {
                return nil
            }

            region = MTLRegion(
                origin: MTLOrigin(x: colorPackingX, y: colorPackingY, z: 0),
                size: MTLSize(width: glyphWidth, height: glyphHeight, depth: 1)
            )

            colorAtlasPages[colorAtlasIndex].replace(
                region: region,
                mipmapLevel: 0,
                withBytes: colorData,
                bytesPerRow: glyphWidth * 4
            )

            uvRect = CGRect(
                x: CGFloat(colorPackingX),
                y: CGFloat(colorPackingY),
                width: CGFloat(glyphWidth),
                height: CGFloat(glyphHeight)
            )

            atlasIndex = colorAtlasIndex

            colorPackingX += glyphWidth + Self.glyphPadding
            colorRowHeight = max(colorRowHeight, glyphHeight)
        } else {
            if packingX + glyphWidth + Self.glyphPadding > Self.atlasSize {
                packingX = Self.glyphPadding
                packingY += rowHeight + Self.glyphPadding
                rowHeight = 0
            }

            if packingY + glyphHeight + Self.glyphPadding > Self.atlasSize {
                createNewAtlasPage()
            }

            guard let alphaData = rasterizeGlyphToAlpha(
                glyph: glyphID,
                font: font,
                boundingRect: boundingRect,
                width: glyphWidth,
                height: glyphHeight,
                padding: padding
            ) else {
                return nil
            }

            region = MTLRegion(
                origin: MTLOrigin(x: packingX, y: packingY, z: 0),
                size: MTLSize(width: glyphWidth, height: glyphHeight, depth: 1)
            )

            atlasPages[currentAtlasIndex].replace(
                region: region,
                mipmapLevel: 0,
                withBytes: alphaData,
                bytesPerRow: glyphWidth
            )

            uvRect = CGRect(
                x: CGFloat(packingX),
                y: CGFloat(packingY),
                width: CGFloat(glyphWidth),
                height: CGFloat(glyphHeight)
            )

            atlasIndex = currentAtlasIndex

            packingX += glyphWidth + Self.glyphPadding
            rowHeight = max(rowHeight, glyphHeight)
        }

        let bearingX = (boundingRect.origin.x - padding) / scaleFactor
        let rawBearingY = -(CGFloat(glyphHeight) - padding + boundingRect.origin.y) / scaleFactor
        let bearingY = round(rawBearingY * scaleFactor) / scaleFactor

        let screenWidth = CGFloat(glyphWidth) / scaleFactor
        let screenHeight = CGFloat(glyphHeight) / scaleFactor

        let cached = MarkdownCachedGlyph(
            glyphID: glyphID,
            fontVariant: variant,
            atlasIndex: atlasIndex,
            uvRect: uvRect,
            size: CGSize(width: screenWidth, height: screenHeight),
            bearing: CGPoint(x: bearingX, y: bearingY),
            advance: advance.width / scaleFactor,
            isColor: isColor
        )

        if storeInVariantCache {
            let intSize = Int(fontSize * scaleFactor)
            let key = GlyphKey(glyphID: glyphID, fontVariant: variant, fontSize: intSize)
            glyphCache[key] = cached
        }

        return cached
    }

    private func rasterizeGlyphToAlpha(
        glyph: CGGlyph,
        font: CTFont,
        boundingRect: CGRect,
        width: Int,
        height: Int,
        padding: CGFloat
    ) -> [UInt8]? {
        let bitsPerComponent = 8
        let bytesPerRow = width
        var alphaData = [UInt8](repeating: 0, count: width * height)

        guard let context = CGContext(
            data: &alphaData,
            width: width,
            height: height,
            bitsPerComponent: bitsPerComponent,
            bytesPerRow: bytesPerRow,
            space: CGColorSpaceCreateDeviceGray(),
            bitmapInfo: CGImageAlphaInfo.none.rawValue
        ) else {
            return nil
        }

        context.setAllowsAntialiasing(true)
        context.setShouldAntialias(true)
        context.setAllowsFontSmoothing(true)
        context.setShouldSmoothFonts(true)
        context.setShouldSubpixelPositionFonts(true)
        context.setShouldSubpixelQuantizeFonts(false)

        context.setFillColor(gray: 0, alpha: 1)
        context.fill(CGRect(x: 0, y: 0, width: width, height: height))

        context.setFillColor(gray: 1, alpha: 1)
        context.translateBy(x: padding, y: padding)

        var glyphID = glyph
        var position = CGPoint(x: -boundingRect.origin.x, y: -boundingRect.origin.y)
        CTFontDrawGlyphs(font, &glyphID, &position, 1, context)

        return alphaData
    }

    private func rasterizeGlyphToRGBA(
        glyph: CGGlyph,
        font: CTFont,
        boundingRect: CGRect,
        width: Int,
        height: Int,
        padding: CGFloat
    ) -> [UInt8]? {
        let bitsPerComponent = 8
        let bytesPerRow = width * 4
        var colorData = [UInt8](repeating: 0, count: width * height * 4)

        guard let context = CGContext(
            data: &colorData,
            width: width,
            height: height,
            bitsPerComponent: bitsPerComponent,
            bytesPerRow: bytesPerRow,
            space: CGColorSpaceCreateDeviceRGB(),
            bitmapInfo: CGImageAlphaInfo.premultipliedLast.rawValue
        ) else {
            return nil
        }

        context.setAllowsAntialiasing(true)
        context.setShouldAntialias(true)
        context.setAllowsFontSmoothing(true)
        context.setShouldSmoothFonts(true)
        context.setShouldSubpixelPositionFonts(true)
        context.setShouldSubpixelQuantizeFonts(false)

        context.setFillColor(red: 0, green: 0, blue: 0, alpha: 0)
        context.fill(CGRect(x: 0, y: 0, width: width, height: height))

        context.translateBy(x: padding, y: padding)

        var glyphID = glyph
        var position = CGPoint(x: -boundingRect.origin.x, y: -boundingRect.origin.y)
        CTFontDrawGlyphs(font, &glyphID, &position, 1, context)

        return colorData
    }

    /// Update the base font
    public func updateFont(_ font: VVFont, scaleFactor: CGFloat? = nil) {
        queue.sync {
            if let scaleFactor = scaleFactor, scaleFactor > 0 {
                self.scaleFactor = scaleFactor
            }
            self.baseFont = font
            glyphCache.removeAll()
            fontGlyphCache.removeAll()
            fonts.removeAll()
            fontCache.removeAll()
            atlasPages.removeAll()
            colorAtlasPages.removeAll()
            setupFontVariants()
            createNewAtlasPage()
        }
    }
}
