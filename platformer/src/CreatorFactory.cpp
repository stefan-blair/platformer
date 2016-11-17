#include "CreatorFactory.h"
#include "Player.h"
#include "Enemy.h"
#include "FinishBlock.h"
#include "HorizontalPlatform.h"


const size_t	GameObjectFactory::_number_of_objects = 4;
size_t			GameObjectFactory::_creator_interval = 0;
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
	++_creator_interval;
}

SDLGameObject* GameObjectFactory::create(std::string id){
	for (size_t i = 0; i < _creator_interval; ++i){
		if (_creatorID[i] == id){
			BaseCreator* creator = _creators[i];
			return creator->createObject();
		}
	}

	return NULL;
}
