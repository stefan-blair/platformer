#include "Melee_Weapon.h"
#include "CollisionDetection.h"
#include "LoaderParams.h"
#include "Camera.h"

Melee_Weapon::Melee_Weapon(SDLGameObject* owner) :
	_timer(SDL_GetTicks()),
	_owner(owner),
	_rechargeTime(0),
	_price(0),
	_damage(0),
	_range(0),
	_id(0)
{
}


Melee_Weapon::~Melee_Weapon()
{
}

void Melee_Weapon::init(Melee_Weapon_Values& values){
	std::cout << values.type << std::endl;
	_range = values.range;
	_damage = values.damage;
	_price = values.price;
	_id = values.id;
	_rechargeTime = values.rechargeTime;
	_type = values.type;
}

void Melee_Weapon::attack(){
	std::cout << "MELEE WEAPON ATTACKING, Damage = " << _damage << " : " << _type << std::endl;
	if (charged()){
		int width = _owner->getWidth();
		int height = _owner->getHeight();
		int x = _owner->getPosition()->getX() + (width / 2);
		int y = _owner->getPosition()->getY() + (height / 2);

		switch (_owner->getDirection()){
		case LEFT:
			x -= _range;
			break;
		case RIGHT:
			x += _range;
			break;
		case UP:
			y -= _range;
			break;
		case DOWN:
			y += _range;
			break;
		}

		if (CollisionDetection::objectCollide(x, y, _owner->getConnections())){
			SDLGameObject* current_object = CollisionDetection::getContactObject();
			if (!current_object->setHealth(_damage)){
				_owner->setMoney(current_object->getMoney());
			}
		}
	}
}

void Melee_Weapon::maintain(){

}

void Melee_Weapon::draw(){
	return;
	int x = _owner->getPosition()->getX();
	int y = _owner->getPosition()->getY();
	if (Camera::checkOnScreen(x, y)){
		LoaderParams params = LoaderParams(x, y, 30, 10, 1, 1, 1);
		Camera::render(params);
	}
}

bool Melee_Weapon::charged(){
	if (SDL_GetTicks() - _timer >= _rechargeTime){
		_timer = SDL_GetTicks();
		return true;
	}
	return false;
}

void Melee_Weapon::writeData(Melee_Weapon_Values& values){
	values.damage = _damage;
	values.id = _id;
	values.price = _price;
	values.range = _range;
	values.rechargeTime = _rechargeTime;
	values.type = _type;
}

int& Melee_Weapon::getPrice(){
	return _price;
}

std::string& Melee_Weapon::getType(){
	return _type;
}


int& Melee_Weapon::getDamage(){
	return _damage;
}
int& Melee_Weapon::getRange(){
	return _range;
}
int& Melee_Weapon::getRechargeTime(){
	return _rechargeTime;
}

void Melee_Weapon::setDamage(int damage){
	_damage = damage;
}
void Melee_Weapon::setRange(int range){
	_range = range;
}
void Melee_Weapon::setRechargeTime(int rechargetime){
	_rechargeTime = rechargetime;
}
void Melee_Weapon::setPrice(int price){
	_price = price;
}
