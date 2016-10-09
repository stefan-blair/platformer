#include "SDLGameObject.h"
#include "CreatorFactory.h"

#pragma once
class HorizontalPlatform : public SDLGameObject
{
public:
	HorizontalPlatform();
	~HorizontalPlatform();

	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	direction	_direction			= RIGHT;
	int			_distance_travelled = 0;
};

class HorizontalPlatformCreator : public BaseCreator
{
public:
	virtual SDLGameObject* createObject(){
		return new HorizontalPlatform();
	}
};
