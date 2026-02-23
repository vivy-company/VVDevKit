#if canImport(SwiftUI) && os(macOS)
import SwiftUI
import VVMarkdown

public struct VVChatTimelineViewRepresentable: NSViewRepresentable {
    public var controller: VVChatTimelineController
    public var onStateChange: ((VVChatTimelineState) -> Void)?

    public init(
        controller: VVChatTimelineController,
        onStateChange: ((VVChatTimelineState) -> Void)? = nil
    ) {
        self.controller = controller
        self.onStateChange = onStateChange
    }

    public func makeNSView(context: Context) -> VVChatTimelineView {
        let view = VVChatTimelineView(frame: .zero)
        view.controller = controller
        view.onStateChange = onStateChange
        return view
    }

    public func updateNSView(_ nsView: VVChatTimelineView, context: Context) {
        nsView.controller = controller
        nsView.onStateChange = onStateChange
    }
}

public struct VVChatTimelineViewSwiftUI: View {
    public var controller: VVChatTimelineController
    public var onStateChange: ((VVChatTimelineState) -> Void)?

    public init(
        controller: VVChatTimelineController,
        onStateChange: ((VVChatTimelineState) -> Void)? = nil
    ) {
        self.controller = controller
        self.onStateChange = onStateChange
    }

    public var body: some View {
        VVChatTimelineViewRepresentable(
            controller: controller,
            onStateChange: onStateChange
        )
    }
}
#endif
