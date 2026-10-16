#pragma once

#include <revolution/types.h>

namespace gsapi {

enum WiFiNetworkRunState {
    WIFINETWORK_RUNSTATE_INIT,
    WIFINETWORK_RUNSTATE_START,
    WIFINETWORK_RUNSTATE_CONNECT,
    WIFINETWORK_RUNSTATE_CONNECT_HOOK,
    WIFINETWORK_RUNSTATE_LOGIN,
    WIFINETWORK_RUNSTATE_LOGIN_HOOK,
    WIFINETWORK_RUNSTATE_ONLINE_HOOK,
    WIFINETWORK_RUNSTATE_ONLINE,
    WIFINETWORK_RUNSTATE_CLIENT,
    WIFINETWORK_RUNSTATE_SERVER,
    WIFINETWORK_RUNSTATE_PEER,
    WIFINETWORK_RUNSTATE_MATCHING,
    WIFINETWORK_RUNSTATE_MATCHED_HOOK,
    WIFINETWORK_RUNSTATE_MATCHED,
    WIFINETWORK_RUNSTATE_DISCONNECT_HOOK,
    WIFINETWORK_RUNSTATE_DISCONNECT,
    WIFINETWORK_RUNSTATE_ERROR,
    WIFINETWORK_RUNSTATE_FATAL
};

// size: 0x74
struct Unk8026419C {
    Unk8026419C() {
        _00 = 0;
        _01 = 0;
        _02 = 0;
        _04 = 0;
        _06 = 0;
        _07 = 0;
        _08 = 0;
        _0C = 0;
        _10 = 0;
        _14 = 0;
        _18 = 0;
        _1C = 0;
        _20 = 0;
        _24 = 0;
        _28 = 200;
        _2C = 50;
        _30 = 10;
    }

    /* 0x00 */ u8 _00;
    /* 0x01 */ u8 _01;
    /* 0x02 */ u16 _02;
    /* 0x04 */ u16 _04;
    /* 0x06 */ u8 _06;
    /* 0x07 */ u8 _07;
    /* 0x08 */ s32 _08;
    /* 0x0C */ s32 _0C;
    /* 0x10 */ s32 _10;
    /* 0x14 */ s32 _14;
    /* 0x18 */ s32 _18;
    /* 0x1C */ s32 _1C;
    /* 0x20 */ s32 _20;
    /* 0x24 */ s32 _24;
    /* 0x28 */ s32 _28;
    /* 0x2C */ s32 _2C;
    /* 0x30 */ s32 _30;
    /* 0x34 */ u8 unk34[0x40];
};

// Name known from RTTI. Every virtual function is pure; the names are those of the WiFiNetwork overrides.
// size: 0xEF4
class WiFi {
public:
    WiFi() {
        _EE4 = 0;
        _EE8 = 0;
        _EEC = 0;
        _EF0 = 0;
    }

    virtual s32 fn_80264414() = 0;
    virtual s32 fn_8026441C() = 0;
    virtual s32 fn_80264454() = 0;
    virtual s32 fn_802644CC() = 0;
    virtual s32 fn_802644D4() = 0;
    virtual BOOL fn_802644DC() = 0;
    virtual s32 fn_80264504() = 0;
    virtual s32 fn_80264570() = 0;
    virtual s32 fn_802645C4() = 0;
    virtual s32 fn_802672E0() = 0;
    virtual s32 fn_80264614() = 0;
    virtual char *fn_80263DB8(u32 runState) = 0;
    virtual s32 fn_80266CE0() = 0;
    virtual s32 fn_80266EE8() = 0;
    virtual char *fn_802640DC() = 0;
    virtual s32 fn_80266F44() = 0;
    virtual s32 fn_80266FFC() = 0;
    virtual s32 fn_80267034() = 0;
    virtual u32 fn_8026703C() = 0;
    virtual u16 fn_802670F8() = 0;
    virtual s32 fn_8026725C(s32 idx) = 0;
    virtual s32 fn_80267100(void *data, u32 size, u8 idx) = 0;
    virtual s32 fn_802671E4(u32 idx) = 0;
    virtual s32 fn_80263D18() = 0;
    virtual s32 fn_80263D20() = 0;
    virtual s32 fn_80263D28() = 0;

    /* 0x004 */ u8 _004[0x20];
    /* 0x024 */ Unk8026419C _024[32];
    /* 0xEA4 */ u8 unkEA4[0x40];
    /* 0xEE4 */ s32 _EE4;
    /* 0xEE8 */ s32 _EE8;
    /* 0xEEC */ s32 _EEC;
    /* 0xEF0 */ s32 _EF0;
};

// size: 0xB8
struct Unk80264F20 {
    /* 0x00 */ s64 _00;
    /* 0x08 */ u8 unk08[0x4];
    /* 0x0C */ u8 _0C[0x20];
    /* 0x2C */ s32 _2C;
    /* 0x30 */ s32 _30;
    /* 0x34 */ u16 _34;
    /* 0x36 */ u16 _36;
    /* 0x38 */ u8 unk38[0x80];
};

// size: 0x8
struct Unk80265074 {
    /* 0x0 */ u8 _0;
    /* 0x1 */ u8 _1;
    /* 0x2 */ u8 _2;
    /* 0x3 */ u8 _3;
    /* 0x4 */ s32 _4;
};

// size: 0x22
struct Unk80264938 {
    /* 0x00 */ u8 _00[0x10];
    /* 0x10 */ u8 unk10[0x10];
    /* 0x20 */ u16 _20;
};

// size: 0x10
struct Unk80263D28 {
    /* 0x0 */ s32 _0;
    /* 0x4 */ s32 _4;
    /* 0x8 */ s32 _8;
    /* 0xC */ s32 _C;
};

// size: 0x8
struct Unk80266274 {
    /* 0x0 */ u8 _0;
    /* 0x4 */ s32 _4;
};

// Name known from RTTI.
// size: 0x66A8
class WiFiNetwork : public WiFi {
public:
    WiFiNetwork();

    virtual s32 fn_80264414();
    virtual s32 fn_8026441C();
    virtual s32 fn_80264454();
    virtual s32 fn_802644CC();
    virtual s32 fn_802644D4();
    virtual BOOL fn_802644DC();
    virtual s32 fn_80264504();
    virtual s32 fn_80264570();
    virtual s32 fn_802645C4();
    virtual s32 fn_802672E0();
    virtual s32 fn_80264614();
    virtual char *fn_80263DB8(u32 runState);
    virtual s32 fn_80266CE0();
    virtual s32 fn_80266EE8();
    virtual char *fn_802640DC();
    virtual s32 fn_80266F44();
    virtual s32 fn_80266FFC();
    virtual s32 fn_80267034();
    virtual u32 fn_8026703C();
    virtual u16 fn_802670F8();
    virtual s32 fn_8026725C(s32 idx);
    virtual s32 fn_80267100(void *data, u32 size, u8 idx);
    virtual s32 fn_802671E4(u32 idx);
    virtual s32 fn_80263D18();
    virtual s32 fn_80263D20();
    virtual s32 fn_80263D28();

    void fn_80263CBC();
    void fn_80264300();
    void fn_80264348(u8 idx);
    void fn_802643AC();
    BOOL fn_802644F0();
    s32 fn_802645EC();
    void fn_8026461C(s32 runState);
    void fn_80264684();
    void fn_802646A0();
    void fn_80264718();
    void fn_80264764();
    void fn_80264790();
    void fn_802648B4();
    s32 fn_802648FC();
    s32 fn_80264938(void *key);
    void fn_802649C8();
    void fn_802649E0(void *key);
    void fn_80264A70();
    void fn_80264DC8();
    void fn_80265074(s32 idx);
    void fn_802650EC();
    void fn_802651B0();
    s32 fn_80265488(s32 *out, s32 max);
    void fn_80265714();
    void fn_80265784();
    void fn_802657D8();
    void fn_80265978(u32 a, char *b, s32 c);
    s32 fn_80265A80(u8 a, char *str, s32 c, u8 d);
    s32 fn_80265BB0(u8 a);
    s32 fn_80265C1C(s32 idx);
    s32 fn_80265D2C();
    s32 fn_80265DEC();
    s32 fn_80265E2C(void *key);
    void fn_80266068();
    void fn_80266118();
    void fn_80266274();
    u32 fn_80266538();
    void fn_80266550();
    u32 fn_80266660();
    void fn_80266784();
    void fn_802668B0();
    s32 fn_80266A7C();
    void fn_80266B80();
    void fn_80266BDC();
    void fn_80266BEC();
    void fn_80266F3C(u32 v);
    s32 fn_80266F7C();
    void fn_80266FBC();
    void fn_80266FC8();
    s32 fn_80267098();
    void fn_802672E8();
    void fn_80267324();
    void fn_80267378();
    void fn_802673B8();
    s32 fn_802673BC(s32 a, s32 b);
    s32 fn_8026745C(s32 *out);

    // TODO Defined in unit 802674CC.
    void *fn_802674DC();
    void *fn_802674E4(s32 idx);
    s32 fn_80267504();
    void fn_80267534();
    void fn_80267690();
    void fn_802676B4(s32 v);
    void *fn_802677F8();
    void fn_8026806C(s32 idx, s64 a, void *b, s32 c, s32 d);

    /* 0x0EF4 */ u8 unkEF4[0xC];
    /* 0x0F00 */ u8 _0F00[0xD28];
    /* 0x1C28 */ u32 _1C28;
    /* 0x1C2C */ s32 _1C2C;
    /* 0x1C30 */ u8 unk1C30[0x1C];
    /* 0x1C4C */ s32 _1C4C;
    /* 0x1C50 */ Unk80264F20 _1C50;
    /* 0x1D08 */ Unk80264F20 _1D08[30];
    /* 0x3298 */ Unk80265074 _3298[30];
    /* 0x3388 */ s32 _3388;
    /* 0x338C */ s32 _338C;
    /* 0x3390 */ s32 _3390;
    /* 0x3394 */ s32 _3394;
    /* 0x3398 */ s32 _3398;
    /* 0x339C */ s32 _339C;
    /* 0x33A0 */ s32 _33A0;
    /* 0x33A4 */ s32 _33A4;
    /* 0x33A8 */ s32 _33A8;
    /* 0x33AC */ s32 _33AC;
    /* 0x33B0 */ s32 _33B0;
    /* 0x33B4 */ s32 _33B4;
    /* 0x33B8 */ Unk80264938 _33B8[64];
    /* 0x3C38 */ s32 mRunState;
    /* 0x3C3C */ s32 mPrevRunState;
    /* 0x3C40 */ s32 _3C40;
    /* 0x3C44 */ s32 _3C44;
    /* 0x3C48 */ s32 _3C48;
    /* 0x3C4C */ s32 _3C4C;
    /* 0x3C50 */ s32 _3C50;
    /* 0x3C54 */ s32 _3C54;
    /* 0x3C58 */ s32 _3C58;
    /* 0x3C5C */ s32 _3C5C;
    /* 0x3C60 */ s32 _3C60;
    /* 0x3C64 */ s32 _3C64;
    /* 0x3C68 */ s32 _3C68;
    /* 0x3C6C */ s32 _3C6C;
    /* 0x3C70 */ s32 _3C70;
    /* 0x3C74 */ s32 _3C74;
    /* 0x3C78 */ s32 _3C78;
    /* 0x3C7C */ s32 _3C7C;
    /* 0x3C80 */ s32 _3C80;
    /* 0x3C84 */ s32 _3C84;
    /* 0x3C88 */ u8 _3C88;
    /* 0x3C89 */ u8 _3C89;
    /* 0x3C8C */ s32 _3C8C;
    /* 0x3C90 */ char _3C90[0x80];
    /* 0x3D10 */ s32 _3D10;
    /* 0x3D14 */ s32 _3D14;
    /* 0x3D18 */ s32 _3D18;
    /* 0x3D1C */ u32 _3D1C[2];
    /* 0x3D24 */ u8 unk3D24[0x7F8];
    /* 0x451C */ u8 _451C[2][0x1000];
    /* 0x651C */ s32 _651C;
    /* 0x6520 */ Unk80263D28 _6520[2];
    /* 0x6540 */ Unk80266274 _6540[4];
    /* 0x6560 */ Unk80266274 _6560[4];
    /* 0x6580 */ s32 _6580[2];
    /* 0x6588 */ u8 unk6588[0x118];
    /* 0x66A0 */ s32 _66A0;
    /* 0x66A4 */ s32 _66A4;
};

} // namespace gsapi
