## Repo map

- `src/`: Game code.
- `src/.unsorted/<addr>.cpp`: TUs not yet identified, named after their start address.
- `include/`: Headers for `src/`, same layout (`include/gs/GSnand.hpp`
  ↔ `src/gs/GSnand.cpp`). 
- `include/common.hpp`: Project-wide helpers and macros.
- `libs/`: RVL SDK, MSL and the MetroWerks Runtime.
- `configure.py`: Compilation settings, plus the unit list with `Matching`/`NonMatching` flags.
  Generates `build.ninja`.
- `config/<version>/splits.txt`: Contains split information (i.e. each TU's sections).
- `config/<version>/symbols.txt`: Contains symbol information.
- `build/`: Files generated automatically by the build process.
- `build/<version>/asm/<split>.s`: Target assembly for a given split (e.g.
  `build/RPBP01/asm/src/gs/GSnand.s`).
- `scripts/`: Custom analysis tooling (writes output to `analysis/`).
- `orig/`: The retail game files (`main.dol`).
- `tools/decomp/`: Scripts for aiding and validating decompilation.
