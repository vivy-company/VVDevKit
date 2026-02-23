import SwiftUI
import AppKit
import Combine
import Metal
import VVGit
import VVLSP
import VVMarkdown

/// LSP connection status
public enum VVLSPStatus: Equatable, Sendable {
    case disabled
    case noServer(language: String)
    case starting(server: String)
    case running(server: String)
    case failed(error: String)
}

/// SwiftUI code editor view - batteries included
/// Automatically handles syntax highlighting and LSP for supported languages
public struct VVCodeView: View {
    // MARK: - Bindings

    @Binding private var document: VVDocument

    // MARK: - Configuration

    private var language: VVLanguage?
    private var theme: VVTheme
    private var configuration: VVConfiguration

    // MARK: - Git Integration

    private var gitDiff: String?
    private var gitBlame: [VVBlameInfo]?

    // MARK: - LSP Integration

    private var customLSPClient: (any VVLSPClient)?
    private var disableLSP: Bool = false

    // MARK: - Callbacks

    private var onTextChange: ((String) -> Void)?
    private var onSelectionChange: ((NSRange) -> Void)?
    private var onCursorPositionChange: ((VVTextPosition) -> Void)?
    private var onLSPStatusChange: ((VVLSPStatus) -> Void)?

    // MARK: - State

    @State private var languageServer: VVLanguageServer?
    @State private var serverStarted = false
    @State private var lspStatus: VVLSPStatus = .disabled

    // MARK: - Initialization

    public init(document: Binding<VVDocument>) {
        self._document = document
        self.language = nil
        self.theme = .defaultDark
        self.configuration = .default
    }

    public var body: some View {
        VVCodeViewRepresentable(
            document: $document,
            language: language,
            theme: theme,
            configuration: configuration,
            gitDiff: gitDiff,
            gitBlame: gitBlame,
            lspClient: customLSPClient ?? languageServer,
            onTextChange: onTextChange,
            onSelectionChange: onSelectionChange,
            onCursorPositionChange: onCursorPositionChange
        )
        .task(priority: .background) {
            await startLSPIfNeeded()
        }
        .onChange(of: effectiveLanguage?.identifier) { _ in
            Task {
                await restartLSP()
            }
        }
    }

    private var effectiveLanguage: VVLanguage? {
        language ?? document.language
    }

    private func startLSPIfNeeded() async {
        guard !disableLSP, customLSPClient == nil, !serverStarted else {
            if disableLSP {
                updateLSPStatus(.disabled)
            }
            return
        }
        guard let lang = effectiveLanguage?.identifier else {
            updateLSPStatus(.disabled)
            return
        }

        let rootPath = document.fileURL?.deletingLastPathComponent().path
            ?? FileManager.default.currentDirectoryPath

        guard let server = VVLanguageServer(language: lang, rootPath: rootPath) else {
            updateLSPStatus(.noServer(language: lang))
            return
        }

        updateLSPStatus(.starting(server: server.serverName))

        do {
            try await server.start()
            await MainActor.run {
                self.languageServer = server
                self.serverStarted = true
                self.updateLSPStatus(.running(server: server.serverName))
            }
        } catch {
            let errorMsg = String(describing: error)
            updateLSPStatus(.failed(error: errorMsg))
        }
    }

    private func updateLSPStatus(_ status: VVLSPStatus) {
        Task { @MainActor in
            self.lspStatus = status
            self.onLSPStatusChange?(status)
        }
    }

    private func restartLSP() async {
        if let server = languageServer {
            await server.shutdownAsync()
        }
        languageServer = nil
        serverStarted = false
        await startLSPIfNeeded()
    }
}

// MARK: - NSViewRepresentable (Internal)

struct VVCodeViewRepresentable: NSViewRepresentable {
    @Binding var document: VVDocument
    var language: VVLanguage?
    var theme: VVTheme
    var configuration: VVConfiguration
    var gitDiff: String?
    var gitBlame: [VVBlameInfo]?
    var lspClient: (any VVLSPClient)?
    var onTextChange: ((String) -> Void)?
    var onSelectionChange: ((NSRange) -> Void)?
    var onCursorPositionChange: ((VVTextPosition) -> Void)?

    func makeNSView(context: Context) -> NSView {
        // Metal-only rendering
        makeMetalView(context: context)
    }

    private func makeMetalView(context: Context) -> VVMetalEditorContainerView {
        let containerView = VVMetalEditorContainerView(
            frame: .zero,
            configuration: configuration,
            theme: theme
        )

        containerView.delegate = context.coordinator
        containerView.setText(document.text)

        if let language = language ?? document.language {
            containerView.setLanguage(language)
        }

        if let diff = gitDiff {
            let hunks = VVDiffParser.parse(unifiedDiff: diff)
            containerView.setGitHunks(hunks)
        }

        if let blame = gitBlame {
            containerView.setBlameInfo(blame)
        }

        // Setup LSP client
        if let client = lspClient {
            let uri = document.fileURL?.absoluteString ?? "untitled:\(UUID().uuidString)"
            containerView.setLSPClient(client, documentURI: uri)
        }

        // Focus the text view after a delay to ensure window is ready
        DispatchQueue.main.async {
            containerView.focusTextView()
        }

        return containerView
    }

    func updateNSView(_ nsView: NSView, context: Context) {
        guard let metalView = nsView as? VVMetalEditorContainerView else { return }
        updateMetalView(metalView, context: context)
    }

    private func updateMetalView(_ nsView: VVMetalEditorContainerView, context: Context) {
        // Update text if changed externally
        if nsView.text != document.text {
            nsView.setText(document.text)
        }

        // Update language
        if let language = language ?? document.language {
            nsView.setLanguage(language)
        }

        // Update theme
        if context.coordinator.lastTheme != theme {
            nsView.setTheme(theme)
            context.coordinator.lastTheme = theme
        }

        // Update configuration
        if context.coordinator.lastConfiguration != configuration {
            nsView.setConfiguration(configuration)
            context.coordinator.lastConfiguration = configuration
        }

        // Update git data
        if context.coordinator.lastGitDiff != gitDiff {
            context.coordinator.lastGitDiff = gitDiff
            let hunks: [VVDiffHunk] = gitDiff.map { VVDiffParser.parse(unifiedDiff: $0) } ?? []
            nsView.setGitHunks(hunks)
        }

        let blame: [VVBlameInfo] = gitBlame ?? []
        if context.coordinator.lastGitBlame != blame {
            nsView.setBlameInfo(blame)
            context.coordinator.lastGitBlame = blame
        }

        // Update LSP client
        let resolvedURI = document.fileURL?.absoluteString ?? context.coordinator.untitledDocumentURI
        let incomingClientID = lspClient.map(ObjectIdentifier.init)

        if context.coordinator.lastLSPClientID != incomingClientID || context.coordinator.lastLSPDocumentURI != resolvedURI {
            if let client = lspClient {
                nsView.setLSPClient(client, documentURI: resolvedURI)
            } else {
                nsView.setLSPClient(nil, documentURI: nil)
            }
            context.coordinator.lastLSPClientID = incomingClientID
            context.coordinator.lastLSPDocumentURI = lspClient == nil ? nil : resolvedURI
        }
    }

    // Metal-only; AppKit backend removed.

    func makeCoordinator() -> Coordinator {
        Coordinator(
            document: $document,
            onTextChange: onTextChange,
            onSelectionChange: onSelectionChange,
            onCursorPositionChange: onCursorPositionChange
        )
    }

    class Coordinator: NSObject, VVEditorDelegate {
        var document: Binding<VVDocument>
        var onTextChange: ((String) -> Void)?
        var onSelectionChange: ((NSRange) -> Void)?
        var onCursorPositionChange: ((VVTextPosition) -> Void)?
        var lastTheme: VVTheme?
        var lastConfiguration: VVConfiguration?
        var lastGitDiff: String?
        var lastGitBlame: [VVBlameInfo] = []
        var lastLSPClientID: ObjectIdentifier?
        var lastLSPDocumentURI: String?
        let untitledDocumentURI = "untitled:\(UUID().uuidString)"

        init(document: Binding<VVDocument>,
             onTextChange: ((String) -> Void)?,
             onSelectionChange: ((NSRange) -> Void)?,
             onCursorPositionChange: ((VVTextPosition) -> Void)?) {
            self.document = document
            self.onTextChange = onTextChange
            self.onSelectionChange = onSelectionChange
            self.onCursorPositionChange = onCursorPositionChange
        }

        func editorDidChangeText(_ text: String) {
            DispatchQueue.main.async { [weak self] in
                self?.document.wrappedValue.text = text
                self?.onTextChange?(text)
            }
        }

        func editorDidChangeSelection(_ range: NSRange) {
            onSelectionChange?(range)
        }

        func editorDidChangeCursorPosition(_ position: VVTextPosition) {
            onCursorPositionChange?(position)
        }
    }
}

// MARK: - View Modifiers

extension VVCodeView {
    /// Set the programming language for syntax highlighting
    public func language(_ language: VVLanguage?) -> VVCodeView {
        var view = self
        view.language = language
        return view
    }

    /// Set the editor theme
    public func theme(_ theme: VVTheme) -> VVCodeView {
        var view = self
        view.theme = theme
        return view
    }

    /// Set the editor configuration
    public func configuration(_ configuration: VVConfiguration) -> VVCodeView {
        var view = self
        view.configuration = configuration
        return view
    }

    /// Set git diff for gutter display (unified diff format)
    public func gitDiff(_ diff: String?) -> VVCodeView {
        var view = self
        view.gitDiff = diff
        return view
    }

    /// Set git blame information for inline display
    public func gitBlame(_ blame: [VVBlameInfo]?) -> VVCodeView {
        var view = self
        view.gitBlame = blame
        return view
    }

    /// Set custom LSP client (overrides auto-managed server)
    public func lspClient(_ client: (any VVLSPClient)?) -> VVCodeView {
        var view = self
        view.customLSPClient = client
        return view
    }

    /// Disable automatic LSP server management
    public func lspDisabled(_ disabled: Bool = true) -> VVCodeView {
        var view = self
        view.disableLSP = disabled
        return view
    }

    /// Callback when text changes
    public func onTextChange(_ handler: @escaping (String) -> Void) -> VVCodeView {
        var view = self
        view.onTextChange = handler
        return view
    }

    /// Callback when selection changes
    public func onSelectionChange(_ handler: @escaping (NSRange) -> Void) -> VVCodeView {
        var view = self
        view.onSelectionChange = handler
        return view
    }

    /// Callback when cursor position changes
    public func onCursorPositionChange(_ handler: @escaping (VVTextPosition) -> Void) -> VVCodeView {
        var view = self
        view.onCursorPositionChange = handler
        return view
    }

    /// Callback when LSP status changes
    public func onLSPStatusChange(_ handler: @escaping (VVLSPStatus) -> Void) -> VVCodeView {
        var view = self
        view.onLSPStatusChange = handler
        return view
    }

    // MARK: - Convenience Modifiers

    /// Set font
    public func font(_ font: NSFont) -> VVCodeView {
        var view = self
        view.configuration = view.configuration.with(font: font)
        return view
    }

    /// Set tab width
    public func tabWidth(_ width: Int) -> VVCodeView {
        var view = self
        view.configuration = view.configuration.with(tabWidth: width)
        return view
    }

    /// Enable/disable line wrapping
    public func wrapLines(_ wrap: Bool) -> VVCodeView {
        var view = self
        view.configuration = view.configuration.with(wrapLines: wrap)
        return view
    }
}

// MARK: - Preview

#if DEBUG
struct VVCodeView_Previews: PreviewProvider {
    static var previews: some View {
        VVCodeViewPreview()
    }

    struct VVCodeViewPreview: View {
        @State private var document = VVDocument(
            text: """
            import Foundation

            func greet(_ name: String) -> String {
                return "Hello, \\(name)!"
            }

            let message = greet("World")
            print(message)
            """,
            language: .swift
        )

        var body: some View {
            VVCodeView(document: $document)
                .language(.swift)
                .theme(.defaultDark)
                .frame(minWidth: 400, minHeight: 300)
        }
    }
}
#endif
