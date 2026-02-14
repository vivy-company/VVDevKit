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

    // MARK: - Border

    public func border(_ border: VVBorder, cornerRadii: VVCornerRadii = .zero) -> VVBorderModifier {
        VVBorderModifier(child: self, border: border, cornerRadii: cornerRadii)
    }

    public func border(color: SIMD4<Float>, width: CGFloat = 1, cornerRadii: VVCornerRadii = .zero) -> VVBorderModifier {
        VVBorderModifier(child: self, border: VVBorder(width: width, color: color), cornerRadii: cornerRadii)
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

    public func frame(width: CGFloat? = nil, height: CGFloat? = nil) -> VVFrameModifier {
        VVFrameModifier(child: self, width: width, height: height)
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
}
