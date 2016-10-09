#include<SDL.h>
#include"Game.h"
#include"Vector2D.h"
#pragma once
class InputHandler
{
public:
	static InputHandler* Instance();
	Vector2D* getMousePosition();
	bool getMouseButtonState(char buttonNumber);
	bool isKeyDown(SDL_Scancode key);
	void update();
	void clean();

private:
	InputHandler();
	~InputHandler();

	bool _mouseButtonStates[3];
	Vector2D* _mousePosition;
	const Uint8* _keyState;
	static InputHandler* _instance;
};