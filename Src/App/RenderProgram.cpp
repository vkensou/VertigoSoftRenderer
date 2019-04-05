#include "RenderProgram.h"

#include <algorithm>

RenderProgram::RenderProgram(unsigned int* backBufferPixels, int width, int height)
	:backBuffer(backBufferPixels), width(width), height(height),
	clearColor(0xff000000)

{
	size = width * height;
}

void RenderProgram::render()
{
	clear();
}

void RenderProgram::clear()
{
	std::fill(backBuffer, backBuffer + size, clearColor);
}

