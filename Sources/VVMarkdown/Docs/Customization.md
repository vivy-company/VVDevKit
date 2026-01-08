# VVMarkdown Customization Hooks

## Pipeline Overview

VVMarkdown renders through a single Metal primitives pipeline:

1. **Parse**: `MarkdownParser` → `ParsedMarkdownDocument`
2. **Layout**: `MarkdownLayoutEngine` → `MarkdownLayout`
3. **Scene**: `VVMarkdownRenderPipeline` → `VVMarkdownSceneBuilder` → `VVMarkdownComponentFactory` → `VVComponent` → `VVScene` (`VVMetalPrimitives`)
4. **Render**: `MarkdownMetalRenderer` draws the scene

This keeps layout deterministic and makes rendering fully composable through `VVMetalPrimitives`.

## Core Hooks

### 1) Theme
Use `MarkdownTheme` to control spacing, fonts, colors, radii, borders, and per-feature styling.

```swift
let theme = MarkdownTheme.dark
theme.codeBlockCornerRadius = 10
theme.tableGridColor = SIMD4<Float>(0.2, 0.2, 0.2, 1)
```

### 2) Style Registry (Block-Level Styling)
Use `MarkdownStyleRegistry` to customize per-block backgrounds, borders, and padding.

```swift
var registry = MarkdownStyleRegistry()
registry.codeBlock = MarkdownBlockStyle(
    padding: VVInsets(top: 8, left: 8, bottom: 8, right: 8),
    cornerRadius: 10,
    backgroundColor: SIMD4<Float>(0.15, 0.15, 0.15, 1),
    borderColor: SIMD4<Float>(0.25, 0.25, 0.25, 1),
    borderWidth: 1
)
```

### 3) Component Provider (Custom Components)
Override or wrap any layout block with custom components.

```swift
let provider: MarkdownComponentProvider = { block, context, fallback in
    switch block.blockType {
    case .heading:
        let base = fallback(block)
        return VVInsetComponent(
            insets: VVInsets(top: 6, left: 0, bottom: 6, right: 0),
            child: base
        )
    default:
        return fallback(block)
    }
}
```

### 4) Render Pipeline
`VVMarkdownRenderPipeline` is the single entry point that wires layout, components, and `VVMetalPrimitives` together.
Custom views should build scenes through the pipeline to ensure styling, hover, and selection behave consistently.

### 5) Component Factory (Default Blocks)
`VVMarkdownComponentFactory` builds the default component tree for each layout block.
You can reuse it or wrap its output inside `MarkdownComponentProvider` for consistent
behavior while adding custom visuals.

### 6) VVMetalPrimitives
Use `VVMetalPrimitives` components (`VVTextBlockComponent`, `VVImageComponent`, `VVLayerComponent`, `VVPrimitiveComponent`, etc.)
to compose custom visuals that still render inside the main pipeline.

`VVPrimitiveComponent` lets you inject raw primitives into the scene when you need custom drawing.

## Example: SwiftUI View

```swift
let view = VVMarkdownView(
    content: markdownText,
    theme: theme,
    componentProvider: provider,
    styleRegistry: registry
)
```

## Notes

- The pipeline is component + scene based: all visual output is composed into a `VVScene`.
- For advanced rendering, create custom `VVComponent`s that emit primitives or wrap existing blocks.
- Scene construction is centralized in `VVMarkdownSceneBuilder` and uses the `VVMetalPrimitives` component pipeline.
- Interaction overlays (selection/hover) are layered on top of the scene in `VVMarkdownView`.
