#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "LoaderParams.h"
#include "Player.h"

#pragma once
#ifndef __Game__
#define __Game__

class Game
{
public:
	static Game* Instance();
	SDL_Renderer* getRenderer();
	bool running();

	bool init(const char* title, short xpos, short ypos, short width, short height, int flags);
	GameStateMachine* getGameStateMachine(){ return _gameStateMachine; }
	int getWidth();
	int getHeight();

	void render();
	void update();
	void handleEvents();
	void clean();

	void resizeWindowWidth(int);
	void resizeWindowHeight(int);
	void toggleFullScreen();
private:
	Game();
	~Game();

	int				_width,
					_height;

	bool			_fullScreen = false;
	bool			_running;
	SDL_Window*		_window;
	SDL_Renderer*	_renderer;
	SDL_Texture*	_texture;
	SDL_Rect		_sourceRectangle;
	SDL_Rect		_destinationRectangle;

	GameStateMachine* _gameStateMachine;
	static Game* _instance;
	Player* _player;
};

#endif
