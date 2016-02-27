#pragma once
#include <glew.h>

#include <math/mat4.h>
#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>

#include <unordered_map>

namespace core {	namespace graphics {

	class Shader {
	
	public: 
		enum Type {
			VERTEX		=	GL_VERTEX_SHADER,			//.vert
			TESS_CTR	=	GL_TESS_CONTROL_SHADER,		//.tesc
			TESS_EV		=	GL_TESS_EVALUATION_SHADER,	//.tese
			GEOMETRY	=	GL_GEOMETRY_SHADER,			//.geom
			FRAGMENT	=	GL_FRAGMENT_SHADER,			//.frag
			COMPUTE		=	GL_COMPUTE_SHADER			//.comp
		};

	private:
		GLuint m_ProgramID;

		std::unordered_map<std::string, const GLint> m_AttribMap;
		std::unordered_map<std::string, const GLint> m_UniformMap;

	public:
		Shader(std::initializer_list<std::pair<const Type, const std::string>> list);
		Shader(const std::string vertPath, const std::string fragPath);
		~Shader();

	private:
		GLuint load(Type type, const std::string path);
		void linkProgram(std::vector<GLuint> shaderIDs);
		void cacheVariableLocations();
		GLchar *getTypeString(Type type);
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
