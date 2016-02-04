#include "..\include\NDEngine.h"
#include <iostream>
#include "logger\log.h"
#include "util\file.h"
#include "util\directory.h"

#include "graphics\shader.h"
#include "graphics\buffers.h"

using namespace core;

class Game : public NDEngine {

	util::DirectoryWatcher *watcher;
	input::InputManager *inputx;
	graphics::Shader *shader;

	void hi() {
		shader->disable();
		delete shader;
		shader = new graphics::Shader("res/basic.vert", "res/basic.frag");
		shader->enable();
		shader->setUniformMat4("pr_matrix", math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	}

	void init() {
		watcher = new util::DirectoryWatcher("C:/Users/Pedro Admin/Documents/visual studio 2015/Projects/NDEngine/core/res/");
		window = new Window("Hello Window", 1280, 720);
		inputx = new input::InputManager(state::StateManager());
		class CommandA : public Command {
			Window *win;
			public:
			CommandA(Window *win) : win(win) {}
			void execute() { win->close(); }
		};
		inputx->setCommand(GLFW_KEY_ESCAPE, new CommandA(window));
		window->setInputManager(inputx);

		math::mat4 ortho = math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
		shader = new graphics::Shader("res\\basic.vert", "res\\basic.frag");
		shader->enable();
		shader->setUniformMat4("pr_matrix", ortho);

		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

		using namespace math;

		GLuint elements[] = {
			0, 1, 2,
			0, 3, 1
		};

		vec3 vertices[] = {
			vec3(6.0, 3.5, 0), 
			vec3(10.0, 5.5, 0), 
			vec3(6.0, 5.5, 0),
			vec3(10.0, 3.5, 0)
		};
		vec4 colors[] = {
			vec4(1.0, 0.8, 0.5, 1.0), 
			vec4(1.0, 0.8, 0.5, 1.0),
			vec4(0.2, 1.0, 1.0, 1.0), 
			vec4(0.2, 1.0, 1.0, 1.0)
		};

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GLuint vbo[2];
		glGenBuffers(2, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		std::cout << sizeof(colors) << std::endl;
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(vao);
	}

	void update() {

	}

	void tick() {
		std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
		if (watcher->updated()) {
			hi();
		}
	}

	void render() {
		double x, y;
		window->getCursorPosition(&x, &y);
		shader->setUniform2f("light_pos", math::vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
};

int main() {
	Game game;
	game.start();
	return 0;
}