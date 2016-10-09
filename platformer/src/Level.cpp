#include "Level.h"
#include "Save.h"
#include "CollisionDetection.h"
#include "LoaderParams.h"
#include "FinishBlock.h"
#include "StateParser.h"
#include "GameOverState.h"

Level::Level()
{
}


Level::~Level()
{
}

void Level::init(){
	StateParser::getCurrentLevel(_name);
	if (stoi(_name) >= 3)
	{
		//STATE FOR GAME COMPLETED
		//PUSH NEW STATE FOR GAME OVER
		//SETTINGS STATE
		//LEVEL SELECT STATE
		std::cout << "YOU WIN THE GAME!!! " << std::endl;
	}
	StateParser::loadStatePlayer(_name, &_player);
	StateParser::loadStateObjects(_name, &_player, &_gameObjects);
	StateParser::loadStateTiles(_name, &_tiles);
	StateParser::loadStatePlayerAttr(&_player);

	_gameObjects.push_back(&_player);

	CollisionDetection::init(&_gameObjects, &_tiles);
	int size = _gameObjects.size();
	for (int i = 0; i < size; i++){
		SDLGameObject* currentObject = _gameObjects[i];
		for (int a = 0; a < size; a++){
			if(a != i)
				currentObject->addConnection(a);
		}
	}
}
void Level::draw(){
	_tiles.draw();
	for (int i = 0; i < _gameObjects.size(); i++){
		if (_gameObjects[i]->isAlive())
			_gameObjects[i]->draw();
	}
}
void Level::update(){
	_tiles.update();
	for (int i = 0; i < _gameObjects.size(); i++){
		if (_gameObjects[i]->isAlive())
			_gameObjects[i]->update();
	}
	if (!_player.isAlive())
		Game::Instance()->getGameStateMachine()->changeState(new GameOverState());
}
void Level::clean(){
	Save::Save(&_player);
	int size = _gameObjects.size();
	for (int i = 0; i < size; i++){
		_gameObjects[i]->clean();
		if (_gameObjects[i] != &_player)
			delete (_gameObjects[i]);
	}
	_gameObjects.clear();
	_tiles.clean();
}

void Level::incrementLevel(int increment){
	//Save::SetLevel(increment);
}

void Level::save(){
	Save::Save(&_player);
}