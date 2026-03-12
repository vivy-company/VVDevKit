import XCTest
import CoreGraphics
#if canImport(Metal)
import Metal
#endif
#if canImport(AppKit)
import AppKit
#endif
@testable import VVMarkdown
import VVMetalPrimitives

final class VVDiffSceneRendererTests: XCTestCase {
    func testAnalyzeParsesRowsAndLineNumbers() {
        let document = VVDiffSceneRenderer.analyze(unifiedDiff: sampleDiff)

        XCTAssertEqual(document.rows.first?.kind, .fileHeader)
        XCTAssertEqual(document.rows.first?.text, "Sources/App.swift")
        XCTAssertEqual(document.rows.first(where: { $0.kind == .hunkHeader })?.text, "@@ -10,3 +10,4 @@ struct AppView {")

        let deleted = document.rows.first(where: { $0.kind == .deleted })
        XCTAssertEqual(deleted?.oldLineNumber, 10)
        XCTAssertNil(deleted?.newLineNumber)

        let addedRows = document.rows.filter { $0.kind == .added }
        XCTAssertEqual(addedRows.count, 2)
        XCTAssertEqual(addedRows.first?.newLineNumber, 10)
        XCTAssertEqual(addedRows.last?.newLineNumber, 11)
    }

    func testAnalyzeBuildsSplitRowsWithInlineChanges() throws {
        let document = VVDiffSceneRenderer.analyze(unifiedDiff: sampleDiff)

        let pairedChange = try XCTUnwrap(document.splitRows.first {
            $0.left?.kind == .deleted && $0.right?.kind == .added
        })

        XCTAssertEqual(pairedChange.left?.text, "    let value = oldValue")
        XCTAssertEqual(pairedChange.right?.text, "    let value = newValue")
        XCTAssertFalse(pairedChange.left?.inlineChanges.isEmpty ?? true)
        XCTAssertFalse(pairedChange.right?.inlineChanges.isEmpty ?? true)
    }

    func testAnalyzePairsReplacementAcrossMetadataMarker() throws {
        let diff = """
        diff --git a/file.txt b/file.txt
        index 1111111..2222222 100644
        --- a/file.txt
        +++ b/file.txt
        @@ -1 +1 @@
        -old
        \\ No newline at end of file
        +new
        """

        let document = VVDiffSceneRenderer.analyze(unifiedDiff: diff)

        let pairedChange = try XCTUnwrap(document.splitRows.first {
            $0.left?.kind == .deleted && $0.right?.kind == .added
        })

        XCTAssertEqual(pairedChange.left?.text, "old")
        XCTAssertEqual(pairedChange.right?.text, "new")
        XCTAssertFalse(document.splitRows.contains {
            ($0.left?.text == "old" && $0.right == nil) ||
            ($0.left == nil && $0.right?.text == "new")
        })
    }

    func testCompactInlineRenderIsShorterThanFullRender() throws {
        let theme = MarkdownTheme.dark
        let font = try makeFont()

        let full = VVDiffSceneRenderer.render(
            unifiedDiff: sampleDiff,
            width: 900,
            theme: theme,
            baseFont: font,
            style: .inline,
            options: .full
        )
        let compact = VVDiffSceneRenderer.render(
            unifiedDiff: sampleDiff,
            width: 900,
            theme: theme,
            baseFont: font,
            style: .inline,
            options: .compactInline
        )

        XCTAssertGreaterThan(full.contentHeight, compact.contentHeight)
        XCTAssertGreaterThan(compact.contentHeight, 0)
    }

    func testRenderInlineProducesScene() throws {
        let theme = MarkdownTheme.dark
        let font = try makeFont()

        let result = VVDiffSceneRenderer.render(
            unifiedDiff: sampleDiff,
            width: 900,
            theme: theme,
            baseFont: font,
            style: .inline,
            options: .full
        )

        XCTAssertGreaterThan(result.contentHeight, 0)
        XCTAssertFalse(result.scene.primitives.isEmpty)
    }

    func testSideBySideRenderWrapsLongLinesWithinPaneBounds() throws {
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

        let result = VVDiffSceneRenderer.render(
            unifiedDiff: diff,
            width: 960,
            theme: theme,
            baseFont: font,
            style: .sideBySide,
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

    func testSideBySideRenderMarksEmptyPaneWithHatchedGuides() throws {
        let theme = MarkdownTheme.dark
        let font = try makeFont()
        let diff = """
        diff --git a/Sources/Feature.swift b/Sources/Feature.swift
        index 1111111..2222222 100644
        --- a/Sources/Feature.swift
        +++ b/Sources/Feature.swift
        @@ -10,2 +10,1 @@
         let preserved = true
        -let removed = false
        """

        let result = VVDiffSceneRenderer.render(
            unifiedDiff: diff,
            width: 960,
            theme: theme,
            baseFont: font,
            style: .sideBySide,
            options: .full
        )

        let paneWidth = max(CGFloat(420), floor(CGFloat(960) / 2))
        let emptyPaneGuides = result.scene.primitives.compactMap { primitive -> VVPathPrimitive? in
            guard case let .path(path) = primitive.kind else { return nil }
            return path
        }

        XCTAssertFalse(emptyPaneGuides.isEmpty)
        XCTAssertTrue(emptyPaneGuides.contains { path in
            path.bounds.maxX >= paneWidth && path.bounds.minY < path.bounds.maxY
        })
    }

    func testSideBySideEmptyPaneRendersVisibleHatch() throws {
        #if canImport(Metal)
        let theme = MarkdownTheme.dark
        let font = try makeFont()
        let diff = """
        diff --git a/Sources/Feature.swift b/Sources/Feature.swift
        index 1111111..2222222 100644
        --- a/Sources/Feature.swift
        +++ b/Sources/Feature.swift
        @@ -10,1 +10,6 @@
         let preserved = true
        +let addedOne = 1
        +let addedTwo = 2
        +let addedThree = 3
        +let addedFour = 4
        +let addedFive = 5
        """

        let result = VVDiffSceneRenderer.render(
            unifiedDiff: diff,
            width: 960,
            theme: theme,
            baseFont: font,
            style: .sideBySide,
            options: .full
        )

        let paneWidth = max(CGFloat(420), floor(CGFloat(960) / 2))
        let leftPaneRect = CGRect(x: 0, y: 0, width: paneWidth, height: ceil(result.contentHeight))
        let emptyStripeBounds = result.scene.primitives.reduce(into: CGRect.null) { partialResult, primitive in
            guard case let .path(path) = primitive.kind else { return }
            let candidateBounds = primitive.clipRect ?? path.bounds
            let clippedBounds = candidateBounds.intersection(leftPaneRect)
            guard !clippedBounds.isNull, clippedBounds.height > 0.5 else { return }
            partialResult = partialResult.union(clippedBounds)
        }

        XCTAssertFalse(emptyStripeBounds.isNull)

        let texture = try renderDiffScene(result.scene, viewportSize: CGSize(width: 960, height: ceil(result.contentHeight)), font: font)
        let sampleRect = CGRect(
            x: 0,
            y: emptyStripeBounds.minY + 2,
            width: paneWidth,
            height: max(1, emptyStripeBounds.height - 4)
        )
        let uniqueColors = try uniqueBGRAColors(
            in: texture,
            sampleRect: sampleRect,
            step: 1
        )

        XCTAssertGreaterThan(uniqueColors.count, 1)
        #else
        throw XCTSkip("Metal is unavailable on this platform.")
        #endif
    }

    func testLayoutRenderShowsHatchForAsymmetricSplitGap() throws {
        #if canImport(Metal)
        let theme = MarkdownTheme.dark
        let font = try makeFont()
        let diff = """
        diff --git a/Sources/Greeting.swift b/Sources/Greeting.swift
        index 1a2b3c4..5d6e7f8 100644
        --- a/Sources/Greeting.swift
        +++ b/Sources/Greeting.swift
        @@ -1,15 +1,19 @@
         import Foundation
        +import os.log
        
        -func greet(name: String) -> String {
        -    return "Hello, " + name + "!"
        +struct Greeting {
        +    let name: String
        +    let style: Style
        +
        +    enum Style {
        +        case formal
        +        case casual
        +    }
        +
        +    func render() -> String {
        +        switch style {
        +        case .formal:
        +            return "Good day, \\(name)."
        +        case .casual:
        +            return "Hey \\(name)!"
        +        }
        +    }
         }
        
        -func greetAll(names: [String]) -> [String] {
        -    var results: [String] = []
        -    for name in names {
        -        results.append(greet(name: name))
        -    }
        -    return results
        -}
        -
        -let message = greet(name: "World")
        +let greeting = Greeting(name: "World", style: .casual)
        +print(greeting.render())
        """

        let document = VVDiffSceneRenderer.analyze(unifiedDiff: diff)
        let layout = VVDiffLayoutBuilder.makeLayout(
            document: document,
            width: 840,
            baseFont: font,
            style: .sideBySide,
            wrapLines: true
        )
        let result = VVDiffSceneRenderer.render(
            layout: layout,
            theme: theme,
            baseFont: font,
            options: .full
        )

        let paneWidth = layout.metrics.columnWidth
        let leftPanePaths = result.scene.primitives.compactMap { primitive -> VVPathPrimitive? in
            guard case let .path(path) = primitive.kind else { return nil }
            guard path.bounds.maxX <= paneWidth + 1 else { return nil }
            return path
        }
        XCTAssertFalse(leftPanePaths.isEmpty)

        let leftPanePathUnion = leftPanePaths.reduce(into: CGRect.null) { acc, path in
            acc = acc.union(path.bounds)
        }
        XCTAssertTrue(
            leftPanePathUnion.minY <= layout.metrics.lineHeight * 5 &&
            leftPanePathUnion.maxY >= layout.metrics.lineHeight * 14
        )

        let sampleRect = CGRect(
            x: 0,
            y: layout.metrics.lineHeight * 4,
            width: paneWidth,
            height: layout.metrics.lineHeight * 11
        )
        let texture = try renderDiffScene(
            result.scene,
            viewportSize: CGSize(width: layout.metrics.totalWidth, height: ceil(result.contentHeight)),
            font: font
        )
        let uniqueColors = try uniqueBGRAColors(in: texture, sampleRect: sampleRect, step: 1)
        XCTAssertGreaterThan(uniqueColors.count, 2)
        #else
        throw XCTSkip("Metal is unavailable on this platform.")
        #endif
    }

    func testSideBySideWrappedShorterPaneStillShowsHatchBelowContent() throws {
        #if canImport(Metal)
        let theme = MarkdownTheme.dark
        let font = try makeFont()
        let repeated = String(repeating: "wrapped_segment ", count: 24)
        let diff = """
        diff --git a/Sources/Feature.swift b/Sources/Feature.swift
        index 1111111..2222222 100644
        --- a/Sources/Feature.swift
        +++ b/Sources/Feature.swift
        @@ -10,1 +10,1 @@
        -let value = 1
        +let value = "\(repeated)"
        """

        let document = VVDiffSceneRenderer.analyze(unifiedDiff: diff)
        let layout = VVDiffLayoutBuilder.makeLayout(
            document: document,
            width: 840,
            baseFont: font,
            style: .sideBySide,
            wrapLines: true
        )
        let result = VVDiffSceneRenderer.render(
            layout: layout,
            theme: theme,
            baseFont: font,
            options: .full
        )

        let splitBlock = try XCTUnwrap(layout.blocks.first {
            if case .splitRow = $0.kind {
                return true
            }
            return false
        })
        XCTAssertGreaterThan(splitBlock.height, layout.metrics.lineHeight)

        let sampleRect = CGRect(
            x: 0,
            y: splitBlock.y + layout.metrics.lineHeight + 2,
            width: layout.metrics.columnWidth,
            height: max(1, splitBlock.height - layout.metrics.lineHeight - 4)
        )
        let texture = try renderDiffScene(
            result.scene,
            viewportSize: CGSize(width: layout.metrics.totalWidth, height: ceil(result.contentHeight)),
            font: font
        )
        let uniqueColors = try uniqueBGRAColors(in: texture, sampleRect: sampleRect, step: 1)

        XCTAssertGreaterThan(uniqueColors.count, 1)
        #else
        throw XCTSkip("Metal is unavailable on this platform.")
        #endif
    }

    func testStandalonePathPrimitiveRendersFilledPixels() throws {
        #if canImport(Metal)
        let font = try makeFont()
        var pathBuilder = VVPathBuilder()
        pathBuilder.addRect(CGRect(x: 40, y: 40, width: 120, height: 80))

        var scene = VVScene()
        scene.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 240, height: 180), color: SIMD4<Float>(0.05, 0.05, 0.07, 1))))
        scene.add(kind: .path(pathBuilder.build(fill: SIMD4<Float>(1, 0, 0, 1))))

        let texture = try renderDiffScene(scene, viewportSize: CGSize(width: 240, height: 180), font: font)
        let centerColor = try bgraColor(in: texture, x: 100, y: 80)
        let backgroundColor = try bgraColor(in: texture, x: 10, y: 10)

        XCTAssertNotEqual(centerColor, backgroundColor)
        #else
        throw XCTSkip("Metal is unavailable on this platform.")
        #endif
    }

    func testRenderProfileLargeSideBySideDiff() throws {
        let font = try makeFont()
        let theme = MarkdownTheme.dark
        let diff = makeLargeDiff(fileCount: 24, hunksPerFile: 6)

        for _ in 0..<5 {
            _ = VVDiffSceneRenderer.render(
                unifiedDiff: diff,
                width: 1280,
                theme: theme,
                baseFont: font,
                style: .sideBySide,
                options: .full
            )
        }

        var samples: [Double] = []
        samples.reserveCapacity(20)
        for _ in 0..<20 {
            let start = CFAbsoluteTimeGetCurrent()
            let result = VVDiffSceneRenderer.render(
                unifiedDiff: diff,
                width: 1280,
                theme: theme,
                baseFont: font,
                style: .sideBySide,
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
            format: "VVDiffSceneRenderer side-by-side render profile: median=%.2fms p95=%.2fms p99=%.2fms samples=%d width=%d files=%d hunksPerFile=%d",
            median, p95, p99, samples.count, 1280, 24, 6
        ))

        XCTAssertLessThan(median, 80)
    }
}

private extension VVDiffSceneRendererTests {
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

    #if canImport(Metal)
    func renderDiffScene(_ scene: VVScene, viewportSize: CGSize, font: VVFont) throws -> MTLTexture {
        guard let device = MTLCreateSystemDefaultDevice() else {
            throw XCTSkip("Metal is unavailable on this machine")
        }

        let context = try VVMetalContext(device: device)
        let renderer = VVTextMetalRenderer(context: context, baseFont: font, scaleFactor: 2.0)
        let sceneRenderer = MarkdownScenePrimitiveRenderer(baseFont: font)

        let textureDescriptor = MTLTextureDescriptor.texture2DDescriptor(
            pixelFormat: .bgra8Unorm,
            width: max(1, Int(ceil(viewportSize.width))),
            height: max(1, Int(ceil(viewportSize.height))),
            mipmapped: false
        )
        textureDescriptor.usage = [.renderTarget, .shaderRead]

        guard let texture = device.makeTexture(descriptor: textureDescriptor) else {
            XCTFail("Failed to create offscreen texture")
            throw CancellationError()
        }
        guard let commandBuffer = renderer.commandQueue.makeCommandBuffer() else {
            XCTFail("Failed to create command buffer")
            throw CancellationError()
        }

        let descriptor = MTLRenderPassDescriptor()
        descriptor.colorAttachments[0].texture = texture
        descriptor.colorAttachments[0].loadAction = .clear
        descriptor.colorAttachments[0].storeAction = .store
        descriptor.colorAttachments[0].clearColor = MTLClearColor(red: 0.06, green: 0.06, blue: 0.08, alpha: 1)

        guard let encoder = commandBuffer.makeRenderCommandEncoder(descriptor: descriptor) else {
            XCTFail("Failed to create render encoder")
            throw CancellationError()
        }

        renderer.beginFrame(viewportSize: viewportSize, scrollOffset: .zero)
        sceneRenderer.renderScene(
            scene,
            orderedPrimitives: scene.orderedPrimitives(),
            visibleRect: CGRect(origin: .zero, size: viewportSize),
            encoder: encoder,
            renderer: renderer
        )
        encoder.endEncoding()

        renderer.recycleTransientBuffers(after: commandBuffer)
        commandBuffer.commit()
        commandBuffer.waitUntilCompleted()

        XCTAssertEqual(commandBuffer.status, .completed)
        return texture
    }

    func uniqueBGRAColors(in texture: MTLTexture, sampleRect: CGRect, step: Int) throws -> Set<UInt32> {
        let pixels = readBGRABytes(from: texture)
        let width = texture.width
        let height = texture.height
        let bytesPerRow = width * 4
        let minX = max(0, min(width - 1, Int(sampleRect.minX.rounded(.down))))
        let maxX = max(minX, min(width - 1, Int(sampleRect.maxX.rounded(.up))))
        let minY = max(0, min(height - 1, Int(sampleRect.minY.rounded(.down))))
        let maxY = max(minY, min(height - 1, Int(sampleRect.maxY.rounded(.up))))
        var colors: Set<UInt32> = []

        for y in stride(from: minY, through: maxY, by: max(1, step)) {
            for x in stride(from: minX, through: maxX, by: max(1, step)) {
                colors.insert(bgraColor(in: pixels, bytesPerRow: bytesPerRow, x: x, y: y))
            }
        }

        return colors
    }

    func bgraColor(in texture: MTLTexture, x: Int, y: Int) throws -> UInt32 {
        let pixels = readBGRABytes(from: texture)
        let clampedX = max(0, min(texture.width - 1, x))
        let clampedY = max(0, min(texture.height - 1, y))
        return bgraColor(in: pixels, bytesPerRow: texture.width * 4, x: clampedX, y: clampedY)
    }

    func readBGRABytes(from texture: MTLTexture) -> [UInt8] {
        let width = texture.width
        let height = texture.height
        let bytesPerRow = width * 4
        var pixels = [UInt8](repeating: 0, count: bytesPerRow * height)
        texture.getBytes(
            &pixels,
            bytesPerRow: bytesPerRow,
            from: MTLRegionMake2D(0, 0, width, height),
            mipmapLevel: 0
        )
        return pixels
    }

    func bgraColor(in pixels: [UInt8], bytesPerRow: Int, x: Int, y: Int) -> UInt32 {
        let offset = y * bytesPerRow + x * 4
        let b = UInt32(pixels[offset])
        let g = UInt32(pixels[offset + 1])
        let r = UInt32(pixels[offset + 2])
        let a = UInt32(pixels[offset + 3])
        return (a << 24) | (r << 16) | (g << 8) | b
    }
    #endif
}
