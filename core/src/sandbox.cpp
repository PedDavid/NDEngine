#include "math\mat4.h"
#include "logger\log.h"
#include "util\timer.h"
#include "window\window.h"


#include "input\input_manager.h"
#include "input\command.h"
#include <iostream>

using namespace core;

int main() {
	Window window = Window("Hello Window!", 640, 300);
	input::InputManager input = input::InputManager(state::StateManager());
	window.setInputManager(&input);
	class CommandA : public Command{
		Window *win;
	public:
		CommandA(Window *win) : win(win) {}
		void execute() { win->close(); }
	};
	input.setCommand(GLFW_KEY_ESCAPE, new CommandA(&window));
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	while (!window.closed()) {
		window.clear();
		glBegin(GL_TRIANGLES);
		glColor3f(0.1, 0.2, 0.3);
		glVertex3f(0, 0.5, 0);
		glVertex3f(-0.5, -0.5, 0);
		glVertex3f(0.5, -0.5, 0);
		glEnd();
		window.update();
	}
	return 0;
}