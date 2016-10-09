#include "GameObject.h"
#include "GameState.h"
#include "Level.h"

#pragma once

class PlayState : public GameState 
{
public:
	PlayState();
	~PlayState();

	virtual void render();
	virtual void update();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return _stateID; }
private:
	static const std::string _stateID;
	Level* _level;
};

