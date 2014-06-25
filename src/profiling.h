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

#ifndef PROFILING_H_INCLUDED
#define PROFILING_H_INCLUDED

#include <string>

#define PROFILING_DISABLE_MESH_DRAWING 0
#define PROFILING_DISABLE_SHADING 0
#define PROFILING_SET_1x1_VIEWPORT 0
#define PROFILING_SET_2x2_TEXTURE 0

class ProfileTimer
{
public:
	ProfileTimer() :
		m_numInvocations(0),
		m_totalTime(0.0),
		m_startTime(0) {}

	void StartInvocation();
	void StopInvocation();
	
	double DisplayAndReset(const std::string& message, double divisor = 0, int displayedMessageLength = 40);
	double GetTimeAndReset(double divisor = 0);
protected:
private:
	int    m_numInvocations;
	double m_totalTime;
	double m_startTime;
};

#endif // PROFILING_H_INCLUDED
