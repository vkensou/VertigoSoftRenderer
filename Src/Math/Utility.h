#pragma once

inline float lerp(float from, float to, float t)
{
	return to * t + from * (1.0F - t);
}
