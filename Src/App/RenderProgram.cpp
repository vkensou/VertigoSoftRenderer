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
}

RenderProgram::~RenderProgram()
{
	delete[] vertex;
}

void RenderProgram::render()
{
	clear();
	drawTriangle(backBuffer, vertex, 6);
}

void RenderProgram::clear()
{
	std::fill(backBuffer, backBuffer + size, clearColor);
}

