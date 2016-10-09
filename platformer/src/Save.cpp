#include <fstream>
#include <iostream>
#include "Save.h"
#include "StateParser.h"
#include "Melee_Weapon.h"
#include "Projectile_Weapon.h"

bool Save::SetLevel(int set_level){
	std::string level = std::to_string(set_level);

	std::ofstream save_level;
	save_level.open("assets/Save_Data/Saved_Level.txt");
	save_level << level;
	save_level.close();
	return true;
}
bool Save::Save(Player* player){
	std::ofstream save_file;
	SDLGameObject_Values values;
	player->writeData(values);

	save_file.open("assets/Save_Data/Saved_Data.txt");
	save_file << "player\n";
	save_file << "end\n";
	save_file << "attr\n";
	save_file << "money " << values.money << "\n";
	save_file << "skill_points " << values.skill_points << "\n";
	save_file << "walkSpeed " << values.walkSpeed << "\n";
	save_file << "runSpeed " << values.runSpeed << "\n";
	save_file << "weight " << values.weight << "\n";
	save_file << "jumpHeight " << values.jumpHeight << "\n";
	save_file << "health " << values.health << "\n";
	save_file << "end\n";
	for (int i = 0; i < 3; i++){
		std::cout << i << " : " << player->getWeaponType(i) << std::endl;
		if (player->getWeaponType(i) == 1){
			std::cout << "SAVING PROJECTILE WEAPON" << std::endl;
			Projectile_Weapon_Values projectile_values, base_values;
			player->writeProjectileData(i, projectile_values);

			StateParser::readProjectileValues(projectile_values.type, base_values);

			save_file << "projectile_weapon\n";
			save_file << "type " << projectile_values.type << "\n";
			save_file << "price " << projectile_values.price << "\n";
			save_file << "id " << projectile_values.id - base_values.id << "\n";
			save_file << "range " << projectile_values.range - base_values.range << "\n";
			save_file << "damage " << projectile_values.damage - base_values.damage << "\n";
			save_file << "bulletSpeed " << projectile_values.bulletSpeed - base_values.bulletSpeed << "\n";
			save_file << "ammunition " << projectile_values.ammunition - base_values.ammunition << "\n";
			save_file << "rechargeTime " << projectile_values.rechargeTime - base_values.rechargeTime << "\n";
			save_file << "position " << i << "\n";
			save_file << "end\n";
		}
		else if (player->getWeaponType(i) == 2){
			std::cout << "SAVING MELEE WEAPON" << std::endl;
			Melee_Weapon_Values melee_values, base_values;
			player->writeMeleeData(i, melee_values);
			
			StateParser::readMeleeValues(melee_values.type, base_values);

			save_file << "melee_weapon\n";
			save_file << "type " << melee_values.type << "\n";
			save_file << "price " << melee_values.price - base_values.price << "\n";
			save_file << "id " << melee_values.id - base_values.id << "\n";
			save_file << "range " << melee_values.range - base_values.range << "\n";
			save_file << "damage " << melee_values.damage - base_values.damage << "\n";
			save_file << "rechargeTime " << melee_values.rechargeTime - base_values.rechargeTime << "\n";
			save_file << "position " << i << "\n";
			save_file << "end\n";
		}
	}

	save_file.close();

	return true;
}
