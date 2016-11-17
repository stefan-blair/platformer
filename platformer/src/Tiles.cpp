#include "Tiles.h"
#include "Camera.h"

Tiles::Tiles() :
	_id(0),
	_width(0),
	_height(0),
	_maxX(0),
	_maxY(0)
{
}


Tiles::~Tiles()
{
}

void Tiles::init(LoaderParams* params)
{
	_maxX = params->getX();
	_maxY = params->getY();
	_id = params->getId();
	_width = params->getWidth();
	_height = params->getHeight();
}

inline bool isBetween(int a, int b, int c){
	return c > b && b > a;
}

void Tiles::draw(){
	for (int y = 0; y < _maxY; ++y){
		for (int x = 0; x < _maxX; ++x){
			tile* current_tile = _tiles[(y*_maxX)+x];
			if (current_tile != 0){
				if (Camera::checkOnScreen(x*_width, y*_height)){
					LoaderParams params = LoaderParams(x*_width, y*_height, _width, _height, _id, current_tile->_row, current_tile->_frame);
					Camera::render(params);
				}
			}
		}
	}
}
void Tiles::update(){

}
void Tiles::clean(){
	for (size_t i = 0; i < _tiles.size(); i++){
		delete _tiles[i];
	}
	_tiles.clear();
}
void Tiles::addTile(tile* t){
	_tiles.push_back(t);
}
