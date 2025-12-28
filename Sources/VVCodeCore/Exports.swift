// VVCodeCore - Core rendering components

import AppKit
import VVGit
import VVLSP

// Re-export types from dependencies
public typealias VVDiffHunk = VVGit.VVDiffHunk
public typealias VVLineGitStatus = VVGit.VVLineGitStatus
public typealias VVBlameInfo = VVGit.VVBlameInfo
public typealias VVTextPosition = VVLSP.VVTextPosition

// MARK: - Configuration

/// Editor configuration
public struct VVConfiguration: Equatable {
    // Display
    public var font: NSFont
    public var lineHeight: CGFloat
    public var showLineNumbers: Bool
    public var showGutter: Bool
    public var wrapLines: Bool

    // Git
    public var showGitGutter: Bool
    public var showInlineBlame: Bool
    public var blameDelay: TimeInterval

    // Performance
    public var viewportBufferLines: Int
    public var highlightChunkSize: Int
    public var enableAsyncHighlighting: Bool

    // Editing
    public var tabWidth: Int
    public var insertSpacesForTab: Bool
    public var autoIndent: Bool
    public var autoBrackets: Bool
    public var helixModeEnabled: Bool

    // Layout
    public var minimumGutterWidth: CGFloat

    public init(
        font: NSFont = .monospacedSystemFont(ofSize: 13, weight: .regular),
        lineHeight: CGFloat = 1.4,
        showLineNumbers: Bool = true,
        showGutter: Bool = true,
        wrapLines: Bool = false,
        showGitGutter: Bool = true,
        showInlineBlame: Bool = false,
        blameDelay: TimeInterval = 0.5,
        viewportBufferLines: Int = 50,
        highlightChunkSize: Int = 100,
        enableAsyncHighlighting: Bool = true,
        tabWidth: Int = 4,
        insertSpacesForTab: Bool = true,
        autoIndent: Bool = true,
        autoBrackets: Bool = true,
        helixModeEnabled: Bool = false,
        minimumGutterWidth: CGFloat = 40
    ) {
        self.font = font
        self.lineHeight = lineHeight
        self.showLineNumbers = showLineNumbers
        self.showGutter = showGutter
        self.wrapLines = wrapLines
        self.showGitGutter = showGitGutter
        self.showInlineBlame = showInlineBlame
        self.blameDelay = blameDelay
        self.viewportBufferLines = viewportBufferLines
        self.highlightChunkSize = highlightChunkSize
        self.enableAsyncHighlighting = enableAsyncHighlighting
        self.tabWidth = tabWidth
        self.insertSpacesForTab = insertSpacesForTab
        self.autoIndent = autoIndent
        self.autoBrackets = autoBrackets
        self.helixModeEnabled = helixModeEnabled
        self.minimumGutterWidth = minimumGutterWidth
    }

    public static let `default` = VVConfiguration()

    // MARK: - Builder Methods

    public func with(font: NSFont) -> VVConfiguration {
        var copy = self
        copy.font = font
        return copy
    }

    public func with(tabWidth: Int) -> VVConfiguration {
        var copy = self
        copy.tabWidth = tabWidth
        return copy
    }

    public func with(wrapLines: Bool) -> VVConfiguration {
        var copy = self
        copy.wrapLines = wrapLines
        return copy
    }

    public func with(lineHeight: CGFloat) -> VVConfiguration {
        var copy = self
        copy.lineHeight = lineHeight
        return copy
    }

    public func with(showLineNumbers: Bool) -> VVConfiguration {
        var copy = self
        copy.showLineNumbers = showLineNumbers
        return copy
    }

    public func with(showGutter: Bool) -> VVConfiguration {
        var copy = self
        copy.showGutter = showGutter
        return copy
    }

    public func with(showGitGutter: Bool) -> VVConfiguration {
        var copy = self
        copy.showGitGutter = showGitGutter
        return copy
    }

    public func with(helixModeEnabled: Bool) -> VVConfiguration {
        var copy = self
        copy.helixModeEnabled = helixModeEnabled
        return copy
    }

    public static func == (lhs: VVConfiguration, rhs: VVConfiguration) -> Bool {
        lhs.font == rhs.font &&
        lhs.lineHeight == rhs.lineHeight &&
        lhs.showLineNumbers == rhs.showLineNumbers &&
        lhs.showGutter == rhs.showGutter &&
        lhs.wrapLines == rhs.wrapLines &&
        lhs.showGitGutter == rhs.showGitGutter &&
        lhs.showInlineBlame == rhs.showInlineBlame &&
        lhs.tabWidth == rhs.tabWidth &&
        lhs.insertSpacesForTab == rhs.insertSpacesForTab &&
        lhs.autoIndent == rhs.autoIndent &&
        lhs.autoBrackets == rhs.autoBrackets &&
        lhs.helixModeEnabled == rhs.helixModeEnabled
    }
}

// MARK: - Theme

/// Editor theme
public struct VVTheme: Equatable, Hashable, Sendable {
    // Theme identifier for Hashable
    private let id: String

    public var backgroundColor: NSColor
    public var textColor: NSColor
    public var selectionColor: NSColor
    public var currentLineColor: NSColor
    public var gutterBackgroundColor: NSColor
    public var gutterTextColor: NSColor
    public var gutterActiveTextColor: NSColor
    public var gutterSeparatorColor: NSColor
    public var cursorColor: NSColor

    // Git gutter colors
    public var gitAddedColor: NSColor
    public var gitModifiedColor: NSColor
    public var gitDeletedColor: NSColor

    public func hash(into hasher: inout Hasher) {
        hasher.combine(id)
    }

    public init(
        id: String = UUID().uuidString,
        backgroundColor: NSColor = NSColor(hex: "#1E1E1E"),
        textColor: NSColor = NSColor(hex: "#D4D4D4"),
        selectionColor: NSColor = NSColor(hex: "#264F78"),
        currentLineColor: NSColor = NSColor(hex: "#282828"),
        gutterBackgroundColor: NSColor = NSColor(hex: "#1E1E1E"),
        gutterTextColor: NSColor = .secondaryLabelColor,
        gutterActiveTextColor: NSColor = .labelColor,
        gutterSeparatorColor: NSColor = .separatorColor,
        cursorColor: NSColor = .textColor,
        gitAddedColor: NSColor = .systemGreen,
        gitModifiedColor: NSColor = .systemBlue,
        gitDeletedColor: NSColor = .systemRed
    ) {
        self.id = id
        self.backgroundColor = backgroundColor
        self.textColor = textColor
        self.selectionColor = selectionColor
        self.currentLineColor = currentLineColor
        self.gutterBackgroundColor = gutterBackgroundColor
        self.gutterTextColor = gutterTextColor
        self.gutterActiveTextColor = gutterActiveTextColor
        self.gutterSeparatorColor = gutterSeparatorColor
        self.cursorColor = cursorColor
        self.gitAddedColor = gitAddedColor
        self.gitModifiedColor = gitModifiedColor
        self.gitDeletedColor = gitDeletedColor
    }

    public static let defaultDark = VVTheme(id: "defaultDark")

    public static let defaultLight = VVTheme(
        id: "defaultLight",
        backgroundColor: NSColor(hex: "#FFFFFF"),
        textColor: NSColor(hex: "#000000"),
        selectionColor: NSColor(hex: "#ADD6FF"),
        currentLineColor: NSColor(hex: "#F5F5F5"),
        gutterBackgroundColor: NSColor(hex: "#FFFFFF"),
        gutterTextColor: .secondaryLabelColor,
        gutterActiveTextColor: .labelColor,
        gutterSeparatorColor: .separatorColor,
        cursorColor: .textColor
    )
}

// MARK: - Language (simplified for VVCodeCore)

/// Language identifier for syntax highlighting
public struct VVLanguage: Hashable, Sendable, Identifiable {
    public var id: String { identifier }
    public let identifier: String
    public let displayName: String
    public let fileExtensions: [String]

    public init(identifier: String, displayName: String, fileExtensions: [String]) {
        self.identifier = identifier
        self.displayName = displayName
        self.fileExtensions = fileExtensions
    }

    public static func == (lhs: VVLanguage, rhs: VVLanguage) -> Bool {
        lhs.identifier == rhs.identifier
    }

    public func hash(into hasher: inout Hasher) {
        hasher.combine(identifier)
    }

    // MARK: - Bundled Languages

    public static let swift = VVLanguage(identifier: "swift", displayName: "Swift", fileExtensions: ["swift"])
    public static let rust = VVLanguage(identifier: "rust", displayName: "Rust", fileExtensions: ["rs"])
    public static let typescript = VVLanguage(identifier: "typescript", displayName: "TypeScript", fileExtensions: ["ts", "tsx"])
    public static let javascript = VVLanguage(identifier: "javascript", displayName: "JavaScript", fileExtensions: ["js", "jsx", "mjs"])
    public static let python = VVLanguage(identifier: "python", displayName: "Python", fileExtensions: ["py", "pyw"])
    public static let go = VVLanguage(identifier: "go", displayName: "Go", fileExtensions: ["go"])
    public static let c = VVLanguage(identifier: "c", displayName: "C", fileExtensions: ["c", "h"])
    public static let cpp = VVLanguage(identifier: "cpp", displayName: "C++", fileExtensions: ["cpp", "cc", "cxx", "hpp", "hh", "hxx"])
    public static let json = VVLanguage(identifier: "json", displayName: "JSON", fileExtensions: ["json"])
    public static let yaml = VVLanguage(identifier: "yaml", displayName: "YAML", fileExtensions: ["yaml", "yml"])
    public static let markdown = VVLanguage(identifier: "markdown", displayName: "Markdown", fileExtensions: ["md", "markdown"])
    public static let html = VVLanguage(identifier: "html", displayName: "HTML", fileExtensions: ["html", "htm"])
    public static let css = VVLanguage(identifier: "css", displayName: "CSS", fileExtensions: ["css"])
    public static let bash = VVLanguage(identifier: "bash", displayName: "Bash", fileExtensions: ["sh", "bash", "zsh"])
    public static let sql = VVLanguage(identifier: "sql", displayName: "SQL", fileExtensions: ["sql"])
    public static let toml = VVLanguage(identifier: "toml", displayName: "TOML", fileExtensions: ["toml"])
    public static let dockerfile = VVLanguage(identifier: "dockerfile", displayName: "Dockerfile", fileExtensions: ["dockerfile"])

    public static let allLanguages: [VVLanguage] = [
        .swift, .rust, .typescript, .javascript, .python, .go, .c, .cpp,
        .json, .yaml, .markdown, .html, .css, .bash, .sql, .toml, .dockerfile
    ]

    // MARK: - Detection

    public static func detect(from url: URL) -> VVLanguage? {
        let ext = url.pathExtension.lowercased()
        let filename = url.lastPathComponent.lowercased()

        // Check by filename first
        if filename == "dockerfile" || filename.hasPrefix("dockerfile.") {
            return .dockerfile
        }
        if filename == "makefile" || filename == "gnumakefile" {
            return .bash
        }

        // Check by extension
        return allLanguages.first { $0.fileExtensions.contains(ext) }
    }
}

// MARK: - NSColor Hex Extension

extension NSColor {
    public convenience init(hex: String) {
        var hexString = hex.trimmingCharacters(in: .whitespacesAndNewlines)
        if hexString.hasPrefix("#") {
            hexString.removeFirst()
        }

        var rgb: UInt64 = 0
        Scanner(string: hexString).scanHexInt64(&rgb)

        let r = CGFloat((rgb >> 16) & 0xFF) / 255.0
        let g = CGFloat((rgb >> 8) & 0xFF) / 255.0
        let b = CGFloat(rgb & 0xFF) / 255.0

        self.init(red: r, green: g, blue: b, alpha: 1.0)
    }
}
