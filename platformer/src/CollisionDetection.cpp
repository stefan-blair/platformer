#include "CollisionDetection.h"


CollisionDetection::CollisionDetection()
{
}


CollisionDetection::~CollisionDetection()
{
}

std::vector<SDLGameObject*>* CollisionDetection::_objects = nullptr;
Tiles* CollisionDetection::_tiles = nullptr;
Vector2D* CollisionDetection::_contactPoint = new Vector2D(0, 0);
SDLGameObject* CollisionDetection::_contactObject = nullptr;

void CollisionDetection::init(std::vector<SDLGameObject*>* objects, Tiles* tiles)
{
	CollisionDetection::_objects = objects;
	CollisionDetection::_tiles = tiles;
}

bool CollisionDetection::tileCollide(int x, int y){
	x /= _tiles->_width;
	y /= _tiles->_height;
	int maxX = _tiles->_maxX;
	if (x > maxX - 1 || y > _tiles->_maxY - 1){
		return false;
	}
	if (_tiles->_tiles[(y*maxX) + x] != 0){
		CollisionDetection::_contactPoint->setX(x * _tiles->_width);
		CollisionDetection::_contactPoint->setY(y * _tiles->_height);
		return true;
	}
	return false;
}

bool CollisionDetection::objectCollide(int x, int y, std::vector<int>* connections){
	x;
	y;
	for (int i = 0; i < connections->size(); ++i){
		SDLGameObject* current_object = (*_objects)[(*connections)[i]];
		if (current_object->isAlive()){
			int x1 = current_object->getPosition()->getX();
			int x2 = x1 + current_object->getWidth();
			if (x >= x1 && x <= x2)
			{
				int y1 = current_object->getPosition()->getY();
				int y2 = y1 + current_object->getHeight();
				if (y >= y1 && y <= y2)
				{
					_contactPoint->setX(x1);
					_contactPoint->setY(y1);
					_contactObject = current_object;
					return true;
				}
			}
		}
	}
	return false;
}

Vector2D* CollisionDetection::getContactPoint(){
	return _contactPoint;
}
SDLGameObject* CollisionDetection::getContactObject(){
	return _contactObject;
}