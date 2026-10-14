#!/usr/bin/env python3
"""Find fakematch constructs in game code (src/ and include/).

Usage:
  python tools/decomp/lint.py [<base_ref>]     lines added since the merge base
                                               with <base_ref> (default: origin/main)
  python tools/decomp/lint.py --all [<path>...]
                                               whole files; each path is a file or a
                                               directory (default: src include)
  python tools/decomp/lint.py --tree <file>    print a file's syntax tree, for
                                               writing rules

The rules live in fakematch_rules.toml, next to this script. Needs tree-sitter:
  pip install -r tools/decomp/requirements.txt

Exits 1 if any error is found. Warnings are reported but never fail.
"""

from collections import Counter
from pathlib import Path
from typing import Dict, Iterator, List, NamedTuple, Optional, Set
import argparse
import re
import subprocess
import sys
import tomllib

try:
    from tree_sitter import Language, Node, Parser, Query, QueryCursor
    import tree_sitter_cpp
except ImportError:
    sys.exit(
        "error: lint.py needs tree-sitter: "
        "pip install -r tools/decomp/requirements.txt"
    )

from common import ROOT

PATHS = ["src", "include"]  # game code only; libs/ (SDK, runtime) is exempt
SOURCE_SUFFIXES = {".c", ".cpp", ".cp", ".h", ".hpp", ".inc"}
RULES_PATH = Path(__file__).with_name("fakematch_rules.toml")

LANGUAGE = Language(tree_sitter_cpp.language())
PARSER = Parser(LANGUAGE)


class Rule(NamedTuple):
    id: str
    severity: str  # "error" or "warning"
    message: str
    query: Query


class Finding(NamedTuple):
    path: str  # relative to the repo root, e.g. "src/gs/GSmem.cpp"
    line_number: int
    rule: Rule
    code: str  # the line the construct starts on


# --------------------------------------------------------------------------
# Rules


class Rules(NamedTuple):
    rules: List[Rule]
    blank_macros: List[str]


def load_rules() -> Rules:
    config = tomllib.loads(RULES_PATH.read_text(encoding="utf-8"))
    rules = []
    for entry in config["rule"]:
        if entry["severity"] not in ("error", "warning"):
            sys.exit(f"error: rule {entry['id']}: unknown severity {entry['severity']!r}")
        try:
            query = Query(LANGUAGE, entry["query"])
        except Exception as error:
            sys.exit(f"error: rule {entry['id']}: bad query: {error}")
        rules.append(Rule(entry["id"], entry["severity"], entry["message"], query))
    return Rules(rules, config.get("blank_macros", []))


# --------------------------------------------------------------------------
# Finding fakematches in a file


def blank_out_macros(source: bytes, macros: List[str]) -> bytes:
    """Replace the given macros with spaces, so every line and column stays
    where it was."""
    for macro in macros:
        pattern = rb"\b" + re.escape(macro.encode()) + rb"\b"
        source = re.sub(pattern, lambda match: b" " * len(match.group()), source)
    return source


def get_line_number(source: bytes, node: Node) -> int:
    """The line the node starts on. (Not via node.start_point: with
    tree-sitter 0.26 on Python 3.14, discarding a Point can crash Python.)"""
    return source.count(b"\n", 0, node.start_byte) + 1


def find_fakematches(path: str, rules: Rules) -> List[Finding]:
    """Every fakematch in the file at `path` (relative to the repo root),
    at most one per rule per line."""
    source = (ROOT / path).read_bytes()
    lines = source.split(b"\n")
    tree = PARSER.parse(blank_out_macros(source, rules.blank_macros))

    findings = []
    for rule in rules.rules:
        captures = QueryCursor(rule.query).captures(tree.root_node)
        line_numbers = {
            get_line_number(source, node) for node in captures.get("match", [])
        }
        for line_number in sorted(line_numbers):
            code = lines[line_number - 1].decode("utf-8", "replace").strip()
            findings.append(Finding(path, line_number, rule, code))
    findings.sort(key=lambda finding: finding.line_number)
    return findings


# --------------------------------------------------------------------------
# Which files and lines to check


def run_git(*args: str) -> str:
    result = subprocess.run(
        ["git", *args], cwd=ROOT, capture_output=True, text=True, check=True
    )
    return result.stdout


def is_source(path: str) -> bool:
    return Path(path).suffix in SOURCE_SUFFIXES


def find_merge_base(base: str) -> str:
    try:
        return run_git("merge-base", "HEAD", base).strip()
    except subprocess.CalledProcessError as error:
        sys.exit(
            f"error: couldn't find the merge base of HEAD and {base}: "
            f"{error.stderr.strip()}"
        )


def get_added_lines(merge_base: str) -> Dict[str, Set[int]]:
    """Line numbers added since the merge base (including untracked files), by
    path."""
    added: Dict[str, Set[int]] = {}

    diff = run_git("diff", "--unified=0", merge_base, "--", *PATHS)
    path = None
    line_number = 0
    for line in diff.splitlines():
        if line.startswith("+++ "):
            # e.g. `+++ b/src/main.cpp`, or `+++ /dev/null` for a deleted file
            path = line.removeprefix("+++ b/") if line.startswith("+++ b/") else None
        elif line.startswith("@@"):
            # e.g. `@@ -10,0 +10 @@`: added lines start at line 10
            match = re.search(r"\+(\d+)", line)
            line_number = int(match.group(1)) if match else 0
        elif line.startswith("+") and path:
            added.setdefault(path, set()).add(line_number)
            line_number += 1

    untracked = run_git("ls-files", "--others", "--exclude-standard", "--", *PATHS)
    for path in untracked.splitlines():
        line_count = len((ROOT / path).read_bytes().splitlines())
        added[path] = set(range(1, line_count + 1))

    return {path: lines for path, lines in added.items() if is_source(path)}


def iter_source_files(paths: List[str]) -> Iterator[str]:
    """Source files under the given files and directories, relative to the
    repo root."""
    for given in paths:
        path = Path(given).resolve()
        if not path.exists():
            sys.exit(f"error: {given} doesn't exist")
        if not path.is_relative_to(ROOT):
            sys.exit(f"error: {given} isn't in the repository")
        files = sorted(path.rglob("*")) if path.is_dir() else [path]
        for file in files:
            if file.is_file() and is_source(file.name):
                yield file.relative_to(ROOT).as_posix()


# --------------------------------------------------------------------------
# Output


def report(findings: List[Finding]) -> int:
    """Print the findings and a summary; return the exit code."""
    for finding in findings:
        label = "ERROR" if finding.rule.severity == "error" else "WARN "
        code = finding.code if len(finding.code) <= 100 else finding.code[:97] + "..."
        print(
            f"{label} {finding.path}:{finding.line_number}: "
            f"{finding.rule.message} [{finding.rule.id}]: {code}"
        )

    error_count = sum(finding.rule.severity == "error" for finding in findings)
    warning_count = len(findings) - error_count
    print(f"{error_count} error(s), {warning_count} warning(s)")
    for rule_id, count in Counter(finding.rule.id for finding in findings).most_common():
        print(f"  {rule_id}: {count}")
    return 1 if error_count else 0


def print_tree(path: str, rules: Rules) -> None:
    """Print each node as `field: type  line: text`, indented by depth."""
    source = Path(path).read_bytes()
    tree = PARSER.parse(blank_out_macros(source, rules.blank_macros))

    def walk(node: Node, depth: int, field: Optional[str]) -> None:
        kind = node.type if node.is_named else repr(node.type)
        label = f"{field}: {kind}" if field else kind
        text = source[node.start_byte : node.end_byte].split(b"\n", 1)[0]
        text = text.decode("utf-8", "replace").strip()[:60]
        line_number = get_line_number(source, node)
        print(f"{'  ' * depth}{label}  {line_number}: {text}")
        for index, child in enumerate(node.children):
            walk(child, depth + 1, node.field_name_for_child(index))

    walk(tree.root_node, 0, None)


def main() -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--all", action="store_true", help="check whole files")
    mode.add_argument("--tree", metavar="FILE", help="print a file's syntax tree")
    parser.add_argument(
        "paths",
        nargs="*",
        metavar="base_ref | path",
        help="base ref (default: origin/main), or with --all, files and directories",
    )
    args = parser.parse_args()
    rules = load_rules()

    if args.tree:
        print_tree(args.tree, rules)
        return 0

    findings: List[Finding] = []
    if args.all:
        for path in iter_source_files(args.paths or [str(ROOT / p) for p in PATHS]):
            findings += find_fakematches(path, rules)
    else:
        if len(args.paths) > 1:
            parser.error("expected at most one base ref (did you mean --all?)")
        merge_base = find_merge_base(args.paths[0] if args.paths else "origin/main")
        for path, added_lines in sorted(get_added_lines(merge_base).items()):
            for finding in find_fakematches(path, rules):
                if finding.line_number in added_lines:
                    findings.append(finding)

    return report(findings)


if __name__ == "__main__":
    sys.exit(main())
