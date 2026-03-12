import Foundation

struct VVChatAdaptedTimelineItem {
    let model: VVChatTimelineItemModel
    let message: VVChatMessage
}

@MainActor
struct VVChatTimelineItemAdapter {
    typealias CustomEntryMessageMapper = VVChatTimelineController.CustomEntryMessageMapper

    var customEntryMessageMapper: CustomEntryMessageMapper?

    func itemModel(for entry: VVChatTimelineEntry) -> VVChatTimelineItemModel {
        switch entry {
        case .message(let message):
            return VVChatTimelineItemModel(message: message)
        case .custom(let custom):
            return VVChatTimelineItemModel(customEntry: custom)
        }
    }

    func adapt(_ entry: VVChatTimelineEntry) -> VVChatAdaptedTimelineItem {
        adapt(itemModel(for: entry))
    }

    func adapt(_ item: VVChatTimelineItemModel) -> VVChatAdaptedTimelineItem {
        VVChatAdaptedTimelineItem(
            model: item,
            message: message(for: item)
        )
    }

    private func message(for item: VVChatTimelineItemModel) -> VVChatMessage {
        switch item.content {
        case .message(let message):
            return message
        case .custom(let custom):
            return customMessage(for: custom)
        }
    }

    private func customMessage(for custom: VVCustomTimelineEntry) -> VVChatMessage {
        if let customEntryMessageMapper {
            return customEntryMessageMapper(custom)
        }
        return defaultMessage(for: custom)
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
