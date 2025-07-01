#pragma once

#include <revolution/types.h>
#include <revolution/mem.h>

#define MAX_HEAPS 16

typedef MEMHeapHandle GSheapHandle;

struct HeapSlot {
    /* 0x0 */ bool isUsed;
    /* 0x4 */ GSheapHandle heap;
    /* 0x8 */ u32 size;
};

struct HeapVisitorContext {
    /* 0x0 */ GSheapHandle heap;
    /* 0x4 */ u16 groupID;
    // TODO name this field
    /* 0x8 */ u32 _8;
};

class GSmem {
public:
    static HeapSlot *getFreeHeapSlot() NO_INLINE;
    static bool isInitialized() NO_INLINE;
    static void init();
    static GSheapHandle createHeap(void *startAddress, u32 size, u16 optFlag);
    static GSheapHandle getDefaultHeap() NO_INLINE;
    static GSheapHandle setDefaultHeap(GSheapHandle heap);
    static u16 setDefaultGroupID(u16 groupID);
    static u16 setHeapGroupID(GSheapHandle heap, u16 groupID);
    static void *allocFromHeap(GSheapHandle heap, u32 size) NO_INLINE;
    static void *allocFromHeapAndFill(GSheapHandle heap, u32 size, u32 value) NO_INLINE;
    static void *allocFromHeapAndClear(GSheapHandle heap, u32 size) NO_INLINE;
    static void *allocFromHeapAligned(GSheapHandle heap, u32 size, int align) NO_INLINE;
    static void *allocFromHeapAlignedTop(GSheapHandle heap, u32 size, int align);
    static bool resizeHeapBlock(GSheapHandle heap, void *block, u32 size) NO_INLINE;
    static void freeHeapBlock(GSheapHandle heap, void *block) NO_INLINE;
    static u32 getHeapBlockSize(GSheapHandle heap, void *block);
    static u32 getTotalFreeSizeInHeap(GSheapHandle heap) NO_INLINE;
    static void *allocFromDefaultHeap(u32 size);
    static void *allocFromDefaultHeapAndClear(u32 size);
    static void *allocFromDefaultHeapAligned(u32 size, int align);
    static void *allocFromDefaultHeapAlignedTop(u32 size, int align);
    static u32 resizeDefaultHeapBlock(void *block, u32 size);
    static void freeDefaultHeapBlock(void *block);
    static u32 getDefaultHeapBlockSize(void *block);
    static u32 getTotalFreeSizeInDefaultHeap();
    static void freeAllInGroupVisitor(void *block, GSheapHandle heap, u32 ctx);
    static void freeAllInGroup(GSheapHandle heap, u16 groupID);
    static void copyMem(void *dst, const void *src, u32 size);
};
