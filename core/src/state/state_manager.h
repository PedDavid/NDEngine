#pragma once

#include <vector>

namespace core {	namespace state {
	class StateManager {
	private:
		std::vector<unsigned int> states;
		unsigned int m_State;
	public:
		StateManager() {}
		void addState(int state) {
			states.push_back(state);
			if (states.size() == 1) m_State = state;
		}
		int setState(int state) {
			std::vector<unsigned int>::iterator it = find(states.begin(), states.end(), state);
			return it != states.end() ? (int) *it : -1;
		}
		int getState() {
			if (states.empty()) return -1;
			return m_State;
		}
	};
}}