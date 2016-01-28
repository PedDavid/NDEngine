#pragma once

class Window {

private:
	GLFWwindow *window;
	const char *m_name;
	const size_t m_Width, m_Height;

public:
	Window(const char *name, size_t width, size_t height);
	~Window();
	void update() const;

private:
	void init();

};