#include ".unsorted/8037A8AC.hpp"

#include "common.hpp"

extern "C" {

void ConvertLabelStringToSoundId__Q34nw4r3snd12SoundArchiveCFPCc(
    u32 a0,
    u32 a1,
    u32 a2,
    u32 a3,
    u32 a4,
    u32 a5,
    u32 a6,
    u32 a7); // nw4r::snd::SoundArchive::ConvertLabelStringToSoundId
void detail_SetupSound__Q34nw4r3snd18SoundArchivePlayerFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerbPCQ44nw4r3snd14SoundStartable9StartInfo(
    u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7); // nw4r::snd::SoundArchivePlayer::detail_SetupSound
void __dt__Q34nw4r3snd18SoundArchivePlayerFv(u32 a0,
                                             u32 a1,
                                             u32 a2,
                                             u32 a3,
                                             u32 a4,
                                             u32 a5,
                                             u32 a6,
                                             u32 a7); // nw4r::snd::SoundArchivePlayer::~SoundArchivePlayer

void fn_8037A8AC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    ConvertLabelStringToSoundId__Q34nw4r3snd12SoundArchiveCFPCc(*(u32 *)(a0 + 0x10), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037A914(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    detail_SetupSound__Q34nw4r3snd18SoundArchivePlayerFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerbPCQ44nw4r3snd14SoundStartable9StartInfo(
        a0 - 0xc,
        a1,
        a2,
        a3,
        a4,
        a5,
        a6,
        a7);
}
void fn_8037A91C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    __dt__Q34nw4r3snd18SoundArchivePlayerFv(a0 - 0xc, a1, a2, a3, a4, a5, a6, a7);
}
}
