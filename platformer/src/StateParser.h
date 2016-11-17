#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Game.h"
#include "CreatorFactory.h"
#include "Projectile_Weapon.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Tiles.h"


#pragma once
class StateParser
{
public:
	static void loadStateObjects(std::string fileName, Player* player, std::vector<SDLGameObject*>* objects);
	static void loadStateTiles(std::string fileName, Tiles* tiles);
	static void loadStatePlayer(std::string, Player* player);
	static void loadStatePlayerAttr(Player* player);
	static void getCurrentLevel(std::string&);
	static void readMeleeValues(std::string&, Melee_Weapon_Values&);
	static void readProjectileValues(std::string&, Projectile_Weapon_Values&);

private:
	StateParser();
	~StateParser();
	static std::string getNextWord(std::string* line);

	static size_t _currentIndex;
	static bool _end;
};

