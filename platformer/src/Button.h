#include"SDLGameObject.h"
#include"LoaderParams.h"

#pragma once
class Button : public SDLGameObject
{
public:
	Button(bool* clicked);
	~Button();

	void refresh();
	virtual void init(LoaderParams* loaderParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	Vector2D*	_mousePos;
	bool*		_clicked;
	bool		_released;

	int
		_cameraX,
		_cameraY;
};

