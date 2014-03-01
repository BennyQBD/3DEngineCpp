#ifndef COREENGINE_H
#define COREENGINE_H

#include "game.h"
#include <string>

class CoreEngine
{
public:
	CoreEngine(int width, int height, double frameRate, Game* game);
	virtual ~CoreEngine();
	
	void CreateWindow(const std::string& title);
	
	void Start();
	void Stop();
	
protected:
private:
	CoreEngine(const CoreEngine& other) {}
	void operator=(const CoreEngine& other) {}
	
	void Run();
	
	bool m_isRunning;
	int m_width;
	int m_height;
	double m_frameTime;
	Game* m_game;
};

#endif // COREENGINE_H
