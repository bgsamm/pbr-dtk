#include ".unsorted/80376F7C.hpp"

#include "common.hpp"

extern "C" {

void detail_FreeAmbientArg__Q34nw4r3snd14Sound3DManagerFPvPCQ44nw4r3snd6detail10BasicSound(
    u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7); // nw4r::snd::Sound3DManager::detail_FreeAmbientArg
void detail_AllocAmbientArg__Q34nw4r3snd14Sound3DManagerFUl(
    u32 a0,
    u32 a1,
    u32 a2,
    u32 a3,
    u32 a4,
    u32 a5,
    u32 a6,
    u32 a7); // nw4r::snd::Sound3DManager::detail_AllocAmbientArg

void fn_80376F7C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    detail_FreeAmbientArg__Q34nw4r3snd14Sound3DManagerFPvPCQ44nw4r3snd6detail10BasicSound(a0 - 0x4,
                                                                                          a1,
                                                                                          a2,
                                                                                          a3,
                                                                                          a4,
                                                                                          a5,
                                                                                          a6,
                                                                                          a7);
}
void fn_80376F84(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    detail_AllocAmbientArg__Q34nw4r3snd14Sound3DManagerFUl(a0 - 0x4, a1, a2, a3, a4, a5, a6, a7);
}
}
