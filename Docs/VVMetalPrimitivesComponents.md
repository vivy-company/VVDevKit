VVMetalPrimitives Components (Draft)

Goal
- Introduce composable, layout-aware components that produce VVNode trees.
- Separate layout/measurement from primitive emission.
- Make Markdown rendering stable and customizable by swapping components or styles.

Core Types
- VVLayoutEnvironment: shared config (scale, colors, corner radii).
- VVComponentLayout: measured size + VVNode.
- VVComponent protocol: measure(width:) -> layout.

Initial Components
- VVStackComponent: vertical layout + alignment.
- VVInsetComponent: padding wrapper.
- VVTextBlockComponent: wraps pre-laid-out runs; computes bounds from run/line/glyph bounds.
- VVImageComponent: image primitive wrapper.
- VVRuleComponent: horizontal rule primitive.

Design Notes
- VVNode already supports children + offset + clipping. Components should emit nodes in local coordinates.
- Layout should be deterministic and purely functional so debug tools can dump the tree.
- MarkdownLayoutEngine can keep doing parsing and glyph layout for now; components can wrap its output.
- Next step: add MarkdownComponentBuilder that maps LayoutBlock -> VVComponent, enabling themed overrides.

Follow-ups
- Add VVAbsoluteComponent for bridging pre-positioned layout blocks.
- Add VVGridComponent for tables.
- Add VVInlineFlowComponent for inline badges/images with consistent spacing.
- Add style tokens (MarkdownTheme -> component styles) for per-block customization.

