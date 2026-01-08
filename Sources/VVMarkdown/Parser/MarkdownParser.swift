//  MarkdownParser.swift
//  VVMarkdown
//
//  Production-ready markdown parser using swift-markdown AST

import Foundation
import Markdown

// MARK: - Markdown Parser

/// Production-ready markdown parser
public final class MarkdownParser: @unchecked Sendable {

    public struct Options: Sendable {
        public var parseSymbolLinks: Bool = true
        public var parseBlockDirectives: Bool = false

        public static let `default` = Options()

        public init(parseSymbolLinks: Bool = true, parseBlockDirectives: Bool = false) {
            self.parseSymbolLinks = parseSymbolLinks
            self.parseBlockDirectives = parseBlockDirectives
        }
    }

    private let options: Options

    public init(options: Options = .default) {
        self.options = options
    }

    private let emojiShortcodes: [String: String] = [
        "rocket": "🚀",
        "fire": "🔥",
        "thumbsup": "👍",
        "+1": "👍",
        "heart": "❤️",
        "star": "⭐",
        "sparkles": "✨",
        "tada": "🎉",
        "warning": "⚠️",
        "check": "✅",
        "x": "❌"
    ]

    /// Parse complete markdown content
    public func parse(_ content: String) -> ParsedMarkdownDocument {
        guard !content.isEmpty else { return .empty }

        var parserOptions: ParseOptions = []
        if options.parseSymbolLinks { parserOptions.insert(.parseSymbolLinks) }
        if options.parseBlockDirectives { parserOptions.insert(.parseBlockDirectives) }

        var blocks: [MarkdownBlock] = []
        var footnotes: [String: MarkdownBlock] = [:]
        var index = 0

        // Extract $$...$$ math blocks first, then parse markdown segments
        let segments = extractMathBlocks(from: content)

        for segment in segments {
            if segment.isMath {
                blocks.append(MarkdownBlock(.mathBlock(segment.content), index: index))
                index += 1
            } else {
                let document = Document(parsing: segment.content, options: parserOptions)
                for child in document.children {
                    if let block = parseBlockElement(child, index: &index) {
                        if case .footnoteDefinition(let id, _) = block.type {
                            footnotes[id] = block
                        } else {
                            blocks.append(block)
                        }
                    }
                }
            }
        }

        return ParsedMarkdownDocument(
            blocks: blocks,
            footnotes: footnotes,
            isComplete: true,
            streamingBuffer: ""
        )
    }

    /// Extract $$...$$ block math from content, skipping fenced code blocks
    private func extractMathBlocks(from content: String) -> [(content: String, isMath: Bool)] {
        var segments: [(content: String, isMath: Bool)] = []
        var current = ""
        var inCodeFence = false

        func flushCurrentIfNeeded() {
            if !current.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty {
                segments.append((current, false))
            }
            current = ""
        }

        func isFenceStart(at index: String.Index) -> Bool {
            guard content[index...].hasPrefix("```") else { return false }
            let lineStart = content[..<index].lastIndex(of: "\n").map { content.index(after: $0) } ?? content.startIndex
            let prefix = content[lineStart..<index]
            return prefix.allSatisfy { $0 == " " || $0 == "\t" }
        }

        var i = content.startIndex
        while i < content.endIndex {
            if isFenceStart(at: i) {
                inCodeFence.toggle()
                current.append(contentsOf: "```")
                i = content.index(i, offsetBy: 3)
                continue
            }

            if !inCodeFence && content[i...].hasPrefix("$$") {
                flushCurrentIfNeeded()

                let afterStart = content.index(i, offsetBy: 2)
                if let endRange = content[afterStart...].range(of: "$$") {
                    let mathContent = String(content[afterStart..<endRange.lowerBound])
                        .trimmingCharacters(in: .whitespacesAndNewlines)
                    if !mathContent.isEmpty {
                        segments.append((mathContent, true))
                    }
                    i = endRange.upperBound
                    continue
                } else {
                    current.append(contentsOf: content[i...])
                    break
                }
            }

            current.append(content[i])
            i = content.index(after: i)
        }

        flushCurrentIfNeeded()

        return segments.isEmpty ? [(content, false)] : segments
    }

    /// Parse markdown content with streaming support
    public func parseStreaming(_ content: String, isComplete: Bool) -> ParsedMarkdownDocument {
        if isComplete {
            return parse(content)
        }

        let (stableContent, buffer) = findStableBoundary(in: content)

        if stableContent.isEmpty {
            return ParsedMarkdownDocument(
                blocks: [],
                footnotes: [:],
                isComplete: false,
                streamingBuffer: content
            )
        }

        let result = parse(stableContent)
        return ParsedMarkdownDocument(
            blocks: result.blocks,
            footnotes: result.footnotes,
            isComplete: false,
            streamingBuffer: buffer
        )
    }

    // MARK: - Block Parsing

    private func parseBlockElement(_ element: Markup, index: inout Int) -> MarkdownBlock? {
        defer { index += 1 }

        switch element {
        case let paragraph as Paragraph:
            return parseParagraph(paragraph, index: index)

        case let heading as Heading:
            let content = parseInlineContent(heading.children)
            return MarkdownBlock(.heading(content, level: heading.level), index: index)

        case let codeBlock as CodeBlock:
            return parseCodeBlock(codeBlock, index: index)

        case let list as UnorderedList:
            return parseList(list, ordered: false, startIndex: 1, index: index)

        case let list as OrderedList:
            return parseList(list, ordered: true, startIndex: Int(list.startIndex), index: index)

        case let quote as BlockQuote:
            return parseBlockQuote(quote, index: index)

        case let table as Markdown.Table:
            return parseTable(table, index: index)

        case is ThematicBreak:
            return MarkdownBlock(.thematicBreak, index: index)

        case let html as HTMLBlock:
            return MarkdownBlock(.htmlBlock(html.rawHTML), index: index)

        default:
            return nil
        }
    }

    private func parseParagraph(_ paragraph: Paragraph, index: Int) -> MarkdownBlock? {
        // Check if this is a standalone image paragraph
        if paragraph.childCount == 1 {
            for child in paragraph.children {
                if let image = child as? Markdown.Image {
                    return MarkdownBlock(.image(url: image.source ?? "", alt: extractAltText(from: image)), index: index)
                }
                break
            }
        }

        let content = parseInlineContent(paragraph.children)
        guard !content.isEmpty else { return nil }

        if let (footnoteId, footnoteContent) = extractFootnoteDefinition(from: content) {
            let defContent = MarkdownInlineContent(elements: [.text(footnoteContent)])
            let defBlock = MarkdownBlock(.paragraph(defContent), index: 0)
            return MarkdownBlock(.footnoteDefinition(id: footnoteId, blocks: [defBlock]), index: index)
        }

        if let mathContent = extractStandaloneMath(from: content) {
            return MarkdownBlock(.mathBlock(mathContent), index: index)
        }

        if let definitionItems = extractDefinitionList(from: content) {
            return MarkdownBlock(.definitionList(items: definitionItems), index: index)
        }

        if let abbreviations = extractAbbreviationList(from: content) {
            return MarkdownBlock(.abbreviationList(items: abbreviations), index: index)
        }

        return MarkdownBlock(.paragraph(content), index: index)
    }

    private func extractFootnoteDefinition(from content: MarkdownInlineContent) -> (id: String, content: String)? {
        let plainText = content.plainText
        guard plainText.hasPrefix("[^") else { return nil }

        guard let closeBracket = plainText.firstIndex(of: "]") else { return nil }
        let afterBracket = plainText.index(after: closeBracket)
        guard afterBracket < plainText.endIndex, plainText[afterBracket] == ":" else { return nil }

        let idStart = plainText.index(plainText.startIndex, offsetBy: 2)
        let id = String(plainText[idStart..<closeBracket])
        guard !id.isEmpty else { return nil }

        var contentStart = plainText.index(after: afterBracket)
        if contentStart < plainText.endIndex && plainText[contentStart] == " " {
            contentStart = plainText.index(after: contentStart)
        }
        let footnoteContent = String(plainText[contentStart...]).trimmingCharacters(in: .whitespacesAndNewlines)

        return (id, footnoteContent)
    }

    private func extractStandaloneMath(from content: MarkdownInlineContent) -> String? {
        let plainText = content.plainText.trimmingCharacters(in: .whitespacesAndNewlines)

        if plainText.hasPrefix("$") && plainText.hasSuffix("$") && !plainText.hasPrefix("$$") {
            let inner = String(plainText.dropFirst().dropLast()).trimmingCharacters(in: .whitespaces)
            if !inner.isEmpty && looksLikeLaTeX(inner) {
                return inner
            }
        }

        if looksLikeLaTeXBlock(plainText) {
            return plainText
        }

        return nil
    }

    private func looksLikeLaTeX(_ text: String) -> Bool {
        let mathPatterns = ["\\frac", "\\sqrt", "\\sum", "\\int", "\\prod", "\\lim",
                           "\\begin{", "\\end{", "^{", "_{", "\\alpha", "\\beta",
                           "\\gamma", "\\delta", "\\theta", "\\pi", "\\infty",
                           "\\partial", "\\nabla", "\\times", "\\cdot", "\\pm"]
        return mathPatterns.contains { text.contains($0) }
    }

    private func looksLikeLaTeXBlock(_ text: String) -> Bool {
        let trimmed = text.trimmingCharacters(in: .whitespacesAndNewlines)
        guard trimmed.hasPrefix("\\") else { return false }

        let blockPatterns = ["\\frac{", "\\sqrt{", "\\sum_", "\\sum^", "\\int_", "\\int^",
                            "\\prod_", "\\lim_", "\\begin{", "\\left", "\\right",
                            "\\mathbf{", "\\mathrm{", "\\text{"]
        return blockPatterns.contains { trimmed.hasPrefix($0) || trimmed.contains($0) }
    }

    private func parseCodeBlock(_ codeBlock: CodeBlock, index: Int) -> MarkdownBlock {
        let language = codeBlock.language?.lowercased()
        let normalized = normalizeCodeBlock(codeBlock.code)

        if language == "math" || language == "latex" || language == "tex" {
            return MarkdownBlock(.mathBlock(normalized), index: index)
        }
        if language == "mermaid" || language == "mermaidjs" {
            return MarkdownBlock(.mermaid(normalized), index: index)
        }

        return MarkdownBlock(.codeBlock(code: normalized, language: codeBlock.language, isStreaming: false), index: index)
    }

    private func normalizeCodeBlock(_ code: String) -> String {
        var trimmed = code
        while trimmed.last == "\n" || trimmed.last == "\r" {
            trimmed.removeLast()
        }
        if trimmed.contains("\r") {
            trimmed = trimmed.replacingOccurrences(of: "\r", with: "")
        }
        return trimmed
    }

    private func parseList(_ list: ListItemContainer, ordered: Bool, startIndex: Int, index: Int) -> MarkdownBlock {
        var items: [MarkdownListItem] = []
        var itemIndex = 0

        for item in list.listItems {
            let parsedItem = parseListItem(
                item,
                depth: 0,
                index: itemIndex,
                listOrdered: ordered,
                listStartIndex: startIndex
            )
            items.append(parsedItem)
            itemIndex += 1
        }

        return MarkdownBlock(.list(items: items, ordered: ordered, startIndex: startIndex), index: index)
    }

    private func parseListItem(
        _ item: Markdown.ListItem,
        depth: Int,
        index: Int,
        listOrdered: Bool,
        listStartIndex: Int
    ) -> MarkdownListItem {
        var checkbox: MarkdownListItem.CheckboxState? = nil

        if let cb = item.checkbox {
            checkbox = cb == .checked ? .checked : .unchecked
        }

        var inlineChildren: [Markup] = []
        var nestedLists: [(ListItemContainer, Bool, Int)] = []

        for child in item.children {
            if let list = child as? UnorderedList {
                nestedLists.append((list, false, 1))
            } else if let list = child as? OrderedList {
                nestedLists.append((list, true, Int(list.startIndex)))
            } else if let paragraph = child as? Paragraph {
                for c in paragraph.children { inlineChildren.append(c) }
            } else {
                inlineChildren.append(child)
            }
        }

        var content = parseInlineContent(inlineChildren)

        if checkbox == nil, case .text(var text) = content.elements.first {
            if text.hasPrefix("[ ] ") {
                checkbox = .unchecked
                text = String(text.dropFirst(4))
                var newElements = content.elements
                newElements[0] = .text(text)
                content = MarkdownInlineContent(elements: newElements)
            } else if text.hasPrefix("[x] ") || text.hasPrefix("[X] ") {
                checkbox = .checked
                text = String(text.dropFirst(4))
                var newElements = content.elements
                newElements[0] = .text(text)
                content = MarkdownInlineContent(elements: newElements)
            }
        }

        var children: [MarkdownListItem] = []
        for (nestedList, nestedOrdered, nestedStartIndex) in nestedLists {
            var nestedIndex = 0
            for nestedItem in nestedList.listItems {
                children.append(
                    parseListItem(
                        nestedItem,
                        depth: depth + 1,
                        index: nestedIndex,
                        listOrdered: nestedOrdered,
                        listStartIndex: nestedStartIndex
                    )
                )
                nestedIndex += 1
            }
        }

        return MarkdownListItem(
            content: content,
            children: children,
            checkbox: checkbox,
            depth: depth,
            index: index,
            listOrdered: listOrdered,
            listStartIndex: listStartIndex
        )
    }

    private func parseBlockQuote(_ quote: BlockQuote, index: Int) -> MarkdownBlock {
        var blocks: [MarkdownBlock] = []
        var blockIndex = 0

        for child in quote.children {
            if let block = parseBlockElement(child, index: &blockIndex) {
                blocks.append(block)
            }
        }

        if let first = blocks.first,
           case .paragraph(let content) = first.type,
           let extracted = extractAlert(from: content) {
            var updatedBlocks = blocks
            if extracted.content.plainText.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty {
                updatedBlocks.removeFirst()
            } else {
                updatedBlocks[0] = MarkdownBlock(.paragraph(extracted.content), index: 0)
            }
            return MarkdownBlock(.alert(kind: extracted.kind, blocks: updatedBlocks), index: index)
        }

        return MarkdownBlock(.blockQuote(blocks: blocks), index: index)
    }

    private func extractAlert(from content: MarkdownInlineContent) -> (kind: MarkdownAlertKind, content: MarkdownInlineContent)? {
        guard let result = stripAlertMarker(from: content.plainText) else { return nil }
        let trimmedContent = dropLeadingCharacters(from: content, count: result.dropCount)
        return (result.kind, trimmedContent)
    }

    private func stripAlertMarker(from text: String) -> (kind: MarkdownAlertKind, dropCount: Int)? {
        var index = text.startIndex
        while index < text.endIndex, text[index].isWhitespace {
            index = text.index(after: index)
        }
        guard index < text.endIndex else { return nil }
        if text[index] == "[", text.index(after: index) < text.endIndex, text[text.index(after: index)] == "!" {
            guard let endIndex = text[index...].firstIndex(of: "]") else { return nil }
            let kindStart = text.index(index, offsetBy: 2)
            guard kindStart < endIndex else { return nil }
            let rawKind = text[kindStart..<endIndex].lowercased()
            guard let kind = MarkdownAlertKind(rawValue: rawKind) else { return nil }

            var remainderStart = text.index(after: endIndex)
            while remainderStart < text.endIndex, text[remainderStart].isWhitespace {
                remainderStart = text.index(after: remainderStart)
            }
            let dropCount = text.distance(from: text.startIndex, to: remainderStart)
            return (kind, dropCount)
        }

        if text[index] == "!" {
            let kindStart = text.index(after: index)
            var kindEnd = kindStart
            while kindEnd < text.endIndex, text[kindEnd].isLetter {
                kindEnd = text.index(after: kindEnd)
            }
            guard kindStart < kindEnd else { return nil }
            let rawKind = text[kindStart..<kindEnd].lowercased()
            guard let kind = MarkdownAlertKind(rawValue: rawKind) else { return nil }
            var remainderStart = kindEnd
            while remainderStart < text.endIndex, text[remainderStart].isWhitespace {
                remainderStart = text.index(after: remainderStart)
            }
            let dropCount = text.distance(from: text.startIndex, to: remainderStart)
            return (kind, dropCount)
        }

        return nil
    }

    private func dropLeadingCharacters(from content: MarkdownInlineContent, count: Int) -> MarkdownInlineContent {
        guard count > 0 else { return content }
        var remaining = count
        var newElements: [InlineElement] = []
        newElements.reserveCapacity(content.elements.count)

        for element in content.elements {
            if remaining <= 0 {
                newElements.append(element)
                continue
            }

            let (newElement, consumed) = dropLeadingCharacters(from: element, count: remaining)
            remaining -= consumed
            if let newElement {
                newElements.append(newElement)
            }
        }

        return MarkdownInlineContent(elements: newElements)
    }

    private func dropLeadingCharacters(from element: InlineElement, count: Int) -> (InlineElement?, Int) {
        guard count > 0 else { return (element, 0) }

        switch element {
        case .text(let text):
            let length = text.count
            if count >= length {
                return (nil, length)
            }
            return (.text(String(text.dropFirst(count))), count)

        case .code(let text):
            let length = text.count
            if count >= length {
                return (nil, length)
            }
            return (.code(String(text.dropFirst(count))), count)

        case .softBreak:
            return (count >= 1 ? nil : .softBreak, min(count, 1))

        case .hardBreak:
            return (count >= 1 ? nil : .hardBreak, min(count, 1))

        case .emphasis(let content):
            let before = content.plainText.count
            let trimmed = dropLeadingCharacters(from: content, count: count)
            let consumed = before - trimmed.plainText.count
            if trimmed.isEmpty { return (nil, consumed) }
            return (.emphasis(trimmed), consumed)

        case .strong(let content):
            let before = content.plainText.count
            let trimmed = dropLeadingCharacters(from: content, count: count)
            let consumed = before - trimmed.plainText.count
            if trimmed.isEmpty { return (nil, consumed) }
            return (.strong(trimmed), consumed)

        case .strikethrough(let content):
            let before = content.plainText.count
            let trimmed = dropLeadingCharacters(from: content, count: count)
            let consumed = before - trimmed.plainText.count
            if trimmed.isEmpty { return (nil, consumed) }
            return (.strikethrough(trimmed), consumed)

        case .link(let text, let url, let title):
            let before = text.plainText.count
            let trimmed = dropLeadingCharacters(from: text, count: count)
            let consumed = before - trimmed.plainText.count
            if trimmed.isEmpty { return (nil, consumed) }
            return (.link(text: trimmed, url: url, title: title), consumed)

        case .image(let url, let alt, let title):
            let length = alt?.count ?? 0
            if count >= length {
                return (nil, length)
            }
            return (.image(url: url, alt: alt, title: title), count)

        case .html(let html):
            let length = html.count
            if count >= length {
                return (nil, length)
            }
            return (.html(String(html.dropFirst(count))), count)

        case .math(let math):
            let length = math.count
            if count >= length {
                return (nil, length)
            }
            return (.math(String(math.dropFirst(count))), count)

        case .footnoteReference(let id):
            let length = id.count + 2
            if count >= length {
                return (nil, length)
            }
            return (.footnoteReference(id: id), count)
        }
    }

    private func parseTable(_ table: Markdown.Table, index: Int) -> MarkdownBlock {
        var rows: [MarkdownTableRow] = []

        let headerCells = table.head.cells.map { self.parseInlineContent($0.children) }
        rows.append(MarkdownTableRow(cells: Array(headerCells), isHeader: true, index: 0))

        var rowIndex = 1
        for row in table.body.rows {
            let cells = row.cells.map { self.parseInlineContent($0.children) }
            rows.append(MarkdownTableRow(cells: Array(cells), isHeader: false, index: rowIndex))
            rowIndex += 1
        }

        let alignments = table.columnAlignments.map { alignment -> ColumnAlignment in
            switch alignment {
            case .left: return .left
            case .center: return .center
            case .right: return .right
            case .none: return .none
            }
        }

        return MarkdownBlock(.table(rows: rows, alignments: Array(alignments)), index: index)
    }

    // MARK: - Inline Parsing

    private func parseInlineContent<S: Sequence>(_ elements: S) -> MarkdownInlineContent where S.Element == Markup {
        var result: [InlineElement] = []

        for element in elements {
            result.append(contentsOf: parseInlineElement(element))
        }

        return MarkdownInlineContent(elements: result)
    }

    private func parseInlineElement(_ element: Markup) -> [InlineElement] {
        switch element {
        case let text as Markdown.Text:
            return parseTextWithMath(text.string)

        case let emphasis as Emphasis:
            let content = parseInlineContent(emphasis.children)
            return [.emphasis(content)]

        case let strong as Strong:
            let content = parseInlineContent(strong.children)
            return [.strong(content)]

        case let strikethrough as Strikethrough:
            let content = parseInlineContent(strikethrough.children)
            return [.strikethrough(content)]

        case let code as InlineCode:
            return [.code(code.code)]

        case let link as Markdown.Link:
            let content = parseInlineContent(link.children)
            return [.link(text: content, url: link.destination ?? "", title: link.title)]

        case let image as Markdown.Image:
            return [.image(url: image.source ?? "", alt: extractAltText(from: image), title: image.title)]

        case is SoftBreak:
            return [.softBreak]

        case is LineBreak:
            return [.hardBreak]

        case let html as InlineHTML:
            return [.html(html.rawHTML)]

        default:
            return []
        }
    }

    private func parseTextWithMath(_ text: String) -> [InlineElement] {
        var result: [InlineElement] = []
        var currentText = ""
        var i = text.startIndex

        func flushCurrentText() {
            guard !currentText.isEmpty else { return }
            result.append(.text(replaceEmojiShortcodes(in: currentText)))
            currentText = ""
        }

        while i < text.endIndex {
            if text[i] == "[" {
                if let (footnoteId, endIndex) = extractFootnoteReference(text, from: i) {
                    flushCurrentText()
                    result.append(.footnoteReference(id: footnoteId))
                    i = endIndex
                    continue
                }
            }

            if text[i] == "$" {
                let next = text.index(after: i)
                if next < text.endIndex && text[next] == "$" {
                    currentText.append(text[i])
                    i = next
                    currentText.append(text[i])
                    i = text.index(after: i)
                    continue
                }

                if let (math, endIndex) = extractInlineMath(text, from: i) {
                    flushCurrentText()
                    result.append(.math(math))
                    i = endIndex
                    continue
                }
            }

            currentText.append(text[i])
            i = text.index(after: i)
        }

        if !currentText.isEmpty {
            result.append(.text(replaceEmojiShortcodes(in: currentText)))
        }

        return result.isEmpty ? [.text(text)] : result
    }

    private func replaceEmojiShortcodes(in text: String) -> String {
        guard text.contains(":") else { return text }
        var result = ""
        var index = text.startIndex

        while index < text.endIndex {
            if text[index] == ":" {
                let start = text.index(after: index)
                if let end = text[start...].firstIndex(of: ":") {
                    let shortcode = String(text[start..<end]).lowercased()
                    if let emoji = emojiShortcodes[shortcode] {
                        result.append(emoji)
                        index = text.index(after: end)
                        continue
                    }
                }
            }
            result.append(text[index])
            index = text.index(after: index)
        }

        return result
    }

    private func extractDefinitionList(from content: MarkdownInlineContent) -> [MarkdownDefinitionItem]? {
        let lines = splitInlineContentIntoLines(content)
        guard lines.count >= 2 else { return nil }

        var items: [MarkdownDefinitionItem] = []
        var currentTerm: MarkdownInlineContent?
        var definitions: [MarkdownInlineContent] = []
        var foundDefinition = false

        for line in lines {
            let trimmed = line.plainText.trimmingCharacters(in: .whitespacesAndNewlines)
            guard !trimmed.isEmpty else { continue }

            if trimmed.hasPrefix(":") {
                foundDefinition = true
                if currentTerm != nil {
                    let definitionText = stripDefinitionPrefix(from: trimmed)
                    if !definitionText.isEmpty {
                        definitions.append(MarkdownInlineContent(text: definitionText))
                    }
                }
            } else {
                if let term = currentTerm, !definitions.isEmpty {
                    items.append(MarkdownDefinitionItem(term: term, definitions: definitions))
                    definitions = []
                }
                currentTerm = MarkdownInlineContent(text: trimmed)
            }
        }

        if let term = currentTerm, !definitions.isEmpty {
            items.append(MarkdownDefinitionItem(term: term, definitions: definitions))
        }

        return (foundDefinition && !items.isEmpty) ? items : nil
    }

    private func extractAbbreviationList(from content: MarkdownInlineContent) -> [MarkdownAbbreviationItem]? {
        let lines = splitInlineContentIntoLines(content)
        var items: [MarkdownAbbreviationItem] = []
        var hasContent = false

        for line in lines {
            let trimmed = line.plainText.trimmingCharacters(in: .whitespacesAndNewlines)
            guard !trimmed.isEmpty else { continue }
            hasContent = true
            guard let item = parseAbbreviationDefinition(from: trimmed) else {
                return nil
            }
            items.append(item)
        }

        guard hasContent, !items.isEmpty else { return nil }
        return items
    }

    private func parseAbbreviationDefinition(from text: String) -> MarkdownAbbreviationItem? {
        guard text.hasPrefix("*[") else { return nil }
        guard let close = text.firstIndex(of: "]") else { return nil }
        let afterClose = text.index(after: close)
        guard afterClose < text.endIndex, text[afterClose] == ":" else { return nil }

        let abbrStart = text.index(text.startIndex, offsetBy: 2)
        let abbr = String(text[abbrStart..<close]).trimmingCharacters(in: .whitespaces)
        guard !abbr.isEmpty else { return nil }

        var defStart = text.index(after: afterClose)
        if defStart < text.endIndex && text[defStart] == " " {
            defStart = text.index(after: defStart)
        }
        let expansion = String(text[defStart...]).trimmingCharacters(in: .whitespaces)
        guard !expansion.isEmpty else { return nil }

        return MarkdownAbbreviationItem(abbreviation: abbr, expansion: expansion)
    }

    private func stripDefinitionPrefix(from text: String) -> String {
        var trimmed = text.trimmingCharacters(in: .whitespacesAndNewlines)
        while let first = trimmed.first, first == ":" || first == " " || first == "\t" {
            trimmed.removeFirst()
        }
        return trimmed.trimmingCharacters(in: .whitespacesAndNewlines)
    }

    private func splitInlineContentIntoLines(_ content: MarkdownInlineContent) -> [MarkdownInlineContent] {
        var lines: [[InlineElement]] = [[]]

        func startNewLine() {
            lines.append([])
        }

        for element in content.elements {
            switch element {
            case .softBreak, .hardBreak:
                startNewLine()
            case .text(let text):
                let parts = text.split(separator: "\n", omittingEmptySubsequences: false)
                for (idx, part) in parts.enumerated() {
                    if !part.isEmpty {
                        lines[lines.count - 1].append(.text(String(part)))
                    }
                    if idx < parts.count - 1 {
                        startNewLine()
                    }
                }
            default:
                lines[lines.count - 1].append(element)
            }
        }

        return lines.map { MarkdownInlineContent(elements: $0) }
    }

    private func extractFootnoteReference(_ text: String, from start: String.Index) -> (String, String.Index)? {
        guard text[start] == "[" else { return nil }
        let afterBracket = text.index(after: start)
        guard afterBracket < text.endIndex, text[afterBracket] == "^" else { return nil }

        var current = text.index(after: afterBracket)
        var id = ""

        while current < text.endIndex {
            if text[current] == "]" {
                if !id.isEmpty {
                    return (id, text.index(after: current))
                }
                return nil
            }
            let char = text[current]
            if char.isLetter || char.isNumber || char == "-" || char == "_" {
                id.append(char)
            } else {
                return nil
            }
            current = text.index(after: current)
        }
        return nil
    }

    private func extractInlineMath(_ text: String, from start: String.Index) -> (String, String.Index)? {
        guard text[start] == "$" else { return nil }
        let afterDollar = text.index(after: start)
        guard afterDollar < text.endIndex else { return nil }

        if text[afterDollar] == " " { return nil }

        var current = afterDollar
        while current < text.endIndex {
            if text[current] == "$" {
                let beforeDollar = text.index(before: current)
                if beforeDollar >= afterDollar && text[beforeDollar] == " " { return nil }

                let content = String(text[afterDollar..<current])
                if !content.isEmpty {
                    return (content, text.index(after: current))
                }
                return nil
            }
            if text[current] == "\n" { return nil }
            current = text.index(after: current)
        }
        return nil
    }

    private func extractAltText(from image: Markdown.Image) -> String? {
        var alt = ""
        for child in image.children {
            if let text = child as? Markdown.Text {
                alt += text.string
            }
        }
        return alt.isEmpty ? nil : alt
    }

    private func findStableBoundary(in content: String) -> (stable: String, buffer: String) {
        var inCodeBlock = false
        var inMathBlock = false
        var codeBlockStart: String.Index?
        var mathBlockStart: String.Index?
        var lastStableBoundary = content.startIndex
        var i = content.startIndex

        while i < content.endIndex {
            if content[i] == "$" && !inCodeBlock {
                let remaining = content[i...]
                if remaining.hasPrefix("$$") {
                    if inMathBlock {
                        let endOfMath = content.index(i, offsetBy: 2, limitedBy: content.endIndex) ?? content.endIndex
                        inMathBlock = false
                        mathBlockStart = nil
                        lastStableBoundary = endOfMath
                        i = endOfMath
                        continue
                    } else {
                        inMathBlock = true
                        mathBlockStart = i
                        i = content.index(i, offsetBy: 2, limitedBy: content.endIndex) ?? content.endIndex
                        continue
                    }
                }
            }

            if content[i] == "`" && !inMathBlock {
                let remaining = content[i...]
                if remaining.hasPrefix("```") {
                    if inCodeBlock {
                        var endOfLine = content.index(i, offsetBy: 3, limitedBy: content.endIndex) ?? content.endIndex
                        while endOfLine < content.endIndex && content[endOfLine] != "\n" {
                            endOfLine = content.index(after: endOfLine)
                        }
                        if endOfLine < content.endIndex {
                            endOfLine = content.index(after: endOfLine)
                        }
                        inCodeBlock = false
                        codeBlockStart = nil
                        lastStableBoundary = endOfLine
                        i = endOfLine
                        continue
                    } else {
                        inCodeBlock = true
                        codeBlockStart = i
                    }
                }
            }

            if !inCodeBlock && !inMathBlock && content[i] == "\n" {
                let next = content.index(after: i)
                if next < content.endIndex && content[next] == "\n" {
                    lastStableBoundary = content.index(after: next)
                }
            }

            i = content.index(after: i)
        }

        if inCodeBlock, let start = codeBlockStart {
            lastStableBoundary = start
        }
        if inMathBlock, let start = mathBlockStart {
            lastStableBoundary = min(lastStableBoundary, start)
        }

        let stable = String(content[..<lastStableBoundary])
        let buffer = String(content[lastStableBoundary...])

        return (stable, buffer)
    }
}
