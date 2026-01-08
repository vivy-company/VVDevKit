import Foundation

public enum SearchEngine {
    public struct Options {
        public var caseSensitive: Bool

        public init(caseSensitive: Bool = true) {
            self.caseSensitive = caseSensitive
        }
    }

    public static func findAllMatches(
        in text: String,
        query: String,
        options: Options = Options(),
        limit: Int? = nil
    ) -> [NSRange] {
        let (haystack, needle) = prepare(text: text, query: query, options: options)
        guard !needle.isEmpty, haystack.count >= needle.count else { return [] }

        let matches = bmhSearchAll(haystack: haystack, needle: needle, limit: limit)
        return matches.map { NSRange(location: $0, length: needle.count) }
    }

    public static func findNextMatch(
        in text: String,
        query: String,
        from start: Int,
        forward: Bool,
        options: Options = Options(),
        wrap: Bool = true
    ) -> NSRange? {
        let (haystack, needle) = prepare(text: text, query: query, options: options)
        guard !needle.isEmpty, haystack.count >= needle.count else { return nil }

        let clampedStart = max(0, min(start, haystack.count))
        if forward {
            if let match = bmhSearchFirst(haystack: haystack, needle: needle, start: min(clampedStart + 1, haystack.count)) {
                return NSRange(location: match, length: needle.count)
            }
            if wrap, let match = bmhSearchFirst(haystack: haystack, needle: needle, start: 0) {
                return NSRange(location: match, length: needle.count)
            }
        } else {
            if let match = bmhSearchLast(haystack: haystack, needle: needle, end: max(0, clampedStart - 1)) {
                return NSRange(location: match, length: needle.count)
            }
            if wrap, let match = bmhSearchLast(haystack: haystack, needle: needle, end: haystack.count - 1) {
                return NSRange(location: match, length: needle.count)
            }
        }

        return nil
    }

    // MARK: - Helpers

    private static func prepare(text: String, query: String, options: Options) -> ([UInt16], [UInt16]) {
        if options.caseSensitive {
            return (Array(text.utf16), Array(query.utf16))
        }
        let lowerText = text.lowercased()
        let lowerQuery = query.lowercased()
        return (Array(lowerText.utf16), Array(lowerQuery.utf16))
    }

    private static func bmhSkipTable(for needle: [UInt16]) -> [Int] {
        let m = needle.count
        var table = Array(repeating: m, count: 65536)
        guard m > 1 else { return table }
        for i in 0..<(m - 1) {
            table[Int(needle[i])] = m - 1 - i
        }
        return table
    }

    private static func bmhSearchAll(haystack: [UInt16], needle: [UInt16], limit: Int?) -> [Int] {
        let n = haystack.count
        let m = needle.count
        guard m > 0, n >= m else { return [] }

        let skip = bmhSkipTable(for: needle)
        var matches: [Int] = []
        matches.reserveCapacity(min(64, limit ?? 64))

        var i = 0
        while i <= n - m {
            var j = m - 1
            while j >= 0, needle[j] == haystack[i + j] {
                j -= 1
            }
            if j < 0 {
                matches.append(i)
                if let limit, matches.count >= limit { break }
                i += 1
            } else {
                let next = haystack[i + m - 1]
                i += max(1, skip[Int(next)])
            }
        }

        return matches
    }

    private static func bmhSearchFirst(haystack: [UInt16], needle: [UInt16], start: Int) -> Int? {
        let n = haystack.count
        let m = needle.count
        guard m > 0, n >= m, start <= n - m else { return nil }

        let skip = bmhSkipTable(for: needle)
        var i = start
        while i <= n - m {
            var j = m - 1
            while j >= 0, needle[j] == haystack[i + j] {
                j -= 1
            }
            if j < 0 {
                return i
            }
            let next = haystack[i + m - 1]
            i += max(1, skip[Int(next)])
        }

        return nil
    }

    private static func bmhSearchLast(haystack: [UInt16], needle: [UInt16], end: Int) -> Int? {
        let n = haystack.count
        let m = needle.count
        guard m > 0, n >= m else { return nil }

        let startIndex = max(0, min(end, n - 1))
        let windowEnd = min(startIndex, n - m)
        if windowEnd < 0 { return nil }

        // Scan forward up to windowEnd, keep last match.
        let skip = bmhSkipTable(for: needle)
        var i = 0
        var lastMatch: Int? = nil
        while i <= windowEnd {
            var j = m - 1
            while j >= 0, needle[j] == haystack[i + j] {
                j -= 1
            }
            if j < 0 {
                lastMatch = i
                i += 1
            } else {
                let next = haystack[i + m - 1]
                i += max(1, skip[Int(next)])
            }
        }

        return lastMatch
    }
}
