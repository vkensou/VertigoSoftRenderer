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

void drawTriangle(unsigned int* target, Vertex *v, int count)
{
	for (int i = 0; i < count; i += 3)
	{
		if (!cullBack(v + i))
			continue;

	}
}
