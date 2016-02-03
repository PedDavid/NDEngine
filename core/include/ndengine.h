#pragma once

#include "../src/window/window_manager.h"
#include "../src/util/timer.h"

#include <math/mat4.h>
#include <math/vec2.h>

namespace core {
	class NDEngine {

	private:
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;

	public:
		Window *window;

	protected:
		NDEngine() : m_FramesPerSecond(0), m_UpdatesPerSecond(0) {	}

		virtual ~NDEngine() {	}

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

			while (!window->closed()) {
				window->clear();

				if ((timer.elapsed() - updateTime) > updateBrake) {
					updateTime += updateBrake;
					updates++;
					update();
				}

				render();
				frames++;
				window->update();

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