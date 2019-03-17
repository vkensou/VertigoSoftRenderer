#pragma once

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	
	float x() { return m_x; }
	float y() { return m_y; }
	float z() { return m_z; }
	float w() { return m_w; }

private:
	float m_x{ 0 };
	float m_y{ 0 };
	float m_z{ 0 };
	float m_w{ 0 };
};