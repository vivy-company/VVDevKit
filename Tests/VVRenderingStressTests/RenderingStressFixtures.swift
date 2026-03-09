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
                lines.append("-let removed\(fileIndex)_\(lineIndex) = \(fileIndex + lineIndex)")
                lines.append("+let added\(fileIndex)_\(lineIndex) = \"line \(fileIndex)-\(lineIndex) with renderer pressure\"")
                lines.append(" context\(fileIndex)_\(lineIndex) = added\(fileIndex)_\(lineIndex)")
            }
        }

        return lines.joined(separator: "\n")
    }
}
