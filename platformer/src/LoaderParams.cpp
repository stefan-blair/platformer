#include "LoaderParams.h"


LoaderParams::LoaderParams(int x, int y, int width, int height, int id, int currentRow, int currentFrame) :_x(x), _y(y), _width(width), _currentRow(currentRow), _currentFrame(currentFrame), _height(height), _id(id)
{
}


LoaderParams::~LoaderParams()
{
}


int const LoaderParams::getX(){ return _x; }
int const LoaderParams::getY(){ return _y; }
int const LoaderParams::getWidth(){ return _width; }
int const LoaderParams::getHeight(){ return _height; }
int const LoaderParams::getCurrentRow(){ return _currentRow; }
int const LoaderParams::getCurrentFrame(){ return _currentFrame; }
int const LoaderParams::getId(){ return _id; }