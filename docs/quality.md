# Quality checks

`tools/qa/check.py` checks a change against its base commit. CI runs it on every pull request and every push to `main`, and it runs the same way locally.

Each check runs on both trees and fails only on problems the change adds. Problems the base already has are counted as inherited, so existing code never blocks an unrelated change, and every new problem does.

## Checks

| Check | Needs the game files | Fails on |
|---|---|---|
| `diagnostics` | no | a new compiler warning or error under the extra warning flags; in C units, a call to a function with no prototype (`-requireprotos`) |
| `symbols` | no | a compiled symbol whose scope differs from `symbols.txt`, a name missing from `symbols.txt`, a definition outside the unit's `splits.txt` range, functions out of retail order, an undefined name that neither `symbols.txt` nor any unit provides |
| `format` | no | a changed file under `src/` or `include/` that clang-format would change (the whole file is checked, not only the changed lines) |
| `lint` | no | an error from `tools/qa/lint.py` on the added lines |
| `regressions` | yes | a function that was 100% and no longer is, or a unit or the total losing matched or linked code or data (objdiff report of the base against the change) |
| `apply` | yes | a line `dtk dol apply` would change in `symbols.txt` |

With the game files, the output also lists units that are 100% but not marked `Matching`, and functions whose match dropped below their previous score. Explain those in the PR.

The warning flags are `-w missingreturn,hidevirtual,possible,unusedexpr,filecaps,sysfilecaps,tokenpasting`. `-W all` is not used: it reports every implicit integer conversion, which the original code is full of. Warning flags do not change the generated code.

The `diagnostics` and `symbols` checks compile every unit of both trees into `build/qa/` with the project's own flags. They do not touch the normal build.

## Running locally

```sh
python tools/qa/check.py                 # compiler-only checks against origin/main
python tools/qa/check.py --with-dol      # all checks; needs orig/ and a configured build
python tools/qa/check.py --show-inherited   # also list the problems the base has
python tools/qa/check.py --base none     # report everything, compare nothing
python tools/qa/check.py --only symbols,format
```

The base defaults to the merge base of `HEAD` and `origin/main`, and is checked out as a worktree in `build/qa/base`. Uncommitted changes in the working tree are included.

Requirements: Python 3.12+, the build tools (`python configure.py` then `ninja`), and the packages in `tools/qa/requirements.txt` (`pip install -r tools/qa/requirements.txt`): clang-format 23 and tree-sitter for `lint.py`. To use another clang-format 23 binary, set `CLANG_FORMAT`.

## Accepting a regression

A cleaner rewrite sometimes matches less than the code it replaces. A maintainer can accept that by adding the `accepted regression` label to the pull request. The regressions are then listed but don't fail the build. The PR description must say why each regression is necessary.

Pushes to `main` never fail on regressions: they were accepted, or not, in the pull request.

## Cleanup index

`tools/qa/cleanup_index.py` lists every place in `src/` and `include/` that keeps code from the definition of done in `docs/STYLE.md`, in three families:

- **names**: functions and data defined with an address name (`fn_`, `lbl_`), `Unk` types, `TODO` notes;
- **structure**: raw pointer arithmetic, pointers moved by a constant or cast and indexed, placeholder parameters (`a0`...), `extern "C"` linkage;
- **fakematch**: the other rules of `tools/qa/fakematch_rules.toml`.

The rules are tree-sitter queries in `tools/qa/cleanup_rules.toml`. Each site is listed with its unit's status and match score, so the work can be picked file by file.

```sh
python tools/qa/cleanup_index.py                      # summary
python tools/qa/cleanup_index.py --tsv -              # every site, as TSV
python tools/qa/cleanup_index.py --out build/pages --report build/RPBP01/report.json
```

CI builds the page on every run (artifact `cleanup_index`) and publishes it to GitHub Pages from `main`.
