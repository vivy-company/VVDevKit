//  VVMarkdownRenderPipeline.swift
//  VVMarkdown
//
//  Centralizes the VVMarkdown → VVMetalPrimitives scene pipeline.

import CoreText
import Foundation
import VVMetalPrimitives

public struct VVMarkdownRenderPipeline {
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

    public init(
        theme: MarkdownTheme,
        layoutEngine: MarkdownLayoutEngine,
        scale: CGFloat = 2.0,
        componentProvider: MarkdownComponentProvider? = nil,
        styleRegistry: MarkdownStyleRegistry? = nil,
        highlightedCodeBlocks: [String: HighlightedCodeBlock] = [:],
        copiedBlockId: String? = nil,
        copiedAt: TimeInterval = 0
    ) {
        self.init(
            theme: theme,
            layoutEngine: layoutEngine,
            scale: scale,
            componentProvider: componentProvider,
            styleRegistry: styleRegistry,
            highlightedCodeBlocks: highlightedCodeBlocks,
            copiedBlockId: copiedBlockId,
            copiedAt: copiedAt,
            runLineBounds: { _ in nil },
            runRenderedBounds: { _ in nil },
            runBounds: { _ in nil },
            runVisualBounds: { _ in nil },
            lineMetrics: { _ in nil },
            runFont: { _ in nil }
        )
    }

    init(
        theme: MarkdownTheme,
        layoutEngine: MarkdownLayoutEngine,
        scale: CGFloat,
        componentProvider: MarkdownComponentProvider?,
        styleRegistry: MarkdownStyleRegistry?,
        highlightedCodeBlocks: [String: HighlightedCodeBlock],
        copiedBlockId: String?,
        copiedAt: TimeInterval,
        runLineBounds: @escaping (LayoutTextRun) -> CGRect?,
        runRenderedBounds: @escaping (LayoutTextRun) -> CGRect?,
        runBounds: @escaping (LayoutTextRun) -> CGRect?,
        runVisualBounds: @escaping (LayoutTextRun) -> CGRect?,
        lineMetrics: @escaping (LayoutTextRun) -> LineMetrics?,
        runFont: @escaping (LayoutTextRun) -> CTFont?
    ) {
        self.theme = theme
        self.layoutEngine = layoutEngine
        self.scale = scale
        self.componentProvider = componentProvider
        self.styleRegistry = styleRegistry
        self.highlightedCodeBlocks = highlightedCodeBlocks
        self.copiedBlockId = copiedBlockId
        self.copiedAt = copiedAt
        self.runLineBounds = runLineBounds
        self.runRenderedBounds = runRenderedBounds
        self.runBounds = runBounds
        self.runVisualBounds = runVisualBounds
        self.lineMetrics = lineMetrics
        self.runFont = runFont
    }

    public func buildScene(from layout: MarkdownLayout) -> VVScene {
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
