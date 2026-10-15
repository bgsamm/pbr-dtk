#!/usr/bin/env python3
"""Print the C/C++ units of a tree and how to compile them, as JSON.

Run from the root of a checkout: it loads that checkout's configure.py
without writing build.ninja, so it works without the game files.

Usage: python tools/qa/units.py <output.json> [configure.py arguments...]
"""

import json
import os
import runpy
import sys
from pathlib import Path


def main() -> None:
    output = Path(sys.argv[1]).resolve()
    root = Path.cwd()
    sys.path.insert(0, str(root))

    import tools.project as project

    project.generate_build = lambda config: None  # type: ignore[assignment]
    sys.argv = ["configure.py", *sys.argv[2:], "configure"]
    config = runpy.run_path("configure.py", run_name="__main__")["config"]

    wrapper = config.compiler_wrapper()
    if config.sjiswrap_path:
        sjiswrap = Path(config.sjiswrap_path)
    else:
        sjiswrap = config.build_dir / "tools" / "sjiswrap.exe"

    units = []
    for lib in config.libs:
        for obj in lib["objects"]:
            resolved = obj.resolve(config, lib)
            src = resolved.src_path
            if src is None or not project.file_is_c_cpp(src) or not src.exists():
                continue
            options = resolved.options
            cflags = list(options["cflags"])
            extra_cflags = list(options["extra_cflags"] or [])
            if not any(flag.startswith("-lang") for flag in cflags + extra_cflags):
                extra_cflags.insert(
                    0, "-lang=c++" if project.file_is_cpp(src) else "-lang=c"
                )
            cflags += extra_cflags
            units.append(
                {
                    "name": obj.name,
                    "source": src.as_posix(),
                    "matching": bool(obj.completed),
                    "compiler": (
                        root
                        / config.compilers()
                        / options["mw_version"]
                        / "mwcceppc.exe"
                    ).as_posix(),
                    "cflags": cflags,
                    "shift_jis": bool(options["shift_jis"]),
                }
            )

    tools = {
        "wrapper": None if wrapper is None else _absolute(root, wrapper),
        "sjiswrap": _absolute(root, sjiswrap),
        "binutils": _absolute(
            root, config.binutils_path or config.build_dir / "binutils"
        ),
        "symbols": (root / "config" / config.version / "symbols.txt").as_posix(),
        "splits": (root / "config" / config.version / "splits.txt").as_posix(),
    }
    output.write_text(json.dumps({"tools": tools, "units": units}, indent=1))


def _absolute(root: Path, path: Path) -> str:
    path = Path(path)
    if (
        not path.is_absolute()
        and os.sep not in str(path)
        and not (root / path).exists()
    ):
        return str(path)  # a command on PATH, such as wine
    return (root / path).as_posix()


if __name__ == "__main__":
    main()
