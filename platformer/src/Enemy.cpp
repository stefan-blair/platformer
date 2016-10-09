#include "Enemy.h"
#include "CollisionDetection.h"
#include "StateParser.h"

Enemy::Enemy()
	: SDLGameObject(),
	_weapon(this)
{
	_walkSpeed = 1;
	_runSpeed = 2;
	_weight = 1;
	_jumpHeight = 10;
	_range = 150;
	_health = 10;

	_money = 10;
	
	Projectile_Weapon_Values values;
	std::string type = "Pistol";

	StateParser::readProjectileValues(type, values);
	_weapon.init(values);
}


Enemy::~Enemy()
{
}

void Enemy::draw(){
	SDLGameObject::draw();
	_weapon.draw();
}
void Enemy::update(){
	
	_velocity.setX(0);
	int distance_from_player = _playerLocation->getX() - _position.getX();
	bool collided = false;
	if (distance_from_player > -_range && distance_from_player < 0)
	{
		if (!collideLeft()){
			_velocity.setX(-_walkSpeed);
		}
		else{
			collided = true;
			if (_tileCollide && !_jumping && !_falling && !checkJumping())
				jump();
		}
	}
	else if (distance_from_player < _range && distance_from_player > 0)
	{
		if (!collideRight()){
			_velocity.setX(_walkSpeed);
		}
		else{
			collided = true;
			if (_tileCollide && !_jumping && !_falling && !checkJumping())
				jump();
		}
	}
	if (abs(distance_from_player) < _weapon.getRange()){
		//_weapon.attack();
	}



	physics();
	_velocity += _acceleration;
	_position += _velocity;
	_weapon.maintain();
}
void Enemy::clean(){
	SDLGameObject::clean();
}
