import AppKit

/// Theme configuration for syntax highlighting
public struct HighlightTheme: Sendable {
    /// Syntax colors mapped by capture name
    public var colors: [String: HighlightStyle]

    /// Default text color
    public var defaultColor: NSColor

    public init(colors: [String: HighlightStyle], defaultColor: NSColor = .textColor) {
        self.colors = colors
        self.defaultColor = defaultColor
    }

    /// Get style for a capture name with fallback chain
    public func style(for capture: String) -> HighlightStyle {
        // Try exact match
        if let style = colors[capture] {
            return style
        }

        // Walk up the hierarchy (e.g., "keyword.control.import" -> "keyword.control" -> "keyword")
        var current = capture
        while let dotIndex = current.lastIndex(of: ".") {
            current = String(current[..<dotIndex])
            if let style = colors[current] {
                return style
            }
        }

        // Fallback to default
        return HighlightStyle(color: defaultColor)
    }
}

// MARK: - Built-in Themes

extension HighlightTheme {
    /// Dark theme
    public static let defaultDark = HighlightTheme(
        colors: [
            // Keywords
            "keyword": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "keyword.function": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "keyword.type": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "keyword.modifier": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "keyword.conditional": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.repeat": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.return": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.exception": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.import": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.coroutine": HighlightStyle(color: NSColor(hex: "#C586C0")),
            // Helix-style keyword variants (keyword.control.*, keyword.storage.*, keyword.operator)
            "keyword.control": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.control.conditional": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.control.repeat": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.control.import": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.control.return": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.control.exception": HighlightStyle(color: NSColor(hex: "#C586C0")),
            "keyword.storage": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "keyword.storage.type": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "keyword.storage.modifier": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "keyword.operator": HighlightStyle(color: NSColor(hex: "#569CD6")),
            // Types
            "type": HighlightStyle(color: NSColor(hex: "#4EC9B0")),
            "type.builtin": HighlightStyle(color: NSColor(hex: "#4EC9B0")),
            "type.parameter": HighlightStyle(color: NSColor(hex: "#4EC9B0")),
            // Functions
            "function": HighlightStyle(color: NSColor(hex: "#DCDCAA")),
            "function.call": HighlightStyle(color: NSColor(hex: "#DCDCAA")),
            "function.method": HighlightStyle(color: NSColor(hex: "#DCDCAA")),
            "function.builtin": HighlightStyle(color: NSColor(hex: "#DCDCAA")),
            // Variables
            "variable": HighlightStyle(color: NSColor(hex: "#9CDCFE")),
            "variable.builtin": HighlightStyle(color: NSColor(hex: "#9CDCFE")),
            "variable.parameter": HighlightStyle(color: NSColor(hex: "#9CDCFE")),
            "variable.other.member": HighlightStyle(color: NSColor(hex: "#9CDCFE")),
            "property": HighlightStyle(color: NSColor(hex: "#9CDCFE")),
            // Literals
            "string": HighlightStyle(color: NSColor(hex: "#CE9178")),
            "string.regexp": HighlightStyle(color: NSColor(hex: "#D16969")),
            "number": HighlightStyle(color: NSColor(hex: "#B5CEA8")),
            "number.float": HighlightStyle(color: NSColor(hex: "#B5CEA8")),
            "boolean": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "constant": HighlightStyle(color: NSColor(hex: "#4FC1FF")),
            "constant.builtin": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "constant.builtin.boolean": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "constant.numeric": HighlightStyle(color: NSColor(hex: "#B5CEA8")),
            "constant.character.escape": HighlightStyle(color: NSColor(hex: "#D7BA7D")),
            // Other
            "comment": HighlightStyle(color: NSColor(hex: "#6A9955"), isItalic: true),
            "operator": HighlightStyle(color: NSColor(hex: "#D4D4D4")),
            "punctuation": HighlightStyle(color: NSColor(hex: "#D4D4D4")),
            "punctuation.bracket": HighlightStyle(color: NSColor(hex: "#D4D4D4")),
            "punctuation.delimiter": HighlightStyle(color: NSColor(hex: "#D4D4D4")),
            "punctuation.special": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "attribute": HighlightStyle(color: NSColor(hex: "#4EC9B0")),
            "tag": HighlightStyle(color: NSColor(hex: "#569CD6")),
            "namespace": HighlightStyle(color: NSColor(hex: "#4EC9B0")),
            "constructor": HighlightStyle(color: NSColor(hex: "#4EC9B0")),
            "embedded": HighlightStyle(color: NSColor(hex: "#D4D4D4")),
            // Markup
            "markup.heading": HighlightStyle(color: NSColor(hex: "#569CD6"), isBold: true),
            "markup.bold": HighlightStyle(color: NSColor(hex: "#D4D4D4"), isBold: true),
            "markup.italic": HighlightStyle(color: NSColor(hex: "#D4D4D4"), isItalic: true),
            "markup.link": HighlightStyle(color: NSColor(hex: "#CE9178"), isUnderlined: true),
            "markup.raw": HighlightStyle(color: NSColor(hex: "#CE9178")),
        ],
        defaultColor: NSColor(hex: "#D4D4D4")
    )

    /// Light theme
    public static let defaultLight = HighlightTheme(
        colors: [
            // Keywords
            "keyword": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "keyword.function": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "keyword.type": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "keyword.modifier": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "keyword.conditional": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.repeat": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.return": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.exception": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.import": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.coroutine": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            // Helix-style keyword variants
            "keyword.control": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.control.conditional": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.control.repeat": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.control.import": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.control.return": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.control.exception": HighlightStyle(color: NSColor(hex: "#AF00DB")),
            "keyword.storage": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "keyword.storage.type": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "keyword.storage.modifier": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "keyword.operator": HighlightStyle(color: NSColor(hex: "#0000FF")),
            // Types
            "type": HighlightStyle(color: NSColor(hex: "#267F99")),
            "type.builtin": HighlightStyle(color: NSColor(hex: "#267F99")),
            "type.parameter": HighlightStyle(color: NSColor(hex: "#267F99")),
            // Functions
            "function": HighlightStyle(color: NSColor(hex: "#795E26")),
            "function.call": HighlightStyle(color: NSColor(hex: "#795E26")),
            "function.method": HighlightStyle(color: NSColor(hex: "#795E26")),
            "function.builtin": HighlightStyle(color: NSColor(hex: "#795E26")),
            // Variables
            "variable": HighlightStyle(color: NSColor(hex: "#001080")),
            "variable.builtin": HighlightStyle(color: NSColor(hex: "#001080")),
            "variable.parameter": HighlightStyle(color: NSColor(hex: "#001080")),
            "variable.other.member": HighlightStyle(color: NSColor(hex: "#001080")),
            "property": HighlightStyle(color: NSColor(hex: "#001080")),
            // Literals
            "string": HighlightStyle(color: NSColor(hex: "#A31515")),
            "string.regexp": HighlightStyle(color: NSColor(hex: "#811F3F")),
            "number": HighlightStyle(color: NSColor(hex: "#098658")),
            "number.float": HighlightStyle(color: NSColor(hex: "#098658")),
            "boolean": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "constant": HighlightStyle(color: NSColor(hex: "#0070C1")),
            "constant.builtin": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "constant.builtin.boolean": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "constant.numeric": HighlightStyle(color: NSColor(hex: "#098658")),
            "constant.character.escape": HighlightStyle(color: NSColor(hex: "#EE0000")),
            // Other
            "comment": HighlightStyle(color: NSColor(hex: "#008000"), isItalic: true),
            "operator": HighlightStyle(color: NSColor(hex: "#000000")),
            "punctuation": HighlightStyle(color: NSColor(hex: "#000000")),
            "punctuation.bracket": HighlightStyle(color: NSColor(hex: "#000000")),
            "punctuation.delimiter": HighlightStyle(color: NSColor(hex: "#000000")),
            "punctuation.special": HighlightStyle(color: NSColor(hex: "#0000FF")),
            "attribute": HighlightStyle(color: NSColor(hex: "#267F99")),
            "tag": HighlightStyle(color: NSColor(hex: "#800000")),
            "namespace": HighlightStyle(color: NSColor(hex: "#267F99")),
            "constructor": HighlightStyle(color: NSColor(hex: "#267F99")),
            "embedded": HighlightStyle(color: NSColor(hex: "#000000")),
            // Markup
            "markup.heading": HighlightStyle(color: NSColor(hex: "#0000FF"), isBold: true),
            "markup.bold": HighlightStyle(color: NSColor(hex: "#000000"), isBold: true),
            "markup.italic": HighlightStyle(color: NSColor(hex: "#000000"), isItalic: true),
            "markup.link": HighlightStyle(color: NSColor(hex: "#A31515"), isUnderlined: true),
            "markup.raw": HighlightStyle(color: NSColor(hex: "#A31515")),
        ],
        defaultColor: NSColor(hex: "#000000")
    )
}

// MARK: - NSColor Hex Extension (for VVHighlighting)

extension NSColor {
    convenience init(hex: String) {
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
