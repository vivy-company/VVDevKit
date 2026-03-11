import Foundation

enum VVChatTimelineItemKind: Hashable, Sendable {
    case message(role: VVChatMessageRole)
    case toolGroup
    case toolCall
    case summaryCard
    case systemEvent
    case diffCard
    case customWidget(name: String)

    static func classify(
        entry: VVChatTimelineEntry,
        message: VVChatMessage
    ) -> VVChatTimelineItemKind {
        switch entry {
        case .message:
            if let customContent = message.customContent {
                switch customContent {
                case .summaryCard:
                    return .summaryCard
                case .inlineDiff:
                    return .diffCard
                }
            }
            return .message(role: message.role)
        case .custom(let custom):
            let normalized = custom.kind
                .trimmingCharacters(in: .whitespacesAndNewlines)
                .lowercased()

            switch normalized {
            case "toolgroup", "tool_call_group", "tool-call-group", "toolcallgroup":
                return .toolGroup
            case "toolcall", "tool_call", "tool-call", "toolcalldetail", "tool_call_detail", "tool-call-detail":
                return .toolCall
            case "summarycard", "summary_card", "summary-card":
                return .summaryCard
            case "systemevent", "system_event", "system-event":
                return .systemEvent
            case "diffcard", "diff_card", "diff-card", "inlinediff", "inline_diff", "inline-diff":
                return .diffCard
            case "":
                return .customWidget(name: "custom")
            default:
                return .customWidget(name: normalized)
            }
        }
    }
}

struct VVChatTimelineItem: Identifiable, Hashable, Sendable {
    let id: String
    let kind: VVChatTimelineItemKind
    let entry: VVChatTimelineEntry
    let message: VVChatMessage
    let revision: Int
    let timestamp: Date?
    let isStreaming: Bool

    init(entry: VVChatTimelineEntry, message: VVChatMessage) {
        self.id = entry.id
        self.kind = VVChatTimelineItemKind.classify(entry: entry, message: message)
        self.entry = entry
        self.message = message
        self.revision = message.revision
        self.timestamp = message.timestamp
        self.isStreaming = message.isStreaming
    }

    init(adaptedEntry: VVChatAdaptedTimelineEntry) {
        self.init(entry: adaptedEntry.entry, message: adaptedEntry.message)
    }

    func replacing(
        entry: VVChatTimelineEntry? = nil,
        message: VVChatMessage? = nil
    ) -> VVChatTimelineItem {
        let nextEntry = entry ?? self.entry
        let nextMessage = message ?? self.message
        return VVChatTimelineItem(entry: nextEntry, message: nextMessage)
    }
}

struct VVChatTimelineCoreSnapshot: Sendable {
    let items: [VVChatTimelineItem]
    let itemIndexByID: [String: Int]

    static let empty = VVChatTimelineCoreSnapshot(items: [], itemIndexByID: [:])

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

    @discardableResult
    func setEntries(_ entries: [VVChatTimelineEntry]) -> VVChatTimelineCoreSnapshot {
        snapshot = makeSnapshot(from: entries.map(itemAdapter.adapt))
        return snapshot
    }

    @discardableResult
    func appendMessage(_ message: VVChatMessage) -> VVChatTimelineCoreSnapshot {
        var items = snapshot.items
        items.append(VVChatTimelineItem(adaptedEntry: itemAdapter.adapt(.message(message))))
        snapshot = makeSnapshot(from: items)
        return snapshot
    }

    @discardableResult
    func appendCustomEntry(_ entry: VVCustomTimelineEntry) -> VVChatTimelineCoreSnapshot {
        var items = snapshot.items
        items.append(VVChatTimelineItem(adaptedEntry: itemAdapter.adapt(.custom(entry))))
        snapshot = makeSnapshot(from: items)
        return snapshot
    }

    @discardableResult
    func replaceEntry(
        id: String,
        with entry: VVChatTimelineEntry
    ) -> VVChatTimelineCoreSnapshot {
        guard let index = snapshot.index(forItemID: id) else { return snapshot }
        var items = snapshot.items
        items[index] = VVChatTimelineItem(adaptedEntry: itemAdapter.adapt(entry))
        snapshot = makeSnapshot(from: items)
        return snapshot
    }

    @discardableResult
    func replaceEntries(
        in range: Range<Int>,
        with entries: [VVChatTimelineEntry]
    ) -> VVChatTimelineCoreSnapshot {
        let lower = max(0, min(range.lowerBound, snapshot.count))
        let upper = max(lower, min(range.upperBound, snapshot.count))
        let adapted = entries.map(itemAdapter.adapt).map(VVChatTimelineItem.init(adaptedEntry:))
        var items = snapshot.items
        items.replaceSubrange(lower..<upper, with: adapted)
        snapshot = makeSnapshot(from: items)
        return snapshot
    }

    @discardableResult
    func syncMessage(_ message: VVChatMessage) -> VVChatTimelineCoreSnapshot {
        guard let index = snapshot.index(forItemID: message.id) else { return snapshot }
        var items = snapshot.items
        let current = items[index]
        let nextEntry: VVChatTimelineEntry
        switch current.entry {
        case .message:
            nextEntry = .message(message)
        case .custom:
            nextEntry = current.entry
        }
        items[index] = current.replacing(entry: nextEntry, message: message)
        snapshot = makeSnapshot(from: items)
        return snapshot
    }

    private func makeSnapshot(from adaptedEntries: [VVChatAdaptedTimelineEntry]) -> VVChatTimelineCoreSnapshot {
        makeSnapshot(from: adaptedEntries.map(VVChatTimelineItem.init(adaptedEntry:)))
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
