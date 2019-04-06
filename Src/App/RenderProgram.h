#pragma once

#include "Math/Matrix.h"

struct Vertex;

class RenderProgram
{
public:
	RenderProgram(unsigned int* backBufferPixels, int width, int height);
	~RenderProgram();

	void render();

private:
	void clear();
	void setObjectMatrix(const Vector3& pos, const Quaternion& q, const Vector3& s);
	void setCameraMatrix(const Vector3& pos, const Quaternion& q);
	void setProjectionMatrix(float fovy, float aspect, float zNear, float zFar);

private:
	unsigned int* backBuffer;
	int width, height;
	int size;
	unsigned int clearColor;
	Vertex *vertex;

	Matrix matrix_WorldToObject;
	Matrix matrix_ObjectToWorld;
	Matrix matrix_Camera;
	Matrix matrix_Projection;
};