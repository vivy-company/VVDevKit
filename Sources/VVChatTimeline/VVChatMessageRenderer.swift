import Foundation
import CoreText
import VVMarkdown
import VVMetalPrimitives

public struct VVChatRenderedMessage {
    public let id: String
    public let revision: Int
    public let chromeScene: VVScene
    public let chromeOrderedPrimitiveIndices: [Int]
    public let chromeVisibilityIndex: VVPrimitiveVisibilityIndex
    public let height: CGFloat
    public let contentOffset: CGPoint
    public let selectionContentOffset: CGPoint
    public let isDraft: Bool
    public let imageURLs: [String]
    public let footerTrailingActionFrame: CGRect?
    public let interactiveRegions: [VVChatInteractiveRegion]
    fileprivate let contentSceneSource: VVChatMessageRenderer.ContentSceneSource
}

public enum VVChatInteractiveAction: Hashable, Sendable {
    case link(String)
}

public struct VVChatInteractiveRegion: Hashable, Sendable {
    public let id: String
    public let frame: CGRect
    public let action: VVChatInteractiveAction
    public let hoverFillColor: SIMD4<Float>?
    public let cornerRadius: CGFloat

    public init(
        id: String,
        frame: CGRect,
        action: VVChatInteractiveAction,
        hoverFillColor: SIMD4<Float>? = nil,
        cornerRadius: CGFloat = 10
    ) {
        self.id = id
        self.frame = frame
        self.action = action
        self.hoverFillColor = hoverFillColor
        self.cornerRadius = cornerRadius
    }
}

struct VVChatSceneArtifacts {
    let scene: VVScene
    let orderedPrimitiveIndices: [Int]
    let visibilityIndex: VVPrimitiveVisibilityIndex
}

public final class VVChatMessageRenderer {
    private final class LRUCache<Key: Hashable, Value> {
        private final class Node {
            let key: Key
            var value: Value
            var cost: Int
            var prev: Node?
            var next: Node?
            init(key: Key, value: Value, cost: Int) {
                self.key = key
                self.value = value
                self.cost = cost
            }
        }

        private var map: [Key: Node] = [:]
        private var head: Node?  // most recent
        private var tail: Node?  // least recent
        private var limit: Int
        private var costLimit: Int?
        private let cost: (Value) -> Int
        private var totalCost = 0

        init(limit: Int, costLimit: Int? = nil, cost: @escaping (Value) -> Int = { _ in 1 }) {
            self.limit = max(0, limit)
            self.costLimit = costLimit.map { max(0, $0) }
            self.cost = cost
        }

        func updateLimit(_ limit: Int) {
            self.limit = max(0, limit)
            evictIfNeeded()
        }

        func updateCostLimit(_ costLimit: Int?) {
            self.costLimit = costLimit.map { max(0, $0) }
            evictIfNeeded()
        }

        func value(for key: Key) -> Value? {
            guard let node = map[key] else { return nil }
            moveToTail(node)
            return node.value
        }

        func set(_ value: Value, for key: Key) {
            if limit == 0 {
                map.removeAll(keepingCapacity: true)
                head = nil
                tail = nil
                totalCost = 0
                return
            }
            let valueCost = max(1, cost(value))
            if let existing = map[key] {
                totalCost -= existing.cost
                existing.value = value
                existing.cost = valueCost
                totalCost += valueCost
                moveToTail(existing)
            } else {
                let node = Node(key: key, value: value, cost: valueCost)
                map[key] = node
                totalCost += valueCost
                appendToTail(node)
            }
            evictIfNeeded()
        }

        func remove(where predicate: (Key) -> Bool) {
            var node = head
            while let current = node {
                node = current.next
                if predicate(current.key) {
                    totalCost -= current.cost
                    unlink(current)
                    map.removeValue(forKey: current.key)
                }
            }
        }

        func removeAll() {
            map.removeAll(keepingCapacity: true)
            head = nil
            tail = nil
            totalCost = 0
        }

        var count: Int {
            map.count
        }

        var currentCost: Int {
            totalCost
        }

        func keysFromLeastRecent() -> [Key] {
            var keys: [Key] = []
            keys.reserveCapacity(map.count)
            var node = head
            while let current = node {
                keys.append(current.key)
                node = current.next
            }
            return keys
        }

        func valuesFromLeastRecent() -> [Value] {
            var values: [Value] = []
            values.reserveCapacity(map.count)
            var node = head
            while let current = node {
                values.append(current.value)
                node = current.next
            }
            return values
        }

        func updateValue(for key: Key, _ update: (inout Value) -> Void) {
            guard let node = map[key] else { return }
            totalCost -= node.cost
            update(&node.value)
            node.cost = max(1, cost(node.value))
            totalCost += node.cost
            evictIfNeeded()
        }

        private func moveToTail(_ node: Node) {
            guard node !== tail else { return }
            unlink(node)
            appendToTail(node)
        }

        private func appendToTail(_ node: Node) {
            node.prev = tail
            node.next = nil
            tail?.next = node
            tail = node
            if head == nil { head = node }
        }

        private func unlink(_ node: Node) {
            node.prev?.next = node.next
            node.next?.prev = node.prev
            if node === head { head = node.next }
            if node === tail { tail = node.prev }
            node.prev = nil
            node.next = nil
        }

        private func evictIfNeeded() {
            guard limit > 0 else { return }
            while (map.count > limit || (costLimit != nil && totalCost > costLimit!)), let oldest = head {
                totalCost -= oldest.cost
                unlink(oldest)
                map.removeValue(forKey: oldest.key)
            }
        }
    }

    fileprivate struct CacheKey: Hashable {
        let id: String
        let revision: Int
        let widthKey: Int
        let isDraft: Bool
        let contentScaleKey: Int
    }

    struct DebugSnapshot {
        let renderedMessageCacheCount: Int
        let renderedMessageCacheEstimatedCost: Int
        let renderedMessageCacheCostLimit: Int
        let preparedMarkdownCacheCount: Int
        let materializedPreparedLayoutCount: Int
        let materializedPreparedLayoutEstimatedCost: Int
        let materializedPreparedLayoutCostLimit: Int
        let preparedMarkdownCacheHits: Int
        let preparedMarkdownCacheMisses: Int
        let preparedMarkdownCacheEstimatedCost: Int
        let preparedMarkdownCacheCostLimit: Int
        let markdownParseCount: Int
        let markdownLayoutCount: Int
        let markdownWindowLayoutCount: Int
        let markdownSceneBuildCount: Int
        let incrementalImageLayoutPassCount: Int
        let sceneWindowCacheEstimatedCost: Int
        let sceneWindowCacheCostLimit: Int
    }

    private struct PreparedMarkdownLayoutAnalysis {
        let imageURLs: Set<String>
        let measuredWidth: CGFloat?
        let contentBounds: CGRect?
        let estimatedCost: Int
        let totalHeight: CGFloat
        let blockFrameMinY: [CGFloat]
        let blockMinY: [CGFloat]
        let blockMaxY: [CGFloat]
        let sourceBlockIndexes: [Int]
        let directImageBlockIDsByURL: [String: [String]]
        let imageRowBlockIDsByURL: [String: [String]]
    }

    private struct PreparedMarkdownContent {
        let document: ParsedMarkdownDocument
        var layout: MarkdownLayout?
        var analysis: PreparedMarkdownLayoutAnalysis
        var appliedImageSizes: [String: CGSize]
    }

    fileprivate enum ContentSceneSource {
        case none
        case markdown(CacheKey)
        case staticScene(VVChatSceneArtifacts)
    }

    private struct SceneWindowCacheKey: Hashable {
        let key: CacheKey
        let startBlock: Int
        let endBlock: Int
    }

    private struct HeaderRender {
        let scene: VVScene
        let height: CGFloat
        let imageURLs: [String]
    }

    private struct CustomContentRender {
        let scene: VVScene
        let height: CGFloat
        let visualWidth: CGFloat
        let interactiveRegions: [VVChatInteractiveRegion]
        let imageURLs: [String]
    }

    private struct FixedResources {
        let final: ContentResources
        let draft: ContentResources
        let header: ContentResources
        let timestamp: ContentResources
        let loading: ContentResources
    }

    private struct StyledTextResourceKey: Hashable {
        let fontName: String
        let fontSizeKey: Int
        let widthKey: Int
        let colorKey: SIMD4<Int>
    }

    private typealias ContentResources = (layoutEngine: MarkdownLayoutEngine, pipeline: VVMarkdownRenderPipeline)

    private let parser = MarkdownParser()
    private var finalLayoutEngine: MarkdownLayoutEngine
    private var draftLayoutEngine: MarkdownLayoutEngine
    private var finalPipeline: VVMarkdownRenderPipeline
    private var draftPipeline: VVMarkdownRenderPipeline
    private var headerLayoutEngine: MarkdownLayoutEngine
    private var timestampLayoutEngine: MarkdownLayoutEngine
    private var headerPipeline: VVMarkdownRenderPipeline
    private var timestampPipeline: VVMarkdownRenderPipeline
    private var loadingLayoutEngine: MarkdownLayoutEngine
    private var loadingPipeline: VVMarkdownRenderPipeline
    private var scaledFinalResources: [Int: ContentResources] = [:]
    private var scaledDraftResources: [Int: ContentResources] = [:]
    private var styledTextResourceCache: [StyledTextResourceKey: ContentResources] = [:]
    private var cache: LRUCache<CacheKey, VVChatRenderedMessage>
    private var preparedMarkdownCache: LRUCache<CacheKey, PreparedMarkdownContent>
    private var sceneWindowCache: LRUCache<SceneWindowCacheKey, VVChatSceneArtifacts>
    private var contentWidth: CGFloat
    private var style: VVChatTimelineStyle
    private var imageSizes: [String: CGSize] = [:]
    private var preparedMarkdownCacheHits = 0
    private var preparedMarkdownCacheMisses = 0
    private var markdownParseCount = 0
    private var markdownLayoutCount = 0
    private var markdownWindowLayoutCount = 0
    private var markdownSceneBuildCount = 0
    private var incrementalImageLayoutPassCount = 0
    private static let renderedMessageCacheCostLimit = 12 * 1024 * 1024
    private static let materializedPreparedLayoutCostLimit = 24 * 1024 * 1024
    private static let preparedMarkdownCacheCostLimit = 64 * 1024 * 1024
    private static let sceneWindowCacheCostLimit = 24 * 1024 * 1024
    private static let timeFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateStyle = .none
        formatter.timeStyle = .short
        return formatter
    }()

    public init(style: VVChatTimelineStyle, contentWidth: CGFloat) {
        let fixedResources = Self.makeFixedResources(style: style, contentWidth: contentWidth)
        self.style = style
        self.contentWidth = contentWidth
        self.finalLayoutEngine = fixedResources.final.layoutEngine
        self.draftLayoutEngine = fixedResources.draft.layoutEngine
        self.finalPipeline = fixedResources.final.pipeline
        self.draftPipeline = fixedResources.draft.pipeline
        self.headerLayoutEngine = fixedResources.header.layoutEngine
        self.timestampLayoutEngine = fixedResources.timestamp.layoutEngine
        self.headerPipeline = fixedResources.header.pipeline
        self.timestampPipeline = fixedResources.timestamp.pipeline
        self.loadingLayoutEngine = fixedResources.loading.layoutEngine
        self.loadingPipeline = fixedResources.loading.pipeline
        self.cache = LRUCache(
            limit: style.renderedCacheLimit,
            costLimit: Self.renderedMessageCacheCostLimit,
            cost: Self.estimatedRenderedMessageCost
        )
        self.preparedMarkdownCache = LRUCache(
            limit: style.renderedCacheLimit,
            costLimit: Self.preparedMarkdownCacheCostLimit,
            cost: Self.estimatedPreparedMarkdownCost
        )
        self.sceneWindowCache = LRUCache(
            limit: max(8, style.renderedCacheLimit * 4),
            costLimit: Self.sceneWindowCacheCostLimit,
            cost: Self.estimatedSceneArtifactsCost
        )
    }

    public func updateStyle(_ style: VVChatTimelineStyle) {
        let fixedResources = Self.makeFixedResources(style: style, contentWidth: contentWidth)
        self.style = style
        finalLayoutEngine = fixedResources.final.layoutEngine
        draftLayoutEngine = fixedResources.draft.layoutEngine
        finalPipeline = fixedResources.final.pipeline
        draftPipeline = fixedResources.draft.pipeline
        headerLayoutEngine = fixedResources.header.layoutEngine
        timestampLayoutEngine = fixedResources.timestamp.layoutEngine
        headerPipeline = fixedResources.header.pipeline
        timestampPipeline = fixedResources.timestamp.pipeline
        loadingLayoutEngine = fixedResources.loading.layoutEngine
        loadingPipeline = fixedResources.loading.pipeline
        clearResourceCaches()
        cache.updateLimit(style.renderedCacheLimit)
        cache.updateCostLimit(Self.renderedMessageCacheCostLimit)
        preparedMarkdownCache.updateLimit(style.renderedCacheLimit)
        preparedMarkdownCache.updateCostLimit(Self.preparedMarkdownCacheCostLimit)
        sceneWindowCache.updateLimit(max(8, style.renderedCacheLimit * 4))
        sceneWindowCache.updateCostLimit(Self.sceneWindowCacheCostLimit)
        cache.removeAll()
        preparedMarkdownCache.removeAll()
        sceneWindowCache.removeAll()
    }

    public func updateContentWidth(_ width: CGFloat) {
        let widthKey = Self.widthKey(for: width)
        if widthKey == Self.widthKey(for: contentWidth) {
            return
        }
        contentWidth = width
        finalLayoutEngine.updateContentWidth(width)
        draftLayoutEngine.updateContentWidth(width)
        headerLayoutEngine.updateContentWidth(width)
        timestampLayoutEngine.updateContentWidth(width)
        loadingLayoutEngine.updateContentWidth(width)
        clearResourceCaches()
        cache.removeAll()
        preparedMarkdownCache.removeAll()
        sceneWindowCache.removeAll()
    }

    public func updateImageSize(url: String, size: CGSize) -> Bool {
        if imageSizes[url] == size {
            return false
        }
        imageSizes[url] = size
        return true
    }

    public func invalidate(messageID: String) {
        cache.remove(where: { $0.id == messageID })
        preparedMarkdownCache.remove(where: { $0.id == messageID })
        sceneWindowCache.remove(where: { $0.key.id == messageID })
    }

    func invalidateRendered(messageID: String) {
        cache.remove(where: { $0.id == messageID })
        sceneWindowCache.remove(where: { $0.key.id == messageID })
    }

    public func invalidateAll() {
        cache.removeAll()
        preparedMarkdownCache.removeAll()
        sceneWindowCache.removeAll()
    }

    func debugSnapshot() -> DebugSnapshot {
        let preparedValues = preparedMarkdownCache.valuesFromLeastRecent()
        return DebugSnapshot(
            renderedMessageCacheCount: cache.count,
            renderedMessageCacheEstimatedCost: cache.currentCost,
            renderedMessageCacheCostLimit: Self.renderedMessageCacheCostLimit,
            preparedMarkdownCacheCount: preparedMarkdownCache.count,
            materializedPreparedLayoutCount: preparedValues.reduce(into: 0) { count, value in
                if value.layout != nil { count += 1 }
            },
            materializedPreparedLayoutEstimatedCost: preparedValues.reduce(into: 0) { total, value in
                total += Self.estimatedResidentPreparedLayoutCost(value)
            },
            materializedPreparedLayoutCostLimit: Self.materializedPreparedLayoutCostLimit,
            preparedMarkdownCacheHits: preparedMarkdownCacheHits,
            preparedMarkdownCacheMisses: preparedMarkdownCacheMisses,
            preparedMarkdownCacheEstimatedCost: preparedMarkdownCache.currentCost,
            preparedMarkdownCacheCostLimit: Self.preparedMarkdownCacheCostLimit,
            markdownParseCount: markdownParseCount,
            markdownLayoutCount: markdownLayoutCount,
            markdownWindowLayoutCount: markdownWindowLayoutCount,
            markdownSceneBuildCount: markdownSceneBuildCount,
            incrementalImageLayoutPassCount: incrementalImageLayoutPassCount,
            sceneWindowCacheEstimatedCost: sceneWindowCache.currentCost,
            sceneWindowCacheCostLimit: Self.sceneWindowCacheCostLimit
        )
    }

    public func renderedMessage(for message: VVChatMessage) -> VVChatRenderedMessage {
        let insets = style.insets(for: message.role)
        let presentation = message.presentation
        let leadingIconURL = normalizedAssetURL(presentation?.leadingIconURL)
        let hasLeadingIcon = leadingIconURL != nil
        let leadingIconSize = hasLeadingIcon ? max(8, presentation?.leadingIconSize ?? style.headerIconSize) : 0
        let leadingIconSpacing = hasLeadingIcon ? max(0, presentation?.leadingIconSpacing ?? style.headerIconSpacing) : 0
        let explicitLaneWidth = max(0, presentation?.leadingLaneWidth ?? 0)
        let implicitLaneWidth = hasLeadingIcon ? (leadingIconSize + leadingIconSpacing) : 0
        let leadingLaneWidth = max(explicitLaneWidth, implicitLaneWidth)
        let bubbleStyle = presentation?.bubbleStyle ?? style.bubbleStyle(for: message.role)
        let usesBubble = bubbleStyle != nil
        let bubbleInsets = bubbleStyle?.insets ?? VVInsets()
        let availableWidth = max(0, contentWidth - insets.left - insets.right - leadingLaneWidth)
        let maxBubbleWidth = bubbleStyle?.maxWidth ?? availableWidth
        let maxContentWidth = usesBubble ? min(availableWidth - bubbleInsets.left - bubbleInsets.right, maxBubbleWidth) : availableWidth
        let messageContentWidth = max(0, maxContentWidth)
        let widthKey = Self.widthKey(for: messageContentWidth)
        let isDraft = message.state == .draft
        let contentScale = normalizedContentScale(presentation?.contentFontScale)
        let contentScaleKey = Self.contentScaleKey(for: contentScale)
        let key = CacheKey(
            id: message.id,
            revision: message.revision,
            widthKey: widthKey,
            isDraft: isDraft,
            contentScaleKey: contentScaleKey
        )
        if let cached = cache.value(for: key) {
            return cached
        }

        let (layoutEngine, _) = contentResources(isDraft: isDraft, scale: contentScale)
        let customContent = message.customContent

        layoutEngine.updateImageSizeProvider { [weak self] url in
            self?.imageSizes[url]
        }
        layoutEngine.updateContentWidth(messageContentWidth)

        let contentLayoutTotalHeight: CGFloat?
        let contentBounds: CGRect?
        let contentMinX: CGFloat
        let contentMinY: CGFloat
        var imageURLs = Set<String>()
        let measuredWidth: CGFloat?
        let interactiveRegions: [VVChatInteractiveRegion]
        let contentSceneSource: ContentSceneSource

        if let customContent {
            markdownParseCount += 1
            markdownLayoutCount += 1
            let customRender = renderCustomContent(
                customContent,
                width: messageContentWidth,
                contentScale: contentScale
            )
            let contentSceneArtifacts = makeSceneArtifacts(customRender.scene)
            contentBounds = sceneBounds(for: customRender.scene, layoutEngine: layoutEngine)
            contentMinX = max(0, contentBounds?.minX ?? 0)
            contentMinY = min(0, contentBounds?.minY ?? 0)
            imageURLs = Set(customRender.imageURLs)
            measuredWidth = customRender.visualWidth
            interactiveRegions = customRender.interactiveRegions
            contentSceneSource = .staticScene(contentSceneArtifacts)
            contentLayoutTotalHeight = nil
        } else {
            let prepared = preparedMarkdownContent(
                for: message,
                key: key,
                layoutEngine: layoutEngine,
                requiresLayout: false
            )
            contentBounds = prepared.analysis.contentBounds
            contentMinX = max(0, prepared.analysis.contentBounds?.minX ?? 0)
            contentMinY = min(0, prepared.analysis.contentBounds?.minY ?? 0)
            imageURLs = prepared.analysis.imageURLs
            measuredWidth = usesBubble ? prepared.analysis.measuredWidth : nil
            interactiveRegions = []
            contentSceneSource = .markdown(key)
            contentLayoutTotalHeight = prepared.layout?.totalHeight
        }

        let bubbleWidthSource = measuredWidth ?? max(0, contentBounds?.width ?? 0)
        let bubbleContentWidth = usesBubble ? max(1, min(messageContentWidth, bubbleWidthSource > 0 ? bubbleWidthSource : messageContentWidth)) : messageContentWidth
        let shouldShowHeader = presentation?.showsHeader ?? style.showsHeader(for: message.role)
        let headerText = shouldShowHeader ? (presentation?.headerTitle ?? style.headerTitle(for: message.role)) : ""
        let headerIconURL = shouldShowHeader ? (presentation?.headerIconURL ?? style.headerIconURL(for: message.role)) : nil
        let headerHasIcon = (headerIconURL?.isEmpty == false)
        let headerIconFootprint: CGFloat
        if headerHasIcon {
            headerIconFootprint = max(8, style.headerIconSize) + max(0, style.headerIconSpacing)
        } else {
            headerIconFootprint = 0
        }
        let footerMetaFont: VVFont
        let footerText: String
        let footerSuffixTextForAction: String?
        let footerPrefixIconURL: String?
        let footerSuffixIconURL: String?
        let footerIconSize: CGFloat
        let footerIconSpacing: CGFloat

        if isDraft && message.role == .assistant {
            footerMetaFont = style.loadingIndicatorFont
            footerText = style.loadingIndicatorText
            footerSuffixTextForAction = nil
            footerPrefixIconURL = nil
            footerSuffixIconURL = nil
            footerIconSize = 0
            footerIconSpacing = 0
        } else if presentation?.showsTimestamp ?? style.showsTimestamp(for: message.role) {
            footerMetaFont = style.timestampFont
            footerPrefixIconURL = normalizedAssetURL(presentation?.timestampPrefixIconURL)
            footerSuffixIconURL = normalizedAssetURL(presentation?.timestampSuffixIconURL)
            let hasPrefixIcon = footerPrefixIconURL != nil
            let hasSuffixIcon = footerSuffixIconURL != nil
            let prefixText = hasPrefixIcon ? "" : (presentation?.timestampPrefix ?? "")
            let suffixText = hasSuffixIcon ? "" : (presentation?.timestampSuffix ?? style.timestampSuffix(for: message.role))
            footerText = prefixText + timestampCoreLabel(for: message) + suffixText
            footerSuffixTextForAction = hasSuffixIcon ? nil : suffixText
            footerIconSize = max(10, presentation?.timestampIconSize ?? ceil(footerMetaFont.pointSize))
            footerIconSpacing = max(0, presentation?.timestampIconSpacing ?? 5)
        } else {
            footerMetaFont = style.timestampFont
            footerText = ""
            footerSuffixTextForAction = nil
            footerPrefixIconURL = normalizedAssetURL(presentation?.timestampPrefixIconURL)
            footerSuffixIconURL = normalizedAssetURL(presentation?.timestampSuffixIconURL)
            let hasFooterIconOnlyAction = footerPrefixIconURL != nil || footerSuffixIconURL != nil
            footerIconSize = hasFooterIconOnlyAction ? max(10, presentation?.timestampIconSize ?? ceil(footerMetaFont.pointSize)) : 0
            footerIconSpacing = hasFooterIconOnlyAction ? max(0, presentation?.timestampIconSpacing ?? 5) : 0
        }

        let footerTextWidth = footerText.isEmpty ? 0 : Self.singleLineMetaWidth(footerText, font: footerMetaFont)
        let hasFooterPrefixIcon = footerPrefixIconURL != nil
        let hasFooterSuffixIcon = footerSuffixIconURL != nil
        let hasFooterText = footerTextWidth > 0
        let prefixIconFootprint = hasFooterPrefixIcon ? (footerIconSize + (hasFooterText ? footerIconSpacing : 0)) : 0
        let suffixIconFootprint = hasFooterSuffixIcon ? ((hasFooterText ? footerIconSpacing : 0) + footerIconSize) : 0
        let footerRowWidth = footerTextWidth + prefixIconFootprint + suffixIconFootprint
        let footerRequiredWidth = footerRowWidth
        if let footerPrefixIconURL {
            imageURLs.insert(footerPrefixIconURL)
        }
        if let footerSuffixIconURL {
            imageURLs.insert(footerSuffixIconURL)
        }

        let headerTrailingIconURL = shouldShowHeader ? normalizedAssetURL(presentation?.headerTrailingIconURL) : nil
        let headerTrailingHasIcon = (headerTrailingIconURL?.isEmpty == false)
        let headerTrailingIconFootprint: CGFloat = headerTrailingHasIcon ? (max(8, style.headerIconSize) + max(0, style.headerIconSpacing)) : 0
        let headerBadgesWidth: CGFloat = {
            guard let badges = presentation?.headerBadges, !badges.isEmpty else { return 0 }
            let spacing: CGFloat = 6
            return badges.reduce(CGFloat(0)) { sum, badge in
                sum + spacing + Self.singleLineMetaWidth(badge.text, font: style.headerFont)
            }
        }()
        let headerRequiredWidth = headerText.isEmpty ? 0 : (Self.singleLineMetaWidth(headerText, font: style.headerFont) + headerIconFootprint + headerTrailingIconFootprint + headerBadgesWidth)
        let preferredMetaWidth = max(style.bubbleMetadataMinWidth, headerRequiredWidth, footerRequiredWidth)
        let clampedMetaWidth = max(1, min(messageContentWidth, preferredMetaWidth))
        let metaWidth = usesBubble ? max(bubbleContentWidth, clampedMetaWidth) : messageContentWidth

        let headerRender: HeaderRender?
        if headerText.isEmpty {
            headerRender = nil
        } else {
            headerRender = renderHeader(text: headerText, iconURL: headerIconURL, trailingIconURL: headerTrailingIconURL, badges: presentation?.headerBadges, width: metaWidth)
            headerRender?.imageURLs.forEach { imageURLs.insert($0) }
        }

        let footerRender: (layout: MarkdownLayout, scene: VVScene)?
        let footerLayoutEngineForBounds: MarkdownLayoutEngine
        if isDraft && message.role == .assistant {
            footerRender = renderMeta(text: footerText, layoutEngine: loadingLayoutEngine, pipeline: loadingPipeline, width: metaWidth)
            footerLayoutEngineForBounds = loadingLayoutEngine
        } else if footerText.isEmpty {
            footerRender = nil
            footerLayoutEngineForBounds = timestampLayoutEngine
        } else {
            footerRender = renderMeta(text: footerText, layoutEngine: timestampLayoutEngine, pipeline: timestampPipeline, width: metaWidth)
            footerLayoutEngineForBounds = timestampLayoutEngine
        }

        let headerHeight = headerRender?.height ?? 0
        let contentHeight = max(1, contentBounds?.height ?? contentLayoutTotalHeight ?? 1)
        let footerTextHeight = footerRender?.layout.totalHeight ?? 0
        let footerHeight = max(footerTextHeight, (hasFooterPrefixIcon || hasFooterSuffixIcon) ? footerIconSize : 0)
        let headerBlockHeight = headerHeight > 0 ? headerHeight + style.headerSpacing : 0
        let footerBlockHeight = footerHeight > 0 ? style.footerSpacing + footerHeight : 0
        let contentBlockHeight = usesBubble
            ? (bubbleInsets.top + contentHeight + bubbleInsets.bottom)
            : contentHeight
        let bubbleWidth = usesBubble ? (bubbleContentWidth + bubbleInsets.left + bubbleInsets.right) : 0
        let contentStartY = headerBlockHeight
        var messageHeight = headerBlockHeight + contentBlockHeight + footerBlockHeight
        if hasLeadingIcon {
            messageHeight = max(messageHeight, contentStartY + leadingIconSize)
        }

        var builder = VVSceneBuilder()
        var footerTrailingActionFrame: CGRect?
        var selectionContentOffset: CGPoint = .zero
        var currentY: CGFloat = 0
        if let headerRender, headerHeight > 0 {
            builder.add(node: VVNode.fromScene(headerRender.scene))
            currentY += headerHeight + style.headerSpacing
        }

        if let bubbleStyle {
            let bubbleFrame = CGRect(x: 0, y: currentY, width: bubbleWidth, height: contentBlockHeight)
            if bubbleStyle.borderWidth > 0, bubbleStyle.borderColor.w > 0 {
                let borderFrame = bubbleFrame.insetBy(dx: -bubbleStyle.borderWidth, dy: -bubbleStyle.borderWidth)
                let border = VVQuadPrimitive(
                    frame: borderFrame,
                    color: bubbleStyle.borderColor,
                    cornerRadius: bubbleStyle.cornerRadius + bubbleStyle.borderWidth
                )
                builder.add(kind: .quad(border), zIndex: -2)
            }
            let bubble = VVQuadPrimitive(
                frame: bubbleFrame,
                color: bubbleStyle.color,
                cornerRadius: bubbleStyle.cornerRadius
            )
            builder.add(kind: .quad(bubble), zIndex: -1)
            let contentOffsetX = bubbleInsets.left - contentMinX
            let contentOffsetY = currentY + bubbleInsets.top - contentMinY
            selectionContentOffset = CGPoint(x: contentOffsetX, y: contentOffsetY)
        } else {
            let contentOffsetX = -contentMinX
            let contentOffsetY = currentY - contentMinY
            selectionContentOffset = CGPoint(x: contentOffsetX, y: contentOffsetY)
        }

        currentY += contentBlockHeight
        if footerHeight > 0 {
            currentY += style.footerSpacing
            let footerBounds: CGRect?
            if let footerRender {
                footerBounds = sceneBounds(for: footerRender.scene, layoutEngine: footerLayoutEngineForBounds)
            } else {
                footerBounds = nil
            }
            let footerMinX = footerBounds?.minX ?? 0
            let footerMinY = footerBounds?.minY ?? 0
            let footerVisualTextHeight = max(1, footerBounds?.height ?? footerTextHeight)
            let footerOffsetX: CGFloat
            if message.role == .user {
                let footerRowContainerWidth = usesBubble ? bubbleWidth : metaWidth
                footerOffsetX = max(0, footerRowContainerWidth - footerRowWidth)
            } else {
                footerOffsetX = 0
            }

            var rowCursorX = footerOffsetX
            let iconY = currentY + max(0, (footerHeight - footerIconSize) * 0.5)

            if let footerPrefixIconURL {
                let icon = VVImagePrimitive(
                    url: footerPrefixIconURL,
                    frame: CGRect(x: rowCursorX, y: iconY, width: footerIconSize, height: footerIconSize),
                    cornerRadius: 0
                )
                builder.add(kind: .image(icon), zIndex: 0)
                rowCursorX += footerIconSize
                if hasFooterText {
                    rowCursorX += footerIconSpacing
                }
            }

            if let footerRender, hasFooterText {
                let textOffsetY = currentY + max(0, (footerHeight - footerVisualTextHeight) * 0.5) - footerMinY
                builder.withOffset(CGPoint(x: rowCursorX - footerMinX, y: textOffsetY)) { builder in
                    builder.add(node: VVNode.fromScene(footerRender.scene))
                }
                rowCursorX += footerTextWidth
            }

            if let footerSuffixIconURL {
                if hasFooterText {
                    rowCursorX += footerIconSpacing
                }
                let iconX = rowCursorX
                let icon = VVImagePrimitive(
                    url: footerSuffixIconURL,
                    frame: CGRect(x: iconX, y: iconY, width: footerIconSize, height: footerIconSize),
                    cornerRadius: 0
                )
                builder.add(kind: .image(icon), zIndex: 0)

                if message.role == .user || message.role == .assistant {
                    let hitPaddingX: CGFloat = 6
                    let hitPaddingY: CGFloat = 3
                    let actionWidth = max(20, footerIconSize + hitPaddingX * 2)
                    let actionHeight = max(18, footerIconSize + hitPaddingY * 2)
                    footerTrailingActionFrame = CGRect(
                        x: iconX - hitPaddingX,
                        y: iconY - hitPaddingY,
                        width: actionWidth,
                        height: actionHeight
                    )
                }
            } else if message.role == .user || message.role == .assistant,
                      let suffix = footerSuffixTextForAction?.trimmingCharacters(in: .whitespacesAndNewlines),
                      !suffix.isEmpty {
                let suffixWidth = max(10, Self.singleLineMetaWidth(suffix, font: footerMetaFont))
                let hitPaddingX: CGFloat = 6
                let hitPaddingY: CGFloat = 3
                let actionWidth = max(18, suffixWidth + hitPaddingX * 2)
                let actionHeight = max(16, footerVisualTextHeight + hitPaddingY * 2)
                let textOffsetY = currentY + max(0, (footerHeight - footerVisualTextHeight) * 0.5)
                let actionX = footerOffsetX + max(0, footerRowWidth - suffixWidth) - hitPaddingX
                let actionY = textOffsetY + footerMinY - hitPaddingY
                footerTrailingActionFrame = CGRect(x: actionX, y: actionY, width: actionWidth, height: actionHeight)
            }
        }

        let baseChromeScene = builder.scene
        let chromeScene: VVScene
        var adjustedInteractiveRegions = interactiveRegions.map { region in
            VVChatInteractiveRegion(
                id: region.id,
                frame: region.frame.offsetBy(dx: selectionContentOffset.x, dy: selectionContentOffset.y),
                action: region.action,
                hoverFillColor: region.hoverFillColor,
                cornerRadius: region.cornerRadius
            )
        }
        if leadingLaneWidth > 0 {
            var laneBuilder = VVSceneBuilder()
            if hasLeadingIcon, let leadingIconURL {
                if !leadingIconURL.isEmpty {
                    imageURLs.insert(leadingIconURL)
                }
                let icon = VVImagePrimitive(
                    url: leadingIconURL,
                    frame: CGRect(x: 0, y: contentStartY, width: leadingIconSize, height: leadingIconSize),
                    cornerRadius: 0
                )
                laneBuilder.add(kind: .image(icon), zIndex: 0)
            }
            laneBuilder.withOffset(CGPoint(x: leadingLaneWidth, y: 0)) { builder in
                builder.add(node: VVNode.fromScene(baseChromeScene))
            }
            selectionContentOffset.x += leadingLaneWidth
            if var actionFrame = footerTrailingActionFrame {
                actionFrame.origin.x += leadingLaneWidth
                footerTrailingActionFrame = actionFrame
            }
            adjustedInteractiveRegions = adjustedInteractiveRegions.map { region in
                VVChatInteractiveRegion(
                    id: region.id,
                    frame: region.frame.offsetBy(dx: leadingLaneWidth, dy: 0),
                    action: region.action,
                    hoverFillColor: region.hoverFillColor,
                    cornerRadius: region.cornerRadius
                )
            }
            chromeScene = laneBuilder.scene
        } else {
            chromeScene = builder.scene
        }

        let topOverflow = max(0, -(contentBounds?.minY ?? 0))
        let height = messageHeight + topOverflow + insets.top + insets.bottom

        let bubbleOffsetX: CGFloat
        if let bubbleStyle {
            switch bubbleStyle.alignment {
            case .leading:
                bubbleOffsetX = 0
            case .center:
                bubbleOffsetX = max(0, (availableWidth - bubbleWidth) / 2)
            case .trailing:
                bubbleOffsetX = max(0, availableWidth - bubbleWidth)
            }
        } else {
            bubbleOffsetX = 0
        }
        let chromeOrderedPrimitiveIndices = chromeScene.orderedPrimitiveIndices()
        let rendered = VVChatRenderedMessage(
            id: message.id,
            revision: message.revision,
            chromeScene: chromeScene,
            chromeOrderedPrimitiveIndices: chromeOrderedPrimitiveIndices,
            chromeVisibilityIndex: VVPrimitiveVisibilityIndex(
                scene: chromeScene,
                orderedPrimitiveIndices: chromeOrderedPrimitiveIndices,
                bucketHeight: 192
            ),
            height: height,
            contentOffset: CGPoint(x: insets.left + bubbleOffsetX, y: insets.top + topOverflow),
            selectionContentOffset: selectionContentOffset,
            isDraft: isDraft,
            imageURLs: Array(imageURLs),
            footerTrailingActionFrame: footerTrailingActionFrame,
            interactiveRegions: adjustedInteractiveRegions,
            contentSceneSource: contentSceneSource
        )
        cache.set(rendered, for: key)
        return rendered
    }

    func selectionHelper(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage
    ) -> VVMarkdownSelectionHelper? {
        switch rendered.contentSceneSource {
        case .none, .staticScene:
            return nil
        case .markdown(let key):
            let contentScale = normalizedContentScale(message.presentation?.contentFontScale)
            let (layoutEngine, _) = contentResources(isDraft: message.state == .draft, scale: contentScale)
            let prepared = preparedMarkdownContent(
                for: message,
                key: key,
                layoutEngine: layoutEngine,
                requiresLayout: false
            )
            let layout = materializedPreparedMarkdownLayout(
                from: prepared,
                layoutEngine: layoutEngine
            )
            return VVMarkdownSelectionHelper(layout: layout, layoutEngine: layoutEngine)
        }
    }

    private func preparedMarkdownContent(
        for message: VVChatMessage,
        key: CacheKey,
        layoutEngine: MarkdownLayoutEngine,
        requiresLayout: Bool
    ) -> PreparedMarkdownContent {
        if var cached = preparedMarkdownCache.value(for: key) {
            preparedMarkdownCacheHits += 1
            let didRefresh = refreshPreparedMarkdownContentIfNeeded(
                &cached,
                layoutEngine: layoutEngine,
                keepMaterializedLayout: requiresLayout
            )
            let didMaterialize = ensurePreparedMarkdownLayoutIfNeeded(
                &cached,
                layoutEngine: layoutEngine,
                requiresLayout: requiresLayout
            )
            if didRefresh || didMaterialize {
                preparedMarkdownCache.set(cached, for: key)
                dematerializePreparedLayoutsIfNeeded(excluding: requiresLayout ? key : nil)
            }
            return cached
        }

        preparedMarkdownCacheMisses += 1
        markdownParseCount += 1
        let document = parser.parse(message.content)
        markdownLayoutCount += 1
        var layout = layoutEngine.layout(document)
        applyKnownImageSizes(to: &layout, layoutEngine: layoutEngine)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)
        let analysis = analyzePreparedMarkdownLayout(layout, document: document)

        let prepared = PreparedMarkdownContent(
            document: document,
            layout: requiresLayout ? layout : nil,
            analysis: analysis,
            appliedImageSizes: currentAppliedImageSizes(for: analysis.imageURLs)
        )
        preparedMarkdownCache.set(prepared, for: key)
        dematerializePreparedLayoutsIfNeeded(excluding: requiresLayout ? key : nil)
        return prepared
    }

    private func refreshPreparedMarkdownContentIfNeeded(
        _ prepared: inout PreparedMarkdownContent,
        layoutEngine: MarkdownLayoutEngine,
        keepMaterializedLayout: Bool
    ) -> Bool {
        guard prepared.layout != nil else {
            return refreshPreparedMarkdownContentByRelayout(
                &prepared,
                layoutEngine: layoutEngine,
                keepMaterializedLayout: keepMaterializedLayout
            )
        }
        guard !prepared.analysis.directImageBlockIDsByURL.isEmpty || !prepared.analysis.imageRowBlockIDsByURL.isEmpty else {
            return refreshPreparedMarkdownContentByRelayout(
                &prepared,
                layoutEngine: layoutEngine,
                keepMaterializedLayout: keepMaterializedLayout
            )
        }

        var directBlockIDs = Set<String>()
        var imageRowBlockIDs = Set<String>()
        var nextAppliedImageSizes = prepared.appliedImageSizes
        var changedURLs = Set<String>()
        var coveredURLs = Set<String>()

        for url in prepared.analysis.imageURLs {
            let currentSize = imageSizes[url]
            if prepared.appliedImageSizes[url] == currentSize {
                continue
            }
            changedURLs.insert(url)

            if let currentSize {
                nextAppliedImageSizes[url] = currentSize
            } else {
                nextAppliedImageSizes.removeValue(forKey: url)
            }

            if let blockIDs = prepared.analysis.directImageBlockIDsByURL[url] {
                directBlockIDs.formUnion(blockIDs)
                coveredURLs.insert(url)
            }
            if let blockIDs = prepared.analysis.imageRowBlockIDsByURL[url] {
                imageRowBlockIDs.formUnion(blockIDs)
                coveredURLs.insert(url)
            }
        }

        guard !changedURLs.isEmpty else {
            return false
        }

        if coveredURLs != changedURLs {
            return refreshPreparedMarkdownContentByRelayout(
                &prepared,
                layoutEngine: layoutEngine,
                keepMaterializedLayout: keepMaterializedLayout
            )
        }

        guard !directBlockIDs.isEmpty || !imageRowBlockIDs.isEmpty else {
            return refreshPreparedMarkdownContentByRelayout(
                &prepared,
                layoutEngine: layoutEngine,
                keepMaterializedLayout: keepMaterializedLayout
            )
        }

        incrementalImageLayoutPassCount += 1
        guard var layout = prepared.layout else { return false }
        applyImageSizeUpdates(
            to: &layout,
            directImageBlockIDs: directBlockIDs,
            imageRowBlockIDs: imageRowBlockIDs,
            layoutEngine: layoutEngine
        )
        layoutEngine.adjustParagraphImageSpacing(in: &layout)
        let analysis = analyzePreparedMarkdownLayout(layout, document: prepared.document)

        prepared.layout = keepMaterializedLayout ? layout : nil
        prepared.analysis = analysis
        prepared.appliedImageSizes = nextAppliedImageSizes
        return true
    }

    private func refreshPreparedMarkdownContentByRelayout(
        _ prepared: inout PreparedMarkdownContent,
        layoutEngine: MarkdownLayoutEngine,
        keepMaterializedLayout: Bool
    ) -> Bool {
        var hasChangedImageSize = false
        for url in prepared.analysis.imageURLs {
            let currentSize = imageSizes[url]
            if prepared.appliedImageSizes[url] != currentSize {
                hasChangedImageSize = true
                break
            }
        }
        guard hasChangedImageSize else { return false }

        markdownLayoutCount += 1
        var layout = layoutEngine.layout(prepared.document)
        applyKnownImageSizes(to: &layout, layoutEngine: layoutEngine)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)
        let analysis = analyzePreparedMarkdownLayout(layout, document: prepared.document)

        prepared.layout = keepMaterializedLayout ? layout : nil
        prepared.analysis = analysis
        prepared.appliedImageSizes = currentAppliedImageSizes(for: analysis.imageURLs)
        return true
    }

    private func ensurePreparedMarkdownLayoutIfNeeded(
        _ prepared: inout PreparedMarkdownContent,
        layoutEngine: MarkdownLayoutEngine,
        requiresLayout: Bool
    ) -> Bool {
        guard requiresLayout, prepared.layout == nil else { return false }
        markdownLayoutCount += 1
        var layout = layoutEngine.layout(prepared.document)
        applyKnownImageSizes(to: &layout, layoutEngine: layoutEngine)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)
        let analysis = analyzePreparedMarkdownLayout(layout, document: prepared.document)
        prepared.layout = layout
        prepared.analysis = analysis
        prepared.appliedImageSizes = currentAppliedImageSizes(for: analysis.imageURLs)
        return true
    }

    private func partialPreparedMarkdownLayout(
        from prepared: PreparedMarkdownContent,
        blockRange: Range<Int>,
        layoutEngine: MarkdownLayoutEngine
    ) -> MarkdownLayout {
        let sourceBlockIndexes = Array(prepared.analysis.sourceBlockIndexes[blockRange])
        let blockYPositions = Array(prepared.analysis.blockFrameMinY[blockRange])
        markdownWindowLayoutCount += 1
        return layoutEngine.layout(
            prepared.document,
            sourceBlockIndexes: sourceBlockIndexes,
            at: blockYPositions,
            totalHeight: prepared.analysis.totalHeight
        )
    }

    private func materializedPreparedMarkdownLayout(
        from prepared: PreparedMarkdownContent,
        layoutEngine: MarkdownLayoutEngine
    ) -> MarkdownLayout {
        if let layout = prepared.layout {
            return layout
        }
        markdownLayoutCount += 1
        var layout = layoutEngine.layout(prepared.document)
        applyKnownImageSizes(to: &layout, layoutEngine: layoutEngine)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)
        return layout
    }

    private func applyKnownImageSizes(
        to layout: inout MarkdownLayout,
        layoutEngine: MarkdownLayoutEngine
    ) {
        guard !imageSizes.isEmpty else { return }

        for block in layout.blocks {
            switch block.content {
            case .image(let url, _, _):
                guard let size = imageSizes[url] else { continue }
                layoutEngine.updateImageLayout(in: &layout, blockId: block.blockId, imageSize: size)
            case .inline(let runs, let images) where runs.isEmpty && images.count == 1:
                let image = images[0]
                guard let size = imageSizes[image.url] else { continue }
                layoutEngine.updateImageLayout(in: &layout, blockId: block.blockId, imageSize: size)
            case .imageRow(let images):
                let hasKnownImage = images.contains { imageSizes[$0.url] != nil }
                guard hasKnownImage else { continue }
                layoutEngine.updateInlineImageRowLayout(in: &layout, blockId: block.blockId, imageSizes: imageSizes)
            default:
                continue
            }
        }
    }

    private func applyImageSizeUpdates(
        to layout: inout MarkdownLayout,
        directImageBlockIDs: Set<String>,
        imageRowBlockIDs: Set<String>,
        layoutEngine: MarkdownLayoutEngine
    ) {
        guard !directImageBlockIDs.isEmpty || !imageRowBlockIDs.isEmpty else { return }

        for block in layout.blocks {
            if directImageBlockIDs.contains(block.blockId) {
                switch block.content {
                case .image(let url, _, _):
                    guard let size = imageSizes[url] else { break }
                    layoutEngine.updateImageLayout(in: &layout, blockId: block.blockId, imageSize: size)
                case .inline(let runs, let images) where runs.isEmpty && images.count == 1:
                    let image = images[0]
                    guard let size = imageSizes[image.url] else { break }
                    layoutEngine.updateImageLayout(in: &layout, blockId: block.blockId, imageSize: size)
                default:
                    break
                }
            }

            if imageRowBlockIDs.contains(block.blockId) {
                layoutEngine.updateInlineImageRowLayout(in: &layout, blockId: block.blockId, imageSizes: imageSizes)
            }
        }
    }

    private func buildPreparedMarkdownScene(
        from layout: MarkdownLayout,
        blockRange: Range<Int>,
        for message: VVChatMessage,
        pipeline: VVMarkdownRenderPipeline
    ) -> VVScene {
        markdownSceneBuildCount += 1
        var scene = pipeline.buildScene(from: layout, blockRange: blockRange)
        if let opacityMultiplier = message.presentation?.textOpacityMultiplier {
            scene = applyingTextOpacity(to: scene, multiplier: opacityMultiplier)
        }
        if let prefixColor = message.presentation?.prefixGlyphColor {
            let glyphCount = max(0, message.presentation?.prefixGlyphCount ?? 0)
            if glyphCount > 0 {
                scene = applyingPrefixGlyphColor(
                    to: scene,
                    color: prefixColor,
                    glyphCount: glyphCount
                )
            }
        }
        return scene
    }

    private func currentAppliedImageSizes(for urls: Set<String>) -> [String: CGSize] {
        var applied: [String: CGSize] = [:]
        applied.reserveCapacity(urls.count)
        for url in urls {
            if let size = imageSizes[url] {
                applied[url] = size
            }
        }
        return applied
    }

    func contentSceneArtifacts(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSceneArtifacts? {
        switch rendered.contentSceneSource {
        case .none:
            return nil
        case .staticScene(let contentArtifacts):
            return contentArtifacts
        case .markdown(let key):
            let (layoutEngine, pipeline) = contentResources(
                isDraft: message.state == .draft,
                scale: normalizedContentScale(message.presentation?.contentFontScale)
            )
            let prepared = preparedMarkdownContent(
                for: message,
                key: key,
                layoutEngine: layoutEngine,
                requiresLayout: false
            )
            let blockRange = visibleMarkdownBlockRange(
                in: visibleRect?.offsetBy(dx: -rendered.selectionContentOffset.x, dy: -rendered.selectionContentOffset.y),
                analysis: prepared.analysis
            )
            let windowKey = SceneWindowCacheKey(
                key: key,
                startBlock: blockRange.lowerBound,
                endBlock: blockRange.upperBound
            )
            if let cached = sceneWindowCache.value(for: windowKey) {
                return cached
            }

            let contentScene: VVScene
            if blockRange.isEmpty {
                contentScene = VVScene()
            } else if let layout = prepared.layout {
                contentScene = buildPreparedMarkdownScene(
                    from: layout,
                    blockRange: blockRange,
                    for: message,
                    pipeline: pipeline
                )
            } else {
                let partialLayout = partialPreparedMarkdownLayout(
                    from: prepared,
                    blockRange: blockRange,
                    layoutEngine: layoutEngine
                )
                contentScene = buildPreparedMarkdownScene(
                    from: partialLayout,
                    blockRange: partialLayout.blocks.indices,
                    for: message,
                    pipeline: pipeline
                )
            }

            let artifacts = makeSceneArtifacts(contentScene)
            sceneWindowCache.set(artifacts, for: windowKey)
            return artifacts
        }
    }

    func sceneArtifacts(
        for message: VVChatMessage,
        rendered: VVChatRenderedMessage,
        visibleRect: CGRect?
    ) -> VVChatSceneArtifacts {
        guard let contentArtifacts = contentSceneArtifacts(for: message, rendered: rendered, visibleRect: visibleRect) else {
            return makeSceneArtifacts(rendered.chromeScene)
        }
        return combineSceneArtifacts(
            chromeScene: rendered.chromeScene,
            contentScene: contentArtifacts.scene,
            contentOffset: rendered.selectionContentOffset
        )
    }

    private func analyzePreparedMarkdownLayout(
        _ layout: MarkdownLayout,
        document: ParsedMarkdownDocument
    ) -> PreparedMarkdownLayoutAnalysis {
        var imageURLs = Set<String>()
        var maxX: CGFloat = 0
        var hasMeasuredWidth = false
        var blockFrameMinY: [CGFloat] = []
        var blockMinY: [CGFloat] = []
        var blockMaxY: [CGFloat] = []
        var sourceBlockIndexes: [Int] = []
        var directImageBlockIDsByURL: [String: [String]] = [:]
        var imageRowBlockIDsByURL: [String: [String]] = [:]
        var bounds = CGRect.null
        var estimatedCost = 0
        let sourceIndexByBlockID = Dictionary(uniqueKeysWithValues: document.blocks.enumerated().map { ($0.element.id, $0.offset) })

        for block in layout.blocks {
            let (blockMaxX, blockHasValue) = measuredMaxX(for: block)
            if blockHasValue {
                maxX = max(maxX, blockMaxX)
                hasMeasuredWidth = true
            }
            let blockBounds = layoutBounds(for: block) ?? block.frame
            blockFrameMinY.append(block.frame.minY)
            blockMinY.append(blockBounds.minY)
            blockMaxY.append(blockBounds.maxY)
            sourceBlockIndexes.append(sourceIndexByBlockID[block.blockId] ?? sourceBlockIndexes.count)
            bounds = bounds.union(blockBounds)
            estimatedCost += estimatedLayoutCost(for: block)

            switch block.content {
            case .image(let url, _, _):
                imageURLs.insert(url)
                directImageBlockIDsByURL[url, default: []].append(block.blockId)
            case .inline(let runs, let images):
                for image in images {
                    imageURLs.insert(image.url)
                }
                if runs.isEmpty, images.count == 1 {
                    directImageBlockIDsByURL[images[0].url, default: []].append(block.blockId)
                }
            case .imageRow(let images):
                for image in images {
                    imageURLs.insert(image.url)
                    imageRowBlockIDsByURL[image.url, default: []].append(block.blockId)
                }
            case .listItems(let items):
                for item in items {
                    collectImageURLs(from: item, into: &imageURLs)
                }
            case .quoteBlocks(let blocks):
                for nested in blocks {
                    collectImageURLs(from: nested, into: &imageURLs)
                }
            case .tableRows(let rows):
                for row in rows {
                    for cell in row.cells {
                        for image in cell.inlineImages {
                            imageURLs.insert(image.url)
                        }
                    }
                }
            case .definitionList(let items):
                for item in items {
                    for image in item.termImages {
                        imageURLs.insert(image.url)
                    }
                    for definitionImages in item.definitionImages {
                        for image in definitionImages {
                            imageURLs.insert(image.url)
                        }
                    }
                }
            case .abbreviationList(let items):
                for item in items {
                    for image in item.images {
                        imageURLs.insert(image.url)
                    }
                }
            default:
                break
            }
        }

        return PreparedMarkdownLayoutAnalysis(
            imageURLs: imageURLs,
            measuredWidth: hasMeasuredWidth ? maxX : nil,
            contentBounds: bounds.isNull ? nil : bounds,
            estimatedCost: max(estimatedCost, 1),
            totalHeight: layout.totalHeight,
            blockFrameMinY: blockFrameMinY,
            blockMinY: blockMinY,
            blockMaxY: blockMaxY,
            sourceBlockIndexes: sourceBlockIndexes,
            directImageBlockIDsByURL: directImageBlockIDsByURL,
            imageRowBlockIDsByURL: imageRowBlockIDsByURL
        )
    }

    private func visibleMarkdownBlockRange(
        in visibleRect: CGRect?,
        analysis: PreparedMarkdownLayoutAnalysis
    ) -> Range<Int> {
        let count = analysis.blockMinY.count
        guard count > 0 else { return 0..<0 }
        guard let visibleRect else { return 0..<count }

        let padding: CGFloat = 640
        let minY = visibleRect.minY - padding
        let maxY = visibleRect.maxY + padding

        var lower = 0
        var upper = count
        while lower < upper {
            let mid = (lower + upper) / 2
            if analysis.blockMaxY[mid] < minY {
                lower = mid + 1
            } else {
                upper = mid
            }
        }
        let start = lower

        lower = 0
        upper = count
        while lower < upper {
            let mid = (lower + upper) / 2
            if analysis.blockMinY[mid] <= maxY {
                lower = mid + 1
            } else {
                upper = mid
            }
        }
        let end = max(start, lower)
        return start..<end
    }

    private func combineSceneArtifacts(
        chromeScene: VVScene,
        contentScene: VVScene,
        contentOffset: CGPoint
    ) -> VVChatSceneArtifacts {
        var builder = VVSceneBuilder()
        builder.add(node: VVNode.fromScene(chromeScene))
        if !contentScene.primitives.isEmpty {
            builder.withOffset(contentOffset) { builder in
                builder.add(node: VVNode.fromScene(contentScene))
            }
        }
        return makeSceneArtifacts(builder.scene)
    }

    private func makeSceneArtifacts(_ scene: VVScene) -> VVChatSceneArtifacts {
        let orderedPrimitiveIndices = scene.orderedPrimitiveIndices()
        return VVChatSceneArtifacts(
            scene: scene,
            orderedPrimitiveIndices: orderedPrimitiveIndices,
            visibilityIndex: VVPrimitiveVisibilityIndex(
                scene: scene,
                orderedPrimitiveIndices: orderedPrimitiveIndices,
                bucketHeight: 192
            )
        )
    }

    private func layoutBounds(for block: LayoutBlock) -> CGRect? {
        switch block.content {
        case .text(let runs):
            return layoutBounds(for: runs, images: [])
        case .inline(let runs, let images):
            return layoutBounds(for: runs, images: images)
        case .imageRow(let images):
            return layoutBounds(for: images)
        case .image:
            return block.frame
        case .code, .diff, .thematicBreak, .math, .mermaid:
            return block.frame
        case .listItems(let items):
            return layoutBounds(for: items)
        case .quoteBlocks(let blocks):
            return layoutBounds(for: blocks)?.union(block.frame) ?? block.frame
        case .tableRows(let rows):
            return layoutBounds(for: rows)?.union(block.frame) ?? block.frame
        case .definitionList(let items):
            return layoutBounds(for: items)?.union(block.frame) ?? block.frame
        case .abbreviationList(let items):
            return layoutBounds(for: items)?.union(block.frame) ?? block.frame
        }
    }

    private func layoutBounds(for blocks: [LayoutBlock]) -> CGRect? {
        var bounds = CGRect.null
        for block in blocks {
            if let blockBounds = layoutBounds(for: block) {
                bounds = bounds.union(blockBounds)
            }
        }
        return bounds.isNull ? nil : bounds
    }

    private func layoutBounds(for rows: [LayoutTableRow]) -> CGRect? {
        var bounds = CGRect.null
        for row in rows {
            bounds = bounds.union(row.frame)
            for cell in row.cells {
                bounds = bounds.union(cell.frame)
                if let cellBounds = layoutBounds(for: cell.textRuns, images: cell.inlineImages) {
                    bounds = bounds.union(cellBounds)
                }
            }
        }
        return bounds.isNull ? nil : bounds
    }

    private func layoutBounds(for items: [LayoutListItem]) -> CGRect? {
        var bounds = CGRect.null
        for item in items {
            if let itemBounds = layoutBounds(for: item) {
                bounds = bounds.union(itemBounds)
            }
        }
        return bounds.isNull ? nil : bounds
    }

    private func layoutBounds(for item: LayoutListItem) -> CGRect? {
        var bounds = CGRect.null
        let bulletSize: CGFloat = 10
        bounds = bounds.union(
            CGRect(
                x: item.bulletPosition.x,
                y: item.bulletPosition.y - bulletSize * 0.5,
                width: bulletSize,
                height: bulletSize
            )
        )
        if let textBounds = layoutBounds(for: item.contentRuns, images: item.inlineImages) {
            bounds = bounds.union(textBounds)
        }
        if let childBounds = layoutBounds(for: item.children) {
            bounds = bounds.union(childBounds)
        }
        return bounds.isNull ? nil : bounds
    }

    private func layoutBounds(for items: [LayoutDefinitionItem]) -> CGRect? {
        var bounds = CGRect.null
        for item in items {
            if let termBounds = layoutBounds(for: item.termRuns, images: item.termImages) {
                bounds = bounds.union(termBounds)
            }
            for (index, runs) in item.definitionRuns.enumerated() {
                let images = index < item.definitionImages.count ? item.definitionImages[index] : []
                if let definitionBounds = layoutBounds(for: runs, images: images) {
                    bounds = bounds.union(definitionBounds)
                }
            }
        }
        return bounds.isNull ? nil : bounds
    }

    private func layoutBounds(for items: [LayoutAbbreviationItem]) -> CGRect? {
        var bounds = CGRect.null
        for item in items {
            if let itemBounds = layoutBounds(for: item.runs, images: item.images) {
                bounds = bounds.union(itemBounds)
            }
        }
        return bounds.isNull ? nil : bounds
    }

    private func layoutBounds(for runs: [LayoutTextRun], images: [LayoutInlineImage]) -> CGRect? {
        var bounds = CGRect.null
        for run in runs {
            if let runBounds = layoutBounds(for: run) {
                bounds = bounds.union(runBounds)
            }
        }
        if let imageBounds = layoutBounds(for: images) {
            bounds = bounds.union(imageBounds)
        }
        return bounds.isNull ? nil : bounds
    }

    private func layoutBounds(for run: LayoutTextRun) -> CGRect? {
        guard !run.glyphs.isEmpty else { return nil }
        var bounds = CGRect.null
        for glyph in run.glyphs where glyph.color.w > 0 {
            let rect = CGRect(
                x: glyph.position.x,
                y: glyph.position.y - glyph.size.height,
                width: glyph.size.width,
                height: glyph.size.height * 1.5
            )
            bounds = bounds.union(rect)
        }
        return bounds.isNull ? nil : bounds
    }

    private func layoutBounds(for images: [LayoutInlineImage]) -> CGRect? {
        var bounds = CGRect.null
        for image in images {
            bounds = bounds.union(image.frame)
        }
        return bounds.isNull ? nil : bounds
    }

    private func estimatedLayoutCost(for block: LayoutBlock) -> Int {
        var cost = 160
        switch block.content {
        case .text(let runs):
            cost += estimatedLayoutCost(for: runs, images: [])
        case .inline(let runs, let images):
            cost += estimatedLayoutCost(for: runs, images: images)
        case .imageRow(let images):
            cost += estimatedLayoutCost(for: images)
        case .code(let code, _, let lines):
            cost += code.utf16.count * 2
            cost += lines.reduce(into: 0) { partial, line in
                partial += 96
                partial += line.text.utf16.count * 2
                partial += line.tokens.count * 64
            }
        case .diff(let text, _):
            cost += 192 + text.utf16.count * 2
        case .listItems(let items):
            cost += items.reduce(into: 0) { $0 += estimatedLayoutCost(for: $1) }
        case .quoteBlocks(let blocks):
            cost += blocks.reduce(into: 0) { $0 += estimatedLayoutCost(for: $1) }
        case .tableRows(let rows):
            cost += estimatedLayoutCost(for: rows)
        case .definitionList(let items):
            cost += items.reduce(into: 0) { $0 += estimatedLayoutCost(for: $1) }
        case .abbreviationList(let items):
            cost += items.reduce(into: 0) { $0 += estimatedLayoutCost(for: $1) }
        case .image(let url, let alt, _):
            cost += 160 + url.utf16.count * 2 + (alt?.utf16.count ?? 0) * 2
        case .thematicBreak:
            cost += 32
        case .math(let latex, let runs):
            cost += latex.utf16.count * 2
            cost += runs.count * 64
        case .mermaid(let diagram):
            cost += 256
            cost += diagram.backgrounds.count * 96
            cost += diagram.nodes.count * 160
            cost += diagram.lines.count * 48
            cost += diagram.pieSlices.count * 64
            cost += diagram.labels.reduce(into: 0) { $0 += estimatedLayoutCost(for: $1) }
            for node in diagram.nodes {
                cost += node.labelRuns.reduce(into: 0) { $0 += estimatedLayoutCost(for: $1) }
            }
        }
        return cost
    }

    private func estimatedLayoutCost(for rows: [LayoutTableRow]) -> Int {
        rows.reduce(into: 0) { partial, row in
            partial += 160
            for cell in row.cells {
                partial += 96
                partial += estimatedLayoutCost(for: cell.textRuns, images: cell.inlineImages)
            }
        }
    }

    private func estimatedLayoutCost(for item: LayoutListItem) -> Int {
        var cost = 128
        cost += estimatedLayoutCost(for: item.contentRuns, images: item.inlineImages)
        cost += item.children.reduce(into: 0) { $0 += estimatedLayoutCost(for: $1) }
        return cost
    }

    private func estimatedLayoutCost(for item: LayoutDefinitionItem) -> Int {
        var cost = 160
        cost += estimatedLayoutCost(for: item.termRuns, images: item.termImages)
        for index in item.definitionRuns.indices {
            let images = index < item.definitionImages.count ? item.definitionImages[index] : []
            cost += estimatedLayoutCost(for: item.definitionRuns[index], images: images)
        }
        return cost
    }

    private func estimatedLayoutCost(for item: LayoutAbbreviationItem) -> Int {
        128 + estimatedLayoutCost(for: item.runs, images: item.images)
    }

    private func estimatedLayoutCost(for runs: [LayoutTextRun], images: [LayoutInlineImage]) -> Int {
        var cost = runs.reduce(into: 0) { $0 += estimatedLayoutCost(for: $1) }
        cost += estimatedLayoutCost(for: images)
        return cost
    }

    private func estimatedLayoutCost(for run: LayoutTextRun) -> Int {
        96 + run.text.utf16.count * 2 + run.glyphs.count * 48
    }

    private func estimatedLayoutCost(for images: [LayoutInlineImage]) -> Int {
        images.reduce(into: 0) { partial, image in
            partial += 128 + image.url.utf16.count * 2
        }
    }

    private func renderMeta(
        text: String,
        layoutEngine: MarkdownLayoutEngine,
        pipeline: VVMarkdownRenderPipeline,
        width: CGFloat
    ) -> (layout: MarkdownLayout, scene: VVScene) {
        layoutEngine.updateContentWidth(width)
        let document = makeMetaDocument(text: text)
        var layout = layoutEngine.layout(document)
        layoutEngine.adjustParagraphImageSpacing(in: &layout)
        let scene = pipeline.buildScene(from: layout)
        return (layout, scene)
    }

    private func applyingTextOpacity(
        to scene: VVScene,
        multiplier: Float
    ) -> VVScene {
        let alpha = max(0, multiplier)
        guard alpha != 1 else { return scene }

        var primitives: [VVPrimitive] = []
        primitives.reserveCapacity(scene.primitives.count)

        for primitive in scene.primitives {
            var updated = primitive
            if case .textRun(var run) = updated.kind {
                run.glyphs = run.glyphs.map { glyph in
                    VVTextGlyph(
                        glyphID: glyph.glyphID,
                        position: glyph.position,
                        size: glyph.size,
                        color: SIMD4<Float>(glyph.color.x, glyph.color.y, glyph.color.z, max(0, min(1, glyph.color.w * alpha))),
                        fontVariant: glyph.fontVariant,
                        fontSize: glyph.fontSize,
                        fontName: glyph.fontName,
                        stringIndex: glyph.stringIndex
                    )
                }
                updated.kind = .textRun(run)
            }
            primitives.append(updated)
        }

        return VVScene(primitives: primitives)
    }

    private func applyingPrefixGlyphColor(
        to scene: VVScene,
        color: SIMD4<Float>,
        glyphCount: Int
    ) -> VVScene {
        guard glyphCount > 0 else { return scene }

        var remaining = glyphCount
        var primitives: [VVPrimitive] = []
        primitives.reserveCapacity(scene.primitives.count)

        for primitive in scene.primitives {
            var updated = primitive
            if remaining > 0, case .textRun(var run) = updated.kind {
                var glyphs = run.glyphs
                for index in glyphs.indices where remaining > 0 {
                    guard glyphs[index].color.w > 0 else { continue }
                    let glyph = glyphs[index]
                    glyphs[index] = VVTextGlyph(
                        glyphID: glyph.glyphID,
                        position: glyph.position,
                        size: glyph.size,
                        color: SIMD4<Float>(color.x, color.y, color.z, glyph.color.w),
                        fontVariant: glyph.fontVariant,
                        fontSize: glyph.fontSize,
                        fontName: glyph.fontName,
                        stringIndex: glyph.stringIndex
                    )
                    remaining -= 1
                }
                run.glyphs = glyphs
                updated.kind = .textRun(run)
            }
            primitives.append(updated)
        }

        return VVScene(primitives: primitives)
    }

    private func renderCustomContent(
        _ content: VVChatCustomContent,
        width: CGFloat,
        contentScale: CGFloat
    ) -> CustomContentRender {
        switch content {
        case .summaryCard(let card):
            return renderSummaryCard(card, width: width)
        case .inlineDiff(let diff):
            return renderInlineDiff(diff, width: width, contentScale: contentScale)
        }
    }

    private func renderInlineDiff(
        _ diff: VVChatInlineDiffContent,
        width: CGFloat,
        contentScale: CGFloat
    ) -> CustomContentRender {
        let scale = normalizedContentScale(contentScale)
        let scaledSize = max(8, style.baseFont.pointSize * scale)
        let scaledFont = CTFontCreateCopyWithAttributes(style.baseFont, scaledSize, nil, nil) as VVFont
        let result = VVDiffSceneRenderer.render(
            unifiedDiff: diff.unifiedDiff,
            width: max(1, width),
            theme: style.theme,
            baseFont: scaledFont,
            options: diff.renderOptions
        )
        return CustomContentRender(
            scene: result.scene,
            height: result.contentHeight,
            visualWidth: width,
            interactiveRegions: [],
            imageURLs: []
        )
    }

    private func renderSummaryCard(_ card: VVChatSummaryCard, width: CGFloat) -> CustomContentRender {
        let titleColor = card.titleColor ?? style.theme.textColor
        let subtitleColor = card.subtitleColor ?? style.headerTextColor
        let dividerColor = card.dividerColor ?? style.theme.thematicBreakColor.withOpacity(0.7)
        let rowDividerColor = card.rowDividerColor ?? dividerColor.withOpacity(0.78)
        let hasTitleIcon = (card.iconURL?.isEmpty == false)
        let titleIconSize: CGFloat = hasTitleIcon ? max(10, style.headerIconSize - 1) : 0
        let titleIconSpacing: CGFloat = hasTitleIcon ? max(4, style.headerIconSpacing - 1) : 0
        let titleFont = style.baseFont.withSize(max(style.baseFont.pointSize + 1.5, 15))
        let subtitleFont = style.timestampFont.withSize(max(style.timestampFont.pointSize, 12.5))
        let rowTitleFont = style.baseFont.withSize(max(style.baseFont.pointSize, 14))
        let rowSecondaryFont = style.timestampFont.withSize(max(style.timestampFont.pointSize, 12))
        let rowDeltaFont = style.timestampFont.withSize(max(style.timestampFont.pointSize + 1, 13))
        let rowIconSize: CGFloat = 14
        let rowIconSpacing: CGFloat = 9
        let rowVerticalPadding: CGFloat = 10
        let rowHighlightHorizontalInset: CGFloat = 10
        let rowHighlightVerticalInset: CGFloat = 3
        let titleSubtitleSpacing: CGFloat = 4
        let dividerSpacingTop: CGFloat = 8
        let dividerSpacingBottom: CGFloat = 8
        let rowCornerRadius: CGFloat = 8

        var builder = VVSceneBuilder()
        var interactiveRegions: [VVChatInteractiveRegion] = []
        var imageURLs: [String] = []
        var currentY: CGFloat = 0

        let titleTextWidth = max(1, width - titleIconSize - titleIconSpacing)
        let titleRender = renderStyledText(card.title, font: titleFont, color: titleColor, width: titleTextWidth)
        let titleVisualHeight = max(titleRender.height, titleIconSize)
        var titleTextX: CGFloat = 0
        if hasTitleIcon, let iconURL = card.iconURL {
            let iconY = currentY + max(0, (titleVisualHeight - titleIconSize) * 0.5)
            let icon = VVImagePrimitive(
                url: iconURL,
                frame: CGRect(x: 0, y: iconY, width: titleIconSize, height: titleIconSize),
                cornerRadius: 2
            )
            builder.add(kind: .image(icon), zIndex: 0)
            imageURLs.append(iconURL)
            titleTextX = titleIconSize + titleIconSpacing
        }
        let titleTextY = currentY + max(0, (titleVisualHeight - titleRender.height) * 0.5) - titleRender.minY
        builder.withOffset(CGPoint(x: titleTextX, y: titleTextY)) { builder in
            builder.add(node: VVNode.fromScene(titleRender.scene))
        }
        currentY += max(1, titleVisualHeight)

        if let subtitle = card.subtitle?.trimmingCharacters(in: .whitespacesAndNewlines), !subtitle.isEmpty {
            currentY += titleSubtitleSpacing
            let subtitleRender = renderStyledText(subtitle, font: subtitleFont, color: subtitleColor, width: width)
            builder.withOffset(CGPoint(x: 0, y: currentY - subtitleRender.minY)) { builder in
                builder.add(node: VVNode.fromScene(subtitleRender.scene))
            }
            currentY += max(1, subtitleRender.height)
        }

        if !card.rows.isEmpty {
            currentY += dividerSpacingTop
            builder.add(
                kind: .line(
                    VVLinePrimitive(
                        start: CGPoint(x: 0, y: currentY),
                        end: CGPoint(x: width, y: currentY),
                        thickness: 1,
                        color: dividerColor
                    )
                ),
                zIndex: 0
            )
            currentY += dividerSpacingBottom
        }

        for (index, row) in card.rows.enumerated() {
            if index > 0 {
                builder.add(
                    kind: .line(
                        VVLinePrimitive(
                            start: CGPoint(x: 0, y: currentY),
                            end: CGPoint(x: width, y: currentY),
                            thickness: 1,
                            color: rowDividerColor
                        )
                    ),
                    zIndex: 0
                )
            }

            let additionsText = row.additionsText?.trimmingCharacters(in: .whitespacesAndNewlines)
            let deletionsText = row.deletionsText?.trimmingCharacters(in: .whitespacesAndNewlines)
            let additionsRender = additionsText.flatMap { text in
                text.isEmpty ? nil : renderStyledText(text, font: rowDeltaFont, color: row.additionsColor ?? style.theme.codeColor, width: width)
            }
            let deletionsRender = deletionsText.flatMap { text in
                text.isEmpty ? nil : renderStyledText(text, font: rowDeltaFont, color: row.deletionsColor ?? style.theme.strikethroughColor, width: width)
            }
            let trailingSpacing: CGFloat = (additionsRender != nil && deletionsRender != nil) ? 10 : 0
            let trailingWidth = (additionsRender?.width ?? 0) + (deletionsRender?.width ?? 0) + trailingSpacing
            let hasRowIcon = (row.iconURL?.isEmpty == false)
            let rowTextLeadingInset = hasRowIcon ? (rowIconSize + rowIconSpacing) : 0
            let titleWidth = max(80, width - trailingWidth - 16 - rowTextLeadingInset)
            let titleRender = renderStyledText(row.title, font: rowTitleFont, color: row.titleColor ?? style.theme.linkColor, width: titleWidth)
            let subtitleRender = row.subtitle.flatMap { subtitle in
                let trimmed = subtitle.trimmingCharacters(in: .whitespacesAndNewlines)
                return trimmed.isEmpty ? nil : renderStyledText(trimmed, font: rowSecondaryFont, color: row.subtitleColor ?? style.headerTextColor, width: titleWidth)
            }

            let rowContentHeight = max(
                titleRender.height + (subtitleRender == nil ? 0 : (4 + subtitleRender!.height)),
                max(additionsRender?.height ?? 0, deletionsRender?.height ?? 0)
            )
            let rowHeight = rowContentHeight + rowVerticalPadding * 2
            let rowTop = currentY
            let textBaseY = rowTop + rowVerticalPadding
            let rowTextX = rowTextLeadingInset

            if hasRowIcon, let iconURL = row.iconURL {
                let iconY = rowTop + max(0, (rowHeight - rowIconSize) * 0.5)
                let icon = VVImagePrimitive(
                    url: iconURL,
                    frame: CGRect(x: 0, y: iconY, width: rowIconSize, height: rowIconSize),
                    cornerRadius: 2
                )
                builder.add(kind: .image(icon), zIndex: 0)
                imageURLs.append(iconURL)
            }

            builder.withOffset(CGPoint(x: rowTextX, y: textBaseY - titleRender.minY)) { builder in
                builder.add(node: VVNode.fromScene(titleRender.scene))
            }
            if let subtitleRender {
                builder.withOffset(CGPoint(x: rowTextX, y: textBaseY + titleRender.height + 4 - subtitleRender.minY)) { builder in
                    builder.add(node: VVNode.fromScene(subtitleRender.scene))
                }
            }

            var trailingCursorX = width
            if let deletionsRender {
                trailingCursorX -= deletionsRender.width
                let deletionsY = rowTop + max(0, (rowHeight - deletionsRender.height) * 0.5) - deletionsRender.minY
                builder.withOffset(CGPoint(x: trailingCursorX, y: deletionsY)) { builder in
                    builder.add(node: VVNode.fromScene(deletionsRender.scene))
                }
            }
            if additionsRender != nil && deletionsRender != nil {
                trailingCursorX -= trailingSpacing
            }
            if let additionsRender {
                trailingCursorX -= additionsRender.width
                let additionsY = rowTop + max(0, (rowHeight - additionsRender.height) * 0.5) - additionsRender.minY
                builder.withOffset(CGPoint(x: trailingCursorX, y: additionsY)) { builder in
                    builder.add(node: VVNode.fromScene(additionsRender.scene))
                }
            }

            if let actionURL = row.actionURL?.trimmingCharacters(in: .whitespacesAndNewlines), !actionURL.isEmpty {
                let hoverFrame = CGRect(
                    x: -rowHighlightHorizontalInset,
                    y: rowTop + rowHighlightVerticalInset,
                    width: max(0, width + rowHighlightHorizontalInset * 2),
                    height: max(0, rowHeight - rowHighlightVerticalInset * 2)
                )
                interactiveRegions.append(
                    VVChatInteractiveRegion(
                        id: row.id,
                        frame: hoverFrame,
                        action: .link(actionURL),
                        hoverFillColor: row.hoverFillColor,
                        cornerRadius: rowCornerRadius
                    )
                )
            }

            currentY += rowHeight
        }

        return CustomContentRender(
            scene: builder.scene,
            height: currentY,
            visualWidth: width,
            interactiveRegions: interactiveRegions,
            imageURLs: imageURLs
        )
    }

    private func renderStyledText(
        _ text: String,
        font: VVFont,
        color: SIMD4<Float>,
        width: CGFloat
    ) -> (scene: VVScene, width: CGFloat, height: CGFloat, minY: CGFloat) {
        let resources = styledTextResources(font: font, color: color, width: width)
        let rendered = renderMeta(
            text: text,
            layoutEngine: resources.layoutEngine,
            pipeline: resources.pipeline,
            width: width
        )
        let bounds = sceneBounds(for: rendered.scene, layoutEngine: resources.layoutEngine)
        return (
            scene: rendered.scene,
            width: max(1, bounds?.width ?? Self.singleLineMetaWidth(text, font: font)),
            height: max(1, bounds?.height ?? rendered.layout.totalHeight),
            minY: bounds?.minY ?? 0
        )
    }

    private func renderHeader(text: String, iconURL: String?, trailingIconURL: String? = nil, badges: [VVHeaderBadge]? = nil, width: CGFloat) -> HeaderRender {
        struct HeaderBadgeRender {
            let scene: VVScene
            let width: CGFloat
            let minY: CGFloat
            let visualHeight: CGFloat
        }

        let hasIcon = (iconURL?.isEmpty == false)
        let iconSize = hasIcon ? max(8, style.headerIconSize) : 0
        let iconSpacing = hasIcon ? max(0, style.headerIconSpacing) : 0
        let hasTrailingIcon = (trailingIconURL?.isEmpty == false)
        let trailingIconSize = hasTrailingIcon ? max(8, style.headerIconSize) : 0
        let trailingIconSpacing = hasTrailingIcon ? max(0, style.headerIconSpacing) : 0
        let badgeSpacing: CGFloat = 6

        let rawBadges = badges ?? []
        let badgesTotalWidth: CGFloat = rawBadges.enumerated().reduce(CGFloat(0)) { sum, item in
            let spacing = item.offset == 0 ? 0 : badgeSpacing
            return sum + spacing + Self.singleLineMetaWidth(item.element.text, font: style.headerFont)
        }

        let textWidth = max(1, width - iconSize - iconSpacing - trailingIconSize - trailingIconSpacing - badgesTotalWidth)
        let textRender = renderMeta(
            text: text,
            layoutEngine: headerLayoutEngine,
            pipeline: headerPipeline,
            width: textWidth
        )
        let textHeight = textRender.layout.totalHeight
        let textBounds = sceneBounds(for: textRender.scene, layoutEngine: headerLayoutEngine)
        let textMinY = textBounds?.minY ?? 0
        let textVisualHeight = max(1, textBounds?.height ?? textHeight)

        let badgeRenders: [HeaderBadgeRender] = rawBadges.map { badge in
            let render = renderMeta(
                text: badge.text,
                layoutEngine: headerLayoutEngine,
                pipeline: headerPipeline,
                width: max(1, Self.singleLineMetaWidth(badge.text, font: style.headerFont))
            )
            let badgeScene = recolorScene(render.scene, color: badge.color)
            let badgeBounds = sceneBounds(for: badgeScene, layoutEngine: headerLayoutEngine)
            let badgeWidth = max(1, badgeBounds?.width ?? Self.singleLineMetaWidth(badge.text, font: style.headerFont))
            let badgeMinY = badgeBounds?.minY ?? 0
            let badgeVisualHeight = max(1, badgeBounds?.height ?? render.layout.totalHeight)
            return HeaderBadgeRender(
                scene: badgeScene,
                width: badgeWidth,
                minY: badgeMinY,
                visualHeight: badgeVisualHeight
            )
        }

        let badgesVisualHeight = badgeRenders.map(\.visualHeight).max() ?? 0
        let effectiveIconSize = max(iconSize, trailingIconSize)
        let height = max(textVisualHeight, badgesVisualHeight, effectiveIconSize)
        let textOffsetY = max(0, (height - textVisualHeight) * 0.5 - textMinY)

        var allImageURLs: [String] = []
        var builder = VVSceneBuilder()

        var textX: CGFloat = 0

        if hasIcon, let iconURL {
            let iconY = max(0, (height - iconSize) * 0.5)
            let icon = VVImagePrimitive(
                url: iconURL,
                frame: CGRect(x: 0, y: iconY, width: iconSize, height: iconSize),
                cornerRadius: 2
            )
            builder.add(kind: .image(icon), zIndex: 0)
            allImageURLs.append(iconURL)
            textX = iconSize + iconSpacing
        }

        builder.withOffset(CGPoint(x: textX, y: textOffsetY)) { builder in
            builder.add(node: VVNode.fromScene(textRender.scene))
        }

        let titleTextWidth = max(1, textBounds?.width ?? Self.singleLineMetaWidth(text, font: style.headerFont))
        var cursorX = textX + titleTextWidth

        if !badgeRenders.isEmpty {
            for (index, badgeRender) in badgeRenders.enumerated() {
                cursorX += index == 0 ? badgeSpacing : badgeSpacing
                let badgeOffsetY = max(0, (height - badgeRender.visualHeight) * 0.5 - badgeRender.minY)
                builder.withOffset(CGPoint(x: cursorX, y: badgeOffsetY)) { builder in
                    builder.add(node: VVNode.fromScene(badgeRender.scene))
                }
                cursorX += badgeRender.width
            }
        }

        if hasTrailingIcon, let trailingIconURL {
            let trailingIconY = max(0, (height - trailingIconSize) * 0.5)
            let trailingX = cursorX + trailingIconSpacing
            let trailingIcon = VVImagePrimitive(
                url: trailingIconURL,
                frame: CGRect(x: trailingX, y: trailingIconY, width: trailingIconSize, height: trailingIconSize),
                cornerRadius: 0
            )
            builder.add(kind: .image(trailingIcon), zIndex: 0)
            allImageURLs.append(trailingIconURL)
        }

        return HeaderRender(
            scene: builder.scene,
            height: height,
            imageURLs: allImageURLs
        )
    }

    /// Replace all glyph colors in a scene with the given color.
    private func recolorScene(_ scene: VVScene, color: SIMD4<Float>) -> VVScene {
        var primitives: [VVPrimitive] = []
        primitives.reserveCapacity(scene.primitives.count)
        for primitive in scene.primitives {
            var updated = primitive
            if case .textRun(var run) = updated.kind {
                var glyphs = run.glyphs
                for index in glyphs.indices {
                    let g = glyphs[index]
                    glyphs[index] = VVTextGlyph(
                        glyphID: g.glyphID,
                        position: g.position,
                        size: g.size,
                        color: SIMD4<Float>(color.x, color.y, color.z, g.color.w),
                        fontVariant: g.fontVariant,
                        fontSize: g.fontSize,
                        fontName: g.fontName,
                        stringIndex: g.stringIndex
                    )
                }
                run.glyphs = glyphs
                updated = VVPrimitive(kind: .textRun(run), zIndex: primitive.zIndex)
            }
            primitives.append(updated)
        }
        return VVScene(primitives: primitives)
    }

    private func makeMetaDocument(text: String) -> ParsedMarkdownDocument {
        let content = MarkdownInlineContent(text: text)
        let block = MarkdownBlock(.paragraph(content), index: 0)
        return ParsedMarkdownDocument(blocks: [block], footnotes: [:], isComplete: true, streamingBuffer: "")
    }

    private static func singleLineMetaWidth(_ text: String, font: VVFont) -> CGFloat {
        guard !text.isEmpty else { return 0 }
        let attributed = NSAttributedString(string: text, attributes: [.font: font])
        let line = CTLineCreateWithAttributedString(attributed)
        let width = CGFloat(CTLineGetTypographicBounds(line, nil, nil, nil))
        return ceil(width + 2)
    }

    private static func contentScaleKey(for scale: CGFloat) -> Int {
        Int((scale * 100).rounded())
    }

    private func normalizedContentScale(_ requested: CGFloat?) -> CGFloat {
        guard let requested, requested.isFinite else { return 1 }
        return max(0.72, min(1.6, requested))
    }

    private func contentResources(isDraft: Bool, scale: CGFloat) -> ContentResources {
        let normalizedScale = normalizedContentScale(scale)
        let scaleKey = Self.contentScaleKey(for: normalizedScale)
        if scaleKey == Self.contentScaleKey(for: 1) {
            return isDraft ? (draftLayoutEngine, draftPipeline) : (finalLayoutEngine, finalPipeline)
        }

        if isDraft {
            if let cached = scaledDraftResources[scaleKey] {
                return cached
            }
            let created = makeScaledContentResources(
                baseFont: style.draftFont,
                theme: style.draftTheme,
                scale: normalizedScale
            )
            scaledDraftResources[scaleKey] = created
            return created
        }

        if let cached = scaledFinalResources[scaleKey] {
            return cached
        }
        let created = makeScaledContentResources(
            baseFont: style.baseFont,
            theme: style.theme,
            scale: normalizedScale
        )
        scaledFinalResources[scaleKey] = created
        return created
    }

    private func styledTextResources(
        font: VVFont,
        color: SIMD4<Float>,
        width: CGFloat
    ) -> ContentResources {
        let key = StyledTextResourceKey(
            fontName: font.fontName,
            fontSizeKey: Self.fontSizeKey(for: font.pointSize),
            widthKey: Self.widthKey(for: width),
            colorKey: Self.colorKey(for: color)
        )
        if let cached = styledTextResourceCache[key] {
            return cached
        }

        let resources = Self.makeResources(
            baseFont: font,
            theme: Self.makeMetaTheme(base: style.theme, textColor: color),
            contentWidth: width
        )
        styledTextResourceCache[key] = resources
        return resources
    }

    private func makeScaledContentResources(
        baseFont: VVFont,
        theme: MarkdownTheme,
        scale: CGFloat
    ) -> ContentResources {
        let scaledSize = max(8, baseFont.pointSize * scale)
        let scaledFont = CTFontCreateCopyWithAttributes(baseFont, scaledSize, nil, nil) as VVFont
        return Self.makeResources(baseFont: scaledFont, theme: theme, contentWidth: contentWidth)
    }

    private func clearResourceCaches() {
        scaledFinalResources.removeAll(keepingCapacity: true)
        scaledDraftResources.removeAll(keepingCapacity: true)
        styledTextResourceCache.removeAll(keepingCapacity: true)
    }

    private func timestampCoreLabel(for message: VVChatMessage) -> String {
        let timestamp = message.timestamp ?? Date()
        return Self.timeFormatter.string(from: timestamp)
    }

    private func normalizedAssetURL(_ value: String?) -> String? {
        guard let trimmed = value?.trimmingCharacters(in: .whitespacesAndNewlines),
              !trimmed.isEmpty else {
            return nil
        }
        return trimmed
    }

    private static func makeMetaTheme(base: MarkdownTheme, textColor: SIMD4<Float>) -> MarkdownTheme {
        var theme = base
        theme.textColor = textColor
        theme.headingColor = textColor
        theme.linkColor = textColor
        theme.codeColor = textColor
        theme.blockQuoteColor = textColor
        theme.listBulletColor = textColor
        theme.checkboxCheckedColor = textColor
        theme.checkboxUncheckedColor = textColor
        theme.thematicBreakColor = textColor
        theme.tableBorderColor = textColor
        theme.diagramTextColor = textColor
        theme.mathColor = textColor
        theme.strikethroughColor = textColor
        theme.contentPadding = 0
        theme.paragraphSpacing = 2
        return theme
    }

    private static func makeResources(
        baseFont: VVFont,
        theme: MarkdownTheme,
        contentWidth: CGFloat
    ) -> ContentResources {
        let layoutEngine = MarkdownLayoutEngine(baseFont: baseFont, theme: theme, contentWidth: contentWidth)
        let pipeline = VVMarkdownRenderPipeline(theme: theme, layoutEngine: layoutEngine)
        return (layoutEngine, pipeline)
    }

    private static func makeFixedResources(
        style: VVChatTimelineStyle,
        contentWidth: CGFloat
    ) -> FixedResources {
        let headerTheme = makeMetaTheme(base: style.theme, textColor: style.headerTextColor)
        let timestampTheme = makeMetaTheme(base: style.theme, textColor: style.timestampTextColor)
        let loadingTheme = makeMetaTheme(base: style.theme, textColor: style.loadingIndicatorTextColor)
        return FixedResources(
            final: makeResources(baseFont: style.baseFont, theme: style.theme, contentWidth: contentWidth),
            draft: makeResources(baseFont: style.draftFont, theme: style.draftTheme, contentWidth: contentWidth),
            header: makeResources(baseFont: style.headerFont, theme: headerTheme, contentWidth: contentWidth),
            timestamp: makeResources(baseFont: style.timestampFont, theme: timestampTheme, contentWidth: contentWidth),
            loading: makeResources(baseFont: style.loadingIndicatorFont, theme: loadingTheme, contentWidth: contentWidth)
        )
    }

    private static func fontSizeKey(for size: CGFloat) -> Int {
        Int((size * 100).rounded())
    }

    private static func colorKey(for color: SIMD4<Float>) -> SIMD4<Int> {
        SIMD4<Int>(
            Int((color.x * 255).rounded()),
            Int((color.y * 255).rounded()),
            Int((color.z * 255).rounded()),
            Int((color.w * 255).rounded())
        )
    }

    private func sceneBounds(for scene: VVScene, layoutEngine: MarkdownLayoutEngine) -> CGRect? {
        var minX = CGFloat.greatestFiniteMagnitude
        var minY = CGFloat.greatestFiniteMagnitude
        var maxX = -CGFloat.greatestFiniteMagnitude
        var maxY = -CGFloat.greatestFiniteMagnitude
        var hasValue = false

        let baseSize = max(1, layoutEngine.baseFontSize)
        let ascent = layoutEngine.currentAscent
        let descent = layoutEngine.currentDescent

        func updateBounds(minX newMinX: CGFloat, minY newMinY: CGFloat, maxX newMaxX: CGFloat, maxY newMaxY: CGFloat) {
            minX = min(minX, newMinX)
            minY = min(minY, newMinY)
            maxX = max(maxX, newMaxX)
            maxY = max(maxY, newMaxY)
            hasValue = true
        }

        func updateBounds(_ rect: CGRect) {
            updateBounds(minX: rect.minX, minY: rect.minY, maxX: rect.maxX, maxY: rect.maxY)
        }

        func updateGlyphs(_ glyphs: [VVTextGlyph], fontSize: CGFloat) {
            guard !glyphs.isEmpty else { return }
            let scale = max(0.5, fontSize / baseSize)
            let glyphAscent = ascent * scale
            let glyphDescent = descent * scale
            for glyph in glyphs where glyph.color.w > 0 {
                updateBounds(
                    minX: glyph.position.x,
                    minY: glyph.position.y - glyphAscent,
                    maxX: glyph.position.x + glyph.size.width,
                    maxY: glyph.position.y + glyphDescent
                )
            }
        }

        for primitive in scene.primitives {
            switch primitive.kind {
            case .textRun(let run):
                updateGlyphs(run.glyphs, fontSize: run.fontSize)

            case .quad(let quad):
                guard quad.color.w > 0 else { continue }
                updateBounds(quad.frame)

            case .gradientQuad(let quad):
                if quad.startColor.w <= 0 && quad.endColor.w <= 0 {
                    continue
                }
                updateBounds(quad.frame)

            case .line(let line):
                guard line.color.w > 0 else { continue }
                let minX = min(line.start.x, line.end.x)
                let minY = min(line.start.y, line.end.y)
                let width = abs(line.end.x - line.start.x)
                let height = abs(line.end.y - line.start.y)
                let rectWidth = width > 0 ? width : line.thickness
                let rectHeight = height > 0 ? height : line.thickness
                updateBounds(CGRect(x: minX, y: minY, width: rectWidth, height: rectHeight))

            case .bullet(let bullet):
                guard bullet.color.w > 0 else { continue }
                updateBounds(CGRect(x: bullet.position.x, y: bullet.position.y, width: bullet.size, height: bullet.size))

            case .image(let image):
                updateBounds(image.frame)

            case .blockQuoteBorder(let border):
                guard border.color.w > 0 else { continue }
                updateBounds(border.frame)

            case .tableLine(let line):
                guard line.color.w > 0 else { continue }
                let minX = min(line.start.x, line.end.x)
                let minY = min(line.start.y, line.end.y)
                let width = abs(line.end.x - line.start.x)
                let height = abs(line.end.y - line.start.y)
                let rectWidth = width > 0 ? width : line.lineWidth
                let rectHeight = height > 0 ? height : line.lineWidth
                updateBounds(CGRect(x: minX, y: minY, width: rectWidth, height: rectHeight))

            case .pieSlice(let slice):
                guard slice.color.w > 0 else { continue }
                let rect = CGRect(
                    x: slice.center.x - slice.radius,
                    y: slice.center.y - slice.radius,
                    width: slice.radius * 2,
                    height: slice.radius * 2
                )
                updateBounds(rect)

            case .underline(let underline):
                guard underline.color.w > 0 else { continue }
                updateBounds(CGRect(x: underline.origin.x, y: underline.origin.y, width: underline.width, height: underline.thickness))

            case .path(let path):
                updateBounds(path.bounds)
            }
        }

        guard hasValue else { return nil }
        return CGRect(x: minX, y: minY, width: max(1, maxX - minX), height: max(1, maxY - minY))
    }

    private func measuredContentWidth(for layout: MarkdownLayout) -> CGFloat? {
        var maxX: CGFloat = 0
        var hasValue = false
        for block in layout.blocks {
            let (blockMaxX, blockHasValue) = measuredMaxX(for: block)
            if blockHasValue {
                maxX = max(maxX, blockMaxX)
                hasValue = true
            }
        }
        return hasValue ? maxX : nil
    }

    private func measuredMaxX(for block: LayoutBlock) -> (CGFloat, Bool) {
        switch block.content {
        case .text(let runs):
            return measuredMaxX(for: runs, images: [])
        case .inline(let runs, let images):
            return measuredMaxX(for: runs, images: images)
        case .listItems(let items):
            return measuredMaxX(for: items)
        case .quoteBlocks(let blocks):
            return measuredMaxX(for: blocks)
        case .definitionList(let items):
            return measuredMaxX(for: items)
        case .abbreviationList(let items):
            return measuredMaxX(for: items)
        case .imageRow(let images):
            return measuredMaxX(for: images)
        case .tableRows(let rows):
            if let rowMax = rows.map({ $0.frame.maxX }).max() {
                return (rowMax, rowMax > 0)
            }
            return (block.frame.maxX, block.frame.maxX > 0)
        case .mermaid(let diagram):
            return (diagram.frame.maxX, diagram.frame.maxX > 0)
        case .image, .code, .diff, .thematicBreak, .math:
            return (block.frame.maxX, block.frame.maxX > 0)
        }
    }

    private func measuredMaxX(for blocks: [LayoutBlock]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for block in blocks {
            let (blockMaxX, blockHasValue) = measuredMaxX(for: block)
            if blockHasValue {
                maxX = max(maxX, blockMaxX)
                hasValue = true
            }
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for items: [LayoutListItem]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for item in items {
            let (itemMaxX, itemHasValue) = measuredMaxX(for: item)
            if itemHasValue {
                maxX = max(maxX, itemMaxX)
                hasValue = true
            }
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for item: LayoutListItem) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        let (contentMaxX, contentHasValue) = measuredMaxX(for: item.contentRuns, images: item.inlineImages)
        if contentHasValue {
            maxX = max(maxX, contentMaxX)
            hasValue = true
        }
        let (childMaxX, childHasValue) = measuredMaxX(for: item.children)
        if childHasValue {
            maxX = max(maxX, childMaxX)
            hasValue = true
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for items: [LayoutDefinitionItem]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for item in items {
            let (termMaxX, termHasValue) = measuredMaxX(for: item.termRuns, images: item.termImages)
            if termHasValue {
                maxX = max(maxX, termMaxX)
                hasValue = true
            }
            for (index, runs) in item.definitionRuns.enumerated() {
                let images = index < item.definitionImages.count ? item.definitionImages[index] : []
                let (defMaxX, defHasValue) = measuredMaxX(for: runs, images: images)
                if defHasValue {
                    maxX = max(maxX, defMaxX)
                    hasValue = true
                }
            }
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for items: [LayoutAbbreviationItem]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for item in items {
            let (itemMaxX, itemHasValue) = measuredMaxX(for: item.runs, images: item.images)
            if itemHasValue {
                maxX = max(maxX, itemMaxX)
                hasValue = true
            }
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for runs: [LayoutTextRun], images: [LayoutInlineImage]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for run in runs {
            for glyph in run.glyphs {
                maxX = max(maxX, glyph.position.x + glyph.size.width)
                hasValue = true
            }
        }
        for image in images {
            maxX = max(maxX, image.frame.maxX)
            hasValue = true
        }
        return (maxX, hasValue)
    }

    private func measuredMaxX(for images: [LayoutInlineImage]) -> (CGFloat, Bool) {
        var maxX: CGFloat = 0
        var hasValue = false
        for image in images {
            maxX = max(maxX, image.frame.maxX)
            hasValue = true
        }
        return (maxX, hasValue)
    }

    private func collectImageURLs(from layout: MarkdownLayout) -> Set<String> {
        var urls = Set<String>()
        for block in layout.blocks {
            collectImageURLs(from: block, into: &urls)
        }
        return urls
    }

    private func collectImageURLs(from block: LayoutBlock, into urls: inout Set<String>) {
        switch block.content {
        case .inline(_, let images):
            for image in images { urls.insert(image.url) }
        case .imageRow(let images):
            for image in images { urls.insert(image.url) }
        case .image(let url, _, _):
            urls.insert(url)
        case .listItems(let items):
            for item in items {
                collectImageURLs(from: item, into: &urls)
            }
        case .quoteBlocks(let blocks):
            for nested in blocks {
                collectImageURLs(from: nested, into: &urls)
            }
        case .tableRows(let rows):
            for row in rows {
                for cell in row.cells {
                    for image in cell.inlineImages {
                        urls.insert(image.url)
                    }
                }
            }
        case .definitionList(let items):
            for item in items {
                for image in item.termImages {
                    urls.insert(image.url)
                }
                for definitionImages in item.definitionImages {
                    for image in definitionImages {
                        urls.insert(image.url)
                    }
                }
            }
        case .abbreviationList(let items):
            for item in items {
                for image in item.images {
                    urls.insert(image.url)
                }
            }
        default:
            break
        }
    }

    private func collectImageURLs(from item: LayoutListItem, into urls: inout Set<String>) {
        for image in item.inlineImages {
            urls.insert(image.url)
        }
        for child in item.children {
            collectImageURLs(from: child, into: &urls)
        }
    }

    private func dematerializePreparedLayoutsIfNeeded(excluding protectedKey: CacheKey?) {
        func currentResidentCost() -> Int {
            preparedMarkdownCache.valuesFromLeastRecent().reduce(into: 0) { total, value in
                total += Self.estimatedResidentPreparedLayoutCost(value)
            }
        }

        var residentCost = currentResidentCost()
        guard residentCost > Self.materializedPreparedLayoutCostLimit ||
                preparedMarkdownCache.currentCost > Self.preparedMarkdownCacheCostLimit else { return }
        for key in preparedMarkdownCache.keysFromLeastRecent() {
            if let protectedKey, protectedKey == key {
                continue
            }
            preparedMarkdownCache.updateValue(for: key) { prepared in
                guard prepared.layout != nil else { return }
                prepared.layout = nil
            }
            residentCost = currentResidentCost()
            if residentCost <= Self.materializedPreparedLayoutCostLimit &&
                preparedMarkdownCache.currentCost <= Self.preparedMarkdownCacheCostLimit {
                break
            }
        }
    }

    private static func estimatedPreparedMarkdownCost(_ content: PreparedMarkdownContent) -> Int {
        let analysisCost = max(
            1024,
            content.analysis.blockMinY.count * MemoryLayout<CGFloat>.stride * 3 +
            content.analysis.sourceBlockIndexes.count * MemoryLayout<Int>.stride
        )
        let mappingCost = (content.analysis.directImageBlockIDsByURL.count + content.analysis.imageRowBlockIDsByURL.count) * 64
        let imageURLCost = content.analysis.imageURLs.reduce(into: 0) { $0 += 32 + $1.utf16.count * 2 }
        let documentFloor = 16 * 1024
        if content.layout != nil {
            return max(content.analysis.estimatedCost + imageURLCost + mappingCost, documentFloor)
        }
        return max(documentFloor, analysisCost + mappingCost + imageURLCost)
    }

    private static func estimatedResidentPreparedLayoutCost(_ content: PreparedMarkdownContent) -> Int {
        guard content.layout != nil else { return 0 }
        return max(content.analysis.estimatedCost, 1)
    }

    private static func estimatedSceneArtifactsCost(_ artifacts: VVChatSceneArtifacts) -> Int {
        var cost = max(artifacts.orderedPrimitiveIndices.count, 1) * MemoryLayout<Int>.stride
        for primitive in artifacts.scene.primitives {
            cost += estimatedPrimitiveCost(primitive)
        }
        return max(cost, 1)
    }

    private static func estimatedRenderedMessageCost(_ rendered: VVChatRenderedMessage) -> Int {
        var cost = max(rendered.chromeOrderedPrimitiveIndices.count, 1) * MemoryLayout<Int>.stride
        cost += rendered.interactiveRegions.count * MemoryLayout<VVChatInteractiveRegion>.stride
        cost += rendered.imageURLs.reduce(into: 0) { total, url in
            total += 32 + url.utf16.count * 2
        }
        if rendered.footerTrailingActionFrame != nil {
            cost += MemoryLayout<CGRect>.stride
        }
        for primitive in rendered.chromeScene.primitives {
            cost += estimatedPrimitiveCost(primitive)
        }
        return max(cost, 1)
    }

    private static func estimatedPrimitiveCost(_ primitive: VVPrimitive) -> Int {
        switch primitive.kind {
        case .textRun(let run):
            let glyphCost = run.glyphs.count * 48
            return 128 + glyphCost
        case .quad:
            return 64
        case .gradientQuad:
            return 96
        case .line, .underline, .bullet, .blockQuoteBorder, .tableLine, .pieSlice:
            return 64
        case .image(let image):
            return 128 + image.url.utf16.count * 2
        case .path(let path):
            return 160 + path.vertices.count * MemoryLayout<VVPathVertex>.stride
        }
    }

    private static func widthKey(for width: CGFloat) -> Int {
        Int((width * 2).rounded(.down))
    }
}
