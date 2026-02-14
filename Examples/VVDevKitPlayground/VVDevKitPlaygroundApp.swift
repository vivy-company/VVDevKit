#if os(macOS)
import AppKit
import CoreText
import Metal
import SwiftUI
import VVChatTimeline
import VVCode
import VVMarkdown
import VVMetalPrimitives
import QuartzCore
import UniformTypeIdentifiers

@main
struct VVDevKitPlaygroundApp: App {
    var body: some Scene {
        WindowGroup("VVDevKit Playground") {
            ContentView()
        }
        .windowStyle(.titleBar)
    }
}

struct ContentView: View {
    enum Tab: String, CaseIterable {
        case code = "Code"
        case diff = "Diff"
        case markdown = "Markdown"
        case mermaid = "Mermaid"
        case primitives = "Primitives"
        case chat = "Chat"
    }

    @State private var selectedTab: Tab = .code
    @State private var showMetrics = true

    var body: some View {
        VStack(spacing: 0) {
            // Metrics bar
            if showMetrics {
                PerformanceMetricsBar()
            }

            TabView(selection: $selectedTab) {
                LazyTab(tag: .code, selected: selectedTab) { CodePlaygroundView() }
                    .tabItem { Text("Code") }.tag(Tab.code)

                LazyTab(tag: .diff, selected: selectedTab) { DiffPlaygroundView() }
                    .tabItem { Text("Diff") }.tag(Tab.diff)

                LazyTab(tag: .markdown, selected: selectedTab) { MarkdownPlaygroundView() }
                    .tabItem { Text("Markdown") }.tag(Tab.markdown)

                LazyTab(tag: .mermaid, selected: selectedTab) { MermaidPlaygroundView() }
                    .tabItem { Text("Mermaid") }.tag(Tab.mermaid)

                LazyTab(tag: .primitives, selected: selectedTab) { PrimitivesPlaygroundView() }
                    .tabItem { Text("Primitives") }.tag(Tab.primitives)

                LazyTab(tag: .chat, selected: selectedTab) { ChatPlaygroundView() }
                    .tabItem { Text("Chat") }.tag(Tab.chat)
            }
        }
        .toolbar {
            ToolbarItem(placement: .automatic) {
                Button(showMetrics ? "Hide Metrics" : "Show Metrics") {
                    showMetrics.toggle()
                }
                .font(.caption)
            }
        }
        .frame(minWidth: 1100, minHeight: 720)
    }
}

// MARK: - Performance Metrics Bar

private struct PerformanceMetricsBar: View {
    @State private var memoryMB: Double = 0
    @State private var alphaPages = 0
    @State private var colorPages = 0
    @State private var cachedGlyphs = 0
    @State private var pooledBuffers = 0
    @State private var atlasMB: Double = 0

    private let timer = Timer.publish(every: 1.0, on: .main, in: .common).autoconnect()

    var body: some View {
        HStack(spacing: 16) {
            MetricLabel(title: "RSS", value: String(format: "%.1f MB", memoryMB))
            Divider().frame(height: 14)
            MetricLabel(title: "Atlas", value: "\(alphaPages)a/\(colorPages)c pages (\(String(format: "%.1f", atlasMB)) MB)")
            Divider().frame(height: 14)
            MetricLabel(title: "Glyphs", value: "\(cachedGlyphs)")
            Divider().frame(height: 14)
            MetricLabel(title: "Buf Pool", value: "\(pooledBuffers)")
            Spacer()
        }
        .padding(.horizontal, 12)
        .padding(.vertical, 4)
        .background(Color(nsColor: .controlBackgroundColor))
        .onReceive(timer) { _ in
            refreshMetrics()
        }
        .onAppear {
            refreshMetrics()
        }
    }

    private func refreshMetrics() {
        // Process memory via mach_task_basic_info
        var info = mach_task_basic_info()
        var count = mach_msg_type_number_t(MemoryLayout<mach_task_basic_info>.size / MemoryLayout<natural_t>.size)
        let result = withUnsafeMutablePointer(to: &info) { infoPtr in
            infoPtr.withMemoryRebound(to: integer_t.self, capacity: Int(count)) { ptr in
                task_info(mach_task_self_, task_flavor_t(MACH_TASK_BASIC_INFO), ptr, &count)
            }
        }
        if result == KERN_SUCCESS {
            memoryMB = Double(info.resident_size) / (1024 * 1024)
        }

        // Atlas diagnostics
        if let ctx = VVMetalContext.shared {
            let d = ctx.atlasDiagnostics()
            alphaPages = d.alphaPages
            colorPages = d.colorPages
            cachedGlyphs = d.cachedGlyphs
            pooledBuffers = ctx.pooledBufferCount

            // Estimate atlas GPU memory: alpha pages = 1MB each (1024^2 * 1 byte),
            // color pages = 4MB each (1024^2 * 4 bytes)
            let atlasSize = MarkdownGlyphAtlas.atlasSize
            let alphaBytes = d.alphaPages * atlasSize * atlasSize * 1
            let colorBytes = d.colorPages * atlasSize * atlasSize * 4
            atlasMB = Double(alphaBytes + colorBytes) / (1024 * 1024)
        }
    }
}

private struct MetricLabel: View {
    let title: String
    let value: String

    var body: some View {
        HStack(spacing: 4) {
            Text(title)
                .foregroundStyle(.secondary)
            Text(value)
        }
        .font(.system(size: 11, design: .monospaced))
    }
}

/// Only creates content for the currently-selected tab.
/// Previous tab content is torn down when switching away, freeing Metal resources.
private struct LazyTab<Content: View>: View {
    let tag: ContentView.Tab
    let selected: ContentView.Tab
    @ViewBuilder let content: () -> Content

    var body: some View {
        if tag == selected {
            content()
        } else {
            Color.clear
        }
    }
}

struct CodePlaygroundView: View {
    @State private var document = VVDocument(text: SampleData.swiftSample, language: .swift)
    @State private var selectedLanguage = VVLanguage.swift
    @State private var useDarkTheme = true
    @State private var wrapLines = false
    @State private var showLineNumbers = true
    @State private var showGutter = true
    @State private var showGitDiff = true
    @State private var showInlineBlame = false
    @State private var enableLSP = false
    @State private var helixModeEnabled = false
    @State private var fontSize: Double = 13
    @State private var tabWidth = 4
    @State private var lspStatus: VVLSPStatus = .disabled
    @State private var fileURL: URL?
    @State private var loadError: String?
    @State private var isDropTargeted = false

    private let languages: [VVLanguage] = [
        .swift,
        .javascript,
        .typescript,
        .python,
        .go,
        .rust,
        .json,
        .yaml,
        .markdown,
        .html,
        .css
    ]

    private var theme: VVTheme {
        useDarkTheme ? .defaultDark : .defaultLight
    }

    private var configuration: VVConfiguration {
        var config = VVConfiguration.default
        config.font = NSFont.monospacedSystemFont(ofSize: fontSize, weight: .regular)
        config.wrapLines = wrapLines
        config.showLineNumbers = showLineNumbers
        config.showGutter = showGutter
        config.showGitGutter = showGitDiff
        config.showInlineBlame = showInlineBlame
        config.tabWidth = tabWidth
        config.helixModeEnabled = helixModeEnabled
        return config
    }

    private var lspStatusLabel: String {
        switch lspStatus {
        case .disabled:
            return "Disabled"
        case .noServer(let language):
            return "No server for \(language)"
        case .starting(let server):
            return "Starting \(server)"
        case .running(let server):
            return "Running \(server)"
        case .failed(let error):
            return "Failed: \(error)"
        }
    }

    var body: some View {
        HSplitView {
            VStack(alignment: .leading, spacing: 12) {
                Text("Editor")
                    .font(.headline)

                HStack(spacing: 8) {
                    Button("Open File") {
                        openFilePanel()
                    }
                    .buttonStyle(.bordered)

                    Button("Reload") {
                        if let fileURL {
                            loadFile(url: fileURL)
                        }
                    }
                    .buttonStyle(.bordered)
                    .disabled(fileURL == nil)
                }

                if let fileURL {
                    Text(fileURL.path)
                        .font(.caption)
                        .foregroundStyle(.secondary)
                        .lineLimit(2)
                }

                if let loadError {
                    Text(loadError)
                        .font(.caption)
                        .foregroundStyle(.red)
                        .fixedSize(horizontal: false, vertical: true)
                }

                Picker("Language", selection: $selectedLanguage) {
                    ForEach(languages, id: \.identifier) { language in
                        Text(language.displayName).tag(language)
                    }
                }

                Toggle("Dark Theme", isOn: $useDarkTheme)
                Toggle("Wrap Lines", isOn: $wrapLines)
                Toggle("Line Numbers", isOn: $showLineNumbers)
                Toggle("Show Gutter", isOn: $showGutter)
                Toggle("Git Diff", isOn: $showGitDiff)
                Toggle("Inline Blame", isOn: $showInlineBlame)
                Toggle("Enable LSP", isOn: $enableLSP)
                Toggle("Helix Mode", isOn: $helixModeEnabled)

                HStack {
                    Text("Font")
                    Slider(value: $fontSize, in: 10...18, step: 1)
                    Text("\(Int(fontSize))")
                        .frame(width: 28, alignment: .trailing)
                }

                HStack {
                    Text("Tab Width")
                    Stepper(value: $tabWidth, in: 2...8) {
                        Text("\(tabWidth)")
                            .frame(width: 24, alignment: .trailing)
                    }
                }

                Divider()

                Button("Load Sample") {
                    document = VVDocument(
                        text: SampleData.sampleText(for: selectedLanguage),
                        language: selectedLanguage
                    )
                    fileURL = nil
                    loadError = nil
                }

                Button("Reset to Swift") {
                    selectedLanguage = .swift
                    document = VVDocument(text: SampleData.swiftSample, language: .swift)
                    fileURL = nil
                    loadError = nil
                }

                Divider()

                Text("LSP: \(lspStatusLabel)")
                    .font(.caption)
                    .foregroundStyle(.secondary)

                Text("If highlighting is missing, build grammars with: swift build --product TreeSitterSwift")
                    .font(.caption2)
                    .foregroundStyle(.secondary)
                    .fixedSize(horizontal: false, vertical: true)

                Spacer()
            }
            .padding(16)
            .frame(minWidth: 240, idealWidth: 280, maxWidth: 340)

            ZStack {
                VVCodeView(document: $document)
                    .language(selectedLanguage)
                    .theme(theme)
                    .configuration(configuration)
                    .gitDiff(showGitDiff ? SampleData.gitDiff : nil)
                    .gitBlame(showInlineBlame ? SampleData.gitBlame : nil)
                    .lspDisabled(!enableLSP)
                    .onLSPStatusChange { status in
                        lspStatus = status
                    }

                if isDropTargeted {
                    RoundedRectangle(cornerRadius: 12)
                        .stroke(Color.accentColor, lineWidth: 2)
                        .padding(16)
                        .allowsHitTesting(false)
                }
            }
            .onDrop(of: [UTType.fileURL], isTargeted: $isDropTargeted) { providers in
                handleDrop(providers: providers)
            }
        }
        .onChange(of: selectedLanguage.identifier) { _ in
            document.language = selectedLanguage
        }
    }

    private func openFilePanel() {
        let panel = NSOpenPanel()
        panel.canChooseFiles = true
        panel.canChooseDirectories = false
        panel.allowsMultipleSelection = false
        panel.title = "Open File"
        if panel.runModal() == .OK, let url = panel.url {
            loadFile(url: url)
        }
    }

    private func loadFile(url: URL) {
        do {
            let newDocument = try VVDocument(contentsOf: url)
            document = newDocument
            if let language = newDocument.language {
                selectedLanguage = language
            } else {
                newDocument.language = selectedLanguage
            }
            fileURL = url
            loadError = nil
        } catch {
            loadError = "Failed to load file: \(error.localizedDescription)"
        }
    }

    private func handleDrop(providers: [NSItemProvider]) -> Bool {
        guard let provider = providers.first else { return false }
        if provider.canLoadObject(ofClass: URL.self) {
            _ = provider.loadObject(ofClass: URL.self) { url, _ in
                guard let url else { return }
                Task { @MainActor in
                    loadFile(url: url)
                }
            }
            return true
        }
        return false
    }
}

struct MarkdownPlaygroundView: View {
    @State private var markdownText = SampleData.markdownSample
    @State private var useLightTheme = false
    @State private var fontSize: Double = 14
    @State private var fileURL: URL?
    @State private var loadError: String?
    @State private var isDropTargeted = false

    private var theme: MarkdownTheme {
        useLightTheme ? .light : .dark
    }

    var body: some View {
        HSplitView {
            VStack(spacing: 12) {
                HStack(spacing: 12) {
                    Toggle("Light Theme", isOn: $useLightTheme)
                    HStack {
                        Text("Font")
                        Slider(value: $fontSize, in: 11...20, step: 1)
                        Text("\(Int(fontSize))")
                            .frame(width: 28, alignment: .trailing)
                    }
                    Spacer()
                    Button("Open File") {
                        openFilePanel()
                    }
                    .buttonStyle(.bordered)
                    Button("Reset") {
                        markdownText = SampleData.markdownSample
                        fileURL = nil
                        loadError = nil
                    }
                }

                if let fileURL {
                    Text(fileURL.path)
                        .font(.caption)
                        .foregroundStyle(.secondary)
                        .lineLimit(2)
                }

                if let loadError {
                    Text(loadError)
                        .font(.caption)
                        .foregroundStyle(.red)
                        .fixedSize(horizontal: false, vertical: true)
                }

                TextEditor(text: $markdownText)
                    .font(.system(size: 12, design: .monospaced))
                    .frame(minWidth: 320)
                    .border(Color(nsColor: .separatorColor))
            }
            .padding(16)

            ZStack {
                VVMarkdownView(
                    content: markdownText,
                    theme: theme,
                    font: NSFont.systemFont(ofSize: fontSize)
                )

                if isDropTargeted {
                    RoundedRectangle(cornerRadius: 12)
                        .stroke(Color.accentColor, lineWidth: 2)
                        .padding(16)
                        .allowsHitTesting(false)
                }
            }
            .onDrop(of: [UTType.fileURL], isTargeted: $isDropTargeted) { providers in
                handleDrop(providers: providers)
            }
        }
    }

    private func openFilePanel() {
        let panel = NSOpenPanel()
        panel.canChooseFiles = true
        panel.canChooseDirectories = false
        panel.allowsMultipleSelection = false
        panel.title = "Open Markdown File"
        if panel.runModal() == .OK, let url = panel.url {
            loadFile(url: url)
        }
    }

    private func loadFile(url: URL) {
        do {
            markdownText = try String(contentsOf: url, encoding: .utf8)
            fileURL = url
            loadError = nil
        } catch {
            loadError = "Failed to load file: \(error.localizedDescription)"
        }
    }

    private func handleDrop(providers: [NSItemProvider]) -> Bool {
        guard let provider = providers.first else { return false }
        if provider.canLoadObject(ofClass: URL.self) {
            _ = provider.loadObject(ofClass: URL.self) { url, _ in
                guard let url else { return }
                Task { @MainActor in
                    loadFile(url: url)
                }
            }
            return true
        }
        return false
    }
}

struct MermaidPlaygroundView: View {
    @State private var baseText = SampleData.mermaidSample
    @State private var useLightTheme = false
    @State private var fontSize: Double = 14
    @State private var repeatCount = 2

    private var theme: MarkdownTheme {
        useLightTheme ? .light : .dark
    }

    private var renderedText: String {
        guard repeatCount > 1 else { return baseText }
        return Array(repeating: baseText, count: repeatCount).joined(separator: "\n\n")
    }

    var body: some View {
        HSplitView {
            VStack(spacing: 12) {
                HStack(spacing: 12) {
                    Toggle("Light Theme", isOn: $useLightTheme)
                    HStack {
                        Text("Font")
                        Slider(value: $fontSize, in: 11...20, step: 1)
                        Text("\(Int(fontSize))")
                            .frame(width: 28, alignment: .trailing)
                    }
                    Spacer()
                    Stepper("Repeat \(repeatCount)x", value: $repeatCount, in: 1...6)
                }

                TextEditor(text: $baseText)
                    .font(.system(size: 12, design: .monospaced))
                    .frame(minWidth: 320)
                    .border(Color(nsColor: .separatorColor))

                Text("Rendered blocks: \(repeatCount)")
                    .font(.caption)
                    .foregroundStyle(.secondary)
            }
            .padding(16)

            VVMarkdownView(
                content: renderedText,
                theme: theme,
                font: NSFont.systemFont(ofSize: fontSize)
            )
        }
    }
}

enum PrimitiveShowcase: String, CaseIterable, Identifiable {
    case textRun = "Text Run"
    case textLayout = "Text Layout"
    case selection = "Selection"
    case quad = "Quad"
    case gradientQuad = "Gradient Quad"
    case shadowQuad = "Shadow Quad"
    case line = "Line"
    case bullet = "Bullet"
    case image = "Image"
    case blockQuoteBorder = "Block Quote"
    case tableLine = "Table Lines"
    case pieSlice = "Pie Chart"
    case underline = "Underline"
    case path = "Path"
    case border = "Border"
    case dashedLine = "Dashed Line"
    case transform = "Transform"
    case rule = "Rule"
    case stack = "Stack"
    case layer = "Layer"
    case vvview = "VVView DSL"
    case combined = "All Combined"

    var id: String { rawValue }

    var description: String {
        switch self {
        case .textRun: return "Glyph-based text with styles, links, and strikethrough"
        case .textLayout: return "Multi-line text layout with VVTextLine"
        case .selection: return "Selection quads and cursor rendering"
        case .quad: return "Solid color rectangles with optional corner radius"
        case .gradientQuad: return "Horizontal and vertical gradient fills"
        case .shadowQuad: return "Layered quads approximating a soft shadow"
        case .line: return "Line segments with configurable thickness"
        case .bullet: return "Disc, circle, square, number, and checkbox markers"
        case .image: return "Image placeholder frames with corner radius"
        case .blockQuoteBorder: return "Left border used for block quotes"
        case .tableLine: return "Grid lines for table rendering"
        case .pieSlice: return "Pie chart segments with start/end angles"
        case .underline: return "Straight and wavy underlines for text decoration"
        case .path: return "Vector paths with bezier curves, fills, and strokes"
        case .border: return "Per-corner radii and per-side borders on quads"
        case .dashedLine: return "Dashed and patterned line styles"
        case .transform: return "2D affine transforms: rotate, scale, translate"
        case .rule: return "VDivider horizontal separators via VVView DSL"
        case .stack: return "VVStack/VVHStack layout via VVView DSL"
        case .layer: return "VVZStack overlapping composition via VVView DSL"
        case .vvview: return "Declarative cards and layouts with VVView DSL"
        case .combined: return "All primitives rendered together"
        }
    }
}

struct PrimitivesPlaygroundView: View {
    @State private var selected: PrimitiveShowcase = .quad
    @State private var useDarkBackground = true
    @State private var cornerRadius: Double = 12

    private var configuration: PrimitiveSceneConfiguration {
        PrimitiveSceneConfiguration(
            backgroundColor: useDarkBackground ? .darkBackground : .rgba(0.96, 0.96, 0.97),
            showcase: selected,
            cornerRadius: CGFloat(cornerRadius)
        )
    }

    var body: some View {
        HSplitView {
            VStack(alignment: .leading, spacing: 0) {
                VStack(alignment: .leading, spacing: 10) {
                    Text("Primitives")
                        .font(.headline)

                    Toggle("Dark Background", isOn: $useDarkBackground)

                    HStack {
                        Text("Corner Radius")
                        Slider(value: $cornerRadius, in: 0...28, step: 1)
                        Text("\(Int(cornerRadius))")
                            .frame(width: 28, alignment: .trailing)
                    }
                }
                .padding(.horizontal, 16)
                .padding(.top, 16)
                .padding(.bottom, 12)

                Divider()

                List(PrimitiveShowcase.allCases, selection: $selected) { item in
                    VStack(alignment: .leading, spacing: 2) {
                        Text(item.rawValue)
                            .fontWeight(item == selected ? .semibold : .regular)
                        Text(item.description)
                            .font(.caption)
                            .foregroundStyle(.secondary)
                            .lineLimit(2)
                    }
                    .padding(.vertical, 4)
                    .tag(item)
                }
                .listStyle(.sidebar)
            }
            .frame(minWidth: 220, idealWidth: 260, maxWidth: 320)

            PrimitiveSceneRepresentable(configuration: configuration)
        }
    }
}

struct PrimitiveSceneConfiguration: Equatable {
    var backgroundColor: SIMD4<Float>
    var showcase: PrimitiveShowcase
    var cornerRadius: CGFloat
}

struct PrimitiveSceneRepresentable: NSViewRepresentable {
    let configuration: PrimitiveSceneConfiguration

    func makeNSView(context: Context) -> PrimitiveSceneView {
        PrimitiveSceneView(configuration: configuration)
    }

    func updateNSView(_ nsView: PrimitiveSceneView, context: Context) {
        nsView.update(configuration: configuration)
    }
}

final class PrimitiveSceneView: NSView, VVChatTimelineRenderDataSource {
    private let metalView: VVChatTimelineMetalView
    private var configuration: PrimitiveSceneConfiguration
    private var scene: VVScene
    private var lastSize: CGSize = .zero

    override var isFlipped: Bool { true }

    init(configuration: PrimitiveSceneConfiguration) {
        self.configuration = configuration
        self.scene = SampleData.primitivesScene(size: .zero, configuration: configuration)
        self.metalView = VVChatTimelineMetalView(frame: .zero, font: .systemFont(ofSize: 14))
        super.init(frame: .zero)
        wantsLayer = true
        metalView.renderDataSource = self
        addSubview(metalView)
    }

    required init?(coder: NSCoder) {
        let configuration = PrimitiveSceneConfiguration(
            backgroundColor: SIMD4(0.08, 0.09, 0.1, 1),
            showcase: .combined,
            cornerRadius: 12
        )
        self.configuration = configuration
        self.scene = SampleData.primitivesScene(size: .zero, configuration: configuration)
        self.metalView = VVChatTimelineMetalView(frame: .zero, font: .systemFont(ofSize: 14))
        super.init(coder: coder)
        wantsLayer = true
        metalView.renderDataSource = self
        addSubview(metalView)
    }

    func update(configuration: PrimitiveSceneConfiguration) {
        self.configuration = configuration
        rebuildScene(force: true)
    }

    override func layout() {
        super.layout()
        metalView.frame = bounds
        rebuildScene(force: false)
    }

    private func rebuildScene(force: Bool) {
        guard force || bounds.size != lastSize else {
            metalView.setNeedsDisplay(bounds)
            return
        }
        lastSize = bounds.size
        scene = SampleData.primitivesScene(size: bounds.size, configuration: configuration)
        metalView.setNeedsDisplay(bounds)
    }

    var renderItemCount: Int { 1 }

    func renderItem(at index: Int) -> VVChatTimelineRenderItem? {
        guard index == 0 else { return nil }
        return VVChatTimelineRenderItem(id: "primitives", frame: bounds, contentOffset: .zero, scene: scene)
    }

    var viewportRect: CGRect { bounds }

    var backgroundColor: SIMD4<Float> { configuration.backgroundColor }

    func texture(for url: String) -> MTLTexture? {
        nil
    }
}

struct ChatPlaygroundView: View {
    @State private var controller = VVChatTimelineController(
        style: SampleData.chatStyle(dark: true, fontSize: 14),
        renderWidth: 0
    )
    @State private var didSeed = false
    @State private var useLightTheme = false
    @State private var fontSize: Double = 14
    @State private var draftID: String?
    @State private var draftContent = ""
    @State private var userIndex = 0
    @State private var assistantIndex = 0
    @State private var autoTurnIndex = 0
    @State private var simulationTask: Task<Void, Never>?
    @State private var isAutoRunning = false
    @State private var streamResponses = true
    @State private var chunkDelay: Double = 0.06
    @State private var minChunkSize = 8
    @State private var maxChunkSize = 28
    @State private var pauseBetweenMessages: Double = 0.8
    @State private var useComplexResponses = true
    @State private var followStreaming = true
    @State private var includeToolCalls = true

    var body: some View {
        HSplitView {
            VStack(alignment: .leading, spacing: 12) {
                Text("Chat")
                    .font(.headline)

                Toggle("Light Theme", isOn: $useLightTheme)
                HStack {
                    Text("Font")
                    Slider(value: $fontSize, in: 11...20, step: 1)
                    Text("\(Int(fontSize))")
                        .frame(width: 28, alignment: .trailing)
                }

                Divider()

                Button("Seed Messages") {
                    seedMessages()
                }

                Button("Append User Message") {
                    appendUserMessage()
                }

                Button("Append Assistant Message") {
                    appendAssistantMessage()
                }

                Divider()

                Toggle("Stream Responses", isOn: $streamResponses)
                Toggle("Complex Responses", isOn: $useComplexResponses)
                Toggle("Follow Stream", isOn: $followStreaming)
                Toggle("Include Tool Calls", isOn: $includeToolCalls)

                HStack {
                    Text("Chunk Delay")
                    Slider(value: $chunkDelay, in: 0.02...0.2, step: 0.01)
                    Text(String(format: "%.02fs", chunkDelay))
                        .frame(width: 52, alignment: .trailing)
                }

                HStack {
                    Text("Chunk Size")
                    Stepper(value: $minChunkSize, in: 2...60) {
                        Text("\(minChunkSize)")
                            .frame(width: 28, alignment: .trailing)
                    }
                    Text("to")
                    Stepper(value: $maxChunkSize, in: minChunkSize...80) {
                        Text("\(maxChunkSize)")
                            .frame(width: 28, alignment: .trailing)
                    }
                }

                HStack {
                    Text("Pause")
                    Slider(value: $pauseBetweenMessages, in: 0.2...2.0, step: 0.1)
                    Text(String(format: "%.01fs", pauseBetweenMessages))
                        .frame(width: 44, alignment: .trailing)
                }

                Button("Stream Assistant Response") {
                    Task { await streamNextAssistantResponse() }
                }

                Button("Run Tool Call Turn") {
                    Task { await runToolCallTurn() }
                }

                Divider()

                HStack {
                    Button(isAutoRunning ? "Stop Auto" : "Start Auto") {
                        isAutoRunning ? stopAutoSimulation() : startAutoSimulation()
                    }
                    .buttonStyle(.borderedProminent)

                    Button("Step Script") {
                        Task { await runSingleAutoStep() }
                    }
                }

                Divider()

                Button("Clear") {
                    controller.setMessages([], scrollToBottom: true)
                }

                Spacer()
            }
            .padding(16)
            .frame(minWidth: 240, idealWidth: 280, maxWidth: 340)

            ChatTimelineRepresentable(controller: controller)
        }
        .onAppear {
            if !didSeed {
                seedMessages()
                didSeed = true
            }
        }
        .onDisappear {
            stopAutoSimulation()
        }
        .onChange(of: useLightTheme) { _ in
            updateChatStyle()
        }
        .onChange(of: fontSize) { _ in
            updateChatStyle()
        }
    }

    private func updateChatStyle() {
        controller.updateStyle(SampleData.chatStyle(dark: !useLightTheme, fontSize: fontSize))
    }

    private func seedMessages() {
        controller.setMessages(SampleData.chatMessages(), scrollToBottom: true)
    }

    private func appendUserMessage(content: String? = nil) {
        let message = content ?? SampleData.userMessages[userIndex % SampleData.userMessages.count]
        if content == nil {
            userIndex += 1
        }
        controller.appendMessage(
            VVChatMessage(role: .user, state: .final, content: message, timestamp: Date())
        )
    }

    private func appendAssistantMessage(content: String? = nil) {
        let message = content ?? assistantResponse(forIndex: assistantIndex)
        if content == nil {
            assistantIndex += 1
        }
        controller.appendMessage(
            VVChatMessage(role: .assistant, state: .final, content: message, timestamp: Date())
        )
    }

    private func appendSystemMessage(content: String) {
        controller.appendMessage(
            VVChatMessage(role: .system, state: .final, content: content, timestamp: Date())
        )
    }

    private func startDraft() {
        draftContent = SampleData.draftSteps.first ?? ""
        draftID = controller.beginStreamingAssistantMessage(content: draftContent)
    }

    private func appendDraft() {
        guard let draftID else { return }
        let nextIndex = draftContent.split(separator: "\n").count
        if nextIndex < SampleData.draftSteps.count {
            draftContent += "\n" + SampleData.draftSteps[nextIndex]
            controller.updateDraftMessage(id: draftID, content: draftContent, throttle: false)
        }
    }

    private func finalizeDraft() {
        guard let draftID else { return }
        controller.finalizeMessage(id: draftID, content: draftContent)
        self.draftID = nil
        draftContent = ""
    }

    private func startAutoSimulation() {
        guard !isAutoRunning else { return }
        isAutoRunning = true
        simulationTask?.cancel()
        simulationTask = Task {
            while !Task.isCancelled {
                let running = await MainActor.run { isAutoRunning }
                if !running { break }
                await runSingleAutoStep()
                try? await Task.sleep(nanoseconds: UInt64(pauseBetweenMessages * 1_000_000_000))
            }
        }
    }

    private func stopAutoSimulation() {
        isAutoRunning = false
        simulationTask?.cancel()
        simulationTask = nil
    }

    private func runSingleAutoStep() async {
        if useComplexResponses && includeToolCalls {
            await runToolCallTurn()
            return
        }

        let turn = nextAutoTurn()
        await MainActor.run {
            appendUserMessage(content: turn.user)
        }

        if streamResponses {
            await streamAssistantMessage(turn.assistant)
        } else {
            await MainActor.run {
                appendAssistantMessage(content: turn.assistant)
            }
        }
    }

    private func streamNextAssistantResponse() async {
        if useComplexResponses && includeToolCalls {
            await runToolCallTurn()
            return
        }
        let response = await MainActor.run { assistantResponse(forIndex: assistantIndex) }
        await streamAssistantMessage(response)
        await MainActor.run { assistantIndex += 1 }
    }

    private func runToolCallTurn() async {
        let turn = nextToolTurn()

        await MainActor.run {
            appendUserMessage(content: turn.user)
        }

        if streamResponses {
            await streamAssistantMessage(turn.preface)
        } else {
            await MainActor.run {
                appendAssistantMessage(content: turn.preface)
            }
        }

        await MainActor.run {
            appendAssistantMessage(content: SampleData.toolCallMessage(
                id: turn.callID,
                name: turn.toolName,
                argumentsJSON: turn.argumentsJSON
            ))
        }

        try? await Task.sleep(nanoseconds: UInt64(max(0.05, chunkDelay) * 1_000_000_000))

        await MainActor.run {
            appendSystemMessage(content: SampleData.toolResultMessage(
                id: turn.callID,
                toolName: turn.toolName,
                resultJSON: turn.resultJSON
            ))
        }

        if streamResponses {
            await streamAssistantMessage(turn.followup)
        } else {
            await MainActor.run {
                appendAssistantMessage(content: turn.followup)
            }
        }
    }

    private func streamAssistantMessage(_ content: String) async {
        let chunks = chunkedSegments(for: content)
        let draftID = await MainActor.run {
            let shouldFollowNow = followStreaming && controller.state.shouldAutoFollow
            if shouldFollowNow {
                controller.jumpToLatest()
            }
            return controller.beginStreamingAssistantMessage(content: "")
        }
        for chunk in chunks {
            if Task.isCancelled { break }
            await MainActor.run {
                controller.appendToDraftMessage(id: draftID, chunk: chunk, throttle: false)
            }
            try? await Task.sleep(nanoseconds: UInt64(chunkDelay * 1_000_000_000))
        }
        await MainActor.run {
            let finalContent = controller.messages.first(where: { $0.id == draftID })?.content ?? content
            controller.finalizeMessage(id: draftID, content: finalContent)
        }
    }

    private func assistantResponse(forIndex index: Int) -> String {
        let responses = useComplexResponses ? SampleData.complexAssistantResponses : SampleData.assistantMessages
        guard !responses.isEmpty else { return "" }
        let base = responses[index % responses.count]
        guard index >= responses.count else { return base }
        return """
        \(base)

        _Update \(index + 1): appended turn in infinite mode._
        """
    }

    private func nextAutoTurn() -> SampleData.AutoTurn {
        let turns = useComplexResponses ? SampleData.autoComplexTurns : SampleData.autoSimpleTurns
        guard !turns.isEmpty else { return .init(user: "", assistant: "") }
        let index = autoTurnIndex
        let turn = turns[index % turns.count]
        autoTurnIndex += 1
        guard index >= turns.count else { return turn }
        return .init(
            user: "\(turn.user) (turn \(index + 1))",
            assistant: """
            \(turn.assistant)

            _Turn \(index + 1): continued transcript; previous messages are preserved._
            """
        )
    }

    private func nextToolTurn() -> SampleData.ToolTurn {
        let turns = SampleData.toolTurns
        guard !turns.isEmpty else {
            return .init(
                user: "",
                preface: "",
                callID: UUID().uuidString,
                toolName: "",
                argumentsJSON: "{}",
                resultJSON: "{}",
                followup: ""
            )
        }
        let index = autoTurnIndex
        let turn = turns[index % turns.count]
        autoTurnIndex += 1
        let sequence = index + 1
        let user = index < turns.count ? turn.user : "\(turn.user) (turn \(sequence))"
        let followup = index < turns.count
            ? turn.followup
            : """
            \(turn.followup)

            _Turn \(sequence): continued transcript; previous messages are preserved._
            """
        return .init(
            user: user,
            preface: turn.preface,
            callID: "\(turn.callID)_\(sequence)",
            toolName: turn.toolName,
            argumentsJSON: turn.argumentsJSON,
            resultJSON: turn.resultJSON,
            followup: followup
        )
    }

    private func chunkedSegments(for text: String) -> [String] {
        guard !text.isEmpty else { return [] }
        var segments: [String] = []
        let scalars = Array(text)
        var index = 0
        while index < scalars.count {
            let jitter = Int.random(in: minChunkSize...maxChunkSize)
            let end = min(index + jitter, scalars.count)
            var slice = String(scalars[index..<end])
            if end < scalars.count {
                if let lastSpace = slice.lastIndex(where: { $0.isWhitespace }) {
                    let prefix = String(slice[..<lastSpace])
                    if !prefix.isEmpty {
                        slice = prefix
                    }
                }
            }
            if slice.isEmpty {
                slice = String(scalars[index..<end])
            }
            segments.append(slice)
            index += slice.count
        }
        return segments
    }
}

struct ChatTimelineRepresentable: NSViewRepresentable {
    let controller: VVChatTimelineController

    func makeNSView(context: Context) -> VVChatTimelineView {
        let view = VVChatTimelineView(frame: .zero)
        view.controller = controller
        return view
    }

    func updateNSView(_ nsView: VVChatTimelineView, context: Context) {
        if nsView.controller !== controller {
            nsView.controller = controller
        }
    }
}

enum SampleData {
    struct AutoTurn {
        let user: String
        let assistant: String
    }

    struct ToolTurn {
        let user: String
        let preface: String
        let callID: String
        let toolName: String
        let argumentsJSON: String
        let resultJSON: String
        let followup: String
    }

    static let swiftSample = """
    import Foundation

    struct Person {
        let name: String
        let age: Int
    }

    func greet(_ person: Person) -> String {
        let greeting = "Hello, \\(person.name)!"
        return "\\(greeting) You are \\(person.age)."
    }

    let person = Person(name: "Lina", age: 29)
    print(greet(person))

    for index in 1...3 {
        print("Item \\(index)")
    }
    """

    static let pythonSample = """
    from dataclasses import dataclass

    @dataclass
    class Person:
        name: str
        age: int

    def greet(person: Person) -> str:
        return f"Hello, {person.name}! You are {person.age}."

    person = Person(name="Lina", age=29)
    print(greet(person))
    """

    static let jsonSample = """
    {
      "name": "VVDevKit",
      "features": ["Code", "Markdown", "Chat"],
      "version": "0.1.0",
      "meta": {
        "platforms": ["macOS", "iOS"],
        "experimental": true
      }
    }
    """

    static let markdownSample = """
    # VVDevKit Markdown Demo

    VVDevKit renders markdown with Metal. This sample includes: **bold**, _italic_, `inline code`, and links.

    > Block quote with a second line.

    ## Lists

    - Plain item
    - [x] Checked item
    - [ ] Unchecked item

    ## Code Blocks

    ```swift
    struct Greeting {
        let message: String
    }
    ```

    ```python
    def add(a, b):
        return a + b
    ```

    ## Table

    | Name | Type | Status |
    | --- | --- | --- |
    | VVCode | Editor | Stable |
    | VVMarkdown | Renderer | Beta |

    ## Math

    $$E = mc^2$$

    ## Mermaid

    ```mermaid
    sequenceDiagram
      Alice->>Bob: Hello Bob
      Bob-->>Alice: Hi Alice
    ```

    ---

    End of sample.
    """

    static let mermaidSample = """
    # Mermaid Stress Sample

    ```mermaid
    flowchart LR
      A[Load] --> B{Parse}
      B -->|OK| C[Render]
      B -->|Fail| D[Report]
    ```

    ```mermaid
    sequenceDiagram
      participant UI
      participant Engine
      UI->>Engine: render(markdown)
      Engine-->>UI: scene
    ```

    ```mermaid
    classDiagram
      class VVScene
      class VVPrimitive
      VVScene --> VVPrimitive
    ```

    ```mermaid
    stateDiagram-v2
      [*] --> Idle
      Idle --> Rendering: start
      Rendering --> Idle: done
    ```

    ```mermaid
    gantt
      title Release Plan
      dateFormat  YYYY-MM-DD
      section Alpha
      Parse :a1, 2025-01-01, 7d
      Render :after a1, 5d
    ```

    ```mermaid
    pie title Allocation
      "Code" : 45
      "Docs" : 15
      "Tests" : 20
      "Perf" : 20
    ```

    ```mermaid
    gitGraph
      commit
      commit
      branch feature
      checkout feature
      commit
      checkout main
      merge feature
    ```
    """

    static let gitDiff = """
    diff --git a/Sample.swift b/Sample.swift
    index 1234567..89abcde 100644
    --- a/Sample.swift
    +++ b/Sample.swift
    @@ -1,7 +1,9 @@
     import Foundation
    +import SwiftUI
    
    func greet(_ name: String) -> String {
    -    return "Hello, \\(name)!"
    +    let greeting = "Hello, \\(name)!"
    +    return greeting
     }
    """

    static let gitBlame: [VVBlameInfo] = {
        let now = Date()
        return [
            VVBlameInfo(lineNumber: 1, commit: "a1b2c3d", author: "Mira", date: now.addingTimeInterval(-3600 * 24 * 3), summary: "Add imports"),
            VVBlameInfo(lineNumber: 2, commit: "a1b2c3d", author: "Mira", date: now.addingTimeInterval(-3600 * 24 * 3), summary: "Add imports"),
            VVBlameInfo(lineNumber: 4, commit: "f9e8d7c", author: "Jin", date: now.addingTimeInterval(-3600 * 24 * 1), summary: "Refactor greeting"),
            VVBlameInfo(lineNumber: 5, commit: "f9e8d7c", author: "Jin", date: now.addingTimeInterval(-3600 * 24 * 1), summary: "Refactor greeting"),
            VVBlameInfo(lineNumber: 10, commit: "0000000", author: "You", date: now, summary: "WIP", isUncommitted: true)
        ]
    }()

    static let userMessages: [String] = [
        "Can you show me the API surface?",
        "Let's test markdown rendering with tables.",
        "Does the editor support wrapping and blame?",
        "Can we stress the chat timeline layout?",
        "Show a tiny Mermaid diagram in chat.",
        "How do system messages look?"
    ]

    static let assistantMessages: [String] = [
        "Sure! Here is a quick walkthrough of VVDevKit components and how they connect.",
        "Markdown supports tables, math, and mermaid diagrams. Try editing the sample.",
        "Inline blame is available when you provide blame info and enable it in configuration.",
        "The chat timeline is virtualized and follows streaming updates when pinned.",
        "Mermaid blocks are rendered with a lightweight parser and layout engine.",
        "System messages render without bubbles and can appear between turns."
    ]

    static let autoSimpleTurns: [AutoTurn] = [
        AutoTurn(
            user: "Can you show me the API surface?",
            assistant: "Sure! Here is a quick walkthrough of VVDevKit components and how they connect."
        ),
        AutoTurn(
            user: "Let's test markdown rendering with tables.",
            assistant: "Markdown supports tables, math, and mermaid diagrams. Try editing the sample."
        ),
        AutoTurn(
            user: "Does the editor support wrapping and blame?",
            assistant: "Inline blame is available when you provide blame info and enable it in configuration."
        ),
        AutoTurn(
            user: "Can we stress the chat timeline layout?",
            assistant: "The chat timeline is virtualized and follows streaming updates when pinned."
        ),
        AutoTurn(
            user: "Show a tiny Mermaid diagram in chat.",
            assistant: "Mermaid blocks are rendered with a lightweight parser and layout engine."
        ),
        AutoTurn(
            user: "How do system messages look?",
            assistant: "System messages render without bubbles and can appear between turns."
        )
    ]

    static let complexAssistantResponses: [String] = [
        """
        Here is a structured response with mixed content:

        1) Summary
        - ✅ Runs on macOS
        - ✅ Metal-backed rendering
        - ⚠️ Dynamic grammars need dylibs

        2) Inline examples: `VVCodeView`, `VVMarkdownView`, `VVChatTimelineView`

        ```swift
        struct Demo {
            let title: String
            let enabled: Bool
        }
        ```

        ```json
        {
          "module": "VVMarkdown",
          "features": ["tables", "math", "mermaid"]
        }
        ```

        > Tip: keep bundle frameworks next to the app when loading grammars.

        $$E = mc^2$$
        """,
        """
        Let’s validate the streaming pipeline:

        - build draft
        - append chunks
        - finalize message

        ```diff
        - return "Hello, world"
        + let greeting = "Hello, world"
        + return greeting
        ```

        | Step | Status |
        | --- | --- |
        | Parse | ✅ |
        | Layout | ✅ |
        | Render | ✅ |

        ```mermaid
        sequenceDiagram
          UI->>Engine: updateDraftMessage()
          Engine-->>UI: scene diff
        ```
        """,
        """
        Long form text to stress wrapping and selection.

        Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer at justo vel augue
        sodales gravida. Aenean ut magna et lectus interdum tristique. Vivamus quis orci
        vitae turpis commodo pulvinar. Proin a metus orci.

        - bullet 1
        - bullet 2
        - bullet 3

        ```bash
        swift build --product TreeSitterSwift
        ```
        """,
        """
        Quick checklist:

        - Paragraphs, lists, and links
        - Inline code: `VVChatTimelineView`
        - Block quote below

        > Keep responses crisp while streaming.

        ```swift
        enum Mode { case read, write }
        ```
        """,
        """
        Pipeline snapshot:

        | Stage | Status |
        | --- | --- |
        | Parse | ✅ |
        | Layout | ✅ |
        | Render | ✅ |

        ```mermaid
        flowchart LR
          A[Input] --> B[Parse]
          B --> C[Layout]
          C --> D[Render]
        ```
        """
    ]

    static let autoComplexTurns: [AutoTurn] = [
        AutoTurn(
            user: "Give me a mixed markdown response with code and math.",
            assistant: complexAssistantResponses[0]
        ),
        AutoTurn(
            user: "Validate streaming, tables, and a mermaid diagram.",
            assistant: complexAssistantResponses[1]
        ),
        AutoTurn(
            user: "Stress long-form wrapping with lists.",
            assistant: complexAssistantResponses[2]
        ),
        AutoTurn(
            user: "Show a quick checklist with a quote and code.",
            assistant: complexAssistantResponses[3]
        ),
        AutoTurn(
            user: "Render a pipeline table and flowchart.",
            assistant: complexAssistantResponses[4]
        )
    ]

    static let toolTurns: [ToolTurn] = [
        ToolTurn(
            user: "What is the weather in Tokyo and should I bring an umbrella?",
            preface: "I can check live weather first and then answer with a recommendation.",
            callID: "call_weather_tokyo",
            toolName: "get_weather",
            argumentsJSON: """
            {
              "city": "Tokyo",
              "unit": "celsius"
            }
            """,
            resultJSON: """
            {
              "city": "Tokyo",
              "temperature_c": 21,
              "condition": "Light rain",
              "precip_probability": 0.62
            }
            """,
            followup: """
            Live weather says **21°C** with light rain and ~62% precipitation probability.
            Bring a compact umbrella.
            """
        ),
        ToolTurn(
            user: "Find any failing CI checks for branch feat/chat-timeline.",
            preface: "I’ll query CI status for that branch before summarizing.",
            callID: "call_ci_status",
            toolName: "fetch_ci_status",
            argumentsJSON: """
            {
              "branch": "feat/chat-timeline"
            }
            """,
            resultJSON: """
            {
              "branch": "feat/chat-timeline",
              "workflows": [
                { "name": "unit-tests", "status": "failed", "failed_jobs": 2 },
                { "name": "lint", "status": "passed", "failed_jobs": 0 }
              ]
            }
            """,
            followup: """
            CI has one failing workflow:

            - `unit-tests` failed with 2 jobs
            - `lint` passed

            I’d inspect the unit-test logs first.
            """
        ),
        ToolTurn(
            user: "Can you look up docs for `MarkdownLayoutEngine` and summarize key APIs?",
            preface: "I’ll run a docs lookup, then summarize the high-value APIs.",
            callID: "call_docs_lookup",
            toolName: "search_docs",
            argumentsJSON: """
            {
              "query": "MarkdownLayoutEngine API"
            }
            """,
            resultJSON: """
            {
              "matches": [
                "layout(_:)",
                "updateContentWidth(_:)",
                "updateImageSizeProvider(_:)",
                "adjustParagraphImageSpacing(in:)"
              ]
            }
            """,
            followup: """
            Key APIs to use:

            1. `layout(_:)` to produce `MarkdownLayout`
            2. `updateContentWidth(_:)` when viewport changes
            3. `updateImageSizeProvider(_:)` for async image sizing
            4. `adjustParagraphImageSpacing(in:)` before rendering
            """
        )
    ]

    static func toolCallMessage(id: String, name: String, argumentsJSON: String) -> String {
        """
        Tool call started:

        ```json
        {
          "type": "tool_call",
          "id": "\(id)",
          "name": "\(name)",
          "arguments": \(argumentsJSON)
        }
        ```
        """
    }

    static func toolResultMessage(id: String, toolName: String, resultJSON: String) -> String {
        """
        Tool result:

        ```json
        {
          "type": "tool_result",
          "tool_call_id": "\(id)",
          "name": "\(toolName)",
          "payload": \(resultJSON)
        }
        ```
        """
    }

    static let draftSteps: [String] = [
        "Streaming draft message...",
        "Adding a second line in the draft.",
        "Finishing up with a final thought."
    ]

    static func chatMessages() -> [VVChatMessage] {
        let now = Date()
        return [
            VVChatMessage(role: .system, state: .final, content: "VVDevKit demo chat initialized.", timestamp: now),
            VVChatMessage(role: .user, state: .final, content: userMessages[0], timestamp: now.addingTimeInterval(5)),
            VVChatMessage(role: .assistant, state: .final, content: assistantMessages[0], timestamp: now.addingTimeInterval(10)),
            VVChatMessage(role: .user, state: .final, content: userMessages[1], timestamp: now.addingTimeInterval(15)),
            VVChatMessage(role: .assistant, state: .final, content: assistantMessages[1], timestamp: now.addingTimeInterval(20))
        ]
    }

    static func chatStyle(dark: Bool, fontSize: Double) -> VVChatTimelineStyle {
        let theme = dark ? MarkdownTheme.dark : MarkdownTheme.light
        let baseFont = NSFont.systemFont(ofSize: fontSize)
        let background: SIMD4<Float> = dark ? .darkBackground : .rgba(0.96, 0.96, 0.97)
        let bubbleColor: SIMD4<Float> = dark ? .rgba(0.18, 0.26, 0.38) : .rgba(0.82, 0.9, 1)
        let headerColor: SIMD4<Float> = dark ? .rgba(0.75, 0.8, 0.9) : .rgba(0.25, 0.3, 0.35)
        let timestampColor: SIMD4<Float> = dark ? .gray60 : .gray40
        return VVChatTimelineStyle(
            theme: theme,
            baseFont: baseFont,
            headerTextColor: headerColor,
            timestampTextColor: timestampColor,
            userBubbleColor: bubbleColor,
            userInsets: VVInsets(top: 6, left: 120, bottom: 6, right: 16),
            assistantInsets: VVInsets(top: 6, left: 16, bottom: 6, right: 120),
            backgroundColor: background
        )
    }

    static func primitivesScene(size: CGSize, configuration: PrimitiveSceneConfiguration) -> VVScene {
        switch configuration.showcase {
        case .textRun: return textRunScene(size: size, config: configuration)
        case .textLayout: return textLayoutScene(size: size, config: configuration)
        case .selection: return selectionScene(size: size, config: configuration)
        case .quad: return quadScene(size: size, config: configuration)
        case .gradientQuad: return gradientQuadScene(size: size, config: configuration)
        case .shadowQuad: return shadowQuadScene(size: size, config: configuration)
        case .line: return lineScene(size: size, config: configuration)
        case .bullet: return bulletScene(size: size, config: configuration)
        case .image: return imageScene(size: size, config: configuration)
        case .blockQuoteBorder: return blockQuoteBorderScene(size: size, config: configuration)
        case .tableLine: return tableLineScene(size: size, config: configuration)
        case .pieSlice: return pieSliceScene(size: size, config: configuration)
        case .underline: return underlineScene(size: size, config: configuration)
        case .path: return pathScene(size: size, config: configuration)
        case .border: return borderScene(size: size, config: configuration)
        case .dashedLine: return dashedLineScene(size: size, config: configuration)
        case .transform: return transformScene(size: size, config: configuration)
        case .rule: return ruleScene(size: size, config: configuration)
        case .stack: return stackScene(size: size, config: configuration)
        case .layer: return layerScene(size: size, config: configuration)
        case .vvview: return vvviewScene(size: size, config: configuration)
        case .combined: return combinedScene(size: size, config: configuration)
        }
    }

    // MARK: - Glyph Helpers

    /// Creates glyphs for the given text. `origin` is the top-left of the line area.
    /// Glyph position.y is set to the baseline (origin.y + ascent) since the Metal renderer
    /// interprets position.y as the baseline coordinate.
    private static func makeGlyphs(
        text: String,
        font: NSFont,
        origin: CGPoint,
        color: SIMD4<Float>,
        variant: VVFontVariant = .regular
    ) -> [VVTextGlyph] {
        let ctFont = font as CTFont
        let chars = Array(text.utf16)
        guard !chars.isEmpty else { return [] }
        var glyphIDs = [CGGlyph](repeating: 0, count: chars.count)
        CTFontGetGlyphsForCharacters(ctFont, chars, &glyphIDs, chars.count)
        var advances = [CGSize](repeating: .zero, count: chars.count)
        CTFontGetAdvancesForGlyphs(ctFont, .horizontal, glyphIDs, &advances, chars.count)

        let fontSize = font.pointSize
        let ascent = CTFontGetAscent(ctFont)
        let lineHeight = ascent + CTFontGetDescent(ctFont) + CTFontGetLeading(ctFont)
        let baselineY = origin.y + ascent
        var result: [VVTextGlyph] = []
        var x = origin.x
        for i in 0..<chars.count {
            let size = CGSize(width: max(advances[i].width, 1), height: lineHeight)
            result.append(VVTextGlyph(
                glyphID: UInt16(glyphIDs[i]),
                position: CGPoint(x: x, y: baselineY),
                size: size,
                color: color,
                fontVariant: variant,
                fontSize: fontSize,
                fontName: font.fontName,
                stringIndex: i
            ))
            x += advances[i].width
        }
        return result
    }

    /// Creates a text run. `origin` is the top-left of the line area.
    /// The run's position is set to origin; lineBounds/runBounds cover the line area.
    private static func makeTextRun(
        text: String,
        font: NSFont,
        origin: CGPoint,
        color: SIMD4<Float>,
        variant: VVFontVariant = .regular,
        isLink: Bool = false,
        isStrikethrough: Bool = false,
        linkURL: String? = nil
    ) -> VVTextRunPrimitive {
        let ctFont = font as CTFont
        let ascent = CTFontGetAscent(ctFont)
        let glyphs = makeGlyphs(text: text, font: font, origin: origin, color: color, variant: variant)
        let width = glyphs.last.map { $0.position.x + $0.size.width - origin.x } ?? 0
        let height = glyphs.first?.size.height ?? font.pointSize * 1.2
        let baselineY = origin.y + ascent
        return VVTextRunPrimitive(
            glyphs: glyphs,
            style: VVTextRunStyle(isStrikethrough: isStrikethrough, isLink: isLink, linkURL: linkURL, color: color),
            lineBounds: CGRect(x: origin.x, y: origin.y, width: width, height: height),
            runBounds: CGRect(x: origin.x, y: origin.y, width: width, height: height),
            position: CGPoint(x: origin.x, y: baselineY),
            fontSize: font.pointSize
        )
    }

    // MARK: - Text Primitive Scenes

    private static func textRunScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let fg = foregroundColor(for: config.backgroundColor)
        let pad: CGFloat = 40
        let lineSpacing: CGFloat = 36
        var y = pad

        let baseFont = NSFont.systemFont(ofSize: 14)
        let boldFont = NSFont.boldSystemFont(ofSize: 14)
        let italicFont = NSFont(descriptor: baseFont.fontDescriptor.withSymbolicTraits(.italic), size: 14) ?? baseFont
        let monoFont = NSFont.monospacedSystemFont(ofSize: 14, weight: .regular)
        let largeBoldFont = NSFont.boldSystemFont(ofSize: 22)
        let smallFont = NSFont.systemFont(ofSize: 11)

        // Row 1: Regular text
        let run1 = makeTextRun(text: "Regular text rendered with VVTextRunPrimitive", font: baseFont, origin: CGPoint(x: pad, y: y), color: fg)
        builder.add(kind: .textRun(run1), zIndex: 1)
        y += lineSpacing

        // Row 2: Bold
        let run2 = makeTextRun(text: "Bold text with semibold font variant", font: boldFont, origin: CGPoint(x: pad, y: y), color: fg, variant: .bold)
        builder.add(kind: .textRun(run2), zIndex: 1)
        y += lineSpacing

        // Row 3: Italic
        let run3 = makeTextRun(text: "Italic text with italic font variant", font: italicFont, origin: CGPoint(x: pad, y: y), color: fg, variant: .italic)
        builder.add(kind: .textRun(run3), zIndex: 1)
        y += lineSpacing

        // Row 4: Monospace
        let run4 = makeTextRun(text: "Monospace: func hello() -> String", font: monoFont, origin: CGPoint(x: pad, y: y), color: SIMD4(0.3, 0.8, 0.6, 1), variant: .monospace)
        builder.add(kind: .textRun(run4), zIndex: 1)
        y += lineSpacing

        // Row 5: Link (underlined)
        let run5 = makeTextRun(text: "This is a link with underline", font: baseFont, origin: CGPoint(x: pad, y: y), color: SIMD4(0.3, 0.6, 0.95, 1), isLink: true, linkURL: "https://example.com")
        builder.add(kind: .textRun(run5), zIndex: 1)
        y += lineSpacing

        // Row 6: Strikethrough
        let run6 = makeTextRun(text: "Strikethrough text with line-through", font: baseFont, origin: CGPoint(x: pad, y: y), color: SIMD4(fg.x, fg.y, fg.z, 0.6), isStrikethrough: true)
        builder.add(kind: .textRun(run6), zIndex: 1)
        y += lineSpacing

        // Row 7: Colored text segments on one line
        let colors: [(String, SIMD4<Float>)] = [
            ("Red ", SIMD4(0.95, 0.3, 0.3, 1)),
            ("Green ", SIMD4(0.3, 0.85, 0.4, 1)),
            ("Blue ", SIMD4(0.3, 0.5, 0.95, 1)),
            ("Yellow ", SIMD4(0.95, 0.85, 0.2, 1)),
            ("Purple", SIMD4(0.7, 0.35, 0.9, 1)),
        ]
        var cx = pad
        for (text, color) in colors {
            let run = makeTextRun(text: text, font: baseFont, origin: CGPoint(x: cx, y: y), color: color)
            builder.add(kind: .textRun(run), zIndex: 1)
            cx += run.runBounds?.width ?? 0
        }
        y += lineSpacing

        // Row 8: Large heading
        let run8 = makeTextRun(text: "Large heading text", font: largeBoldFont, origin: CGPoint(x: pad, y: y), color: fg, variant: .bold)
        builder.add(kind: .textRun(run8), zIndex: 1)
        y += 44

        // Row 9: Small caption
        let run9 = makeTextRun(text: "Small caption text at 11pt", font: smallFont, origin: CGPoint(x: pad, y: y), color: SIMD4(fg.x, fg.y, fg.z, 0.6))
        builder.add(kind: .textRun(run9), zIndex: 1)
        y += lineSpacing

        // Row 10: Mixed bold + regular on same line
        let mixBold = makeTextRun(text: "Bold", font: boldFont, origin: CGPoint(x: pad, y: y), color: fg, variant: .bold)
        builder.add(kind: .textRun(mixBold), zIndex: 1)
        let afterBold = pad + (mixBold.runBounds?.width ?? 0) + 4
        let mixRegular = makeTextRun(text: "then regular", font: baseFont, origin: CGPoint(x: afterBold, y: y), color: fg)
        builder.add(kind: .textRun(mixRegular), zIndex: 1)
        let afterRegular = afterBold + (mixRegular.runBounds?.width ?? 0) + 4
        let mixItalic = makeTextRun(text: "then italic", font: italicFont, origin: CGPoint(x: afterRegular, y: y), color: fg, variant: .italic)
        builder.add(kind: .textRun(mixItalic), zIndex: 1)
        let afterItalic = afterRegular + (mixItalic.runBounds?.width ?? 0) + 4
        let mixMono = makeTextRun(text: "then mono", font: monoFont, origin: CGPoint(x: afterItalic, y: y), color: SIMD4(0.3, 0.75, 0.6, 1), variant: .monospace)
        builder.add(kind: .textRun(mixMono), zIndex: 1)

        return builder.scene
    }

    private static func textLayoutScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let fg = foregroundColor(for: config.backgroundColor)
        let pad: CGFloat = 40

        let baseFont = NSFont.systemFont(ofSize: 14)
        let boldFont = NSFont.boldSystemFont(ofSize: 14)
        let ctFont = baseFont as CTFont
        let ascent = CTFontGetAscent(ctFont)
        let lineHeight = ascent + CTFontGetDescent(ctFont) + CTFontGetLeading(ctFont)

        // Build a multi-line VVTextLayout
        let lines: [String] = [
            "Line 0: VVTextLayout organizes text into VVTextLine rows.",
            "Line 1: Each line has y offset, height, baseline, and glyphs.",
            "Line 2: Hit testing maps CGPoint to character index.",
            "Line 3: Selection uses line geometry for quad computation.",
            "Line 4: The layout frame wraps all lines for bounds.",
            "Line 5: Supports variable line heights and baselines.",
        ]

        var textLines: [VVTextLine] = []
        var y = pad
        for (i, text) in lines.enumerated() {
            let font = i == 0 ? boldFont : baseFont
            let variant: VVFontVariant = i == 0 ? .bold : .regular
            let glyphs = makeGlyphs(text: text, font: font, origin: CGPoint(x: pad, y: y), color: fg, variant: variant)
            let textLine = VVTextLine(y: y, height: lineHeight, baseline: ascent, glyphs: glyphs)
            textLines.append(textLine)

            let run = makeTextRun(text: text, font: font, origin: CGPoint(x: pad, y: y), color: fg, variant: variant)
            builder.add(kind: .textRun(run), zIndex: 1)

            // Line background stripe (alternating)
            if i % 2 == 0 {
                builder.add(kind: .quad(VVQuadPrimitive(
                    frame: CGRect(x: pad, y: y, width: textLine.width, height: lineHeight),
                    color: SIMD4(fg.x, fg.y, fg.z, 0.04)
                )), zIndex: 0)
            }

            y += lineHeight + 6
        }

        let totalHeight = y - pad
        let layoutFrame = CGRect(x: pad, y: pad, width: size.width - pad * 2, height: totalHeight)
        let _ = VVTextLayout(frame: layoutFrame, lines: textLines)

        // Draw layout frame border (left edge)
        let borderColor = SIMD4<Float>(fg.x, fg.y, fg.z, 0.2)
        builder.add(kind: .line(VVLinePrimitive(start: CGPoint(x: pad - 4, y: pad), end: CGPoint(x: pad - 4, y: y - 6), thickness: 1, color: borderColor)), zIndex: 0)

        // Baseline indicators (small tick marks on left)
        for textLine in textLines {
            let baselineY = textLine.y + textLine.baseline
            builder.add(kind: .line(VVLinePrimitive(
                start: CGPoint(x: pad - 10, y: baselineY),
                end: CGPoint(x: pad - 2, y: baselineY),
                thickness: 1,
                color: SIMD4(0.9, 0.4, 0.3, 0.6)
            )), zIndex: 2)
        }

        // Second block: hit test visualization
        let block2Y = y + 20
        let sampleText = "Hit test: click position maps to glyph index"
        let sampleGlyphs = makeGlyphs(text: sampleText, font: baseFont, origin: CGPoint(x: pad, y: block2Y), color: fg)
        let sampleRun = makeTextRun(text: sampleText, font: baseFont, origin: CGPoint(x: pad, y: block2Y), color: fg)
        builder.add(kind: .textRun(sampleRun), zIndex: 1)

        // Show individual glyph bounds (position.y is baseline, so rect top is position.y - ascent)
        for glyph in sampleGlyphs {
            let glyphRect = CGRect(
                x: glyph.position.x,
                y: glyph.position.y - ascent,
                width: glyph.size.width,
                height: glyph.size.height
            ).insetBy(dx: 0.5, dy: 0.5)
            builder.add(kind: .quad(VVQuadPrimitive(
                frame: glyphRect,
                color: SIMD4(0.3, 0.65, 0.95, 0.12)
            )), zIndex: 0)
        }

        // Cursor at index 10
        if sampleGlyphs.count > 10 {
            let g = sampleGlyphs[10]
            builder.add(kind: .quad(VVQuadPrimitive(
                frame: CGRect(x: g.position.x, y: g.position.y - ascent, width: 2, height: g.size.height),
                color: SIMD4(0.95, 0.4, 0.3, 0.9)
            )), zIndex: 3)
        }

        return builder.scene
    }

    private static func selectionScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let fg = foregroundColor(for: config.backgroundColor)
        let pad: CGFloat = 40

        let baseFont = NSFont.systemFont(ofSize: 14)
        let ctFont = baseFont as CTFont
        let ascent = CTFontGetAscent(ctFont)
        let lineHeight = ascent + CTFontGetDescent(ctFont) + CTFontGetLeading(ctFont)
        let lineGap: CGFloat = 6
        let selectionColor = SIMD4<Float>(0.25, 0.5, 0.95, 0.35)
        let cursorColor = SIMD4<Float>(0.95, 0.95, 1, 0.9)

        /// Selection rect from baseline-positioned glyphs.
        func selRect(startGlyph sg: VVTextGlyph, endGlyph eg: VVTextGlyph) -> CGRect {
            CGRect(
                x: sg.position.x,
                y: sg.position.y - ascent - 1,
                width: eg.position.x + eg.size.width - sg.position.x,
                height: lineHeight + 2
            )
        }

        // Build text lines
        let textContent: [String] = [
            "Selection rendering maps text ranges to highlight quads.",
            "The VVTextSelectionRenderer protocol produces VVQuadPrimitives.",
            "VVTextSelectionController handles mouse events for drag selection.",
            "Single click sets caret, double click selects word, triple selects line.",
            "Selected text can be copied via VVTextExtractor.extractText().",
        ]

        var y = pad
        var lineGlyphs: [[VVTextGlyph]] = []

        for text in textContent {
            let glyphs = makeGlyphs(text: text, font: baseFont, origin: CGPoint(x: pad, y: y), color: fg)
            lineGlyphs.append(glyphs)
            let run = makeTextRun(text: text, font: baseFont, origin: CGPoint(x: pad, y: y), color: fg)
            builder.add(kind: .textRun(run), zIndex: 1)
            y += lineHeight + lineGap
        }

        // Demo 1: Single line partial selection (line 0, chars 10..30)
        if lineGlyphs.count > 0 {
            let glyphs = lineGlyphs[0]
            let start = min(10, glyphs.count - 1)
            let end = min(30, glyphs.count - 1)
            if start < end {
                builder.add(kind: .quad(VVQuadPrimitive(
                    frame: selRect(startGlyph: glyphs[start], endGlyph: glyphs[end]),
                    color: selectionColor, cornerRadius: 3
                )), zIndex: 0)
            }
        }

        // Demo 2: Multi-line selection (line 1 from char 4 to line 3 char 20)
        if lineGlyphs.count > 3 {
            let line1 = lineGlyphs[1]
            let startIdx = min(4, line1.count - 1)
            if let sg = line1[safe: startIdx], let lg = line1.last {
                builder.add(kind: .quad(VVQuadPrimitive(frame: selRect(startGlyph: sg, endGlyph: lg), color: selectionColor, cornerRadius: 2)), zIndex: 0)
            }

            let line2 = lineGlyphs[2]
            if let fg = line2.first, let lg = line2.last {
                builder.add(kind: .quad(VVQuadPrimitive(frame: selRect(startGlyph: fg, endGlyph: lg), color: selectionColor, cornerRadius: 2)), zIndex: 0)
            }

            let line3 = lineGlyphs[3]
            let endIdx = min(20, line3.count - 1)
            if let fg = line3.first, let eg = line3[safe: endIdx] {
                builder.add(kind: .quad(VVQuadPrimitive(frame: selRect(startGlyph: fg, endGlyph: eg), color: selectionColor, cornerRadius: 2)), zIndex: 0)
            }
        }

        // Demo 3: Caret (cursor) on line 4
        if lineGlyphs.count > 4 {
            let line4 = lineGlyphs[4]
            let cursorIdx = min(15, line4.count - 1)
            if let g = line4[safe: cursorIdx] {
                builder.add(kind: .quad(VVQuadPrimitive(
                    frame: CGRect(x: g.position.x, y: g.position.y - ascent - 1, width: 2, height: lineHeight + 2),
                    color: cursorColor
                )), zIndex: 3)
            }
        }

        // Section 2: Selection modes visualization
        y += 30
        let modeFont = NSFont.boldSystemFont(ofSize: 13)
        let modeLabels = ["Character selection", "Word selection", "Line selection"]
        let modeSamples = [
            "Select individual characters by click+drag",
            "Double-click selects the whole word boundary",
            "Triple-click selects the entire line content",
        ]

        for (i, (label, sample)) in zip(modeLabels, modeSamples).enumerated() {
            let labelRun = makeTextRun(text: label, font: modeFont, origin: CGPoint(x: pad, y: y), color: SIMD4(0.4, 0.7, 0.95, 1), variant: .bold)
            builder.add(kind: .textRun(labelRun), zIndex: 1)
            y += lineHeight + 4

            let sampleGlyphs = makeGlyphs(text: sample, font: baseFont, origin: CGPoint(x: pad, y: y), color: fg)
            let sampleRun = makeTextRun(text: sample, font: baseFont, origin: CGPoint(x: pad, y: y), color: fg)
            builder.add(kind: .textRun(sampleRun), zIndex: 1)

            switch i {
            case 0:
                let s = min(7, sampleGlyphs.count - 1)
                let e = min(22, sampleGlyphs.count - 1)
                if s < e, let sg = sampleGlyphs[safe: s], let eg = sampleGlyphs[safe: e] {
                    builder.add(kind: .quad(VVQuadPrimitive(frame: selRect(startGlyph: sg, endGlyph: eg), color: selectionColor, cornerRadius: 2)), zIndex: 0)
                }
            case 1:
                let s = min(13, sampleGlyphs.count - 1)
                let e = min(37, sampleGlyphs.count - 1)
                if s < e, let sg = sampleGlyphs[safe: s], let eg = sampleGlyphs[safe: e] {
                    builder.add(kind: .quad(VVQuadPrimitive(frame: selRect(startGlyph: sg, endGlyph: eg), color: SIMD4(0.3, 0.8, 0.5, 0.3), cornerRadius: 2)), zIndex: 0)
                }
            case 2:
                if let fg = sampleGlyphs.first, let lg = sampleGlyphs.last {
                    builder.add(kind: .quad(VVQuadPrimitive(frame: selRect(startGlyph: fg, endGlyph: lg), color: SIMD4(0.9, 0.6, 0.2, 0.25), cornerRadius: 2)), zIndex: 0)
                }
            default:
                break
            }

            y += lineHeight + lineGap + 8
        }

        return builder.scene
    }

    // MARK: - Individual Primitive Scenes

    private static func quadScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let fg = foregroundColor(for: config.backgroundColor)
        let pad: CGFloat = 40
        let gap: CGFloat = 24
        let tileW: CGFloat = 160
        let tileH: CGFloat = 100

        let colors: [(SIMD4<Float>, String)] = [
            (SIMD4(0.2, 0.65, 0.9, 0.9), "Blue"),
            (SIMD4(0.85, 0.38, 0.5, 0.9), "Rose"),
            (SIMD4(0.95, 0.7, 0.2, 0.9), "Amber"),
            (SIMD4(0.3, 0.8, 0.5, 0.9), "Green"),
        ]

        let radii: [CGFloat] = [0, config.cornerRadius, config.cornerRadius * 2, tileH / 2]

        // Row 1: different colors, same corner radius
        for (i, (color, _)) in colors.enumerated() {
            let x = pad + CGFloat(i) * (tileW + gap)
            let frame = CGRect(x: x, y: pad, width: tileW, height: tileH)
            builder.add(kind: .quad(VVQuadPrimitive(frame: frame, color: color, cornerRadius: config.cornerRadius)), zIndex: 1)
        }

        // Row 2: same color, different corner radii
        let row2Y = pad + tileH + gap + 20
        for (i, radius) in radii.enumerated() {
            let x = pad + CGFloat(i) * (tileW + gap)
            let frame = CGRect(x: x, y: row2Y, width: tileW, height: tileH)
            builder.add(kind: .quad(VVQuadPrimitive(frame: frame, color: SIMD4(0.45, 0.55, 0.95, 0.85), cornerRadius: radius)), zIndex: 1)

            // Label line under each quad
            let labelY = row2Y + tileH + 6
            let underline = VVLinePrimitive(
                start: CGPoint(x: x, y: labelY),
                end: CGPoint(x: x + tileW, y: labelY),
                thickness: 1,
                color: SIMD4(fg.x, fg.y, fg.z, 0.25)
            )
            builder.add(kind: .line(underline), zIndex: 0)
        }

        // Row 3: sizes
        let row3Y = row2Y + tileH + gap + 20
        let sizes: [(CGFloat, CGFloat)] = [(60, 60), (120, 80), (200, 60), (80, 120)]
        var xOffset = pad
        for (w, h) in sizes {
            let frame = CGRect(x: xOffset, y: row3Y, width: w, height: h)
            builder.add(kind: .quad(VVQuadPrimitive(frame: frame, color: SIMD4(0.7, 0.4, 0.85, 0.8), cornerRadius: config.cornerRadius)), zIndex: 1)
            xOffset += w + gap
        }

        return builder.scene
    }

    private static func gradientQuadScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let pad: CGFloat = 40
        let gap: CGFloat = 28
        let tileW: CGFloat = 200
        let tileH: CGFloat = 100

        // Horizontal gradients
        let hGradients: [(SIMD4<Float>, SIMD4<Float>, String)] = [
            (SIMD4(0.2, 0.5, 0.95, 1), SIMD4(0.9, 0.3, 0.6, 1), "Blue to Rose"),
            (SIMD4(0.95, 0.7, 0.1, 1), SIMD4(0.3, 0.85, 0.5, 1), "Amber to Green"),
            (SIMD4(0.1, 0.1, 0.15, 1), SIMD4(0.95, 0.95, 1, 1), "Dark to Light"),
        ]

        for (i, (start, end, _)) in hGradients.enumerated() {
            let x = pad + CGFloat(i) * (tileW + gap)
            let frame = CGRect(x: x, y: pad, width: tileW, height: tileH)
            builder.add(kind: .gradientQuad(VVGradientQuadPrimitive(
                frame: frame, startColor: start, endColor: end,
                direction: .horizontal, cornerRadius: config.cornerRadius
            )), zIndex: 1)
        }

        // Vertical gradients
        let row2Y = pad + tileH + gap
        let vGradients: [(SIMD4<Float>, SIMD4<Float>, String)] = [
            (SIMD4(0.9, 0.3, 0.3, 1), SIMD4(0.3, 0.3, 0.9, 1), "Red to Blue"),
            (SIMD4(0.2, 0.8, 0.6, 1), SIMD4(0.8, 0.6, 0.2, 1), "Teal to Orange"),
            (SIMD4(0.6, 0.2, 0.9, 1), SIMD4(0.2, 0.9, 0.6, 1), "Purple to Mint"),
        ]

        for (i, (start, end, _)) in vGradients.enumerated() {
            let x = pad + CGFloat(i) * (tileW + gap)
            let frame = CGRect(x: x, y: row2Y, width: tileW, height: tileH)
            builder.add(kind: .gradientQuad(VVGradientQuadPrimitive(
                frame: frame, startColor: start, endColor: end,
                direction: .vertical, cornerRadius: config.cornerRadius
            )), zIndex: 1)
        }

        // Large gradient with high corner radius
        let row3Y = row2Y + tileH + gap
        let bigW = 3 * tileW + 2 * gap
        let frame = CGRect(x: pad, y: row3Y, width: bigW, height: 80)
        builder.add(kind: .gradientQuad(VVGradientQuadPrimitive(
            frame: frame,
            startColor: SIMD4(0.95, 0.4, 0.2, 1),
            endColor: SIMD4(0.2, 0.4, 0.95, 1),
            direction: .horizontal,
            cornerRadius: config.cornerRadius,
            steps: 24
        )), zIndex: 1)

        return builder.scene
    }

    private static func shadowQuadScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let pad: CGFloat = 50
        let gap: CGFloat = 40
        let tileW: CGFloat = 160
        let tileH: CGFloat = 100

        let spreads: [CGFloat] = [6, 12, 20, 32]
        let cardColor: SIMD4<Float> = SIMD4(0.25, 0.55, 0.9, 1)
        let shadowColor: SIMD4<Float> = SIMD4(0, 0, 0, 0.5)

        for (i, spread) in spreads.enumerated() {
            let x = pad + CGFloat(i) * (tileW + gap)
            let frame = CGRect(x: x, y: pad + 20, width: tileW, height: tileH)

            let shadow = VVShadowQuadPrimitive(
                frame: frame, color: shadowColor,
                cornerRadius: config.cornerRadius, spread: spread
            )
            for expandedQuad in shadow.expandedQuads() {
                builder.add(kind: .quad(expandedQuad), zIndex: 0)
            }
            builder.add(kind: .quad(VVQuadPrimitive(frame: frame, color: cardColor, cornerRadius: config.cornerRadius)), zIndex: 1)
        }

        // Second row: different shadow colors
        let row2Y = pad + tileH + gap + 40
        let shadowColors: [SIMD4<Float>] = [
            SIMD4(0.9, 0.2, 0.2, 0.5),
            SIMD4(0.2, 0.7, 0.3, 0.5),
            SIMD4(0.5, 0.3, 0.9, 0.5),
            SIMD4(0.9, 0.7, 0.1, 0.5),
        ]
        let surfaceColor: SIMD4<Float> = SIMD4(0.92, 0.93, 0.96, 1)

        for (i, sColor) in shadowColors.enumerated() {
            let x = pad + CGFloat(i) * (tileW + gap)
            let frame = CGRect(x: x, y: row2Y, width: tileW, height: tileH)

            let shadow = VVShadowQuadPrimitive(
                frame: frame, color: sColor,
                cornerRadius: config.cornerRadius, spread: 16
            )
            for expandedQuad in shadow.expandedQuads() {
                builder.add(kind: .quad(expandedQuad), zIndex: 0)
            }
            builder.add(kind: .quad(VVQuadPrimitive(frame: frame, color: surfaceColor, cornerRadius: config.cornerRadius)), zIndex: 1)
        }

        return builder.scene
    }

    private static func lineScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let fg = foregroundColor(for: config.backgroundColor)
        let pad: CGFloat = 40

        // Horizontal lines with varying thickness
        let thicknesses: [CGFloat] = [1, 2, 3, 4, 6, 8]
        let lineColors: [SIMD4<Float>] = [
            SIMD4(0.2, 0.65, 0.9, 0.9),
            SIMD4(0.85, 0.38, 0.5, 0.9),
            SIMD4(0.3, 0.8, 0.5, 0.9),
            SIMD4(0.95, 0.7, 0.2, 0.9),
            SIMD4(0.6, 0.4, 0.9, 0.9),
            fg,
        ]

        for (i, thickness) in thicknesses.enumerated() {
            let y = pad + CGFloat(i) * 32
            let line = VVLinePrimitive(
                start: CGPoint(x: pad, y: y),
                end: CGPoint(x: pad + 400, y: y),
                thickness: thickness,
                color: lineColors[i % lineColors.count]
            )
            builder.add(kind: .line(line), zIndex: 1)
        }

        // Diagonal lines (fan pattern)
        let fanOrigin = CGPoint(x: pad + 520, y: pad)
        let fanRadius: CGFloat = 160
        let steps = 12
        for i in 0..<steps {
            let angle = CGFloat(i) * (.pi / CGFloat(steps - 1))
            let endX = fanOrigin.x + fanRadius * cos(angle)
            let endY = fanOrigin.y + fanRadius * sin(angle)
            let t = Float(i) / Float(steps - 1)
            let color = SIMD4<Float>(0.3 + t * 0.6, 0.5, 0.9 - t * 0.5, 0.8)
            let line = VVLinePrimitive(
                start: fanOrigin,
                end: CGPoint(x: endX, y: endY),
                thickness: 2,
                color: color
            )
            builder.add(kind: .line(line), zIndex: 1)
        }

        // Cross-hatch pattern
        let hatchOrigin = CGPoint(x: pad, y: pad + 220)
        let hatchSize: CGFloat = 200
        let hatchStep: CGFloat = 16
        let hatchColor = SIMD4<Float>(fg.x, fg.y, fg.z, 0.3)

        var offset: CGFloat = 0
        while offset <= hatchSize {
            builder.add(kind: .line(VVLinePrimitive(
                start: CGPoint(x: hatchOrigin.x + offset, y: hatchOrigin.y),
                end: CGPoint(x: hatchOrigin.x, y: hatchOrigin.y + offset),
                thickness: 1, color: hatchColor
            )), zIndex: 1)
            builder.add(kind: .line(VVLinePrimitive(
                start: CGPoint(x: hatchOrigin.x + hatchSize, y: hatchOrigin.y + offset),
                end: CGPoint(x: hatchOrigin.x + hatchSize - offset, y: hatchOrigin.y + hatchSize),
                thickness: 1, color: hatchColor
            )), zIndex: 1)
            offset += hatchStep
        }

        return builder.scene
    }

    private static func bulletScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let fg = foregroundColor(for: config.backgroundColor)
        let pad: CGFloat = 40

        // Row 1: all bullet types at standard size
        let types: [(VVBulletType, String)] = [
            (.disc, "disc"),
            (.circle, "circle"),
            (.square, "square"),
            (.number(1), "number(1)"),
            (.number(42), "number(42)"),
            (.checkbox(false), "checkbox off"),
            (.checkbox(true), "checkbox on"),
        ]

        let bulletSize: CGFloat = 18
        let gap: CGFloat = 60

        for (i, (type, _)) in types.enumerated() {
            let x = pad + CGFloat(i) * gap
            builder.add(kind: .bullet(VVBulletPrimitive(
                position: CGPoint(x: x, y: pad),
                size: bulletSize, color: fg, type: type
            )), zIndex: 1)
        }

        // Row 2: different sizes
        let row2Y = pad + 60
        let sizes: [CGFloat] = [10, 14, 18, 24, 32, 40]
        var xOff = pad
        for s in sizes {
            builder.add(kind: .bullet(VVBulletPrimitive(
                position: CGPoint(x: xOff, y: row2Y),
                size: s, color: SIMD4(0.3, 0.7, 0.9, 1), type: .disc
            )), zIndex: 1)
            xOff += s + 24
        }

        // Row 3: colored bullets
        let row3Y = row2Y + 70
        let bulletColors: [SIMD4<Float>] = [
            SIMD4(0.9, 0.3, 0.3, 1),
            SIMD4(0.3, 0.85, 0.4, 1),
            SIMD4(0.3, 0.5, 0.95, 1),
            SIMD4(0.9, 0.7, 0.15, 1),
            SIMD4(0.7, 0.3, 0.9, 1),
        ]

        for (i, color) in bulletColors.enumerated() {
            let x = pad + CGFloat(i) * 50
            builder.add(kind: .bullet(VVBulletPrimitive(
                position: CGPoint(x: x, y: row3Y),
                size: 20, color: color, type: .disc
            )), zIndex: 1)
            builder.add(kind: .bullet(VVBulletPrimitive(
                position: CGPoint(x: x, y: row3Y + 34),
                size: 20, color: color, type: .square
            )), zIndex: 1)
            builder.add(kind: .bullet(VVBulletPrimitive(
                position: CGPoint(x: x, y: row3Y + 68),
                size: 20, color: color, type: .checkbox(i % 2 == 0)
            )), zIndex: 1)
        }

        // Row 4: numbered list
        let row4Y = row3Y + 120
        for i in 1...8 {
            let x = pad + CGFloat(i - 1) * 50
            builder.add(kind: .bullet(VVBulletPrimitive(
                position: CGPoint(x: x, y: row4Y),
                size: 22, color: fg, type: .number(i)
            )), zIndex: 1)
        }

        return builder.scene
    }

    private static func blockQuoteBorderScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let fg = foregroundColor(for: config.backgroundColor)
        let pad: CGFloat = 40

        // Different widths
        let widths: [CGFloat] = [2, 4, 6, 8]
        let blockH: CGFloat = 80

        for (i, bw) in widths.enumerated() {
            let x = pad + CGFloat(i) * 180
            let frame = CGRect(x: x, y: pad, width: 140, height: blockH)

            // Background quad to show the quote area
            builder.add(kind: .quad(VVQuadPrimitive(
                frame: frame,
                color: SIMD4(fg.x, fg.y, fg.z, 0.06),
                cornerRadius: 4
            )), zIndex: 0)
            builder.add(kind: .blockQuoteBorder(VVBlockQuoteBorderPrimitive(
                frame: frame, color: fg, borderWidth: bw
            )), zIndex: 1)
        }

        // Different colors
        let row2Y = pad + blockH + 40
        let borderColors: [SIMD4<Float>] = [
            SIMD4(0.3, 0.7, 0.95, 1),
            SIMD4(0.9, 0.4, 0.4, 1),
            SIMD4(0.3, 0.85, 0.5, 1),
            SIMD4(0.9, 0.7, 0.2, 1),
        ]

        for (i, color) in borderColors.enumerated() {
            let x = pad + CGFloat(i) * 180
            let frame = CGRect(x: x, y: row2Y, width: 140, height: blockH)

            builder.add(kind: .quad(VVQuadPrimitive(
                frame: frame,
                color: SIMD4(color.x, color.y, color.z, 0.08),
                cornerRadius: 4
            )), zIndex: 0)
            builder.add(kind: .blockQuoteBorder(VVBlockQuoteBorderPrimitive(
                frame: frame, color: color, borderWidth: 4
            )), zIndex: 1)
        }

        // Nested quotes
        let row3Y = row2Y + blockH + 40
        let nestWidths: [CGFloat] = [300, 260, 220]
        let nestColors: [SIMD4<Float>] = [
            SIMD4(0.5, 0.6, 0.9, 0.8),
            SIMD4(0.6, 0.75, 0.95, 0.7),
            SIMD4(0.7, 0.85, 1, 0.6),
        ]
        for (i, (w, color)) in zip(nestWidths, nestColors).enumerated() {
            let x = pad + CGFloat(i) * 20
            let frame = CGRect(x: x, y: row3Y + CGFloat(i) * 8, width: w, height: 80 - CGFloat(i) * 8)
            builder.add(kind: .quad(VVQuadPrimitive(
                frame: frame,
                color: SIMD4(color.x, color.y, color.z, 0.06),
                cornerRadius: 2
            )), zIndex: 0)
            builder.add(kind: .blockQuoteBorder(VVBlockQuoteBorderPrimitive(
                frame: frame, color: color, borderWidth: 3
            )), zIndex: 1)
        }

        return builder.scene
    }

    private static func tableLineScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let fg = foregroundColor(for: config.backgroundColor)
        let pad: CGFloat = 40

        // Standard table
        let rows = 4
        let cols = 5
        let cellW: CGFloat = 100
        let cellH: CGFloat = 32
        let origin = CGPoint(x: pad, y: pad)

        for row in 0...rows {
            let y = origin.y + CGFloat(row) * cellH
            let lineWidth: CGFloat = row == 0 || row == 1 ? 2 : 1
            builder.add(kind: .tableLine(VVTableLinePrimitive(
                start: CGPoint(x: origin.x, y: y),
                end: CGPoint(x: origin.x + CGFloat(cols) * cellW, y: y),
                color: fg, lineWidth: lineWidth
            )), zIndex: 1)
        }
        for col in 0...cols {
            let x = origin.x + CGFloat(col) * cellW
            builder.add(kind: .tableLine(VVTableLinePrimitive(
                start: CGPoint(x: x, y: origin.y),
                end: CGPoint(x: x, y: origin.y + CGFloat(rows) * cellH),
                color: fg, lineWidth: 1
            )), zIndex: 1)
        }

        // Header row background
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: origin.x, y: origin.y, width: CGFloat(cols) * cellW, height: cellH),
            color: SIMD4(fg.x, fg.y, fg.z, 0.08)
        )), zIndex: 0)

        // Colored table
        let table2Origin = CGPoint(x: pad, y: pad + CGFloat(rows) * cellH + 50)
        let table2Rows = 3
        let table2Cols = 4
        let coloredLineColor = SIMD4<Float>(0.3, 0.65, 0.95, 0.8)

        for row in 0...table2Rows {
            let y = table2Origin.y + CGFloat(row) * cellH
            builder.add(kind: .tableLine(VVTableLinePrimitive(
                start: CGPoint(x: table2Origin.x, y: y),
                end: CGPoint(x: table2Origin.x + CGFloat(table2Cols) * cellW, y: y),
                color: coloredLineColor, lineWidth: 1
            )), zIndex: 1)
        }
        for col in 0...table2Cols {
            let x = table2Origin.x + CGFloat(col) * cellW
            builder.add(kind: .tableLine(VVTableLinePrimitive(
                start: CGPoint(x: x, y: table2Origin.y),
                end: CGPoint(x: x, y: table2Origin.y + CGFloat(table2Rows) * cellH),
                color: coloredLineColor, lineWidth: 1
            )), zIndex: 1)
        }

        // Alternating row shading
        for row in 0..<table2Rows where row % 2 == 1 {
            let y = table2Origin.y + CGFloat(row) * cellH
            builder.add(kind: .quad(VVQuadPrimitive(
                frame: CGRect(x: table2Origin.x, y: y, width: CGFloat(table2Cols) * cellW, height: cellH),
                color: SIMD4(coloredLineColor.x, coloredLineColor.y, coloredLineColor.z, 0.06)
            )), zIndex: 0)
        }

        return builder.scene
    }

    private static func pieSliceScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let pad: CGFloat = 40

        // Standard pie chart
        let center1 = CGPoint(x: pad + 120, y: pad + 130)
        let radius1: CGFloat = 100
        let slices1: [(CGFloat, CGFloat, SIMD4<Float>)] = [
            (0, 1.2, SIMD4(0.3, 0.8, 0.5, 0.9)),
            (1.2, 2.4, SIMD4(0.95, 0.6, 0.2, 0.9)),
            (2.4, 3.8, SIMD4(0.5, 0.6, 0.95, 0.9)),
            (3.8, 5.2, SIMD4(0.9, 0.4, 0.6, 0.9)),
            (5.2, .pi * 2, SIMD4(0.7, 0.7, 0.75, 0.9)),
        ]
        for (start, end, color) in slices1 {
            builder.add(kind: .pieSlice(VVPieSlicePrimitive(
                center: center1, radius: radius1,
                startAngle: start, endAngle: end, color: color
            )), zIndex: 1)
        }

        // Small donut-like (two overlapping pies)
        let center2 = CGPoint(x: pad + 360, y: pad + 130)
        let radius2: CGFloat = 90
        let slices2: [(CGFloat, CGFloat, SIMD4<Float>)] = [
            (0, .pi * 0.5, SIMD4(0.95, 0.35, 0.35, 0.9)),
            (.pi * 0.5, .pi, SIMD4(0.35, 0.85, 0.45, 0.9)),
            (.pi, .pi * 1.5, SIMD4(0.35, 0.55, 0.95, 0.9)),
            (.pi * 1.5, .pi * 2, SIMD4(0.95, 0.75, 0.25, 0.9)),
        ]
        for (start, end, color) in slices2 {
            builder.add(kind: .pieSlice(VVPieSlicePrimitive(
                center: center2, radius: radius2,
                startAngle: start, endAngle: end, color: color
            )), zIndex: 1)
        }
        // Inner circle to create donut
        builder.add(kind: .pieSlice(VVPieSlicePrimitive(
            center: center2, radius: 40,
            startAngle: 0, endAngle: .pi * 2,
            color: config.backgroundColor
        )), zIndex: 2)

        // Small pie charts in a row
        let row2Y = pad + 290
        let smallRadius: CGFloat = 45
        let smallPies: [[(CGFloat, CGFloat, SIMD4<Float>)]] = [
            [(0, .pi, SIMD4(0.4, 0.7, 0.95, 0.9)), (.pi, .pi * 2, SIMD4(0.95, 0.5, 0.3, 0.9))],
            [(0, .pi * 0.7, SIMD4(0.8, 0.3, 0.8, 0.9)), (.pi * 0.7, .pi * 2, SIMD4(0.3, 0.8, 0.6, 0.9))],
            [(0, .pi * 1.3, SIMD4(0.95, 0.8, 0.2, 0.9)), (.pi * 1.3, .pi * 2, SIMD4(0.5, 0.5, 0.55, 0.9))],
            [(0, .pi * 0.3, SIMD4(0.3, 0.9, 0.5, 0.9)), (.pi * 0.3, .pi * 2, SIMD4(0.4, 0.45, 0.5, 0.4))],
        ]

        for (i, slices) in smallPies.enumerated() {
            let cx = pad + 60 + CGFloat(i) * 130
            for (start, end, color) in slices {
                builder.add(kind: .pieSlice(VVPieSlicePrimitive(
                    center: CGPoint(x: cx, y: row2Y),
                    radius: smallRadius,
                    startAngle: start, endAngle: end, color: color
                )), zIndex: 1)
            }
        }

        return builder.scene
    }

    private static func imageScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let fg = foregroundColor(for: config.backgroundColor)
        let pad: CGFloat = 40
        let gap: CGFloat = 28

        // Image primitives show placeholder frames (no texture loaded, so we add background quads)
        let imageSizes: [(CGFloat, CGFloat, CGFloat)] = [
            (180, 120, 4),
            (120, 120, config.cornerRadius),
            (200, 100, 0),
            (100, 140, config.cornerRadius * 2),
        ]

        var x = pad
        for (w, h, cr) in imageSizes {
            let frame = CGRect(x: x, y: pad, width: w, height: h)

            // Background to show the image area
            builder.add(kind: .quad(VVQuadPrimitive(
                frame: frame,
                color: SIMD4(fg.x, fg.y, fg.z, 0.08),
                cornerRadius: cr
            )), zIndex: 0)

            // Border outline
            let borderTop = VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.minY), end: CGPoint(x: frame.maxX, y: frame.minY), thickness: 1, color: SIMD4(fg.x, fg.y, fg.z, 0.3))
            let borderBottom = VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.maxY), end: CGPoint(x: frame.maxX, y: frame.maxY), thickness: 1, color: SIMD4(fg.x, fg.y, fg.z, 0.3))
            let borderLeft = VVLinePrimitive(start: CGPoint(x: frame.minX, y: frame.minY), end: CGPoint(x: frame.minX, y: frame.maxY), thickness: 1, color: SIMD4(fg.x, fg.y, fg.z, 0.3))
            let borderRight = VVLinePrimitive(start: CGPoint(x: frame.maxX, y: frame.minY), end: CGPoint(x: frame.maxX, y: frame.maxY), thickness: 1, color: SIMD4(fg.x, fg.y, fg.z, 0.3))
            builder.add(kind: .line(borderTop), zIndex: 1)
            builder.add(kind: .line(borderBottom), zIndex: 1)
            builder.add(kind: .line(borderLeft), zIndex: 1)
            builder.add(kind: .line(borderRight), zIndex: 1)

            // Diagonal cross to indicate image placeholder
            let diag1 = VVLinePrimitive(start: CGPoint(x: frame.minX + 4, y: frame.minY + 4), end: CGPoint(x: frame.maxX - 4, y: frame.maxY - 4), thickness: 1, color: SIMD4(fg.x, fg.y, fg.z, 0.15))
            let diag2 = VVLinePrimitive(start: CGPoint(x: frame.maxX - 4, y: frame.minY + 4), end: CGPoint(x: frame.minX + 4, y: frame.maxY - 4), thickness: 1, color: SIMD4(fg.x, fg.y, fg.z, 0.15))
            builder.add(kind: .line(diag1), zIndex: 1)
            builder.add(kind: .line(diag2), zIndex: 1)

            // The actual image primitive (won't render visually without texture)
            builder.add(kind: .image(VVImagePrimitive(url: "placeholder://image\(Int(w))", frame: frame, cornerRadius: cr)), zIndex: 2)
            x += w + gap
        }

        // Second row: same image at different corner radii
        let row2Y = pad + 160
        let imgW: CGFloat = 140
        let imgH: CGFloat = 100
        let radii: [CGFloat] = [0, 8, 16, imgH / 2]
        for (i, cr) in radii.enumerated() {
            let fx = pad + CGFloat(i) * (imgW + gap)
            let frame = CGRect(x: fx, y: row2Y, width: imgW, height: imgH)

            builder.add(kind: .quad(VVQuadPrimitive(
                frame: frame,
                color: SIMD4(0.35, 0.6, 0.9, 0.2),
                cornerRadius: cr
            )), zIndex: 0)
            builder.add(kind: .image(VVImagePrimitive(url: "placeholder://corner\(i)", frame: frame, cornerRadius: cr)), zIndex: 2)
        }

        return builder.scene
    }

    private static func ruleScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        let fg = foregroundColor(for: config.backgroundColor)
        let width = max(size.width - 80, 400)

        let view = VVStack(spacing: 20) {
            VDivider(thickness: 1, color: fg)
            VDivider(thickness: 2, color: .blue.withOpacity(0.9))
            VDivider(thickness: 3, color: .rose.withOpacity(0.9))
            VDivider(thickness: 4, color: .teal.withOpacity(0.9))
            VDivider(thickness: 6, color: .amber.withOpacity(0.9))
            VDivider(thickness: 8, color: .purple.withOpacity(0.9))
            VDivider(thickness: 1, color: fg, inset: 40)
            VDivider(thickness: 2, color: .cyan.withOpacity(0.7), inset: 80)
            VDivider(thickness: 1, color: fg.withOpacity(0.3), inset: 120)
        }
        .padding(40)

        return view.renderScene(
            width: width + 80,
            env: VVLayoutEnvironment(scale: 1, defaultTextColor: fg, defaultCornerRadius: config.cornerRadius)
        )
    }

    private static func stackScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        let fg = foregroundColor(for: config.backgroundColor)
        let width = max(size.width - 80, 500)
        let env = VVLayoutEnvironment(scale: 1, defaultTextColor: fg, defaultCornerRadius: config.cornerRadius)

        let barColors: [SIMD4<Float>] = [
            .blue.withOpacity(0.85), .rose.withOpacity(0.85),
            .teal.withOpacity(0.85), .amber.withOpacity(0.85),
        ]
        let barWidths: [CGFloat] = [300, 220, 260, 180]

        func bars(alignment: VVAlignment) -> VVStack {
            VVStack(spacing: 8, alignment: alignment) {
                for (color, w) in zip(barColors, barWidths) {
                    VRect(color: color, cornerRadius: config.cornerRadius).frame(width: w, height: 36)
                }
            }
        }

        let view = VVStack(spacing: 30) {
            bars(alignment: .leading)
            VVHStack(spacing: 20) {
                bars(alignment: .center)
                bars(alignment: .trailing)
            }
        }
        .padding(40)

        return view.renderScene(width: width + 80, env: env)
    }

    private static func layerScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        let fg = foregroundColor(for: config.backgroundColor)
        let env = VVLayoutEnvironment(scale: 1, defaultTextColor: fg, defaultCornerRadius: config.cornerRadius)
        let cr = config.cornerRadius

        // Overlapping cards via VVZStack with manual offset (padding trick)
        let card1 = VRect(color: .blue.withOpacity(0.7), cornerRadius: cr).frame(width: 200, height: 120)
        let card2 = VRect(color: .pink.withOpacity(0.7), cornerRadius: cr).frame(width: 200, height: 120)
            .padding(top: 30, right: 0, bottom: 0, left: 40)
        let card3 = VRect(color: .teal.withOpacity(0.7), cornerRadius: cr).frame(width: 200, height: 120)
            .padding(top: 60, right: 0, bottom: 0, left: 80)

        let overlapping = VVZStack {
            card1
            card2
            card3
        }

        // Card with background, rule, content
        let card = VVStack(spacing: 12) {
            VRect(color: .indigo.withOpacity(0.8), cornerRadius: 6).frame(width: 260, height: 40)
            VDivider(color: fg.withOpacity(0.3))
            VRect(color: .orange.withOpacity(0.8), cornerRadius: 6).frame(width: 200, height: 40)
        }
        .padding(20)
        .background(color: fg.withOpacity(0.06), cornerRadius: cr)

        let view = VVHStack(spacing: 40) {
            overlapping
            card
        }
        .padding(40)

        return view.renderScene(width: max(size.width, 700), env: env)
    }

    private static func underlineScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        let fg = foregroundColor(for: config.backgroundColor)
        var builder = VVSceneBuilder()
        let inset: CGFloat = 40

        // Straight underlines with varying thickness
        let thicknesses: [CGFloat] = [1, 1.5, 2, 3]
        for (i, thickness) in thicknesses.enumerated() {
            let y = inset + CGFloat(i) * 50
            builder.add(kind: .underline(VVUnderlinePrimitive(
                origin: CGPoint(x: inset, y: y),
                width: 200,
                thickness: thickness,
                color: fg
            )))
        }

        // Wavy underlines (spell-check style)
        let wavyColors: [SIMD4<Float>] = [
            SIMD4(1, 0.3, 0.3, 1),   // red
            SIMD4(0.3, 0.8, 0.3, 1), // green
            SIMD4(0.3, 0.5, 1, 1),   // blue
            SIMD4(0.9, 0.7, 0.1, 1), // yellow
        ]
        for (i, color) in wavyColors.enumerated() {
            let y = inset + CGFloat(i) * 50
            builder.add(kind: .underline(VVUnderlinePrimitive(
                origin: CGPoint(x: inset + 260, y: y),
                width: 180,
                thickness: 2,
                color: color,
                wavy: true
            )))
        }

        return builder.scene
    }

    private static func pathScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        let fg = foregroundColor(for: config.backgroundColor)
        var builder = VVSceneBuilder()
        let inset: CGFloat = 40

        // Triangle (fill)
        var triangleBuilder = VVPathBuilder()
        triangleBuilder.addPolygon([
            CGPoint(x: inset + 50, y: inset),
            CGPoint(x: inset + 100, y: inset + 80),
            CGPoint(x: inset, y: inset + 80)
        ])
        builder.add(kind: .path(triangleBuilder.build(fill: SIMD4(0.3, 0.8, 0.5, 0.9))))

        // Rectangle (stroke only)
        var rectBuilder = VVPathBuilder()
        rectBuilder.addRect(CGRect(x: inset + 130, y: inset, width: 100, height: 80))
        builder.add(kind: .path(rectBuilder.build(stroke: VVStrokeStyle(color: fg, width: 2))))

        // Circle / ellipse (fill + stroke)
        var ellipseBuilder = VVPathBuilder()
        ellipseBuilder.addEllipse(in: CGRect(x: inset + 270, y: inset, width: 100, height: 80))
        builder.add(kind: .path(ellipseBuilder.build(
            fill: SIMD4(0.5, 0.6, 0.95, 0.6),
            stroke: VVStrokeStyle(color: SIMD4(0.5, 0.6, 0.95, 1), width: 2)
        )))

        // Rounded rect with per-corner radii
        var roundedBuilder = VVPathBuilder()
        roundedBuilder.addRoundedRect(
            CGRect(x: inset, y: inset + 120, width: 160, height: 80),
            cornerRadii: VVCornerRadii(topLeft: 20, topRight: 5, bottomLeft: 5, bottomRight: 20)
        )
        builder.add(kind: .path(roundedBuilder.build(
            fill: SIMD4(0.95, 0.6, 0.2, 0.8),
            stroke: VVStrokeStyle(color: SIMD4(0.95, 0.6, 0.2, 1), width: 1.5)
        )))

        // Bezier curve
        var curveBuilder = VVPathBuilder()
        curveBuilder.move(to: CGPoint(x: inset + 200, y: inset + 200))
        curveBuilder.cubicCurve(
            to: CGPoint(x: inset + 400, y: inset + 200),
            control1: CGPoint(x: inset + 250, y: inset + 100),
            control2: CGPoint(x: inset + 350, y: inset + 280)
        )
        builder.add(kind: .path(curveBuilder.build(stroke: VVStrokeStyle(color: SIMD4(0.9, 0.4, 0.6, 1), width: 3))))

        // Star polygon
        var starBuilder = VVPathBuilder()
        let cx: CGFloat = inset + 100
        let cy: CGFloat = inset + 310
        let outerR: CGFloat = 50
        let innerR: CGFloat = 22
        var starPoints: [CGPoint] = []
        for i in 0..<10 {
            let angle = CGFloat(i) * .pi / 5 - .pi / 2
            let r: CGFloat = i % 2 == 0 ? outerR : innerR
            starPoints.append(CGPoint(x: cx + r * cos(angle), y: cy + r * sin(angle)))
        }
        starBuilder.addPolygon(starPoints)
        builder.add(kind: .path(starBuilder.build(fill: SIMD4(0.95, 0.85, 0.2, 0.9))))

        // Arc
        var arcBuilder = VVPathBuilder()
        arcBuilder.addArc(center: CGPoint(x: inset + 300, y: inset + 310), radius: 45, startAngle: -.pi / 4, endAngle: .pi * 1.25)
        builder.add(kind: .path(arcBuilder.build(stroke: VVStrokeStyle(color: fg, width: 2.5))))

        return builder.scene
    }

    private static func borderScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        var builder = VVSceneBuilder()
        let inset: CGFloat = 40

        // Uniform corner radii
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: inset, y: inset, width: 140, height: 80),
            color: .blue.withOpacity(0.9),
            cornerRadii: VVCornerRadii(12)
        )))

        // Per-corner radii
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: inset + 170, y: inset, width: 140, height: 80),
            color: .rose.withOpacity(0.9),
            cornerRadii: VVCornerRadii(topLeft: 24, topRight: 4, bottomLeft: 4, bottomRight: 24)
        )))

        // Pill shape (top corners only)
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: inset + 340, y: inset, width: 120, height: 80),
            color: .amber.withOpacity(0.9),
            cornerRadii: VVCornerRadii(topLeft: 40, topRight: 40, bottomLeft: 0, bottomRight: 0)
        )))

        // Quad with solid border
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: inset, y: inset + 120, width: 140, height: 80),
            color: .darkSurface,
            cornerRadii: VVCornerRadii(8),
            border: VVBorder(width: 2, color: .teal)
        )))

        // Quad with dashed border
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: inset + 170, y: inset + 120, width: 140, height: 80),
            color: .darkSurface,
            cornerRadii: VVCornerRadii(8),
            border: VVBorder(width: 2, color: .indigo, style: .dashed(dashLength: 6, gapLength: 3))
        )))

        // Quad with per-side border widths
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: inset + 340, y: inset + 120, width: 120, height: 80),
            color: .darkSurface,
            cornerRadii: VVCornerRadii(4),
            border: VVBorder(widths: VVEdgeWidths(top: 1, right: 4, bottom: 1, left: 4), color: .pink)
        )))

        // Semi-transparent with opacity
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: inset, y: inset + 240, width: 200, height: 80),
            color: .teal,
            cornerRadii: VVCornerRadii(12),
            opacity: 0.5
        )))
        // Overlapping quad to show opacity
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: CGRect(x: inset + 80, y: inset + 260, width: 200, height: 80),
            color: .indigo,
            cornerRadii: VVCornerRadii(12),
            opacity: 0.5
        )))

        return builder.scene
    }

    private static func dashedLineScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        let fg = foregroundColor(for: config.backgroundColor)
        var builder = VVSceneBuilder()
        let inset: CGFloat = 40

        // Solid line (baseline)
        builder.add(kind: .line(VVLinePrimitive(
            start: CGPoint(x: inset, y: inset),
            end: CGPoint(x: inset + 300, y: inset),
            thickness: 2, color: fg, dash: .solid
        )))

        // Standard dash
        builder.add(kind: .line(VVLinePrimitive(
            start: CGPoint(x: inset, y: inset + 40),
            end: CGPoint(x: inset + 300, y: inset + 40),
            thickness: 2, color: SIMD4(0.3, 0.8, 0.5, 1),
            dash: .dashed(on: 8, off: 4)
        )))

        // Short dash
        builder.add(kind: .line(VVLinePrimitive(
            start: CGPoint(x: inset, y: inset + 80),
            end: CGPoint(x: inset + 300, y: inset + 80),
            thickness: 2, color: SIMD4(0.5, 0.6, 0.95, 1),
            dash: .dashed(on: 4, off: 4)
        )))

        // Dot pattern
        builder.add(kind: .line(VVLinePrimitive(
            start: CGPoint(x: inset, y: inset + 120),
            end: CGPoint(x: inset + 300, y: inset + 120),
            thickness: 2, color: SIMD4(0.95, 0.6, 0.2, 1),
            dash: .dashed(on: 2, off: 4)
        )))

        // Long dash-dot pattern
        builder.add(kind: .line(VVLinePrimitive(
            start: CGPoint(x: inset, y: inset + 160),
            end: CGPoint(x: inset + 300, y: inset + 160),
            thickness: 2, color: SIMD4(0.9, 0.4, 0.6, 1),
            dash: .pattern([12, 4, 2, 4])
        )))

        // Thick dashed
        builder.add(kind: .line(VVLinePrimitive(
            start: CGPoint(x: inset, y: inset + 200),
            end: CGPoint(x: inset + 300, y: inset + 200),
            thickness: 4, color: SIMD4(0.95, 0.85, 0.2, 1),
            dash: .dashed(on: 16, off: 8)
        )))

        // Diagonal dashed
        builder.add(kind: .line(VVLinePrimitive(
            start: CGPoint(x: inset + 340, y: inset),
            end: CGPoint(x: inset + 480, y: inset + 200),
            thickness: 2, color: fg,
            dash: .dashed(on: 6, off: 3)
        )))

        return builder.scene
    }

    private static func transformScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        let fg = foregroundColor(for: config.backgroundColor)
        var builder = VVSceneBuilder()
        let inset: CGFloat = 60

        // Original rect (no transform)
        let baseRect = CGRect(x: inset, y: inset, width: 80, height: 50)
        builder.add(kind: .quad(VVQuadPrimitive(
            frame: baseRect,
            color: SIMD4(fg.x, fg.y, fg.z, 0.3),
            cornerRadii: VVCornerRadii(4)
        )))

        // Translated path (rect moved by transform)
        var translatedBuilder = VVPathBuilder()
        translatedBuilder.addRect(baseRect)
        let translateT = VVTransform2D.identity.translated(by: CGPoint(x: 150, y: 0))
        builder.add(kind: .path(translatedBuilder.build(
            fill: SIMD4(0.3, 0.8, 0.5, 0.8),
            transform: translateT
        )))

        // Scaled path
        var scaledBuilder = VVPathBuilder()
        scaledBuilder.addRect(CGRect(x: inset, y: inset + 100, width: 60, height: 40))
        let scaleT = VVTransform2D.identity.scaled(x: 1.5, y: 2.0)
        builder.add(kind: .path(scaledBuilder.build(
            fill: SIMD4(0.5, 0.6, 0.95, 0.8),
            transform: scaleT
        )))

        // Rotated star
        var starBuilder = VVPathBuilder()
        let cx: CGFloat = inset + 350
        let cy: CGFloat = inset + 80
        let outerR: CGFloat = 40
        let innerR: CGFloat = 18
        var starPoints: [CGPoint] = []
        for i in 0..<10 {
            let angle = CGFloat(i) * .pi / 5 - .pi / 2
            let r: CGFloat = i % 2 == 0 ? outerR : innerR
            starPoints.append(CGPoint(x: cx + r * cos(angle), y: cy + r * sin(angle)))
        }
        starBuilder.addPolygon(starPoints)
        let rotateT = VVTransform2D.identity.rotated(by: .pi / 6)
        builder.add(kind: .path(starBuilder.build(
            fill: SIMD4(0.95, 0.7, 0.2, 0.9),
            transform: rotateT
        )))

        // Composed: scale + rotate
        var composedBuilder = VVPathBuilder()
        composedBuilder.addRect(CGRect(x: inset + 200, y: inset + 200, width: 60, height: 40))
        let composedT = VVTransform2D.identity.scaled(by: 1.5).rotated(by: .pi / 8)
        builder.add(kind: .path(composedBuilder.build(
            fill: SIMD4(0.9, 0.4, 0.6, 0.8),
            stroke: VVStrokeStyle(color: SIMD4(0.9, 0.4, 0.6, 1), width: 2),
            transform: composedT
        )))

        return builder.scene
    }

    private static func vvviewScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        let fg = foregroundColor(for: config.backgroundColor)
        let env = VVLayoutEnvironment(scale: 1, defaultTextColor: fg, defaultCornerRadius: config.cornerRadius)
        let cr = config.cornerRadius
        let width = max(size.width - 80, 600)

        let view = VVStack(spacing: 24) {
            // Card 1: basic text card
            VVStack(spacing: 8) {
                VText("VVView Declarative DSL", font: .title)
                VDivider()
                VText("Build Metal-rendered UIs without coordinate math.", font: .body)
                VText("Uses @resultBuilder for SwiftUI-like syntax.", font: .caption, color: fg.withOpacity(0.6))
            }
            .padding(20)
            .background(color: fg.withOpacity(0.06), cornerRadius: cr)

            // Card 2: VVHStack with colored tiles
            VVHStack(spacing: 12) {
                for color in [SIMD4<Float>.blue, .rose, .teal, .amber] {
                    VVStack(spacing: 6) {
                        VRect(color: color.withOpacity(0.85), cornerRadius: cr).frame(height: 60)
                        VText("Tile", font: .caption, color: fg.withOpacity(0.5))
                    }
                }
            }

            // Card 3: nested layout
            VVStack(spacing: 12) {
                VText("Nested Layout", font: .headline)
                VVHStack(spacing: 16) {
                    VVStack(spacing: 8) {
                        VText("Left Column", font: .body)
                        VRect(color: .indigo.withOpacity(0.3), cornerRadius: 4).frame(height: 40)
                        VRect(color: .indigo.withOpacity(0.2), cornerRadius: 4).frame(height: 30)
                    }
                    VVStack(spacing: 8) {
                        VText("Right Column", font: .body)
                        VRect(color: .teal.withOpacity(0.3), cornerRadius: 4).frame(height: 30)
                        VRect(color: .teal.withOpacity(0.2), cornerRadius: 4).frame(height: 40)
                    }
                }
            }
            .padding(20)
            .background(color: fg.withOpacity(0.04), cornerRadius: cr)
            .border(color: fg.withOpacity(0.1), width: 1, cornerRadii: VVCornerRadii(cr))

            // Card 4: shadow demo
            VVStack(spacing: 8) {
                VText("Shadow & Opacity", font: .headline)
                VText("Cards with depth and layering effects.", font: .body, color: fg.withOpacity(0.7))
            }
            .padding(20)
            .background(color: .darkSurface, cornerRadius: cr)
            .shadow(color: .black.withOpacity(0.4), spread: 12, cornerRadii: VVCornerRadii(cr))

            // Card 5: conditional content
            VVStack(spacing: 8) {
                VText("Conditional Content", font: .headline)
                if config.cornerRadius > 10 {
                    VText("Corner radius > 10 (rounded)", font: .body, color: .teal)
                } else {
                    VText("Corner radius <= 10 (sharp)", font: .body, color: .amber)
                }
                VDivider(color: fg.withOpacity(0.15))
                VText("for-in loops supported too:", font: .caption, color: fg.withOpacity(0.5))
                for i in 1...3 {
                    VText("  Item \(i)", font: .code, color: fg.withOpacity(0.7))
                }
            }
            .padding(16)
            .background(color: fg.withOpacity(0.05), cornerRadius: cr)
        }
        .padding(40)

        return view.renderScene(width: width + 80, env: env)
    }

    private static func combinedScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        let width = max(size.width, 720)
        let height = max(size.height, 520)
        let inset: CGFloat = 28
        let contentRect = CGRect(x: inset, y: inset, width: width - inset * 2, height: height - inset * 2)
        let fg = foregroundColor(for: config.backgroundColor)
        let gridColor = SIMD4<Float>(fg.x, fg.y, fg.z, 0.18)

        var builder = VVSceneBuilder()

        // Grid
        let step: CGFloat = 40
        var x = contentRect.minX
        while x <= contentRect.maxX {
            builder.add(kind: .line(VVLinePrimitive(
                start: CGPoint(x: x, y: contentRect.minY),
                end: CGPoint(x: x, y: contentRect.maxY),
                thickness: 1, color: gridColor
            )), zIndex: 0)
            x += step
        }
        var y = contentRect.minY
        while y <= contentRect.maxY {
            builder.add(kind: .line(VVLinePrimitive(
                start: CGPoint(x: contentRect.minX, y: y),
                end: CGPoint(x: contentRect.maxX, y: y),
                thickness: 1, color: gridColor
            )), zIndex: 0)
            y += step
        }

        // Quads
        let tileSize = CGSize(width: 160, height: 96)
        let tileGap: CGFloat = 22
        let tileY = contentRect.minY + 12
        let tileX = contentRect.minX + 12
        let tiles: [SIMD4<Float>] = [
            SIMD4(0.2, 0.65, 0.9, 0.9),
            SIMD4(0.85, 0.38, 0.5, 0.9),
            SIMD4(0.95, 0.7, 0.2, 0.9),
        ]
        for (index, color) in tiles.enumerated() {
            let tx = tileX + CGFloat(index) * (tileSize.width + tileGap)
            let frame = CGRect(x: tx, y: tileY, width: tileSize.width, height: tileSize.height)
            builder.add(kind: .quad(VVQuadPrimitive(frame: frame, color: color, cornerRadius: config.cornerRadius)), zIndex: 1)
        }

        // Block quote + table
        let borderFrame = CGRect(x: tileX, y: tileY + tileSize.height + 24, width: 180, height: 86)
        builder.add(kind: .blockQuoteBorder(VVBlockQuoteBorderPrimitive(frame: borderFrame, color: fg, borderWidth: 4)), zIndex: 1)

        let tableOrigin = CGPoint(x: tileX + 210, y: borderFrame.minY)
        let tableWidth: CGFloat = 240
        let rowHeight: CGFloat = 28
        let rows = 3
        let cols = 3
        for row in 0...rows {
            let ty = tableOrigin.y + CGFloat(row) * rowHeight
            builder.add(kind: .tableLine(VVTableLinePrimitive(
                start: CGPoint(x: tableOrigin.x, y: ty),
                end: CGPoint(x: tableOrigin.x + tableWidth, y: ty),
                color: fg, lineWidth: 1
            )), zIndex: 1)
        }
        for col in 0...cols {
            let cx = tableOrigin.x + CGFloat(col) * (tableWidth / CGFloat(cols))
            builder.add(kind: .tableLine(VVTableLinePrimitive(
                start: CGPoint(x: cx, y: tableOrigin.y),
                end: CGPoint(x: cx, y: tableOrigin.y + CGFloat(rows) * rowHeight),
                color: fg, lineWidth: 1
            )), zIndex: 1)
        }

        // Bullets
        let bulletSize: CGFloat = 16
        let bulletY = contentRect.maxY - 120
        let bulletX = contentRect.minX + 12
        let bulletTypes: [VVBulletType] = [.disc, .circle, .square, .checkbox(true), .checkbox(false)]
        for (index, type) in bulletTypes.enumerated() {
            let bx = bulletX + CGFloat(index) * (bulletSize + 18)
            builder.add(kind: .bullet(VVBulletPrimitive(
                position: CGPoint(x: bx, y: bulletY),
                size: bulletSize, color: fg, type: type
            )), zIndex: 2)
        }

        // Pie
        let center = CGPoint(x: contentRect.maxX - 140, y: contentRect.minY + 150)
        let radius: CGFloat = 70
        let angles: [CGFloat] = [0, 0.9, 1.8, 2.6, 4.1, .pi * 2]
        let pieColors: [SIMD4<Float>] = [
            SIMD4(0.3, 0.8, 0.5, 0.9), SIMD4(0.95, 0.6, 0.2, 0.9),
            SIMD4(0.5, 0.6, 0.95, 0.9), SIMD4(0.9, 0.4, 0.6, 0.9),
            SIMD4(0.7, 0.7, 0.75, 0.9),
        ]
        for index in 0..<(angles.count - 1) {
            builder.add(kind: .pieSlice(VVPieSlicePrimitive(
                center: center, radius: radius,
                startAngle: angles[index], endAngle: angles[index + 1],
                color: pieColors[index % pieColors.count]
            )), zIndex: 2)
        }

        // Accent line
        builder.add(kind: .line(VVLinePrimitive(
            start: CGPoint(x: contentRect.minX, y: contentRect.maxY - 20),
            end: CGPoint(x: contentRect.maxX, y: contentRect.maxY - 20),
            thickness: 2,
            color: SIMD4(fg.x, fg.y, fg.z, 0.5)
        )), zIndex: 1)

        return builder.scene
    }

    private static func foregroundColor(for background: SIMD4<Float>) -> SIMD4<Float> {
        let luminance = 0.2126 * background.x + 0.7152 * background.y + 0.0722 * background.z
        return luminance > 0.7 ? .darkText : .lightText
    }

    static func sampleText(for language: VVLanguage) -> String {
        switch language.identifier {
        case VVLanguage.swift.identifier:
            return swiftSample
        case VVLanguage.python.identifier:
            return pythonSample
        case VVLanguage.json.identifier:
            return jsonSample
        case VVLanguage.markdown.identifier:
            return markdownSample
        default:
            return swiftSample
        }
    }
}

private extension Array {
    subscript(safe index: Int) -> Element? {
        indices.contains(index) ? self[index] : nil
    }
}
#endif
