#pragma once

#include "ds/convert_pokemon.hpp"

struct Bag;
struct BagItem;
struct TrainerInfo;

#define MAX_PC_BOXES 18
#define MAX_MONS_PER_BOX 30
#define PC_BOX_NAME_LEN 20

// PC boxes of the DS games, little-endian and encrypted.
// size: 0xFF4C
struct DSPCStorage {
    /* 0x0 */ u32 currentBox;
    /* 0x4 */ DSBoxPokemon boxes[MAX_PC_BOXES][MAX_MONS_PER_BOX];
    /* 0xFF04 */ u16 names[MAX_PC_BOXES][PC_BOX_NAME_LEN];
};

// The same boxes after conversion.
// size: 0x101D0
struct PCStorage {
    /* 0x0 */ BoxPokemon boxes[MAX_PC_BOXES][MAX_MONS_PER_BOX];
    /* 0xFF00 */ u16 names[MAX_PC_BOXES][PC_BOX_NAME_LEN];
};

void BagItem_FromDS(const BagItem *src, BagItem *dst);
void Bag_FromDS(const Bag *src, Bag *dst);
void PCStorage_FromDS(DSPCStorage *src, PCStorage *dst);
void TrainerInfo_FromDS(TrainerInfo *src, TrainerInfo *dst);
