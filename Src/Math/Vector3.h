#pragma once

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);

	float x() { return m_x; }
	float y() { return m_y; }
	float z() { return m_z; }

private:
	float m_x{ 0 }, m_y{ 0 }, m_z{ 0 };
};

