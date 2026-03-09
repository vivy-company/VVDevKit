import XCTest
import CoreGraphics
#if canImport(AppKit)
import AppKit
#endif
@testable import VVMarkdown

final class VVUnifiedDiffSceneRendererTests: XCTestCase {
    func testAnalyzeParsesRowsAndLineNumbers() {
        let document = VVUnifiedDiffSceneRenderer.analyze(unifiedDiff: sampleDiff)

        XCTAssertEqual(document.rows.first?.kind, .fileHeader)
        XCTAssertEqual(document.rows.first?.text, "Sources/App.swift")
        XCTAssertEqual(document.rows.first(where: { $0.kind == .hunkHeader })?.text, "struct AppView {")

        let deleted = document.rows.first(where: { $0.kind == .deleted })
        XCTAssertEqual(deleted?.oldLineNumber, 10)
        XCTAssertNil(deleted?.newLineNumber)

        let addedRows = document.rows.filter { $0.kind == .added }
        XCTAssertEqual(addedRows.count, 2)
        XCTAssertEqual(addedRows.first?.newLineNumber, 10)
        XCTAssertEqual(addedRows.last?.newLineNumber, 11)
    }

    func testAnalyzeBuildsSplitRowsWithInlineChanges() throws {
        let document = VVUnifiedDiffSceneRenderer.analyze(unifiedDiff: sampleDiff)

        let pairedChange = try XCTUnwrap(document.splitRows.first {
            $0.left?.kind == .deleted && $0.right?.kind == .added
        })

        XCTAssertEqual(pairedChange.left?.text, "    let value = oldValue")
        XCTAssertEqual(pairedChange.right?.text, "    let value = newValue")
        XCTAssertFalse(pairedChange.left?.inlineChanges.isEmpty ?? true)
        XCTAssertFalse(pairedChange.right?.inlineChanges.isEmpty ?? true)
    }

    func testCompactInlineRenderIsShorterThanFullRender() throws {
        let theme = MarkdownTheme.dark
        let font = try makeFont()

        let full = VVUnifiedDiffSceneRenderer.render(
            unifiedDiff: sampleDiff,
            width: 900,
            theme: theme,
            baseFont: font,
            style: .unifiedTable,
            options: .full
        )
        let compact = VVUnifiedDiffSceneRenderer.render(
            unifiedDiff: sampleDiff,
            width: 900,
            theme: theme,
            baseFont: font,
            style: .unifiedTable,
            options: .compactInline
        )

        XCTAssertGreaterThan(full.contentHeight, compact.contentHeight)
        XCTAssertGreaterThan(compact.contentHeight, 0)
    }

    func testSplitRenderWrapsLongLinesWithinPaneBounds() throws {
        let theme = MarkdownTheme.dark
        let font = try makeFont()
        let longToken = String(repeating: "context_0123456789 ", count: 18)
        let diff = """
        diff --git a/Sources/Feature.swift b/Sources/Feature.swift
        index 1111111..2222222 100644
        --- a/Sources/Feature.swift
        +++ b/Sources/Feature.swift
        @@ -10,2 +10,2 @@
        -let oldValue = "\(longToken)"
        +let newValue = "\(longToken)"
        """

        let result = VVUnifiedDiffSceneRenderer.render(
            unifiedDiff: diff,
            width: 960,
            theme: theme,
            baseFont: font,
            style: .split,
            options: .full
        )

        XCTAssertGreaterThan(result.contentHeight, 40)

        let paneWidth = max(CGFloat(420), floor(CGFloat(960) / 2))
        for primitive in result.scene.primitives {
            guard case let .textRun(run) = primitive.kind else { continue }
            guard let runBounds = run.runBounds else { continue }
            if runBounds.minX < paneWidth {
                XCTAssertLessThanOrEqual(runBounds.maxX, paneWidth + 1)
            } else {
                XCTAssertLessThanOrEqual(runBounds.maxX, paneWidth * 2 + 1)
            }
        }
    }

    func testRenderProfileLargeSplitDiff() throws {
        let font = try makeFont()
        let theme = MarkdownTheme.dark
        let diff = makeLargeDiff(fileCount: 24, hunksPerFile: 6)

        for _ in 0..<5 {
            _ = VVUnifiedDiffSceneRenderer.render(
                unifiedDiff: diff,
                width: 1280,
                theme: theme,
                baseFont: font,
                style: .split,
                options: .full
            )
        }

        var samples: [Double] = []
        samples.reserveCapacity(20)
        for _ in 0..<20 {
            let start = CFAbsoluteTimeGetCurrent()
            let result = VVUnifiedDiffSceneRenderer.render(
                unifiedDiff: diff,
                width: 1280,
                theme: theme,
                baseFont: font,
                style: .split,
                options: .full
            )
            samples.append((CFAbsoluteTimeGetCurrent() - start) * 1000)
            XCTAssertGreaterThan(result.contentHeight, 0)
        }

        let sorted = samples.sorted()
        let median = percentile(sorted, 0.5)
        let p95 = percentile(sorted, 0.95)
        let p99 = percentile(sorted, 0.99)

        print(String(
            format: "VVUnifiedDiffSceneRenderer split render profile: median=%.2fms p95=%.2fms p99=%.2fms samples=%d width=%d files=%d hunksPerFile=%d",
            median, p95, p99, samples.count, 1280, 24, 6
        ))

        XCTAssertLessThan(median, 80)
    }
}

private extension VVUnifiedDiffSceneRendererTests {
    var sampleDiff: String {
        """
        diff --git a/Sources/App.swift b/Sources/App.swift
        index 1111111..2222222 100644
        --- a/Sources/App.swift
        +++ b/Sources/App.swift
        @@ -10,3 +10,4 @@ struct AppView {
        -    let value = oldValue
        +    let value = newValue
        +    let subtitle = value
             return value
        """
    }

    func makeLargeDiff(fileCount: Int, hunksPerFile: Int) -> String {
        var lines: [String] = []
        for fileIndex in 0..<fileCount {
            let path = "Sources/Feature\(fileIndex).swift"
            lines.append("diff --git a/\(path) b/\(path)")
            lines.append("index 1111111..2222222 100644")
            lines.append("--- a/\(path)")
            lines.append("+++ b/\(path)")
            for hunkIndex in 0..<hunksPerFile {
                let start = hunkIndex * 8 + 1
                lines.append("@@ -\(start),4 +\(start),5 @@ func render\(hunkIndex)() {")
                lines.append("     let prefix = \"file-\(fileIndex)\"")
                lines.append("-    let value = oldValue\(hunkIndex)")
                lines.append("+    let value = newValue\(hunkIndex)")
                lines.append("+    let subtitle = value + prefix")
                lines.append("     sink(value)")
            }
        }
        return lines.joined(separator: "\n")
    }

    func percentile(_ sorted: [Double], _ fraction: Double) -> Double {
        guard !sorted.isEmpty else { return 0 }
        let index = Int((Double(sorted.count - 1) * fraction).rounded(.toNearestOrEven))
        return sorted[max(0, min(sorted.count - 1, index))]
    }

    func makeFont() throws -> VVFont {
        #if canImport(AppKit)
        return NSFont.monospacedSystemFont(ofSize: 13, weight: .regular)
        #else
        throw XCTSkip("This benchmark currently requires AppKit fonts.")
        #endif
    }
}
