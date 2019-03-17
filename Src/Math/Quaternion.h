#pragma once

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	
	float x{ 0 };
	float y{ 0 };
	float z{ 0 };
	float w{ 0 };

private:
};