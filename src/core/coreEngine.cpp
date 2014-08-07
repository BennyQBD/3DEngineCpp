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

#include "coreEngine.h"
#include "timing.h"
#include "../rendering/window.h"
#include "input.h"
#include "util.h"
#include "game.h"

#include <stdio.h>

CoreEngine::CoreEngine(double frameRate, Window* window, RenderingEngine* renderingEngine, Game* game) :
	m_isRunning(false),
	m_frameTime(1.0/frameRate),
	m_window(window),
	m_renderingEngine(renderingEngine),
	m_game(game)
{
	//We're telling the game about this engine so it can send the engine any information it needs
	//to the various subsystems.
	m_game->SetEngine(this);
	
	//Game is initialized here because this is the point where all rendering systems
	//are initialized, and so creating meshes/textures/etc. will not fail due
	//to missing context.
	m_game->Init(*m_window);
}

void CoreEngine::Start()
{
	if(m_isRunning)
	{
		return;
	}
		
	m_isRunning = true;

	double lastTime = Time::GetTime(); //Current time at the start of the last frame
	double frameCounter = 0;           //Total passed time since last frame counter display
	double unprocessedTime = 0;        //Amount of passed time that the engine hasn't accounted for
	int frames = 0;                    //Number of frames rendered since last

	ProfileTimer sleepTimer;
	ProfileTimer swapBufferTimer;
	ProfileTimer windowUpdateTimer;
	while(m_isRunning)
	{
		bool render = false;           //Whether or not the game needs to be rerendered.

		double startTime = Time::GetTime();       //Current time at the start of the frame.
		double passedTime = startTime - lastTime; //Amount of passed time since last frame.
		lastTime = startTime;

		unprocessedTime += passedTime;
		frameCounter += passedTime;

		//The engine displays profiling statistics after every second because it needs to display them at some point.
		//The choice of once per second is arbitrary, and can be changed as needed.
		if(frameCounter >= 1.0)
		{
			double totalTime = ((1000.0 * frameCounter)/((double)frames));
			double totalMeasuredTime = 0.0;
			
			totalMeasuredTime += m_game->DisplayInputTime((double)frames);
			totalMeasuredTime += m_game->DisplayUpdateTime((double)frames);
			totalMeasuredTime += m_renderingEngine->DisplayRenderTime((double)frames);
			totalMeasuredTime += sleepTimer.DisplayAndReset("Sleep Time: ", (double)frames);
			totalMeasuredTime += windowUpdateTimer.DisplayAndReset("Window Update Time: ", (double)frames);
			totalMeasuredTime += swapBufferTimer.DisplayAndReset("Buffer Swap Time: ", (double)frames);
			totalMeasuredTime += m_renderingEngine->DisplayWindowSyncTime((double)frames);
			
			printf("Other Time:                             %f ms\n", (totalTime - totalMeasuredTime));
			printf("Total Time:                             %f ms\n\n", totalTime);
			frames = 0;
			frameCounter = 0;
		}

		//The engine works on a fixed update system, where each update is 1/frameRate seconds of time.
		//Because of this, there can be a situation where there is, for instance, a fixed update of 16ms, 
		//but 20ms of actual time has passed. To ensure all time is accounted for, all passed time is
		//stored in unprocessedTime, and then the engine processes as much time as it can. Any
		//unaccounted time can then be processed later, since it will remain stored in unprocessedTime.
		while(unprocessedTime > m_frameTime)
		{
			windowUpdateTimer.StartInvocation();
			m_window->Update();
			
			if(m_window->IsCloseRequested())
			{
				Stop();
			}
			windowUpdateTimer.StopInvocation();
			
			//Input must be processed here because the window may have found new
			//input events from the OS when it updated. Since inputs can trigger
			//new game actions, the game also needs to be updated immediately 
			//afterwards.
			m_game->ProcessInput(m_window->GetInput(), (float)m_frameTime);
			m_game->Update((float)m_frameTime);
			
			//Since any updates can put onscreen objects in a new place, the flag
			//must be set to rerender the scene.
			render = true;

			unprocessedTime -= m_frameTime;
		}

		if(render)
		{
			m_game->Render(m_renderingEngine);
			
			//The newly rendered image will be in the window's backbuffer,
			//so the buffers must be swapped to display the new image.
			swapBufferTimer.StartInvocation();
			m_window->SwapBuffers();
			swapBufferTimer.StopInvocation();
			frames++;
		}
		else
		{
			//If no rendering is needed, sleep for some time so the OS
			//can use the processor for other tasks.
			sleepTimer.StartInvocation();
			Util::Sleep(1);
			sleepTimer.StopInvocation();
		}
	}
}

void CoreEngine::Stop()
{
	m_isRunning = false;
}

