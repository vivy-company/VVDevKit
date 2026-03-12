import CoreGraphics
import Foundation
import XCTest

enum RenderingStressFixtures {
    static func loadMarkdownSample() throws -> String {
        if let overridePath = ProcessInfo.processInfo.environment["VVDEVKIT_MARKDOWN_STRESS_FIXTURE"],
           FileManager.default.fileExists(atPath: overridePath) {
            return try String(contentsOfFile: overridePath, encoding: .utf8)
        }

        guard let url = Bundle.module.url(forResource: "markdown_stress", withExtension: "md") else {
            throw XCTSkip("Missing markdown stress fixture")
        }
        return try String(contentsOf: url, encoding: .utf8)
    }

    static func repeatContent(_ content: String, count: Int) -> String {
        Array(repeating: content, count: count).joined(separator: "\n\n---\n\n")
    }

    static func makeScrollOffsets(totalHeight: CGFloat, viewportHeight: CGFloat, steps: Int) -> [CGFloat] {
        let clampedSteps = max(1, steps)
        let maxOffset = max(0, totalHeight - viewportHeight)
        guard maxOffset > 0 else { return [0] }
        let stride = maxOffset / CGFloat(clampedSteps)
        return (0...clampedSteps).map { min(maxOffset, CGFloat($0) * stride) }
    }

    static func makeLargeUnifiedDiff(fileCount: Int, linesPerHunk: Int) -> String {
        var lines: [String] = []
        lines.reserveCapacity(fileCount * (linesPerHunk * 3 + 8))

        for fileIndex in 0..<fileCount {
            lines.append("diff --git a/Sources/File\(fileIndex).swift b/Sources/File\(fileIndex).swift")
            lines.append("index 1111111..2222222 100644")
            lines.append("--- a/Sources/File\(fileIndex).swift")
            lines.append("+++ b/Sources/File\(fileIndex).swift")
            lines.append("@@ -1,\(linesPerHunk) +1,\(linesPerHunk) @@")
            for lineIndex in 0..<linesPerHunk {
                lines.append(contentsOf: stressDiffTriplet(fileIndex: fileIndex, lineIndex: lineIndex))
            }
        }

        return lines.joined(separator: "\n")
    }

    private static func stressDiffTriplet(fileIndex: Int, lineIndex: Int) -> [String] {
        let symbol = "slot_\(fileIndex)_\(lineIndex)"
        let pattern = (fileIndex * 29 + lineIndex) % 5

        switch pattern {
        case 0:
            return [
                "-let \(symbol) = LegacyRenderer.render(id: \(fileIndex), line: \(lineIndex), isEnabled: false)",
                "+let \(symbol) = DiffRenderer.render(id: \(fileIndex), line: \(lineIndex), theme: .dark, isEnabled: true) ?? \"fallback-\(fileIndex)-\(lineIndex)\"",
                " metrics[\(lineIndex)] = \(symbol).count"
            ]
        case 1:
            return [
                "-let \(symbol) = cache[\"item-\(lineIndex)\"] as! [String]",
                "+let \(symbol) = (cache[\"item-\(lineIndex)\"] as? [String]) ?? fallbackItems(prefix: \"f\(fileIndex)\")",
                " totals[\(lineIndex)] = \(symbol).joined(separator: \":\").utf8.count"
            ]
        case 2:
            return [
                "-let \(symbol) = URL(string: rawEndpoints[\(lineIndex % 4)])!.absoluteString",
                "+let \(symbol) = URL(string: rawEndpoints[\(lineIndex % 4)])?.standardized.absoluteString ?? \"/fallback/\(fileIndex)/\(lineIndex)\"",
                " debugTrail.append(\(symbol))"
            ]
        case 3:
            return [
                "-let \(symbol) = rows.map { $0.name }.joined(separator: \",\")",
                "+let \(symbol) = rows.lazy.map(\\.name).filter { !$0.isEmpty }.joined(separator: \", \")",
                " renderWidth += \(symbol).count"
            ]
        default:
            return [
                "-let \(symbol) = callbacks[\(lineIndex)]?(state) ?? .idle",
                "+let \(symbol) = pipeline.run(stage: \(lineIndex % 6), state: state, retries: \(lineIndex % 3))",
                " timeline.append(\"\(lineIndex):\\(\(symbol))\")"
            ]
        }
    }
}
