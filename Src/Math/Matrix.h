#pragma once

#include "Vector3.h"
#include "Quaternion.h"

class Matrix
{
public:
	Matrix();
	~Matrix();

	float m00{ 1 };
	float m01{ 0 };
	float m02{ 0 };
	float m03{ 0 };
	float m10{ 0 };
	float m11{ 1 };
	float m12{ 0 };
	float m13{ 0 };
	float m20{ 0 };
	float m21{ 0 };
	float m22{ 1 };
	float m23{ 0 };
	float m30{ 0 };
	float m31{ 0 };
	float m32{ 0 };
	float m33{ 1 };

	Matrix operator*(const Matrix& rhs);
	Vector3 operator*(const Vector3& rhs);
	Vector3 perspectiveMultiply(const Vector3& rhs);
	void invert();
	Matrix getInvert();

	static Matrix rotate(const Quaternion& qot);
	static Matrix scale(const Vector3& s);
	static Matrix translate(const Vector3& t);
	static Matrix trs(const Vector3& pos, const Quaternion& q, const Vector3& s);
	static Matrix projection(float left, float right, float bottom, float top, float near, float far);
	static Matrix projection(float fovy, float aspect, float zNear, float zFar);

private:
};

