#include<SDL.h>
#include"TextureManager.h"
#include"SDLGameObject.h"
#include"Button.h"
#include"Player.h"
#pragma once

class MenuState : public GameState
{
public:
	MenuState();
	~MenuState();

	virtual void render();
	virtual void update();

	virtual void refresh();

	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return _stateID; }
private:
	static const std::string _stateID;
	Button 
		_play_button,
		_setting_button,
		_level_button;
	bool 
		_play_pressed = false,
		_setting_pressed = false,
		_level_pressed = false;
};

