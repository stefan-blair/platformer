#include "PauseState.h"
#include "SettingState.h"
#include "MenuState.h"
#include "Game.h"
#include "Camera.h"
#include "TextureManager.h"
#include "LoaderParams.h"

PauseState::PauseState():
GameState(),
_resume(&_resume_clicked),
_settings(&_settings_clicked),
_menu_return(&_menu_return_clicked)
{
}


PauseState::~PauseState()
{
}

const std::string PauseState::_stateID = "PAUSESTATE";

bool PauseState::onEnter(){
	Camera::prepMenuState(201, 600);
	
	std::string message = "Paused";
	_title.init(LoaderParams(0, 0, 200, 80, TextureManager::Instance()->loadFont("8-BIT WONDER", Game::Instance()->getRenderer())), message);
	_resume.init(new LoaderParams(0, 100, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_settings.init(new LoaderParams(0, 200, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_menu_return.init(new LoaderParams(0, 300, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));

	return true;
}

bool PauseState::onExit(){
	return true;
}

void PauseState::update(){
	_resume.update();
	_settings.update();
	_menu_return.update();

	if (_resume_clicked){
		Game::Instance()->getGameStateMachine()->popState();
	}
	else if (_settings_clicked){
		Game::Instance()->getGameStateMachine()->pushState(new SettingState());
	}
	else if (_menu_return_clicked){
		Game::Instance()->getGameStateMachine()->clearStates();
		Game::Instance()->getGameStateMachine()->pushState(new MenuState());
	}

}

void PauseState::render(){
	_title.draw();
	_resume.draw();
	_settings.draw();
	_menu_return.draw();
}

void PauseState::refresh(){
	std::cout << "REFRESHING PAUSESTATE" << std::endl;
	Camera::prepMenuState(201, 600);
	_resume.refresh();
	_settings.refresh();
	_menu_return.refresh();
}