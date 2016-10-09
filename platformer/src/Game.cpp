#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Game.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"
#include "CreatorFactory.h"

Game::Game()
{
}


Game::~Game()
{
}
Game* Game::_instance = 0;
Game* Game::Instance(){
	if (_instance == 0){
		_instance = new Game();
	}
	return _instance;
}

SDL_Renderer* Game::getRenderer(){
	return _renderer;
}

bool Game::init(const char* title, short xpos, short ypos, short width, short height, int flags){
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0){
		_width = width;
		_height = height;
		_window = SDL_CreateWindow(title, xpos, ypos, _width, _height, flags);
		if (_window != 0){
			_renderer = SDL_CreateRenderer(_window, -1, 0);
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
	
	TTF_Init();
	atexit(TTF_Quit);

	_gameStateMachine = new GameStateMachine();
	_gameStateMachine->changeState(new MenuState());
	
	_running = true;

	GameObjectFactory::init();

	return true;
}

void Game::render()
{
	SDL_RenderClear(_renderer);
	_gameStateMachine->render();
	SDL_RenderPresent(_renderer);
}

void Game::update()
{
	_gameStateMachine->update();
}

void Game::handleEvents()
{
	InputHandler::Instance()->update();
}

void Game::clean()
{
	_running = false;
	InputHandler::Instance()->clean();
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);

	SDL_Quit();
}

void Game::resizeWindowWidth(int amount){
	_width += amount;
	SDL_SetWindowSize(_window, _width, _height);
}
void Game::resizeWindowHeight(int amount){
	_height += amount;
	SDL_SetWindowSize(_window, _width, _height);
}
void Game::toggleFullScreen(){
	if (_fullScreen)
		SDL_SetWindowFullscreen(_window, 0);
	else
		SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	_fullScreen = !_fullScreen;
}

bool Game::running(){
	return _running;
}

int Game::getWidth(){
	return _width;
}

int Game::getHeight(){
	return _height;
}