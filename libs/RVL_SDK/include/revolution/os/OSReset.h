#ifndef REVOLUTION_OS_RESET_H
#define REVOLUTION_OS_RESET_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef BOOL (*OSShutdownFunction)(BOOL, u32);

// From doldecomp/ogws (CC0), include/revolution/OS/OSReset.h
typedef enum {
    OS_SD_EVENT_FATAL,
    OS_SD_EVENT_1,
    OS_SD_EVENT_SHUTDOWN,
    OS_SD_EVENT_3,
    OS_SD_EVENT_RESTART,
    OS_SD_EVENT_RETURN_TO_MENU,
    OS_SD_EVENT_LAUNCH_APP,
} OSShutdownEvent;

typedef struct OSShutdownFunctionInfo OSShutdownFunctionInfo;
struct OSShutdownFunctionInfo {
    OSShutdownFunction func;  // 0x00

    u32 priority;  // 0x04

    OSShutdownFunctionInfo* next;  // 0x08
    OSShutdownFunctionInfo* prev;  // 0x0C
};

typedef struct OSShutdownFunctionQueue {
    OSShutdownFunctionInfo* head;  // 0x00
    OSShutdownFunctionInfo* tail;  // 0x04
} OSShutdownFunctionQueue;

void OSRegisterShutdownFunction(OSShutdownFunctionInfo* info);
void OSUnregisterShutdownFunction(OSShutdownFunctionInfo* info);

u32 OSGetResetCode(void);

void OSRebootSystem(void);
void OSReturnToMenu(void);
void OSShutdownSystem(void);

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu);

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_OS_RESET_H
