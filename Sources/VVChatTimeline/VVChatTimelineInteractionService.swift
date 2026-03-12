import CoreGraphics
import Foundation
import VVMarkdown
import VVMetalPrimitives

@MainActor
final class VVChatTimelineInteractionService {
    private struct SelectionHelperCacheKey: Hashable {
        let messageID: String
        let revision: Int
    }

    private struct SelectionContext {
        let documentPoint: CGPoint
        let itemIndex: Int
        let resolvedItem: VVChatTimelineResolvedRenderItem
        let artifacts: VVChatSelectionArtifacts
        let localPoint: CGPoint
    }

    private unowned let controller: VVChatTimelineController
    private let renderer: VVChatTimelineRendering
    private var selectionHelperCache: [SelectionHelperCacheKey: VVMarkdownSelectionHelper] = [:]
    private var selectionHelperCacheOrder: [SelectionHelperCacheKey] = []
    private let maxSelectionHelperCacheEntries = 8

    init(
        controller: VVChatTimelineController,
        renderer: VVChatTimelineRendering
    ) {
        self.controller = controller
        self.renderer = renderer
    }

    func clearCache() {
        selectionHelperCache.removeAll(keepingCapacity: true)
        selectionHelperCacheOrder.removeAll(keepingCapacity: true)
    }

    func invalidate(messageIDs: [String]) {
        guard !messageIDs.isEmpty else { return }
        let ids = Set(messageIDs)
        selectionHelperCache = selectionHelperCache.filter { !ids.contains($0.key.messageID) }
        selectionHelperCacheOrder.removeAll { ids.contains($0.messageID) }
    }

    func selectionQuads(
        for selection: VVTextSelection<ChatTextPosition>,
        itemIndex: Int,
        itemOffset: CGPoint,
        viewportRect: CGRect,
        color: SIMD4<Float>
    ) -> [VVQuadPrimitive] {
        guard let resolvedItem = controller.resolvedRenderItem(
            at: itemIndex,
            hydrateExactLayoutIfNeeded: true
        ) else {
            return []
        }

        let (start, end) = selection.ordered
        guard start.itemIndex <= itemIndex && end.itemIndex >= itemIndex else {
            return []
        }

        let contentOffset = resolvedItem.rendered.selectionContentOffset
        let localVisibleYRange = (
            viewportRect.minY - itemOffset.y - contentOffset.y
        )...(
            viewportRect.maxY - itemOffset.y - contentOffset.y
        )
        let artifacts = visibleSelectionArtifacts(
            for: resolvedItem,
            viewportRect: viewportRect
        )
        guard let artifacts else {
            return []
        }
        let helper = artifacts.helper

        let mdStart: MarkdownTextPosition
        let mdEnd: MarkdownTextPosition
        if start.itemIndex == itemIndex && end.itemIndex == itemIndex {
            guard let localStart = clippedMarkdownPosition(
                from: start.markdownPosition,
                artifacts: artifacts,
                preferLowerBound: true
            ), let localEnd = clippedMarkdownPosition(
                from: end.markdownPosition,
                artifacts: artifacts,
                preferLowerBound: false
            ) else {
                return []
            }
            mdStart = localStart
            mdEnd = localEnd
        } else if start.itemIndex == itemIndex {
            guard let localStart = clippedMarkdownPosition(
                from: start.markdownPosition,
                artifacts: artifacts,
                preferLowerBound: true
            ) else {
                return []
            }
            mdStart = localStart
            mdEnd = helper.findLastPosition() ?? localStart
        } else if end.itemIndex == itemIndex {
            guard let first = helper.findFirstPosition() else { return [] }
            mdStart = first
            guard let localEnd = clippedMarkdownPosition(
                from: end.markdownPosition,
                artifacts: artifacts,
                preferLowerBound: false
            ) else {
                return []
            }
            mdEnd = localEnd
        } else {
            guard let first = helper.findFirstPosition(),
                  let last = helper.findLastPosition() else {
                return []
            }
            mdStart = first
            mdEnd = last
        }

        return helper.selectionRects(
            from: mdStart,
            to: mdEnd,
            visibleYRange: localVisibleYRange
        ).map { rect in
            VVQuadPrimitive(
                frame: rect.offsetBy(dx: itemOffset.x + contentOffset.x, dy: itemOffset.y + contentOffset.y),
                color: color,
                cornerRadius: 2
            )
        }
    }

    func extractText(
        from start: ChatTextPosition,
        to end: ChatTextPosition
    ) -> String {
        guard controller.layoutCount > 0 else { return "" }
        var result: [String] = []

        for itemIndex in start.itemIndex...min(end.itemIndex, controller.layoutCount - 1) {
            guard let resolvedItem = controller.resolvedRenderItem(at: itemIndex),
                  let helper = cachedFullSelectionHelper(for: resolvedItem) else {
                continue
            }

            let mdStart: MarkdownTextPosition
            let mdEnd: MarkdownTextPosition
            if start.itemIndex == itemIndex && end.itemIndex == itemIndex {
                mdStart = start.markdownPosition
                mdEnd = end.markdownPosition
            } else if start.itemIndex == itemIndex {
                mdStart = start.markdownPosition
                mdEnd = helper.findLastPosition() ?? start.markdownPosition
            } else if end.itemIndex == itemIndex {
                mdStart = helper.findFirstPosition() ?? end.markdownPosition
                mdEnd = end.markdownPosition
            } else {
                guard let first = helper.findFirstPosition(),
                      let last = helper.findLastPosition() else {
                    continue
                }
                mdStart = first
                mdEnd = last
            }

            let itemText = helper.extractText(from: mdStart, to: mdEnd)
            if !itemText.isEmpty {
                result.append(itemText)
            }
        }

        return result.joined(separator: "\n\n")
    }

    func selectAllRange() -> VVTextSelection<ChatTextPosition>? {
        guard controller.layoutCount > 0 else { return nil }

        var firstPos: ChatTextPosition?
        for index in 0..<controller.layoutCount {
            guard let resolvedItem = controller.resolvedRenderItem(at: index),
                  let helper = cachedFullSelectionHelper(for: resolvedItem),
                  let pos = helper.findFirstPosition() else {
                continue
            }
            firstPos = ChatTextPosition(
                itemIndex: index,
                blockIndex: pos.blockIndex,
                runIndex: pos.runIndex,
                characterOffset: pos.characterOffset
            )
            break
        }

        var lastPos: ChatTextPosition?
        for index in stride(from: controller.layoutCount - 1, through: 0, by: -1) {
            guard let resolvedItem = controller.resolvedRenderItem(at: index),
                  let helper = cachedFullSelectionHelper(for: resolvedItem),
                  let pos = helper.findLastPosition() else {
                continue
            }
            lastPos = ChatTextPosition(
                itemIndex: index,
                blockIndex: pos.blockIndex,
                runIndex: pos.runIndex,
                characterOffset: pos.characterOffset
            )
            break
        }

        guard let firstPos, let lastPos else { return nil }
        return VVTextSelection(anchor: firstPos, active: lastPos)
    }

    func textPosition(
        atDocumentPoint documentPoint: CGPoint,
        viewportRect: CGRect,
        preferNearest: Bool
    ) -> ChatTextPosition? {
        let targetItemIndex: Int?
        if preferNearest {
            targetItemIndex = controller.nearestItemIndex(forDocumentY: documentPoint.y)
        } else {
            targetItemIndex = controller.itemIndex(containingDocumentY: documentPoint.y)
        }

        guard let targetItemIndex,
              let context = selectionContext(
                atDocumentPoint: documentPoint,
                itemIndex: targetItemIndex,
                viewportRect: viewportRect,
                hydrateExactLayoutIfNeeded: true
              ) else {
            return nil
        }

        let helper = context.artifacts.helper
        let markdownPosition = preferNearest
            ? helper.nearestTextPosition(to: context.localPoint)
            : helper.hitTest(at: context.localPoint)
        guard let mdPos = markdownPosition else { return nil }
        let absolute = absoluteMarkdownPosition(from: mdPos, blockRange: context.artifacts.blockRange)

        return ChatTextPosition(
            itemIndex: targetItemIndex,
            blockIndex: absolute.blockIndex,
            runIndex: absolute.runIndex,
            characterOffset: absolute.characterOffset
        )
    }

    func linkURL(
        atDocumentPoint documentPoint: CGPoint,
        viewportRect: CGRect
    ) -> String? {
        guard let itemIndex = controller.itemIndex(containingDocumentY: documentPoint.y),
              let context = selectionContext(
                atDocumentPoint: documentPoint,
                itemIndex: itemIndex,
                viewportRect: viewportRect,
                hydrateExactLayoutIfNeeded: true
              ) else {
            return nil
        }
        return context.artifacts.helper.linkURL(at: context.localPoint)
    }

    private func selectionContext(
        atDocumentPoint documentPoint: CGPoint,
        itemIndex: Int,
        viewportRect: CGRect,
        hydrateExactLayoutIfNeeded: Bool
    ) -> SelectionContext? {
        guard let resolvedItem = controller.resolvedRenderItem(
            at: itemIndex,
            hydrateExactLayoutIfNeeded: hydrateExactLayoutIfNeeded
        ), let artifacts = visibleSelectionArtifacts(
            for: resolvedItem,
            viewportRect: viewportRect
        ) else {
            return nil
        }

        let contentOffset = resolvedItem.rendered.selectionContentOffset
        let localPoint = CGPoint(
            x: documentPoint.x - resolvedItem.layout.frame.origin.x - resolvedItem.layout.contentOffset.x - contentOffset.x,
            y: documentPoint.y - resolvedItem.layout.frame.origin.y - resolvedItem.layout.contentOffset.y - contentOffset.y
        )

        return SelectionContext(
            documentPoint: documentPoint,
            itemIndex: itemIndex,
            resolvedItem: resolvedItem,
            artifacts: artifacts,
            localPoint: localPoint
        )
    }

    private func visibleSelectionArtifacts(
        for resolvedItem: VVChatTimelineResolvedRenderItem,
        viewportRect: CGRect
    ) -> VVChatSelectionArtifacts? {
        let contentOffset = resolvedItem.rendered.selectionContentOffset
        let localVisibleRect = CGRect(
            x: 0,
            y: viewportRect.minY - resolvedItem.layout.frame.origin.y - resolvedItem.layout.contentOffset.y - contentOffset.y,
            width: max(1, viewportRect.width),
            height: max(1, viewportRect.height)
        )
        return renderer.selectionArtifacts(
            for: resolvedItem.item,
            rendered: resolvedItem.rendered,
            visibleRect: localVisibleRect
        )
    }

    private func cachedFullSelectionHelper(
        for resolvedItem: VVChatTimelineResolvedRenderItem
    ) -> VVMarkdownSelectionHelper? {
        let key = SelectionHelperCacheKey(
            messageID: resolvedItem.layout.id,
            revision: resolvedItem.rendered.revision
        )
        if let cached = selectionHelperCache[key] {
            touchSelectionHelperCache(key)
            return cached
        }

        guard let helper = renderer.selectionHelper(
            for: resolvedItem.item,
            rendered: resolvedItem.rendered
        ) else {
            return nil
        }

        selectionHelperCache[key] = helper
        selectionHelperCacheOrder.removeAll { $0 == key }
        selectionHelperCacheOrder.append(key)
        while selectionHelperCacheOrder.count > maxSelectionHelperCacheEntries {
            let evicted = selectionHelperCacheOrder.removeFirst()
            selectionHelperCache.removeValue(forKey: evicted)
        }
        return helper
    }

    private func touchSelectionHelperCache(_ key: SelectionHelperCacheKey) {
        selectionHelperCacheOrder.removeAll { $0 == key }
        selectionHelperCacheOrder.append(key)
    }

    private func absoluteMarkdownPosition(
        from local: MarkdownTextPosition,
        blockRange: Range<Int>
    ) -> MarkdownTextPosition {
        MarkdownTextPosition(
            blockIndex: blockRange.lowerBound + local.blockIndex,
            runIndex: local.runIndex,
            characterOffset: local.characterOffset
        )
    }

    private func localMarkdownPosition(
        from absolute: MarkdownTextPosition,
        artifacts: VVChatSelectionArtifacts
    ) -> MarkdownTextPosition? {
        guard artifacts.blockRange.contains(absolute.blockIndex) else { return nil }
        return MarkdownTextPosition(
            blockIndex: absolute.blockIndex - artifacts.blockRange.lowerBound,
            runIndex: absolute.runIndex,
            characterOffset: absolute.characterOffset
        )
    }

    private func clippedMarkdownPosition(
        from absolute: MarkdownTextPosition,
        artifacts: VVChatSelectionArtifacts,
        preferLowerBound: Bool
    ) -> MarkdownTextPosition? {
        if let local = localMarkdownPosition(from: absolute, artifacts: artifacts) {
            return local
        }
        if absolute.blockIndex < artifacts.blockRange.lowerBound {
            return preferLowerBound ? artifacts.helper.findFirstPosition() : nil
        }
        if absolute.blockIndex >= artifacts.blockRange.upperBound {
            return preferLowerBound ? nil : artifacts.helper.findLastPosition()
        }
        return nil
    }
}
