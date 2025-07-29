#ifndef OSFASTCAST_H
#define OSFASTCAST_H

#ifdef __cplusplus
extern "C" {
#endif

// GQR type formats
#define OS_GQR_F32 0x0000
#define OS_GQR_U8  0x0004
#define OS_GQR_U16 0x0005
#define OS_GQR_S8  0x0006
#define OS_GQR_S16 0x0007

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

#define OS_GQR_DIVIDE_2     63
#define OS_GQR_DIVIDE_4     62
#define OS_GQR_DIVIDE_8     61
#define OS_GQR_DIVIDE_16    60
#define OS_GQR_DIVIDE_32    59
#define OS_GQR_DIVIDE_64    58
#define OS_GQR_DIVIDE_128   57
#define OS_GQR_DIVIDE_256   56
#define OS_GQR_DIVIDE_512   55
#define OS_GQR_DIVIDE_1024  54
#define OS_GQR_DIVIDE_2048  53
#define OS_GQR_DIVIDE_4096  52
#define OS_GQR_DIVIDE_8192  51
#define OS_GQR_DIVIDE_16384 50
#define OS_GQR_DIVIDE_32768 49
#define OS_GQR_DIVIDE_65536 48
#define OS_GQR_DIVIDE_MAX   32

#define GQR2 0x392
#define GQR3 0x393
#define GQR4 0x394
#define GQR5 0x395
#define GQR6 0x396
#define GQR7 0x397

#define OS_FASTCAST_U8  2
#define OS_FASTCAST_U16 3
#define OS_FASTCAST_S8  4
#define OS_FASTCAST_S16 5

static inline void OSInitFastCast(void) {
    asm {
        li      r3, OS_GQR_U8
        oris    r3, r3, OS_GQR_U8
        mtspr   GQR2, r3

        li      r3, OS_GQR_U16
        oris    r3, r3, OS_GQR_U16
        mtspr   GQR3, r3

        li      r3, OS_GQR_S8
        oris    r3, r3, OS_GQR_S8
        mtspr   GQR4, r3

        li      r3, OS_GQR_S16
        oris    r3, r3, OS_GQR_S16
        mtspr   GQR5, r3
    }
}

static inline void OSSetGQR6(register u32 type, register u32 scale) {
    register u32 val = ((scale << 8 | type) << 16) | ((scale << 8) | type);

    asm {
        mtspr GQR6, val
    }
}

static inline void OSSetGQR7(register u32 type, register u32 scale) {
    register u32 val = ((scale << 8 | type) << 16) | ((scale << 8) | type);

    asm {
        mtspr GQR7, val
    }
}

static inline f32 __OSu16tof32(register u16* in)
{
    register f32   r;
    asm
    {
        psq_l      r, 0(in), 1, OS_FASTCAST_U16
    }
    return r;
}

static inline void OSu16tof32(register u16* in, volatile register f32* out)
{
    *out = __OSu16tof32(in);
}

static inline u16 __OSf32tou16(register f32 in)
{
    f32           a;
    register f32* ptr = &a;
    register u16  r;

    asm
    {
        psq_st  in, 0(ptr), 1, OS_FASTCAST_U16
        lhz     r, 0(ptr)
    }
    return r;
}

static inline void OSf32tou16(register f32* in, volatile register u16* out)
{
    *out = __OSf32tou16(*in);
}

#ifdef __cplusplus
}
#endif

#endif // OSFASTCAST_H
