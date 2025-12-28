//  VVMarkdownView.swift
//  VVMarkdown
//
//  SwiftUI and AppKit views for Metal-based markdown rendering

import Foundation
import Metal
import MetalKit
import SwiftUI
import simd
import VVHighlighting

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

// MARK: - Text Selection Types

/// Position in the markdown text for selection
struct TextPosition: Comparable {
    let blockIndex: Int
    let runIndex: Int
    let glyphIndex: Int
    let characterOffset: Int

    static func < (lhs: TextPosition, rhs: TextPosition) -> Bool {
        if lhs.blockIndex != rhs.blockIndex { return lhs.blockIndex < rhs.blockIndex }
        if lhs.runIndex != rhs.runIndex { return lhs.runIndex < rhs.runIndex }
        return lhs.glyphIndex < rhs.glyphIndex
    }
}

/// A range of selected text with associated layout information
struct SelectionRange {
    let start: TextPosition
    let end: TextPosition
    let rects: [CGRect]
    let selectedText: String
}

// MARK: - VVMarkdownView (SwiftUI)

/// SwiftUI view for rendering markdown with Metal
public struct VVMarkdownView: View {
    private let content: String
    private let theme: MarkdownTheme
    private let font: VVFont

    @State private var scrollOffset: CGPoint = .zero

    public init(
        content: String,
        theme: MarkdownTheme = .dark,
        font: VVFont = .systemFont(ofSize: 14)
    ) {
        self.content = content
        self.theme = theme
        self.font = font
    }

    public var body: some View {
        MetalMarkdownViewRepresentable(
            content: content,
            theme: theme,
            font: font,
            scrollOffset: $scrollOffset
        )
    }
}

// MARK: - MetalMarkdownViewRepresentable

#if canImport(AppKit)
public struct MetalMarkdownViewRepresentable: NSViewRepresentable {
    let content: String
    let theme: MarkdownTheme
    let font: VVFont
    @Binding var scrollOffset: CGPoint

    public func makeNSView(context: Context) -> MetalMarkdownNSView {
        let view = MetalMarkdownNSView(frame: .zero, font: font, theme: theme)
        view.setContent(content)
        return view
    }

    public func updateNSView(_ nsView: MetalMarkdownNSView, context: Context) {
        nsView.setContent(content)
        nsView.updateTheme(theme)
    }
}
#else
public struct MetalMarkdownViewRepresentable: UIViewRepresentable {
    let content: String
    let theme: MarkdownTheme
    let font: VVFont
    @Binding var scrollOffset: CGPoint

    public func makeUIView(context: Context) -> MetalMarkdownUIView {
        let view = MetalMarkdownUIView(frame: .zero, font: font, theme: theme)
        view.setContent(content)
        return view
    }

    public func updateUIView(_ uiView: MetalMarkdownUIView, context: Context) {
        uiView.setContent(content)
        uiView.updateTheme(theme)
    }
}
#endif

// MARK: - MetalMarkdownNSView (macOS)

#if canImport(AppKit)
public class MetalMarkdownNSView: NSView {

    // MARK: - Properties

    private var metalLayer: CAMetalLayer!
    private var renderer: MarkdownMetalRenderer?
    private var displayLink: CVDisplayLink?

    private let parser = MarkdownParser()
    private var layoutEngine: MarkdownLayoutEngine
    private var document: ParsedMarkdownDocument = .empty
    private var cachedLayout: MarkdownLayout?

    private var scrollOffset: CGPoint = .zero
    private var contentHeight: CGFloat = 0
    private var needsRedraw: Bool = true

    private var theme: MarkdownTheme
    private var baseFont: VVFont

    // Code highlighting
    private let codeHighlighter: MarkdownCodeHighlighter
    private var highlightedCodeBlocks: [String: HighlightedCodeBlock] = [:]
    private var pendingHighlightTasks: Set<String> = []

    // Image loading
    private var imageLoader: MarkdownImageLoader?
    private var loadedImages: [String: MTLTexture] = [:]

    // Math rendering
    private let mathRenderer = MarkdownMathRenderer()
    private var parsedMathBlocks: [String: RenderedMath] = [:]

    // Text selection
    private var selectionStart: TextPosition?
    private var selectionEnd: TextPosition?
    private var isSelecting: Bool = false
    private var selectionColor: SIMD4<Float> = SIMD4(0.3, 0.5, 0.8, 0.4)

    // MARK: - Initialization

    public init(frame: CGRect, font: VVFont, theme: MarkdownTheme) {
        self.baseFont = font
        self.theme = theme
        self.layoutEngine = MarkdownLayoutEngine(baseFont: font, theme: theme, contentWidth: frame.width)
        self.codeHighlighter = MarkdownCodeHighlighter(theme: .defaultDark)
        super.init(frame: frame)
        setup()
    }

    required init?(coder: NSCoder) {
        self.baseFont = .systemFont(ofSize: 14)
        self.theme = .dark
        self.layoutEngine = MarkdownLayoutEngine(baseFont: baseFont, theme: theme, contentWidth: 600)
        self.codeHighlighter = MarkdownCodeHighlighter(theme: .defaultDark)
        super.init(coder: coder)
        setup()
    }

    private func setup() {
        wantsLayer = true
        layerContentsRedrawPolicy = .duringViewResize

        metalLayer = CAMetalLayer()
        metalLayer.device = MTLCreateSystemDefaultDevice()
        metalLayer.pixelFormat = .bgra8Unorm
        metalLayer.framebufferOnly = true
        metalLayer.contentsScale = NSScreen.main?.backingScaleFactor ?? 2.0

        layer = metalLayer

        if let device = metalLayer.device {
            do {
                renderer = try MarkdownMetalRenderer(device: device, baseFont: baseFont, scaleFactor: metalLayer.contentsScale)
                imageLoader = MarkdownImageLoader(device: device)
            } catch {
                print("Failed to create markdown renderer: \(error)")
            }
        }

        setupDisplayLink()
    }

    private func setupDisplayLink() {
        var link: CVDisplayLink?
        CVDisplayLinkCreateWithActiveCGDisplays(&link)

        guard let displayLink = link else { return }

        let callback: CVDisplayLinkOutputCallback = { _, _, _, _, _, userInfo -> CVReturn in
            let view = Unmanaged<MetalMarkdownNSView>.fromOpaque(userInfo!).takeUnretainedValue()
            if view.needsRedraw {
                DispatchQueue.main.async {
                    view.render()
                }
            }
            return kCVReturnSuccess
        }

        CVDisplayLinkSetOutputCallback(displayLink, callback, Unmanaged.passUnretained(self).toOpaque())
        CVDisplayLinkStart(displayLink)
        self.displayLink = displayLink
    }

    deinit {
        if let displayLink = displayLink {
            CVDisplayLinkStop(displayLink)
        }
    }

    // MARK: - Public API

    public func setContent(_ content: String) {
        document = parser.parse(content)
        layoutEngine.updateContentWidth(bounds.width)
        cachedLayout = layoutEngine.layout(document)
        contentHeight = cachedLayout?.totalHeight ?? 0

        // Clear selection when content changes
        selectionStart = nil
        selectionEnd = nil
        isSelecting = false

        needsRedraw = true

        // Trigger async highlighting and image loading
        processBlocks()
    }

    public func updateTheme(_ theme: MarkdownTheme) {
        self.theme = theme
        layoutEngine.updateTheme(theme)
        if cachedLayout != nil {
            cachedLayout = layoutEngine.layout(document)
        }
        mathRenderer.setMathColor(theme.mathColor)
        needsRedraw = true
    }

    private func processBlocks() {
        for block in document.blocks {
            processBlock(block)
        }
    }

    private func processBlock(_ block: MarkdownBlock) {
        switch block.type {
        case .codeBlock(let code, let language, _):
            if !highlightedCodeBlocks.keys.contains(block.id) && !pendingHighlightTasks.contains(block.id) {
                pendingHighlightTasks.insert(block.id)
                Task {
                    let highlighted = await codeHighlighter.highlight(code: code, language: language)
                    await MainActor.run {
                        self.highlightedCodeBlocks[block.id] = highlighted
                        self.pendingHighlightTasks.remove(block.id)
                        self.needsRedraw = true
                    }
                }
            }

        case .image(let url, _):
            if loadedImages[url] == nil {
                imageLoader?.loadImage(from: url) { [weak self] loadedImage in
                    guard let self = self, let loadedImage = loadedImage else { return }
                    DispatchQueue.main.async {
                        self.loadedImages[url] = loadedImage.texture
                        // Update layout with actual image size
                        if var layout = self.cachedLayout {
                            self.layoutEngine.updateImageLayout(in: &layout, blockId: block.id, imageSize: loadedImage.size)
                            self.cachedLayout = layout
                            self.contentHeight = layout.totalHeight
                        }
                        self.needsRedraw = true
                    }
                }
            }

        case .mathBlock(let latex):
            if !parsedMathBlocks.keys.contains(block.id) {
                let parsed = mathRenderer.parse(latex: latex, isBlock: true)
                parsedMathBlocks[block.id] = parsed
            }

        case .blockQuote(let nested):
            for nestedBlock in nested {
                processBlock(nestedBlock)
            }

        case .list(let items, _, _):
            for item in items {
                processListItem(item)
            }

        default:
            break
        }
    }

    private func processListItem(_ item: MarkdownListItem) {
        for child in item.children {
            processListItem(child)
        }
    }

    // MARK: - Layout

    public override func layout() {
        super.layout()
        metalLayer.frame = bounds
        metalLayer.drawableSize = CGSize(
            width: bounds.width * metalLayer.contentsScale,
            height: bounds.height * metalLayer.contentsScale
        )
        layoutEngine.updateContentWidth(bounds.width)
        cachedLayout = layoutEngine.layout(document)
        needsRedraw = true
    }

    // MARK: - Scrolling

    public override func scrollWheel(with event: NSEvent) {
        scrollOffset.y = max(0, min(contentHeight - bounds.height, scrollOffset.y - event.scrollingDeltaY))
        scrollOffset.x = max(0, scrollOffset.x - event.scrollingDeltaX)
        needsRedraw = true
    }

    // MARK: - Mouse Events & Selection

    public override var acceptsFirstResponder: Bool { true }

    public override func mouseDown(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        let contentPoint = CGPoint(x: point.x + scrollOffset.x, y: bounds.height - point.y + scrollOffset.y)

        selectionStart = hitTest(at: contentPoint)
        selectionEnd = selectionStart
        isSelecting = true
        needsRedraw = true
    }

    public override func mouseDragged(with event: NSEvent) {
        guard isSelecting else { return }

        let point = convert(event.locationInWindow, from: nil)
        let contentPoint = CGPoint(x: point.x + scrollOffset.x, y: bounds.height - point.y + scrollOffset.y)

        selectionEnd = hitTest(at: contentPoint)
        needsRedraw = true
    }

    public override func mouseUp(with event: NSEvent) {
        isSelecting = false
    }

    public override func keyDown(with event: NSEvent) {
        if event.modifierFlags.contains(.command) && event.charactersIgnoringModifiers == "c" {
            copySelection()
        } else if event.modifierFlags.contains(.command) && event.charactersIgnoringModifiers == "a" {
            selectAll()
        } else {
            super.keyDown(with: event)
        }
    }

    private func selectAll() {
        guard let layout = cachedLayout, !layout.blocks.isEmpty else { return }

        // Find first text position
        selectionStart = findFirstPosition(in: layout)
        selectionEnd = findLastPosition(in: layout)
        needsRedraw = true
    }

    private func findFirstPosition(in layout: MarkdownLayout) -> TextPosition? {
        for (blockIndex, block) in layout.blocks.enumerated() {
            if let runs = getTextRuns(from: block), let firstRun = runs.first, !firstRun.glyphs.isEmpty {
                return TextPosition(blockIndex: blockIndex, runIndex: 0, glyphIndex: 0, characterOffset: 0)
            }
        }
        return nil
    }

    private func findLastPosition(in layout: MarkdownLayout) -> TextPosition? {
        for (blockIndex, block) in layout.blocks.enumerated().reversed() {
            if let runs = getTextRuns(from: block), !runs.isEmpty {
                let lastRunIndex = runs.count - 1
                let lastRun = runs[lastRunIndex]
                if !lastRun.glyphs.isEmpty {
                    return TextPosition(
                        blockIndex: blockIndex,
                        runIndex: lastRunIndex,
                        glyphIndex: lastRun.glyphs.count,
                        characterOffset: lastRun.text.count
                    )
                }
            }
        }
        return nil
    }

    private func copySelection() {
        guard let start = selectionStart, let end = selectionEnd else { return }

        let selectedText = getSelectedText(from: start, to: end)
        if !selectedText.isEmpty {
            NSPasteboard.general.clearContents()
            NSPasteboard.general.setString(selectedText, forType: .string)
        }
    }

    private func hitTest(at point: CGPoint) -> TextPosition? {
        guard let layout = cachedLayout else { return nil }

        for (blockIndex, block) in layout.blocks.enumerated() {
            guard let runs = getTextRuns(from: block) else { continue }

            for (runIndex, run) in runs.enumerated() {
                for (glyphIndex, glyph) in run.glyphs.enumerated() {
                    let glyphFrame = CGRect(
                        x: glyph.position.x,
                        y: glyph.position.y,
                        width: glyph.size.width,
                        height: glyph.size.height
                    )

                    // Check if point is within vertical bounds
                    if point.y >= glyphFrame.minY && point.y <= glyphFrame.maxY {
                        // Check if point is before this glyph
                        if point.x <= glyphFrame.midX {
                            return TextPosition(
                                blockIndex: blockIndex,
                                runIndex: runIndex,
                                glyphIndex: glyphIndex,
                                characterOffset: glyphIndex
                            )
                        }
                        // Check if point is after this glyph
                        if point.x <= glyphFrame.maxX {
                            return TextPosition(
                                blockIndex: blockIndex,
                                runIndex: runIndex,
                                glyphIndex: glyphIndex + 1,
                                characterOffset: glyphIndex + 1
                            )
                        }
                    }
                }

                // Check if point is at end of this run's line
                if let lastGlyph = run.glyphs.last {
                    let lineY = lastGlyph.position.y
                    let lineHeight = lastGlyph.size.height
                    if point.y >= lineY && point.y <= lineY + lineHeight && point.x > lastGlyph.position.x + lastGlyph.size.width {
                        return TextPosition(
                            blockIndex: blockIndex,
                            runIndex: runIndex,
                            glyphIndex: run.glyphs.count,
                            characterOffset: run.text.count
                        )
                    }
                }
            }
        }

        return nil
    }

    private func getTextRuns(from block: LayoutBlock) -> [LayoutTextRun]? {
        switch block.content {
        case .text(let runs):
            return runs
        case .listItems(let items):
            return items.flatMap { $0.contentRuns }
        case .quoteBlocks(let blocks):
            return blocks.compactMap { getTextRuns(from: $0) }.flatMap { $0 }
        case .tableRows(let rows):
            return rows.flatMap { $0.cells.flatMap { $0.textRuns } }
        default:
            return nil
        }
    }

    private func getSelectedText(from start: TextPosition, to end: TextPosition) -> String {
        guard let layout = cachedLayout else { return "" }

        let (actualStart, actualEnd) = start < end ? (start, end) : (end, start)
        var selectedText = ""

        for (blockIndex, block) in layout.blocks.enumerated() {
            guard blockIndex >= actualStart.blockIndex && blockIndex <= actualEnd.blockIndex else { continue }
            guard let runs = getTextRuns(from: block) else { continue }

            for (runIndex, run) in runs.enumerated() {
                let isStartBlock = blockIndex == actualStart.blockIndex
                let isEndBlock = blockIndex == actualEnd.blockIndex
                let isStartRun = isStartBlock && runIndex == actualStart.runIndex
                let isEndRun = isEndBlock && runIndex == actualEnd.runIndex

                if isStartBlock && runIndex < actualStart.runIndex { continue }
                if isEndBlock && runIndex > actualEnd.runIndex { break }

                let startIndex: Int
                let endIndex: Int

                if isStartRun {
                    startIndex = min(actualStart.glyphIndex, run.text.count)
                } else {
                    startIndex = 0
                }

                if isEndRun {
                    endIndex = min(actualEnd.glyphIndex, run.text.count)
                } else {
                    endIndex = run.text.count
                }

                if startIndex < endIndex {
                    let textStartIndex = run.text.index(run.text.startIndex, offsetBy: startIndex)
                    let textEndIndex = run.text.index(run.text.startIndex, offsetBy: endIndex)
                    selectedText += String(run.text[textStartIndex..<textEndIndex])
                }
            }

            // Add newline between blocks
            if blockIndex < actualEnd.blockIndex {
                selectedText += "\n"
            }
        }

        return selectedText
    }

    private func getSelectionRects() -> [CGRect] {
        guard let start = selectionStart, let end = selectionEnd, let layout = cachedLayout else { return [] }

        let (actualStart, actualEnd) = start < end ? (start, end) : (end, start)
        var rects: [CGRect] = []

        for (blockIndex, block) in layout.blocks.enumerated() {
            guard blockIndex >= actualStart.blockIndex && blockIndex <= actualEnd.blockIndex else { continue }
            guard let runs = getTextRuns(from: block) else { continue }

            for (runIndex, run) in runs.enumerated() {
                let isStartBlock = blockIndex == actualStart.blockIndex
                let isEndBlock = blockIndex == actualEnd.blockIndex
                let isStartRun = isStartBlock && runIndex == actualStart.runIndex
                let isEndRun = isEndBlock && runIndex == actualEnd.runIndex

                if isStartBlock && runIndex < actualStart.runIndex { continue }
                if isEndBlock && runIndex > actualEnd.runIndex { break }

                guard !run.glyphs.isEmpty else { continue }

                let startGlyphIndex = isStartRun ? min(actualStart.glyphIndex, run.glyphs.count - 1) : 0
                let endGlyphIndex = isEndRun ? min(actualEnd.glyphIndex, run.glyphs.count) : run.glyphs.count

                if startGlyphIndex < endGlyphIndex && startGlyphIndex < run.glyphs.count {
                    let startGlyph = run.glyphs[startGlyphIndex]
                    let endGlyph = run.glyphs[min(endGlyphIndex - 1, run.glyphs.count - 1)]

                    let rect = CGRect(
                        x: startGlyph.position.x,
                        y: startGlyph.position.y,
                        width: endGlyph.position.x + endGlyph.size.width - startGlyph.position.x,
                        height: startGlyph.size.height
                    )
                    rects.append(rect)
                }
            }
        }

        return rects
    }

    // MARK: - Rendering

    private func render() {
        needsRedraw = false

        guard let renderer = renderer,
              let drawable = metalLayer.nextDrawable(),
              let markdownLayout = cachedLayout else { return }

        let commandBuffer = renderer.commandQueue.makeCommandBuffer()

        let passDescriptor = MTLRenderPassDescriptor()
        passDescriptor.colorAttachments[0].texture = drawable.texture
        passDescriptor.colorAttachments[0].loadAction = .clear
        passDescriptor.colorAttachments[0].storeAction = .store
        passDescriptor.colorAttachments[0].clearColor = MTLClearColor(
            red: Double(theme.codeBackgroundColor.x),
            green: Double(theme.codeBackgroundColor.y),
            blue: Double(theme.codeBackgroundColor.z),
            alpha: 1.0
        )

        guard let encoder = commandBuffer?.makeRenderCommandEncoder(descriptor: passDescriptor) else { return }

        renderer.beginFrame(viewportSize: bounds.size, scrollOffset: scrollOffset)

        // Render selection highlights first (behind text)
        renderSelectionHighlights(encoder: encoder, renderer: renderer)

        // Render each block
        for block in markdownLayout.blocks {
            renderBlock(block, encoder: encoder, renderer: renderer)
        }

        encoder.endEncoding()
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
    }

    private func renderSelectionHighlights(encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        let rects = getSelectionRects()
        guard !rects.isEmpty else { return }

        var instances: [QuadInstance] = []
        for rect in rects {
            instances.append(QuadInstance(
                position: SIMD2<Float>(Float(rect.origin.x), Float(rect.origin.y)),
                size: SIMD2<Float>(Float(rect.width), Float(rect.height)),
                color: selectionColor,
                cornerRadius: 2
            ))
        }

        if let buffer = renderer.makeBuffer(for: instances) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: instances.count, rounded: true)
        }
    }

    private func renderBlock(_ block: LayoutBlock, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        switch block.content {
        case .text(let runs):
            renderTextRuns(runs, encoder: encoder, renderer: renderer)

        case .code(let code, let language, let lines):
            renderCodeBackground(block.frame, encoder: encoder, renderer: renderer)
            renderCodeBlock(blockId: block.blockId, code: code, language: language, defaultLines: lines, frame: block.frame, encoder: encoder, renderer: renderer)

        case .listItems(let items):
            for item in items {
                renderListItem(item, encoder: encoder, renderer: renderer)
            }

        case .quoteBlocks(let nestedBlocks):
            renderBlockQuoteBorder(block.frame, encoder: encoder, renderer: renderer)
            for nested in nestedBlocks {
                renderBlock(nested, encoder: encoder, renderer: renderer)
            }

        case .tableRows(let rows):
            renderTableGrid(block.frame, rows: rows, encoder: encoder, renderer: renderer)
            for row in rows {
                for cell in row.cells {
                    renderTextRuns(cell.textRuns, encoder: encoder, renderer: renderer)
                }
            }

        case .thematicBreak:
            renderThematicBreak(block.frame, encoder: encoder, renderer: renderer)

        case .math(let latex, let defaultRuns):
            renderMathBlock(blockId: block.blockId, latex: latex, defaultRuns: defaultRuns, frame: block.frame, encoder: encoder, renderer: renderer)

        case .image(let url, _, _):
            renderImage(url: url, frame: block.frame, encoder: encoder, renderer: renderer)
        }
    }

    private func renderTextRuns(_ runs: [LayoutTextRun], encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        var glyphInstances: [MarkdownGlyphInstance] = []
        var underlines: [LineInstance] = []
        var strikethroughs: [LineInstance] = []

        for run in runs {
            for glyph in run.glyphs {
                if let cached = renderer.glyphAtlas.glyph(for: glyph.glyphID, variant: glyph.fontVariant, fontSize: glyph.fontSize) {
                    let instance = MarkdownGlyphInstance(
                        position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x), Float(glyph.position.y + cached.bearing.y)),
                        size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
                        uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
                        uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
                        color: glyph.color
                    )
                    glyphInstances.append(instance)
                }
            }

            // Add underline for links
            if run.style.isLink, let firstGlyph = run.glyphs.first, let lastGlyph = run.glyphs.last {
                let width = lastGlyph.position.x + lastGlyph.size.width - firstGlyph.position.x
                underlines.append(LineInstance(
                    position: SIMD2<Float>(Float(firstGlyph.position.x), Float(run.position.y + firstGlyph.fontSize + 2)),
                    width: Float(width),
                    height: 1,
                    color: run.style.color
                ))
            }

            // Add strikethrough
            if run.style.isStrikethrough, let firstGlyph = run.glyphs.first, let lastGlyph = run.glyphs.last {
                let width = lastGlyph.position.x + lastGlyph.size.width - firstGlyph.position.x
                strikethroughs.append(LineInstance(
                    position: SIMD2<Float>(Float(firstGlyph.position.x), Float(run.position.y + firstGlyph.fontSize * 0.4)),
                    width: Float(width),
                    height: 1,
                    color: run.style.color
                ))
            }
        }

        // Render glyphs
        if !glyphInstances.isEmpty, let buffer = renderer.makeBuffer(for: glyphInstances) {
            renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: glyphInstances.count)
        }

        // Render underlines
        if !underlines.isEmpty, let buffer = renderer.makeBuffer(for: underlines) {
            renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: underlines.count)
        }

        // Render strikethroughs
        if !strikethroughs.isEmpty, let buffer = renderer.makeBuffer(for: strikethroughs) {
            renderer.renderStrikethroughs(encoder: encoder, instances: buffer, instanceCount: strikethroughs.count)
        }
    }

    private func renderListItem(_ item: LayoutListItem, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        // Render bullet or checkbox
        let bulletSize: Float = 8
        let bulletColor = theme.listBulletColor

        switch item.bulletType {
        case .disc, .circle, .square:
            let bulletType: UInt32 = item.bulletType == .disc ? 0 : (item.bulletType == .circle ? 1 : 2)
            let instance = BulletInstance(
                position: SIMD2<Float>(Float(item.bulletPosition.x), Float(item.bulletPosition.y + 4)),
                size: SIMD2<Float>(bulletSize, bulletSize),
                color: bulletColor,
                bulletType: bulletType
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderBullets(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .number(let num):
            // Render number as text glyphs
            let numberGlyphs = layoutEngine.layoutNumberGlyphs(num, at: item.bulletPosition, color: bulletColor)
            renderGlyphs(numberGlyphs, encoder: encoder, renderer: renderer)

        case .checkboxChecked, .checkboxUnchecked:
            let checked = item.bulletType == .checkboxChecked
            let color = checked ? theme.checkboxCheckedColor : theme.checkboxUncheckedColor
            let instance = CheckboxInstance(
                position: SIMD2<Float>(Float(item.bulletPosition.x), Float(item.bulletPosition.y + 2)),
                size: SIMD2<Float>(12, 12),
                color: color,
                isChecked: checked
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderCheckboxes(encoder: encoder, instances: buffer, instanceCount: 1)
            }
        }

        // Render content
        renderTextRuns(item.contentRuns, encoder: encoder, renderer: renderer)

        // Render children
        for child in item.children {
            renderListItem(child, encoder: encoder, renderer: renderer)
        }
    }

    private func renderGlyphs(_ glyphs: [LayoutGlyph], encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        guard !glyphs.isEmpty else { return }

        var instances: [MarkdownGlyphInstance] = []

        for glyph in glyphs {
            if let cached = renderer.glyphAtlas.glyph(for: glyph.glyphID, variant: glyph.fontVariant, fontSize: glyph.fontSize) {
                let instance = MarkdownGlyphInstance(
                    position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x), Float(glyph.position.y + cached.bearing.y)),
                    size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
                    uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
                    uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
                    color: glyph.color
                )
                instances.append(instance)
            }
        }

        if let buffer = renderer.makeBuffer(for: instances) {
            renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: instances.count)
        }
    }

    private func renderCodeBlock(blockId: String, code: String, language: String?, defaultLines: [LayoutCodeLine], frame: CGRect, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        let padding = CGFloat(theme.codeBlockPadding)

        // Use highlighted code if available, otherwise use default
        if let highlighted = highlightedCodeBlocks[blockId] {
            var glyphInstances: [MarkdownGlyphInstance] = []

            for line in highlighted.lines {
                let lineY = frame.origin.y + padding + CGFloat(line.lineNumber - 1) * layoutEngine.currentLineHeight
                var x = frame.origin.x + padding

                for token in line.tokens {
                    let glyphs = layoutEngine.layoutCodeGlyphs(token.text, at: CGPoint(x: x, y: lineY), color: token.color)
                    for glyph in glyphs {
                        if let cached = renderer.glyphAtlas.glyph(for: glyph.glyphID, variant: .monospace, fontSize: glyph.fontSize) {
                            let instance = MarkdownGlyphInstance(
                                position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x), Float(glyph.position.y + cached.bearing.y)),
                                size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
                                uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
                                uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
                                color: glyph.color
                            )
                            glyphInstances.append(instance)
                        }
                        x += glyph.size.width
                    }
                }
            }

            if !glyphInstances.isEmpty, let buffer = renderer.makeBuffer(for: glyphInstances) {
                renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: glyphInstances.count)
            }
        } else {
            // Render with default (non-highlighted) tokens
            var glyphInstances: [MarkdownGlyphInstance] = []

            for line in defaultLines {
                let lineY = frame.origin.y + line.yOffset
                var x = frame.origin.x + padding

                for token in line.tokens {
                    let glyphs = layoutEngine.layoutCodeGlyphs(token.text, at: CGPoint(x: x, y: lineY), color: token.color)
                    for glyph in glyphs {
                        if let cached = renderer.glyphAtlas.glyph(for: glyph.glyphID, variant: .monospace, fontSize: glyph.fontSize) {
                            let instance = MarkdownGlyphInstance(
                                position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x), Float(glyph.position.y + cached.bearing.y)),
                                size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
                                uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
                                uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
                                color: glyph.color
                            )
                            glyphInstances.append(instance)
                        }
                        x += glyph.size.width
                    }
                }
            }

            if !glyphInstances.isEmpty, let buffer = renderer.makeBuffer(for: glyphInstances) {
                renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: glyphInstances.count)
            }
        }
    }

    private func renderMathBlock(blockId: String, latex: String, defaultRuns: [LayoutMathRun], frame: CGRect, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        // Render background
        renderCodeBackground(frame, encoder: encoder, renderer: renderer)

        let padding = CGFloat(theme.codeBlockPadding)

        // Use parsed math if available
        if let parsedMath = parsedMathBlocks[blockId] {
            let mathRuns = mathRenderer.layoutMath(parsedMath, at: CGPoint(x: frame.origin.x + padding, y: frame.origin.y + padding), fontSize: baseFont.pointSize)
            var glyphInstances: [MarkdownGlyphInstance] = []

            for run in mathRuns {
                let variant: FontVariant = run.isItalic ? .italic : .regular
                let glyphs = layoutEngine.layoutMathGlyphs(run.text, at: run.position, fontSize: run.fontSize, color: run.color, isItalic: run.isItalic)

                for glyph in glyphs {
                    if let cached = renderer.glyphAtlas.glyph(for: glyph.glyphID, variant: variant, fontSize: glyph.fontSize) {
                        let instance = MarkdownGlyphInstance(
                            position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x), Float(glyph.position.y + cached.bearing.y)),
                            size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
                            uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
                            uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
                            color: glyph.color
                        )
                        glyphInstances.append(instance)
                    }
                }
            }

            if !glyphInstances.isEmpty, let buffer = renderer.makeBuffer(for: glyphInstances) {
                renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: glyphInstances.count)
            }
        } else {
            // Render default text
            var glyphInstances: [MarkdownGlyphInstance] = []

            for run in defaultRuns {
                let variant: FontVariant = run.isItalic ? .italic : .regular
                let glyphs = layoutEngine.layoutMathGlyphs(run.text, at: run.position, fontSize: run.fontSize, color: run.color, isItalic: run.isItalic)

                for glyph in glyphs {
                    if let cached = renderer.glyphAtlas.glyph(for: glyph.glyphID, variant: variant, fontSize: glyph.fontSize) {
                        let instance = MarkdownGlyphInstance(
                            position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x), Float(glyph.position.y + cached.bearing.y)),
                            size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
                            uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
                            uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
                            color: glyph.color
                        )
                        glyphInstances.append(instance)
                    }
                }
            }

            if !glyphInstances.isEmpty, let buffer = renderer.makeBuffer(for: glyphInstances) {
                renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: glyphInstances.count)
            }
        }
    }

    private func renderImage(url: String, frame: CGRect, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        if let texture = loadedImages[url] {
            let instance = ImageRenderInstance(
                position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
                size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
                cornerRadius: 4
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderImages(encoder: encoder, instances: buffer, instanceCount: 1, texture: texture)
            }
        } else {
            // Render placeholder
            let instance = QuadInstance(
                position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
                size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
                color: theme.codeBackgroundColor,
                cornerRadius: 4
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: true)
            }
        }
    }

    private func renderCodeBackground(_ frame: CGRect, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        let instance = QuadInstance(
            position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
            size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
            color: theme.codeBackgroundColor,
            cornerRadius: 4
        )
        if let buffer = renderer.makeBuffer(for: [instance]) {
            renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: true)
        }
    }

    private func renderBlockQuoteBorder(_ frame: CGRect, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        let instance = BlockQuoteBorderInstance(
            position: SIMD2<Float>(Float(frame.origin.x), Float(frame.origin.y)),
            size: SIMD2<Float>(Float(frame.width), Float(frame.height)),
            color: theme.blockQuoteBorderColor,
            borderWidth: theme.blockQuoteBorderWidth
        )
        if let buffer = renderer.makeBuffer(for: [instance]) {
            renderer.renderBlockQuoteBorders(encoder: encoder, instances: buffer, instanceCount: 1)
        }
    }

    private func renderTableGrid(_ frame: CGRect, rows: [LayoutTableRow], encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        var lines: [TableGridLineInstance] = []

        // Horizontal lines
        var y = Float(frame.origin.y)
        for row in rows {
            lines.append(TableGridLineInstance(
                start: SIMD2<Float>(Float(frame.origin.x), y),
                end: SIMD2<Float>(Float(frame.maxX), y),
                color: theme.tableBorderColor,
                lineWidth: 1
            ))
            y += Float(row.frame.height)
        }
        // Bottom line
        lines.append(TableGridLineInstance(
            start: SIMD2<Float>(Float(frame.origin.x), y),
            end: SIMD2<Float>(Float(frame.maxX), y),
            color: theme.tableBorderColor,
            lineWidth: 1
        ))

        // Vertical lines
        if let firstRow = rows.first {
            var x = Float(frame.origin.x)
            for cell in firstRow.cells {
                lines.append(TableGridLineInstance(
                    start: SIMD2<Float>(x, Float(frame.origin.y)),
                    end: SIMD2<Float>(x, Float(frame.maxY)),
                    color: theme.tableBorderColor,
                    lineWidth: 1
                ))
                x += Float(cell.frame.width)
            }
            // Right line
            lines.append(TableGridLineInstance(
                start: SIMD2<Float>(x, Float(frame.origin.y)),
                end: SIMD2<Float>(x, Float(frame.maxY)),
                color: theme.tableBorderColor,
                lineWidth: 1
            ))
        }

        if let buffer = renderer.makeBuffer(for: lines) {
            renderer.renderTableGrid(encoder: encoder, instances: buffer, instanceCount: lines.count)
        }
    }

    private func renderThematicBreak(_ frame: CGRect, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        let instance = LineInstance(
            position: SIMD2<Float>(Float(frame.origin.x + 20), Float(frame.midY)),
            width: Float(frame.width - 40),
            height: 2,
            color: theme.thematicBreakColor
        )
        if let buffer = renderer.makeBuffer(for: [instance]) {
            renderer.renderThematicBreaks(encoder: encoder, instances: buffer, instanceCount: 1)
        }
    }

}
#endif

// MARK: - MetalMarkdownUIView (iOS)

#if canImport(UIKit)
public class MetalMarkdownUIView: UIView {
    private var metalLayer: CAMetalLayer!
    private var renderer: MarkdownMetalRenderer?
    private var displayLink: CADisplayLink?

    private let parser = MarkdownParser()
    private var layoutEngine: MarkdownLayoutEngine
    private var document: ParsedMarkdownDocument = .empty
    private var cachedLayout: MarkdownLayout?

    private var scrollOffset: CGPoint = .zero
    private var contentHeight: CGFloat = 0
    private var needsRedraw: Bool = true

    private var theme: MarkdownTheme
    private var baseFont: VVFont

    public init(frame: CGRect, font: VVFont, theme: MarkdownTheme) {
        self.baseFont = font
        self.theme = theme
        self.layoutEngine = MarkdownLayoutEngine(baseFont: font, theme: theme, contentWidth: frame.width)
        super.init(frame: frame)
        setup()
    }

    required init?(coder: NSCoder) {
        self.baseFont = .systemFont(ofSize: 14)
        self.theme = .dark
        self.layoutEngine = MarkdownLayoutEngine(baseFont: baseFont, theme: theme, contentWidth: 600)
        super.init(coder: coder)
        setup()
    }

    private func setup() {
        metalLayer = CAMetalLayer()
        metalLayer.device = MTLCreateSystemDefaultDevice()
        metalLayer.pixelFormat = .bgra8Unorm
        metalLayer.framebufferOnly = true
        metalLayer.contentsScale = UIScreen.main.scale

        layer.addSublayer(metalLayer)

        if let device = metalLayer.device {
            do {
                renderer = try MarkdownMetalRenderer(device: device, baseFont: baseFont, scaleFactor: metalLayer.contentsScale)
            } catch {
                print("Failed to create markdown renderer: \(error)")
            }
        }

        displayLink = CADisplayLink(target: self, selector: #selector(renderIfNeeded))
        displayLink?.add(to: .main, forMode: .common)
    }

    @objc private func renderIfNeeded() {
        guard needsRedraw else { return }
        render()
    }

    deinit {
        displayLink?.invalidate()
    }

    public func setContent(_ content: String) {
        document = parser.parse(content)
        layoutEngine.updateContentWidth(bounds.width)
        cachedLayout = layoutEngine.layout(document)
        contentHeight = cachedLayout?.totalHeight ?? 0
        needsRedraw = true
    }

    public func updateTheme(_ theme: MarkdownTheme) {
        self.theme = theme
        layoutEngine.updateTheme(theme)
        cachedLayout = layoutEngine.layout(document)
        needsRedraw = true
    }

    public override func layoutSubviews() {
        super.layoutSubviews()
        metalLayer.frame = bounds
        metalLayer.drawableSize = CGSize(
            width: bounds.width * metalLayer.contentsScale,
            height: bounds.height * metalLayer.contentsScale
        )
        layoutEngine.updateContentWidth(bounds.width)
        cachedLayout = layoutEngine.layout(document)
        needsRedraw = true
    }

    @objc private func render() {
        needsRedraw = false

        // Similar rendering logic as macOS version
        guard let renderer = renderer,
              let drawable = metalLayer.nextDrawable() else { return }

        let commandBuffer = renderer.commandQueue.makeCommandBuffer()

        let passDescriptor = MTLRenderPassDescriptor()
        passDescriptor.colorAttachments[0].texture = drawable.texture
        passDescriptor.colorAttachments[0].loadAction = .clear
        passDescriptor.colorAttachments[0].storeAction = .store
        passDescriptor.colorAttachments[0].clearColor = MTLClearColor(red: 0.1, green: 0.1, blue: 0.1, alpha: 1.0)

        guard let encoder = commandBuffer?.makeRenderCommandEncoder(descriptor: passDescriptor) else { return }

        renderer.beginFrame(viewportSize: bounds.size, scrollOffset: scrollOffset)

        // TODO: Render blocks (same as macOS)

        encoder.endEncoding()
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
    }
}
#endif
