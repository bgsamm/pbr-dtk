#ifndef OSCONTEXT_H
#define OSCONTEXT_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// size: 0x2c8
typedef struct OSContext {
    u32 gpr[32];
    u32 cr;
    u32 lr;
    u32 ctr;
    u32 xer;
    f64 fpr[32];
    u32 fpscr_pad;
    u32 fpscr;
    u32 srr0;
    u32 srr1;
    u16 mode;
    u16 state;
    u32 gqr[8];
    u32 psf_pad;
    f64 psf[32];
} OSContext;

#ifdef __cplusplus
}
#endif

#endif // OSCONTEXT_H
