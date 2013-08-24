#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <string>

class Window
{
public:
	static void create(int width, int height, const std::string& title);
	static void render();
	static void dispose();

	static bool isCloseRequested();
	static int getWidth();
	static int getHeight();
	static const std::string& getTitle();

	static void setFullScreen(bool value);

protected:
private:
	static int m_width;
	static int m_height;
	static std::string m_title;
};

#endif