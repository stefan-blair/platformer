#include "GameStateMachine.h"


GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::update(){
	if (!_gameStates.empty()){
		_gameStates.back()->update();
	}
}
void GameStateMachine::render(){
	if (!_gameStates.empty()){
		_gameStates.back()->render();
	}
}

void GameStateMachine::pushState(GameState* state){
	_gameStates.push_back(state);
	_gameStates.back()->onEnter();
}
void GameStateMachine::changeState(GameState* state){
	if (!_gameStates.empty()){
		if (_gameStates.back()->getStateID() == state->getStateID()){
			return;
		}
		if (_gameStates.back()->onExit()){
			delete _gameStates.back();
			_gameStates.pop_back();
		}
	}
	_gameStates.push_back(state);
	_gameStates.back()->onEnter();
}
void GameStateMachine::popState(){
	if (!_gameStates.empty()){
		if (_gameStates.back()->onExit()){
			delete _gameStates.back();
			_gameStates.pop_back();
		}
	}
}

void GameStateMachine::refreshStates(){
	for (int i = 0; i < _gameStates.size(); i++){
		_gameStates[i]->refresh();
	}
}

void GameStateMachine::clearStates(){
	if (!_gameStates.empty()){
		for (int i = 0; i < _gameStates.size(); i++){
			_gameStates[i]->onExit();
			delete _gameStates[i];
		}
	}
	_gameStates.clear();
}