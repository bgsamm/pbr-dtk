// From doldecomp/ogws (CC0), include/revolution/NWC24/internal/NWC24iManage.h
#ifndef RVL_SDK_NWC24_INTERNAL_MANAGE_H
#define RVL_SDK_NWC24_INTERNAL_MANAGE_H
#include <private/nwc24_ogws/NWC24Mime.h>
#include <private/nwc24_ogws/NWC24Types.h>
#include <private/nwc24_ogws/internal/NWC24iConfig.h>
#include <private/nwc24_ogws/internal/NWC24iDownload.h>
#include <private/nwc24_ogws/internal/NWC24iFriendList.h>
#include <private/nwc24_ogws/internal/NWC24iMBoxCtrl.h>
#include <private/nwc24_ogws/internal/NWC24iSecretFList.h>

#include <private/macros.h>
#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NWC24i_IO_BUFFER_SIZE 512
#define NWC24i_STRING_WORK_SIZE 1024
#define NWC24i_PATH_WORK_SIZE 256

#define NWC24i_MANAGE_ERROR_CODE_BASE 109000
#define NWC24i_MSG_ERROR_CODE_BASE 109300

#define NWC24i_APP_ID_IPL FOURCC('H', 'A', 'E', 'A')

typedef enum NWC24iMsgArrivedFlags {
    NWC24_MSG_ARRIVED          = 1 << 0,
    NWC24_MSG_ARRIVED_FOR_MENU = 1 << 1,
} NWC24iMsgArrivedFlags;

#define ROUND_UP(x, align) (((x) + (align) - 1) & (-(align)))
#define WORK_SIZE(x) (ROUND_UP(sizeof(x), 0x100))
typedef struct NWC24iWork {
    char stringWork[NWC24i_STRING_WORK_SIZE]; // at 0x0
    char WORK_0x400[0x800 - 0x400];
    char pathWork[NWC24i_PATH_WORK_SIZE];  // at 0x800
    u8 readBuffer[NWC24i_IO_BUFFER_SIZE];  // at 0x900
    u8 writeBuffer[NWC24i_IO_BUFFER_SIZE]; // at 0xB00
    u8 config[WORK_SIZE(NWC24iConfig)];    // at 0xD00
    NWC24iMBCHeader sendCtrl;              // at 0x1100
    NWC24iMBCHeader recvCtrl;              // at 0x1180
    NWC24iMBCEntry mbcEntry;               // at 0x1200
    char WORK_0x1280[128];
    char base64Work[NWC24_BASE64_TABLE_SIZE]; // at 0x1300
    char WORK_0x1400[0x2400 - 0x1400];
    u8 flHeader[WORK_SIZE(NWC24iFLHeader)];             // at 0x2400
    u8 secretFlHeader[WORK_SIZE(NWC24iSecretFLHeader)]; // at 0x2800
    u8 dlHeader[WORK_SIZE(NWC24iDlHeader)];             // at 0x3000
    u8 dlTask[WORK_SIZE(NWC24iDlTask)];                 // at 0x3800
    u8 padding[0x4000 - 0x3A00];
} NWC24iWork;
#undef WORK_SIZE

extern NWC24iWork *NWC24WorkP;

void NWC24iRegister(void);
NWC24Err NWC24iSetNewMsgArrived(u32 flags);
void NWC24iSetErrorCode(u32 code);

#ifdef __cplusplus
}
#endif
#endif
