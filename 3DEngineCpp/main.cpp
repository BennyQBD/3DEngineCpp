#include "main.h"
#include <stdio.h>

#include "window.h"
#include "time.h"
#include "input.h"
#include "renderUtil.h"
#include "util.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "3D Engine"
#define FRAME_CAP 60.0
#define IGNORE_FRAME_CAP true

Main::Main()
{
	RenderUtil::InitGraphics();
	m_isRunning = false;
}

Main::~Main()
{
	Window::Dispose();
}

void Main::Start()
{
	if(m_isRunning)
		return;

	Run();
}

void Main::Stop()
{
	if(!m_isRunning)
		return;

	m_isRunning = false;
}

void Main::Run()
{
	m_isRunning = true;

	const double frameTime = 1.0 / FRAME_CAP;

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

		while(unprocessedTime > frameTime)
		{
			render = true;

			if(Window::IsCloseRequested())
				m_isRunning = false;

			Time::SetDelta(frameTime);
			Input::Update();

			m_game.Input();
			m_game.Update();

			unprocessedTime -= frameTime;
		}

		if(render || IGNORE_FRAME_CAP)
		{
			RenderUtil::ClearScreen();
			m_game.Render();
			Window::Render();
			frames++;
		}
		else
		{
			Util::sleep(1);
		}
	}
}

int main()
{
	Window::Create(WIDTH,HEIGHT,(char*)TITLE);

	Main main;

	main.Start();

	return 0;
}
