#include ".unsorted/8004E9F0.hpp"
#include ".unsorted/80050324.hpp"

#include "common.hpp"

extern "C" {

// Thunk adjusting the object pointer to the sub-object at 0x14
void fn_8004ECD8(u8 *p) { fn_80050BE0(p + 0x14); }

u8 fn_8004EE68(const u8 *p) { return *p; }

}
