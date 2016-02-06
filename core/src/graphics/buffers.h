#pragma once

#include <glew.h>
#include <vector>

namespace core {	namespace graphics {

	struct vbo {
		GLuint id;
		GLuint comp_count;
		vbo(float *buffer, GLuint comp_count, GLsizei count);
		~vbo();
		void bind();
		void unbind();
	};
	struct ibo {
		GLuint id;
		GLuint count;
		ibo(GLuint *buffer, GLsizei count);
		~ibo();
	};
	struct vao {
		GLuint id;
		vao();
		~vao();
		void bind();
		void addBuffer(vbo *buffer, GLuint index);
		void unbind();
	};
}}