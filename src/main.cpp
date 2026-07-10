#include "version.hpp"

#include <revolution/types.h>
#include <revolution/os.h>
#include <revolution/vi.h>

#include "gs/GScache.hpp"
#include "gs/GSfsys.hpp"
#include "gs/GSinput.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSmem.hpp"
#include "gs/GStask.hpp"
#include "gs/GSthread.hpp"
#include "gs/GStimeline.hpp"
#include "gs/GSvideo.hpp"
#include "wip/80249BA0.hpp"
#include "wip/80249BF0.hpp"

void fn_80006980(u32, void *);
void fn_80006A00(u32, void *);
void fn_80006A84(u32, void *);
void *fn_80006A88(void *);
void *fn_80006FD4(void *);
void fn_80007090(GSdvdError);
void fn_80007164();
void fn_800071F8();
void fn_80007260();
void fn_800072C4();
void fn_80007338();

void fn_8000748C();
void fn_8000A73C();
void fn_8000A77C();
void fn_8000A790();
void fn_8000AC94();
void fn_8000ADC0(char *, MEMHeapHandle);
void fn_8000AE8C();
void fn_8000AEB0(u8);
void fn_8000C764();
void fn_8000C7E8();
void fn_80055D94();
u8 fn_80058B10(bool);
void fn_80059208();
bool fn_8005924C();
void fn_8005925C(u32);
void fn_8015D3D0();
void fn_80162F48(MEMHeapHandle);
void fn_8021C274(u32);
void fn_80231490(void *, f32);
void fn_80231544(void *);
void fn_802353F8(void *);
void fn_80237794(void *, u32);

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

extern GSfsysFileTypeHandler *lbl_8044E828;

MEMHeapHandle lbl_8063E8E8;
MEMHeapHandle lbl_8063E8EC;
MEMHeapHandle lbl_8063E8F0;
MEMHeapHandle lbl_8063E8F4;
MEMHeapHandle lbl_8063E8F8;
u8 lbl_8063E8FC;
u8 lbl_8063E8FE;
u8 lbl_8063E8FF;
u8 lbl_8063E900;

u32 lbl_8063F600;
void *lbl_8063F698;

// "main render"
void fn_80006980(void) {
    u8 refreshRate;
    f32 var2;

    refreshRate = GSvideoManager::sInstance->mRefreshRate;
    var2 = GSvideoManager::sInstance->fn_8023FFEC() / refreshRate;

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

void *fn_80006A88(void *param1) {
    OSInitFastCast();
    
    GSfile::setErrorCallbacks(fn_80007090, fn_80007164);
    GSfsys::init(0x40, 0, 0, 0);
    GSfsys::setFileTypeHandlers(lbl_8044E828);
    fn_8005925C(1);

    while (!fn_8005924C()) {
        GSthreadManager::sInstance->sleepCurrentThread();
    }

    fn_80162F48(lbl_8063E8F4);
    fn_8021C274(0x20);
    fn_8000ADC0("sound/pbr_sound.brsar", lbl_8063E8F0);
    fn_8000AEB0(fn_80058B10(0));
    fn_8000C7E8();
    fn_8000C764();
    fn_8015D3D0();
    fn_8000A73C();
    // inline_func(lbl_8063F698, fn_8000A77C, fn_8000A790);
    // lbl_8063F698->_172C = fn_80058178;
    fn_8000AC94();
    fn_8000748C();
    GSthreadManager::sInstance->createThread(
        100,
        fn_80006FD4,
        NULL,
        0x4000,
        8,
        OS_THREAD_ATTR_DETACH
    );
    
    return 0;
}

void main(void) {
    u8 *var1, *var2;
    u32 var3, var4;
    struct UnkStruct1 var5;
    u32 var6, taskID;
    
    lbl_8063E8FC = 0;
    
    GSmath::init();
    GSmem::init();
    GSfsys::initFsysDataHeap();
    GSfsys::initFsysCacheHeap();
    
    // TODO consider inline function(s)
    var1 = (u8 *)OSGetMEM1ArenaLo();
    var2 = (u8 *)OSGetMEM1ArenaHi();
    var3 = var2 - var1 - 0x100000;
    if (var3 > 0x1500000) {
        var3 = 0x1500000;
    }
    lbl_8063E8E8 = GSmem::createHeap(var1, var3, MEM_HEAP_OPT_THREAD_SAFE);
    OSSetMEM1ArenaLo(var1 + var3);

    var1 = (u8 *)OSGetMEM1ArenaLo();
    var2 = (u8 *)OSGetMEM1ArenaHi();
    var3 = var2 - var1;
    if (var3 > 0x100000) {
        var3 = 0x100000;
    }
    lbl_8063E8F8 = GSmem::createHeap(var1, var3, MEM_HEAP_OPT_THREAD_SAFE);
    OSSetMEM1ArenaLo(var1 + var3);

    var1 = (u8 *)OSGetMEM2ArenaLo();
    var2 = (u8 *)OSGetMEM2ArenaHi();
    var3 = var2 - var1;
    if (var3 > 0xc00000) {
        var3 = 0xc00000;
    }
    lbl_8063E8F0 = GSmem::createHeap(var1, var3, MEM_HEAP_OPT_THREAD_SAFE);
    OSSetMEM2ArenaLo(var1 + var3);

    var1 = (u8 *)OSGetMEM2ArenaLo();
    var2 = (u8 *)OSGetMEM2ArenaHi();
    var3 = var2 - var1;
    if (var3 > 0x100000) {
        var3 = 0x100000;
    }
    lbl_8063E8F4 = GSmem::createHeap(var1, var3, MEM_HEAP_OPT_THREAD_SAFE);
    OSSetMEM2ArenaLo(var1 + var3);

    var1 = (u8 *)OSGetMEM2ArenaLo();
    var2 = (u8 *)OSGetMEM2ArenaHi();
    var3 = var2 - var1;
    lbl_8063E8EC = GSmem::createHeap(var1, var3, MEM_HEAP_OPT_THREAD_SAFE);
    OSSetMEM2ArenaLo(var1 + var3);

    GSmem::setDefaultHeap(lbl_8063E8E8);

    var4 = 0xC000;
    GSunk::fn_80249BF0(var4);
    GSunk::fn_80249BA0(var4 - 0x4000, 2);

    GScache::fn_801DB978(0);

    GStask::init(32, 4);
    
    GScache::initFileCache(400);

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

    GSinput::init(2);

    taskID = GStask::createTask(TASK_TYPE_MAIN, 0, NULL, fn_80006980);
    GStask::setTaskName(taskID, "main render");
    taskID = GStask::createTask(TASK_TYPE_MAIN, 1, NULL, fn_80006A00);
    GStask::setTaskName(taskID, "input");
    taskID = GStask::createTask(TASK_TYPE_MAIN, 128, NULL, fn_80006A84);
    GStask::setTaskName(taskID, "main");

    GSthread::init(32);
    GStimeline::init(32);

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
