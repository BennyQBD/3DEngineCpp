#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <string>

class Window
{
public:
	static void Create(int width, int height, const std::string& title);
	static void Render();
	static void Dispose();

	static bool IsCloseRequested();
	static int GetWidth();
	static int GetHeight();
	static float GetAspect();
	static const std::string& GetTitle();

	static void SetFullScreen(bool value);
protected:
private:
	static int s_width;
	static int s_height;
	static std::string s_title;
};

#endif
