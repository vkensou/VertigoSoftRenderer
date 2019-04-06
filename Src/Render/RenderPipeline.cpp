#include "RenderPipeline.h"

#include "Vertex.h"
#include "Math/Matrix.h"

static Matrix matrix_M;
static Matrix matrix_V;
static Matrix matrix_P;
static Matrix matrix_MVP;

static unsigned int* target;
static int width;
static int height;

void refreshMatrix_MVP()
{
	matrix_MVP = matrix_P * matrix_V * matrix_M;
}

void setModelMatrix(const Matrix& m)
{
	matrix_M = m;
	refreshMatrix_MVP();
}

void setViewMatrix(const Matrix& m)
{
	matrix_V = m;
	refreshMatrix_MVP();
}

void setProjectionMatrix(const Matrix& m)
{
	matrix_P = m;
	refreshMatrix_MVP();
}

void setTarget(unsigned int* target, int width, int height)
{
	::target = target;
	::width = width;
	::height = height;
}

struct VertexInput
{
	Vector3 position;
	Vector3 normal;
	Vector4 texcoord;
};
VertexInput vi[3000];
int vi_count = 0;

VertexInput vertexShader(Vertex &vo)
{
	VertexInput o;

	o.position = matrix_MVP * vo.position;
	o.normal = vo.normal;
	o.texcoord = vo.texcoord;

	return o;
}

unsigned int pixelShader(VertexInput &in)
{
	unsigned int col = 0xff000000;

	return col;
}

//背面剔除，返回false说明被剔除
bool cullBack(VertexInput *vertex)
{
	Vector3 v1 = vertex[1].position - vertex[0].position;
	Vector3 v2 = vertex[2].position - vertex[1].position;
	auto n = cross(v1, v2);
	return n.z < 0;
}

void callVertexShader(Vertex *vo, int count)
{
	vi_count = count;
	for (int i = 0; i < count; i += 3)
	{
		vi[i] = vertexShader(vo[i]);
		vi[i + 1] = vertexShader(vo[i + 1]);
		vi[i + 2] = vertexShader(vo[i + 2]);
	}
}

void callPixelShader(VertexInput *v)
{

}

void drawTriangle(Vertex *v, int count)
{
	callVertexShader(v, count);

	for (int i = 0; i < vi_count; i += 3)
	{
		if (!cullBack(vi + i))
			continue;

		callPixelShader(vi + i);
	}
}
