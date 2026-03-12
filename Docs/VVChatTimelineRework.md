# VVChatTimeline Rework Spec

This document defines the target architecture for reworking `VVChatTimeline`.

It is written for the current project direction:

- macOS first
- Metal-only rendering
- AppKit as a thin host layer, not a rendering framework choice
- `VVMetalPrimitives` remains generic and extraction-ready

## Why Rework

The current timeline already has good low-level ingredients:

- stable item IDs
- estimated vs exact layout hydration
- visible-range rendering
- height indexing for large scrollable transcripts
- cache budgets for prepared markdown and scene windows

Those choices are directionally correct for large transcripts and streaming chat.

The problem is ownership concentration. Today, major responsibilities are fused together:

- timeline state + layout indexing + render cache coordination
- markdown preparation + scene construction + cache policy + custom item rendering
- scroll handling + selection + hover + hit testing + visible window scheduling + animation

This is workable for a focused early implementation, but it does not scale well as the product surface grows.

Main risks if the current shape continues:

- expensive synchronous work stays too close to the interaction path
- every new item kind increases coupling to a few large files
- animation policy remains tangled with scrolling and view hosting
- platform hosting concerns remain mixed into timeline layout/render logic
- public API surface calcifies around renderer implementation details

## Non-Goals

- Replace Metal with AppKit drawing or SwiftUI drawing
- Add UIKit as a first-class requirement
- Move chat-specific semantics into `VVMetalPrimitives`
- Build a generic list framework for every product surface immediately

## Core Principles

1. Metal remains the only rendering backend for the timeline.
2. AppKit remains required for macOS hosting, input, scrolling, and lifecycle.
3. AppKit must be treated as a thin host layer.
4. Timeline item identity and layout state must be platform-neutral.
5. Expensive layout preparation should be separated from interactive viewport logic.
6. New timeline item types must not require edits to one monolithic renderer.
7. Animation must be keyed by stable item identity and anchored geometry.

## Target Architecture

`VVChatTimeline` should be reworked into four internal layers.

### 1. Timeline Core

Owns:

- timeline item identity and ordering
- stable item diffing
- unread state
- pinned-to-bottom state
- anchor preservation
- visible-window bookkeeping inputs
- paging and retention policy hooks

Must not own:

- AppKit views
- Metal command encoding
- markdown parsing
- scene construction

Example responsibilities:

- append / insert / replace / remove items
- compute update deltas
- choose animation anchors
- expose timeline snapshots to layout/render systems

### Viewport Mode

The timeline core should treat viewport follow as an explicit mode, not an inferred scroll special case.

- `liveTail`: the viewport is attached to the transcript tail and new tail items should land in final position without extra viewport compensation
- `detached`: the viewport preserves its current reading position, new tail content accumulates unread state, and offscreen tail work should stay estimated/deferred until the viewport reattaches or approaches it

This keeps the common chat case simple without requiring a fully inverted scroll implementation.

### 2. Timeline Layout

Owns:

- estimated measurement
- exact measurement
- layout invalidation
- prepared layout artifacts
- image-size-driven relayout policy
- background preparation scheduling

Must not own:

- scroll view state
- hit testing
- Metal draw submission

The layout layer should produce a stable intermediate form for each item, for example:

- estimated height
- exact height
- content offset
- local content bounds
- layout revision
- visible content window metadata

### 3. Timeline Render

Owns:

- item renderers by item kind
- conversion from prepared layout to render fragments
- scene fragment assembly
- texture references
- render cache policy
- animation-ready snapshot payloads

Must not own:

- NSView / MTKView hosting
- scroll position policy
- gesture handling

This layer should not think in terms of "the whole timeline scene".
It should think in terms of visible per-item render fragments:

- background
- chrome
- content
- overlays
- hit regions

### 4. Timeline Host (macOS)

Owns:

- `NSView` / `NSScrollView` / `MTKView` hosting
- event routing
- hover / pointer / selection interaction
- clipboard actions
- viewport updates
- display link integration
- accessibility integration when added

Must not own:

- markdown preparation rules
- item-specific render construction
- broad cache policy beyond viewport-driven hints

This host layer is AppKit-specific, but it should stay thin.

## Module Boundary Rules

The following rules apply during the rework:

1. `VVMetalPrimitives` remains generic and must not gain timeline-specific models.
2. `VVChatTimeline` may depend on `VVMarkdown` and `VVMetalPrimitives`.
3. AppKit-specific types should be isolated to host files and not spread through core item/layout/render logic.
4. Timeline item models must not require `NSView`, `NSEvent`, or AppKit-specific geometry wrappers.
5. New reusable primitives discovered during the rework may move into `VVMetalPrimitives` only if they are clearly generic.

## Timeline Item Model

The current message-first model should be replaced with a first-class timeline item model.

Target item categories:

- `message`
- `toolGroup`
- `toolCall`
- `summaryCard`
- `systemEvent`
- `diffCard`
- `customWidget`

Each item must have:

- stable `id`
- `kind`
- semantic payload
- revision
- timestamp if needed

Each item kind should have its own layout/render adapter instead of being forced through a generic fallback message conversion.

## Rendering Contract

Each timeline item kind should implement the same internal contract:

1. Prepare layout input
2. Produce estimated layout output
3. Produce exact layout output
4. Produce render fragments from prepared layout
5. Produce hit regions and interaction metadata

A useful mental model is:

- core decides what items exist
- layout decides how much space they need
- render decides what visual fragments they emit
- host decides how the viewport displays and interacts with them

## Animation Contract

Animation stability is a first-class requirement.

The system must animate by stable item identity, never by list index.

### Required Transition Types

- insert
- remove
- expand
- collapse
- stream-grow
- estimated-to-exact correction

### Rules

1. Every update must preserve one anchor item in screen space when possible.
2. Tail appends while pinned should animate the inserted item locally, not cause double viewport + layout motion.
3. Changes fully above the viewport should compensate scroll by height delta.
4. Changes intersecting the viewport should animate geometry in place.
5. Estimated-to-exact corrections should be subtle and damped.
6. Only the visible window plus a bounded pad may participate in animated snapshots.
7. Offscreen content should snap to final layout.

### Dedicated Coordinator

Introduce a `TimelineTransitionCoordinator` responsible for:

- selecting anchors
- choosing transition kind
- producing start and end snapshots
- suppressing conflicting viewport motion
- unifying insert / expand / correction behavior

This logic should not remain spread across the host view.

## Caching and Preparation

The current cache direction is good and should be preserved conceptually.

Target cache families:

- prepared item layout cache
- rendered fragment cache
- visible content window cache
- selection window cache
- image metadata cache

Changes required:

- move cache ownership behind layout/render services
- make cache invalidation keyed by item revision and width bucket
- keep resident full layouts bounded
- allow background preparation without forcing visible render immediately

## macOS Host Rules

macOS is the primary target.

That does not change the architectural requirement for a thin host boundary.

The AppKit host should be responsible for:

- scroll position
- event translation
- cursor and hover state
- clipboard and selection bridges
- display link timing
- viewport invalidation scheduling

The AppKit host should not be responsible for:

- item-specific layout rules
- markdown preparation
- scene construction policy
- broad cache design

## Public API Direction

The current timeline public surface is too tied to concrete presentation details.

During the rework:

1. keep existing public API working where practical during transition
2. gradually shift toward smaller token groups
3. avoid exposing renderer implementation details as public options

Recommended token groups:

- content theme tokens
- spacing tokens
- bubble tokens
- metadata tokens
- motion tokens

## Migration Plan

### Phase 1: Boundary Definition

- land this spec
- add a short implementation map to code review expectations
- identify current files by future layer ownership
- add tests around anchors, expand/collapse, and visible-window stability

### Phase 2: Item Model Split

- introduce first-class timeline item model
- remove dependence on generic custom-entry-to-message fallback
- add per-kind item adapters

### Phase 3: Layout Extraction

- extract layout preparation from the controller
- create a dedicated layout service
- preserve current estimated/exact behavior while moving ownership

### Phase 4: Render Extraction

- extract per-item renderers
- convert output to render fragments
- keep chrome/content separation
- reduce monolithic renderer responsibilities

### Phase 5: Transition Extraction

- introduce `TimelineTransitionCoordinator`
- move animation decision logic out of the host view
- standardize insert / expand / correction motion rules

### Phase 6: Host Thinning

- keep AppKit host
- move non-host logic out of `NSView` code
- leave the host as viewport, event, and timing glue only

### Phase 7: Paging and Retention

- add transcript windowing hooks
- define cold-history loading shape
- keep large histories bounded without changing visible behavior

## Success Criteria

The rework is successful when all of the following are true:

1. Adding a new timeline item kind does not require editing a single monolithic renderer.
2. Streaming, append, expand, and collapse operations remain visually stable.
3. Exact layout is not required during active user scrolling.
4. The AppKit host can be reasoned about as a thin viewport/input layer.
5. Core item, layout, and render logic can be tested without `NSView`.
6. `VVMetalPrimitives` remains free of timeline-specific semantics.
7. Large transcripts can be retained and paged without redesigning the entire stack.

## Immediate Next Steps

1. Introduce internal layer names in code comments and review language.
2. Define the first internal timeline item protocol and prepared layout protocol.
3. Extract transition coordination into a dedicated type before adding more animation behaviors.
4. Extract layout preparation ownership from `VVChatTimelineController`.
5. Stop expanding the public style surface until the internal split is complete.
