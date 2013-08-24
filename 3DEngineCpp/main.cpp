#include "main.h"
#include <stdio.h>

#include "window.h"
#include "time.h"
#include "input.h"
#include "renderUtil.h"
#include "util.h"

const static int WIDTH = 800;
const static int HEIGHT = 600;
const static char* TITLE = "3D Engine";
const static double FRAME_CAP = 1000.0;
const static bool IGNORE_FRAME_CAP = true;

Main::Main()
{
	RenderUtil::initGraphics();
	isRunning = false;
}

Main::~Main()
{
	Window::dispose();
}

void Main::start()
{
	if(isRunning)
		return;

	run();
}

void Main::stop()
{
	if(!isRunning)
		return;

	isRunning = false;
}

void Main::run()
{
	isRunning = true;

	const double frameTime = 1.0 / FRAME_CAP;

	double lastTime = Time::getTime();
	double unprocessedTime = 0;
	double frameCounter = 0;
	int frames = 0;

	while(isRunning)
	{
		bool render = false;

		double startTime = Time::getTime();
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

			if(Window::isCloseRequested())
				isRunning = false;

			Time::setDelta(frameTime);
			Input::update();

			game.input();
			game.update();

			unprocessedTime -= frameTime;
		}

		if(render || IGNORE_FRAME_CAP)
		{
			RenderUtil::clearScreen();
			game.render();
			Window::render();
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
	Window::create(WIDTH,HEIGHT,(char*)TITLE);

	Main main;

	main.start();

	return 0;
}