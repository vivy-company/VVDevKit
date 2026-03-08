import CoreGraphics

#if canImport(SwiftUI)
import SwiftUI
#endif

// MARK: - Easing

public enum VVEasing: String, Hashable, Sendable, CaseIterable {
    case linear
    case easeIn
    case easeOut
    case easeInOut
    case smooth
    case snappy
    case bouncy

    public func value(at progress: CGFloat) -> CGFloat {
        let t = min(max(progress, 0), 1)

        switch self {
        case .linear:
            return t
        case .easeIn:
            return t * t * t
        case .easeOut:
            let inverse = 1 - t
            return 1 - inverse * inverse * inverse
        case .easeInOut:
            if t < 0.5 {
                return 4 * t * t * t
            }
            let inverse = -2 * t + 2
            return 1 - (inverse * inverse * inverse) / 2
        case .smooth:
            // Smootherstep removes visible acceleration discontinuities.
            return t * t * t * (t * (t * 6 - 15) + 10)
        case .snappy:
            // Back-out curve: quick response with a restrained overshoot.
            let overshoot: CGFloat = 1.45
            let shifted = t - 1
            return 1 + (overshoot + 1) * shifted * shifted * shifted + overshoot * shifted * shifted
        case .bouncy:
            return bounceOut(t)
        }
    }

    private func bounceOut(_ t: CGFloat) -> CGFloat {
        let n1: CGFloat = 7.5625
        let d1: CGFloat = 2.75

        if t < 1 / d1 {
            return n1 * t * t
        }
        if t < 2 / d1 {
            let shifted = t - 1.5 / d1
            return n1 * shifted * shifted + 0.75
        }
        if t < 2.5 / d1 {
            let shifted = t - 2.25 / d1
            return n1 * shifted * shifted + 0.9375
        }
        let shifted = t - 2.625 / d1
        return n1 * shifted * shifted + 0.984375
    }
}

#if canImport(SwiftUI)
// MARK: - SwiftUI Presets

public enum VVAnimation {
    public static func linear(duration: Double = 0.16) -> Animation {
        .linear(duration: duration)
    }

    public static func easeIn(duration: Double = 0.16) -> Animation {
        .easeIn(duration: duration)
    }

    public static func easeOut(duration: Double = 0.16) -> Animation {
        .easeOut(duration: duration)
    }

    public static func easeInOut(duration: Double = 0.2) -> Animation {
        .easeInOut(duration: duration)
    }

    public static func smooth(duration: Double = 0.24) -> Animation {
        if #available(macOS 14.0, iOS 17.0, *) {
            return .smooth(duration: duration)
        } else {
            return .timingCurve(0.25, 0.1, 0.25, 1, duration: duration)
        }
    }

    public static func snappy(duration: Double = 0.24, extraBounce: Double = 0) -> Animation {
        if #available(macOS 14.0, iOS 17.0, *) {
            return .snappy(duration: duration, extraBounce: extraBounce)
        } else {
            return .interpolatingSpring(mass: 0.9, stiffness: 340, damping: 30, initialVelocity: 0)
        }
    }

    public static func bouncy(duration: Double = 0.32, extraBounce: Double = 0.12) -> Animation {
        if #available(macOS 14.0, iOS 17.0, *) {
            return .bouncy(duration: duration, extraBounce: extraBounce)
        } else {
            return .interpolatingSpring(mass: 0.85, stiffness: 250, damping: 18, initialVelocity: 0)
        }
    }

    public static func gentleSpring(response: Double = 0.32, dampingFraction: Double = 0.82) -> Animation {
        .spring(response: response, dampingFraction: dampingFraction)
    }

    public static func transitionSpring(response: Double = 0.26, dampingFraction: Double = 0.86) -> Animation {
        .spring(response: response, dampingFraction: dampingFraction)
    }
}
#endif
