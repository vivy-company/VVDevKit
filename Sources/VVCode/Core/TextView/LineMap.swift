import Foundation

/// Efficient line number <-> character offset mapping
public struct LineMap {
    /// Byte offsets of line starts (0-indexed)
    private var lineStarts: [Int]

    /// Total character count
    private var totalLength: Int

    /// Initialize with text
    public init(text: String) {
        self.lineStarts = [0]  // Line 1 starts at offset 0
        self.totalLength = text.utf16.count

        var offset = 0
        for char in text {
            if char == "\n" {
                lineStarts.append(offset + 1)
            }
            offset += char.utf16.count
        }
    }

    /// Initialize empty
    public init() {
        self.lineStarts = [0]
        self.totalLength = 0
    }

    // MARK: - Queries

    /// Number of lines
    public var lineCount: Int {
        lineStarts.count
    }

    /// Get line number (1-indexed) for a character offset
    public func lineNumber(forOffset offset: Int) -> Int {
        // Binary search for the line
        var low = 0
        var high = lineStarts.count - 1

        while low < high {
            let mid = (low + high + 1) / 2
            if lineStarts[mid] <= offset {
                low = mid
            } else {
                high = mid - 1
            }
        }

        return low + 1  // Convert to 1-indexed
    }

    /// Get character offset for line start (1-indexed line)
    public func offset(forLine line: Int) -> Int {
        guard line > 0 && line <= lineStarts.count else { return 0 }
        return lineStarts[line - 1]
    }

    /// Get the range (start offset, length) for a line (1-indexed)
    public func range(forLine line: Int) -> (start: Int, length: Int) {
        guard line > 0 && line <= lineStarts.count else {
            return (0, 0)
        }

        let start = lineStarts[line - 1]
        let end: Int

        if line < lineStarts.count {
            end = lineStarts[line]
        } else {
            end = totalLength
        }

        return (start, end - start)
    }

    /// Get column (1-indexed) for a character offset
    public func column(forOffset offset: Int) -> Int {
        let line = lineNumber(forOffset: offset)
        let lineStart = self.offset(forLine: line)
        return offset - lineStart + 1
    }

    /// Get line and column (both 1-indexed) for a character offset
    public func position(forOffset offset: Int) -> (line: Int, column: Int) {
        let line = lineNumber(forOffset: offset)
        let lineStart = self.offset(forLine: line)
        return (line, max(1, offset - lineStart + 1))
    }

    /// Get character offset for a position (1-indexed line and column)
    public func offset(forLine line: Int, column: Int) -> Int {
        let lineStart = offset(forLine: line)
        return lineStart + column - 1
    }

    // MARK: - Updates

    /// Update the line map after a text edit
    public mutating func update(after edit: TextEdit, in newText: String) {
        // For simplicity, rebuild the line map
        // TODO: Optimize for incremental updates
        self = LineMap(text: newText)
    }

    /// Text edit information
    public struct TextEdit {
        public let range: NSRange
        public let newLength: Int

        public init(range: NSRange, newLength: Int) {
            self.range = range
            self.newLength = newLength
        }
    }
}

// MARK: - Static Helpers

extension LineMap {
    /// Count lines in a string (static helper)
    public static func lineCount(in text: String) -> Int {
        guard !text.isEmpty else { return 1 }
        // Use UTF8 view for faster iteration
        var count = 1
        for byte in text.utf8 {
            if byte == 0x0A { // newline
                count += 1
            }
        }
        return count
    }

    /// Get position (line, column) at offset in a string (static helper)
    public static func position(at offset: Int, in text: String) -> (line: Int, column: Int) {
        let map = LineMap(text: text)
        return map.position(forOffset: offset)
    }

    /// Get offset for position (line, column) in a string (static helper)
    public static func offset(at position: (line: Int, column: Int), in text: String) -> Int {
        let map = LineMap(text: text)
        let lineStart = map.offset(forLine: position.line)
        return max(0, lineStart + position.column - 1)
    }

    /// Get the text of a specific line (1-indexed)
    public static func lineText(at lineNumber: Int, in text: String) -> String? {
        var currentLine = 1

        for index in text.indices {
            if currentLine == lineNumber {
                // Find the end of this line
                if let endIndex = text[index...].firstIndex(of: "\n") {
                    return String(text[index..<endIndex])
                } else {
                    return String(text[index...])
                }
            }

            if text[index] == "\n" {
                currentLine += 1
            }
        }

        return nil
    }
}
