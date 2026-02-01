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
