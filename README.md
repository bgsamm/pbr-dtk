# Pokémon Battle Revolution — decompilation

A matching decompilation of **Pokémon Battle Revolution** (Wii, PAL release `RPBP01`, Rev 0), with a native PC port and online battles between friends as long-term goals.

The build produces a `main.dol` that is byte-for-byte identical to the original (SHA-1 `ffcd539d239722b8bb27e45c9ad4aacc818c8933`). Every function is compared against the original binary with [objdiff](https://github.com/encounter/objdiff).

This repository contains **no game data and no assembly**. You need your own copy of the game.

This work builds on [bgsamm/pbr-dtk](https://github.com/bgsamm/pbr-dtk) (CC0), which set up the project and decompiled most of the `gs` engine so far. Parts of the Revolution SDK come from [koopthekoopa/wii-ipl](https://github.com/koopthekoopa/wii-ipl) (CC0); each imported file names its source.

## Status

| | |
|---|---|
| Code matched | **10.9 %** (5,005 of 13,890 functions) |

Progress by area (functions matching at 100 % in objdiff):

| Area | Matched code |
|---|---|
| Pokémon data (species, items, strings) | 75 % |
| Game entry point | 34 % |
| Game networking (Wi-Fi state machine) | 28 % |
| Battle presentation | 21 % |
| Battle engine (ported from the DS games) | 20 % |
| `gs` engine | 18 % |
| Battle loop and camera | 17 % |
| Revolution SDK | 7 % |
| Scenes and menus | 5 % |

Many of these functions are still written with placeholder names and types. A unit counts as finished only when it meets [docs/STYLE.md](docs/STYLE.md).
See [docs/architecture.md](docs/architecture.md) for a map of the executable and [docs/PROGRESS.md](docs/PROGRESS.md) for the log.

## Building

Requirements:

- Python 3 and [ninja](https://ninja-build.org/).
- Linux and macOS use [wibo](https://github.com/decompals/wibo) to run the Metrowerks compiler; it is downloaded automatically. On Apple Silicon, wibo needs Rosetta 2 (`softwareupdate --install-rosetta`).
- Windows runs the compiler natively.

Steps:

1. Put your disc image (ISO, RVZ, WBFS, CISO, GCZ…) in `orig/RPBP01/`. It can be deleted after the first build.
2. Configure and build:

   ```sh
   python configure.py
   ninja
   ```

3. To compare functions, open the project directory in [objdiff](https://github.com/encounter/objdiff) once `objdiff.json` exists.

## Layout

| Path | Contents |
|---|---|
| `src/gs/` | Genius Sonority engine (memory, files, `.fsys` archives, scenes, rendering, input) |
| `src/ds/` | Glue for the code ported from the Gen 4 DS games |
| `src/.unsorted/` | Units whose role is not identified yet |
| `libs/RVL_SDK/` | Revolution SDK |
| `config/RPBP01/` | `splits.txt` and `symbols.txt` for decomp-toolkit |
| `tools/stubgen/` | Generators for trivial placeholder functions |
| `ghidra_scripts/` | Imports `symbols.txt` into a Ghidra project |

## License

CC0, like the projects it builds on.
