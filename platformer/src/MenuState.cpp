#include <iostream>
#include "Game.h"
#include "Camera.h"
#include "MenuState.h"
#include "SettingState.h"
#include "LevelSelectState.h"
#include "ShopState.h"
#include "Button.h"
#include "LoaderParams.h"

MenuState::MenuState()
	:GameState(),
	_play_button(&_play_pressed),
	_setting_button(&_setting_pressed),
	_level_button(&_level_pressed)
{}
MenuState::~MenuState(){

}

const std::string MenuState::_stateID = "MENUSTATE";


void MenuState::render(){
	_play_button.draw();
	_setting_button.draw();
	_level_button.draw();
}
void MenuState::update(){
	_play_button.update();
	_setting_button.update();
	_level_button.update();
	if (_play_pressed){
		Game::Instance()->getGameStateMachine()->changeState(new ShopState());		
	}
	else if (_setting_pressed){
		Game::Instance()->getGameStateMachine()->pushState(new SettingState());
	}
	else if (_level_pressed){
		Game::Instance()->getGameStateMachine()->pushState(new LevelSelectState());
	}
}

bool MenuState::onEnter(){
	std::cout << "ENTERING MENUSTATE" << std::endl;

	Camera::prepMenuState(201, 600);
	
	_play_button.init(new LoaderParams(0, 0, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_setting_button.init(new LoaderParams(0, 200, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_level_button.init(new LoaderParams(0, 100, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	return true;
}
bool MenuState::onExit(){
	std::cout << "EXITING MENUSTATE" << std::endl;
	return true;
}

void MenuState::refresh(){
	std::cout << "REFRESHING MENUSTATE" << std::endl;
	Camera::prepMenuState(201, 600);
	_play_button.refresh();
	_setting_button.refresh();
	_level_button.refresh();
}