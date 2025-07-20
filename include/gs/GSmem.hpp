#pragma once

#include <revolution/types.h>
#include <revolution/mem.h>

#define MAX_HEAPS 16

struct HeapSlot {
    /* 0x0 */ bool isUsed;
    /* 0x4 */ MEMHeapHandle heap;
    /* 0x8 */ u32 size;
};

struct HeapVisitorContext {
    /* 0x0 */ MEMHeapHandle heap;
    /* 0x4 */ u16 groupID;
    // TODO name this field
    /* 0x8 */ u32 _8;
};

// TODO improve function names
class GSmem {
public:
    static HeapSlot *getFreeHeapSlot() NO_INLINE;
    static bool isInitialized() NO_INLINE;
    static void init();
    static MEMHeapHandle createHeap(void *startAddress, u32 size, u16 optFlag);
    static MEMHeapHandle getDefaultHeap() NO_INLINE;
    static MEMHeapHandle setDefaultHeap(MEMHeapHandle heap);
    static u16 setDefaultGroupID(u16 groupID);
    static u16 setHeapGroupID(MEMHeapHandle heap, u16 groupID);
    static void *allocFromHeap(MEMHeapHandle heap, u32 size) NO_INLINE;
    static void *allocFromHeapAndFill(MEMHeapHandle heap, u32 size, u32 value) NO_INLINE;
    static void *allocFromHeapAndClear(MEMHeapHandle heap, u32 size) NO_INLINE;
    static void *allocFromHeapAligned(MEMHeapHandle heap, u32 size, int align) NO_INLINE;
    static void *allocFromHeapAlignedTop(MEMHeapHandle heap, u32 size, int align);
    static bool resizeHeapBlock(MEMHeapHandle heap, void *block, u32 size) NO_INLINE;
    static void freeHeapBlock(MEMHeapHandle heap, void *block) NO_INLINE;
    static u32 getHeapBlockSize(MEMHeapHandle heap, void *block);
    static u32 getTotalFreeSizeInHeap(MEMHeapHandle heap) NO_INLINE;
    static void *alloc(u32 size);
    static void *allocAndClear(u32 size);
    static void *allocAligned(u32 size, int align);
    static void *allocAlignedTop(u32 size, int align);
    static u32 realloc(void *block, u32 size);
    static void free(void *block);
    static u32 getAllocatedSize(void *block);
    static u32 getTotalFreeSizeInDefaultHeap();
    static void freeAllInGroupVisitor(void *block, MEMHeapHandle heap, u32 ctx);
    static void freeAllInGroup(MEMHeapHandle heap, u16 groupID);
    static void copyMem(void *dst, const void *src, u32 size);
};
