#ifndef REVOLUTION_OS_CACHE_H
#define REVOLUTION_OS_CACHE_H

#include <revolution/os/OSError.h>
#include <revolution/types.h>


#ifdef __cplusplus
extern "C" {
#endif

#define LC_BASE_PREFIX (0xE000)
#define LC_BASE        (LC_BASE_PREFIX << 16)

#define LC_MAX_DMA_BLOCKS (128)
#define LC_MAX_DMA_BYTES (LC_MAX_DMA_BLOCKS * 32)

#define LCGetBase() ((void*)LC_BASE)

void DCEnable(void);

void DCInvalidateRange(void* addr, u32 len);

void DCFlushRange(void* addr, u32 len);
void DCFlushRangeNoSync(void* addr, u32 len);   

void DCStoreRange(void* addr, u32 len);
void DCStoreRangeNoSync(const void *addr, u32 len);

void DCZeroRange(void* addr, u32 len);

void ICEnable(void);
void ICFlashInvalidate(void);
void ICInvalidateRange(void* addr, u32 len);

void LCEnable(void);
void LCDisable(void);

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_OS_CACHE_H
