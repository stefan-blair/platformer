#include "SDLGameObject.h"
#include "CreatorFactory.h"

#pragma once
class FinishBlock : public SDLGameObject
{
public:
	FinishBlock();
	~FinishBlock();

	virtual void draw();
	virtual void update();
	virtual void clean();
};

class FinishBlockCreator : public BaseCreator
{
public:
	virtual SDLGameObject* createObject(){
		return new FinishBlock();
	}
};