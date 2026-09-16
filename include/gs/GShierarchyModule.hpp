#pragma once

#include "gs/GSlinkedList.hpp"
#include "gs/render/GSrenderModule.hpp"

#include <revolution.h>

class GSobject;
class GSscene;
class GStexture;

// Size: 0x18
class _UnkHierModuleClass_1 {
private:
    /* 0x00 */ u8 _pad_0[0x18];

public:
    _UnkHierModuleClass_1();
    ~_UnkHierModuleClass_1();
};

// Size: 0x154
class GShierarchyModule : public GSrenderModule {
private:
    /* 0x010 */ GSlistNode *mObjectList;
    /* 0x014 */ u32 _14;
    /* 0x018 */ u32 _18;
    /* 0x01C */ u32 _1c;
    /* 0x020 */ u32 _20;
    /* 0x024 */ u32 _24;
    // TODO(samm) #define the 8s
    /* 0x028 */ u32 _28[8];
    /* 0x048 */ _UnkHierModuleClass_1 _48[8];
    /* 0x108 */ u16 _108;
    /* 0x10A */ u16 _10a;
    /* 0x10C */ u32 _10c;
    /* 0x110 */ u32 _110;
    /* 0x114 */ u32 _114;
    /* 0x118 */ u32 _118;
    /* 0x11C */ u32 _11c;
    /* 0x120 */ u32 _120;
    /* 0x124 */ GSscene *mCurrentScene;
    /* 0x128 */ u32 _128;
    /* 0x12C */ GStexture *_12c;
    /* 0x130 */ u32 _130;
    /* 0x134 */ u32 _134;
    /* 0x138 */ u32 _138;
    /* 0x13C */ u32 _13c;
    /* 0x140 */ u32 _140;
    /* 0x144 */ u32 _144;
    /* 0x148 */ u32 _148;
    /* 0x14C */ u32 _14c;
    /* 0x150 */ u32 _150;

public:
    // TODO(samm) Make this private? (See GSobject::~GSobject())
    static GShierarchyModule *sInstance;

public:
    GShierarchyModule();

    /* 0x08 */ virtual void update(f32 deltaTime);
    /* 0x0C */ virtual void fn_80236AE0();
    /* 0x10 */ virtual void fn_80236AE4();
    /* 0x14 */ virtual ~GShierarchyModule();

    // TODO(samm) Move bulk of body to GSlinkedList
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
            while ((curr = tail->sll.mNext)) {
                if (curr->mData == object) {
                    return;
                }
                tail = curr;
            }
        }

        GSlistNode *newNode = GSlinkedList::allocNode();
        if (newNode) {
            newNode->mData = object;
            newNode->sll.mNext = NULL;
        }

        if (tail) {
            tail->sll.mNext = newNode;
        } else {
            mObjectList = newNode;
        }
    }

    // TODO(samm) Move bulk of body to GSlinkedList
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
            node = node->sll.mNext;
        }

        // Return if object not found
        if (!node) {
            return;
        }

        GSlistNode *next = node->sll.mNext;
        if (prev) {
            prev->sll.mNext = next;
        } else {
            mObjectList = next;
        }

        GSlinkedList::freeNode(node);
    }

    static GSlistNode *fn_80200594(GSobject *arg0);
    static GSlistNode *fn_80200858(GSobject *arg0);

    static void setCurrentScene(GSscene *scene);

    static GShierarchyModule *getInstance() {
        return sInstance;
    }

    static bool isCurrentScene(GSscene *scene) {
        return sInstance->mCurrentScene == scene;
    }
};
