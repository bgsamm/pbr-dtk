# Open issues

Known gaps that are not obvious from `configure.py` or the objdiff report: functions left unwritten on purpose, imported code that differs from the binary, and project-wide blockers.

## Keeping this list current

- A PR that leaves a known gap in a unit adds an entry here. A PR that closes one removes it. The PR's description says which.
- One entry per unit or library, under its area. Name the functions or addresses concerned and why they are not done.
- Don't list ordinary unfinished work: a NonMatching unit with no special cause belongs only in `configure.py`.
- Remove an entry when it no longer holds. Don't mark it done.

## SDK

- `dvd.c`: `DVDCheckDiskAsync` is not written yet.
- `NANDCore`: `NANDGetType` and `nandIsRelativePath` are in the imported source but not in the binary. `nandChangeDir`, `NANDChangeDirAsync` and `nandChangeDirCallback` and `SCFlush` are written from the binary. The two NAND check functions at 802EA66C are not written yet.
- `OSExec`: five functions after `__OSGetExecParams` are not in the imported source and stay unwritten (callback, 8026BD34, 8026C328, 8026C474, `__OSBootDol`). `OSFatal` needs more header work (VI, EXI, render mode names) and is not imported yet.
- `vf`: `nand_drv` has one function in the binary (the original uses a different NAND driver); a few functions of `d_common`, `d_vf`, `d_vf_sys`, `pf_volume` and `pf_driver` are not in the binary.
- `ai`/`ax`: four functions of `AXVPB` that are not in ogws are not written yet.
- Fourteen of the 16 wii-ipl SDK files (OSCache, db, OS, OSNet, OSStateTM, OSPlayRecord, dvdfs, nand, OSNandbootInfo, OSStateFlags, __ppc_eabi_init, i2c, WPAD, vi3in1) have code identical to the original, but stay `NonMatching` until the data sections are split. Left to do: `VIConfigure` in vi (register allocation) and OSAudioSystem, which needs the DSP boot code from game data.

## Runtime, C library and MetroTRK

- The C library units split from the old `801C7830` unit have identical code but no data splits yet. The code gaps left between them (`qsort`, `rand`, `atof`, the area around `fseek`) have no source yet, and the assembly parts of MetroTRK (`targsupp.s`, a few stubs) and the debugger library after `801D9F70` are not split.

## Project-wide

- Jump tables and data remain in automatic splits, so functions with a `switch` can show 99.8 % instead of 100 % until the data sections are split; units cannot be marked `Matching` before that.
- Most matched functions outside `src/gs/` and `src/ds/DSbridge.cpp` still use placeholder names and types (`fn_`, offset access): they are scaffolding, to be rewritten unit by unit following [STYLE.md](STYLE.md).
