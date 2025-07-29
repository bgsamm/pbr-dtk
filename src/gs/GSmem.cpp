#include "global.hpp"

#include <cstring>
#include "gs/GSmem.hpp"

extern MEMHeapHandle lbl_8063E8E8;
extern MEMHeapHandle lbl_8063E8EC;

/* lbl_804912B0 */ static HeapSlot sHeapPool[MAX_HEAPS];

/* lbl_8063F2D6 */ static bool sInitialized; 
/* lbl_8063F2D7 */ static bool sUnusedFlag; 
/* lbl_8063F2D8 */ static MEMHeapHandle sDefaultHeap;
/* lbl_8063F2DC */ static u16 sDefaultGroupID;

HeapSlot *GSmem::getFreeHeapSlot() {
    for (int i = 0; i < MAX_HEAPS; i++) {
        if (!sHeapPool[i].isUsed) {
            return &sHeapPool[i];
        }
    }
    return NULL;
}

bool GSmem::isInitialized() {
    return sInitialized;
}

void GSmem::init() {
    memset(sHeapPool, 0, sizeof(sHeapPool));
    sDefaultHeap = NULL;
    sDefaultGroupID = 0;
    sInitialized = true;
    sUnusedFlag = false;
}

MEMHeapHandle GSmem::createHeap(void *startAddress, u32 size, u16 optFlag) {
    if (!isInitialized()) {
        return NULL;
    }
    
    HeapSlot *slot = getFreeHeapSlot();
    
    if (!slot) {
        return NULL;
    }
    
    MEMHeapHandle heap = MEMCreateExpHeapEx(startAddress, size, optFlag);
    
    slot->isUsed = true;
    slot->heap = heap;
    slot->size = size;

    return heap;
}

MEMHeapHandle GSmem::getDefaultHeap() {
    return sDefaultHeap;
}

MEMHeapHandle GSmem::setDefaultHeap(MEMHeapHandle heap) {
    MEMHeapHandle oldHeap = getDefaultHeap();
    sDefaultHeap = heap;

    return oldHeap;
}

// TODO revisit once more info about specific heaps is known
u16 GSmem::setDefaultGroupID(u16 groupID) {
    u16 oldID = sDefaultGroupID;
    sDefaultGroupID = groupID;
    MEMSetGroupIDForExpHeap(lbl_8063E8E8, (u8)sDefaultGroupID);
    MEMSetGroupIDForExpHeap(lbl_8063E8EC, (u8)sDefaultGroupID);

    return oldID;
}

u16 GSmem::setHeapGroupID(MEMHeapHandle heap, u16 groupID) {
    return MEMSetGroupIDForExpHeap(heap, groupID);
}

void *GSmem::allocFromHeap(MEMHeapHandle heap, u32 size) {
    return MEMAllocFromExpHeapEx(heap, size, 0x20);
}

void *GSmem::allocFromHeapAndFill(MEMHeapHandle heap, u32 size, u32 value) {
    void *mem = allocFromHeap(heap, size);

    if (!mem) {
        return NULL;
    }

    memset(mem, value, size);
    return mem;
}

void *GSmem::allocFromHeapAndClear(MEMHeapHandle heap, u32 size) {
    return allocFromHeapAndFill(heap, size, 0);
}

void *GSmem::allocFromHeapAligned(MEMHeapHandle heap, u32 size, int align) {
    return MEMAllocFromExpHeapEx(heap, size, align);
}

void *GSmem::allocFromHeapAlignedTop(MEMHeapHandle heap, u32 size, int align) {
    if (align > 0) {
        align = -align;
    }
    return MEMAllocFromExpHeapEx(heap, size, align);
}

bool GSmem::resizeHeapBlock(MEMHeapHandle heap, void *block, u32 size) {
    return MEMResizeForMBlockExpHeap(heap, block, size) != 0;
}

void GSmem::freeToHeap(MEMHeapHandle heap, void *block) {
    if (block == NULL) {
        return;
    }
    MEMFreeToExpHeap(heap, block);
}

u32 GSmem::getHeapBlockSize(MEMHeapHandle heap, void *block) {
    return MEMGetSizeForMBlockExpHeap(block);
}

u32 GSmem::getTotalFreeSizeInHeap(MEMHeapHandle heap) {
    return MEMGetTotalFreeSizeForExpHeap(heap);
}

void *GSmem::alloc(u32 size) {
    return allocFromHeap(getDefaultHeap(), size);
}

void *GSmem::allocAndClear(u32 size) {
    return allocFromHeapAndClear(getDefaultHeap(), size);
}

void *GSmem::allocAligned(u32 size, int align) {
    return allocFromHeapAligned(getDefaultHeap(), size, align);
}

void *GSmem::allocAlignedTop(u32 size, int align) {
    if (align > 0) {
        align = -align;
    }
    return allocFromHeapAligned(getDefaultHeap(), size, align);
}

u32 GSmem::realloc(void *block, u32 size) {
    return resizeHeapBlock(getDefaultHeap(), block, size);
}

void GSmem::free(void *block) {
    if (block == NULL) {
        return;
    }
    freeToHeap(getDefaultHeap(), block);
}

u32 GSmem::getAllocatedSize(void *block) {
    if (block == NULL) {
        return 0;
    }
    return MEMGetSizeForMBlockExpHeap(block);
}

u32 GSmem::getTotalFreeSizeInDefaultHeap() {
    return getTotalFreeSizeInHeap(getDefaultHeap());
}

void GSmem::freeAllInGroupVisitor(void *block, MEMHeapHandle heap, u32 ctx) {
    HeapVisitorContext *context = (HeapVisitorContext *)ctx;
    if (context->groupID == MEMGetGroupIDForMBlockExpHeap(block)) {
        MEMFreeToExpHeap(context->heap, block);
    }
}

void GSmem::freeAllInGroup(MEMHeapHandle heap, u16 groupID) {
    HeapVisitorContext context;
    context.heap = heap;
    context.groupID = groupID;
    context._8 = 0;
    MEMVisitAllocatedForExpHeap(heap, freeAllInGroupVisitor, (u32)&context);
}

asm void GSmem::copyMem(register void *dst, register const void *src, register u32 size) {
    clrlwi. r0, dst, 27
    bne     use_memcpy
    clrlwi. r0, src, 27
    bne     use_memcpy
    clrlwi. r0, size, 27
    beq     manual_copy

use_memcpy:
    b       memcpy

manual_copy:
    srwi    size, size, 5
    mtctr   size
    subi    dst, dst, 4
    subi    src, src, 4
loop:
    lwzu    r0, 0x4(src)
    lwzu    r5, 0x4(src)
    lwzu    r6, 0x4(src)
    lwzu    r7, 0x4(src)
    lwzu    r8, 0x4(src)
    lwzu    r9, 0x4(src)
    lwzu    r10, 0x4(src)
    lwzu    r11, 0x4(src)
    stwu    r0, 0x4(dst)
    stwu    r5, 0x4(dst)
    stwu    r6, 0x4(dst)
    stwu    r7, 0x4(dst)
    stwu    r8, 0x4(dst)
    stwu    r9, 0x4(dst)
    stwu    r10, 0x4(dst)
    stwu    r11, 0x4(dst)
    bdnz    loop
}
