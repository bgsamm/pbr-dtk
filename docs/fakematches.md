# Fakematches

A fakematch is source that produces the right bytes but that the original
programmers would not plausibly have written. The goal of this project is
plausible source, not just a byte match, so a fakematch counts as unfinished
work even at 100%. If a unit only matches with such a construct, leave it
`NonMatching`; see the [definition of done](../CONTRIBUTING.md#definition-of-done-for-a-unit)
for when a unit can be marked `Matching`.

`tools/decomp/lint.py` helps find both kinds of construct below: it reports
the ones that are never accepted as errors and the ones that need a
justification as warnings. It is not foolproof however. It can't detect every case, so passing lint does not guarantee a unit has no fakematches.

## Never accepted

- `__declspec(section ...)` or other forced section placement
- hard-coded game addresses (main memory, 0x80000000-0x817FFFFF) cast to
  pointers

## Needs justification

List every use in the PR, with the file and line and one sentence on why the
original code plausibly looked like this. "It makes it match" is not a reason
on its own; the question is whether a programmer would have written it.

- `asm`/`__asm`
- `volatile`
- `register`
- `goto`
- `#pragma` (apart from `#pragma once` in headers)
- `NO_INLINE`
- hard-coded hardware addresses (registers, uncached memory) cast to pointers
- casts between unrelated types (type punning), including assignment through
  a reference cast (`static_cast<u32 &>(x) = y`)
- raw pointer arithmetic such as `*(u32 *)(p + 0x2c)` instead of a structure,
  even a partial one
- structures of function pointers standing in for a C++ class with virtual
  methods
