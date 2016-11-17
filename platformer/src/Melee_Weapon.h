#include <string>

#include "SDLGameObject.h"

#pragma once

struct Melee_Weapon_Values{
	int range = 40;
	int damage = 20;
	int price = 0;
	int id = 1;
	int rechargeTime = 180;
	std::string type;
};

class Melee_Weapon
{
public:
	Melee_Weapon(SDLGameObject*);
	~Melee_Weapon();

	void init(Melee_Weapon_Values&);
	void attack();
	void maintain();
	void draw();
	void writeData(Melee_Weapon_Values&);

	int& getDamage();
	int& getRange();
	int& getRechargeTime();

	void setDamage(int);
	void setRange(int);
	void setRechargeTime(int);
	
	void setPrice(int);
	int& getPrice();
	std::string& getType();
private:
	int _range,
		_damage;
	int _price;
	int _id;
	std::string _type;

	bool charged();

	int
		_rechargeTime,
		_timer;
	SDLGameObject* _owner;
};
