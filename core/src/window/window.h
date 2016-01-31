#pragma once

#include <glew.h>
#include <glfw3.h>

#include "../input/input_manager.h"

namespace core {
	class Window {

	private:
		GLFWwindow *m_Window;
		input::InputManager *m_InputManager;

		const char *m_Title;
		const size_t m_Width, m_Height;

	public:
		Window(const char *title, size_t width, size_t height);
		~Window();
		void update() const;
		void clear() const;
		void close() const;

		void makeCurrent() const;
		void setVSync(bool vSync) const;

		bool closed() const;

		void setInputManager(input::InputManager *manager) {
			m_InputManager = manager;
		}

	private:
		void init();

		friend void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		friend void error_callback(int error, const char *description);
	};
}