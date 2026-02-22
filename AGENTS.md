# AGENTS.md

Guidance for coding agents working in this repository.

## Project

- Name: `VVDevKit`
- Type: Swift Package (macOS + iOS)
- Stack: Swift, Metal, Tree-sitter grammars
- Main goal: Metal-based rendering framework with batteries included (`VVCode`, `VVMarkdown`, `VVMetalPrimitives`, `VVChatTimeline`)

## Fast Commands

```bash
# Build all
swift build

# Build in release
swift build -c release

# Build key targets
swift build --target VVDevKit
swift build --target VVCode
swift build --target VVMarkdown
swift build --target VVMetalPrimitives

# Tests
swift test
swift test --filter VVCodeTests.HighlighterTests

# Build a specific dynamic grammar
swift build --product TreeSitterSwift
```

## Repo Map

- `Sources/VVDevKit`: umbrella module (re-exports batteries-included modules)
- `Sources/VVMetalPrimitives`: rendering substrate (primitives, scene graph, view/layout DSL)
- `Sources/VVCode`: editor module
- `Sources/VVMarkdown`: markdown module
- `Sources/VVChatTimeline`: timeline/chat module
- `Sources/VVHighlighting`: Tree-sitter integration and queries
- `Sources/VVGit`: git parsers and models
- `Sources/VVLSP`: LSP clients/transports
- `Sources/Grammars`: vendored/generated Tree-sitter grammars
- `Docs/Architecture.md`: boundary contract and extraction plan

## Architecture Rules

Follow `Docs/Architecture.md` as the source of truth.

- `VVMetalPrimitives` is core substrate only.
- Feature/domain logic stays in `VVCode`, `VVMarkdown`, `VVChatTimeline`.
- `VVMetalPrimitives` must not depend on feature modules.
- Keep primitives generic; avoid domain-specific fields/types.

## Editing Rules

- Keep changes scoped to the user request.
- Preserve public API unless explicitly asked to change it.
- Avoid introducing new package dependencies without clear need.
- Prefer incremental, reviewable commits.
- Update docs when behavior or module boundaries change.

## Generated/Vendored Content

- Do not manually edit generated parser outputs unless the task requires regeneration.
- Avoid broad formatting churn in `Sources/Grammars`.
- Do not commit local build artifacts.

Ignored examples:

- `.build/`, `build/`, `tmp/`
- `*.gch`
- `Package.resolved` (currently ignored in this repo)

## Security + Public Repo Hygiene

- Never commit secrets, tokens, private keys, or credentials.
- Treat test/example credentials as placeholders only.
- Before release/public changes, run a quick secret scan (for example with `gitleaks`).
- Prefer relative or project-generic paths in docs and scripts.

## Validation Checklist

Before finishing:

1. Build relevant targets.
2. Run related tests (or explain why not run).
3. Check `git diff` for unrelated changes.
4. Ensure docs are aligned with architecture and module naming.

## Notes

- VVDevKit is pre-1.0 and APIs can change.
- Current canonical positioning is in `README.md`.
