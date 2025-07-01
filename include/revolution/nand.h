#ifndef NAND_H
#define NAND_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NAND_RESULT_OK                0 
#define NAND_RESULT_ACCESS         (-1)
#define NAND_RESULT_ALLOC_FAILED   (-2)
#define NAND_RESULT_BUSY           (-3)
#define NAND_RESULT_CORRUPT        (-4)
#define NAND_RESULT_ECC_CRIT       (-5)
#define NAND_RESULT_EXISTS         (-6)
#define NAND_RESULT_INVALID        (-8)
#define NAND_RESULT_MAXBLOCKS      (-9)
#define NAND_RESULT_MAXFD          (-10)
#define NAND_RESULT_MAXFILES       (-11)
#define NAND_RESULT_NOEXISTS       (-12)
#define NAND_RESULT_NOTEMPTY       (-13)
#define NAND_RESULT_OPENFD         (-14)
#define NAND_RESULT_AUTHENTICATION (-15)
#define NAND_RESULT_MAXDEPTH       (-16)
#define NAND_RESULT_UNKNOWN        (-64)
#define NAND_RESULT_FATAL_ERROR   (-128)

#define NAND_SEEK_SET          0
#define NAND_SEEK_CUR          1
#define NAND_SEEK_END          2

#define NAND_ACCESS_READ       0x01
#define NAND_ACCESS_WRITE      0x02
#define NAND_ACCESS_RW         (NAND_ACCESS_READ | NAND_ACCESS_WRITE)

#define NAND_PERM_OTHER_READ   0x01
#define NAND_PERM_OTHER_WRITE  0x02
#define NAND_PERM_GROUP_READ   0x04
#define NAND_PERM_GROUP_WRITE  0x08
#define NAND_PERM_OWNER_READ   0x10
#define NAND_PERM_OWNER_WRITE  0x20

// size: 0x8c
typedef struct NANDFileInfo
{
    s32  fileDescriptor;
    s32  origFd;
    char origPath[64];
    char tmpPath[64];
    u8   accType;
    u8   stage;
    u8   mark;
} NANDFileInfo;

typedef struct NANDCommandBlock {
    void *userData;
    void *callback;
    void *fileInfo;
    void *bytes;
    void *inodes;
    void *status;
    u32 ownerId;
    u16 groupId;
    u8  nextStage;
    u32 attr;
    u32 ownerAcc;
    u32 groupAcc;
    u32 othersAcc;
    u32 num;
    char absPath[64];
    u32 *length;
    u32 *pos;
    int state;
    void *copyBuf;
    u32 bufLength;
    u8 *type;
    u32 uniqNo;
    u32 reqBlocks;
    u32 reqInodes;
    u32 *answer;
    u32 homeBlocks;
    u32 homeInodes;
    u32 userBlocks;
    u32 userInodes;
    u32 workBlocks;
    u32 workInodes;
    const char **dir;
    BOOL simpleFlag;
} NANDCommandBlock;

typedef void (*NANDCallback)(s32 result, NANDCommandBlock *block);

s32 NANDCreate(const char *filename, u8 perm, u8 attr);
s32 NANDRead(NANDFileInfo *info, void *buf, u32 length);
s32 NANDReadAsync(NANDFileInfo *info, void *buf, u32 length, NANDCallback cb, NANDCommandBlock *block);
s32 NANDWrite(NANDFileInfo *info, const void *buf, u32 length);
s32 NANDSeek(NANDFileInfo *info, s32 offset, s32 whence);
s32 NANDSeekAsync(NANDFileInfo *info, s32 offset, s32 whence, NANDCallback cb, NANDCommandBlock *block);
s32 NANDGetLength(NANDFileInfo *info, u32 *length);
void NANDSetUserData(NANDCommandBlock *block, void *data);
void* NANDGetUserData(const NANDCommandBlock *block);
s32 NANDOpen(const char *path, NANDFileInfo *info, u8 accType);
s32 NANDClose(NANDFileInfo *info);

s32 NANDInit(void);

#ifdef __cplusplus
}
#endif

#endif // NAND_H
