#include "gs/GSlinkedList.hpp"

#include "common.hpp"
#include "gs/GSmem.hpp"


static GSlistNode *sNodePool;
static GSlistNode *sNextFree;

void GSlinkedList::init(u32 size) {
    if (sNodePool) {
        GSmem::freeToHeap(gUnkHeap1, sNodePool);
    }

    u32 count = (size + sizeof(GSlistNode) - 1) / sizeof(GSlistNode);
    sNodePool = (GSlistNode *)GSmem::allocFromHeap(gUnkHeap1, count * sizeof(GSlistNode));
    sNextFree = sNodePool;

    GSlistNode *curr = sNextFree;
    for (u32 i = 0; i < count - 1; i++) {
        curr->mNextFree = curr + 1;
        curr++;
    }
    curr->mNextFree = NULL;
}

GSlistNode *GSlinkedList::allocNode() {
    GSlistNode *node = sNextFree;
    sNextFree = node->mNextFree;
    return node;
}

void GSlinkedList::freeNode(GSlistNode *node) {
    node->mNextFree = sNextFree;
    sNextFree = node;
}
