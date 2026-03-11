import XCTest
import AppKit
import Darwin.Mach
@testable import VVChatTimeline
import VVMarkdown
import VVMetalPrimitives

@MainActor
final class VVChatTimelinePerformanceTests: XCTestCase {
    private let viewportSize = CGSize(width: 900, height: 720)

    func testRenderedMessageLookupByIndexMatchesID() {
        let controller = makeSeededController(messageCount: 180, width: viewportSize.width)

        for index in stride(from: 0, to: controller.messages.count, by: 17) {
            let messageID = controller.messages[index].id
            let byIndex = controller.renderedMessage(at: index)
            let byID = controller.renderedMessage(for: messageID)
            let fullByIndex = controller.sceneArtifacts(at: index, visibleRect: nil)
            let byIDIndex = controller.messages.firstIndex { $0.id == messageID }!
            let fullByID = controller.sceneArtifacts(at: byIDIndex, visibleRect: nil)
            XCTAssertEqual(byIndex?.id, byID?.id)
            XCTAssertEqual(byIndex?.revision, byID?.revision)
            XCTAssertEqual(fullByIndex?.scene.primitives.count, fullByID?.scene.primitives.count)
        }
    }

    func testVisibleLayoutRangeMatchesLinearScan() {
        let controller = makeSeededController(messageCount: 240, width: viewportSize.width)
        let overscan: CGFloat = 900
        let offsets = makeScrollOffsets(totalHeight: controller.totalHeight, viewportHeight: viewportSize.height, steps: 8)

        for offset in offsets {
            let viewport = CGRect(x: 0, y: offset, width: viewportSize.width, height: viewportSize.height)
            let expected = controller.layouts.enumerated().reduce(into: [Int]()) { result, pair in
                let (index, layout) = pair
                if layout.frame.maxY >= viewport.minY - overscan && layout.frame.minY <= viewport.maxY + overscan {
                    result.append(index)
                }
            }
            let actual = Array(controller.visibleLayoutRange(in: viewport, overscan: overscan))
            XCTAssertEqual(actual, expected, "visible range mismatch at offset \(offset)")
        }
    }

    func testItemLayoutsRemainMonotonicAfterMiddleHeightChange() {
        let controller = makeSeededController(messageCount: 48, width: viewportSize.width)
        let targetID = controller.messages[22].id
        let before = controller.layouts

        controller.replaceEntry(
            id: targetID,
            with: .message(
                VVChatMessage(
                    id: targetID,
                    role: .assistant,
                    state: .final,
                    content: longMessageContent(paragraphCount: 180),
                    revision: controller.messages[22].revision + 1
                )
            ),
            scrollToBottom: false,
            markUnread: false
        )

        let after = controller.layouts
        XCTAssertEqual(before.count, after.count)
        for index in after.indices.dropFirst() {
            XCTAssertGreaterThanOrEqual(after[index].frame.minY, after[index - 1].frame.maxY)
        }
        XCTAssertGreaterThan(after[22].frame.height, before[22].frame.height)
        XCTAssertGreaterThan(after.last?.frame.maxY ?? 0, before.last?.frame.maxY ?? 0)
    }

    func testInitialControllerRebuildKeepsHeavyRendererCachesCold() {
        let controller = makeSeededController(messageCount: 120, width: viewportSize.width)
        let snapshot = controller.debugSnapshot()

        XCTAssertEqual(snapshot.renderedMessageCacheCount, 0)
        XCTAssertEqual(snapshot.preparedMarkdownCacheCount, 0)
        XCTAssertEqual(snapshot.sceneWindowCacheEstimatedCost, 0)
        XCTAssertEqual(controller.debugExactLayoutCount(), 0)
    }

    func testVisibleRenderWarmsChatCachesOnDemandAfterColdRebuild() {
        let controller = makeSeededController(messageCount: 120, width: viewportSize.width)
        XCTAssertEqual(controller.debugSnapshot().renderedMessageCacheCount, 0)
        XCTAssertEqual(controller.debugExactLayoutCount(), 0)

        let visibleRect = CGRect(x: 0, y: 0, width: viewportSize.width, height: viewportSize.height)
        XCTAssertTrue(controller.hydrateExactLayouts(in: visibleRect, overscan: 900))
        _ = controller.contentSceneArtifacts(at: 0, visibleRect: visibleRect)
        let snapshot = controller.debugSnapshot()

        XCTAssertGreaterThan(snapshot.preparedMarkdownCacheCount, 0)
        XCTAssertGreaterThan(snapshot.sceneWindowCacheEstimatedCost, 0)
        XCTAssertGreaterThan(controller.debugExactLayoutCount(), 0)
    }

    func testColdRebuildHydratesOnlyVisibleTranscriptSlice() {
        let controller = makeSeededController(messageCount: 240, width: viewportSize.width)
        XCTAssertEqual(controller.debugExactLayoutCount(), 0)

        let visibleRect = CGRect(x: 0, y: 0, width: viewportSize.width, height: viewportSize.height)
        XCTAssertTrue(controller.hydrateExactLayouts(in: visibleRect, overscan: 900))

        let exactCount = controller.debugExactLayoutCount()
        XCTAssertGreaterThan(exactCount, 0)
        XCTAssertLessThan(exactCount, controller.layoutCount)
    }

    func testScrollingDefersExactHydrationUntilIdle() {
        let controller = makeSeededController(messageCount: 260, width: viewportSize.width)
        let view = VVChatTimelineView(frame: CGRect(origin: .zero, size: viewportSize))
        view.controller = controller
        view.layoutSubtreeIfNeeded()
        drainMainRunLoop(for: 0.2)

        let beforeScrollExactCount = controller.debugExactLayoutCount()
        let targetY = max(0, min(controller.totalHeight - viewportSize.height, controller.totalHeight * 0.45))

        controller.markUserInteraction(true)
        view.restoreScrollPosition(CGPoint(x: 0, y: targetY))
        drainMainRunLoop(for: 0.08)

        XCTAssertEqual(controller.debugExactLayoutCount(), beforeScrollExactCount)

        controller.markUserInteraction(false)
        let resumedY = min(
            max(0, controller.totalHeight - viewportSize.height),
            targetY + 1
        )
        view.restoreScrollPosition(CGPoint(x: 0, y: resumedY))
        drainMainRunLoop(for: 0.25)

        XCTAssertGreaterThan(controller.debugExactLayoutCount(), beforeScrollExactCount)

        view.controller = nil
        drainMainRunLoop(for: 0.05)
    }

    func testRenderItemDuringActiveScrollDoesNotForceExactHydration() {
        let controller = makeSeededController(messageCount: 260, width: viewportSize.width)
        let view = VVChatTimelineView(frame: CGRect(origin: .zero, size: viewportSize))
        view.controller = controller
        view.layoutSubtreeIfNeeded()
        drainMainRunLoop(for: 0.2)

        let targetY = max(0, min(controller.totalHeight - viewportSize.height, controller.totalHeight * 0.45))
        controller.markUserInteraction(true)
        view.restoreScrollPosition(CGPoint(x: 0, y: targetY))
        drainMainRunLoop(for: 0.05)

        let beforeExactCount = controller.debugExactLayoutCount()
        let visibleRect = view.viewportRect
        for index in controller.visibleLayoutRange(in: visibleRect, overscan: 420) {
            _ = view.renderItem(at: index, visibleRect: visibleRect)
        }

        XCTAssertEqual(controller.debugExactLayoutCount(), beforeExactCount)

        controller.markUserInteraction(false)
        view.controller = nil
        drainMainRunLoop(for: 0.05)
    }

    func testStreamingDraftUpdatesReuseIncrementalPreparedState() {
        let controller = VVChatTimelineController(style: .init(), renderWidth: viewportSize.width)
        let draftID = controller.beginStreamingAssistantMessage(content: "")

        for step in 1...24 {
            controller.updateDraftMessage(
                id: draftID,
                content: streamedMarkdown(step: step, cycle: "incremental"),
                throttle: false
            )
        }

        let snapshot = controller.debugSnapshot()
        XCTAssertGreaterThan(snapshot.draftPreparedStateCount, 0)
        XCTAssertGreaterThan(snapshot.incrementalDraftReuseCount, 0)
        XCTAssertGreaterThan(snapshot.incrementalDraftLayoutPassCount, 0)
    }

    func testStreamingDraftLayoutPassKeepsRenderedCacheColdUntilVisibleRender() {
        let controller = VVChatTimelineController(style: .init(), renderWidth: viewportSize.width)
        let draftID = controller.beginStreamingAssistantMessage(content: "")

        for step in 1...12 {
            controller.updateDraftMessage(
                id: draftID,
                content: streamedMarkdown(step: step, cycle: "cold-render-cache"),
                throttle: false
            )
        }

        let beforeVisibleRender = controller.debugSnapshot()
        XCTAssertEqual(beforeVisibleRender.renderedMessageCacheCount, 0)
        XCTAssertGreaterThan(beforeVisibleRender.draftPreparedStateCount, 0)

        let visibleRect = CGRect(x: 0, y: 0, width: viewportSize.width, height: viewportSize.height)
        _ = controller.sceneArtifacts(at: controller.layoutCount - 1, visibleRect: visibleRect)
        let afterVisibleRender = controller.debugSnapshot()
        XCTAssertGreaterThan(afterVisibleRender.renderedMessageCacheCount, 0)
    }

    func testLongRenderedMessageProvidesVisiblePrimitiveSubset() {
        let controller = VVChatTimelineController(style: .init(), renderWidth: viewportSize.width)
        controller.appendMessage(
            VVChatMessage(
                id: "long-message",
                role: .assistant,
                state: .final,
                content: longMessageContent(paragraphCount: 220)
            )
        )

        guard let rendered = controller.renderedMessage(at: 0) else {
            XCTFail("Expected rendered message")
            return
        }

        let localVisibleRect = CGRect(x: 0, y: 0, width: viewportSize.width, height: viewportSize.height)
        guard let fullArtifacts = controller.sceneArtifacts(at: 0, visibleRect: nil),
              let visibleArtifacts = controller.sceneArtifacts(at: 0, visibleRect: localVisibleRect) else {
            XCTFail("Expected scene artifacts")
            return
        }

        XCTAssertGreaterThan(rendered.height, localVisibleRect.height)
        XCTAssertGreaterThan(fullArtifacts.scene.primitives.count, visibleArtifacts.scene.primitives.count)
        XCTAssertGreaterThan(visibleArtifacts.scene.primitives.count, 0)
    }

    func testLongRenderedMessageSeparatesChromeAndContentArtifacts() {
        let controller = VVChatTimelineController(style: .init(), renderWidth: viewportSize.width)
        controller.appendMessage(
            VVChatMessage(
                id: "long-message-layers",
                role: .assistant,
                state: .final,
                content: longMessageContent(paragraphCount: 220)
            )
        )

        let localVisibleRect = CGRect(x: 0, y: 0, width: viewportSize.width, height: viewportSize.height)
        guard let rendered = controller.renderedMessage(at: 0),
              let fullContentArtifacts = controller.contentSceneArtifacts(at: 0, visibleRect: nil),
              let visibleContentArtifacts = controller.contentSceneArtifacts(at: 0, visibleRect: localVisibleRect),
              let fullArtifacts = controller.sceneArtifacts(at: 0, visibleRect: nil) else {
            XCTFail("Expected layered scene artifacts")
            return
        }

        XCTAssertGreaterThan(fullContentArtifacts.scene.primitives.count, visibleContentArtifacts.scene.primitives.count)
        XCTAssertEqual(
            fullArtifacts.scene.primitives.count,
            rendered.chromeScene.primitives.count + fullContentArtifacts.scene.primitives.count
        )
    }

    func testLargeMessageReuseAfterRenderedInvalidationAvoidsReparse() {
        let renderer = VVChatMessageRenderer(style: .init(), contentWidth: viewportSize.width)
        let message = VVChatMessage(
            id: "reuse-large-message",
            role: .assistant,
            state: .final,
            content: longMessageContent(paragraphCount: 260)
        )

        _ = renderer.renderedMessage(for: message)
        let first = renderer.debugSnapshot()
        renderer.invalidateRendered(messageID: message.id)
        _ = renderer.renderedMessage(for: message)
        let second = renderer.debugSnapshot()

        XCTAssertEqual(second.markdownParseCount, first.markdownParseCount)
        XCTAssertEqual(second.markdownLayoutCount, first.markdownLayoutCount)
        XCTAssertEqual(second.markdownSceneBuildCount, first.markdownSceneBuildCount)
        XCTAssertGreaterThan(second.preparedMarkdownCacheHits, first.preparedMarkdownCacheHits)
        XCTAssertEqual(second.preparedMarkdownCacheMisses, first.preparedMarkdownCacheMisses)
    }

    func testImageSizeRelayoutReusesPreparedMarkdownLayout() {
        let renderer = VVChatMessageRenderer(style: .init(), contentWidth: viewportSize.width)
        let url = "https://example.com/hero.png"
        let message = VVChatMessage(
            id: "image-large-message",
            role: .assistant,
            state: .final,
            content: largeImageMessageContent(url: url, paragraphCount: 80)
        )

        _ = renderer.renderedMessage(for: message)
        let firstSnapshot = renderer.debugSnapshot()

        XCTAssertTrue(renderer.updateImageSize(url: url, size: CGSize(width: 1400, height: 900)))
        renderer.invalidateRendered(messageID: message.id)
        let second = renderer.renderedMessage(for: message)
        let secondSnapshot = renderer.debugSnapshot()

        XCTAssertEqual(secondSnapshot.markdownParseCount, firstSnapshot.markdownParseCount)
        XCTAssertGreaterThan(secondSnapshot.preparedMarkdownCacheHits, firstSnapshot.preparedMarkdownCacheHits)
        XCTAssertEqual(secondSnapshot.preparedMarkdownCacheMisses, firstSnapshot.preparedMarkdownCacheMisses)
        XCTAssertTrue(
            secondSnapshot.incrementalImageLayoutPassCount > firstSnapshot.incrementalImageLayoutPassCount ||
            secondSnapshot.markdownLayoutCount > firstSnapshot.markdownLayoutCount
        )
        let fullArtifacts = renderer.sceneArtifacts(for: message, rendered: second, visibleRect: nil)
        let finalSnapshot = renderer.debugSnapshot()
        XCTAssertGreaterThan(finalSnapshot.markdownSceneBuildCount, firstSnapshot.markdownSceneBuildCount)
        XCTAssertGreaterThan(fullArtifacts.scene.primitives.count, 0)
    }

    func testVisibleSceneBuildDoesNotRequireResidentFullPreparedLayout() {
        let renderer = VVChatMessageRenderer(style: .init(), contentWidth: viewportSize.width)
        let message = VVChatMessage(
            id: "windowed-layout-message",
            role: .assistant,
            state: .final,
            content: longMessageContent(paragraphCount: 260)
        )

        let rendered = renderer.renderedMessage(for: message)
        let afterRender = renderer.debugSnapshot()
        XCTAssertEqual(afterRender.materializedPreparedLayoutCount, 0)

        let visibleRect = CGRect(x: 0, y: 0, width: viewportSize.width, height: viewportSize.height)
        let artifacts = renderer.contentSceneArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
        let afterVisibleScene = renderer.debugSnapshot()

        XCTAssertNotNil(artifacts)
        XCTAssertGreaterThan(artifacts?.scene.primitives.count ?? 0, 0)
        XCTAssertEqual(afterVisibleScene.materializedPreparedLayoutCount, 0)
        XCTAssertGreaterThan(afterVisibleScene.markdownWindowLayoutCount, afterRender.markdownWindowLayoutCount)
    }

    func testSelectionHelperDoesNotRetainPreparedFullLayout() {
        let renderer = VVChatMessageRenderer(style: .init(), contentWidth: viewportSize.width)
        let message = VVChatMessage(
            id: "selection-window-message",
            role: .assistant,
            state: .final,
            content: longMessageContent(paragraphCount: 180)
        )

        let rendered = renderer.renderedMessage(for: message)
        XCTAssertEqual(renderer.debugSnapshot().materializedPreparedLayoutCount, 0)

        let helper = renderer.selectionHelper(for: message, rendered: rendered)
        let snapshot = renderer.debugSnapshot()

        XCTAssertNotNil(helper)
        XCTAssertEqual(snapshot.materializedPreparedLayoutCount, 0)
    }

    func testVisibleSelectionArtifactsUseBlockSubsetForLongMessage() {
        let renderer = VVChatMessageRenderer(style: .init(), contentWidth: viewportSize.width)
        let message = VVChatMessage(
            id: "selection-visible-window-message",
            role: .assistant,
            state: .final,
            content: longMessageContent(paragraphCount: 220)
        )

        let rendered = renderer.renderedMessage(for: message)
        let visibleRect = CGRect(x: 0, y: 0, width: viewportSize.width, height: viewportSize.height)
        let visibleArtifacts = renderer.selectionArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
        let fullArtifacts = renderer.selectionArtifacts(for: message, rendered: rendered, visibleRect: nil)

        XCTAssertNotNil(visibleArtifacts)
        XCTAssertNotNil(fullArtifacts)
        XCTAssertLessThan(visibleArtifacts?.helper.layout.blocks.count ?? 0, fullArtifacts?.helper.layout.blocks.count ?? 0)
        XCTAssertLessThan(visibleArtifacts?.blockRange.count ?? 0, fullArtifacts?.blockRange.count ?? 0)
    }

    func testVisibleSelectionArtifactsDoNotMaterializeResidentFullPreparedLayout() {
        let renderer = VVChatMessageRenderer(style: .init(), contentWidth: viewportSize.width)
        let message = VVChatMessage(
            id: "selection-visible-no-full-layout",
            role: .assistant,
            state: .final,
            content: longMessageContent(paragraphCount: 220)
        )

        let rendered = renderer.renderedMessage(for: message)
        XCTAssertEqual(renderer.debugSnapshot().materializedPreparedLayoutCount, 0)

        let visibleRect = CGRect(x: 0, y: 0, width: viewportSize.width, height: viewportSize.height)
        let visibleArtifacts = renderer.selectionArtifacts(for: message, rendered: rendered, visibleRect: visibleRect)
        let snapshot = renderer.debugSnapshot()

        XCTAssertNotNil(visibleArtifacts)
        XCTAssertGreaterThan(visibleArtifacts?.blockRange.count ?? 0, 0)
        XCTAssertEqual(snapshot.materializedPreparedLayoutCount, 0)
    }

    func testVisibleSelectionArtifactsMatchFullSelectionRectsForSameWindow() throws {
        let renderer = VVChatMessageRenderer(style: .init(), contentWidth: viewportSize.width)
        let message = VVChatMessage(
            id: "selection-visible-window-regression",
            role: .assistant,
            state: .final,
            content: """
            I inspected the Aizen timeline and rebuilt this transcript with the same VVDevKit presentation model:

            - user messages stay in timestamped bubbles
            - assistant output renders as an open lane
            - tool work collapses into grouped rows with per-call detail
            - completed turns end with a summary card
            """
        )

        let rendered = renderer.renderedMessage(for: message)
        let visibleRect = CGRect(x: 0, y: 0, width: viewportSize.width, height: 260)
        let fullArtifacts = try XCTUnwrap(renderer.selectionArtifacts(for: message, rendered: rendered, visibleRect: nil))
        let visibleArtifacts = try XCTUnwrap(renderer.selectionArtifacts(for: message, rendered: rendered, visibleRect: visibleRect))
        let localStart = try XCTUnwrap(visibleArtifacts.helper.findFirstPosition())
        let localEnd = try XCTUnwrap(visibleArtifacts.helper.findLastPosition())

        let absoluteStart = MarkdownTextPosition(
            blockIndex: visibleArtifacts.blockRange.lowerBound + localStart.blockIndex,
            runIndex: localStart.runIndex,
            characterOffset: localStart.characterOffset
        )
        let absoluteEnd = MarkdownTextPosition(
            blockIndex: visibleArtifacts.blockRange.lowerBound + localEnd.blockIndex,
            runIndex: localEnd.runIndex,
            characterOffset: localEnd.characterOffset
        )

        let fullRects = fullArtifacts.helper.selectionRects(
            from: absoluteStart,
            to: absoluteEnd,
            visibleYRange: visibleRect.minY...visibleRect.maxY
        )
        let visibleRects = visibleArtifacts.helper.selectionRects(
            from: localStart,
            to: localEnd,
            visibleYRange: visibleRect.minY...visibleRect.maxY
        )

        XCTAssertEqual(visibleRects.count, fullRects.count)
        for (visible, full) in zip(visibleRects, fullRects) {
            XCTAssertEqual(visible.minX, full.minX, accuracy: 1.5)
            XCTAssertEqual(visible.minY, full.minY, accuracy: 1.5)
            XCTAssertEqual(visible.width, full.width, accuracy: 1.5)
            XCTAssertEqual(visible.height, full.height, accuracy: 1.5)
        }
    }

    func testLargeRenderedMessagesRespectCacheCostBudgets() {
        let renderer = VVChatMessageRenderer(style: .init(), contentWidth: viewportSize.width)

        for index in 0..<18 {
            let message = VVChatMessage(
                id: "huge-message-\(index)",
                role: .assistant,
                state: .final,
                content: longMessageContent(paragraphCount: 220)
            )
            let rendered = renderer.renderedMessage(for: message)
            _ = renderer.sceneArtifacts(for: message, rendered: rendered, visibleRect: nil)
        }

        let snapshot = renderer.debugSnapshot()
        XCTAssertGreaterThan(snapshot.preparedMarkdownCacheEstimatedCost, 0)
        XCTAssertGreaterThan(snapshot.sceneWindowCacheEstimatedCost, 0)
        XCTAssertLessThanOrEqual(snapshot.materializedPreparedLayoutEstimatedCost, snapshot.materializedPreparedLayoutCostLimit)
        XCTAssertLessThanOrEqual(snapshot.preparedMarkdownCacheEstimatedCost, snapshot.preparedMarkdownCacheCostLimit)
        XCTAssertLessThanOrEqual(snapshot.sceneWindowCacheEstimatedCost, snapshot.sceneWindowCacheCostLimit)
    }

    func testLargeRenderedMessagesDematerializeColdPreparedLayouts() {
        let renderer = VVChatMessageRenderer(style: .init(), contentWidth: viewportSize.width)

        for index in 0..<18 {
            let message = VVChatMessage(
                id: "cold-layout-message-\(index)",
                role: .assistant,
                state: .final,
                content: longMessageContent(paragraphCount: 220)
            )
            _ = renderer.renderedMessage(for: message)
        }

        let snapshot = renderer.debugSnapshot()
        XCTAssertGreaterThan(snapshot.preparedMarkdownCacheCount, 0)
        XCTAssertLessThan(snapshot.materializedPreparedLayoutCount, snapshot.preparedMarkdownCacheCount)
    }

    func testRenderedMessageCacheRespectsCostBudget() {
        let renderer = VVChatMessageRenderer(style: .init(), contentWidth: viewportSize.width)

        for index in 0..<140 {
            let message = VVChatMessage(
                id: "rendered-cache-\(index)",
                role: index.isMultiple(of: 2) ? .assistant : .user,
                state: .final,
                content: seededMessage(index: index) + "\n\n" + longMessageContent(paragraphCount: 12)
            )
            _ = renderer.renderedMessage(for: message)
        }

        let snapshot = renderer.debugSnapshot()
        XCTAssertGreaterThan(snapshot.renderedMessageCacheCount, 0)
        XCTAssertLessThanOrEqual(snapshot.renderedMessageCacheEstimatedCost, snapshot.renderedMessageCacheCostLimit)
    }

    func testTrimCachesDropsOffscreenChatArtifacts() {
        let controller = makeSeededController(messageCount: 160, width: viewportSize.width)
        for index in 0..<controller.layoutCount {
            _ = controller.renderedMessage(at: index)
            _ = controller.contentSceneArtifacts(at: index, visibleRect: nil)
        }

        let before = controller.debugSnapshot()
        XCTAssertGreaterThan(before.renderedMessageCacheCount, 0)
        XCTAssertGreaterThan(before.preparedMarkdownCacheCount, 0)

        let viewport = CGRect(
            x: 0,
            y: max(0, controller.totalHeight - viewportSize.height),
            width: viewportSize.width,
            height: viewportSize.height
        )
        controller.trimCaches(in: viewport, overscan: 900, itemPadding: 8)
        let after = controller.debugSnapshot()

        XCTAssertLessThan(after.renderedMessageCacheCount, before.renderedMessageCacheCount)
        XCTAssertLessThan(after.preparedMarkdownCacheCount, before.preparedMarkdownCacheCount)
        XCTAssertLessThanOrEqual(after.sceneWindowCacheEstimatedCost, before.sceneWindowCacheEstimatedCost)
    }

    func testRepeatedStreamingMemoryStabilizesAfterWarmCaches() {
        let style = VVChatTimelineStyle()
        let second = profileStreamingCycle(style: style, messageCount: 180, steps: 180, label: "second")
        let third = profileStreamingCycle(style: style, messageCount: 180, steps: 180, label: "third")

        let slack: UInt64 = 12 * 1024 * 1024
        XCTAssertLessThanOrEqual(third.retainedGrowth, second.retainedGrowth + slack)
        XCTAssertLessThanOrEqual(third.peakGrowth, second.peakGrowth + slack)
    }

    func testLayoutAnimationSnapshotsStayBoundedToVisibleWindow() {
        let controller = makeSeededController(messageCount: 320, width: viewportSize.width)
        let view = VVChatTimelineView(frame: CGRect(origin: .zero, size: viewportSize))
        view.controller = controller
        view.layoutSubtreeIfNeeded()
        drainMainRunLoop(for: 0.25)

        let newMessage = VVChatMessage(
            id: "snapshot-bounded-message",
            role: .assistant,
            state: .final,
            content: longMessageContent(paragraphCount: 18)
        )
        controller.appendMessage(newMessage)
        drainMainRunLoop(for: 0.1)

        let visibleCount = max(view.debugVisibleRenderCount(), 1)
        let snapshotCount = view.debugLayoutSnapshotCount()

        XCTAssertLessThan(snapshotCount, controller.layoutCount)
        XCTAssertLessThanOrEqual(snapshotCount, visibleCount + 64)

        view.controller = nil
        drainMainRunLoop(for: 0.05)
    }

    func testPinnedViewportStaysAtBottomAcrossManyAppends() {
        let controller = makeSeededController(messageCount: 180, width: viewportSize.width)
        let view = VVChatTimelineView(frame: CGRect(origin: .zero, size: viewportSize))
        view.controller = controller
        view.layoutSubtreeIfNeeded()
        drainMainRunLoop(for: 0.25)
        view.scrollToBottom(animated: false)
        drainMainRunLoop(for: 0.05)

        for index in 0..<24 {
            controller.appendMessage(
                VVChatMessage(
                    id: "append-\(index)",
                    role: .assistant,
                    state: .final,
                    content: longMessageContent(paragraphCount: 4)
                )
            )
            drainMainRunLoop(for: 0.04)
        }

        let maxOffset = max(0, controller.totalHeight - viewportSize.height)
        let visibleOrigin = view.viewportRect.origin.y

        XCTAssertTrue(controller.state.isPinnedToBottom)
        XCTAssertEqual(visibleOrigin, maxOffset, accuracy: 2.0)

        view.controller = nil
        drainMainRunLoop(for: 0.05)
    }

    func testPinnedTailAppendStartsLocalLayoutAnimationWithoutScrollAnimation() {
        let controller = makeSeededController(messageCount: 180, width: viewportSize.width)
        let view = VVChatTimelineView(frame: CGRect(origin: .zero, size: viewportSize))
        view.controller = controller
        view.layoutSubtreeIfNeeded()
        drainMainRunLoop(for: 0.25)
        view.scrollToBottom(animated: false)
        drainMainRunLoop(for: 0.05)

        controller.appendMessage(
            VVChatMessage(
                id: "tail-append-animation-check",
                role: .assistant,
                state: .final,
                content: longMessageContent(paragraphCount: 8)
            )
        )
        drainMainRunLoop(for: 0.05)

        XCTAssertTrue(view.debugIsLayoutAnimating())
        XCTAssertFalse(view.debugIsScrollAnimating())

        view.controller = nil
        drainMainRunLoop(for: 0.05)
    }

    func testPinnedTailAppendUsesExplicitLayoutTransitionWithoutViewportAnimation() {
        let controller = makeSeededController(messageCount: 180, width: viewportSize.width)
        let view = VVChatTimelineView(frame: CGRect(origin: .zero, size: viewportSize))
        view.controller = controller
        view.layoutSubtreeIfNeeded()
        drainMainRunLoop(for: 0.25)
        view.scrollToBottom(animated: false)
        drainMainRunLoop(for: 0.05)

        if let anchorID = controller.entries.last?.id {
            controller.prepareLayoutTransition(anchorItemID: anchorID)
        }
        controller.appendMessage(
            VVChatMessage(
                id: "tail-append-explicit-transition",
                role: .assistant,
                state: .final,
                content: longMessageContent(paragraphCount: 8)
            )
        )
        drainMainRunLoop(for: 0.05)

        XCTAssertTrue(view.debugIsLayoutAnimating())
        XCTAssertFalse(view.debugIsScrollAnimating())

        view.controller = nil
        drainMainRunLoop(for: 0.05)
    }

    func testPinnedTailRangeReplacementUsesLocalLayoutTransitionWithoutViewportAnimation() {
        let controller = makeSeededController(messageCount: 180, width: viewportSize.width)
        let view = VVChatTimelineView(frame: CGRect(origin: .zero, size: viewportSize))
        view.controller = controller
        view.layoutSubtreeIfNeeded()
        drainMainRunLoop(for: 0.25)
        view.scrollToBottom(animated: false)
        drainMainRunLoop(for: 0.05)

        let groupID = "tail-tool-group"
        let detailID = "\(groupID)::detail"

        if let anchorID = controller.entries.last?.id {
            controller.prepareLayoutTransition(anchorItemID: anchorID)
        }
        controller.replaceEntries(
            in: controller.entries.count..<controller.entries.count,
            with: [
                .custom(VVCustomTimelineEntry(id: groupID, kind: "toolCallGroup", payload: Data("group".utf8), revision: 1)),
                .custom(VVCustomTimelineEntry(id: detailID, kind: "toolCallDetail", payload: Data("detail".utf8), revision: 1))
            ],
            scrollToBottom: true,
            markUnread: false
        )
        drainMainRunLoop(for: 0.05)

        controller.prepareLayoutTransition(anchorItemID: groupID)
        controller.replaceEntries(
            in: (controller.entries.count - 2)..<controller.entries.count,
            with: [
                .custom(VVCustomTimelineEntry(id: groupID, kind: "toolCallGroup", payload: Data("group updated".utf8), revision: 2)),
                .custom(VVCustomTimelineEntry(id: detailID, kind: "toolCallDetail", payload: Data("detail updated".utf8), revision: 2))
            ],
            scrollToBottom: true,
            markUnread: false
        )
        drainMainRunLoop(for: 0.05)

        let maxOffset = max(0, controller.totalHeight - viewportSize.height)
        XCTAssertTrue(view.debugIsLayoutAnimating())
        XCTAssertFalse(view.debugIsScrollAnimating())
        XCTAssertEqual(view.viewportRect.origin.y, maxOffset, accuracy: 2.0)

        view.controller = nil
        drainMainRunLoop(for: 0.05)
    }

    func testRenderItemUsesAnimatedSnapshotFrameDuringPinnedTailAnimation() {
        let controller = makeSeededController(messageCount: 180, width: viewportSize.width)
        let view = VVChatTimelineView(frame: CGRect(origin: .zero, size: viewportSize))
        view.controller = controller
        view.layoutSubtreeIfNeeded()
        drainMainRunLoop(for: 0.25)
        view.scrollToBottom(animated: false)
        drainMainRunLoop(for: 0.05)

        controller.appendMessage(
            VVChatMessage(
                id: "tail-append-animated-frame",
                role: .assistant,
                state: .final,
                content: longMessageContent(paragraphCount: 8)
            )
        )
        drainMainRunLoop(for: 0.05)

        let lastIndex = controller.layoutCount - 1
        let targetFrame = controller.itemLayout(at: lastIndex)?.frame
        let animatedFrame = view.renderItem(at: lastIndex, visibleRect: view.viewportRect)?.frame

        XCTAssertTrue(view.debugIsLayoutAnimating())
        XCTAssertNotNil(targetFrame)
        XCTAssertNotNil(animatedFrame)
        if let targetFrame, let animatedFrame {
            XCTAssertGreaterThan(abs(animatedFrame.minY - targetFrame.minY), 0.5)
        }

        view.controller = nil
        drainMainRunLoop(for: 0.05)
    }

    func testHeadlessVisibleWindowRenderingAcrossLargeTimeline() throws {
        let controller = makeSeededController(messageCount: 420, width: viewportSize.width)
        let harness = try HeadlessSceneStressHarness(
            baseFont: NSFont.systemFont(ofSize: 14),
            viewportSize: viewportSize
        )

        let scrollOffsets = makeScrollOffsets(totalHeight: controller.totalHeight, viewportHeight: viewportSize.height, steps: 10)
        var totalPrimitives = 0
        var primitiveCounts: [Int] = []

        for offset in scrollOffsets {
            let scene = combinedVisibleScene(controller: controller, scrollOffsetY: offset, viewportHeight: viewportSize.height)
            totalPrimitives += scene.primitives.count
            primitiveCounts.append(scene.primitives.count)
            autoreleasepool {
                do {
                    _ = try harness.render(scene: scene, scrollOffset: CGPoint(x: 0, y: offset))
                } catch {
                    XCTFail("Headless timeline render failed at offset \(offset): \(error)")
                }
            }
        }

        XCTAssertGreaterThan(primitiveCounts.min() ?? 0, 240)
        XCTAssertGreaterThan(totalPrimitives, scrollOffsets.count * 360)
    }

    func testZBenchmarkHeadlessVisibleWindowRendering() throws {
        let controller = makeSeededController(messageCount: 320, width: viewportSize.width)
        let harness = try HeadlessSceneStressHarness(
            baseFont: NSFont.systemFont(ofSize: 14),
            viewportSize: viewportSize
        )
        let scrollOffsets = makeScrollOffsets(
            totalHeight: controller.totalHeight,
            viewportHeight: viewportSize.height,
            steps: 5
        )

        measure(metrics: [XCTClockMetric()]) {
            autoreleasepool {
                var renderError: Error?
                for offset in scrollOffsets {
                    let scene = combinedVisibleScene(
                        controller: controller,
                        scrollOffsetY: offset,
                        viewportHeight: viewportSize.height
                    )
                    do {
                        _ = try harness.render(scene: scene, scrollOffset: CGPoint(x: 0, y: offset))
                    } catch {
                        renderError = error
                        break
                    }
                }
                XCTAssertNil(renderError)
            }
        }
    }

    func testZBenchmarkColdControllerRebuildUsesEstimatedLayouts() {
        measure(metrics: [XCTClockMetric()]) {
            autoreleasepool {
                let controller = makeSeededController(messageCount: 420, width: viewportSize.width)
                let snapshot = controller.debugSnapshot()
                XCTAssertEqual(snapshot.renderedMessageCacheCount, 0)
                XCTAssertEqual(snapshot.preparedMarkdownCacheCount, 0)
                XCTAssertEqual(controller.debugExactLayoutCount(), 0)
                XCTAssertGreaterThan(controller.totalHeight, 0)
            }
        }
    }

    func testZBenchmarkHighLoadDraftUpdates() {
        measure(metrics: [XCTClockMetric()]) {
            autoreleasepool {
                let controller = makeSeededController(messageCount: 260, width: viewportSize.width)
                let draftID = controller.beginStreamingAssistantMessage(content: "")
                for step in 0..<110 {
                    controller.updateDraftMessage(
                        id: draftID,
                        content: streamedMarkdown(step: step, cycle: "bench"),
                        throttle: false
                    )
                }
                controller.finalizeMessage(id: draftID, content: streamedMarkdown(step: 110, cycle: "bench-final"))
                XCTAssertGreaterThan(controller.totalHeight, 0)
            }
        }
    }

    private func makeSeededController(messageCount: Int, width: CGFloat) -> VVChatTimelineController {
        let controller = VVChatTimelineController(style: .init(), renderWidth: width)
        for index in 0..<messageCount {
            controller.appendMessage(
                VVChatMessage(
                    id: "seed-\(index)",
                    role: index.isMultiple(of: 3) ? .user : .assistant,
                    state: .final,
                    content: seededMessage(index: index)
                )
            )
        }
        return controller
    }

    private func combinedVisibleScene(
        controller: VVChatTimelineController,
        scrollOffsetY: CGFloat,
        viewportHeight: CGFloat
    ) -> VVScene {
        let overscan: CGFloat = 900
        let minY = scrollOffsetY - overscan
        let maxY = scrollOffsetY + viewportHeight + overscan
        var builder = VVSceneBuilder()

        for index in 0..<controller.layoutCount {
            guard let layout = controller.itemLayout(at: index) else { continue }
            if layout.frame.maxY < minY { continue }
            if layout.frame.minY > maxY { break }
            guard let sceneArtifacts = controller.sceneArtifacts(at: index, visibleRect: nil) else { continue }
            builder.withOffset(CGPoint(x: layout.frame.origin.x + layout.contentOffset.x, y: layout.frame.origin.y + layout.contentOffset.y)) { builder in
                builder.add(node: VVNode.fromScene(sceneArtifacts.scene))
            }
        }

        return builder.scene
    }

    private func profileStreamingCycle(
        style: VVChatTimelineStyle,
        messageCount: Int,
        steps: Int,
        label: String
    ) -> StreamingCycleSample {
        autoreleasepool {
            let controller = VVChatTimelineController(style: style, renderWidth: viewportSize.width)
            let view = VVChatTimelineView(frame: CGRect(origin: .zero, size: viewportSize))
            view.controller = controller

            for index in 0..<messageCount {
                controller.appendMessage(
                    VVChatMessage(
                        id: "\(label)-seed-\(index)",
                        role: index.isMultiple(of: 3) ? .user : .assistant,
                        state: .final,
                        content: seededMessage(index: index)
                    )
                )
            }

            drainMainRunLoop(for: 0.25)
            let baseline = residentMemoryBytes()

            let draftID = controller.beginStreamingAssistantMessage(content: "")
            var peak = baseline

            for step in 0..<steps {
                controller.updateDraftMessage(
                    id: draftID,
                    content: streamedMarkdown(step: step, cycle: label),
                    throttle: false
                )
                drainMainRunLoop(for: 0.008)
                peak = max(peak, residentMemoryBytes())
            }

            controller.finalizeMessage(id: draftID, content: streamedMarkdown(step: steps, cycle: "\(label)-final"))
            drainMainRunLoop(for: 1.0)
            let final = residentMemoryBytes()

            controller.setEntries([], scrollToBottom: false)
            view.controller = nil
            drainMainRunLoop(for: 0.75)

            let sample = StreamingCycleSample(
                baseline: baseline,
                peak: peak,
                final: final
            )

            print(
                """
                chat timeline streaming cycle \(label):
                  baseline_rss_mb=\(formatMB(sample.baseline))
                  peak_rss_mb=\(formatMB(sample.peak))
                  final_rss_mb=\(formatMB(sample.final))
                  peak_growth_mb=\(formatMB(sample.peakGrowth))
                  retained_growth_mb=\(formatMB(sample.retainedGrowth))
                """
            )

            return sample
        }
    }

    private func makeScrollOffsets(totalHeight: CGFloat, viewportHeight: CGFloat, steps: Int) -> [CGFloat] {
        let maxOffset = max(0, totalHeight - viewportHeight)
        guard maxOffset > 0 else { return [0] }
        let count = max(1, steps)
        let stride = maxOffset / CGFloat(count)
        return (0...count).map { min(maxOffset, CGFloat($0) * stride) }
    }

    private func drainMainRunLoop(for duration: TimeInterval) {
        let until = Date().addingTimeInterval(duration)
        while Date() < until {
            RunLoop.main.run(mode: .default, before: min(until, Date().addingTimeInterval(0.01)))
        }
    }

    private func seededMessage(index: Int) -> String {
        """
        ## Seed \(index)

        This is seeded timeline content to make layout snapshots, rendered message caches, and markdown scenes more realistic.

        - first item
        - second item
        - third item

        ```swift
        let value = \(index)
        print(value)
        ```
        """
    }

    private func streamedMarkdown(step: Int, cycle: String) -> String {
        var text = """
        ## Streaming Turn \(cycle)

        The assistant is producing a long answer while tool work is happening in the background.

        """

        for row in 0...step {
            text += "- streamed bullet \(row): rendering should stay stable while memory does not grow without bound.\n"
            if row.isMultiple(of: 16) {
                text += "\n```swift\nlet row\(row) = \(row)\nprint(row\(row))\n```\n\n"
            }
        }

        return text
    }

    private func longMessageContent(paragraphCount: Int) -> String {
        var text = """
        ## Long Message

        This message is intentionally large so the timeline renderer has to deal with many markdown blocks, text runs, and code rows in a single item.

        """

        for index in 0..<paragraphCount {
            text += """
            Paragraph \(index): the renderer should only draw the primitives that intersect the local viewport instead of traversing the entire message scene every frame.

            ```swift
            let value\(index) = BenchmarkRenderer.render(row: \(index), width: 480, theme: .dark)
            print(value\(index))
            ```

            """
        }

        return text
    }

    private func largeImageMessageContent(url: String, paragraphCount: Int) -> String {
        var text = """
        ## Large Image Message

        ![](\(url))

        """

        for index in 0..<paragraphCount {
            text += """
            Paragraph \(index): the image above should relayout in place without reparsing the whole markdown message every time an image size arrives.

            """
        }

        return text
    }

    private func residentMemoryBytes() -> UInt64 {
        var info = task_vm_info_data_t()
        var count = mach_msg_type_number_t(MemoryLayout.size(ofValue: info) / MemoryLayout<natural_t>.size)
        let result = withUnsafeMutablePointer(to: &info) { pointer -> kern_return_t in
            pointer.withMemoryRebound(to: integer_t.self, capacity: Int(count)) { rebound in
                task_info(mach_task_self_, task_flavor_t(TASK_VM_INFO), rebound, &count)
            }
        }
        guard result == KERN_SUCCESS else { return 0 }
        return info.phys_footprint
    }

    private func formatMB(_ bytes: UInt64) -> String {
        String(format: "%.1f", Double(bytes) / 1_048_576.0)
    }
}

private struct StreamingCycleSample {
    let baseline: UInt64
    let peak: UInt64
    let final: UInt64

    var peakGrowth: UInt64 {
        max(0, peak - baseline)
    }

    var retainedGrowth: UInt64 {
        max(0, final - baseline)
    }
}
