#pragma once
//#include <numbers>
#include <cmath>

class CMatrix3x4
{
public:
	float data[3][4];
};

class CVector
{
public:
	constexpr CVector operator-(const CVector& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	constexpr CVector operator+(const CVector& other) const noexcept
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	constexpr CVector operator*(const float scale) const noexcept
	{
		return { x * scale, y * scale, z * scale };
	}

public:
	float x{ };
	float y{ };
	float z{ };
};