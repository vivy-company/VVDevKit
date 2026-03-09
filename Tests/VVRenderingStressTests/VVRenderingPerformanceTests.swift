import AppKit
import Darwin.Mach
import XCTest
@testable import VVCode
@testable import VVMarkdown
import VVMetalPrimitives

@MainActor
final class VVRenderingPerformanceTests: XCTestCase {
    private let viewportSize = CGSize(width: 1100, height: 760)

    func testRepeatedMarkdownBuildAndHeadlessRenderMemoryStabilizesAfterWarmup() throws {
        let sample = try RenderingStressFixtures.loadMarkdownSample()
        let content = RenderingStressFixtures.repeatContent(sample, count: 20)
        let font = NSFont.systemFont(ofSize: 14)
        let harness = try HeadlessSceneStressHarness(baseFont: font, viewportSize: viewportSize)

        let second = profileMarkdownCycle(content: content, font: font, harness: harness, label: "second")
        let third = profileMarkdownCycle(content: content, font: font, harness: harness, label: "third")

        let slack: UInt64 = 14 * 1024 * 1024
        XCTAssertLessThanOrEqual(third.retainedGrowth, second.retainedGrowth + slack)
        XCTAssertLessThanOrEqual(third.peakGrowth, second.peakGrowth + slack)
    }

    func testRepeatedUnifiedDiffBuildAndHeadlessRenderMemoryStabilizesAfterWarmup() throws {
        let diff = RenderingStressFixtures.makeLargeUnifiedDiff(fileCount: 96, linesPerHunk: 30)
        let font = NSFont.monospacedSystemFont(ofSize: 13, weight: .regular)
        let harness = try HeadlessSceneStressHarness(baseFont: font, viewportSize: viewportSize)

        let second = profileDiffCycle(diff: diff, harness: harness, label: "second")
        let third = profileDiffCycle(diff: diff, harness: harness, label: "third")

        let slack: UInt64 = 14 * 1024 * 1024
        XCTAssertLessThanOrEqual(third.retainedGrowth, second.retainedGrowth + slack)
        XCTAssertLessThanOrEqual(third.peakGrowth, second.peakGrowth + slack)
    }

    func testZBenchmarkLargeMarkdownBuildAndHeadlessRender() throws {
        let sample = try RenderingStressFixtures.loadMarkdownSample()
        let content = RenderingStressFixtures.repeatContent(sample, count: 18)
        let font = NSFont.systemFont(ofSize: 14)
        let harness = try HeadlessSceneStressHarness(baseFont: font, viewportSize: viewportSize)

        measure(metrics: [XCTClockMetric()]) {
            autoreleasepool {
                let parser = MarkdownParser()
                let document = parser.parse(content)
                let layoutEngine = MarkdownLayoutEngine(baseFont: font, theme: .dark, contentWidth: viewportSize.width)
                layoutEngine.updateImageSizeProvider { _ in CGSize(width: 88, height: 24) }
                let layout = layoutEngine.layout(document)
                let pipeline = VVMarkdownRenderPipeline(theme: .dark, layoutEngine: layoutEngine, scale: 2.0)
                let scene = pipeline.buildScene(from: layout)
                let scrollOffsets = RenderingStressFixtures.makeScrollOffsets(totalHeight: layout.totalHeight, viewportHeight: viewportSize.height, steps: 4)
                for offset in scrollOffsets {
                    do {
                        _ = try harness.render(scene: scene, scrollOffset: CGPoint(x: 0, y: offset))
                    } catch {
                        XCTFail("Markdown benchmark render failed: \(error)")
                    }
                }
                XCTAssertGreaterThan(scene.primitives.count, 5_000)
            }
        }
    }

    func testZBenchmarkLargeUnifiedDiffBuildAndHeadlessRender() throws {
        let diff = RenderingStressFixtures.makeLargeUnifiedDiff(fileCount: 96, linesPerHunk: 30)
        let font = NSFont.monospacedSystemFont(ofSize: 13, weight: .regular)
        let harness = try HeadlessSceneStressHarness(baseFont: font, viewportSize: viewportSize)

        measure(metrics: [XCTClockMetric()]) {
            autoreleasepool {
                let result = VVUnifiedDiffSceneRenderer.render(
                    unifiedDiff: diff,
                    width: viewportSize.width,
                    theme: .dark,
                    baseFont: font,
                    style: .split,
                    options: .full
                )
                let scrollOffsets = RenderingStressFixtures.makeScrollOffsets(totalHeight: result.contentHeight, viewportHeight: viewportSize.height, steps: 4)
                for offset in scrollOffsets {
                    do {
                        _ = try harness.render(scene: result.scene, scrollOffset: CGPoint(x: 0, y: offset))
                    } catch {
                        XCTFail("Unified diff benchmark render failed: \(error)")
                    }
                }
                XCTAssertGreaterThan(result.scene.primitives.count, 4_000)
            }
        }
    }

    private func profileMarkdownCycle(
        content: String,
        font: NSFont,
        harness: HeadlessSceneStressHarness,
        label: String
    ) -> RenderingResourceSample {
        autoreleasepool {
            let baseline = residentMemoryBytes()
            var peak = baseline

            let parser = MarkdownParser()
            let document = parser.parse(content)
            let layoutEngine = MarkdownLayoutEngine(baseFont: font, theme: .dark, contentWidth: viewportSize.width)
            layoutEngine.updateImageSizeProvider { _ in CGSize(width: 88, height: 24) }
            let layout = layoutEngine.layout(document)
            let pipeline = VVMarkdownRenderPipeline(theme: .dark, layoutEngine: layoutEngine, scale: 2.0)
            let scene = pipeline.buildScene(from: layout)
            let scrollOffsets = RenderingStressFixtures.makeScrollOffsets(totalHeight: layout.totalHeight, viewportHeight: viewportSize.height, steps: 6)

            for offset in scrollOffsets {
                do {
                    _ = try harness.render(scene: scene, scrollOffset: CGPoint(x: 0, y: offset))
                    peak = max(peak, residentMemoryBytes())
                } catch {
                    XCTFail("Markdown stress render failed at offset \(offset): \(error)")
                }
            }

            let final = residentMemoryBytes()
            let sample = RenderingResourceSample(baseline: baseline, peak: peak, final: final)
            print(
                """
                markdown render cycle \(label):
                  baseline_rss_mb=\(formatMB(sample.baseline))
                  peak_rss_mb=\(formatMB(sample.peak))
                  final_rss_mb=\(formatMB(sample.final))
                  peak_growth_mb=\(formatMB(sample.peakGrowth))
                  retained_growth_mb=\(formatMB(sample.retainedGrowth))
                """
            )
            return sample
        }
    }

    private func profileDiffCycle(
        diff: String,
        harness: HeadlessSceneStressHarness,
        label: String
    ) -> RenderingResourceSample {
        autoreleasepool {
            let baseline = residentMemoryBytes()
            var peak = baseline

            let result = VVUnifiedDiffSceneRenderer.render(
                unifiedDiff: diff,
                width: viewportSize.width,
                theme: .dark,
                baseFont: NSFont.monospacedSystemFont(ofSize: 13, weight: .regular),
                style: .split,
                options: .full
            )
            let scrollOffsets = RenderingStressFixtures.makeScrollOffsets(totalHeight: result.contentHeight, viewportHeight: viewportSize.height, steps: 6)

            for offset in scrollOffsets {
                do {
                    _ = try harness.render(scene: result.scene, scrollOffset: CGPoint(x: 0, y: offset))
                    peak = max(peak, residentMemoryBytes())
                } catch {
                    XCTFail("Unified diff stress render failed at offset \(offset): \(error)")
                }
            }

            let final = residentMemoryBytes()
            let sample = RenderingResourceSample(baseline: baseline, peak: peak, final: final)
            print(
                """
                unified diff render cycle \(label):
                  baseline_rss_mb=\(formatMB(sample.baseline))
                  peak_rss_mb=\(formatMB(sample.peak))
                  final_rss_mb=\(formatMB(sample.final))
                  peak_growth_mb=\(formatMB(sample.peakGrowth))
                  retained_growth_mb=\(formatMB(sample.retainedGrowth))
                """
            )
            return sample
        }
    }

    private func residentMemoryBytes() -> UInt64 {
        var info = task_vm_info_data_t()
        var count = mach_msg_type_number_t(MemoryLayout.size(ofValue: info) / MemoryLayout<natural_t>.size)
        let result = withUnsafeMutablePointer(to: &info) { pointer -> kern_return_t in
            pointer.withMemoryRebound(to: integer_t.self, capacity: Int(count)) { rebound in
                task_info(mach_task_self_, task_flavor_t(TASK_VM_INFO), rebound, &count)
            }
        }
        guard result == KERN_SUCCESS else { return 0 }
        return info.phys_footprint
    }

    private func formatMB(_ bytes: UInt64) -> String {
        String(format: "%.1f", Double(bytes) / 1_048_576.0)
    }
}

private struct RenderingResourceSample {
    let baseline: UInt64
    let peak: UInt64
    let final: UInt64

    var peakGrowth: UInt64 {
        max(0, peak - baseline)
    }

    var retainedGrowth: UInt64 {
        max(0, final - baseline)
    }
}
