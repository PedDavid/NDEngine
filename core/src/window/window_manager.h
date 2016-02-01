#pragma once

#include "window.h"

namespace core {
	class WindowManager {
	private:
		std::map<const char *, Window*> m_Map;
		Window *m_Window;
	public:
		WindowManager();
		~WindowManager();

	public:
		void addWindow(const char *name, int width, int height);
		void setWindow(const char *name);
		Window *getWindow(const char *name);
		Window *getWindow();
		void close(Window *window);
		void close();

		void clear();
		void update();
		bool closed();

	private:
		void terminate();
	};
}