#include "time.h"

std::chrono::system_clock::time_point Time::m_epoch = std::chrono::high_resolution_clock::now();
double Time::m_delta = 0.0;

double Time::getTime()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_epoch).count() / 1000000000.0;
}

double Time::getDelta()
{
	return m_delta;
}

void Time::setDelta(double value)
{
	Time::m_delta = value;
}