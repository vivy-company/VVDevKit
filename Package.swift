// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "VVDevKit",
    platforms: [
        .macOS(.v13),
        .iOS(.v13)
    ],
    products: [
        .library(
            name: "VVDevKit",
            targets: ["VVDevKit"]
        ),
        .library(
            name: "VVCode",
            targets: ["VVCode"]
        ),
        .library(
            name: "VVMetalPrimitives",
            targets: ["VVMetalPrimitives"]
        ),
        .library(
            name: "VVMarkdown",
            targets: ["VVMarkdown"]
        ),
        .library(
            name: "VVChatTimeline",
            targets: ["VVChatTimeline"]
        ),
        .executable(
            name: "VVDevKitPlayground",
            targets: ["VVDevKitPlayground"]
        ),
        // Individual dynamic grammar libraries - load on demand via DynamicGrammarLoader
        .library(name: "TreeSitterSwift", type: .dynamic, targets: ["TreeSitterSwift"]),
        .library(name: "TreeSitterAda", type: .dynamic, targets: ["TreeSitterAda"]),
        .library(name: "TreeSitterAdl", type: .dynamic, targets: ["TreeSitterAdl"]),
        .library(name: "TreeSitterAgda", type: .dynamic, targets: ["TreeSitterAgda"]),
        .library(name: "TreeSitterAlloy", type: .dynamic, targets: ["TreeSitterAlloy"]),
        .library(name: "TreeSitterAmber", type: .dynamic, targets: ["TreeSitterAmber"]),
        .library(name: "TreeSitterAwk", type: .dynamic, targets: ["TreeSitterAwk"]),
        .library(name: "TreeSitterBash", type: .dynamic, targets: ["TreeSitterBash"]),
        .library(name: "TreeSitterBasic", type: .dynamic, targets: ["TreeSitterBasic"]),
        .library(name: "TreeSitterBass", type: .dynamic, targets: ["TreeSitterBass"]),
        .library(name: "TreeSitterBeancount", type: .dynamic, targets: ["TreeSitterBeancount"]),
        .library(name: "TreeSitterBibtex", type: .dynamic, targets: ["TreeSitterBibtex"]),
        .library(name: "TreeSitterBitbake", type: .dynamic, targets: ["TreeSitterBitbake"]),
        .library(name: "TreeSitterBlueprint", type: .dynamic, targets: ["TreeSitterBlueprint"]),
        .library(name: "TreeSitterBovex", type: .dynamic, targets: ["TreeSitterBovex"]),
        .library(name: "TreeSitterC", type: .dynamic, targets: ["TreeSitterC"]),
        .library(name: "TreeSitterCpp", type: .dynamic, targets: ["TreeSitterCpp"]),
        .library(name: "TreeSitterCaddyfile", type: .dynamic, targets: ["TreeSitterCaddyfile"]),
        .library(name: "TreeSitterCairo", type: .dynamic, targets: ["TreeSitterCairo"]),
        .library(name: "TreeSitterCapnp", type: .dynamic, targets: ["TreeSitterCapnp"]),
        .library(name: "TreeSitterCel", type: .dynamic, targets: ["TreeSitterCel"]),
        .library(name: "TreeSitterChuck", type: .dynamic, targets: ["TreeSitterChuck"]),
        .library(name: "TreeSitterClarity", type: .dynamic, targets: ["TreeSitterClarity"]),
        .library(name: "TreeSitterClojure", type: .dynamic, targets: ["TreeSitterClojure"]),
        .library(name: "TreeSitterCpon", type: .dynamic, targets: ["TreeSitterCpon"]),
        .library(name: "TreeSitterCss", type: .dynamic, targets: ["TreeSitterCss"]),
        .library(name: "TreeSitterCsv", type: .dynamic, targets: ["TreeSitterCsv"]),
        .library(name: "TreeSitterCue", type: .dynamic, targets: ["TreeSitterCue"]),
        .library(name: "TreeSitterCylc", type: .dynamic, targets: ["TreeSitterCylc"]),
        .library(name: "TreeSitterCython", type: .dynamic, targets: ["TreeSitterCython"]),
        .library(name: "TreeSitterD", type: .dynamic, targets: ["TreeSitterD"]),
        .library(name: "TreeSitterDart", type: .dynamic, targets: ["TreeSitterDart"]),
        .library(name: "TreeSitterDbml", type: .dynamic, targets: ["TreeSitterDbml"]),
        .library(name: "TreeSitterDebian", type: .dynamic, targets: ["TreeSitterDebian"]),
        .library(name: "TreeSitterDevicetree", type: .dynamic, targets: ["TreeSitterDevicetree"]),
        .library(name: "TreeSitterDhall", type: .dynamic, targets: ["TreeSitterDhall"]),
        .library(name: "TreeSitterDiff", type: .dynamic, targets: ["TreeSitterDiff"]),
        .library(name: "TreeSitterDockerfile", type: .dynamic, targets: ["TreeSitterDockerfile"]),
        .library(name: "TreeSitterDot", type: .dynamic, targets: ["TreeSitterDot"]),
        .library(name: "TreeSitterDoxyfile", type: .dynamic, targets: ["TreeSitterDoxyfile"]),
        .library(name: "TreeSitterDtd", type: .dynamic, targets: ["TreeSitterDtd"]),
        .library(name: "TreeSitterDunstrc", type: .dynamic, targets: ["TreeSitterDunstrc"]),
        .library(name: "TreeSitterEarthfile", type: .dynamic, targets: ["TreeSitterEarthfile"]),
        .library(name: "TreeSitterEdoc", type: .dynamic, targets: ["TreeSitterEdoc"]),
        .library(name: "TreeSitterEex", type: .dynamic, targets: ["TreeSitterEex"]),
        .library(name: "TreeSitterEiffel", type: .dynamic, targets: ["TreeSitterEiffel"]),
        .library(name: "TreeSitterElisp", type: .dynamic, targets: ["TreeSitterElisp"]),
        .library(name: "TreeSitterElixir", type: .dynamic, targets: ["TreeSitterElixir"]),
        .library(name: "TreeSitterElm", type: .dynamic, targets: ["TreeSitterElm"]),
        .library(name: "TreeSitterElvish", type: .dynamic, targets: ["TreeSitterElvish"]),
        .library(name: "TreeSitterEmbeddedTemplate", type: .dynamic, targets: ["TreeSitterEmbeddedTemplate"]),
        .library(name: "TreeSitterErlang", type: .dynamic, targets: ["TreeSitterErlang"]),
        .library(name: "TreeSitterFennel", type: .dynamic, targets: ["TreeSitterFennel"]),
        .library(name: "TreeSitterFga", type: .dynamic, targets: ["TreeSitterFga"]),
        .library(name: "TreeSitterFidl", type: .dynamic, targets: ["TreeSitterFidl"]),
        .library(name: "TreeSitterFish", type: .dynamic, targets: ["TreeSitterFish"]),
        .library(name: "TreeSitterFlatbuffers", type: .dynamic, targets: ["TreeSitterFlatbuffers"]),
        .library(name: "TreeSitterForth", type: .dynamic, targets: ["TreeSitterForth"]),
        .library(name: "TreeSitterFreebasic", type: .dynamic, targets: ["TreeSitterFreebasic"]),
        .library(name: "TreeSitterGas", type: .dynamic, targets: ["TreeSitterGas"]),
        .library(name: "TreeSitterGdscript", type: .dynamic, targets: ["TreeSitterGdscript"]),
        .library(name: "TreeSitterGemini", type: .dynamic, targets: ["TreeSitterGemini"]),
        .library(name: "TreeSitterGherkin", type: .dynamic, targets: ["TreeSitterGherkin"]),
        .library(name: "TreeSitterGhostty", type: .dynamic, targets: ["TreeSitterGhostty"]),
        .library(name: "TreeSitterGitConfig", type: .dynamic, targets: ["TreeSitterGitConfig"]),
        .library(name: "TreeSitterGitRebase", type: .dynamic, targets: ["TreeSitterGitRebase"]),
        .library(name: "TreeSitterGitattributes", type: .dynamic, targets: ["TreeSitterGitattributes"]),
        .library(name: "TreeSitterGitcommit", type: .dynamic, targets: ["TreeSitterGitcommit"]),
        .library(name: "TreeSitterGitignore", type: .dynamic, targets: ["TreeSitterGitignore"]),
        .library(name: "TreeSitterGleam", type: .dynamic, targets: ["TreeSitterGleam"]),
        .library(name: "TreeSitterGlimmer", type: .dynamic, targets: ["TreeSitterGlimmer"]),
        .library(name: "TreeSitterGlsl", type: .dynamic, targets: ["TreeSitterGlsl"]),
        .library(name: "TreeSitterGn", type: .dynamic, targets: ["TreeSitterGn"]),
        .library(name: "TreeSitterGo", type: .dynamic, targets: ["TreeSitterGo"]),
        .library(name: "TreeSitterGodotResource", type: .dynamic, targets: ["TreeSitterGodotResource"]),
        .library(name: "TreeSitterGomod", type: .dynamic, targets: ["TreeSitterGomod"]),
        .library(name: "TreeSitterGotmpl", type: .dynamic, targets: ["TreeSitterGotmpl"]),
        .library(name: "TreeSitterGowork", type: .dynamic, targets: ["TreeSitterGowork"]),
        .library(name: "TreeSitterGpr", type: .dynamic, targets: ["TreeSitterGpr"]),
        .library(name: "TreeSitterGraphql", type: .dynamic, targets: ["TreeSitterGraphql"]),
        .library(name: "TreeSitterGren", type: .dynamic, targets: ["TreeSitterGren"]),
        .library(name: "TreeSitterGroovy", type: .dynamic, targets: ["TreeSitterGroovy"]),
        .library(name: "TreeSitterHare", type: .dynamic, targets: ["TreeSitterHare"]),
        .library(name: "TreeSitterHaskellLiterate", type: .dynamic, targets: ["TreeSitterHaskellLiterate"]),
        .library(name: "TreeSitterHaskellPersistent", type: .dynamic, targets: ["TreeSitterHaskellPersistent"]),
        .library(name: "TreeSitterHcl", type: .dynamic, targets: ["TreeSitterHcl"]),
        .library(name: "TreeSitterHdl", type: .dynamic, targets: ["TreeSitterHdl"]),
        .library(name: "TreeSitterHeex", type: .dynamic, targets: ["TreeSitterHeex"]),
        .library(name: "TreeSitterHocon", type: .dynamic, targets: ["TreeSitterHocon"]),
        .library(name: "TreeSitterHoon", type: .dynamic, targets: ["TreeSitterHoon"]),
        .library(name: "TreeSitterHosts", type: .dynamic, targets: ["TreeSitterHosts"]),
        .library(name: "TreeSitterHtml", type: .dynamic, targets: ["TreeSitterHtml"]),
        .library(name: "TreeSitterHtmldjango", type: .dynamic, targets: ["TreeSitterHtmldjango"]),
        .library(name: "TreeSitterHurl", type: .dynamic, targets: ["TreeSitterHurl"]),
        .library(name: "TreeSitterHyprlang", type: .dynamic, targets: ["TreeSitterHyprlang"]),
        .library(name: "TreeSitterIex", type: .dynamic, targets: ["TreeSitterIex"]),
        .library(name: "TreeSitterIni", type: .dynamic, targets: ["TreeSitterIni"]),
        .library(name: "TreeSitterInk", type: .dynamic, targets: ["TreeSitterInk"]),
        .library(name: "TreeSitterInko", type: .dynamic, targets: ["TreeSitterInko"]),
        .library(name: "TreeSitterJanetSimple", type: .dynamic, targets: ["TreeSitterJanetSimple"]),
        .library(name: "TreeSitterJava", type: .dynamic, targets: ["TreeSitterJava"]),
        .library(name: "TreeSitterJavascript", type: .dynamic, targets: ["TreeSitterJavascript"]),
        .library(name: "TreeSitterJinja2", type: .dynamic, targets: ["TreeSitterJinja2"]),
        .library(name: "TreeSitterJjdescription", type: .dynamic, targets: ["TreeSitterJjdescription"]),
        .library(name: "TreeSitterJjrevset", type: .dynamic, targets: ["TreeSitterJjrevset"]),
        .library(name: "TreeSitterJjtemplate", type: .dynamic, targets: ["TreeSitterJjtemplate"]),
        .library(name: "TreeSitterJq", type: .dynamic, targets: ["TreeSitterJq"]),
        .library(name: "TreeSitterJsdoc", type: .dynamic, targets: ["TreeSitterJsdoc"]),
        .library(name: "TreeSitterJson", type: .dynamic, targets: ["TreeSitterJson"]),
        .library(name: "TreeSitterJson5", type: .dynamic, targets: ["TreeSitterJson5"]),
        .library(name: "TreeSitterJsonnet", type: .dynamic, targets: ["TreeSitterJsonnet"]),
        .library(name: "TreeSitterJulia", type: .dynamic, targets: ["TreeSitterJulia"]),
        .library(name: "TreeSitterJust", type: .dynamic, targets: ["TreeSitterJust"]),
        .library(name: "TreeSitterKcl", type: .dynamic, targets: ["TreeSitterKcl"]),
        .library(name: "TreeSitterKconfig", type: .dynamic, targets: ["TreeSitterKconfig"]),
        .library(name: "TreeSitterKoka", type: .dynamic, targets: ["TreeSitterKoka"]),
        .library(name: "TreeSitterKotlin", type: .dynamic, targets: ["TreeSitterKotlin"]),
        .library(name: "TreeSitterKoto", type: .dynamic, targets: ["TreeSitterKoto"]),
        .library(name: "TreeSitterLd", type: .dynamic, targets: ["TreeSitterLd"]),
        .library(name: "TreeSitterLdif", type: .dynamic, targets: ["TreeSitterLdif"]),
        .library(name: "TreeSitterLean", type: .dynamic, targets: ["TreeSitterLean"]),
        .library(name: "TreeSitterLedger", type: .dynamic, targets: ["TreeSitterLedger"]),
        .library(name: "TreeSitterLlvm", type: .dynamic, targets: ["TreeSitterLlvm"]),
        .library(name: "TreeSitterLlvmMir", type: .dynamic, targets: ["TreeSitterLlvmMir"]),
        .library(name: "TreeSitterLog", type: .dynamic, targets: ["TreeSitterLog"]),
        .library(name: "TreeSitterLpf", type: .dynamic, targets: ["TreeSitterLpf"]),
        .library(name: "TreeSitterLuap", type: .dynamic, targets: ["TreeSitterLuap"]),
        .library(name: "TreeSitterMake", type: .dynamic, targets: ["TreeSitterMake"]),
        .library(name: "TreeSitterMarkdoc", type: .dynamic, targets: ["TreeSitterMarkdoc"]),
        .library(name: "TreeSitterMarkdown", type: .dynamic, targets: ["TreeSitterMarkdown"]),
        .library(name: "TreeSitterMarkdownInline", type: .dynamic, targets: ["TreeSitterMarkdownInline"]),
        .library(name: "TreeSitterMatlab", type: .dynamic, targets: ["TreeSitterMatlab"]),
        .library(name: "TreeSitterMermaid", type: .dynamic, targets: ["TreeSitterMermaid"]),
        .library(name: "TreeSitterMeson", type: .dynamic, targets: ["TreeSitterMeson"]),
        .library(name: "TreeSitterMojo", type: .dynamic, targets: ["TreeSitterMojo"]),
        .library(name: "TreeSitterMove", type: .dynamic, targets: ["TreeSitterMove"]),
        .library(name: "TreeSitterNasm", type: .dynamic, targets: ["TreeSitterNasm"]),
        .library(name: "TreeSitterNearley", type: .dynamic, targets: ["TreeSitterNearley"]),
        .library(name: "TreeSitterNginx", type: .dynamic, targets: ["TreeSitterNginx"]),
        .library(name: "TreeSitterNickel", type: .dynamic, targets: ["TreeSitterNickel"]),
        .library(name: "TreeSitterNix", type: .dynamic, targets: ["TreeSitterNix"]),
        .library(name: "TreeSitterOdin", type: .dynamic, targets: ["TreeSitterOdin"]),
        .library(name: "TreeSitterOhm", type: .dynamic, targets: ["TreeSitterOhm"]),
        .library(name: "TreeSitterOpencl", type: .dynamic, targets: ["TreeSitterOpencl"]),
        .library(name: "TreeSitterOpenscad", type: .dynamic, targets: ["TreeSitterOpenscad"]),
        .library(name: "TreeSitterOrg", type: .dynamic, targets: ["TreeSitterOrg"]),
        .library(name: "TreeSitterPascal", type: .dynamic, targets: ["TreeSitterPascal"]),
        .library(name: "TreeSitterPasswd", type: .dynamic, targets: ["TreeSitterPasswd"]),
        .library(name: "TreeSitterPem", type: .dynamic, targets: ["TreeSitterPem"]),
        .library(name: "TreeSitterPest", type: .dynamic, targets: ["TreeSitterPest"]),
        .library(name: "TreeSitterPkl", type: .dynamic, targets: ["TreeSitterPkl"]),
        .library(name: "TreeSitterPo", type: .dynamic, targets: ["TreeSitterPo"]),
        .library(name: "TreeSitterPonylang", type: .dynamic, targets: ["TreeSitterPonylang"]),
        .library(name: "TreeSitterPowershell", type: .dynamic, targets: ["TreeSitterPowershell"]),
        .library(name: "TreeSitterPrisma", type: .dynamic, targets: ["TreeSitterPrisma"]),
        .library(name: "TreeSitterProperties", type: .dynamic, targets: ["TreeSitterProperties"]),
        .library(name: "TreeSitterProto", type: .dynamic, targets: ["TreeSitterProto"]),
        .library(name: "TreeSitterPrql", type: .dynamic, targets: ["TreeSitterPrql"]),
        .library(name: "TreeSitterPug", type: .dynamic, targets: ["TreeSitterPug"]),
        .library(name: "TreeSitterPython", type: .dynamic, targets: ["TreeSitterPython"]),
        .library(name: "TreeSitterQl", type: .dynamic, targets: ["TreeSitterQl"]),
        .library(name: "TreeSitterQuery", type: .dynamic, targets: ["TreeSitterQuery"]),
        .library(name: "TreeSitterRegex", type: .dynamic, targets: ["TreeSitterRegex"]),
        .library(name: "TreeSitterRego", type: .dynamic, targets: ["TreeSitterRego"]),
        .library(name: "TreeSitterRequirements", type: .dynamic, targets: ["TreeSitterRequirements"]),
        .library(name: "TreeSitterRescript", type: .dynamic, targets: ["TreeSitterRescript"]),
        .library(name: "TreeSitterRobot", type: .dynamic, targets: ["TreeSitterRobot"]),
        .library(name: "TreeSitterRobots", type: .dynamic, targets: ["TreeSitterRobots"]),
        .library(name: "TreeSitterRon", type: .dynamic, targets: ["TreeSitterRon"]),
        .library(name: "TreeSitterRust", type: .dynamic, targets: ["TreeSitterRust"]),
        .library(name: "TreeSitterRpmspec", type: .dynamic, targets: ["TreeSitterRpmspec"]),
        .library(name: "TreeSitterRshtml", type: .dynamic, targets: ["TreeSitterRshtml"]),
        .library(name: "TreeSitterRustFormatArgs", type: .dynamic, targets: ["TreeSitterRustFormatArgs"]),
        .library(name: "TreeSitterScfg", type: .dynamic, targets: ["TreeSitterScfg"]),
        .library(name: "TreeSitterScheme", type: .dynamic, targets: ["TreeSitterScheme"]),
        .library(name: "TreeSitterScss", type: .dynamic, targets: ["TreeSitterScss"]),
        .library(name: "TreeSitterSlint", type: .dynamic, targets: ["TreeSitterSlint"]),
        .library(name: "TreeSitterSlisp", type: .dynamic, targets: ["TreeSitterSlisp"]),
        .library(name: "TreeSitterSmali", type: .dynamic, targets: ["TreeSitterSmali"]),
        .library(name: "TreeSitterSmithy", type: .dynamic, targets: ["TreeSitterSmithy"]),
        .library(name: "TreeSitterSml", type: .dynamic, targets: ["TreeSitterSml"]),
        .library(name: "TreeSitterSnakemake", type: .dynamic, targets: ["TreeSitterSnakemake"]),
        .library(name: "TreeSitterSolidity", type: .dynamic, targets: ["TreeSitterSolidity"]),
        .library(name: "TreeSitterSourcepawn", type: .dynamic, targets: ["TreeSitterSourcepawn"]),
        .library(name: "TreeSitterSpade", type: .dynamic, targets: ["TreeSitterSpade"]),
        .library(name: "TreeSitterSpicedb", type: .dynamic, targets: ["TreeSitterSpicedb"]),
        .library(name: "TreeSitterSql", type: .dynamic, targets: ["TreeSitterSql"]),
        .library(name: "TreeSitterSshclientconfig", type: .dynamic, targets: ["TreeSitterSshclientconfig"]),
        .library(name: "TreeSitterStrace", type: .dynamic, targets: ["TreeSitterStrace"]),
        .library(name: "TreeSitterStrictdoc", type: .dynamic, targets: ["TreeSitterStrictdoc"]),
        .library(name: "TreeSitterSupercollider", type: .dynamic, targets: ["TreeSitterSupercollider"]),
        .library(name: "TreeSitterSway", type: .dynamic, targets: ["TreeSitterSway"]),
        .library(name: "TreeSitterSystemverilog", type: .dynamic, targets: ["TreeSitterSystemverilog"]),
        .library(name: "TreeSitterT32", type: .dynamic, targets: ["TreeSitterT32"]),
        .library(name: "TreeSitterTablegen", type: .dynamic, targets: ["TreeSitterTablegen"]),
        .library(name: "TreeSitterTact", type: .dynamic, targets: ["TreeSitterTact"]),
        .library(name: "TreeSitterTask", type: .dynamic, targets: ["TreeSitterTask"]),
        .library(name: "TreeSitterTcl", type: .dynamic, targets: ["TreeSitterTcl"]),
        .library(name: "TreeSitterTempl", type: .dynamic, targets: ["TreeSitterTempl"]),
        .library(name: "TreeSitterTextproto", type: .dynamic, targets: ["TreeSitterTextproto"]),
        .library(name: "TreeSitterThrift", type: .dynamic, targets: ["TreeSitterThrift"]),
        .library(name: "TreeSitterTodotxt", type: .dynamic, targets: ["TreeSitterTodotxt"]),
        .library(name: "TreeSitterToml", type: .dynamic, targets: ["TreeSitterToml"]),
        .library(name: "TreeSitterTsx", type: .dynamic, targets: ["TreeSitterTsx"]),
        .library(name: "TreeSitterTwig", type: .dynamic, targets: ["TreeSitterTwig"]),
        .library(name: "TreeSitterTypescript", type: .dynamic, targets: ["TreeSitterTypescript"]),
        .library(name: "TreeSitterTypespec", type: .dynamic, targets: ["TreeSitterTypespec"]),
        .library(name: "TreeSitterUngrammar", type: .dynamic, targets: ["TreeSitterUngrammar"]),
        .library(name: "TreeSitterUxntal", type: .dynamic, targets: ["TreeSitterUxntal"]),
        .library(name: "TreeSitterVala", type: .dynamic, targets: ["TreeSitterVala"]),
        .library(name: "TreeSitterVento", type: .dynamic, targets: ["TreeSitterVento"]),
        .library(name: "TreeSitterVerilog", type: .dynamic, targets: ["TreeSitterVerilog"]),
        .library(name: "TreeSitterVhs", type: .dynamic, targets: ["TreeSitterVhs"]),
        .library(name: "TreeSitterWesl", type: .dynamic, targets: ["TreeSitterWesl"]),
        .library(name: "TreeSitterWgsl", type: .dynamic, targets: ["TreeSitterWgsl"]),
        .library(name: "TreeSitterWit", type: .dynamic, targets: ["TreeSitterWit"]),
        .library(name: "TreeSitterWren", type: .dynamic, targets: ["TreeSitterWren"]),
        .library(name: "TreeSitterXit", type: .dynamic, targets: ["TreeSitterXit"]),
        .library(name: "TreeSitterXml", type: .dynamic, targets: ["TreeSitterXml"]),
        .library(name: "TreeSitterXtc", type: .dynamic, targets: ["TreeSitterXtc"]),
        .library(name: "TreeSitterYaml", type: .dynamic, targets: ["TreeSitterYaml"]),
        .library(name: "TreeSitterYara", type: .dynamic, targets: ["TreeSitterYara"]),
        .library(name: "TreeSitterYuck", type: .dynamic, targets: ["TreeSitterYuck"]),
        .library(name: "TreeSitterZig", type: .dynamic, targets: ["TreeSitterZig"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
        .package(url: "https://github.com/ChimeHQ/LanguageServerProtocol", from: "0.13.2"),
        .package(url: "https://github.com/apple/swift-markdown", from: "0.5.0"),
    ],
    targets: [
        // Batteries-included public surface
        .target(
            name: "VVDevKit",
            dependencies: [
                "VVCode",
                "VVMarkdown",
                "VVMetalPrimitives",
                "VVChatTimeline",
            ]
        ),

        // Main public API
        .target(
            name: "VVCode",
            dependencies: [
                "VVHighlighting",
                "VVGit",
                "VVLSP",
                "VVMarkdown",
            ]
        ),

        // Tree-sitter Swift grammar (bundled separately)
        .target(
            name: "TreeSitterSwift",
            path: "Sources/TreeSitterSwift",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterAda",
            path: "Sources/Grammars/TreeSitterAda",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterAdl",
            path: "Sources/Grammars/TreeSitterAdl",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterAgda",
            path: "Sources/Grammars/TreeSitterAgda",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterAlloy",
            path: "Sources/Grammars/TreeSitterAlloy",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterAmber",
            path: "Sources/Grammars/TreeSitterAmber",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterAwk",
            path: "Sources/Grammars/TreeSitterAwk",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterBash",
            path: "Sources/Grammars/TreeSitterBash",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterBasic",
            path: "Sources/Grammars/TreeSitterBasic",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterBass",
            path: "Sources/Grammars/TreeSitterBass",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterBeancount",
            path: "Sources/Grammars/TreeSitterBeancount",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterBibtex",
            path: "Sources/Grammars/TreeSitterBibtex",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterBitbake",
            path: "Sources/Grammars/TreeSitterBitbake",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterBlueprint",
            path: "Sources/Grammars/TreeSitterBlueprint",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterBovex",
            path: "Sources/Grammars/TreeSitterBovex",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterC",
            path: "Sources/Grammars/TreeSitterC",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCpp",
            path: "Sources/Grammars/TreeSitterCpp",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCaddyfile",
            path: "Sources/Grammars/TreeSitterCaddyfile",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCairo",
            path: "Sources/Grammars/TreeSitterCairo",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCapnp",
            path: "Sources/Grammars/TreeSitterCapnp",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCel",
            path: "Sources/Grammars/TreeSitterCel",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterChuck",
            path: "Sources/Grammars/TreeSitterChuck",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterClarity",
            path: "Sources/Grammars/TreeSitterClarity",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterClojure",
            path: "Sources/Grammars/TreeSitterClojure",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCpon",
            path: "Sources/Grammars/TreeSitterCpon",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCss",
            path: "Sources/Grammars/TreeSitterCss",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCsv",
            path: "Sources/Grammars/TreeSitterCsv",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCue",
            path: "Sources/Grammars/TreeSitterCue",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCylc",
            path: "Sources/Grammars/TreeSitterCylc",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterCython",
            path: "Sources/Grammars/TreeSitterCython",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterD",
            path: "Sources/Grammars/TreeSitterD",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDart",
            path: "Sources/Grammars/TreeSitterDart",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDbml",
            path: "Sources/Grammars/TreeSitterDbml",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDebian",
            path: "Sources/Grammars/TreeSitterDebian",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDevicetree",
            path: "Sources/Grammars/TreeSitterDevicetree",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDhall",
            path: "Sources/Grammars/TreeSitterDhall",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDiff",
            path: "Sources/Grammars/TreeSitterDiff",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDockerfile",
            path: "Sources/Grammars/TreeSitterDockerfile",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDot",
            path: "Sources/Grammars/TreeSitterDot",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDoxyfile",
            path: "Sources/Grammars/TreeSitterDoxyfile",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDtd",
            path: "Sources/Grammars/TreeSitterDtd",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterDunstrc",
            path: "Sources/Grammars/TreeSitterDunstrc",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterEarthfile",
            path: "Sources/Grammars/TreeSitterEarthfile",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterEdoc",
            path: "Sources/Grammars/TreeSitterEdoc",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterEex",
            path: "Sources/Grammars/TreeSitterEex",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterEiffel",
            path: "Sources/Grammars/TreeSitterEiffel",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterElisp",
            path: "Sources/Grammars/TreeSitterElisp",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterElixir",
            path: "Sources/Grammars/TreeSitterElixir",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterElm",
            path: "Sources/Grammars/TreeSitterElm",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterElvish",
            path: "Sources/Grammars/TreeSitterElvish",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterEmbeddedTemplate",
            path: "Sources/Grammars/TreeSitterEmbeddedTemplate",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterErlang",
            path: "Sources/Grammars/TreeSitterErlang",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterFennel",
            path: "Sources/Grammars/TreeSitterFennel",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterFga",
            path: "Sources/Grammars/TreeSitterFga",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterFidl",
            path: "Sources/Grammars/TreeSitterFidl",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterFish",
            path: "Sources/Grammars/TreeSitterFish",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterFlatbuffers",
            path: "Sources/Grammars/TreeSitterFlatbuffers",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterForth",
            path: "Sources/Grammars/TreeSitterForth",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterFreebasic",
            path: "Sources/Grammars/TreeSitterFreebasic",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGas",
            path: "Sources/Grammars/TreeSitterGas",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGdscript",
            path: "Sources/Grammars/TreeSitterGdscript",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGemini",
            path: "Sources/Grammars/TreeSitterGemini",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGherkin",
            path: "Sources/Grammars/TreeSitterGherkin",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGhostty",
            path: "Sources/Grammars/TreeSitterGhostty",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGitConfig",
            path: "Sources/Grammars/TreeSitterGitConfig",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGitRebase",
            path: "Sources/Grammars/TreeSitterGitRebase",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGitattributes",
            path: "Sources/Grammars/TreeSitterGitattributes",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGitcommit",
            path: "Sources/Grammars/TreeSitterGitcommit",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGitignore",
            path: "Sources/Grammars/TreeSitterGitignore",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGleam",
            path: "Sources/Grammars/TreeSitterGleam",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGlimmer",
            path: "Sources/Grammars/TreeSitterGlimmer",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGlsl",
            path: "Sources/Grammars/TreeSitterGlsl",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGn",
            path: "Sources/Grammars/TreeSitterGn",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGo",
            path: "Sources/Grammars/TreeSitterGo",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGodotResource",
            path: "Sources/Grammars/TreeSitterGodotResource",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGomod",
            path: "Sources/Grammars/TreeSitterGomod",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGotmpl",
            path: "Sources/Grammars/TreeSitterGotmpl",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGowork",
            path: "Sources/Grammars/TreeSitterGowork",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGpr",
            path: "Sources/Grammars/TreeSitterGpr",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGraphql",
            path: "Sources/Grammars/TreeSitterGraphql",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGren",
            path: "Sources/Grammars/TreeSitterGren",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterGroovy",
            path: "Sources/Grammars/TreeSitterGroovy",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHare",
            path: "Sources/Grammars/TreeSitterHare",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHaskellLiterate",
            path: "Sources/Grammars/TreeSitterHaskellLiterate",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHaskellPersistent",
            path: "Sources/Grammars/TreeSitterHaskellPersistent",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHcl",
            path: "Sources/Grammars/TreeSitterHcl",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHdl",
            path: "Sources/Grammars/TreeSitterHdl",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHeex",
            path: "Sources/Grammars/TreeSitterHeex",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHocon",
            path: "Sources/Grammars/TreeSitterHocon",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHoon",
            path: "Sources/Grammars/TreeSitterHoon",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHosts",
            path: "Sources/Grammars/TreeSitterHosts",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHtml",
            path: "Sources/Grammars/TreeSitterHtml",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHtmldjango",
            path: "Sources/Grammars/TreeSitterHtmldjango",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHurl",
            path: "Sources/Grammars/TreeSitterHurl",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterHyprlang",
            path: "Sources/Grammars/TreeSitterHyprlang",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterIex",
            path: "Sources/Grammars/TreeSitterIex",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterIni",
            path: "Sources/Grammars/TreeSitterIni",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterInk",
            path: "Sources/Grammars/TreeSitterInk",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterInko",
            path: "Sources/Grammars/TreeSitterInko",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJanetSimple",
            path: "Sources/Grammars/TreeSitterJanetSimple",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJava",
            path: "Sources/Grammars/TreeSitterJava",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJavascript",
            path: "Sources/Grammars/TreeSitterJavascript",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJinja2",
            path: "Sources/Grammars/TreeSitterJinja2",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJjdescription",
            path: "Sources/Grammars/TreeSitterJjdescription",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJjrevset",
            path: "Sources/Grammars/TreeSitterJjrevset",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJjtemplate",
            path: "Sources/Grammars/TreeSitterJjtemplate",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJq",
            path: "Sources/Grammars/TreeSitterJq",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJsdoc",
            path: "Sources/Grammars/TreeSitterJsdoc",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJson",
            path: "Sources/Grammars/TreeSitterJson",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJson5",
            path: "Sources/Grammars/TreeSitterJson5",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJsonnet",
            path: "Sources/Grammars/TreeSitterJsonnet",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJulia",
            path: "Sources/Grammars/TreeSitterJulia",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterJust",
            path: "Sources/Grammars/TreeSitterJust",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterKcl",
            path: "Sources/Grammars/TreeSitterKcl",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterKconfig",
            path: "Sources/Grammars/TreeSitterKconfig",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterKoka",
            path: "Sources/Grammars/TreeSitterKoka",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterKotlin",
            path: "Sources/Grammars/TreeSitterKotlin",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterKoto",
            path: "Sources/Grammars/TreeSitterKoto",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterLd",
            path: "Sources/Grammars/TreeSitterLd",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterLdif",
            path: "Sources/Grammars/TreeSitterLdif",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterLean",
            path: "Sources/Grammars/TreeSitterLean",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterLedger",
            path: "Sources/Grammars/TreeSitterLedger",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterLlvm",
            path: "Sources/Grammars/TreeSitterLlvm",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterLlvmMir",
            path: "Sources/Grammars/TreeSitterLlvmMir",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterLog",
            path: "Sources/Grammars/TreeSitterLog",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterLpf",
            path: "Sources/Grammars/TreeSitterLpf",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterLuap",
            path: "Sources/Grammars/TreeSitterLuap",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterMake",
            path: "Sources/Grammars/TreeSitterMake",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterMarkdoc",
            path: "Sources/Grammars/TreeSitterMarkdoc",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterMarkdown",
            path: "Sources/Grammars/TreeSitterMarkdown",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterMarkdownInline",
            path: "Sources/Grammars/TreeSitterMarkdownInline",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterMatlab",
            path: "Sources/Grammars/TreeSitterMatlab",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterMermaid",
            path: "Sources/Grammars/TreeSitterMermaid",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterMeson",
            path: "Sources/Grammars/TreeSitterMeson",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterMojo",
            path: "Sources/Grammars/TreeSitterMojo",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterMove",
            path: "Sources/Grammars/TreeSitterMove",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterNasm",
            path: "Sources/Grammars/TreeSitterNasm",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterNearley",
            path: "Sources/Grammars/TreeSitterNearley",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterNginx",
            path: "Sources/Grammars/TreeSitterNginx",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterNickel",
            path: "Sources/Grammars/TreeSitterNickel",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterNix",
            path: "Sources/Grammars/TreeSitterNix",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterOdin",
            path: "Sources/Grammars/TreeSitterOdin",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterOhm",
            path: "Sources/Grammars/TreeSitterOhm",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterOpencl",
            path: "Sources/Grammars/TreeSitterOpencl",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterOpenscad",
            path: "Sources/Grammars/TreeSitterOpenscad",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterOrg",
            path: "Sources/Grammars/TreeSitterOrg",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPascal",
            path: "Sources/Grammars/TreeSitterPascal",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPasswd",
            path: "Sources/Grammars/TreeSitterPasswd",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPem",
            path: "Sources/Grammars/TreeSitterPem",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPest",
            path: "Sources/Grammars/TreeSitterPest",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPkl",
            path: "Sources/Grammars/TreeSitterPkl",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPo",
            path: "Sources/Grammars/TreeSitterPo",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPonylang",
            path: "Sources/Grammars/TreeSitterPonylang",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPowershell",
            path: "Sources/Grammars/TreeSitterPowershell",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPrisma",
            path: "Sources/Grammars/TreeSitterPrisma",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterProperties",
            path: "Sources/Grammars/TreeSitterProperties",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterProto",
            path: "Sources/Grammars/TreeSitterProto",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPrql",
            path: "Sources/Grammars/TreeSitterPrql",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPug",
            path: "Sources/Grammars/TreeSitterPug",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterPython",
            path: "Sources/Grammars/TreeSitterPython",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterQl",
            path: "Sources/Grammars/TreeSitterQl",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterQuery",
            path: "Sources/Grammars/TreeSitterQuery",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRegex",
            path: "Sources/Grammars/TreeSitterRegex",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRego",
            path: "Sources/Grammars/TreeSitterRego",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRequirements",
            path: "Sources/Grammars/TreeSitterRequirements",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRescript",
            path: "Sources/Grammars/TreeSitterRescript",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRobot",
            path: "Sources/Grammars/TreeSitterRobot",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRobots",
            path: "Sources/Grammars/TreeSitterRobots",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRon",
            path: "Sources/Grammars/TreeSitterRon",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRust",
            path: "Sources/Grammars/TreeSitterRust",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRpmspec",
            path: "Sources/Grammars/TreeSitterRpmspec",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRshtml",
            path: "Sources/Grammars/TreeSitterRshtml",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterRustFormatArgs",
            path: "Sources/Grammars/TreeSitterRustFormatArgs",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterScfg",
            path: "Sources/Grammars/TreeSitterScfg",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterScheme",
            path: "Sources/Grammars/TreeSitterScheme",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterScss",
            path: "Sources/Grammars/TreeSitterScss",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSlint",
            path: "Sources/Grammars/TreeSitterSlint",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSlisp",
            path: "Sources/Grammars/TreeSitterSlisp",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSmali",
            path: "Sources/Grammars/TreeSitterSmali",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSmithy",
            path: "Sources/Grammars/TreeSitterSmithy",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSml",
            path: "Sources/Grammars/TreeSitterSml",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSnakemake",
            path: "Sources/Grammars/TreeSitterSnakemake",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSolidity",
            path: "Sources/Grammars/TreeSitterSolidity",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSourcepawn",
            path: "Sources/Grammars/TreeSitterSourcepawn",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSpade",
            path: "Sources/Grammars/TreeSitterSpade",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSpicedb",
            path: "Sources/Grammars/TreeSitterSpicedb",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSql",
            path: "Sources/Grammars/TreeSitterSql",
            sources: ["src/parser.c", "src/scanner.cpp"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src"), .define("__STDC_LIMIT_MACROS")]
        ),

        .target(
            name: "TreeSitterSshclientconfig",
            path: "Sources/Grammars/TreeSitterSshclientconfig",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterStrace",
            path: "Sources/Grammars/TreeSitterStrace",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterStrictdoc",
            path: "Sources/Grammars/TreeSitterStrictdoc",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSupercollider",
            path: "Sources/Grammars/TreeSitterSupercollider",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSway",
            path: "Sources/Grammars/TreeSitterSway",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterSystemverilog",
            path: "Sources/Grammars/TreeSitterSystemverilog",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterT32",
            path: "Sources/Grammars/TreeSitterT32",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTablegen",
            path: "Sources/Grammars/TreeSitterTablegen",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTact",
            path: "Sources/Grammars/TreeSitterTact",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTask",
            path: "Sources/Grammars/TreeSitterTask",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTcl",
            path: "Sources/Grammars/TreeSitterTcl",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTempl",
            path: "Sources/Grammars/TreeSitterTempl",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTextproto",
            path: "Sources/Grammars/TreeSitterTextproto",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterThrift",
            path: "Sources/Grammars/TreeSitterThrift",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTodotxt",
            path: "Sources/Grammars/TreeSitterTodotxt",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterToml",
            path: "Sources/Grammars/TreeSitterToml",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTsx",
            path: "Sources/Grammars/TreeSitterTsx",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTwig",
            path: "Sources/Grammars/TreeSitterTwig",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTypescript",
            path: "Sources/Grammars/TreeSitterTypescript",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterTypespec",
            path: "Sources/Grammars/TreeSitterTypespec",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterUngrammar",
            path: "Sources/Grammars/TreeSitterUngrammar",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterUxntal",
            path: "Sources/Grammars/TreeSitterUxntal",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterVala",
            path: "Sources/Grammars/TreeSitterVala",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterVento",
            path: "Sources/Grammars/TreeSitterVento",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterVerilog",
            path: "Sources/Grammars/TreeSitterVerilog",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterVhs",
            path: "Sources/Grammars/TreeSitterVhs",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterWesl",
            path: "Sources/Grammars/TreeSitterWesl",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterWgsl",
            path: "Sources/Grammars/TreeSitterWgsl",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterWit",
            path: "Sources/Grammars/TreeSitterWit",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterWren",
            path: "Sources/Grammars/TreeSitterWren",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterXit",
            path: "Sources/Grammars/TreeSitterXit",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterXml",
            path: "Sources/Grammars/TreeSitterXml",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterXtc",
            path: "Sources/Grammars/TreeSitterXtc",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterYaml",
            path: "Sources/Grammars/TreeSitterYaml",
            sources: ["src/parser.c", "src/scanner.c", "src/schema.core.c", "src/schema.json.c", "src/schema.legacy.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterYara",
            path: "Sources/Grammars/TreeSitterYara",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterYuck",
            path: "Sources/Grammars/TreeSitterYuck",
            sources: ["src/parser.c", "src/scanner.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        .target(
            name: "TreeSitterZig",
            path: "Sources/Grammars/TreeSitterZig",
            sources: ["src/parser.c"],
            publicHeadersPath: "include",
            cSettings: [.headerSearchPath("src")]
        ),

        // Syntax highlighting - NO grammars linked statically
        // All grammars loaded dynamically via DynamicGrammarLoader
        // Build grammars with: swift build --product TreeSitterSwift (etc)
        // Bundle .dylib files in app's Frameworks folder
        .target(
            name: "VVHighlighting",
            dependencies: [
                "SwiftTreeSitter",
            ],
            resources: [
                .copy("Resources/queries")
            ]
        ),

        // Git integration
        .target(
            name: "VVGit",
            dependencies: []
        ),

        // LSP support
        .target(
            name: "VVLSP",
            dependencies: [
                .product(name: "LanguageServerProtocol", package: "LanguageServerProtocol"),
            ]
        ),

        // Markdown rendering with Metal
        .target(
            name: "VVMetalPrimitives",
            dependencies: []
        ),

        // Markdown rendering with Metal
        .target(
            name: "VVMarkdown",
            dependencies: [
                .product(name: "Markdown", package: "swift-markdown"),
                "VVMetalPrimitives",
                "VVHighlighting",
            ],
            exclude: [
                "Docs"
            ],
            resources: [
                .process("Metal/MarkdownShaders.metal")
            ]
        ),
        .target(
            name: "VVChatTimeline",
            dependencies: [
                "VVMarkdown",
                "VVMetalPrimitives",
            ]
        ),
        .executableTarget(
            name: "VVDevKitPlayground",
            dependencies: [
                "VVCode",
                "VVMarkdown",
                "VVChatTimeline",
                "VVMetalPrimitives"
            ],
            path: "Examples/VVDevKitPlayground"
        ),

        // Tests
        .testTarget(
            name: "VVCodeTests",
            dependencies: ["VVCode", "VVGit", "VVHighlighting"]
        ),
        .testTarget(
            name: "VVChatTimelineTests",
            dependencies: ["VVChatTimeline"]
        ),
        .testTarget(
            name: "VVMetalPrimitivesTests",
            dependencies: ["VVMetalPrimitives"]
        ),
    ]
)
