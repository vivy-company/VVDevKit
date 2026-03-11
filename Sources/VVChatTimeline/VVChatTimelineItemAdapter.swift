import Foundation

struct VVChatAdaptedTimelineEntry {
    let entry: VVChatTimelineEntry
    let message: VVChatMessage
}

@MainActor
struct VVChatTimelineItemAdapter {
    typealias CustomEntryMessageMapper = VVChatTimelineController.CustomEntryMessageMapper

    var customEntryMessageMapper: CustomEntryMessageMapper?

    func adapt(_ entry: VVChatTimelineEntry) -> VVChatAdaptedTimelineEntry {
        VVChatAdaptedTimelineEntry(
            entry: entry,
            message: message(for: entry)
        )
    }

    private func message(for entry: VVChatTimelineEntry) -> VVChatMessage {
        switch entry {
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
