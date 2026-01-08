import CoreGraphics

public extension VVNode {
    static func fromScene(_ scene: VVScene) -> VVNode {
        let children: [VVNode] = scene.primitives.map { primitive in
            VVNode(
                clipRect: primitive.clipRect,
                zIndex: primitive.zIndex,
                primitives: [primitive.kind]
            )
        }
        return VVNode(children: children)
    }
}

