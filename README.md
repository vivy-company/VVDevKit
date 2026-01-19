# VVKit

[![Sponsor](https://img.shields.io/badge/Sponsor-vivy--company-ea4aaa?logo=github)](https://github.com/sponsors/vivy-company)

VVKit is a kit of Metal-based, reusable components and Swift code for building editor- and document-centric apps on macOS and iOS. It includes the VVCode editor, markdown rendering, Metal primitives, highlighting, Git integration, and LSP support.

Built for [Aizen.win](https://github.com/vivy-company/aizen).

> **Note:** VVKit is experimental and under active development. APIs may change and bugs are expected. A demo app will be available in a future release.

The primary editor module is `VVCode`, with supporting modules for rendering, highlighting, Git, LSP, and Markdown.

## Features

- **Metal Primitives** - Reusable Metal-backed nodes and layout components (`VVMetalPrimitives`)
- **VVCode Editor** - Metal-accelerated text rendering and editing
- **Syntax Highlighting** - Tree-sitter based highlighting with a large grammar set
- **Markdown Rendering** - Markdown layout and rendering on top of Metal primitives
- **LSP + Git** - Language Server Protocol integration and git status/diff support
- **Tooling** - `VVMarkdownDump` CLI for debugging markdown output

## Requirements

- macOS 13+ / iOS 13+
- Swift 5.9+

## Installation

Add to your `Package.swift`:

```swift
dependencies: [
    .package(url: "https://github.com/vivy-company/VVKit", from: "0.1.0")
]
```

Then add the dependency to your target (the package name is still `VVCode`):

```swift
.target(
    name: "YourApp",
    dependencies: ["VVCode", "VVMetalPrimitives", "VVMarkdown"]
)
```

## Modules

| Module | Description |
|--------|-------------|
| `VVCode` | Editor public API and SwiftUI wrapper |
| `VVCodeCore` | Core text view, layout, and Metal rendering |
| `VVMetalPrimitives` | Metal-backed primitive scene graph and layout components |
| `VVHighlighting` | Tree-sitter syntax highlighting |
| `VVGit` | Git integration |
| `VVLSP` | Language Server Protocol support |
| `VVMarkdown` | Markdown rendering |
| `VVMarkdownDump` | CLI tool for markdown debugging |

## Dynamic Grammar Loading

Language grammars are built as dynamic libraries and loaded on demand. Build individual grammars:

```bash
swift build --product TreeSitterSwift
swift build --product TreeSitterPython
swift build --product TreeSitterRust
# etc.
```

Bundle the `.dylib` files in your app's Frameworks folder.

## License

GPL-3.0
