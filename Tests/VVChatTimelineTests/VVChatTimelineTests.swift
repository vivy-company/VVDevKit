import XCTest
import AppKit
@testable import VVChatTimeline
import Darwin.Mach

@MainActor
final class VVChatTimelineTests: XCTestCase {
    func testPinnedStateUpdate() {
        var state = VVChatTimelineState(isPinnedToBottom: true, userIsInteracting: false, hasUnreadNewContent: false, pinThreshold: 24)
        // Pinned state should detach quickly as user scrolls up from bottom.
        state.updatePinnedState(distanceFromBottom: 10)
        XCTAssertFalse(state.isPinnedToBottom)
        // Once detached, repin when close enough to bottom.
        state.updatePinnedState(distanceFromBottom: 5)
        XCTAssertTrue(state.isPinnedToBottom)
        state.updatePinnedState(distanceFromBottom: 30)
        XCTAssertFalse(state.isPinnedToBottom)
    }

    func testUnreadFlagWhenNotPinned() {
        let controller = VVChatTimelineController(style: .init(), renderWidth: 320)
        controller.updatePinnedState(distanceFromBottom: 200)
        controller.appendMessage(VVChatMessage(role: .user, state: .final, content: "Hello"))
        XCTAssertTrue(controller.state.hasUnreadNewContent)
    }

    func testDraftUpdateChangesRevision() {
        let controller = VVChatTimelineController(style: .init(), renderWidth: 320)
        let id = controller.beginStreamingAssistantMessage(content: "Hi")
        let before = controller.messages.first(where: { $0.id == id })?.revision ?? 0
        controller.updateDraftMessage(id: id, content: "Hi there", throttle: false)
        let after = controller.messages.first(where: { $0.id == id })?.revision ?? 0
        XCTAssertGreaterThan(after, before)
    }

    func testImageUpdateDoesNotSetUnread() {
        let controller = VVChatTimelineController(style: .init(), renderWidth: 320)
        controller.appendMessage(VVChatMessage(role: .assistant, state: .final, content: "![alt](file:///tmp/test.png)"))
        controller.updatePinnedState(distanceFromBottom: 200)
        XCTAssertFalse(controller.state.hasUnreadNewContent)
        controller.updateImageSize(url: "file:///tmp/test.png", size: CGSize(width: 120, height: 80))
        XCTAssertFalse(controller.state.hasUnreadNewContent)
    }

    func testDraftUpdateDoesNotAutoFollowWhileUserInteracting() {
        let controller = VVChatTimelineController(style: .init(), renderWidth: 320)
        var updates: [VVChatTimelineController.Update] = []
        controller.onUpdate = { updates.append($0) }

        let id = controller.beginStreamingAssistantMessage(content: "hello")
        controller.markUserInteraction(true)
        controller.updateDraftMessage(id: id, content: "hello world", throttle: false)

        XCTAssertEqual(updates.last?.shouldScrollToBottom, false)
    }

    func testFinalizeCancelsPendingThrottledDraftUpdate() {
        let controller = VVChatTimelineController(style: .init(), renderWidth: 320)
        let id = controller.beginStreamingAssistantMessage(content: "h")

        controller.updateDraftMessage(id: id, content: "hello", throttle: true)
        controller.finalizeMessage(id: id, content: "final")

        let flushed = expectation(description: "pending throttled updates flushed")
        DispatchQueue.main.asyncAfter(deadline: .now() + 0.08) {
            flushed.fulfill()
        }
        wait(for: [flushed], timeout: 1.0)

        let message = controller.messages.first(where: { $0.id == id })
        XCTAssertEqual(message?.state, .final)
        XCTAssertEqual(message?.content, "final")
    }

    func testAppendToDraftMessageAppendsChunk() {
        let controller = VVChatTimelineController(style: .init(), renderWidth: 320)
        let id = controller.beginStreamingAssistantMessage(content: "Hello")

        controller.appendToDraftMessage(id: id, chunk: " world", throttle: false)
        controller.appendToDraftMessage(id: id, chunk: "!", throttle: false)

        let message = controller.messages.first(where: { $0.id == id })
        XCTAssertEqual(message?.content, "Hello world!")
        XCTAssertEqual(message?.state, .draft)
    }

    func testStreamingMemoryProfile() {
        let style = VVChatTimelineStyle()
        let controller = VVChatTimelineController(style: style, renderWidth: 900)
        let view = VVChatTimelineView(frame: CGRect(x: 0, y: 0, width: 900, height: 700))
        view.controller = controller

        for index in 0..<120 {
            controller.appendMessage(
                VVChatMessage(
                    id: "seed-\(index)",
                    role: index.isMultiple(of: 3) ? .user : .assistant,
                    state: .final,
                    content: seededMessage(index: index)
                )
            )
        }

        drainMainRunLoop(for: 0.25)
        let baselineRSS = residentMemoryBytes()

        let draftID = controller.beginStreamingAssistantMessage(content: "")
        var peakRSS = baselineRSS

        for step in 0..<220 {
            controller.updateDraftMessage(
                id: draftID,
                content: streamedMarkdown(step: step),
                throttle: false
            )
            drainMainRunLoop(for: 0.01)
            peakRSS = max(peakRSS, residentMemoryBytes())
        }

        controller.finalizeMessage(id: draftID, content: streamedMarkdown(step: 220))
        drainMainRunLoop(for: 2.0)
        let finalRSS = residentMemoryBytes()

        controller.setEntries([], scrollToBottom: false)
        view.controller = nil
        drainMainRunLoop(for: 2.0)
        let clearedRSS = residentMemoryBytes()

        let secondController = VVChatTimelineController(style: style, renderWidth: 900)
        let secondView = VVChatTimelineView(frame: CGRect(x: 0, y: 0, width: 900, height: 700))
        secondView.controller = secondController
        for index in 0..<120 {
            secondController.appendMessage(
                VVChatMessage(
                    id: "seed2-\(index)",
                    role: index.isMultiple(of: 3) ? .user : .assistant,
                    state: .final,
                    content: seededMessage(index: index)
                )
            )
        }
        drainMainRunLoop(for: 0.25)
        let secondBaselineRSS = residentMemoryBytes()
        let secondDraftID = secondController.beginStreamingAssistantMessage(content: "")
        var secondPeakRSS = secondBaselineRSS
        for step in 0..<220 {
            secondController.updateDraftMessage(
                id: secondDraftID,
                content: streamedMarkdown(step: step),
                throttle: false
            )
            drainMainRunLoop(for: 0.01)
            secondPeakRSS = max(secondPeakRSS, residentMemoryBytes())
        }
        secondController.finalizeMessage(id: secondDraftID, content: streamedMarkdown(step: 220))
        drainMainRunLoop(for: 2.0)
        let secondFinalRSS = residentMemoryBytes()

        print(
            """
            chat timeline memory profile:
              baseline_rss_mb=\(formatMB(baselineRSS))
              peak_rss_mb=\(formatMB(peakRSS))
              final_rss_mb=\(formatMB(finalRSS))
              cleared_rss_mb=\(formatMB(clearedRSS))
              peak_growth_mb=\(formatMB(peakRSS - baselineRSS))
              retained_growth_mb=\(formatMB(max(0, finalRSS - baselineRSS)))
              post_clear_growth_mb=\(formatMB(max(0, clearedRSS - baselineRSS)))
              second_baseline_rss_mb=\(formatMB(secondBaselineRSS))
              second_peak_rss_mb=\(formatMB(secondPeakRSS))
              second_final_rss_mb=\(formatMB(secondFinalRSS))
              second_peak_growth_mb=\(formatMB(max(0, secondPeakRSS - secondBaselineRSS)))
              second_retained_growth_mb=\(formatMB(max(0, secondFinalRSS - secondBaselineRSS)))
            """
        )

        XCTAssertGreaterThanOrEqual(peakRSS, baselineRSS)
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

    private func streamedMarkdown(step: Int) -> String {
        var text = """
        ## Streaming Turn

        The assistant is producing a long answer while tool work is happening in the background.

        """

        for row in 0...step {
            text += "- streamed bullet \(row): rendering should stay stable while memory does not grow without bound.\n"
            if row.isMultiple(of: 18) {
                text += "\n```swift\nlet row\(row) = \(row)\nprint(row\(row))\n```\n\n"
            }
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

final class VVChatDraftThrottlerTests: XCTestCase {
    func testThrottlerCoalescesUpdates() {
        let expectation = expectation(description: "flush")
        let throttler = VVChatDraftThrottler(interval: 0.02, queue: .main)
        var received: [String] = []
        throttler.schedule("a") { received.append($0) }
        throttler.schedule("ab") { received.append($0) }
        throttler.schedule("abc") { received.append($0) }

        DispatchQueue.main.asyncAfter(deadline: .now() + 0.06) {
            expectation.fulfill()
        }

        wait(for: [expectation], timeout: 1.0)
        XCTAssertEqual(received, ["abc"])
    }
}
