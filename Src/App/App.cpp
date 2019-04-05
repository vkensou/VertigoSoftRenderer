#include "App.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Matrix.h"
#include "Math/math3d-left.h"

BITMAPINFO backBufferInfo;
unsigned int* backBufferPixels;
int width = 800;
int height = 600;

void initBackBuffer(BITMAPINFO& info, int w, int h, unsigned int*& buffer);

void testVector3()
{
	Vector3 forward(0, 0, 1);
	Vector3 up(0, 1, 0);
	Vector3 left = cross(forward, up);
}

void testQuaternion()
{
	Vector3 forward(1, 0.5f, 0);
	Quaternion q = Quaternion::Euler(0, 45, 45);
	Quaternion q2 = Quaternion::Euler(30, 0, 30);
	auto r = q * q2 * forward;
}

void testMatrix()
{
	Quaternion q = Quaternion::Euler(0, 45, 45);
	Vector3 t = { 0.2, 1, -0.3 };
	Vector3 s = { 2, -1, 1 };
	Matrix m1 = Matrix::rotate(q);
	Matrix m2 = Matrix::translate(t);
	Matrix m3 = Matrix::scale(s);

	Matrix m = Matrix::trs(t, q, s);
	Vector3 v0(0.8, 2, -0.1);
	auto v = m * Vector3(v0);
	//Matrix mr = m1 * m2;

	Matrix tm = m2;
	tm = tm * m1;
	tm = tm * m3;
}

void testMath3d()
{
	vector3 v;
	v.x = 1; v.y = 0.5f; v.z = 0;
	quaternion q;
	quaternion_init(&q, 0, 45 * 3.1415926f / 180, 45 * 3.1415926f / 180);
	matrix44 m;
	matrix44_from_quaternion(&m, &q);

	vector3_mul(&v, &m);
}

void init(HINSTANCE hInst, HWND hWnd)
{
	testVector3();
	testQuaternion();
	testMatrix();
	testMath3d();
	
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
