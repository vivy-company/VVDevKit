import AppKit

/// Hidden NSTextView that handles keyboard input, IME, and clipboard for the Metal text view
public final class HiddenInputView: NSTextView {
    public enum SearchScope {
        case currentFile
        case openDocuments
    }

    // MARK: - Properties

    public weak var metalTextView: MetalTextView?
    public weak var inputDelegate: HiddenInputViewDelegate?
    public var textProvider: (() -> String)?
    public var selectedRangeProvider: (() -> NSRange)?
    public var markedRangeProvider: (() -> NSRange?)?

    // MARK: - Initialization

    public init() {
        super.init(frame: NSRect(x: -1000, y: -1000, width: 1, height: 1))
        commonInit()
    }

    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        commonInit()
    }

    override init(frame frameRect: NSRect, textContainer container: NSTextContainer?) {
        super.init(frame: frameRect, textContainer: container)
        commonInit()
    }

    required init?(coder: NSCoder) {
        super.init(coder: coder)
        commonInit()
    }

    private func commonInit() {
        // Make invisible but functional
        alphaValue = 0.01
        isEditable = true
        isSelectable = true
        isRichText = false
        allowsUndo = true
        usesFontPanel = false
        usesRuler = false
        importsGraphics = false

        // Disable drawing
        drawsBackground = false
    }

    // MARK: - First Responder

    override public var acceptsFirstResponder: Bool { true }

    override public func becomeFirstResponder() -> Bool {
        let result = super.becomeFirstResponder()
        inputDelegate?.hiddenInputViewDidBecomeFirstResponder(self)
        return result
    }

    override public func resignFirstResponder() -> Bool {
        let result = super.resignFirstResponder()
        inputDelegate?.hiddenInputViewDidResignFirstResponder(self)
        return result
    }

    // MARK: - Text Input

    override public func insertText(_ insertString: Any, replacementRange: NSRange) {
        let text: String
        if let str = insertString as? String {
            text = str
        } else if let attrStr = insertString as? NSAttributedString {
            text = attrStr.string
        } else {
            return
        }

        inputDelegate?.hiddenInputView(self, didInsertText: text, replacementRange: replacementRange)
    }

    override public func insertNewline(_ sender: Any?) {
        inputDelegate?.hiddenInputView(self, didInsertText: "\n", replacementRange: selectedRange())
    }

    override public func insertTab(_ sender: Any?) {
        inputDelegate?.hiddenInputView(self, didInsertText: "\t", replacementRange: selectedRange())
    }

    override public func insertBacktab(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidInsertBacktab(self)
    }

    override public func deleteBackward(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidDeleteBackward(self)
    }

    override public func deleteForward(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidDeleteForward(self)
    }

    override public func deleteWordBackward(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidDeleteWordBackward(self)
    }

    override public func deleteWordForward(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidDeleteWordForward(self)
    }

    override public func deleteToBeginningOfLine(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidDeleteToBeginningOfLine(self)
    }

    override public func deleteToEndOfLine(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidDeleteToEndOfLine(self)
    }

    // MARK: - IME / Marked Text

    override public func setMarkedText(_ string: Any, selectedRange: NSRange, replacementRange: NSRange) {
        let text: String
        if let str = string as? String {
            text = str
        } else if let attrStr = string as? NSAttributedString {
            text = attrStr.string
        } else {
            return
        }

        inputDelegate?.hiddenInputView(self, didSetMarkedText: text, selectedRange: selectedRange, replacementRange: replacementRange)
    }

    override public func unmarkText() {
        inputDelegate?.hiddenInputViewDidUnmarkText(self)
    }

    override public func hasMarkedText() -> Bool {
        if let range = markedRangeProvider?() {
            return range.length > 0 && range.location != NSNotFound
        }
        return super.hasMarkedText()
    }

    override public func markedRange() -> NSRange {
        if let range = markedRangeProvider?() {
            return clampRange(range)
        }
        return super.markedRange()
    }

    override public var selectedRange: NSRange {
        get {
            if let range = selectedRangeProvider?() {
                return clampRange(range)
            }
            return super.selectedRange
        }
        set {
            super.selectedRange = newValue
        }
    }

    override public func attributedSubstring(forProposedRange range: NSRange, actualRange: NSRangePointer?) -> NSAttributedString? {
        let text = textProvider?() ?? super.string
        let clamped = clampRange(range, maxLength: (text as NSString).length)
        actualRange?.pointee = clamped
        if clamped.location == NSNotFound || clamped.length == 0 {
            return nil
        }
        let substring = (text as NSString).substring(with: clamped)
        return NSAttributedString(string: substring)
    }

    override public func validAttributesForMarkedText() -> [NSAttributedString.Key] {
        return []
    }

    private func clampRange(_ range: NSRange, maxLength: Int? = nil) -> NSRange {
        let length = maxLength ?? (textProvider?() as NSString?)?.length ?? super.string.count
        if range.location == NSNotFound {
            return NSRange(location: NSNotFound, length: 0)
        }
        let safeLocation = max(0, min(range.location, length))
        let maxLen = max(0, length - safeLocation)
        let safeLength = max(0, min(range.length, maxLen))
        return NSRange(location: safeLocation, length: safeLength)
    }

    override public func firstRect(forCharacterRange range: NSRange, actualRange: NSRangePointer?) -> NSRect {
        if let rect = metalTextView?.insertionRect() {
            let rectInWindow = metalTextView?.convert(rect, to: nil) ?? rect
            let rectOnScreen = metalTextView?.window?.convertToScreen(rectInWindow) ?? rectInWindow
            return rectOnScreen
        }
        return super.firstRect(forCharacterRange: range, actualRange: actualRange)
    }

    override public func characterIndexForInsertion(at point: NSPoint) -> Int {
        if let offset = metalTextView?.insertionOffset() {
            return offset
        }
        return super.characterIndexForInsertion(at: point)
    }

    // MARK: - Movement

    override public func moveUp(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveUp(self)
    }

    override public func moveDown(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveDown(self)
    }

    override public func moveLeft(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveLeft(self)
    }

    override public func moveRight(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveRight(self)
    }

    override public func moveWordLeft(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveWordLeft(self)
    }

    override public func moveWordRight(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveWordRight(self)
    }

    override public func moveToBeginningOfLine(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveToBeginningOfLine(self)
    }

    override public func moveToEndOfLine(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveToEndOfLine(self)
    }

    override public func moveToBeginningOfDocument(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveToBeginningOfDocument(self)
    }

    override public func moveToEndOfDocument(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveToEndOfDocument(self)
    }

    override public func pageUp(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidPageUp(self)
    }

    override public func pageDown(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidPageDown(self)
    }

    // MARK: - Selection Movement

    override public func moveUpAndModifySelection(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveUpAndModifySelection(self)
    }

    override public func moveDownAndModifySelection(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveDownAndModifySelection(self)
    }

    override public func moveLeftAndModifySelection(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveLeftAndModifySelection(self)
    }

    override public func moveRightAndModifySelection(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveRightAndModifySelection(self)
    }

    override public func moveWordLeftAndModifySelection(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveWordLeftAndModifySelection(self)
    }

    override public func moveWordRightAndModifySelection(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveWordRightAndModifySelection(self)
    }

    override public func moveToBeginningOfLineAndModifySelection(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveToBeginningOfLineAndModifySelection(self)
    }

    override public func moveToEndOfLineAndModifySelection(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidMoveToEndOfLineAndModifySelection(self)
    }

    override public func selectAll(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidSelectAll(self)
    }

    // MARK: - Clipboard

    override public func copy(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidCopy(self)
    }

    override public func cut(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidCut(self)
    }

    override public func paste(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidPaste(self)
    }

    override public func validateUserInterfaceItem(_ item: NSValidatedUserInterfaceItem) -> Bool {
        switch item.action {
        case #selector(copy(_:)),
             #selector(cut(_:)),
             #selector(paste(_:)),
             #selector(selectAll(_:)):
            return true
        default:
            return super.validateUserInterfaceItem(item)
        }
    }

    // MARK: - Undo/Redo

    @objc public func performUndo(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidUndo(self)
    }

    @objc public func performRedo(_ sender: Any?) {
        inputDelegate?.hiddenInputViewDidRedo(self)
    }

    // MARK: - Key Events

    override public func keyDown(with event: NSEvent) {
        // Check for custom key bindings
        if inputDelegate?.hiddenInputView(self, shouldHandleKeyDown: event) == true {
            return
        }

        // Default handling
        interpretKeyEvents([event])
    }

    override public func performKeyEquivalent(with event: NSEvent) -> Bool {
        if event.modifierFlags.contains(.command),
           let chars = event.charactersIgnoringModifiers?.lowercased(),
           let ch = chars.first {
            switch ch {
            case "f":
                let scope: SearchScope = event.modifierFlags.contains(.shift) ? .openDocuments : .currentFile
                inputDelegate?.hiddenInputViewDidRequestSearch(self, forward: true, scope: scope)
                return true
            case "g":
                let forward = !event.modifierFlags.contains(.shift)
                inputDelegate?.hiddenInputViewDidRequestRepeatSearch(self, forward: forward)
                return true
            default:
                break
            }
        }

        return super.performKeyEquivalent(with: event)
    }

    // MARK: - Mouse Events (forward to Metal view)

    override public func mouseDown(with event: NSEvent) {
        metalTextView?.mouseDown(with: event)
    }

    override public func mouseDragged(with event: NSEvent) {
        metalTextView?.mouseDragged(with: event)
    }

    override public func mouseUp(with event: NSEvent) {
        metalTextView?.mouseUp(with: event)
    }

    override public func scrollWheel(with event: NSEvent) {
        metalTextView?.scrollWheel(with: event)
    }
}

// MARK: - Delegate Protocol

public protocol HiddenInputViewDelegate: AnyObject {
    // First responder
    func hiddenInputViewDidBecomeFirstResponder(_ view: HiddenInputView)
    func hiddenInputViewDidResignFirstResponder(_ view: HiddenInputView)

    // Text input
    func hiddenInputView(_ view: HiddenInputView, didInsertText text: String, replacementRange: NSRange)

    // Delete
    func hiddenInputViewDidDeleteBackward(_ view: HiddenInputView)
    func hiddenInputViewDidDeleteForward(_ view: HiddenInputView)
    func hiddenInputViewDidDeleteWordBackward(_ view: HiddenInputView)
    func hiddenInputViewDidDeleteWordForward(_ view: HiddenInputView)
    func hiddenInputViewDidDeleteToBeginningOfLine(_ view: HiddenInputView)
    func hiddenInputViewDidDeleteToEndOfLine(_ view: HiddenInputView)
    func hiddenInputViewDidInsertBacktab(_ view: HiddenInputView)

    // IME
    func hiddenInputView(_ view: HiddenInputView, didSetMarkedText text: String, selectedRange: NSRange, replacementRange: NSRange)
    func hiddenInputViewDidUnmarkText(_ view: HiddenInputView)

    // Movement
    func hiddenInputViewDidMoveUp(_ view: HiddenInputView)
    func hiddenInputViewDidMoveDown(_ view: HiddenInputView)
    func hiddenInputViewDidMoveLeft(_ view: HiddenInputView)
    func hiddenInputViewDidMoveRight(_ view: HiddenInputView)
    func hiddenInputViewDidMoveWordLeft(_ view: HiddenInputView)
    func hiddenInputViewDidMoveWordRight(_ view: HiddenInputView)
    func hiddenInputViewDidMoveToBeginningOfLine(_ view: HiddenInputView)
    func hiddenInputViewDidMoveToEndOfLine(_ view: HiddenInputView)
    func hiddenInputViewDidMoveToBeginningOfDocument(_ view: HiddenInputView)
    func hiddenInputViewDidMoveToEndOfDocument(_ view: HiddenInputView)
    func hiddenInputViewDidPageUp(_ view: HiddenInputView)
    func hiddenInputViewDidPageDown(_ view: HiddenInputView)

    // Selection movement
    func hiddenInputViewDidMoveUpAndModifySelection(_ view: HiddenInputView)
    func hiddenInputViewDidMoveDownAndModifySelection(_ view: HiddenInputView)
    func hiddenInputViewDidMoveLeftAndModifySelection(_ view: HiddenInputView)
    func hiddenInputViewDidMoveRightAndModifySelection(_ view: HiddenInputView)
    func hiddenInputViewDidMoveWordLeftAndModifySelection(_ view: HiddenInputView)
    func hiddenInputViewDidMoveWordRightAndModifySelection(_ view: HiddenInputView)
    func hiddenInputViewDidMoveToBeginningOfLineAndModifySelection(_ view: HiddenInputView)
    func hiddenInputViewDidMoveToEndOfLineAndModifySelection(_ view: HiddenInputView)
    func hiddenInputViewDidSelectAll(_ view: HiddenInputView)

    // Clipboard
    func hiddenInputViewDidCopy(_ view: HiddenInputView)
    func hiddenInputViewDidCut(_ view: HiddenInputView)
    func hiddenInputViewDidPaste(_ view: HiddenInputView)

    // Undo/Redo
    func hiddenInputViewDidUndo(_ view: HiddenInputView)
    func hiddenInputViewDidRedo(_ view: HiddenInputView)

    // Key handling
    func hiddenInputView(_ view: HiddenInputView, shouldHandleKeyDown event: NSEvent) -> Bool

    // Search
    func hiddenInputViewDidRequestSearch(_ view: HiddenInputView, forward: Bool, scope: HiddenInputView.SearchScope)
    func hiddenInputViewDidRequestRepeatSearch(_ view: HiddenInputView, forward: Bool)
}

// MARK: - Default Implementations

public extension HiddenInputViewDelegate {
    func hiddenInputViewDidBecomeFirstResponder(_ view: HiddenInputView) {}
    func hiddenInputViewDidResignFirstResponder(_ view: HiddenInputView) {}
    func hiddenInputViewDidDeleteWordBackward(_ view: HiddenInputView) {}
    func hiddenInputViewDidDeleteWordForward(_ view: HiddenInputView) {}
    func hiddenInputViewDidDeleteToBeginningOfLine(_ view: HiddenInputView) {}
    func hiddenInputViewDidDeleteToEndOfLine(_ view: HiddenInputView) {}
    func hiddenInputViewDidInsertBacktab(_ view: HiddenInputView) {}
    func hiddenInputView(_ view: HiddenInputView, didSetMarkedText text: String, selectedRange: NSRange, replacementRange: NSRange) {}
    func hiddenInputViewDidUnmarkText(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveWordLeft(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveWordRight(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveToBeginningOfDocument(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveToEndOfDocument(_ view: HiddenInputView) {}
    func hiddenInputViewDidPageUp(_ view: HiddenInputView) {}
    func hiddenInputViewDidPageDown(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveUpAndModifySelection(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveDownAndModifySelection(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveLeftAndModifySelection(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveRightAndModifySelection(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveWordLeftAndModifySelection(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveWordRightAndModifySelection(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveToBeginningOfLineAndModifySelection(_ view: HiddenInputView) {}
    func hiddenInputViewDidMoveToEndOfLineAndModifySelection(_ view: HiddenInputView) {}
    func hiddenInputViewDidUndo(_ view: HiddenInputView) {}
    func hiddenInputViewDidRedo(_ view: HiddenInputView) {}
    func hiddenInputView(_ view: HiddenInputView, shouldHandleKeyDown event: NSEvent) -> Bool { false }
    func hiddenInputViewDidRequestSearch(_ view: HiddenInputView, forward: Bool, scope: HiddenInputView.SearchScope) {}
    func hiddenInputViewDidRequestRepeatSearch(_ view: HiddenInputView, forward: Bool) {}
}
