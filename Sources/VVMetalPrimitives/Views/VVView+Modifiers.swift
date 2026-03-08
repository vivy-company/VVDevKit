import CoreGraphics

extension VVView {
    // MARK: - Padding

    public func padding(_ value: CGFloat) -> VVPaddingModifier {
        VVPaddingModifier(child: self, top: value, right: value, bottom: value, left: value)
    }

    public func padding(top: CGFloat = 0, right: CGFloat = 0, bottom: CGFloat = 0, left: CGFloat = 0) -> VVPaddingModifier {
        VVPaddingModifier(child: self, top: top, right: right, bottom: bottom, left: left)
    }

    public func padding(horizontal: CGFloat = 0, vertical: CGFloat = 0) -> VVPaddingModifier {
        VVPaddingModifier(child: self, top: vertical, right: horizontal, bottom: vertical, left: horizontal)
    }

    // MARK: - Background

    public func background(color: SIMD4<Float>, cornerRadii: VVCornerRadii = .zero) -> VVBackgroundModifier {
        VVBackgroundModifier(child: self, color: color, cornerRadii: cornerRadii)
    }

    public func background(color: SIMD4<Float>, cornerRadius: CGFloat) -> VVBackgroundModifier {
        VVBackgroundModifier(child: self, color: color, cornerRadii: VVCornerRadii(cornerRadius))
    }

    public func background(alignment: VVFrameAlignment = .center, @VVViewBuilder content: () -> [any VVView]) -> VVBackgroundContentModifier {
        VVBackgroundContentModifier(
            child: self,
            background: VVZStack(alignment: alignment, sizing: .union, children: content()),
            alignment: alignment
        )
    }

    // MARK: - Border

    public func border(_ border: VVBorder, cornerRadii: VVCornerRadii = .zero) -> VVBorderModifier {
        VVBorderModifier(child: self, border: border, cornerRadii: cornerRadii)
    }

    public func border(color: SIMD4<Float>, width: CGFloat = 1, cornerRadii: VVCornerRadii = .zero) -> VVBorderModifier {
        VVBorderModifier(child: self, border: VVBorder(width: width, color: color), cornerRadii: cornerRadii)
    }

    // MARK: - Overlay

    public func overlay(alignment: VVFrameAlignment = .center, @VVViewBuilder content: () -> [any VVView]) -> VVOverlayModifier {
        VVOverlayModifier(
            child: self,
            overlay: VVZStack(alignment: alignment, sizing: .union, children: content()),
            alignment: alignment
        )
    }

    // MARK: - Shadow

    public func shadow(
        color: SIMD4<Float> = .black.withOpacity(0.3),
        spread: CGFloat = 10,
        blurRadius: CGFloat = 0,
        offset: CGPoint = .zero,
        cornerRadii: VVCornerRadii = .zero
    ) -> VVShadowModifier {
        VVShadowModifier(child: self, color: color, cornerRadii: cornerRadii, spread: spread, blurRadius: blurRadius, offset: offset)
    }

    // MARK: - Frame

    public func frame(width: CGFloat? = nil, height: CGFloat? = nil, alignment: VVFrameAlignment = .center) -> VVFrameModifier {
        VVFrameModifier(child: self, width: width, height: height, alignment: alignment)
    }

    public func frame(
        minWidth: CGFloat? = nil,
        idealWidth: CGFloat? = nil,
        maxWidth: CGFloat? = nil,
        minHeight: CGFloat? = nil,
        idealHeight: CGFloat? = nil,
        maxHeight: CGFloat? = nil,
        alignment: VVFrameAlignment = .center
    ) -> VVFrameModifier {
        VVFrameModifier(
            child: self,
            minWidth: minWidth,
            idealWidth: idealWidth,
            maxWidth: maxWidth,
            minHeight: minHeight,
            idealHeight: idealHeight,
            maxHeight: maxHeight,
            alignment: alignment
        )
    }

    public func fillWidth(alignment: VVFrameAlignment = .center) -> VVFrameModifier {
        frame(minWidth: 0, maxWidth: .greatestFiniteMagnitude, alignment: alignment)
    }

    public func fillHeight(alignment: VVFrameAlignment = .center) -> VVFrameModifier {
        frame(minHeight: 0, maxHeight: .greatestFiniteMagnitude, alignment: alignment)
    }

    // MARK: - Scroll

    public func scrollContainer(
        axis: VVScrollAxis = .vertical,
        viewportSize: CGSize? = nil,
        contentOffset: CGPoint = .zero,
        showsClipping: Bool = true
    ) -> VVScrollContainer {
        VVScrollContainer(child: self, axis: axis, viewportSize: viewportSize, contentOffset: contentOffset, showsClipping: showsClipping)
    }

    // MARK: - Opacity

    public func opacity(_ value: Float) -> VVOpacityModifier {
        VVOpacityModifier(child: self, opacity: value)
    }

    // MARK: - Clip

    public func clipRect(_ rect: CGRect) -> VVClipModifier {
        VVClipModifier(child: self, clipRect: rect)
    }

    // MARK: - ZIndex

    public func zIndex(_ value: Int) -> VVZIndexModifier {
        VVZIndexModifier(child: self, zIndex: value)
    }

    // MARK: - Offset

    public func offset(x: CGFloat = 0, y: CGFloat = 0) -> VVOffsetModifier {
        VVOffsetModifier(child: self, x: x, y: y)
    }

    // MARK: - Transform

    public func transform(_ transform: VVTransform2D) -> VVTransformModifier {
        VVTransformModifier(child: self, transform: transform)
    }

    public func rotation(_ angle: CGFloat) -> VVTransformModifier {
        VVTransformModifier(child: self, transform: .identity.rotated(by: angle))
    }

    public func scale(x: CGFloat, y: CGFloat) -> VVTransformModifier {
        VVTransformModifier(child: self, transform: .identity.scaled(x: x, y: y))
    }

    public func scale(_ factor: CGFloat) -> VVTransformModifier {
        VVTransformModifier(child: self, transform: .identity.scaled(by: factor))
    }

    // MARK: - Identity / Animation

    public func id(_ value: String) -> VVIdentityModifier {
        VVIdentityModifier(child: self, id: value)
    }

    public func transition(_ transition: VVTransition) -> VVTransitionModifier {
        VVTransitionModifier(child: self, transition: transition)
    }

    public func animation(_ animation: VVAnimationDescriptor) -> VVAnimationModifier {
        VVAnimationModifier(child: self, animation: animation)
    }
}
