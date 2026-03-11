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

    func trimCaches(keepingMessageIDs: Set<String>)
    func invalidate(messageID: String)
    func invalidateRendered(messageID: String)
    func invalidateAll()

    func debugSnapshot() -> VVChatMessageRenderer.DebugSnapshot
    func renderedMessage(for message: VVChatMessage) -> VVChatRenderedMessage
    func layoutSummary(for message: VVChatMessage) -> VVChatMessageLayoutSummary
    func estimatedLayoutSummary(for message: VVChatMessage) -> VVChatMessageLayoutSummary
    func selectionHelper(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage
    ) -> VVMarkdownSelectionHelper?
    func selectionArtifacts(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSelectionArtifacts?
    func contentSceneArtifacts(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSceneArtifacts?
    func sceneArtifacts(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSceneArtifacts?

#if os(macOS)
    func visibleRenderSnapshot(
        for items: [VVChatTimelineResolvedRenderItem],
        range: Range<Int>,
        viewport: CGRect
    ) -> VVChatTimelineVisibleRenderSnapshot
#endif
}

@MainActor
final class VVChatTimelineRenderService: VVChatTimelineRendering {
    private var renderer: VVChatMessageRenderer
    private(set) var currentStyle: VVChatTimelineStyle
    private(set) var contentWidth: CGFloat

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

    func trimCaches(keepingMessageIDs: Set<String>) {
        renderer.trimCaches(keepingMessageIDs: keepingMessageIDs)
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

    func renderedMessage(for message: VVChatMessage) -> VVChatRenderedMessage {
        renderer.renderedMessage(for: message)
    }

    func layoutSummary(for message: VVChatMessage) -> VVChatMessageLayoutSummary {
        renderer.layoutSummary(for: message)
    }

    func estimatedLayoutSummary(for message: VVChatMessage) -> VVChatMessageLayoutSummary {
        renderer.estimatedLayoutSummary(for: message)
    }

    func selectionHelper(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage
    ) -> VVMarkdownSelectionHelper? {
        renderer.selectionHelper(for: message, rendered: rendered)
    }

    func selectionArtifacts(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSelectionArtifacts? {
        renderer.selectionArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
    }

    func contentSceneArtifacts(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSceneArtifacts? {
        renderer.contentSceneArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
    }

    func sceneArtifacts(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSceneArtifacts? {
        renderer.sceneArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
    }

#if os(macOS)
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
        var imageURLs = Set<String>()

        for item in items {
            let resolvedFrame = item.layout.frame
            let resolvedContentOffset = item.layout.contentOffset
            let itemVisibleRect = viewport.offsetBy(
                dx: -resolvedFrame.origin.x - resolvedContentOffset.x,
                dy: -resolvedFrame.origin.y - resolvedContentOffset.y
            )

            var layers: [VVChatTimelineRenderLayer] = [
                VVChatTimelineRenderLayer(
                    offset: resolvedContentOffset,
                    scene: item.rendered.chromeScene,
                    orderedPrimitiveIndices: item.rendered.chromeOrderedPrimitiveIndices,
                    visibilityIndex: item.rendered.chromeVisibilityIndex
                )
            ]

            if let contentArtifacts = contentSceneArtifacts(
                for: item.item.message,
                rendered: item.rendered,
                visibleRect: itemVisibleRect
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

            itemsByIndex[item.index] = VVChatTimelineRenderItem(
                id: item.layout.id,
                frame: resolvedFrame,
                contentOffset: resolvedContentOffset,
                layers: layers
            )
            imageURLs.formUnion(item.rendered.imageURLs)
        }

        return VVChatTimelineVisibleRenderSnapshot(
            range: range,
            itemsByIndex: itemsByIndex,
            imageURLs: imageURLs
        )
    }
#endif
}
