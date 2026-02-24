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
    private var hoveredFooterActionMessageID: String?
    private var jumpAnimationToken = UUID()

    public var controller: VVChatTimelineController? {
        didSet {
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
        if let controllerObservation {
            NotificationCenter.default.removeObserver(controllerObservation)
        }
    }

    private func setup() {
        wantsLayer = true
        layer?.backgroundColor = NSColor.clear.cgColor

        scrollView.drawsBackground = false
        scrollView.hasVerticalScroller = true
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
        didInitialScroll = false
        controller?.onUpdate = { [weak self] update in
            self?.apply(update: update)
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
        metalView.setNeedsDisplay(metalView.bounds)
    }

    private func apply(update: VVChatTimelineController.Update) {
        guard let controller else { return }
        let style = controller.currentStyle
        if !isSameFont(style.baseFont, currentFont) {
            metalView.updateFont(style.baseFont)
            currentFont = style.baseFont
        }
        updateDocumentHeight(controller.totalHeight)
        clampScrollIfNeeded()
        jumpButton.isHidden = !update.hasUnreadNewContent

        if update.heightDelta != 0,
           let changedIndex = update.changedIndex,
           !update.shouldScrollToBottom,
           let layout = controller.itemLayout(at: changedIndex) {
            compensateScrollIfNeeded(layout: layout, delta: update.heightDelta)
        }

        if update.shouldScrollToBottom {
            scrollToBottom(animated: false)
            controller.updatePinnedState(distanceFromBottom: 0)
            didInitialScroll = true
        } else if !didInitialScroll, update.totalHeight > 0 {
            scrollToBottom(animated: false)
            didInitialScroll = true
        }

        requestImagesForVisibleItems()
        metalView.setNeedsDisplay(metalView.bounds)
        onStateChange?(controller.state)
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
        let visibleRect = scrollView.contentView.bounds
        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        let distanceFromBottom = maxOffset - visibleRect.origin.y
        controller.updatePinnedState(distanceFromBottom: distanceFromBottom)
        jumpButton.isHidden = !controller.state.hasUnreadNewContent
        requestImagesForVisibleItems()
        metalView.setNeedsDisplay(metalView.bounds)
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
            NSAnimationContext.runAnimationGroup { context in
                context.duration = 0.15
                scrollView.contentView.animator().setBoundsOrigin(newOrigin)
            }
        } else {
            scrollView.contentView.setBoundsOrigin(newOrigin)
        }
        scrollView.reflectScrolledClipView(scrollView.contentView)
    }

    public func restoreScrollPosition(_ origin: CGPoint) {
        scrollView.contentView.setBoundsOrigin(origin)
        scrollView.reflectScrolledClipView(scrollView.contentView)
        didInitialScroll = true
    }

    @objc private func handleJumpToLatest() {
        controller?.jumpToLatest()
        animateJumpToLatest()
        if let controller {
            onStateChange?(controller.state)
        }
    }

    private func animateJumpToLatest() {
        guard let controller else { return }
        let visibleRect = scrollView.contentView.bounds
        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        let startY = visibleRect.origin.y
        let distance = maxOffset - startY

        guard distance > 1 else {
            scrollToBottom(animated: false)
            return
        }

        // Short hops feel better with a single easing curve.
        if distance < 220 {
            animateScroll(toY: maxOffset, duration: 0.18, timing: .easeOut, token: nil)
            return
        }

        // Two-stage motion: fast travel, then soft settle near the bottom.
        let token = UUID()
        jumpAnimationToken = token

        let firstStageProgress: CGFloat = distance > 1400 ? 0.93 : 0.89
        let stage1TargetY = startY + distance * firstStageProgress
        let stage1Duration = min(0.16, max(0.08, Double(distance) / 7000))
        let stage2Duration = min(0.42, max(0.18, Double(distance) / 2600))

        animateScroll(toY: stage1TargetY, duration: stage1Duration, timing: .linear, token: token) { [weak self] in
            guard let self else { return }
            self.animateScroll(toY: maxOffset, duration: stage2Duration, timing: .easeOut, token: token)
        }
    }

    private func animateScroll(
        toY targetY: CGFloat,
        duration: TimeInterval,
        timing: CAMediaTimingFunctionName,
        token: UUID?,
        completion: (() -> Void)? = nil
    ) {
        let activeToken = token
        let currentOrigin = scrollView.contentView.bounds.origin
        let targetOrigin = CGPoint(x: currentOrigin.x, y: targetY)

        NSAnimationContext.runAnimationGroup { context in
            context.duration = duration
            context.timingFunction = CAMediaTimingFunction(name: timing)
            scrollView.contentView.animator().setBoundsOrigin(targetOrigin)
        } completionHandler: { [weak self] in
            guard let self else { return }
            if let activeToken, activeToken != self.jumpAnimationToken {
                return
            }
            self.scrollView.reflectScrolledClipView(self.scrollView.contentView)
            completion?()
        }
    }

    private func cancelJumpToLatestAnimation() {
        jumpAnimationToken = UUID()
    }

    // MARK: - VVChatTimelineRenderDataSource

    public var renderItemCount: Int {
        controller?.layouts.count ?? 0
    }

    public func renderItem(at index: Int) -> VVChatTimelineRenderItem? {
        guard let controller,
              let layout = controller.itemLayout(at: index),
              let rendered = controller.renderedMessage(for: layout.id) else { return nil }
        return VVChatTimelineRenderItem(id: layout.id, frame: layout.frame, contentOffset: layout.contentOffset, scene: rendered.scene)
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
        let visibleRect = scrollView.contentView.bounds
        for layout in controller.layouts {
            if layout.frame.maxY < visibleRect.minY { continue }
            if layout.frame.minY > visibleRect.maxY { break }
            if let rendered = controller.renderedMessage(for: layout.id) {
                for url in rendered.imageURLs {
                    imageStore.ensureImage(url: url)
                }
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
        guard let rendered = controller.renderedMessage(for: layout.id) else { return [] }

        let (start, end) = selection.ordered
        guard start.itemIndex <= index && end.itemIndex >= index else { return [] }

        let helper = VVMarkdownSelectionHelper(layout: rendered.layout, layoutEngine: rendered.layoutEngine)

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

        let rects = helper.selectionRects(from: mdStart, to: mdEnd)
        let contentOffset = rendered.selectionContentOffset
        return rects.map { rect in
            VVQuadPrimitive(
                frame: rect.offsetBy(dx: itemOffset.x + contentOffset.x, dy: itemOffset.y + contentOffset.y),
                color: selectionColor,
                cornerRadius: 2
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
                  let rendered = controller.renderedMessage(for: layout.id) else { continue }

            let helper = VVMarkdownSelectionHelper(layout: rendered.layout, layoutEngine: rendered.layoutEngine)

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
                  let rendered = controller.renderedMessage(for: layout.id) else { continue }
            let helper = VVMarkdownSelectionHelper(layout: rendered.layout, layoutEngine: rendered.layoutEngine)
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
                  let rendered = controller.renderedMessage(for: layout.id) else { continue }
            let helper = VVMarkdownSelectionHelper(layout: rendered.layout, layoutEngine: rendered.layoutEngine)
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
        updateFooterActionHover(at: point)
        if handleFooterActionTap(at: point) {
            return
        }
        selectionController.handleMouseDown(at: point, clickCount: clickCount, modifiers: modifiers, hitTester: self)
        metalView.setNeedsDisplay(metalView.bounds)
    }

    public func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseDraggedTo point: CGPoint, event: NSEvent) {
        updateFooterActionHover(at: point)
        selectionController.handleMouseDragged(to: point, hitTester: self)
        metalView.setNeedsDisplay(metalView.bounds)
    }

    public func chatTimelineMetalViewMouseUp(_ view: VVChatTimelineMetalView) {
        selectionController.handleMouseUp()
    }

    public func chatTimelineMetalView(_ view: VVChatTimelineMetalView, mouseMovedTo point: CGPoint) {
        updateFooterActionHover(at: point)
    }

    public func chatTimelineMetalViewMouseExited(_ view: VVChatTimelineMetalView) {
        updateFooterActionHover(at: nil)
    }
}

private extension VVChatTimelineView {
    func handleFooterActionTap(at point: CGPoint) -> Bool {
        guard let messageID = footerActionMessageID(at: point) else { return false }
        onUserMessageCopyAction?(messageID)
        return true
    }

    func updateFooterActionHover(at point: CGPoint?) {
        let hoveredID = point.flatMap { footerActionMessageID(at: $0) }
        guard hoveredID != hoveredFooterActionMessageID else { return }
        hoveredFooterActionMessageID = hoveredID
        onUserMessageCopyHoverChange?(hoveredID)
    }

    func footerActionMessageID(at point: CGPoint) -> String? {
        guard let controller else { return nil }
        let docPoint = viewPointToDocumentPoint(point)

        for (index, layout) in controller.layouts.enumerated() {
            if docPoint.y < layout.frame.minY || docPoint.y > layout.frame.maxY {
                continue
            }
            guard index < controller.messages.count else { continue }
            let message = controller.messages[index]
            guard message.role == .user || message.role == .assistant else { continue }
            guard let rendered = controller.renderedMessage(for: layout.id),
                  let actionFrame = rendered.footerTrailingActionFrame else { continue }

            let frameInDocument = actionFrame.offsetBy(
                dx: layout.frame.origin.x + layout.contentOffset.x,
                dy: layout.frame.origin.y + layout.contentOffset.y
            )
            if frameInDocument.contains(docPoint) {
                return message.id
            }
        }
        return nil
    }
}

// MARK: - VVTextHitTestable

extension VVChatTimelineView: VVTextHitTestable {
    public func hitTest(at point: CGPoint) -> ChatTextPosition? {
        guard let controller else { return nil }
        let docPoint = viewPointToDocumentPoint(point)

        // Find closest user-message item by Y position
        var targetItemIndex: Int?
        var closestDistance = CGFloat.greatestFiniteMagnitude

        for (index, layout) in controller.layouts.enumerated() {
            guard index < controller.messages.count else { continue }

            let frame = layout.frame
            if docPoint.y >= frame.minY && docPoint.y <= frame.maxY {
                targetItemIndex = index
                break
            }
            let distance: CGFloat
            if docPoint.y < frame.minY {
                distance = frame.minY - docPoint.y
            } else {
                distance = docPoint.y - frame.maxY
            }
            if distance < closestDistance {
                closestDistance = distance
                targetItemIndex = index
            }
        }

        guard let itemIndex = targetItemIndex,
              let layout = controller.itemLayout(at: itemIndex),
              let rendered = controller.renderedMessage(for: layout.id) else { return nil }

        // Convert to item-local coordinates
        let contentOffset = rendered.selectionContentOffset
        let localPoint = CGPoint(
            x: docPoint.x - layout.frame.origin.x - layout.contentOffset.x - contentOffset.x,
            y: docPoint.y - layout.frame.origin.y - layout.contentOffset.y - contentOffset.y
        )

        let helper = VVMarkdownSelectionHelper(layout: rendered.layout, layoutEngine: rendered.layoutEngine)
        guard let mdPos = helper.nearestTextPosition(to: localPoint) else { return nil }

        return ChatTextPosition(
            itemIndex: itemIndex,
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
    private let scaleFactorProvider: (String) -> CGFloat

    var onImageSizeUpdate: ((String, CGSize) -> Void)?
    var onImageLoaded: ((String) -> Void)?

    init(device: MTLDevice, scaleFactorProvider: @escaping (String) -> CGFloat) {
        self.loader = MarkdownImageLoader(device: device)
        self.scaleFactorProvider = scaleFactorProvider
    }

    func texture(for url: String) -> MTLTexture? {
        textures[url]
    }

    func clearCache() {
        textures.removeAll()
        sizes.removeAll()
        pending.removeAll()
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
                let scale = max(0.1, self.scaleFactorProvider(url))
                let size = CGSize(width: loaded.size.width / scale, height: loaded.size.height / scale)
                if self.sizes[url] != size {
                    self.sizes[url] = size
                    self.onImageSizeUpdate?(url, size)
                }
                self.onImageLoaded?(url)
            }
        }
    }

}
#endif
