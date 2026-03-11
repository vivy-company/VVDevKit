import CoreGraphics
import Foundation

struct VVChatTimelineResolvedRenderItem {
    let index: Int
    let item: VVChatTimelineItem
    let layout: VVChatTimelineController.ItemLayout
    let rendered: VVChatRenderedMessage
}

#if os(macOS)
struct VVChatTimelineVisibleRenderSnapshot {
    let range: Range<Int>
    let itemsByIndex: [Int: VVChatTimelineRenderItem]
    let imageURLs: Set<String>

    static let empty = VVChatTimelineVisibleRenderSnapshot(
        range: 0..<0,
        itemsByIndex: [:],
        imageURLs: []
    )

    func item(at index: Int) -> VVChatTimelineRenderItem? {
        guard range.contains(index) else { return nil }
        return itemsByIndex[index]
    }
}
#endif
