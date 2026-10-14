#!/usr/bin/env python3
"""Lint changes on this branch against the merge base with <base_ref>.

Usage: python tools/decomp/lint.py [<base_ref>]   (default base: origin/main)

Checks lines added under src/ and include/ for fakematch constructs.

Exits 1 if any error is found.
"""

from typing import Iterator, List, Tuple
import argparse
import re
import subprocess
import sys

PATHS = ["src", "include"]  # game code only; libs/ (SDK, runtime) is exempt

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
    print(f"{results.error_count} error(s), {results.warning_count} warning(s)")
    return 1 if results.error_count else 0


if __name__ == "__main__":
    sys.exit(main())
