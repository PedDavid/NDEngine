#pragma once

#include <glew.h>
#include <glfw3.h>

namespace core {
	class Window {

	private:
		GLFWwindow *m_Window;
		const char *m_Title;
		const size_t m_Width, m_Height;

	public:
		Window(const char *title, size_t width, size_t height);
		~Window();
		void update() const;
		void close() const;

		void makeCurrent() const;
		void setVSync(bool vSync) const;

		bool closed() const;

	private:
		void init();

		friend void error_callback(int error, const char *description);
	};
}