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

/// Metal renderer for markdown content.
///
/// When created with a shared ``VVMetalContext``, the renderer is a lightweight
/// per-view wrapper holding only triple-buffered uniform state.  All pipeline
/// states, samplers, and the glyph atlas are owned by the context.
public final class MarkdownMetalRenderer {

    // MARK: - Properties

    /// Shared context owning device, command queue, pipelines, samplers.
    public let context: VVMetalContext

    /// Shared glyph atlas (cached by scale factor in VVMetalContext).
    public let glyphAtlas: MarkdownGlyphAtlas

    /// The base font this renderer was created with, used for variant-based glyph lookups.
    public let baseFont: VVFont

    /// Forwarding accessors so existing call sites continue to compile.
    public var device: MTLDevice { context.device }
    public var commandQueue: MTLCommandQueue { context.commandQueue }

    // Uniform buffers (triple buffered) – per-view
    private var uniformBuffers: [MTLBuffer] = []
    private var currentUniformBufferIndex = 0
    private let uniformBufferCount = 3

    // Current uniforms
    public var uniforms = MarkdownUniforms()

    // MARK: - Initialization

    /// Create a renderer backed by a shared context. The glyph atlas is shared
    /// across renderers that use the same base font and scale factor.
    public init(context: VVMetalContext, baseFont: VVFont, scaleFactor: CGFloat = 2.0) {
        self.context = context
        self.baseFont = baseFont
        self.glyphAtlas = context.sharedAtlas(baseFont: baseFont, scaleFactor: scaleFactor)
        setupUniformBuffers()
    }

    /// Legacy convenience: uses the process-wide shared ``VVMetalContext``.
    public convenience init(device: MTLDevice, baseFont: VVFont, scaleFactor: CGFloat = 2.0) throws {
        guard let ctx = VVMetalContext.shared else {
            throw MarkdownRendererError.failedToCreateCommandQueue
        }
        self.init(context: ctx, baseFont: baseFont, scaleFactor: scaleFactor)
    }

    private func setupUniformBuffers() {
        let size = MemoryLayout<MarkdownUniforms>.stride
        for _ in 0..<uniformBufferCount {
            if let buffer = context.device.makeBuffer(length: size, options: .storageModeShared) {
                buffer.label = "Markdown Uniform Buffer"
                uniformBuffers.append(buffer)
            }
        }
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

        encoder.setRenderPipelineState(context.glyphPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentTexture(texture, index: 0)
        encoder.setFragmentSamplerState(context.samplerState, index: 0)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderColorGlyphs(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard let atlasTexture = glyphAtlas.colorAtlasTexture else { return }
        renderColorGlyphs(encoder: encoder, instances: instances, instanceCount: instanceCount, texture: atlasTexture)
    }

    public func renderColorGlyphs(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int, texture: MTLTexture) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(context.colorGlyphPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentTexture(texture, index: 0)
        encoder.setFragmentSamplerState(context.samplerState, index: 0)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderQuads(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int, rounded: Bool = false) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(rounded ? context.roundedQuadPipeline : context.quadPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        if rounded {
            encoder.setFragmentBuffer(instances, offset: 0, index: 0)
        }

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderBullets(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(context.bulletPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderCheckboxes(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(context.checkboxPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderThematicBreaks(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(context.thematicBreakPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderBlockQuoteBorders(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(context.blockQuoteBorderPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderTableGrid(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(context.tableGridPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderLinkUnderlines(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(context.linkUnderlinePipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderStrikethroughs(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(context.strikethroughPipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderImages(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int, texture: MTLTexture) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(context.imagePipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentTexture(texture, index: 0)
        encoder.setFragmentSamplerState(context.imageSamplerState, index: 0)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    public func renderPieSlices(encoder: MTLRenderCommandEncoder, instances: MTLBuffer, instanceCount: Int) {
        guard instanceCount > 0 else { return }

        encoder.setRenderPipelineState(context.pieSlicePipeline)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentBuffer(instances, offset: 0, index: 0)
        encoder.setFragmentBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    // MARK: - Buffer Creation

    public func makeBuffer<T>(for instances: [T]) -> MTLBuffer? {
        context.makeBuffer(for: instances)
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
