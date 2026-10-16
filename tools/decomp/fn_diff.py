#!/usr/bin/env python3
"""Show a compact, aligned target-vs-source diff of one function.

Uses objdiff-cli's one-shot JSON output, so rows are aligned with the same
algorithm that produces the match scores in report.json.

Usage:
    python tools/decomp/fn_diff.py <symbol> [-u <unit>] [--context <N>]
    python tools/decomp/fn_diff.py <symbol> --target
    python tools/decomp/fn_diff.py <symbol> --json <path> [...]

<symbol> is the mangled name (e.g. __ct__7GSsceneFP11GSsceneData) or the
demangled one (e.g. "GSscene::GSscene(GSsceneData*)").

The header shows the match % and how many rows carry each marker. Branch
targets are shown as labels (.L_<address> on the target side, matching the
.s files; .L_<offset> on the source side), and float/double loads show the
loaded value. Without source for the function, or with --target, only the
target asm is printed.

Row markers:
    (space) identical    a  argument differs    o  opcode differs
    r  replaced          +  only in source      -  only in target
    n  (with --hide-name-diffs) only the symbol differs, and its value can't
       be compared because it isn't read-only data or isn't known
"""

from collections import Counter
from pathlib import Path
from typing import Literal, NotRequired, Optional, TypedDict
import argparse
import base64
import json
import re
import struct
import subprocess
import sys

from common import Report
import common

MARKERS = {
    "DIFF_NONE": " ",
    "DIFF_ARG_MISMATCH": "a",
    "DIFF_OP_MISMATCH": "o",
    "DIFF_REPLACE": "r",
    "DIFF_INSERT": "+",
    "DIFF_DELETE": "-",
}

NAME_ONLY_MARKER = "n"

TOOLS_DIR = common.ROOT / "build" / "tools"

# Data in these sections can't change at runtime, so two symbols with the same
# bytes are interchangeable
READ_ONLY_SECTIONS = {".rodata", ".sdata2", ".sbss2"}


# --------------------------------------------------------------------------
# objdiff-cli JSON output

# objdiff puts the target on the left and the source on the right
type Side = Literal["left", "right"]
TARGET: Side = "left"
SOURCE: Side = "right"


class Instruction(TypedDict):
    address: NotRequired[str]
    formatted: NotRequired[str]
    branch_dest: NotRequired[str]
    relocation: NotRequired[dict]


class InstructionDiff(TypedDict):
    # Rows without an instruction are padding opposite the other side's extra rows
    instruction: NotRequired[Instruction]
    diff_kind: NotRequired[str]


class DataSegment(TypedDict):
    data: NotRequired[str]
    size: NotRequired[str]


class Symbol(TypedDict):
    name: str
    demangled_name: NotRequired[str]
    instructions: NotRequired[list[InstructionDiff]]
    data_diff: NotRequired[list[DataSegment]]
    match_percent: NotRequired[float]


class SideSymbols(TypedDict):
    symbols: NotRequired[list[Symbol]]


type Diff = dict[Side, SideSymbols]


def get_symbols(diff: Diff, side: Side) -> list[Symbol]:
    if side not in diff:
        return []
    return diff[side].get("symbols", [])


def get_instruction(rows: list[InstructionDiff], index: int) -> Optional[Instruction]:
    """The instruction in row `index`, or None for padding or past the end."""
    if index >= len(rows):
        return None
    return rows[index].get("instruction")


def load_diff_file(json_file: Path) -> Diff:
    with open(json_file, encoding="utf-8") as f:
        return json.load(f)


def find_objdiff_cli() -> str:
    for name in ("objdiff-cli.exe", "objdiff-cli"):
        path = TOOLS_DIR / name
        if path.is_file():
            return str(path)
    sys.exit(f"objdiff-cli not found in {TOOLS_DIR}; run ninja first")


def load_report() -> Optional[Report]:
    return common.load_report("report.json") or common.load_report("baseline.json")


def is_named(function: common.Function, symbol: str) -> bool:
    """Whether `symbol` is the function's mangled or demangled name."""
    demangled = function.get("metadata", {}).get("demangled_name")
    return symbol in (function["name"], demangled)


def find_unit_for_symbol(
    report: Optional[Report], symbol: str
) -> tuple[Optional[str], str]:
    """Return (unit, mangled_name) for symbol, or (None, symbol) if unknown."""
    matches = [
        (unit["name"], function["name"])
        for unit, function in common.iter_report_functions(report)
        if is_named(function, symbol)
    ]

    if len(matches) > 1:
        units = ", ".join(unit for unit, _ in matches)
        sys.exit(f"{symbol} is in more than one unit ({units}); pass -u UNIT")

    if matches:
        return matches[0]
    return None, symbol


def get_section_address(report: Optional[Report], symbol: str) -> Optional[int]:
    """Virtual address of the target function's section, from report.json."""
    for _, function in common.iter_report_functions(report):
        metadata = function.get("metadata", {})
        if is_named(function, symbol) and "virtual_address" in metadata:
            # The function's address minus its offset within the section
            offset = int(function.get("address", 0))
            return int(metadata["virtual_address"]) - offset
    return None


def get_source_object_path(unit: Optional[str]) -> Optional[Path]:
    """The object built from the unit's source, from objdiff.json."""
    if unit is None:
        return None
    try:
        config_text = (common.ROOT / "objdiff.json").read_text(encoding="utf-8")
        config = json.loads(config_text)
    except (OSError, ValueError):
        return None
    for entry in config.get("units", []):
        if entry["name"] == unit and "base_path" in entry:
            return common.ROOT / entry["base_path"]
    return None


def run_objdiff_cli(symbol: str, unit: Optional[str]) -> Diff:
    command = [find_objdiff_cli(), "diff", "-p", ".", "-o", "-", "--format", "json"]
    if unit:
        command += ["-u", unit]
    command.append(symbol)

    result = subprocess.run(command, capture_output=True, text=True, encoding="utf-8")
    if result.returncode != 0:
        sys.exit(
            f"objdiff-cli failed (exit {result.returncode}):\n{result.stderr.strip()}"
        )
    return json.loads(result.stdout)


def find_function(diff: Diff, side: Side, symbol: str) -> Optional[Symbol]:
    for candidate in get_symbols(diff, side):
        names = (candidate["name"], candidate.get("demangled_name"))
        if symbol in names and "instructions" in candidate:
            return candidate
    return None


# --------------------------------------------------------------------------
# Values of relocated data (float constants etc.)


class DataValues:
    """Bytes behind relocated data symbols.

    Source side: data symbols in the diff JSON. Target side: data symbols in
    the diff JSON, else symbols.txt (address, size) read from the retail DOL.
    """

    def __init__(self, diff: Diff, source_object: Optional[Path]):
        self.source_object = source_object
        self.values_by_side: dict[Side, dict[str, bytes]] = {}
        for side in (TARGET, SOURCE):
            values = {}
            for symbol in get_symbols(diff, side):
                segments = symbol.get("data_diff")
                if segments:
                    values[symbol["name"]] = b"".join(
                        base64.b64decode(segment.get("data", ""))
                        for segment in segments
                    )
            self.values_by_side[side] = values

        # Loaded on first use
        self._symbols_txt: Optional[dict[str, common.SymbolEntry]] = None
        self._source_symbols: Optional[dict[str, common.ElfSymbol]] = None
        self._dol: Optional[tuple[bytes, list[tuple[int, int, int]]]] = None

    def get_bytes(self, side: Side, name: str) -> Optional[bytes]:
        value = self.values_by_side[side].get(name)
        if value is not None or side != TARGET:
            return value
        try:
            return self._read_from_dol(name)
        except (OSError, ValueError, struct.error):
            return None

    def is_read_only(self, side: Side, name: str) -> bool:
        """Whether the symbol is in a read-only data section."""
        if side == SOURCE:
            source_symbols = self._get_source_symbols()
            if name in source_symbols:
                return source_symbols[name].section in READ_ONLY_SECTIONS
        # Target symbols, and source references to symbols defined in other
        # units (which use their symbols.txt names)
        entry = self._get_symbols_txt().get(name)
        return entry is not None and entry.section in READ_ONLY_SECTIONS

    def _get_symbols_txt(self) -> dict[str, common.SymbolEntry]:
        if self._symbols_txt is None:
            entries, _ = common.parse_symbols()
            self._symbols_txt = {entry.name: entry for entry in entries}
        return self._symbols_txt

    def _get_source_symbols(self) -> dict[str, common.ElfSymbol]:
        """Symbols defined in the object built from source (empty if unbuilt)."""
        if self._source_symbols is None:
            self._source_symbols = {}
            if self.source_object is not None and self.source_object.exists():
                self._source_symbols = common.get_elf_symbols(self.source_object)
        return self._source_symbols

    def _load_dol(self) -> tuple[bytes, list[tuple[int, int, int]]]:
        """The retail DOL's bytes, and (address, size, file offset) of each section."""
        if self._dol is None:
            config = (common.CONFIG_DIR / "config.yml").read_text(encoding="utf-8")
            object_base = re.search(r"^object_base:\s*(\S+)", config, re.M)
            object_path = re.search(r"^object:\s*(\S+)", config, re.M)
            if object_path is None:
                raise ValueError("no object in config.yml")
            if object_base:
                dol_path = common.ROOT / object_base[1] / object_path[1]
            else:
                dol_path = common.ROOT / object_path[1]

            data = dol_path.read_bytes()
            sections = []
            for i in range(18):  # 7 text + 11 data sections
                # The header holds 18 file offsets, then 18 addresses, then 18 sizes
                file_offset = struct.unpack_from(">I", data, 0x00 + i * 4)[0]
                address = struct.unpack_from(">I", data, 0x48 + i * 4)[0]
                size = struct.unpack_from(">I", data, 0x90 + i * 4)[0]
                if size:
                    sections.append((address, size, file_offset))
            self._dol = (data, sections)
        return self._dol

    def _read_from_dol(self, name: str) -> Optional[bytes]:
        entry = self._get_symbols_txt().get(name)
        if entry is None or not entry.size:
            return None
        address, size = entry.address, entry.size

        data, sections = self._load_dol()
        for section_address, section_size, file_offset in sections:
            section_end = section_address + section_size
            if section_address <= address and address + size <= section_end:
                start = file_offset + (address - section_address)
                return data[start : start + size]
        return None


SAVE_RESTORE_HELPER = re.compile(r"^_(?:save|rest)[gf]pr_\d+$")
RELOCATION_SUFFIX = re.compile(r"@(?:ha|h|l|sda21|sda2)$")
NOT_A_SYMBOL = re.compile(r"^(?:[rf]\d+|cr\d|-?0x[0-9a-fA-F]+|-?\d+|\.L_\w+)$")


def get_relocation_target(instruction: Optional[Instruction]) -> Optional[str]:
    """Name of the symbol a relocated instruction refers to, from its text."""
    if instruction is None or "relocation" not in instruction:
        return None

    # e.g. `lfs f1, @6897@sda21(r2)` -> operands `f1`, `@6897@sda21`, `r2`
    text = instruction.get("formatted", "")
    operands = text.split(None, 1)[1] if " " in text else ""
    for token in re.split(r"[\s,()]+", operands):
        token = re.sub(r"[+-]0x[0-9a-fA-F]+$", "", token)  # drop `+0x10` etc.
        token = RELOCATION_SUFFIX.sub("", token)
        if token and not NOT_A_SYMBOL.match(token):
            return token
    return None


def format_loaded_value(mnemonic: str, value: bytes) -> Optional[str]:
    """The float or double a load instruction reads, as source-like text."""
    if mnemonic.startswith("lfs") and len(value) >= 4:
        raw = value[:4]
        number = struct.unpack(">f", raw)[0]
        # Use the shortest text that converts back to the same f32
        for digits in range(1, 10):
            text = f"{number:.{digits}g}"
            if struct.pack(">f", float(text)) == raw:
                return f"{text}f"
    if mnemonic.startswith("lfd") and len(value) >= 8:
        return repr(struct.unpack(">d", value[:8])[0])
    return None


# --------------------------------------------------------------------------
# Rendering


class SideView:
    """Text for one side's rows: branch targets as labels, values appended."""

    def __init__(
        self,
        side: Side,
        rows: list[InstructionDiff],
        values: DataValues,
        section_address: Optional[int],
    ):
        self.side: Side = side
        self.rows = rows
        self.values = values
        self.section_address = section_address
        self.branch_targets = {
            int(row["instruction"]["branch_dest"])
            for row in rows
            if "instruction" in row and "branch_dest" in row["instruction"]
        }

    def make_label(self, offset: int) -> str:
        if self.section_address is not None:
            return f".L_{self.section_address + offset:08X}"
        return f".L_{offset:x}"

    def get_label(self, index: int) -> str:
        """`.L_xxx:` if row `index` is a branch target, else ""."""
        instruction = get_instruction(self.rows, index)
        if instruction is None:
            return ""
        offset = int(instruction.get("address", 0))
        if offset not in self.branch_targets:
            return ""
        return self.make_label(offset) + ":"

    def get_offset_text(self, index: int) -> str:
        instruction = get_instruction(self.rows, index)
        if instruction is None:
            return ""
        return f"{int(instruction.get('address', 0)):04x}"

    def get_text(self, index: int) -> str:
        instruction = get_instruction(self.rows, index)
        if instruction is None:
            return ""
        text = instruction.get("formatted", "")

        # Replace the branch target's raw offset with its label
        if "branch_dest" in instruction:
            target = int(instruction["branch_dest"])
            before, found, _ = text.rpartition(f"0x{target:x}")
            if found:
                text = before + self.make_label(target)

        # Append the value of a loaded float/double constant
        name = get_relocation_target(instruction)
        if name:
            value = self.values.get_bytes(self.side, name)
            mnemonic = text.split(None, 1)[0]
            shown = format_loaded_value(mnemonic, value) if value else None
            if shown:
                text += f"  ; {shown}"
        return text

    def get_text_without_symbol(self, index: int) -> Optional[str]:
        """Text with the relocated symbol's name blanked out, so that rows
        differing only in the symbol compare equal."""
        instruction = get_instruction(self.rows, index)
        name = get_relocation_target(instruction)
        if not instruction or not name:
            return None
        return instruction.get("formatted", "").replace(name, "<symbol>", 1)

    def get_read_only_value(self, index: int) -> Optional[bytes]:
        """Bytes of the relocated symbol, if it is read-only and known."""
        name = get_relocation_target(get_instruction(self.rows, index))
        if not name or not self.values.is_read_only(self.side, name):
            return None
        return self.values.get_bytes(self.side, name)


def print_target(target: Symbol, view: SideView) -> None:
    rows = target.get("instructions", [])
    indices = [i for i in range(len(rows)) if get_instruction(rows, i)]
    print(f"{len(indices)} instructions")
    for i in indices:
        label = view.get_label(i)
        if label:
            print(label)
        print(f"    {view.get_text(i)}".rstrip())


def count_calls(rows: list[InstructionDiff]) -> Counter:
    """How often each function is called (`bl`, or `b` for a tail call)."""
    calls: Counter = Counter()
    for i in range(len(rows)):
        instruction = get_instruction(rows, i)
        if instruction is None or "relocation" not in instruction:
            continue
        mnemonic, _, operands = instruction.get("formatted", "").partition(" ")
        if mnemonic in ("bl", "b"):
            calls[operands.strip()] += 1
    return calls


def separate_save_restore_helpers(calls: Counter) -> tuple[Counter, list[str]]:
    """Split MWCC's register save/restore helpers, which aren't real calls,
    from the other calls."""
    helpers = sorted(name for name in calls if SAVE_RESTORE_HELPER.match(name))
    other_calls = Counter(
        {name: count for name, count in calls.items() if name not in helpers}
    )
    return other_calls, helpers


def print_calls(
    target_rows: list[InstructionDiff],
    source_rows: Optional[list[InstructionDiff]],
) -> None:
    target_calls, target_helpers = separate_save_restore_helpers(
        count_calls(target_rows)
    )
    helpers_text = f"target {', '.join(target_helpers) or 'none'}"

    if source_rows is None:
        print(f"Register save/restore: {helpers_text}")
        print("Calls  (target)")
        if not target_calls:
            print("  (none)")
        for name in sorted(target_calls):
            print(f"  {target_calls[name]:3}  {name}")
        return

    source_calls, source_helpers = separate_save_restore_helpers(
        count_calls(source_rows)
    )
    helpers_text += f"; source {', '.join(source_helpers) or 'none'}"
    print(f"Register save/restore: {helpers_text}")
    print("Calls  (target, source)")
    if not target_calls and not source_calls:
        print("  (none)")
    for name in sorted(set(target_calls) | set(source_calls)):
        print(f"  {target_calls[name]:3} {source_calls[name]:3}  {name}")


def get_row_marker(
    index: int,
    target_rows: list[InstructionDiff],
    source_rows: list[InstructionDiff],
) -> str:
    target_row = target_rows[index] if index < len(target_rows) else {}
    source_row = source_rows[index] if index < len(source_rows) else {}
    kind = source_row.get("diff_kind") or target_row.get("diff_kind") or "DIFF_NONE"
    return MARKERS.get(kind, "?")


def classify_argument_diff(
    index: int, target_view: SideView, source_view: SideView
) -> str:
    """The marker for an 'a' row, with --hide-name-diffs.

    A row that differs only in which symbol it references is " " (identical)
    if both symbols are read-only with the same value, or NAME_ONLY_MARKER if
    their values can't be compared. Any other row stays "a".
    """
    target_text = target_view.get_text_without_symbol(index)
    source_text = source_view.get_text_without_symbol(index)
    if target_text is None or target_text != source_text:
        return "a"

    target_value = target_view.get_read_only_value(index)
    source_value = source_view.get_read_only_value(index)
    if target_value is None or source_value is None:
        return NAME_ONLY_MARKER
    return " " if target_value == source_value else "a"


def summarize_markers(markers: list[str], hidden_count: int) -> str:
    counts = Counter(markers)
    parts = []
    for marker in [*MARKERS.values(), NAME_ONLY_MARKER]:
        if counts[marker]:
            name = "identical" if marker == " " else marker
            parts.append(f"{name} {counts[marker]}")
    summary = ", ".join(parts)
    if hidden_count:
        summary += f" ({hidden_count} name-only 'a' rows counted as identical)"
    return summary


def select_rows_to_show(markers: list[str], context: Optional[int]) -> list[int]:
    """All rows, or with `context`, only differing rows and their neighbours."""
    if context is None:
        return list(range(len(markers)))
    selected = set()
    for i, marker in enumerate(markers):
        if marker != " ":
            first = max(0, i - context)
            last = min(len(markers) - 1, i + context)
            selected.update(range(first, last + 1))
    return sorted(selected)


def print_diff(
    target: Symbol,
    source: Optional[Symbol],
    values: DataValues,
    section_address: Optional[int],
    context: Optional[int] = None,
    target_only: bool = False,
    hide_name_diffs: bool = False,
    calls: bool = False,
) -> None:
    target_rows = target.get("instructions", [])
    source_rows = source.get("instructions", []) if source else []

    demangled_name = target.get("demangled_name")
    title = f"{demangled_name} [{target['name']}]" if demangled_name else target["name"]
    if source is None:
        match_text = "missing from source"
    else:
        match_text = f"{source.get('match_percent', 0):.2f}%"
    print(f"{title}  match: {match_text}")

    if calls:
        print_calls(target_rows, source_rows if source else None)
        return

    target_view = SideView(TARGET, target_rows, values, section_address)
    if source is None or target_only:
        print_target(target, target_view)
        return
    source_view = SideView(SOURCE, source_rows, values, None)

    markers = []
    hidden_count = 0
    for i in range(max(len(target_rows), len(source_rows))):
        marker = get_row_marker(i, target_rows, source_rows)
        if hide_name_diffs and marker == "a":
            marker = classify_argument_diff(i, target_view, source_view)
            if marker == " ":
                hidden_count += 1
        markers.append(marker)

    print(f"{len(markers)} rows: {summarize_markers(markers, hidden_count)}")

    rows_to_show = select_rows_to_show(markers, context)
    if not rows_to_show:
        print("  (no differences)")
        return

    width = max(
        [len(target_view.get_text(i)) for i in rows_to_show]
        + [len(target_view.get_label(i)) for i in rows_to_show]
        + [len("target")]
    )
    print(f"  {'off':4}  {'target':<{width}}  source")

    previous = None
    for i in rows_to_show:
        if previous is not None and i != previous + 1:
            print("  ...")
        previous = i

        target_label = target_view.get_label(i)
        source_label = source_view.get_label(i)
        if target_label or source_label:
            print(f"  {'':4}  {target_label:<{width}}  {source_label}".rstrip())

        marker = markers[i]
        offset_text = target_view.get_offset_text(i)
        target_text = target_view.get_text(i)
        source_text = "" if marker == " " else source_view.get_text(i)
        line = f"{marker} {offset_text:4}  {target_text:<{width}}  {source_text}"
        print(line.rstrip())


def parse_args() -> argparse.Namespace:
    assert __doc__
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "symbol", help="name of function to diff (mangled or demangled)"
    )
    parser.add_argument(
        "-u",
        "--unit",
        help="objdiff unit name (required if multiple symbols w/ same name)",
    )
    parser.add_argument(
        "--json", type=Path, help="read a saved objdiff-cli JSON file instead"
    )
    parser.add_argument(
        "--context",
        type=int,
        default=None,
        help="only show differing rows plus N rows both before and after",
    )
    parser.add_argument(
        "--target",
        action="store_true",
        help="print only the target asm, with labels (default when there is no source)",
    )
    parser.add_argument(
        "--hide-name-diffs",
        action="store_true",
        help="treat 'a' rows as identical when they differ only in which symbol "
        "they load, and both symbols are read-only data with the same value "
        "(e.g. lbl_80641D98 vs @6897, both 1.0f). Rows that differ only in the "
        "symbol but whose values can't be compared are marked 'n'. The match "
        "%% is objdiff's and doesn't change",
    )
    parser.add_argument(
        "--calls",
        action="store_true",
        help="print only the functions called (bl, and b for tail calls) and how "
        "often, with register save/restore helpers listed separately",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()

    symbol: str = args.symbol
    unit: Optional[str] = args.unit
    json_file: Optional[Path] = args.json
    context: Optional[int] = args.context

    report = load_report()
    objdiff_symbol = symbol
    if unit is None:
        # objdiff-cli only accepts mangled names, unless a unit is given (and
        # then it ignores the symbol name), so look up the unit and mangled
        # name to support demangled names too
        unit, objdiff_symbol = find_unit_for_symbol(report, symbol)

    if json_file:
        diff = load_diff_file(json_file)
    else:
        diff = run_objdiff_cli(objdiff_symbol, unit)

    target = find_function(diff, TARGET, symbol)
    source = find_function(diff, SOURCE, symbol)
    if target is None:
        sys.exit(f"{symbol} not found in the target object")

    print_diff(
        target,
        source,
        DataValues(diff, get_source_object_path(unit)),
        get_section_address(report, target["name"]),
        context,
        target_only=args.target,
        hide_name_diffs=args.hide_name_diffs,
        calls=args.calls,
    )


if __name__ == "__main__":
    main()
