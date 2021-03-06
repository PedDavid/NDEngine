#pragma once

#include <glew.h>
#include <glfw3.h>

#include "input.h"

namespace core {
	class Window {

	private:
		GLFWwindow *m_Window;
		Input *input;

	public:
		Window(const char *title, size_t width, size_t height);
		~Window();
		void update() const;
		void clear() const;
		void close() const;

		void makeCurrent() const;
		void setVSync(int vSync) const;

		bool closed() const;

		void getCursorPosition(double *x, double *y);
		int getMouseButton(int key);
		int getKey(int key);

	private:
		friend static void window_resize(GLFWwindow *window, int width, int heigth);
		friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		friend static void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
		friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		friend static void error_callback(int error, const char *description);
	};
}