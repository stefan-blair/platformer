#include "GameState.h"
#include "TextObject.h"
#include "Button.h"

#pragma once
class PauseState : public GameState
{
public:
	PauseState();
	~PauseState();

	virtual void update();
	virtual void render();

	virtual void refresh();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { 
		return _stateID; 
	}
private:
	TextObject _title;
	Button
		_resume,
		_settings,
		_menu_return;
	bool
		_resume_clicked,
		_settings_clicked,
		_menu_return_clicked;
	const static std::string _stateID;
};

