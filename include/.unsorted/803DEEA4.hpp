#pragma once

#include <revolution/types.h>

struct Unk8063D230;

typedef void (*Unk8063D230Func)(Unk8063D230 *entry, void *arg);

// size: 0x8
struct Unk8063D230 {
    /* 0x0 */ Unk8063D230Func func;
    /* 0x4 */ void *arg;
};

#define UNK_8063D230_COUNT 16

void fn_803DEEA4();
Unk8063D230 *fn_803DEF00(Unk8063D230Func func, void *arg, u32 priority);
void fn_803DEF3C(Unk8063D230 *entry);
void fn_803DEF70();
