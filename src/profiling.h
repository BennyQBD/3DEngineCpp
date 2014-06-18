#ifndef PROFILING_H_INCLUDED
#define PROFILING_H_INCLUDED

#include <string>

class ProfileTimer
{
public:
	ProfileTimer() :
		m_numInvocations(0),
		m_totalTime(0.0),
		m_startTime(0) {}

	void StartInvocation();
	void StopInvocation();
	
	double DisplayAndReset(const std::string& message, double dividend = 0, int displayedMessageLength = 40);
	double GetTimeAndReset(double dividend = 0);
protected:
private:
	int    m_numInvocations;
	double m_totalTime;
	double m_startTime;
};

#endif // PROFILING_H_INCLUDED
