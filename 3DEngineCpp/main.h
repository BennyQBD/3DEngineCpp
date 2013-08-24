#ifndef MAINCOMPONENT_H
#define MAINCOMPONENT_H

#include "game.h"

class Main
{
public:
	Main();
	~Main();

	void start();
	void stop();
protected:
private:
	bool isRunning;
	Game game;

	void run();
};

#endif