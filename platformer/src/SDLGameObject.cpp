#include <SDL.h>
#include <SDL_image.h>
#include"TextureManager.h"
#include "SDLGameObject.h"
#include "Game.h"
#include "CollisionDetection.h"
#include "Camera.h"

SDLGameObject::SDLGameObject() : GameObject(), _mortal(true)
{
}


SDLGameObject::~SDLGameObject()
{
}

void SDLGameObject::init(LoaderParams* params){
	_falling = true;
	_alive = true;
	_direction = RIGHT;

	_position = Vector2D(params->getX(), params->getY());
	_velocity = Vector2D(0, 0);
	_acceleration = Vector2D(0, 0);

	_width = params->getWidth();
	_height = params->getHeight();
	_id = params->getId();
	_currentRow = params->getCurrentRow();
	_currentFrame = params->getCurrentFrame();

	delete params;
}

void SDLGameObject::initAttr(SDLGameObject_Values& values){
	_walkSpeed = values.walkSpeed;
	_runSpeed = values.runSpeed;
	_weight = values.weight;
	_jumpHeight = values.jumpHeight;
	_health = values.health;
	_money = values.money;
	_skill_points = values.skill_points;
	_range = values.range;
}

void SDLGameObject::addConnection(int connection){
	_connections.push_back(connection);
}
void SDLGameObject::setPlayerLocation(Vector2D* location){
	_playerLocation = location;
}
int SDLGameObject::getWidth(){
	return _width;
}
int SDLGameObject::getHeight(){
	return _height;
}
Vector2D* SDLGameObject::getPosition(){
	return &_position;
}

void SDLGameObject::draw(){
	if (Camera::checkOnScreen(_position.getX(), _position.getY())){
		LoaderParams params = LoaderParams(_position.getX(), _position.getY(), _width, _height, _id, _currentRow, _currentFrame);
		Camera::render(params);
	}
}

void SDLGameObject::update(){

}

void SDLGameObject::physics(){
	if (_jumping){
		if (checkJumping() || _velocity.getY() > 0){
			_jumping = false;
			_velocity.setY(0);
			checkFalling();
		}
		_velocity.setY(_velocity.getY() + _weight);
	}
	if (_falling)
	{
		_velocity.setY(_velocity.getY() + _weight);
		checkFalling();
	}

	if (_velocity.getX() != 0 && !_jumping){
		checkFalling();
	}
}

void SDLGameObject::clean(){
	_connections.clear();
}

void SDLGameObject::jump(){
	_velocity.setY(-_jumpHeight);
	_jumping = true;
}

bool SDLGameObject::isAlive(){
	return _alive | !_mortal;
}

direction SDLGameObject::getDirection(){
	return _direction;
}

std::vector<int>* SDLGameObject::getConnections(){
	return &_connections;
}

bool SDLGameObject::setHealth(int damage){
	_health -= damage;
	if (_health <= 0)
		_alive = false;
	return _alive;
}

bool SDLGameObject::collideLeft(){
	int _x1 = _position.getX();
	int _y1 = _position.getY() + 1;
	int _x2 = _x1;
	int _y2 = _y1 + _height - 2;
	_currentObject = CollisionDetection::getContactObject();
	_tileCollide = CollisionDetection::tileCollide(_x1, _y1) || CollisionDetection::tileCollide(_x2, _y2);
	return CollisionDetection::objectCollide(_x1, _y1, &_connections) || CollisionDetection::objectCollide(_x2, _y2, &_connections) || _tileCollide;
}

bool SDLGameObject::collideRight(){
	int _x1 = _position.getX() + _width;
	int _y1 = _position.getY() + 1;
	int _x2 = _x1;
	int _y2 = _position.getY() + _height - 2;
	_currentObject = CollisionDetection::getContactObject();
	_tileCollide = CollisionDetection::tileCollide(_x1, _y1) || CollisionDetection::tileCollide(_x2, _y2);
	return CollisionDetection::objectCollide(_x1, _y1, &_connections) || CollisionDetection::objectCollide(_x2, _y2, &_connections) || _tileCollide;
}

bool SDLGameObject::collideTop(){
	int _x1 = _position.getX();
	int _y1 = _position.getY();
	int _x2 = _x1 + _width;
	
	_tileCollide = CollisionDetection::tileCollide(_x1, _y1) || CollisionDetection::tileCollide(_x2, _y1);
	_currentObject = CollisionDetection::getContactObject();
	return CollisionDetection::objectCollide(_x1, _y1, &_connections) || CollisionDetection::objectCollide(_x2, _y1, &_connections) || _tileCollide;
}

bool SDLGameObject::checkJumping(){
	int _x1 = _position.getX() + 3;
	int _y1 = _position.getY() - 10;		//Optimize this or find a better solution.
	int _x2 = _x1 + _width - 6;
	int _y2 = _y1;
	return CollisionDetection::tileCollide(_x1, _y1) || CollisionDetection::tileCollide(_x2, _y2) || CollisionDetection::objectCollide(_x1, _y1, &_connections) || CollisionDetection::objectCollide(_x2, _y2, &_connections);
}

/*int SDLGameObject::checkSpace(int x, int y){
	if (CollisionDetection::tileCollide(x, y))
		return 1;
	if (CollisionDetection::objectCollide(x, y, &_connections)){
		return 2;
	}
	return 0;
}*/

void SDLGameObject::checkFalling(){
	int _x1 = _position.getX() + 3;
	int _y1 = _position.getY() + _height + 1;
	int _x2 = _x1 + _width - 6;
	int _y2 = _y1;
	if (!(
		CollisionDetection::tileCollide(_x1, _y1) || 
		CollisionDetection::tileCollide(_x2, _y2) || 
		CollisionDetection::tileCollide(_x1, _y1) || 
		CollisionDetection::tileCollide(_x2, _y2) ||
		CollisionDetection::objectCollide(_x1, _y1, &_connections) || 
		CollisionDetection::objectCollide(_x2, _y2, &_connections)
		)){
		_falling = true;
		return;
	}
	else{
		_falling = false;
		_position.setY(CollisionDetection::getContactPoint()->getY() - _height);
		_velocity.setY(0);
	}
}

int SDLGameObject::getMoney(){
	return _money;
}
int SDLGameObject::getSkillPoints(){
	return _skill_points;
}
void SDLGameObject::setMoney(int i){
	_money += i;
}
void SDLGameObject::setSkillPoints(int i){
	_skill_points += i;
}
