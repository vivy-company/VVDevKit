import Foundation
import AppKit
import VVHighlighting

/// Bridges Tree-sitter highlighting output to Metal renderer color format
public struct HighlightBridge {

    /// Convert HighlightRange from Tree-sitter to ColoredRange for Metal
    public static func convertToColoredRanges(
        highlights: [VVHighlighting.HighlightRange],
        theme: VVTheme
    ) -> [ColoredRange] {
        highlights.map { highlight in
            let color = colorForStyle(highlight.style, theme: theme)
            let variant = fontVariantForStyle(highlight.style)

            return ColoredRange(
                range: highlight.range,
                color: color,
                fontVariant: variant
            )
        }
    }

    /// Convert a HighlightStyle to SIMD color
    private static func colorForStyle(_ style: VVHighlighting.HighlightStyle, theme: VVTheme) -> SIMD4<Float> {
        style.color.simdColor
    }

    /// Determine font variant from style
    private static func fontVariantForStyle(_ style: VVHighlighting.HighlightStyle) -> FontVariant {
        FontVariant(bold: style.isBold, italic: style.isItalic)
    }
}
