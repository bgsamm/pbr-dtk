#include ".unsorted/8038F424.hpp"

extern "C" {

void *fn_8039A068(u32 size) {
    return MEMAllocFromAllocator(lbl_8063E80C, size);
}

void fn_8039A074(void *p) {
    MEMFreeToAllocator(lbl_8063E80C, p);
}

void fn_8039A22C(void) {
    OSRegisterVersion(lbl_8063E808);
    fn_8039B474(lbl_806405A0);
}

s32 fn_8039A258(u32 a) {
    fn_8039BD7C(lbl_806405A0, a);
    u8 *p = lbl_806405A0;
    if (*(s32 *)(p + 0x10) != 0x12) {
        return -1;
    }
    return *(s32 *)(p + 0xb0);
}

s32 fn_8039A3C8(void) {
    u8 *p = lbl_806405A0;
    if (*(s32 *)(p + 0x10) != 0x12) {
        return -1;
    }
    return *(s32 *)(p + 0xb0);
}

void fn_8039A3E8(u32 a) {
    fn_803A2E70(lbl_806405A0, a);
}

void fn_8039A3F4(void) {
    fn_803A3078(lbl_806405A0);
}

u8 fn_8039A3FC(void) {
    return *(u8 *)(lbl_806405A0 + 0x88);
}

void fn_8039A4EC(void) {
    fn_803A357C(lbl_806405A0);
    MEMDestroyFrmHeap(*(void **)(lbl_8063CEC8 + 4));
}

u8 *fn_8039B238(u8 *p, s32 del) {
    if (p && del > 0) {
        ::operator delete(p);
    }
    return p;
}

void fn_8039B278(u8 *p, u32 v) {
    *(u32 *)(p + 0x4) = v;
}

void fn_8039B280(u8 *p, u8 v) {
    *(u8 *)(p + 0x24) = v;
}

void fn_8039B288(u8 *p, u32 v) {
    *(u32 *)(p + 0x24) = v;
}

void fn_8039DE00(void *a, void *b) {
    fn_803A57D4(OSGetAlarmUserData(a));
}

void fn_8039DEEC(s32 a, s32 b) {
    if (a == 1) {
        lbl_806405A0[0x8a] = 1;
    }
    void (*fp)(s32, s32) = *(void (**)(s32, s32))(lbl_806405A0 + 0x1bc);
    if (fp) {
        fp(a, b);
    }
}

u32 fn_803A3070(u8 *p) {
    return *(u32 *)(p + 0x2c);
}

void fn_803A36A0(void) {}

void fn_803A36A4(void) {}

void fn_803A36A8(void) {}

void fn_803A36AC(void) {}

void fn_803A36B0(void) {}

void fn_803A36B4(void) {}

void fn_803A36B8(u8 *p) {
    *(u32 *)(p + 0x20) = 0;
    *(u8 **)(p + 0x0) = lbl_80472EF0;
    *(u32 *)(p + 0x24) = 0;
}

u8 *fn_803A36D4(u8 *p, s32 del) {
    if (p && del > 0) {
        ::operator delete(p);
    }
    return p;
}

void fn_803A37C4(u8 *p, s32 m, f32 a, f32 b, f32 c) {
    *(s32 *)(p + 0x18) = m;
    *(f32 *)(p + 0x4) = a;
    *(f32 *)(p + 0x8) = b;
    *(f32 *)(p + 0x10) = c;
    *(u32 *)(p + 0x14) = 0;
    p[0x1c] = 0;
    *(f32 *)(p + 0xc) = (m == 1) ? (f64)a : (f64)b;
}

void fn_803A37FC(u8 *p) {
    f32 f;
    if (*(s32 *)(p + 0x18) == 1) {
        f = *(f32 *)(p + 4);
    } else {
        f = *(f32 *)(p + 8);
    }
    *(f32 *)(p + 0xc) = f;
}

s32 fn_803A3D2C(void) {
    return 1;
}

u8 fn_803A3D34(u8 *p, s32 i) {
    return p[i + 4];
}

void fn_803A3D40(void) {}

void fn_803A3D44(u8 *p) {
    VObj *o = *(VObj **)(p + 4);
    if (o) {
        o->v00();
    }
}

u32 fn_803A3D64(u8 *p) {
    return *(u32 *)(p + 0x20);
}

void fn_803A3D6C(u8 *p, s32 i, u8 v) {
    p[i + 4] = v;
}

void fn_803A3D78(void) {}

void fn_803A3D7C(void) {}

void fn_803A3E3C(u8 *p) {
    for (u32 i = 0; i < *(u16 *)(p + 0x10); i++) {
        (*(VObj3 **)(fn_80362AEC(p + 8, i) + 4))->v01();
    }
}

void fn_803A3EA4(u8 *p) {
    p[0x18] = 0;
    p[0x4] = 0;
    p[0x5] = 0;
    p[0x6] = 0;
    p[0x7] = 0;
    p[0x8] = 0;
    p[0x9] = 0;
    p[0xa] = 0;
    p[0xb] = 0;
}

void fn_803A3F94(u8 *p, u32 v) {
    *(u32 *)(p + 0x28) = v;
}

u32 fn_803A3F9C(u8 *p, u32 x) {
    return *(u32 *)(fn_80362AEC(p + 8, (u16)x) + 4);
}

u8 fn_803A416C(u8 *p) {
    return *(u8 *)(p + 0x24);
}

void fn_803A4174(u8 *p, u32 m, f32 *v) {
    if (m & *(u32 *)(p + 0x1c)) {
        *(f32 *)(p + 0xc) = v[0];
        *(f32 *)(p + 0x10) = v[1];
        *(f32 *)(p + 0x14) = v[2];
        p[0x18] = 1;
    }
}

void fn_803A41A4(u8 *p) {
    for (u32 i = 0; i < *(u16 *)(p + 0x10); i++) {
        (*(VObj3 **)(fn_80362AEC(p + 8, i) + 4))->v02();
    }
}

void fn_803A420C(u8 *p) {
    for (u32 i = 0; i < *(u16 *)(p + 0x10); i++) {
        (*(VObj3 **)(fn_80362AEC(p + 8, i) + 4))->v04();
    }
}

void fn_803A4274(u8 *p, u8 *arg) {
    for (u32 i = 0; i < *(u16 *)(p + 0x10); i++) {
        (*(VObj **)(fn_80362AEC(p + 8, i) + 4))->v18(arg);
    }
}

u8 *fn_803A4440(u8 *p, s32 del) {
    if (p && del > 0) {
        ::operator delete(p);
    }
    return p;
}

u8 *fn_803A4480(u8 *p, s32 del) {
    if (p && del > 0) {
        ::operator delete(p);
    }
    return p;
}

void fn_803A44C0(u8 *o, u8 *b) {
    u8 *q = *(u8 **)(b + 0x10);
    lbl_806405A8 = 0;
    ((VObj *)o)->v18(q + 0x10);
}

void fn_803A4764(u8 *p, u32 v) {
    *(u32 *)(p + 0x2c) = v;
}

u8 *fn_803A476C(u8 *p, u32 key) {
    for (u32 i = 0; i < *(u16 *)(p + 0x10); i++) {
        u8 *e = fn_80362AEC(p + 0x18, i);
        if (*(u32 *)e == key) {
            return *(u8 **)(e + 4);
        }
    }
    return 0;
}

u32 fn_803A49D8(u8 *p) {
    return *(u32 *)(p + 0x24);
}

u8 fn_803A4C6C(u8 *p) {
    return p[0xb7] & 1;
}

u32 fn_803A4C78(u8 *p) {
    return *(u32 *)(p + 0xc);
}

s32 fn_803A4D54(void) {
    return 0;
}

void fn_803A4D5C(u8 *p, u32 v) {
    *(u32 *)(p + 0x1c) = v;
}

void fn_803A4D64(void) {}

void fn_803A4D68(u8 *p, VObj2 *o) {
    *(VObj2 **)(p + 4) = o;
    if (o) {
        o->v01(p);
    }
}

s32 fn_803A4D94(void) {
    return 0;
}

void fn_803A4FC0(void *al, void *ctx) {
    u8 *p = lbl_8063D070[(s32)OSGetAlarmUserData(al)];
    s32 ch = *(s32 *)p;
    if (WPADIsSpeakerEnabled(ch)) {
        WPADControlSpeaker(ch, 3, 0);
    }
    p[0x41] = 0;
}

u8 *fn_803A50E8(u8 *p, s32 del) {
    if (p) {
        OSCancelAlarm(lbl_8063CEF0 + *(s32 *)p * 0x30);
        OSCancelAlarm(lbl_8063CFB0 + *(s32 *)p * 0x30);
        if (p + 0x20) {
            DetachSound__Q34nw4r3snd11SoundHandleFv(p + 0x20);
        }
        if (del > 0) {
            ::operator delete(p);
        }
    }
    return p;
}

void fn_803A5208(s32 *p) {
    WPADSetConnectCallback(*p, *(void **)(p + 10));
    *(void **)(p + 10) = 0;
    WPADSetExtensionCallback(*p, *(void **)(p + 11));
    *(void **)(p + 11) = 0;
}

void fn_803A53E0(u8 *p) {
    *(u32 *)(p + 0x10) = 0;
    *(u32 *)(p + 0x14) = 0;
    *(u32 *)(p + 0x18) = 0;
}

void fn_803A53F4(u8 *p) {
    f32 f = lbl_80642FC4;
    *(f32 *)(p + 0x8) = f;
    *(f32 *)(p + 0xc) = f;
}

void fn_803A5404(u8 *p) {
    fn_803A5F58(*(u8 **)(p + 0x24), *(u32 *)p);
}

void fn_803A5414(void) {}

void fn_803A5418(u8 *p, f32 v) {
    *(f32 *)(p + 0x4) = v;
}

u32 fn_803A54B4(s32 *p, s32 v) {
    if (fn_803A6070(*(u8 **)(p + 9), *p) == 0) {
        return 0;
    }
    return fn_803A608C(*(u8 **)(p + 9), *p, v);
}

void fn_803A5514(u8 *p) {
    p[0x42] = 0;
    p[0x43] = 0;
}

void fn_803A575C(u8 *p) {
    fn_803A60BC(*(u8 **)(p + 0x24), *(u32 *)p);
}

void fn_803A576C(void) {}

void fn_803A5770(s32 *p) {
    if (*p < 4 && fn_803A6070(*(u8 **)(p + 9), *p) == 0 && ((u8 *)p)[0x44] != 0) {
        ((u8 *)p)[0x1c] = 1;
        WPADControlMotor(*p, 1);
    }
}

void fn_803A57D4(void *pv) {
    u8 *p = (u8 *)pv;
    s32 ch = *(s32 *)p;
    if (ch < 4 && p[0x1c]) {
        p[0x1c] = 0;
        WPADControlMotor(ch, 0);
    }
}

s32 fn_803A5804(s32 *p, void *info) {
    if (*p >= 4) {
        return -2;
    }
    if (fn_803A6070(*(u8 **)(p + 9), *p) != 0 || ((u8 *)p)[0x1c] != 0) {
        return -2;
    }
    return WPADGetInfoAsync(*p, info, (void *)fn_803A5888);
}

void fn_803A5888(s32 i, s32 a) {
    if (a == 0 && i < 4) {
        lbl_806405B0[i] = 1;
    }
}

u8 fn_803A58A8(s32 *p) {
    s32 i = *p;
    if (i >= 4) {
        return 0;
    }
    return lbl_806405B0[i];
}

void fn_803A58C8(s32 *p) {
    s32 i = *p;
    if (i < 4) {
        lbl_806405B0[i] = 0;
    }
}

void fn_803A5B48(void) {
    u8 *p = lbl_806405B8;
    *(s32 *)(p + 0x58) = -1;
    *(u32 *)(p + 0x50) = 0;
    *(s32 *)(p + 0xc0) = -1;
    *(u32 *)(p + 0xb8) = 0;
    *(s32 *)(p + 0x128) = -1;
    *(u32 *)(p + 0x120) = 0;
    *(s32 *)(p + 0x190) = -1;
    *(u32 *)(p + 0x188) = 0;
}

u8 *fn_803A5C30(u8 *p, s32 del) {
    if (p) {
        *(u8 **)(p + 0x1f0) = lbl_80473058;
        lbl_806405B8 = 0;
        p[0x1ec] = 0;
        OSCancelAlarm(p + 0x1a0);
        u8 *q = p;
        for (s32 i = 0; i < 4; i++) {
            OSCancelAlarm(q);
            q += 0x68;
        }
        if (del > 0) {
            ::operator delete(p);
        }
    }
    return p;
}

void fn_803A5D64(u8 *p) {
    OSCancelAlarm(p + 0x1a0);
}

void fn_803A5D6C(void *a, void *b) {
    WPADControlSpeaker((s32)OSGetAlarmUserData(a), 1, (void *)fn_803A5D9C);
}

void fn_803A5E60(void *a, void *b) {
    WPADControlSpeaker((s32)OSGetAlarmUserData(a), 4, (void *)fn_803A5E90);
}

u32 fn_803A6070(u8 *p, s32 i) {
    return *(u32 *)(p + i * 0x68 + 0x50) != 0;
}

u32 fn_803A608C(u8 *p, s32 i, s32 v) {
    u8 *q = p + i * 0x68;
    if (*(u32 *)(q + 0x50) != 0 && v == *(s32 *)(q + 0x58)) {
        return 1;
    }
    return 0;
}

u32 fn_803A60BC(u8 *p, u32 i) {
    return *(u8 *)(p + i * 0x68 + 0x62) != 0;
}
}
