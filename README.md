# VVCode

A Swift code editor library for macOS and iOS with syntax highlighting, LSP support, and Metal-accelerated rendering.

## Features

- **Syntax Highlighting** - Tree-sitter based highlighting with 150+ language grammars
- **LSP Support** - Language Server Protocol integration for code intelligence
- **Git Integration** - Built-in git status and diff support
- **Metal Rendering** - GPU-accelerated text rendering
- **Markdown** - Metal-rendered markdown view

## Requirements

- macOS 13+ / iOS 13+
- Swift 5.9+

## Installation

Add to your `Package.swift`:

```swift
dependencies: [
    .package(url: "https://github.com/vivy-company/VVCode", from: "0.1.0")
]
```

Then add the dependency to your target:

```swift
.target(
    name: "YourApp",
    dependencies: ["VVCode"]
)
```

## Modules

| Module | Description |
|--------|-------------|
| `VVCode` | Main public API (includes all modules) |
| `VVCodeCore` | Core text view and Metal rendering |
| `VVHighlighting` | Tree-sitter syntax highlighting |
| `VVGit` | Git integration |
| `VVLSP` | Language Server Protocol support |
| `VVMarkdown` | Markdown rendering |

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
