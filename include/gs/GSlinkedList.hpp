#pragma once

#include <revolution/types.h>

struct GSlistNode {
    // TODO(samm) Something better?
    /* 0x0 */ union {
        GSlistNode *mNextFree;
        void *mData;
    };
    // TODO(samm) Something better?
    /* 0x4 */ union {
        struct {
            GSlistNode *mNext;
        } sll;
        struct {
            GSlistNode *mPrev;
            GSlistNode *mNext;
        } dll;
    };
};

class GSlinkedList {
public:
    static void init(u32 param1);
    static GSlistNode *allocNode();
    static void freeNode(GSlistNode *node);
};
