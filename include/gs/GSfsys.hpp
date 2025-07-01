#pragma once

#include <revolution/types.h>

// TODO give these proper names
enum FsysState {
    FSYS_STATE_NEG_999 = -999,
    FSYS_STATE_NEG_998 = -998,
    FSYS_STATE_0 = 0,
    FSYS_STATE_1 = 1,
    FSYS_STATE_2 = 2,
    FSYS_STATE_3 = 3,
    FSYS_STATE_5 = 5,
    FSYS_STATE_12 = 12,
    FSYS_STATE_FFFF = 0xffff
};

// size: 0x10
// entry in GSfsys.toc
struct UnkStruct2 {
    /* 0x0 */ u32 mID;
    /* 0x4 */ char *mName;
    /* 0x8 */ u32 _8;
    // TODO bitfield?
    /* 0xc */ u32 mFlags;
};

// size: 0x48
struct UnkStruct1 {
    /* 0x0 */ u32 mID;
    u8 unk1[0x4];
    /* 0x8 */ u32 _8;
    /* 0xc */ u32 _C; // probably a file handle
    // TODO enum?
    /* 0x10 */ int _10;
    /* 0x14 */ FsysState mState;
    // TODO verify this is the same enum as 0x14
    /* 0x18 */ FsysState _18;
    /* 0x1c */ UnkStruct2 *_1c;
    /* 0x20 */ u32 _20;
    /* 0x24 */ u32 _24;
    /* 0x28 */ u32 _28;
    /* 0x2c */ bool _2c;
    /* 0x2d */ bool _2d;
    /* 0x2e */ bool _2e;
    /* 0x30 */ u32 _30;
    /* 0x34 */ u32 _34;
    /* 0x38 */ u32 _38;
    /* 0x3c */ u32 _3c;
    /* 0x40 */ u32 _40;
    /* 0x44 */ u32 _44;
};

// GSfsys.toc header?
struct UnkStruct3 {
    u8 unk1[0x8];
    /* 0x8 */ u32 mCount;
    u8 unk2[0x4];
    /* 0x10 */ u32 mTableOffset;
};

// size: 0x28
struct UnkStruct4 {
    /* 0x0 */ UnkStruct4 *mPrev;
    /* 0x4 */ UnkStruct4 *mNext;
    /* 0x8 */ int _8;
    // TODO is this just an UnkStruct1?
    /* 0xc */ u32 mID;
    /* 0x10 */ u32 _10;
    /* 0x14 */ u32 _14;
    /* 0x18 */ u32 _18;
    /* 0x1c */ u32 _1c;
    /* 0x20 */ u32 _20;
    /* 0x24 */ bool _24;
    /* 0x25 */ bool _25;
};

// size: 0x44
struct UnkStruct5 {
    u8 unk1[0x8];
    /* 0x8 */ u8 _8;
    u8 unk2[0x3b];
};

// These 3 structs are possibly external

struct UnkStruct7 {
    /* 0x0 */ u32 _0;
};

struct UnkStruct8 {
    u8 unk1[0x8];
    /* 0x8 */ u32 _8;
};

struct UnkStruct6 {
    u8 unk1[0x4];
    /* 0x4 */ UnkStruct6 *mNext;
    u8 unk2[1];
    /* 0x9 */ u8 _9;
    /* 0xc */ UnkStruct8 *_C;
    /* 0x10 */ UnkStruct7 *_10;
};

class GSfsys {
public:
    static void *fn_80247280(u32 size);
    static bool fn_80247288();
    static UnkStruct1 *fn_80247470(u32 fsysID, bool param2) NO_INLINE;
    static UnkStruct1 *fn_802474F4(int param1);
    static UnkStruct1 *fn_802475C0() NO_INLINE;
    static UnkStruct2 *fn_802477F4(u32 fsysID) NO_INLINE;
    static void fn_80247834(UnkStruct1 *param1, FsysState param2) NO_INLINE;
    static void fn_80247874(UnkStruct1 *param1, u32 param2);
    static bool fn_802478B4(UnkStruct1 *param1, char *param2) NO_INLINE;
    static bool fn_8024790C(UnkStruct1 *param1) NO_INLINE;
    static u32 fn_80247C5C(UnkStruct8 *param1, u32 param2);
    static void fn_80247EA8(u32 fsysID, u32 param2) NO_INLINE;
    static void fn_802482B4(u32 param1, u32 param2);
    static void fn_80248A54(u32 param1, u32 param2);
    static bool fn_80248B4C(bool param1, bool param2, bool param3);
    static int fn_80248DC0(u32 fsysID);
    static void fn_80248E84(u32 fsysID) NO_INLINE;
    static bool fn_80248ED0(u32 fsysID, u32 param2, u32 param3, bool param4, u32 param5, u32 param6, u32 param7, u32 param8);
    static UnkStruct4 *fn_80248FE0(int param1, u32 fsysID, u32 param3, bool param4, bool param5, bool param6, bool param7, int param8);
    static UnkStruct4 *fn_80249074(u32 fsysID, u32 param2) NO_INLINE;
    static bool fn_802490F8(UnkStruct4 *param1, int param2) NO_INLINE;
    static void fn_80249144(UnkStruct4 *param1) NO_INLINE;
    static bool fn_802491BC(UnkStruct4 *param1) NO_INLINE;
    static void fn_80249280();
    // TODO should these return types really be bool?
    static bool fn_80249328(int param1, u32 fsysID, u32 param3, bool param4, bool param5, bool param6, bool param7, int param8, int param9);
    static bool fn_80249438(u32 fsysID) NO_INLINE;
    static bool fn_80249548(u32 fsysID, bool param2);
    static bool fn_802495DC(u32 fsysID);
    static bool fn_80249664(u32 fsysID) NO_INLINE;
    static bool fn_802496DC(u32 fsysID);
    static void fn_802499B0(u32 param1, bool param2, bool param3, bool param4);
    static void fn_80249B58(UnkStruct1 *param1, FsysState param2);
};
