// Imported from doldecomp/ogws (CC0), src/revolution/DSP/dsp.c
#include <revolution/dsp/dsp_hardware.h>

#include <private/dsp.h>
#include <revolution/os.h>

const char *__DSPVersion = "<< RVL_SDK - DSP \trelease build: Nov 30 2006 03:26:46 (0x4199_60831) >>";

static BOOL __DSP_init_flag = FALSE;

BOOL DSPCheckMailToDSP(void) {
    return (DSP_HW_REGS[DSP_DSPMBOX_H] & DSP_DSPMBOX_H_STATUS) != 0;
}

BOOL DSPCheckMailFromDSP(void) {
    return (DSP_HW_REGS[DSP_CPUMBOX_H] & DSP_CPUMBOX_H_STATUS) != 0;
}

u32 DSPReadMailFromDSP(void) {
    return (u32)(DSP_HW_REGS[DSP_CPUMBOX_H] << 16 | DSP_HW_REGS[DSP_CPUMBOX_L]);
}

void DSPSendMailToDSP(u32 mail) {
    DSP_HW_REGS[DSP_DSPMBOX_H] = ((u32)mail) >> 16 & 0xFFFF;
    DSP_HW_REGS[DSP_DSPMBOX_L] = ((u32)mail) & 0xFFFF;
}

void DSPAssertInt(void) {
    BOOL enabled;

    enabled = OSDisableInterrupts();

    DSP_HW_REGS[DSP_CSR] = (DSP_HW_REGS[DSP_CSR] & ~(DSP_CSR_AIDINT | DSP_CSR_ARINT | DSP_CSR_DSPINT)) | DSP_CSR_PIINT;

    OSRestoreInterrupts(enabled);
}

void DSPInit(void) {
    BOOL enabled;

    __DSP_debug_printf("DSPInit(): Build Date: %s %s\n", "Nov 30 2006", "03:26:46");

    if (__DSP_init_flag == TRUE) {
        return;
    }

    OSRegisterVersion(__DSPVersion);

    enabled = OSDisableInterrupts();

    __OSSetInterruptHandler(__OS_INTERRUPT_DSP_DSP, __DSPHandler);
    __OSUnmaskInterrupts(OS_INTERRUPTMASK(__OS_INTERRUPT_DSP_DSP));

    DSP_HW_REGS[DSP_CSR] = (DSP_HW_REGS[DSP_CSR] & ~(DSP_CSR_AIDINT | DSP_CSR_ARINT | DSP_CSR_DSPINT)) | DSP_CSR_RES;

    DSP_HW_REGS[DSP_CSR] &= ~(DSP_CSR_HALT | DSP_CSR_AIDINT | DSP_CSR_ARINT | DSP_CSR_DSPINT);

    __DSP_tmp_task = NULL;
    __DSP_curr_task = NULL;
    __DSP_last_task = NULL;
    __DSP_first_task = NULL;

    __DSP_init_flag = TRUE;

    OSRestoreInterrupts(enabled);
}

BOOL DSPCheckInit(void) {
    return __DSP_init_flag;
}

DSPTaskInfo *DSPAddTask(DSPTaskInfo *task) {
    BOOL enabled;

    enabled = OSDisableInterrupts();

    __DSP_insert_task(task);
    task->state = DSP_TASK_STATE_0;
    task->flags = DSP_TASK_ACTIVE;

    OSRestoreInterrupts(enabled);

    if (task == __DSP_first_task) {
        __DSP_boot_task(task);
    }

    return task;
}

DSPTaskInfo *DSPAssertTask(DSPTaskInfo *task) {
    BOOL enabled;

    enabled = OSDisableInterrupts();

    if (__DSP_curr_task == task) {
        __DSP_rude_task_pending = TRUE;
        __DSP_rude_task = task;
        OSRestoreInterrupts(enabled);
        return task;
    }

    if (task->priority < __DSP_curr_task->priority) {
        __DSP_rude_task_pending = TRUE;
        __DSP_rude_task = task;

        if (__DSP_curr_task->state == DSP_TASK_STATE_1) {
            DSPAssertInt();
        }

        OSRestoreInterrupts(enabled);
        return task;
    }

    OSRestoreInterrupts(enabled);
    return NULL;
}
