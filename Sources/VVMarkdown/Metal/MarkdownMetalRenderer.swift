//  MarkdownMetalRenderer.swift
//  VVMarkdown
//
//  Metal renderer for markdown content

import Foundation
import Metal
import MetalKit
import simd
import CoreText
import CoreGraphics

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

// MARK: - Markdown Uniforms

public struct MarkdownUniforms {
    public var projectionMatrix: simd_float4x4
    public var scrollOffset: SIMD2<Float>
    public var viewportSize: SIMD2<Float>
    public var atlasSize: SIMD2<Float>
    public var time: Float
    public var padding: Float

    public init() {
        self.projectionMatrix = matrix_identity_float4x4
        self.scrollOffset = .zero
        self.viewportSize = .zero
        self.atlasSize = SIMD2<Float>(1024, 1024)
        self.time = 0
        self.padding = 0
    }

    public static func orthographic(width: Float, height: Float) -> simd_float4x4 {
        simd_float4x4(
            SIMD4<Float>(2.0 / width, 0, 0, 0),
            SIMD4<Float>(0, -2.0 / height, 0, 0),
            SIMD4<Float>(0, 0, 1, 0),
            SIMD4<Float>(-1, 1, 0, 1)
        )
    }
}

// MARK: - Instance Structures

public struct MarkdownGlyphInstance {
    public var position: SIMD2<Float>
    public var size: SIMD2<Float>
    public var uvOrigin: SIMD2<Float>
    public var uvSize: SIMD2<Float>
    public var color: SIMD4<Float>
    public var atlasIndex: UInt32
    public var padding: SIMD3<UInt32>

    public init(position: SIMD2<Float>, size: SIMD2<Float>, uvOrigin: SIMD2<Float>, uvSize: SIMD2<Float>, color: SIMD4<Float>, atlasIndex: UInt32 = 0) {
        self.position = position
        self.size = size
        self.uvOrigin = uvOrigin
        self.uvSize = uvSize
        self.color = color
        self.atlasIndex = atlasIndex
        self.padding = .zero
    }
}

public struct QuadInstance {
    public var position: SIMD2<Float>
    public var size: SIMD2<Float>
    public var color: SIMD4<Float>
    public var cornerRadius: Float
    public var borderWidth: Float
    public var padding: SIMD2<Float>

    public init(position: SIMD2<Float>, size: SIMD2<Float>, color: SIMD4<Float>, cornerRadius: Float = 0, borderWidth: Float = 0) {
        self.position = position
        self.size = size
        self.color = color
        self.cornerRadius = cornerRadius
        self.borderWidth = borderWidth
        self.padding = .zero
    }
}

public struct BulletInstance {
    public var position: SIMD2<Float>
    public var size: SIMD2<Float>
    public var color: SIMD4<Float>
    public var bulletType: UInt32  // 0=disc, 1=circle, 2=square
    public var padding: SIMD3<UInt32>

    public init(position: SIMD2<Float>, size: SIMD2<Float>, color: SIMD4<Float>, bulletType: UInt32) {
        self.position = position
        self.size = size
        self.color = color
        self.bulletType = bulletType
        self.padding = .zero
    }
}

public struct CheckboxInstance {
    public var position: SIMD2<Float>
    public var size: SIMD2<Float>
    public var color: SIMD4<Float>
    public var isChecked: UInt32
    public var padding: SIMD3<UInt32>

    public init(position: SIMD2<Float>, size: SIMD2<Float>, color: SIMD4<Float>, isChecked: Bool) {
        self.position = position
        self.size = size
        self.color = color
        self.isChecked = isChecked ? 1 : 0
        self.padding = .zero
    }
}

public struct LineInstance {
    public var position: SIMD2<Float>
    public var width: Float
    public var height: Float
    public var color: SIMD4<Float>

    public init(position: SIMD2<Float>, width: Float, height: Float, color: SIMD4<Float>) {
        self.position = position
        self.width = width
        self.height = height
        self.color = color
    }
}

public struct BlockQuoteBorderInstance {
    public var position: SIMD2<Float>
    public var size: SIMD2<Float>
    public var color: SIMD4<Float>
    public var borderWidth: Float
    public var padding: SIMD3<Float>

    public init(position: SIMD2<Float>, size: SIMD2<Float>, color: SIMD4<Float>, borderWidth: Float) {
        self.position = position
        self.size = size
        self.color = color
        self.borderWidth = borderWidth
        self.padding = .zero
    }
}

public struct TableGridLineInstance {
    public var start: SIMD2<Float>
    public var end: SIMD2<Float>
    public var color: SIMD4<Float>
    public var lineWidth: Float
    public var padding: SIMD3<Float>

    public init(start: SIMD2<Float>, end: SIMD2<Float>, color: SIMD4<Float>, lineWidth: Float) {
        self.start = start
        self.end = end
        self.color = color
        self.lineWidth = lineWidth
        self.padding = .zero
    }
}

public struct ImageRenderInstance {
    public var position: SIMD2<Float>
    public var size: SIMD2<Float>
    public var uvOrigin: SIMD2<Float>
    public var uvSize: SIMD2<Float>
    public var cornerRadius: Float
    public var padding: SIMD3<Float>

    public init(position: SIMD2<Float>, size: SIMD2<Float>, uvOrigin: SIMD2<Float> = SIMD2(0, 0), uvSize: SIMD2<Float> = SIMD2(1, 1), cornerRadius: Float = 0) {
        self.position = position
        self.size = size
        self.uvOrigin = uvOrigin
        self.uvSize = uvSize
        self.cornerRadius = cornerRadius
        self.padding = .zero
    }
}

public struct PieSliceInstance {
    public var center: SIMD2<Float>
    public var radius: Float
    public var startAngle: Float
    public var endAngle: Float
    public var padding0: Float
    public var padding1: Float
    public var padding2: Float
    public var color: SIMD4<Float>

    public init(center: SIMD2<Float>, radius: Float, startAngle: Float, endAngle: Float, color: SIMD4<Float>) {
        self.center = center
        self.radius = radius
        self.startAngle = startAngle
        self.endAngle = endAngle
        self.padding0 = 0
        self.padding1 = 0
        self.padding2 = 0
        self.color = color
    }
}

// MARK: - Markdown Metal Renderer

/// Metal renderer for markdown content
public final class MarkdownMetalRenderer {

    // MARK: - Properties

    public let device: MTLDevice
    public let commandQueue: MTLCommandQueue
    public let glyphAtlas: MarkdownGlyphAtlas

    // Pipeline states
    private var glyphPipeline: MTLRenderPipelineState!
    private var colorGlyphPipeline: MTLRenderPipelineState!
    private var quadPipeline: MTLRenderPipelineState!
    private var roundedQuadPipeline: MTLRenderPipelineState!
    private var bulletPipeline: MTLRenderPipelineState!
    private var checkboxPipeline: MTLRenderPipelineState!
    private var thematicBreakPipeline: MTLRenderPipelineState!
    private var blockQuoteBorderPipeline: MTLRenderPipelineState!
    private var tableGridPipeline: MTLRenderPipelineState!
    private var linkUnderlinePipeline: MTLRenderPipelineState!
    private var strikethroughPipeline: MTLRenderPipelineState!
    private var imagePipeline: MTLRenderPipelineState!
    private var pieSlicePipeline: MTLRenderPipelineState!

    // Image sampler
    private var imageSamplerState: MTLSamplerState!

    // Uniform buffers (triple buffered)
    private var uniformBuffers: [MTLBuffer] = []
    private var currentUniformBufferIndex = 0
    private let uniformBufferCount = 3

    // Sampler
    private var samplerState: MTLSamplerState!

    // Current uniforms
    public var uniforms = MarkdownUniforms()

    // MARK: - Initialization

    public init(device: MTLDevice, baseFont: VVFont, scaleFactor: CGFloat = 2.0) throws {
        self.device = device

        guard let queue = device.makeCommandQueue() else {
            throw MarkdownRendererError.failedToCreateCommandQueue
        }
        self.commandQueue = queue
        self.glyphAtlas = MarkdownGlyphAtlas(device: device, baseFont: baseFont, scaleFactor: scaleFactor)

        try setupPipelines()
        setupUniformBuffers()
        setupSampler()
    }

    // MARK: - Pipeline Setup

    private func setupPipelines() throws {
        let library: MTLLibrary

        // Try loading shader source from bundle (pure SPM builds)
        if let source = Self.loadShaderSource() {
            library = try device.makeLibrary(source: source, options: nil)
        } else if let metallib = Self.loadMetalLibrary(device: device) {
            // Try loading pre-compiled metallib from package bundle (Xcode builds SPM packages this way)
            library = metallib
        } else if let defaultLibrary = device.makeDefaultLibrary() {
            // Try default library (Xcode project with .metal files in main target)
            library = defaultLibrary
        } else {
            fatalError("MarkdownMetalRenderer: Could not load shader. Ensure MarkdownShaders.metal is included in package resources or compiled by Xcode.")
        }

        glyphPipeline = try createPipeline(library: library, vertex: "markdownGlyphVertexShader", fragment: "markdownGlyphFragmentShader", label: "Markdown Glyph")
        colorGlyphPipeline = try createPipeline(library: library, vertex: "markdownGlyphVertexShader", fragment: "markdownColorGlyphFragmentShader", label: "Markdown Color Glyph")
        quadPipeline = try createPipeline(library: library, vertex: "markdownQuadVertexShader", fragment: "markdownQuadFragmentShader", label: "Markdown Quad")
        roundedQuadPipeline = try createPipeline(library: library, vertex: "markdownQuadVertexShader", fragment: "markdownRoundedQuadFragmentShader", label: "Markdown Rounded Quad")
        bulletPipeline = try createPipeline(library: library, vertex: "bulletVertexShader", fragment: "bulletFragmentShader", label: "Bullet")
        checkboxPipeline = try createPipeline(library: library, vertex: "checkboxVertexShader", fragment: "checkboxFragmentShader", label: "Checkbox")
        thematicBreakPipeline = try createPipeline(library: library, vertex: "thematicBreakVertexShader", fragment: "thematicBreakFragmentShader", label: "Thematic Break")
        blockQuoteBorderPipeline = try createPipeline(library: library, vertex: "blockQuoteBorderVertexShader", fragment: "blockQuoteBorderFragmentShader", label: "Block Quote Border")
        tableGridPipeline = try createPipeline(library: library, vertex: "tableGridVertexShader", fragment: "tableGridFragmentShader", label: "Table Grid")
        linkUnderlinePipeline = try createPipeline(library: library, vertex: "linkUnderlineVertexShader", fragment: "linkUnderlineFragmentShader", label: "Link Underline")
        strikethroughPipeline = try createPipeline(library: library, vertex: "strikethroughVertexShader", fragment: "strikethroughFragmentShader", label: "Strikethrough")
        imagePipeline = try createPipeline(library: library, vertex: "imageVertexShader", fragment: "imageFragmentShader", label: "Image")

        pieSlicePipeline = try createPipeline(library: library, vertex: "pieSliceVertexShader", fragment: "pieSliceFragmentShader", label: "Pie Slice")
    }

    private static func loadShaderSource() -> String? {
        #if SWIFT_PACKAGE
        let bundle = Bundle.module
        #else
        let bundle = Bundle(for: MarkdownMetalRenderer.self)
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
        let bundle = Bundle(for: MarkdownMetalRenderer.self)
        #endif

        // Xcode compiles .metal files to default.metallib
        guard let url = bundle.url(forResource: "default", withExtension: "metallib") else {
            return nil
        }

        return try? device.makeLibrary(URL: url)
    }

    private func createPipeline(library: MTLLibrary, vertex: String, fragment: String, label: String) throws -> MTLRenderPipelineState {
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
        descriptor.colorAttachments[0].sourceRGBBlendFactor = .sourceAlpha
        descriptor.colorAttachments[0].sourceAlphaBlendFactor = .sourceAlpha
        descriptor.colorAttachments[0].destinationRGBBlendFactor = .oneMinusSourceAlpha
        descriptor.colorAttachments[0].destinationAlphaBlendFactor = .oneMinusSourceAlpha

        return try device.makeRenderPipelineState(descriptor: descriptor)
    }

    private func setupUniformBuffers() {
        let size = MemoryLayout<MarkdownUniforms>.stride
        for _ in 0..<uniformBufferCount {
            if let buffer = device.makeBuffer(length: size, options: .storageModeShared) {
                buffer.label = "Markdown Uniform Buffer"
                uniformBuffers.append(buffer)
            }
        }
    }

    private func setupSampler() {
        let descriptor = MTLSamplerDescriptor()
        descriptor.minFilter = .nearest
        descriptor.magFilter = .nearest
        descriptor.mipFilter = .notMipmapped
        descriptor.sAddressMode = .clampToEdge
        descriptor.tAddressMode = .clampToEdge
        samplerState = device.makeSamplerState(descriptor: descriptor)

        // Image sampler with linear filtering for smooth scaling
        let imageDescriptor = MTLSamplerDescriptor()
        imageDescriptor.minFilter = .linear
        imageDescriptor.magFilter = .linear
        imageDescriptor.mipFilter = .linear
        imageDescriptor.sAddressMode = .clampToEdge
        imageDescriptor.tAddressMode = .clampToEdge
        imageSamplerState = device.makeSamplerState(descriptor: imageDescriptor)
    }

    // MARK: - Frame Management

    public func beginFrame(viewportSize: CGSize, scrollOffset: CGPoint) {
        uniforms.viewportSize = SIMD2<Float>(Float(viewportSize.width), Float(viewportSize.height))
        uniforms.scrollOffset = SIMD2<Float>(Float(scrollOffset.x), Float(scrollOffset.y))
        uniforms.projectionMatrix = MarkdownUniforms.orthographic(
            width: Float(viewportSize.width),
            height: Float(viewportSize.height)
        )
        uniforms.time = Float(CACurrentMediaTime().truncatingRemainder(dividingBy: 2.0))
        uniforms.atlasSize = SIMD2<Float>(Float(MarkdownGlyphAtlas.atlasSize), Float(MarkdownGlyphAtlas.atlasSize))

        currentUniformBufferIndex = (currentUniformBufferIndex + 1) % uniformBufferCount
        let buffer = uniformBuffers[currentUniformBufferIndex]
        memcpy(buffer.contents(), &uniforms, MemoryLayout<MarkdownUniforms>.stride)
    }

    // MARK: - Rendering

    public func renderGlyphs(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard let atlasTexture = glyphAtlas.atlasTexture else { return }
        renderGlyphs(encoder: encoder, instances: instances, instanceCount: instanceCount, texture: atlasTexture)
    }

    public func renderGlyphs(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int, texture: MTLTexture) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(glyphPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentTexture(texture, index: 0)
        encoder.setFragmentSamplerState(samplerState, index: 0)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderColorGlyphs(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard let atlasTexture = glyphAtlas.colorAtlasTexture else { return }
        renderColorGlyphs(encoder: encoder, instances: instances, instanceCount: instanceCount, texture: atlasTexture)
    }

    public func renderColorGlyphs(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int, texture: MTLTexture) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(colorGlyphPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentTexture(texture, index: 0)
        encoder.setFragmentSamplerState(samplerState, index: 0)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderQuads(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int, rounded: Bool = false) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(rounded ? roundedQuadPipeline : quadPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        if rounded {
            encoder.setFragmentBuffer(instances, offset: 0, index: 0)
        }

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderBullets(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(bulletPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderCheckboxes(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(checkboxPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderThematicBreaks(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(thematicBreakPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderBlockQuoteBorders(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(blockQuoteBorderPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderTableGrid(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(tableGridPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderLinkUnderlines(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(linkUnderlinePipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderStrikethroughs(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(strikethroughPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderImages(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int, texture: MTLTexture) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(imagePipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentTexture(texture, index: 0)
        encoder.setFragmentSamplerState(imageSamplerState, index: 0)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderPieSlices(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(pieSlicePipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentBuffer(instances, offset: 0, index: 0)
        encoder.setFragmentBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    // MARK: - Buffer Creation

    public func makeBuffer<T>(for instances: [T]) -> MTLBuffer? {
        guard !instances.isEmpty else { return nil }
        let size = MemoryLayout<T>.stride * instances.count
        return device.makeBuffer(bytes: instances, length: size, options: .storageModeShared)
    }

    // MARK: - Font Update

    public func updateFont(_ font: VVFont, scaleFactor: CGFloat? = nil) {
        glyphAtlas.updateFont(font, scaleFactor: scaleFactor)
    }
}

// MARK: - Errors

public enum MarkdownRendererError: Error {
    case failedToCreateCommandQueue
    case failedToLoadShaderLibrary
    case failedToCreateShaderFunction(String)
    case failedToCreatePipelineState
}
