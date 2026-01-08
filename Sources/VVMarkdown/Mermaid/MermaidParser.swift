//  MermaidParser.swift
//  VVMarkdown
//
//  Minimal Mermaid parser (sequence + flowchart) with no external dependencies.

import Foundation

public enum MermaidDiagram: Sendable, Equatable {
    case sequence(SequenceDiagram)
    case flow(FlowDiagram)
    case `class`(ClassDiagram)
    case state(StateDiagram)
    case er(ERDiagram)
    case gantt(GanttChart)
    case pie(PieChart)
    case git(GitGraph)
    case unknown
}

public struct SequenceDiagram: Sendable, Equatable {
    public let participants: [String]
    public let messages: [SequenceMessage]
    public let notes: [SequenceNote]
    public let activations: [SequenceActivation]
    public let groups: [SequenceGroup]
    public let eventCount: Int
}

public struct SequenceMessage: Sendable, Equatable {
    public let from: String
    public let to: String
    public let text: String
    public let isDashed: Bool
    public let index: Int
}

public struct SequenceNote: Sendable, Equatable {
    public enum Anchor: Sendable, Equatable {
        case over([String])
        case leftOf(String)
        case rightOf(String)
    }
    public let anchor: Anchor
    public let text: String
    public let index: Int
}

public struct SequenceActivation: Sendable, Equatable {
    public let participant: String
    public let isActivate: Bool
    public let index: Int
}

public struct SequenceGroup: Sendable, Equatable {
    public enum Kind: Sendable, Equatable {
        case loop
        case alt
        case opt
    }
    public let kind: Kind
    public let text: String
    public let startIndex: Int
    public let endIndex: Int
}

public enum FlowDirection: Sendable, Equatable {
    case topDown
    case leftRight
    case rightLeft
    case bottomTop
}

public enum FlowNodeShape: Sendable, Equatable {
    case rect
    case round
    case diamond
    case circle
}

public struct FlowNode: Sendable, Equatable {
    public let id: String
    public let label: String
    public let shape: FlowNodeShape
}

public struct FlowEdge: Sendable, Equatable {
    public let from: String
    public let to: String
    public let label: String?
    public let isDashed: Bool
}

public struct FlowDiagram: Sendable, Equatable {
    public let nodes: [String: FlowNode]
    public let edges: [FlowEdge]
    public let direction: FlowDirection
}

public struct ClassDiagram: Sendable, Equatable {
    public let classes: [String: ClassNode]
    public let edges: [ClassEdge]
}

public struct ClassNode: Sendable, Equatable {
    public let id: String
    public let title: String
    public let members: [String]
}

public struct ClassEdge: Sendable, Equatable {
    public let from: String
    public let to: String
    public let label: String?
    public let kind: ClassEdgeKind
}

public enum ClassEdgeKind: Sendable, Equatable {
    case inheritance
    case composition
    case aggregation
    case association
    case dependency
}

public struct StateDiagram: Sendable, Equatable {
    public let states: [String: StateNode]
    public let edges: [StateEdge]
}

public struct StateNode: Sendable, Equatable {
    public let id: String
    public let label: String
    public let isStart: Bool
    public let isEnd: Bool
}

public struct StateEdge: Sendable, Equatable {
    public let from: String
    public let to: String
    public let label: String?
}

public struct ERDiagram: Sendable, Equatable {
    public let entities: [String: EREntity]
    public let relations: [ERRelation]
}

public struct EREntity: Sendable, Equatable {
    public let id: String
    public let attributes: [String]
}

public struct ERRelation: Sendable, Equatable {
    public let from: String
    public let to: String
    public let label: String?
}

public struct GanttChart: Sendable, Equatable {
    public let sections: [GanttSection]
}

public struct GanttSection: Sendable, Equatable {
    public let title: String
    public let tasks: [GanttTask]
}

public struct GanttTask: Sendable, Equatable {
    public let id: String?
    public let title: String
    public let start: Double
    public let end: Double
    public let status: String?
}

public struct PieChart: Sendable, Equatable {
    public let title: String?
    public let slices: [PieSlice]
}

public struct PieSlice: Sendable, Equatable {
    public let label: String
    public let value: Double
}

public struct GitGraph: Sendable, Equatable {
    public let branches: [String]
    public let commits: [GitCommit]
    public let branchOrigins: [String: Int]
}

public struct GitCommit: Sendable, Equatable {
    public let index: Int
    public let branch: String
    public let mergeFrom: String?
}

public final class MermaidParser {
    public init() {}

    public func parse(_ source: String) -> MermaidDiagram {
        let lines = source
            .split(whereSeparator: \.isNewline)
            .map { $0.trimmingCharacters(in: .whitespaces) }
            .filter { !$0.isEmpty && !$0.hasPrefix("%%") }

        guard let first = lines.first?.lowercased() else { return .unknown }

        if first.hasPrefix("sequencediagram") {
            return .sequence(parseSequence(lines: Array(lines.dropFirst())))
        }

        if first.hasPrefix("graph") || first.hasPrefix("flowchart") {
            return .flow(parseFlow(lines: Array(lines.dropFirst()), header: first))
        }

        if first.hasPrefix("classdiagram") {
            return .class(parseClass(lines: Array(lines.dropFirst())))
        }

        if first.hasPrefix("statediagram") || first.hasPrefix("statediagram-v2") {
            return .state(parseState(lines: Array(lines.dropFirst())))
        }

        if first.hasPrefix("erdiagram") {
            return .er(parseER(lines: Array(lines.dropFirst())))
        }

        if first.hasPrefix("gantt") {
            return .gantt(parseGantt(lines: Array(lines.dropFirst())))
        }

        if first.hasPrefix("pie") {
            return .pie(parsePie(lines: Array(lines.dropFirst())))
        }

        if first.hasPrefix("gitgraph") {
            return .git(parseGitGraph(lines: Array(lines.dropFirst())))
        }

        return .unknown
    }

    private func parseSequence(lines: [String]) -> SequenceDiagram {
        var participants: [String] = []
        var messages: [SequenceMessage] = []
        var notes: [SequenceNote] = []
        var activations: [SequenceActivation] = []
        var groups: [SequenceGroup] = []
        var eventIndex = 0
        var groupStack: [(kind: SequenceGroup.Kind, text: String, start: Int)] = []

        func addParticipant(_ name: String) {
            guard !name.isEmpty else { return }
            if !participants.contains(name) {
                participants.append(name)
            }
        }

        for line in lines {
            let trimmed = line.trimmingCharacters(in: .whitespaces)
            if trimmed.hasPrefix("participant ") || trimmed.hasPrefix("actor ") {
                let parts = trimmed.split(separator: " ", maxSplits: 1).map(String.init)
                if parts.count > 1 {
                    let rest = parts[1]
                    if let range = rest.range(of: " as ") {
                        let name = rest[..<range.lowerBound].trimmingCharacters(in: .whitespaces)
                        addParticipant(String(name))
                    } else {
                        addParticipant(rest)
                    }
                }
                continue
            }

            if let note = parseSequenceNote(line: trimmed) {
                switch note.anchor {
                case .over(let names):
                    names.forEach(addParticipant)
                case .leftOf(let name), .rightOf(let name):
                    addParticipant(name)
                }
                notes.append(SequenceNote(anchor: note.anchor, text: note.text, index: eventIndex))
                eventIndex += 1
                continue
            }

            if let activation = parseSequenceActivation(line: trimmed) {
                addParticipant(activation.participant)
                activations.append(SequenceActivation(participant: activation.participant, isActivate: activation.isActivate, index: eventIndex))
                continue
            }

            if let group = parseSequenceGroupStart(line: trimmed) {
                groupStack.append((group.kind, group.text, eventIndex))
                continue
            }

            if trimmed == "end" || trimmed == "end loop" || trimmed == "end alt" || trimmed == "end opt" {
                if let last = groupStack.popLast() {
                    groups.append(SequenceGroup(kind: last.kind, text: last.text, startIndex: last.start, endIndex: max(last.start, eventIndex - 1)))
                }
                continue
            }

            if let message = parseSequenceMessage(line: trimmed) {
                addParticipant(message.from)
                addParticipant(message.to)
                messages.append(SequenceMessage(from: message.from, to: message.to, text: message.text, isDashed: message.isDashed, index: eventIndex))
                eventIndex += 1
            }
        }

        // Close any open groups
        for pending in groupStack {
            groups.append(SequenceGroup(kind: pending.kind, text: pending.text, startIndex: pending.start, endIndex: max(pending.start, eventIndex - 1)))
        }

        return SequenceDiagram(participants: participants, messages: messages, notes: notes, activations: activations, groups: groups, eventCount: eventIndex)
    }

    private func parseSequenceMessage(line: String) -> SequenceMessage? {
        let arrowTokens = ["-->>", "->>", "-->", "->"]
        for arrow in arrowTokens {
            if let range = line.range(of: arrow) {
                let left = String(line[..<range.lowerBound]).trimmingCharacters(in: .whitespaces)
                let rightAndLabel = String(line[range.upperBound...])
                let parts = rightAndLabel.split(separator: ":", maxSplits: 1).map(String.init)
                let right = parts.first?.trimmingCharacters(in: .whitespaces) ?? ""
                let text = parts.count > 1 ? parts[1].trimmingCharacters(in: .whitespaces) : ""
                let isDashed = arrow.hasPrefix("--")
                if !left.isEmpty && !right.isEmpty {
                    return SequenceMessage(from: left, to: right, text: text, isDashed: isDashed, index: 0)
                }
            }
        }
        return nil
    }

    private func parseSequenceNote(line: String) -> (anchor: SequenceNote.Anchor, text: String)? {
        let lower = line.lowercased()
        guard lower.hasPrefix("note ") else { return nil }

        if lower.hasPrefix("note over ") {
            let rest = String(line.dropFirst("note over ".count))
            let parts = rest.split(separator: ":", maxSplits: 1).map(String.init)
            let names = parts.first?.split(separator: ",").map { $0.trimmingCharacters(in: .whitespaces) } ?? []
            let text = parts.count > 1 ? parts[1].trimmingCharacters(in: .whitespaces) : ""
            return (.over(names.filter { !$0.isEmpty }), text)
        }

        if lower.hasPrefix("note left of ") {
            let rest = String(line.dropFirst("note left of ".count))
            let parts = rest.split(separator: ":", maxSplits: 1).map(String.init)
            let name = parts.first?.trimmingCharacters(in: .whitespaces) ?? ""
            let text = parts.count > 1 ? parts[1].trimmingCharacters(in: .whitespaces) : ""
            return (.leftOf(name), text)
        }

        if lower.hasPrefix("note right of ") {
            let rest = String(line.dropFirst("note right of ".count))
            let parts = rest.split(separator: ":", maxSplits: 1).map(String.init)
            let name = parts.first?.trimmingCharacters(in: .whitespaces) ?? ""
            let text = parts.count > 1 ? parts[1].trimmingCharacters(in: .whitespaces) : ""
            return (.rightOf(name), text)
        }

        return nil
    }

    private func parseSequenceActivation(line: String) -> (participant: String, isActivate: Bool)? {
        let lower = line.lowercased()
        if lower.hasPrefix("activate ") {
            let name = line.dropFirst("activate ".count).trimmingCharacters(in: .whitespaces)
            return (name, true)
        }
        if lower.hasPrefix("deactivate ") {
            let name = line.dropFirst("deactivate ".count).trimmingCharacters(in: .whitespaces)
            return (name, false)
        }
        return nil
    }

    private func parseSequenceGroupStart(line: String) -> (kind: SequenceGroup.Kind, text: String)? {
        let lower = line.lowercased()
        if lower.hasPrefix("loop ") {
            return (.loop, String(line.dropFirst("loop ".count)).trimmingCharacters(in: .whitespaces))
        }
        if lower.hasPrefix("alt ") {
            return (.alt, String(line.dropFirst("alt ".count)).trimmingCharacters(in: .whitespaces))
        }
        if lower.hasPrefix("opt ") {
            return (.opt, String(line.dropFirst("opt ".count)).trimmingCharacters(in: .whitespaces))
        }
        return nil
    }

    private func parseFlow(lines: [String], header: String) -> FlowDiagram {
        let direction = parseFlowDirection(header: header)
        var nodes: [String: FlowNode] = [:]
        var edges: [FlowEdge] = []

        for line in lines {
            let trimmed = line.trimmingCharacters(in: .whitespaces)
            guard !trimmed.isEmpty else { continue }

            if let edge = parseFlowEdge(line: trimmed, nodes: &nodes) {
                edges.append(edge)
                continue
            }

            if let node = parseFlowNodeToken(trimmed) {
                nodes[node.id] = node
            }
        }

        return FlowDiagram(nodes: nodes, edges: edges, direction: direction)
    }

    private func parseClass(lines: [String]) -> ClassDiagram {
        var classes: [String: ClassNode] = [:]
        var edges: [ClassEdge] = []
        var currentClass: String?

        func ensureClass(_ id: String) {
            if classes[id] == nil {
                classes[id] = ClassNode(id: id, title: id, members: [])
            }
        }

        for line in lines {
            let trimmed = line.trimmingCharacters(in: .whitespaces)
            guard !trimmed.isEmpty else { continue }

            if trimmed == "}" {
                currentClass = nil
                continue
            }

            if trimmed.hasPrefix("class ") {
                let rest = String(trimmed.dropFirst("class ".count)).trimmingCharacters(in: .whitespaces)
                let name = rest.replacingOccurrences(of: "{", with: "").trimmingCharacters(in: .whitespaces)
                if !name.isEmpty {
                    ensureClass(name)
                    currentClass = trimmed.contains("{") ? name : nil
                }
                continue
            }

            if let activeClass = currentClass {
                var node = classes[activeClass] ?? ClassNode(id: activeClass, title: activeClass, members: [])
                node = ClassNode(id: node.id, title: node.title, members: node.members + [trimmed])
                classes[activeClass] = node
                continue
            }

            if let edge = parseClassEdge(line: trimmed) {
                ensureClass(edge.from)
                ensureClass(edge.to)
                edges.append(edge)
                continue
            }

            if let member = parseClassMember(line: trimmed) {
                var node = classes[member.classId] ?? ClassNode(id: member.classId, title: member.classId, members: [])
                node = ClassNode(id: node.id, title: node.title, members: node.members + [member.member])
                classes[member.classId] = node
            }
        }

        return ClassDiagram(classes: classes, edges: edges)
    }

    private func parseClassMember(line: String) -> (classId: String, member: String)? {
        if let range = line.range(of: ":") {
            let left = String(line[..<range.lowerBound]).trimmingCharacters(in: .whitespaces)
            let right = String(line[range.upperBound...]).trimmingCharacters(in: .whitespaces)
            guard !left.isEmpty && !right.isEmpty else { return nil }
            return (left, right)
        }
        return nil
    }

    private func parseClassEdge(line: String) -> ClassEdge? {
        let patterns: [(String, ClassEdgeKind)] = [
            ("<|--", .inheritance),
            ("<|..", .inheritance),
            ("*--", .composition),
            ("o--", .aggregation),
            ("-->", .association),
            ("..>", .dependency)
        ]

        for (token, kind) in patterns {
            if let range = line.range(of: token) {
                let left = String(line[..<range.lowerBound]).trimmingCharacters(in: .whitespaces)
                let rightPart = String(line[range.upperBound...]).trimmingCharacters(in: .whitespaces)
                let parts = rightPart.split(separator: ":", maxSplits: 1).map(String.init)
                let right = parts.first?.trimmingCharacters(in: .whitespaces) ?? ""
                let label = parts.count > 1 ? parts[1].trimmingCharacters(in: .whitespaces) : nil
                guard !left.isEmpty && !right.isEmpty else { continue }
                return ClassEdge(from: left, to: right, label: label, kind: kind)
            }
        }

        return nil
    }

    private func parseState(lines: [String]) -> StateDiagram {
        var states: [String: StateNode] = [:]
        var edges: [StateEdge] = []

        func ensureState(_ id: String) {
            if states[id] == nil {
                states[id] = StateNode(id: id, label: id, isStart: id == "[*]", isEnd: false)
            }
        }

        for line in lines {
            let trimmed = line.trimmingCharacters(in: .whitespaces)
            guard !trimmed.isEmpty else { continue }

            if let edge = parseStateEdge(line: trimmed) {
                ensureState(edge.from)
                ensureState(edge.to)
                edges.append(edge)
                continue
            }

            if let state = parseStateNode(line: trimmed) {
                states[state.id] = state
            }
        }

        return StateDiagram(states: states, edges: edges)
    }

    private func parseStateEdge(line: String) -> StateEdge? {
        let tokens = ["-->", "->"]
        for token in tokens {
            if let range = line.range(of: token) {
                let left = String(line[..<range.lowerBound]).trimmingCharacters(in: .whitespaces)
                let rightPart = String(line[range.upperBound...]).trimmingCharacters(in: .whitespaces)
                let parts = rightPart.split(separator: ":", maxSplits: 1).map(String.init)
                let right = parts.first?.trimmingCharacters(in: .whitespaces) ?? ""
                let label = parts.count > 1 ? parts[1].trimmingCharacters(in: .whitespaces) : nil
                guard !left.isEmpty && !right.isEmpty else { continue }
                return StateEdge(from: left, to: right, label: label)
            }
        }
        return nil
    }

    private func parseStateNode(line: String) -> StateNode? {
        if line.lowercased().hasPrefix("state ") {
            let rest = String(line.dropFirst("state ".count))
            if let quoteStart = rest.firstIndex(of: "\""),
               let quoteEnd = rest[rest.index(after: quoteStart)...].firstIndex(of: "\"") {
                let label = String(rest[rest.index(after: quoteStart)..<quoteEnd])
                let after = rest[quoteEnd...]
                if let asRange = after.range(of: "as") {
                    let id = String(after[asRange.upperBound...]).trimmingCharacters(in: .whitespaces)
                    if !id.isEmpty {
                        return StateNode(id: id, label: label, isStart: id == "[*]", isEnd: label == "[*]")
                    }
                }
                return StateNode(id: label, label: label, isStart: label == "[*]", isEnd: false)
            }
            let name = rest.trimmingCharacters(in: .whitespaces)
            if !name.isEmpty {
                return StateNode(id: name, label: name, isStart: name == "[*]", isEnd: false)
            }
        }
        if let range = line.range(of: "as") {
            let left = String(line[..<range.lowerBound]).trimmingCharacters(in: .whitespaces)
            let right = String(line[range.upperBound...]).trimmingCharacters(in: .whitespaces)
            guard !left.isEmpty && !right.isEmpty else { return nil }
            return StateNode(id: left, label: right, isStart: left == "[*]", isEnd: right == "[*]")
        }
        return nil
    }

    private func parseER(lines: [String]) -> ERDiagram {
        var entities: [String: EREntity] = [:]
        var relations: [ERRelation] = []

        var currentEntity: String?
        var currentAttributes: [String] = []

        func closeEntityIfNeeded() {
            if let entity = currentEntity {
                entities[entity] = EREntity(id: entity, attributes: currentAttributes)
                currentEntity = nil
                currentAttributes = []
            }
        }

        for line in lines {
            let trimmed = line.trimmingCharacters(in: .whitespaces)
            guard !trimmed.isEmpty else { continue }

            if trimmed.hasSuffix("{") {
                closeEntityIfNeeded()
                let name = trimmed.replacingOccurrences(of: "{", with: "").trimmingCharacters(in: .whitespaces)
                if !name.isEmpty {
                    currentEntity = name
                }
                continue
            }

            if trimmed == "}" {
                closeEntityIfNeeded()
                continue
            }

            if currentEntity != nil {
                currentAttributes.append(trimmed)
                continue
            }

            if let relation = parseERRelation(line: trimmed) {
                relations.append(relation)
                if entities[relation.from] == nil {
                    entities[relation.from] = EREntity(id: relation.from, attributes: [])
                }
                if entities[relation.to] == nil {
                    entities[relation.to] = EREntity(id: relation.to, attributes: [])
                }
            }
        }

        closeEntityIfNeeded()
        return ERDiagram(entities: entities, relations: relations)
    }

    private func parseERRelation(line: String) -> ERRelation? {
        let tokens = ["||--o{", "||--|{", "}|--||", "}o--||", "}o--o{", "||--||", "}o--|{", "|o--o{", "|o--||"]
        for token in tokens {
            if let range = line.range(of: token) {
                let left = String(line[..<range.lowerBound]).trimmingCharacters(in: .whitespaces)
                let rightPart = String(line[range.upperBound...]).trimmingCharacters(in: .whitespaces)
                let parts = rightPart.split(separator: ":", maxSplits: 1).map(String.init)
                let right = parts.first?.trimmingCharacters(in: .whitespaces) ?? ""
                let label = parts.count > 1 ? parts[1].trimmingCharacters(in: .whitespaces) : nil
                guard !left.isEmpty && !right.isEmpty else { continue }
                return ERRelation(from: left, to: right, label: label)
            }
        }
        return nil
    }

    private func parseGantt(lines: [String]) -> GanttChart {
        var sections: [GanttSection] = []
        var currentSection: String = "Tasks"
        var currentTasks: [GanttTask] = []
        var lastEnd: Double = 0
        var taskById: [String: GanttTask] = [:]

        func flushSection() {
            if !currentTasks.isEmpty {
                sections.append(GanttSection(title: currentSection, tasks: currentTasks))
                currentTasks = []
            }
        }

        for line in lines {
            let trimmed = line.trimmingCharacters(in: .whitespaces)
            guard !trimmed.isEmpty else { continue }

            if trimmed.lowercased().hasPrefix("section ") {
                flushSection()
                currentSection = String(trimmed.dropFirst("section ".count)).trimmingCharacters(in: .whitespaces)
                continue
            }

            if let task = parseGanttTask(line: trimmed, lastEnd: lastEnd, taskById: taskById) {
                currentTasks.append(task)
                lastEnd = max(lastEnd, task.end)
                if let id = task.id {
                    taskById[id] = task
                }
            }
        }

        flushSection()
        return GanttChart(sections: sections)
    }

    private func parseGanttTask(line: String, lastEnd: Double, taskById: [String: GanttTask]) -> GanttTask? {
        let parts = line.split(separator: ":", maxSplits: 1).map(String.init)
        guard parts.count == 2 else { return nil }
        let title = parts[0].trimmingCharacters(in: .whitespaces)
        let tokens = parts[1].split(separator: ",").map { $0.trimmingCharacters(in: .whitespaces) }
        guard !title.isEmpty else { return nil }

        var status: String?
        var id: String?
        var start: Double?
        var duration: Double?

        for token in tokens {
            if token.hasPrefix("after ") {
                let ref = token.replacingOccurrences(of: "after ", with: "")
                if let refTask = taskById[ref] {
                    start = refTask.end
                }
                continue
            }

            if parseDate(token) != nil {
                start = parseDate(token)
                continue
            }

            if let dur = parseDuration(token) {
                duration = dur
                continue
            }

            if status == nil, ["done", "active", "crit", "milestone"].contains(token.lowercased()) {
                status = token
                continue
            }

            if id == nil && !token.isEmpty {
                id = token
            }
        }

        let startValue = start ?? lastEnd
        let durationValue = duration ?? 1
        return GanttTask(id: id, title: title, start: startValue, end: startValue + durationValue, status: status)
    }

    private func parseDuration(_ token: String) -> Double? {
        let trimmed = token.trimmingCharacters(in: .whitespaces)
        guard trimmed.count >= 2 else { return nil }
        let numberPart = trimmed.dropLast()
        let unit = trimmed.last
        guard let value = Double(numberPart) else { return nil }
        if unit == "d" || unit == "D" {
            return value
        }
        if unit == "h" || unit == "H" {
            return value / 24.0
        }
        return nil
    }

    private func parseDate(_ token: String) -> Double? {
        let formatter = DateFormatter()
        formatter.dateFormat = "yyyy-MM-dd"
        if let date = formatter.date(from: token) {
            return date.timeIntervalSinceReferenceDate / 86400.0
        }
        return nil
    }

    private func parsePie(lines: [String]) -> PieChart {
        var title: String?
        var slices: [PieSlice] = []
        for line in lines {
            let trimmed = line.trimmingCharacters(in: .whitespaces)
            guard !trimmed.isEmpty else { continue }
            if trimmed.lowercased().hasPrefix("title ") {
                title = String(trimmed.dropFirst("title ".count)).trimmingCharacters(in: .whitespaces)
                continue
            }
            if let slice = parsePieSlice(line: trimmed) {
                slices.append(slice)
            }
        }
        return PieChart(title: title, slices: slices)
    }

    private func parsePieSlice(line: String) -> PieSlice? {
        let parts = line.split(separator: ":", maxSplits: 1).map(String.init)
        guard parts.count == 2 else { return nil }
        var label = parts[0].trimmingCharacters(in: .whitespacesAndNewlines)
        if label.hasPrefix("\"") && label.hasSuffix("\"") && label.count >= 2 {
            label = String(label.dropFirst().dropLast())
        }
        let valueString = parts[1].trimmingCharacters(in: .whitespacesAndNewlines)
        guard let value = Double(valueString) else { return nil }
        return PieSlice(label: label, value: value)
    }

    private func parseGitGraph(lines: [String]) -> GitGraph {
        var branches: [String] = ["main"]
        var currentBranch = "main"
        var commits: [GitCommit] = []
        var branchOrigins: [String: Int] = ["main": -1]

        func ensureBranch(_ name: String) {
            if !branches.contains(name) {
                branches.append(name)
                branchOrigins[name] = max(commits.count - 1, -1)
            }
        }

        for line in lines {
            let trimmed = line.trimmingCharacters(in: .whitespaces)
            guard !trimmed.isEmpty else { continue }

            if trimmed.lowercased().hasPrefix("branch ") {
                let name = String(trimmed.dropFirst("branch ".count)).trimmingCharacters(in: .whitespaces)
                if !name.isEmpty {
                    ensureBranch(name)
                    currentBranch = name
                }
                continue
            }

            if trimmed.lowercased().hasPrefix("checkout ") {
                let name = String(trimmed.dropFirst("checkout ".count)).trimmingCharacters(in: .whitespaces)
                if !name.isEmpty {
                    ensureBranch(name)
                    currentBranch = name
                }
                continue
            }

            if trimmed.lowercased().hasPrefix("merge ") {
                let remainder = String(trimmed.dropFirst("merge ".count)).trimmingCharacters(in: .whitespaces)
                let name = remainder.split(separator: " ").first.map(String.init) ?? ""
                if !name.isEmpty {
                    ensureBranch(name)
                }
                let commitIndex = commits.count
                commits.append(GitCommit(index: commitIndex, branch: currentBranch, mergeFrom: name.isEmpty ? nil : name))
                continue
            }

            if trimmed.lowercased().hasPrefix("commit") {
                let commitIndex = commits.count
                commits.append(GitCommit(index: commitIndex, branch: currentBranch, mergeFrom: nil))
                continue
            }
        }

        return GitGraph(branches: branches, commits: commits, branchOrigins: branchOrigins)
    }

    private func parseFlowDirection(header: String) -> FlowDirection {
        let parts = header.split(separator: " ")
        if parts.count >= 2 {
            switch parts[1].uppercased() {
            case "LR": return .leftRight
            case "RL": return .rightLeft
            case "BT": return .bottomTop
            default: return .topDown
            }
        }
        return .topDown
    }

    private func parseFlowEdge(line: String, nodes: inout [String: FlowNode]) -> FlowEdge? {
        var label: String?
        var working = line
        if let labelRange = extractPipeLabel(from: working) {
            label = labelRange.label
            working = labelRange.cleaned
        }

        let arrowTokens = ["-->", "->", "==>", "---"]
        for arrow in arrowTokens {
            if let range = working.range(of: arrow) {
                let leftToken = String(working[..<range.lowerBound]).trimmingCharacters(in: .whitespaces)
                let rightToken = String(working[range.upperBound...]).trimmingCharacters(in: .whitespaces)
                guard let leftNode = parseFlowNodeToken(leftToken) else { continue }
                guard let rightNode = parseFlowNodeToken(rightToken) else { continue }
                nodes[leftNode.id] = leftNode
                nodes[rightNode.id] = rightNode
                let isDashed = arrow == "---"
                return FlowEdge(from: leftNode.id, to: rightNode.id, label: label, isDashed: isDashed)
            }
        }
        return nil
    }

    private func extractPipeLabel(from line: String) -> (label: String, cleaned: String)? {
        guard let first = line.firstIndex(of: "|"),
              let last = line[line.index(after: first)...].firstIndex(of: "|"),
              last > first else {
            return nil
        }
        let label = String(line[line.index(after: first)..<last])
        var cleaned = line
        cleaned.removeSubrange(first...last)
        return (label.trimmingCharacters(in: .whitespaces), cleaned.trimmingCharacters(in: .whitespaces))
    }

    private func parseFlowNodeToken(_ token: String) -> FlowNode? {
        let trimmed = token.trimmingCharacters(in: .whitespaces)
        guard !trimmed.isEmpty else { return nil }

        if trimmed.hasPrefix("(("), trimmed.hasSuffix("))") {
            let start = trimmed.index(trimmed.startIndex, offsetBy: 2)
            let end = trimmed.index(trimmed.endIndex, offsetBy: -2)
            let label = String(trimmed[start..<end])
            return FlowNode(id: label.isEmpty ? trimmed : label, label: label.isEmpty ? trimmed : label, shape: .circle)
        }

        if let open = trimmed.firstIndex(of: "["),
           let close = trimmed.lastIndex(of: "]"),
           open < close {
            let id = String(trimmed[..<open]).trimmingCharacters(in: .whitespaces)
            let label = String(trimmed[trimmed.index(after: open)..<close])
            return FlowNode(id: id.isEmpty ? label : id, label: label, shape: .rect)
        }

        if let open = trimmed.firstIndex(of: "("),
           let close = trimmed.lastIndex(of: ")"),
           open < close {
            let id = String(trimmed[..<open]).trimmingCharacters(in: .whitespaces)
            let label = String(trimmed[trimmed.index(after: open)..<close])
            return FlowNode(id: id.isEmpty ? label : id, label: label, shape: .round)
        }

        if let open = trimmed.firstIndex(of: "{"),
           let close = trimmed.lastIndex(of: "}"),
           open < close {
            let id = String(trimmed[..<open]).trimmingCharacters(in: .whitespaces)
            let label = String(trimmed[trimmed.index(after: open)..<close])
            return FlowNode(id: id.isEmpty ? label : id, label: label, shape: .diamond)
        }

        return FlowNode(id: trimmed, label: trimmed, shape: .rect)
    }
}
