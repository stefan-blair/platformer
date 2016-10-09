#include "LoaderParams.h"
#include <string>

#pragma once
class Camera
{
public:
	static int getCurrentX();
	static int getCurrentY();
	static bool checkOnScreen(int x, int y);
	static void render(LoaderParams &);
	static void drawText(LoaderParams &params, std::string &text);
	static void setCurrentX(int x);
	static void setCurrentY(int y);
	static void setWidth(int width);
	static void setHeight(int height);
	static void centerCamera();
	static void setMaxWidth();
	static void prepMenuState(int, int);
private:
	static int _CURRENT_X;
	static int _CURRENT_Y;
	static int _CURRENT_WIDTH;
	static int _CURRENT_HEIGHT;
};