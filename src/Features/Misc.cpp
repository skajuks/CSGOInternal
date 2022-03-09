#include "Misc.h"
#include "../Interfaces/Globals.h"
#include "../Interfaces/Entity.h"
#include "../Interfaces/Interfaces.h"

constexpr auto CS_UM_ServerRankRevealAll = 50;

void misc::BunnyHop(UserCmd* cmd) noexcept {

	// TODO: add ladder check

	// TODO: add check if toggled

	if (cmd->buttons & UserCmd::CommandButtons::IN_JUMP && !(globals::localPlayer->Flags() & 1)) {
		cmd->buttons &= ~UserCmd::CommandButtons::IN_JUMP;
	}
}

void misc::RevealPlayerRanks(UserCmd* cmd) noexcept {

	// TODO: add check if toggled

	if (cmd->buttons & UserCmd::CommandButtons::IN_SCORE)
		interfaces::client->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0, 0, nullptr);
}