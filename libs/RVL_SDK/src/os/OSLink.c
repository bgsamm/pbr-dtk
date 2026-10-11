// Imported from koopthekoopa/wii-ipl (CC0), libs/RVL_SDK/src/os/OSLink.c
#include <private/os.h>
#include <revolution/os.h>

void __OSModuleInit() {
    __OSModuleInfoList.tail = NULL;
    __OSModuleInfoList.head = NULL;
    __OSStringTable = NULL;
}
