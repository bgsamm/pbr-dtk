#include "global.hpp"

#include "gs/GSinput.hpp"

void GSinput::fn_802448E8(GSinputUnkStruct5 *param1) {
    param1->_8 = NULL;
    param1->_C = NULL;
    param1->_0 = 0f;
    param1->_5 = false;
}

void GSinput::fn_80244904(GSinputUnkStruct5 *param1, f32 param2) {
    param1->_5 = false;

    if (param1->_C == NULL) {
        return;
    }

    if (param1->_0 > 0f) {
        param1->_0 -= param2;
    }

    if (param1->_0 <= 0) {
        switch ((param1->_C->_0 & 0xf0)) {
            case 0:
                param1->_4 = param1->_C->_0 & 0x3;
                param1->_0 = ((param1->_C->_1 << 8) | param1->_C->_2) / 4096f;
                param1->_C++;
                break;
            
            case 0x10:
                param1->_C = param1->_8;
                break;
            
            case 0x20:
                param1->_4 = 0;
                param1->_C = NULL;
                break;
            
            default:
                param1->_4 = 0;
                param1->_C = NULL;
                break;
        }

        param1->_5 = true;
    }
}
