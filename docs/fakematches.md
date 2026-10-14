# docs/fakematches.md

A fakematch is source that produces the right bytes but that the original
programmers would not plausibly have written. The goal of this project is
plausible source, not just a byte match, so a fakematch counts as unfinished
work even at 100%. If a unit only matches with a such a construct, leave it
`NonMatching`.

## Fakematches

List every use of these in the PR, with the file and line and one sentence on
why the original code plausibly looked like this. "It makes it match" is not a
reason on its own; the question is whether a programmer would have written it.

- `asm`/`__asm`
- `volatile`
- `register`
- `goto`
- `#pragma` (apart from `#pragma once`)
- `__declspec(section ...)` or other forced section placement
- hard-coded addresses cast to pointers
- casts between unrelated types (type punning)
