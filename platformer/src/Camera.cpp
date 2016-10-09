#include "Camera.h"
#include "Game.h"

int Camera::_CURRENT_X = 0;
int Camera::_CURRENT_Y = 0;
int Camera::_CURRENT_WIDTH = 600;
int Camera::_CURRENT_HEIGHT = 600;

void Camera::render(LoaderParams &params){
	TextureManager::Instance()->drawFrame(params.getId(), params.getX()-Camera::_CURRENT_X, params.getY()-Camera::_CURRENT_Y, params.getWidth(), params.getHeight(), params.getCurrentRow(), params.getCurrentFrame(), Game::Instance()->getRenderer());
}

void Camera::drawText(LoaderParams &params, std::string &text){
	TextureManager::Instance()->writeText(params.getId(), params.getX()-Camera::_CURRENT_X, params.getY()-Camera::_CURRENT_Y, params.getWidth(), params.getHeight(), text, Game::Instance()->getRenderer());
}

bool Camera::checkOnScreen(int x, int y){
	x -= Camera::_CURRENT_X;
	if (x >= -50 && x <= Camera::_CURRENT_WIDTH)
		return true;
	return false;
}

void Camera::centerCamera(){
	std::cout << "SCREEN WIDTH " << Game::Instance()->getWidth() << std::endl;
	Camera::_CURRENT_X = -((Game::Instance()->getWidth() / 2)-(Camera::_CURRENT_WIDTH/2));
	Camera::_CURRENT_Y = 0;
}
void Camera::setMaxWidth(){
	Camera::_CURRENT_WIDTH = Game::Instance()->getWidth();
	Camera::_CURRENT_HEIGHT = Game::Instance()->getHeight();
}
void Camera::prepMenuState(int width, int height){
	Camera::setWidth(width);
	Camera::setHeight(height);
	Camera::centerCamera();
	Camera::setMaxWidth();
}

void Camera::setCurrentX(int x){
	Camera::_CURRENT_X = x;
}

void Camera::setCurrentY(int y){
	Camera::_CURRENT_Y = y;
}

void Camera::setWidth(int width){
	Camera::_CURRENT_WIDTH = width;
}

void Camera::setHeight(int height){
	Camera::_CURRENT_HEIGHT = height;
}

int Camera::getCurrentX(){
	return Camera::_CURRENT_X;
}
int Camera::getCurrentY(){
	return Camera::_CURRENT_Y;
}