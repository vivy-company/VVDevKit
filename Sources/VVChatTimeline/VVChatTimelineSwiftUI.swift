#if canImport(SwiftUI) && os(macOS)
import SwiftUI
import VVMarkdown

public struct VVChatTimelineViewRepresentable: NSViewRepresentable {
    public var controller: VVChatTimelineController
    public var onStateChange: ((VVChatTimelineState) -> Void)?
    public var onUserMessageCopyAction: ((String) -> Void)?
    public var onUserMessageCopyHoverChange: ((String?) -> Void)?
    public var onEntryActivate: ((String) -> Void)?

    public init(
        controller: VVChatTimelineController,
        onStateChange: ((VVChatTimelineState) -> Void)? = nil,
        onUserMessageCopyAction: ((String) -> Void)? = nil,
        onUserMessageCopyHoverChange: ((String?) -> Void)? = nil,
        onEntryActivate: ((String) -> Void)? = nil
    ) {
        self.controller = controller
        self.onStateChange = onStateChange
        self.onUserMessageCopyAction = onUserMessageCopyAction
        self.onUserMessageCopyHoverChange = onUserMessageCopyHoverChange
        self.onEntryActivate = onEntryActivate
    }

    public func makeNSView(context: Context) -> VVChatTimelineView {
        let view = VVChatTimelineView(frame: .zero)
        view.controller = controller
        view.onStateChange = onStateChange
        view.onUserMessageCopyAction = onUserMessageCopyAction
        view.onUserMessageCopyHoverChange = onUserMessageCopyHoverChange
        view.onEntryActivate = onEntryActivate
        return view
    }

    public func updateNSView(_ nsView: VVChatTimelineView, context: Context) {
        nsView.controller = controller
        nsView.onStateChange = onStateChange
        nsView.onUserMessageCopyAction = onUserMessageCopyAction
        nsView.onUserMessageCopyHoverChange = onUserMessageCopyHoverChange
        nsView.onEntryActivate = onEntryActivate
    }
}

public struct VVChatTimelineViewSwiftUI: View {
    public var controller: VVChatTimelineController
    public var onStateChange: ((VVChatTimelineState) -> Void)?
    public var onUserMessageCopyAction: ((String) -> Void)?
    public var onUserMessageCopyHoverChange: ((String?) -> Void)?
    public var onEntryActivate: ((String) -> Void)?

    public init(
        controller: VVChatTimelineController,
        onStateChange: ((VVChatTimelineState) -> Void)? = nil,
        onUserMessageCopyAction: ((String) -> Void)? = nil,
        onUserMessageCopyHoverChange: ((String?) -> Void)? = nil,
        onEntryActivate: ((String) -> Void)? = nil
    ) {
        self.controller = controller
        self.onStateChange = onStateChange
        self.onUserMessageCopyAction = onUserMessageCopyAction
        self.onUserMessageCopyHoverChange = onUserMessageCopyHoverChange
        self.onEntryActivate = onEntryActivate
    }

    public var body: some View {
        VVChatTimelineViewRepresentable(
            controller: controller,
            onStateChange: onStateChange,
            onUserMessageCopyAction: onUserMessageCopyAction,
            onUserMessageCopyHoverChange: onUserMessageCopyHoverChange,
            onEntryActivate: onEntryActivate
        )
    }
}
#endif
