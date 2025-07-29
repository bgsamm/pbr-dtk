#include "global.hpp"

#include "gs/GStask.hpp"
#include "gs/GStimeline.hpp"

extern f32 fn_8000739C();

/* lbl_8063F610 */ GStimelineManager *GStimelineManager::sInstance;

void GStimeline::timelineTaskCallback(u32 taskId, void *userParam) {
    f32 dt = fn_8000739C();
    GStimelineManager::sInstance->update(dt);
}

void GStimeline::init(u32 param1) {
    GStimelineManager::sInstance = new GStimelineManager(param1);

    u32 taskId = GStask::createTask(TASK_TYPE_MAIN, 0, NULL, timelineTaskCallback);
    GStask::setTaskName(taskId, "GStimelineManager");
}

GStimelineManager::GStimelineManager(u32 param1) {
    _0 = param1;
    mNodes = NULL;
}

void GStimelineManager::update(f32 dt) {
    GStimelineNode *next;
    GStimelineNode *node = mNodes;
    GStimelineNode *prev = NULL;
    while (node != NULL) {
        next = node->mNext;
        if (GStimeline::fn_802248E8(node, dt)) {
            GStimeline::fn_8022490C(node);
            delete node;

            if (prev == NULL) {
                mNodes = next;
            }
            else {
                prev->mNext = next;
            }
            node = prev;
        }
        prev = node;
        node = next;
    }
}

bool GStimeline::fn_802248E8(GStimelineNode *node, f32 dt) {
    node->mTimer -= dt;
    return node->mTimer <= 0;
}

void GStimeline::fn_8022490C(GStimelineNode *node) {
    node->mCallback(node->_C, node->_10, node->_14, node->_18);
}
