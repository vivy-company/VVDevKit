//  MarkdownMathRenderer.swift
//  VVMarkdown
//
//  LaTeX math symbol parsing and rendering

import Foundation
import CoreText
import CoreGraphics
import simd

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

// MARK: - Math Token

public enum MathToken: Sendable, Equatable {
    case text(String)
    case symbol(String, MathSymbol)
    case superscript([MathToken])
    case `subscript`([MathToken])
    case fraction(numerator: [MathToken], denominator: [MathToken])
    case sqrt([MathToken])
    case group([MathToken])
    case space(CGFloat)
    case delimiter(String)
}

// MARK: - Math Symbol

public struct MathSymbol: Sendable, Equatable {
    public let command: String
    public let unicode: String
    public let category: MathCategory

    public init(command: String, unicode: String, category: MathCategory) {
        self.command = command
        self.unicode = unicode
        self.category = category
    }
}

// MARK: - Math Category

public enum MathCategory: Sendable, Equatable {
    case greekLower
    case greekUpper
    case operator_
    case relation
    case arrow
    case misc
    case accent
    case function
    case delimiter
}

// MARK: - Rendered Math

public struct RenderedMath: Sendable {
    public let tokens: [MathToken]
    public let displayText: String
    public let isBlock: Bool
    public let baselineOffset: CGFloat

    public init(tokens: [MathToken], displayText: String, isBlock: Bool, baselineOffset: CGFloat = 0) {
        self.tokens = tokens
        self.displayText = displayText
        self.isBlock = isBlock
        self.baselineOffset = baselineOffset
    }
}

// MARK: - Math Glyph Run

public struct MathGlyphRun: Sendable {
    public let text: String
    public let position: CGPoint
    public let fontSize: CGFloat
    public let color: SIMD4<Float>
    public let isItalic: Bool

    public init(text: String, position: CGPoint, fontSize: CGFloat, color: SIMD4<Float>, isItalic: Bool = true) {
        self.text = text
        self.position = position
        self.fontSize = fontSize
        self.color = color
        self.isItalic = isItalic
    }
}

// MARK: - Markdown Math Renderer

public final class MarkdownMathRenderer: @unchecked Sendable {

    // MARK: - Symbol Table

    private static let symbolTable: [String: MathSymbol] = {
        var table: [String: MathSymbol] = [:]

        // Greek lowercase
        let greekLower: [(String, String)] = [
            ("alpha", "\u{03B1}"), ("beta", "\u{03B2}"), ("gamma", "\u{03B3}"),
            ("delta", "\u{03B4}"), ("epsilon", "\u{03B5}"), ("varepsilon", "\u{03F5}"),
            ("zeta", "\u{03B6}"), ("eta", "\u{03B7}"), ("theta", "\u{03B8}"),
            ("vartheta", "\u{03D1}"), ("iota", "\u{03B9}"), ("kappa", "\u{03BA}"),
            ("lambda", "\u{03BB}"), ("mu", "\u{03BC}"), ("nu", "\u{03BD}"),
            ("xi", "\u{03BE}"), ("pi", "\u{03C0}"), ("varpi", "\u{03D6}"),
            ("rho", "\u{03C1}"), ("varrho", "\u{03F1}"), ("sigma", "\u{03C3}"),
            ("varsigma", "\u{03C2}"), ("tau", "\u{03C4}"), ("upsilon", "\u{03C5}"),
            ("phi", "\u{03C6}"), ("varphi", "\u{03D5}"), ("chi", "\u{03C7}"),
            ("psi", "\u{03C8}"), ("omega", "\u{03C9}"),
        ]
        for (cmd, uni) in greekLower {
            table[cmd] = MathSymbol(command: cmd, unicode: uni, category: .greekLower)
        }

        // Greek uppercase
        let greekUpper: [(String, String)] = [
            ("Gamma", "\u{0393}"), ("Delta", "\u{0394}"), ("Theta", "\u{0398}"),
            ("Lambda", "\u{039B}"), ("Xi", "\u{039E}"), ("Pi", "\u{03A0}"),
            ("Sigma", "\u{03A3}"), ("Upsilon", "\u{03A5}"), ("Phi", "\u{03A6}"),
            ("Psi", "\u{03A8}"), ("Omega", "\u{03A9}"),
        ]
        for (cmd, uni) in greekUpper {
            table[cmd] = MathSymbol(command: cmd, unicode: uni, category: .greekUpper)
        }

        // Operators
        let operators: [(String, String)] = [
            ("pm", "\u{00B1}"), ("mp", "\u{2213}"), ("times", "\u{00D7}"),
            ("div", "\u{00F7}"), ("cdot", "\u{22C5}"), ("ast", "\u{2217}"),
            ("star", "\u{22C6}"), ("circ", "\u{2218}"), ("bullet", "\u{2219}"),
            ("oplus", "\u{2295}"), ("ominus", "\u{2296}"), ("otimes", "\u{2297}"),
            ("oslash", "\u{2298}"), ("odot", "\u{2299}"), ("cap", "\u{2229}"),
            ("cup", "\u{222A}"), ("vee", "\u{2228}"), ("wedge", "\u{2227}"),
            ("setminus", "\u{2216}"), ("nabla", "\u{2207}"), ("partial", "\u{2202}"),
            ("sum", "\u{2211}"), ("prod", "\u{220F}"), ("coprod", "\u{2210}"),
            ("int", "\u{222B}"), ("oint", "\u{222E}"), ("iint", "\u{222C}"),
            ("iiint", "\u{222D}"), ("sqrt", "\u{221A}"), ("infty", "\u{221E}"),
        ]
        for (cmd, uni) in operators {
            table[cmd] = MathSymbol(command: cmd, unicode: uni, category: .operator_)
        }

        // Relations
        let relations: [(String, String)] = [
            ("leq", "\u{2264}"), ("le", "\u{2264}"), ("geq", "\u{2265}"), ("ge", "\u{2265}"),
            ("neq", "\u{2260}"), ("ne", "\u{2260}"), ("approx", "\u{2248}"),
            ("equiv", "\u{2261}"), ("sim", "\u{223C}"), ("simeq", "\u{2243}"),
            ("cong", "\u{2245}"), ("propto", "\u{221D}"), ("prec", "\u{227A}"),
            ("succ", "\u{227B}"), ("preceq", "\u{2AAF}"), ("succeq", "\u{2AB0}"),
            ("ll", "\u{226A}"), ("gg", "\u{226B}"), ("subset", "\u{2282}"),
            ("supset", "\u{2283}"), ("subseteq", "\u{2286}"), ("supseteq", "\u{2287}"),
            ("in", "\u{2208}"), ("notin", "\u{2209}"), ("ni", "\u{220B}"),
            ("forall", "\u{2200}"), ("exists", "\u{2203}"), ("nexists", "\u{2204}"),
            ("perp", "\u{22A5}"), ("parallel", "\u{2225}"), ("mid", "\u{2223}"),
        ]
        for (cmd, uni) in relations {
            table[cmd] = MathSymbol(command: cmd, unicode: uni, category: .relation)
        }

        // Arrows
        let arrows: [(String, String)] = [
            ("leftarrow", "\u{2190}"), ("rightarrow", "\u{2192}"), ("to", "\u{2192}"),
            ("uparrow", "\u{2191}"), ("downarrow", "\u{2193}"),
            ("leftrightarrow", "\u{2194}"), ("updownarrow", "\u{2195}"),
            ("Leftarrow", "\u{21D0}"), ("Rightarrow", "\u{21D2}"),
            ("Uparrow", "\u{21D1}"), ("Downarrow", "\u{21D3}"),
            ("Leftrightarrow", "\u{21D4}"), ("Updownarrow", "\u{21D5}"),
            ("mapsto", "\u{21A6}"), ("longmapsto", "\u{27FC}"),
            ("longrightarrow", "\u{27F6}"), ("longleftarrow", "\u{27F5}"),
            ("hookleftarrow", "\u{21A9}"), ("hookrightarrow", "\u{21AA}"),
            ("nearrow", "\u{2197}"), ("searrow", "\u{2198}"),
            ("swarrow", "\u{2199}"), ("nwarrow", "\u{2196}"),
        ]
        for (cmd, uni) in arrows {
            table[cmd] = MathSymbol(command: cmd, unicode: uni, category: .arrow)
        }

        // Misc symbols
        let misc: [(String, String)] = [
            ("aleph", "\u{2135}"), ("beth", "\u{2136}"), ("gimel", "\u{2137}"),
            ("hbar", "\u{210F}"), ("ell", "\u{2113}"), ("wp", "\u{2118}"),
            ("Re", "\u{211C}"), ("Im", "\u{2111}"), ("emptyset", "\u{2205}"),
            ("varnothing", "\u{2205}"), ("angle", "\u{2220}"), ("triangle", "\u{25B3}"),
            ("square", "\u{25A1}"), ("diamond", "\u{25C7}"), ("clubsuit", "\u{2663}"),
            ("diamondsuit", "\u{2666}"), ("heartsuit", "\u{2665}"), ("spadesuit", "\u{2660}"),
            ("flat", "\u{266D}"), ("natural", "\u{266E}"), ("sharp", "\u{266F}"),
            ("ldots", "\u{2026}"), ("cdots", "\u{22EF}"), ("vdots", "\u{22EE}"),
            ("ddots", "\u{22F1}"), ("prime", "\u{2032}"), ("backslash", "\\"),
            ("neg", "\u{00AC}"), ("lnot", "\u{00AC}"), ("top", "\u{22A4}"),
            ("bot", "\u{22A5}"), ("degree", "\u{00B0}"),
        ]
        for (cmd, uni) in misc {
            table[cmd] = MathSymbol(command: cmd, unicode: uni, category: .misc)
        }

        // Delimiters
        let delimiters: [(String, String)] = [
            ("langle", "\u{27E8}"), ("rangle", "\u{27E9}"),
            ("lfloor", "\u{230A}"), ("rfloor", "\u{230B}"),
            ("lceil", "\u{2308}"), ("rceil", "\u{2309}"),
            ("lbrace", "{"), ("rbrace", "}"),
            ("lbrack", "["), ("rbrack", "]"),
            ("vert", "|"), ("Vert", "\u{2016}"),
        ]
        for (cmd, uni) in delimiters {
            table[cmd] = MathSymbol(command: cmd, unicode: uni, category: .delimiter)
        }

        // Functions (rendered as text, not italic)
        let functions: [(String, String)] = [
            ("sin", "sin"), ("cos", "cos"), ("tan", "tan"),
            ("sec", "sec"), ("csc", "csc"), ("cot", "cot"),
            ("arcsin", "arcsin"), ("arccos", "arccos"), ("arctan", "arctan"),
            ("sinh", "sinh"), ("cosh", "cosh"), ("tanh", "tanh"),
            ("log", "log"), ("ln", "ln"), ("lg", "lg"),
            ("exp", "exp"), ("lim", "lim"), ("limsup", "lim sup"),
            ("liminf", "lim inf"), ("sup", "sup"), ("inf", "inf"),
            ("max", "max"), ("min", "min"), ("arg", "arg"),
            ("det", "det"), ("dim", "dim"), ("ker", "ker"),
            ("hom", "Hom"), ("deg", "deg"), ("gcd", "gcd"),
            ("mod", "mod"), ("Pr", "Pr"),
        ]
        for (cmd, text) in functions {
            table[cmd] = MathSymbol(command: cmd, unicode: text, category: .function)
        }

        return table
    }()

    // MARK: - Properties

    private var mathColor: SIMD4<Float>

    // MARK: - Initialization

    public init(mathColor: SIMD4<Float> = SIMD4(0.8, 0.6, 1.0, 1.0)) {
        self.mathColor = mathColor
    }

    // MARK: - Public API

    public func parse(latex: String, isBlock: Bool) -> RenderedMath {
        let tokens = tokenize(latex)
        let displayText = renderToText(tokens: tokens)
        return RenderedMath(tokens: tokens, displayText: displayText, isBlock: isBlock)
    }

    public func setMathColor(_ color: SIMD4<Float>) {
        self.mathColor = color
    }

    public func layoutMath(_ math: RenderedMath, at origin: CGPoint, fontSize: CGFloat) -> [MathGlyphRun] {
        var runs: [MathGlyphRun] = []
        var x = origin.x
        let y = origin.y

        layoutTokens(math.tokens, runs: &runs, x: &x, y: y, fontSize: fontSize, scriptLevel: 0)

        return runs
    }

    // MARK: - Tokenization

    private func tokenize(_ latex: String) -> [MathToken] {
        var tokens: [MathToken] = []
        var index = latex.startIndex

        while index < latex.endIndex {
            let char = latex[index]

            if char == "\\" {
                let (command, newIndex) = parseCommand(latex, from: index)
                index = newIndex

                if let symbol = Self.symbolTable[command] {
                    tokens.append(.symbol(command, symbol))
                } else if command == "frac" {
                    let (num, denIndex) = parseGroup(latex, from: index)
                    let (den, finalIndex) = parseGroup(latex, from: denIndex)
                    tokens.append(.fraction(numerator: tokenize(num), denominator: tokenize(den)))
                    index = finalIndex
                } else if command == "sqrt" {
                    let (content, newIdx) = parseGroup(latex, from: index)
                    tokens.append(.sqrt(tokenize(content)))
                    index = newIdx
                } else if command == "left" || command == "right" {
                    if index < latex.endIndex {
                        let delimChar = String(latex[index])
                        tokens.append(.delimiter(delimChar))
                        index = latex.index(after: index)
                    }
                } else if command == "," {
                    tokens.append(.space(0.17))
                } else if command == ";" {
                    tokens.append(.space(0.28))
                } else if command == ":" || command == ">" {
                    tokens.append(.space(0.22))
                } else if command == "!" {
                    tokens.append(.space(-0.17))
                } else if command == "quad" {
                    tokens.append(.space(1.0))
                } else if command == "qquad" {
                    tokens.append(.space(2.0))
                } else if command == " " {
                    tokens.append(.space(0.25))
                } else if command == "text" || command == "mathrm" || command == "textrm" {
                    let (content, newIdx) = parseGroup(latex, from: index)
                    tokens.append(.text(content))
                    index = newIdx
                } else {
                    tokens.append(.text("\\" + command))
                }

            } else if char == "^" {
                index = latex.index(after: index)
                let (content, newIdx) = parseGroupOrChar(latex, from: index)
                tokens.append(.superscript(tokenize(content)))
                index = newIdx

            } else if char == "_" {
                index = latex.index(after: index)
                let (content, newIdx) = parseGroupOrChar(latex, from: index)
                tokens.append(.subscript(tokenize(content)))
                index = newIdx

            } else if char == "{" {
                let (content, newIdx) = parseGroup(latex, from: index)
                tokens.append(.group(tokenize(content)))
                index = newIdx

            } else if char == "}" {
                index = latex.index(after: index)

            } else if char == " " || char == "\t" || char == "\n" {
                index = latex.index(after: index)

            } else {
                tokens.append(.text(String(char)))
                index = latex.index(after: index)
            }
        }

        return tokens
    }

    private func parseCommand(_ latex: String, from startIndex: String.Index) -> (String, String.Index) {
        var index = latex.index(after: startIndex)

        if index >= latex.endIndex {
            return ("", index)
        }

        let firstChar = latex[index]
        if !firstChar.isLetter {
            return (String(firstChar), latex.index(after: index))
        }

        var command = ""
        while index < latex.endIndex && latex[index].isLetter {
            command.append(latex[index])
            index = latex.index(after: index)
        }

        return (command, index)
    }

    private func parseGroup(_ latex: String, from startIndex: String.Index) -> (String, String.Index) {
        var index = startIndex

        while index < latex.endIndex && (latex[index] == " " || latex[index] == "\t") {
            index = latex.index(after: index)
        }

        guard index < latex.endIndex && latex[index] == "{" else {
            return ("", index)
        }

        index = latex.index(after: index)
        var depth = 1
        var content = ""

        while index < latex.endIndex && depth > 0 {
            let char = latex[index]
            if char == "{" {
                depth += 1
                content.append(char)
            } else if char == "}" {
                depth -= 1
                if depth > 0 {
                    content.append(char)
                }
            } else {
                content.append(char)
            }
            index = latex.index(after: index)
        }

        return (content, index)
    }

    private func parseGroupOrChar(_ latex: String, from startIndex: String.Index) -> (String, String.Index) {
        var index = startIndex

        while index < latex.endIndex && (latex[index] == " " || latex[index] == "\t") {
            index = latex.index(after: index)
        }

        guard index < latex.endIndex else {
            return ("", index)
        }

        if latex[index] == "{" {
            return parseGroup(latex, from: index)
        } else if latex[index] == "\\" {
            let (cmd, newIdx) = parseCommand(latex, from: index)
            return ("\\" + cmd, newIdx)
        } else {
            let char = String(latex[index])
            return (char, latex.index(after: index))
        }
    }

    // MARK: - Rendering

    private func renderToText(tokens: [MathToken]) -> String {
        var result = ""
        for token in tokens {
            switch token {
            case .text(let text):
                result += text
            case .symbol(_, let symbol):
                result += symbol.unicode
            case .superscript(let sub):
                result += renderToText(tokens: sub)
            case .subscript(let sub):
                result += renderToText(tokens: sub)
            case .fraction(let num, let den):
                result += "(" + renderToText(tokens: num) + "/" + renderToText(tokens: den) + ")"
            case .sqrt(let content):
                result += "\u{221A}(" + renderToText(tokens: content) + ")"
            case .group(let content):
                result += renderToText(tokens: content)
            case .space:
                result += " "
            case .delimiter(let d):
                result += d
            }
        }
        return result
    }

    private func layoutTokens(_ tokens: [MathToken], runs: inout [MathGlyphRun], x: inout CGFloat, y: CGFloat, fontSize: CGFloat, scriptLevel: Int) {
        let scaledSize = fontSize * pow(0.7, CGFloat(scriptLevel))
        let yOffset = scriptLevel > 0 ? (scriptLevel == 1 ? -fontSize * 0.4 : fontSize * 0.2) : 0

        for token in tokens {
            switch token {
            case .text(let text):
                runs.append(MathGlyphRun(
                    text: text,
                    position: CGPoint(x: x, y: y + yOffset),
                    fontSize: scaledSize,
                    color: mathColor,
                    isItalic: true
                ))
                x += estimateTextWidth(text, fontSize: scaledSize)

            case .symbol(_, let symbol):
                let isFunction = symbol.category == .function
                runs.append(MathGlyphRun(
                    text: symbol.unicode,
                    position: CGPoint(x: x, y: y + yOffset),
                    fontSize: scaledSize,
                    color: mathColor,
                    isItalic: !isFunction
                ))
                x += estimateTextWidth(symbol.unicode, fontSize: scaledSize)

            case .superscript(let sub):
                layoutTokens(sub, runs: &runs, x: &x, y: y - fontSize * 0.4, fontSize: fontSize, scriptLevel: scriptLevel + 1)

            case .subscript(let sub):
                layoutTokens(sub, runs: &runs, x: &x, y: y + fontSize * 0.2, fontSize: fontSize, scriptLevel: scriptLevel + 1)

            case .fraction(let num, let den):
                let numWidth = estimateTokensWidth(num, fontSize: scaledSize * 0.8)
                let denWidth = estimateTokensWidth(den, fontSize: scaledSize * 0.8)
                let fracWidth = max(numWidth, denWidth) + scaledSize * 0.4

                var numX = x + (fracWidth - numWidth) / 2
                layoutTokens(num, runs: &runs, x: &numX, y: y - scaledSize * 0.5 + yOffset, fontSize: scaledSize * 0.8, scriptLevel: scriptLevel)

                var denX = x + (fracWidth - denWidth) / 2
                layoutTokens(den, runs: &runs, x: &denX, y: y + scaledSize * 0.3 + yOffset, fontSize: scaledSize * 0.8, scriptLevel: scriptLevel)

                x += fracWidth

            case .sqrt(let content):
                runs.append(MathGlyphRun(
                    text: "\u{221A}",
                    position: CGPoint(x: x, y: y + yOffset),
                    fontSize: scaledSize,
                    color: mathColor,
                    isItalic: false
                ))
                x += estimateTextWidth("\u{221A}", fontSize: scaledSize)
                layoutTokens(content, runs: &runs, x: &x, y: y + yOffset, fontSize: scaledSize, scriptLevel: scriptLevel)

            case .group(let content):
                layoutTokens(content, runs: &runs, x: &x, y: y + yOffset, fontSize: fontSize, scriptLevel: scriptLevel)

            case .space(let em):
                x += scaledSize * em

            case .delimiter(let d):
                runs.append(MathGlyphRun(
                    text: d,
                    position: CGPoint(x: x, y: y + yOffset),
                    fontSize: scaledSize,
                    color: mathColor,
                    isItalic: false
                ))
                x += estimateTextWidth(d, fontSize: scaledSize)
            }
        }
    }

    private func estimateTextWidth(_ text: String, fontSize: CGFloat) -> CGFloat {
        return CGFloat(text.count) * fontSize * 0.6
    }

    private func estimateTokensWidth(_ tokens: [MathToken], fontSize: CGFloat) -> CGFloat {
        var width: CGFloat = 0
        for token in tokens {
            switch token {
            case .text(let text):
                width += estimateTextWidth(text, fontSize: fontSize)
            case .symbol(_, let symbol):
                width += estimateTextWidth(symbol.unicode, fontSize: fontSize)
            case .superscript(let sub), .subscript(let sub):
                width += estimateTokensWidth(sub, fontSize: fontSize * 0.7)
            case .fraction(let num, let den):
                let numW = estimateTokensWidth(num, fontSize: fontSize * 0.8)
                let denW = estimateTokensWidth(den, fontSize: fontSize * 0.8)
                width += max(numW, denW) + fontSize * 0.4
            case .sqrt(let content):
                width += estimateTextWidth("\u{221A}", fontSize: fontSize) + estimateTokensWidth(content, fontSize: fontSize)
            case .group(let content):
                width += estimateTokensWidth(content, fontSize: fontSize)
            case .space(let em):
                width += fontSize * em
            case .delimiter(let d):
                width += estimateTextWidth(d, fontSize: fontSize)
            }
        }
        return width
    }
}
