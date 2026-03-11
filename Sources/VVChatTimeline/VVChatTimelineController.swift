import CoreGraphics
import Foundation
import VVMarkdown

@MainActor
public final class VVChatTimelineController {
    public typealias CustomEntryMessageMapper = @MainActor (VVCustomTimelineEntry) -> VVChatMessage

    public struct Update {
        public var insertedIndexes: IndexSet
        public var updatedIndexes: IndexSet
        public var removedIndexes: IndexSet
        public var totalHeight: CGFloat
        public var heightDelta: CGFloat
        public var changedIndex: Int?
        public var shouldScrollToBottom: Bool
        public var hasUnreadNewContent: Bool

        public init(
            insertedIndexes: IndexSet = [],
            updatedIndexes: IndexSet = [],
            removedIndexes: IndexSet = [],
            totalHeight: CGFloat = 0,
            heightDelta: CGFloat = 0,
            changedIndex: Int? = nil,
            shouldScrollToBottom: Bool = false,
            hasUnreadNewContent: Bool = false
        ) {
            self.insertedIndexes = insertedIndexes
            self.updatedIndexes = updatedIndexes
            self.removedIndexes = removedIndexes
            self.totalHeight = totalHeight
            self.heightDelta = heightDelta
            self.changedIndex = changedIndex
            self.shouldScrollToBottom = shouldScrollToBottom
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

    public private(set) var entries: [VVChatTimelineEntry] = []
    public private(set) var messages: [VVChatMessage] = []
    public private(set) var totalHeight: CGFloat = 0
    public private(set) var state: VVChatTimelineState
    public internal(set) var pendingLayoutTransition: PendingLayoutTransition?

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

    public func updateStyle(_ style: VVChatTimelineStyle) {
        self.style = style
        state.pinThreshold = style.pinThreshold
        renderService.updateStyle(style)
        layoutEngine.updateStyle(style)
        rebuildLayouts(shouldScrollToBottom: state.shouldAutoFollow)
    }

    public func updateRenderWidth(_ width: CGFloat) {
        guard width > 0 else { return }
        let normalizedWidth = max(1, (width * 2).rounded() / 2)
        guard abs(normalizedWidth - renderWidth) > 0.5 else { return }
        renderWidth = normalizedWidth
        renderService.updateContentWidth(normalizedWidth)
        layoutEngine.updateRenderWidth(normalizedWidth)
        rebuildLayouts(shouldScrollToBottom: state.shouldAutoFollow)
    }

    public func setMessages(_ newMessages: [VVChatMessage], scrollToBottom: Bool = true) {
        setEntries(
            newMessages.map { .message($0) },
            scrollToBottom: scrollToBottom,
            customEntryMessageMapper: nil
        )
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
        pendingLayoutTransition = PendingLayoutTransition(
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
        draftThrottler.cancel()
        activeDraftID = nil

        coreStore.configure(customEntryMessageMapper: customEntryMessageMapper)
        syncPublicState(from: coreStore.setEntries(newEntries))
        renderService.invalidateAll()

        if scrollToBottom {
            state.hasUnreadNewContent = false
        }

        rebuildLayouts(shouldScrollToBottom: scrollToBottom)
    }

    public func appendMessage(_ message: VVChatMessage) {
        let oldTotalHeight = totalHeight
        preparePendingTailTransition(previousTotalHeight: oldTotalHeight)

        let snapshot = coreStore.appendMessage(message)
        syncPublicState(from: snapshot)
        if let message = snapshot.messages.last {
            layoutEngine.append(message: message, renderer: renderService)
        }
        totalHeight = layoutEngine.totalHeight

        let shouldFollow = state.shouldAutoFollow
        if !shouldFollow {
            state.hasUnreadNewContent = true
        }

        let index = max(0, snapshot.count - 1)
        onUpdate?(
            Update(
                insertedIndexes: IndexSet(integer: index),
                totalHeight: totalHeight,
                heightDelta: totalHeight - oldTotalHeight,
                changedIndex: index,
                shouldScrollToBottom: shouldFollow,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    public func appendCustomEntry(_ entry: VVCustomTimelineEntry) {
        let oldTotalHeight = totalHeight
        preparePendingTailTransition(previousTotalHeight: oldTotalHeight)

        let snapshot = coreStore.appendCustomEntry(entry)
        syncPublicState(from: snapshot)
        if let message = snapshot.messages.last {
            layoutEngine.append(message: message, renderer: renderService)
        }
        totalHeight = layoutEngine.totalHeight

        let shouldFollow = state.shouldAutoFollow
        if !shouldFollow {
            state.hasUnreadNewContent = true
        }

        let index = max(0, snapshot.count - 1)
        onUpdate?(
            Update(
                insertedIndexes: IndexSet(integer: index),
                totalHeight: totalHeight,
                heightDelta: totalHeight - oldTotalHeight,
                changedIndex: index,
                shouldScrollToBottom: shouldFollow,
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

        var message = messages[index]
        message.state = .final
        message.content = content
        message.revision += 1
        syncPublicState(from: coreStore.syncMessage(message))

        if activeDraftID == id {
            draftThrottler.cancel()
            activeDraftID = nil
        }

        updateMessageLayout(at: index, shouldScrollToBottom: state.shouldAutoFollow, markUnread: true)
    }

    public func replaceEntry(
        id: String,
        with entry: VVChatTimelineEntry,
        scrollToBottom: Bool? = nil,
        markUnread: Bool = true
    ) {
        guard let index = indexForItemID(id) else { return }

        let oldTotalHeight = totalHeight
        let previousMessageID = messages[index].id
        renderService.invalidate(messageID: previousMessageID)

        syncPublicState(from: coreStore.replaceEntry(id: id, with: entry))
        if previousMessageID != messages[index].id {
            renderService.invalidate(messageID: messages[index].id)
        }

        if activeDraftID == id, messages[index].state != .draft {
            draftThrottler.cancel()
            activeDraftID = nil
        }

        layoutEngine.reset(messages: messages, renderer: renderService)
        totalHeight = layoutEngine.totalHeight

        let shouldFollow = scrollToBottom ?? state.shouldAutoFollow
        if markUnread && !shouldFollow {
            state.hasUnreadNewContent = true
        } else if shouldFollow {
            state.hasUnreadNewContent = false
        }

        onUpdate?(
            Update(
                updatedIndexes: IndexSet(integer: index),
                totalHeight: totalHeight,
                heightDelta: totalHeight - oldTotalHeight,
                changedIndex: index,
                shouldScrollToBottom: shouldFollow,
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
        let clampedLower = max(0, min(range.lowerBound, entries.count))
        let clampedUpper = max(clampedLower, min(range.upperBound, entries.count))
        let clampedRange = clampedLower..<clampedUpper

        let oldTotalHeight = totalHeight
        let oldMessages = Array(messages[clampedRange])
        let oldCount = oldMessages.count
        let newCount = newEntries.count
        let shouldFollow = scrollToBottom ?? state.shouldAutoFollow

        for message in oldMessages {
            renderService.invalidate(messageID: message.id)
        }

        syncPublicState(from: coreStore.replaceEntries(in: clampedRange, with: newEntries))
        layoutEngine.reset(messages: messages, renderer: renderService)
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
        onUpdate?(
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
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    public func markUserInteraction(_ isInteracting: Bool) {
        state.userIsInteracting = isInteracting
    }

    public func updatePinnedState(distanceFromBottom: CGFloat) {
        state.updatePinnedState(distanceFromBottom: distanceFromBottom)
        if state.isPinnedToBottom {
            state.hasUnreadNewContent = false
        }
    }

    public func jumpToLatest() {
        state.hasUnreadNewContent = false
        state.isPinnedToBottom = true
        state.userIsInteracting = false
        onUpdate?(
            Update(
                totalHeight: totalHeight,
                shouldScrollToBottom: true,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    public func updateImageSize(url: String, size: CGSize) {
        guard renderService.updateImageSize(url: url, size: size) else { return }
        let sorted = layoutEngine.messageIDs(forImageURL: url).compactMap(indexForItemID).sorted()
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
        hydrateExactLayouts(in: visibleLayoutRange(in: viewport, overscan: overscan), emitUpdate: false)
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
        guard let index = indexForItemID(id), messages.indices.contains(index) else { return nil }
        return renderService.renderedMessage(for: messages[index])
    }

    public func renderedMessage(at index: Int) -> VVChatRenderedMessage? {
        guard messages.indices.contains(index) else { return nil }
        return renderService.renderedMessage(for: messages[index])
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
        let rendered = renderService.renderedMessage(for: item.message)
        return VVChatTimelineResolvedRenderItem(
            index: index,
            item: item,
            layout: layout,
            rendered: rendered
        )
    }

#if os(macOS)
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

    func debugSnapshot() -> VVChatMessageRenderer.DebugSnapshot {
        renderService.debugSnapshot()
    }

    func debugExactLayoutCount() -> Int {
        layoutEngine.debugExactLayoutCount()
    }

    func sceneArtifacts(at index: Int, visibleRect: CGRect?) -> VVChatSceneArtifacts? {
        guard messages.indices.contains(index) else { return nil }
        let message = messages[index]
        let rendered = renderService.renderedMessage(for: message)
        return renderService.sceneArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
    }

    func contentSceneArtifacts(at index: Int, visibleRect: CGRect?) -> VVChatSceneArtifacts? {
        guard messages.indices.contains(index) else { return nil }
        let message = messages[index]
        let rendered = renderService.renderedMessage(for: message)
        return renderService.contentSceneArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
    }

    func selectionHelper(at index: Int) -> VVMarkdownSelectionHelper? {
        guard messages.indices.contains(index) else { return nil }
        let message = messages[index]
        let rendered = renderService.renderedMessage(for: message)
        return renderService.selectionHelper(for: message, rendered: rendered)
    }

    func selectionArtifacts(at index: Int, visibleRect: CGRect?) -> VVChatSelectionArtifacts? {
        guard messages.indices.contains(index) else { return nil }
        let message = messages[index]
        let rendered = renderService.renderedMessage(for: message)
        return renderService.selectionArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
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
        var message = messages[index]
        message.content = content
        message.revision += 1
        syncPublicState(from: coreStore.syncMessage(message))

        updateMessageLayout(at: index, shouldScrollToBottom: state.shouldAutoFollow, markUnread: true)
    }

    private func updateMessageLayout(at index: Int, shouldScrollToBottom: Bool, markUnread: Bool) {
        guard messages.indices.contains(index) else { return }
        let delta = layoutEngine.updateLayout(at: index, message: messages[index], renderer: renderService)
        totalHeight = layoutEngine.totalHeight

        if markUnread && !shouldScrollToBottom {
            state.hasUnreadNewContent = true
        }

        onUpdate?(
            Update(
                updatedIndexes: IndexSet(integer: index),
                totalHeight: totalHeight,
                heightDelta: delta,
                changedIndex: index,
                shouldScrollToBottom: shouldScrollToBottom,
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
            if preservePreparedMarkdown {
                renderService.invalidateRendered(messageID: messages[index].id)
            } else {
                renderService.invalidate(messageID: messages[index].id)
            }
        }

        let mutation = layoutEngine.relayout(indexes: uniqueSorted, messages: messages, renderer: renderService)
        totalHeight = layoutEngine.totalHeight

        if markUnread && !shouldScrollToBottom {
            state.hasUnreadNewContent = true
        }

        onUpdate?(
            Update(
                updatedIndexes: mutation.updatedIndexes,
                totalHeight: totalHeight,
                heightDelta: mutation.totalDelta,
                changedIndex: mutation.updatedIndexes.first ?? uniqueSorted.first,
                shouldScrollToBottom: shouldScrollToBottom,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    private func rebuildLayouts(shouldScrollToBottom: Bool) {
        layoutEngine.reset(messages: messages, renderer: renderService)
        totalHeight = layoutEngine.totalHeight
        onUpdate?(
            Update(
                insertedIndexes: IndexSet(integersIn: 0..<layoutCount),
                totalHeight: totalHeight,
                shouldScrollToBottom: shouldScrollToBottom,
                hasUnreadNewContent: state.hasUnreadNewContent
            )
        )
    }

    @discardableResult
    private func hydrateExactLayouts(in range: Range<Int>) -> Bool {
        hydrateExactLayouts(in: range, emitUpdate: true)
    }

    @discardableResult
    private func hydrateExactLayouts(in range: Range<Int>, emitUpdate: Bool) -> Bool {
        let mutation = layoutEngine.hydrateExactLayouts(in: range, messages: messages, renderer: renderService)
        guard !mutation.updatedIndexes.isEmpty else { return false }
        totalHeight = layoutEngine.totalHeight
        if emitUpdate {
            onUpdate?(
                Update(
                    updatedIndexes: mutation.updatedIndexes,
                    totalHeight: totalHeight,
                    heightDelta: mutation.totalDelta,
                    changedIndex: mutation.updatedIndexes.first,
                    shouldScrollToBottom: false,
                    hasUnreadNewContent: state.hasUnreadNewContent
                )
            )
        }
        return true
    }

    private func preparePendingTailTransition(previousTotalHeight: CGFloat) {
        if let lastIndex = (0..<layoutCount).last,
           let anchorLayout = itemLayout(at: lastIndex) {
            pendingLayoutTransition = PendingLayoutTransition(
                anchorID: anchorLayout.id,
                anchorY: anchorLayout.frame.origin.y,
                previousTotalHeight: previousTotalHeight
            )
        }
    }

    private func indexForItemID(_ id: String) -> Int? {
        coreStore.snapshot.index(forItemID: id)
    }

    private func syncPublicState(from snapshot: VVChatTimelineCoreSnapshot) {
        entries = snapshot.entries
        messages = snapshot.messages
    }
}
