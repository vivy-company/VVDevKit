import CoreGraphics
import Foundation
import VVMetalPrimitives

struct VVChatTimelineViewportAnimationPlan {
    let targetY: CGFloat
    let animation: VVAnimationDescriptor
}

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
    let viewportAnimation: VVChatTimelineViewportAnimationPlan?
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
            update.shouldScrollToBottom && (controller.state.isPinnedToBottom || wasPinnedToBottom)
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
        let viewportAnimation = viewportAnimationPlan(
            transition: transition,
            controller: controller,
            visibleRect: visibleRect,
            shouldSuppressPinnedTailViewportMotion: shouldSuppressPinnedTailViewportMotion
        )

        return VVChatTimelineUpdateTransitionPlan(
            snapshotIndexes: snapshotIndexes,
            transition: transition,
            shouldSuppressPinnedTailViewportMotion: shouldSuppressPinnedTailViewportMotion,
            compensatedScrollTargetY: compensatedScrollTargetY,
            viewportAnimation: viewportAnimation
        )
    }

    func makeLayoutAnimationPlan(
        previousSnapshots: [String: VVLayoutAnimationSnapshot],
        nextSnapshots: [String: VVLayoutAnimationSnapshot],
        liveSnapshots: [String: VVLayoutAnimationSnapshot],
        transition: VVChatTimelineController.PendingLayoutTransition,
        viewportWidth: CGFloat,
        motion: VVChatTimelineMotionStyle
    ) -> VVChatTimelineLayoutAnimationPlan? {
        guard !nextSnapshots.isEmpty else { return nil }

        let baselineSnapshots = liveSnapshots.isEmpty ? previousSnapshots : liveSnapshots
        let anchorSnapshot = baselineSnapshots[transition.anchorID] ?? previousSnapshots[transition.anchorID]
        let anchorFrame = anchorSnapshot?.frame ?? CGRect(
            x: 0,
            y: transition.anchorY,
            width: viewportWidth,
            height: 0
        )
        var startSnapshots = baselineSnapshots
        var targetSnapshots = nextSnapshots

        for (id, nextSnapshot) in nextSnapshots where baselineSnapshots[id] == nil {
            let insertedStartFrame = insertedItemStartFrame(
                for: nextSnapshot.frame,
                anchorFrame: anchorFrame
            )
            startSnapshots[id] = VVLayoutAnimationSnapshot(
                id: id,
                frame: insertedStartFrame,
                contentOffset: nextSnapshot.contentOffset,
                transition: nextSnapshot.transition ?? motion.layoutTransition,
                animation: nextSnapshot.animation ?? motion.layoutAnimation
            )
            if targetSnapshots[id]?.transition == nil {
                targetSnapshots[id]?.transition = motion.layoutTransition
            }
            if targetSnapshots[id]?.animation == nil {
                targetSnapshots[id]?.animation = motion.layoutAnimation
            }
        }

        for (id, previousSnapshot) in baselineSnapshots where nextSnapshots[id] == nil {
            let targetFrame = previousSnapshot.frame.offsetBy(
                dx: 0,
                dy: -min(max(previousSnapshot.frame.height * 0.35, 10), 24)
            )
            targetSnapshots[id] = VVLayoutAnimationSnapshot(
                id: id,
                frame: targetFrame,
                contentOffset: previousSnapshot.contentOffset,
                transition: previousSnapshot.transition ?? motion.layoutTransition,
                animation: previousSnapshot.animation ?? motion.layoutAnimation
            )
        }

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
        if let transition = controller.pendingLayoutTransition {
            return transition
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
        guard update.heightDelta != 0,
              let changedIndex = update.changedIndex,
              !update.shouldScrollToBottom,
              let layout = controller.itemLayout(at: changedIndex) else {
            return nil
        }

        let epsilon: CGFloat = 0.5
        guard layout.frame.maxY <= visibleRect.minY + epsilon else { return nil }

        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        return min(max(0, visibleRect.origin.y + update.heightDelta), maxOffset)
    }

    private func viewportAnimationPlan(
        transition: VVChatTimelineController.PendingLayoutTransition?,
        controller: VVChatTimelineController,
        visibleRect: CGRect,
        shouldSuppressPinnedTailViewportMotion: Bool
    ) -> VVChatTimelineViewportAnimationPlan? {
        guard let transition else { return nil }
        let heightDelta = controller.totalHeight - transition.previousTotalHeight
        guard abs(heightDelta) > 1 else { return nil }

        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)

        if heightDelta < 0 {
            let currentY = visibleRect.origin.y
            let clampedY = min(currentY, maxOffset)
            guard abs(clampedY - currentY) > 1 else { return nil }
            return VVChatTimelineViewportAnimationPlan(
                targetY: clampedY,
                animation: controller.currentStyle.motion.viewportClampAnimation
            )
        }

        guard controller.state.isPinnedToBottom, !shouldSuppressPinnedTailViewportMotion else {
            return nil
        }
        return VVChatTimelineViewportAnimationPlan(
            targetY: maxOffset,
            animation: controller.currentStyle.motion.viewportFollowAnimation
        )
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
        if let anchorID = controller.pendingLayoutTransition?.anchorID,
           let anchorIndex = controller.indexForLayout(id: anchorID) {
            indexes.formUnion(
                paddedIndexSet(
                    around: anchorIndex,
                    itemPadding: layoutAnimationItemPadding,
                    count: controller.layoutCount
                )
            )
        }
        if controller.state.isPinnedToBottom, controller.layoutCount > 0 {
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

    private func insertedItemStartFrame(for targetFrame: CGRect, anchorFrame: CGRect) -> CGRect {
        let verticalShift = min(max(targetFrame.height * 0.55, 16), 42)
        let anchorBottom = anchorFrame.maxY
        let startY: CGFloat

        if targetFrame.minY >= anchorBottom {
            startY = max(
                anchorBottom - min(targetFrame.height * 0.35, 12),
                targetFrame.minY - verticalShift
            )
        } else {
            startY = targetFrame.minY - min(verticalShift, 28)
        }

        return CGRect(
            x: targetFrame.origin.x,
            y: startY,
            width: targetFrame.width,
            height: targetFrame.height
        )
    }
}
