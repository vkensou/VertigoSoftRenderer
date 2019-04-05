#include "RenderPipeline.h"

#include "Vertex.h"

//背面剔除，返回false说明被剔除
bool cullBack(Vertex *vertex)
{
	Vector3 v1 = vertex[1].position - vertex[0].position;
	Vector3 v2 = vertex[2].position - vertex[1].position;
	auto n = cross(v1, v2);
	return n.z < 0;
}

static unsigned int* target;
static int width;
static int height;
void setTarget(unsigned int* target, int width, int height)
{
	::target = target;
	::width = width;
	::height = height;
}

void drawTriangle(Vertex *v, int count)
{
	for (int i = 0; i < count; i += 3)
	{
		if (!cullBack(v + i))
			continue;

	}
}
