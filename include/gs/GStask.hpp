#pragma once

#include <revolution/types.h>

typedef void (*GStaskCallback)(u32, u32);

// TODO rename remaining enum values
enum GStaskType {
    TASK_TYPE_NULL      = 0,
    TASK_TYPE_MAIN      = 1,
    TASK_TYPE_IDLE      = 2,
    TASK_TYPE_RETRACE   = 3
};

struct GStaskHandle {
    /* 0x0 */ GStaskHandle *mPrev;
    /* 0x4 */ GStaskHandle *mNext;
    /* 0x8 */ GStaskType mType;
    // TODO name this field
    /* 0xC */ u32 _C;
    /* 0x10 */ u8 mPriority;
    /* 0x11 */ bool mDisabled;
    u8 pad[2];
    /* 0x14 */ char mName[0x20];
    /* 0x34 */ u32 mUserParam;
    /* 0x38 */ GStaskCallback mCallback;
};

class GStask {
public:
    static void runTasksOfType(GStaskType type);
    static void retraceCallback(u32 retraceCount);
    static void idleCallback(void *param);
    static GStaskHandle *getFreeTaskHandle(GStaskType type);
    static void insertTaskByPriority(GStaskHandle *taskHandle);
    static void pushIdleTask(GStaskHandle *taskHandle);
    static void enqueueTask(GStaskHandle *taskHandle);
    static void init(u32 activeCount, u32 idleCount);
    static u32 createTask(GStaskType type, u8 priority, u32 userParam, GStaskCallback callback);
    static void runMainTasks();
    static GStaskHandle *fn_80224074(u32 param1);
    static void setTaskName(u32 taskID, char *name);
};
