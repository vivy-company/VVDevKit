import CoreGraphics
import Foundation
import VVMarkdown
import VVMetalPrimitives

@MainActor
public final class VVChatTimelineController {
    public typealias CustomEntryMessageMapper = @MainActor (VVCustomTimelineEntry) -> VVChatMessage

    public enum UpdateCause: Sendable {
        case rebuild
        case tailAppend
        case singleReplace
        case rangeReplace
        case streamUpdate
        case relayout
        case hydrateCorrection
        case jumpToLatest
    }

    public enum FollowPolicy: Sendable {
        case none
        case preservePinnedBottom
        case forceImmediateBottom
    }

    public struct Update {
        public var insertedIndexes: IndexSet
        public var updatedIndexes: IndexSet
        public var removedIndexes: IndexSet
        public var totalHeight: CGFloat
        public var heightDelta: CGFloat
        public var changedIndex: Int?
        public var shouldScrollToBottom: Bool
        public var cause: UpdateCause
        public var followPolicy: FollowPolicy
        public var layoutTransition: PendingLayoutTransition?
        public var hasUnreadNewContent: Bool

        public init(
            insertedIndexes: IndexSet = [],
            updatedIndexes: IndexSet = [],
            removedIndexes: IndexSet = [],
            totalHeight: CGFloat = 0,
            heightDelta: CGFloat = 0,
            changedIndex: Int? = nil,
            shouldScrollToBottom: Bool = false,
            cause: UpdateCause = .rebuild,
            followPolicy: FollowPolicy = .none,
            layoutTransition: PendingLayoutTransition? = nil,
            hasUnreadNewContent: Bool = false
        ) {
            self.insertedIndexes = insertedIndexes
            self.updatedIndexes = updatedIndexes
            self.removedIndexes = removedIndexes
            self.totalHeight = totalHeight
            self.heightDelta = heightDelta
            self.changedIndex = changedIndex
            self.shouldScrollToBottom = shouldScrollToBottom
            self.cause = cause
            self.followPolicy = followPolicy
            self.layoutTransition = layoutTransition
            self.hasUnreadNewContent = hasUnreadNewContent
        }
    }

    public struct ItemLayout {
        public var id: String
        public var frame: CGRect
        public var contentOffset: CGPoint
        public var isDraft: Bool
        public var revision: Int
        public var isExact: Bool
    }

    /// Pending layout transition state, consumed by the view on next update.
    public struct PendingLayoutTransition {
        public let anchorID: String
        public let anchorY: CGFloat
        public let previousTotalHeight: CGFloat
    }

    public private(set) var items: [VVChatTimelineItemModel] = []
    public private(set) var entries: [VVChatTimelineEntry] = []
    public private(set) var messages: [VVChatMessage] = []
    public private(set) var totalHeight: CGFloat = 0
    public private(set) var state: VVChatTimelineState

    public var layouts: [ItemLayout] {
        layoutEngine.layouts()
    }

    public var onUpdate: ((Update) -> Void)?

    private var style: VVChatTimelineStyle
    private var renderWidth: CGFloat
    private let draftThrottler = VVChatDraftThrottler()
    private var activeDraftID: String?
    private let coreStore = VVChatTimelineCoreStore()
    private var renderService: VVChatTimelineRenderService
    private var layoutEngine: VVChatTimelineLayoutEngine
    private var requestedLayoutTransition: PendingLayoutTransition?
    private lazy var interactionService = VVChatTimelineInteractionService(
        controller: self,
        renderer: renderService
    )

    public init(style: VVChatTimelineStyle = .init(), renderWidth: CGFloat = 0) {
        self.style = style
        self.renderWidth = renderWidth
        self.renderService = VVChatTimelineRenderService(style: style, contentWidth: renderWidth)
        self.layoutEngine = VVChatTimelineLayoutEngine(style: style, renderWidth: renderWidth)
        self.state = VVChatTimelineState(pinThreshold: style.pinThreshold)
    }

    public var currentStyle: VVChatTimelineStyle {
        style
    }

    var hasActiveDraft: Bool {
        activeDraftID != nil
    }

    public func updateStyle(_ style: VVChatTimelineStyle) {
        self.style = style
        state.pinThreshold = style.pinThreshold
        renderService.updateStyle(style)
        layoutEngine.updateStyle(style)
        interactionService.clearCache()
        rebuildLayouts(shouldScrollToBottom: state.shouldAutoFollow)
    }

    public func updateRenderWidth(_ width: CGFloat) {
        guard width > 0 else { return }
        let normalizedWidth = max(1, (width * 2).rounded() / 2)
        guard abs(normalizedWidth - renderWidth) > 0.5 else { return }
        renderWidth = normalizedWidth
        renderService.updateContentWidth(normalizedWidth)
        layoutEngine.updateRenderWidth(normalizedWidth)
        interactionService.clearCache()
        rebuildLayouts(shouldScrollToBottom: state.shouldAutoFollow)
    }

    public func setMessages(_ newMessages: [VVChatMessage], scrollToBottom: Bool = true) {
        setItems(newMessages.map(VVChatTimelineItemModel.init(message:)), scrollToBottom: scrollToBottom)
    }

    /// Call before `setEntries` to animate the layout transition.
    /// Pass the ID of the item at or above the insertion/removal point.
    public func prepareLayoutTransition(anchorItemID: String) {
        let anchorY: CGFloat
        if let index = indexForItemID(anchorItemID), let layout = itemLayout(at: index) {
            anchorY = layout.frame.origin.y
        } else {
            anchorY = 0
        }
        requestedLayoutTransition = PendingLayoutTransition(
            anchorID: anchorItemID,
            anchorY: anchorY,
            previousTotalHeight: totalHeight
        )
    }

    public func setEntries(
        _ newEntries: [VVChatTimelineEntry],
        scrollToBottom: Bool = true,
        customEntryMessageMapper: CustomEntryMessageMapper? = nil
    ) {
        setItems(
            newEntries.map(coreStore.itemModel),
            scrollToBottom: scrollToBottom,
            customEntryMessageMapper: customEntryMessageMapper
        )
    }

    public func setItems(
        _ newItems: [VVChatTimelineItemModel],
        scrollToBottom: Bool = true,
        customEntryMessageMapper: CustomEntryMessageMapper? = nil
    ) {
        draftThrottler.cancel()
        activeDraftID = nil

        coreStore.configure(customEntryMessageMapper: customEntryMessageMapper)
        syncPublicState(from: coreStore.setItems(newItems))
        renderService.invalidateAll()
        interactionService.clearCache()

        if scrollToBottom {
            state.hasUnreadNewContent = false
        }

        rebuildLayouts(shouldScrollToBottom: scrollToBottom)
    }

    public func appendMessage(_ message: VVChatMessage) {
        appendItem(VVChatTimelineItemModel(message: message))
    }

    public func appendCustomEntry(_ entry: VVCustomTimelineEntry) {
        appendItem(VVChatTimelineItemModel(customEntry: entry))
    }

    public func appendItem(_ item: VVChatTimelineItemModel) {
        let oldTotalHeight = totalHeight
        preparePendingTailTransition(previousTotalHeight: oldTotalHeight)

        let snapshot = coreStore.appendItem(item)
        syncPublicState(from: snapshot)
        if let item = snapshot.items.last {
            let shouldMeasureExactly = shouldMeasureTailItemExactly(item)
            layoutEngine.append(
                item: item,
                exact: shouldMeasureExactly,
                renderer: renderService
            )
            if item.message.state == .draft,
               shouldEagerlyPrepareDraftTailItem(at: snapshot.count - 1) {
                Task { @MainActor [weak self] in
                    guard let self else { return }
                    await self.renderService.prepareLayoutIfNeeded(for: item, requiresLayout: true)
                }
            }
        }
        totalHeight = layoutEngine.totalHeight

        let shouldFollow = state.shouldAutoFollow
        if !shouldFollow {
            state.hasUnreadNewContent = true
        }

        let index = max(0, snapshot.count - 1)
        emitUpdate(
            Update(
                insertedIndexes: IndexSet(integer: index),
                totalHeight: totalHeight,
                heightDelta: totalHeight - oldTotalHeight,
                changedIndex: index,
                shouldScrollToBottom: shouldFollow,
                cause: .tailAppend,
                followPolicy: shouldFollow ? .preservePinnedBottom : .none,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    public func beginStreamingAssistantMessage(id: String = UUID().uuidString, content: String = "") -> String {
        if activeDraftID != nil && activeDraftID != id {
            draftThrottler.cancel()
        }
        let message = VVChatMessage(id: id, role: .assistant, state: .draft, content: content, revision: 0)
        activeDraftID = id
        appendMessage(message)
        return id
    }

    public func updateDraftMessage(id: String, content: String, throttle: Bool = true) {
        guard let index = indexForItemID(id) else { return }
        guard messages[index].state == .draft else { return }
        if throttle {
            activeDraftID = id
            draftThrottler.schedule(content) { [weak self] text in
                Task { @MainActor in
                    guard let self else { return }
                    guard self.activeDraftID == id else { return }
                    self.applyDraftUpdate(id: id, content: text)
                }
            }
        } else {
            applyDraftUpdate(id: id, content: content)
        }
    }

    public func appendToDraftMessage(id: String, chunk: String, throttle: Bool = false) {
        guard !chunk.isEmpty else { return }
        guard let index = indexForItemID(id) else { return }
        guard messages[index].state == .draft else { return }
        let appended = messages[index].content + chunk
        updateDraftMessage(id: id, content: appended, throttle: throttle)
    }

    public func finalizeMessage(id: String, content: String) {
        guard let index = indexForItemID(id) else { return }
        renderService.invalidate(messageID: id)
        interactionService.invalidate(messageIDs: [id])

        var message = messages[index]
        message.state = .final
        message.content = content
        message.revision += 1
        syncPublicState(from: coreStore.syncMessage(message))

        if activeDraftID == id {
            draftThrottler.cancel()
            activeDraftID = nil
        }

        updateMessageLayout(
            at: index,
            shouldScrollToBottom: state.shouldAutoFollow,
            markUnread: true,
            cause: .streamUpdate,
            exactLayout: shouldMeasureTailItemExactly(at: index)
        )
    }

    public func replaceEntry(
        id: String,
        with entry: VVChatTimelineEntry,
        scrollToBottom: Bool? = nil,
        markUnread: Bool = true
    ) {
        replaceItem(
            id: id,
            with: coreStore.itemModel(for: entry),
            scrollToBottom: scrollToBottom,
            markUnread: markUnread
        )
    }

    public func replaceItem(
        id: String,
        with item: VVChatTimelineItemModel,
        scrollToBottom: Bool? = nil,
        markUnread: Bool = true
    ) {
        guard let index = indexForItemID(id) else { return }

        let oldTotalHeight = totalHeight
        let previousMessageID = messages[index].id
        renderService.invalidate(messageID: previousMessageID)
        interactionService.invalidate(messageIDs: [previousMessageID, id])

        syncPublicState(from: coreStore.replaceItem(id: id, with: item))
        if previousMessageID != messages[index].id {
            renderService.invalidate(messageID: messages[index].id)
            interactionService.invalidate(messageIDs: [messages[index].id])
        }

        if activeDraftID == id, messages[index].state != .draft {
            draftThrottler.cancel()
            activeDraftID = nil
        }

        guard let item = coreStore.snapshot.item(at: index) else { return }
        layoutEngine.replace(
            range: index..<(index + 1),
            items: [item],
            exact: item.message.state != .draft,
            renderer: renderService
        )
        totalHeight = layoutEngine.totalHeight

        let shouldFollow = scrollToBottom ?? state.shouldAutoFollow
        if markUnread && !shouldFollow {
            state.hasUnreadNewContent = true
        } else if shouldFollow {
            state.hasUnreadNewContent = false
        }

        emitUpdate(
            Update(
                updatedIndexes: IndexSet(integer: index),
                totalHeight: totalHeight,
                heightDelta: totalHeight - oldTotalHeight,
                changedIndex: index,
                shouldScrollToBottom: shouldFollow,
                cause: .singleReplace,
                followPolicy: shouldFollow ? .preservePinnedBottom : .none,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    public func replaceEntries(
        in range: Range<Int>,
        with newEntries: [VVChatTimelineEntry],
        scrollToBottom: Bool? = nil,
        markUnread: Bool = true
    ) {
        replaceItems(
            in: range,
            with: newEntries.map(coreStore.itemModel),
            scrollToBottom: scrollToBottom,
            markUnread: markUnread
        )
    }

    public func replaceItems(
        in range: Range<Int>,
        with newItems: [VVChatTimelineItemModel],
        scrollToBottom: Bool? = nil,
        markUnread: Bool = true
    ) {
        let clampedLower = max(0, min(range.lowerBound, entries.count))
        let clampedUpper = max(clampedLower, min(range.upperBound, entries.count))
        let clampedRange = clampedLower..<clampedUpper

        let oldTotalHeight = totalHeight
        let oldMessages = Array(messages[clampedRange])
        let oldCount = oldMessages.count
        let newCount = newItems.count
        let shouldFollow = scrollToBottom ?? state.shouldAutoFollow

        for message in oldMessages {
            renderService.invalidate(messageID: message.id)
        }
        interactionService.invalidate(messageIDs: oldMessages.map(\.id))

        syncPublicState(from: coreStore.replaceItems(in: clampedRange, with: newItems))
        let replacementUpperBound = clampedLower + newCount
        let replacementItems = replacementUpperBound <= coreStore.snapshot.count
            ? Array(coreStore.snapshot.items[clampedLower..<replacementUpperBound])
            : []
        layoutEngine.replace(
            range: clampedRange,
            items: replacementItems,
            renderer: renderService
        )
        totalHeight = layoutEngine.totalHeight

        if let activeDraftID,
           !messages.contains(where: { $0.id == activeDraftID && $0.state == .draft }) {
            draftThrottler.cancel()
            self.activeDraftID = nil
        }

        if markUnread && !shouldFollow {
            state.hasUnreadNewContent = true
        } else if shouldFollow {
            state.hasUnreadNewContent = false
        }

        let overlappingCount = min(oldCount, newCount)
        let insertedStart = clampedLower + overlappingCount
        let removedStart = clampedLower + newCount
        emitUpdate(
            Update(
                insertedIndexes: newCount > oldCount
                    ? IndexSet(integersIn: insertedStart..<(clampedLower + newCount))
                    : [],
                updatedIndexes: overlappingCount > 0
                    ? IndexSet(integersIn: clampedLower..<(clampedLower + overlappingCount))
                    : [],
                removedIndexes: oldCount > newCount
                    ? IndexSet(integersIn: removedStart..<(clampedLower + oldCount))
                    : [],
                totalHeight: totalHeight,
                heightDelta: totalHeight - oldTotalHeight,
                changedIndex: clampedLower < layoutCount ? clampedLower : max(0, layoutCount - 1),
                shouldScrollToBottom: shouldFollow,
                cause: .rangeReplace,
                followPolicy: shouldFollow ? .preservePinnedBottom : .none,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    public func markUserInteraction(_ isInteracting: Bool) {
        state.userIsInteracting = isInteracting
    }

    public func updateViewportMode(distanceFromBottom: CGFloat) {
        state.updateViewportMode(distanceFromBottom: distanceFromBottom)
    }

    public func jumpToLatest() {
        state.hasUnreadNewContent = false
        state.viewportMode = .liveTail
        state.userIsInteracting = false
        emitUpdate(
            Update(
                totalHeight: totalHeight,
                shouldScrollToBottom: true,
                cause: .jumpToLatest,
                followPolicy: .forceImmediateBottom,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    public func updateImageSize(url: String, size: CGSize) {
        guard renderService.updateImageSize(url: url, size: size) else { return }
        let affectedMessageIDs = layoutEngine.itemIDs(forImageURL: url)
        interactionService.invalidate(messageIDs: affectedMessageIDs)
        let sorted = affectedMessageIDs.compactMap(indexForItemID).sorted()
        relayoutMessages(
            at: sorted,
            shouldScrollToBottom: state.shouldAutoFollow,
            markUnread: false,
            preservePreparedMarkdown: true
        )
    }

    public func itemLayout(at index: Int) -> ItemLayout? {
        layoutEngine.itemLayout(at: index)
    }

    public var layoutCount: Int {
        layoutEngine.layoutCount
    }

    func visibleLayoutRange(in viewport: CGRect, overscan: CGFloat) -> Range<Int> {
        layoutEngine.visibleLayoutRange(in: viewport, overscan: overscan)
    }

    @discardableResult
    func hydrateExactLayouts(in viewport: CGRect, overscan: CGFloat) -> Bool {
        hydrateExactLayouts(in: visibleLayoutRange(in: viewport, overscan: overscan))
    }

    @discardableResult
    func hydrateExactLayoutsSilently(in viewport: CGRect, overscan: CGFloat) -> Bool {
        hydrateExactLayouts(in: visibleLayoutRange(in: viewport, overscan: overscan), shouldEmitUpdate: false)
    }

    func prepareExactLayouts(in viewport: CGRect, overscan: CGFloat) async {
        let range = visibleLayoutRange(in: viewport, overscan: overscan)
        guard !range.isEmpty else { return }

        let candidates = range.compactMap { index -> VVChatTimelineItem? in
            guard let layout = itemLayout(at: index),
                  !layout.isExact,
                  let item = coreStore.snapshot.item(at: index) else {
                return nil
            }
            return item
        }

        for item in candidates {
            await renderService.prepareLayoutIfNeeded(for: item, requiresLayout: true)
        }
    }

    func prepareVisibleSceneArtifacts(in viewport: CGRect, overscan: CGFloat) async {
        let range = visibleLayoutRange(in: viewport, overscan: overscan)
        guard !range.isEmpty else { return }

        let resolvedItems = range.compactMap { resolvedRenderItem(at: $0) }
        for resolvedItem in resolvedItems {
            let itemVisibleRect = viewport.offsetBy(
                dx: -resolvedItem.layout.frame.origin.x - resolvedItem.layout.contentOffset.x,
                dy: -resolvedItem.layout.frame.origin.y - resolvedItem.layout.contentOffset.y
            )
            let contentVisibleRect = resolvedItem.item.message.state == .draft ? nil : itemVisibleRect
            await renderService.prepareVisibleSceneIfNeeded(
                for: resolvedItem.item,
                rendered: resolvedItem.rendered,
                visibleRect: contentVisibleRect
            )
            await renderService.prepareVisibleSelectionIfNeeded(
                for: resolvedItem.item,
                rendered: resolvedItem.rendered,
                visibleRect: contentVisibleRect
            )
        }
    }

    @discardableResult
    func hydrateExactLayout(at index: Int) -> Bool {
        hydrateExactLayouts(in: index..<(index + 1))
    }

    func itemIndex(containingDocumentY y: CGFloat) -> Int? {
        layoutEngine.itemIndex(containingDocumentY: y)
    }

    func nearestItemIndex(forDocumentY y: CGFloat) -> Int? {
        layoutEngine.nearestItemIndex(forDocumentY: y)
    }

    public func entry(at index: Int) -> VVChatTimelineEntry? {
        guard entries.indices.contains(index) else { return nil }
        return entries[index]
    }

    public func renderedMessage(for id: String) -> VVChatRenderedMessage? {
        guard let index = indexForItemID(id),
              let item = coreStore.snapshot.item(at: index) else { return nil }
        return renderService.renderedItem(for: item)
    }

    public func renderedMessage(at index: Int) -> VVChatRenderedMessage? {
        guard let item = coreStore.snapshot.item(at: index) else { return nil }
        return renderService.renderedItem(for: item)
    }

    func resolvedRenderItem(
        at index: Int,
        hydrateExactLayoutIfNeeded: Bool = false
    ) -> VVChatTimelineResolvedRenderItem? {
        guard coreStore.snapshot.items.indices.contains(index) else { return nil }
        if hydrateExactLayoutIfNeeded,
           let existingLayout = itemLayout(at: index),
           !existingLayout.isExact {
            _ = hydrateExactLayout(at: index)
        }
        guard let item = coreStore.snapshot.item(at: index),
              let layout = itemLayout(at: index) else {
            return nil
        }
        let rendered = renderService.renderedItem(for: item)
        return VVChatTimelineResolvedRenderItem(
            index: index,
            item: item,
            layout: layout,
            rendered: rendered
        )
    }

#if os(macOS)
    func visibleRenderItem(
        at index: Int,
        viewport: CGRect,
        hydrateExactLayoutIfNeeded: Bool = false
    ) -> VVChatTimelineVisibleRenderItemUpdate? {
        guard let resolvedItem = resolvedRenderItem(
            at: index,
            hydrateExactLayoutIfNeeded: hydrateExactLayoutIfNeeded
        ) else {
            return nil
        }
        return renderService.visibleRenderItem(for: resolvedItem, viewport: viewport)
    }

    func visibleRenderSnapshot(
        in viewport: CGRect,
        overscan: CGFloat,
        shouldHydrateExactLayouts: Bool
    ) -> VVChatTimelineVisibleRenderSnapshot {
        if shouldHydrateExactLayouts {
            _ = hydrateExactLayouts(in: viewport, overscan: overscan)
        }
        let range = visibleLayoutRange(in: viewport, overscan: overscan)
        guard !range.isEmpty else { return .empty }
        let resolvedItems = range.compactMap { resolvedRenderItem(at: $0) }
        return renderService.visibleRenderSnapshot(
            for: resolvedItems,
            range: range,
            viewport: viewport
        )
    }
#endif

    public func debugSnapshot() -> VVChatMessageRenderer.DebugSnapshot {
        renderService.debugSnapshot()
    }

    public func debugExactLayoutCount() -> Int {
        layoutEngine.debugExactLayoutCount()
    }

    func sceneArtifacts(at index: Int, visibleRect: CGRect?) -> VVChatSceneArtifacts? {
        guard let item = coreStore.snapshot.item(at: index) else { return nil }
        let rendered = renderService.renderedItem(for: item)
        return renderService.sceneArtifacts(for: item, rendered: rendered, visibleRect: visibleRect)
    }

    func contentSceneArtifacts(at index: Int, visibleRect: CGRect?) -> VVChatSceneArtifacts? {
        guard let item = coreStore.snapshot.item(at: index) else { return nil }
        let rendered = renderService.renderedItem(for: item)
        return renderService.contentSceneArtifacts(for: item, rendered: rendered, visibleRect: visibleRect)
    }

    func selectionHelper(at index: Int) -> VVMarkdownSelectionHelper? {
        guard let item = coreStore.snapshot.item(at: index) else { return nil }
        let rendered = renderService.renderedItem(for: item)
        return renderService.selectionHelper(for: item, rendered: rendered)
    }

    func selectionArtifacts(at index: Int, visibleRect: CGRect?) -> VVChatSelectionArtifacts? {
        guard let item = coreStore.snapshot.item(at: index) else { return nil }
        let rendered = renderService.renderedItem(for: item)
        return renderService.selectionArtifacts(for: item, rendered: rendered, visibleRect: visibleRect)
    }

    func invalidateInteractionCaches(for messageIDs: [String]) {
        interactionService.invalidate(messageIDs: messageIDs)
    }

    func selectionQuads(
        for selection: VVTextSelection<ChatTextPosition>,
        itemAt index: Int,
        itemOffset: CGPoint,
        viewportRect: CGRect,
        color: SIMD4<Float>
    ) -> [VVQuadPrimitive] {
        interactionService.selectionQuads(
            for: selection,
            itemIndex: index,
            itemOffset: itemOffset,
            viewportRect: viewportRect,
            color: color
        )
    }

    func extractText(
        from start: ChatTextPosition,
        to end: ChatTextPosition
    ) -> String {
        interactionService.extractText(from: start, to: end)
    }

    func selectAllTextRange() -> VVTextSelection<ChatTextPosition>? {
        interactionService.selectAllRange()
    }

    func textPosition(
        atDocumentPoint documentPoint: CGPoint,
        viewportRect: CGRect,
        preferNearest: Bool
    ) -> ChatTextPosition? {
        interactionService.textPosition(
            atDocumentPoint: documentPoint,
            viewportRect: viewportRect,
            preferNearest: preferNearest
        )
    }

    func linkURL(
        atDocumentPoint documentPoint: CGPoint,
        viewportRect: CGRect
    ) -> String? {
        interactionService.linkURL(
            atDocumentPoint: documentPoint,
            viewportRect: viewportRect
        )
    }

    func trimCaches(in viewport: CGRect, overscan: CGFloat, itemPadding: Int = 12) {
        layoutEngine.trimCaches(
            in: viewport,
            overscan: overscan,
            itemPadding: itemPadding,
            renderer: renderService
        )
    }

    func indexForLayout(id: String) -> Int? {
        indexForItemID(id)
    }

    private func applyDraftUpdate(id: String, content: String) {
        guard let index = indexForItemID(id) else { return }
        guard messages[index].state == .draft else { return }

        renderService.invalidateRendered(messageID: id)
        interactionService.invalidate(messageIDs: [id])
        var message = messages[index]
        message.content = content
        message.revision += 1
        syncPublicState(from: coreStore.syncMessage(message))
        if let item = coreStore.snapshot.item(at: index) {
            if shouldEagerlyPrepareDraftTailItem(at: index) {
                Task { @MainActor [weak self] in
                    guard let self else { return }
                    await self.renderService.prepareLayoutIfNeeded(for: item, requiresLayout: true)
                }
            }
        }

        updateMessageLayout(
            at: index,
            shouldScrollToBottom: state.shouldAutoFollow,
            markUnread: true,
            cause: .streamUpdate,
            exactLayout: false
        )
    }

    private func updateMessageLayout(
        at index: Int,
        shouldScrollToBottom: Bool,
        markUnread: Bool,
        cause: UpdateCause? = nil,
        exactLayout: Bool = true
    ) {
        guard let item = coreStore.snapshot.item(at: index) else { return }
        let delta = layoutEngine.updateLayout(
            at: index,
            item: item,
            exact: exactLayout,
            renderer: renderService
        )
        totalHeight = layoutEngine.totalHeight

        if markUnread && !shouldScrollToBottom {
            state.hasUnreadNewContent = true
        }

        emitUpdate(
            Update(
                updatedIndexes: IndexSet(integer: index),
                totalHeight: totalHeight,
                heightDelta: delta,
                changedIndex: index,
                shouldScrollToBottom: shouldScrollToBottom,
                cause: cause ?? (item.message.state == .draft ? .streamUpdate : .singleReplace),
                followPolicy: shouldScrollToBottom ? .preservePinnedBottom : .none,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    private func relayoutMessages(
        at indexes: [Int],
        shouldScrollToBottom: Bool,
        markUnread: Bool,
        preservePreparedMarkdown: Bool = false
    ) {
        guard !indexes.isEmpty else { return }

        let uniqueSorted = Array(Set(indexes)).sorted()
        for index in uniqueSorted where messages.indices.contains(index) {
            guard let item = coreStore.snapshot.item(at: index) else { continue }
            if preservePreparedMarkdown {
                renderService.invalidateRendered(messageID: item.id)
            } else {
                renderService.invalidate(messageID: item.id)
            }
        }

        let mutation = layoutEngine.relayout(
            indexes: uniqueSorted,
            items: coreStore.snapshot.items,
            renderer: renderService
        )
        totalHeight = layoutEngine.totalHeight

        if markUnread && !shouldScrollToBottom {
            state.hasUnreadNewContent = true
        }

        emitUpdate(
            Update(
                updatedIndexes: mutation.updatedIndexes,
                totalHeight: totalHeight,
                heightDelta: mutation.totalDelta,
                changedIndex: mutation.updatedIndexes.first ?? uniqueSorted.first,
                shouldScrollToBottom: shouldScrollToBottom,
                cause: .relayout,
                followPolicy: shouldScrollToBottom ? .preservePinnedBottom : .none,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    private func rebuildLayouts(shouldScrollToBottom: Bool) {
        layoutEngine.reset(items: coreStore.snapshot.items, renderer: renderService)
        totalHeight = layoutEngine.totalHeight
        emitUpdate(
            Update(
                insertedIndexes: IndexSet(integersIn: 0..<layoutCount),
                totalHeight: totalHeight,
                shouldScrollToBottom: shouldScrollToBottom,
                cause: .rebuild,
                followPolicy: shouldScrollToBottom ? .forceImmediateBottom : .none,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    @discardableResult
    private func hydrateExactLayouts(in range: Range<Int>) -> Bool {
        hydrateExactLayouts(in: range, shouldEmitUpdate: true)
    }

    @discardableResult
    private func hydrateExactLayouts(in range: Range<Int>, shouldEmitUpdate: Bool) -> Bool {
        let mutation = layoutEngine.hydrateExactLayouts(
            in: range,
            items: coreStore.snapshot.items,
            renderer: renderService
        )
        guard !mutation.updatedIndexes.isEmpty else { return false }
        totalHeight = layoutEngine.totalHeight
        if shouldEmitUpdate {
            emitUpdate(
                Update(
                    updatedIndexes: mutation.updatedIndexes,
                    totalHeight: totalHeight,
                    heightDelta: mutation.totalDelta,
                    changedIndex: mutation.updatedIndexes.first,
                    shouldScrollToBottom: false,
                    cause: .hydrateCorrection,
                    followPolicy: .none,
                    hasUnreadNewContent: state.hasUnreadNewContent
                )
            )
        }
        return true
    }

    private func preparePendingTailTransition(previousTotalHeight: CGFloat) {
        if let lastIndex = (0..<layoutCount).last,
           let anchorLayout = itemLayout(at: lastIndex) {
            requestedLayoutTransition = PendingLayoutTransition(
                anchorID: anchorLayout.id,
                anchorY: anchorLayout.frame.origin.y,
                previousTotalHeight: previousTotalHeight
            )
        }
    }

    private func emitUpdate(_ update: Update) {
        let resolved = VVChatTimelineUpdateSemantics.resolved(
            update: update,
            requestedLayoutTransition: requestedLayoutTransition
        )
        requestedLayoutTransition = nil
        onUpdate?(resolved)
    }

    private func indexForItemID(_ id: String) -> Int? {
        coreStore.snapshot.index(forItemID: id)
    }

    private func syncPublicState(from snapshot: VVChatTimelineCoreSnapshot) {
        items = snapshot.itemModels
        entries = snapshot.entries
        messages = snapshot.messages
    }

    private func shouldMeasureTailItemExactly(_ item: VVChatTimelineItem) -> Bool {
        item.message.state != .draft && state.isLiveTail
    }

    private func shouldMeasureTailItemExactly(at index: Int) -> Bool {
        guard let item = coreStore.snapshot.item(at: index) else { return false }
        return shouldMeasureTailItemExactly(item)
    }

    private func shouldEagerlyPrepareDraftTailItem(at index: Int) -> Bool {
        guard coreStore.snapshot.items.indices.contains(index),
              coreStore.snapshot.items[index].message.state == .draft else {
            return false
        }
        return state.isLiveTail || index < coreStore.snapshot.count - 1
    }
}
