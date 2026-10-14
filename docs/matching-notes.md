# Matching notes

Compiler behaviour already worked out on this project. Add to it when a unit teaches something new; remove an entry that turns out wrong.

## Flags

- Code ported from the DS games (`src/ds/` and a few `.unsorted` units) is built with `-O4,s -inline noauto`. Set it per unit with `extra_cflags` in `configure.py`, not with `#pragma` blocks.
- When one function inside such a unit needs different inlining, a per-function `NO_INLINE` (`include/decomp.h`) is preferred to a `#pragma dont_inline` region.

## Code generation

- mwcc emits functions in source order, even with `-ipa file`. Check function offsets in the object against `symbols.txt`, not only sizes.
- The order of local declarations drives register and stack slot allocation.
- Float constants must be written as literals in the source, not declared `extern`.
- Signedness and width change the instructions (`divw` vs `divwu`, `extsh`).

## Data and linking

- `-str` pools identical strings. Removing a function, or making a stripped one `static`, shifts the order of strings in `.data` and breaks the data match of the whole unit.
- Functions of an imported library that the linker stripped from the DOL stay in the source. Don't force them active.
- File statics need `scope:local` in `symbols.txt`; several units each have a local `version` object from `common.hpp`.

## Checking a NonMatching unit

- The DOL hash says nothing about a NonMatching unit. Compare its functions against `symbols.txt` over the unit's range in `splits.txt`: name, size, offset and binding (global or local).
- List the undefined symbols of the object. An upper-case name usually means a macro that is missing and was compiled as a call; an old name means a caller was not updated after a rename.
- After a refactor that should not change code, compare the objects function by function (normalised `objdump`) before and after.
