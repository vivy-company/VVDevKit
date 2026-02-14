//  VVMetalContext.swift
//  VVMarkdown
//
//  Shared Metal resources (device, command queue, pipelines, samplers, glyph atlas)
//  that can be reused across multiple views to avoid redundant GPU allocations.

import Foundation
import Metal
import MetalKit
import SwiftUI
import CoreText

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

// MARK: - VVMetalContext

/// Holds shared, immutable Metal resources: device, command queue, shader library,
/// pipeline states, and samplers.  Multiple ``MarkdownMetalRenderer`` instances can
/// reference one context so pipelines are compiled only once.
///
/// The glyph atlas is intentionally **not** shared here because each view may use
/// a different base font (e.g. proportional for markdown, monospace for code).
public final class VVMetalContext {

    // MARK: - Shared Singleton

    /// Process-wide shared context. Created lazily on first access.
    /// Use this as a fallback when the SwiftUI environment context is unavailable.
    public static let shared: VVMetalContext? = {
        guard let device = MTLCreateSystemDefaultDevice() else { return nil }
        return try? VVMetalContext(device: device)
    }()

    // MARK: - Core Resources

    public let device: MTLDevice
    public let commandQueue: MTLCommandQueue

    // MARK: - Pipeline States

    public let glyphPipeline: MTLRenderPipelineState
    public let colorGlyphPipeline: MTLRenderPipelineState
    public let quadPipeline: MTLRenderPipelineState
    public let roundedQuadPipeline: MTLRenderPipelineState
    public let bulletPipeline: MTLRenderPipelineState
    public let checkboxPipeline: MTLRenderPipelineState
    public let thematicBreakPipeline: MTLRenderPipelineState
    public let blockQuoteBorderPipeline: MTLRenderPipelineState
    public let tableGridPipeline: MTLRenderPipelineState
    public let linkUnderlinePipeline: MTLRenderPipelineState
    public let strikethroughPipeline: MTLRenderPipelineState
    public let imagePipeline: MTLRenderPipelineState
    public let pieSlicePipeline: MTLRenderPipelineState

    // MARK: - Samplers

    public let samplerState: MTLSamplerState
    public let imageSamplerState: MTLSamplerState

    // MARK: - Initialization

    public init(device: MTLDevice) throws {
        self.device = device

        guard let queue = device.makeCommandQueue() else {
            throw MarkdownRendererError.failedToCreateCommandQueue
        }
        self.commandQueue = queue

        // Load shader library
        let library = try Self.loadLibrary(device: device)

        // Create all pipeline states
        glyphPipeline = try Self.createPipeline(device: device, library: library, vertex: "markdownGlyphVertexShader", fragment: "markdownGlyphFragmentShader", label: "Markdown Glyph")
        colorGlyphPipeline = try Self.createPipeline(device: device, library: library, vertex: "markdownGlyphVertexShader", fragment: "markdownColorGlyphFragmentShader", label: "Markdown Color Glyph", premultipliedAlpha: true)
        quadPipeline = try Self.createPipeline(device: device, library: library, vertex: "markdownQuadVertexShader", fragment: "markdownQuadFragmentShader", label: "Markdown Quad")
        roundedQuadPipeline = try Self.createPipeline(device: device, library: library, vertex: "markdownQuadVertexShader", fragment: "markdownRoundedQuadFragmentShader", label: "Markdown Rounded Quad")
        bulletPipeline = try Self.createPipeline(device: device, library: library, vertex: "bulletVertexShader", fragment: "bulletFragmentShader", label: "Bullet")
        checkboxPipeline = try Self.createPipeline(device: device, library: library, vertex: "checkboxVertexShader", fragment: "checkboxFragmentShader", label: "Checkbox")
        thematicBreakPipeline = try Self.createPipeline(device: device, library: library, vertex: "thematicBreakVertexShader", fragment: "thematicBreakFragmentShader", label: "Thematic Break")
        blockQuoteBorderPipeline = try Self.createPipeline(device: device, library: library, vertex: "blockQuoteBorderVertexShader", fragment: "blockQuoteBorderFragmentShader", label: "Block Quote Border")
        tableGridPipeline = try Self.createPipeline(device: device, library: library, vertex: "tableGridVertexShader", fragment: "tableGridFragmentShader", label: "Table Grid")
        linkUnderlinePipeline = try Self.createPipeline(device: device, library: library, vertex: "linkUnderlineVertexShader", fragment: "linkUnderlineFragmentShader", label: "Link Underline")
        strikethroughPipeline = try Self.createPipeline(device: device, library: library, vertex: "strikethroughVertexShader", fragment: "strikethroughFragmentShader", label: "Strikethrough")
        imagePipeline = try Self.createPipeline(device: device, library: library, vertex: "imageVertexShader", fragment: "imageFragmentShader", label: "Image")
        pieSlicePipeline = try Self.createPipeline(device: device, library: library, vertex: "pieSliceVertexShader", fragment: "pieSliceFragmentShader", label: "Pie Slice")

        // Create samplers
        let nearestDesc = MTLSamplerDescriptor()
        nearestDesc.minFilter = .nearest
        nearestDesc.magFilter = .nearest
        nearestDesc.mipFilter = .notMipmapped
        nearestDesc.sAddressMode = .clampToEdge
        nearestDesc.tAddressMode = .clampToEdge
        guard let nearest = device.makeSamplerState(descriptor: nearestDesc) else {
            throw MarkdownRendererError.failedToCreatePipelineState
        }
        self.samplerState = nearest

        let linearDesc = MTLSamplerDescriptor()
        linearDesc.minFilter = .linear
        linearDesc.magFilter = .linear
        linearDesc.mipFilter = .linear
        linearDesc.sAddressMode = .clampToEdge
        linearDesc.tAddressMode = .clampToEdge
        guard let linear = device.makeSamplerState(descriptor: linearDesc) else {
            throw MarkdownRendererError.failedToCreatePipelineState
        }
        self.imageSamplerState = linear
    }

    // MARK: - Glyph Atlas Cache

    private var atlasCache: [Int: MarkdownGlyphAtlas] = [:]  // scaleFactor (tenths) -> atlas
    private let atlasCacheLock = NSLock()

    /// Returns the shared glyph atlas for a given scale factor.
    /// All views at the same scale share one atlas (~80MB GPU memory), regardless of font.
    /// The atlas handles multiple fonts internally via font-name-based glyph lookups.
    public func sharedAtlas(baseFont: VVFont, scaleFactor: CGFloat) -> MarkdownGlyphAtlas {
        let key = Int(scaleFactor * 10)
        atlasCacheLock.lock()
        defer { atlasCacheLock.unlock() }
        if let cached = atlasCache[key] {
            return cached
        }
        let atlas = MarkdownGlyphAtlas(device: device, baseFont: baseFont, scaleFactor: scaleFactor)
        atlasCache[key] = atlas
        return atlas
    }

    // MARK: - Diagnostics

    /// Snapshot of atlas statistics across all cached scale factors.
    public struct AtlasDiagnostics {
        public var alphaPages: Int = 0
        public var colorPages: Int = 0
        public var cachedGlyphs: Int = 0
        public var atlasCount: Int = 0
    }

    /// Collect stats from all cached atlases.
    public func atlasDiagnostics() -> AtlasDiagnostics {
        atlasCacheLock.lock()
        defer { atlasCacheLock.unlock() }
        var d = AtlasDiagnostics()
        d.atlasCount = atlasCache.count
        for atlas in atlasCache.values {
            d.alphaPages += atlas.alphaPageCount
            d.colorPages += atlas.colorPageCount
            d.cachedGlyphs += atlas.cachedGlyphCount
        }
        return d
    }

    /// Number of buffers currently held in the pool.
    public var pooledBufferCount: Int {
        bufferPoolLock.lock()
        defer { bufferPoolLock.unlock() }
        return bufferPool.values.reduce(0) { $0 + $1.count }
    }

    /// Drop cached glyph data from all shared atlases to reclaim GPU memory.
    public func purgeAtlases() {
        atlasCacheLock.lock()
        defer { atlasCacheLock.unlock() }
        for atlas in atlasCache.values {
            atlas.purge()
        }
    }

    private var bufferPool: [Int: [MTLBuffer]] = [:]  // size bucket -> reusable buffers
    private let bufferPoolLock = NSLock()
    private static let maxPooledBuffersPerBucket = 8

    // MARK: - Buffer Creation

    public func makeBuffer<T>(for instances: [T]) -> MTLBuffer? {
        guard !instances.isEmpty else { return nil }
        let size = MemoryLayout<T>.stride * instances.count
        let bucket = Self.bufferBucket(for: size)

        bufferPoolLock.lock()
        if var pooled = bufferPool[bucket], !pooled.isEmpty {
            let buffer = pooled.removeLast()
            bufferPool[bucket] = pooled
            bufferPoolLock.unlock()
            if buffer.length >= size {
                _ = instances.withUnsafeBufferPointer { ptr in
                    memcpy(buffer.contents(), ptr.baseAddress!, size)
                }
                return buffer
            }
        } else {
            bufferPoolLock.unlock()
        }

        return instances.withUnsafeBufferPointer { ptr in
            device.makeBuffer(bytes: ptr.baseAddress!, length: size, options: .storageModeShared)
        }
    }

    /// Return a buffer to the pool for reuse.
    public func recycleBuffer(_ buffer: MTLBuffer) {
        let bucket = Self.bufferBucket(for: buffer.length)
        bufferPoolLock.lock()
        var pooled = bufferPool[bucket] ?? []
        if pooled.count < Self.maxPooledBuffersPerBucket {
            pooled.append(buffer)
            bufferPool[bucket] = pooled
        }
        bufferPoolLock.unlock()
    }

    /// Drain the buffer pool to free GPU memory.
    public func drainBufferPool() {
        bufferPoolLock.lock()
        bufferPool.removeAll()
        bufferPoolLock.unlock()
    }

    private static func bufferBucket(for size: Int) -> Int {
        // Round up to next power of 2, min 4KB
        var bucket = max(4096, size)
        bucket -= 1
        bucket |= bucket >> 1
        bucket |= bucket >> 2
        bucket |= bucket >> 4
        bucket |= bucket >> 8
        bucket |= bucket >> 16
        return bucket + 1
    }

    // MARK: - Shader Loading (private)

    private static func loadLibrary(device: MTLDevice) throws -> MTLLibrary {
        if let source = loadShaderSource() {
            return try device.makeLibrary(source: source, options: nil)
        }
        if let metallib = loadMetalLibrary(device: device) {
            return metallib
        }
        if let defaultLibrary = device.makeDefaultLibrary() {
            return defaultLibrary
        }
        throw MarkdownRendererError.failedToLoadShaderLibrary
    }

    private static func loadShaderSource() -> String? {
        #if SWIFT_PACKAGE
        let bundle = Bundle.module
        #else
        let bundle = Bundle(for: VVMetalContext.self)
        #endif

        guard let url = bundle.url(forResource: "MarkdownShaders", withExtension: "metal") else {
            return nil
        }
        return try? String(contentsOf: url, encoding: .utf8)
    }

    private static func loadMetalLibrary(device: MTLDevice) -> MTLLibrary? {
        #if SWIFT_PACKAGE
        let bundle = Bundle.module
        #else
        let bundle = Bundle(for: VVMetalContext.self)
        #endif

        guard let url = bundle.url(forResource: "default", withExtension: "metallib") else {
            return nil
        }
        return try? device.makeLibrary(URL: url)
    }

    private static func createPipeline(device: MTLDevice, library: MTLLibrary, vertex: String, fragment: String, label: String, premultipliedAlpha: Bool = false) throws -> MTLRenderPipelineState {
        guard let vertexFn = library.makeFunction(name: vertex),
              let fragmentFn = library.makeFunction(name: fragment) else {
            throw MarkdownRendererError.failedToCreateShaderFunction(vertex)
        }

        let descriptor = MTLRenderPipelineDescriptor()
        descriptor.label = label
        descriptor.vertexFunction = vertexFn
        descriptor.fragmentFunction = fragmentFn
        descriptor.colorAttachments[0].pixelFormat = .bgra8Unorm

        // Enable alpha blending
        descriptor.colorAttachments[0].isBlendingEnabled = true
        descriptor.colorAttachments[0].rgbBlendOperation = .add
        descriptor.colorAttachments[0].alphaBlendOperation = .add
        if premultipliedAlpha {
            // Source RGB is already premultiplied — use .one to avoid double-multiplication
            descriptor.colorAttachments[0].sourceRGBBlendFactor = .one
            descriptor.colorAttachments[0].sourceAlphaBlendFactor = .one
        } else {
            descriptor.colorAttachments[0].sourceRGBBlendFactor = .sourceAlpha
            descriptor.colorAttachments[0].sourceAlphaBlendFactor = .sourceAlpha
        }
        descriptor.colorAttachments[0].destinationRGBBlendFactor = .oneMinusSourceAlpha
        descriptor.colorAttachments[0].destinationAlphaBlendFactor = .oneMinusSourceAlpha

        return try device.makeRenderPipelineState(descriptor: descriptor)
    }
}

// MARK: - SwiftUI Environment Key

private struct VVMetalContextKey: EnvironmentKey {
    static let defaultValue: VVMetalContext? = nil
}

public extension EnvironmentValues {
    var vvMetalContext: VVMetalContext? {
        get { self[VVMetalContextKey.self] }
        set { self[VVMetalContextKey.self] = newValue }
    }
}
