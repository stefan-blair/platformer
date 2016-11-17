#include <cstdlib>

#include <string>
#include <sstream>

#include "LevelSelectState.h"
#include "Save.h"
#include "StateParser.h"
#include "Game.h"
#include "TextureManager.h"
#include "ShopState.h"
#include "Camera.h"


LevelSelectState::LevelSelectState() :
	GameState(),
	_increase_level(&_increase_level_pressed),
	_decrease_level(&_decrease_level_pressed),
	_play(&_play_pressed),
	_back(&_back_pressed),
	_message("Select Level"),
	_max_level(0),
	_current_level_index(0)
{}

LevelSelectState::~LevelSelectState()
{}

void LevelSelectState::update(){
	_increase_level.update();
	_decrease_level.update();
	_play.update();
	_back.update();

	if (_increase_level_pressed && _current_level_index < _max_level){
		++_current_level_index;
		std::string current_level = std::to_string(_current_level_index);
		_current_level.setString(current_level);
	}
	else if (_decrease_level_pressed && _current_level_index > 1){
		--_current_level_index;
		std::string current_level = std::to_string(_current_level_index);
		_current_level.setString(current_level);
	}
	else if (_play_pressed){
		Save::SetLevel(_current_level_index);
		Game::Instance()->getGameStateMachine()->pushState(new ShopState());
	}
	else if (_back_pressed){
		Game::Instance()->getGameStateMachine()->popState();
	}
}
void LevelSelectState::render(){
	_increase_level.draw();
	_decrease_level.draw();
	_play.draw();
	_back.draw();

	_title.draw();
	_current_level.draw();
}

bool LevelSelectState::onEnter(){
	Camera::prepMenuState(244, 500);
	std::string level;
	StateParser::getCurrentLevel(level);
	_current_level_index = _max_level = std::stoi(level);

	_increase_level.init(new LoaderParams(172, 100, 72, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_decrease_level.init(new LoaderParams(0, 100, 72, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_play.init(new LoaderParams(22, 200, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	_back.init(new LoaderParams(22, 300, 201, 72, TextureManager::Instance()->load("assets/Textures/startButtonSprite.png",
		Game::Instance()->getRenderer())));
	
	LoaderParams titleLoaderParams(18, 0, 220, 70, TextureManager::Instance()->loadFont("8-BIT WONDER", Game::Instance()->getRenderer()));
	_title.init(titleLoaderParams, _message);

	LoaderParams currentLevelLoaderParams(110, 100, 30, 60, TextureManager::Instance()->loadFont("8-BIT WONDER", Game::Instance()->getRenderer()));
	std::string currentLevel = std::to_string(_current_level_index);
	_current_level.init(currentLevelLoaderParams, currentLevel);

	return true;
}
bool LevelSelectState::onExit(){
	return true;
}

std::string LevelSelectState::getStateID() const{
	return "LEVEL SELECT";
}
