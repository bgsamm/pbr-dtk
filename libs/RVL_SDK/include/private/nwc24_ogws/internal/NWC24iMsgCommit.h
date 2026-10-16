// From doldecomp/ogws (CC0), include/revolution/NWC24/internal/NWC24iMsgCommit.h
#ifndef RVL_SDK_NWC24_INTERNAL_MSG_COMMIT_H
#define RVL_SDK_NWC24_INTERNAL_MSG_COMMIT_H
#include <private/nwc24_ogws/NWC24Types.h>
#include <private/nwc24_ogws/internal/NWC24iMBoxCtrl.h>

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct NWC24iMsgObj NWC24iMsgObj;

NWC24Err NWC24CommitMsgInternal(NWC24iMsgObj *msg, NWC24MsgBoxId id);

#ifdef __cplusplus
}
#endif
#endif
