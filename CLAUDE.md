# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

```bash
# Build the package
swift build

# Build in release mode
swift build -c release

# Run tests
swift test

# Run a specific test
swift test --filter VVCodeTests.HighlighterTests

# Build a specific grammar (produces .dylib for dynamic loading)
swift build --product TreeSitterSwift
swift build --product TreeSitterPython
# etc.
```

## Architecture

VVDevKit is a Metal-based kit of reusable components and Swift code. The VVCode module provides the editor layer, with supporting modules for rendering, highlighting, Git, LSP, and Markdown:

### Module Hierarchy

```
VVCode (public API + core text view / Metal rendering)
├── VVHighlighting (Tree-sitter syntax highlighting)
├── VVGit (git status/diff parsing)
├── VVLSP (Language Server Protocol)
└── VVMarkdown (Markdown rendering)
```

### Key Components

**VVCodeView** (`Sources/VVCode/VVCodeView.swift`)
- SwiftUI wrapper that auto-detects Metal availability
- Uses `VVMetalEditorContainerView` when Metal available, falls back to AppKit
- Manages LSP server lifecycle automatically

**MetalTextView** (`Sources/VVCode/Core/Metal/MetalTextView.swift`)
- GPU-accelerated text rendering using Metal
- Batched rendering: glyphs, selections, cursors, indent guides, gutter
- Uses `TextLayoutEngine` for line layout with glyph caching
- Supports folding via `setFoldedLineRanges()`

**TreeSitterHighlighter** (`Sources/VVHighlighting/TreeSitterHighlighter.swift`)
- Actor-based incremental parsing
- Converts Tree-sitter UTF-16 byte offsets to NSRange
- Supports all Tree-sitter queries (highlights, injections, locals)

**Dynamic Grammar Loading** (`Sources/VVHighlighting/LanguageBundle.swift`)
- 150+ grammars in `Sources/Grammars/`
- Loaded lazily via `LanguageRegistry.shared`
- Grammars built as .dylib for on-demand loading

**VVLanguageServer** (`Sources/VVLSP/Server/VVLanguageServer.swift`)
- Spawns and manages LSP server processes
- Uses JSON-RPC transport over stdin/stdout
- Auto-discovers servers via `LSPServerRegistry`

### Rendering Pipeline

1. Text changes → `MetalTextView.setText()` or `applyEdit()`
2. Layout computed via `TextLayoutEngine.layoutLine()`
3. Syntax ranges from `TreeSitterHighlighter.highlights()`
4. Batches prepared: `prepareGlyphBatch()`, `prepareSelectionBatch()`, etc.
5. Single `draw()` call renders all batches via `MetalRenderer`

### Text Storage

- Uses piece table internally (`PieceTable`)
- Line-based indexing via `lineStarts` and `lineLengths` arrays
- Incremental edits via `applyEdit(range:replacement:)`

## Conventions

- Platform: macOS 13+ / iOS 13+ (Swift 5.9+)
- Metal shaders in `Sources/VVCode/Core/Metal/Shaders.metal`
- Tree-sitter queries in `Sources/VVHighlighting/Resources/queries/`
- Each grammar is a separate target with C sources in `src/` and headers in `include/`
