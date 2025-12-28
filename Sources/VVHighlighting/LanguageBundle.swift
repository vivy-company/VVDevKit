import Foundation
import SwiftTreeSitter

// MARK: - Language Bundle Protocol

/// Protocol for bundled language grammars
public protocol LanguageBundle {
    /// Unique identifier (e.g., "swift", "rust", "python")
    static var identifier: String { get }

    /// Display name (e.g., "Swift", "Rust", "Python")
    static var displayName: String { get }

    /// File extensions this language handles (e.g., ["swift"], ["rs"], ["py", "pyw"])
    static var fileExtensions: [String] { get }

    /// The tree-sitter language pointer
    static var language: Language { get }

    /// Highlights query (S-expression)
    static var highlightsQuery: String { get }

    /// Optional injections query for embedded languages
    static var injectionsQuery: String? { get }

    /// Optional locals query for scope tracking
    static var localsQuery: String? { get }
}

extension LanguageBundle {
    public static var injectionsQuery: String? { nil }
    public static var localsQuery: String? { nil }

    /// Create a LanguageConfiguration from this bundle
    public static func configuration() throws -> LanguageConfiguration {
        try LanguageConfiguration(
            identifier: identifier,
            displayName: displayName,
            language: language,
            highlightQuery: highlightsQuery,
            injectionQuery: injectionsQuery,
            localsQuery: localsQuery
        )
    }
}

// MARK: - Language Registry

/// Central registry for all available languages with lazy loading
public final class LanguageRegistry: @unchecked Sendable {
    public static let shared = LanguageRegistry()

    /// Cached loaded configurations
    private var loadedConfigs: [String: LanguageConfiguration] = [:]
    /// Extension to language identifier mapping (lightweight, no grammar loading)
    private var extensionToId: [String: String] = [:]
    /// All known language identifiers with their extensions
    private var knownLanguages: [(id: String, extensions: [String])] = []
    private let lock = NSLock()

    private init() {
        registerExtensionMappings()
    }

    /// Only register extension-to-identifier mappings (no grammar loading)
    private func registerExtensionMappings() {
        // Swift is special - register its extensions
        knownLanguages.append(("swift", ["swift"]))
        for ext in ["swift"] {
            extensionToId[ext.lowercased()] = "swift"
        }

        // All bundled languages - just store mappings, don't load grammars
        let languages: [(id: String, extensions: [String])] = [
            ("ada", ["ada", "adb", "ads"]),
            ("adl", ["adl"]),
            ("agda", ["agda"]),
            ("alloy", ["als"]),
            ("amber", ["ab"]),
            ("awk", ["awk", "gawk", "mawk"]),
            ("bash", ["sh", "bash", "zsh", "ksh"]),
            ("basic", ["bas", "vb", "vbs"]),
            ("bass", ["bass"]),
            ("beancount", ["beancount"]),
            ("bibtex", ["bib"]),
            ("bitbake", ["bb", "bbappend", "bbclass"]),
            ("blueprint", ["blp"]),
            ("bovex", ["bovex"]),
            ("c", ["c", "h"]),
            ("cpp", ["cpp", "cc", "cxx", "hpp", "hh", "hxx"]),
            ("caddyfile", ["Caddyfile"]),
            ("cairo", ["cairo"]),
            ("capnp", ["capnp"]),
            ("cel", ["cel"]),
            ("chuck", ["ck"]),
            ("clarity", ["clar"]),
            ("clojure", ["clj", "cljs", "cljc", "edn"]),
            ("cpon", ["cpon"]),
            ("css", ["css"]),
            ("csv", ["csv", "tsv"]),
            ("cue", ["cue"]),
            ("cylc", ["cylc"]),
            ("cython", ["pyx", "pxd", "pxi"]),
            ("d", ["d", "di"]),
            ("dart", ["dart"]),
            ("dbml", ["dbml"]),
            ("debian", ["control"]),
            ("devicetree", ["dts", "dtsi"]),
            ("dhall", ["dhall"]),
            ("diff", ["diff", "patch"]),
            ("dockerfile", ["Dockerfile", "dockerfile"]),
            ("dot", ["dot", "gv"]),
            ("doxyfile", ["Doxyfile"]),
            ("dtd", ["dtd"]),
            ("dunstrc", ["dunstrc"]),
            ("earthfile", ["Earthfile"]),
            ("edoc", ["edoc"]),
            ("eex", ["eex"]),
            ("eiffel", ["e"]),
            ("elisp", ["el", "elisp"]),
            ("elixir", ["ex", "exs"]),
            ("elm", ["elm"]),
            ("elvish", ["elv"]),
            ("embeddedtemplate", ["erb", "ejs"]),
            ("erlang", ["erl", "hrl"]),
            ("fennel", ["fnl"]),
            ("fga", ["fga"]),
            ("fidl", ["fidl"]),
            ("fish", ["fish"]),
            ("flatbuffers", ["fbs"]),
            ("forth", ["fs", "fth", "4th"]),
            ("freebasic", ["bas", "bi"]),
            ("gas", ["s", "S", "asm"]),
            ("gdscript", ["gd"]),
            ("gemini", ["gmi", "gemini"]),
            ("gherkin", ["feature"]),
            ("ghostty", ["ghostty"]),
            ("gitattributes", [".gitattributes"]),
            ("gitcommit", ["COMMIT_EDITMSG"]),
            ("gitconfig", [".gitconfig", ".gitmodules"]),
            ("gitignore", [".gitignore", ".dockerignore"]),
            ("gitrebase", ["git-rebase-todo"]),
            ("gleam", ["gleam"]),
            ("glimmer", ["hbs", "handlebars"]),
            ("glsl", ["glsl", "vert", "frag", "geom", "comp"]),
            ("gn", ["gn", "gni"]),
            ("go", ["go"]),
            ("godotresource", ["tres", "tscn"]),
            ("gomod", ["go.mod"]),
            ("gotmpl", ["tmpl", "gotmpl"]),
            ("gowork", ["go.work"]),
            ("gpr", ["gpr"]),
            ("graphql", ["graphql", "gql"]),
            ("gren", ["gren"]),
            ("groovy", ["groovy", "gradle"]),
            ("hare", ["ha"]),
            ("haskellliterate", ["lhs"]),
            ("haskellpersistent", ["persistentmodels"]),
            ("hcl", ["hcl", "tf", "tfvars"]),
            ("hdl", ["hdl"]),
            ("heex", ["heex"]),
            ("hocon", ["conf"]),
            ("hoon", ["hoon"]),
            ("hosts", ["hosts"]),
            ("html", ["html", "htm"]),
            ("htmldjango", ["djhtml"]),
            ("hurl", ["hurl"]),
            ("hyprlang", ["hl"]),
            ("iex", ["iex"]),
            ("ini", ["ini", "cfg", "desktop"]),
            ("ink", ["ink"]),
            ("inko", ["inko"]),
            ("janetsimple", ["janet"]),
            ("java", ["java"]),
            ("javascript", ["js", "mjs", "cjs", "jsx"]),
            ("jinja2", ["j2", "jinja", "jinja2"]),
            ("jjdescription", ["jjdescription"]),
            ("jjrevset", ["jjrevset"]),
            ("jjtemplate", ["jjtemplate"]),
            ("jq", ["jq"]),
            ("jsdoc", ["jsdoc"]),
            ("json", ["json"]),
            ("json5", ["json5"]),
            ("jsonnet", ["jsonnet", "libsonnet"]),
            ("julia", ["jl"]),
            ("just", ["just", "justfile"]),
            ("kcl", ["kcl"]),
            ("kconfig", ["Kconfig"]),
            ("koka", ["kk"]),
            ("kotlin", ["kt", "kts"]),
            ("koto", ["koto"]),
            ("ld", ["ld", "lds"]),
            ("ldif", ["ldif"]),
            ("lean", ["lean"]),
            ("ledger", ["ledger", "journal"]),
            ("llvm", ["ll"]),
            ("llvmmir", ["mir"]),
            ("log", ["log"]),
            ("lpf", ["lpf"]),
            ("luap", ["lua"]),
            ("make", ["mk", "Makefile", "makefile", "GNUmakefile"]),
            ("markdoc", ["markdoc"]),
            ("markdown", ["md", "markdown", "mkd"]),
            ("markdowninline", []),
            ("matlab", ["m", "mat"]),
            ("mermaid", ["mmd", "mermaid"]),
            ("meson", ["meson.build"]),
            ("mojo", ["mojo", "🔥"]),
            ("move", ["move"]),
            ("nasm", ["nasm", "asm"]),
            ("nearley", ["ne"]),
            ("nginx", ["nginx.conf"]),
            ("nickel", ["ncl"]),
            ("nix", ["nix"]),
            ("odin", ["odin"]),
            ("ohm", ["ohm"]),
            ("opencl", ["cl", "opencl"]),
            ("openscad", ["scad"]),
            ("org", ["org"]),
            ("pascal", ["pas", "pp", "inc", "dpr"]),
            ("passwd", ["passwd"]),
            ("pem", ["pem", "crt", "key"]),
            ("pest", ["pest"]),
            ("pkl", ["pkl"]),
            ("po", ["po", "pot"]),
            ("ponylang", ["pony"]),
            ("powershell", ["ps1", "psm1", "psd1"]),
            ("prisma", ["prisma"]),
            ("properties", ["properties"]),
            ("proto", ["proto"]),
            ("prql", ["prql"]),
            ("pug", ["pug", "jade"]),
            ("python", ["py", "pyw", "pyi"]),
            ("ql", ["ql", "qll"]),
            ("query", ["scm"]),
            ("regex", ["regex"]),
            ("rego", ["rego"]),
            ("requirements", ["requirements.txt", "constraints.txt"]),
            ("rescript", ["res", "resi"]),
            ("robot", ["robot"]),
            ("robots", ["robots.txt"]),
            ("ron", ["ron"]),
            ("rpmspec", ["spec"]),
            ("rshtml", ["rshtml"]),
            ("rust", ["rs"]),
            ("rustformatargs", []),
            ("scfg", ["scfg"]),
            ("scheme", ["scm", "ss", "rkt"]),
            ("scss", ["scss"]),
            ("slint", ["slint"]),
            ("slisp", ["slisp"]),
            ("smali", ["smali"]),
            ("smithy", ["smithy"]),
            ("sml", ["sml", "sig"]),
            ("snakemake", ["smk", "Snakefile"]),
            ("solidity", ["sol"]),
            ("sourcepawn", ["sp", "inc"]),
            ("spade", ["spade"]),
            ("spicedb", ["zed"]),
            ("sql", ["sql"]),
            ("sshclientconfig", ["ssh_config"]),
            ("strace", ["strace"]),
            ("strictdoc", ["sdoc"]),
            ("supercollider", ["sc", "scd"]),
            ("sway", ["sw"]),
            ("systemverilog", ["sv", "svh"]),
            ("t32", ["t32", "cmm"]),
            ("tablegen", ["td"]),
            ("tact", ["tact"]),
            ("task", ["task"]),
            ("tcl", ["tcl", "tk"]),
            ("templ", ["templ"]),
            ("textproto", ["textproto", "pbtxt"]),
            ("thrift", ["thrift"]),
            ("todotxt", ["todo.txt"]),
            ("toml", ["toml"]),
            ("tsx", ["tsx"]),
            ("twig", ["twig"]),
            ("typescript", ["ts", "mts", "cts"]),
            ("typespec", ["tsp"]),
            ("ungrammar", ["ungram"]),
            ("uxntal", ["tal"]),
            ("vala", ["vala", "vapi"]),
            ("vento", ["vento"]),
            ("verilog", ["v", "vh"]),
            ("vhs", ["tape"]),
            ("wesl", ["wesl"]),
            ("wgsl", ["wgsl"]),
            ("wit", ["wit"]),
            ("wren", ["wren"]),
            ("xit", ["xit"]),
            ("xml", ["xml", "xsd", "xsl", "xslt", "svg", "xhtml"]),
            ("xtc", ["xtc"]),
            ("yaml", ["yaml", "yml"]),
            ("yara", ["yar", "yara"]),
            ("yuck", ["yuck"]),
            ("zig", ["zig"]),
        ]

        for lang in languages {
            knownLanguages.append(lang)
            for ext in lang.extensions {
                extensionToId[ext.lowercased()] = lang.id
            }
        }
    }

    /// Lazily load and cache a language configuration
    private func loadConfiguration(for identifier: String) -> LanguageConfiguration? {
        // Check cache first (already under lock)
        if let cached = loadedConfigs[identifier] {
            return cached
        }

        // Load the configuration
        let config: LanguageConfiguration?
        if identifier == "swift" {
            config = try? SwiftLanguage.configuration()
        } else {
            config = Self.configuration(for: identifier)
        }

        if let config = config {
            loadedConfigs[identifier] = config
        }
        return config
    }

    /// Register a language configuration (for custom languages)
    public func register(_ config: LanguageConfiguration, extensions: [String]) {
        lock.lock()
        defer { lock.unlock() }

        loadedConfigs[config.identifier] = config
        knownLanguages.append((config.identifier, extensions))
        for ext in extensions {
            extensionToId[ext.lowercased()] = config.identifier
        }
    }

    /// Register a language bundle type
    public func register<L: LanguageBundle>(_ bundle: L.Type) throws {
        let config = try bundle.configuration()
        register(config, extensions: bundle.fileExtensions)
    }

    /// Get language by identifier (lazy loading)
    public func language(for identifier: String) -> LanguageConfiguration? {
        lock.lock()
        defer { lock.unlock() }
        return loadConfiguration(for: identifier)
    }

    /// Get language by file extension (lazy loading)
    public func language(forExtension ext: String) -> LanguageConfiguration? {
        lock.lock()
        defer { lock.unlock() }

        guard let identifier = extensionToId[ext.lowercased()] else {
            return nil
        }
        return loadConfiguration(for: identifier)
    }

    /// Get language for a file path (lazy loading)
    public func language(forPath path: String) -> LanguageConfiguration? {
        let ext = (path as NSString).pathExtension
        return language(forExtension: ext)
    }

    /// All known language identifiers (doesn't load grammars)
    public var registeredLanguages: [String] {
        lock.lock()
        defer { lock.unlock() }
        return knownLanguages.map { $0.id }.sorted()
    }

    /// All supported file extensions (doesn't load grammars)
    public var supportedExtensions: [String] {
        lock.lock()
        defer { lock.unlock() }
        return Array(extensionToId.keys).sorted()
    }

    /// Number of currently loaded language configurations
    public var loadedLanguageCount: Int {
        lock.lock()
        defer { lock.unlock() }
        return loadedConfigs.count
    }
}
