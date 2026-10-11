#pragma once

#include <revolution.h>

#define GS_TEX_MAX_MIPMAPS 8

#define GX_TEX_COPY 0
#define GX_TEX_DIRECT 1

enum GStextureFormat {
    GS_TF_C4     = 0,
    GS_TF_C8     = 1,
    GS_TF_C14X2  = 0x30,
    GS_TF_I4     = 0x40,
    GS_TF_IA4    = 0x41,
    GS_TF_I8     = 0x42,
    GS_TF_IA8    = 0x43,
    GS_TF_RGB565 = 0x44,
    GS_TF_RGBA8  = 0x45,
    GS_TF_RG5A3  = 0x90,
    GS_TF_CMPR   = 0xB0,
    GS_CTF_R4    = 0xA8,
    GS_CTF_A8    = 0xA0,
    GS_CTF_R8    = 0xA1,
    GS_CTF_G8    = 0xA2,
    GS_CTF_B8    = 0xA3,
    GS_CTF_Z8    = 0xA4,
    GS_CTF_Z8M   = 0xA5,
    GS_CTF_Z16   = 0xA6,
    GS_CTF_Z24X8 = 0xA7
};

// Size: 0x80
class GStexture {
    // TODO(samm) Revisit this
    friend class GSrender;

public: // TODO(samm) Make private(?)
    /* 0x00 */ u16 mWidth;
    /* 0x02 */ u16 mHeight;
    /* 0x04 */ u8 mBitsPerPixel;
    /* 0x05 */ u8 mMipmapCount;
    /* 0x06 */ bool _6;
    /* 0x07 */ u8 mFlags;
    /* 0x08 */ GStextureFormat mTextureFormat;
    /* 0x0c */ GStextureFormat mPaletteFormat;
    /* 0x10 */ u32 mWrapS;
    /* 0x14 */ u32 mWrapT;
    /* 0x18 */ GXTexFilter mMinFilter;
    /* 0x1c */ GXTexFilter mMagFilter;
    /* 0x20 */ u32 mFilterFlags;
    /* 0x24 */ void *_24;
    /* 0x28 */ void *mMipmaps[GS_TEX_MAX_MIPMAPS];
    /* 0x48 */ void *mTlutData;
    /* 0x4c */ u32 mDataSize;
    /* 0x50 */ u32 _50;
    /* 0x54 */ GXTexObj mTexObj;
    /* 0x74 */ GXTlutObj mTlutObj;

private:
    bool isCompatibleFormat(GStextureFormat format) const;

public:
    void fn_8023E2D0();
    void *getMipmap(u8 index) const;
    void flush();
    void *getTlut() const;
    void flushTlut();
    u16 getWidth() const;
    u16 getHeight() const;
    u8 getMipmapLevels() const;
    bool setTextureFormat(GStextureFormat format);
    GStextureFormat getTextureFormat() const;
    GStextureFormat getPaletteFormat() const;
    s32 getGXTextureFormat(bool isDirect) const;

    static void initTexturePool(u32 count);
};

// TODO(samm) Move somewhere appropriate
GStexture *fn_8023D6CC(void *arg0);
GStexture *fn_8023D974(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5);
void fn_8023E3C8(GStexture *texture, GXTexFilter minFilter, GXTexFilter magFilter, u32 flags);
u8 *fn_8023E434(GStexture *texture, u32 arg1);
void fn_8023E6F0(GStexture *texture);
void fn_8023E88C(GStexture *texture);
