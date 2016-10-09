#include <vector>
#include "GameObject.h"
#include "Vector2D.h"

#pragma once

enum direction{
	LEFT, RIGHT, UP, DOWN
};

struct SDLGameObject_Values
{
	int money = 0;
	int skill_points = 0;
	int walkSpeed = 2;
	int runSpeed = 4;
	int weight = 2;
	int jumpHeight = 18;
	int health = 10;
	int range = 100;
};

class SDLGameObject : public GameObject
{
public:
	SDLGameObject();
	~SDLGameObject();

	void init(LoaderParams* loaderParams);
	void initAttr(SDLGameObject_Values&);
	virtual void draw();
	virtual void update();
	virtual void clean();
	
	Vector2D* getPosition();
	std::vector<int>* getConnections();
	int getWidth();
	int getHeight();
	direction getDirection();
	bool isAlive();
	bool setHealth(int);
	void setPlayerLocation(Vector2D*);
	void addConnection(int);

	int getMoney();
	int getSkillPoints();
	void setMoney(int);
	void setSkillPoints(int);
protected:
	bool collideLeft();
	bool collideRight();
	bool collideTop();
	bool checkJumping();
	void checkFalling();
	void jump();
	void physics();		//IMPORTANT

	bool
		_jumping,
		_falling;
	bool _tileCollide;
	bool _alive;
	bool _mortal;
	direction _direction;
	int
		_width,
		_height,
		_currentRow,
		_currentFrame,
		_id;
	int _range;
	int
		_walkSpeed,
		_runSpeed,
		_jumpHeight,
		_weight,
		_health;
	int _money,
		_skill_points;
	Vector2D
		_position,
		_velocity,
		_acceleration;
	Vector2D* _playerLocation;
	SDLGameObject* _currentObject;
	std::vector<int> _connections;
};

