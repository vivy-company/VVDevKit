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
    public var codeHeaderBackgroundColor: SIMD4<Float>
    public var codeHeaderTextColor: SIMD4<Float>
    public var codeHeaderDividerColor: SIMD4<Float>
    public var codeCopyButtonBackground: SIMD4<Float>
    public var codeCopyButtonTextColor: SIMD4<Float>
    public var codeBorderColor: SIMD4<Float>
    public var codeGutterBackgroundColor: SIMD4<Float>
    public var codeGutterTextColor: SIMD4<Float>
    public var codeBorderWidth: Float
    public var codeHeaderDividerHeight: Float
    public var codeCopyButtonCornerRadius: Float
    public var codeGutterDividerWidth: Float
    public var codeBlockCornerRadius: Float
    public var codeBlockHeaderHeight: Float
    public var blockQuoteColor: SIMD4<Float>
    public var blockQuoteBorderColor: SIMD4<Float>
    public var listBulletColor: SIMD4<Float>
    public var checkboxCheckedColor: SIMD4<Float>
    public var checkboxUncheckedColor: SIMD4<Float>
    public var thematicBreakColor: SIMD4<Float>
    public var tableHeaderBackground: SIMD4<Float>
    public var tableBackground: SIMD4<Float>
    public var tableBorderColor: SIMD4<Float>
    public var tableCornerRadius: Float
    public var diagramBackground: SIMD4<Float>
    public var diagramNodeBackground: SIMD4<Float>
    public var diagramNodeBorder: SIMD4<Float>
    public var diagramLineColor: SIMD4<Float>
    public var diagramTextColor: SIMD4<Float>
    public var diagramNoteBackground: SIMD4<Float>
    public var diagramNoteBorder: SIMD4<Float>
    public var diagramGroupBackground: SIMD4<Float>
    public var diagramGroupBorder: SIMD4<Float>
    public var diagramActivationColor: SIMD4<Float>
    public var diagramActivationBorder: SIMD4<Float>
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

    public var paragraphSpacing: Float = 6
    public var headingSpacing: Float = 4
    public var listIndent: Float = 16
    public var blockQuoteIndent: Float = 12
    public var blockQuoteBorderWidth: Float = 3
    public var codeBlockPadding: Float = 12
    public var tableRowPadding: Float = 6
    public var tableCellPadding: Float = 10
    public var contentPadding: Float = 16

    // MARK: - Initialization

    public init(
        textColor: SIMD4<Float> = SIMD4(0.9, 0.9, 0.9, 1.0),
        headingColor: SIMD4<Float> = SIMD4(1.0, 1.0, 1.0, 1.0),
        linkColor: SIMD4<Float> = SIMD4(0.4, 0.6, 1.0, 1.0),
        codeColor: SIMD4<Float> = SIMD4(0.9, 0.7, 0.5, 1.0),
        codeBackgroundColor: SIMD4<Float> = SIMD4(0.14, 0.14, 0.14, 1.0),
        codeHeaderBackgroundColor: SIMD4<Float> = SIMD4(0.11, 0.11, 0.11, 1.0),
        codeHeaderTextColor: SIMD4<Float> = SIMD4(0.85, 0.85, 0.85, 1.0),
        codeHeaderDividerColor: SIMD4<Float> = SIMD4(0.22, 0.22, 0.22, 1.0),
        codeCopyButtonBackground: SIMD4<Float> = SIMD4(0.24, 0.24, 0.24, 1.0),
        codeCopyButtonTextColor: SIMD4<Float> = SIMD4(0.95, 0.95, 0.95, 1.0),
        codeBorderColor: SIMD4<Float> = SIMD4(0.22, 0.22, 0.22, 1.0),
        codeGutterBackgroundColor: SIMD4<Float> = SIMD4(0.12, 0.12, 0.12, 1.0),
        codeGutterTextColor: SIMD4<Float> = SIMD4(0.55, 0.55, 0.55, 1.0),
        codeBorderWidth: Float = 1,
        codeHeaderDividerHeight: Float = 1,
        codeCopyButtonCornerRadius: Float = 6,
        codeGutterDividerWidth: Float = 1,
        codeBlockCornerRadius: Float = 12,
        codeBlockHeaderHeight: Float = 30,
        blockQuoteColor: SIMD4<Float> = SIMD4(0.7, 0.7, 0.7, 1.0),
        blockQuoteBorderColor: SIMD4<Float> = SIMD4(0.4, 0.4, 0.4, 1.0),
        listBulletColor: SIMD4<Float> = SIMD4(0.6, 0.6, 0.6, 1.0),
        checkboxCheckedColor: SIMD4<Float> = SIMD4(0.3, 0.8, 0.3, 1.0),
        checkboxUncheckedColor: SIMD4<Float> = SIMD4(0.5, 0.5, 0.5, 1.0),
        thematicBreakColor: SIMD4<Float> = SIMD4(0.3, 0.3, 0.3, 1.0),
        tableHeaderBackground: SIMD4<Float> = SIMD4(0.2, 0.2, 0.2, 1.0),
        tableBackground: SIMD4<Float> = SIMD4(0.16, 0.16, 0.16, 1.0),
        tableBorderColor: SIMD4<Float> = SIMD4(0.28, 0.28, 0.28, 1.0),
        tableCornerRadius: Float = 8,
        diagramBackground: SIMD4<Float> = SIMD4(0.14, 0.14, 0.14, 1.0),
        diagramNodeBackground: SIMD4<Float> = SIMD4(0.18, 0.18, 0.18, 1.0),
        diagramNodeBorder: SIMD4<Float> = SIMD4(0.3, 0.3, 0.3, 1.0),
        diagramLineColor: SIMD4<Float> = SIMD4(0.5, 0.5, 0.5, 1.0),
        diagramTextColor: SIMD4<Float> = SIMD4(0.9, 0.9, 0.9, 1.0),
        diagramNoteBackground: SIMD4<Float> = SIMD4(0.2, 0.2, 0.2, 1.0),
        diagramNoteBorder: SIMD4<Float> = SIMD4(0.35, 0.35, 0.35, 1.0),
        diagramGroupBackground: SIMD4<Float> = SIMD4(0.16, 0.16, 0.16, 0.7),
        diagramGroupBorder: SIMD4<Float> = SIMD4(0.35, 0.35, 0.35, 1.0),
        diagramActivationColor: SIMD4<Float> = SIMD4(0.22, 0.22, 0.22, 0.8),
        diagramActivationBorder: SIMD4<Float> = SIMD4(0.4, 0.4, 0.4, 1.0),
        mathColor: SIMD4<Float> = SIMD4(0.8, 0.6, 1.0, 1.0),
        strikethroughColor: SIMD4<Float> = SIMD4(0.6, 0.6, 0.6, 1.0)
    ) {
        self.textColor = textColor
        self.headingColor = headingColor
        self.linkColor = linkColor
        self.codeColor = codeColor
        self.codeBackgroundColor = codeBackgroundColor
        self.codeHeaderBackgroundColor = codeHeaderBackgroundColor
        self.codeHeaderTextColor = codeHeaderTextColor
        self.codeHeaderDividerColor = codeHeaderDividerColor
        self.codeCopyButtonBackground = codeCopyButtonBackground
        self.codeCopyButtonTextColor = codeCopyButtonTextColor
        self.codeBorderColor = codeBorderColor
        self.codeGutterBackgroundColor = codeGutterBackgroundColor
        self.codeGutterTextColor = codeGutterTextColor
        self.codeBorderWidth = codeBorderWidth
        self.codeHeaderDividerHeight = codeHeaderDividerHeight
        self.codeCopyButtonCornerRadius = codeCopyButtonCornerRadius
        self.codeGutterDividerWidth = codeGutterDividerWidth
        self.codeBlockCornerRadius = codeBlockCornerRadius
        self.codeBlockHeaderHeight = codeBlockHeaderHeight
        self.blockQuoteColor = blockQuoteColor
        self.blockQuoteBorderColor = blockQuoteBorderColor
        self.listBulletColor = listBulletColor
        self.checkboxCheckedColor = checkboxCheckedColor
        self.checkboxUncheckedColor = checkboxUncheckedColor
        self.thematicBreakColor = thematicBreakColor
        self.tableHeaderBackground = tableHeaderBackground
        self.tableBackground = tableBackground
        self.tableBorderColor = tableBorderColor
        self.tableCornerRadius = tableCornerRadius
        self.diagramBackground = diagramBackground
        self.diagramNodeBackground = diagramNodeBackground
        self.diagramNodeBorder = diagramNodeBorder
        self.diagramLineColor = diagramLineColor
        self.diagramTextColor = diagramTextColor
        self.diagramNoteBackground = diagramNoteBackground
        self.diagramNoteBorder = diagramNoteBorder
        self.diagramGroupBackground = diagramGroupBackground
        self.diagramGroupBorder = diagramGroupBorder
        self.diagramActivationColor = diagramActivationColor
        self.diagramActivationBorder = diagramActivationBorder
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
        codeHeaderBackgroundColor: SIMD4(0.9, 0.9, 0.9, 1.0),
        codeHeaderTextColor: SIMD4(0.3, 0.3, 0.3, 1.0),
        codeHeaderDividerColor: SIMD4(0.8, 0.8, 0.8, 1.0),
        codeCopyButtonBackground: SIMD4(0.8, 0.8, 0.8, 1.0),
        codeCopyButtonTextColor: SIMD4(0.1, 0.1, 0.1, 1.0),
        codeBorderColor: SIMD4(0.8, 0.8, 0.8, 1.0),
        codeGutterBackgroundColor: SIMD4(0.92, 0.92, 0.92, 1.0),
        codeGutterTextColor: SIMD4(0.5, 0.5, 0.5, 1.0),
        codeBlockCornerRadius: 10,
        codeBlockHeaderHeight: 30,
        blockQuoteColor: SIMD4(0.4, 0.4, 0.4, 1.0),
        blockQuoteBorderColor: SIMD4(0.7, 0.7, 0.7, 1.0),
        listBulletColor: SIMD4(0.5, 0.5, 0.5, 1.0),
        checkboxCheckedColor: SIMD4(0.2, 0.7, 0.2, 1.0),
        checkboxUncheckedColor: SIMD4(0.6, 0.6, 0.6, 1.0),
        thematicBreakColor: SIMD4(0.8, 0.8, 0.8, 1.0),
        tableHeaderBackground: SIMD4(0.9, 0.9, 0.9, 1.0),
        tableBackground: SIMD4(0.95, 0.95, 0.95, 1.0),
        tableBorderColor: SIMD4(0.8, 0.8, 0.8, 1.0),
        tableCornerRadius: 8,
        diagramBackground: SIMD4(0.95, 0.95, 0.95, 1.0),
        diagramNodeBackground: SIMD4(0.98, 0.98, 0.98, 1.0),
        diagramNodeBorder: SIMD4(0.75, 0.75, 0.75, 1.0),
        diagramLineColor: SIMD4(0.6, 0.6, 0.6, 1.0),
        diagramTextColor: SIMD4(0.2, 0.2, 0.2, 1.0),
        diagramNoteBackground: SIMD4(0.92, 0.92, 0.92, 1.0),
        diagramNoteBorder: SIMD4(0.75, 0.75, 0.75, 1.0),
        diagramGroupBackground: SIMD4(0.92, 0.92, 0.92, 0.6),
        diagramGroupBorder: SIMD4(0.75, 0.75, 0.75, 1.0),
        diagramActivationColor: SIMD4(0.85, 0.85, 0.85, 0.8),
        diagramActivationBorder: SIMD4(0.7, 0.7, 0.7, 1.0),
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
