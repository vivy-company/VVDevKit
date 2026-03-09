import Foundation
import CoreGraphics

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
    }

    public private(set) var entries: [VVChatTimelineEntry] = []
    public private(set) var messages: [VVChatMessage] = []
    public private(set) var layouts: [ItemLayout] = []
    public private(set) var totalHeight: CGFloat = 0
    public private(set) var state: VVChatTimelineState

    public var onUpdate: ((Update) -> Void)?

    private var style: VVChatTimelineStyle
    private var renderer: VVChatMessageRenderer
    private var renderWidth: CGFloat
    private let draftThrottler = VVChatDraftThrottler()
    private var activeDraftID: String?
    private var messageImageURLs: [String: Set<String>] = [:]
    private var imageURLToMessageIDs: [String: Set<String>] = [:]
    private var messageIndexByID: [String: Int] = [:]
    private var entryIndexByID: [String: Int] = [:]
    private var customEntryMessageMapper: CustomEntryMessageMapper?

    public init(style: VVChatTimelineStyle = .init(), renderWidth: CGFloat = 0) {
        self.style = style
        self.renderWidth = renderWidth
        self.renderer = VVChatMessageRenderer(style: style, contentWidth: renderWidth)
        self.state = VVChatTimelineState(pinThreshold: style.pinThreshold)
    }

    public var currentStyle: VVChatTimelineStyle {
        style
    }

    public func updateStyle(_ style: VVChatTimelineStyle) {
        self.style = style
        self.state.pinThreshold = style.pinThreshold
        renderer.updateStyle(style)
        rebuildLayouts(shouldScrollToBottom: state.shouldAutoFollow)
    }

    public func updateRenderWidth(_ width: CGFloat) {
        guard width > 0 else { return }
        let normalizedWidth = max(1, (width * 2).rounded() / 2)
        guard abs(normalizedWidth - renderWidth) > 0.5 else { return }
        renderWidth = normalizedWidth
        renderer.updateContentWidth(normalizedWidth)
        rebuildLayouts(shouldScrollToBottom: state.shouldAutoFollow)
    }

    public func setMessages(_ newMessages: [VVChatMessage], scrollToBottom: Bool = true) {
        setEntries(
            newMessages.map { .message($0) },
            scrollToBottom: scrollToBottom,
            customEntryMessageMapper: nil
        )
    }

    /// Pending layout transition state, consumed by the view on next update.
    public struct PendingLayoutTransition {
        public let anchorID: String
        public let anchorY: CGFloat
        public let previousTotalHeight: CGFloat
    }
    public internal(set) var pendingLayoutTransition: PendingLayoutTransition?

    /// Call before `setEntries` to animate the layout transition.
    /// Pass the ID of the item at or above the insertion/removal point.
    public func prepareLayoutTransition(anchorItemID: String) {
        let anchorY: CGFloat
        if let index = messageIndexByID[anchorItemID], layouts.indices.contains(index) {
            anchorY = layouts[index].frame.origin.y
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

        self.customEntryMessageMapper = customEntryMessageMapper
        entries = newEntries
        messages = newEntries.map { materializeMessage(for: $0) }
        rebuildIDIndexes()
        renderer.invalidateAll()

        messageImageURLs.removeAll(keepingCapacity: true)
        imageURLToMessageIDs.removeAll(keepingCapacity: true)

        if scrollToBottom {
            state.hasUnreadNewContent = false
        }

        rebuildLayouts(shouldScrollToBottom: scrollToBottom)
    }

    public func appendMessage(_ message: VVChatMessage) {
        entries.append(.message(message))

        let index = messages.count
        messages.append(message)
        messageIndexByID[message.id] = index
        entryIndexByID[message.id] = entries.count - 1
        let layout = buildLayout(for: message, at: nextYPosition())
        layouts.append(layout)
        totalHeight = layout.frame.maxY + style.timelineInsets.bottom

        let shouldFollow = state.shouldAutoFollow
        if !shouldFollow {
            state.hasUnreadNewContent = true
        }

        let update = Update(
            insertedIndexes: IndexSet(integer: index),
            totalHeight: totalHeight,
            shouldScrollToBottom: shouldFollow,
            hasUnreadNewContent: state.hasUnreadNewContent
        )
        onUpdate?(update)
    }

    public func appendCustomEntry(_ entry: VVCustomTimelineEntry) {
        entries.append(.custom(entry))

        let index = messages.count
        let message = materializeMessage(for: .custom(entry))
        messages.append(message)
        messageIndexByID[message.id] = index
        entryIndexByID[entry.id] = entries.count - 1

        let layout = buildLayout(for: message, at: nextYPosition())
        layouts.append(layout)
        totalHeight = layout.frame.maxY + style.timelineInsets.bottom

        let shouldFollow = state.shouldAutoFollow
        if !shouldFollow {
            state.hasUnreadNewContent = true
        }

        let update = Update(
            insertedIndexes: IndexSet(integer: index),
            totalHeight: totalHeight,
            shouldScrollToBottom: shouldFollow,
            hasUnreadNewContent: state.hasUnreadNewContent
        )
        onUpdate?(update)
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
        guard let index = messageIndexByID[id] else { return }
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
        guard let index = messageIndexByID[id] else { return }
        guard messages[index].state == .draft else { return }
        let appended = messages[index].content + chunk
        updateDraftMessage(id: id, content: appended, throttle: throttle)
    }

    public func finalizeMessage(id: String, content: String) {
        guard let index = messageIndexByID[id] else { return }
        renderer.invalidate(messageID: id)
        messages[index].state = .final
        messages[index].content = content
        messages[index].revision += 1
        syncMessageBackToEntries(messages[index])
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
        guard let index = entryIndexByID[id] else { return }

        renderer.invalidate(messageID: id)
        let previousMessageID = messages.indices.contains(index) ? messages[index].id : nil
        entries[index] = entry
        messages[index] = materializeMessage(for: entry)
        rebuildIDIndexes()
        if let previousMessageID, previousMessageID != messages[index].id {
            renderer.invalidate(messageID: previousMessageID)
        }

        if activeDraftID == id, messages[index].state != .draft {
            draftThrottler.cancel()
            activeDraftID = nil
        }

        updateMessageLayout(
            at: index,
            shouldScrollToBottom: scrollToBottom ?? state.shouldAutoFollow,
            markUnread: markUnread
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
        let update = Update(
            totalHeight: totalHeight,
            shouldScrollToBottom: true,
            hasUnreadNewContent: state.hasUnreadNewContent
        )
        onUpdate?(update)
    }

    public func updateImageSize(url: String, size: CGSize) {
        guard renderer.updateImageSize(url: url, size: size) else { return }
        guard let messageIDs = imageURLToMessageIDs[url] else { return }
        let sorted = messageIDs.compactMap { id -> Int? in
            messageIndexByID[id]
        }.sorted()
        relayoutMessages(at: sorted, shouldScrollToBottom: state.shouldAutoFollow, markUnread: false)
    }

    public func itemLayout(at index: Int) -> ItemLayout? {
        guard layouts.indices.contains(index) else { return nil }
        return layouts[index]
    }

    public func entry(at index: Int) -> VVChatTimelineEntry? {
        guard entries.indices.contains(index) else { return nil }
        return entries[index]
    }

    public func renderedMessage(for id: String) -> VVChatRenderedMessage? {
        guard let index = messageIndexByID[id] else { return nil }
        return renderer.renderedMessage(for: messages[index])
    }

    public func renderedMessage(at index: Int) -> VVChatRenderedMessage? {
        guard messages.indices.contains(index) else { return nil }
        return renderer.renderedMessage(for: messages[index])
    }

    private func applyDraftUpdate(id: String, content: String) {
        guard let index = messageIndexByID[id] else { return }
        guard messages[index].state == .draft else { return }
        renderer.invalidate(messageID: id)
        messages[index].content = content
        messages[index].revision += 1
        syncMessageBackToEntries(messages[index])
        updateMessageLayout(at: index, shouldScrollToBottom: state.shouldAutoFollow, markUnread: true)
    }

    private func updateMessageLayout(at index: Int, shouldScrollToBottom: Bool, markUnread: Bool) {
        let message = messages[index]
        let shouldFollow = shouldScrollToBottom
        let renderedMessage = renderer.renderedMessage(for: message)
        updateImageMappings(messageID: message.id, imageURLs: Set(renderedMessage.imageURLs))
        let oldHeight = layouts[index].frame.height
        let newHeight = renderedMessage.height
        let delta = newHeight - oldHeight
        layouts[index].frame.size.height = newHeight
        layouts[index].contentOffset = renderedMessage.contentOffset
        layouts[index].isDraft = message.state == .draft
        layouts[index].revision = message.revision

        if delta != 0 {
            shiftLayouts(startingAt: index + 1, delta: delta)
        }
        totalHeight = (layouts.last?.frame.maxY ?? style.timelineInsets.top) + style.timelineInsets.bottom

        if markUnread && !shouldFollow {
            state.hasUnreadNewContent = true
        }

        let update = Update(
            updatedIndexes: IndexSet(integer: index),
            totalHeight: totalHeight,
            heightDelta: delta,
            changedIndex: index,
            shouldScrollToBottom: shouldFollow,
            hasUnreadNewContent: state.hasUnreadNewContent
        )
        onUpdate?(update)
    }

    private func relayoutMessages(at indexes: [Int], shouldScrollToBottom: Bool, markUnread: Bool) {
        guard !indexes.isEmpty else { return }

        let uniqueSorted = Array(Set(indexes)).sorted()
        let affectedIndexes = Set(uniqueSorted)
        let shouldFollow = shouldScrollToBottom

        for index in uniqueSorted {
            guard messages.indices.contains(index) else { continue }
            renderer.invalidate(messageID: messages[index].id)
        }

        var cumulativeDelta: CGFloat = 0
        let startIndex = uniqueSorted[0]
        var updatedIndexes = IndexSet()

        for index in startIndex..<layouts.count {
            if cumulativeDelta != 0 {
                layouts[index].frame.origin.y += cumulativeDelta
            }
            guard affectedIndexes.contains(index) else { continue }

            let message = messages[index]
            let renderedMessage = renderer.renderedMessage(for: message)
            updateImageMappings(messageID: message.id, imageURLs: Set(renderedMessage.imageURLs))

            let oldHeight = layouts[index].frame.height
            let newHeight = renderedMessage.height
            let delta = newHeight - oldHeight

            layouts[index].frame.size.height = newHeight
            layouts[index].contentOffset = renderedMessage.contentOffset
            layouts[index].isDraft = message.state == .draft
            layouts[index].revision = message.revision

            cumulativeDelta += delta
            updatedIndexes.insert(index)
        }

        totalHeight = (layouts.last?.frame.maxY ?? style.timelineInsets.top) + style.timelineInsets.bottom

        if markUnread && !shouldFollow {
            state.hasUnreadNewContent = true
        }

        let update = Update(
            updatedIndexes: updatedIndexes,
            totalHeight: totalHeight,
            heightDelta: cumulativeDelta,
            changedIndex: uniqueSorted.first,
            shouldScrollToBottom: shouldFollow,
            hasUnreadNewContent: state.hasUnreadNewContent
        )
        onUpdate?(update)
    }

    private func rebuildLayouts(shouldScrollToBottom: Bool) {
        layouts.removeAll(keepingCapacity: true)
        messageImageURLs.removeAll(keepingCapacity: true)
        imageURLToMessageIDs.removeAll(keepingCapacity: true)

        var currentY = style.timelineInsets.top
        for message in messages {
            let renderedMessage = renderer.renderedMessage(for: message)
            updateImageMappings(messageID: message.id, imageURLs: Set(renderedMessage.imageURLs))
            let frame = CGRect(x: 0, y: currentY, width: renderWidth, height: renderedMessage.height)
            let layout = ItemLayout(
                id: message.id,
                frame: frame,
                contentOffset: renderedMessage.contentOffset,
                isDraft: message.state == .draft,
                revision: message.revision
            )
            layouts.append(layout)
            currentY = frame.maxY + style.messageSpacing
        }
        totalHeight = (layouts.last?.frame.maxY ?? style.timelineInsets.top) + style.timelineInsets.bottom

        let update = Update(
            insertedIndexes: IndexSet(integersIn: 0..<layouts.count),
            totalHeight: totalHeight,
            shouldScrollToBottom: shouldScrollToBottom,
            hasUnreadNewContent: state.hasUnreadNewContent
        )
        onUpdate?(update)
    }

    private func buildLayout(for message: VVChatMessage, at y: CGFloat) -> ItemLayout {
        let renderedMessage = renderer.renderedMessage(for: message)
        updateImageMappings(messageID: message.id, imageURLs: Set(renderedMessage.imageURLs))
        let frame = CGRect(x: 0, y: y, width: renderWidth, height: renderedMessage.height)
        return ItemLayout(
            id: message.id,
            frame: frame,
            contentOffset: renderedMessage.contentOffset,
            isDraft: message.state == .draft,
            revision: message.revision
        )
    }

    private func nextYPosition() -> CGFloat {
        guard let last = layouts.last else {
            return style.timelineInsets.top
        }
        return last.frame.maxY + style.messageSpacing
    }

    private func shiftLayouts(startingAt index: Int, delta: CGFloat) {
        guard delta != 0, index < layouts.count else { return }
        for i in index..<layouts.count {
            layouts[i].frame.origin.y += delta
        }
    }

    private func updateImageMappings(messageID: String, imageURLs: Set<String>) {
        if let previous = messageImageURLs[messageID] {
            for url in previous {
                imageURLToMessageIDs[url]?.remove(messageID)
                if imageURLToMessageIDs[url]?.isEmpty == true {
                    imageURLToMessageIDs.removeValue(forKey: url)
                }
            }
        }
        messageImageURLs[messageID] = imageURLs
        for url in imageURLs {
            imageURLToMessageIDs[url, default: []].insert(messageID)
        }
    }

    private func syncMessageBackToEntries(_ message: VVChatMessage) {
        guard let entryIndex = entryIndexByID[message.id] else { return }
        entries[entryIndex] = .message(message)
    }

    private func rebuildIDIndexes() {
        messageIndexByID.removeAll(keepingCapacity: true)
        messageIndexByID.reserveCapacity(messages.count)
        for (index, message) in messages.enumerated() {
            messageIndexByID[message.id] = index
        }

        entryIndexByID.removeAll(keepingCapacity: true)
        entryIndexByID.reserveCapacity(entries.count)
        for (index, entry) in entries.enumerated() {
            entryIndexByID[entry.id] = index
        }
    }

    private func materializeMessage(for entry: VVChatTimelineEntry) -> VVChatMessage {
        switch entry {
        case .message(let message):
            return message
        case .custom(let custom):
            if let customEntryMessageMapper {
                return customEntryMessageMapper(custom)
            }
            return defaultMessage(for: custom)
        }
    }

    private func defaultMessage(for custom: VVCustomTimelineEntry) -> VVChatMessage {
        let content = String(data: custom.payload, encoding: .utf8) ?? "[\(custom.kind)]"
        return VVChatMessage(
            id: custom.id,
            role: .system,
            state: .final,
            content: content,
            revision: custom.revision,
            timestamp: custom.timestamp
        )
    }
}
