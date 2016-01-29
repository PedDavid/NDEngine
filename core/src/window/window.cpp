#include "window.h"
#include "..\logger\log.h"

namespace core {
	Window::Window(const char *title, size_t width, size_t height)
		: m_Title(title), m_Width(width), m_Height(height) {
		if (!glfwInit()) {
			LOG_FATAL("[GLFW] INIT");
			glfwTerminate();
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window) {
			LOG_FATAL("[GLFW] WINDOW CREATION");
			glfwTerminate();
		}
		glfwSetWindowUserPointer(m_Window, this);
		makeCurrent();
		//glfwSetFramebufferSizeCallback(m_Window, window_resize);
		//glfwSetKeyCallback(m_Window, key_callback);
		//glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		//glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetErrorCallback(error_callback);
		LOG_SUCCESS("[GLFW] Window creation");

		if (glewInit() != GLEW_OK) {
			LOG_FATAL("[GLEW] INIT");
			glfwTerminate();
			return;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		LOG_SUCCESS("[GLEW] INIT");
		//std::cout << std::string("[OpenGL] v") << (char*)glGetString(GL_VERSION) << std::endl;
		//std::cout << std::string("[GLSL] v") << (char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	}

	Window::~Window() {
		glfwTerminate();
	}

	void Window::update() const {
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::close() const {
		glfwDestroyWindow(m_Window);
	}

	void Window::makeCurrent() const {
		glfwMakeContextCurrent(m_Window);
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_Window) != 0;
	}

	void Window::setVSync(bool vSync) const {
		glfwSwapInterval(vSync ? 1 : 0);
	}

	static void error_callback(int error, const char *description) {
		LOG_ERROR(description);
	}
}