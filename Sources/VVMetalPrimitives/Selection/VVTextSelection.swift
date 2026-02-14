import Foundation
import CoreGraphics
import simd

/// A position within a text document for selection purposes.
/// Conforming types must also implement Comparable separately.
public protocol VVTextPosition: Sendable, Hashable {}

/// A selection range with anchor and active positions.
public struct VVTextSelection<Position>: Sendable where Position: VVTextPosition & Comparable {
    public var anchor: Position
    public var active: Position

    public init(anchor: Position, active: Position) {
        self.anchor = anchor
        self.active = active
    }

    public var isEmpty: Bool { anchor == active }

    public var ordered: (start: Position, end: Position) {
        anchor < active ? (anchor, active) : (active, anchor)
    }
}

/// Hit test result mapping a point to a text position.
public protocol VVTextHitTestable: AnyObject {
    associatedtype Position: VVTextPosition
    func hitTest(at point: CGPoint) -> Position?
}

/// Provides selection quads for rendering.
public protocol VVTextSelectionRenderer: AnyObject {
    associatedtype Position: VVTextPosition
    func selectionQuads(from start: Position, to end: Position, color: SIMD4<Float>) -> [VVQuadPrimitive]
}

/// Extracts plain text from a selection range.
public protocol VVTextExtractor: AnyObject {
    associatedtype Position: VVTextPosition
    func extractText(from start: Position, to end: Position) -> String
}
