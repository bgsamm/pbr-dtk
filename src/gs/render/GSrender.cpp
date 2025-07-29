#include "global.hpp"

#include <cstring>
#include <revolution/cx.h>
#include <revolution/gx.h>
#include <revolution/os.h>
#include <revolution/vi.h>

#include "gs/GSmem.hpp"
#include "gs/GSrender.hpp"
#include "gs/GSvideo.hpp"

extern MEMHeapHandle lbl_8063E8E8;
extern MEMHeapHandle lbl_8063E8EC;

extern GSrenderClass3 *lbl_8063F6F0;
extern GSrenderClass5 *lbl_8063F728;

extern void *fn_80007940();
extern void *fn_800079C0();
extern void *fn_80007A40();
extern bool fn_8024A410(u32);
extern void fn_80250134(u32, u32, u32, u32, u32, u32);
extern void fn_8025B6B0();

// TODO properly fill in this data
static void *lbl_804245BC[0xc];

/* lbl_8063F698 */ GSrenderManager *GSrenderManager::sInstance;
/* lbl_8063F69C */ GSColor CLEAR(0, 0, 0, 0);
/* lbl_8063F6A0 */ GSColor BLACK(0, 0, 0, 255);
/* lbl_8063F6A4 */ GSColor WHITE(255, 255, 255, 255);

GSrenderManager::GSrenderManager(GSrenderStruct1 *param1)
    : GSvideoManager(param1->mNumBuffers, param1->mEfbHeight, param1->mVidFmt) {
    _d8 = lbl_804245BC;
    mState = NULL;
    _16e8 = 0;
    _16ec = NULL;
    _16f0 = 0;
    _16f4 = 0;
    _16f8 = true;
    _16f9 = true;
    _16fa = 0;
    _16fb = 0;
    _16fc = false;
    _16fd = 0;
    mFlags = 0;
    mDvdError = DVD_ERROR_OK;
    _1704 = 0;
    mFillColor.r = 0;
    mFillColor.g = 0;
    mFillColor.b = 0;
    mFillColor.a = 0;
    _170c = 0;
    _1710 = NULL;
    _1714 = NULL;
    _1718 = false;
    _1719 = true;
    _171a = 0;
    _171b = 0;
    _171c = 0;
    _1720 = 0;
    _1724 = 0;
    _1728 = NULL;
    _172c = NULL;
    _1730 = NULL;
    _1734 = NULL;
    mPrimitiveType = GX_TRIANGLES;
    mVertexFormat = NULL;
    memset(&_163c, 0, sizeof(_163c));
    mState = &_dc;
    _16e8 = new GSrenderClass1(param1->_C);
    fn_8023255C(param1->_8, param1->_10);
    sInstance = this;
    fn_80239E58();
    GXSetDrawDoneCallback(GSrender::fn_80232394);
    GXSetBreakPtCallback(GSrender::fn_8023234C);
    GXSetMisc(GX_MT_XF_FLUSH, GX_XF_FLUSH_SAFE);
    fn_8023B704();
    fn_80237798(4);
    fn_80235204(0, 0f, 0f, 640f, 480f);
    fn_80235178(0, 0, 0, 0x280, 0x1e0);
    fn_8024041C();
    fn_8023F45C();
    fn_802327E8();
    _1719 = false;
    _16f9 = false;
}

GSrenderManager::~GSrenderManager() {
    _d8 = lbl_804245BC;
    
    GXSetDrawDoneCallback(NULL);
    GXSetDrawSyncCallback(NULL);
    GXSetBreakPtCallback(NULL);

    fn_80232770();

    if (_16e8 != NULL) {
        delete _16e8;
        _16e8 = NULL;
    }

    sInstance = NULL;
}

void GSrenderManager::fn_802310C0() {
    BOOL intEnabled = OSDisableInterrupts();

    _1719 = true;

    if (_1728 != NULL) {
        _1728();
    }

    fn_8023B6B0();

    OSSetIdleFunction(NULL, NULL, NULL, 0);
    GXSetDrawDoneCallback(NULL);
    GXSetDrawSyncCallback(NULL);
    GXSetBreakPtCallback(NULL);
    GXSetTexRegionCallback(NULL);
    GXSetTlutRegionCallback(NULL);
    VISetPreRetraceCallback(NULL);
    VISetPostRetraceCallback(NULL);
    GXAbortFrame();

    if (_163c._88 != NULL) {
        memset(_163c._88, 0, _163c._84);
        DCFlushRange(_163c._88, _163c._84);
    }

    VISetBlack(TRUE);
    VIFlush();

    OSRestoreInterrupts(intEnabled);

    VIWaitForRetrace();
    VIWaitForRetrace();
}

void GSrenderManager::fn_802311AC(GSrenderStruct3 *param1) {
    param1->_0 = GSvideoManager::sInstance->mRetraceCount;
}

void GSrenderManager::fn_802311BC(GSrenderStruct3 *param1) {
    OSYieldThread();

    GXBool readIdle, dummy;
    GXGetGPStatus(&dummy, &dummy, &readIdle, &dummy, &dummy);
    if (readIdle == GX_TRUE) {
        return;
    }

    s32 var1 = GSvideoManager::sInstance->mRetraceCount - param1->_0;
    u32 var2 = GSvideoManager::sInstance->mRefreshRate * 3;
    if (var1 < 0 || _1719) {
        param1->_0 = GSvideoManager::sInstance->mRetraceCount;
    }
    else if (var1 > var2) {
        _1718 = true;
    }
}

void GSrenderManager::fn_8023125C(GSrenderStruct3 *param1) {

}


void GSrenderManager::fn_80231260() {
    fn_8023B6B0();

    GXAbortFrame();
    GSrender::fn_80232394();

    OSTime time = OSGetTime();
    _8c = (f32)(time - _98) / (OS_TIMER_CLOCK / mRefreshRate);
    _98 = time;

    fn_8023A95C();
    fn_8023AE54();

    GSxfbHandle *xfb;
    
    xfb = fn_8023FC0C(XFB_STATE_4);
    if (xfb != NULL) {
        xfb->mState = XFB_STATE_3;
    }

    xfb = fn_8023FC0C(XFB_STATE_2);
    if (xfb != NULL) {
        xfb->mState = XFB_STATE_3;
    }
    
    xfb = fn_8023FC0C(XFB_STATE_1);
    if (xfb != NULL) {
        xfb->mState = XFB_STATE_2;
    }

    mWaitForRetrace = true;
    _1718 = false;
}

void GSrender::fn_80231374(void *param1) {
    GSrenderManager::sInstance->fn_8023F778();
    
    GSrenderManager::sInstance->_16f8 = true;
    GSrenderManager::sInstance->_16f4 = 0;
}

void GSrenderManager::fn_802313B0() {
    if (!_1718) {
        _16f4 = fn_80232404(GSrender::fn_80231374, this);
        _16f8 = false;
    }
}

void GSrenderManager::fn_80231400() {
    if (_16f8) {
        return;
    }

    BOOL intEnabled = OSEnableInterrupts();

    while (!_16f8) {
        if (fn_8023B864(_16f4) != 0) {
            _16f8 = true;
            _16f4 = 0;
        }
    }
    
    OSRestoreInterrupts(intEnabled);
}


void GSrenderManager::fn_80231490(f32 param1) {
    f32 var1;
    if (_82) {
        var1 = 0f;
    }
    else {
        var1 = param1;
    }

    fn_8025B6B0();

    GSrenderClass3 *var2 = lbl_8063F6F0;
    while (var2 != NULL) {
        var2->func1(var1);
        var2 = (GSrenderClass3 *)var2->_8;
    }

    if (_1730 != NULL) {
        _1730(param1);
    }
}

void GSrenderManager::fn_80231544() {
    _16ec = NULL;
    _16f9 = true;

    fn_8023A95C();
    setScissorBoxOffset(0, 0);
    fn_80235204(0, 0f, 0f, 640f, 480f);
    fn_80235178(0, 0, 0, 640, 480);

    GSrenderClass3 *var1 = lbl_8063F6F0;
    while (var1 != NULL) {
        var1->func2();
        var1 = (GSrenderClass3 *)var1->_8;
    }

    GSrenderClass5 *var2 = lbl_8063F728;
    while (var2 != NULL) {
        var2->func1();
        var2 = (GSrenderClass5 *)var2->_18;
    }

    var2 = lbl_8063F728;
    while (var2 != NULL) {
        var2->func2();
        var2 = (GSrenderClass5 *)var2->_18;
    }

    mState->mCurr.mFogEnable = false;
    mState->_64 |= (1 << 6);
    mState->_0 |= (1 << 6);

    if (_172c != NULL) {
        _172c();
    }

    fn_80240440();

    if (mDvdError != DVD_ERROR_OK) {
        fn_80231918();
    }

    if (_1734 != NULL) {
        _1734();
    }

    mState->mCurr.mColorUpdateEnable = true;
    mState->mCurr.mAlphaUpdateEnable = true;
    mState->mCurr.mZUpdateEnable = true;
    mState->_64 |= (1 << 2);
    mState->_0 |= (1 << 6);

    fn_80235204(0, 0f, 0f, 640f, 480f);
    fn_80235178(0, 0, 0, 640, 480);
    fn_8023AE54();
    prepareCopyDisp();
    fn_8023F4B8();
    fn_802313B0();
    fn_802327E8();

    if (_1718) {
        fn_80231260();
    }

    waitForRetrace();
    
    _16ec = NULL;
    _16f9 = false;
}


void GSrenderManager::fn_8023177C(GSdvdError error, u32 param2, GSColor color) {
    mDvdError = error;
    _1704 = param2;
    mFillColor.r = color.r;
    mFillColor.g = color.g;
    mFillColor.b = color.b;
    mFillColor.a = color.a;

    if (error == DVD_ERROR_OK) {
        if (_1714 != NULL) {
            GSrender::fn_8023E2D0(_1714);
            _1714 = NULL;
        }

        if (_1710 != NULL) {
            GSmem::freeToHeap(_170c, _1710);
            _170c = NULL;
            _1710 = NULL;
        }

        return;
    }

    if (param2 == 0 || !fn_8024A410(param2)) {
        void *src;
        switch (error) {
            case DVD_ERROR_COVER_OPEN:
            case DVD_ERROR_NO_DISK:
            case DVD_ERROR_WRONG_DISK:
                src = fn_80007940();
                break;
            
            case DVD_ERROR_RETRY:
                src = fn_800079C0();
                break;
            
            case DVD_ERROR_FATAL:
                src = fn_80007A40();
                break;
            
            default:
                return;
        }

        u32 size = CXGetUncompressedSize(src);

        _1710 = GSmem::allocFromHeapAligned(lbl_8063E8E8, size, 0x20);
        _170c = lbl_8063E8E8;

        if (_1710 == NULL) {
            _1710 = GSmem::allocFromHeapAligned(lbl_8063E8EC, size, 0x20);
            _170c = lbl_8063E8EC;
        }

        if (_1710 != NULL) {
            CXUncompressLZ(src, _1710);
            DCFlushRange(_1710, size);
            _1714 = GSrender::fn_8023D6CC(_1710);
        }
    }

    if (error == DVD_ERROR_FATAL) {
        fn_802321DC();
    }
}

void GSrenderManager::fn_80231918() {
    GSrenderState *state;
    
    if (mDvdError == DVD_ERROR_OK) {
        return;
    }

    if (mDvdError == DVD_ERROR_COVER_OPEN) {
        return;
    }

    fn_80235204(0, 0f, 0f, 640f, 480f);
    fn_80235178(0, 0, 0, 640, 480);
    fn_80234FE0(0f, 0f, 640f, 480f, 0f, 100000f);

    mState->mCurr.mColorUpdateEnable = GX_TRUE;
    mState->mCurr.mAlphaUpdateEnable = GX_FALSE;
    mState->mCurr.mZUpdateEnable = GX_FALSE;
    mState->_64 |= (1 << 2);
    mState->_0 |= (1 << 6);

    mState->mCurr.mAlphaComp0 = GX_ALWAYS;
    mState->mCurr.mAlphaRef0 = 0;
    mState->mCurr.mAlphaOp = GX_AOP_AND;
    mState->mCurr.mAlphaComp1 = GX_ALWAYS;
    mState->mCurr.mAlphaRef1 = 0;
    mState->mCurr.mZCompBeforeTex = GX_TRUE;
    mState->_64 |= (1 << 4);
    mState->_0 |= (1 << 6);

    mState->mCurr.mZCompareEnable = GX_FALSE;
    mState->mCurr.mZCompareFunc = GX_LEQUAL;
    mState->_64 |= (1 << 3);
    mState->_0 |= (1 << 6);
    
    mState->mCurr.mClipMode = GX_CLIP_DISABLE;
    mState->_10 |= (1 << 2);
    mState->_0 |= (1 << 1);
    
    mState->mCurr.mCullMode = GX_CULL_NONE;
    mState->_10 |= (1 << 1);
    mState->_0 |= (1 << 1);
    
    mState->mCurr.mFogEnable = false;
    mState->_64 |= (1 << 6);
    mState->_0 |= (1 << 6);

    if (_1704 != 0 && fn_8024A410(_1704)) {
        if (mFillColor.a == 255) {
            mState->mCurr.mBlendMode = GX_BM_NONE;
            mState->mCurr.mBlendSrcFactor = GX_BL_ONE;
            mState->mCurr.mBlendDstFactor = GX_BL_ONE;
            mState->mCurr.mBlendOp = GX_LO_NOOP;
            mState->_64 |= (1 << 0);
            mState->_0 |= (1 << 6);
        }
        else {
            mState->mCurr.mBlendMode = GX_BM_BLEND;
            mState->mCurr.mBlendSrcFactor = GX_BL_SRCALPHA;
            mState->mCurr.mBlendDstFactor = GX_BL_INVSRCALPHA;
            mState->mCurr.mBlendOp = GX_LO_NOOP;
            mState->_64 |= (1 << 0);
            mState->_0 |= (1 << 6);
        }

        mState->mCurr.mNumTevStages = 1;
        mState->_24 |= (1 << 0);
        mState->_0 |= (1 << 3);
        
        mState->mCurr.mNumTexGens = 0;
        mState->_4 |= (1 << 0);
        mState->_0 |= (1 << 0);
        
        mState->mCurr.mNumChans = 1;
        mState->_14 |= (1 << 0);
        mState->_0 |= (1 << 2);
        
        mState->mCurr.mNumIndStages = 0;
        mState->_44 |= (1 << 0);
        mState->_0 |= (1 << 7);

        fn_8023378C(0, 3, 1, 1, 0, 0, 2, 0);

        if (mState->mCurr.mIndTexStages[0].mType != TEV_NULL) {
            mState->mCurr.mIndTexStages[0].mType = TEV_DIRECT;
        }
        mState->mIndTexStageFlags |= (1 << 0);
        mState->_0 |= (1 << 3);

        state = mState;
        state->mCurr.mTevStages[0].mTexCoord = GX_TEXCOORD_NULL;
        state->mCurr.mTevStages[0].mTexMap = GX_TEXMAP_NULL;
        state->mCurr.mTevStages[0].mChannel = GX_COLOR0A0;
        mState->mTevStageFlags |= (1 << 0);
        mState->_0 |= (1 << 3);

        fn_80233B88(0, 4);

        state = mState;
        state->mCurr.mTevSwapModes[0].mRasSel = GX_TEV_SWAP0;
        state->mCurr.mTevSwapModes[0].mTexSel = GX_TEV_SWAP0;
        mState->mTevSwapModeFlags |= (1 << 0);
        mState->_0 |= (1 << 5);

        mVertexFormat = GSrender::fn_8023CF1C(2);
        mPrimitiveType = GX_TRIANGLESTRIP;

        fn_8023352C(4);
            // vert 1
            GXPosition2f32(0f, 0f);
            GXColor1u32(mFillColor.rgba);
            // vert 2
            GXPosition2f32(0f, 480f);
            GXColor1u32(mFillColor.rgba);
            // vert 3
            GXPosition2f32(640f, 0f);
            GXColor1u32(mFillColor.rgba);
            // vert 4
            GXPosition2f32(640f, 480f);
            GXColor1u32(mFillColor.rgba);
        fn_80233580();
        fn_80250134(_1704, 100, 200, 0, 0, -1);
    }
    else if (_1714 != NULL) {
        u16 w = GSrender::fn_8023E540(_1714);
        f32 width;
        OSu16tof32(&w, &width);
        f32 centerX = 0.5f * width;
        
        u16 h = GSrender::fn_8023E548(_1714);
        f32 height;
        OSu16tof32(&h, &height);
        f32 centerY = 0.5f * height;

        mState->mCurr.mBlendMode = GX_BM_NONE;
        mState->mCurr.mBlendSrcFactor = GX_BL_ONE;
        mState->mCurr.mBlendDstFactor = GX_BL_ONE;
        mState->mCurr.mBlendOp = GX_LO_NOOP;
        mState->_64 |= (1 << 0);
        mState->_0 |= (1 << 6);

        mState->mCurr.mNumTevStages = 1;
        mState->_24 |= (1 << 0);
        mState->_0 |= (1 << 3);
        
        mState->mCurr.mNumTexGens = 0;
        mState->_4 |= (1 << 0);
        mState->_0 |= (1 << 0);
        
        mState->mCurr.mNumChans = 1;
        mState->_14 |= (1 << 0);
        mState->_0 |= (1 << 2);
        
        mState->mCurr.mNumIndStages = 0;
        mState->_44 |= (1 << 0);
        mState->_0 |= (1 << 7);
        
        mVertexFormat = GSrender::fn_8023CF1C(2);
        mPrimitiveType = GX_TRIANGLESTRIP;

        fn_8023352C(4);
            // vert 1
            GXPosition2f32(0f, 0f);
            GXColor1u32(0);
            // vert 2
            GXPosition2f32(0f, 480f);
            GXColor1u32(0);
            // vert 3
            GXPosition2f32(640f, 0f);
            GXColor1u32(0);
            // vert 4
            GXPosition2f32(640f, 480f);
            GXColor1u32(0);
        fn_80233580();

        mState->mCurr.mNumTevStages = 1;
        mState->_24 |= (1 << 0);
        mState->_0 |= (1 << 3);

        mState->mCurr.mNumTexGens = 1;
        mState->_4 |= (1 << 0);
        mState->_0 |= (1 << 0);
        
        mState->mCurr.mNumChans = 0;
        mState->_14 |= (1 << 0);
        mState->_0 |= (1 << 2);
        
        mState->mCurr.mNumIndStages = 0;
        mState->_44 |= (1 << 0);
        mState->_0 |= (1 << 7);

        fn_80234474(0, 1, 4, 0, 0, 0);

        if (mState->_153c != _1714 || (_1714->_7 & (1 << 0)) == (1 << 0)) {
            mState->_153c = _1714;
            mState->_1538 |= (1 << 0);
        }

        if (mState->mCurr.mIndTexStages[0].mType != TEV_NULL) {
            mState->mCurr.mIndTexStages[0].mType = TEV_DIRECT;
        }
        mState->mIndTexStageFlags |= (1 << 0);
        mState->_0 |= (1 << 3);

        state = mState;
        state->mCurr.mTevStages[0].mTexCoord = GX_TEXCOORD0;
        state->mCurr.mTevStages[0].mTexMap = GX_TEXMAP0;
        state->mCurr.mTevStages[0].mChannel = GX_COLOR_NULL;
        mState->mTevStageFlags |= (1 << 0);
        mState->_0 |= (1 << 3);

        fn_80233B88(0, 3);

        state = mState;
        state->mCurr.mTevSwapModes[0].mRasSel = GX_TEV_SWAP0;
        state->mCurr.mTevSwapModes[0].mTexSel = GX_TEV_SWAP0;
        mState->mTevSwapModeFlags |= (1 << 0);
        mState->_0 |= (1 << 5);
        
        mVertexFormat = GSrender::fn_8023CF1C(5);
        mPrimitiveType = GX_TRIANGLESTRIP;

        fn_8023352C(4);
            // vert 1
            GXPosition2f32(320f - centerX, 240f - centerY);
            GXTexCoord2f32(0f, 0f);
            // vert 2
            GXPosition2f32(320f - centerX, 240f + centerY);
            GXTexCoord2f32(0f, 1f);
            // vert 3
            GXPosition2f32(320f + centerX, 240f - centerY);
            GXTexCoord2f32(1f, 0f);
            // vert 4
            GXPosition2f32(320f + centerX, 240f + centerY);
            GXTexCoord2f32(1f, 1f);
        fn_80233580();
    }
}

void GSrenderManager::fn_802321DC() {
    _16ec = NULL;
    _16f9 = true;
    mFillColor.r = 0;
    mFillColor.g = 0;
    mFillColor.b = 0;
    mFillColor.a = 255;

    fn_8023A95C();
    setScissorBoxOffset(0, 0);
    fn_80231918();

    mState->mCurr.mColorUpdateEnable = GX_TRUE;
    mState->mCurr.mAlphaUpdateEnable = GX_TRUE;
    mState->mCurr.mZUpdateEnable = GX_TRUE;
    mState->_64 |= (1 << 2);
    mState->_0 |= (1 << 6);

    fn_8023AE54();
    prepareCopyDisp();
    fn_8023F4B8();
    fn_802313B0();
    fn_80231400();
    fn_802327E8();

    mWaitForRetrace = true;
    waitForRetrace();

    _16ec = NULL;
    _16f9 = false;

    OSPanic(__FILE__, 1072, "Fatal Error occurred");
}
