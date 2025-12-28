import AppKit
import Combine

/// Observable document model for VVCode editor
@MainActor
public final class VVDocument: ObservableObject {
    /// The text content of the document
    @Published public var text: String {
        didSet {
            guard text != oldValue else { return }
            syncTextStorage()
        }
    }

    /// The programming language for syntax highlighting
    @Published public var language: VVLanguage?

    /// The underlying text storage for direct manipulation (large files)
    public let textStorage: NSTextStorage

    /// Line count (updated on text change)
    @Published public private(set) var lineCount: Int = 1

    /// Whether the document has unsaved changes
    @Published public private(set) var isDirty: Bool = false

    /// File URL if loaded from disk
    public var fileURL: URL?

    private var isUpdatingFromStorage = false

    public init(text: String = "", language: VVLanguage? = nil) {
        self.text = text
        self.language = language
        self.textStorage = NSTextStorage(string: text)
        self.lineCount = Self.countLines(in: text)

        setupTextStorageObserver()
    }

    /// Initialize from file URL
    public convenience init(contentsOf url: URL, language: VVLanguage? = nil) throws {
        let text = try String(contentsOf: url, encoding: .utf8)
        let detectedLanguage = language ?? VVLanguage.detect(from: url)
        self.init(text: text, language: detectedLanguage)
        self.fileURL = url
    }

    /// Initialize with NSTextStorage for large files (avoids String copying)
    public init(textStorage: NSTextStorage, language: VVLanguage? = nil) {
        self.textStorage = textStorage
        self.text = textStorage.string
        self.language = language
        self.lineCount = Self.countLines(in: textStorage.string)

        setupTextStorageObserver()
    }

    deinit {
        NotificationCenter.default.removeObserver(self)
    }

    private func setupTextStorageObserver() {
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(textStorageDidChange(_:)),
            name: NSTextStorage.didProcessEditingNotification,
            object: textStorage
        )
    }

    @objc private func textStorageDidChange(_ notification: Notification) {
        guard !isUpdatingFromStorage else { return }
        isUpdatingFromStorage = true
        defer { isUpdatingFromStorage = false }

        let newText = textStorage.string
        if newText != text {
            text = newText
            lineCount = Self.countLines(in: newText)
            isDirty = true
        }
    }

    private func syncTextStorage() {
        guard !isUpdatingFromStorage else { return }
        isUpdatingFromStorage = true
        defer { isUpdatingFromStorage = false }

        textStorage.beginEditing()
        textStorage.replaceCharacters(
            in: NSRange(location: 0, length: textStorage.length),
            with: text
        )
        textStorage.endEditing()

        lineCount = Self.countLines(in: text)
        isDirty = true
    }

    /// Save document to its file URL
    public func save() throws {
        guard let url = fileURL else {
            throw VVDocumentError.noFileURL
        }
        try save(to: url)
    }

    /// Save document to a specific URL
    public func save(to url: URL) throws {
        try text.write(to: url, atomically: true, encoding: .utf8)
        fileURL = url
        isDirty = false
    }

    /// Reload document from disk
    public func reload() throws {
        guard let url = fileURL else {
            throw VVDocumentError.noFileURL
        }
        text = try String(contentsOf: url, encoding: .utf8)
        isDirty = false
    }

    private static func countLines(in text: String) -> Int {
        var count = 1
        text.enumerateSubstrings(in: text.startIndex..., options: .byLines) { _, _, _, _ in
            count += 1
        }
        return max(1, count - 1)
    }
}

public enum VVDocumentError: Error, LocalizedError {
    case noFileURL

    public var errorDescription: String? {
        switch self {
        case .noFileURL:
            return "Document has no associated file URL"
        }
    }
}
