#include <iostream>
#include "math\mat4.h"
#include "logger\log.h"
#include "util\timer.h"
#include "window\window.h"

using namespace core;

int main() {
	Window window = Window("Hello Window!", 640, 300);
	std::cout << std::string("[OpenGL] v") << (char*)glGetString(GL_VERSION) << std::endl;
	std::cout << std::string("[GLSL] v") << (char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	glClearColor(1.0, 0.3, 0.8, 1.0);
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