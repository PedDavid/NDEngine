#pragma once

#include <glew.h>

namespace core {	namespace graphics {

	struct vbo {
		GLuint id;
		GLuint comp_count;
		vbo();
		~vbo();
		void bind();
		void unbind();
	};
	struct ibo {
		GLuint id;
		GLuint count;
	};
	struct vao {
		GLuint id;
		vao();
		~vao();
		void bind();
		void addBuffer(vbo *buffer);
		void addElementBuffer(ibo *buffer);
		void unbind();
	};
}}