#include<iostream>
#include "CreatorFactory.h"
#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "PauseState.h"
#include "Player.h"
#include "StateParser.h"

PlayState::PlayState()
{
	_level = new Level();
	_level->init();
	//_level->incrementLevel(1);
}


PlayState::~PlayState()
{
}

const std::string PlayState::_stateID = "PLAYSTATE";


void PlayState::render(){
	_level->draw();
}
void PlayState::update(){
	_level->update();
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_P))Game::Instance()->getGameStateMachine()->pushState(new PauseState());
}

bool PlayState::onEnter(){
	std::cout << "ENTERING PLAYSTATE" << std::endl;
	return true;
}
bool PlayState::onExit(){
	std::cout << "EXITING PLAYSTATE" << std::endl;
	_level->clean();
	return true;
}