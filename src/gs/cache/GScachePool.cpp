#include "version.hpp"

#include <cstring>

#include "gs/GScache.hpp"
#include "gs/GSmem.hpp"

/* lbl_80491470 */ static GScacheObjPool sObjectPools[32];

bool GScache::fn_801DBB3C() {
    return false;
}

void GScache::fn_801DBB44(bool param1) {

}

void GScache::initObjectPool(GScacheObjPool *pool, u32 count, u32 objSize) {
    objSize = (objSize + sizeof(GScacheObjNode) + 3) / 4 * 4;

    pool->mCount = count;
    pool->mNodeSize = objSize;

    GScacheObjNode *base = (GScacheObjNode *)GSmem::allocAndClear((count + 1) * objSize);
    pool->mStart = base;
    pool->mEnd = (GScacheObjNode *)((u8 *)base + count * objSize);
    pool->mFreeHead = base;

    u32 i;
    GScacheObjNode *node = base;
    GScacheObjNode *tail = NULL;
    for (i = 0; i < count; i++) {
        tail = node;
        node->mNext = (GScacheObjNode *)((u8 *)node + objSize);
        node = node->mNext;
    }

    tail->mNext = NULL;
}

void *GScache::allocFromPool(GScacheObjPool *pool) {
    GScacheObjNode *node = pool->mFreeHead;

    bool var1 = fn_801DBB3C();
    fn_801DBB44(false);

    if (node != NULL) {
        pool->mFreeHead = node->mNext;
    }
    else {
        fn_801DBB44(var1);
        return NULL;
    }

    fn_801DBB44(var1);

    memset(node, 0, pool->mNodeSize);

    pool->mUsedNodes++;
    
    if (pool->mUsedNodes > pool->mPeakUsedNodes) {
        pool->mPeakUsedNodes = pool->mUsedNodes;
    }

    return node + 1;
}

void GScache::freeToPool(GScacheObjPool *pool, void *obj) {
    bool var1;

    if (obj == NULL) {
        return;
    }

    GScacheObjNode *node = (GScacheObjNode *)obj - 1;
    node->mNext = pool->mFreeHead;

    pool->mUsedNodes--;

    var1 = fn_801DBB3C();
    fn_801DBB44(false);

    pool->mFreeHead = node;
    
    fn_801DBB44(var1);
}

GScacheObjPool *GScache::createObjectPool(u32 count, u32 objSize) {
    u32 i;
    for (i = 0; i < 32; i++) {
        if (sObjectPools[i].mCount == 0) {
            break;
        }
    }

    GScacheObjPool *pool = &sObjectPools[i];
    if (pool->mCount != 0) {
        return NULL;
    }

    initObjectPool(pool, count, objSize);

    return pool;
}
