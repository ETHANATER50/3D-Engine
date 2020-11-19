#include "pch.h"
#include "Timer.h"
namespace ew {
	void Timer::reset() {
		timePoint = clock::now();
	}
	Timer::clock::rep ew::Timer::elapsedTicks() {

		clock_duration duration = clock::now() - timePoint;
		return duration.count();
	}

	Timer::clock::rep ew::Timer::ticksPerSecond() {
		return clock_duration::period::den;
	}

	double Timer::elapsedSeconds()
	{
		return elapsedTicks() / static_cast<double>(ticksPerSecond());
	}

	void FrameTimer::tick() {
		dt = static_cast<float>(elapsedSeconds());
		timePoint = clock::now();

	}

}
