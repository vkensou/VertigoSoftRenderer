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

	vertex[0].color = Vector4(1, 0, 0, 1);
	vertex[1].color = Vector4(0, 1, 0, 1);
	vertex[2].color = Vector4(0, 0, 1, 1);
	vertex[3].color = Vector4(1, 0, 0, 1);
	vertex[4].color = Vector4(0, 1, 0, 1);
	vertex[5].color = Vector4(0, 0, 1, 1);

	vertex[0].normal = Vector3(0, 0, 1);
	vertex[1].normal = Vector3(0, 0, 1);
	vertex[2].normal = Vector3(0, 0, 1);
	vertex[3].normal = Vector3(0, 0, 1);
	vertex[4].normal = Vector3(0, 0, 1);
	vertex[5].normal = Vector3(0, 0, 1);

	setObjectMatrix(Vector3(0, 0, 0), Quaternion::Euler(0, 45, 0), Vector3::one);
	setCameraMatrix(Vector3(0, 1, -10), Quaternion::Euler(0, 0, 0));
	setProjectionMatrix(60, (float)width / height, 0.1f, 1500);

	::setModelMatrix(matrix_ObjectToWorld);
	::setModelIMatrix(matrix_WorldToObject);
	::setViewMatrix(matrix_Camera);
	::setProjectionMatrix(matrix_Projection);
}

RenderProgram::~RenderProgram()
{
	delete[] vertex;
}

void RenderProgram::render()
{
	setObjectMatrix(Vector3(0, 0, 0), Quaternion::Euler(0, oy += oyspeed, 0), Vector3::one);
	::setModelMatrix(matrix_ObjectToWorld);
	::setModelIMatrix(matrix_WorldToObject);
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

	//Unity在DirectX下回进行如下处理
	matrix_Projection.m11 = -matrix_Projection.m11;
	matrix_Projection.m22 = (-matrix_Projection.m22 - 1.0f) / 2.0f;
	matrix_Projection.m23 = -matrix_Projection.m23 / 2.0f;
}

