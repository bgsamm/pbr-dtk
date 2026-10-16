// Imported from doldecomp/ogws (CC0), src/nw4r/snd/snd_StrmSound.cpp
// TODO Functions of the binary not in this source yet: fn_8037F6E0, fn_8037F7D8, fn_8037F8C0, fn_8037F8D4, fn_8037F8DC
// and fn_8037F8E4.
#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {

NW4R_UT_RTTI_DEF_DERIVED(StrmSound, BasicSound);

StrmSound::StrmSound(SoundInstanceManager<StrmSound> *pManager) : mManager(pManager), mTempSpecialHandle(NULL) {}

bool StrmSound::Prepare(
    StrmBufferPool *pPool, StrmPlayer::StartOffsetType offsetType, s32 offset, int voices, ut::FileStream *pStream) {
    if (pPool == NULL) {
        return false;
    }

    InitParam();

    if (!mStrmPlayer.Setup(pPool)) {
        return false;
    }

    if (!mStrmPlayer.Prepare(pStream, voices, offsetType, offset)) {
        mStrmPlayer.Shutdown();
        return false;
    }

    return true;
}

void StrmSound::Shutdown() {
    BasicSound::Shutdown();
    mManager->Free(this);
}

void StrmSound::SetPlayerPriority(int priority) {
    BasicSound::SetPlayerPriority(priority);
    mManager->UpdatePriority(this, CalcCurrentPlayerPriority());
}

bool StrmSound::IsAttachedTempSpecialHandle() {
    return mTempSpecialHandle != NULL;
}

void StrmSound::DetachTempSpecialHandle() {
    mTempSpecialHandle->DetachSound();
}

} // namespace detail
} // namespace snd
} // namespace nw4r
