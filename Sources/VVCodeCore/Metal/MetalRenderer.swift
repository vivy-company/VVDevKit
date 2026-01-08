import Foundation
import Metal
import MetalKit
import simd

/// Main Metal renderer coordinating all text rendering operations
public final class MetalRenderer {

    // MARK: - Properties

    public let device: MTLDevice
    public let commandQueue: MTLCommandQueue
    public let glyphAtlas: GlyphAtlasManager

    // Pipeline states
    private var glyphPipelineState: MTLRenderPipelineState!
    private var colorGlyphPipelineState: MTLRenderPipelineState!
    private var gutterColorGlyphPipelineState: MTLRenderPipelineState!
    private var selectionPipelineState: MTLRenderPipelineState!
    private var cursorPipelineState: MTLRenderPipelineState!
    private var gutterPipelineState: MTLRenderPipelineState!
    private var underlinePipelineState: MTLRenderPipelineState!

    // Uniform buffer (triple buffered)
    private var uniformBuffers: [MTLBuffer] = []
    private var currentUniformBufferIndex = 0
    private let uniformBufferCount = 3

    // Sampler state
    private var samplerState: MTLSamplerState!

    // Current uniforms
    public var uniforms = TextUniforms()

    // MARK: - Initialization

    public init(device: MTLDevice, baseFont: NSFont, scaleFactor: CGFloat = 2.0) throws {
        self.device = device

        guard let queue = device.makeCommandQueue() else {
            throw MetalRendererError.failedToCreateCommandQueue
        }
        self.commandQueue = queue
        self.glyphAtlas = GlyphAtlasManager(device: device, baseFont: baseFont, scaleFactor: scaleFactor)

        try setupPipelines()
        setupUniformBuffers()
        setupSampler()

    }

    // MARK: - Pipeline Setup

    private func setupPipelines() throws {
        // Try loading compiled metallib from package bundle (SPM with .process())
        if let library = MetalRenderer.loadMetalLibrary(device: device) {
            try setupPipelinesWithLibrary(library)
            return
        }

        // Try loading shader source from bundle (SPM with .copy())
        if let source = MetalRenderer.loadShaderSource(),
           let library = try? device.makeLibrary(source: source, options: nil) {
            try setupPipelinesWithLibrary(library)
            return
        }

        // Try default library (Xcode project with .metal files in main target)
        if let library = device.makeDefaultLibrary() {
            try setupPipelinesWithLibrary(library)
            return
        }

        fatalError("MetalRenderer: Could not load shader. Ensure Shaders.metal is included in package resources or compiled by Xcode.")
    }

    private func setupPipelinesWithLibrary(_ library: MTLLibrary) throws {
        // Glyph pipeline
        glyphPipelineState = try createPipeline(
            library: library,
            vertexFunction: "glyphVertexShader",
            fragmentFunction: "msdfFragmentShader",
            label: "Glyph Pipeline"
        )

        // Color glyph pipeline (emoji/color fonts)
        colorGlyphPipelineState = try createPipeline(
            library: library,
            vertexFunction: "glyphVertexShader",
            fragmentFunction: "colorGlyphFragmentShader",
            label: "Color Glyph Pipeline"
        )

        // Selection pipeline
        selectionPipelineState = try createPipeline(
            library: library,
            vertexFunction: "selectionVertexShader",
            fragmentFunction: "selectionFragmentShader",
            label: "Selection Pipeline"
        )

        // Cursor pipeline
        cursorPipelineState = try createPipeline(
            library: library,
            vertexFunction: "selectionVertexShader",
            fragmentFunction: "cursorFragmentShader",
            label: "Cursor Pipeline"
        )

        // Gutter pipeline
        gutterPipelineState = try createPipeline(
            library: library,
            vertexFunction: "gutterVertexShader",
            fragmentFunction: "msdfFragmentShader",
            label: "Gutter Pipeline"
        )

        // Gutter color glyph pipeline (emoji/color fonts)
        gutterColorGlyphPipelineState = try createPipeline(
            library: library,
            vertexFunction: "gutterVertexShader",
            fragmentFunction: "colorGlyphFragmentShader",
            label: "Gutter Color Glyph Pipeline"
        )

        // Underline pipeline
        underlinePipelineState = try createPipeline(
            library: library,
            vertexFunction: "underlineVertexShader",
            fragmentFunction: "wavyUnderlineFragmentShader",
            label: "Underline Pipeline"
        )
    }

    private static func loadShaderSource() -> String? {
        #if SWIFT_PACKAGE
        let bundle = Bundle.module
        #else
        let bundle = Bundle(for: MetalRenderer.self)
        #endif

        guard let url = bundle.url(forResource: "Shaders", withExtension: "metal") else {
            return nil
        }

        return try? String(contentsOf: url, encoding: .utf8)
    }

    private static func loadMetalLibrary(device: MTLDevice) -> MTLLibrary? {
        #if SWIFT_PACKAGE
        let bundle = Bundle.module
        #else
        let bundle = Bundle(for: MetalRenderer.self)
        #endif

        // Xcode compiles .metal files to default.metallib
        guard let url = bundle.url(forResource: "default", withExtension: "metallib") else {
            return nil
        }

        return try? device.makeLibrary(URL: url)
    }

    private func createPipeline(
        library: MTLLibrary,
        vertexFunction: String,
        fragmentFunction: String,
        label: String
    ) throws -> MTLRenderPipelineState {
        guard let vertexFn = library.makeFunction(name: vertexFunction),
              let fragmentFn = library.makeFunction(name: fragmentFunction) else {
            throw MetalRendererError.failedToCreateShaderFunction(vertexFunction)
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
        let uniformSize = MemoryLayout<TextUniforms>.stride
        for _ in 0..<uniformBufferCount {
            if let buffer = device.makeBuffer(length: uniformSize, options: .storageModeShared) {
                buffer.label = "Uniform Buffer"
                uniformBuffers.append(buffer)
            }
        }
    }

    private func setupSampler() {
        let descriptor = MTLSamplerDescriptor()
        // Use nearest neighbor for crisp text (matches shader constexpr sampler)
        descriptor.minFilter = .nearest
        descriptor.magFilter = .nearest
        descriptor.mipFilter = .notMipmapped
        descriptor.sAddressMode = .clampToEdge
        descriptor.tAddressMode = .clampToEdge
        samplerState = device.makeSamplerState(descriptor: descriptor)
    }

    // MARK: - Rendering

    /// Begin a new frame - call before any rendering
    public func beginFrame(viewportSize: CGSize, scrollOffset: CGPoint) {
        uniforms.viewportSize = SIMD2<Float>(Float(viewportSize.width), Float(viewportSize.height))
        uniforms.scrollOffset = SIMD2<Float>(Float(scrollOffset.x), Float(scrollOffset.y))
        uniforms.projectionMatrix = TextUniforms.orthographic(
            width: Float(viewportSize.width),
            height: Float(viewportSize.height)
        )
        uniforms.time = Float(CACurrentMediaTime().truncatingRemainder(dividingBy: 2.0))

        // Atlas size for pixel coordinate sampling
        uniforms.atlasSize = SIMD2<Float>(Float(GlyphAtlasManager.atlasSize), Float(GlyphAtlasManager.atlasSize))
        uniforms.pxRange = 1.0  // Not used in simple alpha mode

        // Update uniform buffer
        currentUniformBufferIndex = (currentUniformBufferIndex + 1) % uniformBufferCount
        let buffer = uniformBuffers[currentUniformBufferIndex]
        memcpy(buffer.contents(), &uniforms, MemoryLayout<TextUniforms>.stride)
    }

    /// Render glyphs
    public func renderGlyphs(
        encoder: MTLRenderCommandEncoder,
        instances: MTLBuffer,
        instanceCount: Int
    ) {
        guard instanceCount > 0, let atlasTexture = glyphAtlas.atlasTexture else { return }

        encoder.setRenderPipelineState(glyphPipelineState)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentTexture(atlasTexture, index: 0)
        encoder.setFragmentSamplerState(samplerState, index: 0)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    /// Render color glyphs (emoji/color fonts)
    public func renderColorGlyphs(
        encoder: MTLRenderCommandEncoder,
        instances: MTLBuffer,
        instanceCount: Int
    ) {
        guard instanceCount > 0, let atlasTexture = glyphAtlas.colorAtlasTexture else { return }

        encoder.setRenderPipelineState(colorGlyphPipelineState)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentTexture(atlasTexture, index: 0)
        encoder.setFragmentSamplerState(samplerState, index: 0)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    /// Render gutter (line numbers)
    public func renderGutter(
        encoder: MTLRenderCommandEncoder,
        instances: MTLBuffer,
        instanceCount: Int
    ) {
        guard instanceCount > 0, let atlasTexture = glyphAtlas.atlasTexture else { return }

        encoder.setRenderPipelineState(gutterPipelineState)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentTexture(atlasTexture, index: 0)
        encoder.setFragmentSamplerState(samplerState, index: 0)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    /// Render color glyphs in gutter (emoji/color fonts)
    public func renderGutterColorGlyphs(
        encoder: MTLRenderCommandEncoder,
        instances: MTLBuffer,
        instanceCount: Int
    ) {
        guard instanceCount > 0, let atlasTexture = glyphAtlas.colorAtlasTexture else { return }

        encoder.setRenderPipelineState(gutterColorGlyphPipelineState)
        encoder.setVertexBuffer(instances, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentTexture(atlasTexture, index: 0)
        encoder.setFragmentSamplerState(samplerState, index: 0)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: instanceCount)
    }

    /// Render selection rectangles
    public func renderSelections(
        encoder: MTLRenderCommandEncoder,
        quads: MTLBuffer,
        quadCount: Int
    ) {
        guard quadCount > 0 else { return }

        encoder.setRenderPipelineState(selectionPipelineState)
        encoder.setVertexBuffer(quads, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: quadCount)
    }

    /// Render cursor
    public func renderCursor(
        encoder: MTLRenderCommandEncoder,
        quads: MTLBuffer,
        quadCount: Int
    ) {
        guard quadCount > 0 else { return }

        encoder.setRenderPipelineState(cursorPipelineState)
        encoder.setVertexBuffer(quads, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)
        encoder.setFragmentBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: quadCount)
    }

    /// Render underlines (for diagnostics)
    public func renderUnderlines(
        encoder: MTLRenderCommandEncoder,
        quads: MTLBuffer,
        quadCount: Int
    ) {
        guard quadCount > 0 else { return }

        encoder.setRenderPipelineState(underlinePipelineState)
        encoder.setVertexBuffer(quads, offset: 0, index: 0)
        encoder.setVertexBuffer(uniformBuffers[currentUniformBufferIndex], offset: 0, index: 1)

        encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: quadCount)
    }

    // MARK: - Buffer Creation

    /// Create a buffer for glyph instances
    public func makeGlyphInstanceBuffer(capacity: Int) -> MTLBuffer? {
        let size = MemoryLayout<GlyphInstance>.stride * capacity
        return device.makeBuffer(length: size, options: .storageModeShared)
    }

    /// Create a buffer for selection quads
    public func makeSelectionQuadBuffer(capacity: Int) -> MTLBuffer? {
        let size = MemoryLayout<SelectionQuad>.stride * capacity
        return device.makeBuffer(length: size, options: .storageModeShared)
    }

    // MARK: - Font Update

    public func updateFont(_ font: NSFont, scaleFactor: CGFloat? = nil) {
        glyphAtlas.updateFont(font, scaleFactor: scaleFactor)
    }
}

// MARK: - Errors

public enum MetalRendererError: Error {
    case failedToCreateCommandQueue
    case failedToLoadShaderLibrary
    case failedToCreateShaderFunction(String)
    case failedToCreatePipelineState
}
