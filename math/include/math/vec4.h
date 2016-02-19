#pragma once

#include <ostream>

namespace core {	namespace math {
	struct vec4 {
		float x, y, z, w;

		vec4();
		vec4(float xyzw);
		vec4(float x, float y, float z, float w);

		float magnitude();

		vec4 &add(const vec4 &other);
		vec4 &subtract(const vec4 &other);
		vec4 &multiply(const vec4 &other);
		vec4 &divide(const vec4 &other);
		vec4 &scale(const float scalar);

		friend vec4 operator+(vec4 operand, const vec4& right);
		friend vec4 operator-(vec4 operand, const vec4& right);
		friend vec4 operator*(vec4 operand, const vec4& right);
		friend vec4 operator/(vec4 operand, const vec4& right);

		bool operator==(const vec4 &right);
		bool operator!=(const vec4 &right);

		vec4 &operator+=(const vec4 &right);
		vec4 &operator-=(const vec4 &right);
		vec4 &operator*=(const vec4 &right);
		vec4& operator*=(const float scalar);
		vec4 &operator/=(const vec4 &right);

		friend std::ostream &operator<<(std::ostream &stream, const vec4 &vector);
	};
}}