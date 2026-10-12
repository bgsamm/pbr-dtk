#pragma once

#include "gs/GSlinkedList.hpp"
#include "gs/GSrender.hpp"
#include "gs/render/GSrenderModule.hpp"

#include <revolution.h>

struct GSvec3;
class GSlight;
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
    /* 0x010 */ GSsinglyLinkedList mObjectList;
    /* 0x014 */ GSdoublyLinkedList _14;
    /* 0x01C */ GSsinglyLinkedList _1c;
    /* 0x020 */ GSsinglyLinkedList _20;
    /* 0x024 */ GSsinglyLinkedList _24;
    // TODO(samm) #define the 8s
    /* 0x028 */ GSobject *_28[8];
    /* 0x048 */ _UnkHierModuleClass_1 _48[8];
    /* 0x108 */ u16 _108;
    /* 0x10A */ u16 _10a;
    /* 0x10C */ GSsinglyLinkedList mLights;
    /* 0x110 */ GStexture *_110;
    /* 0x114 */ GStexture *_114;
    /* 0x118 */ GSlight *_118;
    /* 0x11C */ GSlight *_11c;
    /* 0x120 */ GSlight *_120;
    /* 0x124 */ GSscene *mCurrentScene;
    /* 0x128 */ GStexture *_128;
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

public: // TODO(samm) Make private
    static GSrenderLight *sLights[8];
    static GSrenderLight *lbl_804920B0[8];
    static GSrenderLight *lbl_804920D0[8];
    static u8 sLightCount;
    static u8 lbl_8063F46D;
    static u8 lbl_8063F46E;

public:
    GShierarchyModule();

    /* 0x08 */ virtual void update(f32 deltaTime);
    /* 0x0C */ virtual void fn_80236AE0();
    /* 0x10 */ virtual void fn_80236AE4();
    /* 0x14 */ virtual ~GShierarchyModule();

    void fn_802010E0();

    void registerObject(GSobject *object) {
        mObjectList.append(object);
    }

    void unregisterObject(GSobject *object) {
        mObjectList.remove(object);
    }

    // TODO(samm) Names

    GStexture *get_110() const {
        return _110;
    }

    GStexture *get_114() const {
        return _114;
    }

    GSlight *get_118() const {
        return _118;
    }

    GStexture *get_128() const {
        return _128;
    }

    GSscene *getCurrentScene() const {
        return mCurrentScene;
    }

    u32 get_138() const {
        return _138;
    }

    u32 get_140() const {
        return _140;
    }

    u32 get_144() const {
        return _144;
    }

    static void fn_80200594(GSobject *arg0);
    static void fn_80200858(GSobject *arg0);

    static void fn_802027FC(GSvec3 *arg0);

    static void setCurrentScene(GSscene *scene);

    static bool isCurrentScene(GSscene *scene) {
        return sInstance->mCurrentScene == scene;
    }

    static void applyLights() {
        GSrender::sInstance->setLights(sLightCount, sLights);
    }

    static GShierarchyModule *getInstance() {
        return sInstance;
    }

    static GShierarchyModule *sInstance;
};
