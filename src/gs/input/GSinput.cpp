#include "global.hpp"

#include <cstring>
#include <revolution/kpad.h>
#include <revolution/wpad.h>

#include "gs/GSinput.hpp"
#include "gs/GSmem.hpp"

extern MEMHeapHandle lbl_8063E8EC;

/* lbl_8063F7B0 */ GSinputManager *GSinputManager::sInstance;

void GSinput::fn_802437EC(GSinputUnkStruct2 *param1) {
    param1->_0 = 0;
    param1->_4 = false;
    param1->_C = 0;
    param1->_8 = 0;
    param1->_18 = 0.6f;
    param1->_1c = 0.1f;
    param1->_10 = 0x32000;
}

// Tests for buttons held a minimum length of time?
void GSinput::fn_80243820(GSinputUnkStruct2 *param1, u32 buttons, u32 buttonsDown, f32 param4) {
    param1->_C = 0;

    // TODO #define these flags
    u32 var1 = buttons & ~((1 << 16) | (1 << 17));

    if (param1->_4) {
        if (var1 == 0) {
            param1->_4 = false;
        }
        else {
            param1->_14 -= param4;
            if (param1->_14 < 0f) {
                param1->_14 = param1->_1c;
                param1->_C = var1;
            }
        }
    }
    else if (var1 != 0) {
        param1->_4 = true;
        param1->_14 = param1->_18;
        param1->_C = var1;
    }
}

void GSinput::fn_80243890(GSinputUnkStruct3 *param1) {
    param1->mState = 0;
    param1->_14 = 0.25f;
    param1->_18 = 0.083333336f; // 1/12
}

// Detects double taps? Though I can't get it to reach state 3
void GSinput::fn_802438AC(GSinputUnkStruct3 *param1, u32 buttons, u32 buttonsDown, f32 param4) {
    if (param1->_8 != 0 && (buttons & buttonsDown) == 0) {
        param1->_8 = 0;
        param1->mState = 0;
    }

    switch (param1->mState) {
        case 0:
            if ((buttons & buttonsDown) != 0) {
                param1->_10 = (buttons & buttonsDown);
                param1->_4 = param1->_14;
                param1->mState = 1;
            }
            break;
        
        case 1:
            param1->_4 -= param4;
            if (param1->_4 <= 0f) {
                param1->mState = 0;
            }
            else if ((buttons & buttonsDown) == 0) {
                param1->mState = 2;
            }
            break;
        
        case 2:
            param1->_4 -= param4;
            if (param1->_4 <= 0f) {
                param1->mState = 0;
            }
            else if (param1->_10 == (buttons & buttonsDown)) {
                param1->mState = 3;
                param1->_4 = param1->_18;
                param1->_8 = param1->_10;
                param1->_C = param1->_10;
            }
            break;
        
        case 3:
            if (param1->_4 < (param1->_18 - 2f)) {
                param1->_C = 0;
            }

            if (param1->_10 != (buttons & buttonsDown)) {
                param1->mState = 0;
            }
            else {
                param1->_4 -= param4;
                if (param1->_4 == 0f) {
                    param1->_8 = param1->_10 | (buttons & ~buttonsDown);
                }
            }
            break;
        
        default:
            param1->mState = 0;
            break;
    }
}

GScontrolStick *GSinput::fn_80243A18(GScontrolStick *param1) {
    fn_80243A48(param1);
    return param1;
}

void GSinput::fn_80243A48(GScontrolStick *param1) {
    param1->_4 = 0;
    param1->_8 = 0;
    param1->mNumSteps = 7;
    param1->mPosDelta.x = 0f;
    param1->mPosDelta.y = 0f;
    param1->mTargetPos.x = 0f;
    param1->mTargetPos.y = 0f;
    param1->mCurrentPos.x = 0f;
    param1->mCurrentPos.y = 0f;
}

static inline void sub_vec2(Vec2 *a, Vec2 *b, Vec2 *out) {
    out->x = a->x - b->x;
    out->y = a->y - b->y;
}

// TODO fix reg swaps & instruction ordering (more inlining?)
void GSinput::fn_80243A7C(GScontrolStick *param1, Vec2 *targetPos) {
    // This variable never actually gets used
    Vec2 var1;
    sub_vec2(&param1->mTargetPos, targetPos, &var1);
    if (var1.x < 0f) {
        var1.x = -var1.x;
    }
    if (var1.y < 0f) {
        var1.y = -var1.y;
    }

    sub_vec2(targetPos, &param1->mCurrentPos, &param1->mPosDelta);

    if (param1->_4 == 0) {
        f32 nSteps = ensure_nonzero(param1->mNumSteps);
        param1->mPosDelta.x *= 1f / nSteps;
        param1->mPosDelta.y *= 1f / nSteps;
    }
    else if (param1->_4 == 1) {
        f32 nSteps = ensure_nonzero(param1->mNumSteps * 0.25f);
        param1->mPosDelta.x *= 1f / nSteps;
        param1->mPosDelta.y *= 1f / nSteps;
    }

    param1->_8 = 0;
    param1->mTargetPos.x = targetPos->x;
    param1->mTargetPos.y = targetPos->y;
    param1->mCurrentPos.x += param1->mPosDelta.x;
    param1->mCurrentPos.y += param1->mPosDelta.y;
    
    if (param1->_4 == 1 && (param1->_8 = 1) < param1->mNumSteps) {
        f32 nSteps = ensure_nonzero(2f);
        param1->mPosDelta.x *= 1f / nSteps;
        param1->mPosDelta.y *= 1f / nSteps;

        if (abs(param1->mPosDelta.x) < 1f) {
            param1->mPosDelta.x = (param1->mPosDelta.x > 0) ? 1 : -1;
        }

        if (abs(param1->mPosDelta.y) < 1f) {
            param1->mPosDelta.y = (param1->mPosDelta.y > 0) ? 1 : -1;
        }
    }

    if (param1->mPosDelta.x < 0f) {
        if (param1->mCurrentPos.x < param1->mTargetPos.x) {
            param1->mCurrentPos.x = param1->mTargetPos.x;
        }
    }
    else {
        if (param1->mCurrentPos.x > param1->mTargetPos.x) {
            param1->mCurrentPos.x = param1->mTargetPos.x;
        }
    }

    if (param1->mPosDelta.y < 0f) {
        if (param1->mCurrentPos.y < param1->mTargetPos.y) {
            param1->mCurrentPos.y = param1->mTargetPos.y;
        }
    }
    else {
        if (param1->mCurrentPos.y > param1->mTargetPos.y) {
            param1->mCurrentPos.y = param1->mTargetPos.y;
        }
    }
}

void GSinputDevice::resetData() {
    mButtons = 0;
    mStick1PosRaw.x = 0f;
    mStick1PosRaw.y = 0f;
    mStick2PosRaw.x = 0f;
    mStick2PosRaw.y = 0f;
    mButtonsLast = 0;
    mButtonsDown = 0;
    _28 = 0f;
    _2c = 0f;
    _30 = 0f;
    _34 = 0f;
    mDataSetsRead = 0;
    mLastError = WPAD_ERR_NO_CONTROLLER;
}

void GSinputDevice::read() {
    mLastError = WPADProbe(mChannel, &mWpadType);
    mDataSetsRead = KPADRead(mChannel, mSamplingBufs, 16);

    u8 dev_type;
    s8 wpad_err;
    switch (mLastError) {
        case WPAD_ERR_BUSY:
            dev_type = mSamplingBufs[0].dev_type;
            wpad_err = mSamplingBufs[0].wpad_err;
            memset(&mSamplingBufs[0], 0, sizeof(KPADStatus));
            mSamplingBufs[0].dev_type = dev_type;
            mSamplingBufs[0].wpad_err = wpad_err;
            break;
        
        // NOTE these cases required explicitly to match
        case WPAD_ERR_NONE:
        case WPAD_ERR_TRANSFER:
            break;
    }

    if (WPADIsDpdEnabled(mChannel)) {
        if (!mEnabled) {
            disable();
        }
    }
    else {
        if (mEnabled) {
            enable();
        }
    }
}

void GSinputDevice::updateWiimote(s32 channel, bool param3) {
    if (mDataSetsRead == 0
        || mSamplingBufs[0].wpad_err != WPAD_ERR_NONE
    ) {
        resetData();
    }
    else {
        mButtonsLast = mButtons;
        mButtons = mSamplingBufs[0].hold;
        // NOTE does not match using WPADButtonDown
        mButtonsDown = (mButtons ^ mButtonsLast) & mButtons;
    }
}

void GSinputDevice::updateNunchuk(s32 channel, bool param3) {
    // TODO keep this variable from getting inlined
    KPADEXStatus *exStatus = &mSamplingBufs[0].ex_status;

    if (mDataSetsRead == 0
        || mSamplingBufs[0].wpad_err != WPAD_ERR_NONE
    ) {
        resetData();
    }
    else {
        mStick1PosRaw.x = exStatus->fs.stick.x;
        mStick1PosRaw.y = exStatus->fs.stick.y;
        GSinput::fn_80243A7C(&mStick1, &mStick1PosRaw);
        mStick1Pos.x = mStick1.mCurrentPos.x;
        mStick1Pos.y = mStick1.mCurrentPos.y;
        
        mButtonsLast = mButtons;
        mButtons = mSamplingBufs[0].hold;
        // NOTE does not match using WPADButtonDown
        mButtonsDown = (mButtons ^ mButtonsLast) & mButtons;
    }
}

void GSinputDevice::fn_80243FAC(f32 param2) {
    GSinput::fn_80243820(&_884, mButtons, mButtonsDown, param2);
    GSinput::fn_802438AC(&_8a4, mButtons, mButtonsDown, param2);
    GSinput::fn_80244904(&_918, param2);
}


void GSinputDevice::fn_80244010(GSinputUnkStruct7 **param2, f32 param3) {
    u32 buttonsDown = mButtonsDown;
    u32 buttonsUp = mButtons & ~buttonsDown;
    u32 var5 = _884._C;

    GSinputUnkStruct7 *var1;
    while ((var1 = *param2++) != NULL) {
        u32 var2 = buttonsDown & var1->_0;
        u32 var3 = buttonsUp & var1->_0;
        u32 var4 = var5 & var1->_0;

        if (!var1->_10) {
            if (var2 != var1->_0) {
                var2 = 0;
            }

            if (var4 != var1->_0) {
                var4 = 0;
            }
            
            if (var3 != var1->_0) {
                var3 = 0;
            }
        }

        if (var2 != 0) {
            if (var1->_4 != NULL) {
                var1->_4(mChannel, var2);
            }

            if (var1->_12) {
                break;
            }

            if (var1->_11) {
                buttonsDown &= ~var2;
            }
        }

        if (var4 != 0) {
            if (var1->_C != NULL) {
                var1->_C(mChannel, var4);
            }

            if (var1->_12) {
                break;
            }

            if (var1->_11) {
                var5 &= ~var4;
            }
        }

        if (var3 != 0) {
            if (var1->_8 != NULL) {
                var1->_8(mChannel, var3);
            }

            if (var1->_12) {
                break;
            }

            if (var1->_11) {
                buttonsUp &= ~var3;
            }
        }
    }
}

f32 GSinputDevice::fn_80244168(s32 param2) {
    switch (param2) {
        case 1:
            return _2c;
        
        case 2:
            return _28;
        
        case 0x800:
            return _30;
        
        case 0x400:
            return _34;
        
        default:
            return 0f;
    }
}

void GSinputDevice::enable() {
    KPADEnableDPD(mChannel);
    mEnabled = true;
}

void GSinputDevice::disable() {
    KPADDisableDPD(mChannel);
    mEnabled = false;
}

GSinputManager::GSinputManager(s32 maxDevices) {
    GSinputDevice *device = &mDevices[0];
    do {
        GSinput::fn_802437EC(&device->_884);
        GSinput::fn_80243890(&device->_8a4);
        GSinput::fn_80243A18(&device->mStick1);
        GSinput::fn_80243A18(&device->mStick2);
        GSinput::fn_802448E8(&device->_918);
        device->mDeviceType = DEV_TYPE_INVALID;
        device->mStick1PosRaw.x = 0f;
        device->mStick1PosRaw.y = 0f;
        device->mStick2PosRaw.x = 0f;
        device->mStick2PosRaw.y = 0f;
        device->mButtons = 0;
        device->mButtonsLast = 0;
        device->mButtonsDown = 0;
        device->mStick1Pos.x = 0f;
        device->mStick1Pos.y = 0f;
        device->mStick2Pos.x = 0f;
        device->mStick2Pos.y = 0f;
        device->_28 = 0f;
        device->_2c = 0f;
        device->_30 = 0f;
        device->_34 = 0f;
        device->mDataSetsRead = 0;
        device++;
    } while (device < &mDevices[WPAD_MAX_CONTROLLERS]);

    _2538 = NULL;

    mMaxDevices = WPAD_MAX_CONTROLLERS;
    if (maxDevices < mMaxDevices) {
        mMaxDevices = maxDevices;
    }

    memset(&_24d8, 0, sizeof(_24d8));
    memset(&_24e8, 0, sizeof(_24e8));

    _253c = NULL;
    
    mDeviceInfo[0].mDeviceType = DEV_TYPE_INVALID;
    mDeviceInfo[0].mChannel = WPAD_CHAN0;
    mDevices[0].mChannel = WPAD_CHAN0;
    mDevices[0].mEnabled = true;

    mDeviceInfo[1].mDeviceType = DEV_TYPE_INVALID;
    mDeviceInfo[1].mChannel = WPAD_CHAN1;
    mDevices[1].mChannel = WPAD_CHAN1;
    mDevices[1].mEnabled = true;

    mDeviceInfo[2].mDeviceType = DEV_TYPE_INVALID;
    mDeviceInfo[2].mChannel = WPAD_CHAN2;
    mDevices[2].mChannel = WPAD_CHAN2;
    mDevices[2].mEnabled = true;

    mDeviceInfo[3].mDeviceType = DEV_TYPE_INVALID;
    mDeviceInfo[3].mChannel = WPAD_CHAN3;
    mDevices[3].mChannel = WPAD_CHAN3;
    mDevices[3].mEnabled = true;
}

void GSinputManager::fn_80244390(f32 param1) {
    probeDeviceTypes();

    GSinputDevice *device;
    GSdeviceInfo *deviceInfo;

    bool var3;
    bool homeButton;
    s32 lastErr;
    for (s32 chan = 0; chan < WPAD_MAX_CONTROLLERS; chan++) {
        device = &mDevices[chan];
        deviceInfo = &mDeviceInfo[chan];
        if (chan < mMaxDevices) {
            device->mDeviceType = mDeviceTypes[chan];
            device->read();

            switch(mDeviceTypes[chan]) {
                case DEV_TYPE_20:
                    device->resetData();
                    var3 = true;
                    break;
                
                case DEV_TYPE_30:
                    device->resetData();
                    var3 = true;
                    break;
                
                case DEV_TYPE_CLASSIC:
                    device->updateWiimote(chan, false);
                    var3 = true;
                    break;
                
                case DEV_TYPE_WIIMOTE:
                    device->updateWiimote(chan, false);
                    var3 = true;
                    break;
                
                case DEV_TYPE_NUNCHUK:
                    device->updateNunchuk(chan, false);
                    var3 = true;
                    break;
                
                default:
                    // TODO fix regswap here
                    lastErr = device->mLastError;
                    homeButton = device->mButtons & WPAD_BUTTON_HOME;
                    device->resetData();
                    if (lastErr == WPAD_ERR_BUSY) {
                        WPADStatus status = {};
                        WPADRead(chan, &status);

                        if ((status.button & WPAD_BUTTON_HOME)) {
                            device->mButtons |= WPAD_BUTTON_HOME;

                            if (!homeButton) {
                                device->mButtonsDown |= WPAD_BUTTON_HOME;
                            }
                        }
                    }
                    var3 = true;
                    break;
            }

            if (!var3) {
                if (!deviceInfo->_8 && _2538 != NULL) {
                    _2538->func2(chan);
                }

                device->resetData();
                deviceInfo->_8 = true;
            }
            else {
                if (deviceInfo->_8 && _2538 != NULL) {
                    _2538->func1(chan);
                }

                device->fn_80243FAC(param1);

                if (_253c != NULL) {
                    device->fn_80244010(_253c, param1);
                }

                if (device->_918._5) {
                    WPADControlMotor(chan, device->_918._4);
                }

                deviceInfo->_8 = false;
            }
        }
        else {
            u32 type;
            if (WPADProbe(chan, &type) == WPAD_ERR_NONE
                && type != WPAD_DEV_NOT_FOUND
            ) {
                WPADDisconnect(chan);
            }
        }
    }
}

void GSinputManager::onDataReceived(s32 channel) {

}

void GSinputManager::probeDeviceTypes() {
    _0 = 0;

    u32 type;
    for (s32 chan = 0; chan < WPAD_MAX_CONTROLLERS; chan++) {
        if (WPADProbe(chan, &type) != WPAD_ERR_NONE) {
            mDeviceTypes[chan] = DEV_TYPE_INVALID;
            continue;
        }

        switch (type) {
            case WPAD_DEV_CORE:
            case WPAD_DEV_FUTURE:
                mDeviceTypes[chan] = DEV_TYPE_WIIMOTE;
                break;
            
            case WPAD_DEV_FREESTYLE:
                mDeviceTypes[chan] = DEV_TYPE_NUNCHUK;
                break;
            
            case WPAD_DEV_CLASSIC:
                mDeviceTypes[chan] = DEV_TYPE_CLASSIC;
                break;
            
            case WPAD_DEV_NOT_SUPPORTED:
            case WPAD_DEV_NOT_FOUND:
            case WPAD_DEV_UNKNOWN:
            default:
                mDeviceTypes[chan] = DEV_TYPE_INVALID;
                break;
        }
    }
}

void GSinputManager::enableAllChannels() {
    for (s32 chan = 0; chan < WPAD_MAX_CONTROLLERS; chan++) {
        mDevices[chan].enable();
    }
}

void GSinputManager::disableAllChannels() {
    for (s32 chan = 0; chan < WPAD_MAX_CONTROLLERS; chan++) {
        mDevices[chan].disable();
    }
}

GSinputManager *GSinput::getInputManager() {
    return GSinputManager::sInstance;
}

GSinputDevice *GSinput::getDevice(s32 channel) {
    if (GSinputManager::sInstance != NULL
        && channel < GSinputManager::sInstance->mMaxDevices
    ) {
        return &GSinputManager::sInstance->mDevices[channel];
    }
    return NULL;
}

s32 GSinput::getMaxDevices() {
    if (GSinputManager::sInstance != NULL) {
        return GSinputManager::sInstance->mMaxDevices;
    }
    return 0;
}

void GSinput::samplingCallback(s32 chan) {
    if (GSinputManager::sInstance == NULL) {
        return;
    }
    GSinputManager::sInstance->onDataReceived(chan);
}

void *GSinput::wpadAlloc(u32 size) {
    return GSmem::allocFromHeap(lbl_8063E8EC, size);
}

u8 GSinput::wpadFree(void *ptr) {
    GSmem::freeToHeap(lbl_8063E8EC, ptr);
    // Should this be returning 1 for success?
    return 0;
}

void GSinput::init(s32 maxDevices) {
    GSinputManager::sInstance = new GSinputManager(maxDevices);

    WPADRegisterAllocator(wpadAlloc, wpadFree);
    KPADInit();
    WPADSetSamplingCallback(WPAD_CHAN0, samplingCallback);
    KPADSetFSStickClamp(18, 56);
}

// TODO name this function
void GSinput::fn_802448BC() {
    WPADSetSamplingCallback(WPAD_CHAN0, NULL);
}
