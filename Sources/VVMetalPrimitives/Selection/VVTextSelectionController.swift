import Foundation
import CoreGraphics

public struct VVInputModifiers: OptionSet, Sendable {
    public let rawValue: Int

    public static let shift = VVInputModifiers(rawValue: 1 << 0)
    public static let control = VVInputModifiers(rawValue: 1 << 1)
    public static let option = VVInputModifiers(rawValue: 1 << 2)
    public static let command = VVInputModifiers(rawValue: 1 << 3)

    public init(rawValue: Int) {
        self.rawValue = rawValue
    }
}

/// Reusable mouse event handler for text selection.
public final class VVTextSelectionController<Position>: @unchecked Sendable where Position: VVTextPosition & Comparable {
    public var selection: VVTextSelection<Position>?
    public var selectionAnchor: Position?
    public var selectionMode: SelectionMode = .character
    public var isSelecting: Bool = false

    public enum SelectionMode: Sendable {
        case character
        case word
        case line
    }

    public init() {}

    public func handleMouseDown<T: VVTextHitTestable>(
        at point: CGPoint,
        clickCount: Int,
        modifiers: VVInputModifiers,
        hitTester: T
    ) where T.Position == Position {
        guard let position = hitTester.hitTest(at: point) else { return }
        _ = modifiers

        switch clickCount {
        case 1:
            // Single click: start character selection
            selectionMode = .character
            selectionAnchor = position
            selection = VVTextSelection(anchor: position, active: position)
            isSelecting = true

        case 2:
            // Double click: select word (if word range provider available)
            selectionMode = .word
            // For now, just select character - subclasses can override
            selectionAnchor = position
            selection = VVTextSelection(anchor: position, active: position)
            isSelecting = false

        case 3:
            // Triple click: select line (if line range provider available)
            selectionMode = .line
            // For now, just select character - subclasses can override
            selectionAnchor = position
            selection = VVTextSelection(anchor: position, active: position)
            isSelecting = false

        default:
            break
        }
    }

    @discardableResult
    public func handleMouseDragged<T: VVTextHitTestable>(
        to point: CGPoint,
        hitTester: T
    ) -> Bool where T.Position == Position {
        guard isSelecting, let anchor = selectionAnchor else { return false }
        guard let newPosition = hitTester.nearestTextPosition(to: point) else { return false }

        if selection?.active == newPosition {
            return false
        }

        selection = VVTextSelection(anchor: anchor, active: newPosition)
        return true
    }

    public func handleMouseUp() {
        isSelecting = false
    }

    public func selectAll(from start: Position, to end: Position) {
        selection = VVTextSelection(anchor: start, active: end)
        selectionAnchor = start
    }

    public func clearSelection() {
        selection = nil
        selectionAnchor = nil
    }
}
