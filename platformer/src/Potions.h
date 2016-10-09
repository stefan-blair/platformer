#include "Player.h"

#pragma once

class Potion
{
public:
	Potion();
	~Potion();

	int getPrice();
	std::string& getType();
	virtual void apply(Player&) = 0;
protected:
	int _price;
	std::string _name;
};

class HealthPotion : public Potion
{
public:
	HealthPotion();
	virtual void apply(Player&);
};

class SpeedPotion : public Potion
{
public:
	SpeedPotion();
	virtual void apply(Player&);
};

class StrengthPotion : public Potion
{
public:
	StrengthPotion();
	virtual void apply(Player&);
};

namespace PotionShop
{
	void getPotions(std::vector<Potion*>&);
}