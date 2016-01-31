#include "input_manager.h"

#include <iostream>
#include "../logger/log.h"

namespace core {	namespace input {
	InputManager::InputManager(state::StateManager manager) : m_StateManager(manager) {	}

	void InputManager::setCommand(int key, Command *command) {
		using namespace std;
		pair<map<int, Command*>::iterator, bool> it = m_Map.insert(pair<int, Command*>(key, command));
		if (it.second == false) {
			ostringstream s;
			s << "Key" << key << "already assigned" << ends;
			LOG(Warn, "Input", s.str().c_str());
		}
	}

	void InputManager::callBack(int key, int scancode, int action, int mods) {
		std::cout << "Key: " << key << " ScanCode: " << scancode << " action: " << action << " mods " << mods << std::endl;
		using namespace std;
		/* Need to handle states, mods and release/repeat/press */
		map<int, Command*>::iterator it = m_Map.find(key);
		if (it != m_Map.end()) {
			it->second->execute();
		}
	}
}}