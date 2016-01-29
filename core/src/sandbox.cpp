#include <iostream>
#include "math\mat4.h"
#include "logger\log.h"
#include "util\timer.h"
#include "window\window.h"

using namespace core;

int main() {
	std::cout << "Hello World!" << std::endl;
	LOG_WARN("HELLO LOGS");
	Window window = Window("Hello Window!", 640, 300);
	while (!window.closed()) {
		window.update();
	}
	system("PAUSE");
	return 0;
}