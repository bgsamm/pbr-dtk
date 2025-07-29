#include "global.hpp"

#include <revolution/os.h>

#include "gs/GSfsys.hpp"
#include "gs/GSmem.hpp"

extern MEMHeapHandle lbl_8063E8EC;

#define CHUNK_SIZE 0x8000
#define CHUNK_HEAP_DEFAULT_SIZE 0x80000

/* lbl_8063F7D8 */ u32 GSfsys::gFsysChunkSize;
/* lbl_8063F7DC */ static u32 sFsysChunkHeapSize;
/* lbl_8063F7E0 */ static u32 sFsysChunkPoolCount;
/* lbl_8063F7E4 */ static u32 sFsysChunkPoolLastIndex;
/* lbl_8063F7E8 */ static void *sFsysChunkHeap;
/* lbl_8063F7EC */ static GSfsysChunk *sFsysChunkPool;

bool GSfsys::initFsysChunkSystem(u32 heapSize) {
    sFsysChunkPoolLastIndex = 0;
    gFsysChunkSize = CHUNK_SIZE;
    sFsysChunkHeapSize = heapSize;

    if (sFsysChunkHeapSize == 0) {
        sFsysChunkHeapSize = CHUNK_HEAP_DEFAULT_SIZE;
    }

    sFsysChunkPoolCount = sFsysChunkHeapSize / gFsysChunkSize;
    if (sFsysChunkPoolCount == 0) {
        return false;
    }

    sFsysChunkHeap = GSmem::allocFromHeap(lbl_8063E8EC, sFsysChunkPoolCount * gFsysChunkSize);
    if (sFsysChunkHeap == NULL) {
        return false;
    }

    sFsysChunkPool = (GSfsysChunk *)allocAligned32(sFsysChunkPoolCount * sizeof(GSfsysChunk));
    if (sFsysChunkPool == NULL) {
        return false;
    }

    for (u32 i = 0; i < sFsysChunkPoolCount; i++) {
        sFsysChunkPool[i].mPrev = NULL;
        sFsysChunkPool[i].mNext = NULL;
        sFsysChunkPool[i].mBuffer = NULL;
        sFsysChunkPool[i].mOffset = 0;
    }

    return true;
}

GSfsysChunk *GSfsys::getFreeFsysChunk() {
    GSfsysChunk *chunk = NULL;

    BOOL intEnabled = OSDisableInterrupts();
    
    u32 i = sFsysChunkPoolLastIndex;
    while (chunk == NULL) {
        if (sFsysChunkPool[i].mBuffer == NULL) {
            chunk = &sFsysChunkPool[i];

            chunk->mBuffer = (u8 *)sFsysChunkHeap + i * gFsysChunkSize;
            chunk->mPrev = NULL;
            chunk->mNext = NULL;
            chunk->mOffset = 0;
        }

        i++;
        if (i >= sFsysChunkPoolCount) {
            i = 0;
        }

        if (sFsysChunkPoolLastIndex == i) {
            break;
        }
    }
    sFsysChunkPoolLastIndex = i;

    OSRestoreInterrupts(intEnabled);

    return chunk;
}

bool GSfsys::popChunkFromList(GSfsysChunk **list, bool fromFront) {
    BOOL intEnabled = OSDisableInterrupts();

    GSfsysChunk *chunk = *list;
    if (chunk != NULL) {
        if (!fromFront) {
            while (chunk->mNext != NULL) {
                chunk = chunk->mNext;
            }

            if (chunk->mPrev != NULL) {
                chunk->mPrev->mNext = NULL;
            }

            if (*list == chunk) {
                *list = NULL;
            }

            chunk->mBuffer = NULL;
        }
        else {
            if (chunk->mPrev != NULL) {
                chunk->mPrev->mNext = chunk->mNext;
            }

            if (chunk->mNext != NULL) {
                chunk->mNext->mPrev = chunk->mPrev;
            }

            chunk->mBuffer = NULL;
            *list = chunk->mNext;
        }
    }

    OSRestoreInterrupts(intEnabled);

    return true;
}

void GSfsys::clearChunkList(GSfsysChunk **list) {
    while (true) {
        if (*list == NULL) {
            break;
        }
        popChunkFromList(list, true);
    }
}

void GSfsys::prependToChunkList(GSfsysChunk **list, GSfsysChunk *chunk) {
    BOOL intEnabled = OSDisableInterrupts();

    GSfsysChunk *head = *list;
    if (head != NULL) {
        if (chunk->mNext != NULL) {
            GSfsysChunk *end = chunk->mNext;
            while (end->mNext != NULL) {
                end = end->mNext;
            }
            end->mNext = head;
            head->mPrev = end;
        }
        else {
            chunk->mNext = head;
            head->mPrev = chunk;
        }
    }

    *list = chunk;

    OSRestoreInterrupts(intEnabled);
}

void GSfsys::transferChunkListTail(GSfsysChunk **srcList, GSfsysChunk **dstList) {
    BOOL intEnabled = OSDisableInterrupts();

    GSfsysChunk *chunk = *srcList;
    if (chunk != NULL) {
        while (chunk->mNext != NULL) {
            chunk = chunk->mNext;
        }
        
        if (chunk->mPrev != NULL) {
            chunk->mPrev->mNext = NULL;
        }

        if (*srcList == chunk) {
            *srcList = NULL;
        }

        chunk->mPrev = NULL;
        chunk->mNext = NULL;

        if (*dstList != NULL) {
            GSfsysChunk *end = *dstList;
            while (end->mNext != NULL) {
                end = end->mNext;
            }
            end->mNext = chunk;
            chunk->mPrev = end;
        }
        else {
            *dstList = chunk;
        }
    }

    OSRestoreInterrupts(intEnabled);
}
