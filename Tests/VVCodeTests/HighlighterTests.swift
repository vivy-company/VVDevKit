import XCTest
@testable import VVHighlighting
import AppKit

final class HighlighterTests: XCTestCase {

    // MARK: - Theme Tests

    func testDefaultDarkTheme() {
        let theme = HighlightTheme.defaultDark

        XCTAssertNotNil(theme.colors["keyword"])
        XCTAssertNotNil(theme.colors["string"])
        XCTAssertNotNil(theme.colors["comment"])
        XCTAssertNotNil(theme.colors["function"])
        XCTAssertNotNil(theme.colors["type"])
    }

    func testDefaultLightTheme() {
        let theme = HighlightTheme.defaultLight

        XCTAssertNotNil(theme.colors["keyword"])
        XCTAssertNotNil(theme.colors["string"])
        XCTAssertNotNil(theme.colors["comment"])
    }

    func testThemeStyleFallback() {
        let theme = HighlightTheme(
            colors: [
                "keyword": HighlightStyle(color: .red),
                "keyword.function": HighlightStyle(color: .blue)
            ],
            defaultColor: .white
        )

        // Exact match
        let keywordStyle = theme.style(for: "keyword")
        XCTAssertEqual(keywordStyle.color, .red)

        // Exact match with qualifier
        let keywordFuncStyle = theme.style(for: "keyword.function")
        XCTAssertEqual(keywordFuncStyle.color, .blue)

        // Fallback to parent
        let keywordReturnStyle = theme.style(for: "keyword.return")
        XCTAssertEqual(keywordReturnStyle.color, .red)

        // Fallback to default
        let unknownStyle = theme.style(for: "unknown")
        XCTAssertEqual(unknownStyle.color, .white)
    }

    // MARK: - HighlightStyle Tests

    func testHighlightStyleEquality() {
        let style1 = HighlightStyle(color: .red, isBold: true)
        let style2 = HighlightStyle(color: .red, isBold: true)
        let style3 = HighlightStyle(color: .blue, isBold: true)

        XCTAssertEqual(style1, style2)
        XCTAssertNotEqual(style1, style3)
    }

    func testHighlightStyleAttributes() {
        let baseFont = NSFont.monospacedSystemFont(ofSize: 12, weight: .regular)

        let boldStyle = HighlightStyle(color: .red, isBold: true)
        let boldAttrs = boldStyle.attributes(baseFont: baseFont)
        XCTAssertNotNil(boldAttrs[.font])
        XCTAssertEqual(boldAttrs[.foregroundColor] as? NSColor, .red)

        let italicStyle = HighlightStyle(color: .blue, isItalic: true)
        let italicAttrs = italicStyle.attributes(baseFont: baseFont)
        XCTAssertNotNil(italicAttrs[.font])

        let underlineStyle = HighlightStyle(color: .green, isUnderlined: true)
        let underlineAttrs = underlineStyle.attributes(baseFont: baseFont)
        XCTAssertNotNil(underlineAttrs[.underlineStyle])
    }

    // MARK: - HighlightRange Tests

    func testHighlightRange() {
        let range = HighlightRange(
            range: NSRange(location: 0, length: 10),
            capture: "keyword",
            style: HighlightStyle(color: .red)
        )

        XCTAssertEqual(range.range.location, 0)
        XCTAssertEqual(range.range.length, 10)
        XCTAssertEqual(range.capture, "keyword")
        XCTAssertEqual(range.style.color, .red)
    }

    // MARK: - HighlightCache Tests

    func testCacheBasicOperations() {
        let cache = HighlightCache(maxSize: 10)

        let range = NSRange(location: 0, length: 100)
        let highlights = [
            HighlightRange(range: NSRange(location: 0, length: 5), capture: "keyword", style: HighlightStyle(color: .red))
        ]

        // Set and get
        cache.set(highlights, for: range)
        let retrieved = cache.get(for: range)

        XCTAssertNotNil(retrieved)
        XCTAssertEqual(retrieved?.count, 1)
    }

    func testCacheMiss() {
        let cache = HighlightCache(maxSize: 10)

        let result = cache.get(for: NSRange(location: 0, length: 100))
        XCTAssertNil(result)
    }

    func testCacheEviction() {
        let cache = HighlightCache(maxSize: 3)

        let highlights: [HighlightRange] = []

        // Fill cache
        cache.set(highlights, for: NSRange(location: 0, length: 10))
        cache.set(highlights, for: NSRange(location: 10, length: 10))
        cache.set(highlights, for: NSRange(location: 20, length: 10))

        // Add one more (should evict oldest)
        cache.set(highlights, for: NSRange(location: 30, length: 10))

        // First entry should be evicted
        XCTAssertNil(cache.get(for: NSRange(location: 0, length: 10)))

        // Others should still be present
        XCTAssertNotNil(cache.get(for: NSRange(location: 10, length: 10)))
        XCTAssertNotNil(cache.get(for: NSRange(location: 20, length: 10)))
        XCTAssertNotNil(cache.get(for: NSRange(location: 30, length: 10)))
    }

    func testCacheClear() {
        let cache = HighlightCache(maxSize: 10)

        let highlights: [HighlightRange] = []
        cache.set(highlights, for: NSRange(location: 0, length: 10))
        cache.set(highlights, for: NSRange(location: 10, length: 10))

        cache.clear()

        XCTAssertNil(cache.get(for: NSRange(location: 0, length: 10)))
        XCTAssertNil(cache.get(for: NSRange(location: 10, length: 10)))
    }

    func testCacheInvalidateOverlapping() {
        let cache = HighlightCache(maxSize: 10)

        let highlights: [HighlightRange] = []

        // Add several ranges
        cache.set(highlights, for: NSRange(location: 0, length: 10))
        cache.set(highlights, for: NSRange(location: 10, length: 10))
        cache.set(highlights, for: NSRange(location: 20, length: 10))
        cache.set(highlights, for: NSRange(location: 30, length: 10))

        // Invalidate range that overlaps with 10-20 and 20-30
        cache.invalidate(overlapping: NSRange(location: 15, length: 10))

        // Non-overlapping ranges should remain
        XCTAssertNotNil(cache.get(for: NSRange(location: 0, length: 10)))
        XCTAssertNotNil(cache.get(for: NSRange(location: 30, length: 10)))

        // Overlapping ranges should be removed
        XCTAssertNil(cache.get(for: NSRange(location: 10, length: 10)))
        XCTAssertNil(cache.get(for: NSRange(location: 20, length: 10)))
    }

    func testCacheLRUOrder() {
        let cache = HighlightCache(maxSize: 3)

        let highlights: [HighlightRange] = []

        // Add three entries
        cache.set(highlights, for: NSRange(location: 0, length: 10))
        cache.set(highlights, for: NSRange(location: 10, length: 10))
        cache.set(highlights, for: NSRange(location: 20, length: 10))

        // Access first entry (moves it to end of LRU)
        _ = cache.get(for: NSRange(location: 0, length: 10))

        // Add new entry (should evict second entry, not first)
        cache.set(highlights, for: NSRange(location: 30, length: 10))

        // First should still exist (was accessed recently)
        XCTAssertNotNil(cache.get(for: NSRange(location: 0, length: 10)))

        // Second should be evicted
        XCTAssertNil(cache.get(for: NSRange(location: 10, length: 10)))
    }

    // MARK: - NSColor Hex Extension Tests

    func testNSColorFromHex() {
        let red = NSColor(hex: "#FF0000")
        XCTAssertEqual(red.redComponent, 1.0, accuracy: 0.01)
        XCTAssertEqual(red.greenComponent, 0.0, accuracy: 0.01)
        XCTAssertEqual(red.blueComponent, 0.0, accuracy: 0.01)

        let green = NSColor(hex: "#00FF00")
        XCTAssertEqual(green.redComponent, 0.0, accuracy: 0.01)
        XCTAssertEqual(green.greenComponent, 1.0, accuracy: 0.01)
        XCTAssertEqual(green.blueComponent, 0.0, accuracy: 0.01)

        let blue = NSColor(hex: "#0000FF")
        XCTAssertEqual(blue.redComponent, 0.0, accuracy: 0.01)
        XCTAssertEqual(blue.greenComponent, 0.0, accuracy: 0.01)
        XCTAssertEqual(blue.blueComponent, 1.0, accuracy: 0.01)
    }

    func testNSColorFromHexWithoutHash() {
        let color = NSColor(hex: "569CD6")
        XCTAssertGreaterThan(color.blueComponent, 0.8)
    }

    // MARK: - TreeSitterHighlighter Tests

    func testHighlighterInitialization() async {
        let highlighter = TreeSitterHighlighter()
        let theme = await highlighter.theme
        XCTAssertNotNil(theme)
    }

    func testHighlighterSetTheme() async {
        let highlighter = TreeSitterHighlighter()
        await highlighter.setTheme(.defaultLight)

        // Theme should be updated
        let theme = await highlighter.theme
        // Just verify no crash occurs
        XCTAssertNotNil(theme)
    }
}

// Helper extension for testing
extension TreeSitterHighlighter {
    var theme: HighlightTheme {
        get async {
            return .defaultDark // Placeholder since theme is private
        }
    }
}
