#include ".unsorted/8000ADC0.hpp"

#include ".unsorted/8011C974.hpp"
#include "ds/battle/battle_lib.hpp"
#include "ds/battle/battle_system.hpp"
#include "ds/pokemon.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSthread.hpp"

#include <string.h>

#include "common.hpp"

// TODO Replace with proper imports
extern "C" {
BattleSystem *fn_803AC828();
void *fn_802544D0();
void fn_802549D0();
int fn_80255890(void *);
f32 fn_8039349C(void *, int);
int fn_8039301C(void *, int);
int fn_80392FE8(void *, int);
void fn_802556A8(void *, int, int);
void fn_802554A0(void *, int, int);
u32 fn_802557AC(void *, int);
int fn_802557E0(void *, int);
void fn_80255520(void *, int, f32);
u32 fn_80255738(void *, int);
int fn_80255710(void *, int);
int fn_802553B8(void *, int, int);
int fn_80393084(void *, int);
Unk80035D9C *fn_80035D9C();
int fn_80035ED8(Unk80035D9C *);
void fn_80255350(void *, int, int);
void fn_8025643C(void *, int, int, void *, int);
int fn_80393434(void *, int);
int fn_802552AC(void *, int, int);
int fn_80035E38();
Unk80045590 *fn_80045590();
void fn_80024924();
void fn_80024A34();
void fn_80024BCC();
void fn_80024D80();
int fn_80024AEC(int);
int fn_80024A70(int, u32);
u32 fn_80255834(void *, int);
int fn_80035EA8(Unk80035D9C *);
int fn_8016FA3C();
int fn_8005F198();
int fn_80254E70(void *, int, int, int, int);
int fn_80393050(void *, int);
int fn_802550F8(void *, int, int, int, int);
int fn_80036554(Unk80035D9C *, int, int, int);
void fn_80254460(void *, void *, int, Unk8000ADC0 *, int);
void *fn_803930B8(void *, void *);
void *fn_80392E10(void *, void *);
void *fn_8039325C(void *, void *);
u8 fn_80036E6C(Unk80035D9C *, u8, int);
u8 fn_80036E94(Unk80035D9C *, u8, int);
u8 fn_80024B50(int, int);
u32 fn_80009838();
u32 fn_80256E24(void *);
u16 fn_80391FFC(void *, u16);
u8 fn_80391200(void *, u16);
u8 fn_803919C4(void *, u16);
u8 fn_803919F8(void *, u16);
int fn_8039394C(void *, int);
int fn_80393918(void *, int);
void fn_802565C0(void *, int, int, int, int, int);
void fn_80256850(void *, int, int, int);
int fn_80254A30(void *, int, int, int);
u32 fn_803C9158();
u32 fn_802568BC(void *);
f32 fn_80393468(void *, u8);
int fn_803934D0(void *, u8);
void fn_80255684(void *, int, f32);
void fn_8025565C(void *, int, int, f32);
void fn_80255628(void *, int, int, f32);
u32 fn_80254B80(void *, int);
u32 fn_80254B24(void *, int);
u32 fn_80254C18(void *, int);
int fn_80035F68(void *);
u32 fn_80256890(void *, int);
void fn_802567E8(void *);
void fn_80254AD0(void *, int);
void fn_80256BC0(void *, int);
int fn_80162A90(u32);
int fn_80035E58(Unk80035D9C *);
f32 fn_80393504(void *, int);
f32 fn_80393538(void *, int);
f32 fn_8039356C(void *, int);
f32 fn_803935A0(void *, int);
f32 fn_803935D4(void *, int);
f32 fn_80393608(void *, int);
f32 fn_8039363C(void *, int);
f32 fn_80393670(void *, int);
f32 fn_803936A4(void *, int);
f32 fn_803936D8(void *, int);
f32 fn_8039370C(void *, int);
void fn_802563D8(void *, int, void *, int);
void fn_80255C6C(void *, int, f32, f32, f32, f32, f32, f32);
void fn_80255DF0(void *, int, f32, f32, f32, f32, f32, f32);
void fn_80255F74(void *, int, f32, f32, f32, f32, f32);
void fn_80256264(void *, int, f32, f32, f32);
void fn_802560F0(void *, int, f32, f32, f32);
u8 *fn_8016F3FC(int *);
int fn_80035E68(Unk80035D9C *);
u8 fn_803939B4(void *, int);
u8 fn_80393980(void *, int);
}

extern f32 lbl_8063D318;
extern f32 lbl_8063D31C;
extern f32 lbl_8063D324;
extern u8 lbl_8063D328;
extern void *lbl_8063E958;
extern void *lbl_8063E954;
extern f32 lbl_8063D320;
extern void *lbl_8063E95C;
extern void *lbl_8063E960;
extern void *lbl_8063E964;
extern char lbl_804084E6[];
extern char lbl_80408D04[];
extern char lbl_80408D3C[];
extern char lbl_80408D7D[];
extern char lbl_80408DBE[];
extern char lbl_80409170[];
extern void *lbl_8063EA68;
extern f32 lbl_80640698;
extern char lbl_80407AE4[];
extern char lbl_804088F0[];
extern char lbl_8040933C[];
extern Unk800217CC lbl_804086FC[];
extern Unk800217CC lbl_80408914[];
extern f32 lbl_80640678;
extern char lbl_80409278[];
extern char lbl_8040848E[];
extern char lbl_804087B6[];
extern char lbl_804087EB[];
extern char lbl_8040662D[];
extern char lbl_804061BA[];
extern char lbl_804062B4[];
extern char lbl_804093EB[];
extern char lbl_804093CD[];
extern int lbl_8063E978;
extern char lbl_80408750[];
extern char lbl_80408786[];
extern char lbl_804089BC[];
extern char lbl_804089EA[];
extern char lbl_8063D335[3];
extern char lbl_8063D330[5];
extern char lbl_804092D6[];
extern Unk8000ADC0 lbl_803FB738;
extern void *lbl_8063E950;
extern u8 lbl_8044E9B8[];
extern u8 lbl_8044EA30[];
extern u8 lbl_80458D98[];
extern char lbl_80407C3D[];
extern char lbl_804066A5[];
extern const f32 lbl_80640690;
extern const f32 lbl_80640688;
extern f32 lbl_8063D988;
extern char lbl_804072A2[];
extern char lbl_8040803A[];
// TODO A table of strings read as lbl_80405FC0 + offset; split it with the .data of the unit.
extern char lbl_80405FC0[];
extern char lbl_80408A04[];
extern char lbl_80408890[];
extern u8 lbl_8063CE34[];
extern void *lbl_8063E988;
extern char lbl_80407304[];
extern char lbl_80408AB9[];
extern char lbl_80406534[];
extern int lbl_8063E980;
extern char lbl_80406312[];
extern char lbl_8040639E[];
extern const f32 lbl_8064067C;
extern char lbl_804072BB[];
extern char lbl_80408422[];
extern char lbl_8040844A[];
extern char lbl_804067D4[];
extern char lbl_804067F7[];
extern char lbl_80407494[];
extern char lbl_804074C2[];
extern const f32 lbl_806406A0;
extern char lbl_80406820[];
extern char lbl_80406844[];
extern char lbl_8040601C[];
extern char lbl_804084BD[];
extern char lbl_804082E1[];
extern char lbl_804082B2[];
extern char lbl_80409258[];
extern char lbl_804068E0[];
extern char lbl_804088C5[];
extern char lbl_80408508[];
extern char lbl_80408A51[];

#pragma optimize_for_size on
#pragma dont_inline on

// TODO Initialises the sound archive a with heap b and creates the three sound tables.
void fn_8000ADC0(char *a, MEMHeapHandle b) {
    Unk8000ADC0 buf = lbl_803FB738;
    void *m;
    fn_80254460(a, b, 3, &buf, 0);
    m = operator new(4);
    if (m) {
        m = fn_803930B8(m, lbl_8044E9B8);
    }
    lbl_8063E950 = m;
    m = operator new(4);
    if (m) {
        m = fn_80392E10(m, lbl_8044EA30);
    }
    lbl_8063E954 = m;
    m = operator new(4);
    if (m) {
        m = fn_8039325C(m, lbl_80458D98);
    }
    lbl_8063E958 = m;
    fn_8000B914(1, 0);
    fn_8000B914(2, 0);
    fn_8000B914(4, 0);
}

// TODO Calls fn_802549D0 on the sound system.
void fn_8000AE8C() {
    fn_802544D0();
    fn_802549D0();
}

// TODO Picks the output mode from k and applies it to the sound system.
void fn_8000AEB0(u8 k) {
    switch (k) {
        case 1:  lbl_8063E980 = 1; break;
        case 2:  lbl_8063E980 = 3; break;
        case 3:  lbl_8063E980 = 2; break;
        case 4:  lbl_8063E980 = 4; break;
        default: lbl_8063E980 = 0; break;
    }
    fn_80254A30(fn_802544D0(), 0, 0, 0);
    switch (lbl_8063E980) {
        case 1:  fn_80254A30(fn_802544D0(), 0xac0, 0, 0); break;
        case 3:  fn_80254A30(fn_802544D0(), 0x1116, 0, 0); break;
        case 2:  fn_80254A30(fn_802544D0(), 0x657, 0, 0); break;
        case 4:  fn_80254A30(fn_802544D0(), 0x157f, 0, 0); break;
        default: fn_80254A30(fn_802544D0(), 1, 0, 0); break;
    }
}

// TODO Returns 0 when sound x has category 0x14 and lbl_8063D328 is clear, 1 otherwise.
int fn_8000AFE0(int x) {
    if (lbl_8063D328 == 0) {
        switch ((u8)fn_80393084(lbl_8063E954, x)) {
            case 0x14: return 0;
        }
    }
    return 1;
}

// TODO Applies the table settings of sound a to the playing handle h, with value b and volume f.
void fn_8000B030(int h, int a, int b, f32 f) {
    int d;
    int c;
    u8 idx;
    f32 v;
    idx = fn_80393050(lbl_8063E954, a);
    v = fn_80393468(lbl_8063E958, idx);
    if ((f32)__fabs(v - lbl_80640678) > lbl_8064067C) {
        fn_80255684(fn_802544D0(), h, v);
    }
    c = fn_803934D0(lbl_8063E958, idx);
    d = fn_80393434(lbl_8063E958, idx);
    v = fn_8039349C(lbl_8063E958, idx);
    if ((u8)c && (u8)d != 0xff && v > lbl_8064067C) {
        int o = fn_8000BBB4(idx);
        fn_8025565C(fn_802544D0(), h, o, v);
    }
    if ((f32)__fabs(lbl_80640678 - f) > lbl_8064067C) {
        fn_80255628(fn_802544D0(), h, b, f);
    }
}

// TODO Starts sound a with value b and volume f; returns 1 on success.
int fn_8000B170(int a, int b, f32 f) {
    s16 v;
    int r;
    if (!fn_8000AFE0(a)) {
        return 0;
    }
    v = fn_80392FE8(lbl_8063E954, a);
    r = fn_80254E70(fn_802544D0(), v, b, 0, 0);
    if (r < 0) {
        return 0;
    }
    fn_8000B030(r, a, b, f);
    return 1;
}

// TODO Starts sound a through fn_802550F8 with value b and volume f; returns 1 on success.
int fn_8000B210(int a, int b, f32 f) {
    s16 v;
    int r;
    if (!fn_8000AFE0(a)) {
        return 0;
    }
    v = fn_80392FE8(lbl_8063E954, a);
    fn_80393050(lbl_8063E954, a);
    fn_80393084(lbl_8063E954, a);
    r = fn_802550F8(fn_802544D0(), v, b, 0, 0);
    if (r < 0) {
        return 0;
    }
    fn_8000B030(r, a, b, f);
    return 1;
}

// TODO Returns lbl_8063D328.
u8 fn_8000B2C8() {
    return lbl_8063D328;
}

// TODO Returns whether fn_802553B8 accepts sound x.
int fn_8000B2D0(int x) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    return fn_802553B8(fn_802544D0(), v, 0) >= 0;
}

// TODO Starts sound x through fn_802553B8 and waits up to 120 frames for it; returns 1 when it is ready.
int fn_8000B31C(int x) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    int r = fn_802553B8(fn_802544D0(), v, 0);
    int i;
    if (r < 0) {
        return 0;
    }
    for (i = 0; i < 0x78; i++) {
        if (fn_80255834(fn_802544D0(), r) == 1) {
            return 1;
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }
    return 0;
}

// TODO Starts sound x through fn_802552AC with value y; returns 1 on success.
int fn_8000B3B4(int x, int y) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    int r = fn_802552AC(fn_802544D0(), v, y);
    if (r < 0) {
        return 0;
    }
    fn_8000B030(r, x, y, lbl_80640678);
    return 1;
}

// TODO Returns the fn_80255738 state of sound x.
u32 fn_8000B42C(int x) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    return fn_80255738(fn_802544D0(), v);
}

// TODO Calls fn_80255350 on sound x with value y.
void fn_8000B46C(int x, int y) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    fn_80255350(fn_802544D0(), v, y);
}

// TODO Calls fn_80255710 on sound x and returns its result.
int fn_8000B4C0(int x) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    return fn_80255710(fn_802544D0(), v);
}

// TODO Calls fn_802556A8 on group 1 with x.
void fn_8000B500(int x) {
    fn_802556A8(fn_802544D0(), 1, x);
}

// TODO Calls fn_802556A8 on group 0 with x.
void fn_8000B538(int x) {
    fn_802556A8(fn_802544D0(), 0, x);
}

// TODO Calls fn_802554A0 on group 2 with x.
void fn_8000B570(int x) {
    fn_802554A0(fn_802544D0(), 2, x);
}

// TODO Returns the fn_802557AC value of group 2.
u32 fn_8000B5A8() {
    return fn_802557AC(fn_802544D0(), 2);
}

// TODO Calls fn_802554A0 on group 0 with x.
void fn_8000B5D0(int x) {
    fn_802554A0(fn_802544D0(), 0, x);
}

// TODO Calls fn_802554A0 on group 1 with x.
void fn_8000B608(int x) {
    fn_802554A0(fn_802544D0(), 1, x);
}

// TODO Calls fn_802554A0 on group 3 with x.
void fn_8000B640(int x) {
    fn_802554A0(fn_802544D0(), 3, x);
}

// TODO Calls fn_802554A0 on group 4 with x.
void fn_8000B678(int x) {
    fn_802554A0(fn_802544D0(), 4, x);
}

// TODO Calls fn_802554A0 on group 5 with x.
void fn_8000B6B0(int x) {
    fn_802554A0(fn_802544D0(), 5, x);
}

// TODO Calls fn_802554A0 on group 6 with x.
void fn_8000B6E8(int x) {
    fn_802554A0(fn_802544D0(), 6, x);
}

// TODO Returns the fn_802557AC value of group 3.
u32 fn_8000B720() {
    return fn_802557AC(fn_802544D0(), 3);
}

// TODO Stores f in lbl_8063D318 and sets the volume of group 2.
void fn_8000B748(f32 f) {
    lbl_8063D318 = f;
    fn_80255520(fn_802544D0(), 2, f);
}

// TODO Stores f in lbl_8063D31C and sets the volume of groups 0 and 1.
void fn_8000B784(f32 f) {
    lbl_8063D31C = f;
    fn_80255520(fn_802544D0(), 0, f);
    fn_80255520(fn_802544D0(), 1, f);
}

// TODO Stores f in lbl_8063D320 and sets the volume of group 3.
void fn_8000B7D0(f32 f) {
    lbl_8063D320 = f;
    fn_80255520(fn_802544D0(), 3, f);
}

// TODO Stores f in lbl_8063D324 and sets the volume of group 5.
void fn_8000B80C(f32 f) {
    lbl_8063D324 = f;
    fn_80255520(fn_802544D0(), 5, f);
}

// TODO Returns lbl_8063D318.
f32 fn_8000B848() {
    return lbl_8063D318;
}

// TODO Returns lbl_8063D31C.
f32 fn_8000B850() {
    return lbl_8063D31C;
}

// TODO Returns lbl_8063D324.
f32 fn_8000B858() {
    return lbl_8063D324;
}

// TODO Fills lbl_8063E95C, lbl_8063E960 and lbl_8063E964 through fn_8025643C.
void fn_8000B860() {
    fn_8025643C(fn_802544D0(), 0, 0xfa, &lbl_8063E95C, 0);
    fn_8025643C(fn_802544D0(), 1, 0xfa, &lbl_8063E960, 0);
    fn_8025643C(fn_802544D0(), 2, 0xfa, &lbl_8063E964, 0);
}

// TODO Applies the effects 1, 2 and 4 with the stored settings, then clears them.
void fn_8000B8C4() {
    fn_8000B914(1, lbl_8063E95C);
    fn_8000B914(2, lbl_8063E960);
    fn_8000B914(4, lbl_8063E964);
    lbl_8063E95C = 0;
    lbl_8063E960 = 0;
    lbl_8063E964 = 0;
}

// TODO Applies effect idx, from y when given or from the table otherwise.
// TODO Does not match yet (same size; the code differs).
void fn_8000B914(int idx, void *y) {
    // TODO The cast passes idx as an int, while fn_803934D0 is declared with a u8.
    int t = ((int (*)(void *, int))fn_803934D0)(lbl_8063E958, idx);
    int c;
    f32 x0, x1, x2, x3, x4;
    f32 a;
    if (!(u8)t) {
        return;
    }
    c = fn_8000BBB4(idx);
    if (y) {
        fn_802563D8(fn_802544D0(), c, y, 0);
        return;
    }
    a = fn_80393504(lbl_8063E958, idx);
    switch ((u8)t) {
        case 8:
            x4 = fn_80393538(lbl_8063E958, idx);
            x3 = fn_8039356C(lbl_8063E958, idx);
            x2 = fn_803935A0(lbl_8063E958, idx);
            x1 = fn_803935D4(lbl_8063E958, idx);
            x0 = fn_80393608(lbl_8063E958, idx);
            fn_80255C6C(fn_802544D0(), c, x4, x3, x2, x1, x0, a);
            break;
        case 9:
            x0 = fn_80393538(lbl_8063E958, idx);
            x1 = fn_8039356C(lbl_8063E958, idx);
            x2 = fn_803935A0(lbl_8063E958, idx);
            x3 = fn_803935D4(lbl_8063E958, idx);
            x4 = fn_80393608(lbl_8063E958, idx);
            fn_80255DF0(fn_802544D0(), c, x0, x1, x2, x3, x4, a);
            break;
        case 10:
            x0 = fn_80393538(lbl_8063E958, idx);
            x1 = fn_8039356C(lbl_8063E958, idx);
            x2 = fn_803935A0(lbl_8063E958, idx);
            x3 = fn_803935D4(lbl_8063E958, idx);
            fn_80255F74(fn_802544D0(), c, x0, x1, x2, x3, a);
            break;
        case 11:
            x4 = fn_8039363C(lbl_8063E958, idx);
            x3 = fn_80393670(lbl_8063E958, idx);
            fn_80256264(fn_802544D0(), c, x4, x3, a);
            break;
        case 12:
            a = fn_803936A4(lbl_8063E958, idx);
            x4 = fn_803936D8(lbl_8063E958, idx);
            x3 = fn_8039370C(lbl_8063E958, idx);
            fn_802560F0(fn_802544D0(), c, a, x4, x3);
            break;
    }
}

// TODO Returns the output index (0 to 2) of table entry x.
int fn_8000BBB4(int x) {
    switch ((u8)fn_80393434(lbl_8063E958, x)) {
        case 0xf:  return 0;
        case 0x10: return 1;
        case 0x11: return 2;
    }
    return 0;
}

// TODO Returns the table volume of entry x.
f32 fn_8000BC20(int x) {
    return fn_8039349C(lbl_8063E958, x);
}

// TODO Returns the fn_80255890 value of the sound system.
int fn_8000BC2C() {
    return fn_80255890(fn_802544D0());
}

// TODO Returns the fn_802557E0 value of group 3.
int fn_8000BC50() {
    return fn_802557E0(fn_802544D0(), 3);
}

// TODO Returns the table index of sound x.
int fn_8000BC78(int x) {
    return (s16)fn_80392FE8(lbl_8063E954, x);
}

// TODO Returns the fn_8039301C value of sound x.
int fn_8000BCA4(int x) {
    return fn_8039301C(lbl_8063E954, x);
}

// TODO Returns 1 when the 0x51C value of table entry idx is 4, 5, 6 or 8.
int fn_8000BCB0(int idx) {
    Unk8000BCB0 *s = fn_80045590()[idx]._10;
    switch (s->_51c) {
        case 1:
        case 2:
        case 3:
        case 7: return 0;
        case 4:
        case 5:
        case 6:
        case 8: return 1;
    }
    return 0;
}

// TODO Thread body: updates the lbl_8063E970 object while it is active.
void fn_8000BD2C() {
    while (1) {
        Unk8063E970 *p = lbl_8063E970;
        if (p->_0000 == 1 && p->_0004 != 0) {
            fn_8000D1B8(p);
            fn_8000CD70(lbl_8063E970);
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }
}

// TODO Returns whether the flag that matches k is set in the 0x266C word.
int fn_8000BD6C(Unk8063E970 *p, u32 k) {
    switch (k) {
        case 0x79:
        case 0xf2:
        case 0xf3:
        case 0xf5:
        case 0xf6:
        case 0x173:
        case 0x1b8: return (p->_266c & 0x1) != 0;
        case 0xf7:
        case 0xf8:  return (p->_266c & 0x1001) != 0;
        case 0xf1:  return (p->_266c & 0x2001) != 0;
        case 0x77:
        case 0x78:
        case 0x1b7: return (p->_266c & 0x2) != 0;
        case 0xf9:  return (p->_266c & 0x1004) != 0;
        case 0x7b:  return (p->_266c & 0x200000) != 0;
        case 0x7a:  return (p->_266c & 0x400000) != 0;
        case 0x74:
        case 0x75:
        case 0x1b9:
        case 0x1ba: return (p->_266c & 0x10) != 0;
        case 0xea:  return (p->_266c & 0x20) != 0;
        case 0x104:
        case 0x105:
        case 0x106:
        case 0x107: return (p->_266c & 0x820) != 0;
        case 0xec:  return (p->_266c & 0x40) != 0;
        case 0x122: return (p->_266c & 0x100040) != 0;
        case 0xed:  return (p->_266c & 0x80) != 0;
        case 0x124: return (p->_266c & 0x100080) != 0;
        case 0x123: return (p->_266c & 0x100000) != 0;
        case 0xee:  return (p->_266c & 0x100) != 0;
        case 0x126: return (p->_266c & 0x100100) != 0;
        case 0xef:  return (p->_266c & 0x201) != 0;
        case 0x125: return (p->_266c & 0x100201) != 0;
        case 0xeb:  return (p->_266c & 0x400) != 0;
        case 0xf0:  return (p->_266c & 0x2000) != 0;
        case 0x100:
        case 0x155:
        case 0x15a:
        case 0x15f: return (p->_266c & 0x10000) != 0;
        case 0x101: return (p->_266c & 0x20000) != 0;
        case 0x102:
        case 0x103: return (p->_266c & 0x40000) != 0;
        case 0x85:  return (p->_266c & 0x80000) != 0;
        case 0x76:
        case 0xf4:  break;
    }
    return 0;
}

// TODO Sets the flag that matches k in the 0x266C word.
void fn_8000C04C(Unk8063E970 *p, u32 k) {
    switch (k) {
        case 0x79:
        case 0xf2:
        case 0xf3:
        case 0xf5:
        case 0xf6:
        case 0x173:
        case 0x1b8: p->_266c |= 0x1; break;
        case 0xf7:
        case 0xf8:  p->_266c |= 0x1001; break;
        case 0xf1:  p->_266c |= 0x2001; break;
        case 0x77:
        case 0x78:
        case 0x1b7: p->_266c |= 0x2; break;
        case 0xf9:  p->_266c |= 0x1004; break;
        case 0x7b:  p->_266c |= 0x200000; break;
        case 0x7a:  p->_266c |= 0x400000; break;
        case 0x74:
        case 0x75:
        case 0x1b9:
        case 0x1ba: p->_266c |= 0x10; break;
        case 0xea:  p->_266c |= 0x20; break;
        case 0x104:
        case 0x105:
        case 0x106:
        case 0x107: p->_266c |= 0x820; break;
        case 0xec:  p->_266c |= 0x40; break;
        case 0x122: p->_266c |= 0x100040; break;
        case 0xed:  p->_266c |= 0x80; break;
        case 0x124: p->_266c |= 0x100080; break;
        case 0x123: p->_266c |= 0x100000; break;
        case 0xee:  p->_266c |= 0x100; break;
        case 0x126: p->_266c |= 0x100100; break;
        case 0xef:  p->_266c |= 0x201; break;
        case 0x125: p->_266c |= 0x100201; break;
        case 0xeb:  p->_266c |= 0x400; break;
        case 0x108:
        case 0x109:
        case 0x110: p->_266c |= 0x800; break;
        case 0x127:
        case 0x128: p->_266c |= 0x1000; break;
        case 0xf0:  p->_266c |= 0x2000; break;
        case 0x100:
        case 0x155:
        case 0x15a:
        case 0x15f: p->_266c |= 0x10000; break;
        case 0x101: p->_266c |= 0x20000; break;
        case 0x102:
        case 0x103: p->_266c |= 0x40000; break;
        case 0x85:  p->_266c |= 0x80000; break;
        case 0x76:
        case 0xf4:  break;
    }
}

// TODO Picks an id from the 0x10 value of the fn_8011C974 object and returns fn_80162A90 of it.
int fn_8000C378() {
    Unk8011C974 *q = fn_8011C974();
    u32 id = 0xFFFFFFFF;
    switch (q->_0010) {
        case 1000:
            if (q->_0014 == 0) {
                id = 0x23;
            } else {
                id = 0x1b1;
            }
            break;
        case 1001:
            if (q->_009a == 1) {
                id = 0x24;
            } else {
                id = 0x1b2;
            }
            break;
        case 1002:
            if (q->_009a == 1) {
                id = 0x25;
            } else {
                id = 0x1b3;
            }
            break;
        case 1003:
            if (q->_009a == 1) {
                id = 0x26;
            } else {
                id = 0x1b4;
            }
            break;
        case 1004:
            if (q->_009a == 1) {
                id = 0x27;
            } else {
                id = 0x1b5;
            }
            break;
        case 1005:
            if (q->_0014 == 6) {
                if (q->_009a == 1) {
                    id = 0x28;
                } else {
                    id = 0x1b6;
                }
            } else {
                id = 0x1b7;
            }
            break;
        case 1006:
            if (q->_009a == 1) {
                id = 0x29;
            } else {
                id = 0x1b8;
            }
            break;
        case 1007:
            if (q->_0014 == 10) {
                if (q->_009a == 1) {
                    id = 0x2a;
                } else {
                    id = 0x1b9;
                }
            } else {
                id = 0x1ba;
            }
            break;
        case 1008:
            if (q->_009a == 1) {
                id = 0x2b;
            } else {
                id = 0x1bb;
            }
            break;
        case 1009: id = !fn_80162A90(0x39) ? 0x2c : 0x1bc; break;
    }
    if (id == 0xFFFFFFFF) {
        fn_8000C52C(lbl_80405FC0);
        return 0;
    }
    return fn_80162A90(id);
}

// TODO Debug print; empty in this build.
void fn_8000C52C(const char *fmt, ...) {}

// TODO Picks a second id from the 0x10 value of the fn_8011C974 object and returns fn_80162A90 of it.
int fn_8000C57C() {
    Unk8011C974 *q = fn_8011C974();
    u32 id = 0xFFFFFFFF;
    switch (q->_0010) {
        case 1000:
            if (q->_0014 == 0) {
                id = 0x19;
            } else {
                id = 0x251;
            }
            break;
        case 1001:
            if (q->_009a == 1) {
                id = 0x1a;
            } else {
                id = 0x252;
            }
            break;
        case 1002:
            if (q->_009a == 1) {
                id = 0x1b;
            } else {
                id = 0x253;
            }
            break;
        case 1003:
            if (q->_009a == 1) {
                id = 0x1c;
            } else {
                id = 0x254;
            }
            break;
        case 1004:
            if (q->_009a == 1) {
                id = 0x1d;
            } else {
                id = 0x255;
            }
            break;
        case 1005:
            if (q->_0014 == 6) {
                if (q->_009a == 1) {
                    id = 0x1e;
                } else {
                    id = 0x256;
                }
            } else {
                id = 0x257;
            }
            break;
        case 1006:
            if (q->_009a == 1) {
                id = 0x1f;
            } else {
                id = 0x258;
            }
            break;
        case 1007:
            if (q->_0014 == 10) {
                if (q->_009a == 1) {
                    id = 0x20;
                } else {
                    id = 0x259;
                }
            } else {
                id = 0x25a;
            }
            break;
        case 1008:
            if (q->_009a == 1) {
                id = 0x21;
            } else {
                id = 0x25b;
            }
            break;
        case 1009:
            if (fn_80162A90(0x39) == 0) {
                id = 0x22;
            } else {
                id = (q->_0145 < (u32)fn_80162A90(0x249)) ? 0x25c : 0;
            }
            break;
    }
    if (id == 0) {
        return 0;
    }
    if (id == 0xFFFFFFFF) {
        fn_8000C52C(lbl_8040601C);
        return 0;
    }
    return fn_80162A90(id);
}

// TODO Creates the lbl_8063E970 object and its thread.
void fn_8000C764() {
    Unk8063E970 *p = (Unk8063E970 *)operator new(0x9DFC);
    if (p) {
        p = (Unk8063E970 *)fn_8000C7F0(p);
    }
    lbl_8063E970 = p;
    p->_9dc0 = GSthreadManager::sInstance->createThread(0x136, (void *(*)(void *))fn_8000BD2C, 0, 0x4000, 8, 1);
    fn_80024924();
    fn_80024A34();
    fn_80024BCC();
    fn_80024D80();
}

// TODO Returns lbl_8063E970.
Unk8063E970 *fn_8000C7E8() {
    return lbl_8063E970;
}

// TODO Clears three words.
void fn_8000CBD4(u32 *p) {
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}

// TODO Destructor: frees p when del is positive.
void *fn_8000CBE8(void *p, int del) {
    if (p && del > 0) {
        operator delete(p);
    }
    return p;
}

// TODO Destructor: releases lbl_8063EA68 and frees p when del is positive.
void *fn_8000CC28(void *p, int del) {
    if (p) {
        fn_8000CC28(lbl_8063EA68, 1);
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// TODO Clears an entry.
void fn_8000CC84(Unk8000CC84 *p) {
    p->_00 = 0;
    p->_04 = 0;
    p->_08 = 0xff;
    p->_09 = 0;
    p->_0a = 0;
    p->_0b = 0;
    p->_0c = 0;
    p->_0d = 0;
    p->_12 = 0;
    p->_13 = 0;
    p->_14 = 0;
    p->_15 = 0;
    p->_16 = 0;
    p->_17 = 0;
    p->_18[0] = 0;
    p->_1d = 0xff;
    p->_20 = 0;
    p->_24 = 0;
    p->_26 = 0;
    p->_28 = 0;
    p->_2c = 0;
    p->_30 = 0;
    p->_50 = 0;
    p->_54 = 0;
}

// TODO Destructor: frees p when del is positive.
void *fn_8000CCF0(void *p, int del) {
    if (p && del > 0) {
        operator delete(p);
    }
    return p;
}

// TODO Destructor: frees p when del is positive.
void *fn_8000CD30(void *p, int del) {
    if (p && del > 0) {
        operator delete(p);
    }
    return p;
}

// TODO Per-frame update of the object.
void fn_8000D1B8(Unk8063E970 *p) {
    fn_8000D8AC(p);
    if (fn_80035D9C()) {
        int r = fn_80035E38();
        p->_0040 = r;
        if (p->_0004 == 2) {
            switch (r) {
                case 4:
                    if (fn_8000D230(p) == 1) {
                        fn_8000E2C8(p);
                        fn_8000E4A0(p);
                    }
                    break;
            }
        }
    }
}

// TODO Returns whether the battle system and its context exist.
bool fn_8000D230(void *) {
    BattleSystem *battleSys = fn_803AC828();
    if (battleSys == NULL) {
        return 0;
    }
    return BattleSystem_GetBattleContext(battleSys) != NULL;
}

// TODO Resets the object for state 1 and prints the heap sizes.
void fn_8000D26C(Unk8063E970 *bp) {
    char *str = lbl_80405FC0;
    if (bp->_0000) {
        fn_8000C52C(str + 0x1fa, str + 0x1eb);
        if (fn_80254B80(fn_802544D0(), 1) > 0x100 || fn_80254B80(fn_802544D0(), 2) > 0x100) {
            fn_8000C52C(str + 0x20e, fn_80254B80(fn_802544D0(), 1), fn_80254B80(fn_802544D0(), 2));
        }
        bp->_9dae = 0;
        bp->_003c = 0;
        bp->_0044 = 0;
        bp->_0048 = 0;
        bp->_005c = 0;
        bp->_0004 = 1;
        fn_8000C52C(str + 0x23f,
                    fn_80254B80(fn_802544D0(), 1) >> 10,
                    fn_80254C18(fn_802544D0(), 1) >> 10,
                    fn_80254B24(fn_802544D0(), 1) >> 10);
        fn_8000C52C(str + 0x286,
                    fn_80254B80(fn_802544D0(), 2) >> 10,
                    fn_80254C18(fn_802544D0(), 2) >> 10,
                    fn_80254B24(fn_802544D0(), 2) >> 10);
    }
}

// TODO Resets the object for state 2.
void fn_8000D3C4(Unk8063E970 *bp) {
    char *str = lbl_80405FC0;
    if (bp->_0000) {
        Unk80035D9C *x;
        fn_8000C52C(str + 0x1fa, str + 0x2cd);
        x = fn_80035D9C();
        if (x) {
            int v = fn_80035E58(x);
            bp->_003d = v;
            bp->_003e = !(u8)v ? 2 : 4;
            bp->_003f = fn_80035E68(x) == 2 ? 2 : 4;
        } else {
            fn_8000C52C(str + 0x2d9);
        }
        bp->_0040 = 0;
        bp->_0044 = 0;
        bp->_0048 = 0;
        bp->_004c = 0;
        bp->_0050 = 0;
        bp->_0054 = 0;
        bp->_0058 = 0;
        bp->_1068 = 0;
        bp->_106c = 0;
        bp->_106e = 0;
        bp->_106f = 0xff;
        bp->_280e = 0;
        bp->_2810 = 0;
        bp->_2812 = 0;
        bp->_281c = 0;
        bp->_285c[1] = 0;
        bp->_285c[0] = 0;
        bp->_285e[1] = 0;
        bp->_285e[0] = 0;
        bp->_281e = 0;
        bp->_2820 = 0;
        bp->_281f = 0;
        bp->_2822 = 0;
        bp->_2821 = 0;
        memset(bp->_2824, 0, 8);
        memset(bp->_282c, 0, 8);
        memset(bp->_2834, 0, 0x10);
        memset(bp->_2844, 0, 8);
        memset(bp->_284c, 0, 0x10);
        memset(bp->_285c, 0, 2);
        memset(bp->_285e, 0, 2);
        memset(bp->_2860, 0, 0x18);
        memset(bp->_2878, 0, 0x18);
        memset(bp->_2890, 0, 8);
        memset(bp->_2898, 0, 4);
        memset(bp->_289c, 0, 4);
        memset(bp->_28a0, 0, 0x10);
        memset(bp->_28b0, 0, 4);
        memset(bp->_28b4, 0, 4);
        memset(bp->_28b8, 0, 4);
        memset(bp->_28bc, 0, 4);
        bp->_28c0 = 0;
        bp->_28c4 = 0;
        bp->_28c8 = 0;
        bp->_28cc = 0;
        bp->_28ce = 0;
        bp->_28cf = 0;
        bp->_28d0 = 0;
        bp->_9daf = 0xff;
        bp->_9db0 = 0;
        bp->_9db1 = 0;
        bp->_9db2 = 0;
        bp->_9db3 = 0;
        bp->_9db4 = 0;
        bp->_9db5 = 0;
        bp->_9db6 = 0;
        bp->_9db7 = 0;
        bp->_0004 = 2;
        bp->_28dc = 0;
        bp->_6198 = 0;
        bp->_9a54 = 0;
        bp->_9bc8 = 0;
        fn_80019310(&bp->_9d3c[0]);
        fn_80019310(&bp->_9d3c[1]);
        memset(bp->_9bb8, 0, 0x10);
        memset(bp->_9d2c, 0, 0x10);
        bp->_9dac = 0;
        bp->_9dad = 0;
    }
}

// TODO Queues request 8, waits for the queue to empty and resets the object.
void fn_8000D68C(Unk8063E970 *p) {
    if (p->_0000) {
        fn_8000C52C(lbl_804061BA, lbl_804062B4);
        fn_8000D818(p, 8, 0, 0);
        while ((int)fn_8000D734(p) > 0) {
            GSthreadManager::sInstance->sleepCurrentThread();
        }
        fn_8000EEBC(p);
        p->_0004 = 0;
        p->_004c = 0;
        p->_0050 = 0;
        p->_1068 = 0;
        memset(p->_2890, 0, 8);
    }
}

// TODO Returns the number of queued requests, under the 0x9DC4 mutex.
u32 fn_8000D734(Unk8063E970 *p) {
    OSMutex *l;
    u32 r;
    fn_8000D780((void **)&l, &p->_9dc4);
    r = p->_0008;
    fn_8000D7B8(&l, -1);
    return r;
}

// TODO Locks mutex m and keeps it in p.
void *fn_8000D780(void **p, OSMutex *m) {
    *p = m;
    OSLockMutex(m);
    return p;
}

// TODO Unlocks the mutex kept in p and frees p when del is positive.
void *fn_8000D7B8(OSMutex **p, int del) {
    if (p) {
        OSUnlockMutex(*p);
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// TODO Sets the first byte of the object to v.
void fn_8000D810(Unk8063E970 *p, u8 v) {
    p->_0000 = v;
}

// TODO Queues request (a, b, c), under the 0x9DC4 mutex; at most four.
void fn_8000D818(Unk8063E970 *p, int a, void *b, int c) {
    OSMutex *l;
    int n;
    fn_8000D780((void **)&l, &p->_9dc4);
    n = p->_0008;
    if (n >= 4) {
        fn_8000D7B8(&l, -1);
        return;
    }
    p->_000c[n]._0 = a;
    p->_000c[n]._4 = b;
    p->_000c[n]._8 = c;
    p->_0008 = p->_0008 + 1;
    fn_8000D7B8(&l, -1);
}

// TODO Stops the sounds of the object when one is active.
void fn_8000DE70(Unk8063E970 *p) {
    if (p->_1070._00 != 0 || p->_1170 != 0) {
        fn_80015234(p, 0);
        fn_80020BF8(p);
    }
}

// TODO Counts the entries of each side and flags 0x3C when one of them has the 0x9F value.
void fn_8000DEC4(Unk8063E970 *bp) {
    u32 found;
    u8 i;
    u32 j;
    if (bp->_003f == 2 || bp->_003f == 4) {
        found = 0;
        memset(bp->_9db8, 0, 4);
        for (i = 0; i < bp->_003f; i++) {
            for (j = 0; j < 6; j++) {
                u16 v = fn_8000DFC4(bp, i, j, 5, 0);
                if (v != 0 && v != 0xffff) {
                    bp->_9db8[i]++;
                    if ((u8)fn_8000DFC4(bp, i, j, 0x9f, 0)) {
                        found = 1;
                    }
                }
            }
        }
        if (found == 1) {
            bp->_003c |= 2;
        }
    }
}

// TODO Returns fn_803DAE64 for side a, entry b and value c, folding a for two sides.
u32 fn_8000DFC4(Unk8063E970 *p, int a, u8 b, int c, void *d) {
    u8 m;
    if (b >= 7) {
        fn_8000C52C(lbl_804093EB);
    }
    m = p->_003f;
    if (m == 4) {
        return fn_803DAE64(a, b, c, d);
    }
    if (m != 2) {
        fn_8000C52C(lbl_804093CD, m);
    }
    return fn_803DAE64(a & 1, b, c, d);
}

// TODO Starts a new step of the object.
void fn_8000E06C(Unk8063E970 *p) {
    if (p->_0050 > p->_004c) {
        return;
    }
    p->_0050 = p->_004c + 1;
    p->_9daf = 0xff;
    p->_9db2 = 0;
    p->_106c = 0;
    p->_106e = 0;
    p->_106f = 0xff;
    p->_0044 = 0;
    p->_0048 = 0;
    fn_8000E88C(p);
    fn_8000EBAC(p, fn_803C9158());
    p->_28c0 = fn_803C9158();
    p->_28cc = 0;
    p->_28ce = 0;
    p->_28cf = 0;
    p->_28d4[0] = 0;
    p->_28d4[1] = 0;
    p->_285e[0] = p->_285c[0];
    p->_285e[1] = p->_285c[1];
    fn_80015E7C(p, p->_285c, &p->_285c[1], p->_2824, p->_282c, p->_2834, p->_2844, p->_284c);
    p->_2670 = p->_266c;
    p->_9dad = p->_9dac;
    p->_9dac = 0;
    fn_8000C52C(lbl_80406534, fn_8000BC2C(), fn_8000BC50());
    if (p->_9db7) {
        p->_9db7--;
    }
}

// TODO Stops the sounds, plays the next ones and moves to state 3.
// TODO Does not match yet (0x140 bytes instead of 0x134).
#pragma push
#pragma optimize_for_size off
void fn_8000E194(Unk8063E970 *p, void *x) {
    int a[8];
    int b[8];
    int i;
    int r;
    fn_80015234(p, 0);
    fn_80020D44(p);
    GSthreadManager::sInstance->sleepCurrentThread();
    fn_8000CD70(p);
    for (i = 0; i < 8; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        b[i] = 0;
    }
    r = fn_8000EEF4(p, a, b, x);
    fn_80015608(p, r, a, b);
    if (p->_1070._00 > 0) {
        if (fn_80009838() == 1) {
            fn_8000C52C(lbl_80406312);
            fn_80015234(p, 0);
        } else {
            fn_802568BC(&p->_1070);
            if (fn_80009838() == 1) {
                fn_8000C52C(lbl_8040639E);
                fn_80015234(p, 5);
            }
        }
    }
    p->_0044 = 0;
    p->_0048 = 0;
    p->_005c = 0;
    p->_0004 = 3;
}
#pragma pop

// TODO Updates the 0x54 state of the object.
void fn_8000E2C8(Unk8063E970 *p) {
    char *str = lbl_80405FC0;
    switch (p->_0054) {
        case 1: {
            int t = fn_8016FA3C();
            if (p->_004c < t) {
                fn_8000C52C(str + 0x5a5, t);
                p->_106c = 0;
                p->_106e = 1;
                p->_106f = 0xff;
                p->_004c = t;
                p->_9db6 = 0;
                if (p->_1170 > 0 && p->_2669 < p->_1170 && fn_80256E24(&p->_1268[p->_2669]) == 1) {
                    int a;
                    s8 b;
                    p->_9db6 = 1;
                    a = fn_8039394C(lbl_8063E988, p->_1174[p->_2669]);
                    b = fn_80393918(lbl_8063E988, p->_1174[p->_2669]);
                    fn_8000C52C(str + 0x5d1, p->_2669, b, (s16)a, p->_1174[p->_2669]);
                }
                fn_80020D44(p);
                GSthreadManager::sInstance->sleepCurrentThread();
                fn_8000CD70(p);
                fn_80016580(p);
                p->_0054 = 2;
                if (p->_1170 == 0) {
                    fn_8000C52C(str + 0x618);
                }
            }
            break;
        }
        case 2: break;
        case 3:
            if (p->_1170 > 0) {
                fn_80020E34(p);
                p->_0054 = 4;
                if (p->_1170 > 0 && p->_123c[0] == 0x1d && p->_2668 < 0) {
                    p->_2668 = 0;
                }
            } else {
                fn_8000C52C(str + 0x639);
                p->_0054 = 4;
            }
            break;
    }
}

// TODO Fills the per-side tables at 0x2890.
void fn_8000E88C(Unk8063E970 *p) {
    u8 i;
    u8 n;
    memset(p->_2890, 0, 8);
    memset(p->_2898, 0, 4);
    memset(p->_289c, 0, 4);
    memset(p->_28a0, 0, 0x10);
    memset(p->_28b0, 0, 4);
    memset(p->_28b4, 0, 4);
    memset(p->_28b8, 0, 4);
    memset(p->_28bc, 0, 4);
    n = p->_003e;
    for (i = 0; i < n; i++) {
        BattleSystem *battleSys;
        int v;
        p->_2890[i] = fn_8000EA70(p, i);
        battleSys = fn_803AC828();
        v = BattleContext_Get(battleSys, BattleSystem_GetBattleContext(battleSys), BATTLECTX_SELECTED_PARTY_SLOT, i);
        p->_2898[i] = v;
        if ((u8)v <= 5) {
            u32 t;
            p->_289c[i] = BattleMon_Get(BattleSystem_GetBattleContext(fn_803AC828()), i, BATTLEMON_ABILITY, NULL);
            p->_28a0[i] =
                BattleMon_Get(BattleSystem_GetBattleContext(fn_803AC828()), i, BATTLEMON_MOVE_EFFECTS_MASK, NULL);
            p->_28b0[i] = BattleMon_Get(BattleSystem_GetBattleContext(fn_803AC828()), i, BATTLEMON_ROLLOUT_COUNT, NULL);
            t = BattleMon_Get(BattleSystem_GetBattleContext(fn_803AC828()), i, BATTLEMON_VOLATILE_STATUS, NULL);
            p->_28b4[i] = (t >> 10) & 3;
            p->_28b8[i] = (t >> 4) & 7;
            p->_28bc[i] =
                BattleMon_Get(BattleSystem_GetBattleContext(fn_803AC828()), i, BATTLEMON_PERISH_SONG_TURNS, NULL);
        } else {
            p->_289c[i] = 0;
            p->_28a0[i] = 0;
            p->_28b0[i] = 0;
            p->_28b4[i] = 0;
            p->_28b8[i] = 0;
            p->_28bc[i] = 0;
        }
    }
}

// TODO Returns the 5 value of entry x.
u16 fn_8000EA70(Unk8063E970 *p, int x) {
    BattleSystem *battleSys = fn_803AC828();
    BattleContext *battleCtx = BattleSystem_GetBattleContext(battleSys);
    return fn_8000DFC4(p, x, BattleContext_Get(battleSys, battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, x), 5, 0);
}

// TODO Sets the per-side table entry k from value v.
void fn_8000EAE0(Unk8063E970 *p, u8 k, u16 v) {
    Unk80035D9C *x;
    if (v != 0) {
        x = fn_80035D9C();
        if (v != fn_80036554(x, k, 0, 0)) {
            fn_8000C52C(lbl_804066A5);
        }
        p->_2890[k] = v;
        p->_2898[k] = fn_80036E6C(x, k, 0);
        p->_289c[k] = fn_80036E94(x, k, 0);
        p->_28a0[k] = 0;
        p->_28b0[k] = 0;
        p->_28b4[k] = 0;
        p->_28b8[k] = 0;
        p->_28bc[k] = 0;
    }
}

// TODO Stores v in 0x28C4 and flags 0x3C when some bits were cleared.
void fn_8000EBAC(Unk8063E970 *p, u32 v) {
    u32 old = p->_28c4;
    if ((old & 0x80ff) != (v & 0x80ff) && p->_0050 >= 2) {
        if ((old & 3) && !(v & 3)) {
            p->_003c |= 4;
        } else if ((old & 0xC0) && !(v & 0xC0)) {
            p->_003c |= 0x20;
        } else if ((old & 0xC) && !(v & 0xC)) {
            p->_003c |= 8;
        } else if ((old & 0x30) && !(v & 0x30)) {
            p->_003c |= 0x10;
        }
    }
    p->_28c8 = p->_28c4;
    p->_28c4 = v;
}

// TODO Updates the 0x28C0 flags from the entries of block qi.
void fn_8000EC58(Unk8063E970 *p, Unk80035D9C *q) {
    int n = fn_80035F68(q);
    int i;
    for (i = 0; i < n; i++) {
        u32 x;
        switch (q->_96c[i]._04) {
            case 0x13:
                x = p->_28c0;
                if (!(x & 3)) {
                    p->_28c0 = (x & 0xFFFF7F00) | 2;
                }
                break;
            case 0x14:
                x = p->_28c0;
                if (!(x & 0xC0)) {
                    p->_28c0 = (x & 0xFFFF7F00) | 0x80;
                }
                break;
            case 0x15:
                x = p->_28c0;
                if (!(x & 0xC)) {
                    p->_28c0 = (x & 0xFFFF7F00) | 8;
                }
                break;
            case 0x16:
                x = p->_28c0;
                if (!(x & 0x30)) {
                    p->_28c0 = (x & 0xFFFF7F00) | 0x20;
                }
                break;
            case 0x12: p->_28c0 |= 0x8000; break;
            case 0x74:
            case 0x75:
            case 0x76:
            case 0x77: p->_28c0 &= 0xFFFF7F00; break;
            case 0x78: p->_28c0 &= ~0x8000; break;
        }
    }
}

// TODO Copies the current entries and blocks to the previous ones and clears the current ones.
void fn_8000EDB0(Unk8063E970 *bp) {
    int i;
    bp->_9bc8 = bp->_9a54;
    memcpy(bp->_9bcc, bp->_9a58, bp->_9a54 * sizeof(Unk8000CC84));
    bp->_6198 = bp->_28dc;
    memcpy(bp->_619c, bp->_28e0, bp->_28dc * 0x974);
    memset(bp->_9d2c, 0, sizeof(bp->_9d2c));
    for (i = 0; i < bp->_9bc8; i++) {
        bp->_9bcc[i]._04 = &bp->_619c[bp->_9bcc[i]._00];
        bp->_9d2c[bp->_9bcc[i]._1d] = &bp->_9bcc[i];
    }
    memcpy(bp->_9d74, bp->_9d3c, sizeof(bp->_9d3c));
    bp->_9d74[0]._00 = 0;
    bp->_9d74[1]._00 = 0;
    bp->_9a54 = 0;
    bp->_28dc = 0;
    fn_80019310(&bp->_9d3c[0]);
    fn_80019310(&bp->_9d3c[1]);
}

// TODO Rotates the five 0x2674 buffers and clears the first one.
void fn_8000EEBC(Unk8063E970 *p) {
    u8 *last = p->_2674[4];
    int i;
    for (i = 4; i > 0; i--) {
        p->_2674[i] = p->_2674[i - 1];
    }
    p->_2674[0] = last;
    memset(p->_2688, 0, 0x4e);
}

// TODO Returns a, b, c or d at random.
u32 fn_8000FE58(void *p, u32 a, u32 b, u32 c, u32 d) {
    u32 r = fn_8000FECC(100);
    if (r < 25) {
        return a;
    }
    if (r < 50) {
        return b;
    }
    if (r < 75) {
        d = c;
    }
    return d;
}

// TODO Returns a random number below n.
#pragma push
#pragma optimize_for_size off
u32 fn_8000FECC(u32 n) {
    u32 *seed = GSmath::getRandSeed();
    u32 lo, hi;
    if (n != 0) {
        lo = (u16)fn_8000FF40(seed);
        hi = fn_8000FF40(seed);
        return ((hi << 16) | lo) % n;
    }
    return 0;
}
#pragma pop

// TODO Advances the random seed p and returns its high half.
u32 fn_8000FF40(u32 *p) {
    *p = *p * 0x343FD + 0x269EC3;
    return *p >> 16;
}

// TODO Returns whether the counts from fn_80010078 reach the limit for the 0x3D mode.
int fn_8000FF64(Unk8063E970 *p, void *x) {
    Unk8011C974 *q = fn_8011C974();
    u8 m = p->_003d;
    int t = q->_0018;
    int a, b, c;
    if ((m == 0 && t == 5) || (m == 1 && t == 3)) {
        return 1;
    }
    a = 0;
    b = 0;
    c = 0;
    fn_80010078(p, &a, &b, &c, (int)x);
    m = p->_003d;
    if ((m == 0 && (a == 3 || b == 3)) || (m == 1 && (a == 2 || b == 2))) {
        return 1;
    }
    if (m == 0 && c == 2 && (a == 2 || b == 2)) {
        return 1;
    }
    return 0;
}

// TODO Counts the 0, 1 and 2 values of the 0x80 table of the fn_8011C974 object, then k.
// TODO Does not match yet (same size; the code differs).
int fn_80010078(void *p, int *a, int *b, int *c, int k) {
    Unk8011C974 *q = fn_8011C974();
    u8 n = q->_0018;
    int i;
    for (i = 0; i < n - 1; i++) {
        if (i >= 10) {
            fn_8000C52C(lbl_804067D4, n);
            break;
        }
        switch (q->_0080[i]) {
            case 0:  (*a)++; break;
            case 1:  (*b)++; break;
            case 2:  (*c)++; break;
            default: fn_8000C52C(lbl_804067F7, i + 1, q->_0080[i]); break;
        }
    }
    switch (k) {
        case 0:  (*a)++; break;
        case 1:  (*b)++; break;
        case 2:  (*c)++; break;
        default: fn_8000C52C(lbl_804067F7, n, k); break;
    }
    if (*a == *b) {
        return 2;
    }
    return *a <= *b;
}

// TODO Counts the 0, 1 and 2 values of the 0x1C table of the fn_8011C974 object, then k.
// TODO Does not match yet (same size; the code differs).
int fn_80010968(void *p, int *a, int *b, int *c, int k) {
    Unk8011C974 *q = fn_8011C974();
    u16 n = q->_0016;
    int i;
    for (i = 0; i < n - 1; i++) {
        if (i >= 100) {
            fn_8000C52C(lbl_80406820, n);
            break;
        }
        switch (q->_001c[i]) {
            case 0:  (*a)++; break;
            case 1:  (*b)++; break;
            case 2:  (*c)++; break;
            default: fn_8000C52C(lbl_80406844, n, q->_001c[i]); break;
        }
    }
    switch (k) {
        case 0:  (*a)++; break;
        case 1:  (*b)++; break;
        case 2:  (*c)++; break;
        default: fn_8000C52C(lbl_80406844, n, q->_001c[i]); break;
    }
    if (*a == *b) {
        return 2;
    }
    return *a <= *b;
}

// TODO Appends to out the id that matches the 0x16 count of the fn_8011C974 object.
int fn_80011290(void *p, int *cnt, int *out, int unused, int k) {
    Unk8011C974 *q = fn_8011C974();
    int l = fn_80162A90(0x38);
    fn_8000C52C(lbl_804068E0, q->_0016, l, k);
    switch (k) {
        case 0: {
            u16 t = q->_0016;
            if (l >= 5 && t == l + 1) {
                out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x206 : 0x207;
                (*cnt)++;
            } else {
                switch (t) {
                    case 10:
                        out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x200 : 0x201;
                        (*cnt)++;
                        break;
                    case 0x32:
                        out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x202 : 0x203;
                        (*cnt)++;
                        break;
                    case 0x64:
                        out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x204 : 0x205;
                        (*cnt)++;
                        break;
                }
            }
            break;
        }
        case 1:
        case 2: {
            int t = q->_0016 - 1;
            if (l >= 5 && t > l) {
                if (t >= 100) {
                    out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x23b : 0x23c;
                    (*cnt)++;
                } else {
                    out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x23d : 0x23e;
                    (*cnt)++;
                }
            } else if (t >= 8) {
                out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x23f : 0x240;
                (*cnt)++;
            } else {
                out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x241 : 0x242;
                (*cnt)++;
            }
            break;
        }
    }
    return *cnt;
}

// TODO Returns a, b, c or d at random.
u32 fn_80012908(void *p, u32 a, u32 b, u32 c, u32 d) {
    u32 r = fn_8000FECC(100);
    if (r < 25) {
        return a;
    }
    if (r < 50) {
        return b;
    }
    if (r < 75) {
        d = c;
    }
    return d;
}

// TODO Returns the 0xA2 value of entry x.
u16 fn_8001370C(Unk8063E970 *p, int x) {
    BattleSystem *battleSys = fn_803AC828();
    BattleContext *battleCtx = BattleSystem_GetBattleContext(battleSys);
    return fn_8000DFC4(p, x, BattleContext_Get(battleSys, battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, x), 0xa2, 0);
}

// TODO Returns the 0xA3 value of entry x.
u16 fn_8001377C(Unk8063E970 *p, int x) {
    BattleSystem *battleSys = fn_803AC828();
    BattleContext *battleCtx = BattleSystem_GetBattleContext(battleSys);
    return fn_8000DFC4(p, x, BattleContext_Get(battleSys, battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, x), 0xa3, 0);
}

// TODO Fills out with the values of each entry.
void fn_800137EC(Unk8063E970 *p, Unk800137EC *out) {
    u16 v;
    BattleSystem *battleSys;
    u8 i;
    u8 n;
    Unk800137EC *o;
    n = p->_003e;
    for (i = 0; i < n; i++) {
        o = &out[i];
        v = fn_8000EA70(p, i);
        if (v == 0 || v == 0xffff) {
            o->_0 = 0;
            o->_2 = 0;
            continue;
        }
        o->_0 = v;
        battleSys = fn_803AC828();
        o->_2 = fn_8000DFC4(
            p,
            i,
            BattleContext_Get(battleSys, BattleSystem_GetBattleContext(battleSys), BATTLECTX_SELECTED_PARTY_SLOT, i),
            0x9f,
            0);
        o->_4 = fn_80391200(lbl_8063CE34, fn_80391FFC(lbl_8063CE34 + 0x10, v));
        o->_5 = fn_803919C4(lbl_8063CE34 + 0x10, v);
        o->_6 = fn_803919F8(lbl_8063CE34 + 0x10, v);
    }
}

// TODO Returns a, b or c at random.
u32 fn_80014E88(void *p, u32 a, u32 b, u32 c) {
    u32 r = fn_8000FECC(100);
    if (r < 0x21) {
        return a;
    }
    if (r < 0x42) {
        c = b;
    }
    return c;
}

// TODO Picks a message for step k and plays it.
// TODO Does not match yet (0x1D8 bytes instead of 0x1F8).
void fn_80014EE8(Unk8063E970 *p, int k, u32 flag) {
    char *str = lbl_80405FC0;
    int id;
    int out;
    if (p->_004c == 0) {
        if (flag == 1) {
            if (k == 0 || k == 1) {
                id = 0x70;
            } else {
                id = fn_8000FECC(100) < 50 ? 0x70 : 0x71;
            }
        } else {
            if (k == 0 || k == 1) {
                id = fn_8000FECC(100) < 50 ? 0x70 : 0x71;
            } else {
                id = fn_8000FECC(100) < 50 ? 0x70 : 0x71;
            }
        }
    } else {
        if (k == 0 || k == 1) {
            id = fn_8000FE58(p, 0x56, 0x57, 0x58, 0x59);
        } else {
            id = fn_80014E88(p, 0x56, 0x58, 0x59);
        }
    }
    out = -1;
    if (!fn_800150E0(p, id, &out)) {
        id = 0;
    }
    if (id) {
        fn_800153A8(p, id, out, k, 0);
        if (fn_80009838() == 1) {
            fn_8000C52C(str + 0x352);
            fn_80015234(p, 0);
        } else {
            if (fn_802568BC(&p->_1070) == 1) {
                fn_8000C52C(str + 0x1250, id);
            } else {
                fn_8000C52C(str + 0x128b, id);
            }
            if (fn_80009838() == 1) {
                fn_8000C52C(str + 0x3de);
                fn_80015234(p, 5);
            }
            fn_800241A8(p, id, 0);
        }
    } else {
        fn_8000C52C(str + 0x12bd);
    }
    p->_2810 = id;
}

// TODO Returns whether message n can be used now.
bool fn_800150E0(Unk8063E970 *p, int n, void *x) {
    if (n <= 0 || n >= 0x26a) {
        return 0;
    }
    return !fn_80023E28(p, n, x) ? false : fn_8001515C(p, n, x) != 0;
}

// TODO Picks a variant of message n at random; returns whether one was picked.
int fn_8001515C(void *p, int n, void *x) {
    int *out = (int *)x;
    u32 r;
    u8 c;
    int i;
    u8 cnt;
    u32 sum;
    if (n <= 0 || n >= 0x26a) {
        return 0;
    }
    *out = -1;
    r = fn_8000FECC(100);
    c = fn_80024B50(n, 0);
    if (c) {
        return r < c;
    }
    {
        cnt = fn_80024AEC(n);
        sum = 0;
        for (i = 1; i < cnt; i++) {
            u8 w = fn_80024B50(n, i);
            if (w) {
                sum += w;
                if (r < sum) {
                    *out = i;
                    return 1;
                }
            }
        }
    }
    return 0;
}

// TODO Stops the sound at 0x1070 and waits for it, with mode.
void fn_80015234(Unk8063E970 *p, int x) {
    int i;
    if (p->_1070._00 != 0) {
        if (x > 0) {
            fn_80256BC0(&p->_1070, x);
            i = 0;
            while (fn_8000B720() == 1) {
                if (fn_80009838() != 1) {
                    if (!(i++ < (int)(lbl_80640688 + lbl_80640690 * lbl_8063D988))) {
                        fn_8000C52C(lbl_804072A2);
                        break;
                    }
                }
                GSthreadManager::sInstance->sleepCurrentThread();
                fn_8000CD70(p);
            }
        }
        i = 0;
        while (fn_80256E24(&p->_1070) == 1) {
            if (fn_80009838() != 1) {
                if (!(i++ < (int)(lbl_80640688 + lbl_80640690 * lbl_8063D988))) {
                    fn_8000C52C(lbl_804072A2);
                    break;
                }
            }
            GSthreadManager::sInstance->sleepCurrentThread();
            fn_8000CD70(p);
        }
        fn_802567E8(&p->_1070);
        p->_106c = 0;
        p->_106f = 0xff;
        fn_80254AD0(fn_802544D0(), 1);
    }
}

// TODO Plays message n, variant sel.
void fn_800153A8(Unk8063E970 *p, int n, int c, int x, int y) {
    int buf1[4];
    int buf2[4];
    u8 m;
    int cnt;
    int i;
    if (n <= 0 || n >= 0x26a) {
        return;
    }
    {
        if (p->_1070._00) {
            if (fn_80256E24(&p->_1070) == 1) {
                fn_8000C52C(lbl_804072BB);
            } else {
                fn_80015234(p, 0);
                fn_8000C52C(lbl_804072BB);
            }
        }
        m = fn_80024AEC(n);
        buf1[0] = 0;
        buf1[1] = 0;
        buf1[2] = 0;
        buf1[3] = 0;
        buf2[0] = 0;
        buf2[1] = 0;
        buf2[2] = 0;
        buf2[3] = 0;
        cnt = 0;
        for (i = 0; i < m; i++) {
            s16 id = fn_80024A70(n, i);
            int v;
            if (i > 0 && c != -1 && fn_80024B50(n, i) && i != c) {
                continue;
            }
            v = fn_8000BC78(id);
            if (v < 0x4a38) {
                buf1[cnt] = v;
                buf2[cnt] = (s16)fn_8000BCA4(id);
            } else {
                fn_80015968(p, v, x, y, &buf1[cnt], &buf2[cnt]);
            }
            cnt++;
        }
        fn_802565C0(&p->_1070, cnt, 0, 0, -1, 0);
        for (i = 0; i < cnt; i++) {
            int v;
            int skip;
            fn_80256850(&p->_1070, i, buf1[i], 0);
            v = buf2[i];
            switch (v) {
                case 0:
                case 1:
                case 0x657:
                case 0xac0:
                case 0x1116:
                case 0x157f: skip = 1; break;
                default:     skip = 0; break;
            }
            if (!skip && v != -1) {
                fn_80254A30(fn_802544D0(), v, 1, 0xC000);
                GSthreadManager::sInstance->sleepCurrentThread();
                fn_8000CD70(p);
            }
        }
    }
}

// TODO Plays the n messages of ids.
void fn_80015608(Unk8063E970 *p, int n, int *a, int *b) {
    int buf[16];
    int l1;
    int l2;
    int cnt;
    int j;
    int i;
    u8 m;
    s16 id;
    if (!n) {
        return;
    }
    if (p->_1070._00) {
        if (fn_80256E24(&p->_1070) == 1) {
            fn_8000C52C(lbl_804072BB);
        } else {
            fn_80015234(p, 0);
            fn_8000C52C(lbl_804072BB);
        }
    }
    cnt = 0;
    for (i = 0; i < n; i++) {
        m = fn_80024AEC(a[i]);
        for (j = 0; j < m; j++) {
            int v;
            id = fn_80024A70(a[i], j);
            v = fn_8000BC78(id);
            if (v < 0x4a38) {
                buf[cnt] = id;
            } else {
                buf[cnt] = fn_80015968(p, v, b[i], 0, &l1, &l2);
            }
            cnt++;
        }
    }
    fn_80015740(p, cnt, buf);
}

// TODO Plays the n sounds of ids.
void fn_80015740(Unk8063E970 *p, int n, int *a) {
    int i;
    s16 v;
    int skip;
    fn_802565C0(&p->_1070, n, 0, 0, -1, 0);
    for (i = 0; i < n; i++) {
        fn_80256850(&p->_1070, i, fn_8000BC78(a[i]), 0);
        v = fn_8000BCA4(a[i]);
        switch (v) {
            case 0:
            case 1:
            case 0x657:
            case 0xac0:
            case 0x1116:
            case 0x157f: skip = 1; break;
            default:     skip = 0; break;
        }
        if (!skip && v != -1) {
            fn_80254A30(fn_802544D0(), v, 1, 0xC000);
            GSthreadManager::sInstance->sleepCurrentThread();
            fn_8000CD70(p);
        }
    }
}

// TODO Appends the sounds of message n to outA and outB.
void fn_8001585C(Unk8063E970 *p, int n, int *a, int *b, u32 *cnt, u32 max) {
    u32 i;
    u8 c;
    if (!fn_80023E28(p, n, a)) {
        return;
    }
    {
        int a = fn_8039394C(lbl_8063E988, n);
        fn_8000C52C(lbl_80407304, (s8)fn_80393918(lbl_8063E988, n), (s16)a);
    }
    c = fn_80024AEC(n);
    if (*cnt + c > max) {
        return;
    }
    for (i = 0; i < c; i++) {
        s16 id = fn_80024A70(n, i);
        a[*cnt] = fn_8000BC78(id);
        b[*cnt] = (s16)fn_8000BCA4(id);
        (*cnt)++;
    }
    fn_800241A8(p, n, 0);
}

// TODO Updates the 0x58 state from the 0x281F and 0x285C values.
void fn_80015D38(Unk8063E970 *p) {
    if (p->_0058 == 0 && p->_281f + p->_2820 > 0) {
        p->_0058 = 1;
        fn_8000C52C(lbl_80407494);
    }
    if (p->_0058 <= 1 && p->_004c >= 3) {
        if (p->_003d == 0) {
            if (p->_285c[0] == 1 || p->_285c[1] == 1) {
                p->_0058 = 2;
                fn_8000C52C(lbl_804074C2);
            }
        } else {
            f32 x = p->_2844[0] + p->_2844[2];
            f32 y = p->_2844[1] + p->_2844[3];
            if ((p->_285c[0] <= 2 && x < lbl_806406A0) || (p->_285c[1] <= 2 && y < lbl_806406A0)) {
                p->_0058 = 2;
                fn_8000C52C(lbl_804074C2);
            }
        }
    }
}

// TODO Ends a step of the object.
void fn_80016580(Unk8063E970 *bp) {
    bp->_9daf = 0xff;
    bp->_9db0 = 0;
    bp->_9db1 = 0;
    bp->_9db2 = 0;
    bp->_281c = 0;
    if (bp->_004c >= 2 && bp->_281f == 0 && bp->_2820 == 0) {
        bp->_281e++;
    } else {
        bp->_281e = 0;
    }
    bp->_2820 = 0;
    bp->_281f = 0;
    bp->_2822 = 0;
    bp->_2821 = 0;
    fn_8000EDB0(bp);
    fn_80016640(bp, 0, 1, bp->_9de0);
    fn_800195A8(bp);
}

// TODO Picks a or b at random, preferring a flag that is not set yet, and sets it.
u32 fn_80017B08(Unk8063E970 *p, u32 a, u32 b) {
    u32 r = fn_8000FECC(100);
    if (r < 50 && !fn_8000BD6C(p, a)) {
        fn_8000C04C(p, a);
        return a;
    }
    if (!fn_8000BD6C(p, b)) {
        fn_8000C04C(p, b);
        return b;
    }
    if (r < 50) {
        b = a;
    }
    return b;
}

// TODO Picks a, b, c or d at random, preferring a flag that is not set yet, and sets it.
u32 fn_80017BB4(Unk8063E970 *p, u32 a, u32 b, u32 c, u32 d) {
    u32 r = fn_8000FECC(100);
    if (r < 25 && !fn_8000BD6C(p, a)) {
        fn_8000C04C(p, a);
        return a;
    }
    if (r < 50 && !fn_8000BD6C(p, b)) {
        fn_8000C04C(p, b);
        return b;
    }
    if (r < 75 && !fn_8000BD6C(p, c)) {
        fn_8000C04C(p, c);
        return c;
    }
    if (!fn_8000BD6C(p, d)) {
        fn_8000C04C(p, d);
        return d;
    }
    if (r < 25) {
        return a;
    }
    if (r < 50) {
        return b;
    }
    if (r < 75) {
        d = c;
    }
    return d;
}

// TODO Returns the 0x18 byte that matches the 0x17 index, or 0xFF.
u8 fn_80017CE8(Unk8000CC84 *p) {
    u8 v = p->_17;
    if (v >= 1 && v <= 4) {
        return (&p->_17)[v + 1];
    }
    return 0xff;
}

// TODO Picks a, b or c at random, preferring a flag that is not set yet, and sets it.
u32 fn_80017D10(Unk8063E970 *p, u32 a, u32 b, u32 c) {
    u32 r = fn_8000FECC(100);
    if (r < 33 && !fn_8000BD6C(p, a)) {
        fn_8000C04C(p, a);
        return a;
    }
    if (r < 66 && !fn_8000BD6C(p, b)) {
        fn_8000C04C(p, b);
        return b;
    }
    if (!fn_8000BD6C(p, c)) {
        fn_8000C04C(p, c);
        return c;
    }
    if (r < 33) {
        return a;
    }
    if (r < 66) {
        c = b;
    }
    return c;
}

// TODO Returns whether the 0x1D value of the entry differs from v with the same parity.
int fn_80019090(Unk8000CC84 *p, u32 v) {
    u8 a = p->_1d;
    int r = 0;
    if (((a + v) & 1) == 0) {
        if (a != v) {
            r = 1;
        }
    }
    return r;
}

// TODO Returns whether one of the values of the entry is 0, 0xD or 0x4C.
int fn_800190B4(Unk8000CC84 *p) {
    u8 i;
    u8 n = lbl_8063E970->_003e;
    for (i = 0; i < n; i++) {
        switch (fn_80019170(p, i)) {
            case 0xd:
            case 0x4c: return 1;
            case 0:    return 1;
        }
    }
    return 0;
}

// TODO Returns the number of set bits among the low four bits of 0x2C.
// TODO Does not match yet (same size; the code differs).
int fn_8001914C(Unk8000CC84 *p) {
    Unk8001914C *b = (Unk8001914C *)&p->_2c;
    return b->b1 + b->b0 + b->b3 + b->b2;
}

// TODO Returns value idx of the entry, or 0 when it is unset or out of range.
u8 fn_80019170(Unk8000CC84 *p, u8 idx) {
    if (p->_3c[idx] & 0x200000) {
        return 0;
    }
    u8 v = p->_4c[idx];
    if (v < 1 || v > 0x7b) {
        fn_8000C52C(lbl_80407AE4);
        return 0;
    }
    return v;
}

// TODO Returns whether v matches the first value of the block of the entry.
int fn_800191D4(Unk8000CC84 *p, int v) {
    switch (p->_04->_96c->_0c[0]) {
        case 0x78: return v == 0x36b;
        case 0x3f:
        case 0x4f: return v == 0x36e;
        case 0x55: return v == 0x371;
        case 0x65: return v == 0x374;
        case 0x2f: return v == 0x377;
        case 0x9c: return v == 0x37a;
    }
    return 0;
}

// TODO Clears p and returns it.
Unk80019380 *fn_8001929C(Unk80019380 *p) {
    p->_00 = 0;
    p->_04 = 0;
    p->_05 = 0;
    p->_06 = 0;
    p->_07 = 0;
    memset(p->_08, 0, 8);
    memset(p->_10, 0, 8);
    memset(p->_18, 0, 4);
    return p;
}

// TODO Clears p.
void fn_80019310(Unk80019380 *p) {
    p->_00 = 0;
    p->_04 = 0;
    p->_05 = 0;
    p->_06 = 0;
    p->_07 = 0;
    memset(p->_08, 0, 8);
    memset(p->_10, 0, 8);
    memset(p->_18, 0, 4);
}

// TODO Fills out from the entries of block q and updates the 0x28C0 flags.
// TODO Does not match yet (same size; the code differs).
void fn_80019380(Unk80019380 *out, u8 k, Unk80035D9C *q) {
    u32 f = lbl_8063E970->_28c0;
    u8 i;
    out->_00 = q;
    out->_04 = k;
    out->_05 = fn_80035F68(q);
    out->_06 = 0;
    out->_07 = 0;
    memset(out->_08, 0, 8);
    for (i = 0; i < out->_05; i++) {
        Unk8000EC58 *e = &q->_96c[i];
        switch (e->_04) {
            case 0x64:
                out->_06++;
                out->_07 |= 1 << e->_00;
                break;
            case 2:
                if (e->_14 > e->_16 && e->_00 <= 3) {
                    out->_08[e->_00] |= 1;
                }
                break;
            case 3:
                if (e->_14 > e->_16 && e->_00 <= 3) {
                    out->_08[e->_00] |= 2;
                }
                break;
            case 0x68:
                if (e->_0c[0] == 0x26e && e->_00 <= 3) {
                    out->_08[e->_00] |= 4;
                }
                break;
            case 0x12: f = 0x8000; break;
            case 0x13: f = 2; break;
            case 0x14: f = 0x80; break;
            case 0x15: f = 8; break;
            case 0x16: f = 0x20; break;
            case 0x74:
            case 0x75:
            case 0x76:
            case 0x77:
            case 0x78: f = 0; break;
        }
    }
    memcpy(out->_10, lbl_8063E970->_2890, 8);
    memcpy(out->_18, lbl_8063E970->_2898, 4);
    lbl_8063E970->_28c0 = f;
}

// TODO Returns whether the 0x12 or 0x18 byte of the entry is set.
int fn_8001A544(Unk8000CC84 *p) {
    return p->_12 != 0 || p->_18[0] != 0;
}

// TODO Returns whether bit n of the low four bits of 0x2C is set.
#pragma push
#pragma optimize_for_size off
int fn_8001D1E0(Unk8000CC84 *p, int n) {
    return (p->_2c & ((1 << n) & 0xF)) != 0;
}
#pragma pop

// TODO Returns the id that matches k.
int fn_8001EBF4(void *p, int k) {
    int r = 0;
    switch (k) {
        case 0xdf:  r = 0x17f; break;
        case 0xe8:  r = 0x180; break;
        case 0xe2:  r = 0x181; break;
        case 0xe5:  r = 0x182; break;
        case 0xd3:  r = 0x183; break;
        case 0xdc:  r = 0x184; break;
        case 0xd9:  r = 0x185; break;
        case 0x43a: r = 0x186; break;
        case 0xd6:  r = 0x187; break;
        default:    fn_8000C52C(lbl_8040803A, k); break;
    }
    return r;
}

// TODO Returns the id that matches a and b.
int fn_8001ECE4(void *p, int a, int b) {
    char *str = lbl_80405FC0;
    int r = 0;
    switch (a) {
        case 0x66:
            switch (b) {
                case 0xe:
                case 0x60:
                case 0x9f:
                case 0xbb:
                case 0xe8:
                case 0x135:
                case 0x150: r = 0x1a7; break;
                case 0x4a:
                case 0x126:
                case 0x1a1:
                case 0x1c3: r = 0x1a8; break;
                case 0x16f: r = 0x1a1; break;
                default:    fn_8000C52C(str + 0x209d, b); break;
            }
            break;
        case 0x67:
            switch (b) {
                case 0x6a:
                case 0x6e:
                case 0x6f:
                case 0x70:
                case 0x97:
                case 0xd3:
                case 0x14e: r = 0x1a9; break;
                case 0x68:  r = 0x1a5; break;
                case 0x85:  r = 0x1aa; break;
                case 0x16f: r = 0x1a1; break;
                case 0x69:
                default:    fn_8000C52C(str + 0x20bf, b); break;
            }
            break;
        case 0x68:
            switch (b) {
                case 0x61:
                case 0x16f:
                case 0x18d: r = 0x1a4; break;
                default:    fn_8000C52C(str + 0x20e3, b); break;
            }
            break;
        case 0x69:
            switch (b) {
                case 0x16f: r = 0x1a6; break;
                default:    fn_8000C52C(str + 0x20e3, b); break;
            }
            break;
        default:
            r = 0;
            fn_8000C52C(str + 0x2106);
            break;
    }
    return r;
}

// TODO Returns the second id that matches a and b.
int fn_8001EF1C(void *p, int a, int b) {
    char *str = lbl_80405FC0;
    int r = 0;
    switch (a) {
        case 0x66:
            switch (b) {
                case 0x153:
                case 0x15b:
                case 0x15d: r = 0x1a1; break;
                default:    fn_8000C52C(str + 0x209d, b); break;
            }
            break;
        case 0x67:
            switch (b) {
                case 0x142:
                case 0x1c7: r = 0x1a1; break;
                default:    fn_8000C52C(str + 0x209d, b); break;
            }
            break;
        case 0x68: fn_8000C52C(str + 0x20e3, b); break;
        case 0x69: fn_8000C52C(str + 0x20e3, b); break;
        default:
            r = 0;
            fn_8000C52C(str + 0x2106);
            break;
    }
    return r;
}

// TODO Queues message 0x196 or 0x198 for entry idx when s asks for it; returns 1 when queued.
// TODO Does not match yet (0x13C bytes instead of 0x140).
int fn_8001FA9C(Unk8063E970 *bp, int idx, Unk8001FA9C *s) {
    u16 w;
    u8 b;
    Unk8000CC84 *e;
    int i;
    e = &bp->_9a58[idx];
    w = e->_20;
    b = e->_1d;
    if (w != 0x104) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        switch (s->_0c[i]) {
            case 0x9c:
                if (s->_00 <= 3) {
                    switch (w) {
                        case 0xcf:
                        case 0x104:
                            if ((u32)fn_800210FC(bp,
                                                 fn_8000FECC(100) < 50 ? 0x196 : 0x198,
                                                 idx,
                                                 b,
                                                 w,
                                                 e->_32[s->_00],
                                                 0xff,
                                                 1) == 1) {
                                return 1;
                            }
                            break;
                        default: fn_8000C52C(lbl_804082E1, w); break;
                    }
                } else {
                    fn_8000C52C(lbl_804082B2);
                }
                break;
            case 0: break;
        }
    }
    return 0;
}

// TODO Updates the entries from start on.
void fn_8001FBDC(Unk8063E970 *bp, u8 start) {
    u8 i;
    for (i = start; i < bp->_9a54; i++) {
        if ((u32)fn_8001A544(&bp->_9a58[i]) == 1) {
            if ((u32)fn_80016EE0(bp, i) != 1) {
                fn_8000C52C(lbl_80407C3D);
            }
        } else if ((bp->_9a58[i]._28 & 1) == 1) {
            fn_8001A56C(bp, i);
        }
    }
}

// TODO Calls fn_8002062C or fn_8001FCAC, from the 0x06 byte of the second 0x9D3C entry.
void fn_8001FC94(Unk8063E970 *p) {
    if (p->_9d3c[1]._06) {
        fn_8002062C(p);
    } else {
        fn_8001FCAC(p);
    }
}

// TODO Stops the queued messages and clears the queue.
void fn_80020BF8(Unk8063E970 *p) {
    u32 r;
    int i;
    if (p->_1070._00 > 0) {
        u32 v = fn_80256890(&p->_1070, 0);
        if (v >= 0x76b && v <= 0x110b) {
            u32 d = v - 0x76b;
            r = d % 5;
            fn_8000C52C(lbl_80408422, d / 5 + 1, r + 1);
            if (r == 2) {
                fn_80015234(p, 0);
            }
        }
    }
    if (p->_2669 < p->_1170) {
        int a = fn_8039394C(lbl_8063E988, p->_1174[p->_2669]);
        s8 b = fn_80393918(lbl_8063E988, p->_1174[p->_2669]);
        fn_8000C52C(lbl_8040844A, p->_2669, b, (s16)a, p->_1174[p->_2669]);
    }
    for (i = 0; i < 0x14; i++) {
        fn_802567E8(&p->_1268[i]);
    }
    fn_80254AD0(fn_802544D0(), 2);
    p->_1170 = 0;
    p->_1264 = 0;
    p->_2668 = -1;
    p->_2669 = 0;
    p->_266c = 0;
}

// TODO Waits for the current queued message, then clears the queue.
void fn_80020D44(Unk8063E970 *p) {
    int i;
    if (p->_1170 != 0) {
        if (p->_2669 < p->_1170) {
            i = 0;
            while (fn_80256E24(&p->_1268[p->_2669]) == 1) {
                if (fn_80009838() != 1) {
                    if (!(i++ < (int)(lbl_80640688 + lbl_80640690 * lbl_8063D988))) {
                        fn_8000C52C(lbl_804072A2);
                        break;
                    }
                }
                GSthreadManager::sInstance->sleepCurrentThread();
                fn_8000CD70(p);
            }
        }
        fn_80020BF8(p);
    }
}

// TODO Plays the queued messages that have not started yet.
void fn_80020E34(Unk8063E970 *p) {
    int i;
    if (p->_1170) {
        for (i = 0; i < p->_1170; i++) {
            if (!(p->_1264 & (1 << i))) {
                fn_80020EB8(p, i);
            }
        }
        fn_8000C52C(lbl_8040848E);
    }
}

// TODO Plays queued message k.
// TODO Does not match yet (0x1FC bytes instead of 0x214).
void fn_80020EB8(Unk8063E970 *p, int k) {
    int buf1[4];
    int buf2[4];
    u8 n;
    int i;
    n = fn_80024AEC(p->_1174[k]);
    for (i = 0; i < n; i++) {
        s16 id = fn_80024A70(p->_1174[k], i);
        buf1[i] = fn_8000BC78(id);
        buf2[i] = (s16)fn_8000BCA4(id);
        if (buf1[i] >= 0x4a38) {
            fn_800213D0(p, buf1[i], p->_1214[k], &buf1[i], &buf2[i]);
        }
    }
    if (p->_1268[k]._00) {
        fn_8000C52C(lbl_804084BD);
    }
    fn_802565C0(&p->_1268[k], n, 0, 0, -1, 0);
    for (i = 0; i < n; i++) {
        int v;
        int skip;
        fn_80256850(&p->_1268[k], i, buf1[i], 0);
        v = buf2[i];
        switch (v) {
            case 0:
            case 1:
            case 0x657:
            case 0xac0:
            case 0x1116:
            case 0x157f: skip = 1; break;
            default:     skip = 0; break;
        }
        if (!skip && v != -1) {
            if (fn_80254A30(fn_802544D0(), v, 2, 0xC000) == 0) {
                fn_802567E8(&p->_1268[k]);
                break;
            }
            GSthreadManager::sInstance->sleepCurrentThread();
            fn_8000CD70(p);
        }
    }
    p->_1264 |= 1 << k;
}

// TODO Plays queued message n when it is the last one.
void fn_800210CC(Unk8063E970 *p, int n) {
    int c = p->_1170;
    if (c <= 0) {
        fn_8000C52C(lbl_804084E6);
        return;
    }
    if (n + 1 == c) {
        fn_80020EB8(p, n);
    }
}

// TODO Queues message id with its parameters; returns 1 when queued.
int fn_800210FC(Unk8063E970 *m, int id, u8 a, u8 b, u16 w, s16 v, u8 e, u32 flag) {
    Unk8063E970 *bp = m;
    int local;
    if (id == 0) {
        return 0;
    }
    if (id >= 0x26a) {
        return 0;
    }
    if (m->_1170 >= 20) {
        return 0;
    }
    if (m->_1070._00 && (u32)fn_800241D4(m, id) == 1) {
        return 0;
    }
    if (flag == 1) {
        if ((id >= 0x72 && id <= 0x9c) || (id >= 0x9d && id <= 0xb4)) {
            int c = m->_1170;
            if (c >= 1) {
                switch (id) {
                    case 0x73:
                    case 0x7c:
                    case 0x7d:
                    case 0x81:
                    case 0x93: {
                        int i;
                        for (i = 0; i < c - 1; i++) {
                            if (id == m->_1174[i]) {
                                if (id != 0x73) {
                                    int s1 = fn_8039394C(lbl_8063E988, id);
                                    fn_8000C52C(lbl_80408508, (s8)fn_80393918(lbl_8063E988, id), (s16)s1, id);
                                }
                                return 0;
                            }
                        }
                        break;
                    }
                }
            }
        } else {
            int c;
            // TODO The original calls fn_80023E28 with two arguments instead of three.
            if (!((int (*)(void *, int))fn_80023E28)(m, id)) {
                return 0;
            }
            if (!fn_8001515C(m, id, &local)) {
                return 0;
            }
            c = m->_1170;
            if (c >= 1 && id == m->_1174[c - 1]) {
                return 0;
            }
            if (b <= 3) {
                Unk8000CC84 *x = bp->_9d2c[b];
                Unk8000CC84 *y = bp->_9bb8[b];
                if (x && y && x->_54 == id && x->_30 == y->_30 && x->_30 <= 5) {
                    return 0;
                }
            }
        }
    }
    m->_1174[m->_1170] = id;
    m->_11c4[m->_1170] = a;
    m->_11d8[m->_1170] = b;
    m->_11ec[m->_1170] = w;
    m->_1214[m->_1170] = v;
    m->_123c[m->_1170] = fn_803939B4(lbl_8063E988, id);
    m->_1250[m->_1170] = e;
    m->_1170++;
    if (a < 4) {
        bp->_9a58[a]._54 = id;
    }
    return 1;
}

// TODO Calls handler idx of lbl_804086FC with arg.
void fn_800217CC(Unk8063E970 *p, int idx, void *arg) {
    if (p->_0000) {
        p->_9dbd++;
        (p->*lbl_804086FC[idx])(arg);
        p->_9dbd--;
    }
}

// TODO Waits up to 30 frames for the step to start.
void fn_8002183C(Unk8063E970 *p) {
    int i;
    if (p->_004c != fn_8016FA3C() || p->_0054 < 2) {
        for (i = 0; i < 0x1e; i++) {
            if (p->_004c == fn_8016FA3C() && p->_0054 >= 2) {
                break;
            }
            GSthreadManager::sInstance->sleepCurrentThread();
        }
        fn_8000C52C(lbl_80408750, i + 1);
        if (i == 0x1e) {
            fn_8000C52C(lbl_80408786);
        }
    }
}

// TODO Waits up to 30 frames for the 0x54 state to reach 4.
void fn_800218E8(Unk8063E970 *p) {
    int i;
    if (p->_0054 < 4) {
        for (i = 0; i < 0x1e; i++) {
            if (p->_0054 >= 4) {
                break;
            }
            GSthreadManager::sInstance->sleepCurrentThread();
        }
        fn_8000C52C(lbl_804087B6, i + 1);
        if (i == 0x1e) {
            fn_8000C52C(lbl_804087EB);
        }
    }
}

// TODO Handles the current event, or starts a new step.
void fn_80021974(Unk8063E970 *bp) {
    Unk80035D9C *x = fn_80035D9C();
    if (fn_80035EA8(x) == 0x1000) {
        fn_8000EC58(bp, x);
    } else if (fn_80035EA8(x) == 0x1001) {
        fn_8000EC58(bp, x);
    } else if (bp->_004c != fn_8016FA3C()) {
        bp->_0054 = 1;
        bp->_9de0 = bp->_9ddc;
    }
}

// TODO Copies the incoming packet and queues the requests it carries.
void fn_80021BA8(Unk8063E970 *bp, int x) {
    int len;
    OSMutex *l;
    u8 *data;
    int off;
    if (bp->_0050 > fn_8016FA3C()) {
        return;
    }
    data = fn_8016F3FC(&len);
    if (len == 0) {
        return;
    }
    fn_8000D780((void **)&l, &bp->_9de4);
    bp->_9ddc++;
    bp->_005d = x >> 28;
    bp->_0060 = x & 0x0FFFFFFF;
    off = bp->_0064 - 4;
    bp->_0064 = len;
    memcpy(bp->_0068, data, len + 2);
    if (bp->_0054 == 4) {
        if ((u32)len >= (u32)(off + 8) && data[off] == 0x15) {
            fn_8000D818(bp, 5, (void *)off, bp->_9ddc);
            fn_800218E8(bp);
        } else if (data[0] == 0x18) {
            int r = fn_800242D0(bp, 4, 0);
            if (r > 0) {
                u8 sl = data[1];
                int r2;
                if (sl <= 3) {
                    bp->_2890[sl] = 0;
                    bp->_2898[sl] = 0xff;
                    bp->_289c[sl] = 0;
                    bp->_28a0[sl] = 0;
                    bp->_28b0[sl] = 0;
                    bp->_28b4[sl] = 0;
                    bp->_28b8[sl] = 0;
                    bp->_28bc[sl] = 0;
                }
                r2 = fn_800242D0(bp, 3, 0);
                if ((u32)r2 == (u32)(r + 4)) {
                    fn_8000D818(bp, 6, (void *)r2, bp->_9ddc);
                    fn_800218E8(bp);
                }
            }
        }
    } else if (bp->_0054 == 3) {
        fn_8000C52C(lbl_804088C5);
    }
    fn_8000D7B8(&l, -1);
}

// TODO Catches the 0x4C step up and starts a new step.
void fn_80021D78(Unk8063E970 *p) {
    if (p->_004c < p->_0050) {
        fn_8000C52C(lbl_804088F0);
        p->_004c = p->_0050;
    }
    fn_8000E06C(p);
}

// TODO Calls fn_8000EAE0 with the fields of x.
void fn_80021DD0(Unk8063E970 *p, u32 x) {
    fn_8000EAE0(p, (x >> 16) & 3, x & 0xFFFF);
}

// TODO Queues request 7 with x and waits for the queue to empty.
void fn_80021DE0(Unk8063E970 *p, void *x) {
    fn_8000D818(p, 7, x, 0);
    while ((int)fn_8000D734(p) > 0) {
        GSthreadManager::sInstance->sleepCurrentThread();
    }
}

// TODO Stores the low half of x in 0x48 when fn_8005F198 allows it.
void fn_80021E34(Unk8063E970 *p, u32 x) {
    if (fn_8011C974()->_001b == 1) {
        int r = fn_8005F198();
        if ((u8)r != 0 && (u8)r != 2 && (u8)r != 0xff) {
            fn_8000C52C(lbl_8040662D, (u8)r);
        }
        if ((u8)r <= 3 && (u8)r == 0) {
            p->_0048 = (u16)x;
        }
    }
}

// TODO Calls handler idx of lbl_80408914 with arg.
void fn_80021EC4(Unk8063E970 *p, int idx, void *arg) {
    if (p->_0000) {
        p->_9dbc++;
        (p->*lbl_80408914[idx])(arg);
        p->_9dbc--;
    }
}

// TODO Handles notification k.
// TODO Does not match yet (0xB0 bytes instead of 0xB4).
void fn_80021F34(Unk8063E970 *bp, int k) {
    fn_8000C52C(lbl_804089BC, k);
    switch (k) {
        case 1:
            if (bp->_9dae == 0) {
                fn_8000D818(bp, 4, 0, 0);
                fn_8000C52C(lbl_804089EA, !(u8)fn_8000BCB0(0) ? lbl_8063D330 : lbl_8063D335);
            }
            bp->_9dae++;
            break;
        case 0: break;
    }
}

// TODO Marks the queued messages that match the current event.
// TODO Does not match yet (0xF8 bytes instead of 0x108).
void fn_80021FE8(Unk8063E970 *p) {
    fn_8000C52C(lbl_80408A04, fn_80035ED8(fn_80035D9C()), fn_80035EA8(fn_80035D9C()));
    if (p->_1170 > 0) {
        Unk80035D9C *q = fn_80035D9C();
        if (q) {
            s8 i;
            for (i = (u8)p->_2668 + 1; i < p->_1170; i++) {
                if (p->_123c[i] == 0x1f && p->_11d8[i] == fn_80035ED8(q) && p->_11ec[i] == fn_80035EA8(q)) {
                    fn_8000C52C(lbl_80408890);
                    p->_2668 = i;
                }
            }
        }
    }
}

// TODO Handles message msg.
// TODO Does not match yet (same size; the code differs).
void fn_800220F0(Unk8063E970 *p, u32 m) {
    u32 b = ((Unk800220F0 *)&m)->b31_28;
    u32 a = (m >> 24) & 0xF;
    u32 k = (m >> 16) & 0xFF;
    u32 v = m & 0xFFFF;
    fn_8000C52C(lbl_80408A51, m >> 28, a, k, v);
    switch (k) {
        case 2:
            if (p->_1070._00 == 0) {
                int s = b & 1;
                int e = 0;
                switch (++p->_28d4[s]) {
                    case 1:
                        if (p->_28d4[!s] == 0) {
                            e = !p->_004c ? 0xb6 : 0xb7;
                        } else {
                            e = 0xba;
                        }
                        break;
                    case 2: e = 0xb9; break;
                }
                if (e) {
                    fn_8000D818(p, 2, (void *)e, s);
                }
            }
            break;
        case 3:
            p->_28d0 = 1;
            if (p->_28cf != 0xff) {
                p->_28cf++;
            }
            if (p->_1070._00 == 0) {
                int flag = 0;
                if (p->_28cf == 1) {
                    Unk80035D9C *x = fn_80035D9C();
                    u8 r;
                    if (!x) {
                        return;
                    }
                    // TODO The cast passes a as a u32, while fn_80036E6C is declared with a u8.
                    r = ((u8 (*)(Unk80035D9C *, u32, int))fn_80036E6C)(x, a, 0);
                    if (r <= 5) {
                        if (p->_2860[b][r] & 0xF8) {
                            flag = 1;
                        } else if (p->_2878[b][r] < 0x21 && p->_2878[b][r] != 0) {
                            flag = 1;
                        }
                    }
                }
                fn_8000D818(p, 3, (void *)v, flag);
            }
            break;
    }
}

// TODO Prints the current event.
void fn_80022B60() {
    fn_8000C52C(lbl_80408D04, fn_80035ED8(fn_80035D9C()));
}

// TODO Prints the current event.
void fn_80022B98() {
    fn_8000C52C(lbl_80408D3C, fn_80035ED8(fn_80035D9C()));
}

// TODO Prints the current event.
void fn_80022BD0() {
    fn_8000C52C(lbl_80408D7D, fn_80035ED8(fn_80035D9C()));
}

// TODO Prints the current event.
void fn_80022C08() {
    fn_8000C52C(lbl_80408DBE, fn_80035ED8(fn_80035D9C()));
}

// TODO Marks the queued messages that match entry e for slot.
void fn_80023790(Unk8063E970 *m, int unused, Unk8000EC58 *e, u8 c) {
    char *str = lbl_80405FC0;
    Unk8063E970 *mi;
    s8 i;
    for (i = m->_2668 + 1; i < m->_1170; i++) {
        if (m->_11ec[i] != 0x1001) {
            continue;
        }
        // TODO The shifted pointer keeps r29 and r30 in the order of the original.
        mi = (Unk8063E970 *)((u8 *)m + i);
        switch (mi->_123c[0]) {
            case 0x22:
                if (c == mi->_1250[0]) {
                    if (e->_14 > e->_16 && e->_00 == mi->_11d8[0]) {
                        fn_8000C52C(str + 0x30b0);
                        m->_2668 = i;
                    } else {
                        fn_8000C52C(str + 0x30eb);
                    }
                }
                break;
            case 0x20:
                if (c == mi->_1250[0]) {
                    switch (e->_04) {
                        case 0xa:
                        case 0xe:
                        case 0x89:
                            if (e->_00 == mi->_11d8[0]) {
                                fn_8000C52C(str + 0x30b0, i);
                                m->_2668 = i;
                            } else {
                                fn_8000C52C(str + 0x311f);
                            }
                            break;
                    }
                }
                break;
            case 0x1e:
                if (c == mi->_1250[0]) {
                    int j;
                    for (j = 0; j < 2; j++) {
                        switch (e->_0c[j]) {
                            case 0x2f:
                            case 0x131:
                            case 0x152:
                            case 0x26e:
                                if (e->_00 == mi->_11d8[0]) {
                                    fn_8000C52C(str + 0x3023, i);
                                    m->_2668 = i;
                                } else {
                                    fn_8000C52C(str + 0x311f);
                                }
                                break;
                            case 0: break;
                        }
                    }
                }
                break;
            case 0x34:
                if (c == mi->_1250[0] && e->_04 == 0x86) {
                    fn_8000C52C(str + 0x2f4f);
                    m->_2668 = i;
                }
                break;
            case 0x35:
                if (e->_04 == 0x87) {
                    fn_8000C52C(str + 0x2f4f);
                    m->_2668 = i;
                }
                break;
        }
    }
}

// TODO Marks the queued messages that match the values of s.
int fn_800239DC(Unk8063E970 *p, Unk80035D9C *x, Unk800239DC *s, void *y) {
    u8 a = fn_80035ED8(x);
    u16 b = fn_80035EA8(x);
    int r = 0;
    if (s->_04) {
        r = fn_80023AB0(p, s->_04, (u32)y, a, b, x);
    }
    if (!r && s->_0c) {
        r = fn_80023BC0(p, s->_0c, y, a, b, x);
    }
    if (!r && s->_10) {
        r = fn_80023BC0(p, s->_10, y, a, b, x);
    }
    return r;
}

// TODO Marks the queued messages that match k and y; returns whether k is handled.
int fn_80023AB0(Unk8063E970 *p, u16 k, u32 y, u8 a, u16 b, Unk80035D9C *x) {
    u32 t = 0;
    s8 i;
    switch (k) {
        case 0: break;
        case 0x8e:
            if (y == 1) {
                t = 0x38;
            }
            break;
        case 0x66:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6a:
        case 0x6b:
        case 0x6c:
        case 0x6d:
            if (y == 0) {
                t = 0x37;
            } else if (y == 1) {
                t = 0x38;
            }
            break;
    }
    if (t) {
        for (i = (u8)p->_2668 + 1; i < p->_1170; i++) {
            int j = i;
            if (t == p->_123c[j] && a == p->_11d8[j] && b == p->_11ec[j]) {
                fn_8000C52C(lbl_80408AB9);
                p->_2668 = i;
            }
        }
    }
    return t != 0;
}

// TODO Prints the current event.
void fn_80023DF0() {
    fn_8000C52C(lbl_80409170, fn_80035ED8(fn_80035D9C()));
}

// TODO Returns whether message id can be queued.
int fn_80023E28(Unk8063E970 *p, int id, void *unused) {
    int r;
    u8 t;
    if (id <= 0 || id >= 0x26a) {
        return 0;
    }
    t = fn_80393980(lbl_8063E988, id);
    r = 0;
    switch (t) {
        case 0: r = 1; break;
        case 0x3b:
            if ((u32)fn_80024178(p, id, 0) == 1) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        case 0x3c:
            if ((u32)fn_80024178(p, id, 0) == 1 || (u32)fn_80024178(p, id, 1) == 1) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        case 0x3d:
            if ((u32)fn_80024178(p, id, 0) == 1 || (u32)fn_80024178(p, id, 1) == 1 || (u32)fn_80024178(p, id, 2) == 1) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        case 0x3e:
            if ((u32)fn_80024178(p, id, 0) == 1 || (u32)fn_80024178(p, id, 1) == 1 || (u32)fn_80024178(p, id, 2) == 1 ||
                (u32)fn_80024178(p, id, 3) == 1) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        case 0x3f:
            if ((u32)fn_80024178(p, id, 0) == 1 || (u32)fn_80024178(p, id, 1) == 1 || (u32)fn_80024178(p, id, 2) == 1 ||
                (u32)fn_80024178(p, id, 3) == 1 || (u32)fn_80024178(p, id, 4) == 1) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        case 0x40: {
            int c = p->_1170;
            r = 1;
            if (c >= 1 && id >= 0xea && id <= 0x1ba) {
                int i;
                for (i = 0; i < c; i++) {
                    if (id == p->_1174[i]) {
                        r = 0;
                        break;
                    }
                }
            }
            break;
        }
        case 0x41:
            if (id == p->_280e || id == p->_2810 || id == p->_2812) {
                r = 0;
            } else {
                r = 1;
                switch (id) {
                    case 0x1cd:
                    case 0x1ce:
                    case 0x1cf:
                        switch (p->_2812) {
                            case 0x1cd:
                            case 0x1ce:
                            case 0x1cf: r = 0; break;
                        }
                        break;
                    case 0x1d0:
                    case 0x1d1:
                        switch (p->_2812) {
                            case 0x1d0:
                            case 0x1d1: r = 0; break;
                        }
                        break;
                }
            }
            break;
        case 0x42: r = 1; break;
    }
    return r;
}

// TODO Returns bit bit of buffer idx.
bool fn_80024178(Unk8063E970 *p, int bit, int idx) {
    u8 *buf = p->_2674[idx];
    return !!(buf[bit >> 3] & (1 << (bit & 7)));
}

// TODO Sets bit bit of buffer idx.
void fn_800241A8(Unk8063E970 *p, int bit, int idx) {
    u8 *buf = p->_2674[idx];
    buf[bit >> 3] |= (1 << (bit & 7));
}

// TODO Returns whether one of the sounds of x is 0x145D to 0x1461.
int fn_800241D4(void *p, int x) {
    u32 i;
    u8 n = fn_80024AEC(x);
    for (i = 0; i < n; i++) {
        switch ((s16)fn_80024A70(x, i)) {
            case 0x145d:
            case 0x145e:
            case 0x145f:
            case 0x1460:
            case 0x1461: return 1;
        }
    }
    return 0;
}

// TODO Returns whether side k is empty or used by an entry.
int fn_80024254(Unk8063E970 *bp, u8 k) {
    int n;
    u8 mask;
    u8 i;
    if (bp->_2890[k] == 0) {
        return 1;
    }
    n = bp->_28dc;
    mask = 1 << k;
    for (i = 0; i < n; i++) {
        Unk8000CC84 *e = &bp->_9a58[i];
        if ((e->_16 & mask) || (e->_18[0] & mask)) {
            return 1;
        }
    }
    return 0;
}

// TODO Returns the offset of the first record of type key in the packet, or -1.
int fn_800242D0(Unk8063E970 *p, u8 k, u32 start) {
    char *str;
    u32 total;
    u32 pos;
    u8 *end;
    u8 *cur;
    total = p->_0064;
    str = lbl_80405FC0;
    cur = p->_0068 + start;
    end = p->_0068 + total;
    pos = start;
    while (cur < end) {
        u8 t = *cur;
        int sz;
        if (k == t) {
            return pos;
        }
        sz = 0;
        switch (t) {
            case 1:  sz = 4; break;
            case 2:  sz = 4; break;
            case 3:  sz = 4; break;
            case 4:  sz = 4; break;
            case 5:  sz = 4; break;
            case 6:  sz = 4; break;
            case 7:  sz = 8; break;
            case 8:  sz = 8; break;
            case 9:  sz = 8; break;
            case 10: sz = 8; break;
            case 11: sz = 4; break;
            case 12: sz = 8; break;
            case 13: sz = 8; break;
            case 14: sz = 8; break;
            case 15: sz = 4; break;
            case 16: sz = 8; break;
            case 17: sz = 8; break;
            case 18: sz = 8; break;
            case 19: sz = 4; break;
            case 20: sz = 4; break;
            case 21: sz = 4; break;
            case 22: sz = 4; break;
            case 23: sz = 4; break;
            case 24: sz = 4; break;
            case 25: sz = 4; break;
            case 26: sz = 4; break;
            case 30: sz = 4; break;
            default:
                fn_8000C52C(str + 0x31ea, t);
                fn_8000C52C(str + 0x1640, start, pos);
                fn_8000C52C(str + 0x165d, total);
                cur = end;
                break;
        }
        cur += sz;
        pos += sz;
    }
    return -1;
}

// TODO Counts the entries of the first step and stores the result in 0x9DB4.
void fn_80024480(Unk8063E970 *bp, Unk80035D9C *x) {
    u8 c0, c1, c2, c3, c4;
    u8 n;
    u8 i;
    if (bp->_0050 > 0) {
        return;
    }
    if (bp->_9db5 < 4) {
        bp->_9db5++;
    }
    if (bp->_9db3 == 1) {
        return;
    }
    fn_8000C52C(lbl_80409258);
    bp->_9db3 = 1;
    c0 = 0;
    c1 = 0;
    c2 = 0;
    c3 = 0;
    c4 = 0;
    n = !fn_80035E58(x) ? 2 : 4;
    for (i = 0; i < n; i++) {
        switch (fn_8000EA70(bp, i)) {
            case 0x17e:
                if (i) {
                    bp->_9db4 = 0;
                    return;
                }
                c0++;
                break;
            case 0x17f:
                if (i) {
                    bp->_9db4 = 0;
                    return;
                }
                c1++;
                break;
            case 0x1cb:
            case 0x1cc: c3++; break;
            case 0xf8:
            case 0x1c1:
            case 0x1c2: c2++; break;
            case 0x89:
            case 0xe9:
            case 0x118:
            case 0x119:
            case 0x11a: c4++; break;
        }
    }
    {
        u8 sum = c0 + c1 + c3 + c2;
        if (sum == 0 || c4 != 0 || c0 >= 2 || c1 >= 2 || c3 >= 2 || c2 >= 2) {
            bp->_9db4 = 0;
            return;
        }
        bp->_9db4 = sum;
    }
}

// TODO Returns 0 while the 0x9DB5 count is below the 0x9DB4 count.
int fn_80024688(Unk8063E970 *p) {
    if (p->_0050 == 0 && p->_9db4 != 0) {
        fn_8000C52C(lbl_80409278, p->_9db5, p->_9db4);
        if (p->_9db5 < p->_9db4) {
            return 0;
        }
    }
    return 1;
}

// TODO Starts the sound of the current event; returns 1 when it is ready.
int fn_80024700() {
    Unk80035D9C *x = fn_80035D9C();
    lbl_8063E978 = 0;
    if (fn_80035EA8(x) == 0x2d) {
        int k = fn_80035ED8(x);
        if (k >= 0 && k <= 3) {
            int n = fn_80036554(x, k, 0, 0);
            if (n >= 1 && n <= 0x1ed) {
                lbl_8063E978 = n + 0x2f;
                if ((u32)fn_8000B31C(n + 0x2f) == 1) {
                    return 1;
                }
            }
        }
    }
    fn_8000C52C(lbl_804092D6);
    return 0;
}

// TODO Plays the sound started by fn_80024700 when it matches n.
int fn_800247AC(u32 n) {
    char *str = lbl_80405FC0;
    int r;
    fn_8000C52C(str + 0x333e, fn_80035ED8(fn_80035D9C()));
    if (n < 1 || n > 0x1ed) {
        if (n != 0x259) {
            fn_8000C52C(str + 0x337c, n);
        }
        return 0;
    }
    if (lbl_8063E978 == 0) {
        fn_8000C52C(str + 0x33b9);
        return 0;
    }
    r = 0;
    if (lbl_8063E978 == n + 0x2f) {
        if (fn_8000B42C(lbl_8063E978) == 1) {
            r = fn_8000B3B4(lbl_8063E978, 0);
        } else {
            fn_8000C52C(str + 0x33dd);
            fn_8000B46C(lbl_8063E978, 0);
        }
    }
    lbl_8063E978 = 0;
    return r;
}

// TODO Starts sound n + 0x2F.
int fn_800248A0(u32 n) {
    if (n < 1 || n > 0x1ed) {
        if (n != 0x259) {
            fn_8000C52C(lbl_8040933C, n);
        }
        return 0;
    }
    return fn_8000B170(n + 0x2f, 0, lbl_80640698);
}

#pragma optimize_for_size off
#pragma dont_inline off
