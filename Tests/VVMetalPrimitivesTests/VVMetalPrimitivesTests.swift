import XCTest
@testable import VVMetalPrimitives

final class VVCornerRadiiTests: XCTestCase {
    func testUniformInit() {
        let radii = VVCornerRadii(8)
        XCTAssertEqual(radii.topLeft, 8)
        XCTAssertEqual(radii.topRight, 8)
        XCTAssertEqual(radii.bottomLeft, 8)
        XCTAssertEqual(radii.bottomRight, 8)
        XCTAssertTrue(radii.isUniform)
    }

    func testPerCornerInit() {
        let radii = VVCornerRadii(topLeft: 4, topRight: 8, bottomLeft: 12, bottomRight: 16)
        XCTAssertEqual(radii.topLeft, 4)
        XCTAssertEqual(radii.topRight, 8)
        XCTAssertEqual(radii.bottomLeft, 12)
        XCTAssertEqual(radii.bottomRight, 16)
        XCTAssertFalse(radii.isUniform)
    }

    func testZero() {
        let radii = VVCornerRadii.zero
        XCTAssertTrue(radii.isZero)
        XCTAssertTrue(radii.isUniform)
        XCTAssertEqual(radii.maxRadius, 0)
    }

    func testMaxRadius() {
        let radii = VVCornerRadii(topLeft: 2, topRight: 10, bottomLeft: 5, bottomRight: 7)
        XCTAssertEqual(radii.maxRadius, 10)
    }

    func testEquality() {
        let a = VVCornerRadii(8)
        let b = VVCornerRadii(topLeft: 8, topRight: 8, bottomLeft: 8, bottomRight: 8)
        XCTAssertEqual(a, b)
    }
}

final class VVEdgeWidthsTests: XCTestCase {
    func testUniformInit() {
        let widths = VVEdgeWidths(2)
        XCTAssertEqual(widths.top, 2)
        XCTAssertEqual(widths.right, 2)
        XCTAssertEqual(widths.bottom, 2)
        XCTAssertEqual(widths.left, 2)
    }

    func testPerEdgeInit() {
        let widths = VVEdgeWidths(top: 1, right: 2, bottom: 3, left: 4)
        XCTAssertEqual(widths.top, 1)
        XCTAssertEqual(widths.right, 2)
        XCTAssertEqual(widths.bottom, 3)
        XCTAssertEqual(widths.left, 4)
    }

    func testZero() {
        XCTAssertTrue(VVEdgeWidths.zero.isZero)
        XCTAssertTrue(VVEdgeWidths(0).isZero)
    }
}

final class VVTransform2DTests: XCTestCase {
    func testIdentity() {
        let t = VVTransform2D.identity
        XCTAssertTrue(t.isIdentity)
        let point = CGPoint(x: 10, y: 20)
        let result = t.apply(to: point)
        XCTAssertEqual(result.x, 10, accuracy: 0.001)
        XCTAssertEqual(result.y, 20, accuracy: 0.001)
    }

    func testTranslation() {
        let t = VVTransform2D.identity.translated(by: CGPoint(x: 5, y: -3))
        XCTAssertFalse(t.isIdentity)
        let result = t.apply(to: CGPoint(x: 10, y: 10))
        XCTAssertEqual(result.x, 15, accuracy: 0.001)
        XCTAssertEqual(result.y, 7, accuracy: 0.001)
    }

    func testScale() {
        let t = VVTransform2D.identity.scaled(by: 2)
        let result = t.apply(to: CGPoint(x: 5, y: 3))
        XCTAssertEqual(result.x, 10, accuracy: 0.001)
        XCTAssertEqual(result.y, 6, accuracy: 0.001)
    }

    func testNonUniformScale() {
        let t = VVTransform2D.identity.scaled(x: 3, y: 0.5)
        let result = t.apply(to: CGPoint(x: 4, y: 10))
        XCTAssertEqual(result.x, 12, accuracy: 0.001)
        XCTAssertEqual(result.y, 5, accuracy: 0.001)
    }

    func testRotation90Degrees() {
        let t = VVTransform2D.identity.rotated(by: .pi / 2)
        let result = t.apply(to: CGPoint(x: 1, y: 0))
        XCTAssertEqual(result.x, 0, accuracy: 0.001)
        XCTAssertEqual(result.y, 1, accuracy: 0.001)
    }

    func testComposition() {
        let translate = VVTransform2D.identity.translated(by: CGPoint(x: 10, y: 0))
        let scale = VVTransform2D.identity.scaled(by: 2)
        let combined = scale.composed(with: translate)
        let result = combined.apply(to: CGPoint(x: 1, y: 1))
        // Scale first (2, 2), then translate (+10, 0) → (12, 2)
        XCTAssertEqual(result.x, 12, accuracy: 0.001)
        XCTAssertEqual(result.y, 2, accuracy: 0.001)
    }
}

final class VVBorderTests: XCTestCase {
    func testUniformBorder() {
        let border = VVBorder(width: 2, color: SIMD4(1, 0, 0, 1))
        XCTAssertEqual(border.widths.top, 2)
        XCTAssertEqual(border.widths.right, 2)
        XCTAssertEqual(border.widths.bottom, 2)
        XCTAssertEqual(border.widths.left, 2)
    }

    func testDashedBorder() {
        let border = VVBorder(width: 1, color: SIMD4(1, 1, 1, 1), style: .dashed(dashLength: 4, gapLength: 2))
        if case .dashed(let dl, let gl) = border.style {
            XCTAssertEqual(dl, 4)
            XCTAssertEqual(gl, 2)
        } else {
            XCTFail("Expected dashed style")
        }
    }

    func testPerSideBorder() {
        let widths = VVEdgeWidths(top: 1, right: 2, bottom: 3, left: 4)
        let border = VVBorder(widths: widths, color: SIMD4(0, 0, 1, 1))
        XCTAssertEqual(border.widths.top, 1)
        XCTAssertEqual(border.widths.left, 4)
    }
}

final class VVQuadPrimitiveTests: XCTestCase {
    func testBackwardCompatInit() {
        let quad = VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 100, height: 50), color: SIMD4(1, 0, 0, 1), cornerRadius: 8)
        XCTAssertEqual(quad.cornerRadius, 8)
        XCTAssertTrue(quad.cornerRadii.isUniform)
        XCTAssertNil(quad.border)
        XCTAssertEqual(quad.opacity, 1)
    }

    func testNewInit() {
        let radii = VVCornerRadii(topLeft: 4, topRight: 8, bottomLeft: 0, bottomRight: 12)
        let border = VVBorder(width: 1, color: SIMD4(1, 1, 1, 1))
        let quad = VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 100, height: 50), color: SIMD4(1, 0, 0, 1), cornerRadii: radii, border: border, opacity: 0.8)
        XCTAssertEqual(quad.cornerRadii.topLeft, 4)
        XCTAssertEqual(quad.cornerRadii.topRight, 8)
        XCTAssertNotNil(quad.border)
        XCTAssertEqual(quad.opacity, 0.8)
    }

    func testCornerRadiusComputedProperty() {
        var quad = VVQuadPrimitive(frame: .zero, color: SIMD4(0, 0, 0, 1), cornerRadii: VVCornerRadii(topLeft: 4, topRight: 8, bottomLeft: 12, bottomRight: 16))
        XCTAssertEqual(quad.cornerRadius, 4) // returns topLeft
        quad.cornerRadius = 10
        XCTAssertTrue(quad.cornerRadii.isUniform)
        XCTAssertEqual(quad.cornerRadii.bottomRight, 10)
    }
}

final class VVGradientQuadTests: XCTestCase {
    func testBackwardCompatInit() {
        let grad = VVGradientQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 100, height: 50), startColor: SIMD4(1, 0, 0, 1), endColor: SIMD4(0, 0, 1, 1), direction: .vertical, cornerRadius: 6, steps: 16)
        XCTAssertEqual(grad.cornerRadius, 6)
        XCTAssertNil(grad.angle)
        XCTAssertEqual(grad.steps, 16)
    }

    func testAngleInit() {
        let grad = VVGradientQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 100, height: 50), startColor: SIMD4(1, 0, 0, 1), endColor: SIMD4(0, 0, 1, 1), angle: .pi / 4, cornerRadii: VVCornerRadii(4))
        XCTAssertEqual(grad.angle, .pi / 4)
        XCTAssertEqual(grad.cornerRadii.topLeft, 4)
    }
}

final class VVShadowQuadTests: XCTestCase {
    func testBackwardCompatInit() {
        let shadow = VVShadowQuadPrimitive(frame: CGRect(x: 10, y: 10, width: 80, height: 40), color: SIMD4(0, 0, 0, 0.3), cornerRadius: 4, spread: 8, steps: 4)
        XCTAssertEqual(shadow.cornerRadius, 4)
        XCTAssertEqual(shadow.blurRadius, 0)
        XCTAssertEqual(shadow.offset, .zero)
    }

    func testNewInit() {
        let shadow = VVShadowQuadPrimitive(frame: CGRect(x: 10, y: 10, width: 80, height: 40), color: SIMD4(0, 0, 0, 0.5), cornerRadii: VVCornerRadii(topLeft: 8, topRight: 4, bottomLeft: 0, bottomRight: 0), spread: 10, blurRadius: 5, offset: CGPoint(x: 2, y: 3), steps: 8)
        XCTAssertEqual(shadow.blurRadius, 5)
        XCTAssertEqual(shadow.offset.x, 2)
        XCTAssertEqual(shadow.offset.y, 3)
        XCTAssertEqual(shadow.cornerRadii.topLeft, 8)
    }

    func testExpandedQuads() {
        let shadow = VVShadowQuadPrimitive(frame: CGRect(x: 10, y: 10, width: 80, height: 40), color: SIMD4(0, 0, 0, 0.5), spread: 10, steps: 4)
        let quads = shadow.expandedQuads()
        XCTAssertEqual(quads.count, 4)
        // Each successive quad should be larger (more spread)
        for i in 1..<quads.count {
            XCTAssertGreaterThan(quads[i].frame.width, quads[i-1].frame.width)
        }
    }

    func testExpandedQuadsWithOffset() {
        let shadow = VVShadowQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 100, height: 50), color: SIMD4(0, 0, 0, 0.5), spread: 5, offset: CGPoint(x: 3, y: 4), steps: 2)
        let quads = shadow.expandedQuads()
        // All quads should be offset by (3, 4)
        for quad in quads {
            XCTAssertEqual(quad.frame.midX, 50 + 3, accuracy: 1)
            XCTAssertEqual(quad.frame.midY, 25 + 4, accuracy: 1)
        }
    }

    func testExpandedQuadsEmptyFrame() {
        let shadow = VVShadowQuadPrimitive(frame: .zero, color: SIMD4(0, 0, 0, 0.5))
        XCTAssertTrue(shadow.expandedQuads().isEmpty)
    }
}

final class VVLinePrimitiveTests: XCTestCase {
    func testSolidLine() {
        let line = VVLinePrimitive(start: .zero, end: CGPoint(x: 100, y: 0), thickness: 2, color: SIMD4(1, 1, 1, 1))
        if case .solid = line.dash {} else {
            XCTFail("Expected solid dash")
        }
    }

    func testDashedLine() {
        let line = VVLinePrimitive(start: .zero, end: CGPoint(x: 100, y: 0), thickness: 1, color: SIMD4(1, 1, 1, 1), dash: .dashed(on: 4, off: 2))
        if case .dashed(let on, let off) = line.dash {
            XCTAssertEqual(on, 4)
            XCTAssertEqual(off, 2)
        } else {
            XCTFail("Expected dashed")
        }
    }

    func testPatternDash() {
        let line = VVLinePrimitive(start: .zero, end: CGPoint(x: 100, y: 0), thickness: 1, color: SIMD4(1, 1, 1, 1), dash: .pattern([4, 2, 1, 2]))
        if case .pattern(let p) = line.dash {
            XCTAssertEqual(p, [4, 2, 1, 2])
        } else {
            XCTFail("Expected pattern")
        }
    }
}

final class VVUnderlinePrimitiveTests: XCTestCase {
    func testStraightUnderline() {
        let underline = VVUnderlinePrimitive(origin: CGPoint(x: 10, y: 100), width: 80, color: SIMD4(1, 0, 0, 1))
        XCTAssertFalse(underline.wavy)
        XCTAssertEqual(underline.thickness, 1) // default
    }

    func testWavyUnderline() {
        let underline = VVUnderlinePrimitive(origin: CGPoint(x: 10, y: 100), width: 80, thickness: 2, color: SIMD4(1, 0, 0, 1), wavy: true)
        XCTAssertTrue(underline.wavy)
        XCTAssertEqual(underline.thickness, 2)
    }
}

final class VVImagePrimitiveTests: XCTestCase {
    func testBackwardCompatInit() {
        let image = VVImagePrimitive(url: "https://example.com/img.png", frame: CGRect(x: 0, y: 0, width: 200, height: 100), cornerRadius: 8)
        XCTAssertEqual(image.cornerRadius, 8)
        XCTAssertEqual(image.opacity, 1)
        XCTAssertFalse(image.grayscale)
    }

    func testNewInit() {
        let image = VVImagePrimitive(url: "test.png", frame: CGRect(x: 0, y: 0, width: 100, height: 100), cornerRadii: VVCornerRadii(topLeft: 10, topRight: 10, bottomLeft: 0, bottomRight: 0), opacity: 0.5, grayscale: true)
        XCTAssertEqual(image.cornerRadii.topLeft, 10)
        XCTAssertEqual(image.cornerRadii.bottomLeft, 0)
        XCTAssertEqual(image.opacity, 0.5)
        XCTAssertTrue(image.grayscale)
    }
}

final class VVPathBuilderTests: XCTestCase {
    func testRectangle() {
        var builder = VVPathBuilder()
        builder.addRect(CGRect(x: 0, y: 0, width: 100, height: 50))
        let path = builder.build(fill: SIMD4(1, 0, 0, 1))
        XCTAssertFalse(path.vertices.isEmpty)
        XCTAssertEqual(path.bounds.width, 100, accuracy: 0.001)
        XCTAssertEqual(path.bounds.height, 50, accuracy: 0.001)
    }

    func testTriangle() {
        var builder = VVPathBuilder()
        builder.addPolygon([
            CGPoint(x: 50, y: 0),
            CGPoint(x: 100, y: 100),
            CGPoint(x: 0, y: 100)
        ])
        let path = builder.build(fill: SIMD4(0, 1, 0, 1))
        // Triangle fan: center + 3 edges = 3 triangles × 3 vertices = 9
        XCTAssertEqual(path.vertices.count, 9)
        XCTAssertEqual(path.bounds.minX, 0, accuracy: 0.001)
        XCTAssertEqual(path.bounds.minY, 0, accuracy: 0.001)
        XCTAssertEqual(path.bounds.maxX, 100, accuracy: 0.001)
        XCTAssertEqual(path.bounds.maxY, 100, accuracy: 0.001)
    }

    func testStrokeOnly() {
        var builder = VVPathBuilder()
        builder.addRect(CGRect(x: 0, y: 0, width: 50, height: 50))
        let stroke = VVStrokeStyle(color: SIMD4(1, 1, 1, 1), width: 2)
        let path = builder.build(stroke: stroke)
        // Stroke quads: 5 points (rect + close), 4 segments × 6 vertices = 24
        XCTAssertFalse(path.vertices.isEmpty)
        XCTAssertNotNil(path.stroke)
        XCTAssertNil(path.fill)
    }

    func testFillAndStroke() {
        var builder = VVPathBuilder()
        builder.addRect(CGRect(x: 10, y: 10, width: 80, height: 60))
        let stroke = VVStrokeStyle(color: SIMD4(1, 1, 1, 1), width: 1)
        let path = builder.build(fill: SIMD4(0, 0, 1, 1), stroke: stroke)
        XCTAssertNotNil(path.fill)
        XCTAssertNotNil(path.stroke)
        // Should have both fill triangles and stroke quads
        XCTAssertGreaterThan(path.vertices.count, 6)
    }

    func testEllipse() {
        var builder = VVPathBuilder()
        builder.addEllipse(in: CGRect(x: 0, y: 0, width: 100, height: 60))
        let path = builder.build(fill: SIMD4(1, 0, 0, 1))
        XCTAssertFalse(path.vertices.isEmpty)
        // Bounds should roughly match the rect
        XCTAssertEqual(path.bounds.width, 100, accuracy: 1)
        XCTAssertEqual(path.bounds.height, 60, accuracy: 1)
    }

    func testRoundedRect() {
        var builder = VVPathBuilder()
        builder.addRoundedRect(CGRect(x: 0, y: 0, width: 100, height: 50), cornerRadii: VVCornerRadii(topLeft: 10, topRight: 5, bottomLeft: 0, bottomRight: 15))
        let path = builder.build(fill: SIMD4(0, 1, 0, 1))
        XCTAssertFalse(path.vertices.isEmpty)
    }

    func testArc() {
        var builder = VVPathBuilder()
        builder.addArc(center: CGPoint(x: 50, y: 50), radius: 40, startAngle: 0, endAngle: .pi)
        let path = builder.build(stroke: VVStrokeStyle(color: SIMD4(1, 1, 1, 1), width: 2))
        XCTAssertFalse(path.vertices.isEmpty)
    }

    func testQuadCurve() {
        var builder = VVPathBuilder()
        builder.move(to: CGPoint(x: 0, y: 50))
        builder.quadCurve(to: CGPoint(x: 100, y: 50), control: CGPoint(x: 50, y: 0))
        let path = builder.build(stroke: VVStrokeStyle(color: SIMD4(1, 0, 0, 1)))
        XCTAssertFalse(path.vertices.isEmpty)
        XCTAssertLessThan(path.bounds.minY, 50)
    }

    func testCubicCurve() {
        var builder = VVPathBuilder()
        builder.move(to: CGPoint(x: 0, y: 50))
        builder.cubicCurve(to: CGPoint(x: 100, y: 50), control1: CGPoint(x: 25, y: 0), control2: CGPoint(x: 75, y: 100))
        let path = builder.build(fill: SIMD4(0, 0, 1, 0.5))
        XCTAssertFalse(path.vertices.isEmpty)
    }

    func testEmptyBuilder() {
        let builder = VVPathBuilder()
        let path = builder.build(fill: SIMD4(1, 0, 0, 1))
        XCTAssertTrue(path.vertices.isEmpty)
        XCTAssertEqual(path.bounds, .zero)
    }

    func testWithTransform() {
        var builder = VVPathBuilder()
        builder.addRect(CGRect(x: 0, y: 0, width: 10, height: 10))
        let transform = VVTransform2D.identity.scaled(by: 2)
        let path = builder.build(fill: SIMD4(1, 0, 0, 1), transform: transform)
        XCTAssertEqual(path.transform.m00, 2)
    }
}

final class VVSceneTests: XCTestCase {
    func testAddPrimitives() {
        var scene = VVScene()
        scene.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 100, height: 50), color: SIMD4(1, 0, 0, 1))))
        scene.add(kind: .line(VVLinePrimitive(start: .zero, end: CGPoint(x: 100, y: 0), thickness: 1, color: SIMD4(1, 1, 1, 1))))
        XCTAssertEqual(scene.primitives.count, 2)
    }

    func testOrderedByZIndex() {
        var scene = VVScene()
        scene.add(kind: .quad(VVQuadPrimitive(frame: .zero, color: SIMD4(1, 0, 0, 1))), zIndex: 10)
        scene.add(kind: .quad(VVQuadPrimitive(frame: .zero, color: SIMD4(0, 1, 0, 1))), zIndex: 0)
        scene.add(kind: .quad(VVQuadPrimitive(frame: .zero, color: SIMD4(0, 0, 1, 1))), zIndex: 5)

        let ordered = scene.orderedPrimitives()
        XCTAssertEqual(ordered[0].zIndex, 0)
        XCTAssertEqual(ordered[1].zIndex, 5)
        XCTAssertEqual(ordered[2].zIndex, 10)
    }

    func testOrderPreservedWithinSameZIndex() {
        var scene = VVScene()
        let red = SIMD4<Float>(1, 0, 0, 1)
        let green = SIMD4<Float>(0, 1, 0, 1)
        scene.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 10, height: 10), color: red)))
        scene.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: 20, y: 0, width: 10, height: 10), color: green)))

        let ordered = scene.orderedPrimitives()
        if case .quad(let first) = ordered[0].kind, case .quad(let second) = ordered[1].kind {
            XCTAssertEqual(first.color, red)
            XCTAssertEqual(second.color, green)
        } else {
            XCTFail("Expected quads")
        }
    }
}

final class VVSceneBuilderTests: XCTestCase {
    func testBasicAdd() {
        var builder = VVSceneBuilder()
        builder.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 100, height: 50), color: SIMD4(1, 0, 0, 1))))
        XCTAssertEqual(builder.scene.primitives.count, 1)
    }

    func testClipping() {
        var builder = VVSceneBuilder()
        let clipRect = CGRect(x: 0, y: 0, width: 50, height: 50)
        builder.withClip(clipRect) { b in
            b.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 100, height: 100), color: SIMD4(1, 0, 0, 1))))
        }
        XCTAssertEqual(builder.scene.primitives[0].clipRect, clipRect)
    }

    func testNestedClipping() {
        var builder = VVSceneBuilder()
        builder.withClip(CGRect(x: 0, y: 0, width: 100, height: 100)) { b in
            b.withClip(CGRect(x: 25, y: 25, width: 100, height: 100)) { b2 in
                b2.add(kind: .quad(VVQuadPrimitive(frame: .zero, color: SIMD4(1, 0, 0, 1))))
            }
        }
        // Intersection of (0,0,100,100) and (25,25,100,100) = (25,25,75,75)
        let clip = builder.scene.primitives[0].clipRect!
        XCTAssertEqual(clip.origin.x, 25)
        XCTAssertEqual(clip.origin.y, 25)
        XCTAssertEqual(clip.size.width, 75)
        XCTAssertEqual(clip.size.height, 75)
    }

    func testOffset() {
        var builder = VVSceneBuilder()
        builder.withOffset(CGPoint(x: 10, y: 20)) { b in
            b.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 50, height: 50), color: SIMD4(1, 0, 0, 1))))
        }
        if case .quad(let quad) = builder.scene.primitives[0].kind {
            XCTAssertEqual(quad.frame.origin.x, 10)
            XCTAssertEqual(quad.frame.origin.y, 20)
        } else {
            XCTFail("Expected quad")
        }
    }

    func testNestedOffset() {
        var builder = VVSceneBuilder()
        builder.withOffset(CGPoint(x: 10, y: 0)) { b in
            b.withOffset(CGPoint(x: 5, y: 15)) { b2 in
                b2.add(kind: .quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 50, height: 50), color: SIMD4(1, 0, 0, 1))))
            }
        }
        if case .quad(let quad) = builder.scene.primitives[0].kind {
            XCTAssertEqual(quad.frame.origin.x, 15)
            XCTAssertEqual(quad.frame.origin.y, 15)
        } else {
            XCTFail("Expected quad")
        }
    }

    func testAddNode() {
        let child = VVNode(
            offset: CGPoint(x: 5, y: 10),
            primitives: [.quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 20, height: 20), color: SIMD4(0, 1, 0, 1)))]
        )
        var builder = VVSceneBuilder()
        builder.add(node: child)
        if case .quad(let quad) = builder.scene.primitives[0].kind {
            XCTAssertEqual(quad.frame.origin.x, 5)
            XCTAssertEqual(quad.frame.origin.y, 10)
        } else {
            XCTFail("Expected quad")
        }
    }
}

final class VVNodeTests: XCTestCase {
    func testFlattenSimple() {
        let node = VVNode(primitives: [
            .quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 100, height: 50), color: SIMD4(1, 0, 0, 1)))
        ])
        let scene = node.flattened()
        XCTAssertEqual(scene.primitives.count, 1)
    }

    func testFlattenWithOffset() {
        let node = VVNode(
            offset: CGPoint(x: 10, y: 20),
            primitives: [.quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 50, height: 50), color: SIMD4(1, 0, 0, 1)))]
        )
        let primitives = node.flattenedPrimitives()
        if case .quad(let quad) = primitives[0].kind {
            XCTAssertEqual(quad.frame.origin.x, 10)
            XCTAssertEqual(quad.frame.origin.y, 20)
        } else {
            XCTFail("Expected quad")
        }
    }

    func testFlattenWithChildren() {
        let child = VVNode(
            offset: CGPoint(x: 5, y: 5),
            primitives: [.quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 20, height: 20), color: SIMD4(0, 1, 0, 1)))]
        )
        let parent = VVNode(
            offset: CGPoint(x: 10, y: 10),
            primitives: [.quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 50, height: 50), color: SIMD4(1, 0, 0, 1)))],
            children: [child]
        )
        let primitives = parent.flattenedPrimitives()
        XCTAssertEqual(primitives.count, 2)
        // Parent quad at (10, 10)
        if case .quad(let parentQuad) = primitives[0].kind {
            XCTAssertEqual(parentQuad.frame.origin.x, 10)
        }
        // Child quad at (10+5, 10+5) = (15, 15)
        if case .quad(let childQuad) = primitives[1].kind {
            XCTAssertEqual(childQuad.frame.origin.x, 15)
            XCTAssertEqual(childQuad.frame.origin.y, 15)
        }
    }

    func testFlattenWithClipping() {
        let node = VVNode(
            clipRect: CGRect(x: 0, y: 0, width: 50, height: 50),
            primitives: [.quad(VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 100, height: 100), color: SIMD4(1, 0, 0, 1)))]
        )
        let primitives = node.flattenedPrimitives()
        XCTAssertNotNil(primitives[0].clipRect)
        XCTAssertEqual(primitives[0].clipRect?.width, 50)
    }

    func testFlattenZIndexAccumulation() {
        let child = VVNode(
            zIndex: 5,
            primitives: [.quad(VVQuadPrimitive(frame: .zero, color: SIMD4(0, 1, 0, 1)))]
        )
        let parent = VVNode(
            zIndex: 10,
            primitives: [],
            children: [child]
        )
        let primitives = parent.flattenedPrimitives()
        XCTAssertEqual(primitives[0].zIndex, 15)
    }

    func testOffsetLine() {
        let kind = VVPrimitiveKind.line(VVLinePrimitive(start: CGPoint(x: 0, y: 0), end: CGPoint(x: 100, y: 0), thickness: 1, color: SIMD4(1, 1, 1, 1)))
        let offset = CGPoint(x: 10, y: 20)
        let result = VVNode.offsetPrimitive(kind, by: offset)
        if case .line(let line) = result {
            XCTAssertEqual(line.start.x, 10)
            XCTAssertEqual(line.start.y, 20)
            XCTAssertEqual(line.end.x, 110)
            XCTAssertEqual(line.end.y, 20)
        } else {
            XCTFail("Expected line")
        }
    }

    func testOffsetUnderline() {
        let kind = VVPrimitiveKind.underline(VVUnderlinePrimitive(origin: CGPoint(x: 5, y: 10), width: 50, color: SIMD4(1, 0, 0, 1), wavy: true))
        let result = VVNode.offsetPrimitive(kind, by: CGPoint(x: 3, y: 7))
        if case .underline(let underline) = result {
            XCTAssertEqual(underline.origin.x, 8)
            XCTAssertEqual(underline.origin.y, 17)
            XCTAssertTrue(underline.wavy) // wavy preserved
        } else {
            XCTFail("Expected underline")
        }
    }

    func testOffsetPath() {
        let vertex = VVPathVertex(position: CGPoint(x: 10, y: 20))
        let kind = VVPrimitiveKind.path(VVPathPrimitive(vertices: [vertex], bounds: CGRect(x: 10, y: 20, width: 30, height: 40)))
        let result = VVNode.offsetPrimitive(kind, by: CGPoint(x: 5, y: 5))
        if case .path(let path) = result {
            XCTAssertEqual(path.vertices[0].position.x, 15)
            XCTAssertEqual(path.vertices[0].position.y, 25)
            XCTAssertEqual(path.bounds.origin.x, 15)
            XCTAssertEqual(path.bounds.origin.y, 25)
        } else {
            XCTFail("Expected path")
        }
    }

    func testOffsetZeroIsNoOp() {
        let kind = VVPrimitiveKind.quad(VVQuadPrimitive(frame: CGRect(x: 10, y: 20, width: 30, height: 40), color: SIMD4(1, 0, 0, 1)))
        let result = VVNode.offsetPrimitive(kind, by: .zero)
        if case .quad(let quad) = result {
            XCTAssertEqual(quad.frame.origin.x, 10)
        } else {
            XCTFail("Expected quad")
        }
    }

    func testOffsetPreservesNewFields() {
        // Verify offset preserves border, opacity, cornerRadii on quad
        let border = VVBorder(width: 2, color: SIMD4(1, 1, 1, 1), style: .dashed(dashLength: 4, gapLength: 2))
        let quad = VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 50, height: 50), color: SIMD4(1, 0, 0, 1), cornerRadii: VVCornerRadii(topLeft: 4, topRight: 8, bottomLeft: 0, bottomRight: 12), border: border, opacity: 0.7)
        let kind = VVPrimitiveKind.quad(quad)
        let result = VVNode.offsetPrimitive(kind, by: CGPoint(x: 10, y: 10))
        if case .quad(let offsetQuad) = result {
            XCTAssertEqual(offsetQuad.frame.origin.x, 10)
            XCTAssertEqual(offsetQuad.cornerRadii.topLeft, 4)
            XCTAssertEqual(offsetQuad.cornerRadii.bottomRight, 12)
            XCTAssertNotNil(offsetQuad.border)
            XCTAssertEqual(offsetQuad.opacity, 0.7)
        } else {
            XCTFail("Expected quad")
        }
    }

    func testOffsetPreservesLineDash() {
        let line = VVLinePrimitive(start: .zero, end: CGPoint(x: 100, y: 0), thickness: 2, color: SIMD4(1, 1, 1, 1), dash: .dashed(on: 5, off: 3))
        let kind = VVPrimitiveKind.line(line)
        let result = VVNode.offsetPrimitive(kind, by: CGPoint(x: 5, y: 5))
        if case .line(let offsetLine) = result {
            if case .dashed(let on, let off) = offsetLine.dash {
                XCTAssertEqual(on, 5)
                XCTAssertEqual(off, 3)
            } else {
                XCTFail("Expected dashed")
            }
        } else {
            XCTFail("Expected line")
        }
    }
}

final class VVTextRunStyleTests: XCTestCase {
    func testDefaults() {
        let style = VVTextRunStyle()
        XCTAssertFalse(style.isStrikethrough)
        XCTAssertFalse(style.isLink)
        XCTAssertFalse(style.isWavyUnderline)
        XCTAssertNil(style.linkURL)
    }

    func testWavyUnderlineStyle() {
        let style = VVTextRunStyle(isWavyUnderline: true, color: SIMD4(1, 0, 0, 1))
        XCTAssertTrue(style.isWavyUnderline)
    }

    func testBackwardCompat() {
        // Old-style usage pattern should still work
        let style = VVTextRunStyle(isStrikethrough: false, isLink: true, linkURL: "https://example.com", color: SIMD4(0, 0.5, 1, 1))
        XCTAssertTrue(style.isLink)
        XCTAssertEqual(style.linkURL, "https://example.com")
        XCTAssertFalse(style.isWavyUnderline)
    }
}

final class VVPrimitiveKindTests: XCTestCase {
    func testAllCases() {
        // Verify all VVPrimitiveKind cases can be constructed
        let cases: [VVPrimitiveKind] = [
            .textRun(VVTextRunPrimitive(glyphs: [], style: VVTextRunStyle())),
            .quad(VVQuadPrimitive(frame: .zero, color: .zero)),
            .gradientQuad(VVGradientQuadPrimitive(frame: .zero, startColor: .zero, endColor: .zero)),
            .line(VVLinePrimitive(start: .zero, end: .zero, thickness: 1, color: .zero)),
            .underline(VVUnderlinePrimitive(origin: .zero, width: 10, color: .zero)),
            .bullet(VVBulletPrimitive(position: .zero, size: 10, color: .zero, type: .disc)),
            .image(VVImagePrimitive(url: "", frame: .zero)),
            .blockQuoteBorder(VVBlockQuoteBorderPrimitive(frame: .zero, color: .zero, borderWidth: 1)),
            .tableLine(VVTableLinePrimitive(start: .zero, end: .zero, color: .zero, lineWidth: 1)),
            .pieSlice(VVPieSlicePrimitive(center: .zero, radius: 10, startAngle: 0, endAngle: .pi, color: .zero)),
            .path(VVPathPrimitive(vertices: []))
        ]
        XCTAssertEqual(cases.count, 11)
    }
}

// MARK: - VVView Tests

final class VTextTests: XCTestCase {
    func testBasicText() {
        let view = VText("Hello")
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertGreaterThan(layout.size.width, 0)
        XCTAssertGreaterThan(layout.size.height, 0)
        // Should have a textRun primitive
        XCTAssertEqual(layout.node.primitives.count, 1)
        if case .textRun(let run) = layout.node.primitives[0] {
            XCTAssertFalse(run.glyphs.isEmpty)
        } else {
            XCTFail("Expected textRun")
        }
    }

    func testEmptyText() {
        let view = VText("")
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 0)
        XCTAssertEqual(layout.size.height, 0)
    }

    func testFontSpecs() {
        let body = VText("Test", font: .body)
        let title = VText("Test", font: .title)
        let bodyLayout = body.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        let titleLayout = title.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertGreaterThan(titleLayout.size.height, bodyLayout.size.height)
    }

    func testCustomColor() {
        let red = SIMD4<Float>(1, 0, 0, 1)
        let view = VText("Hi", color: red)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        if case .textRun(let run) = layout.node.primitives[0] {
            XCTAssertEqual(run.glyphs[0].color, red)
        } else {
            XCTFail("Expected textRun")
        }
    }

    func testDefaultColorFromEnv() {
        let envColor = SIMD4<Float>(0.5, 0.5, 0.5, 1)
        let env = VVLayoutEnvironment(defaultTextColor: envColor)
        let view = VText("Hi")
        let layout = view.layout(in: env, constraint: VVLayoutConstraint(maxWidth: 400))
        if case .textRun(let run) = layout.node.primitives[0] {
            XCTAssertEqual(run.glyphs[0].color, envColor)
        } else {
            XCTFail("Expected textRun")
        }
    }
}

final class VRectTests: XCTestCase {
    func testFillsWidth() {
        let view = VRect(color: SIMD4(1, 0, 0, 1))
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 200))
        XCTAssertEqual(layout.size.width, 200)
        XCTAssertEqual(layout.size.height, 0)
    }

    func testWithFrame() {
        let view = VRect(color: SIMD4(1, 0, 0, 1)).frame(width: 100, height: 50)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 100)
        XCTAssertEqual(layout.size.height, 50)
    }
}

final class VSpacerTests: XCTestCase {
    func testFixedSize() {
        let spacer = VSpacer(width: 10, height: 20)
        let layout = spacer.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 10)
        XCTAssertEqual(layout.size.height, 20)
    }

    func testDefaultsToZero() {
        let spacer = VSpacer()
        let layout = spacer.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 0)
        XCTAssertEqual(layout.size.height, 0)
    }
}

final class VDividerTests: XCTestCase {
    func testDivider() {
        let divider = VDivider()
        let layout = divider.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 300))
        XCTAssertEqual(layout.size.width, 300)
        XCTAssertEqual(layout.size.height, 1)
        if case .line(let line) = layout.node.primitives[0] {
            XCTAssertEqual(line.start.x, 0)
            XCTAssertEqual(line.end.x, 300)
        } else {
            XCTFail("Expected line")
        }
    }

    func testDividerWithInset() {
        let divider = VDivider(inset: 16)
        let layout = divider.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 300))
        if case .line(let line) = layout.node.primitives[0] {
            XCTAssertEqual(line.start.x, 16)
            XCTAssertEqual(line.end.x, 300 - 16)
        } else {
            XCTFail("Expected line")
        }
    }
}

final class VStackTests: XCTestCase {
    func testVerticalLayout() {
        let stack = VVStack(spacing: 8) {
            VSpacer(height: 20)
            VSpacer(height: 30)
            VSpacer(height: 10)
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.height, 20 + 8 + 30 + 8 + 10)
    }

    func testCenterAlignment() {
        let stack = VVStack(alignment: .center) {
            VSpacer(width: 100, height: 10)
            VSpacer(width: 50, height: 10)
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        // Second child should be offset to center
        let secondChildOffset = layout.node.children[1].offset.x
        XCTAssertGreaterThan(secondChildOffset, 0)
    }

    func testTrailingAlignment() {
        let stack = VVStack(alignment: .trailing) {
            VSpacer(width: 100, height: 10)
            VSpacer(width: 50, height: 10)
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        let secondChildOffset = layout.node.children[1].offset.x
        XCTAssertGreaterThan(secondChildOffset, 0)
    }

    func testEmpty() {
        let stack = VVStack {}
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.height, 0)
    }

    func testNestedStacks() {
        let stack = VVStack(spacing: 4) {
            VVStack(spacing: 2) {
                VSpacer(height: 10)
                VSpacer(height: 10)
            }
            VSpacer(height: 5)
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        let innerHeight: CGFloat = 10 + 2 + 10
        let totalHeight = innerHeight + 4 + 5
        XCTAssertEqual(layout.size.height, totalHeight)
    }
}

final class HStackTests: XCTestCase {
    func testHorizontalLayout() {
        let stack = VVHStack(spacing: 10) {
            VSpacer(width: 50, height: 20)
            VSpacer(width: 30, height: 40)
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.height, 40)
        XCTAssertEqual(layout.size.width, 50 + 10 + 30)
    }

    func testVerticalCenterAlignment() {
        let stack = VVHStack(alignment: .center) {
            VSpacer(width: 50, height: 20)
            VSpacer(width: 50, height: 40)
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        let firstChildY = layout.node.children[0].offset.y
        XCTAssertEqual(firstChildY, 10) // (40 - 20) / 2
    }

    func testBottomAlignment() {
        let stack = VVHStack(alignment: .bottom) {
            VSpacer(width: 50, height: 20)
            VSpacer(width: 50, height: 40)
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        let firstChildY = layout.node.children[0].offset.y
        XCTAssertEqual(firstChildY, 20) // 40 - 20
    }
}

final class ZStackTests: XCTestCase {
    func testOverlay() {
        let stack = VVZStack {
            VSpacer(width: 100, height: 50)
            VSpacer(width: 80, height: 30)
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 100)
        XCTAssertEqual(layout.size.height, 50)
    }

    func testZIndexAssignment() {
        let stack = VVZStack {
            VSpacer(width: 10, height: 10)
            VSpacer(width: 10, height: 10)
            VSpacer(width: 10, height: 10)
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.node.children[0].zIndex, 0)
        XCTAssertEqual(layout.node.children[1].zIndex, 1)
        XCTAssertEqual(layout.node.children[2].zIndex, 2)
    }
}

final class VVModifierTests: XCTestCase {
    func testPadding() {
        let view = VSpacer(width: 50, height: 30).padding(10)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 70) // 50 + 10 + 10
        XCTAssertEqual(layout.size.height, 50) // 30 + 10 + 10
    }

    func testAsymmetricPadding() {
        let view = VSpacer(width: 50, height: 30).padding(top: 5, right: 10, bottom: 15, left: 20)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 80) // 50 + 10 + 20
        XCTAssertEqual(layout.size.height, 50) // 30 + 5 + 15
    }

    func testBackground() {
        let bgColor = SIMD4<Float>(0.2, 0.2, 0.2, 1)
        let view = VSpacer(width: 100, height: 50).background(color: bgColor, cornerRadius: 8)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 100)
        XCTAssertEqual(layout.size.height, 50)
        // Background node should be first child
        let bgNode = layout.node.children[0]
        if case .quad(let quad) = bgNode.primitives[0] {
            XCTAssertEqual(quad.color, bgColor)
            XCTAssertEqual(quad.cornerRadius, 8)
            XCTAssertEqual(quad.frame.width, 100)
            XCTAssertEqual(quad.frame.height, 50)
        } else {
            XCTFail("Expected background quad")
        }
    }

    func testBorder() {
        let borderColor = SIMD4<Float>(1, 0, 0, 1)
        let view = VSpacer(width: 100, height: 50).border(color: borderColor, width: 2)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        // Should contain a border quad with transparent fill
        let scene = layout.node.flattened()
        let quads = scene.primitives.filter {
            if case .quad = $0.kind { return true }
            return false
        }
        XCTAssertFalse(quads.isEmpty)
    }

    func testFrame() {
        let view = VSpacer(width: 10, height: 10).frame(width: 200, height: 100)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 200)
        XCTAssertEqual(layout.size.height, 100)
    }

    func testOpacity() {
        let view = VDivider(color: SIMD4(1, 1, 1, 1)).opacity(0.5)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        let scene = layout.node.flattened()
        for prim in scene.primitives {
            if case .line(let line) = prim.kind {
                XCTAssertEqual(line.color.w, 0.5, accuracy: 0.01)
            }
        }
    }

    func testClipRect() {
        let clip = CGRect(x: 10, y: 10, width: 80, height: 40)
        let view = VSpacer(width: 100, height: 50).clipRect(clip)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.node.clipRect, clip)
    }

    func testZIndex() {
        let view = VSpacer(width: 10, height: 10).zIndex(5)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.node.zIndex, 5)
    }

    func testModifierChaining() {
        let view = VText("Hello")
            .padding(16)
            .background(color: SIMD4(0.15, 0.15, 0.18, 1), cornerRadius: 8)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertGreaterThan(layout.size.width, 32) // at least padding
        XCTAssertGreaterThan(layout.size.height, 32)
    }

    func testShadow() {
        let view = VSpacer(width: 100, height: 50).shadow(spread: 10)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        let scene = layout.node.flattened()
        // Should have shadow quads
        let quads = scene.primitives.filter {
            if case .quad = $0.kind { return true }
            return false
        }
        XCTAssertFalse(quads.isEmpty)
    }
}

final class VVViewBuilderTests: XCTestCase {
    func testIfElse() {
        let condition = true
        let stack = VVStack {
            if condition {
                VSpacer(height: 10)
            } else {
                VSpacer(height: 20)
            }
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.height, 10)
    }

    func testIfElseFalse() {
        let condition = false
        let stack = VVStack {
            if condition {
                VSpacer(height: 10)
            } else {
                VSpacer(height: 20)
            }
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.height, 20)
    }

    func testForIn() {
        let items = [10, 20, 30]
        let stack = VVStack {
            for height in items {
                VSpacer(height: CGFloat(height))
            }
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.height, 60)
    }

    func testOptional() {
        let value: String? = "Hello"
        let stack = VVStack {
            if let text = value {
                VText(text)
            }
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertGreaterThan(layout.size.height, 0)
    }

    func testOptionalNil() {
        let value: String? = nil
        let stack = VVStack {
            if let _ = value {
                VText("visible")
            }
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.height, 0)
    }
}

final class VVViewIntegrationTests: XCTestCase {
    func testRenderScene() {
        let view = VVStack(spacing: 8) {
            VText("Title", font: .title)
            VDivider()
            VText("Body text", font: .body)
        }
        .padding(16)
        .background(color: SIMD4(0.15, 0.15, 0.18, 1), cornerRadius: 8)

        let scene = view.renderScene(width: 400)
        XCTAssertFalse(scene.primitives.isEmpty)
    }

    func testRenderNode() {
        let view = VText("Hello")
        let node = view.renderNode(width: 300)
        XCTAssertFalse(node.primitives.isEmpty)
    }

    func testRenderLayout() {
        let view = VVStack {
            VText("Line 1")
            VText("Line 2")
        }
        let layout = view.renderLayout(width: 400)
        XCTAssertGreaterThan(layout.size.height, 0)
        XCTAssertGreaterThan(layout.size.width, 0)
    }

    func testComplexScene() {
        let card = VVStack(spacing: 8) {
            VText("Hello World", font: .title)
            VDivider()
            VVHStack(spacing: 12) {
                VText("Left", font: .body)
                VText("Right", font: .body)
            }
            VSpacer(height: 4)
            VText("Footer", font: .caption, color: SIMD4(0.6, 0.6, 0.6, 1))
        }
        .padding(16)
        .background(color: SIMD4(0.15, 0.15, 0.18, 1), cornerRadius: 8)

        let layout = card.renderLayout(width: 400)
        XCTAssertGreaterThan(layout.size.width, 32)
        XCTAssertGreaterThan(layout.size.height, 50)

        let scene = layout.node.flattened()
        XCTAssertFalse(scene.primitives.isEmpty)

        // Should have at least: background quad + text runs + divider line
        let hasQuad = scene.primitives.contains { if case .quad = $0.kind { return true }; return false }
        let hasText = scene.primitives.contains { if case .textRun = $0.kind { return true }; return false }
        let hasLine = scene.primitives.contains { if case .line = $0.kind { return true }; return false }
        XCTAssertTrue(hasQuad)
        XCTAssertTrue(hasText)
        XCTAssertTrue(hasLine)
    }

    func testVVGroupInStack() {
        let stack = VVStack(spacing: 4) {
            VVGroup {
                VText("A")
                VText("B")
            }
            VText("C")
        }
        let layout = stack.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertGreaterThan(layout.size.height, 0)
    }
}

// MARK: - VVNodeView Tests

final class VVNodeViewTests: XCTestCase {
    func testPassthroughNodeAndSize() {
        let quad = VVQuadPrimitive(frame: CGRect(x: 0, y: 0, width: 50, height: 30), color: SIMD4(1, 0, 0, 1))
        let node = VVNode(primitives: [.quad(quad)])
        let view = VVNodeView(node: node, size: CGSize(width: 50, height: 30))
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 50)
        XCTAssertEqual(layout.size.height, 30)
        XCTAssertEqual(layout.node.primitives.count, 1)
    }

    func testIgnoresConstraint() {
        let node = VVNode()
        let view = VVNodeView(node: node, size: CGSize(width: 200, height: 100))
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 50))
        // Size should be the specified size, not constrained
        XCTAssertEqual(layout.size.width, 200)
        XCTAssertEqual(layout.size.height, 100)
    }
}

// MARK: - VVImage Tests

final class VVImageViewTests: XCTestCase {
    func testImageView() {
        let view = VVImage(url: "https://example.com/img.png", size: CGSize(width: 120, height: 80))
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 120)
        XCTAssertEqual(layout.size.height, 80)
        if case .image(let img) = layout.node.primitives[0] {
            XCTAssertEqual(img.url, "https://example.com/img.png")
            XCTAssertEqual(img.cornerRadius, 4)
        } else {
            XCTFail("Expected image primitive")
        }
    }

    func testCustomCornerRadius() {
        let view = VVImage(url: "test.png", size: CGSize(width: 50, height: 50), cornerRadius: 12)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        if case .image(let img) = layout.node.primitives[0] {
            XCTAssertEqual(img.cornerRadius, 12)
        } else {
            XCTFail("Expected image primitive")
        }
    }
}

// MARK: - VVTextBlockView Tests

final class VVTextBlockViewTests: XCTestCase {
    func testEmptyRuns() {
        let view = VVTextBlockView(runs: [])
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 300))
        XCTAssertEqual(layout.size.width, 300)
        XCTAssertEqual(layout.size.height, 0)
    }

    func testWithRuns() {
        let glyph = VVTextGlyph(glyphID: 1, position: CGPoint(x: 10, y: 20), size: CGSize(width: 8, height: 14), color: SIMD4(1, 1, 1, 1), fontVariant: .regular, fontSize: 14)
        let run = VVTextRunPrimitive(glyphs: [glyph], style: VVTextRunStyle(), lineBounds: CGRect(x: 10, y: 10, width: 50, height: 20), runBounds: CGRect(x: 10, y: 10, width: 50, height: 20), position: CGPoint(x: 10, y: 20), fontSize: 14)
        let view = VVTextBlockView(runs: [run])
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 300))
        XCTAssertGreaterThan(layout.size.height, 0)
        XCTAssertEqual(layout.node.primitives.count, 1)
        if case .textRun = layout.node.primitives[0] {} else {
            XCTFail("Expected textRun primitive")
        }
    }
}

// MARK: - VVOffsetModifier Tests

final class VVOffsetModifierTests: XCTestCase {
    func testOffset() {
        let view = VSpacer(width: 50, height: 30).offset(x: 10, y: 20)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        // Size should be the child size
        XCTAssertEqual(layout.size.width, 50)
        XCTAssertEqual(layout.size.height, 30)
        // Node should wrap child with offset
        XCTAssertEqual(layout.node.offset.x, 10)
        XCTAssertEqual(layout.node.offset.y, 20)
    }

    func testZeroOffset() {
        let view = VSpacer(width: 50, height: 30).offset()
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.node.offset.x, 0)
        XCTAssertEqual(layout.node.offset.y, 0)
    }
}

// MARK: - VVPositionedFrame Tests

final class VVPositionedFrameTests: XCTestCase {
    func testPositioning() {
        let child = VSpacer(width: 50, height: 30)
        let frame = CGRect(x: 100, y: 200, width: 80, height: 60)
        let view = VVPositionedFrame(frame: frame, child: child)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 80)
        XCTAssertEqual(layout.size.height, 60)
        XCTAssertEqual(layout.node.offset.x, 100)
        XCTAssertEqual(layout.node.offset.y, 200)
    }

    func testClipping() {
        let child = VSpacer(width: 50, height: 30)
        let frame = CGRect(x: 0, y: 0, width: 80, height: 60)
        let clip = CGRect(x: 0, y: 0, width: 40, height: 40)
        let view = VVPositionedFrame(frame: frame, child: child, clipRect: clip)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.node.clipRect, clip)
    }

    func testConstrainsChild() {
        // The child should receive the frame's dimensions as constraints
        let child = VRect(color: SIMD4(1, 0, 0, 1)) // VRect fills width
        let frame = CGRect(x: 10, y: 10, width: 120, height: 80)
        let view = VVPositionedFrame(frame: frame, child: child)
        let layout = view.layout(in: VVLayoutEnvironment(), constraint: VVLayoutConstraint(maxWidth: 400))
        XCTAssertEqual(layout.size.width, 120)
        XCTAssertEqual(layout.size.height, 80)
    }
}
