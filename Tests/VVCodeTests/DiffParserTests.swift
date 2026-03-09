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

    func testParseFilePatchesPreservesHeadersMetadataAndRawLineOrder() throws {
        let diff = """
        diff --git a/Sources/App.swift b/Sources/App.swift
        index 1111111..2222222 100644
        --- a/Sources/App.swift
        +++ b/Sources/App.swift
        @@ -10,2 +10,2 @@ func render() {
        -    return oldValue
        \\ No newline at end of file
        +    return newValue
        """

        let patches = VVDiffParser.parseFilePatches(unifiedDiff: diff)
        let patch = try XCTUnwrap(patches.first)
        let hunk = try XCTUnwrap(patch.hunks.first)

        XCTAssertEqual(patch.filePath, "Sources/App.swift")
        XCTAssertEqual(patch.metadataLines, [
            "index 1111111..2222222 100644",
            "--- a/Sources/App.swift",
            "+++ b/Sources/App.swift",
        ])
        XCTAssertEqual(hunk.headerLine, "@@ -10,2 +10,2 @@ func render() {")
        XCTAssertEqual(hunk.rawLines.map(\.kind), [.deleted, .metadata, .added])
        XCTAssertEqual(hunk.rawLines[1].text, "\\ No newline at end of file")
    }

    func testParsedAndManualHunksCompareEqualUsingPublicFields() throws {
        let diff = """
        --- a/file.txt
        +++ b/file.txt
        @@ -1,3 +1,3 @@
         line 1
        -old line
        +new line
         line 3
        """

        let parsed = try XCTUnwrap(VVDiffParser.parse(unifiedDiff: diff).first)
        let manual = VVDiffHunk(
            oldStart: 1,
            oldCount: 3,
            newStart: 1,
            newCount: 3,
            changeType: .modified,
            lines: [
                LineDiff(lineNumber: 1, type: .context, content: "line 1"),
                LineDiff(lineNumber: 2, type: .deleted, content: "old line"),
                LineDiff(lineNumber: 2, type: .added, content: "new line"),
                LineDiff(lineNumber: 3, type: .context, content: "line 3"),
            ]
        )

        XCTAssertEqual(parsed, manual)
        XCTAssertEqual(parsed.hashValue, manual.hashValue)
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

    func testParseDocumentPreservesHeaderOrderForRendererConsumption() {
        let diff = """
        diff --git a/Sources/App.swift b/Sources/App.swift
        index 1111111..2222222 100644
        --- a/Sources/App.swift
        +++ b/Sources/App.swift
        @@ -10,2 +10,3 @@ struct AppView {
        -    let value = oldValue
        +    let value = newValue
        +    let subtitle = value
        \\ No newline at end of file
        """

        let document = VVDiffParser.parseDocument(unifiedDiff: diff)

        XCTAssertEqual(document.records.count, 9)

        guard case let .fileHeader(path, headerLine)? = document.records.first else {
            return XCTFail("Expected file header record")
        }
        XCTAssertEqual(path, "Sources/App.swift")
        XCTAssertEqual(headerLine, "diff --git a/Sources/App.swift b/Sources/App.swift")

        XCTAssertEqual(
            document.records.compactMap { record -> String? in
                if case let .metadata(text) = record {
                    return text
                }
                return nil
            },
            [
                "index 1111111..2222222 100644",
                "--- a/Sources/App.swift",
                "+++ b/Sources/App.swift",
                "\\ No newline at end of file",
            ]
        )

        guard case let .hunkHeader(header)? = document.records.first(where: {
            if case .hunkHeader = $0 { return true }
            return false
        }) else {
            return XCTFail("Expected hunk header record")
        }
        XCTAssertEqual(header.rawLine, "@@ -10,2 +10,3 @@ struct AppView {")
    }
}
