import Foundation
import CoreText
import VVMarkdown
import VVMetalPrimitives

public struct VVChatRenderedMessage {
    public let id: String
    public let revision: Int
    public let layout: MarkdownLayout
    public let layoutEngine: MarkdownLayoutEngine
    public let scene: VVScene
    public let height: CGFloat
    public let contentOffset: CGPoint
    public let selectionContentOffset: CGPoint
    public let isDraft: Bool
    public let imageURLs: [String]
    public let footerTrailingActionFrame: CGRect?
    public let interactiveRegions: [VVChatInteractiveRegion]
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

public final class VVChatMessageRenderer {
    private final class LRUCache<Key: Hashable, Value> {
        private final class Node {
            let key: Key
            var value: Value
            var prev: Node?
            var next: Node?
            init(key: Key, value: Value) { self.key = key; self.value = value }
        }

        private var map: [Key: Node] = [:]
        private var head: Node?  // most recent
        private var tail: Node?  // least recent
        private var limit: Int

        init(limit: Int) {
            self.limit = max(0, limit)
        }

        func updateLimit(_ limit: Int) {
            self.limit = max(0, limit)
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
                return
            }
            if let existing = map[key] {
                existing.value = value
                moveToTail(existing)
            } else {
                let node = Node(key: key, value: value)
                map[key] = node
                appendToTail(node)
            }
            evictIfNeeded()
        }

        func remove(where predicate: (Key) -> Bool) {
            var node = head
            while let current = node {
                node = current.next
                if predicate(current.key) {
                    unlink(current)
                    map.removeValue(forKey: current.key)
                }
            }
        }

        func removeAll() {
            map.removeAll(keepingCapacity: true)
            head = nil
            tail = nil
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
            while map.count > limit, let oldest = head {
                unlink(oldest)
                map.removeValue(forKey: oldest.key)
            }
        }
    }

    private struct CacheKey: Hashable {
        let id: String
        let revision: Int
        let widthKey: Int
        let isDraft: Bool
        let contentScaleKey: Int
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
    private var cache: LRUCache<CacheKey, VVChatRenderedMessage>
    private var contentWidth: CGFloat
    private var style: VVChatTimelineStyle
    private var imageSizes: [String: CGSize] = [:]
    private static let timeFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateStyle = .none
        formatter.timeStyle = .short
        return formatter
    }()

    public init(style: VVChatTimelineStyle, contentWidth: CGFloat) {
        self.style = style
        self.contentWidth = contentWidth
        self.finalLayoutEngine = MarkdownLayoutEngine(baseFont: style.baseFont, theme: style.theme, contentWidth: contentWidth)
        self.draftLayoutEngine = MarkdownLayoutEngine(baseFont: style.draftFont, theme: style.draftTheme, contentWidth: contentWidth)
        self.finalPipeline = VVMarkdownRenderPipeline(theme: style.theme, layoutEngine: finalLayoutEngine)
        self.draftPipeline = VVMarkdownRenderPipeline(theme: style.draftTheme, layoutEngine: draftLayoutEngine)
        let headerTheme = Self.makeMetaTheme(base: style.theme, textColor: style.headerTextColor)
        let timestampTheme = Self.makeMetaTheme(base: style.theme, textColor: style.timestampTextColor)
        let loadingTheme = Self.makeMetaTheme(base: style.theme, textColor: style.loadingIndicatorTextColor)
        self.headerLayoutEngine = MarkdownLayoutEngine(baseFont: style.headerFont, theme: headerTheme, contentWidth: contentWidth)
        self.timestampLayoutEngine = MarkdownLayoutEngine(baseFont: style.timestampFont, theme: timestampTheme, contentWidth: contentWidth)
        self.headerPipeline = VVMarkdownRenderPipeline(theme: headerTheme, layoutEngine: headerLayoutEngine)
        self.timestampPipeline = VVMarkdownRenderPipeline(theme: timestampTheme, layoutEngine: timestampLayoutEngine)
        self.loadingLayoutEngine = MarkdownLayoutEngine(baseFont: style.loadingIndicatorFont, theme: loadingTheme, contentWidth: contentWidth)
        self.loadingPipeline = VVMarkdownRenderPipeline(theme: loadingTheme, layoutEngine: loadingLayoutEngine)
        self.cache = LRUCache(limit: style.renderedCacheLimit)
    }

    public func updateStyle(_ style: VVChatTimelineStyle) {
        self.style = style
        finalLayoutEngine = MarkdownLayoutEngine(baseFont: style.baseFont, theme: style.theme, contentWidth: contentWidth)
        draftLayoutEngine = MarkdownLayoutEngine(baseFont: style.draftFont, theme: style.draftTheme, contentWidth: contentWidth)
        finalPipeline = VVMarkdownRenderPipeline(theme: style.theme, layoutEngine: finalLayoutEngine)
        draftPipeline = VVMarkdownRenderPipeline(theme: style.draftTheme, layoutEngine: draftLayoutEngine)
        let headerTheme = Self.makeMetaTheme(base: style.theme, textColor: style.headerTextColor)
        let timestampTheme = Self.makeMetaTheme(base: style.theme, textColor: style.timestampTextColor)
        let loadingTheme = Self.makeMetaTheme(base: style.theme, textColor: style.loadingIndicatorTextColor)
        headerLayoutEngine = MarkdownLayoutEngine(baseFont: style.headerFont, theme: headerTheme, contentWidth: contentWidth)
        timestampLayoutEngine = MarkdownLayoutEngine(baseFont: style.timestampFont, theme: timestampTheme, contentWidth: contentWidth)
        headerPipeline = VVMarkdownRenderPipeline(theme: headerTheme, layoutEngine: headerLayoutEngine)
        timestampPipeline = VVMarkdownRenderPipeline(theme: timestampTheme, layoutEngine: timestampLayoutEngine)
        loadingLayoutEngine = MarkdownLayoutEngine(baseFont: style.loadingIndicatorFont, theme: loadingTheme, contentWidth: contentWidth)
        loadingPipeline = VVMarkdownRenderPipeline(theme: loadingTheme, layoutEngine: loadingLayoutEngine)
        scaledFinalResources.removeAll(keepingCapacity: true)
        scaledDraftResources.removeAll(keepingCapacity: true)
        cache.updateLimit(style.renderedCacheLimit)
        cache.removeAll()
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
        scaledFinalResources.removeAll(keepingCapacity: true)
        scaledDraftResources.removeAll(keepingCapacity: true)
        cache.removeAll()
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
    }

    public func invalidateAll() {
        cache.removeAll()
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

        let (layoutEngine, pipeline) = contentResources(isDraft: isDraft, scale: contentScale)
        let document = parser.parse(message.content)
        let customContent = message.customContent

        layoutEngine.updateImageSizeProvider { [weak self] url in
            self?.imageSizes[url]
        }
        layoutEngine.updateContentWidth(messageContentWidth)

        let layout: MarkdownLayout
        var contentScene: VVScene
        let contentBounds: CGRect?
        let contentMinX: CGFloat
        let contentMinY: CGFloat
        var imageURLs = Set<String>()
        let measuredWidth: CGFloat?
        let interactiveRegions: [VVChatInteractiveRegion]

        if let customContent {
            layout = layoutEngine.layout(parser.parse(""))
            let customRender = renderCustomContent(customContent, width: messageContentWidth)
            contentScene = customRender.scene
            contentBounds = sceneBounds(for: contentScene, layoutEngine: layoutEngine)
            contentMinX = max(0, contentBounds?.minX ?? 0)
            contentMinY = min(0, contentBounds?.minY ?? 0)
            imageURLs = Set(customRender.imageURLs)
            measuredWidth = customRender.visualWidth
            interactiveRegions = customRender.interactiveRegions
        } else {
            var computedLayout = layoutEngine.layout(document)
            layoutEngine.adjustParagraphImageSpacing(in: &computedLayout)
            layout = computedLayout

            var computedScene = pipeline.buildScene(from: layout)
            if let opacityMultiplier = presentation?.textOpacityMultiplier {
                computedScene = applyingTextOpacity(
                    to: computedScene,
                    multiplier: opacityMultiplier
                )
            }
            if let prefixColor = presentation?.prefixGlyphColor {
                let glyphCount = max(0, presentation?.prefixGlyphCount ?? 0)
                if glyphCount > 0 {
                    computedScene = applyingPrefixGlyphColor(
                        to: computedScene,
                        color: prefixColor,
                        glyphCount: glyphCount
                    )
                }
            }

            contentScene = computedScene
            let computedBounds = sceneBounds(for: computedScene, layoutEngine: layoutEngine)
            contentBounds = computedBounds
            // Only compensate positive scene offsets. Negative minX can be produced by
            // markdown sub-primitives (e.g. list markers/row adorners) and should not
            // shift the whole message body to the right.
            contentMinX = max(0, computedBounds?.minX ?? 0)
            contentMinY = min(0, computedBounds?.minY ?? 0)
            imageURLs = Set(collectImageURLs(from: layout))
            measuredWidth = usesBubble ? measuredContentWidth(for: layout) : nil
            interactiveRegions = []
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
        let contentHeight = max(1, contentBounds?.height ?? layout.totalHeight)
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
            builder.withOffset(CGPoint(x: contentOffsetX, y: contentOffsetY)) { builder in
                builder.add(node: VVNode.fromScene(contentScene))
            }
        } else {
            let contentOffsetX = -contentMinX
            let contentOffsetY = currentY - contentMinY
            selectionContentOffset = CGPoint(x: contentOffsetX, y: contentOffsetY)
            builder.withOffset(CGPoint(x: contentOffsetX, y: contentOffsetY)) { builder in
                builder.add(node: VVNode.fromScene(contentScene))
            }
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

        var scene = builder.scene
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
                builder.add(node: VVNode.fromScene(scene))
            }
            scene = laneBuilder.scene
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
        }

        let messageBounds = sceneBounds(for: scene, layoutEngine: layoutEngine)
        let topOverflow = max(0, -(messageBounds?.minY ?? 0))
        let sceneMaxY = max(0, messageBounds?.maxY ?? messageHeight)
        let measuredMessageHeight = max(messageHeight + topOverflow, sceneMaxY + topOverflow)
        let height = measuredMessageHeight + insets.top + insets.bottom

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
        let rendered = VVChatRenderedMessage(
            id: message.id,
            revision: message.revision,
            layout: layout,
            layoutEngine: layoutEngine,
            scene: scene,
            height: height,
            contentOffset: CGPoint(x: insets.left + bubbleOffsetX, y: insets.top + topOverflow),
            selectionContentOffset: selectionContentOffset,
            isDraft: isDraft,
            imageURLs: Array(imageURLs),
            footerTrailingActionFrame: footerTrailingActionFrame,
            interactiveRegions: adjustedInteractiveRegions
        )
        cache.set(rendered, for: key)
        return rendered
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

    private func renderCustomContent(_ content: VVChatCustomContent, width: CGFloat) -> CustomContentRender {
        switch content {
        case .summaryCard(let card):
            return renderSummaryCard(card, width: width)
        case .inlineDiff(let diff):
            return renderInlineDiff(diff, width: width)
        }
    }

    private func renderInlineDiff(_ diff: VVChatInlineDiffContent, width: CGFloat) -> CustomContentRender {
        let result = VVUnifiedDiffSceneRenderer.render(
            unifiedDiff: diff.unifiedDiff,
            width: max(1, width),
            theme: style.theme,
            baseFont: style.baseFont,
            options: .compactInline
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
        let theme = Self.makeMetaTheme(base: style.theme, textColor: color)
        let layoutEngine = MarkdownLayoutEngine(baseFont: font, theme: theme, contentWidth: width)
        let pipeline = VVMarkdownRenderPipeline(theme: theme, layoutEngine: layoutEngine)
        let rendered = renderMeta(text: text, layoutEngine: layoutEngine, pipeline: pipeline, width: width)
        let bounds = sceneBounds(for: rendered.scene, layoutEngine: layoutEngine)
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

    private func makeScaledContentResources(
        baseFont: VVFont,
        theme: MarkdownTheme,
        scale: CGFloat
    ) -> ContentResources {
        let scaledSize = max(8, baseFont.pointSize * scale)
        let scaledFont = CTFontCreateCopyWithAttributes(baseFont, scaledSize, nil, nil) as VVFont
        let layoutEngine = MarkdownLayoutEngine(baseFont: scaledFont, theme: theme, contentWidth: contentWidth)
        let pipeline = VVMarkdownRenderPipeline(theme: theme, layoutEngine: layoutEngine)
        return (layoutEngine, pipeline)
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

    private static func widthKey(for width: CGFloat) -> Int {
        Int((width * 2).rounded(.down))
    }
}
