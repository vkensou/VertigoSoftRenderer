#include "App.h"

BITMAPINFO backBufferInfo;
unsigned int* backBufferPixels;
int width = 800;
int height = 600;

void initBackBuffer(BITMAPINFO& info, int w, int h, unsigned int*& buffer);

void init(HINSTANCE hInst, HWND hWnd)
{
	initBackBuffer(backBufferInfo, width, height, backBufferPixels);
}

void update(HDC hdc)
{
	StretchDIBits(hdc, 0, 0, width, height, 0, 0, width, height, backBufferPixels, &backBufferInfo, DIB_RGB_COLORS, SRCCOPY);
}

void quit()
{
	delete[] backBufferPixels;
}

void initBackBuffer(BITMAPINFO& info, int w, int h, unsigned int*& buffer)
{
	int size = w * h;
	buffer = new unsigned int[size];

	for (int i = 0; i < w * h; ++i)
	{
		buffer[i] = 0xffff0000;
	}

	info.bmiHeader.biSize = sizeof(info.bmiHeader);//结构体所需的字节数
	info.bmiHeader.biWidth = w;
	info.bmiHeader.biHeight = h;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;
	info.bmiHeader.biCompression = BI_RGB; //图片数据压缩格式BI_RGB为RGB数据
	info.bmiHeader.biSizeImage = 0;
	info.bmiHeader.biXPelsPerMeter = 0;
	info.bmiHeader.biYPelsPerMeter = 0;
	info.bmiHeader.biClrUsed = 0;
	info.bmiHeader.biClrImportant = 0;
}