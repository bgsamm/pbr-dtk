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
    "-i libs/Runtime/include",
    "-i libs/RevoEX/include",
    "-i libs/MetroTRK/include",
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
    "-ipa file",
    "-inline on",
    "-fp_contract off",
    "-RTTI on",
]

config.linker_version = "GC/3.0a5.2"

config.src_dir = Path("src")


def RuntimeLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "runtime",
        "objects": objects,
        "src_dir": "libs/Runtime/src",
    }


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


Matching = True  # Object matches and should be linked
NonMatching = False  # Object does not match and should not be linked
Equivalent = (
    config.non_matching
)  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    RuntimeLib(
        "Runtime.PPCEABI.H",
        [
            Object(NonMatching, "global_destructor_chain.c"),
            Object(NonMatching, "__init_cpp_exceptions.cpp"),
        ],
    ),
    RVLSDKLib(
        "os",
        [
            Object(Matching, "os/OSReset.c"),
            Object(Matching, "os/OSRtc.c"),
            Object(Matching, "os/OSSemaphore.c"),
            Object(Matching, "os/OSSync.c"),
            Object(NonMatching, "os/OSThread.c"),
            Object(NonMatching, "os/OSAlarm.c"),
            Object(NonMatching, "os/OSAlloc.c"),
            Object(NonMatching, "os/OSArena.c"),
            Object(NonMatching, "os/OSContext.c"),
            Object(NonMatching, "os/OSFont.c"),
            Object(NonMatching, "os/OSInterrupt.c"),
            Object(NonMatching, "os/OSLink.c"),
            Object(NonMatching, "os/OSMessage.c"),
            Object(NonMatching, "os/OSMemory.c"),
            Object(NonMatching, "os/OSTime.c"),
            Object(NonMatching, "os/OSUtf.c"),
            Object(NonMatching, "os/OSIpc.c"),
            Object(NonMatching, "os/OS.c"),
            Object(NonMatching, "os/OSAudioSystem.c"),
            Object(NonMatching, "os/OSCache.c"),
            Object(NonMatching, "os/OSStateTM.c"),
            Object(NonMatching, "os/OSPlayRecord.c"),
            Object(NonMatching, "os/OSStateFlags.c"),
            Object(NonMatching, "os/OSNet.c"),
            Object(NonMatching, "os/OSNandbootInfo.c"),
            Object(NonMatching, "os/__ppc_eabi_init.cpp"),
        ],
    ),
    RVLSDKLib(
        "base",
        [
            Object(NonMatching, "base/PPCArch.c"),
        ],
    ),
    RVLSDKLib(
        "exi",
        [
            Object(NonMatching, "exi/EXIBios.c"),
            Object(NonMatching, "exi/EXIUart.c"),
        ],
    ),
    RVLSDKLib(
        "si",
        [
            Object(NonMatching, "si/SISamplingRate.c"),
        ],
    ),
    RVLSDKLib(
        "db",
        [
            Object(NonMatching, "db/db.c"),
        ],
    ),
    RVLSDKLib(
        "vi",
        [
            Object(NonMatching, "vi/vi.c"),
            Object(NonMatching, "vi/i2c.c"),
            Object(NonMatching, "vi/vi3in1.c"),
        ],
    ),
    RVLSDKLib(
        "nand",
        [
            Object(NonMatching, "nand/nand.c"),
        ],
    ),
    RVLSDKLib(
        "mtx",
        [
            Object(NonMatching, "mtx/mtx.c"),
            Object(NonMatching, "mtx/mtxvec.c"),
            Object(NonMatching, "mtx/vec.c"),
        ],
    ),
    RVLSDKLib(
        "gx",
        [
            Object(NonMatching, "gx/GXInit.c"),
            Object(NonMatching, "gx/GXFifo.c"),
            Object(NonMatching, "gx/GXAttr.c"),
            Object(NonMatching, "gx/GXMisc.c"),
            Object(NonMatching, "gx/GXGeometry.c"),
            Object(NonMatching, "gx/GXFrameBuf.c"),
            Object(NonMatching, "gx/GXLight.c"),
            Object(NonMatching, "gx/GXTexture.c"),
            Object(NonMatching, "gx/GXBump.c"),
            Object(NonMatching, "gx/GXTev.c"),
            Object(NonMatching, "gx/GXPixel.c"),
            Object(NonMatching, "gx/GXDisplayList.c"),
            Object(NonMatching, "gx/GXTransform.c"),
            Object(NonMatching, "gx/GXPerf.c"),
        ],
    ),
    RVLSDKLib(
        "dvd",
        [
            Object(NonMatching, "dvd/dvdqueue.c"),
            Object(NonMatching, "dvd/dvdfs.c"),
        ],
    ),
    RVLSDKLib(
        "mem",
        [
            Object(NonMatching, "mem/mem_expHeap.c"),
            Object(NonMatching, "mem/mem_frameHeap.c"),
            Object(NonMatching, "mem/mem_allocator.c"),
            Object(NonMatching, "mem/mem_list.c"),
        ],
    ),
    RVLSDKLib(
        "cx",
        [
            Object(NonMatching, "cx/CXUncompression.c"),
        ],
    ),
    RVLSDKLib(
        "ipc",
        [
            Object(NonMatching, "ipc/ipcMain.c"),
            Object(NonMatching, "ipc/memory.c"),
            Object(NonMatching, "ipc/ipcProfile.c"),
        ],
    ),
    RVLSDKLib(
        "wpad",
        [
            Object(NonMatching, "wpad/WPADEncrypt.c"),
            Object(NonMatching, "wpad/debug_msg.c"),
            Object(NonMatching, "wpad/WPAD.c"),
        ],
    ),
    RVLSDKLib(
        "euart",
        [
            Object(NonMatching, "euart/euart.c"),
        ],
    ),
    {
        "lib": "game",
        "mw_version": config.linker_version,
        "cflags": cflags_game,
        "progress_category": "game",
        "objects": [
            Object(NonMatching, "main.cpp"),
            Object(NonMatching, "ds/DSbridge.cpp", extra_cflags=["-O4,s", "-inline noauto"]),
            Object(NonMatching, ".unsorted/800559D4.cpp"),
            Object(NonMatching, ".unsorted/8005B4A4.cpp"),
            Object(NonMatching, ".unsorted/80177C24.cpp"),
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
            Object(NonMatching, "gs/GSnand.cpp"),  # 801DCE6C
            Object(Matching, "gs/scene/GSanimationPlayer.cpp"),  # 801DD5C8
            Object(Matching, "gs/scene/GSanimationObject.cpp"),  # 801DD8C0
            Object(NonMatching, "gs/GSsceneData.cpp"),  # 801E0A54
            Object(NonMatching, "gs/GSobject.cpp"),  # 801F40E0
            Object(Matching, "gs/GSscene.cpp"),  # 801FA094
            Object(NonMatching, "gs/GShierarchyModule.cpp"),  # 802000BC
            Object(Matching, "gs/math/GSrand.cpp"),  # 80223830
            Object(Matching, "gs/math/GStrig.cpp"),
            Object(Matching, "gs/math/GSquat.cpp"),
            Object(Matching, "gs/math/GSmathInit.cpp"),
            Object(Matching, "gs/GStask.cpp"),
            Object(Matching, "gs/GSthread.cpp"),
            Object(Matching, "gs/GStimeline.cpp"),
            Object(NonMatching, ".unsorted/80226364.cpp"),
            Object(NonMatching, "gs/render/GSrender.cpp"),
            Object(NonMatching, "gs/render/8023234C.cpp"),
            Object(NonMatching, "gs/render/8023283C.cpp"),
            Object(NonMatching, "gs/render/80232D24.cpp"),
            Object(NonMatching, "gs/render/802353F8.cpp"),
            Object(Matching, "gs/render/GSrenderLight.cpp"),
            Object(NonMatching, "gs/render/80235A74.cpp"),
            Object(NonMatching, "gs/render/80236704.cpp"),
            Object(NonMatching, "gs/render/GSrenderModule.cpp"),
            Object(NonMatching, "gs/render/GSrenderPass.cpp"),
            Object(NonMatching, "gs/render/80237794.cpp"),
            Object(NonMatching, "gs/render/GSrenderTarget.cpp"),
            Object(NonMatching, "gs/render/8023B64C.cpp"),
            Object(NonMatching, "gs/render/8023B9F4.cpp"),
            Object(NonMatching, "gs/render/GStexture.cpp"),
            Object(NonMatching, "gs/render/8023EA44.cpp"),
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
            Object(NonMatching, ".unsorted/80249B7C.cpp"),
            Object(NonMatching, ".unsorted/80249BA0.cpp"),
            Object(Matching, "gs/debug/regionOverride.cpp"),
            Object(Matching, "gs/GSlinkedList.cpp"),  # 80249BF0
            Object(NonMatching, ".unsorted/8025B6AC.cpp"),
        ],
    },
    {
        "lib": "unsorted",
        "mw_version": config.linker_version,
        "cflags": cflags_game,
        "progress_category": "unsorted",
        "objects": [
            Object(NonMatching, ".unsorted/8000748C.cpp"),
            Object(NonMatching, ".unsorted/80007940.cpp"),
            Object(NonMatching, ".unsorted/800097D8.cpp"),
            Object(NonMatching, ".unsorted/8000A7C4.cpp"),
            Object(NonMatching, ".unsorted/8000AAC4.cpp"),
            Object(NonMatching, ".unsorted/8000ADC0.cpp"),
            Object(NonMatching, ".unsorted/80024914.cpp"),
            Object(NonMatching, ".unsorted/80025390.cpp"),
            Object(NonMatching, ".unsorted/800284B0.cpp"),
            Object(NonMatching, ".unsorted/8002A910.cpp"),
            Object(NonMatching, ".unsorted/8002ABE8.cpp"),
            Object(NonMatching, ".unsorted/8002BB44.cpp"),
            Object(NonMatching, ".unsorted/8002CB00.cpp"),
            Object(NonMatching, ".unsorted/8002DE2C.cpp"),
            Object(NonMatching, ".unsorted/80030134.cpp"),
            Object(NonMatching, ".unsorted/80030320.cpp"),
            Object(NonMatching, ".unsorted/80030BA0.cpp"),
            Object(NonMatching, ".unsorted/800310D8.cpp"),
            Object(NonMatching, ".unsorted/80031544.cpp"),
            Object(NonMatching, ".unsorted/800321E4.cpp"),
            Object(NonMatching, ".unsorted/800324A8.cpp"),
            Object(NonMatching, ".unsorted/80032BC8.cpp"),
            Object(NonMatching, ".unsorted/80032E60.cpp"),
            Object(NonMatching, ".unsorted/80032FE8.cpp"),
            Object(NonMatching, ".unsorted/80035CB0.cpp"),
            Object(NonMatching, ".unsorted/80036F88.cpp"),
            Object(NonMatching, ".unsorted/8003E03C.cpp"),
            Object(NonMatching, ".unsorted/8003E854.cpp"),
            Object(NonMatching, ".unsorted/800400E8.cpp"),
            Object(NonMatching, ".unsorted/800447E4.cpp"),
            Object(NonMatching, ".unsorted/80044F28.cpp"),
            Object(NonMatching, ".unsorted/800477E8.cpp"),
            Object(NonMatching, ".unsorted/800478C0.cpp"),
            Object(NonMatching, ".unsorted/80048728.cpp"),
            Object(NonMatching, ".unsorted/80049084.cpp"),
            Object(NonMatching, ".unsorted/8004ACF4.cpp"),
            Object(NonMatching, ".unsorted/8004D724.cpp"),
            Object(NonMatching, ".unsorted/8004DE88.cpp"),
            Object(NonMatching, ".unsorted/8004E9F0.cpp"),
            Object(NonMatching, ".unsorted/8004F37C.cpp"),
            Object(NonMatching, ".unsorted/8005018C.cpp"),
            Object(NonMatching, ".unsorted/80050324.cpp"),
            Object(NonMatching, ".unsorted/80055504.cpp"),
            Object(NonMatching, ".unsorted/800598F8.cpp"),
            Object(NonMatching, ".unsorted/8005A588.cpp"),
            Object(NonMatching, ".unsorted/8005CEAC.cpp"),
            Object(NonMatching, ".unsorted/8006A878.cpp"),
            Object(NonMatching, ".unsorted/8006E554.cpp"),
            Object(NonMatching, ".unsorted/8007CFB0.cpp"),
            Object(NonMatching, ".unsorted/8007F8C4.cpp"),
            Object(NonMatching, ".unsorted/8008A2D4.cpp"),
            Object(NonMatching, ".unsorted/8008D8CC.cpp"),
            Object(NonMatching, ".unsorted/80091268.cpp"),
            Object(NonMatching, ".unsorted/80094DC0.cpp"),
            Object(NonMatching, ".unsorted/8009598C.cpp"),
            Object(NonMatching, ".unsorted/8009A2BC.cpp"),
            Object(NonMatching, ".unsorted/8009C1A8.cpp"),
            Object(NonMatching, ".unsorted/8009F6C4.cpp"),
            Object(NonMatching, ".unsorted/800AA038.cpp"),
            Object(NonMatching, ".unsorted/800AA470.cpp"),
            Object(NonMatching, ".unsorted/800B9E10.cpp"),
            Object(NonMatching, ".unsorted/800C5968.cpp"),
            Object(NonMatching, ".unsorted/800D7C90.cpp"),
            Object(NonMatching, ".unsorted/800E4234.cpp"),
            Object(NonMatching, ".unsorted/800E96C4.cpp"),
            Object(NonMatching, ".unsorted/800F8AC4.cpp"),
            Object(NonMatching, ".unsorted/80104354.cpp"),
            Object(NonMatching, ".unsorted/801166F8.cpp"),
            Object(NonMatching, ".unsorted/8011B19C.cpp"),
            Object(NonMatching, ".unsorted/8011C954.cpp"),
            Object(NonMatching, ".unsorted/8011C974.cpp"),
            Object(NonMatching, ".unsorted/8011E1FC.cpp"),
            Object(NonMatching, ".unsorted/8012F0D8.cpp"),
            Object(NonMatching, ".unsorted/80131CF0.cpp"),
            Object(NonMatching, ".unsorted/8013A930.cpp"),
            Object(NonMatching, ".unsorted/8013F044.cpp"),
            Object(NonMatching, ".unsorted/8014FEA8.cpp"),
            Object(NonMatching, ".unsorted/80151474.cpp"),
            Object(NonMatching, ".unsorted/80155B50.cpp"),
            Object(NonMatching, ".unsorted/80157854.cpp"),
            Object(NonMatching, ".unsorted/801581B8.cpp"),
            Object(NonMatching, ".unsorted/80158E50.cpp"),
            Object(NonMatching, ".unsorted/8015D390.cpp"),
            Object(NonMatching, ".unsorted/80162784.cpp"),
            Object(NonMatching, ".unsorted/80162B70.cpp"),
            Object(NonMatching, ".unsorted/8016340C.cpp"),
            Object(NonMatching, ".unsorted/80163674.cpp"),
            Object(NonMatching, ".unsorted/80164CE8.cpp"),
            Object(NonMatching, ".unsorted/80164E3C.cpp"),
            Object(NonMatching, ".unsorted/80164FA0.cpp"),
            Object(NonMatching, ".unsorted/80165534.cpp"),
            Object(NonMatching, ".unsorted/80166D6C.cpp"),
            Object(NonMatching, ".unsorted/80167298.cpp"),
            Object(NonMatching, ".unsorted/80167820.cpp"),
            Object(NonMatching, ".unsorted/80167994.cpp"),
            Object(NonMatching, ".unsorted/801679F8.cpp"),
            Object(NonMatching, ".unsorted/801682D0.cpp"),
            Object(NonMatching, ".unsorted/80168798.cpp"),
            Object(NonMatching, ".unsorted/80168C1C.cpp"),
            Object(NonMatching, ".unsorted/80169268.cpp"),
            Object(NonMatching, ".unsorted/801697AC.cpp"),
            Object(NonMatching, ".unsorted/8016A25C.cpp"),
            Object(NonMatching, ".unsorted/8016E2B8.cpp"),
            Object(NonMatching, ".unsorted/8016EFCC.cpp"),
            Object(NonMatching, ".unsorted/801708DC.cpp"),
            Object(NonMatching, ".unsorted/80176EB4.cpp"),
            Object(NonMatching, ".unsorted/8017B4B8.cpp"),
            Object(NonMatching, ".unsorted/8017C588.cpp"),
            Object(NonMatching, ".unsorted/8017C980.cpp"),
            Object(NonMatching, ".unsorted/8017CC8C.cpp"),
            Object(NonMatching, ".unsorted/8017E3F4.cpp"),
            Object(NonMatching, ".unsorted/8017E954.cpp"),
            Object(NonMatching, ".unsorted/80185AE0.cpp"),
            Object(NonMatching, ".unsorted/8018777C.cpp"),
            Object(NonMatching, ".unsorted/8019BEC4.cpp"),
            Object(NonMatching, ".unsorted/801C7830.cpp"),
            Object(NonMatching, "gs/scene/GScamera.cpp"),
            Object(NonMatching, "gs/scene/GSvolumeNode.cpp"),
            Object(NonMatching, ".unsorted/801E07E8.cpp"),
            Object(NonMatching, ".unsorted/801E0810.cpp"),
            Object(NonMatching, "gs/scene/GSjointNode.cpp"),
            Object(NonMatching, ".unsorted/801E474C.cpp"),
            Object(NonMatching, "gs/scene/GSlight.cpp"),
            Object(NonMatching, "gs/scene/GSmaterial.cpp"),
            Object(NonMatching, "gs/scene/GSmesh.cpp"),
            Object(NonMatching, "gs/scene/GSmodel.cpp"),
            Object(NonMatching, "gs/scene/GSnull.cpp"),
            Object(NonMatching, "gs/scene/GSparticle.cpp"),
            Object(NonMatching, ".unsorted/801FA38C.cpp"),
            Object(NonMatching, ".unsorted/801FB42C.cpp"),
            Object(NonMatching, ".unsorted/801FF308.cpp"),
            Object(NonMatching, "gs/GSmenuModule.cpp"),
            Object(NonMatching, ".unsorted/80204058.cpp"),
            Object(NonMatching, ".unsorted/80205954.cpp"),
            Object(NonMatching, ".unsorted/802078B8.cpp"),
            Object(NonMatching, ".unsorted/80207C4C.cpp"),
            Object(NonMatching, ".unsorted/8020B4F8.cpp"),
            Object(NonMatching, ".unsorted/8020CA38.cpp"),
            Object(NonMatching, ".unsorted/8020D250.cpp"),
            Object(NonMatching, ".unsorted/8020EB1C.cpp"),
            Object(NonMatching, ".unsorted/8020F998.cpp"),
            Object(NonMatching, ".unsorted/80211564.cpp"),
            Object(NonMatching, ".unsorted/80211A04.cpp"),
            Object(NonMatching, ".unsorted/80213694.cpp"),
            Object(NonMatching, ".unsorted/80219E48.cpp"),
            Object(NonMatching, ".unsorted/8021C220.cpp"),
            Object(NonMatching, ".unsorted/8021CAA0.cpp"),
            Object(NonMatching, ".unsorted/8021D0E0.cpp"),
            Object(NonMatching, ".unsorted/8021D424.cpp"),
            Object(NonMatching, ".unsorted/8021EA48.cpp"),
            Object(NonMatching, ".unsorted/8021FB44.cpp"),
            Object(NonMatching, "gs/math/GSboundingBox.cpp"),
            Object(NonMatching, ".unsorted/80220DC4.cpp"),
            Object(NonMatching, ".unsorted/802233C8.cpp"),
            Object(NonMatching, ".unsorted/80223694.cpp"),
            Object(NonMatching, ".unsorted/802236C0.cpp"),
            Object(NonMatching, ".unsorted/8022494C.cpp"),
            Object(NonMatching, ".unsorted/80224B10.cpp"),
            Object(NonMatching, ".unsorted/80225E44.cpp"),
            Object(NonMatching, ".unsorted/8022773C.cpp"),
            Object(NonMatching, ".unsorted/80228970.cpp"),
            Object(NonMatching, ".unsorted/80228B0C.cpp"),
            Object(NonMatching, ".unsorted/8022910C.cpp"),
            Object(NonMatching, ".unsorted/8022D72C.cpp"),
            Object(NonMatching, ".unsorted/80230BD4.cpp"),
            Object(NonMatching, ".unsorted/80240060.cpp"),
            Object(NonMatching, ".unsorted/8024052C.cpp"),
            Object(NonMatching, ".unsorted/80249D38.cpp"),
            Object(NonMatching, ".unsorted/80250F18.cpp"),
            Object(NonMatching, ".unsorted/80253FEC.cpp"),
            Object(NonMatching, ".unsorted/80254260.cpp"),
            Object(NonMatching, ".unsorted/80254460.cpp"),
            Object(NonMatching, ".unsorted/8025716C.cpp"),
            Object(NonMatching, ".unsorted/80259AA4.cpp"),
            Object(NonMatching, ".unsorted/8025A710.cpp"),
            Object(NonMatching, ".unsorted/8025AD84.cpp"),
            Object(NonMatching, ".unsorted/8025B164.cpp"),
            Object(NonMatching, ".unsorted/8025B6E8.cpp"),
            Object(NonMatching, ".unsorted/8025D3B8.cpp"),
            Object(NonMatching, ".unsorted/8025D7CC.cpp"),
            Object(NonMatching, ".unsorted/8025DCC0.cpp"),
            Object(NonMatching, ".unsorted/8025DF80.cpp"),
            Object(NonMatching, ".unsorted/8025E348.cpp"),
            Object(NonMatching, ".unsorted/8025E86C.cpp"),
            Object(NonMatching, ".unsorted/8025EC68.cpp"),
            Object(NonMatching, ".unsorted/8025F07C.cpp"),
            Object(NonMatching, ".unsorted/8025FFF8.cpp"),
            Object(NonMatching, ".unsorted/802609E0.cpp"),
            Object(NonMatching, ".unsorted/8026138C.cpp"),
            Object(NonMatching, ".unsorted/80262B00.cpp"),
            Object(NonMatching, ".unsorted/80262E90.cpp"),
            Object(NonMatching, ".unsorted/80263CBC.cpp"),
            Object(NonMatching, ".unsorted/802674CC.cpp"),
            Object(NonMatching, ".unsorted/80363510.cpp"),
            Object(NonMatching, ".unsorted/80363618.cpp"),
            Object(NonMatching, ".unsorted/80363C30.cpp"),
            Object(NonMatching, ".unsorted/80363E84.cpp"),
            Object(NonMatching, ".unsorted/80367FAC.cpp"),
            Object(NonMatching, ".unsorted/8036E198.cpp"),
            Object(NonMatching, ".unsorted/8037536C.cpp"),
            Object(NonMatching, ".unsorted/8037C450.cpp"),
            Object(NonMatching, ".unsorted/8037F908.cpp"),
            Object(NonMatching, ".unsorted/803839A4.cpp"),
            Object(NonMatching, ".unsorted/80385E20.cpp"),
            Object(NonMatching, ".unsorted/803872DC.cpp"),
            Object(NonMatching, ".unsorted/80387EB4.cpp"),
            Object(NonMatching, ".unsorted/8038A32C.cpp"),
            Object(NonMatching, ".unsorted/8038A3D8.cpp"),
            Object(NonMatching, ".unsorted/8038F424.cpp"),
            Object(NonMatching, ".unsorted/8026B49C.cpp"),
            Object(NonMatching, ".unsorted/8026F910.cpp"),
            Object(NonMatching, ".unsorted/80272BCC.cpp"),
            Object(NonMatching, ".unsorted/80275DEC.cpp"),
            Object(NonMatching, ".unsorted/80276120.cpp"),
            Object(NonMatching, ".unsorted/8027738C.cpp"),
            Object(NonMatching, ".unsorted/80277498.cpp"),
            Object(NonMatching, ".unsorted/8027C5C0.cpp"),
            Object(NonMatching, ".unsorted/8027CA50.cpp"),
            Object(NonMatching, ".unsorted/8027CE24.cpp"),
            Object(NonMatching, ".unsorted/80281F38.cpp"),
            Object(NonMatching, ".unsorted/80284950.cpp"),
            Object(NonMatching, ".unsorted/8028680C.cpp"),
            Object(NonMatching, ".unsorted/802880D4.cpp"),
            Object(NonMatching, ".unsorted/8028CB24.cpp"),
            Object(NonMatching, ".unsorted/802973F8.cpp"),
            Object(NonMatching, ".unsorted/80297890.cpp"),
            Object(NonMatching, ".unsorted/802A2904.cpp"),
            Object(NonMatching, ".unsorted/802A4660.cpp"),
            Object(NonMatching, ".unsorted/802AD0D4.cpp"),
            Object(NonMatching, ".unsorted/802B2D18.cpp"),
            Object(NonMatching, ".unsorted/802B3C20.cpp"),
            Object(NonMatching, ".unsorted/802E82F4.cpp"),
            Object(NonMatching, ".unsorted/803D9EB4.cpp"),
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
    ProgressCategory("runtime", "MetroWerks Runtime"),
    ProgressCategory("sdk", "RVL SDK"),
    ProgressCategory("unsorted", "Unsorted"),
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
