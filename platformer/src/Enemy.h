#include "SDLGameObject.h"
#include "CreatorFactory.h"
#include "Melee_Weapon.h"
#include "Projectile_Weapon.h"

#pragma once

class Enemy : public SDLGameObject
{
public:
	Enemy();
	~Enemy();
	virtual void draw();
	virtual void update();
	virtual void clean();
private:
//	Melee_Weapon _weapon;
	Projectile_Weapon _weapon;
};

class EnemyCreator : public BaseCreator
{
public:
	virtual SDLGameObject* createObject(){
		return new Enemy();
	}
};