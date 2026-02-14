@resultBuilder
public struct VVViewBuilder {
    public static func buildBlock() -> [any VVView] {
        []
    }

    public static func buildBlock(_ components: any VVView...) -> [any VVView] {
        components
    }

    public static func buildBlock(_ components: [any VVView]...) -> [any VVView] {
        components.flatMap { $0 }
    }

    public static func buildExpression(_ expression: any VVView) -> [any VVView] {
        [expression]
    }

    public static func buildExpression(_ expression: [any VVView]) -> [any VVView] {
        expression
    }

    public static func buildOptional(_ component: [any VVView]?) -> [any VVView] {
        component ?? []
    }

    public static func buildEither(first component: [any VVView]) -> [any VVView] {
        component
    }

    public static func buildEither(second component: [any VVView]) -> [any VVView] {
        component
    }

    public static func buildArray(_ components: [[any VVView]]) -> [any VVView] {
        components.flatMap { $0 }
    }

    public static func buildLimitedAvailability(_ component: [any VVView]) -> [any VVView] {
        component
    }

    public static func buildFinalResult(_ component: [any VVView]) -> [any VVView] {
        component
    }
}
