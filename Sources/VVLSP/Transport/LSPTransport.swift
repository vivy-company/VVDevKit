import Foundation
import LanguageServerProtocol

/// Handles JSON-RPC communication with a language server process
public actor LSPTransport {
    private let process: Process
    private let stdin: FileHandle
    private let stdout: FileHandle
    private let stderr: FileHandle

    private var requestId: Int = 0
    private var pendingRequests: [RequestID: CheckedContinuation<LSPAny, Error>] = [:]
    private var readTask: Task<Void, Never>?

    public enum TransportError: Error {
        case processNotRunning
        case invalidResponse
        case serverError(code: Int, message: String)
        case timeout
        case encodingError
        case decodingError(String)
    }

    /// Initialize transport with a running language server process
    public init(process: Process, stdin: FileHandle, stdout: FileHandle, stderr: FileHandle) {
        self.process = process
        self.stdin = stdin
        self.stdout = stdout
        self.stderr = stderr
    }

    /// Start reading responses from the server
    public func start(onNotification: @escaping @Sendable (ServerNotification) -> Void) {
        readTask = Task { [weak self] in
            guard let self = self else { return }
            await self.readLoop(onNotification: onNotification)
        }
    }

    /// Stop the transport
    public func stop() {
        readTask?.cancel()
        readTask = nil
        process.terminate()
    }

    /// Send a request and wait for response with timeout
    public func sendRequest<T: Codable>(_ method: String, params: T, timeout: TimeInterval = 30) async throws -> LSPAny {
        let id = nextRequestId()

        let request = JSONRPCRequest(
            id: .numericId(id),
            method: method,
            params: params
        )

        try await writeMessage(request)

        return try await withThrowingTaskGroup(of: LSPAny.self) { group in
            group.addTask {
                try await withCheckedThrowingContinuation { continuation in
                    Task { await self.registerContinuation(id: id, continuation: continuation) }
                }
            }

            group.addTask {
                try await Task.sleep(nanoseconds: UInt64(timeout * 1_000_000_000))
                throw TransportError.timeout
            }

            guard let result = try await group.next() else {
                throw TransportError.timeout
            }

            group.cancelAll()
            return result
        }
    }

    private func registerContinuation(id: Int, continuation: CheckedContinuation<LSPAny, Error>) {
        pendingRequests[.numericId(id)] = continuation
    }

    /// Send a notification (no response expected)
    public func sendNotification<T: Codable>(_ method: String, params: T) async throws {
        let notification = JSONRPCNotification(method: method, params: params)
        try await writeMessage(notification)
    }

    // MARK: - Private

    private func nextRequestId() -> Int {
        requestId += 1
        return requestId
    }

    private func writeMessage<T: Encodable>(_ message: T) async throws {
        let encoder = JSONEncoder()
        let data = try encoder.encode(message)

        let header = "Content-Length: \(data.count)\r\n\r\n"
        guard let headerData = header.data(using: .utf8) else {
            throw TransportError.encodingError
        }

        try stdin.write(contentsOf: headerData)
        try stdin.write(contentsOf: data)
    }

    private func readLoop(onNotification: @escaping @Sendable (ServerNotification) -> Void) async {
        var buffer = Data()

        // Capture file handles for use in closures
        let stdoutHandle = stdout
        let stderrHandle = stderr

        // Use readability handler for non-blocking reads
        let stream = AsyncStream<Data> { continuation in
            stdoutHandle.readabilityHandler = { handle in
                let data = handle.availableData
                if data.isEmpty {
                    continuation.finish()
                } else {
                    continuation.yield(data)
                }
            }

            continuation.onTermination = { @Sendable _ in
                stdoutHandle.readabilityHandler = nil
            }
        }

        // Silently consume stderr
        stderrHandle.readabilityHandler = { handle in
            _ = handle.availableData
        }

        for await data in stream {
            if Task.isCancelled { break }

            buffer.append(data)

            do {
                while let message = try parseMessage(from: &buffer) {
                    await handleMessage(message, onNotification: onNotification)
                }
            } catch {
                // Ignore parse errors
            }
        }

        stderrHandle.readabilityHandler = nil
    }

    private func parseMessage(from buffer: inout Data) throws -> JSONRPCMessage? {
        guard let headerEnd = buffer.range(of: Data("\r\n\r\n".utf8)) else {
            return nil
        }

        let headerData = buffer[..<headerEnd.lowerBound]
        guard let headerString = String(data: headerData, encoding: .utf8) else {
            return nil
        }

        var contentLength: Int?
        for line in headerString.split(separator: "\r\n") {
            if line.lowercased().hasPrefix("content-length:") {
                let value = line.dropFirst("content-length:".count).trimmingCharacters(in: .whitespaces)
                contentLength = Int(value)
                break
            }
        }

        guard let length = contentLength else {
            return nil
        }

        let contentStart = headerEnd.upperBound
        let contentEnd = contentStart + length

        guard buffer.count >= contentEnd else {
            return nil
        }

        let contentData = buffer[contentStart..<contentEnd]
        buffer.removeSubrange(..<contentEnd)

        let decoder = JSONDecoder()
        return try decoder.decode(JSONRPCMessage.self, from: contentData)
    }

    private func handleMessage(_ message: JSONRPCMessage, onNotification: @escaping @Sendable (ServerNotification) -> Void) async {
        switch message {
        case .response(let id, let result):
            if let continuation = pendingRequests.removeValue(forKey: id) {
                continuation.resume(returning: result ?? .null)
            }

        case .errorResponse(let id, let error):
            if let continuation = pendingRequests.removeValue(forKey: id) {
                continuation.resume(throwing: TransportError.serverError(code: error.code, message: error.message))
            }

        case .notification(let method, let params):
            let notification = ServerNotification(method: method, params: params)
            onNotification(notification)

        case .request(let id, let method, let params):
            // Server-initiated request - send empty response for now
            let response = JSONRPCResponse(id: id, result: LSPAny.null)
            try? await writeMessage(response)
        }
    }
}

// MARK: - JSON-RPC Types

struct JSONRPCRequest<T: Encodable>: Encodable {
    let jsonrpc: String = "2.0"
    let id: RequestID
    let method: String
    let params: T
}

struct JSONRPCNotification<T: Encodable>: Encodable {
    let jsonrpc: String = "2.0"
    let method: String
    let params: T
}

struct JSONRPCResponse: Encodable {
    let jsonrpc: String = "2.0"
    let id: RequestID
    let result: LSPAny
}

enum JSONRPCMessage: Decodable {
    case response(id: RequestID, result: LSPAny?)
    case errorResponse(id: RequestID, error: JSONRPCError)
    case notification(method: String, params: LSPAny?)
    case request(id: RequestID, method: String, params: LSPAny?)

    enum CodingKeys: String, CodingKey {
        case jsonrpc, id, method, result, error, params
    }

    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)

        let id = try container.decodeIfPresent(RequestID.self, forKey: .id)
        let method = try container.decodeIfPresent(String.self, forKey: .method)

        if let id = id {
            if let error = try container.decodeIfPresent(JSONRPCError.self, forKey: .error) {
                self = .errorResponse(id: id, error: error)
            } else if method != nil {
                let params = try container.decodeIfPresent(LSPAny.self, forKey: .params)
                self = .request(id: id, method: method!, params: params)
            } else {
                let result = try container.decodeIfPresent(LSPAny.self, forKey: .result)
                self = .response(id: id, result: result)
            }
        } else if let method = method {
            let params = try container.decodeIfPresent(LSPAny.self, forKey: .params)
            self = .notification(method: method, params: params)
        } else {
            throw DecodingError.dataCorrupted(.init(codingPath: [], debugDescription: "Invalid JSON-RPC message"))
        }
    }
}

struct JSONRPCError: Decodable {
    let code: Int
    let message: String
}

public enum RequestID: Hashable, Codable {
    case numericId(Int)
    case stringId(String)

    public init(from decoder: Decoder) throws {
        let container = try decoder.singleValueContainer()
        if let intValue = try? container.decode(Int.self) {
            self = .numericId(intValue)
        } else if let stringValue = try? container.decode(String.self) {
            self = .stringId(stringValue)
        } else {
            throw DecodingError.dataCorrupted(.init(codingPath: [], debugDescription: "Invalid request ID"))
        }
    }

    public func encode(to encoder: Encoder) throws {
        var container = encoder.singleValueContainer()
        switch self {
        case .numericId(let id):
            try container.encode(id)
        case .stringId(let id):
            try container.encode(id)
        }
    }
}

/// Notification from server
public struct ServerNotification: Sendable {
    public let method: String
    public let params: LSPAny?
}

// MARK: - Extensions

extension Data {
    var nilIfEmpty: Data? {
        isEmpty ? nil : self
    }
}
