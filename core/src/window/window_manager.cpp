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

	Window *WindowManager::getWindow() {
		return m_Window;
	}

	void WindowManager::setWindow(const char *name) {
		std::map<const char*, Window*>::iterator it;
		it = m_Map.find(name);
		if (it == m_Map.end()) {
			LOG(Error, "MapManager", "No Window with name found");
		} else {
			m_Window = it->second;
		}
	}

	void WindowManager::close() {
		size_t deleted = m_Map.erase(m_Window->m_Title);
		delete m_Window;
		m_Window = m_Map.begin()->second;
	}

	void WindowManager::clear() {
		for (std::pair<const char*, Window *> pair : m_Map) {
			pair.second->clear();
		}
	}

	void WindowManager::update() {
		for (std::pair<const char*, Window *> pair : m_Map) {
			pair.second->update();
		}
	}

	bool WindowManager::closed() {
		if (m_Map.empty()) {
			terminate();
			return true;
		} 
		return false;
	}

	void WindowManager::terminate() {
		glfwTerminate();
	}
}
