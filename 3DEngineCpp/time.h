#ifndef TIME_H
#define TIME_H

#include <chrono>

class Time
{
public:
	static double getTime();
	static double getDelta();

	static void setDelta(double value);
protected:
private:
	static double m_delta;
	static std::chrono::system_clock::time_point m_epoch;
};

#endif