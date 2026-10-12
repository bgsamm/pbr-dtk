#pragma once

#include <revolution/gx.h>
#include <revolution/os.h>
#include <revolution/sc.h>
#include <revolution/types.h>
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

struct GSxfbHandle {
    XfbState mState;
    void *mBuffer;
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

// NOTE(samm) Name known from RTTI
class GSvideo {
public:
    // Read directly by game code.
    /* 0x0 */ GXRenderModeObj mRenderMode;

protected:
    /* 0x3c */ GSxfbHandle mXfbs[MAX_XFBS];
    /* 0x54 */ GSxfbHandle *mActiveXfb;
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

public:
    // Read directly by game code.
    /* 0x70 */ VideoFormat mVideoFmt;

protected:
    /* 0x74 */ VIRetraceCallback mRetraceCallback;
    u8 _78;
    u8 _79;
    // NOT a boolean
    /* 0x7a */ u8 _7a;
    u32 _7c;
    u8 _80;
    u8 _81;
    /* 0x82 */ bool mHomeMenuActive;
    /* 0x83 */ bool _83;
    u32 _84;
    u32 _88;
    /* 0x8c */ f32 _8c;
    /* 0x90 */ f32 _90;
    /* 0x98 */ OSTime _98;
    f64 _a0;
    U32F32 _a8;
    U32F32 _ac;
    /* 0xb0 */ U32F32 mViewportWidth;
    /* 0xb4 */ U32F32 mViewportHeight;
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

    static GSvideo *sInstance;

public:
    GSvideo(u8, u16, VideoFormat);
    virtual ~GSvideo();

    void getRenderDimensions(u16 *width, u16 *height) const {
        if (width) {
            *width = mRenderMode.fbWidth;
        }
        if (height) {
            *height = mRenderMode.efbHeight;
        }
    }

    bool getHomeMenuActive() const {
        return mHomeMenuActive;
    }

    u8 get_7a() {
        return _7a;
    }

    bool _unkCondition1() {
        return mHomeMenuActive || _83;
    }

    u8 getRefreshRate() {
        return mRefreshRate;
    }

    u32 getRetraceCount() {
        return mRetraceCount;
    }

    VIRetraceCallback getRetraceCallback() {
        return mRetraceCallback;
    }

    void setRetraceCallback(VIRetraceCallback callback) {
        mRetraceCallback = callback;
    }

    static GSvideo *getInstance() {
        return sInstance;
    }

    static void preRetraceCallback(u32 retraceCount);
    static void postRetraceCallback(u32 retraceCount);

    void waitForRetrace();
    void fn_8023F45C();
    void fn_8023F4B8();
    void prepareCopyDisp();
    void copyDisp(GSxfbHandle *);
    void fn_8023F5E8(u32, u32, u32, u32);
    void fn_8023F778();
    bool fn_8023F858(VideoFormat, u32, u32, u32);
    void fn_8023FB04(bool);
    void fn_8023FBA0(GSxfbHandle *, u32);
    GSxfbHandle *fn_8023FC0C(XfbState);
    GSxfbHandle *fn_8023FC54(u32);
    void fn_8023FD64();
    void fn_8023FE30(bool);
    void setViewport(f32, f32, f32, f32, f32, f32);
    void setScissor(u32, u32, u32, u32);
    void setScissorBoxOffset(s32, s32);
    f32 fn_8023FFEC() const;

    void fn_8024041C();
    void fn_80240440();
};
