#include "RenderProgram.h"

#include <algorithm>
#include "Render/Vertex.h"
#include "Render/RenderPipeline.h"

RenderProgram::RenderProgram(unsigned int* backBufferPixels, int width, int height)
	:backBuffer(backBufferPixels), width(width), height(height),
	clearColor(0xff000000)
{
	size = width * height;
	vertex = new Vertex[6];	
	vertex[0].position = Vector3(0, 1, 0);
	vertex[1].position = Vector3(1, 0, 0);
	vertex[2].position = Vector3(-1, 0, 0);
	vertex[3].position = Vector3(0, -1, 0);
	vertex[4].position = Vector3(1, 0, 0);
	vertex[5].position = Vector3(-1, 0, 0);

	setObjectMatrix(Vector3(3.209, 0, 4.307), Quaternion::Euler(29.594, -24.01, 53.752), Vector3::one);
	setCameraMatrix(Vector3(-5.95, 3.37, -13.48), Quaternion::Euler(-3.544, 53.982, 18.256));
	setProjectionMatrix(60, (float)width / height, 0.3, 1000);

	::setModelMatrix(matrix_WorldToObject);
	::setViewMatrix(matrix_Camera);
	::setProjectionMatrix(matrix_Projection);
}

RenderProgram::~RenderProgram()
{
	delete[] vertex;
}

void RenderProgram::render()
{
	clear();
	setTarget(backBuffer, width, height);
	drawTriangle(vertex, 6);
}

void RenderProgram::clear()
{
	std::fill(backBuffer, backBuffer + size, clearColor);
}

void RenderProgram::setObjectMatrix(const Vector3& pos, const Quaternion& q, const Vector3& s)
{
	matrix_ObjectToWorld = Matrix::trs(pos, q, s);
	matrix_WorldToObject = matrix_ObjectToWorld.getInvert();
}

void RenderProgram::setCameraMatrix(const Vector3& pos, const Quaternion& q)
{
	Vector3 offset(-pos.x, -pos.y ,pos.z);
	Vector3 scale(1, 1, -1);
	matrix_Camera = Matrix::trs(pos, q, Vector3::one);
	matrix_Camera.invert();
	matrix_Camera.m20 = -matrix_Camera.m20;
	matrix_Camera.m21 = -matrix_Camera.m21;
	matrix_Camera.m22 = -matrix_Camera.m22;
	matrix_Camera.m23 = -matrix_Camera.m23;
}

void RenderProgram::setProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
{
	matrix_Projection = Matrix::projection(fovy, aspect, zNear, zFar);
}

