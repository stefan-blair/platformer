#include "UpgradeState.h"
#include "Game.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "LoaderParams.h"
#include <iostream>

UpgradeState::UpgradeState()
	:
	GameState(),
	_released(false),
	_back_pressed(false),
	_back_button(&_back_pressed),
	_projectile_weapon(nullptr),
	_melee_weapon(nullptr),
	_player(nullptr),
	_shopstate(nullptr),
	_weapon_price(nullptr),
	_font_id(0),
	_type(0),
	_number_of_attributes(0)
{
}


UpgradeState::~UpgradeState()
{
}

void UpgradeState::update(){
	_back_button.update();
	bool clicked = InputHandler::Instance()->getMouseButtonState(0);
	int mouseY = InputHandler::Instance()->getMousePosition()->getY() / 60;

	if (clicked)
	{
		_released = true;
	}
	if (!clicked && _released){
		_released = false;
		if (InputHandler::Instance()->getMousePosition()->getX() < 250){
			if (mouseY < _number_of_attributes)
			{
				if (_player->getMoney() >= 100){
					*_weapon_attribute_values[mouseY] += _weapon_upgrade_values[mouseY];
					*_weapon_price += 50;
					_player->setMoney(-100);
				}
			}
		}
	}

	if (_back_pressed)
	{
		_shopstate->refreshPlayer();
		Game::Instance()->getGameStateMachine()->popState();
	}
}
void UpgradeState::render(){
	for (int i = 0; i < _number_of_attributes; i++)
	{
		std::string attribute = _weapon_attribute_names[i] + "   " + std::to_string(*_weapon_attribute_values[i]);
		TextureManager::Instance()->writeText(_font_id, 50, 60 * i, 200, 50, attribute, Game::Instance()->getRenderer());
	}
	_back_button.draw();
}

bool UpgradeState::onEnter(){
	_font_id = TextureManager::Instance()->loadFont("8-BIT WONDER", Game::Instance()->getRenderer());
	LoaderParams* params = new LoaderParams(500, 50, 100, 50, 0);
	_back_button.init(params);

	_weapon_upgrade_values[0] = 1;
	_weapon_upgrade_values[1] = -10;
	_weapon_upgrade_values[2] = 50;
	_weapon_upgrade_values[3] = 10;

	return true;
}
bool UpgradeState::onExit(){
	return true;
}

std::string UpgradeState::getStateID() const{
	return "UPGRADE STATE";
}

void UpgradeState::setShopState(ShopState* shopstate){
	_shopstate = shopstate;
}
void UpgradeState::setProjectileWeapon(Projectile_Weapon* weapon){
	_projectile_weapon = weapon; 
	_type = 1;
	_number_of_attributes = 4;

	_weapon_attribute_names[0] = "Damage";
	_weapon_attribute_values[0] = &weapon->getDamage();
	_weapon_attribute_names[1] = "Reload Time";
	_weapon_attribute_values[1] = &weapon->getRechargeTime();
	_weapon_attribute_names[2] = "Ammunition";
	_weapon_attribute_values[2] = &weapon->getAmmo();
	_weapon_attribute_names[3] = "Bullet Speed";
	_weapon_attribute_values[3] = &weapon->getBulletSpeed();

	_weapon_price = &weapon->getPrice();
}
void UpgradeState::setMeleeWeapon(Melee_Weapon* weapon){
	_melee_weapon = weapon;
	_type = 2;
	_number_of_attributes = 2;

	_weapon_attribute_names[0] = "Damage";
	_weapon_attribute_values[0] = &weapon->getDamage();
	_weapon_attribute_names[1] = "Reload Time";
	_weapon_attribute_values[1] = &weapon->getRechargeTime();
	
	_weapon_price = &weapon->getPrice();
}
void UpgradeState::setPlayer(Player* player){
	_player = player;
}
