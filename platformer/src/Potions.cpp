#include "Potions.h"

Potion::Potion(){}
Potion::~Potion(){}
int Potion::getPrice(){
	return _price;
}

std::string& Potion::getType(){
	return _name;
}

void PotionShop::getPotions(std::vector<Potion*>& list)
{
	list.push_back(new HealthPotion());
	list.push_back(new SpeedPotion());
	list.push_back(new StrengthPotion());
}

HealthPotion::HealthPotion(){ _price = 20; _name = "Health Potion"; }
void HealthPotion::apply(Player& player){ player.setHealth(-20); player.setMoney(-20); }

SpeedPotion::SpeedPotion(){ _price = 1000; _name = "Speed Potion"; }
void SpeedPotion::apply(Player& player){ player.setSpeed(player.getSpeed() + 1); player.setMoney(-_price); }

StrengthPotion::StrengthPotion(){ _price = 200; _name = "Strength Potion"; }
void StrengthPotion::apply(Player& player) { return; };