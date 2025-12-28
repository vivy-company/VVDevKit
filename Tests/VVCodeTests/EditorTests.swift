import XCTest
import AppKit
@testable import VVCode
@testable import VVCodeCore

@MainActor
final class EditorTests: XCTestCase {

    // MARK: - VVDocument Tests

    func testDocumentInit() {
        let doc = VVDocument(text: "Hello World")
        XCTAssertEqual(doc.text, "Hello World")
        XCTAssertNil(doc.language)
        XCTAssertNil(doc.fileURL)
        XCTAssertFalse(doc.isDirty)
    }

    func testDocumentWithLanguage() {
        let doc = VVDocument(text: "let x = 1", language: .swift)
        XCTAssertEqual(doc.language, .swift)
    }

    func testDocumentTextChange() {
        let doc = VVDocument(text: "Initial")
        doc.text = "Changed"
        XCTAssertEqual(doc.text, "Changed")
        XCTAssertTrue(doc.isDirty)
    }

    func testDocumentLineCount() {
        let doc = VVDocument(text: "Line 1\nLine 2\nLine 3")
        XCTAssertEqual(doc.lineCount, 3)
    }

    func testDocumentEmptyLineCount() {
        let doc = VVDocument(text: "")
        XCTAssertEqual(doc.lineCount, 1)
    }

    // MARK: - VVConfiguration Tests

    func testConfigurationDefault() {
        let config = VVConfiguration.default
        XCTAssertTrue(config.showLineNumbers)
        XCTAssertTrue(config.showGutter)
        XCTAssertFalse(config.wrapLines)
        XCTAssertEqual(config.tabWidth, 4)
    }

    func testConfigurationBuilder() {
        let config = VVConfiguration.default
            .with(tabWidth: 2)
            .with(wrapLines: true)
            .with(showLineNumbers: false)

        XCTAssertEqual(config.tabWidth, 2)
        XCTAssertTrue(config.wrapLines)
        XCTAssertFalse(config.showLineNumbers)
    }

    func testConfigurationEquality() {
        let config1 = VVConfiguration.default
        let config2 = VVConfiguration.default
        XCTAssertEqual(config1, config2)

        let config3 = config1.with(tabWidth: 8)
        XCTAssertNotEqual(config1, config3)
    }

    // MARK: - VVTheme Tests

    func testThemeDefault() {
        let dark = VVTheme.defaultDark
        let light = VVTheme.defaultLight

        XCTAssertNotEqual(dark, light)
    }

    func testThemeHashable() {
        let themes: Set<VVTheme> = [.defaultDark, .defaultLight]
        XCTAssertEqual(themes.count, 2)
    }

    // MARK: - VVLanguage Tests

    func testLanguageDetection() {
        XCTAssertEqual(VVLanguage.detect(from: URL(fileURLWithPath: "/test.swift")), .swift)
        XCTAssertEqual(VVLanguage.detect(from: URL(fileURLWithPath: "/test.rs")), .rust)
        XCTAssertEqual(VVLanguage.detect(from: URL(fileURLWithPath: "/test.py")), .python)
        XCTAssertEqual(VVLanguage.detect(from: URL(fileURLWithPath: "/test.ts")), .typescript)
        XCTAssertEqual(VVLanguage.detect(from: URL(fileURLWithPath: "/test.js")), .javascript)
        XCTAssertEqual(VVLanguage.detect(from: URL(fileURLWithPath: "/test.json")), .json)
        XCTAssertEqual(VVLanguage.detect(from: URL(fileURLWithPath: "/Dockerfile")), .dockerfile)
        XCTAssertNil(VVLanguage.detect(from: URL(fileURLWithPath: "/test.unknown")))
    }

    func testLanguageProperties() {
        XCTAssertEqual(VVLanguage.swift.identifier, "swift")
        XCTAssertEqual(VVLanguage.swift.displayName, "Swift")
        XCTAssertTrue(VVLanguage.swift.fileExtensions.contains("swift"))
    }

    func testAllLanguages() {
        XCTAssertEqual(VVLanguage.allLanguages.count, 17)
        XCTAssertTrue(VVLanguage.allLanguages.contains(.swift))
        XCTAssertTrue(VVLanguage.allLanguages.contains(.rust))
        XCTAssertTrue(VVLanguage.allLanguages.contains(.python))
    }

    // MARK: - VVEditorContainerView Tests

    func testEditorContainerInit() {
        let editor = VVEditorContainerView(
            frame: NSRect(x: 0, y: 0, width: 800, height: 600),
            configuration: .default,
            theme: .defaultDark
        )
        XCTAssertNotNil(editor)
        XCTAssertEqual(editor.text, "")
    }

    func testEditorSetText() {
        let editor = VVEditorContainerView(
            frame: NSRect(x: 0, y: 0, width: 800, height: 600),
            configuration: .default,
            theme: .defaultDark
        )

        editor.setText("Hello World")
        XCTAssertEqual(editor.text, "Hello World")
    }

    func testEditorSetMultilineText() {
        let editor = VVEditorContainerView(
            frame: NSRect(x: 0, y: 0, width: 800, height: 600),
            configuration: .default,
            theme: .defaultDark
        )

        let multilineText = """
        Line 1
        Line 2
        Line 3
        """
        editor.setText(multilineText)
        XCTAssertEqual(editor.text, multilineText)
    }

    func testEditorThemeChange() {
        let editor = VVEditorContainerView(
            frame: NSRect(x: 0, y: 0, width: 800, height: 600),
            configuration: .default,
            theme: .defaultDark
        )

        // Should not crash
        editor.setTheme(.defaultLight)
        editor.setTheme(.defaultDark)
    }

    func testEditorConfigurationChange() {
        let editor = VVEditorContainerView(
            frame: NSRect(x: 0, y: 0, width: 800, height: 600),
            configuration: .default,
            theme: .defaultDark
        )

        let newConfig = VVConfiguration.default.with(wrapLines: true)
        editor.setConfiguration(newConfig)
        // Should not crash
    }

    func testEditorLanguageChange() {
        let editor = VVEditorContainerView(
            frame: NSRect(x: 0, y: 0, width: 800, height: 600),
            configuration: .default,
            theme: .defaultDark
        )

        editor.setLanguage(.swift)
        editor.setLanguage(.rust)
        editor.setLanguage(.python)
        // Should not crash
    }

    func testEditorGitHunks() {
        let editor = VVEditorContainerView(
            frame: NSRect(x: 0, y: 0, width: 800, height: 600),
            configuration: .default,
            theme: .defaultDark
        )

        let hunks = [
            VVDiffHunk(oldStart: 1, oldCount: 3, newStart: 1, newCount: 4, changeType: .added)
        ]
        editor.setGitHunks(hunks)
        editor.setGitHunks([])
        // Should not crash
    }

    // MARK: - VVTextView Tests

    func testTextViewInit() {
        let textContainer = NSTextContainer()
        let layoutManager = VVLayoutManager()
        layoutManager.addTextContainer(textContainer)
        let textStorage = NSTextStorage()
        textStorage.addLayoutManager(layoutManager)

        let textView = VVTextView(frame: NSRect(x: 0, y: 0, width: 400, height: 300), textContainer: textContainer)
        XCTAssertNotNil(textView)
    }

    func testTextViewProperties() {
        let textContainer = NSTextContainer()
        let layoutManager = VVLayoutManager()
        layoutManager.addTextContainer(textContainer)
        let textStorage = NSTextStorage()
        textStorage.addLayoutManager(layoutManager)

        let textView = VVTextView(frame: NSRect(x: 0, y: 0, width: 400, height: 300), textContainer: textContainer)

        textView.tabWidth = 2
        XCTAssertEqual(textView.tabWidth, 2)

        textView.useSpacesForTabs = false
        XCTAssertFalse(textView.useSpacesForTabs)

        textView.autoCloseBrackets = false
        XCTAssertFalse(textView.autoCloseBrackets)
    }
}
