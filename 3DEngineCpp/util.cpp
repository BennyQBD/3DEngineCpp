#include "util.h"
#include <SDL2/SDL.h>
//#include "sdl_backend.h"

void Util::sleep(int milliseconds)
{
	SDL_Delay(milliseconds);
	//SDLDelay(milliseconds);
}
