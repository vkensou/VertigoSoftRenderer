#pragma once

class Vector4
{
public:
	Vector4();
	Vector4(float x, float y, float z, float w);

	float x() { return m_x; }
	float y() { return m_y; }
	float z() { return m_z; }
	float w() { return m_w; }

private:
	float m_x{ 0 }, m_y{ 0 }, m_z{ 0 }, m_w{ 0 };
};
