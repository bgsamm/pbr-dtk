#include "gs/render/GSrenderModule.hpp"

#include "gs/render/80235A74.hpp"

#include "version.hpp"

u8 sNextModuleId = 1;

GSrenderModule *GSrenderModule::sHead;
GSrenderModule *GSrenderModule::sTail;

GSrenderModule *GSrenderModule::findModule(u8 id) {
    GSrenderModule *module = sHead;
    while (module) {
        if (module->mId == id) {
            return module;
        }
        module = module->mNext;
    }
    return NULL;
}

void GSrenderModule::registerModule(GSrenderModule *module) {
    if (!sHead) {
        sHead = module;
    }

    if (sTail) {
        sTail->mNext = module;
    }

    sTail = module;
    module->mNext = NULL;
}

void GSrenderModule::unregisterModule(GSrenderModule *module) {
    if (module == sHead) {
        sHead = module->mNext;

        if (sTail == module) {
            sTail = NULL;
        }
    } else {
        GSrenderModule *prev = sHead;
        while (prev) {
            if (prev->mNext == module) {
                break;
            }
            prev = prev->mNext;
        }

        prev->mNext = module->mNext;

        if (sTail == module) {
            sTail = module->mNext;
        }
    }

    module->mNext = NULL;
}

GSrenderModule::GSrenderModule(const char *name) : mName(name), mId(sNextModuleId++), mNext(NULL) {
    registerModule(this);
}

GSrenderModule::~GSrenderModule() {
    fn_80236618(this);
    unregisterModule(this);
}

void GSrenderModule::update(f32 deltaTime) {}

void GSrenderModule::fn_80236AE0() {}

void GSrenderModule::fn_80236AE4() {}
