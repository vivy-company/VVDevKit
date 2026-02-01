import AppKit

/// Custom NSTextStorage backed by a PieceTable for O(log n) editing performance
/// Drop-in replacement for NSTextStorage with better performance for large files
public class PieceTableTextStorage: NSTextStorage {
    // MARK: - Storage

    private let pieceTable: PieceTable
    private var _attributes: [Int: [NSAttributedString.Key: Any]] = [:]

    // Cache the string to avoid repeated materialization
    private var cachedString: String?
    private var cacheValid = false

    // MARK: - Initialization

    public override init() {
        self.pieceTable = PieceTable()
        super.init()
    }

    /// Create storage with initial text content
    public static func with(text: String) -> PieceTableTextStorage {
        let storage = PieceTableTextStorage()
        if !text.isEmpty {
            storage.replaceCharacters(in: NSRange(location: 0, length: 0), with: text)
        }
        return storage
    }

    required init?(coder: NSCoder) {
        self.pieceTable = PieceTable()
        super.init(coder: coder)
    }

    required init?(pasteboardPropertyList propertyList: Any, ofType type: NSPasteboard.PasteboardType) {
        self.pieceTable = PieceTable()
        super.init(pasteboardPropertyList: propertyList, ofType: type)
    }

    // MARK: - NSTextStorage Required Overrides

    public override var string: String {
        if cacheValid, let cached = cachedString {
            return cached
        }
        let str = pieceTable.string
        cachedString = str
        cacheValid = true
        return str
    }

    public override func attributes(at location: Int, effectiveRange range: NSRangePointer?) -> [NSAttributedString.Key: Any] {
        guard location >= 0, location < pieceTable.length else {
            range?.pointee = NSRange(location: 0, length: 0)
            return [:]
        }

        // Find attributes at this location
        // For simplicity, we store attributes per-character
        // A production implementation would use an interval tree
        let attrs = _attributes[location] ?? [:]

        // Calculate effective range (simplified - returns single character range)
        // A production impl would find the actual run of same attributes
        range?.pointee = NSRange(location: location, length: 1)

        return attrs
    }

    public override func replaceCharacters(in range: NSRange, with str: String) {
        beginEditing()

        let delta = str.utf16.count - range.length

        // Update piece table
        pieceTable.replace(range: range, with: str)

        // Invalidate cache
        cacheValid = false

        // Shift attributes after the edit
        if delta != 0 {
            var newAttributes: [Int: [NSAttributedString.Key: Any]] = [:]
            for (loc, attrs) in _attributes {
                if loc < range.location {
                    newAttributes[loc] = attrs
                } else if loc >= range.location + range.length {
                    newAttributes[loc + delta] = attrs
                }
                // Attributes in deleted range are removed
            }
            _attributes = newAttributes
        }

        // Notify of change
        edited(.editedCharacters, range: range, changeInLength: delta)

        endEditing()
    }

    public override func setAttributes(_ attrs: [NSAttributedString.Key: Any]?, range: NSRange) {
        beginEditing()

        // Set attributes for range
        for i in range.location..<(range.location + range.length) {
            if i < pieceTable.length {
                _attributes[i] = attrs ?? [:]
            }
        }

        edited(.editedAttributes, range: range, changeInLength: 0)

        endEditing()
    }

    // MARK: - Performance Optimizations

    /// Direct access to piece table length (faster than string.count)
    public var pieceTableLength: Int {
        pieceTable.length
    }

    /// Direct substring access without materializing full string
    public func substringWithPieceTable(in range: NSRange) -> String {
        pieceTable.substring(in: range)
    }

    /// Get line count efficiently
    public var lineCount: Int {
        pieceTable.lineCount
    }
}
