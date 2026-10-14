# Contributing

Goal: plausible original C++ that byte-matches retail. Clean C++ at 90% is better than a hack at 100%.

Read before starting:

- `docs/repo-map.md`: how the repository is laid out.
- `STYLE.md`: code rules (files, naming, declarations, structures, what does not belong in finished code).
- `docs/fakematches.md`: what counts as a fakematch and how to justify one.
- `docs/matching-notes.md`: compiler behaviour already worked out on this project.

## Scope of a change

- One unit per PR (for an imported library: one library). Touch other files only for headers, types or symbol names that unit needs, and list every such change in the PR.
- Areas being worked on are listed in `docs/areas.md`. Say so in the PR if you edit a unit in someone else's area.
- `config/RPBP01/splits.txt`: adding the sections of the unit you are linking is part of the PR. Moving or removing an existing boundary, or renaming a unit, needs sign-off first (see below).
- `config/RPBP01/symbols.txt`: you may rename a symbol, fix `size:`, set `scope:` or `data:`, and split an existing data symbol inside the unit you are linking. Nothing else; `lint.py` checks this.

## Tools

Found in `tools/decomp/` (Python 3.12+); each has `--help`.

- `unit_status.py <unit>`: the unit's status, baseline vs current scores, and its functions in retail order with source line numbers.
- `fn_diff.py <symbol>`: target vs current asm for one function (mangled or demangled name; `-u <unit>` if ambiguous). `--context N` shows only differing rows plus N rows around them. `--target` prints the target asm alone, with labels.
- `lint.py`: checks for fakematches and the `symbols.txt` rules above.

## Build and verify

- Work on an up-to-date branch named `<area>/<unit>` (for example `gs/GSmaterial`, `battle/battle_main`, `sdk/ax`).
- Record a baseline before editing: `ninja baseline`.
- Rebuild one unit and the report: `ninja build/RPBP01/src/<path>.o build/RPBP01/report.json`. If compilation failed, `report.json` on disk is stale: fix the failure first.
- `ninja changes` lists regressions against your baseline; `ninja changes_all` lists improvements too. Game code uses `-ipa file`: changing one function can change codegen elsewhere in the same unit, so judge the whole unit.
- Before opening a PR: clang-format (version given in `STYLE.md`) on the files you changed under `src/` and `include/`, plain `ninja` exits 0, and `python tools/decomp/lint.py` reports 0 errors. List each fakematch warning in the PR's Fakematches section.

## Rules

- Keep functions, and their declarations, in retail order.
- Before adding a type, grep `include/` and `src/` for an existing one.
- To produce a particular asm shape, find already-matched code that emits it and reuse the C++ pattern.
- Whole-unit compiler flags go in `configure.py` (`extra_cflags`). A local `#pragma` is allowed only with a one-line comment directly above it saying why the original plausibly looked like this.
- Names follow `STYLE.md`: a real name only with evidence, stated in the PR; otherwise keep the placeholder.
- Imported code keeps its credit line on the first line of each file.
- A partial clean improvement is a good outcome: open it as a draft with notes on what is left.

## Definition of done for a unit

A unit is finished when:

1. Every function matches at 100% in objdiff.
2. Its data sections are split in `splits.txt` and the object is marked `Matching` (linked) in `configure.py`, with the DOL hash unchanged.
3. It has no `fn_` names or unknown types left except documented unknowns, no raw offset access, no placeholder signatures, and no unjustified fakematch.
4. It follows `STYLE.md` and has been reviewed before merging.

Units that are not finished stay `NonMatching` and may contain scaffolding (for instance the placeholder stubs in `src/.unsorted/`), which is replaced unit by unit, never extended.

## Commits and PRs

- Fill in every section of `.github/pull_request_template.md`.
- Commit subject: `<area>: <what changed>`, with a short body if useful.
- Commit messages, PR descriptions and comments describe the change only: no attribution lines, co-author trailers, links to outside tools or generated footers. No game data, personal names, e-mail addresses or local file paths.
- Editor, assistant and tool configuration stays out of the repository.
- PRs are squash-merged once CI is green and the review is done.
- Don't regenerate the README progress table in a unit PR. It is refreshed in an occasional small PR.

## Sign-off

These wait for the other maintainer's approval:

- moving or removing an existing `splits.txt` boundary, renaming a unit;
- project-wide flags, compilers or build changes in `configure.py`;
- history rewrites and force-pushes;
- repository and organisation settings;
- changes to `STYLE.md`, `docs/fakematches.md` or `tools/decomp/lint.py`;
- code imported from a new outside source.

## Roles

- bgsamm: organisation Owner (settings, secrets, app installs).
- salvagedisc: Maintain on the repository (branches, PRs, reviews, merges).
- Admin requests go to bgsamm.
