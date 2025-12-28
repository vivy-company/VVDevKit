import XCTest
@testable import VVGit

final class DiffParserTests: XCTestCase {

    // MARK: - Basic Parsing

    func testParseEmptyDiff() {
        let diff = ""
        let hunks = VVDiffParser.parse(unifiedDiff: diff)
        XCTAssertTrue(hunks.isEmpty)
    }

    func testParseSimpleAddition() {
        let diff = """
        --- a/file.txt
        +++ b/file.txt
        @@ -1,3 +1,4 @@
         line 1
         line 2
        +new line
         line 3
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)

        XCTAssertEqual(hunks.count, 1)
        XCTAssertEqual(hunks[0].oldStart, 1)
        XCTAssertEqual(hunks[0].oldCount, 3)
        XCTAssertEqual(hunks[0].newStart, 1)
        XCTAssertEqual(hunks[0].newCount, 4)
        XCTAssertEqual(hunks[0].changeType, .added)
    }

    func testParseSimpleDeletion() {
        let diff = """
        --- a/file.txt
        +++ b/file.txt
        @@ -1,4 +1,3 @@
         line 1
         line 2
        -deleted line
         line 3
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)

        XCTAssertEqual(hunks.count, 1)
        XCTAssertEqual(hunks[0].changeType, .deleted)
    }

    func testParseModification() {
        let diff = """
        --- a/file.txt
        +++ b/file.txt
        @@ -1,3 +1,3 @@
         line 1
        -old line
        +new line
         line 3
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)

        XCTAssertEqual(hunks.count, 1)
        XCTAssertEqual(hunks[0].changeType, .modified)
    }

    // MARK: - Multiple Hunks

    func testParseMultipleHunks() {
        let diff = """
        --- a/file.txt
        +++ b/file.txt
        @@ -1,3 +1,4 @@
         line 1
        +added line
         line 2
         line 3
        @@ -10,3 +11,2 @@
         line 10
        -removed line
         line 12
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)

        XCTAssertEqual(hunks.count, 2)
        XCTAssertEqual(hunks[0].newStart, 1)
        XCTAssertEqual(hunks[0].changeType, .added)
        XCTAssertEqual(hunks[1].newStart, 11)
        XCTAssertEqual(hunks[1].changeType, .deleted)
    }

    // MARK: - Line Statuses

    func testLineStatusesForAddition() {
        let diff = """
        --- a/file.txt
        +++ b/file.txt
        @@ -1,2 +1,4 @@
         line 1
        +new line 2
        +new line 3
         line 2
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)
        let statuses = VVDiffParser.lineStatuses(from: hunks)

        // Lines 2 and 3 should be marked as added
        let addedLines = statuses.filter { $0.status == .added }.map { $0.lineNumber }
        XCTAssertTrue(addedLines.contains(2))
        XCTAssertTrue(addedLines.contains(3))
    }

    func testLineStatusesForModification() {
        let diff = """
        --- a/file.txt
        +++ b/file.txt
        @@ -1,3 +1,3 @@
         line 1
        -old line
        +new line
         line 3
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)
        let statuses = VVDiffParser.lineStatuses(from: hunks)

        let modifiedLines = statuses.filter { $0.status == .modified }.map { $0.lineNumber }
        XCTAssertTrue(modifiedLines.contains(2))
    }

    // MARK: - Edge Cases

    func testParseNoNewlineAtEnd() {
        let diff = """
        --- a/file.txt
        +++ b/file.txt
        @@ -1,2 +1,2 @@
         line 1
        -line 2
        \\ No newline at end of file
        +new line 2
        \\ No newline at end of file
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)

        XCTAssertEqual(hunks.count, 1)
        XCTAssertEqual(hunks[0].changeType, .modified)
    }

    func testParseNewFile() {
        let diff = """
        --- /dev/null
        +++ b/newfile.txt
        @@ -0,0 +1,3 @@
        +line 1
        +line 2
        +line 3
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)

        XCTAssertEqual(hunks.count, 1)
        XCTAssertEqual(hunks[0].oldStart, 0)
        XCTAssertEqual(hunks[0].oldCount, 0)
        XCTAssertEqual(hunks[0].newStart, 1)
        XCTAssertEqual(hunks[0].newCount, 3)
        XCTAssertEqual(hunks[0].changeType, .added)
    }

    func testParseDeletedFile() {
        let diff = """
        --- a/oldfile.txt
        +++ /dev/null
        @@ -1,3 +0,0 @@
        -line 1
        -line 2
        -line 3
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)

        XCTAssertEqual(hunks.count, 1)
        XCTAssertEqual(hunks[0].newStart, 0)
        XCTAssertEqual(hunks[0].newCount, 0)
        XCTAssertEqual(hunks[0].changeType, .deleted)
    }

    // MARK: - Hunk Header Parsing

    func testParseHunkHeaderWithFunctionContext() {
        let diff = """
        --- a/file.swift
        +++ b/file.swift
        @@ -10,5 +10,6 @@ func myFunction() {
             let x = 1
        +    let y = 2
             return x
         }
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)

        XCTAssertEqual(hunks.count, 1)
        XCTAssertEqual(hunks[0].oldStart, 10)
        XCTAssertEqual(hunks[0].newStart, 10)
    }

    func testParseHunkHeaderWithSingleLineCount() {
        // When count is 1, it may be omitted in the header
        let diff = """
        --- a/file.txt
        +++ b/file.txt
        @@ -5 +5,2 @@
         unchanged
        +added
        """

        let hunks = VVDiffParser.parse(unifiedDiff: diff)

        XCTAssertEqual(hunks.count, 1)
        XCTAssertEqual(hunks[0].oldStart, 5)
        XCTAssertEqual(hunks[0].oldCount, 1) // Default when omitted
    }
}
