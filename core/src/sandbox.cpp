#include "..\include\NDEngine.h"
#include <iostream>
#include "logger\log.h"

#include "graphics\shader.h"

using namespace core;

class Game : public NDEngine {

	input::InputManager *input;
	graphics::Shader *shader;

	void init() {
		window = new Window("Hello Window", 1280, 720);
		input = new input::InputManager(state::StateManager());
		class CommandA : public Command {
			Window *win;
		public:
			CommandA(Window *win) : win(win) {}
			void execute() { win->close(); }
		};
		input->setCommand(GLFW_KEY_ESCAPE, new CommandA(window));
		window->setInputManager(input);

		math::mat4 ortho = math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

		shader = new graphics::Shader("res\\basic.vert", "res\\basic.frag");
		shader->enable();
		shader->setUniformMat4("pr_matrix", ortho);
		
		glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
	}

	void update() {

	}

	void tick() {
		std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
	}

	void render() {
		double x, y;
		window->getCursorPosition(&x, &y);
		shader->setUniform2f("light_pos", math::vec2((float)(x * 160 / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));

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