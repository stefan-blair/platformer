#include "SDLGameObject.h"
#include "CreatorFactory.h"
#include "Projectile_Weapon.h"
#include "Melee_Weapon.h"

/*struct Player_Values
{
	int money = 0;
	int skill_points = 0;
	int walkSpeed = 2;
	int runSpeed = 4;
	int weight = 2;
	int jumpHeight = 18;
	int health = 10;
};*/

#pragma once
class Player : public SDLGameObject
{
public:
	Player();
	~Player();

	//void init(Player_Values&);
	virtual void draw();
	virtual void update();
	virtual void clean();

	void equip(int index, Projectile_Weapon* projectile_weapon, Melee_Weapon* melee_weapon);

	void writeData(SDLGameObject_Values&);
	void writeProjectileData(int, Projectile_Weapon_Values&);
	void writeMeleeData(int, Melee_Weapon_Values&);

	void setSpeed(int);
	int getSpeed();

	int getWeaponType(int);
	int getFreeWeaponSpace();

	Melee_Weapon* getMeleeWeapon(int);
	Projectile_Weapon* getProjectileWeapon(int);
private:
	int _current_weapon;
	int _weapon_map[3];
	Projectile_Weapon* _projectile_weapon[3];
	Melee_Weapon* _melee_weapon[3];
};

class PlayorCreator : public BaseCreator
{
public:
	virtual SDLGameObject* createObject(){
		return new Player();
	}
};