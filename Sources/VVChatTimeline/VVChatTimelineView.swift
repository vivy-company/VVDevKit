#if os(macOS)
import AppKit
import CoreText
import Foundation
import Metal
import QuartzCore
import VVMarkdown
import VVMetalPrimitives

/// Plain NSView used as the scroll view's documentView purely for content sizing.
private final class ChatTimelineDocumentView: NSView {
    override var isFlipped: Bool { true }
}

public final class VVChatTimelineView: NSView, VVChatTimelineRenderDataSource {
    private let scrollView: VVChatTimelineScrollView
    private let documentView: ChatTimelineDocumentView
    private let metalView: VVChatTimelineMetalView
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
    private struct TimelineInteractionContext {
        let documentPoint: CGPoint
        let layout: VVChatTimelineController.ItemLayout
        let message: VVChatMessage
        let rendered: VVChatRenderedMessage
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
    private let layoutAnimationItemPadding = 12
    private let layoutAnimationOverscan: CGFloat = 1400
    private var pendingEntryActivationID: String?
    private var suppressEntryActivationForCurrentClick = false
    private var didDragDuringCurrentClick = false
    private var displayLink: CVDisplayLink?
    private var workScheduler: VVChatTimelineViewScheduler!
    private var pendingDisplayLinkedRender = false
    private var suppressBoundsChangedDuringAnimatedScroll = false
    private var isApplyingUpdate = false
    private var pendingInteractiveScrollFrame = false
    private let activeVisibleOverscan: CGFloat = 420
    private let idleVisibleOverscan: CGFloat = 900
    private let transitionCoordinator = VVChatTimelineTransitionCoordinator()
    private var currentRenderSnapshot = VVChatTimelineVisibleRenderSnapshot.empty

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
        super.init(frame: frameRect)
        setup()
    }

    required init?(coder: NSCoder) {
        self.metalContext = VVMetalContext.shared
        scrollView = VVChatTimelineScrollView(frame: .zero)
        documentView = ChatTimelineDocumentView(frame: .zero)
        metalView = VVChatTimelineMetalView(frame: .zero, font: .systemFont(ofSize: 14), metalContext: VVMetalContext.shared)
        super.init(coder: coder)
        setup()
    }

    deinit {
        stopDisplayLink()
        if let controllerObservation {
            NotificationCenter.default.removeObserver(controllerObservation)
        }
    }

    private func setup() {
        workScheduler = VVChatTimelineViewScheduler(
            relayoutBatchInterval: { [weak self] in
                self?.controller?.currentStyle.motion.updateBatchInterval ?? 0
            },
            applyUpdate: { [weak self] update in
                self?.apply(update: update)
            },
            performVisibleHydration: { [weak self] in
                await self?.performVisibleHydrationIfNeeded() ?? .completed
            },
            performCacheTrim: { [weak self] in
                self?.trimOffscreenCachesIfNeeded()
            }
        )
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
            if !isInteracting {
                self?.workScheduler.scheduleVisibleHydration(after: 0.04)
                self?.trimOffscreenCachesIfNeeded()
            }
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
        updateVisibleRenderRange(hydrateExactLayouts: shouldHydrateVisibleExactLayouts)
        if !shouldHydrateVisibleExactLayouts {
            workScheduler.scheduleVisibleHydration()
        }
    }

    public override func viewDidMoveToWindow() {
        super.viewDidMoveToWindow()
        if window != nil {
            ensureDisplayLink()
            updateVisibleRenderRange(hydrateExactLayouts: shouldHydrateVisibleExactLayouts)
            workScheduler.scheduleVisibleHydration(after: 0.04)
        } else {
            stopDisplayLink()
        }
    }

    private func bindController(oldValue: VVChatTimelineController?) {
        oldValue?.onUpdate = nil
        workScheduler.reset()
        didInitialScroll = false
        stopLayoutAnimation()
        stableLayoutSnapshots.removeAll(keepingCapacity: false)
        animatedLayoutSnapshots.removeAll(keepingCapacity: false)
        visibleRenderRange = 0..<0
        currentRenderSnapshot = .empty
        isPointingCursorActive = false
        controller?.onUpdate = { [weak self] update in
            self?.workScheduler.enqueueControllerUpdate(update)
        }
        if let style = controller?.currentStyle {
            metalView.updateFont(style.baseFont)
            currentFont = style.baseFont
        }
        updateContentWidth()
        apply(update: .init(totalHeight: controller?.totalHeight ?? 0))
    }

    private func updateContentWidth() {
        guard let controller else { return }
        let width = scrollView.contentView.bounds.width
        controller.updateRenderWidth(width)
        requestRender()
    }

    private func apply(update: VVChatTimelineController.Update) {
        guard let controller else { return }
        isApplyingUpdate = true
        defer { isApplyingUpdate = false }
        workScheduler.cancelVisibleHydration()
        let wasPinnedToBottom = isViewportPinnedToBottom(
            totalHeight: max(0, controller.totalHeight - update.heightDelta)
        )
        controller.invalidateInteractionCaches(
            for: update.updatedIndexes.compactMap { controller.itemLayout(at: $0)?.id }
        )
        let style = controller.currentStyle
        if !isSameFont(style.baseFont, currentFont) {
            metalView.updateFont(style.baseFont)
            currentFont = style.baseFont
        }
        updateDocumentHeight(controller.totalHeight)
        clampScrollIfNeeded()
        updateVisibleRangeOnly()
        let transitionPlan = transitionCoordinator.makeUpdatePlan(
            update: update,
            controller: controller,
            visibleRect: scrollView.contentView.bounds,
            wasPinnedToBottom: wasPinnedToBottom,
            visibleRenderRange: visibleRenderRange,
            stableSnapshots: stableLayoutSnapshots,
            layoutAnimationOverscan: layoutAnimationOverscan,
            layoutAnimationItemPadding: layoutAnimationItemPadding
        )
        let latestSnapshots = currentLayoutSnapshots(in: transitionPlan.snapshotIndexes)

        if let targetY = transitionPlan.compensatedScrollTargetY {
            let newOrigin = CGPoint(x: scrollView.contentView.bounds.origin.x, y: targetY)
            scrollView.contentView.scroll(to: newOrigin)
            scrollView.reflectScrolledClipView(scrollView.contentView)
            updateMetalViewport()
        }

        if transitionPlan.shouldSuppressPinnedTailViewportMotion {
            stopScrollAnimation()
            isAnimatingJump = false
            scrollToBottom(animated: false)
            controller.updateViewportMode(distanceFromBottom: 0)
            updateMetalViewport()
        }

        if !didInitialScroll, update.totalHeight > 0 {
            scrollToBottom(animated: false)
            didInitialScroll = true
            updateMetalViewport()
        } else if update.followPolicy == .forceImmediateBottom, !isAnimatingJump {
            scrollToBottom(animated: false)
            controller.updateViewportMode(distanceFromBottom: 0)
            updateMetalViewport()
        }

        refreshVisibleRenderSnapshot(for: update, hydrateExactLayouts: false)
        if let transition = transitionPlan.transition {
            if let layoutPlan = transitionCoordinator.makeLayoutAnimationPlan(
                previousSnapshots: stableLayoutSnapshots,
                nextSnapshots: latestSnapshots,
                liveSnapshots: layoutAnimator.isRunning ? layoutAnimator.state().snapshots : [:],
                transition: transition,
                viewportWidth: scrollView.contentView.bounds.width,
                viewportIsFollowing: transitionPlan.shouldSuppressPinnedTailViewportMotion,
                motion: style.motion
            ) {
                startLayoutAnimation(layoutPlan)
            } else {
                stableLayoutSnapshots = latestSnapshots
            }

        } else {
            stopLayoutAnimation(commitTargetSnapshots: false)
            stableLayoutSnapshots = latestSnapshots
        }

        trimStaleLayoutSnapshots(for: update)
        requestImagesForVisibleItems()
        workScheduler.scheduleVisibleHydration()
        scheduleCacheTrimIfNeeded()
        requestRender()
        onStateChange?(controller.state)
    }

    private func trimStaleLayoutSnapshots(for update: VVChatTimelineController.Update) {
        guard !stableLayoutSnapshots.isEmpty else { return }
        // Only need to trim when items were removed or the timeline was rebuilt.
        guard !update.removedIndexes.isEmpty || update.cause == .rebuild else { return }
        guard let controller else {
            stableLayoutSnapshots.removeAll()
            return
        }
        // Build set of current layout IDs from the snapshot range around the viewport.
        let viewport = scrollView.contentView.bounds
        let range = controller.visibleLayoutRange(in: viewport, overscan: layoutAnimationOverscan)
        let lowerBound = max(0, range.lowerBound - layoutAnimationItemPadding)
        let upperBound = min(controller.layoutCount, range.upperBound + layoutAnimationItemPadding)
        var validIDs = Set<String>()
        validIDs.reserveCapacity(upperBound - lowerBound)
        for index in lowerBound..<upperBound {
            if let id = controller.itemLayout(at: index)?.id {
                validIDs.insert(id)
            }
        }
        stableLayoutSnapshots = stableLayoutSnapshots.filter { validIDs.contains($0.key) }
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

    private func handleScroll() {
        if isApplyingUpdate { return }
        if suppressBoundsChangedDuringAnimatedScroll {
            suppressBoundsChangedDuringAnimatedScroll = false
            return
        }
        guard let controller else { return }
        updateMetalViewport()
        if controller.state.userIsInteracting,
           scrollAnimationDuration <= 0,
           !layoutAnimator.isRunning {
            pendingInteractiveScrollFrame = true
            startDisplayLink()
            return
        }
        updateVisibleRenderRange(hydrateExactLayouts: false)
        requestImagesForVisibleItems()
        workScheduler.scheduleVisibleHydration()
        scheduleCacheTrimIfNeeded()
        requestRender(immediate: controller.state.userIsInteracting)

        // During a jump animation, skip state updates that could interfere
        // with the in-flight scroll. Only update the viewport for rendering.
        guard !isAnimatingJump else { return }

        let visibleRect = scrollView.contentView.bounds
        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        let distanceFromBottom = maxOffset - visibleRect.origin.y
        controller.updateViewportMode(distanceFromBottom: distanceFromBottom)
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

    public func jumpToLatestAnimated() {
        isAnimatingJump = true
        controller?.jumpToLatest()
        animateJumpToLatest()
        if let controller {
            onStateChange?(controller.state)
        }
    }

    private func isViewportPinnedToBottom(totalHeight: CGFloat) -> Bool {
        guard let controller else { return false }
        let visibleRect = scrollView.contentView.bounds
        let contentHeight = max(totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        let distanceFromBottom = max(0, maxOffset - visibleRect.origin.y)
        return distanceFromBottom <= controller.state.pinThreshold
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

    private func currentLayoutSnapshots(in indexes: IndexSet) -> [String: VVLayoutAnimationSnapshot] {
        guard let controller, !indexes.isEmpty else { return [:] }
        var snapshots: [String: VVLayoutAnimationSnapshot] = [:]
        snapshots.reserveCapacity(indexes.count)
        for index in indexes {
            guard let layout = controller.itemLayout(at: index) else { continue }
            snapshots[layout.id] = VVLayoutAnimationSnapshot(
                id: layout.id,
                frame: layout.frame,
                contentOffset: layout.contentOffset
            )
        }
        return snapshots
    }

    private func startLayoutAnimation(_ plan: VVChatTimelineLayoutAnimationPlan) {
        guard !plan.targetSnapshots.isEmpty else {
            stableLayoutSnapshots = plan.targetSnapshots
            return
        }
        layoutAnimator.start(
            from: plan.startSnapshots,
            to: plan.targetSnapshots,
            fallbackTransition: plan.fallbackTransition,
            fallbackAnimation: plan.fallbackAnimation
        )
        animatedLayoutSnapshots = layoutAnimator.state().snapshots
        startDisplayLink()
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

        if state.isComplete {
            stableLayoutSnapshots = state.snapshots
            stopLayoutAnimation()
        }
    }

    private func scrollAnimationTick(at now: CFTimeInterval) {
        guard scrollAnimationDuration > 0 else { return }
        let elapsed = now - scrollAnimationStartTime
        let progress = min(1.0, elapsed / scrollAnimationDuration)
        let t = scrollAnimationCurve.value(at: CGFloat(progress))

        let currentY = scrollAnimationStartY + (scrollAnimationTargetY - scrollAnimationStartY) * t
        let origin = CGPoint(x: scrollView.contentView.bounds.origin.x, y: currentY)
        suppressBoundsChangedDuringAnimatedScroll = true
        scrollView.contentView.setBoundsOrigin(origin)
        scrollView.reflectScrolledClipView(scrollView.contentView)
        updateMetalViewport()
        updateVisibleRenderRange(hydrateExactLayouts: false)

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

        let callback: CVDisplayLinkOutputCallback = { _, inNow, _, _, _, userInfo in
            let view = Unmanaged<VVChatTimelineView>.fromOpaque(userInfo!).takeUnretainedValue()
            // Schedule on the main runloop with .common mode so the tick lands as
            // early as possible, even during scroll tracking / live resize.
            CFRunLoopPerformBlock(CFRunLoopGetMain(), CFRunLoopMode.commonModes.rawValue) {
                view.animationFrameTick()
            }
            CFRunLoopWakeUp(CFRunLoopGetMain())
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
        guard let displayLink else { return }
        if CVDisplayLinkIsRunning(displayLink) {
            CVDisplayLinkStop(displayLink)
        }
        self.displayLink = nil
    }

    private func animationFrameTick() {
        let now = CACurrentMediaTime()
        var needsRender = pendingDisplayLinkedRender
        if scrollAnimationDuration > 0 {
            scrollAnimationTick(at: now)
            needsRender = true
        }
        if layoutAnimator.isRunning {
            layoutAnimationTick(at: now)
            needsRender = true
        }
        if pendingInteractiveScrollFrame {
            flushInteractiveScrollFrame()
            needsRender = true
        }
        if needsRender {
            pendingDisplayLinkedRender = false
            // Use setNeedsDisplay so the draw coalesces with the next
            // compositing pass, keeping Metal presentation vsync-aligned.
            metalView.setNeedsDisplay(metalView.bounds)
        }
        if scrollAnimationDuration <= 0 &&
            !layoutAnimator.isRunning &&
            !pendingInteractiveScrollFrame &&
            !pendingDisplayLinkedRender {
            stopDisplayLink()
            workScheduler.scheduleVisibleHydration(after: 0.03)
        }
    }

    private func flushInteractiveScrollFrame() {
        pendingInteractiveScrollFrame = false
        guard let controller else { return }
        updateVisibleRenderRange(hydrateExactLayouts: false)
        requestImagesForVisibleItems()

        // During a jump animation, skip state updates that could interfere
        // with the in-flight scroll. Only update the viewport for rendering.
        guard !isAnimatingJump else { return }

        let visibleRect = scrollView.contentView.bounds
        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        let distanceFromBottom = maxOffset - visibleRect.origin.y
        controller.updateViewportMode(distanceFromBottom: distanceFromBottom)
        onStateChange?(controller.state)
    }

    private var shouldHydrateVisibleExactLayouts: Bool {
        guard let controller else { return false }
        return !controller.hasActiveDraft &&
            !controller.state.userIsInteracting &&
            scrollAnimationDuration <= 0 &&
            !layoutAnimator.isRunning
    }

    private func currentVisibleOverscan() -> CGFloat {
        shouldHydrateVisibleExactLayouts ? idleVisibleOverscan : activeVisibleOverscan
    }

    private func updateVisibleRenderRange(hydrateExactLayouts: Bool) {
        guard let controller else {
            visibleRenderRange = 0..<0
            currentRenderSnapshot = .empty
            return
        }
        let viewport = scrollView.contentView.bounds
        let overscan = currentVisibleOverscan()
        let snapshot = controller.visibleRenderSnapshot(
            in: viewport,
            overscan: overscan,
            shouldHydrateExactLayouts: hydrateExactLayouts
        )
        visibleRenderRange = snapshot.range
        currentRenderSnapshot = snapshot
    }

    private func updateVisibleRangeOnly() {
        guard let controller else {
            visibleRenderRange = 0..<0
            return
        }
        let viewport = scrollView.contentView.bounds
        visibleRenderRange = controller.visibleLayoutRange(
            in: viewport,
            overscan: currentVisibleOverscan()
        )
    }

    private func refreshVisibleRenderSnapshot(
        for update: VVChatTimelineController.Update?,
        hydrateExactLayouts: Bool
    ) {
        guard let controller else {
            visibleRenderRange = 0..<0
            currentRenderSnapshot = .empty
            return
        }

        let viewport = scrollView.contentView.bounds
        let overscan = currentVisibleOverscan()
        let range = controller.visibleLayoutRange(in: viewport, overscan: overscan)
        visibleRenderRange = range

        guard !hydrateExactLayouts,
              let update else {
            currentRenderSnapshot = controller.visibleRenderSnapshot(
                in: viewport,
                overscan: overscan,
                shouldHydrateExactLayouts: hydrateExactLayouts
            )
            return
        }

        if canIncrementallyRefreshVisibleRenderSnapshot(for: update, range: range) {
            let visibleIndexes = update.updatedIndexes.filter(range.contains)
            guard !visibleIndexes.isEmpty else {
                return
            }

            let visibleUpdates = visibleIndexes.compactMap { controller.visibleRenderItem(at: $0, viewport: viewport) }
            guard visibleUpdates.count == visibleIndexes.count else {
                currentRenderSnapshot = controller.visibleRenderSnapshot(
                    in: viewport,
                    overscan: overscan,
                    shouldHydrateExactLayouts: false
                )
                return
            }

            currentRenderSnapshot = currentRenderSnapshot.applying(visibleUpdates)
            return
        }

        if let tailRefreshLowerBound = incrementalTailRefreshLowerBound(for: update, range: range) {
            var itemsByIndex = currentRenderSnapshot.itemsByIndex.filter { index, _ in
                range.contains(index) && index < tailRefreshLowerBound
            }
            var imageURLsByIndex = currentRenderSnapshot.imageURLsByIndex.filter { index, _ in
                range.contains(index) && index < tailRefreshLowerBound
            }
            for index in tailRefreshLowerBound..<range.upperBound {
                guard let visibleUpdate = controller.visibleRenderItem(at: index, viewport: viewport) else {
                    currentRenderSnapshot = controller.visibleRenderSnapshot(
                        in: viewport,
                        overscan: overscan,
                        shouldHydrateExactLayouts: false
                    )
                    return
                }
                itemsByIndex[index] = visibleUpdate.item
                if visibleUpdate.imageURLs.isEmpty {
                    imageURLsByIndex.removeValue(forKey: index)
                } else {
                    imageURLsByIndex[index] = visibleUpdate.imageURLs
                }
            }

            currentRenderSnapshot = VVChatTimelineVisibleRenderSnapshot(
                range: range,
                itemsByIndex: itemsByIndex,
                imageURLsByIndex: imageURLsByIndex
            )
            return
        }

        currentRenderSnapshot = controller.visibleRenderSnapshot(
            in: viewport,
            overscan: overscan,
            shouldHydrateExactLayouts: hydrateExactLayouts
        )
    }

    private func incrementalTailRefreshLowerBound(
        for update: VVChatTimelineController.Update,
        range: Range<Int>
    ) -> Int? {
        guard !range.isEmpty,
              range.lowerBound == currentRenderSnapshot.range.lowerBound,
              range.upperBound >= currentRenderSnapshot.range.lowerBound else {
            return nil
        }

        let affectedIndexes = update.insertedIndexes.union(update.updatedIndexes).union(update.removedIndexes)
        guard let affectedLowerBound = affectedIndexes.first else { return nil }

        // Affected indexes beyond the visible range can't be incrementally refreshed.
        guard affectedLowerBound < range.upperBound else { return nil }

        let tailThreshold = max(currentRenderSnapshot.range.lowerBound, currentRenderSnapshot.range.upperBound - 12)
        guard affectedLowerBound >= tailThreshold else { return nil }

        let removedTailOnly = update.removedIndexes.allSatisfy { $0 >= affectedLowerBound }
        let updatedTailOnly = update.updatedIndexes.allSatisfy { $0 >= affectedLowerBound }
        let insertedTailOnly = update.insertedIndexes.allSatisfy { $0 >= affectedLowerBound }
        guard removedTailOnly, updatedTailOnly, insertedTailOnly else { return nil }

        return affectedLowerBound
    }

    private func canIncrementallyRefreshVisibleRenderSnapshot(
        for update: VVChatTimelineController.Update,
        range: Range<Int>
    ) -> Bool {
        guard update.cause == .streamUpdate,
              update.insertedIndexes.isEmpty,
              update.removedIndexes.isEmpty,
              !update.updatedIndexes.isEmpty,
              range == currentRenderSnapshot.range else {
            return false
        }
        return true
    }

    private func trimOffscreenCachesIfNeeded() {
        guard let controller,
              !controller.hasActiveDraft,
              !controller.state.userIsInteracting else { return }
        controller.trimCaches(in: scrollView.contentView.bounds, overscan: 1200, itemPadding: 16)
    }

    private func scheduleCacheTrimIfNeeded(delay: TimeInterval = 0.22) {
        workScheduler.cancelCacheTrim()
        guard let controller,
              !controller.hasActiveDraft,
              !controller.state.userIsInteracting else {
            return
        }
        // If animations are still running, defer longer but still schedule.
        let effectiveDelay = (scrollAnimationDuration > 0 || layoutAnimator.isRunning) ? 0.5 : delay
        workScheduler.scheduleCacheTrim(after: effectiveDelay)
    }

    private func performVisibleHydrationIfNeeded() async -> VVChatTimelineViewScheduler.VisibleHydrationResult {
        guard let controller else { return .completed }
        guard shouldHydrateVisibleExactLayouts else {
            return .reschedule(0.08)
        }
        let viewport = scrollView.contentView.bounds
        let overscan = idleVisibleOverscan
        await controller.prepareExactLayouts(in: viewport, overscan: overscan)
        if controller.hydrateExactLayoutsSilently(in: viewport, overscan: overscan) {
            await controller.prepareVisibleSceneArtifacts(in: viewport, overscan: overscan)
            updateDocumentHeight(controller.totalHeight)
            clampScrollIfNeeded()
            updateVisibleRenderRange(hydrateExactLayouts: false)
            requestImagesForVisibleItems()
            requestRender()
        } else {
            await controller.prepareVisibleSceneArtifacts(in: viewport, overscan: overscan)
        }
        return .completed
    }

    func debugLayoutSnapshotCount() -> Int {
        max(stableLayoutSnapshots.count, animatedLayoutSnapshots.count)
    }

    func debugVisibleRenderCount() -> Int {
        visibleRenderRange.count
    }

    func debugIsLayoutAnimating() -> Bool {
        layoutAnimator.isRunning
    }

    func debugIsScrollAnimating() -> Bool {
        scrollAnimationDuration > 0
    }

    private func itemIndex(containingDocumentPoint point: CGPoint) -> Int? {
        controller?.itemIndex(containingDocumentY: point.y)
    }

    // MARK: - VVChatTimelineRenderDataSource

    public var renderItemCount: Int {
        currentRenderSnapshot.range.upperBound
    }

    public func visibleRenderIndexes() -> Range<Int> {
        currentRenderSnapshot.range
    }

    public func renderItem(at index: Int, visibleRect: CGRect) -> VVChatTimelineRenderItem? {
        _ = visibleRect
        guard let item = currentRenderSnapshot.item(at: index) else { return nil }
        let resolvedFrame: CGRect
        let resolvedContentOffset: CGPoint
        if layoutAnimator.isRunning, let snapshot = animatedLayoutSnapshots[item.id] {
            resolvedFrame = snapshot.frame
            resolvedContentOffset = snapshot.contentOffset
        } else {
            resolvedFrame = item.frame
            resolvedContentOffset = item.contentOffset
        }

        return VVChatTimelineRenderItem(
            id: item.id,
            frame: resolvedFrame,
            contentOffset: resolvedContentOffset,
            layers: item.layers.map { layer in
                VVChatTimelineRenderLayer(
                    offset: layer.offset,
                    scene: layer.scene,
                    orderedPrimitiveIndices: layer.orderedPrimitiveIndices,
                    visibilityIndex: layer.visibilityIndex
                )
            }
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

    private func requestRender(immediate: Bool = false) {
        let bounds = metalView.bounds
        guard bounds.width > 0, bounds.height > 0 else { return }
        if !immediate,
           controller?.hasActiveDraft == true || workScheduler.hasPendingStreamUpdate {
            pendingDisplayLinkedRender = true
            startDisplayLink()
            return
        }
        metalView.setNeedsDisplay(bounds)
    }

    private func isSameFont(_ lhs: VVFont?, _ rhs: VVFont?) -> Bool {
        guard let lhs, let rhs else { return false }
        return lhs.fontName == rhs.fontName && lhs.pointSize == rhs.pointSize
    }

    private func requestImagesForVisibleItems() {
        guard let imageStore else { return }
        for url in currentRenderSnapshot.imageURLs {
            imageStore.ensureImage(url: url)
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
        return controller?.selectionQuads(
            for: selection,
            itemAt: index,
            itemOffset: itemOffset,
            viewportRect: viewportRect,
            color: selectionColor
        ) ?? []
    }

    public func hoverQuads(forItemAt index: Int, itemOffset: CGPoint) -> [VVQuadPrimitive] {
        guard let hoveredInteractiveRegionKey,
              let resolvedItem = controller?.resolvedRenderItem(at: index) else {
            return []
        }

        return resolvedItem.rendered.interactiveRegions.compactMap { region in
            guard let hoverFillColor = region.hoverFillColor else {
                return nil
            }
            let key = interactiveRegionKey(messageID: resolvedItem.layout.id, regionID: region.id)
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
        guard let controller else { return }
        let text = controller.extractText(from: selection.ordered.start, to: selection.ordered.end)
        guard !text.isEmpty else { return }
        NSPasteboard.general.clearContents()
        NSPasteboard.general.setString(text, forType: .string)
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
        guard let controller, controller.layoutCount > 0 else { return }
        guard let selection = controller.selectAllTextRange() else { return }
        selectionController.selectAll(from: selection.anchor, to: selection.active)
        metalView.setNeedsDisplay(metalView.bounds)
    }
}

// MARK: - VVChatTimelineSelectionDelegate

extension VVChatTimelineView: VVChatTimelineSelectionDelegate {
    public func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseDownAt point: CGPoint, clickCount: Int, modifiers: VVInputModifiers) {
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
        guard let itemIndex = itemIndex(containingDocumentPoint: documentPoint) else {
            return nil
        }
        guard let resolvedItem = controller.resolvedRenderItem(
            at: itemIndex,
            hydrateExactLayoutIfNeeded: true
        ) else {
            return nil
        }

        return TimelineInteractionContext(
            documentPoint: documentPoint,
            layout: resolvedItem.layout,
            message: resolvedItem.item.message,
            rendered: resolvedItem.rendered
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
        controller?.linkURL(atDocumentPoint: context.documentPoint, viewportRect: viewportRect)
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
        return controller.itemLayout(at: index)?.id
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
        return controller.textPosition(
            atDocumentPoint: docPoint,
            viewportRect: viewportRect,
            preferNearest: preferNearest
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
