#!/usr/bin/env python3
"""Show the state of one translation unit.

Usage: python tools/decomp/unit_status.py <TU> [--unmatched] [--mangled]

<TU> can be e.g. GSmaterial, gs/scene/GSmaterial or src/gs/scene/GSmaterial.cpp.

Prints the unit's configure.py status, source file, split ranges and scores
(baseline.json vs report.json), then every target function in retail order:
address, size, baseline and current fuzzy match, and the line where the
source defines it. "-" means no score (the function is unpaired, usually
because it has no source yet or its symbols.txt name doesn't match the
source; a line number next to "-" means the latter). Line numbers are found
by name, so overloads are assigned to definitions in the order they appear,
which assumes the source keeps retail order. Also lists source functions that
have no target symbol, which usually means the symbols.txt entry still needs
renaming.

Scores come from build/RPBP01/report.json, which only `ninja` (or
`ninja build/RPBP01/report.json`) updates.
"""

from pathlib import Path
from typing import Dict, List, Optional, Set
import argparse
import re
import sys

from common import (
    BUILD_DIR,
    ROOT,
    Function,
    Unit,
    Units,
    get_demangled_name,
    get_elf_symbols,
    get_report_unit_entry,
    get_unit_object_path,
    get_virtual_address,
    load_report,
    parse_splits,
    resolve_unit,
)

REPORT_PATH = BUILD_DIR / "report.json"
BASELINE_PATH = BUILD_DIR / "baseline.json"


def get_configure_status(unit: str) -> str:
    """The unit's Matching/NonMatching flag in configure.py, with its line."""
    relative_path = re.sub(r"^src/", "", unit)
    # e.g. `Object(NonMatching, "gs/GSmem.cpp")`
    pattern = re.compile(r'Object\(\s*(\w+)\s*,\s*"' + re.escape(relative_path) + '"')

    lines = (ROOT / "configure.py").read_text(encoding="utf-8").splitlines()
    for line_number, line in enumerate(lines, 1):
        match = pattern.search(line)
        if match:
            return f"{match[1]} (configure.py:{line_number})"
    return "not in configure.py"


def find_definition_line(
    source_lines: List[str], function: Function, taken_lines: Set[int]
) -> Optional[int]:
    """Line of the function's definition in the source, from its demangled name.

    Skips lines in `taken_lines`, so that when called in retail order,
    overloads are matched to their definitions in order.
    """
    demangled = get_demangled_name(function)

    # `void GSfoo::bar(int)` -> `GSfoo::bar`
    if "(" in demangled:
        qualified_name = demangled.split("(", 1)[0].split()[-1]
    else:
        qualified_name = demangled
    pattern = re.compile(r"(^|[\s*&])" + re.escape(qualified_name) + r"\s*\(")

    for line_number, line in enumerate(source_lines, 1):
        if line_number in taken_lines:
            continue
        # Definitions start at column 0; skip indented code,
        # preprocessor lines, comments and declarations
        is_indented = line[:1].isspace()
        is_directive_or_comment = line.startswith(("#", "/"))
        is_declaration = line.rstrip().endswith(";")
        if is_indented or is_directive_or_comment or is_declaration:
            continue
        if pattern.search(line):
            return line_number
    return None


def find_definition_lines(
    source_lines: List[str], functions: List[Function]
) -> Dict[str, Optional[int]]:
    """Definition line of each function (by mangled name), in retail order."""
    taken_lines: Set[int] = set()
    lines = {}
    for function in functions:
        line = find_definition_line(source_lines, function, taken_lines)
        if line is not None:
            taken_lines.add(line)
        lines[function["name"]] = line
    return lines


def format_match_percent(function: Optional[Function]) -> str:
    """A function's fuzzy match as shown in the table ("-" if unscored)."""
    if function is None:
        return "-"
    percent = function.get("fuzzy_match_percent")
    if percent is None:
        return "-"
    if percent == 100:
        return "100"
    # Never round up to 100.0 for a function that isn't a full match
    return f"{min(percent, 99.9):.1f}"


def format_unit_scores(unit: Optional[Unit]) -> str:
    if unit is None:
        return "n/a"
    measures = unit["measures"]
    fuzzy = measures.get("fuzzy_match_percent", 0)
    code = measures.get("matched_code_percent", 0)
    matched_functions = measures.get("matched_functions", 0)
    total_functions = measures.get("total_functions", 0)
    return (
        f"fuzzy {fuzzy:.2f}%, code {code:.2f}%, "
        f"functions {matched_functions}/{total_functions}"
    )


def read_source_lines(source_path: Path) -> List[str]:
    if not source_path.exists():
        return []
    return source_path.read_text(encoding="utf-8", errors="replace").splitlines()


def is_newer(path: Path, than: Path) -> bool:
    """Whether both files exist and `path` was modified after `than`."""
    if not path.exists() or not than.exists():
        return False
    return path.stat().st_mtime > than.stat().st_mtime


def print_summary(
    unit: str,
    units: Units,
    source_lines: List[str],
    current: Optional[Unit],
    baseline: Optional[Unit],
) -> None:
    source_path = ROOT / unit
    object_path = get_unit_object_path(unit)

    print(f"{unit}: {get_configure_status(unit)}")

    if source_path.exists():
        print(f"  source:   {unit} ({len(source_lines)} lines)")
    else:
        print("  source:   none yet")

    section_width = max(len(entry.section) for entry in units[unit])
    for i, entry in enumerate(units[unit]):
        heading = "splits:" if i == 0 else ""
        print(
            f"  {heading:9} {entry.section:{section_width}}"
            f"  0x{entry.start:08X}-0x{entry.end:08X}"
        )

    baseline_line = f"  baseline: {format_unit_scores(baseline)}"
    if not BASELINE_PATH.exists():
        baseline_line += " (run `ninja baseline`)"
    print(baseline_line)

    current_line = f"  current:  {format_unit_scores(current)}"
    if not REPORT_PATH.exists():
        current_line += " (run `ninja`)"
    print(current_line)

    # Staleness hints (based on modification times; a rebuild clears them)
    if is_newer(source_path, than=object_path):
        print(
            "  note: the source changed after the unit was last built; scores are stale until you rebuild"
        )
    if is_newer(object_path, than=REPORT_PATH):
        print(
            "  note: report.json is older than the unit's object; run `ninja build/RPBP01/report.json`"
        )


def print_function_table(
    functions: List[Function],
    baseline: Optional[Unit],
    source_lines: List[str],
    unmatched_only: bool,
    show_mangled: bool,
) -> None:
    baseline_functions = {}
    if baseline is not None:
        for function in baseline.get("functions", []):
            baseline_functions[function["name"]] = function

    # Found for every function, including hidden ones, so that overloads are
    # matched in order
    definition_lines = find_definition_lines(source_lines, functions)

    rows = []
    for function in functions:
        current_percent = format_match_percent(function)
        if unmatched_only and current_percent == "100":
            continue

        baseline_percent = format_match_percent(
            baseline_functions.get(function["name"])
        )
        address = get_virtual_address(function)
        size = int(function["size"])
        line = definition_lines[function["name"]]
        line_text = "-" if line is None else str(line)
        if show_mangled:
            name = function["name"]
        else:
            name = get_demangled_name(function)
        rows.append(
            f"  {address:08X} {size:6X} {baseline_percent:>6} {current_percent:>6} {line_text:>5}  {name}"
        )

    print(f"\n  {'address':8} {'size':>6} {'base':>6} {'now':>6} {'line':>5}  function")
    if rows:
        print("\n".join(rows))
    else:
        print("  (none)")


def print_unpaired_source_functions(unit: str, functions: List[Function]) -> None:
    """List functions in the built object that no target function pairs with."""
    object_path = get_unit_object_path(unit)
    if not object_path.exists():
        return

    target_names = {function["name"] for function in functions}
    unpaired = sorted(
        name
        for name, symbol in get_elf_symbols(object_path).items()
        if symbol.kind == "func"
        and name not in target_names
        and not name.startswith("@")  # compiler-generated
    )
    if not unpaired:
        return

    print(
        "\n  Source functions with no target symbol (needs a symbols.txt rename, or not in retail):"
    )
    for name in unpaired:
        print(f"    {name}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("unit")
    parser.add_argument(
        "--unmatched", action="store_true", help="only list functions below 100%%"
    )
    parser.add_argument(
        "--mangled", action="store_true", help="show mangled names instead of demangled"
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()

    units = parse_splits()
    try:
        unit = resolve_unit(args.unit, units)
    except ValueError as error:
        sys.exit(f"error: {error}")

    current = get_report_unit_entry(load_report("report.json"), unit)
    baseline = get_report_unit_entry(load_report("baseline.json"), unit)
    source_lines = read_source_lines(ROOT / unit)

    print_summary(unit, units, source_lines, current, baseline)

    if current is None:
        print("  (unit not found in report.json)")
        return 0

    functions = sorted(current.get("functions", []), key=get_virtual_address)
    print_function_table(
        functions,
        baseline,
        source_lines,
        unmatched_only=args.unmatched,
        show_mangled=args.mangled,
    )
    print_unpaired_source_functions(unit, functions)
    return 0


if __name__ == "__main__":
    sys.exit(main())
