#pragma once

#include <revolution/types.h>

typedef void (*GStimelineCallback)(u32, u32, u32, u32);

struct GStimelineNode {
    u8 unk1[0x4];
    /* 0x4 */ f32 mTimer;
    /* 0x8 */ GStimelineNode *mNext;
    /* 0xC */ u32 _C;
    /* 0x10 */ u32 _10;
    /* 0x14 */ u32 _14;
    /* 0x18 */ u32 _18;
    /* 0x1c */ GStimelineCallback mCallback;
};

// size: 0xc
class GStimelineManager {
public:
    /* 0x0 */ u32 _0;
    /* 0x4 */ GStimelineNode *mNodes;
    u8 unk1[0x4];

    GStimelineManager(u32 param1);
    ~GStimelineManager();

    void update(f32 dt);

    static GStimelineManager *sInstance; 
};

namespace GStimeline {
    void timelineTaskCallback(u32 taskId, void *userParam);
    void init(u32 param1);
    bool fn_802248E8(GStimelineNode *node, f32 dt);
    void fn_8022490C(GStimelineNode *node);
}
