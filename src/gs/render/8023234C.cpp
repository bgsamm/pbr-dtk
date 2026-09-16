#include "gs/GSmem.hpp"
#include "gs/GSrender.hpp"

#include <cstring>
#include <revolution/gx.h>
#include <revolution/os.h>

#include "version.hpp"

// BreakPtCallback
void fn_8023234C() {
    if (GSrender::getInstance() == NULL) {
        return;
    }

    u8 var1 = GSrender::getInstance()->get_16f9();
    GSrender::getInstance()->set_16f9(false);
    GXDisableBreakPt();
    GSrender::getInstance()->set_16f9(var1);
}

// DrawDoneCallback
void fn_80232394() {
    if (GSrender::getInstance() == NULL) {
        return;
    }

    u8 var1 = GSrender::getInstance()->get_16f9();
    GSrender::getInstance()->set_16f9(false);

    GSrenderStruct2 *var2;
    while ((var2 = GSrender::getInstance()->fn_802324F0()) != 0) {
        if (var2->_0 != NULL) {
            var2->_0(var2->_4);
        }
    }
    GSrender::getInstance()->set_16f9(var1);
}

u32 GSrender::fn_80232404(_UnkRenderFunc_1 param1, void *param2) {
    GSrenderStruct2 *var1 = fn_8023246C();
    var1->_0 = param1;
    var1->_4 = param2;
    var1->_8 = fn_8023B948(param2);

    GXSetDrawDone();

    return var1->_8;
}

GSrenderStruct2 *GSrender::fn_8023246C() {
    BOOL intEnabled = OSDisableInterrupts();

    GSrenderStruct2 *var1 = mGraphicsFifo._a4;
    mGraphicsFifo._a4 = var1->_c;
    var1->_c = NULL;
    var1->_0 = 0;
    var1->_4 = NULL;

    GSrenderStruct2 *var2 = mGraphicsFifo._a0;
    if (var2 != NULL) {
        while (var2->_c != NULL) {
            var2 = var2->_c;
        }
        var2->_c = var1;
    } else {
        mGraphicsFifo._a0 = var1;
    }

    OSRestoreInterrupts(intEnabled);
    return var1;
}

GSrenderStruct2 *GSrender::fn_802324F0() {
    GSrenderStruct2 *var1 = mGraphicsFifo._a0;
    if (var1 == NULL || fn_8023B864(var1->_8) == 0) {
        return NULL;
    }

    mGraphicsFifo._a0 = var1->_c;
    var1->_c = mGraphicsFifo._a4;
    mGraphicsFifo._a4 = var1;

    return var1;
}

void GSrender::fn_80232770() {
    GXSetCPUFifo(NULL);
    GXSetGPFifo(NULL);

    if (mGraphicsFifo._a8 != NULL) {
        GSmem::free(mGraphicsFifo._a8);
    }

    if (mGraphicsFifo._88 != NULL) {
        GSmem::free(mGraphicsFifo._88);
    }

    memset(&mGraphicsFifo, 0, 0xac);
}

void GSrender::fn_802327E8() {
    fn_8023B6BC();
    fn_8023FD64();
}
