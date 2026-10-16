Pokémon Battle Revolution 
[![Build Status]][actions] [![Progress]][progress site] [![Discord Badge]][discord]
=============

[Build Status]: https://github.com/pbr-ret/pbr-decomp/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/pbr-ret/pbr-decomp/actions/workflows/build.yml
<!--
decomp.dev progress badges
See https://decomp.dev/api for an API overview.
-->
[Progress]: https://decomp.dev/pbr-ret/pbr-decomp.svg?mode=shield&label=Progress
[progress site]: https://decomp.dev/pbr-ret/pbr-decomp
[Discord Badge]: https://img.shields.io/discord/727908905392275526?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.gg/hKx3FJJgrV

A work-in-progress matching decompilation of **Pokémon Battle Revolution** for the Wii. It currently targets the PAL release (`RPBP01`, revision 0).

This repository contains no game assets or assembly. You need your own copy of the game to build it.

> [!NOTE]
> Some contributions are made with the help of AI. However, this project still strives to maintain a high standard of quality through the use of fakematch linting and human PR reviews.

## Progress

[![Overview](https://decomp.dev/pbr-ret/pbr-decomp.svg?mode=overview)][progress site]

<!-- progress:start -->
**21.05%** of the code matches the original (6,410 of 13,890 functions). **2.32%** is in finished units linked into the build.

| Area | Size | Matched | |
|---|---:|---:|---|
| Startup | 2 KiB | 7.0 % | `█░░░░░░░░░░░░░░░░░░░` |
| Game entry point | 37 KiB | 34.7 % | `███████░░░░░░░░░░░░░` |
| Battle presentation | 288 KiB | 22.2 % | `████░░░░░░░░░░░░░░░░` |
| Scenes and menus | 1,024 KiB | 4.9 % | `█░░░░░░░░░░░░░░░░░░░` |
| Save data and Wi-Fi data | 68 KiB | 5.0 % | `█░░░░░░░░░░░░░░░░░░░` |
| Battle loop and camera | 375 KiB | 17.0 % | `███░░░░░░░░░░░░░░░░░` |
| Runtime, C library and MetroTRK | 79 KiB | 86.9 % | `█████████████████░░░` |
| gs engine | 470 KiB | 18.7 % | `████░░░░░░░░░░░░░░░░` |
| Game sound | 46 KiB | 3.4 % | `█░░░░░░░░░░░░░░░░░░░` |
| Game networking | 51 KiB | 29.4 % | `██████░░░░░░░░░░░░░░` |
| Revolution SDK | 627 KiB | 26.7 % | `█████░░░░░░░░░░░░░░░` |
| Other Nintendo libraries (VF, DWC, NW4R, HOME menu) | 602 KiB | 15.6 % | `███░░░░░░░░░░░░░░░░░` |
| Battle engine (ported from the DS games) | 204 KiB | 68.6 % | `██████████████░░░░░░` |
| Pokémon data | 78 KiB | 79.8 % | `████████████████░░░░` |

_Updated 2026-10-12 from the objdiff report of a local build._
<!-- progress:end -->

Many matched functions still use placeholder names and types. A unit is marked `Matching` only once it meets the definition of done in [CONTRIBUTING.md](CONTRIBUTING.md).

## Building

Requirements:

- Python 3 and [ninja](https://ninja-build.org/).
- On Linux and macOS, the Metrowerks compiler runs through [wibo](https://github.com/decompals/wibo), which is downloaded automatically. On Apple Silicon, wibo needs Rosetta 2 (`softwareupdate --install-rosetta`).
- On Windows, the compiler runs natively.

Steps:

1. Put your disc image (ISO, RVZ, WBFS, CISO, GCZ…) in `orig/RPBP01/`. It can be deleted after the first build.
2. Configure and build:

   ```sh
   python configure.py
   ninja
   ```

   The build checks the resulting `main.dol` against [config/RPBP01/build.sha1](config/RPBP01/build.sha1).

3. To compare functions, open the project directory in [objdiff](https://github.com/encounter/objdiff) once `objdiff.json` exists.

## Documentation

| File | Contents |
|---|---|
| [CONTRIBUTING.md](CONTRIBUTING.md) | How to contribute: scope of a change, tools, build and verify, definition of done, commits and PRs, sign-off |
| [STYLE.md](STYLE.md) | Code conventions |
| [docs/areas.md](docs/areas.md) | Currently claimed sections being worked on |
| [docs/fakematches.md](docs/fakematches.md) | What counts as a fakematch and how to justify one |
| [docs/matching-notes.md](docs/matching-notes.md) | Compiler behaviour worked out on this project |
| [docs/game-map.md](docs/game-map.md) | Map of `main.dol` by area (addresses, sizes, dependencies) and of the game's data files |

## Repository layout

| Path | Contents |
|---|---|
| `src/` | Source files for game code (i.e. excluding external libraries) |
| `src/gs/` | Genius Sonority engine (memory, files, `.fsys` archives, scenes, rendering, input) |
| `src/ds/` | Code ported from the Gen 4 DS games, including the battle engine (`src/ds/battle/`) |
| `src/.unsorted/` | Units whose role is not identified yet, named after their start address |
| `include/` | Headers, one per module, mirroring `src/` ([include/gs/GSnand.hpp](include/gs/GSnand.hpp) for [src/gs/GSnand.cpp](src/gs/GSnand.cpp)); project-wide helpers and macros in [include/common.hpp](include/common.hpp) |
| `libs/` | Revolution SDK, RevoEX, Metrowerks runtime and C library, MetroTRK |
| `config/RPBP01/` | [splits.txt](config/RPBP01/splits.txt) and [symbols.txt](config/RPBP01/symbols.txt) for [decomp-toolkit](https://github.com/encounter/decomp-toolkit) |
| `configure.py` | Compiler settings and the unit list with `Matching`/`NonMatching` flags; generates `build.ninja` |
| `orig/RPBP01/` | Your disc image (not in the repository) |
| `build/` | Build output, including the target assembly of each split in `build/RPBP01/asm/` |
| `tools/` | Build scripts and [progress.py](tools/progress.py); `tools/decomp/` has scripts for checking a unit |
| `scripts/` | Custom analysis scripts |
| `ghidra_scripts/` | Imports [symbols.txt](config/RPBP01/symbols.txt) into a Ghidra project |
| `docs/` | Documentation (see above) |

## Credits

- Parts of the Revolution SDK come from [koopthekoopa/wii-ipl](https://github.com/koopthekoopa/wii-ipl) and [doldecomp/ogws](https://github.com/doldecomp/ogws), and the C library and MetroTRK from [SMGCommunity/Petari](https://github.com/SMGCommunity/Petari), all CC0. Files imported in this repository name their source on their first line.
- Names and structures in the code ported from the DS games follow [pret/pokeplatinum](https://github.com/pret/pokeplatinum) and [pret/pokediamond](https://github.com/pret/pokediamond).
- The build system comes from [encounter/dtk-template](https://github.com/encounter/dtk-template).

## License

CC0, like the projects whose code it imports, except the Bluetooth stack headers in `libs/RVL_SDK/include/private/bte/`, which derive from bluedroid and are under the Apache License 2.0 (see `LICENSE` and `NOTICE` in that directory).
