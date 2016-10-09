#include "Projectile_Weapon.h"
#include "CollisionDetection.h"

#include "Camera.h"

Projectile_Weapon::Projectile_Weapon(SDLGameObject* owner) :
_current_bullet(0),
_free_bullets(0),
_active_bullets(0),
_timer(SDL_GetTicks()),
_owner(owner)
{
}


Projectile_Weapon::~Projectile_Weapon()
{
	//DELETE ALL BULLETS SON!
}

void Projectile_Weapon::init(Projectile_Weapon_Values& values){
	_price = values.price;
	_id = values.id;
	_range = values.range;
	_damage = values.damage;
	_bulletSpeed = values.bulletSpeed;
	_ammunition = values.ammunition;
	_rechargeTime = values.rechargeTime;
	_type = values.type;
}

void Projectile_Weapon::attack(){
	std::cout << "damage: " << _damage << ", range : " << _range << "price: " << _price << "bulletSpeed: " << _bulletSpeed << std::endl;
	
	if (charged()){
		int x = _owner->getPosition()->getX() + (_owner->getWidth() / 2);
		int y = _owner->getPosition()->getY() + (_owner->getHeight() / 2);
		int speed = 6;

		if (_owner->getDirection() == LEFT)
			speed *= -1;
		
		_active_bullets++;
		if (_free_bullets == 0){	
			_bullets.push_back(new Bullet());
			_bullets.back()->init(x, y, speed);
		}else{
			_bullets[_current_bullet]->init(x, y, speed);
		}
	}
}

void Projectile_Weapon::maintain(){
	int active = 0;
	_free_bullets = 0;
	_current_bullet = 0;
	for (int i = 0; i < _bullets.size(); i++){
		if (!_bullets[i]->_active){
			_free_bullets++;
			continue;
		}
		if (_current_bullet == i)
			_current_bullet++;
		active++;
		bool clearing = false;
		_bullets[i]->update();
		if (abs(_bullets[i]->_distance) >= _range)
		{
			clearing = true;
		}
		if (CollisionDetection::tileCollide(_bullets[i]->_x, _bullets[i]->_y))
			clearing = true;
		else if (CollisionDetection::objectCollide(_bullets[i]->_x, _bullets[i]->_y, _owner->getConnections())){
			SDLGameObject* current_object = CollisionDetection::getContactObject();
			if (!current_object->setHealth(_damage)){
				_owner->setMoney(current_object->getMoney());
			}
			clearing = true;
		}
		if (clearing){
			_bullets[i]->_active = false;
		}
	}
	//std::cout << _bullets.size() << std::endl;
}

void Projectile_Weapon::draw(){
	for (int i = 0; i < _bullets.size(); i++){
		if (!_bullets[i]->_active)
			continue;
		LoaderParams params = LoaderParams(_bullets[i]->_x, _bullets[i]->_y, 20, 10, 1, 1, 1);
		if (Camera::checkOnScreen(_bullets[i]->_x, _bullets[i]->_y))
			Camera::render(params);
	}
}


bool Projectile_Weapon::charged(){
	if (SDL_GetTicks() - _timer >= _rechargeTime){
		_timer = SDL_GetTicks();
		return true;
	}
	return false;
}

void Projectile_Weapon::writeData(Projectile_Weapon_Values& values){
	values.ammunition = _ammunition;
	values.bulletSpeed = _bulletSpeed;
	values.damage = _damage;
	values.id = _id;
	values.price = _price;
	values.range = _range;
	values.rechargeTime = _rechargeTime;
	values.type = _type;
}

int& Projectile_Weapon::getPrice()
{
	return _price;
}

std::string& Projectile_Weapon::getType(){
	return _type;
}

int& Projectile_Weapon::getAmmo(){
	return _ammunition;
}
int& Projectile_Weapon::getBulletSpeed(){
	return _bulletSpeed;
}
int& Projectile_Weapon::getDamage(){
	return _damage;
}
int& Projectile_Weapon::getRange(){
	return _range;
}
int& Projectile_Weapon::getRechargeTime(){
	return _rechargeTime;
}

void Projectile_Weapon::setAmmo(int ammo){
	_ammunition = ammo;
}
void Projectile_Weapon::setBulletSpeed(int bulletspeed){
	_bulletSpeed = bulletspeed;
}
void Projectile_Weapon::setDamage(int damage){
	_damage = damage;
}
void Projectile_Weapon::setRange(int range){
	_range = range;
}
void Projectile_Weapon::setRechargeTime(int rechargetime){
	_rechargeTime = rechargetime;
}
void Projectile_Weapon::setPrice(int price){
	_price = price;
}

Bullet::Bullet(){

}
Bullet::~Bullet(){

}
void Bullet::init(int x, int y, int speed){
	_x = x;
	_y = y;
	_speed = speed;
	_distance = 0;
	_active = true;
}
void Bullet::update(){
	_x += _speed;
	_distance += _speed;
}