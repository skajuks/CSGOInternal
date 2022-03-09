#pragma once
#include "../Offsets/Netvars/Netvars.h"
#include "Memory.h"
#include "../Math/UtlVector.h"
#include "../Math/CVector.h"
#include "../Structs/WeaponData.h"

class CEntity;
class ClientUnknown
{
public:
	constexpr CEntity* GetBaseEntity() noexcept {
		return memory::Call<CEntity*>(this, 7);
	}
};

class ClientRenderable {
public:
	constexpr ClientUnknown* GetClientUnknown() noexcept {
		return memory::Call<ClientUnknown*>(this, 0);
	}
};

class CEntity {
public:

	constexpr int32_t GetTeam() noexcept {
		return memory::Call<int32_t>(this, 88);
	}

	constexpr int32_t GetHealth() noexcept {
		return memory::Call<int32_t>(this, 122);
	}

	constexpr bool IsAlive() noexcept {
		return memory::Call<bool>(this, 156);
	}

	constexpr bool IsPlayer() noexcept {
		return memory::Call<bool>(this, 158);
	}

	constexpr void GetEyePosition(CVector& eyePositionOut) noexcept {
		memory::Call<void, CVector&>(this, 285, eyePositionOut);
	}

	constexpr void GetAimPunch(CVector& aimPunchOut) noexcept {
		memory::Call<void, CVector&>(this, 346, aimPunchOut);
	}

	constexpr WeaponType GetWeaponType() noexcept {
		return memory::Call<WeaponType>(this, 455);
	}

	constexpr WeaponInfo* GetWeaponInfo() noexcept {
		return memory::Call<WeaponInfo*>(this, 461);
	}

	constexpr bool IsWeapon() noexcept {
		return memory::Call<bool>(this, 166);
	}

	// Networkable

	constexpr ClientClass* GetClientClass() noexcept {
		return memory::Call<ClientClass*>(this + 0x8, 2);
	}
	constexpr bool IsDormant() noexcept {
		return memory::Call<bool>(this + 0x8, 9);
	}
	constexpr int32_t Index() noexcept {
		return memory::Call<int>(this + 0x8 , 10);
	}


	// CBasePlayer netvars

	NETVAR(Flags, "CBasePlayer->m_fFlags", int32_t);
	NETVAR(Spotted, "CBaseEntity->m_bSpotted", bool);

	auto IsPistol() noexcept { return GetWeaponType() == WeaponType::Pistol; }
	auto IsSniperRifle() noexcept { return GetWeaponType() == WeaponType::SniperRifle; }
	auto IsGrenade() noexcept { return GetWeaponType() == WeaponType::Grenade; }

	auto IsFullAuto() noexcept {
		const auto weaponData = GetWeaponInfo();
		if (weaponData)
			return weaponData->fullAuto;
		return false;
	}

	auto requiresRecoilControl() noexcept {
		const auto weaponData = GetWeaponInfo();
		if (weaponData)
			return weaponData->recoilMagnitude < 35.0f && weaponData->recoveryTimeStand > weaponData->cycletime;
		return false;
	}

};

class CSPlayer : public CEntity {
public:
	NETVAR(IsScoped, "CCSPlayer->m_bIsScoped", bool);
};