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
    private var atlasPages: [MTLTexture] = []
    private var glyphCache: [GlyphKey: CachedGlyph] = [:]
    private var customGlyphCache: [CustomGlyphKey: CachedGlyph] = [:]
    private var fonts: [FontVariant: CTFont] = [:]

    // Scale factor for Retina displays
    private var scaleFactor: CGFloat = 2.0  // Default to 2x for Retina

    // Atlas packing state
    private var currentAtlasIndex = 0
    private var packingX = 0
    private var packingY = 0
    private var rowHeight = 0

    private let queue = DispatchQueue(label: "com.vvcode.glyphatlas")

    // MARK: - Initialization

    public init(device: MTLDevice, baseFont: NSFont, scaleFactor: CGFloat = 2.0) {
        self.device = device
        self.scaleFactor = scaleFactor
        setupFontVariants(baseFont: baseFont)
        createNewAtlasPage()
    }

    private func setupFontVariants(baseFont: NSFont) {
        let ctFont = baseFont as CTFont
        let baseSize = CTFontGetSize(ctFont)
        // Scale font size for Retina rendering
        let scaledSize = baseSize * scaleFactor

        // Create scaled fonts for high-quality rendering
        fonts[.regular] = CTFontCreateWithFontDescriptor(CTFontCopyFontDescriptor(ctFont), scaledSize, nil)

        // Bold
        if let boldDesc = CTFontCopyFontDescriptor(ctFont).withSymbolicTraits(.boldTrait, .boldTrait) {
            fonts[.bold] = CTFontCreateWithFontDescriptor(boldDesc, scaledSize, nil)
        } else {
            fonts[.bold] = fonts[.regular]
        }

        // Italic
        if let italicDesc = CTFontCopyFontDescriptor(ctFont).withSymbolicTraits(.italicTrait, .italicTrait) {
            fonts[.italic] = CTFontCreateWithFontDescriptor(italicDesc, scaledSize, nil)
        } else {
            fonts[.italic] = fonts[.regular]
        }

        // Bold Italic
        let boldItalicTraits: CTFontSymbolicTraits = [.boldTrait, .italicTrait]
        if let boldItalicDesc = CTFontCopyFontDescriptor(ctFont).withSymbolicTraits(boldItalicTraits, boldItalicTraits) {
            fonts[.boldItalic] = CTFontCreateWithFontDescriptor(boldItalicDesc, scaledSize, nil)
        } else {
            fonts[.boldItalic] = fonts[.bold]
        }
    }

    // MARK: - Public API

    /// Get or create a cached glyph for rendering
    public func glyph(for glyphID: CGGlyph, variant: FontVariant) -> CachedGlyph? {
        let key = GlyphKey(glyphID: glyphID, fontVariant: variant)

        if let cached = glyphCache[key] {
            return cached
        }

        return queue.sync {
            glyphUnsafe(for: glyphID, variant: variant)
        }
    }

    /// Internal glyph lookup - must be called from queue
    private func glyphUnsafe(for glyphID: CGGlyph, variant: FontVariant) -> CachedGlyph? {
        let key = GlyphKey(glyphID: glyphID, fontVariant: variant)

        // Double-check after acquiring lock
        if let cached = glyphCache[key] {
            return cached
        }

        guard let font = fonts[variant] else { return nil }
        return rasterizeGlyph(glyphID: glyphID, font: font, variant: variant)
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

        var unichars = Array(String(character).utf16)
        var glyphs = [CGGlyph](repeating: 0, count: unichars.count)

        guard CTFontGetGlyphsForCharacters(font, &unichars, &glyphs, unichars.count) else {
            return nil
        }

        return glyphUnsafe(for: glyphs[0], variant: variant)
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

        if packingX + glyphWidth + Self.glyphPadding > Self.atlasSize {
            packingX = Self.glyphPadding
            packingY += rowHeight + Self.glyphPadding
            rowHeight = 0
        }

        if packingY + glyphHeight + Self.glyphPadding > Self.atlasSize {
            createNewAtlasPage()
        }

        let region = MTLRegion(
            origin: MTLOrigin(x: packingX, y: packingY, z: 0),
            size: MTLSize(width: glyphWidth, height: glyphHeight, depth: 1)
        )

        atlasPages[currentAtlasIndex].replace(
            region: region,
            mipmapLevel: 0,
            withBytes: alphaData,
            bytesPerRow: glyphWidth
        )

        let uvRect = CGRect(
            x: CGFloat(packingX),
            y: CGFloat(packingY),
            width: CGFloat(glyphWidth),
            height: CGFloat(glyphHeight)
        )

        let screenWidth = CGFloat(pixelWidth) / scaleFactor
        let screenHeight = CGFloat(pixelHeight) / scaleFactor
        let cached = CachedGlyph(
            glyphID: key.glyphID,
            fontVariant: .regular,
            atlasIndex: currentAtlasIndex,
            uvRect: uvRect,
            size: CGSize(width: screenWidth, height: screenHeight),
            bearing: .zero,
            advance: screenWidth
        )

        packingX += glyphWidth + Self.glyphPadding
        rowHeight = max(rowHeight, glyphHeight)

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
        atlasPages.first
    }

    /// Get all atlas pages
    public var allAtlasTextures: [MTLTexture] {
        atlasPages
    }

    // MARK: - Private Methods

    private func createNewAtlasPage() {
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

        atlasPages.append(texture)
        currentAtlasIndex = atlasPages.count - 1
        packingX = Self.glyphPadding
        packingY = Self.glyphPadding
        rowHeight = 0
    }

    private func rasterizeGlyph(glyphID: CGGlyph, font: CTFont, variant: FontVariant) -> CachedGlyph? {
        // Get glyph metrics
        var glyph = glyphID
        var boundingRect = CGRect.zero
        CTFontGetBoundingRectsForGlyphs(font, .horizontal, &glyph, &boundingRect, 1)

        var advance = CGSize.zero
        CTFontGetAdvancesForGlyphs(font, .horizontal, &glyph, &advance, 1)

        // Calculate rasterization size with padding
        let padding = CGFloat(Self.glyphPadding)
        let glyphWidth = Int(ceil(boundingRect.width + padding * 2))
        let glyphHeight = Int(ceil(boundingRect.height + padding * 2))

        guard glyphWidth > 0 && glyphHeight > 0 else {
            // Empty glyph (space, etc.) - advance still needs to be scaled
            return CachedGlyph(
                glyphID: glyphID,
                fontVariant: variant,
                atlasIndex: currentAtlasIndex,
                uvRect: .zero,
                size: .zero,
                bearing: .zero,
                advance: advance.width / scaleFactor
            )
        }

        // Check if we need to wrap to next row
        if packingX + glyphWidth + Self.glyphPadding > Self.atlasSize {
            packingX = Self.glyphPadding
            packingY += rowHeight + Self.glyphPadding
            rowHeight = 0
        }

        // Check if we need a new atlas page
        if packingY + glyphHeight + Self.glyphPadding > Self.atlasSize {
            createNewAtlasPage()
        }

        // Rasterize glyph to grayscale alpha texture
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

        // Upload to atlas (grayscale r8Unorm - 1 byte per pixel)
        let region = MTLRegion(
            origin: MTLOrigin(x: packingX, y: packingY, z: 0),
            size: MTLSize(width: glyphWidth, height: glyphHeight, depth: 1)
        )

        atlasPages[currentAtlasIndex].replace(
            region: region,
            mipmapLevel: 0,
            withBytes: alphaData,
            bytesPerRow: glyphWidth  // 1 byte per pixel for r8Unorm
        )

        // Store UV in pixel coordinates (not normalized) for pixel-perfect sampling
        let uvRect = CGRect(
            x: CGFloat(packingX),
            y: CGFloat(packingY),
            width: CGFloat(glyphWidth),
            height: CGFloat(glyphHeight)
        )

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
            fontVariant: variant,
            atlasIndex: currentAtlasIndex,
            uvRect: uvRect,
            size: CGSize(width: screenWidth, height: screenHeight),
            bearing: CGPoint(x: bearingX, y: bearingY),
            advance: advance.width / scaleFactor
        )

        // Update packing position
        packingX += glyphWidth + Self.glyphPadding
        rowHeight = max(rowHeight, glyphHeight)

        // Cache the glyph
        let key = GlyphKey(glyphID: glyphID, fontVariant: variant)
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
            let inset = max(0, lineWidth * 0.5)
            let strokeRect = rect.insetBy(dx: inset, dy: inset)
            let minX = strokeRect.minX
            let maxX = strokeRect.maxX
            let minY = strokeRect.minY
            let maxY = strokeRect.maxY
            let midX = strokeRect.midX
            let midY = strokeRect.midY

            let path = CGMutablePath()
            if kind == .foldChevronClosed {
                path.move(to: CGPoint(x: minX, y: minY))
                path.addLine(to: CGPoint(x: maxX, y: midY))
                path.addLine(to: CGPoint(x: minX, y: maxY))
            } else {
                path.move(to: CGPoint(x: minX, y: minY))
                path.addLine(to: CGPoint(x: midX, y: maxY))
                path.addLine(to: CGPoint(x: maxX, y: minY))
            }

            context.addPath(path)
            context.setStrokeColor(gray: 1, alpha: 1)
            context.setLineWidth(lineWidth)
            context.setLineCap(.round)
            context.setLineJoin(.round)
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
            atlasPages.removeAll()
            setupFontVariants(baseFont: font)
            createNewAtlasPage()
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
