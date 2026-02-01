#if canImport(SwiftUI) && os(macOS)
import SwiftUI

public struct VVChatTimelineViewRepresentable: NSViewRepresentable {
    public var controller: VVChatTimelineController

    public init(controller: VVChatTimelineController) {
        self.controller = controller
    }

    public func makeNSView(context: Context) -> VVChatTimelineView {
        let view = VVChatTimelineView(frame: .zero)
        view.controller = controller
        return view
    }

    public func updateNSView(_ nsView: VVChatTimelineView, context: Context) {
        nsView.controller = controller
    }
}

public struct VVChatTimelineViewSwiftUI: View {
    public var controller: VVChatTimelineController

    public init(controller: VVChatTimelineController) {
        self.controller = controller
    }

    public var body: some View {
        VVChatTimelineViewRepresentable(controller: controller)
    }
}
#endif
