import XCTest
@testable import VVCode

final class LineMapTests: XCTestCase {

    // MARK: - Initialization

    func testEmptyString() {
        let map = LineMap(text: "")
        XCTAssertEqual(map.lineCount, 1)  // Empty string = 1 line
    }

    func testSingleLine() {
        let map = LineMap(text: "Hello World")
        XCTAssertEqual(map.lineCount, 1)
    }

    func testMultipleLines() {
        let text = "Line 1\nLine 2\nLine 3"
        let map = LineMap(text: text)
        XCTAssertEqual(map.lineCount, 3)
    }

    func testEmptyLines() {
        let text = "Line 1\n\nLine 3"
        let map = LineMap(text: text)
        XCTAssertEqual(map.lineCount, 3)
    }

    func testTrailingNewline() {
        let text = "Line 1\nLine 2\n"
        let map = LineMap(text: text)
        XCTAssertEqual(map.lineCount, 3)
    }

    // MARK: - Line Number from Offset

    func testLineNumberForOffset() {
        let text = "abc\ndef\nghi"
        let map = LineMap(text: text)

        XCTAssertEqual(map.lineNumber(forOffset: 0), 1)  // 'a'
        XCTAssertEqual(map.lineNumber(forOffset: 2), 1)  // 'c'
        XCTAssertEqual(map.lineNumber(forOffset: 3), 1)  // '\n' belongs to line 1
        XCTAssertEqual(map.lineNumber(forOffset: 4), 2)  // 'd'
        XCTAssertEqual(map.lineNumber(forOffset: 8), 3)  // 'g'
    }

    func testLineNumberForOffsetAtBoundaries() {
        let text = "a\nb\nc"
        let map = LineMap(text: text)

        XCTAssertEqual(map.lineNumber(forOffset: 0), 1)
        XCTAssertEqual(map.lineNumber(forOffset: 1), 1)  // '\n' at end of line 1
        XCTAssertEqual(map.lineNumber(forOffset: 2), 2)  // 'b'
        XCTAssertEqual(map.lineNumber(forOffset: 4), 3)  // 'c'
    }

    func testLineNumberForOffsetBeyondEnd() {
        let text = "abc"
        let map = LineMap(text: text)

        // Offset beyond text length should return last line
        XCTAssertEqual(map.lineNumber(forOffset: 100), 1)
    }

    // MARK: - Offset from Line Number

    func testOffsetForLine() {
        let text = "abc\ndef\nghi"
        let map = LineMap(text: text)

        XCTAssertEqual(map.offset(forLine: 1), 0)
        XCTAssertEqual(map.offset(forLine: 2), 4)
        XCTAssertEqual(map.offset(forLine: 3), 8)
    }

    func testOffsetForLineOutOfBounds() {
        let text = "abc\ndef"
        let map = LineMap(text: text)

        // Line 0 or below should return 0
        XCTAssertEqual(map.offset(forLine: 0), 0)

        // Line beyond count should return 0 (invalid)
        XCTAssertEqual(map.offset(forLine: 100), 0)
    }

    // MARK: - Line Range

    func testRangeForLine() {
        let text = "abc\ndefgh\ni"
        let map = LineMap(text: text)

        let range1 = map.range(forLine: 1)
        XCTAssertEqual(range1.start, 0)
        XCTAssertEqual(range1.length, 4)  // "abc\n"

        let range2 = map.range(forLine: 2)
        XCTAssertEqual(range2.start, 4)
        XCTAssertEqual(range2.length, 6)  // "defgh\n"

        let range3 = map.range(forLine: 3)
        XCTAssertEqual(range3.start, 10)
        XCTAssertEqual(range3.length, 1)  // "i"
    }

    func testRangeForEmptyLine() {
        let text = "abc\n\ndef"
        let map = LineMap(text: text)

        let range2 = map.range(forLine: 2)
        XCTAssertEqual(range2.start, 4)
        XCTAssertEqual(range2.length, 1)  // Just the newline
    }

    // MARK: - Edit Handling

    func testUpdateAfterInsert() {
        var map = LineMap(text: "abc\ndef")

        // Insert "X" at position 1 (between 'a' and 'b')
        let edit = LineMap.TextEdit(range: NSRange(location: 1, length: 0), newLength: 1)
        map.update(after: edit, in: "aXbc\ndef")

        XCTAssertEqual(map.lineCount, 2)
        XCTAssertEqual(map.offset(forLine: 2), 5)  // Shifted by 1
    }

    func testUpdateAfterInsertNewline() {
        var map = LineMap(text: "abc\ndef")

        // Insert newline in first line
        let edit = LineMap.TextEdit(range: NSRange(location: 2, length: 0), newLength: 1)
        map.update(after: edit, in: "ab\nc\ndef")

        XCTAssertEqual(map.lineCount, 3)
        XCTAssertEqual(map.offset(forLine: 2), 3)
        XCTAssertEqual(map.offset(forLine: 3), 5)
    }

    func testUpdateAfterDelete() {
        var map = LineMap(text: "abc\ndef")

        // Delete 'b'
        let edit = LineMap.TextEdit(range: NSRange(location: 1, length: 1), newLength: 0)
        map.update(after: edit, in: "ac\ndef")

        XCTAssertEqual(map.lineCount, 2)
        XCTAssertEqual(map.offset(forLine: 2), 3)
    }

    func testUpdateAfterDeleteNewline() {
        var map = LineMap(text: "abc\ndef")

        // Delete newline (merge lines)
        let edit = LineMap.TextEdit(range: NSRange(location: 3, length: 1), newLength: 0)
        map.update(after: edit, in: "abcdef")

        XCTAssertEqual(map.lineCount, 1)
    }

    // MARK: - Unicode Handling

    func testUnicodeCharacters() {
        let text = "こんにちは\n世界"
        let map = LineMap(text: text)

        XCTAssertEqual(map.lineCount, 2)
        XCTAssertEqual(map.lineNumber(forOffset: 0), 1)
    }

    func testEmoji() {
        let text = "Hello 👋\nWorld 🌍"
        let map = LineMap(text: text)

        XCTAssertEqual(map.lineCount, 2)
    }

    // MARK: - Static Helpers

    func testStaticLineCount() {
        XCTAssertEqual(LineMap.lineCount(in: ""), 1)
        XCTAssertEqual(LineMap.lineCount(in: "hello"), 1)
        XCTAssertEqual(LineMap.lineCount(in: "hello\nworld"), 2)
        XCTAssertEqual(LineMap.lineCount(in: "a\nb\nc\n"), 4)
    }

    func testStaticPosition() {
        let text = "abc\ndef\nghi"

        let pos0 = LineMap.position(at: 0, in: text)
        XCTAssertEqual(pos0.line, 1)
        XCTAssertEqual(pos0.column, 1)

        let pos4 = LineMap.position(at: 4, in: text)
        XCTAssertEqual(pos4.line, 2)
        XCTAssertEqual(pos4.column, 1)

        let pos5 = LineMap.position(at: 5, in: text)
        XCTAssertEqual(pos5.line, 2)
        XCTAssertEqual(pos5.column, 2)
    }

    // MARK: - Performance

    func testLargeFile() {
        let lines = (1...10000).map { "Line \($0)" }
        let text = lines.joined(separator: "\n")

        let map = LineMap(text: text)

        XCTAssertEqual(map.lineCount, 10000)
        XCTAssertEqual(map.lineNumber(forOffset: 0), 1)
    }

    // MARK: - Edge Cases

    func testOnlyNewlines() {
        let text = "\n\n\n"
        let map = LineMap(text: text)
        XCTAssertEqual(map.lineCount, 4)
    }
}
