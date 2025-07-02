#include "version.hpp"
#include <cstring>

#include "gs/GSmem.hpp"
#include "gs/GSrender.hpp"
#include "gs/GSvideo.hpp"

extern void fn_8025B6B4(u32);
extern void fn_8025B6B8(f32 *, f32 *);

extern f32 lbl_8063D988;
extern GSrender *lbl_8063F698;

static UnkStruct7 lbl_80424840[10];
static void *lbl_8042491C[0x10]; // dummy

GSvideo *GSvideo::sInstance;

void GSvideo::preRetraceCallback(u32 retraceCount) {
    if (sInstance == NULL) {
        return;
    }

    if (sInstance->_81 == 1 && sInstance->_80 > 0) {
        sInstance->_80--;
        return;
    }

    XfbInfo *xfb = sInstance->fn_8023FC0C(XFB_STATE_2);
    if (xfb == NULL) {
        sInstance->_84++;
        return;
    }

    sInstance->mWaitForRetrace = false;
    sInstance->_88++;

    VISetNextFrameBuffer(xfb->buf);
    VIFlush();

    xfb->state = XFB_STATE_1;
    sInstance->mActiveXfb->state = XFB_STATE_3;
    sInstance->mActiveXfb = xfb;
    sInstance->_80 = sInstance->_7c;
}

void GSvideo::postRetraceCallback(u32 retraceCount) {
    if (sInstance == NULL) {
        return;
    }

    sInstance->mRetraceCount++;

    if (sInstance->mRetraceCallback != NULL) {
        u8 var1 = lbl_8063F698->_16f9;
        lbl_8063F698->_16f9 = 0;
        sInstance->mRetraceCallback(retraceCount);
        lbl_8063F698->_16f9 = var1;
    }
}

GSvideo::GSvideo(u8 numBuffers, u16 efbHeight, VideoFormat videoFmt) {
    _d8 = lbl_8042491C;
    mActiveXfb = NULL;
    mNumBuffers = numBuffers;
    mRefreshRate = (videoFmt == VID_FMT_PAL) ? 50 : 60;
    mNextField = 0;
    mWaitForRetrace = true;
    mEfbHeight = efbHeight;
    mXfbHeight = 528;
    mGamma = GX_GM_1_0;
    mPixelFmt = GX_PF_RGB8_Z24;
    mYScale = 1f;
    mRetraceCount = 0;
    mVideoFmt = videoFmt;
    mRetraceCallback = NULL;
    _78 = 0xa;
    _79 = 0;
    _7a = 0;
    _7c = 0;
    _80 = 0;
    _81 = 1;
    _82 = 0;
    _83 = 0;
    _84 = 0;
    _88 = 0;
    _8c = 0f;
    _90 = 0f;
    _98 = 0;
    _a0 = 0.0;
    _a8.ival = 0;
    _ac.ival = 0;
    _b0.ival = 0;
    _b4.ival = 0;
    _b8.ival = 0;
    _bc.ival = 0;
    _a8.fval = 0f;
    _ac.fval = 0f;
    _b0.fval = 640f;
    _b4.fval = 480f;
    _c0_u32 = 0;
    _c4_u32 = 0;
    mScissorXOrig = 0;
    mScissorYOrig = 0;
    mScissorWidth = 640;
    mScissorHeight = 480;
    _c8 = 0;
    _cc = 0;
    lbl_8063D988 = (f32)mRefreshRate / 60f;

    if (numBuffers == 0) {
        return;
    }

    if (numBuffers > MAX_XFBS) {
        return;
    }

    if (efbHeight > 528) {
        return;
    }

    VIInit();
    mRefreshRate = 60;

    int var2;
    VideoFormat fmt;
    if (SCGetProgressiveMode() == SC_PROGRESSIVE_MODE_ON && VIGetDTVStatus() == 1) {
        VIGetScanMode();
        if (VIGetTvFormat() == VI_NTSC) {
            fmt = VID_FMT_NTSC;
        }
        else {
            fmt = VID_FMT_EURGB60;
        }
        var2 = 1;
    }
    else {
        if (VIGetTvFormat() == VI_NTSC) {
            fmt = VID_FMT_NTSC;
        }
        else if (SCGetEuRgb60Mode() == SC_EURGB60_MODE_ON) {
            VIGetTvFormat();
            fmt = VID_FMT_EURGB60;
        }
        else {
            VIGetTvFormat();
            fmt = VID_FMT_PAL;
            mRefreshRate = 50;
        }
        var2 = 0;
    }

    bool aspectRatio = (SCGetAspectRatio() == 1);
    lbl_8063D988 = mRefreshRate / 60f;
    fn_8023F858(fmt, var2, 1, aspectRatio);

    switch (fmt) {
        case VID_FMT_NTSC:
            mXfbHeight = 480;
            break;
        case VID_FMT_PAL:
        case VID_FMT_EURGB60:
            if (fmt == VID_FMT_PAL && var2 != 1) {
                mYScale = 1.1f;
                mXfbHeight = GXGetNumXfbLines(mRenderMode.efbHeight, mYScale);
            }
            break;
        case VID_FMT_MPAL:
            mXfbHeight = 480;
            break;
    }

    u32 xfbWidth = (mRenderMode.fbWidth + 0xf) & 0xfff0;
    u32 size = xfbWidth * mXfbHeight * VI_DISPLAY_PIX_SZ;
    for (int i = 0; i < MAX_XFBS; i++) {
        if (i < mNumBuffers) {
            mXfbs[i].buf = GSmem::allocFromDefaultHeap(size);
            mXfbs[i].state = XFB_STATE_3;
            fn_8023FBA0(&mXfbs[i], size);
        }
        else {
            mXfbs[i].buf = NULL;
            mXfbs[i].state = XFB_STATE_UNUSED;
        }
    }

    mClearColor.r = 0;
    mClearColor.g = 0;
    mClearColor.b = 0;
    mClearColor.a = 0;
    mClearZ = GX_MAX_Z24;
    VISetPreRetraceCallback(preRetraceCallback);
    VISetPostRetraceCallback(postRetraceCallback);

    mXfbs[0].state = XFB_STATE_1;
    VISetNextFrameBuffer(mXfbs[0].buf);
    mActiveXfb = &mXfbs[0];
    _98 = OSGetTime();
    sInstance = this;
    fn_8023FB04(false);
}

GSvideo::~GSvideo() {
    _d8 = lbl_8042491C;

    VISetPreRetraceCallback(NULL);
    VISetPostRetraceCallback(NULL);
    VISetBlack(TRUE);
    VIFlush();

    mWaitForRetrace = true;
    waitForRetrace();

    for (int i = 0; i < mNumBuffers; i++) {
        if (mXfbs[i].buf != NULL) {
            GSmem::freeDefaultHeapBlock(mXfbs[i].buf);
            mXfbs[i].buf = NULL;
        }
    }

    sInstance = NULL;
}

void GSvideo::waitForRetrace() {
    if (mWaitForRetrace) {
        VIWaitForRetrace();
    }
    mWaitForRetrace = true;
}

void GSvideo::fn_8023F45C() {
    prepareCopyDisp();
    copyDisp(mActiveXfb);
    copyDisp(mActiveXfb);
    mActiveXfb->state = XFB_STATE_1;
    VISetBlack(FALSE);
    VIFlush();
}

void GSvideo::fn_8023F4B8() {
    XfbInfo *var1 = fn_8023FC54(1);
    fn_8025B6B4(0);

    if (var1 != NULL) {
        copyDisp(var1);
    }
}

void GSvideo::prepareCopyDisp() {
    if (sInstance == NULL) {
        return;
    }

    GXSetDispCopySrc(0, 0, mRenderMode.fbWidth, mRenderMode.efbHeight);
    GXSetDispCopyDst(mRenderMode.fbWidth, mRenderMode.xfbHeight);
    GXSetDispCopyFrame2Field(GX_COPY_PROGRESSIVE);
    GXSetDispCopyGamma(mGamma);
    GXSetDispCopyYScale(mYScale);
    GXSetCopyFilter(mRenderMode.aa, mRenderMode.sample_pattern, GX_TRUE, mRenderMode.vfilter);
    GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
    GXSetCopyClear(mClearColor, mClearZ);
}

void GSvideo::copyDisp(XfbInfo *xfb) {
    if (sInstance == NULL) {
        return;
    }
    xfb->state = XFB_STATE_4;
    GXCopyDisp(xfb->buf, GX_TRUE);
}

void GSvideo::fn_8023F778() {
    XfbInfo *var1 = fn_8023FC0C(XFB_STATE_4);
    if (var1 == NULL) {
        return;
    }

    if (mNumBuffers == 3) {
        XfbInfo *var2 = fn_8023FC0C(XFB_STATE_2);
        if (var2) {
            var2->state = XFB_STATE_3;
        }
    }

    OSTime time = OSGetTime();
    _8c = (f32)(time - _98) / (OS_TIMER_CLOCK / mRefreshRate);
    _98 = time;

    var1->state = XFB_STATE_2;
}

bool GSvideo::fn_8023F858(VideoFormat vidFmt, u32 param2, u32 param3, u32 param4) {
    int var1 = 0;

    switch (param2) {
        case 2:
            switch (param3) {
                case 0:
                case 1:
                    var1 = 1;
                    break;
                case 2:
                    var1 = 2;
                    break;
            }
            break;
        case 0:
            switch (param3) {
                case 0:
                    var1 = 5;
                    break;
                case 1:
                    var1 = 6;
                    break;
                case 2:
                    var1 = 7;
                    break;
            }
            break;
        case 1:
            switch (param3) {
                case 0:
                    var1 = 8;
                    break;
                case 1:
                    var1 = 9;
                    break;
                case 2:
                    var1 = 10;
                    break;
            }
            break;
        case 3:
            switch (param3) {
                case 0:
                case 1:
                    var1 = 3;
                    break;
                case 2:
                    var1 = 4;
                    break;
            }
            break;
    }

    if (var1 == 0) {
        return false;
    }


    UnkStruct7 *ptr = lbl_80424840;
    GXRenderModeObj *rmode = NULL;
    u16 var3;
    while (ptr->_0 != 0) {
        if (ptr->_0 == var1) {
            switch (vidFmt) {
                case VID_FMT_NTSC:
                    rmode = ptr->ntsc;
                    var3 = 720;
                    break;
                case VID_FMT_PAL:
                    rmode = ptr->pal;
                    var3 = 720;
                    break;
                case VID_FMT_EURGB60:
                    rmode = ptr->eurgb60;
                    var3 = 720;
                    break;
                case VID_FMT_MPAL:
                    rmode = ptr->mpal;
                    var3 = 720;
                    break;
            }
            break;
        }
        ptr++;
    }

    if (rmode == 0) {
        return false;
    }

    memcpy(&mRenderMode, rmode, sizeof(GXRenderModeObj));

    if (mEfbHeight != 0) {
        mRenderMode.efbHeight = mEfbHeight;
    }

    _7a = param4;
    if (param4 != 0) {
        mRenderMode.viWidth = var3;
        if (vidFmt == VID_FMT_PAL) {
            mRenderMode.viWidth = var3 - 40;
        }
    }
    else {
        if (vidFmt != VID_FMT_PAL) {
            mRenderMode.viWidth += 20;
        }
        if (mRenderMode.viWidth > var3) {
            mRenderMode.viWidth = var3;
        }
    }

    mRenderMode.viXOrigin = (var3 - mRenderMode.viWidth) >> 1; // dividing by 2 does not match
    
    mVideoFmt = vidFmt;
    if (vidFmt == VID_FMT_PAL) {
        mRefreshRate = 50;
    }
    else {
        mRefreshRate = 60;
    }
    lbl_8063D988 = mRefreshRate / 60f;
    mYScale = GXGetYScaleFactor(mRenderMode.efbHeight, mRenderMode.xfbHeight);
    return true;
}

void GSvideo::fn_8023FB04(bool param1) {
    VISetPreRetraceCallback(NULL);
    VISetPostRetraceCallback(NULL);
    VISetBlack(TRUE);
    VIConfigure(&mRenderMode);
    VIFlush();
    mWaitForRetrace = true;
    waitForRetrace();
    waitForRetrace();
    VISetPreRetraceCallback(preRetraceCallback);
    VISetPostRetraceCallback(postRetraceCallback);
    if (param1 == true) {
        VISetBlack(FALSE);
        VIFlush();
    }
}

void GSvideo::fn_8023FBA0(XfbInfo *param1, u32 param2) {
    u32 *ptr = (u32 *)param1->buf;
    for (u32 i = 0; i != param2 / 4; i++) {
        *(ptr + i) = 0x10801080;
    }
    DCFlushRange(param1->buf, param2);
}

XfbInfo *GSvideo::fn_8023FC0C(XfbState param1) {
    for (int i = 0; i < mNumBuffers; i++) {
        if (mXfbs[i].state == param1) {
            return &mXfbs[i];
        }
    }
    return NULL;
}

XfbInfo *GSvideo::fn_8023FC54(u32 param1) {
    if (lbl_8063F698->_1718) {
        return NULL;
    }

    UnkStruct8 var1;
    lbl_8063F698->fn_802311AC(&var1);

    XfbInfo *var2;
    u32 var3 = param1;
    while (true) {
        BOOL intEnabled = OSDisableInterrupts();
        
        if (lbl_8063F698->_1718 || lbl_8063F698->_1719) {
            var2 = NULL;
            var3 = 0;
        }
        else {
            var2 = fn_8023FC0C(XFB_STATE_3);
        }

        OSRestoreInterrupts(intEnabled);

        if (var3 == 0 || var2 != NULL) {
            lbl_8063F698->fn_8023125C(&var1);
            return var2;
        }

        lbl_8063F698->fn_802311BC(&var1);

        GXBool readIdle, dummy;
        GXGetGPStatus(&dummy, &dummy, &readIdle, &dummy, &dummy);

        if (readIdle == GX_TRUE) {
            lbl_8063F698->fn_80231374();
        }
    }
}

void GSvideo::fn_8023FD64() {
    _90 = _8c;
    if (_90 > 5.00001f) {
        _90 = 5.0f;
    }

    if (_83 == 0 && _82 == 0) {
        _a0 += fn_8023FFEC();
    }

    GXBool half_aspect_ratio = (mRenderMode.viHeight >= 2 * mRenderMode.xfbHeight);
    GXSetFieldMode(mRenderMode.field_rendering, half_aspect_ratio);

    if (mRenderMode.aa == GX_TRUE) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    }
    else {
        GXSetPixelFmt(mPixelFmt, GX_ZC_LINEAR);
    }

    mNextField = VIGetNextField();
    GXFlush();
}

void GSvideo::fn_8023FE30(u32 param1) {
    f32 var1, var2;

    if (param1 != 0) {
        fn_8025B6B8(&var1, &var2);
    }
    else {
        var1 = 0f;
        var2 = 0f;
    }

    if (mRenderMode.field_rendering) {
        GXSetViewportJitter(_a8.fval + var1, _ac.fval + var2, _b0.fval, _b4.fval, _b8.fval, _bc.fval, mNextField);
    }
    else {
        GXSetViewport(_a8.fval + var1, _ac.fval + var2, _b0.fval, _b4.fval, _b8.fval, _bc.fval);
    }
}

void GSvideo::fn_8023FEE8(f32 param1, f32 param2, f32 param3, f32 param4, f32 param5, f32 param6) {
    _a8.fval = param1;
    _ac.fval = param2;
    _b0.fval = param3;
    _b4.fval = param4;
    _b8.fval = param5;
    _bc.fval = param6;
    fn_8023FE30(1);
}

void GSvideo::setScissor(u32 xOrig, u32 yOrig, u32 width, u32 height) {
    mScissorXOrig = xOrig;
    mScissorYOrig = yOrig;
    mScissorWidth = width;
    mScissorHeight = height;

    u16 xMax, yMax;
    // TODO presumably inlining
    if (&xMax != NULL) {
        *(&xMax) = mRenderMode.fbWidth;
    }
    if (&yMax != NULL) {
        *(&yMax) = mRenderMode.efbHeight;
    }
    --xMax;
    --yMax;

    // TODO revisit all this casting
    if (xOrig > xMax) {
        xOrig = xMax;
    }

    if ((int)((u16)xOrig + width) > xMax) {
        width = (u16)(xMax - xOrig);
    }

    if (yOrig > yMax) {
        yOrig = yMax;
    }

    if ((int)((u16)yOrig + height) > yMax) {
        height = (u16)(yMax - yOrig);
    }
    
    GXSetScissor((u16)xOrig, (u16)yOrig, width, height);
}

void GSvideo::setScissorBoxOffset(s32 param1, s32 param2) {
    _c8 = param1;
    _cc = param2;
    GXSetScissorBoxOffset(param1, param2);
}

f32 GSvideo::fn_8023FFEC() {
    if (_82) {
        return 0f;
    }

    if (_81) {
        return _90;
    }

    return _7c + 1;
}
