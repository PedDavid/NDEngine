#include "../include/ndengine.h"
#include <iostream>

using namespace core;

class Game : public NDEngine {

	input::InputManager *input;

	void init() {
		window = new Window("Swagg", 640, 330);
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

	}
};

int main() {
	//Window window = Window("Hello Window!", 640, 300);
	//input::InputManager input = input::InputManager(state::StateManager());
	//window.setInputManager(&input);
	//class CommandA : public Command{
	//	Window *win;
	//public:
	//	CommandA(Window *win) : win(win) {}
	//	void execute() { win->close(); }
	//};
	//input.setCommand(GLFW_KEY_ESCAPE, new CommandA(&window));
	//glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	//while (!window.closed()) {
	//	window.clear();
	//	glBegin(GL_TRIANGLES);
	//	glColor3f(0.1, 0.2, 0.3);
	//	glVertex3f(0, 0.5, 0);
	//	glVertex3f(-0.5, -0.5, 0);
	//	glVertex3f(0.5, -0.5, 0);
	//	glEnd();
	//	window.update();
	//}
	//return 0;
	Game game;
	game.start();
	return 0;
}