# Code style and definition of done

The reference is the code already decompiled upstream in `src/gs/` and `include/gs/`.
When in doubt, do what that code does. Format with the repository's `.clang-format`.

## Files

- One translation unit per original source file, placed by module: `src/gs/...`, `src/ds/...`, game code under a descriptive directory.
  `src/.unsorted/<address>.cpp` is only a holding area for units whose role is still unknown.
- One header per module in `include/`, mirroring `src/`. Structures and declarations used by more than one unit live in a header, never copied between files.
- Functions appear in the file in address order, as in the original object.
- Source files are ASCII (the compiler reads Shift-JIS).

## Naming

- Functions: real name when the evidence supports it (strings, symbol maps, the DS code it is ported from, behaviour). Class methods use the class (`GSfsys::initFsysChunkSystem`).
  When the purpose is not established yet, keep the address name (`fn_803D9778`) with a one-line `// TODO` saying what is known. Never invent a confident name.
- Types: `PascalCase` (`ItemData`, `GSfsysEntry`). Members: `mName` for classes and engine structures, plain `camelCase` for data records ported from the DS code (`price`, `holdEffect`).
- Globals `gName`, file statics `sName`, constants and enum values `UPPER_CASE`.
- Data whose address is known gets a `/* lbl_XXXXXXXX */` comment where it is defined.
- `symbols.txt` is updated with the mangled name produced by the compiler; the address comment in the source keeps the link.

## Types and structures

- Every structure has its size (`// size: 0x22`) and a `/* 0xNN */` offset comment on each member. Unknown regions are `u8 unkN[size]`, unknown fields `_NN`.
- No raw pointer arithmetic such as `*(u32 *)(p + 0x2c)`: define the structure, even partially.
- Use the right signedness and width; they change the generated code (`divw` vs `divwu`, `extsh`).
- Bitfields, unions and enums as the data really is (see `ItemPartyParam`).
- Virtual calls go through real C++ classes with virtual methods, not through structures of function pointers.

## What does not belong in finished code

- Placeholder signatures (`u32 a0, ..., u32 a7`), dummy classes made only to reproduce a call sequence, `extern "C"` blocks around our own code.
- Comments that restate the code, banners, or comments about how the code was produced.
- Duplicate `extern` declarations of the same function with different prototypes across files: declare it once in its header.
- `extern "C"` is only for functions that are not decompiled yet, grouped under one `// TODO Replace with proper imports` block, as upstream does.

## Compiler pragmas and flags

- Prefer per-object flags in `configure.py` (`extra_cflags`) when a whole unit was built differently (for example the DS-derived code: `-O4,s -inline noauto`).
- A local `#pragma` is acceptable when only one function needs it; say why in one line.

## Definition of done for a unit

A unit is finished when:

1. Every function matches at 100 % in objdiff.
2. Its data sections are split in `splits.txt` and the object is marked `Matching` (linked), with the DOL hash unchanged.
3. It has no `fn_`/`lbl_` names left except documented unknowns, no raw offset access, no placeholder signatures.
4. It follows this guide and has been reviewed before merging.

Units that are not finished stay `NonMatching` and may contain scaffolding (for instance the generated stubs in `src/.unsorted/`), which is replaced unit by unit, never extended.

## Commits

- One subject line saying what was decompiled or changed (`ds: decompile item data and NARC helpers`), a short body if useful.
- No game data, no personal names or addresses.
