#pragma once

<<<<<<< HEAD
#include <ostream>

=======
>>>>>>> 66ce75b9f3ff8154094f462204ecf2e6df26e8f1
namespace core {	namespace math {
	struct vec3 {
		float x, y, z;

		vec3() = default;
		vec3(float x, float y, float z);

		vec3 &add(const vec3 &other);
		vec3 &subtract(const vec3 &other);
		vec3 &multiply(const vec3 &other);
		vec3 &divide(const vec3 &other);
		vec3 &scale(const float scalar);

		friend vec3 operator+(vec3 operand, const vec3 &right);
		friend vec3 operator-(vec3 operand, const vec3 &right);
		friend vec3 operator*(vec3 operand, const vec3 &right);
		friend vec3 operator/(vec3 operand, const vec3 &right);

		vec3 &operator+=(const vec3 &right);
		vec3 &operator-=(const vec3 &right);
		vec3 &operator*=(const vec3 &right);
		vec3 &operator*=(const float scalar);
		vec3 &operator/=(const vec3 &right);

		bool operator==(const vec3 &right);
		bool operator!=(const vec3 &right);

		float getMagnitude();

		friend std::ostream &operator<<(std::ostream &stream, const vec3 &vector);
	};
}}