// Imported from doldecomp/ogws (CC0), include/revolution/DSP/dsp_hardware.h; register indexes as macros, register array mapped to ours
#ifndef REVOLUTION_DSP_HARDWARE_H
#define REVOLUTION_DSP_HARDWARE_H

#include <revolution/types.h>
#include <private/hollywood.h>
#define DSP_HW_REGS __DSPRegs

#define DSP_DSPMBOX_H 0
#define DSP_DSPMBOX_L 1
#define DSP_CPUMBOX_H 2
#define DSP_CPUMBOX_L 3
#define DSP_REG_0x8 4
#define DSP_CSR 5
#define DSP_REG_0xC 6
#define DSP_REG_0xE 7
#define DSP_REG_0x10 8
/* DSP_AR_SIZE is defined by our register headers */
#define DSP_REG_0x14 10
/* DSP_AR_MODE is defined by our register headers */
#define DSP_REG_0x18 12
/* DSP_AR_REFRESH is defined by our register headers */
#define DSP_REG_0x1C 14
#define DSP_REG_0x1E 15
/* DSP_AR_DMA_MMADDR_H is defined by our register headers */
/* DSP_AR_DMA_MMADDR_L is defined by our register headers */
/* DSP_AR_DMA_ARADDR_H is defined by our register headers */
/* DSP_AR_DMA_ARADDR_L is defined by our register headers */
#define DSP_AR_DMA_CNT_H 20
#define DSP_AR_DMA_CNT_L 21
#define DSP_REG_0x2C 22
#define DSP_REG_0x2E 23
#define DSP_AI_DMA_START_H 24
#define DSP_AI_DMA_START_L 25
#define DSP_REG_0x34 26
#define DSP_AI_DMA_CSR 27
#define DSP_REG_0x38 28
#define DSP_AI_DMA_BYTES_LEFT 29



// DSPMBOX_H - DSP Mailbox High (to DSP)
#define DSP_DSPMBOX_H_STATUS (1 << 15)

// CPUMBOX_H - CPU Mailbox High (from DSP)
#define DSP_CPUMBOX_H_STATUS (1 << 15)

// CSR - Control Status Register
#define DSP_CSR_RES (1 << 11)
#define DSP_CSR_DMAINT (1 << 9)
#define DSP_CSR_DSPINTMSK (1 << 8)
#define DSP_CSR_DSPINT (1 << 7)
#define DSP_CSR_ARINTMSK (1 << 6)
#define DSP_CSR_ARINT (1 << 5)
#define DSP_CSR_AIDINTMSK (1 << 4)
#define DSP_CSR_AIDINT (1 << 3)
#define DSP_CSR_HALT (1 << 2)
#define DSP_CSR_PIINT (1 << 1)

// AI_DMA_CSR - AI DMA Control Status Register
#define DSP_AI_DMA_CSR_PLAY (1 << 15)


#endif
