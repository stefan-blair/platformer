#include <vector>
#include "SDLGameObject.h"

#pragma once

struct Projectile_Weapon_Values
{
	int price = 0;
	int id = 0;
	int range = 100;
	int damage = 2;
	int bulletSpeed = 6;
	int ammunition = 100;
	int rechargeTime = 180;
	std::string type;
};

class Bullet
{
public:
	Bullet();
	~Bullet();

	friend class Projectile_Weapon;
	
	void init(int x, int y, int speed);
	void update();
private:
	bool _active;
	int _x, 
		_y,
		_distance;
	int _speed;
};

class Projectile_Weapon
{
public:
	Projectile_Weapon(SDLGameObject* owner);
	~Projectile_Weapon();

	void init(Projectile_Weapon_Values&);
	void attack();
	void maintain();
	void draw();

	void writeData(Projectile_Weapon_Values&);

	int& getAmmo();
	int& getBulletSpeed();
	int& getDamage();
	int& getRange();
	int& getRechargeTime();

	void setAmmo(int);
	void setBulletSpeed(int);
	void setDamage(int);
	void setRange(int);
	void setRechargeTime(int);

	void setPrice(int);
	int& getPrice();
	std::string& getType();
private:
	bool charged();

	int _price,
		_id;

	int _range, 
		_damage, 
		_bulletSpeed;
	int _ammunition;
	int _current_bullet;
	int _free_bullets;
	int _active_bullets;

	int
		_rechargeTime,
		_timer;
	std::string _type;
	SDLGameObject* _owner;
	std::vector<Bullet*> _bullets;
};

/*ammunition 0
bulletSpeed 10
damage 5
price 500
range 200
rechargeTime 400*/