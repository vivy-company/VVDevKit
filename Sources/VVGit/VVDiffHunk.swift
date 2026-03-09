import Foundation

package struct VVParsedDiffDocument: Sendable, Equatable, Hashable {
    package let records: [VVParsedDiffRecord]

    package init(records: [VVParsedDiffRecord]) {
        self.records = records
    }
}

package enum VVParsedDiffRecord: Sendable, Equatable, Hashable {
    case fileHeader(String, String?)
    case metadata(String)
    case hunkHeader(VVParsedDiffHunkHeader)
    case line(VVParsedDiffLine)
}

package struct VVParsedDiffHunkHeader: Sendable, Equatable, Hashable {
    package let rawLine: String
    package let oldStart: Int
    package let oldCount: Int
    package let newStart: Int
    package let newCount: Int

    package init(rawLine: String, oldStart: Int, oldCount: Int, newStart: Int, newCount: Int) {
        self.rawLine = rawLine
        self.oldStart = oldStart
        self.oldCount = oldCount
        self.newStart = newStart
        self.newCount = newCount
    }
}

package struct VVParsedDiffLine: Sendable, Equatable, Hashable {
    package enum Kind: Sendable, Equatable, Hashable {
        case context
        case added
        case deleted
    }

    package let kind: Kind
    package let text: String
    package let oldLineNumber: Int?
    package let newLineNumber: Int?

    package init(kind: Kind, text: String, oldLineNumber: Int?, newLineNumber: Int?) {
        self.kind = kind
        self.text = text
        self.oldLineNumber = oldLineNumber
        self.newLineNumber = newLineNumber
    }
}

package struct VVDiffRawLine: Sendable, Equatable, Hashable {
    package enum Kind: Sendable, Equatable, Hashable {
        case context
        case added
        case deleted
        case metadata
    }

    package let kind: Kind
    package let text: String
    package let oldLineNumber: Int?
    package let newLineNumber: Int?

    package init(kind: Kind, text: String, oldLineNumber: Int?, newLineNumber: Int?) {
        self.kind = kind
        self.text = text
        self.oldLineNumber = oldLineNumber
        self.newLineNumber = newLineNumber
    }
}

package struct VVDiffFilePatch: Sendable, Equatable, Hashable {
    package let headerLine: String?
    package let oldPath: String?
    package let newPath: String?
    package let filePath: String
    package let metadataLines: [String]
    package let hunks: [VVDiffHunk]

    package init(
        headerLine: String?,
        oldPath: String?,
        newPath: String?,
        filePath: String,
        metadataLines: [String] = [],
        hunks: [VVDiffHunk] = []
    ) {
        self.headerLine = headerLine
        self.oldPath = oldPath
        self.newPath = newPath
        self.filePath = filePath
        self.metadataLines = metadataLines
        self.hunks = hunks
    }
}

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

    /// Raw unified diff hunk header, including optional trailing context.
    package let headerLine: String

    /// Raw hunk payload, preserving metadata markers such as "\ No newline at end of file".
    package let rawLines: [VVDiffRawLine]

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
        self.headerLine = ""
        self.rawLines = []
    }

    package init(
        oldStart: Int,
        oldCount: Int,
        newStart: Int,
        newCount: Int,
        headerLine: String,
        changeType: ChangeType,
        lines: [LineDiff],
        rawLines: [VVDiffRawLine]
    ) {
        self.oldStart = oldStart
        self.oldCount = oldCount
        self.newStart = newStart
        self.newCount = newCount
        self.changeType = changeType
        self.lines = lines
        self.headerLine = headerLine
        self.rawLines = rawLines
    }

    /// Type of change in a hunk
    public enum ChangeType: Sendable, Equatable, Hashable {
        case added
        case deleted
        case modified
    }

    public static func == (lhs: VVDiffHunk, rhs: VVDiffHunk) -> Bool {
        lhs.oldStart == rhs.oldStart &&
        lhs.oldCount == rhs.oldCount &&
        lhs.newStart == rhs.newStart &&
        lhs.newCount == rhs.newCount &&
        lhs.changeType == rhs.changeType &&
        lhs.lines == rhs.lines
    }

    public func hash(into hasher: inout Hasher) {
        hasher.combine(oldStart)
        hasher.combine(oldCount)
        hasher.combine(newStart)
        hasher.combine(newCount)
        hasher.combine(changeType)
        hasher.combine(lines)
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
        case context
        case added
        case deleted
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
        case deleted
    }
}
