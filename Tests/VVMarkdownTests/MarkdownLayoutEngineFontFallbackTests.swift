import XCTest
import CoreText
#if canImport(AppKit)
import AppKit
#endif
@testable import VVMarkdown

final class MarkdownLayoutEngineFontFallbackTests: XCTestCase {
    func testLayoutTextGlyphsPreserveFallbackRunFontNamesForCJK() throws {
        #if canImport(AppKit)
        let baseFont = NSFont.systemFont(ofSize: 15, weight: .regular)
        let text = "Status: 世界 means the fallback path is active."
        let fallbackFontNames = distinctFallbackRunFontNames(in: text, baseFont: baseFont as CTFont)

        guard !fallbackFontNames.isEmpty else {
            throw XCTSkip("CoreText did not expose a distinct CJK fallback font in this environment.")
        }

        let layoutEngine = MarkdownLayoutEngine(
            baseFont: baseFont,
            theme: .dark,
            contentWidth: 480
        )
        let glyphs = layoutEngine.layoutTextGlyphs(
            text,
            variant: .regular,
            at: CGPoint(x: 0, y: 0),
            color: SIMD4<Float>(1, 1, 1, 1)
        )
        let storedFontNames = Set(glyphs.compactMap(\.fontName))

        XCTAssertTrue(
            fallbackFontNames.isSubset(of: storedFontNames),
            "Expected fallback fonts \(fallbackFontNames) to be preserved in glyph metadata, got \(storedFontNames)."
        )
        #else
        throw XCTSkip("Fallback font regression test requires AppKit fonts.")
        #endif
    }

    func testMarkdownParagraphUsesCoreTextShapingForArabic() throws {
        #if canImport(AppKit)
        let text = "العربية: هذا سطر عربي لاختبار اتجاه النص وأشكال الحروف."
        let baseFont = NSFont.systemFont(ofSize: 15, weight: .regular)
        let parser = MarkdownParser()
        let document = parser.parse(text)
        let layoutEngine = MarkdownLayoutEngine(
            baseFont: baseFont,
            theme: .dark,
            contentWidth: 1200
        )
        let layout = layoutEngine.layout(document)
        let block = try XCTUnwrap(layout.blocks.first)

        guard case .text(let runs) = block.content else {
            XCTFail("Expected text block.")
            return
        }

        let actualGlyphIDs = runs
            .flatMap(\.glyphs)
            .map(\.glyphID)
            .filter { $0 != 0 }
        let expectedGlyphIDs = coreTextGlyphIDs(for: text, font: baseFont as CTFont)

        // Compare as sorted sets — word-by-word layout may reorder vs single CTLine,
        // but the same shaped glyphs must be produced.
        XCTAssertEqual(actualGlyphIDs.sorted(), expectedGlyphIDs.sorted())
        #else
        throw XCTSkip("Arabic shaping test requires AppKit fonts.")
        #endif
    }

    func testMultilingualListItemsDoNotCollapseOntoEachOther() throws {
        #if canImport(AppKit)
        let text = """
        - 简体中文: 你好，世界。欢迎来到 VVDevKit 聊天时间线。
        - 日本語: 日本語新段落では句読点と全角文字の見え方を確認します。
        - 한국어: 한글 조사와 받침이 자연스럽게 렌더링되는지 확인하세요.
        - العربية: هذا سطر عربي لاختبار اتجاه النص وأشكال الحروف.
        - हिन्दी: यह पंक्ति देवनागरी रेंडरिंग की जाँच के लिए है.
        """
        let parser = MarkdownParser()
        let document = parser.parse(text)
        let layoutEngine = MarkdownLayoutEngine(
            baseFont: NSFont.systemFont(ofSize: 14, weight: .regular),
            theme: .dark,
            contentWidth: 1200
        )
        let layout = layoutEngine.layout(document)
        let listBlock = try XCTUnwrap(layout.blocks.first)

        guard case .listItems(let items) = listBlock.content else {
            XCTFail("Expected list block.")
            return
        }

        let lineTops = items.compactMap { item in
            item.contentRuns.compactMap { $0.lineY }.min()
        }

        XCTAssertEqual(lineTops.count, 5)
        for (lhs, rhs) in zip(lineTops, lineTops.dropFirst()) {
            XCTAssertLessThan(lhs, rhs)
            XCTAssertGreaterThanOrEqual(rhs - lhs, layoutEngine.currentLineHeight * 0.9)
        }
        #else
        throw XCTSkip("Multilingual list layout test requires AppKit fonts.")
        #endif
    }

    #if canImport(AppKit)
    private func distinctFallbackRunFontNames(in text: String, baseFont: CTFont) -> Set<String> {
        let requestedName = CTFontCopyPostScriptName(baseFont) as String
        let attributed = NSAttributedString(
            string: text,
            attributes: [
                .font: baseFont,
                .ligature: 1
            ]
        )
        let line = CTLineCreateWithAttributedString(attributed)
        let runs = CTLineGetGlyphRuns(line) as? [CTRun] ?? []

        return runs.reduce(into: Set<String>()) { result, run in
            let attributes = CTRunGetAttributes(run) as NSDictionary
            let runFont = attributes[kCTFontAttributeName] as! CTFont
            let runName = CTFontCopyPostScriptName(runFont) as String
            let usesRequestedFont =
                runName == requestedName &&
                abs(CTFontGetSize(runFont) - CTFontGetSize(baseFont)) < 0.5

            if !usesRequestedFont && !runName.contains("Emoji") {
                // Hidden fonts are stored as family|style (not PostScript name)
                if runName.hasPrefix(".") {
                    let family = CTFontCopyFamilyName(runFont) as String
                    let style = CTFontCopyAttribute(runFont, kCTFontStyleNameAttribute) as? String ?? "Regular"
                    result.insert("\(family)|\(style)")
                } else {
                    result.insert(runName)
                }
            }
        }
    }

    private func coreTextGlyphIDs(for text: String, font: CTFont) -> [CGGlyph] {
        let attributed = NSAttributedString(
            string: text,
            attributes: [
                .font: font,
                .ligature: 1
            ]
        )
        let line = CTLineCreateWithAttributedString(attributed)
        let runs = CTLineGetGlyphRuns(line) as? [CTRun] ?? []

        return runs.flatMap { run in
            let glyphCount = CTRunGetGlyphCount(run)
            var glyphs = [CGGlyph](repeating: 0, count: glyphCount)
            CTRunGetGlyphs(run, CFRangeMake(0, glyphCount), &glyphs)
            return glyphs.filter { $0 != 0 }
        }
    }
    #endif
}
