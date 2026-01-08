import Foundation
import VVMarkdown
import ImageIO

#if canImport(UniformTypeIdentifiers)
import UniformTypeIdentifiers
#endif

#if canImport(AppKit)
import AppKit
public typealias PlatformFont = NSFont
#else
import UIKit
public typealias PlatformFont = UIFont
#endif

struct DumpOptions {
    var filePath: String
    var width: CGFloat
    var maxRuns: Int
    var imagePath: String?
    var imageScale: CGFloat
}

func parseArguments() -> DumpOptions? {
    var args = CommandLine.arguments.dropFirst()
    var filePath: String?
    var width: CGFloat = 1000
    var maxRuns = 80
    var imagePath: String? = "/tmp/VVMarkdownDump.png"
    var imageScale: CGFloat = 2.0

    while let arg = args.first {
        args = args.dropFirst()
        switch arg {
        case "--file", "-f":
            if let value = args.first {
                filePath = value
                args = args.dropFirst()
            }
        case "--image", "-i":
            if let value = args.first, !value.hasPrefix("-") {
                imagePath = value
                args = args.dropFirst()
            } else {
                imagePath = "VVMarkdownDump.png"
            }
        case "--no-image":
            imagePath = nil
        case "--scale":
            if let value = args.first, let number = Double(value) {
                imageScale = max(0.5, CGFloat(number))
                args = args.dropFirst()
            }
        case "--width", "-w":
            if let value = args.first, let number = Double(value) {
                width = CGFloat(number)
                args = args.dropFirst()
            }
        case "--max-runs":
            if let value = args.first, let number = Int(value) {
                maxRuns = number
                args = args.dropFirst()
            }
        default:
            if arg.hasPrefix("-") {
                continue
            }
            if filePath == nil {
                filePath = arg
            }
        }
    }

    if filePath == nil {
        let cwd = FileManager.default.currentDirectoryPath
        let candidate = (cwd as NSString).appendingPathComponent("test.md")
        if FileManager.default.fileExists(atPath: candidate) {
            filePath = candidate
        }
    }

    guard let resolvedPath = filePath else {
        return nil
    }

    return DumpOptions(
        filePath: resolvedPath,
        width: width,
        maxRuns: maxRuns,
        imagePath: imagePath,
        imageScale: imageScale
    )
}

func formatPoint(_ point: CGPoint) -> String {
    String(format: "(%.1f, %.1f)", point.x, point.y)
}

func formatSize(_ size: CGSize) -> String {
    String(format: "(%.1f × %.1f)", size.width, size.height)
}

func formatRect(_ rect: CGRect) -> String {
    "\(formatPoint(rect.origin)) \(formatSize(rect.size))"
}

func describeBlockType(_ type: LayoutBlockType) -> String {
    switch type {
    case .paragraph: return "paragraph"
    case .heading(let level): return "heading(\(level))"
    case .codeBlock(let language): return "code(\(language ?? "text"))"
    case .list: return "list"
    case .blockQuote: return "blockquote"
    case .alert(let kind): return "alert(\(kind.rawValue))"
    case .table: return "table"
    case .definitionList: return "definitionList"
    case .abbreviationList: return "abbreviationList"
    case .image: return "image"
    case .thematicBreak: return "thematicBreak"
    case .mathBlock: return "math"
    case .mermaid: return "mermaid"
    }
}

func describeRunStyle(_ style: TextRunStyle) -> String {
    var flags: [String] = []
    if style.isBold { flags.append("bold") }
    if style.isItalic { flags.append("italic") }
    if style.isCode { flags.append("code") }
    if style.isStrikethrough { flags.append("strike") }
    if style.isLink { flags.append("link") }
    if let variant = style.fontVariant { flags.append("\(variant)") }
    return flags.isEmpty ? "regular" : flags.joined(separator: "+")
}

private func collectInlineImageURLs(from content: MarkdownInlineContent) -> [String] {
    var urls: [String] = []
    func walk(_ content: MarkdownInlineContent) {
        for element in content.elements {
            switch element {
            case .image(let url, _, _):
                urls.append(url)
            case .link(let child, _, _):
                walk(child)
            case .strong(let child),
                 .emphasis(let child),
                 .strikethrough(let child):
                walk(child)
            default:
                continue
            }
        }
    }
    walk(content)
    return urls
}

private func collectImageURLs(from block: MarkdownBlock) -> [String] {
    switch block.type {
    case .image(let url, _):
        return [url]
    case .paragraph(let content),
         .heading(let content, _):
        return collectInlineImageURLs(from: content)
    case .list(let items, _, _):
        return collectImageURLs(from: items)
    case .table(let rows, _):
        return rows.flatMap { row in row.cells.flatMap { collectInlineImageURLs(from: $0) } }
    case .definitionList(let items):
        return items.flatMap { item in
            [collectInlineImageURLs(from: item.term)] + item.definitions.map { collectInlineImageURLs(from: $0) }
        }.flatMap { $0 }
    case .abbreviationList:
        return []
    case .blockQuote(let blocks),
         .alert(_, let blocks):
        return blocks.flatMap { collectImageURLs(from: $0) }
    case .htmlBlock:
        return []
    default:
        return []
    }
}

private func collectImageURLs(from items: [MarkdownListItem]) -> [String] {
    var urls: [String] = []
    for item in items {
        urls.append(contentsOf: collectInlineImageURLs(from: item.content))
        if !item.children.isEmpty {
            urls.append(contentsOf: collectImageURLs(from: item.children))
        }
    }
    return urls
}

private func collectImageURLs(from document: ParsedMarkdownDocument) -> [String] {
    var urls: [String] = []
    for block in document.blocks {
        urls.append(contentsOf: collectImageURLs(from: block))
    }
    return Array(Set(urls))
}

private func isSVGData(_ data: Data) -> Bool {
    guard let text = String(data: data, encoding: .utf8) else { return false }
    let lower = text.lowercased()
    return lower.contains("<svg") || lower.contains("image/svg+xml")
}

private func svgTypeIdentifier() -> CFString {
    #if canImport(UniformTypeIdentifiers)
    if #available(macOS 11.0, iOS 14.0, tvOS 14.0, *) {
        return UTType.svg.identifier as CFString
    }
    #endif
    return "public.svg-image" as CFString
}

private func loadImageData(from url: URL) -> Data? {
    if url.isFileURL {
        return try? Data(contentsOf: url)
    }
    let semaphore = DispatchSemaphore(value: 0)
    var result: Data?
    var responseError: Error?
    let task = URLSession.shared.dataTask(with: url) { data, _, error in
        result = data
        responseError = error
        semaphore.signal()
    }
    task.resume()
    _ = semaphore.wait(timeout: .now() + 12)
    if responseError != nil {
        return nil
    }
    return result
}

private func loadCGImage(from urlString: String) -> CGImage? {
    let expanded = (urlString as NSString).expandingTildeInPath
    let url: URL
    if expanded.hasPrefix("http://") || expanded.hasPrefix("https://") {
        guard let resolved = URL(string: expanded) else { return nil }
        url = resolved
    } else if expanded.hasPrefix("file://") {
        guard let resolved = URL(string: expanded) else { return nil }
        url = resolved
    } else if expanded.hasPrefix("/") {
        url = URL(fileURLWithPath: expanded)
    } else {
        url = URL(fileURLWithPath: FileManager.default.currentDirectoryPath).appendingPathComponent(expanded)
    }

    guard let data = loadImageData(from: url) else { return nil }
    let options: [CFString: Any] = isSVGData(data) ? [kCGImageSourceTypeIdentifierHint: svgTypeIdentifier()] : [:]
    guard let source = CGImageSourceCreateWithData(data as CFData, options as CFDictionary) else { return nil }
    return CGImageSourceCreateImageAtIndex(source, 0, options as CFDictionary)
}

func runBounds(_ run: LayoutTextRun, lineHeight: CGFloat, ascent: CGFloat) -> CGRect? {
    guard let first = run.glyphs.first else { return nil }
    var minX = first.position.x
    var maxX = first.position.x + first.size.width
    for glyph in run.glyphs.dropFirst() {
        minX = min(minX, glyph.position.x)
        maxX = max(maxX, glyph.position.x + glyph.size.width)
    }
    let minY = run.position.y - ascent
    let maxY = run.position.y + (lineHeight - ascent)
    return CGRect(x: minX, y: minY, width: maxX - minX, height: maxY - minY)
}

func dumpLayout(_ layout: MarkdownLayout, engine: MarkdownLayoutEngine, maxRuns: Int) -> String {
    var output: [String] = []
    output.append("Markdown layout dump")
    output.append("contentWidth=\(String(format: "%.1f", layout.contentWidth)) totalHeight=\(String(format: "%.1f", layout.totalHeight)) blocks=\(layout.blocks.count)")
    output.append("lineHeight=\(String(format: "%.2f", engine.currentLineHeight)) ascent=\(String(format: "%.2f", engine.currentAscent)) descent=\(String(format: "%.2f", engine.currentDescent))")

    let lineHeight = engine.currentLineHeight
    let ascent = engine.currentAscent

    for (index, block) in layout.blocks.enumerated() {
        output.append("")
        output.append("[\(index)] \(describeBlockType(block.blockType)) frame \(formatRect(block.frame)) id=\(block.blockId)")

        switch block.content {
        case .text(let runs):
            output.append("  runs=\(runs.count)")
            for (runIndex, run) in runs.prefix(maxRuns).enumerated() {
                let bounds = runBounds(run, lineHeight: lineHeight, ascent: ascent) ?? .zero
                let text = run.text.replacingOccurrences(of: "\n", with: "\\n")
                output.append("  [\(runIndex)] \"\(text)\" pos \(formatPoint(run.position)) bounds \(formatRect(bounds)) style \(describeRunStyle(run.style))")
            }
            if runs.count > maxRuns { output.append("  … \(runs.count - maxRuns) more runs") }

        case .inline(let runs, let images):
            output.append("  runs=\(runs.count) images=\(images.count)")
            for (runIndex, run) in runs.prefix(maxRuns).enumerated() {
                let bounds = runBounds(run, lineHeight: lineHeight, ascent: ascent) ?? .zero
                let text = run.text.replacingOccurrences(of: "\n", with: "\\n")
                output.append("  [\(runIndex)] \"\(text)\" pos \(formatPoint(run.position)) bounds \(formatRect(bounds)) style \(describeRunStyle(run.style))")
            }
            if runs.count > maxRuns { output.append("  … \(runs.count - maxRuns) more runs") }
            for image in images {
                output.append("  img \(formatRect(image.frame)) url=\(image.url) link=\(image.linkURL ?? "-")")
            }

        case .imageRow(let images):
            output.append("  imageRow count=\(images.count)")
            for image in images {
                output.append("  img \(formatRect(image.frame)) url=\(image.url) link=\(image.linkURL ?? "-")")
            }

        case .code(_, let language, let lines):
            let maxLine = lines.map(\.lineNumber).max() ?? lines.count
            output.append("  code lines=\(lines.count) language=\(language ?? "text") gutterWidth=\(String(format: "%.1f", engine.measureTextWidth(String(repeating: "8", count: max(2, String(maxLine).count)), variant: .monospace) + 20))")
            for line in lines.prefix(12) {
                let lineY = block.frame.origin.y + line.yOffset
                output.append("  line \(line.lineNumber) y=\(String(format: "%.1f", lineY)) text=\"\(line.text)\"")
            }
            if lines.count > 12 { output.append("  … \(lines.count - 12) more lines") }

        case .listItems(let items):
            output.append("  listItems=\(items.count)")
            for item in items.prefix(20) {
                output.append("  item depth=\(item.depth) bullet=\(formatPoint(item.bulletPosition)) runs=\(item.contentRuns.count)")
            }
            if items.count > 20 { output.append("  … \(items.count - 20) more items") }

        case .quoteBlocks(let blocks):
            output.append("  quoteBlocks=\(blocks.count)")

        case .tableRows(let rows):
            output.append("  table rows=\(rows.count)")
            for (rowIndex, row) in rows.enumerated() {
                output.append("  row[\(rowIndex)] frame \(formatRect(row.frame)) header=\(row.isHeader)")
                for (cellIndex, cell) in row.cells.enumerated() {
                    let baseline = cell.textRuns.first?.position.y ?? 0
                    output.append("    cell[\(cellIndex)] frame \(formatRect(cell.frame)) baseline=\(String(format: "%.1f", baseline)) runs=\(cell.textRuns.count) images=\(cell.inlineImages.count)")
                }
            }

        case .definitionList(let items):
            output.append("  definitionItems=\(items.count)")

        case .abbreviationList(let items):
            output.append("  abbreviationItems=\(items.count)")

        case .image(let url, _, let size):
            if let size = size {
                output.append("  image url=\(url) size=\(formatSize(size))")
            } else {
                output.append("  image url=\(url) size=unknown")
            }

        case .thematicBreak:
            output.append("  thematicBreak")

        case .math(let latex, let runs):
            output.append("  math runs=\(runs.count) latex=\"\(latex.prefix(80))\"")

        case .mermaid(let diagram):
            output.append("  mermaid frame \(formatRect(diagram.frame)) nodes=\(diagram.nodes.count) lines=\(diagram.lines.count) labels=\(diagram.labels.count)")
        }
    }

    return output.joined(separator: "\n")
}

#if canImport(AppKit)
private func cgColor(_ color: SIMD4<Float>) -> CGColor {
    NSColor(calibratedRed: CGFloat(color.x), green: CGFloat(color.y), blue: CGFloat(color.z), alpha: CGFloat(color.w)).cgColor
}

private func variantForRun(_ run: LayoutTextRun) -> FontVariant {
    if run.style.isCode {
        return .monospace
    }
    if run.style.isBold && run.style.isItalic {
        return .boldItalic
    }
    if run.style.isBold {
        return .bold
    }
    if let override = run.style.fontVariant {
        if override == .semibold && run.style.isItalic {
            return .semiboldItalic
        }
        return override
    }
    if run.style.isItalic {
        return .italic
    }
    return .regular
}

private func fontForRun(_ run: LayoutTextRun, engine: MarkdownLayoutEngine) -> CTFont? {
    let runSize = run.glyphs.first?.fontSize ?? engine.baseFontSize
    if let fontName = run.glyphs.first?.fontName {
        let resolvedName: String
        switch fontName {
        case ".AppleColorEmojiUI":
            resolvedName = "AppleColorEmoji"
        default:
            resolvedName = fontName
        }
        return CTFontCreateWithName(resolvedName as CFString, runSize, nil)
    }
    let variant = variantForRun(run)
    guard let baseFont = engine.font(for: variant) else { return nil }
    return CTFontCreateCopyWithAttributes(baseFont, runSize, nil, nil)
}

private func drawTextRuns(_ runs: [LayoutTextRun], context: CGContext, engine: MarkdownLayoutEngine, theme: MarkdownTheme) {
    for run in runs {
        guard let font = fontForRun(run, engine: engine) else { continue }
        let color = cgColor(run.style.color)
        let resolvedColor = NSColor(cgColor: color) ?? .white
        let attributes: [NSAttributedString.Key: Any] = [
            .font: font,
            .foregroundColor: resolvedColor
        ]
        let line = CTLineCreateWithAttributedString(NSAttributedString(string: run.text, attributes: attributes))
        context.textPosition = run.position
        CTLineDraw(line, context)

        if run.style.isStrikethrough {
            let ascent = CTFontGetAscent(font)
            let strikeY = run.position.y - ascent * 0.35
            let width = CGFloat(CTLineGetTypographicBounds(line, nil, nil, nil))
            context.setStrokeColor(cgColor(theme.strikethroughColor))
            context.setLineWidth(1)
            context.stroke(CGRect(x: run.position.x, y: strikeY, width: width, height: 1))
        }

        if run.style.isLink {
            let underlineY = run.position.y + max(1, engine.currentDescent * 0.4)
            let width = CGFloat(CTLineGetTypographicBounds(line, nil, nil, nil))
            context.setStrokeColor(cgColor(theme.linkColor))
            context.setLineWidth(1)
            context.stroke(CGRect(x: run.position.x, y: underlineY, width: width, height: 1))
        }
    }
}

private func drawInlineImages(_ images: [LayoutInlineImage], imageCache: [String: CGImage], context: CGContext) {
    for image in images {
        if let cgImage = imageCache[image.url] {
            context.saveGState()
            context.interpolationQuality = .high
            context.draw(cgImage, in: image.frame)
            context.restoreGState()
        } else {
            context.setFillColor(NSColor(calibratedWhite: 0.12, alpha: 1.0).cgColor)
            context.fill(image.frame)
            context.setStrokeColor(NSColor(calibratedWhite: 0.35, alpha: 1.0).cgColor)
            context.setLineWidth(1)
            context.stroke(image.frame)
        }
    }
}

private func drawListItem(_ item: LayoutListItem, context: CGContext, engine: MarkdownLayoutEngine, theme: MarkdownTheme, imageCache: [String: CGImage]) {
    var bulletCenterY = item.bulletPosition.y - engine.currentAscent * 0.32
    if let sample = item.contentRuns.first {
        bulletCenterY = sample.position.y - engine.currentAscent * 0.32
    }
    let bulletSize = max(6, min(10, engine.currentLineHeight * 0.45))
    let bulletRect = CGRect(
        x: item.bulletPosition.x,
        y: bulletCenterY - bulletSize * 0.5,
        width: bulletSize,
        height: bulletSize
    )
    context.setStrokeColor(cgColor(theme.listBulletColor))
    context.setFillColor(cgColor(theme.listBulletColor))

    switch item.bulletType {
    case .disc:
        context.fillEllipse(in: bulletRect)
    case .circle:
        context.setLineWidth(1)
        context.strokeEllipse(in: bulletRect)
    case .square:
        context.fill(bulletRect)
    case .number(let num):
        let text = "\(num)."
        if let font = engine.font(for: .regular) {
            let resolvedColor = NSColor(cgColor: cgColor(theme.listBulletColor)) ?? .white
            let attrs: [NSAttributedString.Key: Any] = [
                .font: font,
                .foregroundColor: resolvedColor
            ]
            let line = CTLineCreateWithAttributedString(NSAttributedString(string: text, attributes: attrs))
            context.textPosition = item.bulletPosition
            CTLineDraw(line, context)
        }
    case .checkboxChecked, .checkboxUnchecked:
        let checked = item.bulletType == .checkboxChecked
        let boxSize = max(10, engine.currentLineHeight * 0.6)
        let boxRect = CGRect(
            x: item.bulletPosition.x,
            y: bulletCenterY - boxSize * 0.5,
            width: boxSize,
            height: boxSize
        )
        let color = checked ? theme.checkboxCheckedColor : theme.checkboxUncheckedColor
        context.setStrokeColor(cgColor(color))
        context.setLineWidth(1)
        context.stroke(boxRect)
        if checked {
            context.setLineWidth(2)
            context.move(to: CGPoint(x: boxRect.minX + boxSize * 0.2, y: boxRect.midY))
            context.addLine(to: CGPoint(x: boxRect.midX, y: boxRect.minY + boxSize * 0.25))
            context.addLine(to: CGPoint(x: boxRect.maxX - boxSize * 0.2, y: boxRect.maxY - boxSize * 0.2))
            context.strokePath()
        }
    }

    drawInlineImages(item.inlineImages, imageCache: imageCache, context: context)
    drawTextRuns(item.contentRuns, context: context, engine: engine, theme: theme)
    for child in item.children {
        drawListItem(child, context: context, engine: engine, theme: theme, imageCache: imageCache)
    }
}

private func drawCodeBlock(
    frame: CGRect,
    language: String?,
    lines: [LayoutCodeLine],
    context: CGContext,
    engine: MarkdownLayoutEngine,
    theme: MarkdownTheme
) {
    let borderWidth = CGFloat(theme.codeBorderWidth)
    let cornerRadius = CGFloat(theme.codeBlockCornerRadius)
    let headerHeight = CGFloat(theme.codeBlockHeaderHeight)
    let padding = CGFloat(theme.codeBlockPadding)
    let gutterDigits = max(1, String(max(1, lines.count)).count)
    let gutterWidth = max(32, engine.measureTextWidth(String(repeating: "8", count: gutterDigits), variant: .monospace) + 16)

    let path = CGPath(roundedRect: frame, cornerWidth: cornerRadius, cornerHeight: cornerRadius, transform: nil)
    context.setFillColor(cgColor(theme.codeBackgroundColor))
    context.addPath(path)
    context.fillPath()

    if borderWidth > 0 {
        context.setStrokeColor(cgColor(theme.codeBorderColor))
        context.setLineWidth(borderWidth)
        context.addPath(path)
        context.strokePath()
    }

    let innerFrame = frame.insetBy(dx: borderWidth, dy: borderWidth)
    let headerFrame = CGRect(x: innerFrame.minX, y: innerFrame.minY, width: innerFrame.width, height: min(headerHeight, innerFrame.height))
    let headerPath = CGPath(roundedRect: headerFrame, cornerWidth: min(headerHeight, cornerRadius), cornerHeight: min(headerHeight, cornerRadius), transform: nil)
    context.setFillColor(cgColor(theme.codeHeaderBackgroundColor))
    context.addPath(headerPath)
    context.fillPath()

    let gutterFrame = CGRect(
        x: frame.minX + borderWidth,
        y: frame.minY + headerHeight + borderWidth,
        width: gutterWidth,
        height: max(0, frame.height - headerHeight - borderWidth * 2)
    )
    context.setFillColor(cgColor(theme.codeGutterBackgroundColor))
    context.fill(gutterFrame)
    context.setStrokeColor(cgColor(theme.codeHeaderDividerColor))
    context.setLineWidth(max(1, CGFloat(theme.codeGutterDividerWidth)))
    context.stroke(CGRect(x: gutterFrame.maxX - 1, y: gutterFrame.minY, width: 1, height: gutterFrame.height))

    let label = (language?.isEmpty == false ? language! : "Text").uppercased()
    if let labelFont = engine.font(for: .semibold) {
        let resolvedColor = NSColor(cgColor: cgColor(theme.codeHeaderTextColor)) ?? .white
        let attrs: [NSAttributedString.Key: Any] = [
            .font: labelFont,
            .foregroundColor: resolvedColor
        ]
        let line = CTLineCreateWithAttributedString(NSAttributedString(string: label, attributes: attrs))
        context.textPosition = CGPoint(x: frame.minX + 12 + borderWidth, y: frame.minY + headerHeight * 0.65)
        CTLineDraw(line, context)
    }

    for line in lines {
        let lineY = frame.minY + line.yOffset
        let lineNumber = "\(line.lineNumber)"
        let numberWidth = engine.measureTextWidth(lineNumber, variant: .monospace)
        if let monoFont = engine.font(for: .monospace) {
            let resolvedColor = NSColor(cgColor: cgColor(theme.codeGutterTextColor)) ?? .white
            let attrs: [NSAttributedString.Key: Any] = [
                .font: monoFont,
                .foregroundColor: resolvedColor
            ]
            let numberLine = CTLineCreateWithAttributedString(NSAttributedString(string: lineNumber, attributes: attrs))
            let numberX = frame.minX + borderWidth + gutterWidth - numberWidth - 8
            context.textPosition = CGPoint(x: numberX, y: lineY)
            CTLineDraw(numberLine, context)
        }

        var x = frame.minX + borderWidth + padding + gutterWidth
        for token in line.tokens {
            if token.text.isEmpty { continue }
            if let monoFont = engine.font(for: .monospace) {
                let resolvedColor = NSColor(cgColor: cgColor(token.color)) ?? .white
                let attrs: [NSAttributedString.Key: Any] = [
                    .font: monoFont,
                    .foregroundColor: resolvedColor
                ]
                let tokenLine = CTLineCreateWithAttributedString(NSAttributedString(string: token.text, attributes: attrs))
                context.textPosition = CGPoint(x: x, y: lineY)
                CTLineDraw(tokenLine, context)
                let tokenWidth = engine.measureTextWidth(token.text, variant: .monospace)
                x += tokenWidth
            }
        }
    }
}

private func drawTable(
    frame: CGRect,
    rows: [LayoutTableRow],
    context: CGContext,
    engine: MarkdownLayoutEngine,
    theme: MarkdownTheme,
    imageCache: [String: CGImage]
) {
    context.setFillColor(cgColor(theme.tableBackground))
    context.fill(frame)
    context.setStrokeColor(cgColor(theme.tableBorderColor))
    context.setLineWidth(1)
    context.stroke(frame)

    for row in rows where row.isHeader {
        context.setFillColor(cgColor(theme.tableHeaderBackground))
        context.fill(row.frame)
    }

    for row in rows {
        for cell in row.cells {
            drawInlineImages(cell.inlineImages, imageCache: imageCache, context: context)
            drawTextRuns(cell.textRuns, context: context, engine: engine, theme: theme)
        }
        context.setStrokeColor(cgColor(theme.tableBorderColor))
        context.setLineWidth(1)
        context.move(to: CGPoint(x: frame.minX, y: row.frame.maxY))
        context.addLine(to: CGPoint(x: frame.maxX, y: row.frame.maxY))
        context.strokePath()
    }
}

private func drawBlock(_ block: LayoutBlock, context: CGContext, engine: MarkdownLayoutEngine, theme: MarkdownTheme, imageCache: [String: CGImage]) {
    switch block.content {
    case .text(let runs):
        drawTextRuns(runs, context: context, engine: engine, theme: theme)
    case .inline(let runs, let images):
        drawInlineImages(images, imageCache: imageCache, context: context)
        drawTextRuns(runs, context: context, engine: engine, theme: theme)
    case .image(let url, _, _):
        if let cgImage = imageCache[url] {
            context.saveGState()
            context.interpolationQuality = .high
            context.draw(cgImage, in: block.frame)
            context.restoreGState()
        } else {
            let label = url.isEmpty ? "image" : url
            context.setFillColor(NSColor(calibratedWhite: 0.12, alpha: 1.0).cgColor)
            context.fill(block.frame)
            context.setStrokeColor(NSColor(calibratedWhite: 0.35, alpha: 1.0).cgColor)
            context.setLineWidth(1)
            context.stroke(block.frame)
            if let font = engine.font(for: .regular) {
                let attrs: [NSAttributedString.Key: Any] = [
                    .font: font,
                    .foregroundColor: NSColor(calibratedWhite: 0.7, alpha: 1.0)
                ]
                let line = CTLineCreateWithAttributedString(NSAttributedString(string: label, attributes: attrs))
                context.textPosition = CGPoint(x: block.frame.minX + 8, y: block.frame.minY + 18)
                CTLineDraw(line, context)
            }
        }
    case .imageRow(let images):
        drawInlineImages(images, imageCache: imageCache, context: context)
    case .code(_, let language, let lines):
        drawCodeBlock(frame: block.frame, language: language, lines: lines, context: context, engine: engine, theme: theme)
    case .listItems(let items):
        for item in items {
            drawListItem(item, context: context, engine: engine, theme: theme, imageCache: imageCache)
        }
    case .quoteBlocks(let blocks):
        context.setStrokeColor(cgColor(theme.blockQuoteBorderColor))
        context.setLineWidth(CGFloat(theme.blockQuoteBorderWidth))
        context.move(to: CGPoint(x: block.frame.minX + 1, y: block.frame.minY))
        context.addLine(to: CGPoint(x: block.frame.minX + 1, y: block.frame.maxY))
        context.strokePath()
        for nested in blocks {
            drawBlock(nested, context: context, engine: engine, theme: theme, imageCache: imageCache)
        }
    case .tableRows(let rows):
        drawTable(frame: block.frame, rows: rows, context: context, engine: engine, theme: theme, imageCache: imageCache)
    case .definitionList(let items):
        for item in items {
            drawInlineImages(item.termImages, imageCache: imageCache, context: context)
            drawTextRuns(item.termRuns, context: context, engine: engine, theme: theme)
            for (idx, runs) in item.definitionRuns.enumerated() {
                if idx < item.definitionImages.count {
                    drawInlineImages(item.definitionImages[idx], imageCache: imageCache, context: context)
                }
                drawTextRuns(runs, context: context, engine: engine, theme: theme)
            }
        }
    case .abbreviationList(let items):
        for item in items {
            drawInlineImages(item.images, imageCache: imageCache, context: context)
            drawTextRuns(item.runs, context: context, engine: engine, theme: theme)
        }
    case .thematicBreak:
        context.setStrokeColor(cgColor(theme.thematicBreakColor))
        context.setLineWidth(1)
        context.move(to: CGPoint(x: block.frame.minX + 20, y: block.frame.midY))
        context.addLine(to: CGPoint(x: block.frame.maxX - 20, y: block.frame.midY))
        context.strokePath()
    case .math(let latex, _):
        context.setFillColor(cgColor(theme.codeBackgroundColor))
        context.fill(block.frame)
        if let font = engine.font(for: .regular) {
            let resolvedColor = NSColor(cgColor: cgColor(theme.mathColor)) ?? .white
            let attrs: [NSAttributedString.Key: Any] = [
                .font: font,
                .foregroundColor: resolvedColor
            ]
            let line = CTLineCreateWithAttributedString(NSAttributedString(string: latex, attributes: attrs))
            context.textPosition = CGPoint(x: block.frame.minX + 8, y: block.frame.minY + 18)
            CTLineDraw(line, context)
        }
    case .mermaid(let diagram):
        context.setFillColor(cgColor(theme.diagramBackground))
        context.fill(diagram.frame)
        context.setStrokeColor(cgColor(theme.diagramLineColor))
        context.setLineWidth(1)
        context.stroke(diagram.frame)
    }
}

private func renderLayoutImage(
    layout: MarkdownLayout,
    engine: MarkdownLayoutEngine,
    theme: MarkdownTheme,
    imageCache: [String: CGImage],
    options: DumpOptions
) {
    let size = CGSize(width: layout.contentWidth, height: layout.totalHeight)
    let scale = max(0.5, options.imageScale)
    let pixelWidth = max(1, Int(size.width * scale))
    let pixelHeight = max(1, Int(size.height * scale))

    let bytesPerRow = pixelWidth * 4
    let colorSpace = CGColorSpaceCreateDeviceRGB()
    let bitmapInfo = CGImageAlphaInfo.premultipliedLast.rawValue

    guard let context = CGContext(
        data: nil,
        width: pixelWidth,
        height: pixelHeight,
        bitsPerComponent: 8,
        bytesPerRow: bytesPerRow,
        space: colorSpace,
        bitmapInfo: bitmapInfo
    ) else { return }

    // Fill the full image before applying transforms so we never leave transparent rows.
    context.setFillColor(cgColor(theme.codeBackgroundColor))
    context.fill(CGRect(origin: .zero, size: CGSize(width: CGFloat(pixelWidth), height: CGFloat(pixelHeight))))

    // Flip the context so layout coordinates use a top-left origin.
    // Use an explicit transform to avoid scale/translation order bugs.
    let transform = CGAffineTransform(a: scale, b: 0, c: 0, d: -scale, tx: 0, ty: size.height * scale)
    context.concatenate(transform)
    // CoreText expects a y-up text matrix; flip text to stay upright in the y-down layout space.
    context.textMatrix = CGAffineTransform(scaleX: 1, y: -1)

    for block in layout.blocks {
        drawBlock(block, context: context, engine: engine, theme: theme, imageCache: imageCache)
    }

    if let path = options.imagePath,
       let image = context.makeImage() {
        let url = URL(fileURLWithPath: path)
        let type: CFString
        #if canImport(UniformTypeIdentifiers)
        if #available(macOS 11.0, iOS 14.0, tvOS 14.0, *) {
            type = UTType.png.identifier as CFString
        } else {
            type = "public.png" as CFString
        }
        #else
        type = "public.png" as CFString
        #endif

        if let destination = CGImageDestinationCreateWithURL(url as CFURL, type, 1, nil) {
            CGImageDestinationAddImage(destination, image, nil)
            if CGImageDestinationFinalize(destination) {
                print("Wrote image: \(url.path)")
            }
        }
    }
}
#endif

guard let options = parseArguments() else {
    print("Usage: VVMarkdownDump --file <path> [--width <px>] [--max-runs <n>] [--image <path>] [--no-image] [--scale <n>]")
    exit(1)
}

let fileURL = URL(fileURLWithPath: options.filePath)
let content: String

do {
    content = try String(contentsOf: fileURL, encoding: .utf8)
} catch {
    print("Failed to read file: \(fileURL.path) (\(error))")
    exit(1)
}

let parser = MarkdownParser()
let document = parser.parse(content)

let font = PlatformFont.monospacedSystemFont(ofSize: 14, weight: .regular)
let theme = MarkdownTheme.dark
let engine = MarkdownLayoutEngine(baseFont: font, theme: theme, contentWidth: options.width)
let imageURLs = collectImageURLs(from: document)
var imageCache: [String: CGImage] = [:]
var imageSizes: [String: CGSize] = [:]
for url in imageURLs {
    if let cgImage = loadCGImage(from: url) {
        imageCache[url] = cgImage
        imageSizes[url] = CGSize(width: cgImage.width, height: cgImage.height)
    }
}
engine.updateImageSizeProvider { imageSizes[$0] }
let layout = engine.layout(document)

let dump = dumpLayout(layout, engine: engine, maxRuns: options.maxRuns)
print(dump)

#if canImport(AppKit)
if options.imagePath != nil {
    renderLayoutImage(layout: layout, engine: engine, theme: theme, imageCache: imageCache, options: options)
}
#else
if options.imagePath != nil {
    print("Image output is only available on AppKit platforms.")
}
#endif
