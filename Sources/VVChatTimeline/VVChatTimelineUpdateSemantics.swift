import Foundation

enum VVChatTimelineUpdateSemantics {
    static func resolved(
        update: VVChatTimelineController.Update,
        requestedLayoutTransition: VVChatTimelineController.PendingLayoutTransition?
    ) -> VVChatTimelineController.Update {
        var resolved = update
        if resolved.layoutTransition == nil {
            resolved.layoutTransition = requestedLayoutTransition
        }
        assert(isValid(resolved), "Invalid VVChatTimeline update semantics: \(resolved)")
        return resolved
    }

    private static func isValid(_ update: VVChatTimelineController.Update) -> Bool {
        switch update.cause {
        case .tailAppend:
            return !update.insertedIndexes.isEmpty &&
                update.removedIndexes.isEmpty &&
                update.followPolicy != .forceImmediateBottom
        case .hydrateCorrection:
            return !update.shouldScrollToBottom && update.followPolicy == .none
        case .jumpToLatest:
            return update.shouldScrollToBottom &&
                update.insertedIndexes.isEmpty &&
                update.updatedIndexes.isEmpty &&
                update.removedIndexes.isEmpty &&
                update.followPolicy == .forceImmediateBottom
        case .rebuild, .singleReplace, .rangeReplace, .streamUpdate, .relayout:
            return true
        }
    }
}
