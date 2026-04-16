#ifndef PRIVATE_OS_THREAD_H
#define PRIVATE_OS_THREAD_H

#include <revolution/os/OSThread.h>

void __OSReschedule();

OSPriority __OSGetEffectivePriority(OSThread* thread);
void __OSPromoteThread(OSThread* thread, OSPriority priority);

#endif  // PRIVATE_OS_THREAD_H
