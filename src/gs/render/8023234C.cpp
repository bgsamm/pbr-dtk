#include "global.hpp"

#include <cstring>
#include <revolution/gx.h>
#include <revolution/os.h>

#include "gs/GSmem.hpp"
#include "gs/GSrender.hpp"

// BreakPtCallback
void fn_8023234C() {
    if (GSrenderManager::sInstance == NULL) {
        return;
    }

    u8 var1 = GSrenderManager::sInstance->_16f9;
    GSrenderManager::sInstance->_16f9 = 0;
    GXDisableBreakPt();
    GSrenderManager::sInstance->_16f9 = var1;
}

// DrawDoneCallback
void fn_80232394() {
    if (GSrenderManager::sInstance == NULL) {
        return;
    }

    u8 var1 = GSrenderManager::sInstance->_16f9;
    GSrenderManager::sInstance->_16f9 = 0;

    GSrenderStruct2 *var2;
    while ((var2 = GSrenderManager::sInstance->fn_802324F0()) != 0) {
        if (var2->_0 != NULL) {
            var2->_0(var2->_4);
        }
    }
    GSrenderManager::sInstance->_16f9 = var1;
}

u32 GSrenderManager::fn_80232404(UnkFunc1 param1, void *param2) {
    GSrenderStruct2 *var1 = fn_8023246C();
    var1->_0 = param1;
    var1->_4 = param2;
    var1->_8 = fn_8023B948(param2);

    GXSetDrawDone();

    return var1->_8;
}

GSrenderStruct2 *GSrenderManager::fn_8023246C() {
    BOOL intEnabled = OSDisableInterrupts();

    GSrenderStruct2 *var1 = _163c._a4;
    _163c._a4 = var1->_c;
    var1->_c = NULL;
    var1->_0 = 0;
    var1->_4 = NULL;

    GSrenderStruct2 *var2 = _163c._a0;
    if (var2 != NULL) {
        while (var2->_c != NULL) {
            var2 = var2->_c;
        }
        var2->_c = var1;
    }
    else {
        _163c._a0 = var1;
    }

    OSRestoreInterrupts(intEnabled);
    return var1;
}

GSrenderStruct2 *GSrenderManager::fn_802324F0() {
    GSrenderStruct2 *var1 = _163c._a0;
    if (var1 == NULL || fn_8023B864(var1->_8) == 0) {
        return NULL;
    }

    _163c._a0 = var1->_c;
    var1->_c = _163c._a4;
    _163c._a4 = var1;

    return var1;
}

void GSrenderManager::fn_80232770() {
    GXSetCPUFifo(NULL);
    GXSetGPFifo(NULL);

    if (_163c._a8 != NULL) {
        GSmem::free(_163c._a8);
    }

    if (_163c._88 != NULL) {
        GSmem::free(_163c._88);
    }

    memset(&_163c, 0, 0xac);
}

void GSrenderManager::fn_802327E8() {
    fn_8023B6BC();
    fn_8023FD64();
}
