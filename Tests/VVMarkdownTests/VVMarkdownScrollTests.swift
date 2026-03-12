import XCTest
@testable import VVMarkdown

#if canImport(AppKit)
final class VVMarkdownScrollTests: XCTestCase {
    func testPreciseScrollDeltaPassesThrough() {
        let delta = MetalMarkdownNSView.normalizedScrollDelta(
            -7.5,
            hasPreciseScrollingDeltas: true,
            lineScrollDistance: 20
        )

        XCTAssertEqual(delta, -7.5)
    }

    func testDiscreteScrollDeltaScalesByLineDistance() {
        let delta = MetalMarkdownNSView.normalizedScrollDelta(
            -1,
            hasPreciseScrollingDeltas: false,
            lineScrollDistance: 20
        )

        XCTAssertEqual(delta, -20)
    }

    func testContainerDocumentSizeIncludesViewportMinimums() {
        let size = MetalMarkdownContainerView.documentSize(
            contentSize: CGSize(width: 320, height: 480),
            viewportSize: CGSize(width: 640, height: 360)
        )

        XCTAssertEqual(size.width, 640)
        XCTAssertEqual(size.height, 480)
    }
}
#endif
