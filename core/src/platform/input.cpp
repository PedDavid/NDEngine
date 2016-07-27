#include "input.h"

#include <iostream> //TODO

namespace core {

	void Input::cursorPositionCallback(double ypos, double xpos) {

	}

	void Input::mouseButtonCallback(int button, int action, int mods) {
		std::cout << "Mouse: Key: " << button << " Action: " << action << " Mods: " << mods << std::endl;
	}

	void Input::mouseScrollCallback(double xoff, double yoff) {
		std::cout << "MouseScroll: X off: " << xoff << " Y off: " << yoff << std::endl;
	}

	void Input::keyCallback(int key, int scancode, int action, int mods) {
		std::cout << "KeyBoard: Key: " << key << " ScanCode: " << scancode << " Action: " << action << " Mods: " << mods << std::endl;
	}

}