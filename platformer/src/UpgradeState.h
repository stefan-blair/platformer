#include "GameState.h"
#include "Melee_Weapon.h"
#include "Projectile_Weapon.h"
#include "Button.h"
#include "ShopState.h"

#pragma once
class UpgradeState : public GameState
{
public:
	UpgradeState();
	~UpgradeState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;

	void setPlayer(Player*);
	void setShopState(ShopState*);
	void setProjectileWeapon(Projectile_Weapon*);
	void setMeleeWeapon(Melee_Weapon*);
private:
	int _font_id;
	int _type;
	int _number_of_attributes;
	int* _weapon_price;
	int* _weapon_attribute_values[5];
	int  _weapon_upgrade_values[5];
	std::string _weapon_attribute_names[5];

	bool _released;
	bool _back_pressed;
	Button _back_button;
	ShopState* _shopstate;
	Projectile_Weapon* _projectile_weapon;
	Melee_Weapon* _melee_weapon;
	Player* _player;
};

