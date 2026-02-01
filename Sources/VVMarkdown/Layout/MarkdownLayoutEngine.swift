//  MarkdownLayoutEngine.swift
//  VVMarkdown
//
//  Layout engine for markdown blocks - computes positions and sizes

import Foundation
import simd
import CoreText
import CoreGraphics

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

// MARK: - Layout Result

/// Result of laying out a markdown document
public struct MarkdownLayout {
    public let blocks: [LayoutBlock]
    public let totalHeight: CGFloat
    public let contentWidth: CGFloat

    public init(blocks: [LayoutBlock], totalHeight: CGFloat, contentWidth: CGFloat) {
        self.blocks = blocks
        self.totalHeight = totalHeight
        self.contentWidth = contentWidth
    }
}

/// A laid out block ready for rendering
public struct LayoutBlock {
    public let blockId: String
    public let blockType: LayoutBlockType
    public let frame: CGRect
    public let content: LayoutContent

    public init(blockId: String, blockType: LayoutBlockType, frame: CGRect, content: LayoutContent) {
        self.blockId = blockId
        self.blockType = blockType
        self.frame = frame
        self.content = content
    }
}

public enum LayoutBlockType {
    case paragraph
    case heading(level: Int)
    case codeBlock(language: String?)
    case list
    case blockQuote
    case alert(kind: MarkdownAlertKind)
    case table
    case definitionList
    case abbreviationList
    case image
    case thematicBreak
    case mathBlock
    case mermaid
}

/// Highlighted code token for rendering
public struct LayoutCodeToken: Sendable {
    public let text: String
    public let range: NSRange
    public let color: SIMD4<Float>
    public let isBold: Bool
    public let isItalic: Bool

    public init(text: String, range: NSRange, color: SIMD4<Float>, isBold: Bool = false, isItalic: Bool = false) {
        self.text = text
        self.range = range
        self.color = color
        self.isBold = isBold
        self.isItalic = isItalic
    }
}

/// Highlighted code line for rendering
public struct LayoutCodeLine: Sendable {
    public let lineNumber: Int
    public let text: String
    public let tokens: [LayoutCodeToken]
    public let yOffset: CGFloat

    public init(lineNumber: Int, text: String, tokens: [LayoutCodeToken], yOffset: CGFloat) {
        self.lineNumber = lineNumber
        self.text = text
        self.tokens = tokens
        self.yOffset = yOffset
    }
}

/// Rendered math glyph run
public struct LayoutMathRun: Sendable {
    public let text: String
    public let position: CGPoint
    public let fontSize: CGFloat
    public let color: SIMD4<Float>
    public let isItalic: Bool

    public init(text: String, position: CGPoint, fontSize: CGFloat, color: SIMD4<Float>, isItalic: Bool = true) {
        self.text = text
        self.position = position
        self.fontSize = fontSize
        self.color = color
        self.isItalic = isItalic
    }
}

/// Content within a layout block
public enum LayoutContent {
    case text([LayoutTextRun])
    case inline(text: [LayoutTextRun], images: [LayoutInlineImage])
    case imageRow([LayoutInlineImage])
    case code(String, language: String?, lines: [LayoutCodeLine])
    case listItems([LayoutListItem])
    case quoteBlocks([LayoutBlock])
    case tableRows([LayoutTableRow])
    case definitionList([LayoutDefinitionItem])
    case abbreviationList([LayoutAbbreviationItem])
    case image(url: String, alt: String?, size: CGSize?)
    case thematicBreak
    case math(latex: String, runs: [LayoutMathRun])
    case mermaid(LayoutMermaidDiagram)
}

/// Mermaid diagram layout primitives
public struct LayoutMermaidDiagram {
    public let frame: CGRect
    public let backgrounds: [LayoutMermaidBackground]
    public let nodes: [LayoutMermaidNode]
    public let lines: [LayoutMermaidLine]
    public let labels: [LayoutTextRun]
    public let pieSlices: [LayoutMermaidPieSlice]

    public init(
        frame: CGRect,
        backgrounds: [LayoutMermaidBackground],
        nodes: [LayoutMermaidNode],
        lines: [LayoutMermaidLine],
        labels: [LayoutTextRun],
        pieSlices: [LayoutMermaidPieSlice] = []
    ) {
        self.frame = frame
        self.backgrounds = backgrounds
        self.nodes = nodes
        self.lines = lines
        self.labels = labels
        self.pieSlices = pieSlices
    }
}

public struct LayoutDefinitionItem {
    public let termRuns: [LayoutTextRun]
    public let termImages: [LayoutInlineImage]
    public let definitionRuns: [[LayoutTextRun]]
    public let definitionImages: [[LayoutInlineImage]]
}

public struct LayoutAbbreviationItem {
    public let runs: [LayoutTextRun]
    public let images: [LayoutInlineImage]
}

public struct LayoutMermaidBackground {
    public let frame: CGRect
    public let cornerRadius: CGFloat
    public let fillColor: SIMD4<Float>
    public let borderColor: SIMD4<Float>?

    public init(frame: CGRect, cornerRadius: CGFloat, fillColor: SIMD4<Float>, borderColor: SIMD4<Float>? = nil) {
        self.frame = frame
        self.cornerRadius = cornerRadius
        self.fillColor = fillColor
        self.borderColor = borderColor
    }
}

public struct LayoutMermaidPieSlice {
    public let center: CGPoint
    public let radius: CGFloat
    public let startAngle: CGFloat
    public let endAngle: CGFloat
    public let color: SIMD4<Float>

    public init(center: CGPoint, radius: CGFloat, startAngle: CGFloat, endAngle: CGFloat, color: SIMD4<Float>) {
        self.center = center
        self.radius = radius
        self.startAngle = startAngle
        self.endAngle = endAngle
        self.color = color
    }
}

public enum LayoutMermaidNodeShape {
    case rect
    case round
    case circle
}

public struct LayoutMermaidNode {
    public let frame: CGRect
    public let shape: LayoutMermaidNodeShape
    public let fillColor: SIMD4<Float>
    public let borderColor: SIMD4<Float>
    public let labelRuns: [LayoutTextRun]

    public init(frame: CGRect, shape: LayoutMermaidNodeShape, fillColor: SIMD4<Float>, borderColor: SIMD4<Float>, labelRuns: [LayoutTextRun]) {
        self.frame = frame
        self.shape = shape
        self.fillColor = fillColor
        self.borderColor = borderColor
        self.labelRuns = labelRuns
    }
}

public struct LayoutMermaidLine {
    public let start: CGPoint
    public let end: CGPoint
    public let color: SIMD4<Float>
    public let width: Float
    public let isDashed: Bool

    public init(start: CGPoint, end: CGPoint, color: SIMD4<Float>, width: Float, isDashed: Bool = false) {
        self.start = start
        self.end = end
        self.color = color
        self.width = width
        self.isDashed = isDashed
    }
}

/// A run of styled text
public struct LayoutTextRun {
    public let text: String
    public let position: CGPoint
    public let glyphs: [LayoutGlyph]
    public let style: TextRunStyle
    public let characterRange: Range<Int>
    public let lineY: CGFloat?
    public let lineHeight: CGFloat?

    public init(
        text: String,
        position: CGPoint,
        glyphs: [LayoutGlyph],
        style: TextRunStyle,
        characterRange: Range<Int>,
        lineY: CGFloat? = nil,
        lineHeight: CGFloat? = nil
    ) {
        self.text = text
        self.position = position
        self.glyphs = glyphs
        self.style = style
        self.characterRange = characterRange
        self.lineY = lineY
        self.lineHeight = lineHeight
    }
}

/// Inline image rendered inside a paragraph (e.g. badge rows)
public struct LayoutInlineImage {
    public let url: String
    public let linkURL: String?
    public let frame: CGRect

    public init(url: String, linkURL: String?, frame: CGRect) {
        self.url = url
        self.linkURL = linkURL
        self.frame = frame
    }
}

/// Style for a text run
public struct TextRunStyle {
    public var isBold: Bool = false
    public var isItalic: Bool = false
    public var isCode: Bool = false
    public var isStrikethrough: Bool = false
    public var isLink: Bool = false
    public var linkURL: String?
    public var color: SIMD4<Float>
    public var fontVariant: FontVariant?

    public init(color: SIMD4<Float> = SIMD4(1, 1, 1, 1), fontVariant: FontVariant? = nil) {
        self.color = color
        self.fontVariant = fontVariant
    }
}

/// A positioned glyph
public struct LayoutGlyph {
    public let glyphID: CGGlyph
    public let position: CGPoint
    public let size: CGSize
    public let color: SIMD4<Float>
    public let fontVariant: FontVariant
    public let fontSize: CGFloat
    public let fontName: String?
    public let stringIndex: Int?

    public init(glyphID: CGGlyph, position: CGPoint, size: CGSize, color: SIMD4<Float>, fontVariant: FontVariant, fontSize: CGFloat = 14, fontName: String? = nil, stringIndex: Int? = nil) {
        self.glyphID = glyphID
        self.position = position
        self.size = size
        self.color = color
        self.fontVariant = fontVariant
        self.fontSize = fontSize
        self.fontName = fontName
        self.stringIndex = stringIndex
    }
}

/// Font variant for styling
public enum FontVariant: Hashable, Sendable {
    case regular
    case semibold
    case semiboldItalic
    case bold
    case italic
    case boldItalic
    case monospace
    case emoji
}

/// Layout list item
public struct LayoutListItem {
    public let depth: Int
    public let bulletPosition: CGPoint
    public let bulletType: BulletType
    public let contentRuns: [LayoutTextRun]
    public let inlineImages: [LayoutInlineImage]
    public let children: [LayoutListItem]

    public init(
        depth: Int,
        bulletPosition: CGPoint,
        bulletType: BulletType,
        contentRuns: [LayoutTextRun],
        inlineImages: [LayoutInlineImage] = [],
        children: [LayoutListItem]
    ) {
        self.depth = depth
        self.bulletPosition = bulletPosition
        self.bulletType = bulletType
        self.contentRuns = contentRuns
        self.inlineImages = inlineImages
        self.children = children
    }
}

public enum BulletType: Equatable {
    case disc
    case circle
    case square
    case number(Int)
    case checkboxChecked
    case checkboxUnchecked
}

/// Layout table row
public struct LayoutTableRow {
    public let cells: [LayoutTableCell]
    public let isHeader: Bool
    public let frame: CGRect

    public init(cells: [LayoutTableCell], isHeader: Bool, frame: CGRect) {
        self.cells = cells
        self.isHeader = isHeader
        self.frame = frame
    }
}

/// Layout table cell
public struct LayoutTableCell {
    public let textRuns: [LayoutTextRun]
    public let inlineImages: [LayoutInlineImage]
    public let frame: CGRect
    public let alignment: ColumnAlignment

    public init(textRuns: [LayoutTextRun], inlineImages: [LayoutInlineImage] = [], frame: CGRect, alignment: ColumnAlignment) {
        self.textRuns = textRuns
        self.inlineImages = inlineImages
        self.frame = frame
        self.alignment = alignment
    }
}

// MARK: - Markdown Layout Engine

/// Engine for laying out markdown documents
public final class MarkdownLayoutEngine {

    // MARK: - Properties

    private var baseFont: VVFont
    private var monoFont: VVFont
    private var theme: MarkdownTheme
    private var contentWidth: CGFloat
    private var scaleFactor: CGFloat
    private var imageSizeProvider: ((String) -> CGSize?)?
    private let mermaidParser = MermaidParser()
    private let mathRenderer = MarkdownMathRenderer()

    private var fonts: [FontVariant: CTFont] = [:]
    private var lineHeight: CGFloat = 20
    private var ascent: CGFloat = 14
    private var descent: CGFloat = 4
    private var baselineOffset: CGFloat = 14

    // MARK: - Initialization

    public init(
        baseFont: VVFont,
        monoFont: VVFont? = nil,
        theme: MarkdownTheme = .dark,
        contentWidth: CGFloat = 600,
        scaleFactor: CGFloat = 2.0
    ) {
        self.baseFont = baseFont
        self.monoFont = monoFont ?? VVFont.monospacedSystemFont(ofSize: baseFont.pointSize, weight: .regular)
        self.theme = theme
        self.contentWidth = contentWidth
        self.scaleFactor = scaleFactor
        setupFonts()
    }

    private func setupFonts() {
        let ctFont = baseFont as CTFont

        fonts[.regular] = ctFont

        #if canImport(AppKit)
        let semiboldDescriptor = baseFont.fontDescriptor.addingAttributes([
            NSFontDescriptor.AttributeName.traits: [
                NSFontDescriptor.TraitKey.weight: NSFont.Weight.semibold
            ]
        ])
        if let semiboldFont = NSFont(descriptor: semiboldDescriptor, size: baseFont.pointSize) {
            fonts[.semibold] = semiboldFont as CTFont
            let semiboldItalic = NSFontManager.shared.convert(semiboldFont, toHaveTrait: .italicFontMask)
            fonts[.semiboldItalic] = semiboldItalic as CTFont
        } else {
            fonts[.semibold] = ctFont
            fonts[.semiboldItalic] = ctFont
        }
        #else
        let semiboldDescriptor = baseFont.fontDescriptor.addingAttributes([
            UIFontDescriptor.AttributeName.traits: [
                UIFontDescriptor.TraitKey.weight: UIFont.Weight.semibold
            ]
        ])
        let semiboldFont = UIFont(descriptor: semiboldDescriptor, size: baseFont.pointSize)
        fonts[.semibold] = semiboldFont as CTFont
        if let italicDescriptor = semiboldDescriptor.withSymbolicTraits(.traitItalic) {
            let semiboldItalic = UIFont(descriptor: italicDescriptor, size: baseFont.pointSize)
            fonts[.semiboldItalic] = semiboldItalic as CTFont
        } else {
            fonts[.semiboldItalic] = semiboldFont as CTFont
        }
        #endif

        #if canImport(AppKit)
        let manager = NSFontManager.shared

        if let bold = manager.convert(baseFont, toHaveTrait: .boldFontMask) as CTFont? {
            fonts[.bold] = bold
        } else {
            fonts[.bold] = ctFont
        }

        if let italic = manager.convert(baseFont, toHaveTrait: .italicFontMask) as CTFont? {
            fonts[.italic] = italic
        } else {
            fonts[.italic] = ctFont
        }

        if let boldItalic = manager.convert(baseFont, toHaveTrait: [.boldFontMask, .italicFontMask]) as CTFont? {
            fonts[.boldItalic] = boldItalic
        } else {
            fonts[.boldItalic] = fonts[.bold]
        }
        #else
        fonts[.bold] = ctFont
        fonts[.italic] = ctFont
        fonts[.boldItalic] = ctFont
        #endif

        fonts[.monospace] = monoFont as CTFont

        #if canImport(AppKit)
        if let emojiFont = NSFont(name: "AppleColorEmoji", size: baseFont.pointSize) {
            fonts[.emoji] = emojiFont as CTFont
        } else {
            fonts[.emoji] = baseFont as CTFont
        }
        #else
        if let emojiFont = UIFont(name: "AppleColorEmoji", size: baseFont.pointSize) {
            fonts[.emoji] = emojiFont as CTFont
        } else {
            fonts[.emoji] = baseFont as CTFont
        }
        #endif

        ascent = CTFontGetAscent(ctFont)
        descent = CTFontGetDescent(ctFont)
        let leading = CTFontGetLeading(ctFont)
        lineHeight = ceil((ascent + descent + leading) * 1.05)
        let extraLeading = max(0, lineHeight - (ascent + descent))
        baselineOffset = ascent + extraLeading * 0.5
    }

    // MARK: - Public API

    public var currentLineHeight: CGFloat { lineHeight }
    public var currentAscent: CGFloat { ascent }
    public var currentDescent: CGFloat { descent }
    public var baseFontSize: CGFloat { baseFont.pointSize }

    public func font(for variant: FontVariant) -> CTFont? {
        fonts[variant]
    }

    public func updateTheme(_ theme: MarkdownTheme) {
        self.theme = theme
        mathRenderer.setMathColor(theme.mathColor)
    }

    public func updateContentWidth(_ width: CGFloat) {
        self.contentWidth = width
    }

    public func updateImageSizeProvider(_ provider: ((String) -> CGSize?)?) {
        self.imageSizeProvider = provider
    }

    /// Get glyphs for a number string (for list item number rendering)
    public func layoutNumberGlyphs(_ number: Int, at position: CGPoint, color: SIMD4<Float>) -> [LayoutGlyph] {
        let text = "\(number)."
        return layoutTextGlyphs(text, variant: .regular, at: position, color: color)
    }

    /// Get glyphs for code text (for code block rendering)
    public func layoutCodeGlyphs(_ text: String, at position: CGPoint, color: SIMD4<Float>) -> [LayoutGlyph] {
        return layoutGlyphsWithEmoji(text, baseVariant: .monospace, at: position, color: color)
    }

    /// Get glyphs for UI labels (e.g. copy button)
    public func layoutTextGlyphs(_ text: String, variant: FontVariant, at position: CGPoint, color: SIMD4<Float>) -> [LayoutGlyph] {
        return layoutGlyphsWithEmoji(text, baseVariant: variant, at: position, color: color)
    }

    private func layoutGlyphsWithEmoji(
        _ text: String,
        baseVariant: FontVariant,
        at position: CGPoint,
        color: SIMD4<Float>
    ) -> [LayoutGlyph] {
        guard !text.isEmpty else { return [] }
        guard let baseFont = fonts[baseVariant] else { return [] }
        let segments = splitFontSegments(text, baseFont: baseFont)
        var glyphs: [LayoutGlyph] = []
        var currentX = position.x
        for segment in segments {
            let result = layoutGlyphs(for: segment.text, font: segment.font, variant: baseVariant, color: color, startX: currentX, startY: position.y)
            glyphs.append(contentsOf: result.glyphs)
            currentX += result.advance
        }
        return glyphs
    }

    public func measureTextWidth(_ text: String, variant: FontVariant) -> CGFloat {
        guard let font = fonts[variant] else { return 0 }
        return measureTextWidth(text, font: font)
    }

    private func measureTextWidth(_ text: String, font: CTFont) -> CGFloat {
        guard !text.isEmpty else { return 0 }
        let attributes: [NSAttributedString.Key: Any] = [
            .font: font,
            .ligature: 1
        ]
        let line = CTLineCreateWithAttributedString(NSAttributedString(string: text, attributes: attributes))
        let width = CTLineGetTypographicBounds(line, nil, nil, nil)
        return CGFloat(width)
    }

    /// Get glyphs for math text (for math rendering)
    public func layoutMathGlyphs(_ text: String, at position: CGPoint, fontSize: CGFloat, color: SIMD4<Float>, isItalic: Bool) -> [LayoutGlyph] {
        let variant: FontVariant = isItalic ? .italic : .regular
        guard let baseFont = fonts[variant] else { return [] }
        let font = CTFontCreateCopyWithAttributes(baseFont, fontSize, nil, nil)
        let result = layoutGlyphs(for: text, font: font, variant: variant, color: color, startX: position.x, startY: position.y)
        return result.glyphs
    }

    /// Layout a parsed markdown document
    public func layout(_ document: ParsedMarkdownDocument) -> MarkdownLayout {
        var blocks: [LayoutBlock] = []
        let padding = CGFloat(theme.contentPadding)
        var currentY: CGFloat = padding

        for (index, block) in document.blocks.enumerated() {
            if isEmptyParagraph(block) {
                continue
            }
            let layoutBlock = layoutBlock(block, at: currentY)
            if isEmptyParagraphBlock(layoutBlock) {
                continue
            }
            blocks.append(layoutBlock)
            let nextBlock = nextNonEmptyBlock(after: index, in: document.blocks)
            currentY = layoutBlock.frame.maxY + blockSpacing(after: layoutBlock.blockType, currentBlock: block, nextBlock: nextBlock)
        }

        return MarkdownLayout(
            blocks: blocks,
            totalHeight: currentY + padding,
            contentWidth: contentWidth
        )
    }

    private func blockSpacing(after blockType: LayoutBlockType, currentBlock: MarkdownBlock, nextBlock: MarkdownBlock?) -> CGFloat {
        switch blockType {
        case .heading(let level):
            let base = CGFloat(theme.headingSpacing)
            let levelScale: CGFloat = level <= 2 ? 1.0 : 0.75
            var spacing = max(4, base * levelScale)
            if let nextBlock {
                switch nextBlock.type {
                case .heading:
                    spacing = max(2, base * 0.35)
                case .table, .codeBlock, .mermaid, .list, .blockQuote, .alert, .definitionList, .abbreviationList:
                    spacing = max(4, base * 0.6)
                default:
                    break
                }
            }
            return spacing
        case .paragraph:
            let baseSpacing = CGFloat(theme.paragraphSpacing)
            if isLinkOnlyParagraph(currentBlock) {
                if let nextBlock {
                    switch nextBlock.type {
                    case .paragraph where isLinkOnlyParagraph(nextBlock):
                        return max(1, baseSpacing * 0.2)
                    case .image:
                        return 0
                    default:
                        break
                    }
                }
            }
            if let nextBlock {
                switch nextBlock.type {
                case .image:
                    return 0
                case .paragraph(let content):
                    if let inlineImages = extractInlineImageElements(from: content), !inlineImages.isEmpty {
                        return 0
                    }
                default:
                    break
                }
            }
            return baseSpacing
        case .codeBlock, .mermaid:
            return max(CGFloat(theme.paragraphSpacing) * 1.2, lineHeight)
        case .definitionList, .abbreviationList:
            return max(4, CGFloat(theme.paragraphSpacing) * 0.8)
        default:
            return CGFloat(theme.paragraphSpacing)
        }
    }

    private func isEmptyParagraphBlock(_ block: LayoutBlock) -> Bool {
        guard case .paragraph = block.blockType else { return false }
        switch block.content {
        case .text(let runs):
            return runs.allSatisfy { $0.text.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty }
        case .inline(let runs, let images):
            return images.isEmpty && runs.allSatisfy { $0.text.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty }
        case .imageRow(let images):
            return images.isEmpty
        default:
            return false
        }
    }

    private func isLinkOnlyLayoutParagraph(_ block: LayoutBlock) -> Bool {
        guard case .paragraph = block.blockType else { return false }
        let runs: [LayoutTextRun]
        let images: [LayoutInlineImage]
        switch block.content {
        case .text(let textRuns):
            runs = textRuns
            images = []
        case .inline(let textRuns, let inlineImages):
            runs = textRuns
            images = inlineImages
        default:
            return false
        }
        guard images.isEmpty else { return false }
        var hasLink = false
        for run in runs {
            let trimmed = run.text.trimmingCharacters(in: .whitespacesAndNewlines)
            guard !trimmed.isEmpty else { continue }
            if run.style.isLink {
                hasLink = true
            } else {
                return false
            }
        }
        return hasLink
    }

    private func isImageLayoutBlock(_ block: LayoutBlock) -> Bool {
        switch block.content {
        case .image:
            return true
        case .imageRow(let images):
            return !images.isEmpty
        case .inline(let runs, let images):
            guard !images.isEmpty else { return false }
            let hasText = runs.contains { !$0.text.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty }
            return !hasText
        default:
            return false
        }
    }

    public func adjustParagraphImageSpacing(in layout: inout MarkdownLayout) {
        guard layout.blocks.count > 1 else { return }
        var updatedBlocks = layout.blocks
        var yAdjustment: CGFloat = 0
        let targetSpacing = max(2, lineHeight * 0.25)

        for index in 0..<updatedBlocks.count {
            if yAdjustment != 0 {
                updatedBlocks[index] = offsetLayoutBlock(updatedBlocks[index], dx: 0, dy: yAdjustment)
            }

            guard index < updatedBlocks.count - 1 else { continue }
            let current = updatedBlocks[index]
            let next = updatedBlocks[index + 1]
            guard isLinkOnlyLayoutParagraph(current) else { continue }
            guard isImageLayoutBlock(next) else { continue }

            let projectedNextMinY = next.frame.minY + yAdjustment
            let gap = projectedNextMinY - current.frame.maxY
            if gap > targetSpacing {
                yAdjustment += (targetSpacing - gap)
            }
        }

        if yAdjustment != 0 || updatedBlocks.count != layout.blocks.count {
            layout = MarkdownLayout(
                blocks: updatedBlocks,
                totalHeight: layout.totalHeight + yAdjustment,
                contentWidth: layout.contentWidth
            )
        }
    }

    private func isEmptyParagraph(_ block: MarkdownBlock) -> Bool {
        guard case .paragraph(let content) = block.type else { return false }
        guard !content.containsImages else { return false }
        return content.plainText.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty
    }

    private func isLinkOnlyParagraph(_ block: MarkdownBlock) -> Bool {
        guard case .paragraph(let content) = block.type else { return false }
        var hasLink = false
        for element in content.elements {
            switch element {
            case .link:
                hasLink = true
            case .text(let text):
                if !text.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty {
                    return false
                }
            case .softBreak, .hardBreak:
                continue
            default:
                return false
            }
        }
        return hasLink
    }

    private func nextNonEmptyBlock(after index: Int, in blocks: [MarkdownBlock]) -> MarkdownBlock? {
        guard index + 1 < blocks.count else { return nil }
        for nextIndex in (index + 1)..<blocks.count {
            let candidate = blocks[nextIndex]
            if isEmptyParagraph(candidate) { continue }
            return candidate
        }
        return nil
    }

    // MARK: - Block Layout

    private func layoutBlock(_ block: MarkdownBlock, at y: CGFloat) -> LayoutBlock {
        switch block.type {
        case .paragraph(let content):
            return layoutParagraph(block.id, content: content, at: y)

        case .heading(let content, let level):
            return layoutHeading(block.id, content: content, level: level, at: y)

        case .codeBlock(let code, let language, _):
            return layoutCodeBlock(block.id, code: code, language: language, at: y)

        case .list(let items, _, _):
            return layoutList(block.id, items: items, at: y)

        case .blockQuote(let nestedBlocks):
            return layoutBlockQuote(block.id, blocks: nestedBlocks, at: y)
        case .alert(let kind, let nestedBlocks):
            let labelHeight = lineHeight * 1.05
            let topInset = labelHeight + max(4, lineHeight * 0.2)
            return layoutBlockQuote(block.id, blocks: nestedBlocks, at: y, alertKind: kind, topInset: topInset)

        case .table(let rows, let alignments):
            return layoutTable(block.id, rows: rows, alignments: alignments, at: y)

        case .definitionList(let items):
            return layoutDefinitionList(block.id, items: items, at: y)

        case .abbreviationList(let items):
            return layoutAbbreviationList(block.id, items: items, at: y)

        case .image(let url, let alt):
            return layoutImage(block.id, url: url, alt: alt, at: y)

        case .thematicBreak:
            return layoutThematicBreak(block.id, at: y)

        case .mathBlock(let content):
            return layoutMathBlock(block.id, content: content, at: y)

        case .mermaid(let code):
            return layoutMermaidBlock(block.id, code: code, at: y)

        case .htmlBlock(let html):
            return layoutParagraph(block.id, content: MarkdownInlineContent(text: html), at: y)

        case .footnoteReference(let id):
            return layoutParagraph(block.id, content: MarkdownInlineContent(text: "[\(id)]"), at: y)

        case .footnoteDefinition(let id, let nestedBlocks):
            let content = MarkdownInlineContent(text: "[\(id)]: " + nestedBlocks.map { block in
                if case .paragraph(let c) = block.type { return c.plainText }
                return ""
            }.joined())
            return layoutParagraph(block.id, content: content, at: y)
        }
    }

    private func layoutParagraph(_ id: String, content: MarkdownInlineContent, at y: CGFloat) -> LayoutBlock {
        let padding = CGFloat(theme.contentPadding)
        if let standalone = extractStandaloneImage(from: content) {
            let availableWidth = max(0, contentWidth - padding * 2)
            let size = imageSizeProvider?(standalone.url) ?? inferImageSize(from: standalone.url)
            let displayWidth = min(availableWidth, size?.width ?? availableWidth)
            let aspectRatio = (size?.width ?? 1) / max(1, size?.height ?? 1)
            let fallbackHeight = max(120, lineHeight * 4.5)
            let displayHeight = size == nil ? fallbackHeight : (displayWidth / max(0.01, aspectRatio))
            let frame = CGRect(x: padding, y: y, width: displayWidth, height: displayHeight)
            let image = LayoutInlineImage(url: standalone.url, linkURL: standalone.linkURL, frame: frame)
            return LayoutBlock(
                blockId: id,
                blockType: .paragraph,
                frame: CGRect(x: padding, y: y, width: contentWidth - padding * 2, height: displayHeight),
                content: .inline(text: [], images: [image])
            )
        }

        if let imageRow = layoutImageRow(id: id, content: content, at: y) {
            return imageRow
        }

        let baseStyle = TextRunStyle(color: theme.textColor)
        let maxX = contentWidth - padding
        let inline = layoutInlineContent(content, baseStyle: baseStyle, startX: padding, startY: y, maxX: maxX)
        let height = inlineContentHeight(runs: inline.runs, images: inline.images, startY: y)
        let contentValue: LayoutContent = inline.images.isEmpty ? .text(inline.runs) : .inline(text: inline.runs, images: inline.images)

        return LayoutBlock(
            blockId: id,
            blockType: .paragraph,
            frame: CGRect(x: padding, y: y, width: contentWidth - padding * 2, height: height),
            content: contentValue
        )
    }

    private func layoutDefinitionList(_ id: String, items: [MarkdownDefinitionItem], at y: CGFloat) -> LayoutBlock {
        let padding = CGFloat(theme.contentPadding)
        let indent = max(16, CGFloat(theme.listIndent) * 1.1)
        let maxX = contentWidth - padding
        let definitionMaxX = contentWidth - padding
        let itemSpacing = max(2, lineHeight * 0.2)

        var layoutItems: [LayoutDefinitionItem] = []
        var currentY = y

        for item in items {
            var termStyle = TextRunStyle(color: theme.textColor)
            termStyle.fontVariant = .semibold
            let termInline = layoutInlineContent(item.term, baseStyle: termStyle, startX: padding, startY: currentY, maxX: maxX)
            let termHeight = inlineContentHeight(runs: termInline.runs, images: termInline.images, startY: currentY)
            currentY += termHeight + itemSpacing

            var defRuns: [[LayoutTextRun]] = []
            var defImages: [[LayoutInlineImage]] = []
            for definition in item.definitions {
                let defStyle = TextRunStyle(color: theme.textColor)
                let defInline = layoutInlineContent(definition, baseStyle: defStyle, startX: padding + indent, startY: currentY, maxX: definitionMaxX)
                let defHeight = inlineContentHeight(runs: defInline.runs, images: defInline.images, startY: currentY)
                defRuns.append(defInline.runs)
                defImages.append(defInline.images)
                currentY += defHeight + itemSpacing
            }

            layoutItems.append(LayoutDefinitionItem(
                termRuns: termInline.runs,
                termImages: termInline.images,
                definitionRuns: defRuns,
                definitionImages: defImages
            ))

            currentY += itemSpacing
        }

        return LayoutBlock(
            blockId: id,
            blockType: .definitionList,
            frame: CGRect(x: padding, y: y, width: contentWidth - padding * 2, height: currentY - y),
            content: .definitionList(layoutItems)
        )
    }

    private func layoutAbbreviationList(_ id: String, items: [MarkdownAbbreviationItem], at y: CGFloat) -> LayoutBlock {
        let padding = CGFloat(theme.contentPadding)
        let maxX = contentWidth - padding
        let itemSpacing = max(2, lineHeight * 0.2)

        var layoutItems: [LayoutAbbreviationItem] = []
        var currentY = y

        for item in items {
            let inline = MarkdownInlineContent(elements: [
                .strong(MarkdownInlineContent(text: item.abbreviation)),
                .text(" — "),
                .text(item.expansion)
            ])
            let baseStyle = TextRunStyle(color: theme.textColor)
            let result = layoutInlineContent(inline, baseStyle: baseStyle, startX: padding, startY: currentY, maxX: maxX)
            let height = inlineContentHeight(runs: result.runs, images: result.images, startY: currentY)
            layoutItems.append(LayoutAbbreviationItem(runs: result.runs, images: result.images))
            currentY += height + itemSpacing
        }

        return LayoutBlock(
            blockId: id,
            blockType: .abbreviationList,
            frame: CGRect(x: padding, y: y, width: contentWidth - padding * 2, height: currentY - y),
            content: .abbreviationList(layoutItems)
        )
    }

    private func layoutHeading(_ id: String, content: MarkdownInlineContent, level: Int, at y: CGFloat) -> LayoutBlock {
        let padding = CGFloat(theme.contentPadding)
        let scale = CGFloat(theme.headingScale(for: level))

        // Create scaled font for heading that preserves the base font family.
        #if canImport(AppKit)
        let headingFont = baseFont.withSize(baseFont.pointSize * scale)
        #else
        let headingFont = baseFont.withSize(baseFont.pointSize * scale)
        #endif
        let savedFont = baseFont
        baseFont = headingFont
        setupFonts()

        var baseStyle = TextRunStyle(color: theme.headingColor)
        if level <= 2 {
            baseStyle.isBold = true
        } else {
            baseStyle.fontVariant = .semibold
        }
        let maxX = contentWidth - padding
        let inline = layoutInlineContent(content, baseStyle: baseStyle, startX: padding, startY: y, maxX: maxX)
        var runs = inline.runs
        var images = inline.images
        var headingLineHeight = inlineContentHeight(runs: runs, images: images, startY: y)
        if let bounds = inlineContentBounds(runs: runs, images: images) {
            let dy = y - bounds.minY
            if abs(dy) > 0.1 {
                let shifted = offsetInlineContent(runs: runs, images: images, dx: 0, dy: dy)
                runs = shifted.runs
                images = shifted.images
            }
            headingLineHeight = max(bounds.height, lineHeight * 0.85)
        }

        baseFont = savedFont
        setupFonts()

        let height = headingLineHeight
        let contentValue: LayoutContent = images.isEmpty ? .text(runs) : .inline(text: runs, images: images)

        return LayoutBlock(
            blockId: id,
            blockType: .heading(level: level),
            frame: CGRect(x: padding, y: y, width: contentWidth - padding * 2, height: height),
            content: contentValue
        )
    }

    private func layoutCodeBlock(_ id: String, code: String, language: String?, at y: CGFloat) -> LayoutBlock {
        let contentPadding = CGFloat(theme.contentPadding)
        let codePadding = CGFloat(theme.codeBlockPadding)
        let headerHeight = CGFloat(theme.codeBlockHeaderHeight)
        let borderWidth = CGFloat(theme.codeBorderWidth)
        let codeLines = normalizedCodeLines(code)
        let maxLineNumber = max(1, codeLines.count)
        let gutterWidth = codeGutterWidth(for: maxLineNumber)

        let innerWidth = max(40, contentWidth - contentPadding * 2 - borderWidth * 2)
        let availableWidth = max(24, innerWidth - codePadding * 2 - gutterWidth)
        let charWidth = max(1, measureTextWidth("8", variant: .monospace))
        let maxChars = max(6, Int(floor(availableWidth / charWidth)))

        var layoutLines: [LayoutCodeLine] = []
        layoutLines.reserveCapacity(codeLines.count)
        var visualIndex = 0

        for (index, lineText) in codeLines.enumerated() {
            let wrapped = wrapCodeLine(lineText, maxChars: maxChars)
            if wrapped.isEmpty {
                let yOffset = codePadding + headerHeight + baselineOffset + CGFloat(visualIndex) * lineHeight
                let defaultToken = LayoutCodeToken(
                    text: "",
                    range: NSRange(location: 0, length: 0),
                    color: theme.codeColor
                )
                layoutLines.append(LayoutCodeLine(
                    lineNumber: index + 1,
                    text: "",
                    tokens: [defaultToken],
                    yOffset: yOffset
                ))
                visualIndex += 1
                continue
            }
            for (wrapIndex, segment) in wrapped.enumerated() {
                let yOffset = codePadding + headerHeight + baselineOffset + CGFloat(visualIndex) * lineHeight
                let defaultToken = LayoutCodeToken(
                    text: segment,
                    range: NSRange(location: 0, length: segment.utf16.count),
                    color: theme.codeColor
                )
                layoutLines.append(LayoutCodeLine(
                    lineNumber: wrapIndex == 0 ? (index + 1) : 0,
                    text: segment,
                    tokens: [defaultToken],
                    yOffset: yOffset
                ))
                visualIndex += 1
            }
        }

        let extraBottomPadding = max(4, codePadding * 0.5)
        let height = CGFloat(layoutLines.count) * lineHeight + codePadding * 2 + headerHeight + extraBottomPadding

        return LayoutBlock(
            blockId: id,
            blockType: .codeBlock(language: language),
            frame: CGRect(x: contentPadding, y: y, width: contentWidth - contentPadding * 2, height: height),
            content: .code(code, language: language, lines: layoutLines)
        )
    }

    private func wrapCodeLine(_ text: String, maxChars: Int) -> [String] {
        guard maxChars > 0 else { return [text] }
        let nsText = text as NSString
        let length = nsText.length
        guard length > 0 else { return [""] }
        var segments: [String] = []
        var index = 0
        while index < length {
            let count = min(maxChars, length - index)
            let part = nsText.substring(with: NSRange(location: index, length: count))
            segments.append(part)
            index += count
        }
        return segments
    }

    private func normalizedCodeLines(_ code: String) -> [String] {
        var lines = code
            .components(separatedBy: .newlines)
            .map { $0.replacingOccurrences(of: "\r", with: "") }
        while lines.count > 1, let first = lines.first, first.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty {
            lines.removeFirst()
        }
        while lines.count > 1, let last = lines.last, last.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty {
            lines.removeLast()
        }
        return lines
    }

    private func codeGutterWidth(for maxLineNumber: Int) -> CGFloat {
        let digits = max(1, String(maxLineNumber).count)
        let charWidth = measureTextWidth("8", variant: .monospace)
        return max(30, (CGFloat(digits) + 1.2) * charWidth)
    }

    private func layoutList(_ id: String, items: [MarkdownListItem], at y: CGFloat) -> LayoutBlock {
        var layoutItems: [LayoutListItem] = []
        var currentY = y

        for item in items {
            let (layoutItem, itemHeight) = layoutListItem(item, at: currentY)
            layoutItems.append(layoutItem)
            currentY += itemHeight
        }

        return LayoutBlock(
            blockId: id,
            blockType: .list,
            frame: CGRect(x: 0, y: y, width: contentWidth, height: currentY - y),
            content: .listItems(layoutItems)
        )
    }

    private func layoutListItem(_ item: MarkdownListItem, at y: CGFloat) -> (LayoutListItem, CGFloat) {
        let padding = CGFloat(theme.contentPadding)
        let indent = CGFloat(item.depth) * CGFloat(theme.listIndent)
        let bulletX = padding + indent
        let bulletGap: CGFloat = 8

        let bulletType: BulletType
        if let checkbox = item.checkbox {
            bulletType = checkbox == .checked ? .checkboxChecked : .checkboxUnchecked
        } else if item.listOrdered {
            bulletType = .number(item.listStartIndex + item.itemIndex)
        } else {
            switch item.depth % 3 {
            case 0: bulletType = .disc
            case 1: bulletType = .circle
            default: bulletType = .square
            }
        }

        let bulletWidth: CGFloat
        switch bulletType {
        case .number(let num):
            bulletWidth = measureTextWidth("\(num).", variant: .regular)
        case .checkboxChecked, .checkboxUnchecked:
            bulletWidth = max(10, lineHeight * 0.6)
        case .disc, .circle, .square:
            bulletWidth = max(6, min(10, lineHeight * 0.45))
        }

        let contentX = max(padding + indent + CGFloat(theme.listIndent), bulletX + bulletWidth + bulletGap)

        let isChecked = item.checkbox == .checked
        let color = isChecked ? theme.strikethroughColor : theme.textColor
        var baseStyle = TextRunStyle(color: color)
        if isChecked {
            baseStyle.isStrikethrough = true
        }
        let maxX = contentWidth - padding
        let inline = layoutInlineContent(item.content, baseStyle: baseStyle, startX: contentX, startY: y, maxX: maxX)
        let contentHeight = inlineContentHeight(runs: inline.runs, images: inline.images, startY: y)

        var totalHeight = contentHeight
        var childItems: [LayoutListItem] = []

        for child in item.children {
            let (childItem, childHeight) = layoutListItem(child, at: y + totalHeight)
            childItems.append(childItem)
            totalHeight += childHeight
        }

        let layoutItem = LayoutListItem(
            depth: item.depth,
            bulletPosition: CGPoint(x: bulletX, y: y + baselineOffset),
            bulletType: bulletType,
            contentRuns: inline.runs,
            inlineImages: inline.images,
            children: childItems
        )

        return (layoutItem, totalHeight)
    }

    private func layoutBlockQuote(
        _ id: String,
        blocks: [MarkdownBlock],
        at y: CGFloat,
        alertKind: MarkdownAlertKind? = nil,
        topInset: CGFloat = 0
    ) -> LayoutBlock {
        var nestedBlocks: [LayoutBlock] = []
        var currentY = y + topInset
        let padding = CGFloat(theme.contentPadding)
        let indent = CGFloat(theme.blockQuoteIndent)
        let shift = indent + CGFloat(theme.blockQuoteBorderWidth) + 4
        let interBlockSpacing = max(4, CGFloat(theme.paragraphSpacing) * 0.7)

        for block in blocks {
            let original = layoutBlock(block, at: currentY)
            var shifted = offsetLayoutBlock(original, dx: shift)
            shifted = LayoutBlock(
                blockId: shifted.blockId,
                blockType: shifted.blockType,
                frame: CGRect(
                    x: padding + shift,
                    y: shifted.frame.origin.y,
                    width: contentWidth - padding * 2 - shift,
                    height: shifted.frame.height
                ),
                content: shifted.content
            )
            nestedBlocks.append(shifted)
            currentY = shifted.frame.maxY + interBlockSpacing
        }

        let blockType: LayoutBlockType = alertKind.map { .alert(kind: $0) } ?? .blockQuote
        return LayoutBlock(
            blockId: id,
            blockType: blockType,
            frame: CGRect(x: padding, y: y, width: contentWidth - padding * 2, height: currentY - y),
            content: .quoteBlocks(nestedBlocks)
        )
    }

    private func offsetLayoutBlock(_ block: LayoutBlock, dx: CGFloat, dy: CGFloat = 0) -> LayoutBlock {
        let newFrame = CGRect(
            x: block.frame.origin.x + dx,
            y: block.frame.origin.y + dy,
            width: block.frame.width,
            height: block.frame.height
        )

        let newContent: LayoutContent
        switch block.content {
        case .text(let runs):
            let shifted = offsetInlineContent(runs: runs, images: [], dx: dx, dy: dy)
            newContent = .text(shifted.runs)
        case .inline(let runs, let images):
            let shifted = offsetInlineContent(runs: runs, images: images, dx: dx, dy: dy)
            newContent = .inline(text: shifted.runs, images: shifted.images)
        case .imageRow(let images):
            let shiftedImages = images.map { image in
                LayoutInlineImage(
                    url: image.url,
                    linkURL: image.linkURL,
                    frame: CGRect(
                        x: image.frame.origin.x + dx,
                        y: image.frame.origin.y + dy,
                        width: image.frame.width,
                        height: image.frame.height
                    )
                )
            }
            newContent = .imageRow(shiftedImages)
        case .listItems(let items):
            newContent = .listItems(offsetListItems(items, dx: dx, dy: dy))
        case .quoteBlocks(let blocks):
            newContent = .quoteBlocks(blocks.map { offsetLayoutBlock($0, dx: dx, dy: dy) })
        case .tableRows(let rows):
            newContent = .tableRows(offsetTableRows(rows, dx: dx, dy: dy))
        case .definitionList(let items):
            let shiftedItems = items.map { item in
                let termShifted = offsetInlineContent(runs: item.termRuns, images: item.termImages, dx: dx, dy: dy)
                var defRuns: [[LayoutTextRun]] = []
                var defImages: [[LayoutInlineImage]] = []
                for (index, runs) in item.definitionRuns.enumerated() {
                    let images = index < item.definitionImages.count ? item.definitionImages[index] : []
                    let shifted = offsetInlineContent(runs: runs, images: images, dx: dx, dy: dy)
                    defRuns.append(shifted.runs)
                    defImages.append(shifted.images)
                }
                return LayoutDefinitionItem(
                    termRuns: termShifted.runs,
                    termImages: termShifted.images,
                    definitionRuns: defRuns,
                    definitionImages: defImages
                )
            }
            newContent = .definitionList(shiftedItems)
        case .abbreviationList(let items):
            let shiftedItems = items.map { item in
                let shifted = offsetInlineContent(runs: item.runs, images: item.images, dx: dx, dy: dy)
                return LayoutAbbreviationItem(runs: shifted.runs, images: shifted.images)
            }
            newContent = .abbreviationList(shiftedItems)
        case .math(let latex, let runs):
            let shiftedRuns = runs.map { run in
                LayoutMathRun(
                    text: run.text,
                    position: CGPoint(x: run.position.x + dx, y: run.position.y + dy),
                    fontSize: run.fontSize,
                    color: run.color,
                    isItalic: run.isItalic
                )
            }
            newContent = .math(latex: latex, runs: shiftedRuns)
        case .mermaid(let diagram):
            newContent = .mermaid(offsetMermaidDiagram(diagram, dx: dx, dy: dy))
        default:
            newContent = block.content
        }

        return LayoutBlock(
            blockId: block.blockId,
            blockType: block.blockType,
            frame: newFrame,
            content: newContent
        )
    }

    private func offsetListItems(_ items: [LayoutListItem], dx: CGFloat, dy: CGFloat = 0) -> [LayoutListItem] {
        return items.map { item in
            let shifted = offsetInlineContent(runs: item.contentRuns, images: item.inlineImages, dx: dx, dy: dy)
            return LayoutListItem(
                depth: item.depth,
                bulletPosition: CGPoint(x: item.bulletPosition.x + dx, y: item.bulletPosition.y + dy),
                bulletType: item.bulletType,
                contentRuns: shifted.runs,
                inlineImages: shifted.images,
                children: offsetListItems(item.children, dx: dx, dy: dy)
            )
        }
    }

    private func offsetTableRows(_ rows: [LayoutTableRow], dx: CGFloat, dy: CGFloat = 0) -> [LayoutTableRow] {
        return rows.map { row in
            let shiftedCells = row.cells.map { cell in
                let shifted = offsetInlineContent(runs: cell.textRuns, images: cell.inlineImages, dx: dx, dy: dy)
                return LayoutTableCell(
                    textRuns: shifted.runs,
                    inlineImages: shifted.images,
                    frame: CGRect(
                        x: cell.frame.origin.x + dx,
                        y: cell.frame.origin.y + dy,
                        width: cell.frame.width,
                        height: cell.frame.height
                    ),
                    alignment: cell.alignment
                )
            }
            return LayoutTableRow(
                cells: shiftedCells,
                isHeader: row.isHeader,
                frame: CGRect(
                    x: row.frame.origin.x + dx,
                    y: row.frame.origin.y + dy,
                    width: row.frame.width,
                    height: row.frame.height
                )
            )
        }
    }

    private func offsetMermaidDiagram(_ diagram: LayoutMermaidDiagram, dx: CGFloat, dy: CGFloat = 0) -> LayoutMermaidDiagram {
        guard dx != 0 || dy != 0 else { return diagram }
        let shiftedBackgrounds = diagram.backgrounds.map { bg in
            LayoutMermaidBackground(
                frame: CGRect(x: bg.frame.origin.x + dx, y: bg.frame.origin.y + dy, width: bg.frame.width, height: bg.frame.height),
                cornerRadius: bg.cornerRadius,
                fillColor: bg.fillColor,
                borderColor: bg.borderColor
            )
        }
        let shiftedSlices = diagram.pieSlices.map { slice in
            LayoutMermaidPieSlice(
                center: CGPoint(x: slice.center.x + dx, y: slice.center.y + dy),
                radius: slice.radius,
                startAngle: slice.startAngle,
                endAngle: slice.endAngle,
                color: slice.color
            )
        }
        let shiftedNodes = diagram.nodes.map { node in
            let frame = CGRect(x: node.frame.origin.x + dx, y: node.frame.origin.y + dy, width: node.frame.width, height: node.frame.height)
            let shiftedRuns = offsetInlineContent(runs: node.labelRuns, images: [], dx: dx, dy: dy).runs
            return LayoutMermaidNode(frame: frame, shape: node.shape, fillColor: node.fillColor, borderColor: node.borderColor, labelRuns: shiftedRuns)
        }
        let shiftedLines = diagram.lines.map { line in
            LayoutMermaidLine(
                start: CGPoint(x: line.start.x + dx, y: line.start.y + dy),
                end: CGPoint(x: line.end.x + dx, y: line.end.y + dy),
                color: line.color,
                width: line.width,
                isDashed: line.isDashed
            )
        }
        let shiftedLabels = offsetInlineContent(runs: diagram.labels, images: [], dx: dx, dy: dy).runs
        let frame = CGRect(x: diagram.frame.origin.x + dx, y: diagram.frame.origin.y + dy, width: diagram.frame.width, height: diagram.frame.height)
        return LayoutMermaidDiagram(frame: frame, backgrounds: shiftedBackgrounds, nodes: shiftedNodes, lines: shiftedLines, labels: shiftedLabels, pieSlices: shiftedSlices)
    }

    private func layoutTable(_ id: String, rows: [MarkdownTableRow], alignments: [ColumnAlignment], at y: CGFloat) -> LayoutBlock {
        let contentPadding = CGFloat(theme.contentPadding)
        guard !rows.isEmpty else {
            return LayoutBlock(
                blockId: id,
                blockType: .table,
                frame: CGRect(x: contentPadding, y: y, width: contentWidth - contentPadding * 2, height: 0),
                content: .tableRows([])
            )
        }

        let columnCount = rows.first?.cells.count ?? 0
        let cellPadding = CGFloat(theme.tableCellPadding)
        let tableWidth = contentWidth - contentPadding * 2
        let columnWidth = (tableWidth - cellPadding * 2 * CGFloat(columnCount)) / CGFloat(max(1, columnCount))

        var layoutRows: [LayoutTableRow] = []
        var currentY = y

        for row in rows {
            var cellRuns: [[LayoutTextRun]] = []
            var cellImages: [[LayoutInlineImage]] = []
            var cellAlignments: [ColumnAlignment] = []
            var cellHeights: [CGFloat] = []
            var cellBounds: [CGRect?] = []
            var maxContentHeight: CGFloat = 0
            var cellX: CGFloat = contentPadding

            for (i, cell) in row.cells.enumerated() {
                let alignment = i < alignments.count ? alignments[i] : .left
                var baseStyle = TextRunStyle(color: row.isHeader ? theme.headingColor : theme.textColor)
                if row.isHeader {
                    baseStyle.isBold = true
                }
                let cellStartX = cellX + cellPadding
                let cellMaxX = cellX + columnWidth + cellPadding
                let extraLeading = max(0, lineHeight - (ascent + descent))
                let lineTopY = currentY + CGFloat(theme.tableRowPadding) + extraLeading * 0.5
                let inline = layoutInlineContent(
                    cell,
                    baseStyle: baseStyle,
                    startX: cellStartX,
                    startY: lineTopY,
                    maxX: cellMaxX
                )

                var runs = inline.runs
                var images = inline.images
                if let bounds = inlineContentBounds(runs: runs, images: images) {
                    let availableWidth = columnWidth
                    let contentWidth = bounds.width
                    let extra = max(0, availableWidth - contentWidth)
                    let dx: CGFloat
                    switch alignment {
                    case .center:
                        dx = extra * 0.5
                    case .right:
                        dx = extra
                    default:
                        dx = 0
                    }
                    if dx != 0 {
                        let shifted = offsetInlineContent(runs: runs, images: images, dx: dx)
                        runs = shifted.runs
                        images = shifted.images
                    }
                }

                let contentBounds = inlineContentBounds(runs: runs, images: images)
                let contentHeight = contentBounds?.height ?? inlineContentHeight(
                    runs: runs,
                    images: images,
                    startY: lineTopY
                )
                maxContentHeight = max(maxContentHeight, max(contentHeight, lineHeight))

                cellRuns.append(runs)
                cellImages.append(images)
                cellAlignments.append(alignment)
                cellHeights.append(contentHeight)
                cellBounds.append(contentBounds)
                cellX += columnWidth + cellPadding * 2
            }

            let rowHeight = maxContentHeight + CGFloat(theme.tableRowPadding) * 2
            var cells: [LayoutTableCell] = []
            cellX = contentPadding
            for idx in 0..<cellRuns.count {
                var runs = cellRuns[idx]
                var images = cellImages[idx]
                if let bounds = cellBounds[idx] {
                    let contentTop = currentY + CGFloat(theme.tableRowPadding)
                    let contentHeight = max(0, rowHeight - CGFloat(theme.tableRowPadding) * 2)
                    let targetTop = contentTop + max(0, contentHeight - bounds.height) * 0.5
                    let dy = targetTop - bounds.minY
                    if abs(dy) > 0.1 {
                        let shifted = offsetInlineContent(runs: runs, images: images, dx: 0, dy: dy)
                        runs = shifted.runs
                        images = shifted.images
                    }
                } else {
                    let contentHeight = max(0, rowHeight - CGFloat(theme.tableRowPadding) * 2)
                    let verticalOffset = max(0, (contentHeight - cellHeights[idx]) * 0.5)
                    if verticalOffset > 0 {
                        let shifted = offsetInlineContent(runs: runs, images: images, dx: 0, dy: verticalOffset)
                        runs = shifted.runs
                        images = shifted.images
                    }
                }
                let cellFrame = CGRect(
                    x: cellX,
                    y: currentY,
                    width: columnWidth + cellPadding * 2,
                    height: rowHeight
                )
                cells.append(
                    LayoutTableCell(
                        textRuns: runs,
                        inlineImages: images,
                        frame: cellFrame,
                        alignment: cellAlignments[idx]
                    )
                )
                cellX += columnWidth + cellPadding * 2
            }

            let rowFrame = CGRect(x: contentPadding, y: currentY, width: tableWidth, height: rowHeight)
            layoutRows.append(LayoutTableRow(cells: cells, isHeader: row.isHeader, frame: rowFrame))
            currentY += rowHeight
        }

        return LayoutBlock(
            blockId: id,
            blockType: .table,
            frame: CGRect(x: contentPadding, y: y, width: tableWidth, height: currentY - y),
            content: .tableRows(layoutRows)
        )
    }

    private func layoutImageRow(id: String, content: MarkdownInlineContent, at y: CGFloat) -> LayoutBlock? {
        guard let inlineImages = extractInlineImageElements(from: content), !inlineImages.isEmpty else {
            return nil
        }
        guard inlineImages.allSatisfy({ isBadgeImage($0.url) }) else {
            return nil
        }

        let padding = CGFloat(theme.contentPadding)
        let rowHeight = max(lineHeight, lineHeight * 1.12)
        let spacing = max(6, rowHeight * 0.35)
        let maxX = contentWidth - padding

        var x = padding
        var currentY = y
        var maxY = y + rowHeight
        var images: [LayoutInlineImage] = []

        for image in inlineImages {
            let size = imageSizeProvider?(image.url) ?? inferImageSize(from: image.url) ?? CGSize(width: rowHeight, height: rowHeight)
            let aspectRatio = size.width / max(1, size.height)
            let width = max(rowHeight, rowHeight * aspectRatio)
            if x + width > maxX && x > padding {
                x = padding
                currentY += rowHeight + spacing
            }
            let frame = CGRect(x: x, y: currentY, width: width, height: rowHeight)
            images.append(LayoutInlineImage(url: image.url, linkURL: image.linkURL, frame: frame))
            x += width + spacing
            maxY = max(maxY, currentY + rowHeight)
        }

        return LayoutBlock(
            blockId: id,
            blockType: .paragraph,
            frame: CGRect(x: padding, y: y, width: contentWidth - padding * 2, height: maxY - y),
            content: .imageRow(images)
        )
    }

    private func layoutImage(_ id: String, url: String, alt: String?, at y: CGFloat) -> LayoutBlock {
        let contentPadding = CGFloat(theme.contentPadding)
        if let imageSize = imageSizeProvider?(url) ?? inferImageSize(from: url) {
            let aspectRatio = imageSize.width / max(1, imageSize.height)
            let availableWidth = max(0, contentWidth - contentPadding * 2)
            let displayWidth = min(availableWidth, imageSize.width)
            let displayHeight = displayWidth / aspectRatio
            return LayoutBlock(
                blockId: id,
                blockType: .image,
                frame: CGRect(x: contentPadding, y: y, width: displayWidth, height: displayHeight),
                content: .image(url: url, alt: alt, size: imageSize)
            )
        }

        let placeholderHeight: CGFloat = max(100, lineHeight * 5.0)
        return LayoutBlock(
            blockId: id,
            blockType: .image,
            frame: CGRect(x: contentPadding, y: y, width: contentWidth - contentPadding * 2, height: placeholderHeight),
            content: .image(url: url, alt: alt, size: nil)
        )
    }

    private func inferImageSize(from url: String) -> CGSize? {
        let trimmed = url.trimmingCharacters(in: .whitespacesAndNewlines)
        guard !trimmed.isEmpty else { return nil }

        func validatedSize(width: Int, height: Int) -> CGSize? {
            guard width > 0, height > 0 else { return nil }
            let maxDimension = max(width, height)
            guard maxDimension <= 8192 else { return nil }
            return CGSize(width: CGFloat(width), height: CGFloat(height))
        }

        if let components = URLComponents(string: trimmed) {
            let queryItems = components.queryItems ?? []
            let widthValue = queryItems.first { ["w", "width"].contains($0.name.lowercased()) }?.value
            let heightValue = queryItems.first { ["h", "height"].contains($0.name.lowercased()) }?.value
            if let widthString = widthValue, let heightString = heightValue,
               let width = Int(widthString), let height = Int(heightString),
               let size = validatedSize(width: width, height: height) {
                return size
            }
            if let sizeItem = queryItems.first(where: { $0.name.lowercased() == "size" })?.value {
                if let match = sizeItem.range(of: #"(\d{2,5})x(\d{2,5})"#, options: .regularExpression) {
                    let parts = sizeItem[match].split(separator: "x")
                    if parts.count == 2,
                       let width = Int(parts[0]),
                       let height = Int(parts[1]),
                       let size = validatedSize(width: width, height: height) {
                        return size
                    }
                }
            }

            if let url = components.url {
                let pathParts = url.path.split(separator: "/")
                for part in pathParts {
                    if let match = part.range(of: #"(\d{2,5})x(\d{2,5})"#, options: .regularExpression) {
                        let pieces = part[match].split(separator: "x")
                        if pieces.count == 2,
                           let width = Int(pieces[0]),
                           let height = Int(pieces[1]),
                           let size = validatedSize(width: width, height: height) {
                            return size
                        }
                    }
                }

                if pathParts.count >= 2,
                   let width = Int(pathParts[pathParts.count - 2]),
                   let height = Int(pathParts[pathParts.count - 1]),
                   let size = validatedSize(width: width, height: height) {
                    return size
                }
            }
        }

        if let match = trimmed.range(of: #"(\d{2,5})x(\d{2,5})"#, options: .regularExpression) {
            let parts = trimmed[match].split(separator: "x")
            if parts.count == 2,
               let width = Int(parts[0]),
               let height = Int(parts[1]),
               let size = validatedSize(width: width, height: height) {
                return size
            }
        }

        let pathComponents = trimmed.split(separator: "/")
        if pathComponents.count >= 2 {
            let last = pathComponents[pathComponents.count - 1]
            let secondLast = pathComponents[pathComponents.count - 2]
            if let width = Int(secondLast), let height = Int(last),
               let size = validatedSize(width: width, height: height) {
                return size
            }
        }

        return nil
    }

    private func extractInlineImageElements(from content: MarkdownInlineContent) -> [(url: String, linkURL: String?)]? {
        var images: [(url: String, linkURL: String?)] = []

        for element in content.elements {
            switch element {
            case .image(let url, _, _):
                images.append((url, nil))

            case .link(let linkContent, let linkURL, _):
                guard let linkImages = extractInlineImageElements(from: linkContent) else {
                    return nil
                }
                if linkImages.isEmpty {
                    if linkContent.plainText.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty {
                        continue
                    }
                    return nil
                }
                images.append(contentsOf: linkImages.map { (url: $0.url, linkURL: linkURL) })

            case .text(let text):
                if !text.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty {
                    return nil
                }

            case .softBreak, .hardBreak:
                continue

            case .emphasis, .strong, .strikethrough, .code, .html, .math, .footnoteReference:
                return nil
            }
        }

        return images
    }

    private func extractStandaloneImage(from content: MarkdownInlineContent) -> (url: String, linkURL: String?)? {
        guard let images = extractInlineImageElements(from: content), images.count == 1 else {
            return nil
        }
        let image = images[0]
        if isBadgeImage(image.url) {
            return nil
        }
        return image
    }

    private func isBadgeImage(_ url: String) -> Bool {
        let lower = url.lowercased()
        return lower.contains("shields.io") || lower.contains("badgen.net")
    }

    /// Update layout for a specific image with loaded size
    public func updateImageLayout(in layout: inout MarkdownLayout, blockId: String, imageSize: CGSize) {
        var updatedBlocks = layout.blocks
        var yAdjustment: CGFloat = 0
        let contentPadding = CGFloat(theme.contentPadding)
        let availableWidth = max(0, contentWidth - contentPadding * 2)

        for i in 0..<updatedBlocks.count {
            var block = updatedBlocks[i]

            // Adjust position by accumulated adjustment
            if yAdjustment != 0 {
                block = LayoutBlock(
                    blockId: block.blockId,
                    blockType: block.blockType,
                    frame: CGRect(
                        x: block.frame.origin.x,
                        y: block.frame.origin.y + yAdjustment,
                        width: block.frame.width,
                        height: block.frame.height
                    ),
                    content: block.content
                )
            }

            if block.blockId == blockId {
                switch block.content {
                case .image(let url, let alt, _):
                    let aspectRatio = imageSize.width / max(1, imageSize.height)
                    let displayWidth = min(availableWidth, imageSize.width)
                    let displayHeight = displayWidth / aspectRatio
                    let oldHeight = block.frame.height

                    block = LayoutBlock(
                        blockId: block.blockId,
                        blockType: block.blockType,
                        frame: CGRect(
                            x: block.frame.origin.x,
                            y: block.frame.origin.y,
                            width: displayWidth,
                            height: displayHeight
                        ),
                        content: .image(url: url, alt: alt, size: imageSize)
                    )

                    yAdjustment += displayHeight - oldHeight
                case .inline(let runs, let images) where runs.isEmpty && images.count == 1:
                    let image = images[0]
                    let aspectRatio = imageSize.width / max(1, imageSize.height)
                    let displayWidth = min(availableWidth, imageSize.width)
                    let displayHeight = displayWidth / aspectRatio
                    let oldHeight = block.frame.height
                    let updatedImage = LayoutInlineImage(
                        url: image.url,
                        linkURL: image.linkURL,
                        frame: CGRect(
                            x: block.frame.origin.x,
                            y: block.frame.origin.y,
                            width: displayWidth,
                            height: displayHeight
                        )
                    )
                    block = LayoutBlock(
                        blockId: block.blockId,
                        blockType: block.blockType,
                        frame: CGRect(
                            x: block.frame.origin.x,
                            y: block.frame.origin.y,
                            width: block.frame.width,
                            height: displayHeight
                        ),
                        content: .inline(text: [], images: [updatedImage])
                    )
                    yAdjustment += displayHeight - oldHeight
                default:
                    break
                }
            }

            updatedBlocks[i] = block
        }

        layout = MarkdownLayout(
            blocks: updatedBlocks,
            totalHeight: layout.totalHeight + yAdjustment,
            contentWidth: layout.contentWidth
        )
    }

    /// Update inline image row layout (size/positions) without changing row height.
    public func updateInlineImageRowLayout(in layout: inout MarkdownLayout, blockId: String, imageSizes: [String: CGSize]) {
        guard !imageSizes.isEmpty else { return }

        var updatedBlocks = layout.blocks

        for i in 0..<updatedBlocks.count {
            let block = updatedBlocks[i]
            guard block.blockId == blockId, case .imageRow(let images) = block.content else { continue }

            var x = block.frame.origin.x
            var updatedImages: [LayoutInlineImage] = []
            let rowHeight = block.frame.height
            let spacing = max(6, rowHeight * 0.35)

            for image in images {
                let size = imageSizes[image.url] ?? CGSize(width: rowHeight, height: rowHeight)
                let aspectRatio = size.width / max(1, size.height)
                let width = rowHeight * aspectRatio
                let frame = CGRect(x: x, y: block.frame.origin.y, width: width, height: rowHeight)
                updatedImages.append(LayoutInlineImage(url: image.url, linkURL: image.linkURL, frame: frame))
                x += width + spacing
            }

            updatedBlocks[i] = LayoutBlock(
                blockId: block.blockId,
                blockType: block.blockType,
                frame: block.frame,
                content: .imageRow(updatedImages)
            )
        }

        layout = MarkdownLayout(
            blocks: updatedBlocks,
            totalHeight: layout.totalHeight,
            contentWidth: layout.contentWidth
        )
    }

    private func layoutThematicBreak(_ id: String, at y: CGFloat) -> LayoutBlock {
        let contentPadding = CGFloat(theme.contentPadding)
        return LayoutBlock(
            blockId: id,
            blockType: .thematicBreak,
            frame: CGRect(x: contentPadding, y: y, width: contentWidth - contentPadding * 2, height: 20),
            content: .thematicBreak
        )
    }

    private func layoutMathBlock(_ id: String, content: String, at y: CGFloat) -> LayoutBlock {
        // Math is rendered with padding like code blocks
        let contentPadding = CGFloat(theme.contentPadding)
        let codePadding = CGFloat(theme.codeBlockPadding)
        let rendered = mathRenderer.parse(latex: content, isBlock: true)
        let startX = contentPadding + codePadding
        let baselineY = y + codePadding + baseFont.pointSize
        let mathRuns = mathRenderer.layoutMath(rendered, at: CGPoint(x: startX, y: baselineY), fontSize: baseFont.pointSize)

        let bounds = mathRunsBounds(mathRuns)
        let availableWidth = max(0, contentWidth - contentPadding * 2 - codePadding * 2)
        let mathContentWidth = bounds.width
        let contentHeight = bounds.height
        let verticalGuard = max(6, lineHeight * 0.25)
        let height = max(lineHeight, contentHeight + codePadding * 2 + verticalGuard * 2)

        let innerLeft = contentPadding + codePadding
        let innerTop = y + codePadding + verticalGuard + (height - codePadding * 2 - verticalGuard * 2 - contentHeight) * 0.5
        let guardInset: CGFloat = max(12, codePadding * 0.9, lineHeight * 0.5)
        let minDx = innerLeft + guardInset - bounds.minX
        let maxDx = innerLeft + max(0, availableWidth - mathContentWidth) - bounds.minX - guardInset
        let isTooWide = mathContentWidth > availableWidth
        let desiredDx = isTooWide
            ? minDx
            : innerLeft + max(0, availableWidth - mathContentWidth) * 0.5 - bounds.minX
        let clampedMaxDx = max(minDx, maxDx)
        let dx = max(minDx, min(desiredDx, clampedMaxDx))
        let dy = innerTop - bounds.minY

        let runs = mathRuns.map { run in
            LayoutMathRun(
                text: run.text,
                position: CGPoint(x: run.position.x + dx, y: run.position.y + dy),
                fontSize: run.fontSize,
                color: run.color,
                isItalic: run.isItalic
            )
        }

        return LayoutBlock(
            blockId: id,
            blockType: .mathBlock,
            frame: CGRect(x: contentPadding, y: y, width: self.contentWidth - contentPadding * 2, height: height),
            content: .math(latex: content, runs: runs)
        )
    }

    private func mathRunsBounds(_ runs: [MathGlyphRun]) -> CGRect {
        guard !runs.isEmpty else { return .zero }
        var minX = CGFloat.greatestFiniteMagnitude
        var maxX = CGFloat.leastNormalMagnitude
        var minY = CGFloat.greatestFiniteMagnitude
        var maxY = CGFloat.leastNormalMagnitude

        for run in runs {
            let variant: FontVariant = run.isItalic ? .italic : .regular
            guard let base = fonts[variant] else { continue }
            let font = CTFontCreateCopyWithAttributes(base, run.fontSize, nil, nil)
            let attributes: [NSAttributedString.Key: Any] = [
                .font: font,
                .ligature: 1
            ]
            let line = CTLineCreateWithAttributedString(NSAttributedString(string: run.text, attributes: attributes))
            let bounds = CTLineGetBoundsWithOptions(line, [.useGlyphPathBounds, .useOpticalBounds])
            minX = min(minX, run.position.x + bounds.minX)
            maxX = max(maxX, run.position.x + bounds.maxX)
            minY = min(minY, run.position.y + bounds.minY)
            maxY = max(maxY, run.position.y + bounds.maxY)
        }

        if minX == CGFloat.greatestFiniteMagnitude { return .zero }
        return CGRect(x: minX, y: minY, width: max(0, maxX - minX), height: max(0, maxY - minY))
    }

    private func estimateMathHeight(runs: [MathGlyphRun], startY: CGFloat, padding: CGFloat) -> CGFloat {
        guard !runs.isEmpty else { return lineHeight + padding * 2 }
        var minY = CGFloat.greatestFiniteMagnitude
        var maxY = CGFloat.leastNormalMagnitude
        for run in runs {
            minY = min(minY, run.position.y - run.fontSize)
            maxY = max(maxY, run.position.y + run.fontSize * 0.4)
        }
        return max(lineHeight, maxY - minY + padding * 2)
    }

    private func layoutMermaidBlock(_ id: String, code: String, at y: CGFloat) -> LayoutBlock {
        let padding = CGFloat(theme.contentPadding)
        let availableWidth = max(0, contentWidth - padding * 2)
        let origin = CGPoint(x: padding, y: y)

        let diagram = mermaidParser.parse(code)
        if case .unknown = diagram {
            return layoutCodeBlock(id, code: code, language: "mermaid", at: y)
        }

        let layout = layoutMermaid(diagram, origin: origin, width: availableWidth)
        return LayoutBlock(
            blockId: id,
            blockType: .mermaid,
            frame: layout.frame,
            content: .mermaid(layout)
        )
    }

    private func layoutMermaid(_ diagram: MermaidDiagram, origin: CGPoint, width: CGFloat) -> LayoutMermaidDiagram {
        switch diagram {
        case .sequence(let sequence):
            return layoutSequenceDiagram(sequence, origin: origin, width: width)
        case .flow(let flow):
            return layoutFlowDiagram(flow, origin: origin, width: width)
        case .class(let classDiagram):
            return layoutClassDiagram(classDiagram, origin: origin, width: width)
        case .state(let stateDiagram):
            return layoutStateDiagram(stateDiagram, origin: origin, width: width)
        case .er(let erDiagram):
            return layoutERDiagram(erDiagram, origin: origin, width: width)
        case .gantt(let ganttChart):
            return layoutGanttChart(ganttChart, origin: origin, width: width)
        case .pie(let pieChart):
            return layoutPieChart(pieChart, origin: origin, width: width)
        case .git(let gitGraph):
            return layoutGitGraph(gitGraph, origin: origin, width: width)
        case .unknown:
            return LayoutMermaidDiagram(frame: CGRect(x: origin.x, y: origin.y, width: width, height: lineHeight * 2), backgrounds: [], nodes: [], lines: [], labels: [])
        }
    }

    private func layoutSequenceDiagram(_ diagram: SequenceDiagram, origin: CGPoint, width: CGFloat) -> LayoutMermaidDiagram {
        let participants = diagram.participants
        let paddingY: CGFloat = 16
        let headerBoxHeight = lineHeight * 2.1
        let messageSpacing = lineHeight * 2.4
        let minBoxWidth: CGFloat = 90
        let lineColor = theme.diagramLineColor
        let nodeFill = theme.diagramNodeBackground
        let nodeBorder = theme.diagramNodeBorder
        let textColor = theme.diagramTextColor
        let noteFill = theme.diagramNoteBackground
        let noteBorder = theme.diagramNoteBorder
        let groupFill = theme.diagramGroupBackground
        let groupBorder = theme.diagramGroupBorder

        let columnCount = max(1, participants.count)
        let columnGap = width / CGFloat(columnCount)
        let headerY = origin.y + paddingY
        let messageStartY = headerY + headerBoxHeight + paddingY

        var backgrounds: [LayoutMermaidBackground] = []
        var nodes: [LayoutMermaidNode] = []
        var lines: [LayoutMermaidLine] = []
        var labels: [LayoutTextRun] = []
        var participantCenters: [String: CGPoint] = [:]

        for (index, name) in participants.enumerated() {
            let centerX = origin.x + columnGap * (CGFloat(index) + 0.5)
            let textWidth = measureTextWidth(name, variant: .semibold)
            let boxWidth = max(minBoxWidth, textWidth + 20)
            let frame = CGRect(
                x: centerX - boxWidth * 0.5,
                y: headerY,
                width: boxWidth,
                height: headerBoxHeight
            )

            let baseline = frame.midY + (ascent - descent) * 0.5
            let glyphs = layoutTextGlyphs(name, variant: .semibold, at: CGPoint(x: frame.midX - textWidth * 0.5, y: baseline), color: textColor)
            let run = LayoutTextRun(text: name, position: CGPoint(x: frame.midX - textWidth * 0.5, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<name.count)

            nodes.append(LayoutMermaidNode(frame: frame, shape: .round, fillColor: nodeFill, borderColor: nodeBorder, labelRuns: [run]))
            participantCenters[name] = CGPoint(x: centerX, y: frame.maxY)
        }

        let totalHeight = messageStartY + CGFloat(max(1, diagram.eventCount)) * messageSpacing + paddingY

        let messagesByIndex = Dictionary(grouping: diagram.messages, by: { $0.index })
        let notesByIndex = Dictionary(grouping: diagram.notes, by: { $0.index })

        for idx in 0..<max(1, diagram.eventCount) {
            let y = messageStartY + CGFloat(idx) * messageSpacing
            if let messages = messagesByIndex[idx] {
                for message in messages {
                    guard let from = participantCenters[message.from], let to = participantCenters[message.to] else { continue }
                    let start = CGPoint(x: from.x, y: y)
                    let end = CGPoint(x: to.x, y: y)
                    let width: Float = message.isDashed ? 1 : 1.5
                    lines.append(LayoutMermaidLine(start: start, end: end, color: lineColor, width: width, isDashed: message.isDashed))

                    let arrowLines = arrowHeadLines(from: start, to: end, color: lineColor, width: width)
                    lines.append(contentsOf: arrowLines)

                    if !message.text.isEmpty {
                        let labelWidth = measureTextWidth(message.text, variant: .regular)
                        let labelX = (start.x + end.x) * 0.5 - labelWidth * 0.5
                        let baseline = y - lineHeight * 0.4
                        let glyphs = layoutTextGlyphs(message.text, variant: .regular, at: CGPoint(x: labelX, y: baseline), color: textColor)
                        let run = LayoutTextRun(text: message.text, position: CGPoint(x: labelX, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<message.text.count)
                        labels.append(run)
                    }
                }
            }

            if let notes = notesByIndex[idx] {
                for note in notes {
                    let noteY = y - lineHeight * 0.6
                    let noteWidth = min(width * 0.6, max(140, measureTextWidth(note.text, variant: .regular) + 20))
                    let noteHeight = lineHeight * 1.6
                    let noteX: CGFloat
                    switch note.anchor {
                    case .leftOf(let name):
                        noteX = (participantCenters[name]?.x ?? origin.x) - noteWidth - 16
                    case .rightOf(let name):
                        noteX = (participantCenters[name]?.x ?? origin.x) + 16
                    case .over(let names):
                        let centers = names.compactMap { participantCenters[$0]?.x }
                        let centerX = centers.isEmpty ? origin.x + width * 0.5 : (centers.min()! + centers.max()!) * 0.5
                        noteX = centerX - noteWidth * 0.5
                    }
                    let frame = CGRect(x: noteX, y: noteY, width: noteWidth, height: noteHeight)
                    let baseline = frame.midY + (ascent - descent) * 0.5
                    let textWidth = measureTextWidth(note.text, variant: .regular)
                    let glyphs = layoutTextGlyphs(note.text, variant: .regular, at: CGPoint(x: frame.midX - textWidth * 0.5, y: baseline), color: textColor)
                    let run = LayoutTextRun(text: note.text, position: CGPoint(x: frame.midX - textWidth * 0.5, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<note.text.count)
                    nodes.append(LayoutMermaidNode(frame: frame, shape: .rect, fillColor: noteFill, borderColor: noteBorder, labelRuns: [run]))
                }
            }
        }

        // Lifelines
        for (_, center) in participantCenters {
            let start = CGPoint(x: center.x, y: center.y)
            let end = CGPoint(x: center.x, y: totalHeight - paddingY)
            lines.append(LayoutMermaidLine(start: start, end: end, color: lineColor, width: 1))
        }

        // Activation bars
        let activationsByParticipant = Dictionary(grouping: diagram.activations, by: { $0.participant })
        for (name, entries) in activationsByParticipant {
            guard let center = participantCenters[name] else { continue }
            var stack: [Int] = []
            let sorted = entries.sorted { $0.index < $1.index }
            for entry in sorted {
                if entry.isActivate {
                    stack.append(entry.index)
                } else if let startIdx = stack.popLast() {
                    let startY = messageStartY + CGFloat(startIdx) * messageSpacing
                    let endY = messageStartY + CGFloat(entry.index) * messageSpacing
                    let frame = CGRect(x: center.x - 6, y: startY, width: 12, height: max(12, endY - startY))
                    backgrounds.append(LayoutMermaidBackground(frame: frame, cornerRadius: 3, fillColor: theme.diagramActivationColor, borderColor: theme.diagramActivationBorder))
                }
            }
        }

        // Group boxes
        for group in diagram.groups {
            let startY = messageStartY + CGFloat(group.startIndex) * messageSpacing - messageSpacing * 0.7
            let endY = messageStartY + CGFloat(group.endIndex) * messageSpacing + messageSpacing * 0.7
            let frame = CGRect(x: origin.x + 8, y: startY, width: width - 16, height: max(28, endY - startY))
            backgrounds.append(LayoutMermaidBackground(frame: frame, cornerRadius: 6, fillColor: groupFill, borderColor: groupBorder))
            if !group.text.isEmpty {
                let baseline = frame.minY + lineHeight * 1.0
                let glyphs = layoutTextGlyphs(group.text, variant: .semibold, at: CGPoint(x: frame.minX + 8, y: baseline), color: textColor)
                let run = LayoutTextRun(text: group.text, position: CGPoint(x: frame.minX + 8, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<group.text.count)
                labels.append(run)
            }
        }

        let frame = CGRect(x: origin.x, y: origin.y, width: width, height: totalHeight - origin.y)
        return LayoutMermaidDiagram(frame: frame, backgrounds: backgrounds, nodes: nodes, lines: lines, labels: labels)
    }

    private func layoutFlowDiagram(
        _ diagram: FlowDiagram,
        origin: CGPoint,
        width: CGFloat,
        spacingScale: CGFloat = 1.0,
        labelOffset: CGFloat? = nil,
        nodeHeightScale: CGFloat = 1.0
    ) -> LayoutMermaidDiagram {
        let paddingY: CGFloat = 16
        let rowGap = max(120, lineHeight * 3.6) * spacingScale
        let columnGap = max(220, width * 0.42) * spacingScale
        let nodePadding: CGFloat = 16
        let nodeHeight = lineHeight * 2.1 * nodeHeightScale
        let lineColor = theme.diagramLineColor
        let nodeFill = theme.diagramNodeBackground
        let nodeBorder = theme.diagramNodeBorder
        let textColor = theme.diagramTextColor
        let effectiveLabelOffset = labelOffset ?? (lineHeight * 0.6 * spacingScale)

        let levels = computeFlowLevels(nodes: diagram.nodes, edges: diagram.edges)
        let isHorizontal = diagram.direction == .leftRight || diagram.direction == .rightLeft

        var nodeFrames: [String: CGRect] = [:]
        var nodes: [LayoutMermaidNode] = []
        var labels: [LayoutTextRun] = []

        for (levelIndex, levelNodes) in levels.enumerated() {
            let count = max(1, levelNodes.count)
            let spacing = isHorizontal ? rowGap : (width / CGFloat(count + 1))
            for (idx, nodeId) in levelNodes.enumerated() {
                guard let node = diagram.nodes[nodeId] else { continue }
                let textWidth = measureTextWidth(node.label, variant: .regular)
                var boxWidth = max(90, textWidth + nodePadding * 2)

                let x: CGFloat
                let y: CGFloat
                if isHorizontal {
                    let columnX = origin.x + columnGap * CGFloat(levelIndex + 1)
                    let offset = (CGFloat(idx) + 1) * spacing
                    y = origin.y + paddingY + offset
                    x = diagram.direction == .rightLeft
                        ? origin.x + width - columnGap * CGFloat(levelIndex + 1)
                        : columnX
                } else {
                    x = origin.x + (CGFloat(idx) + 1) * spacing
                    y = origin.y + paddingY + CGFloat(levelIndex) * rowGap
                }

                if node.shape == .circle {
                    boxWidth = nodeHeight
                }

                let frame = CGRect(
                    x: x - boxWidth * 0.5,
                    y: y,
                    width: boxWidth,
                    height: nodeHeight
                )
                let baseline = frame.midY + (ascent - descent) * 0.5
                let glyphs = layoutTextGlyphs(node.label, variant: .regular, at: CGPoint(x: frame.midX - textWidth * 0.5, y: baseline), color: textColor)
                let run = LayoutTextRun(text: node.label, position: CGPoint(x: frame.midX - textWidth * 0.5, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<node.label.count)

                let shape: LayoutMermaidNodeShape = node.shape == .round ? .round : (node.shape == .circle ? .circle : .rect)
                nodes.append(LayoutMermaidNode(frame: frame, shape: shape, fillColor: nodeFill, borderColor: nodeBorder, labelRuns: [run]))
                nodeFrames[node.id] = frame
            }
        }

        var lines: [LayoutMermaidLine] = []
        let trimPadding = max(12, nodeHeight * 0.6)
        for edge in diagram.edges {
            guard let fromFrame = nodeFrames[edge.from], let toFrame = nodeFrames[edge.to] else { continue }
            let start = intersectEdge(from: fromFrame, to: toFrame.center)
            let end = intersectEdge(from: toFrame, to: fromFrame.center)
            let trimmed = trimMermaidLine(start: start, end: end, padding: trimPadding)
            let width: Float = edge.isDashed ? 1 : 1.5
            lines.append(LayoutMermaidLine(start: trimmed.start, end: trimmed.end, color: lineColor, width: width, isDashed: edge.isDashed))
            lines.append(contentsOf: arrowHeadLines(from: trimmed.start, to: trimmed.end, color: lineColor, width: width))

            if let label = edge.label, !label.isEmpty {
                let labelWidth = measureTextWidth(label, variant: .regular)
                let anchor = edgeLabelAnchor(start: trimmed.start, end: trimmed.end, offset: effectiveLabelOffset)
                let baseline = CGPoint(x: anchor.x - labelWidth * 0.5, y: anchor.y)
                let glyphs = layoutTextGlyphs(label, variant: .regular, at: baseline, color: textColor)
                let run = LayoutTextRun(text: label, position: baseline, glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<label.count)
                labels.append(run)
            }
        }

        let maxY = nodes.map { $0.frame.maxY }.max() ?? origin.y + lineHeight * 2
        let frame = CGRect(x: origin.x, y: origin.y, width: width, height: maxY - origin.y + paddingY)
        return LayoutMermaidDiagram(frame: frame, backgrounds: [], nodes: nodes, lines: lines, labels: labels)
    }

    private func layoutClassDiagram(_ diagram: ClassDiagram, origin: CGPoint, width: CGFloat) -> LayoutMermaidDiagram {
        let paddingY: CGFloat = 20
        let rowGap = max(140, lineHeight * 4.2)
        let nodePadding: CGFloat = 14
        let nodeFill = theme.diagramNodeBackground
        let nodeBorder = theme.diagramNodeBorder
        let textColor = theme.diagramTextColor
        let lineColor = theme.diagramLineColor

        let levels = computeFlowLevels(nodes: diagram.classes.mapValues { FlowNode(id: $0.id, label: $0.title, shape: .rect) }, edges: diagram.edges.map { FlowEdge(from: $0.from, to: $0.to, label: $0.label, isDashed: $0.kind == .dependency) })

        var nodeFrames: [String: CGRect] = [:]
        var nodes: [LayoutMermaidNode] = []
        var labels: [LayoutTextRun] = []

        for (levelIndex, levelNodes) in levels.enumerated() {
            let count = max(1, levelNodes.count)
            let spacing = width / CGFloat(count + 1)
            for (idx, nodeId) in levelNodes.enumerated() {
                guard let node = diagram.classes[nodeId] else { continue }
                let lines = [node.title] + node.members
                let maxTextWidth = lines.map { measureTextWidth($0, variant: .regular) }.max() ?? 0
                let boxWidth = max(140, maxTextWidth + nodePadding * 2)
                let boxHeight = CGFloat(lines.count) * lineHeight * 1.05 + nodePadding * 2

                let x = origin.x + CGFloat(idx + 1) * spacing
                let y = origin.y + paddingY + CGFloat(levelIndex) * rowGap
                let frame = CGRect(x: x - boxWidth * 0.5, y: y, width: boxWidth, height: boxHeight)

                var runs: [LayoutTextRun] = []
                for (lineIdx, text) in lines.enumerated() {
                    let textWidth = measureTextWidth(text, variant: lineIdx == 0 ? .semibold : .regular)
                    let baseline = frame.minY + nodePadding + CGFloat(lineIdx) * lineHeight * 1.05 + lineHeight * 0.8
                    let glyphs = layoutTextGlyphs(text, variant: lineIdx == 0 ? .semibold : .regular, at: CGPoint(x: frame.midX - textWidth * 0.5, y: baseline), color: textColor)
                    let run = LayoutTextRun(text: text, position: CGPoint(x: frame.midX - textWidth * 0.5, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<text.count)
                    runs.append(run)
                }

                nodes.append(LayoutMermaidNode(frame: frame, shape: .rect, fillColor: nodeFill, borderColor: nodeBorder, labelRuns: runs))
                nodeFrames[node.id] = frame
            }
        }

        var lines: [LayoutMermaidLine] = []
        for edge in diagram.edges {
            guard let fromFrame = nodeFrames[edge.from], let toFrame = nodeFrames[edge.to] else { continue }
            let start = intersectEdge(from: fromFrame, to: toFrame.center)
            let end = intersectEdge(from: toFrame, to: fromFrame.center)
            let trimmed = trimMermaidLine(start: start, end: end, padding: max(4, lineHeight * 0.3))
            let width: Float = edge.kind == .dependency ? 1 : 1.5
            let dashed = edge.kind == .dependency
            lines.append(LayoutMermaidLine(start: trimmed.start, end: trimmed.end, color: lineColor, width: width, isDashed: dashed))
            lines.append(contentsOf: arrowHeadLines(from: trimmed.start, to: trimmed.end, color: lineColor, width: width))

            if let label = edge.label, !label.isEmpty {
                let labelWidth = measureTextWidth(label, variant: .regular)
                let anchor = edgeLabelAnchor(start: trimmed.start, end: trimmed.end, offset: lineHeight * 0.35)
                let baseline = CGPoint(x: anchor.x - labelWidth * 0.5, y: anchor.y)
                let glyphs = layoutTextGlyphs(label, variant: .regular, at: baseline, color: textColor)
                let run = LayoutTextRun(text: label, position: baseline, glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<label.count)
                labels.append(run)
            }
        }

        let maxY = nodes.map { $0.frame.maxY }.max() ?? origin.y + lineHeight * 2
        let frame = CGRect(x: origin.x, y: origin.y, width: width, height: maxY - origin.y + paddingY)
        return LayoutMermaidDiagram(frame: frame, backgrounds: [], nodes: nodes, lines: lines, labels: labels)
    }

    private func layoutStateDiagram(_ diagram: StateDiagram, origin: CGPoint, width: CGFloat) -> LayoutMermaidDiagram {
        var flowNodes: [String: FlowNode] = [:]
        var flowEdges: [FlowEdge] = []

        for (id, state) in diagram.states {
            let shape: FlowNodeShape = state.isStart ? .circle : .round
            flowNodes[id] = FlowNode(id: id, label: state.isStart ? "" : state.label, shape: shape)
        }

        for edge in diagram.edges {
            flowEdges.append(FlowEdge(from: edge.from, to: edge.to, label: edge.label, isDashed: false))
        }

        let flow = FlowDiagram(nodes: flowNodes, edges: flowEdges, direction: .topDown)
        return layoutFlowDiagram(flow, origin: origin, width: width, spacingScale: 6.0, labelOffset: lineHeight * 7.5, nodeHeightScale: 2.3)
    }

    private func layoutERDiagram(_ diagram: ERDiagram, origin: CGPoint, width: CGFloat) -> LayoutMermaidDiagram {
        let paddingY: CGFloat = 16
        let rowGap = max(420, lineHeight * 12.0)
        let nodePadding: CGFloat = 16
        let nodeFill = theme.diagramNodeBackground
        let nodeBorder = theme.diagramNodeBorder
        let textColor = theme.diagramTextColor
        let lineColor = theme.diagramLineColor

        let flowNodes = diagram.entities.mapValues { FlowNode(id: $0.id, label: $0.id, shape: .rect) }
        let flowEdges = diagram.relations.map { FlowEdge(from: $0.from, to: $0.to, label: $0.label, isDashed: false) }
        let levels = computeFlowLevels(nodes: flowNodes, edges: flowEdges)

        var nodeFrames: [String: CGRect] = [:]
        var nodes: [LayoutMermaidNode] = []
        var labels: [LayoutTextRun] = []

        for (levelIndex, levelNodes) in levels.enumerated() {
            let count = max(1, levelNodes.count)
            let levelWidths: [CGFloat] = levelNodes.compactMap { nodeId in
                guard let entity = diagram.entities[nodeId] else { return nil }
                let lines = [entity.id] + entity.attributes
                let maxTextWidth = lines.map { measureTextWidth($0, variant: .regular) }.max() ?? 0
                return max(140, maxTextWidth + nodePadding * 2)
            }
            let maxLevelWidth = levelWidths.max() ?? 0
            let spacing = max(width / CGFloat(count + 1), maxLevelWidth + nodePadding * 2 + lineHeight * 3.2)
            for (idx, nodeId) in levelNodes.enumerated() {
                guard let entity = diagram.entities[nodeId] else { continue }
                let lines = [entity.id] + entity.attributes
                let maxTextWidth = lines.map { measureTextWidth($0, variant: .regular) }.max() ?? 0
                let boxWidth = max(140, maxTextWidth + nodePadding * 2)
                let boxHeight = CGFloat(lines.count) * lineHeight * 1.05 + nodePadding * 2

                let x = origin.x + CGFloat(idx + 1) * spacing
                let y = origin.y + paddingY + CGFloat(levelIndex) * rowGap
                let frame = CGRect(x: x - boxWidth * 0.5, y: y, width: boxWidth, height: boxHeight)

                var runs: [LayoutTextRun] = []
                for (lineIdx, text) in lines.enumerated() {
                    let textWidth = measureTextWidth(text, variant: lineIdx == 0 ? .semibold : .regular)
                    let baseline = frame.minY + nodePadding + CGFloat(lineIdx) * lineHeight * 1.05 + lineHeight * 0.8
                    let glyphs = layoutTextGlyphs(text, variant: lineIdx == 0 ? .semibold : .regular, at: CGPoint(x: frame.midX - textWidth * 0.5, y: baseline), color: textColor)
                    let run = LayoutTextRun(text: text, position: CGPoint(x: frame.midX - textWidth * 0.5, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<text.count)
                    runs.append(run)
                }

                nodes.append(LayoutMermaidNode(frame: frame, shape: .rect, fillColor: nodeFill, borderColor: nodeBorder, labelRuns: runs))
                nodeFrames[entity.id] = frame
            }
        }

        var lines: [LayoutMermaidLine] = []
        let edgeTrimPadding = max(48, lineHeight * 4.2)
        for relation in diagram.relations {
            guard let fromFrame = nodeFrames[relation.from], let toFrame = nodeFrames[relation.to] else { continue }
            let start = intersectEdge(from: fromFrame, to: toFrame.center)
            let end = intersectEdge(from: toFrame, to: fromFrame.center)
            let trimmed = trimMermaidLine(start: start, end: end, padding: edgeTrimPadding)
            lines.append(LayoutMermaidLine(start: trimmed.start, end: trimmed.end, color: lineColor, width: 1.5, isDashed: false))
            lines.append(contentsOf: arrowHeadLines(from: trimmed.start, to: trimmed.end, color: lineColor, width: 1.5))

            if let label = relation.label, !label.isEmpty {
                let labelWidth = measureTextWidth(label, variant: .regular)
                let anchor = edgeLabelAnchor(start: trimmed.start, end: trimmed.end, offset: lineHeight * 6.4)
                let baseline = CGPoint(x: anchor.x - labelWidth * 0.5, y: anchor.y)
                let glyphs = layoutTextGlyphs(label, variant: .regular, at: baseline, color: textColor)
                let run = LayoutTextRun(text: label, position: baseline, glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<label.count)
                labels.append(run)
            }
        }

        let maxY = nodes.map { $0.frame.maxY }.max() ?? origin.y + lineHeight * 2
        let frame = CGRect(x: origin.x, y: origin.y, width: width, height: maxY - origin.y + paddingY)
        return LayoutMermaidDiagram(frame: frame, backgrounds: [], nodes: nodes, lines: lines, labels: labels)
    }

    private func layoutGanttChart(_ chart: GanttChart, origin: CGPoint, width: CGFloat) -> LayoutMermaidDiagram {
        let padding: CGFloat = 12
        let rowHeight = lineHeight * 1.2
        let sectionGap = lineHeight * 0.8
        let labelWidth: CGFloat = 160
        let barHeight: CGFloat = rowHeight * 0.7
        let textColor = theme.diagramTextColor
        let palette = diagramPalette()

        var backgrounds: [LayoutMermaidBackground] = []
        var labels: [LayoutTextRun] = []

        let allTasks = chart.sections.flatMap { $0.tasks }
        let minStart = allTasks.map { $0.start }.min() ?? 0
        let maxEnd = allTasks.map { $0.end }.max() ?? (minStart + 1)
        let span = max(1.0, maxEnd - minStart)
        let barAreaWidth = max(80, width - labelWidth - padding * 2)

        var currentY = origin.y + padding
        for (sectionIndex, section) in chart.sections.enumerated() {
            if !section.title.isEmpty {
                let baseline = currentY + lineHeight * 0.8
                let glyphs = layoutTextGlyphs(section.title, variant: .semibold, at: CGPoint(x: origin.x + padding, y: baseline), color: textColor)
                let run = LayoutTextRun(text: section.title, position: CGPoint(x: origin.x + padding, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<section.title.count)
                labels.append(run)
                currentY += rowHeight
            }

            for (taskIndex, task) in section.tasks.enumerated() {
                let barX = origin.x + padding + labelWidth
                let startRatio = (task.start - minStart) / span
                let endRatio = (task.end - minStart) / span
                let barWidth = max(4, barAreaWidth * CGFloat(endRatio - startRatio))
                let barFrame = CGRect(
                    x: barX + barAreaWidth * CGFloat(startRatio),
                    y: currentY + (rowHeight - barHeight) * 0.5,
                    width: barWidth,
                    height: barHeight
                )
                let color = palette[(sectionIndex + taskIndex) % palette.count]
                backgrounds.append(LayoutMermaidBackground(frame: barFrame, cornerRadius: 4, fillColor: color, borderColor: nil))

                let baseline = currentY + lineHeight * 0.8
                let glyphs = layoutTextGlyphs(task.title, variant: .regular, at: CGPoint(x: origin.x + padding, y: baseline), color: textColor)
                let run = LayoutTextRun(text: task.title, position: CGPoint(x: origin.x + padding, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<task.title.count)
                labels.append(run)
                currentY += rowHeight
            }

            currentY += sectionGap
        }

        let frame = CGRect(x: origin.x, y: origin.y, width: width, height: max(currentY - origin.y, rowHeight * 2))
        return LayoutMermaidDiagram(frame: frame, backgrounds: backgrounds, nodes: [], lines: [], labels: labels)
    }

    private func layoutPieChart(_ chart: PieChart, origin: CGPoint, width: CGFloat) -> LayoutMermaidDiagram {
        let padding: CGFloat = 16
        let legendRowHeight: CGFloat = lineHeight * 1.4
        let legendGap: CGFloat = lineHeight * 0.6
        let palette = diagramPalette()
        let textColor = theme.diagramTextColor

        var backgrounds: [LayoutMermaidBackground] = []
        var pieSlices: [LayoutMermaidPieSlice] = []
        var labels: [LayoutTextRun] = []
        let total = chart.slices.map { $0.value }.reduce(0, +)
        let diameter = max(lineHeight * 6.5, min(width - padding * 2, lineHeight * 11))
        let radius = diameter * 0.5

        var currentY = origin.y + padding
        if let title = chart.title, !title.isEmpty {
            let baseline = currentY + lineHeight * 0.8
            let glyphs = layoutTextGlyphs(title, variant: .semibold, at: CGPoint(x: origin.x + padding, y: baseline), color: textColor)
            let run = LayoutTextRun(text: title, position: CGPoint(x: origin.x + padding, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<title.count)
            labels.append(run)
            currentY += legendRowHeight + lineHeight * 0.2
        }

        let centerX = origin.x + width * 0.5
        let centerY = currentY + radius
        var startAngle: CGFloat = -.pi / 2
        for (index, slice) in chart.slices.enumerated() {
            let ratio = total > 0 ? slice.value / total : 0
            let angle = CGFloat(ratio) * (.pi * 2)
            let endAngle = startAngle + angle
            let color = palette[index % palette.count]
            if angle > 0.0001 {
                let twoPi: CGFloat = .pi * 2
                var normalizedStart = startAngle.truncatingRemainder(dividingBy: twoPi)
                var normalizedEnd = endAngle.truncatingRemainder(dividingBy: twoPi)
                if normalizedStart < 0 { normalizedStart += twoPi }
                if normalizedEnd < 0 { normalizedEnd += twoPi }
                if normalizedEnd <= normalizedStart {
                    normalizedEnd += twoPi
                }
                pieSlices.append(LayoutMermaidPieSlice(center: CGPoint(x: centerX, y: centerY), radius: radius, startAngle: normalizedStart, endAngle: normalizedEnd, color: color))
            }
            startAngle = endAngle
        }

        currentY = centerY + radius + legendGap
        for (index, slice) in chart.slices.enumerated() {
            let color = palette[index % palette.count]
            let swatch = CGRect(x: origin.x + padding, y: currentY + (legendRowHeight - 10) * 0.5, width: 10, height: 10)
            backgrounds.append(LayoutMermaidBackground(frame: swatch, cornerRadius: 2, fillColor: color, borderColor: nil))
            let label = "\(slice.label) \(slice.value)"
            let baseline = currentY + lineHeight * 0.8
            let glyphs = layoutTextGlyphs(label, variant: .regular, at: CGPoint(x: swatch.maxX + 8, y: baseline), color: textColor)
            let run = LayoutTextRun(text: label, position: CGPoint(x: swatch.maxX + 8, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<label.count)
            labels.append(run)
            currentY += legendRowHeight
        }

        let frameHeight = max(currentY - origin.y + padding, diameter + padding * 2)
        let frame = CGRect(x: origin.x, y: origin.y, width: width, height: frameHeight)
        return LayoutMermaidDiagram(frame: frame, backgrounds: backgrounds, nodes: [], lines: [], labels: labels, pieSlices: pieSlices)
    }

    private func layoutGitGraph(_ graph: GitGraph, origin: CGPoint, width: CGFloat) -> LayoutMermaidDiagram {
        let padding: CGFloat = 12
        let rowGap = lineHeight * 2.8
        let columnCount = max(1, graph.branches.count)
        let columnGap = max(80, (width - padding * 2) / CGFloat(max(1, columnCount - 1)))
        let lineColor = theme.diagramLineColor
        let nodeFill = theme.diagramNodeBackground
        let nodeBorder = theme.diagramNodeBorder
        let textColor = theme.diagramTextColor

        var nodes: [LayoutMermaidNode] = []
        var labels: [LayoutTextRun] = []
        var lines: [LayoutMermaidLine] = []
        var lastPosition: [String: CGPoint] = [:]
        var commitPositions: [Int: CGPoint] = [:]
        var branchFirstCommit: [String: CGPoint] = [:]

        for branch in graph.branches {
            let index = graph.branches.firstIndex(of: branch) ?? 0
            let x = origin.x + padding + CGFloat(index) * columnGap
            let baseline = origin.y + padding + lineHeight * 0.8
            let textWidth = measureTextWidth(branch, variant: .semibold)
            let originX = x - textWidth * 0.5
            let glyphs = layoutTextGlyphs(branch, variant: .semibold, at: CGPoint(x: originX, y: baseline), color: textColor)
            let run = LayoutTextRun(text: branch, position: CGPoint(x: originX, y: baseline), glyphs: glyphs, style: TextRunStyle(color: textColor), characterRange: 0..<branch.count)
            labels.append(run)
        }

        for commit in graph.commits {
            let branchIndex = graph.branches.firstIndex(of: commit.branch) ?? 0
            let x = origin.x + padding + CGFloat(branchIndex) * columnGap
            let y = origin.y + padding + lineHeight * 1.6 + CGFloat(commit.index) * rowGap
            let position = CGPoint(x: x, y: y)
            let frame = CGRect(x: x - 6, y: y - 6, width: 12, height: 12)
            nodes.append(LayoutMermaidNode(frame: frame, shape: .circle, fillColor: nodeFill, borderColor: nodeBorder, labelRuns: []))

            if let last = lastPosition[commit.branch] {
                lines.append(LayoutMermaidLine(start: last, end: position, color: lineColor, width: 1.5, isDashed: false))
            }
            lastPosition[commit.branch] = position
            commitPositions[commit.index] = position
            if branchFirstCommit[commit.branch] == nil {
                branchFirstCommit[commit.branch] = position
            }

            if let mergeFrom = commit.mergeFrom, let fromPos = lastPosition[mergeFrom] {
                lines.append(LayoutMermaidLine(start: fromPos, end: position, color: lineColor, width: 1, isDashed: true))
            }
        }

        for (branch, originIndex) in graph.branchOrigins {
            guard originIndex >= 0, branchFirstCommit[branch] == nil,
                  let originPos = commitPositions[originIndex] else { continue }
            let branchIndex = graph.branches.firstIndex(of: branch) ?? 0
            let branchX = origin.x + padding + CGFloat(branchIndex) * columnGap
            let ghostPos = CGPoint(x: branchX, y: originPos.y + rowGap * 0.6)
            let frame = CGRect(x: ghostPos.x - 5, y: ghostPos.y - 5, width: 10, height: 10)
            nodes.append(LayoutMermaidNode(frame: frame, shape: .circle, fillColor: nodeFill, borderColor: nodeBorder, labelRuns: []))
            lines.append(LayoutMermaidLine(start: originPos, end: ghostPos, color: lineColor, width: 1, isDashed: true))
            branchFirstCommit[branch] = ghostPos
            lastPosition[branch] = ghostPos
        }

        // Ensure branches without commits still render a starting node.
        for branch in graph.branches {
            guard branchFirstCommit[branch] == nil else { continue }
            let branchIndex = graph.branches.firstIndex(of: branch) ?? 0
            let branchX = origin.x + padding + CGFloat(branchIndex) * columnGap
            let ghostPos = CGPoint(x: branchX, y: origin.y + padding + lineHeight * 1.6 + rowGap * 0.4)
            let frame = CGRect(x: ghostPos.x - 5, y: ghostPos.y - 5, width: 10, height: 10)
            nodes.append(LayoutMermaidNode(frame: frame, shape: .circle, fillColor: nodeFill, borderColor: nodeBorder, labelRuns: []))
            branchFirstCommit[branch] = ghostPos
            lastPosition[branch] = ghostPos
        }

        for (branch, originIndex) in graph.branchOrigins {
            guard originIndex >= 0,
                  let originPos = commitPositions[originIndex],
                  let firstPos = branchFirstCommit[branch],
                  originPos != firstPos else { continue }
            lines.append(LayoutMermaidLine(start: originPos, end: firstPos, color: lineColor, width: 1, isDashed: true))
        }

        let maxY = (graph.commits.last?.index ?? 0) > 0
            ? origin.y + padding + lineHeight * 1.6 + CGFloat(graph.commits.count) * rowGap
            : origin.y + padding + lineHeight * 2
        let frame = CGRect(x: origin.x, y: origin.y, width: width, height: maxY - origin.y + padding)
        return LayoutMermaidDiagram(frame: frame, backgrounds: [], nodes: nodes, lines: lines, labels: labels)
    }

    private func diagramPalette() -> [SIMD4<Float>] {
        return [
            SIMD4(0.36, 0.64, 0.96, 1.0),
            SIMD4(0.42, 0.78, 0.47, 1.0),
            SIMD4(0.94, 0.55, 0.32, 1.0),
            SIMD4(0.74, 0.56, 0.95, 1.0),
            SIMD4(0.91, 0.75, 0.35, 1.0),
            SIMD4(0.5, 0.82, 0.82, 1.0)
        ]
    }

    private func computeFlowLevels(nodes: [String: FlowNode], edges: [FlowEdge]) -> [[String]] {
        var incoming: [String: Int] = [:]
        var outgoing: [String: [String]] = [:]

        for (id, _) in nodes {
            incoming[id] = 0
        }
        for edge in edges {
            incoming[edge.to, default: 0] += 1
            outgoing[edge.from, default: []].append(edge.to)
        }

        var queue: [String] = incoming.filter { $0.value == 0 }.map { $0.key }
        if queue.isEmpty {
            queue = Array(nodes.keys)
        }

        var level: [String: Int] = [:]
        while !queue.isEmpty {
            let node = queue.removeFirst()
            let currentLevel = level[node] ?? 0
            for next in outgoing[node, default: []] {
                incoming[next, default: 0] -= 1
                level[next] = max(level[next] ?? 0, currentLevel + 1)
                if incoming[next] == 0 {
                    queue.append(next)
                }
            }
        }

        for id in nodes.keys where level[id] == nil {
            level[id] = 0
        }

        let maxLevel = level.values.max() ?? 0
        var levels: [[String]] = Array(repeating: [], count: maxLevel + 1)
        for (id, lvl) in level {
            if lvl >= levels.count { continue }
            levels[lvl].append(id)
        }
        return levels
    }

    private func arrowHeadLines(from start: CGPoint, to end: CGPoint, color: SIMD4<Float>, width: Float) -> [LayoutMermaidLine] {
        let dx = end.x - start.x
        let dy = end.y - start.y
        let length = max(1, hypot(dx, dy))
        let ux = dx / length
        let uy = dy / length
        let size: CGFloat = 8
        let angle: CGFloat = .pi / 6

        let leftX = end.x - size * (ux * cos(angle) - uy * sin(angle))
        let leftY = end.y - size * (uy * cos(angle) + ux * sin(angle))
        let rightX = end.x - size * (ux * cos(-angle) - uy * sin(-angle))
        let rightY = end.y - size * (uy * cos(-angle) + ux * sin(-angle))

        return [
            LayoutMermaidLine(start: CGPoint(x: leftX, y: leftY), end: end, color: color, width: width),
            LayoutMermaidLine(start: CGPoint(x: rightX, y: rightY), end: end, color: color, width: width)
        ]
    }

    private func intersectEdge(from rect: CGRect, to target: CGPoint) -> CGPoint {
        let center = rect.center
        let dx = target.x - center.x
        let dy = target.y - center.y
        let absDx = abs(dx)
        let absDy = abs(dy)
        let inset: CGFloat = max(6, lineHeight * 0.35)
        let length = max(1, hypot(dx, dy))
        let ux = dx / length
        let uy = dy / length
        if absDx > absDy {
            let sign: CGFloat = dx >= 0 ? 1 : -1
            let x = center.x + rect.width * 0.5 * sign
            let y = center.y + dy * (rect.width * 0.5 / max(1, absDx))
            return CGPoint(x: x + ux * inset, y: y + uy * inset)
        } else {
            let sign: CGFloat = dy >= 0 ? 1 : -1
            let y = center.y + rect.height * 0.5 * sign
            let x = center.x + dx * (rect.height * 0.5 / max(1, absDy))
            return CGPoint(x: x + ux * inset, y: y + uy * inset)
        }
    }

    private func trimMermaidLine(start: CGPoint, end: CGPoint, padding: CGFloat) -> (start: CGPoint, end: CGPoint) {
        let dx = end.x - start.x
        let dy = end.y - start.y
        let length = hypot(dx, dy)
        guard length > padding * 2 else { return (start, end) }
        let ux = dx / length
        let uy = dy / length
        let trimmedStart = CGPoint(x: start.x + ux * padding, y: start.y + uy * padding)
        let trimmedEnd = CGPoint(x: end.x - ux * padding, y: end.y - uy * padding)
        return (trimmedStart, trimmedEnd)
    }

    private func edgeLabelAnchor(start: CGPoint, end: CGPoint, offset: CGFloat) -> CGPoint {
        let midX = (start.x + end.x) * 0.5
        let midY = (start.y + end.y) * 0.5
        let dx = end.x - start.x
        let dy = end.y - start.y
        let length = max(1, hypot(dx, dy))
        let nx = -dy / length
        let ny = dx / length
        let sign: CGFloat
        if abs(dx) < 1 {
            sign = dy >= 0 ? 1 : -1
        } else if abs(dy) < 1 {
            sign = dx >= 0 ? 1 : -1
        } else {
            sign = dx * dy >= 0 ? 1 : -1
        }
        let offsetX = nx * offset * sign
        let offsetY = ny * offset * sign
        let baseline = midY + offsetY + (ascent - descent) * 0.5
        return CGPoint(x: midX + offsetX, y: baseline)
    }

    // MARK: - Inline Layout
    private typealias InlineLayoutResult = (
        runs: [LayoutTextRun],
        images: [LayoutInlineImage],
        endX: CGFloat,
        endY: CGFloat,
        endCharIndex: Int
    )

    private func layoutInlineContent(
        _ content: MarkdownInlineContent,
        baseStyle: TextRunStyle,
        startX: CGFloat,
        startY: CGFloat,
        maxX: CGFloat
    ) -> (runs: [LayoutTextRun], images: [LayoutInlineImage]) {
        let result = layoutInlineContentWithState(
            content,
            baseStyle: baseStyle,
            startX: startX,
            startY: startY,
            maxX: maxX,
            lineStartX: startX,
            startCharIndex: 0
        )
        return (result.runs, result.images)
    }

    private func layoutInlineContentWithState(
        _ content: MarkdownInlineContent,
        baseStyle: TextRunStyle,
        startX: CGFloat,
        startY: CGFloat,
        maxX: CGFloat,
        lineStartX: CGFloat,
        startCharIndex: Int
    ) -> InlineLayoutResult {
        var runs: [LayoutTextRun] = []
        var images: [LayoutInlineImage] = []
        var currentX = startX
        var currentY = startY
        var charIndex = startCharIndex

        for element in content.elements {
            let result = layoutInlineElement(
                element,
                baseStyle: baseStyle,
                startX: currentX,
                startY: currentY,
                maxX: maxX,
                lineStartX: lineStartX,
                startCharIndex: charIndex
            )
            runs.append(contentsOf: result.runs)
            images.append(contentsOf: result.images)
            currentX = result.endX
            currentY = result.endY
            charIndex = result.endCharIndex
        }

        return (runs, images, currentX, currentY, charIndex)
    }

    private func layoutInlineElement(
        _ element: InlineElement,
        baseStyle: TextRunStyle,
        startX: CGFloat,
        startY: CGFloat,
        maxX: CGFloat,
        lineStartX: CGFloat,
        startCharIndex: Int
    ) -> InlineLayoutResult {
        switch element {
        case .text(let text):
            return layoutText(text, style: baseStyle, startX: startX, startY: startY, maxX: maxX, lineStartX: lineStartX, startCharIndex: startCharIndex)

        case .strong(let content):
            var style = baseStyle
            style.isBold = true
            return layoutInlineContentWithState(
                content,
                baseStyle: style,
                startX: startX,
                startY: startY,
                maxX: maxX,
                lineStartX: lineStartX,
                startCharIndex: startCharIndex
            )

        case .emphasis(let content):
            var style = baseStyle
            style.isItalic = true
            return layoutInlineContentWithState(
                content,
                baseStyle: style,
                startX: startX,
                startY: startY,
                maxX: maxX,
                lineStartX: lineStartX,
                startCharIndex: startCharIndex
            )

        case .strikethrough(let content):
            var style = baseStyle
            style.isStrikethrough = true
            style.color = theme.strikethroughColor
            return layoutInlineContentWithState(
                content,
                baseStyle: style,
                startX: startX,
                startY: startY,
                maxX: maxX,
                lineStartX: lineStartX,
                startCharIndex: startCharIndex
            )

        case .code(let code):
            var style = baseStyle
            style.isCode = true
            style.color = theme.codeColor
            return layoutText(code, style: style, startX: startX, startY: startY, maxX: maxX, lineStartX: lineStartX, startCharIndex: startCharIndex)

        case .link(let content, let url, _):
            var style = baseStyle
            style.isLink = true
            style.linkURL = url
            style.color = theme.linkColor
            return layoutInlineContentWithState(
                content,
                baseStyle: style,
                startX: startX,
                startY: startY,
                maxX: maxX,
                lineStartX: lineStartX,
                startCharIndex: startCharIndex
            )

        case .math(let math):
            return layoutInlineMath(math, style: baseStyle, startX: startX, startY: startY, maxX: maxX, lineStartX: lineStartX, startCharIndex: startCharIndex)

        case .image(let url, _, _):
            return layoutInlineImage(url, style: baseStyle, startX: startX, startY: startY, maxX: maxX, lineStartX: lineStartX, startCharIndex: startCharIndex)

        case .softBreak:
            return layoutText(" ", style: baseStyle, startX: startX, startY: startY, maxX: maxX, lineStartX: lineStartX, startCharIndex: startCharIndex)

        case .hardBreak:
            return ([], [], lineStartX, startY + lineHeight, startCharIndex + 1)

        case .html(let html):
            return layoutText(html, style: baseStyle, startX: startX, startY: startY, maxX: maxX, lineStartX: lineStartX, startCharIndex: startCharIndex)

        case .footnoteReference(let id):
            return layoutText("[\(id)]", style: baseStyle, startX: startX, startY: startY, maxX: maxX, lineStartX: lineStartX, startCharIndex: startCharIndex)
        }
    }

    private func layoutInlineImage(
        _ url: String,
        style: TextRunStyle,
        startX: CGFloat,
        startY: CGFloat,
        maxX: CGFloat,
        lineStartX: CGFloat,
        startCharIndex: Int
    ) -> InlineLayoutResult {
        let baselineY = startY + baselineOffset
        let size = imageSizeProvider?(url) ?? inferImageSize(from: url) ?? CGSize(width: lineHeight, height: lineHeight)
        let aspectRatio = size.width / max(1, size.height)
        let height = lineHeight
        let width = max(4, height * aspectRatio)

        var x = startX
        let y = baselineY

        if x + width > maxX && x > lineStartX {
            x = lineStartX
            return layoutInlineImage(
                url,
                style: style,
                startX: x,
                startY: startY + lineHeight,
                maxX: maxX,
                lineStartX: lineStartX,
                startCharIndex: startCharIndex
            )
        }

        let frame = CGRect(
            x: x,
            y: y - ascent,
            width: width,
            height: height
        )

        let image = LayoutInlineImage(
            url: url,
            linkURL: style.isLink ? style.linkURL : nil,
            frame: frame
        )

        return ([], [image], x + width, startY, startCharIndex)
    }

    private func layoutInlineMath(
        _ latex: String,
        style: TextRunStyle,
        startX: CGFloat,
        startY: CGFloat,
        maxX: CGFloat,
        lineStartX: CGFloat,
        startCharIndex: Int
    ) -> InlineLayoutResult {
        guard !latex.isEmpty else {
            return ([], [], startX, startY, startCharIndex)
        }

        let parsed = mathRenderer.parse(latex: latex, isBlock: false)
        let fontSize = baseFont.pointSize
        let baselineY = startY + baselineOffset

        func buildRuns(atX x: CGFloat, baseline: CGFloat, charIndex: inout Int) -> (runs: [LayoutTextRun], width: CGFloat) {
            let mathRuns = mathRenderer.layoutMath(parsed, at: CGPoint(x: x, y: baseline), fontSize: fontSize)
            var layoutRuns: [LayoutTextRun] = []
            var minX = CGFloat.greatestFiniteMagnitude
            var maxX = CGFloat.leastNormalMagnitude

            for run in mathRuns {
                let glyphs = layoutMathGlyphs(run.text, at: run.position, fontSize: run.fontSize, color: run.color, isItalic: run.isItalic)
                if !glyphs.isEmpty {
                    for glyph in glyphs {
                        minX = min(minX, glyph.position.x)
                        maxX = max(maxX, glyph.position.x + glyph.size.width)
                    }
                }
                var runStyle = style
                runStyle.color = run.color
                runStyle.fontVariant = run.isItalic ? .italic : nil
                let range = charIndex..<(charIndex + run.text.count)
                layoutRuns.append(LayoutTextRun(
                    text: run.text,
                    position: run.position,
                    glyphs: glyphs,
                    style: runStyle,
                    characterRange: range,
                    lineY: startY,
                    lineHeight: lineHeight
                ))
                charIndex += run.text.count
            }

            let width = maxX > minX ? (maxX - minX) : 0
            return (layoutRuns, width)
        }

        var measureIndex = startCharIndex
        let measured = buildRuns(atX: 0, baseline: baselineY, charIndex: &measureIndex)
        let width = measured.width

        if startX != lineStartX && startX + width > maxX {
            return layoutInlineMath(
                latex,
                style: style,
                startX: lineStartX,
                startY: startY + lineHeight,
                maxX: maxX,
                lineStartX: lineStartX,
                startCharIndex: startCharIndex
            )
        }

        var charIndex = startCharIndex
        let built = buildRuns(atX: startX, baseline: baselineY, charIndex: &charIndex)
        let newX = startX + built.width
        return (built.runs, [], newX, startY, charIndex)
    }

    private func layoutText(
        _ text: String,
        style: TextRunStyle,
        startX: CGFloat,
        startY: CGFloat,
        maxX: CGFloat,
        lineStartX: CGFloat,
        startCharIndex: Int
    ) -> InlineLayoutResult {
        guard !text.isEmpty else {
            return ([], [], startX, startY, startCharIndex)
        }

        let variant: FontVariant
        if style.isCode {
            variant = .monospace
        } else if style.isBold && style.isItalic {
            variant = .boldItalic
        } else if style.isBold {
            variant = .bold
        } else if let override = style.fontVariant {
            if override == .semibold && style.isItalic {
                variant = .semiboldItalic
            } else {
                variant = override
            }
        } else if style.isItalic {
            variant = .italic
        } else {
            variant = .regular
        }

        guard fonts[variant] != nil else {
            return ([], [], startX, startY, startCharIndex + text.count)
        }

        let tokens = tokenize(text: text)
        var runs: [LayoutTextRun] = []
        var currentX = startX
        var currentY = startY
        var charIndex = startCharIndex
        let maxLineWidth = max(1, maxX - lineStartX)

        func layoutLongToken(
            _ token: String,
            startX: CGFloat,
            startY: CGFloat,
            charIndex: Int
        ) -> InlineLayoutResult {
            guard let baseFont = fonts[variant] else { return ([], [], startX, startY, charIndex + token.count) }

            let attributes: [NSAttributedString.Key: Any] = [
                .font: baseFont,
                .ligature: 1
            ]
            let attrString = NSAttributedString(string: token, attributes: attributes)
            let typesetter = CTTypesetterCreateWithAttributedString(attrString)
            let nsText = token as NSString
            let length = nsText.length

            var runs: [LayoutTextRun] = []
            var x = startX
            var y = startY
            var localCharIndex = charIndex
            var index = 0

            while index < length {
                let availableWidth = max(1, (x == lineStartX ? maxX - lineStartX : maxX - x))
                let breakCount = CTTypesetterSuggestLineBreak(typesetter, index, Double(availableWidth))
                let count = max(1, min(breakCount, length - index))
                let substring = nsText.substring(with: NSRange(location: index, length: count))

                let baselineY = y + baselineOffset
                let glyphsResult = layoutGlyphs(for: substring, font: baseFont, variant: variant, color: style.color, startX: x, startY: baselineY)
                let run = LayoutTextRun(
                    text: substring,
                    position: CGPoint(x: x, y: baselineY),
                    glyphs: glyphsResult.glyphs,
                    style: style,
                    characterRange: localCharIndex..<(localCharIndex + substring.count),
                    lineY: y,
                    lineHeight: lineHeight
                )
                runs.append(run)

                x += glyphsResult.advance
                index += count
                localCharIndex += substring.count

                if index < length {
                    x = lineStartX
                    y += lineHeight
                }
            }

            return (runs, [], x, y, localCharIndex)
        }

        for token in tokens {
            let isWhitespace = token.allSatisfy { $0.isWhitespace }
            if token.isEmpty {
                continue
            }

            let tokenWidth = measureTextWidth(token, variant: variant)

            if currentX != lineStartX && currentX + tokenWidth > maxX {
                currentX = lineStartX
                currentY += lineHeight

                if isWhitespace {
                    charIndex += token.count
                    continue
                }
            }

            if !isWhitespace && tokenWidth > maxLineWidth {
                let longResult = layoutLongToken(token, startX: currentX, startY: currentY, charIndex: charIndex)
                runs.append(contentsOf: longResult.runs)
                currentX = longResult.endX
                currentY = longResult.endY
                charIndex = longResult.endCharIndex
                continue
            }

            let baselineY = currentY + baselineOffset
            guard let baseFont = fonts[variant] else { continue }
            let segments = splitFontSegments(token, baseFont: baseFont)
            for segment in segments {
                let glyphsResult = layoutGlyphs(for: segment.text, font: segment.font, variant: variant, color: style.color, startX: currentX, startY: baselineY)
                let run = LayoutTextRun(
                    text: segment.text,
                    position: CGPoint(x: currentX, y: baselineY),
                    glyphs: glyphsResult.glyphs,
                    style: style,
                    characterRange: charIndex..<(charIndex + segment.text.count),
                    lineY: currentY,
                    lineHeight: lineHeight
                )
                runs.append(run)
                currentX += glyphsResult.advance
                charIndex += segment.text.count
            }
        }

        return (runs, [], currentX, currentY, charIndex)
    }

    private func splitFontSegments(_ text: String, baseFont: CTFont) -> [(text: String, font: CTFont)] {
        var segments: [(text: String, font: CTFont)] = []
        var buffer = ""
        var bufferFont = baseFont
        var bufferFontName = CTFontCopyPostScriptName(baseFont) as String

        for ch in text {
            let chunk = String(ch)
            let utf16Count = chunk.utf16.count
            let fallback = CTFontCreateForString(baseFont, chunk as CFString, CFRangeMake(0, utf16Count))
            let fallbackName = CTFontCopyPostScriptName(fallback) as String

            if buffer.isEmpty {
                buffer = chunk
                bufferFont = fallback
                bufferFontName = fallbackName
                continue
            }

            if fallbackName == bufferFontName {
                buffer.append(chunk)
            } else {
                segments.append((buffer, bufferFont))
                buffer = chunk
                bufferFont = fallback
                bufferFontName = fallbackName
            }
        }

        if !buffer.isEmpty {
            segments.append((buffer, bufferFont))
        }

        return segments
    }

    private func inlineContentHeight(runs: [LayoutTextRun], images: [LayoutInlineImage], startY: CGFloat) -> CGFloat {
        if let bounds = inlineContentBounds(runs: runs, images: images) {
            let maxY = max(startY + lineHeight, bounds.maxY)
            return maxY - startY
        }
        return lineHeight
    }

    private func inlineContentBounds(runs: [LayoutTextRun], images: [LayoutInlineImage]) -> CGRect? {
        var minX = CGFloat.greatestFiniteMagnitude
        var minY = CGFloat.greatestFiniteMagnitude
        var maxX = CGFloat.leastNormalMagnitude
        var maxY = CGFloat.leastNormalMagnitude

        for run in runs {
            for glyph in run.glyphs {
                let baseSize = max(1, baseFontSize)
                let scale = max(0.5, glyph.fontSize / baseSize)
                let glyphAscent = currentAscent * scale
                let glyphDescent = currentDescent * scale
                minX = min(minX, glyph.position.x)
                minY = min(minY, glyph.position.y - glyphAscent)
                maxX = max(maxX, glyph.position.x + glyph.size.width)
                maxY = max(maxY, glyph.position.y + glyphDescent)
            }
        }

        for image in images {
            minX = min(minX, image.frame.minX)
            minY = min(minY, image.frame.minY)
            maxX = max(maxX, image.frame.maxX)
            maxY = max(maxY, image.frame.maxY)
        }

        guard minX != CGFloat.greatestFiniteMagnitude else { return nil }
        return CGRect(x: minX, y: minY, width: maxX - minX, height: maxY - minY)
    }

    private func offsetInlineContent(
        runs: [LayoutTextRun],
        images: [LayoutInlineImage],
        dx: CGFloat,
        dy: CGFloat = 0
    ) -> (runs: [LayoutTextRun], images: [LayoutInlineImage]) {
        guard dx != 0 || dy != 0 else { return (runs, images) }

        let shiftedRuns = runs.map { run in
            let shiftedGlyphs = run.glyphs.map { glyph in
                LayoutGlyph(
                    glyphID: glyph.glyphID,
                    position: CGPoint(x: glyph.position.x + dx, y: glyph.position.y + dy),
                    size: glyph.size,
                    color: glyph.color,
                    fontVariant: glyph.fontVariant,
                    fontSize: glyph.fontSize,
                    fontName: glyph.fontName,
                    stringIndex: glyph.stringIndex
                )
            }
            return LayoutTextRun(
                text: run.text,
                position: CGPoint(x: run.position.x + dx, y: run.position.y + dy),
                glyphs: shiftedGlyphs,
                style: run.style,
                characterRange: run.characterRange,
                lineY: run.lineY.map { $0 + dy },
                lineHeight: run.lineHeight
            )
        }

        let shiftedImages = images.map { image in
            LayoutInlineImage(
                url: image.url,
                linkURL: image.linkURL,
                frame: CGRect(
                    x: image.frame.origin.x + dx,
                    y: image.frame.origin.y + dy,
                    width: image.frame.width,
                    height: image.frame.height
                )
            )
        }

        return (shiftedRuns, shiftedImages)
    }

    private func layoutGlyphs(
        for text: String,
        font: CTFont,
        variant: FontVariant,
        color: SIMD4<Float>,
        startX: CGFloat,
        startY: CGFloat
    ) -> (glyphs: [LayoutGlyph], advance: CGFloat) {
        guard !text.isEmpty else { return ([], 0) }

        let attributes: [NSAttributedString.Key: Any] = [
            .font: font,
            .ligature: 1
        ]
        let line = CTLineCreateWithAttributedString(NSAttributedString(string: text, attributes: attributes))
        let runs = CTLineGetGlyphRuns(line) as? [CTRun] ?? []
        let lineWidth = CGFloat(CTLineGetTypographicBounds(line, nil, nil, nil))

        var glyphs: [LayoutGlyph] = []
        var maxX = startX

        for run in runs {
            let glyphCount = CTRunGetGlyphCount(run)
            guard glyphCount > 0 else { continue }

            let attributes = CTRunGetAttributes(run) as NSDictionary
            let runFont = attributes[kCTFontAttributeName] as! CTFont
            let fontName = CTFontCopyPostScriptName(runFont) as String
            let storedFontName = isSystemUIFontName(fontName) ? nil : fontName
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

                let position = CGPoint(x: startX + positions[i].x, y: startY + positions[i].y)
                let width = advances[i].width
                let glyph = LayoutGlyph(
                    glyphID: glyphID,
                    position: position,
                    size: CGSize(width: width, height: lineHeight),
                    color: color,
                    fontVariant: variant,
                    fontSize: runFontSize,
                    fontName: storedFontName,
                    stringIndex: Int(stringIndices[i])
                )
                glyphs.append(glyph)
                maxX = max(maxX, position.x + width)
            }
        }

        let computedWidth = max(0, maxX - startX)
        return (glyphs, max(computedWidth, lineWidth))
    }

    private func tokenize(text: String) -> [String] {
        guard !text.isEmpty else { return [] }
        var tokens: [String] = []
        var current = ""
        var currentIsWhitespace: Bool?

        for character in text {
            let isWhitespace = character.isWhitespace
            if let currentIsWhitespace = currentIsWhitespace, currentIsWhitespace != isWhitespace {
                tokens.append(current)
                current = ""
            }
            if currentIsWhitespace == nil {
                currentIsWhitespace = isWhitespace
            }
            current.append(character)
            currentIsWhitespace = isWhitespace
        }

        if !current.isEmpty {
            tokens.append(current)
        }

        return tokens
    }

    private func isSystemUIFontName(_ name: String) -> Bool {
        if name.hasPrefix(".SF") || name.hasPrefix(".AppleSystem") {
            return true
        }
        if name == ".AppleColorEmojiUI" || name == "AppleColorEmoji" || name == "AppleColorEmojiUI" {
            return false
        }
        return false
    }
}

private extension CGRect {
    var center: CGPoint {
        CGPoint(x: midX, y: midY)
    }
}
