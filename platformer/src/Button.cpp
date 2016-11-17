#include "Button.h"
#include "Camera.h"
#include "InputHandler.h"

Button::Button(bool* clicked) : 
	SDLGameObject(),
	_mousePos(InputHandler::Instance()->getMousePosition()),
	_clicked(clicked),
	_released(false),
	_cameraX(0),
	_cameraY(0)
{
}


Button::~Button()
{
}

void Button::init(LoaderParams* params){
	SDLGameObject::init(params);
	_cameraX = Camera::getCurrentX();
	_cameraY = Camera::getCurrentY();
}

void Button::refresh(){
	_cameraX = Camera::getCurrentX();
	_cameraY = Camera::getCurrentY();
}

void Button::draw(){
	SDLGameObject::draw();
}

void Button::update(){
	*_clicked = false;
	if (_mousePos->getX() >= _position.getX() -_cameraX &&
		_mousePos->getX() <= _position.getX() + _width - _cameraX &&
		_mousePos->getY() >= _position.getY() - _cameraY &&
		_mousePos->getY() <= _position.getY() + _height - _cameraY)
	{
		_currentRow = 2;
		if (InputHandler::Instance()->getMouseButtonState(0)){
			_currentRow = 3;
			_released = true;
		}
		else{
			if (_released){
				_released = false;
				*_clicked = true;
			}
		}
	}
	else
	{
		_currentRow = 1;
	}
	SDLGameObject::update();
}

void Button::clean(){
	SDLGameObject::clean();
}
