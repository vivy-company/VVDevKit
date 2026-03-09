import AppKit
import XCTest
@testable import VVCode
@testable import VVMarkdown
import VVMetalPrimitives

@MainActor
final class VVRenderingStressTests: XCTestCase {
    private let viewportSize = CGSize(width: 1100, height: 760)

    func testLargeMarkdownPipelineBuildsAndRendersHeadlessly() throws {
        let sample = try loadMarkdownSample()
        let content = repeatContent(sample, count: 28)
        let font = NSFont.systemFont(ofSize: 14)

        let parser = MarkdownParser()
        let document = parser.parse(content)

        let layoutEngine = MarkdownLayoutEngine(baseFont: font, theme: .dark, contentWidth: viewportSize.width)
        layoutEngine.updateImageSizeProvider { _ in CGSize(width: 88, height: 24) }
        let layout = layoutEngine.layout(document)
        let pipeline = VVMarkdownRenderPipeline(theme: .dark, layoutEngine: layoutEngine, scale: 2.0)
        let scene = pipeline.buildScene(from: layout)

        XCTAssertGreaterThan(document.blocks.count, 200)
        XCTAssertGreaterThan(layout.totalHeight, 20_000)
        XCTAssertGreaterThan(scene.primitives.count, 8_000)

        let harness = try HeadlessSceneStressHarness(baseFont: font, viewportSize: viewportSize)
        let scrollOffsets = makeScrollOffsets(totalHeight: layout.totalHeight, viewportHeight: viewportSize.height, steps: 12)

        for offset in scrollOffsets {
            autoreleasepool {
                do {
                    _ = try harness.render(scene: scene, scrollOffset: CGPoint(x: 0, y: offset))
                } catch {
                    XCTFail("Headless markdown render failed at offset \(offset): \(error)")
                }
            }
        }

        XCTAssertLessThanOrEqual(harness.pooledBufferBytes, 8 * 1024 * 1024)
        XCTAssertLessThanOrEqual(harness.pooledBufferCount, 64)
    }

    func testCodeDiffSceneBuildsAndRendersHeadlessly() throws {
        let diff = makeLargeUnifiedDiff(fileCount: 120, linesPerHunk: 36)
        let result = VVDiffInlineRenderer.renderUnified(
            unifiedDiff: diff,
            width: viewportSize.width,
            theme: .defaultDark,
            configuration: .default
        )

        XCTAssertGreaterThan(result.contentHeight, 40_000)
        XCTAssertGreaterThan(result.scene.primitives.count, 6_000)

        let harness = try HeadlessSceneStressHarness(
            baseFont: NSFont.monospacedSystemFont(ofSize: 13, weight: .regular),
            viewportSize: viewportSize
        )
        let scrollOffsets = makeScrollOffsets(totalHeight: result.contentHeight, viewportHeight: viewportSize.height, steps: 10)

        for offset in scrollOffsets {
            autoreleasepool {
                do {
                    _ = try harness.render(scene: result.scene, scrollOffset: CGPoint(x: 0, y: offset))
                } catch {
                    XCTFail("Headless diff render failed at offset \(offset): \(error)")
                }
            }
        }
    }

    func testLargeCodeLayoutEngineHandlesWrappedSourceHeadlessly() {
        let engine = TextLayoutEngine(
            font: NSFont.monospacedSystemFont(ofSize: 13, weight: .regular),
            lineHeightMultiplier: 1.4,
            scaleFactor: 2.0
        )
        let source = makeLargeSwiftSource(lineCount: 4_000)
        let lines = source.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)

        var glyphCount = 0
        var wrappedLineCount = 0
        var currentY: CGFloat = 0

        for (index, line) in lines.enumerated() {
            autoreleasepool {
                let layout = engine.layoutLine(
                    text: line,
                    lineIndex: index,
                    yOffset: currentY,
                    wrapWidth: 640,
                    coloredRanges: [],
                    defaultColor: SIMD4<Float>(repeating: 1)
                )
                glyphCount += layout.glyphs.count
                wrappedLineCount += layout.wrapCount
                currentY += layout.height
            }
        }

        XCTAssertGreaterThan(glyphCount, 120_000)
        XCTAssertGreaterThan(wrappedLineCount, lines.count)
        XCTAssertGreaterThan(currentY, 100_000)
    }

    private func loadMarkdownSample() throws -> String {
        let absolutePath = "/Users/uyakauleu/vivy/experiments/vvdevkit/test.md"
        if FileManager.default.fileExists(atPath: absolutePath) {
            return try String(contentsOfFile: absolutePath, encoding: .utf8)
        }
        guard let url = Bundle.module.url(forResource: "markdown_stress", withExtension: "md") else {
            throw XCTSkip("Missing markdown stress fixture")
        }
        return try String(contentsOf: url, encoding: .utf8)
    }

    private func repeatContent(_ content: String, count: Int) -> String {
        Array(repeating: content, count: count).joined(separator: "\n\n---\n\n")
    }

    private func makeScrollOffsets(totalHeight: CGFloat, viewportHeight: CGFloat, steps: Int) -> [CGFloat] {
        let clampedSteps = max(1, steps)
        let maxOffset = max(0, totalHeight - viewportHeight)
        guard maxOffset > 0 else { return [0] }
        let stride = maxOffset / CGFloat(clampedSteps)
        return (0...clampedSteps).map { min(maxOffset, CGFloat($0) * stride) }
    }

    private func makeLargeUnifiedDiff(fileCount: Int, linesPerHunk: Int) -> String {
        var lines: [String] = []
        lines.reserveCapacity(fileCount * (linesPerHunk * 2 + 8))

        for fileIndex in 0..<fileCount {
            lines.append("diff --git a/Sources/File\(fileIndex).swift b/Sources/File\(fileIndex).swift")
            lines.append("index 1111111..2222222 100644")
            lines.append("--- a/Sources/File\(fileIndex).swift")
            lines.append("+++ b/Sources/File\(fileIndex).swift")
            lines.append("@@ -1,\(linesPerHunk) +1,\(linesPerHunk) @@")
            for lineIndex in 0..<linesPerHunk {
                lines.append("-let removed\(fileIndex)_\(lineIndex) = \(fileIndex + lineIndex)")
                lines.append("+let added\(fileIndex)_\(lineIndex) = \"line \(fileIndex)-\(lineIndex) with a moderately long payload for wrapping checks\"")
                lines.append(" context\(fileIndex)_\(lineIndex) = added\(fileIndex)_\(lineIndex)")
            }
        }

        return lines.joined(separator: "\n")
    }

    private func makeLargeSwiftSource(lineCount: Int) -> String {
        (0..<lineCount).map { index in
            "let longVariableName\(index) = [\"alpha\", \"beta\", \"gamma\", \"delta\", \"epsilon\"].map { value in value + \"_segment_\(index)_with_wrapping_pressure\" }.joined(separator: \", \")"
        }.joined(separator: "\n")
    }
}
