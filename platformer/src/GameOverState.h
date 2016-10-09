#include "GameState.h"
#include "Button.h"
#include "TextObject.h"

#pragma once
class GameOverState : public GameState
{
public:
	GameOverState();
	~GameOverState();

	virtual void update();
	virtual void render();

	virtual void refresh();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;
private:
	std::string _text_message;
	TextObject _title;

	Button
		_restart,
		_settings,
		_menu;
	bool
		_restart_pressed = false,
		_settings_pressed = false,
		_menu_pressed = false;
	
};

