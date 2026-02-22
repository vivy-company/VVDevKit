# VVDevKit

[![macOS](https://img.shields.io/badge/macOS-13.0+-black?style=flat-square&logo=apple)](https://github.com/vivy-company/VVDevKit)
[![iOS](https://img.shields.io/badge/iOS-13.0+-black?style=flat-square&logo=apple)](https://github.com/vivy-company/VVDevKit)
[![Swift](https://img.shields.io/badge/Swift-5.9+-F05138?style=flat-square&logo=swift&logoColor=white)](https://swift.org)
[![License](https://img.shields.io/badge/License-GPL%203.0-blue?style=flat-square)](LICENSE)
[![Sponsor](https://img.shields.io/badge/-Sponsor-ff69b4?style=flat-square&logo=githubsponsors&logoColor=white)](https://github.com/sponsors/vivy-company)

VVDevKit is a Metal-based rendering framework for macOS and iOS with batteries included.
It provides production-oriented modules for code editing, markdown rendering, syntax highlighting, and timeline-style UI, all built on top of a shared primitives layer.

Built for [Aizen.win](https://github.com/vivy-company/aizen).

> **Status:** VVDevKit is early and under active development. Public APIs, module boundaries, and package structure can change.

## What Is Included

- `VVDevKit` (umbrella module)
- `VVCode` (Metal-based code editor)
- `VVMarkdown` (Metal-based markdown renderer)
- `VVMetalPrimitives` (scene graph, primitives, and layout/view composition)
- `VVHighlighting` (Tree-sitter syntax highlighting)
- `VVGit` (git parsing/integration helpers)
- `VVLSP` (Language Server Protocol integration)
- `VVChatTimeline` (timeline/chat UI module built on VVMarkdown + primitives)

## Architecture

VVDevKit is layered:

1. `VVMetalPrimitives` is the rendering substrate (primitives, scene, layout/view composition).
2. Feature modules (`VVCode`, `VVMarkdown`, `VVChatTimeline`) build on top of primitives.
3. Support modules (`VVHighlighting`, `VVGit`, `VVLSP`) provide language and tooling integration.
4. `VVDevKit` re-exports the batteries-included surface for convenient adoption.

See `Docs/Architecture.md` for module boundaries, dependency rules, and extraction phases.

## Requirements

- macOS 13+ / iOS 13+
- Swift 5.9+

## Installation

Add the package:

```swift
dependencies: [
    .package(url: "https://github.com/vivy-company/VVDevKit", from: "0.1.0")
]
```

Use the umbrella product:

```swift
.target(
    name: "YourApp",
    dependencies: [
        .product(name: "VVDevKit", package: "VVDevKit")
    ]
)
```

Then import:

```swift
import VVDevKit
```

You can also depend on individual products (`VVCode`, `VVMarkdown`, `VVMetalPrimitives`, `VVChatTimeline`) if you want a narrower integration.

## Dynamic Grammar Loading

Language grammars are built as dynamic libraries and loaded on demand.

```bash
swift build --product TreeSitterSwift
swift build --product TreeSitterPython
swift build --product TreeSitterRust
```

Bundle the generated `.dylib` files in your app's Frameworks folder.

## Roadmap

- Keep VVDevKit as the batteries-included framework in this repository.
- Keep `VVMetalPrimitives` as the core substrate and continue hardening boundaries.
- Extract primitives/pipelines into a separate Swift package (and potentially separate repo) when boundaries are stable.

## License

GPL-3.0
