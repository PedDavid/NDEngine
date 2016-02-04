#include "shader.h"
#include "..\util\file.h"
#include "..\logger\log.h"

namespace core {	namespace graphics {

	Shader::Shader(const char *vertPath, const char *fragPath) 
		: m_VertPath(vertPath), m_FragPath(fragPath) {
		
		GLuint programID = glCreateProgram();
		GLuint vertexID = load(m_VertPath, GL_VERTEX_SHADER);
		GLuint fragmentID = load(m_FragPath, GL_FRAGMENT_SHADER);
		glAttachShader(programID, vertexID);
		glAttachShader(programID, fragmentID);
		glLinkProgram(programID);
		glValidateProgram(programID);
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);

		m_ShaderID = programID;
		LOG(Success, "Shader", "ID: %d", m_ShaderID);
	}

	Shader::~Shader() {
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::load(const char *path, GLuint type) {
		GLuint shaderID = glCreateShader(type);
		std::string vertSourceString = util::readFile(path);
		const char *source = vertSourceString.c_str();
		glShaderSource(shaderID, 1, &source, NULL);
		glCompileShader(shaderID);
		GLint result;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
			char *error = new char[length];
			glGetShaderInfoLog(shaderID, length, &length, error);
			error[length - 2] = '\0'; //delete double \n at end of report
			LOG(Error, "GLSL", "Shader compilation \n\t%s", error);
			delete error;
			glDeleteShader(shaderID);
		} else {
			LOG(Success, "Shader" , "ID: %d | Path: %s", shaderID, path);
		}
		return shaderID;
	}

	void Shader::enable() {
		glUseProgram(m_ShaderID);
	}

	void Shader::disable() {
		glUseProgram(0);
	}

	GLint Shader::getUniformLocation(const GLchar *name) {
		return glGetUniformLocation(m_ShaderID, name);
	}

	void Shader::setUniform1f(const GLchar *name, float value) {
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1fv(const GLchar *name, float *value, GLsizei size) {
		glUniform1fv(getUniformLocation(name), size, value);
	}

	void Shader::setUniform1i(const GLchar *name, int value) {
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform1iv(const GLchar *name, int *value, GLsizei size) {
		glUniform1iv(getUniformLocation(name), size, value);
	}

	void Shader::setUniform2f(const GLchar *name, const math::vec2& vector) {
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const GLchar *name, const math::vec3& vector) {
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}
	void Shader::setUniform4f(const GLchar *name, const math::vec4& vector) {
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}
	void Shader::setUniformMat4(const GLchar* name, const math::mat4 &matrix) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

}}