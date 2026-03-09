import Foundation

/// Parser for unified diff format (git diff output)
public struct VVDiffParser {
    private static let hunkHeaderRegex: NSRegularExpression? = try? NSRegularExpression(
        pattern: #"@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@"#
    )

    /// Parse unified diff output into file patches that preserve file headers, metadata, and raw hunk payloads.
    package static func parseFilePatches(unifiedDiff: String) -> [VVDiffFilePatch] {
        let lines = normalizedLines(from: unifiedDiff)
        guard !lines.isEmpty else { return [] }

        var patches: [VVDiffFilePatch] = []
        patches.reserveCapacity(max(1, lines.count / 32))

        var currentPatch = FilePatchBuilder()
        var currentHunk: HunkBuilder?

        func flushHunk() {
            guard let hunk = currentHunk else { return }
            currentPatch.hunks.append(hunk.build())
            currentHunk = nil
        }

        func flushPatch() {
            flushHunk()
            guard currentPatch.hasContent else { return }
            patches.append(currentPatch.build())
            currentPatch = FilePatchBuilder()
        }

        for line in lines {
            if line.hasPrefix("diff --git ") {
                flushPatch()
                currentPatch.headerLine = line
                currentPatch.filePath = filePath(fromDiffHeader: line)
                continue
            }

            if line.hasPrefix("--- ") {
                flushHunk()
                if currentPatch.shouldStartNewPatch(beforeFileMarker: true) {
                    flushPatch()
                }
                currentPatch.oldPath = normalizedFileMarkerPath(String(line.dropFirst(4)))
                currentPatch.filePath = preferredFilePath(
                    explicit: currentPatch.filePath,
                    oldPath: currentPatch.oldPath,
                    newPath: currentPatch.newPath
                )
                currentPatch.metadataLines.append(line)
                continue
            }

            if line.hasPrefix("+++ ") {
                flushHunk()
                currentPatch.newPath = normalizedFileMarkerPath(String(line.dropFirst(4)))
                currentPatch.filePath = preferredFilePath(
                    explicit: currentPatch.filePath,
                    oldPath: currentPatch.oldPath,
                    newPath: currentPatch.newPath
                )
                currentPatch.metadataLines.append(line)
                continue
            }

            if line.hasPrefix("@@") {
                flushHunk()
                guard let header = parseHunkHeader(line) else { continue }
                currentHunk = HunkBuilder(
                    oldStart: header.oldStart,
                    oldCount: header.oldCount,
                    newStart: header.newStart,
                    newCount: header.newCount,
                    headerLine: line
                )
                continue
            }

            if currentHunk != nil {
                currentHunk?.append(line)
                continue
            }

            if isMetadataLine(line) {
                if currentPatch.shouldStartNewPatch(beforeFileMarker: false) {
                    flushPatch()
                }
                currentPatch.metadataLines.append(line)
            }
        }

        flushPatch()
        return patches
    }

    /// Parse unified diff output into a flat record stream suitable for rendering and row-model construction.
    package static func parseDocument(unifiedDiff: String) -> VVParsedDiffDocument {
        let patches = parseFilePatches(unifiedDiff: unifiedDiff)
        var records: [VVParsedDiffRecord] = []
        records.reserveCapacity(patches.reduce(into: 0) { partial, patch in
            partial += patch.metadataLines.count + patch.hunks.count
            partial += patch.hunks.reduce(0) { $0 + $1.rawLines.count }
            if patch.headerLine != nil {
                partial += 1
            }
        })

        for patch in patches {
            if let headerLine = patch.headerLine {
                records.append(.fileHeader(patch.filePath, headerLine))
            }

            for metadataLine in patch.metadataLines {
                records.append(.metadata(metadataLine))
            }

            for hunk in patch.hunks {
                records.append(
                    .hunkHeader(
                        VVParsedDiffHunkHeader(
                            rawLine: hunk.headerLine,
                            oldStart: hunk.oldStart,
                            oldCount: hunk.oldCount,
                            newStart: hunk.newStart,
                            newCount: hunk.newCount
                        )
                    )
                )

                for line in hunk.rawLines {
                    switch line.kind {
                    case .context:
                        records.append(
                            .line(
                                VVParsedDiffLine(
                                    kind: .context,
                                    text: line.text,
                                    oldLineNumber: line.oldLineNumber,
                                    newLineNumber: line.newLineNumber
                                )
                            )
                        )
                    case .added:
                        records.append(
                            .line(
                                VVParsedDiffLine(
                                    kind: .added,
                                    text: line.text,
                                    oldLineNumber: line.oldLineNumber,
                                    newLineNumber: line.newLineNumber
                                )
                            )
                        )
                    case .deleted:
                        records.append(
                            .line(
                                VVParsedDiffLine(
                                    kind: .deleted,
                                    text: line.text,
                                    oldLineNumber: line.oldLineNumber,
                                    newLineNumber: line.newLineNumber
                                )
                            )
                        )
                    case .metadata:
                        records.append(.metadata(line.text))
                    }
                }
            }
        }

        return VVParsedDiffDocument(records: records)
    }

    /// Parse unified diff output into hunks.
    /// - Parameter unifiedDiff: The unified diff string (output of `git diff`)
    /// - Returns: Array of diff hunks
    public static func parse(unifiedDiff: String) -> [VVDiffHunk] {
        parseFilePatches(unifiedDiff: unifiedDiff).flatMap(\.hunks)
    }

    /// Convert hunks to line-level git status for gutter display
    /// - Parameter hunks: Parsed diff hunks
    /// - Returns: Array of line statuses sorted by line number
    public static func lineStatuses(from hunks: [VVDiffHunk]) -> [VVLineGitStatus] {
        var statuses: [VVLineGitStatus] = []
        statuses.reserveCapacity(hunks.count * 4)

        for hunk in hunks {
            var lastDeletedLine: Int?

            for lineDiff in hunk.lines {
                switch lineDiff.type {
                case .added:
                    if lastDeletedLine != nil {
                        statuses.append(VVLineGitStatus(lineNumber: lineDiff.lineNumber, status: .modified))
                        lastDeletedLine = nil
                    } else {
                        statuses.append(VVLineGitStatus(lineNumber: lineDiff.lineNumber, status: .added))
                    }

                case .deleted:
                    lastDeletedLine = lineDiff.lineNumber

                case .context:
                    if lastDeletedLine != nil {
                        statuses.append(VVLineGitStatus(lineNumber: lineDiff.lineNumber, status: .deleted))
                        lastDeletedLine = nil
                    }
                }
            }

            if lastDeletedLine != nil {
                let lastLineNumber = hunk.newStart + hunk.newCount
                statuses.append(VVLineGitStatus(lineNumber: lastLineNumber, status: .deleted))
            }
        }

        let sorted = statuses.sorted { $0.lineNumber < $1.lineNumber }
        var unique: [VVLineGitStatus] = []
        var lastLine = -1

        for status in sorted where status.lineNumber != lastLine {
            unique.append(status)
            lastLine = status.lineNumber
        }

        return unique
    }
}

private extension VVDiffParser {
    struct FilePatchBuilder {
        var headerLine: String?
        var oldPath: String?
        var newPath: String?
        var filePath: String?
        var metadataLines: [String] = []
        var hunks: [VVDiffHunk] = []

        var hasContent: Bool {
            headerLine != nil ||
            oldPath != nil ||
            newPath != nil ||
            !metadataLines.isEmpty ||
            !hunks.isEmpty
        }

        func shouldStartNewPatch(beforeFileMarker: Bool) -> Bool {
            if beforeFileMarker {
                return !hunks.isEmpty
            }
            return !hunks.isEmpty && headerLine == nil
        }

        func build() -> VVDiffFilePatch {
            let resolvedFilePath = preferredFilePath(explicit: filePath, oldPath: oldPath, newPath: newPath)
            return VVDiffFilePatch(
                headerLine: headerLine,
                oldPath: oldPath,
                newPath: newPath,
                filePath: resolvedFilePath ?? "workspace.diff",
                metadataLines: metadataLines,
                hunks: hunks
            )
        }
    }

    struct HunkBuilder {
        let oldStart: Int
        let oldCount: Int
        let newStart: Int
        let newCount: Int
        let headerLine: String
        var lineDiffs: [LineDiff] = []
        var rawLines: [VVDiffRawLine] = []
        var addedCount = 0
        var deletedCount = 0
        var nextOldLine: Int
        var nextNewLine: Int

        init(oldStart: Int, oldCount: Int, newStart: Int, newCount: Int, headerLine: String) {
            self.oldStart = oldStart
            self.oldCount = oldCount
            self.newStart = newStart
            self.newCount = newCount
            self.headerLine = headerLine
            self.nextOldLine = oldStart
            self.nextNewLine = newStart
        }

        mutating func append(_ line: String) {
            if line.hasPrefix("+") && !line.hasPrefix("+++") {
                let text = String(line.dropFirst())
                rawLines.append(
                    VVDiffRawLine(kind: .added, text: text, oldLineNumber: nil, newLineNumber: nextNewLine)
                )
                lineDiffs.append(LineDiff(lineNumber: nextNewLine, type: .added, content: text))
                addedCount += 1
                nextNewLine += 1
                return
            }

            if line.hasPrefix("-") && !line.hasPrefix("---") {
                let text = String(line.dropFirst())
                rawLines.append(
                    VVDiffRawLine(kind: .deleted, text: text, oldLineNumber: nextOldLine, newLineNumber: nil)
                )
                lineDiffs.append(LineDiff(lineNumber: nextOldLine, type: .deleted, content: text))
                deletedCount += 1
                nextOldLine += 1
                return
            }

            if line.hasPrefix(" ") || line.isEmpty {
                let text = line.hasPrefix(" ") ? String(line.dropFirst()) : line
                rawLines.append(
                    VVDiffRawLine(kind: .context, text: text, oldLineNumber: nextOldLine, newLineNumber: nextNewLine)
                )
                lineDiffs.append(LineDiff(lineNumber: nextNewLine, type: .context, content: text))
                nextOldLine += 1
                nextNewLine += 1
                return
            }

            if line.hasPrefix("\\") {
                rawLines.append(
                    VVDiffRawLine(kind: .metadata, text: line, oldLineNumber: nil, newLineNumber: nil)
                )
                return
            }

            rawLines.append(
                VVDiffRawLine(kind: .context, text: line, oldLineNumber: nextOldLine, newLineNumber: nextNewLine)
            )
            lineDiffs.append(LineDiff(lineNumber: nextNewLine, type: .context, content: line))
            nextOldLine += 1
            nextNewLine += 1
        }

        func build() -> VVDiffHunk {
            let changeType: VVDiffHunk.ChangeType
            if deletedCount == 0 && addedCount > 0 {
                changeType = .added
            } else if addedCount == 0 && deletedCount > 0 {
                changeType = .deleted
            } else {
                changeType = .modified
            }

            return VVDiffHunk(
                oldStart: oldStart,
                oldCount: oldCount,
                newStart: newStart,
                newCount: newCount,
                headerLine: headerLine,
                changeType: changeType,
                lines: lineDiffs,
                rawLines: rawLines
            )
        }
    }

    static func normalizedLines(from unifiedDiff: String) -> [String] {
        var lines = unifiedDiff.split(omittingEmptySubsequences: false, whereSeparator: \.isNewline).map(String.init)
        if lines.last?.isEmpty == true {
            _ = lines.popLast()
        }
        return lines
    }

    static func isMetadataLine(_ line: String) -> Bool {
        line.hasPrefix("index ") ||
        line.hasPrefix("--- ") ||
        line.hasPrefix("+++ ") ||
        line.hasPrefix("old mode ") ||
        line.hasPrefix("new mode ") ||
        line.hasPrefix("new file mode ") ||
        line.hasPrefix("deleted file mode ") ||
        line.hasPrefix("rename from ") ||
        line.hasPrefix("rename to ") ||
        line.hasPrefix("copy from ") ||
        line.hasPrefix("copy to ") ||
        line.hasPrefix("similarity index ") ||
        line.hasPrefix("dissimilarity index ") ||
        line.hasPrefix("Binary files ")
    }

    static func parseHunkHeader(_ line: String) -> (oldStart: Int, oldCount: Int, newStart: Int, newCount: Int)? {
        guard let regex = hunkHeaderRegex,
              let match = regex.firstMatch(in: line, range: NSRange(line.startIndex..., in: line)) else {
            return nil
        }

        func extractInt(_ range: NSRange) -> Int? {
            guard range.location != NSNotFound,
                  let swiftRange = Range(range, in: line) else {
                return nil
            }
            return Int(line[swiftRange])
        }

        guard let oldStart = extractInt(match.range(at: 1)),
              let newStart = extractInt(match.range(at: 3)) else {
            return nil
        }

        let oldCount = extractInt(match.range(at: 2)) ?? 1
        let newCount = extractInt(match.range(at: 4)) ?? 1
        return (oldStart, oldCount, newStart, newCount)
    }

    static func filePath(fromDiffHeader line: String) -> String? {
        let parts = line.split(separator: " ")
        guard parts.count >= 4 else { return nil }
        return normalizedFileMarkerPath(String(parts[3]))
    }

    static func normalizedFileMarkerPath(_ rawPath: String) -> String? {
        if rawPath == "/dev/null" {
            return nil
        }
        if rawPath.hasPrefix("a/") || rawPath.hasPrefix("b/") {
            return String(rawPath.dropFirst(2))
        }
        return rawPath.isEmpty ? nil : rawPath
    }

    static func preferredFilePath(explicit: String?, oldPath: String?, newPath: String?) -> String? {
        if let newPath {
            return newPath
        }
        if let oldPath {
            return oldPath
        }
        return explicit
    }
}

// MARK: - Convenience Extensions

extension VVDiffParser {
    /// Check if a line has git changes
    public static func hasChanges(at lineNumber: Int, in hunks: [VVDiffHunk]) -> VVLineGitStatus.Status? {
        for hunk in hunks {
            if lineNumber >= hunk.newStart && lineNumber < hunk.newStart + hunk.newCount {
                for lineDiff in hunk.lines where lineDiff.type != .deleted {
                    if lineDiff.lineNumber == lineNumber {
                        switch lineDiff.type {
                        case .added:
                            return .added
                        case .context:
                            return nil
                        case .deleted:
                            continue
                        }
                    }
                }

                if hunk.changeType == .modified {
                    return .modified
                }
            }
        }
        return nil
    }

    /// Get the range of lines affected by git changes
    public static func changedLineRanges(from hunks: [VVDiffHunk]) -> [(range: ClosedRange<Int>, type: VVDiffHunk.ChangeType)] {
        hunks.compactMap { hunk in
            guard hunk.newCount > 0 else { return nil }
            let range = hunk.newStart...(hunk.newStart + hunk.newCount - 1)
            return (range: range, type: hunk.changeType)
        }
    }
}
