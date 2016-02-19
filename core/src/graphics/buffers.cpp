#include "buffers.h"
#include <iostream>

namespace core {	namespace graphics {
	
	/* ******** VERTEX ARRAY OBJECT ******* */

	vao::vao() {
		glGenVertexArrays(1, &id);
	}
	vao::~vao() {
		glDeleteVertexArrays(1, &id);
	}
	void vao::addBuffer(vbo *buffer, GLuint index) {
		glVertexAttribPointer(index, buffer->comp_count, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(index);
	}
	void vao::bind() {
		glBindVertexArray(id);
	}
	void vao::unbind() {
		glBindVertexArray(0);
	}

	/* ******** VERTEX BUFFER OBJECT ******* */

	vbo::vbo(GLfloat *buffer, GLuint comp_count, GLsizei count) : comp_count(comp_count){
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, count * comp_count * sizeof(GLfloat), buffer, GL_STATIC_DRAW);
	}
	vbo::~vbo() {
		glDeleteBuffers(1, &id);
	}
	void vbo::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	void vbo::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/* ******** INDEX BUFFER OBJECT ******* */

	ibo::ibo(GLuint *buffer, GLsizei count) : count(count) {
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), buffer, GL_STATIC_DRAW);
	}
	ibo::~ibo() {
		glDeleteBuffers(1, &id);
	}
	void ibo::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
	void ibo::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}}