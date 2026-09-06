#pragma once

#include <revolution/types.h>

struct GSlistNode {
    // TODO(samm) Something better?
    /* 0x0 */ union {
        GSlistNode *mNextFree;
        void *mData;
    };
    /* 0x4 */ GSlistNode *mNext;
    /* 0x8 */ GSlistNode *_8;
};

class GSlinkedList {
public:
    static void init(u32 param1);
    static GSlistNode *allocNode();
    static void freeNode(GSlistNode *node);
};
