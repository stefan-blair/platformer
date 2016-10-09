#include "Game.h"
#include "CreatorFactory.h"
#include "Vector2D.h"

#pragma once
struct tile{
	int _row;
	int _frame;
};
class Tiles
{
public:
	Tiles();
	~Tiles();

	friend class CollisionDetection;
	
	void init(LoaderParams* params);
	void draw();
	void update();
	void clean();
	
	void addTile(tile*);
private:
	int _id,
		_width,
		_height,
		_maxY,
		_maxX;
	std::vector<tile*> _tiles;
};
