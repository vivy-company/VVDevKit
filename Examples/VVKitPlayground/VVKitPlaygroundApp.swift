#if os(macOS)
import AppKit
import Metal
import SwiftUI
import VVChatTimeline
import VVCode
import VVMarkdown
import VVMetalPrimitives
import UniformTypeIdentifiers

@main
struct VVKitPlaygroundApp: App {
    var body: some Scene {
        WindowGroup("VVKit Playground") {
            ContentView()
        }
        .windowStyle(.titleBar)
    }
}

struct ContentView: View {
    var body: some View {
        TabView {
            CodePlaygroundView()
                .tabItem { Text("Code") }

            MarkdownPlaygroundView()
                .tabItem { Text("Markdown") }

            MermaidPlaygroundView()
                .tabItem { Text("Mermaid") }

            PrimitivesPlaygroundView()
                .tabItem { Text("Primitives") }

            ChatPlaygroundView()
                .tabItem { Text("Chat") }
        }
        .frame(minWidth: 1100, minHeight: 720)
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

struct PrimitivesPlaygroundView: View {
    @State private var useDarkBackground = true
    @State private var showGrid = true
    @State private var showBullets = true
    @State private var showPie = true
    @State private var showBorders = true
    @State private var cornerRadius: Double = 16

    private var configuration: PrimitiveSceneConfiguration {
        PrimitiveSceneConfiguration(
            backgroundColor: useDarkBackground ? SIMD4(0.08, 0.09, 0.1, 1) : SIMD4(0.96, 0.96, 0.97, 1),
            showGrid: showGrid,
            showBullets: showBullets,
            showPie: showPie,
            showBorders: showBorders,
            cornerRadius: CGFloat(cornerRadius)
        )
    }

    var body: some View {
        HSplitView {
            VStack(alignment: .leading, spacing: 12) {
                Text("Primitives")
                    .font(.headline)

                Toggle("Dark Background", isOn: $useDarkBackground)
                Toggle("Show Grid", isOn: $showGrid)
                Toggle("Show Bullets", isOn: $showBullets)
                Toggle("Show Pie", isOn: $showPie)
                Toggle("Show Borders", isOn: $showBorders)

                HStack {
                    Text("Corner")
                    Slider(value: $cornerRadius, in: 0...28, step: 1)
                    Text("\(Int(cornerRadius))")
                        .frame(width: 28, alignment: .trailing)
                }

                Text("Uses VVMetalPrimitives rendered through VVChatTimelineMetalView.")
                    .font(.caption)
                    .foregroundStyle(.secondary)
                    .fixedSize(horizontal: false, vertical: true)

                Spacer()
            }
            .padding(16)
            .frame(minWidth: 240, idealWidth: 280, maxWidth: 340)

            PrimitiveSceneRepresentable(configuration: configuration)
        }
    }
}

struct PrimitiveSceneConfiguration: Equatable {
    var backgroundColor: SIMD4<Float>
    var showGrid: Bool
    var showBullets: Bool
    var showPie: Bool
    var showBorders: Bool
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
            showGrid: true,
            showBullets: true,
            showPie: true,
            showBorders: true,
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
    @State private var simulationTask: Task<Void, Never>?
    @State private var isAutoRunning = false
    @State private var streamResponses = true
    @State private var chunkDelay: Double = 0.06
    @State private var minChunkSize = 8
    @State private var maxChunkSize = 28
    @State private var pauseBetweenMessages: Double = 0.8
    @State private var useComplexResponses = true
    @State private var followStreaming = true

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

    private func appendUserMessage() {
        let content = SampleData.userMessages[userIndex % SampleData.userMessages.count]
        userIndex += 1
        controller.appendMessage(
            VVChatMessage(role: .user, state: .final, content: content, timestamp: Date())
        )
    }

    private func appendAssistantMessage() {
        let content = assistantResponse(forIndex: assistantIndex)
        assistantIndex += 1
        controller.appendMessage(
            VVChatMessage(role: .assistant, state: .final, content: content, timestamp: Date())
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
        await MainActor.run {
            appendUserMessage()
        }

        if streamResponses {
            await streamNextAssistantResponse()
        } else {
            await MainActor.run {
                appendAssistantMessage()
            }
        }
    }

    private func streamNextAssistantResponse() async {
        let response = await MainActor.run { assistantResponse(forIndex: assistantIndex) }
        await streamAssistantMessage(response)
        await MainActor.run { assistantIndex += 1 }
    }

    private func streamAssistantMessage(_ content: String) async {
        let chunks = chunkedSegments(for: content)
        let draftID = await MainActor.run {
            if followStreaming {
                controller.jumpToLatest()
            }
            return controller.beginStreamingAssistantMessage(content: "")
        }
        var assembled = ""
        for chunk in chunks {
            if Task.isCancelled { break }
            assembled += chunk
            await MainActor.run {
                if followStreaming {
                    controller.jumpToLatest()
                }
                controller.updateDraftMessage(id: draftID, content: assembled, throttle: false)
            }
            try? await Task.sleep(nanoseconds: UInt64(chunkDelay * 1_000_000_000))
        }
        await MainActor.run {
            controller.finalizeMessage(id: draftID, content: assembled)
        }
    }

    private func assistantResponse(forIndex index: Int) -> String {
        let responses = useComplexResponses ? SampleData.complexAssistantResponses : SampleData.assistantMessages
        return responses[index % responses.count]
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
        let view = VVChatTimelineView()
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
      "name": "VVKit",
      "features": ["Code", "Markdown", "Chat"],
      "version": "0.1.0",
      "meta": {
        "platforms": ["macOS", "iOS"],
        "experimental": true
      }
    }
    """

    static let markdownSample = """
    # VVKit Markdown Demo

    VVKit renders markdown with Metal. This sample includes: **bold**, _italic_, `inline code`, and links.

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
        "Does the editor support wrapping and blame?"
    ]

    static let assistantMessages: [String] = [
        "Sure! Here is a quick walkthrough of VVKit components and how they connect.",
        "Markdown supports tables, math, and mermaid diagrams. Try editing the sample.",
        "Inline blame is available when you provide blame info and enable it in configuration."
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
        """
    ]

    static let draftSteps: [String] = [
        "Streaming draft message...",
        "Adding a second line in the draft.",
        "Finishing up with a final thought."
    ]

    static func chatMessages() -> [VVChatMessage] {
        let now = Date()
        return [
            VVChatMessage(role: .system, state: .final, content: "VVKit demo chat initialized.", timestamp: now),
            VVChatMessage(role: .user, state: .final, content: userMessages[0], timestamp: now.addingTimeInterval(5)),
            VVChatMessage(role: .assistant, state: .final, content: assistantMessages[0], timestamp: now.addingTimeInterval(10)),
            VVChatMessage(role: .user, state: .final, content: userMessages[1], timestamp: now.addingTimeInterval(15)),
            VVChatMessage(role: .assistant, state: .final, content: assistantMessages[1], timestamp: now.addingTimeInterval(20))
        ]
    }

    static func chatStyle(dark: Bool, fontSize: Double) -> VVChatTimelineStyle {
        let theme = dark ? MarkdownTheme.dark : MarkdownTheme.light
        let baseFont = NSFont.systemFont(ofSize: fontSize)
        let background: SIMD4<Float> = dark ? SIMD4(0.08, 0.09, 0.1, 1) : SIMD4(0.96, 0.96, 0.97, 1)
        let bubbleColor: SIMD4<Float> = dark ? SIMD4(0.18, 0.26, 0.38, 1) : SIMD4(0.82, 0.9, 1, 1)
        let headerColor: SIMD4<Float> = dark ? SIMD4(0.75, 0.8, 0.9, 1) : SIMD4(0.25, 0.3, 0.35, 1)
        let timestampColor: SIMD4<Float> = dark ? SIMD4(0.6, 0.65, 0.7, 1) : SIMD4(0.4, 0.45, 0.5, 1)
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
        let width = max(size.width, 720)
        let height = max(size.height, 520)
        let inset: CGFloat = 28
        let contentRect = CGRect(x: inset, y: inset, width: width - inset * 2, height: height - inset * 2)

        let baseForeground = foregroundColor(for: configuration.backgroundColor)
        let gridColor = SIMD4<Float>(baseForeground.x, baseForeground.y, baseForeground.z, 0.18)

        var builder = VVSceneBuilder()

        if configuration.showGrid {
            let step: CGFloat = 40
            var x = contentRect.minX
            while x <= contentRect.maxX {
                let line = VVLinePrimitive(
                    start: CGPoint(x: x, y: contentRect.minY),
                    end: CGPoint(x: x, y: contentRect.maxY),
                    thickness: 1,
                    color: gridColor
                )
                builder.add(kind: .line(line), zIndex: 0)
                x += step
            }

            var y = contentRect.minY
            while y <= contentRect.maxY {
                let line = VVLinePrimitive(
                    start: CGPoint(x: contentRect.minX, y: y),
                    end: CGPoint(x: contentRect.maxX, y: y),
                    thickness: 1,
                    color: gridColor
                )
                builder.add(kind: .line(line), zIndex: 0)
                y += step
            }
        }

        let tileSize = CGSize(width: 160, height: 96)
        let tileGap: CGFloat = 22
        let tileY = contentRect.minY + 12
        let tileX = contentRect.minX + 12
        let tiles: [SIMD4<Float>] = [
            SIMD4(0.2, 0.65, 0.9, 0.9),
            SIMD4(0.85, 0.38, 0.5, 0.9),
            SIMD4(0.95, 0.7, 0.2, 0.9)
        ]

        for (index, color) in tiles.enumerated() {
            let x = tileX + CGFloat(index) * (tileSize.width + tileGap)
            let frame = CGRect(x: x, y: tileY, width: tileSize.width, height: tileSize.height)
            let quad = VVQuadPrimitive(frame: frame, color: color, cornerRadius: configuration.cornerRadius)
            builder.add(kind: .quad(quad), zIndex: 1)
        }

        if configuration.showBorders {
            let borderFrame = CGRect(x: tileX, y: tileY + tileSize.height + 24, width: 180, height: 86)
            let border = VVBlockQuoteBorderPrimitive(frame: borderFrame, color: baseForeground, borderWidth: 4)
            builder.add(kind: .blockQuoteBorder(border), zIndex: 1)

            let tableOrigin = CGPoint(x: tileX + 210, y: borderFrame.minY)
            let tableWidth: CGFloat = 240
            let rowHeight: CGFloat = 28
            let rows = 3
            let cols = 3

            for row in 0...rows {
                let y = tableOrigin.y + CGFloat(row) * rowHeight
                let line = VVTableLinePrimitive(
                    start: CGPoint(x: tableOrigin.x, y: y),
                    end: CGPoint(x: tableOrigin.x + tableWidth, y: y),
                    color: baseForeground,
                    lineWidth: 1
                )
                builder.add(kind: .tableLine(line), zIndex: 1)
            }

            for col in 0...cols {
                let x = tableOrigin.x + CGFloat(col) * (tableWidth / CGFloat(cols))
                let line = VVTableLinePrimitive(
                    start: CGPoint(x: x, y: tableOrigin.y),
                    end: CGPoint(x: x, y: tableOrigin.y + CGFloat(rows) * rowHeight),
                    color: baseForeground,
                    lineWidth: 1
                )
                builder.add(kind: .tableLine(line), zIndex: 1)
            }
        }

        if configuration.showBullets {
            let bulletSize: CGFloat = 16
            let bulletY = contentRect.maxY - 120
            let bulletX = contentRect.minX + 12
            let bulletColor = baseForeground

            let bullets: [VVBulletType] = [
                .disc,
                .circle,
                .square,
                .checkbox(true),
                .checkbox(false)
            ]

            for (index, type) in bullets.enumerated() {
                let x = bulletX + CGFloat(index) * (bulletSize + 18)
                let bullet = VVBulletPrimitive(
                    position: CGPoint(x: x, y: bulletY),
                    size: bulletSize,
                    color: bulletColor,
                    type: type
                )
                builder.add(kind: .bullet(bullet), zIndex: 2)
            }
        }

        if configuration.showPie {
            let center = CGPoint(x: contentRect.maxX - 140, y: contentRect.minY + 150)
            let radius: CGFloat = 70
            let angles: [CGFloat] = [0, 0.9, 1.8, 2.6, 4.1, CGFloat.pi * 2]
            let colors: [SIMD4<Float>] = [
                SIMD4(0.3, 0.8, 0.5, 0.9),
                SIMD4(0.95, 0.6, 0.2, 0.9),
                SIMD4(0.5, 0.6, 0.95, 0.9),
                SIMD4(0.9, 0.4, 0.6, 0.9),
                SIMD4(0.7, 0.7, 0.75, 0.9)
            ]

            for index in 0..<(angles.count - 1) {
                let slice = VVPieSlicePrimitive(
                    center: center,
                    radius: radius,
                    startAngle: angles[index],
                    endAngle: angles[index + 1],
                    color: colors[index % colors.count]
                )
                builder.add(kind: .pieSlice(slice), zIndex: 2)
            }
        }

        let accentLine = VVLinePrimitive(
            start: CGPoint(x: contentRect.minX, y: contentRect.maxY - 20),
            end: CGPoint(x: contentRect.maxX, y: contentRect.maxY - 20),
            thickness: 2,
            color: SIMD4(baseForeground.x, baseForeground.y, baseForeground.z, 0.5)
        )
        builder.add(kind: .line(accentLine), zIndex: 1)

        return builder.scene
    }

    private static func foregroundColor(for background: SIMD4<Float>) -> SIMD4<Float> {
        let luminance = 0.2126 * background.x + 0.7152 * background.y + 0.0722 * background.z
        if luminance > 0.7 {
            return SIMD4(0.18, 0.2, 0.24, 1)
        }
        return SIMD4(0.9, 0.92, 0.95, 1)
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
#endif
