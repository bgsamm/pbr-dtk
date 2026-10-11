# Map of `main.dol` (RPBP01)

A map of the executable's modules, used to pick what to decompile next and to prepare the PC port and online play.

## Method and confidence

- Functions, sizes and names: `config/RPBP01/symbols.txt` (13,890 functions, 3.86 MiB of code).
- Identification of unnamed areas: strings referenced by the code (through Ghidra) and the call graph.
- Boundaries of areas without any known name are **approximate** (to within a few functions). Areas marked "to be confirmed" are inferences.
  `splits.txt` makes 0x8038F424–0x803D9208 a single unit of DS-derived code (item data file readers, then the battle engine), so the ends of areas 16 and 17 below overlap it and are to be redone.
- Libraries identified from their version banners: `RVL_SDK` (OS, GX, DVD, VI, AI, AX, DSP, EXI, SI, KPAD, WPAD, NAND, SC, MP, MPDL, NCD, SO, NWC24, THP, HBM, DWC, DWCDL), `NW4R - SND`, `REX-PPC 1.0.0.1 (RevoEX-1.0plus1)`, MetroTRK. The OS library is dated April 2007, DWC March 2007.

## Overview

Genius Sonority game code: about **1.8 MiB** at the start of the binary, plus the `gs` engine and the battle engine at the end.
Nintendo and Metrowerks libraries: about **1.5 MiB**, a large part of which a PC port does not need (Bluetooth, NAND, debugger, Nintendo Wi-Fi Connection).

## Map

| # | Area | Addresses | Functions | Size | Depends on | Priority |
|---|---|---|---|---|---|---|
| 1 | Startup (`.init`, `__start`, ROM copy) | 80004000–80006BC4 | 18 | 2 KiB | — | Low |
| 2 | `main`, main loop, HOME menu integration | 80006BC4–80010000 | 235 | 37 KiB | gs, HBM, sound | Medium |
| 3 | **Battle presentation**: turn flow, announcer ("Jikkyo"), messages, status display, battle models and effect sequences (`eftseq`, `script/esq`) | 80010000–80058000 | 1,177 | 288 KiB | 18, gs (scene, render), sound | **High** |
| 4 | **Scenes, menus, UI** (many classes with vtables, few strings; loads arena archives `*_tr_*.fsys`) | 80058000–80158000 | 1,310 | 1,024 KiB | gs, sound, 5 | Medium |
| 5 | Save data (`/GeniusPbr`, `PbrSaveData`, `banner.bin`), Battle Pass (`PbrPassData`), DS transfer (`wifi/child0.srl`), "pseudo:" files exchanged during online battles | 80158000–80169000 | 502 | 68 KiB | NAND, 12, 15 | **High** (network protocol) |
| 6 | Battle init and main loop (`battleInit`, `battleMain`, `fightcommon`, `battleCamera`, `be_seq_rev.narc`) and remaining game code (to be confirmed) | 80169000–801C6C48 | 1,827 | 375 KiB | 3, 18, gs | **High** |
| 7 | Metrowerks runtime and MSL C (`memcpy`, `printf`, math) | 801C6C48–801D4838 | 143 | 55 KiB | — | High (reusable) |
| 8 | MetroTRK (hardware debugger) | 801D4838–801DA014 | 150 | 22 KiB | EXI | Very low (dropped in a port) |
| 9 | `DB` debugger, EXI2 | 801DA014–801DAA30 | 12 | 3 KiB | — | Very low |
| 10 | **gs engine** (`src/gs/`): memory, cache, files, NAND, scenes, objects, animation, math, tasks, threads, timeline, script (`GSscript`), GX rendering, textures, video, input, `.fsys` | 801DAA30–80250000 | 1,592 | 470 KiB | RVL SDK, MSL | **High** (foundation) |
| 11 | Game sound (`GSsound.cpp`) and NW4R glue (3D listener) | 80250000–8025B6AC | 250 | 46 KiB | 16, AX | Medium |
| 12 | Game networking: sockets, `PBRC` stats client (ghttp), packet allocator, DS link (`WIFIMP`, `WIFIMPDL`), network state machine, `pokebattlewii` matchmaking | 8025B6AC–80268228 | 472 | 51 KiB | 15, SO, MP | **High** for online play (to be replaced) |
| 13 | RVL SDK: OS, PPC, GX, DVD, VI, MTX, MEM, PAD, KPAD, WPAD, Bluetooth stack (WUD/BTA/BTM/L2CAP/RFCOMM), IPC/IOS, NAND, SC, ARC, NCD, WD, MPDL, SO, NHTTP, SSL, NWC24, AI/AX/DSP | 80268228–80304DC4 | 2,472 | 627 KiB | — | High for OS/GX/MTX (reusable), low for the rest |
| 14 | Unidentified standalone library (only calls MSL; string `NO NAME`: likely the VF FAT file system) | 80304DC4–80318000 | 222 | 77 KiB | MSL | Low |
| 15 | DWC (Nintendo Wi-Fi Connection) and GameSpy (GP, SB, QR2, NatNeg, ghttp) | 80318000–80362000 | 908 | 296 KiB | SO, SSL, NHTTP | Low: **to be replaced**, not decompiled (service closed in 2014) |
| 16 | NW4R: `db` (panic/trace), `snd` (plays `pbr_sound.brsar`), probably `ut`, `math`, `lyt` (to be confirmed) | 80362000–80398000 | 1,364 | 216 KiB | AX, DVD | Medium (reusable) |
| 17 | HBM (HOME menu: `homeBtn.arc`, `.brlyt`/`.brlan` layouts) | 80398000–803A3000 | 136 | 44 KiB | 16 (lyt), WPAD | Very low (dropped in a port) |
| 18 | **Battle engine, pure logic**: battle server command queue (`ServerQueSet`), damage calculation, move effects, inherited from the Gen 4 DS games | 803A3000–803D9208 | 856 | 216 KiB | 19, MSL | **Very high** (core of the game and of netplay) |
| 19 | Pokémon data: parameters, growth, items, moves, Arceus type, `STRBUF` strings, checksums | 803D9208–803E3000 | 244 | 35 KiB | MSL | **Very high** |

## Game data

- `files/`: 1,114 files, almost all **`.fsys`** archives of the gs engine (`common.fsys`, `fight_common.fsys`, `menu_*.fsys`, arenas `*_tr_00/10.fsys`, `bf_*.fsys`…), indexed by `GSfsys.toc`.
  The format is handled by the matched code in `src/gs/fsys/`, a good base for a PC reader.
- Sound: `sound/pbr_sound.brsar` (NW4R format). HOME menu: `hb/`. Fonts: `font/`.

## What this means

1. **Battles are split in two.** Pure logic (area 18, with the data in area 19) and presentation (areas 3 and 6).
   The pure logic depends on little more than MSL, is small (about 250 KiB), deterministic, and descends from the Gen 4 DS games.
   It is the best target for lockstep netplay and can be built as a library testable on PC before the rest.
2. **The online protocol is already there.** During Wi-Fi battles the consoles exchange "pseudo:" files (area 5: `fight/command`, `fight/turn_pokeparty.lz`, `fight/result`, `battle/battlepass`…).
   Understanding them gives the message format for a replacement server.
3. **Libraries to reuse rather than decompile**: MSL, runtime, RVL SDK (OS, GX, MTX, DVD) and NW4R exist, matched, in other decomp-toolkit projects of the same era (exact versions to check).
4. **To skip or replace in a port**: MetroTRK, DB, Bluetooth, HOME menu, NWC24, MPDL, DWC and GameSpy (about 600 KiB).

## Suggested order

1. Runtime, MSL and SDK OS/MTX (areas 7 and 13), importing versions already matched elsewhere.
2. Finish the gs engine (area 10).
3. Pokémon data (area 19), then the pure battle engine (area 18).
4. Online battle protocol (area 5) and game networking (area 12), to prepare online play.
5. Battle presentation (areas 3 and 6), then scenes and menus (area 4), sound (11, 16).
