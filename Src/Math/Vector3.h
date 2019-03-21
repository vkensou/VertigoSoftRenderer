#pragma once

#include <cmath>

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);

	float x{ 0 }, y{ 0 }, z{ 0 };

	Vector3 operator+(const Vector3& rhs)
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3 operator-(const Vector3& rhs)
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	float length();
	void normalize();

	static const Vector3 forward;
	static const Vector3 up;
	static const Vector3 left;
	static const Vector3 right;
	static const Vector3 back;
	static const Vector3 down;
	static const Vector3 zero;
	static const Vector3 one;

private:
};

inline Vector3 operator*(float lhs, const Vector3& rhs)
{
	return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

inline Vector3 operator*(const Vector3& lhs, float rhs)
{
	return rhs * lhs;
}

inline Vector3 operator/(const Vector3& lhs, float rhs)
{
	return Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

bool operator==(const Vector3& lhs, const Vector3& rhs);

inline bool operator!=(const Vector3& lhs, const Vector3& rhs)
{
	return !(lhs == rhs);
}

inline Vector3 operator+(float lhs, const Vector3& rhs)
{
	return Vector3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
}

inline Vector3 operator+(const Vector3& lhs, float rhs)
{
	return rhs + lhs;
}

float dot(const Vector3& lhs, const Vector3& rhs);

Vector3 cross(const Vector3& lhs, const Vector3& rhs);
