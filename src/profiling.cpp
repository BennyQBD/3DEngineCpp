/*
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "profiling.h"
#include "timing.h"
#include <cassert>
#include <iostream>

void ProfileTimer::StartInvocation()
{
	m_startTime = Time::GetTime();
}

void ProfileTimer::StopInvocation()
{
	if(m_startTime == 0)
	{
		std::cout << "Error: StopInvocation called without matching start invocation" << std::endl;
		assert(m_startTime != 0);
	}
	
	m_numInvocations++;
	m_totalTime += (Time::GetTime() - m_startTime);
	m_startTime = 0;
}

double ProfileTimer::GetTimeAndReset(double divisor)
{
	divisor = (divisor == 0) ? m_numInvocations : divisor;
	double result = (m_totalTime == 0 && divisor == 0.0) ? 0.0 : (1000.0 * m_totalTime)/((double)divisor);
	m_totalTime = 0.0;
	m_numInvocations = 0;
	
	return result;
}

double ProfileTimer::DisplayAndReset(const std::string& message, double divisor, int displayedMessageLength)
{
	std::string whiteSpace = "";
	for(int i = message.length(); i < displayedMessageLength; i++)
	{
		whiteSpace += " ";
	}
	
	double time = GetTimeAndReset(divisor);
	std::cout << message << whiteSpace << time << " ms" << std::endl;
	return time;
}
