#pragma once

#include <revolution/types.h>

struct Bag;
struct Pokemon;

#define FS_OVERLAY_ID_NONE -1

struct ApplicationManager;

typedef BOOL (*OverlayFunc)(ApplicationManager *appMan, s32 *state);

// size: 0x10
struct ApplicationManagerTemplate {
    /* 0x0 */ OverlayFunc init;
    /* 0x4 */ OverlayFunc main;
    /* 0x8 */ OverlayFunc exit;
    /* 0xC */ s32 overlayID;
};

// size: 0x28
struct ApplicationManager {
    /* 0x0 */ ApplicationManagerTemplate appTemplate;
    /* 0x10 */ s32 execState;
    /* 0x14 */ s32 procState;
    /* 0x18 */ void *args;
    /* 0x1C */ void *data;
    /* 0x20 */ ApplicationManager *parent;
    /* 0x24 */ ApplicationManager *child;
};

// size: 0x8 + 2 * maxSize
struct Strbuf {
    /* 0x0 */ u16 maxSize;
    /* 0x2 */ u16 size;
    /* 0x4 */ u32 integrity;
    /* 0x8 */ u16 data[1];
};

// size: 0x17C
struct FieldBattleDTO {
    /* 0x0 */ u32 battleType;
    /* 0x4 */ void *parties[4];
    /* 0x14 */ u32 _14;
    /* 0x18 */ u8 unk18[0xC0];
    /* 0xD8 */ void *trainerInfo[4];
    /* 0xE8 */ Bag *bag;
    /* 0xEC */ u32 _EC;
    /* 0xF0 */ u32 _F0;
    /* 0xF4 */ u8 unkF4[0x3C];
    /* 0x130 */ u32 _130;
    /* 0x134 */ u32 _134;
    /* 0x138 */ u8 unk138[0x8];
    /* 0x140 */ u32 _140;
    /* 0x144 */ u8 unk144[0x10];
    /* 0x154 */ u32 _154;
    /* 0x158 */ u8 unk158[0x14];
    /* 0x16C */ u32 _16C;
    /* 0x170 */ u8 unk170[0x4];
    /* 0x174 */ u32 _174;
    /* 0x178 */ u8 unk178[0x4];
};

Pokemon *Pokemon_New(u32 heapId);
void fn_803DEEA4();
void fn_803DEF70();
ApplicationManager *ApplicationManager_New(const ApplicationManagerTemplate *appTemplate, void *args, u32 heapId);
void ApplicationManager_Free(ApplicationManager *appMan);
void *ApplicationManager_Data(ApplicationManager *appMan);
void *ApplicationManager_Args(ApplicationManager *appMan);
BOOL ApplicationManager_Exec(ApplicationManager *appMan);
// TODO Returns the manager's procState; there is no such accessor in the DS games.
s32 fn_803DEE9C(ApplicationManager *appMan);
u32 Strbuf_Length(const Strbuf *str);
const u16 *Strbuf_GetData(const Strbuf *str);
