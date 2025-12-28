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
    case table
    case image
    case thematicBreak
    case mathBlock
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
    case code(String, language: String?, lines: [LayoutCodeLine])
    case listItems([LayoutListItem])
    case quoteBlocks([LayoutBlock])
    case tableRows([LayoutTableRow])
    case image(url: String, alt: String?, size: CGSize?)
    case thematicBreak
    case math(latex: String, runs: [LayoutMathRun])
}

/// A run of styled text
public struct LayoutTextRun {
    public let text: String
    public let position: CGPoint
    public let glyphs: [LayoutGlyph]
    public let style: TextRunStyle
    public let characterRange: Range<Int>

    public init(text: String, position: CGPoint, glyphs: [LayoutGlyph], style: TextRunStyle, characterRange: Range<Int>) {
        self.text = text
        self.position = position
        self.glyphs = glyphs
        self.style = style
        self.characterRange = characterRange
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

    public init(color: SIMD4<Float> = SIMD4(1, 1, 1, 1)) {
        self.color = color
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

    public init(glyphID: CGGlyph, position: CGPoint, size: CGSize, color: SIMD4<Float>, fontVariant: FontVariant, fontSize: CGFloat = 14) {
        self.glyphID = glyphID
        self.position = position
        self.size = size
        self.color = color
        self.fontVariant = fontVariant
        self.fontSize = fontSize
    }
}

/// Font variant for styling
public enum FontVariant: Hashable, Sendable {
    case regular
    case bold
    case italic
    case boldItalic
    case monospace
}

/// Layout list item
public struct LayoutListItem {
    public let depth: Int
    public let bulletPosition: CGPoint
    public let bulletType: BulletType
    public let contentRuns: [LayoutTextRun]
    public let children: [LayoutListItem]

    public init(depth: Int, bulletPosition: CGPoint, bulletType: BulletType, contentRuns: [LayoutTextRun], children: [LayoutListItem]) {
        self.depth = depth
        self.bulletPosition = bulletPosition
        self.bulletType = bulletType
        self.contentRuns = contentRuns
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
    public let frame: CGRect
    public let alignment: ColumnAlignment

    public init(textRuns: [LayoutTextRun], frame: CGRect, alignment: ColumnAlignment) {
        self.textRuns = textRuns
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

    private var fonts: [FontVariant: CTFont] = [:]
    private var lineHeight: CGFloat = 20
    private var ascent: CGFloat = 14
    private var descent: CGFloat = 4

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

        ascent = CTFontGetAscent(ctFont)
        descent = CTFontGetDescent(ctFont)
        let leading = CTFontGetLeading(ctFont)
        lineHeight = ceil((ascent + descent + leading) * 1.4)
    }

    // MARK: - Public API

    public var currentLineHeight: CGFloat { lineHeight }
    public var currentAscent: CGFloat { ascent }
    public var currentDescent: CGFloat { descent }

    public func updateTheme(_ theme: MarkdownTheme) {
        self.theme = theme
    }

    public func updateContentWidth(_ width: CGFloat) {
        self.contentWidth = width
    }

    /// Get glyphs for a number string (for list item number rendering)
    public func layoutNumberGlyphs(_ number: Int, at position: CGPoint, color: SIMD4<Float>) -> [LayoutGlyph] {
        let text = "\(number)."
        guard let font = fonts[.regular] else { return [] }

        var glyphs: [LayoutGlyph] = []
        var currentX = position.x

        var unichars = Array(text.utf16)
        var cgGlyphs = [CGGlyph](repeating: 0, count: unichars.count)
        CTFontGetGlyphsForCharacters(font, &unichars, &cgGlyphs, unichars.count)

        var advances = [CGSize](repeating: .zero, count: cgGlyphs.count)
        CTFontGetAdvancesForGlyphs(font, .horizontal, cgGlyphs, &advances, cgGlyphs.count)

        let fontSize = CTFontGetSize(font)
        for i in 0..<cgGlyphs.count {
            if cgGlyphs[i] != 0 {
                glyphs.append(LayoutGlyph(
                    glyphID: cgGlyphs[i],
                    position: CGPoint(x: currentX, y: position.y),
                    size: CGSize(width: advances[i].width, height: lineHeight),
                    color: color,
                    fontVariant: .regular,
                    fontSize: fontSize
                ))
            }
            currentX += advances[i].width
        }

        return glyphs
    }

    /// Get glyphs for code text (for code block rendering)
    public func layoutCodeGlyphs(_ text: String, at position: CGPoint, color: SIMD4<Float>) -> [LayoutGlyph] {
        guard let font = fonts[.monospace] else { return [] }

        var glyphs: [LayoutGlyph] = []
        var currentX = position.x

        var unichars = Array(text.utf16)
        var cgGlyphs = [CGGlyph](repeating: 0, count: unichars.count)
        CTFontGetGlyphsForCharacters(font, &unichars, &cgGlyphs, unichars.count)

        var advances = [CGSize](repeating: .zero, count: cgGlyphs.count)
        CTFontGetAdvancesForGlyphs(font, .horizontal, cgGlyphs, &advances, cgGlyphs.count)

        let fontSize = CTFontGetSize(font)
        for i in 0..<cgGlyphs.count {
            if cgGlyphs[i] != 0 {
                glyphs.append(LayoutGlyph(
                    glyphID: cgGlyphs[i],
                    position: CGPoint(x: currentX, y: position.y),
                    size: CGSize(width: advances[i].width, height: lineHeight),
                    color: color,
                    fontVariant: .monospace,
                    fontSize: fontSize
                ))
            }
            currentX += advances[i].width
        }

        return glyphs
    }

    /// Get glyphs for math text (for math rendering)
    public func layoutMathGlyphs(_ text: String, at position: CGPoint, fontSize: CGFloat, color: SIMD4<Float>, isItalic: Bool) -> [LayoutGlyph] {
        let variant: FontVariant = isItalic ? .italic : .regular
        guard let font = fonts[variant] else { return [] }

        var glyphs: [LayoutGlyph] = []
        var currentX = position.x

        var unichars = Array(text.utf16)
        var cgGlyphs = [CGGlyph](repeating: 0, count: unichars.count)
        CTFontGetGlyphsForCharacters(font, &unichars, &cgGlyphs, unichars.count)

        var advances = [CGSize](repeating: .zero, count: cgGlyphs.count)
        CTFontGetAdvancesForGlyphs(font, .horizontal, cgGlyphs, &advances, cgGlyphs.count)

        for i in 0..<cgGlyphs.count {
            if cgGlyphs[i] != 0 {
                glyphs.append(LayoutGlyph(
                    glyphID: cgGlyphs[i],
                    position: CGPoint(x: currentX, y: position.y),
                    size: CGSize(width: advances[i].width, height: fontSize),
                    color: color,
                    fontVariant: variant,
                    fontSize: fontSize
                ))
            }
            currentX += advances[i].width
        }

        return glyphs
    }

    /// Layout a parsed markdown document
    public func layout(_ document: ParsedMarkdownDocument) -> MarkdownLayout {
        var blocks: [LayoutBlock] = []
        let padding = CGFloat(theme.contentPadding)
        var currentY: CGFloat = padding

        for block in document.blocks {
            let layoutBlock = layoutBlock(block, at: currentY)
            blocks.append(layoutBlock)
            currentY = layoutBlock.frame.maxY + CGFloat(theme.paragraphSpacing)
        }

        return MarkdownLayout(
            blocks: blocks,
            totalHeight: currentY + padding,
            contentWidth: contentWidth
        )
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

        case .table(let rows, let alignments):
            return layoutTable(block.id, rows: rows, alignments: alignments, at: y)

        case .image(let url, let alt):
            return layoutImage(block.id, url: url, alt: alt, at: y)

        case .thematicBreak:
            return layoutThematicBreak(block.id, at: y)

        case .mathBlock(let content):
            return layoutMathBlock(block.id, content: content, at: y)

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
        let runs = layoutInlineContent(content, color: theme.textColor, startX: padding, startY: y)
        let height = runs.isEmpty ? lineHeight : runs.map { $0.position.y + lineHeight }.max()! - y

        return LayoutBlock(
            blockId: id,
            blockType: .paragraph,
            frame: CGRect(x: padding, y: y, width: contentWidth - padding * 2, height: height),
            content: .text(runs)
        )
    }

    private func layoutHeading(_ id: String, content: MarkdownInlineContent, level: Int, at y: CGFloat) -> LayoutBlock {
        let padding = CGFloat(theme.contentPadding)
        let scale = CGFloat(theme.headingScale(for: level))
        let scaledLineHeight = lineHeight * scale

        // Create scaled font for heading
        let headingFont = VVFont.systemFont(ofSize: baseFont.pointSize * scale, weight: level <= 2 ? .bold : .semibold)
        let savedFont = baseFont
        baseFont = headingFont
        setupFonts()

        let runs = layoutInlineContent(content, color: theme.headingColor, startX: padding, startY: y)

        baseFont = savedFont
        setupFonts()

        let height = runs.isEmpty ? scaledLineHeight : runs.map { $0.position.y + scaledLineHeight }.max()! - y

        return LayoutBlock(
            blockId: id,
            blockType: .heading(level: level),
            frame: CGRect(x: padding, y: y, width: contentWidth - padding * 2, height: height),
            content: .text(runs)
        )
    }

    private func layoutCodeBlock(_ id: String, code: String, language: String?, at y: CGFloat) -> LayoutBlock {
        let contentPadding = CGFloat(theme.contentPadding)
        let codePadding = CGFloat(theme.codeBlockPadding)
        let codeLines = code.components(separatedBy: "\n")
        let height = CGFloat(codeLines.count) * lineHeight + codePadding * 2

        // Create default layout lines (highlighting applied async by view)
        var layoutLines: [LayoutCodeLine] = []
        for (index, lineText) in codeLines.enumerated() {
            let yOffset = codePadding + CGFloat(index) * lineHeight
            let defaultToken = LayoutCodeToken(
                text: lineText,
                range: NSRange(location: 0, length: lineText.utf16.count),
                color: theme.codeColor
            )
            layoutLines.append(LayoutCodeLine(
                lineNumber: index + 1,
                text: lineText,
                tokens: [defaultToken],
                yOffset: yOffset
            ))
        }

        return LayoutBlock(
            blockId: id,
            blockType: .codeBlock(language: language),
            frame: CGRect(x: contentPadding, y: y, width: contentWidth - contentPadding * 2, height: height),
            content: .code(code, language: language, lines: layoutLines)
        )
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
        let contentX = padding + indent + CGFloat(theme.listIndent)

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

        let color = item.checkbox == .checked ? theme.strikethroughColor : theme.textColor
        let runs = layoutInlineContent(item.content, color: color, startX: contentX, startY: y)
        let contentHeight = runs.isEmpty ? lineHeight : runs.map { $0.position.y + lineHeight }.max()! - y

        var totalHeight = contentHeight
        var childItems: [LayoutListItem] = []

        for child in item.children {
            let (childItem, childHeight) = layoutListItem(child, at: y + totalHeight)
            childItems.append(childItem)
            totalHeight += childHeight
        }

        let layoutItem = LayoutListItem(
            depth: item.depth,
            bulletPosition: CGPoint(x: bulletX, y: y),
            bulletType: bulletType,
            contentRuns: runs,
            children: childItems
        )

        return (layoutItem, totalHeight)
    }

    private func layoutBlockQuote(_ id: String, blocks: [MarkdownBlock], at y: CGFloat) -> LayoutBlock {
        var nestedBlocks: [LayoutBlock] = []
        var currentY = y
        let padding = CGFloat(theme.contentPadding)
        let indent = CGFloat(theme.blockQuoteIndent)

        for block in blocks {
            var layoutBlock = layoutBlock(block, at: currentY)
            // Adjust frame for indent
            layoutBlock = LayoutBlock(
                blockId: layoutBlock.blockId,
                blockType: layoutBlock.blockType,
                frame: CGRect(
                    x: padding + indent + CGFloat(theme.blockQuoteBorderWidth) + 4,
                    y: layoutBlock.frame.origin.y,
                    width: contentWidth - padding * 2 - indent - CGFloat(theme.blockQuoteBorderWidth) - 4,
                    height: layoutBlock.frame.height
                ),
                content: layoutBlock.content
            )
            nestedBlocks.append(layoutBlock)
            currentY = layoutBlock.frame.maxY + 4
        }

        return LayoutBlock(
            blockId: id,
            blockType: .blockQuote,
            frame: CGRect(x: 0, y: y, width: contentWidth, height: currentY - y),
            content: .quoteBlocks(nestedBlocks)
        )
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
            var cells: [LayoutTableCell] = []
            var cellX: CGFloat = contentPadding

            for (i, cell) in row.cells.enumerated() {
                let alignment = i < alignments.count ? alignments[i] : .left
                let runs = layoutInlineContent(cell, color: theme.textColor, startX: cellX + cellPadding, startY: currentY + CGFloat(theme.tableRowPadding))

                let cellFrame = CGRect(
                    x: cellX,
                    y: currentY,
                    width: columnWidth + cellPadding * 2,
                    height: lineHeight + CGFloat(theme.tableRowPadding) * 2
                )

                cells.append(LayoutTableCell(textRuns: runs, frame: cellFrame, alignment: alignment))
                cellX += columnWidth + cellPadding * 2
            }

            let rowHeight = lineHeight + CGFloat(theme.tableRowPadding) * 2
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

    private func layoutImage(_ id: String, url: String, alt: String?, at y: CGFloat) -> LayoutBlock {
        // Placeholder size for images - actual size updated when image loads
        let contentPadding = CGFloat(theme.contentPadding)
        let placeholderHeight: CGFloat = 200

        return LayoutBlock(
            blockId: id,
            blockType: .image,
            frame: CGRect(x: contentPadding, y: y, width: contentWidth - contentPadding * 2, height: placeholderHeight),
            content: .image(url: url, alt: alt, size: nil)
        )
    }

    /// Update layout for a specific image with loaded size
    public func updateImageLayout(in layout: inout MarkdownLayout, blockId: String, imageSize: CGSize) {
        var updatedBlocks = layout.blocks
        var yAdjustment: CGFloat = 0

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

            if block.blockId == blockId, case .image(let url, let alt, _) = block.content {
                let aspectRatio = imageSize.width / max(1, imageSize.height)
                let displayWidth = min(contentWidth, imageSize.width)
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
            }

            updatedBlocks[i] = block
        }

        layout = MarkdownLayout(
            blocks: updatedBlocks,
            totalHeight: layout.totalHeight + yAdjustment,
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
        let mathLines = content.split(separator: "\n", omittingEmptySubsequences: false)
        let height = CGFloat(max(1, mathLines.count)) * lineHeight + codePadding * 2

        // Create placeholder math runs - actual parsing done by MarkdownMathRenderer
        var runs: [LayoutMathRun] = []
        let startX = contentPadding + codePadding
        var currentY = y + codePadding

        for line in mathLines {
            runs.append(LayoutMathRun(
                text: String(line),
                position: CGPoint(x: startX, y: currentY),
                fontSize: baseFont.pointSize,
                color: theme.mathColor,
                isItalic: true
            ))
            currentY += lineHeight
        }

        return LayoutBlock(
            blockId: id,
            blockType: .mathBlock,
            frame: CGRect(x: contentPadding, y: y, width: contentWidth - contentPadding * 2, height: height),
            content: .math(latex: content, runs: runs)
        )
    }

    // MARK: - Inline Layout

    private func layoutInlineContent(
        _ content: MarkdownInlineContent,
        color: SIMD4<Float>,
        startX: CGFloat,
        startY: CGFloat
    ) -> [LayoutTextRun] {
        var runs: [LayoutTextRun] = []
        var currentX = startX
        var currentY = startY
        var charIndex = 0

        for element in content.elements {
            let (elementRuns, endX, endY, endCharIndex) = layoutInlineElement(
                element,
                baseColor: color,
                startX: currentX,
                startY: currentY,
                startCharIndex: charIndex
            )
            runs.append(contentsOf: elementRuns)
            currentX = endX
            currentY = endY
            charIndex = endCharIndex
        }

        return runs
    }

    private func layoutInlineElement(
        _ element: InlineElement,
        baseColor: SIMD4<Float>,
        startX: CGFloat,
        startY: CGFloat,
        startCharIndex: Int
    ) -> ([LayoutTextRun], CGFloat, CGFloat, Int) {
        switch element {
        case .text(let text):
            return layoutText(text, style: TextRunStyle(color: baseColor), startX: startX, startY: startY, startCharIndex: startCharIndex)

        case .strong(let content):
            var style = TextRunStyle(color: baseColor)
            style.isBold = true
            return layoutStyledContent(content, style: style, startX: startX, startY: startY, startCharIndex: startCharIndex)

        case .emphasis(let content):
            var style = TextRunStyle(color: baseColor)
            style.isItalic = true
            return layoutStyledContent(content, style: style, startX: startX, startY: startY, startCharIndex: startCharIndex)

        case .strikethrough(let content):
            var style = TextRunStyle(color: theme.strikethroughColor)
            style.isStrikethrough = true
            return layoutStyledContent(content, style: style, startX: startX, startY: startY, startCharIndex: startCharIndex)

        case .code(let code):
            var style = TextRunStyle(color: theme.codeColor)
            style.isCode = true
            return layoutText(code, style: style, startX: startX, startY: startY, startCharIndex: startCharIndex)

        case .link(let content, let url, _):
            var style = TextRunStyle(color: theme.linkColor)
            style.isLink = true
            style.linkURL = url
            return layoutStyledContent(content, style: style, startX: startX, startY: startY, startCharIndex: startCharIndex)

        case .math(let math):
            var style = TextRunStyle(color: theme.mathColor)
            style.isCode = true
            return layoutText("$\(math)$", style: style, startX: startX, startY: startY, startCharIndex: startCharIndex)

        case .softBreak:
            return ([], startX + 4, startY, startCharIndex + 1)

        case .hardBreak:
            return ([], 0, startY + lineHeight, startCharIndex + 1)

        case .image, .html, .footnoteReference:
            // Placeholder
            return ([], startX, startY, startCharIndex)
        }
    }

    private func layoutStyledContent(
        _ content: MarkdownInlineContent,
        style: TextRunStyle,
        startX: CGFloat,
        startY: CGFloat,
        startCharIndex: Int
    ) -> ([LayoutTextRun], CGFloat, CGFloat, Int) {
        var runs: [LayoutTextRun] = []
        var currentX = startX
        var currentY = startY
        var charIndex = startCharIndex

        for element in content.elements {
            let text = element.plainText
            let (elementRuns, endX, endY, endCharIndex) = layoutText(
                text,
                style: style,
                startX: currentX,
                startY: currentY,
                startCharIndex: charIndex
            )
            runs.append(contentsOf: elementRuns)
            currentX = endX
            currentY = endY
            charIndex = endCharIndex
        }

        return (runs, currentX, currentY, charIndex)
    }

    private func layoutText(
        _ text: String,
        style: TextRunStyle,
        startX: CGFloat,
        startY: CGFloat,
        startCharIndex: Int
    ) -> ([LayoutTextRun], CGFloat, CGFloat, Int) {
        guard !text.isEmpty else {
            return ([], startX, startY, startCharIndex)
        }

        let variant: FontVariant
        if style.isCode {
            variant = .monospace
        } else if style.isBold && style.isItalic {
            variant = .boldItalic
        } else if style.isBold {
            variant = .bold
        } else if style.isItalic {
            variant = .italic
        } else {
            variant = .regular
        }

        guard let font = fonts[variant] else {
            return ([], startX, startY, startCharIndex + text.count)
        }

        // Simple single-line layout for now
        var glyphs: [LayoutGlyph] = []
        var currentX = startX

        var unichars = Array(text.utf16)
        var cgGlyphs = [CGGlyph](repeating: 0, count: unichars.count)
        CTFontGetGlyphsForCharacters(font, &unichars, &cgGlyphs, unichars.count)

        var advances = [CGSize](repeating: .zero, count: cgGlyphs.count)
        CTFontGetAdvancesForGlyphs(font, .horizontal, cgGlyphs, &advances, cgGlyphs.count)

        let fontSize = CTFontGetSize(font)
        for i in 0..<cgGlyphs.count {
            if cgGlyphs[i] != 0 {
                var boundingRect = CGRect.zero
                var glyph = cgGlyphs[i]
                CTFontGetBoundingRectsForGlyphs(font, .horizontal, &glyph, &boundingRect, 1)

                glyphs.append(LayoutGlyph(
                    glyphID: cgGlyphs[i],
                    position: CGPoint(x: currentX, y: startY),
                    size: CGSize(width: advances[i].width, height: lineHeight),
                    color: style.color,
                    fontVariant: variant,
                    fontSize: fontSize
                ))
            }
            currentX += advances[i].width
        }

        let run = LayoutTextRun(
            text: text,
            position: CGPoint(x: startX, y: startY),
            glyphs: glyphs,
            style: style,
            characterRange: startCharIndex..<(startCharIndex + text.count)
        )

        return ([run], currentX, startY, startCharIndex + text.count)
    }
}
