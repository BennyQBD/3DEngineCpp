#include "coreEngine.h"
#include "testGame.h"

int main()
{
	TestGame game;
	CoreEngine engine(800, 600, 60, &game);
	engine.CreateWindow("3D Game Engine!");
	engine.Start();
	
	return 0;
}
