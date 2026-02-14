import XCTest
@testable import VVCode

@MainActor
final class MultiDiffDocumentTests: XCTestCase {

    func testProjectionContainsFileHeaderAndHunks() {
        let oldDocument = VVDocument(
            text: """
            let a = 1
            let b = 2
            let c = 3
            """,
            language: .swift
        )
        let newDocument = VVDocument(
            text: """
            let a = 1
            let b = 20
            let c = 3
            """,
            language: .swift
        )
        let diff = """
        diff --git a/Sources/Test.swift b/Sources/Test.swift
        index 1111111..2222222 100644
        --- a/Sources/Test.swift
        +++ b/Sources/Test.swift
        @@ -2,1 +2,1 @@
        -let b = 2
        +let b = 20
        """

        let document = VVMultiDiffDocument(
            entries: [
                VVMultiDiffEntry(
                    id: "test",
                    path: "Sources/Test.swift",
                    oldDocument: oldDocument,
                    newDocument: newDocument,
                    language: .swift,
                    unifiedDiff: diff
                )
            ],
            contextLines: 1
        )

        XCTAssertTrue(document.projectDocument.text.contains("diff -- Sources/Test.swift"))
        XCTAssertTrue(document.projectDocument.text.contains("@@ 1,3 @@"))
        XCTAssertTrue(document.projectDocument.text.contains("let b = 20"))

        let presentation = document.presentation()
        XCTAssertEqual(presentation.visualHunks.count, 1)
        XCTAssertEqual(presentation.visualHunks.first?.changeType, .modified)
        XCTAssertEqual(presentation.visualHunks.first?.addedLineCount, 1)
        XCTAssertEqual(presentation.visualHunks.first?.deletedLineCount, 1)

        XCTAssertEqual(presentation.fileSummaries.count, 1)
        XCTAssertEqual(presentation.fileSummaries.first?.path, "Sources/Test.swift")
        XCTAssertEqual(presentation.fileSummaries.first?.hunkCount, 1)
        XCTAssertEqual(presentation.fileSummaries.first?.addedLineCount, 1)
        XCTAssertEqual(presentation.fileSummaries.first?.deletedLineCount, 1)
    }

    func testProjectedEditUpdatesUnderlyingBuffer() {
        let oldDocument = VVDocument(
            text: """
            one
            two
            three
            """,
            language: .markdown
        )
        let newDocument = VVDocument(
            text: """
            one
            two changed
            three
            """,
            language: .markdown
        )
        let diff = """
        diff --git a/file.txt b/file.txt
        index 1111111..2222222 100644
        --- a/file.txt
        +++ b/file.txt
        @@ -2,1 +2,1 @@
        -two
        +two changed
        """

        let document = VVMultiDiffDocument(
            entries: [
                VVMultiDiffEntry(
                    id: "file",
                    path: "file.txt",
                    oldDocument: oldDocument,
                    newDocument: newDocument,
                    unifiedDiff: diff
                )
            ],
            contextLines: 1
        )

        let before = document.projectDocument.text
        let edited = before.replacingOccurrences(of: "two changed", with: "two edited again")
        document.handleProjectedTextChange(edited)

        XCTAssertTrue(newDocument.text.contains("two edited again"))
        XCTAssertEqual(document.projectDocument.text, edited)
        XCTAssertEqual(document.presentation().fileSummaries.count, 1)
        XCTAssertEqual(document.presentation().visualHunks.count, 1)
    }

    func testEditInHeaderIsRejectedAndProjectionRestored() {
        let oldDocument = VVDocument(text: "a\nb\n", language: .swift)
        let newDocument = VVDocument(text: "a\nbb\n", language: .swift)
        let diff = """
        diff --git a/file.swift b/file.swift
        index 1111111..2222222 100644
        --- a/file.swift
        +++ b/file.swift
        @@ -2,1 +2,1 @@
        -b
        +bb
        """

        let document = VVMultiDiffDocument(
            entries: [
                VVMultiDiffEntry(
                    id: "file",
                    path: "file.swift",
                    oldDocument: oldDocument,
                    newDocument: newDocument,
                    language: .swift,
                    unifiedDiff: diff
                )
            ],
            contextLines: 0
        )

        let originalProjection = document.projectDocument.text
        let invalid = "X" + originalProjection
        document.handleProjectedTextChange(invalid)

        XCTAssertEqual(document.projectDocument.text, originalProjection)
        XCTAssertEqual(newDocument.text, "a\nbb\n")
        XCTAssertEqual(document.presentation().visualHunks.first?.changeType, .modified)
    }

    func testEditingEarlierFileShiftsLaterFileSummaryStartLines() {
        let firstOld = VVDocument(text: "one\ntwo\nthree\n", language: .swift)
        let firstNew = VVDocument(text: "one\ntwo changed\nthree\n", language: .swift)
        let firstDiff = """
        diff --git a/first.swift b/first.swift
        index 1111111..2222222 100644
        --- a/first.swift
        +++ b/first.swift
        @@ -2,1 +2,1 @@
        -two
        +two changed
        """

        let secondOld = VVDocument(text: "alpha\nbeta\ngamma\n", language: .swift)
        let secondNew = VVDocument(text: "alpha\nbeta changed\ngamma\n", language: .swift)
        let secondDiff = """
        diff --git a/second.swift b/second.swift
        index 3333333..4444444 100644
        --- a/second.swift
        +++ b/second.swift
        @@ -2,1 +2,1 @@
        -beta
        +beta changed
        """

        let document = VVMultiDiffDocument(
            entries: [
                VVMultiDiffEntry(
                    id: "first",
                    path: "first.swift",
                    oldDocument: firstOld,
                    newDocument: firstNew,
                    language: .swift,
                    unifiedDiff: firstDiff
                ),
                VVMultiDiffEntry(
                    id: "second",
                    path: "second.swift",
                    oldDocument: secondOld,
                    newDocument: secondNew,
                    language: .swift,
                    unifiedDiff: secondDiff
                )
            ],
            contextLines: 1
        )

        let initialPresentation = document.presentation()
        XCTAssertEqual(initialPresentation.fileSummaries.count, 2)
        let firstStart = initialPresentation.fileSummaries[0].startLine
        let secondStart = initialPresentation.fileSummaries[1].startLine
        XCTAssertTrue(secondStart > firstStart)

        let editedProjection = document.projectDocument.text.replacingOccurrences(
            of: "two changed",
            with: "two changed\ninserted line"
        )
        document.handleProjectedTextChange(editedProjection)

        XCTAssertTrue(firstNew.text.contains("inserted line"))

        let updatedPresentation = document.presentation()
        XCTAssertEqual(updatedPresentation.fileSummaries.count, 2)
        XCTAssertEqual(updatedPresentation.fileSummaries[1].startLine, secondStart + 1)
    }

    func testRenderWindowLimitsVisibleHunksOnLargeDiff() {
        let totalLines = 140
        let changedLines = stride(from: 4, through: 130, by: 7).map { $0 }
        let oldDocument = VVDocument(
            text: makeNumberedText(prefix: "base", totalLines: totalLines),
            language: .swift
        )
        let newDocument = VVDocument(
            text: makeChangedNumberedText(prefix: "next", totalLines: totalLines, changedLines: Set(changedLines)),
            language: .swift
        )
        let diff = makeUnifiedDiff(path: "window.swift", totalLines: totalLines, changedLines: changedLines)

        let document = VVMultiDiffDocument(
            entries: [
                VVMultiDiffEntry(
                    id: "window",
                    path: "window.swift",
                    oldDocument: oldDocument,
                    newDocument: newDocument,
                    language: .swift,
                    unifiedDiff: diff
                )
            ],
            contextLines: 1
        )

        document.setRenderWindow(.init(isEnabled: true, hunkBuffer: 2, minimumTotalHunks: 1))
        let presentation = document.presentation()

        XCTAssertTrue(presentation.renderWindowState.isActive)
        XCTAssertEqual(presentation.renderWindowState.totalHunkCount, changedLines.count)
        XCTAssertLessThanOrEqual(presentation.visualHunks.count, 5)
        XCTAssertEqual(presentation.visualHunks.count, presentation.renderWindowState.visibleHunkCount)
    }

    func testRenderWindowAnchorMovesAsVisibleRangeChanges() {
        let totalLines = 120
        let changedLines = stride(from: 5, through: 110, by: 7).map { $0 }
        let oldDocument = VVDocument(
            text: makeNumberedText(prefix: "base", totalLines: totalLines),
            language: .swift
        )
        let newDocument = VVDocument(
            text: makeChangedNumberedText(prefix: "next", totalLines: totalLines, changedLines: Set(changedLines)),
            language: .swift
        )
        let diff = makeUnifiedDiff(path: "anchor.swift", totalLines: totalLines, changedLines: changedLines)

        let document = VVMultiDiffDocument(
            entries: [
                VVMultiDiffEntry(
                    id: "anchor",
                    path: "anchor.swift",
                    oldDocument: oldDocument,
                    newDocument: newDocument,
                    language: .swift,
                    unifiedDiff: diff
                )
            ],
            contextLines: 1
        )

        document.setRenderWindow(.init(isEnabled: true, hunkBuffer: 1, minimumTotalHunks: 1))
        let initial = document.presentation()
        let initialIDs = initial.visualHunks.map(\.id)
        guard let targetHunk = initial.visualHunks.last else {
            XCTFail("Expected visible hunks")
            return
        }

        document.updateRenderAnchor(forVisibleLineRange: targetHunk.startLine...targetHunk.endLine)
        let updated = document.presentation()
        let updatedIDs = updated.visualHunks.map(\.id)

        XCTAssertNotEqual(updated.renderWindowState.anchorHunkID, initial.renderWindowState.anchorHunkID)
        XCTAssertEqual(updated.renderWindowState.anchorHunkID, targetHunk.id)
        XCTAssertNotEqual(updatedIDs, initialIDs)
        XCTAssertTrue(updatedIDs.contains(targetHunk.id))
    }

    private func makeNumberedText(prefix: String, totalLines: Int) -> String {
        (1...totalLines).map { "\(prefix)-\($0)" }.joined(separator: "\n") + "\n"
    }

    private func makeChangedNumberedText(prefix: String, totalLines: Int, changedLines: Set<Int>) -> String {
        (1...totalLines).map { line in
            if changedLines.contains(line) {
                return "\(prefix)-\(line)-changed"
            }
            return "\(prefix)-\(line)"
        }
        .joined(separator: "\n") + "\n"
    }

    private func makeUnifiedDiff(path: String, totalLines: Int, changedLines: [Int]) -> String {
        var lines: [String] = []
        lines.append("diff --git a/\(path) b/\(path)")
        lines.append("index 1111111..2222222 100644")
        lines.append("--- a/\(path)")
        lines.append("+++ b/\(path)")

        for line in changedLines {
            let start = max(1, line - 1)
            let end = min(totalLines, line + 1)
            let count = end - start + 1
            lines.append("@@ -\(start),\(count) +\(start),\(count) @@")
            for current in start...end {
                if current == line {
                    lines.append("-base-\(current)")
                    lines.append("+next-\(current)-changed")
                } else {
                    lines.append(" base-\(current)")
                }
            }
        }

        return lines.joined(separator: "\n")
    }
}
