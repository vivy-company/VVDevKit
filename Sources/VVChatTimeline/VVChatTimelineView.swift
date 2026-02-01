#if os(macOS)
import AppKit
import Foundation
import Metal
import VVMarkdown

public final class VVChatTimelineView: NSView, VVChatTimelineRenderDataSource {
    private let scrollView: VVChatTimelineScrollView
    private let metalView: VVChatTimelineMetalView
    private let jumpButton: NSButton
    private var didInitialScroll: Bool = false
    private var controllerObservation: NSObjectProtocol?
    private var currentFont: VVFont?
    private var imageStore: VVChatTimelineImageStore?

    public var controller: VVChatTimelineController? {
        didSet {
            bindController(oldValue: oldValue)
        }
    }

    public override init(frame frameRect: NSRect) {
        scrollView = VVChatTimelineScrollView(frame: frameRect)
        metalView = VVChatTimelineMetalView(frame: frameRect, font: .systemFont(ofSize: 14))
        jumpButton = NSButton(title: "Jump to latest", target: nil, action: nil)
        super.init(frame: frameRect)
        setup()
    }

    required init?(coder: NSCoder) {
        scrollView = VVChatTimelineScrollView(frame: .zero)
        metalView = VVChatTimelineMetalView(frame: .zero, font: .systemFont(ofSize: 14))
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

        scrollView.drawsBackground = false
        scrollView.hasVerticalScroller = true
        scrollView.documentView = metalView
        scrollView.contentView.postsBoundsChangedNotifications = true
        scrollView.onInteractionChange = { [weak self] isInteracting in
            self?.controller?.markUserInteraction(isInteracting)
        }
        addSubview(scrollView)

        metalView.renderDataSource = self
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
        } else if !didInitialScroll, update.totalHeight > 0 {
            scrollToBottom(animated: false)
            didInitialScroll = true
        }

        requestImagesForVisibleItems()
        metalView.setNeedsDisplay(metalView.bounds)
    }

    private func updateDocumentHeight(_ height: CGFloat) {
        let contentBounds = scrollView.contentView.bounds
        let width = contentBounds.width
        let minHeight = contentBounds.height
        let newFrame = CGRect(x: 0, y: 0, width: width, height: max(height, minHeight))
        if metalView.frame != newFrame {
            metalView.frame = newFrame
        }
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
        let visibleRect = scrollView.contentView.bounds
        if layout.frame.maxY < visibleRect.minY {
            let newOrigin = CGPoint(x: visibleRect.origin.x, y: visibleRect.origin.y + delta)
            scrollView.contentView.scroll(to: newOrigin)
            scrollView.reflectScrolledClipView(scrollView.contentView)
        }
    }

    private func handleScroll() {
        guard let controller else { return }
        let visibleRect = scrollView.contentView.bounds
        let contentHeight = max(controller.totalHeight, visibleRect.height)
        let maxOffset = max(0, contentHeight - visibleRect.height)
        let distanceFromBottom = maxOffset - visibleRect.origin.y
        controller.updatePinnedState(distanceFromBottom: distanceFromBottom)
        jumpButton.isHidden = !controller.state.hasUnreadNewContent
        requestImagesForVisibleItems()
        metalView.setNeedsDisplay(metalView.bounds)
    }

    public func scrollToBottom(animated: Bool) {
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
        scrollToBottom(animated: true)
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
        controller?.currentStyle.backgroundColor ?? SIMD4(0, 0, 0, 1)
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
}

private final class VVChatTimelineScrollView: NSScrollView {
    var onInteractionChange: ((Bool) -> Void)?

    override func scrollWheel(with event: NSEvent) {
        let phase = event.phase
        let momentum = event.momentumPhase
        if phase == .began || phase == .changed || momentum == .began {
            onInteractionChange?(true)
        }
        if phase == .ended || momentum == .ended {
            onInteractionChange?(false)
        }
        super.scrollWheel(with: event)
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
