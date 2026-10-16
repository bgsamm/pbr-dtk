#!/usr/bin/env python3
"""Update the progress section of README.md from build/RPBP01/report.json.

Run after `ninja`:  python3 tools/progress.py
The section between the `progress:start` and `progress:end` markers is replaced.
"""

import datetime
import json
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REPORT = os.path.join(ROOT, "build", "RPBP01", "report.json")
README = os.path.join(ROOT, "README.md")

# Areas of main.dol, see docs/architecture.md (boundaries are approximate)
AREAS = [
    ("Startup", [(0x80004000, 0x80006BC4)]),
    ("Game entry point", [(0x80006BC4, 0x80010000)]),
    ("Battle presentation", [(0x80010000, 0x80058000)]),
    ("Scenes and menus", [(0x80058000, 0x80158000)]),
    ("Save data and Wi-Fi data", [(0x80158000, 0x80169000)]),
    ("Battle loop and camera", [(0x80169000, 0x801C6C48)]),
    ("Runtime, C library and MetroTRK", [(0x801C6C48, 0x801DAA30)]),
    ("gs engine", [(0x801DAA30, 0x80250000)]),
    ("Game sound", [(0x80250000, 0x8025B6AC)]),
    ("Game networking", [(0x8025B6AC, 0x80268228)]),
    ("Revolution SDK", [(0x80268228, 0x80304DC4)]),
    ("Other Nintendo libraries (VF, DWC, NW4R, HOME menu)", [(0x80304DC4, 0x8038F424), (0x8039A068, 0x803A60D8)]),
    ("Battle engine (ported from the DS games)", [(0x803A60D8, 0x803D9208)]),
    ("Pokémon data", [(0x8038F424, 0x8039A068), (0x803D9208, 0x803E3000)]),
]


def bar(percent, width=20):
    filled = round(percent / 100 * width)
    return "█" * filled + "░" * (width - filled)


def main():
    with open(REPORT) as f:
        report = json.load(f)
    measures = report["measures"]

    totals = {name: [0, 0] for name, _ in AREAS}
    for unit in report["units"]:
        for func in unit.get("functions", []):
            address = func.get("metadata", {}).get("virtual_address")
            if address is None:
                continue
            address = int(address)
            size = int(func.get("size", 0))
            matched = func.get("fuzzy_match_percent", 0) == 100
            for name, ranges in AREAS:
                if any(start <= address < end for start, end in ranges):
                    totals[name][0] += size
                    if matched:
                        totals[name][1] += size
                    break

    code = measures["matched_code_percent"]
    linked = measures.get("complete_code_percent", measures.get("linked_code_percent", 0.0))
    lines = [
        "<!-- progress:start -->",
        f"![Code matched](https://img.shields.io/badge/code%20matched-{code:.1f}%25-blue)"
        f" ![Functions](https://img.shields.io/badge/functions-{measures['matched_functions']}%2F{measures['total_functions']}-blue)"
        f" ![Linked](https://img.shields.io/badge/linked-{linked:.1f}%25-green)",
        "",
        f"**{code:.2f} %** of the code matches the original "
        f"({measures['matched_functions']:,} of {measures['total_functions']:,} functions). "
        f"**{linked:.2f} %** is in finished units linked into the build.",
        "",
        "| Area | Size | Matched | |",
        "|---|---:|---:|---|",
    ]
    for name, _ in AREAS:
        total, matched = totals[name]
        percent = 100 * matched / total if total else 0.0
        lines.append(f"| {name} | {total / 1024:,.0f} KiB | {percent:.1f} % | `{bar(percent)}` |")
    lines += [
        "",
        f"_Updated {datetime.date.today().isoformat()} from the objdiff report of a local build._",
        "<!-- progress:end -->",
    ]

    with open(README) as f:
        text = f.read()
    text = re.sub(
        r"<!-- progress:start -->.*?<!-- progress:end -->",
        "\n".join(lines),
        text,
        flags=re.S,
    )
    with open(README, "w") as f:
        f.write(text)


if __name__ == "__main__":
    main()
