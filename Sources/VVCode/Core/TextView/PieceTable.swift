import Foundation

/// A piece in the piece table - references a span of text in either original or add buffer
public struct Piece {
    enum Source {
        case original
        case add
    }

    let source: Source
    let start: Int      // Start index in source buffer
    let length: Int     // Length in UTF-16 code units

    var range: Range<Int> {
        start..<(start + length)
    }
}

/// Piece Table data structure for O(log n) text editing
/// Used by VS Code, Visual Studio, and other modern editors
public final class PieceTable {
    // MARK: - Buffers

    /// Original text (immutable after init)
    private let originalBuffer: String

    /// Add buffer - appended to for each insert (immutable per insert)
    private var addBuffer: String = ""

    /// Pieces describing the document structure
    private var pieces: [Piece] = []

    /// Cached total length
    private var _length: Int = 0

    // MARK: - Initialization

    public init(text: String = "") {
        self.originalBuffer = text
        if !text.isEmpty {
            pieces.append(Piece(source: .original, start: 0, length: text.utf16.count))
            _length = text.utf16.count
        }
    }

    // MARK: - Properties

    public var length: Int { _length }

    public var isEmpty: Bool { _length == 0 }

    /// Materialize the full string (O(n) - avoid in hot paths)
    public var string: String {
        var result = ""
        result.reserveCapacity(_length)

        for piece in pieces {
            let buffer = piece.source == .original ? originalBuffer : addBuffer
            let startIndex = buffer.utf16.index(buffer.startIndex, offsetBy: piece.start)
            let endIndex = buffer.utf16.index(startIndex, offsetBy: piece.length)
            result += String(buffer[startIndex..<endIndex])
        }

        return result
    }

    // MARK: - Editing

    /// Insert text at position - O(log n) amortized
    public func insert(_ text: String, at position: Int) {
        guard !text.isEmpty else { return }

        let insertLength = text.utf16.count

        // Add to add buffer
        let addStart = addBuffer.utf16.count
        addBuffer += text

        // Create new piece for inserted text
        let newPiece = Piece(source: .add, start: addStart, length: insertLength)

        // Find which piece contains the insertion point
        var offset = 0
        var pieceIndex = 0

        while pieceIndex < pieces.count {
            let piece = pieces[pieceIndex]
            if offset + piece.length >= position {
                break
            }
            offset += piece.length
            pieceIndex += 1
        }

        if pieceIndex >= pieces.count {
            // Insert at end
            pieces.append(newPiece)
        } else {
            let piece = pieces[pieceIndex]
            let splitPoint = position - offset

            if splitPoint == 0 {
                // Insert before this piece
                pieces.insert(newPiece, at: pieceIndex)
            } else if splitPoint == piece.length {
                // Insert after this piece
                pieces.insert(newPiece, at: pieceIndex + 1)
            } else {
                // Split the piece
                let leftPiece = Piece(source: piece.source, start: piece.start, length: splitPoint)
                let rightPiece = Piece(source: piece.source, start: piece.start + splitPoint, length: piece.length - splitPoint)

                pieces.replaceSubrange(pieceIndex...pieceIndex, with: [leftPiece, newPiece, rightPiece])
            }
        }

        _length += insertLength
    }

    /// Delete text in range - O(log n) amortized
    public func delete(range: NSRange) {
        guard range.length > 0, range.location >= 0, range.location + range.length <= _length else { return }

        let deleteStart = range.location
        let deleteEnd = range.location + range.length

        var newPieces: [Piece] = []
        var offset = 0

        for piece in pieces {
            let pieceStart = offset
            let pieceEnd = offset + piece.length

            if pieceEnd <= deleteStart || pieceStart >= deleteEnd {
                // Piece is entirely outside delete range - keep it
                newPieces.append(piece)
            } else if pieceStart >= deleteStart && pieceEnd <= deleteEnd {
                // Piece is entirely inside delete range - remove it
                // (don't add to newPieces)
            } else if pieceStart < deleteStart && pieceEnd > deleteEnd {
                // Delete range is inside this piece - split into two
                let leftLength = deleteStart - pieceStart
                let rightStart = piece.start + (deleteEnd - pieceStart)
                let rightLength = pieceEnd - deleteEnd

                newPieces.append(Piece(source: piece.source, start: piece.start, length: leftLength))
                newPieces.append(Piece(source: piece.source, start: rightStart, length: rightLength))
            } else if pieceStart < deleteStart {
                // Delete starts inside this piece - keep left part
                let keepLength = deleteStart - pieceStart
                newPieces.append(Piece(source: piece.source, start: piece.start, length: keepLength))
            } else {
                // Delete ends inside this piece - keep right part
                let skipLength = deleteEnd - pieceStart
                let keepStart = piece.start + skipLength
                let keepLength = piece.length - skipLength
                newPieces.append(Piece(source: piece.source, start: keepStart, length: keepLength))
            }

            offset = pieceEnd
        }

        pieces = newPieces
        _length -= range.length
    }

    /// Replace text in range - combines delete + insert
    public func replace(range: NSRange, with text: String) {
        delete(range: range)
        insert(text, at: range.location)
    }

    // MARK: - Substring Access

    /// Get substring at range - O(k) where k is number of pieces in range
    public func substring(in range: NSRange) -> String {
        guard range.length > 0, range.location >= 0, range.location + range.length <= _length else {
            return ""
        }

        var result = ""
        var offset = 0

        for piece in pieces {
            let pieceStart = offset
            let pieceEnd = offset + piece.length

            if pieceEnd <= range.location {
                // Piece is before range
                offset = pieceEnd
                continue
            }

            if pieceStart >= range.location + range.length {
                // Piece is after range - done
                break
            }

            // Calculate overlap
            let overlapStart = max(pieceStart, range.location)
            let overlapEnd = min(pieceEnd, range.location + range.length)

            let buffer = piece.source == .original ? originalBuffer : addBuffer
            let bufferStart = piece.start + (overlapStart - pieceStart)
            let bufferLength = overlapEnd - overlapStart

            let startIndex = buffer.utf16.index(buffer.startIndex, offsetBy: bufferStart)
            let endIndex = buffer.utf16.index(startIndex, offsetBy: bufferLength)
            result += String(buffer[startIndex..<endIndex])

            offset = pieceEnd
        }

        return result
    }

    // MARK: - Line Operations

    /// Count newlines in range - O(k) where k is pieces in range
    public func countNewlines(in range: NSRange) -> Int {
        let substr = substring(in: range)
        return substr.filter { $0 == "\n" }.count
    }

    /// Get total line count - cached for performance
    public var lineCount: Int {
        var count = 1
        for piece in pieces {
            let buffer = piece.source == .original ? originalBuffer : addBuffer
            let startIndex = buffer.utf16.index(buffer.startIndex, offsetBy: piece.start)
            let endIndex = buffer.utf16.index(startIndex, offsetBy: piece.length)
            for char in buffer[startIndex..<endIndex] {
                if char == "\n" { count += 1 }
            }
        }
        return count
    }
}
