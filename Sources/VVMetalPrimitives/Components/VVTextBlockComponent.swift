import CoreGraphics

public struct VVTextBlockComponent: VVComponent {
    public var runs: [VVTextRunPrimitive]

    public init(runs: [VVTextRunPrimitive]) {
        self.runs = runs
    }

    public func measure(in env: VVLayoutEnvironment, width: CGFloat) -> VVComponentLayout {
        var bounds = CGRect.null
        for run in runs {
            if let runBounds = run.runBounds {
                bounds = bounds.union(runBounds)
                continue
            }
            if let lineBounds = run.lineBounds {
                bounds = bounds.union(lineBounds)
                continue
            }
            for glyph in run.glyphs {
                let glyphRect = CGRect(origin: glyph.position, size: glyph.size)
                bounds = bounds.union(glyphRect)
            }
        }

        if bounds.isNull {
            bounds = CGRect(origin: .zero, size: CGSize(width: width, height: 0))
        }

        let primitives = runs.map { VVPrimitiveKind.textRun($0) }
        let node = VVNode(primitives: primitives)
        let size = CGSize(width: max(width, bounds.maxX), height: max(0, bounds.maxY))
        return VVComponentLayout(size: size, node: node)
    }
}

