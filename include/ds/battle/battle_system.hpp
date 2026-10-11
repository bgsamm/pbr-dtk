#pragma once

#include <revolution/types.h>

struct Strbuf;

// Only the fields used so far (pokeplatinum BattleMessage).
// size: unknown
struct BattleMessage {
    /* 0x0 */ u8 commandCode;
};

// Only the fields used so far (pokeplatinum BattleSystem).
// size: unknown
struct BattleSystem {
    /* 0x0 */ u8 unk0[0x18];
    /* 0x18 */ Strbuf *msgBuffer;
};
