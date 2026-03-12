import Foundation

@MainActor
final class VVChatTimelineViewScheduler {
    enum VisibleHydrationResult {
        case completed
        case reschedule(TimeInterval)
    }

    private let relayoutBatchInterval: () -> TimeInterval
    private let applyUpdate: (VVChatTimelineController.Update) -> Void
    private let performVisibleHydration: () async -> VisibleHydrationResult
    private let performCacheTrim: () -> Void

    private var pendingControllerUpdate: VVChatTimelineController.Update?
    private var controllerUpdateTask: Task<Void, Never>?
    private var visibleHydrationTask: Task<Void, Never>?
    private var cacheTrimTask: Task<Void, Never>?

    var hasPendingStreamUpdate: Bool {
        pendingControllerUpdate?.cause == .streamUpdate
    }

    init(
        relayoutBatchInterval: @escaping () -> TimeInterval,
        applyUpdate: @escaping (VVChatTimelineController.Update) -> Void,
        performVisibleHydration: @escaping () async -> VisibleHydrationResult,
        performCacheTrim: @escaping () -> Void
    ) {
        self.relayoutBatchInterval = relayoutBatchInterval
        self.applyUpdate = applyUpdate
        self.performVisibleHydration = performVisibleHydration
        self.performCacheTrim = performCacheTrim
    }

    deinit {
        controllerUpdateTask?.cancel()
        visibleHydrationTask?.cancel()
        cacheTrimTask?.cancel()
    }

    func reset() {
        controllerUpdateTask?.cancel()
        visibleHydrationTask?.cancel()
        cacheTrimTask?.cancel()
        controllerUpdateTask = nil
        visibleHydrationTask = nil
        cacheTrimTask = nil
        pendingControllerUpdate = nil
    }

    func cancelVisibleHydration() {
        visibleHydrationTask?.cancel()
        visibleHydrationTask = nil
    }

    func cancelCacheTrim() {
        cacheTrimTask?.cancel()
        cacheTrimTask = nil
    }

    func enqueueControllerUpdate(_ update: VVChatTimelineController.Update) {
        if let existing = pendingControllerUpdate,
           !canCoalesce(existing, with: update) {
            flushPendingControllerUpdate()
        }

        pendingControllerUpdate = merge(pendingControllerUpdate, with: update)
        let interval = updateBatchInterval(for: update)

        if controllerUpdateTask != nil {
            guard interval == 0 else { return }
            controllerUpdateTask?.cancel()
            controllerUpdateTask = nil
        }

        controllerUpdateTask = Task { [weak self] in
            await Self.delay(for: interval)
            guard !Task.isCancelled, let self else { return }
            self.controllerUpdateTask = nil
            guard let pendingUpdate = self.pendingControllerUpdate else { return }
            self.pendingControllerUpdate = nil
            self.applyUpdate(pendingUpdate)
        }
    }

    func flushPendingControllerUpdate() {
        controllerUpdateTask?.cancel()
        controllerUpdateTask = nil
        guard let pendingControllerUpdate else { return }
        self.pendingControllerUpdate = nil
        applyUpdate(pendingControllerUpdate)
    }

    func scheduleVisibleHydration(after delay: TimeInterval = 0.12) {
        visibleHydrationTask?.cancel()
        visibleHydrationTask = Task { [weak self] in
            await Self.delay(for: delay)
            guard !Task.isCancelled, let self else { return }
            self.visibleHydrationTask = nil

            switch await self.performVisibleHydration() {
            case .completed:
                break
            case .reschedule(let nextDelay):
                self.scheduleVisibleHydration(after: nextDelay)
            }
        }
    }

    func scheduleCacheTrim(after delay: TimeInterval) {
        cacheTrimTask?.cancel()
        cacheTrimTask = Task { [weak self] in
            await Self.delay(for: delay)
            guard !Task.isCancelled, let self else { return }
            self.cacheTrimTask = nil
            self.performCacheTrim()
        }
    }

    private func canCoalesce(
        _ existing: VVChatTimelineController.Update,
        with incoming: VVChatTimelineController.Update
    ) -> Bool {
        guard existing.cause == incoming.cause else { return false }
        if existing.followPolicy != incoming.followPolicy &&
            existing.followPolicy != .none &&
            incoming.followPolicy != .none {
            return false
        }
        if let existingTransition = existing.layoutTransition,
           let incomingTransition = incoming.layoutTransition,
           existingTransition.anchorID != incomingTransition.anchorID {
            return false
        }
        return true
    }

    private func merge(
        _ existing: VVChatTimelineController.Update?,
        with incoming: VVChatTimelineController.Update
    ) -> VVChatTimelineController.Update {
        guard let existing else { return incoming }
        return VVChatTimelineController.Update(
            insertedIndexes: existing.insertedIndexes.union(incoming.insertedIndexes),
            updatedIndexes: existing.updatedIndexes.union(incoming.updatedIndexes),
            removedIndexes: existing.removedIndexes.union(incoming.removedIndexes),
            totalHeight: incoming.totalHeight,
            heightDelta: existing.heightDelta + incoming.heightDelta,
            changedIndex: incoming.changedIndex ?? existing.changedIndex,
            shouldScrollToBottom: existing.shouldScrollToBottom || incoming.shouldScrollToBottom,
            cause: incoming.cause,
            followPolicy: incoming.followPolicy == .none ? existing.followPolicy : incoming.followPolicy,
            layoutTransition: incoming.layoutTransition ?? existing.layoutTransition,
            hasUnreadNewContent: incoming.hasUnreadNewContent
        )
    }

    private func updateBatchInterval(for update: VVChatTimelineController.Update) -> TimeInterval {
        switch update.cause {
        case .tailAppend:
            return 0
        case .streamUpdate:
            return 0
        case .singleReplace, .rangeReplace:
            return 0
        case .relayout, .hydrateCorrection, .rebuild, .jumpToLatest:
            return relayoutBatchInterval()
        }
    }

    private static func delay(for interval: TimeInterval) async {
        guard interval > 0 else {
            await Task.yield()
            return
        }

        let nanoseconds = UInt64((interval * 1_000_000_000).rounded(.up))
        try? await Task.sleep(nanoseconds: nanoseconds)
    }
}
