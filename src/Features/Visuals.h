#pragma once
#include "../Interfaces/Interfaces.h"
#include "../Hooks/Hooks.h"
#include <array>

namespace visuals {

	std::array<float, 4> RGBAtoFloat(std::array<float, 4> col);
	std::array<float, 3> RGBtoFloat(std::array<float, 3> col);
	std::array<float, 4> HealthToRGB(int health);

	inline struct color_map {
		// glow
		std::pair<bool, std::array<float, 4>> playerTeam{ false, RGBAtoFloat({11, 255, 148, 0.8f}) };
		std::pair<bool, std::array<float, 4>> chicken{ false, RGBAtoFloat({66, 19, 69, 1.f}) };
		std::pair<bool, std::array<float, 4>> c4{ false, RGBAtoFloat({146, 19, 69, 1.f}) };
		std::pair<bool, std::array<float, 4>> c4_planted{ false, RGBAtoFloat({255, 0, 255, 1.f}) };
		std::pair<bool, std::array<float, 4>> grenade_projectile{ false, RGBAtoFloat({255, 255, 0, 1.f}) };
		std::pair<bool, std::array<float, 4>> weapons{ false, RGBAtoFloat({255, 255, 255, 1.f}) };
		// chams
		std::pair<bool, std::array<float, 3>> playerHidden{ false, RGBtoFloat({255, 0, 188}) };
		std::pair<bool, std::array<float, 3>> playerVisible{ false, RGBtoFloat({0, 0, 255}) };
	} colors;

	inline std::array<float, 4> world = { 0.f, 0.5f, 0.2f, 1.f };
	inline std::array<float, 4> sky = { 1.f, 0.f, 1.f, 1.f };

	struct toggles {
		bool playerGlowTeam = true;
		bool playerGlowEnemy = true;
		bool chickenGlow = true;
		bool glowMaster = false;
		bool enemyGlowByHealth = true;
		bool chamsMaster = true;
	};
	inline toggles toggle;


	void Glow();
	void ChangeWorldColors();
	void D3D9DrawEsp();
	bool ChangeChamsColors(void* results, const DrawModelInfo& info, CMatrix3x4* bones, float* weights,
		float* delayedWeights, const CVector& modelOrigin, const int32_t flags);

}

