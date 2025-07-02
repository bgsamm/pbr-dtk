#include "version.hpp"

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

void GSmem::freeHeapBlock(MEMHeapHandle heap, void *block) {
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

void *GSmem::allocFromDefaultHeap(u32 size) {
    return allocFromHeap(getDefaultHeap(), size);
}

void *GSmem::allocFromDefaultHeapAndClear(u32 size) {
    return allocFromHeapAndClear(getDefaultHeap(), size);
}

void *GSmem::allocFromDefaultHeapAligned(u32 size, int align) {
    return allocFromHeapAligned(getDefaultHeap(), size, align);
}

void *GSmem::allocFromDefaultHeapAlignedTop(u32 size, int align) {
    if (align > 0) {
        align = -align;
    }
    return allocFromHeapAligned(getDefaultHeap(), size, align);
}

u32 GSmem::resizeDefaultHeapBlock(void *block, u32 size) {
    return resizeHeapBlock(getDefaultHeap(), block, size);
}

void GSmem::freeDefaultHeapBlock(void *block) {
    if (block == NULL) {
        return;
    }
    freeHeapBlock(getDefaultHeap(), block);
}

u32 GSmem::getDefaultHeapBlockSize(void *block) {
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

void GSmem::copyMem(void *dst, const void *src, u32 size) {
    if ((u32)dst % 0x20 != 0 || (u32)src % 0x20 != 0 || size % 0x20 != 0) {
        memcpy(dst, src, size);
        return;
    }

    u32 *pDst = (u32 *)dst - 1;
    u32 *pSrc = (u32 *)src - 1;
    // TODO get this loop to unroll properly (asm? hand unrolled?)
    for (int i = 0;  i < size / 4; i++) {
        *(++pDst) = *(++pSrc);
    }
}
