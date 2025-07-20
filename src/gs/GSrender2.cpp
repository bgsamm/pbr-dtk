#include "version.hpp"
#include <cstring>

#include <revolution/gx.h>
#include <revolution/os.h>

#include "gs/GSmem.hpp"
#include "gs/GSrender.hpp"
#include "gs/GSrender2.hpp"

extern GSrender *lbl_8063F698;



// BreakPtCallback
void fn_8023234C() {
    if (lbl_8063F698 == NULL) {
        return;
    }

    u8 var1 = lbl_8063F698->_16f9;
    lbl_8063F698->_16f9 = 0;
    GXDisableBreakPt();
    lbl_8063F698->_16f9 = var1;
}

// DrawDoneCallback
void fn_80232394() {
    if (lbl_8063F698 == NULL) {
        return;
    }

    u8 var1 = lbl_8063F698->_16f9;
    lbl_8063F698->_16f9 = 0;

    UnkStruct2 *var2;
    while ((var2 = lbl_8063F698->fn_802324F0()) != 0) {
        if (var2->_0 != NULL) {
            var2->_0(var2->_4);
        }
    }
    lbl_8063F698->_16f9 = var1;
}

u32 GSrender::fn_80232404(UnkFunc1 param1, u32 param2) {
    UnkStruct2 *var1 = fn_8023246C();
    var1->_0 = param1;
    var1->_4 = param2;
    var1->_8 = fn_8023B948(param2);

    GXSetDrawDone();

    return var1->_8;
}

UnkStruct2 *GSrender::fn_8023246C() {
    BOOL intEnabled = OSDisableInterrupts();

    UnkStruct2 *var1 = _163c._16e0;
    _163c._16e0 = var1->_c;
    var1->_c = NULL;
    var1->_0 = 0;
    var1->_4 = 0;

    UnkStruct2 *var2 = _163c._16dc;
    if (var2 != NULL) {
        while (var2->_c != NULL) {
            var2 = var2->_c;
        }
        var2->_c = var1;
    }
    else {
        _163c._16dc = var1;
    }

    OSRestoreInterrupts(intEnabled);
    return var1;
}

UnkStruct2 *GSrender::fn_802324F0() {
    UnkStruct2 *var1 = _163c._16dc;
    if (var1 == NULL || fn_8023B864(var1->_8) == 0) {
        return NULL;
    }

    _163c._16dc = var1->_c;
    var1->_c = _163c._16e0;
    _163c._16e0 = var1;

    return var1;
}

void GSrender::fn_80232770() {
    GXSetCPUFifo(NULL);
    GXSetGPFifo(NULL);

    if (_163c._16e4 != NULL) {
        GSmem::free(_163c._16e4);
    }

    if (_163c._16c4 != NULL) {
        GSmem::free(_163c._16c4);
    }

    memset(&_163c, 0, 0xac);
}
