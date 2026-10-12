#include "ds/field_battle_data_transfer.hpp"

#include "ds/DSbridge.hpp"
#include "ds/party.hpp"
#include "ds/trainer_info.hpp"

#include <cstring>

// TODO Replace with proper imports
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
}

FieldBattleDTO *FieldBattleDTO_New(u32 heapId, u32 battleType, u32 arg2, u32 arg3, u32 arg4) {
    FieldBattleDTO *dto = (FieldBattleDTO *)fn_8016DF70(heapId, sizeof(FieldBattleDTO));
    s32 i;
    memset(dto, 0, sizeof(FieldBattleDTO));
    dto->battleType = battleType;
    dto->_16C = 0;
    dto->resultMask = 0;
    dto->_130 = 0;
    dto->_134 = arg4;
    dto->_174 = arg3;
    dto->_140 = 0;
    dto->_154 = arg2;
    for (i = 0; i < MAX_BATTLERS; i++) {
        dto->parties[i] = Party_New(heapId);
    }
    for (i = 0; i < MAX_BATTLERS; i++) {
        dto->trainerInfo[i] = TrainerInfo_New(heapId);
    }
    dto->bag = Bag_New(heapId);
    dto->_F0 = 0;
    dto->_EC = 0;
    return dto;
}
