#include "SettingState.h"
#include "Camera.h"
#include "Game.h"

SettingState::SettingState()
	: GameState(),
	_back_button(&_back_pressed),
	_increase_window_width(&_increase_window_width_pressed),
	_decrease_window_width(&_decrease_window_width_pressed),
	_increase_window_height(&_increase_window_height_pressed),
	_decrease_window_height(&_decrease_window_height_pressed)
{
}


SettingState::~SettingState()
{
}

void SettingState::update(){
	_back_button.update();
	_increase_window_width.update();
	_decrease_window_width.update();
	_increase_window_height.update();
	_decrease_window_height.update();

	if (_increase_window_width_pressed){
		Game::Instance()->resizeWindowWidth(10);
		refresh();
	}
	if (_decrease_window_width_pressed){
		Game::Instance()->resizeWindowWidth(-10);
		refresh();
	}
	if (_increase_window_height_pressed){
		Game::Instance()->resizeWindowHeight(10);
		refresh();
	}
	if (_decrease_window_height_pressed){
		Game::Instance()->resizeWindowHeight(-10);
		refresh();
	}
	if (_back_pressed){
		Game::Instance()->getGameStateMachine()->popState();
		Game::Instance()->getGameStateMachine()->refreshStates();
	}
}
void SettingState::render(){
	_back_button.draw();
	_increase_window_width.draw();
	_decrease_window_width.draw();
	_increase_window_height.draw();
	_decrease_window_height.draw();
}

bool SettingState::onEnter(){

	Camera::prepMenuState(272, 500);

	_increase_window_width.init(new LoaderParams(200, 0, 72, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_decrease_window_width.init(new LoaderParams(0, 0, 72, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_increase_window_height.init(new LoaderParams(200, 100, 72, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_decrease_window_height.init(new LoaderParams(0, 100, 72, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_back_button.init(new LoaderParams(50, 200, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));


	return true;
}
bool SettingState::onExit(){
	return true;
}

std::string SettingState::getStateID() const{
	return "SETTINGS";
}

void SettingState::refresh(){
	Camera::prepMenuState(272, 500);
	_back_button.refresh();
	_increase_window_width.refresh();
	_decrease_window_width.refresh();
	_increase_window_height.refresh();
	_decrease_window_height.refresh();
}