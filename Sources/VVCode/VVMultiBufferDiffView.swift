import AppKit
import Foundation
import SwiftUI
import VVHighlighting

/// Input file pair for a multi-buffer diff projection.
@MainActor
public struct VVMultiDiffEntry: Identifiable {
    public let id: String
    public let path: String
    public let oldDocument: VVDocument
    public let newDocument: VVDocument
    public let language: VVLanguage?
    public let unifiedDiff: String

    public init(
        id: String = UUID().uuidString,
        path: String,
        oldDocument: VVDocument,
        newDocument: VVDocument,
        language: VVLanguage? = nil,
        unifiedDiff: String
    ) {
        self.id = id
        self.path = path
        self.oldDocument = oldDocument
        self.newDocument = newDocument
        self.language = language
        self.unifiedDiff = unifiedDiff
    }
}

public struct VVMultiDiffFoldRange: Hashable {
    public let id: String
    public let startLine: Int
    public let endLine: Int

    public init(id: String, startLine: Int, endLine: Int) {
        self.id = id
        self.startLine = startLine
        self.endLine = endLine
    }
}

public struct VVMultiDiffHighlightSegment: Hashable {
    public let range: NSRange
    public let language: VVLanguage?

    public init(range: NSRange, language: VVLanguage?) {
        self.range = range
        self.language = language
    }
}

public struct VVMultiDiffVisualHunk: Hashable, Identifiable {
    public enum ChangeType: Hashable {
        case added
        case modified
        case deleted
    }

    public let id: String
    public let entryID: String
    public let path: String
    public let startLine: Int
    public let endLine: Int
    public let changeType: ChangeType
    public let addedLineCount: Int
    public let deletedLineCount: Int

    public init(
        id: String,
        entryID: String,
        path: String,
        startLine: Int,
        endLine: Int,
        changeType: ChangeType,
        addedLineCount: Int,
        deletedLineCount: Int
    ) {
        self.id = id
        self.entryID = entryID
        self.path = path
        self.startLine = startLine
        self.endLine = endLine
        self.changeType = changeType
        self.addedLineCount = addedLineCount
        self.deletedLineCount = deletedLineCount
    }
}

public struct VVMultiDiffFileSummary: Hashable, Identifiable {
    public let id: String
    public let path: String
    public let startLine: Int
    public let hunkCount: Int
    public let addedLineCount: Int
    public let deletedLineCount: Int

    public init(
        id: String,
        path: String,
        startLine: Int,
        hunkCount: Int,
        addedLineCount: Int,
        deletedLineCount: Int
    ) {
        self.id = id
        self.path = path
        self.startLine = startLine
        self.hunkCount = hunkCount
        self.addedLineCount = addedLineCount
        self.deletedLineCount = deletedLineCount
    }
}

public struct VVMultiDiffRenderWindow: Hashable {
    public var isEnabled: Bool
    public var hunkBuffer: Int
    public var minimumTotalHunks: Int

    public init(
        isEnabled: Bool = false,
        hunkBuffer: Int = 18,
        minimumTotalHunks: Int = 64
    ) {
        self.isEnabled = isEnabled
        self.hunkBuffer = max(0, hunkBuffer)
        self.minimumTotalHunks = max(1, minimumTotalHunks)
    }

    public static let disabled = VVMultiDiffRenderWindow(isEnabled: false)
    public static let `default` = VVMultiDiffRenderWindow(isEnabled: true, hunkBuffer: 18, minimumTotalHunks: 64)
}

public struct VVMultiDiffRenderWindowState: Hashable {
    public let isActive: Bool
    public let totalHunkCount: Int
    public let visibleHunkCount: Int
    public let anchorHunkID: String?

    public init(
        isActive: Bool,
        totalHunkCount: Int,
        visibleHunkCount: Int,
        anchorHunkID: String?
    ) {
        self.isActive = isActive
        self.totalHunkCount = totalHunkCount
        self.visibleHunkCount = visibleHunkCount
        self.anchorHunkID = anchorHunkID
    }
}

public enum VVMultiDiffHunkAction: Hashable {
    case comment
    case copy
    case toggleFold
}

public struct VVMultiDiffPresentation {
    public let text: String
    public let foldRanges: [VVMultiDiffFoldRange]
    public let foldedStartLines: Set<Int>
    public let highlightSegments: [VVMultiDiffHighlightSegment]
    public let visualHunks: [VVMultiDiffVisualHunk]
    public let fileSummaries: [VVMultiDiffFileSummary]
    public let renderWindowState: VVMultiDiffRenderWindowState
    public let revision: Int

    public init(
        text: String,
        foldRanges: [VVMultiDiffFoldRange],
        foldedStartLines: Set<Int>,
        highlightSegments: [VVMultiDiffHighlightSegment],
        visualHunks: [VVMultiDiffVisualHunk],
        fileSummaries: [VVMultiDiffFileSummary],
        renderWindowState: VVMultiDiffRenderWindowState,
        revision: Int
    ) {
        self.text = text
        self.foldRanges = foldRanges
        self.foldedStartLines = foldedStartLines
        self.highlightSegments = highlightSegments
        self.visualHunks = visualHunks
        self.fileSummaries = fileSummaries
        self.renderWindowState = renderWindowState
        self.revision = revision
    }
}

@MainActor
private struct VVMultiDiffEditableSegment {
    let entryID: String
    let language: VVLanguage?
    let foldID: String
    var streamRange: NSRange
    var sourceRange: NSRange
}

@MainActor
private struct VVMultiDiffProjection {
    var text: String
    var segments: [VVMultiDiffEditableSegment]
    var foldRanges: [VVMultiDiffFoldRange]
    var foldedStartLines: Set<Int>
    var visualHunks: [VVMultiDiffVisualHunk]
    var fileSummaries: [VVMultiDiffFileSummary]
    var renderWindowState: VVMultiDiffRenderWindowState
}

private struct VVMultiDiffExcerptDescriptor {
    var range: ClosedRange<Int>
    var changeType: VVDiffHunk.ChangeType
    var addedLineCount: Int
    var deletedLineCount: Int
}

private struct VVMultiDiffPendingVisualHunk {
    let id: String
    let entryID: String
    let path: String
    let changeType: VVDiffHunk.ChangeType
    let addedLineCount: Int
    let deletedLineCount: Int
}

private struct VVMultiDiffPendingFileSummary {
    let id: String
    let path: String
    let startOffset: Int
    let hunkCount: Int
    let addedLineCount: Int
    let deletedLineCount: Int
}

private struct VVMultiDiffRenderPlan {
    let allowedHunkIDs: Set<String>?
    let isWindowed: Bool
    let anchorHunkID: String?
}

/// Native multi-buffer diff document that projects many file hunks into one editable stream.
@MainActor
public final class VVMultiDiffDocument: ObservableObject {
    @Published public private(set) var entries: [VVMultiDiffEntry]
    @Published public var projectDocument: VVDocument
    @Published public private(set) var presentationRevision: Int = 0

    public var contextLines: Int {
        didSet {
            contextLines = max(0, contextLines)
            rebuildProjection()
        }
    }

    public var renderWindow: VVMultiDiffRenderWindow {
        didSet {
            renderWindow.hunkBuffer = max(0, renderWindow.hunkBuffer)
            renderWindow.minimumTotalHunks = max(1, renderWindow.minimumTotalHunks)
            if oldValue != renderWindow {
                rebuildProjection()
            }
        }
    }

    private var projection: VVMultiDiffProjection
    private var collapsedFoldIDs: Set<String> = []
    private var isApplyingProgrammaticText = false
    private var renderAnchorHunkID: String?

    public init(entries: [VVMultiDiffEntry] = [], contextLines: Int = 3) {
        self.entries = entries
        self.contextLines = max(0, contextLines)
        self.renderWindow = .default
        self.projectDocument = VVDocument(text: "", language: .diff)
        self.projection = VVMultiDiffProjection(
            text: "",
            segments: [],
            foldRanges: [],
            foldedStartLines: [],
            visualHunks: [],
            fileSummaries: [],
            renderWindowState: VVMultiDiffRenderWindowState(
                isActive: false,
                totalHunkCount: 0,
                visibleHunkCount: 0,
                anchorHunkID: nil
            )
        )
        rebuildProjection()
    }

    public func setEntries(_ entries: [VVMultiDiffEntry], contextLines: Int? = nil) {
        self.entries = entries
        if let contextLines {
            self.contextLines = max(0, contextLines)
        } else {
            rebuildProjection()
        }
    }

    public func setRenderWindow(_ configuration: VVMultiDiffRenderWindow) {
        renderWindow = configuration
    }

    public func updateRenderAnchor(forVisibleLineRange range: ClosedRange<Int>) {
        guard renderWindow.isEnabled else { return }
        guard !projection.visualHunks.isEmpty else { return }

        let centerLine = range.lowerBound + (range.upperBound - range.lowerBound) / 2
        var nearest: (id: String, distance: Int)?

        for hunk in projection.visualHunks {
            let distance: Int
            if centerLine < hunk.startLine {
                distance = hunk.startLine - centerLine
            } else if centerLine > hunk.endLine {
                distance = centerLine - hunk.endLine
            } else {
                distance = 0
            }

            if let current = nearest {
                if distance < current.distance {
                    nearest = (hunk.id, distance)
                }
            } else {
                nearest = (hunk.id, distance)
            }
        }

        guard let nearestID = nearest?.id else { return }
        guard nearestID != renderAnchorHunkID else { return }

        renderAnchorHunkID = nearestID
        rebuildProjection()
    }

    public func rebuildProjection() {
        var stream = ""
        var segments: [VVMultiDiffEditableSegment] = []
        var pendingFolds: [(id: String, startOffset: Int, endOffset: Int)] = []
        var pendingVisualHunks: [VVMultiDiffPendingVisualHunk] = []
        var pendingFileSummaries: [VVMultiDiffPendingFileSummary] = []
        var offset = 0

        let estimatedUTF16 = entries.reduce(into: 0) { partialResult, entry in
            let textLength = entry.newDocument.text.utf16.count
            partialResult += min(textLength, 20_000) + 192
        }
        if estimatedUTF16 > 0 {
            stream.reserveCapacity(estimatedUTF16)
        }

        func append(_ chunk: String) {
            stream.append(chunk)
            offset += chunk.utf16.count
        }

        let descriptorsByEntryID: [String: [VVMultiDiffExcerptDescriptor]] = Dictionary(
            uniqueKeysWithValues: entries.map { entry in
                let text = entry.newDocument.text
                let starts = Self.lineStartOffsets(in: text)
                let lineCount = max(1, starts.count - 1)
                let descriptors = Self.excerptDescriptors(
                    from: entry.unifiedDiff,
                    totalLines: lineCount,
                    contextLines: contextLines
                )
                return (entry.id, descriptors)
            }
        )
        let allHunkIDs: [String] = entries.flatMap { entry in
            let descriptors = descriptorsByEntryID[entry.id] ?? []
            return descriptors.indices.map { "\(entry.id)#\($0)" }
        }

        let renderPlan = makeRenderPlan(allHunkIDs: allHunkIDs)
        let allowedHunkIDs = renderPlan.allowedHunkIDs
        let reserveCount = max(16, allHunkIDs.count)
        segments.reserveCapacity(reserveCount)
        pendingFolds.reserveCapacity(reserveCount)
        pendingVisualHunks.reserveCapacity(reserveCount)
        pendingFileSummaries.reserveCapacity(entries.count)

        var appendedEntryCount = 0

        for entry in entries {
            let descriptors = descriptorsByEntryID[entry.id] ?? []
            if descriptors.isEmpty {
                continue
            }

            var fileStartOffset = offset
            var appendedEntry = false

            let text = entry.newDocument.text
            let starts = Self.lineStartOffsets(in: text)
            let nsText = text as NSString

            var entryAdded = 0
            var entryDeleted = 0
            var skippedHunks = 0
            var visibleHunkCount = 0

            for (hunkIndex, descriptor) in descriptors.enumerated() {
                let range = descriptor.range
                let foldID = "\(entry.id)#\(hunkIndex)"
                let shouldInclude = allowedHunkIDs?.contains(foldID) ?? true
                guard shouldInclude else {
                    skippedHunks += 1
                    continue
                }

                if !appendedEntry {
                    if appendedEntryCount > 0 {
                        append("\n")
                    }
                    fileStartOffset = offset
                    append("diff -- \(entry.path)\n")
                    appendedEntry = true
                    appendedEntryCount += 1
                }

                if skippedHunks > 0 {
                    append("... [\(skippedHunks) hunks elided] ...\n")
                    skippedHunks = 0
                }

                let hunkStartOffset = offset

                append("@@ \(range.lowerBound),\(range.count) @@\n")

                let sourceStart = starts[range.lowerBound - 1]
                let sourceEnd = starts[range.upperBound]
                let sourceRange = NSRange(location: sourceStart, length: max(0, sourceEnd - sourceStart))
                let excerptText = nsText.substring(with: sourceRange)
                let streamRange = NSRange(location: offset, length: excerptText.utf16.count)

                segments.append(
                    VVMultiDiffEditableSegment(
                        entryID: entry.id,
                        language: entry.language,
                        foldID: foldID,
                        streamRange: streamRange,
                        sourceRange: sourceRange
                    )
                )

                append(excerptText)
                if !excerptText.hasSuffix("\n") {
                    append("\n")
                }

                pendingFolds.append((id: foldID, startOffset: hunkStartOffset, endOffset: offset))
                pendingVisualHunks.append(
                    VVMultiDiffPendingVisualHunk(
                        id: foldID,
                        entryID: entry.id,
                        path: entry.path,
                        changeType: descriptor.changeType,
                        addedLineCount: descriptor.addedLineCount,
                        deletedLineCount: descriptor.deletedLineCount
                    )
                )
                entryAdded += descriptor.addedLineCount
                entryDeleted += descriptor.deletedLineCount
                visibleHunkCount += 1

                if hunkIndex < descriptors.count - 1 && (allowedHunkIDs?.contains("\(entry.id)#\(hunkIndex + 1)") ?? true) {
                    append("...\n")
                }
            }

            guard appendedEntry else {
                continue
            }

            if skippedHunks > 0 {
                append("... [\(skippedHunks) hunks elided] ...\n")
            }

            pendingFileSummaries.append(
                VVMultiDiffPendingFileSummary(
                    id: entry.id,
                    path: entry.path,
                    startOffset: fileStartOffset,
                    hunkCount: visibleHunkCount,
                    addedLineCount: entryAdded,
                    deletedLineCount: entryDeleted
                )
            )
        }

        let foldRanges = Self.makeFoldRanges(from: pendingFolds, text: stream)
        let foldedStartLines = foldedStarts(for: foldRanges)
        let foldRangesByID = Dictionary(uniqueKeysWithValues: foldRanges.map { ($0.id, $0) })
        let lineStarts = Self.lineStartOffsets(in: stream)
        let visualHunks = pendingVisualHunks.compactMap { pending -> VVMultiDiffVisualHunk? in
            guard let foldRange = foldRangesByID[pending.id] else {
                return nil
            }

            return VVMultiDiffVisualHunk(
                id: pending.id,
                entryID: pending.entryID,
                path: pending.path,
                startLine: foldRange.startLine,
                endLine: foldRange.endLine,
                changeType: Self.visualChangeType(from: pending.changeType),
                addedLineCount: pending.addedLineCount,
                deletedLineCount: pending.deletedLineCount
            )
        }
        let fileSummaries = pendingFileSummaries.map { pending in
            VVMultiDiffFileSummary(
                id: pending.id,
                path: pending.path,
                startLine: Self.lineIndex(forUTF16Offset: pending.startOffset, lineStarts: lineStarts),
                hunkCount: pending.hunkCount,
                addedLineCount: pending.addedLineCount,
                deletedLineCount: pending.deletedLineCount
            )
        }

        projection = VVMultiDiffProjection(
            text: stream,
            segments: segments,
            foldRanges: foldRanges,
            foldedStartLines: foldedStartLines,
            visualHunks: visualHunks,
            fileSummaries: fileSummaries,
            renderWindowState: VVMultiDiffRenderWindowState(
                isActive: renderPlan.isWindowed,
                totalHunkCount: allHunkIDs.count,
                visibleHunkCount: visualHunks.count,
                anchorHunkID: renderPlan.anchorHunkID
            )
        )
        applyProgrammaticProjectedText(stream)
        presentationRevision &+= 1
    }

    /// Apply user edits from the projected stream back into the underlying file buffer.
    public func handleProjectedTextChange(_ newText: String) {
        guard !isApplyingProgrammaticText else { return }
        guard newText != projection.text else { return }

        guard let edit = Self.computeSingleEdit(old: projection.text, new: newText),
              let segmentIndex = segmentIndex(containing: edit.oldRange),
              let entryIndex = entries.firstIndex(where: { $0.id == projection.segments[segmentIndex].entryID }),
              let sourceEditRange = sourceRange(for: edit.oldRange, in: projection.segments[segmentIndex]) else {
            applyProgrammaticProjectedText(projection.text)
            return
        }

        var updatedSource = entries[entryIndex].newDocument.text
        let oldSourceSlice = (updatedSource as NSString).substring(with: sourceEditRange)
        guard let sourceSwiftRange = Self.swiftRange(in: updatedSource, nsRange: sourceEditRange) else {
            applyProgrammaticProjectedText(projection.text)
            return
        }

        updatedSource.replaceSubrange(sourceSwiftRange, with: edit.replacement)
        entries[entryIndex].newDocument.text = updatedSource

        let sourceOldLength = sourceEditRange.length
        let replacementLength = (edit.replacement as NSString).length
        let delta = replacementLength - sourceOldLength
        let lineDelta = Self.newlineCount(in: edit.replacement) - Self.newlineCount(in: oldSourceSlice)

        projection.text = newText
        applyProgrammaticProjectedText(newText)

        patchSegmentsAfterEdit(
            segmentIndex: segmentIndex,
            entryID: entries[entryIndex].id,
            sourceEditRange: sourceEditRange,
            delta: delta
        )

        if lineDelta != 0 {
            patchFoldRangesAfterEdit(
                foldID: projection.segments[segmentIndex].foldID,
                lineDelta: lineDelta
            )
            patchFileSummariesAfterEdit(
                editedEntryID: entries[entryIndex].id,
                lineDelta: lineDelta
            )
        }

        refreshVisualHunkLineRanges()
        projection.foldedStartLines = foldedStarts(for: projection.foldRanges)
        presentationRevision &+= 1
    }

    public func toggleFold(atLine line: Int) {
        guard let fold = projection.foldRanges.first(where: { $0.startLine == line }) else {
            return
        }

        if collapsedFoldIDs.contains(fold.id) {
            collapsedFoldIDs.remove(fold.id)
        } else {
            collapsedFoldIDs.insert(fold.id)
        }

        projection.foldedStartLines = foldedStarts(for: projection.foldRanges)
        presentationRevision &+= 1
    }

    public func presentation() -> VVMultiDiffPresentation {
        VVMultiDiffPresentation(
            text: projection.text,
            foldRanges: projection.foldRanges,
            foldedStartLines: projection.foldedStartLines,
            highlightSegments: projection.segments.map { segment in
                VVMultiDiffHighlightSegment(range: segment.streamRange, language: segment.language)
            },
            visualHunks: projection.visualHunks,
            fileSummaries: projection.fileSummaries,
            renderWindowState: projection.renderWindowState,
            revision: presentationRevision
        )
    }

    private func applyProgrammaticProjectedText(_ text: String) {
        isApplyingProgrammaticText = true
        projectDocument.text = text
        isApplyingProgrammaticText = false
    }

    private func foldedStarts(for foldRanges: [VVMultiDiffFoldRange]) -> Set<Int> {
        Set(
            foldRanges
                .filter { collapsedFoldIDs.contains($0.id) }
                .map(\.startLine)
        )
    }

    private func makeRenderPlan(allHunkIDs: [String]) -> VVMultiDiffRenderPlan {
        if allHunkIDs.isEmpty {
            renderAnchorHunkID = nil
            return VVMultiDiffRenderPlan(
                allowedHunkIDs: nil,
                isWindowed: false,
                anchorHunkID: nil
            )
        }

        guard renderWindow.isEnabled else {
            return VVMultiDiffRenderPlan(
                allowedHunkIDs: nil,
                isWindowed: false,
                anchorHunkID: nil
            )
        }
        guard allHunkIDs.count > renderWindow.minimumTotalHunks else {
            return VVMultiDiffRenderPlan(
                allowedHunkIDs: nil,
                isWindowed: false,
                anchorHunkID: nil
            )
        }

        let anchorID: String
        if let existingAnchor = renderAnchorHunkID,
           allHunkIDs.contains(existingAnchor) {
            anchorID = existingAnchor
        } else if let first = allHunkIDs.first {
            anchorID = first
            renderAnchorHunkID = first
        } else {
            return VVMultiDiffRenderPlan(
                allowedHunkIDs: nil,
                isWindowed: false,
                anchorHunkID: nil
            )
        }

        guard let anchorIndex = allHunkIDs.firstIndex(of: anchorID) else {
            return VVMultiDiffRenderPlan(
                allowedHunkIDs: nil,
                isWindowed: false,
                anchorHunkID: nil
            )
        }

        let start = max(0, anchorIndex - renderWindow.hunkBuffer)
        let end = min(allHunkIDs.count - 1, anchorIndex + renderWindow.hunkBuffer)
        let allowed = Set(allHunkIDs[start...end])
        return VVMultiDiffRenderPlan(
            allowedHunkIDs: allowed,
            isWindowed: true,
            anchorHunkID: anchorID
        )
    }

    private func segmentIndex(containing streamRange: NSRange) -> Int? {
        if streamRange.length == 0 {
            for index in projection.segments.indices {
                let segment = projection.segments[index]
                let start = segment.streamRange.location
                let end = segment.streamRange.location + segment.streamRange.length
                if streamRange.location >= start && streamRange.location <= end {
                    return index
                }
            }
            return nil
        }

        for index in projection.segments.indices {
            let intersection = NSIntersectionRange(projection.segments[index].streamRange, streamRange)
            if intersection.length > 0 {
                return index
            }
        }
        return nil
    }

    private func sourceRange(for streamRange: NSRange, in segment: VVMultiDiffEditableSegment) -> NSRange? {
        let segmentStart = segment.streamRange.location
        let segmentEnd = segmentStart + segment.streamRange.length
        let editStart = streamRange.location
        let editEnd = streamRange.location + streamRange.length

        guard editStart >= segmentStart, editEnd <= segmentEnd else {
            return nil
        }

        let startDelta = editStart - segmentStart
        let endDelta = editEnd - segmentStart
        let sourceStart = segment.sourceRange.location + startDelta
        let sourceEnd = segment.sourceRange.location + endDelta
        return NSRange(location: sourceStart, length: max(0, sourceEnd - sourceStart))
    }

    private func patchSegmentsAfterEdit(
        segmentIndex: Int,
        entryID: String,
        sourceEditRange: NSRange,
        delta: Int
    ) {
        guard delta != 0 else { return }

        let sourceEditEndBeforePatch = sourceEditRange.location + sourceEditRange.length
        for index in projection.segments.indices {
            if index == segmentIndex {
                projection.segments[index].streamRange.length += delta
                projection.segments[index].sourceRange.length += delta
            } else if index > segmentIndex {
                projection.segments[index].streamRange.location += delta
            }

            guard projection.segments[index].entryID == entryID, index != segmentIndex else {
                continue
            }

            if projection.segments[index].sourceRange.location >= sourceEditEndBeforePatch {
                projection.segments[index].sourceRange.location += delta
            }
        }
    }

    private func patchFoldRangesAfterEdit(foldID: String, lineDelta: Int) {
        guard lineDelta != 0 else { return }
        guard let editedIndex = projection.foldRanges.firstIndex(where: { $0.id == foldID }) else {
            return
        }

        let editedRange = projection.foldRanges[editedIndex]
        var updated = projection.foldRanges

        for index in updated.indices {
            var range = updated[index]
            if range.id == foldID {
                range = VVMultiDiffFoldRange(
                    id: range.id,
                    startLine: range.startLine,
                    endLine: max(range.startLine, range.endLine + lineDelta)
                )
            } else if range.startLine > editedRange.endLine {
                range = VVMultiDiffFoldRange(
                    id: range.id,
                    startLine: range.startLine + lineDelta,
                    endLine: range.endLine + lineDelta
                )
            }
            updated[index] = range
        }

        projection.foldRanges = updated
    }

    private func refreshVisualHunkLineRanges() {
        let foldRangesByID = Dictionary(uniqueKeysWithValues: projection.foldRanges.map { ($0.id, $0) })
        projection.visualHunks = projection.visualHunks.map { hunk in
            guard let range = foldRangesByID[hunk.id] else {
                return hunk
            }

            return VVMultiDiffVisualHunk(
                id: hunk.id,
                entryID: hunk.entryID,
                path: hunk.path,
                startLine: range.startLine,
                endLine: range.endLine,
                changeType: hunk.changeType,
                addedLineCount: hunk.addedLineCount,
                deletedLineCount: hunk.deletedLineCount
            )
        }
    }

    private func patchFileSummariesAfterEdit(editedEntryID: String, lineDelta: Int) {
        guard lineDelta != 0 else { return }
        guard let editedSummary = projection.fileSummaries.first(where: { $0.id == editedEntryID }) else {
            return
        }

        projection.fileSummaries = projection.fileSummaries.map { summary in
            guard summary.startLine > editedSummary.startLine else {
                return summary
            }

            return VVMultiDiffFileSummary(
                id: summary.id,
                path: summary.path,
                startLine: max(0, summary.startLine + lineDelta),
                hunkCount: summary.hunkCount,
                addedLineCount: summary.addedLineCount,
                deletedLineCount: summary.deletedLineCount
            )
        }
    }

    private static func computeSingleEdit(old: String, new: String) -> (oldRange: NSRange, replacement: String)? {
        let oldNSString = old as NSString
        let newNSString = new as NSString

        let oldLength = oldNSString.length
        let newLength = newNSString.length
        let sharedPrefixLimit = min(oldLength, newLength)

        var prefix = 0
        while prefix < sharedPrefixLimit &&
            oldNSString.character(at: prefix) == newNSString.character(at: prefix) {
            prefix += 1
        }

        if prefix == oldLength, prefix == newLength {
            return nil
        }

        var oldSuffix = oldLength
        var newSuffix = newLength
        while oldSuffix > prefix,
            newSuffix > prefix,
            oldNSString.character(at: oldSuffix - 1) == newNSString.character(at: newSuffix - 1) {
            oldSuffix -= 1
            newSuffix -= 1
        }

        let oldRange = NSRange(location: prefix, length: oldSuffix - prefix)
        let replacement = newNSString.substring(with: NSRange(location: prefix, length: newSuffix - prefix))
        return (oldRange, replacement)
    }

    private static func swiftRange(in text: String, nsRange: NSRange) -> Range<String.Index>? {
        let utf16Count = text.utf16.count
        let end = nsRange.location + nsRange.length
        guard nsRange.location >= 0, nsRange.length >= 0, end <= utf16Count else { return nil }
        let startIndex = String.Index(utf16Offset: nsRange.location, in: text)
        let endIndex = String.Index(utf16Offset: end, in: text)
        return startIndex..<endIndex
    }

    private static func lineStartOffsets(in text: String) -> [Int] {
        var offsets: [Int] = [0]
        var utf16Offset = 0

        for codeUnit in text.utf16 {
            utf16Offset += 1
            if codeUnit == 10 {
                offsets.append(utf16Offset)
            }
        }

        offsets.append(utf16Offset)
        return offsets
    }

    private static func lineIndex(forUTF16Offset offset: Int, lineStarts: [Int]) -> Int {
        guard !lineStarts.isEmpty else { return 0 }
        let clamped = max(0, min(offset, lineStarts.last ?? 0))

        var low = 0
        var high = max(0, lineStarts.count - 1)
        while low + 1 < high {
            let mid = (low + high) / 2
            if lineStarts[mid] <= clamped {
                low = mid
            } else {
                high = mid
            }
        }

        return max(0, low)
    }

    private static func makeFoldRanges(
        from pendingFolds: [(id: String, startOffset: Int, endOffset: Int)],
        text: String
    ) -> [VVMultiDiffFoldRange] {
        let lineStarts = lineStartOffsets(in: text)

        return pendingFolds.compactMap { pending in
            guard pending.endOffset > pending.startOffset else {
                return nil
            }

            let startLine = lineIndex(forUTF16Offset: pending.startOffset, lineStarts: lineStarts)
            let endLineOffset = max(pending.startOffset, pending.endOffset - 1)
            let endLine = lineIndex(forUTF16Offset: endLineOffset, lineStarts: lineStarts)

            return VVMultiDiffFoldRange(
                id: pending.id,
                startLine: startLine,
                endLine: max(startLine, endLine)
            )
        }
    }

    private static func newlineCount(in text: String) -> Int {
        text.utf16.reduce(into: 0) { partialResult, codeUnit in
            if codeUnit == 10 {
                partialResult += 1
            }
        }
    }

    private static func excerptDescriptors(
        from unifiedDiff: String,
        totalLines: Int,
        contextLines: Int
    ) -> [VVMultiDiffExcerptDescriptor] {
        let safeTotalLines = max(1, totalLines)
        let hunks = VVDiffParser.parse(unifiedDiff: unifiedDiff)
        guard !hunks.isEmpty else {
            let end = min(safeTotalLines, max(1, contextLines * 2 + 1))
            return [
                VVMultiDiffExcerptDescriptor(
                    range: 1...end,
                    changeType: .modified,
                    addedLineCount: 0,
                    deletedLineCount: 0
                )
            ]
        }

        var descriptors: [VVMultiDiffExcerptDescriptor] = []
        descriptors.reserveCapacity(hunks.count)

        for hunk in hunks {
            let newCount = max(1, hunk.newCount)
            let start = max(1, hunk.newStart - contextLines)
            let end = min(safeTotalLines, hunk.newStart + newCount - 1 + contextLines)
            guard start <= end else { continue }
            let addedCount = hunk.lines.reduce(into: 0) { result, line in
                if line.type == .added {
                    result += 1
                }
            }
            let deletedCount = hunk.lines.reduce(into: 0) { result, line in
                if line.type == .deleted {
                    result += 1
                }
            }

            descriptors.append(
                VVMultiDiffExcerptDescriptor(
                    range: start...end,
                    changeType: hunk.changeType,
                    addedLineCount: addedCount,
                    deletedLineCount: deletedCount
                )
            )
        }

        return mergeDescriptors(descriptors)
    }

    private static func mergeDescriptors(_ descriptors: [VVMultiDiffExcerptDescriptor]) -> [VVMultiDiffExcerptDescriptor] {
        let sorted = descriptors.sorted { lhs, rhs in
            if lhs.range.lowerBound == rhs.range.lowerBound {
                return lhs.range.upperBound < rhs.range.upperBound
            }
            return lhs.range.lowerBound < rhs.range.lowerBound
        }
        guard var current = sorted.first else { return [] }

        var merged: [VVMultiDiffExcerptDescriptor] = []
        for descriptor in sorted.dropFirst() {
            if descriptor.range.lowerBound <= current.range.upperBound + 1 {
                current = VVMultiDiffExcerptDescriptor(
                    range: current.range.lowerBound...max(current.range.upperBound, descriptor.range.upperBound),
                    changeType: mergeChangeTypes(current.changeType, descriptor.changeType),
                    addedLineCount: current.addedLineCount + descriptor.addedLineCount,
                    deletedLineCount: current.deletedLineCount + descriptor.deletedLineCount
                )
            } else {
                merged.append(current)
                current = descriptor
            }
        }
        merged.append(current)
        return merged
    }

    private static func mergeChangeTypes(_ lhs: VVDiffHunk.ChangeType, _ rhs: VVDiffHunk.ChangeType) -> VVDiffHunk.ChangeType {
        if lhs == rhs {
            return lhs
        }
        return .modified
    }

    private static func visualChangeType(from type: VVDiffHunk.ChangeType) -> VVMultiDiffVisualHunk.ChangeType {
        switch type {
        case .added:
            return .added
        case .modified:
            return .modified
        case .deleted:
            return .deleted
        }
    }
}

private final class VVMultiSegmentHighlighter {
    private var highlightersByLanguageID: [String: TreeSitterHighlighter] = [:]
    private var highlightTheme: HighlightTheme = .defaultDark
    private var usesDarkTheme = true

    func highlightRanges(
        text: String,
        segments: [VVMultiDiffHighlightSegment],
        theme: VVTheme
    ) async -> [ColoredRange] {
        let shouldUseDarkTheme = theme.backgroundColor.brightnessComponent < 0.5
        let desiredTheme: HighlightTheme = shouldUseDarkTheme
            ? .defaultDark
            : .defaultLight

        if shouldUseDarkTheme != usesDarkTheme {
            usesDarkTheme = shouldUseDarkTheme
            highlightTheme = desiredTheme
            for highlighter in highlightersByLanguageID.values {
                await highlighter.setTheme(desiredTheme)
            }
        }

        let nsText = text as NSString
        let textLength = nsText.length
        var result: [ColoredRange] = []

        for segment in segments {
            guard let language = segment.language else { continue }
            let range = segment.range
            guard range.location >= 0, range.length > 0, range.location + range.length <= textLength else {
                continue
            }

            let segmentText = nsText.substring(with: range)
            guard let highlighter = await highlighter(for: language) else {
                continue
            }

            do {
                _ = try await highlighter.parse(segmentText)
                let highlights = try await highlighter.highlights(in: nil)

                for highlight in highlights {
                    let absolute = NSRange(
                        location: range.location + highlight.range.location,
                        length: highlight.range.length
                    )
                    guard absolute.location >= range.location,
                          absolute.length > 0,
                          absolute.location + absolute.length <= range.location + range.length else {
                        continue
                    }

                    result.append(
                        ColoredRange(
                            range: absolute,
                            color: highlight.style.color.simdColor,
                            fontVariant: FontVariant(
                                bold: highlight.style.isBold,
                                italic: highlight.style.isItalic
                            )
                        )
                    )
                }
            } catch {
                continue
            }
        }

        result.sort { lhs, rhs in
            if lhs.range.location == rhs.range.location {
                return lhs.range.length < rhs.range.length
            }
            return lhs.range.location < rhs.range.location
        }
        return result
    }

    private func highlighter(for language: VVLanguage) async -> TreeSitterHighlighter? {
        if let cached = highlightersByLanguageID[language.identifier] {
            return cached
        }

        guard let config = LanguageRegistry.shared.language(for: language.identifier) else {
            return nil
        }

        let highlighter = TreeSitterHighlighter(theme: highlightTheme)
        do {
            try await highlighter.setLanguage(config)
            highlightersByLanguageID[language.identifier] = highlighter
            return highlighter
        } catch {
            return nil
        }
    }
}

private struct VVMultiBufferDiffRepresentable: NSViewRepresentable {
    @ObservedObject var document: VVMultiDiffDocument
    var theme: VVTheme
    var configuration: VVConfiguration
    var showsDiffOverlayCallouts: Bool
    var onDiffOverlayHover: ((String?) -> Void)?
    var onDiffOverlayAction: ((String, VVMultiDiffHunkAction) -> Void)?
    var onVisibleLineRange: ((ClosedRange<Int>) -> Void)?

    func makeNSView(context: Context) -> VVMetalEditorContainerView {
        let container = VVMetalEditorContainerView(
            frame: .zero,
            configuration: configuration,
            theme: theme
        )
        container.delegate = context.coordinator
        context.coordinator.view = container
        context.coordinator.document = document
        context.coordinator.onDiffOverlayHover = onDiffOverlayHover
        context.coordinator.onDiffOverlayAction = onDiffOverlayAction
        context.coordinator.onVisibleLineRange = onVisibleLineRange
        container.setShowsDiffOverlayHunks(showsDiffOverlayCallouts)

        let presentation = document.presentation()
        context.coordinator.isApplyingProgrammaticText = true
        container.setText(presentation.text, applyHighlighting: false)
        context.coordinator.isApplyingProgrammaticText = false
        container.setHighlighter(nil)

        container.metalTextView.onToggleFold = { [weak coordinator = context.coordinator] line in
            coordinator?.document.toggleFold(atLine: line)
        }
        if showsDiffOverlayCallouts {
            container.metalTextView.onDiffOverlayHover = { [weak coordinator = context.coordinator] hunkID in
                coordinator?.onDiffOverlayHover?(hunkID)
            }
            container.metalTextView.onDiffOverlayAction = { [weak coordinator = context.coordinator] hunkID, action in
                coordinator?.handleDiffOverlayAction(hunkID: hunkID, action: action)
            }
        } else {
            container.metalTextView.onDiffOverlayHover = nil
            container.metalTextView.onDiffOverlayAction = nil
        }
        container.onVisibleLineRangeChange = { [weak coordinator = context.coordinator] range in
            coordinator?.handleVisibleLineRange(range)
        }

        applyFolding(presentation, to: container)
        context.coordinator.scheduleHighlights(
            for: presentation,
            theme: theme,
            force: true
        )

        DispatchQueue.main.async {
            container.focusTextView()
        }

        return container
    }

    func updateNSView(_ nsView: VVMetalEditorContainerView, context: Context) {
        context.coordinator.document = document
        context.coordinator.onDiffOverlayHover = onDiffOverlayHover
        context.coordinator.onDiffOverlayAction = onDiffOverlayAction
        context.coordinator.onVisibleLineRange = onVisibleLineRange
        nsView.setTheme(theme)
        nsView.setConfiguration(configuration)
        nsView.setShowsDiffOverlayHunks(showsDiffOverlayCallouts)
        if showsDiffOverlayCallouts {
            nsView.metalTextView.onDiffOverlayHover = { [weak coordinator = context.coordinator] hunkID in
                coordinator?.onDiffOverlayHover?(hunkID)
            }
            nsView.metalTextView.onDiffOverlayAction = { [weak coordinator = context.coordinator] hunkID, action in
                coordinator?.handleDiffOverlayAction(hunkID: hunkID, action: action)
            }
        } else {
            nsView.metalTextView.onDiffOverlayHover = nil
            nsView.metalTextView.onDiffOverlayAction = nil
        }

        let presentation = document.presentation()
        if nsView.text != presentation.text {
            context.coordinator.isApplyingProgrammaticText = true
            nsView.setText(presentation.text, applyHighlighting: false)
            context.coordinator.isApplyingProgrammaticText = false
        }

        applyFolding(presentation, to: nsView)
        context.coordinator.scheduleHighlights(for: presentation, theme: theme)
    }

    func makeCoordinator() -> Coordinator {
        Coordinator(document: document)
    }

    private func applyFolding(_ presentation: VVMultiDiffPresentation, to view: VVMetalEditorContainerView) {
        let foldMarkers = presentation.foldRanges.map { range in
            MetalGutterFoldRange(startLine: range.startLine, endLine: range.endLine)
        }
        view.metalTextView.setFoldRanges(foldMarkers, foldedStartLines: presentation.foldedStartLines)

        let foldedRanges = presentation.foldRanges
            .filter { presentation.foldedStartLines.contains($0.startLine) }
            .map { $0.startLine...$0.endLine }
        view.metalTextView.setFoldedLineRanges(foldedRanges)

        let gitHunks = presentation.visualHunks.map { hunk in
            MetalGutterGitHunk(
                startLine: hunk.startLine,
                lineCount: max(1, hunk.endLine - hunk.startLine + 1),
                status: metalGutterStatus(from: hunk.changeType)
            )
        }
        view.setGitHunks(gitHunks)

        if showsDiffOverlayCallouts {
            let overlayHunks = presentation.visualHunks.map { hunk in
                MetalDiffOverlayHunk(
                    id: hunk.id,
                    startLine: hunk.startLine,
                    endLine: hunk.endLine,
                    status: metalOverlayStatus(from: hunk.changeType),
                    addedLineCount: hunk.addedLineCount,
                    deletedLineCount: hunk.deletedLineCount,
                    filePath: hunk.path
                )
            }
            view.setDiffOverlayHunks(overlayHunks)
        } else {
            view.setDiffOverlayHunks([])
        }
    }

    private func metalGutterStatus(from type: VVMultiDiffVisualHunk.ChangeType) -> MetalGutterGitHunk.Status {
        switch type {
        case .added:
            return .added
        case .modified:
            return .modified
        case .deleted:
            return .deleted
        }
    }

    private func metalOverlayStatus(from type: VVMultiDiffVisualHunk.ChangeType) -> MetalDiffOverlayHunk.Status {
        switch type {
        case .added:
            return .added
        case .modified:
            return .modified
        case .deleted:
            return .deleted
        }
    }

    final class Coordinator: NSObject, VVEditorDelegate {
        var document: VVMultiDiffDocument
        weak var view: VVMetalEditorContainerView?
        var isApplyingProgrammaticText = false
        var onDiffOverlayHover: ((String?) -> Void)?
        var onDiffOverlayAction: ((String, VVMultiDiffHunkAction) -> Void)?
        var onVisibleLineRange: ((ClosedRange<Int>) -> Void)?

        private let segmentHighlighter = VVMultiSegmentHighlighter()
        private var highlightTask: Task<Void, Never>?
        private var highlightRequestID = 0
        private var lastHighlightedRevision = -1
        private var lastTheme: VVTheme?

        init(document: VVMultiDiffDocument) {
            self.document = document
        }

        deinit {
            highlightTask?.cancel()
        }

        nonisolated func editorDidChangeText(_ text: String) {
            Task { @MainActor [weak self] in
                self?.handleEditorDidChangeText(text)
            }
        }

        @MainActor
        private func handleEditorDidChangeText(_ text: String) {
            guard !isApplyingProgrammaticText else { return }
            document.handleProjectedTextChange(text)

            if let view,
               view.text != document.projectDocument.text {
                isApplyingProgrammaticText = true
                view.setText(document.projectDocument.text, applyHighlighting: false)
                isApplyingProgrammaticText = false
            }
        }

        nonisolated func editorDidChangeSelection(_ range: NSRange) {}

        nonisolated func editorDidChangeCursorPosition(_ position: VVTextPosition) {}

        func handleVisibleLineRange(_ range: ClosedRange<Int>) {
            Task { @MainActor [weak self] in
                guard let self else { return }
                document.updateRenderAnchor(forVisibleLineRange: range)
                onVisibleLineRange?(range)
            }
        }

        func handleDiffOverlayAction(hunkID: String, action: MetalTextView.DiffOverlayAction) {
            Task { @MainActor [weak self] in
                guard let self else { return }

                let mapped: VVMultiDiffHunkAction
                switch action {
                case .comment:
                    mapped = .comment
                case .copy:
                    mapped = .copy
                case .toggleFold:
                    mapped = .toggleFold
                }

                onDiffOverlayAction?(hunkID, mapped)
            }
        }

        @MainActor
        func scheduleHighlights(
            for presentation: VVMultiDiffPresentation,
            theme: VVTheme,
            force: Bool = false
        ) {
            guard let view else { return }

            let themeChanged = lastTheme != theme
            if !force && !themeChanged && lastHighlightedRevision == presentation.revision {
                return
            }

            lastTheme = theme
            lastHighlightedRevision = presentation.revision

            highlightRequestID += 1
            let requestID = highlightRequestID
            highlightTask?.cancel()

            highlightTask = Task { [weak self, weak view] in
                guard let self else { return }

                let ranges = await self.segmentHighlighter.highlightRanges(
                    text: presentation.text,
                    segments: presentation.highlightSegments,
                    theme: theme
                )

                guard !Task.isCancelled else { return }
                guard requestID == self.highlightRequestID else { return }
                guard let view else { return }
                guard view.text == presentation.text else { return }

                view.restoreHighlightRanges(ranges)
            }
        }
    }
}

private struct VVMultiDiffOverviewStrip: View {
    let presentation: VVMultiDiffPresentation
    let theme: VVTheme
    let configuration: VVConfiguration

    private var totalAdded: Int {
        presentation.fileSummaries.reduce(0) { $0 + $1.addedLineCount }
    }

    private var totalDeleted: Int {
        presentation.fileSummaries.reduce(0) { $0 + $1.deletedLineCount }
    }

    private var totalHunks: Int {
        presentation.fileSummaries.reduce(0) { $0 + $1.hunkCount }
    }

    var body: some View {
        ScrollView(.horizontal, showsIndicators: false) {
            HStack(spacing: 8) {
                chip(
                    title: "Diff",
                    subtitle: "\(presentation.fileSummaries.count) files • \(totalHunks) hunks • +\(totalAdded) -\(totalDeleted)",
                    accent: theme.gitModifiedColor
                )

                if presentation.renderWindowState.isActive {
                    chip(
                        title: "Windowed",
                        subtitle: "\(presentation.renderWindowState.visibleHunkCount)/\(presentation.renderWindowState.totalHunkCount) hunks",
                        accent: theme.selectionColor
                    )
                }

                ForEach(presentation.fileSummaries) { summary in
                    chip(
                        title: (summary.path as NSString).lastPathComponent,
                        subtitle: "+\(summary.addedLineCount) -\(summary.deletedLineCount) • \(summary.hunkCount) hunks",
                        accent: summaryAccentColor(for: summary)
                    )
                }
            }
            .padding(.horizontal, 10)
            .padding(.vertical, 8)
        }
        .background(
            LinearGradient(
                colors: [
                    Color(nsColor: theme.gutterBackgroundColor.withAlphaComponent(0.98)),
                    Color(nsColor: theme.backgroundColor.withAlphaComponent(0.95))
                ],
                startPoint: .topLeading,
                endPoint: .bottomTrailing
            )
        )
        .overlay(alignment: .bottom) {
            Rectangle()
                .fill(Color(nsColor: theme.gutterSeparatorColor.withAlphaComponent(0.65)))
                .frame(height: 1)
        }
    }

    @ViewBuilder
    private func chip(title: String, subtitle: String, accent: NSColor) -> some View {
        VStack(alignment: .leading, spacing: 2) {
            Text(title)
                .font(.system(size: configuration.font.pointSize, weight: .semibold, design: .monospaced))
                .foregroundStyle(Color(nsColor: theme.textColor))
                .lineLimit(1)
            Text(subtitle)
                .font(.system(size: max(10, configuration.font.pointSize - 2), design: .monospaced))
                .foregroundStyle(Color(nsColor: theme.gutterTextColor))
                .lineLimit(1)
        }
        .padding(.horizontal, 10)
        .padding(.vertical, 6)
        .background(
            RoundedRectangle(cornerRadius: 8, style: .continuous)
                .fill(Color(nsColor: accent.withAlphaComponent(0.16)))
        )
        .overlay(
            RoundedRectangle(cornerRadius: 8, style: .continuous)
                .stroke(Color(nsColor: accent.withAlphaComponent(0.5)), lineWidth: 1)
        )
    }

    private func summaryAccentColor(for summary: VVMultiDiffFileSummary) -> NSColor {
        if summary.deletedLineCount > 0 && summary.addedLineCount == 0 {
            return theme.gitDeletedColor
        }
        if summary.addedLineCount > 0 && summary.deletedLineCount == 0 {
            return theme.gitAddedColor
        }
        return theme.gitModifiedColor
    }
}

/// Single editor surface backed by `VVMultiDiffDocument` projection.
public struct VVMultiBufferDiffView: View {
    @ObservedObject private var document: VVMultiDiffDocument
    @State private var hoveredHunkID: String?
    private var theme: VVTheme
    private var configuration: VVConfiguration
    private var showsOverviewStrip: Bool
    private var showsDiffOverlayCallouts: Bool
    private var headerMetadataRenderer: ((VVMultiDiffPresentation) -> AnyView)?
    private var hoverUtilityRenderer: ((VVMultiDiffVisualHunk, @escaping (VVMultiDiffHunkAction) -> Void) -> AnyView)?
    private var onHunkAction: ((VVMultiDiffVisualHunk, VVMultiDiffHunkAction) -> Void)?
    private var onHoverHunk: ((VVMultiDiffVisualHunk?) -> Void)?

    public init(document: VVMultiDiffDocument) {
        self.document = document
        self.theme = .defaultDark
        self.configuration = .default
        self.showsOverviewStrip = true
        self.showsDiffOverlayCallouts = true
        self.headerMetadataRenderer = nil
        self.hoverUtilityRenderer = nil
        self.onHunkAction = nil
        self.onHoverHunk = nil
    }

    public var body: some View {
        let presentation = document.presentation()
        let hoveredHunk = showsDiffOverlayCallouts
            ? hoveredHunkID.flatMap { id in
                presentation.visualHunks.first(where: { $0.id == id })
            }
            : nil

        VStack(spacing: 0) {
            if showsOverviewStrip {
                if let headerMetadataRenderer {
                    headerMetadataRenderer(presentation)
                } else {
                    VVMultiDiffOverviewStrip(
                        presentation: presentation,
                        theme: theme,
                        configuration: configuration
                    )
                }
            }

            ZStack(alignment: .topTrailing) {
                VVMultiBufferDiffRepresentable(
                    document: document,
                    theme: theme,
                    configuration: configuration,
                    showsDiffOverlayCallouts: showsDiffOverlayCallouts,
                    onDiffOverlayHover: showsDiffOverlayCallouts ? { hunkID in
                        hoveredHunkID = hunkID
                        let hunk = hunkID.flatMap { id in
                            presentation.visualHunks.first(where: { $0.id == id })
                        }
                        onHoverHunk?(hunk)
                    } : nil,
                    onDiffOverlayAction: showsDiffOverlayCallouts ? { hunkID, action in
                        guard let hunk = presentation.visualHunks.first(where: { $0.id == hunkID }) else { return }
                        performHunkAction(action, hunk: hunk, presentation: presentation)
                    } : nil,
                    onVisibleLineRange: { _ in }
                )

                if let hoveredHunk {
                    if let hoverUtilityRenderer {
                        hoverUtilityRenderer(hoveredHunk) { action in
                            performHunkAction(action, hunk: hoveredHunk, presentation: presentation)
                        }
                        .padding(.top, 10)
                        .padding(.trailing, 10)
                    } else {
                        hoverUtilitySlot(for: hoveredHunk, presentation: presentation)
                            .padding(.top, 10)
                            .padding(.trailing, 10)
                    }
                }
            }
        }
        .onChange(of: showsDiffOverlayCallouts) { show in
            if !show {
                hoveredHunkID = nil
            }
        }
    }

    @ViewBuilder
    private func hoverUtilitySlot(
        for hunk: VVMultiDiffVisualHunk,
        presentation: VVMultiDiffPresentation
    ) -> some View {
        let fileName = (hunk.path as NSString).lastPathComponent
        let statusColor = accentColor(for: hunk.changeType)

        VStack(alignment: .leading, spacing: 6) {
            Text(fileName)
                .font(.system(size: configuration.font.pointSize - 1, weight: .semibold, design: .monospaced))
                .foregroundStyle(Color(nsColor: theme.textColor))
            Text("+\(hunk.addedLineCount) -\(hunk.deletedLineCount) • lines \(hunk.startLine + 1)-\(hunk.endLine + 1)")
                .font(.system(size: max(10, configuration.font.pointSize - 3), design: .monospaced))
                .foregroundStyle(Color(nsColor: theme.gutterTextColor))

            HStack(spacing: 6) {
                hoverActionButton("Comment", color: statusColor) {
                    performHunkAction(.comment, hunk: hunk, presentation: presentation)
                }
                hoverActionButton("Copy", color: statusColor) {
                    performHunkAction(.copy, hunk: hunk, presentation: presentation)
                }
                hoverActionButton("Fold", color: statusColor) {
                    performHunkAction(.toggleFold, hunk: hunk, presentation: presentation)
                }
            }
        }
        .padding(.horizontal, 10)
        .padding(.vertical, 8)
        .background(
            RoundedRectangle(cornerRadius: 9, style: .continuous)
                .fill(Color(nsColor: theme.gutterBackgroundColor.withAlphaComponent(0.96)))
        )
        .overlay(
            RoundedRectangle(cornerRadius: 9, style: .continuous)
                .stroke(Color(nsColor: statusColor.withAlphaComponent(0.6)), lineWidth: 1)
        )
    }

    @ViewBuilder
    private func hoverActionButton(_ title: String, color: NSColor, action: @escaping () -> Void) -> some View {
        Button(title, action: action)
            .buttonStyle(.plain)
            .font(.system(size: max(10, configuration.font.pointSize - 3), weight: .medium, design: .monospaced))
            .foregroundStyle(Color(nsColor: theme.textColor))
            .padding(.horizontal, 7)
            .padding(.vertical, 4)
            .background(
                RoundedRectangle(cornerRadius: 6, style: .continuous)
                    .fill(Color(nsColor: color.withAlphaComponent(0.18)))
            )
            .overlay(
                RoundedRectangle(cornerRadius: 6, style: .continuous)
                    .stroke(Color(nsColor: color.withAlphaComponent(0.5)), lineWidth: 1)
            )
    }

    private func accentColor(for changeType: VVMultiDiffVisualHunk.ChangeType) -> NSColor {
        switch changeType {
        case .added:
            return theme.gitAddedColor
        case .modified:
            return theme.gitModifiedColor
        case .deleted:
            return theme.gitDeletedColor
        }
    }

    private func performHunkAction(
        _ action: VVMultiDiffHunkAction,
        hunk: VVMultiDiffVisualHunk,
        presentation: VVMultiDiffPresentation
    ) {
        onHunkAction?(hunk, action)

        switch action {
        case .comment:
            break
        case .copy:
            if let hunkText = hunkText(for: hunk.id, in: presentation) {
                let pasteboard = NSPasteboard.general
                pasteboard.clearContents()
                pasteboard.setString(hunkText, forType: .string)
            }
        case .toggleFold:
            document.toggleFold(atLine: hunk.startLine)
        }
    }

    private func hunkText(for hunkID: String, in presentation: VVMultiDiffPresentation) -> String? {
        guard let foldRange = presentation.foldRanges.first(where: { $0.id == hunkID }) else {
            return nil
        }

        let lines = presentation.text.split(separator: "\n", omittingEmptySubsequences: false).map(String.init)
        guard !lines.isEmpty else { return nil }

        let start = max(0, min(foldRange.startLine, lines.count - 1))
        let end = max(start, min(foldRange.endLine, lines.count - 1))
        return lines[start...end].joined(separator: "\n")
    }
}

extension VVMultiBufferDiffView {
    public func theme(_ theme: VVTheme) -> VVMultiBufferDiffView {
        var view = self
        view.theme = theme
        return view
    }

    public func configuration(_ configuration: VVConfiguration) -> VVMultiBufferDiffView {
        var view = self
        view.configuration = configuration
        return view
    }

    public func showsOverviewStrip(_ show: Bool) -> VVMultiBufferDiffView {
        var view = self
        view.showsOverviewStrip = show
        return view
    }

    public func showsDiffOverlayCallouts(_ show: Bool) -> VVMultiBufferDiffView {
        var view = self
        view.showsDiffOverlayCallouts = show
        return view
    }

    public func renderHeaderMetadata<Content: View>(
        _ builder: @escaping (VVMultiDiffPresentation) -> Content
    ) -> VVMultiBufferDiffView {
        var view = self
        view.headerMetadataRenderer = { presentation in
            AnyView(builder(presentation))
        }
        return view
    }

    public func renderHoverUtility<Content: View>(
        _ builder: @escaping (VVMultiDiffVisualHunk, @escaping (VVMultiDiffHunkAction) -> Void) -> Content
    ) -> VVMultiBufferDiffView {
        var view = self
        view.hoverUtilityRenderer = { hunk, perform in
            AnyView(builder(hunk, perform))
        }
        return view
    }

    public func onHunkAction(
        _ handler: @escaping (VVMultiDiffVisualHunk, VVMultiDiffHunkAction) -> Void
    ) -> VVMultiBufferDiffView {
        var view = self
        view.onHunkAction = handler
        return view
    }

    public func onHoverHunk(
        _ handler: @escaping (VVMultiDiffVisualHunk?) -> Void
    ) -> VVMultiBufferDiffView {
        var view = self
        view.onHoverHunk = handler
        return view
    }
}
