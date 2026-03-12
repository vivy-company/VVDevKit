import CoreGraphics
import Foundation
import VVMarkdown
import VVMetalPrimitives

/// Position within the chat timeline: item index + block/run/character within that item's markdown layout.
public struct ChatTextPosition: Sendable, Hashable, Comparable, VVMetalPrimitives.VVTextPosition {
    public let itemIndex: Int
    public let blockIndex: Int
    public let runIndex: Int
    public let characterOffset: Int

    public static func < (lhs: Self, rhs: Self) -> Bool {
        if lhs.itemIndex != rhs.itemIndex { return lhs.itemIndex < rhs.itemIndex }
        if lhs.blockIndex != rhs.blockIndex { return lhs.blockIndex < rhs.blockIndex }
        if lhs.runIndex != rhs.runIndex { return lhs.runIndex < rhs.runIndex }
        return lhs.characterOffset < rhs.characterOffset
    }

    var markdownPosition: MarkdownTextPosition {
        MarkdownTextPosition(
            blockIndex: blockIndex,
            runIndex: runIndex,
            characterOffset: characterOffset
        )
    }
}
