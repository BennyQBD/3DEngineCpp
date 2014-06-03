#include "input.h"
#include "window.h"
#include <SDL2/SDL.h>
#include <cstring>

Input::Input(Window* window) :
	m_mouseX(0),
	m_mouseY(0),
	m_window(window)
{
	memset(m_inputs, 0, NUM_KEYS * sizeof(bool));
	memset(m_downKeys, 0, NUM_KEYS * sizeof(bool));
	memset(m_upKeys, 0, NUM_KEYS * sizeof(bool));
	
	memset(m_mouseInput, 0, NUM_MOUSEBUTTONS * sizeof(bool));
	memset(m_downMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
	memset(m_upMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
}

void Input::SetCursor(bool visible) const
{
	if(visible)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}

void Input::SetMousePosition(const Vector2f& pos) const
{
	SDL_WarpMouseInWindow(m_window->GetSDLWindow(), (int)pos.GetX(), (int)pos.GetY());
//	SDLSetMousePosition((int)pos.GetX(), (int)pos.GetY());
}
