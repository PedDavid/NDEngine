#include "../include/ndengine.h"
#include <iostream>

using namespace core;

class Game : public NDEngine {

	input::InputManager *input;

	void init() {
		window = new Window("Hello Window", 640, 330);
		input = new input::InputManager(state::StateManager());
		class CommandA : public Command {
			Window *win;
		public:
			CommandA(Window *win) : win(win) {}
			void execute() { win->close(); }
		};
		input->setCommand(GLFW_KEY_ESCAPE, new CommandA(window));
		window->setInputManager(input);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	}

	void update() {

	}

	void tick() {
		std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
	}

	void render() {
		glBegin(GL_TRIANGLES);
		glColor3f(0.1, 0.2, 0.3);
		glVertex3f(0, 0.5, 0);
		glVertex3f(-0.5, -0.5, 0);
		glVertex3f(0.5, -0.5, 0);
		glEnd();
	}
};

int main() {
	Game game;
	game.start();
	return 0;
}