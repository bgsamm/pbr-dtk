// From doldecomp/ogws (CC0), include/revolution/NWC24/internal/NWC24iSecretFList.h
#ifndef RVL_SDK_NWC24_INTERNAL_SECRET_FRIEND_LIST_H
#define RVL_SDK_NWC24_INTERNAL_SECRET_FRIEND_LIST_H
#include <private/nwc24_ogws/NWC24Types.h>

#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct NWC24iSecretFLHeader {
    u32 magic;   // at 0x0
    u32 version; // at 0x4
    u8 UNK_0x8[0x800 - 0x8];
} NWC24iSecretFLHeader;

NWC24Err NWC24iOpenSecretFriendList(void);

#ifdef __cplusplus
}
#endif
#endif
