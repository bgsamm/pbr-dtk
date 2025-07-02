#include <revolution/types.h>
#include <revolution/os.h>
#include <revolution/vi.h>

#include "gs/GSmem.hpp"
#include "gs/GStask.hpp"
#include "gs/GSthread.hpp"
#include "gs/GSvideo.hpp"

void fn_80006980(u32, u32);
void fn_80006A00(u32, u32);
void fn_80006A84(u32, u32);
void *fn_80006A88(void *);
void fn_800071F8();
void fn_80007260();
void fn_800072C4();
void fn_80007338();

void fn_8000AE8C();
void fn_80055D94();
void fn_80059208();
void fn_8005925C(u32);
void fn_801DB15C(u32);
void fn_801DB978(u32);
void fn_80223BC8();
void fn_80223F0C(u32, u32);
void fn_8022410C(u32);
void fn_80224214(u32, u32, void *, u32, u32, u32, u32);
void fn_802247C8(u32);
void fn_80231490(void *, f32);
void fn_80231544(void *);
void fn_802353F8(void *);
void fn_80237794(void *, u32);
void fn_8024483C(u32);
void fn_80244A50();
void fn_8024575C();
void fn_80249BA0(u32, u32);
void fn_80249BF0(u32);

struct UnkStruct1 {
    u8 _0;
    u16 _2;
    u32 _4;
    u32 _8;
    u32 _C;
    u32 _10;
    u16 _14;
    u8 _16;
    u8 _17;
};

class UnkClass1 {
public:
    u8 unk[0x2c];

    UnkClass1(u32);
};

MEMHeapHandle lbl_8063E8E8; // global
MEMHeapHandle lbl_8063E8EC; // global
MEMHeapHandle lbl_8063E8F0;
MEMHeapHandle lbl_8063E8F4;
MEMHeapHandle lbl_8063E8F8; // global
u8 lbl_8063E8FC; // global?
u8 lbl_8063E8FE;
u8 lbl_8063E8FF;
u8 lbl_8063E900;

u32 lbl_8063F600;
void *lbl_8063F698;

// "main render"
void fn_80006980(void) {
    u8 refreshRate;
    f32 var2;

    refreshRate = GSvideo::sInstance->mRefreshRate;
    var2 = GSvideo::sInstance->fn_8023FFEC() / refreshRate;

    fn_80231490(lbl_8063F698, var2 > 0f ? var2 : 0f);
    fn_80231544(lbl_8063F698);

    if (lbl_8063E8FC) {
        fn_8000AE8C();
    }
}

// "main"
void fn_80006A84(void) {
    fn_80055D94();
}

void main(void) {
    u8 *var1, *var2;
    u32 var3, var4;
    struct UnkStruct1 var5;
    u32 var6, taskID;
    
    lbl_8063E8FC = 0;
    
    fn_80223BC8();
    GSmem::init();
    fn_80244A50();
    fn_8024575C();
    
    // TODO consider inline function(s)
    var1 = (u8 *)OSGetMEM1ArenaLo();
    var2 = (u8 *)OSGetMEM1ArenaHi();
    var3 = var2 - var1 - 0x100000;
    if (var3 > 0x1500000) {
        var3 = 0x1500000;
    }
    lbl_8063E8E8 = GSmem::createHeap(var1, var3, 4);
    OSSetMEM1ArenaLo(var1 + var3);

    var1 = (u8 *)OSGetMEM1ArenaLo();
    var2 = (u8 *)OSGetMEM1ArenaHi();
    var3 = var2 - var1;
    if (var3 > 0x100000) {
        var3 = 0x100000;
    }
    lbl_8063E8F8 = GSmem::createHeap(var1, var3, 4);
    OSSetMEM1ArenaLo(var1 + var3);

    var1 = (u8 *)OSGetMEM2ArenaLo();
    var2 = (u8 *)OSGetMEM2ArenaHi();
    var3 = var2 - var1;
    if (var3 > 0xc00000) {
        var3 = 0xc00000;
    }
    lbl_8063E8F0 = GSmem::createHeap(var1, var3, 4);
    OSSetMEM2ArenaLo(var1 + var3);

    var1 = (u8 *)OSGetMEM2ArenaLo();
    var2 = (u8 *)OSGetMEM2ArenaHi();
    var3 = var2 - var1;
    if (var3 > 0x100000) {
        var3 = 0x100000;
    }
    lbl_8063E8F4 = GSmem::createHeap(var1, var3, 4);
    OSSetMEM2ArenaLo(var1 + var3);

    var1 = (u8 *)OSGetMEM2ArenaLo();
    var2 = (u8 *)OSGetMEM2ArenaHi();
    var3 = var2 - var1;
    lbl_8063E8EC = GSmem::createHeap(var1, var3, 4);
    OSSetMEM2ArenaLo(var1 + var3);

    GSmem::setDefaultHeap(lbl_8063E8E8);

    var4 = 0xC000;
    fn_80249BF0(var4);
    fn_80249BA0(var4 - 0x4000, 2);
    fn_801DB978(0);

    GStask::init(32, 4);
    
    fn_801DB15C(0x190);
    var5._16 = 1;
    var5._17 = 1;
    var5._8 = 0x100000;
    var5._C = 0x10;
    var5._10 = 0x20;
    var5._4 = 0;
    var5._0 = 2;
    var5._2 = 0x1e0;
    var5._14 = 0x80;
    new UnkClass1(0x20);
    fn_802353F8(&var5);
    fn_80237794(lbl_8063F698, 0);

    VIEnableDimming(TRUE);
    VISetTimeToDimming(VI_DM_10M);

    fn_8024483C(2);

    taskID = GStask::createTask(TASK_TYPE_MAIN, 0, 0, fn_80006980);
    GStask::setTaskName(taskID, "main render");
    taskID = GStask::createTask(TASK_TYPE_MAIN, 1, 0, fn_80006A00);
    GStask::setTaskName(taskID, "input");
    taskID = GStask::createTask(TASK_TYPE_MAIN, 0x80, 0, fn_80006A84);
    GStask::setTaskName(taskID, "main");

    GSthread::init(32);

    fn_802247C8(0x20);

    OSSetPowerCallback(fn_80007338);
    OSSetResetCallback(fn_800072C4);

    fn_8005925C(0);

    GSthreadManager::sInstance->createThread(
        1,
        fn_80006A88,
        NULL,
        0x4000,
        0,
        OS_THREAD_ATTR_DETACH
    );

    fn_80059208();
    
    while (1) {
        if (lbl_8063E8FF) {
            lbl_8063E8FF = 0;
            OSSetResetCallback(fn_800072C4);
        }
        if (lbl_8063E8FE) {
            fn_800071F8();
        }
        if (lbl_8063E900) {
            fn_80007260();
        }
        GStask::runMainTasks();
    }
}
