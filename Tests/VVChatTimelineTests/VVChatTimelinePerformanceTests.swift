import XCTest
import AppKit
import Darwin.Mach
@testable import VVChatTimeline
import VVMetalPrimitives

@MainActor
final class VVChatTimelinePerformanceTests: XCTestCase {
    private let viewportSize = CGSize(width: 900, height: 720)

    func testRenderedMessageLookupByIndexMatchesID() {
        let controller = makeSeededController(messageCount: 180, width: viewportSize.width)

        for index in stride(from: 0, to: controller.messages.count, by: 17) {
            let messageID = controller.messages[index].id
            let byIndex = controller.renderedMessage(at: index)
            let byID = controller.renderedMessage(for: messageID)
            XCTAssertEqual(byIndex?.id, byID?.id)
            XCTAssertEqual(byIndex?.revision, byID?.revision)
            XCTAssertEqual(byIndex?.scene.primitives.count, byID?.scene.primitives.count)
        }
    }

    func testRepeatedStreamingMemoryStabilizesAfterWarmCaches() {
        let style = VVChatTimelineStyle()
        let second = profileStreamingCycle(style: style, messageCount: 180, steps: 180, label: "second")
        let third = profileStreamingCycle(style: style, messageCount: 180, steps: 180, label: "third")

        let slack: UInt64 = 12 * 1024 * 1024
        XCTAssertLessThanOrEqual(third.retainedGrowth, second.retainedGrowth + slack)
        XCTAssertLessThanOrEqual(third.peakGrowth, second.peakGrowth + slack)
    }

    func testHeadlessVisibleWindowRenderingAcrossLargeTimeline() throws {
        let controller = makeSeededController(messageCount: 420, width: viewportSize.width)
        let harness = try HeadlessSceneStressHarness(
            baseFont: NSFont.systemFont(ofSize: 14),
            viewportSize: viewportSize
        )

        let scrollOffsets = makeScrollOffsets(totalHeight: controller.totalHeight, viewportHeight: viewportSize.height, steps: 10)
        var totalPrimitives = 0
        var primitiveCounts: [Int] = []

        for offset in scrollOffsets {
            let scene = combinedVisibleScene(controller: controller, scrollOffsetY: offset, viewportHeight: viewportSize.height)
            totalPrimitives += scene.primitives.count
            primitiveCounts.append(scene.primitives.count)
            autoreleasepool {
                do {
                    _ = try harness.render(scene: scene, scrollOffset: CGPoint(x: 0, y: offset))
                } catch {
                    XCTFail("Headless timeline render failed at offset \(offset): \(error)")
                }
            }
        }

        XCTAssertGreaterThan(primitiveCounts.min() ?? 0, 240)
        XCTAssertGreaterThan(totalPrimitives, scrollOffsets.count * 360)
    }

    func testZBenchmarkHeadlessVisibleWindowRendering() throws {
        let controller = makeSeededController(messageCount: 320, width: viewportSize.width)
        let harness = try HeadlessSceneStressHarness(
            baseFont: NSFont.systemFont(ofSize: 14),
            viewportSize: viewportSize
        )
        let scrollOffsets = makeScrollOffsets(
            totalHeight: controller.totalHeight,
            viewportHeight: viewportSize.height,
            steps: 5
        )

        measure(metrics: [XCTClockMetric()]) {
            autoreleasepool {
                var renderError: Error?
                for offset in scrollOffsets {
                    let scene = combinedVisibleScene(
                        controller: controller,
                        scrollOffsetY: offset,
                        viewportHeight: viewportSize.height
                    )
                    do {
                        _ = try harness.render(scene: scene, scrollOffset: CGPoint(x: 0, y: offset))
                    } catch {
                        renderError = error
                        break
                    }
                }
                XCTAssertNil(renderError)
            }
        }
    }

    func testZBenchmarkHighLoadDraftUpdates() {
        measure(metrics: [XCTClockMetric()]) {
            autoreleasepool {
                let controller = makeSeededController(messageCount: 260, width: viewportSize.width)
                let draftID = controller.beginStreamingAssistantMessage(content: "")
                for step in 0..<110 {
                    controller.updateDraftMessage(
                        id: draftID,
                        content: streamedMarkdown(step: step, cycle: "bench"),
                        throttle: false
                    )
                }
                controller.finalizeMessage(id: draftID, content: streamedMarkdown(step: 110, cycle: "bench-final"))
                XCTAssertGreaterThan(controller.totalHeight, 0)
            }
        }
    }

    private func makeSeededController(messageCount: Int, width: CGFloat) -> VVChatTimelineController {
        let controller = VVChatTimelineController(style: .init(), renderWidth: width)
        for index in 0..<messageCount {
            controller.appendMessage(
                VVChatMessage(
                    id: "seed-\(index)",
                    role: index.isMultiple(of: 3) ? .user : .assistant,
                    state: .final,
                    content: seededMessage(index: index)
                )
            )
        }
        return controller
    }

    private func combinedVisibleScene(
        controller: VVChatTimelineController,
        scrollOffsetY: CGFloat,
        viewportHeight: CGFloat
    ) -> VVScene {
        let overscan: CGFloat = 900
        let minY = scrollOffsetY - overscan
        let maxY = scrollOffsetY + viewportHeight + overscan
        var builder = VVSceneBuilder()

        for index in controller.layouts.indices {
            let layout = controller.layouts[index]
            if layout.frame.maxY < minY { continue }
            if layout.frame.minY > maxY { break }
            guard let rendered = controller.renderedMessage(at: index) else { continue }
            builder.withOffset(CGPoint(x: layout.frame.origin.x + layout.contentOffset.x, y: layout.frame.origin.y + layout.contentOffset.y)) { builder in
                builder.add(node: VVNode.fromScene(rendered.scene))
            }
        }

        return builder.scene
    }

    private func profileStreamingCycle(
        style: VVChatTimelineStyle,
        messageCount: Int,
        steps: Int,
        label: String
    ) -> StreamingCycleSample {
        autoreleasepool {
            let controller = VVChatTimelineController(style: style, renderWidth: viewportSize.width)
            let view = VVChatTimelineView(frame: CGRect(origin: .zero, size: viewportSize))
            view.controller = controller

            for index in 0..<messageCount {
                controller.appendMessage(
                    VVChatMessage(
                        id: "\(label)-seed-\(index)",
                        role: index.isMultiple(of: 3) ? .user : .assistant,
                        state: .final,
                        content: seededMessage(index: index)
                    )
                )
            }

            drainMainRunLoop(for: 0.25)
            let baseline = residentMemoryBytes()

            let draftID = controller.beginStreamingAssistantMessage(content: "")
            var peak = baseline

            for step in 0..<steps {
                controller.updateDraftMessage(
                    id: draftID,
                    content: streamedMarkdown(step: step, cycle: label),
                    throttle: false
                )
                drainMainRunLoop(for: 0.008)
                peak = max(peak, residentMemoryBytes())
            }

            controller.finalizeMessage(id: draftID, content: streamedMarkdown(step: steps, cycle: "\(label)-final"))
            drainMainRunLoop(for: 1.0)
            let final = residentMemoryBytes()

            controller.setEntries([], scrollToBottom: false)
            view.controller = nil
            drainMainRunLoop(for: 0.75)

            let sample = StreamingCycleSample(
                baseline: baseline,
                peak: peak,
                final: final
            )

            print(
                """
                chat timeline streaming cycle \(label):
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

    private func makeScrollOffsets(totalHeight: CGFloat, viewportHeight: CGFloat, steps: Int) -> [CGFloat] {
        let maxOffset = max(0, totalHeight - viewportHeight)
        guard maxOffset > 0 else { return [0] }
        let count = max(1, steps)
        let stride = maxOffset / CGFloat(count)
        return (0...count).map { min(maxOffset, CGFloat($0) * stride) }
    }

    private func drainMainRunLoop(for duration: TimeInterval) {
        let until = Date().addingTimeInterval(duration)
        while Date() < until {
            RunLoop.main.run(mode: .default, before: min(until, Date().addingTimeInterval(0.01)))
        }
    }

    private func seededMessage(index: Int) -> String {
        """
        ## Seed \(index)

        This is seeded timeline content to make layout snapshots, rendered message caches, and markdown scenes more realistic.

        - first item
        - second item
        - third item

        ```swift
        let value = \(index)
        print(value)
        ```
        """
    }

    private func streamedMarkdown(step: Int, cycle: String) -> String {
        var text = """
        ## Streaming Turn \(cycle)

        The assistant is producing a long answer while tool work is happening in the background.

        """

        for row in 0...step {
            text += "- streamed bullet \(row): rendering should stay stable while memory does not grow without bound.\n"
            if row.isMultiple(of: 16) {
                text += "\n```swift\nlet row\(row) = \(row)\nprint(row\(row))\n```\n\n"
            }
        }

        return text
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

private struct StreamingCycleSample {
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
