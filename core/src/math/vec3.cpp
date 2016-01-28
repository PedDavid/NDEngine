#include <iostream>

#include "vec3.h"

namespace math{

	vec3::vec3(float x, float y, float z) : x(x), y(y), z(z){	}

	vec3 &vec3::add(const vec3 &vector){
		x += vector.x;
		y += vector.y;
		z += vector.z;

		return *this;
	}

	vec3 &vec3::subtract(const vec3 &vector){
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;

		return *this;
	}

	vec3 &vec3::multiply(const vec3 &vector){
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;

		return *this;
	}

	vec3 &vec3::divide(const vec3 &vector){
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;

		return *this;
	}

	vec3 &vec3::scale(const float scalar){
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	vec3 operator+(vec3 &operand, const vec3 vector){
		return operand.add(vector);
	}

	vec3 operator-(vec3 &operand, const vec3 vector){
		return operand.subtract(vector);
	}

	vec3 operator*(vec3 &operand, const vec3 vector){
		return operand.multiply(vector);
	}

	vec3 operator/(vec3 &operand, const vec3 vector){
		return operand.divide(vector);
	}

	vec3 &vec3::operator+=(const vec3 &vector){
		return add(vector);
	}

	vec3 &vec3::operator-=(const vec3 &vector){
		return subtract(vector);
	}

	vec3 &vec3::operator*=(const vec3 &vector){
		return multiply(vector);
	}

	vec3 &vec3::operator*=(const float scalar){
		return scale(scalar);
	}

	vec3 &vec3::operator/=(const vec3 &vector){
		return divide(vector);
	}

	bool vec3::operator==(const vec3 &vector){
		return (x == vector.x && y == vector.y && z == vector.z);
	}

	bool vec3::operator!=(const vec3 &vector){
		return !(*this == vector);
	}

	float vec3::getMagnitude(){
		return sqrt(x * x + y * y + z * z);
	}

	std::ostream &operator<<(std::ostream &stream, const vec3 &vector){
		return stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	}
}