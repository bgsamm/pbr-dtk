# Map of the game (RPBP01)

A map of `main.dol` and of the game's data files.

## main.dol

| # | Area | Addresses | Functions | Size | Depends on |
|---|---|---|---|---|---|
| 1 | Startup (`.init`, `__start`, ROM copy) | 80004000–80006BC4 | 18 | 2 KiB | — |
| 2 | `main`, main loop, HOME menu integration | 80006BC4–80010000 | 235 | 37 KiB | gs, HBM, sound |
| 3 | **Battle presentation**: turn flow, announcer ("Jikkyo"), messages, status display, battle models and effect sequences (`eftseq`, `script/esq`) | 80010000–80058000 | 1,177 | 288 KiB | 18, gs (scene, render), sound |
| 4 | **Scenes, menus, UI** (many classes with vtables, few strings; loads arena archives `*_tr_*.fsys`) | 80058000–80158000 | 1,310 | 1,024 KiB | gs, sound, 5 |
| 5 | Save data (`/GeniusPbr`, `PbrSaveData`, `banner.bin`), Battle Pass (`PbrPassData`), DS transfer (`wifi/child0.srl`), "pseudo:" files exchanged during online battles | 80158000–80169000 | 502 | 68 KiB | NAND, 12, 15 |
| 6 | Battle init and main loop (`battleInit`, `battleMain`, `fightcommon`, `battleCamera`, `be_seq_rev.narc`) and remaining game code (to be confirmed) | 80169000–801C6C48 | 1,827 | 375 KiB | 3, 18, gs |
| 7 | Metrowerks runtime and MSL C (`memcpy`, `printf`, math) | 801C6C48–801D4838 | 143 | 55 KiB | — |
| 8 | MetroTRK (hardware debugger) | 801D4838–801DA014 | 150 | 22 KiB | EXI |
| 9 | `DB` debugger, EXI2 | 801DA014–801DAA30 | 12 | 3 KiB | — |
| 10 | **gs engine** (`src/gs/`): memory, cache, files, NAND, scenes, objects, animation, math, tasks, threads, timeline, script (`GSscript`), GX rendering, textures, video, input, `.fsys` | 801DAA30–80250000 | 1,592 | 470 KiB | RVL SDK, MSL |
| 11 | Game sound (`GSsound.cpp`) and NW4R glue (3D listener) | 80250000–8025B6AC | 250 | 46 KiB | 16, AX |
| 12 | Game networking: sockets, `PBRC` stats client (ghttp), packet allocator, DS link (`WIFIMP`, `WIFIMPDL`), network state machine, `pokebattlewii` matchmaking | 8025B6AC–80268228 | 472 | 51 KiB | 15, SO, MP |
| 13 | RVL SDK: OS, PPC, GX, DVD, VI, MTX, MEM, PAD, KPAD, WPAD, Bluetooth stack (WUD/BTA/BTM/L2CAP/RFCOMM), IPC/IOS, NAND, SC, ARC, NCD, WD, MPDL, SO, NHTTP, SSL, NWC24, AI/AX/DSP | 80268228–80304E94 | 2,473 | 627 KiB | — |
| 14 | VF: Prfile2 FAT file system (`libs/RVL_SDK/src/vf/`) | 80304E94–8031C124 | 305 | 93 KiB | MSL |
| 15 | DWC (Nintendo Wi-Fi Connection) and GameSpy (GP, SB, QR2, NatNeg, ghttp) | 8031C124–80362000 | 824 | 280 KiB | SO, SSL, NHTTP |
| 16 | NW4R: `db` (panic/trace), `snd` (plays `pbr_sound.brsar`), probably `ut`, `math`, `lyt` (to be confirmed) | 80362000–8038F424 | 952 | 181 KiB | AX, DVD |
| 17 | HBM (HOME menu: `homeBtn.arc`, `.brlyt`/`.brlan` layouts; string `RVL_SDK - HBM`) | 8039A068–803A60D8 | 142 | 48 KiB | 16 (lyt), WPAD |
| 18 | **Battle engine** inherited from the Gen 4 DS games: battler I/O commands, battle system state and messages, server command queue (`ServerQueSet`), turn controller, damage calculation, move effects, battle script interpreter (see below) | 803A60D8–803D9208 | 757 | 204 KiB | 19, MSL |
| 19 | Pokémon data: parameters, growth, items, moves, Arceus type, `STRBUF` strings, checksums; record readers for the game's data files (8038F424–8039A068, called by `ItemTable_Load` and `SpeciesData_LoadSpecies`) | 8038F424–8039A068, 803D9208–803E3000 | 749 | 78 KiB | MSL |

### Battle engine units

Area 18 descends from the Diamond and Pearl battle code. Its units are named after their counterparts in [pret/pokeplatinum](https://github.com/pret/pokeplatinum), the furthest along of the Gen 4 decompilations, whose structure gives the unit boundaries:

| Unit | Addresses | Functions | pokeplatinum counterpart | Evidence |
|---|---|---|---|---|
| `ds/battle/battle_io_command.cpp` | 803A60D8–803A7418 | 70 | `battle_io_command.c` | 803A60D8 allocates the 0x194-byte battler data; 803A6138 dispatches through a table of 67 battler commands (0x80405048), in the same order as in pokeplatinum. |
| `ds/battle/battle_display.cpp` | 803A7418–803AB534 | 100 | `battle_display.c` | 803A7418 onwards are the display tasks the command handlers start; it ends with the battler data getters (`BattlerData_GetBattlerType` at 803AB514), as in pokeplatinum. |
| `ds/battle/battle_main.cpp` | 803AB534–803AC820 | 3 | part of `battle_main.c` | 803AB534 creates the battle (eight battler data, party order, context setup) and 803AC5F0 frees it. |
| `ds/battle/battle_system.cpp` | 803AC820–803AF444 | 60 | `battle_system.c` | Battle system getters from 803AC820 (`BattleSystem_GetBattleType` at 803AC840); message formatting with two 61-case switches. |
| `ds/battle/battle_controller.cpp` | 803AF444–803B2AF8 | 79 | `battle_controller.c` | 803AF444 receives server messages (dequeues the I/O queue); 803AF5F0 sends them and has 73 callers, the emit functions. |
| `ds/battle/battle_controller_player.cpp` | 803B2AF8–803BA360 | 59 | `battle_controller_player.c` | 803B2AF8 allocates the battle context; 803B2C3C runs a table of 44 control states (45 in pokeplatinum). |
| `ds/battle/battle_lib.cpp` | 803BA360–803C94CC | 140 | `battle_lib.c` | Starts with battler initialisation (803BA360) and the script stack; I/O queue with the `ServerQueSet` assertions at 803BAABC–803BABF0; a 112-entry table of three-byte records at 0x80405248, read by the type effectiveness code (the type chart in pokeplatinum). Ends with functions only PBR has (803C90D0–803C94CC), called by the game code. |
| `ds/battle/battle_script.cpp` | 803C94CC–803D9208 | 246 | `battle_script.c` | 803C94CC dispatches through the 222-entry command table at 0x804056D8; the unit's static initializer is the last function. |

Unlike pokeplatinum, area 18 has no trainer AI (trainer_ai.c and its AI script commands), and the battle controller never waits for an AI decision. The opponent’s choices are made elsewhere, presumably in the game code.

## Game data

The disc's `files/` directory holds 8 directories and 1,106 files. Almost all files are `.fsys` archives, indexed by `GSfsys.toc` and read by the code in `src/gs/fsys/`; each archive usually holds several files.
In the table, `pkx_###` and `wzx_waza_###` are grouped, as are language versions (`_e`, `_f`, `_g`, `_i`, `_s`: English, French, German, Italian, Spanish; some sets add the letter without `_`, and `strap` has a sixth version, `d`). `menu_fight_s.fsys` has no other versions, so its `_s` may mean something else. Directory contents are not listed yet.

| File | Size | Contents |
|---|---|---|
| `arcDat/` | — | Data for the DS battle engine, apparently taken directly from the DS games |
| `font/` | — | Fonts |
| `hb/` | — | HOME menu |
| `menu/` | — |  |
| `message/` | — |  |
| `msgDat/` | — |  |
| `sound/` | — | Sound (`pbr_sound.brsar`, NW4R format) |
| `wifi/` | — | DS transfer (`child0.srl`) |
| `b1_tr_00.fsys` | 520 KiB | Trainer models |
| `b2_tr_00.fsys` | 626 KiB | Trainer models |
| `b3_tr_00.fsys` | 560 KiB | Trainer models |
| `b4_tr_00.fsys` | 586 KiB | Trainer models |
| `bf_00.fsys` | 1011 KiB | Battlefield (stadium) models |
| `bf_01.fsys` | 1.3 MiB | Battlefield (stadium) models |
| `bf_02.fsys` | 1.7 MiB | Battlefield (stadium) models |
| `bf_03.fsys` | 1.2 MiB | Battlefield (stadium) models |
| `bf_04.fsys` | 1.3 MiB | Battlefield (stadium) models |
| `bf_05.fsys` | 1.2 MiB | Battlefield (stadium) models |
| `bf_06.fsys` | 1.3 MiB | Battlefield (stadium) models |
| `bf_07.fsys` | 1.2 MiB | Battlefield (stadium) models |
| `bf_08.fsys` | 1.6 MiB | Battlefield (stadium) models |
| `bf_09.fsys` | 1.0 MiB | Battlefield (stadium) models |
| `bf_10.fsys` | 1.5 MiB | Battlefield (stadium) models |
| `common.fsys` | 431 KiB | Game data tables (Pokémon stats, level-up movesets…) and some Poké Ball icon textures |
| `db_tr_00.fsys` | 532 KiB | Trainer models |
| `db_tr_10.fsys` | 236 KiB | Trainer models |
| `deck.fsys` | 130 KiB | AI trainers and their Pokémon |
| `dg_tr_00.fsys` | 526 KiB | Trainer models |
| `dg_tr_10.fsys` | 289 KiB | Trainer models |
| `ending.fsys` | 1.5 MiB | Ending |
| `ending_movie.fsys` | 129.7 MiB | Ending movie |
| `fc_tr_00.fsys` | 2.7 MiB | Trainer models |
| `fc_tr_10.fsys` | 1.6 MiB | Trainer models |
| `fight_common.fsys` | 1.6 MiB |  |
| `fm_tr_00.fsys` | 2.6 MiB | Trainer models |
| `fm_tr_10.fsys` | 1.4 MiB | Trainer models |
| `fn_tr_00.fsys` | 2.9 MiB | Trainer models |
| `fn_tr_10.fsys` | 1.5 MiB | Trainer models |
| `GSfsys.toc` | 29 KiB | Index of the `.fsys` archives |
| `mc_tr_00.fsys` | 2.3 MiB | Trainer models |
| `mc_tr_10.fsys` | 1.2 MiB | Trainer models |
| `menu_bg.fsys` | 459 KiB | Menu layouts: backgrounds |
| `menu_bpass.fsys` | 661 KiB | Menu layouts: Battle Pass |
| `menu_bpass2.fsys` | 1.6 MiB | Menu layouts: Battle Pass |
| `menu_btutorial.fsys` | 38 KiB | Menu layouts: battle tutorial |
| `menu_btutorial_{f,g,i,s}.fsys` | 163 KiB | Menu layouts: battle tutorial |
| `menu_colo1.fsys` | 450 KiB | Menu layouts: Colosseum |
| `menu_colo2.fsys` | 1.3 MiB | Menu layouts: Colosseum |
| `menu_colosseum.fsys` | 375 KiB | Menu layouts: Colosseum |
| `menu_colosseum2.fsys` | 1.7 MiB | Menu layouts: Colosseum |
| `menu_colosseum3.fsys` | 110 KiB | Menu layouts: Colosseum |
| `menu_colosseum3_{f,g,i,s}.fsys` | 431 KiB | Menu layouts: Colosseum |
| `menu_common.fsys` | 111 KiB | Menu layouts: shared |
| `menu_comvs.fsys` | 129 KiB | Menu layouts |
| `menu_ds.fsys` | 800 KiB | Menu layouts: DS link |
| `menu_ds2.fsys` | 9 KiB | Menu layouts: DS link |
| `menu_face.fsys` | 2.5 MiB | Menu layouts |
| `menu_fbattle.fsys` | 28 KiB | Menu layouts |
| `menu_fbttle2.fsys` | 206 KiB | Menu layouts |
| `menu_fight.fsys` | 181 KiB | Menu layouts: battle |
| `menu_fight2.fsys` | 681 KiB | Menu layouts: battle |
| `menu_fight_s.fsys` | 32 KiB | Menu layouts: battle |
| `menu_g_fight_{e,f,g,i,s}.fsys` | 74 KiB | Menu layouts: battle |
| `menu_ls.fsys` | 144 KiB | Menu layouts |
| `menu_name.fsys` | 667 KiB | Menu layouts: naming |
| `menu_name2.fsys` | 19 KiB | Menu layouts: naming |
| `menu_opening.fsys` | 258 KiB | Menu layouts: opening |
| `menu_option.fsys` | 250 KiB | Menu layouts: options |
| `menu_pokemon.fsys` | 2.1 MiB | Menu layouts: Pokémon |
| `menu_root.fsys` | 280 KiB | Menu layouts |
| `menu_root2.fsys` | 53 KiB | Menu layouts |
| `menu_root2{e,f,g,i,s}.fsys` | 41 KiB | Menu layouts |
| `menu_roulette_{e,f,g,i,s}.fsys` | 32 KiB | Menu layouts: roulette |
| `menu_rule.fsys` | 204 KiB | Menu layouts: rules |
| `menu_shop.fsys` | 342 KiB | Menu layouts: shop |
| `menu_status.fsys` | 219 KiB | Menu layouts: status |
| `menu_status2.fsys` | 4 KiB | Menu layouts: status |
| `menu_storage.fsys` | 584 KiB | Menu layouts: storage |
| `menu_wifi.fsys` | 758 KiB | Menu layouts: Wi-Fi |
| `menu_wifi2.fsys` | 10 KiB | Menu layouts: Wi-Fi |
| `mes_bpass_{e,f,g,i,s}.fsys` | 635 KiB | String tables: Battle Pass |
| `mes_common.fsys` | 460 KiB | String tables: shared |
| `mes_common_{f,g,i,s}.fsys` | 1.8 MiB | String tables: shared |
| `mes_fight_{e,f,g,i,s}.fsys` | 623 KiB | String tables: battle |
| `mes_name_{e,f,g,i,s}.fsys` | 12 KiB | String tables: names |
| `mng_common{e,f,g,i,s}.fsys` | 82 KiB |  |
| `mn_tr_00.fsys` | 2.4 MiB | Trainer models |
| `mn_tr_10.fsys` | 1.3 MiB | Trainer models |
| `mt_tr_00.fsys` | 2.8 MiB | Trainer models |
| `mt_tr_10.fsys` | 1.5 MiB | Trainer models |
| `opening.bnr` | 177 KiB | Banner shown in the Wii menu |
| `opening_movie.fsys` | 106.6 MiB | Opening movie |
| `pkx_###.fsys` (495 files, `pkx_001`–`pkx_601`) | 367.6 MiB | Pokémon models |
| `rr_00.fsys` | 1.1 MiB |  |
| `strap{d,e,f,g,i,s}.fsys` | 1.0 MiB | Wii Remote strap reminder |
| `title.fsys` | 513 KiB | Title screen |
| `title_bg_{e,f,g,i,s}.fsys` | 4.2 MiB | Title screen |
| `tr_badge.fsys` | 77 KiB |  |
| `tr_dpboy_10.fsys` | 209 KiB | Trainer models |
| `tr_dpgirl_10.fsys` | 240 KiB | Trainer models |
| `wm_00.fsys` | 1.4 MiB |  |
| `wzx_bthr.fsys` | 2.9 MiB |  |
| `wzx_btlintro.fsys` | 357 KiB |  |
| `wzx_extend.fsys` | 5.7 MiB |  |
| `wzx_turnend.fsys` | 576 KiB |  |
| `wzx_turnstart.fsys` | 4 KiB |  |
| `wzx_waza_###.fsys` (467 files, `001`–`467`) | 70.1 MiB | Move effects, one archive per move (*waza*: move) |
| `zzzzzzzz.zzz` | 32 KiB | Disc padding |

## Method and confidence

- Functions, sizes and names: `config/RPBP01/symbols.txt` (13,890 functions, 3.86 MiB of code).
- Identification of unnamed areas: strings referenced by the code (through Ghidra) and the call graph.
- Boundaries of areas without any known name are **approximate** (to within a few functions). Areas marked "to be confirmed" are inferences.
  The README progress table uses its own boundaries from `tools/progress.py`, kept in step with this map.
- Libraries identified from their version banners: `RVL_SDK` (OS, GX, DVD, VI, AI, AX, DSP, EXI, SI, KPAD, WPAD, NAND, SC, MP, MPDL, NCD, SO, NWC24, THP, HBM, DWC, DWCDL), `NW4R - SND`, `REX-PPC 1.0.0.1 (RevoEX-1.0plus1)`, MetroTRK. The OS library is dated April 2007, DWC March 2007.
