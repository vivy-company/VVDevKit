import CoreGraphics

// MARK: - VSpacer

public struct VSpacer: VVView {
    public var width: CGFloat
    public var height: CGFloat

    public init(width: CGFloat = 0, height: CGFloat = 0) {
        self.width = width
        self.height = height
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        VVViewLayout(size: CGSize(width: width, height: height), node: VVNode())
    }
}

// MARK: - VDivider

public struct VDivider: VVView {
    public var thickness: CGFloat
    public var color: SIMD4<Float>
    public var inset: CGFloat

    public init(thickness: CGFloat = 1, color: SIMD4<Float> = .white.withOpacity(0.2), inset: CGFloat = 0) {
        self.thickness = thickness
        self.color = color
        self.inset = inset
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let lineWidth = max(0, constraint.maxWidth - inset * 2)
        let line = VVLinePrimitive(
            start: CGPoint(x: inset, y: thickness * 0.5),
            end: CGPoint(x: inset + lineWidth, y: thickness * 0.5),
            thickness: thickness,
            color: color
        )
        let node = VVNode(primitives: [.line(line)])
        return VVViewLayout(size: CGSize(width: constraint.maxWidth, height: max(1, thickness)), node: node)
    }
}

// MARK: - VVNodeView

public struct VVNodeView: VVView {
    public var node: VVNode
    public var size: CGSize

    public init(node: VVNode, size: CGSize) {
        self.node = node
        self.size = size
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        VVViewLayout(size: size, node: node)
    }
}

// MARK: - VVImage

public struct VVImage: VVView {
    public var url: String
    public var size: CGSize
    public var cornerRadius: CGFloat

    public init(url: String, size: CGSize, cornerRadius: CGFloat = 4) {
        self.url = url
        self.size = size
        self.cornerRadius = cornerRadius
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        let frame = CGRect(origin: .zero, size: size)
        let primitive = VVImagePrimitive(url: url, frame: frame, cornerRadius: cornerRadius)
        let node = VVNode(primitives: [.image(primitive)])
        return VVViewLayout(size: size, node: node)
    }
}

// MARK: - VVTextBlockView

public struct VVTextBlockView: VVView {
    public var runs: [VVTextRunPrimitive]

    public init(runs: [VVTextRunPrimitive]) {
        self.runs = runs
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
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
            bounds = CGRect(origin: .zero, size: CGSize(width: constraint.maxWidth, height: 0))
        }

        let primitives = runs.map { VVPrimitiveKind.textRun($0) }
        let node = VVNode(primitives: primitives)
        let size = CGSize(width: max(constraint.maxWidth, bounds.maxX), height: max(0, bounds.maxY))
        return VVViewLayout(size: size, node: node)
    }
}

// MARK: - VVGroup

public struct VVGroup: VVView {
    public var children: [any VVView]

    public init(@VVViewBuilder content: () -> [any VVView]) {
        self.children = content()
    }

    public init(_ children: [any VVView]) {
        self.children = children
    }

    public func layout(in env: VVLayoutEnvironment, constraint: VVLayoutConstraint) -> VVViewLayout {
        var y: CGFloat = 0
        var maxWidth: CGFloat = 0
        var nodes: [VVNode] = []

        for child in children {
            let childLayout = child.layout(in: env, constraint: constraint)
            let node = VVNode(offset: CGPoint(x: 0, y: y), children: [childLayout.node])
            nodes.append(node)
            y += childLayout.size.height
            maxWidth = max(maxWidth, childLayout.size.width)
        }

        return VVViewLayout(
            size: CGSize(width: maxWidth, height: y),
            node: VVNode(children: nodes)
        )
    }
}
