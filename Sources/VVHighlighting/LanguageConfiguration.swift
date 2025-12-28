import Foundation
import SwiftTreeSitter

/// Configuration for a language with tree-sitter support
public struct LanguageConfiguration: Sendable {
    /// Language identifier
    public let identifier: String

    /// Display name
    public let displayName: String

    /// The tree-sitter language
    public let language: Language

    /// Compiled queries for this language
    public let queries: [QueryType: Query]

    /// Query types used for highlighting
    public enum QueryType: Hashable, Sendable {
        case highlights
        case injections
        case locals
    }

    public init(
        identifier: String,
        displayName: String,
        language: Language,
        highlightQuery: String,
        injectionQuery: String? = nil,
        localsQuery: String? = nil
    ) throws {
        self.identifier = identifier
        self.displayName = displayName
        self.language = language

        var queries: [QueryType: Query] = [:]

        // Compile highlight query
        if !highlightQuery.isEmpty {
            do {
                queries[.highlights] = try Query(language: language, data: Data(highlightQuery.utf8))
            } catch {
                #if DEBUG
                print("Warning: Failed to compile highlight query for \(identifier): \(error)")
                #endif
            }
        }

        // Compile injection query if provided
        if let injection = injectionQuery, !injection.isEmpty {
            do {
                queries[.injections] = try Query(language: language, data: Data(injection.utf8))
            } catch {
                print("Warning: Failed to compile injection query for \(identifier): \(error)")
            }
        }

        // Compile locals query if provided
        if let locals = localsQuery, !locals.isEmpty {
            do {
                queries[.locals] = try Query(language: language, data: Data(locals.utf8))
            } catch {
                print("Warning: Failed to compile locals query for \(identifier): \(error)")
            }
        }

        self.queries = queries
    }
}
