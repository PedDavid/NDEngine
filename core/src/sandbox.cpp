#include <iostream>
#include <glfw3.h>
#include "math\mat4.h"
#include "util\log.h"
#include "util\timer.h"

int main() {
	GLFWwindow *window;
	std::cout << "Hello World!" << std::endl;
	if (!glfwInit()) {
		std::cout << "GLFW Error!" << std::endl;
		return -1;
	}
	window = glfwCreateWindow(640, 480, "Hello World!", 0, 0);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	util::Timer timer;
	util::Timer timer2;
	LOG_SUCCESS("cool");
	std::cout << timer.elapsed() << std::endl;
	std::cout << timer2.elapsed() << std::endl;
	math::mat4 vector = math::mat4::orthographic(0.0f, 10.0f, 0.0f, 5.0f, 0.1f, 100.0f);
	std::cout << vector << std::endl;
	vector.multiply(vector);
	std::cout << vector << std::endl;
	system("PAUSE");
	return 0;
}