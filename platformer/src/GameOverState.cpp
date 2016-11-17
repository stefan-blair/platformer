#include "GameOverState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Camera.h"
#include "PlayState.h"
#include "MenuState.h"
#include "SettingState.h"
#include "LoaderParams.h"

GameOverState::GameOverState()
	: GameState(),
	_restart(&_restart_pressed),
	_settings(&_settings_pressed),
	_menu(&_menu_pressed),
	_text_message("You Died")
{
}


GameOverState::~GameOverState()
{
}

void GameOverState::update(){
	_restart.update();
	_settings.update();
	_menu.update();
	//Camera::setCurrentX(Camera::getCurrentX() - 1);
	if (_restart_pressed){
		std::cout << "RESTART PRESSED" << std::endl;
		Game::Instance()->getGameStateMachine()->changeState(new PlayState());
	}
	else if (_settings_pressed){
		std::cout << "SETTINGS PRESSED" << std::endl;
		Game::Instance()->getGameStateMachine()->pushState(new SettingState());
	}
	else if (_menu_pressed){
		std::cout << "MENU PRESSED" << std::endl;
		Game::Instance()->getGameStateMachine()->changeState(new MenuState());
	}
}
void GameOverState::render(){
	_restart.draw();
	_settings.draw();
	_menu.draw();
	_title.draw();
}

bool GameOverState::onEnter(){
	Camera::prepMenuState(201, 600);

	_restart.init(new LoaderParams(0, 100, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_settings.init(new LoaderParams(0, 200, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_menu.init(new LoaderParams(0, 300, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));

	LoaderParams params(0, 0, 200, 50, TextureManager::Instance()->loadFont("8-BIT WONDER", Game::Instance()->getRenderer()));
	_title.init(params, _text_message);
	
	return true;
}
bool GameOverState::onExit(){
	return true;
}

std::string GameOverState::getStateID() const{
	return "GAME OVER";
}

void GameOverState::refresh(){
	Camera::prepMenuState(201, 600);
	_restart.refresh();
	_settings.refresh();
	_menu.refresh();
}
