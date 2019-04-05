#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

Matrix Matrix::operator*(const Matrix& rhs)
{
	Matrix m;
	m.m00 = m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20 + m03 * rhs.m30;
	m.m01 = m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21 + m03 * rhs.m31;
	m.m02 = m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22 + m03 * rhs.m32;
	m.m03 = m00 * rhs.m03 + m01 * rhs.m13 + m02 * rhs.m23 + m03 * rhs.m33;

	m.m10 = m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20 + m13 * rhs.m30;
	m.m11 = m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31;
	m.m12 = m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32;
	m.m13 = m10 * rhs.m03 + m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33;

	m.m20 = m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20 + m23 * rhs.m30;
	m.m21 = m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31;
	m.m22 = m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32;
	m.m23 = m20 * rhs.m03 + m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33;

	m.m30 = m30 * rhs.m00 + m31 * rhs.m10 + m32 * rhs.m20 + m33 * rhs.m30;
	m.m31 = m30 * rhs.m01 + m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31;
	m.m32 = m30 * rhs.m02 + m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32;
	m.m33 = m30 * rhs.m03 + m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33;

	return m;
}

Vector3 Matrix::operator*(const Vector3& rhs)
{
	Vector3 v;

	v.x = m00 * rhs.x + m01 * rhs.y + m02 * rhs.z + m03;
	v.y = m10 * rhs.x + m11 * rhs.y + m12 * rhs.z + m13;
	v.z = m20 * rhs.x + m21 * rhs.y + m22 * rhs.z + m23;

	return v;
}

Matrix Matrix::rotate(const Quaternion& qot)
{
	Matrix m;

	float x2 = qot.x + qot.x, y2 = qot.y + qot.y, z2 = qot.z + qot.z;
	float xx = qot.x * x2, xy = qot.x * y2, xz = qot.x * z2;
	float yy = qot.y * y2, yz = qot.y * z2, zz = qot.z * z2;
	float wx = qot.w * x2, wy = qot.w * y2, wz = qot.w * z2;

	m.m00 = 1 - (yy + zz);		m.m10 = xy + wz;
	m.m20 = xz - wy;			m.m30 = 0;
	m.m01 = xy - wz;			m.m11 = 1 - (xx + zz);
	m.m21 = yz + wx;			m.m31 = 0;
	m.m02 = xz + wy;			m.m12 = yz - wx;
	m.m22 = 1 - (xx + yy);		m.m32 = 0;
	m.m03 = 0;					m.m13 = 0;
	m.m23 = 0;					m.m33 = 1;

	return m;
}

Matrix Matrix::scale(const Vector3& s)
{
	Matrix m;

	m.m00 = s.x;
	m.m11 = s.y;
	m.m22 = s.z;

	return m;
}

Matrix Matrix::translate(const Vector3& t)
{
	Matrix m;

	m.m03 = t.x;
	m.m13 = t.y;
	m.m23 = t.z;

	return m;
}

Matrix Matrix::trs(const Vector3& pos, const Quaternion& q, const Vector3& s)
{
	Matrix m = rotate(q);

	m.m00 *= s.x;
	m.m10 *= s.x;
	m.m20 *= s.x;

	m.m01 *= s.y;
	m.m11 *= s.y;
	m.m21 *= s.y;

	m.m02 *= s.z;
	m.m12 *= s.z;
	m.m22 *= s.z;

	m.m03 = pos.x;
	m.m13 = pos.y;
	m.m23 = pos.z;

	return m;
}
