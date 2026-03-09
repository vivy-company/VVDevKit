# Stress Markdown Fixture

## Overview

This fixture exists to exercise the markdown parser, layout engine, scene builder, and headless Metal renderer without requiring a live window.

It intentionally mixes:

- paragraphs with long wrapping text that should span multiple lines inside a constrained viewport width
- inline `code spans`, [links](https://example.com/docs), and ~~strikethrough~~ segments
- task lists and nested lists
- block quotes and callout-like prose
- tables and fenced code blocks
- image references that resolve to deterministic placeholder sizes during tests

> Renderers should keep scrolling responsive even when repeated blocks create a very tall document.
> Selection is not the focus here; this fixture is about parse, layout, scene construction, and visible-slice encoding.

### Checklist

- [x] Parse markdown into blocks
- [x] Build a layout tree
- [x] Convert layout into `VVScene`
- [x] Encode visible slices into an offscreen Metal texture
- [ ] Regress performance unnoticed

### Data Table

| Column | Value | Notes |
| --- | --- | --- |
| Name | Render Stress | Used by automated tests |
| Surface | Markdown | Repeated many times |
| Width | 1100 | Chosen to force wrap in some blocks |
| Goal | Headless encode | No NSWindow required |

### Code

```swift
struct StressCard: Identifiable {
    let id: Int
    let title: String
    let detail: String

    var debugDescription: String {
        "\(id): \(title) -> \(detail)"
    }
}

let cards = (0..<16).map {
    StressCard(
        id: $0,
        title: "Card \($0)",
        detail: "This is a moderately long detail string used to force wrapping and repeated glyph emission."
    )
}

for card in cards {
    print(card.debugDescription)
}
```

### Mixed Inline Content

This line contains badges and images:

![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Coverage](https://img.shields.io/badge/coverage-95%25-blue)
![Version](https://img.shields.io/badge/version-1.2.3-orange)

### Nested Lists

1. First section
   - Item A with additional explanatory text that wraps in narrower widths.
   - Item B with `inline code` and [docs](https://example.com/reference).
2. Second section
   - Nested check
     - [x] completed row
     - [ ] pending row
3. Third section
   - Final note with enough text to create a visibly wider paragraph region and a denser scene.

### Quote

> A fast renderer is only useful if interactions and redraw paths stay bounded.
>
> The headless tests should step through multiple scroll windows and encode only the visible slice plus a small overscan region.

### Footer

The tests repeat this fixture many times to create a large document from a portable in-repo resource.
