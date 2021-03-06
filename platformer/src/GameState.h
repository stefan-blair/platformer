#include<string>
#pragma once
class GameState
{
public:
	GameState(){}
	~GameState(){}

	virtual void update()	= 0;
	virtual void render()	= 0;
	
	virtual void refresh(){

	}

	virtual bool onEnter()	= 0;
	virtual bool onExit()	= 0;

	virtual std::string getStateID() const = 0;
};

