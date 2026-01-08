//  VVMarkdownRenderPipeline.swift
//  VVMarkdown
//
//  Centralizes the VVMarkdown → VVMetalPrimitives scene pipeline.

import CoreText
import Foundation
import VVMetalPrimitives

struct VVMarkdownRenderPipeline {
    typealias LineMetrics = VVMarkdownSceneBuilder.LineMetrics

    let theme: MarkdownTheme
    let layoutEngine: MarkdownLayoutEngine
    let scale: CGFloat
    let componentProvider: MarkdownComponentProvider?
    let styleRegistry: MarkdownStyleRegistry?
    let highlightedCodeBlocks: [String: HighlightedCodeBlock]
    let copiedBlockId: String?
    let copiedAt: TimeInterval
    let runLineBounds: (LayoutTextRun) -> CGRect?
    let runRenderedBounds: (LayoutTextRun) -> CGRect?
    let runBounds: (LayoutTextRun) -> CGRect?
    let runVisualBounds: (LayoutTextRun) -> CGRect?
    let lineMetrics: (LayoutTextRun) -> LineMetrics?
    let runFont: (LayoutTextRun) -> CTFont?

    func buildScene(from layout: MarkdownLayout) -> VVScene {
        let sceneBuilder = VVMarkdownSceneBuilder(
            theme: theme,
            layoutEngine: layoutEngine,
            contentWidth: layout.contentWidth,
            scale: scale,
            componentProvider: componentProvider,
            styleRegistry: styleRegistry,
            highlightedCodeBlocks: highlightedCodeBlocks,
            copiedBlockId: copiedBlockId,
            copiedAt: copiedAt,
            runLineBounds: runLineBounds,
            runRenderedBounds: runRenderedBounds,
            runBounds: runBounds,
            runVisualBounds: runVisualBounds,
            lineMetrics: lineMetrics,
            runFont: runFont
        )
        return sceneBuilder.buildScene(from: layout)
    }
}
