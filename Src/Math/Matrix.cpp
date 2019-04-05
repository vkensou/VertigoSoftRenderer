#include "Matrix.h"

#define _USE_MATH_DEFINES
#include <math.h>

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

Matrix Matrix::projection(float left, float right, float bottom, float top, float near, float far)
{
	float x = 2.0F * near / (right - left);
	float y = 2.0F * near / (top - bottom);
	float a = (right + left) / (right - left);
	float b = (top + bottom) / (top - bottom);
	float c = -(far + near) / (far - near);
	float d = -(2.0F * far * near) / (far - near);
	float e = -1.0F;

	Matrix m;

	m.m00 = x;	m.m01 = 0;	m.m02 = a;	m.m03 = 0;
	m.m10 = 0;	m.m11 = y;	m.m12 = b;	m.m13 = 0;
	m.m20 = 0;	m.m21 = 0;	m.m22 = c;	m.m23 = d;
	m.m30 = 0;	m.m31 = 0;	m.m32 = e;	m.m33 = 0;

	return m;
}

Matrix Matrix::projection(float fovy, float aspect, float zNear, float zFar)
{
	float cotangent, deltaZ;
	float radians = (fovy / 2.0f) * (M_PI / 180);
	cotangent = cos(radians) / sin(radians);
	deltaZ = zNear - zFar;

	Matrix m;

	m.m00 = cotangent / aspect; m.m01 = 0.0F;      m.m02 = 0.0F;                    m.m03 = 0.0F;
	m.m10 = 0.0F;               m.m11 = cotangent; m.m12 = 0.0F;                    m.m13 = 0.0F;
	m.m20 = 0.0F;               m.m21 = 0.0F;      m.m22 = (zFar + zNear) / deltaZ; m.m23 = 2.0F * zNear * zFar / deltaZ;
	m.m30 = 0.0F;               m.m31 = 0.0F;      m.m32 = -1.0F;                   m.m33 = 0.0F;

	return m;
}

void Matrix::invert()
{
	float tmp[12];
	Matrix m = *this;

	// Calculate pairs for first 8 elements (cofactors)
	tmp[0] = m.m22 * m.m33;
	tmp[1] = m.m32 * m.m23;
	tmp[2] = m.m12 * m.m33;
	tmp[3] = m.m32 * m.m13;
	tmp[4] = m.m12 * m.m23;
	tmp[5] = m.m22 * m.m13;
	tmp[6] = m.m02 * m.m33;
	tmp[7] = m.m32 * m.m03;
	tmp[8] = m.m02 * m.m23;
	tmp[9] = m.m22 * m.m03;
	tmp[10] = m.m02 * m.m13;
	tmp[11] = m.m12 * m.m03;

	// Calculate first 8 elements (cofactors)
	m00 = tmp[0] * m.m11 + tmp[3] * m.m21 + tmp[4] * m.m31;
	m00 -= tmp[1] * m.m11 + tmp[2] * m.m21 + tmp[5] * m.m31;
	m01 = tmp[1] * m.m01 + tmp[6] * m.m21 + tmp[9] * m.m31;
	m01 -= tmp[0] * m.m01 + tmp[7] * m.m21 + tmp[8] * m.m31;
	m02 = tmp[2] * m.m01 + tmp[7] * m.m11 + tmp[10] * m.m31;
	m02 -= tmp[3] * m.m01 + tmp[6] * m.m11 + tmp[11] * m.m31;
	m03 = tmp[5] * m.m01 + tmp[8] * m.m11 + tmp[11] * m.m21;
	m03 -= tmp[4] * m.m01 + tmp[9] * m.m11 + tmp[10] * m.m21;
	m10 = tmp[1] * m.m10 + tmp[2] * m.m20 + tmp[5] * m.m30;
	m10 -= tmp[0] * m.m10 + tmp[3] * m.m20 + tmp[4] * m.m30;
	m11 = tmp[0] * m.m00 + tmp[7] * m.m20 + tmp[8] * m.m30;
	m11 -= tmp[1] * m.m00 + tmp[6] * m.m20 + tmp[9] * m.m30;
	m12 = tmp[3] * m.m00 + tmp[6] * m.m10 + tmp[11] * m.m30;
	m12 -= tmp[2] * m.m00 + tmp[7] * m.m10 + tmp[10] * m.m30;
	m13 = tmp[4] * m.m00 + tmp[9] * m.m10 + tmp[10] * m.m20;
	m13 -= tmp[5] * m.m00 + tmp[8] * m.m10 + tmp[11] * m.m20;

	// Calculate pairs for second 8 elements (cofactors)
	tmp[0] = m.m20*m.m31;
	tmp[1] = m.m30*m.m21;
	tmp[2] = m.m10*m.m31;
	tmp[3] = m.m30*m.m11;
	tmp[4] = m.m10*m.m21;
	tmp[5] = m.m20*m.m11;
	tmp[6] = m.m00*m.m31;
	tmp[7] = m.m30*m.m01;
	tmp[8] = m.m00*m.m21;
	tmp[9] = m.m20*m.m01;
	tmp[10] = m.m00*m.m11;
	tmp[11] = m.m10*m.m01;

	// Calculate second 8 elements (cofactors)
	m20 = tmp[0] * m.m13 + tmp[3] * m.m23 + tmp[4] * m.m33;
	m20 -= tmp[1] * m.m13 + tmp[2] * m.m23 + tmp[5] * m.m33;
	m21 = tmp[1] * m.m03 + tmp[6] * m.m23 + tmp[9] * m.m33;
	m21 -= tmp[0] * m.m03 + tmp[7] * m.m23 + tmp[8] * m.m33;
	m22 = tmp[2] * m.m03 + tmp[7] * m.m13 + tmp[10] * m.m33;
	m22 -= tmp[3] * m.m03 + tmp[6] * m.m13 + tmp[11] * m.m33;
	m23 = tmp[5] * m.m03 + tmp[8] * m.m13 + tmp[11] * m.m23;
	m23 -= tmp[4] * m.m03 + tmp[9] * m.m13 + tmp[10] * m.m23;
	m30 = tmp[2] * m.m22 + tmp[5] * m.m32 + tmp[1] * m.m12;
	m30 -= tmp[4] * m.m32 + tmp[0] * m.m12 + tmp[3] * m.m22;
	m31 = tmp[8] * m.m32 + tmp[0] * m.m02 + tmp[7] * m.m22;
	m31 -= tmp[6] * m.m22 + tmp[9] * m.m32 + tmp[1] * m.m02;
	m32 = tmp[6] * m.m12 + tmp[11] * m.m32 + tmp[3] * m.m02;
	m32 -= tmp[10] * m.m32 + tmp[2] * m.m02 + tmp[7] * m.m12;
	m33 = tmp[10] * m.m22 + tmp[4] * m.m02 + tmp[9] * m.m12;
	m33 -= tmp[8] * m.m12 + tmp[11] * m.m22 + tmp[5] * m.m02;

	// Calculate determinant
	float det = (m.m00*m00 + m.m10*m01 + m.m20*m02 + m.m30*m03);
	//if (fabs_tpl(det)<0.0001f) assert(0);	

	// Divide the cofactor-matrix by the determinant
	float idet = (float)1.0 / det;
	m00 *= idet; m01 *= idet; m02 *= idet; m03 *= idet;
	m10 *= idet; m11 *= idet; m12 *= idet; m13 *= idet;
	m20 *= idet; m21 *= idet; m22 *= idet; m23 *= idet;
	m30 *= idet; m31 *= idet; m32 *= idet; m33 *= idet;
}

Matrix Matrix::getInvert()
{
	Matrix m = *this;
	m.invert();
	return m;
}
