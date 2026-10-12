#include ".unsorted/80263CBC.hpp"

#include ".unsorted/8025E348.hpp"

#include <cstdio>
#include <cstring>

#include "common.hpp"

using namespace gsapi;

// TODO Replace with proper imports
extern "C" {
char *fn_8025E4E8();
u32 fn_8025E370();
WiFiNetwork *fn_8025E31C(void *);
void *fn_8025DFD0();
s32 fn_8025E80C(const void *a, const void *b, u32 size);
void fn_8025E7D8(void *dst, const void *src, u32 size);
u16 fn_8025E78C(const void *data, u32 size);
void fn_8025E86C();
s32 fn_8025BDA4();
void fn_8025BEB4();
s32 fn_8025BD9C();
void fn_8025BBFC(char *dst, char *src, s32 n);
void fn_8025CAA8(void *);
void fn_8025CACC();
void fn_8025CC38();
s32 fn_8025CC48();
s32 fn_8025CC94();
void fn_8025CCA4(s32, s32);
void fn_8025EC68(WiFiNetwork *, u32, u16, u8, s32);
s32 fn_8025ECF8(WiFiNetwork *, void *, u32, s32, u8);
void fn_8025EDC8(WiFiNetwork *, u32);
void fn_8025EE18(WiFiNetwork *);
s32 fn_8025EF54(WiFiNetwork *);
u32 fn_8025EFA4(WiFiNetwork *, u16 *, u16 *);
void fn_8025F00C(WiFiNetwork *);
void fn_8025F4E0();
void fn_8025F934(WiFiNetwork *, s32);
s32 fn_802F4D18();
u32 fn_802F4FE8(s32, s32);
s32 fn_8031C48C(s32 *);
s32 fn_8031C4A4(s32 *, s32 *);
void fn_8031C550();
void fn_8031C598(s32, char *, u32, void *, void *);
void fn_8031C890();
void fn_8031CB2C(s32);
void fn_8031C2B4(char *, u32, void *, u32);
void fn_8031D4B0(void *);
void fn_8031D510(void *);
void fn_8031D51C(void *);
void fn_8031D528();
s32 fn_8031DFFC(u8, void *);
void fn_8031E014();
s32 fn_8031E08C();
s32 fn_8031E0B0(u16, u32, u16, s32);
u8 fn_8031F198(void *, u8 *, u8 *, s32);
void fn_8031F2E4(void *, u32);
void fn_8031F484(void *, void *);
void fn_80321BFC(void *, void *, s32, char *, char *, s32, s32, void *, s32);
void fn_80321E84();
void fn_80321FEC();
s32 fn_80322260(void *, s32, void *, void *);
s32 fn_803223C4(s32, void *, void *, void *, void *, void *, void *);
s32 fn_803224B0(u8, char *, void *, void *, void *, void *);
s32 fn_803225B8(u8, void *, void *, void *, void *);
s32 fn_803226C4(s32, void *, void *, void *, void *);
void fn_80322950(void *, void *);
s32 fn_80322978();
s32 fn_80322A70(u8);
s32 fn_80322B9C();
s32 fn_80322BF8();
u32 fn_80322C58();
s32 fn_80322DC8(u8);
s32 fn_80322E74();
void fn_8032432C();
s32 fn_803243B0();
u8 fn_80324440(u8, char *, void *);
s32 fn_80324800(void *, char *, s32);
void fn_8032488C(s32, void *, s32);
s32 fn_80330D88(u8, u32, u16);
void fn_80330E7C(u8, void *, u32);
void fn_80330EEC(u8);
void fn_80330F94(void *);
void fn_80330FB4(void *);
void fn_80330FD4(void *);
s32 fn_803331D0(void *);
s32 fn_80333578(void *);
void fn_80333584(void *);
s64 fn_803338A4(void *);
s32 fn_80335DB4();
void DCFlushRange(void *, u32);
}

extern f32 lbl_8063D988;
extern const f32 lbl_80642608;
extern const f32 lbl_8064260C;
extern const f32 lbl_80642610;

/* lbl_8063FA10 */ s32 lbl_8063FA10;
/* lbl_8063FA14 */ u32 lbl_8063FA14;
/* lbl_8063FA18 */ s32 lbl_8063FA18;
/* lbl_80503BF8 */ s32 lbl_80503BF8[32];

void fn_80265FF0(u32 a, u32 idx);
void fn_80265FF8(u32 idx, u32 a, u32 b);
void fn_80265218();
void fn_802652A4(s32 idx);
void fn_802652E8(s32 idx);
void fn_80267374();
void fn_802673B4();

// TODO Starts the local connection library once and registers fn_80265FF0 and fn_80265FF8 as its callbacks.
void WiFiNetwork::fn_80263CBC() {
    if (lbl_8063FA10 == 0) {
        fn_8031D4B0(&lbl_8063FA14);
        lbl_8063FA10 = 1;
        fn_8031D51C((void *)fn_80265FF0);
        fn_8031D510((void *)fn_80265FF8);
    }
}

// TODO Clears the flag set by fn_80263CBC and stops the local connection library.
void fn_80263D0C() {
    lbl_8063FA10 = 0;
    fn_8031E014();
}

// TODO Fixed value 300; the callers are outside this unit.
s32 WiFiNetwork::fn_80263D18() {
    return 300;
}

// TODO Fixed value 40; the callers are outside this unit.
s32 WiFiNetwork::fn_80263D20() {
    return 40;
}

// TODO Largest value among the remote entries of _6520, between 10 and 40.
s32 WiFiNetwork::fn_80263D28() {
    s32 r = 10;
    for (s32 i = 0; i < 2; i++) {
        if (_6520[i]._4 != 0 && _6520[i]._0 == 0) {
            if (_6520[i]._8 / 100 > r) {
                r = _6520[i]._8;
            }
        }
    }
    if (r > 40) {
        r = 40;
    }
    return r;
}

// TODO Name of a run state, for debug output.
char *WiFiNetwork::fn_80263DB8(u32 runState) {
    switch (runState) {
        case WIFINETWORK_RUNSTATE_INIT:            return "WIFINETWORK_RUNSTATE_INIT";
        case WIFINETWORK_RUNSTATE_START:           return "WIFINETWORK_RUNSTATE_START";
        case WIFINETWORK_RUNSTATE_CONNECT:         return "WIFINETWORK_RUNSTATE_CONNECT";
        case WIFINETWORK_RUNSTATE_CONNECT_HOOK:    return "WIFINETWORK_RUNSTATE_CONNECT_HOOK";
        case WIFINETWORK_RUNSTATE_LOGIN:           return "WIFINETWORK_RUNSTATE_LOGIN";
        case WIFINETWORK_RUNSTATE_LOGIN_HOOK:      return "WIFINETWORK_RUNSTATE_LOGIN_HOOK";
        case WIFINETWORK_RUNSTATE_ONLINE_HOOK:     return "WIFINETWORK_RUNSTATE_ONLINE_HOOK";
        case WIFINETWORK_RUNSTATE_ONLINE:          return "WIFINETWORK_RUNSTATE_ONLINE";
        case WIFINETWORK_RUNSTATE_CLIENT:          return "WIFINETWORK_RUNSTATE_CLIENT";
        case WIFINETWORK_RUNSTATE_SERVER:          return "WIFINETWORK_RUNSTATE_SERVER";
        case WIFINETWORK_RUNSTATE_PEER:            return "WIFINETWORK_RUNSTATE_PEER";
        case WIFINETWORK_RUNSTATE_MATCHING:        return "WIFINETWORK_RUNSTATE_MATCHING";
        case WIFINETWORK_RUNSTATE_MATCHED_HOOK:    return "WIFINETWORK_RUNSTATE_MATCHED_HOOK";
        case WIFINETWORK_RUNSTATE_MATCHED:         return "WIFINETWORK_RUNSTATE_MATCHED";
        case WIFINETWORK_RUNSTATE_DISCONNECT_HOOK: return "WIFINETWORK_RUNSTATE_DISCONNECT_HOOK";
        case WIFINETWORK_RUNSTATE_DISCONNECT:      return "WIFINETWORK_RUNSTATE_DISCONNECT";
        case WIFINETWORK_RUNSTATE_ERROR:           return "WIFINETWORK_RUNSTATE_ERROR";
        case WIFINETWORK_RUNSTATE_FATAL:           return "WIFINETWORK_RUNSTATE_FATAL";
    }
    char *buf = fn_8025E4E8();
    sprintf(buf, "WIFINET_RUNSTATE_%d", runState);
    return buf;
}

// TODO Name of a DWC error code.
char *fn_80263EC4(u32 error) {
    switch (error) {
        case 0:  return "DWC_ERROR_NONE";
        case 1:  return "DWC_ERROR_DS_MEMORY_ANY";
        case 2:  return "DWC_ERROR_AUTH_ANY";
        case 3:  return "DWC_ERROR_AUTH_OUT_OF_SERVICE";
        case 4:  return "DWC_ERROR_AUTH_STOP_SERVICE";
        case 5:  return "DWC_ERROR_AC_ANY";
        case 6:  return "DWC_ERROR_NETWORK";
        case 7:  return "DWC_ERROR_GHTTP_ANY";
        case 8:  return "DWC_ERROR_DISCONNECTED";
        case 9:  return "DWC_ERROR_FATAL";
        case 10: return "DWC_ERROR_FRIENDS_SHORTAGE";
        case 11: return "DWC_ERROR_NOT_FRIEND_SERVER";
        case 12: return "DWC_ERROR_MO_SC_CONNECT_BLOCK";
        case 13: return "DWC_ERROR_SERVER_FULL";
        case 14: return "DWC_ERROR_ND_ANY";
        case 15: return "DWC_ERROR_ND_HTTP";
        case 16: return "DWC_ERROR_SVL_ANY";
        case 17: return "DWC_ERROR_SVL_HTTP";
    }
    char *buf = fn_8025E4E8();
    sprintf(buf, "DWC_ERROR_UNKNOWN_%d", error);
    return buf;
}

// TODO Name of a DWC error type.
char *fn_80263FD0(u32 type) {
    switch (type) {
        case 0: return "DWC_ETYPE_NO_ERROR";
        case 1: return "DWC_ETYPE_LIGHT";
        case 2: return "DWC_ETYPE_SHOW_ERROR";
        case 3: return "DWC_ETYPE_SHUTDOWN_FM";
        case 4: return "DWC_ETYPE_SHUTDOWN_GHTTP";
        case 5: return "DWC_ETYPE_SHUTDOWN_ND";
        case 6: return "DWC_ETYPE_DISCONNECT";
        case 7: return "DWC_ETYPE_FATAL";
    }
    char *buf = fn_8025E4E8();
    sprintf(buf, "DWC_ETYPE_UNKNOWN_%d", type);
    return buf;
}

// TODO Text of a DWC error code number.
char *fn_8026408C(s32 code) {
    char *buf = fn_8025E4E8();
    if (code < 0) {
        code = -code;
    }
    sprintf(buf, "DWC_ECODE_%d", code);
    return buf;
}

// The callees are not inlined in the original.
#pragma dont_inline on
// TODO Text of the current error as "error.type.code".
char *WiFiNetwork::fn_802640DC() {
    s32 code;
    s32 type;
    s32 error;
    char *buf = fn_8025E4E8();
    if (_3D18 != 0) {
        type = 2;
        error = 5;
        code = _3D18;
    } else {
        error = fn_8031C4A4(&code, &type);
    }
    sprintf(buf, "%s.%s.%s", fn_80263EC4(error), fn_80263FD0(type), fn_8026408C(code));
    return buf;
}
#pragma dont_inline reset

WiFiNetwork::WiFiNetwork() {
    mRunState = WIFINETWORK_RUNSTATE_INIT;
    mPrevRunState = WIFINETWORK_RUNSTATE_INIT;
    _3C40 = 0;
    _1C2C = 0;
    _66A0 = 0;
    _3C50 = 0;
    _3C54 = 0;
    _3C74 = 0;
    _3C60 = 0;
    _3C64 = 0;
    _3C68 = 0;
    _3C84 = 0;
    _3C88 = 0;
    _3390 = 0;
    _3394 = 0;
    _338C = 0;
    _3C6C = 0;
    _3C70 = 0;
    _3C58 = 0;
    _3C5C = 0;
    _3D14 = 0;
    _3388 = 0;
    memset(&_1C50, 0, sizeof(Unk80264F20));
    fn_80266FC8();
    _651C = 0;
    fn_802643AC();
    fn_80265218();
    fn_802650EC();
    fn_80264300();
    fn_802649C8();
    _66A4 = 0;
}

// TODO Clears the two matchmaking key tables.
void WiFiNetwork::fn_80264300() {
    memset(_6540, 0, sizeof(_6540));
    memset(_6560, 0, sizeof(_6560));
}

// TODO Clears the connection entry of player idx.
void WiFiNetwork::fn_80264348(u8 idx) {
    if (idx < 2) {
        memset(&_6520[idx], 0, sizeof(Unk80263D28));
        _3D1C[idx] = 0;
    }
}

// The callee is not inlined in the original.
#pragma dont_inline on
// TODO Clears the connection entries of both players.
void WiFiNetwork::fn_802643AC() {
    for (u32 i = 0; i < 2; i++) {
        fn_80264348(i);
    }
}
#pragma dont_inline reset

// TODO Allocation callback given to the DWC library.
void fn_802643F8(u32, u32 size) {
    fn_8025E47C(size);
}

// TODO Free callback given to the DWC library.
void fn_80264400(u32, u32 block) {
    if (block) {
        fn_8025E4D0((void *)block);
    }
}

// TODO Always returns 0.
s32 WiFiNetwork::fn_80264414() {
    return 0;
}

// TODO Requests the connection; fails when it is already requested or locked.
s32 WiFiNetwork::fn_8026441C() {
    if (_3C50) {
        return -1;
    }
    if (_3D14) {
        return -1;
    }
    _3C50 = 1;
    return 0;
}

// TODO Requests the disconnection; fails when no connection was requested or it is locked.
s32 WiFiNetwork::fn_80264454() {
    if (_3C50 == 0) {
        return -1;
    }
    if (_3D14) {
        return -1;
    }
    fn_80266EE8();
    _3C50 = 0;
    _3C58 = 1;
    _3C5C = 1;
    return 0;
}

// TODO Always returns -1.
s32 WiFiNetwork::fn_802644CC() {
    return -1;
}

// TODO Whether the connection is requested.
s32 WiFiNetwork::fn_802644D4() {
    return _3C50;
}

// TODO Whether the state machine has left the initial state.
BOOL WiFiNetwork::fn_802644DC() {
    return mRunState != WIFINETWORK_RUNSTATE_INIT;
}

// TODO Whether the online state asked for a new login.
BOOL WiFiNetwork::fn_802644F0() {
    return _3C70 != 0;
}

// TODO Whether the player is online, including a light error.
s32 WiFiNetwork::fn_80264504() {
    s32 code;
    s32 type;
    switch (mRunState) {
        case WIFINETWORK_RUNSTATE_ONLINE_HOOK:
        case WIFINETWORK_RUNSTATE_ONLINE:
        case WIFINETWORK_RUNSTATE_CLIENT:
        case WIFINETWORK_RUNSTATE_SERVER:
        case WIFINETWORK_RUNSTATE_PEER:
        case WIFINETWORK_RUNSTATE_MATCHING:
        case WIFINETWORK_RUNSTATE_MATCHED_HOOK:
        case WIFINETWORK_RUNSTATE_MATCHED:      return 1;
        case WIFINETWORK_RUNSTATE_ERROR:
            fn_8031C4A4(&code, &type);
            if (type == 1) {
                return 1;
            }
            break;
    }
    return 0;
}

// TODO Whether a match is being made or requested.
s32 WiFiNetwork::fn_80264570() {
    switch (mRunState) {
        case WIFINETWORK_RUNSTATE_CLIENT:
        case WIFINETWORK_RUNSTATE_SERVER:
        case WIFINETWORK_RUNSTATE_PEER:
        case WIFINETWORK_RUNSTATE_MATCHING:
        case WIFINETWORK_RUNSTATE_MATCHED_HOOK:
        case WIFINETWORK_RUNSTATE_MATCHED:      return 1;
    }
    if (_3C60 || _3C64 || _3C68) {
        return 1;
    }
    return 0;
}

// TODO Whether a match is made.
s32 WiFiNetwork::fn_802645C4() {
    switch (mRunState) {
        case WIFINETWORK_RUNSTATE_MATCHED_HOOK:
        case WIFINETWORK_RUNSTATE_MATCHED:      return 1;
    }
    return 0;
}

// TODO Whether the state machine is in an error state.
s32 WiFiNetwork::fn_802645EC() {
    switch (mRunState) {
        case WIFINETWORK_RUNSTATE_ERROR:
        case WIFINETWORK_RUNSTATE_FATAL: return 1;
    }
    return 0;
}

// TODO Current run state.
s32 WiFiNetwork::fn_80264614() {
    return mRunState;
}

// The callees are not inlined in the original.
#pragma dont_inline on
// TODO Switches to another run state and restarts its step counter.
void WiFiNetwork::fn_8026461C(s32 runState) {
    fn_80322E74();
    fn_80267098();
    fn_80266660();
    fn_8026703C();
    mRunState = runState;
    _3C40 = 0;
}
#pragma dont_inline reset

// TODO Shuts the DWC friend matching library down if it was started.
void WiFiNetwork::fn_80264684() {
    if (lbl_8063FA18) {
        lbl_8063FA18 = 0;
        fn_8031C890();
    }
}

// The callees are not inlined in the original.
#pragma dont_inline on
// TODO Starts the DWC friend matching library for the game code RPBJ.
void WiFiNetwork::fn_802646A0() {
    if (lbl_8063FA18 == 0) {
        lbl_8063FA18 = 1;
        fn_8031C598(1, "pokebattlewii", 'RPBJ', (void *)fn_802643F8, (void *)fn_80264400);
        fn_8031CB2C(0);
        fn_802676B4(0);
    }
}
#pragma dont_inline reset

// TODO Handler of WIFINETWORK_RUNSTATE_INIT.
void WiFiNetwork::fn_80264718() {
    switch (_3C40) {
        case 0:
            _3390 = 0;
            _3394 = 0;
            _338C = 0;
            _3C40++;
            break;
        case 1:
            if (_3C50) {
                fn_8026461C(WIFINETWORK_RUNSTATE_START);
            }
            break;
    }
}

// TODO Handler of WIFINETWORK_RUNSTATE_START.
void WiFiNetwork::fn_80264764() {
    _3390 = 0;
    _3394 = 0;
    _338C = 0;
    _3C6C = 0;
    _3C70 = 0;
    _33A8 = 0;
    _33AC = 0;
    _33B0 = 0;
    fn_8026461C(WIFINETWORK_RUNSTATE_CONNECT);
}

// TODO Handler of WIFINETWORK_RUNSTATE_CONNECT.
void WiFiNetwork::fn_80264790() {
    switch (_3C40) {
        case 0:
            _338C = 0;
            if (fn_8025BDA4() == 0) {
                _3C40 = 99;
            } else {
                _3C40++;
            }
            break;
        case 1: _3C40++; break;
        case 2: _3C40++; break;
        case 3:
            if (_3C50 == 0) {
                _3C58 = 0;
                fn_8025BEB4();
                fn_8026461C(WIFINETWORK_RUNSTATE_INIT);
            } else {
                fn_8026461C(WIFINETWORK_RUNSTATE_CONNECT_HOOK);
            }
            break;
        case 99:
            if (_3C50 == 0) {
                fn_8026461C(WIFINETWORK_RUNSTATE_INIT);
            } else {
                _338C = 1;
                s32 h = fn_8025BD9C();
                fn_80266F3C(fn_802F4FE8(h, fn_802F4D18()));
            }
            break;
    }
}

// TODO Handler of WIFINETWORK_RUNSTATE_CONNECT_HOOK.
void WiFiNetwork::fn_802648B4() {
    _339C = 0;
    fn_802672E8();
    fn_802646A0();
    fn_8026461C(WIFINETWORK_RUNSTATE_LOGIN);
}

// TODO Login result: -1 while pending, otherwise whether the login was rejected.
s32 WiFiNetwork::fn_802648FC() {
    if (_3C6C) {
        return -1;
    }
    if (_3390) {
        return _3394 != 0;
    }
    return -1;
}

// The callee is not inlined in the original.
#pragma dont_inline on
// TODO Whether the key is among the 64 entries of _33B8.
s32 WiFiNetwork::fn_80264938(void *key) {
    for (s32 i = 0; i < 64; i++) {
        if (_33B8[i]._20 == 1 && fn_8025E80C(_33B8[i]._00, key, 0x10) == 0) {
            return 1;
        }
    }
    return 0;
}
#pragma dont_inline reset

// TODO Clears the table of known keys.
void WiFiNetwork::fn_802649C8() {
    _33B4 = 0;
    memset(_33B8, 0, sizeof(_33B8));
}

// TODO Adds the key to the 64 entries of _33B8, overwriting the oldest one.
void WiFiNetwork::fn_802649E0(void *key) {
    if (fn_80264938(key) == 0) {
        if (_33B4 >= 64) {
            _33B4 = 0;
        }
        fn_8025E7D8(_33B8[_33B4]._00, key, 0x10);
        _33B8[_33B4]._20 = 1;
        _33B4++;
    }
}

void fn_80264E14(s32 result, s32 a, WiFiNetwork *self);
void fn_8026560C(s32 result, s32 a, s32 b, u8 idx, s32 id, WiFiNetwork *self);
void fn_80265EF0(u32 a, u8 idx);
void fn_80265F6C(u8 idx, u32 a, u32 b);
void fn_80266000(s32 v, u8 idx);

// TODO Handler of WIFINETWORK_RUNSTATE_LOGIN.
void WiFiNetwork::fn_80264A70() {
    switch (_3C40) {
        case 0:
            _3C4C = (s32)(lbl_80642608 + lbl_8064260C * lbl_8063D988);
            _3C40++;
            break;
        case 1:
            if (_3C4C-- <= 0) {
                _3C40++;
            }
            break;
        case 2:
            _3C6C = 0;
            _3C40++;
            break;
        case 3:
            if (_66A0) {
                _3C40 = 50;
            } else {
                _3C40 = 10;
            }
            break;
        case 10: {
            memset(&_1C28, 0, sizeof(_1C28));
            fn_80321BFC(&_1C28, fn_802674DC(), 0x2A93, "pokebattlewii", "TzRgSc", 0, 0, fn_802674E4(0), fn_80267504());
            _339C = 0;
            if (fn_80322260(_004, 0, (void *)fn_80264E14, this) == 0) {
                fn_80264DC8();
                fn_80264454();
                _3C70 = 0;
                fn_8026461C(WIFINETWORK_RUNSTATE_DISCONNECT_HOOK);
            } else {
                _3C4C = (s32)(lbl_80642608 + lbl_80642610 * lbl_8063D988);
                _3C40++;
            }
            break;
        }
        case 11:
            fn_80321FEC();
            if (_3C4C-- <= 0) {
                fn_80264DC8();
                fn_80264454();
                _3C70 = 0;
                fn_8026461C(WIFINETWORK_RUNSTATE_DISCONNECT_HOOK);
            } else if (_339C) {
                _3394 = 0;
                if (fn_80335DB4() == 2) {
                    _3394 = 1;
                }
                _3390 = 1;
                if (_3394 == 0) {
                    fn_802649E0(_004);
                }
                if (_66A4 == 0) {
                    fn_8025CAA8(fn_802677F8());
                    _66A4 = 1;
                }
                fn_80267534();
                _33A0 = 0;
                _33A4 = 0;
                fn_80322950((void *)fn_8026560C, this);
                fn_80330F94((void *)fn_80265EF0);
                fn_80330FB4((void *)fn_80265F6C);
                fn_80330FD4((void *)fn_80266000);
                for (u8 i = 0; i < 2; i++) {
                    fn_80330E7C(i, _451C[i], 0x1000);
                }
                fn_8026461C(WIFINETWORK_RUNSTATE_LOGIN_HOOK);
            }
            break;
        case 50:
            _33A0 = 0;
            _33A4 = 0;
            fn_80263CBC();
            _3394 = 0;
            _3390 = 1;
            fn_8026461C(WIFINETWORK_RUNSTATE_LOGIN_HOOK);
            break;
    }
}

// TODO Undoes the login: clears _3390 and, outside local mode, calls fn_80321E84.
void WiFiNetwork::fn_80264DC8() {
    _3390 = 0;
    fn_802673B4();
    if (_66A0 == 0) {
        fn_80321E84();
    }
    fn_802673B8();
}

void fn_80264ED8(s32 result, s32 a, WiFiNetwork *self);
void fn_80264F20(s32 idx, s32 a, char *str, WiFiNetwork *self);
void fn_80265138(s32 a, s32 b, WiFiNetwork *self);
void fn_80265174(s32 a, WiFiNetwork *self);

// TODO Login callback: stores the result and starts the friend list update.
void fn_80264E14(s32 result, s32 a, WiFiNetwork *self) {
    if (result) {
        self->_3C70 = 0;
        return;
    }
    self->_1C4C = a;
    if (fn_80333578(self->fn_802674DC())) {
        fn_80333584(self->fn_802674DC());
        self->fn_80267690();
    }
    self->_3398 = 0;
    if (fn_803223C4(0, (void *)fn_80264ED8, self, (void *)fn_80264F20, self, (void *)fn_80265138, self) == 0) {
        self->_3C70 = 0;
    } else {
        fn_8031F484((void *)fn_80265174, self);
    }
}

// TODO Callback of the friend list update.
void fn_80264ED8(s32 result, s32 a, WiFiNetwork *self) {
    if (result == 0) {
        if (a) {
            self->fn_80267690();
        }
        self->_339C = 1;
    }
}

// TODO Callback receiving the status string of friend idx.
void fn_80264F20(s32 idx, s32, char *str, WiFiNetwork *self) {
    if (idx >= 0 && idx < 30) {
        Unk80264F20 buf;
        u8 x9;
        u8 x8;
        memset(&buf, 0, sizeof(buf));
        fn_8031C2B4(str, strlen(str), &buf, sizeof(buf));
        if ((u16)fn_8025E78C(&buf, sizeof(buf)) == 0) {
            memcpy(&self->_1D08[idx], &buf, sizeof(buf));
            self->fn_8026806C(idx, buf._00, buf._0C, buf._2C, buf._30);
        } else {
            memset(&self->_1D08[idx], 0, sizeof(Unk80264F20));
        }
        u8 r = fn_8031F198(self->fn_802674E4(idx), &x9, &x8, 0);
        self->_3298[idx]._1 = x9;
        self->_3298[idx]._2 = x8;
        self->_3298[idx]._3 = 1;
        if (r != self->_3298[idx]._0) {
            self->_3298[idx]._4 = fn_8025E370();
        }
        self->_3298[idx]._0 = r;
        self->_3388++;
    }
}

// TODO Clears the data of friend idx.
void WiFiNetwork::fn_80265074(s32 idx) {
    if (!(idx >= 0 && idx <= 30)) {
        return;
    }
    memset(&_1D08[idx], 0, sizeof(Unk80264F20));
    memset(&_3298[idx], 0, sizeof(Unk80265074));
}

// TODO Clears the data of every friend.
void WiFiNetwork::fn_802650EC() {
    for (s32 i = 0; i < 30; i++) {
        fn_80265074(i);
    }
}

// TODO Callback counting a friend list change.
void fn_80265138(s32, s32, WiFiNetwork *self) {
    self->fn_80267690();
    self->_3388++;
}

// TODO Second callback of fn_8031F484; counts a change like fn_80265138.
void fn_80265174(s32, WiFiNetwork *self) {
    self->fn_80267690();
    self->_3388++;
}

// TODO Handler of WIFINETWORK_RUNSTATE_LOGIN_HOOK.
void WiFiNetwork::fn_802651B0() {
    fn_80267374();
    if (_3C50 && _3C58) {
        _3C58 = 0;
    }
    _33A8 = 0;
    _3C7C = 0;
    _3C80 = 0;
    fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
}

// TODO Clears the list of connection ids.
void fn_80265218() {
    for (s32 i = 0; i < 32; i++) {
        lbl_80503BF8[i] = -1;
    }
}

// TODO Adds a connection id to the list.
void fn_802652A4(s32 idx) {
    for (s32 i = 0; i < 32; i++) {
        if (lbl_80503BF8[i] < 0) {
            lbl_80503BF8[i] = idx;
            return;
        }
    }
}

// TODO Removes a connection id from the list and packs the rest.
void fn_802652E8(s32 idx) {
    s32 n;
    s32 i;
    for (i = 0; i < 32; i++) {
        if (idx == lbl_80503BF8[i]) {
            lbl_80503BF8[i] = -1;
            break;
        }
    }
    n = 0;
    for (s32 j = 0; j < 32; j++) {
        if (lbl_80503BF8[j] >= 0) {
            lbl_80503BF8[n++] = lbl_80503BF8[j];
        }
    }
    for (; n < 32; n++) {
        lbl_80503BF8[n] = -1;
    }
}

// TODO Copies up to max connection ids of the other players.
s32 WiFiNetwork::fn_80265488(s32 *out, s32 max) {
    u32 mask = fn_80266660();
    s32 n = 0;
    u8 own = fn_8026703C();
    for (s32 i = 0; i < 32; i++) {
        if (own != i && (mask & (1 << i))) {
            n++;
        }
    }
    if (n > max) {
        n = max;
    }
    memcpy(out, lbl_80503BF8, n * 4);
    return n;
}

// TODO Callback for a closed connection, handled according to the matchmaking mode.
void fn_8026560C(s32 result, s32, s32 b, u8 idx, s32 id, WiFiNetwork *self) {
    if (id >= 0) {
        fn_802652E8(id);
    }
    if (result == 0) {
        switch (self->_3C84) {
            case 1:
                self->_6520[idx]._4 = 0;
                if (self->fn_80267098() <= 1) {
                    self->fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
                }
                break;
            case 2:
                if (b) {
                    self->fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
                } else {
                    self->fn_80264348(idx);
                    self->_3C5C = 1;
                    fn_803243B0();
                }
                break;
            case 3:
                if (b) {
                    fn_80322978();
                    self->fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
                }
                break;
        }
    }
}

// TODO Builds the own status record, with its checksum, and sends it.
void WiFiNetwork::fn_80265714() {
    _1C50._00 = fn_803338A4(fn_802674DC());
    _1C50._36 = fn_8025E370();
    _1C50._34 = 0;
    _1C50._34 = fn_8025E78C(&_1C50, sizeof(Unk80264F20));
    DCFlushRange(&_1C50, sizeof(Unk80264F20));
    fn_8031F2E4(&_1C50, sizeof(Unk80264F20));
}

// TODO Handler of WIFINETWORK_RUNSTATE_ONLINE_HOOK.
void WiFiNetwork::fn_80265784() {
    _3C70 = 0;
    fn_80267378();
    fn_80265714();
    _3C78 = 0;
    fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE);
}

// TODO Handler of WIFINETWORK_RUNSTATE_ONLINE.
void WiFiNetwork::fn_802657D8() {
    _3C84 = 0;
    fn_802643AC();
    fn_80265218();
    if (_3C50 == 0) {
        _3C58 = 1;
    }
    if (_3C58) {
        _3C58 = 0;
        fn_80264DC8();
        fn_8026461C(WIFINETWORK_RUNSTATE_DISCONNECT_HOOK);
        return;
    }
    if (_66A0 == 0 && _3398) {
        _3398 = 0;
        fn_803223C4(0, (void *)fn_80264ED8, this, (void *)fn_80264F20, this, (void *)fn_80265138, this);
    }
    if (_3C5C) {
        _3C5C = 0;
    }
    if (fn_80322E74() == 6) {
        _3C6C = 1;
    }
    if (_3C6C) {
        _3390 = 0;
        _3C6C = 0;
        _3C70 = 1;
        fn_80264DC8();
        fn_8026461C(WIFINETWORK_RUNSTATE_LOGIN);
        return;
    }
    if (_3C60) {
        fn_8026461C(WIFINETWORK_RUNSTATE_PEER);
        _3C60 = 0;
        return;
    }
    if (_3C64) {
        fn_8026461C(WIFINETWORK_RUNSTATE_SERVER);
        _3C64 = 0;
        return;
    }
    if (_3C68) {
        fn_8026461C(WIFINETWORK_RUNSTATE_CLIENT);
        _3C68 = 0;
        return;
    }
    if (_66A0 == 0) {
        fn_80321FEC();
    }
}

// TODO Builds the matchmaking filter for version a and region b, then requests a peer match.
void WiFiNetwork::fn_80265978(u32 a, char *b, s32 c) {
    char buf[0x80];
    s32 n;
    _6540[0]._4 = 2;
    _6540[1]._4 = a;
    _6540[2]._4 = (s32)b;
    _6540[3]._4 = c;
    sprintf(buf, "ver = %d and reg = %d", 2, a);
    if (fn_80266538() <= 30) {
        n = 0;
    } else {
        n = fn_80266538() <= 60 ? 1 : 2;
    }
    strcat(buf, " and ");
    fn_8025BBFC(buf + strlen(buf), b, n);
    if (c) {
        sprintf(buf + strlen(buf), " and dis = %d", c);
    }
    fn_80265A80(2, buf, 0, 0);
}

// TODO Requests a peer match; checks the player counts and copies the filter string.
s32 WiFiNetwork::fn_80265A80(u8 a, char *str, s32 c, u8 d) {
    if (_3C58) {
        return -2;
    }
    if (_3C60 || _3C64 || _3C68) {
        return -2;
    }
    switch (mRunState) {
        case WIFINETWORK_RUNSTATE_ONLINE_HOOK:
        case WIFINETWORK_RUNSTATE_ONLINE:      break;
        default:                               return -3;
    }
    if (a > 2 || a < 2 || d > 2) {
        return -4;
    }
    if (c) {
        if (d >= a || d < 2) {
            return -5;
        }
    } else if (d) {
        return -1;
    }
    _3C88 = a;
    _3C89 = d;
    _3C8C = c;
    if (str) {
        if (strlen(str) + 1 >= sizeof(_3C90)) {
            _3C90[0] = 0;
        } else {
            strcpy(_3C90, str);
        }
    } else {
        _3C90[0] = 0;
    }
    _3C60 = 1;
    return 0;
}

// TODO Requests to host a match for a players.
s32 WiFiNetwork::fn_80265BB0(u8 a) {
    if (_3C58) {
        return -2;
    }
    if (_3C60 || _3C64 || _3C68) {
        return -2;
    }
    if (a <= 1 || a > 2) {
        return -1;
    }
    _3C88 = a;
    _3C64 = 1;
    return 0;
}

// TODO Requests to join the match hosted by friend idx.
s32 WiFiNetwork::fn_80265C1C(s32 idx) {
    u8 x9;
    u8 x8;
    if (_3C58) {
        return -2;
    }
    if (_3C60 || _3C64 || _3C68) {
        return -2;
    }
    switch (mRunState) {
        case WIFINETWORK_RUNSTATE_ONLINE_HOOK:
        case WIFINETWORK_RUNSTATE_ONLINE:      break;
        default:                               return -3;
    }
    if (idx >= 30) {
        return -4;
    }
    if (fn_803331D0(fn_802674E4(idx)) == 0) {
        return -5;
    }
    if (fn_8031F198(fn_802674E4(idx), &x9, &x8, 0) != 6) {
        return -6;
    }
    if (x8 >= x9) {
        return -7;
    }
    _3D10 = idx;
    _3C68 = 1;
    return 0;
}

// TODO Cancels the matchmaking in progress.
s32 WiFiNetwork::fn_80265D2C() {
    if (_66A0) {
        fn_80263D0C();
        fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
        return 0;
    }
    switch (mRunState) {
        case WIFINETWORK_RUNSTATE_MATCHING:
            if (fn_803243B0() == 0) {
                return -1;
            }
            break;
        case WIFINETWORK_RUNSTATE_MATCHED_HOOK:
        case WIFINETWORK_RUNSTATE_MATCHED:
            switch (fn_80322978()) {
                case 0: break;
                case 1:
                    fn_803243B0();
                    fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
                    break;
                default:
                    fn_803243B0();
                    fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
                    break;
            }
            break;
    }
    return 0;
}

// TODO Cancels the pending match requests.
s32 WiFiNetwork::fn_80265DEC() {
    _3C60 = 0;
    _3C64 = 0;
    _3C68 = 0;
    if (_3C5C) {
        return -1;
    }
    _3C60 = 0;
    _3C64 = 0;
    _3C68 = 0;
    _3C5C = 1;
    return 0;
}

// TODO Checks the key against the known ones and asks for a new login when it is unknown.
s32 WiFiNetwork::fn_80265E2C(void *key) {
    if (_3C58) {
        return -2;
    }
    if (_3C60 || _3C64 || _3C68) {
        return -2;
    }
    switch (mRunState) {
        case WIFINETWORK_RUNSTATE_ONLINE_HOOK:
        case WIFINETWORK_RUNSTATE_ONLINE:      break;
        default:                               return -3;
    }
    fn_8025E86C();
    if (fn_80264938(key)) {
        return 0;
    }
    _3390 = 0;
    _3C6C = 1;
    return 0;
}

// TODO Callback for a completed send to player idx; frees the packet.
void fn_80265EF0(u32, u8 idx) {
    WiFiNetwork *self = fn_8025E31C(fn_8025DFD0());
    u32 v = self->_3D1C[idx];
    s32 n = 0;
    if (v) {
        if (self->_3D1C[0] == v) {
            n = 1;
        }
        if (self->_3D1C[1] == v) {
            n++;
        }
        if (n <= 1) {
            fn_8025EDC8(self, v);
        }
        self->_3D1C[idx] = 0;
    }
}

// TODO Callback for data received from player idx.
void fn_80265F6C(u8 idx, u32 a, u32 b) {
    WiFiNetwork *self = fn_8025E31C(fn_8025DFD0());
    if (idx < 2) {
        Unk80263D28 *entry = &self->_6520[idx];
        entry->_C = fn_8025E370();
        if (entry->_C == 0) {
            entry->_C = 1;
        }
    }
    fn_8025EC68(self, a, b, idx, 1);
}

// TODO Same as fn_80265EF0, for the local connection library.
void fn_80265FF0(u32 a, u32 idx) {
    fn_80265EF0(a, idx);
}

// TODO Same as fn_80265F6C, for the local connection library.
void fn_80265FF8(u32 idx, u32 a, u32 b) {
    fn_80265F6C(idx, a, b);
}

// TODO Callback storing a value reported for player idx, with the time.
void fn_80266000(s32 v, u8 idx) {
    WiFiNetwork *self = fn_8025E31C(fn_8025DFD0());
    if (idx < 2) {
        Unk80263D28 *entry = &self->_6520[idx];
        entry->_8 = v;
        s32 t = fn_8025E370();
        entry->_C = t;
        if (t == 0) {
            entry->_C = 1;
        }
    }
}

void fn_802661D0(s32 result, s32 a, s32 b, s32 c, s32 idx, WiFiNetwork *self);
void fn_80266224(s32 idx);

// TODO Handler of WIFINETWORK_RUNSTATE_SERVER.
void WiFiNetwork::fn_80266068() {
    if (_3C5C) {
        fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE);
        _3C5C = 0;
        return;
    }
    _3C84 = 2;
    _33A0 = 0;
    _33A4 = 0;
    fn_80265218();
    if (fn_803225B8(_3C88, (void *)fn_802661D0, this, (void *)fn_80266224, this) == 0) {
        _3C84 = 0;
        fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
    } else {
        fn_8026461C(WIFINETWORK_RUNSTATE_MATCHING);
    }
}

// TODO Handler of WIFINETWORK_RUNSTATE_CLIENT.
void WiFiNetwork::fn_80266118() {
    if (_3C5C) {
        fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE);
        _3C5C = 0;
        return;
    }
    _3C84 = 3;
    _33A0 = 0;
    _33A4 = 0;
    fn_80265218();
    fn_802652A4(_3D10);
    if (fn_803226C4(_3D10, (void *)fn_802661D0, this, (void *)fn_80266224, this) == 0) {
        _3C84 = 0;
        fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
    } else {
        fn_8026461C(WIFINETWORK_RUNSTATE_MATCHING);
    }
}

// TODO Callback of the host and join matchmaking.
void fn_802661D0(s32 result, s32 a, s32 b, s32 c, s32 idx, WiFiNetwork *self) {
    if (result) {
        return;
    }
    if (a == 0) {
        self->_33A0 = 1;
        if (idx >= 0) {
            fn_802652A4(idx);
        }
    } else {
        if (b || c) {
            self->_33A4 = 1;
        }
        if (idx >= 0) {
            fn_802652E8(idx);
        }
    }
}

// TODO Callback for a new connection during the host and join matchmaking.
void fn_80266224(s32 idx) {
    if (idx >= 0) {
        fn_802652A4(idx);
    }
}

// TODO Matchmaking callback of the local connection library.
void fn_80266234(s32 result) {
    WiFiNetwork *self = fn_8025E31C(fn_8025DFD0());
    if (result == 0) {
        self->_33A0 = 1;
    }
}

void fn_80266464(s32 result, s32 a, WiFiNetwork *self);
s32 fn_8026648C(void *a, WiFiNetwork *self);

// TODO Handler of WIFINETWORK_RUNSTATE_PEER.
void WiFiNetwork::fn_80266274() {
    if (_3C5C) {
        fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE);
        _3C5C = 0;
        return;
    }
    _3C84 = 1;
    _33A0 = 0;
    _33A4 = 0;
    fn_80265218();
    if (_66A0) {
        fn_80263CBC();
        if (fn_8031DFFC(_3C88, (void *)fn_80266234) == 0) {
            _3C84 = 0;
            fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
        } else {
            fn_8026461C(WIFINETWORK_RUNSTATE_MATCHING);
        }
        return;
    }
    _6560[0]._4 = _6540[0]._4;
    _6560[1]._4 = _6540[1]._4;
    _6560[2]._4 = _6540[2]._4;
    _6560[3]._4 = _6540[3]._4;
    _6560[0]._0 = fn_80324440(_6560[0]._0, "ver", &_6560[0]._4);
    _6560[1]._0 = fn_80324440(_6560[1]._0, "reg", &_6560[1]._4);
    _6560[2]._0 = fn_80324440(_6560[2]._0, "win", &_6560[2]._4);
    _6560[3]._0 = fn_80324440(_6560[3]._0, "dis", &_6560[3]._4);
    u8 buf[8];
    memset(buf, 0, sizeof(buf));
    if (_3C8C && _3C89 < _3C88) {
        buf[0] = 1;
        buf[1] = _3C89;
        *(s32 *)(buf + 4) = _3C8C;
    } else {
        buf[0] = 0;
    }
    fn_8032488C(0, buf, sizeof(buf));
    if (fn_803224B0(_3C88,
                    ((s8 *)_3C90)[0] ? _3C90 : (char *)NULL,
                    (void *)fn_80266464,
                    this,
                    (void *)fn_8026648C,
                    this) == 0) {
        _3C84 = 0;
        fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
    } else {
        fn_8026461C(WIFINETWORK_RUNSTATE_MATCHING);
    }
}

// TODO Callback of the peer matchmaking.
void fn_80266464(s32 result, s32 a, WiFiNetwork *self) {
    if (result) {
        return;
    }
    if (a == 0) {
        self->_33A0 = 1;
    } else {
        self->_33A4 = 1;
    }
}

// TODO Accepts a peer whose "ver" and "reg" match ours.
s32 fn_8026648C(void *a, WiFiNetwork *self) {
    s32 ver = fn_80324800(a, "ver", -1);
    s32 reg = fn_80324800(a, "reg", -1);
    fn_80324800(a, "win", -1);
    fn_80324800(a, "dis", -1);
    if (ver != self->_6560[0]._4) {
        return 0;
    }
    return reg == self->_6560[1]._4;
}

// TODO Elapsed matchmaking time divided by 10.
u32 WiFiNetwork::fn_80266538() {
    return (u32)_3C80 / 10;
}

// TODO Handler of WIFINETWORK_RUNSTATE_MATCHING.
void WiFiNetwork::fn_80266550() {
    if (_66A0) {
        fn_8031D528();
    } else {
        fn_80321FEC();
    }
    switch (_3C40) {
        case 0:
            _3C7C = fn_8025E370();
            _3C40++;
            break;
        case 1: break;
    }
    _3C80 = fn_8025E370() - _3C7C;
    if (_33A0) {
        _33A0 = 0;
        fn_8026461C(WIFINETWORK_RUNSTATE_MATCHED_HOOK);
    }
    if (_33A4) {
        _33A4 = 0;
        fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
    }
    if (_3C58) {
        fn_80265DEC();
    }
    if (_3C84 == 3 && (u32)_3C80 >= 450) {
        fn_80265DEC();
    }
    if (_3C5C) {
        _3C5C = 0;
        fn_80265D2C();
    }
}

// TODO Bit mask of the connected players.
u32 WiFiNetwork::fn_80266660() {
    u32 mask;
    if (_66A0) {
        mask = 0;
        s32 n = fn_80267098();
        for (s32 i = 0; i < n; i++) {
            mask |= 1 << i;
        }
    } else {
        mask = fn_80322C58();
    }
    return mask;
}

// TODO Handler of WIFINETWORK_RUNSTATE_MATCHED_HOOK.
void WiFiNetwork::fn_80266784() {
    u32 t = fn_8025E370();
    u32 mask = fn_80266660();
    u8 own = fn_8026703C();
    for (u8 i = 0; i < 2; i++) {
        Unk80263D28 *entry = &_6520[i];
        if (own == i) {
            entry->_0 = 1;
            entry->_4 = 1;
            entry->_8 = 0;
            entry->_C = t;
        } else if (mask & (1 << i)) {
            entry->_0 = 0;
            entry->_4 = 1;
            entry->_8 = 0;
            entry->_C = t;
        } else {
            entry->_0 = 0;
            entry->_4 = 0;
            entry->_8 = 0;
            entry->_C = 0;
        }
    }
    _651C = fn_8025E370() - own * 10;
    fn_8026461C(WIFINETWORK_RUNSTATE_MATCHED);
}

// TODO Handler of WIFINETWORK_RUNSTATE_MATCHED.
void WiFiNetwork::fn_802668B0() {
    if (_66A0) {
        fn_8031D528();
    } else {
        fn_80321FEC();
        u32 t = fn_8025E370();
        if (t - _651C >= 50) {
            for (u8 i = 0; i < 2; i++) {
                if (_6520[i]._0) {
                    _6520[i]._C = t;
                } else {
                    if (_6520[i]._4 && t - _6520[i]._C > 300) {
                        _6520[i]._4 = 0;
                        fn_80322A70(i);
                    }
                    if (_6520[i]._4) {
                        fn_80330EEC(i);
                    }
                }
            }
            _651C = t;
        }
    }
    fn_8025F934(this, 1);
    for (s32 k = 0; k < 8; k++) {
        if (fn_80266A7C()) {
            break;
        }
        fn_80321FEC();
    }
    if (_66A0) {
        fn_8031D528();
    } else {
        fn_80321FEC();
    }
    u32 now = fn_8025E370();
    for (u8 i = 0; i < 2; i++) {
        Unk80263D28 *entry = &_6520[i];
        if (entry->_0 == 0 && entry->_4) {
            if (now - _6580[i] >= 50) {
                u16 msg[3];
                msg[0] = 14;
                msg[1] = 6;
                msg[2] = 0;
                fn_80267100(msg, sizeof(msg), i);
                _6580[i] = now;
            }
        }
    }
    if (_3C58) {
        fn_80265DEC();
    }
    if (_3C5C) {
        fn_80265D2C();
    }
}

// TODO Hands the next pending packet to the network library.
s32 WiFiNetwork::fn_80266A7C() {
    u16 xa;
    u16 x8;
    if (fn_8025EF54(this) == 0) {
        return -1;
    }
    u32 h = fn_8025EFA4(this, &xa, &x8);
    if (h == 0) {
        return -1;
    }
    if (x8 >= 2) {
        return -1;
    }
    if (_3D1C[x8]) {
        return -1;
    }
    _3D1C[x8] = h;
    s32 r;
    if (_66A0) {
        r = fn_8031E0B0(x8, h, xa, 0);
    } else {
        r = fn_80330D88(x8, h, xa);
    }
    if (r == 0) {
        _3D1C[x8] = 0;
        return -1;
    }
    _6580[x8] = fn_8025E370();
    fn_8025F00C(this);
    return 0;
}

// TODO Handler of WIFINETWORK_RUNSTATE_DISCONNECT_HOOK.
void WiFiNetwork::fn_80266B80() {
    fn_80264300();
    _3C60 = 0;
    _3C64 = 0;
    _3C68 = 0;
    fn_80264684();
    fn_8025BEB4();
    fn_80267324();
    fn_8026461C(WIFINETWORK_RUNSTATE_DISCONNECT);
}

// TODO Handler of WIFINETWORK_RUNSTATE_DISCONNECT.
void WiFiNetwork::fn_80266BDC() {
    _3C58 = 0;
    fn_8026461C(WIFINETWORK_RUNSTATE_INIT);
}

// TODO Handler of WIFINETWORK_RUNSTATE_ERROR.
void WiFiNetwork::fn_80266BEC() {
    s32 code;
    s32 type;
    _3C70 = 0;
    if (_3C54 == 0) {
        fn_8031C4A4(&code, &type);
        switch ((u32)type) {
            case 0: fn_8026461C(WIFINETWORK_RUNSTATE_DISCONNECT_HOOK); break;
            case 1:
                fn_80267534();
                fn_8026461C(WIFINETWORK_RUNSTATE_ONLINE_HOOK);
                break;
            case 3:
            case 6:
                fn_802643AC();
                fn_80265218();
                fn_80264DC8();
                fn_80264454();
                fn_8026461C(WIFINETWORK_RUNSTATE_DISCONNECT_HOOK);
                break;
            case 7:  fn_8026461C(WIFINETWORK_RUNSTATE_FATAL); break;
            default: fn_8026461C(WIFINETWORK_RUNSTATE_FATAL); break;
        }
        fn_8031C550();
        fn_80266FBC();
    }
}

// TODO Runs one frame of the state machine; returns whether the run state changed.
s32 WiFiNetwork::fn_80266CE0() {
    u8 changed = FALSE;
    fn_8025F4E0();
    switch ((u32)mRunState) {
        case WIFINETWORK_RUNSTATE_INIT:            fn_80264718(); break;
        case WIFINETWORK_RUNSTATE_START:           fn_80264764(); break;
        case WIFINETWORK_RUNSTATE_CONNECT:         fn_80264790(); break;
        case WIFINETWORK_RUNSTATE_CONNECT_HOOK:    fn_802648B4(); break;
        case WIFINETWORK_RUNSTATE_LOGIN:           fn_80264A70(); break;
        case WIFINETWORK_RUNSTATE_LOGIN_HOOK:      fn_802651B0(); break;
        case WIFINETWORK_RUNSTATE_ONLINE_HOOK:     fn_80265784(); break;
        case WIFINETWORK_RUNSTATE_ONLINE:          fn_802657D8(); break;
        case WIFINETWORK_RUNSTATE_CLIENT:          fn_80266118(); break;
        case WIFINETWORK_RUNSTATE_SERVER:          fn_80266068(); break;
        case WIFINETWORK_RUNSTATE_PEER:            fn_80266274(); break;
        case WIFINETWORK_RUNSTATE_MATCHING:        fn_80266550(); break;
        case WIFINETWORK_RUNSTATE_MATCHED_HOOK:    fn_80266784(); break;
        case WIFINETWORK_RUNSTATE_MATCHED:         fn_802668B0(); break;
        case WIFINETWORK_RUNSTATE_DISCONNECT_HOOK: fn_80266B80(); break;
        case WIFINETWORK_RUNSTATE_DISCONNECT:      fn_80266BDC(); break;
        case WIFINETWORK_RUNSTATE_ERROR:           fn_80266BEC(); break;
    }
    if (_3C78 && fn_80264504()) {
        if (_3C78 <= 1) {
            fn_80265714();
            _3C78 = 0;
        } else {
            _3C78--;
        }
    }
    if (mRunState != WIFINETWORK_RUNSTATE_ERROR && fn_80266F44()) {
        _3C44 = mRunState;
        _3C48 = _3C40;
        _3C54 = 1;
        fn_8026461C(WIFINETWORK_RUNSTATE_ERROR);
    }
    if (mPrevRunState != mRunState) {
        changed = TRUE;
        mPrevRunState = mRunState;
        _3388++;
    }
    if (fn_80264504()) {
        fn_8025CACC();
    }
    return changed;
}

// TODO Takes the pending error flag; returns -1 when none, otherwise whether the error is light.
s32 WiFiNetwork::fn_80266EE8() {
    s32 code;
    s32 type;
    if (_3C54 == 0) {
        return -1;
    }
    _3C54 = 0;
    fn_8031C4A4(&code, &type);
    return type == 1;
}

// TODO Sets the error code reported by fn_802640DC.
void WiFiNetwork::fn_80266F3C(u32 v) {
    _3D18 = v;
}

// TODO Current error, 5 when an error code was set by fn_80266F3C.
s32 WiFiNetwork::fn_80266F44() {
    s32 code;
    if (_3D18) {
        return 5;
    }
    return fn_8031C48C(&code);
}

// TODO Current error code as a positive number.
s32 WiFiNetwork::fn_80266F7C() {
    s32 code;
    if (_3D18) {
        return -_3D18;
    }
    fn_8031C48C(&code);
    return -code;
}

// TODO Clears the error code set by fn_80266F3C.
void WiFiNetwork::fn_80266FBC() {
    _3D18 = 0;
}

// TODO Clears the DWC error and the error code.
void WiFiNetwork::fn_80266FC8() {
    fn_8031C550();
    fn_80266FBC();
}

// TODO Whether the current error is fatal.
s32 WiFiNetwork::fn_80266FFC() {
    s32 code;
    s32 type;
    fn_8031C4A4(&code, &type);
    return type == 7;
}

// TODO Change counter, incremented on every state change and friend update.
s32 WiFiNetwork::fn_80267034() {
    return _3388;
}

// TODO Own connection index.
u32 WiFiNetwork::fn_8026703C() {
    if (_66A0) {
        if (fn_802645C4()) {
            return (u16)fn_8031E08C();
        }
        return 0;
    }
    return (u8)fn_80322BF8();
}

// TODO Number of connected players.
s32 WiFiNetwork::fn_80267098() {
    if (_66A0) {
        if (lbl_8063FA10 && fn_802645C4()) {
            return 2;
        }
        return 1;
    }
    return fn_80322B9C();
}

// TODO Largest packet size.
u16 WiFiNetwork::fn_802670F8() {
    return 1020;
}

// TODO Sends data to player idx; returns the size sent or an error.
s32 WiFiNetwork::fn_80267100(void *data, u32 size, u8 idx) {
    if (fn_802645C4() == 0) {
        return -1;
    }
    if (size > fn_802670F8()) {
        return -1;
    }
    if (fn_8026725C(idx) == 0) {
        return -1;
    }
    s32 r = fn_8025ECF8(this, data, size, 1, idx);
    if (r < 0) {
        size = r;
    }
    return size;
}

// TODO Closes the connection with player idx.
s32 WiFiNetwork::fn_802671E4(u32 idx) {
    if (fn_8026725C(idx) == 0) {
        return -1;
    }
    if (_66A0) {
        _3C58 = 1;
        return 0;
    }
    return fn_80322A70(idx);
}

// TODO Whether player idx is connected.
s32 WiFiNetwork::fn_8026725C(s32 idx) {
    if (fn_802645C4() == 0) {
        return 0;
    }
    if (_66A0) {
        return idx < _3C88;
    }
    return fn_80322DC8(idx);
}

// TODO Always returns -1.
s32 WiFiNetwork::fn_802672E0() {
    return -1;
}

// TODO Clears the send queue, the friend data and the known keys.
void WiFiNetwork::fn_802672E8() {
    fn_8025EE18(this);
    fn_802650EC();
    fn_802649C8();
}

// TODO Releases the data set by fn_8025CAA8 and clears the send queue and the friend data.
void WiFiNetwork::fn_80267324() {
    if (_66A4) {
        fn_8025CC38();
        _66A4 = 0;
    }
    fn_8025EE18(this);
    fn_802650EC();
}

// TODO Empty.
void fn_80267374() {}

// TODO Clears the send queue and the DWC status data.
void WiFiNetwork::fn_80267378() {
    fn_8025EE18(this);
    if (_66A0 == 0) {
        fn_8032432C();
    }
}

// TODO Empty.
void fn_802673B4() {}

// TODO Empty.
void WiFiNetwork::fn_802673B8() {}

// TODO Sends a request with a value between 0 and 6 while online.
s32 WiFiNetwork::fn_802673BC(s32 a, s32 b) {
    if (b < 0 || b > 6) {
        return -1;
    }
    if (a == 0) {
        return -1;
    }
    if (fn_80264504() == 0) {
        return -3;
    }
    if (fn_8025CC48() == 0) {
        return -2;
    }
    fn_8025CCA4(a, b);
    return 0;
}

// TODO Reads the answer to the request sent by fn_802673BC.
s32 WiFiNetwork::fn_8026745C(s32 *out) {
    if (fn_8025CC48() == 0) {
        return 0;
    }
    s32 r = fn_8025CC94();
    if (r >= 0) {
        *out = r;
        r = 1;
    }
    return r;
}
