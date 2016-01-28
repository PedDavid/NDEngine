#include <glfw3.h>

#include "window.h"

Window::Window(const char *name, size_t width, size_t height) 
	: m_name(name), m_Width(width), m_Height(height) {
}