#include "window.h"
#include <SDL.h>
#include <GL/glew.h>
#include "sdl_backend.h"

int Window::m_width = 0;
int Window::m_height = 0;
std::string Window::m_title = "Title";

void Window::create(int width, int height, const std::string& title)
{
	Window::m_width = width;
	Window::m_height = height;
	Window::m_title = title;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	SDLCreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false);

	GLenum res = glewInit();
	if(res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	}
}

void Window::render()
{
	SDLSwapBuffers();
}

void Window::dispose()
{
	SDLDestroyWindow();
	SDL_Quit();
}

bool Window::isCloseRequested()
{
	return SDLGetIsCloseRequested();
}

void Window::setFullScreen(bool value)
{
	SDLSetWindowFullscreen(value);
}

int Window::getWidth()
{
	return m_width;
}

int Window::getHeight()
{
	return m_height;
}

const std::string& Window::getTitle()
{
	return m_title;
}