#include "FinishBlock.h"
#include "Game.h"
#include "ShopState.h"
#include "Save.h"
#include "StateParser.h"

FinishBlock::FinishBlock() :
	SDLGameObject()
{
}


FinishBlock::~FinishBlock()
{
}

void FinishBlock::draw(){
	SDLGameObject::draw();
}

void FinishBlock::update(){
	SDLGameObject::update();
	int xDif = abs(_playerLocation->getX() - _position.getX());
	int yDif = abs(_playerLocation->getY() - _position.getY());

	if (xDif < 50 & yDif < 50)
	{
		std::string current_level;
		StateParser::getCurrentLevel(current_level);
		Save::SetLevel(stoi(current_level)+1);
		Game::Instance()->getGameStateMachine()->changeState(new ShopState());
	}
}

void FinishBlock::clean(){
	SDLGameObject::clean();
}
