#if os(macOS)
import AppKit
import SwiftUI
import VVCode

struct DiffPlaygroundView: View {
    @State private var selectedSampleID: String = DiffSamples.swiftRefactor.id
    @State private var renderStyle: VVDiffRenderStyle = .sideBySide
    @State private var useDarkTheme = true
    @State private var syntaxHighlightingEnabled = true
    @State private var wrapLinesEnabled = true
    @State private var fontSize: Double = 13

    private var theme: VVTheme {
        useDarkTheme ? .defaultDark : .defaultLight
    }

    private var configuration: VVConfiguration {
        var config = VVConfiguration.default
        config.font = NSFont.monospacedSystemFont(ofSize: fontSize, weight: .regular)
        config.showLineNumbers = true
        config.showGutter = true
        config.wrapLines = wrapLinesEnabled
        return config
    }

    private var selectedSample: DiffSample {
        DiffSamples.all.first(where: { $0.id == selectedSampleID }) ?? DiffSamples.all[0]
    }

    var body: some View {
        HSplitView {
            sidebar
            diffPane
        }
    }

    private var sidebar: some View {
        VStack(alignment: .leading, spacing: 0) {
            VStack(alignment: .leading, spacing: 12) {
                Picker("Style", selection: $renderStyle) {
                    Text("Side By Side").tag(VVDiffRenderStyle.sideBySide)
                    Text("Inline").tag(VVDiffRenderStyle.inline)
                }
                .pickerStyle(.segmented)

                Toggle("Dark Theme", isOn: $useDarkTheme)
                Toggle("Syntax Highlighting", isOn: $syntaxHighlightingEnabled)
                Toggle("Wrap Lines", isOn: $wrapLinesEnabled)

                HStack {
                    Text("Font")
                    Slider(value: $fontSize, in: 10...18, step: 1)
                    Text("\(Int(fontSize))")
                        .frame(width: 24, alignment: .trailing)
                }
            }
            .padding(12)

            Divider()

            List(DiffSamples.all, id: \.id, selection: $selectedSampleID) { sample in
                sampleRow(sample)
                    .tag(sample.id)
            }
            .listStyle(.sidebar)
        }
        .frame(minWidth: 220, idealWidth: 260, maxWidth: 320)
    }

    private func sampleRow(_ sample: DiffSample) -> some View {
        VStack(alignment: .leading, spacing: 3) {
            HStack(spacing: 6) {
                Text(sample.title)
                    .font(.system(size: 12, weight: .medium))
                    .lineLimit(1)
                if sample.isStressSample {
                    Text("Stress")
                        .font(.system(size: 9, weight: .semibold))
                        .foregroundStyle(Color.orange)
                        .padding(.horizontal, 6)
                        .padding(.vertical, 2)
                        .background(Color.orange.opacity(0.12), in: Capsule())
                }
            }
            Text(sample.subtitle)
                .font(.system(size: 10))
                .foregroundStyle(.secondary)
                .lineLimit(1)
        }
        .padding(.vertical, 2)
    }

    private var diffPane: some View {
        VStack(spacing: 0) {
            HStack(alignment: .top, spacing: 16) {
                VStack(alignment: .leading, spacing: 4) {
                    Text(selectedSample.title)
                        .font(.headline)
                    Text(selectedSample.subtitle)
                        .font(.caption)
                        .foregroundStyle(.secondary)
                    if let metrics = selectedSample.metrics {
                        Text(metrics)
                            .font(.caption2)
                            .foregroundStyle(.secondary)
                    }
                }

                Spacer()

                VStack(alignment: .trailing, spacing: 4) {
                    Text(renderStyle == .sideBySide ? "Side-by-side diff" : "Inline diff")
                        .font(.caption)
                        .foregroundStyle(.secondary)
                    Text(syntaxHighlightingEnabled ? "Highlighting on" : "Highlighting off")
                        .font(.caption)
                        .foregroundStyle(syntaxHighlightingEnabled ? .green : .secondary)
                }
            }
            .padding(.horizontal, 16)
            .padding(.vertical, 12)
            .background(Color(nsColor: .windowBackgroundColor))

            Divider()

            VVDiffView(unifiedDiff: selectedSample.diff)
                .renderStyle(renderStyle)
                .language(selectedSample.language)
                .syntaxHighlighting(syntaxHighlightingEnabled)
                .theme(theme)
                .configuration(configuration)
        }
    }
}

private struct DiffSample: Identifiable {
    let id: String
    let title: String
    let subtitle: String
    let language: VVLanguage?
    private let diffProvider: () -> String
    let metrics: String?
    let isStressSample: Bool

    var diff: String {
        diffProvider()
    }

    init(
        id: String,
        title: String,
        subtitle: String,
        language: VVLanguage?,
        diff: @escaping @autoclosure () -> String,
        metrics: String? = nil,
        isStressSample: Bool = false
    ) {
        self.id = id
        self.title = title
        self.subtitle = subtitle
        self.language = language
        self.diffProvider = diff
        self.metrics = metrics
        self.isStressSample = isStressSample
    }
}

private enum DiffSamples {
    static let all: [DiffSample] = [
        heavySwiftStress,
        swiftRefactor,
        multiFileChange,
        rustAddFunction,
        typescriptRename,
        pythonBugfix,
        newFile,
        deleteFile,
        largeHunk,
    ]

    static let heavySwiftStress: DiffSample = {
        let fileCount = 128
        let linesPerHunk = 30
        let totalRows = fileCount * (linesPerHunk * 3 + 5)
        return DiffSample(
            id: "heavy-swift-stress",
            title: "Heavy Swift Stress",
            subtitle: "128 files · \(totalRows.formatted()) diff rows",
            language: nil,
            diff: DiffStressFixtures.heavySwiftStressDiff,
            metrics: "Benchmark-scale unified diff with automatic Swift highlighting, large hunk bodies, and enough rows to test scroll/render behavior.",
            isStressSample: true
        )
    }()

    static let swiftRefactor = DiffSample(
        id: "swift-refactor",
        title: "Refactor greeting",
        subtitle: "Sources/Greeting.swift",
        language: .swift,
        diff: """
        diff --git a/Sources/Greeting.swift b/Sources/Greeting.swift
        index 1a2b3c4..5d6e7f8 100644
        --- a/Sources/Greeting.swift
        +++ b/Sources/Greeting.swift
        @@ -1,15 +1,19 @@
         import Foundation
        +import os.log

        -func greet(name: String) -> String {
        -    return "Hello, " + name + "!"
        +struct Greeting {
        +    let name: String
        +    let style: Style
        +
        +    enum Style {
        +        case formal
        +        case casual
        +    }
        +
        +    func render() -> String {
        +        switch style {
        +        case .formal:
        +            return "Good day, \\(name)."
        +        case .casual:
        +            return "Hey \\(name)!"
        +        }
        +    }
         }

        -func greetAll(names: [String]) -> [String] {
        -    var results: [String] = []
        -    for name in names {
        -        results.append(greet(name: name))
        -    }
        -    return results
        -}
        -
        -let message = greet(name: "World")
        -print(message)
        +let greeting = Greeting(name: "World", style: .casual)
        +print(greeting.render())
        """
    )

    static let multiFileChange = DiffSample(
        id: "multi-file",
        title: "Multi-file change",
        subtitle: "Config + Router + Tests",
        language: .swift,
        diff: """
        diff --git a/Sources/Config.swift b/Sources/Config.swift
        index aaa1111..bbb2222 100644
        --- a/Sources/Config.swift
        +++ b/Sources/Config.swift
        @@ -3,8 +3,10 @@
         struct Config {
             let apiURL: URL
             let timeout: TimeInterval
        +    let retryCount: Int

        -    static let production = Config(
        +    static func production(retries: Int = 3) -> Config {
        +        Config(
                 apiURL: URL(string: "https://api.example.com")!,
        -        timeout: 30
        -    )
        +            timeout: 30,
        +            retryCount: retries
        +        )
        +    }
         }
        diff --git a/Sources/Router.swift b/Sources/Router.swift
        index ccc3333..ddd4444 100644
        --- a/Sources/Router.swift
        +++ b/Sources/Router.swift
        @@ -8,6 +8,7 @@
         final class Router {
             private let config: Config
        +    private var currentRoute: String = "/"

             init(config: Config) {
                 self.config = config
        @@ -15,7 +16,11 @@

             func navigate(to path: String) {
        -        print("Navigating to \\(path)")
        +        guard path != currentRoute else {
        +            return
        +        }
        +        currentRoute = path
        +        print("Router: \\(currentRoute)")
             }
         }
        diff --git a/Tests/RouterTests.swift b/Tests/RouterTests.swift
        index eee5555..fff6666 100644
        --- a/Tests/RouterTests.swift
        +++ b/Tests/RouterTests.swift
        @@ -5,6 +5,13 @@
         final class RouterTests: XCTestCase {
             func testNavigate() {
        -        let router = Router(config: .production)
        +        let router = Router(config: .production())
                 router.navigate(to: "/home")
             }
        +
        +    func testDeduplicateNavigation() {
        +        let router = Router(config: .production())
        +        router.navigate(to: "/home")
        +        router.navigate(to: "/home")
        +        // Should only navigate once
        +    }
         }
        """
    )

    static let rustAddFunction = DiffSample(
        id: "rust-add",
        title: "Add cache layer",
        subtitle: "src/cache.rs",
        language: .rust,
        diff: """
        diff --git a/src/cache.rs b/src/cache.rs
        index 1111aaa..2222bbb 100644
        --- a/src/cache.rs
        +++ b/src/cache.rs
        @@ -1,8 +1,25 @@
         use std::collections::HashMap;
        +use std::time::{Duration, Instant};

        -pub struct Cache {
        -    data: HashMap<String, String>,
        +pub struct Cache<V> {
        +    data: HashMap<String, CacheEntry<V>>,
        +    ttl: Duration,
        +}
        +
        +struct CacheEntry<V> {
        +    value: V,
        +    inserted_at: Instant,
         }

        -impl Cache {
        -    pub fn new() -> Self {
        -        Cache { data: HashMap::new() }
        +impl<V: Clone> Cache<V> {
        +    pub fn new(ttl: Duration) -> Self {
        +        Cache {
        +            data: HashMap::new(),
        +            ttl,
        +        }
        +    }
        +
        +    pub fn get(&self, key: &str) -> Option<V> {
        +        self.data.get(key).and_then(|entry| {
        +            if entry.inserted_at.elapsed() < self.ttl {
        +                Some(entry.value.clone())
        +            } else {
        +                None
        +            }
        +        })
             }
         }
        """
    )

    static let typescriptRename = DiffSample(
        id: "ts-rename",
        title: "Rename handler",
        subtitle: "src/api/handler.ts",
        language: .typescript,
        diff: """
        diff --git a/src/api/handler.ts b/src/api/handler.ts
        index aaaa111..bbbb222 100644
        --- a/src/api/handler.ts
        +++ b/src/api/handler.ts
        @@ -1,12 +1,12 @@
        -import { Request, Response } from "express";
        +import { Request, Response, NextFunction } from "express";

        -export function handleRequest(req: Request, res: Response) {
        -  const userId = req.params.id;
        -  if (!userId) {
        -    res.status(400).json({ error: "Missing user ID" });
        +export async function handleUserRequest(req: Request, res: Response, next: NextFunction) {
        +  const userId = req.params.userId;
        +  if (!userId?.trim()) {
        +    res.status(400).json({ error: "User ID is required" });
             return;
           }

        -  const data = fetchUser(userId);
        -  res.json(data);
        +  const user = await fetchUser(userId);
        +  res.json({ user, timestamp: Date.now() });
         }
        """
    )

    static let pythonBugfix = DiffSample(
        id: "python-bugfix",
        title: "Fix off-by-one",
        subtitle: "utils/pagination.py",
        language: .python,
        diff: """
        diff --git a/utils/pagination.py b/utils/pagination.py
        index 3333aaa..4444bbb 100644
        --- a/utils/pagination.py
        +++ b/utils/pagination.py
        @@ -4,11 +4,11 @@

         def paginate(items: list, page: int, per_page: int = 20) -> dict:
        -    total = len(items)
        -    start = page * per_page
        +    total_items = len(items)
        +    start = (page - 1) * per_page
             end = start + per_page
        -    total_pages = total // per_page
        +    total_pages = math.ceil(total_items / per_page) if per_page > 0 else 0

             return {
        -        "items": items[start:end],
        +        "items": items[start:end] if start < total_items else [],
                 "page": page,
        -        "total_pages": total_pages,
        -        "total": total,
        +        "total_pages": total_pages,
        +        "total_items": total_items,
             }
        """
    )

    static let newFile = DiffSample(
        id: "new-file",
        title: "New file",
        subtitle: "Sources/Logger.swift",
        language: .swift,
        diff: """
        diff --git a/Sources/Logger.swift b/Sources/Logger.swift
        new file mode 100644
        index 0000000..abcdef1
        --- /dev/null
        +++ b/Sources/Logger.swift
        @@ -0,0 +1,22 @@
        +import Foundation
        +import os.log
        +
        +enum LogLevel: String {
        +    case debug = "DEBUG"
        +    case info = "INFO"
        +    case warning = "WARN"
        +    case error = "ERROR"
        +}
        +
        +struct Logger {
        +    let subsystem: String
        +    let category: String
        +
        +    func log(_ level: LogLevel, _ message: String) {
        +        let timestamp = ISO8601DateFormatter().string(from: Date())
        +        print("[\\(timestamp)] [\\(level.rawValue)] [\\(category)] \\(message)")
        +    }
        +
        +    func error(_ message: String) {
        +        log(.error, message)
        +    }
        +}
        """
    )

    static let deleteFile = DiffSample(
        id: "delete-file",
        title: "Delete legacy helper",
        subtitle: "Sources/LegacyHelper.swift",
        language: .swift,
        diff: """
        diff --git a/Sources/LegacyHelper.swift b/Sources/LegacyHelper.swift
        deleted file mode 100644
        index fedcba0..0000000
        --- a/Sources/LegacyHelper.swift
        +++ /dev/null
        @@ -1,18 +0,0 @@
        -import Foundation
        -
        -// MARK: - Deprecated helpers
        -
        -@available(*, deprecated, message: "Use Logger instead")
        -func legacyLog(_ message: String) {
        -    print("[LOG] \\(message)")
        -}
        -
        -@available(*, deprecated, message: "Use Config.production()")
        -func loadConfig() -> [String: Any] {
        -    return [
        -        "api_url": "https://api.example.com",
        -        "timeout": 30,
        -    ]
        -}
        -
        -let _legacyConfigCache = loadConfig()
        """
    )

    static let largeHunk = DiffSample(
        id: "large-hunk",
        title: "Rewrite parser",
        subtitle: "Sources/Parser/Tokenizer.swift",
        language: .swift,
        diff: """
        diff --git a/Sources/Parser/Tokenizer.swift b/Sources/Parser/Tokenizer.swift
        index 5555aaa..6666bbb 100644
        --- a/Sources/Parser/Tokenizer.swift
        +++ b/Sources/Parser/Tokenizer.swift
        @@ -1,30 +1,45 @@
         import Foundation

        -enum Token {
        +enum Token: Equatable {
             case identifier(String)
        -    case number(Int)
        +    case number(Double)
        +    case string(String)
             case symbol(Character)
        +    case keyword(String)
             case eof
         }

        -func tokenize(_ input: String) -> [Token] {
        -    var tokens: [Token] = []
        -    var index = input.startIndex
        -
        -    while index < input.endIndex {
        -        let ch = input[index]
        -
        -        if ch.isWhitespace {
        -            index = input.index(after: index)
        -            continue
        -        }
        -
        -        if ch.isLetter {
        -            var word = String(ch)
        -            index = input.index(after: index)
        -            while index < input.endIndex && input[index].isLetter {
        -                word.append(input[index])
        +struct Tokenizer {
        +    private let input: [Character]
        +    private var position: Int = 0
        +
        +    private static let keywords: Set<String> = [
        +        "let", "var", "func", "struct", "class", "enum",
        +        "if", "else", "guard", "return", "import",
        +    ]
        +
        +    init(source: String) {
        +        self.input = Array(source)
        +    }
        +
        +    mutating func tokenize() -> [Token] {
        +        var tokens: [Token] = []
        +
        +        while position < input.count {
        +            let ch = input[position]
        +
        +            if ch.isWhitespace {
        +                position += 1
        +                continue
        +            }
        +
        +            if ch.isLetter || ch == "_" {
        +                let word = readWhile { $0.isLetter || $0.isNumber || $0 == "_" }
        +                if Self.keywords.contains(word) {
        +                    tokens.append(.keyword(word))
        +                } else {
        +                    tokens.append(.identifier(word))
        +                }
        +            } else if ch.isNumber || ch == "." {
        +                let num = readWhile { $0.isNumber || $0 == "." || $0 == "_" }
        +                tokens.append(.number(Double(num) ?? 0))
        +            } else if ch == "\\"" {
        +                position += 1
        +                let str = readWhile { $0 != "\\"" }
        +                position += 1
        +                tokens.append(.string(str))
        +            } else {
        +                tokens.append(.symbol(ch))
        +                position += 1
        +            }
        +        }
        +
        +        tokens.append(.eof)
        +        return tokens
        +    }
        +
        +    private mutating func readWhile(_ predicate: (Character) -> Bool) -> String {
        +        var result = ""
        +        while position < input.count && predicate(input[position]) {
        +            result.append(input[position])
        +            position += 1
        +        }
        +        return result
        +    }
        +}
        @@ -32,19 +47,4 @@
        -                index = input.index(after: index)
        -            }
        -            tokens.append(.identifier(word))
        -        } else if ch.isNumber {
        -            var num = String(ch)
        -            index = input.index(after: index)
        -            while index < input.endIndex && input[index].isNumber {
        -                num.append(input[index])
        -                index = input.index(after: index)
        -            }
        -            tokens.append(.number(Int(num)!))
        -        } else {
        -            tokens.append(.symbol(ch))
        -            index = input.index(after: index)
        -        }
        -    }
        -
        -    tokens.append(.eof)
        -    return tokens
        -}
        +// Tokenizer rewritten as a struct with keyword support,
        +// double-precision numbers, and string literal parsing.
        +// See: https://docs.swift.org/swift-book/documentation/the-swift-programming-language/lexicalstructure
        +// Migration: replace `tokenize(input)` with `Tokenizer(source: input).tokenize()`
        """
    )

    fileprivate static func makeHeavySwiftStressDiff(fileCount: Int, linesPerHunk: Int) -> String {
        var lines: [String] = []
        lines.reserveCapacity(fileCount * (linesPerHunk * 3 + 8))

        for fileIndex in 0..<fileCount {
            let path = "Sources/Benchmark/File\(fileIndex).swift"
            lines.append("diff --git a/\(path) b/\(path)")
            lines.append("index 1111111..2222222 100644")
            lines.append("--- a/\(path)")
            lines.append("+++ b/\(path)")
            lines.append("@@ -1,\(linesPerHunk) +1,\(linesPerHunk) @@")
            var emitted = 0
            while emitted < linesPerHunk {
                let chunk = heavySwiftStressSeedBodies[(fileIndex + emitted) % heavySwiftStressSeedBodies.count]
                for line in chunk {
                    guard emitted < linesPerHunk else { break }
                    lines.append(
                        line
                            .replacingOccurrences(of: "__FILE__", with: "\(fileIndex)")
                            .replacingOccurrences(of: "__LINE__", with: "\(emitted)")
                            .replacingOccurrences(of: "__NEXT__", with: "\(emitted + 1)")
                    )
                    emitted += 1
                }
            }
        }

        return lines.joined(separator: "\n")
    }

    fileprivate static let heavySwiftStressSeedBodies: [[String]] = [
        [
            " import Foundation",
            "+import os.log",
            "-func greet(name: String) -> String {",
            "-    return \"Hello, \" + name + \"!\"",
            "+struct GreetingFormatter__FILE__ {",
            "+    func render(name: String, style: Greeting.Style) -> String {",
            "+        style == .formal ? \"Good day, \\(name).\" : \"Hey \\(name)!\"",
            "+    }",
            " }",
        ],
        [
            " struct AppConfig__FILE__ {",
            "-    static let apiBaseURL = URL(string: \"https://api.old.example.com\")!",
            "-    static let timeout: TimeInterval = 15",
            "+    static let apiBaseURL = URL(string: \"https://api.service.example.com/v2\")!",
            "+    static let timeout: TimeInterval = 30",
            "+    static let retryBudget = RetryBudget(maxAttempts: 3, backoff: .exponential(base: 0.25))",
            " }",
            " let currentTimeout__LINE__ = AppConfig__FILE__.timeout",
        ],
        [
            " enum Route__FILE__ {",
            "-    case profile(id: String)",
            "-    case settings",
            "+    case profile(id: String, tab: ProfileTab)",
            "+    case settings(section: SettingsSection = .general)",
            "+    case billing(invoiceID: String)",
            " }",
            " let route__LINE__ = Route__FILE__.settings(section: .notifications)",
        ],
        [
            " enum Token: Equatable {",
            "-    case number(Int)",
            "+    case number(Double)",
            "+    case string(String)",
            "+    case keyword(String)",
            " }",
            "-func tokenize(_ input: String) -> [Token] {",
            "+struct Tokenizer__FILE__ {",
            "+    mutating func tokenize() -> [Token] {",
        ],
        [
            " final class ParserCache__FILE__ {",
            "-    private var storage: [String: [Token]] = [:]",
            "+    private var storage: LRUCache<String, [Token]>(capacity: 256)",
            "+    private var accessLog: RingBuffer<String>(capacity: 64)",
            " }",
            "-func cachedTokens(for source: String) -> [Token]? { storage[source] }",
            "+func cachedTokens(for source: String) -> [Token]? {",
            "+    accessLog.append(\"lookup-__FILE__-__LINE__\")",
            "+    return storage[source]",
        ],
        [
            " @MainActor",
            "-func renderPreview() {",
            "-    renderer.renderSynchronously()",
            "+func renderPreview() async {",
            "+    let snapshot = await renderer.snapshot(for: .init(id: \"preview-__FILE__-__LINE__\"))",
            "+    await previewStore.apply(snapshot)",
            " }",
            " let previewID__NEXT__ = \"preview-__FILE__\"",
        ],
    ]
}

private enum DiffStressFixtures {
    static let heavySwiftStressDiff = DiffSamples.makeHeavySwiftStressDiff(fileCount: 128, linesPerHunk: 30)
}
#endif
