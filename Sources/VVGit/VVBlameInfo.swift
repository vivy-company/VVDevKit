import Foundation

/// Git blame information for a line
public struct VVBlameInfo: Sendable, Equatable, Identifiable {
    public var id: Int { lineNumber }

    /// Line number (1-indexed)
    public let lineNumber: Int

    /// Commit SHA (abbreviated or full)
    public let commit: String

    /// Author name
    public let author: String

    /// Author email
    public let authorEmail: String?

    /// Commit timestamp
    public let date: Date

    /// Commit summary/message
    public let summary: String?

    /// Whether this line is uncommitted (dirty)
    public let isUncommitted: Bool

    public init(
        lineNumber: Int,
        commit: String,
        author: String,
        authorEmail: String? = nil,
        date: Date,
        summary: String? = nil,
        isUncommitted: Bool = false
    ) {
        self.lineNumber = lineNumber
        self.commit = commit
        self.author = author
        self.authorEmail = authorEmail
        self.date = date
        self.summary = summary
        self.isUncommitted = isUncommitted
    }

    /// Short commit hash (first 7 characters)
    public var shortCommit: String {
        if commit.count > 7 {
            return String(commit.prefix(7))
        }
        return commit
    }

    /// Relative date string (e.g., "2 days ago")
    public var relativeDate: String {
        let formatter = RelativeDateTimeFormatter()
        formatter.unitsStyle = .short
        return formatter.localizedString(for: date, relativeTo: Date())
    }

    /// Formatted blame string for display
    public var formattedBlame: String {
        if isUncommitted {
            return "Not Committed Yet"
        }
        return "\(author), \(relativeDate) • \(summary ?? shortCommit)"
    }

    /// Compact blame string (for inline display)
    public var compactBlame: String {
        if isUncommitted {
            return "Uncommitted"
        }
        return "\(author), \(relativeDate)"
    }
}

/// Blame information grouped by commit
public struct VVBlameGroup: Sendable, Equatable, Identifiable {
    public var id: String { commit }

    /// Commit SHA
    public let commit: String

    /// Author name
    public let author: String

    /// Commit date
    public let date: Date

    /// Commit summary
    public let summary: String?

    /// Line numbers in this group
    public let lineNumbers: [Int]

    /// Start line of this group
    public var startLine: Int { lineNumbers.min() ?? 0 }

    /// End line of this group
    public var endLine: Int { lineNumbers.max() ?? 0 }

    /// Number of lines
    public var lineCount: Int { lineNumbers.count }

    public init(
        commit: String,
        author: String,
        date: Date,
        summary: String?,
        lineNumbers: [Int]
    ) {
        self.commit = commit
        self.author = author
        self.date = date
        self.summary = summary
        self.lineNumbers = lineNumbers
    }
}

extension Array where Element == VVBlameInfo {
    /// Group blame info by commit into continuous ranges
    public func grouped() -> [VVBlameGroup] {
        guard !isEmpty else { return [] }

        var groups: [VVBlameGroup] = []
        var currentCommit = ""
        var currentLines: [Int] = []
        var currentAuthor = ""
        var currentDate = Date()
        var currentSummary: String?

        let sorted = self.sorted { $0.lineNumber < $1.lineNumber }

        for blame in sorted {
            if blame.commit == currentCommit {
                currentLines.append(blame.lineNumber)
            } else {
                // Finish previous group
                if !currentLines.isEmpty {
                    groups.append(VVBlameGroup(
                        commit: currentCommit,
                        author: currentAuthor,
                        date: currentDate,
                        summary: currentSummary,
                        lineNumbers: currentLines
                    ))
                }

                // Start new group
                currentCommit = blame.commit
                currentAuthor = blame.author
                currentDate = blame.date
                currentSummary = blame.summary
                currentLines = [blame.lineNumber]
            }
        }

        // Finish last group
        if !currentLines.isEmpty {
            groups.append(VVBlameGroup(
                commit: currentCommit,
                author: currentAuthor,
                date: currentDate,
                summary: currentSummary,
                lineNumbers: currentLines
            ))
        }

        return groups
    }
}
