// Imported from SMGCommunity/Petari (CC0), src/MetroTRK/debugger/embedded/MetroTRK/Portable/msg.c
/**
 * msg.c
 * Description:
 */

#include "MetroTRK/Portable/msg.h"
#include "trk.h"

DSError TRKMessageSend(TRK_Msg* msg) {
    DSError write_err = TRKWriteUARTN(&msg->m_msg, msg->m_msgLength);
    return DS_NoError;
}
