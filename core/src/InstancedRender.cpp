#include "..\include\NDEngine.h"
#include <iostream>
#include "logger\log.h"
#include "util\file.h"
#include "util\directory.h"

#include "graphics\shader.h"
#include "graphics\buffers.h"
#include "graphics\sprite_renderer.h"

using namespace core;

class InstancedRenderTest : public NDEngine {

	input::InputManager *inputx;
	graphics::Shader *shader;

	void init() {
		window = new Window("Hello Window", 1280, 720);

		math::mat4 ortho = math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
		shader = new graphics::Shader("res/simple.vert", "res/simple.frag");
		shader->enable();
		shader->setUniformMat4("pr_matrix", ortho);
		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

		GLfloat vertices[] = {
			0.0f, 0.0f,
			0.0f, 0.1f,
			0.1f, 0.1f,
			0.1f, 0.0f,
		};
		GLuint elements[] = { 0, 2, 1, 0, 3, 2 };
		GLfloat *offsets = new GLfloat[1000000];
		int count = 0;
		for (int i = 0; i < 160; i++) {
			for (int c = 0; c < 90; c++) {
				offsets[count++] = 0.2f * i;
				offsets[count++] = 0.2f * c;
			}
			std::cout << count << " " << i << std::endl;
		}

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GLuint vbo[2];
		glGenBuffers(2, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), offsets, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribDivisor(1, 1);
		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	}

	void update() {

	}

	void tick() {
		std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
	}

	void render() {
		double x, y;
		window->getCursorPosition(&x, &y);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0, 30000);
	}
};

int main() {
	InstancedRenderTest game;
	game.start();
	return 0;
}