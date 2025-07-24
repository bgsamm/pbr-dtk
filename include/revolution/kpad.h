#ifndef KPAD_H
#define KPAD_H

#include <revolution/types.h>
#include <revolution/mtx.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Vec2 {
    f32 x;
    f32 y;
} Vec2;

typedef union KPADEXStatus {
    struct {
        Vec2 stick;
        Vec acc;
        f32 acc_value;
        f32 acc_speed;
    } fs;

    struct {
        u32 hold;
        u32 trig;
        u32 release;
        Vec2 lstick;
        Vec2 rstick;
        f32 ltrigger;
        f32 rtrigger;
    } cl;
} KPADEXStatus;

// size: 0x84
typedef struct KPADStatus {
    /* 0x0 */ u32 hold;
    /* 0x4 */ u32 trig;
    /* 0x8 */ u32 release;
    Vec acc;
    f32 acc_value;
    f32 acc_speed;
    Vec2 pos;
    Vec2 vec;
    f32 speed;
    Vec2 horizon;
    Vec2 hori_vec;
    f32 hori_speed;
    f32 dist;
    f32 dist_vec;
    f32 dist_speed;
    Vec2 acc_vertical;
    /* 0x5c */ u8 dev_type;
    /* 0x5d */ s8 wpad_err;
    /* 0x5e */ s8 dpd_valid_fg;
    /* 0x5f */ u8 data_format;
    /* 0x60 */ KPADEXStatus ex_status;
} KPADStatus;

void KPADSetFSStickClamp(s8 min, s8 max);

s32 KPADRead(s32 chan, KPADStatus samplingBufs[], u32 length);
void KPADInit(void);
void KPADDisableDPD(s32 chan);
void KPADEnableDPD(s32 chan);

#ifdef __cplusplus
}
#endif

#endif // KPAD_H
