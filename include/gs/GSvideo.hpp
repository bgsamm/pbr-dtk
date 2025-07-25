#pragma once

#include <revolution/types.h>
#include <revolution/gx.h>
#include <revolution/os.h>
#include <revolution/sc.h>
#include <revolution/vi.h>

#define MAX_XFBS 3

enum VideoFormat {
    VID_FMT_NTSC,
    VID_FMT_PAL,
    VID_FMT_EURGB60,
    VID_FMT_MPAL
};

enum XfbState {
    XFB_STATE_UNUSED,
    XFB_STATE_1,
    XFB_STATE_2,
    XFB_STATE_3,
    XFB_STATE_4
};

struct XfbInfo {
    XfbState state;
    void *buf;
};

struct UnkStruct7 {
    int _0;
    GXRenderModeObj *ntsc;
    GXRenderModeObj *pal;
    GXRenderModeObj *eurgb60;
    GXRenderModeObj *mpal;
};

union U32F32 {
    u32 ival;
    f32 fval;
};

class GSvideoManager {
public:
    /* 0x0 */ GXRenderModeObj mRenderMode;
    /* 0x3c */ XfbInfo mXfbs[MAX_XFBS];
    /* 0x54 */ XfbInfo *mActiveXfb;
    /* 0x58 */ u8 mNumBuffers;
    /* 0x59 */ u8 mRefreshRate;
    /* 0x5a */ u8 mNextField;
    /* 0x5b */ bool mWaitForRetrace;
    /* 0x5c */ u16 mEfbHeight;
    /* 0x5e */ u16 mXfbHeight;
    /* 0x60 */ GXGamma mGamma;
    /* 0x64 */ GXPixelFmt mPixelFmt;
    /* 0x68 */ f32 mYScale;
    /* 0x6c */ u32 mRetraceCount;
    /* 0x70 */ VideoFormat mVideoFmt;
    /* 0x74 */ VIRetraceCallback mRetraceCallback;
    u8 _78;
    u8 _79;
    u8 _7a;
    u32 _7c;
    u8 _80;
    u8 _81;
    u8 _82;
    u8 _83;
    u32 _84;
    u32 _88;
    f32 _8c;
    f32 _90;
    OSTime _98;
    f64 _a0;
    U32F32 _a8;
    U32F32 _ac;
    U32F32 _b0;
    U32F32 _b4;
    U32F32 _b8;
    U32F32 _bc;
    union {
        u32 _c0_u32;
        struct {
            u16 mScissorXOrig;
            u16 mScissorYOrig;
        };
    };
    union {
        u32 _c4_u32;
        struct {
            u16 mScissorWidth;
            u16 mScissorHeight;
        };
    };
    s32 _c8;
    s32 _cc;
    /* 0xd0 */ GXColor mClearColor;
    /* 0xd4 */ u32 mClearZ;
    void **_d8;

    GSvideoManager(u8, u16, VideoFormat);
    ~GSvideoManager();

    static void preRetraceCallback(u32 retraceCount);
    static void postRetraceCallback(u32 retraceCount);

    void waitForRetrace();
    void fn_8023F45C();
    void fn_8023F4B8();
    void prepareCopyDisp();
    void copyDisp(XfbInfo *);
    void fn_8023F5E8(u32, u32, u32, u32);
    void fn_8023F778();
    bool fn_8023F858(VideoFormat, u32, u32, u32);
    void fn_8023FB04(bool);
    void fn_8023FBA0(XfbInfo *, u32);
    XfbInfo *fn_8023FC0C(XfbState);
    XfbInfo *fn_8023FC54(u32);
    void fn_8023FD64();
    void fn_8023FE30(u32);
    void fn_8023FEE8(f32, f32, f32, f32, f32, f32);
    void setScissor(u32, u32, u32, u32);
    void setScissorBoxOffset(s32, s32);
    f32 fn_8023FFEC();

    static GSvideoManager *sInstance;
};
