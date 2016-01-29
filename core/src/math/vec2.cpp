#include <iostream>

#include "vec2.h"

namespace core {	namespace math {

	vec2::vec2(float x, float y) : x(x), y(y) {	}

	vec2 &vec2::add(const vec2 &vector) {
		x += vector.x;
		y += vector.y;

		return *this;
	}

	vec2 &vec2::subtract(const vec2 &vector) {
		x -= vector.x;
		y -= vector.y;

		return *this;
	}

	vec2 &vec2::multiply(const vec2 &vector) {
		x *= vector.x;
		y *= vector.y;

		return *this;
	}

	vec2 &vec2::divide(const vec2 &vector) {
		x /= vector.x;
		y /= vector.y;

		return *this;
	}

	vec2& vec2::scale(const float scalar) {
		x *= scalar;
		y *= scalar;

		return *this;
	}

	vec2 operator+(vec2 &operand, const vec2 vector) {
		return operand.add(vector);
	}

	vec2 operator-(vec2 &operand, const vec2 vector) {
		return operand.subtract(vector);
	}

	vec2 operator*(vec2 &operand, const vec2 vector) {
		return operand.multiply(vector);
	}

	vec2 operator/(vec2 &operand, const vec2 vector) {
		return operand.divide(vector);
	}

	vec2 &vec2::operator+=(const vec2 &vector) {
		return add(vector);
	}

	vec2 &vec2::operator-=(const vec2 &vector) {
		return subtract(vector);
	}

	vec2 &vec2::operator*=(const vec2 &vector) {
		return multiply(vector);
	}

	vec2 &vec2::operator*=(const float scalar) {
		return scale(scalar);
	}

	vec2 &vec2::operator/=(const vec2 &vector) {
		return divide(vector);
	}

	bool vec2::operator==(const vec2 &vector) {
		return (x == vector.x && y == vector.y);
	}

	bool vec2::operator!=(const vec2 &vector) {
		return !(*this == vector);
	}

	float vec2::getMagnitude() {
		return sqrt(x * x + y * y);
	}

	std::ostream& operator<<(std::ostream &stream, const vec2 &vector) {
		return stream << "(" << vector.x << ", " << vector.y << ")";
	}

}}