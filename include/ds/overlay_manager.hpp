#pragma once

#include <revolution/types.h>

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

ApplicationManager *ApplicationManager_New(const ApplicationManagerTemplate *appTemplate, void *args, u32 heapId);
void ApplicationManager_Free(ApplicationManager *appMan);
void *ApplicationManager_NewData(ApplicationManager *appMan, u32 size, u32 heapId);
void *ApplicationManager_Data(ApplicationManager *appMan);
void *ApplicationManager_Args(ApplicationManager *appMan);
BOOL ApplicationManager_Exec(ApplicationManager *appMan);
s32 fn_803DEE9C(ApplicationManager *appMan);
