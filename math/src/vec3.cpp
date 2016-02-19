#include "../include/math/vec3.h"

namespace core {	namespace math {

	vec3::vec3() : x(0.0f), y(0.0f), z(0.0f) {	}
	vec3::vec3(float xyz) : x(xyz), y(xyz), z(xyz) {	}
	vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {	}

	float vec3::magnitude() {
		return sqrt(x * x + y * y + z * z);
	}

	vec3 &vec3::add(const vec3 &vector) {
		x += vector.x;
		y += vector.y;
		z += vector.z;

		return *this;
	}

	vec3 &vec3::subtract(const vec3 &vector) {
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;

		return *this;
	}

	vec3 &vec3::multiply(const vec3 &vector) {
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;

		return *this;
	}

	vec3 &vec3::divide(const vec3 &vector) {
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;

		return *this;
	}

	vec3 &vec3::scale(const float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	vec3 &vec3::operator+=(const vec3 &vector) {
		return add(vector);
	}

	vec3 &vec3::operator-=(const vec3 &vector) {
		return subtract(vector);
	}

	vec3 &vec3::operator*=(const vec3 &vector) {
		return multiply(vector);
	}

	vec3 &vec3::operator*=(const float scalar) {
		return scale(scalar);
	}

	vec3 &vec3::operator/=(const vec3 &vector) {
		return divide(vector);
	}

	bool vec3::operator==(const vec3 &vector) {
		return (x == vector.x && y == vector.y && z == vector.z);
	}

	bool vec3::operator!=(const vec3 &vector) {
		return !(*this == vector);
	}

	vec3 operator+(const vec3 lhs, const vec3 rhs) {
		return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	vec3 operator-(const vec3 lhs, const vec3 rhs) {
		return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	vec3 operator*(const vec3 lhs, const vec3 rhs) {
		return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	vec3 operator/(const vec3 lhs, const vec3 rhs) {
		return vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	std::ostream &operator<<(std::ostream &stream, const vec3 &vector) {
		return stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	}
}}