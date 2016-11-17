#include "LoaderParams.h"


LoaderParams::LoaderParams(int x, int y, int width, int height, int id, int currentRow, int currentFrame) :
	_x(x),
	_y(y),
	_width(width),
	_currentRow(currentRow),
	_currentFrame(currentFrame),
	_height(height),
	_id(id)
{
}


LoaderParams::~LoaderParams()
{
}


int LoaderParams::getX() const { return _x; }
int LoaderParams::getY() const { return _y; }
int LoaderParams::getWidth() const { return _width; }
int LoaderParams::getHeight() const { return _height; }
int LoaderParams::getCurrentRow() const { return _currentRow; }
int LoaderParams::getCurrentFrame() const { return _currentFrame; }
int LoaderParams::getId() const { return _id; }
