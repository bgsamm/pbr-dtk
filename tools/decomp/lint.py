#!/usr/bin/env python3
"""Lint changes on this branch against the merge base with <base_ref>.

Usage: python tools/decomp/lint.py [<base_ref>]   (default base: origin/main)

Checks:
  * Fakematch constructs in lines added under src/ and include/.
  * Edits to config/RPBP01/symbols.txt. Allowed per existing entry:
      - renaming it,
      - changing its size attribute,
      - changing its scope attribute.
    Not allowed: adding or removing entries, changing an address or section,
    or any other attribute change. A name may appear more than once only if
    every entry with that name is scope:local and they are all in different
    units. A renamed entry whose unit has a built object that doesn't define
    the new name gets a warning (usually a typo or a mis-escaped name).

Exits 1 if any error is found.
"""

from typing import Dict, Iterator, List, Optional, Tuple
import argparse
import re
import subprocess
import sys

from common import (
    ROOT,
    ElfSymbol,
    SymbolEntry,
    find_unit_containing,
    get_elf_symbols,
    get_unit_object_path,
    parse_splits,
    parse_symbols,
)

PATHS = ["src", "include"]  # game code only; libs/ (SDK, runtime) is exempt
SYMBOLS = "config/RPBP01/symbols.txt"

# (regex, label) pairs checked against each added line of code
ERROR_PATTERNS: List[Tuple[str, str]] = []
WARNING_PATTERNS = [
    (r"\b(asm|__asm)\b", "inline asm"),
    (r"#\s*pragma\b(?!\s+once)", "#pragma in source"),
    (r"\bvolatile\b", "volatile"),
    (r"\bregister\b", "register"),
    (r"\bgoto\b", "goto"),
    (r"__declspec\s*\(\s*section", "section forcing"),
    (r"\(\s*[\w:]+\s*\*\s*\)\s*0x8[0-9A-Fa-f]{7}\b", "hard-coded address"),
    (
        r"\*\s*\(\s*(f32|f64|float|double|u32|s32|int)\s*\*\s*\)\s*&",
        "type-punned dereference",
    ),
]


class LintResults:
    """Prints problems as they are found, and counts them."""

    def __init__(self) -> None:
        self.error_count = 0
        self.warning_count = 0

    def add_error(self, location: str, message: str) -> None:
        print(f"ERROR {location}: {message}")
        self.error_count += 1

    def add_warning(self, location: str, message: str) -> None:
        print(f"WARN  {location}: {message}")
        self.warning_count += 1


def run_git(*args: str) -> str:
    result = subprocess.run(["git", *args], capture_output=True, text=True, check=True)
    return result.stdout


# --------------------------------------------------------------------------
# Fakematch constructs in added source lines


def mark_new_files_as_intended() -> None:
    """Make untracked files under PATHS show up in `git diff`."""
    subprocess.run(["git", "add", "--intent-to-add", *PATHS], check=True)


def find_merge_base(base: str) -> str:
    try:
        return run_git("merge-base", "HEAD", base).strip()
    except subprocess.CalledProcessError as error:
        sys.exit(
            f"error: couldn't find the merge base of HEAD and {base}: "
            f"{error.stderr.strip()}"
        )


def iter_added_lines(merge_base: str) -> Iterator[Tuple[str, int, str]]:
    """(path, line number, text) for each line added since the merge base."""
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
            # e.g. `+#include "common.hpp"`
            yield path, line_number, line[1:]
            line_number += 1


def lint_fakematches(merge_base: str, results: LintResults) -> None:
    mark_new_files_as_intended()
    for path, line_number, text in iter_added_lines(merge_base):
        location = f"{path}:{line_number}"
        code = text.split("//", 1)[0]
        for pattern, label in ERROR_PATTERNS:
            if re.search(pattern, code):
                results.add_error(location, f"{label}: {code.strip()}")
        for pattern, label in WARNING_PATTERNS:
            if re.search(pattern, code):
                results.add_warning(location, f"{label}: {code.strip()}")


# --------------------------------------------------------------------------
# symbols.txt edits

# (section, address, n) for the n-th entry at that address
EntryKey = Tuple[str, int, int]


def key_entries_by_address(entries: List[SymbolEntry]) -> Dict[EntryKey, SymbolEntry]:
    """Key entries by position, so old and new entries can be paired up
    regardless of renames."""
    count_at_address: Dict[Tuple[str, int], int] = {}
    keyed = {}
    for entry in entries:
        location = (entry.section, entry.address)
        n = count_at_address.get(location, 0)
        count_at_address[location] = n + 1
        keyed[(entry.section, entry.address, n)] = entry
    return keyed


def is_local_scope(entry: SymbolEntry) -> bool:
    return "scope:local" in entry.attributes


def get_fixed_attributes(entry: SymbolEntry) -> List[str]:
    """The attributes that must not change (all but size and scope)."""
    return [
        attribute
        for attribute in entry.attributes
        if not attribute.startswith(("size:", "scope:"))
    ]


def is_unchanged(old: SymbolEntry, new: SymbolEntry) -> bool:
    """Whether the entry's name, section, address and attributes are the same
    (its line number may differ)."""
    return (old.name, old.section, old.address, old.attributes) == (
        new.name,
        new.section,
        new.address,
        new.attributes,
    )


def describe_entry(entry: SymbolEntry) -> str:
    return f"{entry.name} ({entry.section}:0x{entry.address:08X})"


class RenameChecker:
    """Checks renamed symbols.txt entries against built objects and each other."""

    def __init__(self, new_entries: List[SymbolEntry], results: LintResults):
        self.results = results
        self.units = parse_splits()
        self.object_symbols: Dict[str, Dict[str, ElfSymbol]] = {}  # by unit
        self.entries_by_name: Dict[str, List[SymbolEntry]] = {}
        for entry in new_entries:
            self.entries_by_name.setdefault(entry.name, []).append(entry)

    def find_unit(self, entry: SymbolEntry) -> Optional[str]:
        return find_unit_containing(entry.section, entry.address, self.units)

    def get_object_symbols(self, unit: str) -> Optional[Dict[str, ElfSymbol]]:
        """The symbols in the unit's built object (cached), or None if unbuilt."""
        if unit not in self.object_symbols:
            object_path = get_unit_object_path(unit)
            if not object_path.exists():
                return None
            self.object_symbols[unit] = get_elf_symbols(object_path)
        return self.object_symbols[unit]

    def check(self, old: SymbolEntry, new: SymbolEntry, location: str) -> None:
        print(f"INFO  {location}: renamed {old.name} -> {new.name}")
        label = describe_entry(old)
        self.check_defined_in_object(new, location, label)
        self.check_duplicates(new, location, label)

    def check_defined_in_object(
        self, entry: SymbolEntry, location: str, label: str
    ) -> None:
        unit = self.find_unit(entry)
        if unit is None:
            return
        symbols = self.get_object_symbols(unit)
        if symbols is not None and entry.name not in symbols:
            self.results.add_warning(
                location,
                f"{label}: renamed to {entry.name}, but {unit}'s object doesn't "
                "define it (check the spelling and escaping, or rebuild)",
            )

    def check_duplicates(self, entry: SymbolEntry, location: str, label: str) -> None:
        duplicates = self.entries_by_name[entry.name]
        if len(duplicates) <= 1:
            return

        if not all(is_local_scope(duplicate) for duplicate in duplicates):
            self.results.add_error(
                location,
                f"{label}: name {entry.name} is used {len(duplicates)} times; "
                "duplicates must all be scope:local",
            )
            return

        units = [self.find_unit(duplicate) for duplicate in duplicates]
        any_outside_unit = None in units
        any_share_unit = len(set(units)) != len(units)
        if any_outside_unit or any_share_unit:
            self.results.add_error(
                location,
                f"{label}: name {entry.name} is used more than once in the same unit (or outside any unit)",
            )


def find_moved_entries(
    removed: List[SymbolEntry], added: List[SymbolEntry]
) -> List[Tuple[SymbolEntry, SymbolEntry]]:
    """(old, new) pairs of removed and added entries that are the same symbol
    at a different address or section, i.e. their name is unique in both lists."""
    removed_names = [entry.name for entry in removed]
    added_names = [entry.name for entry in added]
    moved = []
    for old in removed:
        if removed_names.count(old.name) != 1 or added_names.count(old.name) != 1:
            continue
        new = added[added_names.index(old.name)]
        moved.append((old, new))
    return moved


def lint_symbols(merge_base: str, results: LintResults) -> None:
    try:
        old_text = run_git("show", f"{merge_base}:{SYMBOLS}")
    except subprocess.CalledProcessError as error:
        results.add_error(
            SYMBOLS,
            "couldn't read it at the merge base, so its edits weren't checked: "
            + error.stderr.strip(),
        )
        return
    new_text = (ROOT / SYMBOLS).read_text(encoding="utf-8")
    if old_text.replace("\r", "") == new_text.replace("\r", ""):
        return

    old_entries, old_other_lines = parse_symbols(old_text)
    new_entries, new_other_lines = parse_symbols(new_text)

    if old_other_lines != new_other_lines:
        results.add_error(SYMBOLS, "lines other than symbol entries were changed")

    old_by_key = key_entries_by_address(old_entries)
    new_by_key = key_entries_by_address(new_entries)

    removed = [old_by_key[key] for key in sorted(old_by_key.keys() - new_by_key.keys())]
    added = [new_by_key[key] for key in sorted(new_by_key.keys() - old_by_key.keys())]

    for old, new in find_moved_entries(removed, added):
        removed.remove(old)
        added.remove(new)
        results.add_error(
            f"{SYMBOLS}:{new.line_number}",
            f"entry's address/section changed: {old.name} "
            f"({old.section}:0x{old.address:08X} -> {new.section}:0x{new.address:08X})",
        )
    for entry in removed:
        results.add_error(
            SYMBOLS,
            f"entry removed or its address/section changed: {describe_entry(entry)}",
        )
    for entry in added:
        results.add_error(
            f"{SYMBOLS}:{entry.line_number}",
            f"entry added or its address/section changed: {describe_entry(entry)}",
        )

    rename_checker = RenameChecker(new_entries, results)
    for key in sorted(old_by_key.keys() & new_by_key.keys()):
        old, new = old_by_key[key], new_by_key[key]
        if is_unchanged(old, new):
            continue

        location = f"{SYMBOLS}:{new.line_number}"
        if get_fixed_attributes(old) != get_fixed_attributes(new):
            results.add_error(
                location,
                f"{describe_entry(old)}: only size and scope may change; attributes went from "
                f"'{' '.join(old.attributes)}' to '{' '.join(new.attributes)}'",
            )
        if new.name != old.name:
            rename_checker.check(old, new, location)


# --------------------------------------------------------------------------


def main() -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "base", nargs="?", default="origin/main", help="base ref (default: origin/main)"
    )
    args = parser.parse_args()

    merge_base = find_merge_base(args.base)
    results = LintResults()
    lint_fakematches(merge_base, results)
    lint_symbols(merge_base, results)
    print(f"{results.error_count} error(s), {results.warning_count} warning(s)")
    return 1 if results.error_count else 0


if __name__ == "__main__":
    sys.exit(main())
