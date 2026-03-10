import AppKit
import XCTest
@testable import VVCode

@MainActor
final class VVDiffViewPerformanceTests: XCTestCase {
    func testHeavySplitDiffHighlightTargetStaysViewportLocal() {
        var configuration = VVConfiguration.default
        configuration.font = NSFont.monospacedSystemFont(ofSize: 13, weight: .regular)

        let diff = makeLargeUnifiedDiff(fileCount: 96, linesPerHunk: 30)
        let topMetrics = VVDiffViewDebug.makeMetrics(
            unifiedDiff: diff,
            style: .sideBySide,
            configuration: configuration,
            viewportSize: CGSize(width: 1100, height: 760),
            scrollOffsetY: 0
        )
        let midMetrics = VVDiffViewDebug.makeMetrics(
            unifiedDiff: diff,
            style: .sideBySide,
            configuration: configuration,
            viewportSize: CGSize(width: 1100, height: 760),
            scrollOffsetY: max(0, topMetrics.contentHeight * 0.45)
        )

        XCTAssertLessThanOrEqual(topMetrics.desiredHighlightRange.count, 320)
        XCTAssertLessThanOrEqual(midMetrics.desiredHighlightRange.count, 320)
        XCTAssertGreaterThan(midMetrics.desiredHighlightRange.lowerBound, 0)
        XCTAssertLessThan(midMetrics.desiredHighlightRange.upperBound, midMetrics.codeRowCount)
    }

    func testHeavySplitDiffRowGeometryDoesNotRetainWrappedStrings() {
        var configuration = VVConfiguration.default
        configuration.font = NSFont.monospacedSystemFont(ofSize: 13, weight: .regular)

        let diff = makeLargeUnifiedDiff(fileCount: 96, linesPerHunk: 30)
        let metrics = VVDiffViewDebug.makeMetrics(
            unifiedDiff: diff,
            style: .sideBySide,
            configuration: configuration,
            viewportSize: CGSize(width: 1100, height: 760),
            scrollOffsetY: 0
        )

        XCTAssertEqual(
            metrics.storedTextGeometryCount,
            0,
            "Row geometry should keep offsets/lengths only, not retain wrapped strings for every visual line."
        )
        XCTAssertEqual(metrics.storedTextCharacterCount, 0)
    }

    func testHeavySplitDiffViewportSceneWindowCoversVisibleBlocks() {
        var configuration = VVConfiguration.default
        configuration.font = NSFont.monospacedSystemFont(ofSize: 13, weight: .regular)

        let diff = makeLargeUnifiedDiff(fileCount: 96, linesPerHunk: 30)
        let topMetrics = VVDiffViewDebug.makeMetrics(
            unifiedDiff: diff,
            style: .sideBySide,
            configuration: configuration,
            viewportSize: CGSize(width: 1100, height: 760),
            scrollOffsetY: 0
        )
        let midMetrics = VVDiffViewDebug.makeMetrics(
            unifiedDiff: diff,
            style: .sideBySide,
            configuration: configuration,
            viewportSize: CGSize(width: 1100, height: 760),
            scrollOffsetY: max(0, topMetrics.contentHeight * 0.45)
        )
        let deepMetrics = VVDiffViewDebug.makeMetrics(
            unifiedDiff: diff,
            style: .sideBySide,
            configuration: configuration,
            viewportSize: CGSize(width: 1100, height: 760),
            scrollOffsetY: max(0, topMetrics.contentHeight * 0.82)
        )

        for metrics in [topMetrics, midMetrics, deepMetrics] {
            XCTAssertTrue(metrics.sceneCoversVisibleBlocks)
            XCTAssertGreaterThan(metrics.cachedScenePrimitiveCount, 0)
            XCTAssertLessThan(metrics.cachedSceneBlockRange.count, metrics.totalDisplayBlockCount)
        }
    }

    func testHeavySplitDiffRowGeometryIsWindowed() {
        var configuration = VVConfiguration.default
        configuration.font = NSFont.monospacedSystemFont(ofSize: 13, weight: .regular)

        let diff = makeLargeUnifiedDiff(fileCount: 96, linesPerHunk: 30)
        let topMetrics = VVDiffViewDebug.makeMetrics(
            unifiedDiff: diff,
            style: .sideBySide,
            configuration: configuration,
            viewportSize: CGSize(width: 1100, height: 760),
            scrollOffsetY: 0
        )
        let deepMetrics = VVDiffViewDebug.makeMetrics(
            unifiedDiff: diff,
            style: .sideBySide,
            configuration: configuration,
            viewportSize: CGSize(width: 1100, height: 760),
            scrollOffsetY: max(0, topMetrics.contentHeight * 0.8)
        )

        for metrics in [topMetrics, deepMetrics] {
            XCTAssertGreaterThan(metrics.totalVisualLineCount, 0)
            XCTAssertLessThan(
                metrics.rowGeometryCount,
                metrics.totalVisualLineCount,
                "Visible row geometry should be materialized as a window, not the full diff."
            )
        }
    }

    private func makeLargeUnifiedDiff(fileCount: Int, linesPerHunk: Int) -> String {
        var lines: [String] = []
        lines.reserveCapacity(fileCount * (linesPerHunk * 3 + 6))

        for fileIndex in 0..<fileCount {
            let fileName = "Sources/Benchmark/File\(fileIndex).swift"
            let oldHash = String(format: "%07x", fileIndex + 1)
            let newHash = String(format: "%07x", fileIndex + 2)
            lines.append("diff --git a/\(fileName) b/\(fileName)")
            lines.append("index \(oldHash)..\(newHash) 100644")
            lines.append("--- a/\(fileName)")
            lines.append("+++ b/\(fileName)")
            lines.append("@@ -1,\(linesPerHunk) +1,\(linesPerHunk) @@ struct Bench\(fileIndex) {")

            for lineIndex in 0..<linesPerHunk {
                lines.append(" let context\(fileIndex)_\(lineIndex) = metrics[\(lineIndex)]")
                lines.append("-private let removed\(fileIndex)_\(lineIndex) = LegacyRenderer.render(id: \(fileIndex), line: \(lineIndex), isEnabled: false) // legacy")
                lines.append("+let added\(fileIndex)_\(lineIndex): String? = DiffRenderer.render(id: \(fileIndex), line: \(lineIndex), theme: .dark, isEnabled: true) ?? \"fallback-\\\\(lineIndex)\"")
            }
        }

        return lines.joined(separator: "\n")
    }
}
