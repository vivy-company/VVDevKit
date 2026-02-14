import CoreGraphics
import simd

// MARK: - Geometry Types

/// Per-corner radii for rounded rectangles.
public struct VVCornerRadii: Hashable, Sendable {
    public var topLeft: CGFloat
    public var topRight: CGFloat
    public var bottomLeft: CGFloat
    public var bottomRight: CGFloat

    public init(topLeft: CGFloat = 0, topRight: CGFloat = 0, bottomLeft: CGFloat = 0, bottomRight: CGFloat = 0) {
        self.topLeft = topLeft
        self.topRight = topRight
        self.bottomLeft = bottomLeft
        self.bottomRight = bottomRight
    }

    public init(_ uniform: CGFloat) {
        self.topLeft = uniform
        self.topRight = uniform
        self.bottomLeft = uniform
        self.bottomRight = uniform
    }

    public static let zero = VVCornerRadii(0)

    public var isZero: Bool {
        topLeft == 0 && topRight == 0 && bottomLeft == 0 && bottomRight == 0
    }

    public var isUniform: Bool {
        topLeft == topRight && topRight == bottomLeft && bottomLeft == bottomRight
    }

    public var maxRadius: CGFloat {
        max(max(topLeft, topRight), max(bottomLeft, bottomRight))
    }
}

/// Per-edge widths for borders and insets.
public struct VVEdgeWidths: Hashable, Sendable {
    public var top: CGFloat
    public var right: CGFloat
    public var bottom: CGFloat
    public var left: CGFloat

    public init(top: CGFloat = 0, right: CGFloat = 0, bottom: CGFloat = 0, left: CGFloat = 0) {
        self.top = top
        self.right = right
        self.bottom = bottom
        self.left = left
    }

    public init(_ uniform: CGFloat) {
        self.top = uniform
        self.right = uniform
        self.bottom = uniform
        self.left = uniform
    }

    public static let zero = VVEdgeWidths(0)

    public var isZero: Bool {
        top == 0 && right == 0 && bottom == 0 && left == 0
    }
}

// MARK: - Transform

/// 2D affine transformation matrix.
public struct VVTransform2D: Hashable, Sendable {
    public var m00: Float
    public var m01: Float
    public var m10: Float
    public var m11: Float
    public var tx: Float
    public var ty: Float

    public init(m00: Float, m01: Float, m10: Float, m11: Float, tx: Float, ty: Float) {
        self.m00 = m00
        self.m01 = m01
        self.m10 = m10
        self.m11 = m11
        self.tx = tx
        self.ty = ty
    }

    public static let identity = VVTransform2D(m00: 1, m01: 0, m10: 0, m11: 1, tx: 0, ty: 0)

    public var isIdentity: Bool {
        m00 == 1 && m01 == 0 && m10 == 0 && m11 == 1 && tx == 0 && ty == 0
    }

    public func translated(by point: CGPoint) -> VVTransform2D {
        VVTransform2D(m00: m00, m01: m01, m10: m10, m11: m11,
                      tx: tx + Float(point.x), ty: ty + Float(point.y))
    }

    public func rotated(by angle: CGFloat) -> VVTransform2D {
        let c = Float(cos(angle))
        let s = Float(sin(angle))
        return composed(with: VVTransform2D(m00: c, m01: -s, m10: s, m11: c, tx: 0, ty: 0))
    }

    public func scaled(by factor: CGFloat) -> VVTransform2D {
        scaled(x: factor, y: factor)
    }

    public func scaled(x sx: CGFloat, y sy: CGFloat) -> VVTransform2D {
        let fsx = Float(sx)
        let fsy = Float(sy)
        return composed(with: VVTransform2D(m00: fsx, m01: 0, m10: 0, m11: fsy, tx: 0, ty: 0))
    }

    public func composed(with other: VVTransform2D) -> VVTransform2D {
        VVTransform2D(
            m00: m00 * other.m00 + m01 * other.m10,
            m01: m00 * other.m01 + m01 * other.m11,
            m10: m10 * other.m00 + m11 * other.m10,
            m11: m10 * other.m01 + m11 * other.m11,
            tx: tx * other.m00 + ty * other.m10 + other.tx,
            ty: tx * other.m01 + ty * other.m11 + other.ty
        )
    }

    public func apply(to point: CGPoint) -> CGPoint {
        let x = Float(point.x)
        let y = Float(point.y)
        return CGPoint(
            x: CGFloat(m00 * x + m01 * y + tx),
            y: CGFloat(m10 * x + m11 * y + ty)
        )
    }
}

// MARK: - Border & Style Types

public enum VVBorderStyle: Hashable, Sendable {
    case solid
    case dashed(dashLength: CGFloat, gapLength: CGFloat)
}

public struct VVBorder: Hashable, Sendable {
    public var widths: VVEdgeWidths
    public var color: SIMD4<Float>
    public var style: VVBorderStyle

    public init(widths: VVEdgeWidths, color: SIMD4<Float>, style: VVBorderStyle = .solid) {
        self.widths = widths
        self.color = color
        self.style = style
    }

    public init(width: CGFloat, color: SIMD4<Float>, style: VVBorderStyle = .solid) {
        self.widths = VVEdgeWidths(width)
        self.color = color
        self.style = style
    }
}

public enum VVLineDash: Hashable, Sendable {
    case solid
    case dashed(on: CGFloat, off: CGFloat)
    case pattern([CGFloat])
}

public enum VVFillPattern: Hashable, Sendable {
    case slash(spacing: CGFloat, color: SIMD4<Float>)
    case checkerboard(size: CGFloat, color1: SIMD4<Float>, color2: SIMD4<Float>)
}

// MARK: - Text Primitives

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
    public var isWavyUnderline: Bool
    public var linkURL: String?
    public var color: SIMD4<Float>

    public init(
        isStrikethrough: Bool = false,
        isLink: Bool = false,
        isWavyUnderline: Bool = false,
        linkURL: String? = nil,
        color: SIMD4<Float> = .white
    ) {
        self.isStrikethrough = isStrikethrough
        self.isLink = isLink
        self.isWavyUnderline = isWavyUnderline
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

// MARK: - Quad Primitives

public struct VVQuadPrimitive: Hashable, Sendable {
    public var frame: CGRect
    public var color: SIMD4<Float>
    public var cornerRadii: VVCornerRadii
    public var border: VVBorder?
    public var opacity: Float

    /// Backward-compatible convenience for uniform corner radius.
    public var cornerRadius: CGFloat {
        get { cornerRadii.topLeft }
        set { cornerRadii = VVCornerRadii(newValue) }
    }

    public init(frame: CGRect, color: SIMD4<Float>, cornerRadius: CGFloat = 0) {
        self.frame = frame
        self.color = color
        self.cornerRadii = VVCornerRadii(cornerRadius)
        self.border = nil
        self.opacity = 1
    }

    public init(
        frame: CGRect,
        color: SIMD4<Float>,
        cornerRadii: VVCornerRadii,
        border: VVBorder? = nil,
        opacity: Float = 1
    ) {
        self.frame = frame
        self.color = color
        self.cornerRadii = cornerRadii
        self.border = border
        self.opacity = opacity
    }
}

public enum VVGradientDirection: Hashable, Sendable {
    case horizontal
    case vertical
}

public struct VVGradientQuadPrimitive: Hashable, Sendable {
    public var frame: CGRect
    public var startColor: SIMD4<Float>
    public var endColor: SIMD4<Float>
    public var direction: VVGradientDirection
    public var cornerRadii: VVCornerRadii
    public var angle: CGFloat?
    public var steps: Int

    /// Backward-compatible convenience for uniform corner radius.
    public var cornerRadius: CGFloat {
        get { cornerRadii.topLeft }
        set { cornerRadii = VVCornerRadii(newValue) }
    }

    public init(
        frame: CGRect,
        startColor: SIMD4<Float>,
        endColor: SIMD4<Float>,
        direction: VVGradientDirection = .horizontal,
        cornerRadius: CGFloat = 0,
        steps: Int = 12
    ) {
        self.frame = frame
        self.startColor = startColor
        self.endColor = endColor
        self.direction = direction
        self.cornerRadii = VVCornerRadii(cornerRadius)
        self.angle = nil
        self.steps = steps
    }

    public init(
        frame: CGRect,
        startColor: SIMD4<Float>,
        endColor: SIMD4<Float>,
        angle: CGFloat,
        cornerRadii: VVCornerRadii = .zero,
        steps: Int = 12
    ) {
        self.frame = frame
        self.startColor = startColor
        self.endColor = endColor
        self.direction = .horizontal
        self.angle = angle
        self.cornerRadii = cornerRadii
        self.steps = steps
    }
}

/// Shadow primitive with blur support. Falls back to layered quads when blur is unavailable.
public struct VVShadowQuadPrimitive: Hashable, Sendable {
    public var frame: CGRect
    public var color: SIMD4<Float>
    public var cornerRadii: VVCornerRadii
    public var spread: CGFloat
    public var blurRadius: CGFloat
    public var offset: CGPoint
    public var steps: Int

    /// Backward-compatible convenience for uniform corner radius.
    public var cornerRadius: CGFloat {
        get { cornerRadii.topLeft }
        set { cornerRadii = VVCornerRadii(newValue) }
    }

    public init(
        frame: CGRect,
        color: SIMD4<Float>,
        cornerRadius: CGFloat = 0,
        spread: CGFloat = 10,
        steps: Int = 6
    ) {
        self.frame = frame
        self.color = color
        self.cornerRadii = VVCornerRadii(cornerRadius)
        self.spread = max(0, spread)
        self.blurRadius = 0
        self.offset = .zero
        self.steps = max(1, steps)
    }

    public init(
        frame: CGRect,
        color: SIMD4<Float>,
        cornerRadii: VVCornerRadii = .zero,
        spread: CGFloat = 10,
        blurRadius: CGFloat = 0,
        offset: CGPoint = .zero,
        steps: Int = 6
    ) {
        self.frame = frame
        self.color = color
        self.cornerRadii = cornerRadii
        self.spread = max(0, spread)
        self.blurRadius = max(0, blurRadius)
        self.offset = offset
        self.steps = max(1, steps)
    }

    public func expandedQuads() -> [VVQuadPrimitive] {
        guard frame.width > 0, frame.height > 0 else { return [] }
        let effectiveSpread = spread + blurRadius
        let layerCount = max(1, steps)
        var result: [VVQuadPrimitive] = []
        result.reserveCapacity(layerCount)

        for index in 0..<layerCount {
            let t = Float(index + 1) / Float(layerCount)
            let inset = effectiveSpread * CGFloat(t)
            let alpha = max(0, color.w * (1 - t * 0.65) / Float(layerCount))
            guard alpha > 0 else { continue }
            let layerColor = SIMD4<Float>(color.x, color.y, color.z, alpha)
            let layerFrame = frame.offsetBy(dx: offset.x, dy: offset.y).insetBy(dx: -inset, dy: -inset)
            let expandedRadii = VVCornerRadii(
                topLeft: max(0, cornerRadii.topLeft + inset),
                topRight: max(0, cornerRadii.topRight + inset),
                bottomLeft: max(0, cornerRadii.bottomLeft + inset),
                bottomRight: max(0, cornerRadii.bottomRight + inset)
            )
            result.append(VVQuadPrimitive(frame: layerFrame, color: layerColor, cornerRadii: expandedRadii))
        }

        return result
    }
}

// MARK: - Line Primitive

public struct VVLinePrimitive: Hashable, Sendable {
    public var start: CGPoint
    public var end: CGPoint
    public var thickness: CGFloat
    public var color: SIMD4<Float>
    public var dash: VVLineDash

    public init(start: CGPoint, end: CGPoint, thickness: CGFloat, color: SIMD4<Float>, dash: VVLineDash = .solid) {
        self.start = start
        self.end = end
        self.thickness = thickness
        self.color = color
        self.dash = dash
    }
}

// MARK: - Underline Primitive

public struct VVUnderlinePrimitive: Hashable, Sendable {
    public var origin: CGPoint
    public var width: CGFloat
    public var thickness: CGFloat
    public var color: SIMD4<Float>
    public var wavy: Bool

    public init(origin: CGPoint, width: CGFloat, thickness: CGFloat = 1, color: SIMD4<Float>, wavy: Bool = false) {
        self.origin = origin
        self.width = width
        self.thickness = thickness
        self.color = color
        self.wavy = wavy
    }
}

// MARK: - Bullet Primitive

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

// MARK: - Image Primitive

public struct VVImagePrimitive: Hashable, Sendable {
    public var url: String
    public var frame: CGRect
    public var cornerRadii: VVCornerRadii
    public var opacity: Float
    public var grayscale: Bool

    /// Backward-compatible convenience for uniform corner radius.
    public var cornerRadius: CGFloat {
        get { cornerRadii.topLeft }
        set { cornerRadii = VVCornerRadii(newValue) }
    }

    public init(url: String, frame: CGRect, cornerRadius: CGFloat = 4) {
        self.url = url
        self.frame = frame
        self.cornerRadii = VVCornerRadii(cornerRadius)
        self.opacity = 1
        self.grayscale = false
    }

    public init(
        url: String,
        frame: CGRect,
        cornerRadii: VVCornerRadii,
        opacity: Float = 1,
        grayscale: Bool = false
    ) {
        self.url = url
        self.frame = frame
        self.cornerRadii = cornerRadii
        self.opacity = opacity
        self.grayscale = grayscale
    }
}

// MARK: - Block Quote Border

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

// MARK: - Table Line

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

// MARK: - Pie Slice

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

// MARK: - Path Primitive

public struct VVPathVertex: Hashable, Sendable {
    public var position: CGPoint
    public var stPosition: CGPoint

    public init(position: CGPoint, stPosition: CGPoint = .zero) {
        self.position = position
        self.stPosition = stPosition
    }
}

public struct VVStrokeStyle: Hashable, Sendable {
    public var color: SIMD4<Float>
    public var width: CGFloat
    public var dash: VVLineDash

    public init(color: SIMD4<Float>, width: CGFloat = 1, dash: VVLineDash = .solid) {
        self.color = color
        self.width = width
        self.dash = dash
    }
}

public struct VVPathPrimitive: Hashable, Sendable {
    public var vertices: [VVPathVertex]
    public var fill: SIMD4<Float>?
    public var stroke: VVStrokeStyle?
    public var bounds: CGRect
    public var transform: VVTransform2D

    public init(
        vertices: [VVPathVertex],
        fill: SIMD4<Float>? = nil,
        stroke: VVStrokeStyle? = nil,
        bounds: CGRect = .zero,
        transform: VVTransform2D = .identity
    ) {
        self.vertices = vertices
        self.fill = fill
        self.stroke = stroke
        self.bounds = bounds
        self.transform = transform
    }
}

// MARK: - Path Builder

public enum VVPathCommand: Hashable, Sendable {
    case moveTo(CGPoint)
    case lineTo(CGPoint)
    case quadCurveTo(to: CGPoint, control: CGPoint)
    case cubicCurveTo(to: CGPoint, control1: CGPoint, control2: CGPoint)
    case close
}

public struct VVPathBuilder: Sendable {
    private var commands: [VVPathCommand] = []
    private var currentPoint: CGPoint = .zero
    private var startPoint: CGPoint = .zero

    public init() {}

    public mutating func move(to point: CGPoint) {
        commands.append(.moveTo(point))
        currentPoint = point
        startPoint = point
    }

    public mutating func line(to point: CGPoint) {
        commands.append(.lineTo(point))
        currentPoint = point
    }

    public mutating func quadCurve(to point: CGPoint, control: CGPoint) {
        commands.append(.quadCurveTo(to: point, control: control))
        currentPoint = point
    }

    public mutating func cubicCurve(to point: CGPoint, control1: CGPoint, control2: CGPoint) {
        commands.append(.cubicCurveTo(to: point, control1: control1, control2: control2))
        currentPoint = point
    }

    public mutating func addArc(center: CGPoint, radius: CGFloat, startAngle: CGFloat, endAngle: CGFloat, clockwise: Bool = false) {
        let segments = max(4, Int(abs(endAngle - startAngle) / (.pi / 8)))
        let step = (endAngle - startAngle) / CGFloat(segments)
        let start = CGPoint(x: center.x + radius * cos(startAngle), y: center.y + radius * sin(startAngle))
        if commands.isEmpty {
            move(to: start)
        } else {
            line(to: start)
        }
        for i in 1...segments {
            let angle = startAngle + step * CGFloat(i)
            let pt = CGPoint(x: center.x + radius * cos(angle), y: center.y + radius * sin(angle))
            line(to: pt)
        }
    }

    public mutating func addRect(_ rect: CGRect) {
        move(to: rect.origin)
        line(to: CGPoint(x: rect.maxX, y: rect.minY))
        line(to: CGPoint(x: rect.maxX, y: rect.maxY))
        line(to: CGPoint(x: rect.minX, y: rect.maxY))
        close()
    }

    public mutating func addRoundedRect(_ rect: CGRect, cornerRadii: VVCornerRadii) {
        let tl = min(cornerRadii.topLeft, rect.width / 2, rect.height / 2)
        let tr = min(cornerRadii.topRight, rect.width / 2, rect.height / 2)
        let bl = min(cornerRadii.bottomLeft, rect.width / 2, rect.height / 2)
        let br = min(cornerRadii.bottomRight, rect.width / 2, rect.height / 2)

        move(to: CGPoint(x: rect.minX + tl, y: rect.minY))
        line(to: CGPoint(x: rect.maxX - tr, y: rect.minY))
        if tr > 0 { addArc(center: CGPoint(x: rect.maxX - tr, y: rect.minY + tr), radius: tr, startAngle: -.pi / 2, endAngle: 0) }
        line(to: CGPoint(x: rect.maxX, y: rect.maxY - br))
        if br > 0 { addArc(center: CGPoint(x: rect.maxX - br, y: rect.maxY - br), radius: br, startAngle: 0, endAngle: .pi / 2) }
        line(to: CGPoint(x: rect.minX + bl, y: rect.maxY))
        if bl > 0 { addArc(center: CGPoint(x: rect.minX + bl, y: rect.maxY - bl), radius: bl, startAngle: .pi / 2, endAngle: .pi) }
        line(to: CGPoint(x: rect.minX, y: rect.minY + tl))
        if tl > 0 { addArc(center: CGPoint(x: rect.minX + tl, y: rect.minY + tl), radius: tl, startAngle: .pi, endAngle: .pi * 1.5) }
        close()
    }

    public mutating func addEllipse(in rect: CGRect) {
        addArc(center: CGPoint(x: rect.midX, y: rect.midY),
               radius: 1,
               startAngle: 0,
               endAngle: .pi * 2)
        // Replace with actual ellipse: scale by rect size
        // For now, approximate with many-segment arc
        commands.removeLast(commands.count)
        let cx = rect.midX
        let cy = rect.midY
        let rx = rect.width / 2
        let ry = rect.height / 2
        let segments = 32
        move(to: CGPoint(x: cx + rx, y: cy))
        for i in 1...segments {
            let angle = CGFloat(i) * (.pi * 2) / CGFloat(segments)
            line(to: CGPoint(x: cx + rx * cos(angle), y: cy + ry * sin(angle)))
        }
        close()
    }

    public mutating func addPolygon(_ points: [CGPoint]) {
        guard let first = points.first else { return }
        move(to: first)
        for point in points.dropFirst() {
            line(to: point)
        }
        close()
    }

    public mutating func close() {
        commands.append(.close)
        currentPoint = startPoint
    }

    public func build(fill: SIMD4<Float>? = nil, stroke: VVStrokeStyle? = nil, transform: VVTransform2D = .identity) -> VVPathPrimitive {
        let points = tessellate()
        guard !points.isEmpty else {
            return VVPathPrimitive(vertices: [], fill: fill, stroke: stroke, bounds: .zero, transform: transform)
        }

        var vertices: [VVPathVertex] = []
        var minX = CGFloat.greatestFiniteMagnitude, minY = CGFloat.greatestFiniteMagnitude
        var maxX = -CGFloat.greatestFiniteMagnitude, maxY = -CGFloat.greatestFiniteMagnitude

        for point in points {
            minX = min(minX, point.x)
            minY = min(minY, point.y)
            maxX = max(maxX, point.x)
            maxY = max(maxY, point.y)
        }

        let bounds = CGRect(x: minX, y: minY, width: maxX - minX, height: maxY - minY)

        // Triangulate: simple ear-clipping for convex-ish shapes, fan for fill
        if fill != nil && points.count >= 3 {
            let center = CGPoint(
                x: points.reduce(0) { $0 + $1.x } / CGFloat(points.count),
                y: points.reduce(0) { $0 + $1.y } / CGFloat(points.count)
            )
            for i in 0..<points.count {
                let next = (i + 1) % points.count
                vertices.append(VVPathVertex(position: center))
                vertices.append(VVPathVertex(position: points[i]))
                vertices.append(VVPathVertex(position: points[next]))
            }
        }

        // Stroke: expand each segment into a quad
        if let stroke = stroke, stroke.width > 0 {
            let half = stroke.width / 2
            for i in 0..<points.count {
                let next = (i + 1) % points.count
                let p0 = points[i]
                let p1 = points[next]
                let dx = p1.x - p0.x
                let dy = p1.y - p0.y
                let len = sqrt(dx * dx + dy * dy)
                guard len > 0 else { continue }
                let nx = -dy / len * half
                let ny = dx / len * half
                let a = CGPoint(x: p0.x + nx, y: p0.y + ny)
                let b = CGPoint(x: p0.x - nx, y: p0.y - ny)
                let c = CGPoint(x: p1.x - nx, y: p1.y - ny)
                let d = CGPoint(x: p1.x + nx, y: p1.y + ny)
                vertices.append(VVPathVertex(position: a))
                vertices.append(VVPathVertex(position: b))
                vertices.append(VVPathVertex(position: c))
                vertices.append(VVPathVertex(position: a))
                vertices.append(VVPathVertex(position: c))
                vertices.append(VVPathVertex(position: d))
            }
        }

        return VVPathPrimitive(vertices: vertices, fill: fill, stroke: stroke, bounds: bounds, transform: transform)
    }

    private func tessellate() -> [CGPoint] {
        var points: [CGPoint] = []
        for command in commands {
            switch command {
            case .moveTo(let pt):
                points.append(pt)
            case .lineTo(let pt):
                points.append(pt)
            case .quadCurveTo(let to, let control):
                let from = points.last ?? .zero
                let segments = 8
                for i in 1...segments {
                    let t = CGFloat(i) / CGFloat(segments)
                    let omt = 1 - t
                    let x = omt * omt * from.x + 2 * omt * t * control.x + t * t * to.x
                    let y = omt * omt * from.y + 2 * omt * t * control.y + t * t * to.y
                    points.append(CGPoint(x: x, y: y))
                }
            case .cubicCurveTo(let to, let c1, let c2):
                let from = points.last ?? .zero
                let segments = 12
                for i in 1...segments {
                    let t = CGFloat(i) / CGFloat(segments)
                    let omt = 1 - t
                    let x = omt * omt * omt * from.x + 3 * omt * omt * t * c1.x + 3 * omt * t * t * c2.x + t * t * t * to.x
                    let y = omt * omt * omt * from.y + 3 * omt * omt * t * c1.y + 3 * omt * t * t * c2.y + t * t * t * to.y
                    points.append(CGPoint(x: x, y: y))
                }
            case .close:
                break
            }
        }
        return points
    }
}
