#ifndef PRIVATE_DVD_H
#define PRIVATE_DVD_H

#include <revolution/types.h>

#include <revolution/dvd.h>

#include <revolution/os/OSAlarm.h>

#include <revolution/esp.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DVD_DEVICE_CODE (1 << 15)

#define DVD_PRIVATE_PAD32(size) u8 CONCAT(padding, __LINE__)[OSRoundUp32B((size)) - (size)]

enum {
    DVD_INTTYPE_TC = (1 << 0),
    DVD_INTTYPE_DE = (1 << 1),
    DVD_INTTYPE_CVR = (1 << 2),
    DVD_INTTYPE_BR = (1 << 3),
    DVD_INTTYPE_TIME = (1 << 4),
    DVD_INTTYPE_SERR = (1 << 5),
    DVD_INTTYPE_VERR = (1 << 6),
    DVD_INTTYPE_ARGS = (1 << 7),
};

enum {
    DVD_COVER_BUSY = 0,
    DVD_COVER_OPENED,
    DVD_COVER_CLOSED,
};

#define DVD_DICVR_CVR (1 << 0)
#define DVD_DICVR_CVRINTMASK (1 << 1)
#define DVD_DICVR_CVRINT (1 << 2)

typedef struct DVDVideoReportKey {
    u8 data[32];
} DVDVideoReportKey;

typedef struct DVDGamePartition {
    ESTicket ticket;  // 0x00

    u32 tmdSize;       // 0x2A4
    ESTitleMeta* tmd;  // 0x2A8

    u32 certSize;  // 0x2AC
    void* cert;    // 0x2B0

    u8* h3Hash;         // 0x2B4
    u8* encryptedArea;  // 0x2B8
} DVDGamePartition;

typedef struct DVDPartitionInfo {
    DVDGamePartition* partition;  // 0x00
    u32 partitionType;            // 0x04
} DVDPartitionInfo;

typedef struct DVDGameTOC {
    u32 partitionCount;               // 0x00
    DVDPartitionInfo* partitionInfo;  // 0x04
} DVDGameTOC;

typedef struct DVDPartitionParams {
    ESTicket ticket;
    DVD_PRIVATE_PAD32(sizeof(ESTicket));
    ESTicketView ticketView;
    DVD_PRIVATE_PAD32(sizeof(ESTicketView));

    u32 numTmdBytes;
    DVD_PRIVATE_PAD32(sizeof(u32));
    ESTitleMeta tmd;
    DVD_PRIVATE_PAD32(sizeof(ESTitleMeta));

    u32 numCertBytes;
    DVD_PRIVATE_PAD32(sizeof(u32));
    u8 certificates[0x1000];

    u32 dataWordOffset;
    DVD_PRIVATE_PAD32(sizeof(u32));
    u8 h3Hash[0x18000];
} DVDPartitionParams;

typedef struct DVDBB2 {
    u32 bootFilePosition;  // 0x00

    u32 FSTPosition;   // 0x04
    u32 FSTLength;     // 0x08
    u32 FSTMaxLength;  // 0x0C
    void* FSTAddress;  // 0x10

    u32 userPosition;  // 0x14
    u32 userLength;    // 0x18

    u32 pad_0x1C;
} DVDBB2;

/* Low level broadway stuff */

BOOL DVDLowFinalize();
BOOL DVDLowInit();

BOOL DVDLowReadDiskID(DVDDiskID* diskID, DVDLowCallback callback);

BOOL DVDLowOpenPartition(u32 partitionWordOffset, const ESTicket* eTicket, u32 numCertBytes, const void* certificates, ESTitleMeta* tmd, DVDLowCallback callback);
BOOL DVDLowOpenPartitionWithTmdAndTicketView(u32 partitionWordOffset, ESTicketView* eTicketView, u32 numTmdBytes, ESTitleMeta* tmd, u32 numCertBytes,
                                             u8* certificates, DVDLowCallback callback);

BOOL DVDLowGetNoDiscBufferSizes(const u32 partitionWordOffset, u32* numTmdBytes, u32* numCertBytes, DVDLowCallback callback);
BOOL DVDLowGetNoDiscOpenPartitionParams(const u32 partitionWordOffset, ESTicket* eTicket, u32* numTmdBytes, ESTitleMeta* tmd, u32* numCertBytes,
                                        u8* certificates, u32* dataWordOffset, u8* h3HashPtr, DVDLowCallback callback);

BOOL DVDLowClosePartition(DVDLowCallback callback);
BOOL DVDLowUnencryptedRead(void* destAddr, u32 length, u32 wordOffset, DVDLowCallback callback);

BOOL DVDLowStopMotor(BOOL eject, BOOL saving, DVDLowCallback callback);
BOOL DVDLowInquiry(DVDDriveInfo* info, DVDLowCallback callback);

BOOL DVDLowRequestError(DVDLowCallback callback);

BOOL DVDLowSetSpinupFlag(BOOL enable);

BOOL DVDLowReset(DVDLowCallback callback);

BOOL DVDLowAudioBufferConfig(BOOL enable, u32 size, DVDLowCallback callback);
BOOL DVDLowSetMaximumRotation(u32 subcmd, DVDLowCallback callback);

BOOL DVDLowRead(void* destAddr, u32 length, u32 wordOffset, DVDLowCallback callback);
BOOL DVDLowSeek(u32 wordOffset, DVDLowCallback callback);

u32 DVDLowGetCoverRegister();
u32 DVDLowGetStatusRegister();
BOOL DVDLowPrepareCoverRegister(DVDLowCallback callback);
BOOL DVDLowPrepareStatusRegister(DVDLowCallback callback);

u32 DVDLowGetImmBufferReg();

BOOL DVDLowUnmaskStatusInterrupts();
BOOL DVDLowMaskCoverInterrupt();
BOOL DVDLowClearCoverInterrupt(DVDLowCallback callback);

s32 DVDLowGetLastEticketError();

BOOL __DVDLowTestAlarm(const OSAlarm* alarm);

/* Main stuff */

extern DVDCommandBlock __DVDStopMotorCommandBlock;

void __DVDAudioBufferConfig(DVDCommandBlock* block, u32 enable, u32 size, DVDCommandCallback callback);

s32 __DVDGetDriveStatus();
u32 __DVDGetCoverStatus();

BOOL __DVDGetCoverStatusAsync(DVDCommandBlock* block, DVDCommandCallback callback);

void __DVDPrepareResetAsync(DVDCommandCallback callback);
void __DVDPrepareReset();
void __DVDResetWithNoSpinup();

BOOL __DVDTestAlarm(OSAlarm* alarm);

BOOL __DVDStopMotorAsync(DVDCommandBlock* block, DVDCommandCallback callback);
void __DVDRestartMotor();

BOOL DVDOpenPartitionAsync(DVDCommandBlock* block, void* addr, u32 offset, DVDCommandCallback callback);
BOOL DVDClosePartitionAsync(DVDCommandBlock* block, DVDCommandCallback callback);
BOOL DVDUnencryptedReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length, u32 offset, DVDCommandCallback callback);
BOOL DVDDownRotationAsync(DVDCommandBlock* block, DVDCommandCallback callback);
BOOL DVDGetPartitionParamsAsync(DVDCommandBlock* block, DVDPartitionParams* params, u32 offset, DVDCommandCallback callback);
BOOL DVDOpenPartitionWithParamsAsync(DVDCommandBlock* block, DVDPartitionParams* params, u32 offset, DVDCommandCallback callback);

/* Error stuff */

void __DVDStoreErrorCode(u32 error, DVDErrorCallback callback);

/* File system stuff */

void __DVDFSInit();

/* Fatal stuff */

void __DVDShowFatalMessage();
void __DVDPrintFatalMessage();
BOOL __DVDGetAutoFatalMessaging();

/* Queue stuff */

void __DVDClearWaitingQueue();

DVDCommandBlock* __DVDPopWaitingQueue();
BOOL __DVDPushWaitingQueue(s32 prio, DVDCommandBlock* block);
BOOL __DVDDequeueWaitingQueue(DVDCommandBlock* block);

BOOL __DVDCheckWaitingQueue();

DVDCommandBlock* __DVDGetNextWaitingQueue();

#ifdef __cplusplus
}
#endif

#endif  // PRIVATE_DVD_H
