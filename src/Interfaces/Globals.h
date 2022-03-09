#pragma once
#include "EntityManager.h"

class CSPlayer;
namespace globals {

	void Setup();
	void Destory();

	// global pointer
	// all pointers must be inline
	inline CSPlayer* localPlayer = nullptr;

	inline auto entities = entityManager{ };

}