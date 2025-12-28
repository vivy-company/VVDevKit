import Foundation

/// Parser for unified diff format (git diff output)
public struct VVDiffParser {
    /// Parse unified diff output into hunks
    /// - Parameter unifiedDiff: The unified diff string (output of `git diff`)
    /// - Returns: Array of diff hunks
    public static func parse(unifiedDiff: String) -> [VVDiffHunk] {
        var hunks: [VVDiffHunk] = []
        let lines = unifiedDiff.components(separatedBy: .newlines)

        var i = 0
        while i < lines.count {
            let line = lines[i]

            // Look for hunk header: @@ -oldStart,oldCount +newStart,newCount @@
            if line.hasPrefix("@@") {
                if let hunk = parseHunk(lines: lines, startIndex: &i) {
                    hunks.append(hunk)
                }
            } else {
                i += 1
            }
        }

        return hunks
    }

    /// Parse a single hunk starting at the given index
    private static func parseHunk(lines: [String], startIndex: inout Int) -> VVDiffHunk? {
        let headerLine = lines[startIndex]

        // Parse the header: @@ -oldStart,oldCount +newStart,newCount @@
        guard let (oldStart, oldCount, newStart, newCount) = parseHunkHeader(headerLine) else {
            startIndex += 1
            return nil
        }

        startIndex += 1

        var lineDiffs: [LineDiff] = []
        var addedCount = 0
        var deletedCount = 0
        var newLineNumber = newStart
        var oldLineNumber = oldStart

        // Parse the hunk content
        while startIndex < lines.count {
            let line = lines[startIndex]

            // Stop at next hunk or end of diff
            if line.hasPrefix("@@") || line.hasPrefix("diff ") || line.hasPrefix("---") || line.hasPrefix("+++") {
                break
            }

            if line.hasPrefix("+") && !line.hasPrefix("+++") {
                // Added line
                let content = String(line.dropFirst())
                lineDiffs.append(LineDiff(lineNumber: newLineNumber, type: .added, content: content))
                addedCount += 1
                newLineNumber += 1
            } else if line.hasPrefix("-") && !line.hasPrefix("---") {
                // Deleted line
                let content = String(line.dropFirst())
                lineDiffs.append(LineDiff(lineNumber: oldLineNumber, type: .deleted, content: content))
                deletedCount += 1
                oldLineNumber += 1
            } else if line.hasPrefix(" ") || line.isEmpty {
                // Context line
                let content = line.hasPrefix(" ") ? String(line.dropFirst()) : line
                lineDiffs.append(LineDiff(lineNumber: newLineNumber, type: .context, content: content))
                newLineNumber += 1
                oldLineNumber += 1
            } else if line.hasPrefix("\\") {
                // "\ No newline at end of file" - skip
            } else {
                // Unknown line format, treat as context
                lineDiffs.append(LineDiff(lineNumber: newLineNumber, type: .context, content: line))
                newLineNumber += 1
                oldLineNumber += 1
            }

            startIndex += 1
        }

        // Determine change type
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
            changeType: changeType,
            lines: lineDiffs
        )
    }

    /// Parse the hunk header line
    /// Format: @@ -oldStart,oldCount +newStart,newCount @@
    private static func parseHunkHeader(_ line: String) -> (Int, Int, Int, Int)? {
        // Regex: @@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@
        let pattern = #"@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@"#

        guard let regex = try? NSRegularExpression(pattern: pattern),
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

    /// Convert hunks to line-level git status for gutter display
    /// - Parameter hunks: Parsed diff hunks
    /// - Returns: Array of line statuses sorted by line number
    public static func lineStatuses(from hunks: [VVDiffHunk]) -> [VVLineGitStatus] {
        var statuses: [VVLineGitStatus] = []

        for hunk in hunks {
            var lastDeletedLine: Int?

            for lineDiff in hunk.lines {
                switch lineDiff.type {
                case .added:
                    // If there was a preceding deletion, this is a modification
                    if lastDeletedLine != nil {
                        statuses.append(VVLineGitStatus(lineNumber: lineDiff.lineNumber, status: .modified))
                        lastDeletedLine = nil
                    } else {
                        statuses.append(VVLineGitStatus(lineNumber: lineDiff.lineNumber, status: .added))
                    }

                case .deleted:
                    lastDeletedLine = lineDiff.lineNumber

                case .context:
                    // If there's a pending deletion without a corresponding addition,
                    // mark the deletion indicator on the next line
                    if let deletedLine = lastDeletedLine {
                        statuses.append(VVLineGitStatus(lineNumber: lineDiff.lineNumber, status: .deleted))
                        lastDeletedLine = nil
                    }
                }
            }

            // Handle trailing deletion
            if let _ = lastDeletedLine {
                // Mark deletion at the end of the hunk
                let lastLineNumber = hunk.newStart + hunk.newCount
                statuses.append(VVLineGitStatus(lineNumber: lastLineNumber, status: .deleted))
            }
        }

        // Sort by line number and remove duplicates
        let sorted = statuses.sorted { $0.lineNumber < $1.lineNumber }
        var unique: [VVLineGitStatus] = []
        var lastLine = -1

        for status in sorted {
            if status.lineNumber != lastLine {
                unique.append(status)
                lastLine = status.lineNumber
            }
        }

        return unique
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

                // Check if this line is in a modified region
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
