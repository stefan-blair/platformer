#include <vector>
#include "Vector2D.h"
#include "Tiles.h"
#include "SDLGameObject.h"

#pragma once

class CollisionDetection
{
public:
	static void init(std::vector<SDLGameObject*>* objects, Tiles* tiles);
	static bool tileCollide(int x, int y);
	static bool objectCollide(int x, int y, std::vector<int>*);
	static Vector2D* getContactPoint();
	static SDLGameObject* getContactObject();
private:
	static std::vector<SDLGameObject*>* _objects;
	static Tiles* _tiles;
	static Vector2D* _contactPoint;
	static SDLGameObject* _contactObject;

	CollisionDetection();
	~CollisionDetection();
};

