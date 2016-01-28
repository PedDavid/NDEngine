#pragma once

#include "vec3.h"
#include "vec4.h"

namespace math{
	struct mat4{
		union{
			float elements[4 * 4];
			vec4 columns[4];
			struct
			{
				//m_row_col(column major)
				float m11, m21, m31, m41; //column 1
				float m12, m22, m32, m42; //column 2
				float m13, m23, m33, m43; //column 3
				float m14, m24, m34, m44; //column 4
				//TRUE VISUAL REPRESENTATIOn
				//m11 m12 m13 m14
				//m21 m22 m23 m24
				//m31 m32 m33 m34
				//m41 m42 m43 m44
			};
		};

		mat4();
		mat4(float diagonal);

		static mat4 identity();

		static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 prespective(float fov, float aspectRatio, float near, float far);

		static mat4 translation(const vec3 &translation);
		static mat4 rotation(float angle, const vec3 &axis);
		static mat4 sheer(int i, int j, float distance);
		static mat4 scale(const vec3 &scale);

		mat4& multiply(const mat4 &other);
		friend mat4 operator*(mat4 left, const mat4 &right);
		mat4& operator *=(const mat4 &right);

		vec3 multiply(const vec3 &other) const;
		friend vec3 operator*(const mat4 &left, const vec3 &right);

		vec4 multiply(const vec4 &other) const;
		friend vec4 operator*(const mat4 &left, const vec4 &right);

		friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix);
	};
}