#ifndef WPAD_H
#define WPAD_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WPAD_DPD_MAX_OBJECTS       4

#define WPAD_CHAN0                 0
#define WPAD_CHAN1                 1
#define WPAD_CHAN2                 2
#define WPAD_CHAN3                 3

#define WPAD_MAX_CONTROLLERS       4

#define WPAD_DEV_CORE              0
#define WPAD_DEV_FREESTYLE         1
#define WPAD_DEV_CLASSIC           2
#define WPAD_DEV_FUTURE          251
#define WPAD_DEV_NOT_SUPPORTED   252
#define WPAD_DEV_NOT_FOUND       253
#define WPAD_DEV_UNKNOWN         255

#define WPAD_BUTTON_LEFT            0x0001
#define WPAD_BUTTON_RIGHT           0x0002
#define WPAD_BUTTON_DOWN            0x0004
#define WPAD_BUTTON_UP              0x0008
#define WPAD_BUTTON_PLUS            0x0010
#define WPAD_BUTTON_2               0x0100
#define WPAD_BUTTON_1               0x0200
#define WPAD_BUTTON_B               0x0400
#define WPAD_BUTTON_A               0x0800
#define WPAD_BUTTON_MINUS           0x1000
#define WPAD_BUTTON_HOME            0x8000
// for FreeStyle
#define WPAD_BUTTON_Z               0x2000
#define WPAD_BUTTON_C               0x4000
// for ClassicStyle
#define WPAD_CL_BUTTON_UP           0x0001
#define WPAD_CL_BUTTON_LEFT         0x0002
#define WPAD_CL_TRIGGER_ZR          0x0004
#define WPAD_CL_BUTTON_X            0x0008
#define WPAD_CL_BUTTON_A            0x0010
#define WPAD_CL_BUTTON_Y            0x0020
#define WPAD_CL_BUTTON_B            0x0040
#define WPAD_CL_TRIGGER_ZL          0x0080
#define WPAD_CL_RESERVED            0x0100
#define WPAD_CL_TRIGGER_R           0x0200
#define WPAD_CL_BUTTON_PLUS         0x0400
#define WPAD_CL_BUTTON_HOME         0x0800
#define WPAD_CL_BUTTON_MINUS        0x1000
#define WPAD_CL_TRIGGER_L           0x2000
#define WPAD_CL_BUTTON_DOWN         0x4000
#define WPAD_CL_BUTTON_RIGHT        0x8000
// for compatibility
#define WPAD_BUTTON_SELECT          WPAD_BUTTON_MINUS
#define WPAD_BUTTON_START           WPAD_BUTTON_PLUS
#define WPAD_BUTTON_SMALL_B         WPAD_BUTTON_2
#define WPAD_BUTTON_SMALL_A         WPAD_BUTTON_1
#define WPAD_BUTTON_Z1              WPAD_BUTTON_Z
#define WPAD_BUTTON_Z2              WPAD_BUTTON_C

#define WPAD_MOTOR_STOP          0
#define WPAD_MOTOR_RUMBLE        1

#define WPAD_ERR_NONE              0
#define WPAD_ERR_NO_CONTROLLER    -1
#define WPAD_ERR_BUSY             -2
#define WPAD_ERR_TRANSFER         -3

typedef struct DPDObject {
    s16 x;
    s16 y;
    u16 size;
    u8  traceId;
} DPDObject;

typedef struct WPADStatus {
    u16       button;
    s16       accX;
    s16       accY;
    s16       accZ;
    DPDObject obj[WPAD_DPD_MAX_OBJECTS];
    u8        dev;
    s8        err;
} WPADStatus;

typedef void *(*WPADAlloc)(u32  size);
typedef u8    (*WPADFree )(void *ptr);

typedef void (*WPADSamplingCallback)(s32 chan);

#define WPADButtonDown(buttonLast, button) \
((u16) (((buttonLast) ^ (button)) & (button)))

#define WPADButtonUp(buttonLast, button) \
((u16) (((buttonLast) ^ (button)) & (buttonLast)))

void WPADRegisterAllocator(WPADAlloc alloc, WPADFree free);

void WPADDisconnect(s32 chan);
s32 WPADProbe(s32 chan, u32 *type);
WPADSamplingCallback WPADSetSamplingCallback(s32 chan, WPADSamplingCallback callback);

void WPADControlMotor(s32 chan, u32 command);

void WPADRead(s32 chan, void *status);

BOOL WPADIsDpdEnabled(s32 chan);

#ifdef __cplusplus
}
#endif

#endif // WPAD_H
