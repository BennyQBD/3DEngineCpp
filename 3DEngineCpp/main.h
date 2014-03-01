#ifndef MAINCOMPONENT_H
#define MAINCOMPONENT_H

#include "game.h"

class Main
{
public:
	Main();
	virtual ~Main();

	void Start();
	void Stop();
protected:
private:
	Main(Main& main) {}
	void operator=(Main& main) {}
	
	bool m_isRunning;
	Game m_game;

	void Run();
};

#endif
