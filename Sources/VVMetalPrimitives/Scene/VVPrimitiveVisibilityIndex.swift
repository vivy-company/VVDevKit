import CoreGraphics

public func vvTextGlyphBounds(for glyphs: [VVTextGlyph]) -> CGRect? {
    guard let first = glyphs.first else { return nil }

    var minX = first.position.x
    var minY = first.position.y
    var maxX = first.position.x + first.size.width
    var maxY = first.position.y + first.size.height

    for glyph in glyphs.dropFirst() {
        minX = min(minX, glyph.position.x)
        minY = min(minY, glyph.position.y)
        maxX = max(maxX, glyph.position.x + glyph.size.width)
        maxY = max(maxY, glyph.position.y + glyph.size.height)
    }

    return CGRect(x: minX, y: minY, width: max(1, maxX - minX), height: max(1, maxY - minY))
}

public func vvPrimitiveVisibilityBounds(_ primitive: VVPrimitive) -> CGRect? {
    if let clipRect = primitive.clipRect, !clipRect.isNull, !clipRect.isEmpty {
        return clipRect
    }

    switch primitive.kind {
    case .textRun(let run):
        let baseBounds = run.lineBounds ?? run.runBounds ?? vvTextGlyphBounds(for: run.glyphs)
        return baseBounds.map { vvTransform(rect: $0, by: primitive.transform) }
    case .quad(let quad):
        return vvTransform(rect: quad.frame, by: primitive.transform)
    case .gradientQuad(let quad):
        return vvTransform(rect: quad.frame, by: primitive.transform)
    case .line(let line):
        let minX = min(line.start.x, line.end.x)
        let minY = min(line.start.y, line.end.y)
        return vvTransform(
            rect: CGRect(
                x: minX - line.thickness * 0.5,
                y: minY - line.thickness * 0.5,
                width: abs(line.end.x - line.start.x) + line.thickness,
                height: abs(line.end.y - line.start.y) + line.thickness
            ),
            by: primitive.transform
        )
    case .underline(let underline):
        return vvTransform(
            rect: CGRect(
                x: underline.origin.x,
                y: underline.origin.y,
                width: underline.width,
                height: max(underline.thickness, 1)
            ),
            by: primitive.transform
        )
    case .bullet(let bullet):
        return vvTransform(
            rect: CGRect(x: bullet.position.x, y: bullet.position.y, width: bullet.size, height: bullet.size),
            by: primitive.transform
        )
    case .image(let image):
        return vvTransform(rect: image.frame, by: primitive.transform)
    case .blockQuoteBorder(let border):
        return vvTransform(rect: border.frame, by: primitive.transform)
    case .tableLine(let line):
        let minX = min(line.start.x, line.end.x)
        let minY = min(line.start.y, line.end.y)
        return vvTransform(
            rect: CGRect(
                x: minX - line.lineWidth * 0.5,
                y: minY - line.lineWidth * 0.5,
                width: abs(line.end.x - line.start.x) + line.lineWidth,
                height: abs(line.end.y - line.start.y) + line.lineWidth
            ),
            by: primitive.transform
        )
    case .pieSlice(let slice):
        return vvTransform(
            rect: CGRect(
                x: slice.center.x - slice.radius,
                y: slice.center.y - slice.radius,
                width: slice.radius * 2,
                height: slice.radius * 2
            ),
            by: primitive.transform
        )
    case .path(let path):
        let pathBounds = vvTransform(rect: path.bounds, by: path.transform)
        return vvTransform(rect: pathBounds, by: primitive.transform)
    }
}

public struct VVPrimitiveVisibilityIndex {
    private let bucketHeight: CGFloat
    private let buckets: [Int: [Int]]
    private let alwaysVisiblePositions: [Int]

    public init(orderedPrimitives: [VVPrimitive], bucketHeight: CGFloat = 320) {
        self.bucketHeight = max(64, bucketHeight)

        var builtBuckets: [Int: [Int]] = [:]
        var alwaysVisible: [Int] = []

        for position in orderedPrimitives.indices {
            guard let bounds = vvPrimitiveVisibilityBounds(orderedPrimitives[position]) else {
                alwaysVisible.append(position)
                continue
            }

            let startBucket = bucketIndex(for: bounds.minY, bucketHeight: self.bucketHeight)
            let endBucket = bucketIndex(for: max(bounds.minY, bounds.maxY - 0.001), bucketHeight: self.bucketHeight)
            for bucket in startBucket...endBucket {
                builtBuckets[bucket, default: []].append(position)
            }
        }

        self.buckets = builtBuckets
        self.alwaysVisiblePositions = alwaysVisible
    }

    public init(scene: VVScene, orderedPrimitiveIndices: [Int], bucketHeight: CGFloat = 320) {
        self.bucketHeight = max(64, bucketHeight)

        var builtBuckets: [Int: [Int]] = [:]
        var alwaysVisible: [Int] = []
        let primitives = scene.primitives

        for position in orderedPrimitiveIndices.indices {
            let primitiveIndex = orderedPrimitiveIndices[position]
            guard primitiveIndex >= primitives.startIndex && primitiveIndex < primitives.endIndex else { continue }
            guard let bounds = vvPrimitiveVisibilityBounds(primitives[primitiveIndex]) else {
                alwaysVisible.append(position)
                continue
            }

            let startBucket = bucketIndex(for: bounds.minY, bucketHeight: self.bucketHeight)
            let endBucket = bucketIndex(for: max(bounds.minY, bounds.maxY - 0.001), bucketHeight: self.bucketHeight)
            for bucket in startBucket...endBucket {
                builtBuckets[bucket, default: []].append(position)
            }
        }

        self.buckets = builtBuckets
        self.alwaysVisiblePositions = alwaysVisible
    }

    public func visiblePositions(in rect: CGRect) -> [Int] {
        guard !rect.isNull, !rect.isEmpty else { return [] }
        guard let bucketRange = bucketRange(for: rect) else { return [] }
        return visiblePositions(inBucketRange: bucketRange)
    }

    public func bucketRange(for rect: CGRect) -> ClosedRange<Int>? {
        guard !rect.isNull, !rect.isEmpty else { return nil }
        let startBucket = bucketIndex(for: rect.minY, bucketHeight: bucketHeight)
        let endBucket = bucketIndex(for: rect.maxY, bucketHeight: bucketHeight)
        guard startBucket <= endBucket else { return nil }
        return startBucket...endBucket
    }

    public func visiblePositions(inBucketRange bucketRange: ClosedRange<Int>) -> [Int] {
        var positions = alwaysVisiblePositions
        for bucket in bucketRange {
            guard let bucketPositions = buckets[bucket], !bucketPositions.isEmpty else { continue }
            positions = mergeSortedUniquePositions(positions, bucketPositions)
        }
        return positions
    }

    public func visiblePrimitives(in rect: CGRect, from orderedPrimitives: [VVPrimitive]) -> [VVPrimitive] {
        let positions = visiblePositions(in: rect)
        guard !positions.isEmpty else { return [] }

        var visible: [VVPrimitive] = []
        visible.reserveCapacity(positions.count)
        for position in positions where position >= orderedPrimitives.startIndex && position < orderedPrimitives.endIndex {
            visible.append(orderedPrimitives[position])
        }
        return visible
    }

    public func visiblePrimitiveIndices(in rect: CGRect, from orderedPrimitiveIndices: [Int]) -> [Int] {
        let positions = visiblePositions(in: rect)
        guard !positions.isEmpty else { return [] }

        var visible: [Int] = []
        visible.reserveCapacity(positions.count)
        for position in positions where position >= orderedPrimitiveIndices.startIndex && position < orderedPrimitiveIndices.endIndex {
            visible.append(orderedPrimitiveIndices[position])
        }
        return visible
    }

    public func visiblePrimitiveIndices(inBucketRange bucketRange: ClosedRange<Int>, from orderedPrimitiveIndices: [Int]) -> [Int] {
        let positions = visiblePositions(inBucketRange: bucketRange)
        guard !positions.isEmpty else { return [] }

        var visible: [Int] = []
        visible.reserveCapacity(positions.count)
        for position in positions where position >= orderedPrimitiveIndices.startIndex && position < orderedPrimitiveIndices.endIndex {
            visible.append(orderedPrimitiveIndices[position])
        }
        return visible
    }
}

private func bucketIndex(for y: CGFloat, bucketHeight: CGFloat) -> Int {
    Int(floor(y / bucketHeight))
}

private func mergeSortedUniquePositions(_ lhs: [Int], _ rhs: [Int]) -> [Int] {
    guard !lhs.isEmpty else { return rhs }
    guard !rhs.isEmpty else { return lhs }

    var merged: [Int] = []
    merged.reserveCapacity(lhs.count + rhs.count)

    var lhsIndex = 0
    var rhsIndex = 0
    var lastValue: Int?

    while lhsIndex < lhs.count || rhsIndex < rhs.count {
        let nextValue: Int
        if rhsIndex >= rhs.count {
            nextValue = lhs[lhsIndex]
            lhsIndex += 1
        } else if lhsIndex >= lhs.count {
            nextValue = rhs[rhsIndex]
            rhsIndex += 1
        } else {
            let lhsValue = lhs[lhsIndex]
            let rhsValue = rhs[rhsIndex]
            if lhsValue <= rhsValue {
                nextValue = lhsValue
                lhsIndex += 1
                if lhsValue == rhsValue {
                    rhsIndex += 1
                }
            } else {
                nextValue = rhsValue
                rhsIndex += 1
            }
        }

        if lastValue != nextValue {
            merged.append(nextValue)
            lastValue = nextValue
        }
    }

    return merged
}

private func vvTransform(rect: CGRect, by transform: VVTransform2D?) -> CGRect {
    guard let transform, !transform.isIdentity else { return rect }
    let corners = [
        rect.origin,
        CGPoint(x: rect.maxX, y: rect.minY),
        CGPoint(x: rect.maxX, y: rect.maxY),
        CGPoint(x: rect.minX, y: rect.maxY)
    ].map { transform.apply(to: $0) }
    let xs = corners.map(\.x)
    let ys = corners.map(\.y)
    return CGRect(
        x: xs.min() ?? rect.minX,
        y: ys.min() ?? rect.minY,
        width: (xs.max() ?? rect.maxX) - (xs.min() ?? rect.minX),
        height: (ys.max() ?? rect.maxY) - (ys.min() ?? rect.minY)
    )
}
