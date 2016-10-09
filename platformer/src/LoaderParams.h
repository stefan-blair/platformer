#pragma once
class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, int id, int currentRow = 1, int currentFrame = 0);
	~LoaderParams();

	int const getX();
	int const getY();
	int const getWidth();
	int const getHeight();
	int const getCurrentRow();
	int const getCurrentFrame();
	int const getId();
private:
	int
		_x,
		_y,
		_width,
		_height,
		_currentRow,
		_currentFrame,
		_id;
};

