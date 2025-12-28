import Foundation

/// Represents a single hunk of changes from a unified diff
public struct VVDiffHunk: Sendable, Equatable, Hashable {
    /// Starting line number in the old file (1-indexed)
    public let oldStart: Int

    /// Number of lines in the old file
    public let oldCount: Int

    /// Starting line number in the new file (1-indexed)
    public let newStart: Int

    /// Number of lines in the new file
    public let newCount: Int

    /// Type of change
    public let changeType: ChangeType

    /// Individual line changes within this hunk
    public let lines: [LineDiff]

    public init(
        oldStart: Int,
        oldCount: Int,
        newStart: Int,
        newCount: Int,
        changeType: ChangeType,
        lines: [LineDiff] = []
    ) {
        self.oldStart = oldStart
        self.oldCount = oldCount
        self.newStart = newStart
        self.newCount = newCount
        self.changeType = changeType
        self.lines = lines
    }

    /// Type of change in a hunk
    public enum ChangeType: Sendable, Equatable, Hashable {
        case added
        case deleted
        case modified
    }
}

/// Represents a single line change within a diff
public struct LineDiff: Sendable, Equatable, Hashable {
    /// Line number in the new file (for added/modified) or old file (for deleted)
    public let lineNumber: Int

    /// Type of line change
    public let type: LineType

    /// Content of the line (without the +/- prefix)
    public let content: String

    public init(lineNumber: Int, type: LineType, content: String) {
        self.lineNumber = lineNumber
        self.type = type
        self.content = content
    }

    public enum LineType: Sendable, Equatable, Hashable {
        case context    // Unchanged line
        case added      // Line was added
        case deleted    // Line was removed
    }
}

/// Summary of git changes for a file
public struct VVGitStatus: Sendable, Equatable {
    public let addedLines: Int
    public let modifiedLines: Int
    public let deletedLines: Int

    public init(addedLines: Int = 0, modifiedLines: Int = 0, deletedLines: Int = 0) {
        self.addedLines = addedLines
        self.modifiedLines = modifiedLines
        self.deletedLines = deletedLines
    }

    /// Create from hunks
    public static func from(hunks: [VVDiffHunk]) -> VVGitStatus {
        var added = 0
        var modified = 0
        var deleted = 0

        for hunk in hunks {
            switch hunk.changeType {
            case .added:
                added += hunk.newCount
            case .deleted:
                deleted += hunk.oldCount
            case .modified:
                modified += max(hunk.oldCount, hunk.newCount)
            }
        }

        return VVGitStatus(addedLines: added, modifiedLines: modified, deletedLines: deleted)
    }
}

/// Line-level git status for gutter display
public struct VVLineGitStatus: Sendable, Equatable {
    public let lineNumber: Int
    public let status: Status

    public init(lineNumber: Int, status: Status) {
        self.lineNumber = lineNumber
        self.status = status
    }

    public enum Status: Sendable, Equatable {
        case added
        case modified
        case deleted  // Indicates a deletion happened before this line
    }
}
