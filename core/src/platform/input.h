#pragma once

namespace core {

	class Input {
		
	public:

		void Input::cursorPositionCallback(double ypos, double xpos);

		void Input::mouseButtonCallback(int button, int action, int mods);

		void Input::mouseScrollCallback(double xoff, double yoff);

		void Input::keyCallback(int key, int scancode, int action, int mods);

	};
}