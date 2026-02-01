import Foundation
import CoreGraphics

@MainActor
public final class VVChatTimelineController {
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
        guard width > 0, width != renderWidth else { return }
        renderWidth = width
        renderer.updateContentWidth(width)
        rebuildLayouts(shouldScrollToBottom: state.shouldAutoFollow)
    }

    public func setMessages(_ newMessages: [VVChatMessage], scrollToBottom: Bool = true) {
        messages = newMessages
        messageImageURLs.removeAll(keepingCapacity: true)
        imageURLToMessageIDs.removeAll(keepingCapacity: true)
        rebuildLayouts(shouldScrollToBottom: scrollToBottom)
    }

    public func appendMessage(_ message: VVChatMessage) {
        let index = messages.count
        messages.append(message)
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
        let message = VVChatMessage(id: id, role: .assistant, state: .draft, content: content, revision: 0)
        activeDraftID = id
        appendMessage(message)
        return id
    }

    public func updateDraftMessage(id: String, content: String, throttle: Bool = true) {
        guard let index = messages.firstIndex(where: { $0.id == id }) else { return }
        guard messages[index].state == .draft else { return }
        if throttle {
            activeDraftID = id
            draftThrottler.schedule(content) { [weak self] text in
                Task { @MainActor in
                    self?.applyDraftUpdate(id: id, content: text)
                }
            }
        } else {
            applyDraftUpdate(id: id, content: content)
        }
    }

    public func finalizeMessage(id: String, content: String) {
        guard let index = messages.firstIndex(where: { $0.id == id }) else { return }
        messages[index].state = .final
        messages[index].content = content
        messages[index].revision += 1
        if activeDraftID == id {
            activeDraftID = nil
        }
        updateMessageLayout(at: index, shouldScrollToBottom: state.shouldAutoFollow, markUnread: true)
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
            messages.firstIndex(where: { $0.id == id })
        }.sorted()
        for index in sorted {
            let messageID = messages[index].id
            renderer.invalidate(messageID: messageID)
            updateMessageLayout(at: index, shouldScrollToBottom: state.shouldAutoFollow, markUnread: false)
        }
    }

    public func itemLayout(at index: Int) -> ItemLayout? {
        guard layouts.indices.contains(index) else { return nil }
        return layouts[index]
    }

    public func renderedMessage(for id: String) -> VVChatRenderedMessage? {
        guard let index = messages.firstIndex(where: { $0.id == id }) else { return nil }
        return renderer.renderedMessage(for: messages[index])
    }

    private func applyDraftUpdate(id: String, content: String) {
        guard let index = messages.firstIndex(where: { $0.id == id }) else { return }
        messages[index].content = content
        messages[index].revision += 1
        updateMessageLayout(at: index, shouldScrollToBottom: state.shouldAutoFollow, markUnread: true)
    }

    private func updateMessageLayout(at index: Int, shouldScrollToBottom: Bool, markUnread: Bool) {
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

        if delta != 0 {
            shiftLayouts(startingAt: index + 1, delta: delta)
        }
        totalHeight = (layouts.last?.frame.maxY ?? style.timelineInsets.top) + style.timelineInsets.bottom

        if markUnread && !shouldScrollToBottom {
            state.hasUnreadNewContent = true
        }

        let update = Update(
            updatedIndexes: IndexSet(integer: index),
            totalHeight: totalHeight,
            heightDelta: delta,
            changedIndex: index,
            shouldScrollToBottom: shouldScrollToBottom,
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
}
