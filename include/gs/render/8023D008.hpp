#pragma once

#include <revolution/gx/GXEnum.h>
#include <revolution/types.h>

namespace gs {

struct GStextureData {
    /* 0x00 */ u16 mWidth;
    /* 0x02 */ u16 mHeight;
    /* 0x04 */ u8 _04;
    /* 0x05 */ u8 mNumLODs;
    /* 0x06 */ u8 _pad_06[1];
    /* 0x07 */ u8 _07;
    /* 0x08 */ u32 mImageFormat;
    /* 0x0c */ u32 mPaletteFormat;
    /* 0x10 */ u32 mWrapS;
    /* 0x14 */ u32 mWrapT;
    /* 0x18 */ GXTexFilter mMinFilter;
    /* 0x1c */ GXTexFilter mMagFilter;
    /* 0x20 */ u32 mFilterFlags;
    /* 0x24 */ u32 _24;
    /* 0x28 */ u32 mImageData;
    /* 0x2c */ u8 _pad_2c[28];
    /* 0x48 */ u32 mTlutData;
    /* 0x4c */ u32 mDataSize;
    /* 0x50 */ u32 _50;
};

GStextureData *fn_8023D6CC(GStextureData *textureData);
void fn_8023E3C8(GStextureData *textureData, GXTexFilter minFilter, GXTexFilter magFilter, u32 flags);

} // namespace gs
