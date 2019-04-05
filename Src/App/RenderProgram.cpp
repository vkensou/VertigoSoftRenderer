#include "RenderProgram.h"

#include <algorithm>
#include "Render/Vertex.h"
#include "Render/RenderPipeline.h"

RenderProgram::RenderProgram(unsigned int* backBufferPixels, int width, int height)
	:backBuffer(backBufferPixels), width(width), height(height),
	clearColor(0xff000000)
{
	size = width * height;
	vertex = new Vertex[3];	
}

RenderProgram::~RenderProgram()
{
	delete[] vertex;
}

void RenderProgram::render()
{
	clear();
	drawTriangle(backBuffer, vertex, 3);
}

void RenderProgram::clear()
{
	std::fill(backBuffer, backBuffer + size, clearColor);
}

