#include "..\include\NDEngine.h"
#include <iostream>
#include "logger\log.h"
#include "util\file.h"

#include "graphics\shader.h"

using namespace core;

class Game : public NDEngine {

	int c = 0;

	input::InputManager *inputx;
	graphics::Shader *shader;

	void hi() {
		shader->disable();
		delete shader;
		shader = new graphics::Shader("res\\basic.vert", "res\\basic.frag");
		shader->enable();
		shader->setUniformMat4("pr_matrix", math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	}

	void init() {
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
		
		glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
		util::directoryWatcher("C:\\Users\\Pedro Admin\\Documents\\visual studio 2015\\Projects\\NDEngine\\core\\res\\", &c);
	}

	void update() {

	}

	void tick() {
		if (c) {
			hi();
			c = 0;
		}
	}

	void render() {
		double x, y;
		window->getCursorPosition(&x, &y);
		shader->setUniform2f("light_pos", math::vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));

		glBegin(GL_TRIANGLES);
		glVertex3f(6.0, 5.5, 0);
		glVertex3f(6.0, 3.5, 0);
		glVertex3f(10.0, 3.5, 0);

		glVertex3f(10.0, 5.5, 0);
		glVertex3f(6.0, 5.5, 0);
		glVertex3f(10.0, 3.5, 0);
		glEnd();
	}
};

int main() {
	Game game;
	game.start();
	return 0;
}