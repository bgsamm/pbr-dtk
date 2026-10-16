#pragma once

// Names as in pret/pokeplatinum; values are this game's (Diamond and Pearl numbering where Platinum differs).

enum PokemonType {
    TYPE_NORMAL = 0,
    TYPE_FIGHTING,
    TYPE_FLYING,
    TYPE_POISON,
    TYPE_GROUND,
    TYPE_ROCK,
    TYPE_BUG,
    TYPE_GHOST,
    TYPE_STEEL,
    TYPE_MYSTERY,
    TYPE_FIRE,
    TYPE_WATER,
    TYPE_GRASS,
    TYPE_ELECTRIC,
    TYPE_PSYCHIC,
    TYPE_ICE,
    TYPE_DRAGON,
    TYPE_DARK,
};
#define TYPE_MULTI_IMMUNE 0
#define TYPE_MULTI_NOT_VERY_EFF 5
#define TYPE_MULTI_SUPER_EFF 20
