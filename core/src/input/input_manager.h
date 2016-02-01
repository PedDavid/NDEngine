#pragma once

#include "../state/state_manager.h"
#include "command.h"
#include <map>

namespace core {	namespace input {
	class InputManager{
	public:
		state::StateManager m_StateManager;
		std::map<int, Command*> m_Map;

		InputManager(state::StateManager manager);

		void setCommand(int key, Command *command);

		void cursorPositionCallback(double xpos, double ypos);
		void mouseButtonCallback(int button, int action, int mods);
		void mouseScrollCallback(double xoff, double yoff);
		void keyCallback(int key, int scancode, int action, int mods);
	};
}}