#!/usr/bin/env python3
"""Inventory of the cleanup work left in the game code (src/ and include/).

Lists every site that keeps the code from the definition of done in
docs/STYLE.md: address names, Unk types and TODO notes (names still to find),
raw offsets, placeholder parameters and extern "C" linkage (memory and
signatures still to type), and the constructs tools/qa/lint.py reports
(fakematches). Each site is listed with its unit's status and, given a
report.json, its match score.

The rules are tree-sitter queries: cleanup_rules.toml next to this script,
plus fakematch_rules.toml. Needs tree-sitter:
  pip install -r tools/qa/requirements.txt

Usage:
  python tools/qa/cleanup_index.py               summary on stdout
  python tools/qa/cleanup_index.py --tsv FILE    every site as TSV ('-': stdout)
  python tools/qa/cleanup_index.py --out DIR     DIR/index.html and
                                                 DIR/cleanup_index.tsv
  Options for the page: --report build/RPBP01/report.json (match scores),
  --revision, --generated, --repo.
"""

from collections import Counter
from pathlib import Path
from typing import Dict, Iterator, List, NamedTuple, Optional, TextIO, Tuple
import argparse
import json
import re
import subprocess
import sys
import tempfile
import tomllib

import lint  # next to this script; exits with a hint without tree-sitter
from tree_sitter import Node, Query, QueryCursor

ROOT = lint.ROOT

RULES_PATH = Path(__file__).with_name("cleanup_rules.toml")
TEMPLATE_PATH = Path(__file__).with_name("cleanup_index.html")
FAMILIES = ["names", "structure", "fakematch"]
OFFSET = re.compile(r"([-+])\s*(0[xX][0-9A-Fa-f]+|\d+)\s*\)*$")


class Category(NamedTuple):
    id: str
    family: str
    message: str
    query: Query
    once_per_name: bool = False
    skip_inside: Tuple[str, ...] = ()


class Site(NamedTuple):
    category: str
    path: str
    line: int
    detail: str
    code: str


class SourceFile(NamedTuple):
    path: str
    unit: str  # "" for headers and files no unit compiles
    status: str  # "Matching", "NonMatching" or ""
    match: Optional[float]  # fuzzy match percent from report.json


# --------------------------------------------------------------------------
# Rules


def load_categories() -> Tuple[List[Category], List[str]]:
    """Our cleanup rules, then the fakematch rules; and the macros to blank."""
    config = tomllib.loads(RULES_PATH.read_text(encoding="utf-8"))
    fakematch = lint.load_rules()
    fakematch_by_id = {rule.id: rule for rule in fakematch.rules}
    categories = []
    for entry in config["rule"]:
        if entry["family"] not in FAMILIES:
            sys.exit(f"error: rule {entry['id']}: unknown family {entry['family']!r}")
        if "query" not in entry:
            # A fakematch rule listed in another family
            if entry["id"] not in fakematch_by_id:
                sys.exit(f"error: rule {entry['id']}: no query and no fakematch rule")
            rule = fakematch_by_id[entry["id"]]
            query, message = rule.query, entry.get("message", rule.message)
        else:
            try:
                query = Query(lint.LANGUAGE, entry["query"])
            except Exception as error:
                sys.exit(f"error: rule {entry['id']}: bad query: {error}")
            message = entry["message"]
        categories.append(
            Category(
                entry["id"],
                entry["family"],
                message,
                query,
                entry.get("once_per_name", False),
                tuple(entry.get("skip_inside", [])),
            )
        )
    listed = {category.id for category in categories}
    for rule in fakematch.rules:
        if rule.id in listed:
            continue
        categories.append(Category(rule.id, "fakematch", rule.message, rule.query))
    return categories, fakematch.blank_macros


# --------------------------------------------------------------------------
# Scanning


def node_text(source: bytes, node: Node) -> str:
    return source[node.start_byte : node.end_byte].decode("utf-8", "replace")


def detail_of(category: Category, text: str) -> str:
    """What a site is about, beyond its line: the name, or the offset."""
    if category.once_per_name:
        return text
    if category.family == "structure":
        match = OFFSET.search(re.sub(r"\s+", " ", text))
        return f"{match.group(1)}{match.group(2)}" if match else ""
    return ""


def scan_file(
    path: str, categories: List[Category], blank_macros: List[str]
) -> List[Site]:
    """Every site in one file, at most one per category and line."""
    source = (ROOT / path).read_bytes()
    lines = source.split(b"\n")
    tree = lint.PARSER.parse(lint.blank_out_macros(source, blank_macros))
    spans: Dict[str, List[Tuple[int, int]]] = {}
    sites = []
    for category in categories:
        captures = QueryCursor(category.query).captures(tree.root_node)
        matches = sorted(captures.get("match", []), key=lambda node: node.start_byte)
        names = sorted(captures.get("_name", []), key=lambda node: node.start_byte)
        outer = [
            span for other in category.skip_inside for span in spans.get(other, [])
        ]
        spans[category.id] = []
        seen = set()
        for node in matches:
            if any(a <= node.start_byte and node.end_byte <= b for a, b in outer):
                continue
            spans[category.id].append((node.start_byte, node.end_byte))
            named = next(
                (n for n in names if node.start_byte <= n.start_byte < node.end_byte),
                node,
            )
            line = lint.get_line_number(source, named)
            detail = detail_of(category, node_text(source, named))
            key = detail if category.once_per_name else line
            if key in seen:
                continue
            seen.add(key)
            code = lines[line - 1].decode("utf-8", "replace").strip()
            sites.append(Site(category.id, path, line, detail, code[:160]))
    return sites


def source_paths() -> Iterator[str]:
    for top in lint.PATHS:
        for path in sorted((ROOT / top).rglob("*")):
            if path.is_file() and lint.is_source(path.name):
                yield path.relative_to(ROOT).as_posix()


# --------------------------------------------------------------------------
# Units


def load_units() -> Dict[str, Tuple[str, bool]]:
    """Source path -> (unit name, Matching), from configure.py via units.py.
    Empty, with a warning, when configure.py can't be loaded."""
    with tempfile.TemporaryDirectory() as directory:
        output = Path(directory) / "units.json"
        result = subprocess.run(
            [sys.executable, str(ROOT / "tools" / "qa" / "units.py"), str(output)],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if result.returncode != 0:
            print(
                "warning: no unit status (configure.py could not be loaded)",
                file=sys.stderr,
            )
            return {}
        data = json.loads(output.read_text())
    return {unit["source"]: (unit["name"], unit["matching"]) for unit in data["units"]}


def load_scores(report: Optional[Path]) -> Dict[str, float]:
    """Source path without extension -> fuzzy match percent. Report unit names
    look like `main/src/gs/GSmem`."""
    if report is None:
        return {}
    scores = {}
    for unit in json.loads(report.read_text(encoding="utf-8")).get("units", []):
        name = unit.get("name", "")
        measures = unit.get("measures", {})
        if "fuzzy_match_percent" in measures:
            stem = name.split("/", 1)[1] if "/" in name else name
            scores[stem] = float(measures["fuzzy_match_percent"])
    return scores


def describe_files(
    paths: List[str], units: Dict[str, Tuple[str, bool]], scores: Dict[str, float]
) -> List[SourceFile]:
    files = []
    for path in paths:
        name, matching = units.get(path, ("", False))
        status = ("Matching" if matching else "NonMatching") if name else ""
        score = scores.get(str(Path(path).with_suffix(""))) if name else None
        files.append(SourceFile(path, name, status, score))
    return files


# --------------------------------------------------------------------------
# Output


def write_tsv(sites: List[Site], files: Dict[str, SourceFile], out: TextIO) -> None:
    out.write("category\tfile\tline\tunit\tstatus\tdetail\tcode\n")
    for site in sites:
        source = files[site.path]
        code = site.code.replace("\t", " ")
        out.write(
            f"{site.category}\t{site.path}\t{site.line}\t{source.unit}\t"
            f"{source.status}\t{site.detail}\t{code}\n"
        )


def write_html(
    sites: List[Site],
    files: List[SourceFile],
    categories: List[Category],
    path: Path,
    meta: dict,
) -> None:
    file_index = {source.path: index for index, source in enumerate(files)}
    category_index = {category.id: index for index, category in enumerate(categories)}
    data = {
        "meta": meta,
        "families": FAMILIES,
        "categories": [[c.id, c.family, c.message] for c in categories],
        "files": [[f.path, f.status, f.match] for f in files],
        "sites": [
            [category_index[s.category], file_index[s.path], s.line, s.detail, s.code]
            for s in sites
        ],
    }
    payload = json.dumps(data, separators=(",", ":")).replace("</", "<\\/")
    html = TEMPLATE_PATH.read_text(encoding="utf-8").replace("__DATA__", payload)
    path.write_text(html, encoding="utf-8")


def summarize(sites: List[Site], categories: List[Category]) -> None:
    by_category = Counter(site.category for site in sites)
    family_of = {category.id: category.family for category in categories}
    by_family = Counter(family_of[site.category] for site in sites)
    print(
        f"{len(sites)} sites in {len({site.path for site in sites})} files: "
        + ", ".join(f"{by_family[family]} {family}" for family in FAMILIES)
    )
    for family in FAMILIES:
        print(f"\n  {family}")
        for category in categories:
            if category.family == family and by_category[category.id]:
                print(
                    f"  {by_category[category.id]:6d}  {category.id:<22} {category.message}"
                )
    print("\n  most sites")
    for path, count in Counter(site.path for site in sites).most_common(10):
        print(f"  {count:6d}  {path}")


def main() -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "--out", type=Path, help="write index.html and cleanup_index.tsv here"
    )
    parser.add_argument("--tsv", help="write the TSV to this file ('-' for stdout)")
    parser.add_argument("--report", type=Path, help="report.json, for match scores")
    parser.add_argument("--revision", default="", help="commit the page describes")
    parser.add_argument("--generated", default="", help="date shown on the page")
    parser.add_argument(
        "--repo",
        default="https://github.com/pbr-ret/pbr-decomp",
        help="repository the page links into",
    )
    args = parser.parse_args()

    categories, blank_macros = load_categories()
    paths = list(source_paths())
    sites = [
        site for path in paths for site in scan_file(path, categories, blank_macros)
    ]
    sites.sort(key=lambda site: (site.path, site.line))
    files = describe_files(paths, load_units(), load_scores(args.report))
    by_path = {source.path: source for source in files}

    if args.tsv == "-":
        write_tsv(sites, by_path, sys.stdout)
    elif args.tsv:
        with open(args.tsv, "w", encoding="utf-8") as handle:
            write_tsv(sites, by_path, handle)
    if args.out:
        args.out.mkdir(parents=True, exist_ok=True)
        meta = {
            "revision": args.revision,
            "generated": args.generated,
            "repo": args.repo.rstrip("/"),
            "scores": args.report is not None,
        }
        write_html(sites, files, categories, args.out / "index.html", meta)
        with open(args.out / "cleanup_index.tsv", "w", encoding="utf-8") as handle:
            write_tsv(sites, by_path, handle)
        print(f"wrote {args.out}/index.html and {args.out}/cleanup_index.tsv")
    if not args.tsv and not args.out:
        summarize(sites, categories)
    return 0


if __name__ == "__main__":
    sys.exit(main())
