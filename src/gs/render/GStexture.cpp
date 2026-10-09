#include "gs/render/GStexture.hpp"

#include "gs/GSmem.hpp"
#include "gs/GSrender.hpp"

#include "common.hpp"

static u32 sTexturePoolCount;
static GStexture *sTexturePool;

static s32 getGXTextureFormat(u32 format, bool isDirect) {
    switch (format) {
        case GS_TF_C4:     return GX_TF_C4;
        case GS_TF_C8:     return GX_TF_C8;
        case GS_TF_C14X2:  return GX_TF_C14X2;
        case GS_TF_I4:     return GX_TF_I4;
        case GS_TF_IA4:    return GX_TF_IA4;
        case GS_TF_I8:     return GX_TF_I8;
        case GS_TF_IA8:    return GX_TF_IA8;
        case GS_TF_RGB565: return GX_TF_RGB565;
        case GS_TF_RGBA8:  return GX_TF_RGBA8;
        case GS_TF_RG5A3:  return GX_TF_RGB5A3;
        case GS_TF_CMPR:   return GX_TF_CMPR;
        case GS_CTF_R4:    return isDirect ? GX_TF_I4 : GX_CTF_R4;
        case GS_CTF_A8:    return isDirect ? GX_TF_I8 : GX_CTF_A8;
        case GS_CTF_R8:    return isDirect ? GX_TF_I8 : GX_CTF_R8;
        case GS_CTF_G8:    return isDirect ? GX_TF_I8 : GX_CTF_G8;
        case GS_CTF_B8:    return isDirect ? GX_TF_I8 : GX_CTF_B8;
        case GS_CTF_Z8:    return isDirect ? GX_TF_I8 : GX_TF_Z8;
        case GS_CTF_Z8M:   return isDirect ? GX_TF_I8 : GX_CTF_Z8M;
        case GS_CTF_Z16:   return isDirect ? GX_TF_IA8 : GX_TF_Z16;
        case GS_CTF_Z24X8: return isDirect ? GX_TF_RGBA8 : GX_TF_Z24X8;
        default:           return -1;
    }
}

void GStexture::initTexturePool(u32 count) {
    sTexturePoolCount = count;
    sTexturePool = (GStexture *)GSmem::alloc(count * sizeof(*sTexturePool));

    if (sTexturePool) {
        for (u32 i = 0; i < sTexturePoolCount; i++) {
            sTexturePool[i]._6 = false;
        }
    }
}

void GStexture::fn_8023E2D0() {
    if (_6) {
        _6 = false;

        if (_24) {
            if (_50) {
                GSrender::sInstance->fn_8023B88C(_50);
                _50 = NULL;
            }

            if ((mFlags & (1 << 1))) {
                GSmem::freeToHeap(gUnkHeap2, _24);
            } else {
                GSmem::freeToHeap(gUnkHeap1, _24);
            }
            _24 = NULL;
            mFlags = 0;
        }
    }
}

void *GStexture::getMipmap(u8 index) const {
    if (index >= GS_TEX_MAX_MIPMAPS) {
        return NULL;
    }
    return mMipmaps[index];
}

void GStexture::flush() {
    DCStoreRange(*mMipmaps, mDataSize);
    GSrender::sInstance->setFlag((1 << 1));
}

void *GStexture::getTlut() const {
    return mTlutData;
}

void GStexture::flushTlut() {
    DCStoreRange(*mMipmaps, mDataSize);
    GSrender::sInstance->setFlag((1 << 1));
}

u16 GStexture::getWidth() const {
    return mWidth;
}

u16 GStexture::getHeight() const {
    return mHeight;
}

u8 GStexture::getMipmapLevels() const {
    return mMipmapCount - 1;
}

bool GStexture::isCompatibleFormat(GStextureFormat format) const {
    if (mTextureFormat == format) {
        return true;
    }

    switch (mTextureFormat) {
        case GS_TF_C4:
        case GS_TF_C8:
        case GS_TF_C14X2:
        case GS_TF_CMPR:  return false;
        default:          break;
    }

    switch (format) {
        case GS_TF_C4:
        case GS_TF_C8:
        case GS_TF_C14X2:
        case GS_TF_CMPR:   return false;
        case GS_TF_I4:
        case GS_CTF_R4:    return mBitsPerPixel == 4;
        case GS_TF_IA4:
        case GS_TF_I8:
        case GS_CTF_A8:
        case GS_CTF_R8:
        case GS_CTF_G8:
        case GS_CTF_B8:
        case GS_CTF_Z8:
        case GS_CTF_Z8M:   return mBitsPerPixel == 8;
        case GS_TF_IA8:
        case GS_TF_RGB565:
        case GS_TF_RG5A3:
        case GS_CTF_Z16:   return mBitsPerPixel == 16;
        case GS_TF_RGBA8:
        case GS_CTF_Z24X8: return mBitsPerPixel == 32;
        default:           return false;
    }
}

bool GStexture::setTextureFormat(GStextureFormat format) {
    if (!isCompatibleFormat(format)) {
        return false;
    }
    mTextureFormat = format;
    return true;
}

GStextureFormat GStexture::getTextureFormat() const {
    return mTextureFormat;
}

GStextureFormat GStexture::getPaletteFormat() const {
    return mPaletteFormat;
}

s32 GStexture::getGXTextureFormat(bool isDirect) const {
    return ::getGXTextureFormat(mTextureFormat, isDirect);
}
