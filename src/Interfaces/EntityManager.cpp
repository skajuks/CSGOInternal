#include "EntityManager.h"

void entityManager::Setup() noexcept {
	playerList.reserve(64); // max player entities
	interfaces::entityList->AddEntityListener(this);
}

void entityManager::Destroy() noexcept {
	interfaces::entityList->RemoveEntityListener(this);
}

void entityManager::ClassCheck(CEntity* entity, const int id) noexcept {

	// Cast entity to correct class from id

	switch (id) {
	case ClassIndex::CCSPlayer: {

		const auto player = static_cast<CSPlayer*>(entity);
		if (entity->Index() == interfaces::engine->GetLocalPlayerIndex())
			globals::localPlayer = player;
		playerList.emplace_back(player);
	}
	break;
	case ClassIndex::CCSPlayerResource: {
	}
	default: break;
	}
}

void entityManager::Update() noexcept {

	// Iterate through all game entities

	for (auto i = 0; i <= interfaces::entityList->GetHighestEntityIndex(); i++) {
		
		const auto entity = interfaces::entityList->Get(i);

		if (!entity)
			continue;

		const auto clientClass = entity->GetClientClass();

		if (!clientClass)
			continue;

		ClassCheck(entity, clientClass->classID);
	}
}

void entityManager::OnEntityCreated(CEntity* entity) {
	if (!entity) return;

	const ClientClass* clientClass = entity->GetClientClass();

	if (!clientClass) return;

	ClassCheck(entity, clientClass->classID);
}

void entityManager::OnEntityDeleted(CEntity* entity) {
	if (!entity) return;

	const auto ent = std::ranges::find(playerList, entity);

	if (ent == playerList.end()) return;

	playerList.erase(ent);
}