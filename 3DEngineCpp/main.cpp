#include "coreEngine.h"

int main()
{
	Game game;
	CoreEngine engine(800, 600, 60, &game);
	engine.CreateWindow("3D Game Engine!");
	engine.Start();
	
	return 0;
}
