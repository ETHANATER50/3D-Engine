#pragma once
#include <chrono>

namespace ew {
	class Timer {
	public:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = std::chrono::duration<clock::rep, std::nano>;

	public:
		Timer() : timePoint{ clock::now() } {}

		void reset();
		clock::rep elapsedTicks();
		clock::rep ticksPerSecond();

		double elapsedSeconds();

	protected:
		clock::time_point timePoint;
	};

	class FrameTimer : public Timer{
	public:
		void tick();

		float deltaTime() { return dt; };

	protected:
		float dt{ 0 };
		
	};
}