#include "Vector4.h"
#include "Utility.h"

Vector4::Vector4()
{

}

Vector4::Vector4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{

}

Vector4 lerp(Vector4 &a, Vector4 &b, float t)
{
	Vector4 o;

	o.x = lerp(a.x, b.x, t);
	o.y = lerp(a.y, b.y, t);
	o.z = lerp(a.z, b.z, t);
	o.w = lerp(a.w, b.w, t);

	return o;
}
