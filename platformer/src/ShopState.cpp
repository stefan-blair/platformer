#include "ShopState.h"
#include "Camera.h"
#include "PlayState.h"
#include "UpgradeState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "Save.h"

Shop_Item::Shop_Item()
	:
	delete_clicked(false),
	upgrade_clicked(false),
	delete_button(&delete_clicked),
	upgrade_button(&upgrade_clicked)
{
}
int Shop_Item::width = 80;
int Shop_Item::height = 40;

ShopState::ShopState()
	: 
	GameState(), 
	_continueButton(&_continue),
	_released(false)
{
}


ShopState::~ShopState()
{
}

void ShopState::update(){

	upgradeButtons();
	sellButtons();
	buyButtons();

	_continueButton.update();
	if (_continue)
	{
		Save::Save(&_player);
		Game::Instance()->getGameStateMachine()->clearStates();
		Game::Instance()->getGameStateMachine()->changeState(new PlayState());
	}
}

void ShopState::render(){
	_continueButton.draw();
	for (int i = 0; i < _projectile_end; i++)
	{
		std::string toWrite;
		if (i < _potion_end){
			Potion* potion = _potions[i];
			toWrite = potion->getType()+"  Buy for " + std::to_string(potion->getPrice());
		}
		else if (i < _melee_end){
			Melee_Weapon* weapon = _melee_weapons[i - _potion_end];
			toWrite = weapon->getType() + " Buy for " + std::to_string(weapon->getPrice());
		}
		else if (i < _projectile_end){
			Projectile_Weapon* weapon = _projectile_weapons[i - _melee_end];
			toWrite = weapon->getType() + " Buy for " + std::to_string(weapon->getPrice());
		}
		TextureManager::Instance()->writeText(_font_id, 10, i * _itemHeight, 300, 20, toWrite, Game::Instance()->getRenderer());
	}
	for (int i = 0; i < 3; i++)
	{
		std::string toWrite;
		switch (_player_items[i].type)
		{
		case 1:
			toWrite = _player_items[i].projectile_weapon->getType();
			break;
		case 2:
			toWrite = _player_items[i].melee_weapon->getType();
			break;
		case 3:
			toWrite = "Nothing";
			break;
		}
		_player_items[i].delete_button.draw();
		_player_items[i].upgrade_button.draw();
		TextureManager::Instance()->writeText(_font_id, _player_items[i].x, _player_items[i].y, 80, 40, toWrite, Game::Instance()->getRenderer());
	}
	TextureManager::Instance()->writeText(_font_id, 450, 10, 60, 20, std::to_string(_player.getMoney()), Game::Instance()->getRenderer());
}

bool ShopState::onEnter(){
	Camera::setCurrentX(0);
	Camera::setCurrentY(0);
	loadPlayer();

	_font_id = TextureManager::Instance()->loadFont("8-BIT WONDER", Game::Instance()->getRenderer());

	PotionShop::getPotions(_potions);

	_potion_end = _potions.size();
	for (int i = 0; i < Melee_Data::_amountOfTypes; i++){
		Melee_Weapon_Values values;
		StateParser::readMeleeValues(Melee_Data::_strings[i], values);
		_melee_weapons.push_back(new Melee_Weapon(&_player));
		_melee_weapons.back()->init(values);
	}
	_melee_end = _potion_end + _melee_weapons.size();
	for (int i = 0; i < Projectile_Data::_amountOfTypes; i++){
		Projectile_Weapon_Values values;
		StateParser::readProjectileValues(Projectile_Data::_strings[i], values);
		_projectile_weapons.push_back(new Projectile_Weapon(&_player));
		_projectile_weapons.back()->init(values);
	}
	_projectile_end = _melee_end + _projectile_weapons.size();
	_scroll_offset = 0;
	_itemHeight = 50;

	LoaderParams* params = new LoaderParams(400, 300, 201, 72, 0);
	_continueButton.init(params);

	return true;
}

bool ShopState::onExit(){
	for (int i = 0; i < _potions.size(); i++){
		delete _potions[i];
	}
	for (int i = 0; i < _melee_weapons.size(); i++){
		delete _melee_weapons[i];
	}
	for (int i = 0; i < _projectile_weapons.size(); i++){
		delete _projectile_weapons[i];
	}
	std::cout << "EXITING SHOP" << std::endl;
	Save::Save(&_player);
	return true;
}

void ShopState::upgradeButtons(){
	for (int i = 0; i < 3; i++){
		_player_items[i].upgrade_button.update();

		if (_player_items[i].upgrade_clicked)
		{
			std::cout << "Upgrading item " << std::endl;
			UpgradeState* upgradestate = new UpgradeState();
			upgradestate->setShopState(this);
			upgradestate->setPlayer(&_player);
			switch (_player_items[i].type)
			{
			case 1:
				std::cout << " UPGRADING PROJECTILE WEAPON " << std::endl;
				upgradestate->setProjectileWeapon(_player_items[i].projectile_weapon);
				Game::Instance()->getGameStateMachine()->pushState(upgradestate);
				break;
			case 2:
				std::cout << " UPGRADING MELEE WEAPON " << std::endl;

				upgradestate->setMeleeWeapon(_player_items[i].melee_weapon);
				Game::Instance()->getGameStateMachine()->pushState(upgradestate);
				break;
			case 3:
				delete upgradestate;
				break;
			}
		}
	}
}
void ShopState::sellButtons(){
	for (int i = 0; i < 3; i++){
		_player_items[i].delete_button.update();

		if (_player_items[i].delete_clicked)
		{
			std::cout << "Selling item " << std::endl;
			switch (_player_items[i].type)
			{
			case 1:
				_player.setMoney(_player_items[i].projectile_weapon->getPrice() / 2);
				delete _player_items[i].projectile_weapon;
				_player.equip(i, 0, 0);
				refreshPlayer();
				//toWrite = _player_items[i].projectile_weapon->getType();
				break;
			case 2:
				_player.setMoney(_player_items[i].melee_weapon->getPrice() / 2);
				delete _player_items[i].melee_weapon;
				_player.equip(i, 0, 0);
				refreshPlayer();
				//toWrite = _player_items[i].melee_weapon->getType();
				break;
			case 3:
				break;
			}
		}
	}
}
void ShopState::buyButtons(){
	int _mouseX = InputHandler::Instance()->getMousePosition()->getX();
	int _mouseY = InputHandler::Instance()->getMousePosition()->getY() / _itemHeight;

	bool clicked = InputHandler::Instance()->getMouseButtonState(0) && _mouseX < 320;

	if (clicked)
	{
		_released = true;
	}

	if (_released && !clicked){
		_released = false;
		if (_mouseY < _potion_end)
		{			
			Potion* potion = _potions[_mouseY];
			std::cout << "POTION CLICKED:  " << potion->getType()<< std::endl;

			if (checkEnough(potion->getPrice())){
				std::cout << "POTION BOUGHT:  " << potion->getType() << std::endl;
				potion->apply(_player);
			}
		}
		else if (_mouseY < _melee_end)
		{
			Melee_Weapon* weapon = _melee_weapons[_mouseY - _potion_end];
			if (checkEnough(weapon->getPrice()))
			{
				std::cout << "IS ENOUGH" << std::endl;
				int index = _player.getFreeWeaponSpace();
				if (index != 3)
				{
					Melee_Weapon_Values values;
					StateParser::readMeleeValues(weapon->getType(), values);
					std::cout << values.range << std::endl;
					Melee_Weapon* newWeapon = new Melee_Weapon(&_player);
					newWeapon->init(values);
					_player.equip(index, 0, newWeapon);
					_player.setMoney(-weapon->getPrice());
					refreshPlayer();
				}
			}
		}
		else if (_mouseY < _projectile_end)
		{
			Projectile_Weapon* weapon = _projectile_weapons[_mouseY - _melee_end];
			if (checkEnough(weapon->getPrice()))
			{
				std::cout << "IS ENOUGH" << std::endl;
				int index = _player.getFreeWeaponSpace();
				if (index != 3)
				{
					std::cout << "THERE IS ENOUGH SPACE" << std::endl;
					Projectile_Weapon_Values values;
					StateParser::readProjectileValues(weapon->getType(), values);
					std::cout << values.range << std::endl;
					Projectile_Weapon* newWeapon = new Projectile_Weapon(&_player);
					newWeapon->init(values);
					_player.equip(index, newWeapon, 0);
					_player.setMoney(-weapon->getPrice());
					refreshPlayer();
				}
			}
		}
	}
}

void ShopState::refreshPlayer(){
	for (int i = 0; i < 3; i++)
	{
		_player_items[i].x = 350 + (i * 100);
		_player_items[i].y = 100;
		_player_items[i].type = _player.getWeaponType(i);

		LoaderParams* params = new LoaderParams(_player_items[i].x, _player_items[i].y + 50, _player_items[i].width, _player_items[i].height, 0);
		_player_items[i].upgrade_button.init(params);

		params = new LoaderParams(_player_items[i].x, _player_items[i].y + 100, _player_items[i].width, _player_items[i].height, 0);
		_player_items[i].delete_button.init(params);


		switch (_player.getWeaponType(i)){
		case 1:
			_player_items[i].melee_weapon = 0;
			_player_items[i].projectile_weapon = _player.getProjectileWeapon(i);
			break;
		case 2:
			_player_items[i].melee_weapon = _player.getMeleeWeapon(i);
			_player_items[i].projectile_weapon = 0;
			break;
		case 3:
			_player_items[i].melee_weapon = 0;
			_player_items[i].projectile_weapon = 0;
			break;
		}
	}
}

void ShopState::loadPlayer(){
	_player = Player();
	StateParser::loadStatePlayerAttr(&_player);

	refreshPlayer();
}

std::string ShopState::getStateID() const{
	return "SHOPSTATE";
}

inline bool ShopState::checkEnough(int price){
	return _player.getMoney() >= price;
}