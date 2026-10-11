"""Check direct exported-header and evaluated CMake edges against the domain ownership contract."""

import argparse
from pathlib import Path
import re
import sys


ALLOWED = {
    "Physics": set(),
    "Uncertainty": set(),
    "Catalog": {"Physics"},
    "Units": {"Catalog", "Physics"},
    "Observations": {"Catalog", "Physics", "Uncertainty"},
    "Orders": {"Observations", "Physics", "Uncertainty"},
    "Environment": {"Physics", "Uncertainty"},
    "World": {"Units", "Observations", "Environment", "Physics", "Uncertainty"},
}
INCLUDE = re.compile(r'^\s*#\s*include\b([^\n]*)', re.MULTILINE)
LITERAL_INCLUDE = re.compile(r'\s*([<"])([^>"\n]+)[>"]\s*(?://.*|/\*.*\*/\s*)?$')
NAMESPACE = re.compile(r'\bnamespace\s+NavalCommand::([A-Za-z]+)::Api\b')


class ArchitectureError(ValueError):
    pass


def cycle_errors(graph, label):
    errors = []
    visited = set()
    active = []

    def visit(node):
        if node in active:
            cycle = active[active.index(node):] + [node]
            errors.append(f"{label} cycle: {' -> '.join(cycle)}")
            return
        if node in visited:
            return
        active.append(node)
        for dependency in sorted(graph[node]):
            visit(dependency)
        active.pop()
        visited.add(node)

    for node in sorted(graph):
        visit(node)
    return errors


def header_graph(root):
    public = root / "public"
    graph = {domain: set() for domain in ALLOWED}
    populated = set()
    errors = []
    for header in sorted(public.rglob("*.h")):
        relative = header.relative_to(public)
        parts = relative.parts
        if len(parts) != 4 or parts[0] != "NavalCommand" or parts[2] != "Api" or parts[1] not in ALLOWED:
            errors.append(f"{header}: exported header must use public/NavalCommand/<Domain>/Api/<Type>.h")
            continue
        owner = parts[1]
        populated.add(owner)
        text = header.read_text(encoding="utf-8")
        namespaces = set(NAMESPACE.findall(text))
        if namespaces != {owner}:
            errors.append(f"{header}: expected only namespace NavalCommand::{owner}::Api, found {sorted(namespaces)}")
        for match in INCLUDE.finditer(text):
            line_number = text.count("\n", 0, match.start()) + 1
            literal = LITERAL_INCLUDE.fullmatch(match.group(1))
            if literal is None:
                errors.append(f"{header}:{line_number}: macro/nonliteral public include is forbidden")
                continue
            delimiter, included = literal.groups()
            location = f"{header}:{line_number}"
            if delimiter != "<":
                errors.append(f"{location}: quoted/relative public include is forbidden: {included}")
                continue
            if "/" not in included and "\\" not in included:
                continue  # Standard-library headers have no namespace ownership edge.
            included_parts = included.split("/")
            if len(included_parts) != 4 or included_parts[0] != "NavalCommand" or included_parts[2] != "Api" or included_parts[1] not in ALLOWED:
                errors.append(f"{location}: noncanonical or external domain include: {included}")
                continue
            dependency = included_parts[1]
            if not (public / included).is_file():
                errors.append(f"{location}: missing exported header: {included}")
            if dependency == owner:
                continue
            graph[owner].add(dependency)
            if dependency not in ALLOWED[owner]:
                errors.append(f"{location}: forbidden include edge {owner}.Api -> {dependency}.Api ({included})")
    errors.extend(cycle_errors(graph, "Public header"))
    return graph, populated, errors


def target_graph(manifest):
    graph = {domain: set() for domain in ALLOWED}
    declared = set()
    errors = []
    for line_number, line in enumerate(manifest.read_text(encoding="utf-8").splitlines(), 1):
        if not line:
            continue
        target, separator, links = line.partition("|")
        location = f"{manifest}:{line_number} target {target} INTERFACE_LINK_LIBRARIES"
        if not separator or not target.endswith(".Api") or target[:-4] not in ALLOWED:
            errors.append(f"{location}: invalid target graph record")
            continue
        owner = target[:-4]
        if owner in declared:
            errors.append(f"{location}: duplicate target")
        declared.add(owner)
        for dependency_target in filter(None, links.split(";")):
            if not dependency_target.endswith(".Api") or dependency_target[:-4] not in ALLOWED:
                errors.append(f"{location}: unknown/external/alias/generator-expression dependency {dependency_target}")
                continue
            dependency = dependency_target[:-4]
            graph[owner].add(dependency)
            if dependency not in ALLOWED[owner]:
                errors.append(f"{location}: forbidden target edge {target} -> {dependency_target}")
    errors.extend(cycle_errors(graph, "CMake target"))
    for owner in declared:
        for dependency in graph[owner] - declared:
            errors.append(f"{manifest}: target {owner}.Api links missing target {dependency}.Api")
    return graph, declared, errors


def check(root, manifest):
    headers, populated, errors = header_graph(root)
    targets, declared, target_errors = target_graph(manifest)
    errors.extend(target_errors)
    if populated != declared:
        errors.append(f"{manifest}: populated header domains {sorted(populated)} do not match INTERFACE targets {sorted(declared)}")
    for owner in sorted(populated | declared):
        if headers[owner] != targets[owner]:
            errors.append(
                f"{manifest}: {owner}.Api direct links {sorted(targets[owner])} must exactly match "
                f"its direct exported-header dependencies {sorted(headers[owner])}"
            )
    if errors:
        raise ArchitectureError("\n".join(errors))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, required=True)
    parser.add_argument("--targets", type=Path, required=True)
    arguments = parser.parse_args()
    try:
        check(arguments.root, arguments.targets)
    except (ArchitectureError, OSError) as error:
        print(error, file=sys.stderr)
        return 1
    print("Domain public-header and evaluated CMake dependency graphs conform to the exact allowlist.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
