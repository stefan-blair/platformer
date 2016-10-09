#include "GameState.h"
#include "TextObject.h"
#include "Button.h"

#pragma once
class LevelSelectState : public GameState
{
public:
	LevelSelectState();
	~LevelSelectState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;
private:
	std::string _message;
	int _current_level_index,
		_max_level;
	TextObject _title,
				_current_level;
	Button
		_increase_level,
		_decrease_level,
		_play,
		_back;
	bool
		_increase_level_pressed = false,
		_decrease_level_pressed = false,
		_play_pressed = false,
		_back_pressed = false;
};