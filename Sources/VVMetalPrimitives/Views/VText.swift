import Foundation
import CoreGraphics
import CoreText

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

// MARK: - Font Spec

public struct VVFontSpec: Sendable, Hashable {
    public var name: String?
    public var size: CGFloat
    public var variant: VVFontVariant

    public init(name: String? = nil, size: CGFloat = 14, variant: VVFontVariant = .regular) {
        self.name = name
        self.size = size
        self.variant = variant
    }

    public static let body = VVFontSpec(size: 14, variant: .regular)
    public static let title = VVFontSpec(size: 24, variant: .bold)
    public static let headline = VVFontSpec(size: 18, variant: .semibold)
    public static let caption = VVFontSpec(size: 12, variant: .regular)
    public static let code = VVFontSpec(size: 13, variant: .monospace)

    public static func custom(name: String, size: CGFloat) -> VVFontSpec {
        VVFontSpec(name: name, size: size, variant: .regular)
    }

    func makeCTFont() -> CTFont {
        if let name {
            return CTFontCreateWithName(name as CFString, size, nil)
        }
        switch variant {
        case .monospace:
            return CTFontCreateWithName("Menlo" as CFString, size, nil)
        case .bold, .boldItalic:
            let base = CTFontCreateWithName(".AppleSystemUIFont" as CFString, size, nil)
            return CTFontCreateCopyWithSymbolicTraits(base, 0, nil, .traitBold, .traitBold) ?? base
        case .semibold, .semiboldItalic:
            let desc = CTFontDescriptorCreateWithAttributes([
                kCTFontFamilyNameAttribute: ".AppleSystemUIFont" as CFString,
                kCTFontTraitsAttribute: [kCTFontWeightTrait: 0.23] as CFDictionary
            ] as CFDictionary)
            return CTFontCreateWithFontDescriptor(desc, size, nil)
        case .italic:
            let base = CTFontCreateWithName(".AppleSystemUIFont" as CFString, size, nil)
            return CTFontCreateCopyWithSymbolicTraits(base, 0, nil, .traitItalic, .traitItalic) ?? base
        default:
            return CTFontCreateWithName(".AppleSystemUIFont" as CFString, size, nil)
        }
    }
}

// MARK: - VText

public enum VVTextTruncationMode: Sendable, Hashable {
    case clip
    case tail
}

public enum VVTextAlignment: Sendable, Hashable {
    case leading
    case center
    case trailing

    var ctAlignment: CTTextAlignment {
        switch self {
        case .leading:
            return .left
        case .center:
            return .center
        case .trailing:
            return .right
        }
    }
}

public struct VText: VVView {
    public var text: String
    public var font: VVFontSpec
    public var color: SIMD4<Float>?
    public var lineLimit: Int?
    public var truncationMode: VVTextTruncationMode
    public var alignment: VVTextAlignment
    public var lineSpacing: CGFloat

    public var maxLines: Int {
        get { lineLimit ?? 0 }
        set { lineLimit = newValue > 0 ? newValue : nil }
    }

    public init(
        _ text: String,
        font: VVFontSpec = .body,
        color: SIMD4<Float>? = nil,
        maxLines: Int = 0,
        truncationMode: VVTextTruncationMode = .tail,
        alignment: VVTextAlignment = .leading,
        lineSpacing: CGFloat = 0
    ) {
        self.text = text
        self.font = font
        self.color = color
        self.lineLimit = maxLines > 0 ? maxLines : nil
        self.truncationMode = truncationMode
        self.alignment = alignment
        self.lineSpacing = lineSpacing
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        guard !text.isEmpty else { return .empty }

        let resolvedColor = color ?? env.defaultTextColor
        let ctFont = font.makeCTFont()
        let ascent = CTFontGetAscent(ctFont)
        let descent = CTFontGetDescent(ctFont)
        let leading = CTFontGetLeading(ctFont)
        let lineHeight = ceil(ascent + descent + leading)
        let adjustedLineHeight = lineHeight + lineSpacing

        var ctAlignment = alignment.ctAlignment
        var spacing = lineSpacing
        let paragraphStyle = withUnsafePointer(to: &ctAlignment) { alignmentPointer in
            withUnsafePointer(to: &spacing) { spacingPointer in
                var paragraphSettings = [
                    CTParagraphStyleSetting(
                        spec: .alignment,
                        valueSize: MemoryLayout<CTTextAlignment>.size,
                        value: alignmentPointer
                    ),
                    CTParagraphStyleSetting(
                        spec: .lineSpacingAdjustment,
                        valueSize: MemoryLayout<CGFloat>.size,
                        value: spacingPointer
                    )
                ]
                return CTParagraphStyleCreate(&paragraphSettings, paragraphSettings.count)
            }
        }

        let attributes: [NSAttributedString.Key: Any] = [
            .font: ctFont,
            .ligature: 1 as NSNumber,
            .paragraphStyle: paragraphStyle
        ]
        let attrString = NSAttributedString(string: text, attributes: attributes)

        let framesetter = CTFramesetterCreateWithAttributedString(attrString)
        let framePath = CGMutablePath()
        let frameWidth = max(1, min(constraint.maxWidth, constraint.idealWidth ?? constraint.maxWidth))
        let limitedLines = lineLimit ?? 0
        let frameHeight: CGFloat = limitedLines > 0 ? adjustedLineHeight * CGFloat(limitedLines) + 1 : 100_000
        framePath.addRect(CGRect(x: 0, y: 0, width: frameWidth, height: frameHeight))
        let frame = CTFramesetterCreateFrame(framesetter, CFRangeMake(0, 0), framePath, nil)

        let lines = CTFrameGetLines(frame) as? [CTLine] ?? []
        guard !lines.isEmpty else { return .empty }

        var effectiveLines = limitedLines > 0 ? Array(lines.prefix(limitedLines)) : lines
        let visibleRange = CTFrameGetVisibleStringRange(frame)
        let requiresTruncation = limitedLines > 0 &&
            visibleRange.location + visibleRange.length < attrString.length &&
            truncationMode == .tail &&
            !effectiveLines.isEmpty
        if requiresTruncation, let lastLine = effectiveLines.last {
            let token = CTLineCreateWithAttributedString(NSAttributedString(string: "\u{2026}", attributes: attributes))
            effectiveLines[effectiveLines.count - 1] = CTLineCreateTruncatedLine(lastLine, Double(frameWidth), .end, token) ?? lastLine
        }

        var allGlyphs: [VVTextGlyph] = []
        var totalWidth: CGFloat = 0
        var y: CGFloat = 0

        for (lineIndex, line) in effectiveLines.enumerated() {
            let lineWidth = CGFloat(CTLineGetTypographicBounds(line, nil, nil, nil))
            totalWidth = max(totalWidth, lineWidth)

            let baselineY = y + ascent

            let runs = CTLineGetGlyphRuns(line) as? [CTRun] ?? []
            for run in runs {
                let glyphCount = CTRunGetGlyphCount(run)
                guard glyphCount > 0 else { continue }

                let runAttributes = CTRunGetAttributes(run) as NSDictionary
                let runFont = runAttributes[kCTFontAttributeName] as! CTFont
                let storedFontName = storedFontName(for: runFont, requestedFont: ctFont)
                let storedFontDescriptorData = archivedFontDescriptorData(for: runFont)
                let runFontSize = CTFontGetSize(runFont)

                var runGlyphs = [CGGlyph](repeating: 0, count: glyphCount)
                CTRunGetGlyphs(run, CFRangeMake(0, glyphCount), &runGlyphs)

                var positions = [CGPoint](repeating: .zero, count: glyphCount)
                CTRunGetPositions(run, CFRangeMake(0, glyphCount), &positions)

                var advances = [CGSize](repeating: .zero, count: glyphCount)
                CTRunGetAdvances(run, CFRangeMake(0, glyphCount), &advances)

                var stringIndices = [CFIndex](repeating: 0, count: glyphCount)
                CTRunGetStringIndices(run, CFRangeMake(0, glyphCount), &stringIndices)

                for i in 0..<glyphCount {
                    let glyphID = runGlyphs[i]
                    guard glyphID != 0 else { continue }

                    let position = CGPoint(x: positions[i].x, y: baselineY)
                    let width = advances[i].width
                    let glyph = VVTextGlyph(
                        glyphID: glyphID,
                        position: position,
                        size: CGSize(width: width, height: adjustedLineHeight),
                        color: resolvedColor,
                        fontVariant: font.variant,
                        fontSize: runFontSize,
                        fontName: storedFontName,
                        fontDescriptorData: storedFontDescriptorData,
                        stringIndex: Int(stringIndices[i])
                    )
                    allGlyphs.append(glyph)
                }
            }

            if lineIndex < effectiveLines.count - 1 {
                y += adjustedLineHeight
            }
        }

        let totalHeight = y + adjustedLineHeight
        let textRun = VVTextRunPrimitive(
            glyphs: allGlyphs,
            style: VVTextRunStyle(color: resolvedColor),
            lineBounds: CGRect(x: 0, y: 0, width: totalWidth, height: totalHeight),
            runBounds: CGRect(x: 0, y: 0, width: totalWidth, height: totalHeight),
            position: .zero,
            fontSize: font.size
        )

        let node = VVNode(primitives: [.textRun(textRun)])
        return VVViewLayout(size: constraint.clamped(size: CGSize(width: min(totalWidth, frameWidth), height: totalHeight)), node: node)
    }

    public func lineLimit(_ limit: Int?) -> VText {
        var copy = self
        copy.lineLimit = limit
        return copy
    }

    public func truncationMode(_ mode: VVTextTruncationMode) -> VText {
        var copy = self
        copy.truncationMode = mode
        return copy
    }

    public func multilineTextAlignment(_ alignment: VVTextAlignment) -> VText {
        var copy = self
        copy.alignment = alignment
        return copy
    }

    public func lineSpacing(_ spacing: CGFloat) -> VText {
        var copy = self
        copy.lineSpacing = spacing
        return copy
    }

    private func isSystemUIFontName(_ name: String) -> Bool {
        if name.hasPrefix(".SF") || name.hasPrefix(".AppleSystem") {
            return true
        }
        if name == ".AppleColorEmojiUI" || name == "AppleColorEmoji" || name == "AppleColorEmojiUI" {
            return false
        }
        if name.hasPrefix(".") {
            return true
        }
        return false
    }

    private func storedFontName(for resolvedFont: CTFont, requestedFont: CTFont) -> String? {
        let resolvedName = CTFontCopyPostScriptName(resolvedFont) as String
        let requestedName = CTFontCopyPostScriptName(requestedFont) as String
        let usesRequestedFont =
            resolvedName == requestedName &&
            abs(CTFontGetSize(resolvedFont) - CTFontGetSize(requestedFont)) < 0.5

        if usesRequestedFont && isSystemUIFontName(resolvedName) {
            return nil
        }
        return resolvedName
    }

    private func archivedFontDescriptorData(for font: CTFont) -> Data? {
        let descriptor = (font as VVFont).fontDescriptor
        return try? NSKeyedArchiver.archivedData(withRootObject: descriptor, requiringSecureCoding: true)
    }
}
