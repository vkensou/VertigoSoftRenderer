#include "RenderPipeline.h"

#include "Vertex.h"
#include "Math/Matrix.h"
#include <algorithm>

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

	o.position = matrix_MVP.perspectiveMultiply(vo.position);
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
	return n.z > 0;
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

void callPixelShader(VertexInput &v)
{

}

void drawPoint(int x, int y)
{
	y = height - y;
	if (x >= 0 && x < width && y >= 0 && y < height)
		target[y * width + x] = 0xffffffff;
}

void drawLine(int x0, int y0, int x1, int y1)
{

}

//平底
void drawTriangle1(int x0, int y0, int x1, int y1, int x2, int y2, VertexInput &v0, VertexInput &v1, VertexInput &v2)
{
	int yr = y1 - y0;
	int x1r = x1 - x0;
	int x2r = x2 - x0;
	for (int y = y0; y <= y1; ++y)
	{
		float f = float(y - y0) / yr;
		int xl = f * x1r + x0;
		int xr = f * x2r + x0;
		if (xl > xr)
			std::swap(xl, xr);
		for (int x = xl; x <= xr; ++x)
		{
			drawPoint(x, y);
			//VertexInput v;
			//callPixelShader(v);
		}
	}
}

//平顶
void drawTriangle2(int x0, int y0, int x1, int y1, int x2, int y2, VertexInput &v0, VertexInput &v1, VertexInput &v2)
{
	int yr = y1 - y0;
	int x1r = x1 - x0;
	int x2r = x2 - x0;
	for (int y = y0; y >= y1; --y)
	{
		float f = float(y - y0) / yr;
		int xl = f * x1r + x0;
		int xr = f * x2r + x0;
		if (xl > xr)
			std::swap(xl, xr);
		for (int x = xl; x <= xr; ++x)
		{
			drawPoint(x, y);
			//VertexInput v;
			//callPixelShader(v);
		}
	}
}

//右边为主
void drawTriangle3(int x0, int y0, int x1, int y1, int x2, int y2, VertexInput &v0, VertexInput &v1, VertexInput &v2)
{
	int y = y0;
	int ylr = y1 - y0;
	int yrr = y2 - y0;
	int xlr = x1 - x0;
	int xrr = x2 - x0;
	for (; y <= y1; ++y) 
	{
		float fl = float(y - y0) / ylr;
		int xl = fl * xlr + x0;
		float fr = float(y - y0) / yrr;
		int xr = fr * xrr + x0;
		//if (xl > xr)
		//	std::swap(xl, xr);
		for (int x = xl; x < xr; ++x)
			drawPoint(x, y);
	}

	ylr = y2 - y1;
	xlr = x2 - x1;
	for (; y <= y2; ++y)
	{
		float fl = float(y - y1) / ylr;
		int xl = fl * xlr + x1;
		float fr = float(y - y0) / yrr;
		int xr = fr * xrr + x0;
		//if (xl > xr)
		//	std::swap(xl, xr);
		for (int x = xl; x < xr; ++x)
			drawPoint(x, y);
	}
}

//左边为主
void drawTriangle4(int x0, int y0, int x1, int y1, int x2, int y2, VertexInput &v0, VertexInput &v1, VertexInput &v2)
{
	int y = y0;
	int ylr = y2 - y0;
	int yrr = y1 - y0;
	int xlr = x2 - x0;
	int xrr = x1 - x0;
	for (; y <= y1; ++y)
	{
		float fl = float(y - y0) / ylr;
		int xl = fl * xlr + x0;
		float fr = float(y - y0) / yrr;
		int xr = fr * xrr + x0;
		//if (xl > xr)
		//	std::swap(xl, xr);
		for (int x = xl; x < xr; ++x)
			drawPoint(x, y);
	}

	yrr = y2 - y1;
	xrr = x2 - x1;
	for (; y <= y2; ++y)
	{
		float fl = float(y - y0) / ylr;
		int xl = fl * xlr + x0;
		float fr = float(y - y1) / yrr;
		int xr = fr * xrr + x1;
		//if (xl > xr)
		//	std::swap(xl, xr);
		for (int x = xl; x < xr; ++x)
			drawPoint(x, y);
	}
}

void rasterizeTriangle(VertexInput *vertex)
{
	auto& v0 = vertex[0];
	auto& v1 = vertex[1];
	auto& v2 = vertex[2];
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	int x0 = (v0.position.x + 1) * halfWidth;
	int y0 = (v0.position.y + 1) * halfHeight;
	int x1 = (v1.position.x + 1) * halfWidth;
	int y1 = (v1.position.y + 1) * halfHeight;
	int x2 = (v2.position.x + 1) * halfWidth;
	int y2 = (v2.position.y + 1) * halfHeight;

	if (y0 == y1)
	{
		if (y2 <= y0)
			drawTriangle1(x2, y2, x0, y0, x1, y1, v2, v0, v1);
		else
			drawTriangle2(x2, y2, x0, y0, x1, y1, v2, v0, v1);
	}
	else if (y0 == y2)
	{
		if (y1 <= y0)
			drawTriangle1(x1, y1, x0, y0, x2, y2, v1, v0, v2);
		else
			drawTriangle2(x1, y1, x0, y0, x2, y2, v1, v0, v2);
	}
	else if (y1 == y2)
	{
		if (y0 <= y1)
			drawTriangle1(x0, y0, x1, y1, x2, y2, v0, v1, v2);
		else
			drawTriangle2(x0, y0, x1, y1, x2, y2, v0, v1, v2);
	}
	else
	{
		int vti, vmi, vbi;
		int xtop, ytop, xmiddle, ymiddle, xbottom, ybottom;
		if (y0 < y1 && y1 < y2)
		{
			vti = 0;
			vmi = 1;
			vbi = 2;
			xtop = x0;
			ytop = y0;
			xmiddle = x1;
			ymiddle = y1;
			xbottom = x2;
			ybottom = y2;
		}
		else  if (y0 < y2 && y2 < y1)
		{
			vti = 0;
			vmi = 2;
			vbi = 1;
			xtop = x0;
			ytop = y0;
			xmiddle = x2;
			ymiddle = y2;
			xbottom = x1;
			ybottom = y1;
		}
		else  if (y1 < y0 && y0 < y2)
		{
			vti = 1;
			vmi = 0;
			vbi = 2;
			xtop = x1;
			ytop = y1;
			xmiddle = x0;
			ymiddle = y0;
			xbottom = x2;
			ybottom = y2;
		}
		else  if (y1 < y2 && y2 < y0)
		{
			vti = 1;
			vmi = 2;
			vbi = 0;
			xtop = x1;
			ytop = y1;
			xmiddle = x2;
			ymiddle = y2;
			xbottom = x0;
			ybottom = y0;
		}
		else  if (y2 < y1 && y1 < y0)
		{
			vti = 2;
			vmi = 1;
			vbi = 0;
			xtop = x2;
			ytop = y2;
			xmiddle = x1;
			ymiddle = y1;
			xbottom = x0;
			ybottom = y0;
		}
		else  if (y2 < y0 && y0 < y1)
		{
			vti = 2;
			vmi = 0;
			vbi = 1;
			xtop = x2;
			ytop = y2;
			xmiddle = x0;
			ymiddle = y0;
			xbottom = x1;
			ybottom = y1;
		}

		int xz = (xtop + xbottom) / 2;
		if (xmiddle <= xz)
			drawTriangle3(xtop, ytop, xmiddle, ymiddle, xbottom, ybottom, vertex[vti], vertex[vmi], vertex[vbi]);
		else
			drawTriangle4(xtop, ytop, xmiddle, ymiddle, xbottom, ybottom, vertex[vti], vertex[vmi], vertex[vbi]);
	}
}

void drawTriangle(Vertex *v, int count)
{
	callVertexShader(v, count);

	for (int i = 0; i < vi_count; i += 3)
	{
		if (!cullBack(vi + i))
			continue;

		rasterizeTriangle(vi + i);
	}
}
