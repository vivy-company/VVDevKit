import simd

// MARK: - Color Presets

extension SIMD4 where Scalar == Float {
    // MARK: Basic Colors

    public static var white: SIMD4<Float> { SIMD4(1, 1, 1, 1) }
    public static var black: SIMD4<Float> { SIMD4(0, 0, 0, 1) }
    public static var clear: SIMD4<Float> { SIMD4(0, 0, 0, 0) }

    // MARK: Standard Colors

    public static var red: SIMD4<Float> { SIMD4(0.95, 0.3, 0.3, 1) }
    public static var green: SIMD4<Float> { SIMD4(0.3, 0.85, 0.4, 1) }
    public static var blue: SIMD4<Float> { SIMD4(0.3, 0.5, 0.95, 1) }
    public static var yellow: SIMD4<Float> { SIMD4(0.95, 0.85, 0.2, 1) }
    public static var orange: SIMD4<Float> { SIMD4(0.95, 0.6, 0.2, 1) }
    public static var purple: SIMD4<Float> { SIMD4(0.7, 0.35, 0.9, 1) }
    public static var pink: SIMD4<Float> { SIMD4(0.9, 0.4, 0.6, 1) }
    public static var cyan: SIMD4<Float> { SIMD4(0.3, 0.8, 0.9, 1) }
    public static var teal: SIMD4<Float> { SIMD4(0.3, 0.8, 0.5, 1) }
    public static var amber: SIMD4<Float> { SIMD4(0.95, 0.7, 0.2, 1) }
    public static var rose: SIMD4<Float> { SIMD4(0.85, 0.38, 0.5, 1) }
    public static var indigo: SIMD4<Float> { SIMD4(0.45, 0.55, 0.95, 1) }
    public static var mint: SIMD4<Float> { SIMD4(0.2, 0.9, 0.6, 1) }

    // MARK: Grayscale

    public static func gray(_ brightness: Float, opacity: Float = 1) -> SIMD4<Float> {
        SIMD4(brightness, brightness, brightness, opacity)
    }

    public static var gray10: SIMD4<Float> { gray(0.1) }
    public static var gray20: SIMD4<Float> { gray(0.2) }
    public static var gray30: SIMD4<Float> { gray(0.3) }
    public static var gray40: SIMD4<Float> { gray(0.4) }
    public static var gray50: SIMD4<Float> { gray(0.5) }
    public static var gray60: SIMD4<Float> { gray(0.6) }
    public static var gray70: SIMD4<Float> { gray(0.7) }
    public static var gray80: SIMD4<Float> { gray(0.8) }
    public static var gray90: SIMD4<Float> { gray(0.9) }

    // MARK: Surface Colors (dark UI)

    public static var darkSurface: SIMD4<Float> { SIMD4(0.15, 0.15, 0.18, 1) }
    public static var darkBackground: SIMD4<Float> { SIMD4(0.08, 0.09, 0.1, 1) }
    public static var lightText: SIMD4<Float> { SIMD4(0.9, 0.92, 0.95, 1) }
    public static var darkText: SIMD4<Float> { SIMD4(0.18, 0.2, 0.24, 1) }

    // MARK: Constructors

    public static func rgba(_ r: Float, _ g: Float, _ b: Float, _ a: Float = 1) -> SIMD4<Float> {
        SIMD4(r, g, b, a)
    }

    public static func hex(_ value: UInt32) -> SIMD4<Float> {
        let r = Float((value >> 16) & 0xFF) / 255.0
        let g = Float((value >> 8) & 0xFF) / 255.0
        let b = Float(value & 0xFF) / 255.0
        return SIMD4(r, g, b, 1)
    }

    public static func hex(_ value: UInt32, opacity: Float) -> SIMD4<Float> {
        let r = Float((value >> 16) & 0xFF) / 255.0
        let g = Float((value >> 8) & 0xFF) / 255.0
        let b = Float(value & 0xFF) / 255.0
        return SIMD4(r, g, b, opacity)
    }

    // MARK: Modifiers

    public func withOpacity(_ alpha: Float) -> SIMD4<Float> {
        SIMD4(x, y, z, alpha)
    }

    public func lighter(_ amount: Float = 0.15) -> SIMD4<Float> {
        SIMD4(min(1, x + amount), min(1, y + amount), min(1, z + amount), w)
    }

    public func darker(_ amount: Float = 0.15) -> SIMD4<Float> {
        SIMD4(max(0, x - amount), max(0, y - amount), max(0, z - amount), w)
    }
}
