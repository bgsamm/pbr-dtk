# Code style

These rules apply to all code in the repository. Some existing code, including parts of `src/gs/`, predates them and is being brought in line.
Format with the repository's [.clang-format](.clang-format), using clang-format 23.

## Files

- One translation unit per original source file, placed by module: `src/gs/...`, `src/ds/...`, etc. `src/.unsorted/<address>.cpp` is only a holding area for units whose role is still unknown.
- One header per module in `include/`, mirroring `src/`. Structures and declarations used by more than one unit live in a header, never copied between files.
- Functions appear in the file in address order, as in the original object.
- Source files are Shift-JIS, the encoding the compiler reads. Keep to ASCII except for Japanese text in string literals.

## Naming

- Functions: real name when the evidence supports it (strings, symbol maps, the DS code it is ported from, behaviour).
  When the purpose is not established yet, keep the address name (`fn_803D9778`) with a one-line `// TODO` at the definition site saying what is known. Never invent a confident name.
- Types: `PascalCase` (`ItemData`). gs engine types are `GS` followed by `camelCase` (`GSfsys`, `GSfsysEntry`).
  Members: `mName` for classes and engine structures, plain `camelCase` for data records ported from the DS code (`price`, `holdEffect`).
  A type whose role is not established is named `Unk` plus the address of the function or object it was found from (`Unk80035CB0`).
- Globals `gName`, file statics `sName`, constants and enum values `UPPER_CASE`.

## Declarations

- Declare a function in the header of the unit that defines it, even when that unit is not yet decompiled. Never declare the same function in several places (e.g. using `extern`).
- Data from a unit whose data sections are not yet split may be declared `extern` in the file that uses it, until its home is known.
- A static or global variable whose address is known gets the address in a comment where it is defined: `/* 0x8063F2E8 */ static GScacheEntry *sFileCacheList;`.
  Addresses are those of RPBP01, the version this project builds. Float and string literals are written directly in the source and get no address.

## Structures and classes

- Every structure and class has its size (`// size: 0x10`) and a `/* 0xNN */` offset comment on each member.
  When the true size is not known yet, give the smallest size the code proves: `// size: >= 0x14`.
- A class with virtual methods also gives the offset of its vtable pointer (`// vtable: 0xC`), and each virtual method has its offset in the vtable.
- Unknown regions are `u8 _unkNN[size]`; unknown fields are named `_NN` after their offset.

```cpp
// size: >= 0x14
struct GStocHeader {
    /* 0x00 */ char mMagic[4]; // "GLLA"
    /* 0x04 */ u8 _unk4[0x4];
    /* 0x08 */ u32 mCount;
    /* 0x0C */ u8 _unkC[0x4];
    /* 0x10 */ u32 mTableOffset;
};

// size: 0x10
class GSrenderModule {
protected:
    /* 0x0 */ const char *mName;
    /* 0x4 */ u8 mId;
    /* 0x8 */ GSrenderModule *mNext;

    static GSrenderModule *sHead;
    static GSrenderModule *sTail;

public:
    GSrenderModule(const char *name);

    // vtable: 0xC
    /* 0x8 */ virtual void update(f32 deltaTime);
    /* 0xC */ virtual void fn_80236AE0();
};
```

## What does not belong in finished code

- `extern "C"` blocks around game code, used to link against unmangled placeholder symbols. Work out the signature and give the symbol its mangled name in [symbols.txt](config/RPBP01/symbols.txt) instead.
- Comments that restate the code, banners, or comments about how the code was produced.
- Anything listed in [docs/fakematches.md](docs/fakematches.md) without the justification that file asks for.
