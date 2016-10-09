#include<vector>
#include"GameState.h"

#pragma once
class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();
	
	void update();
	void render();

	void refreshStates();
	void clearStates();

	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();
private:
	std::vector<GameState*>_gameStates;
};

