#include <revolution/types.h>

#include "gs/GSmem.hpp"

void main(void) {
    // u8 *var1, *var2;
    // u32 var3, var4;
    // struct UnkStruct1 var5;
    // u32 var6, var7;
    
    // lbl_8063E8FC = 0;
    
    // fn_80223BC8();
    GSmem::init();
    // fn_80244A50();
    // fn_8024575C();
    
    // var1 = OSGetMEM1ArenaLo();
    // var2 = OSGetMEM1ArenaHi();
    // var3 = var2 - var1 - 0x100000;
    // if (var3 > 0x1500000) {
    //     var3 = 0x1500000;
    // }
    // lbl_8063E8E8 = fn_801DAB78(var1, var3, 4);
    // OSSetMEM1ArenaLo(var1 + var3);

    // var1 = OSGetMEM1ArenaLo();
    // var2 = OSGetMEM1ArenaHi();
    // var3 = var2 - var1;
    // if (var3 > 0x100000) {
    //     var3 = 0x100000;
    // }
    // lbl_8063E8F8 = fn_801DAB78(var1, var3, 4);
    // OSSetMEM1ArenaLo(var1 + var3);

    // var1 = OSGetMEM2ArenaLo();
    // var2 = OSGetMEM2ArenaHi();
    // var3 = var2 - var1;
    // if (var3 > 0xc00000) {
    //     var3 = 0xc00000;
    // }
    // lbl_8063E8F0 = fn_801DAB78(var1, var3, 4);
    // OSSetMEM2ArenaLo(var1 + var3);

    // var1 = OSGetMEM2ArenaLo();
    // var2 = OSGetMEM2ArenaHi();
    // var3 = var2 - var1;
    // if (var3 > 0x100000) {
    //     var3 = 0x100000;
    // }
    // lbl_8063E8F4 = fn_801DAB78(var1, var3, 4);
    // OSSetMEM2ArenaLo(var1 + var3);

    // var1 = OSGetMEM2ArenaLo();
    // var2 = OSGetMEM2ArenaHi();
    // var3 = var2 - var1;
    // lbl_8063E8EC = fn_801DAB78(var1, var3, 4);
    // OSSetMEM2ArenaLo(var1 + var3);

    // fn_801DAC14(lbl_8063E8E8);
    // var4 = 0xC000;
    // fn_80249BF0(var4);
    // fn_80249BA0(var4 - 0x4000, 2);
    // fn_801DB978(0);
    // fn_80223F0C(0x20, 4);
    // fn_801DB15C(0x190);
    // var5._16 = 1;
    // var5._17 = 1;
    // var5._8 = 0x100000;
    // var5._C = 0x10;
    // var5._10 = 0x20;
    // var5._4 = 0;
    // var5._0 = 2;
    // var5._2 = 0x1e0;
    // var5._14 = 0x80;
    // var6 = fn_801DAA30(0x2c);
    // if (var6) {
    //     fn_801FA38C(var6, 0x20);
    // }
    // fn_802353F8(&var5);
    // fn_80237794(lbl_8063F698, 0);
    // VIEnableDimming(1);
    // VISetTimeToDimming(1);
    // fn_8024483C(2);
    // var7 = fn_80223FD0(1, 0, 0, fn_80006980);
    // fn_8022408C(var7, "main render");
    // var7 = fn_80223FD0(1, 1, 0, fn_80006A00);
    // fn_8022408C(var7, "input");
    // var7 = fn_80223FD0(1, 0x80, 0, fn_80006A84);
    // fn_8022408C(var7, "main");
    // fn_8022410C(0x20);
    // fn_802247C8(0x20);
    // OSSetPowerCallback(fn_80007338);
    // OSSetResetCallback(fn_800072C4);
    // fn_8005925C(0);
    // fn_80224214(lbl_8063F600, 1, fn_80006A88, 0, 0x4000, 0, 1);
    // fn_80059208();
    
    // while (1) {
    //     if (lbl_8063E8FF) {
    //         lbl_8063E8FF = 0;
    //         OSSetResetCallback(fn_800072C4);
    //     }
    //     if (lbl_8063E8FE) {
    //         fn_800071F8();
    //     }
    //     if (lbl_8063E900) {
    //         fn_80007260();
    //     }
    //     fn_8022406C();
    // }
}
