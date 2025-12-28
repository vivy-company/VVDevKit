import Foundation
import Combine
import LanguageServerProtocol

/// Built-in LSP client that spawns and manages a language server process
public final class VVLanguageServer: VVLSPClient, @unchecked Sendable {
    private let config: LSPServerConfig
    private let rootPath: String
    private var transport: LSPTransport?
    private var process: Process?

    private let diagnosticsSubject = PassthroughSubject<DocumentDiagnostics, Never>()
    private var serverCapabilities: ServerCapabilities?

    private let stateQueue = DispatchQueue(label: "VVLSP.VVLanguageServer.state")
    private var isInitialized = false
    private var isShutdown = false

    /// The name of the language server
    public var serverName: String { config.name }

    public enum ServerError: Error {
        case notInitialized
        case serverNotFound(String)
        case spawnFailed(String)
        case initializationFailed(String)
        case requestFailed(String)
    }

    // MARK: - Initialization

    /// Create a language server with a specific configuration
    public init(config: LSPServerConfig, rootPath: String) {
        self.config = config
        self.rootPath = rootPath
    }

    /// Create a language server for a language identifier
    public convenience init?(language: String, rootPath: String) {
        guard let config = LSPServerRegistry.shared.server(forLanguage: language) else {
            return nil
        }
        self.init(config: config, rootPath: rootPath)
    }

    /// Create a language server for a file path
    public convenience init?(filePath: String, rootPath: String) {
        guard let config = LSPServerRegistry.shared.server(forPath: filePath) else {
            return nil
        }
        self.init(config: config, rootPath: rootPath)
    }

    deinit {
        // Don't call shutdown() here - it's async and can cause race conditions
        // Just terminate the process synchronously
        process?.terminate()
    }

    // MARK: - Lifecycle

    /// Start the language server
    public func start() async throws {
        guard let path = findExecutable(config.command) else {
            throw ServerError.serverNotFound("Could not find \(config.command) in PATH")
        }

        let process = Process()
        process.executableURL = URL(fileURLWithPath: path)
        process.arguments = config.args
        process.currentDirectoryURL = URL(fileURLWithPath: rootPath)

        var env = ProcessInfo.processInfo.environment
        for (key, value) in config.environment {
            env[key] = value
        }
        process.environment = env

        let stdinPipe = Pipe()
        let stdoutPipe = Pipe()
        let stderrPipe = Pipe()

        process.standardInput = stdinPipe
        process.standardOutput = stdoutPipe
        process.standardError = stderrPipe

        do {
            try process.run()
        } catch {
            throw ServerError.spawnFailed("Failed to spawn \(config.command): \(error)")
        }

        self.process = process

        let transport = LSPTransport(
            process: process,
            stdin: stdinPipe.fileHandleForWriting,
            stdout: stdoutPipe.fileHandleForReading,
            stderr: stderrPipe.fileHandleForReading
        )

        await transport.start { [weak self] notification in
            self?.handleNotification(notification)
        }

        self.transport = transport

        try await initialize()
    }

    /// Shutdown the language server (fire-and-forget)
    public func shutdown() {
        Task {
            await shutdownAsync()
        }
    }

    /// Shutdown the language server and wait for completion
    public func shutdownAsync() async {
        let (currentTransport, currentProcess) = prepareShutdown()
        guard currentTransport != nil || currentProcess != nil else { return }

        if let transport = currentTransport {
            _ = try? await transport.sendRequest("shutdown", params: EmptyParams())
            _ = try? await transport.sendNotification("exit", params: EmptyParams())
            await transport.stop()
        }
        currentProcess?.terminate()
    }

    private func prepareShutdown() -> (LSPTransport?, Process?) {
        stateQueue.sync {
            guard !isShutdown else {
                return (nil, nil)
            }
            isShutdown = true
            isInitialized = false
            let currentTransport = transport
            let currentProcess = process
            transport = nil
            process = nil
            return (currentTransport, currentProcess)
        }
    }

    // MARK: - VVLSPClient Protocol

    public var diagnosticsPublisher: AnyPublisher<DocumentDiagnostics, Never> {
        diagnosticsSubject.eraseToAnyPublisher()
    }

    public func completions(
        at position: VVTextPosition,
        in document: DocumentURI,
        triggerKind: VVCompletionTriggerKind,
        triggerCharacter: String?
    ) async throws -> [VVCompletionItem] {
        guard isInitialized, let transport = transport else {
            throw ServerError.notInitialized
        }

        let params = CompletionParams(
            textDocument: TextDocumentIdentifier(uri: document),
            position: Position(line: position.line, character: position.character),
            context: CompletionContext(
                triggerKind: CompletionTriggerKind(rawValue: triggerKind.rawValue) ?? .invoked,
                triggerCharacter: triggerCharacter
            )
        )

        let result = try await transport.sendRequest("textDocument/completion", params: params)
        return parseCompletions(result)
    }

    public func hover(
        at position: VVTextPosition,
        in document: DocumentURI
    ) async throws -> VVHoverInfo? {
        guard isInitialized, let transport = transport else {
            throw ServerError.notInitialized
        }

        let params = TextDocumentPositionParams(
            textDocument: TextDocumentIdentifier(uri: document),
            position: Position(line: position.line, character: position.character)
        )

        let result = try await transport.sendRequest("textDocument/hover", params: params)
        return parseHover(result)
    }

    public func signatureHelp(
        at position: VVTextPosition,
        in document: DocumentURI
    ) async throws -> VVSignatureHelp? {
        guard isInitialized, let transport = transport else {
            throw ServerError.notInitialized
        }

        let params = TextDocumentPositionParams(
            textDocument: TextDocumentIdentifier(uri: document),
            position: Position(line: position.line, character: position.character)
        )

        let result = try await transport.sendRequest("textDocument/signatureHelp", params: params)
        return parseSignatureHelp(result)
    }

    public func definition(
        at position: VVTextPosition,
        in document: DocumentURI
    ) async throws -> [VVLocation]? {
        guard isInitialized, let transport = transport else {
            throw ServerError.notInitialized
        }

        let params = TextDocumentPositionParams(
            textDocument: TextDocumentIdentifier(uri: document),
            position: Position(line: position.line, character: position.character)
        )

        let result = try await transport.sendRequest("textDocument/definition", params: params)
        return parseLocations(result)
    }

    public func diagnostics(for document: DocumentURI) async throws -> [VVDiagnostic] {
        // Most servers push diagnostics via notifications
        // This could request them explicitly if the server supports it
        return []
    }

    public func documentOpened(_ document: DocumentURI, text: String, language: String) async {
        guard let transport = transport else { return }

        let params = DidOpenTextDocumentParams(
            textDocument: TextDocumentItem(
                uri: document,
                languageId: language,
                version: 1,
                text: text
            )
        )

        try? await transport.sendNotification("textDocument/didOpen", params: params)
    }

    public func documentChanged(_ document: DocumentURI, changes: [VVTextChange]) async {
        guard let transport = transport else { return }

        let contentChanges = changes.map { change -> TextDocumentContentChangeEvent in
            if let range = change.range {
                return TextDocumentContentChangeEvent(
                    range: LSPRange(
                        start: Position(line: range.start.line, character: range.start.character),
                        end: Position(line: range.end.line, character: range.end.character)
                    ),
                    rangeLength: nil,
                    text: change.text
                )
            } else {
                return TextDocumentContentChangeEvent(range: nil, rangeLength: nil, text: change.text)
            }
        }

        let params = DidChangeTextDocumentParams(
            textDocument: VersionedTextDocumentIdentifier(uri: document, version: nil),
            contentChanges: contentChanges
        )

        try? await transport.sendNotification("textDocument/didChange", params: params)
    }

    public func documentClosed(_ document: DocumentURI) async {
        guard let transport = transport else { return }

        let params = DidCloseTextDocumentParams(
            textDocument: TextDocumentIdentifier(uri: document)
        )

        try? await transport.sendNotification("textDocument/didClose", params: params)
    }

    // MARK: - Private

    private func initialize() async throws {
        guard let transport = transport else {
            throw ServerError.notInitialized
        }

        let rootUri = URL(fileURLWithPath: rootPath).absoluteString

        let capabilities = ClientCapabilities(
            workspace: nil,
            textDocument: TextDocumentClientCapabilities(
                synchronization: nil,
                completion: CompletionClientCapabilities(
                    dynamicRegistration: false,
                    completionItem: CompletionClientCapabilities.CompletionItem(
                        snippetSupport: config.capabilities.completionSnippets,
                        commitCharactersSupport: true,
                        documentationFormat: [.markdown, .plaintext],
                        deprecatedSupport: true,
                        preselectSupport: true,
                        insertReplaceSupport: true,
                        resolveSupport: nil,
                        insertTextModeSupport: nil,
                        labelDetailsSupport: true
                    ),
                    completionItemKind: nil,
                    contextSupport: true,
                    insertTextMode: nil,
                    completionList: nil
                ),
                hover: HoverClientCapabilities(
                    dynamicRegistration: false,
                    contentFormat: config.capabilities.hoverMarkdown ? [.markdown, .plaintext] : [.plaintext]
                ),
                signatureHelp: SignatureHelpClientCapabilities(
                    dynamicRegistration: false,
                    signatureInformation: nil,
                    contextSupport: true
                ),
                declaration: nil,
                definition: DefinitionClientCapabilities(dynamicRegistration: false, linkSupport: true),
                typeDefinition: nil,
                implementation: nil,
                references: nil,
                documentHighlight: nil,
                documentSymbol: nil,
                codeAction: nil,
                codeLens: nil,
                documentLink: nil,
                colorProvider: nil,
                formatting: nil,
                rangeFormatting: nil,
                onTypeFormatting: nil,
                rename: nil,
                publishDiagnostics: PublishDiagnosticsClientCapabilities(
                    relatedInformation: config.capabilities.diagnosticRelatedInfo,
                    tagSupport: nil,
                    versionSupport: true,
                    codeDescriptionSupport: true,
                    dataSupport: true
                ),
                foldingRange: nil,
                selectionRange: nil,
                linkedEditingRange: nil,
                callHierarchy: nil,
                semanticTokens: nil,
                moniker: nil,
                inlayHint: nil,
                diagnostic: nil
            ),
            window: nil,
            general: nil,
            experimental: nil
        )

        let params = InitializeParams(
            processId: Int(ProcessInfo.processInfo.processIdentifier),
            locale: nil,
            rootPath: rootPath,
            rootUri: rootUri,
            initializationOptions: nil,
            capabilities: capabilities,
            trace: nil,
            workspaceFolders: [WorkspaceFolder(uri: rootUri, name: (rootPath as NSString).lastPathComponent)]
        )

        let result = try await transport.sendRequest("initialize", params: params)

        if let resultDict = result.dictionary,
           resultDict["capabilities"] != nil {
            // Parse server capabilities
            // For now, just mark as initialized
        }

        try await transport.sendNotification("initialized", params: EmptyParams())

        stateQueue.sync {
            isInitialized = true
        }
    }

    private func handleNotification(_ notification: ServerNotification) {
        switch notification.method {
        case "textDocument/publishDiagnostics":
            if let params = notification.params,
               let dict = params.dictionary,
               let uri = dict["uri"]?.string {
                let diagnostics = parseDiagnostics(dict["diagnostics"])
                diagnosticsSubject.send(DocumentDiagnostics(uri: uri, diagnostics: diagnostics))
            }

        case "window/logMessage", "window/showMessage":
            if let params = notification.params,
               let dict = params.dictionary,
               let message = dict["message"]?.string {
                print("[LSP \(config.name)] \(message)")
            }

        default:
            break
        }
    }

    private func findExecutable(_ name: String) -> String? {
        let paths = (ProcessInfo.processInfo.environment["PATH"] ?? "")
            .split(separator: ":")
            .map(String.init)

        for path in paths {
            let fullPath = (path as NSString).appendingPathComponent(name)
            if FileManager.default.isExecutableFile(atPath: fullPath) {
                return fullPath
            }
        }
        return nil
    }

    // MARK: - Response Parsing

    private func parseCompletions(_ result: LSPAny) -> [VVCompletionItem] {
        var items: [LSPAny] = []

        if let array = result.array {
            items = array
        } else if let dict = result.dictionary,
                  let itemsArray = dict["items"]?.array {
            items = itemsArray
        }

        return items.compactMap { item -> VVCompletionItem? in
            guard let dict = item.dictionary,
                  let label = dict["label"]?.string else {
                return nil
            }

            let kind = dict["kind"]?.int.flatMap { VVCompletionKind(rawValue: $0) } ?? .text
            let detail = dict["detail"]?.string
            let documentation = parseDocumentation(dict["documentation"])
            let insertText = dict["insertText"]?.string
            let filterText = dict["filterText"]?.string
            let sortText = dict["sortText"]?.string
            let preselect = dict["preselect"]?.bool ?? false
            let insertTextFormat = dict["insertTextFormat"]?.int == 2
                ? VVCompletionItem.InsertTextFormat.snippet
                : .plainText

            return VVCompletionItem(
                label: label,
                kind: kind,
                detail: detail,
                documentation: documentation,
                insertText: insertText,
                filterText: filterText,
                sortText: sortText,
                preselect: preselect,
                insertTextFormat: insertTextFormat
            )
        }
    }

    private func parseDocumentation(_ value: LSPAny?) -> String? {
        guard let value = value else { return nil }

        if let string = value.string {
            return string
        }

        if let dict = value.dictionary {
            return dict["value"]?.string
        }

        return nil
    }

    private func parseHover(_ result: LSPAny) -> VVHoverInfo? {
        guard let dict = result.dictionary else { return nil }

        let contents = dict["contents"]
        var markdown: String?

        if let string = contents?.string {
            markdown = string
        } else if let markupDict = contents?.dictionary {
            markdown = markupDict["value"]?.string
        } else if let array = contents?.array {
            markdown = array.compactMap { item -> String? in
                if let string = item.string { return string }
                if let dict = item.dictionary { return dict["value"]?.string }
                return nil
            }.joined(separator: "\n\n")
        }

        guard let content = markdown, !content.isEmpty else { return nil }

        var range: VVTextRange?
        if let rangeDict = dict["range"]?.dictionary {
            range = parseRange(rangeDict)
        }

        return VVHoverInfo(contents: content, range: range)
    }

    private func parseSignatureHelp(_ result: LSPAny) -> VVSignatureHelp? {
        guard let dict = result.dictionary,
              let signaturesArray = dict["signatures"]?.array,
              !signaturesArray.isEmpty else {
            return nil
        }

        let signatures = signaturesArray.compactMap { sig -> VVSignatureInfo? in
            guard let sigDict = sig.dictionary,
                  let label = sigDict["label"]?.string else {
                return nil
            }

            let documentation = parseDocumentation(sigDict["documentation"])
            let parameters = sigDict["parameters"]?.array?.compactMap { param -> VVParameterInfo? in
                guard let paramDict = param.dictionary,
                      let paramLabel = paramDict["label"]?.string else {
                    return nil
                }
                let paramDoc = parseDocumentation(paramDict["documentation"])
                return VVParameterInfo(label: paramLabel, documentation: paramDoc)
            } ?? []

            return VVSignatureInfo(label: label, documentation: documentation, parameters: parameters)
        }

        let activeSignature = dict["activeSignature"]?.int ?? 0
        let activeParameter = dict["activeParameter"]?.int ?? 0

        return VVSignatureHelp(
            signatures: signatures,
            activeSignature: activeSignature,
            activeParameter: activeParameter
        )
    }

    private func parseLocations(_ result: LSPAny) -> [VVLocation]? {
        if let dict = result.dictionary {
            if let location = parseLocation(dict) {
                return [location]
            }
        }

        if let array = result.array {
            let locations = array.compactMap { item -> VVLocation? in
                guard let dict = item.dictionary else { return nil }
                return parseLocation(dict)
            }
            return locations.isEmpty ? nil : locations
        }

        return nil
    }

    private func parseLocation(_ dict: [String: LSPAny]) -> VVLocation? {
        guard let uri = dict["uri"]?.string,
              let rangeDict = dict["range"]?.dictionary,
              let range = parseRange(rangeDict) else {
            return nil
        }
        return VVLocation(uri: uri, range: range)
    }

    private func parseRange(_ dict: [String: LSPAny]) -> VVTextRange? {
        guard let startDict = dict["start"]?.dictionary,
              let endDict = dict["end"]?.dictionary,
              let startLine = startDict["line"]?.int,
              let startChar = startDict["character"]?.int,
              let endLine = endDict["line"]?.int,
              let endChar = endDict["character"]?.int else {
            return nil
        }

        return VVTextRange(
            start: VVTextPosition(line: startLine, character: startChar),
            end: VVTextPosition(line: endLine, character: endChar)
        )
    }

    private func parseDiagnostics(_ value: LSPAny?) -> [VVDiagnostic] {
        guard let array = value?.array else { return [] }

        return array.compactMap { item -> VVDiagnostic? in
            guard let dict = item.dictionary,
                  let rangeDict = dict["range"]?.dictionary,
                  let range = parseRange(rangeDict),
                  let message = dict["message"]?.string else {
                return nil
            }

            let severity: VVDiagnosticSeverity
            switch dict["severity"]?.int {
            case 1: severity = .error
            case 2: severity = .warning
            case 3: severity = .information
            case 4: severity = .hint
            default: severity = .error
            }

            let source = dict["source"]?.string
            let code = dict["code"]?.string ?? dict["code"]?.int.map(String.init)

            return VVDiagnostic(
                range: range,
                severity: severity,
                code: code,
                source: source,
                message: message
            )
        }
    }
}

// MARK: - Helper Types

private struct EmptyParams: Codable {}

// MARK: - LSPAny Extensions

extension LSPAny {
    var dictionary: [String: LSPAny]? {
        if case .hash(let dict) = self {
            return dict
        }
        return nil
    }

    var array: [LSPAny]? {
        if case .array(let arr) = self {
            return arr
        }
        return nil
    }

    var string: String? {
        if case .string(let str) = self {
            return str
        }
        return nil
    }

    var int: Int? {
        if case .number(let value) = self {
            return Int(value)
        }
        return nil
    }

    var bool: Bool? {
        if case .bool(let value) = self {
            return value
        }
        return nil
    }
}
