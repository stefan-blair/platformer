#include "LoaderParams.h"
#pragma once
class GameObject
{
public:
	
	virtual void init(LoaderParams* params) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

protected:
	GameObject();
	virtual ~GameObject();
};

