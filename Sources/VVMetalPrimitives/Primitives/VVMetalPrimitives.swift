import CoreGraphics
import simd

public enum VVFontVariant: Hashable, Sendable {
    case regular
    case semibold
    case semiboldItalic
    case bold
    case italic
    case boldItalic
    case monospace
    case emoji
}

public struct VVTextRunStyle: Hashable, Sendable {
    public var isStrikethrough: Bool
    public var isLink: Bool
    public var linkURL: String?
    public var color: SIMD4<Float>

    public init(isStrikethrough: Bool = false, isLink: Bool = false, linkURL: String? = nil, color: SIMD4<Float> = SIMD4(1, 1, 1, 1)) {
        self.isStrikethrough = isStrikethrough
        self.isLink = isLink
        self.linkURL = linkURL
        self.color = color
    }
}

public struct VVTextGlyph: Hashable, Sendable {
    public let glyphID: UInt16
    public let position: CGPoint
    public let size: CGSize
    public let color: SIMD4<Float>
    public let fontVariant: VVFontVariant
    public let fontSize: CGFloat
    public let fontName: String?
    public let stringIndex: Int?

    public init(
        glyphID: UInt16,
        position: CGPoint,
        size: CGSize,
        color: SIMD4<Float>,
        fontVariant: VVFontVariant,
        fontSize: CGFloat,
        fontName: String? = nil,
        stringIndex: Int? = nil
    ) {
        self.glyphID = glyphID
        self.position = position
        self.size = size
        self.color = color
        self.fontVariant = fontVariant
        self.fontSize = fontSize
        self.fontName = fontName
        self.stringIndex = stringIndex
    }
}

public struct VVTextRunPrimitive: Hashable, Sendable {
    public var glyphs: [VVTextGlyph]
    public var style: VVTextRunStyle
    public var lineBounds: CGRect?
    public var runBounds: CGRect?
    public var position: CGPoint
    public var fontSize: CGFloat

    public init(
        glyphs: [VVTextGlyph],
        style: VVTextRunStyle,
        lineBounds: CGRect? = nil,
        runBounds: CGRect? = nil,
        position: CGPoint = .zero,
        fontSize: CGFloat = 14
    ) {
        self.glyphs = glyphs
        self.style = style
        self.lineBounds = lineBounds
        self.runBounds = runBounds
        self.position = position
        self.fontSize = fontSize
    }
}

public struct VVQuadPrimitive: Hashable, Sendable {
    public var frame: CGRect
    public var color: SIMD4<Float>
    public var cornerRadius: CGFloat

    public init(frame: CGRect, color: SIMD4<Float>, cornerRadius: CGFloat = 0) {
        self.frame = frame
        self.color = color
        self.cornerRadius = cornerRadius
    }
}

public struct VVLinePrimitive: Hashable, Sendable {
    public var start: CGPoint
    public var end: CGPoint
    public var thickness: CGFloat
    public var color: SIMD4<Float>

    public init(start: CGPoint, end: CGPoint, thickness: CGFloat, color: SIMD4<Float>) {
        self.start = start
        self.end = end
        self.thickness = thickness
        self.color = color
    }
}

public enum VVBulletType: Hashable, Sendable {
    case disc
    case circle
    case square
    case number(Int)
    case checkbox(Bool)
}

public struct VVBulletPrimitive: Hashable, Sendable {
    public var position: CGPoint
    public var size: CGFloat
    public var color: SIMD4<Float>
    public var type: VVBulletType

    public init(position: CGPoint, size: CGFloat, color: SIMD4<Float>, type: VVBulletType) {
        self.position = position
        self.size = size
        self.color = color
        self.type = type
    }
}

public struct VVImagePrimitive: Hashable, Sendable {
    public var url: String
    public var frame: CGRect
    public var cornerRadius: CGFloat

    public init(url: String, frame: CGRect, cornerRadius: CGFloat = 4) {
        self.url = url
        self.frame = frame
        self.cornerRadius = cornerRadius
    }
}

public struct VVBlockQuoteBorderPrimitive: Hashable, Sendable {
    public var frame: CGRect
    public var color: SIMD4<Float>
    public var borderWidth: CGFloat

    public init(frame: CGRect, color: SIMD4<Float>, borderWidth: CGFloat) {
        self.frame = frame
        self.color = color
        self.borderWidth = borderWidth
    }
}

public struct VVTableLinePrimitive: Hashable, Sendable {
    public var start: CGPoint
    public var end: CGPoint
    public var color: SIMD4<Float>
    public var lineWidth: CGFloat

    public init(start: CGPoint, end: CGPoint, color: SIMD4<Float>, lineWidth: CGFloat) {
        self.start = start
        self.end = end
        self.color = color
        self.lineWidth = lineWidth
    }
}

public struct VVPieSlicePrimitive: Hashable, Sendable {
    public var center: CGPoint
    public var radius: CGFloat
    public var startAngle: CGFloat
    public var endAngle: CGFloat
    public var color: SIMD4<Float>

    public init(center: CGPoint, radius: CGFloat, startAngle: CGFloat, endAngle: CGFloat, color: SIMD4<Float>) {
        self.center = center
        self.radius = radius
        self.startAngle = startAngle
        self.endAngle = endAngle
        self.color = color
    }
}
