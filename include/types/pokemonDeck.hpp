#pragma once

// Size: 0x10
struct PokemonDeckHeader {
    /* 0x00 */ u8 _00[0x10];
};

// Size: 0x38
struct PokemonDeckEntry {
    /* 0x00 */ u8 _00[0x38];
};

struct PokemonDeck {
    /* 0x00 */ PokemonDeckHeader mHeader;
    /* 0x10 */ PokemonDeckEntry mEntries[];
};
