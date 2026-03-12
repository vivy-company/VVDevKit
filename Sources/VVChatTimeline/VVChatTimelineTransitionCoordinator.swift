import CoreGraphics
import Foundation
import VVMetalPrimitives

struct VVChatTimelineLayoutAnimationPlan {
    let startSnapshots: [String: VVLayoutAnimationSnapshot]
    let targetSnapshots: [String: VVLayoutAnimationSnapshot]
    let fallbackTransition: VVTransition
    let fallbackAnimation: VVAnimationDescriptor
}

struct VVChatTimelineUpdateTransitionPlan {
    let snapshotIndexes: IndexSet
    let transition: VVChatTimelineController.PendingLayoutTransition?
    let shouldSuppressPinnedTailViewportMotion: Bool
    let compensatedScrollTargetY: CGFloat?
}

@MainActor
final class VVChatTimelineTransitionCoordinator {
    func makeUpdatePlan(
        update: VVChatTimelineController.Update,
        controller: VVChatTimelineController,
        visibleRect: CGRect,
        wasPinnedToBottom: Bool,
        visibleRenderRange: Range<Int>,
        stableSnapshots: [String: VVLayoutAnimationSnapshot],
        layoutAnimationOverscan: CGFloat,
        layoutAnimationItemPadding: Int
    ) -> VVChatTimelineUpdateTransitionPlan {
        let snapshotIndexes = animationSnapshotIndexes(
            for: update,
            controller: controller,
            visibleRect: visibleRect,
            visibleRenderRange: visibleRenderRange,
            layoutAnimationOverscan: layoutAnimationOverscan,
            layoutAnimationItemPadding: layoutAnimationItemPadding
        )
        let shouldSuppressPinnedTailViewportMotion =
            update.followPolicy == .preservePinnedBottom &&
            (controller.state.isLiveTail || wasPinnedToBottom)
        let compensatedScrollTargetY = compensatedScrollTargetY(
            for: update,
            controller: controller,
            visibleRect: visibleRect
        )
        let transition = consumePendingOrImplicitTransition(
            for: update,
            controller: controller,
            stableSnapshots: stableSnapshots
        )

        return VVChatTimelineUpdateTransitionPlan(
            snapshotIndexes: snapshotIndexes,
            transition: transition,
            shouldSuppressPinnedTailViewportMotion: shouldSuppressPinnedTailViewportMotion,
            compensatedScrollTargetY: compensatedScrollTargetY
        )
    }

    func makeLayoutAnimationPlan(
        previousSnapshots: [String: VVLayoutAnimationSnapshot],
        nextSnapshots: [String: VVLayoutAnimationSnapshot],
        liveSnapshots: [String: VVLayoutAnimationSnapshot],
        transition: VVChatTimelineController.PendingLayoutTransition,
        viewportWidth: CGFloat,
        viewportIsFollowing: Bool,
        motion: VVChatTimelineMotionStyle
    ) -> VVChatTimelineLayoutAnimationPlan? {
        guard !nextSnapshots.isEmpty else { return nil }

        let baselineSnapshots = liveSnapshots.isEmpty ? previousSnapshots : liveSnapshots
        var startSnapshots = baselineSnapshots
        var targetSnapshots = nextSnapshots

        for (id, nextSnapshot) in nextSnapshots where baselineSnapshots[id] == nil {
            if viewportIsFollowing {
                // When the viewport follows content (pinned to bottom), inserted
                // items appear at their target position immediately — no accordion
                // slide — because the viewport scrolls to accommodate them and any
                // Y-offset animation creates a visible bounce on short items.
                startSnapshots[id] = nextSnapshot
            } else {
                let insertionTransition = nextSnapshot.transition ?? motion.layoutTransition
                let insertionAnimation = nextSnapshot.animation ?? motion.layoutAnimation
                let insertedStartFrame = insertedItemStartFrame(
                    for: nextSnapshot.frame,
                    transition: insertionTransition
                )
                startSnapshots[id] = VVLayoutAnimationSnapshot(
                    id: id,
                    frame: insertedStartFrame,
                    contentOffset: nextSnapshot.contentOffset,
                    opacity: insertionTransition.insertion.opacity,
                    scale: insertionTransition.insertion.scale,
                    transition: insertionTransition,
                    animation: insertionAnimation
                )
                if targetSnapshots[id]?.transition == nil {
                    targetSnapshots[id]?.transition = insertionTransition
                }
                if targetSnapshots[id]?.animation == nil {
                    targetSnapshots[id]?.animation = insertionAnimation
                }
            }
        }

        for (id, previousSnapshot) in baselineSnapshots where nextSnapshots[id] == nil {
            let removalTransition = previousSnapshot.transition ?? motion.layoutTransition
            let removalAnimation = previousSnapshot.animation ?? motion.layoutAnimation
            let targetFrame = previousSnapshot.frame.offsetBy(
                dx: removalTransition.removal.offset.width,
                dy: removalTransition.removal.offset.height
            )
            targetSnapshots[id] = VVLayoutAnimationSnapshot(
                id: id,
                frame: targetFrame,
                contentOffset: previousSnapshot.contentOffset,
                opacity: removalTransition.removal.opacity,
                scale: removalTransition.removal.scale,
                transition: removalTransition,
                animation: removalAnimation
            )
        }

        let hasInsertionsOrRemovals = nextSnapshots.keys != baselineSnapshots.keys
        // When the viewport follows content (pinned to bottom), shared items appear
        // stationary from the user's perspective — freeze them. When the viewport is
        // stationary (user scrolled away), shared items must slide to their new
        // positions so the accordion effect is visible.
        if hasInsertionsOrRemovals && !viewportIsFollowing {
            animateSharedItemPositions(
                startSnapshots: &startSnapshots,
                targetSnapshots: &targetSnapshots,
                baselineSnapshots: baselineSnapshots,
                nextSnapshots: nextSnapshots,
                motion: motion
            )
        } else {
            freezeSharedItemGeometry(
                startSnapshots: &startSnapshots,
                targetSnapshots: targetSnapshots,
                baselineSnapshots: baselineSnapshots,
                nextSnapshots: nextSnapshots
            )
        }
        stabilizeChatGeometry(
            startSnapshots: &startSnapshots,
            targetSnapshots: &targetSnapshots
        )

        return VVChatTimelineLayoutAnimationPlan(
            startSnapshots: startSnapshots,
            targetSnapshots: targetSnapshots,
            fallbackTransition: motion.layoutTransition,
            fallbackAnimation: motion.layoutAnimation
        )
    }

    private func consumePendingOrImplicitTransition(
        for update: VVChatTimelineController.Update,
        controller: VVChatTimelineController,
        stableSnapshots: [String: VVLayoutAnimationSnapshot]
    ) -> VVChatTimelineController.PendingLayoutTransition? {
        // Always honor an explicitly prepared layout transition, regardless of cause.
        if let transition = update.layoutTransition {
            return transition
        }

        guard shouldCreateImplicitLayoutTransition(for: update, controller: controller) else {
            return nil
        }

        guard update.heightDelta != 0,
              let changedIndex = update.changedIndex,
              let layout = controller.itemLayout(at: changedIndex) else {
            return nil
        }

        let previousTotalHeight = max(0, controller.totalHeight - update.heightDelta)
        let previousSnapshot = stableSnapshots[layout.id]
        let anchorY = previousSnapshot?.frame.origin.y ?? max(0, layout.frame.origin.y - update.heightDelta)

        return VVChatTimelineController.PendingLayoutTransition(
            anchorID: layout.id,
            anchorY: anchorY,
            previousTotalHeight: previousTotalHeight
        )
    }

    private func compensatedScrollTargetY(
        for update: VVChatTimelineController.Update,
        controller: VVChatTimelineController,
        visibleRect: CGRect
    ) -> CGFloat? {
        guard shouldCompensateViewport(for: update) else {
            return nil
        }
        guard update.heightDelta != 0,
              let changedIndex = update.changedIndex,
              let layout = controller.itemLayout(at: changedIndex) else {
            return nil
        }

        let epsilon: CGFloat = 0.5
        guard layout.frame.maxY <= visibleRect.minY + epsilon else { return nil }

        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        return min(max(0, visibleRect.origin.y + update.heightDelta), maxOffset)
    }

    private func animationSnapshotIndexes(
        for update: VVChatTimelineController.Update,
        controller: VVChatTimelineController,
        visibleRect: CGRect,
        visibleRenderRange: Range<Int>,
        layoutAnimationOverscan: CGFloat,
        layoutAnimationItemPadding: Int
    ) -> IndexSet {
        var indexes = IndexSet()

        let viewportRange = controller.visibleLayoutRange(
            in: visibleRect,
            overscan: layoutAnimationOverscan
        )
        indexes.formUnion(
            paddedIndexSet(
                for: viewportRange,
                itemPadding: layoutAnimationItemPadding,
                count: controller.layoutCount
            )
        )
        indexes.formUnion(
            paddedIndexSet(
                for: visibleRenderRange,
                itemPadding: layoutAnimationItemPadding,
                count: controller.layoutCount
            )
        )

        if let changedIndex = update.changedIndex {
            indexes.formUnion(
                paddedIndexSet(
                    around: changedIndex,
                    itemPadding: layoutAnimationItemPadding,
                    count: controller.layoutCount
                )
            )
        }
        for range in [update.insertedIndexes, update.updatedIndexes, update.removedIndexes] {
            for index in range {
                indexes.formUnion(
                    paddedIndexSet(
                        around: index,
                        itemPadding: layoutAnimationItemPadding,
                        count: controller.layoutCount
                    )
                )
            }
        }
        if let anchorID = update.layoutTransition?.anchorID,
           let anchorIndex = controller.indexForLayout(id: anchorID) {
            indexes.formUnion(
                paddedIndexSet(
                    around: anchorIndex,
                    itemPadding: layoutAnimationItemPadding,
                    count: controller.layoutCount
                )
            )
        }
        if controller.state.isLiveTail, controller.layoutCount > 0 {
            let tailStart = max(0, controller.layoutCount - 24)
            indexes.formUnion(IndexSet(integersIn: tailStart..<controller.layoutCount))
        }

        return indexes
    }

    private func paddedIndexSet(
        for range: Range<Int>,
        itemPadding: Int,
        count: Int
    ) -> IndexSet {
        guard count > 0, !range.isEmpty else { return [] }
        let lowerBound = max(0, range.lowerBound - itemPadding)
        let upperBound = min(count, range.upperBound + itemPadding)
        guard lowerBound < upperBound else { return [] }
        return IndexSet(integersIn: lowerBound..<upperBound)
    }

    private func paddedIndexSet(
        around index: Int,
        itemPadding: Int,
        count: Int
    ) -> IndexSet {
        guard count > 0 else { return [] }
        let lowerBound = max(0, index - itemPadding)
        let upperBound = min(count, index + itemPadding + 1)
        guard lowerBound < upperBound else { return [] }
        return IndexSet(integersIn: lowerBound..<upperBound)
    }

    private func insertedItemStartFrame(
        for targetFrame: CGRect,
        transition: VVTransition
    ) -> CGRect {
        targetFrame.offsetBy(
            dx: transition.insertion.offset.width,
            dy: transition.insertion.offset.height
        )
    }

    private func stabilizeChatGeometry(
        startSnapshots: inout [String: VVLayoutAnimationSnapshot],
        targetSnapshots: inout [String: VVLayoutAnimationSnapshot]
    ) {
        for (id, target) in targetSnapshots {
            guard var start = startSnapshots[id] else { continue }

            // Chat timeline motion should animate container geometry, not slide
            // inner content independently. Keeping x/content offsets pinned to the
            // target layout removes left/right and inner up/down jitter.
            start.frame.origin.x = target.frame.origin.x
            start.frame.size.width = target.frame.size.width
            start.contentOffset = target.contentOffset
            startSnapshots[id] = start
        }
    }

    private func animateSharedItemPositions(
        startSnapshots: inout [String: VVLayoutAnimationSnapshot],
        targetSnapshots: inout [String: VVLayoutAnimationSnapshot],
        baselineSnapshots: [String: VVLayoutAnimationSnapshot],
        nextSnapshots: [String: VVLayoutAnimationSnapshot],
        motion: VVChatTimelineMotionStyle
    ) {
        for (id, target) in targetSnapshots {
            guard baselineSnapshots[id] != nil,
                  nextSnapshots[id] != nil,
                  var start = startSnapshots[id] else {
                continue
            }
            // Keep the item at its previous Y so it slides to its new position.
            // Freeze opacity/scale/size so only the vertical position animates.
            start.frame.size = target.frame.size
            start.opacity = target.opacity
            start.scale = target.scale
            if start.animation == nil {
                start.animation = motion.layoutAnimation
            }
            if start.transition == nil {
                start.transition = motion.layoutTransition
            }
            startSnapshots[id] = start
            if targetSnapshots[id]?.animation == nil {
                targetSnapshots[id]?.animation = motion.layoutAnimation
            }
        }
    }

    private func freezeSharedItemGeometry(
        startSnapshots: inout [String: VVLayoutAnimationSnapshot],
        targetSnapshots: [String: VVLayoutAnimationSnapshot],
        baselineSnapshots: [String: VVLayoutAnimationSnapshot],
        nextSnapshots: [String: VVLayoutAnimationSnapshot]
    ) {
        for (id, target) in targetSnapshots {
            guard baselineSnapshots[id] != nil,
                  nextSnapshots[id] != nil,
                  var start = startSnapshots[id] else {
                continue
            }
            start.frame = target.frame
            start.contentOffset = target.contentOffset
            start.opacity = target.opacity
            start.scale = target.scale
            start.transition = target.transition
            start.animation = target.animation
            startSnapshots[id] = start
        }
    }

    private func shouldCreateImplicitLayoutTransition(
        for update: VVChatTimelineController.Update,
        controller: VVChatTimelineController
    ) -> Bool {
        guard update.heightDelta != 0 || !update.insertedIndexes.isEmpty || !update.removedIndexes.isEmpty else {
            return false
        }
        switch update.cause {
        case .tailAppend:
            guard update.insertedIndexes.count == 1,
                  update.updatedIndexes.isEmpty,
                  update.removedIndexes.isEmpty,
                  let insertedIndex = update.insertedIndexes.first,
                  controller.entries.indices.contains(insertedIndex) else {
                return false
            }
            return true
        case .rangeReplace:
            return !update.insertedIndexes.isEmpty || !update.removedIndexes.isEmpty
        case .rebuild, .singleReplace, .streamUpdate, .relayout, .hydrateCorrection, .jumpToLatest:
            return false
        }
    }

    private func shouldCompensateViewport(
        for update: VVChatTimelineController.Update
    ) -> Bool {
        guard update.followPolicy == .none else {
            return false
        }
        switch update.cause {
        case .singleReplace, .rangeReplace, .streamUpdate, .relayout, .hydrateCorrection:
            return true
        case .rebuild, .tailAppend, .jumpToLatest:
            return false
        }
    }
}
