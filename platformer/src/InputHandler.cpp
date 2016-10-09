#include"InputHandler.h"

InputHandler::InputHandler() :_mousePosition(new Vector2D(0,0))
{
	_keyState = SDL_GetKeyboardState(0);
	_mouseButtonStates[0] = false;
	_mouseButtonStates[1] = false;
	_mouseButtonStates[2] = false;
}

InputHandler::~InputHandler(){

}


InputHandler* InputHandler::_instance = 0;
InputHandler* InputHandler::Instance(){
	if (_instance == 0){
		_instance = new InputHandler();
	}
	return _instance;
}
bool InputHandler::getMouseButtonState(char buttonNumber){
	return _mouseButtonStates[buttonNumber];
}

bool InputHandler::isKeyDown(SDL_Scancode key){
	if (_keyState != 0){
		if (_keyState[key] == 1){
			return true;
		}
	}
	return false;
}

void InputHandler::update(){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			Game::Instance()->clean();
		}
		if (event.type == SDL_MOUSEBUTTONDOWN){
			if (event.button.button == SDL_BUTTON_LEFT){
				_mouseButtonStates[0] = true;
			}
			if (event.button.button == SDL_BUTTON_RIGHT){
				_mouseButtonStates[2] = true;
			}
			if (event.button.button == SDL_BUTTON_MIDDLE){
				_mouseButtonStates[1] = true;
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP){
			if (event.button.button == SDL_BUTTON_LEFT){
				_mouseButtonStates[0] = false;
			}
			if (event.button.button == SDL_BUTTON_RIGHT){
				_mouseButtonStates[2] = false;
			}
			if (event.button.button == SDL_BUTTON_MIDDLE){
				_mouseButtonStates[1] = false;
			}
		}
		if (event.type == SDL_MOUSEMOTION){
			_mousePosition->setX(event.motion.x);
			_mousePosition->setY(event.motion.y);
		}
	}
}
void InputHandler::clean(){

}

Vector2D* InputHandler::getMousePosition(){
	return _mousePosition;
}
