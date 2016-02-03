#include <iostream>

#include "../include/math/mat4.h"
#include "../include/math/utils.h"

namespace core {	namespace math {

	mat4::mat4() : mat4(0.0f) {	}

	mat4::mat4(float diag) {
		m11 = diag;	m12 = 0.0f;	m13 = 0.0f;	m14 = 0.0f;
		m21 = 0.0f;	m22 = diag;	m23 = 0.0f;	m24 = 0.0f;
		m31 = 0.0f;	m32 = 0.0f;	m33 = diag;	m34 = 0.0f;
		m41 = 0.0f;	m42 = 0.0f;	m43 = 0.0f;	m44 = diag;
	}

	mat4 mat4::identity() {
		return mat4(1.0f);
	}

	mat4& mat4::multiply(const mat4 &other) {
		float data[16];
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				float sum = 0.0f;
				for (int e = 0; e < 4; e++) {
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}
		memcpy(elements, data, 4 * 4 * sizeof(float));
		return *this;
	}

	vec3 mat4::multiply(const vec3 &other) const {
		return vec3(
			columns[0].x * other.x + columns[1].x * other.y + +columns[2].x * other.z + columns[3].x,
			columns[0].y * other.x + columns[1].y * other.y + +columns[2].y * other.z + columns[3].y,
			columns[0].z * other.x + columns[1].z * other.y + +columns[2].z * other.z + columns[3].z
			);
	}

	vec4 mat4::multiply(const vec4 &other) const {
		return vec4(
			columns[0].x * other.x + columns[1].x * other.y + +columns[2].x * other.z + columns[3].x * other.w,
			columns[0].y * other.x + columns[1].y * other.y + +columns[2].y * other.z + columns[3].y * other.w,
			columns[0].z * other.x + columns[1].z * other.y + +columns[2].z * other.z + columns[3].z * other.w,
			columns[0].w * other.x + columns[1].w * other.y + +columns[2].w * other.z + columns[3].w * other.w
			);
	}

	mat4 operator*(mat4 left, const mat4& right) {
		return left.multiply(right);
	}

	mat4& mat4::operator*=(const mat4& right) {
		return multiply(right);
	}

	vec3 operator*(const mat4 &left, const vec3 &right) {
		return left.multiply(right);
	}

	vec4 operator*(const mat4 &left, const vec4 &right) {
		return left.multiply(right);
	}

	mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
		mat4 result(1.0f);
		result.m11 = 2.0f / (right - left);
		result.m22 = 2.0f / (top - bottom);
		result.m33 = 2.0f / (near - far);

		result.m14 = (left + right) / (left - right);
		result.m24 = (bottom + top) / (bottom - top);
		result.m34 = (far + near) / (near - far);

		return result;
	}

	mat4 mat4::prespective(float fov, float aspectRatio, float near, float far) {
		mat4 result;
		float xScale = 1.0f / tan(toRadians(fov / 2.0f));
		float yScale = xScale * aspectRatio;

		float frustumLength = far - near;

		result.m11 = xScale;
		result.m22 = yScale;
		result.m33 = -(far + near) / frustumLength;
		result.m43 = -1.0f;
		result.m34 = -(2.0f * far * near) / frustumLength;

		return result;
	}

	mat4 mat4::translation(const vec3& translation) {
		mat4 result(1.0f);

		result.m14 = translation.x;
		result.m24 = translation.y;
		result.m34 = translation.z;

		return result;
	}

	mat4 mat4::rotation(float angle, const vec3& axis) {
		mat4 result(1.0f);

		float r = toRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		result.m11 = axis.x * axis.x * omc + c;
		result.m21 = axis.x * axis.y * omc + axis.z * s;
		result.m31 = axis.x * axis.z * omc - axis.y * s;

		result.m12 = axis.y * axis.x * omc - axis.z * s;
		result.m22 = axis.y * axis.y * omc + c;
		result.m32 = axis.y * axis.z * omc + axis.x * s;

		result.m13 = axis.z * axis.x * omc + axis.y * s;
		result.m23 = axis.z * axis.y * omc - axis.x * s;
		result.m33 = axis.z * axis.z * omc + c;

		return result;
	}

	mat4 mat4::sheer(int line, int column, float distance) {
		mat4 result(1.0f);

		//	| 1    Syx  Szx  0	|
		//	| Sxy  1    Szy  0	|
		//	| Sxz  Syz  1    0	|
		//	| 0    0    0    1	|
		//	Where Sij implements a shear of I by J
		//	Thus, Sxy shears X by Y

		result.elements[(line - 1) + (column - 1) * 4] = distance;

		return result;
	}

	mat4 mat4::scale(const vec3& scale) {
		mat4 result(1.0f);

		result.m11 = scale.x;
		result.m22 = scale.y;
		result.m33 = scale.z;

		return result;
	}

	std::ostream& operator<<(std::ostream& stream, const mat4& matrix) {
		return stream << "(" << matrix.m11 << ", " << matrix.m12 << ", " << matrix.m13 << ", " << matrix.m14 << ")" << std::endl <<
			"(" << matrix.m21 << ", " << matrix.m22 << ", " << matrix.m23 << ", " << matrix.m24 << ")" << std::endl <<
			"(" << matrix.m31 << ", " << matrix.m32 << ", " << matrix.m33 << ", " << matrix.m34 << ")" << std::endl <<
			"(" << matrix.m41 << ", " << matrix.m42 << ", " << matrix.m43 << ", " << matrix.m44 << ")";
	}
}}