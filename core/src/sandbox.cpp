<<<<<<< HEAD
=======
#include <iostream>
>>>>>>> 66ce75b9f3ff8154094f462204ecf2e6df26e8f1
#include "math\mat4.h"
#include "logger\log.h"
#include "util\timer.h"
#include "window\window.h"

<<<<<<< HEAD
#include <CL\cl2.hpp>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

=======
>>>>>>> 66ce75b9f3ff8154094f462204ecf2e6df26e8f1
using namespace core;

int main() {
	Window window = Window("Hello Window!", 640, 300);
	std::cout << std::string("[OpenGL] v") << (char*)glGetString(GL_VERSION) << std::endl;
	std::cout << std::string("[GLSL] v") << (char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
<<<<<<< HEAD
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
=======
	glClearColor(1.0, 0.3, 0.8, 1.0);
>>>>>>> 66ce75b9f3ff8154094f462204ecf2e6df26e8f1
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