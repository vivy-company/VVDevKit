import Foundation

public struct MetalGutterFoldRange: Hashable, Sendable {
    public let startLine: Int
    public let endLine: Int

    public init(startLine: Int, endLine: Int) {
        self.startLine = startLine
        self.endLine = endLine
    }
}

public struct MetalGutterGitHunk: Hashable, Sendable {
    public enum Status: Hashable, Sendable {
        case added
        case modified
        case deleted
    }

    public let startLine: Int
    public let lineCount: Int
    public let status: Status

    public init(startLine: Int, lineCount: Int, status: Status) {
        self.startLine = startLine
        self.lineCount = lineCount
        self.status = status
    }
}

public struct MetalDiffOverlayHunk: Hashable, Sendable {
    public enum Status: Hashable, Sendable {
        case added
        case modified
        case deleted
    }

    public let id: String
    public let startLine: Int
    public let endLine: Int
    public let status: Status
    public let addedLineCount: Int
    public let deletedLineCount: Int
    public let filePath: String

    public init(
        id: String,
        startLine: Int,
        endLine: Int,
        status: Status,
        addedLineCount: Int,
        deletedLineCount: Int,
        filePath: String
    ) {
        self.id = id
        self.startLine = startLine
        self.endLine = endLine
        self.status = status
        self.addedLineCount = addedLineCount
        self.deletedLineCount = deletedLineCount
        self.filePath = filePath
    }
}
