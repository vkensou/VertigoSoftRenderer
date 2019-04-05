#pragma once

class RenderProgram
{
public:
	RenderProgram(unsigned int* backBufferPixels, int width, int height);

	void render();

private:
	void clear();

private:
	unsigned int* backBuffer;
	int width, height;
	int size;
	unsigned int clearColor;
};