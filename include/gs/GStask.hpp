#pragma once

#include <revolution/types.h>

typedef void (*TaskCallback)(u32, u32);

// TODO rename remaining enum values
enum TaskType {
    TASK_TYPE_NULL,
    TASK_TYPE_1,
    TASK_TYPE_2,
    TASK_TYPE_3
};

struct TaskNode {
    /* 0x0 */ TaskNode *prev;
    /* 0x4 */ TaskNode *next;
    /* 0x8 */ TaskType type;
    // TODO name this field
    /* 0xC */ u32 _C;
    /* 0x10 */ u8 priority;
    /* 0x11 */ bool disabled;
    u8 pad[2];
    /* 0x14 */ char name[0x20];
    /* 0x34 */ u32 userParam;
    /* 0x38 */ TaskCallback run;
};

class GStask {
public:
    static void runTasksOfType(TaskType type) NO_INLINE;
    static void fn_80223D0C(u32 param1);
    static void idleCallback(void *);
    static TaskNode *getFreeTaskNode(TaskType type) NO_INLINE;
    static void fn_80223E00(TaskNode *newNode);
    static void fn_80223E88(TaskNode *newNode) NO_INLINE;
    static void insertTaskNode(TaskNode *newNode) NO_INLINE;
    static void init(int param1, int param2);
    static u32 createTask(TaskType type, u8 priority, u32 userParam, TaskCallback callback);
    static void fn_8022406C();
    static TaskNode *fn_80224074(u32 param);
    static void setTaskName(u32 taskIndex, char *name);
};
