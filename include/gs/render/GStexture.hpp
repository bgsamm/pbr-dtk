#pragma once

#include <revolution.h>

#define GS_TEXTURE_MAX_MIPMAPS 8

struct GStexture {
    /* 0x00 */ u16 mWidth;
    /* 0x02 */ u16 mHeight;
    /* 0x04 */ u8 mBitsPerPixel;
    /* 0x05 */ u8 mMipmapCount;
    /* 0x06 */ u8 _pad_06[1];
    /* 0x07 */ u8 mFlags;
    /* 0x08 */ u32 mImageFormat;
    /* 0x0c */ u32 mPaletteFormat;
    /* 0x10 */ u32 mWrapS;
    /* 0x14 */ u32 mWrapT;
    /* 0x18 */ GXTexFilter mMinFilter;
    /* 0x1c */ GXTexFilter mMagFilter;
    /* 0x20 */ u32 mFilterFlags;
    /* 0x24 */ u32 _24;
    /* 0x28 */ void *mMipmaps[GS_TEXTURE_MAX_MIPMAPS];
    /* 0x48 */ void *mTlutData;
    /* 0x4c */ u32 mDataSize;
    /* 0x50 */ u32 _50;
    /* 0x54 */ GXTexObj mTexObj;
    /* 0x74 */ GXTlutObj mTlutObj;
};

GStexture *fn_8023D974(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5);
void fn_8023E3C8(GStexture *texture, GXTexFilter minFilter, GXTexFilter magFilter, u32 flags);
u8 *fn_8023E434(GStexture *texture, u32 arg1);
void fn_8023E4C0(GStexture *texture);
