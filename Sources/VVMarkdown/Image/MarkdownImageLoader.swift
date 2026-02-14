//  MarkdownImageLoader.swift
//  VVMarkdown
//
//  Async image loading and Metal texture creation for markdown images

import Foundation
@preconcurrency import Metal
import MetalKit
import CoreGraphics
import ImageIO

#if canImport(UniformTypeIdentifiers)
import UniformTypeIdentifiers
#endif

#if canImport(AppKit)
import AppKit
#else
import UIKit
#endif

// MARK: - Loaded Image

public struct LoadedMarkdownImage: Sendable {
    public let url: String
    public let texture: MTLTexture
    public let size: CGSize
    public let aspectRatio: CGFloat

    public init(url: String, texture: MTLTexture, size: CGSize) {
        self.url = url
        self.texture = texture
        self.size = size
        self.aspectRatio = size.width / max(1, size.height)
    }
}

// MARK: - Image Instance (for Metal rendering)

public struct ImageInstance {
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

// MARK: - Markdown Image Loader

public final class MarkdownImageLoader: @unchecked Sendable {

    // MARK: - Properties

    private let device: MTLDevice
    private var textureCache: [String: MTLTexture] = [:]
    private var loadingTasks: [String: Task<MTLTexture?, Never>] = [:]
    private var cacheOrder: [String] = []
    private let queue = DispatchQueue(label: "com.vvmarkdown.imageloader")
    private let textureLoader: MTKTextureLoader
    private let maxImageSize: CGFloat
    private let maxCacheEntries: Int
    private let placeholderTexture: MTLTexture?

    // MARK: - Initialization

    public init(device: MTLDevice, maxImageSize: CGFloat = 1024, maxCacheEntries: Int = 64) {
        self.device = device
        self.textureLoader = MTKTextureLoader(device: device)
        self.maxImageSize = maxImageSize
        self.maxCacheEntries = maxCacheEntries
        self.placeholderTexture = Self.createPlaceholderTexture(device: device)
    }

    // MARK: - Public API

    /// Load image from URL string (file path or http URL)
    public func loadImage(from urlString: String, completion: @escaping (LoadedMarkdownImage?) -> Void) {
        queue.async { [weak self] in
            guard let self = self else {
                completion(nil)
                return
            }

            if let cached = self.textureCache[urlString] {
                let size = CGSize(width: cached.width, height: cached.height)
                completion(LoadedMarkdownImage(url: urlString, texture: cached, size: size))
                return
            }

            if let task = self.loadingTasks[urlString] {
                Task {
                    if let texture = await task.value {
                        let size = CGSize(width: texture.width, height: texture.height)
                        completion(LoadedMarkdownImage(url: urlString, texture: texture, size: size))
                    } else {
                        completion(nil)
                    }
                }
                return
            }

            let task = Task<MTLTexture?, Never> { [weak self] in
                guard let self = self else { return nil }
                return await self.loadTextureAsync(from: urlString)
            }

            self.loadingTasks[urlString] = task

            Task {
                if let texture = await task.value {
                    self.queue.async {
                        self.textureCache[urlString] = texture
                        self.cacheOrder.removeAll(where: { $0 == urlString })
                        self.cacheOrder.append(urlString)
                        while self.cacheOrder.count > self.maxCacheEntries {
                            let evicted = self.cacheOrder.removeFirst()
                            self.textureCache.removeValue(forKey: evicted)
                        }
                        self.loadingTasks.removeValue(forKey: urlString)
                    }
                    let size = CGSize(width: texture.width, height: texture.height)
                    completion(LoadedMarkdownImage(url: urlString, texture: texture, size: size))
                } else {
                    self.queue.async {
                        self.loadingTasks.removeValue(forKey: urlString)
                    }
                    completion(nil)
                }
            }
        }
    }

    /// Synchronously get cached texture or placeholder
    public func cachedTexture(for urlString: String) -> MTLTexture? {
        queue.sync {
            textureCache[urlString] ?? placeholderTexture
        }
    }

    /// Get cached image size
    public func cachedImageSize(for urlString: String) -> CGSize? {
        queue.sync {
            if let texture = textureCache[urlString] {
                return CGSize(width: texture.width, height: texture.height)
            }
            return nil
        }
    }

    /// Preload images
    public func preloadImages(urls: [String]) {
        for url in urls {
            loadImage(from: url) { _ in }
        }
    }

    /// Clear cache
    public func clearCache() {
        queue.async {
            self.textureCache.removeAll()
            self.cacheOrder.removeAll()
        }
    }

    // MARK: - Private Methods

    private func loadTextureAsync(from urlString: String) async -> MTLTexture? {
        if urlString.hasPrefix("http://") || urlString.hasPrefix("https://") {
            return await loadFromNetwork(urlString: urlString)
        } else {
            return await loadFromFile(path: urlString)
        }
    }

    private func loadFromNetwork(urlString: String) async -> MTLTexture? {
        guard let url = URL(string: urlString) else { return nil }

        do {
            let (data, response) = try await URLSession.shared.data(from: url)

            guard let httpResponse = response as? HTTPURLResponse,
                  (200...299).contains(httpResponse.statusCode) else {
                return nil
            }

            return createTexture(from: data)
        } catch {
            return nil
        }
    }

    private func loadFromFile(path: String) async -> MTLTexture? {
        let expandedPath = (path as NSString).expandingTildeInPath
        let url: URL

        if path.hasPrefix("/") {
            url = URL(fileURLWithPath: expandedPath)
        } else if path.hasPrefix("file://") {
            guard let fileURL = URL(string: path) else { return nil }
            url = fileURL
        } else {
            url = URL(fileURLWithPath: FileManager.default.currentDirectoryPath).appendingPathComponent(path)
        }

        do {
            let data = try Data(contentsOf: url)
            return createTexture(from: data)
        } catch {
            return nil
        }
    }

    private func createTexture(from data: Data) -> MTLTexture? {
        if isSVGData(data) {
            if let svgImage = renderSVGImage(from: data) {
                return createTexture(from: svgImage)
            }
        }

        #if canImport(AppKit)
        guard let image = NSImage(data: data),
              let cgImage = image.cgImage(forProposedRect: nil, context: nil, hints: nil) else {
            return nil
        }
        #else
        guard let image = UIImage(data: data),
              let cgImage = image.cgImage else {
            return nil
        }
        #endif

        return createTexture(from: cgImage)
    }

    private func isSVGData(_ data: Data) -> Bool {
        guard let text = String(data: data, encoding: .utf8) else { return false }
        let lower = text.lowercased()
        return lower.contains("<svg") || lower.contains("image/svg+xml")
    }

    private func renderSVGImage(from data: Data) -> CGImage? {
        let options: [CFString: Any] = [
            kCGImageSourceTypeIdentifierHint: svgTypeIdentifier()
        ]
        guard let source = CGImageSourceCreateWithData(data as CFData, options as CFDictionary) else {
            return nil
        }
        return CGImageSourceCreateImageAtIndex(source, 0, options as CFDictionary)
    }

    private func svgTypeIdentifier() -> CFString {
        #if canImport(UniformTypeIdentifiers)
        if #available(macOS 11.0, iOS 14.0, tvOS 14.0, *) {
            return UTType.svg.identifier as CFString
        }
        #endif
        return "public.svg-image" as CFString
    }

    private func createTexture(from cgImage: CGImage) -> MTLTexture? {
        var width = cgImage.width
        var height = cgImage.height

        let scale = min(1.0, min(maxImageSize / CGFloat(width), maxImageSize / CGFloat(height)))
        if scale < 1.0 {
            width = Int(CGFloat(width) * scale)
            height = Int(CGFloat(height) * scale)
        }

        let descriptor = MTLTextureDescriptor.texture2DDescriptor(
            pixelFormat: .rgba8Unorm,
            width: width,
            height: height,
            mipmapped: false
        )
        descriptor.usage = [.shaderRead]
        descriptor.storageMode = device.hasUnifiedMemory ? .shared : .managed

        guard let texture = device.makeTexture(descriptor: descriptor) else {
            return nil
        }

        let colorSpace = CGColorSpaceCreateDeviceRGB()
        let bytesPerPixel = 4
        let bytesPerRow = bytesPerPixel * width
        var pixelData = [UInt8](repeating: 0, count: width * height * bytesPerPixel)

        guard let context = CGContext(
            data: &pixelData,
            width: width,
            height: height,
            bitsPerComponent: 8,
            bytesPerRow: bytesPerRow,
            space: colorSpace,
            bitmapInfo: CGImageAlphaInfo.premultipliedLast.rawValue
        ) else {
            return nil
        }

        context.draw(cgImage, in: CGRect(x: 0, y: 0, width: width, height: height))

        let region = MTLRegion(origin: MTLOrigin(x: 0, y: 0, z: 0), size: MTLSize(width: width, height: height, depth: 1))
        texture.replace(region: region, mipmapLevel: 0, withBytes: pixelData, bytesPerRow: bytesPerRow)

        return texture
    }

    private static func createPlaceholderTexture(device: MTLDevice) -> MTLTexture? {
        let size = 64
        let descriptor = MTLTextureDescriptor.texture2DDescriptor(
            pixelFormat: .rgba8Unorm,
            width: size,
            height: size,
            mipmapped: false
        )
        descriptor.usage = [.shaderRead]
        descriptor.storageMode = device.hasUnifiedMemory ? .shared : .managed

        guard let texture = device.makeTexture(descriptor: descriptor) else {
            return nil
        }

        var pixelData = [UInt8](repeating: 0, count: size * size * 4)
        for y in 0..<size {
            for x in 0..<size {
                let index = (y * size + x) * 4
                let isCheckerDark = ((x / 8) + (y / 8)) % 2 == 0
                let gray: UInt8 = isCheckerDark ? 60 : 80
                pixelData[index] = gray
                pixelData[index + 1] = gray
                pixelData[index + 2] = gray
                pixelData[index + 3] = 255
            }
        }

        let region = MTLRegion(origin: MTLOrigin(x: 0, y: 0, z: 0), size: MTLSize(width: size, height: size, depth: 1))
        texture.replace(region: region, mipmapLevel: 0, withBytes: pixelData, bytesPerRow: size * 4)

        return texture
    }
}
