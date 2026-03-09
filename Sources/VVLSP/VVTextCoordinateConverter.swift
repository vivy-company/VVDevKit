import Foundation

/// Maps between UTF-16 offsets and LSP-style line/character positions.
struct VVTextCoordinateConverter {
    private let text: NSString
    private let textLength: Int
    private let lineStarts: [Int]

    init(text: String) {
        self.text = text as NSString
        self.textLength = self.text.length

        var starts: [Int] = [0]
        starts.reserveCapacity(max(1, textLength / 32))

        var offset = 0
        for codeUnit in text.utf16 {
            offset += 1
            if codeUnit == 0x0A {
                starts.append(offset)
            }
        }

        self.lineStarts = starts
    }

    func position(atUTF16Offset offset: Int) -> VVTextPosition {
        let clampedOffset = max(0, min(offset, textLength))
        let lineIndex = lineIndex(containing: clampedOffset)
        let character = clampedOffset - lineStarts[lineIndex]
        return VVTextPosition(line: lineIndex, character: character)
    }

    func utf16Offset(for position: VVTextPosition) -> Int? {
        guard position.line >= 0, position.line < lineStarts.count else {
            return nil
        }

        let lineStart = lineStarts[position.line]
        let lineEnd = lineContentEnd(forLineAt: position.line)
        let lineLength = lineEnd - lineStart
        guard position.character >= 0, position.character <= lineLength else {
            return nil
        }

        return lineStart + position.character
    }

    func nsRange(for range: VVTextRange) -> NSRange? {
        guard let start = utf16Offset(for: range.start),
              let end = utf16Offset(for: range.end),
              end >= start else {
            return nil
        }

        return NSRange(location: start, length: end - start)
    }

    func substring(utf16Range: NSRange) -> String? {
        guard utf16Range.location >= 0,
              utf16Range.length >= 0,
              utf16Range.location + utf16Range.length <= textLength else {
            return nil
        }

        return text.substring(with: utf16Range)
    }

    private func lineContentEnd(forLineAt index: Int) -> Int {
        if index + 1 < lineStarts.count {
            return max(lineStarts[index], lineStarts[index + 1] - 1)
        }
        return textLength
    }

    private func lineIndex(containing offset: Int) -> Int {
        var low = 0
        var high = lineStarts.count

        while low < high {
            let mid = (low + high) / 2
            if lineStarts[mid] <= offset {
                low = mid + 1
            } else {
                high = mid
            }
        }

        return max(0, low - 1)
    }
}
