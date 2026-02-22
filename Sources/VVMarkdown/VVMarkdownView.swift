//  VVMarkdownView.swift
//  VVMarkdown
//
//  SwiftUI and AppKit views for Metal-based markdown rendering

import Foundation
import Metal
import MetalKit
import SwiftUI
import simd
import CoreText
import VVHighlighting
import VVMetalPrimitives

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

// MARK: - Text Selection Types

/// MarkdownTextPosition is now defined in Selection/VVMarkdownSelectionHelper.swift
/// and conforms to VVMetalPrimitives.VVTextPosition.
extension MarkdownTextPosition: VVMetalPrimitives.VVTextPosition {}

// MARK: - VVMarkdownView (SwiftUI)

/// SwiftUI view for rendering markdown with Metal
public struct VVMarkdownView: View {
    private let content: String
    private let theme: MarkdownTheme
    private let font: VVFont
    private let viewProvider: MarkdownViewProvider?
    private let styleRegistry: MarkdownStyleRegistry?

    @State private var scrollOffset: CGPoint = .zero

    public init(
        content: String,
        theme: MarkdownTheme = .dark,
        font: VVFont = .systemFont(ofSize: 14),
        viewProvider: MarkdownViewProvider? = nil,
        styleRegistry: MarkdownStyleRegistry? = nil
    ) {
        self.content = content
        self.theme = theme
        self.font = font
        self.viewProvider = viewProvider
        self.styleRegistry = styleRegistry
    }

    public var body: some View {
        MetalMarkdownViewRepresentable(
            content: content,
            theme: theme,
            font: font,
            viewProvider: viewProvider,
            styleRegistry: styleRegistry,
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
    let viewProvider: MarkdownViewProvider?
    let styleRegistry: MarkdownStyleRegistry?
    @Binding var scrollOffset: CGPoint

    public func makeNSView(context: Context) -> MetalMarkdownNSView {
        let view = MetalMarkdownNSView(frame: .zero, font: font, theme: theme, viewProvider: viewProvider, styleRegistry: styleRegistry)
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
    let viewProvider: MarkdownViewProvider?
    let styleRegistry: MarkdownStyleRegistry?
    @Binding var scrollOffset: CGPoint

    public func makeUIView(context: Context) -> MetalMarkdownUIView {
        let view = MetalMarkdownUIView(frame: .zero, font: font, theme: theme, viewProvider: viewProvider, styleRegistry: styleRegistry)
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

public struct MarkdownDebugOptions: OptionSet, Sendable {
    public let rawValue: Int
    public init(rawValue: Int) { self.rawValue = rawValue }

    public static let blockFrames = MarkdownDebugOptions(rawValue: 1 << 0)
    public static let textBaselines = MarkdownDebugOptions(rawValue: 1 << 1)
    public static let inlineImages = MarkdownDebugOptions(rawValue: 1 << 2)
    public static let codeGutter = MarkdownDebugOptions(rawValue: 1 << 3)
}

public class MetalMarkdownNSView: NSView {

    // Match editor coordinate system (origin at top-left).
    public override var isFlipped: Bool { true }

    // MARK: - Properties

    private var metalLayer: CAMetalLayer!
    private var renderer: MarkdownMetalRenderer?
    private var displayLink: CVDisplayLink?

    private let parser = MarkdownParser()
    private var layoutEngine: MarkdownLayoutEngine
    private var document: ParsedMarkdownDocument = .empty
    private var cachedLayout: MarkdownLayout?
    private var cachedScene = VVScene()
    private var sceneDirty: Bool = true

    private var scrollOffset: CGPoint = .zero
    private var contentHeight: CGFloat = 0
    private var needsRedraw: Bool = true
    private var currentDrawableSize: CGSize = .zero
    private var currentScaleFactor: CGFloat = 1.0

    /// Top content inset for safe area (e.g., titlebar)
    public var topInset: CGFloat = 0 {
        didSet {
            needsRedraw = true
        }
    }

    private var theme: MarkdownTheme
    private var baseFont: VVFont
    private let viewProvider: MarkdownViewProvider?
    private let styleRegistry: MarkdownStyleRegistry?

    // Code highlighting
    private let codeHighlighter: MarkdownCodeHighlighter
    private var highlightedCodeBlocks: [String: HighlightedCodeBlock] = [:]
    private var pendingHighlightTasks: Set<String> = []
    private var pendingImageTasks: Set<String> = []

    // Image loading
    private var imageLoader: MarkdownImageLoader?
    private var loadedImages: [String: MTLTexture] = [:]
    private var loadedImageSizes: [String: CGSize] = [:]

    // Math rendering
    private let mathRenderer = MarkdownMathRenderer()
    private var parsedMathBlocks: [String: RenderedMath] = [:]

    // Text selection
    private var selectionStart: MarkdownTextPosition?
    private var selectionEnd: MarkdownTextPosition?
    private var isSelecting: Bool = false
    private var selectionHelper: VVMarkdownSelectionHelper?
    private var lastDragPoint: CGPoint?
    private var selectionColor: SIMD4<Float> = .blue.withOpacity(0.4)
    private var hoveredLinkURL: String?
    private var trackingArea: NSTrackingArea?
    private var copiedBlockId: String?
    private var copiedAt: TimeInterval = 0
    private var headingAnchors: [String: CGFloat] = [:]
    public var debugOptions: MarkdownDebugOptions = [] {
        didSet { needsRedraw = true }
    }

    // MARK: - Initialization

    public init(frame: CGRect, font: VVFont, theme: MarkdownTheme, viewProvider: MarkdownViewProvider? = nil, styleRegistry: MarkdownStyleRegistry? = nil, metalContext: VVMetalContext? = nil) {
        self.baseFont = font
        self.theme = theme
        self.layoutEngine = MarkdownLayoutEngine(baseFont: font, theme: theme, contentWidth: frame.width)
        self.codeHighlighter = MarkdownCodeHighlighter(theme: .defaultDark)
        self.viewProvider = viewProvider
        self.styleRegistry = styleRegistry
        super.init(frame: frame)
        setup()
    }

    required init?(coder: NSCoder) {
        self.baseFont = .systemFont(ofSize: 14)
        self.theme = .dark
        self.layoutEngine = MarkdownLayoutEngine(baseFont: baseFont, theme: theme, contentWidth: 600)
        self.codeHighlighter = MarkdownCodeHighlighter(theme: .defaultDark)
        self.viewProvider = nil
        self.styleRegistry = nil
        super.init(coder: coder)
        setup()
    }

    private func setup() {
        wantsLayer = true
        layerContentsRedrawPolicy = .duringViewResize

        let ctx = VVMetalContext.shared
        metalLayer = CAMetalLayer()
        metalLayer.device = ctx?.device ?? MTLCreateSystemDefaultDevice()
        metalLayer.pixelFormat = .bgra8Unorm
        metalLayer.framebufferOnly = true
        metalLayer.maximumDrawableCount = 2
        metalLayer.contentsScale = NSScreen.main?.backingScaleFactor ?? 2.0
        // Keep the layer unflipped; renderer already uses a top-left projection.

        layer = metalLayer

        if let ctx {
            renderer = MarkdownMetalRenderer(context: ctx, baseFont: baseFont, scaleFactor: metalLayer.contentsScale)
            imageLoader = MarkdownImageLoader(device: ctx.device)
        }

        setupDisplayLink()
    }

    public override func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        if window != nil {
            window?.acceptsMouseMovedEvents = true
            startDisplayLink()
        } else {
            stopDisplayLink()
        }
    }

    public override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        if superview != nil && window != nil {
            startDisplayLink()
            needsRedraw = true
        }
    }

    public override func viewDidUnhide() {
        super.viewDidUnhide()
        startDisplayLink()
        needsRedraw = true
    }

    public override func viewDidHide() {
        super.viewDidHide()
        stopDisplayLink()
        metalLayer.drawableSize = CGSize(width: 1, height: 1)
    }

    public override func updateTrackingAreas() {
        super.updateTrackingAreas()
        if let trackingArea = trackingArea {
            removeTrackingArea(trackingArea)
        }
        let options: NSTrackingArea.Options = [.mouseMoved, .mouseEnteredAndExited, .activeInKeyWindow, .inVisibleRect]
        let area = NSTrackingArea(rect: bounds, options: options, owner: self, userInfo: nil)
        addTrackingArea(area)
        trackingArea = area
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
        // Don't start yet - viewDidMoveToWindow will start it when visible
        self.displayLink = displayLink
    }

    private func startDisplayLink() {
        guard let displayLink, !CVDisplayLinkIsRunning(displayLink) else { return }
        CVDisplayLinkStart(displayLink)
    }

    private func stopDisplayLink() {
        guard let displayLink, CVDisplayLinkIsRunning(displayLink) else { return }
        CVDisplayLinkStop(displayLink)
    }

    deinit {
        if let displayLink = displayLink {
            CVDisplayLinkStop(displayLink)
        }
    }

    // MARK: - Public API

    public func setContent(_ content: String) {
        document = parser.parse(content)

        // Clear stale caches from previous content
        let currentBlockIDs = Set(document.blocks.map(\.id))
        highlightedCodeBlocks = highlightedCodeBlocks.filter { currentBlockIDs.contains($0.key) }
        parsedMathBlocks = parsedMathBlocks.filter { currentBlockIDs.contains($0.key) }
        pendingHighlightTasks = pendingHighlightTasks.intersection(currentBlockIDs)

        rebuildLayout()

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
        rebuildLayout()
        mathRenderer.setMathColor(theme.mathColor)
        needsRedraw = true
    }

    private func rebuildLayout() {
        layoutEngine.updateContentWidth(bounds.width)
        layoutEngine.updateImageSizeProvider { [weak self] url in
            self?.loadedImageSizes[url]
        }
        var layout = layoutEngine.layout(document)

        for block in layout.blocks {
            switch block.content {
            case .image(let url, _, _):
                if let size = loadedImageSizes[url] {
                    layoutEngine.updateImageLayout(in: &layout, blockId: block.blockId, imageSize: size)
                }
            case .inline(let runs, let images) where runs.isEmpty && images.count == 1:
                let image = images[0]
                if let size = loadedImageSizes[image.url] {
                    layoutEngine.updateImageLayout(in: &layout, blockId: block.blockId, imageSize: size)
                }
            case .imageRow:
                if !loadedImageSizes.isEmpty {
                    layoutEngine.updateInlineImageRowLayout(in: &layout, blockId: block.blockId, imageSizes: loadedImageSizes)
                }
            default:
                break
            }
        }

        layoutEngine.adjustParagraphImageSpacing(in: &layout)

        headingAnchors = buildHeadingAnchors(from: layout)

        cachedLayout = layout
        contentHeight = layout.totalHeight
        selectionHelper = VVMarkdownSelectionHelper(layout: layout, layoutEngine: layoutEngine)
        sceneDirty = true
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
                            self.sceneDirty = true
                            self.needsRedraw = true
                        }
                    }
                }

        case .image(let url, _):
            if loadedImages[url] == nil && !pendingImageTasks.contains(url) {
                pendingImageTasks.insert(url)
                imageLoader?.loadImage(from: url) { [weak self] loadedImage in
                    guard let self = self else { return }
                    DispatchQueue.main.async {
                        self.pendingImageTasks.remove(url)
                        guard let loadedImage = loadedImage else { return }

                        self.loadedImages[url] = loadedImage.texture
                        let scaleFactor = self.imageScaleFactor(for: url)
                        let pointSize = CGSize(
                            width: loadedImage.size.width / scaleFactor,
                            height: loadedImage.size.height / scaleFactor
                        )
                        self.loadedImageSizes[url] = pointSize
                        // Rebuild layout to apply actual image sizes (including inline images).
                        self.rebuildLayout()
                        self.needsRedraw = true
                    }
                }
            }

        case .paragraph(let content):
            let inlineImages = extractInlineImages(from: content)
            let isImageRow = !(extractInlineImageRowElements(from: content).isEmpty)
            for image in inlineImages {
                enqueueInlineImageLoad(url: image.url, blockId: block.id, isImageRow: isImageRow)
            }

        case .list(let items, _, _):
            processInlineImages(in: items)

        case .table(let rows, _):
            processInlineImages(in: rows)

        case .mathBlock(let latex):
            if !parsedMathBlocks.keys.contains(block.id) {
                let parsed = mathRenderer.parse(latex: latex, isBlock: true)
                parsedMathBlocks[block.id] = parsed
            }

        case .blockQuote(let nested):
            for nestedBlock in nested {
                processBlock(nestedBlock)
            }
        case .alert(_, let nested):
            for nestedBlock in nested {
                processBlock(nestedBlock)
            }

        default:
            break
        }
    }

    private func extractInlineImageRowElements(from content: MarkdownInlineContent) -> [(url: String, linkURL: String?)] {
        func extract(from content: MarkdownInlineContent) -> [(url: String, linkURL: String?)]? {
            var images: [(url: String, linkURL: String?)] = []

            for element in content.elements {
                switch element {
                case .image(let url, _, _):
                    images.append((url, nil))

                case .link(let linkContent, let linkURL, _):
                    guard let linkImages = extract(from: linkContent) else {
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

        return extract(from: content) ?? []
    }

    private func extractInlineImages(from content: MarkdownInlineContent) -> [(url: String, linkURL: String?)] {
        var images: [(url: String, linkURL: String?)] = []

        func walk(_ content: MarkdownInlineContent, linkURL: String?) {
            for element in content.elements {
                switch element {
                case .image(let url, _, _):
                    images.append((url, linkURL))
                case .link(let childContent, let url, _):
                    walk(childContent, linkURL: url)
                case .strong(let childContent),
                     .emphasis(let childContent),
                     .strikethrough(let childContent):
                    walk(childContent, linkURL: linkURL)
                default:
                    continue
                }
            }
        }

        walk(content, linkURL: nil)
        return images
    }

    private func processInlineImages(in items: [MarkdownListItem]) {
        for item in items {
            let images = extractInlineImages(from: item.content)
            for image in images {
                enqueueInlineImageLoad(url: image.url, blockId: nil, isImageRow: false)
            }
            processInlineImages(in: item.children)
        }
    }

    private func processInlineImages(in rows: [MarkdownTableRow]) {
        for row in rows {
            for cell in row.cells {
                let images = extractInlineImages(from: cell)
                for image in images {
                    enqueueInlineImageLoad(url: image.url, blockId: nil, isImageRow: false)
                }
            }
        }
    }

    private func enqueueInlineImageLoad(url: String, blockId: String?, isImageRow: Bool) {
        if loadedImages[url] != nil || pendingImageTasks.contains(url) { return }
        pendingImageTasks.insert(url)
        imageLoader?.loadImage(from: url) { [weak self] loadedImage in
            guard let self = self else { return }
            DispatchQueue.main.async {
                self.pendingImageTasks.remove(url)
                guard let loadedImage = loadedImage else { return }

                self.loadedImages[url] = loadedImage.texture
                let scaleFactor = self.imageScaleFactor(for: url)
                let pointSize = CGSize(
                    width: loadedImage.size.width / scaleFactor,
                    height: loadedImage.size.height / scaleFactor
                )
                self.loadedImageSizes[url] = pointSize

                if isImageRow, let blockId = blockId, var layout = self.cachedLayout {
                    self.layoutEngine.updateInlineImageRowLayout(in: &layout, blockId: blockId, imageSizes: self.loadedImageSizes)
                    self.cachedLayout = layout
                    self.sceneDirty = true
                } else {
                    self.rebuildLayout()
                }

                self.needsRedraw = true
            }
        }
    }

    private func imageScaleFactor(for url: String) -> CGFloat {
        let lower = url.lowercased()
        if lower.contains(".svg") || lower.contains("image/svg+xml") {
            return 1.0
        }
        return metalLayer.contentsScale
    }

    // MARK: - Layout

    public override func layout() {
        super.layout()
        metalLayer.frame = bounds
        rebuildLayout()
        needsRedraw = true
    }

    // MARK: - Scrolling

    public override func scrollWheel(with event: NSEvent) {
        let maxScrollY = max(0, contentHeight + topInset - bounds.height)
        scrollOffset.y = max(0, min(maxScrollY, scrollOffset.y - event.scrollingDeltaY))
        scrollOffset.x = max(0, scrollOffset.x - event.scrollingDeltaX)
        needsRedraw = true
    }

    // MARK: - Mouse Events & Selection

    public override var acceptsFirstResponder: Bool { true }

    private func contentPoint(from point: CGPoint) -> CGPoint {
        if isFlipped {
            return CGPoint(
                x: point.x + scrollOffset.x,
                y: point.y + scrollOffset.y - topInset
            )
        }
        return CGPoint(
            x: point.x + scrollOffset.x,
            y: bounds.height - point.y + scrollOffset.y - topInset
        )
    }

    public override func mouseDown(with event: NSEvent) {
        window?.makeFirstResponder(self)
        let point = convert(event.locationInWindow, from: nil)
        lastDragPoint = point
        let contentPoint = contentPoint(from: point)

        if copyCodeBlock(at: contentPoint) {
            selectionStart = nil
            selectionEnd = nil
            isSelecting = false
            return
        }

        selectionStart = selectionHelper?.nearestTextPosition(to: contentPoint)
        selectionEnd = selectionStart
        isSelecting = true
        NSCursor.iBeam.set()
        needsRedraw = true
    }

    public override func mouseDragged(with event: NSEvent) {
        guard isSelecting else { return }

        let point = convert(event.locationInWindow, from: nil)
        lastDragPoint = point
        autoscrollForDrag(point)
        let contentPoint = contentPoint(from: point)

        selectionEnd = selectionHelper?.nearestTextPosition(to: contentPoint) ?? selectionEnd
        NSCursor.iBeam.set()
        needsRedraw = true
    }

    public override func mouseUp(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        lastDragPoint = nil
        let contentPoint = contentPoint(from: point)

        if copyCodeBlock(at: contentPoint) {
            isSelecting = false
            return
        }

        if let url = linkURL(at: contentPoint) {
            if let start = selectionStart, let end = selectionEnd, !(start < end) && !(end < start) {
                openLink(url)
                isSelecting = false
                return
            } else if selectionStart == nil && selectionEnd == nil {
                openLink(url)
                isSelecting = false
                return
            }
        }

        if let start = selectionStart, let end = selectionEnd {
            let isCollapsed = !(start < end) && !(end < start)
            if isCollapsed {
                if let url = linkURL(at: contentPoint) { openLink(url) }
            }
        }

        isSelecting = false
        if linkURL(at: contentPoint) != nil {
            NSCursor.pointingHand.set()
        } else {
            NSCursor.iBeam.set()
        }
    }

    public override func mouseMoved(with event: NSEvent) {
        let point = convert(event.locationInWindow, from: nil)
        let contentPoint = contentPoint(from: point)
        let url = linkURL(at: contentPoint)
        if url != hoveredLinkURL {
            hoveredLinkURL = url
            sceneDirty = true
            needsRedraw = true
        }
        if url != nil {
            NSCursor.pointingHand.set()
        } else {
            NSCursor.iBeam.set()
        }
    }

    public override func mouseExited(with event: NSEvent) {
        if hoveredLinkURL != nil {
            hoveredLinkURL = nil
            sceneDirty = true
            needsRedraw = true
        }
        NSCursor.arrow.set()
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
        guard let helper = selectionHelper else { return }

        selectionStart = helper.findFirstPosition()
        selectionEnd = helper.findLastPosition()
        needsRedraw = true
    }

    private func buildHeadingAnchors(from layout: MarkdownLayout) -> [String: CGFloat] {
        var anchors: [String: CGFloat] = [:]
        var counts: [String: Int] = [:]
        for block in layout.blocks {
            guard case .heading = block.blockType else { continue }
            let text = extractPlainText(from: block).trimmingCharacters(in: .whitespacesAndNewlines)
            guard !text.isEmpty else { continue }
            let slug = slugify(text)
            let count = counts[slug, default: 0] + 1
            counts[slug] = count
            let key = count == 1 ? slug : "\(slug)-\(count)"
            anchors[key] = block.frame.minY
        }
        return anchors
    }

    private func extractPlainText(from block: LayoutBlock) -> String {
        switch block.content {
        case .text(let runs):
            return runs.map { $0.text }.joined()
        case .inline(let runs, _):
            return runs.map { $0.text }.joined()
        default:
            return ""
        }
    }

    private func slugify(_ text: String) -> String {
        let lower = text.lowercased()
        var slug = ""
        var lastWasDash = false
        for scalar in lower.unicodeScalars {
            let isAlnum = CharacterSet.alphanumerics.contains(scalar)
            if isAlnum {
                slug.unicodeScalars.append(scalar)
                lastWasDash = false
            } else {
                if !lastWasDash {
                    slug.append("-")
                    lastWasDash = true
                }
            }
        }
        while slug.hasPrefix("-") { slug.removeFirst() }
        while slug.hasSuffix("-") { slug.removeLast() }
        return slug
    }


    private func copySelection() {
        guard let start = selectionStart, let end = selectionEnd, let helper = selectionHelper else { return }

        let selectedText = helper.extractText(from: start, to: end)
        if !selectedText.isEmpty {
            NSPasteboard.general.clearContents()
            NSPasteboard.general.setString(selectedText, forType: .string)
        }
    }

    private func glyphRect(for glyph: LayoutGlyph) -> CGRect {
        if let renderer = renderer,
           let cached = cachedGlyph(for: glyph, renderer: renderer) {
            return CGRect(
                x: glyph.position.x + cached.bearing.x,
                y: glyph.position.y + cached.bearing.y,
                width: cached.size.width,
                height: cached.size.height
            )
        }

        return CGRect(
            x: glyph.position.x,
            y: glyph.position.y,
            width: glyph.size.width,
            height: glyph.size.height
        )
    }

    private func toVVFontVariant(_ variant: FontVariant) -> VVFontVariant {
        switch variant {
        case .regular: return .regular
        case .semibold: return .semibold
        case .semiboldItalic: return .semiboldItalic
        case .bold: return .bold
        case .italic: return .italic
        case .boldItalic: return .boldItalic
        case .monospace: return .monospace
        case .emoji: return .emoji
        }
    }

    private func toVVTextRunStyle(_ style: TextRunStyle) -> VVTextRunStyle {
        VVTextRunStyle(
            isStrikethrough: style.isStrikethrough,
            isLink: style.isLink,
            linkURL: style.linkURL,
            color: style.color
        )
    }

    private func toVVTextGlyph(_ glyph: LayoutGlyph) -> VVTextGlyph {
        VVTextGlyph(
            glyphID: UInt16(glyph.glyphID),
            position: glyph.position,
            size: glyph.size,
            color: glyph.color,
            fontVariant: toVVFontVariant(glyph.fontVariant),
            fontSize: glyph.fontSize,
            fontName: glyph.fontName,
            stringIndex: glyph.stringIndex
        )
    }

    private func runFont(for run: LayoutTextRun) -> CTFont? {
        let baseSize = layoutEngine.baseFontSize
        let runFontSize: CGFloat
        if let runLineHeight = run.lineHeight, runLineHeight > 0 {
            runFontSize = max(1, baseSize * (runLineHeight / max(1, layoutEngine.currentLineHeight)))
        } else {
            runFontSize = baseSize
        }
        let variant: FontVariant
        if run.style.isCode { variant = .monospace }
        else if run.style.isBold && run.style.isItalic { variant = .boldItalic }
        else if run.style.isBold { variant = .bold }
        else if let override = run.style.fontVariant {
            if override == .semibold && run.style.isItalic { variant = .semiboldItalic }
            else { variant = override }
        }
        else if run.style.isItalic { variant = .italic }
        else { variant = .regular }
        guard let baseFont = layoutEngine.font(for: variant) else { return nil }
        return CTFontCreateCopyWithAttributes(baseFont, runFontSize, nil, nil)
    }

    private func autoscrollForDrag(_ point: CGPoint) {
        let maxScrollY = max(0, contentHeight + topInset - bounds.height)
        let maxScrollX = max(0, (cachedLayout?.contentWidth ?? bounds.width) - bounds.width)
        var newOffset = scrollOffset

        if point.y < 0 {
            let speed = min(60, max(4, abs(point.y) * 0.35))
            newOffset.y = max(0, newOffset.y - speed)
        } else if point.y > bounds.height {
            let speed = min(60, max(4, (point.y - bounds.height) * 0.35))
            newOffset.y = min(maxScrollY, newOffset.y + speed)
        }

        if point.x < 0 {
            let speed = min(40, max(3, abs(point.x) * 0.25))
            newOffset.x = max(0, newOffset.x - speed)
        } else if point.x > bounds.width {
            let speed = min(40, max(3, (point.x - bounds.width) * 0.25))
            newOffset.x = min(maxScrollX, newOffset.x + speed)
        }

        if newOffset.x != scrollOffset.x || newOffset.y != scrollOffset.y {
            scrollOffset = newOffset
            needsRedraw = true
        }
    }


    private func linkURL(at point: CGPoint) -> String? {
        guard let layout = cachedLayout else { return nil }

        for block in layout.blocks {
            if let url = linkURL(in: block, point: point) {
                return url
            }
        }

        return nil
    }

    private func linkURL(in block: LayoutBlock, point: CGPoint) -> String? {
        switch block.content {
        case .text(let runs):
            return linkURL(in: runs, point: point)
        case .inline(let runs, let images):
            if let url = linkURL(in: runs, point: point) { return url }
            for image in images {
                if let linkURL = image.linkURL, !linkURL.isEmpty, image.frame.contains(point) {
                    return linkURL
                }
            }
        case .listItems(let items):
            return linkURL(in: items, point: point)
        case .quoteBlocks(let blocks):
            for nested in blocks {
                if let url = linkURL(in: nested, point: point) { return url }
            }
        case .tableRows(let rows):
            for row in rows {
                for cell in row.cells {
                    if let url = linkURL(in: cell.textRuns, point: point) { return url }
                    for image in cell.inlineImages {
                        if let linkURL = image.linkURL, !linkURL.isEmpty, image.frame.contains(point) {
                            return linkURL
                        }
                    }
                }
            }
        case .definitionList(let items):
            for item in items {
                if let url = linkURL(in: item.termRuns, point: point) { return url }
                for image in item.termImages {
                    if let linkURL = image.linkURL, !linkURL.isEmpty, image.frame.contains(point) {
                        return linkURL
                    }
                }
                for (index, runs) in item.definitionRuns.enumerated() {
                    if let url = linkURL(in: runs, point: point) { return url }
                    let images = index < item.definitionImages.count ? item.definitionImages[index] : []
                    for image in images {
                        if let linkURL = image.linkURL, !linkURL.isEmpty, image.frame.contains(point) {
                            return linkURL
                        }
                    }
                }
            }
        case .abbreviationList(let items):
            for item in items {
                if let url = linkURL(in: item.runs, point: point) { return url }
                for image in item.images {
                    if let linkURL = image.linkURL, !linkURL.isEmpty, image.frame.contains(point) {
                        return linkURL
                    }
                }
            }
        case .imageRow(let images):
            for image in images {
                if let linkURL = image.linkURL, !linkURL.isEmpty, image.frame.contains(point) {
                    return linkURL
                }
            }
        default:
            break
        }

        return nil
    }

    private func linkURL(in items: [LayoutListItem], point: CGPoint) -> String? {
        for item in items {
            if let url = linkURL(in: item.contentRuns, point: point) { return url }
            for image in item.inlineImages {
                if let linkURL = image.linkURL, !linkURL.isEmpty, image.frame.contains(point) {
                    return linkURL
                }
            }
            if let url = linkURL(in: item.children, point: point) { return url }
        }
        return nil
    }

    private func linkURL(in runs: [LayoutTextRun], point: CGPoint) -> String? {
        for run in runs where run.style.isLink {
            guard let url = run.style.linkURL else { continue }
            let baseBounds = selectionHelper?.runSelectionBounds(run) ?? selectionHelper?.runLineBounds(run) ?? selectionHelper?.runHitBounds(run)
            guard let bounds = baseBounds else { continue }
            let hitPadY = max(2, bounds.height * 0.18)
            let hitBounds = bounds.insetBy(dx: -3, dy: -hitPadY)
            if hitBounds.contains(point) {
                return url
            }
        }
        return nil
    }

    private func copyCodeBlock(at point: CGPoint) -> Bool {
        guard let layout = cachedLayout else { return false }
        let headerHeight = CGFloat(theme.codeBlockHeaderHeight)
        guard headerHeight > 0 else { return false }

        for block in layout.blocks {
            guard case .code(let code, _, _) = block.content else { continue }
            guard let buttonRect = codeCopyButtonRect(for: block.frame, headerHeight: headerHeight) else { continue }
            if buttonRect.insetBy(dx: -8, dy: -8).contains(point) {
                NSPasteboard.general.clearContents()
                NSPasteboard.general.setString(code, forType: .string)
                copiedBlockId = block.blockId
                copiedAt = Date.timeIntervalSinceReferenceDate
                sceneDirty = true
                needsRedraw = true
                let blockId = block.blockId
                DispatchQueue.main.asyncAfter(deadline: .now() + 1.4) { [weak self] in
                    guard let self = self else { return }
                    if self.copiedBlockId == blockId {
                        self.copiedBlockId = nil
                        self.sceneDirty = true
                        self.needsRedraw = true
                    }
                }
                return true
            }
        }

        return false
    }

    private func codeCopyButtonRect(for frame: CGRect, headerHeight: CGFloat) -> CGRect? {
        let borderWidth = CGFloat(theme.codeBorderWidth)
        let paddingX: CGFloat = 12
        let iconSize: CGFloat = 14
        let iconX = frame.maxX - borderWidth - paddingX - iconSize
        let iconY = frame.origin.y + borderWidth + (headerHeight - iconSize) * 0.5
        return CGRect(x: iconX - 4, y: iconY - 4, width: iconSize + 8, height: iconSize + 8)
    }

    private func openLink(_ urlString: String) {
        guard !urlString.isEmpty else { return }
        if urlString.hasPrefix("#") {
            let rawAnchor = String(urlString.dropFirst())
            let decoded = rawAnchor.removingPercentEncoding ?? rawAnchor
            let trimmed = decoded.trimmingCharacters(in: .whitespacesAndNewlines)
            let anchor = trimmed.hasPrefix("#") ? String(trimmed.dropFirst()) : trimmed
            if let target = headingAnchors[anchor] ?? headingAnchors[slugify(anchor)] {
                let targetY = max(0, target - CGFloat(theme.contentPadding))
                scrollOffset.y = min(max(0, targetY), max(0, contentHeight - bounds.height))
                needsRedraw = true
            }
            return
        }
        guard let url = URL(string: urlString) else { return }
        #if canImport(AppKit)
        NSWorkspace.shared.open(url)
        #else
        UIApplication.shared.open(url, options: [:], completionHandler: nil)
        #endif
    }

    // MARK: - Scene Construction

    private func rebuildSceneIfNeeded() {
        guard sceneDirty, let layout = cachedLayout else {
            if cachedLayout == nil {
                cachedScene = VVScene()
            }
            return
        }
        cachedScene = buildScene(from: layout)
        sceneDirty = false
    }

    private func buildScene(from layout: MarkdownLayout) -> VVScene {
        let helper = selectionHelper
        let pipeline = VVMarkdownRenderPipeline(
            theme: theme,
            layoutEngine: layoutEngine,
            scale: currentScaleFactor,
            viewProvider: viewProvider,
            styleRegistry: styleRegistry,
            highlightedCodeBlocks: highlightedCodeBlocks,
            copiedBlockId: copiedBlockId,
            copiedAt: copiedAt,
            runLineBounds: { run in helper?.runLineBounds(run) },
            runRenderedBounds: { run in helper?.runRenderedBounds(run) },
            runBounds: { run in helper?.runLineBounds(run) },
            runVisualBounds: { run in helper?.runVisualBounds(run) },
            lineMetrics: { run in
                guard let m = helper?.lineMetrics(for: run) else { return nil }
                return (m.line, m.length, m.originX, m.lineY, m.lineHeight, m.baseline, m.ascent, m.descent, m.lineWidth)
            },
            runFont: { [weak self] run in self?.runFont(for: run) }
        )
        return pipeline.buildScene(from: layout)
    }

    // MARK: - Rendering

    private func render() {
        needsRedraw = false

        // Validate drawable size before every render — self-corrects after release
        guard window != nil, bounds.width > 0, bounds.height > 0 else { return }
        let scale = metalLayer.contentsScale
        let expectedW = max(1, bounds.width * scale)
        let expectedH = max(1, bounds.height * scale)
        if abs(metalLayer.drawableSize.width - expectedW) > 0.5
            || abs(metalLayer.drawableSize.height - expectedH) > 0.5 {
            metalLayer.drawableSize = CGSize(width: expectedW, height: expectedH)
        }

        if isSelecting, let dragPoint = lastDragPoint {
            let beforeOffset = scrollOffset
            autoscrollForDrag(dragPoint)
            let contentPoint = contentPoint(from: dragPoint)
            let newEnd = selectionHelper?.nearestTextPosition(to: contentPoint)
            if newEnd != selectionEnd {
                selectionEnd = newEnd
                needsRedraw = true
            }
            if beforeOffset.x != scrollOffset.x || beforeOffset.y != scrollOffset.y {
                needsRedraw = true
            }
        }

        guard let renderer = renderer,
              let drawable = metalLayer.nextDrawable(),
              let markdownLayout = cachedLayout else { return }

        let commandBuffer = renderer.commandQueue.makeCommandBuffer()
        currentDrawableSize = CGSize(width: drawable.texture.width, height: drawable.texture.height)
        currentScaleFactor = metalLayer.contentsScale

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

        // Apply topInset to push content down below safe area
        let adjustedScrollOffset = CGPoint(x: scrollOffset.x, y: scrollOffset.y - topInset)
        renderer.beginFrame(viewportSize: bounds.size, scrollOffset: adjustedScrollOffset)

        rebuildSceneIfNeeded()
        renderScene(cachedScene, encoder: encoder, renderer: renderer)

        // Render selection highlights on top so they are visible over block backgrounds.
        renderSelectionHighlights(encoder: encoder, renderer: renderer)

        if !debugOptions.isEmpty {
            renderDebugOverlay(markdownLayout, encoder: encoder, renderer: renderer)
        }

        encoder.endEncoding()
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
    }

    private func renderSelectionHighlights(encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        guard let start = selectionStart, let end = selectionEnd, let helper = selectionHelper else { return }
        let rects = helper.selectionRects(from: start, to: end)
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

    private func renderScene(_ scene: VVScene, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        var currentClip: CGRect? = nil
        var glyphInstances: [Int: [MarkdownGlyphInstance]] = [:]
        var colorGlyphInstances: [Int: [MarkdownGlyphInstance]] = [:]
        var underlines: [LineInstance] = []
        var strikethroughs: [LineInstance] = []

        func flushTextBatches() {
            if !glyphInstances.isEmpty || !colorGlyphInstances.isEmpty {
                renderGlyphBatches(glyphInstances, encoder: encoder, renderer: renderer, isColor: false)
                renderGlyphBatches(colorGlyphInstances, encoder: encoder, renderer: renderer, isColor: true)
            }
            if !underlines.isEmpty, let buffer = renderer.makeBuffer(for: underlines) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: underlines.count)
            }
            if !strikethroughs.isEmpty, let buffer = renderer.makeBuffer(for: strikethroughs) {
                renderer.renderStrikethroughs(encoder: encoder, instances: buffer, instanceCount: strikethroughs.count)
            }
            glyphInstances.removeAll(keepingCapacity: true)
            colorGlyphInstances.removeAll(keepingCapacity: true)
            underlines.removeAll(keepingCapacity: true)
            strikethroughs.removeAll(keepingCapacity: true)
        }

        func updateClip(_ clip: CGRect?) {
            if clip != currentClip {
                flushTextBatches()
                if let clip {
                    encoder.setScissorRect(scissorRect(for: clip))
                } else {
                    encoder.setScissorRect(fullScissorRect())
                }
                currentClip = clip
            }
        }

        for primitive in scene.orderedPrimitives() {
            updateClip(primitive.clipRect)
            switch primitive.kind {
            case .textRun(let run):
                appendTextPrimitive(run, renderer: renderer, glyphInstances: &glyphInstances, colorGlyphInstances: &colorGlyphInstances, underlines: &underlines, strikethroughs: &strikethroughs)
            default:
                flushTextBatches()
                renderPrimitive(primitive, encoder: encoder, renderer: renderer)
            }
        }

        flushTextBatches()
        updateClip(nil)
    }

    private func renderPrimitive(_ primitive: VVPrimitive, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        switch primitive.kind {
        case .quad(let quad):
            let instance = QuadInstance(
                position: SIMD2<Float>(Float(quad.frame.origin.x), Float(quad.frame.origin.y)),
                size: SIMD2<Float>(Float(quad.frame.width), Float(quad.frame.height)),
                color: quad.color,
                cornerRadius: Float(quad.cornerRadius)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 1, rounded: quad.cornerRadius > 0)
            }

        case .gradientQuad(let quad):
            renderGradientQuad(quad, encoder: encoder, renderer: renderer)

        case .line(let line):
            let minX = min(line.start.x, line.end.x)
            let minY = min(line.start.y, line.end.y)
            let width = abs(line.end.x - line.start.x)
            let height = abs(line.end.y - line.start.y)
            let rectWidth = width > 0 ? width : line.thickness
            let rectHeight = height > 0 ? height : line.thickness
            let instance = LineInstance(
                position: SIMD2<Float>(Float(minX), Float(minY)),
                width: Float(rectWidth),
                height: Float(rectHeight),
                color: line.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .bullet(let bullet):
            switch bullet.type {
            case .disc, .circle, .square:
                let bulletType: UInt32
                switch bullet.type {
                case .disc: bulletType = 0
                case .circle: bulletType = 1
                case .square: bulletType = 2
                default: bulletType = 0
                }
                let instance = BulletInstance(
                    position: SIMD2<Float>(Float(bullet.position.x), Float(bullet.position.y)),
                    size: SIMD2<Float>(Float(bullet.size), Float(bullet.size)),
                    color: bullet.color,
                    bulletType: bulletType
                )
                if let buffer = renderer.makeBuffer(for: [instance]) {
                    renderer.renderBullets(encoder: encoder, instances: buffer, instanceCount: 1)
                }
            case .checkbox(let checked):
                let instance = CheckboxInstance(
                    position: SIMD2<Float>(Float(bullet.position.x), Float(bullet.position.y)),
                    size: SIMD2<Float>(Float(bullet.size), Float(bullet.size)),
                    color: bullet.color,
                    isChecked: checked
                )
                if let buffer = renderer.makeBuffer(for: [instance]) {
                    renderer.renderCheckboxes(encoder: encoder, instances: buffer, instanceCount: 1)
                }
            case .number:
                break
            }

        case .image(let image):
            if let texture = loadedImages[image.url] {
                let instance = ImageRenderInstance(
                    position: SIMD2<Float>(Float(image.frame.origin.x), Float(image.frame.origin.y)),
                    size: SIMD2<Float>(Float(image.frame.width), Float(image.frame.height)),
                    cornerRadius: Float(image.cornerRadius)
                )
                if let buffer = renderer.makeBuffer(for: [instance]) {
                    renderer.renderImages(encoder: encoder, instances: buffer, instanceCount: 1, texture: texture)
                }
            } else {
                let borderColor: SIMD4<Float> = .gray(0.35)
                let background: SIMD4<Float> = .gray(0.12)
                let border = QuadInstance(
                    position: SIMD2<Float>(Float(image.frame.origin.x), Float(image.frame.origin.y)),
                    size: SIMD2<Float>(Float(image.frame.width), Float(image.frame.height)),
                    color: borderColor,
                    cornerRadius: Float(image.cornerRadius)
                )
                let innerFrame = image.frame.insetBy(dx: 1, dy: 1)
                let fill = QuadInstance(
                    position: SIMD2<Float>(Float(innerFrame.origin.x), Float(innerFrame.origin.y)),
                    size: SIMD2<Float>(Float(innerFrame.width), Float(innerFrame.height)),
                    color: background,
                    cornerRadius: Float(max(0, image.cornerRadius - 1))
                )
                if let buffer = renderer.makeBuffer(for: [border, fill]) {
                    renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: 2, rounded: true)
                }
            }

        case .blockQuoteBorder(let border):
            let instance = BlockQuoteBorderInstance(
                position: SIMD2<Float>(Float(border.frame.origin.x), Float(border.frame.origin.y)),
                size: SIMD2<Float>(Float(border.frame.width), Float(border.frame.height)),
                color: border.color,
                borderWidth: Float(border.borderWidth)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderBlockQuoteBorders(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .tableLine(let line):
            let instance = TableGridLineInstance(
                start: SIMD2<Float>(Float(line.start.x), Float(line.start.y)),
                end: SIMD2<Float>(Float(line.end.x), Float(line.end.y)),
                color: line.color,
                lineWidth: Float(line.lineWidth)
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderTableGrid(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .pieSlice(let slice):
            let instance = PieSliceInstance(
                center: SIMD2<Float>(Float(slice.center.x), Float(slice.center.y)),
                radius: Float(slice.radius),
                startAngle: Float(slice.startAngle),
                endAngle: Float(slice.endAngle),
                color: slice.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderPieSlices(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .textRun:
            break

        case .underline(let underline):
            let minX = underline.origin.x
            let y = underline.origin.y
            let instance = LineInstance(
                position: SIMD2<Float>(Float(minX), Float(y)),
                width: Float(underline.width),
                height: Float(underline.thickness),
                color: underline.color
            )
            if let buffer = renderer.makeBuffer(for: [instance]) {
                renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: 1)
            }

        case .path:
            break
        }
    }

    private func renderGradientQuad(
        _ gradient: VVGradientQuadPrimitive,
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer
    ) {
        let stepCount = max(2, min(36, gradient.steps))
        let frame = gradient.frame.integral
        guard frame.width > 0, frame.height > 0 else { return }

        var instances: [QuadInstance] = []
        instances.reserveCapacity(stepCount)

        switch gradient.direction {
        case .horizontal:
            let segmentWidth = frame.width / CGFloat(stepCount)
            for index in 0..<stepCount {
                let t = stepCount <= 1 ? Float(0) : Float(index) / Float(stepCount - 1)
                let x = frame.minX + CGFloat(index) * segmentWidth
                let width = index == stepCount - 1 ? max(0, frame.maxX - x) : segmentWidth + 0.75
                guard width > 0 else { continue }
                let cornerRadius = (index == 0 || index == stepCount - 1) ? gradient.cornerRadius : 0
                instances.append(
                    QuadInstance(
                        position: SIMD2<Float>(Float(x), Float(frame.minY)),
                        size: SIMD2<Float>(Float(width), Float(frame.height)),
                        color: lerpColor(gradient.startColor, gradient.endColor, t: t),
                        cornerRadius: Float(cornerRadius)
                    )
                )
            }

        case .vertical:
            let segmentHeight = frame.height / CGFloat(stepCount)
            for index in 0..<stepCount {
                let t = stepCount <= 1 ? Float(0) : Float(index) / Float(stepCount - 1)
                let y = frame.minY + CGFloat(index) * segmentHeight
                let height = index == stepCount - 1 ? max(0, frame.maxY - y) : segmentHeight + 0.75
                guard height > 0 else { continue }
                let cornerRadius = (index == 0 || index == stepCount - 1) ? gradient.cornerRadius : 0
                instances.append(
                    QuadInstance(
                        position: SIMD2<Float>(Float(frame.minX), Float(y)),
                        size: SIMD2<Float>(Float(frame.width), Float(height)),
                        color: lerpColor(gradient.startColor, gradient.endColor, t: t),
                        cornerRadius: Float(cornerRadius)
                    )
                )
            }
        }

        guard !instances.isEmpty, let buffer = renderer.makeBuffer(for: instances) else { return }
        renderer.renderQuads(encoder: encoder, instances: buffer, instanceCount: instances.count, rounded: gradient.cornerRadius > 0)
    }

    private func lerpColor(_ start: SIMD4<Float>, _ end: SIMD4<Float>, t: Float) -> SIMD4<Float> {
        let clamped = max(0, min(1, t))
        return start + (end - start) * clamped
    }

    private func appendTextPrimitive(
        _ run: VVTextRunPrimitive,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]],
        underlines: inout [LineInstance],
        strikethroughs: inout [LineInstance]
    ) {
        for glyph in run.glyphs {
            appendGlyphInstance(glyph, renderer: renderer, glyphInstances: &glyphInstances, colorGlyphInstances: &colorGlyphInstances)
        }

        let baseSize = layoutEngine.baseFontSize
        let scale = baseSize > 0 ? run.fontSize / baseSize : 1
        let ascent = layoutEngine.currentAscent * scale
        let descent = layoutEngine.currentDescent * scale
        let glyphMinX = run.glyphs.map { $0.position.x }.min() ?? run.position.x
        let glyphMaxX = run.glyphs.map { $0.position.x + $0.size.width }.max() ?? run.position.x
        let fallbackBounds = run.runBounds ?? run.lineBounds
        let underlineStartX = fallbackBounds?.minX ?? glyphMinX
        let underlineWidth = max(0, fallbackBounds?.width ?? (glyphMaxX - glyphMinX))

        if run.style.isLink, let url = run.style.linkURL, url == hoveredLinkURL {
            let underlineY = run.position.y + max(1, descent * 0.6)
            underlines.append(LineInstance(
                position: SIMD2<Float>(Float(underlineStartX), Float(underlineY)),
                width: Float(underlineWidth),
                height: 1,
                color: run.style.color
            ))
        }

        if run.style.isStrikethrough {
            let strikeY = run.position.y - max(1, ascent * 0.35)
            strikethroughs.append(LineInstance(
                position: SIMD2<Float>(Float(underlineStartX), Float(strikeY)),
                width: Float(underlineWidth),
                height: 1,
                color: run.style.color
            ))
        }
    }

    private func cachedGlyph(for glyph: LayoutGlyph, renderer: MarkdownMetalRenderer) -> MarkdownCachedGlyph? {
        if let fontName = glyph.fontName {
            return renderer.glyphAtlas.glyph(for: glyph.glyphID, fontName: fontName, fontSize: glyph.fontSize, variant: glyph.fontVariant)
        }
        return renderer.glyphAtlas.glyph(for: glyph.glyphID, variant: glyph.fontVariant, fontSize: glyph.fontSize, baseFont: renderer.baseFont)
    }

    private func toLayoutFontVariant(_ variant: VVFontVariant) -> FontVariant {
        switch variant {
        case .regular: return .regular
        case .semibold: return .semibold
        case .semiboldItalic: return .semiboldItalic
        case .bold: return .bold
        case .italic: return .italic
        case .boldItalic: return .boldItalic
        case .monospace: return .monospace
        case .emoji: return .emoji
        }
    }

    private func cachedGlyph(for glyph: VVTextGlyph, renderer: MarkdownMetalRenderer) -> MarkdownCachedGlyph? {
        let layoutVariant = toLayoutFontVariant(glyph.fontVariant)
        let cgGlyph = CGGlyph(glyph.glyphID)
        if let fontName = glyph.fontName {
            return renderer.glyphAtlas.glyph(for: cgGlyph, fontName: fontName, fontSize: glyph.fontSize, variant: layoutVariant)
        }
        return renderer.glyphAtlas.glyph(for: cgGlyph, variant: layoutVariant, fontSize: glyph.fontSize, baseFont: renderer.baseFont)
    }

    private func appendGlyphInstance(
        _ glyph: LayoutGlyph,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]]
    ) {
        guard let cached = cachedGlyph(for: glyph, renderer: renderer) else { return }
        let glyphColor = cached.isColor ? SIMD4<Float>(1, 1, 1, glyph.color.w) : glyph.color
        let instance = MarkdownGlyphInstance(
            position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x), Float(glyph.position.y + cached.bearing.y)),
            size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
            uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
            uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
            color: glyphColor,
            atlasIndex: UInt32(cached.atlasIndex)
        )

        if cached.isColor {
            colorGlyphInstances[cached.atlasIndex, default: []].append(instance)
        } else {
            glyphInstances[cached.atlasIndex, default: []].append(instance)
        }
    }

    private func appendGlyphInstance(
        _ glyph: VVTextGlyph,
        renderer: MarkdownMetalRenderer,
        glyphInstances: inout [Int: [MarkdownGlyphInstance]],
        colorGlyphInstances: inout [Int: [MarkdownGlyphInstance]]
    ) {
        guard let cached = cachedGlyph(for: glyph, renderer: renderer) else { return }
        let glyphColor = cached.isColor ? SIMD4<Float>(1, 1, 1, glyph.color.w) : glyph.color
        let instance = MarkdownGlyphInstance(
            position: SIMD2<Float>(Float(glyph.position.x + cached.bearing.x), Float(glyph.position.y + cached.bearing.y)),
            size: SIMD2<Float>(Float(cached.size.width), Float(cached.size.height)),
            uvOrigin: SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y)),
            uvSize: SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height)),
            color: glyphColor,
            atlasIndex: UInt32(cached.atlasIndex)
        )

        if cached.isColor {
            colorGlyphInstances[cached.atlasIndex, default: []].append(instance)
        } else {
            glyphInstances[cached.atlasIndex, default: []].append(instance)
        }
    }

    private func renderGlyphBatches(
        _ batches: [Int: [MarkdownGlyphInstance]],
        encoder: MTLRenderCommandEncoder,
        renderer: MarkdownMetalRenderer,
        isColor: Bool
    ) {
        guard !batches.isEmpty else { return }
        let textures = isColor ? renderer.glyphAtlas.allColorAtlasTextures : renderer.glyphAtlas.allAtlasTextures
        for atlasIndex in batches.keys.sorted() {
            guard atlasIndex >= 0 && atlasIndex < textures.count else { continue }
            guard let instances = batches[atlasIndex], !instances.isEmpty else { continue }
            guard let buffer = renderer.makeBuffer(for: instances) else { continue }
            if isColor {
                renderer.renderColorGlyphs(encoder: encoder, instances: buffer, instanceCount: instances.count, texture: textures[atlasIndex])
            } else {
                renderer.renderGlyphs(encoder: encoder, instances: buffer, instanceCount: instances.count, texture: textures[atlasIndex])
            }
        }
    }

    private func codeGutterWidth(for maxLineNumber: Int) -> CGFloat {
        let digits = max(1, String(maxLineNumber).count)
        let charWidth = layoutEngine.measureTextWidth("8", variant: .monospace)
        return max(30, (CGFloat(digits) + 1.2) * charWidth)
    }

    private func fullScissorRect() -> MTLScissorRect {
        let width = max(1, Int(currentDrawableSize.width))
        let height = max(1, Int(currentDrawableSize.height))
        return MTLScissorRect(x: 0, y: 0, width: width, height: height)
    }

    private func scissorRect(for frame: CGRect) -> MTLScissorRect {
        let adjustedScrollOffset = CGPoint(x: scrollOffset.x, y: scrollOffset.y - topInset)
        let visibleFrame = frame.offsetBy(dx: -adjustedScrollOffset.x, dy: -adjustedScrollOffset.y)
        let viewBounds = CGRect(origin: .zero, size: bounds.size)
        let clipped = visibleFrame.intersection(viewBounds)
        if clipped.isNull || clipped.width <= 0 || clipped.height <= 0 {
            return fullScissorRect()
        }
        let scaleX = currentDrawableSize.width / max(1, bounds.width)
        let scaleY = currentDrawableSize.height / max(1, bounds.height)
        let x = max(0, Int(floor(clipped.minX * scaleX)))
        let y = max(0, Int(floor(clipped.minY * scaleY)))
        let maxWidth = max(1, Int(currentDrawableSize.width) - x)
        let maxHeight = max(1, Int(currentDrawableSize.height) - y)
        let width = min(maxWidth, Int(ceil(clipped.width * scaleX)))
        let height = min(maxHeight, Int(ceil(clipped.height * scaleY)))
        return MTLScissorRect(x: x, y: y, width: max(1, width), height: max(1, height))
    }

    private func renderDebugOverlay(_ layout: MarkdownLayout, encoder: MTLRenderCommandEncoder, renderer: MarkdownMetalRenderer) {
        var lines: [LineInstance] = []

        func appendRect(_ rect: CGRect, color: SIMD4<Float>) {
            let top = LineInstance(position: SIMD2<Float>(Float(rect.minX), Float(rect.minY)), width: Float(rect.width), height: 1, color: color)
            let bottom = LineInstance(position: SIMD2<Float>(Float(rect.minX), Float(rect.maxY - 1)), width: Float(rect.width), height: 1, color: color)
            let left = LineInstance(position: SIMD2<Float>(Float(rect.minX), Float(rect.minY)), width: 1, height: Float(rect.height), color: color)
            let right = LineInstance(position: SIMD2<Float>(Float(rect.maxX - 1), Float(rect.minY)), width: 1, height: Float(rect.height), color: color)
            lines.append(contentsOf: [top, bottom, left, right])
        }

        if debugOptions.contains(.blockFrames) {
            for block in layout.blocks {
                let color = debugColor(for: block.blockType)
                appendRect(block.frame, color: color)
            }
        }

        if debugOptions.contains(.textBaselines) {
            for block in layout.blocks {
                guard let runs = selectionHelper?.getTextRuns(from: block) else { continue }
                for run in runs {
                    guard let bounds = selectionHelper?.runLineBounds(run) else { continue }
                    let baseline = run.position.y
                    lines.append(LineInstance(
                        position: SIMD2<Float>(Float(bounds.minX), Float(baseline)),
                        width: Float(bounds.width),
                        height: 1,
                        color: .teal.withOpacity(0.6)
                    ))
                }
            }
        }

        if debugOptions.contains(.inlineImages) {
            for block in layout.blocks {
                let images: [LayoutInlineImage]
                switch block.content {
                case .inline(_, let imgs):
                    images = imgs
                case .imageRow(let imgs):
                    images = imgs
                case .listItems(let items):
                    images = items.flatMap { $0.inlineImages }
                case .tableRows(let rows):
                    images = rows.flatMap { $0.cells.flatMap { $0.inlineImages } }
                case .definitionList(let items):
                    images = items.flatMap { $0.termImages + $0.definitionImages.flatMap { $0 } }
                case .abbreviationList(let items):
                    images = items.flatMap { $0.images }
                default:
                    images = []
                }
                for image in images {
                    appendRect(image.frame, color: .orange.withOpacity(0.7))
                }
            }
        }

        if debugOptions.contains(.codeGutter) {
            for block in layout.blocks {
                guard case .code(_, _, let lines) = block.content else { continue }
                let maxLineNumber = max(lines.map(\.lineNumber).max() ?? 0, 1)
                let gutterWidth = codeGutterWidth(for: maxLineNumber)
                let headerHeight = CGFloat(theme.codeBlockHeaderHeight)
                let borderWidth: CGFloat = 1
                let gutterFrame = CGRect(
                    x: block.frame.origin.x + borderWidth,
                    y: block.frame.origin.y + headerHeight + borderWidth,
                    width: gutterWidth,
                    height: max(0, block.frame.height - headerHeight - borderWidth * 2)
                )
                appendRect(gutterFrame, color: .blue.withOpacity(0.6))
            }
        }

        if !lines.isEmpty, let buffer = renderer.makeBuffer(for: lines) {
            renderer.renderLinkUnderlines(encoder: encoder, instances: buffer, instanceCount: lines.count)
        }
    }

    // MARK: - Debug Dump

    public func debugLayoutDump(maxRunsPerBlock: Int = 80) -> String {
        guard let layout = cachedLayout else {
            return "Markdown layout dump: no layout available"
        }

        func formatPoint(_ point: CGPoint) -> String {
            String(format: "(%.1f, %.1f)", point.x, point.y)
        }

        func formatSize(_ size: CGSize) -> String {
            String(format: "(%.1f × %.1f)", size.width, size.height)
        }

        func formatRect(_ rect: CGRect) -> String {
            "\(formatPoint(rect.origin)) \(formatSize(rect.size))"
        }

        func describeBlockType(_ type: LayoutBlockType) -> String {
            switch type {
            case .paragraph: return "paragraph"
            case .heading(let level): return "heading(\(level))"
            case .codeBlock(let language): return "code(\(language ?? "text"))"
            case .list: return "list"
            case .blockQuote: return "blockquote"
            case .alert(let kind): return "alert(\(kind.rawValue))"
            case .table: return "table"
            case .definitionList: return "definitionList"
            case .abbreviationList: return "abbreviationList"
            case .image: return "image"
            case .thematicBreak: return "thematicBreak"
            case .mathBlock: return "math"
            case .mermaid: return "mermaid"
            }
        }

        func describeRunStyle(_ style: TextRunStyle) -> String {
            var flags: [String] = []
            if style.isBold { flags.append("bold") }
            if style.isItalic { flags.append("italic") }
            if style.isCode { flags.append("code") }
            if style.isStrikethrough { flags.append("strike") }
            if style.isLink { flags.append("link") }
            if let variant = style.fontVariant { flags.append("\(variant)") }
            return flags.isEmpty ? "regular" : flags.joined(separator: "+")
        }

        func describeRuns(_ runs: [LayoutTextRun], indent: String) -> [String] {
            var lines: [String] = []
            for (index, run) in runs.prefix(maxRunsPerBlock).enumerated() {
                let bounds = selectionHelper?.runLineBounds(run) ?? .zero
                let style = describeRunStyle(run.style)
                let text = run.text.replacingOccurrences(of: "\n", with: "\\n")
                lines.append("\(indent)[\(index)] \"\(text)\" pos \(formatPoint(run.position)) bounds \(formatRect(bounds)) style \(style)")
            }
            if runs.count > maxRunsPerBlock {
                lines.append("\(indent)… \(runs.count - maxRunsPerBlock) more runs")
            }
            return lines
        }

        func describeImages(_ images: [LayoutInlineImage], indent: String) -> [String] {
            images.map { image in
                let link = image.linkURL ?? "-"
                return "\(indent)img \(formatRect(image.frame)) url=\(image.url) link=\(link)"
            }
        }

        var output: [String] = []
        output.append("Markdown layout dump")
        output.append("contentWidth=\(String(format: "%.1f", layout.contentWidth)) totalHeight=\(String(format: "%.1f", layout.totalHeight)) blocks=\(layout.blocks.count)")
        output.append("lineHeight=\(String(format: "%.2f", layoutEngine.currentLineHeight)) ascent=\(String(format: "%.2f", layoutEngine.currentAscent)) descent=\(String(format: "%.2f", layoutEngine.currentDescent))")

        for (index, block) in layout.blocks.enumerated() {
            output.append("")
            output.append("[\(index)] \(describeBlockType(block.blockType)) frame \(formatRect(block.frame)) id=\(block.blockId)")

            switch block.content {
            case .text(let runs):
                output.append("  runs=\(runs.count)")
                output.append(contentsOf: describeRuns(runs, indent: "  "))

            case .inline(let runs, let images):
                output.append("  runs=\(runs.count) images=\(images.count)")
                output.append(contentsOf: describeRuns(runs, indent: "  "))
                output.append(contentsOf: describeImages(images, indent: "  "))

            case .imageRow(let images):
                output.append("  imageRow count=\(images.count)")
                output.append(contentsOf: describeImages(images, indent: "  "))

            case .code(_, let language, let lines):
                let maxLine = lines.map(\.lineNumber).max() ?? lines.count
                let gutterWidth = codeGutterWidth(for: maxLine)
                output.append("  code lines=\(lines.count) language=\(language ?? "text") gutterWidth=\(String(format: "%.1f", gutterWidth))")
                for line in lines.prefix(12) {
                    let lineY = block.frame.origin.y + line.yOffset
                    output.append("  line \(line.lineNumber) y=\(String(format: "%.1f", lineY)) text=\"\(line.text)\"")
                }
                if lines.count > 12 { output.append("  … \(lines.count - 12) more lines") }

            case .listItems(let items):
                output.append("  listItems=\(items.count)")
                for item in items.prefix(20) {
                    let bullet = formatPoint(item.bulletPosition)
                    let runCount = item.contentRuns.count
                    output.append("  item depth=\(item.depth) bullet=\(bullet) runs=\(runCount)")
                }
                if items.count > 20 { output.append("  … \(items.count - 20) more items") }

            case .quoteBlocks(let blocks):
                output.append("  quoteBlocks=\(blocks.count)")

            case .tableRows(let rows):
                output.append("  table rows=\(rows.count)")
                for (rowIndex, row) in rows.enumerated() {
                    output.append("  row[\(rowIndex)] frame \(formatRect(row.frame)) header=\(row.isHeader)")
                    for (cellIndex, cell) in row.cells.enumerated() {
                        let baseline = cell.textRuns.first?.position.y ?? 0
                        output.append("    cell[\(cellIndex)] frame \(formatRect(cell.frame)) baseline=\(String(format: "%.1f", baseline)) runs=\(cell.textRuns.count) images=\(cell.inlineImages.count)")
                    }
                }

            case .definitionList(let items):
                output.append("  definitionItems=\(items.count)")

            case .abbreviationList(let items):
                output.append("  abbreviationItems=\(items.count)")

            case .image(let url, _, let size):
                if let size = size {
                    output.append("  image url=\(url) size=\(formatSize(size))")
                } else {
                    output.append("  image url=\(url) size=unknown")
                }

            case .thematicBreak:
                output.append("  thematicBreak")

            case .math(let latex, let runs):
                output.append("  math runs=\(runs.count) latex=\"\(latex.prefix(80))\"")

            case .mermaid(let diagram):
                output.append("  mermaid frame \(formatRect(diagram.frame)) nodes=\(diagram.nodes.count) lines=\(diagram.lines.count) labels=\(diagram.labels.count)")
            }
        }

        return output.joined(separator: "\n")
    }

    private func debugColor(for blockType: LayoutBlockType) -> SIMD4<Float> {
        switch blockType {
        case .heading:
            return .blue.withOpacity(0.6)
        case .codeBlock:
            return .green.withOpacity(0.6)
        case .table:
            return .orange.withOpacity(0.6)
        case .list:
            return .gray70.withOpacity(0.6)
        case .blockQuote:
            return .purple.withOpacity(0.6)
        case .alert:
            return .red.withOpacity(0.6)
        case .definitionList:
            return .cyan.withOpacity(0.6)
        case .abbreviationList:
            return .teal.withOpacity(0.6)
        case .mermaid:
            return .amber.withOpacity(0.6)
        default:
            return .gray50.withOpacity(0.4)
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
    private let viewProvider: MarkdownViewProvider?
    private let styleRegistry: MarkdownStyleRegistry?

    public init(frame: CGRect, font: VVFont, theme: MarkdownTheme, viewProvider: MarkdownViewProvider? = nil, styleRegistry: MarkdownStyleRegistry? = nil) {
        self.baseFont = font
        self.theme = theme
        self.layoutEngine = MarkdownLayoutEngine(baseFont: font, theme: theme, contentWidth: frame.width)
        self.viewProvider = viewProvider
        self.styleRegistry = styleRegistry
        super.init(frame: frame)
        setup()
    }

    required init?(coder: NSCoder) {
        self.baseFont = .systemFont(ofSize: 14)
        self.theme = .dark
        self.layoutEngine = MarkdownLayoutEngine(baseFont: baseFont, theme: theme, contentWidth: 600)
        self.viewProvider = nil
        self.styleRegistry = nil
        super.init(coder: coder)
        setup()
    }

    private func setup() {
        let ctx = VVMetalContext.shared
        metalLayer = CAMetalLayer()
        metalLayer.device = ctx?.device ?? MTLCreateSystemDefaultDevice()
        metalLayer.pixelFormat = .bgra8Unorm
        metalLayer.framebufferOnly = true
        metalLayer.contentsScale = UIScreen.main.scale

        layer.addSublayer(metalLayer)

        if let ctx {
            renderer = MarkdownMetalRenderer(context: ctx, baseFont: baseFont, scaleFactor: metalLayer.contentsScale)
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
