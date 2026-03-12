import CoreGraphics
import Foundation

@MainActor
protocol VVChatTimelineLayoutRendering: AnyObject {
    func layoutSummary(for item: VVChatTimelineItem) -> VVChatMessageLayoutSummary
    func estimatedLayoutSummary(for item: VVChatTimelineItem) -> VVChatMessageLayoutSummary
    func trimCaches(keepingItemIDs: Set<String>)
}

@MainActor
extension VVChatTimelineRenderService: VVChatTimelineLayoutRendering {}

struct VVChatTimelineLayoutMutation {
    let updatedIndexes: IndexSet
    let totalDelta: CGFloat
}

@MainActor
final class VVChatTimelineLayoutEngine {
    struct LayoutRecord {
        var id: String
        var height: CGFloat
        var contentOffset: CGPoint
        var isDraft: Bool
        var revision: Int
        var isExact: Bool
    }

    private struct HeightIndex {
        private var heights: [CGFloat] = []
        private var tree: [CGFloat] = [0]

        mutating func rebuild(heights: [CGFloat]) {
            self.heights = heights
            tree = Array(repeating: 0, count: heights.count + 1)
            for (index, height) in heights.enumerated() {
                add(height, at: index)
            }
        }

        mutating func append(_ height: CGFloat) {
            heights.append(height)
            let oneBasedIndex = heights.count
            let lowerBound = oneBasedIndex - (oneBasedIndex & -oneBasedIndex)
            let previousCoveredHeight =
                prefixHeight(before: oneBasedIndex - 1) - prefixHeight(before: lowerBound)
            tree.append(previousCoveredHeight + height)
        }

        mutating func updateHeight(at index: Int, to newHeight: CGFloat) {
            guard heights.indices.contains(index) else { return }
            let delta = newHeight - heights[index]
            guard delta != 0 else { return }
            heights[index] = newHeight
            add(delta, at: index)
        }

        func height(at index: Int) -> CGFloat {
            guard heights.indices.contains(index) else { return 0 }
            return heights[index]
        }

        func prefixHeight(before count: Int) -> CGFloat {
            guard count > 0 else { return 0 }
            var index = min(count, heights.count)
            var sum: CGFloat = 0
            while index > 0 {
                sum += tree[index]
                index -= index & -index
            }
            return sum
        }

        private mutating func add(_ delta: CGFloat, at index: Int) {
            var treeIndex = index + 1
            while treeIndex < tree.count {
                tree[treeIndex] += delta
                treeIndex += treeIndex & -treeIndex
            }
        }
    }

    private var style: VVChatTimelineStyle
    private var renderWidth: CGFloat
    private var layoutRecords: [LayoutRecord] = []
    private var heightIndex = HeightIndex()
    private var itemImageURLs: [String: Set<String>] = [:]
    private var imageURLToItemIDs: [String: Set<String>] = [:]

    init(style: VVChatTimelineStyle, renderWidth: CGFloat) {
        self.style = style
        self.renderWidth = renderWidth
    }

    var totalHeight: CGFloat {
        computedTotalHeight()
    }

    var layoutCount: Int {
        layoutRecords.count
    }

    func updateStyle(_ style: VVChatTimelineStyle) {
        self.style = style
    }

    func updateRenderWidth(_ width: CGFloat) {
        renderWidth = width
    }

    func reset(
        items: [VVChatTimelineItem],
        renderer: VVChatTimelineLayoutRendering
    ) {
        layoutRecords.removeAll(keepingCapacity: true)
        itemImageURLs.removeAll(keepingCapacity: true)
        imageURLToItemIDs.removeAll(keepingCapacity: true)

        var heights: [CGFloat] = []
        heights.reserveCapacity(items.count)
        for item in items {
            let record = buildLayoutRecord(for: item, exact: false, renderer: renderer)
            layoutRecords.append(record)
            heights.append(record.height)
        }
        heightIndex.rebuild(heights: heights)
    }

    func append(
        item: VVChatTimelineItem,
        exact: Bool,
        renderer: VVChatTimelineLayoutRendering
    ) {
        let record = buildLayoutRecord(for: item, exact: exact, renderer: renderer)
        layoutRecords.append(record)
        heightIndex.append(record.height)
    }

    func replace(
        range: Range<Int>,
        items: [VVChatTimelineItem],
        exact: Bool,
        renderer: VVChatTimelineLayoutRendering
    ) {
        // Clean up image mappings for records being replaced.
        for index in range where layoutRecords.indices.contains(index) {
            let removedID = layoutRecords[index].id
            if let urls = itemImageURLs.removeValue(forKey: removedID) {
                for url in urls {
                    imageURLToItemIDs[url]?.remove(removedID)
                    if imageURLToItemIDs[url]?.isEmpty == true {
                        imageURLToItemIDs.removeValue(forKey: url)
                    }
                }
            }
        }
        let newRecords = items.map { buildLayoutRecord(for: $0, exact: exact, renderer: renderer) }
        layoutRecords.replaceSubrange(range, with: newRecords)
        heightIndex.rebuild(heights: layoutRecords.map(\.height))
    }

    func replace(
        range: Range<Int>,
        items: [VVChatTimelineItem],
        renderer: VVChatTimelineLayoutRendering
    ) {
        for index in range where layoutRecords.indices.contains(index) {
            let removedID = layoutRecords[index].id
            if let urls = itemImageURLs.removeValue(forKey: removedID) {
                for url in urls {
                    imageURLToItemIDs[url]?.remove(removedID)
                    if imageURLToItemIDs[url]?.isEmpty == true {
                        imageURLToItemIDs.removeValue(forKey: url)
                    }
                }
            }
        }
        let newRecords = items.map { item in
            buildLayoutRecord(for: item, exact: item.message.state != .draft, renderer: renderer)
        }
        layoutRecords.replaceSubrange(range, with: newRecords)
        heightIndex.rebuild(heights: layoutRecords.map(\.height))
    }

    @discardableResult
    func updateLayout(
        at index: Int,
        item: VVChatTimelineItem,
        exact: Bool,
        renderer: VVChatTimelineLayoutRendering
    ) -> CGFloat {
        let summary = exact
            ? renderer.layoutSummary(for: item)
            : renderer.estimatedLayoutSummary(for: item)
        updateImageMappings(itemID: item.id, imageURLs: Set(summary.imageURLs))
        let oldHeight = heightIndex.height(at: index)
        let newHeight = summary.height
        layoutRecords[index].height = newHeight
        layoutRecords[index].contentOffset = summary.contentOffset
        layoutRecords[index].isDraft = item.message.state == .draft
        layoutRecords[index].revision = item.revision
        layoutRecords[index].isExact = exact

        if newHeight != oldHeight {
            heightIndex.updateHeight(at: index, to: newHeight)
        }
        return newHeight - oldHeight
    }

    func relayout(
        indexes: [Int],
        items: [VVChatTimelineItem],
        renderer: VVChatTimelineLayoutRendering
    ) -> VVChatTimelineLayoutMutation {
        let uniqueSorted = Array(Set(indexes)).sorted()
        var updatedIndexes = IndexSet()
        var totalDelta: CGFloat = 0

        for index in uniqueSorted where items.indices.contains(index) {
            totalDelta += updateLayout(at: index, item: items[index], exact: true, renderer: renderer)
            updatedIndexes.insert(index)
        }

        return VVChatTimelineLayoutMutation(updatedIndexes: updatedIndexes, totalDelta: totalDelta)
    }

    func hydrateExactLayouts(
        in range: Range<Int>,
        items: [VVChatTimelineItem],
        renderer: VVChatTimelineLayoutRendering
    ) -> VVChatTimelineLayoutMutation {
        let clampedLower = max(0, range.lowerBound)
        let clampedUpper = min(layoutRecords.count, range.upperBound)
        guard clampedLower < clampedUpper else {
            return VVChatTimelineLayoutMutation(updatedIndexes: [], totalDelta: 0)
        }

        var updatedIndexes = IndexSet()
        var totalDelta: CGFloat = 0

        for index in clampedLower..<clampedUpper {
            guard layoutRecords.indices.contains(index),
                  !layoutRecords[index].isExact,
                  items.indices.contains(index) else { continue }
            totalDelta += updateLayout(at: index, item: items[index], exact: true, renderer: renderer)
            updatedIndexes.insert(index)
        }

        return VVChatTimelineLayoutMutation(updatedIndexes: updatedIndexes, totalDelta: totalDelta)
    }

    func itemLayout(at index: Int) -> VVChatTimelineController.ItemLayout? {
        guard layoutRecords.indices.contains(index) else { return nil }
        let record = layoutRecords[index]
        return VVChatTimelineController.ItemLayout(
            id: record.id,
            frame: CGRect(
                x: 0,
                y: originY(for: index),
                width: renderWidth,
                height: record.height
            ),
            contentOffset: record.contentOffset,
            isDraft: record.isDraft,
            revision: record.revision,
            isExact: record.isExact
        )
    }

    func layouts() -> [VVChatTimelineController.ItemLayout] {
        guard !layoutRecords.isEmpty else { return [] }
        var snapshot: [VVChatTimelineController.ItemLayout] = []
        snapshot.reserveCapacity(layoutRecords.count)
        for index in layoutRecords.indices {
            if let layout = itemLayout(at: index) {
                snapshot.append(layout)
            }
        }
        return snapshot
    }

    func visibleLayoutRange(in viewport: CGRect, overscan: CGFloat) -> Range<Int> {
        guard !layoutRecords.isEmpty else { return 0..<0 }
        let minY = viewport.minY - overscan
        let maxY = viewport.maxY + overscan
        let lower = lowerBound(forMaxYAbove: minY)
        let upper = upperBound(forMinYBelow: maxY)
        return lower..<max(lower, upper)
    }

    func itemIndex(containingDocumentY y: CGFloat) -> Int? {
        guard !layoutRecords.isEmpty else { return nil }
        var low = 0
        var high = layoutRecords.count - 1
        while low <= high {
            let mid = (low + high) / 2
            guard let frame = frame(at: mid) else { return nil }
            if y < frame.minY {
                high = mid - 1
            } else if y > frame.maxY {
                low = mid + 1
            } else {
                return mid
            }
        }
        return nil
    }

    func nearestItemIndex(forDocumentY y: CGFloat) -> Int? {
        guard !layoutRecords.isEmpty else { return nil }
        var low = 0
        var high = layoutRecords.count - 1
        while low <= high {
            let mid = (low + high) / 2
            guard let frame = frame(at: mid) else { return nil }
            if y < frame.minY {
                high = mid - 1
            } else if y > frame.maxY {
                low = mid + 1
            } else {
                return mid
            }
        }

        if low >= layoutRecords.count { return layoutRecords.count - 1 }
        if high < 0 { return 0 }

        guard let lowerFrame = frame(at: high),
              let upperFrame = frame(at: low) else {
            return nil
        }
        let lowerDistance = abs(y - lowerFrame.maxY)
        let upperDistance = abs(upperFrame.minY - y)
        return lowerDistance <= upperDistance ? high : low
    }

    func trimCaches(
        in viewport: CGRect,
        overscan: CGFloat,
        itemPadding: Int = 12,
        renderer: VVChatTimelineLayoutRendering
    ) {
        guard !layoutRecords.isEmpty else { return }
        let visible = visibleLayoutRange(in: viewport, overscan: overscan)
        guard !visible.isEmpty else { return }

        let lowerBound = max(0, visible.lowerBound - itemPadding)
        let upperBound = min(layoutRecords.count, visible.upperBound + itemPadding)
        var keepIDs = Set<String>()
        keepIDs.reserveCapacity((upperBound - lowerBound) + 4)

        for index in lowerBound..<upperBound {
            keepIDs.insert(layoutRecords[index].id)
        }
        for record in layoutRecords where record.isDraft {
            keepIDs.insert(record.id)
        }

        renderer.trimCaches(keepingItemIDs: keepIDs)
    }

    func itemIDs(forImageURL url: String) -> [String] {
        Array(imageURLToItemIDs[url] ?? [])
    }

    func debugExactLayoutCount() -> Int {
        layoutRecords.reduce(into: 0) { count, record in
            if record.isExact { count += 1 }
        }
    }

    private func buildLayoutRecord(
        for item: VVChatTimelineItem,
        exact: Bool,
        renderer: VVChatTimelineLayoutRendering
    ) -> LayoutRecord {
        let summary = exact
            ? renderer.layoutSummary(for: item)
            : renderer.estimatedLayoutSummary(for: item)
        updateImageMappings(itemID: item.id, imageURLs: Set(summary.imageURLs))
        return LayoutRecord(
            id: item.id,
            height: summary.height,
            contentOffset: summary.contentOffset,
            isDraft: item.message.state == .draft,
            revision: item.revision,
            isExact: exact
        )
    }

    private func computedTotalHeight() -> CGFloat {
        guard !layoutRecords.isEmpty else {
            return style.timelineInsets.top + style.timelineInsets.bottom
        }
        let heights = heightIndex.prefixHeight(before: layoutRecords.count)
        let spacing = CGFloat(max(0, layoutRecords.count - 1)) * style.messageSpacing
        return style.timelineInsets.top + heights + spacing + style.timelineInsets.bottom
    }

    private func originY(for index: Int) -> CGFloat {
        style.timelineInsets.top +
            heightIndex.prefixHeight(before: index) +
            CGFloat(index) * style.messageSpacing
    }

    private func frame(at index: Int) -> CGRect? {
        guard layoutRecords.indices.contains(index) else { return nil }
        return CGRect(
            x: 0,
            y: originY(for: index),
            width: renderWidth,
            height: layoutRecords[index].height
        )
    }

    private func lowerBound(forMaxYAbove value: CGFloat) -> Int {
        var low = 0
        var high = layoutRecords.count
        while low < high {
            let mid = (low + high) / 2
            let maxY = originY(for: mid) + layoutRecords[mid].height
            if maxY < value {
                low = mid + 1
            } else {
                high = mid
            }
        }
        return low
    }

    private func upperBound(forMinYBelow value: CGFloat) -> Int {
        var low = 0
        var high = layoutRecords.count
        while low < high {
            let mid = (low + high) / 2
            let minY = originY(for: mid)
            if minY <= value {
                low = mid + 1
            } else {
                high = mid
            }
        }
        return low
    }

    private func updateImageMappings(itemID: String, imageURLs: Set<String>) {
        if let previous = itemImageURLs[itemID] {
            for url in previous {
                imageURLToItemIDs[url]?.remove(itemID)
                if imageURLToItemIDs[url]?.isEmpty == true {
                    imageURLToItemIDs.removeValue(forKey: url)
                }
            }
        }
        itemImageURLs[itemID] = imageURLs
        for url in imageURLs {
            imageURLToItemIDs[url, default: []].insert(itemID)
        }
    }
}
