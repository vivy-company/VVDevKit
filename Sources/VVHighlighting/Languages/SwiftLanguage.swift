import Foundation
import SwiftTreeSitter

/// Swift language configuration for syntax highlighting
public struct SwiftLanguage {
    /// Create Swift language configuration
    public static func configuration() throws -> LanguageConfiguration {
        guard let language = DynamicGrammarLoader.shared.loadLanguage("swift") else {
            throw LanguageError.grammarNotFound("swift")
        }
        let highlightsQuery = try loadHighlightsQuery()

        return try LanguageConfiguration(
            identifier: "swift",
            displayName: "Swift",
            language: language,
            highlightQuery: highlightsQuery
        )
    }

    private static func loadHighlightsQuery() throws -> String {
        #if SWIFT_PACKAGE
        guard let url = Bundle.module.url(
            forResource: "swift-highlights",
            withExtension: "scm",
            subdirectory: "queries"
        ) else {
            throw LanguageError.queryFileNotFound("swift-highlights.scm")
        }
        return try String(contentsOf: url, encoding: .utf8)
        #else
        throw LanguageError.queryFileNotFound("swift-highlights.scm - not in SPM")
        #endif
    }
}

public enum LanguageError: Error {
    case queryFileNotFound(String)
    case grammarNotFound(String)
}
