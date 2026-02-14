//  Exports.swift
//  VVMarkdown
//
//  Re-export all VVMarkdown public types

// This file serves as documentation for the module's public API.
// All types are exported via their respective source files.
//
// Parser:
//   - ParsedMarkdownDocument
//   - MarkdownBlock, MarkdownBlockType
//   - MarkdownInlineContent, InlineElement
//   - MarkdownListItem, MarkdownTableRow
//   - ColumnAlignment, InlineStyle
//   - MarkdownParser
//
// Theme:
//   - MarkdownTheme
//
// Layout:
//   - MarkdownLayout, LayoutBlock, LayoutBlockType
//   - LayoutContent, LayoutTextRun, LayoutInlineImage, TextRunStyle
//   - LayoutGlyph, FontVariant
//   - LayoutListItem, BulletType
//   - LayoutTableRow, LayoutTableCell
//   - LayoutCodeToken, LayoutCodeLine
//   - LayoutMathRun
//   - MarkdownLayoutEngine
//
// Metal Rendering:
//   - VVMetalContext (shared Metal resources + SwiftUI EnvironmentKey: \.vvMetalContext)
//   - MarkdownUniforms
//   - MarkdownGlyphInstance, QuadInstance
//   - BulletInstance, CheckboxInstance
//   - LineInstance, BlockQuoteBorderInstance
//   - TableGridLineInstance, ImageRenderInstance
//   - MarkdownMetalRenderer
//   - MarkdownCachedGlyph, MarkdownGlyphAtlas
//
// Code Highlighting:
//   - MarkdownCodeHighlighter
//   - HighlightedCodeBlock, HighlightedCodeLine, HighlightedCodeToken
//
// Image Loading:
//   - MarkdownImageLoader
//   - LoadedMarkdownImage, ImageInstance
//
// Math Rendering:
//   - MarkdownMathRenderer
//   - RenderedMath, MathToken, MathSymbol, MathCategory
//   - MathGlyphRun
//
// Selection:
//   - MarkdownTextPosition
//   - MarkdownLineMetrics
//   - VVMarkdownSelectionHelper
//
// Views:
//   - VVMarkdownView
