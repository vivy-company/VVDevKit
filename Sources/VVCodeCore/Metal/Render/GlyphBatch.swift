import Foundation
import Metal
import simd
import AppKit

/// Manages batched glyph instances for efficient GPU rendering
public final class GlyphBatch {

    // MARK: - Properties

    private let device: MTLDevice
    private var instanceBuffer: MTLBuffer?
    private var instances: [GlyphInstance] = []
    private var bufferCapacity: Int = 0

    private let initialCapacity = 4096
    private let growthFactor = 2

    // MARK: - Initialization

    public init(device: MTLDevice) {
        self.device = device
        ensureCapacity(initialCapacity)
    }

    // MARK: - Public API

    /// Clear all instances
    public func clear() {
        instances.removeAll(keepingCapacity: true)
    }

    /// Add a glyph instance
    public func addGlyph(
        position: SIMD2<Float>,
        size: SIMD2<Float>,
        uvOrigin: SIMD2<Float>,
        uvSize: SIMD2<Float>,
        color: SIMD4<Float>,
        atlasIndex: UInt32 = 0
    ) {
        instances.append(GlyphInstance(
            position: position,
            size: size,
            uvOrigin: uvOrigin,
            uvSize: uvSize,
            color: color,
            atlasIndex: atlasIndex
        ))
    }

    /// Add a glyph from cached glyph info
    public func addGlyph(
        cached: CachedGlyph,
        screenPosition: CGPoint,
        color: SIMD4<Float>
    ) {
        // Skip empty glyphs (like spaces)
        guard cached.size.width > 0 && cached.size.height > 0 else { return }

        // Bearing normalization happens in GlyphAtlasManager for consistent baseline alignment
        let position = SIMD2<Float>(
            Float(screenPosition.x + cached.bearing.x),
            Float(screenPosition.y + cached.bearing.y)
        )
        let size = SIMD2<Float>(Float(cached.size.width), Float(cached.size.height))
        let uvOrigin = SIMD2<Float>(Float(cached.uvRect.origin.x), Float(cached.uvRect.origin.y))
        let uvSize = SIMD2<Float>(Float(cached.uvRect.width), Float(cached.uvRect.height))

        addGlyph(
            position: position,
            size: size,
            uvOrigin: uvOrigin,
            uvSize: uvSize,
            color: color,
            atlasIndex: UInt32(cached.atlasIndex)
        )
    }

    /// Prepare buffer for rendering
    public func prepareBuffer() -> (buffer: MTLBuffer, count: Int)? {
        guard !instances.isEmpty else { return nil }

        ensureCapacity(instances.count)

        guard let buffer = instanceBuffer else { return nil }

        // Copy instance data to buffer
        let dataSize = instances.count * MemoryLayout<GlyphInstance>.stride
        memcpy(buffer.contents(), &instances, dataSize)

        return (buffer, instances.count)
    }

    /// Get instance count
    public var count: Int {
        instances.count
    }

    /// Get the buffer directly (for external use)
    public var buffer: MTLBuffer? {
        instanceBuffer
    }

    // MARK: - Private Methods

    private func ensureCapacity(_ required: Int) {
        guard required > bufferCapacity else { return }

        let newCapacity = max(required, bufferCapacity * growthFactor)
        let bufferSize = newCapacity * MemoryLayout<GlyphInstance>.stride

        guard let newBuffer = device.makeBuffer(length: bufferSize, options: .storageModeShared) else {
            return
        }

        newBuffer.label = "Glyph Instance Buffer"
        instanceBuffer = newBuffer
        bufferCapacity = newCapacity
    }
}

/// Manages batched selection/cursor quads
public final class QuadBatch {

    // MARK: - Properties

    private let device: MTLDevice
    private var quadBuffer: MTLBuffer?
    private var quads: [SelectionQuad] = []
    private var bufferCapacity: Int = 0

    private let initialCapacity = 256
    private let growthFactor = 2

    // MARK: - Initialization

    public init(device: MTLDevice) {
        self.device = device
        ensureCapacity(initialCapacity)
    }

    // MARK: - Public API

    /// Clear all quads
    public func clear() {
        quads.removeAll(keepingCapacity: true)
    }

    /// Add a selection quad
    public func addQuad(position: SIMD2<Float>, size: SIMD2<Float>, color: SIMD4<Float>) {
        quads.append(SelectionQuad(position: position, size: size, color: color))
    }

    /// Add a selection quad from CGRect
    public func addQuad(rect: CGRect, color: NSColor) {
        quads.append(SelectionQuad(rect: rect, color: color))
    }

    /// Add a cursor quad
    public func addCursor(x: CGFloat, y: CGFloat, height: CGFloat, width: CGFloat = 2, color: NSColor) {
        addQuad(
            position: SIMD2<Float>(Float(x), Float(y)),
            size: SIMD2<Float>(Float(width), Float(height)),
            color: color.simdColor
        )
    }

    /// Prepare buffer for rendering
    public func prepareBuffer() -> (buffer: MTLBuffer, count: Int)? {
        guard !quads.isEmpty else { return nil }

        ensureCapacity(quads.count)

        guard let buffer = quadBuffer else { return nil }

        let dataSize = quads.count * MemoryLayout<SelectionQuad>.stride
        memcpy(buffer.contents(), &quads, dataSize)

        return (buffer, quads.count)
    }

    /// Get quad count
    public var count: Int {
        quads.count
    }

    // MARK: - Private Methods

    private func ensureCapacity(_ required: Int) {
        guard required > bufferCapacity else { return }

        let newCapacity = max(required, bufferCapacity * growthFactor)
        let bufferSize = newCapacity * MemoryLayout<SelectionQuad>.stride

        guard let newBuffer = device.makeBuffer(length: bufferSize, options: .storageModeShared) else {
            return
        }

        newBuffer.label = "Quad Buffer"
        quadBuffer = newBuffer
        bufferCapacity = newCapacity
    }
}

/// Pool of reusable buffers for triple buffering
public final class BufferPool<T> {

    private let device: MTLDevice
    private var buffers: [MTLBuffer] = []
    private var currentIndex: Int = 0
    private let bufferCount: Int

    public init(device: MTLDevice, capacity: Int, count: Int = 3) {
        self.device = device
        self.bufferCount = count

        let size = capacity * MemoryLayout<T>.stride
        for i in 0..<count {
            if let buffer = device.makeBuffer(length: size, options: .storageModeShared) {
                buffer.label = "Pool Buffer \(i)"
                buffers.append(buffer)
            }
        }
    }

    public func nextBuffer() -> MTLBuffer? {
        guard !buffers.isEmpty else { return nil }
        currentIndex = (currentIndex + 1) % buffers.count
        return buffers[currentIndex]
    }

    public var currentBuffer: MTLBuffer? {
        guard !buffers.isEmpty else { return nil }
        return buffers[currentIndex]
    }
}
