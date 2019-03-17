#pragma once

class Matrix
{
public:
	Matrix();
	~Matrix();

	float m00() { return m_m00; }
	float m01() { return m_m01; }
	float m02() { return m_m02; }
	float m03() { return m_m03; }
	float m10() { return m_m10; }
	float m11() { return m_m11; }
	float m12() { return m_m12; }
	float m13() { return m_m13; }
	float m20() { return m_m20; }
	float m21() { return m_m21; }
	float m22() { return m_m22; }
	float m23() { return m_m23; }
	float m30() { return m_m30; }
	float m31() { return m_m31; }
	float m32() { return m_m32; }
	float m33() { return m_m33; }

private:
	float m_m00{ 1 };
	float m_m01{ 0 };
	float m_m02{ 0 };
	float m_m03{ 0 };
	float m_m10{ 0 };
	float m_m11{ 0 };
	float m_m12{ 0 };
	float m_m13{ 0 };
	float m_m20{ 0 };
	float m_m21{ 0 };
	float m_m22{ 0 };
	float m_m23{ 0 };
	float m_m30{ 0 };
	float m_m31{ 0 };
	float m_m32{ 0 };
	float m_m33{ 0 };
};

