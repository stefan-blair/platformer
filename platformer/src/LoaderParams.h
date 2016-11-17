#pragma once
class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, int id, int currentRow = 1, int currentFrame = 0);
	~LoaderParams();

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	int getCurrentRow() const;
	int getCurrentFrame() const;
	int getId() const;
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

