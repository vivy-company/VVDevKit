import Foundation

/// Configuration for a language server
public struct LSPServerConfig {
    /// Unique identifier for this server
    public let name: String

    /// Command to launch the server
    public let command: String

    /// Arguments to pass to the command
    public let args: [String]

    /// Environment variables
    public let environment: [String: String]

    /// Language identifiers this server handles
    public let languages: [String]

    /// File extensions this server handles
    public let fileExtensions: [String]

    /// Root URI detection patterns (files/dirs that indicate project root)
    public let rootMarkers: [String]

    /// Initialization options to send to the server
    public let initializationOptions: [String: Any]?

    /// Server capabilities to request
    public let capabilities: LSPClientCapabilities

    public init(
        name: String,
        command: String,
        args: [String] = [],
        environment: [String: String] = [:],
        languages: [String],
        fileExtensions: [String],
        rootMarkers: [String] = [],
        initializationOptions: [String: Any]? = nil,
        capabilities: LSPClientCapabilities = .default
    ) {
        self.name = name
        self.command = command
        self.args = args
        self.environment = environment
        self.languages = languages
        self.fileExtensions = fileExtensions
        self.rootMarkers = rootMarkers
        self.initializationOptions = initializationOptions
        self.capabilities = capabilities
    }
}

/// Client capabilities to advertise to the server
public struct LSPClientCapabilities: Sendable {
    public let completionSnippets: Bool
    public let hoverMarkdown: Bool
    public let signatureHelpMarkdown: Bool
    public let diagnosticRelatedInfo: Bool

    public static let `default` = LSPClientCapabilities(
        completionSnippets: true,
        hoverMarkdown: true,
        signatureHelpMarkdown: true,
        diagnosticRelatedInfo: true
    )

    public init(
        completionSnippets: Bool,
        hoverMarkdown: Bool,
        signatureHelpMarkdown: Bool,
        diagnosticRelatedInfo: Bool
    ) {
        self.completionSnippets = completionSnippets
        self.hoverMarkdown = hoverMarkdown
        self.signatureHelpMarkdown = signatureHelpMarkdown
        self.diagnosticRelatedInfo = diagnosticRelatedInfo
    }
}

// MARK: - Built-in Server Configurations

extension LSPServerConfig {
    // MARK: Swift

    /// SourceKit-LSP for Swift
    public static let sourceKitLSP = LSPServerConfig(
        name: "sourcekit-lsp",
        command: "sourcekit-lsp",
        args: [],
        languages: ["swift"],
        fileExtensions: ["swift"],
        rootMarkers: ["Package.swift", ".git", "*.xcodeproj", "*.xcworkspace"]
    )

    // MARK: Rust

    /// rust-analyzer for Rust
    public static let rustAnalyzer = LSPServerConfig(
        name: "rust-analyzer",
        command: "rust-analyzer",
        args: [],
        languages: ["rust"],
        fileExtensions: ["rs"],
        rootMarkers: ["Cargo.toml", ".git"]
    )

    // MARK: JavaScript/TypeScript

    /// TypeScript language server
    public static let typescriptLanguageServer = LSPServerConfig(
        name: "typescript-language-server",
        command: "typescript-language-server",
        args: ["--stdio"],
        languages: ["typescript", "javascript", "tsx", "jsx"],
        fileExtensions: ["ts", "tsx", "js", "jsx", "mjs", "cjs"],
        rootMarkers: ["tsconfig.json", "jsconfig.json", "package.json", ".git"]
    )

    // MARK: Python

    /// Pyright for Python
    public static let pyright = LSPServerConfig(
        name: "pyright",
        command: "pyright-langserver",
        args: ["--stdio"],
        languages: ["python"],
        fileExtensions: ["py", "pyi", "pyw"],
        rootMarkers: ["pyproject.toml", "setup.py", "requirements.txt", ".git"]
    )

    /// Python LSP Server (pylsp)
    public static let pylsp = LSPServerConfig(
        name: "pylsp",
        command: "pylsp",
        args: [],
        languages: ["python"],
        fileExtensions: ["py", "pyi", "pyw"],
        rootMarkers: ["pyproject.toml", "setup.py", "requirements.txt", ".git"]
    )

    // MARK: Go

    /// gopls for Go
    public static let gopls = LSPServerConfig(
        name: "gopls",
        command: "gopls",
        args: [],
        languages: ["go"],
        fileExtensions: ["go"],
        rootMarkers: ["go.mod", "go.work", ".git"]
    )

    // MARK: C/C++

    /// clangd for C/C++
    public static let clangd = LSPServerConfig(
        name: "clangd",
        command: "clangd",
        args: ["--background-index"],
        languages: ["c", "cpp", "objc", "objcpp"],
        fileExtensions: ["c", "h", "cpp", "hpp", "cc", "hh", "cxx", "hxx", "m", "mm"],
        rootMarkers: ["compile_commands.json", ".clangd", "CMakeLists.txt", ".git"]
    )

    // MARK: Java

    /// Eclipse JDT Language Server for Java
    public static let jdtls = LSPServerConfig(
        name: "jdtls",
        command: "jdtls",
        args: [],
        languages: ["java"],
        fileExtensions: ["java"],
        rootMarkers: ["pom.xml", "build.gradle", "build.gradle.kts", ".git"]
    )

    // MARK: Kotlin

    /// Kotlin Language Server
    public static let kotlinLanguageServer = LSPServerConfig(
        name: "kotlin-language-server",
        command: "kotlin-language-server",
        args: [],
        languages: ["kotlin"],
        fileExtensions: ["kt", "kts"],
        rootMarkers: ["build.gradle", "build.gradle.kts", "pom.xml", ".git"]
    )

    // MARK: Ruby

    /// Solargraph for Ruby
    public static let solargraph = LSPServerConfig(
        name: "solargraph",
        command: "solargraph",
        args: ["stdio"],
        languages: ["ruby"],
        fileExtensions: ["rb", "rake", "gemspec"],
        rootMarkers: ["Gemfile", ".git"]
    )

    // MARK: Lua

    /// lua-language-server
    public static let luaLanguageServer = LSPServerConfig(
        name: "lua-language-server",
        command: "lua-language-server",
        args: [],
        languages: ["lua"],
        fileExtensions: ["lua"],
        rootMarkers: [".luarc.json", ".luarc.jsonc", ".git"]
    )

    // MARK: Zig

    /// ZLS for Zig
    public static let zls = LSPServerConfig(
        name: "zls",
        command: "zls",
        args: [],
        languages: ["zig"],
        fileExtensions: ["zig"],
        rootMarkers: ["build.zig", ".git"]
    )

    // MARK: Elixir

    /// ElixirLS
    public static let elixirLS = LSPServerConfig(
        name: "elixir-ls",
        command: "elixir-ls",
        args: [],
        languages: ["elixir"],
        fileExtensions: ["ex", "exs"],
        rootMarkers: ["mix.exs", ".git"]
    )

    // MARK: Haskell

    /// Haskell Language Server
    public static let hls = LSPServerConfig(
        name: "haskell-language-server",
        command: "haskell-language-server-wrapper",
        args: ["--lsp"],
        languages: ["haskell"],
        fileExtensions: ["hs", "lhs"],
        rootMarkers: ["*.cabal", "stack.yaml", "cabal.project", ".git"]
    )

    // MARK: OCaml

    /// OCaml LSP
    public static let ocamlLSP = LSPServerConfig(
        name: "ocamllsp",
        command: "ocamllsp",
        args: [],
        languages: ["ocaml"],
        fileExtensions: ["ml", "mli"],
        rootMarkers: ["dune-project", ".git"]
    )

    // MARK: CSS/SCSS/LESS

    /// CSS Language Server
    public static let cssLanguageServer = LSPServerConfig(
        name: "vscode-css-language-server",
        command: "vscode-css-language-server",
        args: ["--stdio"],
        languages: ["css", "scss", "less"],
        fileExtensions: ["css", "scss", "less"],
        rootMarkers: ["package.json", ".git"]
    )

    // MARK: HTML

    /// HTML Language Server
    public static let htmlLanguageServer = LSPServerConfig(
        name: "vscode-html-language-server",
        command: "vscode-html-language-server",
        args: ["--stdio"],
        languages: ["html"],
        fileExtensions: ["html", "htm"],
        rootMarkers: ["package.json", ".git"]
    )

    // MARK: JSON

    /// JSON Language Server
    public static let jsonLanguageServer = LSPServerConfig(
        name: "vscode-json-language-server",
        command: "vscode-json-language-server",
        args: ["--stdio"],
        languages: ["json", "jsonc"],
        fileExtensions: ["json", "jsonc"],
        rootMarkers: [".git"]
    )

    // MARK: YAML

    /// YAML Language Server
    public static let yamlLanguageServer = LSPServerConfig(
        name: "yaml-language-server",
        command: "yaml-language-server",
        args: ["--stdio"],
        languages: ["yaml"],
        fileExtensions: ["yaml", "yml"],
        rootMarkers: [".git"]
    )

    // MARK: Markdown

    /// Marksman for Markdown
    public static let marksman = LSPServerConfig(
        name: "marksman",
        command: "marksman",
        args: ["server"],
        languages: ["markdown"],
        fileExtensions: ["md", "markdown"],
        rootMarkers: [".marksman.toml", ".git"]
    )

    // MARK: TOML

    /// Taplo for TOML
    public static let taplo = LSPServerConfig(
        name: "taplo",
        command: "taplo",
        args: ["lsp", "stdio"],
        languages: ["toml"],
        fileExtensions: ["toml"],
        rootMarkers: [".git"]
    )

    // MARK: Bash/Shell

    /// Bash Language Server
    public static let bashLanguageServer = LSPServerConfig(
        name: "bash-language-server",
        command: "bash-language-server",
        args: ["start"],
        languages: ["bash", "sh"],
        fileExtensions: ["sh", "bash", "zsh"],
        rootMarkers: [".git"]
    )

    // MARK: Docker

    /// Dockerfile Language Server
    public static let dockerLanguageServer = LSPServerConfig(
        name: "docker-langserver",
        command: "docker-langserver",
        args: ["--stdio"],
        languages: ["dockerfile"],
        fileExtensions: ["dockerfile", "Dockerfile"],
        rootMarkers: ["Dockerfile", "docker-compose.yml", ".git"]
    )

    // MARK: SQL

    /// SQL Language Server
    public static let sqls = LSPServerConfig(
        name: "sqls",
        command: "sqls",
        args: [],
        languages: ["sql"],
        fileExtensions: ["sql"],
        rootMarkers: [".git"]
    )

    // MARK: GraphQL

    /// GraphQL Language Server
    public static let graphqlLanguageServer = LSPServerConfig(
        name: "graphql-lsp",
        command: "graphql-lsp",
        args: ["server", "-m", "stream"],
        languages: ["graphql"],
        fileExtensions: ["graphql", "gql"],
        rootMarkers: [".graphqlrc", "graphql.config.js", ".git"]
    )

    // MARK: Terraform/HCL

    /// Terraform Language Server
    public static let terraformLS = LSPServerConfig(
        name: "terraform-ls",
        command: "terraform-ls",
        args: ["serve"],
        languages: ["terraform", "hcl"],
        fileExtensions: ["tf", "tfvars", "hcl"],
        rootMarkers: [".terraform", "*.tf", ".git"]
    )

    // MARK: Nix

    /// nil for Nix
    public static let nilNix = LSPServerConfig(
        name: "nil",
        command: "nil",
        args: [],
        languages: ["nix"],
        fileExtensions: ["nix"],
        rootMarkers: ["flake.nix", "default.nix", ".git"]
    )

    // MARK: Dart/Flutter

    /// Dart Analysis Server
    public static let dartAnalysisServer = LSPServerConfig(
        name: "dart",
        command: "dart",
        args: ["language-server", "--protocol=lsp"],
        languages: ["dart"],
        fileExtensions: ["dart"],
        rootMarkers: ["pubspec.yaml", ".git"]
    )

    // MARK: PHP

    /// Intelephense for PHP
    public static let intelephense = LSPServerConfig(
        name: "intelephense",
        command: "intelephense",
        args: ["--stdio"],
        languages: ["php"],
        fileExtensions: ["php", "phtml"],
        rootMarkers: ["composer.json", ".git"]
    )

    // MARK: Vue

    /// Vue Language Server (Volar)
    public static let volar = LSPServerConfig(
        name: "vue-language-server",
        command: "vue-language-server",
        args: ["--stdio"],
        languages: ["vue"],
        fileExtensions: ["vue"],
        rootMarkers: ["vite.config.js", "vue.config.js", "package.json", ".git"]
    )

    // MARK: Svelte

    /// Svelte Language Server
    public static let svelteLanguageServer = LSPServerConfig(
        name: "svelte-language-server",
        command: "svelteserver",
        args: ["--stdio"],
        languages: ["svelte"],
        fileExtensions: ["svelte"],
        rootMarkers: ["svelte.config.js", "package.json", ".git"]
    )

    // MARK: All Built-in Servers

    /// All built-in server configurations
    public static let allBuiltIn: [LSPServerConfig] = [
        .sourceKitLSP,
        .rustAnalyzer,
        .typescriptLanguageServer,
        .pyright,
        .gopls,
        .clangd,
        .jdtls,
        .kotlinLanguageServer,
        .solargraph,
        .luaLanguageServer,
        .zls,
        .elixirLS,
        .hls,
        .ocamlLSP,
        .cssLanguageServer,
        .htmlLanguageServer,
        .jsonLanguageServer,
        .yamlLanguageServer,
        .marksman,
        .taplo,
        .bashLanguageServer,
        .dockerLanguageServer,
        .sqls,
        .graphqlLanguageServer,
        .terraformLS,
        .nilNix,
        .dartAnalysisServer,
        .intelephense,
        .volar,
        .svelteLanguageServer,
    ]
}

// MARK: - Server Registry

/// Registry for language server configurations
public final class LSPServerRegistry: @unchecked Sendable {
    public static let shared = LSPServerRegistry()

    private var configs: [String: LSPServerConfig] = [:]
    private var byLanguage: [String: LSPServerConfig] = [:]
    private var byExtension: [String: LSPServerConfig] = [:]
    private let lock = NSLock()

    private init() {
        registerBuiltInServers()
    }

    private func registerBuiltInServers() {
        for config in LSPServerConfig.allBuiltIn {
            register(config)
        }
    }

    /// Register a server configuration
    public func register(_ config: LSPServerConfig) {
        lock.lock()
        defer { lock.unlock() }

        configs[config.name] = config

        for lang in config.languages {
            byLanguage[lang] = config
        }

        for ext in config.fileExtensions {
            byExtension[ext.lowercased()] = config
        }
    }

    /// Get server config by name
    public func server(named name: String) -> LSPServerConfig? {
        lock.lock()
        defer { lock.unlock() }
        return configs[name]
    }

    /// Get server config for a language identifier
    public func server(forLanguage language: String) -> LSPServerConfig? {
        lock.lock()
        defer { lock.unlock() }
        return byLanguage[language]
    }

    /// Get server config for a file extension
    public func server(forExtension ext: String) -> LSPServerConfig? {
        lock.lock()
        defer { lock.unlock() }
        return byExtension[ext.lowercased()]
    }

    /// Get server config for a file path
    public func server(forPath path: String) -> LSPServerConfig? {
        let ext = (path as NSString).pathExtension
        return server(forExtension: ext)
    }

    /// All registered server names
    public var registeredServers: [String] {
        lock.lock()
        defer { lock.unlock() }
        return Array(configs.keys).sorted()
    }
}
