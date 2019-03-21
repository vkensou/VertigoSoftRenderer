#include "Quaternion.h"

#define _USE_MATH_DEFINES
#include <math.h>

const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1);

Quaternion::Quaternion()
{

}

Quaternion::Quaternion(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{

}

Quaternion Quaternion::operator*(const Quaternion& rhs)
{
	Quaternion r;
	r.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
	r.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
	r.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
	r.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
	return r;
}

Vector3 Quaternion::operator*(const Vector3& v)
{
	Vector3 u(x, y, z);
	float s = w;
	return 2 * dot(u, v) * u + (s * s - dot(u, u)) * v + 2 * s * cross(u, v);
}

Quaternion Quaternion::Euler(float x, float y, float z)
{
	x *= M_PI / 180;
	y *= M_PI / 180;
	z *= M_PI / 180;

	float sx_2 = sin(x / 2);
	float cx_2 = cos(x / 2);
	float sy_2 = sin(y / 2);
	float cy_2 = cos(y / 2);
	float sz_2 = sin(z / 2);
	float cz_2 = cos(z / 2);

	Quaternion qX(sx_2, 0.0F, 0.0F, cx_2);
	Quaternion qY(0.0F, sy_2, 0.0F, cy_2);
	Quaternion qZ(0.0F, 0.0F, sz_2, cz_2);
	Quaternion ret = (qY * qX) * qZ;
	return ret;
}

Quaternion Quaternion::AxisAngle(Vector3 axis, float a)
{
	Quaternion ret;
	a *= M_PI / 180;
	float a_2 = a / 2;
	float sa_2 = sin(a_2);
	ret.w = cos(sa_2);
	ret.x = sa_2 * axis.x;
	ret.y = sa_2 * axis.y;
	ret.z = sa_2 * axis.z;
	return ret;
}
