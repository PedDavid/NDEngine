#pragma once
#include <glew.h>

#include <math/mat4.h> //already includes vec3/4
#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>

#include <unordered_map>

namespace core {	namespace graphics {
		class Shader {
		private:
			GLuint m_ProgramID;

			std::unordered_map<std::string, GLint> m_AttribMap;
			std::unordered_map<std::string, GLint> m_UniformMap;

		public:
			Shader(const char *vertPath, const char *fragPath);
			~Shader();

		private:
			GLuint load(const char *path, GLuint type);
			void cacheVariableLocations();
			GLint getAttribLocation(const GLchar *name);
			GLint getUniformLocation(const GLchar *name);

		public:
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
		};
}}
