//#include <vector>
#include "GameState.h"
#include "Button.h"
#include "Player.h"

#include "Potions.h"
#include "Melee_Weapon_Types.h"
#include "Projectile_Weapon_Types.h"

#pragma once

struct Shop_Item
{
	Shop_Item();

	Projectile_Weapon* projectile_weapon;
	Melee_Weapon* melee_weapon;
	Button 
		delete_button,
		upgrade_button;
	int type;
	int x, 
		y;
	static int 
		width, 
		height;
	bool 
		delete_clicked,
		upgrade_clicked;
};

class ShopState : public GameState
{
public:
	ShopState();
	~ShopState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const; 
	void refreshPlayer();
private:
	void applyPotion(int);
	void loadPlayer();

	void upgradeButtons(); 
	void sellButtons();
	void buyButtons();

	inline bool checkEnough(int);

	bool _continue;
	Button _continueButton;

	bool _released;

	int _scroll_offset;
	int _font_id;
	int _itemHeight;

	std::vector<Potion*> _potions;
	int _potion_end;
	std::vector<Melee_Weapon*> _melee_weapons;
	int _melee_end;
	std::vector<Projectile_Weapon*> _projectile_weapons;
	int _projectile_end;

	Shop_Item _player_items[3];

	Player _player;

};

