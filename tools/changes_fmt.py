#!/usr/bin/env python3

from argparse import ArgumentParser
import os
import json
from pathlib import Path
from typing import Optional, Tuple

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.abspath(os.path.join(script_dir, ".."))


UNIT_KEYS_TO_DIFF = [
    "fuzzy_match_percent",
    "matched_code_percent",
    "matched_data_percent",
    "complete_code_percent",
    "complete_data_percent",
]

FUNCTION_KEYS_TO_DIFF = [
    "fuzzy_match_percent",
]

Change = Tuple[str, str, float, float]


def format_float(value: float) -> str:
    if value < 100.0 and value > 99.99:
        value = 99.99
    return "%6.2f" % value


def pair_renames(functions: list[dict]) -> Tuple[list[dict], list[Tuple[dict, dict]]]:
    """Pair functions that disappeared with ones that appeared at the same address.

    objdiff pairs baseline and current functions by name, so a function renamed in
    symbols.txt shows up as one function removed (no "to") and one added (no "from").
    Matching those by virtual address turns them back into a single renamed function.
    Returns the remaining functions and the (old, new) pairs.
    """

    def vaddr(func: dict) -> Optional[int]:
        value = func.get("metadata", {}).get("virtual_address")
        return int(value) if value is not None else None

    removed: dict[int, list[dict]] = {}
    added: dict[int, list[dict]] = {}
    for func in functions:
        addr = vaddr(func)
        if addr is None:
            continue
        if "to" not in func and "from" in func:
            removed.setdefault(addr, []).append(func)
        elif "from" not in func and "to" in func:
            added.setdefault(addr, []).append(func)

    pairs = []
    paired = set()
    for addr, olds in removed.items():
        news = added.get(addr, [])
        if len(olds) == 1 and len(news) == 1:  # skip anything ambiguous
            pairs.append((olds[0], news[0]))
            paired.update((id(olds[0]), id(news[0])))
    rest = [func for func in functions if id(func) not in paired]
    return rest, pairs


def get_changes(changes_file: str) -> Tuple[list[Change], list[Change], list[Change]]:
    changes_file = os.path.relpath(changes_file, root_dir)
    with open(changes_file, "r") as f:
        changes_json = json.load(f)

    regressions = []
    progressions = []
    renames = []

    def diff_key(object_name: Optional[str], object: dict, key: str):
        from_value = object.get("from", {}).get(key, 0.0)
        to_value = object.get("to", {}).get(key, 0.0)
        key = key.removesuffix("_percent")
        change = (object_name, key, from_value, to_value)
        if from_value > to_value:
            regressions.append(change)
        elif to_value > from_value:
            progressions.append(change)

    for key in UNIT_KEYS_TO_DIFF:
        diff_key(None, changes_json, key)

    for unit in changes_json.get("units", []):
        unit_name = unit["name"]
        for key in UNIT_KEYS_TO_DIFF:
            diff_key(unit_name, unit, key)
        # Ignore sections
        functions, pairs = pair_renames(unit.get("functions", []))
        for func in functions:
            func_name = func["name"]
            for key in FUNCTION_KEYS_TO_DIFF:
                diff_key(func_name, func, key)
        for old, new in pairs:
            func_name = f"{old['name']} -> {new['name']}"
            merged = {"from": old.get("from", {}), "to": new.get("to", {})}
            count = len(regressions) + len(progressions)
            for key in FUNCTION_KEYS_TO_DIFF:
                diff_key(func_name, merged, key)
            if len(regressions) + len(progressions) == count:  # score unchanged
                value = merged["to"].get("fuzzy_match_percent", 0.0)
                renames.append((func_name, "renamed", value, value))

    return regressions, progressions, renames


def generate_changes_plaintext(changes: list[Change]) -> str:
    if len(changes) == 0:
        return ""

    table_total_width = 136
    percents_max_len = 7 + 4 + 7
    key_max_len = max(len(key) for _, key, _, _ in changes)
    name_max_len = max(len(name or "Total") for name, _, _, _ in changes)
    max_width_for_name_col = table_total_width - 3 - key_max_len - 3 - percents_max_len
    name_max_len = min(max_width_for_name_col, name_max_len)

    out_lines = []
    for name, key, from_value, to_value in changes:
        if name is None:
            name = "Total"
        if len(name) > name_max_len:
            name = name[: name_max_len - len("[...]")] + "[...]"
        out_lines.append(
            f"{name:>{name_max_len}} | {key:<{key_max_len}} | {format_float(from_value)}% -> {format_float(to_value)}%"
        )

    return "\n".join(out_lines)


def generate_changes_markdown(changes: list[Change], description: str) -> str:
    if len(changes) == 0:
        return ""

    out_lines = []
    name_max_len = 100

    out_lines.append("<details>")
    out_lines.append(
        f"<summary>Detected {len(changes)} {description} compared to the base:</summary>"
    )
    out_lines.append("")  # Must include a blank line before a table
    out_lines.append("| Name | Type | Before | After |")
    out_lines.append("| ---- | ---- | ------ | ----- |")

    for name, key, from_value, to_value in changes:
        if name is None:
            name = "Total"
        else:
            if len(name) > name_max_len:
                name = name[: name_max_len - len("...")] + "..."
            name = f"`{name}`"  # Surround with backticks
        key = key.replace("_", " ").capitalize()
        out_lines.append(
            f"| {name} | {key} | {format_float(from_value)}% | {format_float(to_value)}% |"
        )

    out_lines.append("</details>")

    return "\n".join(out_lines)


def main():
    parser = ArgumentParser(description="Format objdiff-cli report changes.")
    parser.add_argument(
        "report_changes_file",
        type=Path,
        help="""path to the JSON file containing the changes, generated by objdiff-cli.""",
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        help="""Output file (prints to console if unspecified)""",
    )
    parser.add_argument(
        "--all",
        action="store_true",
        help="""Includes progressions as well.""",
    )
    args = parser.parse_args()

    regressions, progressions, renames = get_changes(args.report_changes_file)

    if args.output:
        markdown_output = generate_changes_markdown(regressions, "regressions")
        if args.all:
            markdown_output += generate_changes_markdown(progressions, "progressions")
            markdown_output += generate_changes_markdown(renames, "renames")
        with open(args.output, "w", encoding="utf-8") as f:
            f.write(markdown_output)
    else:
        if args.all:
            changes = progressions + renames + regressions
        else:
            changes = regressions
        text_output = generate_changes_plaintext(changes)
        print(text_output)


if __name__ == "__main__":
    main()
