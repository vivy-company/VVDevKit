import CoreGraphics
import Foundation

struct VVChatTimelineResolvedRenderItem {
    let index: Int
    let item: VVChatTimelineItem
    let layout: VVChatTimelineController.ItemLayout
    let rendered: VVChatRenderedMessage
}

#if os(macOS)
struct VVChatTimelineVisibleRenderItemUpdate {
    let index: Int
    let item: VVChatTimelineRenderItem
    let imageURLs: Set<String>
}

struct VVChatTimelineVisibleRenderSnapshot {
    let range: Range<Int>
    let itemsByIndex: [Int: VVChatTimelineRenderItem]
    let imageURLsByIndex: [Int: Set<String>]

    var imageURLs: Set<String> {
        imageURLsByIndex.values.reduce(into: Set<String>()) { $0.formUnion($1) }
    }

    static let empty = VVChatTimelineVisibleRenderSnapshot(
        range: 0..<0,
        itemsByIndex: [:],
        imageURLsByIndex: [:]
    )

    init(range: Range<Int>, itemsByIndex: [Int: VVChatTimelineRenderItem], imageURLsByIndex: [Int: Set<String>]) {
        self.range = range
        self.itemsByIndex = itemsByIndex
        self.imageURLsByIndex = imageURLsByIndex
    }

    func item(at index: Int) -> VVChatTimelineRenderItem? {
        guard range.contains(index) else { return nil }
        return itemsByIndex[index]
    }

    func applying(_ updates: [VVChatTimelineVisibleRenderItemUpdate]) -> VVChatTimelineVisibleRenderSnapshot {
        guard !updates.isEmpty else { return self }

        var nextItems = itemsByIndex
        var nextURLs = imageURLsByIndex
        for update in updates {
            guard range.contains(update.index) else { continue }
            nextItems[update.index] = update.item
            if update.imageURLs.isEmpty {
                nextURLs.removeValue(forKey: update.index)
            } else {
                nextURLs[update.index] = update.imageURLs
            }
        }

        return VVChatTimelineVisibleRenderSnapshot(
            range: range,
            itemsByIndex: nextItems,
            imageURLsByIndex: nextURLs
        )
    }
}
#endif
