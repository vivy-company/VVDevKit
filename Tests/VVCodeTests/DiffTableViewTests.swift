import XCTest
@testable import VVCode

final class DiffTableViewTests: XCTestCase {

    func testParseCreatesFileAndHunkRows() {
        let diff = """
        diff --git a/crates/brain/src/tools/mod.rs b/crates/brain/src/tools/mod.rs
        index 93b2471..b4720aa 100644
        --- a/crates/brain/src/tools/mod.rs
        +++ b/crates/brain/src/tools/mod.rs
        @@ -10,3 +10,4 @@ fn test() {
         let value = 1;
        -let old = value;
        +let old = value + 1;
        +let next = old;
         return;
        """

        let rows = VVDiffTable.parse(unifiedDiff: diff)

        XCTAssertFalse(rows.isEmpty)
        XCTAssertEqual(rows.first?.kind, .fileHeader)
        XCTAssertEqual(rows.first?.text, "crates/brain/src/tools/mod.rs")
        XCTAssertEqual(rows.first(where: { $0.kind == .hunkHeader })?.text, "@@ -10,3 +10,4 @@ fn test() {")
    }

    func testParseMapsLineNumbersAcrossAddedDeletedAndContextRows() {
        let diff = """
        diff --git a/file.swift b/file.swift
        index 1111111..2222222 100644
        --- a/file.swift
        +++ b/file.swift
        @@ -5,4 +5,5 @@
         let a = 1
        -let b = 2
        +let b = 3
        +let c = b
         return a
        """

        let rows = VVDiffTable.parse(unifiedDiff: diff)

        let contextBefore = rows.first(where: { $0.kind == .context && $0.text == "let a = 1" })
        XCTAssertEqual(contextBefore?.oldLineNumber, 5)
        XCTAssertEqual(contextBefore?.newLineNumber, 5)

        let deleted = rows.first(where: { $0.kind == .deleted })
        XCTAssertEqual(deleted?.oldLineNumber, 6)
        XCTAssertNil(deleted?.newLineNumber)

        let firstAdded = rows.first(where: { $0.kind == .added })
        XCTAssertNil(firstAdded?.oldLineNumber)
        XCTAssertEqual(firstAdded?.newLineNumber, 6)

        let secondAdded = rows.filter { $0.kind == .added }.dropFirst().first
        XCTAssertEqual(secondAdded?.newLineNumber, 7)

        let contextAfter = rows.first(where: { $0.kind == .context && $0.text == "return a" })
        XCTAssertEqual(contextAfter?.oldLineNumber, 7)
        XCTAssertEqual(contextAfter?.newLineNumber, 8)
    }

    func testParseIncludesNoNewlineMarkerAsMetadata() {
        let diff = """
        diff --git a/file.txt b/file.txt
        index 1111111..2222222 100644
        --- a/file.txt
        +++ b/file.txt
        @@ -1 +1 @@
        -old
        \\ No newline at end of file
        +new
        """

        let rows = VVDiffTable.parse(unifiedDiff: diff)

        XCTAssertTrue(rows.contains(where: { $0.kind == .metadata && $0.text == "\\ No newline at end of file" }))
    }
}
