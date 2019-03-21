#pragma once

#include "Vector3.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	
	float x{ 0 };
	float y{ 0 };
	float z{ 0 };
	float w{ 0 };

	Quaternion operator*(const Quaternion& rhs);
	Vector3 operator*(const Vector3& v);

	static Quaternion Euler(float x, float y, float z);
	static Quaternion AxisAngle(Vector3 axis, float angle);

	static const Quaternion identity;
private:
};