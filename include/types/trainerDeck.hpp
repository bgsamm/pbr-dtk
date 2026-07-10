#pragma once

#include "common.hpp"

struct TrainerDeckHeader {
    /* 0x00 */ u8 _00[0x10];
};

struct TrainerDeckEntry {
    /* 0x00 */ u8 _00[0x2];
    /* 0x02 */ u8 mTeamSize;
    /* 0x04 */ u16 mPokeDeckStart;
    /* 0x06 */ u16 mPokeDeckEnd;
};

struct TrainerDeck {
    /* 0x00 */ TrainerDeckHeader mHeader;
    /* 0x10 */ TrainerDeckEntry mEntries[];
};
