#include "window.h"

#include "..\logger\log.h"

namespace core {

	Window::Window(const char *title, size_t width, size_t height) {
		/* TODO : Better Error checking (glfwTerminate always?) */
		if (!glfwInit()) {
			LOG(Fatal, "GLFW", "INIT");
			glfwTerminate();
		}
		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!m_Window) {
			LOG(Fatal, "GLFW", "WINDOW CREATION");
			glfwTerminate();
		}
		makeCurrent();

		/* Set pointer for callbacks and set callbacks */
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, window_resize);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetScrollCallback(m_Window, mouse_scroll_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetErrorCallback(error_callback);
		LOG(Success, "GLFW",  "Window creation");

		/* Give glew extension to GLFW openGL context 
		 *	(this needs to come after window creation) 
		 */
		if (glewInit() != GLEW_OK) {
			LOG(Fatal, "GLEW", "INIT");
			glfwTerminate();
			return;
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		LOG(Success, "GLEW", "INIT");
		LOG(Info, "OpenGL", "Version: %s", glGetString(GL_VERSION));
		LOG(Info, "GLSL", "Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	Window::~Window() {
		glfwDestroyWindow(m_Window);
	}

	void Window::update() const {
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::close() const {
		glfwSetWindowShouldClose(m_Window, GL_TRUE);
	}

	void Window::makeCurrent() const {
		glfwMakeContextCurrent(m_Window);
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_Window) != 0;
	}

	void Window::setVSync(int vSync) const {
		glfwSwapInterval(vSync);
	}

	void Window::getCursorPosition(double *x, double *y) {
		glfwGetCursorPos(m_Window, x, y);
	}

	int Window::getMouseButton(int key) {
		return glfwGetMouseButton(m_Window, key);
	}

	int Window::getKey(int key) {
		return glfwGetKey(m_Window, key);
	}

	static void window_resize(GLFWwindow* window, int width, int heigth) {
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		if (win->input) {
		}
	}

	static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		if (win->input) {
			win->input->cursorPositionCallback(xpos, ypos);
		}
	}

	static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		if (win->input) {
			win->input->mouseButtonCallback(button, action, mods);
		}
	}

	static void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		if (win->input) {
			win->input->mouseScrollCallback(xoffset, yoffset);
		}
	}

	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		if (win->input) {
			win->input->keyCallback(key, scancode, action, mods);
		}
	}

	static void error_callback(int error, const char *description) {
		LOG(Error, "GLFW", "Error: %d | Description: %s", error, description);
	}

}