#pragma once

#include "Math/Vector3.h"
#include "Math/Vector4.h"

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector4 color;
	Vector4 texcoord;
};