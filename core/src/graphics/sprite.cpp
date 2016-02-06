#include "sprite.h"

namespace core {	namespace graphics {
	Sprite::Sprite(math::vec3 position, math::vec2 size, unsigned int color, Shader *shader)
		: m_Position(position), m_Size(size), m_Color(color), shader(shader) {

		m_vao = new vao();
		m_vao->bind();
		GLfloat vertices[] = {
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f
		};

		float red = ((color & 0xFF000000) >> 24) / 255.0f;
		float green = ((color & 0x00FF0000) >> 16)/ 255.0f;
		float blue = ((color & 0x0000FF00) >> 8)/ 255.0f;
		float alpha = (color & 0x000000FF)	/ 255.0f;
		GLfloat colors[] = {
			red, green, blue, alpha,
			red, green, blue, alpha,
			red, green, blue, alpha,
			red, green, blue, alpha
		};

		m_vao->addBuffer(new vbo(vertices, 3, 4 * 3), 0);
		m_vao->addBuffer(new vbo(colors, 4, 4 * 4), 1);

		GLuint elements[] = { 0, 1, 2, 2, 3, 0 };
		new ibo(elements, 6);
		elem_count = 6;
	}

	Sprite::~Sprite() {
		delete m_vao;
	}
}}