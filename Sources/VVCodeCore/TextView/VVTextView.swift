import AppKit

/// Custom NSTextView for code editing
public class VVTextView: NSTextView {
    // MARK: - Properties

    /// Current line highlight color
    public var currentLineHighlightColor: NSColor?

    /// Whether to highlight the current line
    public var highlightCurrentLine: Bool = true

    /// Tab width in characters
    public var tabWidth: Int = 4

    /// Use spaces for tabs
    public var useSpacesForTabs: Bool = true

    /// Auto-close brackets
    public var autoCloseBrackets: Bool = true

    /// Auto-indent
    public var autoIndent: Bool = true

    // MARK: - Bracket Pairs

    private let bracketPairs: [(open: Character, close: Character)] = [
        ("(", ")"),
        ("[", "]"),
        ("{", "}"),
        ("\"", "\""),
        ("'", "'"),
        ("`", "`")
    ]

    // MARK: - Drawing

    public override func draw(_ dirtyRect: NSRect) {
        // Draw current line highlight
        if highlightCurrentLine, let color = currentLineHighlightColor {
            drawCurrentLineHighlight(color: color)
        }

        super.draw(dirtyRect)
    }

    private func drawCurrentLineHighlight(color: NSColor) {
        guard let layoutManager = layoutManager else { return }

        let selectedRange = selectedRange()
        let glyphRange = layoutManager.glyphRange(forCharacterRange: selectedRange, actualCharacterRange: nil)

        var lineRect = layoutManager.lineFragmentRect(forGlyphAt: glyphRange.location, effectiveRange: nil)
        lineRect.origin.x = 0
        lineRect.size.width = bounds.width

        color.setFill()
        lineRect.fill()
    }

    // MARK: - Key Handling

    public override func keyDown(with event: NSEvent) {
        let characters = event.characters ?? ""

        // Handle tab key
        if event.keyCode == 48 { // Tab key
            handleTab(event: event)
            return
        }

        // Handle Enter/Return for auto-indent
        if event.keyCode == 36 { // Return key
            if autoIndent {
                handleReturn()
                return
            }
        }

        // Handle bracket auto-close
        if autoCloseBrackets, let char = characters.first {
            if handleBracketAutoClose(char: char) {
                return
            }
        }

        super.keyDown(with: event)
    }

    private func handleTab(event: NSEvent) {
        let isShiftPressed = event.modifierFlags.contains(.shift)

        if isShiftPressed {
            // Outdent
            outdentSelectedLines()
        } else {
            // Insert tab or spaces
            if useSpacesForTabs {
                let spaces = String(repeating: " ", count: tabWidth)
                insertText(spaces, replacementRange: selectedRange())
            } else {
                insertText("\t", replacementRange: selectedRange())
            }
        }
    }

    private func handleReturn() {
        guard let textStorage = textStorage else {
            insertNewline(nil)
            return
        }

        let currentPosition = selectedRange().location
        let text = textStorage.string as NSString

        // Find the start of the current line
        let lineRange = text.lineRange(for: NSRange(location: currentPosition, length: 0))
        let lineStart = lineRange.location
        let lineEnd = min(currentPosition, lineStart + lineRange.length)

        // Extract the current line up to cursor
        let currentLine = text.substring(with: NSRange(location: lineStart, length: lineEnd - lineStart))

        // Calculate indentation
        var indentation = ""
        for char in currentLine {
            if char == " " || char == "\t" {
                indentation.append(char)
            } else {
                break
            }
        }

        // Check if we should add extra indentation (after { [ ( )
        let trimmedLine = currentLine.trimmingCharacters(in: .whitespaces)
        if let lastChar = trimmedLine.last, ["{", "[", "(", ":"].contains(lastChar) {
            if useSpacesForTabs {
                indentation += String(repeating: " ", count: tabWidth)
            } else {
                indentation += "\t"
            }
        }

        // Insert newline with indentation
        insertText("\n" + indentation, replacementRange: selectedRange())
    }

    private func handleBracketAutoClose(char: Character) -> Bool {
        // Check if it's an opening bracket
        for pair in bracketPairs where pair.open == char {
            // Don't auto-close if we're closing an existing pair
            let selectedRange = self.selectedRange()
            if let textStorage = textStorage,
               selectedRange.location < textStorage.length {
                let nextChar = (textStorage.string as NSString).character(at: selectedRange.location)
                if Character(UnicodeScalar(nextChar)!) == pair.close {
                    // Just move cursor past the closing bracket
                    if pair.open == pair.close {
                        setSelectedRange(NSRange(location: selectedRange.location + 1, length: 0))
                        return true
                    }
                }
            }

            // For quotes, check if we're at the start of a word
            if pair.open == pair.close {
                // It's a quote - check context
                let selectedRange = self.selectedRange()
                if selectedRange.location > 0,
                   let textStorage = textStorage {
                    let prevChar = (textStorage.string as NSString).character(at: selectedRange.location - 1)
                    let prevCharacter = Character(UnicodeScalar(prevChar)!)
                    // Don't auto-close if previous character is alphanumeric (likely closing a string)
                    if prevCharacter.isLetter || prevCharacter.isNumber {
                        return false
                    }
                }
            }

            // Insert the pair
            let insertString = String(pair.open) + String(pair.close)
            let currentRange = self.selectedRange()
            insertText(insertString, replacementRange: currentRange)

            // Move cursor between the brackets
            let newLocation = self.selectedRange().location - 1
            setSelectedRange(NSRange(location: newLocation, length: 0))
            return true
        }

        // Check if it's a closing bracket - skip over it if matching
        for pair in bracketPairs where pair.close == char && pair.open != pair.close {
            let selectedRange = self.selectedRange()
            if let textStorage = textStorage,
               selectedRange.location < textStorage.length {
                let nextChar = (textStorage.string as NSString).character(at: selectedRange.location)
                if Character(UnicodeScalar(nextChar)!) == pair.close {
                    // Move cursor past the closing bracket
                    setSelectedRange(NSRange(location: selectedRange.location + 1, length: 0))
                    return true
                }
            }
        }

        return false
    }

    private func outdentSelectedLines() {
        guard let textStorage = textStorage else { return }

        let selectedRange = self.selectedRange()
        let text = textStorage.string as NSString

        // Find line range
        let lineRange = text.lineRange(for: selectedRange)
        var newText = ""
        var removedChars = 0
        var firstLineRemoved = 0

        text.enumerateSubstrings(in: lineRange, options: .byLines) { substring, substringRange, _, _ in
            guard var line = substring else { return }

            var charsToRemove = 0
            if line.hasPrefix("\t") {
                charsToRemove = 1
            } else {
                // Remove up to tabWidth spaces
                for (i, char) in line.enumerated() {
                    if char == " " && i < self.tabWidth {
                        charsToRemove = i + 1
                    } else {
                        break
                    }
                }
            }

            if charsToRemove > 0 {
                line = String(line.dropFirst(charsToRemove))
                removedChars += charsToRemove

                if substringRange.location == lineRange.location {
                    firstLineRemoved = charsToRemove
                }
            }

            if !newText.isEmpty {
                newText += "\n"
            }
            newText += line
        }

        // Replace the text
        if shouldChangeText(in: lineRange, replacementString: newText) {
            textStorage.replaceCharacters(in: lineRange, with: newText)
            didChangeText()

            // Adjust selection
            let newStart = max(lineRange.location, selectedRange.location - firstLineRemoved)
            let newLength = max(0, selectedRange.length - removedChars + firstLineRemoved)
            setSelectedRange(NSRange(location: newStart, length: newLength))
        }
    }

    // MARK: - First Responder

    public override var acceptsFirstResponder: Bool { true }

    public override func becomeFirstResponder() -> Bool {
        let result = super.becomeFirstResponder()
        needsDisplay = true
        return result
    }

    public override func resignFirstResponder() -> Bool {
        let result = super.resignFirstResponder()
        needsDisplay = true
        return result
    }

    // MARK: - Scrolling

    public override func scrollRangeToVisible(_ range: NSRange) {
        super.scrollRangeToVisible(range)

        // Also scroll the gutter if needed
        if let scrollView = enclosingScrollView {
            scrollView.reflectScrolledClipView(scrollView.contentView)
        }
    }
}
