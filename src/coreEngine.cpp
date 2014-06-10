#include "coreEngine.h"
#include "timing.h"
#include "window.h"
#include "input.h"
#include "util.h"
#include "game.h"

#include <stdio.h>

CoreEngine::CoreEngine(int width, int height, double frameRate, Game* game) :
	m_isRunning(false),
	m_width(width),
	m_height(height),
	m_frameTime(1.0/frameRate),
	m_game(game),
	m_renderingEngine(NULL) 
{
	m_game->SetEngine(this);
}
	
CoreEngine::~CoreEngine()
{
	if(m_window) delete m_window;
	if(m_renderingEngine) delete m_renderingEngine;
}

void CoreEngine::CreateWindow(const std::string& title)
{
	m_window = new Window(m_width, m_height, title);
	m_renderingEngine = new RenderingEngine(*m_window);
}

void CoreEngine::Start()
{
	if(m_isRunning)
	{
		return;
	}
		
	Run();
}

void CoreEngine::Stop()
{
	if(!m_isRunning)
	{
		return;
	}
		
	m_isRunning = false;
}

void CoreEngine::Run()
{
	m_isRunning = true;

	m_game->Init(*m_window);

	double lastTime = Time::GetTime();
	double unprocessedTime = 0;
	double frameCounter = 0;
	int frames = 0;

	while(m_isRunning)
	{
		bool render = false;

		double startTime = Time::GetTime();
		double passedTime = startTime - lastTime;
		lastTime = startTime;

		unprocessedTime += passedTime;
		frameCounter += passedTime;

		if(frameCounter >= 1.0)
		{
			printf("%i\n",frames);
			frames = 0;
			frameCounter = 0;
		}

		while(unprocessedTime > m_frameTime)
		{
			render = true;

			if(m_window->IsCloseRequested())
			{
				Stop();
			}

			m_window->Update();

			m_game->ProcessInput(m_window->GetInput(), (float)m_frameTime);
			m_game->Update((float)m_frameTime);

			unprocessedTime -= m_frameTime;
		}

		if(render)
		{
			m_game->Render(m_renderingEngine, *m_mainCamera);
			m_window->SwapBuffers();
			frames++;
		}
		else
		{
			Util::Sleep(1);
		}
	}
}

