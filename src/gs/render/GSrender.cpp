#include "gs/GSrender.hpp"

#include ".unsorted/8025B6AC.hpp"
#include "gs/GSmem.hpp"
#include "gs/GSvideo.hpp"
#include "gs/render/80236704.hpp"
#include "gs/render/GSrenderModule.hpp"
#include "gs/render/GSrenderTarget.hpp"

#include <cstring>
#include <revolution.h>
#include <revolution/cx.h>

#include "common.hpp"

extern void *fn_80007940();
extern void *fn_800079C0();
extern void *fn_80007A40();
extern bool fn_8024A410(u32);
extern void fn_80250134(u32, u32, u32, u32, u32, u32);

/* lbl_8063F698 */ GSrender *GSrender::sInstance;
/* lbl_8063F69C */ static GScolor CLEAR(0, 0, 0, 0);
/* lbl_8063F6A0 */ static GScolor BLACK(0, 0, 0, 255);
/* lbl_8063F6A4 */ static GScolor WHITE(255, 255, 255, 255);

GSrender::GSrender(GSrenderStruct1 *param1) : GSvideo(param1->mNumBuffers, param1->mEfbHeight, param1->mVidFmt) {
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
    memset(&mGraphicsFifo, 0, sizeof(mGraphicsFifo));
    mState = &_dc;
    _16e8 = new _UnkClass80236704(param1->_C);
    fn_8023255C(param1->_8, param1->_10);
    sInstance = this;
    fn_80239E58();
    GXSetDrawDoneCallback(fn_80232394);
    GXSetBreakPtCallback(fn_8023234C);
    GXSetMisc(GX_MT_XF_FLUSH, GX_XF_FLUSH_SAFE);
    fn_8023B704();
    fn_80237798(4);
    fn_80235204(0, 0.f, 0.f, 640.f, 480.f);
    fn_80235178(0, 0, 0, 0x280, 0x1e0);
    fn_8024041C();
    fn_8023F45C();
    fn_802327E8();
    _1719 = false;
    _16f9 = false;
}

GSrender::~GSrender() {
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

void GSrender::fn_802310C0() {
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

    if (mGraphicsFifo._88 != NULL) {
        memset(mGraphicsFifo._88, 0, mGraphicsFifo._84);
        DCFlushRange(mGraphicsFifo._88, mGraphicsFifo._84);
    }

    VISetBlack(TRUE);
    VIFlush();

    OSRestoreInterrupts(intEnabled);

    VIWaitForRetrace();
    VIWaitForRetrace();
}

void GSrender::fn_802311AC(u32 *param1) {
    *param1 = GSvideo::getInstance()->getRetraceCount();
}

void GSrender::fn_802311BC(u32 *param1) {
    OSYieldThread();

    GXBool readIdle, dummy;
    GXGetGPStatus(&dummy, &dummy, &readIdle, &dummy, &dummy);
    if (readIdle == GX_TRUE) {
        return;
    }

    s32 var1 = GSvideo::sInstance->getRetraceCount() - *param1;
    u32 var2 = GSvideo::sInstance->getRefreshRate() * 3;
    if (var1 < 0 || _1719) {
        *param1 = GSvideo::sInstance->getRetraceCount();
    } else if (var1 > var2) {
        _1718 = true;
    }
}

void GSrender::fn_8023125C(u32 *param1) {}

void GSrender::fn_80231260() {
    fn_8023B6B0();

    GXAbortFrame();
    fn_80232394();

    OSTime time = OSGetTime();
    _8c = (f32)(time - _98) / (OS_TIMER_CLOCK / mRefreshRate);
    _98 = time;

    fn_8023A95C();
    sync();

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

void fn_80231374(void *param1) {
    GSrender::sInstance->fn_8023F778();

    GSrender::sInstance->set_16f8(true);
    GSrender::sInstance->set_16f4(0);
}

void GSrender::fn_802313B0() {
    if (!_1718) {
        _16f4 = fn_80232404(fn_80231374, this);
        _16f8 = false;
    }
}

void GSrender::fn_80231400() {
    if (_16f8) {
        return;
    }

    BOOL intEnabled = OSEnableInterrupts();

    while (!_16f8) {
        if (fn_8023B864(_16f4)) {
            _16f8 = true;
            _16f4 = 0;
        }
    }

    OSRestoreInterrupts(intEnabled);
}

void GSrender::update(f32 deltaTime) {
    f32 gameDeltaTime = mHomeMenuActive ? 0.f : deltaTime;

    fn_8025B6B0();

    GSrenderModule *module = GSrenderModule::getModuleList();
    while (module) {
        module->update(gameDeltaTime);
        module = module->getNext();
    }

    if (_1730) {
        _1730(deltaTime);
    }
}

void GSrender::draw() {
    _16ec = NULL;
    _16f9 = true;

    fn_8023A95C();
    setScissorBoxOffset(0, 0);
    fn_80235204(0, 0.f, 0.f, 640.f, 480.f);
    fn_80235178(0, 0, 0, 640, 480);

    GSrenderModule *module = GSrenderModule::getModuleList();
    while (module) {
        module->fn_80236AE0();
        module = module->getNext();
    }

    GSrenderTarget *target = GSrenderTarget::getTargetList();
    while (target) {
        target->fn_8023B59C();
        target = target->getNext();
    }

    target = GSrenderTarget::getTargetList();
    while (target) {
        target->fn_8023B5A0();
        target = target->getNext();
    }

    mState->mCurr.mFogEnable = false;
    mState->_64 |= (1 << 6);
    mState->_0 |= (1 << 6);

    if (_172c) {
        _172c();
    }

    fn_80240440();

    if (mDvdError != DVD_ERROR_OK) {
        fn_80231918();
    }

    if (_1734) {
        _1734();
    }

    mState->mCurr.mColorUpdateEnable = true;
    mState->mCurr.mAlphaUpdateEnable = true;
    mState->mCurr.mZUpdateEnable = true;
    mState->_64 |= (1 << 2);
    mState->_0 |= (1 << 6);

    fn_80235204(0, 0.f, 0.f, 640.f, 480.f);
    fn_80235178(0, 0, 0, 640, 480);
    sync();
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

void GSrender::fn_8023177C(GSdvdError error, u32 param2, GScolor color) {
    mDvdError = error;
    _1704 = param2;
    mFillColor.r = color.r;
    mFillColor.g = color.g;
    mFillColor.b = color.b;
    mFillColor.a = color.a;

    if (error == DVD_ERROR_OK) {
        if (_1714 != NULL) {
            _1714->fn_8023E2D0();
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
            case DVD_ERROR_WRONG_DISK: src = fn_80007940(); break;

            case DVD_ERROR_RETRY:      src = fn_800079C0(); break;

            case DVD_ERROR_FATAL:      src = fn_80007A40(); break;

            default:                   return;
        }

        u32 size = CXGetUncompressedSize(src);

        _1710 = GSmem::allocFromHeapAligned(gUnkHeap1, size, 0x20);
        _170c = gUnkHeap1;

        if (!_1710) {
            _1710 = GSmem::allocFromHeapAligned(gUnkHeap2, size, 0x20);
            _170c = gUnkHeap2;
        }

        if (_1710) {
            CXUncompressLZ(src, _1710);
            DCFlushRange(_1710, size);
            _1714 = fn_8023D6CC(_1710);
        }
    }

    if (error == DVD_ERROR_FATAL) {
        fn_802321DC();
    }
}

void GSrender::fn_80231918() {
    GSrenderState *state;

    if (mDvdError == DVD_ERROR_OK) {
        return;
    }

    if (mDvdError == DVD_ERROR_COVER_OPEN) {
        return;
    }

    fn_80235204(0, 0.f, 0.f, 640.f, 480.f);
    fn_80235178(0, 0, 0, 640, 480);
    fn_80234FE0(0.f, 0.f, 640.f, 480.f, 0.f, 100000.f);

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
        } else {
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

        configureColorChannel(0, (1 << 0) | (1 << 1), GX_SRC_VTX, GX_SRC_VTX, 0, NULL, GX_AF_NONE, GX_DF_NONE);

        if (mState->mCurr.mIndTexStages[0].mType != GS_TEV_NULL) {
            mState->mCurr.mIndTexStages[0].mType = GS_TEV_DIRECT;
        }
        mState->mIndTexStageFlags |= (1 << 0);
        mState->_0 |= (1 << 3);

        state = mState;
        state->mCurr.mTevStages[0].mTexCoord = GX_TEXCOORD_NULL;
        state->mCurr.mTevStages[0].mTexMap = GX_TEXMAP_NULL;
        state->mCurr.mTevStages[0].mChannel = GX_COLOR0A0;
        mState->mTevStageFlags |= (1 << 0);
        mState->_0 |= (1 << 3);

        configureTevStage(0, GS_TEV_MODE_PASSCLR);

        state = mState;
        state->mCurr.mTevSwapModes[0].mRasSel = GX_TEV_SWAP0;
        state->mCurr.mTevSwapModes[0].mTexSel = GX_TEV_SWAP0;
        mState->mTevSwapModeFlags |= (1 << 0);
        mState->_0 |= (1 << 5);

        mVertexFormat = fn_8023CF1C(2);
        mPrimitiveType = GX_TRIANGLESTRIP;

        fn_8023352C(4);
        // vert 1
        GXPosition2f32(0.f, 0.f);
        GXColor1u32(mFillColor);
        // vert 2
        GXPosition2f32(0.f, 480.f);
        GXColor1u32(mFillColor);
        // vert 3
        GXPosition2f32(640.f, 0.f);
        GXColor1u32(mFillColor);
        // vert 4
        GXPosition2f32(640.f, 480.f);
        GXColor1u32(mFillColor);
        fn_80233580();
        fn_80250134(_1704, 100, 200, 0, 0, -1);
    } else if (_1714) {
        u16 w = _1714->getWidth();
        f32 width;
        OSu16tof32(&w, &width);
        f32 centerX = 0.5f * width;

        u16 h = _1714->getHeight();
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

        mVertexFormat = fn_8023CF1C(2);
        mPrimitiveType = GX_TRIANGLESTRIP;

        fn_8023352C(4);
        // vert 1
        GXPosition2f32(0.f, 0.f);
        GXColor1u32(0);
        // vert 2
        GXPosition2f32(0.f, 480.f);
        GXColor1u32(0);
        // vert 3
        GXPosition2f32(640.f, 0.f);
        GXColor1u32(0);
        // vert 4
        GXPosition2f32(640.f, 480.f);
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

        configureTexCoordGen(0, GX_TG_MTX2x4, GX_TG_TEX0, NULL, GX_FALSE, NULL);

        if (mState->mTextures[0] != _1714 || (_1714->mFlags & (1 << 0)) == (1 << 0)) {
            mState->mTextures[0] = _1714;
            mState->mTextureFlags |= (1 << 0);
        }

        if (mState->mCurr.mIndTexStages[0].mType != GS_TEV_NULL) {
            mState->mCurr.mIndTexStages[0].mType = GS_TEV_DIRECT;
        }
        mState->mIndTexStageFlags |= (1 << 0);
        mState->_0 |= (1 << 3);

        state = mState;
        state->mCurr.mTevStages[0].mTexCoord = GX_TEXCOORD0;
        state->mCurr.mTevStages[0].mTexMap = GX_TEXMAP0;
        state->mCurr.mTevStages[0].mChannel = GX_COLOR_NULL;
        mState->mTevStageFlags |= (1 << 0);
        mState->_0 |= (1 << 3);

        configureTevStage(0, GS_TEV_MODE_REPLACE);

        state = mState;
        state->mCurr.mTevSwapModes[0].mRasSel = GX_TEV_SWAP0;
        state->mCurr.mTevSwapModes[0].mTexSel = GX_TEV_SWAP0;
        mState->mTevSwapModeFlags |= (1 << 0);
        mState->_0 |= (1 << 5);

        mVertexFormat = fn_8023CF1C(5);
        mPrimitiveType = GX_TRIANGLESTRIP;

        fn_8023352C(4);
        // vert 1
        GXPosition2f32(320.f - centerX, 240.f - centerY);
        GXTexCoord2f32(0.f, 0.f);
        // vert 2
        GXPosition2f32(320.f - centerX, 240.f + centerY);
        GXTexCoord2f32(0.f, 1.f);
        // vert 3
        GXPosition2f32(320.f + centerX, 240.f - centerY);
        GXTexCoord2f32(1.f, 0.f);
        // vert 4
        GXPosition2f32(320.f + centerX, 240.f + centerY);
        GXTexCoord2f32(1.f, 1.f);
        fn_80233580();
    }
}

void GSrender::fn_802321DC() {
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

    sync();
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
