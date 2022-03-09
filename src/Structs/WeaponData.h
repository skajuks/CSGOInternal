#pragma once
enum class WeaponType {
	Knife = 0,
	Pistol,
	SubMachinegun,
	Rifle,
	Shotgun,
	SniperRifle,
	Machinegun,
	C4,
	Placeholder,
	Grenade,
	Unknown,
	StackableItem,
	Fists,
	BreachCharge,
	BumpMine,
	Tablet,
	Melee
};

struct WeaponInfo {
	char filler_0[20];
		int maxClip;
	char filler_1[112];
		const char* name;
	char filler_2[60];
		WeaponType type;
	char filler_3[4];
		int price;
	char filler_4[8];
		float cycletime;
	char filler_5[12];
		bool fullAuto;
	char filler_6[3];
		int damage;
		float headshotMultiplier;
		float armorRatio;
		int bullets;
		float penetration;
	char filler_7[8];
		float range;
		float rangeModifier;
	char filler_8[16];
		bool silencer;
	char filler_9[15];
		float maxSpeed;
		float maxSpeedAlt;
	char filler_10[100];
		float recoilMagnitude;
		float recoilMagnitudeAlt;
	char filler_11[16];
		float recoveryTimeStand;
};