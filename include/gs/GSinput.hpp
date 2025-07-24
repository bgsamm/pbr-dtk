#pragma once

#include <revolution/types.h>
#include <revolution/kpad.h>
#include <revolution/wpad.h>

#define DEV_TYPE_INVALID 0x00
#define DEV_TYPE_20      0x20
#define DEV_TYPE_30      0x30
#define DEV_TYPE_WIIMOTE 0x40
#define DEV_TYPE_NUNCHUK 0x50
#define DEV_TYPE_CLASSIC 0x60

typedef void (*GSinputUnkFunc1)(s32, u32);

// size: 0x20
struct GSinputUnkStruct2 {
    /* 0x0 */ u32 _0;
    /* 0x4 */ bool _4;
    /* 0x8 */ u32 _8;
    /* 0xc */ u32 _C;
    /* 0x10 */ u32 _10;
    /* 0x14 */ f32 _14;
    /* 0x18 */ f32 _18;
    /* 0x1c */ f32 _1c;
};

// size: 0x1c
struct GSinputUnkStruct3 {
    /* 0x0 */ u32 mState;
    /* 0x4 */ f32 _4;
    /* 0x8 */ u32 _8;
    /* 0xc */ u32 _C;
    /* 0x10 */ u32 _10;
    /* 0x14 */ f32 _14;
    /* 0x18 */ f32 _18;
};

// size: 0x24
struct GScontrolStick {
    /* 0x0 */ u8 mNumSteps;
    /* 0x4 */ s32 _4;
    /* 0x8 */ u8 _8;
    /* 0xc */ Vec2 mPosDelta;
    /* 0x14 */ Vec2 mTargetPos;
    /* 0x1c */ Vec2 mCurrentPos;
};

struct UnkStruct8 {
    /* 0x0 */ u8 _0;
    /* 0x1 */ u8 _1;
    /* 0x2 */ u8 _2;
};

// size: 0x10
struct GSinputUnkStruct5 {
    /* 0x0 */ f32 _0;
    /* 0x4 */ u8 _4;
    /* 0x5 */ bool _5;
    /* 0x8 */ UnkStruct8 *_8;
    /* 0xC */ UnkStruct8 *_C;
};

struct GSdeviceInfo {
    /* 0x0 */ u32 mDeviceType;
    /* 0x4 */ u32 mChannel;
    /* 0x8 */ bool _8;
};

struct GSinputUnkStruct7 {
    /* 0x0 */ u32 _0;
    /* 0x4 */ GSinputUnkFunc1 _4;
    /* 0x8 */ GSinputUnkFunc1 _8;
    /* 0xc */ GSinputUnkFunc1 _C;
    /* 0x10 */ bool _10;
    /* 0x11 */ bool _11;
    /* 0x12 */ bool _12;
};

// size: 0x928
struct GSinputDevice {
    /* 0x0 */ bool mEnabled;
    /* 0x4 */ s32 mChannel;
    /* 0x8 */ u32 mDeviceType;
    /* 0xc */ Vec2 mStick1PosRaw;
    /* 0x14 */ Vec2 mStick2PosRaw;
    /* 0x1c */ u32 mButtonsDown;
    /* 0x20 */ u32 mButtons;
    /* 0x24 */ u32 mButtonsLast;
    /* 0x28 */ f32 _28;
    /* 0x2c */ f32 _2c;
    /* 0x30 */ f32 _30;
    /* 0x34 */ f32 _34;
    /* 0x38 */ u32 mWpadType;
    /* 0x3c */ s32 mLastError;
    /* 0x40 */ s32 mDataSetsRead;
    /* 0x44 */ KPADStatus mSamplingBufs[16];
    /* 0x884 */ GSinputUnkStruct2 _884;
    /* 0x8a4 */ GSinputUnkStruct3 _8a4;
    /* 0x8c0 */ GScontrolStick mStick1;
    /* 0x8e4 */ GScontrolStick mStick2;
    /* 0x908 */ Vec2 mStick1Pos;
    /* 0x910 */ Vec2 mStick2Pos;
    /* 0x918 */ GSinputUnkStruct5 _918;

    void resetData();
    void read();
    void updateWiimote(s32 channel, bool param3);
    void updateNunchuk(s32 channel, bool param3);
    void fn_80243FAC(f32 param2);
    void fn_80244010(GSinputUnkStruct7 **param2, f32 param3);
    f32 fn_80244168(s32 param2);
    void enable();
    void disable();
};

class GSinputUnkClass1 {
public:
    virtual void func1(s32 chan);
    virtual void func2(s32 chan);
};

// size: 0x2540
class GSinputManager {
public:
    /* 0x0 */ u8 _0;
    /* 0x4 */ s32 mMaxDevices;
    /* 0x8 */ GSdeviceInfo mDeviceInfo[WPAD_MAX_CONTROLLERS];
    /* 0x38 */ GSinputDevice mDevices[WPAD_MAX_CONTROLLERS];
    /* 0x24d8 */ u8 _24d8[16];
    /* 0x24e8 */ u8 _24e8[16];
    u8 unk1[0x30];
    /* 0x2528 */ u32 mDeviceTypes[WPAD_MAX_CONTROLLERS];
    /* 0x2538 */ GSinputUnkClass1 *_2538;
    /* 0x253c */ GSinputUnkStruct7 **_253c;
    
    GSinputManager(s32 maxDevices);

    void fn_80244390(f32 param1);
    void onDataReceived(s32 channel);
    void probeDeviceTypes();
    void enableAllChannels();
    void disableAllChannels();

    static GSinputManager *sInstance;
};

namespace GSinput {
    void fn_802437EC(GSinputUnkStruct2 *param1);
    void fn_80243820(GSinputUnkStruct2 *param1, u32 buttons, u32 buttonsDown, f32 param4);
    void fn_80243890(GSinputUnkStruct3 *param1);
    void fn_802438AC(GSinputUnkStruct3 *param1, u32 buttons, u32 buttonsDown, f32 param4);
    GScontrolStick *fn_80243A18(GScontrolStick *param1);
    void fn_80243A48(GScontrolStick *param1);
    void fn_80243A7C(GScontrolStick *param1, Vec2 *param2);

    GSinputManager *getInputManager();
    GSinputDevice *getDevice(s32 channel);
    s32 getMaxDevices();
    void samplingCallback(s32 chan);
    void *wpadAlloc(u32 size);
    u8 wpadFree(void *ptr);
    void init(s32 maxDevices);
    void fn_802448BC();

    // 802448E8
    void fn_802448E8(GSinputUnkStruct5 *param1);
    void fn_80244904(GSinputUnkStruct5 *param1, f32 param2);
};
