#if os(macOS)
import AppKit
import CoreText
import Foundation
import Metal
import QuartzCore
import VVMarkdown
import VVMetalPrimitives

/// Position within the chat timeline: item index + block/run/character within that item's markdown layout.
public struct ChatTextPosition: Sendable, Hashable, Comparable, VVMetalPrimitives.VVTextPosition {
    public let itemIndex: Int
    public let blockIndex: Int
    public let runIndex: Int
    public let characterOffset: Int

    public static func < (lhs: Self, rhs: Self) -> Bool {
        if lhs.itemIndex != rhs.itemIndex { return lhs.itemIndex < rhs.itemIndex }
        if lhs.blockIndex != rhs.blockIndex { return lhs.blockIndex < rhs.blockIndex }
        if lhs.runIndex != rhs.runIndex { return lhs.runIndex < rhs.runIndex }
        return lhs.characterOffset < rhs.characterOffset
    }

    /// Convert to MarkdownTextPosition for VVMarkdownSelectionHelper calls.
    var markdownPosition: MarkdownTextPosition {
        MarkdownTextPosition(blockIndex: blockIndex, runIndex: runIndex, characterOffset: characterOffset)
    }
}

/// Plain NSView used as the scroll view's documentView purely for content sizing.
private final class ChatTimelineDocumentView: NSView {
    override var isFlipped: Bool { true }
}

public final class VVChatTimelineView: NSView, VVChatTimelineRenderDataSource {
    private let scrollView: VVChatTimelineScrollView
    private let documentView: ChatTimelineDocumentView
    private let metalView: VVChatTimelineMetalView
    private let jumpButton: NSButton
    private var didInitialScroll: Bool = false
    private var controllerObservation: NSObjectProtocol?
    private var currentFont: VVFont?
    private var imageStore: VVChatTimelineImageStore?
    public var metalContext: VVMetalContext?

    // Selection support
    private let selectionController = VVTextSelectionController<ChatTextPosition>()
    private let selectionColor: SIMD4<Float> = .blue.withOpacity(0.4)
    public var onStateChange: ((VVChatTimelineState) -> Void)?
    public var onUserMessageCopyAction: ((String) -> Void)?
    public var onUserMessageCopyHoverChange: ((String?) -> Void)?
    public var onEntryActivate: ((String) -> Void)?
    public var onLinkActivate: ((String) -> Void)?
    private var hoveredFooterActionMessageID: String?
    private var hoveredLinkURL: String?
    private var hoveredInteractiveRegionKey: String?
    private var isPointingCursorActive = false
    private var jumpAnimationToken = UUID()
    private var isAnimatingJump = false
    private var scrollAnimationStartTime: CFTimeInterval = 0
    private var scrollAnimationDuration: CFTimeInterval = 0
    private var scrollAnimationStartY: CGFloat = 0
    private var scrollAnimationTargetY: CGFloat = 0
    private var scrollAnimationCompletion: (() -> Void)?
    private var scrollAnimationCurve: VVEasing = .easeOut
    private var layoutAnimator = VVLayoutTransitionAnimator()
    private var animatedLayoutSnapshots: [String: VVLayoutAnimationSnapshot] = [:]
    private var stableLayoutSnapshots: [String: VVLayoutAnimationSnapshot] = [:]
    private var visibleRenderRange: Range<Int> = 0..<0
    private struct SelectionHelperCacheKey: Hashable {
        let messageID: String
        let revision: Int
    }
    private struct TimelineInteractionContext {
        let documentPoint: CGPoint
        let itemIndex: Int
        let layout: VVChatTimelineController.ItemLayout
        let message: VVChatMessage
        let rendered: VVChatRenderedMessage
        let localPoint: CGPoint
    }
    private struct TimelineHoverTargets {
        let footerActionMessageID: String?
        let linkURL: String?
        let interactiveRegionHit: (messageID: String, region: VVChatInteractiveRegion)?

        static let empty = TimelineHoverTargets(
            footerActionMessageID: nil,
            linkURL: nil,
            interactiveRegionHit: nil
        )
    }
    private var selectionHelperCache: [SelectionHelperCacheKey: VVMarkdownSelectionHelper] = [:]
    private var selectionHelperCacheOrder: [SelectionHelperCacheKey] = []
    private let maxSelectionHelperCacheEntries = 8
    private var pendingEntryActivationID: String?
    private var suppressEntryActivationForCurrentClick = false
    private var didDragDuringCurrentClick = false
    private var displayLink: CVDisplayLink?
    private var pendingControllerUpdate: VVChatTimelineController.Update?
    private var hasScheduledControllerUpdateApply = false
    private var pendingControllerUpdateWorkItem: DispatchWorkItem?

    public var controller: VVChatTimelineController? {
        didSet {
            guard controller !== oldValue else { return }
            bindController(oldValue: oldValue)
        }
    }


    public init(frame frameRect: NSRect, metalContext: VVMetalContext? = nil) {
        self.metalContext = metalContext ?? VVMetalContext.shared
        scrollView = VVChatTimelineScrollView(frame: frameRect)
        documentView = ChatTimelineDocumentView(frame: frameRect)
        metalView = VVChatTimelineMetalView(frame: frameRect, font: .systemFont(ofSize: 14), metalContext: self.metalContext)
        jumpButton = NSButton(title: "Jump to latest", target: nil, action: nil)
        super.init(frame: frameRect)
        setup()
    }

    required init?(coder: NSCoder) {
        self.metalContext = VVMetalContext.shared
        scrollView = VVChatTimelineScrollView(frame: .zero)
        documentView = ChatTimelineDocumentView(frame: .zero)
        metalView = VVChatTimelineMetalView(frame: .zero, font: .systemFont(ofSize: 14), metalContext: VVMetalContext.shared)
        jumpButton = NSButton(title: "Jump to latest", target: nil, action: nil)
        super.init(coder: coder)
        setup()
    }

    deinit {
        stopDisplayLink()
        pendingControllerUpdateWorkItem?.cancel()
        if let controllerObservation {
            NotificationCenter.default.removeObserver(controllerObservation)
        }
    }

    private func setup() {
        wantsLayer = true
        layer?.backgroundColor = NSColor.clear.cgColor

        scrollView.drawsBackground = false
        scrollView.hasVerticalScroller = true
        scrollView.scrollerStyle = .overlay
        scrollView.autohidesScrollers = true
        scrollView.documentView = documentView
        scrollView.contentView.postsBoundsChangedNotifications = true
        scrollView.onInteractionChange = { [weak self] isInteracting in
            self?.controller?.markUserInteraction(isInteracting)
        }
        addSubview(scrollView)

        // MTKView is a sibling of the document view, always pinned to the visible
        // viewport (same pattern as VVMetalEditorContainerView / MetalTextView).
        scrollView.addSubview(metalView)
        metalView.renderDataSource = self
        metalView.selectionDelegate = self
        if let device = metalView.device {
            let store = VVChatTimelineImageStore(device: device, scaleFactorProvider: { [weak self] url in
                self?.imageScaleFactor(for: url) ?? 2.0
            })
            store.onImageSizeUpdate = { [weak self] url, size in
                self?.controller?.updateImageSize(url: url, size: size)
            }
            store.onImageLoaded = { [weak self] _ in
                self?.metalView.setNeedsDisplay(self?.metalView.bounds ?? .zero)
            }
            imageStore = store
        }

        jumpButton.target = self
        jumpButton.action = #selector(handleJumpToLatest)
        jumpButton.isHidden = true
        jumpButton.bezelStyle = .rounded
        jumpButton.controlSize = .regular
        addSubview(jumpButton)

        controllerObservation = NotificationCenter.default.addObserver(
            forName: NSView.boundsDidChangeNotification,
            object: scrollView.contentView,
            queue: .main
        ) { [weak self] _ in
            self?.handleScroll()
        }
    }

    public override func layout() {
        super.layout()
        scrollView.frame = bounds
        updateMetalViewport()
        updateContentWidth()
        layoutJumpButton()
        updateVisibleRenderRange()
    }

    public override func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        if window != nil {
            ensureDisplayLink()
            updateVisibleRenderRange()
        } else {
            stopDisplayLink()
        }
    }

    private func layoutJumpButton() {
        let buttonSize = jumpButton.intrinsicContentSize
        let padding: CGFloat = 12
        jumpButton.frame = CGRect(
            x: bounds.maxX - buttonSize.width - padding,
            y: bounds.maxY - buttonSize.height - padding,
            width: buttonSize.width,
            height: buttonSize.height
        )
    }

    private func bindController(oldValue: VVChatTimelineController?) {
        oldValue?.onUpdate = nil
        pendingControllerUpdateWorkItem?.cancel()
        pendingControllerUpdateWorkItem = nil
        pendingControllerUpdate = nil
        hasScheduledControllerUpdateApply = false
        didInitialScroll = false
        stopLayoutAnimation()
        stableLayoutSnapshots.removeAll(keepingCapacity: false)
        animatedLayoutSnapshots.removeAll(keepingCapacity: false)
        clearSelectionHelperCache()
        visibleRenderRange = 0..<0
        isPointingCursorActive = false
        controller?.onUpdate = { [weak self] update in
            self?.enqueue(update: update)
        }
        if let style = controller?.currentStyle {
            metalView.updateFont(style.baseFont)
            currentFont = style.baseFont
        }
        updateContentWidth()
        apply(update: .init(totalHeight: controller?.totalHeight ?? 0))
    }

    private func enqueue(update: VVChatTimelineController.Update) {
        pendingControllerUpdate = merge(pendingControllerUpdate, with: update)
        guard !hasScheduledControllerUpdateApply else { return }
        hasScheduledControllerUpdateApply = true
        let interval = controller?.currentStyle.motion.updateBatchInterval ?? 0
        let workItem = DispatchWorkItem { [weak self] in
            guard let self else { return }
            self.hasScheduledControllerUpdateApply = false
            self.pendingControllerUpdateWorkItem = nil
            guard let update = self.pendingControllerUpdate else { return }
            self.pendingControllerUpdate = nil
            self.apply(update: update)
        }
        pendingControllerUpdateWorkItem = workItem
        DispatchQueue.main.asyncAfter(deadline: .now() + max(0, interval), execute: workItem)
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
            hasUnreadNewContent: incoming.hasUnreadNewContent
        )
    }

    private func updateContentWidth() {
        guard let controller else { return }
        let width = scrollView.contentView.bounds.width
        controller.updateRenderWidth(width)
        clearSelectionHelperCache()
        metalView.setNeedsDisplay(metalView.bounds)
    }

    private func apply(update: VVChatTimelineController.Update) {
        guard let controller else { return }
        invalidateSelectionHelpers(for: update.updatedIndexes.compactMap { controller.itemLayout(at: $0)?.id })
        let latestSnapshots = currentLayoutSnapshots()
        let style = controller.currentStyle
        if !isSameFont(style.baseFont, currentFont) {
            metalView.updateFont(style.baseFont)
            currentFont = style.baseFont
        }
        updateDocumentHeight(controller.totalHeight)
        clampScrollIfNeeded()
        updateVisibleRenderRange()
        jumpButton.isHidden = !update.hasUnreadNewContent

        if update.heightDelta != 0,
           let changedIndex = update.changedIndex,
           !update.shouldScrollToBottom,
           let layout = controller.itemLayout(at: changedIndex) {
            compensateScrollIfNeeded(layout: layout, delta: update.heightDelta)
        }

        let transition = consumePendingOrImplicitTransition(for: update, controller: controller)

        if !didInitialScroll, update.totalHeight > 0 {
            scrollToBottom(animated: false)
            didInitialScroll = true
        } else if update.shouldScrollToBottom, !isAnimatingJump, transition == nil {
            scrollToBottom(animated: false)
            controller.updatePinnedState(distanceFromBottom: 0)
        }

        if let transition {
            controller.pendingLayoutTransition = nil
            let heightDelta = controller.totalHeight - transition.previousTotalHeight
            startLayoutAnimation(
                from: stableLayoutSnapshots,
                to: latestSnapshots,
                transition: transition
            )

            if abs(heightDelta) > 1 {
                let visibleRect = scrollView.contentView.bounds
                let contentHeight = max(controller.totalHeight, visibleRect.height)
                let maxOffset = max(0, contentHeight - visibleRect.height)

                if heightDelta < 0 {
                    // Collapse: content shrank. If we're scrolled past the new max, animate to clamp.
                    let currentY = visibleRect.origin.y
                    let clampedY = min(currentY, maxOffset)
                    if abs(clampedY - currentY) > 1 {
                        isAnimatingJump = true
                        let motion = style.motion.viewportClampAnimation
                        animateScroll(toY: clampedY, animation: motion, token: nil) { [weak self] in
                            self?.isAnimatingJump = false
                        }
                    }
                } else {
                    // Expand: content grew. If pinned to bottom, animate to new bottom.
                    if controller.state.isPinnedToBottom {
                        isAnimatingJump = true
                        let motion = style.motion.viewportFollowAnimation
                        animateScroll(toY: maxOffset, animation: motion, token: nil) { [weak self] in
                            self?.isAnimatingJump = false
                        }
                    }
                }
            }
        } else {
            stopLayoutAnimation(commitTargetSnapshots: false)
            stableLayoutSnapshots = latestSnapshots
        }

        requestImagesForVisibleItems()
        metalView.setNeedsDisplay(metalView.bounds)
        onStateChange?(controller.state)
    }

    private func consumePendingOrImplicitTransition(
        for update: VVChatTimelineController.Update,
        controller: VVChatTimelineController
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
        let previousSnapshot = stableLayoutSnapshots[layout.id]
        let anchorY = previousSnapshot?.frame.origin.y ?? max(0, layout.frame.origin.y - update.heightDelta)

        return VVChatTimelineController.PendingLayoutTransition(
            anchorID: layout.id,
            anchorY: anchorY,
            previousTotalHeight: previousTotalHeight
        )
    }

    private func updateDocumentHeight(_ height: CGFloat) {
        let contentBounds = scrollView.contentView.bounds
        let width = contentBounds.width
        let minHeight = contentBounds.height
        let newFrame = CGRect(x: 0, y: 0, width: width, height: max(height, minHeight))
        if documentView.frame != newFrame {
            documentView.frame = newFrame
        }
        updateMetalViewport()
    }

    /// Keep MTKView pinned to the visible viewport (same pattern as MetalTextView).
    private func updateMetalViewport() {
        let viewportSize = scrollView.contentView.bounds.size
        let viewportOrigin = scrollView.contentView.frame.origin
        metalView.frame = CGRect(origin: viewportOrigin, size: viewportSize)
    }

    private func clampScrollIfNeeded() {
        guard let controller else { return }
        let visibleRect = scrollView.contentView.bounds
        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        if visibleRect.origin.y > maxOffset {
            let newOrigin = CGPoint(x: visibleRect.origin.x, y: maxOffset)
            scrollView.contentView.setBoundsOrigin(newOrigin)
            scrollView.reflectScrolledClipView(scrollView.contentView)
        }
    }

    private func compensateScrollIfNeeded(layout: VVChatTimelineController.ItemLayout, delta: CGFloat) {
        guard let controller else { return }
        let visibleRect = scrollView.contentView.bounds
        // Preserve viewport position only when the changed item is fully above the viewport.
        // If the item intersects the visible region, compensating causes a perceived jump.
        let epsilon: CGFloat = 0.5
        if layout.frame.maxY <= visibleRect.minY + epsilon {
            let contentHeight = max(controller.totalHeight, visibleRect.height)
            let maxOffset = max(0, contentHeight - visibleRect.height)
            let targetY = min(max(0, visibleRect.origin.y + delta), maxOffset)
            let newOrigin = CGPoint(x: visibleRect.origin.x, y: targetY)
            scrollView.contentView.scroll(to: newOrigin)
            scrollView.reflectScrolledClipView(scrollView.contentView)
        }
    }

    private func handleScroll() {
        guard let controller else { return }
        updateMetalViewport()
        updateVisibleRenderRange()
        requestImagesForVisibleItems()
        metalView.setNeedsDisplay(metalView.bounds)

        // During a jump animation, skip state updates that could interfere
        // with the in-flight scroll. Only update the viewport for rendering.
        guard !isAnimatingJump else { return }

        let visibleRect = scrollView.contentView.bounds
        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        let distanceFromBottom = maxOffset - visibleRect.origin.y
        controller.updatePinnedState(distanceFromBottom: distanceFromBottom)
        jumpButton.isHidden = !controller.state.hasUnreadNewContent
        onStateChange?(controller.state)
    }

    public func scrollToBottom(animated: Bool) {
        cancelJumpToLatestAnimation()
        guard let controller else { return }
        let visibleRect = scrollView.contentView.bounds
        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        let newOrigin = CGPoint(x: visibleRect.origin.x, y: maxOffset)
        if animated {
            animateScroll(toY: maxOffset, animation: controller.currentStyle.motion.viewportFollowAnimation, token: nil)
        } else {
            scrollView.contentView.setBoundsOrigin(newOrigin)
            scrollView.reflectScrolledClipView(scrollView.contentView)
        }
    }

    public func restoreScrollPosition(_ origin: CGPoint) {
        scrollView.contentView.setBoundsOrigin(origin)
        scrollView.reflectScrolledClipView(scrollView.contentView)
        didInitialScroll = true
    }

    // prepareLayoutTransition is now on the controller — no view-side capture needed

    @objc private func handleJumpToLatest() {
        jumpToLatestAnimated()
    }

    public func jumpToLatestAnimated() {
        isAnimatingJump = true
        controller?.jumpToLatest()
        animateJumpToLatest()
        if let controller {
            onStateChange?(controller.state)
        }
    }

    private func animateJumpToLatest() {
        guard let controller else {
            isAnimatingJump = false
            return
        }
        let visibleRect = scrollView.contentView.bounds
        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        let startY = visibleRect.origin.y
        let distance = maxOffset - startY

        guard distance > 1 else {
            scrollToBottom(animated: false)
            isAnimatingJump = false
            return
        }
        let token = UUID()
        jumpAnimationToken = token
        animateScroll(toY: maxOffset, animation: controller.currentStyle.motion.jumpToLatestAnimation, token: token) { [weak self] in
            self?.isAnimatingJump = false
        }
    }

    private func animateScroll(
        toY targetY: CGFloat,
        animation: VVAnimationDescriptor,
        token: UUID?,
        completion: (() -> Void)? = nil
    ) {
        scrollAnimationStartY = scrollView.contentView.bounds.origin.y
        scrollAnimationTargetY = targetY
        scrollAnimationDuration = max(0.05, animation.duration)
        scrollAnimationStartTime = CACurrentMediaTime()
        scrollAnimationCurve = animation.easing
        scrollAnimationCompletion = { [weak self] in
            guard let self else { return }
            if let token, token != self.jumpAnimationToken { return }
            self.scrollView.reflectScrolledClipView(self.scrollView.contentView)
            completion?()
        }
        startDisplayLink()
    }

    private func animateScroll(
        toY targetY: CGFloat,
        duration: TimeInterval,
        curve: VVEasing,
        token: UUID?,
        completion: (() -> Void)? = nil
    ) {
        animateScroll(
            toY: targetY,
            animation: .timing(duration: duration, easing: curve),
            token: token,
            completion: completion
        )
    }

    private func stopScrollAnimation() {
        scrollAnimationDuration = 0
        scrollAnimationCompletion = nil
    }

    private func cancelJumpToLatestAnimation() {
        stopScrollAnimation()
        scrollAnimationCompletion = nil
        jumpAnimationToken = UUID()
        isAnimatingJump = false
    }

    private func currentLayoutSnapshots() -> [String: VVLayoutAnimationSnapshot] {
        guard let controller else { return [:] }
        var snapshots: [String: VVLayoutAnimationSnapshot] = [:]
        snapshots.reserveCapacity(controller.layouts.count)
        for layout in controller.layouts {
            snapshots[layout.id] = VVLayoutAnimationSnapshot(
                id: layout.id,
                frame: layout.frame,
                contentOffset: layout.contentOffset
            )
        }
        return snapshots
    }

    private func startLayoutAnimation(
        from previousSnapshots: [String: VVLayoutAnimationSnapshot],
        to nextSnapshots: [String: VVLayoutAnimationSnapshot],
        transition: VVChatTimelineController.PendingLayoutTransition
    ) {
        guard !nextSnapshots.isEmpty else {
            stableLayoutSnapshots = nextSnapshots
            return
        }
        let liveSnapshots = layoutAnimator.isRunning ? layoutAnimator.state().snapshots : [:]
        let baselineSnapshots = liveSnapshots.isEmpty ? previousSnapshots : liveSnapshots
        let anchorSnapshot = baselineSnapshots[transition.anchorID] ?? previousSnapshots[transition.anchorID]
        let anchorFrame = anchorSnapshot?.frame ?? CGRect(x: 0, y: transition.anchorY, width: scrollView.contentView.bounds.width, height: 0)
        var startSnapshots = baselineSnapshots
        var targetSnapshots = nextSnapshots

        for (id, nextSnapshot) in nextSnapshots where baselineSnapshots[id] == nil {
            let insertedStartFrame = insertedItemStartFrame(for: nextSnapshot.frame, anchorFrame: anchorFrame)
            startSnapshots[id] = VVLayoutAnimationSnapshot(
                id: id,
                frame: insertedStartFrame,
                contentOffset: nextSnapshot.contentOffset,
                transition: nextSnapshot.transition ?? controller?.currentStyle.motion.layoutTransition ?? .accordion,
                animation: nextSnapshot.animation ?? controller?.currentStyle.motion.layoutAnimation ?? .smooth(duration: 0.2)
            )
            if targetSnapshots[id]?.transition == nil {
                targetSnapshots[id]?.transition = controller?.currentStyle.motion.layoutTransition ?? .accordion
            }
            if targetSnapshots[id]?.animation == nil {
                targetSnapshots[id]?.animation = controller?.currentStyle.motion.layoutAnimation ?? .smooth(duration: 0.2)
            }
        }

        for (id, previousSnapshot) in baselineSnapshots where nextSnapshots[id] == nil {
            let targetFrame = previousSnapshot.frame.offsetBy(dx: 0, dy: -min(max(previousSnapshot.frame.height * 0.35, 10), 24))
            targetSnapshots[id] = VVLayoutAnimationSnapshot(
                id: id,
                frame: targetFrame,
                contentOffset: previousSnapshot.contentOffset,
                transition: previousSnapshot.transition ?? controller?.currentStyle.motion.layoutTransition ?? .accordion,
                animation: previousSnapshot.animation ?? controller?.currentStyle.motion.layoutAnimation ?? .smooth(duration: 0.2)
            )
        }

        let motion = controller?.currentStyle.motion ?? .init()
        layoutAnimator.start(
            from: startSnapshots,
            to: targetSnapshots,
            fallbackTransition: motion.layoutTransition,
            fallbackAnimation: motion.layoutAnimation
        )
        animatedLayoutSnapshots = layoutAnimator.state().snapshots
        startDisplayLink()
    }

    private func insertedItemStartFrame(for targetFrame: CGRect, anchorFrame: CGRect) -> CGRect {
        let verticalShift = min(max(targetFrame.height * 0.55, 16), 42)
        let anchorBottom = anchorFrame.maxY
        let startY: CGFloat

        if targetFrame.minY >= anchorBottom {
            startY = max(anchorBottom - min(targetFrame.height * 0.35, 12), targetFrame.minY - verticalShift)
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

    private func stopLayoutAnimation(commitTargetSnapshots: Bool = true) {
        if commitTargetSnapshots {
            let finalSnapshots = layoutAnimator.state().snapshots
            if !finalSnapshots.isEmpty {
                stableLayoutSnapshots = finalSnapshots
            }
        }
        layoutAnimator.complete(with: stableLayoutSnapshots)
        animatedLayoutSnapshots.removeAll(keepingCapacity: true)
    }

    private func layoutAnimationTick(at now: CFTimeInterval) {
        let state = layoutAnimator.state(at: now)
        animatedLayoutSnapshots = state.snapshots
        metalView.setNeedsDisplay(metalView.bounds)

        if state.isComplete {
            stableLayoutSnapshots = state.snapshots
            stopLayoutAnimation()
            metalView.setNeedsDisplay(metalView.bounds)
        }
    }

    private func scrollAnimationTick(at now: CFTimeInterval) {
        guard scrollAnimationDuration > 0 else { return }
        let elapsed = now - scrollAnimationStartTime
        let progress = min(1.0, elapsed / scrollAnimationDuration)
        let t = scrollAnimationCurve.value(at: CGFloat(progress))

        let currentY = scrollAnimationStartY + (scrollAnimationTargetY - scrollAnimationStartY) * t
        let origin = CGPoint(x: scrollView.contentView.bounds.origin.x, y: currentY)
        scrollView.contentView.setBoundsOrigin(origin)
        scrollView.reflectScrolledClipView(scrollView.contentView)
        updateMetalViewport()
        updateVisibleRenderRange()
        metalView.setNeedsDisplay(metalView.bounds)

        if progress >= 1.0 {
            scrollAnimationDuration = 0
            let completion = scrollAnimationCompletion
            scrollAnimationCompletion = nil
            completion?()
        }
    }

    private func ensureDisplayLink() {
        guard displayLink == nil else { return }
        var link: CVDisplayLink?
        CVDisplayLinkCreateWithActiveCGDisplays(&link)
        guard let link else { return }

        let callback: CVDisplayLinkOutputCallback = { _, _, _, _, _, userInfo in
            let view = Unmanaged<VVChatTimelineView>.fromOpaque(userInfo!).takeUnretainedValue()
            DispatchQueue.main.async {
                view.animationFrameTick()
            }
            return kCVReturnSuccess
        }
        CVDisplayLinkSetOutputCallback(link, callback, Unmanaged.passUnretained(self).toOpaque())
        displayLink = link
    }

    private func startDisplayLink() {
        ensureDisplayLink()
        guard let displayLink, !CVDisplayLinkIsRunning(displayLink) else { return }
        CVDisplayLinkStart(displayLink)
    }

    private func stopDisplayLink() {
        guard let displayLink, CVDisplayLinkIsRunning(displayLink) else { return }
        CVDisplayLinkStop(displayLink)
    }

    private func animationFrameTick() {
        let now = CACurrentMediaTime()
        if scrollAnimationDuration > 0 {
            scrollAnimationTick(at: now)
        }
        if layoutAnimator.isRunning {
            layoutAnimationTick(at: now)
        }
        if scrollAnimationDuration <= 0 && !layoutAnimator.isRunning {
            stopDisplayLink()
        }
    }

    private func updateVisibleRenderRange() {
        guard let controller else {
            visibleRenderRange = 0..<0
            return
        }
        let layouts = controller.layouts
        guard !layouts.isEmpty else {
            visibleRenderRange = 0..<0
            return
        }

        let viewport = scrollView.contentView.bounds
        let overscan: CGFloat = 900
        let minY = viewport.minY - overscan
        let maxY = viewport.maxY + overscan

        let lower = lowerBound(forMaxYAbove: minY, layouts: layouts)
        let upper = upperBound(forMinYBelow: maxY, layouts: layouts)
        visibleRenderRange = lower..<max(lower, upper)
    }

    private func clearSelectionHelperCache() {
        selectionHelperCache.removeAll(keepingCapacity: true)
        selectionHelperCacheOrder.removeAll(keepingCapacity: true)
    }

    private func invalidateSelectionHelpers(for messageIDs: [String]) {
        guard !messageIDs.isEmpty else { return }
        let ids = Set(messageIDs)
        selectionHelperCache = selectionHelperCache.filter { !ids.contains($0.key.messageID) }
        selectionHelperCacheOrder.removeAll { ids.contains($0.messageID) }
    }

    private func cachedSelectionHelper(messageID: String, rendered: VVChatRenderedMessage) -> VVMarkdownSelectionHelper {
        let key = SelectionHelperCacheKey(messageID: messageID, revision: rendered.revision)
        if let cached = selectionHelperCache[key] {
            touchSelectionHelperCache(key)
            return cached
        }

        let helper = VVMarkdownSelectionHelper(layout: rendered.layout, layoutEngine: rendered.layoutEngine)
        selectionHelperCache[key] = helper
        selectionHelperCacheOrder.removeAll { $0 == key }
        selectionHelperCacheOrder.append(key)
        while selectionHelperCacheOrder.count > maxSelectionHelperCacheEntries {
            let evicted = selectionHelperCacheOrder.removeFirst()
            selectionHelperCache.removeValue(forKey: evicted)
        }
        return helper
    }

    private func touchSelectionHelperCache(_ key: SelectionHelperCacheKey) {
        selectionHelperCacheOrder.removeAll { $0 == key }
        selectionHelperCacheOrder.append(key)
    }

    private func itemIndex(containingDocumentPoint point: CGPoint) -> Int? {
        guard let controller else { return nil }
        let layouts = controller.layouts
        guard !layouts.isEmpty else { return nil }

        var low = 0
        var high = layouts.count - 1
        while low <= high {
            let mid = (low + high) / 2
            let frame = layouts[mid].frame
            if point.y < frame.minY {
                high = mid - 1
            } else if point.y > frame.maxY {
                low = mid + 1
            } else {
                return frame.contains(point) ? mid : nil
            }
        }
        return nil
    }

    private func nearestItemIndex(forDocumentY y: CGFloat) -> Int? {
        guard let controller else { return nil }
        let layouts = controller.layouts
        guard !layouts.isEmpty else { return nil }

        var low = 0
        var high = layouts.count - 1
        while low <= high {
            let mid = (low + high) / 2
            let frame = layouts[mid].frame
            if y < frame.minY {
                high = mid - 1
            } else if y > frame.maxY {
                low = mid + 1
            } else {
                return mid
            }
        }

        if low >= layouts.count { return layouts.count - 1 }
        if high < 0 { return 0 }

        let lowerDistance = abs(y - layouts[high].frame.maxY)
        let upperDistance = abs(layouts[low].frame.minY - y)
        return lowerDistance <= upperDistance ? high : low
    }

    private func lowerBound(forMaxYAbove value: CGFloat, layouts: [VVChatTimelineController.ItemLayout]) -> Int {
        var low = 0
        var high = layouts.count
        while low < high {
            let mid = (low + high) / 2
            if layouts[mid].frame.maxY < value {
                low = mid + 1
            } else {
                high = mid
            }
        }
        return low
    }

    private func upperBound(forMinYBelow value: CGFloat, layouts: [VVChatTimelineController.ItemLayout]) -> Int {
        var low = 0
        var high = layouts.count
        while low < high {
            let mid = (low + high) / 2
            if layouts[mid].frame.minY <= value {
                low = mid + 1
            } else {
                high = mid
            }
        }
        return low
    }

    // MARK: - VVChatTimelineRenderDataSource

    public var renderItemCount: Int {
        controller?.layouts.count ?? 0
    }

    public func visibleRenderIndexes() -> Range<Int> {
        visibleRenderRange
    }

    public func renderItem(at index: Int) -> VVChatTimelineRenderItem? {
        guard let controller,
              let layout = controller.itemLayout(at: index),
              let rendered = controller.renderedMessage(at: index) else { return nil }
        let snapshot = animatedLayoutSnapshots[layout.id] ?? stableLayoutSnapshots[layout.id]
        return VVChatTimelineRenderItem(
            id: layout.id,
            frame: snapshot?.frame ?? layout.frame,
            contentOffset: snapshot?.contentOffset ?? layout.contentOffset,
            scene: rendered.scene,
            orderedPrimitiveIndices: rendered.orderedPrimitiveIndices
        )
    }

    public var viewportRect: CGRect {
        scrollView.contentView.bounds
    }

    public var backgroundColor: SIMD4<Float> {
        controller?.currentStyle.backgroundColor ?? .black
    }

    public func texture(for url: String) -> MTLTexture? {
        imageStore?.texture(for: url)
    }

    private func isSameFont(_ lhs: VVFont?, _ rhs: VVFont?) -> Bool {
        guard let lhs, let rhs else { return false }
        return lhs.fontName == rhs.fontName && lhs.pointSize == rhs.pointSize
    }

    private func requestImagesForVisibleItems() {
        guard let controller, let imageStore else { return }
        for index in visibleRenderRange {
            guard let rendered = controller.renderedMessage(at: index) else { continue }
            for url in rendered.imageURLs {
                imageStore.ensureImage(url: url)
            }
        }
    }

    private func imageScaleFactor(for url: String) -> CGFloat {
        let lower = url.lowercased()
        if lower.contains(".svg") || lower.contains("image/svg+xml") {
            return 1.0
        }
        if let windowScale = window?.backingScaleFactor {
            return windowScale
        }
        return NSScreen.main?.backingScaleFactor ?? 2.0
    }

    // MARK: - Selection Data Source

    public func selectionQuads(forItemAt index: Int, itemOffset: CGPoint) -> [VVQuadPrimitive] {
        guard let selection = selectionController.selection else { return [] }
        guard let controller else { return [] }
        guard index < controller.messages.count else { return [] }

        guard let layout = controller.itemLayout(at: index) else { return [] }
        guard let rendered = controller.renderedMessage(at: index) else { return [] }

        let (start, end) = selection.ordered
        guard start.itemIndex <= index && end.itemIndex >= index else { return [] }

        let helper = cachedSelectionHelper(messageID: layout.id, rendered: rendered)

        // Map chat positions to markdown positions for the item
        let mdStart: MarkdownTextPosition
        let mdEnd: MarkdownTextPosition
        if start.itemIndex == index && end.itemIndex == index {
            mdStart = start.markdownPosition
            mdEnd = end.markdownPosition
        } else if start.itemIndex == index {
            mdStart = start.markdownPosition
            mdEnd = helper.findLastPosition() ?? start.markdownPosition
        } else if end.itemIndex == index {
            mdStart = helper.findFirstPosition() ?? end.markdownPosition
            mdEnd = end.markdownPosition
        } else {
            // Entire item is selected
            guard let first = helper.findFirstPosition(), let last = helper.findLastPosition() else { return [] }
            mdStart = first
            mdEnd = last
        }

        let contentOffset = rendered.selectionContentOffset
        let localVisibleYRange = (viewportRect.minY - itemOffset.y - contentOffset.y)...(viewportRect.maxY - itemOffset.y - contentOffset.y)
        let rects = helper.selectionRects(from: mdStart, to: mdEnd, visibleYRange: localVisibleYRange)
        return rects.map { rect in
            VVQuadPrimitive(
                frame: rect.offsetBy(dx: itemOffset.x + contentOffset.x, dy: itemOffset.y + contentOffset.y),
                color: selectionColor,
                cornerRadius: 2
            )
        }
    }

    public func hoverQuads(forItemAt index: Int, itemOffset: CGPoint) -> [VVQuadPrimitive] {
        guard let controller,
              let hoveredInteractiveRegionKey,
              let layout = controller.itemLayout(at: index),
              let rendered = controller.renderedMessage(at: index) else {
            return []
        }

        return rendered.interactiveRegions.compactMap { region in
            guard let hoverFillColor = region.hoverFillColor else {
                return nil
            }
            let key = interactiveRegionKey(messageID: layout.id, regionID: region.id)
            guard key == hoveredInteractiveRegionKey else { return nil }
            return VVQuadPrimitive(
                frame: region.frame.offsetBy(dx: itemOffset.x, dy: itemOffset.y),
                color: hoverFillColor,
                cornerRadius: region.cornerRadius
            )
        }
    }

    // MARK: - Hit Testing Helpers

    private func viewPointToDocumentPoint(_ point: CGPoint) -> CGPoint {
        let scrollOffset = scrollView.contentView.bounds.origin
        return CGPoint(x: point.x + scrollOffset.x, y: point.y + scrollOffset.y)
    }


    // MARK: - Copy Support

    private func copySelection() {
        guard let selection = selectionController.selection else { return }
        let text = extractText(from: selection.ordered.start, to: selection.ordered.end)
        guard !text.isEmpty else { return }
        NSPasteboard.general.clearContents()
        NSPasteboard.general.setString(text, forType: .string)
    }

    private func extractText(from start: ChatTextPosition, to end: ChatTextPosition) -> String {
        guard let controller else { return "" }
        var result: [String] = []

        for itemIndex in start.itemIndex...min(end.itemIndex, controller.layouts.count - 1) {
            guard itemIndex < controller.messages.count else { continue }

            guard let layout = controller.itemLayout(at: itemIndex),
                  let rendered = controller.renderedMessage(at: itemIndex) else { continue }

            let helper = cachedSelectionHelper(messageID: layout.id, rendered: rendered)

            let mdStart: MarkdownTextPosition
            let mdEnd: MarkdownTextPosition
            if start.itemIndex == itemIndex && end.itemIndex == itemIndex {
                mdStart = start.markdownPosition
                mdEnd = end.markdownPosition
            } else if start.itemIndex == itemIndex {
                mdStart = start.markdownPosition
                mdEnd = helper.findLastPosition() ?? start.markdownPosition
            } else if end.itemIndex == itemIndex {
                mdStart = helper.findFirstPosition() ?? end.markdownPosition
                mdEnd = end.markdownPosition
            } else {
                guard let first = helper.findFirstPosition(), let last = helper.findLastPosition() else { continue }
                mdStart = first
                mdEnd = last
            }

            let itemText = helper.extractText(from: mdStart, to: mdEnd)
            if !itemText.isEmpty {
                result.append(itemText)
            }
        }

        return result.joined(separator: "\n\n")
    }

    public override var acceptsFirstResponder: Bool { true }

    public override func performKeyEquivalent(with event: NSEvent) -> Bool {
        if event.modifierFlags.contains(.command),
           let chars = event.charactersIgnoringModifiers?.lowercased() {
            switch chars {
            case "c":
                copySelection()
                return true
            case "a":
                selectAllText()
                return true
            default:
                break
            }
        }
        return super.performKeyEquivalent(with: event)
    }

    private func selectAllText() {
        guard let controller, !controller.layouts.isEmpty else { return }

        // Find first valid position
        var firstPos: ChatTextPosition?
        for i in 0..<controller.layouts.count {
            guard i < controller.messages.count else { continue }
            guard let layout = controller.itemLayout(at: i),
                  let rendered = controller.renderedMessage(at: i) else { continue }
            let helper = cachedSelectionHelper(messageID: layout.id, rendered: rendered)
            if let pos = helper.findFirstPosition() {
                firstPos = ChatTextPosition(itemIndex: i, blockIndex: pos.blockIndex, runIndex: pos.runIndex, characterOffset: pos.characterOffset)
                break
            }
        }

        // Find last valid position
        var lastPos: ChatTextPosition?
        for i in stride(from: controller.layouts.count - 1, through: 0, by: -1) {
            guard i < controller.messages.count else { continue }
            guard let layout = controller.itemLayout(at: i),
                  let rendered = controller.renderedMessage(at: i) else { continue }
            let helper = cachedSelectionHelper(messageID: layout.id, rendered: rendered)
            if let pos = helper.findLastPosition() {
                lastPos = ChatTextPosition(itemIndex: i, blockIndex: pos.blockIndex, runIndex: pos.runIndex, characterOffset: pos.characterOffset)
                break
            }
        }

        guard let first = firstPos, let last = lastPos else { return }
        selectionController.selectAll(from: first, to: last)
        metalView.setNeedsDisplay(metalView.bounds)
    }
}

// MARK: - VVChatTimelineSelectionDelegate

extension VVChatTimelineView: VVChatTimelineSelectionDelegate {
    public func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseDownAt point: CGPoint, clickCount: Int, modifiers: NSEvent.ModifierFlags) {
        pendingEntryActivationID = nil
        suppressEntryActivationForCurrentClick = false
        didDragDuringCurrentClick = false
        let hoverTargets = resolveHoverTargets(at: point)
        applyHoverTargets(hoverTargets)
        if handleFooterActionTap(hoverTargets) {
            suppressEntryActivationForCurrentClick = true
            return
        }
        if handleInteractiveRegionTap(hoverTargets) {
            suppressEntryActivationForCurrentClick = true
            return
        }
        if clickCount >= 1, let url = hoverTargets.linkURL {
            suppressEntryActivationForCurrentClick = true
            if let onLinkActivate {
                onLinkActivate(url)
            } else if let resolvedURL = URL(string: url) {
                NSWorkspace.shared.open(resolvedURL)
            }
            return
        }
        let hitText = hitTest(at: point) != nil
        if hitText {
            suppressEntryActivationForCurrentClick = true
        } else if clickCount == 1 {
            pendingEntryActivationID = timelineEntryID(at: point)
        }
        selectionController.handleMouseDown(at: point, clickCount: clickCount, modifiers: modifiers, hitTester: self)
        metalView.setNeedsDisplay(metalView.bounds)
    }

    public func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseDraggedTo point: CGPoint, event: NSEvent) {
        didDragDuringCurrentClick = true
        updatePointerHover(at: point)
        if selectionController.handleMouseDragged(to: point, hitTester: self) {
            metalView.setNeedsDisplay(metalView.bounds)
        }
    }

    public func chatTimelineMetalViewMouseUp(_ view: VVChatTimelineMetalView) {
        selectionController.handleMouseUp()
        if !didDragDuringCurrentClick,
           !suppressEntryActivationForCurrentClick,
           let entryID = pendingEntryActivationID {
            onEntryActivate?(entryID)
        }
        pendingEntryActivationID = nil
        suppressEntryActivationForCurrentClick = false
        didDragDuringCurrentClick = false
    }

    public func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseMovedTo point: CGPoint) {
        updatePointerHover(at: point)
    }

    public func chatTimelineMetalViewMouseExited(_ view: VVChatTimelineMetalView) {
        updatePointerHover(at: nil)
    }
}

private extension VVChatTimelineView {
    private func handleFooterActionTap(_ hoverTargets: TimelineHoverTargets) -> Bool {
        guard let messageID = hoverTargets.footerActionMessageID else { return false }
        onUserMessageCopyAction?(messageID)
        return true
    }

    private func interactionContext(at point: CGPoint) -> TimelineInteractionContext? {
        guard let controller else { return nil }
        let documentPoint = viewPointToDocumentPoint(point)
        guard let itemIndex = itemIndex(containingDocumentPoint: documentPoint),
              let layout = controller.itemLayout(at: itemIndex),
              controller.messages.indices.contains(itemIndex),
              let rendered = controller.renderedMessage(at: itemIndex) else {
            return nil
        }

        let contentOffset = rendered.selectionContentOffset
        let localPoint = CGPoint(
            x: documentPoint.x - layout.frame.origin.x - layout.contentOffset.x - contentOffset.x,
            y: documentPoint.y - layout.frame.origin.y - layout.contentOffset.y - contentOffset.y
        )

        return TimelineInteractionContext(
            documentPoint: documentPoint,
            itemIndex: itemIndex,
            layout: layout,
            message: controller.messages[itemIndex],
            rendered: rendered,
            localPoint: localPoint
        )
    }

    private func footerActionMessageID(in context: TimelineInteractionContext) -> String? {
        guard context.message.role == .user || context.message.role == .assistant else { return nil }
        guard let actionFrame = context.rendered.footerTrailingActionFrame else { return nil }
        let frameInDocument = actionFrame.offsetBy(
            dx: context.layout.frame.origin.x + context.layout.contentOffset.x,
            dy: context.layout.frame.origin.y + context.layout.contentOffset.y
        )
        return frameInDocument.contains(context.documentPoint) ? context.message.id : nil
    }

    private func linkURL(in context: TimelineInteractionContext) -> String? {
        let helper = cachedSelectionHelper(messageID: context.layout.id, rendered: context.rendered)
        return helper.linkURL(at: context.localPoint)
    }

    private func interactiveRegionHit(in context: TimelineInteractionContext) -> (messageID: String, region: VVChatInteractiveRegion)? {
        for region in context.rendered.interactiveRegions {
            let frameInDocument = region.frame.offsetBy(
                dx: context.layout.frame.origin.x + context.layout.contentOffset.x,
                dy: context.layout.frame.origin.y + context.layout.contentOffset.y
            )
            if frameInDocument.contains(context.documentPoint) {
                return (context.layout.id, region)
            }
        }
        return nil
    }

    private func resolveHoverTargets(at point: CGPoint?) -> TimelineHoverTargets {
        guard let point, let context = interactionContext(at: point) else {
            return .empty
        }
        return TimelineHoverTargets(
            footerActionMessageID: footerActionMessageID(in: context),
            linkURL: linkURL(in: context),
            interactiveRegionHit: interactiveRegionHit(in: context)
        )
    }

    private func applyHoverTargets(_ hoverTargets: TimelineHoverTargets) {
        if hoverTargets.footerActionMessageID != hoveredFooterActionMessageID {
            hoveredFooterActionMessageID = hoverTargets.footerActionMessageID
            onUserMessageCopyHoverChange?(hoverTargets.footerActionMessageID)
        }

        hoveredLinkURL = hoverTargets.linkURL

        let hoveredKey = hoverTargets.interactiveRegionHit.map {
            interactiveRegionKey(messageID: $0.messageID, regionID: $0.region.id)
        }
        if hoveredKey != hoveredInteractiveRegionKey {
            hoveredInteractiveRegionKey = hoveredKey
            metalView.setNeedsDisplay(metalView.bounds)
        }
    }

    private func updatePointerHover(at point: CGPoint?) {
        let hoverTargets = resolveHoverTargets(at: point)
        applyHoverTargets(hoverTargets)

        let shouldUsePointingCursor = hoverTargets.footerActionMessageID != nil ||
            hoverTargets.interactiveRegionHit != nil ||
            hoverTargets.linkURL != nil
        guard shouldUsePointingCursor != isPointingCursorActive else { return }
        isPointingCursorActive = shouldUsePointingCursor

        if shouldUsePointingCursor {
            NSCursor.pointingHand.set()
        } else {
            NSCursor.arrow.set()
        }
    }

    private func handleInteractiveRegionTap(_ hoverTargets: TimelineHoverTargets) -> Bool {
        guard let hit = hoverTargets.interactiveRegionHit else { return false }
        switch hit.region.action {
        case .link(let url):
            if let onLinkActivate {
                onLinkActivate(url)
            } else if let resolvedURL = URL(string: url) {
                NSWorkspace.shared.open(resolvedURL)
            }
            return true
        }
    }

    private func linkURL(at point: CGPoint) -> String? {
        guard let context = interactionContext(at: point) else { return nil }
        return linkURL(in: context)
    }

    private func footerActionMessageID(at point: CGPoint) -> String? {
        guard let context = interactionContext(at: point) else { return nil }
        return footerActionMessageID(in: context)
    }

    private func interactiveRegionHit(at point: CGPoint) -> (messageID: String, region: VVChatInteractiveRegion)? {
        guard let context = interactionContext(at: point) else { return nil }
        return interactiveRegionHit(in: context)
    }

    private func interactiveRegionKey(messageID: String, regionID: String) -> String {
        "\(messageID)::\(regionID)"
    }

    private func timelineEntryID(at point: CGPoint) -> String? {
        guard let controller else { return nil }
        let docPoint = viewPointToDocumentPoint(point)
        guard let index = itemIndex(containingDocumentPoint: docPoint) else { return nil }
        return controller.layouts[index].id
    }
}

// MARK: - VVTextHitTestable

extension VVChatTimelineView: VVTextHitTestable {
    public func hitTest(at point: CGPoint) -> ChatTextPosition? {
        textPosition(at: point, preferNearest: false)
    }

    public func nearestTextPosition(to point: CGPoint) -> ChatTextPosition? {
        textPosition(at: point, preferNearest: true)
    }

    private func textPosition(at point: CGPoint, preferNearest: Bool) -> ChatTextPosition? {
        guard let controller else { return nil }
        let docPoint = viewPointToDocumentPoint(point)
        let targetItemIndex: Int?
        if preferNearest {
            targetItemIndex = nearestItemIndex(forDocumentY: docPoint.y)
        } else {
            targetItemIndex = itemIndex(containingDocumentPoint: docPoint)
        }
        guard let targetItemIndex,
              let layout = controller.itemLayout(at: targetItemIndex),
              let rendered = controller.renderedMessage(at: targetItemIndex) else { return nil }

        // Convert to item-local coordinates
        let contentOffset = rendered.selectionContentOffset
        let localPoint = CGPoint(
            x: docPoint.x - layout.frame.origin.x - layout.contentOffset.x - contentOffset.x,
            y: docPoint.y - layout.frame.origin.y - layout.contentOffset.y - contentOffset.y
        )

        let helper = cachedSelectionHelper(messageID: layout.id, rendered: rendered)
        let markdownPosition = preferNearest
            ? helper.nearestTextPosition(to: localPoint)
            : helper.hitTest(at: localPoint)
        guard let mdPos = markdownPosition else { return nil }

        return ChatTextPosition(
            itemIndex: targetItemIndex,
            blockIndex: mdPos.blockIndex,
            runIndex: mdPos.runIndex,
            characterOffset: mdPos.characterOffset
        )
    }
}

private final class VVChatTimelineScrollView: NSScrollView {
    var onInteractionChange: ((Bool) -> Void)?
    private var endInteractionWorkItem: DispatchWorkItem?
    private let interactionEndDelay: TimeInterval = 0.2

    private func beginInteraction() {
        endInteractionWorkItem?.cancel()
        endInteractionWorkItem = nil
        onInteractionChange?(true)
    }

    private func scheduleEndInteraction() {
        endInteractionWorkItem?.cancel()
        let workItem = DispatchWorkItem { [weak self] in
            self?.onInteractionChange?(false)
            self?.endInteractionWorkItem = nil
        }
        endInteractionWorkItem = workItem
        DispatchQueue.main.asyncAfter(deadline: .now() + interactionEndDelay, execute: workItem)
    }

    override func scrollWheel(with event: NSEvent) {
        let phase = event.phase
        let momentum = event.momentumPhase
        let isDiscreteWheel = phase.isEmpty && momentum.isEmpty
        if isDiscreteWheel {
            beginInteraction()
        } else if phase == .began || phase == .changed || momentum == .began || momentum == .changed {
            beginInteraction()
        }

        super.scrollWheel(with: event)

        if isDiscreteWheel || phase == .ended || momentum == .ended || phase == .cancelled {
            scheduleEndInteraction()
        }
    }
}

private final class VVChatTimelineImageStore {
    private let loader: MarkdownImageLoader
    private var textures: [String: MTLTexture] = [:]
    private var sizes: [String: CGSize] = [:]
    private var pending: Set<String> = []
    private var cacheOrder: [String] = []
    private let scaleFactorProvider: (String) -> CGFloat
    private let maxTextureEntries: Int

    var onImageSizeUpdate: ((String, CGSize) -> Void)?
    var onImageLoaded: ((String) -> Void)?

    init(
        device: MTLDevice,
        maxTextureEntries: Int = 96,
        scaleFactorProvider: @escaping (String) -> CGFloat
    ) {
        self.loader = MarkdownImageLoader(device: device)
        self.maxTextureEntries = max(8, maxTextureEntries)
        self.scaleFactorProvider = scaleFactorProvider
    }

    func texture(for url: String) -> MTLTexture? {
        guard let texture = textures[url] else { return nil }
        touch(url)
        return texture
    }

    func clearCache() {
        textures.removeAll()
        sizes.removeAll()
        pending.removeAll()
        cacheOrder.removeAll()
        loader.clearCache()
    }

    func ensureImage(url: String) {
        if textures[url] != nil || pending.contains(url) { return }
        pending.insert(url)
        loader.loadImage(from: url) { [weak self] loaded in
            guard let self else { return }
            DispatchQueue.main.async {
                self.pending.remove(url)
                guard let loaded else { return }
                self.textures[url] = loaded.texture
                self.touch(url)
                let scale = max(0.1, self.scaleFactorProvider(url))
                let size = CGSize(width: loaded.size.width / scale, height: loaded.size.height / scale)
                if self.sizes[url] != size {
                    self.sizes[url] = size
                    self.onImageSizeUpdate?(url, size)
                }
                self.evictIfNeeded()
                self.onImageLoaded?(url)
            }
        }
    }

    private func touch(_ url: String) {
        cacheOrder.removeAll(where: { $0 == url })
        cacheOrder.append(url)
    }

    private func evictIfNeeded() {
        while cacheOrder.count > maxTextureEntries {
            let evictedURL = cacheOrder.removeFirst()
            textures.removeValue(forKey: evictedURL)
            sizes.removeValue(forKey: evictedURL)
        }
    }
}
#endif
