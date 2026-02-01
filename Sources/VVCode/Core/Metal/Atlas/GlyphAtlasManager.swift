import Foundation
import Metal
import MetalKit
import CoreText
import CoreGraphics
import AppKit

/// Manages glyph texture atlases for Metal text rendering
/// Uses direct grayscale alpha mask (like Ghostty) instead of MSDF for crisp rendering
public final class GlyphAtlasManager {

    // MARK: - Constants

    public static let atlasSize = 1024
    public static let glyphPadding = 2

    // MARK: - Properties

    private let device: MTLDevice
    private var alphaAtlasPages: [MTLTexture] = []
    private var colorAtlasPages: [MTLTexture] = []
    private var glyphCache: [GlyphKey: CachedGlyph] = [:]
    private var customGlyphCache: [CustomGlyphKey: CachedGlyph] = [:]
    private var fonts: [FontVariant: CTFont] = [:]
    private var scaledFontCache: [FontKey: CTFont] = [:]

    // Scale factor for Retina displays
    private var scaleFactor: CGFloat = 2.0  // Default to 2x for Retina

    // Atlas packing state
    private var alphaAtlasIndex = 0
    private var alphaPackingX = 0
    private var alphaPackingY = 0
    private var alphaRowHeight = 0

    private var colorAtlasIndex = 0
    private var colorPackingX = 0
    private var colorPackingY = 0
    private var colorRowHeight = 0

    private let queue = DispatchQueue(label: "com.vvcode.glyphatlas")

    // MARK: - Initialization

    public init(device: MTLDevice, baseFont: NSFont, scaleFactor: CGFloat = 2.0) {
        self.device = device
        self.scaleFactor = scaleFactor
        setupFontVariants(baseFont: baseFont)
        createNewAlphaAtlasPage()
    }

    private func setupFontVariants(baseFont: NSFont) {
        let ctFont = baseFont as CTFont
        let baseSize = CTFontGetSize(ctFont)

        // Create fonts at base size (scale is applied during rasterization)
        fonts[.regular] = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(ctFont), baseSize, nil)

        // Bold
        if let boldDesc = CTFontCopyFontDescriptor(ctFont).withSymbolicTraits(.boldTrait, .boldTrait) {
            fonts[.bold] = CTFontCreateWithFontDescriptor(boldDesc, baseSize, nil)
        } else {
            fonts[.bold] = fonts[.regular]
        }

        // Italic
        if let italicDesc = CTFontCopyFontDescriptor(ctFont).withSymbolicTraits(.italicTrait, .italicTrait) {
            fonts[.italic] = CTFontCreateWithFontDescriptor(italicDesc, baseSize, nil)
        } else {
            fonts[.italic] = fonts[.regular]
        }

        // Bold Italic
        let boldItalicTraits: CTFontSymbolicTraits = [.boldTrait, .italicTrait]
        if let boldItalicDesc = CTFontCopyFontDescriptor(ctFont).withSymbolicTraits(boldItalicTraits, boldItalicTraits) {
            fonts[.boldItalic] = CTFontCreateWithFontDescriptor(boldItalicDesc, baseSize, nil)
        } else {
            fonts[.boldItalic] = fonts[.bold]
        }
    }

    // MARK: - Public API

    /// Get or create a cached glyph for rendering
    public func glyph(for glyphID: CGGlyph, variant: FontVariant) -> CachedGlyph? {
        guard let font = fonts[variant] else { return nil }
        return glyph(for: glyphID, font: font)
    }

    /// Get or create a cached glyph for rendering with a specific font
    public func glyph(for glyphID: CGGlyph, font: CTFont) -> CachedGlyph? {
        let fontKey = FontKey(font)
        let key = GlyphKey(glyphID: glyphID, fontKey: fontKey)

        if let cached = glyphCache[key] {
            return cached
        }

        return queue.sync {
            glyphUnsafe(for: glyphID, font: font, fontKey: fontKey)
        }
    }

    /// Internal glyph lookup - must be called from queue
    private func glyphUnsafe(for glyphID: CGGlyph, font: CTFont, fontKey: FontKey) -> CachedGlyph? {
        let key = GlyphKey(glyphID: glyphID, fontKey: fontKey)

        // Double-check after acquiring lock
        if let cached = glyphCache[key] {
            return cached
        }

        return rasterizeGlyph(glyphID: glyphID, font: font, fontKey: fontKey)
    }

    /// Get glyph for a character (convenience)
    public func glyph(for character: Character, variant: FontVariant) -> CachedGlyph? {
        return queue.sync {
            glyphUnsafe(for: character, variant: variant)
        }
    }

    public func customGlyph(
        kind: CustomGlyphKind,
        size: CGSize,
        lineWidth: CGFloat = 1.5,
        cornerRadius: CGFloat = 0
    ) -> CachedGlyph? {
        return queue.sync {
            customGlyphUnsafe(kind: kind, size: size, lineWidth: lineWidth, cornerRadius: cornerRadius)
        }
    }

    /// Internal character glyph lookup - must be called from queue
    private func glyphUnsafe(for character: Character, variant: FontVariant) -> CachedGlyph? {
        guard let font = fonts[variant] else { return nil }

        let text = String(character)
        var unichars = Array(text.utf16)
        var glyphs = [CGGlyph](repeating: 0, count: unichars.count)

        if CTFontGetGlyphsForCharacters(font, &unichars, &glyphs, unichars.count) {
            let fontKey = FontKey(font)
            return glyphUnsafe(for: glyphs[0], font: font, fontKey: fontKey)
        }

        let fallback = CTFontCreateForString(font, text as CFString, CFRangeMake(0, unichars.count))
        var fallbackGlyphs = [CGGlyph](repeating: 0, count: unichars.count)
        guard CTFontGetGlyphsForCharacters(fallback, &unichars, &fallbackGlyphs, unichars.count) else {
            return nil
        }

        let fontKey = FontKey(fallback)
        return glyphUnsafe(for: fallbackGlyphs[0], font: fallback, fontKey: fontKey)
    }

    private func customGlyphUnsafe(
        kind: CustomGlyphKind,
        size: CGSize,
        lineWidth: CGFloat,
        cornerRadius: CGFloat
    ) -> CachedGlyph? {
        let pixelWidth = max(1, Int(ceil(size.width * scaleFactor)))
        let pixelHeight = max(1, Int(ceil(size.height * scaleFactor)))
        let lineWidthPx = max(1, Int(round(lineWidth * scaleFactor)))
        let cornerRadiusPx = max(0, Int(round(cornerRadius * scaleFactor)))
        let key = CustomGlyphKey(
            kind: kind,
            width: pixelWidth,
            height: pixelHeight,
            lineWidth: lineWidthPx,
            cornerRadius: cornerRadiusPx
        )

        if let cached = customGlyphCache[key] {
            return cached
        }

        let padding = CGFloat(Self.glyphPadding)
        let glyphWidth = pixelWidth + Int(padding * 2)
        let glyphHeight = pixelHeight + Int(padding * 2)

        guard let alphaData = rasterizeCustomGlyphToAlpha(
            kind: kind,
            glyphWidth: glyphWidth,
            glyphHeight: glyphHeight,
            iconSize: CGSize(width: pixelWidth, height: pixelHeight),
            padding: padding,
            lineWidth: CGFloat(lineWidthPx),
            cornerRadius: CGFloat(cornerRadiusPx)
        ) else {
            return nil
        }

        if alphaPackingX + glyphWidth + Self.glyphPadding > Self.atlasSize {
            alphaPackingX = Self.glyphPadding
            alphaPackingY += alphaRowHeight + Self.glyphPadding
            alphaRowHeight = 0
        }

        if alphaPackingY + glyphHeight + Self.glyphPadding > Self.atlasSize {
            createNewAlphaAtlasPage()
        }

        let region = MTLRegion(
            origin: MTLOrigin(x: alphaPackingX, y: alphaPackingY, z: 0),
            size: MTLSize(width: glyphWidth, height: glyphHeight, depth: 1)
        )

        alphaAtlasPages[alphaAtlasIndex].replace(
            region: region,
            mipmapLevel: 0,
            withBytes: alphaData,
            bytesPerRow: glyphWidth
        )

        let uvRect = CGRect(
            x: CGFloat(alphaPackingX),
            y: CGFloat(alphaPackingY),
            width: CGFloat(glyphWidth),
            height: CGFloat(glyphHeight)
        )

        let screenWidth = CGFloat(pixelWidth) / scaleFactor
        let screenHeight = CGFloat(pixelHeight) / scaleFactor
        let cached = CachedGlyph(
            glyphID: key.glyphID,
            fontKey: .custom,
            atlasIndex: alphaAtlasIndex,
            uvRect: uvRect,
            size: CGSize(width: screenWidth, height: screenHeight),
            bearing: .zero,
            advance: screenWidth
        )

        alphaPackingX += glyphWidth + Self.glyphPadding
        alphaRowHeight = max(alphaRowHeight, glyphHeight)

        customGlyphCache[key] = cached

        return cached
    }

    /// Preload ASCII glyphs for fast startup
    public func preloadASCII() {
        queue.async { [weak self] in
            guard let self = self else { return }

            for variant in FontVariant.allCases {
                for codePoint in 32..<127 {
                    if let scalar = Unicode.Scalar(codePoint) {
                        _ = self.glyphUnsafe(for: Character(scalar), variant: variant)
                    }
                }
            }
        }
    }

    /// Get the current atlas texture
    public var atlasTexture: MTLTexture? {
        alphaAtlasPages.first
    }

    /// Get all atlas pages
    public var allAtlasTextures: [MTLTexture] {
        alphaAtlasPages
    }

    /// Get the current color atlas texture
    public var colorAtlasTexture: MTLTexture? {
        colorAtlasPages.first
    }

    /// Get all color atlas pages
    public var allColorAtlasTextures: [MTLTexture] {
        colorAtlasPages
    }

    // MARK: - Private Methods

    private func createNewAlphaAtlasPage() {
        let descriptor = MTLTextureDescriptor.texture2DDescriptor(
            pixelFormat: .r8Unorm,  // Grayscale alpha mask only
            width: Self.atlasSize,
            height: Self.atlasSize,
            mipmapped: false
        )
        descriptor.usage = [.shaderRead]
        descriptor.storageMode = device.hasUnifiedMemory ? .shared : .managed

        guard let texture = device.makeTexture(descriptor: descriptor) else {
            fatalError("Failed to create atlas texture")
        }

        alphaAtlasPages.append(texture)
        alphaAtlasIndex = alphaAtlasPages.count - 1
        alphaPackingX = Self.glyphPadding
        alphaPackingY = Self.glyphPadding
        alphaRowHeight = 0
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

    private func scaledFont(for fontKey: FontKey, font: CTFont) -> CTFont {
        if let cached = scaledFontCache[fontKey] {
            return cached
        }

        let scaledSize = CTFontGetSize(font) * scaleFactor
        let scaledFont = CTFontCreateCopyWithAttributes(font, scaledSize, nil, nil)
        scaledFontCache[fontKey] = scaledFont
        return scaledFont
    }

    private func isColorGlyph(_ glyphID: CGGlyph, font: CTFont) -> Bool {
        return CTFontCreatePathForGlyph(font, glyphID, nil) == nil
    }

    private func rasterizeGlyph(glyphID: CGGlyph, font: CTFont, fontKey: FontKey) -> CachedGlyph? {
        let scaledFont = scaledFont(for: fontKey, font: font)

        // Get glyph metrics
        var glyph = glyphID
        var boundingRect = CGRect.zero
        CTFontGetBoundingRectsForGlyphs(scaledFont, .horizontal, &glyph, &boundingRect, 1)

        var advance = CGSize.zero
        CTFontGetAdvancesForGlyphs(scaledFont, .horizontal, &glyph, &advance, 1)

        // Calculate rasterization size with padding
        let padding = CGFloat(Self.glyphPadding)
        let glyphWidth = Int(ceil(boundingRect.width + padding * 2))
        let glyphHeight = Int(ceil(boundingRect.height + padding * 2))

        guard glyphWidth > 0 && glyphHeight > 0 else {
            // Empty glyph (space, etc.) - advance still needs to be scaled
            return CachedGlyph(
                glyphID: glyphID,
                fontKey: fontKey,
                atlasIndex: alphaAtlasIndex,
                uvRect: .zero,
                size: .zero,
                bearing: .zero,
                advance: advance.width / scaleFactor
            )
        }

        let isColor = isColorGlyph(glyphID, font: font)

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
                font: scaledFont,
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
            // Check if we need to wrap to next row
            if alphaPackingX + glyphWidth + Self.glyphPadding > Self.atlasSize {
                alphaPackingX = Self.glyphPadding
                alphaPackingY += alphaRowHeight + Self.glyphPadding
                alphaRowHeight = 0
            }

            // Check if we need a new atlas page
            if alphaPackingY + glyphHeight + Self.glyphPadding > Self.atlasSize {
                createNewAlphaAtlasPage()
            }

            // Rasterize glyph to grayscale alpha texture
            guard let alphaData = rasterizeGlyphToAlpha(
                glyph: glyphID,
                font: scaledFont,
                boundingRect: boundingRect,
                width: glyphWidth,
                height: glyphHeight,
                padding: padding
            ) else {
                return nil
            }

            // Upload to atlas (grayscale r8Unorm - 1 byte per pixel)
            region = MTLRegion(
                origin: MTLOrigin(x: alphaPackingX, y: alphaPackingY, z: 0),
                size: MTLSize(width: glyphWidth, height: glyphHeight, depth: 1)
            )

            alphaAtlasPages[alphaAtlasIndex].replace(
                region: region,
                mipmapLevel: 0,
                withBytes: alphaData,
                bytesPerRow: glyphWidth  // 1 byte per pixel for r8Unorm
            )

            // Store UV in pixel coordinates (not normalized) for pixel-perfect sampling
            uvRect = CGRect(
                x: CGFloat(alphaPackingX),
                y: CGFloat(alphaPackingY),
                width: CGFloat(glyphWidth),
                height: CGFloat(glyphHeight)
            )

            atlasIndex = alphaAtlasIndex

            // Update packing position
            alphaPackingX += glyphWidth + Self.glyphPadding
            alphaRowHeight = max(alphaRowHeight, glyphHeight)
        }

        // Calculate bearing for positioning (in screen coordinates)
        // bearing.x: offset from pen position to left edge of glyph quad
        // bearing.y: offset from baseline to TOP of glyph quad (negative = above baseline)
        //
        // The baseline in the bitmap is at y = (padding - origin.y) from the bottom.
        // For descenders (origin.y < 0), baseline is higher in the bitmap.
        // In screen coordinates (Y-down), distance from quad top to baseline is:
        //   (glyphHeight - (padding - origin.y)) / scale = (glyphHeight - padding + origin.y) / scale
        //
        // Snap bearingY to device pixel grid to prevent vertical waviness.
        let bearingX = (boundingRect.origin.x - padding) / scaleFactor
        let rawBearingY = -(CGFloat(glyphHeight) - padding + boundingRect.origin.y) / scaleFactor
        let bearingY = round(rawBearingY * scaleFactor) / scaleFactor

        // Size in screen coordinates (for quad rendering)
        let screenWidth = CGFloat(glyphWidth) / scaleFactor
        let screenHeight = CGFloat(glyphHeight) / scaleFactor

        let cached = CachedGlyph(
            glyphID: glyphID,
            fontKey: fontKey,
            atlasIndex: atlasIndex,
            uvRect: uvRect,
            size: CGSize(width: screenWidth, height: screenHeight),
            bearing: CGPoint(x: bearingX, y: bearingY),
            advance: advance.width / scaleFactor,
            isColor: isColor
        )

        // Cache the glyph
        let key = GlyphKey(glyphID: glyphID, fontKey: fontKey)
        glyphCache[key] = cached

        return cached
    }

    /// Rasterize glyph to grayscale alpha mask
    private func rasterizeGlyphToAlpha(
        glyph: CGGlyph,
        font: CTFont,
        boundingRect: CGRect,
        width: Int,
        height: Int,
        padding: CGFloat
    ) -> [UInt8]? {
        // Create grayscale bitmap context
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

        // Setup context for high-quality rendering
        context.setAllowsAntialiasing(true)
        context.setShouldAntialias(true)
        context.setAllowsFontSmoothing(true)
        context.setShouldSmoothFonts(true)
        context.setShouldSubpixelPositionFonts(true)
        context.setShouldSubpixelQuantizeFonts(false)

        // Fill with black (transparent)
        context.setFillColor(gray: 0, alpha: 1)
        context.fill(CGRect(x: 0, y: 0, width: width, height: height))

        // Draw glyph in white (opaque)
        context.setFillColor(gray: 1, alpha: 1)

        // Translate to padding position
        context.translateBy(x: padding, y: padding)

        // Draw glyph at negated bearing (positions glyph so bounding box starts at origin)
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

    private func rasterizeCustomGlyphToAlpha(
        kind: CustomGlyphKind,
        glyphWidth: Int,
        glyphHeight: Int,
        iconSize: CGSize,
        padding: CGFloat,
        lineWidth: CGFloat,
        cornerRadius: CGFloat
    ) -> [UInt8]? {
        let bitsPerComponent = 8
        let bytesPerRow = glyphWidth
        var alphaData = [UInt8](repeating: 0, count: glyphWidth * glyphHeight)

        guard let context = CGContext(
            data: &alphaData,
            width: glyphWidth,
            height: glyphHeight,
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

        context.setFillColor(gray: 0, alpha: 1)
        context.fill(CGRect(x: 0, y: 0, width: glyphWidth, height: glyphHeight))

        context.translateBy(x: 0, y: CGFloat(glyphHeight))
        context.scaleBy(x: 1, y: -1)

        let rect = CGRect(x: padding, y: padding, width: iconSize.width, height: iconSize.height)

        switch kind {
        case .foldHoverBackground:
            let radius = max(0, min(cornerRadius, min(rect.width, rect.height) * 0.5))
            let path = CGPath(roundedRect: rect, cornerWidth: radius, cornerHeight: radius, transform: nil)
            context.addPath(path)
            context.setFillColor(gray: 1, alpha: 1)
            context.fillPath()
        case .foldChevronClosed, .foldChevronOpen:
            let inset = max(0, lineWidth)
            let chevronRect = rect.insetBy(dx: inset, dy: inset)
            let minX = chevronRect.minX
            let maxX = chevronRect.maxX
            let minY = chevronRect.minY
            let maxY = chevronRect.maxY
            let midX = chevronRect.midX
            let midY = chevronRect.midY

            let path = CGMutablePath()
            if kind == .foldChevronClosed {
                // Right-pointing chevron
                path.move(to: CGPoint(x: minX, y: minY))
                path.addLine(to: CGPoint(x: maxX, y: midY))
                path.addLine(to: CGPoint(x: minX, y: maxY))
            } else {
                // Down-pointing chevron
                path.move(to: CGPoint(x: minX, y: minY))
                path.addLine(to: CGPoint(x: midX, y: maxY))
                path.addLine(to: CGPoint(x: maxX, y: minY))
            }

            context.addPath(path)
            context.setStrokeColor(gray: 1, alpha: 1)
            context.setLineWidth(max(1, lineWidth))
            context.setLineJoin(.round)
            context.setLineCap(.round)
            context.strokePath()
        }

        return alphaData
    }

    /// Update the base font (recreates all variants and clears cache)
    public func updateFont(_ font: NSFont, scaleFactor: CGFloat? = nil) {
        queue.sync {
            if let scaleFactor = scaleFactor, scaleFactor > 0 {
                self.scaleFactor = scaleFactor
            }
            glyphCache.removeAll()
            customGlyphCache.removeAll()
            scaledFontCache.removeAll()
            alphaAtlasPages.removeAll()
            colorAtlasPages.removeAll()
            setupFontVariants(baseFont: font)
            createNewAlphaAtlasPage()
        }
    }
}

public enum CustomGlyphKind: Hashable {
    case foldChevronClosed
    case foldChevronOpen
    case foldHoverBackground
}

private struct CustomGlyphKey: Hashable {
    let kind: CustomGlyphKind
    let width: Int
    let height: Int
    let lineWidth: Int
    let cornerRadius: Int

    var glyphID: CGGlyph {
        switch kind {
        case .foldChevronClosed: return 0xFF01
        case .foldChevronOpen: return 0xFF02
        case .foldHoverBackground: return 0xFF03
        }
    }
}

// MARK: - FontVariant CaseIterable

extension FontVariant: CaseIterable {
    public static var allCases: [FontVariant] = [.regular, .bold, .italic, .boldItalic]
}

// MARK: - CTFontDescriptor Extension

extension CTFontDescriptor {
    func withSymbolicTraits(_ traits: CTFontSymbolicTraits, _ mask: CTFontSymbolicTraits) -> CTFontDescriptor? {
        guard let currentTraits = CTFontDescriptorCopyAttribute(self, kCTFontTraitsAttribute) as? [CFString: Any],
              let symbolicTraits = currentTraits[kCTFontSymbolicTrait] as? UInt32 else {
            // Create new traits
            let newTraits: [CFString: Any] = [kCTFontSymbolicTrait: traits.rawValue]
            return CTFontDescriptorCreateCopyWithAttributes(self, [kCTFontTraitsAttribute: newTraits] as CFDictionary)
        }

        let newSymbolicTraits = (symbolicTraits & ~mask.rawValue) | (traits.rawValue & mask.rawValue)
        var newTraits = currentTraits
        newTraits[kCTFontSymbolicTrait] = newSymbolicTraits

        return CTFontDescriptorCreateCopyWithAttributes(self, [kCTFontTraitsAttribute: newTraits] as CFDictionary)
    }
}
