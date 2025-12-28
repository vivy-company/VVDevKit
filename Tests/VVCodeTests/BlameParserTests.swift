import XCTest
@testable import VVGit

final class BlameParserTests: XCTestCase {

    // MARK: - Porcelain Format Parsing

    func testParsePorcelainEmpty() {
        let output = ""
        let blame = VVBlameParser.parse(porcelainOutput: output)
        XCTAssertTrue(blame.isEmpty)
    }

    func testParsePorcelainSingleLine() {
        let output = """
        abc123def456789012345678901234567890abcd 1 1 1
        author John Doe
        author-mail <john@example.com>
        author-time 1609459200
        author-tz +0000
        committer John Doe
        committer-mail <john@example.com>
        committer-time 1609459200
        committer-tz +0000
        summary Initial commit
        filename file.txt
        \tThis is line content
        """

        let blame = VVBlameParser.parse(porcelainOutput: output)

        XCTAssertEqual(blame.count, 1)
        XCTAssertEqual(blame[0].lineNumber, 1)
        XCTAssertEqual(blame[0].commit, "abc123def456789012345678901234567890abcd")
        XCTAssertEqual(blame[0].author, "John Doe")
        XCTAssertEqual(blame[0].summary, "Initial commit")
    }

    func testParsePorcelainMultipleLines() {
        let output = """
        abc123def456789012345678901234567890abcd 1 1 2
        author John Doe
        author-mail <john@example.com>
        author-time 1609459200
        author-tz +0000
        committer John Doe
        committer-mail <john@example.com>
        committer-time 1609459200
        committer-tz +0000
        summary First commit
        filename file.txt
        \tLine 1
        abc123def456789012345678901234567890abcd 2 2
        \tLine 2
        def456789012345678901234567890abcd1234 3 3 1
        author Jane Smith
        author-mail <jane@example.com>
        author-time 1609545600
        author-tz +0000
        committer Jane Smith
        committer-mail <jane@example.com>
        committer-time 1609545600
        committer-tz +0000
        summary Second commit
        filename file.txt
        \tLine 3
        """

        let blame = VVBlameParser.parse(porcelainOutput: output)

        XCTAssertEqual(blame.count, 3)

        // First two lines same commit
        XCTAssertEqual(blame[0].lineNumber, 1)
        XCTAssertEqual(blame[0].author, "John Doe")
        XCTAssertEqual(blame[0].summary, "First commit")

        XCTAssertEqual(blame[1].lineNumber, 2)
        XCTAssertEqual(blame[1].author, "John Doe")
        XCTAssertEqual(blame[1].summary, "First commit")

        // Third line different commit
        XCTAssertEqual(blame[2].lineNumber, 3)
        XCTAssertEqual(blame[2].author, "Jane Smith")
        XCTAssertEqual(blame[2].summary, "Second commit")
    }

    // MARK: - Standard Format Parsing

    func testParseStandardEmpty() {
        let output = ""
        let blame = VVBlameParser.parseStandard(output: output)
        XCTAssertTrue(blame.isEmpty)
    }

    func testParseStandardFormat() {
        let output = """
        abc1234 (John Doe 2021-01-01 10:00:00 +0000 1) First line
        abc1234 (John Doe 2021-01-01 10:00:00 +0000 2) Second line
        def5678 (Jane Smith 2021-01-02 11:00:00 +0000 3) Third line
        """

        let blame = VVBlameParser.parseStandard(output: output)

        XCTAssertEqual(blame.count, 3)

        XCTAssertEqual(blame[0].lineNumber, 1)
        XCTAssertEqual(blame[0].commit, "abc1234")
        XCTAssertEqual(blame[0].author, "John Doe")

        XCTAssertEqual(blame[1].lineNumber, 2)
        XCTAssertEqual(blame[1].commit, "abc1234")

        XCTAssertEqual(blame[2].lineNumber, 3)
        XCTAssertEqual(blame[2].commit, "def5678")
        XCTAssertEqual(blame[2].author, "Jane Smith")
    }

    // MARK: - Date Parsing

    func testDateParsing() {
        let output = """
        abc123def456789012345678901234567890abcd 1 1 1
        author John Doe
        author-mail <john@example.com>
        author-time 1609459200
        author-tz +0000
        committer John Doe
        committer-mail <john@example.com>
        committer-time 1609459200
        committer-tz +0000
        summary Test commit
        filename file.txt
        \tContent
        """

        let blame = VVBlameParser.parse(porcelainOutput: output)

        XCTAssertEqual(blame.count, 1)

        // 1609459200 = 2021-01-01 00:00:00 UTC
        let expectedDate = Date(timeIntervalSince1970: 1609459200)
        XCTAssertEqual(blame[0].date.timeIntervalSince1970, expectedDate.timeIntervalSince1970, accuracy: 1)
    }

    // MARK: - Edge Cases

    func testUncommittedChanges() {
        // Git blame shows uncommitted changes with special hash
        let output = """
        0000000000000000000000000000000000000000 1 1 1
        author Not Committed Yet
        author-mail <not.committed.yet>
        author-time 1609459200
        author-tz +0000
        committer Not Committed Yet
        committer-mail <not.committed.yet>
        committer-time 1609459200
        committer-tz +0000
        summary Not Committed Yet
        filename file.txt
        \tUncommitted line
        """

        let blame = VVBlameParser.parse(porcelainOutput: output)

        XCTAssertEqual(blame.count, 1)
        XCTAssertEqual(blame[0].commit, "0000000000000000000000000000000000000000")
        XCTAssertEqual(blame[0].author, "Not Committed Yet")
    }

    func testAuthorWithSpecialCharacters() {
        let output = """
        abc123def456789012345678901234567890abcd 1 1 1
        author José García-López
        author-mail <jose@example.com>
        author-time 1609459200
        author-tz +0000
        committer José García-López
        committer-mail <jose@example.com>
        committer-time 1609459200
        committer-tz +0000
        summary Añadir función
        filename archivo.txt
        \tContenido
        """

        let blame = VVBlameParser.parse(porcelainOutput: output)

        XCTAssertEqual(blame.count, 1)
        XCTAssertEqual(blame[0].author, "José García-López")
        XCTAssertEqual(blame[0].summary, "Añadir función")
    }

    func testLongCommitSummary() {
        let output = """
        abc123def456789012345678901234567890abcd 1 1 1
        author John Doe
        author-mail <john@example.com>
        author-time 1609459200
        author-tz +0000
        committer John Doe
        committer-mail <john@example.com>
        committer-time 1609459200
        committer-tz +0000
        summary This is a very long commit message that spans many characters and might need truncation in display
        filename file.txt
        \tContent
        """

        let blame = VVBlameParser.parse(porcelainOutput: output)

        XCTAssertEqual(blame.count, 1)
        XCTAssertTrue(blame[0].summary?.contains("very long commit message") ?? false)
    }

    func testBoundaryCommit() {
        // Test boundary commits (indicated with ^)
        let output = """
        ^abc123def456789012345678901234567890abc 1 1 1
        author Initial Author
        author-mail <initial@example.com>
        author-time 1609459200
        author-tz +0000
        committer Initial Author
        committer-mail <initial@example.com>
        committer-time 1609459200
        committer-tz +0000
        summary Initial commit
        boundary
        filename file.txt
        \tContent
        """

        let blame = VVBlameParser.parse(porcelainOutput: output)

        XCTAssertEqual(blame.count, 1)
        // The ^ should be handled (either stripped or kept as-is depending on implementation)
    }
}
