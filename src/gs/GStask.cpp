#include <version.hpp>
#include <string.h>

#include <revolution/os.h>
#include <revolution/vi.h>

#include "gs/GSmem.hpp"
#include "gs/GStask.hpp"
#include "gs/GSvideo.hpp"

#define STACK_SIZE 0x2000

// TODO name remaining unnamed labels
/* lbl_8063F5D0 */ static TaskNode *taskPool;
static u32 lbl_8063F5D4;
static u32 lbl_8063F5D8;
static u32 lbl_8063F5DC;
static bool lbl_8063F5E0;
/* lbl_8063F5E4 */ static u8 *stack;
/* lbl_8063F5E8 */ static TaskNode *active;
/* lbl_8063F5EC */ static TaskNode *head;
static TaskNode *lbl_8063F5F0;
static VIRetraceCallback lbl_8063F5F4;

static inline u32 getTaskID(TaskNode *task) {
    return ((u32)task - (u32)taskPool) / sizeof(TaskNode) + 1;
}

void GStask::runTasksOfType(TaskType type) {
    TaskNode *task = head;
    while (task) {
        TaskNode *next = task->next;
        if (task->type == type && !task->disabled && (!lbl_8063F5E0 || !task->_C)) {
            active = task;
            task->run(getTaskID(task), task->userParam);
        }
        task = next;
    }
    active = NULL;
}

// TODO name this function
void GStask::fn_80223D0C(u32 param1) {
    runTasksOfType(TASK_TYPE_3);

    if (lbl_8063F5F4 != NULL) {
        lbl_8063F5F4(param1);
    }
}

void GStask::idleCallback(void *param) {
    #pragma unused(param)

    TaskNode *node, *next;

    while (true) {
        runTasksOfType(TASK_TYPE_2);
    
        BOOL intEnabled = OSDisableInterrupts();

        node = lbl_8063F5F0;
        while (node) {
            next = node->next;
            fn_80223E00(node);
            node = next;
        }
        lbl_8063F5F0 = NULL;
    
        OSRestoreInterrupts(intEnabled);
    }
}

TaskNode *GStask::getFreeTaskNode(TaskType type) {
    TaskNode *node;
    int count;
    
    if (type == TASK_TYPE_2) {
        node = taskPool + lbl_8063F5D4;
        count = lbl_8063F5D8;
    }
    else {
        node = taskPool;
        count = lbl_8063F5D4;
    }

    for (int i = 0; i != count; i++, node++) {
        if (node->type == TASK_TYPE_NULL) {
            return node;
        }
    }

    return NULL;
}

// TODO name this function
void GStask::fn_80223E00(TaskNode *newNode) {
    TaskNode *node = head;
    while (node->next && node->priority < newNode->priority) {
        node = node->next;
    }

    if (!node->next && node->priority < newNode->priority) {
        newNode->prev = node;
        newNode->next = NULL;
        node->next = newNode;
        return;
    }

    if (node->prev != NULL) {
        node->prev->next = newNode;
    }

    newNode->prev = node->prev;
    newNode->next = node;
    node->prev = newNode;

    if (head == node) {
        head = newNode;
    }
}

// TODO name this function
void GStask::fn_80223E88(TaskNode *newNode) {
    newNode->next = lbl_8063F5F0;
    lbl_8063F5F0 = newNode;
}

void GStask::insertTaskNode(TaskNode *newNode) {
    if (head == NULL) {
        head = newNode;
        return;
    }

    BOOL intEnabled = OSDisableInterrupts();
    if (newNode->type == TASK_TYPE_2) {
        fn_80223E88(newNode);
    }
    else {
        fn_80223E00(newNode);
    }
    OSRestoreInterrupts(intEnabled);
}

void GStask::init(int param1, int param2) {
    lbl_8063F5D4 = param1;
    lbl_8063F5D8 = param2;
    lbl_8063F5DC = param1 + param2;
    active = NULL;
    taskPool = (TaskNode *)GSmem::allocFromDefaultHeap(lbl_8063F5DC * sizeof(TaskNode));
    
    if (taskPool == NULL) {
        return;
    }
    
    for (int i = 0; i < lbl_8063F5DC; i++) {
        taskPool[i].type = TASK_TYPE_NULL;
    }

    stack = (u8 *)GSmem::allocFromDefaultHeap(STACK_SIZE);
    OSSetIdleFunction(idleCallback, NULL, stack + STACK_SIZE - 4, STACK_SIZE - 4);

    if (GSvideo::sInstance) {
        VIRetraceCallback temp = GSvideo::sInstance->mRetraceCallback;
        GSvideo::sInstance->mRetraceCallback = fn_80223D0C;
        lbl_8063F5F4 = temp;
    }
}

u32 GStask::createTask(TaskType type, u8 priority, u32 userParam, TaskCallback callback) {
    TaskNode *node = getFreeTaskNode(type);

    if (node == NULL) {
        return 0;
    }

    node->prev = NULL;
    node->next = NULL;
    node->type = type;
    node->priority = priority;
    node->disabled = false;
    node->userParam = userParam;
    node->run = callback;
    node->_C = 0;
    node->name[0] = '\0';

    insertTaskNode(node);

    return getTaskID(node);
}

// TODO name this function
void GStask::fn_8022406C() {
    runTasksOfType(TASK_TYPE_1);
}

// TODO name this function
TaskNode *GStask::fn_80224074(u32 param) {
    #pragma unused(param)

    TaskNode *node = head;
    while (node) {
        node = node->next;
    }
    return node;
}

void GStask::setTaskName(u32 taskID, char *name) {
    TaskNode *node;
    
    if (name != NULL && taskID != 0) {
        node = &taskPool[taskID - 1];
        memcpy(node->name, name, sizeof(node->name) - 1);
        node->name[sizeof(node->name) - 1] = '\0';
    }
}
