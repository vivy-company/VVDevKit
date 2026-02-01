import Foundation

public final class VVChatDraftThrottler {
    private let interval: TimeInterval
    private let queue: DispatchQueue
    private var timer: DispatchSourceTimer?
    private var pendingText: String?
    private var onFlush: ((String) -> Void)?

    public init(interval: TimeInterval = 0.03, queue: DispatchQueue = .main) {
        self.interval = interval
        self.queue = queue
    }

    public func schedule(_ text: String, onFlush: @escaping (String) -> Void) {
        queue.async {
            self.pendingText = text
            self.onFlush = onFlush
            if self.timer == nil {
                self.startTimer()
            }
        }
    }

    public func cancel() {
        queue.async {
            self.timer?.cancel()
            self.timer = nil
            self.pendingText = nil
        }
    }

    private func startTimer() {
        let timer = DispatchSource.makeTimerSource(queue: queue)
        timer.schedule(deadline: .now() + interval, repeating: interval)
        timer.setEventHandler { [weak self] in
            guard let self else { return }
            guard let text = self.pendingText else {
                self.timer?.cancel()
                self.timer = nil
                return
            }
            self.pendingText = nil
            if let onFlush = self.onFlush {
                onFlush(text)
            }
        }
        self.timer = timer
        timer.resume()
    }
}
