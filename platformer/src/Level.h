#include <string>
#include <vector>
#include "SDLGameObject.h"
#include "Tiles.h"
#include "Player.h"

#pragma once
class Level
{
public:
	Level();
	~Level();

	void init();
	void draw();
	void update();
	void clean();

	void incrementLevel(int);
	void save();
private:
	Tiles _tiles;
	std::vector <SDLGameObject*> _gameObjects;
	Player _player;
	std::string _name;
};