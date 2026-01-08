//  VVMarkdownSceneBuilder.swift
//  VVMarkdown
//
//  Converts MarkdownLayout blocks into VVMetalPrimitives scenes.

import Foundation
import CoreText
import simd
import VVHighlighting
import VVMetalPrimitives

struct VVMarkdownSceneBuilder {
    typealias LineMetrics = (line: CTLine, length: Int, originX: CGFloat, lineY: CGFloat, lineHeight: CGFloat, baseline: CGFloat, ascent: CGFloat, descent: CGFloat, lineWidth: CGFloat)

    let theme: MarkdownTheme
    let layoutEngine: MarkdownLayoutEngine
    let contentWidth: CGFloat
    let scale: CGFloat
    let componentProvider: MarkdownComponentProvider?
    let styleRegistry: MarkdownStyleRegistry?
    let highlightedCodeBlocks: [String: HighlightedCodeBlock]
    let copiedBlockId: String?
    let copiedAt: TimeInterval

    let runLineBounds: (LayoutTextRun) -> CGRect?
    let runRenderedBounds: (LayoutTextRun) -> CGRect?
    let runBounds: (LayoutTextRun) -> CGRect?
    let runVisualBounds: (LayoutTextRun) -> CGRect?
    let lineMetrics: (LayoutTextRun) -> LineMetrics?
    let runFont: (LayoutTextRun) -> CTFont?

    func buildScene(from layout: MarkdownLayout) -> VVScene {
        var builder = VVSceneBuilder()
        let env = VVLayoutEnvironment(
            scale: scale,
            defaultTextColor: theme.textColor,
            defaultCornerRadius: CGFloat(theme.codeBlockCornerRadius)
        )
        let context = MarkdownComponentContext(
            theme: theme,
            layoutEngine: layoutEngine,
            contentWidth: layout.contentWidth
        )
        let componentFactory = VVMarkdownComponentFactory(builder: self)
        let defaultFactory: (LayoutBlock) -> VVComponent = { block in
            componentFactory.component(for: block)
        }
        for block in layout.blocks {
            let component = componentProvider?(block, context, defaultFactory) ?? defaultFactory(block)
            let styledComponent = componentFactory.applyStyleRegistry(to: component, for: block)
            let measured = styledComponent.measure(in: env, width: layout.contentWidth)
            builder.add(node: measured.node)
        }
        return builder.scene
    }

    fileprivate func makeBlockComponent(for block: LayoutBlock) -> VVComponent {
        let clipRect = CGRect(origin: .zero, size: block.frame.size)
        switch block.content {
        case .text(let runs):
            let primitives = makeTextRunPrimitives(runs, relativeTo: block.frame)
            let textComponent = VVTextBlockComponent(runs: primitives)
            return VVFrameComponent(frame: block.frame, child: textComponent, clipRect: clipRect)
        case .inline(let runs, let images):
            let textComponent = VVTextBlockComponent(runs: makeTextRunPrimitives(runs, relativeTo: block.frame))
            let imageComponents = images.map { makeInlineImageComponent($0, relativeTo: block.frame) }
            let layer = VVLayerComponent(children: [textComponent] + imageComponents)
            return VVFrameComponent(frame: block.frame, child: layer, clipRect: clipRect)
        case .imageRow(let images):
            let imageComponents = images.map { makeInlineImageComponent($0, relativeTo: block.frame) }
            let layer = VVLayerComponent(children: imageComponents)
            return VVFrameComponent(frame: block.frame, child: layer, clipRect: clipRect)
        case .image(let url, _, let size):
            let imageSize = size ?? block.frame.size
            let imageComponent = VVImageComponent(url: url, size: imageSize, cornerRadius: 4)
            return VVFrameComponent(frame: block.frame, child: imageComponent, clipRect: clipRect)
        case .thematicBreak:
            let line = VVRuleComponent(
                thickness: 2,
                color: theme.thematicBreakColor,
                inset: 20
            )
            return VVFrameComponent(frame: block.frame, child: line, clipRect: clipRect)
        case .code(let code, let language, let lines):
            var codeBuilder = VVSceneBuilder()
            appendCodeBlockPrimitives(
                blockId: block.blockId,
                code: code,
                language: language,
                lines: lines,
                frame: block.frame,
                to: &codeBuilder
            )
            let codeNode = localizedNode(from: codeBuilder.scene, blockFrame: block.frame)
            let component = VVPrimitiveComponent(node: codeNode, size: block.frame.size)
            return VVFrameComponent(frame: block.frame, child: component, clipRect: clipRect)
        case .quoteBlocks:
            let component = makePrimitiveComponent(for: block)
            return VVFrameComponent(frame: block.frame, child: component, clipRect: clipRect)
        case .listItems:
            let component = makePrimitiveComponent(for: block)
            return VVFrameComponent(frame: block.frame, child: component, clipRect: clipRect)
        case .tableRows:
            let component = makePrimitiveComponent(for: block)
            return VVFrameComponent(frame: block.frame, child: component, clipRect: clipRect)
        case .definitionList:
            let component = makePrimitiveComponent(for: block)
            return VVFrameComponent(frame: block.frame, child: component, clipRect: clipRect)
        case .abbreviationList:
            let component = makePrimitiveComponent(for: block)
            return VVFrameComponent(frame: block.frame, child: component, clipRect: clipRect)
        case .math:
            let component = makePrimitiveComponent(for: block)
            return VVFrameComponent(frame: block.frame, child: component, clipRect: clipRect)
        case .mermaid:
            let component = makePrimitiveComponent(for: block)
            return VVFrameComponent(frame: block.frame, child: component, clipRect: clipRect)
        }
    }

    private func makePrimitiveComponent(for block: LayoutBlock) -> VVPrimitiveComponent {
        var builder = VVSceneBuilder()
        appendBlock(block, to: &builder)
        let node = localizedNode(from: builder.scene, blockFrame: block.frame)
        return VVPrimitiveComponent(node: node, size: block.frame.size)
    }

    fileprivate func applyStyleRegistry(to component: VVComponent, for block: LayoutBlock) -> VVComponent {
        guard let registry = styleRegistry else { return component }
        let style = registry.style(for: block.blockType)
        var wrapped: VVComponent = component
        if let backgroundColor = style.backgroundColor {
            let cornerRadius = style.cornerRadius ?? 0
            let background = VVQuadPrimitive(frame: CGRect(origin: .zero, size: block.frame.size), color: backgroundColor, cornerRadius: cornerRadius)
            let backgroundNode = VVNode(primitives: [.quad(background)])
            wrapped = VVLayerComponent(children: [VVAbsoluteComponent(frame: CGRect(origin: .zero, size: block.frame.size), child: backgroundNode), wrapped])
        }
        if let borderColor = style.borderColor, let borderWidth = style.borderWidth, borderWidth > 0 {
            let cornerRadius = style.cornerRadius ?? 0
            let borderQuad = VVQuadPrimitive(frame: CGRect(origin: .zero, size: block.frame.size), color: borderColor, cornerRadius: cornerRadius)
            let borderNode = VVNode(primitives: [.quad(borderQuad)])
            wrapped = VVLayerComponent(children: [VVAbsoluteComponent(frame: CGRect(origin: .zero, size: block.frame.size), child: borderNode), wrapped])
        }
        if style.padding.top != 0 || style.padding.left != 0 || style.padding.bottom != 0 || style.padding.right != 0 {
            wrapped = VVInsetComponent(insets: style.padding, child: wrapped)
        }
        return wrapped
    }

    private func makeInlineImageComponent(_ image: LayoutInlineImage, relativeTo frame: CGRect) -> VVComponent {
        let relativeFrame = image.frame.offsetBy(dx: -frame.origin.x, dy: -frame.origin.y)
        let imageComponent = VVImageComponent(url: image.url, size: relativeFrame.size, cornerRadius: 4)
        return VVFrameComponent(frame: relativeFrame, child: imageComponent)
    }

    private func makeTextRunPrimitives(_ runs: [LayoutTextRun], relativeTo frame: CGRect) -> [VVTextRunPrimitive] {
        let offset = frame.origin
        return runs.compactMap { run in
            let glyphs = run.glyphs.map { glyph -> VVTextGlyph in
                let resolved = toVVTextGlyph(glyph)
                return VVTextGlyph(
                    glyphID: resolved.glyphID,
                    position: CGPoint(x: resolved.position.x - offset.x, y: resolved.position.y - offset.y),
                    size: resolved.size,
                    color: resolved.color,
                    fontVariant: resolved.fontVariant,
                    fontSize: resolved.fontSize,
                    fontName: resolved.fontName,
                    stringIndex: resolved.stringIndex
                )
            }
            guard !glyphs.isEmpty else { return nil }
            let lineBounds = runLineBounds(run)?.offsetBy(dx: -offset.x, dy: -offset.y)
            let renderedBounds = (runRenderedBounds(run) ?? runBounds(run))?.offsetBy(dx: -offset.x, dy: -offset.y)
            return VVTextRunPrimitive(
                glyphs: glyphs,
                style: toVVTextRunStyle(run.style),
                lineBounds: lineBounds,
                runBounds: renderedBounds ?? lineBounds,
                position: CGPoint(x: run.position.x - offset.x, y: run.position.y - offset.y),
                fontSize: run.glyphs.first?.fontSize ?? layoutEngine.baseFontSize
            )
        }
    }

    private func localizedNode(from scene: VVScene, blockFrame: CGRect) -> VVNode {
        let baseNode = VVNode.fromScene(scene)
        guard blockFrame.origin != .zero else { return baseNode }
        return VVNode(offset: CGPoint(x: -blockFrame.origin.x, y: -blockFrame.origin.y), children: [baseNode])
    }

    private func appendBlock(_ block: LayoutBlock, to builder: inout VVSceneBuilder) {
        switch block.content {
        case .text(let runs):
            appendTextRuns(runs, to: &builder)

        case .inline(let runs, let images):
            appendInlineImages(images, to: &builder)
            appendTextRuns(runs, to: &builder)

        case .code(let code, let language, let lines):
            appendCodeBlockPrimitives(blockId: block.blockId, code: code, language: language, lines: lines, frame: block.frame, to: &builder)

        case .listItems(let items):
            for item in items {
                appendListItem(item, to: &builder)
            }

        case .quoteBlocks(let nestedBlocks):
            if case .alert(let kind) = block.blockType {
                appendAlertPrimitives(frame: block.frame, kind: kind, to: &builder)
            } else {
                let border = VVBlockQuoteBorderPrimitive(
                    frame: block.frame,
                    color: theme.blockQuoteBorderColor,
                    borderWidth: CGFloat(theme.blockQuoteBorderWidth)
                )
                builder.add(kind: .blockQuoteBorder(border))
            }
            for nested in nestedBlocks {
                appendBlock(nested, to: &builder)
            }

        case .tableRows(let rows):
            appendTablePrimitives(frame: block.frame, rows: rows, to: &builder)
            builder.withClip(block.frame) { builder in
                for row in rows {
                    for cell in row.cells {
                        appendInlineImages(cell.inlineImages, to: &builder)
                        appendTextRuns(cell.textRuns, to: &builder)
                    }
                }
            }

        case .definitionList(let items):
            for item in items {
                appendInlineImages(item.termImages, to: &builder)
                appendTextRuns(item.termRuns, to: &builder)
                for (index, runs) in item.definitionRuns.enumerated() {
                    let images = index < item.definitionImages.count ? item.definitionImages[index] : []
                    appendInlineImages(images, to: &builder)
                    appendTextRuns(runs, to: &builder)
                }
            }

        case .abbreviationList(let items):
            for item in items {
                appendInlineImages(item.images, to: &builder)
                appendTextRuns(item.runs, to: &builder)
            }

        case .thematicBreak:
            let line = VVLinePrimitive(
                start: CGPoint(x: block.frame.origin.x + 20, y: block.frame.midY),
                end: CGPoint(x: block.frame.maxX - 20, y: block.frame.midY),
                thickness: 2,
                color: theme.thematicBreakColor
            )
            builder.add(kind: .line(line))

        case .math(let latex, let defaultRuns):
            appendMathBlockPrimitives(blockId: block.blockId, latex: latex, runs: defaultRuns, frame: block.frame, to: &builder)

        case .image(let url, _, _):
            let image = VVImagePrimitive(url: url, frame: block.frame, cornerRadius: 4)
            builder.add(kind: .image(image))

        case .imageRow(let images):
            appendInlineImages(images, to: &builder)

        case .mermaid(let diagram):
            appendMermaidPrimitives(diagram, to: &builder)
        }
    }

    private func appendTextRuns(_ runs: [LayoutTextRun], to builder: inout VVSceneBuilder) {
        for run in runs {
            let glyphs = run.glyphs.map { toVVTextGlyph($0) }
            guard !glyphs.isEmpty else { continue }
            let lineBounds = runLineBounds(run)
            let renderedBounds = runRenderedBounds(run) ?? runBounds(run)
            let primitive = VVTextRunPrimitive(
                glyphs: glyphs,
                style: toVVTextRunStyle(run.style),
                lineBounds: lineBounds,
                runBounds: renderedBounds ?? lineBounds,
                position: run.position,
                fontSize: run.glyphs.first?.fontSize ?? layoutEngine.baseFontSize
            )
            builder.add(kind: .textRun(primitive))
        }
    }

    private func appendInlineImages(_ images: [LayoutInlineImage], to builder: inout VVSceneBuilder) {
        for image in images {
            let primitive = VVImagePrimitive(url: image.url, frame: image.frame, cornerRadius: 4)
            builder.add(kind: .image(primitive))
        }
    }

    private func appendListItem(_ item: LayoutListItem, to builder: inout VVSceneBuilder) {
        var lineHeight = layoutEngine.currentLineHeight
        var bulletCenterY: CGFloat? = nil
        if let sample = item.contentRuns.first, let metrics = lineMetrics(sample) {
            lineHeight = metrics.lineHeight
            bulletCenterY = metrics.lineY + metrics.lineHeight * 0.5
        } else if let sample = item.contentRuns.first, let lineRect = runLineBounds(sample) {
            lineHeight = lineRect.height
            bulletCenterY = lineRect.midY
        } else {
            let ascent = layoutEngine.currentAscent
            bulletCenterY = item.bulletPosition.y - ascent + lineHeight * 0.5
        }
        let resolvedCenterY = bulletCenterY ?? item.bulletPosition.y
        let bulletSize = max(6, min(10, lineHeight * 0.45))
        let bulletY = resolvedCenterY - bulletSize * 0.5
        let bulletColor = theme.listBulletColor

        switch item.bulletType {
        case .disc:
            let bullet = VVBulletPrimitive(position: CGPoint(x: item.bulletPosition.x, y: bulletY), size: bulletSize, color: bulletColor, type: .disc)
            builder.add(kind: .bullet(bullet))
        case .circle:
            let bullet = VVBulletPrimitive(position: CGPoint(x: item.bulletPosition.x, y: bulletY), size: bulletSize, color: bulletColor, type: .circle)
            builder.add(kind: .bullet(bullet))
        case .square:
            let bullet = VVBulletPrimitive(position: CGPoint(x: item.bulletPosition.x, y: bulletY), size: bulletSize, color: bulletColor, type: .square)
            builder.add(kind: .bullet(bullet))
        case .number(let num):
            let glyphs = layoutEngine.layoutNumberGlyphs(num, at: item.bulletPosition, color: bulletColor)
            if !glyphs.isEmpty {
                let run = VVTextRunPrimitive(
                    glyphs: glyphs.map { toVVTextGlyph($0) },
                    style: VVTextRunStyle(color: bulletColor),
                    lineBounds: nil,
                    runBounds: nil,
                    position: item.bulletPosition,
                    fontSize: glyphs.first?.fontSize ?? layoutEngine.baseFontSize
                )
                builder.add(kind: .textRun(run))
            }
        case .checkboxChecked:
            let bullet = VVBulletPrimitive(position: CGPoint(x: item.bulletPosition.x, y: bulletY), size: bulletSize, color: bulletColor, type: .checkbox(true))
            builder.add(kind: .bullet(bullet))
        case .checkboxUnchecked:
            let bullet = VVBulletPrimitive(position: CGPoint(x: item.bulletPosition.x, y: bulletY), size: bulletSize, color: bulletColor, type: .checkbox(false))
            builder.add(kind: .bullet(bullet))
        }

        appendInlineImages(item.inlineImages, to: &builder)
        appendTextRuns(item.contentRuns, to: &builder)

        for child in item.children {
            appendListItem(child, to: &builder)
        }
    }

    private func appendAlertPrimitives(frame: CGRect, kind: MarkdownAlertKind, to builder: inout VVSceneBuilder) {
        let colors = alertColors(for: kind)
        let inset: CGFloat = 0.5
        let background = VVQuadPrimitive(
            frame: CGRect(x: frame.origin.x + inset, y: frame.origin.y + inset, width: frame.width - inset * 2, height: frame.height - inset * 2),
            color: colors.background,
            cornerRadius: 6
        )
        builder.add(kind: .quad(background))

        let borderWidth = max(2, CGFloat(theme.blockQuoteBorderWidth))
        let border = VVBlockQuoteBorderPrimitive(
            frame: frame,
            color: colors.border,
            borderWidth: borderWidth
        )
        builder.add(kind: .blockQuoteBorder(border))

        let label = kind.title.uppercased()
        let paddingX: CGFloat = 12
        let paddingY: CGFloat = 8
        let baselineY = frame.origin.y + paddingY + layoutEngine.currentAscent
        let glyphs = layoutEngine.layoutTextGlyphs(label, variant: .semibold, at: CGPoint(x: frame.origin.x + paddingX, y: baselineY), color: colors.text)
        let primitive = VVTextRunPrimitive(
            glyphs: glyphs.map { toVVTextGlyph($0) },
            style: VVTextRunStyle(color: colors.text),
            lineBounds: nil,
            runBounds: nil,
            position: CGPoint(x: frame.origin.x + paddingX, y: baselineY),
            fontSize: glyphs.first?.fontSize ?? layoutEngine.baseFontSize
        )
        builder.add(kind: .textRun(primitive))
    }

    private func appendCodeBlockPrimitives(
        blockId: String,
        code: String,
        language: String?,
        lines: [LayoutCodeLine],
        frame: CGRect,
        to builder: inout VVSceneBuilder
    ) {
        let padding = CGFloat(theme.codeBlockPadding)
        let headerHeight = CGFloat(theme.codeBlockHeaderHeight)
        let borderWidth = CGFloat(theme.codeBorderWidth)
        let cornerRadius = CGFloat(theme.codeBlockCornerRadius)

        if borderWidth > 0 {
            let borderQuad = VVQuadPrimitive(frame: frame, color: theme.codeBorderColor, cornerRadius: cornerRadius)
            builder.add(kind: .quad(borderQuad))
        }

        let innerFrame = frame.insetBy(dx: borderWidth, dy: borderWidth)
        let innerRadius = max(0, cornerRadius - borderWidth)
        let fillQuad = VVQuadPrimitive(frame: innerFrame, color: theme.codeBackgroundColor, cornerRadius: innerRadius)
        builder.add(kind: .quad(fillQuad))

        if headerHeight > 0 {
            let headerFrame = CGRect(x: innerFrame.origin.x, y: innerFrame.origin.y, width: innerFrame.width, height: min(headerHeight, innerFrame.height))
            let headerRadius = min(cornerRadius, headerFrame.height)
            let headerQuad = VVQuadPrimitive(frame: headerFrame, color: theme.codeHeaderBackgroundColor, cornerRadius: headerRadius)
            builder.add(kind: .quad(headerQuad))

            let dividerHeight = max(1, CGFloat(theme.codeHeaderDividerHeight))
            let divider = VVLinePrimitive(
                start: CGPoint(x: frame.origin.x + borderWidth, y: frame.origin.y + borderWidth + headerHeight - dividerHeight),
                end: CGPoint(x: frame.maxX - borderWidth, y: frame.origin.y + borderWidth + headerHeight - dividerHeight),
                thickness: dividerHeight,
                color: theme.codeHeaderDividerColor
            )
            builder.add(kind: .line(divider))
        }

        let highlightedLines = highlightedCodeBlocks[blockId]?.lines
        let lineCount = highlightedLines?.count ?? lines.count
        let maxLineNumber = max(highlightedLines?.map(\.lineNumber).max() ?? 0,
                                lines.map(\.lineNumber).max() ?? 0,
                                lineCount)
        let gutterWidth = codeGutterWidth(for: maxLineNumber)

        let bottomInset = max(0, cornerRadius - borderWidth)
        let gutterFrame = CGRect(
            x: innerFrame.minX,
            y: innerFrame.minY + headerHeight,
            width: gutterWidth,
            height: max(0, innerFrame.height - headerHeight - bottomInset)
        )
        let gutterQuad = VVQuadPrimitive(frame: gutterFrame, color: theme.codeGutterBackgroundColor, cornerRadius: 0)
        builder.add(VVPrimitive(kind: .quad(gutterQuad), clipRect: innerFrame))

        let dividerWidth = max(1, CGFloat(theme.codeGutterDividerWidth))
        let gutterDivider = VVLinePrimitive(
            start: CGPoint(x: gutterFrame.maxX - dividerWidth, y: gutterFrame.minY),
            end: CGPoint(x: gutterFrame.maxX - dividerWidth, y: gutterFrame.maxY),
            thickness: dividerWidth,
            color: theme.codeHeaderDividerColor
        )
        builder.add(VVPrimitive(kind: .line(gutterDivider), clipRect: innerFrame))

        if headerHeight > 0 {
            let label = (language?.isEmpty == false ? language! : "Text").uppercased()
            let lineLabel = "\(lineCount) lines"
            let paddingX: CGFloat = 12
            let labelBaselineY = frame.origin.y + borderWidth + headerHeight * 0.5 + (layoutEngine.currentAscent - layoutEngine.currentDescent) * 0.5
            let leftGlyphs = layoutEngine.layoutTextGlyphs(label, variant: .semibold, at: CGPoint(x: frame.origin.x + paddingX + borderWidth, y: labelBaselineY), color: theme.codeHeaderTextColor)
            if !leftGlyphs.isEmpty {
                let run = VVTextRunPrimitive(
                    glyphs: leftGlyphs.map { toVVTextGlyph($0) },
                    style: VVTextRunStyle(color: theme.codeHeaderTextColor),
                    position: CGPoint(x: frame.origin.x + paddingX + borderWidth, y: labelBaselineY),
                    fontSize: leftGlyphs.first?.fontSize ?? layoutEngine.baseFontSize
                )
                builder.add(kind: .textRun(run))
            }

            let rightTextWidth = layoutEngine.measureTextWidth(lineLabel, variant: .regular)
            let buttonRect = codeCopyButtonRect(for: frame, headerHeight: headerHeight)
            let rightEdge = buttonRect?.minX ?? (frame.maxX - paddingX)
            let rightX = max(frame.origin.x + paddingX, rightEdge - rightTextWidth - 12)
            let rightGlyphs = layoutEngine.layoutTextGlyphs(lineLabel, variant: .regular, at: CGPoint(x: rightX - borderWidth, y: labelBaselineY), color: theme.codeHeaderTextColor)
            if !rightGlyphs.isEmpty {
                let run = VVTextRunPrimitive(
                    glyphs: rightGlyphs.map { toVVTextGlyph($0) },
                    style: VVTextRunStyle(color: theme.codeHeaderTextColor),
                    position: CGPoint(x: rightX - borderWidth, y: labelBaselineY),
                    fontSize: rightGlyphs.first?.fontSize ?? layoutEngine.baseFontSize
                )
                builder.add(kind: .textRun(run))
            }

            appendCodeCopyButtonPrimitives(frame: frame, headerHeight: headerHeight, blockId: blockId, to: &builder)
        }

        let contentOriginX = frame.origin.x + borderWidth
        let contentOriginY = frame.origin.y + borderWidth
        let baseAscent = layoutEngine.currentAscent
        let baseDescent = layoutEngine.currentDescent
        let baseLineHeight = layoutEngine.currentLineHeight
        let extraLeading = max(0, baseLineHeight - (baseAscent + baseDescent))
        let baselineOffset = baseAscent + extraLeading * 0.5
        var clipFrame = frame.insetBy(dx: borderWidth, dy: borderWidth)
        if bottomInset > 0 {
            clipFrame.size.height = max(0, clipFrame.height - bottomInset)
        }

        if let highlighted = highlightedCodeBlocks[blockId] {
            for line in highlighted.lines {
                let lineY = contentOriginY + padding + headerHeight + baselineOffset + CGFloat(line.lineNumber - 1) * baseLineHeight
                let startX = contentOriginX + padding + gutterWidth
                appendCodeLineNumberPrimitive(line.lineNumber, at: CGPoint(x: contentOriginX, y: lineY), gutterWidth: gutterWidth, clipRect: clipFrame, to: &builder)
                var x = startX
                let tokens = line.tokens.isEmpty
                    ? [HighlightedCodeToken(text: line.text, range: NSRange(location: 0, length: line.text.utf16.count), color: theme.codeColor)]
                    : line.tokens
                for token in tokens {
                    let tokenWidth = layoutEngine.measureTextWidth(token.text, variant: .monospace)
                    let glyphs = layoutEngine.layoutCodeGlyphs(token.text, at: CGPoint(x: x, y: lineY), color: token.color)
                    if !glyphs.isEmpty {
                        let run = VVTextRunPrimitive(
                            glyphs: glyphs.map { toVVTextGlyph($0) },
                            style: VVTextRunStyle(color: token.color),
                            position: CGPoint(x: x, y: lineY),
                            fontSize: glyphs.first?.fontSize ?? layoutEngine.baseFontSize
                        )
                        builder.add(VVPrimitive(kind: .textRun(run), clipRect: clipFrame))
                    }
                    x += tokenWidth
                }
            }
        } else {
            for line in lines {
                let lineY = contentOriginY + line.yOffset
                let startX = contentOriginX + padding + gutterWidth
                appendCodeLineNumberPrimitive(line.lineNumber, at: CGPoint(x: contentOriginX, y: lineY), gutterWidth: gutterWidth, clipRect: clipFrame, to: &builder)
                var x = startX
                for token in line.tokens {
                    let tokenWidth = layoutEngine.measureTextWidth(token.text, variant: .monospace)
                    let glyphs = layoutEngine.layoutCodeGlyphs(token.text, at: CGPoint(x: x, y: lineY), color: token.color)
                    if !glyphs.isEmpty {
                        let run = VVTextRunPrimitive(
                            glyphs: glyphs.map { toVVTextGlyph($0) },
                            style: VVTextRunStyle(color: token.color),
                            position: CGPoint(x: x, y: lineY),
                            fontSize: glyphs.first?.fontSize ?? layoutEngine.baseFontSize
                        )
                        builder.add(VVPrimitive(kind: .textRun(run), clipRect: clipFrame))
                    }
                    x += tokenWidth
                }
            }
        }
    }

    private func appendCodeCopyButtonPrimitives(frame: CGRect, headerHeight: CGFloat, blockId: String, to builder: inout VVSceneBuilder) {
        let now = Date.timeIntervalSinceReferenceDate
        let isCopied = copiedBlockId == blockId && (now - copiedAt) < 1.4
        let label = isCopied ? "Copied" : "Copy"
        let textWidth = layoutEngine.measureTextWidth(label, variant: .regular)
        let horizontalPadding: CGFloat = 8
        let buttonHeight = max(16, headerHeight - 6)
        let buttonWidth = textWidth + horizontalPadding * 2

        let borderWidth = CGFloat(theme.codeBorderWidth)
        let buttonFrame = CGRect(
            x: frame.maxX - borderWidth - buttonWidth - 8,
            y: frame.origin.y + borderWidth + (headerHeight - buttonHeight) * 0.5,
            width: buttonWidth,
            height: buttonHeight
        )

        let background = isCopied
            ? SIMD4<Float>(min(1, theme.codeCopyButtonBackground.x + 0.08),
                           min(1, theme.codeCopyButtonBackground.y + 0.08),
                           min(1, theme.codeCopyButtonBackground.z + 0.08),
                           theme.codeCopyButtonBackground.w)
            : theme.codeCopyButtonBackground
        let buttonQuad = VVQuadPrimitive(frame: buttonFrame, color: background, cornerRadius: CGFloat(theme.codeCopyButtonCornerRadius))
        builder.add(kind: .quad(buttonQuad))

        let textX = buttonFrame.origin.x + horizontalPadding
        let baselineY = buttonFrame.midY + (layoutEngine.currentAscent - layoutEngine.currentDescent) * 0.5
        let glyphs = layoutEngine.layoutTextGlyphs(label, variant: .regular, at: CGPoint(x: textX, y: baselineY), color: theme.codeCopyButtonTextColor)
        if !glyphs.isEmpty {
            let run = VVTextRunPrimitive(
                glyphs: glyphs.map { toVVTextGlyph($0) },
                style: VVTextRunStyle(color: theme.codeCopyButtonTextColor),
                position: CGPoint(x: textX, y: baselineY),
                fontSize: glyphs.first?.fontSize ?? layoutEngine.baseFontSize
            )
            builder.add(kind: .textRun(run))
        }
    }

    private func appendCodeLineNumberPrimitive(_ lineNumber: Int, at position: CGPoint, gutterWidth: CGFloat, clipRect: CGRect, to builder: inout VVSceneBuilder) {
        let text = "\(lineNumber)"
        let textWidth = layoutEngine.measureTextWidth(text, variant: .monospace)
        let x = position.x + gutterWidth - textWidth - 8
        let glyphs = layoutEngine.layoutTextGlyphs(text, variant: .monospace, at: CGPoint(x: x, y: position.y), color: theme.codeGutterTextColor)
        if !glyphs.isEmpty {
            let run = VVTextRunPrimitive(
                glyphs: glyphs.map { toVVTextGlyph($0) },
                style: VVTextRunStyle(color: theme.codeGutterTextColor),
                position: CGPoint(x: x, y: position.y),
                fontSize: glyphs.first?.fontSize ?? layoutEngine.baseFontSize
            )
            builder.add(VVPrimitive(kind: .textRun(run), clipRect: clipRect))
        }
    }

    private func appendMathBlockPrimitives(
        blockId: String,
        latex: String,
        runs: [LayoutMathRun],
        frame: CGRect,
        to builder: inout VVSceneBuilder
    ) {
        let borderWidth = CGFloat(theme.codeBorderWidth)
        let cornerRadius = CGFloat(theme.codeBlockCornerRadius)
        if borderWidth > 0 {
            let borderQuad = VVQuadPrimitive(frame: frame, color: theme.codeBorderColor, cornerRadius: cornerRadius)
            builder.add(kind: .quad(borderQuad))
        }
        let innerFrame = frame.insetBy(dx: borderWidth, dy: borderWidth)
        let innerRadius = max(0, cornerRadius - borderWidth)
        let fillQuad = VVQuadPrimitive(frame: innerFrame, color: theme.codeBackgroundColor, cornerRadius: innerRadius)
        builder.add(kind: .quad(fillQuad))

        let clipInset = max(borderWidth + 1.0, CGFloat(theme.codeBlockPadding) * 0.75)
        let clipFrame = frame.insetBy(dx: clipInset, dy: clipInset)

        for run in runs {
            let glyphs = layoutEngine.layoutMathGlyphs(run.text, at: run.position, fontSize: run.fontSize, color: run.color, isItalic: run.isItalic)
            guard !glyphs.isEmpty else { continue }
            let primitive = VVTextRunPrimitive(
                glyphs: glyphs.map { toVVTextGlyph($0) },
                style: VVTextRunStyle(color: run.color),
                position: run.position,
                fontSize: run.fontSize
            )
            builder.add(VVPrimitive(kind: .textRun(primitive), clipRect: clipFrame))
        }
    }

    private func appendMermaidPrimitives(_ diagram: LayoutMermaidDiagram, to builder: inout VVSceneBuilder) {
        let background = VVQuadPrimitive(frame: diagram.frame, color: theme.diagramBackground, cornerRadius: 8)
        builder.add(kind: .quad(background))

        for slice in diagram.pieSlices {
            let primitive = VVPieSlicePrimitive(
                center: slice.center,
                radius: slice.radius,
                startAngle: slice.startAngle,
                endAngle: slice.endAngle,
                color: slice.color
            )
            builder.add(kind: .pieSlice(primitive))
        }

        for bg in diagram.backgrounds {
            let quad = VVQuadPrimitive(frame: bg.frame, color: bg.fillColor, cornerRadius: bg.cornerRadius)
            builder.add(kind: .quad(quad))
            if let borderColor = bg.borderColor {
                let top = VVTableLinePrimitive(
                    start: CGPoint(x: bg.frame.minX, y: bg.frame.minY),
                    end: CGPoint(x: bg.frame.maxX, y: bg.frame.minY),
                    color: borderColor,
                    lineWidth: 1
                )
                let bottom = VVTableLinePrimitive(
                    start: CGPoint(x: bg.frame.minX, y: bg.frame.maxY - 1),
                    end: CGPoint(x: bg.frame.maxX, y: bg.frame.maxY - 1),
                    color: borderColor,
                    lineWidth: 1
                )
                let left = VVTableLinePrimitive(
                    start: CGPoint(x: bg.frame.minX, y: bg.frame.minY),
                    end: CGPoint(x: bg.frame.minX, y: bg.frame.maxY),
                    color: borderColor,
                    lineWidth: 1
                )
                let right = VVTableLinePrimitive(
                    start: CGPoint(x: bg.frame.maxX - 1, y: bg.frame.minY),
                    end: CGPoint(x: bg.frame.maxX - 1, y: bg.frame.maxY),
                    color: borderColor,
                    lineWidth: 1
                )
                builder.add(kind: .tableLine(top))
                builder.add(kind: .tableLine(bottom))
                builder.add(kind: .tableLine(left))
                builder.add(kind: .tableLine(right))
            }
        }

        for line in diagram.lines {
            if line.isDashed {
                let segments = makeDashedLineSegments(line)
                for segment in segments {
                    builder.add(kind: .tableLine(segment))
                }
            } else {
                let primitive = VVTableLinePrimitive(start: line.start, end: line.end, color: line.color, lineWidth: CGFloat(line.width))
                builder.add(kind: .tableLine(primitive))
            }
        }

        for node in diagram.nodes {
            let cornerRadius: CGFloat
            switch node.shape {
            case .round, .circle:
                cornerRadius = node.frame.height * 0.5
            case .rect:
                cornerRadius = 6
            }
            let borderQuad = VVQuadPrimitive(frame: node.frame, color: node.borderColor, cornerRadius: cornerRadius)
            builder.add(kind: .quad(borderQuad))
            let inset: CGFloat = 1
            let innerFrame = node.frame.insetBy(dx: inset, dy: inset)
            let innerRadius = max(0, cornerRadius - inset)
            let fillQuad = VVQuadPrimitive(frame: innerFrame, color: node.fillColor, cornerRadius: innerRadius)
            builder.add(kind: .quad(fillQuad))
            appendTextRuns(node.labelRuns, to: &builder)
        }

        appendTextRuns(diagram.labels, to: &builder)
    }

    private func makeDashedLineSegments(_ line: LayoutMermaidLine) -> [VVTableLinePrimitive] {
        let dashLength: CGFloat = 6
        let gapLength: CGFloat = 4
        let dx = line.end.x - line.start.x
        let dy = line.end.y - line.start.y
        let length = max(1, hypot(dx, dy))
        let ux = dx / length
        let uy = dy / length
        var segments: [VVTableLinePrimitive] = []
        var current: CGFloat = 0
        while current < length {
            let segmentLength = min(dashLength, length - current)
            let start = CGPoint(x: line.start.x + ux * current, y: line.start.y + uy * current)
            let end = CGPoint(x: line.start.x + ux * (current + segmentLength), y: line.start.y + uy * (current + segmentLength))
            segments.append(VVTableLinePrimitive(start: start, end: end, color: line.color, lineWidth: CGFloat(line.width)))
            current += dashLength + gapLength
        }
        return segments
    }

    private func appendTablePrimitives(frame: CGRect, rows: [LayoutTableRow], to builder: inout VVSceneBuilder) {
        let borderWidth: CGFloat = 1
        let inset = borderWidth + 1
        let innerFrame = frame.insetBy(dx: inset, dy: inset)
        let backgroundClip = innerFrame
        let maxRadius = min(innerFrame.width, innerFrame.height) * 0.5
        let backgroundRadius = max(0, min(CGFloat(theme.tableCornerRadius), maxRadius) - inset)
        let background = VVQuadPrimitive(
            frame: innerFrame,
            color: theme.tableBackground,
            cornerRadius: backgroundRadius
        )
        builder.add(VVPrimitive(kind: .quad(background), clipRect: backgroundClip))

        let topY = rows.map { $0.frame.minY }.min() ?? 0
        for row in rows where row.isHeader {
            let rowFrame = row.frame.insetBy(dx: inset, dy: inset).intersection(innerFrame)
            let isTopRow = rowFrame.minY <= topY + inset + 0.5
            let radius: CGFloat = isTopRow ? backgroundRadius : 0
            let headerQuad = VVQuadPrimitive(frame: rowFrame, color: theme.tableHeaderBackground, cornerRadius: radius)
            builder.add(VVPrimitive(kind: .quad(headerQuad), clipRect: backgroundClip))
        }

        var lines: [VVPrimitive] = []
        let cornerRadius = CGFloat(theme.tableCornerRadius)
        var y = frame.origin.y
        for (rowIndex, row) in rows.enumerated() {
            let isTop = rowIndex == 0
            let startX = frame.origin.x + (isTop ? cornerRadius : 0)
            let endX = frame.maxX - (isTop ? cornerRadius : 0)
            lines.append(VVPrimitive(kind: .tableLine(VVTableLinePrimitive(
                start: CGPoint(x: startX, y: y),
                end: CGPoint(x: endX, y: y),
                color: theme.tableBorderColor,
                lineWidth: 1
            ))))
            y += row.frame.height
        }
        let bottomStartX = frame.origin.x + cornerRadius
        let bottomEndX = frame.maxX - cornerRadius
        lines.append(VVPrimitive(kind: .tableLine(VVTableLinePrimitive(
            start: CGPoint(x: bottomStartX, y: y),
            end: CGPoint(x: bottomEndX, y: y),
            color: theme.tableBorderColor,
            lineWidth: 1
        ))))

        if let firstRow = rows.first {
            var x = frame.origin.x
            for cell in firstRow.cells {
                let isLeft = x == frame.origin.x
                let startY = frame.origin.y + (isLeft ? cornerRadius : 0)
                let endY = frame.maxY - (isLeft ? cornerRadius : 0)
                lines.append(VVPrimitive(kind: .tableLine(VVTableLinePrimitive(
                    start: CGPoint(x: x, y: startY),
                    end: CGPoint(x: x, y: endY),
                    color: theme.tableBorderColor,
                    lineWidth: 1
                ))))
                x += cell.frame.width
            }
            let startY = frame.origin.y + cornerRadius
            let endY = frame.maxY - cornerRadius
            lines.append(VVPrimitive(kind: .tableLine(VVTableLinePrimitive(
                start: CGPoint(x: x, y: startY),
                end: CGPoint(x: x, y: endY),
                color: theme.tableBorderColor,
                lineWidth: 1
            ))))
        }

        for line in lines {
            builder.add(line)
        }
    }

    private func codeCopyButtonRect(for frame: CGRect, headerHeight: CGFloat) -> CGRect? {
        let labelWidth = max(
            layoutEngine.measureTextWidth("Copy", variant: .regular),
            layoutEngine.measureTextWidth("Copied", variant: .regular)
        )
        let horizontalPadding: CGFloat = 8
        let buttonHeight = max(16, headerHeight - 6)
        let buttonWidth = labelWidth + horizontalPadding * 2
        let borderWidth = CGFloat(theme.codeBorderWidth)

        return CGRect(
            x: frame.maxX - borderWidth - buttonWidth - 8,
            y: frame.origin.y + borderWidth + (headerHeight - buttonHeight) * 0.5,
            width: buttonWidth,
            height: buttonHeight
        )
    }

    private func codeGutterWidth(for maxLineNumber: Int) -> CGFloat {
        let digits = max(1, String(maxLineNumber).count)
        let charWidth = layoutEngine.measureTextWidth("8", variant: .monospace)
        return max(30, (CGFloat(digits) + 1.2) * charWidth)
    }

    private func alertColors(for kind: MarkdownAlertKind) -> (background: SIMD4<Float>, border: SIMD4<Float>, text: SIMD4<Float>) {
        let base: SIMD4<Float>
        switch kind {
        case .note:
            base = SIMD4(0.36, 0.62, 1.0, 1.0)
        case .tip:
            base = SIMD4(0.33, 0.78, 0.45, 1.0)
        case .important:
            base = SIMD4(0.73, 0.55, 0.94, 1.0)
        case .warning:
            base = SIMD4(0.94, 0.66, 0.25, 1.0)
        case .caution:
            base = SIMD4(0.92, 0.35, 0.35, 1.0)
        }
        let background = SIMD4(base.x * 0.18, base.y * 0.18, base.z * 0.18, 1.0)
        return (background, base, base)
    }

    private func toVVFontVariant(_ variant: FontVariant) -> VVFontVariant {
        switch variant {
        case .regular: return .regular
        case .semibold: return .semibold
        case .semiboldItalic: return .semiboldItalic
        case .bold: return .bold
        case .italic: return .italic
        case .boldItalic: return .boldItalic
        case .monospace: return .monospace
        case .emoji: return .emoji
        }
    }

    private func toVVTextRunStyle(_ style: TextRunStyle) -> VVTextRunStyle {
        VVTextRunStyle(
            isStrikethrough: style.isStrikethrough,
            isLink: style.isLink,
            linkURL: style.linkURL,
            color: style.color
        )
    }

    private func toVVTextGlyph(_ glyph: LayoutGlyph) -> VVTextGlyph {
        VVTextGlyph(
            glyphID: UInt16(glyph.glyphID),
            position: glyph.position,
            size: glyph.size,
            color: glyph.color,
            fontVariant: toVVFontVariant(glyph.fontVariant),
            fontSize: glyph.fontSize,
            fontName: glyph.fontName,
            stringIndex: glyph.stringIndex
        )
    }
}

fileprivate struct VVMarkdownComponentFactory {
    let builder: VVMarkdownSceneBuilder

    func component(for block: LayoutBlock) -> VVComponent {
        builder.makeBlockComponent(for: block)
    }

    func applyStyleRegistry(to component: VVComponent, for block: LayoutBlock) -> VVComponent {
        builder.applyStyleRegistry(to: component, for: block)
    }
}
