import CoreGraphics

// MARK: - Convenience Rendering

extension VVView {
    public func renderNode(width: CGFloat, env: VVLayoutEnvironment = VVLayoutEnvironment()) -> VVNode {
        let constraint = VVLayoutConstraint(maxWidth: width)
        return layout(in: env, constraint: constraint).node
    }

    public func renderScene(width: CGFloat, env: VVLayoutEnvironment = VVLayoutEnvironment()) -> VVScene {
        renderNode(width: width, env: env).flattened()
    }

    public func renderLayout(width: CGFloat, env: VVLayoutEnvironment = VVLayoutEnvironment()) -> VVViewLayout {
        let constraint = VVLayoutConstraint(maxWidth: width)
        return layout(in: env, constraint: constraint)
    }
}
