#ifndef TIME_H
#define TIME_H

class Time
{
public:
	static double GetTime();
	static double GetDelta();

	static void SetDelta(double value);
protected:
private:
	static double s_delta;
};

#endif
