#include "HorizontalPlatform.h"


HorizontalPlatform::HorizontalPlatform() :
	SDLGameObject()
{
}


HorizontalPlatform::~HorizontalPlatform()
{
}

void HorizontalPlatform::update(){
	int current_x = _position.getX();

	switch (_direction){
	case RIGHT:
		if (_distance_travelled > _range || collideRight()){
			_direction = LEFT;
			_walkSpeed *= -1;
		}
		break;
	case LEFT:
		if (_distance_travelled <= 0 || collideLeft()){
			_direction = RIGHT;
			_walkSpeed *= -1;
		}
		break;
	}
	_distance_travelled += _walkSpeed;
	_position.setX(_position.getX() + _walkSpeed);

	SDLGameObject::update();
}

void HorizontalPlatform::draw(){
	SDLGameObject::draw();
}

void HorizontalPlatform::clean(){
	SDLGameObject::clean();
}
