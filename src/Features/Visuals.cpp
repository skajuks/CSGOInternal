#include "Visuals.h"

std::array<float, 4U> visuals::RGBAtoFloat(std::array<float, 4> col) {
	return { col[0] / 255, col[1] / 255, col[2] / 255, col[3] };
}
std::array<float, 3U> visuals::RGBtoFloat(std::array<float, 3> col) {
	return { col[0] / 255, col[1] / 255, col[2] / 255};
}
std::array<float, 4U> visuals::HealthToRGB(int health) {
	return RGBAtoFloat({ abs(255 - (health * 2.55f)), health * 2.55f, 0.f, 1.f});
}

void visuals::Glow() {

	if (!toggle.glowMaster)
		return;

	if (!globals::localPlayer)
		return;

	for (auto i = 0; i < interfaces::glow->glowObjectDefinitions.Count(); i++) {
		
		auto& glow = interfaces::glow->glowObjectDefinitions[i];

		if (glow.IsUnused()) {
			continue;
		}
	
		CEntity* entity = glow.entity;

		if (!entity) {
			continue;
		}
		
		ClientClass* clientClass = entity->GetClientClass();

		if (!clientClass) {
			continue;
		}

		switch (clientClass->classID) {
		case (ClassIndex::CCSPlayer): {

			if (!toggle.playerGlowTeam || !toggle.playerGlowEnemy)
				break;

			CSPlayer* player = static_cast<CSPlayer*>(entity);

			if (!player->IsAlive())
				break;

			if (player->GetTeam() == globals::localPlayer->GetTeam()) {
				if (toggle.playerGlowTeam)
					glow.SetColor(colors.playerTeam.second.data());
			}
			else {
				if (toggle.playerGlowEnemy) {
					std::array<float, 4U> health = HealthToRGB(player->GetHealth());
					glow.SetColor(health.data());
				}
			}
			break;
		}
		case ClassIndex::CChicken:

			if (!toggle.chickenGlow)
				break;

			glow.SetColor(colors.chicken.second.data());
			break;
		case ClassIndex::CC4:
			glow.SetColor(colors.c4.second.data());
			break;
		case ClassIndex::CPlantedC4:
			glow.SetColor(colors.c4_planted.second.data());
			break;
		case ClassIndex::CBaseCSGrenadeProjectile ||
			 ClassIndex::CMolotovProjectile ||
			 ClassIndex::CSmokeGrenadeProjectile:
			glow.SetColor(colors.grenade_projectile.second.data());
			break;
		default:
			if (!entity->IsWeapon())
				break;
			glow.SetColor(colors.weapons.second.data());	// for weapons
			break;
		}
	}
}

void visuals::ChangeWorldColors() {
	for (auto i = interfaces::materialSys->FirstMaterial(); i != interfaces::materialSys->InvalidMaterial();
		i = interfaces::materialSys->NextMaterial(i)) {

		const auto mat = interfaces::materialSys->GetMaterial(i);
		if (!mat || mat->IsErrorMaterial())
			continue;
		const auto group = std::string_view(mat->GetTextureGroupName());

		if (group.starts_with("World"))
			mat->Modulate(world.data());
		else if (group.starts_with("Sky"))
			mat->Modulate(sky.data());
	}
}

bool visuals::ChangeChamsColors(void* results, const DrawModelInfo& info, CMatrix3x4* bones, float* weights,
	float* delayedWeights, const CVector& modelOrigin, const int32_t flags) {
	if (toggle.chamsMaster) {
		CEntity* entity = info.renderable->GetClientUnknown()->GetBaseEntity();
		if (entity && entity->IsPlayer()) {
			static Material* material = interfaces::materialSys->FindMaterial("debug/debugambientcube");

			interfaces::render->SetAlphaModulation(1.f);

			// part of model that can be seen through walls
			material->SetMaterialVarFlag(Material::IGNOREZ, true);
			interfaces::render->SetColorModulation(colors.playerHidden.second.data());
			interfaces::render->ForcedMaterialOverride(material);
			hooks::DrawModelFnOriginal(interfaces::render, results, info, bones, weights, delayedWeights, modelOrigin, flags);

			// part of model that doens't render through walls
			material->SetMaterialVarFlag(Material::IGNOREZ, false);
			interfaces::render->SetColorModulation(colors.playerVisible.second.data());
			interfaces::render->ForcedMaterialOverride(material);
			hooks::DrawModelFnOriginal(interfaces::render, results, info, bones, weights, delayedWeights, modelOrigin, flags);
			return true;
		}
		return false;
	}
	return false;
}