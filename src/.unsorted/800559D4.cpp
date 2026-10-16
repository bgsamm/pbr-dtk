#include ".unsorted/800559D4.hpp"

#include ".unsorted/8000ADC0.hpp"
#include ".unsorted/8011C974.hpp"
#include "gs/GScache.hpp"
#include "gs/GSfile.hpp"
#include "gs/GSfsys.hpp"
#include "gs/GShierarchyModule.hpp"
#include "gs/GSinput.hpp"
#include "gs/GSmem.hpp"
#include "gs/GSobject.hpp"
#include "gs/GSrender.hpp"
#include "gs/GSscene.hpp"
#include "gs/GSthread.hpp"
#include "gs/render/GSrenderTarget.hpp"
#include "gs/render/GStexture.hpp"
#include "gs/scene/GScamera.hpp"

#include <cstring>
#include <revolution/os/OSFastCast.h>

#include "common.hpp"

// size: unknown
struct Unk8015F690 {
    /* 0x00 */ u8 unk00[0x48];
    /* 0x48 */ s32 _48;
};

// size: 0x8
struct Unk803FB838 {
    /* 0x0 */ u32 _0;
    /* 0x4 */ u32 _4;
};

// size: 0x60
struct Unk803FB820 {
    /* 0x00 */ u32 _00[6];
    /* 0x18 */ Unk803FB838 _18[6];
    /* 0x48 */ u32 _48[6];
};

// TODO Replace with proper imports
extern "C" {
int fn_80253F6C(int, void (*)(), int);
void fn_8005C9C8();
void fn_800E43D0();
void fn_80253DB0(s16, int, int);
u16 fn_80253DD0(s16);
u16 fn_80253DE0(s16);
int fn_80253E8C(s16, int, int, void *);
void fn_8015C4F4(u8, u32);
Unk8015F690 *fn_8015F690();
double fn_8015F7A0();
void fn_8015F758(double);
int fn_8000708C();
u32 fn_80164BA8();
int fn_80164D78();
int fn_80164DA8();
void fn_80177080(u16 *, u16 *, int);
void fn_80253EB4(s16, int, int, int);
int fn_801E07E8();
int fn_80007084();
void fn_80253DF0(s16, int, int);
void fn_80253E10(s16, int, f32);
u32 fn_80391F94(void *, int);
void fn_802503D8(u16, u16 *);
void fn_80176EB4(u16 *, u16 *, int);
void fn_80101C18();
void fn_80226700(u32, u32);
void fn_80226A68(u32);
void fn_8022673C(u32);
u8 SCGetLanguage();
void *fn_802502F4(u16);
void fn_8015C308(int, u16 *);
void fn_80250134(int, int, int, int, int, int);
int fn_80250398(int, int, int);
int fn_803919C4(void *, int);
int fn_803919F8(void *, int);
void fn_80253CCC(u16);
void fn_801E37F0(void *);
void fn_80253F8C(int);
void fn_8005A994();
u16 fn_80253C38(void *, void *, void *, void *, int, int, int, int);
void fn_80253EDC(s16, void *, int, void *);
GStexture *fn_8005AC60(u32, u32);
void fn_8005AF78(GStexture *, Unk80058FD4 *, u32, int);
void fn_80234FE0(GSrender *, f32, f32, f32, f32, f32, f32);
void fn_8025005C(void *);
void fn_8025006C(void *);
void fn_8005C9A8(int);
void fn_8005C9B8(int);
void fn_8005A588();
void fn_80055504();
void fn_8005A450();
void fn_800AA470();
void fn_800F8B04();
void fn_80104354();
void fn_800E9740();
void fn_800E4320();
void fn_8011E1FC();
void fn_8013A930();
void fn_80131CF0();
void fn_801581B8();
void fn_80162790();
void fn_8016281C(int);
void fn_80161164();
u32 fn_8023B330(GSrenderTarget *, u32);
}

extern u16 lbl_8040B088[];
extern u32 lbl_803FB880[][5];
extern const f32 lbl_80640B70;
extern f32 lbl_8063D988;
extern const f32 lbl_80640B6C;
extern const f32 lbl_80640B68;
extern const f32 lbl_80640B60;
extern const f32 lbl_80640B64;
extern const f32 lbl_80640B78;
extern u8 lbl_8063CE34[];
extern u32 lbl_8063F640;
extern const f32 lbl_80640B84;
extern u8 lbl_8063EB6E;
extern const f32 lbl_80640B74;
extern const f32 lbl_80640BA0;
extern const f32 lbl_80640BA4;
extern const f32 lbl_80640B88;
extern const f32 lbl_80640B8C;
extern const f32 lbl_80640B90;
extern void *lbl_8063E908;
extern void *lbl_8063E90C;
extern const f32 lbl_80640BB0;
extern const f32 lbl_80640BB4;
extern const f32 lbl_80640BB8;
extern const f32 lbl_80640BBC;
extern const f32 lbl_80640B7C;
extern const f32 lbl_80640B80;
extern Unk803FB820 lbl_803FB820;

// TODO Loads a pair of message files from an fsys archive; inlined in fn_80058778.
static inline void fn_80058778Inline(u32 fsys, u32 f1, u32 f2) {
    u32 size;
    GSfsys::loadFsys(fsys);
    size = GScache::getCachedFileSize(fsys, f1);
    memcpy(lbl_8063E908, GScache::getCachedFile(fsys, f1), size);
    size = GScache::getCachedFileSize(fsys, f2);
    memcpy(lbl_8063E90C, GScache::getCachedFile(fsys, f2), size);
    GSfsys::fn_80249890(fsys);
    GScache::freeFsysCacheEntries(fsys);
    fn_8025005C(lbl_8063E908);
    fn_8025006C(lbl_8063E90C);
}

// TODO Initializes the game systems: threads, layouts and the three objects of fn_80253C38.
void fn_800559D4() {
    lbl_8063D4A0->_0000 = 0;
    lbl_8063D4A0->_0008.b31 = 0;
    lbl_8063D4A0->_0008.b30 = 0;
    lbl_8063D4A0->_0008.b29 = 0;
    lbl_8063D4A0->_0008.b28 = 0;
    lbl_8063D4A0->_0008.b27 = 1;
    lbl_8063D4A0->_0008.b26 = 0;
    lbl_8063D4A0->_0020 = 0;
    lbl_8063D4A0->_001c = 0;
    lbl_8063D4A0->_0008.b3 = 0;
    lbl_8063D4A0->_0008.b23 = 0;
    lbl_8063D4A0->_0008.b22 = 0;
    lbl_8063D4A0->_0008.b20 = 0;
    lbl_8063D4A0->_0008.b19 = 0;
    lbl_8063D4A0->_0008.b11 = 0;
    lbl_8063D4A0->_0008.b6 = 0;
    lbl_8063D4A0->_1081 = 0;
    lbl_8063D4A0->_107c = 0;
    lbl_8063D4A0->_1080 = 0;
    lbl_8063D4A0->_0008.b3 = 1;
    lbl_8063D4A0->_0008.b23 = 1;
    GSthreadManager::sInstance->createThread(0x9fc78, fn_8005757C, 0, 0x2000, 8, 1);
    fn_8005C9A8(0x80);
    fn_8005C9B8(0x60);
    fn_8005A588();
    GSfsys::loadFsys(0xe);
    fn_80055504();
    GSthreadManager::sInstance->createThread(0x9fbf1, fn_80055EDC, 0, 0x2000, 8, 1);
    GSthreadManager::sInstance->createThread(0xa2c2a, fn_8005606C, 0, 0x2000, 8, 1);
    GSthreadManager::sInstance->createThread(0x9fbfd, fn_80056120, 0, 0x2000, 8, 1);
    fn_8005A450();
    fn_80055EB4(0);
    fn_800AA470();
    fn_800F8B04();
    fn_80104354();
    fn_800E9740();
    fn_800E4320();
    fn_8011E1FC();
    fn_8013A930();
    fn_80131CF0();
    fn_801581B8();
    fn_80162790();
    fn_8016281C(0);
    fn_8016281C(1);
    fn_8016281C(2);
    fn_8016281C(3);
    lbl_8063D4A0->_1040 = fn_80055D98(0xe, 0x1d571a00);
    lbl_8063D4A0->_1044 = fn_80253C38(lbl_8063D4A0->_1040, 0, 0, (void *)fn_800564CC, -1, 1, 1, 0);
    fn_80253DB0(lbl_8063D4A0->_1044, 1, 0);
    fn_80253DF0(lbl_8063D4A0->_1044, 9, 3);
    lbl_8063D4A0->_1048 = fn_80055D98(0xe, 0x21881a00);
    lbl_8063D4A0->_104c =
        fn_80253C38(lbl_8063D4A0->_1048, (void *)fn_8005654C, (void *)fn_800565BC, (void *)fn_80056630, -1, 1, 1, 0);
    fn_80253DB0(lbl_8063D4A0->_104c, 0, 0);
    fn_80253DF0(lbl_8063D4A0->_104c, 9, 2);
    lbl_8063D4A0->_1050 = fn_80055D98(0xe, 0x23881a00);
    lbl_8063D4A0->_1054 =
        fn_80253C38(lbl_8063D4A0->_1050, (void *)fn_800568C0, (void *)fn_8005694C, (void *)fn_80056978, -1, 1, 1, 0);
    fn_80253DB0(lbl_8063D4A0->_1054, 0, 0);
    fn_80253DF0(lbl_8063D4A0->_1054, 9, 2);
    fn_80161164();
}

// TODO Calls fn_8005C9C8.
void fn_80055D94() {
    fn_8005C9C8();
}

// TODO Copies a cached file into a new block of heap 2.
void *fn_80055D98(u32 a, u32 b) {
    u32 size = GScache::getCachedFileSize(a, b);
    void *p = GSmem::allocFromHeapAlignedTop(gUnkHeap2, (size + 0x1f) & ~0x1f, 0x20);
    memcpy(p, GScache::getCachedFile(a, b), size);
    return p;
}

// TODO Allocates a block of heap 2, rounded up to 32 bytes.
void *fn_80055E1C(u32 size) {
    return GSmem::allocFromHeap(gUnkHeap2, (size + 0x1f) & ~0x1f);
}

// TODO Frees a block of heap 2.
void fn_80055E30(void *p) {
    GSmem::freeToHeap(gUnkHeap2, p);
}

// TODO Frame time from _0000, 0 while paused (home menu and others).
f32 fn_80055E3C() {
    if (fn_801E07E8()) {
        return lbl_80640B60;
    }
    if (fn_80007084()) {
        return lbl_80640B60;
    }
    if (GSrender::sInstance->getHomeMenuActive()) {
        return lbl_80640B60;
    }
    return lbl_8063D4A0->_0000 / lbl_80640B64 / lbl_80640B64;
}

// TODO Sets flag bit 31.
void fn_80055EB4(int x) {
    lbl_8063D4A0->_0008.b31 = x;
}

// TODO Asks the second worker thread to call fn_80101C18.
void fn_80055EC8() {
    lbl_8063D4A0->_0008.b28 = 1;
}

// TODO Thread measuring the frame time and running the two countdowns.
void *fn_80055EDC(void *arg) {
    OSTime t;
    int last;
    t = OSGetTime();
    last = 0;
    OSInitFastCast();
    while (TRUE) {
        lbl_8063D4A0->_0000 = OSTicksToMicroseconds((u64)(OSGetTime() - t));
        t = OSGetTime();
        if (lbl_8063D4A0->_0008.b31) {
            fn_800561B0();
        }
        if (!lbl_8063D4A0->_0008.b5 && lbl_8063D4A0->_0008.b10 && lbl_8063D4A0->_1088 < lbl_8063D4A0->_108c) {
            lbl_8063D4A0->_1088 += fn_80055E3C();
        }
        if (!lbl_8063D4A0->_0008.b4 && lbl_8063D4A0->_0008.b8 && lbl_8063D4A0->_1090 < lbl_8063D4A0->_1094) {
            int rem;
            lbl_8063D4A0->_1090 += fn_80055E3C();
            rem = lbl_8063D4A0->_1094 - lbl_8063D4A0->_1090;
            if ((u16)rem <= 5 && (u16)last != (u16)rem && (u16)rem != 0) {
                last = rem;
                fn_8000B170(0x234, 0, lbl_80640B68);
            }
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }
}

// TODO Worker thread serving the requests of flag bits 30 and 29.
void *fn_8005606C(void *arg) {
    OSInitFastCast();
    while (TRUE) {
        if (lbl_8063D4A0->_0008.b30) {
            fn_80226700(lbl_8063F640, lbl_8063D4A0->_0010);
            fn_80226A68(lbl_8063F640);
            *lbl_8063D4A0->_0014 = lbl_8063D4A0->_0018;
            lbl_8063D4A0->_0008.b30 = 0;
        }
        if (lbl_8063D4A0->_0008.b29) {
            fn_8022673C(lbl_8063F640);
            lbl_8063D4A0->_0008.b29 = 0;
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }
}

// TODO Worker thread serving the requests of flag bits 28 and 26.
void *fn_80056120(void *arg) {
    OSInitFastCast();
    while (TRUE) {
        if (lbl_8063D4A0->_0008.b28) {
            fn_80101C18();
            lbl_8063D4A0->_0008.b28 = 0;
        }
        if (lbl_8063D4A0->_0008.b26) {
            fn_800576AC();
            lbl_8063D4A0->_0008.b26 = 0;
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }
}

// TODO Advances the value of fn_8015F758 by one frame.
void fn_800561B0() {
    double a = fn_8015F7A0();
    fn_8015F758(a + fn_80055E3C());
}

// TODO Puts object _1044 in state 2 unless it already is.
void fn_800561E8() {
    if (fn_80253DE0(lbl_8063D4A0->_1044) != 2) {
        fn_80253DB0(lbl_8063D4A0->_1044, 2, 0);
    }
}

// TODO Puts object _1044 back in state 0 when fn_80253DE0 is set.
void fn_80056230() {
    if (fn_80253DE0(lbl_8063D4A0->_1044)) {
        fn_80253DB0(lbl_8063D4A0->_1044, 0, 0);
    }
}

// TODO Same as fn_800561E8.
void fn_80056274() {
    if (fn_80253DE0(lbl_8063D4A0->_1044) != 2) {
        fn_80253DB0(lbl_8063D4A0->_1044, 2, 0);
    }
}

// TODO Puts object _1044 in state 0.
void fn_800562BC() {
    fn_80253DB0(lbl_8063D4A0->_1044, 0, 0);
}

// TODO Puts object _1044 in state 5.
void fn_800562D0() {
    fn_80253DB0(lbl_8063D4A0->_1044, 5, 0);
}

// TODO Puts object _1044 in state 4.
void fn_800562E4() {
    fn_80253DB0(lbl_8063D4A0->_1044, 4, 0);
}

// TODO Whether object _1044 is in state 3.
BOOL fn_800562F8() {
    return fn_80253DD0(lbl_8063D4A0->_1044) == 3;
}

// TODO Puts object _1044 in state 1.
void fn_80056330() {
    fn_80253DB0(lbl_8063D4A0->_1044, 1, 0);
}

// TODO Puts object _1044 in state 3.
void fn_80056344() {
    fn_80253DB0(lbl_8063D4A0->_1044, 3, 0);
}

// TODO Sets the options read by the callbacks of object _104c.
void fn_80056358(int a, int b, int c, int d, int e) {
    u32 w;
    lbl_8063D4A0->_0008.b22 = a;
    lbl_8063D4A0->_0008.b21 = b;
    lbl_8063D4A0->_0008.b20 = c;
    lbl_8063D4A0->_0008.b18_15 = d;
    lbl_8063D4A0->_0008.b19 = e;
    w = lbl_8063D4A0->_000c_word;
    w &= ~0x40000000;
    lbl_8063D4A0->_000c_word = w;
    lbl_8063D4A0->_000c.b31 = w >> 30;
}

// TODO Sets flag bit 6.
void fn_800563CC(int x) {
    lbl_8063D4A0->_0008.b6 = x;
}

// TODO Sets _1081.
void fn_800563E0(u8 x) {
    lbl_8063D4A0->_1081 = x;
}

// TODO Calls fn_8000B170 on id, unless fn_8000B4C0 says it is already set.
void fn_800563EC(int id, int x) {
    if (x) {
        fn_8000B170(id, 0, lbl_80640B68);
    } else if (fn_8000708C() && !fn_8000B4C0(id)) {
        fn_8000B170(id, 0, lbl_80640B68);
    }
}

// TODO Calls fn_8000B570 with a value or 0.
void fn_80056458(int x) {
    if (x) {
        fn_8000B570(lbl_80640B6C + lbl_80640B70 * lbl_8063D988);
    } else {
        fn_8000B570(0);
    }
}

// TODO Sets _1084.
void fn_800564AC(u32 x) {
    lbl_8063D4A0->_1084 = x;
}

// TODO Sets _1080 and _107c.
void fn_800564B8(u8 a, u32 b) {
    lbl_8063D4A0->_1080 = a;
    lbl_8063D4A0->_107c = b;
}

// TODO Callback of object _1044; sends the pending request of _107c.
void fn_800564CC() {
    if (lbl_8063D4A0->_107c) {
        fn_8015C4F4(lbl_8063D4A0->_1080, lbl_8063D4A0->_107c);
        lbl_8063D4A0->_107c = 0;
    }
}

// TODO Sends request 9 with _1084 when it is set.
void fn_8005650C() {
    u32 v = lbl_8063D4A0->_1084;
    if (v) {
        fn_8015C4F4(9, v);
    }
}

// TODO Sets bit 30 of _000c.
void fn_80056528() {
    u32 w = lbl_8063D4A0->_000c_word;
    w |= 0x40000000;
    lbl_8063D4A0->_000c_word = w;
    lbl_8063D4A0->_000c.b31 = w >> 30;
}

// TODO Callback of object _104c.
void fn_8005654C() {
    if (lbl_8063D4A0->_0008.b22) {
        lbl_8063D4A0->_1058 = fn_80164BA8();
    }
    if (lbl_8063D4A0->_0008.b19) {
        if (!fn_80164D78() && fn_80164DA8() == 1) {
            lbl_8063D4A0->_0008.b19 = 0;
        }
    }
}

// TODO Second callback of object _104c.
void fn_800565BC(s16 a, int b) {
    int tmp;
    fn_80253E8C(a, b, 3, &tmp);
    switch (tmp) {
        case 2:
            if (!lbl_8063D4A0->_0008.b20) {
                fn_80253EB4(a, b, 1, 0);
            }
            break;
    }
}

// TODO Third callback of object _104c.
void fn_80056630(s16 a, Unk80056630 *o) {
    int st;
    f32 buf[8];
    fn_80253EDC(a, o, 3, &st);
    switch (st) {
        case 3:
            if (lbl_8063D4A0->_000c.b31) {
                o->_48 += lbl_80640B74;
                o->_4c += lbl_80640B74;
                o->_50 += lbl_80640B74;
                o->_54 += lbl_80640B74;
                lbl_8063D4A0->_000c.b31 = 0;
            }
            if (lbl_8063D4A0->_0008.b20) {
                u32 color;
                int x;
                int y, w, h;
                fn_80253EDC(a, o, 6, buf);
                x = buf[0];
                y = buf[4];
                w = buf[1] - buf[0];
                h = buf[6] - buf[4];
                color = o->_11 | 0xffffff00;
                fn_8015C308(8, (u16 *)lbl_8063D4A0->_0008.b18_15);
                fn_80250134(0x3ed, x, y, (s16)w, (s16)h, color);
            }
            break;
        case 2:
            if (lbl_8063D4A0->_000c.b30) {
                o->_48 += lbl_80640B74;
                o->_4c += lbl_80640B74;
                o->_50 += lbl_80640B74;
                o->_54 += lbl_80640B74;
                lbl_8063D4A0->_000c.b30 = 0;
            }
            break;
        case 0:
        case 1:
            if (((u32)st == 1 && lbl_8063D4A0->_0008.b21) || (st == 0 && !lbl_8063D4A0->_0008.b21)) {
                switch (lbl_8063D4A0->_1058) {
                    case 0:  lbl_8063D4A0->_0008.b14_12 = 0; break;
                    case 1:  lbl_8063D4A0->_0008.b14_12 = 1; break;
                    case 2:  lbl_8063D4A0->_0008.b14_12 = 2; break;
                    case 3:  lbl_8063D4A0->_0008.b14_12 = 3; break;
                    default: lbl_8063D4A0->_0008.b14_12 = 7; break;
                }
                fn_80253EDC(a, o, 6, lbl_8063D4A0->_105c);
            }
            break;
    }
}

// TODO Callback of object _1054.
void fn_800568C0(s16 a) {
    fn_80253DF0(a, 8, lbl_8063D4A0->_0008.b6);
    if (lbl_8063D4A0->_0008.b6) {
        switch (lbl_8063D4A0->_1081) {
            case 0: fn_80253E10(a, 4, lbl_80640B60); break;
            case 1: fn_80253E10(a, 4, lbl_80640B78); break;
        }
    }
}

// TODO Second callback of object _1054.
int fn_8005694C(int a, int b) {
    u32 tmp;
    return fn_80253E8C(a, b, 3, &tmp);
}

// TODO Empty; third callback of object _1054.
void fn_80056978() {}

// TODO Copies the nickname of a BoxPokemon into the next of the 64 name buffers.
u16 *fn_8005697C(BoxPokemon *p) {
    u16 buf[32];
    BoxPokemon_GetValue(p, MON_DATA_NICKNAME, buf);
    fn_80177080(lbl_8063D4A0->_003c[lbl_8063D4A0->_103c & 0x3f], buf, 0x20);
    lbl_8063D4A0->_103c++;
    return lbl_8063D4A0->_003c[(lbl_8063D4A0->_103c - 1) & 0x3f];
}

// TODO Copies the nickname of a Pokemon into the next of the 64 name buffers.
u16 *fn_800569EC(Pokemon *p) {
    u16 buf[32];
    Pokemon_GetValue(p, MON_DATA_NICKNAME, buf);
    fn_80177080(lbl_8063D4A0->_003c[lbl_8063D4A0->_103c & 0x3f], buf, 0x20);
    lbl_8063D4A0->_103c++;
    return lbl_8063D4A0->_003c[(lbl_8063D4A0->_103c - 1) & 0x3f];
}

// TODO Gender of a BoxPokemon for display: 0, 1, or 2 when none is shown.
u8 fn_80056A5C(BoxPokemon *p) {
    if (!fn_80056BD4(p)) {
        return 2;
    }
    if (BoxPokemon_GetValue(p, MON_DATA_SANITY_IS_EGG, NULL)) {
        return 2;
    }
    if (!BoxPokemon_GetValue(p, MON_DATA_NO_PRINT_GENDER, NULL)) {
        return 2;
    }
    switch ((u16)BoxPokemon_GetValue(p, MON_DATA_GENDER, NULL)) {
        case 0:  return 0;
        case 1:  return 1;
        default: return 2;
    }
}

// TODO Gender of a Pokemon for display: 0, 1, or 2 when none is shown.
u8 fn_80056B18(Pokemon *p) {
    if (!fn_80056C4C(p)) {
        return 2;
    }
    if (Pokemon_GetValue(p, MON_DATA_SANITY_IS_EGG, NULL)) {
        return 2;
    }
    if (!Pokemon_GetValue(p, MON_DATA_NO_PRINT_GENDER, NULL)) {
        return 2;
    }
    switch ((u16)Pokemon_GetValue(p, MON_DATA_GENDER, NULL)) {
        case 0:  return 0;
        case 1:  return 1;
        default: return 2;
    }
}

// TODO Whether a BoxPokemon holds a valid species.
int fn_80056BD4(BoxPokemon *p) {
    u16 v;
    if (p == 0) {
        return 0;
    }
    v = BoxPokemon_GetValue(p, MON_DATA_SPECIES, NULL);
    if (v == 0 || v > 0x1ef) {
        return 0;
    }
    if (BoxPokemon_GetValue(p, MON_DATA_SPECIES_EXISTS, NULL)) {
        return 1;
    }
    return 0;
}

// TODO Whether a Pokemon holds a valid species.
int fn_80056C4C(Pokemon *p) {
    u16 v;
    if (p == 0) {
        return 0;
    }
    v = Pokemon_GetValue(p, MON_DATA_SPECIES, NULL);
    if (v == 0 || v > 0x1ef) {
        return 0;
    }
    if (Pokemon_GetValue(p, MON_DATA_SPECIES_EXISTS, NULL)) {
        return 1;
    }
    return 0;
}

// TODO Species name string of a BoxPokemon, with the egg cases.
void *fn_80056CC4(BoxPokemon *p) {
    if (!fn_80056BD4(p)) {
        return fn_802502F4(10);
    } else if (BoxPokemon_GetValue(p, MON_DATA_SANITY_IS_EGG, NULL)) {
        if (BoxPokemon_GetValue(p, MON_DATA_CHECKSUM_FAILED, NULL)) {
            return fn_802502F4(0x1f9);
        } else {
            return fn_802502F4(0x1f8);
        }
    } else {
        return fn_802502F4(fn_80391F94(lbl_8063CE34 + 0x10, BoxPokemon_GetValue(p, MON_DATA_SPECIES, NULL)));
    }
}

// TODO Species name string of a Pokemon, with the egg cases.
void *fn_80056D78(Pokemon *p) {
    if (!fn_80056C4C(p)) {
        return fn_802502F4(10);
    } else if (Pokemon_GetValue(p, MON_DATA_SANITY_IS_EGG, NULL)) {
        if (Pokemon_GetValue(p, MON_DATA_CHECKSUM_FAILED, NULL)) {
            return fn_802502F4(0x1f9);
        } else {
            return fn_802502F4(0x1f8);
        }
    } else {
        return fn_802502F4(fn_80391F94(lbl_8063CE34 + 0x10, Pokemon_GetValue(p, MON_DATA_SPECIES, NULL)));
    }
}

// TODO Whether a valid BoxPokemon is an egg.
BOOL fn_80056E2C(BoxPokemon *p) {
    if (!fn_80056BD4(p)) {
        return 0;
    }
    if (BoxPokemon_GetValue(p, MON_DATA_SANITY_IS_EGG, NULL)) {
        return 1;
    }
    return 0;
}

// TODO Whether a valid Pokemon is an egg.
BOOL fn_80056E84(Pokemon *p) {
    if (fn_80056C4C(p) == 0) {
        return 0;
    }
    return (u32)Pokemon_GetValue(p, MON_DATA_SANITY_IS_EGG, NULL) != 0;
}

// TODO Whether a valid BoxPokemon failed its checksum.
BOOL fn_80056EDC(BoxPokemon *p) {
    if (!fn_80056BD4(p)) {
        return 0;
    }
    if (BoxPokemon_GetValue(p, MON_DATA_CHECKSUM_FAILED, NULL)) {
        return 1;
    }
    return 0;
}

// TODO Calls fn_80056F68 on the BoxPokemon of a Pokemon.
void fn_80056F34(int a, int b) {
    fn_80056F68(Pokemon_GetBoxPokemon((Pokemon *)a), b);
}

// TODO Form-dependent value of a BoxPokemon (Arceus and Unown forms).
int fn_80056F68(BoxPokemon *p, int b) {
    int v = BoxPokemon_GetValue(p, MON_DATA_SPECIES, NULL);
    if (v == 0x1ed) {
        switch (BoxPokemon_GetValue(p, MON_DATA_FORM, NULL)) {
            case 1:  return 1;
            case 2:  return 2;
            case 3:  return 3;
            case 4:  return 4;
            case 5:  return 5;
            case 6:  return 6;
            case 7:  return 7;
            case 8:  return 8;
            case 10: return 10;
            case 11: return 11;
            case 12: return 12;
            case 13: return 13;
            case 14: return 14;
            case 15: return 15;
            case 16: return 16;
            case 17: return 17;
            default: return 0;
        }
    } else if (b == 0) {
        return fn_803919C4(lbl_8063CE34 + 0x10, v);
    } else if (v == 0x19d) {
        switch (BoxPokemon_GetValue(p, MON_DATA_FORM, NULL)) {
            case 0:
            default: return 12;
            case 1:  return 4;
            case 2:  return 8;
        }
    } else {
        return fn_803919F8(lbl_8063CE34 + 0x10, v);
    }
}

// TODO Writes the met data and original trainer of q into a BoxPokemon.
void fn_800570E8(BoxPokemon *p, Unk800570E8 *q) {
    u32 tmp;
    u16 buf[20];
    tmp = 0;
    BoxPokemon_SetValue(p, MON_DATA_EGG_LOCATION, &tmp);
    BoxPokemon_SetValue(p, MON_DATA_FATEFUL_ENCOUNTER, &tmp);
    tmp = 0x37;
    BoxPokemon_SetValue(p, MON_DATA_MET_LOCATION, &tmp);
    tmp = 0x10;
    BoxPokemon_SetValue(p, MON_DATA_MET_GAME, &tmp);
    tmp = q->_0;
    BoxPokemon_SetValue(p, MON_DATA_MET_YEAR, &tmp);
    tmp = q->_2;
    BoxPokemon_SetValue(p, MON_DATA_MET_MONTH, &tmp);
    tmp = q->_4;
    BoxPokemon_SetValue(p, MON_DATA_MET_DAY, &tmp);
    tmp = q->_6;
    BoxPokemon_SetValue(p, MON_DATA_MET_LEVEL, &tmp);
    tmp = q->_8;
    BoxPokemon_SetValue(p, MON_DATA_OT_ID, &tmp);
    fn_80176EB4(buf, q->_c, 0x10);
    BoxPokemon_SetValue(p, MON_DATA_OT_NAME, buf);
}

// TODO Restores the PP of the moves of a Pokemon.
void fn_80057208(Pokemon *p) {
    u32 tmp;
    if (fn_80056C4C(p)) {
        if (Pokemon_GetValue(p, MON_DATA_MOVE1, NULL)) {
            tmp = Pokemon_GetValue(p, MON_DATA_MOVE1_MAX_PP, NULL);
            Pokemon_SetValue(p, MON_DATA_MOVE1_PP, &tmp);
        }
        if (Pokemon_GetValue(p, MON_DATA_MOVE2, NULL)) {
            tmp = Pokemon_GetValue(p, MON_DATA_MOVE2_MAX_PP, NULL);
            Pokemon_SetValue(p, MON_DATA_MOVE2_PP, &tmp);
        }
        if (Pokemon_GetValue(p, MON_DATA_MOVE3, NULL)) {
            tmp = Pokemon_GetValue(p, MON_DATA_MOVE3_MAX_PP, NULL);
            Pokemon_SetValue(p, MON_DATA_MOVE3_PP, &tmp);
        }
        if (Pokemon_GetValue(p, MON_DATA_MOVE4, NULL)) {
            tmp = Pokemon_GetValue(p, MON_DATA_MOVE4_MAX_PP, NULL);
            Pokemon_SetValue(p, MON_DATA_MOVE4_PP, &tmp);
        }
    }
}

// TODO Restores the PP of the moves of a BoxPokemon.
void fn_8005732C(BoxPokemon *p) {
    u32 tmp;
    if (fn_80056BD4(p)) {
        if (BoxPokemon_GetValue(p, MON_DATA_MOVE1, NULL)) {
            tmp = BoxPokemon_GetValue(p, MON_DATA_MOVE1_MAX_PP, NULL);
            BoxPokemon_SetValue(p, MON_DATA_MOVE1_PP, &tmp);
        }
        if (BoxPokemon_GetValue(p, MON_DATA_MOVE2, NULL)) {
            tmp = BoxPokemon_GetValue(p, MON_DATA_MOVE2_MAX_PP, NULL);
            BoxPokemon_SetValue(p, MON_DATA_MOVE2_PP, &tmp);
        }
        if (BoxPokemon_GetValue(p, MON_DATA_MOVE3, NULL)) {
            tmp = BoxPokemon_GetValue(p, MON_DATA_MOVE3_MAX_PP, NULL);
            BoxPokemon_SetValue(p, MON_DATA_MOVE3_PP, &tmp);
        }
        if (BoxPokemon_GetValue(p, MON_DATA_MOVE4, NULL)) {
            tmp = BoxPokemon_GetValue(p, MON_DATA_MOVE4_MAX_PP, NULL);
            BoxPokemon_SetValue(p, MON_DATA_MOVE4_PP, &tmp);
        }
    }
}

// TODO Resets the nickname of a BoxPokemon to its species name.
void fn_80057450(BoxPokemon *p) {
    u32 z;
    u16 buf2[32];
    u16 buf1[32];
    fn_802503D8(fn_80391F94(lbl_8063CE34 + 0x10, BoxPokemon_GetValue(p, MON_DATA_SPECIES, NULL)), buf2);
    fn_80176EB4(buf1, buf2, 0x20);
    BoxPokemon_SetValue(p, MON_DATA_NICKNAME, buf1);
    z = 0;
    BoxPokemon_SetValue(p, MON_DATA_HAS_NICKNAME, &z);
}

// TODO Shows the gender symbol of a BoxPokemon in an object of fn_80253C38.
void fn_800574DC(s16 a, int b, BoxPokemon *c) {
    int id;
    switch (fn_80056A5C(c)) {
        case 0:  id = 0xe8d; break;
        case 1:  id = 0xe90; break;
        default: return;
    }
    fn_80253EB4(a, b, 2, id);
}

// TODO Empty.
void fn_80057558() {}

// TODO Flag bit 3.
u32 fn_8005755C() {
    return lbl_8063D4A0->_0008.b3;
}

// TODO Flag bit 23.
u32 fn_8005756C() {
    return lbl_8063D4A0->_0008.b23;
}

// TODO Thread copying the trainer and menu archives to NAND.
void *fn_8005757C(void *arg) {
    while (!lbl_8063D4A0->_0008.b27) {
        GSthreadManager::sInstance->sleepCurrentThread();
    }
    lbl_8063EB6E = 0;
    GSfile::copyFileToNand("mn_tr_10.fsys");
    GSfile::copyFileToNand("mc_tr_10.fsys");
    GSfile::copyFileToNand("mt_tr_10.fsys");
    GSfile::copyFileToNand("fn_tr_10.fsys");
    GSfile::copyFileToNand("fc_tr_10.fsys");
    GSfile::copyFileToNand("fm_tr_10.fsys");
    GSfile::copyFileToNand("mn_tr_00.fsys");
    GSfile::copyFileToNand("mc_tr_00.fsys");
    GSfile::copyFileToNand("mt_tr_00.fsys");
    GSfile::copyFileToNand("fn_tr_00.fsys");
    GSfile::copyFileToNand("fc_tr_00.fsys");
    GSfile::copyFileToNand("fm_tr_00.fsys");
    lbl_8063D4A0->_0008.b3 = 0;
    while (!lbl_8063EB6E) {
        GSthreadManager::sInstance->sleepCurrentThread();
    }
    GSfile::copyFileToNand("menu_face.fsys");
    GSfile::copyFileToNand("menu_pokemon.fsys");
    lbl_8063D4A0->_0008.b23 = 0;
    GSthreadManager::sInstance->stopThread(0x9fc78);
    return 0;
}

// TODO Asks the second worker thread to call fn_800576AC.
void fn_80057688() {
    lbl_8063D4A0->_0008.b26 = 1;
}

// TODO Flag bit 26.
u32 fn_8005769C() {
    return lbl_8063D4A0->_0008.b26;
}

// TODO Calls fn_800E43D0.
void fn_800576AC() {
    fn_800E43D0();
}

// TODO Loads the two scenes and the layout of archive 0x401.
void fn_800576B0() {
    GSsceneData *d;
    GSobject *o;
    lbl_8063D4A0->_0008.b25_24 = 0;
    if (!lbl_8063D4A0->_001c) {
        GSfsys::loadFsys(0x401);
        lbl_8063D4A0->_001c = fn_80055D98(0x401, 0x44a0000);
        d = (GSsceneData *)lbl_8063D4A0->_001c;
        fn_801E34DC(d, (u32)d);
        lbl_8063D4A0->_0028 = new GSscene(d);
        lbl_8063D4A0->_0030 = 0;
        o = lbl_8063D4A0->_0028->getObject(0);
        if (o) {
            GShierarchyModule::fn_80200858(o);
        }
        lbl_8063D4A0->_0020 = fn_80055D98(0x401, 0x1b9b1a00);
        lbl_8063D4A0->_0034 = fn_80253C38(lbl_8063D4A0->_0020, 0, 0, 0, -1, 0, 1, 0);
        fn_80253DF0((s16)lbl_8063D4A0->_0034, 10, 1);
        lbl_8063D4A0->_0024 = fn_80055D98(0x401, 0x23800000);
        d = (GSsceneData *)lbl_8063D4A0->_0024;
        fn_801E34DC(d, (u32)d);
        lbl_8063D4A0->_002c = new GSscene(d);
        o = lbl_8063D4A0->_002c->getObject(0);
        if (o) {
            GShierarchyModule::fn_80200858(o);
        }
        GSfsys::fn_80249890(0x401);
        GScache::freeFsysCacheEntries(0x401);
    }
}

// The callees are not inlined in the original.
#pragma dont_inline on
// TODO Releases what fn_800576B0 loaded.
void fn_800578BC() {
    switch (lbl_8063D4A0->_0008.b25_24) {
        case 2: fn_80057FB4(2); break;
        case 3: fn_80057FB4(3); break;
    }
    if (lbl_8063D4A0->_0028) {
        delete lbl_8063D4A0->_0028;
        lbl_8063D4A0->_0028 = 0;
        lbl_8063F410->_40d = 0;
    }
    if (lbl_8063D4A0->_002c) {
        delete lbl_8063D4A0->_002c;
        lbl_8063D4A0->_002c = 0;
    }
    if (!lbl_8063D4A0->_0030) {
        GShierarchyModule::setCurrentScene(lbl_8063D4A0->_0030);
    }
    lbl_8063D4A0->_0030 = 0;
    fn_80253CCC(lbl_8063D4A0->_0034);
    if (lbl_8063D4A0->_001c) {
        fn_801E37F0(lbl_8063D4A0->_001c);
        fn_80055E30(lbl_8063D4A0->_001c);
    }
    if (lbl_8063D4A0->_0020) {
        fn_80055E30(lbl_8063D4A0->_0020);
    }
    if (lbl_8063D4A0->_0024) {
        fn_801E37F0(lbl_8063D4A0->_0024);
        fn_80055E30(lbl_8063D4A0->_0024);
    }
    lbl_8063D4A0->_001c = 0;
    lbl_8063D4A0->_0020 = 0;
    lbl_8063D4A0->_0024 = 0;
}
#pragma dont_inline reset

// TODO Switches the display to the layout (1) or to one of the two scenes (2, 3).
void fn_800579FC(int mode) {
    Unk80242A00 *rt = (Unk80242A00 *)GSrenderTarget::findTarget(2);
    switch (mode) {
        case 1:
            if (lbl_8063D4A0->_0008.b25_24 == 1) {
                break;
            }
            if (lbl_8063D4A0->_0008.b25_24 == 2) {
                Unk80242A00 *rt2 = (Unk80242A00 *)GSrenderTarget::findTarget(2);
                GSobject *o;
                u32 v;
                if (rt2 && (v = lbl_8063D4A0->_0038) != 0) {
                    rt2->_20 = 0;
                    rt2->_c = v;
                }
                o = lbl_8063D4A0->_0028->getObject(0);
                if (o) {
                    GShierarchyModule::fn_80200858(o);
                }
                GShierarchyModule::setCurrentScene(lbl_8063D4A0->_0030);
                lbl_8063F410->_40d = 0;
            }
            lbl_8063D4A0->_0008.b25_24 = 1;
            fn_80253DF0((s16)lbl_8063D4A0->_0034, 8, 1);
            break;
        case 2:
            if (lbl_8063D4A0->_0008.b25_24 == 2) {
                break;
            }
            if (lbl_8063D4A0->_0008.b25_24 == 1) {
                fn_80253DF0((s16)lbl_8063D4A0->_0034, 8, 0);
            }
            if (lbl_8063D4A0->_0008.b25_24 == 3) {
                fn_80057FB4(3);
            }
            lbl_8063D4A0->_0008.b25_24 = 2;
            if (rt) {
                lbl_8063D4A0->_0038 = rt->_20 == 0 ? rt->_c : (u32)rt->_24;
            }
            if (lbl_8063D4A0->_0028) {
                Vec2 tmp;
                GSobject *o;
                GSnull *cam;
                lbl_8063D4A0->_0030 = GShierarchyModule::sInstance->getCurrentScene();
                GShierarchyModule::setCurrentScene(lbl_8063D4A0->_0028);
                lbl_8063F410->_40d = 1;
                lbl_8063F410->_42c = lbl_80640B7C;
                lbl_8063F410->_430 = 0;
                lbl_8063F410->_434 = 0;
                lbl_8063F410->_431 = 50;
                tmp.x = lbl_80640B60;
                tmp.y = lbl_80640B60;
                lbl_8063F410->_424 = tmp;
                o = lbl_8063D4A0->_0028->getObject(0);
                if (o) {
                    GShierarchyModule::fn_80200594(o);
                    cam = o->getCamera(0);
                    if (rt && cam) {
                        rt->_20 = 0;
                        rt->_c = (u32)cam;
                    }
                }
            }
            break;
        case 3:
            if (lbl_8063D4A0->_0008.b25_24 == 3) {
                break;
            }
            if (lbl_8063D4A0->_0008.b25_24 == 1) {
                fn_80253DF0((s16)lbl_8063D4A0->_0034, 8, 0);
            }
            if (lbl_8063D4A0->_0008.b25_24 == 2) {
                fn_80057FB4(2);
            }
            lbl_8063D4A0->_0008.b25_24 = 3;
            if (rt) {
                lbl_8063D4A0->_0038 = rt->_20 == 0 ? rt->_c : (u32)rt->_24;
            }
            if (lbl_8063D4A0->_002c) {
                Vec2 tmp;
                GSobject *o;
                u32 v;
                s32 id;
                GSrenderTarget *t;
                u32 r;
                lbl_8063D4A0->_0030 = GShierarchyModule::sInstance->getCurrentScene();
                GShierarchyModule::setCurrentScene(lbl_8063D4A0->_002c);
                lbl_8063F410->_40d = 1;
                lbl_8063F410->_42c = lbl_80640B80;
                lbl_8063F410->_431 = 40;
                lbl_8063F410->_430 = 0;
                if (lbl_8063F410->_418) {
                    lbl_8063F410->_40e = 1;
                } else {
                    lbl_8063F410->_40e = 0;
                }
                lbl_8063F410->_434 = 0;
                lbl_8063F410->_450 = lbl_80640B6C;
                tmp.x = lbl_80640B60;
                tmp.y = lbl_80640B60;
                lbl_8063F410->_424 = tmp;
                o = lbl_8063D4A0->_002c->getObject(0);
                {
                    u32 v = GShierarchyModule::sInstance->get_138();
                    s32 id = (v >> 16) & 0xff;
                    GSrenderTarget *t = GSrenderTarget::findTarget(id);
                    u32 r;
                    if (t) {
                        r = fn_8023B330(t, v);
                    } else {
                        r = 0;
                    }
                    if (!r) {
                        t = GSrenderTarget::findTarget(id);
                        if (t) {
                            t->fn_8023B3B8(v);
                        }
                    }
                }
                {
                    v = GShierarchyModule::sInstance->get_144();
                    id = (v >> 16) & 0xff;
                    t = GSrenderTarget::findTarget(id);
                    if (t) {
                        r = fn_8023B330(t, v);
                    } else {
                        r = 0;
                    }
                    if (!r) {
                        t = GSrenderTarget::findTarget(id);
                        if (t) {
                            t->fn_8023B3B8(v);
                        }
                    }
                }
                if (o) {
                    GShierarchyModule::fn_80200594(o);
                    o = (GSobject *)o->getCamera(0);
                    if (rt && o) {
                        rt->_20 = 0;
                        rt->_c = (u32)o;
                        ((GSnull *)o)->initTransform(false);
                        if ((((GScamera *)o)->_104 & 3) == 1) {
                            ((GScamera *)o)->_168 = lbl_80640B84;
                            ((GScamera *)o)->_104 |= 8;
                        }
                    }
                }
            }
            break;
    }
}

// TODO Leaves the display mode set by fn_800579FC.
void fn_80057FB4(int mode) {
    Unk80242A00 *rt = (Unk80242A00 *)GSrenderTarget::findTarget(2);
    switch (mode) {
        case 1:
            if (lbl_8063D4A0->_0020) {
                fn_80253DF0((s16)lbl_8063D4A0->_0034, 8, 0);
                lbl_8063D4A0->_0008.b25_24 = 0;
            }
            break;
        case 2:
            if (lbl_8063D4A0->_001c) {
                GSobject *o;
                u32 v;
                if (rt && (v = lbl_8063D4A0->_0038) != 0) {
                    rt->_20 = 0;
                    rt->_c = v;
                }
                o = lbl_8063D4A0->_0028->getObject(0);
                if (o) {
                    GShierarchyModule::fn_80200858(o);
                }
                GShierarchyModule::setCurrentScene(lbl_8063D4A0->_0030);
                lbl_8063F410->_40d = 0;
                lbl_8063D4A0->_0008.b25_24 = 0;
            }
            break;
        case 3:
            if (lbl_8063D4A0->_0024) {
                GSobject *o;
                u32 v;
                if (rt && (v = lbl_8063D4A0->_0038) != 0) {
                    rt->_20 = 0;
                    rt->_c = v;
                }
                o = lbl_8063D4A0->_002c->getObject(0);
                if (o) {
                    GShierarchyModule::fn_80200858(o);
                }
                GShierarchyModule::setCurrentScene(lbl_8063D4A0->_0030);
                lbl_8063F410->_40d = 0;
                lbl_8063D4A0->_0008.b25_24 = 0;
            }
            break;
    }
}

// TODO Sets the render state used to draw the full-screen images.
void fn_80058178() {
    GSrender *r = GSrender::sInstance;
    r->getState()->mCurr.mLineWidth = 6;
    r->getState()->mCurr.mLineTexOffsets = GX_TO_ZERO;
    r->getState()->_4 |= (1 << 2);
    r->getState()->_0 |= (1 << 0);
    GSrender::sInstance->setBlend(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
    fn_80234FE0(GSrender::sInstance,
                lbl_80640B60,
                lbl_80640B60,
                lbl_80640B88,
                lbl_80640B8C,
                lbl_80640B60,
                lbl_80640B90);
    GSrender::sInstance->setEfbUpdate(true, false, false);
    GSrender::sInstance->setZCompare(false, 3);
    GSrender::sInstance->setAlphaCompare(false, 0, 0);
    GSrender::sInstance->setCullMode(GX_CULL_NONE);
    GSrender::sInstance->setClipMode(GX_CLIP_DISABLE);
    GSrender::sInstance->setFogEnabled(false);
    fn_8005650C();
}

// TODO Sets flag bit 9.
void fn_800583A4() {
    lbl_8063D4A0->_0008.b9 = 1;
}

// TODO Clears flag bit 9.
void fn_800583B8() {
    lbl_8063D4A0->_0008.b9 = 0;
}

// TODO Clears flag bit 10.
void fn_800583CC() {
    lbl_8063D4A0->_0008.b10 = 0;
}

// TODO Sets flag bit 7.
void fn_800583E0() {
    lbl_8063D4A0->_0008.b7 = 1;
}

// TODO Clears flag bit 7.
void fn_800583F4() {
    lbl_8063D4A0->_0008.b7 = 0;
}

// TODO Clears flag bit 8.
void fn_80058408() {
    lbl_8063D4A0->_0008.b8 = 0;
}

// TODO Clears the countdown flags.
void fn_8005841C() {
    lbl_8063D4A0->_0008.b10 = 0;
    lbl_8063D4A0->_0008.b9 = 0;
    lbl_8063D4A0->_0008.b8 = 0;
    lbl_8063D4A0->_0008.b7 = 0;
    lbl_8063D4A0->_0008.b5 = 0;
    lbl_8063D4A0->_0008.b4 = 0;
}

// TODO Flag bit 10.
u32 fn_80058480() {
    return lbl_8063D4A0->_0008.b10;
}

// TODO Flag bit 9.
u32 fn_80058490() {
    return lbl_8063D4A0->_0008.b9;
}

// TODO Flag bit 8.
u32 fn_800584A0() {
    return lbl_8063D4A0->_0008.b8;
}

// TODO Flag bit 7.
u32 fn_800584B0() {
    return lbl_8063D4A0->_0008.b7;
}

// TODO Sets flag bit 4.
void fn_800584C0() {
    lbl_8063D4A0->_0008.b4 = 1;
}

// TODO Clears flag bit 4.
void fn_800584D4() {
    lbl_8063D4A0->_0008.b4 = 0;
}

// TODO Starts the first countdown from the value of fn_8011C974.
void fn_800584E8() {
    Unk8011C974 *p = fn_8011C974();
    if (p->_0094 == 0) {
        lbl_8063D4A0->_0008.b10 = 0;
    } else {
        lbl_8063D4A0->_0008.b10 = 1;
        lbl_8063D4A0->_108c = lbl_80640B84 * p->_0094;
        lbl_8063D4A0->_1088 = lbl_80640B60;
        lbl_8063D4A0->_0008.b5 = 0;
    }
}

// TODO Starts the second countdown from the value of fn_8011C974.
void fn_80058580() {
    Unk8011C974 *p = fn_8011C974();
    if (p->_0092 == 0) {
        lbl_8063D4A0->_0008.b8 = 0;
    } else {
        lbl_8063D4A0->_0008.b8 = 1;
        lbl_8063D4A0->_1094 = p->_0092;
        lbl_8063D4A0->_1090 = lbl_80640B60;
        lbl_8063D4A0->_0008.b4 = 0;
    }
}

// TODO Whether the first countdown is over.
BOOL fn_80058610() {
    if (fn_8011C974()->_0094 == 0) {
        return 0;
    }
    return lbl_8063D4A0->_1088 >= lbl_8063D4A0->_108c;
}

// TODO Whether the second countdown is over.
BOOL fn_80058660() {
    if (fn_8011C974()->_0092 == 0) {
        return 0;
    }
    return lbl_8063D4A0->_1090 >= lbl_8063D4A0->_1094;
}

// TODO Time left in the first countdown.
int fn_800586B0() {
    if (fn_8011C974()->_0094 == 0) {
        return 0;
    }
    if (lbl_8063D4A0->_1088 >= lbl_8063D4A0->_108c) {
        return 0;
    }
    return lbl_8063D4A0->_108c - lbl_8063D4A0->_1088;
}

// TODO Time left in the second countdown.
int fn_80058714() {
    if (fn_8011C974()->_0092 == 0) {
        return 0;
    }
    if (lbl_8063D4A0->_1090 >= lbl_8063D4A0->_1094) {
        return 0;
    }
    return lbl_8063D4A0->_1094 - lbl_8063D4A0->_1090;
}

// TODO Loads the message files for the console language.
void fn_80058778(int x) {
    if (x) {
        switch ((u8)fn_80058B10(0)) {
            case 0: fn_80058778Inline(0x5dc, 0x27c00000, 0x27c10000); break;
            case 1: fn_80058778Inline(0x5de, 0x2b820000, 0x2b830000); break;
            case 2: fn_80058778Inline(0x5e0, 0x2b860000, 0x2b870000); break;
            case 3: fn_80058778Inline(0x5dd, 0x2b800000, 0x2b810000); break;
            case 4: fn_80058778Inline(0x5df, 0x2b840000, 0x2b850000); break;
        }
    } else {
        switch (fn_8015F690()->_48) {
            case 1:
            case 2:
            case 3:
            case 4:  break;
            case 0:
            default: fn_80058778Inline(0x5dc, 0x27c00000, 0x27c10000); break;
        }
    }
}

// TODO Index of the console language in the localized file tables.
u8 fn_80058B10(bool x) {
    switch (SCGetLanguage()) {
        case 2:  return 1;
        case 3:  return 3;
        case 4:  return 2;
        case 5:  return 4;
        case 6:  return x ? 5 : 0;
        default: return 0;
    }
}

// TODO Value _48 of the object of fn_8015F690.
u8 fn_80058BA4() {
    return fn_8015F690()->_48;
}

// TODO Entry x of a 12-entry table, 0 outside 1 to 12.
u16 fn_80058BCC(u32 x) {
    if (x >= 1 && x <= 12) {
        u32 i = x - 1;
        return lbl_8040B088[i];
    }
    return 0;
}

// TODO Formats a number with message 0x3F9.
u16 fn_80058BFC(int a, int b, int c) {
    u16 buf[3] = {0, 0, 0};
    if (fn_80058BA4() == 1) {
        buf[0] = 0x2e;
        buf[1] = 0x20;
    } else {
        buf[0] = 0x20;
        buf[1] = 0;
    }
    fn_8015C308(0xf, buf);
    fn_80250134(0x3f9, a, b, 0, 0, c);
    return fn_80250398(0x3f9, 1, 0);
}

// TODO Inserts a 0xFFFF 0x13 marker at the start of a code list.
void fn_80058CBC(Unk80058EA0 *p) {
    s16 i;
    int j;
    for (i = 0; i < 12; i++) {
        if (p->_004[i] == 0xffff && p->_004[i + 1] == 0xffff) {
            p->_004[i] = 0;
            break;
        }
        if (p->_004[i] == 0) {
            break;
        }
    }
    for (j = 9; j >= 0; j--) {
        p->_004[j + 2] = p->_004[j];
    }
    p->_004[0] = 0xffff;
    p->_004[1] = 0x13;
}

// TODO Removes the marker inserted by fn_80058CBC.
void fn_80058E34(u16 *p) {
    int i;
    if (p[2] == 0xffff && p[3] == 0x13) {
        for (i = 0; i < 10; i++) {
            p[2 + i] = p[4 + i];
        }
    }
}

// TODO Inserts a 0xFFFF 0x14 marker at the start of a code list.
void fn_80058EA0(Unk80058EA0 *p) {
    s16 i;
    int j;
    for (i = 0; i < 10; i++) {
        if (p->_004[i] == 0xffff && p->_004[i + 1] == 0xffff) {
            p->_004[i] = 0xffff;
            p->_004[i + 1] = 0x13;
            p->_004[i + 2] = 0;
            break;
        }
        if (p->_004[i] == 0) {
            p->_004[i] = 0xffff;
            p->_004[i + 1] = 0x13;
            p->_004[i + 2] = 0;
            break;
        }
    }
    for (j = 9; j >= 0; j--) {
        p->_004[j + 2] = p->_004[j];
    }
    p->_004[0] = 0xffff;
    p->_004[1] = 0x14;
}

// TODO Draws a localized full-screen image with alpha c. Does not match yet (0x21C bytes instead of 0x234).
void fn_80058FD4(u8 c, int mode) {
    Unk80058FD4 q;
    u32 color = c | 0xffffff00;
    Unk803FB820 *t = &lbl_803FB820;
    if (mode) {
        if (GSrender::sInstance->get_7a()) {
            Unk803FB838 *e;
            q._00[0] = q._00[3] = lbl_80640BA0;
            q._00[1] = q._00[2] = lbl_80640BA4;
            q._10[0] = q._10[1] = lbl_80640B60;
            q._10[2] = q._10[3] = lbl_80640B8C;
            e = &t->_18[(u8)fn_80058B10(1)];
            fn_8005AF78(fn_8005AC60(t->_00[(u8)fn_80058B10(1)], e->_4), &q, color, 0);
        } else {
            q._00[0] = q._00[3] = lbl_80640B60;
            q._00[1] = q._00[2] = lbl_80640B88;
            q._10[0] = q._10[1] = lbl_80640B60;
            q._10[2] = q._10[3] = lbl_80640B8C;
            fn_8005AF78(fn_8005AC60(t->_00[(u8)fn_80058B10(1)], t->_18[(u8)fn_80058B10(1)]._0), &q, color, 0);
        }
    } else {
        GStexture *tex;
        u16 w, h;
        f32 left, top;
        tex = fn_8005AC60(t->_00[(u8)fn_80058B10(1)], t->_48[(u8)fn_80058B10(1)]);
        w = tex->getWidth();
        h = tex->getHeight();
        left = (640 - w) / 2;
        top = (480 - h) / 2;
        q._00[0] = q._00[3] = left;
        q._00[1] = q._00[2] = left + w;
        q._10[0] = q._10[1] = top;
        q._10[2] = q._10[3] = top + h;
        fn_8005AF78(tex, &q, color, 0);
    }
}

// TODO Starts the thread of fn_80059288.
void fn_80059208() {
    lbl_8063D4A0->_0008.b2 = 0;
    GSthreadManager::sInstance->createThread(200, fn_80059288, 0, 0x2000, 8, 1);
}

// TODO Flag bit 2.
u32 fn_8005923C() {
    return lbl_8063D4A0->_0008.b2;
}

// TODO Flag bit 0.
bool fn_8005924C() {
    return lbl_8063D4A0->_0008.b0;
}

// TODO Sets flag bit 1, and clears bit 0 when x is 0.
void fn_8005925C(u32 x) {
    lbl_8063D4A0->_0008.b1 = x;
    if (!x) {
        lbl_8063D4A0->_0008.b0 = 0;
    }
}

// TODO Thread showing the localized startup images until the state machine of fn_80059414 ends.
void *fn_80059288(void *arg) {
    OSTime t;
    int h;
    lbl_8063D4A0->_10a8 = 0;
    lbl_8063D4A0->_1098 = lbl_80640B60;
    h = fn_80253F6C(0, fn_80059414, -1);
    fn_8005A994();
    while (!lbl_8063D4A0->_0008.b1) {
        GSthreadManager::sInstance->sleepCurrentThread();
    }
    GSfsys::loadFsys(lbl_803FB820._00[(u8)fn_80058B10(1)]);
    lbl_8063D4A0->_10a8 = 1;
    lbl_8063D4A0->_0008.b0 = 1;
    t = OSGetTime();
    do {
        lbl_8063D4A0->_10a0 = OSTicksToMicroseconds((u64)(OSGetTime() - t));
        t = OSGetTime();
        lbl_8063D4A0->_1098 += fn_800597C4();
        GSthreadManager::sInstance->sleepCurrentThread();
    } while (lbl_8063D4A0->_10a8 != 15);
    GSfsys::fn_80249890(lbl_803FB820._00[(u8)fn_80058B10(1)]);
    GScache::freeFsysCacheEntries(lbl_803FB820._00[(u8)fn_80058B10(1)]);
    fn_80253F8C(h);
    lbl_8063D4A0->_0008.b2 = 1;
    return 0;
}

// TODO State machine fading the localized startup images in and out.
void fn_80059414() {
    GSinputDevice *dev = GSinput::getDevice(0);
    f32 f;
    switch (lbl_8063D4A0->_10a8) {
        case 0: break;
        case 1:
            lbl_8063D4A0->_109c = lbl_8063D4A0->_1098;
            fn_80058FD4(0, 1);
            lbl_8063D4A0->_10a8 = 2;
            break;
        case 2:
            f = lbl_80640BB0 * (lbl_8063D4A0->_1098 - lbl_8063D4A0->_109c);
            if (f >= lbl_80640B68) {
                f = lbl_80640B68;
                lbl_8063D4A0->_10a8 = 3;
                lbl_8063D4A0->_109c = lbl_8063D4A0->_1098;
            }
            fn_80058FD4(lbl_80640BB4 * f, 1);
            break;
        case 3:
            if (lbl_8063D4A0->_1098 - lbl_8063D4A0->_109c >= lbl_80640BB0) {
                lbl_8063D4A0->_10a8 = 4;
            }
            fn_80058FD4(0xff, 1);
            break;
        case 4:
            if (lbl_8063D4A0->_1098 - lbl_8063D4A0->_109c >= lbl_80640BB8) {
                lbl_8063D4A0->_10a8 = 5;
                lbl_8063D4A0->_109c = lbl_8063D4A0->_1098;
            } else if (dev && (dev->mButtonsDown & 0x1f1f)) {
                lbl_8063D4A0->_10a8 = 5;
                lbl_8063D4A0->_109c = lbl_8063D4A0->_1098;
            }
            fn_80058FD4(0xff, 1);
            break;
        case 5:
            f = lbl_80640BB0 * (lbl_8063D4A0->_1098 - lbl_8063D4A0->_109c);
            if (f >= lbl_80640B68) {
                f = lbl_80640B68;
                lbl_8063D4A0->_10a8 = 6;
                lbl_8063D4A0->_109c = lbl_8063D4A0->_1098;
            }
            fn_80058FD4(lbl_80640BB4 * (lbl_80640B68 - f), 1);
            break;
        case 6:
            fn_80058FD4(0, 1);
            lbl_8063D4A0->_10a8 = 13;
            break;
        case 7:
            lbl_8063D4A0->_109c = lbl_8063D4A0->_1098;
            fn_80058FD4(0, 0);
            lbl_8063D4A0->_10a8 = 8;
            break;
        case 8:
            f = lbl_80640BB0 * (lbl_8063D4A0->_1098 - lbl_8063D4A0->_109c);
            if (f >= lbl_80640B68) {
                f = lbl_80640B68;
                lbl_8063D4A0->_10a8 = 9;
                lbl_8063D4A0->_109c = lbl_8063D4A0->_1098;
            }
            fn_80058FD4(lbl_80640BB4 * f, 0);
            break;
        case 9:
            if (lbl_8063D4A0->_1098 - lbl_8063D4A0->_109c >= lbl_80640BB0) {
                lbl_8063D4A0->_10a8 = 10;
            }
            fn_80058FD4(0xff, 0);
            break;
        case 10:
            if (lbl_8063D4A0->_1098 - lbl_8063D4A0->_109c >= lbl_80640BBC) {
                lbl_8063D4A0->_10a8 = 11;
                lbl_8063D4A0->_109c = lbl_8063D4A0->_1098;
            } else if (dev && (dev->mButtonsDown & 0x1f1f)) {
                lbl_8063D4A0->_10a8 = 11;
                lbl_8063D4A0->_109c = lbl_8063D4A0->_1098;
            }
            fn_80058FD4(0xff, 0);
            break;
        case 11:
            f = lbl_80640BB0 * (lbl_8063D4A0->_1098 - lbl_8063D4A0->_109c);
            if (f >= lbl_80640B68) {
                f = lbl_80640B68;
                lbl_8063D4A0->_10a8 = 12;
                lbl_8063D4A0->_109c = lbl_8063D4A0->_1098;
            }
            fn_80058FD4(lbl_80640BB4 * (lbl_80640B68 - f), 0);
            break;
        case 12:
            fn_80058FD4(0, 0);
            lbl_8063D4A0->_10a8 = 13;
            break;
        case 13: lbl_8063D4A0->_10a8 = 14; break;
        case 14: lbl_8063D4A0->_10a8 = 15; break;
    }
}

// TODO Frame time from _10a0, 0 while paused.
f32 fn_800597C4() {
    if (fn_801E07E8()) {
        return lbl_80640B60;
    }
    if (fn_80007084()) {
        return lbl_80640B60;
    }
    if (GSrender::sInstance->getHomeMenuActive()) {
        return lbl_80640B60;
    }
    return lbl_8063D4A0->_10a0 / lbl_80640B64 / lbl_80640B64;
}

// TODO Loads localized archive i.
bool fn_8005983C(int i) {
    return GSfsys::loadFsys(lbl_803FB880[i][fn_80058BA4()]);
}

// TODO Releases localized archive i.
void fn_80059884(int i) {
    u32 *row = lbl_803FB880[i];
    GScache::freeFsysCacheEntries(row[fn_80058BA4()]);
    GSfsys::fn_80249890(row[fn_80058BA4()]);
}
