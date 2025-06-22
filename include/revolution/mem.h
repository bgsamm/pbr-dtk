#ifndef MEM_H
#define MEM_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMiHeapHead MEMiHeapHead;
typedef MEMiHeapHead* MEMHeapHandle;

typedef void (*MEMHeapVisitor)(void*, MEMHeapHandle, u32);

MEMHeapHandle MEMCreateExpHeapEx(void*, u32, u16);
void* MEMAllocFromExpHeapEx(MEMHeapHandle, u32, int);
u32 MEMResizeForMBlockExpHeap(MEMHeapHandle, void*, u32);
void MEMFreeToExpHeap(MEMHeapHandle, void*);
u32 MEMGetTotalFreeSizeForExpHeap(MEMHeapHandle);
u16 MEMSetGroupIDForExpHeap(MEMHeapHandle, u16);
void MEMVisitAllocatedForExpHeap(MEMHeapHandle, MEMHeapVisitor, u32);
u32 MEMGetSizeForMBlockExpHeap(const void*);
u16 MEMGetGroupIDForMBlockExpHeap(const void*);

#ifdef __cplusplus
}
#endif

#endif // MEM_H
