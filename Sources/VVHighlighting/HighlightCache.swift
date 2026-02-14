import Foundation

public final class HighlightCache {
  public let maxSize: Int

  private struct RangeKey: Hashable {
    let location: Int
    let length: Int

    init(_ range: NSRange) {
      self.location = range.location
      self.length = range.length
    }

    var nsRange: NSRange {
      NSRange(location: location, length: length)
    }
  }

  private final class Node {
    let key: RangeKey
    var value: [HighlightRange]
    var prev: Node?
    var next: Node?

    init(key: RangeKey, value: [HighlightRange]) {
      self.key = key
      self.value = value
    }
  }

  private var nodes: [RangeKey: Node] = [:]
  private var head: Node?
  private var tail: Node?

  public init(maxSize: Int) {
    self.maxSize = max(0, maxSize)
  }

  public func get(for range: NSRange) -> [HighlightRange]? {
    guard let node = nodes[RangeKey(range)] else { return nil }
    moveToTail(node)
    return node.value
  }

  public func set(_ highlights: [HighlightRange], for range: NSRange) {
    guard maxSize > 0 else { return }
    let key = RangeKey(range)

    if let node = nodes[key] {
      node.value = highlights
      moveToTail(node)
      return
    }

    let node = Node(key: key, value: highlights)
    appendToTail(node)
    nodes[key] = node
    evictIfNeeded()
  }

  public func clear() {
    nodes.removeAll()
    head = nil
    tail = nil
  }

  public func invalidate(overlapping range: NSRange) {
    var current = head

    while let node = current {
      current = node.next
      if NSIntersectionRange(node.key.nsRange, range).length > 0 {
        remove(node)
      }
    }
  }

  private func moveToTail(_ node: Node) {
    guard tail !== node else { return }
    unlink(node)
    appendToTail(node)
  }

  private func appendToTail(_ node: Node) {
    node.prev = tail
    node.next = nil

    if let tailNode = tail {
      tailNode.next = node
    } else {
      head = node
    }

    tail = node
  }

  private func unlink(_ node: Node) {
    if let prev = node.prev {
      prev.next = node.next
    } else {
      head = node.next
    }

    if let next = node.next {
      next.prev = node.prev
    } else {
      tail = node.prev
    }

    node.prev = nil
    node.next = nil
  }

  private func remove(_ node: Node) {
    unlink(node)
    nodes[node.key] = nil
  }

  private func evictIfNeeded() {
    while nodes.count > maxSize, let currentHead = head {
      remove(currentHead)
    }
  }
}
