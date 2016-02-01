#include "window_manager.h"

#include "../logger/log.h"

namespace core {

	WindowManager::WindowManager(){
		glfwInit();
	}
	WindowManager::~WindowManager() { }

	void WindowManager::addWindow(const char* name, int width, int height) {
		Window *tempWindow = new Window(name, width, height);
		m_Map.insert(std::pair<const char*, Window*>(name, tempWindow));
		if (m_Window == NULL) 
			m_Window = tempWindow;
	}

	void WindowManager::setWindow(const char *name) {
		Window *tempWindow = getWindow(name);
		if (tempWindow != NULL) m_Window = tempWindow;
	}

	Window *WindowManager::getWindow(const char *name) {
		auto it = m_Map.find(name);
		if (it == m_Map.end()) {
			LOG(Error, "MapManager", "No Window with name found");
			return NULL;
		}
		else {
			return it->second;
		}
	}

	Window *WindowManager::getWindow() {
		return m_Window;
	}

	void WindowManager::close(Window *window) {
		size_t deleted = m_Map.erase(m_Window->m_Title);
		delete m_Window;
		m_Window = m_Map.begin()->second;
	}

	void WindowManager::close() {
		close(m_Window);
	}

	void WindowManager::clear() {
		for (auto it : m_Map) {
			it.second->clear();
		}
	}

	void WindowManager::update() {
		for (auto it : m_Map) {
			it.second->update();
		}
	}

	bool WindowManager::closed() {
		/* THIS CODE IS BUGGED */
		bool toClose = true;
		for (auto it = m_Map.begin(); it != m_Map.end();) {
			if (!(Window *)it->second->closed()) {
				toClose = false;
				++it;
			} else {
				Window *tempWindow = (Window *)it->second;
				it++;
				close(tempWindow);
			}
		}
		return toClose;
	}

	void WindowManager::terminate() {
		glfwTerminate();
	}
}
