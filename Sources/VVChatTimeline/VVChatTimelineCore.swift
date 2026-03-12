import Foundation

struct VVChatTimelineItem: Identifiable, Hashable, Sendable {
    let model: VVChatTimelineItemModel
    let message: VVChatMessage

    var id: String { model.id }
    var kind: VVChatTimelineItemKind { model.kind }
    var entry: VVChatTimelineEntry { model.entry }
    var revision: Int { model.revision }
    var timestamp: Date? { model.timestamp }
    var isStreaming: Bool { message.isStreaming }

    init(model: VVChatTimelineItemModel, message: VVChatMessage) {
        self.model = model
        self.message = message
    }

    init(adaptedItem: VVChatAdaptedTimelineItem) {
        self.init(model: adaptedItem.model, message: adaptedItem.message)
    }

    func replacing(
        model: VVChatTimelineItemModel? = nil,
        message: VVChatMessage? = nil
    ) -> VVChatTimelineItem {
        let nextModel = model ?? self.model
        let nextMessage = message ?? self.message
        return VVChatTimelineItem(model: nextModel, message: nextMessage)
    }
}

struct VVChatTimelineCoreSnapshot: Sendable {
    let items: [VVChatTimelineItem]
    let itemIndexByID: [String: Int]

    static let empty = VVChatTimelineCoreSnapshot(items: [], itemIndexByID: [:])

    var itemModels: [VVChatTimelineItemModel] {
        items.map(\.model)
    }

    var entries: [VVChatTimelineEntry] {
        items.map(\.entry)
    }

    var messages: [VVChatMessage] {
        items.map(\.message)
    }

    var count: Int {
        items.count
    }

    func item(at index: Int) -> VVChatTimelineItem? {
        guard items.indices.contains(index) else { return nil }
        return items[index]
    }

    func item(id: String) -> VVChatTimelineItem? {
        guard let index = itemIndexByID[id] else { return nil }
        return item(at: index)
    }

    func entry(at index: Int) -> VVChatTimelineEntry? {
        item(at: index)?.entry
    }

    func message(at index: Int) -> VVChatMessage? {
        item(at: index)?.message
    }

    func index(forItemID id: String) -> Int? {
        itemIndexByID[id]
    }
}

@MainActor
final class VVChatTimelineCoreStore {
    typealias CustomEntryMessageMapper = VVChatTimelineController.CustomEntryMessageMapper

    private var itemAdapter = VVChatTimelineItemAdapter()
    private(set) var snapshot: VVChatTimelineCoreSnapshot = .empty

    func configure(customEntryMessageMapper: CustomEntryMessageMapper?) {
        itemAdapter.customEntryMessageMapper = customEntryMessageMapper
    }

    func itemModel(for entry: VVChatTimelineEntry) -> VVChatTimelineItemModel {
        itemAdapter.itemModel(for: entry)
    }

    @discardableResult
    func setItems(_ items: [VVChatTimelineItemModel]) -> VVChatTimelineCoreSnapshot {
        snapshot = makeSnapshot(from: items.map(itemAdapter.adapt))
        return snapshot
    }

    @discardableResult
    func setEntries(_ entries: [VVChatTimelineEntry]) -> VVChatTimelineCoreSnapshot {
        snapshot = setItems(entries.map(itemAdapter.itemModel))
        return snapshot
    }

    @discardableResult
    func appendItem(_ item: VVChatTimelineItemModel) -> VVChatTimelineCoreSnapshot {
        var items = snapshot.items
        items.append(VVChatTimelineItem(adaptedItem: itemAdapter.adapt(item)))
        snapshot = makeSnapshot(from: items)
        return snapshot
    }

    @discardableResult
    func appendMessage(_ message: VVChatMessage) -> VVChatTimelineCoreSnapshot {
        appendItem(VVChatTimelineItemModel(message: message))
    }

    @discardableResult
    func appendCustomEntry(_ entry: VVCustomTimelineEntry) -> VVChatTimelineCoreSnapshot {
        appendItem(VVChatTimelineItemModel(customEntry: entry))
    }

    @discardableResult
    func replaceItem(
        id: String,
        with item: VVChatTimelineItemModel
    ) -> VVChatTimelineCoreSnapshot {
        guard let index = snapshot.index(forItemID: id) else { return snapshot }
        var items = snapshot.items
        items[index] = VVChatTimelineItem(adaptedItem: itemAdapter.adapt(item))
        snapshot = makeSnapshot(from: items)
        return snapshot
    }

    @discardableResult
    func replaceEntry(
        id: String,
        with entry: VVChatTimelineEntry
    ) -> VVChatTimelineCoreSnapshot {
        replaceItem(id: id, with: itemAdapter.itemModel(for: entry))
    }

    @discardableResult
    func replaceItems(
        in range: Range<Int>,
        with items: [VVChatTimelineItemModel]
    ) -> VVChatTimelineCoreSnapshot {
        let lower = max(0, min(range.lowerBound, snapshot.count))
        let upper = max(lower, min(range.upperBound, snapshot.count))
        let adapted = items.map(itemAdapter.adapt).map(VVChatTimelineItem.init(adaptedItem:))
        var currentItems = snapshot.items
        currentItems.replaceSubrange(lower..<upper, with: adapted)
        snapshot = makeSnapshot(from: currentItems)
        return snapshot
    }

    @discardableResult
    func replaceEntries(
        in range: Range<Int>,
        with entries: [VVChatTimelineEntry]
    ) -> VVChatTimelineCoreSnapshot {
        replaceItems(in: range, with: entries.map(itemAdapter.itemModel))
    }

    @discardableResult
    func syncMessage(_ message: VVChatMessage) -> VVChatTimelineCoreSnapshot {
        guard let index = snapshot.index(forItemID: message.id) else { return snapshot }
        var items = snapshot.items
        let current = items[index]
        let nextModel: VVChatTimelineItemModel
        switch current.model.content {
        case .message:
            nextModel = VVChatTimelineItemModel(message: message)
        case .custom:
            nextModel = current.model
        }
        items[index] = current.replacing(model: nextModel, message: message)
        snapshot = makeSnapshot(from: items)
        return snapshot
    }

    private func makeSnapshot(from adaptedItems: [VVChatAdaptedTimelineItem]) -> VVChatTimelineCoreSnapshot {
        makeSnapshot(from: adaptedItems.map(VVChatTimelineItem.init(adaptedItem:)))
    }

    private func makeSnapshot(from items: [VVChatTimelineItem]) -> VVChatTimelineCoreSnapshot {
        var itemIndexByID: [String: Int] = [:]
        itemIndexByID.reserveCapacity(items.count)
        for (index, item) in items.enumerated() {
            itemIndexByID[item.id] = index
        }
        return VVChatTimelineCoreSnapshot(items: items, itemIndexByID: itemIndexByID)
    }
}
