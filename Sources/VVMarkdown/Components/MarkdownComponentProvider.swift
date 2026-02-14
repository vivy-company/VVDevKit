import Foundation
import VVMetalPrimitives

public struct MarkdownComponentContext {
    public let theme: MarkdownTheme
    public let layoutEngine: MarkdownLayoutEngine
    public let contentWidth: CGFloat

    public init(theme: MarkdownTheme, layoutEngine: MarkdownLayoutEngine, contentWidth: CGFloat) {
        self.theme = theme
        self.layoutEngine = layoutEngine
        self.contentWidth = contentWidth
    }
}

public typealias MarkdownViewProvider = (_ block: LayoutBlock, _ context: MarkdownComponentContext, _ defaultView: (LayoutBlock) -> any VVView) -> any VVView

public struct MarkdownBlockStyle: Sendable {
    public var padding: VVInsets
    public var cornerRadius: CGFloat?
    public var backgroundColor: SIMD4<Float>?
    public var borderColor: SIMD4<Float>?
    public var borderWidth: CGFloat?

    public init(
        padding: VVInsets = .init(),
        cornerRadius: CGFloat? = nil,
        backgroundColor: SIMD4<Float>? = nil,
        borderColor: SIMD4<Float>? = nil,
        borderWidth: CGFloat? = nil
    ) {
        self.padding = padding
        self.cornerRadius = cornerRadius
        self.backgroundColor = backgroundColor
        self.borderColor = borderColor
        self.borderWidth = borderWidth
    }
}

public struct MarkdownStyleRegistry: Sendable {
    public var paragraph: MarkdownBlockStyle
    public var heading: [Int: MarkdownBlockStyle]
    public var codeBlock: MarkdownBlockStyle
    public var list: MarkdownBlockStyle
    public var blockQuote: MarkdownBlockStyle
    public var table: MarkdownBlockStyle
    public var image: MarkdownBlockStyle
    public var math: MarkdownBlockStyle
    public var mermaid: MarkdownBlockStyle

    public init(
        paragraph: MarkdownBlockStyle = .init(),
        heading: [Int: MarkdownBlockStyle] = [:],
        codeBlock: MarkdownBlockStyle = .init(),
        list: MarkdownBlockStyle = .init(),
        blockQuote: MarkdownBlockStyle = .init(),
        table: MarkdownBlockStyle = .init(),
        image: MarkdownBlockStyle = .init(),
        math: MarkdownBlockStyle = .init(),
        mermaid: MarkdownBlockStyle = .init()
    ) {
        self.paragraph = paragraph
        self.heading = heading
        self.codeBlock = codeBlock
        self.list = list
        self.blockQuote = blockQuote
        self.table = table
        self.image = image
        self.math = math
        self.mermaid = mermaid
    }

    public func style(for blockType: LayoutBlockType) -> MarkdownBlockStyle {
        switch blockType {
        case .paragraph:
            return paragraph
        case .heading(let level):
            return heading[level] ?? paragraph
        case .codeBlock:
            return codeBlock
        case .list:
            return list
        case .blockQuote, .alert:
            return blockQuote
        case .table:
            return table
        case .image:
            return image
        case .mathBlock:
            return math
        case .mermaid:
            return mermaid
        case .definitionList, .abbreviationList:
            return list
        case .thematicBreak:
            return paragraph
        }
    }
}
