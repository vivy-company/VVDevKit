import AppKit
import XCTest
@testable import VVCode
@testable import VVMarkdown
import VVMetalPrimitives

@MainActor
final class VVRenderingStressTests: XCTestCase {
    private let viewportSize = CGSize(width: 1100, height: 760)

    func testLargeMarkdownPipelineBuildsAndRendersHeadlessly() throws {
        let sample = try RenderingStressFixtures.loadMarkdownSample()
        let content = RenderingStressFixtures.repeatContent(sample, count: 28)
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
        let scrollOffsets = RenderingStressFixtures.makeScrollOffsets(totalHeight: layout.totalHeight, viewportHeight: viewportSize.height, steps: 12)

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
        let diff = RenderingStressFixtures.makeLargeUnifiedDiff(fileCount: 120, linesPerHunk: 36)
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
        let scrollOffsets = RenderingStressFixtures.makeScrollOffsets(totalHeight: result.contentHeight, viewportHeight: viewportSize.height, steps: 10)

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

    private func makeLargeSwiftSource(lineCount: Int) -> String {
        (0..<lineCount).map { index in
            "let longVariableName\(index) = [\"alpha\", \"beta\", \"gamma\", \"delta\", \"epsilon\"].map { value in value + \"_segment_\(index)_with_wrapping_pressure\" }.joined(separator: \", \")"
        }.joined(separator: "\n")
    }
}
