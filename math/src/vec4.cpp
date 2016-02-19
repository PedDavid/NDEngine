#include "../include/math/vec4.h"

namespace core {	namespace math {

	vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {	}
	vec4::vec4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {	}
	vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {	}

	float vec4::magnitude() {
		return sqrt(x * x + y * y + z * z + w * w);
	}

	vec4 &vec4::add(const vec4 &vector) {
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;

		return *this;
	}

	vec4 &vec4::subtract(const vec4 &vector) {
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;

		return *this;
	}

	vec4 &vec4::multiply(const vec4 &vector) {
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		w *= vector.w;

		return *this;
	}

	vec4 &vec4::divide(const vec4 &vector) {
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		w /= vector.w;

		return *this;
	}

	vec4 &vec4::scale(const float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;

		return *this;
	}

	vec4 &vec4::operator+=(const vec4 &vector) {
		return add(vector);
	}

	vec4 &vec4::operator-=(const vec4 &vector) {
		return subtract(vector);
	}

	vec4 &vec4::operator*=(const vec4 &vector) {
		return multiply(vector);
	}

	vec4 &vec4::operator*=(const float scalar) {
		return scale(scalar);
	}

	vec4 &vec4::operator/=(const vec4 &vector) {
		return divide(vector);
	}

	bool vec4::operator==(const vec4 &vector) {
		return (x == vector.x && y == vector.y && z == vector.z && w == vector.w);
	}

	bool vec4::operator!=(const vec4 &vector) {
		return !(*this == vector);
	}

	vec4 operator+(const vec4 lhs, const vec4 rhs) {
		return vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.z);
	}

	vec4 operator-(const vec4 lhs, const vec4 rhs) {
		return vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.z);
	}

	vec4 operator*(const vec4 lhs, const vec4 rhs) {
		return vec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.z);
	}

	vec4 operator/(const vec4 lhs, const vec4 rhs) {
		return vec4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.z);
	}

	std::ostream &operator<<(std::ostream &stream, const vec4 &vector) {
		return stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
	}
}}