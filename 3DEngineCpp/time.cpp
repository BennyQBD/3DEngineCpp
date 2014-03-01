#include "time.h"
#include <time.h>

#ifdef WIN32
	#define OS_WINDOWS
#else
	#ifdef __linux__
		#define OS_LINUX
	#else
		#if __cplusplus >= 201103L
			#define OS_OTHER_CPP11
		#else
			#define OS_OTHER
		#endif
	#endif
#endif

#ifdef OS_WINDOWS
	#include <Windows.h>
	#include <iostream>
	static double g_freq;
	static bool g_timerInitialized = false;
#endif

#ifdef OS_LINUX
	#include <sys/time.h>
	static const long NANOSECONDS_PER_SECOND = 1000000000L;
#endif

#ifdef OS_OTHER_CPP11
	#include <chrono>
	static std::chrono::system_clock::time_point m_epoch = std::chrono::high_resolution_clock::now();
#endif

double Time::s_delta = 0.0;

double Time::GetTime()
{
	#ifdef OS_WINDOWS
		if(!g_timerInitialized)
		{
			LARGE_INTEGER li;
			if(!QueryPerformanceFrequency(&li))
				std::cerr("QueryPerformanceFrequency failed in timer initialization");
			
			g_freq = double(li.QuadPart);
			g_timerInitialized = true;
		}
	
		LARGE_INTEGER li;
		if(!QueryPerformanceCounter(&li))
			std::cerr("QueryPerformanceCounter failed in get time!");
		
		return double(li.QuadPart)/g_freq;
	#endif

	#ifdef OS_LINUX
		timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		return (double)(((long) ts.tv_sec * NANOSECONDS_PER_SECOND) + ts.tv_nsec)/((double)(NANOSECONDS_PER_SECOND));
	#endif

	#ifdef OS_OTHER_CPP11
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_epoch).count() / 1000000000.0;
	#endif

	#ifdef OS_OTHER
		return (clock())/((double)(CLOCKS_PER_SEC));//std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_epoch).count() / 1000000000.0;
	#endif
}

double Time::GetDelta()
{
	return s_delta;
}

void Time::SetDelta(double value)
{
	Time::s_delta = value;
}
