// Imported from doldecomp/ogws (CC0), src/revolution/DSP/dsp_task.c
#include <revolution/dsp/dsp_hardware.h>

#include <decomp.h>
#include <private/dsp.h>
#include <revolution/os.h>

/**
 * Commands to the DSP sent via the mailbox.
 */
typedef enum {
    MAIL_SET_IRAM_MMEM_ADDR = 0x80F3A001,
    MAIL_SET_IRAM_DSP_ADDR  = 0x80F3C002,
    MAIL_SET_IRAM_LENGTH    = 0x80F3A002,
    MAIL_SET_ARAM_MMEM_ADDR = 0x80F3B002,
    MAIL_SET_START_VECTOR   = 0x80F3D001
} DSPMailCmd;

/**
 * DSP microcodes (from Dolphin Emulator)
 */
typedef enum {
    TASK_MAIL_MASK   = 0xFFFF0000,
    TASK_MAIL_TO_CPU = 0xDCD10000,
    TASK_MAIL_TO_DSP = 0xCDD10000,

    DSP_INIT      = (TASK_MAIL_TO_CPU | 0x0000),
    DSP_RESUME    = (TASK_MAIL_TO_CPU | 0x0001),
    DSP_YIELD     = (TASK_MAIL_TO_CPU | 0x0002),
    DSP_DONE      = (TASK_MAIL_TO_CPU | 0x0003),
    DSP_SYNC      = (TASK_MAIL_TO_CPU | 0x0004),
    DSP_FRAME_END = (TASK_MAIL_TO_CPU | 0x0005),

    MAIL_RESUME    = (TASK_MAIL_TO_DSP | 0x0000),
    MAIL_NEW_UCODE = (TASK_MAIL_TO_DSP | 0x0001),
    MAIL_RESET     = (TASK_MAIL_TO_DSP | 0x0002),
    MAIL_CONTINUE  = (TASK_MAIL_TO_DSP | 0x0003)
} DSPUCode;

DSPTaskInfo *__DSP_curr_task;
DSPTaskInfo *__DSP_first_task;
DSPTaskInfo *__DSP_last_task;
DSPTaskInfo *__DSP_tmp_task;
DSPTaskInfo *__DSP_rude_task;
BOOL __DSP_rude_task_pending;

void __DSPHandler(s16 intr, OSContext *ctx) {
#pragma unused(intr)

    OSContext tmpCtx;
    u32 ucode;

    DSP_HW_REGS[DSP_CSR] = (DSP_HW_REGS[DSP_CSR] & ~(DSP_CSR_AIDINT | DSP_CSR_ARINT)) | DSP_CSR_DSPINT;

    OSClearContext(&tmpCtx);
    OSSetCurrentContext(&tmpCtx);

    while (!DSPCheckMailFromDSP()) {
        ;
    }
    ucode = (u32)DSPReadMailFromDSP();

    if ((__DSP_curr_task->flags & DSP_TASK_CANCELED) && ucode == DSP_YIELD) {
        ucode = DSP_DONE;
    }

    switch (ucode) {
        case DSP_INIT:
            __DSP_curr_task->state = DSP_TASK_STATE_1;
            if (__DSP_curr_task->init_cb != NULL) {
                __DSP_curr_task->init_cb(__DSP_curr_task);
            }
            break;
        case DSP_RESUME:
            __DSP_curr_task->state = DSP_TASK_STATE_1;
            if (__DSP_curr_task->res_cb != NULL) {
                __DSP_curr_task->res_cb(__DSP_curr_task);
            }
            break;
        case DSP_YIELD:
            if (__DSP_rude_task_pending) {
                if (__DSP_curr_task == __DSP_rude_task) {
                    DSP_SEND_MAIL_SYNC(MAIL_CONTINUE);

                    __DSP_rude_task = NULL;
                    __DSP_rude_task_pending = FALSE;

                    if (__DSP_curr_task->res_cb != NULL) {
                        __DSP_curr_task->res_cb(__DSP_curr_task);
                    }
                } else {
                    DSP_SEND_MAIL_SYNC(MAIL_NEW_UCODE);

                    __DSP_exec_task(__DSP_curr_task, __DSP_rude_task);

                    __DSP_curr_task->state = DSP_TASK_STATE_2;
                    __DSP_curr_task = __DSP_rude_task;

                    __DSP_rude_task = NULL;
                    __DSP_rude_task_pending = FALSE;
                }
            } else if (__DSP_curr_task->next == NULL) {
                if (__DSP_curr_task == __DSP_first_task) {
                    DSP_SEND_MAIL_SYNC(MAIL_CONTINUE);

                    if (__DSP_curr_task->res_cb != NULL) {
                        __DSP_curr_task->res_cb(__DSP_curr_task);
                    }
                } else {
                    DSP_SEND_MAIL_SYNC(MAIL_NEW_UCODE);

                    __DSP_exec_task(__DSP_curr_task, __DSP_first_task);

                    __DSP_curr_task->state = DSP_TASK_STATE_2;
                    __DSP_curr_task = __DSP_first_task;
                }
            } else {
                DSP_SEND_MAIL_SYNC(MAIL_NEW_UCODE);

                __DSP_exec_task(__DSP_curr_task, __DSP_curr_task->next);

                __DSP_curr_task->state = DSP_TASK_STATE_2;
                __DSP_curr_task = __DSP_curr_task->next;
            }
            break;
        case DSP_DONE:
            if (__DSP_rude_task_pending) {
                if (__DSP_curr_task != __DSP_rude_task) {
                    if (__DSP_curr_task->done_cb != NULL) {
                        __DSP_curr_task->done_cb(__DSP_curr_task);
                    }

                    DSP_SEND_MAIL_SYNC(MAIL_NEW_UCODE);

                    __DSP_exec_task(NULL, __DSP_rude_task);
                    __DSP_remove_task(__DSP_curr_task);

                    __DSP_curr_task = __DSP_rude_task;
                    __DSP_rude_task = NULL;
                    __DSP_rude_task_pending = FALSE;
                    break;
                }

                __DSP_rude_task = NULL;
                __DSP_rude_task_pending = FALSE;
            }

            if (__DSP_curr_task->next == NULL) {
                if (__DSP_curr_task == __DSP_first_task) {
                    if (__DSP_curr_task->done_cb != NULL) {
                        __DSP_curr_task->done_cb(__DSP_curr_task);
                    }

                    DSP_SEND_MAIL_SYNC(MAIL_RESET);

                    __DSP_curr_task->state = DSP_TASK_STATE_3;
                    __DSP_remove_task(__DSP_curr_task);

                } else {
                    if (__DSP_curr_task->done_cb != NULL) {
                        __DSP_curr_task->done_cb(__DSP_curr_task);
                    }

                    DSP_SEND_MAIL_SYNC(MAIL_NEW_UCODE);

                    __DSP_curr_task->state = DSP_TASK_STATE_3;
                    __DSP_exec_task(NULL, __DSP_first_task);
                    __DSP_curr_task = __DSP_first_task;
                    __DSP_remove_task(__DSP_last_task);
                }
            } else {
                if (__DSP_curr_task->done_cb != NULL) {
                    __DSP_curr_task->done_cb(__DSP_curr_task);
                }

                DSP_SEND_MAIL_SYNC(MAIL_NEW_UCODE);

                __DSP_curr_task->state = DSP_TASK_STATE_3;
                __DSP_exec_task(NULL, __DSP_curr_task->next);
                __DSP_curr_task = __DSP_curr_task->next;
                __DSP_remove_task(__DSP_curr_task->prev);
            }
            break;
        case DSP_SYNC:
            if (__DSP_curr_task->req_cb != NULL) {
                __DSP_curr_task->req_cb(__DSP_curr_task);
            }
            break;
    }

    OSClearContext(&tmpCtx);
    OSSetCurrentContext(ctx);
}

void __DSP_exec_task(DSPTaskInfo *task1, DSPTaskInfo *task2) {
    if (task1 != NULL) {
        DSP_SEND_MAIL_SYNC(task1->dram_mmem_addr);
        DSP_SEND_MAIL_SYNC(task1->dram_length);
        DSP_SEND_MAIL_SYNC(task1->dram_addr);
    } else {
        DSP_SEND_MAIL_SYNC(0);
        DSP_SEND_MAIL_SYNC(0);
        DSP_SEND_MAIL_SYNC(0);
    }

    DSP_SEND_MAIL_SYNC(task2->iram_mmem_addr);
    DSP_SEND_MAIL_SYNC(task2->iram_length);
    DSP_SEND_MAIL_SYNC(task2->iram_addr);

    if (task2->state == DSP_TASK_STATE_0) {
        DSP_SEND_MAIL_SYNC(task2->dsp_init_vector);
        DSP_SEND_MAIL_SYNC(0);
        DSP_SEND_MAIL_SYNC(0);
        DSP_SEND_MAIL_SYNC(0);
    } else {
        DSP_SEND_MAIL_SYNC(task2->dsp_resume_vector);
        DSP_SEND_MAIL_SYNC(task2->dram_mmem_addr);
        DSP_SEND_MAIL_SYNC(task2->dram_length);
        DSP_SEND_MAIL_SYNC(task2->dram_addr);
    }
}

void __DSP_boot_task(DSPTaskInfo *task) {
    volatile u32 mail;

    // Sync with DSP
    while (!DSPCheckMailFromDSP()) {
        ;
    }
    mail = DSPReadMailFromDSP();

    // Send IRAM MMEM address
    DSP_SEND_MAIL_SYNC(MAIL_SET_IRAM_MMEM_ADDR);
    DSP_SEND_MAIL_SYNC(task->iram_mmem_addr);

    // Send IRAM DSP address
    DSP_SEND_MAIL_SYNC(MAIL_SET_IRAM_DSP_ADDR);
    DSP_SEND_MAIL_SYNC(task->iram_addr & 0xFFFF);

    // Send IRAM length
    DSP_SEND_MAIL_SYNC(MAIL_SET_IRAM_LENGTH);
    DSP_SEND_MAIL_SYNC(task->iram_length);

    // Send ARAM MMEM address(?)
    DSP_SEND_MAIL_SYNC(MAIL_SET_ARAM_MMEM_ADDR);
    DSP_SEND_MAIL_SYNC(NULL);

    // Send start vector
    DSP_SEND_MAIL_SYNC(MAIL_SET_START_VECTOR);
    DSP_SEND_MAIL_SYNC(task->dsp_init_vector);

    __DSP_debug_printf("DSP is booting task: 0x%08X\n", task);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM MMEM ADDR: 0x%08X\n", task->iram_mmem_addr);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM DSP ADDR : 0x%08X\n", task->iram_addr);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM LENGTH   : 0x%08X\n", task->iram_length);
    __DSP_debug_printf("__DSP_boot_task()  : DRAM MMEM ADDR: 0x%08X\n", task->dram_length);
    __DSP_debug_printf("__DSP_boot_task()  : Start Vector  : 0x%08X\n", task->dsp_init_vector);
}

void __DSP_insert_task(DSPTaskInfo *task) {
    DSPTaskInfo *it;
    DSPTaskInfo *first;
    DSPTaskInfo *prev;

    it = __DSP_first_task;

    if (__DSP_first_task == NULL) {
        __DSP_first_task = __DSP_last_task = __DSP_curr_task = task;
        task->next = task->prev = NULL;
        return;
    }

    first = __DSP_first_task;

    // Tasks sorted by priority
    for (; it != NULL; it = it->next) {
        if (task->priority < it->priority) {
            task->prev = it->prev;
            it->prev = task;
            task->next = it;

            first = task;
            prev = task->prev;

            if (prev == NULL) {
                __DSP_first_task = first;
            } else {
                prev->next = task;
            }

            break;
        }
    }

    if (it == NULL) {
        __DSP_last_task->next = task;
        task->next = NULL;
        task->prev = __DSP_last_task;
        __DSP_last_task = task;
    }
}

void __DSP_remove_task(DSPTaskInfo *task) {
    task->flags = 0;
    task->state = DSP_TASK_STATE_3;

    if (__DSP_first_task == task) {
        if (task->next != NULL) {
            __DSP_first_task = task->next;
            task->next->prev = NULL;
        } else {
            __DSP_curr_task = NULL;
            __DSP_last_task = NULL;
            __DSP_first_task = NULL;
        }
    } else if (__DSP_last_task == task) {
        __DSP_last_task = task->prev;
        task->prev->next = NULL;
        __DSP_curr_task = __DSP_first_task;
    } else {
        __DSP_curr_task = task->next;
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }
}

DECOMP_FORCE_ACTIVE(dsp_task_c, "__DSP_add_task() : Added task    : 0x%08X\n");
