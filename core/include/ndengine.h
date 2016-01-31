#pragma once

#include "..\src\window\window.h"

#include "..\src\math\mat4.h"
#include "..\src\math\vec2.h"
#include "..\src\math\vec3.h"
#include "..\src\math\vec4.h"

#include "..\src\util\timer.h"

namespace core {
	class NubDevEngine {

	private:
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;
		std::vector<Window*> m_Windows;

	protected:
		NubDevEngine() : m_FramesPerSecond(0), m_UpdatesPerSecond(0) {	}

		virtual ~NubDevEngine() {
			for (Window *m_Window : m_Windows) {
				delete m_Window;
			}
		}

		Window *createWindow(const char *name, int width, int height) {
			m_Windows.push_back(new Window(name, width, height));
			return m_Windows.back();
		}


	public:
		void start() {
			init();
			run();
			terminate();
		}

	protected:
		//Runs once upon initialization
		virtual void init() = 0;
		//Runs once per second
		virtual void tick() { }
		//Runs a set amount of times per second
		virtual void update() { }
		//Runs as fast as possible(unless the frame rate is capped)
		virtual void render() = 0;

		inline unsigned int getFPS() { return m_FramesPerSecond; }
		inline unsigned int getUPS() { return m_UpdatesPerSecond; }

	private:

		void run() {
			timer::Timer timer;

			float updateTime = 0.0f;
			float tickTime = 0.0f;

			float updateBrake = 1.0f / 60.0f;
			float tickBrake = 1.0f;

			unsigned int frames = 0;
			unsigned int updates = 0;

			while (!m_Window->closed()) {
				m_Window->clear();

				if ((timer.elapsed() - updateTime) > updateBrake) {
					updateTime += updateBrake;
					updates++;
					update();
				}

				render();
				frames++;
				m_Window->update();

				if ((timer.elapsed() - tickTime) > tickBrake) {
					tickTime += tickBrake;
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = 0;
					updates = 0;
					tick();
				}
			}
		}

		void terminate() {

		}
	};
}