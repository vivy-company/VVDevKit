import XCTest
#if canImport(AppKit)
import AppKit
#endif
@testable import VVMarkdown

final class VVMarkdownSelectionHelperTests: XCTestCase {
    func testSelectionRectsStaySplitAcrossWrappedLinesAndListItems() throws {
        #if canImport(AppKit)
        let parser = MarkdownParser()
        let document = parser.parse(
            """
            I inspected the Aizen timeline and rebuilt this transcript with the same VVDevKit presentation model:

            - user messages stay in timestamped bubbles
            - assistant output renders as an open lane
            - tool work collapses into grouped rows with per-call detail
            - completed turns end with a summary card
            """
        )
        let layoutEngine = MarkdownLayoutEngine(
            baseFont: NSFont.systemFont(ofSize: 17, weight: .regular),
            theme: .dark,
            contentWidth: 760
        )
        let layout = layoutEngine.layout(document)
        let helper = VVMarkdownSelectionHelper(layout: layout, layoutEngine: layoutEngine)

        let first = try XCTUnwrap(helper.findFirstPosition())
        let last = try XCTUnwrap(helper.findLastPosition())
        let rects = helper.selectionRects(from: first, to: last)

        XCTAssertGreaterThanOrEqual(rects.count, 5)
        for (lhs, rhs) in zip(rects, rects.dropFirst()) {
            XCTAssertLessThan(lhs.midY, rhs.midY)
        }
        #else
        throw XCTSkip("Selection helper tests require AppKit fonts.")
        #endif
    }
}
