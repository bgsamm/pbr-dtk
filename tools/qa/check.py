#!/usr/bin/env python3
"""Quality checks for a change, compared with its base.

Every check runs on the working tree (HEAD plus uncommitted changes) and on
the base commit, and fails only on problems the change introduces. Problems
already present in the base are counted, and listed with --show-inherited.

Checks that need only the compilers (no game files):
  diagnostics  compiler warnings and errors with extra warning flags, and
               calls without a prototype in C units (-requireprotos)
  symbols      each compiled object against symbols.txt and splits.txt:
               scope (static or global), names missing from symbols.txt,
               definitions outside the unit's address range, functions out of
               retail order, and undefined names that nothing provides
  format       clang-format (the major version pinned in tools/qa/requirements.txt)
               on the changed files under src/ and include/
  lint         tools/qa/lint.py on the lines added

Checks that need the game files (--with-dol):
  regressions  objdiff report of the base against the change: a function that
               was 100% and no longer is, or a unit that loses matched or
               linked code or data, fails
  apply        `dtk dol apply`: symbols.txt must already agree with the names,
               sizes and scopes of the linked objects

Usage:
  python tools/qa/check.py [--base REF] [--with-dol] [--only CHECK,...]
                           [--configure-args "ARGS"] [--show-inherited]
  python tools/qa/check.py --base none     report everything, compare nothing

The base defaults to the merge base of HEAD and origin/main. The base tree is
checked out in build/qa/base. Exit status: 0 when the change adds no problem,
1 otherwise.
"""

from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple
import argparse
import difflib
import json
import os
import re
import shlex
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
QA_DIR = ROOT / "build" / "qa"
VERSION = "RPBP01"

# Warnings that point at real defects and stay quiet on correct original code.
# `-W all` is not used: it reports every implicit integer conversion, which
# the original code is full of. None of these flags changes the object code.
WARNING_FLAGS = [
    "-w missingreturn,hidevirtual,possible,unusedexpr,filecaps,sysfilecaps,tokenpasting",
]
# Compiler intrinsics: -requireprotos reports them, but they need no declaration.
INTRINSICS = {
    "__abs",
    "__labs",
    "__fabs",
    "__fabsf",
    "__fnabs",
    "__fnabsf",
    "__cntlzw",
    "__rlwinm",
    "__rlwimi",
    "__rlwnm",
    "__lhbrx",
    "__lwbrx",
    "__sthbrx",
    "__stwbrx",
    "__dcbf",
    "__dcbi",
    "__dcbst",
    "__dcbt",
    "__dcbtst",
    "__dcbz",
    "__eieio",
    "__isync",
    "__sync",
    "__mulhw",
    "__mulhwu",
    "__fmadd",
    "__fmadds",
    "__fmsub",
    "__fmsubs",
    "__fnmadd",
    "__fnmadds",
    "__fnmsub",
    "__fnmsubs",
    "__fres",
    "__frsqrte",
    "__fsel",
    "__fsels",
    "__setflm",
    "__mffs",
    "__mtfsf",
    "__mtfsfi",
    "__mtfsb0",
    "__mtfsb1",
    "__alloca",
    "__memcpy",
}
REQUIREMENTS = ROOT / "tools" / "qa" / "requirements.txt"
FORMAT_PATHS = ["src", "include"]
SOURCE_SUFFIXES = {".c", ".cpp", ".cp", ".h", ".hpp", ".inc"}
ALL_CHECKS = ["diagnostics", "symbols", "format", "lint", "regressions", "apply"]
DOL_CHECKS = {"regressions", "apply"}
# Undefined names the linker provides itself.
LINKER_NAMES = re.compile(
    r"^(_SDA2?_BASE_|_stack_(addr|end)|_db_stack_(addr|end)|"
    r"__ArenaLo|__ArenaHi|_f_\w+|_e_\w+|__(init|fini)_\w+_table)$"
)


# --------------------------------------------------------------------------
# Results


@dataclass(frozen=True)
class Issue:
    check: str
    key: Tuple[str, ...]  # identifies the problem in both trees
    message: str
    path: str = ""
    line: int = 0
    detail: str = ""  # pairs an issue with the same one in the base first


@dataclass
class CheckResult:
    name: str
    new: List[Issue] = field(default_factory=list)
    inherited: List[Issue] = field(default_factory=list)
    notes: List[str] = field(default_factory=list)
    skipped: Optional[str] = None
    failed: bool = False  # the check itself could not run


def compare(name: str, head: List[Issue], base: Optional[List[Issue]]) -> CheckResult:
    """Issues of the head that the base does not have, counting repeats.

    Issues with the same key are paired by detail first, so that when a file
    gains a problem the new one is reported rather than an old one."""
    result = CheckResult(name)
    if base is None:
        result.new = list(head)
        return result
    remaining = Counter(issue.key for issue in base)
    details = Counter((issue.key, issue.detail) for issue in base)
    unpaired = []
    for issue in head:
        if details[(issue.key, issue.detail)] > 0:
            details[(issue.key, issue.detail)] -= 1
            remaining[issue.key] -= 1
            result.inherited.append(issue)
        else:
            unpaired.append(issue)
    for issue in unpaired:
        if remaining[issue.key] > 0:
            remaining[issue.key] -= 1
            result.inherited.append(issue)
        else:
            result.new.append(issue)
    return result


# --------------------------------------------------------------------------
# Trees


def run(
    cmd: List[str], cwd: Path, check: bool = True, **kwargs
) -> subprocess.CompletedProcess:
    return subprocess.run(
        cmd, cwd=cwd, check=check, text=True, capture_output=True, **kwargs
    )


def git(*args: str, cwd: Path = ROOT) -> str:
    return run(["git", *args], cwd).stdout.strip()


def resolve_base(base: Optional[str]) -> Optional[str]:
    if base == "none":
        return None
    if (
        base is None or base == "" or set(base) == {"0"}
    ):  # a new branch has no "before" commit
        try:
            return git("merge-base", "HEAD", "origin/main")
        except subprocess.CalledProcessError:
            sys.exit("error: no merge base with origin/main; pass --base")
    try:
        return git("rev-parse", "--verify", base + "^{commit}")
    except subprocess.CalledProcessError:
        sys.exit(f"error: unknown base {base}")


def checkout_base(sha: str) -> Path:
    path = QA_DIR / "base"
    if path.exists():
        try:
            same = git("rev-parse", "HEAD", cwd=path) == sha
            clean = git("status", "--porcelain", "--untracked-files=no", cwd=path) == ""
        except subprocess.CalledProcessError:
            same = clean = False
        if same and clean:
            return path
        run(["git", "worktree", "remove", "--force", str(path)], ROOT, check=False)
        shutil.rmtree(path, ignore_errors=True)
        run(["git", "worktree", "prune"], ROOT)
    QA_DIR.mkdir(parents=True, exist_ok=True)
    run(["git", "worktree", "add", "--detach", str(path), sha], ROOT)
    return path


@dataclass
class Tree:
    label: str
    root: Path
    tools: dict
    units: List[dict]

    @property
    def out(self) -> Path:
        return QA_DIR / self.label


def load_tree(label: str, root: Path, configure_args: List[str]) -> Tree:
    output = QA_DIR / f"{label}-units.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    script = ROOT / "tools" / "qa" / "units.py"
    result = run(
        [sys.executable, str(script), str(output), *configure_args], root, check=False
    )
    if result.returncode != 0:
        sys.exit(
            f"error: could not read the units of {root}:\n{result.stdout}{result.stderr}"
        )
    data = json.loads(output.read_text())
    (root / "build" / VERSION / "include").mkdir(parents=True, exist_ok=True)
    return Tree(label, root, data["tools"], data["units"])


def configure_args_for_base(head: Tree, configure_args: List[str]) -> List[str]:
    """Point the base at the head's compilers and binutils, so the base tree
    needs no download."""
    args = list(configure_args)
    if "--compilers" not in args:
        args += ["--compilers", head.tools["compilers"]]
    if "--binutils" not in args:
        args += ["--binutils", head.tools["binutils"]]
    return args


# --------------------------------------------------------------------------
# Compiling


@dataclass
class Diagnostic:
    path: str
    line: int
    kind: str  # "Warning" or "Error"
    message: str
    text: str  # the source line, stripped
    marked: str = ""  # the part of the line the compiler points at


MESSAGE_START = "### mwcceppc.exe Compiler:"
NOISE = ("Too many errors", "Errors caused tool", "User break")


def parse_diagnostics(output: str, root: Path) -> List[Diagnostic]:
    """Parse mwcc messages:

    ### mwcceppc.exe Compiler:
    #    File: libs\\RVL_SDK\\src\\os\\OSReset.c
    # ---------------------------------------
    #     250:     void *buf;
    # Warning:          ^
    #   (10185) variable 'buf' is not initialized before being used

    Later messages for the same file leave out the File line."""
    diagnostics = []
    path = ""
    for block in output.split(MESSAGE_START)[1:]:
        lines = [
            line[1:] if line.startswith("#") else line for line in block.splitlines()
        ]
        line_number, source, kind, marked, message = 0, "", "", "", []
        for index, line in enumerate(lines):
            location = re.match(r"\s*(?:File|In):\s*(.+?)\s*$", line)
            if location:
                path = normalize_path(location.group(1), root)
                continue
            match = re.match(r"\s*(\d+):\s?(.*)$", line)
            if match:
                line_number, source = int(match.group(1)), line
                continue
            match = re.match(r"\s*(Warning|Error)\s*:", line)
            if match:
                kind = match.group(1)
                carets = re.search(r"\^+", line[match.end() :])
                if carets:
                    start = match.end() + carets.start()
                    marked = source[start : start + len(carets.group())].strip()
                message = [
                    m.strip()
                    for m in lines[index + 1 :]
                    if m.strip() and not m.strip().startswith(NOISE)
                ]
                break
        if kind:
            text = re.sub(r"^\s*\d+:\s?", "", source).strip()
            diagnostics.append(
                Diagnostic(path, line_number, kind, " ".join(message), text, marked)
            )
    return diagnostics


def normalize_path(path: str, root: Path) -> str:
    path = path.replace("\\", "/")
    try:
        return (
            Path(path).resolve().relative_to(root.resolve()).as_posix()
            if Path(path).is_absolute()
            else path
        )
    except ValueError:
        return path


@dataclass
class CompileResult:
    unit: dict
    object_path: Optional[Path]
    diagnostics: List[Diagnostic]
    failed: bool


def compile_command(
    tree: Tree, unit: dict, flags: List[str], output: Path
) -> List[str]:
    command = []
    if tree.tools["wrapper"]:
        command.append(tree.tools["wrapper"])
    if unit["shift_jis"]:
        command.append(tree.tools["sjiswrap"])
    command.append(unit["compiler"])
    for flag in flags:
        command += shlex.split(flag)
    return command + ["-c", unit["source"], "-o", str(output)]


def compile_unit(tree: Tree, unit: dict) -> CompileResult:
    base_flags = [f for f in unit["cflags"] if not f.startswith("-maxerrors")] + [
        "-maxerrors 0"
    ]
    stem = tree.out / "obj" / unit["name"]
    stem.parent.mkdir(parents=True, exist_ok=True)
    object_path = stem.with_suffix(".o")
    object_path.unlink(missing_ok=True)

    result = run(
        compile_command(tree, unit, base_flags + WARNING_FLAGS, object_path),
        tree.root,
        check=False,
    )
    diagnostics = parse_diagnostics(result.stdout + result.stderr, tree.root)
    failed = result.returncode != 0 or not object_path.exists()
    if failed and not any(d.kind == "Error" for d in diagnostics):
        diagnostics.append(
            Diagnostic(
                unit["source"],
                0,
                "Error",
                "compilation failed: " + (result.stdout + result.stderr).strip()[-300:],
                "",
            )
        )

    if unit["source"].endswith(".c") and not failed:
        protos_path = stem.with_suffix(".protos.o")
        result = run(
            compile_command(tree, unit, base_flags + ["-requireprotos"], protos_path),
            tree.root,
            check=False,
        )
        protos_path.unlink(missing_ok=True)
        for diagnostic in parse_diagnostics(result.stdout + result.stderr, tree.root):
            if "prototype" not in diagnostic.message or diagnostic.marked in INTRINSICS:
                continue
            if diagnostic.kind == "Error" and diagnostic.marked:
                diagnostic.message = f"call to {diagnostic.marked}, which has no prototype (-requireprotos)"
            else:
                diagnostic.message = (
                    "function defined without a prototype in a header (-requireprotos)"
                )
            diagnostics.append(diagnostic)
    return CompileResult(unit, None if failed else object_path, diagnostics, failed)


def compile_tree(tree: Tree, jobs: int) -> List[CompileResult]:
    with ThreadPoolExecutor(jobs) as pool:
        return list(pool.map(lambda unit: compile_unit(tree, unit), tree.units))


# --------------------------------------------------------------------------
# Check: diagnostics


def diagnostic_issues(results: List[CompileResult]) -> List[Issue]:
    """Diagnostics as issues keyed by file, kind and message, so that moving or
    reformatting code does not make them new. A diagnostic in a header shows
    up once per unit that includes it, so repeats are counted within a unit
    only."""
    best: Dict[Tuple[str, ...], List[Diagnostic]] = {}
    for result in results:
        groups: Dict[Tuple[str, ...], List[Diagnostic]] = defaultdict(list)
        for d in result.diagnostics:
            message = re.sub(r"^\(\d+\)\s*", "", d.message)
            groups[(d.path, d.kind, message)].append(d)
        for key, group in groups.items():
            if len(group) > len(best.get(key, [])):
                best[key] = group
    issues = []
    for key, group in best.items():
        for d in group:
            issues.append(
                Issue(
                    "diagnostics",
                    key,
                    f"{d.kind.lower()}: {d.message}  [{d.text}]",
                    d.path,
                    d.line,
                    re.sub(r"\s+", "", d.text),
                )
            )
    return issues


# --------------------------------------------------------------------------
# Check: symbols


@dataclass
class Symbol:
    name: str
    section: str
    address: int
    scope: str
    kind: str


def load_symbols(path: Path) -> Dict[str, List[Symbol]]:
    symbols: Dict[str, List[Symbol]] = defaultdict(list)
    pattern = re.compile(r"^(\S+) = (\.?\w+):0x([0-9A-Fa-f]+);\s*//(.*)$")
    for line in path.read_text().splitlines():
        match = pattern.match(line)
        if not match:
            continue
        attributes = match.group(4)
        scope = re.search(r"\bscope:(\w+)", attributes)
        kind = re.search(r"\btype:(\w+)", attributes)
        symbols[match.group(1)].append(
            Symbol(
                match.group(1),
                match.group(2),
                int(match.group(3), 16),
                scope.group(1) if scope else "global",
                kind.group(1) if kind else "",
            )
        )
    return symbols


def load_splits(path: Path) -> Dict[str, List[Tuple[str, int, int]]]:
    splits: Dict[str, List[Tuple[str, int, int]]] = defaultdict(list)
    unit = None
    for line in path.read_text().splitlines():
        if line and not line[0].isspace() and line.endswith(":"):
            unit = line[:-1]
            continue
        match = re.match(
            r"\s+(\S+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)", line
        )
        if match and unit and unit != "Sections":
            splits[unit].append(
                (match.group(1), int(match.group(2), 16), int(match.group(3), 16))
            )
    return splits


@dataclass
class ElfSymbol:
    name: str
    value: int
    kind: str  # FUNC, OBJECT, ...
    bind: str  # global, local, weak
    section: str  # section name, or "UND"


def read_elf_symbols(readelf: str, path: Path) -> List[ElfSymbol]:
    sections = {}
    output = run([readelf, "-SW", str(path)], ROOT).stdout
    for match in re.finditer(r"^\s*\[\s*(\d+)\]\s+(\S+)", output, re.M):
        sections[match.group(1)] = match.group(2)
    symbols = []
    output = run([readelf, "-sW", str(path)], ROOT).stdout
    for line in output.splitlines():
        fields = line.split()
        if len(fields) < 8 or not fields[0].rstrip(":").isdigit():
            continue
        _, value, _, kind, bind, _, ndx, name = fields[:8]
        section = "UND" if ndx == "UND" else sections.get(ndx, ndx)
        symbols.append(ElfSymbol(name, int(value, 16), kind, bind.lower(), section))
    return symbols


def is_compiler_name(name: str) -> bool:
    return name.startswith("@") or "$" in name or name.startswith(".")


def symbol_issues(tree: Tree, results: List[CompileResult]) -> List[Issue]:
    symbols = load_symbols(Path(tree.tools["symbols"]))
    splits = load_splits(Path(tree.tools["splits"]))
    readelf = str(Path(tree.tools["binutils"]) / "powerpc-eabi-readelf")
    issues: List[Issue] = []

    per_unit: Dict[str, List[ElfSymbol]] = {}
    defined: Set[str] = set()
    for result in results:
        if result.object_path is None:
            continue
        elf_symbols = read_elf_symbols(readelf, result.object_path)
        per_unit[result.unit["name"]] = elf_symbols
        defined.update(
            s.name for s in elf_symbols if s.section != "UND" and s.bind != "local"
        )

    for result in results:
        unit = result.unit
        name = unit["name"]
        if name not in per_unit:
            continue
        ranges = splits.get(name, [])

        def in_unit(symbol: Symbol) -> bool:
            return any(start <= symbol.address < end for _, start, end in ranges)

        text_order: List[Tuple[str, int, int, str]] = (
            []
        )  # (section, offset, address, name)
        for elf in per_unit[name]:
            if elf.kind not in ("FUNC", "OBJECT") or is_compiler_name(elf.name):
                continue
            if elf.section == "UND":
                continue
            candidates = symbols.get(elf.name, [])
            local = [s for s in candidates if in_unit(s)]
            where = f"{unit['source']}: {elf.name}"
            if not candidates:
                issues.append(
                    Issue(
                        "symbols",
                        (name, "unknown", elf.name),
                        f"{where} is not in symbols.txt (wrong name, or code the game does not have)",
                        unit["source"],
                    )
                )
                continue
            if not local:
                if ranges:
                    issues.append(
                        Issue(
                            "symbols",
                            (name, "outside", elf.name),
                            f"{where} belongs to another unit (symbols.txt places it at "
                            f"0x{candidates[0].address:08X})",
                            unit["source"],
                        )
                    )
                continue
            target = local[0]
            if target.scope != elf.bind:
                issues.append(
                    Issue(
                        "symbols",
                        (name, "scope", elf.name),
                        f"{where} is {elf.bind} in the object but scope:{target.scope} in symbols.txt",
                        unit["source"],
                    )
                )
            if elf.kind == "FUNC":
                text_order.append((elf.section, elf.value, target.address, elf.name))

        text_order.sort()
        previous = None
        previous_section = None
        for section, _, address, function in text_order:
            if section != previous_section:
                previous, previous_section = None, section
            if previous and address < previous[0]:
                issues.append(
                    Issue(
                        "symbols",
                        (name, "order", previous[1], function),
                        f"{unit['source']}: {function} (0x{address:08X}) is defined after "
                        f"{previous[1]} (0x{previous[0]:08X}); keep retail order",
                        unit["source"],
                    )
                )
            previous = (address, function)

        for elf in per_unit[name]:
            if elf.section != "UND" or not elf.name or is_compiler_name(elf.name):
                continue
            if (
                elf.name in symbols
                or elf.name in defined
                or LINKER_NAMES.match(elf.name)
            ):
                continue
            hint = (
                " (an uppercase name is usually a missing macro)"
                if re.match(r"^[A-Z0-9_]+$", elf.name)
                else ""
            )
            issues.append(
                Issue(
                    "symbols",
                    (name, "unresolved", elf.name),
                    f"{unit['source']}: uses {elf.name}, which neither symbols.txt nor any unit "
                    f"defines{hint}",
                    unit["source"],
                )
            )
    return issues


# --------------------------------------------------------------------------
# Check: format


def changed_files(base: Optional[str], paths: List[str]) -> List[str]:
    if base is None:
        files = git("ls-files", "--", *paths).splitlines()
    else:
        files = git(
            "diff", "--name-only", "--diff-filter=d", base, "--", *paths
        ).splitlines()
        files += git(
            "ls-files", "--others", "--exclude-standard", "--", *paths
        ).splitlines()
    return sorted(
        {f for f in files if Path(f).suffix in SOURCE_SUFFIXES and (ROOT / f).exists()}
    )


def clang_format_major() -> str:
    """The clang-format major version pinned in tools/qa/requirements.txt."""
    match = re.search(r"^clang-format==(\d+)\.", REQUIREMENTS.read_text(), re.MULTILINE)
    if match is None:
        sys.exit(f"error: no clang-format version in {REQUIREMENTS}")
    return match.group(1)


def find_clang_format(major: str) -> Optional[str]:
    for candidate in [
        os.environ.get("CLANG_FORMAT"),
        "clang-format",
        f"clang-format-{major}",
    ]:
        if candidate and shutil.which(candidate):
            version = run([candidate, "--version"], ROOT, check=False).stdout
            if re.search(rf"version {major}\.", version):
                return candidate
    return None


def check_format(base: Optional[str]) -> CheckResult:
    result = CheckResult("format")
    major = clang_format_major()
    clang_format = find_clang_format(major)
    if clang_format is None:
        result.failed = True
        result.notes.append(
            f"clang-format {major} not found (set CLANG_FORMAT, or "
            "`pip install -r tools/qa/requirements.txt`)"
        )
        return result
    # Whole files, not only the changed lines: a change to a file that is not
    # formatted yet (some of src/gs and include/gs today) formats all of it.
    files = changed_files(base, FORMAT_PATHS)
    for path in files:
        check = run([clang_format, "--dry-run", "--Werror", path], ROOT, check=False)
        if check.returncode != 0:
            first = re.search(rf"^{re.escape(path)}:(\d+):", check.stderr, re.M)
            line = int(first.group(1)) if first else 0
            result.new.append(
                Issue(
                    "format",
                    (path,),
                    f"{path}: not formatted (run {clang_format} -i {path})",
                    path,
                    line,
                )
            )
    result.notes.append(f"{len(files)} changed file(s) checked")
    return result


# --------------------------------------------------------------------------
# Check: lint


def check_lint(base: Optional[str]) -> CheckResult:
    result = CheckResult("lint")
    lint = ROOT / "tools" / "qa" / "lint.py"
    args = ["--all", "src", "include"] if base is None else [base]
    output = run([sys.executable, str(lint), *args], ROOT, check=False)
    text = output.stdout + output.stderr
    for line in text.splitlines():
        match = re.match(r"^(ERROR|ERR)\s+(\S+?):(\d+):\s*(.*)$", line)
        if match:
            result.new.append(
                Issue(
                    "lint",
                    (match.group(2), match.group(4)),
                    f"error: {match.group(4)}",
                    match.group(2),
                    int(match.group(3)),
                )
            )
    warnings = sum(1 for line in text.splitlines() if line.startswith("WARN"))
    if warnings:
        result.notes.append(f"{warnings} fakematch warning(s): list each one in the PR")
    if output.returncode != 0 and not result.new:
        result.failed = True
        result.notes.append(text.strip()[-500:])
    return result


# --------------------------------------------------------------------------
# Checks that need the game files


def ninja(tree_root: Path, *targets: str) -> None:
    result = subprocess.run(["ninja", *targets], cwd=tree_root, text=True)
    if result.returncode != 0:
        sys.exit(f"error: `ninja {' '.join(targets)}` failed in {tree_root}")


def prepare_dol_tree(tree: Tree, configure_args: List[str]) -> Path:
    """Configure and build a tree; return its report.json."""
    if tree.root != ROOT:
        # Link the top-level entries: orig/ may hold directories or symlinks
        # to them, which a recursive walk would not follow.
        orig = ROOT / "orig" / VERSION
        for source in orig.iterdir():
            if source.name == ".gitkeep":
                continue
            target = tree.root / "orig" / VERSION / source.name
            if not target.exists() and not target.is_symlink():
                target.parent.mkdir(parents=True, exist_ok=True)
                target.symlink_to(source.resolve())
        result = run(
            [sys.executable, "configure.py", *configure_args], tree.root, check=False
        )
        if result.returncode != 0:
            sys.exit(
                f"error: configure.py failed in {tree.root}:\n{result.stdout}{result.stderr}"
            )
    report = tree.root / "build" / VERSION / "report.json"
    ninja(tree.root)
    ninja(tree.root, str(report.relative_to(tree.root)))
    return report


def measures(entry: Optional[dict]) -> dict:
    return (entry or {}).get("measures", entry or {})


def check_regressions(head_report: Path, base_report: Optional[Path]) -> CheckResult:
    result = CheckResult("regressions")
    if base_report is None:
        result.skipped = "no base to compare with"
        return result
    objdiff = ROOT / "build" / "tools" / "objdiff-cli"
    changes_path = QA_DIR / "report_changes.json"
    run(
        [
            str(objdiff),
            "report",
            "changes",
            "--format",
            "json",
            str(base_report),
            str(head_report),
            "-o",
            str(changes_path),
        ],
        ROOT,
    )
    changes = json.loads(changes_path.read_text())

    unit_keys = [
        "matched_code_percent",
        "matched_data_percent",
        "complete_code_percent",
        "complete_data_percent",
        "matched_functions",
    ]

    def compare_measures(label: str, entry: dict) -> None:
        before, after = measures(entry.get("from")), measures(entry.get("to"))
        if not before:
            return
        for key in unit_keys:
            if key in before and float(after.get(key, 0)) < float(before[key]):
                result.new.append(
                    Issue(
                        "regressions",
                        (label, key),
                        f"{label}: {key} {before[key]} -> {after.get(key, 0)}",
                    )
                )

    compare_measures("total", changes)
    for unit in changes.get("units", []):
        name = unit.get("name", "?")
        compare_measures(name, unit)
        functions = unit.get("functions", []) or []
        added = {}
        for function in functions:
            address = (function.get("metadata") or {}).get("virtual_address")
            if (
                function.get("from") is None
                and function.get("to") is not None
                and address is not None
            ):
                added[address] = function
        for function in functions:
            before = (function.get("from") or {}).get("fuzzy_match_percent")
            after = (function.get("to") or {}).get("fuzzy_match_percent")
            address = (function.get("metadata") or {}).get("virtual_address")
            label = function.get("name", "?")
            if function.get("to") is None and address in added:
                after = (added[address].get("to") or {}).get("fuzzy_match_percent")
                label = f"{label} -> {added[address].get('name')}"
            if before is None:
                continue
            after = float(after or 0)
            if float(before) >= 100.0 and after < 100.0:
                result.new.append(
                    Issue(
                        "regressions",
                        (name, function.get("name", "?")),
                        f"{name}: {label} was 100% and is now {after:.2f}%",
                    )
                )
            elif after < float(before):
                result.notes.append(
                    f"{name}: {label} {float(before):.2f}% -> {after:.2f}% (explain in the PR)"
                )
    if os.environ.get("QA_ACCEPT_REGRESSIONS") == "1" and result.new:
        result.notes.append(
            f"{len(result.new)} regression(s) accepted by a maintainer (QA_ACCEPT_REGRESSIONS)"
        )
        result.inherited, result.new = result.new, []
    return result


def unlinked_complete_units(report: Path) -> List[str]:
    data = json.loads(report.read_text())
    names = []
    for unit in data.get("units", []):
        unit_measures = unit.get("measures", {})
        metadata = unit.get("metadata", {})
        if metadata.get("auto_generated") or metadata.get("complete"):
            continue
        if float(unit_measures.get("total_code", 0) or 0) == 0:
            continue
        if float(unit_measures.get("fuzzy_match_percent", 0)) >= 100.0:
            names.append(unit["name"])
    return names


def apply_drift(tree_root: Path) -> Set[Tuple[str, str]]:
    """Lines `dtk dol apply` would change in symbols.txt, as (old, new)."""
    config = tree_root / "config" / VERSION
    # Restore the bytes and the times, so the next ninja run does not see
    # splits.txt or symbols.txt as changed and split again.
    saved = {
        path: (path.read_bytes(), path.stat())
        for path in config.rglob("*")
        if path.is_file()
    }
    try:
        ninja(tree_root, "apply")
        after = (config / "symbols.txt").read_text().splitlines()
    finally:
        for path, (data, stat) in saved.items():
            path.write_bytes(data)
            os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))
    before = saved[config / "symbols.txt"][0].decode().splitlines()
    drift = set()
    removed: List[str] = []
    for line in difflib.ndiff(before, after):
        if line.startswith("- "):
            removed.append(line[2:])
        elif line.startswith("+ "):
            drift.add((removed.pop(0) if removed else "", line[2:]))
    drift.update((old, "") for old in removed)
    return drift


def check_apply(head_root: Path, base_root: Optional[Path]) -> CheckResult:
    head = apply_drift(head_root)
    base = apply_drift(base_root) if base_root else None
    issues = [
        Issue("apply", pair, f"symbols.txt: `{pair[0]}` should be `{pair[1]}`")
        for pair in sorted(head)
    ]
    base_issues = None if base is None else [Issue("apply", pair, "") for pair in base]
    return compare("apply", issues, base_issues)


# --------------------------------------------------------------------------
# Output


def escape_data(text: str) -> str:
    """Escape a workflow command's message."""
    return text.replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")


def escape_property(text: str) -> str:
    """Escape a workflow command's property value."""
    return escape_data(text).replace(":", "%3A").replace(",", "%2C")


def annotation(issue: Issue) -> str:
    """A GitHub Actions error annotation; file-level issues have no line."""
    properties = []
    if issue.path:
        properties.append(f"file={escape_property(issue.path)}")
        if issue.line:
            properties.append(f"line={issue.line}")
    where = " " + ",".join(properties) if properties else ""
    return f"::error{where}::{escape_data(f'{issue.check}: {issue.message}')}"


def report(
    results: List[CheckResult], show_inherited: bool, summary: Optional[Path]
) -> bool:
    github = os.environ.get("GITHUB_ACTIONS") == "true"
    ok = True
    lines = [
        "## Quality checks",
        "",
        "| Check | New | Inherited | Result |",
        "|---|---|---|---|",
    ]
    for result in results:
        if result.skipped:
            print(f"[skip] {result.name}: {result.skipped}")
            lines.append(f"| {result.name} | | | skipped: {result.skipped} |")
            continue
        status = "FAIL" if (result.new or result.failed) else "ok"
        ok = ok and status == "ok"
        print(
            f"[{status}] {result.name}: {len(result.new)} new, {len(result.inherited)} inherited"
        )
        for issue in result.new:
            location = (
                f"{issue.path}:{issue.line}: " if issue.path and issue.line else ""
            )
            print(f"    {location}{issue.message}")
            if github:
                print(annotation(issue))
        if show_inherited:
            for issue in result.inherited:
                print(f"    (inherited) {issue.message}")
        for note in result.notes:
            print(f"    note: {note}")
        lines.append(
            f"| {result.name} | {len(result.new)} | {len(result.inherited)} | {status} |"
        )
    if summary:
        with summary.open("a") as handle:
            handle.write("\n".join(lines) + "\n")
    return ok


# --------------------------------------------------------------------------


def main() -> None:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "--base",
        help="base commit (default: merge base with origin/main; `none`: no comparison)",
    )
    parser.add_argument(
        "--with-dol",
        action="store_true",
        help="also run the checks that need the game files",
    )
    parser.add_argument(
        "--only", help="comma-separated checks to run: " + ",".join(ALL_CHECKS)
    )
    parser.add_argument(
        "--configure-args",
        default="",
        help='arguments for configure.py, e.g. "--compilers /compilers"',
    )
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    parser.add_argument(
        "--show-inherited",
        action="store_true",
        help="also list problems the base already has",
    )
    parser.add_argument(
        "--summary",
        type=Path,
        default=os.environ.get("GITHUB_STEP_SUMMARY") or None,
        help="append a Markdown summary to this file",
    )
    args = parser.parse_args()

    checks = (
        args.only.split(",")
        if args.only
        else [c for c in ALL_CHECKS if args.with_dol or c not in DOL_CHECKS]
    )
    unknown = set(checks) - set(ALL_CHECKS)
    if unknown:
        sys.exit(f"error: unknown check(s): {', '.join(sorted(unknown))}")
    configure_args = shlex.split(args.configure_args)
    base_sha = resolve_base(args.base)
    print(f"base: {base_sha or 'none'}")

    needs_trees = {"diagnostics", "symbols", "regressions", "apply"} & set(checks)
    head = load_tree("head", ROOT, configure_args) if needs_trees else None
    base = None
    if base_sha and needs_trees:
        base = load_tree(
            "base",
            checkout_base(base_sha),
            configure_args_for_base(head, configure_args),
        )
        for tool in (
            "wrapper",
            "sjiswrap",
            "binutils",
        ):  # the base tree has no downloaded tools
            base.tools[tool] = head.tools[tool]

    results: List[CheckResult] = []
    if {"diagnostics", "symbols"} & set(checks):
        head_compiled = compile_tree(head, args.jobs)
        base_compiled = compile_tree(base, args.jobs) if base else None
        if "diagnostics" in checks:
            results.append(
                compare(
                    "diagnostics",
                    diagnostic_issues(head_compiled),
                    diagnostic_issues(base_compiled) if base_compiled else None,
                )
            )
        if "symbols" in checks:
            results.append(
                compare(
                    "symbols",
                    symbol_issues(head, head_compiled),
                    (
                        symbol_issues(base, base_compiled)
                        if base and base_compiled
                        else None
                    ),
                )
            )
    if "format" in checks:
        results.append(check_format(base_sha))
    if "lint" in checks:
        results.append(check_lint(base_sha))
    if DOL_CHECKS & set(checks):
        head_report = prepare_dol_tree(head, configure_args)
        base_report = (
            prepare_dol_tree(base, configure_args_for_base(head, configure_args))
            if base
            else None
        )
        if "regressions" in checks:
            results.append(check_regressions(head_report, base_report))
        if "apply" in checks:
            results.append(check_apply(head.root, base.root if base else None))
        complete = CheckResult("complete")
        complete.notes += [
            f"{name} is 100% but not marked Matching"
            for name in unlinked_complete_units(head_report)
        ]
        results.append(complete)

    sys.exit(0 if report(results, args.show_inherited, args.summary) else 1)


if __name__ == "__main__":
    main()
