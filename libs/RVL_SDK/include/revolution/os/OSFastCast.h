#ifndef REVOLUTION_OS_FAST_CAST_H
#define REVOLUTION_OS_FAST_CAST_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/////// FAST CAST DEFINES ////////
// GQR formats.
#define OS_GQR_U8  (0x0004) // GQR 1
#define OS_GQR_U16 (0x0005) // GQR 2
#define OS_GQR_S8  (0x0006) // GQR 3
#define OS_GQR_S16 (0x0007) // GQR 4

// GQRs for fast casting.
#define OS_FASTCAST_U8  (2)
#define OS_FASTCAST_U16 (3)
#define OS_FASTCAST_S8  (4)
#define OS_FASTCAST_S16 (5)

// GQR scale factors
#define OS_GQR_SCALE_NONE   0
#define OS_GQR_SCALE_2      1
#define OS_GQR_SCALE_4      2
#define OS_GQR_SCALE_8      3
#define OS_GQR_SCALE_16     4
#define OS_GQR_SCALE_32     5
#define OS_GQR_SCALE_64     6
#define OS_GQR_SCALE_128    7
#define OS_GQR_SCALE_256    8
#define OS_GQR_SCALE_512    9
#define OS_GQR_SCALE_1024   10
#define OS_GQR_SCALE_2048   11
#define OS_GQR_SCALE_4096   12
#define OS_GQR_SCALE_8192   13
#define OS_GQR_SCALE_16384  14
#define OS_GQR_SCALE_32768  15
#define OS_GQR_SCALE_65536  16
#define OS_GQR_SCALE_MAX    31

static void OSInitFastCast(void) {
    // clang-format off
#ifdef __MWERKS__
    asm {
		li        r3,     OS_GQR_U8
		oris      r3, r3, OS_GQR_U8
		mtspr     GQR2, r3

		li        r3,     OS_GQR_U16
		oris      r3, r3, OS_GQR_U16
		mtspr     GQR3, r3

		li        r3,     OS_GQR_S8
		oris      r3, r3, OS_GQR_S8
		mtspr     GQR4, r3

		li        r3,     OS_GQR_S16
		oris      r3, r3, OS_GQR_S16
		mtspr     GQR5, r3
    }
#endif
    // clang-format on
}

static void OSSetGQR6(register u32 type, register u32 scale)
{
	register u32 val = ((scale << 8 | type) << 16) | ((scale << 8) | type);

#ifdef __MWERKS__ // clang-format off
    asm (
        mtspr GQR6, val
    );
#endif // clang-format on
}

static void OSSetGQR7(register u32 type, register u32 scale)
{
	register u32 val = ((scale << 8 | type) << 16) | ((scale << 8) | type);

#ifdef __MWERKS__ // clang-format off
    asm (
        mtspr GQR7, val
    );
#endif // clang-format on
}

/*** TO F32 ***/

static f32 __OSu16tof32(register const u16* arg) {
    register f32 ret;
    // clang-format off
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 3 }
#endif
    // clang-format on
    return ret;
}

static void OSu16tof32(const u16* in, f32* out) {
    *out = __OSu16tof32(in);
}

/*** FROM F32 ***/

static u8 __OSf32tou8(register f32 arg) {
    f32 a;
    register f32* ptr = &a;
    u8 r;
    // clang-format off
#ifdef __MWERKS__
    asm {
        psq_st arg, 0(ptr), 1, 2
    }
#endif
    // clang-format on
    r = *(u8*)ptr;
    return r;
}

static void OSf32tou8(f32* in, vu8* out) {
    *out = __OSf32tou8(*in);
}

static u16 __OSf32tou16(register f32 arg) {
    f32 a;
    register f32* ptr = &a;
    u16 r;
    // clang-format off
#ifdef __MWERKS__
    asm { psq_st arg, 0(ptr), 1, 3 }
#endif
    // clang-format on
    r = *(u16*)ptr;
    return r;
}

static void OSf32tou16(const f32* in, u16* out) {
    *out = __OSf32tou16(*in);
}

static f32 __OSs16tof32(register const s16* arg) {
    register f32 ret;
    // clang-format off
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 5 }
#endif
    // clang-format on
    return ret;
}

static void OSs16tof32(const s16* in, f32* out) {
    *out = __OSs16tof32(in);
}

static s16 __OSf32tos16(register f32 arg) {
    f32 a;
    register f32* ptr = &a;
    s16 r;
    // clang-format off
#ifdef __MWERKS__
    asm { psq_st arg, 0(ptr), 1, 5 }
#endif
    // clang-format on
    r = *(s16*)ptr;
    return r;
}

static void OSf32tos16(const f32* in, s16* out) {
    *out = __OSf32tos16(*in);
}

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_OS_FAST_CAST_H
