# VVDevKit Architecture Contract

This document defines stable boundaries between VVDevKit modules and `VVMetalPrimitives`.

## Goals

- Keep VVDevKit batteries included and practical for app teams.
- Keep `VVMetalPrimitives` extraction-ready as a standalone Swift package.
- Avoid tight coupling from primitives into product/domain modules.

## Module Roles

### `VVMetalPrimitives` (Core Rendering Substrate)

Owns low-level, reusable rendering building blocks:

- Primitive models (`VVQuadPrimitive`, `VVTextRunPrimitive`, paths, lines, images, table lines, etc.)
- Scene graph and scene building (`VVNode`, `VVScene`, `VVSceneBuilder`)
- Rendering/layout composition DSL (`VVView`, stacks, modifiers, components)
- Generic text layout/selection data structures and protocols
- Cross-module value types (`VVColor`, shared geometry/style tokens)

Must not own:

- Markdown parsing or markdown-specific domain models
- Code-editor behavior, diff presentation logic, or LSP/Git workflows
- Tree-sitter language/highlighting policy
- Product-specific UI semantics

### `VVCode` (Editor Module)

Owns editor behavior and UX:

- Editing operations, viewport management, cursor/selection policy
- Diff presentation, gutter UX, code-focused interactions
- Integration with `VVHighlighting`, `VVGit`, and `VVLSP`
- Rendering by converting editor state into primitives/scenes

### `VVMarkdown` (Markdown Module)

Owns markdown domain pipeline:

- Parse/layout/theme/component mapping for markdown content
- Markdown selection/hover semantics and markdown-specific overlays
- Rendering path that emits `VVMetalPrimitives` scenes

### `VVChatTimeline` (Timeline/Chat Module)

Owns timeline/chat presentation model and composition logic using markdown and primitives.

### Support Modules

- `VVHighlighting`: Tree-sitter loading and highlighting outputs
- `VVGit`: git parsing/status/blame helpers
- `VVLSP`: LSP transport/client abstractions

## Dependency Rules

1. `VVMetalPrimitives` must not import `VVCode`, `VVMarkdown`, `VVChatTimeline`, `VVHighlighting`, `VVGit`, or `VVLSP`.
2. Feature modules may depend on `VVMetalPrimitives`.
3. Domain-specific data should not be added to primitive types.
4. New primitives must be generic and reusable by at least two feature contexts, or they remain module-local.

## Platform Adapter Rule

To keep primitives extraction-ready:

- Core `VVMetalPrimitives` should stay platform-minimal.
- AppKit/UIKit-specific event controllers should live in adapter targets (for example, `VVMetalPrimitivesAppKit`) when split work begins.

Current note:

- `VVTextSelectionController` currently imports AppKit and is a candidate to move into an adapter target during boundary hardening.

## Extraction Plan (Phased)

1. Boundary hardening inside this repo
- Keep package monorepo.
- Enforce dependency rules in code review.
- Move platform adapters out of primitives core target.

2. Separate package publishing (same repo first)
- Publish `VVMetalPrimitives` as its own package product/path from this repository.
- Keep VVDevKit consuming the published primitives package interface.

3. Optional separate repository
- If needed, split `VVMetalPrimitives` to its own repository.
- Keep VVDevKit integration stable via package dependency and compatibility shims.

## Public API Stability

VVDevKit is pre-1.0. Breaking changes are expected while module boundaries and APIs evolve.
