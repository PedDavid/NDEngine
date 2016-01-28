#pragma once

#define PI 3.1415927f

namespace math{
	inline float toRadians(float degrees){ return degrees * (PI / 180.0f); }
}