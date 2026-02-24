#if canImport(SwiftUI) && os(macOS)
import SwiftUI
import VVMarkdown

public struct VVChatTimelineViewRepresentable: NSViewRepresentable {
    public var controller: VVChatTimelineController
    public var onStateChange: ((VVChatTimelineState) -> Void)?
    public var onUserMessageCopyAction: ((String) -> Void)?

    public init(
        controller: VVChatTimelineController,
        onStateChange: ((VVChatTimelineState) -> Void)? = nil,
        onUserMessageCopyAction: ((String) -> Void)? = nil
    ) {
        self.controller = controller
        self.onStateChange = onStateChange
        self.onUserMessageCopyAction = onUserMessageCopyAction
    }

    public func makeNSView(context: Context) -> VVChatTimelineView {
        let view = VVChatTimelineView(frame: .zero)
        view.controller = controller
        view.onStateChange = onStateChange
        view.onUserMessageCopyAction = onUserMessageCopyAction
        return view
    }

    public func updateNSView(_ nsView: VVChatTimelineView, context: Context) {
        nsView.controller = controller
        nsView.onStateChange = onStateChange
        nsView.onUserMessageCopyAction = onUserMessageCopyAction
    }
}

public struct VVChatTimelineViewSwiftUI: View {
    public var controller: VVChatTimelineController
    public var onStateChange: ((VVChatTimelineState) -> Void)?
    public var onUserMessageCopyAction: ((String) -> Void)?

    public init(
        controller: VVChatTimelineController,
        onStateChange: ((VVChatTimelineState) -> Void)? = nil,
        onUserMessageCopyAction: ((String) -> Void)? = nil
    ) {
        self.controller = controller
        self.onStateChange = onStateChange
        self.onUserMessageCopyAction = onUserMessageCopyAction
    }

    public var body: some View {
        VVChatTimelineViewRepresentable(
            controller: controller,
            onStateChange: onStateChange,
            onUserMessageCopyAction: onUserMessageCopyAction
        )
    }
}
#endif
