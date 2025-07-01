#ifndef OS_H
#define OS_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef s64 OSTime;

#ifdef __MWERKS__
u32 __OSBusClock : (0x8000 << 16 | 0x00F8);
#else
u32 __OSBusClock = 0x800000F8;
#endif

#define OS_BUS_CLOCK        __OSBusClock
#define OS_TIMER_CLOCK      (OS_BUS_CLOCK/4)

typedef struct OSThread OSThread;
typedef struct OSThreadQueue OSThreadQueue;
typedef struct OSSemaphore OSSemaphore;

struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
};

// size: 0xc
struct OSSemaphore {
    s32 count;
    OSThreadQueue queue;
};

typedef void (*OSIdleFunction)(void*);
typedef void (*OSResetCallback)(void);
typedef void (*OSPowerCallback)(void);

void* OSGetMEM1ArenaHi(void);
void* OSGetMEM2ArenaHi(void);
void* OSGetMEM1ArenaLo(void);
void* OSGetMEM2ArenaLo(void);
void OSSetMEM1ArenaLo(void* newLo);
void OSSetMEM2ArenaLo(void* newLo);
void DCInvalidateRange(void* startAddr, u32 nBytes);
void DCFlushRange(void* startAddr, u32 nBytes);

void OSInitSemaphore(OSSemaphore* sem, s32 count);
s32 OSWaitSemaphore(OSSemaphore* sem);
s32 OSSignalSemaphore(OSSemaphore* sem);

OSTime OSGetTime(void);

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL);

OSThread* OSSetIdleFunction(OSIdleFunction idleFunction, void* param, void* stack, u32 stackSize);
OSResetCallback OSSetResetCallback(OSResetCallback callback);
OSPowerCallback OSSetPowerCallback(OSPowerCallback callback);


#ifdef __cplusplus
}
#endif

#endif // OS_H
