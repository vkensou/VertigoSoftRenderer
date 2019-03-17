#include "Vector3.h"
#include <cmath>

Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z)
	:x(x), y(y), z(z)
{

}

float Vector3::length()
{
	if (x == 0 && y == 0 && z == 0)
		return 0;

	return sqrt(x * x + y * y + z + z);
}

void Vector3::normalize()
{
	float len = length();
	if (len > 0)
	{
		x /= len;
		y /= len;
		z /= len;
	}
}

const Vector3 Vector3::forward = Vector3(0, 0, 1);

const Vector3 Vector3::up = Vector3(0, 1, 0);

const Vector3 Vector3::left = Vector3(-1, 0, 0);

const Vector3 Vector3::right = Vector3(1, 0, 0);

const Vector3 Vector3::back = Vector3(0, 0, -1);

const Vector3 Vector3::down = Vector3(0, -1, 0);

const Vector3 Vector3::zero = Vector3(0, 0, 0);

const Vector3 Vector3::one = Vector3(1, 1, 1);

bool operator==(Vector3 lhs, Vector3 rhs)
{
	return std::abs(lhs.x - rhs.x) < 1e-5 && std::abs(lhs.y - rhs.y) < 1e-5 && std::abs(lhs.z - rhs.z) < 1e-5;
}

float dot(Vector3 lhs, Vector3 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 cross(Vector3 lhs, Vector3 rhs)
{
	float _x = lhs.y * rhs.z - lhs.z * rhs.y;
	float _y = lhs.z * rhs.x - lhs.x * rhs.z;
	float _z = lhs.x * rhs.y - lhs.y * rhs.x;
	return Vector3(_x, _y, _z);
}
