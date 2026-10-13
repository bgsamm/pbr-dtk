"""Helpers shared by the scripts in tools/decomp/.

Scripts are run as `python tools/decomp/<script>.py`, which puts this folder on
sys.path, so they can simply `import common`.
"""

from pathlib import Path
from typing import (
    Dict,
    Iterator,
    List,
    Literal,
    NamedTuple,
    NotRequired,
    Optional,
    Tuple,
    TypedDict,
)
import json
import re
import struct

VERSION = "RPBP01"
ROOT = Path(__file__).resolve().parents[2]
CONFIG_DIR = ROOT / "config" / VERSION
BUILD_DIR = ROOT / "build" / VERSION

SOURCE_EXTENSION = re.compile(r"\.(c|cpp|cp|s)$")


# --------------------------------------------------------------------------
# Progress report types (report.json / baseline.json)


class FunctionMetadata(TypedDict):
    demangled_name: NotRequired[str]
    virtual_address: NotRequired[str]


class Function(TypedDict):
    name: str
    size: str
    metadata: NotRequired[FunctionMetadata]
    address: NotRequired[str]
    fuzzy_match_percent: NotRequired[float]


class Unit(TypedDict):
    name: str
    measures: dict
    functions: NotRequired[list[Function]]


class Report(TypedDict):
    units: NotRequired[list[Unit]]


def get_demangled_name(function: Function) -> str:
    """The function's demangled name, or its mangled name if it has none."""
    metadata = function.get("metadata", {})
    return metadata.get("demangled_name") or function["name"]


def get_virtual_address(function: Function) -> int:
    """The function's address in the retail executable (0 if unknown)."""
    metadata = function.get("metadata", {})
    return int(metadata.get("virtual_address", 0))


# --------------------------------------------------------------------------
# splits.txt and units


class SectionEntry(NamedTuple):
    section: str
    start: int
    end: int


# unit (as named in splits.txt, e.g. "src/gs/GSmem.cpp") -> [(section, start, end)]
Units = Dict[str, List[SectionEntry]]

SECTION_LINE = re.compile(r"^\s+(\S+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)")


def parse_splits(text: Optional[str] = None) -> Units:
    """Units and their section ranges from splits.txt (or the given text)."""
    if text is None:
        text = (CONFIG_DIR / "splits.txt").read_text(encoding="utf-8")

    units: Units = {}
    current_unit = None
    for line in text.splitlines():
        # Unit headers are unindented and end in a colon, e.g. `src/gs/GSmem.cpp:`
        is_unit_header = line and not line[0].isspace() and line.rstrip().endswith(":")
        if is_unit_header:
            current_unit = line.rstrip()[:-1]
            continue

        match = SECTION_LINE.match(line)
        if match and current_unit:
            section, start, end = match.groups()
            entry = SectionEntry(section, int(start, 16), int(end, 16))
            units.setdefault(current_unit, []).append(entry)
    return units


def find_unit_containing(section: str, address: int, units: Units) -> Optional[str]:
    """The unit whose split contains section:address, if any."""
    for unit, entries in units.items():
        for entry in entries:
            if entry.section == section and entry.start <= address < entry.end:
                return unit
    return None


def get_unit_stem(path: str) -> str:
    """`main/src/gs/GSmem.cpp` -> `gs/GSmem`, for loose unit-name matching."""
    path = path.replace("\\", "/")
    path = re.sub(r"^(main/)?(src/)?", "", path)
    return SOURCE_EXTENSION.sub("", path)


def resolve_unit(name: str, units: Units) -> str:
    """Find the one unit matching e.g. `GSmem`, `gs/GSmem` or `src/gs/GSmem.cpp`."""
    wanted_stem = get_unit_stem(name)

    # Prefer exact matches; fall back to matching the end of the path
    matches = [unit for unit in units if get_unit_stem(unit) == wanted_stem]
    if not matches:
        matches = [
            unit for unit in units if get_unit_stem(unit).endswith("/" + wanted_stem)
        ]

    if len(matches) != 1:
        message = f"{name!r} matches {len(matches)} units in splits.txt"
        if matches:
            message += ": " + ", ".join(matches)
        raise ValueError(message)
    return matches[0]


def get_unit_object_path(unit: str) -> Path:
    """The unit's object built from source (it may not exist)."""
    relative_path = re.sub(r"^src/", "", unit)
    return BUILD_DIR / "src" / Path(relative_path).with_suffix(".o")


# --------------------------------------------------------------------------
# symbols.txt


class SymbolEntry(NamedTuple):
    name: str
    section: str
    address: int
    attributes: List[str]
    line_number: int

    @property
    def size(self) -> Optional[int]:
        for attribute in self.attributes:
            if attribute.startswith("size:"):
                return int(attribute.removeprefix("size:"), 16)
        return None


# e.g. `fn_801E6F78 = .text:0x801E6F78; // type:function size:0x538`
SYMBOL_LINE = re.compile(r"^(\S+) = ([^:\s]+):0x([0-9A-Fa-f]+);\s*(?://\s*(.*))?$")


def parse_symbols(text: Optional[str] = None) -> Tuple[List[SymbolEntry], List[str]]:
    """Entries of symbols.txt (or the given text), and every other line."""
    if text is None:
        text = (CONFIG_DIR / "symbols.txt").read_text(encoding="utf-8")

    entries: List[SymbolEntry] = []
    other_lines: List[str] = []
    for line_number, line in enumerate(text.splitlines(), 1):
        line = line.rstrip("\r")
        match = SYMBOL_LINE.match(line)
        if match is None:
            other_lines.append(line)
            continue

        name, section, address, comment = match.groups()
        attributes = comment.split() if comment else []
        entries.append(
            SymbolEntry(name, section, int(address, 16), attributes, line_number)
        )
    return entries, other_lines


# --------------------------------------------------------------------------
# Object files

SHT_SYMTAB = 2
STT_OBJECT = 1
STT_FUNC = 2
SHN_UNDEF = 0
SHN_LORESERVE = 0xFF00


class SectionHeader(NamedTuple):
    """An ELF32 section header (Elf32_Shdr)."""

    name: int
    type: int
    flags: int
    address: int
    offset: int
    size: int
    link: int
    info: int
    alignment: int
    entry_size: int


class ElfSymbol(NamedTuple):
    kind: str  # "func" or "object"
    size: int
    section: str  # e.g. ".text" or ".sdata2"


def read_c_string(data: bytes, start: int) -> str:
    end = data.index(b"\0", start)
    return data[start:end].decode("utf-8", "replace")


def read_section_headers(data: bytes, byte_order: str) -> List[SectionHeader]:
    table_offset = struct.unpack_from(byte_order + "I", data, 0x20)[0]
    header_size, header_count = struct.unpack_from(byte_order + "HH", data, 0x2E)
    headers = []
    for i in range(header_count):
        fields = struct.unpack_from(
            byte_order + "10I", data, table_offset + i * header_size
        )
        headers.append(SectionHeader(*fields))
    return headers


def get_elf_symbols(path: Path) -> Dict[str, ElfSymbol]:
    """Defined function and object symbols in an ELF32 object, by name."""
    data = path.read_bytes()
    byte_order = ">" if data[5] == 2 else "<"  # EI_DATA: 2 means big-endian
    sections = read_section_headers(data, byte_order)

    section_names_index = struct.unpack_from(byte_order + "H", data, 0x32)[0]
    section_names = sections[section_names_index]

    symbols: Dict[str, ElfSymbol] = {}
    for symbol_table in sections:
        if symbol_table.type != SHT_SYMTAB:
            continue
        string_table = sections[symbol_table.link]
        entry_size = symbol_table.entry_size or 16
        table_end = symbol_table.offset + symbol_table.size

        for offset in range(symbol_table.offset, table_end, entry_size):
            name_offset, _, size, info, _, section_index = struct.unpack_from(
                byte_order + "IIIBBH", data, offset
            )

            symbol_type = info & 0xF
            if symbol_type == STT_FUNC:
                kind = "func"
            elif symbol_type == STT_OBJECT:
                kind = "object"
            else:
                continue

            is_undefined = section_index == SHN_UNDEF
            is_special = section_index >= SHN_LORESERVE
            if is_undefined or is_special:
                continue

            name = read_c_string(data, string_table.offset + name_offset)
            section_header = sections[section_index]
            section = read_c_string(data, section_names.offset + section_header.name)
            symbols[name] = ElfSymbol(kind, size, section)
    return symbols


# --------------------------------------------------------------------------
# Progress reports


def load_report(
    name: Literal["report.json", "baseline.json"] = "report.json",
) -> Optional[Report]:
    """build/RPBP01/<name>, or None if missing."""
    path = BUILD_DIR / name
    if not path.exists():
        return None
    return json.loads(path.read_text(encoding="utf-8"))


def iter_report_functions(report: Optional[Report]) -> Iterator[Tuple[Unit, Function]]:
    """Every (unit, function) pair in the report."""
    if report is None:
        return
    for unit in report.get("units", []):
        for function in unit.get("functions", []):
            yield unit, function


def get_report_unit_entry(report: Optional[Report], unit: str) -> Optional[Unit]:
    """The report entry for a splits.txt unit name."""
    if report is None:
        return None

    # Report unit names look like `main/src/gs/GSmem`
    wanted_suffix = "/" + SOURCE_EXTENSION.sub("", unit)
    for entry in report.get("units", []):
        if entry["name"].endswith(wanted_suffix):
            return entry
    return None
