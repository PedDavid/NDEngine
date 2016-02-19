#pragma once

#include "vec2.h"
#include <ostream>

namespace core {	namespace math {
	struct vec3 {
		float x, y, z;

		vec3();
		vec3(float xyz);
		vec3(float x, float y, float z);

		float magnitude();

		vec3 &add(const vec3 &other);
		vec3 &subtract(const vec3 &other);
		vec3 &multiply(const vec3 &other);
		vec3 &divide(const vec3 &other);
		vec3 &scale(const float scalar);

		vec3 &operator+=(const vec3 &right);
		vec3 &operator-=(const vec3 &right);
		vec3 &operator*=(const vec3 &right);
		vec3 &operator*=(const float scalar);
		vec3 &operator/=(const vec3 &right);

		bool operator==(const vec3 &right);
		bool operator!=(const vec3 &right);

		friend vec3 operator+(const vec3 lhs, const vec3 rhs);
		friend vec3 operator-(const vec3 lhs, const vec3 rhs);
		friend vec3 operator*(const vec3 lhs, const vec3 rhs);
		friend vec3 operator/(const vec3 lhs, const vec3 rhs);

		friend std::ostream &operator<<(std::ostream &stream, const vec3 &vector);
	};
}}