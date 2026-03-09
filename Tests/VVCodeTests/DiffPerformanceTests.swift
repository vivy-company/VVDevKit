import XCTest
import Darwin.Mach
@testable import VVCode
@testable import VVGit

    @MainActor
final class DiffPerformanceTests: XCTestCase {
    func testRepeatedLargeUnifiedDiffParseMemoryStabilizesAfterWarmup() {
        let diff = makeLargeSingleFileUnifiedDiff(hunkCount: 1_200, linesPerHunk: 6)

        let second = profileParseCycle(diff: diff, iterations: 18, label: "second")
        let third = profileParseCycle(diff: diff, iterations: 18, label: "third")

        let slack: UInt64 = 8 * 1024 * 1024
        XCTAssertLessThanOrEqual(third.retainedGrowth, second.retainedGrowth + slack)
        XCTAssertLessThanOrEqual(third.peakGrowth, second.peakGrowth + slack)
    }

    func testRepeatedMultiDiffProjectionMemoryStabilizesAfterWarmup() {
        let entries = makeMultiDiffEntries(fileCount: 16, totalLines: 220)

        let second = profileProjectionCycle(entries: entries, iterations: 10, label: "second")
        let third = profileProjectionCycle(entries: entries, iterations: 10, label: "third")

        let slack: UInt64 = 10 * 1024 * 1024
        XCTAssertLessThanOrEqual(third.retainedGrowth, second.retainedGrowth + slack)
        XCTAssertLessThanOrEqual(third.peakGrowth, second.peakGrowth + slack)
    }

    func testZBenchmarkLargeUnifiedDiffParse() {
        let diff = makeLargeSingleFileUnifiedDiff(hunkCount: 1_200, linesPerHunk: 6)

        measure(metrics: [XCTClockMetric()]) {
            autoreleasepool {
                let hunks = VVDiffParser.parse(unifiedDiff: diff)
                let statuses = VVDiffParser.lineStatuses(from: hunks)
                XCTAssertGreaterThan(hunks.count, 1_000)
                XCTAssertGreaterThan(statuses.count, 1_000)
            }
        }
    }

    func testZBenchmarkLargeMultiDiffProjectionBuild() {
        let entries = makeMultiDiffEntries(fileCount: 16, totalLines: 220)

        measure(metrics: [XCTClockMetric()]) {
            autoreleasepool {
                let document = VVMultiDiffDocument(entries: entries, contextLines: 1)
                let presentation = document.presentation()
                XCTAssertGreaterThan(presentation.visualHunks.count, 12)
                XCTAssertFalse(presentation.fileSummaries.isEmpty)
            }
        }
    }

    private func profileParseCycle(diff: String, iterations: Int, label: String) -> ResourceSample {
        autoreleasepool {
            let baseline = residentMemoryBytes()
            var peak = baseline

            for _ in 0..<iterations {
                autoreleasepool {
                    let hunks = VVDiffParser.parse(unifiedDiff: diff)
                    let statuses = VVDiffParser.lineStatuses(from: hunks)
                    XCTAssertGreaterThan(hunks.count, 1_000)
                    XCTAssertGreaterThan(statuses.count, 1_000)
                    peak = max(peak, residentMemoryBytes())
                }
            }

            let final = residentMemoryBytes()
            let sample = ResourceSample(baseline: baseline, peak: peak, final: final)
            print(
                """
                diff parse cycle \(label):
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

    private func profileProjectionCycle(
        entries: [VVMultiDiffEntry],
        iterations: Int,
        label: String
    ) -> ResourceSample {
        autoreleasepool {
            let baseline = residentMemoryBytes()
            var peak = baseline

            for _ in 0..<iterations {
                autoreleasepool {
                    let document = VVMultiDiffDocument(entries: entries, contextLines: 1)
                    document.setRenderWindow(.init(isEnabled: true, hunkBuffer: 2, minimumTotalHunks: 1))
                    let initial = document.presentation()
                    XCTAssertGreaterThan(initial.renderWindowState.totalHunkCount, 100)
                    XCTAssertGreaterThan(initial.visualHunks.count, 0)
                    if let middleHunk = initial.visualHunks.dropFirst(initial.visualHunks.count / 2).first {
                        document.updateRenderAnchor(forVisibleLineRange: middleHunk.startLine...middleHunk.endLine)
                    }
                    let updated = document.presentation()
                    XCTAssertFalse(updated.visualHunks.isEmpty)
                    peak = max(peak, residentMemoryBytes())
                }
            }

            let final = residentMemoryBytes()
            let sample = ResourceSample(baseline: baseline, peak: peak, final: final)
            print(
                """
                multi diff projection cycle \(label):
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

    private func makeMultiDiffEntries(fileCount: Int, totalLines: Int) -> [VVMultiDiffEntry] {
        (0..<fileCount).map { fileIndex in
            let changedLines = stride(from: 4 + (fileIndex % 3), through: totalLines - 4, by: 7).map { $0 }
            let oldDocument = VVDocument(
                text: makeNumberedText(prefix: "base-\(fileIndex)", totalLines: totalLines),
                language: .swift
            )
            let newDocument = VVDocument(
                text: makeChangedNumberedText(
                    prefix: "next-\(fileIndex)",
                    totalLines: totalLines,
                    changedLines: Set(changedLines)
                ),
                language: .swift
            )
            return VVMultiDiffEntry(
                id: "entry-\(fileIndex)",
                path: "Sources/File\(fileIndex).swift",
                oldDocument: oldDocument,
                newDocument: newDocument,
                language: .swift,
                unifiedDiff: makeUnifiedDiff(
                    path: "Sources/File\(fileIndex).swift",
                    totalLines: totalLines,
                    changedLines: changedLines,
                    prefix: "file\(fileIndex)"
                )
            )
        }
    }

    private func makeLargeSingleFileUnifiedDiff(hunkCount: Int, linesPerHunk: Int) -> String {
        var lines: [String] = []
        lines.reserveCapacity(hunkCount * (linesPerHunk * 3 + 8))

        let path = "Sources/LargeFeature.swift"
        lines.append("diff --git a/\(path) b/\(path)")
        lines.append("index 1111111..2222222 100644")
        lines.append("--- a/\(path)")
        lines.append("+++ b/\(path)")

        for hunkIndex in 0..<hunkCount {
            let start = hunkIndex * (linesPerHunk + 1) + 1
            lines.append("@@ -\(start),\(linesPerHunk) +\(start),\(linesPerHunk) @@ func render\(hunkIndex)() {")
            for lineIndex in 0..<linesPerHunk {
                lines.append("-let removed_\(hunkIndex)_\(lineIndex) = \(hunkIndex + lineIndex)")
                lines.append("+let added_\(hunkIndex)_\(lineIndex) = \"payload \(hunkIndex)-\(lineIndex)\"")
                lines.append(" context_\(hunkIndex)_\(lineIndex) = added_\(hunkIndex)_\(lineIndex)")
            }
        }

        return lines.joined(separator: "\n")
    }

    private func makeNumberedText(prefix: String, totalLines: Int) -> String {
        (1...totalLines).map { "\(prefix)-\($0)" }.joined(separator: "\n") + "\n"
    }

    private func makeChangedNumberedText(prefix: String, totalLines: Int, changedLines: Set<Int>) -> String {
        (1...totalLines).map { line in
            if changedLines.contains(line) {
                return "\(prefix)-\(line)-changed"
            }
            return "\(prefix)-\(line)"
        }
        .joined(separator: "\n") + "\n"
    }

    private func makeUnifiedDiff(path: String, totalLines: Int, changedLines: [Int], prefix: String) -> String {
        var lines: [String] = []
        lines.append("diff --git a/\(path) b/\(path)")
        lines.append("index 1111111..2222222 100644")
        lines.append("--- a/\(path)")
        lines.append("+++ b/\(path)")

        for line in changedLines {
            let start = max(1, line - 1)
            let end = min(totalLines, line + 1)
            let count = end - start + 1
            lines.append("@@ -\(start),\(count) +\(start),\(count) @@")
            for current in start...end {
                if current == line {
                    lines.append("-\(prefix)-base-\(current)")
                    lines.append("+\(prefix)-next-\(current)-changed")
                } else {
                    lines.append(" \(prefix)-base-\(current)")
                }
            }
        }

        return lines.joined(separator: "\n")
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

private struct ResourceSample {
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
