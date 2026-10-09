#include "gs/GSrender.hpp"

#include "common.hpp"

struct _UnkStruct8023B64C_1 {
    /* 0x0 */ u16 _0;
    /* 0x2 */ u16 _2;
    /* 0x4 */ GXDrawSyncCallback mCallback;
};
static _UnkStruct8023B64C_1 lbl_804967A0[4];

static u16 sNextToken;
static u16 lbl_8063F740;
static u16 lbl_8063F742;
static u16 lbl_8063F744;
static u16 sMaxToken;
static u16 lbl_8063F748;
static u8 lbl_8063F74A;

static void fn_8023B64C(u16 token) {
    if (!GSrender::sInstance) {
        return;
    }

    u8 _unk1 = lbl_8063F74A;
    for (u8 i = 0; i < _unk1; i++) {
        _UnkStruct8023B64C_1 *_unk2 = &lbl_804967A0[i];
        if (_unk2->_0 <= token && _unk2->_2 >= token) {
            _unk2->mCallback(token);
            return;
        }
    }

    lbl_8063F744 = token;
}
void GSrender::fn_8023B6B0() {
    lbl_8063F744 = lbl_8063F740;
}

void GSrender::fn_8023B6BC() {
    if (lbl_8063F748 != 0xFFFF) {
        lbl_8063F748++;
    } else {
        lbl_8063F748 = 1;
    }

    lbl_8063F740 = sNextToken;
    lbl_8063F742 = sNextToken + 0x800;

    if (lbl_8063F742 >= sMaxToken) {
        lbl_8063F742 -= sMaxToken;
    }
}

void GSrender::fn_8023B704() {
    lbl_8063F744 = 0;
    sNextToken = 1;
    sMaxToken = 0xE000;
    lbl_8063F748 = 0;

    fn_8023B6BC();

    lbl_8063F74A = 0;

    for (u32 i = 0; i < 4; i++) {
        lbl_804967A0[i].mCallback = NULL;
    }

    GXSetDrawSyncCallback(fn_8023B64C);
}

static bool fn_8023B774(u16 token, u16 end) {
    if (sNextToken > end) {
        if (token <= end || token > sNextToken) {
            return true;
        }
    } else {
        if (token > sNextToken && token <= end) {
            return true;
        }
    }
    return false;
}

static bool fn_8023B7B8(u32 arg0) {
    u16 token = arg0 & 0xFFFF;
    u16 _unk2 = arg0 >> 16;

    if (lbl_8063F748 < _unk2) {
        if (0xFFFF - _unk2 + lbl_8063F748 > 1) {
            return true;
        }
    } else {
        if (lbl_8063F748 - _unk2 > 1) {
            return true;
        }
    }

    if (fn_8023B774(token, lbl_8063F744)) {
        return true;
    }

    u16 currToken = GXReadDrawSync();
    if (currToken >= sMaxToken) {
        return false;
    }

    return fn_8023B774(token, currToken);
}

bool GSrender::fn_8023B864(u32 arg0) {
    if (!arg0 || _1718) {
        return true;
    }
    return fn_8023B7B8(arg0);
}

void GSrender::fn_8023B88C(u32 arg0) {
    if (!arg0 || _1718) {
        return;
    }

    u32 _unk1;
    fn_802311AC(&_unk1);

    GXBool readIdle, dummy;
    while (!fn_8023B7B8(arg0)) {
        fn_802311BC(&_unk1);

        if (_1718 || _1719) {
            break;
        }

        GXGetGPStatus(&dummy, &dummy, &readIdle, &dummy, &dummy);

        if (readIdle == GX_TRUE) {
            break;
        }
    }

    fn_8023125C(&_unk1);
}

u32 GSrender::fn_8023B948(void *arg0) {
    if (_1718) {
        return 0;
    }

    u16 _unk1 = lbl_8063F742;
    u16 nextToken = sNextToken;

    if (nextToken == _unk1) {
        return (lbl_8063F748 << 16) | _unk1;
    }

    GXSetDrawSync(nextToken);

    sNextToken++;
    if (sNextToken >= sMaxToken) {
        sNextToken = 1;
    }

    return (lbl_8063F748 << 16) | nextToken;
}
