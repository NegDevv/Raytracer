#include "Timer.h"

Timer::Timer()
{
	start = std::chrono::steady_clock::now();
}

/// <returns>Returns time elapsed in milliseconds as a double</returns>
const double Timer::Time()
{
	double ms = std::chrono::nanoseconds{ std::chrono::steady_clock::now() - start }.count() / 1000000.0f;
	used = true;
	return ms;
}


/// <returns>Returns time elapsed in milliseconds as a formatted string</returns>
const std::string Timer::Time_str()
{
	double ms = std::chrono::nanoseconds{ std::chrono::steady_clock::now() - start }.count() / 1000000.0f;
	std::string ret = "<" + std::to_string(ms) + "ms> ";
	used = true;
	return ret;
}

Timer::~Timer()
{
	// If the timer has not been used to print/return time before destructor print it here(exiting scope)
	if (!used)
	{
		double ms = std::chrono::nanoseconds{ std::chrono::steady_clock::now() - start }.count() / 1000000.0f;
		std::cout << "<" + std::to_string(ms) + "ms> \n\n";
	}
}