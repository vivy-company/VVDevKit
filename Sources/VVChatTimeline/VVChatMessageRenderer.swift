import Foundation
import VVMarkdown
import VVMetalPrimitives

public struct VVChatRenderedMessage {
    public let id: String
    public let revision: Int
    public let layout: MarkdownLayout
    public let scene: VVScene
    public let height: CGFloat
    public let contentOffset: CGPoint
    public let isDraft: Bool
    public let imageURLs: [String]
}

public final class VVChatMessageRenderer {
    private final class LRUCache<Key: Hashable, Value> {
        private var values: [Key: Value] = [:]
        private var order: [Key] = []
        private var limit: Int

        init(limit: Int) {
            self.limit = max(0, limit)
        }

        func updateLimit(_ limit: Int) {
            self.limit = max(0, limit)
            evictIfNeeded()
        }

        func value(for key: Key) -> Value? {
            guard let value = values[key] else { return nil }
            touch(key)
            return value
        }

        func set(_ value: Value, for key: Key) {
            if limit == 0 {
                values.removeAll(keepingCapacity: true)
                order.removeAll(keepingCapacity: true)
                return
            }
            values[key] = value
            touch(key)
            evictIfNeeded()
        }

        func remove(where predicate: (Key) -> Bool) {
            for key in order where predicate(key) {
                values.removeValue(forKey: key)
            }
            order.removeAll(where: predicate)
        }

        func removeAll() {
            values.removeAll(keepingCapacity: true)
            order.removeAll(keepingCapacity: true)
        }

        private func touch(_ key: Key) {
            if let index = order.firstIndex(of: key) {
                order.remove(at: index)
            }
            order.append(key)
        }

        private func evictIfNeeded() {
            guard limit > 0 else { return }
            while order.count > limit {
                let key = order.removeFirst()
                values.removeValue(forKey: key)
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
        let usesBubble = message.role == .user
        let bubbleInsets = usesBubble ? style.userBubbleInsets : VVInsets()
        let availableWidth = max(0, contentWidth - insets.left - insets.right)
        let maxContentWidth = usesBubble ? min(availableWidth - bubbleInsets.left - bubbleInsets.right, style.userBubbleMaxWidth) : availableWidth
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
        let imageURLs = Array(collectImageURLs(from: layout))
        let measuredWidth = usesBubble ? measuredContentWidth(for: layout) : nil
        let bubbleContentWidth = usesBubble ? max(0, min(messageContentWidth, measuredWidth ?? messageContentWidth)) : messageContentWidth
        let metaWidth = usesBubble ? max(bubbleContentWidth, 1) : messageContentWidth
        let headerText = headerTitle(for: message.role)
        let headerRender = renderMeta(text: headerText, layoutEngine: headerLayoutEngine, pipeline: headerPipeline, width: metaWidth)
        let footerRender: (layout: MarkdownLayout, scene: VVScene)
        if isDraft && message.role == .assistant {
            footerRender = renderMeta(text: style.loadingIndicatorText, layoutEngine: loadingLayoutEngine, pipeline: loadingPipeline, width: metaWidth)
        } else {
            footerRender = renderMeta(text: timestampLabel(for: message), layoutEngine: timestampLayoutEngine, pipeline: timestampPipeline, width: metaWidth)
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
        let height = messageHeight + insets.top + insets.bottom

        var builder = VVSceneBuilder()
        var currentY: CGFloat = 0
        if headerHeight > 0 {
            builder.add(node: VVNode.fromScene(headerRender.scene))
            currentY += headerHeight + style.headerSpacing
        }

        if usesBubble {
            let bubble = VVQuadPrimitive(
                frame: CGRect(x: 0, y: currentY, width: bubbleWidth, height: contentBlockHeight),
                color: style.userBubbleColor,
                cornerRadius: style.userBubbleCornerRadius
            )
            builder.add(kind: .quad(bubble), zIndex: -1)
            builder.withOffset(CGPoint(x: bubbleInsets.left, y: currentY + bubbleInsets.top)) { builder in
                builder.add(node: VVNode.fromScene(contentScene))
            }
        } else {
            builder.withOffset(CGPoint(x: 0, y: currentY)) { builder in
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
        let bubbleOffsetX = usesBubble ? max(0, availableWidth - bubbleWidth) : 0
        let rendered = VVChatRenderedMessage(
            id: message.id,
            revision: message.revision,
            layout: layout,
            scene: scene,
            height: height,
            contentOffset: CGPoint(x: insets.left + bubbleOffsetX, y: insets.top),
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
