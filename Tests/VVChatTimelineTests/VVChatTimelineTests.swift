import XCTest
@testable import VVChatTimeline

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
