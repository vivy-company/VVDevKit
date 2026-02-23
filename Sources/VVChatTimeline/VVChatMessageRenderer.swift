import Foundation
import CoreText
import VVMarkdown
import VVMetalPrimitives

public struct VVChatRenderedMessage {
    public let id: String
    public let revision: Int
    public let layout: MarkdownLayout
    public let layoutEngine: MarkdownLayoutEngine
    public let scene: VVScene
    public let height: CGFloat
    public let contentOffset: CGPoint
    public let isDraft: Bool
    public let imageURLs: [String]
}

public final class VVChatMessageRenderer {
    private final class LRUCache<Key: Hashable, Value> {
        private final class Node {
            let key: Key
            var value: Value
            var prev: Node?
            var next: Node?
            init(key: Key, value: Value) { self.key = key; self.value = value }
        }

        private var map: [Key: Node] = [:]
        private var head: Node?  // most recent
        private var tail: Node?  // least recent
        private var limit: Int

        init(limit: Int) {
            self.limit = max(0, limit)
        }

        func updateLimit(_ limit: Int) {
            self.limit = max(0, limit)
            evictIfNeeded()
        }

        func value(for key: Key) -> Value? {
            guard let node = map[key] else { return nil }
            moveToTail(node)
            return node.value
        }

        func set(_ value: Value, for key: Key) {
            if limit == 0 {
                map.removeAll(keepingCapacity: true)
                head = nil
                tail = nil
                return
            }
            if let existing = map[key] {
                existing.value = value
                moveToTail(existing)
            } else {
                let node = Node(key: key, value: value)
                map[key] = node
                appendToTail(node)
            }
            evictIfNeeded()
        }

        func remove(where predicate: (Key) -> Bool) {
            var node = head
            while let current = node {
                node = current.next
                if predicate(current.key) {
                    unlink(current)
                    map.removeValue(forKey: current.key)
                }
            }
        }

        func removeAll() {
            map.removeAll(keepingCapacity: true)
            head = nil
            tail = nil
        }

        private func moveToTail(_ node: Node) {
            guard node !== tail else { return }
            unlink(node)
            appendToTail(node)
        }

        private func appendToTail(_ node: Node) {
            node.prev = tail
            node.next = nil
            tail?.next = node
            tail = node
            if head == nil { head = node }
        }

        private func unlink(_ node: Node) {
            node.prev?.next = node.next
            node.next?.prev = node.prev
            if node === head { head = node.next }
            if node === tail { tail = node.prev }
            node.prev = nil
            node.next = nil
        }

        private func evictIfNeeded() {
            guard limit > 0 else { return }
            while map.count > limit, let oldest = head {
                unlink(oldest)
                map.removeValue(forKey: oldest.key)
            }
        }
    }

    private struct CacheKey: Hashable {
        let id: String
        let revision: Int
        let widthKey: Int
        let isDraft: Bool
    }

    private let parser = MarkdownParser()
    private var finalLayoutEngine: MarkdownLayoutEngine
    private var draftLayoutEngine: MarkdownLayoutEngine
    private var finalPipeline: VVMarkdownRenderPipeline
    private var draftPipeline: VVMarkdownRenderPipeline
    private var headerLayoutEngine: MarkdownLayoutEngine
    private var timestampLayoutEngine: MarkdownLayoutEngine
    private var headerPipeline: VVMarkdownRenderPipeline
    private var timestampPipeline: VVMarkdownRenderPipeline
    private var loadingLayoutEngine: MarkdownLayoutEngine
    private var loadingPipeline: VVMarkdownRenderPipeline
    private var cache: LRUCache<CacheKey, VVChatRenderedMessage>
    private var contentWidth: CGFloat
    private var style: VVChatTimelineStyle
    private var imageSizes: [String: CGSize] = [:]
    private static let timeFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateStyle = .none
        formatter.timeStyle = .short
        return formatter
    }()

    public init(style: VVChatTimelineStyle, contentWidth: CGFloat) {
        self.style = style
        self.contentWidth = contentWidth
        self.finalLayoutEngine = MarkdownLayoutEngine(baseFont: style.baseFont, theme: style.theme, contentWidth: contentWidth)
        self.draftLayoutEngine = MarkdownLayoutEngine(baseFont: style.draftFont, theme: style.draftTheme, contentWidth: contentWidth)
        self.finalPipeline = VVMarkdownRenderPipeline(theme: style.theme, layoutEngine: finalLayoutEngine)
        self.draftPipeline = VVMarkdownRenderPipeline(theme: style.draftTheme, layoutEngine: draftLayoutEngine)
        let headerTheme = Self.makeMetaTheme(base: style.theme, textColor: style.headerTextColor)
        let timestampTheme = Self.makeMetaTheme(base: style.theme, textColor: style.timestampTextColor)
        let loadingTheme = Self.makeMetaTheme(base: style.theme, textColor: style.loadingIndicatorTextColor)
        self.headerLayoutEngine = MarkdownLayoutEngine(baseFont: style.headerFont, theme: headerTheme, contentWidth: contentWidth)
        self.timestampLayoutEngine = MarkdownLayoutEngine(baseFont: style.timestampFont, theme: timestampTheme, contentWidth: contentWidth)
        self.headerPipeline = VVMarkdownRenderPipeline(theme: headerTheme, layoutEngine: headerLayoutEngine)
        self.timestampPipeline = VVMarkdownRenderPipeline(theme: timestampTheme, layoutEngine: timestampLayoutEngine)
        self.loadingLayoutEngine = MarkdownLayoutEngine(baseFont: style.loadingIndicatorFont, theme: loadingTheme, contentWidth: contentWidth)
        self.loadingPipeline = VVMarkdownRenderPipeline(theme: loadingTheme, layoutEngine: loadingLayoutEngine)
        self.cache = LRUCache(limit: style.renderedCacheLimit)
    }

    public func updateStyle(_ style: VVChatTimelineStyle) {
        self.style = style
        finalLayoutEngine = MarkdownLayoutEngine(baseFont: style.baseFont, theme: style.theme, contentWidth: contentWidth)
        draftLayoutEngine = MarkdownLayoutEngine(baseFont: style.draftFont, theme: style.draftTheme, contentWidth: contentWidth)
        finalPipeline = VVMarkdownRenderPipeline(theme: style.theme, layoutEngine: finalLayoutEngine)
        draftPipeline = VVMarkdownRenderPipeline(theme: style.draftTheme, layoutEngine: draftLayoutEngine)
        let headerTheme = Self.makeMetaTheme(base: style.theme, textColor: style.headerTextColor)
        let timestampTheme = Self.makeMetaTheme(base: style.theme, textColor: style.timestampTextColor)
        let loadingTheme = Self.makeMetaTheme(base: style.theme, textColor: style.loadingIndicatorTextColor)
        headerLayoutEngine = MarkdownLayoutEngine(baseFont: style.headerFont, theme: headerTheme, contentWidth: contentWidth)
        timestampLayoutEngine = MarkdownLayoutEngine(baseFont: style.timestampFont, theme: timestampTheme, contentWidth: contentWidth)
        headerPipeline = VVMarkdownRenderPipeline(theme: headerTheme, layoutEngine: headerLayoutEngine)
        timestampPipeline = VVMarkdownRenderPipeline(theme: timestampTheme, layoutEngine: timestampLayoutEngine)
        loadingLayoutEngine = MarkdownLayoutEngine(baseFont: style.loadingIndicatorFont, theme: loadingTheme, contentWidth: contentWidth)
        loadingPipeline = VVMarkdownRenderPipeline(theme: loadingTheme, layoutEngine: loadingLayoutEngine)
        cache.updateLimit(style.renderedCacheLimit)
        cache.removeAll()
    }

    public func updateContentWidth(_ width: CGFloat) {
        let widthKey = Self.widthKey(for: width)
        if widthKey == Self.widthKey(for: contentWidth) {
            return
        }
        contentWidth = width
        finalLayoutEngine.updateContentWidth(width)
        draftLayoutEngine.updateContentWidth(width)
        headerLayoutEngine.updateContentWidth(width)
        timestampLayoutEngine.updateContentWidth(width)
        loadingLayoutEngine.updateContentWidth(width)
        cache.removeAll()
    }

    public func updateImageSize(url: String, size: CGSize) -> Bool {
        if imageSizes[url] == size {
            return false
        }
        imageSizes[url] = size
        return true
    }

    public func invalidate(messageID: String) {
        cache.remove(where: { $0.id == messageID })
    }

    public func renderedMessage(for message: VVChatMessage) -> VVChatRenderedMessage {
        let insets = style.insets(for: message.role)
        let bubbleStyle = style.bubbleStyle(for: message.role)
        let usesBubble = bubbleStyle != nil
        let bubbleInsets = bubbleStyle?.insets ?? VVInsets()
        let availableWidth = max(0, contentWidth - insets.left - insets.right)
        let maxBubbleWidth = bubbleStyle?.maxWidth ?? availableWidth
        let maxContentWidth = usesBubble ? min(availableWidth - bubbleInsets.left - bubbleInsets.right, maxBubbleWidth) : availableWidth
        let messageContentWidth = max(0, maxContentWidth)
        let widthKey = Self.widthKey(for: messageContentWidth)
        let isDraft = message.state == .draft
        let key = CacheKey(id: message.id, revision: message.revision, widthKey: widthKey, isDraft: isDraft)
        if let cached = cache.value(for: key) {
            return cached
        }

        let document = isDraft ? makeStreamingDocument(text: message.content) : parser.parse(message.content)
        let (layoutEngine, pipeline) = isDraft ? (draftLayoutEngine, draftPipeline) : (finalLayoutEngine, finalPipeline)

        layoutEngine.updateImageSizeProvider { [weak self] url in
            self?.imageSizes[url]
        }
        layoutEngine.updateContentWidth(messageContentWidth)
        var layout = layoutEngine.layout(document)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)

        let contentScene = pipeline.buildScene(from: layout)
        let contentBounds = sceneBounds(for: contentScene, layoutEngine: layoutEngine)
        let contentMinX = min(0, contentBounds?.minX ?? 0)
        let contentMinY = min(0, contentBounds?.minY ?? 0)
        let imageURLs = Array(collectImageURLs(from: layout))
        let measuredWidth = usesBubble ? measuredContentWidth(for: layout) : nil
        let bubbleWidthSource = measuredWidth ?? max(0, contentBounds?.width ?? 0)
        let bubbleContentWidth = usesBubble ? max(1, min(messageContentWidth, bubbleWidthSource > 0 ? bubbleWidthSource : messageContentWidth)) : messageContentWidth
        let headerText = headerTitle(for: message.role)
        let footerText: String
        let footerMetaFont: VVFont
        if isDraft && message.role == .assistant {
            footerText = style.loadingIndicatorText
            footerMetaFont = style.loadingIndicatorFont
        } else {
            footerText = timestampLabel(for: message)
            footerMetaFont = style.timestampFont
        }

        let headerRequiredWidth = Self.singleLineMetaWidth(headerText, font: style.headerFont)
        let footerRequiredWidth = Self.singleLineMetaWidth(footerText, font: footerMetaFont)
        let preferredMetaWidth = max(style.bubbleMetadataMinWidth, headerRequiredWidth, footerRequiredWidth)
        let clampedMetaWidth = max(1, min(messageContentWidth, preferredMetaWidth))
        let metaWidth = usesBubble ? max(bubbleContentWidth, clampedMetaWidth) : messageContentWidth

        let headerRender = renderMeta(text: headerText, layoutEngine: headerLayoutEngine, pipeline: headerPipeline, width: metaWidth)
        let footerRender: (layout: MarkdownLayout, scene: VVScene)
        if isDraft && message.role == .assistant {
            footerRender = renderMeta(text: footerText, layoutEngine: loadingLayoutEngine, pipeline: loadingPipeline, width: metaWidth)
        } else {
            footerRender = renderMeta(text: footerText, layoutEngine: timestampLayoutEngine, pipeline: timestampPipeline, width: metaWidth)
        }

        let headerHeight = headerRender.layout.totalHeight
        let contentHeight = layout.totalHeight
        let footerHeight = footerRender.layout.totalHeight
        let headerBlockHeight = headerHeight > 0 ? headerHeight + style.headerSpacing : 0
        let footerBlockHeight = footerHeight > 0 ? style.footerSpacing + footerHeight : 0
        let contentBlockHeight = usesBubble
            ? (bubbleInsets.top + contentHeight + bubbleInsets.bottom)
            : contentHeight
        let bubbleWidth = usesBubble ? (bubbleContentWidth + bubbleInsets.left + bubbleInsets.right) : 0
        let messageHeight = headerBlockHeight + contentBlockHeight + footerBlockHeight

        var builder = VVSceneBuilder()
        var currentY: CGFloat = 0
        if headerHeight > 0 {
            builder.add(node: VVNode.fromScene(headerRender.scene))
            currentY += headerHeight + style.headerSpacing
        }

        if let bubbleStyle {
            let bubbleFrame = CGRect(x: 0, y: currentY, width: bubbleWidth, height: contentBlockHeight)
            if bubbleStyle.borderWidth > 0, bubbleStyle.borderColor.w > 0 {
                let borderFrame = bubbleFrame.insetBy(dx: -bubbleStyle.borderWidth, dy: -bubbleStyle.borderWidth)
                let border = VVQuadPrimitive(
                    frame: borderFrame,
                    color: bubbleStyle.borderColor,
                    cornerRadius: bubbleStyle.cornerRadius + bubbleStyle.borderWidth
                )
                builder.add(kind: .quad(border), zIndex: -2)
            }
            let bubble = VVQuadPrimitive(
                frame: bubbleFrame,
                color: bubbleStyle.color,
                cornerRadius: bubbleStyle.cornerRadius
            )
            builder.add(kind: .quad(bubble), zIndex: -1)
            let contentOffsetX = bubbleInsets.left - contentMinX
            let contentOffsetY = currentY + bubbleInsets.top - contentMinY
            builder.withOffset(CGPoint(x: contentOffsetX, y: contentOffsetY)) { builder in
                builder.add(node: VVNode.fromScene(contentScene))
            }
        } else {
            let contentOffsetX = -contentMinX
            let contentOffsetY = currentY - contentMinY
            builder.withOffset(CGPoint(x: contentOffsetX, y: contentOffsetY)) { builder in
                builder.add(node: VVNode.fromScene(contentScene))
            }
        }

        currentY += contentBlockHeight
        if footerHeight > 0 {
            currentY += style.footerSpacing
            builder.withOffset(CGPoint(x: 0, y: currentY)) { builder in
                builder.add(node: VVNode.fromScene(footerRender.scene))
            }
        }

        let scene = builder.scene
        let messageBounds = sceneBounds(for: scene, layoutEngine: layoutEngine)
        let topOverflow = max(0, -(messageBounds?.minY ?? 0))
        let sceneMaxY = max(0, messageBounds?.maxY ?? messageHeight)
        let measuredMessageHeight = max(messageHeight + topOverflow, sceneMaxY + topOverflow)
        let height = measuredMessageHeight + insets.top + insets.bottom

        let bubbleOffsetX: CGFloat
        if let bubbleStyle {
            switch bubbleStyle.alignment {
            case .leading:
                bubbleOffsetX = 0
            case .trailing:
                bubbleOffsetX = max(0, availableWidth - bubbleWidth)
            }
        } else {
            bubbleOffsetX = 0
        }
        let rendered = VVChatRenderedMessage(
            id: message.id,
            revision: message.revision,
            layout: layout,
            layoutEngine: layoutEngine,
            scene: scene,
            height: height,
            contentOffset: CGPoint(x: insets.left + bubbleOffsetX, y: insets.top + topOverflow),
            isDraft: isDraft,
            imageURLs: imageURLs
        )
        cache.set(rendered, for: key)
        return rendered
    }

    private func makeDraftDocument(text: String) -> ParsedMarkdownDocument {
        let content = MarkdownInlineContent(text: text)
        let block = MarkdownBlock(.paragraph(content), index: 0)
        return ParsedMarkdownDocument(blocks: [block], footnotes: [:], isComplete: false, streamingBuffer: text)
    }

    private func makeStreamingDocument(text: String) -> ParsedMarkdownDocument {
        let parsed = parser.parseStreaming(text, isComplete: false)
        guard !parsed.streamingBuffer.isEmpty else { return parsed }

        var blocks = parsed.blocks
        let bufferContent = MarkdownInlineContent(text: parsed.streamingBuffer)
        blocks.append(MarkdownBlock(.paragraph(bufferContent), index: blocks.count))
        return ParsedMarkdownDocument(
            blocks: blocks,
            footnotes: parsed.footnotes,
            isComplete: false,
            streamingBuffer: parsed.streamingBuffer
        )
    }

    private func renderMeta(
        text: String,
        layoutEngine: MarkdownLayoutEngine,
        pipeline: VVMarkdownRenderPipeline,
        width: CGFloat
    ) -> (layout: MarkdownLayout, scene: VVScene) {
        layoutEngine.updateContentWidth(width)
        let document = makeMetaDocument(text: text)
        var layout = layoutEngine.layout(document)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)
        let scene = pipeline.buildScene(from: layout)
        return (layout, scene)
    }

    private func makeMetaDocument(text: String) -> ParsedMarkdownDocument {
        let content = MarkdownInlineContent(text: text)
        let block = MarkdownBlock(.paragraph(content), index: 0)
        return ParsedMarkdownDocument(blocks: [block], footnotes: [:], isComplete: true, streamingBuffer: "")
    }

    private static func singleLineMetaWidth(_ text: String, font: VVFont) -> CGFloat {
        guard !text.isEmpty else { return 0 }
        let attributed = NSAttributedString(string: text, attributes: [.font: font])
        let line = CTLineCreateWithAttributedString(attributed)
        let width = CGFloat(CTLineGetTypographicBounds(line, nil, nil, nil))
        return ceil(width + 2)
    }

    private func headerTitle(for role: VVChatMessageRole) -> String {
        switch role {
        case .user:
            return "User"
        case .assistant:
            return "Agent"
        case .system:
            return "System"
        }
    }

    private func timestampLabel(for message: VVChatMessage) -> String {
        let timestamp = message.timestamp ?? Date()
        return Self.timeFormatter.string(from: timestamp)
    }

    private static func makeMetaTheme(base: MarkdownTheme, textColor: SIMD4<Float>) -> MarkdownTheme {
        var theme = base
        theme.textColor = textColor
        theme.headingColor = textColor
        theme.linkColor = textColor
        theme.codeColor = textColor
        theme.blockQuoteColor = textColor
        theme.listBulletColor = textColor
        theme.checkboxCheckedColor = textColor
        theme.checkboxUncheckedColor = textColor
        theme.thematicBreakColor = textColor
        theme.tableBorderColor = textColor
        theme.diagramTextColor = textColor
        theme.mathColor = textColor
        theme.strikethroughColor = textColor
        theme.contentPadding = 0
        theme.paragraphSpacing = 2
        return theme
    }

    private func sceneBounds(for scene: VVScene, layoutEngine: MarkdownLayoutEngine) -> CGRect? {
        var minX = CGFloat.greatestFiniteMagnitude
        var minY = CGFloat.greatestFiniteMagnitude
        var maxX = -CGFloat.greatestFiniteMagnitude
        var maxY = -CGFloat.greatestFiniteMagnitude
        var hasValue = false

        let baseSize = max(1, layoutEngine.baseFontSize)
        let ascent = layoutEngine.currentAscent
        let descent = layoutEngine.currentDescent

        func updateBounds(minX newMinX: CGFloat, minY newMinY: CGFloat, maxX newMaxX: CGFloat, maxY newMaxY: CGFloat) {
            minX = min(minX, newMinX)
            minY = min(minY, newMinY)
            maxX = max(maxX, newMaxX)
            maxY = max(maxY, newMaxY)
            hasValue = true
        }

        func updateBounds(_ rect: CGRect) {
            updateBounds(minX: rect.minX, minY: rect.minY, maxX: rect.maxX, maxY: rect.maxY)
        }

        func updateGlyphs(_ glyphs: [VVTextGlyph], fontSize: CGFloat) {
            guard !glyphs.isEmpty else { return }
            let scale = max(0.5, fontSize / baseSize)
            let glyphAscent = ascent * scale
            let glyphDescent = descent * scale
            for glyph in glyphs where glyph.color.w > 0 {
                updateBounds(
                    minX: glyph.position.x,
                    minY: glyph.position.y - glyphAscent,
                    maxX: glyph.position.x + glyph.size.width,
                    maxY: glyph.position.y + glyphDescent
                )
            }
        }

        for primitive in scene.primitives {
            switch primitive.kind {
            case .textRun(let run):
                updateGlyphs(run.glyphs, fontSize: run.fontSize)

            case .quad(let quad):
                guard quad.color.w > 0 else { continue }
                updateBounds(quad.frame)

            case .gradientQuad(let quad):
                if quad.startColor.w <= 0 && quad.endColor.w <= 0 {
                    continue
                }
                updateBounds(quad.frame)

            case .line(let line):
                guard line.color.w > 0 else { continue }
                let minX = min(line.start.x, line.end.x)
                let minY = min(line.start.y, line.end.y)
                let width = abs(line.end.x - line.start.x)
                let height = abs(line.end.y - line.start.y)
                let rectWidth = width > 0 ? width : line.thickness
                let rectHeight = height > 0 ? height : line.thickness
                updateBounds(CGRect(x: minX, y: minY, width: rectWidth, height: rectHeight))

            case .bullet(let bullet):
                guard bullet.color.w > 0 else { continue }
                updateBounds(CGRect(x: bullet.position.x, y: bullet.position.y, width: bullet.size, height: bullet.size))

            case .image(let image):
                updateBounds(image.frame)

            case .blockQuoteBorder(let border):
                guard border.color.w > 0 else { continue }
                updateBounds(border.frame)

            case .tableLine(let line):
                guard line.color.w > 0 else { continue }
                let minX = min(line.start.x, line.end.x)
                let minY = min(line.start.y, line.end.y)
                let width = abs(line.end.x - line.start.x)
                let height = abs(line.end.y - line.start.y)
                let rectWidth = width > 0 ? width : line.lineWidth
                let rectHeight = height > 0 ? height : line.lineWidth
                updateBounds(CGRect(x: minX, y: minY, width: rectWidth, height: rectHeight))

            case .pieSlice(let slice):
                guard slice.color.w > 0 else { continue }
                let rect = CGRect(
                    x: slice.center.x - slice.radius,
                    y: slice.center.y - slice.radius,
                    width: slice.radius * 2,
                    height: slice.radius * 2
                )
                updateBounds(rect)

            case .underline(let underline):
                guard underline.color.w > 0 else { continue }
                updateBounds(CGRect(x: underline.origin.x, y: underline.origin.y, width: underline.width, height: underline.thickness))

            case .path(let path):
                updateBounds(path.bounds)
            }
        }

        guard hasValue else { return nil }
        return CGRect(x: minX, y: minY, width: max(1, maxX - minX), height: max(1, maxY - minY))
    }

    private func measuredContentWidth(for layout: MarkdownLayout) -> CGFloat? {
        var maxX: CGFloat = 0
        var hasValue = false
        for block in layout.blocks {
            let (blockMaxX, blockHasValue) = measuredMaxX(for: block)
            if blockHasValue {
                maxX = max(maxX, blockMaxX)
                hasValue = true
            }
        }
        return hasValue ? maxX : nil
    }

    private func measuredMaxX(for block: LayoutBlock) -> (CGFloat, Bool) {
        switch block.content {
        case .text(let runs):
            return measuredMaxX(for: runs, images: [])
        case .inline(let runs, let images):
            return measuredMaxX(for: runs, images: images)
        case .listItems(let items):
            return measuredMaxX(for: items)
        case .quoteBlocks(let blocks):
            return measuredMaxX(for: blocks)
        case .definitionList(let items):
            return measuredMaxX(for: items)
        case .abbreviationList(let items):
            return measuredMaxX(for: items)
        case .imageRow(let images):
            return measuredMaxX(for: images)
        case .tableRows(let rows):
            if let rowMax = rows.map({ $0.frame.maxX }).max() {
                return (rowMax, rowMax > 0)
            }
            return (block.frame.maxX, block.frame.maxX > 0)
        case .mermaid(let diagram):
            return (diagram.frame.maxX, diagram.frame.maxX > 0)
        case .image, .code, .thematicBreak, .math:
            return (block.frame.maxX, block.frame.maxX > 0)
        }
    }

    private func measuredMaxX(for blocks: [LayoutBlock]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for block in blocks {
            let (blockMaxX, blockHasValue) = measuredMaxX(for: block)
            if blockHasValue {
                maxX = max(maxX, blockMaxX)
                hasValue = true
            }
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for items: [LayoutListItem]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for item in items {
            let (itemMaxX, itemHasValue) = measuredMaxX(for: item)
            if itemHasValue {
                maxX = max(maxX, itemMaxX)
                hasValue = true
            }
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for item: LayoutListItem) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        let (contentMaxX, contentHasValue) = measuredMaxX(for: item.contentRuns, images: item.inlineImages)
        if contentHasValue {
            maxX = max(maxX, contentMaxX)
            hasValue = true
        }
        let (childMaxX, childHasValue) = measuredMaxX(for: item.children)
        if childHasValue {
            maxX = max(maxX, childMaxX)
            hasValue = true
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for items: [LayoutDefinitionItem]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for item in items {
            let (termMaxX, termHasValue) = measuredMaxX(for: item.termRuns, images: item.termImages)
            if termHasValue {
                maxX = max(maxX, termMaxX)
                hasValue = true
            }
            for (index, runs) in item.definitionRuns.enumerated() {
                let images = index < item.definitionImages.count ? item.definitionImages[index] : []
                let (defMaxX, defHasValue) = measuredMaxX(for: runs, images: images)
                if defHasValue {
                    maxX = max(maxX, defMaxX)
                    hasValue = true
                }
            }
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for items: [LayoutAbbreviationItem]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for item in items {
            let (itemMaxX, itemHasValue) = measuredMaxX(for: item.runs, images: item.images)
            if itemHasValue {
                maxX = max(maxX, itemMaxX)
                hasValue = true
            }
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for runs: [LayoutTextRun], images: [LayoutInlineImage]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for run in runs {
            for glyph in run.glyphs {
                maxX = max(maxX, glyph.position.x + glyph.size.width)
                hasValue = true
            }
        }
        for image in images {
            maxX = max(maxX, image.frame.maxX)
            hasValue = true
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for images: [LayoutInlineImage]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for image in images {
            maxX = max(maxX, image.frame.maxX)
            hasValue = true
        }
        return (maxX, hasValue)
    }

    private func collectImageURLs(from layout: MarkdownLayout) -> Set<String> {
        var urls = Set<String>()
        for block in layout.blocks {
            collectImageURLs(from: block, into: &urls)
        }
        return urls
    }

    private func collectImageURLs(from block: LayoutBlock, into urls: inout Set<String>) {
        switch block.content {
        case .inline(_, let images):
            for image in images { urls.insert(image.url) }
        case .imageRow(let images):
            for image in images { urls.insert(image.url) }
        case .image(let url, _, _):
            urls.insert(url)
        case .listItems(let items):
            for item in items {
                collectImageURLs(from: item, into: &urls)
            }
        case .quoteBlocks(let blocks):
            for nested in blocks {
                collectImageURLs(from: nested, into: &urls)
            }
        case .tableRows(let rows):
            for row in rows {
                for cell in row.cells {
                    for image in cell.inlineImages {
                        urls.insert(image.url)
                    }
                }
            }
        case .definitionList(let items):
            for item in items {
                for image in item.termImages {
                    urls.insert(image.url)
                }
                for definitionImages in item.definitionImages {
                    for image in definitionImages {
                        urls.insert(image.url)
                    }
                }
            }
        case .abbreviationList(let items):
            for item in items {
                for image in item.images {
                    urls.insert(image.url)
                }
            }
        default:
            break
        }
    }

    private func collectImageURLs(from item: LayoutListItem, into urls: inout Set<String>) {
        for image in item.inlineImages {
            urls.insert(image.url)
        }
        for child in item.children {
            collectImageURLs(from: child, into: &urls)
        }
    }

    private static func widthKey(for width: CGFloat) -> Int {
        Int((width * 2).rounded(.down))
    }
}
