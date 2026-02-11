import Foundation
import SwiftTreeSitter

// MARK: - Dynamic Grammar Loader
// Loads tree-sitter grammars on-demand using dlopen/dlsym
// This avoids loading all 200+ grammars into memory at startup

public final class DynamicGrammarLoader {
    public static let shared = DynamicGrammarLoader()

    private var loadedHandles: [String: UnsafeMutableRawPointer] = [:]
    private var loadedLanguages: [String: Language] = [:]
    private let lock = NSLock()

    private init() {}

    deinit {
        // Close all loaded libraries
        for handle in loadedHandles.values {
            dlclose(handle)
        }
    }

    /// Load a tree-sitter language dynamically
    /// - Parameter identifier: Language identifier (e.g., "swift", "python")
    /// - Returns: The Language if successfully loaded, nil otherwise
    public func loadLanguage(_ identifier: String) -> Language? {
        lock.lock()
        defer { lock.unlock() }

        // Return cached if already loaded
        if let cached = loadedLanguages[identifier] {
            return cached
        }

        // Get the C function name for this language
        guard let functionName = grammarFunctionName(for: identifier) else {
            return nil
        }

        // Build the dylib name from identifier
        // SPM names them: libTreeSitterSwift.dylib, libTreeSitterPython.dylib, etc.
        let dylibName = dylibNameForIdentifier(identifier)

        // Search paths for grammar dylibs
        var searchPaths: [String] = []

        // 1. App bundle Frameworks folder (for bundled apps)
        if let frameworksPath = Bundle.main.privateFrameworksPath {
            searchPaths.append("\(frameworksPath)/\(dylibName)")
        }

        // 2. App bundle PlugIns/Grammars folder
        if let pluginsPath = Bundle.main.builtInPlugInsPath {
            searchPaths.append("\(pluginsPath)/Grammars/\(dylibName)")
        }

        // 3. VVDevKit package build directory (for development)
        // Find VVHighlighting module location and navigate to .build folder
        #if SWIFT_PACKAGE
        let moduleBundle = Bundle.module
        if let modulePath = moduleBundle.bundlePath.components(separatedBy: ".build").first {
            // We're in: /path/to/VVDevKit/.build/...
            // Navigate to: /path/to/VVDevKit/.build/debug/ or release/
            let vvdevkitPath = modulePath.hasSuffix("/") ? String(modulePath.dropLast()) : modulePath
            searchPaths.append("\(vvdevkitPath)/.build/debug/\(dylibName)")
            searchPaths.append("\(vvdevkitPath)/.build/release/\(dylibName)")
        }
        #endif

        // 4. Relative to executable (for CLI tools)
        searchPaths.append("@executable_path/../lib/\(dylibName)")
        searchPaths.append("@executable_path/../Frameworks/\(dylibName)")

        // 5. Common development paths
        let homeDir = FileManager.default.homeDirectoryForCurrentUser.path
        searchPaths.append("\(homeDir)/vivy/experiments/swift-code-editor/VVDevKit/.build/debug/\(dylibName)")
        searchPaths.append("\(homeDir)/vivy/experiments/swift-code-editor/VVDevKit/.build/release/\(dylibName)")

        // 6. Current working directory
        searchPaths.append("./\(dylibName)")
        searchPaths.append(".build/debug/\(dylibName)")
        searchPaths.append(".build/release/\(dylibName)")

        // Try each path
        for path in searchPaths {
            if let handle = dlopen(path, RTLD_LAZY) {
                loadedHandles[identifier] = handle

                if let ptr = dlsym(handle, functionName) {
                    let langFunc = unsafeBitCast(ptr, to: (@convention(c) () -> OpaquePointer).self)
                    let language = Language(language: langFunc())
                    loadedLanguages[identifier] = language
                    return language
                }
                dlclose(handle)
            }
        }

        return nil
    }

    /// Get the dylib filename for a language identifier
    private func dylibNameForIdentifier(_ identifier: String) -> String {
        // Map identifier to SPM product name - all 220+ grammars
        let productNames: [String: String] = [
            "ada": "TreeSitterAda",
            "adl": "TreeSitterAdl",
            "agda": "TreeSitterAgda",
            "alloy": "TreeSitterAlloy",
            "amber": "TreeSitterAmber",
            "awk": "TreeSitterAwk",
            "bash": "TreeSitterBash",
            "basic": "TreeSitterBasic",
            "bass": "TreeSitterBass",
            "beancount": "TreeSitterBeancount",
            "bibtex": "TreeSitterBibtex",
            "bitbake": "TreeSitterBitbake",
            "blueprint": "TreeSitterBlueprint",
            "bovex": "TreeSitterBovex",
            "c": "TreeSitterC",
            "cpp": "TreeSitterCpp",
            "caddyfile": "TreeSitterCaddyfile",
            "cairo": "TreeSitterCairo",
            "capnp": "TreeSitterCapnp",
            "cel": "TreeSitterCel",
            "chuck": "TreeSitterChuck",
            "clarity": "TreeSitterClarity",
            "clojure": "TreeSitterClojure",
            "cpon": "TreeSitterCpon",
            "css": "TreeSitterCss",
            "csv": "TreeSitterCsv",
            "cue": "TreeSitterCue",
            "cylc": "TreeSitterCylc",
            "cython": "TreeSitterCython",
            "d": "TreeSitterD",
            "dart": "TreeSitterDart",
            "dbml": "TreeSitterDbml",
            "debian": "TreeSitterDebian",
            "devicetree": "TreeSitterDevicetree",
            "dhall": "TreeSitterDhall",
            "diff": "TreeSitterDiff",
            "dockerfile": "TreeSitterDockerfile",
            "dot": "TreeSitterDot",
            "doxyfile": "TreeSitterDoxyfile",
            "dtd": "TreeSitterDtd",
            "dunstrc": "TreeSitterDunstrc",
            "earthfile": "TreeSitterEarthfile",
            "edoc": "TreeSitterEdoc",
            "eex": "TreeSitterEex",
            "eiffel": "TreeSitterEiffel",
            "elisp": "TreeSitterElisp",
            "elixir": "TreeSitterElixir",
            "elm": "TreeSitterElm",
            "elvish": "TreeSitterElvish",
            "embedded-template": "TreeSitterEmbeddedTemplate",
            "erlang": "TreeSitterErlang",
            "fennel": "TreeSitterFennel",
            "fga": "TreeSitterFga",
            "fidl": "TreeSitterFidl",
            "fish": "TreeSitterFish",
            "flatbuffers": "TreeSitterFlatbuffers",
            "forth": "TreeSitterForth",
            "freebasic": "TreeSitterFreebasic",
            "gas": "TreeSitterGas",
            "gdscript": "TreeSitterGdscript",
            "gemini": "TreeSitterGemini",
            "gherkin": "TreeSitterGherkin",
            "ghostty": "TreeSitterGhostty",
            "git-config": "TreeSitterGitConfig",
            "git-rebase": "TreeSitterGitRebase",
            "gitattributes": "TreeSitterGitattributes",
            "gitcommit": "TreeSitterGitcommit",
            "gitignore": "TreeSitterGitignore",
            "gleam": "TreeSitterGleam",
            "glimmer": "TreeSitterGlimmer",
            "glsl": "TreeSitterGlsl",
            "gn": "TreeSitterGn",
            "go": "TreeSitterGo",
            "godot-resource": "TreeSitterGodotResource",
            "gomod": "TreeSitterGomod",
            "gotmpl": "TreeSitterGotmpl",
            "gowork": "TreeSitterGowork",
            "gpr": "TreeSitterGpr",
            "graphql": "TreeSitterGraphql",
            "gren": "TreeSitterGren",
            "groovy": "TreeSitterGroovy",
            "hare": "TreeSitterHare",
            "haskell-literate": "TreeSitterHaskellLiterate",
            "haskell-persistent": "TreeSitterHaskellPersistent",
            "hcl": "TreeSitterHcl",
            "hdl": "TreeSitterHdl",
            "heex": "TreeSitterHeex",
            "hocon": "TreeSitterHocon",
            "hoon": "TreeSitterHoon",
            "hosts": "TreeSitterHosts",
            "html": "TreeSitterHtml",
            "htmldjango": "TreeSitterHtmldjango",
            "hurl": "TreeSitterHurl",
            "hyprlang": "TreeSitterHyprlang",
            "iex": "TreeSitterIex",
            "ini": "TreeSitterIni",
            "ink": "TreeSitterInk",
            "inko": "TreeSitterInko",
            "janet-simple": "TreeSitterJanetSimple",
            "java": "TreeSitterJava",
            "javascript": "TreeSitterJavascript",
            "jinja2": "TreeSitterJinja2",
            "jjdescription": "TreeSitterJjdescription",
            "jjrevset": "TreeSitterJjrevset",
            "jjtemplate": "TreeSitterJjtemplate",
            "jq": "TreeSitterJq",
            "jsdoc": "TreeSitterJsdoc",
            "json": "TreeSitterJson",
            "json5": "TreeSitterJson5",
            "jsonnet": "TreeSitterJsonnet",
            "julia": "TreeSitterJulia",
            "just": "TreeSitterJust",
            "kcl": "TreeSitterKcl",
            "kconfig": "TreeSitterKconfig",
            "koka": "TreeSitterKoka",
            "kotlin": "TreeSitterKotlin",
            "koto": "TreeSitterKoto",
            "ld": "TreeSitterLd",
            "ldif": "TreeSitterLdif",
            "lean": "TreeSitterLean",
            "ledger": "TreeSitterLedger",
            "llvm": "TreeSitterLlvm",
            "llvm-mir": "TreeSitterLlvmMir",
            "log": "TreeSitterLog",
            "lpf": "TreeSitterLpf",
            "luap": "TreeSitterLuap",
            "make": "TreeSitterMake",
            "markdoc": "TreeSitterMarkdoc",
            "markdown": "TreeSitterMarkdown",
            "markdown-inline": "TreeSitterMarkdownInline",
            "matlab": "TreeSitterMatlab",
            "mermaid": "TreeSitterMermaid",
            "meson": "TreeSitterMeson",
            "mojo": "TreeSitterMojo",
            "move": "TreeSitterMove",
            "nasm": "TreeSitterNasm",
            "nearley": "TreeSitterNearley",
            "nginx": "TreeSitterNginx",
            "nickel": "TreeSitterNickel",
            "nix": "TreeSitterNix",
            "odin": "TreeSitterOdin",
            "ohm": "TreeSitterOhm",
            "opencl": "TreeSitterOpencl",
            "openscad": "TreeSitterOpenscad",
            "org": "TreeSitterOrg",
            "pascal": "TreeSitterPascal",
            "passwd": "TreeSitterPasswd",
            "pem": "TreeSitterPem",
            "pest": "TreeSitterPest",
            "pkl": "TreeSitterPkl",
            "po": "TreeSitterPo",
            "ponylang": "TreeSitterPonylang",
            "powershell": "TreeSitterPowershell",
            "prisma": "TreeSitterPrisma",
            "properties": "TreeSitterProperties",
            "proto": "TreeSitterProto",
            "prql": "TreeSitterPrql",
            "pug": "TreeSitterPug",
            "python": "TreeSitterPython",
            "ql": "TreeSitterQl",
            "query": "TreeSitterQuery",
            "regex": "TreeSitterRegex",
            "rego": "TreeSitterRego",
            "requirements": "TreeSitterRequirements",
            "rescript": "TreeSitterRescript",
            "robot": "TreeSitterRobot",
            "robots": "TreeSitterRobots",
            "ron": "TreeSitterRon",
            "rpmspec": "TreeSitterRpmspec",
            "rshtml": "TreeSitterRshtml",
            "rust": "TreeSitterRust",
            "rust-format-args": "TreeSitterRustFormatArgs",
            "scfg": "TreeSitterScfg",
            "scheme": "TreeSitterScheme",
            "scss": "TreeSitterScss",
            "slint": "TreeSitterSlint",
            "slisp": "TreeSitterSlisp",
            "smali": "TreeSitterSmali",
            "smithy": "TreeSitterSmithy",
            "sml": "TreeSitterSml",
            "snakemake": "TreeSitterSnakemake",
            "solidity": "TreeSitterSolidity",
            "sourcepawn": "TreeSitterSourcepawn",
            "spade": "TreeSitterSpade",
            "spicedb": "TreeSitterSpicedb",
            "sql": "TreeSitterSql",
            "sshclientconfig": "TreeSitterSshclientconfig",
            "strace": "TreeSitterStrace",
            "strictdoc": "TreeSitterStrictdoc",
            "supercollider": "TreeSitterSupercollider",
            "swift": "TreeSitterSwift",
            "sway": "TreeSitterSway",
            "systemverilog": "TreeSitterSystemverilog",
            "t32": "TreeSitterT32",
            "tablegen": "TreeSitterTablegen",
            "tact": "TreeSitterTact",
            "task": "TreeSitterTask",
            "tcl": "TreeSitterTcl",
            "templ": "TreeSitterTempl",
            "textproto": "TreeSitterTextproto",
            "thrift": "TreeSitterThrift",
            "todotxt": "TreeSitterTodotxt",
            "toml": "TreeSitterToml",
            "tsx": "TreeSitterTsx",
            "twig": "TreeSitterTwig",
            "typescript": "TreeSitterTypescript",
            "typespec": "TreeSitterTypespec",
            "ungrammar": "TreeSitterUngrammar",
            "uxntal": "TreeSitterUxntal",
            "vala": "TreeSitterVala",
            "vento": "TreeSitterVento",
            "verilog": "TreeSitterVerilog",
            "vhs": "TreeSitterVhs",
            "wesl": "TreeSitterWesl",
            "wgsl": "TreeSitterWgsl",
            "wit": "TreeSitterWit",
            "wren": "TreeSitterWren",
            "xit": "TreeSitterXit",
            "xml": "TreeSitterXml",
            "xtc": "TreeSitterXtc",
            "yaml": "TreeSitterYaml",
            "yara": "TreeSitterYara",
            "yuck": "TreeSitterYuck",
            "zig": "TreeSitterZig",
        ]

        if let name = productNames[identifier] {
            return "lib\(name).dylib"
        }

        // Default: capitalize first letter
        let capitalized = identifier.prefix(1).uppercased() + identifier.dropFirst()
        return "libTreeSitter\(capitalized).dylib"
    }

    /// Get the C function name for a language
    private func grammarFunctionName(for identifier: String) -> String? {
        // Map identifier to tree_sitter_xxx function name
        let functionNames: [String: String] = [
            "ada": "tree_sitter_ada",
            "adl": "tree_sitter_adl",
            "agda": "tree_sitter_agda",
            "alloy": "tree_sitter_alloy",
            "amber": "tree_sitter_amber",
            "awk": "tree_sitter_awk",
            "bash": "tree_sitter_bash",
            "basic": "tree_sitter_basic",
            "bass": "tree_sitter_bass",
            "beancount": "tree_sitter_beancount",
            "bibtex": "tree_sitter_bibtex",
            "bitbake": "tree_sitter_bitbake",
            "blueprint": "tree_sitter_blueprint",
            "bovex": "tree_sitter_bovex",
            "c": "tree_sitter_c",
            "cpp": "tree_sitter_cpp",
            "caddyfile": "tree_sitter_caddyfile",
            "cairo": "tree_sitter_cairo",
            "capnp": "tree_sitter_capnp",
            "cel": "tree_sitter_cel",
            "chuck": "tree_sitter_chuck",
            "clarity": "tree_sitter_clarity",
            "clojure": "tree_sitter_clojure",
            "cpon": "tree_sitter_cpon",
            "css": "tree_sitter_css",
            "csv": "tree_sitter_csv",
            "cue": "tree_sitter_cue",
            "cylc": "tree_sitter_cylc",
            "cython": "tree_sitter_cython",
            "d": "tree_sitter_d",
            "dart": "tree_sitter_dart",
            "dbml": "tree_sitter_dbml",
            "debian": "tree_sitter_debian",
            "devicetree": "tree_sitter_devicetree",
            "dhall": "tree_sitter_dhall",
            "diff": "tree_sitter_diff",
            "dockerfile": "tree_sitter_dockerfile",
            "dot": "tree_sitter_dot",
            "doxyfile": "tree_sitter_doxyfile",
            "dtd": "tree_sitter_dtd",
            "dunstrc": "tree_sitter_dunstrc",
            "earthfile": "tree_sitter_earthfile",
            "edoc": "tree_sitter_edoc",
            "eex": "tree_sitter_eex",
            "eiffel": "tree_sitter_eiffel",
            "elisp": "tree_sitter_elisp",
            "elixir": "tree_sitter_elixir",
            "elm": "tree_sitter_elm",
            "elvish": "tree_sitter_elvish",
            "embedded-template": "tree_sitter_embedded_template",
            "erlang": "tree_sitter_erlang",
            "fennel": "tree_sitter_fennel",
            "fga": "tree_sitter_fga",
            "fidl": "tree_sitter_fidl",
            "fish": "tree_sitter_fish",
            "flatbuffers": "tree_sitter_flatbuffers",
            "forth": "tree_sitter_forth",
            "freebasic": "tree_sitter_freebasic",
            "gas": "tree_sitter_gas",
            "gdscript": "tree_sitter_gdscript",
            "gemini": "tree_sitter_gemini",
            "gherkin": "tree_sitter_gherkin",
            "ghostty": "tree_sitter_ghostty",
            "git-config": "tree_sitter_git_config",
            "git-rebase": "tree_sitter_git_rebase",
            "gitattributes": "tree_sitter_gitattributes",
            "gitcommit": "tree_sitter_gitcommit",
            "gitignore": "tree_sitter_gitignore",
            "gleam": "tree_sitter_gleam",
            "glimmer": "tree_sitter_glimmer",
            "glsl": "tree_sitter_glsl",
            "gn": "tree_sitter_gn",
            "go": "tree_sitter_go",
            "godot-resource": "tree_sitter_godot_resource",
            "gomod": "tree_sitter_gomod",
            "gotmpl": "tree_sitter_gotmpl",
            "gowork": "tree_sitter_gowork",
            "gpr": "tree_sitter_gpr",
            "graphql": "tree_sitter_graphql",
            "gren": "tree_sitter_gren",
            "groovy": "tree_sitter_groovy",
            "hare": "tree_sitter_hare",
            "haskell-literate": "tree_sitter_haskell_literate",
            "haskell-persistent": "tree_sitter_haskell_persistent",
            "hcl": "tree_sitter_hcl",
            "hdl": "tree_sitter_hdl",
            "heex": "tree_sitter_heex",
            "hocon": "tree_sitter_hocon",
            "hoon": "tree_sitter_hoon",
            "hosts": "tree_sitter_hosts",
            "html": "tree_sitter_html",
            "htmldjango": "tree_sitter_htmldjango",
            "hurl": "tree_sitter_hurl",
            "hyprlang": "tree_sitter_hyprlang",
            "iex": "tree_sitter_iex",
            "ini": "tree_sitter_ini",
            "ink": "tree_sitter_ink",
            "inko": "tree_sitter_inko",
            "janet-simple": "tree_sitter_janet_simple",
            "java": "tree_sitter_java",
            "javascript": "tree_sitter_javascript",
            "jinja2": "tree_sitter_jinja2",
            "jjdescription": "tree_sitter_jjdescription",
            "jjrevset": "tree_sitter_jjrevset",
            "jjtemplate": "tree_sitter_jjtemplate",
            "jq": "tree_sitter_jq",
            "jsdoc": "tree_sitter_jsdoc",
            "json": "tree_sitter_json",
            "json5": "tree_sitter_json5",
            "jsonnet": "tree_sitter_jsonnet",
            "julia": "tree_sitter_julia",
            "just": "tree_sitter_just",
            "kcl": "tree_sitter_kcl",
            "kconfig": "tree_sitter_kconfig",
            "koka": "tree_sitter_koka",
            "kotlin": "tree_sitter_kotlin",
            "koto": "tree_sitter_koto",
            "ld": "tree_sitter_ld",
            "ldif": "tree_sitter_ldif",
            "lean": "tree_sitter_lean",
            "ledger": "tree_sitter_ledger",
            "llvm": "tree_sitter_llvm",
            "llvm-mir": "tree_sitter_llvm_mir",
            "log": "tree_sitter_log",
            "lpf": "tree_sitter_lpf",
            "luap": "tree_sitter_luap",
            "make": "tree_sitter_make",
            "markdoc": "tree_sitter_markdoc",
            "markdown": "tree_sitter_markdown",
            "markdown-inline": "tree_sitter_markdown_inline",
            "matlab": "tree_sitter_matlab",
            "mermaid": "tree_sitter_mermaid",
            "meson": "tree_sitter_meson",
            "mojo": "tree_sitter_mojo",
            "move": "tree_sitter_move",
            "nasm": "tree_sitter_nasm",
            "nearley": "tree_sitter_nearley",
            "nginx": "tree_sitter_nginx",
            "nickel": "tree_sitter_nickel",
            "nix": "tree_sitter_nix",
            "odin": "tree_sitter_odin",
            "ohm": "tree_sitter_ohm",
            "opencl": "tree_sitter_opencl",
            "openscad": "tree_sitter_openscad",
            "org": "tree_sitter_org",
            "pascal": "tree_sitter_pascal",
            "passwd": "tree_sitter_passwd",
            "pem": "tree_sitter_pem",
            "pest": "tree_sitter_pest",
            "pkl": "tree_sitter_pkl",
            "po": "tree_sitter_po",
            "ponylang": "tree_sitter_ponylang",
            "powershell": "tree_sitter_powershell",
            "prisma": "tree_sitter_prisma",
            "properties": "tree_sitter_properties",
            "proto": "tree_sitter_proto",
            "prql": "tree_sitter_prql",
            "pug": "tree_sitter_pug",
            "python": "tree_sitter_python",
            "ql": "tree_sitter_ql",
            "query": "tree_sitter_query",
            "regex": "tree_sitter_regex",
            "rego": "tree_sitter_rego",
            "requirements": "tree_sitter_requirements",
            "rescript": "tree_sitter_rescript",
            "robot": "tree_sitter_robot",
            "robots": "tree_sitter_robots",
            "ron": "tree_sitter_ron",
            "rpmspec": "tree_sitter_rpmspec",
            "rshtml": "tree_sitter_rshtml",
            "rust": "tree_sitter_rust",
            "rust-format-args": "tree_sitter_rust_format_args",
            "scfg": "tree_sitter_scfg",
            "scheme": "tree_sitter_scheme",
            "scss": "tree_sitter_scss",
            "slint": "tree_sitter_slint",
            "slisp": "tree_sitter_slisp",
            "smali": "tree_sitter_smali",
            "smithy": "tree_sitter_smithy",
            "sml": "tree_sitter_sml",
            "snakemake": "tree_sitter_snakemake",
            "solidity": "tree_sitter_solidity",
            "sourcepawn": "tree_sitter_sourcepawn",
            "spade": "tree_sitter_spade",
            "spicedb": "tree_sitter_spicedb",
            "sql": "tree_sitter_sql",
            "sshclientconfig": "tree_sitter_ssh_client_config",
            "strace": "tree_sitter_strace",
            "strictdoc": "tree_sitter_strictdoc",
            "supercollider": "tree_sitter_supercollider",
            "swift": "tree_sitter_swift",
            "sway": "tree_sitter_sway",
            "systemverilog": "tree_sitter_systemverilog",
            "t32": "tree_sitter_t32",
            "tablegen": "tree_sitter_tablegen",
            "tact": "tree_sitter_tact",
            "task": "tree_sitter_task",
            "tcl": "tree_sitter_tcl",
            "templ": "tree_sitter_templ",
            "textproto": "tree_sitter_textproto",
            "thrift": "tree_sitter_thrift",
            "todotxt": "tree_sitter_todotxt",
            "toml": "tree_sitter_toml",
            "tsx": "tree_sitter_tsx",
            "twig": "tree_sitter_twig",
            "typescript": "tree_sitter_typescript",
            "typespec": "tree_sitter_typespec",
            "ungrammar": "tree_sitter_ungrammar",
            "uxntal": "tree_sitter_uxntal",
            "vala": "tree_sitter_vala",
            "vento": "tree_sitter_vento",
            "verilog": "tree_sitter_verilog",
            "vhs": "tree_sitter_vhs",
            "wesl": "tree_sitter_wesl",
            "wgsl": "tree_sitter_wgsl",
            "wit": "tree_sitter_wit",
            "wren": "tree_sitter_wren",
            "xit": "tree_sitter_xit",
            "xml": "tree_sitter_xml",
            "xtc": "tree_sitter_xtc",
            "yaml": "tree_sitter_yaml",
            "yara": "tree_sitter_yara",
            "yuck": "tree_sitter_yuck",
            "zig": "tree_sitter_zig",
        ]
        return functionNames[identifier]
    }

    /// Number of currently loaded grammars
    public var loadedCount: Int {
        lock.lock()
        defer { lock.unlock() }
        return loadedLanguages.count
    }
}

// MARK: - Language Configuration Factory

public extension LanguageRegistry {
    /// Get or create configuration for a language by identifier (lazy loading)
    static func configuration(for identifier: String) -> LanguageConfiguration? {
        // Use dynamic loader to get the language
        guard let language = DynamicGrammarLoader.shared.loadLanguage(identifier) else {
            return nil
        }

        // Load the highlight query
        let queryName = "\(identifier)-highlights"
        guard let queryURL = Bundle.module.url(forResource: queryName, withExtension: "scm", subdirectory: "queries"),
              let queryString = try? String(contentsOf: queryURL, encoding: .utf8) else {
            return nil
        }

        do {
            let config = try LanguageConfiguration(
                identifier: identifier,
                displayName: identifier.capitalized,
                language: language,
                highlightQuery: queryString
            )
            return config
        } catch {
            return nil
        }
    }
}
