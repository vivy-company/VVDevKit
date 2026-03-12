import CoreGraphics
import Foundation
import VVMarkdown

@MainActor
protocol VVChatTimelineRendering: AnyObject {
    var currentStyle: VVChatTimelineStyle { get }
    var contentWidth: CGFloat { get }

    func updateStyle(_ style: VVChatTimelineStyle)
    func updateContentWidth(_ width: CGFloat)
    func updateImageSize(url: String, size: CGSize) -> Bool

    func trimCaches(keepingItemIDs: Set<String>)
    func invalidate(messageID: String)
    func invalidateRendered(messageID: String)
    func invalidateAll()

    func debugSnapshot() -> VVChatMessageRenderer.DebugSnapshot
    func renderedItem(for item: VVChatTimelineItem) -> VVChatRenderedMessage
    func layoutSummary(for item: VVChatTimelineItem) -> VVChatMessageLayoutSummary
    func estimatedLayoutSummary(for item: VVChatTimelineItem) -> VVChatMessageLayoutSummary
    func selectionHelper(
        for item: VVChatTimelineItem,
        rendered: VVChatRenderedMessage
    ) -> VVMarkdownSelectionHelper?
    func selectionArtifacts(
        for item: VVChatTimelineItem,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSelectionArtifacts?
    func contentSceneArtifacts(
        for item: VVChatTimelineItem,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSceneArtifacts?
    func sceneArtifacts(
        for item: VVChatTimelineItem,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSceneArtifacts?

#if os(macOS)
    func visibleRenderItem(
        for item: VVChatTimelineResolvedRenderItem,
        viewport: CGRect
    ) -> VVChatTimelineVisibleRenderItemUpdate

    func visibleRenderSnapshot(
        for items: [VVChatTimelineResolvedRenderItem],
        range: Range<Int>,
        viewport: CGRect
    ) -> VVChatTimelineVisibleRenderSnapshot
#endif
}

@MainActor
final class VVChatTimelineRenderService: VVChatTimelineRendering {
    private protocol ItemRendererBackend: AnyObject {
        func prepareLayoutIfNeeded(
            for item: VVChatTimelineItem,
            requiresLayout: Bool
        ) async
        func prepareVisibleSceneIfNeeded(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage,
            visibleRect: CGRect?
        ) async
        func prepareVisibleSelectionIfNeeded(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage,
            visibleRect: CGRect?
        ) async
        func renderedItem(for item: VVChatTimelineItem) -> VVChatRenderedMessage
        func layoutSummary(for item: VVChatTimelineItem) -> VVChatMessageLayoutSummary
        func estimatedLayoutSummary(for item: VVChatTimelineItem) -> VVChatMessageLayoutSummary
        func selectionHelper(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage
        ) -> VVMarkdownSelectionHelper?
        func selectionArtifacts(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage,
            visibleRect: CGRect?
        ) -> VVChatSelectionArtifacts?
        func contentSceneArtifacts(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage,
            visibleRect: CGRect?
        ) -> VVChatSceneArtifacts?
        func sceneArtifacts(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage,
            visibleRect: CGRect?
        ) -> VVChatSceneArtifacts?
    }

    private final class MessageItemRendererBackend: ItemRendererBackend {
        private let renderer: VVChatMessageRenderer

        init(renderer: VVChatMessageRenderer) {
            self.renderer = renderer
        }

        func prepareLayoutIfNeeded(
            for item: VVChatTimelineItem,
            requiresLayout: Bool
        ) async {
            await renderer.prepareMarkdownContentIfNeeded(
                for: item.message,
                requiresLayout: requiresLayout
            )
        }

        func prepareVisibleSceneIfNeeded(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage,
            visibleRect: CGRect?
        ) async {
            await renderer.prepareVisibleSceneArtifactsIfNeeded(
                for: item.message,
                rendered: rendered,
                visibleRect: visibleRect
            )
        }

        func prepareVisibleSelectionIfNeeded(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage,
            visibleRect: CGRect?
        ) async {
            await renderer.prepareVisibleSelectionArtifactsIfNeeded(
                for: item.message,
                rendered: rendered,
                visibleRect: visibleRect
            )
        }

        func renderedItem(for item: VVChatTimelineItem) -> VVChatRenderedMessage {
            renderer.renderedMessage(for: item.message)
        }

        func layoutSummary(for item: VVChatTimelineItem) -> VVChatMessageLayoutSummary {
            renderer.layoutSummary(for: item.message)
        }

        func estimatedLayoutSummary(for item: VVChatTimelineItem) -> VVChatMessageLayoutSummary {
            renderer.estimatedLayoutSummary(for: item.message)
        }

        func selectionHelper(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage
        ) -> VVMarkdownSelectionHelper? {
            renderer.selectionHelper(for: item.message, rendered: rendered)
        }

        func selectionArtifacts(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage,
            visibleRect: CGRect?
        ) -> VVChatSelectionArtifacts? {
            renderer.selectionArtifacts(for: item.message, rendered: rendered, visibleRect: visibleRect)
        }

        func contentSceneArtifacts(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage,
            visibleRect: CGRect?
        ) -> VVChatSceneArtifacts? {
            renderer.contentSceneArtifacts(for: item.message, rendered: rendered, visibleRect: visibleRect)
        }

        func sceneArtifacts(
            for item: VVChatTimelineItem,
            rendered: VVChatRenderedMessage,
            visibleRect: CGRect?
        ) -> VVChatSceneArtifacts? {
            renderer.sceneArtifacts(for: item.message, rendered: rendered, visibleRect: visibleRect)
        }
    }

    private var renderer: VVChatMessageRenderer
    private(set) var currentStyle: VVChatTimelineStyle
    private(set) var contentWidth: CGFloat
    private lazy var messageBackend: ItemRendererBackend = MessageItemRendererBackend(renderer: renderer)

    init(style: VVChatTimelineStyle, contentWidth: CGFloat) {
        self.currentStyle = style
        self.contentWidth = contentWidth
        self.renderer = VVChatMessageRenderer(style: style, contentWidth: contentWidth)
    }

    func updateStyle(_ style: VVChatTimelineStyle) {
        currentStyle = style
        renderer.updateStyle(style)
    }

    func updateContentWidth(_ width: CGFloat) {
        contentWidth = width
        renderer.updateContentWidth(width)
    }

    func updateImageSize(url: String, size: CGSize) -> Bool {
        renderer.updateImageSize(url: url, size: size)
    }

    func prepareLayoutIfNeeded(
        for item: VVChatTimelineItem,
        requiresLayout: Bool
    ) async {
        await backend(for: item).prepareLayoutIfNeeded(for: item, requiresLayout: requiresLayout)
    }

    func prepareVisibleSceneIfNeeded(
        for item: VVChatTimelineItem,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) async {
        await backend(for: item).prepareVisibleSceneIfNeeded(
            for: item,
            rendered: rendered,
            visibleRect: visibleRect
        )
    }

    func prepareVisibleSelectionIfNeeded(
        for item: VVChatTimelineItem,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) async {
        await backend(for: item).prepareVisibleSelectionIfNeeded(
            for: item,
            rendered: rendered,
            visibleRect: visibleRect
        )
    }

    func trimCaches(keepingItemIDs: Set<String>) {
        renderer.trimCaches(keepingMessageIDs: keepingItemIDs)
    }

    func invalidate(messageID: String) {
        renderer.invalidate(messageID: messageID)
    }

    func invalidateRendered(messageID: String) {
        renderer.invalidateRendered(messageID: messageID)
    }

    func invalidateAll() {
        renderer.invalidateAll()
    }

    func debugSnapshot() -> VVChatMessageRenderer.DebugSnapshot {
        renderer.debugSnapshot()
    }

    private func backend(for item: VVChatTimelineItem) -> ItemRendererBackend {
        switch item.kind {
        case .message, .toolGroup, .toolCall, .summaryCard, .systemEvent, .diffCard, .customWidget:
            return messageBackend
        }
    }

    func renderedItem(for item: VVChatTimelineItem) -> VVChatRenderedMessage {
        backend(for: item).renderedItem(for: item)
    }

    func layoutSummary(for item: VVChatTimelineItem) -> VVChatMessageLayoutSummary {
        backend(for: item).layoutSummary(for: item)
    }

    func estimatedLayoutSummary(for item: VVChatTimelineItem) -> VVChatMessageLayoutSummary {
        backend(for: item).estimatedLayoutSummary(for: item)
    }

    func selectionHelper(
        for item: VVChatTimelineItem,
        rendered: VVChatRenderedMessage
    ) -> VVMarkdownSelectionHelper? {
        backend(for: item).selectionHelper(for: item, rendered: rendered)
    }

    func selectionArtifacts(
        for item: VVChatTimelineItem,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSelectionArtifacts? {
        backend(for: item).selectionArtifacts(for: item, rendered: rendered, visibleRect: visibleRect)
    }

    func contentSceneArtifacts(
        for item: VVChatTimelineItem,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSceneArtifacts? {
        backend(for: item).contentSceneArtifacts(for: item, rendered: rendered, visibleRect: visibleRect)
    }

    func sceneArtifacts(
        for item: VVChatTimelineItem,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSceneArtifacts? {
        backend(for: item).sceneArtifacts(for: item, rendered: rendered, visibleRect: visibleRect)
    }

#if os(macOS)
    func visibleRenderItem(
        for item: VVChatTimelineResolvedRenderItem,
        viewport: CGRect
    ) -> VVChatTimelineVisibleRenderItemUpdate {
        let resolvedFrame = item.layout.frame
        let resolvedContentOffset = item.layout.contentOffset
        let itemVisibleRect = viewport.offsetBy(
            dx: -resolvedFrame.origin.x - resolvedContentOffset.x,
            dy: -resolvedFrame.origin.y - resolvedContentOffset.y
        )
        let contentVisibleRect = item.item.message.state == .draft ? nil : itemVisibleRect

        var layers: [VVChatTimelineRenderLayer] = [
            VVChatTimelineRenderLayer(
                offset: resolvedContentOffset,
                scene: item.rendered.chromeScene,
                orderedPrimitiveIndices: item.rendered.chromeOrderedPrimitiveIndices,
                visibilityIndex: item.rendered.chromeVisibilityIndex
            )
        ]

        if let contentArtifacts = contentSceneArtifacts(
            for: item.item,
            rendered: item.rendered,
            visibleRect: contentVisibleRect
        ) {
            layers.append(
                VVChatTimelineRenderLayer(
                    offset: CGPoint(
                        x: resolvedContentOffset.x + item.rendered.selectionContentOffset.x,
                        y: resolvedContentOffset.y + item.rendered.selectionContentOffset.y
                    ),
                    scene: contentArtifacts.scene,
                    orderedPrimitiveIndices: contentArtifacts.orderedPrimitiveIndices,
                    visibilityIndex: contentArtifacts.visibilityIndex
                )
            )
        }

        return VVChatTimelineVisibleRenderItemUpdate(
            index: item.index,
            item: VVChatTimelineRenderItem(
                id: item.layout.id,
                frame: resolvedFrame,
                contentOffset: resolvedContentOffset,
                layers: layers
            ),
            imageURLs: Set(item.rendered.imageURLs)
        )
    }

    func visibleRenderSnapshot(
        for items: [VVChatTimelineResolvedRenderItem],
        range: Range<Int>,
        viewport: CGRect
    ) -> VVChatTimelineVisibleRenderSnapshot {
        guard !items.isEmpty else {
            return .empty
        }

        var itemsByIndex: [Int: VVChatTimelineRenderItem] = [:]
        itemsByIndex.reserveCapacity(items.count)
        var imageURLsByIndex: [Int: Set<String>] = [:]

        for item in items {
            let renderItem = visibleRenderItem(for: item, viewport: viewport)
            itemsByIndex[item.index] = renderItem.item
            if !renderItem.imageURLs.isEmpty {
                imageURLsByIndex[item.index] = renderItem.imageURLs
            }
        }

        return VVChatTimelineVisibleRenderSnapshot(
            range: range,
            itemsByIndex: itemsByIndex,
            imageURLsByIndex: imageURLsByIndex
        )
    }
#endif
}
