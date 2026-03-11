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
    @State private var pooledBufferMB: Double = 0
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
            MetricLabel(title: "Buf Pool", value: "\(pooledBuffers) (\(String(format: "%.1f", pooledBufferMB)) MB)")
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
            pooledBufferMB = Double(ctx.pooledBufferBytes) / (1024 * 1024)

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
    case transitions = "Transitions"
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
        case .image: return "Image primitives with texture-backed rendering and rounded corners"
        case .blockQuoteBorder: return "Left border used for block quotes"
        case .tableLine: return "Grid lines for table rendering"
        case .pieSlice: return "Pie chart segments with start/end angles"
        case .underline: return "Straight and wavy underlines for text decoration"
        case .path: return "Vector paths with bezier curves, fills, and strokes"
        case .border: return "Per-corner radii and per-side borders on quads"
        case .dashedLine: return "Dashed and patterned line styles"
        case .transform: return "2D affine transforms: rotate, scale, translate"
        case .transitions: return "First-class VVView transitions via .id, .transition, and .animation"
        case .rule: return "VDivider horizontal separators via VVView DSL"
        case .stack: return "VVStack/VVHStack layout with flexible rows and spacers"
        case .layer: return "VVZStack composition for cards, overlays, and stacked surfaces"
        case .vvview: return "Boxes, containers, padding, images, and UI composition via VVView DSL"
        case .combined: return "All primitives rendered together"
        }
    }
}

struct PrimitivesPlaygroundView: View {
    @State private var selected: PrimitiveShowcase = .transitions
    @State private var useDarkBackground = true
    @State private var cornerRadius: Double = 12
    @State private var transitionAutoPlay = true
    @State private var transitionReplayToken = 0
    @State private var transitionSpeed = 1.0

    private struct ShowcaseSection: Identifiable {
        let title: String
        let items: [PrimitiveShowcase]
        var id: String { title }
    }

    private var sections: [ShowcaseSection] {
        [
            ShowcaseSection(
                title: "Animation",
                items: [.transitions, .transform]
            ),
            ShowcaseSection(
                title: "Layout",
                items: [.vvview, .stack, .layer, .rule]
            ),
            ShowcaseSection(
                title: "Drawing",
                items: [
                    .quad, .gradientQuad, .shadowQuad, .line, .dashedLine,
                    .border, .image, .path, .underline, .bullet,
                    .blockQuoteBorder, .tableLine, .pieSlice
                ]
            ),
            ShowcaseSection(
                title: "Text",
                items: [.textRun, .textLayout, .selection]
            ),
            ShowcaseSection(
                title: "Full Scene",
                items: [.combined]
            )
        ]
    }

    private var configuration: PrimitiveSceneConfiguration {
        PrimitiveSceneConfiguration(
            backgroundColor: useDarkBackground ? .darkBackground : .rgba(0.96, 0.96, 0.97),
            showcase: selected,
            cornerRadius: CGFloat(cornerRadius),
            transitionAutoPlay: transitionAutoPlay,
            transitionReplayToken: transitionReplayToken,
            transitionSpeed: transitionSpeed
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

                List(selection: $selected) {
                    ForEach(sections) { section in
                        Section(section.title) {
                            ForEach(section.items) { item in
                                primitiveRow(item)
                                    .tag(item)
                            }
                        }
                    }
                }
                .listStyle(.sidebar)
            }
            .frame(minWidth: 220, idealWidth: 260, maxWidth: 320)

            VStack(spacing: 0) {
                if selected == .transitions {
                    transitionControls
                }

                GeometryReader { proxy in
                    ScrollView([.horizontal, .vertical]) {
                        PrimitiveSceneRepresentable(configuration: configuration)
                            .frame(
                                width: max(proxy.size.width, configuration.minimumCanvasSize.width),
                                height: max(proxy.size.height, configuration.minimumCanvasSize.height)
                            )
                    }
                    .background(Color.black.opacity(useDarkBackground ? 0.18 : 0.03))
                }
            }
        }
    }

    @ViewBuilder
    private func primitiveRow(_ item: PrimitiveShowcase) -> some View {
        VStack(alignment: .leading, spacing: 4) {
            HStack(spacing: 6) {
                Text(item.rawValue)
                    .fontWeight(item == selected ? .semibold : .regular)
                if item == .transitions {
                    Text("API")
                        .font(.system(size: 9, weight: .bold))
                        .padding(.horizontal, 5)
                        .padding(.vertical, 2)
                        .background(Color.orange.opacity(0.18))
                        .foregroundStyle(.orange)
                        .clipShape(Capsule())
                }
            }
            Text(item.description)
                .font(.caption)
                .foregroundStyle(.secondary)
                .lineLimit(2)
        }
        .padding(.vertical, 4)
    }

    private var transitionControls: some View {
        HStack(spacing: 16) {
            VStack(alignment: .leading, spacing: 4) {
                Text("Transitions API Demo")
                    .font(.headline)
                Text("Replay the same first-class `.id`, `.transition`, and `.animation` flow used by the primitives layer.")
                    .font(.caption)
                    .foregroundStyle(.secondary)
            }

            Spacer(minLength: 24)

            Button("Replay") {
                transitionReplayToken &+= 1
            }
            .buttonStyle(.borderedProminent)

            Toggle("Auto Loop", isOn: $transitionAutoPlay)
                .toggleStyle(.switch)
                .frame(width: 120)

            HStack(spacing: 8) {
                Text("Speed")
                    .font(.caption)
                    .foregroundStyle(.secondary)
                Slider(value: $transitionSpeed, in: 0.55...1.8, step: 0.05)
                    .frame(width: 120)
                Text(String(format: "%.2fx", transitionSpeed))
                    .font(.system(.caption, design: .monospaced))
                    .frame(width: 44, alignment: .trailing)
            }
        }
        .padding(.horizontal, 18)
        .padding(.vertical, 12)
        .background(.thinMaterial)
        .overlay(alignment: .bottom) {
            Divider()
        }
    }
}

struct PrimitiveSceneConfiguration: Equatable {
    var backgroundColor: SIMD4<Float>
    var showcase: PrimitiveShowcase
    var cornerRadius: CGFloat
    var transitionAutoPlay: Bool = true
    var transitionReplayToken: Int = 0
    var transitionSpeed: Double = 1

    var minimumCanvasSize: CGSize {
        switch showcase {
        case .vvview:
            return CGSize(width: 1400, height: 920)
        case .transitions:
            return CGSize(width: 1280, height: 860)
        case .combined:
            return CGSize(width: 1500, height: 1100)
        case .stack, .layer, .image, .path, .transform, .border, .dashedLine:
            return CGSize(width: 1100, height: 760)
        default:
            return CGSize(width: 960, height: 680)
        }
    }
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
    private var textureCache: [String: MTLTexture] = [:]
    private var transitionTimer: Timer?
    private var transitionAnimator = VVLayoutTransitionAnimator()
    private var isExpanded = false
    private var scheduledTransitionDate: Date?
    private var scheduledExpandedState: Bool?
    private var lastReplayToken = 0

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
        let previous = self.configuration
        self.configuration = configuration
        lastReplayToken = max(lastReplayToken, previous.transitionReplayToken)
        updateTransitionDriver(previous: previous)
        rebuildScene(force: true)
    }

    override func layout() {
        super.layout()
        metalView.frame = bounds
        updateTransitionDriver()
        rebuildScene(force: false)
    }

    deinit {
        transitionTimer?.invalidate()
    }

    private func rebuildScene(force: Bool) {
        guard force || bounds.size != lastSize else {
            metalView.setNeedsDisplay(bounds)
            return
        }
        lastSize = bounds.size
        scene = currentScene()
        metalView.setNeedsDisplay(bounds)
    }

    private func currentScene() -> VVScene {
        if configuration.showcase == .transitions {
            return SampleData.transitionAnimationScene(
                size: bounds.size,
                configuration: configuration,
                state: transitionAnimator.state().snapshots.isEmpty ? SampleData.transitionAnimationSnapshots(size: bounds.size, configuration: configuration, expanded: isExpanded) : transitionAnimator.state().snapshots,
                expanded: isExpanded
            )
        }
        return SampleData.primitivesScene(size: bounds.size, configuration: configuration)
    }

    private func updateTransitionDriver(previous: PrimitiveSceneConfiguration? = nil) {
        guard configuration.showcase == .transitions else {
            transitionTimer?.invalidate()
            transitionTimer = nil
            scheduledTransitionDate = nil
            scheduledExpandedState = nil
            return
        }

        if transitionTimer == nil {
            let timer = Timer(timeInterval: 1.0 / 60.0, repeats: true) { [weak self] _ in
                self?.transitionTick()
            }
            RunLoop.main.add(timer, forMode: .common)
            transitionTimer = timer
        }

        if transitionAnimator.state().snapshots.isEmpty || previous?.showcase != .transitions {
            setTransitionState(expanded: false)
            if configuration.transitionAutoPlay {
                scheduleTransition(to: true, after: 0.45)
            }
        }

        if configuration.transitionReplayToken != lastReplayToken {
            lastReplayToken = configuration.transitionReplayToken
            replayTransition()
            return
        }

        if previous?.transitionAutoPlay != configuration.transitionAutoPlay,
           configuration.transitionAutoPlay,
           !transitionAnimator.isRunning,
           scheduledExpandedState == nil {
            scheduleTransition(to: !isExpanded, after: 0.9)
        }
    }

    private func transitionTick() {
        guard configuration.showcase == .transitions else { return }
        guard bounds.width > 0, bounds.height > 0 else { return }

        let now = Date()
        if !transitionAnimator.isRunning,
           let target = scheduledExpandedState,
           let due = scheduledTransitionDate,
           now >= due {
            let from = transitionAnimator.state().snapshots
            isExpanded = target
            let to = SampleData.transitionAnimationSnapshots(size: bounds.size, configuration: configuration, expanded: target)
            transitionAnimator.start(
                from: from,
                to: to,
                fallbackTransition: .morph,
                fallbackAnimation: .spring(response: 0.42 / max(0.55, configuration.transitionSpeed), dampingFraction: 0.82)
            )
            scheduledExpandedState = nil
            scheduledTransitionDate = nil
        }

        let wasRunning = transitionAnimator.isRunning
        let state = transitionAnimator.state()
        scene = SampleData.transitionAnimationScene(size: bounds.size, configuration: configuration, state: state.snapshots, expanded: isExpanded)
        metalView.setNeedsDisplay(bounds)

        if wasRunning && state.isComplete {
            transitionAnimator.complete(with: state.snapshots)
            if configuration.transitionAutoPlay {
                scheduleTransition(to: !isExpanded, after: 1.0)
            }
        }
    }

    private func setTransitionState(expanded: Bool) {
        isExpanded = expanded
        let snapshots = SampleData.transitionAnimationSnapshots(size: bounds.size, configuration: configuration, expanded: expanded)
        transitionAnimator.complete(with: snapshots)
        scene = SampleData.transitionAnimationScene(size: bounds.size, configuration: configuration, state: snapshots, expanded: expanded)
        metalView.setNeedsDisplay(bounds)
    }

    private func scheduleTransition(to expanded: Bool, after delay: TimeInterval) {
        scheduledExpandedState = expanded
        scheduledTransitionDate = .now.addingTimeInterval(delay / max(0.55, configuration.transitionSpeed))
    }

    private func replayTransition() {
        guard configuration.showcase == .transitions else { return }
        setTransitionState(expanded: false)
        scheduleTransition(to: true, after: 0.12)
    }

    var renderItemCount: Int { 1 }
    func visibleRenderIndexes() -> Range<Int> { 0..<1 }

    func renderItem(at index: Int, visibleRect: CGRect) -> VVChatTimelineRenderItem? {
        guard index == 0 else { return nil }
        let orderedPrimitiveIndices = scene.primitives.enumerated().sorted { lhs, rhs in
            if lhs.element.zIndex == rhs.element.zIndex {
                return lhs.offset < rhs.offset
            }
            return lhs.element.zIndex < rhs.element.zIndex
        }.map(\.offset)
        let visibilityIndex = VVPrimitiveVisibilityIndex(
            scene: scene,
            orderedPrimitiveIndices: orderedPrimitiveIndices,
            bucketHeight: 192
        )
        return VVChatTimelineRenderItem(
            id: "primitives",
            frame: bounds,
            contentOffset: .zero,
            layers: [
                VVChatTimelineRenderLayer(
                    offset: .zero,
                    scene: scene,
                    orderedPrimitiveIndices: orderedPrimitiveIndices,
                    visibilityIndex: visibilityIndex
                )
            ]
        )
    }

    var viewportRect: CGRect { bounds }

    var backgroundColor: SIMD4<Float> { configuration.backgroundColor }

    func texture(for url: String) -> MTLTexture? {
        if let cached = textureCache[url] {
            return cached
        }
        guard let device = metalView.device else { return nil }
        let texture = makeDemoTexture(for: url, device: device)
        textureCache[url] = texture
        return texture
    }

    private func makeDemoTexture(for url: String, device: MTLDevice) -> MTLTexture? {
        let width = 192
        let height = 128
        let descriptor = MTLTextureDescriptor.texture2DDescriptor(pixelFormat: .rgba8Unorm, width: width, height: height, mipmapped: false)
        descriptor.usage = .shaderRead
        guard let texture = device.makeTexture(descriptor: descriptor) else { return nil }

        var pixels = [UInt8](repeating: 0, count: width * height * 4)
        let hash = abs(url.hashValue)
        let baseHue = Float(hash % 360) / 360.0
        let accentHue = fmodf(baseHue + 0.18, 1)

        func hueColor(_ hue: Float, brightness: Float) -> SIMD3<Float> {
            let h = hue * 6
            let c = brightness * 0.9
            let x = c * (1 - abs(fmodf(h, 2) - 1))
            switch Int(h) {
            case 0: return SIMD3(c, x, 0.22)
            case 1: return SIMD3(x, c, 0.22)
            case 2: return SIMD3(0.22, c, x)
            case 3: return SIMD3(0.22, x, c)
            case 4: return SIMD3(x, 0.22, c)
            default: return SIMD3(c, 0.22, x)
            }
        }

        let topColor = hueColor(baseHue, brightness: 0.95)
        let bottomColor = hueColor(accentHue, brightness: 0.72)

        for y in 0..<height {
            let t = Float(y) / Float(max(1, height - 1))
            let rowColor = topColor + (bottomColor - topColor) * t
            for x in 0..<width {
                let xf = Float(x) / Float(max(1, width - 1))
                let stripe: Float = ((x / 18) + (y / 18)) % 2 == 0 ? 0.08 : -0.04
                let vignette = Float(1 - pow(Double((xf - 0.5) * 1.35), 2))
                let highlight = max(Float(0), Float(0.18) - abs(xf - Float(0.24))) * Float(0.6)
                let r = min(Float(1), max(Float(0), rowColor.x + stripe + highlight + vignette * Float(0.04)))
                let g = min(Float(1), max(Float(0), rowColor.y + stripe + vignette * Float(0.03)))
                let b = min(Float(1), max(Float(0), rowColor.z + stripe + vignette * Float(0.02)))
                let index = (y * width + x) * 4
                pixels[index] = UInt8(r * 255)
                pixels[index + 1] = UInt8(g * 255)
                pixels[index + 2] = UInt8(b * 255)
                pixels[index + 3] = 255
            }
        }

        let bytesPerRow = width * 4
        texture.replace(region: MTLRegionMake2D(0, 0, width, height), mipmapLevel: 0, withBytes: pixels, bytesPerRow: bytesPerRow)
        return texture
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
    @State private var simulationTask: Task<Void, Never>?
    @State private var isAutoRunning = false
    @State private var chunkDelay: Double = 0.05
    @State private var pauseBetweenTurns: Double = 1.1
    @State private var expandNewToolGroups = true
    @State private var includeInterrupts = true
    @State private var expandedToolGroupIDs: Set<String> = []
    @State private var toolGroupsByID: [String: PlaygroundToolGroup] = [:]
    @State private var nextScriptedTurn = 0
    @State private var chatState = VVChatTimelineState()
    var body: some View {
        HSplitView {
            VStack(alignment: .leading, spacing: 12) {
                Text("Aizen Chat")
                    .font(.headline)

                Toggle("Light Theme", isOn: $useLightTheme)
                HStack {
                    Text("Font")
                    Slider(value: $fontSize, in: 11...20, step: 1)
                    Text("\(Int(fontSize))")
                        .frame(width: 28, alignment: .trailing)
                }

                Divider()

                Button("Seed Aizen Transcript") {
                    seedTranscript()
                }

                Button("Append Scripted Turn") {
                    Task { await runNextTurn() }
                }

                Toggle("Expand New Tool Groups", isOn: $expandNewToolGroups)
                Toggle("Include Interrupts", isOn: $includeInterrupts)

                HStack {
                    Text("Chunk Delay")
                    Slider(value: $chunkDelay, in: 0.02...0.18, step: 0.01)
                    Text(String(format: "%.02fs", chunkDelay))
                        .frame(width: 52, alignment: .trailing)
                }

                HStack {
                    Text("Turn Pause")
                    Slider(value: $pauseBetweenTurns, in: 0.3...2.2, step: 0.1)
                    Text(String(format: "%.01fs", pauseBetweenTurns))
                        .frame(width: 44, alignment: .trailing)
                }

                Divider()

                Button(isAutoRunning ? "Stop Auto" : "Start Auto") {
                    isAutoRunning ? stopAutoSimulation() : startAutoSimulation()
                }
                .buttonStyle(.borderedProminent)

                Divider()

                Button("Clear Timeline") {
                    stopAutoSimulation()
                    expandedToolGroupIDs = []
                    toolGroupsByID = [:]
                    controller.setEntries([], scrollToBottom: true, customEntryMessageMapper: customEntryMapper())
                }

                Spacer()
            }
            .padding(16)
            .frame(minWidth: 240, idealWidth: 280, maxWidth: 340)

            PlaygroundChatTimelineHost(
                controller: controller,
                onStateChange: handleStateChange,
                onEntryActivate: handleEntryActivate,
                onLinkActivate: handleLinkActivate
            )
        }
        .onAppear {
            if !didSeed {
                seedTranscript()
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
        .onChange(of: includeInterrupts) { _ in
            seedTranscript()
        }
    }

    private func updateChatStyle() {
        controller.updateStyle(SampleData.chatStyle(dark: !useLightTheme, fontSize: fontSize))
        rebuildTimelineFromController(scrollToBottom: controller.state.shouldAutoFollow)
    }

    private func handleStateChange(_ state: VVChatTimelineState) {
        withAnimation(.easeOut(duration: 0.2)) {
            chatState = state
        }
    }

    private func seedTranscript() {
        stopAutoSimulation()
        nextScriptedTurn = 0
        let seedItems = SampleData.aizenSeedTimelineItems(includeInterrupts: includeInterrupts)
        expandedToolGroupIDs = Set(seedItems.compactMap { item in
            guard case .toolGroup(let group) = item else { return nil }
            return group.id
        })
        toolGroupsByID = Dictionary(
            uniqueKeysWithValues: seedItems.compactMap { item in
                guard case .toolGroup(let group) = item else { return nil }
                return (group.id, group)
            }
        )
        controller.setEntries(
            buildEntries(from: seedItems),
            scrollToBottom: true,
            customEntryMessageMapper: customEntryMapper()
        )
    }

    private func rebuildTimelineFromController(scrollToBottom: Bool, animatedAnchorID: String? = nil) {
        if let animatedAnchorID {
            controller.prepareLayoutTransition(anchorItemID: animatedAnchorID)
        }
        controller.setEntries(
            buildEntries(from: controllerBaseEntries()),
            scrollToBottom: scrollToBottom,
            customEntryMessageMapper: customEntryMapper()
        )
    }

    private func controllerBaseEntries() -> [VVChatTimelineEntry] {
        controller.entries.filter { entry in
            guard case .custom(let custom) = entry else { return true }
            return custom.kind != "toolCallDetail" && custom.kind != "toolCallInlineDiff"
        }
    }

    private func expandedToolEntries(for group: PlaygroundToolGroup) -> [VVChatTimelineEntry] {
        guard expandedToolGroupIDs.contains(group.id) else { return [] }
        var entries: [VVChatTimelineEntry] = []
        entries.reserveCapacity(group.toolCalls.count * 2)
        for call in group.toolCalls {
            entries.append(.custom(toolDetailEntry(for: call, group: group)))
            if let diffEntry = toolInlineDiffEntry(for: call, group: group) {
                entries.append(.custom(diffEntry))
            }
        }
        return entries
    }

    private func toolEntryRange(afterGroupID groupID: String) -> Range<Int>? {
        guard let groupIndex = controller.entries.firstIndex(where: { $0.id == groupID }) else {
            return nil
        }

        var end = groupIndex + 1
        while end < controller.entries.count {
            guard case .custom(let custom) = controller.entries[end],
                  custom.id.hasPrefix("\(groupID)::") else {
                break
            }
            end += 1
        }
        return (groupIndex + 1)..<end
    }

    private func upsertToolGroupBlock(
        _ group: PlaygroundToolGroup,
        replacingExistingGroup: Bool,
        scrollToBottom: Bool,
        markUnread: Bool = true,
        animatedAnchorID: String? = nil
    ) {
        if let animatedAnchorID {
            controller.prepareLayoutTransition(anchorItemID: animatedAnchorID)
        }

        let desiredEntries = [VVChatTimelineEntry.custom(groupEntry(for: group))] + expandedToolEntries(for: group)
        if replacingExistingGroup,
           let groupIndex = controller.entries.firstIndex(where: { $0.id == group.id }) {
            let replacementRange = groupIndex..<(toolEntryRange(afterGroupID: group.id)?.upperBound ?? (groupIndex + 1))
            controller.replaceEntries(
                in: replacementRange,
                with: desiredEntries,
                scrollToBottom: scrollToBottom,
                markUnread: markUnread
            )
        } else {
            let insertIndex = controller.entries.count
            controller.replaceEntries(
                in: insertIndex..<insertIndex,
                with: desiredEntries,
                scrollToBottom: scrollToBottom,
                markUnread: markUnread
            )
        }
    }

    private func syncExpandedToolGroupEntries(for groupID: String, scrollToBottom: Bool, animatedAnchorID: String? = nil) {
        guard let group = toolGroupsByID[groupID],
              let toolRange = toolEntryRange(afterGroupID: groupID) else {
            return
        }
        if let animatedAnchorID {
            controller.prepareLayoutTransition(anchorItemID: animatedAnchorID)
        }
        controller.replaceEntries(
            in: toolRange,
            with: expandedToolEntries(for: group),
            scrollToBottom: scrollToBottom,
            markUnread: false
        )
    }

    private func buildEntries(from items: [PlaygroundChatTimelineItem]) -> [VVChatTimelineEntry] {
        buildEntries(
            from: items.map { item in
                switch item {
                case .message(let message):
                    return .message(chatMessage(from: message, startsAssistantLane: false))
                case .toolGroup(let group):
                    return .custom(groupEntry(for: group))
                case .turnSummary(let summary):
                    return .custom(turnSummaryEntry(for: summary))
                }
            }
        )
    }

    private func buildEntries(from baseEntries: [VVChatTimelineEntry]) -> [VVChatTimelineEntry] {
        var entries: [VVChatTimelineEntry] = []
        entries.reserveCapacity(baseEntries.count * 2)
        var hasRenderedAssistantMessageInTurn = false

        for entry in baseEntries {
            switch entry {
            case .message(let message):
                let startsAssistantLane = message.role == .assistant && !hasRenderedAssistantMessageInTurn
                entries.append(.message(restyledMessage(message, startsAssistantLane: startsAssistantLane)))
                hasRenderedAssistantMessageInTurn = message.role == .assistant

            case .custom(let custom):
                entries.append(.custom(custom))
                if custom.kind == "toolCallGroup",
                   expandedToolGroupIDs.contains(custom.id),
                   let group = toolGroupsByID[custom.id] {
                    for call in group.toolCalls {
                        entries.append(.custom(toolDetailEntry(for: call, group: group)))
                        if let diffEntry = toolInlineDiffEntry(for: call, group: group) {
                            entries.append(.custom(diffEntry))
                        }
                    }
                }
                if custom.kind == "turnSummary" {
                    hasRenderedAssistantMessageInTurn = false
                }
            }
        }

        return entries
    }

    private func restyledMessage(
        _ message: VVChatMessage,
        startsAssistantLane: Bool
    ) -> VVChatMessage {
        VVChatMessage(
            id: message.id,
            role: message.role,
            state: message.state,
            content: message.content,
            revision: message.revision,
            timestamp: message.timestamp,
            presentation: messagePresentation(for: message, startsAssistantLane: startsAssistantLane),
            customContent: message.customContent
        )
    }

    private func storeToolGroup(_ group: PlaygroundToolGroup, replacing previousID: String? = nil) {
        if let previousID {
            toolGroupsByID.removeValue(forKey: previousID)
            if previousID != group.id, expandedToolGroupIDs.remove(previousID) != nil {
                expandedToolGroupIDs.insert(group.id)
            }
        }
        toolGroupsByID[group.id] = group
    }

    private func chatMessage(from message: PlaygroundChatMessage, startsAssistantLane: Bool) -> VVChatMessage {
        VVChatMessage(
            id: message.id,
            role: message.role,
            state: message.state,
            content: message.content,
            revision: message.revision,
            timestamp: message.timestamp,
            presentation: messagePresentation(for: message, startsAssistantLane: startsAssistantLane)
        )
    }

    private func messagePresentation(for message: VVChatMessage, startsAssistantLane: Bool) -> VVChatMessagePresentation? {
        switch message.role {
        case .user:
            return VVChatMessagePresentation(
                timestampPrefixIconURL: timelineSymbolIconURL("clock", fallbackID: "timestamp-clock"),
                timestampSuffixIconURL: timelineSymbolIconURL("doc.on.doc", fallbackID: "copy-user"),
                timestampIconSize: max(14, CGFloat(fontSize) - 0.5),
                timestampIconSpacing: 6
            )
        case .assistant:
            return VVChatMessagePresentation(
                bubbleStyle: VVChatBubbleStyle(
                    isEnabled: true,
                    color: .clear,
                    borderColor: .clear,
                    borderWidth: 0,
                    cornerRadius: 0,
                    insets: .init(top: 0, left: 0, bottom: 4, right: 0),
                    maxWidth: 4000,
                    alignment: .leading
                ),
                showsHeader: false,
                leadingLaneWidth: 0,
                leadingIconURL: startsAssistantLane ? timelineSymbolIconURL("sparkles", fallbackID: "assistant-lane") : nil,
                leadingIconSize: startsAssistantLane ? 0 : nil,
                leadingIconSpacing: startsAssistantLane ? 0 : nil,
                showsTimestamp: false
            )
        case .system:
            return VVChatMessagePresentation(
                showsHeader: false,
                showsTimestamp: false,
                contentFontScale: 0.78,
                textOpacityMultiplier: !useLightTheme ? 0.5 : 0.58
            )
        }
    }

    private func messagePresentation(for message: PlaygroundChatMessage, startsAssistantLane: Bool) -> VVChatMessagePresentation? {
        switch message.role {
        case .user:
            return VVChatMessagePresentation(
                timestampPrefixIconURL: timelineSymbolIconURL("clock", fallbackID: "timestamp-clock"),
                timestampSuffixIconURL: timelineSymbolIconURL("doc.on.doc", fallbackID: "copy-user"),
                timestampIconSize: max(14, CGFloat(fontSize) - 0.5),
                timestampIconSpacing: 6
            )
        case .assistant:
            return VVChatMessagePresentation(
                bubbleStyle: VVChatBubbleStyle(
                    isEnabled: true,
                    color: .clear,
                    borderColor: .clear,
                    borderWidth: 0,
                    cornerRadius: 0,
                    insets: .init(top: 0, left: 0, bottom: 4, right: 0),
                    maxWidth: 4000,
                    alignment: .leading
                ),
                showsHeader: false,
                leadingLaneWidth: 0,
                leadingIconURL: startsAssistantLane ? timelineSymbolIconURL("sparkles", fallbackID: "assistant-lane") : nil,
                leadingIconSize: startsAssistantLane ? 0 : nil,
                leadingIconSpacing: startsAssistantLane ? 0 : nil,
                showsTimestamp: false
            )
        case .system:
            return VVChatMessagePresentation(
                showsHeader: false,
                showsTimestamp: false,
                contentFontScale: 0.78,
                textOpacityMultiplier: !useLightTheme ? 0.5 : 0.58
            )
        }
    }

    private func groupEntry(for group: PlaygroundToolGroup) -> VVCustomTimelineEntry {
        let payload = PlaygroundTimelineCustomPayload(
            title: group.title,
            body: "",
            status: group.status.rawValue,
            toolKind: nil,
            showsAgentLaneIcon: false,
            badges: nil,
            summaryCard: nil
        )
        return VVCustomTimelineEntry(
            id: group.id,
            kind: "toolCallGroup",
            payload: encodeCustomPayload(payload, fallback: group.title),
            revision: group.revision,
            timestamp: group.timestamp
        )
    }

    private func toolDetailEntry(for call: PlaygroundToolCall, group: PlaygroundToolGroup) -> VVCustomTimelineEntry {
        let payload = PlaygroundTimelineCustomPayload(
            title: call.title,
            body: "",
            status: call.status.rawValue,
            toolKind: call.kind.rawValue,
            showsAgentLaneIcon: false,
            badges: call.badges.map {
                PayloadBadge(text: $0.text, r: $0.color.x, g: $0.color.y, b: $0.color.z, a: $0.color.w)
            },
            summaryCard: nil
        )
        return VVCustomTimelineEntry(
            id: "\(group.id)::\(call.id)",
            kind: "toolCallDetail",
            payload: encodeCustomPayload(payload, fallback: call.title),
            revision: group.revision ^ call.revision,
            timestamp: call.timestamp
        )
    }

    private func turnSummaryEntry(for summary: PlaygroundTurnSummary) -> VVCustomTimelineEntry {
        let payload = PlaygroundTimelineCustomPayload(
            title: nil,
            body: "\(summary.toolCallCount) tool calls • \(summary.formattedDuration)",
            status: "completed",
            toolKind: nil,
            showsAgentLaneIcon: false,
            badges: nil,
            summaryCard: PayloadSummaryCard(
                title: "Turn Summary",
                subtitle: "\(summary.toolCallCount) tool call\(summary.toolCallCount == 1 ? "" : "s") • \(summary.formattedDuration)",
                rows: summary.files.map { file in
                    PayloadSummaryRow(
                        id: file.id,
                        title: file.compactTitle,
                        subtitle: nil,
                        iconURL: summaryFileIconURL(for: file.path),
                        actionURL: "playground-file://\(file.path.addingPercentEncoding(withAllowedCharacters: .urlPathAllowed) ?? file.path)",
                        additionsText: "+\(file.linesAdded)",
                        deletionsText: "-\(file.linesRemoved)"
                    )
                }
            )
        )
        return VVCustomTimelineEntry(
            id: summary.id,
            kind: "turnSummary",
            payload: encodeCustomPayload(payload, fallback: "Turn Summary"),
            revision: summary.revision,
            timestamp: summary.timestamp
        )
    }

    private func toolInlineDiffEntry(for call: PlaygroundToolCall, group: PlaygroundToolGroup) -> VVCustomTimelineEntry? {
        guard let diff = call.diff?.trimmingCharacters(in: .whitespacesAndNewlines), !diff.isEmpty else {
            return nil
        }
        let payload = PlaygroundTimelineCustomPayload(
            title: nil,
            body: diff,
            status: call.status.rawValue,
            toolKind: call.kind.rawValue,
            showsAgentLaneIcon: false,
            badges: nil,
            summaryCard: nil
        )
        return VVCustomTimelineEntry(
            id: "\(group.id)::\(call.id)::diff",
            kind: "toolCallInlineDiff",
            payload: encodeCustomPayload(payload, fallback: diff),
            revision: group.revision ^ call.revision ^ 1,
            timestamp: call.timestamp
        )
    }

    private func customEntryMapper() -> VVChatTimelineController.CustomEntryMessageMapper {
        { custom in
            let decoded = decodeCustomPayload(from: custom.payload)
            let body = decoded?.body ?? String(data: custom.payload, encoding: .utf8) ?? ""
            let title = decoded?.title?.trimmingCharacters(in: .whitespacesAndNewlines)
            let statusTint = toolGroupStatusNSColor(statusRawValue: decoded?.status)
            let showsHeader = title?.isEmpty == false

            switch custom.kind {
            case "toolCallGroup":
                return VVChatMessage(
                    id: custom.id,
                    role: .assistant,
                    state: .final,
                    content: body,
                    revision: custom.revision,
                    timestamp: custom.timestamp,
                    presentation: VVChatMessagePresentation(
                        bubbleStyle: nil,
                        showsHeader: showsHeader,
                        headerTitle: title,
                        headerIconURL: timelineSymbolIconURL("square.stack.3d.up", fallbackID: "tool-group", tintColor: statusTint),
                        headerTrailingIconURL: timelineSymbolIconURL(
                            expandedToolGroupIDs.contains(custom.id) ? "chevron.down" : "chevron.right",
                            fallbackID: expandedToolGroupIDs.contains(custom.id) ? "chevron-down" : "chevron-right",
                            tintColor: headerIconTintColor
                        ),
                        leadingLaneWidth: 0,
                        showsTimestamp: false,
                        contentFontScale: 0.74,
                        textOpacityMultiplier: dimmedMetaOpacity
                    )
                )

            case "toolCallDetail":
                let badges = decoded?.badges?.map {
                    VVHeaderBadge(text: $0.text, color: SIMD4<Float>($0.r, $0.g, $0.b, $0.a))
                }
                return VVChatMessage(
                    id: custom.id,
                    role: .assistant,
                    state: .final,
                    content: "",
                    revision: custom.revision,
                    timestamp: custom.timestamp,
                    presentation: VVChatMessagePresentation(
                        bubbleStyle: nil,
                        showsHeader: showsHeader,
                        headerTitle: title,
                        headerIconURL: timelineSymbolIconURL(
                            toolHeaderSymbol(for: decoded?.toolKind),
                            fallbackID: "tool-\(decoded?.toolKind ?? "unknown")",
                            tintColor: statusTint
                        ),
                        leadingLaneWidth: 0,
                        showsTimestamp: false,
                        contentFontScale: 0.72,
                        textOpacityMultiplier: dimmedMetaOpacity * 0.93,
                        headerBadges: badges
                    )
                )

            case "toolCallInlineDiff":
                return VVChatMessage(
                    id: custom.id,
                    role: .assistant,
                    state: .final,
                    content: "",
                    revision: custom.revision,
                    timestamp: custom.timestamp,
                    presentation: VVChatMessagePresentation(
                        bubbleStyle: nil,
                        showsHeader: false,
                        leadingLaneWidth: 0,
                        showsTimestamp: false,
                        contentFontScale: 0.82,
                        textOpacityMultiplier: 0.97
                    ),
                    customContent: .inlineDiff(.init(unifiedDiff: body))
                )

            case "turnSummary":
                let summaryCard = decoded?.summaryCard.map(makeSummaryCard(from:))
                return VVChatMessage(
                    id: custom.id,
                    role: .assistant,
                    state: .final,
                    content: "",
                    revision: custom.revision,
                    timestamp: custom.timestamp,
                    presentation: VVChatMessagePresentation(
                        bubbleStyle: turnSummaryBubbleStyle,
                        showsHeader: false,
                        leadingLaneWidth: 0,
                        showsTimestamp: false,
                        contentFontScale: 0.86,
                        textOpacityMultiplier: !useLightTheme ? 0.86 : 0.90
                    ),
                    customContent: summaryCard.map { .summaryCard($0) }
                )

            default:
                return VVChatMessage(
                    id: custom.id,
                    role: .system,
                    state: .final,
                    content: body,
                    revision: custom.revision,
                    timestamp: custom.timestamp
                )
            }
        }
    }

    private var headerIconTintColor: NSColor {
        if useLightTheme {
            return NSColor(calibratedWhite: 0.18, alpha: 1)
        }
        return NSColor(calibratedWhite: 0.94, alpha: 1)
    }

    private var dimmedMetaOpacity: Float {
        useLightTheme ? 0.50 : 0.40
    }

    private var turnSummaryBubbleStyle: VVChatBubbleStyle {
        VVChatBubbleStyle(
            isEnabled: true,
            color: useLightTheme ? .rgba(0.98, 0.985, 0.992, 0.98) : .rgba(0.12, 0.14, 0.17, 0.92),
            borderColor: useLightTheme ? .rgba(0.56, 0.60, 0.68, 0.18) : .rgba(0.52, 0.56, 0.62, 0.34),
            borderWidth: 0.8,
            cornerRadius: 14,
            insets: .init(top: 10, left: 14, bottom: 10, right: 14),
            maxWidth: 4000,
            alignment: .leading
        )
    }

    private func makeSummaryCard(from payload: PayloadSummaryCard) -> VVChatSummaryCard {
        VVChatSummaryCard(
            title: payload.title,
            iconURL: timelineSymbolIconURL("checklist", fallbackID: "turn-summary", tintColor: headerIconTintColor, pointSize: 12),
            subtitle: payload.subtitle,
            rows: payload.rows.map { row in
                VVChatSummaryCardRow(
                        id: row.id,
                        title: row.title,
                        subtitle: row.subtitle,
                        iconURL: row.iconURL,
                        actionURL: row.actionURL,
                    titleColor: useLightTheme ? .rgba(0.12, 0.14, 0.18, 1) : .rgba(0.96, 0.97, 0.99, 1),
                    subtitleColor: useLightTheme ? .rgba(0.34, 0.38, 0.46, 0.92) : .rgba(0.83, 0.85, 0.90, 0.92),
                    additionsText: row.additionsText,
                    additionsColor: useLightTheme ? .rgba(0.11, 0.60, 0.25, 1) : .rgba(0.50, 0.86, 0.62, 1),
                    deletionsText: row.deletionsText,
                    deletionsColor: useLightTheme ? .rgba(0.78, 0.36, 0.08, 1) : .rgba(0.94, 0.69, 0.48, 1),
                    hoverFillColor: useLightTheme ? .rgba(0.14, 0.20, 0.30, 0.03) : .rgba(0.86, 0.90, 0.98, 0.035)
                )
            },
            titleColor: useLightTheme ? .rgba(0.12, 0.14, 0.18, 1) : .rgba(0.96, 0.97, 0.99, 1),
            subtitleColor: useLightTheme ? .rgba(0.34, 0.38, 0.46, 0.92) : .rgba(0.83, 0.85, 0.90, 0.92),
            dividerColor: useLightTheme ? .rgba(0.56, 0.60, 0.68, 0.18) : .rgba(0.52, 0.56, 0.62, 0.34),
            rowDividerColor: useLightTheme ? .rgba(0.56, 0.60, 0.68, 0.12) : .rgba(0.52, 0.56, 0.62, 0.18)
        )
    }

    private func timelineSymbolIconURL(
        _ symbolName: String,
        fallbackID: String,
        tintColor: NSColor? = nil,
        pointSize: CGFloat? = nil
    ) -> String? {
        PlaygroundHeaderIconStore.urlString(
            for: .sfSymbol(symbolName),
            fallbackAgentId: fallbackID,
            tintColor: tintColor,
            targetPointSize: pointSize ?? 14
        )
    }

    private func summaryFileIconURL(for path: String) -> String? {
        let ext = URL(fileURLWithPath: path).pathExtension
        let contentType = UTType(filenameExtension: ext.isEmpty ? "txt" : ext) ?? .plainText
        let icon = NSWorkspace.shared.icon(for: contentType)
        guard let data = icon.tiffRepresentation else { return nil }
        return PlaygroundHeaderIconStore.urlString(
            for: .customImage(data),
            fallbackAgentId: "summary-file-\(path.hashValue)",
            tintColor: nil,
            targetPointSize: 16
        )
    }

    private func toolHeaderSymbol(for rawKind: String?) -> String {
        switch rawKind {
        case "read":
            return "doc.text.magnifyingglass"
        case "edit":
            return "pencil"
        case "delete":
            return "trash"
        case "move":
            return "arrow.left.and.right.square"
        case "task":
            return "checklist"
        case "execute":
            return "terminal"
        case "search":
            return "magnifyingglass"
        case "think":
            return "brain.head.profile"
        case "fetch":
            return "globe"
        case "plan":
            return "list.bullet.clipboard"
        case "switchMode":
            return "arrow.triangle.swap"
        default:
            return "wrench.and.screwdriver"
        }
    }

    private func toolGroupStatusNSColor(statusRawValue: String?) -> NSColor {
        switch statusRawValue {
        case "failed":
            return useLightTheme
                ? NSColor(red: 0.82, green: 0.24, blue: 0.28, alpha: 1)
                : NSColor(red: 0.92, green: 0.42, blue: 0.44, alpha: 1)
        case "in_progress":
            return useLightTheme
                ? NSColor(red: 0.88, green: 0.62, blue: 0.06, alpha: 1)
                : NSColor(red: 0.98, green: 0.78, blue: 0.36, alpha: 1)
        default:
            return headerIconTintColor
        }
    }

    private func startAutoSimulation() {
        guard !isAutoRunning else { return }
        isAutoRunning = true
        simulationTask?.cancel()
        simulationTask = Task {
            while !Task.isCancelled {
                let running = await MainActor.run { isAutoRunning }
                if !running { break }
                await runNextTurn()
                try? await Task.sleep(nanoseconds: UInt64(pauseBetweenTurns * 1_000_000_000))
            }
        }
    }

    private func stopAutoSimulation() {
        isAutoRunning = false
        simulationTask?.cancel()
        simulationTask = nil
    }

    private func runNextTurn() async {
        let scriptedTurns = SampleData.aizenScriptedTurns(includeInterrupts: includeInterrupts)
        guard !scriptedTurns.isEmpty else { return }
        let sequence = nextScriptedTurn
        let baseTurn = scriptedTurns[sequence % scriptedTurns.count]
        let turn = uniquedTurn(baseTurn, sequence: sequence)
        nextScriptedTurn += 1

        await MainActor.run {
            prepareAppendTransition()
            controller.appendMessage(chatMessage(from: turn.userMessage, startsAssistantLane: false))
        }

        let draftID = "assistant-draft-\(UUID().uuidString)"
        var currentDraft = PlaygroundChatMessage(
            id: draftID,
            role: .assistant,
            state: .draft,
            content: "",
            revision: 0,
            timestamp: turn.agentPreface.timestamp
        )
        await MainActor.run {
            prepareAppendTransition()
            controller.appendMessage(chatMessage(from: currentDraft, startsAssistantLane: true))
        }

        for chunk in markdownStreamingSegments(for: turn.agentPreface.content) {
            if Task.isCancelled { return }
            currentDraft.content += chunk
            currentDraft.revision += 1
            await MainActor.run {
                controller.updateDraftMessage(id: currentDraft.id, content: currentDraft.content, throttle: true)
            }
            try? await Task.sleep(nanoseconds: UInt64(chunkDelay * 1_000_000_000))
        }

        currentDraft.state = .final
        currentDraft.revision += 1
        await MainActor.run {
            controller.prepareLayoutTransition(anchorItemID: currentDraft.id)
            controller.replaceEntry(
                id: currentDraft.id,
                with: .message(chatMessage(from: currentDraft, startsAssistantLane: true))
            )

            storeToolGroup(turn.toolGroup.inProgressVersion)
            if expandNewToolGroups {
                expandedToolGroupIDs.insert(turn.toolGroup.inProgressVersion.id)
            }
            prepareAppendTransition()
            upsertToolGroupBlock(
                turn.toolGroup.inProgressVersion,
                replacingExistingGroup: false,
                scrollToBottom: controller.state.shouldAutoFollow,
                markUnread: true
            )
        }

        try? await Task.sleep(nanoseconds: UInt64(max(chunkDelay, 0.05) * 5 * 1_000_000_000))

        await MainActor.run {
            storeToolGroup(turn.toolGroup.completedVersion, replacing: turn.toolGroup.inProgressVersion.id)
            upsertToolGroupBlock(
                turn.toolGroup.completedVersion,
                replacingExistingGroup: true,
                scrollToBottom: controller.state.shouldAutoFollow,
                markUnread: false,
                animatedAnchorID: turn.toolGroup.completedVersion.id
            )
        }

        let finalAssistant = PlaygroundChatMessage(
            id: "assistant-final-\(UUID().uuidString)",
            role: .assistant,
            state: .draft,
            content: "",
            revision: 0,
            timestamp: turn.agentFinal.timestamp
        )
        await MainActor.run {
            prepareAppendTransition()
            controller.appendMessage(chatMessage(from: finalAssistant, startsAssistantLane: false))
        }
        var streamedFinal = finalAssistant
        for chunk in markdownStreamingSegments(for: turn.agentFinal.content) {
            if Task.isCancelled { return }
            streamedFinal.content += chunk
            streamedFinal.revision += 1
            await MainActor.run {
                controller.updateDraftMessage(id: streamedFinal.id, content: streamedFinal.content, throttle: true)
            }
            try? await Task.sleep(nanoseconds: UInt64(chunkDelay * 1_000_000_000))
        }

        streamedFinal.state = .final
        streamedFinal.revision += 1
        await MainActor.run {
            controller.prepareLayoutTransition(anchorItemID: streamedFinal.id)
            controller.replaceEntry(
                id: streamedFinal.id,
                with: .message(chatMessage(from: streamedFinal, startsAssistantLane: false))
            )

            prepareAppendTransition()
            controller.appendCustomEntry(turnSummaryEntry(for: turn.summary))
            if let systemMessage = turn.systemMessage, includeInterrupts {
                prepareAppendTransition()
                controller.appendMessage(chatMessage(from: systemMessage, startsAssistantLane: false))
            }
        }
    }

    private func prepareAppendTransition() {
        let anchorID = controller.entries.last?.id
        if let anchorID {
            controller.prepareLayoutTransition(anchorItemID: anchorID)
        }
    }

    private func handleEntryActivate(_ entryID: String) {
        let hadStateChange: Bool
        if expandedToolGroupIDs.contains(entryID) {
            expandedToolGroupIDs.remove(entryID)
            hadStateChange = true
        } else if toolGroupsByID[entryID] != nil {
            expandedToolGroupIDs.insert(entryID)
            hadStateChange = true
        } else {
            hadStateChange = false
        }
        if hadStateChange {
            syncExpandedToolGroupEntries(
                for: entryID,
                scrollToBottom: controller.state.shouldAutoFollow,
                animatedAnchorID: entryID
            )
        }
    }

    private func handleLinkActivate(_ url: String) {
        guard let parsed = URL(string: url), parsed.scheme == "playground-file" else { return }
    }

    private func uniquedTurn(_ turn: PlaygroundScriptedTurn, sequence: Int) -> PlaygroundScriptedTurn {
        let suffix = "-loop-\(sequence + 1)"
        let offset = TimeInterval(sequence * 60)

        func uniquedMessage(_ message: PlaygroundChatMessage?) -> PlaygroundChatMessage? {
            guard let message else { return nil }
            return PlaygroundChatMessage(
                id: message.id + suffix,
                role: message.role,
                state: message.state,
                content: sequence == 0 ? message.content : "\(message.content)\n\n_Turn \(sequence + 1)_",
                revision: message.revision,
                timestamp: message.timestamp?.addingTimeInterval(offset)
            )
        }

        let inProgressCalls = turn.toolGroup.inProgressVersion.toolCalls.map { call in
            PlaygroundToolCall(
                id: call.id + suffix,
                title: call.title,
                kind: call.kind,
                status: call.status,
                badges: call.badges,
                timestamp: call.timestamp.addingTimeInterval(offset),
                revision: call.revision
            )
        }
        let completedCalls = turn.toolGroup.completedVersion.toolCalls.map { call in
            PlaygroundToolCall(
                id: call.id + suffix,
                title: call.title,
                kind: call.kind,
                status: call.status,
                badges: call.badges,
                timestamp: call.timestamp.addingTimeInterval(offset),
                revision: call.revision
            )
        }

        let inProgressGroup = PlaygroundToolGroup(
            id: turn.toolGroup.inProgressVersion.id + suffix,
            title: turn.toolGroup.inProgressVersion.title,
            status: turn.toolGroup.inProgressVersion.status,
            toolCalls: inProgressCalls,
            timestamp: turn.toolGroup.inProgressVersion.timestamp.addingTimeInterval(offset),
            revision: turn.toolGroup.inProgressVersion.revision
        )
        let completedGroup = PlaygroundToolGroup(
            id: turn.toolGroup.completedVersion.id + suffix,
            title: turn.toolGroup.completedVersion.title,
            status: turn.toolGroup.completedVersion.status,
            toolCalls: completedCalls,
            timestamp: turn.toolGroup.completedVersion.timestamp.addingTimeInterval(offset),
            revision: turn.toolGroup.completedVersion.revision
        )

        let summary = PlaygroundTurnSummary(
            id: turn.summary.id + suffix,
            timestamp: turn.summary.timestamp.addingTimeInterval(offset),
            duration: turn.summary.duration,
            toolCallCount: turn.summary.toolCallCount,
            files: turn.summary.files,
            revision: turn.summary.revision
        )

        return PlaygroundScriptedTurn(
            userMessage: uniquedMessage(turn.userMessage)!,
            agentPreface: uniquedMessage(turn.agentPreface)!,
            toolGroup: PlaygroundToolGroupTransition(
                inProgressVersion: inProgressGroup,
                completedVersion: completedGroup
            ),
            agentFinal: uniquedMessage(turn.agentFinal)!,
            summary: summary,
            systemMessage: uniquedMessage(turn.systemMessage)
        )
    }

    private func markdownStreamingSegments(for text: String) -> [String] {
        guard !text.isEmpty else { return [] }

        let normalized = text.replacingOccurrences(of: "\r\n", with: "\n")
        let lines = normalized.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        var segments: [String] = []
        var current = ""
        var inCodeFence = false

        func flushCurrent() {
            guard !current.isEmpty else { return }
            segments.append(current)
            current = ""
        }

        for line in lines {
            let trimmed = line.trimmingCharacters(in: .whitespaces)
            current += line
            current += "\n"

            if trimmed.hasPrefix("```") {
                inCodeFence.toggle()
                if !inCodeFence {
                    flushCurrent()
                }
                continue
            }

            if inCodeFence {
                continue
            }

            let isBlockBoundary =
                trimmed.isEmpty ||
                trimmed.hasPrefix("#") ||
                trimmed.hasPrefix("- ") ||
                trimmed.hasPrefix("* ") ||
                trimmed.hasPrefix(">") ||
                trimmed.hasPrefix("|") ||
                trimmed.hasPrefix("1.") ||
                trimmed.hasPrefix("2.") ||
                trimmed.hasPrefix("3.") ||
                trimmed.hasPrefix("```")

            if isBlockBoundary || current.count > 220 {
                flushCurrent()
            }
        }

        flushCurrent()
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

private struct PlaygroundChatTimelineHost: NSViewRepresentable {
    let controller: VVChatTimelineController
    let onStateChange: (VVChatTimelineState) -> Void
    let onEntryActivate: (String) -> Void
    let onLinkActivate: (String) -> Void

    func makeNSView(context: Context) -> VVChatTimelineView {
        let view = VVChatTimelineView(frame: .zero)
        view.controller = controller
        view.onStateChange = onStateChange
        view.onEntryActivate = onEntryActivate
        view.onLinkActivate = onLinkActivate
        return view
    }

    func updateNSView(_ nsView: VVChatTimelineView, context: Context) {
        if nsView.controller !== controller {
            nsView.controller = controller
        }
        nsView.onStateChange = onStateChange
        nsView.onEntryActivate = onEntryActivate
        nsView.onLinkActivate = onLinkActivate
    }
}

private struct PlaygroundChatMessage: Identifiable, Hashable {
    let id: String
    let role: VVChatMessageRole
    var state: VVChatMessageState
    var content: String
    var revision: Int
    let timestamp: Date?
}

private struct PlaygroundToolBadge: Hashable {
    let text: String
    let color: SIMD4<Float>
}

private enum PlaygroundToolKind: String, Hashable {
    case read
    case edit
    case execute
    case search
    case think
    case fetch
    case plan
    case switchMode
    case delete
    case move
    case task
}

private enum PlaygroundToolStatus: String, Hashable {
    case completed = "completed"
    case inProgress = "in_progress"
    case failed = "failed"
}

private struct PlaygroundToolCall: Identifiable, Hashable {
    let id: String
    let title: String
    let kind: PlaygroundToolKind
    let status: PlaygroundToolStatus
    let badges: [PlaygroundToolBadge]
    let diff: String?
    let timestamp: Date
    let revision: Int

    init(
        id: String,
        title: String,
        kind: PlaygroundToolKind,
        status: PlaygroundToolStatus,
        badges: [PlaygroundToolBadge],
        diff: String? = nil,
        timestamp: Date,
        revision: Int
    ) {
        self.id = id
        self.title = title
        self.kind = kind
        self.status = status
        self.badges = badges
        self.diff = diff
        self.timestamp = timestamp
        self.revision = revision
    }
}

private struct PlaygroundToolGroup: Identifiable, Hashable {
    let id: String
    let title: String
    let status: PlaygroundToolStatus
    let toolCalls: [PlaygroundToolCall]
    let timestamp: Date
    let revision: Int
}

private struct PlaygroundFileChange: Identifiable, Hashable {
    let path: String
    let linesAdded: Int
    let linesRemoved: Int

    var id: String { path }

    var compactTitle: String {
        let parts = path.split(separator: "/")
        if parts.count <= 4 {
            return path
        }
        return "…/" + parts.suffix(4).joined(separator: "/")
    }
}

private struct PlaygroundTurnSummary: Identifiable, Hashable {
    let id: String
    let timestamp: Date
    let duration: TimeInterval
    let toolCallCount: Int
    let files: [PlaygroundFileChange]
    let revision: Int

    var formattedDuration: String {
        if duration < 1 {
            return "<1s"
        }
        if duration < 60 {
            return "\(Int(duration))s"
        }
        return "\(Int(duration) / 60)m \(Int(duration) % 60)s"
    }
}

private enum PlaygroundChatTimelineItem: Hashable {
    case message(PlaygroundChatMessage)
    case toolGroup(PlaygroundToolGroup)
    case turnSummary(PlaygroundTurnSummary)
}

private struct PlaygroundToolGroupTransition: Hashable {
    let inProgressVersion: PlaygroundToolGroup
    let completedVersion: PlaygroundToolGroup
}

private struct PlaygroundScriptedTurn: Hashable {
    let userMessage: PlaygroundChatMessage
    let agentPreface: PlaygroundChatMessage
    let toolGroup: PlaygroundToolGroupTransition
    let agentFinal: PlaygroundChatMessage
    let summary: PlaygroundTurnSummary
    let systemMessage: PlaygroundChatMessage?
}

private struct PayloadBadge: Codable {
    var text: String
    var r: Float
    var g: Float
    var b: Float
    var a: Float
}

private struct PayloadSummaryRow: Codable {
    var id: String
    var title: String
    var subtitle: String?
    var iconURL: String?
    var actionURL: String?
    var additionsText: String?
    var deletionsText: String?
}

private struct PayloadSummaryCard: Codable {
    var title: String
    var subtitle: String?
    var rows: [PayloadSummaryRow]
}

private struct PlaygroundTimelineCustomPayload: Codable {
    var title: String?
    var body: String
    var status: String?
    var toolKind: String?
    var showsAgentLaneIcon: Bool?
    var badges: [PayloadBadge]?
    var summaryCard: PayloadSummaryCard?
}

private func encodeCustomPayload(_ payload: PlaygroundTimelineCustomPayload, fallback: String) -> Data {
    if let encoded = try? JSONEncoder().encode(payload) {
        return encoded
    }
    return Data(fallback.utf8)
}

private func decodeCustomPayload(from data: Data) -> PlaygroundTimelineCustomPayload? {
    try? JSONDecoder().decode(PlaygroundTimelineCustomPayload.self, from: data)
}

private enum PlaygroundHeaderIconType {
    case sfSymbol(String)
    case customImage(Data)
}

private enum PlaygroundHeaderIconStore {
    private static var cache: [String: String] = [:]
    private static let lock = NSLock()
    private static let fileManager = FileManager.default
    private static let directoryURL: URL = {
        let url = URL(fileURLWithPath: NSTemporaryDirectory(), isDirectory: true)
            .appendingPathComponent("vvdevkit-playground-chat-icons", isDirectory: true)
        try? fileManager.createDirectory(at: url, withIntermediateDirectories: true)
        return url
    }()

    static func urlString(
        for iconType: PlaygroundHeaderIconType,
        fallbackAgentId: String,
        tintColor: NSColor?,
        targetPointSize: CGFloat
    ) -> String? {
        let cacheKey = "\(fallbackAgentId)-\(targetPointSize)-\(tintColor?.description ?? "default")"
        lock.lock()
        if let cached = cache[cacheKey] {
            lock.unlock()
            return cached
        }
        lock.unlock()

        guard let pngData = pngData(for: iconType, tintColor: tintColor, targetPointSize: targetPointSize) else {
            return nil
        }
        let fileURL = directoryURL.appendingPathComponent("\(abs(cacheKey.hashValue)).png")
        if !fileManager.fileExists(atPath: fileURL.path) {
            try? pngData.write(to: fileURL, options: .atomic)
        }
        lock.lock()
        cache[cacheKey] = fileURL.path
        lock.unlock()
        return fileURL.path
    }

    private static func pngData(
        for iconType: PlaygroundHeaderIconType,
        tintColor: NSColor?,
        targetPointSize: CGFloat
    ) -> Data? {
        let image: NSImage?
        switch iconType {
        case .sfSymbol(let symbol):
            image = NSImage(
                systemSymbolName: symbol,
                accessibilityDescription: nil
            )?.withSymbolConfiguration(.init(pointSize: max(12, targetPointSize), weight: .regular))
        case .customImage(let data):
            image = NSImage(data: data)
        }
        guard let image else { return nil }
        let scale = NSScreen.main?.backingScaleFactor ?? 2
        let pixels = Int(ceil(targetPointSize * scale))
        guard let rep = NSBitmapImageRep(
            bitmapDataPlanes: nil,
            pixelsWide: pixels,
            pixelsHigh: pixels,
            bitsPerSample: 8,
            samplesPerPixel: 4,
            hasAlpha: true,
            isPlanar: false,
            colorSpaceName: .deviceRGB,
            bytesPerRow: 0,
            bitsPerPixel: 0
        ) else { return nil }

        rep.size = NSSize(width: targetPointSize, height: targetPointSize)
        NSGraphicsContext.saveGraphicsState()
        guard let context = NSGraphicsContext(bitmapImageRep: rep) else {
            NSGraphicsContext.restoreGraphicsState()
            return nil
        }
        NSGraphicsContext.current = context
        let rect = NSRect(origin: .zero, size: NSSize(width: targetPointSize, height: targetPointSize))
        if let tintColor {
            let tinted = tintedImage(from: image, color: tintColor) ?? image
            tinted.draw(in: rect)
        } else {
            image.draw(in: rect)
        }
        NSGraphicsContext.restoreGraphicsState()
        return rep.representation(using: .png, properties: [:])
    }

    private static func tintedImage(from image: NSImage, color: NSColor) -> NSImage? {
        let tinted = NSImage(size: image.size)
        tinted.lockFocus()
        let rect = NSRect(origin: .zero, size: image.size)
        image.draw(in: rect)
        color.set()
        rect.fill(using: .sourceAtop)
        tinted.unlockFocus()
        return tinted
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

    static let chatEditDiffSample = [
        "diff --git a/Examples/VVDevKitPlayground/VVDevKitPlaygroundApp.swift b/Examples/VVDevKitPlayground/VVDevKitPlaygroundApp.swift",
        "index 4b7b9b1..d25f8c2 100644",
        "--- a/Examples/VVDevKitPlayground/VVDevKitPlaygroundApp.swift",
        "+++ b/Examples/VVDevKitPlayground/VVDevKitPlaygroundApp.swift",
        "@@ -1450,6 +1450,16 @@ struct ChatPlaygroundView: View {",
        "     private func handleLinkActivate(_ url: String) {",
        "         guard let parsed = URL(string: url), parsed.scheme == \"playground-file\" else { return }",
        "     }",
        "",
        "+        private func diffPreview(for entryID: String) -> PlaygroundDiffPreview? {",
        "+            guard entryID.contains(\"::\") else { return nil }",
        "+            return PlaygroundDiffPreview(",
        "+                id: entryID,",
        "+                title: \"VVDevKitPlaygroundApp.swift\",",
        "+                diff: SampleData.chatEditDiffSample",
        "+            )",
        "+        }",
        " }"
    ].joined(separator: "\n")

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

    fileprivate static func aizenSeedTimelineItems(includeInterrupts: Bool) -> [PlaygroundChatTimelineItem] {
        let base = Date().addingTimeInterval(-1800)

        let firstUser = PlaygroundChatMessage(
            id: "seed-user-1",
            role: .user,
            state: .final,
            content: "Make the chat timeline in the playground match what I see in Aizen.",
            revision: 1,
            timestamp: base
        )
        let firstAssistant = PlaygroundChatMessage(
            id: "seed-assistant-1",
            role: .assistant,
            state: .final,
            content: """
            I inspected the Aizen timeline and rebuilt this transcript with the same VVDevKit presentation model:

            - user messages stay in timestamped bubbles
            - assistant output renders as an open lane
            - tool work collapses into grouped rows with per-call detail
            - completed turns end with a summary card
            """,
            revision: 1,
            timestamp: base.addingTimeInterval(3)
        )
        let firstGroup = PlaygroundToolGroup(
            id: "seed-group-1",
            title: "Read 3, Searched 1, Planned 1 • 6s",
            status: .completed,
            toolCalls: [
                PlaygroundToolCall(
                    id: "seed-read-1",
                    title: "Read",
                    kind: .read,
                    status: .completed,
                    badges: [
                        PlaygroundToolBadge(text: "…/aizen/Views/Chat/Components/ChatMessageList.swift", color: .rgba(0.72, 0.74, 0.79, 0.72)),
                        PlaygroundToolBadge(text: "219 lines", color: .rgba(0.72, 0.74, 0.79, 0.72))
                    ],
                    timestamp: base.addingTimeInterval(4),
                    revision: 1
                ),
                PlaygroundToolCall(
                    id: "seed-search-1",
                    title: "Searched",
                    kind: .search,
                    status: .completed,
                    badges: [
                        PlaygroundToolBadge(text: "VVChatTimeline", color: .rgba(0.72, 0.74, 0.79, 0.72)),
                        PlaygroundToolBadge(text: "12 matches", color: .rgba(0.72, 0.74, 0.79, 0.72))
                    ],
                    timestamp: base.addingTimeInterval(5),
                    revision: 1
                ),
                PlaygroundToolCall(
                    id: "seed-plan-1",
                    title: "Planned",
                    kind: .plan,
                    status: .completed,
                    badges: [
                        PlaygroundToolBadge(text: "3 steps", color: .rgba(0.72, 0.74, 0.79, 0.72))
                    ],
                    timestamp: base.addingTimeInterval(6),
                    revision: 1
                )
            ],
            timestamp: base.addingTimeInterval(4),
            revision: 1
        )
        let firstAssistantFinal = PlaygroundChatMessage(
            id: "seed-assistant-2",
            role: .assistant,
            state: .final,
            content: """
            The playground now uses the same entry categories Aizen does, so you can evaluate real user/agent turn boundaries instead of plain markdown messages.
            """,
            revision: 1,
            timestamp: base.addingTimeInterval(8)
        )
        let firstSummary = PlaygroundTurnSummary(
            id: "seed-summary-1",
            timestamp: base.addingTimeInterval(9),
            duration: 6,
            toolCallCount: 5,
            files: [
                PlaygroundFileChange(path: "Examples/VVDevKitPlayground/VVDevKitPlaygroundApp.swift", linesAdded: 198, linesRemoved: 42),
                PlaygroundFileChange(path: "Sources/VVChatTimeline/VVChatTimelineModels.swift", linesAdded: 0, linesRemoved: 0)
            ],
            revision: 1
        )

        let secondUser = PlaygroundChatMessage(
            id: "seed-user-2",
            role: .user,
            state: .final,
            content: "Show me a failing turn too, not just a happy path.",
            revision: 1,
            timestamp: base.addingTimeInterval(14)
        )
        let secondAssistant = PlaygroundChatMessage(
            id: "seed-assistant-3",
            role: .assistant,
            state: .final,
            content: "I can simulate a failed edit pass and keep the turn summary visible below it.",
            revision: 1,
            timestamp: base.addingTimeInterval(17)
        )
        let secondGroup = PlaygroundToolGroup(
            id: "seed-group-2",
            title: "Edited 1, Ran 1 • 4s",
            status: .failed,
            toolCalls: [
                PlaygroundToolCall(
                    id: "seed-edit-1",
                    title: "Edited",
                    kind: .edit,
                    status: .completed,
                    badges: [
                        PlaygroundToolBadge(text: "…/Examples/VVDevKitPlayground/VVDevKitPlaygroundApp.swift", color: .rgba(0.72, 0.74, 0.79, 0.72)),
                        PlaygroundToolBadge(text: "+34", color: .rgba(0.42, 0.82, 0.52, 1)),
                        PlaygroundToolBadge(text: "-8", color: .rgba(0.92, 0.42, 0.44, 1))
                    ],
                    diff: chatEditDiffSample,
                    timestamp: base.addingTimeInterval(18),
                    revision: 1
                ),
                PlaygroundToolCall(
                    id: "seed-run-1",
                    title: "Ran",
                    kind: .execute,
                    status: .failed,
                    badges: [
                        PlaygroundToolBadge(text: "swift build --product VVDevKitPlayground", color: .rgba(0.72, 0.74, 0.79, 0.72)),
                        PlaygroundToolBadge(text: "failed", color: .rgba(0.92, 0.42, 0.44, 1))
                    ],
                    timestamp: base.addingTimeInterval(20),
                    revision: 1
                )
            ],
            timestamp: base.addingTimeInterval(18),
            revision: 1
        )
        let secondAssistantFinal = PlaygroundChatMessage(
            id: "seed-assistant-4",
            role: .assistant,
            state: .final,
            content: "That failed build state is preserved exactly the way Aizen renders it: failed tool row, then the assistant follow-up, then a summary card.",
            revision: 1,
            timestamp: base.addingTimeInterval(22)
        )
        let secondSummary = PlaygroundTurnSummary(
            id: "seed-summary-2",
            timestamp: base.addingTimeInterval(23),
            duration: 4,
            toolCallCount: 2,
            files: [
                PlaygroundFileChange(path: "Examples/VVDevKitPlayground/VVDevKitPlaygroundApp.swift", linesAdded: 34, linesRemoved: 8)
            ],
            revision: 1
        )

        var items: [PlaygroundChatTimelineItem] = [
            .message(PlaygroundChatMessage(
                id: "seed-system-0",
                role: .system,
                state: .final,
                content: "Restored Aizen-style session transcript.",
                revision: 1,
                timestamp: base.addingTimeInterval(-3)
            )),
            .message(firstUser),
            .message(firstAssistant),
            .toolGroup(firstGroup),
            .message(firstAssistantFinal),
            .turnSummary(firstSummary)
        ]

        if includeInterrupts {
            items.append(.message(PlaygroundChatMessage(
                id: "seed-system-1",
                role: .system,
                state: .final,
                content: "**Plan approval requested**\n\nWrite access outside the active worktree requires confirmation.",
                revision: 1,
                timestamp: base.addingTimeInterval(12)
            )))
        }

        items.append(contentsOf: [
            .message(secondUser),
            .message(secondAssistant),
            .toolGroup(secondGroup),
            .message(secondAssistantFinal),
            .turnSummary(secondSummary)
        ])

        return items
    }

    fileprivate static func aizenScriptedTurns(includeInterrupts: Bool) -> [PlaygroundScriptedTurn] {
        let base = Date()
        let neutral: SIMD4<Float> = .rgba(0.72, 0.74, 0.79, 0.72)
        let green: SIMD4<Float> = .rgba(0.42, 0.82, 0.52, 1)
        let red: SIMD4<Float> = .rgba(0.92, 0.42, 0.44, 1)

        let turn1 = PlaygroundScriptedTurn(
            userMessage: PlaygroundChatMessage(
                id: "turn-user-1",
                role: .user,
                state: .final,
                content: "Simulate the exact Aizen turn loop for a read-heavy investigation.",
                revision: 1,
                timestamp: base
            ),
            agentPreface: PlaygroundChatMessage(
                id: "turn-preface-1",
                role: .assistant,
                state: .draft,
                content: "I’m going to inspect the Aizen chat layer, group the exploration work, then summarize what changed in VVDevKit.",
                revision: 0,
                timestamp: base.addingTimeInterval(2)
            ),
            toolGroup: PlaygroundToolGroupTransition(
                inProgressVersion: PlaygroundToolGroup(
                    id: "turn-group-1",
                    title: "Read 2, Searched 2 • 3s",
                    status: .inProgress,
                    toolCalls: [
                        PlaygroundToolCall(id: "turn1-read1", title: "Read", kind: .read, status: .completed, badges: [PlaygroundToolBadge(text: "…/ChatMessageList.swift", color: neutral)], timestamp: base.addingTimeInterval(3), revision: 1),
                        PlaygroundToolCall(id: "turn1-read2", title: "Read", kind: .read, status: .completed, badges: [PlaygroundToolBadge(text: "…/ChatSessionViewModel+Timeline.swift", color: neutral)], timestamp: base.addingTimeInterval(4), revision: 1),
                        PlaygroundToolCall(id: "turn1-search1", title: "Searched", kind: .search, status: .completed, badges: [PlaygroundToolBadge(text: "toolCallGroup", color: neutral)], timestamp: base.addingTimeInterval(5), revision: 1),
                        PlaygroundToolCall(id: "turn1-plan1", title: "Planned…", kind: .plan, status: .inProgress, badges: [PlaygroundToolBadge(text: "1 step running", color: neutral)], timestamp: base.addingTimeInterval(6), revision: 1)
                    ],
                    timestamp: base.addingTimeInterval(3),
                    revision: 1
                ),
                completedVersion: PlaygroundToolGroup(
                    id: "turn-group-1",
                    title: "Read 2, Searched 2, Planned 1 • 5s",
                    status: .completed,
                    toolCalls: [
                        PlaygroundToolCall(id: "turn1-read1", title: "Read", kind: .read, status: .completed, badges: [PlaygroundToolBadge(text: "…/ChatMessageList.swift", color: neutral), PlaygroundToolBadge(text: "182 lines", color: neutral)], timestamp: base.addingTimeInterval(3), revision: 2),
                        PlaygroundToolCall(id: "turn1-read2", title: "Read", kind: .read, status: .completed, badges: [PlaygroundToolBadge(text: "…/ChatSessionViewModel+Timeline.swift", color: neutral), PlaygroundToolBadge(text: "247 lines", color: neutral)], timestamp: base.addingTimeInterval(4), revision: 2),
                        PlaygroundToolCall(id: "turn1-search1", title: "Searched", kind: .search, status: .completed, badges: [PlaygroundToolBadge(text: "toolCallGroup", color: neutral), PlaygroundToolBadge(text: "7 matches", color: neutral)], timestamp: base.addingTimeInterval(5), revision: 2),
                        PlaygroundToolCall(id: "turn1-plan1", title: "Planned", kind: .plan, status: .completed, badges: [PlaygroundToolBadge(text: "3 steps", color: neutral)], timestamp: base.addingTimeInterval(6), revision: 2)
                    ],
                    timestamp: base.addingTimeInterval(3),
                    revision: 2
                )
            ),
            agentFinal: PlaygroundChatMessage(
                id: "turn-final-1",
                role: .assistant,
                state: .draft,
                content: """
                ## Investigation Result

                The investigation turn now matches Aizen’s structure:

                - the assistant speaks in an open lane
                - exploration work sits in grouped tool rows
                - completion closes with a turn summary card

                ### Rendering Notes

                | Area | Behavior |
                | --- | --- |
                | Messages | Markdown reflows as blocks complete |
                | Tools | Group rows stay compact until expanded |
                | Summary | File rows hover independently |

                ```swift
                controller.prepareLayoutTransition(anchorItemID: draftID)
                controller.setEntries(entries, scrollToBottom: true)
                ```

                > The key improvement is that the markdown stays readable while it streams instead of waiting for the full response.
                """,
                revision: 0,
                timestamp: base.addingTimeInterval(8)
            ),
            summary: PlaygroundTurnSummary(
                id: "turn-summary-1",
                timestamp: base.addingTimeInterval(9),
                duration: 5,
                toolCallCount: 5,
                files: [PlaygroundFileChange(path: "Examples/VVDevKitPlayground/VVDevKitPlaygroundApp.swift", linesAdded: 52, linesRemoved: 14)],
                revision: 1
            ),
            systemMessage: includeInterrupts ? PlaygroundChatMessage(
                id: "turn-system-1",
                role: .system,
                state: .final,
                content: "**Plan approval requested**\n\nAllow write access outside the worktree?",
                revision: 1,
                timestamp: base.addingTimeInterval(10)
            ) : nil
        )

        let turn2 = PlaygroundScriptedTurn(
            userMessage: PlaygroundChatMessage(
                id: "turn-user-2",
                role: .user,
                state: .final,
                content: "Simulate an edit pass with a failing build so I can see the error state.",
                revision: 1,
                timestamp: base.addingTimeInterval(40)
            ),
            agentPreface: PlaygroundChatMessage(
                id: "turn-preface-2",
                role: .assistant,
                state: .draft,
                content: "I’ll stage the edit, run a build, and preserve the failed tool row the same way Aizen does.",
                revision: 0,
                timestamp: base.addingTimeInterval(42)
            ),
            toolGroup: PlaygroundToolGroupTransition(
                inProgressVersion: PlaygroundToolGroup(
                    id: "turn-group-2",
                    title: "Edited 1, Ran 1 • 2s",
                    status: .inProgress,
                    toolCalls: [
                        PlaygroundToolCall(id: "turn2-edit1", title: "Edited", kind: .edit, status: .completed, badges: [PlaygroundToolBadge(text: "…/VVDevKitPlaygroundApp.swift", color: neutral), PlaygroundToolBadge(text: "+18", color: green), PlaygroundToolBadge(text: "-3", color: red)], diff: chatEditDiffSample, timestamp: base.addingTimeInterval(43), revision: 1),
                        PlaygroundToolCall(id: "turn2-run1", title: "Ran…", kind: .execute, status: .inProgress, badges: [PlaygroundToolBadge(text: "swift build --product VVDevKitPlayground", color: neutral)], timestamp: base.addingTimeInterval(44), revision: 1)
                    ],
                    timestamp: base.addingTimeInterval(43),
                    revision: 1
                ),
                completedVersion: PlaygroundToolGroup(
                    id: "turn-group-2",
                    title: "Edited 1, Ran 1 • 4s",
                    status: .failed,
                    toolCalls: [
                        PlaygroundToolCall(id: "turn2-edit1", title: "Edited", kind: .edit, status: .completed, badges: [PlaygroundToolBadge(text: "…/VVDevKitPlaygroundApp.swift", color: neutral), PlaygroundToolBadge(text: "+18", color: green), PlaygroundToolBadge(text: "-3", color: red)], diff: chatEditDiffSample, timestamp: base.addingTimeInterval(43), revision: 2),
                        PlaygroundToolCall(id: "turn2-run1", title: "Ran", kind: .execute, status: .failed, badges: [PlaygroundToolBadge(text: "swift build --product VVDevKitPlayground", color: neutral), PlaygroundToolBadge(text: "failed", color: red)], timestamp: base.addingTimeInterval(46), revision: 2)
                    ],
                    timestamp: base.addingTimeInterval(43),
                    revision: 2
                )
            ),
            agentFinal: PlaygroundChatMessage(
                id: "turn-final-2",
                role: .assistant,
                state: .draft,
                content: """
                ## Failed Build Turn

                The failure is represented inline inside the tool group, then the assistant explanation and turn summary follow beneath it.

                ### What You See

                1. The edit row lands first.
                2. The build row flips into a failed state.
                3. The assistant writes a markdown explanation below the failed tool cluster.

                ```text
                swift build --product VVDevKitPlayground
                error: build failed in Example target
                ```

                That gives the transcript a clear turn boundary even when the execution path is unsuccessful.
                """,
                revision: 0,
                timestamp: base.addingTimeInterval(48)
            ),
            summary: PlaygroundTurnSummary(
                id: "turn-summary-2",
                timestamp: base.addingTimeInterval(49),
                duration: 4,
                toolCallCount: 2,
                files: [PlaygroundFileChange(path: "Examples/VVDevKitPlayground/VVDevKitPlaygroundApp.swift", linesAdded: 18, linesRemoved: 3)],
                revision: 1
            ),
            systemMessage: nil
        )

        return [turn1, turn2]
    }

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
        var theme = dark ? MarkdownTheme.dark : MarkdownTheme.light
        theme.paragraphSpacing = 10
        theme.headingSpacing = 22
        theme.contentPadding = 0
        var draftTheme = theme
        draftTheme.textColor = theme.textColor.withOpacity(theme.textColor.w * 0.72)
        let baseFont = NSFont.systemFont(ofSize: fontSize)
        let headerColor: SIMD4<Float> = dark ? .rgba(0.98, 0.98, 1.0, 1.0) : .rgba(0.14, 0.16, 0.20, 1.0)
        let timestampColor: SIMD4<Float> = dark ? .rgba(0.66, 0.69, 0.75, 1.0) : .rgba(0.45, 0.48, 0.54, 1.0)
        return VVChatTimelineStyle(
            theme: theme,
            draftTheme: draftTheme,
            baseFont: baseFont,
            draftFont: baseFont,
            headerFont: NSFont.systemFont(ofSize: max(fontSize - 1.5, 11.5)),
            timestampFont: NSFont.systemFont(ofSize: max(fontSize - 0.25, 12.5), weight: .medium),
            headerTextColor: headerColor,
            timestampTextColor: timestampColor,
            userBubbleColor: dark ? .rgba(0.20, 0.22, 0.25, 0.78) : .rgba(0.91, 0.93, 0.96, 0.92),
            userBubbleBorderColor: dark ? .rgba(0.52, 0.56, 0.62, 0.32) : .rgba(0.56, 0.60, 0.68, 0.18),
            userBubbleBorderWidth: 0.6,
            userBubbleCornerRadius: 16,
            userBubbleInsets: .init(top: 8, left: 14, bottom: 8, right: 14),
            userBubbleMaxWidth: 560,
            assistantBubbleEnabled: false,
            assistantBubbleMaxWidth: 4000,
            assistantBubbleAlignment: .leading,
            systemBubbleEnabled: true,
            systemBubbleColor: .clear,
            systemBubbleBorderColor: .clear,
            systemBubbleBorderWidth: 0,
            systemBubbleInsets: .init(top: 0, left: 0, bottom: 0, right: 0),
            systemBubbleMaxWidth: 4000,
            systemBubbleAlignment: .center,
            userHeaderEnabled: false,
            assistantHeaderEnabled: false,
            systemHeaderEnabled: false,
            assistantHeaderTitle: "",
            systemHeaderTitle: "",
            userTimestampEnabled: true,
            assistantTimestampEnabled: false,
            systemTimestampEnabled: false,
            bubbleMetadataMinWidth: 1,
            headerSpacing: 1,
            footerSpacing: 0,
            timelineInsets: .init(top: 10, left: 20, bottom: 10, right: 20),
            messageSpacing: 6,
            userInsets: .init(top: 7, left: 20, bottom: 7, right: 20),
            assistantInsets: .init(top: 3, left: 20, bottom: 4, right: 20),
            systemInsets: .init(top: 15, left: 20, bottom: 15, right: 20),
            backgroundColor: .clear,
            renderedCacheLimit: 12,
            motion: .init(
                layoutTransition: .accordion,
                layoutAnimation: .spring(response: 0.34, dampingFraction: 0.84),
                viewportFollowAnimation: .smooth(duration: 0.18),
                viewportClampAnimation: .smooth(duration: 0.18),
                jumpToLatestAnimation: .timing(duration: 0.28, easing: .easeOut),
                updateBatchInterval: 1.0 / 90.0
            )
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
        case .transitions: return transitionAnimationScene(size: size, configuration: configuration, state: transitionAnimationSnapshots(size: size, configuration: configuration, expanded: false), expanded: false)
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
        guard !text.isEmpty else { return [] }

        let ascent = CTFontGetAscent(ctFont)
        let lineHeight = ascent + CTFontGetDescent(ctFont) + CTFontGetLeading(ctFont)
        let baselineY = origin.y + ascent

        let attributes: [NSAttributedString.Key: Any] = [
            .font: font,
            .ligature: 1
        ]
        let line = CTLineCreateWithAttributedString(NSAttributedString(string: text, attributes: attributes))
        let runs = CTLineGetGlyphRuns(line) as? [CTRun] ?? []

        var result: [VVTextGlyph] = []
        for run in runs {
            let glyphCount = CTRunGetGlyphCount(run)
            guard glyphCount > 0 else { continue }

            let runAttributes = CTRunGetAttributes(run) as NSDictionary
            let runFont = runAttributes[kCTFontAttributeName] as! CTFont
            let fontName = CTFontCopyPostScriptName(runFont) as String
            let storedFontName = isSystemUIFontName(fontName) ? nil : fontName
            let runFontSize = CTFontGetSize(runFont)

            var glyphIDs = [CGGlyph](repeating: 0, count: glyphCount)
            CTRunGetGlyphs(run, CFRangeMake(0, glyphCount), &glyphIDs)

            var positions = [CGPoint](repeating: .zero, count: glyphCount)
            CTRunGetPositions(run, CFRangeMake(0, glyphCount), &positions)

            var advances = [CGSize](repeating: .zero, count: glyphCount)
            CTRunGetAdvances(run, CFRangeMake(0, glyphCount), &advances)

            var stringIndices = [CFIndex](repeating: 0, count: glyphCount)
            CTRunGetStringIndices(run, CFRangeMake(0, glyphCount), &stringIndices)

            for i in 0..<glyphCount {
                let glyphID = glyphIDs[i]
                guard glyphID != 0 else { continue }

                result.append(VVTextGlyph(
                    glyphID: UInt16(glyphID),
                    position: CGPoint(x: origin.x + positions[i].x, y: baselineY),
                    size: CGSize(width: max(advances[i].width, 1), height: lineHeight),
                    color: color,
                    fontVariant: variant,
                    fontSize: runFontSize,
                    fontName: storedFontName,
                    stringIndex: Int(stringIndices[i])
                ))
            }
        }

        return result
    }

    private static func isSystemUIFontName(_ name: String) -> Bool {
        if name == ".AppleColorEmojiUI" || name == "AppleColorEmoji" || name == "AppleColorEmojiUI" {
            return false
        }
        return name.hasPrefix(".SF") || name.hasPrefix(".AppleSystem") || name.hasPrefix(".")
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
        let fg = foregroundColor(for: config.backgroundColor)
        let pad: CGFloat = 40
        let gap: CGFloat = 28
        let tileW: CGFloat = 200
        let tileH: CGFloat = 100

        builder.add(kind: .textRun(makeTextRun(
            text: "Gradient Quad",
            font: NSFont.systemFont(ofSize: 26, weight: .bold),
            origin: CGPoint(x: pad, y: 18),
            color: fg,
            variant: .bold
        )), zIndex: 2)
        builder.add(kind: .textRun(makeTextRun(
            text: "Single-pass gradients with proper rounded corners and directional control.",
            font: NSFont.systemFont(ofSize: 13, weight: .regular),
            origin: CGPoint(x: pad, y: 50),
            color: SIMD4<Float>(fg.x, fg.y, fg.z, 0.62)
        )), zIndex: 2)

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

        builder.add(kind: .gradientQuad(VVGradientQuadPrimitive(
            frame: CGRect(x: pad, y: row3Y + 118, width: bigW, height: 120),
            startColor: SIMD4(0.15, 0.65, 0.95, 1),
            endColor: SIMD4(0.9, 0.28, 0.54, 1),
            angle: -.pi / 4.5,
            cornerRadii: VVCornerRadii(config.cornerRadius),
            steps: 32
        )), zIndex: 1)
        builder.add(kind: .textRun(makeTextRun(
            text: "Angled gradient",
            font: NSFont.systemFont(ofSize: 12, weight: .semibold),
            origin: CGPoint(x: pad + 18, y: row3Y + 132),
            color: SIMD4<Float>(1, 1, 1, 0.88)
        )), zIndex: 2)
        builder.add(kind: .textRun(makeTextRun(
            text: "The shader now clips the full fill once, instead of stacking many rounded strips.",
            font: NSFont.systemFont(ofSize: 13, weight: .regular),
            origin: CGPoint(x: pad + 18, y: row3Y + 156),
            color: SIMD4<Float>(1, 1, 1, 0.7)
        )), zIndex: 2)

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
        let borderColor = SIMD4(fg.x, fg.y, fg.z, 0.3)

        let imageSizes: [(CGFloat, CGFloat, CGFloat)] = [
            (180, 120, 4),
            (120, 120, config.cornerRadius),
            (200, 100, 0),
            (100, 140, config.cornerRadius * 2),
        ]

        var x = pad
        for (w, h, cr) in imageSizes {
            let frame = CGRect(x: x, y: pad, width: w, height: h)

            builder.add(kind: .quad(VVQuadPrimitive(
                frame: frame,
                color: SIMD4(fg.x, fg.y, fg.z, 0.08),
                cornerRadius: cr
            )), zIndex: 0)

            builder.add(kind: .quad(VVQuadPrimitive(
                frame: frame,
                color: SIMD4<Float>(0, 0, 0, 0),
                cornerRadii: VVCornerRadii(cr),
                border: VVBorder(width: 1, color: borderColor)
            )), zIndex: 1)

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
            builder.add(kind: .quad(VVQuadPrimitive(
                frame: frame,
                color: SIMD4<Float>(0, 0, 0, 0),
                cornerRadii: VVCornerRadii(cr),
                border: VVBorder(width: 1, color: borderColor)
            )), zIndex: 1)
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
        let inset: CGFloat = 44
        let cardSize = CGSize(width: 240, height: 170)
        let spacing = CGSize(width: 36, height: 36)
        let guideFill = SIMD4(fg.x, fg.y, fg.z, 0.04)
        let guideBorder = SIMD4(fg.x, fg.y, fg.z, 0.12)
        let ghostStroke = SIMD4(fg.x, fg.y, fg.z, 0.38)
        let originColor = SIMD4<Float>(1, 1, 1, 0.9)
        let env = VVLayoutEnvironment(scale: 1, defaultTextColor: fg, defaultCornerRadius: config.cornerRadius)

        func card(at origin: CGPoint) -> CGRect {
            CGRect(origin: origin, size: cardSize)
        }

        func rectPoints(size: CGSize) -> [CGPoint] {
            [
                CGPoint(x: -size.width * 0.5, y: -size.height * 0.5),
                CGPoint(x: size.width * 0.5, y: -size.height * 0.5),
                CGPoint(x: size.width * 0.5, y: size.height * 0.5),
                CGPoint(x: -size.width * 0.5, y: size.height * 0.5),
            ]
        }

        func starPoints(outerRadius: CGFloat, innerRadius: CGFloat) -> [CGPoint] {
            var points: [CGPoint] = []
            points.reserveCapacity(10)
            for index in 0..<10 {
                let angle = CGFloat(index) * .pi / 5 - .pi / 2
                let radius = index.isMultiple(of: 2) ? outerRadius : innerRadius
                points.append(CGPoint(x: cos(angle) * radius, y: sin(angle) * radius))
            }
            return points
        }

        func polygonPath(points: [CGPoint], fill: SIMD4<Float>, stroke: VVStrokeStyle? = nil) -> VVPathPrimitive {
            var path = VVPathBuilder()
            path.addPolygon(points)
            return path.build(fill: fill, stroke: stroke)
        }

        func transformed(_ points: [CGPoint], by transform: VVTransform2D) -> [CGPoint] {
            points.map { transform.apply(to: $0) }
        }

        func addGuideCard(_ frame: CGRect, title: String, detail: String) {
            builder.add(kind: .quad(VVQuadPrimitive(
                frame: frame,
                color: guideFill,
                cornerRadii: VVCornerRadii(18),
                border: VVBorder(width: 1, color: guideBorder)
            )), zIndex: 0)

            let labelNode = VVStack(spacing: 4, alignment: .leading) {
                VText(title, font: .headline, color: fg.withOpacity(0.94))
                VText(detail, font: .caption, color: fg.withOpacity(0.62), maxLines: 2)
            }
            .renderNode(width: frame.width - 28, env: env)
            builder.add(node: VVNode(
                offset: CGPoint(x: frame.minX + 14, y: frame.minY + 14),
                zIndex: 2,
                children: [labelNode]
            ))

            let center = CGPoint(x: frame.midX, y: frame.midY)
            builder.add(kind: .quad(VVQuadPrimitive(
                frame: CGRect(x: center.x - 2, y: center.y - 2, width: 4, height: 4),
                color: originColor,
                cornerRadii: VVCornerRadii(2)
            )), zIndex: 3)
        }

        let topLeft = card(at: CGPoint(x: inset, y: inset))
        let topRight = card(at: CGPoint(x: topLeft.maxX + spacing.width, y: inset))
        let bottomLeft = card(at: CGPoint(x: inset, y: topLeft.maxY + spacing.height))
        let bottomRight = card(at: CGPoint(x: topRight.minX, y: bottomLeft.minY))

        addGuideCard(topLeft, title: "Translate", detail: "A direct x/y move with a ghost start frame.")
        addGuideCard(topRight, title: "Scale", detail: "Scaling around the local center, then positioning the result.")
        addGuideCard(bottomLeft, title: "Rotate", detail: "Rotation kept local so the star stays centered in its card.")
        addGuideCard(bottomRight, title: "Compose", detail: "Scale plus rotation applied before final placement.")

        let translatedStart = CGPoint(x: topLeft.midX - 54, y: topLeft.midY + 18)
        let translatedEnd = CGPoint(x: topLeft.midX + 44, y: topLeft.midY + 18)
        builder.add(kind: .path(polygonPath(
            points: transformed(rectPoints(size: CGSize(width: 76, height: 50)), by: .identity.translated(by: translatedStart)),
            fill: SIMD4<Float>(0, 0, 0, 0),
            stroke: VVStrokeStyle(color: ghostStroke, width: 1.5)
        )), zIndex: 1)
        builder.add(kind: .path(polygonPath(
            points: transformed(rectPoints(size: CGSize(width: 76, height: 50)), by: .identity.translated(by: translatedEnd)),
            fill: SIMD4(0.3, 0.8, 0.5, 0.82),
            stroke: VVStrokeStyle(color: SIMD4(0.3, 0.8, 0.5, 1), width: 2)
        )), zIndex: 2)

        let scaleCenter = CGPoint(x: topRight.midX, y: topRight.midY + 18)
        builder.add(kind: .path(polygonPath(
            points: transformed(rectPoints(size: CGSize(width: 62, height: 42)), by: .identity.translated(by: scaleCenter)),
            fill: SIMD4<Float>(0, 0, 0, 0),
            stroke: VVStrokeStyle(color: ghostStroke, width: 1.5)
        )), zIndex: 1)
        builder.add(kind: .path(polygonPath(
            points: transformed(
                rectPoints(size: CGSize(width: 62, height: 42)),
                by: .identity
                    .scaled(x: 1.55, y: 1.95)
                    .translated(by: scaleCenter)
            ),
            fill: SIMD4(0.5, 0.6, 0.95, 0.82),
            stroke: VVStrokeStyle(color: SIMD4(0.5, 0.6, 0.95, 1), width: 2)
        )), zIndex: 2)

        let rotationCenter = CGPoint(x: bottomLeft.midX, y: bottomLeft.midY + 18)
        builder.add(kind: .path(polygonPath(
            points: transformed(starPoints(outerRadius: 42, innerRadius: 18), by: .identity.translated(by: rotationCenter)),
            fill: SIMD4<Float>(0, 0, 0, 0),
            stroke: VVStrokeStyle(color: ghostStroke, width: 1.5)
        )), zIndex: 1)
        builder.add(kind: .path(polygonPath(
            points: transformed(
                starPoints(outerRadius: 42, innerRadius: 18),
                by: .identity
                    .rotated(by: .pi / 6)
                    .translated(by: rotationCenter)
            ),
            fill: SIMD4(0.95, 0.7, 0.2, 0.92),
            stroke: VVStrokeStyle(color: SIMD4(0.95, 0.7, 0.2, 1), width: 2)
        )), zIndex: 2)

        let composedCenter = CGPoint(x: bottomRight.midX, y: bottomRight.midY + 18)
        builder.add(kind: .path(polygonPath(
            points: transformed(rectPoints(size: CGSize(width: 70, height: 44)), by: .identity.translated(by: composedCenter)),
            fill: SIMD4<Float>(0, 0, 0, 0),
            stroke: VVStrokeStyle(color: ghostStroke, width: 1.5)
        )), zIndex: 1)
        builder.add(kind: .path(polygonPath(
            points: transformed(
                rectPoints(size: CGSize(width: 70, height: 44)),
                by: .identity
                    .scaled(x: 1.45, y: 1.25)
                    .rotated(by: .pi / 8)
                    .translated(by: composedCenter)
            ),
            fill: SIMD4(0.9, 0.4, 0.6, 0.84),
            stroke: VVStrokeStyle(color: SIMD4(0.9, 0.4, 0.6, 1), width: 2)
        )), zIndex: 2)

        return builder.scene
    }

    static func transitionAnimationSnapshots(
        size: CGSize,
        configuration: PrimitiveSceneConfiguration,
        expanded: Bool
    ) -> [String: VVLayoutAnimationSnapshot] {
        let fg = foregroundColor(for: configuration.backgroundColor)
        let env = VVLayoutEnvironment(scale: 1, defaultTextColor: fg, defaultCornerRadius: configuration.cornerRadius)
        let canvas = CGRect(x: 44, y: 36, width: max(1080, size.width - 88), height: max(740, size.height - 72))
        let stage = CGRect(x: canvas.minX + 28, y: canvas.minY + 74, width: min(canvas.width - 300, 760), height: canvas.height - 118)
        let contentWidth = stage.width - 56
        let mediaSize = expanded ? CGSize(width: 180, height: 156) : CGSize(width: 132, height: 112)
        let copyWidth = max(260, contentWidth - mediaSize.width - 20)

        let view = VVStack(spacing: 18, alignment: .leading) {
            VVStack(spacing: 6, alignment: .leading) {
                VText("Payment Summary", font: .headline, color: .white)
                VText(
                    expanded ? "3 items, delivery, payment method, and contact details." : "Compact order card with expandable detail rows.",
                    font: .caption,
                    color: SIMD4<Float>(1, 1, 1, 0.78),
                    maxLines: expanded ? 2 : 1
                )
            }
            .padding(18)
            .frame(width: contentWidth)
            .background(color: .indigo.withOpacity(0.16), cornerRadius: configuration.cornerRadius)
                .id("hero")
                .transition(.morph)
                .animation(.spring(response: 0.34, dampingFraction: 0.78))

            VVHStack(spacing: 14) {
                VVImage(
                    url: expanded ? "placeholder://hero-expanded" : "placeholder://hero-collapsed",
                    size: mediaSize,
                    cornerRadius: 16
                )
                    .id("media")
                    .transition(.morph)

                VVStack(spacing: 10, alignment: .leading) {
                    VText("Design Review", font: .headline)
                    VText(
                        "Reusable motion for cards, details, and contextual expansion. Containers should size from content, not from manual scene math.",
                        font: .body,
                        color: fg.withOpacity(0.72),
                        maxLines: expanded ? 3 : 2
                    )
                    VText("Shared Animation Layer", font: .caption, color: .amber)
                    if expanded {
                        VText(
                            "Auto-layout shifts siblings while preserving identity.",
                            font: .caption,
                            color: fg.withOpacity(0.82),
                            maxLines: 2
                        )
                            .padding(horizontal: 10, vertical: 8)
                            .background(color: fg.withOpacity(0.06), cornerRadius: 10)
                            .id("detail-line")
                            .transition(.accordion)
                    }
                }
                .padding(16)
                .frame(width: copyWidth)
                .background(color: fg.withOpacity(0.055), cornerRadius: 16)
                .id("copy")
                .transition(.morph)
            }
            .id("row")
            .transition(.morph)

            if expanded {
                VVStack(spacing: 10, alignment: .leading) {
                    VVHStack(spacing: 18) {
                        VText("Shipping", font: .caption, color: fg.withOpacity(0.62))
                            .frame(width: 88)
                        VText("Express delivery", font: .caption, color: fg.withOpacity(0.95))
                    }
                    VVHStack(spacing: 18) {
                        VText("Payment", font: .caption, color: fg.withOpacity(0.62))
                            .frame(width: 88)
                        VText("Visa ending in 4021", font: .caption, color: fg.withOpacity(0.95))
                    }
                    VVHStack(spacing: 18) {
                        VText("Contact", font: .caption, color: fg.withOpacity(0.62))
                            .frame(width: 88)
                        VText("notifications@vv.dev", font: .caption, color: fg.withOpacity(0.95))
                    }
                }
                .padding(18)
                .background(color: fg.withOpacity(0.045), cornerRadius: configuration.cornerRadius)
                .border(color: fg.withOpacity(0.12), width: 1, cornerRadii: VVCornerRadii(configuration.cornerRadius))
                .frame(width: contentWidth)
                .id("accordion")
                .transition(.accordion)
                .animation(.spring(response: 0.4, dampingFraction: 0.8))
            }
        }
        .padding(40)

        return view.renderAnimationSnapshots(width: contentWidth, env: env)
    }

    static func transitionAnimationScene(
        size: CGSize,
        configuration: PrimitiveSceneConfiguration,
        state: [String: VVLayoutAnimationSnapshot],
        expanded: Bool
    ) -> VVScene {
        let fg = foregroundColor(for: configuration.backgroundColor)
        let warm = SIMD4<Float>(0.96, 0.67, 0.18, 1)
        let cool = SIMD4<Float>(0.26, 0.73, 0.88, 1)
        let canvas = CGRect(x: 44, y: 36, width: max(1080, size.width - 88), height: max(740, size.height - 72))
        let stage = CGRect(x: canvas.minX + 28, y: canvas.minY + 74, width: min(canvas.width - 300, 760), height: canvas.height - 118)
        let contentOrigin = CGPoint(x: stage.minX + 28, y: stage.minY + 72)
        let rail = CGRect(x: stage.maxX + 24, y: stage.minY, width: 220, height: stage.height)
        let env = VVLayoutEnvironment(scale: 1, defaultTextColor: fg, defaultCornerRadius: configuration.cornerRadius)
        let checkpoints = [
            ("Stable identity via `.id(...)`", cool),
            ("Reusable transitions: `.morph` and `.accordion`", warm),
            ("Shared spring animation driver", cool),
            ("Works for arbitrary VVView trees", warm)
        ]

        var children: [any VVView] = [
            transitionPositioned(
                canvas,
                child: transitionGradientPanel(
                    size: canvas.size,
                    start: SIMD4<Float>(0.08, 0.09, 0.14, 0.92),
                    end: SIMD4<Float>(0.05, 0.09, 0.12, 0.98),
                    cornerRadius: 30,
                    angle: -.pi / 7,
                    border: VVBorder(width: 1, color: SIMD4<Float>(fg.x, fg.y, fg.z, 0.09))
                )
            ),
            transitionPositioned(
                CGRect(x: canvas.minX + 30, y: canvas.minY + 22, width: canvas.width - 60, height: 56),
                child: VVStack(spacing: 6, alignment: .leading) {
                    VText("First-Class VVView Animations", font: .title)
                    VText("The sample below is laid out as VVView content inside animated frames instead of manual text overlays.", font: .caption, color: fg.withOpacity(0.64))
                }
            ),
            transitionPositioned(
                stage,
                child: transitionPanel(size: stage.size, color: SIMD4<Float>(0.07, 0.08, 0.11, 0.9), cornerRadius: 24, border: VVBorder(width: 1, color: fg.withOpacity(0.08)))
            ),
            transitionPositioned(
                CGRect(x: stage.minX + 18, y: stage.minY + 18, width: stage.width - 36, height: 150),
                child: transitionGradientPanel(
                    size: CGSize(width: stage.width - 36, height: 150),
                    start: SIMD4<Float>(0.18, 0.2, 0.34, 0.56),
                    end: SIMD4<Float>(0.08, 0.09, 0.12, 0.08),
                    cornerRadius: 18,
                    angle: -.pi / 5
                )
            ),
            transitionPositioned(
                CGRect(x: stage.minX + 28, y: stage.minY + 24, width: stage.width - 56, height: 40),
                child: VVStack(spacing: 4, alignment: .leading) {
                    VText(expanded ? "Checkout Flow · Expanded" : "Checkout Flow · Compact", font: .caption, color: fg.withOpacity(0.74))
                    VText("The animated regions below clip and size their own content.", font: .caption, color: fg.withOpacity(0.52))
                }
            ),
            transitionPositioned(
                rail,
                child: transitionPanel(size: rail.size, color: SIMD4<Float>(0.06, 0.07, 0.1, 0.86), cornerRadius: 22, border: VVBorder(width: 1, color: fg.withOpacity(0.08)))
            ),
            transitionPositioned(
                CGRect(x: rail.minX + 18, y: rail.minY + 18, width: rail.width - 36, height: 60),
                child: VVStack(spacing: 6, alignment: .leading) {
                    VText(expanded ? "Expanded State" : "Collapsed State", font: .headline)
                    VText(expanded ? "Details are inserted and the card stack reflows without manual positioning." : "Replay or enable Auto Loop to inspect the transition path.", font: .caption, color: fg.withOpacity(0.66), maxLines: 3)
                }
            )
        ]

        for (index, entry) in checkpoints.enumerated() {
            let y = rail.minY + 116 + CGFloat(index) * 82
            children.append(
                transitionPositioned(
                    CGRect(x: rail.minX + 18, y: y, width: rail.width - 36, height: 60),
                    child: VVHStack(spacing: 12) {
                        VRect(color: entry.1, cornerRadius: 5).frame(width: 10, height: 10)
                        VText(entry.0, font: .caption, color: fg.withOpacity(0.92), maxLines: 2)
                    }
                    .padding(16)
                    .background(color: fg.withOpacity(0.04), cornerRadius: 14)
                    .border(color: fg.withOpacity(0.06), width: 1, cornerRadii: VVCornerRadii(14))
                )
            )
        }

        if let rowSnapshot = state["row"] {
            let rowFrame = transitionSnapshotFrame(rowSnapshot, origin: contentOrigin)
            children.append(
                transitionPositioned(
                    rowFrame,
                    child: transitionPanel(
                        size: rowFrame.size,
                        color: SIMD4<Float>(fg.x, fg.y, fg.z, 0.045 * rowSnapshot.opacity),
                        cornerRadius: 20
                    ).opacity(rowSnapshot.opacity)
                )
            )
        }

        if let heroSnapshot = state["hero"] {
            let frame = transitionSnapshotFrame(heroSnapshot, origin: contentOrigin)
            children.append(
                transitionPositioned(
                    frame,
                    child: VVZStack(children: [
                        transitionGradientPanel(
                            size: frame.size,
                            start: SIMD4<Float>(0.27, 0.45, 0.98, 0.96 * heroSnapshot.opacity),
                            end: SIMD4<Float>(0.88, 0.31, 0.56, 0.92 * heroSnapshot.opacity),
                            cornerRadius: configuration.cornerRadius,
                            angle: -.pi / 8
                        ),
                        VVStack(spacing: 6, alignment: .leading) {
                            VText("Payment Summary", font: .headline, color: .white)
                            VText(expanded ? "3 items, delivery, payment method, and contact details." : "Compact order card with expandable detail rows.", font: .caption, color: SIMD4<Float>(1, 1, 1, 0.8), maxLines: 2)
                        }
                        .padding(18)
                    ]).opacity(heroSnapshot.opacity)
                )
            )
        }

        if let mediaSnapshot = state["media"] {
            let frame = transitionSnapshotFrame(mediaSnapshot, origin: contentOrigin)
            children.append(
                transitionPositioned(
                    frame,
                    child: VVImage(
                        url: expanded ? "placeholder://hero-expanded" : "placeholder://hero-collapsed",
                        size: frame.size,
                        cornerRadius: 16
                    )
                    .opacity(mediaSnapshot.opacity)
                    .border(color: SIMD4<Float>(1, 1, 1, 0.08 * mediaSnapshot.opacity), width: 1, cornerRadii: VVCornerRadii(16))
                )
            )
        }

        if let copySnapshot = state["copy"] {
            let frame = transitionSnapshotFrame(copySnapshot, origin: contentOrigin)
            children.append(
                transitionPositioned(
                    frame,
                    child: VVStack(spacing: 10, alignment: .leading) {
                        VText("Design Review", font: .headline)
                        VText("Reusable motion for cards, details, and contextual expansion. Containers should size from content, not from manual scene math.", font: .body, color: fg.withOpacity(0.72), maxLines: expanded ? 3 : 2)
                        VText("Shared Animation Layer", font: .caption, color: .amber)
                    }
                    .padding(16)
                    .background(color: fg.withOpacity(0.055), cornerRadius: 16)
                    .opacity(copySnapshot.opacity)
                )
            )
        }

        if let detailSnapshot = state["detail-line"] {
            let frame = transitionSnapshotFrame(detailSnapshot, origin: contentOrigin)
            children.append(
                transitionPositioned(
                    frame,
                    child: VText("Auto-layout shifts siblings while preserving identity.", font: .caption, color: fg.withOpacity(0.82), maxLines: 2)
                        .padding(horizontal: 10, vertical: 8)
                        .background(color: fg.withOpacity(0.06), cornerRadius: 10)
                        .opacity(detailSnapshot.opacity)
                )
            )
        }

        if let accordionSnapshot = state["accordion"] {
            let frame = transitionSnapshotFrame(accordionSnapshot, origin: contentOrigin)
            children.append(
                transitionPositioned(
                    frame,
                    child: VVStack(spacing: 10, alignment: .leading) {
                        VVHStack(spacing: 18) {
                            VText("Shipping", font: .caption, color: fg.withOpacity(0.62)).frame(width: 88)
                            VText("Express delivery", font: .caption, color: fg.withOpacity(0.95))
                        }
                        VVHStack(spacing: 18) {
                            VText("Payment", font: .caption, color: fg.withOpacity(0.62)).frame(width: 88)
                            VText("Visa ending in 4021", font: .caption, color: fg.withOpacity(0.95))
                        }
                        VVHStack(spacing: 18) {
                            VText("Contact", font: .caption, color: fg.withOpacity(0.62)).frame(width: 88)
                            VText("notifications@vv.dev", font: .caption, color: fg.withOpacity(0.95))
                        }
                    }
                    .padding(18)
                    .background(color: fg.withOpacity(0.045), cornerRadius: configuration.cornerRadius)
                    .border(color: fg.withOpacity(0.14 * accordionSnapshot.opacity), width: 1, cornerRadii: VVCornerRadii(configuration.cornerRadius))
                    .opacity(accordionSnapshot.opacity)
                )
            )
        }

        return VVZStack(children: children).renderScene(width: canvas.maxX + 40, env: env)
    }

    private static func transitionSnapshotFrame(_ snapshot: VVLayoutAnimationSnapshot, origin: CGPoint) -> CGRect {
        CGRect(
            x: origin.x + snapshot.frame.midX - snapshot.frame.width * snapshot.scale * 0.5,
            y: origin.y + snapshot.frame.midY - snapshot.frame.height * snapshot.scale * 0.5,
            width: snapshot.frame.width * snapshot.scale,
            height: snapshot.frame.height * snapshot.scale
        )
    }

    private static func transitionPositioned(_ frame: CGRect, child: any VVView) -> VVPositionedFrame {
        VVPositionedFrame(frame: frame, child: child, clipRect: CGRect(origin: .zero, size: frame.size))
    }

    private static func transitionPanel(
        size: CGSize,
        color: SIMD4<Float>,
        cornerRadius: CGFloat,
        border: VVBorder? = nil
    ) -> VVNodeView {
        let base = VVQuadPrimitive(frame: CGRect(origin: .zero, size: size), color: color, cornerRadii: VVCornerRadii(cornerRadius))
        if let border {
            let borderQuad = VVQuadPrimitive(frame: CGRect(origin: .zero, size: size), color: .clear, cornerRadii: VVCornerRadii(cornerRadius), border: border)
            return VVNodeView(node: VVNode(children: [VVNode(primitives: [.quad(base)]), VVNode(zIndex: 1, primitives: [.quad(borderQuad)])]), size: size)
        }
        return VVNodeView(node: VVNode(primitives: [.quad(base)]), size: size)
    }

    private static func transitionGradientPanel(
        size: CGSize,
        start: SIMD4<Float>,
        end: SIMD4<Float>,
        cornerRadius: CGFloat,
        angle: CGFloat,
        border: VVBorder? = nil
    ) -> VVNodeView {
        let gradient = VVGradientQuadPrimitive(
            frame: CGRect(origin: .zero, size: size),
            startColor: start,
            endColor: end,
            angle: angle,
            cornerRadii: VVCornerRadii(cornerRadius),
            steps: 32
        )
        if let border {
            let borderQuad = VVQuadPrimitive(frame: CGRect(origin: .zero, size: size), color: .clear, cornerRadii: VVCornerRadii(cornerRadius), border: border)
            return VVNodeView(node: VVNode(children: [VVNode(primitives: [.gradientQuad(gradient)]), VVNode(zIndex: 1, primitives: [.quad(borderQuad)])]), size: size)
        }
        return VVNodeView(node: VVNode(primitives: [.gradientQuad(gradient)]), size: size)
    }

    private static func vvviewScene(size: CGSize, config: PrimitiveSceneConfiguration) -> VVScene {
        let fg = foregroundColor(for: config.backgroundColor)
        let env = VVLayoutEnvironment(scale: 1, defaultTextColor: fg, defaultCornerRadius: config.cornerRadius)
        let cr = config.cornerRadius
        let width = max(size.width - 80, 600)

        let view = VVStack(spacing: 24) {
            VVStack(spacing: 8) {
                VText("VVView Declarative DSL", font: .title)
                VDivider()
                VText("Build boxes, rows, surfaces, and media cards without dropping into manual coordinates.", font: .body)
                VText("This pass exercises padding, background, border, spacer, shadow, and image composition.", font: .caption, color: fg.withOpacity(0.6))
            }
            .padding(20)
            .background(color: fg.withOpacity(0.06), cornerRadius: cr)

            VVStack(spacing: 10) {
                VText("Container + Flexible Row", font: .headline)
                VVHStack(spacing: 12) {
                    VVImage(url: "placeholder://hero", size: CGSize(width: 96, height: 72), cornerRadius: cr)
                    VVStack(spacing: 6, alignment: .leading) {
                        VText("Media Card", font: .headline)
                        VText("The row uses a real spacer instead of equal-width slicing.", font: .caption, color: fg.withOpacity(0.65))
                    }
                    VSpacer(minLength: 12)
                    VVStack(spacing: 6, alignment: .trailing) {
                        VText("LIVE", font: .caption, color: .teal)
                        VText("12:45", font: .headline)
                    }
                }
                .overlay(alignment: .topTrailing) {
                    VText("LIVE", font: .caption, color: .white)
                        .padding(horizontal: 8, vertical: 4)
                        .background(color: .rose.withOpacity(0.9), cornerRadius: 999)
                        .offset(x: -6, y: 6)
                }
            }
            .padding(18)
            .background(color: fg.withOpacity(0.05), cornerRadius: cr)
            .border(color: fg.withOpacity(0.1), width: 1, cornerRadii: VVCornerRadii(cr))

            VVStack(spacing: 12) {
                VText("Basic UI Blocks", font: .headline)
                VVHStack(spacing: 16) {
                    VVStack(spacing: 8) {
                        VText("Panel", font: .body)
                        VRect(color: .indigo.withOpacity(0.3), cornerRadius: 4).frame(height: 40)
                        VRect(color: .indigo.withOpacity(0.2), cornerRadius: 4).frame(height: 30)
                        VRect(color: .indigo.withOpacity(0.14), cornerRadius: 4).frame(height: 18)
                    }
                    VVStack(spacing: 8) {
                        VText("Sidebar", font: .body)
                        VRect(color: .teal.withOpacity(0.3), cornerRadius: 4).frame(height: 30)
                        VRect(color: .teal.withOpacity(0.2), cornerRadius: 4).frame(height: 40)
                        VRect(color: .teal.withOpacity(0.14), cornerRadius: 4).frame(height: 24)
                    }
                }
            }
            .padding(20)
            .background(color: fg.withOpacity(0.04), cornerRadius: cr)
            .border(color: fg.withOpacity(0.1), width: 1, cornerRadii: VVCornerRadii(cr))

            VVStack(spacing: 12, alignment: .leading) {
                VText("Flow Layout", font: .headline)
                VText("Chips and token-like UI no longer need manual row splitting.", font: .caption, color: fg.withOpacity(0.66))
                VVFlowStack(horizontalSpacing: 10, verticalSpacing: 10) {
                    VText("Layout", font: .caption, color: fg.withOpacity(0.92))
                        .padding(horizontal: 12, vertical: 8)
                        .background(color: .indigo.withOpacity(0.22), cornerRadius: 999)
                    VText("Animation", font: .caption, color: fg.withOpacity(0.92))
                        .padding(horizontal: 12, vertical: 8)
                        .background(color: .teal.withOpacity(0.22), cornerRadius: 999)
                    VText("Containers", font: .caption, color: fg.withOpacity(0.92))
                        .padding(horizontal: 12, vertical: 8)
                        .background(color: .amber.withOpacity(0.22), cornerRadius: 999)
                    VText("Scroll", font: .caption, color: fg.withOpacity(0.92))
                        .padding(horizontal: 12, vertical: 8)
                        .background(color: .rose.withOpacity(0.22), cornerRadius: 999)
                    VText("Overlay", font: .caption, color: fg.withOpacity(0.92))
                        .padding(horizontal: 12, vertical: 8)
                        .background(color: fg.withOpacity(0.08), cornerRadius: 999)
                    VText("Text Wrapping", font: .caption, color: fg.withOpacity(0.92))
                        .padding(horizontal: 12, vertical: 8)
                        .background(color: .teal.withOpacity(0.14), cornerRadius: 999)
                    VText("VVView", font: .caption, color: fg.withOpacity(0.92))
                        .padding(horizontal: 12, vertical: 8)
                        .background(color: .indigo.withOpacity(0.14), cornerRadius: 999)
                    VText("Primitives", font: .caption, color: fg.withOpacity(0.92))
                        .padding(horizontal: 12, vertical: 8)
                        .background(color: .amber.withOpacity(0.14), cornerRadius: 999)
                }
                .fillWidth(alignment: .leading)
            }
            .padding(20)
            .background(color: fg.withOpacity(0.04), cornerRadius: cr)
            .border(color: fg.withOpacity(0.1), width: 1, cornerRadii: VVCornerRadii(cr))

            VVStack(spacing: 12, alignment: .leading) {
                VText("Overlay + Scroll Container", font: .headline)
                VText("Badges, chrome, and clipped scrolling content now work at the VVView layer.", font: .caption, color: fg.withOpacity(0.66))
                    .lineSpacing(2)

                VVHStack(spacing: 18) {
                    VVStack(spacing: 8, alignment: .leading) {
                        VText("Overlay Card", font: .body)
                        VRect(color: .teal.withOpacity(0.2), cornerRadius: 14)
                            .frame(width: 220, height: 110)
                            .overlay(alignment: .bottomTrailing) {
                                VText("3 new", font: .caption, color: .white)
                                    .padding(horizontal: 10, vertical: 6)
                                    .background(color: .teal, cornerRadius: 999)
                                    .offset(x: -10, y: -10)
                            }
                            .background(alignment: .center) {
                                VRect(color: .black.withOpacity(0.18), cornerRadius: 18)
                                    .frame(width: 236, height: 126)
                            }
                    }

                    VVStack(spacing: 8, alignment: .leading) {
                        VText("Scroll View", font: .body)
                        VVStack(spacing: 8, alignment: .leading) {
                            VText("Scrollable row 1", font: .caption, color: fg.withOpacity(0.9))
                                .padding(horizontal: 12, vertical: 10)
                                .fillWidth(alignment: .leading)
                                .background(color: fg.withOpacity(0.08), cornerRadius: 10)
                            VText("Scrollable row 2", font: .caption, color: fg.withOpacity(0.9))
                                .padding(horizontal: 12, vertical: 10)
                                .fillWidth(alignment: .leading)
                                .background(color: fg.withOpacity(0.05), cornerRadius: 10)
                            VText("Scrollable row 3", font: .caption, color: fg.withOpacity(0.9))
                                .padding(horizontal: 12, vertical: 10)
                                .fillWidth(alignment: .leading)
                                .background(color: fg.withOpacity(0.08), cornerRadius: 10)
                            VText("Scrollable row 4", font: .caption, color: fg.withOpacity(0.9))
                                .padding(horizontal: 12, vertical: 10)
                                .fillWidth(alignment: .leading)
                                .background(color: fg.withOpacity(0.05), cornerRadius: 10)
                            VText("Scrollable row 5", font: .caption, color: fg.withOpacity(0.9))
                                .padding(horizontal: 12, vertical: 10)
                                .fillWidth(alignment: .leading)
                                .background(color: fg.withOpacity(0.08), cornerRadius: 10)
                            VText("Scrollable row 6", font: .caption, color: fg.withOpacity(0.9))
                                .padding(horizontal: 12, vertical: 10)
                                .fillWidth(alignment: .leading)
                                .background(color: fg.withOpacity(0.05), cornerRadius: 10)
                        }
                        .scrollContainer(
                            axis: .vertical,
                            viewportSize: CGSize(width: 260, height: 128),
                            contentOffset: CGPoint(x: 0, y: 34)
                        )
                        .background(color: fg.withOpacity(0.035), cornerRadius: 14)
                        .border(color: fg.withOpacity(0.08), width: 1, cornerRadii: VVCornerRadii(14))
                    }
                }
            }
            .padding(20)
            .background(color: fg.withOpacity(0.04), cornerRadius: cr)
            .border(color: fg.withOpacity(0.1), width: 1, cornerRadii: VVCornerRadii(cr))

            VVHStack(spacing: 16) {
                VVStack(spacing: 8, alignment: .leading) {
                    VText("Accordion State A", font: .headline)
                    VText("Expanded content can be represented with stacked blocks and clip-driven transitions.", font: .caption, color: fg.withOpacity(0.65))
                    VRect(color: .amber.withOpacity(0.25), cornerRadius: 8).frame(height: 42)
                    VRect(color: .amber.withOpacity(0.16), cornerRadius: 8).frame(height: 32)
                    VRect(color: .amber.withOpacity(0.1), cornerRadius: 8).frame(height: 20)
                }
                .padding(18)
                .background(color: .darkSurface, cornerRadius: cr)
                .shadow(color: .black.withOpacity(0.25), spread: 10, cornerRadii: VVCornerRadii(cr))

                VVStack(spacing: 8, alignment: .leading) {
                    VText("Accordion State B", font: .headline)
                    VText("Collapsed content keeps the same shell while layout above and below remains composable.", font: .caption, color: fg.withOpacity(0.65))
                    VRect(color: .rose.withOpacity(0.22), cornerRadius: 8).frame(height: 18)
                }
                .padding(18)
                .background(color: fg.withOpacity(0.05), cornerRadius: cr)
                .border(color: fg.withOpacity(0.12), width: 1, cornerRadii: VVCornerRadii(cr))
            }

            VVStack(spacing: 8) {
                VText("Conditional Content", font: .headline)
                if config.cornerRadius > 10 {
                    VText("Rounded shell active", font: .body, color: .teal)
                } else {
                    VText("Sharper shell active", font: .body, color: .amber)
                }
                VDivider(color: fg.withOpacity(0.15))
                for i in 1...3 {
                    VText("Action \(i)", font: .code, color: fg.withOpacity(0.7))
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
