#include "ds/overlay_manager.hpp"

// TODO Replace with proper imports
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
}

ApplicationManager *ApplicationManager_New(const ApplicationManagerTemplate *appTemplate, void *args, u32 heapId) {
    ApplicationManager *appMan = (ApplicationManager *)fn_8016DF70(heapId, sizeof(ApplicationManager));
    appMan->appTemplate = *appTemplate;
    appMan->execState = 0;
    appMan->procState = 0;
    appMan->args = args;
    appMan->data = NULL;
    appMan->parent = NULL;
    appMan->child = NULL;
    return appMan;
}

void ApplicationManager_Free(ApplicationManager *appMan) {
    fn_8016E0A0(appMan);
}

void *ApplicationManager_NewData(ApplicationManager *appMan, u32 size, u32 heapId) {
    appMan->data = fn_8016DF70(heapId, size);
    return appMan->data;
}

void *ApplicationManager_Data(ApplicationManager *appMan) {
    return appMan->data;
}

void *ApplicationManager_Args(ApplicationManager *appMan) {
    return appMan->args;
}

BOOL ApplicationManager_Exec(ApplicationManager *appMan) {
    switch (appMan->execState) {
        case 0: appMan->execState = 1;
        case 1:
            if (appMan->appTemplate.init(appMan, &appMan->procState) == TRUE) {
                appMan->execState = 2;
                appMan->procState = 0;
            }
            break;
        case 2:
            if (appMan->appTemplate.main(appMan, &appMan->procState) == TRUE) {
                appMan->execState = 3;
                appMan->procState = 0;
            }
            break;
        case 3:
            if (appMan->appTemplate.exit(appMan, &appMan->procState) == TRUE) {
                return TRUE;
            }
            break;
    }
    return FALSE;
}
// TODO Returns the manager's procState; there is no such accessor in the DS games.

s32 fn_803DEE9C(ApplicationManager *appMan) {
    return appMan->procState;
}
