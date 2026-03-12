# VVChatTimeline Performance Guide

Hard-won findings from profiling VVChatTimeline under sustained streaming load (90+ turns, 0.02s chunk delay). Check these areas first when investigating performance regressions.

## Memory

### What RSS actually is (and isn't)

- Application heap (malloc) is typically 30-45 MB under load. Caches are LRU-bounded.
- RSS includes IOSurface (Metal drawables/compositing), CoreText internal caches, mapped frameworks. These dominate and are not directly controllable.
- `vmmap --summary <pid>` and `footprint <pid>` are the best tools. `heap` freezes the process.

### Metal drawable memory

- Each MTKView drawable is ~12 MB at retina. Set `maximumDrawableCount = 2` (not default 3) on CAMetalLayer.
- `stopDisplayLink()` must set `displayLink = nil` to release the CVDisplayLink object and terminate its thread. Just calling `CVDisplayLinkStop()` leaks the thread.

### Cache budget defaults (VVChatTimelineStyle)

- `renderedCacheLimit`: 24 (not 50). Scene/selection caches scale from this.
- `sceneWindowCountLimit`: 48 (not 4x rendered). `selectionWindowCountLimit`: 24 (not 3x).
- These are the biggest memory consumers after Metal. Tune via `VVChatTimelineCacheBudget`.

### CoreText memory

- Each `CTLineCreateWithAttributedString` call creates objects CoreText caches permanently.
- Reducing layout/parse count is the only lever. Wrap `layout()` and `relayout()` in `autoreleasepool` to release temporaries sooner.
- `imageSizes` dictionary in `VVChatMessageRenderer` never evicts — bounded by unique URLs but worth watching.

## CPU

### Top hotspots during streaming (ranked by sample count)

1. **Metal drawable wait** (~18%) — `nextDrawable` blocks when rendering faster than vsync. Normal with `maximumDrawableCount = 2`.
2. **Scene primitive rendering** (~28%) — glyph batching, Metal buffer creation. The hot path. Buffer pool reuse helps (`VVMetalContext.makeBuffer`).
3. **`touchPreparedTextRun`** — Was O(n) array scan per cached text run access. Fixed: use generation counter + dictionary for O(1) touch.
4. **`syncPublicState`** — Was re-mapping 3 arrays (`entries`, `messages`, `itemModels`) on every draft update. Fixed: pre-compute in `makeSnapshot`.
5. **`summaryFileIconURL`** (playground) — Was doing `NSWorkspace.icon(for:)` + TIFF encoding on main thread per file per turn. Fixed: cache by file extension, lazy load on miss.

### Draft streaming layout

- `draftRebuild` count should be ~2/turn (one per streaming phase, initial build only).
- If higher, check `updateDraftPreparedState` — full rebuild triggers when `content.hasPrefix(state.content)` fails or `previousPrepared.layout == nil`.
- `relayout` with `commonPrefixCount == 0` still uses incremental path (starts from block 0) — don't gate on `commonPrefixCount > 0`.

### Async method isolation

- `VVChatMessageRenderer` is NOT `@MainActor`. All `async` methods (`prepareMarkdownContentIfNeeded`, `prepareVisibleSceneArtifactsIfNeeded`, `prepareVisibleSelectionArtifactsIfNeeded`) must wrap pre-await shared state reads AND post-await cache writes in `MainActor.run {}`. Missing this causes data race crashes (`EXC_BAD_ACCESS` in `Dictionary._Variant` or `MarkdownLayoutEngine`).

## Animation

### Layout transitions

- When viewport is following (pinned to bottom), inserted items should appear at target position immediately — no accordion Y-offset. This avoids bounce on short items (tool calls, summaries).
- `freezeSharedItemGeometry` handles shared items; insertion animation is controlled in `makeLayoutAnimationPlan`.
- `isApplyingUpdate` flag gates `handleScroll()` during `apply()` to prevent intermediate renders.
- Opacity/scale in `VVLayoutAnimationSnapshot` are computed by the animator but NOT rendered — only `frame` and `contentOffset` are read by `renderItem(at:)`.

### Per-item exact layout

- `replaceEntries` with mixed draft/non-draft items: each item should be measured based on its own state (`item.message.state != .draft`), not a batch-level flag. Otherwise non-draft items (user messages) get estimated layout with wrong contentOffset (left-aligned bubble).

## Diagnostic Tools (Playground)

The playground sidebar has built-in profiling:

- **Copy Memory Snapshot** — full cache breakdown with hit/miss/eviction stats, malloc zone info
- **Copy Memory Log** — per-turn TSV table (RSS, malloc, cache counts, cumulative counters)
- **Copy heap/vmmap/footprint** — shell out to system profiling tools
- **PID display** — for manual `sample <pid>` or Instruments attachment

## Key Files

| Area | File | What to look at |
|------|------|-----------------|
| Cache budgets | `VVChatTimelineStyle.swift` | `VVChatTimelineCacheBudget`, cache limits |
| LRU caches | `VVChatMessageRenderer.swift` | `LRUCache`, `trimCaches`, cost functions |
| Layout engine | `VVChatTimelineLayoutEngine.swift` | BIT/Fenwick tree, `visibleLayoutRange` |
| Render snapshot | `VVChatTimelineRenderSnapshot.swift` | `imageURLsByIndex`, incremental refresh |
| Metal rendering | `VVChatTimelineMetalView.swift` | `draw()`, drawable config, scene rendering |
| Scene primitives | `MarkdownScenePrimitiveRenderer.swift` | Text run cache, glyph batching |
| Transition anim | `VVChatTimelineTransitionCoordinator.swift` | `makeLayoutAnimationPlan`, insertion behavior |
| View orchestrator | `VVChatTimelineView.swift` | `apply()`, display link, scroll handling |
| Draft streaming | `VVChatMessageRenderer.swift` | `updateDraftPreparedState`, incremental relayout |
| Metal context | `VVMetalContext.swift` | Buffer pool, atlas cache, shader pipelines |
