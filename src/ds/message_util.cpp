#include "ds/message_util.hpp"

#include "ds/message.hpp"

Strbuf *MessageUtil_SpeciesName(u32 species, u32 heapId) {
    MessageLoader *loader =
        MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA, MESSAGE_BANK_SPECIES_NAMES, heapId);
    Strbuf *name;
    if (loader != NULL) {
        name = MessageLoader_GetNewString(loader, species);
        MessageLoader_Free(loader);
        return name;
    }
    return NULL;
}
