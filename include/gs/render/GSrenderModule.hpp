#pragma once

#include <revolution.h>

// NOTE(samm) Name known from RTTI
class GSrenderModule {
protected:
    /* 0x0 */ const char *mName;
    /* 0x4 */ u8 mId;
    /* 0x8 */ GSrenderModule *mNext;

    static GSrenderModule *sHead;
    static GSrenderModule *sTail;

public:
    GSrenderModule(const char *name);

    // TODO(samm) Names
    /* 0x08 */ virtual void update(f32 deltaTime);
    /* 0x0C */ virtual void fn_80236AE0();
    /* 0x10 */ virtual void fn_80236AE4();
    /* 0x14 */ virtual ~GSrenderModule();

    GSrenderModule *getNext() const {
        return mNext;
    }

    static GSrenderModule *findModule(u8 id);
    static void registerModule(GSrenderModule *module);
    static void unregisterModule(GSrenderModule *module);

    static GSrenderModule *getModuleList() {
        return sHead;
    }
};
