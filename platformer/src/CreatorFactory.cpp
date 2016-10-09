#include "CreatorFactory.h"
#include "Player.h"
#include "Enemy.h"
#include "FinishBlock.h"
#include "HorizontalPlatform.h"


const int		GameObjectFactory::_number_of_objects = 3;
int				GameObjectFactory::_creator_interval = 0;
std::string		GameObjectFactory::_creatorID[GameObjectFactory::_number_of_objects];
BaseCreator*	GameObjectFactory::_creators[GameObjectFactory::_number_of_objects];

void GameObjectFactory::init(){
	registerType("player", new PlayorCreator());
	registerType("enemy", new EnemyCreator());
	registerType("finishblock", new FinishBlockCreator());
	registerType("horizontalplatform", new HorizontalPlatformCreator());
}

void GameObjectFactory::registerType(std::string id, BaseCreator* creator){
	_creators[_creator_interval] = creator;
	_creatorID[_creator_interval] = id;
	_creator_interval++;
}

SDLGameObject* GameObjectFactory::create(std::string id){
	for (char index = 0; index < _creator_interval; index++){
		if (_creatorID[index] == id){
			return _creators[index]->createObject();
		}
	}
}