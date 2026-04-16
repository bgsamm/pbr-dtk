#include "revolution/os/OSReset.h"
#include "private/os/OSExec.h"
#include "private/os/OSPlayRecord.h"
#include "private/os/OSReset.h"
#include "private/os/OSRtc.h"
#include "private/os/OSStateFlags.h"
#include "private/os/OSStateTM.h"
#include "revolution/DVD.h"
#include "revolution/os/OSError.h"
#include "revolution/os/OSThread.h"
#include "revolution/sc.h"
#include <private/os.h>
#include <revolution/os.h>

#include <private/pad.h>

#include <private/dvd.h>
#include <private/vi.h>

#include <private/hollywood.h>

#include <string.h>

// TODO(samm) Replace with proper import
extern void fn_8026C328(void);

static OSShutdownFunctionQueue ShutdownFunctionQueue;

// TODO(samm) Give proper name
static u32 lbl_8063FAD8;

#define ENQUEUE_INFO(info, queue)                                                                                                                    \
    {                                                                                                                                                \
        OSShutdownFunctionInfo* __prev = (queue)->tail;                                                                                              \
        if (__prev == 0) {                                                                                                                           \
            (queue)->head = (info);                                                                                                                  \
        } else {                                                                                                                                     \
            __prev->next = (info);                                                                                                                   \
        }                                                                                                                                            \
        (info)->prev = __prev;                                                                                                                       \
        (info)->next = 0;                                                                                                                            \
        (queue)->tail = (info);                                                                                                                      \
    }

#define DEQUEUE_INFO(info, queue)                                                                                                                    \
    {                                                                                                                                                \
        OSShutdownFunctionInfo* __next = (info)->next;                                                                                               \
        OSShutdownFunctionInfo* __prev = (info)->prev;                                                                                               \
        if (__next == 0) {                                                                                                                           \
            (queue)->tail = __prev;                                                                                                                  \
        } else {                                                                                                                                     \
            __next->prev = __prev;                                                                                                                   \
        }                                                                                                                                            \
        if (__prev == 0) {                                                                                                                           \
            (queue)->head = __next;                                                                                                                  \
        } else {                                                                                                                                     \
            __prev->next = __next;                                                                                                                   \
        }                                                                                                                                            \
    }

#define ENQUEUE_INFO_PRIO(info, queue)                                                                                                               \
    {                                                                                                                                                \
        OSShutdownFunctionInfo* __prev;                                                                                                              \
        OSShutdownFunctionInfo* __next;                                                                                                              \
        for (__next = (queue)->head; __next && (__next->priority <= (info)->priority); __next = __next->next)                                        \
            ;                                                                                                                                        \
                                                                                                                                                     \
        if (__next == 0) {                                                                                                                           \
            ENQUEUE_INFO(info, queue);                                                                                                               \
        } else {                                                                                                                                     \
            (info)->next = __next;                                                                                                                   \
            __prev = __next->prev;                                                                                                                   \
            __next->prev = (info);                                                                                                                   \
            (info)->prev = __prev;                                                                                                                   \
            if (__prev == 0) {                                                                                                                       \
                (queue)->head = (info);                                                                                                              \
            } else {                                                                                                                                 \
                __prev->next = (info);                                                                                                               \
            }                                                                                                                                        \
        }                                                                                                                                            \
    }

enum {
    LAUNCH_ARG_MENU = 0,
    LAUNCH_ARG_SETTING,
};

static void KillThreads() {
    OSThread* thread;
    OSThread* next;

    for (thread = __OSActiveThreadQueue.head; thread; thread = next) {
        next = thread->linkActive.next;

        switch (thread->state) {
            case OS_THREAD_STATE_READY:
            case OS_THREAD_STATE_WAITING: {
                OSCancelThread(thread);
                break;
            }
            default: {
                break;
            }
        }
    }
}

void __OSReboot(u32 resetCode, u32 bootDol);

void OSRegisterShutdownFunction(OSShutdownFunctionInfo* info) {
    ENQUEUE_INFO_PRIO(info, &ShutdownFunctionQueue);
}

BOOL __OSCallShutdownFunctions(BOOL final, u32 event) {
    OSShutdownFunctionInfo* info;
    BOOL err;
    u32 priority = 0;

    err = FALSE;
    info = ShutdownFunctionQueue.head;
    while (info) {
        if (err && priority != info->priority) {
            break;
        }

        err |= !info->func(final, event);
        priority = info->priority;
        info = info->next;
    }
    err |= !__OSSyncSram();
    return err ? FALSE : TRUE;
}

void __OSShutdownDevices(u32 event) {
    BOOL rc, disableRecalibration, doRecal;

    switch (event) {
        case OS_SHUTDOWN_FATAL:
        case OS_SHUTDOWN_RESTART:
        case OS_SHUTDOWN_RETURN_MENU:
        case OS_SHUTDOWN_EXEC: {
            doRecal = FALSE;
            break;
        }
        case OS_SHUTDOWN_REBOOT:
        case OS_SHUTDOWN_SHUTDOWN:
        case OS_SHUTDOWN_IDLE:
        default: {
            doRecal = TRUE;
            break;
        }
    }

    __OSStopAudioSystem();

    if (!doRecal) {
        disableRecalibration = __PADDisableRecalibration(TRUE);
    }

    while (!__OSCallShutdownFunctions(FALSE, event)) {
    }
    while (!__OSSyncSram()) {
    }

    OSDisableInterrupts();
    rc = __OSCallShutdownFunctions(TRUE, event);
    LCDisable();

    if (!doRecal) {
        __PADDisableRecalibration(disableRecalibration);
    }

    KillThreads();
}

void OSRebootSystem() {
    OSStateFlags state;
    u32 rtcFlags;

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();
    __DVDPrepareReset();
    __OSReadStateFlags(&state);

    if (__DVDGetCoverStatus() != DVD_COVER_CLOSED) {
        state.discState = DVD_STATE_COVER_CLOSED;
    } else if (state.discState != DVD_STATE_BUSY || (__OSGetRTCFlags(&rtcFlags) && rtcFlags)) {
        state.discState = DVD_STATE_WAITING;
    } else {
        state.discState = DVD_STATE_BUSY;
    }

    state.shutdownType = OS_SHUTDOWN_SHUTDOWN;

    __OSClearRTCFlags();
    __OSWriteStateFlags(&state);
    OSDisableScheduler();
    __OSShutdownDevices(OS_SHUTDOWN_REBOOT);
    __OSHotReset();
}

void OSShutdownSystem() {
    SCIdleModeInfo idleInfo;
    OSStateFlags state;
    u32 rtcFlags;
    OSIOSRev iosRev;

    memset(&idleInfo, 0, sizeof(idleInfo));

    SCInit();
    while (SCCheckStatus() == SC_STATUS_BUSY)
        ;

    SCGetIdleMode(&idleInfo);

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();
    __DVDPrepareReset();
    __OSReadStateFlags(&state);

    if (__DVDGetCoverStatus() != DVD_COVER_CLOSED) {
        state.discState = DVD_STATE_COVER_CLOSED;
    } else if (state.discState != DVD_STATE_BUSY || (__OSGetRTCFlags(&rtcFlags) && rtcFlags)) {
        state.discState = DVD_STATE_WAITING;
    } else {
        state.discState = DVD_STATE_BUSY;
    }

    if (idleInfo.standby == TRUE) {
        state.shutdownType = OS_SHUTDOWN_RETURN_MENU;
    } else {
        state.shutdownType = OS_SHUTDOWN_REBOOT;
    }
    
    __OSClearRTCFlags();
    __OSWriteStateFlags(&state);
    __OSGetIOSRev(&iosRev);

    if (idleInfo.standby == TRUE) {
        OSDisableScheduler();
        __OSShutdownDevices(OS_SHUTDOWN_RETURN_MENU);
        OSEnableScheduler();
        __OSLaunchMenu();
    } else {
        OSDisableScheduler();
        __OSShutdownDevices(OS_SHUTDOWN_SHUTDOWN);
        __OSShutdownToSBY();
    }
}

// TODO(samm) Not actually sure this is the right name
void OSShutdownSystemForBS(u32 resetCode) {
    void *buf;
    OSNandbootInfo *nandInfo;
    OSStateFlags state;

    OSSetArenaLo(EXEC_WORK_ARENA_LO);
    OSSetArenaHi(EXEC_WORK_ARENA_HI);
    
    // TODO(samm) Determine signifance of size
    nandInfo = OSAllocFromMEM1ArenaLo(sizeof(OSNandbootInfo), 32);
    memset(buf, 0, sizeof(OSNandbootInfo));

    __OSReadNandbootInfo(nandInfo);
    nandInfo->returnValue = 1;
    nandInfo->argValue = resetCode | (1 << 31);
    __OSWriteNandbootInfo(nandInfo);

    if (__OSReadStateFlags(&state)) {
        state.shutdownType = OS_SHUTDOWN_IDLE;
        __OSWriteStateFlags(&state);
    }

    OSDisableScheduler();
    __OSShutdownDevices(OS_SHUTDOWN_RESTART);
    OSEnableScheduler();

    fn_8026C328();
}

void OSRestart(u32 resetCode) {
    u8 appType;

    appType = OSGetAppType();

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();

    if (appType == OS_APP_TYPE_CHANNEL) {
        OSShutdownSystemForBS(resetCode);
    } else if (appType == OS_APP_TYPE_DVD) {
        OSDisableScheduler();
        __OSShutdownDevices(OS_SHUTDOWN_RESTART);
        OSEnableScheduler();
        __OSReboot(resetCode, lbl_8063FAD8);
    }

    OSDisableScheduler();
    __OSShutdownDevices(OS_SHUTDOWN_REBOOT);
    __OSHotReset();
}

void OSReturnToMenu() {
    OSStateFlags state;
    u32 rtcFlags;

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();
    __DVDPrepareReset();
    __OSReadStateFlags(&state);

    if (__DVDGetCoverStatus() != DVD_COVER_CLOSED) {
        state.discState = DVD_STATE_COVER_CLOSED;
    } else if (state.discState != DVD_STATE_BUSY || (__OSGetRTCFlags(&rtcFlags) && rtcFlags)) {
        state.discState = DVD_STATE_WAITING;
    } else {
        state.discState = DVD_STATE_BUSY;
    }

    state.shutdownType = OS_SHUTDOWN_IDLE;
    
    __OSClearRTCFlags();
    __OSWriteStateFlags(&state);

    OSDisableScheduler();
    __OSShutdownDevices(OS_SHUTDOWN_RETURN_MENU);
    OSEnableScheduler();

    __OSLaunchMenu();

    OSDisableScheduler();
    __VISetRGBModeImm();
    __OSHotReset();
#line 843
    OSHalt("OSReturnToMenu(): Falied to boot system menu.\n");
}

void __OSReturnToMenuForError() {
    OSStateFlags state;

    __OSReadStateFlags(&state);
    state.discState = OS_STATE_FLAGS_DISC_CHANGED;
    state.shutdownType = OS_STATE_FLAGS_SHUTDOWN_RETURN_MENU;
    __OSClearRTCFlags();
    __OSWriteStateFlags(&state);

    __OSLaunchMenu();

    OSDisableScheduler();
    __VISetRGBModeImm();
    __OSHotReset();
#line 869
    OSHalt("__OSReturnToMenu(): Falied to boot system menu.\n");
}

u32 OSGetResetCode() {
    u32 code;
    if (__OSRebootParams.valid) {
        code = ((1 << 31) | __OSRebootParams.restartCode);
    } else {
        code = (PI_READ_REG(PI_RESET_REQUEST) & 0xFFFFFFF8) >> 3;
    }
    return code;
}

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu) {
#line 1020
    OSHalt("OSResetSystem() is obsoleted. It doesn't work any longer.\n");
}
