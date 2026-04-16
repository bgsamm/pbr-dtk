#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "RPBP01",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-gdwarf-2")
if args.map:
    config.ldflags.append("-mapunused")
    config.ldflags.append("-listclosure")

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

cflags_includes = [
    "-i include",
    "-i libs/MSL/include",
    "-i libs/RVL_SDK/include",
    f"-i build/{config.version}/include",
]

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-str reuse",
    "-enc SJIS",
    *cflags_includes,
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

# Debug flags
if args.debug:
    cflags_base.extend(["-sym dwarf-2", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
    "-fp_contract on",
]

# RVL SDK flags
cflags_sdk = [
    *cflags_base,
    "-ipa file",
    "-inline auto",
    "-fp_contract off",
]

# Main game flags
cflags_game = [
    *cflags_base,
    "-inline on",
    "-fp_contract off",
]

config.linker_version = "GC/3.0a5.2"

config.src_dir = "src"

# Helper function for RVL SDK libraries
def RVLSDKLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": config.linker_version,
        "cflags": cflags_sdk,
        "progress_category": "sdk",
        "objects": objects,
        "src_dir": "libs/RVL_SDK/src",
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",  # str | List[str]
        "objects": [
            Object(NonMatching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
        ],
    },
    RVLSDKLib("os", [
            Object(Matching, "os/OSSemaphore.c"),
            Object(Matching, "os/OSSync.c"),
            Object(NonMatching, "os/OSThread.c"),
        ]
    ),
    {
        "lib": "game",
        "mw_version": config.linker_version,
        "cflags": cflags_game,
        "progress_category": "game",
        "objects": [
            Object(NonMatching, "main.cpp"),
            Object(NonMatching, "wip/800559D4.cpp"),
            Object(NonMatching, "wip/8005B4A4.cpp"),
        ],
    },
    {
        "lib": "gs",
        "mw_version": config.linker_version,
        "cflags": cflags_game,
        "progress_category": "game",
        "objects": [
            Object(Matching, "gs/operators.cpp"),
            Object(Matching, "gs/GSmem.cpp"),
            Object(Matching, "gs/cache/GScache.cpp"),
            Object(Matching, "gs/cache/GScacheScratchpad.cpp"),
            Object(Matching, "gs/cache/GScachePool.cpp"),
            Object(Matching, "gs/GSfile.cpp"),
            Object(NonMatching, "gs/GSnand.cpp"),
            Object(NonMatching, "wip/801DD5C8.cpp"),
            Object(NonMatching, "wip/801DD8C0.cpp"),
            Object(NonMatching, "wip/801DDF78.cpp"),
            Object(NonMatching, "wip/801DF040.cpp"),
            Object(NonMatching, "wip/801E07E8.cpp"),
            Object(NonMatching, "wip/801E0810.cpp"),
            Object(NonMatching, "wip/801E0A54.cpp"),
            Object(NonMatching, "wip/801E4360.cpp"),
            Object(NonMatching, "wip/801E474C.cpp"),
            Object(NonMatching, "wip/801E5F7C.cpp"),
            Object(NonMatching, "wip/801E6BF8.cpp"),
            Object(NonMatching, "wip/801ED3F0.cpp"),
            Object(NonMatching, "wip/801EE044.cpp"),
            Object(NonMatching, "wip/801F1AE8.cpp"),
            Object(NonMatching, "wip/801F40E0.cpp"),
            Object(NonMatching, "wip/801F98EC.cpp"),
            Object(NonMatching, "wip/801FA094.cpp"),
            Object(NonMatching, "wip/801FA38C.cpp"),
            Object(NonMatching, "wip/801FB42C.cpp"),
            Object(NonMatching, "wip/801FF308.cpp"),
            Object(Matching, "gs/math/GSrand.cpp"),
            Object(Matching, "gs/math/GStrig.cpp"),
            Object(Matching, "gs/math/GSquat.cpp"),
            Object(Matching, "gs/math/GSmathInit.cpp"),
            Object(Matching, "gs/GStask.cpp"),
            Object(Matching, "gs/GSthread.cpp"),
            Object(Matching, "gs/GStimeline.cpp"),
            Object(NonMatching, "wip/80226364.cpp"),
            Object(NonMatching, "gs/render/GSrender.cpp"),
            Object(NonMatching, "gs/render/8023234C.cpp"),
            Object(Matching, "gs/render/GSrenderLight.cpp"),
            Object(NonMatching, "gs/render/802377BC.cpp"),
            Object(NonMatching, "gs/GSvideo.cpp"),
            Object(NonMatching, "gs/input/GSinput.cpp"),
            Object(NonMatching, "gs/input/802448E8.cpp"),
            Object(Matching, "gs/fsys/GSfsysMem.cpp"),
            Object(Matching, "gs/fsys/GSfsysChunk.cpp"),
            Object(Matching, "gs/fsys/GSfsysCache.cpp"),
            Object(Matching, "gs/fsys/GSfsysRead.cpp"),
            Object(Matching, "gs/fsys/GSfsysStream.cpp"),
            Object(NonMatching, "gs/fsys/80247038.cpp"),
            Object(NonMatching, "gs/fsys/GSfsys.cpp"),
            Object(NonMatching, "wip/80249B7C.cpp"),
            Object(NonMatching, "wip/80249BA0.cpp"),
            Object(Matching, "gs/debug/regionOverride.cpp"),
            Object(NonMatching, "wip/80249BF0.cpp"),
            Object(NonMatching, "wip/8025B6AC.cpp"),
        ],
    },
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
