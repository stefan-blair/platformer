#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#ifndef __TextureManager__
#define __TextureManager__
#pragma once

class TextureManager
{
public:
	static TextureManager* Instance();
	short load(std::string fileName, SDL_Renderer* renderer);
	short loadFont(std::string fileName, SDL_Renderer* renderer);
	void draw(short id, short x, short y, short width, short height, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(short id, short x, short y, short width, short height, short currentRow, short currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void writeText(int id, int x, int y, int width, int height, std::string& text, SDL_Renderer* renderer);
	void clear();
private:
	TextureManager();
	~TextureManager();
	
	std::vector<std::string> _fontfiles;
	std::vector<TTF_Font*> _fonts;

	std::vector<std::string> _files;
	std::vector<SDL_Texture*> _textureMap;
};

#endif

