import Foundation

/// Parser for git blame output
public struct VVBlameParser {
    /// Parse git blame --porcelain output
    /// - Parameter porcelainOutput: Output from `git blame --porcelain <file>`
    /// - Returns: Array of blame info for each line
    public static func parse(porcelainOutput: String) -> [VVBlameInfo] {
        var blameInfos: [VVBlameInfo] = []
        let lines = porcelainOutput.components(separatedBy: .newlines)

        var i = 0
        var lineNumber = 1

        // Commit info cache (commits appear multiple times)
        var commitCache: [String: CommitInfo] = [:]

        while i < lines.count {
            let line = lines[i]

            // First line of a blame entry: <sha> <original-line> <final-line> [<num-lines>]
            guard !line.isEmpty else {
                i += 1
                continue
            }

            let components = line.split(separator: " ")
            guard components.count >= 3,
                  let sha = components.first,
                  sha.count >= 40 || sha.allSatisfy({ $0.isHexDigit || $0 == "^" }) else {
                i += 1
                continue
            }

            let commit = String(sha).replacingOccurrences(of: "^", with: "")
            let isUncommitted = commit.allSatisfy { $0 == "0" }

            // Look for cached commit info or parse new one
            var commitInfo: CommitInfo

            if let cached = commitCache[commit] {
                commitInfo = cached
                // Skip to content line
                while i < lines.count && !lines[i].hasPrefix("\t") {
                    i += 1
                }
            } else {
                // Parse commit headers
                commitInfo = CommitInfo()
                i += 1

                while i < lines.count {
                    let headerLine = lines[i]

                    if headerLine.hasPrefix("\t") {
                        // Content line reached
                        break
                    }

                    if headerLine.hasPrefix("author ") {
                        commitInfo.author = String(headerLine.dropFirst(7))
                    } else if headerLine.hasPrefix("author-mail ") {
                        let email = String(headerLine.dropFirst(12))
                        commitInfo.authorEmail = email.trimmingCharacters(in: CharacterSet(charactersIn: "<>"))
                    } else if headerLine.hasPrefix("author-time ") {
                        if let timestamp = Double(headerLine.dropFirst(12)) {
                            commitInfo.date = Date(timeIntervalSince1970: timestamp)
                        }
                    } else if headerLine.hasPrefix("summary ") {
                        commitInfo.summary = String(headerLine.dropFirst(8))
                    }

                    i += 1
                }

                commitCache[commit] = commitInfo
            }

            // Create blame info
            let blameInfo = VVBlameInfo(
                lineNumber: lineNumber,
                commit: commit,
                author: commitInfo.author ?? "Unknown",
                authorEmail: commitInfo.authorEmail,
                date: commitInfo.date ?? Date(),
                summary: commitInfo.summary,
                isUncommitted: isUncommitted
            )

            blameInfos.append(blameInfo)
            lineNumber += 1

            // Skip content line
            if i < lines.count && lines[i].hasPrefix("\t") {
                i += 1
            }
        }

        return blameInfos
    }

    /// Parse standard git blame output (non-porcelain)
    /// Format: <sha> (<author> <date> <time> <timezone> <line-number>) <content>
    public static func parseStandard(output: String) -> [VVBlameInfo] {
        var blameInfos: [VVBlameInfo] = []
        let lines = output.components(separatedBy: .newlines)

        let pattern = #"^(\^?[a-f0-9]+)\s+(?:\((.+?)\s+(\d{4}-\d{2}-\d{2})\s+\d{2}:\d{2}:\d{2}\s+[+-]\d{4}\s+(\d+)\))"#
        guard let regex = try? NSRegularExpression(pattern: pattern) else {
            return []
        }

        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "yyyy-MM-dd"

        for line in lines {
            let range = NSRange(line.startIndex..., in: line)
            guard let match = regex.firstMatch(in: line, range: range) else {
                continue
            }

            func extract(_ index: Int) -> String? {
                guard match.range(at: index).location != NSNotFound,
                      let range = Range(match.range(at: index), in: line) else {
                    return nil
                }
                return String(line[range])
            }

            guard let commit = extract(1),
                  let author = extract(2),
                  let dateString = extract(3),
                  let lineNumberString = extract(4),
                  let lineNumber = Int(lineNumberString) else {
                continue
            }

            let date = dateFormatter.date(from: dateString) ?? Date()
            let cleanCommit = commit.replacingOccurrences(of: "^", with: "")
            let isUncommitted = cleanCommit.allSatisfy { $0 == "0" }

            blameInfos.append(VVBlameInfo(
                lineNumber: lineNumber,
                commit: cleanCommit,
                author: author.trimmingCharacters(in: .whitespaces),
                date: date,
                isUncommitted: isUncommitted
            ))
        }

        return blameInfos
    }

    /// Helper struct for parsing
    private struct CommitInfo {
        var author: String?
        var authorEmail: String?
        var date: Date?
        var summary: String?
    }
}

// MARK: - Convenience

extension VVBlameParser {
    /// Get blame info for a specific line
    public static func blame(forLine lineNumber: Int, in blameInfos: [VVBlameInfo]) -> VVBlameInfo? {
        blameInfos.first { $0.lineNumber == lineNumber }
    }

    /// Get blame info for a range of lines
    public static func blame(forRange range: ClosedRange<Int>, in blameInfos: [VVBlameInfo]) -> [VVBlameInfo] {
        blameInfos.filter { range.contains($0.lineNumber) }
    }
}

// MARK: - Character Extension

extension Character {
    var isHexDigit: Bool {
        self.isNumber || ("a"..."f").contains(self) || ("A"..."F").contains(self)
    }
}
