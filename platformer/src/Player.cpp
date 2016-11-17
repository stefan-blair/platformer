#include "Player.h"
#include "InputHandler.h"
#include "Vector2D.h"
#include "Camera.h"

#include "Melee_Weapon.h"
#include "Projectile_Weapon.h"

Player::Player() :
	SDLGameObject(),
	_current_weapon(0)
{
	_alive = true;
	for (int i = 0; i < 3; i++){
		_projectile_weapon[i] = nullptr;
		_melee_weapon[i] = nullptr;
		_weapon_map[i] = 3;
	}
}


Player::~Player() 
{
}
void Player::draw(){
	SDLGameObject::draw();
	switch (_weapon_map[_current_weapon]){
	case 3:
		break;
	case 2:
		_melee_weapon[_current_weapon]->draw();
		break;
	case 1:
		_projectile_weapon[_current_weapon]->draw();
		break;
	}
}

void Player::update(){
	//_currentFrame = int(((SDL_GetTicks() / 100) % 7));

	if (InputHandler::Instance()->getMouseButtonState(0)){
		_velocity.setX(6);
	}
	else
	{
		_velocity.setX(0);
	}
	_velocity.setX(0);


	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) ){
		_direction = LEFT;
		if (!collideLeft())
			_velocity.setX(-_walkSpeed); 
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) ){ 
		_direction = RIGHT;
		if (!collideRight())
			_velocity.setX(_walkSpeed);
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)){
		_direction = UP;
		if (!_jumping && !_falling && !checkJumping())
		{
			jump();
		}
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)){
		_direction = DOWN;
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_L)){
		switch (_weapon_map[_current_weapon]){
		case 3:
			break;
		case 2:
			_melee_weapon[_current_weapon]->attack();
			break;
		case 1:
			_projectile_weapon[_current_weapon]->attack();
			break;
		}
	}

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_E)){
		_current_weapon++;
		if (_current_weapon >= 3){
			_current_weapon = 0;
		}
	}

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_Q)){
		_current_weapon--;
		if (_current_weapon < 0){
			_current_weapon = 2;
		}
	}

	physics();
	_velocity += _acceleration;
	_position += _velocity;

	switch (_weapon_map[_current_weapon]){
	case 3:
		break;
	case 2:
		_melee_weapon[_current_weapon]->maintain();
		break;
	case 1:
		_projectile_weapon[_current_weapon]->maintain();
		break;
	}
	
	Camera::setCurrentX(_position.getX()-300);
}

void Player::clean(){
	SDLGameObject::clean();
//	delete[] _weapon_map;
	for (int i = 0; i < 3; i++)
	{
		delete _melee_weapon[i];
		delete _projectile_weapon[i];
	}
}

void Player::equip(int index, Projectile_Weapon* projectile_weapon, Melee_Weapon* melee_weapon){
	// player's position is invalid.  break in the player creator
	if (melee_weapon != 0){
		_melee_weapon[index] = melee_weapon;
		_weapon_map[index] = 2;
	}
	else if (projectile_weapon != 0){
		_projectile_weapon[index] = projectile_weapon;
		_weapon_map[index] = 1;
	}
	else _weapon_map[index] = 3;
}

int Player::getWeaponType(int index){
	return _weapon_map[index];
}

void Player::writeData(SDLGameObject_Values& values){
	values.health = _health;
	values.jumpHeight = _jumpHeight;
	values.money = _money;
	values.runSpeed = _runSpeed;
	values.skill_points = _skill_points;
	values.walkSpeed = _walkSpeed;
	values.weight = _weight;
}

void Player::writeProjectileData(int index, Projectile_Weapon_Values& values){
	_projectile_weapon[index]->writeData(values);
}
void Player::writeMeleeData(int index, Melee_Weapon_Values& values){
	_melee_weapon[index]->writeData(values);
}

int Player::getFreeWeaponSpace(){
	for (int i = 0; i < 3; i++)
	{
		if (_weapon_map[i] == 3)
			return i;
	}
	return 3;
}
Melee_Weapon* Player::getMeleeWeapon(int i){
	return _melee_weapon[i];
}
Projectile_Weapon* Player::getProjectileWeapon(int i){
	return _projectile_weapon[i];
}

void Player::setSpeed(int speed){
	_walkSpeed = speed;
	_runSpeed = speed + 1;
}
int Player::getSpeed(){
	return _walkSpeed;
}
