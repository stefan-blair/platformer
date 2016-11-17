#include <iostream>
#include "SDLGameObject.h"
#include "Melee_Weapon_Types.h"
#include "Projectile_Weapon_Types.h"
#pragma once

class BaseCreator
{
public:
	virtual SDLGameObject* createObject() = 0;
	virtual ~BaseCreator(){}
};

class GameObjectFactory
{
public:
	static void	init();
	static SDLGameObject* create(std::string id);
private:
	static void registerType(std::string id, BaseCreator* creator);

	static const size_t			_number_of_objects;
	static size_t				_creator_interval;
	static std::string			_creatorID[];
	static BaseCreator*			_creators[];
};
