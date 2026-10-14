#include ".unsorted/8037F5B0.hpp"

#include "common.hpp"

extern "C" {

void OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv(
    u32 a0,
    u32 a1,
    u32 a2,
    u32 a3,
    u32 a4,
    u32 a5,
    u32 a6,
    u32 a7); // nw4r::snd::detail::StrmPlayer::OnShutdownSoundThread
void fn_8037D464(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8037F5B0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv(a0 - 0x74, a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037F5C8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8037D464(a0 - 0x74, a1, a2, a3, a4, a5, a6, a7);
}
}
