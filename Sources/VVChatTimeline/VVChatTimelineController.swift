import Foundation
import CoreGraphics
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
    }

    private struct LayoutRecord {
        var id: String
        var height: CGFloat
        var contentOffset: CGPoint
        var isDraft: Bool
        var revision: Int
    }

    private struct HeightIndex {
        private var heights: [CGFloat] = []
        private var tree: [CGFloat] = [0]

        var count: Int { heights.count }

        mutating func rebuild(heights: [CGFloat]) {
            self.heights = heights
            tree = Array(repeating: 0, count: heights.count + 1)
            for (index, height) in heights.enumerated() {
                add(height, at: index)
            }
        }

        mutating func append(_ height: CGFloat) {
            heights.append(height)
            let oneBasedIndex = heights.count
            let lowerBound = oneBasedIndex - (oneBasedIndex & -oneBasedIndex)
            let previousCoveredHeight = prefixHeight(before: oneBasedIndex - 1) - prefixHeight(before: lowerBound)
            tree.append(previousCoveredHeight + height)
        }

        mutating func updateHeight(at index: Int, to newHeight: CGFloat) {
            guard heights.indices.contains(index) else { return }
            let delta = newHeight - heights[index]
            guard delta != 0 else { return }
            heights[index] = newHeight
            add(delta, at: index)
        }

        func height(at index: Int) -> CGFloat {
            guard heights.indices.contains(index) else { return 0 }
            return heights[index]
        }

        func prefixHeight(before count: Int) -> CGFloat {
            guard count > 0 else { return 0 }
            var index = min(count, heights.count)
            var sum: CGFloat = 0
            while index > 0 {
                sum += tree[index]
                index -= index & -index
            }
            return sum
        }

        private mutating func add(_ delta: CGFloat, at index: Int) {
            var treeIndex = index + 1
            while treeIndex < tree.count {
                tree[treeIndex] += delta
                treeIndex += treeIndex & -treeIndex
            }
        }
    }

    public private(set) var entries: [VVChatTimelineEntry] = []
    public private(set) var messages: [VVChatMessage] = []
    public private(set) var totalHeight: CGFloat = 0
    public private(set) var state: VVChatTimelineState
    public var layouts: [ItemLayout] {
        layoutSnapshot()
    }

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
    private var layoutRecords: [LayoutRecord] = []
    private var heightIndex = HeightIndex()

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
        if let index = messageIndexByID[anchorItemID], let layout = itemLayout(at: index) {
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
        let layout = buildLayoutRecord(for: message)
        layoutRecords.append(layout)
        heightIndex.append(layout.height)
        totalHeight = computedTotalHeight()

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

        let layout = buildLayoutRecord(for: message)
        layoutRecords.append(layout)
        heightIndex.append(layout.height)
        totalHeight = computedTotalHeight()

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
        relayoutMessages(
            at: sorted,
            shouldScrollToBottom: state.shouldAutoFollow,
            markUnread: false,
            preservePreparedMarkdown: true
        )
    }

    public func itemLayout(at index: Int) -> ItemLayout? {
        guard layoutRecords.indices.contains(index) else { return nil }
        let record = layoutRecords[index]
        return ItemLayout(
            id: record.id,
            frame: CGRect(
                x: 0,
                y: originY(for: index),
                width: renderWidth,
                height: record.height
            ),
            contentOffset: record.contentOffset,
            isDraft: record.isDraft,
            revision: record.revision
        )
    }

    public var layoutCount: Int {
        layoutRecords.count
    }

    func visibleLayoutRange(in viewport: CGRect, overscan: CGFloat) -> Range<Int> {
        guard !layoutRecords.isEmpty else { return 0..<0 }
        let minY = viewport.minY - overscan
        let maxY = viewport.maxY + overscan
        let lower = lowerBound(forMaxYAbove: minY)
        let upper = upperBound(forMinYBelow: maxY)
        return lower..<max(lower, upper)
    }

    func itemIndex(containingDocumentY y: CGFloat) -> Int? {
        guard !layoutRecords.isEmpty else { return nil }
        var low = 0
        var high = layoutRecords.count - 1
        while low <= high {
            let mid = (low + high) / 2
            guard let frame = frame(at: mid) else { return nil }
            if y < frame.minY {
                high = mid - 1
            } else if y > frame.maxY {
                low = mid + 1
            } else {
                return mid
            }
        }
        return nil
    }

    func nearestItemIndex(forDocumentY y: CGFloat) -> Int? {
        guard !layoutRecords.isEmpty else { return nil }
        var low = 0
        var high = layoutRecords.count - 1
        while low <= high {
            let mid = (low + high) / 2
            guard let frame = frame(at: mid) else { return nil }
            if y < frame.minY {
                high = mid - 1
            } else if y > frame.maxY {
                low = mid + 1
            } else {
                return mid
            }
        }

        if low >= layoutRecords.count { return layoutRecords.count - 1 }
        if high < 0 { return 0 }

        guard let lowerFrame = frame(at: high), let upperFrame = frame(at: low) else {
            return nil
        }
        let lowerDistance = abs(y - lowerFrame.maxY)
        let upperDistance = abs(upperFrame.minY - y)
        return lowerDistance <= upperDistance ? high : low
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

    func sceneArtifacts(at index: Int, visibleRect: CGRect?) -> VVChatSceneArtifacts? {
        guard messages.indices.contains(index) else { return nil }
        let message = messages[index]
        let rendered = renderer.renderedMessage(for: message)
        return renderer.sceneArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
    }

    func contentSceneArtifacts(at index: Int, visibleRect: CGRect?) -> VVChatSceneArtifacts? {
        guard messages.indices.contains(index) else { return nil }
        let message = messages[index]
        let rendered = renderer.renderedMessage(for: message)
        return renderer.contentSceneArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
    }

    func selectionHelper(at index: Int) -> VVMarkdownSelectionHelper? {
        guard messages.indices.contains(index) else { return nil }
        let message = messages[index]
        let rendered = renderer.renderedMessage(for: message)
        return renderer.selectionHelper(for: message, rendered: rendered)
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
        let oldHeight = heightIndex.height(at: index)
        let newHeight = renderedMessage.height
        let delta = newHeight - oldHeight
        layoutRecords[index].height = newHeight
        layoutRecords[index].contentOffset = renderedMessage.contentOffset
        layoutRecords[index].isDraft = message.state == .draft
        layoutRecords[index].revision = message.revision

        if delta != 0 {
            heightIndex.updateHeight(at: index, to: newHeight)
        }
        totalHeight = computedTotalHeight()

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

    private func relayoutMessages(
        at indexes: [Int],
        shouldScrollToBottom: Bool,
        markUnread: Bool,
        preservePreparedMarkdown: Bool = false
    ) {
        guard !indexes.isEmpty else { return }

        let uniqueSorted = Array(Set(indexes)).sorted()
        let affectedIndexes = Set(uniqueSorted)
        let shouldFollow = shouldScrollToBottom

        for index in uniqueSorted {
            guard messages.indices.contains(index) else { continue }
            if preservePreparedMarkdown {
                renderer.invalidateRendered(messageID: messages[index].id)
            } else {
                renderer.invalidate(messageID: messages[index].id)
            }
        }

        var updatedIndexes = IndexSet()

        var cumulativeDelta: CGFloat = 0
        for index in uniqueSorted {
            guard affectedIndexes.contains(index), messages.indices.contains(index) else { continue }

            let message = messages[index]
            let renderedMessage = renderer.renderedMessage(for: message)
            updateImageMappings(messageID: message.id, imageURLs: Set(renderedMessage.imageURLs))

            let oldHeight = heightIndex.height(at: index)
            let newHeight = renderedMessage.height
            let delta = newHeight - oldHeight

            layoutRecords[index].height = newHeight
            layoutRecords[index].contentOffset = renderedMessage.contentOffset
            layoutRecords[index].isDraft = message.state == .draft
            layoutRecords[index].revision = message.revision

            heightIndex.updateHeight(at: index, to: newHeight)
            cumulativeDelta += delta
            updatedIndexes.insert(index)
        }

        totalHeight = computedTotalHeight()

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
        layoutRecords.removeAll(keepingCapacity: true)
        messageImageURLs.removeAll(keepingCapacity: true)
        imageURLToMessageIDs.removeAll(keepingCapacity: true)

        var heights: [CGFloat] = []
        heights.reserveCapacity(messages.count)
        for message in messages {
            let record = buildLayoutRecord(for: message)
            layoutRecords.append(record)
            heights.append(record.height)
        }
        heightIndex.rebuild(heights: heights)
        totalHeight = computedTotalHeight()

        let update = Update(
            insertedIndexes: IndexSet(integersIn: 0..<layoutRecords.count),
            totalHeight: totalHeight,
            shouldScrollToBottom: shouldScrollToBottom,
            hasUnreadNewContent: state.hasUnreadNewContent
        )
        onUpdate?(update)
    }

    private func buildLayoutRecord(for message: VVChatMessage) -> LayoutRecord {
        let renderedMessage = renderer.renderedMessage(for: message)
        updateImageMappings(messageID: message.id, imageURLs: Set(renderedMessage.imageURLs))
        return LayoutRecord(
            id: message.id,
            height: renderedMessage.height,
            contentOffset: renderedMessage.contentOffset,
            isDraft: message.state == .draft,
            revision: message.revision
        )
    }

    private func layoutSnapshot() -> [ItemLayout] {
        guard !layoutRecords.isEmpty else { return [] }
        var snapshot: [ItemLayout] = []
        snapshot.reserveCapacity(layoutRecords.count)
        for index in layoutRecords.indices {
            if let layout = itemLayout(at: index) {
                snapshot.append(layout)
            }
        }
        return snapshot
    }

    private func computedTotalHeight() -> CGFloat {
        guard !layoutRecords.isEmpty else {
            return style.timelineInsets.top + style.timelineInsets.bottom
        }
        let heights = heightIndex.prefixHeight(before: layoutRecords.count)
        let spacing = CGFloat(max(0, layoutRecords.count - 1)) * style.messageSpacing
        return style.timelineInsets.top + heights + spacing + style.timelineInsets.bottom
    }

    private func originY(for index: Int) -> CGFloat {
        style.timelineInsets.top + heightIndex.prefixHeight(before: index) + CGFloat(index) * style.messageSpacing
    }

    private func frame(at index: Int) -> CGRect? {
        guard layoutRecords.indices.contains(index) else { return nil }
        return CGRect(
            x: 0,
            y: originY(for: index),
            width: renderWidth,
            height: layoutRecords[index].height
        )
    }

    private func lowerBound(forMaxYAbove value: CGFloat) -> Int {
        var low = 0
        var high = layoutRecords.count
        while low < high {
            let mid = (low + high) / 2
            let maxY = originY(for: mid) + layoutRecords[mid].height
            if maxY < value {
                low = mid + 1
            } else {
                high = mid
            }
        }
        return low
    }

    private func upperBound(forMinYBelow value: CGFloat) -> Int {
        var low = 0
        var high = layoutRecords.count
        while low < high {
            let mid = (low + high) / 2
            let minY = originY(for: mid)
            if minY <= value {
                low = mid + 1
            } else {
                high = mid
            }
        }
        return low
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
