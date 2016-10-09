#include "GameState.h"
#include "Button.h"

#pragma once
class SettingState : public GameState
{
public:
	SettingState();
	~SettingState();

	virtual void refresh();
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;
private:
	Button	
		_back_button,
		_increase_window_width,
		_decrease_window_width,
		_increase_window_height,
		_decrease_window_height;
	bool	
		_back_pressed = false,
		_increase_window_width_pressed = false,
		_decrease_window_width_pressed = false,
		_increase_window_height_pressed = false,
		_decrease_window_height_pressed = false;
};

