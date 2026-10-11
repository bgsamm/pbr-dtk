// Imported from koopthekoopa/wii-ipl (CC0), libs/RVL_SDK/src/os/OSCache.c
#include <decomp.h>

#include <revolution/os.h>

#include <revolution/base/PPCArch.h>

#include <private/db.h>


// clang-format off

asm void DCEnable() {
#ifdef __MWERKS__
    nofralloc
    
    sync

    // Enable cache
    mfspr   r3, HID0
    ori     r3, r3, HID0_DCE
    mtspr   HID0, r3

    blr
#endif // __MWERKS__
}

asm void DCInvalidateRange(register void* addr, register u32 len) {
#ifdef __MWERKS__
    nofralloc
    
    cmplwi  len, 0
    blelr 

    clrlwi  r5, addr, 27
    add     len, len, r5
    addi    len, len, 31
    srwi    len, len, 5
    mtctr   len

do_invalidate:
    dcbi    0, addr
    addi    addr, addr, 32
    bdnz    do_invalidate

    blr
#endif // __MWERKS__
}

asm void DCFlushRange(register void* addr, register u32 len) {
#ifdef __MWERKS__
    nofralloc
    
    cmplwi  len, 0
    blelr 

    clrlwi  r5, addr, 27
    add     len, len, r5
    addi    len, len, 31
    srwi    len, len, 5
    mtctr   len

do_flush:
    dcbf    0, addr
    addi    addr, addr, 32
    bdnz    do_flush
    sc

    blr
#endif // __MWERKS__
}

asm void DCStoreRange(register void* addr, register u32 len) {
#ifdef __MWERKS__
    nofralloc
    
    cmplwi  len, 0
    blelr 

    clrlwi  r5, addr, 27
    add     len, len, r5
    addi    len, len, 31
    srwi    len, len, 5
    mtctr   len

do_store:
    dcbst   0, addr
    addi    addr, addr, 32
    bdnz    do_store
    sc

    blr
#endif // __MWERKS__
}

asm void DCFlushRangeNoSync(register void* addr, register u32 len) {
#ifdef __MWERKS__
    nofralloc
    
    cmplwi  len, 0
    blelr 

    clrlwi  r5, addr, 27
    add     len, len, r5
    addi    len, len, 31
    srwi    len, len, 5
    mtctr   len

do_flush:
    dcbf    0, addr
    addi    addr, addr, 32
    bdnz    do_flush

    blr
#endif // __MWERKS__
}

asm void DCStoreRangeNoSync(register const void* addr, register u32 len) {
#ifdef __MWERKS__
    nofralloc

    cmplwi  len, 0
    blelr

    clrlwi  r5, addr, 27
    add     len, len, r5
    addi    len, len, 31
    srwi    len, len, 5
    mtctr   len

do_store:
    dcbst   0, addr
    addi    addr, addr, 32
    bdnz    do_store

    blr
#endif // __MWERKS__
}

asm void DCZeroRange(register void* addr, register u32 len) {
#ifdef __MWERKS__
    nofralloc
    
    cmplwi  len, 0
    blelr 

    clrlwi  r5, addr, 27
    add     len, len, r5
    addi    len, len, 31
    srwi    len, len, 5
    mtctr   len

do_zero:
    dcbz    0, addr
    addi    addr, addr, 32
    bdnz    do_zero

    blr
#endif // __MWERKS__
}

asm void ICInvalidateRange(register void* addr, register u32 len) {
#ifdef __MWERKS__
    nofralloc
    
    cmplwi  len, 0
    blelr 

    clrlwi  r5, addr, 27
    add     len, len, r5
    addi    len, len, 31
    srwi    len, len, 5
    mtctr   len

do_invalidate:
    icbi    0, addr
    addi    addr, addr, 32
    bdnz    do_invalidate
    
    sync
    isync

    blr
#endif // __MWERKS__
}

asm void ICFlashInvalidate() {
#ifdef __MWERKS__
    nofralloc
    
    mfspr   r3, HID0
    ori     r3, r3, HID0_ICFI
    mtspr   HID0, r3

    blr
#endif // __MWERKS__
}

asm void ICEnable() {
#ifdef __MWERKS__
    nofralloc

    isync
    mfspr   r3, HID0
    ori     r3, r3, HID0_ICE
    mtspr   HID0, r3

    blr
#endif // __MWERKS__
}

#define LC_LINES    512

static asm void __LCEnable() {
#ifdef __MWERKS__
    nofralloc

    mfmsr   r5
    ori     r5, r5, 0x1000
    mtmsr   r5

    lis     r3, 0x8000
    li      r4, 0x400
    mtctr   r4
do_touch:
    dcbt    0, r3
    dcbst   0, r3
    addi    r3, r3, 32
    bdnz    do_touch

    mfspr   r4, HID2
    oris    r4, r4, 0x100f
    mtspr   HID2, r4

    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    lis     r3, LC_BASE_PREFIX
    ori     r3, r3, 0x2
    mtdbatl 3, r3
    ori     r3, r3, 0x1fe
    mtdbatu 3, r3
    isync

    lis     r3, LC_BASE_PREFIX
    li      r6, 0x200
    mtctr   r6
    li      r6, 0
do_zero_lc:
    dcbz_l  r6, r3
    addi    r3, r3, 32
    bdnz    do_zero_lc

    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    blr
#endif // __MWERKS__
}

// clang-format on

void LCEnable() {
    BOOL enabled = OSDisableInterrupts();
    __LCEnable();
    OSRestoreInterrupts(enabled);
}

// clang-format off

asm void LCDisable() {
#ifdef __MWERKS__
    nofralloc
    
    lis     r3, LC_BASE_PREFIX
    li      r4, LC_LINES
    mtctr   r4
do_invalidate:
    dcbi    0, r3
    addi    r3, r3, 32
    bdnz    do_invalidate
    
    mfspr   r4, HID2
    rlwinm  r4, r4, 0, 4, 2
    mtspr   HID2, r4

    blr
#endif // __MWERKS__
}

asm void LCStoreBlocks(register void* dst, register void* src, register u32 blocks) {
#ifdef __MWERKS__
    nofralloc

    rlwinm  r6, blocks, 30, 27, 31
    clrlwi  dst, dst, 3
    or      r6, r6, dst
    mtspr   DMA_U, r6

    rlwinm  r6, blocks, 2, 28, 29
    or      r6, r6, src
    ori     r6, r6, 0x2
    mtspr   DMA_L, r6

    blr
#endif // __MWERKS__
}

// clang-format on

u32 LCStoreData(void* dst, void* src, u32 len) {
    u32 blocks = (len + 31) >> 5;
    u32 transfers = (blocks + 127) >> 7;

    while (blocks != 0) {
        if (blocks < LC_MAX_DMA_BLOCKS) {
            LCStoreBlocks(dst, src, blocks);
            blocks = 0;
        } else {
            LCStoreBlocks(dst, src, 0);
            blocks -= LC_MAX_DMA_BLOCKS;
            dst = (u8*)dst + LC_MAX_DMA_BLOCKS * 32;
            src = (u8*)src + LC_MAX_DMA_BLOCKS * 32;
        }
    }

    return transfers;
}

// clang-format off

asm void LCQueueWait(register u32 len) {
#ifdef __MWERKS__
    nofralloc

wait:
    mfspr   r4, HID2
    rlwinm  r4, r4, 8, 28, 31
    cmpw    r4, len
    bgt     wait

    blr
#endif // __MWERKS__
}

// clang-format on

static void L2Init() {
    u32 msr;

    msr = PPCMfmsr();
    __sync();
    PPCMtmsr(MSR_IR | MSR_DR);
    __sync();

    L2Disable();
    L2GlobalInvalidate();
    PPCMtmsr(msr);
}

void L2Enable() {
    u32 l2cr = PPCMfl2cr();
    PPCMtl2cr((l2cr | L2CR_L2E) & ~L2CR_L2I);
}

void L2Disable() {
    u32 l2cr;

    __sync();
    l2cr = PPCMfl2cr();
    PPCMtl2cr(l2cr & ~L2CR_L2E);
    __sync();
}

void L2GlobalInvalidate() {
    u32 l2cr;

    L2Disable();

    l2cr = PPCMfl2cr();
    PPCMtl2cr(l2cr | L2CR_L2I);

    while (PPCMfl2cr() & L2CR_L2IP) {
    }

    l2cr = PPCMfl2cr();
    PPCMtl2cr(l2cr & ~L2CR_L2I);

    while (PPCMfl2cr() & L2CR_L2IP) {
        DBPrintf(">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n");
    }
}

void DMAErrorHandler(OSError error, OSContext* context, ...) {
    u32 hid2 = PPCMfhid2();

    OSReport("Machine check received\n");
    OSReport("HID2 = 0x%x   SRR1 = 0x%x\n", hid2, context->srr1);

    if (!(hid2 & (HID2_DCHERR | HID2_DNCERR | HID2_DCMERR | HID2_DQOERR)) || !(context->srr1 & 0x200000)) {
        OSReport("Machine check was not DMA/locked cache related\n");
        OSDumpContext(context);
        PPCHalt();
    }

    OSReport("DMAErrorHandler(): An error occurred while processing DMA.\n");
    OSReport("The following errors have been detected and cleared :\n");

    if (hid2 & HID2_DCHERR) {
        OSReport("\t- Requested a locked cache tag that was already in the cache\n");
    }
    if (hid2 & HID2_DNCERR) {
        OSReport("\t- DMA attempted to access normal cache\n");
    }
    if (hid2 & HID2_DCMERR) {
        OSReport("\t- DMA missed in data cache\n");
    }
    if (hid2 & HID2_DQOERR) {
        OSReport("\t- DMA queue overflowed\n");
    }

    PPCMthid2(hid2);
}

void __OSCacheInit() {
    if (!(PPCMfhid0() & HID0_ICE)) {
        ICEnable();
        DBPrintf("L1 i-caches initialized\n");
    }

    if (!(PPCMfhid0() & HID0_DCE)) {
        DCEnable();
        DBPrintf("L1 d-caches initialized\n");
    }

    if (!(PPCMfl2cr() & L2CR_L2E)) {
        L2Init();
        L2Enable();
        DBPrintf("L2 cache initialized\n");
    }

    OSSetErrorHandler(OS_EXCEPTION_MACHINE_CHECK, DMAErrorHandler);
    DBPrintf("Locked cache machine check handler installed\n");
}
