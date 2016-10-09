#include "TextureManager.h"
#include <iostream>
#include "Game.h"

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}
static TextureManager* _instance;
TextureManager* TextureManager::Instance(){
	if (_instance == 0){
		_instance = new TextureManager();
	}
	return _instance;
}

short TextureManager::load(std::string fileName, SDL_Renderer* renderer)
{
	for (int i = 0; i < _files.size(); ++i){
		if (_files[i] == fileName)
			return i;
	}
	_files.push_back(fileName);
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
	if (tempSurface == 0){
		return 0;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (texture != 0)
	{
		_textureMap.push_back(texture);
		return _textureMap.size()-1;
	}

	return 0;
}


short TextureManager::loadFont(std::string fileName, SDL_Renderer* renderer)
{
	for (int i = 0; i < _fontfiles.size(); i++)
	{
		if (_fontfiles[i] == fileName)
			return i;
	}
	_fontfiles.push_back(fileName);

	TTF_Font* font = TTF_OpenFont(("assets/Fonts/"+fileName+".ttf").c_str(), 12);
	if (font != 0)
	{
		_fonts.push_back(font);
		return _fonts.size() - 1;
	}
	return 0;
}

void TextureManager::draw(short id, short x, short y, short width, short height, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(renderer, _textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
void TextureManager::drawFrame(short id, short x, short y, short width, short height, short currentRow, short currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width*currentFrame;
	srcRect.y = height*(currentRow-1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(renderer, _textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::writeText(int id, int x, int y, int width, int height, std::string& text, SDL_Renderer* renderer)
{
	SDL_Color c = { 255, 255, 255, 0 };
	SDL_Surface* text_surface = TTF_RenderText_Solid(_fonts[id], text.c_str(), c);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_Rect srcRect, destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = srcRect.h = 500;

	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_FreeSurface(text_surface);
	
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

void TextureManager::clear(){
	_files.clear();
	_textureMap.clear();
}