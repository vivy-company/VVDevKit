//  MarkdownTheme.swift
//  VVMarkdown
//
//  Theme configuration for Metal-based markdown rendering

import Foundation
import simd

#if canImport(AppKit)
import AppKit
public typealias VVColor = NSColor
public typealias VVFont = NSFont
#else
import UIKit
public typealias VVColor = UIColor
public typealias VVFont = UIFont
#endif

// MARK: - Markdown Theme

/// Theme configuration for markdown rendering
public struct MarkdownTheme: Sendable {

    // MARK: - Text Colors

    public var textColor: SIMD4<Float>
    public var headingColor: SIMD4<Float>
    public var linkColor: SIMD4<Float>
    public var codeColor: SIMD4<Float>
    public var codeBackgroundColor: SIMD4<Float>
    public var blockQuoteColor: SIMD4<Float>
    public var blockQuoteBorderColor: SIMD4<Float>
    public var listBulletColor: SIMD4<Float>
    public var checkboxCheckedColor: SIMD4<Float>
    public var checkboxUncheckedColor: SIMD4<Float>
    public var thematicBreakColor: SIMD4<Float>
    public var tableHeaderBackground: SIMD4<Float>
    public var tableBorderColor: SIMD4<Float>
    public var mathColor: SIMD4<Float>
    public var strikethroughColor: SIMD4<Float>

    // MARK: - Font Sizes (relative to base)

    public var h1Scale: Float = 2.0
    public var h2Scale: Float = 1.5
    public var h3Scale: Float = 1.25
    public var h4Scale: Float = 1.1
    public var h5Scale: Float = 1.0
    public var h6Scale: Float = 0.9

    // MARK: - Spacing

    public var paragraphSpacing: Float = 16
    public var headingSpacing: Float = 24
    public var listIndent: Float = 20
    public var blockQuoteIndent: Float = 16
    public var blockQuoteBorderWidth: Float = 3
    public var codeBlockPadding: Float = 12
    public var tableRowPadding: Float = 8
    public var tableCellPadding: Float = 12
    public var contentPadding: Float = 24

    // MARK: - Initialization

    public init(
        textColor: SIMD4<Float> = SIMD4(0.9, 0.9, 0.9, 1.0),
        headingColor: SIMD4<Float> = SIMD4(1.0, 1.0, 1.0, 1.0),
        linkColor: SIMD4<Float> = SIMD4(0.4, 0.6, 1.0, 1.0),
        codeColor: SIMD4<Float> = SIMD4(0.9, 0.7, 0.5, 1.0),
        codeBackgroundColor: SIMD4<Float> = SIMD4(0.15, 0.15, 0.15, 1.0),
        blockQuoteColor: SIMD4<Float> = SIMD4(0.7, 0.7, 0.7, 1.0),
        blockQuoteBorderColor: SIMD4<Float> = SIMD4(0.4, 0.4, 0.4, 1.0),
        listBulletColor: SIMD4<Float> = SIMD4(0.6, 0.6, 0.6, 1.0),
        checkboxCheckedColor: SIMD4<Float> = SIMD4(0.3, 0.8, 0.3, 1.0),
        checkboxUncheckedColor: SIMD4<Float> = SIMD4(0.5, 0.5, 0.5, 1.0),
        thematicBreakColor: SIMD4<Float> = SIMD4(0.3, 0.3, 0.3, 1.0),
        tableHeaderBackground: SIMD4<Float> = SIMD4(0.2, 0.2, 0.2, 1.0),
        tableBorderColor: SIMD4<Float> = SIMD4(0.3, 0.3, 0.3, 1.0),
        mathColor: SIMD4<Float> = SIMD4(0.8, 0.6, 1.0, 1.0),
        strikethroughColor: SIMD4<Float> = SIMD4(0.6, 0.6, 0.6, 1.0)
    ) {
        self.textColor = textColor
        self.headingColor = headingColor
        self.linkColor = linkColor
        self.codeColor = codeColor
        self.codeBackgroundColor = codeBackgroundColor
        self.blockQuoteColor = blockQuoteColor
        self.blockQuoteBorderColor = blockQuoteBorderColor
        self.listBulletColor = listBulletColor
        self.checkboxCheckedColor = checkboxCheckedColor
        self.checkboxUncheckedColor = checkboxUncheckedColor
        self.thematicBreakColor = thematicBreakColor
        self.tableHeaderBackground = tableHeaderBackground
        self.tableBorderColor = tableBorderColor
        self.mathColor = mathColor
        self.strikethroughColor = strikethroughColor
    }

    // MARK: - Presets

    public static let dark = MarkdownTheme()

    public static let light = MarkdownTheme(
        textColor: SIMD4(0.1, 0.1, 0.1, 1.0),
        headingColor: SIMD4(0.0, 0.0, 0.0, 1.0),
        linkColor: SIMD4(0.0, 0.4, 0.8, 1.0),
        codeColor: SIMD4(0.6, 0.3, 0.1, 1.0),
        codeBackgroundColor: SIMD4(0.95, 0.95, 0.95, 1.0),
        blockQuoteColor: SIMD4(0.4, 0.4, 0.4, 1.0),
        blockQuoteBorderColor: SIMD4(0.7, 0.7, 0.7, 1.0),
        listBulletColor: SIMD4(0.5, 0.5, 0.5, 1.0),
        checkboxCheckedColor: SIMD4(0.2, 0.7, 0.2, 1.0),
        checkboxUncheckedColor: SIMD4(0.6, 0.6, 0.6, 1.0),
        thematicBreakColor: SIMD4(0.8, 0.8, 0.8, 1.0),
        tableHeaderBackground: SIMD4(0.9, 0.9, 0.9, 1.0),
        tableBorderColor: SIMD4(0.8, 0.8, 0.8, 1.0),
        mathColor: SIMD4(0.5, 0.2, 0.7, 1.0),
        strikethroughColor: SIMD4(0.5, 0.5, 0.5, 1.0)
    )

    // MARK: - Font Scale

    public func headingScale(for level: Int) -> Float {
        switch level {
        case 1: return h1Scale
        case 2: return h2Scale
        case 3: return h3Scale
        case 4: return h4Scale
        case 5: return h5Scale
        default: return h6Scale
        }
    }
}

// MARK: - Color Conversion

extension SIMD4 where Scalar == Float {

    #if canImport(AppKit)
    public init(nsColor: NSColor) {
        let color = nsColor.usingColorSpace(.sRGB) ?? nsColor
        var r: CGFloat = 0, g: CGFloat = 0, b: CGFloat = 0, a: CGFloat = 0
        color.getRed(&r, green: &g, blue: &b, alpha: &a)
        self.init(Float(r), Float(g), Float(b), Float(a))
    }
    #else
    public init(uiColor: UIColor) {
        var r: CGFloat = 0, g: CGFloat = 0, b: CGFloat = 0, a: CGFloat = 0
        uiColor.getRed(&r, green: &g, blue: &b, alpha: &a)
        self.init(Float(r), Float(g), Float(b), Float(a))
    }
    #endif
}
