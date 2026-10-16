// From doldecomp/ogws (CC0), include/revolution/NWC24/NWC24MsgCommit.h
#ifndef RVL_SDK_NWC24_MSG_COMMIT_H
#define RVL_SDK_NWC24_MSG_COMMIT_H
#include <private/nwc24_ogws/NWC24Types.h>

#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct NWC24MsgObj NWC24MsgObj;

NWC24Err NWC24CommitMsg(NWC24MsgObj *pMsg);

#ifdef __cplusplus
}
#endif
#endif
