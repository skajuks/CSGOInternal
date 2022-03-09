#pragma once
#include "Entity.h"
#include "../Structs/IClientEntityList.h"
#include "Interfaces.h"

class entityManager : public ClientEntityListener {
public:
	void Setup() noexcept;
	void Destroy() noexcept;

	void ClassCheck(CEntity* entity, const int id) noexcept;
	void Update() noexcept;

	virtual void OnEntityCreated(CEntity* entity) override;
	virtual void OnEntityDeleted(CEntity* entity) override;

	std::vector<CEntity*> playerList = { };
};