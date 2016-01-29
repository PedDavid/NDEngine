#pragma once 

#include <chrono>

namespace core {	namespace timer {
	class Timer {

	private:
		typedef std::chrono::high_resolution_clock hrClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<hrClock> m_Start;

	public:
		Timer() {
			reset();
		}

		void reset() {
			m_Start = hrClock::now();
		}

		float elapsed() {
			return std::chrono::duration_cast<milliseconds_type>(hrClock::now() - m_Start).count() / 1000.0f;
		}
	};
}}