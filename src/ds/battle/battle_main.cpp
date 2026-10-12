// 803AB534-803AC820 (part of battle_main.c): creation and teardown of the battle.

#include ".unsorted/8038F424.hpp"
#include "ds/DSbridge.hpp"
#include "ds/battle/battle_common.hpp"
#include "ds/battle/battle_constants.hpp"
#include "ds/battle/battle_controller_player.hpp"
#include "ds/battle/battle_io_command.hpp"
#include "ds/battle/battle_lib.hpp"
#include "ds/battle/battle_system.hpp"
#include "ds/field_battle_data_transfer.hpp"
#include "ds/message.hpp"
#include "ds/overlay_manager.hpp"
#include "ds/party.hpp"
#include "ds/pokemon.hpp"
#include "ds/string_template.hpp"

extern "C" {

// TODO probably BattleMain_CopyBattleSysToDTOAndFree (pret); the battle results are mostly not copied back in this
// game.
void fn_803AC5F0(void) {
    ApplicationManager *appMan = fn_803D9E48();
    BattleSystem *battleSys = (BattleSystem *)ApplicationManager_Data(appMan);
    FieldBattleDTO *dto = (FieldBattleDTO *)ApplicationManager_Args(appMan);
    int battlerId;

    if ((battleSys->battleType & (BATTLE_TYPE_FRONTIER - 1)) == BATTLE_TYPE_AI_PARTNER) {
        // Only the first three Pokemon of the player's party go back.
        for (battlerId = 0; battlerId < 3; battlerId++) {
            Pokemon *src = Party_GetPokemonBySlotIndex(battleSys->parties[BATTLER_US], battlerId);
            Pokemon *dst = Party_GetPokemonBySlotIndex(dto->parties[BATTLER_US], battlerId);

            Pokemon_Copy(src, dst);
        }

        for (battlerId = 0; battlerId < MAX_BATTLERS; battlerId++) {
            fn_8016E0A0(battleSys->parties[battlerId]);
            fn_8016E0A0(battleSys->trainerInfo[battlerId]);
        }
    } else {
        for (battlerId = 0; battlerId < MAX_BATTLERS; battlerId++) {
            Party_Copy(battleSys->parties[battlerId], dto->parties[battlerId]);
            fn_8016E0A0(battleSys->parties[battlerId]);
            fn_8016E0A0(battleSys->trainerInfo[battlerId]);
        }
    }

    dto->resultMask = battleSys->resultMask;
    dto->leveledUpMonsMask = BattleContext_Get(battleSys, battleSys->battleCtx, BATTLECTX_LEVEL_UP_MONS, 0);

    fn_8016E0A0(battleSys->msgBuffer);
    MessageLoader_Free(battleSys->msgLoader);
    MessageLoader_Free(battleSys->attackMsgLoader);
    StringTemplate_Free(battleSys->strFormatter);
    BattleContext_Free(battleSys->battleCtx);

    for (battlerId = 0; battlerId < battleSys->maxBattlers; battlerId++) {
        BattlerData_Delete(battleSys, battleSys->battlers[battlerId], battleSys->renderMode);
    }

    fn_8016E0A0(battleSys);
    fn_803D9854(0);

    if (!fn_803D9870()) {
        fn_803D9854(1);
    }
}

// TODO Counts the battlers up to the first one of a single controller in a double battle
int fn_803AC78C(void) {
    BattleSystem *battleSys = lbl_806405C0;
    u32 battleType = BattleSystem_GetBattleType(battleSys);
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    int count = 0;

    for (u8 i = 0; i < maxBattlers; i++) {
        if ((battleType & BATTLE_TYPE_2vs2) == FALSE && (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_DOUBLES) &&
            i > 1) {
            break;
        }

        count++;
    }

    return count;
}
}
