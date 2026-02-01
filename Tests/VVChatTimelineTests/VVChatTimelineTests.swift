import XCTest
@testable import VVChatTimeline

@MainActor
final class VVChatTimelineTests: XCTestCase {
    func testPinnedStateUpdate() {
        var state = VVChatTimelineState(isPinnedToBottom: true, userIsInteracting: false, hasUnreadNewContent: false, pinThreshold: 24)
        state.updatePinnedState(distanceFromBottom: 10)
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
