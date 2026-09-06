#pragma once

#include "gs/GSlinkedList.hpp"

#include <revolution.h>

class GSobject;
class GSscene;

class GSsceneManager {
private:
    /* 0x000 */ u8 _pad_0[0x10];
    /* 0x010 */ GSlistNode *mObjectList;
    /* 0x014 */ u8 _pad_14[0x110];
    /* 0x124 */ GSscene *mCurrentScene;

public:
    void registerObject(GSobject *object) {
        if (!object) {
            return;
        }

        GSlistNode *tail = mObjectList;

        // Walk through list until found or at end
        if (tail) {
            if (tail->mData == object) {
                return;
            }

            GSlistNode *curr;
            while ((curr = tail->mNext)) {
                if (curr->mData == object) {
                    return;
                }
                tail = curr;
            }
        }

        GSlistNode *newNode = GSlinkedList::allocNode();
        if (newNode) {
            newNode->mData = object;
            newNode->mNext = NULL;
        }

        if (tail) {
            tail->mNext = newNode;
        } else {
            mObjectList = newNode;
        }
    }

    void unregisterObject(GSobject *object) {
        if (!object) {
            return;
        }

        GSlistNode *node = mObjectList;
        GSlistNode *prev = NULL;

        // Return if list is empty
        if (!node) {
            return;
        }

        while (node) {
            if (node->mData == object) {
                break;
            }
            prev = node;
            node = node->mNext;
        }

        // Return if object not found
        if (!node) {
            return;
        }

        GSlistNode *next = node->mNext;
        if (prev) {
            prev->mNext = next;
        } else {
            mObjectList = next;
        }

        GSlinkedList::freeNode(node);
    }

    static GSlistNode *fn_80200594(GSobject *arg0);
    static GSlistNode *fn_80200858(GSobject *arg0);

    static GSsceneManager *getInstance() {
        return sInstance;
    }

    static bool isCurrentScene(GSscene *scene) {
        return sInstance->mCurrentScene == scene;
    }

    static void setCurrentScene(GSscene *scene);

    // TODO(samm) Make this private? See GSobject::~GSobject()
    static GSsceneManager *sInstance;
};
