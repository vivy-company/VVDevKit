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
        let innerWidth = max(0, availableWidth - bubbleInsets.left - bubbleInsets.right)
        let widthKey = Self.widthKey(for: innerWidth)
        let isDraft = message.state == .draft
        let key = CacheKey(id: message.id, revision: message.revision, widthKey: widthKey, isDraft: isDraft)
        if let cached = cache.value(for: key) {
            return cached
        }

        let document = isDraft ? makeDraftDocument(text: message.content) : parser.parse(message.content)
        let (layoutEngine, pipeline) = isDraft ? (draftLayoutEngine, draftPipeline) : (finalLayoutEngine, finalPipeline)

        layoutEngine.updateImageSizeProvider { [weak self] url in
            self?.imageSizes[url]
        }
        layoutEngine.updateContentWidth(innerWidth)
        var layout = layoutEngine.layout(document)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)

        let contentScene = pipeline.buildScene(from: layout)
        let imageURLs = Array(collectImageURLs(from: layout))
        let headerText = headerTitle(for: message.role)
        let headerRender = renderMeta(text: headerText, layoutEngine: headerLayoutEngine, pipeline: headerPipeline, width: innerWidth)
        let footerRender: (layout: MarkdownLayout, scene: VVScene)
        if isDraft && message.role == .assistant {
            footerRender = renderMeta(text: style.loadingIndicatorText, layoutEngine: loadingLayoutEngine, pipeline: loadingPipeline, width: innerWidth)
        } else {
            footerRender = renderMeta(text: timestampLabel(for: message), layoutEngine: timestampLayoutEngine, pipeline: timestampPipeline, width: innerWidth)
        }

        let headerHeight = headerRender.layout.totalHeight
        let contentHeight = layout.totalHeight
        let footerHeight = footerRender.layout.totalHeight
        let bubbleHeight = bubbleInsets.top
            + headerHeight
            + style.headerSpacing
            + contentHeight
            + style.footerSpacing
            + footerHeight
            + bubbleInsets.bottom
        let height = bubbleHeight + insets.top + insets.bottom

        var builder = VVSceneBuilder()
        if usesBubble {
            let bubble = VVQuadPrimitive(
                frame: CGRect(x: 0, y: 0, width: availableWidth, height: bubbleHeight),
                color: style.userBubbleColor,
                cornerRadius: style.userBubbleCornerRadius
            )
            builder.add(kind: .quad(bubble), zIndex: -1)
        }

        let innerOrigin = CGPoint(x: bubbleInsets.left, y: bubbleInsets.top)
        builder.withOffset(innerOrigin) { builder in
            if headerHeight > 0 {
                builder.add(node: VVNode.fromScene(headerRender.scene))
            }
            let contentOffsetY = headerHeight + style.headerSpacing
            builder.withOffset(CGPoint(x: 0, y: contentOffsetY)) { builder in
                builder.add(node: VVNode.fromScene(contentScene))
            }
            let timestampOffsetY = contentOffsetY + contentHeight + style.footerSpacing
            if footerHeight > 0 {
                builder.withOffset(CGPoint(x: 0, y: timestampOffsetY)) { builder in
                    builder.add(node: VVNode.fromScene(footerRender.scene))
                }
            }
        }

        let scene = builder.scene
        let rendered = VVChatRenderedMessage(
            id: message.id,
            revision: message.revision,
            layout: layout,
            scene: scene,
            height: height,
            contentOffset: CGPoint(x: insets.left, y: insets.top),
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
