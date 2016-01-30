#pragma once

<<<<<<< HEAD
#include <ostream>

=======
>>>>>>> 66ce75b9f3ff8154094f462204ecf2e6df26e8f1
namespace core {	namespace math {
	struct vec2 {
		float x, y;

		vec2() = default;
		vec2(float x, float y);

		vec2 &add(const vec2 &vector);
		vec2 &subtract(const vec2 &vector);
		vec2 &multiply(const vec2 &vector);
		vec2 &divide(const vec2 &vector);
		vec2 &scale(const float scalar);

		friend vec2 operator+(vec2 operand, const vec2 &vector);
		friend vec2 operator-(vec2 operand, const vec2 &vector);
		friend vec2 operator*(vec2 operand, const vec2 &vector);
		friend vec2 operator/(vec2 operand, const vec2 &vector);

		vec2 &operator+=(const vec2 &vector);
		vec2 &operator-=(const vec2 &vector);
		vec2 &operator*=(const vec2 &vector);
		vec2 &operator*=(const float scalar);
		vec2 &operator/=(const vec2 &vector);

		bool operator==(const vec2 &vector);
		bool operator!=(const vec2 &vector);

		float getMagnitude();

		friend std::ostream &operator<<(std::ostream &stream, const vec2 &vector);
	};
}}