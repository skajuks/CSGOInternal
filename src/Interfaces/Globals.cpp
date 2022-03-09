#include "Globals.h"

void globals::Setup() noexcept {
	if (!interfaces::engine->IsInGame())
		return;

	globals::entities.Update();
}

void globals::Destory() noexcept {
	localPlayer = nullptr;
}