#include<iostream>
#include "Game.h"

int main(int argc, char* args[]){
	const int FPS = 60;
	const int DELAY_TIME = 1000.0f / FPS;

	Uint32 frameStart, frameTime;

	Game::Instance()->init("Chapter 1:  Making Windows", 100, 100, 1200, 700, 0);
	
	while (Game::Instance()->running()){
		frameStart = SDL_GetTicks();

		Game::Instance()->handleEvents();
		Game::Instance()->update();
		Game::Instance()->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < DELAY_TIME){
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}
	Game::Instance()->clean();
	return 0;
}