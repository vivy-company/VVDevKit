//  MarkdownCodeHighlighter.swift
//  VVMarkdown
//
//  Syntax highlighting for code blocks using VVHighlighting

import Foundation
import VVHighlighting
import simd

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

// MARK: - Highlighted Code Token

public struct HighlightedCodeToken: Sendable {
    public let text: String
    public let range: NSRange
    public let color: SIMD4<Float>
    public let isBold: Bool
    public let isItalic: Bool

    public init(text: String, range: NSRange, color: SIMD4<Float>, isBold: Bool = false, isItalic: Bool = false) {
        self.text = text
        self.range = range
        self.color = color
        self.isBold = isBold
        self.isItalic = isItalic
    }
}

// MARK: - Highlighted Code Block

public struct HighlightedCodeBlock: Sendable {
    public let code: String
    public let language: String?
    public let tokens: [HighlightedCodeToken]
    public let lines: [HighlightedCodeLine]

    public init(code: String, language: String?, tokens: [HighlightedCodeToken]) {
        self.code = code
        self.language = language
        self.tokens = tokens
        self.lines = Self.splitIntoLines(code: code, tokens: tokens)
    }

    private static func splitIntoLines(code: String, tokens: [HighlightedCodeToken]) -> [HighlightedCodeLine] {
        let lineStrings = code.components(separatedBy: "\n")
        var lines: [HighlightedCodeLine] = []
        var currentOffset = 0

        for (lineIndex, lineString) in lineStrings.enumerated() {
            let lineRange = NSRange(location: currentOffset, length: lineString.utf16.count)
            var lineTokens: [HighlightedCodeToken] = []

            for token in tokens {
                let intersection = NSIntersectionRange(token.range, lineRange)
                if intersection.length > 0 {
                    let localStart = intersection.location - currentOffset
                    let localRange = NSRange(location: localStart, length: intersection.length)

                    if let range = Range(localRange, in: lineString) {
                        let tokenText = String(lineString[range])
                        lineTokens.append(HighlightedCodeToken(
                            text: tokenText,
                            range: localRange,
                            color: token.color,
                            isBold: token.isBold,
                            isItalic: token.isItalic
                        ))
                    }
                }
            }

            lines.append(HighlightedCodeLine(
                lineNumber: lineIndex + 1,
                text: lineString,
                tokens: lineTokens
            ))

            currentOffset += lineString.utf16.count + 1
        }

        return lines
    }
}

// MARK: - Highlighted Code Line

public struct HighlightedCodeLine: Sendable {
    public let lineNumber: Int
    public let text: String
    public let tokens: [HighlightedCodeToken]

    public init(lineNumber: Int, text: String, tokens: [HighlightedCodeToken]) {
        self.lineNumber = lineNumber
        self.text = text
        self.tokens = tokens
    }
}

// MARK: - Markdown Code Highlighter

public actor MarkdownCodeHighlighter {

    // MARK: - Properties

    private var highlighters: [String: TreeSitterHighlighter] = [:]
    private var defaultColor: SIMD4<Float>
    private var theme: HighlightTheme

    // Language aliases for common markdown code fence labels
    private static let languageAliases: [String: String] = [
        "js": "javascript",
        "ts": "typescript",
        "py": "python",
        "rb": "ruby",
        "rs": "rust",
        "sh": "bash",
        "shell": "bash",
        "zsh": "bash",
        "yml": "yaml",
        "md": "markdown",
        "objc": "objective-c",
        "objective-c": "c",
        "c++": "cpp",
        "h": "c",
        "hpp": "cpp",
        "m": "c",
        "mm": "cpp",
        "cs": "c",
        "dockerfile": "dockerfile",
        "docker": "dockerfile",
        "makefile": "make",
        "cmake": "make",
        "asm": "nasm",
        "assembly": "nasm",
        "tex": "latex",
        "plaintext": "",
        "text": "",
        "plain": "",
    ]

    // MARK: - Initialization

    public init(theme: HighlightTheme = .defaultDark, defaultColor: SIMD4<Float> = SIMD4(0.85, 0.85, 0.85, 1.0)) {
        self.theme = theme
        self.defaultColor = defaultColor
    }

    // MARK: - Public API

    public func highlight(code: String, language: String?) async -> HighlightedCodeBlock {
        guard let lang = language?.lowercased(), !lang.isEmpty else {
            return HighlightedCodeBlock(code: code, language: language, tokens: defaultTokens(for: code))
        }

        let resolvedLanguage = Self.languageAliases[lang] ?? lang

        if resolvedLanguage.isEmpty {
            return HighlightedCodeBlock(code: code, language: language, tokens: defaultTokens(for: code))
        }

        do {
            let highlighter = try await getOrCreateHighlighter(for: resolvedLanguage)
            _ = try await highlighter.parse(code)
            let highlights = try await highlighter.allHighlights()

            var tokens: [HighlightedCodeToken] = []

            for highlight in highlights {
                let style = theme.style(for: highlight.capture)
                let color = simdColor(from: style.color)

                if let range = Range(highlight.range, in: code) {
                    let tokenText = String(code[range])
                    tokens.append(HighlightedCodeToken(
                        text: tokenText,
                        range: highlight.range,
                        color: color,
                        isBold: style.isBold,
                        isItalic: style.isItalic
                    ))
                }
            }

            if tokens.isEmpty {
                return HighlightedCodeBlock(code: code, language: language, tokens: defaultTokens(for: code))
            }

            let mergedTokens = mergeAndFillGaps(tokens: tokens, code: code)
            return HighlightedCodeBlock(code: code, language: language, tokens: mergedTokens)

        } catch {
            return HighlightedCodeBlock(code: code, language: language, tokens: defaultTokens(for: code))
        }
    }

    public func updateTheme(_ theme: HighlightTheme) {
        self.theme = theme
        for highlighter in highlighters.values {
            Task {
                await highlighter.setTheme(theme)
            }
        }
    }

    // MARK: - Private Methods

    private func getOrCreateHighlighter(for language: String) async throws -> TreeSitterHighlighter {
        if let existing = highlighters[language] {
            return existing
        }

        let highlighter = TreeSitterHighlighter(theme: theme)

        if let config = LanguageRegistry.configuration(for: language) {
            try await highlighter.setLanguage(config)
            highlighters[language] = highlighter
            return highlighter
        }

        throw HighlighterError.languageNotSupported(language)
    }

    private func defaultTokens(for code: String) -> [HighlightedCodeToken] {
        return [HighlightedCodeToken(
            text: code,
            range: NSRange(location: 0, length: code.utf16.count),
            color: defaultColor
        )]
    }

    private func mergeAndFillGaps(tokens: [HighlightedCodeToken], code: String) -> [HighlightedCodeToken] {
        guard !tokens.isEmpty else { return defaultTokens(for: code) }

        let sorted = tokens.sorted { $0.range.location < $1.range.location }
        var result: [HighlightedCodeToken] = []
        var lastEnd = 0

        for token in sorted {
            if token.range.location > lastEnd {
                let gapRange = NSRange(location: lastEnd, length: token.range.location - lastEnd)
                if let range = Range(gapRange, in: code) {
                    let gapText = String(code[range])
                    result.append(HighlightedCodeToken(
                        text: gapText,
                        range: gapRange,
                        color: defaultColor
                    ))
                }
            }

            result.append(token)
            lastEnd = token.range.location + token.range.length
        }

        let codeLength = code.utf16.count
        if lastEnd < codeLength {
            let gapRange = NSRange(location: lastEnd, length: codeLength - lastEnd)
            if let range = Range(gapRange, in: code) {
                let gapText = String(code[range])
                result.append(HighlightedCodeToken(
                    text: gapText,
                    range: gapRange,
                    color: defaultColor
                ))
            }
        }

        return result
    }

    private func simdColor(from color: VVColor) -> SIMD4<Float> {
        #if canImport(AppKit)
        let converted = color.usingColorSpace(.sRGB) ?? color
        var r: CGFloat = 0, g: CGFloat = 0, b: CGFloat = 0, a: CGFloat = 0
        converted.getRed(&r, green: &g, blue: &b, alpha: &a)
        return SIMD4<Float>(Float(r), Float(g), Float(b), Float(a))
        #else
        var r: CGFloat = 0, g: CGFloat = 0, b: CGFloat = 0, a: CGFloat = 0
        color.getRed(&r, green: &g, blue: &b, alpha: &a)
        return SIMD4<Float>(Float(r), Float(g), Float(b), Float(a))
        #endif
    }
}

// MARK: - Errors

public enum HighlighterError: Error {
    case languageNotSupported(String)
    case parsingFailed
}
