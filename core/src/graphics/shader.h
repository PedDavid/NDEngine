#pragma once
#include <glew.h>

#include "..\math\vec2.h"
#include "..\math\mat4.h" //already includes vec3/4

namespace core {	namespace graphics {
		class Shader {
		private:
			GLuint m_ShaderID;
			const char *m_VertPath, *m_FragPath;
		public:
			Shader(const char *vertPath, const char *fragPath);
			~Shader();

			void enable();
			void disable();

			void setUniform1f(const GLchar *name, float value);
			void setUniform1fv(const GLchar *name, float *value, GLsizei size);
			void setUniform1i(const GLchar *name, int value);
			void setUniform1iv(const GLchar *name, int *value, GLsizei size);
			void setUniform2f(const GLchar *name, const math::vec2& vector);
			void setUniform3f(const GLchar *name, const math::vec3& vector);
			void setUniform4f(const GLchar *name, const math::vec4& vector);
			void setUniformMat4(const GLchar* name, const math::mat4 &matrix);

		private:
			GLuint load(const char *path, GLuint type);

			GLint getUniformLocation(const GLchar *name);
		};
}}
