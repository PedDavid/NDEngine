#pragma once

#include <ostream>

namespace core {	namespace math {

	struct vec2 {
		float x, y;

		vec2();
		vec2(float xy);
		vec2(float x, float y);

		float magnitude();

		vec2 &add(const vec2 &vector);
		vec2 &subtract(const vec2 &vector);
		vec2 &multiply(const vec2 &vector);
		vec2 &divide(const vec2 &vector);
		vec2 &scale(const float scalar);

		vec2 &operator+=(const vec2 &vector);
		vec2 &operator-=(const vec2 &vector);
		vec2 &operator*=(const vec2 &vector);
		vec2 &operator*=(const float scalar);
		vec2 &operator/=(const vec2 &vector);

		bool operator==(const vec2 &vector);
		bool operator!=(const vec2 &vector);

		friend vec2 operator+(const vec2 lhs, const vec2 rhs);
		friend vec2 operator-(const vec2 lhs, const vec2 rhs);
		friend vec2 operator*(const vec2 lhs, const vec2 rhs);
		friend vec2 operator/(const vec2 lhs, const vec2 rhs);

		friend std::ostream &operator<<(std::ostream &stream, const vec2 &vector);
	};
}}